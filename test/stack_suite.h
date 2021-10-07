#ifndef STACK_SUITE_INCLUDED
#define STACK_SUITE_INCLUDED

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "greatest.h"
#include "stack_test_helper.h"
#include "stack.h"

/* Declare a local suite. */
SUITE(Stack_Suite);

TEST Stack_can_report_empty(void)
{
    /*****************    Arrange    *****************/
    Stack_t s;
    uint8_t buf[sizeof(uint8_t)];

    Stack_Init(&s, buf, sizeof(buf), sizeof(uint8_t));

    /*****************     Act       *****************/
    bool status = Stack_IsEmpty(&s);

    /*****************    Assert     *****************/
    ASSERT_EQ(true, status);
    ASSERT_EQ(false, Stack_IsFull(&s));

    PASS();
}

TEST Stack_can_report_not_empty(void)
{
    /*****************    Arrange    *****************/
    Stack_t s;
    uint8_t buf[2 * sizeof(uint8_t)];
    uint8_t dataIn = 10;

    Stack_Init(&s, buf, sizeof(buf), sizeof(uint8_t));
    Stack_Push(&s, &dataIn);

    /*****************     Act       *****************/
    bool status = Stack_IsEmpty(&s);

    /*****************    Assert     *****************/
    ASSERT_EQ(false, status);

    PASS();
}

TEST Stack_can_report_full(void)
{
    /*****************    Arrange    *****************/
    Stack_t s;
    uint8_t buf[sizeof(uint8_t)];
    uint8_t dataIn = 10;
    uint8_t err = (uint8_t)Stack_Error_None;

    Stack_Init(&s, buf, sizeof(buf), sizeof(uint8_t));

    /*****************     Act       *****************/
    err |= Stack_Push(&s, &dataIn);

    /*****************    Assert     *****************/
    ASSERT_EQ(Stack_Error_None, (Stack_Error_e)err);
    ASSERT_EQ(true, Stack_IsFull(&s));

    PASS();
}

TEST Stack_can_report_not_full(void)
{
    /*****************    Arrange    *****************/
    Stack_t s;
    uint8_t buf[2 * sizeof(uint8_t)];
    uint8_t dataIn = 10;
    uint8_t err = (uint8_t)Stack_Error_None;

    Stack_Init(&s, buf, sizeof(buf), sizeof(uint8_t));

    /*****************     Act       *****************/
    err |= Stack_Push(&s, &dataIn);

    /*****************    Assert     *****************/
    ASSERT_EQ(Stack_Error_None, (Stack_Error_e)err);
    ASSERT_EQ(false, Stack_IsFull(&s));

    PASS();
}


TEST Stack_can_underflow(void)
{
    /*****************    Arrange    *****************/
    Stack_t s;
    uint8_t buf[5 * sizeof(uint8_t)];
    uint8_t poppedData;
    uint8_t err = (uint8_t)Stack_Error_None;

    Stack_Init(&s, buf, sizeof(buf), sizeof(uint8_t));

    /*****************     Act       *****************/
    err |= Stack_Pop(&s, &poppedData);

    /*****************    Assert     *****************/
    ASSERT_EQ(Stack_Error, (Stack_Error_e)err);

    PASS();
}

TEST Stack_can_overflow(void)
{
    /*****************    Arrange    *****************/
    Stack_t s;
    uint8_t buf[5 * sizeof(uint8_t)];
    uint64_t dataIn[] = { 10, 82, 99, 201, 254 };
    uint8_t overflowData = 1;
    uint8_t err = (uint8_t)Stack_Error_None;

    Stack_Init(&s, buf, sizeof(buf), sizeof(uint8_t));

    /* Fill the stack up */
    for (uint8_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        Stack_Push(&s, &dataIn);
    }

    /*****************     Act       *****************/
    err |= Stack_Push(&s, &overflowData);

    /*****************    Assert     *****************/
    ASSERT_EQ(Stack_Error, (Stack_Error_e)err);

    PASS();
}

TEST Stack_can_pop_1_byte_data_types(void)
{
    /*****************    Arrange    *****************/
    Stack_t s;
    uint8_t buf[sizeof(uint8_t)];
    uint8_t dataIn = 10;
    uint8_t dataOut;
    uint8_t err = (uint8_t)Stack_Error_None;

    Stack_Init(&s, buf, sizeof(buf), sizeof(uint8_t));
    Stack_Push(&s, &dataIn);

    /*****************     Act       *****************/
    err |= Stack_Pop(&s, &dataOut);

    /*****************    Assert     *****************/
    ASSERT_EQ(Stack_Error_None, (Stack_Error_e)err);
    ASSERT_EQ(dataIn, dataOut);
    ASSERT_EQ(true, Stack_IsEmpty(&s));

    PASS();
}

