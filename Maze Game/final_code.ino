#include <Metro.h>

//let's do this
#include <LiquidCrystal_I2C.h>
#include <VarSpeedServo.h>  //include the VarSpeedServo library
LiquidCrystal_I2C lcd(0x27, 16, 2);
Metro servo_delay = Metro(200);
Metro score_delay = Metro(500);
Metro one_delay = Metro(20);
Metro check_score_delay = Metro(3000);
int buzzer = 11 ;
Metro two_delay = Metro(200);
int post = 2 ;
Metro timer_delay = Metro(1000);
int round_init = 1 ;
#define joy_xaxis  A0
#define joy_yaxis  A1
unsigned long  game_start  ;
#define joy_button 8
#define touch_sensor 9
int number_ofplayers = 0 ;
int joy_center = 500 ;
int range = 23;  //please enter the range + 3 seconds for execution
int rr = 0 ;
int servoval;
unsigned long diff_score_1 = 0 ;
unsigned long diff_score_2 = 0 ;
unsigned long timer_start = 0 ;
int riri = 0 ;
int mode = 0 ;
int range_time = range ; //time for one round
const int sp = 20;   //speed setting for VarSpeedServo SlowMove
const int y_colevel = 97;   //set so the maze pitch direction is level
const int x_colevel = 90;    //set so the maze roll direction is level
int ylevel;
int xlevel;
int num = 0 ;
int score_1 = 0 ;
int score_player1 = 0 ;
int score_player2 = 0 ;


VarSpeedServo servo_yaxis;   //c
VarSpeedServo servo_xaxis ;


void setup() {
  // put your setup code here, to run once:
  lcd.init(); // initialize the lcd
  lcd.backlight();
  Serial.begin(9600) ;
  servo_yaxis.attach(3);  //attach servos to pins
  servo_xaxis.attach(5);
  pinMode(joy_button, INPUT_PULLUP);
  pinMode(touch_sensor, INPUT);
  pinMode(buzzer, OUTPUT);

  servo_yaxis.slowmove(y_colevel, sp);  //Home servos to start
  servo_xaxis.slowmove(x_colevel, sp);
  delay(200);
  initiate();
  running_biss();
  two_modes();
  number_players() ;


}

void loop()
{

  if ((mode == 1) && (servo_delay.check() == 1))
  {
    if ( !(analogRead(joy_xaxis) >= 450 && analogRead(joy_xaxis) <= 580 ) )
    {
      servoval = analogRead(joy_xaxis) ;
      Serial.println(servoval);
      xlevel = map(servoval, 10, 1023, -30, 30);
    }

    if ( !(analogRead(joy_yaxis) >= 450 && analogRead(joy_yaxis) <= 580 ) )
    {
      servoval = analogRead(joy_yaxis);
      Serial.println(servoval);
      ylevel = map(servoval, 10, 1023, -30, 30);
    }
    servo_xaxis.slowmove(x_colevel - xlevel, sp);
    servo_yaxis.slowmove(y_colevel  - ylevel, sp);


  }
  if ((mode == 2) && (servo_delay.check() == 1))
  {

    while (Serial.available() > 0)
    {
      ylevel =  Serial.parseInt();
      xlevel =  Serial.parseInt();
      if (Serial.read() == '\n') break;
    }
    ylevel = constrain(ylevel , -20, 20);
    xlevel = constrain(xlevel, -20, 20);
    servo_xaxis.slowmove(x_colevel - xlevel, sp);
    servo_yaxis.slowmove(y_colevel + ylevel, sp);

  }


  if ((num == 1) && (round_init != 5))  // one player
  {

    round_5() ;


  }
  if (( num == 2) && (post != 6))   // two players
  {

    rounds_2();

  }



}


void rounds_2 (void)
{

  if ((score_delay.check() == 1) && digitalRead(touch_sensor) == HIGH )
  {


    if ( (millis() - diff_score_1) > 10000)
    {
      diff_score_1 = millis();

      lcd.setCursor(7, 0);
      if ( post % 2 == 0 )
      {
        score_player1 ++ ;
        lcd.print(score_player1) ;
        digitalWrite(buzzer, HIGH);
        delay(500);
        digitalWrite(buzzer, LOW);
      }
      else
      {
        score_player2 ++ ;
        lcd.print(score_player2) ;
        digitalWrite(buzzer, HIGH);
        delay(500);
        digitalWrite(buzzer, LOW);
      }
    }
  }

  if ((timer_delay.check() == 1) && (range_time != 0))
  {
    if ( range_time == range )
    {
      rr = range_time - 3 ;
    }
    timer_start = millis();
    lcd.setCursor(7, 1);
    lcd.print(rr) ;
    if (rr < 10 )
    {
      lcd.setCursor(8, 1);
      lcd.print(" ");

    }

    range_time = range_time - 1  ;
    rr = rr - 1 ;

  }

  if (range_time == 1)
  { round_init ++ ;
    range_time = range ;
    post = post + 1 ;
    r4() ;

  }
  if (post == 6)
  {
    check_score();
  }

}


