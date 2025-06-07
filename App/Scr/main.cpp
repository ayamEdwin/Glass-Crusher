/*********************************************************************
*                   MECHATRONICS '25 FINAL YEAR PROJECT              *
*                        Glass Crusher Firmware                      *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

Frameworks : Low Level Drivers(CMSIS), FreeRTOS
Language  : C/C++
Tools    : Embedded studio, Jlink CMD, JScope, RTT Viewer, SystemView
Team    : Edwin Setsoafia(Lead), Mannaseh Aboagye, Kartey Titus, Joseph Nkansah,
                      Kelvin Nongor, Christian Akuffo.
Comment Style: @brief describes in brief the funtionality
               @param description of parameters

NB: This is a standard for code clarity and better documentation
Adhere to it!

*/


/* all included headers and APIs from core*/
#include "main.h"
#include "pwm.h"
#include "wait.h"
#include "DigitalOut.h"
#include "DigitalIn.h"


/*********************************************************************
*
*       main()
*
*  Function description
*   Application entry point.
*/

PwmOut T1_pwm("PA4");
PwmOut T2_pwm("PA6");
DigitalOut T1_EN(PA0);
DigitalOut T2_EN(PA1);
DigitalOut ON_BOARD_LED(PD2);


void normal_drive(float duty_cycle){
        
               T1_pwm.write(duty_cycle);
               T2_EN.write(0);
               T2_pwm.write(0.0f);
               T1_EN.write(1);
}

void reverse_drive(float duty_cycle){
              // reverse
              T1_pwm.write(0.0f);
              T2_EN.write(1);
              T2_pwm.write(duty_cycle);
              T1_EN.write(0);
}


int main(void) {
      /* system core clock configuration */
      SystemClock_Config();
      ON_BOARD_LED.write(1);
      T1_pwm.setPeriod(0.001f);
      T2_pwm.setPeriod(0.001f);

     while(1){
              normal_drive(1.0f);
              ThisThread::sleep_for(5000);
              reverse_drive(0.5f);
              ThisThread::sleep_for(5000);
        }

}


/*************************** End of file ****************************/