TEST Stack_can_pop_2_byte_data_types(void)
{
    /*****************    Arrange    *****************/
    Stack_t s;
    uint8_t buf[sizeof(uint16_t)];
    uint16_t dataIn = 5;
    uint16_t dataOut = 0;
    uint8_t err = (uint8_t)Stack_Error_None;

    Stack_Init(&s, buf, sizeof(buf), sizeof(uint16_t));
    Stack_Push(&s, &dataIn);

    /*****************     Act       *****************/
    err |= Stack_Pop(&s, &dataOut);

    /*****************    Assert     *****************/
    ASSERT_EQ(Stack_Error_None, (Stack_Error_e)err);
    ASSERT_EQ(dataIn, dataOut);
    ASSERT_EQ(true, Stack_IsEmpty(&s));

    PASS();
}

TEST Stack_can_pop_8_byte_data_types(void)
{
    /*****************    Arrange    *****************/
    Stack_t s;
    uint8_t buf[sizeof(uint64_t)];
    uint64_t dataIn = 5;
    uint64_t dataOut = 0;
    uint8_t err = (uint8_t)Stack_Error_None;

    Stack_Init(&s, buf, sizeof(buf), sizeof(uint64_t));
    Stack_Push(&s, &dataIn);

    /*****************     Act       *****************/
    err |= Stack_Pop(&s, &dataOut);

    /*****************    Assert     *****************/
    ASSERT_EQ(Stack_Error_None, (Stack_Error_e)err);
    ASSERT_EQ(dataIn, dataOut);
    ASSERT_EQ(true, Stack_IsEmpty(&s));

    PASS();
}

TEST Stack_can_pop_a_struct_data_type()
{
    /*****************    Arrange    *****************/
    typedef struct _Stack_Struct_t
    {
        uint8_t a;
        uint16_t b;
        uint32_t c;
        uint8_t d;
        uint32_t e;
    } Stack_Struct_t;

    Stack_t s;
    uint8_t buf[sizeof(Stack_Struct_t)];
    Stack_Struct_t dataIn = { .a = 5, .b = 54, .c = 1000, .d = 254, .e = 9999 };
    Stack_Struct_t dataOut;
    uint8_t err = (uint8_t)Stack_Error_None;

    Stack_Init(&s, buf, sizeof(buf), sizeof(Stack_Struct_t));
    Stack_Push(&s, &dataIn);

    /*****************     Act       *****************/
    err |= Stack_Pop(&s, &dataOut);

    /*****************    Assert     *****************/
    ASSERT_EQ(Stack_Error_None, (Stack_Error_e)err);
    ASSERT_MEM_EQ(&dataIn, &dataOut, sizeof(Stack_Struct_t));
    ASSERT_EQ(true, Stack_IsEmpty(&s));


    PASS();
}

TEST Stack_can_peek_at_next_element_to_be_popped(void)
{
    /*****************    Arrange    *****************/
    Stack_t s;
    uint8_t buf[5 * sizeof(uint64_t)];
    uint64_t dataIn[] = { 10, 82 };
    uint64_t peekData;
    uint64_t poppedData;
    uint8_t err = (uint8_t)Stack_Error_None;

    Stack_Init(&s, buf, sizeof(buf), sizeof(uint64_t));
    Stack_Push(&s, &dataIn[0]);
    Stack_Push(&s, &dataIn[1]);

    /*****************     Act       *****************/
    err |= Stack_Peek(&s, &peekData);

    /*****************    Assert     *****************/
    Stack_Pop(&s, &poppedData);
    ASSERT_EQ(Stack_Error_None, (Stack_Error_e)err);
    ASSERT_EQ(dataIn[1], peekData);
    ASSERT_EQ(peekData, poppedData);

    PASS();
}

TEST Stack_can_fill_and_empty_a_large_buffer_with_1_byte_data_types(void)
{
    /*****************    Arrange    *****************/
    Stack_t s;
    int8_t buf[1000];
    int8_t dataIn[1000] =
    {
        [  1] = INT8_MIN,
        [101] = -1,
        [501] = 1,
        [999] = INT8_MAX,
    };
    int8_t dataOut[1000];
    uint8_t err = (uint8_t)Stack_Error_None;

    Stack_Init(&s, buf, sizeof(buf), sizeof(int8_t));

    /*****************     Act       *****************/

    /* Fill the stack up */
    for (uint16_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= Stack_Push(&s, &dataIn[i]);
    }

    /* Empty the stack */
    for (uint16_t i = ELEMENTS_IN(dataOut); i > 0; i--)
    {
        err |= Stack_Pop(&s, &dataOut[i - 1]);
    }

    /*****************    Assert     *****************/
    ASSERT_EQ(Stack_Error_None, (Stack_Error_e)err);
    ASSERT_MEM_EQ(dataIn, dataOut, ELEMENTS_IN(dataIn));
    ASSERT_EQ(true, Stack_IsEmpty(&s));

    PASS();
}

