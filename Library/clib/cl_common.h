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
};

#define CL_CPU_TYPE CL_CORTEX_M3


#define CL_NOTHING


#define CL_BOOL             uint8_t
#define CL_TRUE             (1)
#define CL_FALSE            (0)


#define CL_RESULT           int32_t
#define CL_SUCCESS          (0)
#define CL_FAILED           (-1)
#define CL_INVALID_PARAM    (-2)

#define CL_INLINE           __inline
#define CL_STATIC_INLINE    static CL_INLINE
#define CL_NULL             (0)

#ifdef _DEBUG
#include "assert.h"
#else
#define assert(expression)      CL_NOTHING
#endif

#define CL_ARRAY_LENGTH(array)      (sizeof(array) / sizeof(array[0]))

#define Log     printf


