/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef DATACOLLECT_ELEMENTBASE_HPP
#define DATACOLLECT_ELEMENTBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class DataCollect_ElementBase : public touchgfx::Container
{
public:
    DataCollect_ElementBase();
    virtual ~DataCollect_ElementBase() {}
    virtual void initialize();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Image BG_Image;
    touchgfx::TextAreaWithOneWildcard DataRecord_Order;
    touchgfx::TextAreaWithTwoWildcards Longtitude_Seconds;
    touchgfx::TextAreaWithTwoWildcards Longtitude_Minutes;
    touchgfx::TextAreaWithTwoWildcards Lattitude_Minutes;
    touchgfx::TextAreaWithTwoWildcards Lattitude_Seconds;
    touchgfx::TextAreaWithOneWildcard EularAngle_Z;
    touchgfx::TextAreaWithOneWildcard EularAngle_Y;
    touchgfx::TextAreaWithOneWildcard EularAngle_X;
    touchgfx::TextAreaWithOneWildcard Magnetic_Z;
    touchgfx::TextAreaWithOneWildcard Magnetic_Y;
    touchgfx::TextAreaWithOneWildcard Magnetic_X;
    touchgfx::TextAreaWithOneWildcard AngularRate_Z;
    touchgfx::TextAreaWithOneWildcard AngularRate_Y;
    touchgfx::TextAreaWithOneWildcard AngularRate_X;
    touchgfx::TextAreaWithOneWildcard Acceleration_Z;
    touchgfx::TextAreaWithOneWildcard Acceleration_Y;
    touchgfx::TextAreaWithOneWildcard Acceleration_X;

    /*
     * Wildcard Buffers
     */
    static const uint16_t DATARECORD_ORDER_SIZE = 10;
    touchgfx::Unicode::UnicodeChar DataRecord_OrderBuffer[DATARECORD_ORDER_SIZE];
    static const uint16_t LONGTITUDE_SECONDSBUFFER1_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Longtitude_SecondsBuffer1[LONGTITUDE_SECONDSBUFFER1_SIZE];
    static const uint16_t LONGTITUDE_SECONDSBUFFER2_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Longtitude_SecondsBuffer2[LONGTITUDE_SECONDSBUFFER2_SIZE];
    static const uint16_t LONGTITUDE_MINUTESBUFFER1_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Longtitude_MinutesBuffer1[LONGTITUDE_MINUTESBUFFER1_SIZE];
    static const uint16_t LONGTITUDE_MINUTESBUFFER2_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Longtitude_MinutesBuffer2[LONGTITUDE_MINUTESBUFFER2_SIZE];
    static const uint16_t LATTITUDE_MINUTESBUFFER1_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Lattitude_MinutesBuffer1[LATTITUDE_MINUTESBUFFER1_SIZE];
    static const uint16_t LATTITUDE_MINUTESBUFFER2_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Lattitude_MinutesBuffer2[LATTITUDE_MINUTESBUFFER2_SIZE];
    static const uint16_t LATTITUDE_SECONDSBUFFER1_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Lattitude_SecondsBuffer1[LATTITUDE_SECONDSBUFFER1_SIZE];
    static const uint16_t LATTITUDE_SECONDSBUFFER2_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Lattitude_SecondsBuffer2[LATTITUDE_SECONDSBUFFER2_SIZE];
    static const uint16_t EULARANGLE_Z_SIZE = 10;
    touchgfx::Unicode::UnicodeChar EularAngle_ZBuffer[EULARANGLE_Z_SIZE];
    static const uint16_t EULARANGLE_Y_SIZE = 10;
    touchgfx::Unicode::UnicodeChar EularAngle_YBuffer[EULARANGLE_Y_SIZE];
    static const uint16_t EULARANGLE_X_SIZE = 10;
    touchgfx::Unicode::UnicodeChar EularAngle_XBuffer[EULARANGLE_X_SIZE];
    static const uint16_t MAGNETIC_Z_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Magnetic_ZBuffer[MAGNETIC_Z_SIZE];
    static const uint16_t MAGNETIC_Y_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Magnetic_YBuffer[MAGNETIC_Y_SIZE];
    static const uint16_t MAGNETIC_X_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Magnetic_XBuffer[MAGNETIC_X_SIZE];
    static const uint16_t ANGULARRATE_Z_SIZE = 10;
    touchgfx::Unicode::UnicodeChar AngularRate_ZBuffer[ANGULARRATE_Z_SIZE];
    static const uint16_t ANGULARRATE_Y_SIZE = 10;
    touchgfx::Unicode::UnicodeChar AngularRate_YBuffer[ANGULARRATE_Y_SIZE];
    static const uint16_t ANGULARRATE_X_SIZE = 10;
    touchgfx::Unicode::UnicodeChar AngularRate_XBuffer[ANGULARRATE_X_SIZE];
    static const uint16_t ACCELERATION_Z_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Acceleration_ZBuffer[ACCELERATION_Z_SIZE];
    static const uint16_t ACCELERATION_Y_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Acceleration_YBuffer[ACCELERATION_Y_SIZE];
    static const uint16_t ACCELERATION_X_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Acceleration_XBuffer[ACCELERATION_X_SIZE];

private:

};

#endif // DATACOLLECT_ELEMENTBASE_HPP
