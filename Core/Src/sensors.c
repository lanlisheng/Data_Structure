#include "sensors.h"
#include "main.h"
#include "string.h"
#include "usart.h"

typedef enum {
  kItemID = 0x90,       /* user programed ID    size: 1 */
  kItemIPAdress = 0x92, /* ip address           size: 4 */
  kItemAccRaw = 0xA0,   /* raw acc              size: 3x2 */
  kItemAccRawFiltered = 0xA1,
  kItemAccDynamic = 0xA2,
  kItemGyoRaw = 0xB0, /* raw gyro             size: 3x2 */
  kItemGyoRawFiltered = 0xB1,
  kItemMagRaw = 0xC0, /* raw mag              size: 3x2 */
  kItemMagRawFiltered = 0xC1,
  kItemAtdE = 0xD0, /* eular angle          size:3x2 */
  kItemAtdQ = 0xD1, /* att q,               size:4x4 */
  kItemTemp = 0xE0,
  kItemPressure = 0xF0, /* pressure             size:1x4 */
  kItemEnd = 0xFF,
} ItemID_t;

/* IMU Datas */
int16_t AccRaw[3];
int16_t GyoRaw[3];
int16_t MagRaw[3];
float Eular[3];
float Pressure;

/* IMU and GPS data status */
volatile uint8_t IMU_Data_Status = 0;
volatile uint8_t GPS_Data_Status = 0;

/* GPS Datas */
Longtitude_And_Latitude_Data_Type Longtitude_Data;
Longtitude_And_Latitude_Data_Type Latitude_Data;

/* Received full sensor data flag */
uint8_t MPU_Full_Data_Flag = 0;
uint8_t GPS_Full_Data_Flag = 0;

/* Send out sensor data */
uint8_t Sensors_Data_OUT[49] = {0};

/* Data records */
uint8_t Data_Record_Frame_CNT = 0;
Data_Record_Frame_Type Data_Record_Frames[10] = {{{0},
                                                  {0},
                                                  {0},
                                                  {0.0},
                                                  {
                                                      0,
                                                      0,
                                                      0.0,
                                                      0x2D,
                                                  },
                                                  {
                                                      0,
                                                      0,
                                                      0.0,
                                                      0x2D,
                                                  }}};

/* GCI210 Data record */
uint8_t GCI_Data_Record_Frame_CNT = 0;
CGI_Data_Record_Frame_Type CGI_Data_Record_Frame[10] = {{{
                                                             0,
                                                             0,
                                                             0.0,
                                                             0x2D,
                                                         },
                                                         {
                                                             0,
                                                             0,
                                                             0.0,
                                                             0x2D,
                                                         }}};
// void CRC_IMU_Data(uint8_t *IMU_Data)
// {
//     uint16_t Payload_Len;
//     uint16_t IMU_CRC = 0;
//     Payload_Len = IMU_Data[2] + (IMU_Data[3] << 8);
//     IMU_CRC = HAL_CRC_Accumulate(&hcrc, IMU_Data, 4);
//     IMU_CRC = HAL_CRC_Accumulate(&hcrc, IMU_Data, Payload_Len);
// }

