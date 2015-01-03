#ifndef TOOLS_BITS_H
#define	TOOLS_BITS_H

#include <stdbool.h>

/**
 *  \file bits.h
 *  \brief Utility to manipulate bits in registers
 */
 
/**
 *  \var regPtr
 *  \brief Pointer to a register
 */
typedef volatile unsigned int* regPtr;

/**
 *  \struct bitPtr
 *  \brief Pointer to a bit inside a register
 */
struct bitPtr {
    regPtr reg;
    unsigned char n;
};
typedef struct bitPtr bitPtr;

/**
 *  \brief Initialises a bitPtr variable
 *  
 *  \param [in] bptr bitPtr variable to initialise
 *  \param [in] reg Pointer to the register
 *  \param [in] n Bit in that register
 */
void bitInit(bitPtr *bptr, regPtr reg, unsigned char n);
/**
 *  \brief Set a bitPtr to 1 or 0
 *  
 *  \param [in] bptr bitPtr to set
 *  \param [in] b Value to set to
 */
void bitSet(bitPtr bptr, bool b);
/**
 *  \brief Get a bitPtr's value
 *  
 *  \param [in] rb 
 *  \return bitPtr's value
 *  
 *  \details Details
 */
bool bitGet(bitPtr rb);

#endif	/* TOOLS_BITS_H */

