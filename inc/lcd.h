/*
 * file: lcd.h
 * description: These routines handle the functions of an lcd
 * author: Cody Nettesheim
 */
#ifndef LCD_H_
#define LCD_H_

//LCD is 32 characters wide
#define LCD_WIDTH 40
//Define GPIO clock address and offsets
#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830
#define GPIOAEN 0
#define GPIOCEN 2

/**
 * Initialize GPIO and clear + home display
 * Parameters: none
 * Returns:    void
 */
void lcd_init();
/**
 * Send data to the LCD controller
 * Parameters: none
 * Returns:    void
 */
void lcd_data(uint8_t);
/**
 * Send command to the LCD controller
 * Parameters: none
 * Returns:    void
 */
void lcd_cmd(uint8_t);
/**
 * Clear display
 * Parameters: none
 * Returns:    void
 */
void lcd_clear();
/**
 * Move cursor to home position
 * Parameters: none
 * Returns:    void
 */
void lcd_home();
/**
 * Move cursor to a given position
 * Parameters: zero-based row and zero-based column
 * Returns:    void
 */
void lcd_set_position(uint8_t, uint8_t);
/**
 * Print a string on the display
 * Parameters: pointer to a null-terminated string to display
 * Returns:    number of chars written to display
 */
int lcd_print_string(char*);
/**
 * Print a number on the display
 * Parameters: decimal number to display
 * Returns:    number of chars written to display
 */
int lcd_print_num(int);

#endif
