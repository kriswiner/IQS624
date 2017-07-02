#include "IQS624.h"
#include "Wire.h"

IQS624::IQS624(uint8_t intPin)
{
    pinMode(intPin, INPUT);
  _intPin = intPin;
}

#define IQS624_ADDRESS 0x44

void IQS624::configure() {

/* Change the Prox Sensor Settings */
/* Memory Map Position 0x40 - 0x49 */
  writeByte( IQS624_ADDRESS, 0x40,  PXS_SETTINGS_0     );
  writeByte( IQS624_ADDRESS, 0x41,  PXS_SETTINGS_1     );
  writeByte( IQS624_ADDRESS, 0x42,  PXS_SETTINGS_2     );      
  writeByte( IQS624_ADDRESS, 0x43,  PXS_SETTINGS_3     );
  writeByte( IQS624_ADDRESS, 0x44,  PXS_SETTINGS_4     );
  writeByte( IQS624_ADDRESS, 0x45,  PXS_SETTINGS_5     );
  writeByte( IQS624_ADDRESS, 0x46,  PXS_SETTINGS_6     );     
  writeByte( IQS624_ADDRESS, 0x47,  PXS_SETTINGS_7     );
  writeByte( IQS624_ADDRESS, 0x48,  PXS_SETTINGS_8     );
  writeByte( IQS624_ADDRESS, 0x49,  PXS_SETTINGS_9     );     

/* Change the Prox UI Settings */
/* Memory Map Position 0x50 - 0x54 */
  writeByte( IQS624_ADDRESS, 0x50,  PXS_UI_SETTINGS_0  );
  writeByte( IQS624_ADDRESS, 0x51,  PXS_UI_SETTINGS_1  );
  writeByte( IQS624_ADDRESS, 0x52,  PXS_UI_SETTINGS_2  );
  writeByte( IQS624_ADDRESS, 0x53,  PXS_UI_SETTINGS_3  );
  writeByte( IQS624_ADDRESS, 0x54,  PXS_UI_SETTINGS_4  );

/* Change the HALL Sensor Settings */
/* Memory Map Position 0x70 - 0x7A */
  writeByte( IQS624_ADDRESS, 0x70,  HALL_SETTINGS_0    );
  writeByte( IQS624_ADDRESS, 0x71,  HALL_SETTINGS_1    );
  writeByte( IQS624_ADDRESS, 0x72,  HALL_SETTINGS_2    );
  writeByte( IQS624_ADDRESS, 0x73,  HALL_SETTINGS_3    );
  writeByte( IQS624_ADDRESS, 0x74,  HALL_SETTINGS_4    );
  writeByte( IQS624_ADDRESS, 0x75,  HALL_SETTINGS_5    );
  writeByte( IQS624_ADDRESS, 0x76,  HALL_SETTINGS_6    );
  writeByte( IQS624_ADDRESS, 0x77,  HALL_SETTINGS_7    );
  writeByte( IQS624_ADDRESS, 0x78,  HALL_SETTINGS_8    );
  writeByte( IQS624_ADDRESS, 0x79,  HALL_SETTINGS_9    );
  writeByte( IQS624_ADDRESS, 0x7a,  HALL_SETTINGS_10   );           

/* Change the Device & PMU Settings */
/* Memory Map Position 0xD0 - 0xD7 */
  writeByte( IQS624_ADDRESS, 0xd0,  SYSTEM_SETTINGS        );
  writeByte( IQS624_ADDRESS, 0xd1,  ACTIVE_CHS             );            
  writeByte( IQS624_ADDRESS, 0xd2,  PMU_SETTINGS           );
  writeByte( IQS624_ADDRESS, 0xd3,  REPORT_RATES_TIMINGS_0 );    
  writeByte( IQS624_ADDRESS, 0xd4,  REPORT_RATES_TIMINGS_1 );
  writeByte( IQS624_ADDRESS, 0xd5,  REPORT_RATES_TIMINGS_2 );
  writeByte( IQS624_ADDRESS, 0xd6,  REPORT_RATES_TIMINGS_3 );
  // NO 0xd7 in data sheet....    writeByte( 0xd7,  REPORT_RATES_TIMINGS_4 );

 /*  //reset ATI
   uint8_t c = readByte( IQS624_ADDRESS, IQS624_SYSTEM_FLAGS);
   while(c & 0x04){} // wait for ATI busy flag to clear
   writeByte( IQS624_ADDRESS, 0xF0,  0xD5 );
   delay(100);
   writeByte( IQS624_ADDRESS, 0xF0,  0x01 );
*/
   // Check device status
   uint8_t eventStatus = readByte(IQS624_ADDRESS, IQS624_SYSTEM_FLAGS);
   if(eventStatus & 0x40){
   Serial.println("Ready active HIGH set!");
   }
   uint8_t powerModeStatus = (eventStatus & 0x18) >> 3;
   if(powerModeStatus == 0) Serial.println("Device in normal power mode!");
   if(powerModeStatus == 1) Serial.println("Device in low power mode!");
   if(powerModeStatus == 2) Serial.println("Device in ultra-low power mode!");
   if(powerModeStatus == 3) Serial.println("Device in halt power mode!");

}

 bool IQS624::checkChipID()
 {
  // Read the Device Product Number register of the IQS624, this is a good test of communication
  byte c = readByte(IQS624_ADDRESS, IQS624_PRODUCT_NUMBER);   
  Serial.print("IQS624 Product Number is 0x"); Serial.print(c, HEX); Serial.println(" It should be 0x43");

  // Read the Device Product Number register of the IQS624, this is a good test of communication
  byte d = readByte(IQS624_ADDRESS, IQS624_SOFTWARE_NUMBER);   
  Serial.print("IQS624 Software Number is 0x"); Serial.print(d, HEX); Serial.println(" It should be 0x02"); 

  // Read the Device Product Number register of the IQS624, this is a good test of communication
  byte e = readByte(IQS624_ADDRESS, IQS624_HARDWARE_NUMBER);   
  Serial.print("IQS624 Hardware Number is "); Serial.print((int) e); Serial.println(" It should be 130");

   return (c == 0x43);
  }

