#include "spi_gpio.h"
#include "stm32f4xx_ll_gpio.h"

#define SPI_CS_PORT         GPIOA
#define SPI_CS_PIN          LL_GPIO_PIN_4

#define SPI_MOSI_PORT       GPIOA
#define SPI_MOSI_PIN        LL_GPIO_PIN_7

#define SPI_CLK_PORT        GPIOA
#define SPI_CLK_PIN         LL_GPIO_PIN_5

#define SPI_MISO_PORT       GPIOA
#define SPI_MISO_PIN        LL_GPIO_PIN_6

//------------CS-------------------
CL_STATIC_INLINE void CS_Low()
{
    LL_GPIO_ResetOutputPin(SPI_CS_PORT, SPI_CS_PIN);
}

CL_STATIC_INLINE void CS_High()
{
    LL_GPIO_SetOutputPin(SPI_CS_PORT, SPI_CS_PIN);
}

//-------------MOSI---------------------
CL_STATIC_INLINE void MOSI_Low()
{
    LL_GPIO_ResetOutputPin(SPI_MOSI_PORT, SPI_MOSI_PIN);
}

CL_STATIC_INLINE void MOSI_High()
{
    LL_GPIO_SetOutputPin(SPI_MOSI_PORT, SPI_MOSI_PIN);
}

//-------------CLK-------------------
CL_STATIC_INLINE void CLK_Low()
{
    LL_GPIO_ResetOutputPin(SPI_CLK_PORT, SPI_CLK_PIN);
}

CL_STATIC_INLINE void CLK_High()
{
    LL_GPIO_SetOutputPin(SPI_CLK_PORT, SPI_CLK_PIN);
}

//---------------MISO-------------------
CL_STATIC_INLINE uint8_t Read_MISO()
{
    return LL_GPIO_IsInputPinSet(SPI_MISO_PORT, SPI_MISO_PIN);
}

void SPI_Init(void)
{
    CS_High();
    CLK_High();
    MOSI_High();
}

//SPI的延时
//static void SPI_Delay(int x)
//{
//    int i;
//    for(i = 0; i < x; i++)  
//    {
//        __NOP();
//    }
//}

//发1Byte,并返回接收到的数据
//static uint8_t SPI_Send(uint8_t byte)
//{
//    uint8_t i, Dat = 0;
//
//    SPI_Delay(1);
//    for(i=0; i<8; i++)
//    {
//        Dat<<=1;
//        CLK_Low();
//        SPI_Delay(1);
//        (byte&0x80) ? MOSI_High() : MOSI_Low();     // 三目运算符传输数据
//        SPI_Delay(1);
//        CLK_High();
//        Dat |= Read_MISO();
//        byte<<=1;
//        SPI_Delay(1);
//    }
//
//    MOSI_High();                                    //  释放MOSI
//    return Dat;
//}

static uint8_t SPI_SendFast(uint8_t byte)
{
    uint8_t i, Dat = 0;

    for(i=0; i<8; i++)
    {
        Dat<<=1;
        CLK_Low();
        (byte&0x80) ? MOSI_High() : MOSI_Low();     // 三目运算符传输数据
        CLK_High();
        Dat |= Read_MISO();
        byte<<=1;
    }

    MOSI_High();                                    //  释放MOSI
    return Dat;
}



uint8_t SPI_ReadReg(uint8_t reg)
{
    uint8_t res;
    CS_Low();
    SPI_SendFast(reg);
    res = SPI_SendFast(0xff);
    CS_High();
    return res;
}

void SPI_ReadMultiReg(uint8_t reg, uint8_t* buff, uint16_t length)
{
    uint16_t i;
    CS_Low();
    SPI_SendFast(reg);
    for(i = 0; i < length; i++)
    {
        buff[i] = SPI_SendFast(0xff);
    }
    CS_High();
    
}



void SPI_WriteReg(uint8_t reg, uint8_t value)
{
    CS_Low();
    SPI_SendFast(reg);
    SPI_SendFast(value);
    CS_High();
}

void SPI_WriteMultiReg(uint8_t reg, uint8_t* buff, uint16_t length)
{
    uint16_t i;
    CS_Low();
    SPI_SendFast(reg);
    for(i = 0; i < length; i++)
    {
        SPI_SendFast(buff[i]);
    }
    CS_High();
}



