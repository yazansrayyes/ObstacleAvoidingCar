#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <AFMotor.h>  
#include <Servo.h> 

#define TRIG_PIN 2
#define ECHO_PIN 3
#define MAX_DISTANCE 200 // Just a definition in case you need it for setup.
#define SAFE_THRESHOLD 13 // Adjust as needed based on your environment
#define TURN_THRESHOLD 10 // Threshold for determining which direction to turn

#define MAX_SPEED 80 // sets speed of DC motors
#define MAX_SPEED_OFFSET 20

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Connect four motors to ports M1, M2, M3, and M4
Adafruit_DCMotor *motorA = AFMS.getMotor(1);
Adafruit_DCMotor *motorB = AFMS.getMotor(2);
Adafruit_DCMotor *motorC = AFMS.getMotor(3);
Adafruit_DCMotor *motorD = AFMS.getMotor(4);

Servo myservo;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  myservo.attach(10);  
  myservo.write(90); // Initially point the servo straight ahead
  delay(100);
  AFMS.begin();  // Start the motor shield
  motorA->setSpeed(MAX_SPEED);
  motorB->setSpeed(MAX_SPEED);
  motorC->setSpeed(MAX_SPEED);
  motorD->setSpeed(MAX_SPEED);
  motorB->run(BACKWARD);

}

void loop() {

  // Activate the ultrasonic distance sensor to continuously scan for obstacles
  moveForward();
  long distance = measureDistance();

  if (distance < SAFE_THRESHOLD) {
    // Obstacle detected
    stopMotors();
    delay(500);
    reverse();
    delay(1500); // Brief pause before reversing
    stopMotors();
    delay(500); // Pause to reevaluate
    // Analyze Direction
    int rightDistance = measureRightDistance();
    int leftDistance = measureLeftDistance();
    // Path Decision
    if (rightDistance > leftDistance + TURN_THRESHOLD) {
      // Turn right
      turnRight();
    } else if (leftDistance > rightDistance + TURN_THRESHOLD) {
      // Turn left
      turnLeft();
    }
    else{
      reverse();
    }
    stopMotors();
  } 

  else {
    // Move Forward
    moveForward();
  }
}

// Function to measure distance to the nearest object
long measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, MAX_DISTANCE * 58.0);
  long distance = duration * 0.034 / 2.0;
  if (distance > MAX_DISTANCE || distance ==0) {
    distance = MAX_DISTANCE; // Cap the distance at the MAX_DISTANCE if it's larger
  }
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

// Function to measure distance to the right
int measureRightDistance() {
  myservo.write(0); // Turn the servo to the right
  delay(1000); // Wait for the servo to stabilize
  int distance = measureDistance();
  myservo.write(90); // Reset the servo to the center position
  return distance;
}

// Function to measure distance to the left
int measureLeftDistance() {
  myservo.write(180); // Turn the servo to the left
  delay(1000); // Wait for the servo to stabilize
  int distance = measureDistance();
  myservo.write(90); // Reset the servo to the center position
  return distance;
}

// Function to move the vehicle forward
void moveForward() {
  motorA->run(FORWARD);
  motorB->run(FORWARD);
  motorC->run(FORWARD);
  motorD->run(FORWARD);
}

// Function to stop the vehicle
void stopMotors() {
  motorA->run(RELEASE);
  motorB->run(RELEASE);
  motorC->run(RELEASE);
  motorD->run(RELEASE);
}

// Function to move the vehicle backward
void reverse() {
  motorA->run(BACKWARD);
  motorB->run(BACKWARD);
  motorC->run(BACKWARD);
  motorD->run(BACKWARD);
}

void turnRight() {
  motorA->setSpeed(200);   // Back left motor moves backward
  motorB->setSpeed(MAX_SPEED / 2);   // Back right motor moves backward
  motorC->setSpeed(MAX_SPEED / 2); // Front right motor moves forward at half speed
  motorD->setSpeed(200); // Front left motor moves forward at half speed
  motorA->run(FORWARD);
  motorB->run(BACKWARD);
  motorC->run(BACKWARD);
  motorD->run(FORWARD);
  motorA->setSpeed(MAX_SPEED);
  motorB->setSpeed(MAX_SPEED);
  motorC->setSpeed(MAX_SPEED);
  motorD->setSpeed(MAX_SPEED);
}

// Function to turn the vehicle left
void turnLeft() {
  motorA->setSpeed(MAX_SPEED / 2); // Back left motor moves backward at half speed
  motorB->setSpeed(200); // Back right motor moves backward at half speed
  motorC->setSpeed(200);   // Front right motor moves forward
  motorD->setSpeed(MAX_SPEED / 2);   // Front left motor moves forward
  motorA->run(BACKWARD);
  motorB->run(FORWARD);
  motorC->run(FORWARD);
  motorD->run(BACKWARD);
  motorA->setSpeed(MAX_SPEED);
  motorB->setSpeed(MAX_SPEED);
  motorC->setSpeed(MAX_SPEED);
  motorD->setSpeed(MAX_SPEED);
}
