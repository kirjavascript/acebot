#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int buttonPin = 10;          // input pin for pushbutton
int previousButtonState = HIGH;   // for checking the state of a pushButton
int counter = 0;                  // button push counter
int counter2 = 0;
int frames = 0;

#define RIGHT 11
#define LEFT 1
#define DOWN 8
#define UP 9
#define A 4
#define START 5
#define SELECT 6
#define B 7

#define LATCH 0

void setup() {
  pinMode(buttonPin, INPUT);

  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
    display.clearDisplay();

  display.setTextColor(WHITE);

  display.setTextSize(3);
  display.setCursor(0, 10);
  display.println("acebot");
  display.setTextSize(2);
  display.setCursor(50, 35);
  // Display static text
  display.println("v0.1");
  display.display();

    pinMode(RIGHT, OUTPUT);
    pinMode(LEFT, OUTPUT);
    pinMode(UP, OUTPUT);
    pinMode(DOWN, OUTPUT);
    pinMode(SELECT, OUTPUT);
    pinMode(START, OUTPUT);
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);

    attachInterrupt(digitalPinToInterrupt(LATCH),latch_pulse, FALLING);
    digitalWrite(LEFT, 1);
    digitalWrite(RIGHT, 1);
    digitalWrite(UP, 1);
    digitalWrite(DOWN, 1);
    digitalWrite(START, 1);
    digitalWrite(SELECT, 1);
    digitalWrite(A, 1);
    digitalWrite(B, 1);
}

void latch_pulse() {
  frames++;
  //digitalWrite(LEFT, frames % 2);
  writeButtons(frames);
}

// Write the given button sequence to the shift register
void writeButtons(byte buttons)
{
    digitalWrite(A,      buttons & 1);
    buttons = buttons >> 1;
    digitalWrite(B,      buttons & 1);
    buttons = buttons >> 1;
    digitalWrite(SELECT,      buttons & 1);
    buttons = buttons >> 1;
    digitalWrite(START,      buttons & 1);
    buttons = buttons >> 1;
    digitalWrite(UP,      buttons & 1);
    buttons = buttons >> 1;
    digitalWrite(DOWN,      buttons & 1);
    buttons = buttons >> 1;
    digitalWrite(LEFT,      buttons & 1);
    buttons = buttons >> 1;
    digitalWrite(RIGHT,      buttons & 1);
}



void loop() {
  /*int buttonState = digitalRead(buttonPin);

  if ((buttonState != previousButtonState)
      && (buttonState == HIGH)) {
    counter++;
  }
  // save the current button state for comparison next time:
  previousButtonState = buttonState;*/

/*
  digitalWrite(LEFT, frames % 2);
    digitalWrite(RIGHT, 1);
    digitalWrite(UP, 1);
    digitalWrite(DOWN, 1);
    digitalWrite(START, 1);
    digitalWrite(SELECT, 1);
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    */
    //if (frames % 50 == 0) {
    
  display.fillRect(0, 50, 160, 20, 0);
  display.setCursor(0, 50);
  display.println(frames);
  display.display();
    //}
}
