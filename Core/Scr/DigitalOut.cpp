#include "main.h"
#include "DigitalOut.h"



namespace gp_output {

           // Constructor implementation for DigitalOut
                  DigitalOut::DigitalOut(PinName pin) {
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

                            // Configure the GPIO port as output and set speed to medium
                            GPIO_TypeDef* GPIOx = GPIO_ports[portNum];
                            GPIOx->MODER &= ~(0x3 << (pinNum * 2));  // Reset bits
                            GPIOx->MODER |= (0x1 << (pinNum * 2));   // Set pin mode to output
                            GPIOx->OSPEEDR |= (0x1 << (pinNum * 2)); // Set default speed to medium
                        }

                  // writes an integer value to specified pin
                  void DigitalOut::write(int value) {
                            // Array of GPIO port base addresses
                            GPIO_TypeDef* GPIO_ports[] = {GPIOA, GPIOB, GPIOC, GPIOD, nullptr, GPIOF};

                            // Validate portNum
                            if (portNum >= sizeof(GPIO_ports) / sizeof(GPIO_ports[0]) || GPIO_ports[portNum] == nullptr) {
                                printf("Invalid Pin Name!");
                                return;
                            }

                            // Get the GPIO port
                            GPIO_TypeDef* GPIOx = GPIO_ports[portNum];

                            if (value == 1) {
                                GPIOx->BSRR |= (0x1 << pinNum); // Set the pin
                            } else if (value == 0) {
                                GPIOx->BSRR |= (0x1 << (pinNum + 16)); // Reset the pin
                            } else {
                                printf("Incorrect write value. You can only write 0 or 1");
                            }
                        }

                  // reads the output state of specified pin
                  int DigitalOut::read() {
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


}