void two_players(void)
{
  if (post == 2)
  {
    lcd.clear();
    lcd.print("ROUND 1 for");
    lcd.setCursor(4, 1);
    lcd.print(" Player 1 ");
    delay(3000);
    one_player();
  }
}
void r4 (void)
{

  if (post == 3)
  {
    lcd.clear();
    lcd.print("ROUND 1 for");
    lcd.setCursor(4, 1);
    lcd.print(" Player 2 ");
    delay(3000);
    one_player();


  }
  else if (post == 4)
  {
    lcd.clear();
    lcd.print("ROUND 2 for");
    lcd.setCursor(4, 1);
    lcd.print(" Player 1 ");
    delay(3000);
    one_player();


  }
  else if (post == 5)
  {
    lcd.clear();
    lcd.print("ROUND 2 for");
    lcd.setCursor(4, 1);
    lcd.print(" Player 2 ");
    delay(3000);
    one_player();


  }
}














void game_mode(void)
{
  do
  {

  } while (digitalRead(joy_button) == HIGH ) ;
  delay(10);
  if (analogRead(joy_xaxis) > 930 && digitalRead(joy_button) == LOW )
  {
    mode = 1 ;
    lcd.clear();
    lcd.print("CONTROLLED VIA");
    lcd.setCursor(5, 1);
    lcd.print("JOYSTICK") ;

    delay(2000);

  }
  else if (analogRead(joy_xaxis) < 100 && digitalRead(joy_button) == LOW )
  {
    mode = 2 ;
    lcd.clear();
    lcd.print("CONTROLLED VIA");
    lcd.setCursor(8, 1);
    lcd.print("APP") ;
    delay(2000);

  }
  else
  {
    game_mode();
  }
}


void two_modes ()
{
  lcd.clear();
  lcd.print("play via : ");
  lcd.setCursor(0, 1);
  lcd.print("a)joystick ");
  lcd.setCursor(11, 1);
  lcd.print("b)APP  ");
  delay(2000);
  game_mode() ;
}
void initiate()
{
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("MAZE GAME");
  lcd.setCursor(4, 1);
  lcd.print("BY : NORHAN");
  delay(1000);
  for (int positionCounter = 0; positionCounter < 13; positionCounter++)
  {

    lcd.scrollDisplayLeft();

    delay(200);
  }

  for (int positionCounter = 0; positionCounter < 29; positionCounter++)
  {
    lcd.scrollDisplayRight();
    delay(200);
  }
}



void round_5 (void)
{

  if ((score_delay.check() == 1) && digitalRead(touch_sensor) == HIGH )
  {

    if ( (millis() - diff_score_1) > 10000)
    {
      diff_score_1 = millis();
      score_1 ++ ;
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);

      lcd.setCursor(7, 0);
      lcd.print(score_1) ;

    }

  }

  if ((timer_delay.check() == 1) && (range_time != 0))
  {
    if ( range_time == range )
    {
      rr = range_time - 3 ;
    }
    timer_start = millis();
    lcd.setCursor(7, 1);
    lcd.print(rr) ;
    if (rr < 10 )
    {
      lcd.setCursor(8, 1);
      lcd.print(" ");

    }

    range_time = range_time - 1  ;
    rr = rr - 1 ;

  }

  if (range_time == 1)
  { round_init ++ ;
    range_time = range ;
    lcd.clear();
    lcd.print("ROUND NUMBER ");
    lcd.setCursor(8, 1);
    lcd.print(round_init);

    delay(3000);
    one_player();
  }
  if (round_init == 5)
  {
    check_score();
  }



}

