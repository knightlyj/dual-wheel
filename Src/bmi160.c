#include "bmi160.h"
#include "spi_gpio.h"

void BMI160_SelfTest(void)
{
    SPI_WriteReg(0x40, 0x2c); //ACC_CONF = 0x2c  ��������Ϊ8g
    SPI_WriteReg(0x6d, 0x01); //SELF_TEST = 0x01 ʹ�ܲ��� 
}


