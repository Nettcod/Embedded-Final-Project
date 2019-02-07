/**
 * file: servo.c
 * description: These routines use PWM to control servo motors with the STM32f4.
 * author: Cody Nettesheim
 */
#include "servo.h"
#include <gpio.h>

void servo_init() {
    //Enable clock for GPIOD and TIM2
    *RCC_AHB1ENR |= 8;
    *RCC_APB1ENR |= 1;
    //Set PD3 to alternate function mode
    *GPIOD_MODER &= ~(0b11 << 6);
    *GPIOD_MODER |=  (0b10 << 6);
    *GPIOD_AFRL  &= ~(0xF << 12);
    *GPIOD_AFRL  |=  (0x2 << 12);
    //Set TIM2 to PWM mode 1
    *TIM2_CCMR1 &= ~(0b111 << 12);
    *TIM2_CCMR1 |=  (0b110 << 12);
    //Enable TIM2 Channel 2
    *TIM2_CR1 |= 1 << 7;
    *TIM2_CCMR1 |= 1 << 11;
    *TIM2_CCER |= 1 << 4;
}

void servo_set_pos(unsigned int us) {
    //Load wave period into ARR
    *TIM2_ARR  = TICKS_S / SERVO_HZ;
    //Load pulse duration into CCR2
    *TIM2_CCR2 = TICKS_US * us;
    //Enable counter
    *TIM2_CR1 |= 1;
}
