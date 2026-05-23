# NOT Adafruit SH1122

This is an Arduino library for SH1122 256x64 4bpp greyscale OLED boards. It was cloned/bodged from Adafruit's SSD1327 library. It works OK with [this module](https://goldenmorninglcd.com/oled-display-module/2.08-inch-256x64-sh1122-gme25664-65/).

NOTE: there are a few modules out there which use i2c. This code might work with them but is wholly untested.

The display is well-supported by u8g2, but only in black and white mode. I wanted to be able to use greyscale.

## About this Driver
Written/cloned/bodged from [Adafruit SSD1327](https://github.com/adafruit/Adafruit_SSD1327):

<blockquote>
Written by Limor Fried for Adafruit Industries.
BSD license, check license.txt for more information
All text above must be included in any redistribution
</blockquote>

with reference to commandset from the [u8g2](https://github.com/olikraus/u8g2/) code.

## TODO

[ ] Fix partial/windowed updates.
[ ] Reconcile the ssd1327 driver's other init commands (this has only the basics stolen from u8g2). Maybe there's something worth having.