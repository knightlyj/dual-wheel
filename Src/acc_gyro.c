#include "acc_gyro.h"
#include "bmi160.h"
#include "spi_gpio.h"
#include "sys_time.h"

#define __ACC_RANGE     BMI160_ACCEL_RANGE_8G
#define __GYRO_RANGE    BMI160_GYRO_RANGE_2000_DPS

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


static CL_RESULT AccGyro_SelfTest(void)
{
    if(bmi160_perform_self_test(BMI160_ACCEL_ONLY, &sensor) == BMI160_OK
       && bmi160_perform_self_test(BMI160_GYRO_ONLY, &sensor) == BMI160_OK)
    {
        return CL_SUCCESS;
    }

    return CL_FAILED;
}


CL_RESULT AccGyro_Init(void)
{
    int8_t res = BMI160_E_DEV_NOT_FOUND;
    CL_RESULT selfTestRes = CL_FAILED;

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
        selfTestRes = AccGyro_SelfTest();

        /* Select the Output data rate, range of accelerometer sensor */
        sensor.accel_cfg.odr = BMI160_ACCEL_ODR_1600HZ;
        sensor.accel_cfg.range = __ACC_RANGE;
        sensor.accel_cfg.bw = BMI160_ACCEL_BW_NORMAL_AVG4;

        /* Select the power mode of accelerometer sensor */
        sensor.accel_cfg.power = BMI160_ACCEL_NORMAL_MODE;

        /* Select the Output data rate, range of Gyroscope sensor */
        sensor.gyro_cfg.odr = BMI160_GYRO_ODR_3200HZ;
        sensor.gyro_cfg.range = __GYRO_RANGE;
        sensor.gyro_cfg.bw = BMI160_GYRO_BW_NORMAL_MODE;

        /* Select the power mode of Gyroscope sensor */
        sensor.gyro_cfg.power = BMI160_GYRO_NORMAL_MODE;

        res = bmi160_set_sens_conf(&sensor);  //传感器配置
        AccGro_GetData(CL_NULL);
    }

    if(selfTestRes == CL_SUCCESS && res == BMI160_OK)
    {
        initialized = CL_TRUE;
        return CL_SUCCESS;
    }
    else
    {
        Log("acc gyro init failed\r\n");
        return CL_FAILED;
    }
}


#if __ACC_RANGE == BMI160_ACCEL_RANGE_8G
const float accResolution = 0.00024415f; //以g为单位
#endif

#if __GYRO_RANGE == BMI160_GYRO_RANGE_2000_DPS
const float gyroResolution = 0.061037f;  //以度数为单位
#elif __GYRO_RANGE == BMI160_GYRO_RANGE_1000_DPS
const float gyroResolution = 0.030519f;  //以度数为单位
#endif
CL_RESULT AccGro_GetData(AccGyro_Data_t* data)
{
    int8_t res;
    if(initialized != CL_TRUE)
        return CL_FAILED;
    
    struct bmi160_sensor_data accel;
    struct bmi160_sensor_data gyro;

    res = bmi160_get_sensor_data((BMI160_ACCEL_SEL | BMI160_GYRO_SEL), &accel, &gyro, &sensor);



    if(res == BMI160_OK)
    {
//        Log("acc: %d, %d, %d\r\n", accel.x, accel.y, accel.z);
//        Log("gyro: %d, %d, %d\r\n", gyro.x, gyro.y, gyro.z);
        if(data != CL_NULL)
        {
            data->acc_x = accel.x  * accResolution;
            data->acc_y = accel.y  * accResolution;
            data->acc_z = accel.z  * accResolution;

            data->gyro_x = gyro.x * gyroResolution;
            data->gyro_y = gyro.y * gyroResolution;
            data->gyro_z = gyro.z * gyroResolution;
        }
        return CL_SUCCESS;
    }
    else
    {
        return CL_FAILED;
    }
}


