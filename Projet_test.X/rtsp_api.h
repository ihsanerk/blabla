

#ifndef _RTSPAPI_H
#define _RTSPAPI_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>


#ifdef __cplusplus  // Provide C++ Compatability

    extern "C" {

#endif

// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************
/*  Flash Memory is organised into ROWs of 64 instructions or 192 bytes.
    RTSP allows the user to erage a PAGE of memory which consists of EIGHT ROWs
    (512 instructions or 1536byts) at a time.
    RTSP allows the user to program a ROW (64 instructions or 192 bytes) at a
    time
*/

// *****************************************************************************
/* Function:
    int16_t flashPageErase(uint16_t nvmAdru, uint16_t nvmAdr);

  Summary:
    Flash Page Erase function

  Description:
    This function provides the interface to erase the flash.

  Precondition:
    List and describe any required preconditions. If there are no
    preconditions, enter "None."

  Parameters:
    nvmAdru      - Selects the upper 8bits of the location to program or erase
                   in program flash memory

    nvmAdr       - Selects the location to program or erase in program flash
                   memory. It must be aligned to 512 instruction boundary,
                   LSB 10bits of address must be zero

  Returns:
    Function returns ERROREE (or -1), if it is not successful,
    Function return ZERO, if successful

  Example:

  Remarks:
    None.
*/

int16_t flashPageErase(uint16_t nvmAdru, uint16_t nvmAdr);


// *****************************************************************************
/* Function:
    int16_t flashPageRead(uint16_t nvmAdru, uint16_t nvmAdr, int16_t *pageBufPtr);

  Summary:
    Flash Page Read function

  Description:
    This function provides the interface to read the flash.

  Precondition:
    List and describe any required preconditions. If there are no
    preconditions, enter "None."

  Parameters:
    nvmAdru      - Selects the upper 8bits of the location to program or erase
                   in program flash memory

    nvmAdr       - Selects the location to program or erase in program flash
                   memory. It must be aligned to 512 instruction boundary,
                   LSB 10bits of address must be zero
    pageBufPtr   - Pointer to the data array in which read data will be stored

  Returns:
    Function returns ERROREE (or -1), if it is not successful,
    Function return ZERO, if successful

  Example:

  Remarks:
    None.
*/

int16_t flashPageRead(uint16_t nvmAdru, uint16_t nvmAdr, int16_t *pageBufPtr);


// *****************************************************************************
/* Function:
    int16_t flashWordRead(uint16_t nvmRow, uint16_t nvmOffset, uint16_t nvmAdru, uint16_t nvmAdr, int16_t *wordBufptr);

  Summary:
    Flash Page Read function

  Description:
    This function provides the interface to read the flash.

  Precondition:
    List and describe any required preconditions. If there are no
    preconditions, enter "None."

  Parameters:
    nvmRow       - Selects the row in the the Flash page that will be read

	nvmOffset    - Defines the offset from the start of the row where a pair of words should be read.

    nvmAdru      - Selects the upper 8bits of the location to program or erase
                   in program flash memory

    nvmAdr       - Selects the location to program or erase in program flash
                   memory. It must be aligned to 512 instruction boundary,
                   LSB 10bits of address must be zero
    wordBufPtr   - Pointer to the data array in which read data will be stored

  Returns:
    Function returns ERROREE (or -1), if it is not successful,
    Function return ZERO, if successful

  Example:

  Remarks:
    None.
*/
extern int16_t flashWordRead(uint16_t nvmRow, uint16_t nvmOffset, uint16_t nvmAdru, uint16_t nvmAdr, int16_t *wordBufptr);


// *****************************************************************************
/* Function:
    int16_t flashPageModify(uint16_t row, uint16_t size, int16_t *rowBuf, int16_t *pageBufPtr)

  Summary:
    Flash Page Modify function

  Description:
    This function provides the interface to modify the flash.

  Precondition:
    List and describe any required preconditions. If there are no
    preconditions, enter "None."

  Parameters:
    nvmAdru      - Selects the upper 8bits of the location to program or erase
                   in program flash memory

    nvmAdr       - Selects the location to program or erase in program flash
                   memory. It must be aligned to 512 instruction boundary,
                   LSB 10bits of address must be zero

    rowBuf       - Selects the location to read in program flash memory

    pageBufPtr   - Pointer to the data array in which read data will be stored

  Returns:
    Function returns ERROREE (or -1), if it is not successful,
    Function return ZERO, if successful

  Example:

  Remarks:
    None.
*/

int16_t flashPageModify(uint16_t row, uint16_t size, int16_t *rowBuf, int16_t *pageBufPtr);


// *****************************************************************************
/* Function:
    int16_t flashPageWrite(uint16_t nvmAdru, uint16_t nvmAdr, int16_t *pageBufPtr);

  Summary:
    Flash Page Write function

  Description:
    This function provides the interface to write the flash.

  Precondition:
    List and describe any required preconditions. If there are no
    preconditions, enter "None."

  Parameters:
    nvmAdru      - Selects the upper 8bits of the location to program or erase
                   in program flash memory

    nvmAdr       - Selects the location to program or erase in program flash
                   memory. It must be aligned to 512 instruction boundary,
                   LSB 10bits of address must be zero

    pageBufPtr   - Pointer to the data array in which read data will be stored

  Returns:
    Function returns ERROREE (or -1), if it is not successful,
    Function return ZERO, if successful

  Example:

  Remarks:
    None.
*/

int16_t flashPageWrite(uint16_t nvmAdru, uint16_t nvmAdr, int16_t *pageBufPtr);

// *****************************************************************************
/* Function:
    int16_t flashWordModify(uint16_t row, uint16_t offset, uint16_t nvmAdru, uint16_t nvmAdr, int16_t *ModWords);

  Summary:
    Flash Page Read function

  Description:
    This function provides the interface to read the flash.

  Precondition:
    List and describe any required preconditions. If there are no
    preconditions, enter "None."

  Parameters:
    row       - Selects the row in the the Flash page that will be modified

	offset    - Defines the offset from the start of the row where a pair of words should be modified.

    nvmAdru   - Selects the upper 8bits of the location to program or erase
                   in program flash memory

    nvmAdr    - Selects the location to program or erase in program flash
                   memory. It must be aligned to 512 instruction boundary,
                   LSB 10bits of address must be zero
    ModWords  - Pointer to the word data array, that will modify the already existing Flash contents.

  Returns:
    Function returns ERROREE (or -1), if it is not successful,
    Function return ZERO, if successful

  Example:

  Remarks:
    None.
*/

extern int16_t flashWordModify(uint16_t row, uint16_t offset, uint16_t nvmAdru, uint16_t nvmAdr, int16_t *ModWords);
// *****************************************************************************

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif


#endif /* _RTSPAPI_H */

/*******************************************************************************
 End of File
*/