void check_score(void)
{
  if (num == 1)
  {
    if ( score_1 > 0)
    {

      lcd.clear();
      image_1();
      lcd.setCursor(0, 0);
      lcd.print("ur score");
      lcd.setCursor(0, 1);
      lcd.print(score_1);
      lcd.setCursor(13, 0);
      delay(3000);
    }
    else if (score_1 == 0)
    {

      lcd.clear();
      image_sad();
      lcd.setCursor(0, 0);
      lcd.print("GAME OVER");
      lcd.setCursor(5, 1);
      lcd.print("LOSER ");
      delay(3000);
    }
  }
  if (num == 2 )
  {
    if (score_player1 > score_player2)
    {
      lcd.clear();
      // image_1();
      lcd.setCursor(0, 0);
      lcd.print("WINNER IS ");
      delay(1500);
      lcd.setCursor(0, 1);
      lcd.print("PLAYER 1 ");   //drum roll if i can make soundeffects
      lcd.setCursor(13, 0);
      delay(3000);
    }
    else if (score_player1 < score_player2)
    {
      lcd.clear();
      // image_1();
      lcd.setCursor(0, 0);
      lcd.print("WINNER IS ");
      delay(1500);
      lcd.setCursor(0, 1);
      lcd.print("PLAYER 2 ");   //drum roll if i can make soundeffects
      lcd.setCursor(13, 0);
      delay(3000);
    }
    else
    {
      lcd.clear();
      // image_1();
      lcd.setCursor(0, 0);
      lcd.print("botH OF YOU");
      delay(1500);
      lcd.setCursor(0, 1);
      lcd.print("ARE lOseRs");   //drum roll if i can make soundeffects
      lcd.setCursor(13, 0);
      delay(3000);
    }
  }
}





void number_players (void)
{
  lcd.clear();
  lcd.print("Number of players : ");
  lcd.setCursor(0, 1);
  lcd.print("a) one ");
  lcd.setCursor(8, 1);
  lcd.print("a) two  ");
  delay(2000);
  choose();


}

void choose (void)
{

  do
  {

  } while (digitalRead(joy_button) == HIGH ) ;
  delay(10);
  if (analogRead(joy_xaxis) > 930 && digitalRead(joy_button) == LOW )
  {
    number_ofplayers = 1 ;
    lcd.clear();
    lcd.print("one player ");
    num = 1 ;
    lcd.setCursor(8, 1);
    lcd.print("mode") ;

    delay(2000);
    player();
    one_player() ;

  }
  else if (analogRead(joy_xaxis) < 100 && digitalRead(joy_button) == LOW )
  {
    number_ofplayers = 2 ;
    lcd.clear();
    lcd.print("two player ");
    num = 2 ;
    lcd.setCursor(8, 1);
    lcd.print("mode") ;
    delay(2000);
    //player();
    two_players();

  }
  else
  {
    choose();
  }
}









void one_player (void)
{

  lcd.clear();
  lcd.print("SCORE:");
  lcd.setCursor(0, 1);
  lcd.print("TIME:");
  lcd.setCursor(7, 0);
  if (num == 1)
  {
    lcd.print(score_1) ;

  }
  else if (num == 2)
  {
    if ( post % 2 == 0 )
    {

      lcd.print(score_player1) ;
    }
    else
    {
      lcd.print(score_player2) ;
    }
  }



}





void player (void)
{
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("game starts  ");
  lcd.setCursor(1, 1);
  lcd.print("in  ");
  game_start = millis();

  timer1();
}


void timer1 ( void)
{
  while ((millis() - game_start) < 5000)
  {
    if (millis() ==  (game_start + 3000) )
    {
      lcd.setCursor(4, 1);
      lcd.print("3" ) ;
      delay(500);
      lcd.clear();
      lcd.print("ball in ");
      lcd.setCursor(0, 1);
      lcd.print("start position");

    }
    else if (millis() == (game_start + 2000))
    {
      lcd.setCursor(4, 1);
      lcd.print("2") ;
      delay(10);
      timer1();

    }
    else if (millis() == (game_start + 1000))
    {
      lcd.setCursor(4, 1);
      lcd.print("1") ;
      delay(10);
      timer1();

    }
  }
}


