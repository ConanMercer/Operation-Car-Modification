#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h> //OLED Lib
#include <Adafruit_SSD1306.h> //OLED Lib
#include <NewPing.h> //ultrasonic lib

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define TRIGGER_PIN 16 //ultrasonic pin
#define ECHO_PIN 17 //ultrasonic pin
#define MAX_DISTANCE 200

// NewPing setup of pins and maximum distance
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(22,20);        //x,y coordinates
  display.println("distance");
  display.display();
  // Display static text

}

void loop() {
  unsigned int distance = sonar.ping_cm();
  display.setCursor(22,20);        //x,y coordinates
  display.setTextSize(2);         //size of the text
  display.setTextColor(WHITE);    //if you write BLACK it erases things
  display.println(distance);      //print our variable
  display.setCursor(85,20);       //set size,print the units (cm/in)
  display.setTextSize(2); 
  display.println("cm");        //print "cm" in oled
  display.display();          //you need to actually display all that data
  delay(500);                 //wait!, human speed
  display.clearDisplay();      //clear black the display
}