/*
 * ML8511 UV Sensor Example
 * 
 * This example demonstrates how to use the ML8511 library to:
 * - Measure UV intensity in different units
 * - Calculate the UV Index
 * - Calibrate the sensor with custom voltage values
 * - Enable logging for debugging
 * 
 * Hardware Connections:
 * - ML8511 OUT pin -> A0 (analog input)
 * - ML8511 EN pin  -> D2 (digital output)
 * - VCC            -> 3.3V
 * - GND            -> GND
 * 
 * Author: Saurav Sajeev
 */

 #include <ML8511.h>

 // Define pins
 const uint8_t ANALOG_PIN = A0;  // Analog pin connected to ML8511 OUT
 const uint8_t ENABLE_PIN = 2;   // Digital pin connected to ML8511 EN
 
 // Create ML8511 object
 ML8511 uvSensor(ANALOG_PIN, ENABLE_PIN);
 
 void setup() {
   // Initialize serial communication
   Serial.begin(9600);
   while (!Serial) {
     ; // Wait for serial port to connect (needed for some boards like Leonardo)
   }
 
   // Enable logging to see debug messages
   uvSensor.showLogs(true);
   Serial.println("ML8511 UV Sensor Example Started");
 
   // Set initial unit to mW/cm²
   uvSensor.setActiveUnit(mW_Per_Sq_cm);
   Serial.println("Unit set to mW/cm²");
 
   // Calibrate the sensor with custom voltage values
   // These are example values; adjust based on your sensor's datasheet or testing
   if (uvSensor.calibrateSensor(0.85, 2.1, 2.8)) {
     Serial.println("Sensor calibration successful!");
   } else {
     Serial.println("Sensor calibration failed!");
   }
 
   // Set over-sampling to improve consistency (optional)
   uvSensor.setOverSampling(ML8511_OSS_2); // 10 samples
   Serial.println("Over-sampling set to 10 steps");
 }
 
 void loop() {
   // Get UV intensity and UV Index
   float uvIntensity = uvSensor.getUVIntensity();
   uint8_t uvIndex = uvSensor.getUVIndex();
 
   // Print results for mW/cm²
   Serial.print("UV Intensity (mW/cm²): ");
   Serial.print(uvIntensity);
   Serial.print(" | UV Index: ");
   Serial.println(uvIndex);
 
   // Switch unit to MED and measure again
   uvSensor.setActiveUnit(MED);
   uvIntensity = uvSensor.getUVIntensity();
   Serial.print("UV Intensity (MED): ");
   Serial.println(uvIntensity);
 
   // Switch unit to W/m² and measure again
   uvSensor.setActiveUnit(W_Per_Sq_m);
   uvIntensity = uvSensor.getUVIntensity();
   Serial.print("UV Intensity (W/m²): ");
   Serial.println(uvIntensity);
 
   // Delay before next reading
   delay(2000); // Wait 2 seconds
 }