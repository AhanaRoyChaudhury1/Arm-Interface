
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
  servo_wrist_twist.attach(10);

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

// speed is 5 degrees / half second for all functions

// function for the motion of the arm (0-150)
// gear ratio of 1:2
void arm_extend_up(int degrees){
  degrees += 5;
  if (degrees > 75){
    degrees = 75;
  }
  servo_arm.write(degrees);
  delay(500); // half a second for the motion to be completed
  return degrees;
}

void arm_extend_down(int degrees){
  degrees -= 5;
  if (degrees < 0){
    degrees = 0;
  }
  servo_arm.write(degrees);
  delay(500); // half a second for the motion to be completed
  return degrees;
}

/*
twists wrist to the right by increments of 5 degrees
0 is palm down, 180 is palm up
*/
void wrist_twist_right(int degrees){
   degrees += 5;
    if (degrees > 180){
      degrees = 180;
    }
  servo_wrist_twist(degrees);
  delay(500); // half a second for the motion to be completed
  return degrees;
}

/*
twists wrist to the left by increments of 5 degrees
0 is palm down, 180 is palm up
*/
void wrist_twist_left(int degrees){
  degrees -= 5;
  if (degrees < 0){
    degrees = 0;
  }
  servo_wrist_twist(degrees);
  delay(500); // half a second for the motion to be completed
  return degrees;
}

/*
turns wrist to the left or down by increments of 5 degrees
-60 is wrist all the way to the left or all the way down
*/
void wrist_negative(int degrees){
  degrees -= 5;
  if (degrees < -60){
    degrees = 60;
  }
  servo_wrist_twist(degrees);
  delay(500); // half a second for the motion to be completed
  return degrees;
}

/*
turns wrist to the right or up by increments of 5 degrees
60 is wrist all the way to the right or all the way up
*/
void wrist_positive(int degrees){
    degrees += 5;
    if (degrees > 60){
      degrees = 60;
    }
  servo_wrist_twist(degrees);
  delay(500); // half a second for the motion to be completed
  return degrees;
}

void index_finger_up(int degrees){
  
}
void index_finger_down(int degrees){
  
}

void middle_finger_up(int degrees){
  
}
void middle_finger_down(int degrees){
  
}

void ring_finger_up(int degrees){
  
}
void ring_finger_down(int degrees){
  
}

void pinky_finger_up(int degrees){
  
}
void pinky_finger_down(int degrees){
  
}

void thumb_up(int degrees){
  
}
void thumb_down(int degrees){
  
}

void loop() {
  int voltage = analogRead(analogPin);

  // start arm in same position each time 
  start_position();
  int degrees_arm = 0;
  int degrees_wrist_x = 0;
  int degrees_wrist_y = 0;
  int degrees_wrist_twist = 0;
  int degrees_index = 0;
  int degrees_middle = 0;
  int degrees_ring = 0;
  int degrees_pinky = 0;
  int degrees_thumb = 0;
  
  // arm
  while (voltage < .28){
    degrees_arm = arm_extend_up(degrees_arm);
  }
  while (voltage < .56 and voltage > .28){
    degrees_arm = arm_extend_down(degrees_arm);
  }

  //wrist twisting
  while (voltage < .84 and voltage > .56){
    degrees_wrist_twist = wrist_twist_right(degrees_wrist_twist);
  }
  while (voltage < 1.12 and voltage > .84){
    degrees_wrist_twist = wrist_twist_left(degrees_wrist_twist);
  }

  //wrist left and right movement
  while (voltage < 1.4 and voltage > 1.12 ){
    degrees_wrist_x = wrist_positive(degrees_wrist_x);
  }
  while (voltage < 1.68 and voltage > 1.4 ){
    degrees_wrist_x = wrist_negative(degrees_wrist_x);
  }

  //wrist up and down movement
  while (voltage < 1.96 and voltage > 1.68){
    degrees_wrist_y = wrist_positive(degrees_wrist_y);
  }
  while (voltage < 2.24 and voltage > 1.96){
    degrees_wrist_y = wrist_negative(degrees_wrist_y);
  }

  // index finger movement 
  while (voltage < 2.52 and voltage > 2.24){
    degrees_index = index_finger_up(degrees_index);
  }
  while (voltage < 2.8 and voltage > 2.52){
    degrees_index = index_finger_down(degrees_index);
  }

  // middle finger movement 
  while (voltage < 3.08 and voltage > 2.8){
    degrees_middle = middle_finger_up(degrees_middle);
  }
  while (voltage < 3.36 and voltage > 3.08){
    degrees_middle = middle_finger_down(degrees_middle);
  }

  // ring finger movement 
  while (voltage < 3.64 and voltage > 3.36){
    degrees_ring = ring_finger_up(degrees_ring);
  }
  while (voltage < 3.92 and voltage > 3.64){
    degrees_ring = ring_finger_down(degrees_ring);
  }

  // pinky finger movement 
  while (voltage < 4.2 and voltage > 3.92){
    degrees_pinky = pinky_finger_up(degrees_pinky);
  }
  while (voltage < 4.48 and voltage > 4.2){
    degrees_pinky = pinky_finger_up(degrees_pinky);
  }

  // thumb movement 
  while (voltage < 4.76 and voltage > 4.48){
    degrees_thumb = thumb_up(degrees_thumb);
  }

  while (voltage < 5 and voltage > 4.76){
    degrees_thumb = thumb_down (degrees_thumb);
  }

}
