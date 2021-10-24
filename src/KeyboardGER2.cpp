/*
  KeyboardGER2.cpp
  derived from Keyboard.cpp and modified by user StefanL38

  Copyright (c) 2015, Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  ATTENTION ! for easier writing down code there is a convention to give
  the class and the constructor-function the exact same name as the filenames *.h / *.cpp
  in this case this is "KeyboardGER2"
*/

#include "KeyboardGER2.h"

#if defined(_USING_HID)


static const uint8_t _hidReportDescriptor[] PROGMEM = {

  //  Keyboard
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)  // 47
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x85, 0x02,                    //   REPORT_ID (2)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
   
  0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    
  0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
    
  0x95, 0x06,                    //   REPORT_COUNT (6)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x73,                    //   LOGICAL_MAXIMUM (115)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    
  0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x73,                    //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xc0,                          // END_COLLECTION
};


KeyboardGER2::KeyboardGER2(void) { //<= the first "KeyboardGER2::" is the class-NAME the second "KeyboardGER2" is the functionname of the constructor
	static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
	HID().AppendDescriptor(&node);
}

void KeyboardGER2::begin(void){ } // insert class-Name:: between returntype and function-name 

void KeyboardGER2::end(void) { }

void KeyboardGER2::sendReport(KeyReport_t* keys){
	HID().SendReport(2,keys,sizeof(KeyReport_t));
}


void KeyboardGER2::sendKeyPress(uint8_t p_key, uint8_t p_modifiers) {
  
  KeyReport_t myKeyMessage;
  
  for (int j = 0; j < 6; j++) {
    myKeyMessage.pressedKeys[j] = 0;
  }
  
  myKeyMessage.pressedKeys[0] = p_key;
  myKeyMessage.modifiers = p_modifiers;
  myKeyMessage.reserved  = 0;

  sendReport(&myKeyMessage);  
  delay(SendDelay);  
}


void KeyboardGER2::sendKeyRelease() {

  KeyReport_t myKeyMessage;

  for (int j = 0; j < 6; j++) {
    myKeyMessage.pressedKeys[j] = 0;
  }

  myKeyMessage.pressedKeys[0] = 0;
  myKeyMessage.modifiers = 0;
  myKeyMessage.reserved  = 0;
  
  sendReport(&myKeyMessage);
}


void KeyboardGER2::SendReturn() {
  sendKeyPress(88,0);
  sendKeyRelease();  
}


// as some special characters like "@" "Ä", "€" have a two-byte or even three-byte-representation
// a simple write (uint8_t that_one_single_byte) is NOT possible 
// the multibyte characters need a more special analyses to set the correspnding key-press-value
void KeyboardGER2::typeText(const char* text) {

  uint8_t ASCII_Code;
  uint8_t SecondByte;
  uint8_t ThirdByte;
  
  uint8_t key;
  uint8_t modifiers;

  int len = strlen(text);
  int i = -1; // initialise with -1 to get i = 0 at first run with i++ at the top of the loop

  while (i < len) {
    i++;
    // translate character to key combination
    ASCII_Code = (uint8_t)text[i];

    if (ASCII_Code > KEY_MOD_TABLE_SIZE) { // character has a multibyte representation
      switch (ASCII_Code) {
        case aeoeue_1stByte: // if it's an äöü
          i++;
          SecondByte = text[i];

          if (SecondByte == ae_2ndByte) { // if it's an ä
            key = 52; 
            modifiers   = 0;
            break;
          }

          if (SecondByte == oe_2ndByte) { // if it's an ö
            key = 51; 
            modifiers   = 0;
            break;
          }

          if (SecondByte == ue_2ndByte) { // if it's an ü
            key = 47; 
            modifiers   = 0;
            break;
          }

          if (SecondByte == Ae_2ndByte) { // if it's an Ä
            key = 52; 
            modifiers   = Shift;
            break;
          }

          if (SecondByte == Oe_2ndByte) { // if it's an Ö
            key = 51; 
            modifiers   = Shift;
            break;
          }

          if (SecondByte == Ue_2ndByte) { // if it's an Ü
            key = 47; 
            modifiers   = Shift;
            break;
          }

          if (SecondByte == SharpS_2ndByte) { // if it's an ß
            key = 45; 
            modifiers   = 0;
            break;
          }
          
        case mue23_1stByte: // if it's a µ²³
          i++;
          SecondByte = text[i];

          if (SecondByte == mue_2ndByte) { // if it's an µ
            key = 16; 
            modifiers   = CtrlAlt;
            break;
          }

          if (SecondByte == mue2_2ndByte) { // if it's an ²
            key = 31; 
            modifiers   = CtrlAlt;
            break;
          }

          if (SecondByte == mue3_2ndByte) { // if it's an ³
            key = 32; 
            modifiers   = CtrlAlt;
            break;
          }

          if (SecondByte == degree_2ndByte) { // if it's an °
            key = 53; 
            modifiers   = Shift;
            break;
          }

          if (SecondByte == paragraph_2ndByte) { // if it's an §
            key = 32; 
            modifiers   = Shift;
            break;
          }

        case euro_1stByte: // if it's a €-symbol
          i++;
          SecondByte = text[i];
          if (SecondByte == euro_2ndByte) {
            i++;
            ThirdByte = text[i];
            if (ThirdByte == euro_3rdByte) {
              key = 8; 
              modifiers   = CtrlAlt;
              break;
            }
          }
        default:
          key = 0; 
          modifiers      = 0;
          //dbg("default", ASCII_Code);
          break;
      }
    } //if (ASCII_Code > KEY_MOD_TABLE_SIZE) multibyte representation

    else { // character has a single-byte representation
      KEY_MOD_VALUE myKeyAndMod = key_mod_values[ASCII_Code];
      modifiers = myKeyAndMod.modifier;

      key = myKeyAndMod.key; // myKeyMessage.pressedKeys[0] = myKeyAndMod.key;
    } //  else { // character has a single-byte representation

    sendKeyPress(key,modifiers);
    sendKeyRelease();  
  } //while (i < len)

} // void typeText(const char* text)

#endif

