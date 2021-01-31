#include "Debug.h"
#include "string.h"

void traductionUART(char* message)
{
    for (uint8_t i = 0; i < strlen(message) - 1; i++)
    {
        transmissionUART(message[i]);
    }
}

void traductionUART(char message)
{
	transmissionUART(message);
}