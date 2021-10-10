/*******************************************************************************
 * @file  stack.c
 *
 * @brief Stack implementation
 *
 * @author Brooks Anderson <bilbrobaggins@gmail.com>
 ******************************************************************************/

/*============================================================================*
 *                              I N C L U D E S                               *
 *============================================================================*/
#include "stack.h"

/*============================================================================*
 *                      P U B L I C    F U N C T I O N S                      *
 *============================================================================*/

void Stack_Init(Stack_t *pObj, void *pBuf, size_t bufSize, size_t dataSize)
{
    pObj->top = SIZE_MAX;
    pObj->pBuf = pBuf;
    pObj->bufSize = bufSize;
    pObj->dataSize = dataSize;
}

bool Stack_IsEmpty(Stack_t *pObj)
{
    return pObj->top == SIZE_MAX;
}

bool Stack_IsFull(Stack_t *pObj)
{
    return pObj->top == (pObj->bufSize - 1);
}

Stack_Error_e Stack_Push(Stack_t *pObj, void *pDataIn)
{
    Stack_Error_e err = Stack_Error_None;
    uint8_t *pData = (uint8_t *)pDataIn;

    /* Push the data on to the stack one byte at a time */
    size_t idx = 0;
    while (idx < pObj->dataSize)
    {
        if (Stack_IsFull(pObj))
        {
            err = Stack_Error;
            break;
        }

        pObj->top++;
        pObj->pBuf[pObj->top] = pData[idx];
        idx++;
    }

    return err;
}

Stack_Error_e Stack_Pop(Stack_t *pObj, void *pDataOut)
{
    Stack_Error_e err = Stack_Error_None;
    uint8_t *pData = (uint8_t *)pDataOut;

    /* Pop the data off the stack one byte at a time */
    size_t idx = pObj->dataSize;
    while (idx > 0)
    {
        if (Stack_IsEmpty(pObj))
        {
            err = Stack_Error;
            break;
        }

        idx--;
        pData[idx] = pObj->pBuf[pObj->top];
        pObj->top--;
    }

    return err;
}

Stack_Error_e Stack_Peek(Stack_t *pObj, void *pDataOut)
{
    Stack_Error_e err = Stack_Error_None;
    size_t top = pObj->top;

    err = Stack_Pop(pObj, pDataOut);
    pObj->top = top;

    return err;
}