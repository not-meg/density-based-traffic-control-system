# Density-Based Traffic Control System

This project utilizes an Arduino MEGA board, 6 ultrasonic sensors (HC-SR04), 12 LED lights (red, yellow, green), and connector wires to implement a traffic control system based on road traffic density.

## Overview
The system continuously monitors traffic density on four roads using ultrasonic sensors. LED lights indicate the status of each intersection's traffic signal, dynamically adjusting signal timings based on real-time vehicle presence.

## Functionality
- Each road intersection has red, yellow, and green LED lights controlled by the Arduino board.
- Ultrasonic sensors detect the presence of vehicles on each road segment.
- The traffic signal remains green for up to 10 seconds as long as there are vehicles on the road.
- When the time limit is reached or no vehicles are detected on the current road, the system switches to the next road to check for traffic.

## Abstract of Connections
![Ultrasonic Sensor and LED Connections](https://github.com/not-meg/density-based-traffic-control-system/assets/116863014/94becfea-d319-449c-a153-2e309e7052f2)

## Final Look
![Final Look of the Traffic Control System](https://github.com/not-meg/density-based-traffic-control-system/assets/116863014/0ff44e0b-ff47-400a-a36e-ed5ca9e3ce36)
