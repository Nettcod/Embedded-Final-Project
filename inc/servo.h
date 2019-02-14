/**
 * file: servo.h
 * description: These routines use PWM to control servo motors with the STM32f4.
 * author: Cody Nettesheim
 */
#ifndef SERVO_H_
#define SERVO_H_
#include <inttypes.h>
#include "peripherals.h"

//Clock ticks per second and microsecond
#define TICKS_S  180000000
#define TICKS_MS 180000
#define TICKS_US 180
//Servo expects a pulse every 20ms
#define SERVO_PERIOD_MS 20

//Structure for setting up a servo
typedef struct {
    //GPIO bus pin is attached to
    GPIO*  gpio;
    //Timer peripheral attached to pin
    TIMER* timer;
    //Pin number
    uint8_t pin;
    //Timer channel attached to pin
    uint8_t channel;
} servo;

/**
 * Configure GPIO and set up PWM
 * Parameters: servo to initialize
 * Returns:    none
 */
void servo_init(servo*);

/**
 * Send a pulse of a specified duration every 20us to set the angle of the servo
 * Parameters: servo and pulse duration (microseconds)
 * Returns:    none
 */
void servo_set_us(servo*, unsigned int);

/**
 * Set the desired position of a given servo in degrees
 * Parameters: servo and angle
 * Returns:    none
 */
void servo_set_deg(servo*, unsigned int);

#endif
