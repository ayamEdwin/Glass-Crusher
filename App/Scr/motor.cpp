#include "motor.h"
#include "PWM.h"
#include "DigitalOut.h"

    
PwmOut T1_pwm(PTB0); // transistor 1 pwm
PwmOut T2_pwm(PTB1); // transistor 2 pwm 
DigitalOut T1_EN(PTA0); // transistor 1 enable
DigitalOut T2_EN(PTA1); // transistor 2 enable
    
// PwmOut greenLed(PTB0);

void Motor::applyBreak(){
          T1_EN.write(1);
          T2_EN.write(1);
  }


void Motor::driveForward(float duty_cycle){
          T1_pwm.write(duty_cycle);
          T2_pwm.write(0.0);
          T2_EN.write(0);
          T1_EN.write(1);
  }


void Motor::driveReverse(float duty_cycle){
          applyBreak();
          //offState();
          wait_ms(10);
          T2_pwm.write(duty_cycle);
          T1_pwm.write(0.0);
          T1_EN.write(0);
          T2_EN.write(1);
  }

  
/* @brief the pwm drive needs values 0 - 65535 since all timers are 16 bits
  *to achieve a gradual acceleration from 0 to 65535, over 5 seconds, 
  *we start from 0 and every 5/65535 seconds increase it by 1.
*/
void Motor::soft_start(float targetSpeed, unsigned long rampTime){
                           for (float dc=INIT_SPEED; dc<=FULL_SPEED; dc+=STEP_VAL){
                                  driveForward(dc);
                                  wait_ms(rampTime);
                                  if (dc == targetSpeed) break;
                  }
                 
}


void Motor::soft_stop(unsigned long rampTime){
         for (float dc=FULL_SPEED; dc>=INIT_SPEED; dc-=STEP_VAL){
              driveForward(dc);
              wait_ms(rampTime);
              if (dc == INIT_SPEED) break;
         }
        
    }
                        
                     