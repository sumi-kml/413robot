#include <Servo.h>

// ---------------- SERVOS ----------------
Servo fls, fle;   // Front Left shoulder, elbow
Servo frs, fre;   // Front Right
Servo bls, ble;   // Back Left
Servo brs, bre;   // Back Right

// ---------------- ANGLES ----------------
// Elbows (same for all, unless you find one is reversed)
const int ELBOW_FRONT = 0;
const int ELBOW_BACK  = 60;

// Shoulders
const int SHOULDER_DOWN = 0;

// Right side shoulders lift positive
const int RIGHT_SHOULDER_UP = 15;

// Left side shoulders lift negative
const int LEFT_SHOULDER_UP = -15;

// ---------------- TIMING ----------------
const int UNIT_TIME = 100;   // ms per gait unit
const int TOTAL_UNITS = 10;   // full cycle length (change later if needed)

// 1-unit stagger like you said
const int FL_OFFSET = 2;
const int BR_OFFSET = 0;
const int FR_OFFSET = 10;
const int BL_OFFSET = 8;

// ---------------- MOVE ONE LEG ----------------
void moveLeg(Servo &shoulder, Servo &elbow, int shoulderUpAngle, int phase) {
  // phase 0 = push back on ground
  if (phase == 0) {
    shoulder.write(SHOULDER_DOWN);
    elbow.write(ELBOW_BACK);
  }

  // phase 1 = lift foot
  else if (phase == 1) {
    shoulder.write(shoulderUpAngle);
    elbow.write(ELBOW_BACK);
  }

  // phase 2 = swing forward in air
  else if (phase == 2) {
    shoulder.write(shoulderUpAngle);
    elbow.write(ELBOW_FRONT);
  }

  // phase 3 = put foot down
  else if (phase == 3) {
    shoulder.write(SHOULDER_DOWN);
    elbow.write(ELBOW_FRONT);
  }
}

// ---------------- UPDATE LEG ----------------
void updateLeg(Servo &shoulder, Servo &elbow, int shoulderUpAngle, int cyclePos) {
  int phaseLength = TOTAL_UNITS / 5;   // if TOTAL_UNITS=8, each phase is 2 units
  int phase = cyclePos / phaseLength;

  if (phase > 3) phase = 3;

  moveLeg(shoulder, elbow, shoulderUpAngle, phase);
}

// ---------------- SETUP ----------------
void setup() {
  fls.attach(2);
  fle.attach(3);

  frs.attach(4);
  fre.attach(5);

  bls.attach(6);
  ble.attach(7);

  brs.attach(8);
  bre.attach(9);
}

// ---------------- LOOP ----------------
void loop() {
  for (int t = 0; t < TOTAL_UNITS; t++) {

    int flPos = (t + FL_OFFSET) % TOTAL_UNITS;
    int brPos = (t + BR_OFFSET) % TOTAL_UNITS;
    int frPos = (t + FR_OFFSET) % TOTAL_UNITS;
    int blPos = (t + BL_OFFSET) % TOTAL_UNITS;

    // Left legs use -15 for lift
    updateLeg(fls, fle, LEFT_SHOULDER_UP, flPos);
    updateLeg(bls, ble, LEFT_SHOULDER_UP, blPos);

    // Right legs use +15 for lift
    updateLeg(frs, fre, RIGHT_SHOULDER_UP, frPos);
    updateLeg(brs, bre, RIGHT_SHOULDER_UP, brPos);

    delay(UNIT_TIME);
  }
}