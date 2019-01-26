/**
 * file: delay.h
 * description: These functions run delays using the timers on the STM32
 * author: Cody Nettesheim
 */
#include <inttypes.h>

//include guards
#ifndef DELAY_H_
#define DELAY_H_

//Addresses for memory mapped registers
#define STK_CTRL (volatile uint32_t*) 0xE000E010
#define STK_LOAD (volatile uint32_t*) 0xE000E014
#define STK_VAL  (volatile uint32_t*) 0xE000E018
//Bit indexes in STK_CTRL
#define EN        00
#define TICKINT   01
#define CLKSOURCE 02
#define COUNTFLAG 16
//Clock ticks for certain times
#define TICKS_S  2000000
#define TICKS_MS 2000
#define TICKS_US 2

/**
 * Delay for n seconds
 * Parameters: number of sec to delay for
 * Returns:    void
 */
void delay_s(uint32_t n);

/*
 * Delay for n milliseconds
 * Parameters: number of ms to delay for
 * Returns:    void
 */
void delay_ms(uint32_t n);

/**
 * Delay for n microseconds
 * Parameters: number of us to delay for
 * Returns:    void
 */
void delay_us(uint32_t n);

#endif
