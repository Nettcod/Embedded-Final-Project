/**
 * file: servo.h
 * description: These routines use PWM to control servo motors with the STM32f4.
 * author: Cody Nettesheim
 */
#ifndef SERVO_H_
#define SERVO_H_

//Memory mapped registers
#define TIM2_CR1    (volatile uint32_t*) 0x40000000
#define TIM2_CCMR1  (volatile uint32_t*) 0x40000018
#define TIM2_CCER   (volatile uint32_t*) 0x40000020
#define TIM2_CNT    (volatile uint32_t*) 0x40000024
#define TIM2_ARR    (volatile uint32_t*) 0x4000002C
#define TIM2_CCR2   (volatile uint32_t*) 0x40000038
#define GPIOD_MODER (volatile uint32_t*) 0x40020C00
#define GPIOD_AFRL  (volatile uint32_t*) 0x40020C20
#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830
#define RCC_APB1ENR (volatile uint32_t*) 0x40023840
//Clock ticks per second and microsecond
#define TICKS_S  2000000
#define TICKS_US 2
//Send a pulse to the servo 50 times per second
#define SERVO_HZ 50

/**
 * Configure GPIO and set up PWM
 * Parameters: none
 * Returns:    none
 */
void servo_init();

/**
 * Send a pulse of a specified duration every 20us to set the angle of the servo
 * Parameters: pulse duration in microseconds
 * Returns:    none
 */
void servo_set_pos(unsigned int);

#endif
