/**
 * file: main.c
 * description: This program does things (or will when it's done)
 * author: Cody Nettesheim
 */
#include "delay.h"
#include "lcd.h"

int main()
{
    //Initialize peripherals
    lcd_init();
    //Display placeholder message on LCD
    lcd_print_string("Hello, world! (WIP)");
    //Program exit
    return 0;
}
