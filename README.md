# Smart Plant Watering System

## I. INTRODUCTION
The Smart Plant Watering System integrates NodeMCU ESP8266, a moisture sensor, relay module, and ThingSpeak IoT platform to create an IoT-based plant care solution. Monitoring soil moisture levels in real-time, the system autonomously activates a relay-controlled water pump when moisture dips below a predefined threshold. ThingSpeak stores and analyzes data, while users gain control over the motor state via a dedicated web interface. This project ensures optimal plant hydration through automated watering and user-controlled interventions, enhancing plant health with a streamlined and accessible IoT application.

## II. PROJECT DETAILS

### Objective:
The Smart Plant Watering System is designed to revolutionize plant care through an IoT-based solution. Utilizing a NodeMCU ESP8266, moisture sensor, relay module, DC motor, Arduino IDE for programming, breadboard for prototyping, and ThingSpeak for cloud connectivity, the system provides automated and user-controlled watering based on real-time soil moisture data.

### Components:
- **NodeMCU ESP8266**: Central controller for data processing and communication.
- **Moisture Sensor**: Monitors soil moisture levels for real-time plant hydration assessment.
- **Relay Module**: Controls a water pump (DC motor) for precise and automated watering.
- **DC Motor**: Activates water pump to deliver water to plants when needed.
- **Arduino IDE**: Used for programming the NodeMCU and integrating components.
- **Breadboard**: Facilitates prototyping and easy component integration.
- **ThingSpeak**: Cloud-based platform for storing and retrieving moisture data.

### Functionality:
- **Automated Watering**: The system autonomously waters plants when soil moisture falls below a predefined threshold, ensuring optimal hydration.
- **Cloud Data Storage**: ThingSpeak facilitates cloud connectivity, storing real-time moisture data for historical tracking and analysis.
- **Web Interface Control**: Users can access a web interface to monitor current soil moisture levels and manually control the water pump.
- **Real-time Tracking**: The web interface allows users to track the current soil moisture level, enabling proactive plant care.
- **Customizable Control**: Arduino IDE enables flexible programming, allowing users to customize watering thresholds and intervals.

### Benefits:
- **Efficient Watering**: Automated watering promotes plant health by delivering precise moisture levels.
- **Data Analysis**: ThingSpeak's cloud storage enables users to analyze moisture trends, facilitating informed plant care decisions.
- **Real-time Monitoring**: Users can track current soil moisture levels through the web interface, ensuring timely interventions.
- **Customizable Settings**: Arduino IDE and the web interface provide users with customizable control over watering parameters.

## III. INTERFACING COMPONENTS

### Relay Module:
- Connect the VCC of the relay module to the 5V output on the NodeMCU.
- Attach the GND of the relay module to the ground (GND) pin on the NodeMCU.
- Use a digital pin (D4) to connect to the IN or signal pin on the relay module.

### DC Motor:
- Power the DC motor using an external DC battery to ensure adequate power supply.
- Connect the positive terminal of the motor to the common (COM) terminal on the relay module.
- Link the normally open (NO) terminal of the relay module to the negative terminal of the DC motor.

### Moisture Sensor:
- Connect the VCC and GND of the moisture sensor to the 5V and GND pins on the NodeMCU.
- Use an analog pin on the NodeMCU (A0) to connect to the AO (analog output) pin on the moisture sensor.

### NodeMCU:
- Program the NodeMCU using Arduino IDE for reading data from the moisture sensor and controlling the relay module.
- Implement appropriate code logic to compare moisture levels and trigger the relay module to activate or deactivate the DC motor.
- Upload the compiled code to the NodeMCU.

## IV. INSTALLATION

1. **Hardware Setup**:
   - Assemble the circuit by connecting all components as described above. Ensure that the moisture sensor is placed in the soil, the relay controls the water pump, and the NodeMCU is powered.

2. **Software Setup**:
   - Download and install [Arduino IDE](https://www.arduino.cc/en/software).
   - Install the ESP8266 board in Arduino IDE by going to `File > Preferences > Additional Boards Manager URLs` and adding `http://arduino.esp8266.com/stable/package_esp8266com_index.json`.
   - In the `Boards Manager`, search for `ESP8266` and install it.
   - Set the board to `NodeMCU 1.0` in the `Tools > Board` menu.
   - Install the necessary libraries for WiFi and HTTPClient by going to `Sketch > Include Library > Manage Libraries`.

3. **Upload Code**:
   - Upload the provided code (stored in the `src` folder) to the NodeMCU ESP8266 using Arduino IDE.
   - Replace the ThingSpeak API key and Wi-Fi credentials in the code.
   - Monitor the serial output for Wi-Fi connection details and check ThingSpeak for data updates.

## V. REFERENCES

- [ThingSpeak IoT Platform](https://thingspeak.com/)
- [NodeMCU ESP8266 Documentation](https://nodemcu.readthedocs.io/en/master/)
- [Arduino IDE](https://www.arduino.cc/en/software)

## VI. LICENSE

This project is open-source. You are free to modify, distribute, and use it under the terms of the MIT License.
