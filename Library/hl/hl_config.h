/**
  ******************************************************************************
  * @file    HL_Config.h
  * @author  LYJ
  * @version V3.5.0
  * @brief   HL库的配置文件,这个库依赖CLIB库
  ******************************************************************************
  */


#pragma once

//--------CPU类型表-----------
#define HL_STM32F10X_CL     0
#define HL_STM32F407X       407

//CPU类型
#define HL_MCU_TYPE HL_STM32F407X


//flash page size
#if HL_MCU_TYPE == HL_STM32F10X_CL
#define HL_IAP_PAGE_SIZE  (1024 * 2)  //2K
#endif


//定时器时钟频率
#define TIMER_CLOCK_FREQ        (84000000ul)



