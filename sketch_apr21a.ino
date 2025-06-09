void setup() {
  // Start the serial port to communicate with the thermal printer
  Serial.begin(9600);
  delay(2000); // Give the printer time to initialize

  // Print custom text
  Serial.println("=== Water Quality Report ===");
  Serial.println("TDS: 310 ppm");
  Serial.println("pH: 7.2");
  Serial.println("Temperature: 25.6 C");
  Serial.println("============================");
  Serial.println(); // Feed some blank lines
  Serial.println();
}

void loop() {
  // Nothing to do here
}
