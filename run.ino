/*
 * 4-Legged Robot Walking Gait
 * Trot gait: diagonal pairs (FL+BR) and (FR+BL) move together,
 * offset by half a cycle.
 *
 * Each leg has a SHOULDER and ELBOW servo.
 * 
 * Leg cycle (one full stride):
 *   STANCE phase (leg on floor, drives body forward):
 *     - Elbow sweeps BACK  60 deg  (pushes robot forward)
 *   SWING phase  (leg in air, resets to start):
 *     Step 1 – Shoulder lifts leg UP   (+15 deg off floor)
 *     Step 2 – Elbow swings FORWARD    60 deg (returns to start position)
 *     Step 3 – Shoulder lowers leg DOWN (-15 deg, back on floor)
 *
 * Pin assignments – change to match your wiring:
 *   FL_SHOULDER = 2   FL_ELBOW = 3
 *   FR_SHOULDER = 4   FR_ELBOW = 5
 *   BL_SHOULDER = 6   BL_ELBOW = 7
 *   BR_SHOULDER = 8   BR_ELBOW = 9
 */

#include <Servo.h>

void moveLeg(Servo &shoulder, Servo &elbow, int phaseStep);

// ── Pin assignments ────────────────────────────────────────────────────────
#define FL_SHOULDER_PIN  2
#define FL_ELBOW_PIN     3
#define FR_SHOULDER_PIN  4
#define FR_ELBOW_PIN     5
#define BL_SHOULDER_PIN  6
#define BL_ELBOW_PIN     7
#define BR_SHOULDER_PIN  8
#define BR_ELBOW_PIN     9

// ── Neutral / rest angles (tune for your robot's geometry) ─────────────────
#define SHOULDER_NEUTRAL  90   // shoulder angle when leg is on the floor
#define SHOULDER_LIFTED   (SHOULDER_NEUTRAL + 15)  // lifted clear of ground
#define ELBOW_NEUTRAL     90   // elbow angle at the start of stance
#define ELBOW_BACK        (ELBOW_NEUTRAL + 60)     // fully pushed back
// (ELBOW_NEUTRAL is also the "fully forward" position after swing)

// ── Timing ────────────────────────────────────────────────────────────────
// Total cycle divided into STEPS discrete moves. Each step lasts STEP_MS ms.
// With 16 steps × 50 ms = 800 ms per full stride.
#define TOTAL_STEPS   16
#define STEP_MS       50      // ms per step – decrease to walk faster

// Fraction of cycle spent in STANCE (on floor). 8/16 = 50 % duty cycle.
#define STANCE_STEPS  8       // steps 0 .. 7  → stance
#define SWING_STEPS   8       // steps 8 .. 15 → swing

/*
 * Phase offsets (in steps) read from the gait chart:
 *   Diagonal pairs share the same phase; opposite pairs are offset by half.
 *   FL + BR  → phase 0
 *   FR + BL  → phase 8  (half cycle later)
 */
#define PHASE_FL  0
#define PHASE_FR  8
#define PHASE_BL  8
#define PHASE_BR  0

// ── Servo objects ──────────────────────────────────────────────────────────
Servo flShoulder, flElbow;
Servo frShoulder, frElbow;
Servo blShoulder, blElbow;
Servo brShoulder, brElbow;

// ── Helper: move one leg according to its current phase step ───────────────
//
// phaseStep : 0 .. TOTAL_STEPS-1, where 0 is the START of stance
//
void moveLeg(Servo &shoulder, Servo &elbow, int phaseStep) {

  if (phaseStep < STANCE_STEPS) {
    // ── STANCE: leg on floor, elbow sweeps back to push body forward ────────
    // Shoulder stays at neutral (floor).
    shoulder.write(SHOULDER_NEUTRAL);

    // Linearly interpolate elbow from NEUTRAL (start) → BACK (end of stance)
    int elbowAngle = map(phaseStep, 0, STANCE_STEPS - 1,
                         ELBOW_NEUTRAL, ELBOW_BACK);
    elbow.write(elbowAngle);

  } else {
    // ── SWING: leg in air, elbow swings forward, then shoulder lowers ────────
    int swingStep = phaseStep - STANCE_STEPS; // 0 .. SWING_STEPS-1

    // Divide swing into 3 equal sub-phases
    int third = SWING_STEPS / 3; // ≈ 2-3 steps each

    if (swingStep < third) {
      // Sub-phase 1: lift shoulder, hold elbow at BACK
      int t = map(swingStep, 0, third - 1, SHOULDER_NEUTRAL, SHOULDER_LIFTED);
      shoulder.write(t);
      elbow.write(ELBOW_BACK);

    } else if (swingStep < 2 * third) {
      // Sub-phase 2: swing elbow forward (BACK → NEUTRAL), shoulder stays up
      shoulder.write(SHOULDER_LIFTED);
      int t = map(swingStep, third, 2 * third - 1,
                  ELBOW_BACK, ELBOW_NEUTRAL);
      elbow.write(t);

    } else {
      // Sub-phase 3: lower shoulder back to floor, elbow at NEUTRAL
      int t = map(swingStep, 2 * third, SWING_STEPS - 1,
                  SHOULDER_LIFTED, SHOULDER_NEUTRAL);
      shoulder.write(t);
      elbow.write(ELBOW_NEUTRAL);
    }
  }
}

// ── Global step counter ────────────────────────────────────────────────────
int globalStep = 0;

// ── Setup ──────────────────────────────────────────────────────────────────
void setup() {
  flShoulder.attach(FL_SHOULDER_PIN);  flElbow.attach(FL_ELBOW_PIN);
  frShoulder.attach(FR_SHOULDER_PIN);  frElbow.attach(FR_ELBOW_PIN);
  blShoulder.attach(BL_SHOULDER_PIN);  blElbow.attach(BL_ELBOW_PIN);
  brShoulder.attach(BR_SHOULDER_PIN);  brElbow.attach(BR_ELBOW_PIN);

  // Move all servos to their neutral starting position
  flShoulder.write(SHOULDER_NEUTRAL);  flElbow.write(ELBOW_NEUTRAL);
  frShoulder.write(SHOULDER_NEUTRAL);  frElbow.write(ELBOW_NEUTRAL);
  blShoulder.write(SHOULDER_NEUTRAL);  blElbow.write(ELBOW_NEUTRAL);
  brShoulder.write(SHOULDER_NEUTRAL);  brElbow.write(ELBOW_NEUTRAL);

  delay(1000); // let servos reach start position before walking
}

// ── Loop ───────────────────────────────────────────────────────────────────
void loop() {
  // Compute each leg's local phase step by applying its offset
  int flStep = (globalStep + PHASE_FL) % TOTAL_STEPS;
  int frStep = (globalStep + PHASE_FR) % TOTAL_STEPS;
  int blStep = (globalStep + PHASE_BL) % TOTAL_STEPS;
  int brStep = (globalStep + PHASE_BR) % TOTAL_STEPS;

  moveLeg(flShoulder, flElbow, flStep);
  moveLeg(frShoulder, frElbow, frStep);
  moveLeg(blShoulder, blElbow, blStep);
  moveLeg(brShoulder, brElbow, brStep);

  globalStep = (globalStep + 1) % TOTAL_STEPS;
  delay(STEP_MS);
}
