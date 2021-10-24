/*
  KeyboardGER2.h
  derived from Keyboard.h and modified by user StefanL38

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
*/

#ifndef KEYBOARDGER2_h  // this #ifndef #define prevents from re-declaration-errors 
#define KEYBOARDGER2_h  // through accidentically "double"-including KeyboardGER2.h


#include "Arduino.h"
#include "HID.h"

#if !defined(_USING_HID)

#warning "Using legacy HID core (non pluggable)"

#endif

const byte Ctrl  = 1;
const byte Shift = 2;
const byte Alt   = 4;

const byte CtrlAlt   = Ctrl + Alt;
const byte AltCtrl   = CtrlAlt;

const byte aeoeue_1stByte = 195;
const byte ae_2ndByte = 164;
const byte oe_2ndByte = 182;
const byte ue_2ndByte = 188;

const byte Ae_2ndByte = 132;
const byte Oe_2ndByte = 150;
const byte Ue_2ndByte = 156;
const byte SharpS_2ndByte = 159;

const byte mue23_1stByte = 194;
const byte mue_2ndByte   = 181;
const byte mue2_2ndByte  = 178;
const byte mue3_2ndByte  = 179;

const byte degree_2ndByte = 176;
const byte paragraph_2ndByte = 167;

const byte euro_1stByte = 226;
const byte euro_2ndByte = 130;
const byte euro_3rdByte = 172;

const int SendDelay = 5;

/* Modifiers */
enum MODIFIER_KEY {
	KEY_CTRL     = 1,
	KEY_SHIFT    = 2,
	KEY_ALT      = 4,
    KEY_CTRL_ALT = 5
};


typedef struct {
	unsigned char key;
	unsigned char modifier;
	} KEY_MOD_VALUE;


typedef struct {
  uint8_t modifiers;
  uint8_t reserved;
  uint8_t pressedKeys[6];
} KeyReport_t;



/* German keyboard (as HID standard) */
#define KEY_MOD_TABLE_SIZE (127)

