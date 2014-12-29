/*
  Stepper.h - - Stepper library for Wiring/Arduino - Version 0.5
  
  Original library     (0.1) by Tom Igoe.
  Two-wire modifications   (0.2) by Sebastian Gassner
  Combination version   (0.3) by Tom Igoe and David Mellis
  Bug fix for four-wire   (0.4) by Tom Igoe, bug fix from Noah Shibley
  Support for half wave    (0.5) by Virgilio Villatora

  Drives a unipolar or bipolar stepper motor using  2 wires or 4 wires

  When wiring multiple stepper motors to a microcontroller,
  you quickly run out of output pins, with each motor requiring 4 connections. 

  By making use of the fact that at any time two of the four motor
  coils are the inverse  of the other two, the number of
  control connections can be reduced from 4 to 2. 

  A slightly modified circuit around a Darlington transistor array or an L293 H-bridge
  connects to only 2 microcontroler pins, inverts the signals received,
  and delivers the 4 (2 plus 2 inverted ones) output signals required
  for driving a stepper motor.

  The sequence of control signals for 4 control wires is as follows:

  FULL-WAVE
  
  Step C0 C1 C2 C3
     1  1  0  1  0
     2  0  1  1  0
     3  0  1  0  1
     4  1  0  0  1

  The sequence of controls signals for 2 control wires is as follows
  (columns C1 and C2 from above):

  Step C0 C1
     1  0  1
     2  1  1
     3  1  0
     4  0  0
----------------------------------------------
	 
  HALF-WAVE
  The sequence of control signals for 4 control wires is as follows:

  Step C0 C1 C2 C3
     1  1  0  0  0
     1b 1  0  1  0
     2  0  0  1  0
     2b 0  1  1  0
     3  0  1  0  0
     3b 0  1  0  1
     4  0  0  0  1
     4b 1  0  0  1
(useless for two wire)

  The circuits can be found at 
  http://www.arduino.cc/en/Tutorial/Stepper
*/

// ensure this library description is only included once
#ifndef Stepper_h
#define Stepper_h

// library interface description
class Stepper {
  public:
    // constructors:
    Stepper(int step_per_turn, int motor_pin_1, int motor_pin_2);
    Stepper(int step_per_turn, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4);
    Stepper(unsigned char half, int step_per_turn, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4);

    // speed setter method:
    void setSpeed(long whatSpeed);

    // mover method:
    void step(int step_per_turn);
	  void set_step(int step_per_turn);
	  void loop(void);

    int version(void);
	  int steps_to_run(void);
	  int position(void);

  private:
    void stepMotor(int this_step);
    void init_helper(int,int,int);
    
    int direction;        // Direction of rotation
	  int steps_left;        	// run time counter. Number of step to the next stop.
	  int speed;          // Speed in RPMs
    unsigned long step_delay;    // delay between steps, in ms, based on speed
    int number_of_steps;      // total number of steps this motor can take
    int pin_count;        // whether you're driving the motor with 2 or 4 pins
    int step_number;        // which step the motor is on
	  unsigned char is_half;  // 0 (false) --> full wave (previous library compliant);  1 (true) --> half wave driver
	  
    // motor pin numbers:
    int motor_pin_1;
    int motor_pin_2;
    int motor_pin_3;
    int motor_pin_4;
    
    long last_step_time;      // time stamp in ms of when the last step was taken
};

#endif

