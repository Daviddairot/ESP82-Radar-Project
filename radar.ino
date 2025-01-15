#include <Servo.h>  // Include the Servo library

// Define Trigger and Echo pins of the Ultrasonic Sensor
const int trigPin = D2;
const int echoPin = D1;

// Variables for the duration and the distance
long duration;
int distance;

Servo myServo;  // Create a servo object for controlling the servo motor

void setup() {
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input
  Serial.begin(9600);        // Starts serial communication at 9600 baud rate
  myServo.attach(D5);        // Defines the pin where the servo motor is attached
  Serial.println("Servo Angle, Distance (cm)");  // Print a header for the output
}

void loop() {
  // Rotate the servo motor from 15 to 165 degrees with smoother increments
  for (int i = 0; i <= 180; i++) {
    myServo.write(i);  // Move the servo to the current angle
    delay(14);          // Reduced delay for smoother movement
    distance = calculateDistance();  // Get the distance from the ultrasonic sensor

    // Print the degree and distance to the Serial Monitor
    printData(i, distance);
  }

  // Repeat the movement from 165 to 15 degrees with smoother increments
  for (int i = 180; i >= 0; i--) {
    myServo.write(i);  // Move the servo to the current angle
    delay(14);          // Reduced delay for smoother movement
    distance = calculateDistance();  // Get the distance from the ultrasonic sensor

    // Print the degree and distance to the Serial Monitor
    printData(i, distance);
  }
}

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance() {
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  
  // Set the trigPin HIGH for 10 microseconds to send the pulse
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);  // Read the echoPin to get the pulse duration
  distance = duration * 0.034 / 2;    // Convert the duration to distance in cm
  return distance;
}

// Function to print the angle and distance to the Serial Monitor
void printData(int angle, int distance) {
  Serial.print("Degree: ");  // Label for the angle
  Serial.print(angle);       // Print the servo's current angle
  Serial.print(", ");        // Separator between angle and distance
  Serial.print("Distance: "); // Label for the distance
  Serial.print(distance);    // Print the distance from the ultrasonic sensor
  Serial.println(" cm");     // Unit of measurement for distance
}
