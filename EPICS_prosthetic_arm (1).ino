
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

// function for the motion of the arm (0-150)
void arm_extend(int degrees){
  degrees = degrees/2;
  if (degrees >75){
    degrees = 75;
  }
  servo_arm.write(degrees);
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
  int action;
  int degrees;
  //(1 = arm, 2 = wrist_z, 3 = wrist_x, 4 = wrist_y, 5 = index, 6 = middle, 7 = ring, 8 = pinky, 9 = thumb)
  std::cout << "Enter an action: ";
  std::cin >> action;
  std::cout << "Enter the degrees: ";
  std::cin >> degrees;

  if (action = 1){
    arm_extend(degrees);
  }
  else if (action = 2){
    wrist_z(degrees);
  }
  else if (action = 3){
    wrist_x(degrees);
  }
  else if (action = 4){
    wrist_y(degrees);
  }
  else if (action = 5){
    index_finger(degrees);
  }
  else if (action = 6){
    middle_finger(degrees);
  }
  else if (action = 7){
    ring_finger(degrees);
  }
  else if (action = 8){
    pinky_finger(degrees);
  }
  else if (action = 9){
    thumb(degrees);
  }
  else {
    std::cout << "Please input a valid action number" << std::endl;
  }

}
