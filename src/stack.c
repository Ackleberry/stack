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

/*******************************************************************************
 * @brief  Initializes the stack object
 *
 * @details  The caller is responsible for allocating the stack object, and
 *           stack buffer.
 *
 * @param pObj      Pointer to the stack object
 * @param pBuf      Pointer to the stack buffer
 * @param bufSize   Size of the buffer
 * @param dataSize  Size of the data type that the stack is handling
 *
 * @return none
 ******************************************************************************/
void Stack_Init(Stack_t *pObj, void *pBuf, size_t bufSize, size_t dataSize)
{
    pObj->top = SIZE_MAX;
    pObj->pBuf = pBuf;
    pObj->bufSize = bufSize;
    pObj->dataSize = dataSize;
}

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
bool Stack_IsEmpty(Stack_t *pObj)
{
    return pObj->top == SIZE_MAX;
}

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
bool Stack_IsFull(Stack_t *pObj)
{
    return pObj->top == (pObj->bufSize - 1);
}

/*******************************************************************************
 * @brief  Pushes some data type onto the stack
 *
 * @param pObj     Pointer to the stack object
 * @param pDataIn  Pointer to the data that will be pushed onto the stack
 *
 * @returns Stack error flag
 ******************************************************************************/
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

/*******************************************************************************
 * @brief  Pops some data type off the stack
 *
 * @param pObj      Pointer to the stack object
 * @param pDataOut  Pointer to the data that will be popped off the stack
 *
 * @returns Stack error flag
 ******************************************************************************/
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

/*******************************************************************************
 * @brief  Peek at the data on the top of the stack
 *
 * @param  pObj      Pointer to the stack object
 * @param  pDataOut  Pointer to the peeked data
 *
 * @returns Stack error flag
 ******************************************************************************/
Stack_Error_e Stack_Peek(Stack_t *pObj, void *pDataOut)
{
    Stack_Error_e err = Stack_Error_None;
    size_t top = pObj->top;

    err = Stack_Pop(pObj, pDataOut);
    pObj->top = top;

    return err;
}