const KEY_MOD_VALUE key_mod_values[KEY_MOD_TABLE_SIZE] = {
   {0x00, 0 }, /* 0  */
   {0x00, 0 }, /* 1  */
   {0x00, 0 }, /* 2  */
   {0x00, 0 }, /* 3  */
   {0x00, 0 }, /* 4  */
   {0x00, 0 }, /* 5  */
   {0x00, 0 }, /* 6  */
   {0x00, 0 }, /* 7  */
   {0x00, 0 }, /* 8  */
   {0x00, 0 }, /* 9  */
   {0x58, 0 }, /* 10  */  //translate newline to returnkey
   {0x00, 0 }, /* 11  */
   {0x00, 0 }, /* 12  */
   {0x58, 0 }, /* 13  */  // translate return to returnkey
   {0x00, 0 }, /* 14  */
   {0x00, 0 }, /* 15  */
   {0x00, 0 }, /* 16  */
   {0x00, 0 }, /* 17  */
   {0x00, 0 }, /* 18  */
   {0x00, 0 }, /* 19  */
   {0x00, 0 }, /* 20  */
   {0x00, 0 }, /* 21  */
   {0x00, 0 }, /* 22  */
   {0x00, 0 }, /* 23  */
   {0x00, 0 }, /* 24  */
   {0x00, 0 }, /* 25  */
   {0x00, 0 }, /* 26  */
   {0x00, 0 }, /* 27  */
   {0x00, 0 }, /* 28  */
   {0x00, 0 }, /* 29  */
   {0x00, 0 }, /* 30  */
   {0x00, 0 }, /* 31  */
   {0x00, 0 }, /* 32  */
   {0x1E, KEY_SHIFT }, /* 33   !  */
   {0x1F, KEY_SHIFT }, /* 34   "  */
   {0x31, 0 }, /* 35   #  */
   {0x21, KEY_SHIFT }, /* 36   $  */
   {0x22, KEY_SHIFT }, /* 37   %  */
   {0x23, KEY_SHIFT }, /* 38   &  */
   {0x31, KEY_SHIFT }, /* 39   '  */
   {0x25, KEY_SHIFT }, /* 40   (  */
   {0x26, KEY_SHIFT }, /* 41   )  */
   {0x30, KEY_SHIFT }, /* 42   * */
   {0x30, 0 }, /* 43   +  */
   {0x36, 0 }, /* 44   ,  */
   {0x38, 0 }, /* 45   -  */
   {0x37, 0 }, /* 46   .  */
   {0x24, KEY_SHIFT }, /* 47   / */
   {0x27, 0 }, /* 48 0 */
   {0x1E, 0 }, /* 49 1 */
   {0x1F, 0 }, /* 50 2 */
   {0x20, 0 }, /* 51 3 */     // {0x20, 0 }, /* 51 3 */
   {0x21, 0 }, /* 52 4 */
   {0x22, 0 }, /* 53 5 */
   {0x23, 0 }, /* 54 6 */
   {0x24, 0 }, /* 55 7 */
   {0x25, 0 }, /* 56 8 */
   {0x26, 0 }, /* 57 9 */
   {0x37, KEY_SHIFT }, /* 58   :  */
   {0x36, KEY_SHIFT }, /* 59   ; */
   {0x64, 0 }, /* 60   <  */
   {0x27, KEY_SHIFT }, /* 61   =  */
   {0x64, KEY_SHIFT }, /* 62   >  */
   {0x2D, KEY_SHIFT }, /* 63   ?  */
   {0x14, KEY_CTRL_ALT }, /* 64   @ */
   {0x04, KEY_SHIFT }, /* 65   A  */
   {0x05, KEY_SHIFT }, /* 66   B  */
   {0x06, KEY_SHIFT }, /* 67   C  */
   {0x07, KEY_SHIFT }, /* 68   D  */
   {0x08, KEY_SHIFT }, /* 69   E */
   {0x09, KEY_SHIFT }, /* 70   F  */
   {0x0A, KEY_SHIFT }, /* 71   G  */
   {0x0B, KEY_SHIFT }, /* 72   H  */
   {0x0C, KEY_SHIFT }, /* 73   I */
   {0x0D, KEY_SHIFT }, /* 74   J  */
   {0x0E, KEY_SHIFT }, /* 75   K  */
   {0x0F, KEY_SHIFT }, /* 76   L  */
   {0x10, KEY_SHIFT }, /* 77   M  */
   {0x11, KEY_SHIFT }, /* 78   N  */
   {0x12, KEY_SHIFT }, /* 79   O */
   {0x13, KEY_SHIFT }, /* 80   P */
   {0x14, KEY_SHIFT }, /* 81   Q */
   {0x15, KEY_SHIFT }, /* 82   R */
   {0x16, KEY_SHIFT }, /* 83   S  */
   {0x17, KEY_SHIFT }, /* 84   T */
   {0x18, KEY_SHIFT }, /* 85   U */
   {0x19, KEY_SHIFT }, /* 86   V  */
   {0x1A, KEY_SHIFT }, /* 87   W */
   {0x1B, KEY_SHIFT }, /* 88   X  */
   {0x1D, KEY_SHIFT }, /* 89   Y  */
   {0x1C, KEY_SHIFT }, /* 90   Z */
   {0x25, KEY_CTRL_ALT }, /* 91   [ */
   {0x2D, KEY_CTRL_ALT }, /* 92   \ */
   {0x26, KEY_CTRL_ALT }, /* 93   ] */
   {0x35, 0 }, /* 94   ^  */
   {0x38, KEY_SHIFT }, /* 95   _  */
   {0x2E, KEY_SHIFT }, /* 96   `  */
   {0x04, 0 }, /* 97   a  */
   {0x05, 0 }, /* 98   b  */
   {0x06, 0 }, /* 99   c  */
   {0x07, 0 }, /* 100   d  */
   {0x08, 0 }, /* 101   e  */
   {0x09, 0 }, /* 102   f  */
   {0x0A, 0 }, /* 103   g  */
   {0x0B, 0 }, /* 104   h  */
   {0x0C, 0 }, /* 105   i  */
   {0x0D, 0 }, /* 106   j  */
   {0x0E, 0 }, /* 107   k  */
   {0x0F, 0 }, /* 108   l  */
   {0x10, 0 }, /* 109   m  */
   {0x11, 0 }, /* 110   n  */
   {0x12, 0 }, /* 111   o  */
   {0x13, 0 }, /* 112   p  */
   {0x14, 0 }, /* 113   q  */
   {0x15, 0 }, /* 114   r  */
   {0x16, 0 }, /* 115   s  */
   {0x17, 0 }, /* 116   t  */
   {0x18, 0 }, /* 117   u  */
   {0x19, 0 }, /* 118   v  */
   {0x1A, 0 }, /* 119   w  */
   {0x1B, 0 }, /* 120   x  */
   {0x1D, 0 }, /* 121   y  */
   {0x1C, 0 }, /* 122   z  */
   {0x0 , 0 }, /* 123   { */
   {0x64, KEY_CTRL_ALT }, /* 124   | */
   {0x0 , 0 }, /* 125   } */
   {0x30, KEY_CTRL_ALT }, /* 126   ~ */
};



class KeyboardGER2 
{
//private: {}
public:
  KeyReport_t _keyReport;
  void sendReport(KeyReport_t* keys);
  KeyboardGER2(void);
  void begin(void);
  void end(void);
  void sendKeyPress(uint8_t p_key, uint8_t p_modifiers);
  void sendKeyRelease();
  void SendReturn();
  void typeText(const char* text);

};

#endif
