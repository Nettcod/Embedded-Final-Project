/**
 * file: servo.c
 * description: These routines use PWM to control servo motors with the STM32f4.
 * author: Cody Nettesheim
 */
#include "servo.h"
#include <gpio.h>

void servo_init() {
    //Enable clock for GPIOA and TIM3
    *RCC_AHB1ENR |= 0b01;
    *RCC_APB1ENR |= 0b10;
    //Set PB3 to alternate function mode
    *GPIOA_MODER &= ~(0b0011 << 14);
    *GPIOA_MODER |=  (0b0010 << 14);
    *GPIOA_AFRL  &= ~(0b1111 << 28);
    *GPIOA_AFRL  |=  (0b0010 << 28);
    //Set TIM3 to PWM mode 1
    *TIM3_CCMR1  &= ~(0b111 << 12);
    *TIM3_CCMR1  |=  (0b110 << 12);
    //Enable output compare
    *TIM3_CCER   |= 1 << 4;
    //Enable timer update generation
    *TIM3_EGR    |= 1;
    //Load wave period into ARR
    *TIM3_ARR    = 20 * TICKS_MS;
}

void servo_set_pos(unsigned int us) {
    //Disable counter
    *TIM3_CR1    &= ~1;
    //Load pulse duration into CCR2
    *TIM3_CCR2   = us * TICKS_US;
    //Enable counter
    *TIM3_CR1    |= 1;
}
