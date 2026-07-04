/*
  Automatic Air Defense Tracking System

  A servo sweeps an HC-SR04 ultrasonic sensor back and forth like a small radar.
  At each angle it measures the distance and sends "angle,distance." over serial
  so a Processing sketch can draw it. When a target comes within DETECT_RANGE it
  stops sweeping and keeps pointing at the target until it goes away, then it
  starts scanning again.

  Uses one servo, so it only pans left and right.

  Noor Fatima, Computer Engineering, NUST (SEECS)

  Pins are set below to match docs/wiring.md.
*/

#include <Servo.h>

// ---------- Pin map (see docs/wiring.md) ----------
const int TRIG_PIN  = A0;
const int ECHO_PIN  = A1;
const int SERVO_PIN = 11;

// ---------- Sweep + detection settings ----------
const int  SWEEP_MIN   = 15;    // servo sweep limits (degrees)
const int  SWEEP_MAX   = 165;
const int  STEP        = 2;     // degrees per step
const long DETECT_RANGE = 40;   // cm - a target closer than this is "acquired"
const int  LOCK_HOLD_MS = 400;  // how long to keep aiming after last detection

Servo panServo;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  panServo.attach(SERVO_PIN);
  panServo.write((SWEEP_MIN + SWEEP_MAX) / 2);
  delay(400);
}

void loop() {
  // Sweep across the field. sweepAndScan returns the bearing of a detected
  // target, or -1 if the field is clear this pass.
  int target = sweepAndScan(SWEEP_MIN, SWEEP_MAX,  STEP);   // left → right
  if (target >= 0) { trackTarget(target); return; }

  target = sweepAndScan(SWEEP_MAX, SWEEP_MIN, -STEP);       // right → left
  if (target >= 0) { trackTarget(target); }
}

// Sweep between two angles, reporting each reading. Returns the first angle at
// which a target falls inside DETECT_RANGE, or -1 if none.
int sweepAndScan(int from, int to, int step) {
  for (int angle = from; (step > 0) ? angle <= to : angle >= to; angle += step) {
    panServo.write(angle);
    delay(30);                       // let the servo reach the angle
    long d = readDistance();
    report(angle, d);
    if (d > 0 && d < DETECT_RANGE) return angle;
  }
  return -1;
}

// Hold aim on an acquired target. Keeps re-measuring at the locked bearing and
// releases once the target has been gone for LOCK_HOLD_MS.
void trackTarget(int bearing) {
  panServo.write(bearing);
  unsigned long lastSeen = millis();
  while (millis() - lastSeen < LOCK_HOLD_MS) {
    long d = readDistance();
    report(bearing, d);
    if (d > 0 && d < DETECT_RANGE) lastSeen = millis();  // still locked
    delay(40);
  }
}

// HC-SR04 distance in cm. Returns 0 on timeout (nothing in range).
long readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 25000UL);
  if (duration == 0) return 0;
  return duration * 0.0343 / 2;
}

// Stream "angle,distance." - the format a Processing radar sketch expects.
void report(int angle, long distance) {
  Serial.print(angle);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
}
