#pragma once

#include "cl_common.h"
#include "hl_config.h"

//��ʱ��id
typedef enum
{
    HL_Timer2 = 2,
    HL_Timer3 = 3,
    HL_Timer4 = 4,
    HL_Timer5 = 5,
} HL_TimerId_t;

/**
  * ��ʱ��������ʽ
  * HL_TimerAutoLoad: �Զ�װ��
  * HL_TimerOneShot:  һ����
  */
typedef enum
{
    HL_TimerAutoLoad = 0,
    HL_TimerOneShot = 1,   //��ʱû��ʵ��
} HL_TimerMode_t;


/**
  * @brief  ������ʱ��
  * @param  id: Ҫ�����Ķ�ʱ��id
  *         mode:   ��ʱ���Ĵ���ģʽ
  *         interval: ��ʱ���������,��λΪms
  * @retval None
  */
extern int HL_TimerStart(HL_TimerId_t id, HL_TimerMode_t mode, uint16_t interval);

/**
  * @brief  �رն�ʱ��
  * @param  id: Ҫ�����Ķ�ʱ��id
  * @retval None
  */
extern int HL_TimerStop(HL_TimerId_t id);


