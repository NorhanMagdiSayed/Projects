/*
 * MATH_H.h
 *
 *  Created on: 12 Aug 2021
 *      Author: norha
 */

#ifndef MATH_H_H_
#define MATH_H_H_

#define SET_BIT(REG,BITNO) (REG |=(1<<BITNO))
#define CLR_BIT(REG,BITNO) (REG &= ~(1<<BITNO))
#define TOGGLE_BIT(REG,bitno) (REG ^= ((1)<<bitno))
#define GET_BIT(REG,bitno) ((REG  >> bitno ) & (1))


#endif /* MATH_H_H_ */
