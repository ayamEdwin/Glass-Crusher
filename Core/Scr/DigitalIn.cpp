#include "DigitalIn.h"



namespace gp_input {

                  // Constructor implementation for DigitalIn
                  DigitalIn::DigitalIn(PinName pin) {
                            // Extracts port and pin number from PinName
                            portNum = (pin >> 4) & 0xF;  // Extracts port number
                            pinNum = (pin & 0xF);        // Extracts pin number

                            // Array of GPIO port base addresses
                            GPIO_TypeDef* GPIO_ports[] = {GPIOA, GPIOB, GPIOC, GPIOD, nullptr, GPIOF};

                            // Validate portNum
                            if (portNum >= sizeof(GPIO_ports) / sizeof(GPIO_ports[0]) || GPIO_ports[portNum] == nullptr) {
                                printf("Invalid Pin Name!");
                                return;
                            }

                            // Enable clock for the corresponding GPIO port
                            RCC->AHBENR |= (0x1 << (17 + portNum));

                            // Configure the GPIO port as input with pull-up
                            GPIO_TypeDef* GPIOx = GPIO_ports[portNum];
                            GPIOx->MODER &= ~(0x3 << (pinNum * 2));  // Reset bits to input
                            GPIOx->PUPDR &= ~(0x3 << (pinNum * 2));  // Clear bits for existing mode
                            GPIOx->PUPDR |= (0x1 << (pinNum * 2));   // Set default mode to pull-up
                        } 

                  // reads the state of specified input pin
                  int DigitalIn::read() {
                            // Array of GPIO port base addresses
                            GPIO_TypeDef* GPIO_ports[] = {GPIOA, GPIOB, GPIOC, GPIOD, nullptr, GPIOF};

                            // Validate portNum
                            if (portNum >= sizeof(GPIO_ports) / sizeof(GPIO_ports[0]) || GPIO_ports[portNum] == nullptr) {
                                printf("Invalid Pin Name!");
                                return 0;
                            }

                            // Get the GPIO port
                            GPIO_TypeDef* GPIOx = GPIO_ports[portNum];

                            // Return the pin state using IDR
                            return (GPIOx->IDR & (0x1 << pinNum)) ? 1 : 0;
                        }

                  // sets the mode
                  void DigitalIn::mode(PinMode pull) {
                            // Extracts port and pin number from PinName
                            portNum = (user_pin >> 4) & 0xF;  // Extracts port number
                            pinNum = (user_pin & 0xF);        // Extracts pin number

                            // Array of GPIO port base addresses
                            GPIO_TypeDef* GPIO_ports[] = {GPIOA, GPIOB, GPIOC, GPIOD, nullptr, GPIOF};

                            // Validate portNum
                            if (portNum >= sizeof(GPIO_ports) / sizeof(GPIO_ports[0]) || GPIO_ports[portNum] == nullptr) {
                                printf("Invalid Pin Name!");
                                return;
                            }

                            // Get the GPIO port
                            GPIO_TypeDef* GPIOx = GPIO_ports[portNum];

                            // Configure the pull mode
                            if (pull == 0) {
                                // PullNone (external resistor required)
                                GPIOx->PUPDR &= ~(0x3 << (pinNum * 2));
                            } else if (pull == 1) {
                                // PullUp
                                GPIOx->PUPDR &= ~(0x3 << (pinNum * 2)); // Clear bits for existing mode
                                GPIOx->PUPDR |= (0x1 << (pinNum * 2));  // Set mode to pull-up
                            } else if (pull == 2) {
                                // PullDown
                                GPIOx->PUPDR &= ~(0x3 << (pinNum * 2)); // Clear bits for existing mode
                                GPIOx->PUPDR |= (0x2 << (pinNum * 2));  // Set mode to pull-down
                            } else {
                                printf("Invalid Mode! Available Modes: PullNone, PullUp, PullDown");
                            }
                        }
  }