void Deal_With_IMU_Data(uint8_t *IMU_Data) {

  int i = 0;
  i += 6; // moving right 5bit to 0x90

  // Acc value
  if (IMU_Data[i + 2] == kItemAccRaw) {
    AccRaw[0] = (int16_t)(IMU_Data[i + 3] + (IMU_Data[i + 4] << 8));
    AccRaw[1] = (int16_t)(IMU_Data[i + 5] + (IMU_Data[i + 6] << 8));
    AccRaw[2] = (int16_t)(IMU_Data[i + 7] + (IMU_Data[i + 8] << 8));
    if (MPU_Full_Data_Flag == 0) {
      Sensors_Data_OUT[2] = IMU_Data[i + 4];
      Sensors_Data_OUT[3] = IMU_Data[i + 3];
      Sensors_Data_OUT[4] = IMU_Data[i + 6];
      Sensors_Data_OUT[5] = IMU_Data[i + 5];
      Sensors_Data_OUT[6] = IMU_Data[i + 8];
      Sensors_Data_OUT[7] = IMU_Data[i + 7];
    }
  }
  // Gyro value
  if (IMU_Data[i + 9] == kItemGyoRaw) {
    GyoRaw[0] = (int16_t)(IMU_Data[i + 10] + (IMU_Data[i + 11] << 8));
    GyoRaw[1] = (int16_t)(IMU_Data[i + 12] + (IMU_Data[i + 13] << 8));
    GyoRaw[2] = (int16_t)(IMU_Data[i + 14] + (IMU_Data[i + 15] << 8));
    if (MPU_Full_Data_Flag == 0) {
      Sensors_Data_OUT[8] = IMU_Data[i + 11];
      Sensors_Data_OUT[9] = IMU_Data[i + 10];
      Sensors_Data_OUT[10] = IMU_Data[i + 13];
      Sensors_Data_OUT[11] = IMU_Data[i + 12];
      Sensors_Data_OUT[12] = IMU_Data[i + 15];
      Sensors_Data_OUT[13] = IMU_Data[i + 14];
    }
  }
  // Mag value
  if (IMU_Data[i + 16] == kItemMagRaw) {
    MagRaw[0] = (int16_t)(IMU_Data[i + 17] + (IMU_Data[i + 18] << 8));
    MagRaw[1] = (int16_t)(IMU_Data[i + 19] + (IMU_Data[i + 20] << 8));
    MagRaw[2] = (int16_t)(IMU_Data[i + 21] + (IMU_Data[i + 22] << 8));
    if (MPU_Full_Data_Flag == 0) {
      Sensors_Data_OUT[14] = IMU_Data[i + 18];
      Sensors_Data_OUT[15] = IMU_Data[i + 17];
      Sensors_Data_OUT[16] = IMU_Data[i + 20];
      Sensors_Data_OUT[17] = IMU_Data[i + 19];
      Sensors_Data_OUT[18] = IMU_Data[i + 22];
      Sensors_Data_OUT[19] = IMU_Data[i + 21];
    }
  }
  // ATD E
  if (IMU_Data[i + 23] == kItemAtdE) {
    Eular[0] =
        ((float)(int16_t)(IMU_Data[i + 24] + (IMU_Data[i + 25] << 8))) / 100;
    Eular[1] =
        ((float)(int16_t)(IMU_Data[i + 26] + (IMU_Data[i + 27] << 8))) / 100;
    Eular[2] =
        ((float)(int16_t)(IMU_Data[i + 28] + (IMU_Data[i + 29] << 8))) / 10;
    if (MPU_Full_Data_Flag == 0) {
      memcpy(Sensors_Data_OUT + 20, &Eular[0], 12);
    }
  }
  // Pressure value
  if (IMU_Data[i + 30] == kItemPressure) {
    Pressure =
        (float)(int32_t)(IMU_Data[i + 31] + (IMU_Data[i + 32] << 8) +
                         (IMU_Data[i + 33] << 16) + (IMU_Data[i + 34] << 24));
  }

  MPU_Full_Data_Flag = 1;
  IMU_Data_Status = 1;
}

/* Deal with GPS data frame */
void Deal_With_GPS_Data(uint8_t *GPS_Data) {

  if ((GPS_Data[3] == 'R') && (GPS_Data[4] == 'M') && (GPS_Data[5] == 'C')) {
    int i = 0;
    i += 19; // Movind right 5bits to first comma

    Latitude_Data.Degrees =
        (GPS_Data[i + 1] - 48) * 10 + (GPS_Data[i + 2] - 48);
    Latitude_Data.Minutes =
        (GPS_Data[i + 3] - 48) * 10 + (GPS_Data[i + 4] - 48);
    Latitude_Data.Seconds =
        (float)(((GPS_Data[i + 6] - 48) * 0.1 + (GPS_Data[i + 7] - 48) * 0.01 +
                 (GPS_Data[i + 8] - 48) * 0.001 +
                 (GPS_Data[i + 9] - 48) * 0.0001) *
                60.0);
    Latitude_Data.Hemisphere = GPS_Data[i + 11];

    Longtitude_Data.Degrees = (GPS_Data[i + 13] - 48) * 100 +
                              (GPS_Data[i + 14] - 48) * 10 +
                              (GPS_Data[i + 15] - 48);
    Longtitude_Data.Minutes =
        (GPS_Data[i + 16] - 48) * 10 + (GPS_Data[i + 17] - 48);
    Longtitude_Data.Seconds = (float)(((GPS_Data[i + 19] - 48) * 0.1 +
                                       (GPS_Data[i + 20] - 48) * 0.01 +
                                       (GPS_Data[i + 21] - 48) * 0.001 +
                                       (GPS_Data[i + 22] - 48) * 0.0001) *
                                      60);
    Longtitude_Data.Hemisphere = GPS_Data[i + 24];

    Sensors_Data_OUT[32] = Longtitude_Data.Degrees;
    Sensors_Data_OUT[33] = Longtitude_Data.Minutes;
    memcpy(Sensors_Data_OUT + 34, &Longtitude_Data.Seconds, 4);
    Sensors_Data_OUT[38] = Longtitude_Data.Hemisphere;

    Sensors_Data_OUT[39] = Latitude_Data.Degrees;
    Sensors_Data_OUT[40] = Latitude_Data.Minutes;
    memcpy(Sensors_Data_OUT + 41, &Latitude_Data.Seconds, 4);
    Sensors_Data_OUT[45] = Latitude_Data.Hemisphere;

    GPS_Full_Data_Flag = 1;
    GPS_Data_Status = 1;
  }
}

