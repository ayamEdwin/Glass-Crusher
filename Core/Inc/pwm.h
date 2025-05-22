#pragma once //ifndef, define
#include "main.h"


/* @brief pin map entry */
typedef struct {
    const char* pin;
    GPIO_TypeDef* port;
    uint32_t gpioPin;
    TIM_TypeDef* timer;
    uint32_t channel;
    uint8_t af;
} PinMap;

/* @brief Pwm compatible pins 
 * @array {pin_name, port, pin_number, timer, timer_channel, alternate_func}
*/
static const PinMap pinMap[] = {
    {"PA4", GPIOA, LL_GPIO_PIN_4, TIM14, LL_TIM_CHANNEL_CH1, LL_GPIO_AF_4},
    {"PA6", GPIOA, LL_GPIO_PIN_6, TIM3,  LL_TIM_CHANNEL_CH1, LL_GPIO_AF_1},
    {"PA7", GPIOA, LL_GPIO_PIN_7, TIM3,  LL_TIM_CHANNEL_CH2, LL_GPIO_AF_1},
    {"PB0", GPIOB, LL_GPIO_PIN_0, TIM3,  LL_TIM_CHANNEL_CH3, LL_GPIO_AF_1},
    {"PB1", GPIOB, LL_GPIO_PIN_1, TIM3,  LL_TIM_CHANNEL_CH4, LL_GPIO_AF_1},
    {"PA2", GPIOA, LL_GPIO_PIN_2, TIM15, LL_TIM_CHANNEL_CH1, LL_GPIO_AF_0},
    {"PA3", GPIOA, LL_GPIO_PIN_3, TIM15, LL_TIM_CHANNEL_CH2, LL_GPIO_AF_0},
    {"PC4", GPIOC, LL_GPIO_PIN_4, TIM14, LL_TIM_CHANNEL_CH1, LL_GPIO_AF_4},
};


/* @brief groups pwm api into single a scope
 * so that other classes can be added
 */
namespace core_pwm {

          class PwmOut {
                public:
                    /* Constructor e.g., "PA4" */
                    PwmOut(const char* pin); 

                    void setPeriod(float seconds);
                    void setFrequency(float hertz);
                    void write(float DutyCycle);

                private:
                    void initTimer();
                    void initGPIO();
                    void configurePWM();

                    const char* pinName;
                    TIM_TypeDef* timer;
                    uint32_t channel;
                    GPIO_TypeDef* gpioPort;
                    uint32_t gpioPin;
                    uint8_t alternateFunction;
          };

} // namespace core_pwm

/* @brief brings core_pwm into glbal scope */
using namespace core_pwm;





























///* Define to prevent recursive inclusion -------------------------------------*/
//#ifndef PWM_H
//#define PWM_H

///* Includes ------------------------------------------------------------------*/
//#include "main.h"

//#ifdef __cplusplus
//extern "C" {
//#endif


//#if defined(USE_FULL_ASSERT)
//#include "stm32_assert.h"
//#endif /* USE_FULL_ASSERT */


///* Error handler function prototype ---------------------------------------------*/
//void Error_Handler(void);


///* Private defines -----------------------------------------------------------*/
//#ifndef NVIC_PRIORITYGROUP_0
//#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
//                                                                 4 bits for subpriority */
//#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
//                                                                 3 bits for subpriority */
//#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
//                                                                 2 bits for subpriority */
//#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
//                                                                 1 bit  for subpriority */
//#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
//                                                                 0 bit  for subpriority */
//#endif


//#ifdef __cplusplus
//}
//#endif

///* creates a namespace with identifier core_pwm */
//namespace core_pwm {
//          /* prototypes */
//          class Pwm {
//                    //int f_TC;
//                    public:
//                          Pwm(); // constructor
//          };
//}

///* includes namespace core_pwm into global scope */
//using namespace core_pwm;


//#endif /* PWM_H */

