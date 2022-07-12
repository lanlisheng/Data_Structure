#include "sensors.h"
#include <gui/data_collector_screen/Data_CollectorView.hpp>

Data_CollectorView::Data_CollectorView() {}

void Data_CollectorView::setupScreen() {
  Data_CollectorViewBase::setupScreen();

  // for (uint8_t i = 0; i < numberOfListElements; i++)
  // {
  //     listElements[i].Init_ListElement(i + 1);
  //     DataList.add(listElements[i]);
  // }

  for (uint8_t i = 0; i < numberOfListElements; i++) {
    listElements[i].Update_ListElement(
        i + 1, Data_Record_Frames[i].Acc_Data, Data_Record_Frames[i].Gyo_Data,
        Data_Record_Frames[i].Mag_Data, Data_Record_Frames[i].Eular_Data,
        CGI_Data_Record_Frame[i].Lat_Data, CGI_Data_Record_Frame[i].Long_Data);
    DataList.add(listElements[i]);
  }
}

void Data_CollectorView::tearDownScreen() {
  Data_CollectorViewBase::tearDownScreen();
}

void Data_CollectorView::handleTickEvent() {
  // Execute_DataRecordButton_Event();

  for (uint8_t i = 0; i < numberOfListElements; i++) {
    listElements[i].Update_ListElement(
        i + 1, Data_Record_Frames[i].Acc_Data, Data_Record_Frames[i].Gyo_Data,
        Data_Record_Frames[i].Mag_Data, Data_Record_Frames[i].Eular_Data,
        CGI_Data_Record_Frame[i].Lat_Data, CGI_Data_Record_Frame[i].Long_Data);
  }
  Data_CollectorView::handleKeyEvent(0);
}
