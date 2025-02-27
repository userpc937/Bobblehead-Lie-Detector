#include <DFRobot_DF1201S.h>
#include <SoftwareSerial.h>
#include <Servo.h>




#define BUTTON1 4  // Button for Track 1
#define BUTTON2 5  // Button for Track 2
#define BUTTON3 6  // Button for Track 3
#define SERVO_PIN 9  // Servo connected to pin 9




SoftwareSerial DF1201SSerial(2, 3);  // RX, TX for DFPlayer Pro
DFRobot_DF1201S DF1201S;
Servo myServo;  // Create servo object




void setup() {
 Serial.begin(115200);
 DF1201SSerial.begin(115200);
 myServo.attach(SERVO_PIN);
 myServo.write(0);  // Set servo to initial position




 // Initialize MP3 player
 while (!DF1201S.begin(DF1201SSerial)) {
   Serial.println("Init failed, check wiring!");
   delay(1000);
 }




 // Set volume and playback mode
 DF1201S.setVol(40);
 DF1201S.switchFunction(DF1201S.MUSIC);
 delay(2000);
 DF1201S.setPlayMode(DF1201S.SINGLE);




 // Configure buttons as inputs with pull-up resistors
 pinMode(BUTTON1, INPUT_PULLUP);
 pinMode(BUTTON2, INPUT_PULLUP);
 pinMode(BUTTON3, INPUT_PULLUP);
}




void loop() {
 int button1State = digitalRead(BUTTON1);
 int button2State = digitalRead(BUTTON2);
 int button3State = digitalRead(BUTTON3);


//violent crime
 if (button1State == LOW) {
   Serial.println("Button 1 Pressed - Playing Track 1 & Moving Servo");
   DF1201S.playFileNum(1);
   waitForAudioToFinish();
 }


//president joe
 if (button2State == LOW) {
   Serial.println("Button 2 Pressed - Playing Track 2");
   DF1201S.playFileNum(2);
   moveServo();  // Move servo for this button
   waitForAudioToFinish();
 }


//cat and dogs
 if (button3State == LOW) {
   Serial.println("Button 3 Pressed - Playing Track 3 & Moving Servo");
   DF1201S.playFileNum(3);
   moveServo();  // Move servo for this button
   waitForAudioToFinish();
 }
}




void moveServo() {
 for (int pos = 0; pos <= 60; pos++) {
   myServo.write(pos);
   delay(5);
 }
 delay(500);
 for (int pos = 60; pos >= 0; pos--) {
   myServo.write(pos);
   delay(5);
 }
}




void waitForAudioToFinish() {
 while (DF1201S.isPlaying()) {
   delay(100);
 }
 delay(200);
}


