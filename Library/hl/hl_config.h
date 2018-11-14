/**
  ******************************************************************************
  * @file    HL_Config.h
  * @author  LYJ
  * @version V3.5.0
  * @brief   HL��������ļ�,���������CLIB��
  ******************************************************************************
  */


#pragma once

//--------CPU���ͱ�-----------
#define HL_STM32F10X_CL     0
#define HL_STM32F407X       407

//CPU����
#define HL_MCU_TYPE HL_STM32F407X


//flash page size
#if HL_MCU_TYPE == HL_STM32F10X_CL
#define HL_IAP_PAGE_SIZE  (1024 * 2)  //2K
#endif


//��ʱ��ʱ��Ƶ��
#define TIMER_CLOCK_FREQ        (84000000ul)



