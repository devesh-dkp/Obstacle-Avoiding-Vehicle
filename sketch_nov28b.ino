#include <NewPing.h>
#include <AFMotor.h>

#define TRIG_PIN A4
#define ECHO_PIN A5
#define MAX_DISTANCE 200
#define MAX_SPEED 90 // Sets speed of DC motors


NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

AF_DCMotor motor1(1, MOTOR12_1KHZ); // First motor to connection 1
AF_DCMotor motor2(2, MOTOR12_1KHZ); // Second motor to connection 2

boolean goesForward = false;
int distance = 100; // Define an int for distance and speed
int speedSet = 0;
void setup() {
distance = readPing(); // Read the distance from the sensor
delay(100);
}

void loop() {
delay(40);
// If distance is less than 10 cm, carry out this function
if (distance <= 10) {
moveStop();
delay(50);
moveBackward();
delay(100);
moveStop();
delay(100);
turnLeft();
moveStop();
} else {
moveForward();
}
distance = readPing();
}

int readPing() {
delay(20);
int cm = sonar.ping_cm();
if (cm == 0) {
cm = 250;
}
return cm;
}
void moveStop() {
motor1.run(RELEASE);
motor2.run(RELEASE);
}
void moveForward() {
if (!goesForward) { // If area is clear, motors move forward
goesForward = true;
motor1.run(FORWARD);
motor2.run(FORWARD);
// Slowly bring up speed to avoid loading down
// batteries too quickly
for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
motor1.setSpeed(speedSet);
motor2.setSpeed(speedSet);
delay(1);}
  }
    }
void moveBackward() {
goesForward = false;
motor1.run(BACKWARD);
motor2.run(BACKWARD);
// Slowly bring up speed to avoid loading down
// batteries too quickly
for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
motor1.setSpeed(speedSet);
motor2.setSpeed(speedSet);
delay(1);
}
}
void turnLeft() { // Movement for turning left
motor1.run(BACKWARD);
motor2.run(FORWARD);
delay(89);
motor1.run(FORWARD);
motor2.run(FORWARD);
}
void turnRight() { // Movement for turning right
motor1.run(FORWARD);
motor2.run(BACKWARD);
delay(89);
motor1.run(FORWARD);
motor2.run(FORWARD);
}