void running_biss(void)
{
  int f = 4;
  int s;


  byte mario11[8] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00001,
    B00001,
    B00001,
    B00000,

  };
  byte mario12[8] = {
    B00001,
    B00001,
    B00001,
    B00001,
    B00000,
    B00000,
    B00000,
    B00000
  };
  byte mario13[8] = {
    B00000,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,

  };
  byte mario14[8] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11110
  };

  byte mario15[8] = {
    B00000,
    B00000,
    B11000,
    B00000,
    B11000,
    B11100,
    B11000,
    B10000,

  };

  byte mario16[8] = {
    B00000,
    B10000,
    B10000,
    B10000,
    B00000,
    B00000,
    B10000,
    B00000
  };

  byte mario21[8] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  };

  byte mario22[8] = {
    B00111,
    B00111,
    B00111,
    B00000,
    B00001,
    B00011,
    B00011,
    B00001
  };

  byte mario23[8] = {
    B00000,
    B01111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B01111,

  };

  byte mario24[8] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11001,
    B00000,
    B10000
  };
  byte mario25[8] = {
    B00000,
    B00000,
    B11100,
    B10000,
    B11100,
    B11110,
    B11100,
    B11000,

  };

  byte mario26[8] = {
    B11111,
    B11111,
    B10110,
    B11110,
    B11110,
    B11110,
    B00000,
    B00000,
  };

  byte mario31[8] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,

  };


  byte mario32[8] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00011,
    B00011,
    B00111,
    B00000
  };


  byte mario33[8] = {
    B00000,
    B00000,
    B00111,
    B01111,
    B01111,
    B11111,
    B11111,
    B11111,

  };

  byte mario34[8] = {
    B01111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B00111,
    B00111
  };

  byte mario35[8] = {
    B00000,
    B00000,
    B10000,
    B11110,
    B11000,
    B11110,
    B11111,
    B11110,

  };

  byte mario36[8] = {
    B11100,
    B11110,
    B11100,
    B11000,
    B11000,
    B10000,
    B00000,
    B10000,
  };

  byte mario41[8] = {
    B00000,
    B00011,
    B00111,
    B00111,
    B01111,
    B01111,
    B01111,
    B00011,

  };


  byte mario42[8] = {
    B01111,
    B01111,
    B01111,
    B01111,
    B00111,
    B00011,
    B00011,
    B00011
  };

  byte mario43[8] = {
    B00000,
    B11000,
    B11111,
    B11100,
    B11111,
    B11111,
    B11111,
    B11110,
  };

  byte mario44[8] = {
    B11100,
    B11110,
    B11110,
    B11110,
    B11100,
    B11100,
    B11110,
    B10000
  };


  byte mario51[8] = {
    B00000,
    B00001,
    B00011,
    B00011,
    B00111,
    B00111,
    B00111,
    B00001,
  };

  byte mario52[8] = {
    B11111,
    B11111,
    B11011,
    B00111,
    B01111,
    B11111,
    B11100,
    B01110,
  };

  byte mario53[8] = {
    B00000,
    B11100,
    B11111,
    B11110,
    B11111,
    B11111,
    B11111,
    B11111,
  };

  byte mario54[8] = {
    B11111,
    B11111,
    B11110,
    B11111,
    B11111,
    B01111,
    B00000,
    B00000,
  };



  byte mario55[8] = {
    B00000,
    B00000,
    B10000,
    B00000,
    B00000,
    B10000,
    B00000,
    B00000,
  };


  byte mario56[8] = {
    B11000,
    B11000,
    B10000,
    B10000,
    B10000,
    B10000,
    B00000,
    B00000,
  };


  byte mario61[8] = {
    B00000,
    B00000,
    B00000,
    B00001,
    B00001,
    B00011,
    B00011,
    B00011,
  };

  byte mario62[8] = {
    B00001,
    B00011,
    B00111,
    B01111,
    B01111,
    B11111,
    B11000,
    B00000,
  };



  byte mario63[8] = {
    B00000,
    B00000,
    B11110,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
  };

  byte mario64[8] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11110,
    B11100,
    B11110,
  };

  byte mario65[8] = {
    B00000,
    B00000,
    B00000,
    B10000,
    B00000,
    B10000,
    B11000,
    B10000,
  };


  byte mario66[8] = {
    B00000,
    B10000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  };

  byte clean[8] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  };

  lcd.clear();

  s = 250 / f;
  for (int a = 0; a < 16; a++) //for loop to repeat marios animation until the end of the display
  {
    int b = a + 1;
    int c = a + 2;
    int d = a + 3;
    int e = a + 4;

    lcd.createChar(1, mario11);
    lcd.createChar(2, mario12);
    lcd.createChar(3, mario13);
    lcd.createChar(4, mario14);
    lcd.createChar(5, mario15);
    lcd.createChar(6, mario16);
    lcd.createChar(7, clean);

    lcd.setCursor(a, 0);
    lcd.write(1);
    lcd.setCursor(a, 1);
    lcd.write(2);
    lcd.setCursor(b, 0);
    lcd.write(3);
    lcd.setCursor(b, 1);
    lcd.write(4);
    lcd.setCursor(c, 0);
    lcd.write(5);
    lcd.setCursor(c, 1);
    lcd.write(6);
    delay(s);

    lcd.createChar(1, mario21);
    lcd.createChar(2, mario22);
    lcd.createChar(3, mario23);
    lcd.createChar(4, mario24);
    lcd.createChar(5, mario25);
    lcd.createChar(6, mario26);

    lcd.setCursor(a, 0);
    lcd.write(1);
    lcd.setCursor(a, 1);
    lcd.write(2);
    lcd.setCursor(b, 0);
    lcd.write(3);
    lcd.setCursor(b, 1);
    lcd.write(4);
    lcd.setCursor(c, 0);
    lcd.write(5);
    lcd.setCursor(c, 1);
    lcd.write(6);

    delay(s);

    lcd.createChar(1, mario31);
    lcd.createChar(2, mario32);
    lcd.createChar(3, mario33);
    lcd.createChar(4, mario34);
    lcd.createChar(5, mario35);
    lcd.createChar(6, mario36);

    lcd.setCursor(a, 0);
    lcd.write(1);
    lcd.setCursor(a, 1);
    lcd.write(2);
    lcd.setCursor(b, 0);
    lcd.write(3);
    lcd.setCursor(b, 1);
    lcd.write(4);
    lcd.setCursor(c, 0);
    lcd.write(5);
    lcd.setCursor(c, 1);
    lcd.write(6);

    delay(s);
    lcd.setCursor(7, 0);
    lcd.print("ENJOY");
    lcd.createChar(1, mario41);
    lcd.createChar(2, mario42);
    lcd.createChar(3, mario43);
    lcd.createChar(4, mario44);
    lcd.createChar(7, clean);
    lcd.setCursor(a, 0);
    lcd.write(7);
    lcd.setCursor(a, 1);
    lcd.write(7);
    lcd.setCursor(b, 0);
    lcd.write(1);
    lcd.setCursor(b, 1);
    lcd.write(2);
    lcd.setCursor(c, 0);
    lcd.write(3);
    lcd.setCursor(c, 1);
    lcd.write(4);
    delay(s);




  }



















}




