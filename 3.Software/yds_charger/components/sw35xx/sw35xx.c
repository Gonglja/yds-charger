/*
 * @Author: [Gonglja]
 * @Date: 2022-06-18 18:28:00
 * @LastEditors: [Gonglja]
 * @LastEditTime: 2022-06-20 15:13:00
 * @Description: 
 */

#include "software_i2c.h"

#define SW3526
// #define SW3518s


#if defined(SW3526) 
void SW3526Init();
void SW3526Update();
#endif

#if defined(SW3518s)
void SW3518sInit(void);
void SW3518sUpdate(void);
#endif

/* 内部接口 */
uint8_t SW35xxReadReg(swi2c_t port, uint8_t address, uint8_t reg) {
    uint8_t buf=0;
    setsw_i2c(port);
    sw_i2c_master_start();
    if(sw_i2c_master_write_byte(address)){
        //ESP_LOGI(TAG,"find_none_sw3526!\n");
        return 0;
    }
    if(sw_i2c_master_write_byte(reg)){
        //ESP_LOGI(TAG,"sw3525_resister_error!\n");
        return 0;
    }
    sw_i2c_master_start();
    if(sw_i2c_master_write_byte(address+1)){
        //ESP_LOGI(TAG,"sw3526_read_address_error!\n");
        return 0;
    }
    if(sw_i2c_master_read_byte(&buf,1)){
        //ESP_LOGI(TAG,"sw3526_read_error!\n");
        return 0;
    }
    sw_i2c_master_stop();
    //ESP_LOGI(TAG,"sw3526_data = %x\n",buf);
    return buf;
}


uint8_t SW35xxWriteReg(swi2c_t port, uint8_t address, uint8_t reg, uint8_t data){
    setsw_i2c(port);
    sw_i2c_master_start();
    if(sw_i2c_master_write_byte(address)){
        //ESP_LOGI(TAG,"find_none_sw3526!\n");
        return 0;
    }
    if(sw_i2c_master_write_byte(reg)){
        //ESP_LOGI(TAG,"sw3525_resister_error!\n");
        return 0;
    }
    if(sw_i2c_master_write_byte(data)){
        //ESP_LOGI(TAG,"sw3526_write_error!\n");
        return 0;
    }
    sw_i2c_master_stop();
    //ESP_LOGI(TAG,"sw3526_write_success!\n");
    return 1;
}

/* 外部接口 */
void SW35xxInit() {
#if defined(SW3526) 
    SW3526Init();
#endif

#if defined(SW3518s)
    SW3518sInit();
#endif
}


void SW35xxUpdate() {
#if defined(SW3526) 
    SW3526Update();
#endif

#if defined(SW3518s)
    SW3518sUpdate();
#endif 
}