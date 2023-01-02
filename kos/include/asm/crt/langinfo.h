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
#ifndef _ASM_CRT_LANGINFO_H
#define _ASM_CRT_LANGINFO_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <asm/crt/locale.h>

#define _NL_ITEM(category, index) (((category) << 16) | (index))
#define _NL_ITEM_CATEGORY(item)   (__CCAST(int)(item) >> 16)
#define _NL_ITEM_INDEX(item)      (__CCAST(int)(item) & 0xffff)

#define _NL_TIME_ABDAY_1                       _NL_ITEM(__LC_TIME, 0x00) /* "Sun" */
#define _NL_TIME_ABDAY_2                       _NL_ITEM(__LC_TIME, 0x01) /* "Mon" */
#define _NL_TIME_ABDAY_3                       _NL_ITEM(__LC_TIME, 0x02) /* "Tue" */
#define _NL_TIME_ABDAY_4                       _NL_ITEM(__LC_TIME, 0x03) /* "Wed" */
#define _NL_TIME_ABDAY_5                       _NL_ITEM(__LC_TIME, 0x04) /* "Thu" */
#define _NL_TIME_ABDAY_6                       _NL_ITEM(__LC_TIME, 0x05) /* "Fri" */
#define _NL_TIME_ABDAY_7                       _NL_ITEM(__LC_TIME, 0x06) /* "Sat" */
#define _NL_TIME_DAY_1                         _NL_ITEM(__LC_TIME, 0x07) /* "Sunday" */
#define _NL_TIME_DAY_2                         _NL_ITEM(__LC_TIME, 0x08) /* "Monday" */
#define _NL_TIME_DAY_3                         _NL_ITEM(__LC_TIME, 0x09) /* "Tuesday" */
#define _NL_TIME_DAY_4                         _NL_ITEM(__LC_TIME, 0x0a) /* "Wednesday" */
#define _NL_TIME_DAY_5                         _NL_ITEM(__LC_TIME, 0x0b) /* "Thursday" */
#define _NL_TIME_DAY_6                         _NL_ITEM(__LC_TIME, 0x0c) /* "Friday" */
#define _NL_TIME_DAY_7                         _NL_ITEM(__LC_TIME, 0x0d) /* "Saturday" */
#define _NL_TIME_ABMON_1                       _NL_ITEM(__LC_TIME, 0x0e) /* "Jan" */
#define _NL_TIME_ABMON_2                       _NL_ITEM(__LC_TIME, 0x0f) /* "Feb" */
#define _NL_TIME_ABMON_3                       _NL_ITEM(__LC_TIME, 0x10) /* "Mar" */
#define _NL_TIME_ABMON_4                       _NL_ITEM(__LC_TIME, 0x11) /* "Apr" */
#define _NL_TIME_ABMON_5                       _NL_ITEM(__LC_TIME, 0x12) /* "May" */
#define _NL_TIME_ABMON_6                       _NL_ITEM(__LC_TIME, 0x13) /* "Jun" */
#define _NL_TIME_ABMON_7                       _NL_ITEM(__LC_TIME, 0x14) /* "Jul" */
#define _NL_TIME_ABMON_8                       _NL_ITEM(__LC_TIME, 0x15) /* "Aug" */
#define _NL_TIME_ABMON_9                       _NL_ITEM(__LC_TIME, 0x16) /* "Sep" */
#define _NL_TIME_ABMON_10                      _NL_ITEM(__LC_TIME, 0x17) /* "Oct" */
#define _NL_TIME_ABMON_11                      _NL_ITEM(__LC_TIME, 0x18) /* "Nov" */
#define _NL_TIME_ABMON_12                      _NL_ITEM(__LC_TIME, 0x19) /* "Dec" */
#define _NL_TIME_MON_1                         _NL_ITEM(__LC_TIME, 0x1a) /* "January" */
#define _NL_TIME_MON_2                         _NL_ITEM(__LC_TIME, 0x1b) /* "February" */
#define _NL_TIME_MON_3                         _NL_ITEM(__LC_TIME, 0x1c) /* "March" */
#define _NL_TIME_MON_4                         _NL_ITEM(__LC_TIME, 0x1d) /* "April" */
#define _NL_TIME_MON_5                         _NL_ITEM(__LC_TIME, 0x1e) /* "May" */
#define _NL_TIME_MON_6                         _NL_ITEM(__LC_TIME, 0x1f) /* "June" */
#define _NL_TIME_MON_7                         _NL_ITEM(__LC_TIME, 0x20) /* "July" */
#define _NL_TIME_MON_8                         _NL_ITEM(__LC_TIME, 0x21) /* "August" */
#define _NL_TIME_MON_9                         _NL_ITEM(__LC_TIME, 0x22) /* "September" */
#define _NL_TIME_MON_10                        _NL_ITEM(__LC_TIME, 0x23) /* "October" */
#define _NL_TIME_MON_11                        _NL_ITEM(__LC_TIME, 0x24) /* "November" */
#define _NL_TIME_MON_12                        _NL_ITEM(__LC_TIME, 0x25) /* "December" */
#define _NL_TIME_AM_STR                        _NL_ITEM(__LC_TIME, 0x26) /* "AM" */
#define _NL_TIME_PM_STR                        _NL_ITEM(__LC_TIME, 0x27) /* "PM" */
#define _NL_TIME_D_T_FMT                       _NL_ITEM(__LC_TIME, 0x28) /* "%a %b %e %H:%M:%S %Y" */
#define _NL_TIME_D_FMT                         _NL_ITEM(__LC_TIME, 0x29) /* "%m/%d/%y" */
#define _NL_TIME_T_FMT                         _NL_ITEM(__LC_TIME, 0x2a) /* "%H:%M:%S" */
#define _NL_TIME_T_FMT_AMPM                    _NL_ITEM(__LC_TIME, 0x2b) /* "%I:%M:%S %p" */
#define _NL_TIME_ERA                           _NL_ITEM(__LC_TIME, 0x2c) /* "" */
#define _NL_TIME_ERA_YEAR                      _NL_ITEM(__LC_TIME, 0x2d) /* "" */
#define _NL_TIME_ERA_D_FMT                     _NL_ITEM(__LC_TIME, 0x2e) /* "" */
#define _NL_TIME_ALT_DIGITS                    _NL_ITEM(__LC_TIME, 0x2f) /* "" */
#define _NL_TIME_ERA_D_T_FMT                   _NL_ITEM(__LC_TIME, 0x30) /* "" */
#define _NL_TIME_ERA_T_FMT                     _NL_ITEM(__LC_TIME, 0x31) /* "" */
#define _NL_TIME_ERA_NUM_ENTRIES               _NL_ITEM(__LC_TIME, 0x32) /* "" */
#define _NL_TIME_ERA_ENTRIES                   _NL_ITEM(__LC_TIME, 0x33) /* "" */
#define _NL_TIME_WABDAY_1                      _NL_ITEM(__LC_TIME, 0x34) /* L"Sun" */
#define _NL_TIME_WABDAY_2                      _NL_ITEM(__LC_TIME, 0x35) /* L"Mon" */
#define _NL_TIME_WABDAY_3                      _NL_ITEM(__LC_TIME, 0x36) /* L"Tue" */
#define _NL_TIME_WABDAY_4                      _NL_ITEM(__LC_TIME, 0x37) /* L"Wed" */
#define _NL_TIME_WABDAY_5                      _NL_ITEM(__LC_TIME, 0x38) /* L"Thu" */
#define _NL_TIME_WABDAY_6                      _NL_ITEM(__LC_TIME, 0x39) /* L"Fri" */
#define _NL_TIME_WABDAY_7                      _NL_ITEM(__LC_TIME, 0x3a) /* L"Sat" */
#define _NL_TIME_WDAY_1                        _NL_ITEM(__LC_TIME, 0x3b) /* L"Sunday" */
#define _NL_TIME_WDAY_2                        _NL_ITEM(__LC_TIME, 0x3c) /* L"Monday" */
#define _NL_TIME_WDAY_3                        _NL_ITEM(__LC_TIME, 0x3d) /* L"Tuesday" */
#define _NL_TIME_WDAY_4                        _NL_ITEM(__LC_TIME, 0x3e) /* L"Wednesday" */
#define _NL_TIME_WDAY_5                        _NL_ITEM(__LC_TIME, 0x3f) /* L"Thursday" */
#define _NL_TIME_WDAY_6                        _NL_ITEM(__LC_TIME, 0x40) /* L"Friday" */
#define _NL_TIME_WDAY_7                        _NL_ITEM(__LC_TIME, 0x41) /* L"Saturday" */
#define _NL_TIME_WABMON_1                      _NL_ITEM(__LC_TIME, 0x42) /* L"Jan" */
#define _NL_TIME_WABMON_2                      _NL_ITEM(__LC_TIME, 0x43) /* L"Feb" */
#define _NL_TIME_WABMON_3                      _NL_ITEM(__LC_TIME, 0x44) /* L"Mar" */
#define _NL_TIME_WABMON_4                      _NL_ITEM(__LC_TIME, 0x45) /* L"Apr" */
#define _NL_TIME_WABMON_5                      _NL_ITEM(__LC_TIME, 0x46) /* L"May" */
#define _NL_TIME_WABMON_6                      _NL_ITEM(__LC_TIME, 0x47) /* L"Jun" */
#define _NL_TIME_WABMON_7                      _NL_ITEM(__LC_TIME, 0x48) /* L"Jul" */
#define _NL_TIME_WABMON_8                      _NL_ITEM(__LC_TIME, 0x49) /* L"Aug" */
#define _NL_TIME_WABMON_9                      _NL_ITEM(__LC_TIME, 0x4a) /* L"Sep" */
#define _NL_TIME_WABMON_10                     _NL_ITEM(__LC_TIME, 0x4b) /* L"Oct" */
#define _NL_TIME_WABMON_11                     _NL_ITEM(__LC_TIME, 0x4c) /* L"Nov" */
#define _NL_TIME_WABMON_12                     _NL_ITEM(__LC_TIME, 0x4d) /* L"Dec" */
#define _NL_TIME_WMON_1                        _NL_ITEM(__LC_TIME, 0x4e) /* L"January" */
#define _NL_TIME_WMON_2                        _NL_ITEM(__LC_TIME, 0x4f) /* L"February" */
#define _NL_TIME_WMON_3                        _NL_ITEM(__LC_TIME, 0x50) /* L"March" */
#define _NL_TIME_WMON_4                        _NL_ITEM(__LC_TIME, 0x51) /* L"April" */
#define _NL_TIME_WMON_5                        _NL_ITEM(__LC_TIME, 0x52) /* L"May" */
#define _NL_TIME_WMON_6                        _NL_ITEM(__LC_TIME, 0x53) /* L"June" */
#define _NL_TIME_WMON_7                        _NL_ITEM(__LC_TIME, 0x54) /* L"July" */
#define _NL_TIME_WMON_8                        _NL_ITEM(__LC_TIME, 0x55) /* L"August" */
#define _NL_TIME_WMON_9                        _NL_ITEM(__LC_TIME, 0x56) /* L"September" */
#define _NL_TIME_WMON_10                       _NL_ITEM(__LC_TIME, 0x57) /* L"October" */
#define _NL_TIME_WMON_11                       _NL_ITEM(__LC_TIME, 0x58) /* L"November" */
#define _NL_TIME_WMON_12                       _NL_ITEM(__LC_TIME, 0x59) /* L"December" */
#define _NL_TIME_WAM_STR                       _NL_ITEM(__LC_TIME, 0x5a) /* L"AM" */
#define _NL_TIME_WPM_STR                       _NL_ITEM(__LC_TIME, 0x5b) /* L"PM" */
#define _NL_TIME_WD_T_FMT                      _NL_ITEM(__LC_TIME, 0x5c) /* L"%a %b %e %H:%M:%S %Y" */
#define _NL_TIME_WD_FMT                        _NL_ITEM(__LC_TIME, 0x5d) /* L"%m/%d/%y" */
#define _NL_TIME_WT_FMT                        _NL_ITEM(__LC_TIME, 0x5e) /* L"%H:%M:%S" */
#define _NL_TIME_WT_FMT_AMPM                   _NL_ITEM(__LC_TIME, 0x5f) /* L"%I:%M:%S %p" */
#define _NL_TIME_WERA_YEAR                     _NL_ITEM(__LC_TIME, 0x60) /* L"" */
#define _NL_TIME_WERA_D_FMT                    _NL_ITEM(__LC_TIME, 0x61) /* L"" */
#define _NL_TIME_WALT_DIGITS                   _NL_ITEM(__LC_TIME, 0x62) /* L"" */
#define _NL_TIME_WERA_D_T_FMT                  _NL_ITEM(__LC_TIME, 0x63) /* L"" */
#define _NL_TIME_WERA_T_FMT                    _NL_ITEM(__LC_TIME, 0x64) /* L"" */
#define _NL_TIME_WEEK_NDAYS                    _NL_ITEM(__LC_TIME, 0x65) /* 0x7 [pointer-to-uint8_t] */
#define _NL_TIME_WEEK_1STDAY                   _NL_ITEM(__LC_TIME, 0x66) /* 19971130 [uintptr_t] */
#define _NL_TIME_WEEK_1STWEEK                  _NL_ITEM(__LC_TIME, 0x67) /* 0x4 [pointer-to-uint8_t] */
#define _NL_TIME_FIRST_WEEKDAY                 _NL_ITEM(__LC_TIME, 0x68) /* 0x1 [pointer-to-uint8_t] */
#define _NL_TIME_FIRST_WORKDAY                 _NL_ITEM(__LC_TIME, 0x69) /* 0x2 [pointer-to-uint8_t] */
#define _NL_TIME_CAL_DIRECTION                 _NL_ITEM(__LC_TIME, 0x6a) /* 0x1 [pointer-to-uint8_t] */
#define _NL_TIME_TIMEZONE                      _NL_ITEM(__LC_TIME, 0x6b) /* "" */
#define _NL_TIME_DATE_FMT                      _NL_ITEM(__LC_TIME, 0x6c) /* "%a %b %e %H:%M:%S %Z %Y" */
#define _NL_TIME_W_DATE_FMT                    _NL_ITEM(__LC_TIME, 0x6d) /* L"%a %b %e %H:%M:%S %Z %Y" */
#define _NL_TIME_CODESET                       _NL_ITEM(__LC_TIME, 0x6e) /* "utf-8" */
#define _NL_TIME_ALTMON_1                      _NL_ITEM(__LC_TIME, 0x6f) /* "January" */
#define _NL_TIME_ALTMON_2                      _NL_ITEM(__LC_TIME, 0x70) /* "February" */
#define _NL_TIME_ALTMON_3                      _NL_ITEM(__LC_TIME, 0x71) /* "March" */
#define _NL_TIME_ALTMON_4                      _NL_ITEM(__LC_TIME, 0x72) /* "April" */
#define _NL_TIME_ALTMON_5                      _NL_ITEM(__LC_TIME, 0x73) /* "May" */
#define _NL_TIME_ALTMON_6                      _NL_ITEM(__LC_TIME, 0x74) /* "June" */
#define _NL_TIME_ALTMON_7                      _NL_ITEM(__LC_TIME, 0x75) /* "July" */
#define _NL_TIME_ALTMON_8                      _NL_ITEM(__LC_TIME, 0x76) /* "August" */
#define _NL_TIME_ALTMON_9                      _NL_ITEM(__LC_TIME, 0x77) /* "September" */
#define _NL_TIME_ALTMON_10                     _NL_ITEM(__LC_TIME, 0x78) /* "October" */
#define _NL_TIME_ALTMON_11                     _NL_ITEM(__LC_TIME, 0x79) /* "November" */
#define _NL_TIME_ALTMON_12                     _NL_ITEM(__LC_TIME, 0x7a) /* "December" */
#define _NL_TIME_WALTMON_1                     _NL_ITEM(__LC_TIME, 0x7b) /* L"January" */
#define _NL_TIME_WALTMON_2                     _NL_ITEM(__LC_TIME, 0x7c) /* L"February" */
#define _NL_TIME_WALTMON_3                     _NL_ITEM(__LC_TIME, 0x7d) /* L"March" */
#define _NL_TIME_WALTMON_4                     _NL_ITEM(__LC_TIME, 0x7e) /* L"April" */
#define _NL_TIME_WALTMON_5                     _NL_ITEM(__LC_TIME, 0x7f) /* L"May" */
#define _NL_TIME_WALTMON_6                     _NL_ITEM(__LC_TIME, 0x80) /* L"June" */
#define _NL_TIME_WALTMON_7                     _NL_ITEM(__LC_TIME, 0x81) /* L"July" */
#define _NL_TIME_WALTMON_8                     _NL_ITEM(__LC_TIME, 0x82) /* L"August" */
#define _NL_TIME_WALTMON_9                     _NL_ITEM(__LC_TIME, 0x83) /* L"September" */
#define _NL_TIME_WALTMON_10                    _NL_ITEM(__LC_TIME, 0x84) /* L"October" */
#define _NL_TIME_WALTMON_11                    _NL_ITEM(__LC_TIME, 0x85) /* L"November" */
#define _NL_TIME_WALTMON_12                    _NL_ITEM(__LC_TIME, 0x86) /* L"December" */
#define _NL_TIME_ABALTMON_1                    _NL_ITEM(__LC_TIME, 0x87) /* "Jan" */
#define _NL_TIME_ABALTMON_2                    _NL_ITEM(__LC_TIME, 0x88) /* "Feb" */
#define _NL_TIME_ABALTMON_3                    _NL_ITEM(__LC_TIME, 0x89) /* "Mar" */
#define _NL_TIME_ABALTMON_4                    _NL_ITEM(__LC_TIME, 0x8a) /* "Apr" */
#define _NL_TIME_ABALTMON_5                    _NL_ITEM(__LC_TIME, 0x8b) /* "May" */
#define _NL_TIME_ABALTMON_6                    _NL_ITEM(__LC_TIME, 0x8c) /* "Jun" */
#define _NL_TIME_ABALTMON_7                    _NL_ITEM(__LC_TIME, 0x8d) /* "Jul" */
#define _NL_TIME_ABALTMON_8                    _NL_ITEM(__LC_TIME, 0x8e) /* "Aug" */
#define _NL_TIME_ABALTMON_9                    _NL_ITEM(__LC_TIME, 0x8f) /* "Sep" */
#define _NL_TIME_ABALTMON_10                   _NL_ITEM(__LC_TIME, 0x90) /* "Oct" */
#define _NL_TIME_ABALTMON_11                   _NL_ITEM(__LC_TIME, 0x91) /* "Nov" */
#define _NL_TIME_ABALTMON_12                   _NL_ITEM(__LC_TIME, 0x92) /* "Dec" */
#define _NL_TIME_WABALTMON_1                   _NL_ITEM(__LC_TIME, 0x93) /* L"Jan" */
#define _NL_TIME_WABALTMON_2                   _NL_ITEM(__LC_TIME, 0x94) /* L"Feb" */
#define _NL_TIME_WABALTMON_3                   _NL_ITEM(__LC_TIME, 0x95) /* L"Mar" */
#define _NL_TIME_WABALTMON_4                   _NL_ITEM(__LC_TIME, 0x96) /* L"Apr" */
#define _NL_TIME_WABALTMON_5                   _NL_ITEM(__LC_TIME, 0x97) /* L"May" */
#define _NL_TIME_WABALTMON_6                   _NL_ITEM(__LC_TIME, 0x98) /* L"Jun" */
#define _NL_TIME_WABALTMON_7                   _NL_ITEM(__LC_TIME, 0x99) /* L"Jul" */
#define _NL_TIME_WABALTMON_8                   _NL_ITEM(__LC_TIME, 0x9a) /* L"Aug" */
#define _NL_TIME_WABALTMON_9                   _NL_ITEM(__LC_TIME, 0x9b) /* L"Sep" */
#define _NL_TIME_WABALTMON_10                  _NL_ITEM(__LC_TIME, 0x9c) /* L"Oct" */
#define _NL_TIME_WABALTMON_11                  _NL_ITEM(__LC_TIME, 0x9d) /* L"Nov" */
#define _NL_TIME_WABALTMON_12                  _NL_ITEM(__LC_TIME, 0x9e) /* L"Dec" */
#define _NL_NUM_LC_TIME                        _NL_ITEM(__LC_TIME, 0x9f)
#define _NL_COLLATE_NRULES                     _NL_ITEM(__LC_COLLATE, 0x00) /* 0 [uintptr_t] */
#define _NL_COLLATE_RULESETS                   _NL_ITEM(__LC_COLLATE, 0x01) /* "" */
#define _NL_COLLATE_TABLEMB                    _NL_ITEM(__LC_COLLATE, 0x02) /* L"..." */
#define _NL_COLLATE_WEIGHTMB                   _NL_ITEM(__LC_COLLATE, 0x03) /* L"..." */
#define _NL_COLLATE_EXTRAMB                    _NL_ITEM(__LC_COLLATE, 0x04) /* L"..." */
#define _NL_COLLATE_INDIRECTMB                 _NL_ITEM(__LC_COLLATE, 0x05) /* L"..." */
#define _NL_COLLATE_GAP1                       _NL_ITEM(__LC_COLLATE, 0x06) /* L"..." */
#define _NL_COLLATE_GAP2                       _NL_ITEM(__LC_COLLATE, 0x07) /* L"..." */
#define _NL_COLLATE_GAP3                       _NL_ITEM(__LC_COLLATE, 0x08) /* L"..." */
#define _NL_COLLATE_TABLEWC                    _NL_ITEM(__LC_COLLATE, 0x09) /* L"..." */
#define _NL_COLLATE_WEIGHTWC                   _NL_ITEM(__LC_COLLATE, 0x0a) /* L"..." */
#define _NL_COLLATE_EXTRAWC                    _NL_ITEM(__LC_COLLATE, 0x0b) /* L"..." */
#define _NL_COLLATE_INDIRECTWC                 _NL_ITEM(__LC_COLLATE, 0x0c) /* L"..." */
#define _NL_COLLATE_SYMB_HASH_SIZEMB           _NL_ITEM(__LC_COLLATE, 0x0d) /* 0 [uintptr_t] */
#define _NL_COLLATE_SYMB_TABLEMB               _NL_ITEM(__LC_COLLATE, 0x0e) /* L"..." */
#define _NL_COLLATE_SYMB_EXTRAMB               _NL_ITEM(__LC_COLLATE, 0x0f) /* L"..." */
#define _NL_COLLATE_COLLSEQMB                  _NL_ITEM(__LC_COLLATE, 0x10) /* L"..." */
#define _NL_COLLATE_COLLSEQWC                  _NL_ITEM(__LC_COLLATE, 0x11) /* L"..." */
#define _NL_COLLATE_CODESET                    _NL_ITEM(__LC_COLLATE, 0x12) /* "utf-8" */
#define _NL_NUM_LC_COLLATE                     _NL_ITEM(__LC_COLLATE, 0x13)
#define _NL_CTYPE_CLASS                        _NL_ITEM(__LC_CTYPE, 0x00) /* L"" */
#define _NL_CTYPE_TOUPPER                      _NL_ITEM(__LC_CTYPE, 0x01) /* L"..." */
#define _NL_CTYPE_GAP1                         _NL_ITEM(__LC_CTYPE, 0x02) /* 0 [pointer-to-uint8_t] */
#define _NL_CTYPE_TOLOWER                      _NL_ITEM(__LC_CTYPE, 0x03) /* L"..." */
#define _NL_CTYPE_GAP2                         _NL_ITEM(__LC_CTYPE, 0x04) /* 0 [pointer-to-uint8_t] */
#define _NL_CTYPE_CLASS32                      _NL_ITEM(__LC_CTYPE, 0x05) /* L"..." */
#define _NL_CTYPE_GAP3                         _NL_ITEM(__LC_CTYPE, 0x06) /* "" */
#define _NL_CTYPE_GAP4                         _NL_ITEM(__LC_CTYPE, 0x07) /* "" */
#define _NL_CTYPE_GAP5                         _NL_ITEM(__LC_CTYPE, 0x08) /* "" */
#define _NL_CTYPE_GAP6                         _NL_ITEM(__LC_CTYPE, 0x09) /* "" */
#define _NL_CTYPE_CLASS_NAMES                  _NL_ITEM(__LC_CTYPE, 0x0a) /* "upper\0lower\0alpha\0digit\0xdigit\0space\0print\0graph\0blank\0cntrl\0punct\0alnum\0\0" */
#define _NL_CTYPE_MAP_NAMES                    _NL_ITEM(__LC_CTYPE, 0x0b) /* "toupper\0tolower\0\0" */
#define _NL_CTYPE_WIDTH                        _NL_ITEM(__LC_CTYPE, 0x0c) /* [0x07,0x00] [array-of-uint8_t] */
#define _NL_CTYPE_MB_CUR_MAX                   _NL_ITEM(__LC_CTYPE, 0x0d) /* 1 [uintptr_t] */
#define _NL_CTYPE_CODESET_NAME                 _NL_ITEM(__LC_CTYPE, 0x0e) /* "utf-8" */
#define _NL_CTYPE_TOUPPER32                    _NL_ITEM(__LC_CTYPE, 0x0f) /* L"" */
#define _NL_CTYPE_TOLOWER32                    _NL_ITEM(__LC_CTYPE, 0x10) /* L"" */
#define _NL_CTYPE_CLASS_OFFSET                 _NL_ITEM(__LC_CTYPE, 0x11) /* 72 [uintptr_t] */
#define _NL_CTYPE_MAP_OFFSET                   _NL_ITEM(__LC_CTYPE, 0x12) /* 84 [uintptr_t] */
#define _NL_CTYPE_INDIGITS_MB_LEN              _NL_ITEM(__LC_CTYPE, 0x13) /* 1 [uintptr_t] */
#define _NL_CTYPE_INDIGITS0_MB                 _NL_ITEM(__LC_CTYPE, 0x14) /* "0" */
#define _NL_CTYPE_INDIGITS1_MB                 _NL_ITEM(__LC_CTYPE, 0x15) /* "1" */
#define _NL_CTYPE_INDIGITS2_MB                 _NL_ITEM(__LC_CTYPE, 0x16) /* "2" */
#define _NL_CTYPE_INDIGITS3_MB                 _NL_ITEM(__LC_CTYPE, 0x17) /* "3" */
#define _NL_CTYPE_INDIGITS4_MB                 _NL_ITEM(__LC_CTYPE, 0x18) /* "4" */
#define _NL_CTYPE_INDIGITS5_MB                 _NL_ITEM(__LC_CTYPE, 0x19) /* "5" */
#define _NL_CTYPE_INDIGITS6_MB                 _NL_ITEM(__LC_CTYPE, 0x1a) /* "6" */
#define _NL_CTYPE_INDIGITS7_MB                 _NL_ITEM(__LC_CTYPE, 0x1b) /* "7" */
#define _NL_CTYPE_INDIGITS8_MB                 _NL_ITEM(__LC_CTYPE, 0x1c) /* "8" */
#define _NL_CTYPE_INDIGITS9_MB                 _NL_ITEM(__LC_CTYPE, 0x1d) /* "9" */
#define _NL_CTYPE_INDIGITS_WC_LEN              _NL_ITEM(__LC_CTYPE, 0x1e) /* 1 [uintptr_t] */
#define _NL_CTYPE_INDIGITS0_WC                 _NL_ITEM(__LC_CTYPE, 0x1f) /* L"0" */
#define _NL_CTYPE_INDIGITS1_WC                 _NL_ITEM(__LC_CTYPE, 0x20) /* L"1" */
#define _NL_CTYPE_INDIGITS2_WC                 _NL_ITEM(__LC_CTYPE, 0x21) /* L"2" */
#define _NL_CTYPE_INDIGITS3_WC                 _NL_ITEM(__LC_CTYPE, 0x22) /* L"3" */
#define _NL_CTYPE_INDIGITS4_WC                 _NL_ITEM(__LC_CTYPE, 0x23) /* L"4" */
#define _NL_CTYPE_INDIGITS5_WC                 _NL_ITEM(__LC_CTYPE, 0x24) /* L"5" */
#define _NL_CTYPE_INDIGITS6_WC                 _NL_ITEM(__LC_CTYPE, 0x25) /* L"6" */
#define _NL_CTYPE_INDIGITS7_WC                 _NL_ITEM(__LC_CTYPE, 0x26) /* L"7" */
#define _NL_CTYPE_INDIGITS8_WC                 _NL_ITEM(__LC_CTYPE, 0x27) /* L"8" */
#define _NL_CTYPE_INDIGITS9_WC                 _NL_ITEM(__LC_CTYPE, 0x28) /* L"9" */
#define _NL_CTYPE_OUTDIGIT0_MB                 _NL_ITEM(__LC_CTYPE, 0x29) /* "0" */
#define _NL_CTYPE_OUTDIGIT1_MB                 _NL_ITEM(__LC_CTYPE, 0x2a) /* "1" */
#define _NL_CTYPE_OUTDIGIT2_MB                 _NL_ITEM(__LC_CTYPE, 0x2b) /* "2" */
#define _NL_CTYPE_OUTDIGIT3_MB                 _NL_ITEM(__LC_CTYPE, 0x2c) /* "3" */
#define _NL_CTYPE_OUTDIGIT4_MB                 _NL_ITEM(__LC_CTYPE, 0x2d) /* "4" */
#define _NL_CTYPE_OUTDIGIT5_MB                 _NL_ITEM(__LC_CTYPE, 0x2e) /* "5" */
#define _NL_CTYPE_OUTDIGIT6_MB                 _NL_ITEM(__LC_CTYPE, 0x2f) /* "6" */
#define _NL_CTYPE_OUTDIGIT7_MB                 _NL_ITEM(__LC_CTYPE, 0x30) /* "7" */
#define _NL_CTYPE_OUTDIGIT8_MB                 _NL_ITEM(__LC_CTYPE, 0x31) /* "8" */
#define _NL_CTYPE_OUTDIGIT9_MB                 _NL_ITEM(__LC_CTYPE, 0x32) /* "9" */
#define _NL_CTYPE_OUTDIGIT0_WC                 _NL_ITEM(__LC_CTYPE, 0x33) /* 48 [uintptr_t] */
#define _NL_CTYPE_OUTDIGIT1_WC                 _NL_ITEM(__LC_CTYPE, 0x34) /* 49 [uintptr_t] */
#define _NL_CTYPE_OUTDIGIT2_WC                 _NL_ITEM(__LC_CTYPE, 0x35) /* 50 [uintptr_t] */
#define _NL_CTYPE_OUTDIGIT3_WC                 _NL_ITEM(__LC_CTYPE, 0x36) /* 51 [uintptr_t] */
#define _NL_CTYPE_OUTDIGIT4_WC                 _NL_ITEM(__LC_CTYPE, 0x37) /* 52 [uintptr_t] */
#define _NL_CTYPE_OUTDIGIT5_WC                 _NL_ITEM(__LC_CTYPE, 0x38) /* 53 [uintptr_t] */
#define _NL_CTYPE_OUTDIGIT6_WC                 _NL_ITEM(__LC_CTYPE, 0x39) /* 54 [uintptr_t] */
#define _NL_CTYPE_OUTDIGIT7_WC                 _NL_ITEM(__LC_CTYPE, 0x3a) /* 55 [uintptr_t] */
#define _NL_CTYPE_OUTDIGIT8_WC                 _NL_ITEM(__LC_CTYPE, 0x3b) /* 56 [uintptr_t] */
#define _NL_CTYPE_OUTDIGIT9_WC                 _NL_ITEM(__LC_CTYPE, 0x3c) /* 57 [uintptr_t] */
#define _NL_CTYPE_TRANSLIT_TAB_SIZE            _NL_ITEM(__LC_CTYPE, 0x3d) /* 0 [uintptr_t] */
#define _NL_CTYPE_TRANSLIT_FROM_IDX            _NL_ITEM(__LC_CTYPE, 0x3e) /* L"" */
#define _NL_CTYPE_TRANSLIT_FROM_TBL            _NL_ITEM(__LC_CTYPE, 0x3f) /* L"" */
#define _NL_CTYPE_TRANSLIT_TO_IDX              _NL_ITEM(__LC_CTYPE, 0x40) /* L"" */
#define _NL_CTYPE_TRANSLIT_TO_TBL              _NL_ITEM(__LC_CTYPE, 0x41) /* L"" */
#define _NL_CTYPE_TRANSLIT_DEFAULT_MISSING_LEN _NL_ITEM(__LC_CTYPE, 0x42) /* 1 [uintptr_t] */
#define _NL_CTYPE_TRANSLIT_DEFAULT_MISSING     _NL_ITEM(__LC_CTYPE, 0x43) /* L"?" */
#define _NL_CTYPE_TRANSLIT_IGNORE_LEN          _NL_ITEM(__LC_CTYPE, 0x44) /* 0 [uintptr_t] */
#define _NL_CTYPE_TRANSLIT_IGNORE              _NL_ITEM(__LC_CTYPE, 0x45) /* "" */
#define _NL_CTYPE_MAP_TO_NONASCII              _NL_ITEM(__LC_CTYPE, 0x46) /* 0 [uintptr_t] */
#define _NL_CTYPE_NONASCII_CASE                _NL_ITEM(__LC_CTYPE, 0x47) /* 0 [uintptr_t] */
#define _NL_CTYPE_EXTRA_MAP_1                  _NL_ITEM(__LC_CTYPE, 0x48) /* L"..." */
#define _NL_CTYPE_EXTRA_MAP_2                  _NL_ITEM(__LC_CTYPE, 0x49) /* L"..." */
#define _NL_CTYPE_EXTRA_MAP_3                  _NL_ITEM(__LC_CTYPE, 0x4a) /* L"..." */
#define _NL_CTYPE_EXTRA_MAP_4                  _NL_ITEM(__LC_CTYPE, 0x4b) /* L"..." */
#define _NL_CTYPE_EXTRA_MAP_5                  _NL_ITEM(__LC_CTYPE, 0x4c) /* L"..." */
#define _NL_CTYPE_EXTRA_MAP_6                  _NL_ITEM(__LC_CTYPE, 0x4d) /* L"..." */
#define _NL_CTYPE_EXTRA_MAP_7                  _NL_ITEM(__LC_CTYPE, 0x4e) /* L"..." */
#define _NL_CTYPE_EXTRA_MAP_8                  _NL_ITEM(__LC_CTYPE, 0x4f) /* L"..." */
#define _NL_CTYPE_EXTRA_MAP_9                  _NL_ITEM(__LC_CTYPE, 0x50) /* L"..." */
#define _NL_CTYPE_EXTRA_MAP_10                 _NL_ITEM(__LC_CTYPE, 0x51) /* L"..." */
#define _NL_CTYPE_EXTRA_MAP_11                 _NL_ITEM(__LC_CTYPE, 0x52) /* L"..." */
#define _NL_CTYPE_EXTRA_MAP_12                 _NL_ITEM(__LC_CTYPE, 0x53) /* L"..." */
#define _NL_CTYPE_EXTRA_MAP_13                 _NL_ITEM(__LC_CTYPE, 0x54) /* L"..." */
#define _NL_CTYPE_EXTRA_MAP_14                 _NL_ITEM(__LC_CTYPE, 0x55) /* L"..." */
#define _NL_NUM_LC_CTYPE                       _NL_ITEM(__LC_CTYPE, 0x56)
#define _NL_MONETARY_INT_CURR_SYMBOL           _NL_ITEM(__LC_MONETARY, 0x00) /* "" */
#define _NL_MONETARY_CURRENCY_SYMBOL           _NL_ITEM(__LC_MONETARY, 0x01) /* "" */
#define _NL_MONETARY_MON_DECIMAL_POINT         _NL_ITEM(__LC_MONETARY, 0x02) /* "" */
#define _NL_MONETARY_MON_THOUSANDS_SEP         _NL_ITEM(__LC_MONETARY, 0x03) /* "" */
#define _NL_MONETARY_MON_GROUPING              _NL_ITEM(__LC_MONETARY, 0x04) /* [0x00] [array-of-uint8_t] */
#define _NL_MONETARY_POSITIVE_SIGN             _NL_ITEM(__LC_MONETARY, 0x05) /* "" */
#define _NL_MONETARY_NEGATIVE_SIGN             _NL_ITEM(__LC_MONETARY, 0x06) /* "" */
#define _NL_MONETARY_INT_FRAC_DIGITS           _NL_ITEM(__LC_MONETARY, 0x07) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_FRAC_DIGITS               _NL_ITEM(__LC_MONETARY, 0x08) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_P_CS_PRECEDES             _NL_ITEM(__LC_MONETARY, 0x09) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_P_SEP_BY_SPACE            _NL_ITEM(__LC_MONETARY, 0x0a) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_N_CS_PRECEDES             _NL_ITEM(__LC_MONETARY, 0x0b) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_N_SEP_BY_SPACE            _NL_ITEM(__LC_MONETARY, 0x0c) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_P_SIGN_POSN               _NL_ITEM(__LC_MONETARY, 0x0d) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_N_SIGN_POSN               _NL_ITEM(__LC_MONETARY, 0x0e) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_CRNCYSTR                  _NL_ITEM(__LC_MONETARY, 0x0f) /* "-" */
#define _NL_MONETARY_INT_P_CS_PRECEDES         _NL_ITEM(__LC_MONETARY, 0x10) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_INT_P_SEP_BY_SPACE        _NL_ITEM(__LC_MONETARY, 0x11) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_INT_N_CS_PRECEDES         _NL_ITEM(__LC_MONETARY, 0x12) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_INT_N_SEP_BY_SPACE        _NL_ITEM(__LC_MONETARY, 0x13) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_INT_P_SIGN_POSN           _NL_ITEM(__LC_MONETARY, 0x14) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_INT_N_SIGN_POSN           _NL_ITEM(__LC_MONETARY, 0x15) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_DUO_INT_CURR_SYMBOL       _NL_ITEM(__LC_MONETARY, 0x16) /* "" */
#define _NL_MONETARY_DUO_CURRENCY_SYMBOL       _NL_ITEM(__LC_MONETARY, 0x17) /* "" */
#define _NL_MONETARY_DUO_INT_FRAC_DIGITS       _NL_ITEM(__LC_MONETARY, 0x18) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_DUO_FRAC_DIGITS           _NL_ITEM(__LC_MONETARY, 0x19) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_DUO_P_CS_PRECEDES         _NL_ITEM(__LC_MONETARY, 0x1a) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_DUO_P_SEP_BY_SPACE        _NL_ITEM(__LC_MONETARY, 0x1b) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_DUO_N_CS_PRECEDES         _NL_ITEM(__LC_MONETARY, 0x1c) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_DUO_N_SEP_BY_SPACE        _NL_ITEM(__LC_MONETARY, 0x1d) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_DUO_INT_P_CS_PRECEDES     _NL_ITEM(__LC_MONETARY, 0x1e) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_DUO_INT_P_SEP_BY_SPACE    _NL_ITEM(__LC_MONETARY, 0x1f) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_DUO_INT_N_CS_PRECEDES     _NL_ITEM(__LC_MONETARY, 0x20) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_DUO_INT_N_SEP_BY_SPACE    _NL_ITEM(__LC_MONETARY, 0x21) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_DUO_P_SIGN_POSN           _NL_ITEM(__LC_MONETARY, 0x22) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_DUO_N_SIGN_POSN           _NL_ITEM(__LC_MONETARY, 0x23) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_DUO_INT_P_SIGN_POSN       _NL_ITEM(__LC_MONETARY, 0x24) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_DUO_INT_N_SIGN_POSN       _NL_ITEM(__LC_MONETARY, 0x25) /* 0xff [pointer-to-uint8_t] */
#define _NL_MONETARY_UNO_VALID_FROM            _NL_ITEM(__LC_MONETARY, 0x26) /* 10101 [uintptr_t] */
#define _NL_MONETARY_UNO_VALID_TO              _NL_ITEM(__LC_MONETARY, 0x27) /* 99991231 [uintptr_t] */
#define _NL_MONETARY_DUO_VALID_FROM            _NL_ITEM(__LC_MONETARY, 0x28) /* 10101 [uintptr_t] */
#define _NL_MONETARY_DUO_VALID_TO              _NL_ITEM(__LC_MONETARY, 0x29) /* 99991231 [uintptr_t] */
#define _NL_MONETARY_CONVERSION_RATE           _NL_ITEM(__LC_MONETARY, 0x2a) /* [...,0x00] [array-of-uint32_t] */
#define _NL_MONETARY_DECIMAL_POINT_WC          _NL_ITEM(__LC_MONETARY, 0x2b) /* 0 [uintptr_t] */
#define _NL_MONETARY_THOUSANDS_SEP_WC          _NL_ITEM(__LC_MONETARY, 0x2c) /* 0 [uintptr_t] */
#define _NL_MONETARY_CODESET                   _NL_ITEM(__LC_MONETARY, 0x2d) /* "utf-8" */
#define _NL_NUM_LC_MONETARY                    _NL_ITEM(__LC_MONETARY, 0x2e)
#define _NL_NUMERIC_DECIMAL_POINT              _NL_ITEM(__LC_NUMERIC, 0) /* "." */
#define _NL_NUMERIC_THOUSANDS_SEP              _NL_ITEM(__LC_NUMERIC, 1) /* "" */
#define _NL_NUMERIC_GROUPING                   _NL_ITEM(__LC_NUMERIC, 2) /* [0x00] [array-of-uint8_t] */
#define _NL_NUMERIC_DECIMAL_POINT_WC           _NL_ITEM(__LC_NUMERIC, 3) /* 46 [uintptr_t] */
#define _NL_NUMERIC_THOUSANDS_SEP_WC           _NL_ITEM(__LC_NUMERIC, 4) /* 0 [uintptr_t] */
#define _NL_NUMERIC_CODESET                    _NL_ITEM(__LC_NUMERIC, 5) /* "utf-8" */
#define _NL_NUM_LC_NUMERIC                     _NL_ITEM(__LC_NUMERIC, 6)
#define _NL_MESSAGES_YESEXPR                   _NL_ITEM(__LC_MESSAGES, 0) /* "^[yY]" */
#define _NL_MESSAGES_NOEXPR                    _NL_ITEM(__LC_MESSAGES, 1) /* "^[nN]" */
#define _NL_MESSAGES_YESSTR                    _NL_ITEM(__LC_MESSAGES, 2) /* "" */
#define _NL_MESSAGES_NOSTR                     _NL_ITEM(__LC_MESSAGES, 3) /* "" */
#define _NL_MESSAGES_CODESET                   _NL_ITEM(__LC_MESSAGES, 4) /* "utf-8" */
#define _NL_NUM_LC_MESSAGES                    _NL_ITEM(__LC_MESSAGES, 5)
#define _NL_PAPER_HEIGHT                       _NL_ITEM(__LC_PAPER, 0) /* 297 [uintptr_t] */
#define _NL_PAPER_WIDTH                        _NL_ITEM(__LC_PAPER, 1) /* 210 [uintptr_t] */
#define _NL_PAPER_CODESET                      _NL_ITEM(__LC_PAPER, 2) /* "utf-8" */
#define _NL_NUM_LC_PAPER                       _NL_ITEM(__LC_PAPER, 3)
#define _NL_NAME_NAME_FMT                      _NL_ITEM(__LC_NAME, 0) /* "%p%t%g%t%m%t%f" */
#define _NL_NAME_NAME_GEN                      _NL_ITEM(__LC_NAME, 1) /* "" */
#define _NL_NAME_NAME_MR                       _NL_ITEM(__LC_NAME, 2) /* "" */
#define _NL_NAME_NAME_MRS                      _NL_ITEM(__LC_NAME, 3) /* "" */
#define _NL_NAME_NAME_MISS                     _NL_ITEM(__LC_NAME, 4) /* "" */
#define _NL_NAME_NAME_MS                       _NL_ITEM(__LC_NAME, 5) /* "" */
#define _NL_NAME_CODESET                       _NL_ITEM(__LC_NAME, 6) /* "utf-8" */
#define _NL_NUM_LC_NAME                        _NL_ITEM(__LC_NAME, 7)
#define _NL_ADDRESS_POSTAL_FMT                 _NL_ITEM(__LC_ADDRESS, 0x00) /* "%a%N%f%N%d%N%b%N%s %h %e %r%N%C-%z %T%N%c%N" */
#define _NL_ADDRESS_COUNTRY_NAME               _NL_ITEM(__LC_ADDRESS, 0x01) /* "" */
#define _NL_ADDRESS_COUNTRY_POST               _NL_ITEM(__LC_ADDRESS, 0x02) /* "" */
#define _NL_ADDRESS_COUNTRY_AB2                _NL_ITEM(__LC_ADDRESS, 0x03) /* "" */
#define _NL_ADDRESS_COUNTRY_AB3                _NL_ITEM(__LC_ADDRESS, 0x04) /* "" */
#define _NL_ADDRESS_COUNTRY_CAR                _NL_ITEM(__LC_ADDRESS, 0x05) /* "" */
#define _NL_ADDRESS_COUNTRY_NUM                _NL_ITEM(__LC_ADDRESS, 0x06) /* 0 [uintptr_t] */
#define _NL_ADDRESS_COUNTRY_ISBN               _NL_ITEM(__LC_ADDRESS, 0x07) /* "" */
#define _NL_ADDRESS_LANG_NAME                  _NL_ITEM(__LC_ADDRESS, 0x08) /* "" */
#define _NL_ADDRESS_LANG_AB                    _NL_ITEM(__LC_ADDRESS, 0x09) /* "" */
#define _NL_ADDRESS_LANG_TERM                  _NL_ITEM(__LC_ADDRESS, 0x0a) /* "" */
#define _NL_ADDRESS_LANG_LIB                   _NL_ITEM(__LC_ADDRESS, 0x0b) /* "" */
#define _NL_ADDRESS_CODESET                    _NL_ITEM(__LC_ADDRESS, 0x0c) /* "utf-8" */
#define _NL_NUM_LC_ADDRESS                     _NL_ITEM(__LC_ADDRESS, 0x0d)
#define _NL_TELEPHONE_TEL_INT_FMT              _NL_ITEM(__LC_TELEPHONE, 0) /* "+%c %a %l" */
#define _NL_TELEPHONE_TEL_DOM_FMT              _NL_ITEM(__LC_TELEPHONE, 1) /* "" */
#define _NL_TELEPHONE_INT_SELECT               _NL_ITEM(__LC_TELEPHONE, 2) /* "" */
#define _NL_TELEPHONE_INT_PREFIX               _NL_ITEM(__LC_TELEPHONE, 3) /* "" */
#define _NL_TELEPHONE_CODESET                  _NL_ITEM(__LC_TELEPHONE, 4) /* "utf-8" */
#define _NL_NUM_LC_TELEPHONE                   _NL_ITEM(__LC_TELEPHONE, 5)
#define _NL_MEASUREMENT_MEASUREMENT            _NL_ITEM(__LC_MEASUREMENT, 0) /* 0x1 [pointer-to-uint8_t] */
#define _NL_MEASUREMENT_CODESET                _NL_ITEM(__LC_MEASUREMENT, 1) /* "utf-8" */
#define _NL_NUM_LC_MEASUREMENT                 _NL_ITEM(__LC_MEASUREMENT, 2)
#define _NL_IDENTIFICATION_TITLE               _NL_ITEM(__LC_IDENTIFICATION, 0x00) /* "" */
#define _NL_IDENTIFICATION_SOURCE              _NL_ITEM(__LC_IDENTIFICATION, 0x01) /* "" */
#define _NL_IDENTIFICATION_ADDRESS             _NL_ITEM(__LC_IDENTIFICATION, 0x02) /* "" */
#define _NL_IDENTIFICATION_CONTACT             _NL_ITEM(__LC_IDENTIFICATION, 0x03) /* "" */
#define _NL_IDENTIFICATION_EMAIL               _NL_ITEM(__LC_IDENTIFICATION, 0x04) /* "" */
#define _NL_IDENTIFICATION_TEL                 _NL_ITEM(__LC_IDENTIFICATION, 0x05) /* "" */
#define _NL_IDENTIFICATION_FAX                 _NL_ITEM(__LC_IDENTIFICATION, 0x06) /* "" */
#define _NL_IDENTIFICATION_LANGUAGE            _NL_ITEM(__LC_IDENTIFICATION, 0x07) /* "" */
#define _NL_IDENTIFICATION_TERRITORY           _NL_ITEM(__LC_IDENTIFICATION, 0x08) /* "" */
#define _NL_IDENTIFICATION_AUDIENCE            _NL_ITEM(__LC_IDENTIFICATION, 0x09) /* "" */
#define _NL_IDENTIFICATION_APPLICATION         _NL_ITEM(__LC_IDENTIFICATION, 0x0a) /* "" */
#define _NL_IDENTIFICATION_ABBREVIATION        _NL_ITEM(__LC_IDENTIFICATION, 0x0b) /* "" */
#define _NL_IDENTIFICATION_REVISION            _NL_ITEM(__LC_IDENTIFICATION, 0x0c) /* "" */
#define _NL_IDENTIFICATION_DATE                _NL_ITEM(__LC_IDENTIFICATION, 0x0d) /* "" */
#define _NL_IDENTIFICATION_CATEGORY            _NL_ITEM(__LC_IDENTIFICATION, 0x0e) /* "" */
#define _NL_IDENTIFICATION_CODESET             _NL_ITEM(__LC_IDENTIFICATION, 0x0f) /* "utf-8" */
#define _NL_NUM_LC_IDENTIFICATION              _NL_ITEM(__LC_IDENTIFICATION, 0x10)
#define _NL_NUM                                _NL_ITEM(__LC_IDENTIFICATION, 0x11)


#endif /* !_ASM_CRT_LANGINFO_H */