/* 华测 CGI-210串口数据接收 */
void Deal_With_GPS_Data_For_CGI210(uint8_t *GPS_Data) {
  if ((GPS_Data[3] == 'G') && (GPS_Data[4] == 'G') && (GPS_Data[5] == 'A')) {
    int i = 0;
    i += 16; // Movind right 16bits to first comma
    /* Latitude_Data 纬度 */
    Latitude_Data.Degrees =
        (GPS_Data[i + 1] - 48) * 10 + (GPS_Data[i + 2] - 48);
    Latitude_Data.Minutes =
        (GPS_Data[i + 3] - 48) * 10 + (GPS_Data[i + 4] - 48);

    Latitude_Data.Seconds =
        (float)(((GPS_Data[i + 6] - 48) * 0.1 + (GPS_Data[i + 7] - 48) * 0.01 +
                 (GPS_Data[i + 8] - 48) * 0.001 +
                 (GPS_Data[i + 9] - 48) * 0.0001) *
                60.0);
    Latitude_Data.Hemisphere = GPS_Data[i + 13];

    /* Longtitude_Data 经度 */
    Longtitude_Data.Degrees = (GPS_Data[i + 15] - 48) * 100 +
                              (GPS_Data[i + 16] - 48) * 10 +
                              (GPS_Data[i + 17] - 48);
    Longtitude_Data.Minutes =
        (GPS_Data[i + 18] - 48) * 10 + (GPS_Data[i + 19] - 48);

    Longtitude_Data.Seconds = (float)(((GPS_Data[i + 21] - 48) * 0.1 +
                                       (GPS_Data[i + 22] - 48) * 0.01 +
                                       (GPS_Data[i + 23] - 48) * 0.001 +
                                       (GPS_Data[i + 24] - 48) * 0.0001) *
                                      60.0);
    Longtitude_Data.Hemisphere = GPS_Data[i + 28];

    /* CGI GPS Status */
  }
}

/* Add new frame record */
void Data_Record_Add_New_Frame(void) {
  CGI_Data_Record_Frame_Type Data_Frame;

  // for (uint8_t i = 0; i < 3; i++) {
  //   Data_Frame.Acc_Data[i] = AccRaw[i];
  //   Data_Frame.Gyo_Data[i] = GyoRaw[i];
  //   Data_Frame.Mag_Data[i] = MagRaw[i];
  //   Data_Frame.Eular_Data[i] = Eular[i];
  // }
  Data_Frame.Lat_Data = Latitude_Data;
  Data_Frame.Long_Data = Longtitude_Data;

  /* A simple FIFO algorithm */
  if (GCI_Data_Record_Frame_CNT <= 9) {
    CGI_Data_Record_Frame[GCI_Data_Record_Frame_CNT] = Data_Frame;
    GCI_Data_Record_Frame_CNT++;
  } else {
    for (uint8_t i = 0; i < 9; i++) {
      CGI_Data_Record_Frame[i] = CGI_Data_Record_Frame[i + 1];
    }
    CGI_Data_Record_Frame[9] = Data_Frame;
  }
}
