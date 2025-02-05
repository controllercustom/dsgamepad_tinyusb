/************************************************************************
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
*************************************************************************/
#ifndef DSGAMEPAD_TINYUSB_H_
#define DSGAMEPAD_TINYUSB_H_

#include "Adafruit_TinyUSB.h"

// Dpad directions
typedef uint8_t DSDirection_t;
#define DSGAMEPAD_DPAD_CENTERED 8
#define DSGAMEPAD_DPAD_UP 0
#define DSGAMEPAD_DPAD_UP_RIGHT 1
#define DSGAMEPAD_DPAD_RIGHT 2
#define DSGAMEPAD_DPAD_DOWN_RIGHT 3
#define DSGAMEPAD_DPAD_DOWN 4
#define DSGAMEPAD_DPAD_DOWN_LEFT 5
#define DSGAMEPAD_DPAD_LEFT 6
#define DSGAMEPAD_DPAD_UP_LEFT 7

enum DSButtons {
  // button1
  DSButton_SQUARE = 0,
  DSButton_X = DSButton_SQUARE,
  DSButton_CROSS = 1,
  DSButton_A = DSButton_CROSS,
  DSButton_CIRCLE = 2,
  DSButton_B = DSButton_CIRCLE,
  DSButton_TRIANGLE = 3,
  DSButton_Y = DSButton_TRIANGLE,
  // button2
  DSButton_L1 = 4,
  DSButton_R1,
  DSButton_L2,   // also axis
  DSButton_R2,   // also axis
  DSButton_SHARE,
  DSButton_OPTIONS,
  DSButton_MENU = DSButton_OPTIONS,
  DSButton_L3,   // stick button
  DSButton_R3,   // stick button
                  // button3
  DSButton_LOGO,
  DSButton_TPAD
};

#define ATTRIBUTE_PACKED  __attribute__((packed, aligned(1)))

// 14 Buttons, 6 Axes, 1 D-Pad
typedef struct ATTRIBUTE_PACKED {
  uint8_t ReportID;   // always 0x01
  uint8_t leftXAxis;
  uint8_t leftYAxis;
  uint8_t L2Axis;
  uint8_t R2Axis;
  uint8_t dPad:4;     // dpad[3-0]
  uint8_t button1:4;  // Triangle[7], circle[6], cross[5], square[4]
  uint8_t button2;    // R3:7,L3:6,Options:5,share:4,R2:3,L2:2,R1:1,L1:0
  uint8_t button3:2;  // tpad click[1], logo[0]
  uint8_t reportCnt:6;
  uint8_t rightXAxis;
  uint8_t rightYAxis;
  uint16_t timestamp; // increment by 188 per report
  uint8_t batteryLvl;
  uint16_t gyroX;
  uint16_t gyroY;
  uint16_t gyroZ;
  int16_t accelX;
  int16_t accelY;
  int16_t accelZ;
  uint8_t filler[39];
} HID_DSGamepadReport_Data_t;

