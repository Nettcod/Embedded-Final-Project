/*
 * file: keypad.h
 * description: These routines handle input from a keypad
 * author: Cody Nettesheim
 */
#include <stdint.h>

#ifndef KEYPAD_H_
#define KEYPAD_H_

//Define GPIO clock address and offsets
#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830
#define GPIOCEN 2
//Characters that the key codes map to
#define KEYMAP "!123A456B789C*0#D"

/**
 * Initialize keypad GPIO
 * Parameters: none
 * Returns:    void
 */
void key_init();

/**
 * Return a numeric keycode corresponding to a keypress, or 0 if no key is pressed
 * Parameters: none
 * Returns:    numeric keycode (0-16)
 */
uint8_t key_getkey_noblock();

/**
 * Wait for a keypress and then return the corresponding keycode
 * Parameters: none
 * Returns:    numeric keycode (1-16)
 */
uint8_t key_getkey();

/**
 * Wait for a keypress and then return the corresponding ASCII value
 * Parameters: none
 * Returns:    ASCII keycode
 */
char key_getchar();

/**
 * Return the ASCII value of a keypress, or '!' if no key was pressed
 * Parameters: none
 * Returns:    ASCII keycode
 */
char key_getchar_noblock();

#endif
