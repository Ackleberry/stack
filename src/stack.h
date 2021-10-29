/*******************************************************************************
 * @file  stack.h
 *
 * @brief Stack public function declarations
 *
 * @author Brooks Anderson <bilbrobaggins@gmail.com>
 ******************************************************************************/

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

/*============================================================================*
 *                              I N C L U D E S                               *
 *============================================================================*/
#include <stddef.h>
#include <stdbool.h>

#include "stack_t.h"

/*============================================================================*
 *                 F U N C T I O N    D E C L A R A T I O N S                 *
 *============================================================================*/

/*******************************************************************************
 * @brief  Initializes the stack object
 *
 * @details  The caller is responsible for allocating the stack object, and
 *           stack buffer.
 *
 * @param pObj      Pointer to the stack object
 * @param pBuf      Pointer to the stack buffer
 * @param bufSize   Size of the buffer, must be an integer multiple of datasize
 * @param dataSize  Size of the data type that the stack is handling
 ******************************************************************************/
void Stack_Init(Stack_t *pObj, void *pBuf, size_t bufSize, size_t dataSize);

/*******************************************************************************
 * @brief  Check if the stack is empty
 *
 * @details  Stack top is considered empty when set to largest `size_t` value,
 *           SIZE_MAX. The first added element "rolls" the top over from
 *           SIZE_MAX to 0.
 *
 * @param pObj  Pointer to the stack object
 *
 * @returns true if empty
 ******************************************************************************/
bool Stack_IsEmpty(Stack_t *pObj);

/*******************************************************************************
 * @brief Check if the stack is full
 *
 * @details  Stack top is considered full when set to one less than the buffer
 *           size.
 *
 * @param pObj  Pointer to the stack object
 *
 * @returns true if full
 ******************************************************************************/
bool Stack_IsFull(Stack_t *pObj);

/*******************************************************************************
 * @brief  Pushes some data type onto the stack
 *
 * @param pObj     Pointer to the stack object
 * @param pDataIn  Pointer to the data that will be pushed onto the stack
 *
 * @returns Stack error flag
 ******************************************************************************/
Stack_Error_e Stack_Push(Stack_t *pObj, void *pDataIn);

/*******************************************************************************
 * @brief  Pops some data type off the stack
 *
 * @param pObj      Pointer to the stack object
 * @param pDataOut  Pointer to the data that will be popped off the stack
 *
 * @returns Stack error flag
 ******************************************************************************/
Stack_Error_e Stack_Pop(Stack_t *pObj, void *pDataOut);

/*******************************************************************************
 * @brief  Peek at the data on the top of the stack
 *
 * @param  pObj      Pointer to the stack object
 * @param  pDataOut  Pointer to the peeked data
 *
 * @returns Stack error flag
 ******************************************************************************/
Stack_Error_e Stack_Peek(Stack_t *pObj, void *pDataOut);

#endif /* STACK_H_INCLUDED */