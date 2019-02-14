/*
 * file: keypad.c
 * description: These routines handle input from a keypad
 * author: Cody Nettesheim
 */
#include "peripherals.h"
#include "keypad.h"

//Initialize GPIO
static volatile GPIO* GPIOC = (GPIO*) 0x40020800;

/**
 * Get the position of the most significant high bit in a number
 * Parameters: number containing the bit
 * Returns:    bit position
 */
uint8_t get_bitPos(int);

void key_init() {
    //Set columns (PC0-3) to output and rows (PC4-7) to input
    GPIOC->MODER &= ~0xFFFF;
    GPIOC->MODER |= 0x0055;
    //Set rows to pullup
    GPIOC->PUPDR &= ~0xFFFF;
    GPIOC->PUPDR |= 0x5500;
}

uint8_t get_bitPos(int num) {
    int position = 0;
    //Count number of shifts taken to reach zero
    while (num > 0) {
        num >>= 1;
        position++;
    }
    //Return the position of the largest high bit
    return position;
}

uint8_t key_getkey_noblock() {
    //Keycode defaults to zero if no key was pressed
    uint8_t keycode = 0;
    uint8_t bitmask = 0b1000;
    //Iterate through all columns
    while (bitmask != 0 && keycode == 0) {
        //Set current column to low
        GPIOC->ODR |= 0xF;
        GPIOC->ODR &= ~bitmask;
        //Check rows for keypress
        uint8_t rows = (GPIOC->IDR >> 4) & 0xF;
        if (rows != 0xF) {
            //If a key was pressed, get the keycode
            rows = get_bitPos(~rows & 0xF) - 1;
            uint8_t cols = get_bitPos(bitmask);
            keycode = cols + (rows * 4);
        } else {
            //Shift to next column
            bitmask >>= 1;
        }
    }
    //Return numeric keycode value
    return keycode;
}

uint8_t key_getkey() {
    uint8_t keycode = 0;
    //Check keypad until a key is pressed
    while (keycode == 0) {
        //Get numeric keycode from keypad
        keycode = key_getkey_noblock();
    }
    //Wait for key to be released
    while (key_getkey_noblock() != 0) {}
    //Return numeric keycode
    return keycode;
}

char key_getchar() {
    //Get numeric keycode
    int keycode = key_getkey();
    //Convert to ASCII and return
    char keychar = KEYMAP[keycode];
    return keychar;
}

char key_getchar_noblock() {
    //Get numeric keycode
    int keycode = key_getkey_noblock();
    //Convert to ASCII and return
    char keychar = KEYMAP[keycode];
    return keychar;
}
