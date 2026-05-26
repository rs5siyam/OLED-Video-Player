#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "video_frames.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDR     0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int FRAME_DELAY_MS = 66;
const bool LOOP_VIDEO = true;

void showSimpleCountdown() {
  // Draw countdown circle animation
  for (int i = 3; i > 0; i--) {
    display.clearDisplay();
    
    // Draw circular progress (simulated with rectangles)
    display.drawCircle(64, 32, 25, SSD1306_WHITE);
    
    // Draw filled portion based on countdown
    float angle = (3 - i) * 120;  // 0, 120, 240 degrees
    for (int a = 0; a < angle; a += 10) {
      float rad = a * 3.14159 / 180;
      int x = 64 + 20 * cos(rad);
      int y = 32 + 20 * sin(rad);
      display.drawPixel(x, y, SSD1306_WHITE);
    }
    
    // Show number
    display.setTextSize(3);
    display.setCursor(58, 25);
    display.print(i);
    display.display();
    delay(1000);
  }
  
  // Flash "GO"
  for (int flash = 0; flash < 2; flash++) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(52, 28);
    display.print("GO!");
    display.display();
    delay(100);
    display.clearDisplay();
    display.display();
    delay(50);
  }
}

void playVideo() {
  // First show countdown
  showSimpleCountdown();
  
  // Then play all frames
  for (int i = 0; i < TOTAL_FRAMES; i++) {
    display.clearDisplay();
    display.drawBitmap(0, 0, FRAMES[i], SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
    display.display();
    delay(FRAME_DELAY_MS);
  }
}

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
}

void loop() {
  playVideo();
  if (LOOP_VIDEO) delay(1000);
  else while(1);
}