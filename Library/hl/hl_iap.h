#pragma once

#include "cl_common.h"
#include "hl_config.h"

/******************************
 ��Щ������Ҫ���ж��������

 *******************************/

//������д����ǰ,��Ҫ��ʹ��
extern int HL_IAP_Enable(uint32_t addr, uint32_t size);

//������֮��,Ҫ�ر�IAP
extern int HL_IAP_Disable(uint32_t addr, uint32_t size);

//��addr��ʼ,������СΪsize
extern int HL_IAP_Erase(uint32_t addr, uint32_t size);

//write֮ǰ,��Ҫȷ���Ѿ�erase
extern int HL_IAP_Write(uint32_t addr, const uint8_t* buff, uint32_t length);


