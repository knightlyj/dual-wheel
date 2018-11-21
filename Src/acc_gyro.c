#include "acc_gyro.h"
#include "bmi160.h"
#include "spi_gpio.h"
#include "sys_time.h"

static CL_BOOL initialized = CL_FALSE;
static struct bmi160_dev sensor;

void AccGryo_DelayMS(uint32_t period)
{
    DelayMs((uint16_t)period);
}


int8_t AccGryo_Read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    SPI_ReadMultiReg(reg_addr, data, len);
    return BMI160_OK;
}

int8_t AccGryo_Write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    SPI_WriteMultiReg(reg_addr, data, len);
    return BMI160_OK;
}


void AccGyro_Init(void)
{
    int8_t res = BMI160_E_DEV_NOT_FOUND;
    CL_BOOL selfTestRes = CL_FALSE;

    SPI_Init();
    DelayMs(2);

    sensor.id = 0;
    sensor.interface = BMI160_SPI_INTF;

    sensor.read = AccGryo_Read;
    sensor.write = AccGryo_Write;
    sensor.delay_ms = AccGryo_DelayMS;

    res = bmi160_init(&sensor); //先初始化
    if(res == BMI160_OK)
    {
        sensor.accel_cfg.power = BMI160_ACCEL_NORMAL_MODE;
        sensor.gyro_cfg.power = BMI160_GYRO_NORMAL_MODE;
        res = bmi160_set_power_mode(&sensor); //设置为正常工作模式
        
        if(res == BMI160_OK)
        {
            selfTestRes = AccGyro_SelfTest();
        }

    }

    if(selfTestRes == CL_TRUE && res == BMI160_OK)
    {
        initialized = CL_TRUE;

    }
    else
    {
        Log("acc gyro init failed\r\n");
    }
}

CL_BOOL AccGyro_SelfTest(void)
{
    if(bmi160_perform_self_test(BMI160_ACCEL_ONLY, &sensor) == BMI160_OK
       && bmi160_perform_self_test(BMI160_GYRO_ONLY, &sensor) == BMI160_OK)
    {
        return CL_TRUE;
    }

    return CL_FALSE;
}



