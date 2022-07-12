#ifndef __SENSORS_H
#define __SENSORS_H
#ifdef __cplusplus
extern "C" {
#endif

#include "crc.h"
#include "main.h"

typedef struct Longtitude_And_Latitude_Data {
  float Seconds;
  uint8_t Degrees;
  uint8_t Minutes;
  uint8_t Hemisphere;
} Longtitude_And_Latitude_Data_Type;

/* 正点原子GPS模块的接收数据结构体 */
typedef struct Data_Record_Frame {
  float Eular_Data[3];
  int16_t Acc_Data[3];
  int16_t Gyo_Data[3];
  int16_t Mag_Data[3];
  Longtitude_And_Latitude_Data_Type Lat_Data;
  Longtitude_And_Latitude_Data_Type Long_Data;
} Data_Record_Frame_Type;

/* 华测CGI-210接收 GPGGA命令 数据的结构体 */
typedef struct CGI_Data_Record_Frame {
  Longtitude_And_Latitude_Data_Type Lat_Data;
  Longtitude_And_Latitude_Data_Type Long_Data;
} CGI_Data_Record_Frame_Type;

/* 华测CGI-210 */
extern uint8_t GPS_Status;
extern uint8_t NSC_Quantity;
extern float HDOP_Factor;
extern int16_t Altitude_Data;

extern int16_t AccRaw[3];
extern int16_t GyoRaw[3];
extern int16_t MagRaw[3];
extern float Eular[3];
extern float Pressure;
extern volatile uint8_t IMU_Data_Status;
extern volatile uint8_t GPS_Data_Status;

extern Longtitude_And_Latitude_Data_Type Longtitude_Data;
extern Longtitude_And_Latitude_Data_Type Latitude_Data;

extern uint8_t MPU_Full_Data_Flag;
extern uint8_t GPS_Full_Data_Flag;

extern uint8_t Sensors_Data_OUT[49];

extern uint8_t Data_Record_Frame_CNT;
extern Data_Record_Frame_Type Data_Record_Frames[10];

/* 华测CGI210 */
extern uint8_t GCI_Data_Record_Frame_CNT;
extern CGI_Data_Record_Frame_Type CGI_Data_Record_Frame[10];

// void CRC_IMU_Data(uint8_t *IMU_Data);
void Deal_With_IMU_Data(uint8_t *IMU_Data);
void Deal_With_GPS_Data(uint8_t *GPS_Data);
void Data_Record_Add_New_Frame(void);
/* 华测CGI210 */
void Deal_With_GPS_Data_For_CGI210(uint8_t *GPS_Data);
#ifdef __cplusplus
}
#endif
#endif // !__SENSORS_H
