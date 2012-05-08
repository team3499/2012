#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#define IS_DEBUG_MODE   true

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
#define ARM_ACCELEROMETER_CHANNEL      2
//analog
#define RANGEFINDER_CHANNEL            1
#define CHASSIS_GYRO_CHANNEL           2
//pwm
#define DRIVE_LEFT_FRONT               1,1
#define DRIVE_LEFT_REAR                1,2
#define DRIVE_RIGHT_MOTORS             1,3
/*There is NOT two connections for the right motors*/
#define MAGAZINE_BELT_CHANNEL          1,5
#define SHOOTER_BELT_TOP_CHANNEL       1,7
#define SHOOTER_BELT_BOTTOM_CHANNEL    1,6
//Digital input
#define MAGAZINE_BUTTON_FRONT_CHANNEL  7
#define MAGAZINE_BUTTON_MIDDLE_CHANNEL 8
#define MAGAZINE_BUTTON_BACK_CHANNEL   9
//relays
#define ARM_MOVEMENT_CHANNEL           1
// lights
#define LEDS_BLUE_CHANNEL              3
#define LEDS_RED_CHANNEL               4
#define LEDS_WHITE_1_CHANNEL           1
#define LEDS_WHITE_2_CHANNEL           2
// camera
#define CAMERA_IP_ADDR                 "10.34.99.90"
// joystick
#define JOYSTICK_COUNT                 2
#define JOYSTICK_DRIVE                 1
#define JOYSTICK_ACCESSORY             2
// NOTE: use these ^ two UNLESS Talking DIRECTLY to the Array, or initializing.
// on a side note, this is probably a really bad way to do this...
#define JOYSTICK_INIT_DRIVE            JOYSTICK_DRIVE
#define JOYSTICK_INIT_ACCESSORY        JOYSTICK_ACCESSORY
#define JOYSTICK_ARRAY_DRIVE           JOYSTICK_DRIVE-1
#define JOYSTICK_ARRAY_ACCESSORY       JOYSTICK_ACCESSORY-1

#endif
