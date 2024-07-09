#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
const char* displayText = "RAYCURA";
int textLength = 7; 
int textWidth = textLength * 6; 
int textHeight = 8; 

int xPos = SCREEN_WIDTH; 
int yPos = (SCREEN_HEIGHT - textHeight) / 2; 
void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  // Clear the display buffer
  display.clearDisplay();

  // Set text properties
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}
 int L = 1;
 int c=0;
void loop() {
  String originalWord = displayText;

  // Extract the first three letters
  String firstThreeLetters = originalWord.substring(0, L);
// Print the result
  Serial.println(firstThreeLetters);
  display.clearDisplay(); 
  display.setCursor(xPos-7, yPos);
  display.print(firstThreeLetters);
  display.display();
 c++;// counter.
 if(c==7){ // for smooth movement forward motion. 
  c=0;
  L++;
}
  xPos=xPos-1;
 if (xPos < -textWidth) { // left dissappearance.
   xPos = SCREEN_WIDTH ; // riight appearance.
   L=1;
  }
  delay(50);  
  if(xPos==64-13){// center stop.
    delay(2000);
  }
}
