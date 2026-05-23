/*********************************************************************
This is a library for our Grayscale OLEDs based on SSD1327 drivers

  Pick one up today in the adafruit shop!
  ------> https://www.adafruit.com/products/4741

These displays use I2C or SPI to communicate

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/
#ifndef NotAdafruit_SH1122_H
#define NotAdafruit_SH1122_H

#include <Adafruit_GrayOLED.h>

#define SH1122_BLACK 0x0
#define SH1122_WHITE 0xF

#define SH1122_I2C_ADDRESS 0x3C

#define SH1122_SET_COL_ADR_LSB (0X0)
#define SH1122_SET_COL_ADR_MSB (0X10)
#define SH1122_SET_DISP_START_LINE (0X40)
#define SH1122_SET_CONTRAST (0X81)
#define SH1122_SET_SEG_REMAP (0XA0)
#define SH1122_SET_ENTIRE_ON (0XA4)
#define SH1122_SET_NORM_INV (0XA6)
#define SH1122_SET_MUX_RATIO (0XA8)
#define SH1122_SET_CTRL_DCDC (0XAD)
#define SH1122_SET_DISP (0XAE)
#define SH1122_SET_ROW_ADR (0XB0)
#define SH1122_SET_COM_OUT_DIR (0XC0)
#define SH1122_SET_DISP_OFFSET (0XD3)
#define SH1122_SET_DISP_CLK_DIV (0XD5)
#define SH1122_SET_PRECHARGE (0xD9)
#define SH1122_SET_VCOM_DESEL (0xDB)
#define SH1122_SET_VSEG_LEVEL (0XDC)
#define SH1122_SET_DISCHARGE_LEVEL (0X30)

// #define SSD1305_SETBRIGHTNESS 0x82

// #define SSD1327_SETCOLUMN 0x15

// #define SSD1327_SETROW 0x75

// #define SSD1327_SETCONTRAST 0x81

// #define SSD1305_SETLUT 0x91

// #define SSD1327_SEGREMAP 0xA0
// #define SSD1327_SETSTARTLINE 0xA1
// #define SSD1327_SETDISPLAYOFFSET 0xA2
#define SH1122_NORMALDISPLAY 0xA4
// #define SSD1327_DISPLAYALLON 0xA5
// #define SSD1327_DISPLAYALLOFF 0xA6
#define SH1122_INVERTDISPLAY 0xA7
// #define SSD1327_SETMULTIPLEX 0xA8
// #define SSD1327_REGULATOR 0xAB
// #define SSD1327_DISPLAYOFF 0xAE
// #define SSD1327_DISPLAYON 0xAF

// #define SSD1327_PHASELEN 0xB1
// #define SSD1327_DCLK 0xB3
// #define SSD1327_PRECHARGE2 0xB6
// #define SSD1327_GRAYTABLE 0xB8
// #define SSD1327_PRECHARGE 0xBC
// #define SSD1327_SETVCOM 0xBE

// #define SSD1327_FUNCSELB 0xD5

// #define SSD1327_CMDLOCK 0xFD

/*! The controller object for SSD1327 OLED displays */
class Adafruit_SH1122 : public Adafruit_GrayOLED {
public:
  Adafruit_SH1122(uint16_t w, uint16_t h, TwoWire *twi = &Wire,
                   int8_t rst_pin = -1, uint32_t preclk = 400000,
                   uint32_t postclk = 100000);
  Adafruit_SH1122(uint16_t w, uint16_t h, int8_t mosi_pin, int8_t sclk_pin,
                   int8_t dc_pin, int8_t rst_pin, int8_t cs_pin);
  Adafruit_SH1122(uint16_t w, uint16_t h, SPIClass *spi, int8_t dc_pin,
                   int8_t rst_pin, int8_t cs_pin, uint32_t bitrate = 8000000UL);
  ~Adafruit_SH1122(void);

  bool begin(uint8_t i2caddr = SH1122_I2C_ADDRESS, bool reset = true);
  void display();
  void invertDisplay(bool i);

private:
  int8_t page_offset = 0;
  int8_t column_offset = 0;
};

#endif