/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBDISASM__HEXSTR_H
#define GUARD_LIBDISASM__HEXSTR_H 1

#include "api.h"
/**/

/*[[[deemon
for (local x: [:256]) {
	local b = x.tostr(2, 8);
	local h = x.tostr(16, 2);
	print("#define BINSTR_", b, " \"\\x", h, "\"");
}
]]]*/
#define BINSTR_00000000 "\x00"
#define BINSTR_00000001 "\x01"
#define BINSTR_00000010 "\x02"
#define BINSTR_00000011 "\x03"
#define BINSTR_00000100 "\x04"
#define BINSTR_00000101 "\x05"
#define BINSTR_00000110 "\x06"
#define BINSTR_00000111 "\x07"
#define BINSTR_00001000 "\x08"
#define BINSTR_00001001 "\x09"
#define BINSTR_00001010 "\x0a"
#define BINSTR_00001011 "\x0b"
#define BINSTR_00001100 "\x0c"
#define BINSTR_00001101 "\x0d"
#define BINSTR_00001110 "\x0e"
#define BINSTR_00001111 "\x0f"
#define BINSTR_00010000 "\x10"
#define BINSTR_00010001 "\x11"
#define BINSTR_00010010 "\x12"
#define BINSTR_00010011 "\x13"
#define BINSTR_00010100 "\x14"
#define BINSTR_00010101 "\x15"
#define BINSTR_00010110 "\x16"
#define BINSTR_00010111 "\x17"
#define BINSTR_00011000 "\x18"
#define BINSTR_00011001 "\x19"
#define BINSTR_00011010 "\x1a"
#define BINSTR_00011011 "\x1b"
#define BINSTR_00011100 "\x1c"
#define BINSTR_00011101 "\x1d"
#define BINSTR_00011110 "\x1e"
#define BINSTR_00011111 "\x1f"
#define BINSTR_00100000 "\x20"
#define BINSTR_00100001 "\x21"
#define BINSTR_00100010 "\x22"
#define BINSTR_00100011 "\x23"
#define BINSTR_00100100 "\x24"
#define BINSTR_00100101 "\x25"
#define BINSTR_00100110 "\x26"
#define BINSTR_00100111 "\x27"
#define BINSTR_00101000 "\x28"
#define BINSTR_00101001 "\x29"
#define BINSTR_00101010 "\x2a"
#define BINSTR_00101011 "\x2b"
#define BINSTR_00101100 "\x2c"
#define BINSTR_00101101 "\x2d"
#define BINSTR_00101110 "\x2e"
#define BINSTR_00101111 "\x2f"
#define BINSTR_00110000 "\x30"
#define BINSTR_00110001 "\x31"
#define BINSTR_00110010 "\x32"
#define BINSTR_00110011 "\x33"
#define BINSTR_00110100 "\x34"
#define BINSTR_00110101 "\x35"
#define BINSTR_00110110 "\x36"
#define BINSTR_00110111 "\x37"
#define BINSTR_00111000 "\x38"
#define BINSTR_00111001 "\x39"
#define BINSTR_00111010 "\x3a"
#define BINSTR_00111011 "\x3b"
#define BINSTR_00111100 "\x3c"
#define BINSTR_00111101 "\x3d"
#define BINSTR_00111110 "\x3e"
#define BINSTR_00111111 "\x3f"
#define BINSTR_01000000 "\x40"
#define BINSTR_01000001 "\x41"
#define BINSTR_01000010 "\x42"
#define BINSTR_01000011 "\x43"
#define BINSTR_01000100 "\x44"
#define BINSTR_01000101 "\x45"
#define BINSTR_01000110 "\x46"
#define BINSTR_01000111 "\x47"
#define BINSTR_01001000 "\x48"
#define BINSTR_01001001 "\x49"
#define BINSTR_01001010 "\x4a"
#define BINSTR_01001011 "\x4b"
#define BINSTR_01001100 "\x4c"
#define BINSTR_01001101 "\x4d"
#define BINSTR_01001110 "\x4e"
#define BINSTR_01001111 "\x4f"
#define BINSTR_01010000 "\x50"
#define BINSTR_01010001 "\x51"
#define BINSTR_01010010 "\x52"
#define BINSTR_01010011 "\x53"
#define BINSTR_01010100 "\x54"
#define BINSTR_01010101 "\x55"
#define BINSTR_01010110 "\x56"
#define BINSTR_01010111 "\x57"
#define BINSTR_01011000 "\x58"
#define BINSTR_01011001 "\x59"
#define BINSTR_01011010 "\x5a"
#define BINSTR_01011011 "\x5b"
#define BINSTR_01011100 "\x5c"
#define BINSTR_01011101 "\x5d"
#define BINSTR_01011110 "\x5e"
#define BINSTR_01011111 "\x5f"
#define BINSTR_01100000 "\x60"
#define BINSTR_01100001 "\x61"
#define BINSTR_01100010 "\x62"
#define BINSTR_01100011 "\x63"
#define BINSTR_01100100 "\x64"
#define BINSTR_01100101 "\x65"
#define BINSTR_01100110 "\x66"
#define BINSTR_01100111 "\x67"
#define BINSTR_01101000 "\x68"
#define BINSTR_01101001 "\x69"
#define BINSTR_01101010 "\x6a"
#define BINSTR_01101011 "\x6b"
#define BINSTR_01101100 "\x6c"
#define BINSTR_01101101 "\x6d"
#define BINSTR_01101110 "\x6e"
#define BINSTR_01101111 "\x6f"
#define BINSTR_01110000 "\x70"
#define BINSTR_01110001 "\x71"
#define BINSTR_01110010 "\x72"
#define BINSTR_01110011 "\x73"
#define BINSTR_01110100 "\x74"
#define BINSTR_01110101 "\x75"
#define BINSTR_01110110 "\x76"
#define BINSTR_01110111 "\x77"
#define BINSTR_01111000 "\x78"
#define BINSTR_01111001 "\x79"
#define BINSTR_01111010 "\x7a"
#define BINSTR_01111011 "\x7b"
#define BINSTR_01111100 "\x7c"
#define BINSTR_01111101 "\x7d"
#define BINSTR_01111110 "\x7e"
#define BINSTR_01111111 "\x7f"
#define BINSTR_10000000 "\x80"
#define BINSTR_10000001 "\x81"
#define BINSTR_10000010 "\x82"
#define BINSTR_10000011 "\x83"
#define BINSTR_10000100 "\x84"
#define BINSTR_10000101 "\x85"
#define BINSTR_10000110 "\x86"
#define BINSTR_10000111 "\x87"
#define BINSTR_10001000 "\x88"
#define BINSTR_10001001 "\x89"
#define BINSTR_10001010 "\x8a"
#define BINSTR_10001011 "\x8b"
#define BINSTR_10001100 "\x8c"
#define BINSTR_10001101 "\x8d"
#define BINSTR_10001110 "\x8e"
#define BINSTR_10001111 "\x8f"
#define BINSTR_10010000 "\x90"
#define BINSTR_10010001 "\x91"
#define BINSTR_10010010 "\x92"
#define BINSTR_10010011 "\x93"
#define BINSTR_10010100 "\x94"
#define BINSTR_10010101 "\x95"
#define BINSTR_10010110 "\x96"
#define BINSTR_10010111 "\x97"
#define BINSTR_10011000 "\x98"
#define BINSTR_10011001 "\x99"
#define BINSTR_10011010 "\x9a"
#define BINSTR_10011011 "\x9b"
#define BINSTR_10011100 "\x9c"
#define BINSTR_10011101 "\x9d"
#define BINSTR_10011110 "\x9e"
#define BINSTR_10011111 "\x9f"
#define BINSTR_10100000 "\xa0"
#define BINSTR_10100001 "\xa1"
#define BINSTR_10100010 "\xa2"
#define BINSTR_10100011 "\xa3"
#define BINSTR_10100100 "\xa4"
#define BINSTR_10100101 "\xa5"
#define BINSTR_10100110 "\xa6"
#define BINSTR_10100111 "\xa7"
#define BINSTR_10101000 "\xa8"
#define BINSTR_10101001 "\xa9"
#define BINSTR_10101010 "\xaa"
#define BINSTR_10101011 "\xab"
#define BINSTR_10101100 "\xac"
#define BINSTR_10101101 "\xad"
#define BINSTR_10101110 "\xae"
#define BINSTR_10101111 "\xaf"
#define BINSTR_10110000 "\xb0"
#define BINSTR_10110001 "\xb1"
#define BINSTR_10110010 "\xb2"
#define BINSTR_10110011 "\xb3"
#define BINSTR_10110100 "\xb4"
#define BINSTR_10110101 "\xb5"
#define BINSTR_10110110 "\xb6"
#define BINSTR_10110111 "\xb7"
#define BINSTR_10111000 "\xb8"
#define BINSTR_10111001 "\xb9"
#define BINSTR_10111010 "\xba"
#define BINSTR_10111011 "\xbb"
#define BINSTR_10111100 "\xbc"
#define BINSTR_10111101 "\xbd"
#define BINSTR_10111110 "\xbe"
#define BINSTR_10111111 "\xbf"
#define BINSTR_11000000 "\xc0"
#define BINSTR_11000001 "\xc1"
#define BINSTR_11000010 "\xc2"
#define BINSTR_11000011 "\xc3"
#define BINSTR_11000100 "\xc4"
#define BINSTR_11000101 "\xc5"
#define BINSTR_11000110 "\xc6"
#define BINSTR_11000111 "\xc7"
#define BINSTR_11001000 "\xc8"
#define BINSTR_11001001 "\xc9"
#define BINSTR_11001010 "\xca"
#define BINSTR_11001011 "\xcb"
#define BINSTR_11001100 "\xcc"
#define BINSTR_11001101 "\xcd"
#define BINSTR_11001110 "\xce"
#define BINSTR_11001111 "\xcf"
#define BINSTR_11010000 "\xd0"
#define BINSTR_11010001 "\xd1"
#define BINSTR_11010010 "\xd2"
#define BINSTR_11010011 "\xd3"
#define BINSTR_11010100 "\xd4"
#define BINSTR_11010101 "\xd5"
#define BINSTR_11010110 "\xd6"
#define BINSTR_11010111 "\xd7"
#define BINSTR_11011000 "\xd8"
#define BINSTR_11011001 "\xd9"
#define BINSTR_11011010 "\xda"
#define BINSTR_11011011 "\xdb"
#define BINSTR_11011100 "\xdc"
#define BINSTR_11011101 "\xdd"
#define BINSTR_11011110 "\xde"
#define BINSTR_11011111 "\xdf"
#define BINSTR_11100000 "\xe0"
#define BINSTR_11100001 "\xe1"
#define BINSTR_11100010 "\xe2"
#define BINSTR_11100011 "\xe3"
#define BINSTR_11100100 "\xe4"
#define BINSTR_11100101 "\xe5"
#define BINSTR_11100110 "\xe6"
#define BINSTR_11100111 "\xe7"
#define BINSTR_11101000 "\xe8"
#define BINSTR_11101001 "\xe9"
#define BINSTR_11101010 "\xea"
#define BINSTR_11101011 "\xeb"
#define BINSTR_11101100 "\xec"
#define BINSTR_11101101 "\xed"
#define BINSTR_11101110 "\xee"
#define BINSTR_11101111 "\xef"
#define BINSTR_11110000 "\xf0"
#define BINSTR_11110001 "\xf1"
#define BINSTR_11110010 "\xf2"
#define BINSTR_11110011 "\xf3"
#define BINSTR_11110100 "\xf4"
#define BINSTR_11110101 "\xf5"
#define BINSTR_11110110 "\xf6"
#define BINSTR_11110111 "\xf7"
#define BINSTR_11111000 "\xf8"
#define BINSTR_11111001 "\xf9"
#define BINSTR_11111010 "\xfa"
#define BINSTR_11111011 "\xfb"
#define BINSTR_11111100 "\xfc"
#define BINSTR_11111101 "\xfd"
#define BINSTR_11111110 "\xfe"
#define BINSTR_11111111 "\xff"
//[[[end]]]

