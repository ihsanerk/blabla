/*******************************************************************************
  Run Time Self Programming API

  Company:
    Microchip Technology Inc.

  File Name:
    rtspapi.s

  Summary:
    This file has flash routines

  Description:
    This file consists of Flash Erase, Flash Read and Flash Page modify
    and Flash Programming routines that are called by the main function which are
    used to erase a page, read a page, modify a page and program a row of flash memory
    respectively.
*******************************************************************************/

/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/

/*****************************************************************************
 *****************************************************************************
 Section: Included Files
 *****************************************************************************
 *****************************************************************************/

.include "xc.inc"

/*****************************************************************************
 *****************************************************************************
 Section: File Scope or Global Constants
 *****************************************************************************
 *****************************************************************************/

.equ    FLASH_PAGE_ERASE_CODE,  0x4003
.equ    FLASH_ROW_PROG_CODE,  0x4002
.equ    FLASH_WORD_PROG_CODE, 0x4001

 .global _flashPageRead
 .global _flashPageErase
 .global _flashPageWrite
 .global _flashPageModify
 .global _flashWordModify
 .global _flashWordRead

 .section .text

/******************************************************************************
  Flash Page Read
  Read EIGHT rows (PAGE) of memory, upper PM byte is discarded
*******************************************************************************/
_flashPageRead:
        push    TBLPAG
        mov     w0, TBLPAG
        mov     #1024, w3

readNext:
  tblrdl  [w1],[w2++]
  tblrdh [w1++],w6  ; Discard PM upper byte
        dec     w3, w3
        bra     nz, readNext

  clr  w0
   pop     TBLPAG
        return



/******************************************************************************
  Flash Page Modify
  Read EIGHT rows (PAGE) of memory, upper PM byte is discarded
*******************************************************************************/
_flashPageModify:
  sl   w0,#7,w0
  add  w0,w3,w3

modifyNext:
  mov    [w2++],[w3++] ; Discard PM upper byte
        dec     w1, w1
        bra     nz, modifyNext

  return

/******************************************************************************
  Flash Page Erase
  Erase EIGHT rows (PAGE) of memory
*******************************************************************************/
_flashPageErase:
    push    TBLPAG

    mov     w0, TBLPAG  ; Init Pointer to page to be erased
    mov     w0,NVMADRU ; Init Pointer to row to be erased
    mov  w1,NVMADR
    tblwtl  w1, [w1]

    mov    #FLASH_PAGE_ERASE_CODE,w7
    mov     w7, NVMCON
    bset  w7,#WR;NVMCON,#15
    disi  #5    ; Block all interrupt with priority <7 for next 5 instructions
    mov   #0x55, W0
    mov   W0, NVMKEY
    mov   #0xAA, W0
    mov   W0, NVMKEY
    mov   w7,NVMCON  ; Start Program Operation
    nop
    nop


erase_wait:
  btsc    NVMCON, #WR
  bra     erase_wait

  clr  w0

  pop     TBLPAG
  return

  nop

/******************************************************************************
  Flash Page Program
  Program EIGHT rows (PAGE) of memory,
  Each row contains 192 bytes of data (64 instructions, with upper PM byte == NOP)
*******************************************************************************/


_flashPageWrite:
        push    TBLPAG
  MOV  W0, W9              ; Add loc to be written
  MOV  w1, w8
  mov  #0xFA, w0
  mov  w0, TBLPAG          ;TBLPAG has to point to the SRAM latch section
  mov  #0, w1

  mov  #0,w6
  mov  #7,w5   ; w5=row counter
row_loop:
  mov  #64,w3
  mov  #0, w1   ;clear w1 - address is relative to the row start address
pinst_loop:

  TBLWTL.b [w2++], [w1]
  TBLWTH.b w6, [w1++]  ; write 0 to high byte to be decoded as nop
  TBLWTL.b    [w2++], [w1++]

  TBLWTL.b [w2++], [w1]
  TBLWTH.b w6, [w1++]  ; write 0 to high byte to be decoded as nop
  TBLWTL.b    [w2++], [w1++]

  dec2  w1,w1
  dec2  w1,w1

;        dec     w3, w3
;        bra     NZ, pinst_loop

  MOV  w9, NVMADRU        ;point to the row to be written to
  MOV  w8, NVMADR

;  ; Setup NVCON for row program
  mov    #FLASH_WORD_PROG_CODE,w7
  mov     w7, NVMCON
  bset    w7,#15
  disi  #5    ; Block all interrupt with priority <7 for next 5 instructions
  mov     #0x55, W0
  mov     W0, NVMKEY
  mov     #0xAA, W0
  mov     W0, NVMKEY

  mov     w7,NVMCON  ; Start Program Operation
  nop
  nop
  add  w8,#4,w8
prog_wait:
  btsc    NVMCON, #WR
  bra     prog_wait
  dec     w3, w3
  bra     NZ, pinst_loop



;  mov  #256,w1   ; load with row size
;  mov  w8,w0   ; load previous row address
;  add  w1,w0,w0  ; compute new row address
;  mov  w0,w8   ; load new row address in w8

  dec     w5, w5
  bra     nz, row_loop ; test if all rows are written

  clr  w0
  pop     TBLPAG
  return

_flashWordModify:

  push    TBLPAG
  sl   w0,#7,w0
  add  w0,w3,w3
  mov  #0xFA, w0
  mov  w0, TBLPAG
  add  w1,w3,w3
  MOV  W2, W9; Add loc to be written
  MOV  w3, w8

  mov #0, w3
  mov #0, w6

; Copy the bytes to the latches.

  TBLWTL.b [w4++], [w3]
  TBLWTH.b w6, [w3++]  ; write 0 to high byte to be decoded as nop
  TBLWTL.b    [w4++], [w3++]

  TBLWTL.b [w4++], [w3]
  TBLWTH.b w6, [w3++]  ; write 0 to high byte to be decoded as nop
  TBLWTL.b    [w4++], [w3++]

  MOV w9, NVMADRU
  MOV w8, NVMADR

 ; Setup NVCON for word program
  mov    #FLASH_WORD_PROG_CODE,w7
  MOV W7, NVMCON
  bset w7,#15
  disi #5

  MOV #0x55, W0
  MOV W0, NVMKEY
  MOV #0xAA, W0
  MOV W0, NVMKEY

mov     w7,NVMCON		; Start Program Operation
  ;bset w7,#WR;NVMCON, #WR
  nop
  nop

  wait:
   btsc NVMCON, #WR
   bra wait

   clr W0
   pop TBLPAG
   return

_flashWordRead:

  push  TBLPAG
  sl   w0,#7,w0
  add     w0,w3,w3
  add     w1,w3,w3
  mov     w2, TBLPAG
  mov  #2, w5

readloop:
  tblrdl.b  [w3], [w4++]
  tblrdh.b  [w3++], [w4++]
  tblrdl.b  [w3++], [w4]
  dec  w5, w5
  bra  nz, readloop

  clr  w0
  pop  TBLPAG
  return

.end





