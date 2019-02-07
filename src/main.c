/**
 * file: main.c
 * description: This program does things (or will when it's done)
 * author: Cody Nettesheim
 */
#include "delay.h"
#include "lcd.h"
#include "servo.h"

void main()
{
    //Initialize peripherals
    lcd_init();
    servo_init();
    //Display placeholder message on LCD
    lcd_print_string("Hello, world!");
    while (1) {
        //Set servo to -90 degrees
        servo_set_pos(1000);
        delay_ms(1000);
        //Set servo to 0 degrees
        servo_set_pos(1500);
        delay_ms(1000);
        //Set servo to +90 degrees
        servo_set_pos(2000);
        delay_ms(1000);
    }
}
