/**
 * file: servo.c
 * description: These routines use PWM to control servo motors with the STM32f4.
 * author: Cody Nettesheim
 */
#include <peripherals.h>
#include "servo.h"

void servo_init(servo *motor) {
    //Set pin to alternate function mode
    motor->gpio->MODER &= ~(0b11   << 2 * motor->pin);
    motor->gpio->MODER |=  (0b10   << 2 * motor->pin);
    //First 8 pins use low AFR, second 8 use high AFR
    if (motor->pin <= 7) {
        motor->gpio->AFRL  &= ~(0b1111 << 4 * motor->pin);
        motor->gpio->AFRL  |=  (0b0010 << 4 * motor->pin);
    } else {
        motor->gpio->AFRH  &= ~(0b1111 << 4 * (motor->pin - 8));
        motor->gpio->AFRH  |=  (0b0010 << 4 * (motor->pin - 8));
    }
    //Set timer to PWM mode 1
    switch(motor->channel) {
    case 1:
        //Channel 1: set bits 4 to 6 on CCMR1
        motor->timer->CCMR1  &= ~(0b111 << 4);
        motor->timer->CCMR1  |=  (0b110 << 4);
        break;
    case 2:
        //Channel 2: set bits 12 to 14 on CCMR1
        motor->timer->CCMR1  &= ~(0b111 << 12);
        motor->timer->CCMR1  |=  (0b110 << 12);
        break;
    case 3:
        //Channel 3: set bits 4 to 6 on CCMR2
        motor->timer->CCMR2  &= ~(0b111 << 4);
        motor->timer->CCMR2  |=  (0b110 << 4);
        break;
    case 4:
        //Channel 4: set bits 12 to 14 on CCMR2
        motor->timer->CCMR2  &= ~(0b111 << 12);
        motor->timer->CCMR2  |=  (0b110 << 12);
        break;
    }
    //Enable output compare
    motor->timer->CCER |= 1 << 4 * (motor->channel - 1);
    //Enable update generation
    motor->timer->EGR  |= 1;
    //Load wave period into ARR
    motor->timer->ARR  = SERVO_PERIOD_MS * TICKS_MS;
    //Enable counter
    motor->timer->CR1  |= 1;
}

void servo_set_us(servo *motor, unsigned int us) {
    //Load pulse duration into CCRx
    switch (motor->channel) {
    case 1:
        //Channel 1: CCR1
        motor->timer->CCR1 = us * TICKS_US;
        break;
    case 2:
        //Channel 2: CCR2
        motor->timer->CCR2 = us * TICKS_US;
        break;
    case 3:
        //Channel 3: CCR3
        motor->timer->CCR3 = us * TICKS_US;
        break;
    case 4:
        //Channel 4: CCR4
        motor->timer->CCR4 = us * TICKS_US;
        break;
    }
}


void servo_set_deg(servo *motor, unsigned int deg) {
    //Keep angle within bounds
    if (deg > 180) {
        deg = 180;
    }
    //Convert degrees to microseconds
    unsigned int us = deg * 1000 / 180 + 1000;
    //Set position
    servo_set_us(motor, us);
}