#define BINSTR2(a, b) BINSTR_##a##b
#define BINSTR(a, b) BINSTR2(a, b)

#define NORMBIN1_0 0
#define NORMBIN1_1 1

#define NORMBIN1_0x0 0
#define NORMBIN1_0x1 1

#define NORMBIN1_0X0 0
#define NORMBIN1_0X1 1

#define NORMBIN1_01 1

#define NORMBIN1_0b0 0
#define NORMBIN1_0b1 1

#define NORMBIN1_0B0 0
#define NORMBIN1_0B1 1

#define NORMBIN2_0 00
#define NORMBIN2_1 01
#define NORMBIN2_2 10
#define NORMBIN2_3 11

#define NORMBIN2_0x0 00
#define NORMBIN2_0x1 01
#define NORMBIN2_0x2 10
#define NORMBIN2_0x3 11

#define NORMBIN2_0X0 00
#define NORMBIN2_0X1 01
#define NORMBIN2_0X2 10
#define NORMBIN2_0X3 11

#define NORMBIN2_01 01
#define NORMBIN2_02 10
#define NORMBIN2_03 11

#define NORMBIN2_0b0  00
#define NORMBIN2_0b00 00
#define NORMBIN2_0b1  01
#define NORMBIN2_0b01 01
#define NORMBIN2_0b10 10
#define NORMBIN2_0b11 11

