#include "sensors.h"
#include "bmi160.h"
#include "spi_gpio.h"
#include "sys_time.h"
#include "stm32f4xx_ll_gpio.h"
#include "mathex.h"

//-----------------------------------------------------
//                  bmi160
//----------------------------------------------------
#define __ACC_RANGE     BMI160_ACCEL_RANGE_8G
#define __GYRO_RANGE    BMI160_GYRO_RANGE_2000_DPS

static struct bmi160_dev bmi160_device;

static void BMI160_DelayMs(uint32_t period)
{
    DelayMs((uint16_t)period);
}

static void BMI160_DelayFast(uint32_t period)
{
    return;        
}



static int8_t BMI160_SPIRead(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    SPI_ReadMultiReg(reg_addr, data, len);
    return BMI160_OK;
}

static int8_t BMI160_SPIWrite(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    SPI_WriteMultiReg(reg_addr, data, len);
    return BMI160_OK;
}

static CL_RESULT BMI160_SelfTest(void)
{
    if(bmi160_perform_self_test(BMI160_ACCEL_ONLY, &bmi160_device) == BMI160_OK
       && bmi160_perform_self_test(BMI160_GYRO_ONLY, &bmi160_device) == BMI160_OK)
    {
        return CL_SUCCESS;
    }

    return CL_FAILED;
}

CL_RESULT BMI160_Init(void)
{
    int8_t res = BMI160_E_DEV_NOT_FOUND;
    CL_RESULT selfTestRes = CL_FAILED;

    SPI_Init();
    DelayMs(2);

    bmi160_device.id = 0;
    bmi160_device.interface = BMI160_SPI_INTF;
    bmi160_device.read = BMI160_SPIRead;
    bmi160_device.write = BMI160_SPIWrite;
    bmi160_device.delay_ms = BMI160_DelayMs;

    res = bmi160_init(&bmi160_device); //先初始化
    if(res == BMI160_OK)
    {
        selfTestRes = BMI160_SelfTest();

        /* Select the Output data rate, range of accelerometer sensor */
        bmi160_device.accel_cfg.odr = BMI160_ACCEL_ODR_1600HZ;
        bmi160_device.accel_cfg.range = __ACC_RANGE;
        bmi160_device.accel_cfg.bw = BMI160_ACCEL_BW_NORMAL_AVG4;

        /* Select the power mode of accelerometer sensor */
        bmi160_device.accel_cfg.power = BMI160_ACCEL_NORMAL_MODE;

        /* Select the Output data rate, range of Gyroscope sensor */
        bmi160_device.gyro_cfg.odr = BMI160_GYRO_ODR_3200HZ;
        bmi160_device.gyro_cfg.range = __GYRO_RANGE;
        bmi160_device.gyro_cfg.bw = BMI160_GYRO_BW_NORMAL_MODE;

        /* Select the power mode of Gyroscope sensor */
        bmi160_device.gyro_cfg.power = BMI160_GYRO_NORMAL_MODE;

        res = bmi160_set_sens_conf(&bmi160_device);  //传感器配置
        BMI160_GetData(CL_NULL, CL_NULL);
    }

    if(selfTestRes == CL_SUCCESS && res == BMI160_OK)
    {
        return CL_SUCCESS;
    }
    else
    {
        Log("acc gyro init failed\r\n");
        return CL_FAILED;
    }
}

#if __ACC_RANGE == BMI160_ACCEL_RANGE_8G
const float accResolution = (8.0f * GRAVITY / 32767.0f); 
#endif

#if __GYRO_RANGE == BMI160_GYRO_RANGE_2000_DPS
const float gyroResolution = 0.061037f;  //以度数为单位
#elif __GYRO_RANGE == BMI160_GYRO_RANGE_1000_DPS
const float gyroResolution = 0.030519f;  //以度数为单位
#endif

CL_RESULT BMI160_GetData(Vector3* accData, Vector3* gyroData)
{
    int8_t res;
    
    struct bmi160_sensor_data accel;
    struct bmi160_sensor_data gyro;

    bmi160_device.delay_ms = BMI160_DelayFast;
    res = bmi160_get_sensor_data((BMI160_ACCEL_SEL | BMI160_GYRO_SEL), &accel, &gyro, &bmi160_device);
    
    if(res == BMI160_OK)
    {
//        Log("acc: %d, %d, %d\r\n", accel.x, accel.y, accel.z);
//        Log("gyro: %d, %d, %d\r\n", gyro.x, gyro.y, gyro.z);
        if(accData != CL_NULL)
        {
            accData->x = accel.x  * accResolution;
            accData->y = accel.y  * accResolution;
            accData->z = accel.z  * accResolution;            
        }
        if(gyroData != CL_NULL)
        {
            gyroData->x = gyro.x * gyroResolution;
            gyroData->y = gyro.y * gyroResolution;
            gyroData->z = gyro.z * gyroResolution;
        }
        return CL_SUCCESS;
    }
    else
    {
        return CL_FAILED;
    }
}

//-------------------------------------------------------





