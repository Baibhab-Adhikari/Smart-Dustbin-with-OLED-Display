#include <Servo.h>
#include <Wire.h>
#include <U8g2lib.h> // Include the U8g2 library
#define SDA_PIN D2
#define SCL_PIN D1

// Ultrasonic sensor pins
const int trigPin1 = D5;
const int echoPin1 = D6;
const int trigPin2 = D3;
const int echoPin2 = D4;

// Maximum distance between trash and ultrasonic sensor for an empty dustbin
const float maxDistance = 19.0; // Adjust this value according to the height of your dustbin

// Create servo object (2 servos for more support. Optional)
Servo servo1;
Servo servo2;

// Create U8g2 display object
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL_PIN, /* data=*/ SDA_PIN, /* reset=*/ U8X8_PIN_NONE);


void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  Serial.println("Ultrasonic Sensor Test");
  
  // Initialize ultrasonic sensor pins
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  // Initialize servo1 and servo2
  servo1.attach(D7); // Assuming the servo is connected to pin D7
  servo1.write(90); // Initially set servo to center position (90 degrees)

  servo2.attach(D8); // Assuming the servo is connected to pin D8
  servo2.write(90); // Initially set servo to center position (90 degrees)


  // Initialize OLED display
  u8g2.begin();
}

void loop() {
  // Measure distance for hand detection
  long duration1, distance1;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;

  // Measure distance for garbage level
  long duration2, distance2;
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;

  // Print distances to Serial Monitor
  Serial.print("Hand Distance: ");
  Serial.print(distance1);
  Serial.println(" cm");
  Serial.print("Garbage Level Distance: ");
  Serial.print(distance2);
  Serial.println(" cm");

  // Check if hand is near
  if (distance1 < 20) { // Adjust the threshold distance as needed
    Serial.println("Hand detected. Opening the dustbin lid.");
    // Open the dustbin lid
    openLid();
    delay(3000); // Keep the lid open for 2 seconds

    // Close the dustbin lid
    Serial.println("Closing the dustbin lid.");
    closeLid();
  }
  else {
    // If hand is not detected, stop servo rotation
    stopServo();
  }

  // Calculate garbage level percentage
  float garbageLevelPercentage = ((maxDistance - distance2) / maxDistance) * 100;
  Serial.print("Garbage Level Percentage: ");
  Serial.print(garbageLevelPercentage);
  Serial.println("%");

  // Display garbage level information on OLED display
  displayGarbageLevel(distance2, garbageLevelPercentage);

  delay(1000); // Adjust delay as needed
}

void openLid() {
  // Rotate servo to fully open position
  servo1.write(180); // Adjust angle as needed for your servo
  servo2.write(180); //second servo doing the same thing
}

void closeLid() {
  // Rotate servo to fully closed position
  servo1.write(0); // Adjust angle as needed for your servo
  servo2.write(0); // second servo doing the same thing
}

void stopServo() {
  // Stop servo rotation
  servo1.write(0); // Set servo to center position
  servo2.write(0);
}

void displayGarbageLevel(float distance, float percentage) {
  // Clear display
  u8g2.clearBuffer();

  // Display garbage level distance in cm
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setCursor(0, 15);
  u8g2.print("Garbage Level: ");
  u8g2.print(distance);
  u8g2.print(" cm");

  // Display garbage level percentage with percentage symbol
  u8g2.setCursor(0, 30);
  u8g2.print("Percentage: ");
  u8g2.print(percentage);
  u8g2.print("%");

  // Send display buffer to OLED
  u8g2.sendBuffer();
}