#define NORMBIN2_0B0  00
#define NORMBIN2_0B00 00
#define NORMBIN2_0B1  01
#define NORMBIN2_0B01 01
#define NORMBIN2_0B10 10
#define NORMBIN2_0B11 11

#define NORMBIN3_0 000
#define NORMBIN3_1 001
#define NORMBIN3_2 010
#define NORMBIN3_3 011
#define NORMBIN3_4 100
#define NORMBIN3_5 101
#define NORMBIN3_6 110
#define NORMBIN3_7 111

#define NORMBIN3_0x0 000
#define NORMBIN3_0x1 001
#define NORMBIN3_0x2 010
#define NORMBIN3_0x3 011
#define NORMBIN3_0x4 100
#define NORMBIN3_0x5 101
#define NORMBIN3_0x6 110
#define NORMBIN3_0x7 111

#define NORMBIN3_0X0 000
#define NORMBIN3_0X1 001
#define NORMBIN3_0X2 010
#define NORMBIN3_0X3 011
#define NORMBIN3_0X4 100
#define NORMBIN3_0X5 101
#define NORMBIN3_0X6 110
#define NORMBIN3_0X7 111

#define NORMBIN3_01 001
#define NORMBIN3_02 010
#define NORMBIN3_03 011
#define NORMBIN3_04 100
#define NORMBIN3_05 101
#define NORMBIN3_06 110
#define NORMBIN3_07 111

