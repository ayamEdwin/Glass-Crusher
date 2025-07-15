#pragma once

#include "main.h"
#include "PWM.h"
#include "DigitalOut.h"


#define STEP_VAL 0.01f
#define FULL_SPEED 1.0f
#define INIT_SPEED 0.0f


 /* @brief  motor functions*/
class Motor {
        private:
               PwmOut t1_pwm;
               PwmOut t2_pwm;
               DigitalOut t1_en;
               DigitalOut t2_en;
               float targetSpeed;
        public:
              /* @brief this constructor initializes pin and off all motors
               * @param pwm1 pwm pin connected via transistor 1 
               * @param pwm2 pwm pin connected via transistor 2  
               * @param en1  enable pin for transistor 1    
               * @param en2 enable pin for transistor 2
              */
              Motor (pin_name pwm1, pin_name pwm2, pin_name en1, pin_name en2, float target_speed);
              /* @brief performs a soft start operation with gradual pwm increment
               * over a time period
               * @param motorPin periphal pin motor has been connected to
               * @param rampDelay the time taken to go from minimum speed to target speed
                 (acceleration)
              */
              void soft_start(unsigned long rampDelay);

              /* @brief performs a soft stop operation with gradual pwm decrement
               * over a time period
               * @param motorPin periphal pin motor has been connected to
               * @param rampDelay the time taken to go from operating back to minimum/zero
               (deceleration)
              */
              void soft_stop(unsigned long rampDelay);

              /* @brief spins motor at full speed
               * @param motorPin periphal pin motor has been connected to
              */
              void impulse();

              /* @brief reverse the motor to the opposite direction
               * @param motorPin periphal pin motor has been connected to
              */
              void driveReverse(float duty_cycle);

              /* @brief drives motor forward */
              void driveForward(float duty_cycle);

              /* @brief breaks motor */
              void applyBreak();

              /* @brief all motors off */
              void offState();

};

// #endif // motor.h