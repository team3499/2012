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

#define CHASSIS_GYRO_CHANNEL 2

#define SHOOTER_BELT_TOP_CHANNEL 3
#define SHOOTER_BELT_BOTTOM_CHANNEL 4
#define MAGAZINE_BELT_LEFT_CHANNEL 5
#define MAGAZINE_BELT_RIGHT_CHANNEL 6
#define MAGAZINE_BUTTON_FRONT_CHANNEL 7
#define MAGAZINE_BUTTON_MIDDLE_CHANNEL 8
#define MAGAZINE_BUTTON_BACK_CHANNEL 9

#endif
