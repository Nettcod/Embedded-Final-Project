/*
 * file: lcd.c
 * description: These routines handle the functions of an lcd
 * author: Cody Nettesheim
 */
#include <stdlib.h>
#include <math.h>
#include <gpio.h>
#include "delay.h"
#include "lcd.h"

//Initialize GPIO
static volatile GPIO* GPIOA = (GPIO*) 0x40020000;
static volatile GPIO* GPIOC = (GPIO*) 0x40020800;

void lcd_init() {
    //Wait 5ms for LCD to power on
    delay_ms(5);
    //Enable clock for GPIO
    *RCC_AHB1ENR |= 1 << GPIOAEN;
    *RCC_AHB1ENR |= 1 << GPIOCEN;
    //Set GPIO pins to output (PA4-11 and PC8-10)
    GPIOA->MODER &= ~(0xFFFFF << 8);
    GPIOA->MODER |= 0x5555 << 8;
    GPIOC->MODER &= ~(0x3F << 16);
    GPIOC->MODER |= 0x15 << 16;
    //Set display to 8-bit mode and 2-line mode
    lcd_cmd(0x38);
    delay_us(37);
    //Set entry mode
    lcd_cmd(0x6);
    delay_us(37);
    //Turn on display
    lcd_cmd(0xD);
    delay_us(37);
    //Clear and home display
    lcd_clear();
    lcd_home();
}

void lcd_data(uint8_t data) {
    //Set RS to high and R/W to low
    GPIOC->ODR &= ~(0x7 << 8);
    GPIOC->ODR |= 1 << 8;
    //Clear bits and send data
    GPIOA->ODR &= ~(0xFF << 4);
    GPIOA->ODR |= data << 4;
    //Pulse En
    GPIOC->ODR |= 1<<10;
    delay_us(1);
    GPIOC->ODR &= ~(1<<10);
    delay_us(38);
}

void lcd_cmd(uint8_t cmd) {
    //Set RS and R/W to low
    GPIOC->ODR &= ~(0x7 << 8);
    //Clear bits and send cmd
    GPIOA->ODR &= ~(0xFF << 4);
    GPIOA->ODR |= cmd << 4;
    //Pulse En
    GPIOC->ODR |= 1<<10;
    delay_us(1);
    GPIOC->ODR &= ~(1<<10);
    delay_us(1);
}

void lcd_clear() {
    //Send clear command to LCD controller
    lcd_cmd(0x1);
    //Wait 1.52ms for display to clear
    delay_us(15200);
}

void lcd_home() {
    //Send home command to LCD controller
    lcd_cmd(0x2);
    //Wait 1.52ms for cursor to home
    delay_us(15200);
}

void lcd_set_position(uint8_t row, uint8_t col) {
    //Shift by display width to get to the second row
    row *= LCD_WIDTH;
    col += row;
    //Return to home
    lcd_home();
    //Shift cursor until at target position
    for (int i = 0; i < col; i++) {
        //Shift cursor one place to the right
        lcd_cmd(0x14);
        //Wait 37us for LCD controller to execute command
        delay_us(37);
    }
}

int lcd_print_string(char *str) {
    //Initialize string index
    int i = 0;
    //Print each character to LCD
    while (str[i] != '\0') {
        //Send character to LCD controller
        lcd_data(str[i]);
        //Wait 37us for display to print character
        delay_us(37);
        //Increment index
        i++;
    }
    //Return number of characters printed
    return i;
}

int lcd_print_num(int num) {
    //Find amount of digits in number
    int size = 0;
    for (int i = num; i > 0; i /= 10) {
        size++;
    }
    //Convert number to ASCII string
    char output[size];
    itoa(num, output, 10);
    //Output string to LCD controller
    lcd_print_string(output);
    //Return number of digits printed
    return size;
}
