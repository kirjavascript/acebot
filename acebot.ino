#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define RIGHT 11
#define LEFT 10
#define DOWN 8
#define UP 9
#define A 4
#define START 5
#define SELECT 6
#define B 12

#define LATCH 7

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

volatile unsigned long frames = 0;
volatile unsigned long frameCount = 0;

byte stream0[256];
byte stream1[256];

void setup() {
    Serial.begin(9600);

    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }

    display.clearDisplay();

    display.setTextColor(WHITE);

    display.setTextSize(3);
    display.setCursor(0, 10);
    display.println("acebot");
    display.setTextSize(2);
    display.setCursor(50, 35);
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

    while (!Serial); // wait for Serial connection (arduino leonardo)
    uint8_t first = 0;
    Serial.write(first);
    Serial.readBytes(stream0, 256);
}

void load_next_chunk() {
    uint8_t next_chunk = (frameCount / 256) + 1;
    Serial.write(next_chunk);
    if (next_chunk % 2 == 0) {
        Serial.readBytes(stream0, 256);
    } else {
        Serial.readBytes(stream1, 256);
    }
}

void latch_pulse() {
    byte buttons;

    if (frameCount % 512 >= 256) {
        buttons = ~stream1[frameCount % 256];
    } else {
        buttons = ~stream0[frameCount % 256];
    }

    if (frames%2==0) { // twice per frame polling
        frameCount++;
    }

    if (false) detachInterrupt(digitalPinToInterrupt(LATCH));

    frames++;
    digitalWrite(A, buttons & 1);
    buttons = buttons >> 1;
    digitalWrite(B, buttons & 1);
    buttons = buttons >> 1;
    digitalWrite(SELECT, buttons & 1);
    buttons = buttons >> 1;
    digitalWrite(START, buttons & 1);
    buttons = buttons >> 1;
    digitalWrite(RIGHT, buttons & 1);
    buttons = buttons >> 1;
    digitalWrite(LEFT, buttons & 1);
    buttons = buttons >> 1;
    digitalWrite(DOWN, buttons & 1);
    buttons = buttons >> 1;
    digitalWrite(UP, buttons & 1);
}

void loop() {
    display.fillRect(0, 50, 160, 20, 0);
    display.setCursor(0, 50);
    display.println(frameCount);
    display.setCursor(0, 33);
    display.fillRect(0, 33, 160, 16, 0);
    display.println(frameCount / 256);
    display.display();
    load_next_chunk();
}
