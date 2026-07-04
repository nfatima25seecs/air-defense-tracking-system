# Wiring

These are the pins used in src/air_defense_tracking_system.ino. If your build is
different, change them here and in the code so they match.

## Pin connections

| Arduino Pin | Connected to      | Notes                       |
| ----------- | ----------------- | --------------------------- |
| A0          | HC-SR04 TRIG      |                             |
| A1          | HC-SR04 ECHO      |                             |
| D11         | Servo signal      | Sweeps the sensor           |
| 5V          | HC-SR04 VCC       | Power the servo separately  |
| GND         | Common ground     | Connect all grounds together |

## Notes

- It is better to power the servo from a separate 5V supply, not the Arduino 5V
  pin, so it does not reset during the sweep. Connect the grounds together.
- The detection range in the code is 40 cm and the sweep goes from 15 to 165
  degrees.
- The code sends the angle and distance over serial at 9600 baud. This is the
  format a Processing radar sketch reads, which is handy for the demo.
