/*
 * @Author: [Gonglja]
 * @Date: 2022-06-18 18:28:00
 * @LastEditors: [Gonglja]
 * @LastEditTime: 2022-06-18 19:54:00
 * @Description: 
 */

#include "sw3518s.h"
#include <stdio.h>
#include "esp_log.h"
#include <driver/gpio.h>
#include "software_i2c.h"
#include "sw35xx.h"

static const char* TAG = "sw3518s";

static void sw3518sWrReg(swi2c_t i2c_x, uint8_t reg, uint8_t val) {
    SW35xxWriteReg(i2c_x, SW3518S_ADDRESS, reg, val);
}

static uint8_t sw3518sRdReg(swi2c_t i2c_x, uint8_t reg) {
    return SW35xxReadReg(i2c_x, SW3518S_ADDRESS, reg);
}


void SW3518sInit(void){
    for(swi2c_t i2c_x=SW_I2C_1; i2c_x < SW_I2C_MAX; ++i2c_x) {
        sw_i2c_init(GPIO_NUM_7,GPIO_NUM_6, SW_I2C_1);
        // REG 0xB0~0xBF 使能
        sw3518sWrReg(SW3518S_I2C_ENABLE_CTL, 0x20, i2c_x);
        sw3518sWrReg(SW3518S_I2C_ENABLE_CTL, 0x40, i2c_x);
        sw3518sWrReg(SW3518S_I2C_ENABLE_CTL, 0x80, i2c_x);

        // ADC_VIN 使能
        sw3518sWrReg(SW3518S_ADC_VIN_ENABLE, 0x01, i2c_x);

        // PWR 写使能
        sw3518sWrReg(SW3518S_PWR_WR_ENABLE,  0x20, i2c_x);
        sw3518sWrReg(SW3518S_PWR_WR_ENABLE,  0x40, i2c_x);
        sw3518sWrReg(SW3518S_PWR_WR_ENABLE,  0x80, i2c_x);

        // 功率配置(非 PD 和低压直充和双口在线以外的功率设置)
        sw3518sWrReg(SW3518S_POWER_CONFIG,   0x03, i2c_x);
    } 
}

void SW3518sUpdate(void){
    uint8_t buf_1,buf_2;
    // C1口状态读取
    // 输入电压
    sw3518sWrReg(SW3518S_ADC_CONFIG, 0x01, SW_I2C_1);
    buf_1 = sw3518sRdReg(SW3518S_ADC_H8B_DATA, SW_I2C_1);
    buf_2 = sw3518sRdReg(SW3518S_ADC_L4B_DATA, SW_I2C_1);
    sw35xx_c1.InVol = (buf_1<<4|buf_2);

    // 输入电压
    sw3518sWrReg(SW3518S_ADC_CONFIG, 0x02, SW_I2C_1);
    buf_1 = sw3518sRdReg(SW3518S_ADC_H8B_DATA, SW_I2C_1);
    buf_2 = sw3518sRdReg(SW3518S_ADC_L4B_DATA, SW_I2C_1);
    sw35xx_c1.OutVol = (buf_1<<4|buf_2);

    // 输出c口电流
    sw3518sWrReg(SW3518S_ADC_CONFIG, 0x03, SW_I2C_1);
    buf_1 = sw3518sRdReg(SW3518S_ADC_H8B_DATA, SW_I2C_1);
    buf_2 = sw3518sRdReg(SW3518S_ADC_L4B_DATA, SW_I2C_1);
    sw35xx_c1.OutCur = (buf_1<<4|buf_2);

    // 输出指示
    buf_1 = sw3518sRdReg(SW3518S_QC_INDICATOR, SW_I2C_1);
    sw35xx_c1.protocol = (buf_1&0X0F);
    sw35xx_c1.pdversion = (buf_1&0X30);
    sw35xx_c1.state.pro_fastcharge = (buf_1&0X80);
    // sw35xx_c1.state.val_fastcharge = (buf_1&0X40);

    // 系统状态 
    buf_1 = sw3518sRdReg(SW3518S_SYS_STATUS0, SW_I2C_1);
    sw35xx_c1.state.out_open = (buf_1&0x04);
    sw35xx_c1.state.buck_open = (buf_1&0x01);

    // buf_1 = sw3518sRdReg(SW35XX_PWR_FAULTS, SW_I2C_1);
    // sw35xx_c1.state.val_input_upmax = (buf_1&0x10);
    // sw35xx_c1.state.tem_alarm_upmax = (buf_1&0x04);
    // sw35xx_c1.state.tem_shutdown = (buf_1&0x02);
    // sw35xx_c1.state.short_citcuit = (buf_1&0x01); 

    // C2口状态读取
    // 输入电压
    sw3518sWrReg(SW3518S_ADC_CONFIG, 0x01, SW_I2C_2);
    buf_1 = sw3518sRdReg(SW3518S_ADC_H8B_DATA, SW_I2C_2);
    buf_2 = sw3518sRdReg(SW3518S_ADC_L4B_DATA, SW_I2C_2);
    sw35xx_c2.InVol = (buf_1<<4|buf_2);

    // 输入电压
    sw3518sWrReg(SW3518S_ADC_CONFIG, 0x02, SW_I2C_2);
    buf_1 = sw3518sRdReg(SW3518S_ADC_H8B_DATA, SW_I2C_2);
    buf_2 = sw3518sRdReg(SW3518S_ADC_L4B_DATA, SW_I2C_2);
    sw35xx_c2.OutVol = (buf_1<<4|buf_2);

    // 输出c口电流
    sw3518sWrReg(SW3518S_ADC_CONFIG, 0x03, SW_I2C_2);
    buf_1 = sw3518sRdReg(SW3518S_ADC_H8B_DATA, SW_I2C_2);
    buf_2 = sw3518sRdReg(SW3518S_ADC_L4B_DATA, SW_I2C_2);
    sw35xx_c2.OutCur = (buf_1<<4|buf_2);

    // 输出指示
    buf_1 = sw3518sRdReg(SW3518S_QC_INDICATOR, SW_I2C_2);
    sw35xx_c2.protocol = (buf_1&0X0F);
    sw35xx_c2.pdversion = (buf_1&0X30);
    sw35xx_c2.state.pro_fastcharge = (buf_1&0X80);
    // sw35xx_c2.state.val_fastcharge = (buf_1&0X40);

    // 系统状态
    buf_1 = sw3518sRdReg(SW3518S_SYS_STATUS0, SW_I2C_2);
    sw35xx_c2.state.out_open = (buf_1&0x04);
    sw35xx_c2.state.buck_open = (buf_1&0x01);
    //ESP_LOGI(TAG,"\r\nsw3526_c1_out=%d\r\nsw3526_c1_cur=%d\r\nsw3526_c1_vin=%d\r\n",sw35xx_c1.OutVol,sw35xx_c1.OutCur,sw35xx_c1.InVol);
    //ESP_LOGI(TAG,"\r\nsw3526_c2_out=%d\r\nsw3526_c2_cur=%d\r\nsw3526_c2_vin=%d\r\n",sw35xx_c2.OutVol,sw35xx_c2.OutCur,sw35xx_c2.InVol);
}