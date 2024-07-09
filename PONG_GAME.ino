#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

const unsigned char THUNDER[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 0xff, 0x9c, 0x00, 0x01, 0xff, 0x1f, 0x00, 
  0x03, 0xff, 0x1f, 0x80, 0x07, 0xfe, 0x3f, 0xc0, 0x0f, 0xfe, 0x3f, 0xe0, 0x1f, 0xfc, 0x3f, 0xe0, 
  0x3f, 0xf8, 0x7f, 0xf0, 0x3f, 0xf8, 0x7f, 0xf0, 0x3f, 0xf0, 0x7f, 0xf8, 0x7f, 0xf0, 0xff, 0xf8, 
  0x7f, 0xe0, 0xff, 0xf8, 0x7f, 0xe0, 0x03, 0xf8, 0x7f, 0xc0, 0x07, 0xfc, 0x7f, 0x80, 0x07, 0xfc, 
  0x7f, 0x80, 0x0f, 0xf8, 0x7f, 0xfc, 0x0f, 0xf8, 0x7f, 0xfc, 0x1f, 0xf8, 0x7f, 0xfc, 0x3f, 0xf8, 
  0x3f, 0xf8, 0x3f, 0xf8, 0x3f, 0xf8, 0x7f, 0xf0, 0x1f, 0xf8, 0x7f, 0xf0, 0x1f, 0xf8, 0xff, 0xe0, 
  0x0f, 0xf0, 0xff, 0xc0, 0x07, 0xf1, 0xff, 0x80, 0x03, 0xf3, 0xff, 0x00, 0x00, 0xe3, 0xfe, 0x00, 
  0x00, 0x27, 0xf8, 0x00, 0x00, 0x03, 0x00, 0x00
};

const int thunderSize = 31; // Size of the thunder image
const int thunderColor = SSD1306_WHITE;

// Ball parameters
int ballX = SCREEN_WIDTH / 2;   // Initial x position of the ball
int ballY = SCREEN_HEIGHT / 2;  // Initial y position of the ball
int dx = 1;       // Movement increment for x
int dy = 1;       // Movement increment for y

void setup() {
  Serial.begin(9600);
  Serial.println("OLED begun");

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.display();
  delay(1000);

  Serial.println("IO test");
}

void drawThunder(int x, int y) {
  display.drawBitmap(x, y, THUNDER, thunderSize, thunderSize, thunderColor);
}

void loop() {
  display.clearDisplay();

  // Update the position of the ball
  ballX += dx;
  ballY += dy;

  // Reverse direction if hitting the display edges
  if (ballX <= thunderSize / 2 || ballX >= SCREEN_WIDTH - thunderSize / 2) {
    dx = -dx;
  }
  if (ballY <= thunderSize / 2 || ballY >= SCREEN_HEIGHT - thunderSize / 1.25) {
    dy = -dy;
  }

  // Draw thunder at its current position
  drawThunder(ballX - thunderSize / 2, ballY - thunderSize / 2);

  // Read battery level from A0 pin
  int batteryLevel = analogRead(A0);
  // Calculate battery percentage
  int batteryPercent = map(batteryLevel, 0, 1023, 0, 100);
  
  display.setCursor(ballX - 9, ballY + thunderSize / 2 + 2);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("");
  display.print(batteryPercent);
  display.println("%");

  // Send the buffer to the display
  display.display();

  delay(50);
}
