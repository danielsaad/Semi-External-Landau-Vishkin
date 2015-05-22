#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <stdint.h>
#include <cinttypes>
#include <cstdio>
#include <climits>
#include <iostream>


/**
    Basic type definition
**/

#define ARCH_32

class serializable{
public:
    virtual void serialize(std::ostream& output) = 0;
    virtual ~serializable();
};


#ifdef ARCH_32
    #define WORD_SIZE 32
    #define WORD_MOD 0X1F
    #define WORD_SHIFT 5

    typedef uint32_t word;
    typedef int32_t integer;

    #define integer_MAX 0x7fffffff
    #define PRINT_WORD PRIu32
    #define MAX_WORD 0xffffffff
#else
    #define WORD_SIZE 64
    #define WORD_MOD 63
    #define WORD_SHIFT 6
    typedef uint64_t word;
    typedef int64_t integer;
    #define integer_MAX INT64_MAX
    #define PRINT_WORD PRIu64
    #define MAX_WORD 0xffffffffffffffff
#endif



typedef uint8_t byte;

#endif // TYPES_H_INCLUDED
