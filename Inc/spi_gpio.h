#pragma once

#include "cl_common.h"

void SPI_Init(void);
uint8_t SPI_ReadReg(uint8_t reg);
void SPI_WriteReg(uint8_t reg, uint8_t value);

void SPI_WriteMultiReg(uint8_t reg, uint8_t* buff, uint16_t length);
void SPI_ReadMultiReg(uint8_t reg, uint8_t* buff, uint16_t length);