void IQS624::checkEvents()
{
  // check for events
 byte eventStatus = readByte(IQS624_ADDRESS, IQS624_SYSTEM_FLAGS);
 if(eventStatus & 0x80)
 {
  Serial.println("Device reset has occured and needs to be acknowledged!");
  // acknowledge and clear reset
  byte temp = readByte(IQS624_ADDRESS, IQS624_SYSTEM_SETTINGS);
  writeByte(IQS624_ADDRESS, IQS624_SYSTEM_SETTINGS, temp | 0x40); // acknowledge reset event
 }
//  if(eventStatus & 0x02){
//  Serial.println("An event has occured and should be handled!");
// }
}


void IQS624::checkHallStatus()
{
   // check Hall status
    byte hallStatus = readByte(IQS624_ADDRESS, IQS624_HALL_UI_FLAGS);

      if(hallStatus & 0x80) 
      {
        Serial.print("Wheel movement detected");
        if(hallStatus & 0x40) Serial.println(" in positive direction");
        else Serial.println(" in negative direction");
      }
      
}

uint16_t IQS624::readRotation()
{
    uint8_t degrees[2] = {0, 0};
    waitForIqsReady();
    readBytes(IQS624_ADDRESS, IQS624_DEGREE_OUT_LSB, 2, &degrees[0]);
    uint16_t temp = (uint16_t) ( ((uint16_t) degrees[1] << 8) | degrees[0]);
    return temp;
}

  
   
uint8_t IQS624::readRelRotation()
{
  waitForIqsReady();
  uint8_t temp = readByte(IQS624_ADDRESS, IQS624_REL_ROT_ANGLE);
  return temp;
}


// wait for IQS624 to provide a ready signal (low) on IQS624 RDY pin
void IQS624::waitForIqsReady()
{
    uint32_t timeout=0;
    while (1) {
        if(digitalRead(_intPin) == 1) break;
        if (timeout++ > 1000000) goto fatal_error;
    }
    timeout=0;
    while (1) {
        if(digitalRead(_intPin) ==0 ) break;
        if (timeout++ > 1000000) goto fatal_error;
    }
    return;; 
fatal_error:
    Serial.println("Fatal Error: IQS624 ready pin is not toggling");
}


void IQS624::I2Cscan()
{
// scan for i2c devices
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    error = Wire.transfer(address, NULL, 0, NULL, 0);

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknown error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n"); 
}

// I2C read/write functions for the IQS624 Hall sensor

        void IQS624::writeByte(uint8_t address, uint8_t subAddress, uint8_t data) {
        uint8_t temp[2];
        temp[0] = subAddress;
        temp[1] = data;
        Wire.transfer(address, &temp[0], 2, NULL, 0); 
        }

        uint8_t IQS624::readByte(uint8_t address, uint8_t subAddress) {
        uint8_t temp[1];
        Wire.transfer(address, &subAddress, 1, &temp[0], 1);
        return temp[0];
        }

        void IQS624::readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest) {
        Wire.transfer(address, &subAddress, 1, dest, count); 
        }

