/*
 * @Author: [Gonglja]
 * @Date: 2022-06-18 18:28:00
 * @LastEditors: [Gonglja]
 * @LastEditTime: 2022-06-18 19:54:00
 * @Description: 
 */
#ifndef _SW3518S_H_
#define _SW3518S_H_


// 芯片地址
#define SW3618S_ADDRESS         0x78

// 版本信息 : bit[2:0] default:0x07
#define SW3518S_IC_VERSION      0x01

// 快充指示                
#define SW3518S_QC_INDICATOR    0x06
// 快充配置0
#define SW3518S_QC_CONFIG0      0xAA
// 快充配置1 三星1.2v模式
#define SW3518S_QC_CONFIG1_     0xAD
// 快充配置1
#define SW3518S_QC_CONFIG1      0xB9
// 快充配置2
#define SW3518S_QC_CONFIG2      0xBA
// 快充配置3
#define SW3518S_QC_CONFIG3      0xBC

// 系统状态0
#define SW3518S_SYS_STATUS0     0x07
// 系统状态1
#define SW3518S_SYS_STATUS1     0x08

// IIC 使能控制
#define SW3518S_I2C_ENABLE_CTL  0x12

// PWR 寄存器写使能
#define SW3518S_PWR_WR_ENABLE   0x15
// PWR 强制操作
#define SW3518S_PWR_FORCE_OP    0x16

// ADC VIN使能
#define SW3518S_ADC_VIN_ENABLE  0x13
// ADC VIN数据 高8位，系数160mV/bit
#define SW3518S_ADC_VIN_DATA    0x30
// ADC VOUT数据 高8位，系数96mV/bit
#define SW3518S_ADC_VOUT_DATA   0x31
// ADC IOUT C口数据 高8位，系数40mA/bit
#define SW3518S_ADC_IOUT_C_DATA 0x33
// ADC IOUT A口数据 高8位，系数40mA/bit
#define SW3518S_ADC_IOUT_A_DATA 0x34
// ADC NTC电压数据 高8位，系数8mV/bit
#define SW3518S_ADC_VNTC_DATA   0x37
// ADC 配置
#define SW3518S_ADC_CONFIG      0x3A
// ADC 数据高8位
#define SW3518S_ADC_H8B_DATA    0x3B
// ADC 数据低4位
#define SW3518S_ADC_L4B_DATA    0x3C

// HARDRESET 次数设置
#define SW3518S_HARDRESET_COUNT 0x75
// 连接设置
#define SW3518S_CONNECT_SET     0x76
// 功率配置
#define SW3518S_POWER_CONFIG    0xA6
// 端口配置
#define SW3518S_ENDPOINT_CONFIG 0xAB

// VID 配置0
#define SW3518S_VID_CONFIG0     0xAF
// VID 配置1
#define SW3518S_VID_CONFIG1     0xBF

// PD 命令请求
#define SW3518S_PD_CMD_REQ      0x70
// PD 命令使能
#define SW3518S_PD_CMD_ENABLE   0x71
// PD 配置0
#define SW3518S_PD_CONFIG0      0xB0
// PD 配置1
#define SW3518S_PD_CONFIG1      0xB1
// PD 配置2
#define SW3518S_PD_CONFIG2      0xB2
// PD 配置3
#define SW3518S_PD_CONFIG3      0xB3
// PD 配置4
#define SW3518S_PD_CONFIG4      0xB4
// PD 配置5
#define SW3518S_PD_CONFIG5      0xB5
// PD 配置6
#define SW3518S_PD_CONFIG6      0xB6
// PD 配置7
#define SW3518S_PD_CONFIG7      0xB7
// PD 配置8
#define SW3518S_PD_CONFIG8      0xB8
// PD 配置9
#define SW3518S_PD_CONFIG9      0xBE

// 限流控制
#define SW3518S_CURRENTLIMIT_CONFIG 0xBD


#endif