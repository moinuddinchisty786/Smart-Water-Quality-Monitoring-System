#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>
#include <Adafruit_Thermal.h>

// === Pin Definitions ===
#define TDS_SENSOR A0
#define PH_SENSOR A1
#define DO_SENSOR A2
#define TEMP_SENSOR 7  // DS18B20 DATA pin connected to D7

// === Thermal Printer Setup ===
#define PRINTER_RX_PIN 1  // Arduino transmits to printer on pin 5
#define PRINTER_TX_PIN 0  // Arduino receives from printer on pin 6 (not used in this example)
SoftwareSerial printerSerial(PRINTER_TX_PIN, PRINTER_RX_PIN);
Adafruit_Thermal printer(&printerSerial);

// === DS18B20 Temperature Sensor Setup ===
OneWire oneWire(TEMP_SENSOR);
DallasTemperature sensors(&oneWire);

// === Global Variables ===
float temperature = 25.0; // default temperature
float tdsVoltage = 0.0, tdsValue = 0.0;
float phVoltage = 0.0, phValue = 0.0;
float doVoltage = 0.0, doValue = 0.0;
bool printRequested = false;
bool monitoringEnabled = true;

// === Command Protocol ===
const char CMD_PRINT = 'P';
const char CMD_TOGGLE_MONITORING = 'M';
const char CMD_REQUEST_DATA = 'D';

void setup() {
  // Hardware Serial for computer communication
  Serial.begin(9600);
  
  // SoftwareSerial for printer
  printerSerial.begin(9600);
  printer.begin();
  
  sensors.begin();  // Start temperature sensor
  delay(1000);
  
  Serial.println("System initialized with thermal printer");
  Serial.println("Commands: P=Print, M=Toggle Monitoring, D=Request Data");
}

void loop() {
  // Read sensors
  readSensors();
  
  // Check for commands from GUI
  checkSerialCommands();
  
  // Print sensor data to serial if monitoring is enabled
  if (monitoringEnabled) {
    reportSensorData();
  }
  
  // Print report if requested
  if (printRequested) {
    printWaterQualityReport();
    printRequested = false;
  }
  
  delay(2000);  // 2 sec delay
}

void readSensors() {
  // === Temperature Reading ===
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);
  
  if (temperature == -127.00) {
    if (monitoringEnabled) {
      Serial.println("Temperature sensor error! Check connection.");
    }
    temperature = 0.0;  // default fallback
  }

  // === TDS Sensor Reading ===
  int tdsRaw = analogRead(TDS_SENSOR);
  tdsVoltage = tdsRaw * (5.0 / 1023.0);

  float compCoeff = 1.0 + 0.02 * (temperature - 0.0);
  float compVoltage = tdsVoltage / compCoeff;

  tdsValue = (133.42 * pow(compVoltage, 3)) - (255.86 * pow(compVoltage, 2)) + (857.39 * compVoltage);
  tdsValue /= 2.0;  // convert to ppm

  // Sanity check for TDS
  if (tdsValue < 0) tdsValue = 0;

  // === pH Sensor Reading ===
  int phRaw = analogRead(PH_SENSOR);
  phVoltage = phRaw * (5.0 / 1023.0);
  phValue = 3.5 * phVoltage;  // Adjust based on calibration

  // === Dissolved Oxygen (DO) Sensor Reading ===
  int doRaw = analogRead(DO_SENSOR);
  doVoltage = doRaw * (5.0 / 1023.0);
  doValue = (doVoltage / 5.0) * 10.0;  // scale to 0-10 mg/L range
}

void reportSensorData() {
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("TDS: ");
  Serial.print(tdsValue);
  Serial.println(" ppm");

  Serial.print("pH: ");
  Serial.println(phValue);

  Serial.print("Dissolved Oxygen: ");
  Serial.print(doValue);
  Serial.println(" mg/L");

  Serial.println("---------------------------");
}

void checkSerialCommands() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    switch (command) {
      case CMD_PRINT:
        Serial.println("Print command received");
        printRequested = true;
        break;
        
      case CMD_TOGGLE_MONITORING:
        monitoringEnabled = !monitoringEnabled;
        Serial.print("Monitoring ");
        Serial.println(monitoringEnabled ? "enabled" : "disabled");
        break;
        
      case CMD_REQUEST_DATA:
        // Send data in a compact format for GUI parsing
        Serial.print("DATA:");
        Serial.print(temperature);
        Serial.print(",");
        Serial.print(tdsValue);
        Serial.print(",");
        Serial.print(phValue);
        Serial.print(",");
        Serial.println(doValue);
        break;
    }
    
    // Clear any remaining characters in buffer
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}

void printWaterQualityReport() {
  // Temporarily pause serial monitoring to avoid conflicts
  bool wasMonitoring = monitoringEnabled;
  monitoringEnabled = false;
  
  Serial.println("Printing report...");
  
  // Get current timestamp (if you have an RTC module, use that instead)
  unsigned long seconds = millis() / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;
  
  // Format: HH:MM:SS (uptime)
  char timestamp[9];
  sprintf(timestamp, "%02lu:%02lu:%02lu", hours % 24, minutes % 60, seconds % 60);
  
  printer.wake();       // Wake printer if it was sleeping
  printer.setFont('A'); // Set font to normal size
  
  // Print header with timestamp
  printer.boldOn();
  printer.justify('C');
  printer.println("WATER QUALITY REPORT");
  printer.boldOff();
  printer.println(timestamp);
  printer.println("-------------------");
  
  // Print readings
  printer.justify('L');
  
  printer.print("Temperature: ");
  printer.print(temperature);
  printer.println(" C");
  
  printer.print("TDS: ");
  printer.print(tdsValue);
  printer.println(" ppm");
  
  printer.print("pH: ");
  printer.println(phValue);
  
  printer.print("DO: ");
  printer.print(doValue);
  printer.println(" mg/L");
  
  // Water quality assessment
  printer.println("-------------------");
  printer.boldOn();
  printer.println("ASSESSMENT:");
  printer.boldOff();
  
  // Simple water quality assessment
  if (phValue < 6.5 || phValue > 8.5) {
    printer.println("pH: Out of ideal range");
  } else {
    printer.println("pH: Normal");
  }
  
  if (tdsValue > 500) {
    printer.println("TDS: High mineral content");
  } else {
    printer.println("TDS: Normal");
  }
  
  if (doValue < 5.0) {
    printer.println("DO: Low oxygen levels");
  } else {
    printer.println("DO: Normal");
  }
  
  printer.feed(3); // Feed paper to make it easier to tear
  printer.sleep();  // Sleep the printer to save power
  
  Serial.println("Report printed successfully");
  
  // Restore previous monitoring state
  monitoringEnabled = wasMonitoring;
}
