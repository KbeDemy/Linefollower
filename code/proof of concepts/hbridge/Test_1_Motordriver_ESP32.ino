#include <TB6612.h>

// Pinconfiguratie voor TB6612
const uint8_t pwmA = 25;
const uint8_t in1A = 17;
const uint8_t in2A = 16;

const uint8_t pwmB = 26;
const uint8_t in1B = 18;
const uint8_t in2B = 19;


// Maak MotorDriver object
MotorDriver motors(pwmA, in1A, in2A, pwmB, in1B, in2B);


void setup() {
  Serial.begin(115200);
  motors.motor_init(); // Initialize motor driver
}
  

void loop() {
  for(int i = -255; i < 255; i++){
    motors.set_speed(i,-i);
  }
}
