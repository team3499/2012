#ifndef ROBOTMAP_H
#define ROBOTMAP_H


/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
 
// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// #define LEFTMOTOR 1
// #define RIGHTMOTOR 2

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// #define RANGE_FINDER_PORT 1
// #define RANGE_FINDER_MODULE 1

//i2c
#define ARM_ACCELEROMETER_CHANNEL 1
//analog
#define RANGEFINDER_CHANNEL 1
#define CHASSIS_GYRO_CHANNEL 2
//pwm
#define DRIVE_LEFT 1,3
#define DRIVE_RIGHT 1,4
#define MAGAZINE_BELT_CHANNEL 1,5
#define SHOOTER_BELT_BOTTOM_CHANNEL 1,6
#define SHOOTER_BELT_TOP_CHANNEL 1,7
//Digital input
#define MAGAZINE_BUTTON_FRONT_CHANNEL 7
#define MAGAZINE_BUTTON_MIDDLE_CHANNEL 8
#define MAGAZINE_BUTTON_BACK_CHANNEL 9
//relays
#define ARM_MOVEMENT_CHANNEL 1
// lights
#define LEDS_BLUE_CHANNEL 1
#define LEDS_RED_CHANNEL 2
#define LEDS_WHITE_1_CHANNEL 3
#define LEDS_WHITE_2_CHANNEL 4

#endif
