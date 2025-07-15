#include "motor.h"


// Constructor
Motor::Motor(pin_name pwm1, pin_name pwm2, pin_name en1, pin_name en2, float target_speed):
     t1_pwm(pwm1), t2_pwm(pwm2), t1_en(en1), t2_en(en2),  targetSpeed(target_speed){
          // turns motor off 
          t1_pwm.write(0.0);
          t2_pwm.write(0.0);
          t2_en.write(0);
          t1_en.write(0);
     }
    
// PwmOut greenLed(PTB0);

void Motor::applyBreak(){
          t1_en.write(1);
          t2_en.write(1);
  }


void Motor::driveForward(float duty_cycle){
          t1_pwm.write(duty_cycle);
          t2_pwm.write(0.0);
          t2_en.write(0);
          t1_en.write(1);
  }


void Motor::driveReverse(float duty_cycle){
          applyBreak();
          //offState();
          wait_ms(10);
          t2_pwm.write(duty_cycle);
          t1_pwm.write(0.0);
          t1_en.write(0);
          t2_en.write(1);
  }

  
/* @brief the pwm drive needs values 0 - 65535 since all timers are 16 bits
  *to achieve a gradual acceleration from 0 to 65535, over 5 seconds, 
  *we start from 0 and every 5/65535 seconds increase it by 1.
*/
void Motor::soft_start(unsigned long rampDelay){
                           for (float dc=INIT_SPEED; dc<=targetSpeed; dc+=STEP_VAL){
                                  driveForward(dc);
                                  wait(rampDelay);
                                  //if (dc == targetSpeed) continue;
                  }
                 
}


void Motor::soft_stop(unsigned long rampDelay){
         for (float dc=targetSpeed; dc>=INIT_SPEED; dc-=STEP_VAL){
              driveForward(dc);
              wait(rampDelay);
              if (dc == INIT_SPEED) break;
         }
        
    }


void Motor::impulse(){
         driveForward(FULL_SPEED); 
}
                        
                     