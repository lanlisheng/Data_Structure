#ifdef __cplusplus
extern "C" {
#endif

#ifndef __FT5206_H
#define __FT5206_H

#include "main.h"

//����ݴ��������ӵ�оƬ����(δ����IIC����)
// IO��������
#define FT_RST(n)                                                              \
  (n ? HAL_GPIO_WritePin(GPIOI, GPIO_PIN_8, GPIO_PIN_SET)                      \
     : HAL_GPIO_WritePin(GPIOI, GPIO_PIN_8, GPIO_PIN_RESET)) // FT5206��λ����
#define FT_INT HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_7)           // FT5206������

// I2C��д����
#define FT_CMD_WR 0X70 //д����
#define FT_CMD_RD 0X71 //������

// FT5206 ���ּĴ�������
#define FT_DEVIDE_MODE 0x00    // FT5206ģʽ���ƼĴ���
#define FT_REG_NUM_FINGER 0x02 //����״̬�Ĵ���

#define FT_TP1_REG 0X03 //��һ�����������ݵ�ַ
#define FT_TP2_REG 0X09 //�ڶ������������ݵ�ַ
#define FT_TP3_REG 0X0F //���������������ݵ�ַ
#define FT_TP4_REG 0X15 //���ĸ����������ݵ�ַ
#define FT_TP5_REG 0X1B //��������������ݵ�ַ

#define FT_ID_G_LIB_VERSION 0xA1  //�汾
#define FT_ID_G_MODE 0xA4         // FT5206�ж�ģʽ���ƼĴ���
#define FT_ID_G_THGROUP 0x80      //������Чֵ���üĴ���
#define FT_ID_G_PERIODACTIVE 0x88 //����״̬�������üĴ���

#define TP_PRES_DOWN 0x80 //����������
#define TP_CATH_PRES 0x40 //�а���������
#define CT_MAX_TOUCH 10   //������֧�ֵĵ���,�̶�Ϊ5��

//������������
typedef struct {
  uint8_t (*init)(void);    //��ʼ��������������
  uint8_t (*scan)(uint8_t); //ɨ�败����.0,��Ļɨ��;1,��������;
                            //   void (*adjust)(void);     //������У׼
  uint16_t x[CT_MAX_TOUCH]; //��ǰ����
  uint16_t y
      [CT_MAX_TOUCH]; //�����������10������,����������x[0],y[0]����:�˴�ɨ��ʱ,����������,��
                      // x[9],y[9]�洢��һ�ΰ���ʱ������.
  uint8_t sta;        //�ʵ�״̬
                      // b15:����1/�ɿ�0;
  // b14:0,û�а�������;1,�а�������.
  // b13~b10:����
  // b9~b0:���ݴ��������µĵ���(0,��ʾδ����,1��ʾ����)
  /////////////////////������У׼����(����������ҪУ׼)//////////////////////
  //   float xfac;
  //   float yfac;
  //   short xoff;
  //   short yoff;
  //�����Ĳ���,��������������������ȫ�ߵ�ʱ��Ҫ�õ�.
  // b0:0,����(�ʺ�����ΪX����,����ΪY�����TP)
  //   1,����(�ʺ�����ΪY����,����ΪX�����TP)
  // b1~6:����.
  // b7:0,������
  //   1,������
  //   uint8_t touchtype;
} _m_tp_dev;

extern _m_tp_dev tp_dev; //������������ft5206.c���涨��

uint8_t FT5206_WR_Reg(uint16_t reg, uint8_t *buf, uint8_t len);
void FT5206_RD_Reg(uint16_t reg, uint8_t *buf, uint8_t len);
uint8_t FT5206_Init(void);
uint8_t FT5206_Scan(uint8_t mode);

#endif

#ifdef __cplusplus
}

#endif
