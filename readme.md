# ML8511 UV Sensor Arduino Library

This is an Arduino library for interfacing with the **ML8511 UV sensor**, a compact ultraviolet (UV) sensor that measures UV intensity and calculates the UV Index. The library provides a simple and flexible API to monitor UV exposure with support for multiple units and calibration options.

## Features
- Measure UV intensity in various units (e.g., mW/cm², W/m², μW/cm², MED, etc.).
- Calculate the UV Index based on sensor readings.
- Configurable over-sampling for improved measurement consistency.
- Custom calibration with user-defined voltage values.
- Support for multiple microcontroller platforms (e.g., ESP32, RP2040, STM32, SAM3X8E).
- Optional serial logging for debugging.

## Supported Platforms
- Arduino (AVR-based boards)
- ESP32
- Raspberry Pi Pico (RP2040)
- STM32F1 and STM32F4
- Arduino Due (SAM3X8E)

## Installation

### Using Arduino IDE
1. Download the latest release as a `.zip` file from the [Releases](https://github.com/styropyr0/ML8511/releases) page.
2. Open the Arduino IDE.
3. Go to **Sketch > Include Library > Add .ZIP Library**.
4. Select the downloaded `.zip` file and click **Open**.
5. The library will now be available under **Sketch > Include Library > ML8511**.

### Manual Installation
1. Clone or download this repository.
2. Copy the folder containing `ML8511.h` and `ML8511DEFS.h` to your Arduino `libraries` folder:
   - Windows: `Documents\Arduino\libraries\`
   - macOS/Linux: `~/Documents/Arduino/libraries/`
3. Restart the Arduino IDE.

## Hardware Connections
- **OUT Pin**: Connect to an analog input pin on your microcontroller (e.g., `A0`).
- **EN Pin**: Connect to a digital output pin for enabling/disabling the sensor (e.g., `D2`).
- **VCC**: Connect to 3.3V (or as per your microcontroller's logic level).
- **GND**: Connect to ground.

## Usage

### Basic Example
```cpp
#include <ML8511.h>

// Define pins
const uint8_t ANALOG_PIN = A0;
const uint8_t ENABLE_PIN = 2;

// Create sensor object
ML8511 uvSensor(ANALOG_PIN, ENABLE_PIN);

void setup() {
  Serial.begin(9600);
  uvSensor.setActiveUnit(mW_Per_Sq_cm); // Set unit to mW/cm²
}

void loop() {
  float uvIntensity = uvSensor.getUVIntensity();
  uint8_t uvIndex = uvSensor.getUVIndex();
  
  Serial.print("UV Intensity: ");
  Serial.print(uvIntensity);
  Serial.println(" mW/cm²");
  Serial.print("UV Index: ");
  Serial.println(uvIndex);
  
  delay(1000);
}
```

### Calibration Example
```cpp
#include <ML8511.h>

ML8511 uvSensor(A0, 2);

void setup() {
  Serial.begin(9600);
  
  // Calibrate with custom voltage values
  if (uvSensor.calibrateSensor(0.9, 2.1, 2.8)) {
    Serial.println("Calibration successful!");
  } else {
    Serial.println("Calibration failed!");
  }
  
  uvSensor.setActiveUnit(W_Per_Sq_m); // Set unit to W/m²
}

void loop() {
  float uvIntensity = uvSensor.getUVIntensity();
  Serial.print("UV Intensity: ");
  Serial.print(uvIntensity);
  Serial.println(" W/m²");
  delay(1000);
}
```

### Enable Logging
```cpp
#include <ML8511.h>

ML8511 uvSensor(A0, 2);

void setup() {
  Serial.begin(9600);
  uvSensor.showLogs(true); // Enable serial logging
  uvSensor.setActiveUnit(MED); // Set unit to MED
}

void loop() {
  float uvIntensity = uvSensor.getUVIntensity();
  Serial.print("UV Intensity: ");
  Serial.print(uvIntensity);
  Serial.println(" MED");
  delay(1000);
}
```

## API Reference

### Constructor
- `ML8511(uint8_t analog, uint8_t enable)`: Initializes the sensor with the analog and enable pins.

### Methods
- `float getUVIntensity()`: Returns the UV intensity in the currently set unit.
- `uint8_t getUVIndex()`: Returns the calculated UV Index (0-11+).
- `void set_V0(float v0)`: Sets the zero-UV voltage (default: 0.87V).
- `void setOverSampling(uint8_t oss)`: Sets the over-sampling factor (options: `ML8511_OSS_0`, `ML8511_OSS_1`, `ML8511_OSS_2`, `ML8511_OSS_3`).
- `bool calibrateSensor(float UV0_voltage, float UV10_voltage, float UV15_voltage)`: Calibrates the sensor with custom voltage values.
- `void setActiveUnit(uint8_t unit)`: Sets the unit for UV intensity (e.g., `mW_Per_Sq_cm`, `W_Per_Sq_m`, `MED`).
- `void showLogs(bool show)`: Enables or disables serial logging.

### Supported Units
| Constant            | Description           | String Representation |
|---------------------|-----------------------|-----------------------|
| `mW_Per_Sq_cm`      | Milliwatts per cm²    | `mW/cm2`             |
| `W_Per_Sq_m`        | Watts per m²          | `W/m2`               |
| `microW_Per_Sq_cm`  | Microwatts per cm²    | `μW/cm2`             |
| `Joules_s_Per_Sq_m` | Joules/s per m²       | `Js/m2`              |
| `mJoules_s_Per_Sq_cm`| Millijoules/s per cm²| `mJs/cm2`            |
| `Joules_s_Per_Sq_cm`| Joules/s per cm²      | `Js/cm2`             |
| `MED`               | Minimal Erythemal Dose| `MED`                |

## Notes
- The default ADC resolution is 10-bit (0-1023), but it switches to 12-bit (0-4095) for ESP32, RP2040, STM32, and SAM3X8E platforms.
- Ensure the sensor is powered with a stable 3.3V supply for accurate readings.
- Calibration voltages should align with the sensor's characteristics for reliable results.

## License
This library is released under the [MIT License](LICENSE). See the `LICENSE` file for details.

## Author
- **Saurav Sajeev**

## Contributing
Contributions are welcome! Please submit a pull request or open an issue on the [GitHub repository](https://github.com/styropyr0/ML8511).
