#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define CommonSenseMetricSystem
//#define ImperialNonsenseSystem
#define trigPin 13
#define echoPin 12
#define OLED_RESET -1
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void setup() {
 Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
 display.clearDisplay();
}
void loop() {
 long duration, distance;
 digitalWrite(trigPin, LOW);  //PULSE ___|---|___
 delayMicroseconds(2); 
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 #ifdef CommonSenseMetricSystem
 distance = (duration/2) / 29.1;
 #endif
 #ifdef ImperialNonsenseSystem
 distance = (duration/2) / 73.914;
 #endif
 display.setCursor(22,20);  //oled display
 display.setTextSize(3);
 display.setTextColor(WHITE);
 display.println(distance);
 display.setCursor(75,20);
 display.setTextSize(3);
 #ifdef CommonSenseMetricSystem
 display.println("cm");
 #endif
 #ifdef ImperialNonsenseSystem
 display.println("in");
 #endif
 display.display();
 delay(500);
 display.clearDisplay();
 Serial.println(distance);//debug
}