#include <Servo.h>
// pin to read voltage input 
const int analogPin = 34;

Servo servo_arm;
Servo servo_wrist_x;
Servo servo_wrist_y;
Servo servo_wrist_twist;
Servo servo_index;
Servo servo_middle;
Servo servo_ring;
Servo servo_thumb;
Servo servo_pinky;

  // start arm in same position each time 
int degrees_arm = 0; // wrist starts fully extended
int degrees_wrist_x = 60; //wrist starts in the middle
int degrees_wrist_y = 60; //wrist starts in the middle
int degrees_wrist_twist = 0; // wrist starts palm down
int degrees_index = 0; //finger starts fully extended
int degrees_middle = 0; //finger starts fully extended
int degrees_ring = 0; //finger starts fully extended
int degrees_pinky = 0; //finger starts fully extended
int degrees_thumb = 0; //finger starts fully extended


void setup() {
  // set up code
  Serial.begin(115200); // Start serial communication
  pinMode(analogPin, INPUT); // Configure the pin as an input

  servo_arm.attach(26);

  servo_wrist_x.attach(13);
  servo_wrist_y.attach(14);
  servo_wrist_twist.attach(16);

  servo_index.attach(4);
  servo_middle.attach(5);
  servo_ring.attach(25);
  servo_pinky.attach(27);
  servo_thumb.attach(32);
  
}


// speed is 1 degree1 / 20 milliseconds for all functions

// function for the motion of the arm (0-270)
// gear ratio of 1:1/4

int arm_extend_up(int degrees){
  degrees += 1;
  if (degrees > 270){
    degrees = 270;
  }
  servo_arm.write(degrees);
  delay(20);
  return degrees;
  }

  int arm_extend_down(int degrees){
    degrees -= 1;
    if (degrees < 0){
      degrees = 0;
    }
    servo_arm.write(degrees);
    delay(20); 
    return degrees;
  }

/*
twists wrist to the right by increments of 5 degrees
0 is palm down, 180 is palm up
*/
int wrist_twist_right(int degrees){
   degrees += 1;
    if (degrees > 180){
      degrees = 180;
    }
    servo_wrist_twist.write(degrees);
    delay(20); 
    return degrees;
}

/*
twists wrist to the left by increments of 5 degrees
0 is palm down, 180 is palm up
*/
int wrist_twist_left(int degrees){
  degrees -= 1;
  if (degrees < 0){
    degrees = 0;
  }
  servo_wrist_twist.write(degrees);
  delay(20); // half a second for the motion to be completed
  return degrees;
}

/*
turns wrist to the left or down by increments of 5 degrees
0 is wrist all the way to the left or all the way down
*/
int wrist_negative(int degrees, Servo &servo_name){
  degrees -= 1;
  if (degrees < 0){
    degrees = 0;
  }
  servo_name.write(degrees);
  delay(20); // half a second for the motion to be completed
  return degrees;
}

/*
turns wrist to the right or up by increments of 5 degrees
120 is wrist all the way to the right or all the way up
*/
int wrist_positive(int degrees, Servo &servo_name){
    degrees += 1;
    if (degrees > 120){
      degrees = 120;
    }
  servo_name.write(degrees);
  delay(20); // half a second for the motion to be completed
  return degrees;
}

int finger_up(int degrees, Servo &servo_name){
   degrees += 1;
  if (degrees > 90) {  // Assuming max bend is 90 degrees
    degrees = 90;
  }
  servo_name.write(degrees); // update the servo
  delay(20);
  return degrees;
}

int finger_down(int degrees, Servo &servo_name){
   degrees -= 1;
  if (degrees < 0) {  // Assuming 0 is fully extended
    degrees = 0;
  }
  servo_name.write(degrees);
  delay(20);
  return degrees;
}


void loop() {
  int analogValue = analogRead(analogPin); // Read the analog value
  float voltage = (float)analogValue / 4095.0 * 3.3; // Assuming 3.3V reference voltage
  Serial.print("Analog value: ");
  Serial.print(analogValue);
  Serial.print(" Voltage: ");
  Serial.println(voltage);
  delay(1000);
  
  servo_arm.write(degrees_arm);
  servo_wrist_x.write(degrees_wrist_x);
  servo_wrist_y.write(degrees_wrist_y);
  servo_wrist_twist.write(degrees_wrist_twist);
  servo_index.write(degrees_index);
  servo_middle.write(degrees_middle);
  servo_ring.write(degrees_ring);
  servo_thumb.write(degrees_thumb);
  servo_pinky.write(degrees_pinky);
  
  // arm
  if (voltage < .28){
  degrees_arm =  arm_extend_up(degrees_arm);
  }
  else if (voltage < .56 && voltage > .28){
    degrees_arm = arm_extend_down(degrees_arm);
  }

  //wrist twisting
  else if (voltage < .84 && voltage > .56){
   degrees_wrist_twist = wrist_twist_right(degrees_wrist_twist);
  }
  else if (voltage < 1.12 && voltage > .84){
   degrees_wrist_twist = wrist_twist_left(degrees_wrist_twist);
  }

  //wrist left and right movement
  else if (voltage < 1.4 && voltage > 1.12 ){
   degrees_wrist_x = wrist_positive(degrees_wrist_x,servo_wrist_x);
  }
  else if (voltage < 1.68 && voltage > 1.4 ){
   degrees_wrist_x = wrist_negative(degrees_wrist_x,servo_wrist_x);
  }

  //wrist up and down movement
  else if (voltage < 1.96 && voltage > 1.68){
   degrees_wrist_y = wrist_positive(degrees_wrist_y,servo_wrist_y);
  }
  else if (voltage < 2.24 && voltage > 1.96){
   degrees_wrist_y = wrist_negative(degrees_wrist_y,servo_wrist_y);
  }

  // index finger movement 
  else if (voltage < 2.52 && voltage > 2.24){
    degrees_index = finger_up(degrees_index, servo_index);
  }
  else if (voltage < 2.8 && voltage > 2.52){
   degrees_index = finger_down(degrees_index, servo_index);
  }

  // middle finger movement 
  else if (voltage < 3.08 && voltage > 2.8){
   degrees_middle = finger_up(degrees_middle, servo_middle);
  }
  else if (voltage < 3.36 && voltage > 3.08){
   degrees_middle = finger_down(degrees_middle, servo_middle);
  }

  // ring finger movement 
  else if (voltage < 3.64 && voltage > 3.36){
  degrees_ring = finger_up(degrees_ring, servo_ring);

  }
  else if (voltage < 3.92 && voltage > 3.64){
  degrees_ring = finger_down(degrees_ring, servo_ring);
  }

  // pinky finger movement 
  else if (voltage < 4.2 && voltage > 3.92){
   degrees_pinky = finger_up(degrees_pinky, servo_pinky);
  }
  else if (voltage < 4.48 && voltage > 4.2){
   degrees_pinky = finger_down(degrees_pinky, servo_pinky);
  }

  // thumb movement 
  else if (voltage < 4.76 && voltage > 4.48){
    degrees_thumb = finger_up(degrees_thumb, servo_thumb);
  }

  else if (voltage < 5 && voltage > 4.76){
   degrees_thumb = finger_down(degrees_thumb, servo_thumb);
  }

}

