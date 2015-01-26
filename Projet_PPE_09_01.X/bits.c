#include "bits.h"

void bitInit(bitPtr *bptr, regPtr reg, unsigned char n)
{
    bptr->reg = reg;
    bptr->n = n;
}

void bitSet(bitPtr bptr, BOOL b) {
    if(b) {
        *bptr.reg = *bptr.reg | (1 << bptr.n);
    }
    else {
        *bptr.reg = *bptr.reg & (~(1 << bptr.n));
    }
}

BOOL bitGet(bitPtr rb) {
    return *rb.reg & (1 << rb.n);
}

