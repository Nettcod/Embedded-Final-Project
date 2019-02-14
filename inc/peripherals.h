/*
 * file: peripherals.h
 * description: This file defines structs for accessing the control registers of some hardware peripherals
 * author: Cody Nettesheim
 */
#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

/*How to use:
 * Create a pointer to the structure with the base address of the peripheral.
 * To access a given control register, simply dereference it from the pointer.
 */

#include <inttypes.h>

//GPIO pins
typedef struct {
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDER;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
    uint32_t LCKR;
    uint32_t AFRL;
    uint32_t AFRH;
} GPIO;

//General purpose timers (TIM2 to TIM5)
typedef struct {
    uint32_t CR1;
    uint32_t CR2;
    uint32_t SMCR;
    uint32_t DIER;
    uint32_t SR;
    uint32_t EGR;
    uint32_t CCMR1;
    uint32_t CCMR2;
    uint32_t CCER;
    uint32_t CNT;
    uint32_t PSC;
    uint32_t ARR;
    uint32_t CCR1;
    uint32_t CCR2;
    uint32_t CCR3;
    uint32_t CCR4;
    uint32_t DCR;
    uint32_t DMAR;
    uint32_t OR;
} TIMER;

#endif
