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

void Stack_Init(Stack_t *pObj, void *pBuf, size_t bufSize, size_t dataSize);

bool Stack_IsEmpty(Stack_t *pObj);

bool Stack_IsFull(Stack_t *pObj);

Stack_Error_e Stack_Push(Stack_t *pObj, void *pDataIn);

Stack_Error_e Stack_Pop(Stack_t *pObj, void *pDataOut);

Stack_Error_e Stack_Peek(Stack_t *pObj, void *pDataOut);

#endif /* STACK_H_INCLUDED */