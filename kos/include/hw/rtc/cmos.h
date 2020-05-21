/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _HW_RTC_CMOS_H
#define _HW_RTC_CMOS_H 1

#include <__stdinc.h>

#include <sys/io.h>

/* CMOS ports */
#define CMOS_ADDR __IOPORT(0x70)
#   define CMOS_ADDR_NONMI 0x80 /* Disable non-maskable interrupts. */
#define CMOS_DATA __IOPORT(0x71)

/* CMOS register indices */
#define CMOS_SECOND  0x00
#define CMOS_MINUTE  0x02
#define CMOS_HOUR    0x04
#define CMOS_DAY     0x07
#define CMOS_MONTH   0x08
#define CMOS_YEAR    0x09
#define CMOS_STATE_A 0x0a
#   define CMOS_A_UPDATING 0x80 /* Set while the CMOS chip is updating its time. */
#define CMOS_STATE_B 0x0b
#   define CMOS_B_NOBCD    0x04 /* When set, CMOS time is in decimal format. */
#   define CMOS_B_24H      0x02 /* When set, CMOS hours uses a 24-hour format. */

#define CMOS_BCD_DECODE(x) (((x) & 0xf) + (((x) >> 4) * 10))
#define CMOS_BCD_ENCODE(x) (((x) % 10) | (((x) / 10) << 4))

#endif /* !_HW_RTC_CMOS_H */
