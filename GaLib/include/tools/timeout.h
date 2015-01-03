#ifndef TIMEOUT_H
#define TIMEOUT_H

#include <stdint.h>
#include <stdbool.h>

void timeoutInit(void);
void timeoutSet(uint16_t msb, uint16_t lsb);
bool timeoutCheck(void);

#endif // TIMEOUT_H
