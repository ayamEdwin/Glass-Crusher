#ifndef  MOTOR_H
#define  MOTOR_H


#define STEP_VAL 0.05f
#define FULL_SPEED 1.0f
#define INIT_SPEED 0.0f


 /* @brief  motor functions*/
class Motor {
        public:
              /* @brief performs a soft start operation with gradual pwm increment
               * over a time period
               * @param motorPin periphal pin motor has been connected to
               * @param targetSpeed the exact cruching speed
               * @param rampTime the time taken to go from minimum speed to target speed
                 (acceleration)
              */
              void soft_start(float targetSpeed, unsigned long rampTime);

              /* @brief performs a soft stop operation with gradual pwm decrement
               * over a time period
               * @param motorPin periphal pin motor has been connected to
               * @param rampTime the time taken to go from operating back to minimum/zero
               (deceleration)
              */
              void soft_stop(unsigned long rampTime);

              /* @brief spins motor at full speed
               * @param motorPin periphal pin motor has been connected to
              */
              void impulse();

              /* @brief reverse the motor to the opposite direction
               * @param motorPin periphal pin motor has been connected to
              */
              void reverse(int targetSpeed, unsigned long rampTime);

              /* @brief drives motor forward */
              void driveForward(float duty_cycle);

              /* @brief breaks motor */
              void applyBreak();

              /* @brief all motors off */
              void offState();

              /* @brief reverses motor direction*/
              void driveReverse(float duty_cycle);

};

#endif // motor.h