/**
 * file: main.c
 * description: This program does things (or will when it's done)
 * author: Cody Nettesheim
 */
#include <stdlib.h>
#include "delay.h"
#include "keypad.h"
#include "lcd.h"
#include "servo.h"

//Memory-mapped registers for the clock control
#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830
#define RCC_APB1ENR (volatile uint32_t*) 0x40023840
//Upper and lower bound for pulse width (us) for the SG90 servo
#define PULSE_MIN 500
#define PULSE_MAX 2400
//Adjust pulse width by this many us each time it is changed by the user
#define PULSE_INCREMENT 100

//Servos: {GPIO base addr, TIM base addr, GPIO pin #, TIM channel #}
servo arm[5] = {
    //PB5, TIM3-2
    {(GPIO*) 0x40020400, (TIMER*) 0x40000400, 5, 2},
    //PB6, TIM4-1
    {(GPIO*) 0x40020400, (TIMER*) 0x40000800, 6, 1},
    //PB7, TIM4-2
    {(GPIO*) 0x40020400, (TIMER*) 0x40000800, 7, 2},
    //PB8, TIM4-3
    {(GPIO*) 0x40020400, (TIMER*) 0x40000800, 8, 3},
    //PB9, TIM4-4
    {(GPIO*) 0x40020400, (TIMER*) 0x40000800, 9, 4}
};

//Store arm position
int position[5] = {1500, 1500, 1500, 1500, 1500};

//State control variables
char input = '\0';
int current_servo = 0;

void main(void) {
    //Enable clock for GPIOB and TIM3-4
    *RCC_AHB1ENR |= 0b10;
    *RCC_APB1ENR |= 0b110;
    //Initialize peripherals
    lcd_init();
    key_init();
    for (int i = 0; i < 5; i++) {
        servo_init(&arm[i]);
        servo_set_us(&arm[i], position[i]);
    }
    //Print startup message
    lcd_print_string("For instruction,");
    lcd_set_position(1, 0);
    lcd_print_string("RTFM.");
    delay_s(2);
    lcd_clear();
    lcd_print_string("Servo 1");
    lcd_set_position(1, 0);
    lcd_print_num(position[0]);
    while (1) {
            //Get user input
            input = key_getchar();
            //Select a different servo if user entered a number between 1 and 5
            if (input >= 0x31 && input <= 0x35) {
                current_servo = input - 0x31;
                lcd_clear();
                lcd_print_string("Servo ");
                lcd_print_num(current_servo + 1);
            //Increase pulse width if user pressed 'A' and servo is not already at max pulse width
            } else if (input == 'A' && position[current_servo] < PULSE_MAX) {
                position[current_servo] += PULSE_INCREMENT;
                servo_set_us(&arm[current_servo], position[current_servo]);
                lcd_set_position(1,0);
                lcd_print_num(position[current_servo]);
                //Derease pulse width if user pressed 'B' and servo is not already at min pulse width
            } else if (input == 'B' && position[current_servo] > PULSE_MIN) {
                position[current_servo] -= PULSE_INCREMENT;
                servo_set_us(&arm[current_servo], position[current_servo]);
                lcd_set_position(1,0);
                lcd_print_num(position[current_servo]);
            }
    }
}
