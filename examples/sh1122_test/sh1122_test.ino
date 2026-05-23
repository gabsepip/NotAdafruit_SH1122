#include <NotAdafruit_SH1122.h>

// Used for software SPI
#define OLED_CLK 13
#define OLED_MOSI 11

// Used for software or hardware SPI
#define OLED_CS 17
#define OLED_DC 20

// Used for I2C or SPI
#define OLED_RESET 21

// software SPI UNTESTED
//Adafruit_SH1122 display(128, 128, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
// hardware SPI
Adafruit_SH1122 display(256, 64, &SPI, OLED_DC, OLED_RESET, OLED_CS);

// I2C UNTESTED
// Adafruit_SH1122 display(128, 128, &Wire, OLED_RESET, 1000000);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };


void setup() {
  Serial.begin(115200);
  while (!Serial) delay(100);
  Serial.println("SSD1327 OLED test");

  if (!display.begin()) {
    Serial.println("Unable to initialize OLED");
    while (1) yield();
  }
  display.clearDisplay();
  display.display();

  // draw many lines
  Serial.println("LINES");
  delay(100);
  Serial.flush();
  testdrawline();
  display.display();
  Serial.println("DONE");
  delay(1000);
  display.clearDisplay();

  // draw rectangles
  Serial.println("RECTANGLES");
  delay(100);
  Serial.flush();
  testdrawrect();
  display.display();
  Serial.println("DONE");
  delay(1000);
  display.clearDisplay();

  // draw multiple rectangles
  Serial.println("FILLED RECTANGLES");
  delay(100);
  Serial.flush();
  testfillrect();
  display.display();
  Serial.println("DONE");
  delay(1000);
  display.clearDisplay();

  // draw mulitple circles
  Serial.println("CIRCLES");
  delay(100);
  Serial.flush();
  testdrawcircle();
  display.display();
  Serial.println("DONE");
  delay(1000);
  display.clearDisplay();

  // draw a SSD1327_WHITE circle, 10 pixel radius
  Serial.println("ONE CIRCLE");
  delay(100);
  Serial.flush();
  display.fillCircle(display.width() / 2, display.height() / 2, 10, SSD1327_WHITE);
  display.display();
  Serial.println("DONE");
  delay(1000);
  display.clearDisplay();

  Serial.println("ROUND RECT");
  delay(100);
  Serial.flush();
  testdrawroundrect();
  delay(1000);
  display.clearDisplay();

  Serial.println("FILL ROUND RECT");
  delay(100);
  Serial.flush();
  testfillroundrect();
  delay(1000);
  display.clearDisplay();

  Serial.println("TRIANGLE");
  delay(100);
  Serial.flush();
  testdrawtriangle();
  delay(1000);
  display.clearDisplay();

  Serial.println("FILL TRIANGLE");
  delay(100);
  Serial.flush();
  testfilltriangle();
  delay(1000);
  display.clearDisplay();

  // draw the first ~12 characters in the font
  Serial.println("DRAW CHAR");
  delay(100);
  Serial.flush();
  testdrawchar();
  display.display();
  delay(1000);
  display.clearDisplay();

  Serial.println("ROTATION");
  delay(100);
  Serial.flush();
  for (uint8_t rot = 0; rot < 4; rot++) {
    display.setRotation(rot);
    display.clearDisplay();
    // text display tests
    display.setTextSize(1);
    display.setTextColor(SSD1327_WHITE);
    display.setCursor(0,0);
    display.println("Hello, world!");
    display.setTextColor(SSD1327_BLACK, SSD1327_WHITE); // 'inverted' text
    display.println(3.141592);
    display.setTextSize(2);
    display.setTextColor(SSD1327_WHITE);
    display.print("0x"); display.println(0xDEADBEEF, HEX);
    display.display();
    delay(1000);
  }

  display.setRotation(0);

  // miniature bitmap display
  Serial.println("LOGO");
  delay(100);
  Serial.flush();
  display.clearDisplay();
  display.drawBitmap(30, 16,  logo16_glcd_bmp, 16, 16, 1);
  display.display();

  // invert the display
  Serial.println("INVERT");
  delay(100);
  Serial.flush();

  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);

  // draw a bitmap icon and 'animate' movement
  testdrawbitmap(logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);
}


void loop() {
}


void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];
  randomSeed(666);  // whatever seed

  // initialize
  for (uint8_t f = 0; f < NUMFLAKES; f++) {
    icons[f][XPOS] = random(display.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;

    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }

  while (1) {
    // draw each icon
    display.clearDisplay();
    for (uint8_t f = 0; f < NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, f + 1);
    }
    display.display();
    // delay(200);

    // then erase it + move it
    for (uint8_t f = 0; f < NUMFLAKES; f++) {
      // display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1327_BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > display.height()) {
        icons[f][XPOS] = random(display.width());
        icons[f][YPOS] = 0;
        icons[f][DELTAY] = random(5) + 1;
      }
    }
  }
}