#define NORMBIN3_0b0   000
#define NORMBIN3_0b00  000
#define NORMBIN3_0b000 000
#define NORMBIN3_0b1   001
#define NORMBIN3_0b01  001
#define NORMBIN3_0b001 001
#define NORMBIN3_0b10  010
#define NORMBIN3_0b010 010
#define NORMBIN3_0b11  011
#define NORMBIN3_0b011 011
#define NORMBIN3_0b100 100
#define NORMBIN3_0b101 101
#define NORMBIN3_0b110 110
#define NORMBIN3_0b111 111

#define NORMBIN3_0B0   000
#define NORMBIN3_0B00  000
#define NORMBIN3_0B000 000
#define NORMBIN3_0B1   001
#define NORMBIN3_0B01  001
#define NORMBIN3_0B001 001
#define NORMBIN3_0B10  010
#define NORMBIN3_0B010 010
#define NORMBIN3_0B11  011
#define NORMBIN3_0B011 011
#define NORMBIN3_0B100 100
#define NORMBIN3_0B101 101
#define NORMBIN3_0B110 110
#define NORMBIN3_0B111 111

#define NORMBIN4_0  0000
#define NORMBIN4_1  0001
#define NORMBIN4_2  0010
#define NORMBIN4_3  0011
#define NORMBIN4_4  0100
#define NORMBIN4_5  0101
#define NORMBIN4_6  0110
#define NORMBIN4_7  0111
#define NORMBIN4_8  1000
#define NORMBIN4_9  1001
#define NORMBIN4_10 1010
#define NORMBIN4_11 1011
#define NORMBIN4_12 1100
#define NORMBIN4_13 1101
#define NORMBIN4_14 1110
#define NORMBIN4_15 1111

#define NORMBIN4_0x0 0000
#define NORMBIN4_0x1 0001
#define NORMBIN4_0x2 0010
#define NORMBIN4_0x3 0011
#define NORMBIN4_0x4 0100
#define NORMBIN4_0x5 0101
#define NORMBIN4_0x6 0110
#define NORMBIN4_0x7 0111
#define NORMBIN4_0x8 1000
#define NORMBIN4_0x9 1001
#define NORMBIN4_0xa 1010
#define NORMBIN4_0xb 1011
#define NORMBIN4_0xc 1100
#define NORMBIN4_0xd 1101
#define NORMBIN4_0xe 1110
#define NORMBIN4_0xf 1111