TEST Stack_can_fill_and_empty_a_large_buffer_with_8_byte_data_types(void)
{
    /*****************    Arrange    *****************/
    Stack_t s;
    int64_t buf[1000];
    int64_t dataIn[1000] =
    {
        [  1] = INT64_MIN,
        [101] = -1,
        [501] = 1,
        [999] = INT64_MAX,
    };
    int64_t dataOut[1000];
    uint8_t err = (uint8_t)Stack_Error_None;

    Stack_Init(&s, buf, sizeof(buf), sizeof(int64_t));

    /*****************     Act       *****************/

    /* Fill the stack up */
    for (uint16_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= Stack_Push(&s, &dataIn[i]);
    }

    /* Empty the stack */
    for (uint16_t i = ELEMENTS_IN(dataOut); i > 0; i--)
    {
        err |= Stack_Pop(&s, &dataOut[i - 1]);
    }

    /*****************    Assert     *****************/
    ASSERT_EQ(Stack_Error_None, (Stack_Error_e)err);
    ASSERT_MEM_EQ(dataIn, dataOut, ELEMENTS_IN(dataIn));
    ASSERT_EQ(true, Stack_IsEmpty(&s));

    PASS();
}

TEST Stack_can_fill_and_empty_a_large_buffer_with_struct_data_types(void)
{
    typedef struct _Stack_Struct_t
    {
        uint8_t a;
        int16_t b;
        uint32_t c;
        int8_t d;
        uint32_t e;
    } Stack_Struct_t;

    /*****************    Arrange    *****************/
    Stack_t s;
    Stack_Struct_t buf[1000];
    Stack_Struct_t dataIn[1000] =
    {
        [  1] = { .a = UINT8_MAX, .b = INT16_MAX, .c = -1, .d = INT8_MIN, .e = 1  },
        [101] = { .a = INT8_MAX,  .b = INT16_MIN, .c = 0,  .d = INT8_MAX, .e = -1 },
        [501] = { .a = UINT8_MAX, .b = INT16_MAX, .c = -1, .d = INT8_MIN, .e = 1  },
        [999] = { .a = INT8_MAX,  .b = INT16_MIN, .c = 0,  .d = INT8_MAX, .e = -1 },
    };
    Stack_Struct_t dataOut[1000];
    uint8_t err = (uint8_t)Stack_Error_None;

    Stack_Init(&s, buf, sizeof(buf), sizeof(Stack_Struct_t));

    /*****************     Act       *****************/

    /* Fill the stack up */
    for (uint16_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= Stack_Push(&s, &dataIn[i]);
    }

    /* Empty the stack */
    for (uint16_t i = ELEMENTS_IN(dataOut); i > 0; i--)
    {
        err |= Stack_Pop(&s, &dataOut[i - 1]);
    }

    /*****************    Assert     *****************/
    ASSERT_EQ(Stack_Error_None, (Stack_Error_e)err);
    ASSERT_MEM_EQ(dataIn, dataOut, ELEMENTS_IN(dataIn));
    ASSERT_EQ(true, Stack_IsEmpty(&s));

    PASS();
}

SUITE(Stack_Suite)
{
    /* Unit Tests */
    RUN_TEST(Stack_can_report_empty);
    RUN_TEST(Stack_can_report_not_empty);
    RUN_TEST(Stack_can_report_full);
    RUN_TEST(Stack_can_report_not_full);
    RUN_TEST(Stack_can_underflow);
    RUN_TEST(Stack_can_overflow);
    RUN_TEST(Stack_can_pop_1_byte_data_types);
    RUN_TEST(Stack_can_pop_2_byte_data_types);
    RUN_TEST(Stack_can_pop_8_byte_data_types);
    RUN_TEST(Stack_can_pop_a_struct_data_type);
    RUN_TEST(Stack_can_peek_at_next_element_to_be_popped);

    /* Integration Tests */
    RUN_TEST(Stack_can_fill_and_empty_a_large_buffer_with_1_byte_data_types);
    RUN_TEST(Stack_can_fill_and_empty_a_large_buffer_with_8_byte_data_types);
    RUN_TEST(Stack_can_fill_and_empty_a_large_buffer_with_struct_data_types);

}

#endif /* STACK_SUITE_INCLUDED */