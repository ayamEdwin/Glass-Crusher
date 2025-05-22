#pragma  once
#include "main.h"



namespace gp_output {
            class DigitalOut{
                          private:
                                uint32_t portNum;
                                uint32_t pinNum;
                          public:
                                // constructor to initialize gpio output pins 
                                DigitalOut(PinName pin);

                                // writes to specified pin
                                void write(int value);
    
                                //return state of output pin
                                int read();

                };
}


using namespace gp_output;

