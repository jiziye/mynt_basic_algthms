//
// Created by cg on 9/16/19.
//

#ifndef MYNT_BASIC_ALGTHMS_COMMON_H
#define MYNT_BASIC_ALGTHMS_COMMON_H

namespace mynt {

#define DELETE_NEW_OBJ(obj) if(nullptr!=obj){delete obj;obj=nullptr;}

#define endll std::endl << std::endl // double end line definition

#ifndef _MSC_VER
#include <stdint.h>
#else
    typedef __int8            int8_t;
    typedef __int16           int16_t;
    typedef __int32           int32_t;
    typedef __int64           int64_t;
    typedef unsigned __int8   uint8_t;
    typedef unsigned __int16  uint16_t;
    typedef unsigned __int32  uint32_t;
    typedef unsigned __int64  uint64_t;
#endif

    typedef double FLOAT; // double precision, float for single precision
}

#endif //MYNT_BASIC_ALGTHMS_COMMON_H
