/* Copyright (c) 2019-2025 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _HW_HID_USBKBD_H
#define _HW_HID_USBKBD_H 1

#include <__stdinc.h>


/* USB Keyboard modifier mask shifts */
#define USBKBD_MODSHIFT_LEFTCTRL   0 /* KEY_LEFTCTRL */
#define USBKBD_MODSHIFT_LEFTSHIFT  1 /* KEY_LEFTSHIFT */
#define USBKBD_MODSHIFT_LEFTALT    2 /* KEY_LEFTALT */
#define USBKBD_MODSHIFT_LEFTMETA   3 /* KEY_LEFTMETA */
#define USBKBD_MODSHIFT_RIGHTCTRL  4 /* KEY_RIGHTCTRL */
#define USBKBD_MODSHIFT_RIGHTSHIF  5 /* KEY_RIGHTSHIFT */
#define USBKBD_MODSHIFT_RIGHTALT   6 /* KEY_RIGHTALT */
#define USBKBD_MODSHIFT_RIGHTMETA  7 /* KEY_RIGHTMETA */

/* USB Keyboard modifier masks. */
#define USBKBD_MOD_LEFTCTRL  (1 << USBKBD_MODSHIFT_LEFTCTRL)  /* KEY_LEFTCTRL */
#define USBKBD_MOD_LEFTSHIFT (1 << USBKBD_MODSHIFT_LEFTSHIFT) /* KEY_LEFTSHIFT */
#define USBKBD_MOD_LEFTALT   (1 << USBKBD_MODSHIFT_LEFTALT)   /* KEY_LEFTALT */
#define USBKBD_MOD_LEFTMETA  (1 << USBKBD_MODSHIFT_LEFTMETA)  /* KEY_LEFTMETA */
#define USBKBD_MOD_RIGHTCTRL (1 << USBKBD_MODSHIFT_RIGHTCTRL) /* KEY_RIGHTCTRL */
#define USBKBD_MOD_RIGHTSHIF (1 << USBKBD_MODSHIFT_RIGHTSHIF) /* KEY_RIGHTSHIFT */
#define USBKBD_MOD_RIGHTALT  (1 << USBKBD_MODSHIFT_RIGHTALT)  /* KEY_RIGHTALT */
#define USBKBD_MOD_RIGHTMETA (1 << USBKBD_MODSHIFT_RIGHTMETA) /* KEY_RIGHTMETA */



/* USB Keyboard keycodes.
 * - https://gist.github.com/MightyPork/6da26e382a7ad91b5496ee55fdc73db2
 * - https://www.win.tue.nl/~aeb/linux/kbd/scancodes-14.html */

