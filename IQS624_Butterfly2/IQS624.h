#ifndef IQS624_h
#define IQS624_h

#include "Arduino.h"
#include "Wire.h"

/* Change the Prox Sensor Settings */
/* Memory Map Position 0x40 - 0x49 */
#define PXS_SETTINGS_0                      0x01
#define PXS_SETTINGS_1                      0x02
#define PXS_SETTINGS_2                      0x5A
#define PXS_SETTINGS_3                      0x18
#define PXS_SETTINGS_4                      0xD0
#define PXS_SETTINGS_5                      0x00
#define PXS_SETTINGS_6                      0xE6
#define PXS_SETTINGS_7                      0x9A
#define PXS_SETTINGS_8                      0x81
#define PXS_SETTINGS_9                      0x05

/* Change the Prox UI Settings */
/* Memory Map Position 0x50 - 0x54 */
#define PXS_UI_SETTINGS_0                   0x14
#define PXS_UI_SETTINGS_1                   0x20
#define PXS_UI_SETTINGS_2                   0x14
#define PXS_UI_SETTINGS_3                   0x20
#define PXS_UI_SETTINGS_4                   0x28

/* Change the HALL Sensor Settings */
/* Memory Map Position 0x70 - 0x7A */
#define HALL_SETTINGS_0                     0x04
#define HALL_SETTINGS_1                     0x03
#define HALL_SETTINGS_2                     0x93
#define HALL_SETTINGS_3                     0x93
#define HALL_SETTINGS_4                     0xAC
#define HALL_SETTINGS_5                     0xA1
#define HALL_SETTINGS_6                     0x0A
#define HALL_SETTINGS_7                     0x09
#define HALL_SETTINGS_8                     0x46
#define HALL_SETTINGS_9                     0x70
#define HALL_SETTINGS_10                    0xE5

/* Change the Device & PMU Settings */
/* Memory Map Position 0xD0 - 0xD7 */
#define SYSTEM_SETTINGS                     0x08
#define ACTIVE_CHS                          0x3F
#define PMU_SETTINGS                        0x03
#define REPORT_RATES_TIMINGS_0              0x10
#define REPORT_RATES_TIMINGS_1              0x64
#define REPORT_RATES_TIMINGS_2              0x0A
#define REPORT_RATES_TIMINGS_3              0x14
#define REPORT_RATES_TIMINGS_4              0x07


/* IQS624 Register Map */
/* http://www.mouser.com/ds/2/42/iqs624_datasheet-1092834.pdf */
// Device Information
#define IQS624_PRODUCT_NUMBER     0x00
#define IQS624_SOFTWARE_NUMBER    0x01
#define IQS624_HARDWARE_NUMBER    0x02

// Device Specific Data
#define IQS624_SYSTEM_FLAGS       0x10
#define IQS624_UI_FLAGS           0x11
#define IQS624_PROXIMITY_UI_FLAGS 0x12
#define IQS624_HALL_UI_FLAGS      0x14
#define IQS624_HALL_RATIO_FLAGS   0x15
#define IQS624_ALS_FLAGS          0x16

// Count Data
#define IQS624_CH0_CS_LOW         0x20
#define IQS624_CH0_CS_HIGH        0x21
#define IQS624_CH1_CS_LOW         0x22
#define IQS624_CH1_CS_HIGH        0x23
#define IQS624_CH2_CS_LOW         0x24
#define IQS624_CH2_CS_HIGH        0x25
#define IQS624_CH3_CS_LOW         0x26
#define IQS624_CH3_CS_HIGH        0x27
#define IQS624_CH4_CS_LOW         0x28
#define IQS624_CH4_CS_HIGH        0x29
#define IQS624_CH5_CS_LOW         0x2A
#define IQS624_CH5_CS_HIGH        0x2B
#define IQS624_CH0_LTA_LOW        0x30
#define IQS624_CH0_LTA_HIGH       0x31
#define IQS624_CH1_LTA_LOW        0x32
#define IQS624_CH1_LTA_HIGH       0x33

// ProxFusion Sensor Settings

#define IQS624_CH0_SETTINGS_0     0x40
#define IQS624_CH1_SETTINGS_0     0x41
#define IQS624_CH0_1_SETTINGS_1   0x42
#define IQS624_CH0_SETTINGS_2     0x43
#define IQS624_CH1_SETTINGS_2     0x44
#define IQS624_CH0_1_SETTINGS_3   0x45
#define IQS624_CH0_COMPENSATION   0x46
#define IQS624_CH1_COMPENSATION   0x47
#define IQS624_CH0_MULTIPLIERS    0x48
#define IQS624_CH1_MULTIPLIERS    0x49

#define IQS624_PCC_CH0            0x4A
#define IQS624_PCC_CH1            0x4B
#define IQS624_NP_MIRROR_CH0      0x4C
#define IQS624_NP_MIRROR_CH1      0x4D

