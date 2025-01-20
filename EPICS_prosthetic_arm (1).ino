
/*

*/
#include <ESP32Servo.h>
#include <iostream>

// pin to read voltage input 
const int analogPin = 34;

Servo servo_arm;
Servo servo_wrist_x;
Servo servo_wrist_y;
Servo servo_wrist_z;
Servo servo_index;
Servo servo_middle;
Servo servo_ring;
Servo servo_thumb;
Servo servo_pinky;


void setup() {
  // set up code
  Serial.begin(115200); // Start serial communication
  pinMode(analogPin, INPUT); // Configure the pin as an input

  servo_arm.attach(14);

  servo_wrist_x.attach(12);
  servo_wrist_y.attach(11);
  servo_wrist_z.attach(10);

  servo_index.attach(3);
  servo_middle.attach(8);
  servo_ring.attach(18);
  servo_pinky.attach(17);
  servo_thumb.attach(16);
  
}

// start position of all servos at zero to be able to track position
// might change start position later
void start_position(){
  servo_arm.write(0);
  servo_wrist_x.write(0);
  servo_wrist_y.write(0);
  servo_wrist_z.write(0);
  servo_index.write(0);
  servo_middle.write(0);
  servo_ring.write(0);
  servo_pinky.write(0);
  servo_thumb.write(0);
  
}

// function for the motion of the arm (0-150)
// gear ratio of 1:2
void arm_extend(int degrees){
  degrees += 5;
  if (degrees > 75){
    degrees = 75;
  }
  if (degrees < 0){
    degrees = 0;
  }
  servo_arm.write(degrees);
  delay(500); // half a second for the motion to be completed
  return degrees;
  
}

void wrist_z(int degrees){

}

void wrist_x(int degrees){
  
}

void wrist_y(int degrees){
  
}

void index_finger(int degrees){
  
}

void middle_finger(int degrees){
  
}

void ring_finger(int degrees){
  
}

void pinky_finger(int degrees){
  
}

void thumb(int degrees){
  
}

void loop() {
  int voltage = analogRead(analogPin);

  // start arm in same position each time 
  start_position();
  int degrees_arm = 0;
  int degrees_wrist_x = 0;
  int degrees_wrist_y = 0;
  int degrees_wrist_z = 0;
  int degrees_index = 0;
  int degrees_middle = 0;
  int degrees_ring = 0;
  int degrees_pinky = 0;
  int degrees_thumb = 0;
  

  while (voltage < .56){
    degrees_arm = arm_extend(degrees_arm);
  }
  while (voltage < 1.12 and voltage > .56){
    wrist_z();
  }
  while (voltage < 1.68 and voltage > 1.12 ){
    wrist_x();
  }
  while (voltage < 2.24 and voltage > 1.68){
    wrist_y();
  }
  while (voltage < 2.8 and voltage > 2.24){
    index_finger();
  }
  while (voltage < 3.36 and voltage > 2.8){
    middle_finger();
  }
  while (voltage < 3.92 and voltage > 3.36){
    ring_finger();
  }
  while (voltage < 4.48 and voltage > 3.92){
    pinky_finger();
  }
  while (voltage < 5 and voltage > 4.48){
    thumb();
  }


}
