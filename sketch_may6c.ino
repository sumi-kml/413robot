#include <Servo.h> 
/* 
Example of a simple 4-step walking gait
*/
 
// Servo Variables
// First subscript Front or Back
// Second subscript Left or Right 
// Third subscript Upper or Lower 

Servo servo_f_l_u, servo_f_l_l, servo_f_r_u, servo_f_r_l, servo_b_l_u, servo_b_l_l, servo_b_r_u, servo_b_r_l;

int initial_angle_value_f_l_u = 90;
int initial_angle_value_f_l_l = 90;
int initial_angle_value_f_r_u = 90;
int initial_angle_value_f_r_l = 90;
int initial_angle_value_b_l_u = 90;
int initial_angle_value_b_l_l = 90;
int initial_angle_value_b_r_u = 90;
int initial_angle_value_b_r_l = 90;

int gait_steps = 12;

// int angle_value_f_l_u[] = {90, 90, 75, 75};
// int angle_value_f_l_l[] = {90, 30, 30, 90};
// int angle_value_f_r_u[] = {105, 105, 90, 90};
// int angle_value_f_r_l[] = {150, 90, 90, 150};
// int angle_value_b_l_u[] = {75, 75, 90, 90};
// int angle_value_b_l_l[] = {30, 90, 90, 30};
// int angle_value_b_r_u[] = {90, 90, 105, 105};
// int angle_value_b_r_l[] = {90, 150, 150, 90};

int angle_value_f_l_u[] = {105, 105, 105, 105, 100, 95, 90, 90, 90, 90, 95, 100};
int angle_value_f_l_l[] = {150, 130, 110, 90, 90, 90, 90, 110, 130, 150, 150, 150};
int angle_value_f_r_u[] = {90, 90, 90, 90, 85, 80, 75, 75, 75, 75, 80, 85};
int angle_value_f_r_l[] = {90, 70, 50, 30, 30, 30, 30, 50, 70, 90, 90, 90};

int angle_value_b_l_u[] = {90, 90, 90, 90, 95, 100, 105, 105, 105, 105, 100, 95};
int angle_value_b_l_l[] = {90, 110, 130, 150, 150, 150, 150, 130, 110, 90, 90, 90};
int angle_value_b_r_u[] = {75, 75, 75, 75, 80, 85, 90, 90, 90, 90, 85, 80};
int angle_value_b_r_l[] = {30, 50, 70, 90, 90, 90, 90, 70, 50, 30, 30, 30};

int angle_time[] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

void setup() {
 
  // define pins for servo
  servo_f_l_u.attach(13);    
  servo_f_l_l.attach(12); 
  servo_f_r_u.attach(11);
  servo_f_r_l.attach(10);
  servo_b_l_u.attach(9); 
  servo_b_l_l.attach(8); 
  servo_b_r_u.attach(7);
  servo_b_r_l.attach(6);
  
  //send motors to initial angle values 
  servo_f_l_u.write(initial_angle_value_f_l_u);    
  servo_f_l_l.write(initial_angle_value_f_l_l); 
  servo_f_r_u.write(initial_angle_value_f_r_u);
  servo_f_r_l.write(initial_angle_value_f_r_l);
  servo_b_l_u.write(initial_angle_value_b_l_u); 
  servo_b_l_l.write(initial_angle_value_b_l_l); 
  servo_b_r_u.write(initial_angle_value_b_r_u);
  servo_b_r_l.write(initial_angle_value_b_r_l);
  
  //wait for 2 seconds
  delay(500); 
  
}

void loop() {

  for (int i=0;i<gait_steps;i++){        
    
  //send motors to gait an angles 
    servo_f_l_u.write(90);    
    servo_f_l_l.write(90); 
    servo_f_r_u.write(90);
    servo_f_r_l.write(90);
    servo_b_l_u.write(90); 
    servo_b_l_l.write(90); 
    servo_b_r_u.write(90);
    servo_b_r_l.write(90);
    
  //wait for motors to reach angles 
    delay(angle_time[i]);
  }
}