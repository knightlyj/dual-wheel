#pragma once
#include "cl_common.h"

extern uint64_t g_sysTotalTime; //系统时间,单位毫秒,不考虑溢出

//更新系统时间,传入调用间隔
CL_STATIC_INLINE void UpdateSysTime(uint16_t interval)
{
    g_sysTotalTime += interval;
}


//从preTime到现在经过的时间
CL_STATIC_INLINE uint64_t TimeElapsed(uint64_t preTime)
{
    return g_sysTotalTime - preTime;
}

//*pTime设置为当前时间
CL_STATIC_INLINE void SetToCurTime(uint64_t* pTime)
{
    *pTime = g_sysTotalTime;
}


extern void DelayMs(uint16_t ms);
extern void DelayUs(uint16_t us);

