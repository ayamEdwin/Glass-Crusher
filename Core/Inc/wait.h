#include "main.h"


namespace wait {
      /* delay class in milli seconds */
      class ThisThread {
              public:
                    static void sleep_for(uint32_t time_ms);
      };
}

/* includes delay in global scope */
using namespace wait;