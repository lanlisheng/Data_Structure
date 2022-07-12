#ifndef DATACOLLECT_ELEMENT_HPP
#define DATACOLLECT_ELEMENT_HPP

#include "sensors.h"
#include <gui_generated/containers/DataCollect_ElementBase.hpp>

class DataCollect_Element : public DataCollect_ElementBase {
public:
  DataCollect_Element();
  virtual ~DataCollect_Element() {}

  virtual void initialize();

  /**
   * Initialize this containers widgets
   */
  void Update_ListElement(int16_t List_Order, int16_t *Acc_Data,
                          int16_t *Gyo_Data, int16_t *Mag_Data,
                          float *Eular_Data,
                          Longtitude_And_Latitude_Data_Type Lat_Data,
                          Longtitude_And_Latitude_Data_Type long_Data);

  void Init_ListElement(int16_t List_Order);

protected:
};

#endif // DATACOLLECT_ELEMENT_HPP