void image_1() {
  lcd.clear();

  byte image26[8] = {B01110, B10001, B10101, B11111, B11111, B00000, B00010, B00001};
  byte image27[8] = {B01110, B10001, B10101, B11111, B11111, B00000, B01000, B10000};
  byte image11[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B01001, B00110};
  byte image10[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B01001, B00110};


  lcd.createChar(0, image26);
  lcd.createChar(1, image27);
  lcd.createChar(2, image11);
  lcd.createChar(3, image10);


  lcd.setCursor(9, 1);
  lcd.write(byte(0));
  lcd.setCursor(10, 1);
  lcd.write(byte(1));
  lcd.setCursor(10, 0);
  lcd.write(byte(2));
  lcd.setCursor(9, 0);
  lcd.write(byte(3));

}
void image_sad() {
  lcd.clear();

  byte image30[8] = {B10000, B01000, B10100, B01000, B10001, B00010, B00100, B01000};
  byte image31[8] = {B00001, B00010, B00101, B00010, B10001, B01000, B00100, B00010};
  byte image13[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00001};
  byte image29[8] = {B00010, B00000, B00000, B00000, B00000, B00000, B00000, B00000};
  byte image14[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B10000};
  byte image32[8] = {B01000, B00000, B00000, B00000, B00000, B00000, B00000, B00000};
  byte image16[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B10000};
  byte image15[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00001};

  lcd.createChar(0, image30);
  lcd.createChar(1, image31);
  lcd.createChar(2, image13);
  lcd.createChar(3, image29);
  lcd.createChar(4, image14);
  lcd.createChar(5, image32);
  lcd.createChar(6, image16);
  lcd.createChar(7, image15);

  lcd.setCursor(13, 1);
  lcd.write(byte(0));
  lcd.setCursor(14, 1);
  lcd.write(byte(1));
  lcd.setCursor(12, 0);
  lcd.write(byte(2));
  lcd.setCursor(12, 1);
  lcd.write(byte(3));
  lcd.setCursor(13, 0);
  lcd.write(byte(4));
  lcd.setCursor(15, 1);
  lcd.write(byte(5));
  lcd.setCursor(15, 0);
  lcd.write(byte(6));
  lcd.setCursor(14, 0);
  lcd.write(byte(7));
}
