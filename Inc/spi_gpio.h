#pragma once

#include "cl_common.h"

extern void SPI_Init(void);
extern uint8_t SPI_ReadReg(uint8_t reg);
extern void SPI_WriteReg(uint8_t reg, uint8_t value);

