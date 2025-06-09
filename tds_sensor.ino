#include <DFRobot_BC20AT.h>
#include <DFRobot_BC20_Gravity.h>
#include <DFRobot_queue.h>

#include <EEPROM.h>
#include <CQRobotTDS.h>

#define TdsSensorPin A1  // Define TDS sensor pin
CQRobot_TDS tdsSensor;

float temperature = 25.0, tdsValue = 0;

void setup()
{
    Serial.begin(115200);
    tdsSensor.SetPin(TdsSensorPin);
    tdsSensor.SetAref(5.0);      // Reference voltage on ADC (Default: 5.0V on Arduino UNO)
    tdsSensor.SetAdcRange(1024); // 10-bit ADC (1024) or 12-bit ADC (4096)
    tdsSensor.Begin();           // Initialize the TDS sensor
}

void loop()
{
    tdsSensor.SetTemperature(temperature);  // Apply temperature compensation
    tdsSensor.Update();  // Read and calculate TDS
    tdsValue = tdsSensor.GetTdsValue();  // Get the calculated TDS value

    Serial.print(tdsValue, 0);
    Serial.println(" ppm");
    delay(1000);
}
