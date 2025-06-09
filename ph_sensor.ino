const int PH_SENSOR_PIN = A0; 
float pHValue = 0.0;

const float PH_SLOPE = -5.7;  // Adjust based on calibration
const float PH_OFFSET = 16.5; // Adjust to match pH 7 calibration

void setup() {
  Serial.begin(9600);
  Serial.println("pH Sensor Test Started...");
}

void loop() {
  int sensorValue = analogRead(PH_SENSOR_PIN);
  float voltage = sensorValue * (5.0 / 1023.0); // Convert analog to voltage
  pHValue = PH_SLOPE * voltage + PH_OFFSET;     // Calculate pH value

  // Print readings
  Serial.print("Analog Value: ");
  Serial.print(sensorValue);
  Serial.print(", Voltage: ");
  Serial.print(voltage, 2);
  Serial.print(" V, pH Value: ");
  Serial.println(pHValue, 2);

  delay(1000); // Delay for stability
}
