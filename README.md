# Smart Dustbin Project

This repository contains the code and documentation for a smart dustbin project using NodeMCU, ultrasonic sensors, servos, and an OLED display.

## Hardware Requirements

- NodeMCU ESP8266 development board
- HC-SR04 ultrasonic sensors (x2)
- SG90 servo motor (x2) (Second servo motor is for more force to open the dustbin lid, optional)
- OLED display with SH1106 driver (I2C communication protocol used)
- Breadboard and jumper wires
- Power source (2 x 18650 batteries)
- Buck Converter LM2596 (dial down to steady 5v)
- 6 amp rocker switch
- 2x 18650 battery holder

## Software Requirements

- Arduino IDE
- libraries -> "Wire.h", "Servo.h" and "U8g2lib.h"

## Connections

### Ultrasonic Sensors
- **Sensor 1 (Hand Detection):**
  - Trig Pin: D5
  - Echo Pin: D6
- **Sensor 2 (Garbage Level Monitoring):**
  - Trig Pin: D3
  - Echo Pin: D4

### Servo Motors
- **Servo 1 (Main Lid Opening):**
  - Signal Pin: D7
- **Servo 2 (Additional Force Lid Opening):**
  - Signal Pin: D8

### OLED Display
- SCL Pin: D1
- SDA Pin: D2

## Making the Smart Dustbin

1. **Assemble Hardware:**
   - Connect the NodeMCU board, ultrasonic sensors, servos, and OLED display according to the connections mentioned above.
   - Ensure all connections are secure and wires are properly connected.
   - Place the second ultrasonic sensor at the middle of the dustbin lid facing downwards to measure the garbage level.
   - Connect the batteries with the buck converter and add a switch in between the node MCU and the out of the converter.
   - Place the first ultrasonic sensor at the front of the lid for hand detection, and place the OLED display just above it to read sensor data.

2. **Upload Code:**
   - Upload the provided Arduino code (`smart_dustbin.ino`) to the NodeMCU board using the Arduino IDE or any other compatible IDE.

3. **Adjust Parameters:**
   - Adjust the threshold distance and lid open/close delays in the code as needed to fit your requirements.
   - Verify that the garbage level percentage calculation is accurate for your dustbin's dimensions.

4. **Power Up:**
   - Power up the NodeMCU board using the 18650 batteries woth the LM2596 buck converter dialed down to 5V.
   - Ensure all components are receiving power and functioning correctly.

5. **Testing:**
   - Test the smart dustbin by placing your hand near the hand detection sensor and observing the lid opening.
   - Monitor the garbage level percentage displayed on the OLED display as you fill the dustbin.

6. **Finalize Assembly:**
   - Once everything is working as expected, finalize the assembly of the smart dustbin.
   - Secure all components in place and ensure the dustbin is ready for use.

## OLED Display
The OLED display used in this project is a 128x64 pixels monochrome display with an SH1106 driver. It communicates with the NodeMCU board using the I2C protocol.

## License
This project is licensed under the [MIT License](LICENSE).
