/*
 * @Author: [LiaoZhelin]
 * @Date: 2022-04-07 22:32:34
 * @LastEditors: [Gonglja]
 * @LastEditTime: 2022-06-20 15:06:54
 * @Description: 
 */
#ifndef _SW3526_H_
#define _SW3526_H_

#include "software_i2c.h"

#define SW35XX_ADDRESS 0x78

#define SW35XX_IC_VERSION 0x01
#define SW35XX_BUCK_DATE_H 0X03
#define SW35XX_BUCK_DATE_L 0X04
#define SW35XX_BUCK_LIMIT_I 0X05
#define SW35XX_FCX_STATUS 0x06
#define SW35XX_PWR_STATUS 0x07
#define SW35XX_PWR_FAULTS 0X0B
#define SW35XX_I2C_WRITE_ENABLE 0x12
#define SW35XX_BUCK_SHUTDOWN 0x13

#define SW35XX_ADC_VIN_H 0x30
#define SW35XX_ADC_VOUT_H 0x31

#define SW35XX_ADC_IOUT_H 0x33

#define SW35XX_ADC_DATA_TYPE 0x3a
#define SW35XX_ADC_DATA_BUF_H 0x3b
#define SW35XX_ADC_DATA_BUF_L 0x3c

#define SW35XX_POW_STATUS 0x68
#define SW35XX_PWR_CONF 0xa7

#define SW35XX_PD_SRC_REQ 0x70
#define SW35XX_FAST_CHARGE_CON0 0xa8
#define SW35XX_FAST_CHARGE_CON1 0xa9
#define SW35XX_FAST_CHARGE_CON2 0xaa
#define SW35XX_FAST_CHARGE_CON3 0xab
#define SW35XX_FAST_CHARGE_CON4 0xac

#define SW35XX_VID_CONF0 0xae
#define SW35XX_VID_CONF1 0xaf


void SW3526Init(void);
void SW3526Update(void);

#endif