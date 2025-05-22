#include "pwm.h"


namespace core_pwm {

/* @brief initializes pin for pwm
 * @param pin refers to the name of pwm pin
 */
PwmOut::PwmOut(const char* pin) : pinName(pin) {
    for (const auto& entry : pinMap) {
        if (strcmp(entry.pin, pinName) == 0) {
            gpioPort = entry.port;
            gpioPin = entry.gpioPin;
            timer = entry.timer;
            channel = entry.channel;
            alternateFunction = entry.af;
            break;
        }
    }

    initGPIO();
    initTimer();
    configurePWM();
}

void PwmOut::initGPIO() {
    if (gpioPort == GPIOA) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    else if (gpioPort == GPIOB) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = gpioPin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = alternateFunction;
    LL_GPIO_Init(gpioPort, &GPIO_InitStruct);
}

void PwmOut::initTimer() {
    if (timer == TIM3) LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
    else if (timer == TIM14) LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM14);

    LL_TIM_InitTypeDef TIM_InitStruct = {0};
    TIM_InitStruct.Prescaler = (SystemCoreClock / 1000000) - 1; // 1us tick
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload = 1000 - 1; // default 1ms
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    LL_TIM_Init(timer, &TIM_InitStruct);
    LL_TIM_EnableCounter(timer);
    LL_TIM_GenerateEvent_UPDATE(timer);
}

void PwmOut::configurePWM() {
    LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};
    TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
    TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
    TIM_OC_InitStruct.CompareValue = 0;
    LL_TIM_OC_Init(timer, channel, &TIM_OC_InitStruct);
    LL_TIM_OC_EnablePreload(timer, channel);
    LL_TIM_CC_EnableChannel(timer, channel);
}

void PwmOut::setPeriod(float seconds) {
    uint32_t us = static_cast<uint32_t>(seconds * 1e6f);
    LL_TIM_SetAutoReload(timer, us - 1);
    LL_TIM_OC_SetCompareCH1(timer, (us - 1) / 2); // 50% default
    LL_TIM_GenerateEvent_UPDATE(timer);
}

void PwmOut::setFrequency(float hz) {
    if (hz > 0.0f)
        setPeriod(1.0f / hz);
}

void PwmOut::write(float duty) {
    if (duty < 0.0f) duty = 0.0f;
    if (duty > 1.0f) duty = 1.0f;
    uint32_t arr = LL_TIM_GetAutoReload(timer);
    uint32_t ccr = static_cast<uint32_t>(duty * arr);
    LL_TIM_OC_SetCompareCH1(timer, ccr);
}



} // namespace core_pwm
































/*#include "pwm.h"*/


/*namespace core_pwm {
          /* pwm class implementation */
          //Pwm::Pwm() {
                        /*LL_TIM_InitTypeDef TIM_InitStruct = {0};
                        LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};

                        LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

                        /* Peripheral clock enable */
                        //LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM14);

                        /*TIM_InitStruct.Prescaler = LL_TIM_IC_FILTER_FDIV1_N4-LL_TIM_IC_FILTER_FDIV1_N2;
                        TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
                        //scanf("%i", f_TC);
                        TIM_InitStruct.Autoreload = 100-LL_TIM_IC_FILTER_FDIV1_N2;
                        TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
                        LL_TIM_Init(TIM14, &TIM_InitStruct);
                        LL_TIM_DisableARRPreload(TIM14);
                        LL_TIM_OC_EnablePreload(TIM14, LL_TIM_CHANNEL_CH1);
                        TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
                        TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
                        TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
                        TIM_OC_InitStruct.CompareValue = 0;
                        TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
                        LL_TIM_OC_Init(TIM14, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);
                        LL_TIM_OC_DisableFast(TIM14, LL_TIM_CHANNEL_CH1);
                       
                        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
                        /**TIM14 GPIO Configuration
                        PA4   ------> TIM14_CH1
                        */
                        /*GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
                        GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
                        GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
                        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
                        GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
                        GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
                        LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

                        // Enable capture/compare channel 1 output (TIM14_CCER)
                        TIM14->CCER |= TIM_CCER_CC1E;

                        // Enable counter (TIM14_CR1)
                        TIM14->CR1 |= TIM_CR1_CEN;

                        // Generate an update event to load registers (TIM14_EGR)
                        TIM14->EGR |= TIM_EGR_UG;
            
          }
}*/
