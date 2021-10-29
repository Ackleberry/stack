/*******************************************************************************
 * @file  stack_t.h
 *
 * @brief Stack public function declarations
 *
 * @author Brooks Anderson <bilbrobaggins@gmail.com>
 ******************************************************************************/
#ifndef STACK_T_H_INCLUDED
#define STACK_T_H_INCLUDED

/*============================================================================*
 *                              I N C L U D E S                               *
 *============================================================================*/
#include <stddef.h>
#include <stdint.h>

/*============================================================================*
 *                                D E F I N E S                               *
 *============================================================================*/

/*============================================================================*
 *                           E N U M E R A T I O N S                          *
 *============================================================================*/

/**
 * @brief Error flag
**/
typedef enum _Stack_Error_e
{
    Stack_Error_None = 0,
    Stack_Error      = 1,
} Stack_Error_e;

/*============================================================================*
 *                             S T R U C T U R E S                            *
 *============================================================================*/

/**
 * @brief  Stack Object
 *
 * @note   This object should never be directly manipulated by the caller.
**/
typedef struct _Stack_t
{
    size_t   top;      /*!< Buffer Index to the top of the stack */
    uint8_t *pBuf;     /*!< Pointer to the stack buffer */
    size_t   bufSize;  /*!< Size of the stack buffer */
    size_t   dataSize; /*!< Size of the data type to be stored in the stack */
} Stack_t;

#endif /* STACK_T_H_INCLUDED */