#define NORMBIN4_0X0 0000
#define NORMBIN4_0X1 0001
#define NORMBIN4_0X2 0010
#define NORMBIN4_0X3 0011
#define NORMBIN4_0X4 0100
#define NORMBIN4_0X5 0101
#define NORMBIN4_0X6 0110
#define NORMBIN4_0X7 0111
#define NORMBIN4_0X8 1000
#define NORMBIN4_0X9 1001
#define NORMBIN4_0XA 1010
#define NORMBIN4_0XB 1011
#define NORMBIN4_0XC 1100
#define NORMBIN4_0XD 1101
#define NORMBIN4_0XE 1110
#define NORMBIN4_0XF 1111

#define NORMBIN4_01  0001
#define NORMBIN4_02  0010
#define NORMBIN4_03  0011
#define NORMBIN4_04  0100
#define NORMBIN4_05  0101
#define NORMBIN4_06  0110
#define NORMBIN4_07  0111
#define NORMBIN4_010 1000
#define NORMBIN4_011 1001
#define NORMBIN4_012 1010
#define NORMBIN4_013 1011
#define NORMBIN4_014 1100
#define NORMBIN4_015 1101
#define NORMBIN4_016 1110
#define NORMBIN4_017 1111

#define NORMBIN4_0b0    0000
#define NORMBIN4_0b00   0000
#define NORMBIN4_0b000  0000
#define NORMBIN4_0b0000 0000
#define NORMBIN4_0b1    0001
#define NORMBIN4_0b01   0001
#define NORMBIN4_0b001  0001
#define NORMBIN4_0b0001 0001
#define NORMBIN4_0b10   0010
#define NORMBIN4_0b010  0010
#define NORMBIN4_0b0010 0010
#define NORMBIN4_0b11   0011
#define NORMBIN4_0b011  0011
#define NORMBIN4_0b0011 0011
#define NORMBIN4_0b100  0100
#define NORMBIN4_0b0100 0100
#define NORMBIN4_0b101  0101
#define NORMBIN4_0b0101 0101
#define NORMBIN4_0b110  0110
#define NORMBIN4_0b0110 0110
#define NORMBIN4_0b111  0111
#define NORMBIN4_0b0111 0111
#define NORMBIN4_0b1000 1000
#define NORMBIN4_0b1001 1001
#define NORMBIN4_0b1010 1010
#define NORMBIN4_0b1011 1011
#define NORMBIN4_0b1100 1100
#define NORMBIN4_0b1101 1101
#define NORMBIN4_0b1110 1110
#define NORMBIN4_0b1111 1111

#define NORMBIN4_0B0    0000
#define NORMBIN4_0B00   0000
#define NORMBIN4_0B000  0000
#define NORMBIN4_0B0000 0000
#define NORMBIN4_0B1    0001
#define NORMBIN4_0B01   0001
#define NORMBIN4_0B001  0001
#define NORMBIN4_0B0001 0001
#define NORMBIN4_0B10   0010
#define NORMBIN4_0B010  0010
#define NORMBIN4_0B0010 0010
#define NORMBIN4_0B11   0011
#define NORMBIN4_0B011  0011
#define NORMBIN4_0B0011 0011
#define NORMBIN4_0B100  0100
#define NORMBIN4_0B0100 0100
#define NORMBIN4_0B101  0101
#define NORMBIN4_0B0101 0101
#define NORMBIN4_0B110  0110
#define NORMBIN4_0B0110 0110
#define NORMBIN4_0B111  0111
#define NORMBIN4_0B0111 0111
#define NORMBIN4_0B1000 1000
#define NORMBIN4_0B1001 1001
#define NORMBIN4_0B1010 1010
#define NORMBIN4_0B1011 1011
#define NORMBIN4_0B1100 1100
#define NORMBIN4_0B1101 1101
#define NORMBIN4_0B1110 1110
#define NORMBIN4_0B1111 1111

#define _NORMBIN1(x) NORMBIN1_##x
#define NORMBIN1(x) _NORMBIN1(x)
#define _NORMBIN2(x) NORMBIN2_##x
#define NORMBIN2(x) _NORMBIN2(x)
#define _NORMBIN3(x) NORMBIN3_##x
#define NORMBIN3(x) _NORMBIN3(x)
#define _NORMBIN4(x) NORMBIN4_##x
#define NORMBIN4(x) _NORMBIN4(x)

#endif /* !GUARD_LIBDISASM__HEXSTR_H */
