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
//#include "mbed.h"


/*********************************************************************
*
*       main()
*
*  Function description
*   Application entry point.
*/

#include "mbed.h" // includes all libraries


DigitalOut ON_BOARD_LED(LED);
InterruptIn startButton(SOFT_START_BTN);
Motor crushingMotor(PWM_1, PWM_2, EN_1, EN_2, 1.0); //pwm1, pwm2, en1, en2

// interrupt flags
volatile uint8_t startBtn_pressed_flag = BUTTON_NOT_PRESSED_FLAG;

void detect_startBtn_interrupt(){
      //  updates flag to indicate interrupt
      startBtn_pressed_flag = BUTTON_PRESSED_FLAG;
}



int main(void) {
      ON_BOARD_LED.write(1);
      startButton.mode(PullUp);
      startButton.rise(&detect_startBtn_interrupt);
      
      while(1){
              if (startBtn_pressed_flag){
                    // resets the flag immediately after detecting it
                    startBtn_pressed_flag = BUTTON_NOT_PRESSED_FLAG;

                    // soft starts motor
                    crushingMotor.soft_start(1);
              }
        }

}


/*************************** End of file ****************************/
