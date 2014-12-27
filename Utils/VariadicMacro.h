#pragma once

// Usage:
// 1. Declare new variadic macro
// #define VARIADIC_MACRO(...) MACRO_DISPATCHER(VARIADIC_MACRO, __VA_ARGS__)(__VA_ARGS__)
// 2. Declare VARIADIC_MACRO0, VARIADIC_MACRO1, VARIADIC_MACRO2, ... , VARIADIC_MACRO[N] macros where N is a number of input parameters


// Due to MSVC compiler issue expand of __VA_ARGS__ functions that accepts it should be 
// wrapped with fake function. Otherwise the whole param list will go to first parameter of nested macro
// MSVC compiler is GUANO!
#define VA_NUM_ARGS(...) VA_NUM_ARGS_(VA_NUM_PREFIX_ ## __VA_ARGS__ ## _VA_NUM_POSTFIX, VA_SEQ)
#define VA_NUM_PREFIX__VA_NUM_POSTFIX ,,,,,,,,,,,,,,,0
#define VA_NUM_ARGS_(...) EXPAND(VA_NUM_ARGS__(__VA_ARGS__))
#define VA_NUM_ARGS__(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, N, ...) N
#define VA_SEQ 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#define EXPAND(x) x

#define VARIADIC_EXPAND(CONSTRUCTOR) \
    CONSTRUCTOR() \
    CONSTRUCTOR(T0) \
    CONSTRUCTOR(T0, T1) \
    CONSTRUCTOR(T0, T1, T2) \
    CONSTRUCTOR(T0, T1, T2, T3) \
    CONSTRUCTOR(T0, T1, T2, T3, T4) \
    CONSTRUCTOR(T0, T1, T2, T3, T4, T5)

#define MACRO_DISPATCHER(func, ...) \
            MACRO_DISPATCHER_(func, VA_NUM_ARGS(__VA_ARGS__))

#define MACRO_DISPATCHER_(func, nargs) \
        MACRO_DISPATCHER__(func, nargs)

#define MACRO_DISPATCHER__(func, nargs) \
        func ## nargs
