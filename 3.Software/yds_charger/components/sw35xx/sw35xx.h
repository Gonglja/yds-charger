/*
 * @Author: [Gonglja]
 * @Date: 2022-06-20 09:00:00
 * @LastEditors: [Gonglja]
 * @LastEditTime: 2022-06-20 15:13:00
 * @Description: 
 */

#ifndef SW35XX_H_
#define SW35XX_H_

#include "software_i2c.h"

#define I2C_RETRIES 10

typedef enum{
    NONE_PROC = 0,
    QC2_0,
    QC3_0,
    FCP,
    SCP,
    PD_FIX,
    PD_PPS,
    PE1_1,
    PE2_0,
    VOOC,
    SFCP,
    AFC,
    CP_RESERVED
}chargeprotocol_t;

typedef enum{
    NONE_PD = 0,
    PD2_0,
    PD3_0,
    PV_RESERVED
}pdversion_t;

typedef struct{
    uint16_t OutVol;// 输出电压
    uint16_t OutCur;// 输出电流
    uint16_t InVol;// 输入电压
    struct{
        bool pro_fastcharge;// 0-非快充协议  1-快充协议 
        bool val_fastcharge;// 0-电压处于非快充  1-电压处于快充
        bool out_open;// 0-端口关闭  1-端口打开
        bool buck_open;// 0-buck关闭  1-buck打开
        bool val_input_upmax;// 0-输入正常  1-输入过压
        bool tem_alarm_upmax;// 0-温度正常  1-温度报警
        bool tem_shutdown;// 0-温度正常  1-高温关机保护
        bool short_citcuit;// 0-输出正常  1-输出短路
    }state;
    chargeprotocol_t protocol;//当前协议
    pdversion_t pdversion;//PD版本
}sw35xx_t;

sw35xx_t sw35xx_c1,sw35xx_c2;

/* 内部接口 */
uint8_t SW35xxReadReg(swi2c_t port, uint8_t address, uint8_t reg);
uint8_t SW35xxWriteReg(swi2c_t port, uint8_t address, uint8_t reg, uint8_t data);

/* 外部接口 */
void SW35xxInit();
void SW35xxUpdate();

#endif