#include <Servo.h>

Servo servoYaw;      // neck (X)
Servo servoPitchA;   // left pitch
Servo servoPitchB;   // right pitch (mirrored)

bool armed = false;
unsigned long armTimer = 0;

// ---- HARD SERVO LIMITS (DO NOT EXCEED) ----
const int YAW_MIN    = 20;
const int YAW_MAX    = 160;

const int PITCH_MIN  = 50;
const int PITCH_MAX  = 170;

int safeX  = 90;
int safeY1 = 90;
int safeY2 = 150; // B

// ---- SOFT MOVE FUNCTION ----
// void moveSoft(Servo &s, int targetAngle, int stepDelay = 10) {
//     int current = s.read();
//     if (current < targetAngle) {
//         for (int i = current; i <= targetAngle; i++) {
//             s.write(i);
//             delay(stepDelay);
//         }
//     } else if (current > targetAngle) {
//         for (int i = current; i >= targetAngle; i--) {
//             s.write(i);
//             delay(stepDelay);
//         }
//     }
// }

// void moveSoft(Servo &s, int from, int to) {
//   int step = (to > from) ? 1 : -1;
//   for (int pos = from; pos != to; pos += step) {
//     s.write(pos);
//     delay(10);
//   }
// }

void setup() {
  Serial.begin(115200);

  servoYaw.attach(9, 1000, 2000);
  servoPitchA.attach(10, 1000, 2000);
  servoPitchB.attach(11, 1000, 2000);

  // HARD POSITION IMMEDIATELY — NO MOVE SOFT HERE
  servoYaw.write(90);
  servoPitchA.write(150);
  servoPitchB.write(150);   // mirror of 150

  delay(1200);  // allow physical settle
}

void loop() {

if (!armed) {
  if (millis() > 1500) armed = true;
  return;
}

  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    int comma = data.indexOf(',');

    if (comma > 0) {
      int yaw   = data.substring(0, comma).toInt();
      int pitch = data.substring(comma + 1).toInt();

      yaw   = constrain(yaw,   YAW_MIN,   YAW_MAX);
      pitch = constrain(pitch, PITCH_MIN, PITCH_MAX);

      servoYaw.write(yaw);
      servoPitchA.write(pitch);
      servoPitchB.write(180 - pitch);

    }
  }
}