// HID report descriptor using TinyUSB's template
// Single Report (no ID) descriptor
static const uint8_t desc_hid_report[] = {
  0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
  0x09, 0x05,        // Usage (Game Pad)
  0xA1, 0x01,        // Collection (Application)
  0x85, 0x01,        //   Report ID (1)
  0x09, 0x30,        //   Usage (X)
  0x09, 0x31,        //   Usage (Y)
  0x09, 0x32,        //   Usage (Z)
  0x09, 0x35,        //   Usage (Rz)
  0x15, 0x00,        //   Logical Minimum (0)
  0x26, 0xFF, 0x00,  //   Logical Maximum (255)
  0x75, 0x08,        //   Report Size (8)
  0x95, 0x04,        //   Report Count (4)
  0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0x09, 0x39,        //   Usage (Hat switch)
  0x15, 0x00,        //   Logical Minimum (0)
  0x25, 0x07,        //   Logical Maximum (7)
  0x35, 0x00,        //   Physical Minimum (0)
  0x46, 0x3B, 0x01,  //   Physical Maximum (315)
  0x65, 0x14,        //   Unit (System: English Rotation, Length: Centimeter)
  0x75, 0x04,        //   Report Size (4)
  0x95, 0x01,        //   Report Count (1)
  0x81, 0x42,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,Null State)
  0x65, 0x00,        //   Unit (None)
  0x05, 0x09,        //   Usage Page (Button)
  0x19, 0x01,        //   Usage Minimum (0x01)
  0x29, 0x0E,        //   Usage Maximum (0x0E)
  0x15, 0x00,        //   Logical Minimum (0)
  0x25, 0x01,        //   Logical Maximum (1)
  0x75, 0x01,        //   Report Size (1)
  0x95, 0x0E,        //   Report Count (14)
  0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
  0x09, 0x20,        //   Usage (0x20)
  0x75, 0x06,        //   Report Size (6)
  0x95, 0x01,        //   Report Count (1)
  0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0x05, 0x01,        //   Usage Page (Generic Desktop Ctrls)
  0x09, 0x33,        //   Usage (Rx)
  0x09, 0x34,        //   Usage (Ry)
  0x15, 0x00,        //   Logical Minimum (0)
  0x26, 0xFF, 0x00,  //   Logical Maximum (255)
  0x75, 0x08,        //   Report Size (8)
  0x95, 0x02,        //   Report Count (2)
  0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
  0x09, 0x21,        //   Usage (0x21)
  0x95, 0x36,        //   Report Count (54)
  0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0x85, 0x05,        //   Report ID (5)
  0x09, 0x22,        //   Usage (0x22)
  0x95, 0x1F,        //   Report Count (31)
  0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
  0x85, 0x03,        //   Report ID (3)
  0x0A, 0x21, 0x27,  //   Usage (0x2721)
  0x95, 0x2F,        //   Report Count (47)
  0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
  0xC0,              // End Collection
  0x06, 0xF0, 0xFF,  // Usage Page (Vendor Defined 0xFFF0)
  0x09, 0x40,        // Usage (0x40)
  0xA1, 0x01,        // Collection (Application)
  0x85, 0xF0,        //   Report ID (-16)
  0x09, 0x47,        //   Usage (0x47)
  0x95, 0x3F,        //   Report Count (63)
  0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
  0x85, 0xF1,        //   Report ID (-15)
  0x09, 0x48,        //   Usage (0x48)
  0x95, 0x3F,        //   Report Count (63)
  0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
  0x85, 0xF2,        //   Report ID (-14)
  0x09, 0x49,        //   Usage (0x49)
  0x95, 0x0F,        //   Report Count (15)
  0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
  0x85, 0xF3,        //   Report ID (-13)
  0x0A, 0x01, 0x47,  //   Usage (0x4701)
  0x95, 0x07,        //   Report Count (7)
  0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
  0xC0,              // End Collection
};

class DSGamepad {
  public:
    explicit inline DSGamepad(Adafruit_USBD_HID *usb_hid);

    inline void begin(void);
    inline void end(void);
    inline void loop(void);
    inline void write(void);
    inline void write(void *report);
    inline void press(uint8_t b);
    inline void release(uint8_t b);
    inline void releaseAll(void);

    inline void buttons(uint16_t b);
    inline void leftXAxis(uint8_t a);
    inline void leftYAxis(uint8_t a);
    inline void rightXAxis(uint8_t a);
    inline void rightYAxis(uint8_t a);
    inline void rightTrigger(uint8_t a);
    inline void leftTrigger(uint8_t a);
    inline void dPad(DSDirection_t d);
    inline void dPad(bool up, bool down, bool left, bool right);
    inline bool ready(void) { return this->usb_hid->ready(); }

    // Sending is public for advanced users.
    inline bool SendReport(void* data, size_t length) {
      return this->usb_hid->sendReport(0, data, (uint8_t)length);
    }

  protected:
    HID_DSGamepadReport_Data_t _report;
    uint32_t startMillis;
    Adafruit_USBD_HID *usb_hid;
};

DSGamepad::DSGamepad(Adafruit_USBD_HID *usb_hid) {
  this->usb_hid = usb_hid;
  startMillis = millis();
  memset(&_report, 0, sizeof(_report));
  this->usb_hid->setStringDescriptor("Gamepad");
}

void DSGamepad::begin(void) {
  this->usb_hid->setPollInterval(1);
  this->usb_hid->setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  USBDevice.setID(0x0f0d, 0x00ee);
  this->usb_hid->begin();

  // release all buttons, center all sticks, etc.
  end();
  startMillis = millis();
}

void DSGamepad::loop(void) {
  if (startMillis != millis()) {
    write();
    startMillis = millis();
  }
}

void DSGamepad::end(void) {
  releaseAll();
}

void DSGamepad::write(void) {
  SendReport(&_report, sizeof(_report));
  _report.reportCnt++;
  _report.timestamp += 188;
}

void DSGamepad::write(void *report) {
  uint16_t save_timestamp = _report.timestamp;
  uint8_t save_reportCnt = _report.reportCnt;
  memcpy(&_report, report, sizeof(_report));
  _report.timestamp = save_timestamp;
  _report.reportCnt = save_reportCnt;
  SendReport(&_report, sizeof(_report));
}

