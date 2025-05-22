#include "wait.h"


/* @brief delays for specified time in milliseconds
 * @param time_ms delay time in milliseconds
 */
 void ThisThread::sleep_for(uint32_t time_ms) {
                  /* call to delay function from LL Driver*/
                  LL_mDelay(time_ms);
 }