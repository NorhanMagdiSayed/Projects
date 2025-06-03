# main.py
#Python Script to Run YOLOv8 and Send Output via Serial
from ultralytics import YOLO
import argparse
import math
import serial
import time

temp_arr = []

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--model", required=True, default="./models/best.pt")
    args = parser.parse_args()

    classNames = [
        'mouse_bite', 'spur', 'missing_hole',
        'short', 'open_circuit', 'excess_copper'
    ]

    ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
    ser.reset_input_buffer()

    model = YOLO(args.model)
    results = model.predict('tcp://192.168.137.36:8080', stream=True, imgsz=416)

    for result in results:
        boxes = result.boxes
        for box in boxes:
            probs = math.ceil((box.conf[0] * 100)) / 100
            print(f"Confidence = {probs}")

            cls = int(box.cls[0])
            cls_str = str(cls) + "\n"

            if len(temp_arr) < 1:
                x = str.encode(cls_str)
                print(x)
                ser.write(x)
                temp_arr = []

            elif cls_str != temp_arr[-1]:
                temp_arr.append(cls_str)
                x = str.encode(temp_arr[-1])
                print(x)
                ser.write(x)
                temp_arr = []