void DSGamepad::press(uint8_t b) {
  b &= 0xF;   // Limit value between 0..15
  switch (b) {
    // button 1
    case DSButton_SQUARE:
    case DSButton_CROSS:
    case DSButton_CIRCLE:
    case DSButton_TRIANGLE:
      _report.button1 |= 1 << b;
      break;
      // button2
    case DSButton_L1:
    case DSButton_R1:
    case DSButton_L2:  // also axis
    case DSButton_R2:  // also axis
    case DSButton_SHARE:
    case DSButton_OPTIONS:
    case DSButton_L3:  // stick button
    case DSButton_R3:  // stick button
      _report.button2 |= 1 << (b - DSButton_L1);
      break;
      // button3
    case DSButton_LOGO:
    case DSButton_TPAD:
      _report.button3 |= 1 << (b - DSButton_LOGO);
      break;
    default:
      break;
  }
}


void DSGamepad::release(uint8_t b) {
  b &= 0xF;   // Limit value between 0..15
  switch (b) {
    // button 1
    case DSButton_SQUARE:
    case DSButton_CROSS:
    case DSButton_CIRCLE:
    case DSButton_TRIANGLE:
      _report.button1 &= ~(1 << b);
      break;
      // button2
    case DSButton_L1:
    case DSButton_R1:
    case DSButton_L2:  // also axis
    case DSButton_R2:  // also axis
    case DSButton_SHARE:
    case DSButton_OPTIONS:
    case DSButton_L3:  // stick button
    case DSButton_R3:  // stick button
      _report.button2 &= ~(1 << (b - DSButton_L1));
      break;
      // button3
    case DSButton_LOGO:
    case DSButton_TPAD:
      _report.button3 &= ~(1 << (b - DSButton_LOGO));
      break;
    default:
      break;
  }
}


void DSGamepad::releaseAll(void) {
  uint16_t save_timestamp = _report.timestamp;
  uint8_t save_reportCnt = _report.reportCnt;
  memset(&_report, 0x00, sizeof(_report));
  _report.timestamp = save_timestamp;
  _report.reportCnt = save_reportCnt;
  _report.ReportID = 0x01;
  _report.leftXAxis = _report.leftYAxis = 0x80;
  _report.L2Axis = _report.R2Axis = 0x80;
  _report.dPad = DSGAMEPAD_DPAD_CENTERED;
}

void DSGamepad::buttons(uint16_t b) {
  _report.button1 = _report.button2 = _report.button3 = 0;
  for (int i = DSButton_SQUARE; i <= DSButton_TPAD; i++) {
    if (b & (1 << i)) press(i);
  }
}


void DSGamepad::leftXAxis(uint8_t a) {
  _report.leftXAxis = a;
}


void DSGamepad::leftYAxis(uint8_t a) {
  _report.leftYAxis = a;
}


void DSGamepad::rightXAxis(uint8_t a) {
  _report.rightXAxis = a;
}


void DSGamepad::rightYAxis(uint8_t a) {
  _report.rightYAxis = a;
}

void DSGamepad::rightTrigger(uint8_t a) {
  _report.R2Axis = a;
}


void DSGamepad::leftTrigger(uint8_t a) {
  _report.L2Axis = a;
}


// The direction pad is limited to 8 directions plus centered. This means
// some combinations of 4 dpad buttons are not valid and cannot be sent.
// Button down = true(1)
// Valid: Any 1 button down, any 2 adjacent buttons down, no buttons down
// Invalid: all other combinations
void DSGamepad::dPad(bool up, bool down, bool left, bool right) {
  static const DSDirection_t BITS2DIR[16] = {
    DSGAMEPAD_DPAD_CENTERED,    // 0000
    DSGAMEPAD_DPAD_RIGHT,       // 0001
    DSGAMEPAD_DPAD_LEFT,        // 0010
    DSGAMEPAD_DPAD_CENTERED,    // 0011
    DSGAMEPAD_DPAD_DOWN,        // 0100
    DSGAMEPAD_DPAD_DOWN_RIGHT,  // 0101
    DSGAMEPAD_DPAD_DOWN_LEFT,   // 0110
    DSGAMEPAD_DPAD_CENTERED,    // 0111
    DSGAMEPAD_DPAD_UP,          // 1000
    DSGAMEPAD_DPAD_UP_RIGHT,    // 1001
    DSGAMEPAD_DPAD_UP_LEFT,     // 1010
    DSGAMEPAD_DPAD_CENTERED,    // 1011
    DSGAMEPAD_DPAD_CENTERED,    // 1100
    DSGAMEPAD_DPAD_CENTERED,    // 1101
    DSGAMEPAD_DPAD_CENTERED,    // 1110
    DSGAMEPAD_DPAD_CENTERED     // 1111
  };
  uint8_t dpad_bits = (up << 3) | (down << 2) | (left << 1) | (right << 0);
  _report.dPad = BITS2DIR[dpad_bits];
}

void DSGamepad::dPad(DSDirection_t d) {
  _report.dPad = d;
}
#endif  // DSGAMEPAD_TINYUSB_H_
