# Automatic Air Defense Tracking System

Arduino project that works kind of like a small radar. An ultrasonic sensor sits
on a servo and sweeps back and forth to scan the area. When it finds a target
that is close enough, it stops sweeping and points at it. I made this as one of
my semester projects.

## What it does

- The servo sweeps the ultrasonic sensor left and right
- It measures the distance at each angle
- When something comes within range, it locks on and keeps pointing at it
- It sends the angle and distance over serial, so you can show it on a radar
  display made in Processing

## Parts used

- Arduino Uno
- Servo motor (for the sweep)
- HC-SR04 ultrasonic sensor
- Jumper wires and a breadboard

## Wiring

The pin connections are in docs/wiring.md.

## How to run it

1. Open the code in the Arduino IDE
2. Install the Servo library if you don't already have it
3. Select your board and port
4. Upload

## Notes

- It uses one servo, so it only pans left and right
- The detection range is set to 40 cm and it sweeps from 15 to 165 degrees. You
  can change these values at the top of the code.

## Author

Noor Fatima
Computer Engineering, NUST (SEECS)
