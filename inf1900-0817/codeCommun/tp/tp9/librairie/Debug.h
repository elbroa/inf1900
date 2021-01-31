#include "UART.h"

#ifdef DEBUG

#define DEBUG_PRINT(x) traductionUART (x)

#else

# define DEBUG_PRINT(x) do {} while (0)

#endif


