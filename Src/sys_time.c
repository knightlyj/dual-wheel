#include "sys_time.h"
#include "stm32f4xx_ll_iwdg.h"

uint64_t g_sysTotalTime = 0; //系统时间,单位毫秒,不考虑溢出

void DelayMs(uint16_t ms)
{
    uint64_t targetTime;
    targetTime = g_sysTotalTime + ms;
    while(g_sysTotalTime < targetTime)
    {
        LL_IWDG_ReloadCounter(IWDG); //喂狗
    }
}


void DelayUs(uint16_t us)
{
    int i;
    for(i = 0; i < us; i++)
    {
        __NOP();__NOP();__NOP();__NOP();
    }
}

