
#if (HL_MCU_TYPE == HL_STM32F10X_CL)
#include "stm32f1xx_ll_tim.h"
#elif (HL_MCU_TYPE == HL_STM32F407X)
#include "stm32f4xx_ll_tim.h"
#endif

//��ʱ֧��TIM2~5,�Լ�auto reloadģʽ

//����ʱ��
int HL_TimerStart(HL_TimerId_t id, HL_TimerMode_t mode, uint16_t interval)
{
    LL_TIM_InitTypeDef TIM_InitStruct;
    TIM_TypeDef* TIM;
    uint32_t periph;
    IRQn_Type irq;
    const uint32_t presc = 1000;

    switch(id)
    {
        case HL_Timer2:
            TIM = TIM2;
            periph = LL_APB1_GRP1_PERIPH_TIM2;
            irq = TIM2_IRQn;
            break;
        case HL_Timer3:
            TIM = TIM3;
            periph = LL_APB1_GRP1_PERIPH_TIM3;
            irq = TIM3_IRQn;
            break;
        case HL_Timer4:
            TIM = TIM4;
            periph = LL_APB1_GRP1_PERIPH_TIM4;
            irq = TIM4_IRQn;
            break;
        case HL_Timer5:
            TIM = TIM5;
            periph = LL_APB1_GRP1_PERIPH_TIM5;
            irq = TIM5_IRQn;
            break;
        default:
            return CL_INVALID_PARAM;
    }

    if(mode == HL_TimerAutoLoad)
    {
        /* Peripheral clock enable */
        LL_APB1_GRP1_EnableClock(periph);

        /* TIM2 interrupt Init */
        NVIC_SetPriority(irq, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
        NVIC_EnableIRQ(irq);

        TIM_InitStruct.Prescaler = presc - 1;
        TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP; //���ϼ���
        TIM_InitStruct.Autoreload = TIMER_CLOCK_FREQ * interval / presc / 1000 - 1; //����Ԥ��Ƶ�������ֵ
        TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1; //����Ƶ
        LL_TIM_Init(TIM, &TIM_InitStruct);  //��ʼ����ʱ��

        LL_TIM_EnableARRPreload(TIM); //����auto reload

        LL_TIM_SetClockSource(TIM, LL_TIM_CLOCKSOURCE_INTERNAL); //�ڲ�ʱ��Դ

        LL_TIM_SetTriggerOutput(TIM, LL_TIM_TRGO_RESET); //���ô������??

        LL_TIM_DisableMasterSlaveMode(TIM); //����ģʽ,���� 

        LL_TIM_EnableIT_UPDATE(TIM); //ʹ��update�ж�

        LL_TIM_EnableCounter(TIM); //���￪������

    }
    else
    {
        return CL_INVALID_PARAM;
    }

    return CL_SUCCESS;
}

//�ض�ʱ��
int HL_TimerStop(HL_TimerId_t id)
{
    TIM_TypeDef* TIM;
    switch(id)
    {
        case HL_Timer2:
            TIM = TIM2;
            break;
        case HL_Timer3:
            TIM = TIM3;
            break;
        case HL_Timer4:
            TIM = TIM4;
            break;
        case HL_Timer5:
            TIM = TIM5;
            break;
        default:
            return CL_INVALID_PARAM;
    }

    LL_TIM_DeInit(TIM); //��λ��ʱ��

    return CL_SUCCESS;

}


