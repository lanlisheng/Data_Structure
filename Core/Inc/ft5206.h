#ifdef __cplusplus
extern "C" {
#endif

#ifndef __FT5206_H
#define __FT5206_H

#include "main.h"

//与电容触摸屏连接的芯片引脚(未包含IIC引脚)
// IO操作函数
#define FT_RST(n)                                                              \
  (n ? HAL_GPIO_WritePin(GPIOI, GPIO_PIN_8, GPIO_PIN_SET)                      \
     : HAL_GPIO_WritePin(GPIOI, GPIO_PIN_8, GPIO_PIN_RESET)) // FT5206复位引脚
#define FT_INT HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_7)           // FT5206断引脚

// I2C读写命令
#define FT_CMD_WR 0X70 //写命令
#define FT_CMD_RD 0X71 //读命令

// FT5206 部分寄存器定义
#define FT_DEVIDE_MODE 0x00    // FT5206模式控制寄存器
#define FT_REG_NUM_FINGER 0x02 //触摸状态寄存器

#define FT_TP1_REG 0X03 //第一个触摸点数据地址
#define FT_TP2_REG 0X09 //第二个触摸点数据地址
#define FT_TP3_REG 0X0F //第三个触摸点数据地址
#define FT_TP4_REG 0X15 //第四个触摸点数据地址
#define FT_TP5_REG 0X1B //第五个触摸点数据地址

#define FT_ID_G_LIB_VERSION 0xA1  //版本
#define FT_ID_G_MODE 0xA4         // FT5206中断模式控制寄存器
#define FT_ID_G_THGROUP 0x80      //触摸有效值设置寄存器
#define FT_ID_G_PERIODACTIVE 0x88 //激活状态周期设置寄存器

#define TP_PRES_DOWN 0x80 //触屏被按下
#define TP_CATH_PRES 0x40 //有按键按下了
#define CT_MAX_TOUCH 10   //电容屏支持的点数,固定为5点

//触摸屏控制器
typedef struct {
  uint8_t (*init)(void);    //初始化触摸屏控制器
  uint8_t (*scan)(uint8_t); //扫描触摸屏.0,屏幕扫描;1,物理坐标;
                            //   void (*adjust)(void);     //触摸屏校准
  uint16_t x[CT_MAX_TOUCH]; //当前坐标
  uint16_t y
      [CT_MAX_TOUCH]; //电容屏有最多10组坐标,电阻屏则用x[0],y[0]代表:此次扫描时,触屏的坐标,用
                      // x[9],y[9]存储第一次按下时的坐标.
  uint8_t sta;        //笔的状态
                      // b15:按下1/松开0;
  // b14:0,没有按键按下;1,有按键按下.
  // b13~b10:保留
  // b9~b0:电容触摸屏按下的点数(0,表示未按下,1表示按下)
  /////////////////////触摸屏校准参数(电容屏不需要校准)//////////////////////
  //   float xfac;
  //   float yfac;
  //   short xoff;
  //   short yoff;
  //新增的参数,当触摸屏的左右上下完全颠倒时需要用到.
  // b0:0,竖屏(适合左右为X坐标,上下为Y坐标的TP)
  //   1,横屏(适合左右为Y坐标,上下为X坐标的TP)
  // b1~6:保留.
  // b7:0,电阻屏
  //   1,电容屏
  //   uint8_t touchtype;
} _m_tp_dev;

extern _m_tp_dev tp_dev; //触屏控制器在ft5206.c里面定义

uint8_t FT5206_WR_Reg(uint16_t reg, uint8_t *buf, uint8_t len);
void FT5206_RD_Reg(uint16_t reg, uint8_t *buf, uint8_t len);
uint8_t FT5206_Init(void);
uint8_t FT5206_Scan(uint8_t mode);

#endif

#ifdef __cplusplus
}

#endif
