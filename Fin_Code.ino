#include <VarSpeedServo.h>

// Create 8 servo objects
VarSpeedServo servo1, servo2, servo3, servo4, servo5, servo6, servo7, servo8;

void setup() {
  // Attach servos to digital pins
  servoFLS.attach(2); // front left shoulder
  servoFLE.attach(3); // front left elbow
  servoFRS.attach(4); // front right shoulder
  servoFRE.attach(5); // front right elbow
  servoBLS.attach(6); // back left shoulder
  servoBLE.attach(7); // back left elbow
  servoBRS.attach(8); // back right shoulder
  servoBRE.attach(9); // back right elbow
}

void loop() {
  // servo.write(angle, speed, wait)
  // Speed is 0=fastest, 255=slowest
  
  startingTime = millis();

  servoFLE.write(60, 45, false);
  delay(500);
  servoFLS.write(15, 100, false);
  delay(500);
  servoFLE.write(0, 45, false);
  delay(500);
  servoFLS.write(0, 100, false);
  delay(500);

  servoBRE.write(60, 45, false);
  delay(500);
  servoBRS.write(15, 100, false);
  delay(500);
  servoBRE.write(0, 45, false);
  delay(500);
  servoBRS.write(0, 100, false);
  delay(500);

  servoBLE.write(60, 45, false);
  delay(500);
  servoBLS.write(15, 100, false);
  delay(500);
  servoBLE.write(0, 45, false);
  delay(500);
  servoBLS.write(0, 100, false);
  delay(500);

  servoFRE.write(60, 45, false);
  delay(500);
  servoFRS.write(15, 100, false);
  delay(500);
  servoFRE.write(0, 45, false);
  delay(500);
  servoFRS.write(0, 100, false);
  delay(500);

  // servoFLS.write(0, 30, false);   // Fast
  // servoFLE.write(180, 100, false); // Medium
  // servoFRS.write(90, 200, false);  // Slow
  // servoFRE.write(45, 50, false);
  // servoBLS.write(135, 150, false);
  // servoBLE.write(10, 80, false);
  // servoBRS.write(170, 120, false);
  // servoBRE.write(90, 255, false); // Very slow
}
