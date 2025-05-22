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

int main(void) {
  SystemClock_Config();
  while(1){
      
  }
}


///*
//int main(void) {
//      /* system core clock configuration */
//      SystemClock_Config();
//      //SystemCoreClockUpdate();
//      printf("Generating Pwm signal...\n");
//      //PwmOut pwm("PA4");
//      DigitalOut led(PA0);
//      DigitalOut no_write_state(PA1);
//      DigitalIn  button(PB11);
//      DigitalOut ON_BOARD_LED(PD2);

//      // pwm settings
//     // pwm.setFrequency(1000);
//      float duty = 0.0f;
//      float step = 0.05f;

//      // DigitalOut test 1 (pin state = 1)
//      led.write(1);
//      printf("Led Value: %i", led.read());

//      // DigitalOut test (pin state = 0)
//      printf("No value written to pin: %i", no_write_state.read());

//      // internal pullup
//      button.mode(PullUp);

//     while(1){
//              // Digital Test
//               if (button.read() == 1) {
//                    ON_BOARD_LED.write(1);
                    
//               }
//               else {ON_BOARD_LED.write(0);}

//               /*// pwm test
//               pwm.write(duty);
//               // wait test
//               ThisThread::sleep_for(100);

//               duty += step;
//               if (duty >= 1.0f || duty <= 0.0f) {
//               step = -step; // reverse direction
//                }*/
//        }

//}

/*************************** End of file ****************************/