/*      USBKBD_KEY_                       0x00  * ... */
/*      USBKBD_KEY_                       0x01  * ... */
/*      USBKBD_KEY_                       0x02  * ... */
/*      USBKBD_KEY_                       0x03  * ... */
#define USBKBD_KEY_A                      0x04 /* s.a. `KEY_A' */
#define USBKBD_KEY_B                      0x05 /* s.a. `KEY_B' */
#define USBKBD_KEY_C                      0x06 /* s.a. `KEY_C' */
#define USBKBD_KEY_D                      0x07 /* s.a. `KEY_D' */
#define USBKBD_KEY_E                      0x08 /* s.a. `KEY_E' */
#define USBKBD_KEY_F                      0x09 /* s.a. `KEY_F' */
#define USBKBD_KEY_G                      0x0a /* s.a. `KEY_G' */
#define USBKBD_KEY_H                      0x0b /* s.a. `KEY_H' */
#define USBKBD_KEY_I                      0x0c /* s.a. `KEY_I' */
#define USBKBD_KEY_J                      0x0d /* s.a. `KEY_J' */
#define USBKBD_KEY_K                      0x0e /* s.a. `KEY_K' */
#define USBKBD_KEY_L                      0x0f /* s.a. `KEY_L' */
#define USBKBD_KEY_M                      0x10 /* s.a. `KEY_M' */
#define USBKBD_KEY_N                      0x11 /* s.a. `KEY_N' */
#define USBKBD_KEY_O                      0x12 /* s.a. `KEY_O' */
#define USBKBD_KEY_P                      0x13 /* s.a. `KEY_P' */
#define USBKBD_KEY_Q                      0x14 /* s.a. `KEY_Q' */
#define USBKBD_KEY_R                      0x15 /* s.a. `KEY_R' */
#define USBKBD_KEY_S                      0x16 /* s.a. `KEY_S' */
#define USBKBD_KEY_T                      0x17 /* s.a. `KEY_T' */
#define USBKBD_KEY_U                      0x18 /* s.a. `KEY_U' */
#define USBKBD_KEY_V                      0x19 /* s.a. `KEY_V' */
#define USBKBD_KEY_W                      0x1a /* s.a. `KEY_W' */
#define USBKBD_KEY_X                      0x1b /* s.a. `KEY_X' */
#define USBKBD_KEY_Y                      0x1c /* s.a. `KEY_Y' */
#define USBKBD_KEY_Z                      0x1d /* s.a. `KEY_Z' */
#define USBKBD_KEY_1                      0x1e /* s.a. `KEY_1' */
#define USBKBD_KEY_2                      0x1f /* s.a. `KEY_2' */
#define USBKBD_KEY_3                      0x20 /* s.a. `KEY_3' */
#define USBKBD_KEY_4                      0x21 /* s.a. `KEY_4' */
#define USBKBD_KEY_5                      0x22 /* s.a. `KEY_5' */
#define USBKBD_KEY_6                      0x23 /* s.a. `KEY_6' */
#define USBKBD_KEY_7                      0x24 /* s.a. `KEY_7' */
#define USBKBD_KEY_8                      0x25 /* s.a. `KEY_8' */
#define USBKBD_KEY_9                      0x26 /* s.a. `KEY_9' */
#define USBKBD_KEY_0                      0x27 /* s.a. `KEY_0' */
#define USBKBD_KEY_ENTER                  0x28 /* s.a. `KEY_ENTER' */
#define USBKBD_KEY_ESC                    0x29 /* s.a. `KEY_ESC' */
#define USBKBD_KEY_BACKSPACE              0x2a /* s.a. `KEY_BACKSPACE' */
#define USBKBD_KEY_TAB                    0x2b /* s.a. `KEY_TAB' */
#define USBKBD_KEY_SPACE                  0x2c /* s.a. `KEY_SPACE' */
#define USBKBD_KEY_MINUS                  0x2d /* s.a. `KEY_MINUS' */
#define USBKBD_KEY_EQUAL                  0x2e /* s.a. `KEY_EQUAL' */
#define USBKBD_KEY_LEFTBRACE              0x2f /* s.a. `KEY_LEFTBRACE' */
#define USBKBD_KEY_RIGHTBRACE             0x30 /* s.a. `KEY_RIGHTBRACE' */
#define USBKBD_KEY_BACKSLASH              0x31 /* s.a. `KEY_BACKSLASH' */
#define USBKBD_KEY_POUND                  0x32 /* s.a. `KEY_APOSTROPHE' */
#define USBKBD_KEY_SEMICOLON              0x33 /* s.a. `KEY_SEMICOLON' */
#define USBKBD_KEY_APOSTROPHE             0x34 /* s.a. `KEY_APOSTROPHE' */
#define USBKBD_KEY_GRAVE                  0x35 /* s.a. `KEY_GRAVE' */
#define USBKBD_KEY_COMMA                  0x36 /* s.a. `KEY_COMMA' */
#define USBKBD_KEY_DOT                    0x37 /* s.a. `KEY_DOT' */
#define USBKBD_KEY_SLASH                  0x38 /* s.a. `KEY_SLASH' */
#define USBKBD_KEY_CAPSLOCK               0x39 /* s.a. `KEY_CAPSLOCK' */
#define USBKBD_KEY_F1                     0x3a /* s.a. `KEY_F1' */
#define USBKBD_KEY_F2                     0x3b /* s.a. `KEY_F2' */
#define USBKBD_KEY_F3                     0x3c /* s.a. `KEY_F3' */
#define USBKBD_KEY_F4                     0x3d /* s.a. `KEY_F4' */
#define USBKBD_KEY_F5                     0x3e /* s.a. `KEY_F5' */
#define USBKBD_KEY_F6                     0x3f /* s.a. `KEY_F6' */
#define USBKBD_KEY_F7                     0x40 /* s.a. `KEY_F7' */
#define USBKBD_KEY_F8                     0x41 /* s.a. `KEY_F8' */
#define USBKBD_KEY_F9                     0x42 /* s.a. `KEY_F9' */
#define USBKBD_KEY_F10                    0x43 /* s.a. `KEY_F10' */
#define USBKBD_KEY_F11                    0x44 /* s.a. `KEY_F11' */
#define USBKBD_KEY_F12                    0x45 /* s.a. `KEY_F12' */
#define USBKBD_KEY_PRINTSCREEN            0x46 /* s.a. `KEY_PRINTSCREEN' */
#define USBKBD_KEY_SCROLLLOCK             0x47 /* s.a. `KEY_SCROLLLOCK' */
#define USBKBD_KEY_PAUSE                  0x48 /* s.a. `KEY_PAUSE' */
#define USBKBD_KEY_INSERT                 0x49 /* s.a. `KEY_INSERT' */
#define USBKBD_KEY_HOME                   0x4a /* s.a. `KEY_HOME' */
#define USBKBD_KEY_PAGEUP                 0x4b /* s.a. `KEY_PAGEUP' */
#define USBKBD_KEY_DELETE                 0x4c /* s.a. `KEY_DELETE' */
#define USBKBD_KEY_END                    0x4d /* s.a. `KEY_END' */
#define USBKBD_KEY_PAGEDOWN               0x4e /* s.a. `KEY_PAGEDOWN' */
#define USBKBD_KEY_RIGHT                  0x4f /* s.a. `KEY_RIGHT' */
#define USBKBD_KEY_LEFT                   0x50 /* s.a. `KEY_LEFT' */
#define USBKBD_KEY_DOWN                   0x51 /* s.a. `KEY_DOWN' */
#define USBKBD_KEY_UP                     0x52 /* s.a. `KEY_UP' */
#define USBKBD_KEY_NUMLOCK                0x53 /* s.a. `KEY_NUMLOCK' */
#define USBKBD_KEY_KPSLASH                0x54 /* s.a. `KEY_KPSLASH' */
#define USBKBD_KEY_KPASTERISK             0x55 /* s.a. `KEY_KPASTERISK' */
#define USBKBD_KEY_KPMINUS                0x56 /* s.a. `KEY_KPMINUS' */
#define USBKBD_KEY_KPPLUS                 0x57 /* s.a. `KEY_KPPLUS' */
#define USBKBD_KEY_KPENTER                0x58 /* s.a. `KEY_KPENTER' */
#define USBKBD_KEY_KP1                    0x59 /* s.a. `KEY_KP1' */
#define USBKBD_KEY_KP2                    0x5a /* s.a. `KEY_KP2' */
#define USBKBD_KEY_KP3                    0x5b /* s.a. `KEY_KP3' */
#define USBKBD_KEY_KP4                    0x5c /* s.a. `KEY_KP4' */
#define USBKBD_KEY_KP5                    0x5d /* s.a. `KEY_KP5' */
#define USBKBD_KEY_KP6                    0x5e /* s.a. `KEY_KP6' */
#define USBKBD_KEY_KP7                    0x5f /* s.a. `KEY_KP7' */
#define USBKBD_KEY_KP8                    0x60 /* s.a. `KEY_KP8' */
#define USBKBD_KEY_KP9                    0x61 /* s.a. `KEY_KP9' */
#define USBKBD_KEY_KP0                    0x62 /* s.a. `KEY_KP0' */
#define USBKBD_KEY_KPDOT                  0x63 /* s.a. `KEY_KPDOT' */
#define USBKBD_KEY_102ND                  0x64 /* s.a. `KEY_102ND' */
#define USBKBD_KEY_COMPOSE                0x65 /* s.a. `KEY_COMPOSE' */
#define USBKBD_KEY_POWER                  0x66 /* s.a. `KEY_POWER' */
#define USBKBD_KEY_KPEQUAL                0x67 /* s.a. `KEY_KPEQUAL' */
#define USBKBD_KEY_F13                    0x68 /* s.a. `KEY_F13' */
#define USBKBD_KEY_F14                    0x69 /* s.a. `KEY_F14' */
#define USBKBD_KEY_F15                    0x6a /* s.a. `KEY_F15' */
#define USBKBD_KEY_F16                    0x6b /* s.a. `KEY_F16' */
#define USBKBD_KEY_F17                    0x6c /* s.a. `KEY_F17' */
#define USBKBD_KEY_F18                    0x6d /* s.a. `KEY_F18' */
#define USBKBD_KEY_F19                    0x6e /* s.a. `KEY_F19' */
#define USBKBD_KEY_F20                    0x6f /* s.a. `KEY_F20' */
#define USBKBD_KEY_F21                    0x70 /* s.a. `KEY_F21' */
#define USBKBD_KEY_F22                    0x71 /* s.a. `KEY_F22' */
#define USBKBD_KEY_F23                    0x72 /* s.a. `KEY_F23' */
#define USBKBD_KEY_F24                    0x73 /* s.a. `KEY_F24' */
#define USBKBD_KEY_EXECUTE                0x74 /* s.a. `KEY_OPEN' */
#define USBKBD_KEY_HELP                   0x75 /* s.a. `KEY_HELP' */
#define USBKBD_KEY_PROPS                  0x76 /* s.a. `KEY_PROPS' */
#define USBKBD_KEY_FRONT                  0x77 /* s.a. `KEY_FRONT' */
#define USBKBD_KEY_STOP                   0x78 /* s.a. `KEY_STOP' */
#define USBKBD_KEY_AGAIN                  0x79 /* s.a. `KEY_AGAIN' */
#define USBKBD_KEY_UNDO                   0x7a /* s.a. `KEY_UNDO' */
#define USBKBD_KEY_CUT                    0x7b /* s.a. `KEY_CUT' */
#define USBKBD_KEY_COPY                   0x7c /* s.a. `KEY_COPY' */
#define USBKBD_KEY_PASTE                  0x7d /* s.a. `KEY_PASTE' */
#define USBKBD_KEY_FIND                   0x7e /* s.a. `KEY_FIND' */
#define USBKBD_KEY_MUTE                   0x7f /* s.a. `KEY_MUTE' */
#define USBKBD_KEY_VOLUMEUP               0x80 /* s.a. `KEY_VOLUMEUP' */
#define USBKBD_KEY_VOLUMEDOWN             0x81 /* s.a. `KEY_VOLUMEDOWN' */
#define USBKBD_KEY_LOCKING_CAPS_LOCK      0x82 /* ?Keyboard Locking Caps Lock? */
#define USBKBD_KEY_LOCKING_NUM_LOCK       0x83 /* ?Keyboard Locking Num Lock? */
#define USBKBD_KEY_LOCKING_SCROLL_LOCK    0x84 /* ?Keyboard Locking Scroll Lock? */
#define USBKBD_KEY_KPCOMMA                0x85 /* s.a. `KEY_KPCOMMA' */
#define USBKBD_KEY_KPEQUAL2               0x86 /* s.a. `KEY_KPEQUAL' */
#define USBKBD_KEY_RO                     0x87 /* s.a. `KEY_RO' */
#define USBKBD_KEY_KATAKANAHIRAGANA       0x88 /* s.a. `KEY_KATAKANAHIRAGANA' */
#define USBKBD_KEY_YEN                    0x89 /* s.a. `KEY_YEN' */
#define USBKBD_KEY_HENKAN                 0x8a /* s.a. `KEY_HENKAN' */
#define USBKBD_KEY_MUHENKAN               0x8b /* s.a. `KEY_MUHENKAN' */
#define USBKBD_KEY_KPJPCOMMA              0x8c /* s.a. `KEY_KPJPCOMMA' */
#define USBKBD_KEY_INTERNATIONAL7         0x8d /* Keyboard International7 */
#define USBKBD_KEY_INTERNATIONAL8         0x8e /* Keyboard International8 */
#define USBKBD_KEY_INTERNATIONAL9         0x8f /* Keyboard International9 */
#define USBKBD_KEY_KEY_HANGEUL            0x90 /* s.a. `KEY_HANGEUL' */
#define USBKBD_KEY_KEY_HANJA              0x91 /* s.a. `KEY_HANJA' */
#define USBKBD_KEY_KEY_KATAKANA           0x92 /* s.a. `KEY_KATAKANA' */
#define USBKBD_KEY_KEY_HIRAGANA           0x93 /* s.a. `KEY_HIRAGANA' */
#define USBKBD_KEY_KEY_ZENKAKUHANKAKU     0x94 /* s.a. `KEY_ZENKAKUHANKAKU' */
#define USBKBD_KEY_LANG6                  0x95 /* Keyboard LANG6 */
#define USBKBD_KEY_LANG7                  0x96 /* Keyboard LANG7 */
#define USBKBD_KEY_LANG8                  0x97 /* Keyboard LANG8 */
#define USBKBD_KEY_LANG9                  0x98 /* Keyboard LANG9 */
#define USBKBD_KEY_ALTERNATE_ERASE        0x99 /* ?Keyboard Alternate Erase? */
#define USBKBD_KEY_SYSRQ                  0x9a /* s.a. `KEY_SYSRQ' */
#define USBKBD_KEY_CANCEL                 0x9b /* s.a. `KEY_CANCEL' */
#define USBKBD_KEY_CLEAR                  0x9c /* s.a. `KEY_CLEAR' */
#define USBKBD_KEY_PREVIOUS               0x9d /* s.a. `KEY_PREVIOUS' */
#define USBKBD_KEY_RETURN                 0x9e /* ?Keyboard Return? */
#define USBKBD_KEY_SEPARATOR              0x9f /* ?Keyboard Separator? */
#define USBKBD_KEY_OUT                    0xa0 /* ?Keyboard Out? */
#define USBKBD_KEY_OPEN                   0xa1 /* s.a. `KEY_OPEN' */
#define USBKBD_KEY_CLEAR_AGAIN            0xa2 /* ?Keyboard Clear/Again? */
#define USBKBD_KEY_CRSEL_PROPS            0xa3 /* ?Keyboard CrSel/Props? */
#define USBKBD_KEY_EXSEL                  0xa4 /* ?Keyboard ExSel? */
/*      USBKBD_KEY_                       0xa5  * ... */
/*      USBKBD_KEY_                       0xa6  * ... */
/*      USBKBD_KEY_                       0xa7  * ... */
/*      USBKBD_KEY_                       0xa8  * ... */
/*      USBKBD_KEY_                       0xa9  * ... */
/*      USBKBD_KEY_                       0xaa  * ... */
/*      USBKBD_KEY_                       0xab  * ... */
/*      USBKBD_KEY_                       0xac  * ... */
/*      USBKBD_KEY_                       0xad  * ... */
/*      USBKBD_KEY_                       0xae  * ... */
/*      USBKBD_KEY_                       0xaf  * ... */
#define USBKBD_KEY_KP_00                  0xb0 /* Keypad 00 */
#define USBKBD_KEY_KP_000                 0xb1 /* Keypad 000 */
#define USBKBD_KEY_KP_THOUSANDS_SEPARATOR 0xb2 /* Keypad Thousands Separator */
#define USBKBD_KEY_KP_DECIMAL_SEPARATOR   0xb3 /* Keypad Decimal Separator */
#define USBKBD_KEY_KP_CURRENCY_UNIT       0xb4 /* Keypad Currency Unit */
#define USBKBD_KEY_KP_CURRENCY_SUB_UNIT   0xb5 /* Keypad Currency Sub-unit */
#define USBKBD_KEY_KP_LEFTPAREN           0xb6 /* s.a. `KEY_KPLEFTPAREN' */
#define USBKBD_KEY_KP_RIGHTPAREN          0xb7 /* s.a. `KEY_KPRIGHTPAREN' */
#define USBKBD_KEY_KP_LBRACE              0xb8 /* Keypad { */
#define USBKBD_KEY_KP_RBRACE              0xb9 /* Keypad } */
#define USBKBD_KEY_KP_TAB                 0xba /* Keypad Tab */
#define USBKBD_KEY_KP_BACKSPACE           0xbb /* Keypad Backspace */
#define USBKBD_KEY_KP_A                   0xbc /* Keypad A */
#define USBKBD_KEY_KP_B                   0xbd /* Keypad B */
#define USBKBD_KEY_KP_C                   0xbe /* Keypad C */
#define USBKBD_KEY_KP_D                   0xbf /* Keypad D */
#define USBKBD_KEY_KP_E                   0xc0 /* Keypad E */
#define USBKBD_KEY_KP_F                   0xc1 /* Keypad F */
#define USBKBD_KEY_KP_XOR                 0xc2 /* Keypad XOR */
#define USBKBD_KEY_KP_CARET               0xc3 /* Keypad ^ */
#define USBKBD_KEY_KP_PERCENT             0xc4 /* Keypad % */
#define USBKBD_KEY_KP_LESS                0xc5 /* Keypad < */
#define USBKBD_KEY_KP_MORE                0xc6 /* Keypad > */
#define USBKBD_KEY_KP_AND                 0xc7 /* Keypad & */
#define USBKBD_KEY_KP_ANDAND              0xc8 /* Keypad && */
#define USBKBD_KEY_KP_PIPE                0xc9 /* Keypad | */
#define USBKBD_KEY_KP_PIPEPIPE            0xca /* Keypad || */
#define USBKBD_KEY_KP_COLON               0xcb /* Keypad : */
#define USBKBD_KEY_KP_POUND               0xcc /* Keypad # */
#define USBKBD_KEY_KP_SPACE               0xcd /* Keypad Space */
#define USBKBD_KEY_KP_AT                  0xce /* Keypad @ */
#define USBKBD_KEY_KP_EXCLAIM             0xcf /* Keypad ! */
#define USBKBD_KEY_KP_MEM_STORE           0xd0 /* Keypad Memory Store */
#define USBKBD_KEY_KP_MEM_RECALL          0xd1 /* Keypad Memory Recall */
#define USBKBD_KEY_KP_MEM_CLEAR           0xd2 /* Keypad Memory Clear */
#define USBKBD_KEY_KP_MEM_ADD             0xd3 /* Keypad Memory Add */
#define USBKBD_KEY_KP_MEM_SUBTRACT        0xd4 /* Keypad Memory Subtract */
#define USBKBD_KEY_KP_MEM_MULTIPLY        0xd5 /* Keypad Memory Multiply */
#define USBKBD_KEY_KP_MEM_DIVIDE          0xd6 /* Keypad Memory Divide */
#define USBKBD_KEY_KP_PLUSMINUS           0xd7 /* Keypad +/- */
#define USBKBD_KEY_KP_CLEAR               0xd8 /* Keypad Clear */
#define USBKBD_KEY_KP_CLEAR_ENTRY         0xd9 /* Keypad Clear Entry */
#define USBKBD_KEY_KP_BINARY              0xda /* Keypad Binary */
#define USBKBD_KEY_KP_OCTAL               0xdb /* Keypad Octal */
#define USBKBD_KEY_KP_DECIMAL             0xdc /* Keypad Decimal */
#define USBKBD_KEY_KP_HEXADECIMAL         0xdd /* Keypad Hexadecimal */
/*      USBKBD_KEY_                       0xde  * ... */
/*      USBKBD_KEY_                       0xdf  * ... */
#define USBKBD_KEY_LEFTCTRL               0xe0 /* s.a. `KEY_LEFTCTRL' */
#define USBKBD_KEY_LEFTSHIFT              0xe1 /* s.a. `KEY_LEFTSHIFT' */
#define USBKBD_KEY_LEFTALT                0xe2 /* s.a. `KEY_LEFTALT' */
#define USBKBD_KEY_LEFTMETA               0xe3 /* s.a. `KEY_LEFTMETA' */
#define USBKBD_KEY_RIGHTCTRL              0xe4 /* s.a. `KEY_RIGHTCTRL' */
#define USBKBD_KEY_RIGHTSHIFT             0xe5 /* s.a. `KEY_RIGHTSHIFT' */
#define USBKBD_KEY_RIGHTALT               0xe6 /* s.a. `KEY_RIGHTALT' */
#define USBKBD_KEY_RIGHTMETA              0xe7 /* s.a. `KEY_RIGHTMETA' */
#define USBKBD_KEY_MM_PLAY_PAUSE          0xe8 /* s.a. `KEY_MM_PLAY_PAUSE' */
#define USBKBD_KEY_MM_STOP                0xe9 /* s.a. `KEY_MM_STOP' */
#define USBKBD_KEY_MM_PREVIOUS_TRACK      0xea /* s.a. `KEY_MM_PREVIOUS_TRACK' */
#define USBKBD_KEY_MM_NEXT_TRACK          0xeb /* s.a. `KEY_MM_NEXT_TRACK' */
#define USBKBD_KEY_EJECTCD                0xec /* s.a. `KEY_EJECTCD' */
#define USBKBD_KEY_VOLUMEUP2              0xed /* s.a. `KEY_VOLUMEUP' */
#define USBKBD_KEY_VOLUMEDOWN2            0xee /* s.a. `KEY_VOLUMEDOWN' */
#define USBKBD_KEY_MUTE2                  0xef /* s.a. `KEY_MUTE' */
#define USBKBD_KEY_WWW                    0xf0 /* s.a. `KEY_WWW' */
#define USBKBD_KEY_WWW_BACK               0xf1 /* s.a. `KEY_WWW_BACK' */
#define USBKBD_KEY_WWW_FORWARD            0xf2 /* s.a. `KEY_WWW_FORWARD' */
#define USBKBD_KEY_WWW_STOP               0xf3 /* s.a. `KEY_WWW_STOP' */
#define USBKBD_KEY_WWW_SEARCH             0xf4 /* s.a. `KEY_WWW_SEARCH' */
#define USBKBD_KEY_SCROLLUP               0xf5 /* s.a. `KEY_SCROLLUP' */
#define USBKBD_KEY_SCROLLDOWN             0xf6 /* s.a. `KEY_SCROLLDOWN' */
#define USBKBD_KEY_EDIT                   0xf7 /* s.a. `KEY_EDIT' */
#define USBKBD_KEY_APIC_SLEEP             0xf8 /* s.a. `KEY_APIC_SLEEP' */
#define USBKBD_KEY_COFFEE                 0xf9 /* s.a. `KEY_COFFEE' */
#define USBKBD_KEY_REFRESH                0xfa /* s.a. `KEY_REFRESH' */
#define USBKBD_KEY_CALC                   0xfb /* s.a. `KEY_CALC' */
/*      USBKBD_KEY_                       0xfc  * ... */
/*      USBKBD_KEY_                       0xfd  * ... */
/*      USBKBD_KEY_                       0xfe  * ... */
/*      USBKBD_KEY_                       0xff  * ... */



#endif /* !_HW_HID_USBKBD_H */
