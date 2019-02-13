/**
 * file: delay.c
 * description: These functions run delays using the timers on the STM32
 * author: Cody Nettesheim
 */
#include "delay.h"

void delay_s(uint32_t n) {
    //Repeat n times
    for (int i = 0; i <= n; i++) {
        //Set clock ticks to count for
        *STK_LOAD = SYS_TICKS_S;
        //Enable timer
        *STK_CTRL &= 0xFFFF ^ (1 << CLKSOURCE);
        *STK_CTRL |= 1 << EN;
        //Busy delay: poll systick value until the value is 0
        while (*STK_VAL > 0) {}
    }
}

void delay_ms(uint32_t n) {
    //Repeat n times
    for (int i = 0; i <= n; i++) {
        //Set clock ticks to count for
        *STK_LOAD = SYS_TICKS_MS;
        //Enable timer
        *STK_CTRL &= 0xFFFF ^ (1 << CLKSOURCE);
        *STK_CTRL |= 1 << EN;
        //Busy delay: poll systick value until the value is 0
        while (*STK_VAL > 0) {}
    }
}

void delay_us(uint32_t n) {
    //Repeat n times
    for (int i = 0; i <= n; i++) {
        //Set clock ticks to count for
        *STK_LOAD = SYS_TICKS_US;
        //Enable timer
        *STK_CTRL &= 0xFFFF ^ (1 << CLKSOURCE);
        *STK_CTRL |= 1 << EN;
        //Busy delay: poll systick value until the value is 0
        while (*STK_VAL > 0) {}
    }
}
