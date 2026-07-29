# Autonomous Maze-Solving Robot

An Arduino-based autonomous robot designed to navigate a maze using ultrasonic distance sensing and a finite state machine.

The robot detects obstacles, makes navigation decisions, and adjusts its movement without human input. This project combines embedded programming, hardware integration, and algorithm design to create an autonomous navigation system.

---

## Overview

The robot uses an Arduino RedBoard, motor driver, two gear motors, an ultrasonic distance sensor, RGB LED indicators, and control buttons to navigate through a maze.

A state machine controls the robot's behavior by switching between movement states based on sensor input.

---

## Features

- Autonomous obstacle detection and navigation
- Ultrasonic distance sensing
- State machine-based decision making
- PWM motor speed control
- RGB LED status indicators
- Start and stop controls
- Real-time distance monitoring through serial output

---

## System Architecture

### Hardware

- Arduino RedBoard
- Motor driver
- Two gear motors
- Ultrasonic distance sensor
- RGB LED
- Push buttons
- Battery pack
- Robot chassis


### Software

- Language: C++
- Platform: Arduino
- Control Method: Finite State Machine

---

## State Machine

The robot operates through four main states:

### GO_STRAIGHT

The robot moves forward while continuously checking the distance sensor.

If an obstacle is detected within the threshold distance, the robot stops, backs up, and transitions into the turning process.

---

### TURN_RIGHT

The robot performs a right turn after backing away from an obstacle.

After turning, it checks whether the path is clear.

---

### CHECK_PATH

The robot moves slowly and rechecks the environment.

- If another obstacle is detected, it transitions to `TURN_LEFT`.
- Otherwise, it returns to `GO_STRAIGHT`.

---

### TURN_LEFT

The robot performs a corrective left turn and resumes forward movement.

---

## Engineering Challenges

Throughout development, the robot required debugging across both hardware and software systems.

Challenges included:

- Calibrating ultrasonic sensor thresholds
- Tuning motor speeds for consistent movement
- Adjusting turn timing for accurate navigation
- Debugging wiring and hardware reliability
- Designing a reliable state transition system

---

## Lessons Learned

This project provided experience with:

- Embedded C++ programming
- Hardware-software integration
- Sensor data processing
- Finite state machines
- Debugging physical systems
- Iterative engineering design

---

## Documentation

Additional project documentation can be found in the `docs/` folder, including the design process, algorithm description, testing results, and presentation materials.

---

## Contributors

- Ananth Karthic

---

## License

This project is licensed under the MIT License.
