/*
 * @Author: [LiaoZhelin]
 * @Date: 2022-04-07 22:32:34
 * @LastEditors: [Gonglja]
 * @LastEditTime: 2022-06-20 15:06:54
 * @Description: 
 */
#include <stdio.h>
#include "esp_log.h"
#include <driver/gpio.h>

#include "sw35xx.h"
#include "sw3526.h"

static const char* TAG = "sw3526";

static void sw3526WrReg(uint8_t reg, uint8_t val, swi2c_t i2c_x) {
    SW35xxWriteReg(i2c_x, SW35XX_ADDRESS, reg, val);
}

static uint8_t sw3526RdReg(uint8_t reg, swi2c_t i2c_x) {
    return SW35xxReadReg(i2c_x, SW35XX_ADDRESS, reg);
}

void SW3526Init(void){
    sw_i2c_init(GPIO_NUM_7,GPIO_NUM_6,SW_I2C_1);
    sw3526WrReg(SW35XX_I2C_WRITE_ENABLE,0x20,SW_I2C_1);
    sw3526WrReg(SW35XX_I2C_WRITE_ENABLE,0x40,SW_I2C_1);
    sw3526WrReg(SW35XX_I2C_WRITE_ENABLE,0x80,SW_I2C_1);
    sw3526WrReg(SW35XX_PWR_CONF,0x07,SW_I2C_1);//设定功率限制为64W
    ESP_LOGI(TAG,"C1-Version=%d\r\n",sw3526RdReg(SW35XX_IC_VERSION,SW_I2C_1));

    sw_i2c_init(GPIO_NUM_5,GPIO_NUM_6,SW_I2C_2);
    sw3526WrReg(SW35XX_I2C_WRITE_ENABLE,0x20,SW_I2C_2);
    sw3526WrReg(SW35XX_I2C_WRITE_ENABLE,0x40,SW_I2C_2);
    sw3526WrReg(SW35XX_I2C_WRITE_ENABLE,0x80,SW_I2C_2);
    sw3526WrReg(SW35XX_PWR_CONF,0x07,SW_I2C_2);//设定功率限制为64W
    ESP_LOGI(TAG,"C2-Version=%d\r\n",sw3526RdReg(SW35XX_IC_VERSION,SW_I2C_2));
}

void SW3526Update(void){
    uint8_t buf_1,buf_2;
    //C1口状态读取
    sw3526WrReg(SW35XX_ADC_DATA_TYPE,0x01,SW_I2C_1);
    buf_1 = sw3526RdReg(SW35XX_ADC_DATA_BUF_H,SW_I2C_1);
    buf_2 = sw3526RdReg(SW35XX_ADC_DATA_BUF_L,SW_I2C_1);
    sw35xx_c1.InVol = ((buf_1<<4)|buf_2);
    sw3526WrReg(SW35XX_ADC_DATA_TYPE,0x02,SW_I2C_1);
    buf_1 = sw3526RdReg(SW35XX_ADC_DATA_BUF_H,SW_I2C_1);
    buf_2 = sw3526RdReg(SW35XX_ADC_DATA_BUF_L,SW_I2C_1);
    sw35xx_c1.OutVol = (buf_1<<4|buf_2);
    sw3526WrReg(SW35XX_ADC_DATA_TYPE,0x03,SW_I2C_1);
    buf_1 = sw3526RdReg(SW35XX_ADC_DATA_BUF_H,SW_I2C_1);
    buf_2 = sw3526RdReg(SW35XX_ADC_DATA_BUF_L,SW_I2C_1);
    sw35xx_c1.OutCur = (buf_1<<4|buf_2);
    buf_1 = sw3526RdReg(SW35XX_FCX_STATUS,SW_I2C_1);
    sw35xx_c1.protocol = (buf_1&0X0F);
    sw35xx_c1.pdversion = (buf_1&0X30);
    sw35xx_c1.state.pro_fastcharge = (buf_1&0X80);
    sw35xx_c1.state.val_fastcharge = (buf_1&0X40);
    buf_1 = sw3526RdReg(SW35XX_PWR_STATUS,SW_I2C_1);
    sw35xx_c1.state.out_open = (buf_1&0x02);
    sw35xx_c1.state.buck_open = (buf_1&0x01);
    buf_1 = sw3526RdReg(SW35XX_PWR_FAULTS,SW_I2C_1);
    sw35xx_c1.state.val_input_upmax = (buf_1&0x10);
    sw35xx_c1.state.tem_alarm_upmax = (buf_1&0x04);
    sw35xx_c1.state.tem_shutdown = (buf_1&0x02);
    sw35xx_c1.state.short_citcuit = (buf_1&0x01); 

    //C2口状态读取
    sw3526WrReg(SW35XX_ADC_DATA_TYPE,0x01,SW_I2C_2);
    buf_1 = sw3526RdReg(SW35XX_ADC_DATA_BUF_H,SW_I2C_2);
    buf_2 = sw3526RdReg(SW35XX_ADC_DATA_BUF_L,SW_I2C_2);
    sw35xx_c2.InVol = (buf_1<<4|buf_2);
    sw3526WrReg(SW35XX_ADC_DATA_TYPE,0x02,SW_I2C_2);
    buf_1 = sw3526RdReg(SW35XX_ADC_DATA_BUF_H,SW_I2C_2);
    buf_2 = sw3526RdReg(SW35XX_ADC_DATA_BUF_L,SW_I2C_2);
    sw35xx_c2.OutVol = (buf_1<<4|buf_2);
    sw3526WrReg(SW35XX_ADC_DATA_TYPE,0x03,SW_I2C_2);
    buf_1 = sw3526RdReg(SW35XX_ADC_DATA_BUF_H,SW_I2C_2);
    buf_2 = sw3526RdReg(SW35XX_ADC_DATA_BUF_L,SW_I2C_2);
    sw35xx_c2.OutCur = (buf_1<<4|buf_2);
    buf_1 = sw3526RdReg(SW35XX_FCX_STATUS,SW_I2C_2);
    sw35xx_c2.protocol = (buf_1&0X0F);
    sw35xx_c2.pdversion = (buf_1&0X30);
    sw35xx_c2.state.pro_fastcharge = (buf_1&0X80);
    sw35xx_c2.state.val_fastcharge = (buf_1&0X40);
    buf_1 = sw3526RdReg(SW35XX_PWR_STATUS,SW_I2C_2);
    sw35xx_c2.state.out_open = (buf_1&0x02);
    sw35xx_c2.state.buck_open = (buf_1&0x01);
    buf_1 = sw3526RdReg(SW35XX_PWR_FAULTS,SW_I2C_2);
    sw35xx_c2.state.val_input_upmax = (buf_1&0x10);
    sw35xx_c2.state.tem_alarm_upmax = (buf_1&0x04);
    sw35xx_c2.state.tem_shutdown = (buf_1&0x02);
    sw35xx_c2.state.short_citcuit = (buf_1&0x01); 
    //ESP_LOGI(TAG, "state=%x",buf_1);
    //ESP_LOGI(TAG,"\r\nsw3526_c1_out=%d\r\nsw3526_c1_cur=%d\r\nsw3526_c1_vin=%d\r\n",sw35xx_c1.OutVol,sw35xx_c1.OutCur,sw35xx_c1.InVol);
    //ESP_LOGI(TAG,"\r\nsw3526_c2_out=%d\r\nsw3526_c2_cur=%d\r\nsw3526_c2_vin=%d\r\n",sw35xx_c2.OutVol,sw35xx_c2.OutCur,sw35xx_c2.InVol);
}