void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextWrap(false);
  display.setTextColor(SSD1327_WHITE);
  display.setCursor(0, 0);

  for (uint8_t i = 0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }
  display.display();
}

void testdrawcircle(void) {
  for (uint8_t i = 0; i < display.height(); i += 2) {
    display.drawCircle(display.width() / 2, display.height() / 2, i, i % 15 + 1);
    display.display();
  }
}

void testfillrect(void) {
  uint8_t color = 1;
  for (uint8_t i = 0; i < display.height() / 2; i += 3) {
    // alternate colors
    display.fillRect(i, i, display.width() - i * 2, display.height() - i * 2, i % 15 + 1);
    display.display();
    color++;
  }
}

void testdrawtriangle(void) {
  for (uint16_t i = 0; i < min(display.width(), display.height()) / 2; i += 5) {
    display.drawTriangle(display.width() / 2, display.height() / 2 - i,
                         display.width() / 2 - i, display.height() / 2 + i,
                         display.width() / 2 + i, display.height() / 2 + i, i % 15 + 1);
    display.display();
  }
}

void testfilltriangle(void) {
  // uint8_t color = SSD1327_WHITE;
  for (int16_t i = min(display.width(), display.height()) / 2; i > 0; i -= 5) {
    display.fillTriangle(display.width() / 2, display.height() / 2 - i,
                         display.width() / 2 - i, display.height() / 2 + i,
                         display.width() / 2 + i, display.height() / 2 + i, i % 15 + 1);
    display.display();
  }
}

void testdrawroundrect(void) {
  for (uint8_t i = 0; i < display.height() / 3 - 2; i += 2) {
    display.drawRoundRect(i, i, display.width() - 2 * i, display.height() - 2 * i, display.height() / 4, i % 15 + 1);
    display.display();
  }
}

void testfillroundrect(void) {
  // uint8_t color = SSD1327_WHITE;
  for (uint8_t i = 0; i < display.height() / 3 - 2; i += 2) {
    display.fillRoundRect(i, i, display.width() - 2 * i, display.height() - 2 * i, display.height() / 4, i % 15 + 1);
    display.display();
  }
}

void testdrawrect(void) {
  for (uint8_t i = 0; i < display.height() / 2; i += 2) {
    display.drawRect(i, i, display.width() - 2 * i, display.height() - 2 * i, i % 15 + 1);
    display.display();
  }
}

void testdrawline() {
  Serial.println("LINES 0");
  Serial.println("vertical");
  for (uint16_t i = 0; i < display.width(); i += 4) {
    Serial.print(" ");
    Serial.print(i);
    display.drawLine(i, 0, i, display.height() - 1, SSD1327_WHITE);
    display.display();
  }
  Serial.println();
  Serial.println("horizontal");
  for (uint16_t i = 0; i < display.height(); i += 4) {
    Serial.print(" ");
    Serial.print(i);
    display.drawLine(0, i, display.width() - 1, i, SSD1327_WHITE);
    display.display();
  }
  Serial.println();
  delay(250);

  display.clearDisplay();


  Serial.println("LINES 1");
  Serial.print("width ");
  Serial.println(display.width());
  Serial.print("height ");
  Serial.println(display.height());
  for (uint16_t i = 0; i < display.width(); i += 4) {
    Serial.print(" ");
    Serial.print(i);
    display.drawLine(0, 0, i, display.height() - 1, SSD1327_WHITE);
    display.display();
  }
  Serial.println();
  for (uint16_t i = 0; i < display.height(); i += 4) {
    Serial.print(" ");
    Serial.print(i);
    display.drawLine(0, 0, display.width() - 1, i, SSD1327_WHITE);
    display.display();
  }
  Serial.println();
  delay(250);

  Serial.println("LINES 2");
  display.clearDisplay();
  for (uint16_t i = 0; i < display.width(); i += 4) {
    display.drawLine(0, display.height() - 1, i, 0, SSD1327_WHITE);
    display.display();
  }
  for (int16_t i = display.height() - 1; i >= 0; i -= 4) {
    display.drawLine(0, display.height() - 1, display.width() - 1, i, SSD1327_WHITE);
    display.display();
  }
  delay(250);

  Serial.println("LINES 3");
  display.clearDisplay();
  for (int8_t i = display.width() - 1; i >= 0; i -= 4) {
    display.drawLine(display.width() - 1, display.height() - 1, i, 0, SSD1327_WHITE);
    display.display();
  }
  for (int8_t i = display.height() - 1; i >= 0; i -= 4) {
    display.drawLine(display.width() - 1, display.height() - 1, 0, i, SSD1327_WHITE);
    display.display();
  }
  delay(250);

  Serial.println("LINES 4");
  display.clearDisplay();
  for (uint16_t i = 0; i < display.height(); i += 4) {
    display.drawLine(display.width() - 1, 0, 0, i, SSD1327_WHITE);
    display.display();
  }
  for (uint16_t i = 0; i < display.width(); i += 4) {
    display.drawLine(display.width() - 1, 0, i, display.height() - 1, SSD1327_WHITE);
    display.display();
  }
  delay(250);
}