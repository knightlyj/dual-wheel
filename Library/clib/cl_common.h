/**
  ******************************************************************************
  * @file    CL_Common.h
  * @author  LYJ
  * @brief   CLIB��Ŀ���Ǳ�д��ƽ̨��C��,Ϊ��֧��ԭ�Ӳ���,��Ҫ����CPU������
  ******************************************************************************
  */


#pragma once

#include "stdint.h"
#include "string.h"
#include "stdio.h"

enum
{
    CL_CORTEX_M3 = 3,
    CL_CORTEX_M4 = 4,
};

#define CL_CPU_TYPE CL_CORTEX_M4

typedef enum
{
    CL_FALSE = 0,
    CL_TRUE = 1,
} CL_BOOL;

typedef enum
{
    CL_SUCCESS = 0,

    CL_FAILED = -1,
    CL_INVALID_PARAM = -2,
    
} CL_RESULT;


#define CL_INLINE           __inline
#define CL_STATIC_INLINE    static CL_INLINE
#define CL_NULL             (0)

#ifdef _DEBUG
#include "assert.h"
#else
#define assert(expression)      
#endif

#define CL_ARRAY_LENGTH(array)      (sizeof(array) / sizeof(array[0]))

#define Log     printf


