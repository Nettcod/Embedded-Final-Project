/**
 * file: main.c
 * description: This program does things (or will when it's done)
 * author: Cody Nettesheim
 */
#include "delay.h"
#include "lcd.h"
#include "servo.h"

//Memory-mapped registers for the clock control
#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830
#define RCC_APB1ENR (volatile uint32_t*) 0x40023840

servo test = {(GPIO*) 0x40020000, (TIMER*) 0x40000400, 7, 2};


void main(void) {
    //Enable clock for GPIOA and TIM3
    *RCC_AHB1ENR |= 0b01;
    *RCC_APB1ENR |= 0b10;
    //Initialize peripherals
    lcd_init();
    //Display placeholder message on LCD
    lcd_print_string("Hello, world!");
    servo_init(&test);
    while (1) {
        for (int i = 1000; i < 2000; i++) {
            servo_set_us(&test, i);
            delay_ms(10);
        }
    }
}
