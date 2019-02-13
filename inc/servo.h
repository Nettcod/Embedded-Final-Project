/**
 * file: servo.h
 * description: These routines use PWM to control servo motors with the STM32f4.
 * author: Cody Nettesheim
 */
#ifndef SERVO_H_
#define SERVO_H_

//Memory mapped registers
#define TIM3_CR1    (volatile uint32_t*) 0x40000400
#define TIM3_EGR    (volatile uint32_t*) 0x40000414
#define TIM3_CCMR1  (volatile uint32_t*) 0x40000418
#define TIM3_CCER   (volatile uint32_t*) 0x40000420
#define TIM3_CNT    (volatile uint32_t*) 0x40000424
#define TIM3_ARR    (volatile uint32_t*) 0x4000042C
//#define TIM2_CCR1   (volatile uint32_t*) 0x40000034
#define TIM3_CCR2   (volatile uint32_t*) 0x40000438
#define GPIOA_MODER (volatile uint32_t*) 0x40020000
#define GPIOA_AFRL  (volatile uint32_t*) 0x40020020
#define GPIOA_AFRH  (volatile uint32_t*) 0x40020024
#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830
#define RCC_APB1ENR (volatile uint32_t*) 0x40023840
//Clock ticks per second and microsecond
#define TICKS_S  180000000
#define TICKS_MS 180000
#define TICKS_US 180
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
