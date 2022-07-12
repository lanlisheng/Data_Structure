#include <gui/containers/DataCollect_Element.hpp>

DataCollect_Element::DataCollect_Element() {}

void DataCollect_Element::initialize() {
  DataCollect_ElementBase::initialize();
}

/**
 * Initialize this containers widgets
 */
void DataCollect_Element::Update_ListElement(
    int16_t List_Order, int16_t *Acc_Data, int16_t *Gyo_Data, int16_t *Mag_Data,
    float *Eular_Data, Longtitude_And_Latitude_Data_Type Lat_Data,
    Longtitude_And_Latitude_Data_Type long_Data) {
  if (List_Order < 10) {
    Unicode::snprintf(DataRecord_OrderBuffer, DATARECORD_ORDER_SIZE, "0%i",
                      List_Order);
    DataRecord_Order.invalidate();
    DataRecord_Order.resizeToCurrentTextWithAlignment();
  } else {
    Unicode::snprintf(DataRecord_OrderBuffer, DATARECORD_ORDER_SIZE, "%i",
                      List_Order);
    DataRecord_Order.invalidate();
    DataRecord_Order.resizeToCurrentTextWithAlignment();
  }
  //   Unicode::snprintf(Acceleration_XBuffer, ACCELERATION_X_SIZE, "%i",
  //                     Acc_Data[0]);
  //   Acceleration_X.invalidate();
  //   Acceleration_X.resizeToCurrentTextWithAlignment();
  //   Unicode::snprintf(Acceleration_YBuffer, ACCELERATION_Y_SIZE, "%i",
  //                     Acc_Data[1]);
  //   Acceleration_Y.invalidate();
  //   Acceleration_Y.resizeToCurrentTextWithAlignment();
  //   Unicode::snprintf(Acceleration_ZBuffer, ACCELERATION_Z_SIZE, "%i",
  //                     Acc_Data[2]);
  //   Acceleration_Z.invalidate();
  //   Acceleration_Z.resizeToCurrentTextWithAlignment();
  //   Unicode::snprintf(AngularRate_XBuffer, ANGULARRATE_X_SIZE, "%i",
  //   Gyo_Data[0]); AngularRate_X.invalidate();
  //   AngularRate_X.resizeToCurrentTextWithAlignment();
  //   Unicode::snprintf(AngularRate_YBuffer, ANGULARRATE_Y_SIZE, "%i",
  //   Gyo_Data[1]); AngularRate_Y.invalidate();
  //   AngularRate_Y.resizeToCurrentTextWithAlignment();
  //   Unicode::snprintf(AngularRate_ZBuffer, ANGULARRATE_Z_SIZE, "%i",
  //   Gyo_Data[2]); AngularRate_Z.invalidate();
  //   AngularRate_Z.resizeToCurrentTextWithAlignment();
  //   Unicode::snprintf(Magnetic_XBuffer, MAGNETIC_X_SIZE, "%i", Mag_Data[0]);
  //   Magnetic_X.invalidate();
  //   Magnetic_X.resizeToCurrentTextWithAlignment();
  //   Unicode::snprintf(Magnetic_YBuffer, MAGNETIC_Y_SIZE, "%i", Mag_Data[1]);
  //   Magnetic_Y.invalidate();
  //   Magnetic_Y.resizeToCurrentTextWithAlignment();
  //   Unicode::snprintf(Magnetic_ZBuffer, MAGNETIC_Z_SIZE, "%i", Mag_Data[2]);
  //   Magnetic_Z.invalidate();
  //   Magnetic_Z.resizeToCurrentTextWithAlignment();
  //   Unicode::snprintfFloat(EularAngle_XBuffer, EULARANGLE_X_SIZE, "%3.2f",
  //                          Eular_Data[0]);
  //   EularAngle_X.invalidate();
  //   EularAngle_X.resizeToCurrentTextWithAlignment();
  //   Unicode::snprintfFloat(EularAngle_YBuffer, EULARANGLE_Y_SIZE, "%3.2f",
  //                          Eular_Data[1]);
  //   EularAngle_Y.invalidate();
  //   EularAngle_Y.resizeToCurrentTextWithAlignment();
  //   Unicode::snprintfFloat(EularAngle_ZBuffer, EULARANGLE_Z_SIZE, "%3.2f",
  //                          Eular_Data[2]);
  //   EularAngle_Z.invalidate();
  //   EularAngle_Z.resizeToCurrentTextWithAlignment();
  Unicode::snprintf(Lattitude_MinutesBuffer1, LATTITUDE_MINUTESBUFFER1_SIZE,
                    "%i", Lat_Data.Degrees);
  Unicode::snprintf(Lattitude_MinutesBuffer2, LATTITUDE_MINUTESBUFFER2_SIZE,
                    "%i", Lat_Data.Minutes);
  Lattitude_Minutes.invalidate();
  Lattitude_Minutes.resizeToCurrentTextWithAlignment();
  Unicode::snprintfFloat(Lattitude_SecondsBuffer1,
                         LATTITUDE_SECONDSBUFFER1_SIZE, "%2.2f",
                         Lat_Data.Seconds);
  Unicode::snprintf(Lattitude_SecondsBuffer2, LATTITUDE_SECONDSBUFFER2_SIZE,
                    "%c", Lat_Data.Hemisphere);
  Lattitude_Seconds.invalidate();
  Lattitude_Seconds.resizeToCurrentTextWithAlignment();
  Unicode::snprintf(Longtitude_MinutesBuffer1, LONGTITUDE_MINUTESBUFFER1_SIZE,
                    "%i", long_Data.Degrees);
  Unicode::snprintf(Longtitude_MinutesBuffer2, LONGTITUDE_MINUTESBUFFER2_SIZE,
                    "%i", long_Data.Minutes);
  Longtitude_Minutes.invalidate();
  Longtitude_Minutes.resizeToCurrentTextWithAlignment();
  Unicode::snprintfFloat(Longtitude_SecondsBuffer1,
                         LONGTITUDE_SECONDSBUFFER1_SIZE, "%2.2f",
                         long_Data.Seconds);
  Unicode::snprintf(Longtitude_SecondsBuffer2, LONGTITUDE_SECONDSBUFFER2_SIZE,
                    "%c", long_Data.Hemisphere);
  Longtitude_Seconds.invalidate();
  Longtitude_Seconds.resizeToCurrentTextWithAlignment();
}

/* Initialize List elements */
void DataCollect_Element::Init_ListElement(int16_t List_Order) {
  int16_t Acc_Data[3] = {0};
  int16_t Gyo_Data[3] = {0};
  int16_t Mag_Data[3] = {0};
  float Eular_Data[3] = {0.0};
  Longtitude_And_Latitude_Data_Type Lat_Data, Long_Data;

  Lat_Data.Degrees = 0;
  Lat_Data.Minutes = 0;
  Lat_Data.Seconds = 0.0;
  Lat_Data.Hemisphere = 0x2D;
  Long_Data.Degrees = 0;
  Long_Data.Minutes = 0;
  Long_Data.Seconds = 0.0;
  Long_Data.Hemisphere = 0x2D;

  Update_ListElement(List_Order, Acc_Data, Gyo_Data, Mag_Data, Eular_Data,
                     Lat_Data, Long_Data);
}