// Touch/Proximity UI Settings
#define IQS624_CH0_PROXIMITY_THR  0x50
#define IQS624_CH0_TOUCH_THR      0x51
#define IQS624_CH1_PROXIMITY_THR  0x52
#define IQS624_CH1_TOUCH_THR      0x53
#define IQS624_UI_HALT_PERIOD     0x54

#define IQS624_METAL_UI_SETTINGS  0x60
#define IQS624_METAL_UI_FHALT     0x61
#define IQS624_METAL_UI_THR_P     0x62
#define IQS624_METAL_UI_THR_T     0x63

// Hall Sensor Settings
#define IQS624_HALL_ROT_SETTINGS  0x70
#define IQS624_HALL_SENS_SETTINGS 0x71
#define IQS624_CH2_3_HALL_ATI     0x72
#define IQS624_CH4_5_HALL_ATI     0x73
#define IQS624_CH2_3_COMP         0x74
#define IQS624_CH4_5_COMP         0x75
#define IQS624_CH2_3_MULT         0x76
#define IQS624_CH4_5_MULT         0x77
#define IQS624_HALL_RATIO         0x78
#define IQS624_SIN_CONST          0x79
#define IQS624_COS_CONST          0x7A

// Hall Wheel Output
#define IQS624_DEGREE_OUT_LSB     0x80
#define IQS624_DEGREE_OUT_MSB     0x81
#define IQS624_RATIO_OUT_LSB      0x82
#define IQS624_RATIO_OUT_MSB      0x83
#define IQS624_RATIO_NUM_LSB      0x84
#define IQS624_RATIO_NUM_MSB      0x85
#define IQS624_RATIO_DENOM_LSB    0x86
#define IQS624_RATIO_DENOM_MSB    0x87
#define IQS624_ROT_CORR_FAC_LSB   0x88
#define IQS624_ROT_CORR_FAC_MSB   0x89
#define IQS624_MAX_NUM_RAT_LSB    0x8A
#define IQS624_MAX_NUM_RAT_MSB    0x8B
#define IQS624_MAX_DENOM_RAT_LSB  0x8C
#define IQS624_MAX_DENOM_RAT_MSB  0x8D
#define IQS624_REL_ROT_ANGLE      0x8E
#define IQS624_MOV_COUNTER_TIM    0x8F

#define IQS624_HALL_SETTINGS_0    0x90
#define IQS624_HALL_SETTINGS_1    0x91
#define IQS624_PCC_CH5_CH6        0x92
#define IQS624_NP_MIRROR_CH5_CH6  0x93

#define IQS624_HALL_UI_SETTINGS_0 0xA0
#define IQS624_HALL_UI_SETTINGS_1 0xA1
#define IQS624_TEMP_UI_SETTINGS   0xC0
#define IQS624_NP_MIRROR_CH2      0xC1
#define IQS624_TEMP_CALLBR_0      0xC2
#define IQS624_TEMP_CALLBR_1      0xC3

// Device and Power Mode Settings
#define IQS624_SYSTEM_SETTINGS    0xD0
#define IQS624_ACTIVE_CHAN        0xD1
#define IQS624_PMU_SETTINGS       0xD2
#define IQS624_NMD_REPORT_RATE    0xD3
#define IQS624_LPMD_REPORT_RATE   0xD4
#define IQS624_ULPMD_REPORT_RATE  0xD5
#define IQS624_AUTOMD_TIME        0xD6

#define IQS624_GLOBAL_EVENT_MASK  0xD7
#define IQS624_DIRECT_ADDRESS     0xF0
#define IQS624_DIRECT_DATA        0xF1

#define IQS624_ADDRESS            0x44

#define HALL_SIN_STARTUP      99           //    sin(degrees/180*pi)*255
#define HALL_COS_STARTUP      235          //    cos(degrees/180*pi)*255

#define NUMBER_OF_REGISTERS 224 /* number of registers to read from IQS62x */
#define I2CBufferSize 256 /* size of I2C read buffer */

class IQS624 { // basic IQS624 block read and write
  public:
     IQS624(uint8_t inpPin); // constructor    
    
    int IQSframes; // number of reads we've done

    char writeFlag       [I2CBufferSize]; // to remember our if we wrote to this register
    char lastWrite       [I2CBufferSize]; // to remember what we wrote to this register
    char lastRead        [I2CBufferSize]; // to remember what we read from this register
    char readChanges     [I2CBufferSize]; // to log changes from previous read
    char readChangesEver [I2CBufferSize]; // to log changes from previous read BUT this one never forgets a change
    char writeChanges    [I2CBufferSize]; // to log changes from what we wrote

    char * registers; // pointer to I2C read buffer

    void I2Cscan();
    bool checkChipID();
    void checkEvents();
    void checkHallStatus();
    uint16_t readRotation();
    uint8_t readRelRotation();
    void writeByte(uint8_t address, uint8_t subAddress, uint8_t data);
    uint8_t readByte(uint8_t address, uint8_t subAddress);
    void configure(); // write configuration registers of the IQS624    
    void readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest);
    void waitForIqsReady(); // wait for IQS62x ready signal
    private:
    uint8_t _intPin;
};

#endif
