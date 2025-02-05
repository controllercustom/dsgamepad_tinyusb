/*
MIT License

Copyright (c) 2025 controllercustom@myyahoo.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "dsgamepad_tinyusb.h"
Adafruit_USBD_HID G_usb_hid;
DSGamepad Gamepad(&G_usb_hid);

const int pinLed = LED_BUILTIN;

void setup() {
  Serial.end();   // Disable CDC ACM USB serial port
  Gamepad.begin();
  pinMode(pinLed, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // wait until device mounted
  while( !USBDevice.mounted() ) delay(1);
}

void loop() {
  static uint8_t count = DSButton_SQUARE;
  static bool button_on = true;
  if (count > DSButton_TPAD) {
    button_on = !button_on;
    count = DSButton_SQUARE;
  }
  if (button_on) {
    Gamepad.press(count);
  }
  else {
    Gamepad.release(count);
  }
  count++;

  // Move x/y Axis to a new position (8 bit)
  Gamepad.leftXAxis(random(256));
  Gamepad.leftYAxis(random(256));
  Gamepad.rightXAxis(random(256));
  Gamepad.rightYAxis(random(256));
  Gamepad.leftTrigger(random(256));
  Gamepad.rightTrigger(random(256));

  // Go through all dPad positions
  // values: 0-8 (8==centered)
  static uint8_t dpad = DSGAMEPAD_DPAD_UP;
  Gamepad.dPad(dpad++);
  if (dpad > DSGAMEPAD_DPAD_CENTERED)
    dpad = DSGAMEPAD_DPAD_UP;

  // Functions above only set the values.
  // This writes the report to the host.
  if ( Gamepad.ready() ) Gamepad.loop();
  delay(100);
}
