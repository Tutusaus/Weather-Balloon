# Low-Cost Stratospheric Probe Project

## Overview
This repository contains the software and scripts developed for the **Low-Cost Stratospheric Probe** project. The project was undertaken to design and deploy a high-altitude weather balloon equipped with sensors and cameras using affordable, open-source hardware and software solutions. The goal is to capture atmospheric data at altitudes up to 30 km and study environmental conditions, with the ability to log data for post-flight analysis.

## Features
- **Arduino-Based Sensor Suite**:
  - Collects temperature, humidity, and pressure data using DHT11 and BMP180 sensors.
  - Measures external and internal temperatures with DS18B20 sensors.
  - Logs data to an SD card for offline storage.
  
- **GPS Tracking System**:
  - Real-time GPS tracking using Adafruit Ultimate GPS Breakout module.
  - SMS-based GPS location updates via GSM module (SIM900).

- **Real-Time Data Collection**:
  - Captures continuous environmental data during ascent.
  - Takes periodic photographs using a mobile phone camera controlled by Arduino.

- **Custom Arduino Code**:
  - Optimized sketches for handling data collection, storage, and transmission.
  - Power-efficient code to extend battery life during the flight.

## Hardware Requirements
- **Microcontrollers**:
  - Arduino Uno or Arduino Nano
- **Sensors**:
  - [DHT11](https://www.adafruit.com/product/386) - Temperature and humidity sensor
  - [BMP180](https://www.adafruit.com/product/1603) - Pressure sensor
  - [DS18B20](https://www.adafruit.com/product/381) - Waterproof temperature sensor
- **Modules**:
  - [Adafruit Ultimate GPS Breakout](https://www.adafruit.com/product/746) - For GPS tracking
  - [SIM900 GSM Module](https://www.adafruit.com/product/2637) - For SMS-based GPS updates
  - SD Card Module - For data logging
- **Power Supply**:
  - Li-ion batteries
- **Additional Components**:
  - High-altitude weather balloon
  - Helium for balloon inflation
  - Parachute for safe descent

## Software Requirements
- **Arduino IDE**: [Download here](https://www.arduino.cc/en/software)
- **Arduino Libraries**:
  - `Adafruit GPS`
  - `SD`
  - `DHT`
  - `OneWire` and `DallasTemperature` for DS18B20 sensor
- **Mobile App**:
  - [MobileWebCam](https://play.google.com/store/apps/details?id=com.dngames.mobilewebcam) - For automated image capturing
- **Python** (for data analysis):
  - `matplotlib`, `pandas`, `numpy` (for data visualization)

## Setup Instructions
1. **Clone this repository**:
   ```bash
   git clone https://github.com/Tutusaus/Weather-Balloon.git
   cd Weather-Balloon
