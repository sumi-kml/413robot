#include <Servo.h>

// Define states for the gait cycle
enum State { PUSH, LIFT, FORWARD, PUT_DOWN };

struct Leg {
  Servo upper;
  Servo lower;
  State currentState;
  int currentUpper, currentLower;
  int targetUpper, targetLower;
  unsigned long lastMoveTime;
  int speed; // Delay in ms per degree
};

// Initialize legs
Leg legs[4] = {
  {Servo(), Servo(), PUSH, 15, 0, 15, 60, 0, 45}, // Front Left
  {Servo(), Servo(), PUSH, 15, 0, 15, 60, 0, 45}, // Front Right
  {Servo(), Servo(), PUSH, 15, 0, 15, 60, 0, 45}, // Back Left
  {Servo(), Servo(), PUSH, 15, 0, 15, 60, 0, 45}  // Back Right
};

void setup() {
  // Attach servos (Pin assignments based on your first snippet)
  legs[0].upper.attach(13); legs[0].lower.attach(12);
  legs[1].upper.attach(11); legs[1].lower.attach(10);
  legs[2].upper.attach(9);  legs[2].lower.attach(8);
  legs[3].upper.attach(7);  legs[3].lower.attach(6);
}

void updateLeg(Leg &leg) {
  unsigned long now = millis();
  
  if (now - leg.lastMoveTime >= leg.speed) {
    leg.lastMoveTime = now;
    
    switch (leg.currentState) {
      case PUSH: // Lower servo 0 -> 60
        if (leg.currentLower < 60) { leg.currentLower++; leg.lower.write(leg.currentLower); }
        else { leg.currentState = LIFT; leg.speed = 100; } // Switch to Upper Servo speed
        break;
        
      case LIFT: // Upper servo 15 -> 0
        if (leg.currentUpper > 0) { leg.currentUpper--; leg.upper.write(leg.currentUpper); }
        else { leg.currentState = FORWARD; leg.speed = 45; }
        break;
        
      case FORWARD: // Lower servo 60 -> 0
        if (leg.currentLower > 0) { leg.currentLower--; leg.lower.write(leg.currentLower); }
        else { leg.currentState = PUT_DOWN; leg.speed = 100; }
        break;
        
      case PUT_DOWN: // Upper servo 0 -> 15
        if (leg.currentUpper < 15) { leg.currentUpper++; leg.upper.write(leg.currentUpper); }
        else { leg.currentState = PUSH; leg.speed = 45; }
        break;
    }
  }
}

void loop() {
  // Every leg updates independently in every loop iteration
  for (int i = 0; i < 4; i++) {
    updateLeg(legs[i]);
  }
}

//2:16: error: variable or field 'updateLeg' declared void


//2:16: error: 'Leg' was not declared in this scope
//2:21: error: 'leg' was not declared in this scope


//2:21: note: suggested alternative: 'log'
