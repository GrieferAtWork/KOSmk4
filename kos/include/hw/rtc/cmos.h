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
#ifndef _HW_RTC_CMOS_H
#define _HW_RTC_CMOS_H 1

#include <__stdinc.h>

#include <sys/io.h>

/* CMOS ports */
#define CMOS_ADDR __IOPORT(0x70)
#   define CMOS_ADDR_NONMI 0x80 /* Disable non-maskable interrupts. */
#define CMOS_DATA __IOPORT(0x71)

/* CMOS register indices
 *  - https://web.archive.org/web/20150514082645/http://www.nondot.org/sabre/os/files/MiscHW/RealtimeClockFAQ.txt
 */
#define CMOS_SECOND        0x00 /* [r/w] Current second (0-59; binary/bcd based on `CMOS_B_DM') */
#define CMOS_ALARM_SECOND  0x01 /* [r/w] Alarm second (0-59; binary/bcd based on `CMOS_B_DM') */
#define CMOS_MINUTE        0x02 /* [r/w] Current minute (0-59; binary/bcd based on `CMOS_B_DM') */
#define CMOS_ALARM_MINUTE  0x03 /* [r/w] Alarm minute (0-59; binary/bcd based on `CMOS_B_DM') */
#define CMOS_HOUR          0x04 /* [r/w] Current hour (0-23; binary/bcd based on `CMOS_B_DM')
                                 *       When `CMOS_B_2412_12H' isn't set, 0-11, with 0x80 masked if PM */
#define CMOS_ALARM_HOUR    0x05 /* [r/w] Alarm hour (0-23; binary/bcd based on `CMOS_B_DM')
                                 *       When `CMOS_B_2412_12H' isn't set, 0-11, with 0x80 masked if PM */
#define CMOS_DOW           0x06 /* [r/w] Current day of week (1-7; 1=Sunday) */
#define CMOS_DAY           0x07 /* [r/w] Current day of month (1-31; binary/bcd based on `CMOS_B_DM') */
#define CMOS_MONTH         0x08 /* [r/w] Current month (1-12; binary/bcd based on `CMOS_B_DM') */
#define CMOS_YEAR          0x09 /* [r/w] Current year of century (0-99; binary/bcd based on `CMOS_B_DM') */
#define CMOS_STATE_A       0x0a /* CMOS status register A */
#   define CMOS_A_UPDATING 0x80 /* [r] Set while the CMOS chip is updating its time. */
#   define CMOS_A_RESERVED 0x70 /* [r] Reserved bits (must not be altered during writes! On some machines,
                                 *     these bits control how fast the wall clock will be running!). */
#   define CMOS_A_PINTRATE 0x0f /* [r/w] Periodic interrupt rate. (when `CMOS_B_PIE' is enabled) */
#      define CMOS_A_PINTRATE_NONE    0x00 /* none */
/*            CMOS_A_PINTRATE_HZ_256  0x01  * 3.90625 ms */
/*            CMOS_A_PINTRATE_HZ_128  0x02  * 7.8125 ms */
#      define CMOS_A_PINTRATE_HZ_8192 0x03 /* 122.070 Micros */
#      define CMOS_A_PINTRATE_HZ_4096 0x04 /* 244.141 Micros */
#      define CMOS_A_PINTRATE_HZ_2048 0x05 /* 488.281 Micros */
#      define CMOS_A_PINTRATE_HZ_1024 0x06 /* 976.562 Micros (usually the default set by the BIOS) */
#      define CMOS_A_PINTRATE_HZ_512  0x07 /* 1.93125 ms */
#      define CMOS_A_PINTRATE_HZ_256  0x08 /* 3.90625 ms */
#      define CMOS_A_PINTRATE_HZ_128  0x09 /* 7.8125 ms */
#      define CMOS_A_PINTRATE_HZ_64   0x0a /* 15.625 ms */
#      define CMOS_A_PINTRATE_HZ_32   0x0b /* 31.25 ms */
#      define CMOS_A_PINTRATE_HZ_16   0x0c /* 62.50 ms */
#      define CMOS_A_PINTRATE_HZ_8    0x0d /* 125.0 ms */
#      define CMOS_A_PINTRATE_HZ_4    0x0e /* 250.0 ms */
#      define CMOS_A_PINTRATE_HZ_2    0x0f /* 500.0 ms */
#define CMOS_STATE_B       0x0b /* CMOS status register B */
#   define CMOS_B_DSE      0x01 /* [r] Daylight Savings Enable (When enabled, the RTC will automatically
                                 *     turn the clock back/forward at appropriate times through the year)
                                 *     (might  be  writable?   Don't  risk   changing  this,   though...) */
#   define CMOS_B_2412     0x02 /* [r] 24/12-hour mode. (might be writable? Don't risk changing this, though...) */
#      define CMOS_B_2412_12H         0x00 /* 12-hour format (PM-bit is masked by 0x80) */
#      define CMOS_B_2412_24H         0x02 /* 24-hour format (BIOS default) */
#   define CMOS_B_DM       0x04 /* [r] Data mode. (might be writable? Don't risk changing this, though...) */
#      define CMOS_B_DM_BCD           0x00 /* Operate in BCD mode (BIOS default) */
#      define CMOS_B_DM_BIN           0x04 /* Operate in binary mode */
#   define CMOS_B_NOBCD    0x04 /* When set, CMOS time is in decimal format. */
#   define CMOS_B_UIE      0x10 /* [r/w] Update-ended Interrupt Enable (triggers when `CMOS_A_UPDATING' is cleared) */
#   define CMOS_B_AIE      0x20 /* [r/w] Alarm Interrupt Enable (s.a. `CMOS_ALARM_*') */
#   define CMOS_B_PIE      0x40 /* [r/w] Periodic Interrupt Enable (s.a. `CMOS_A_PINTRATE') */
#   define CMOS_B_SET      0x80 /* [r/w] When set, abort in-progress update, and prevent further updates.
                                 *       I believe this must be set before attempting to write to any
                                 *       of  the  Current/Alarm   registers,  and  cleared   after...
                                 *       Also: Setting this bit clears `CMOS_B_UIE' */
#define CMOS_STATE_C       0x0c /* CMOS status register C */
#   define CMOS_C_UF       0x10 /* [r/c] Update-ended interrupt occurred (cleared on read) */
#   define CMOS_C_AF       0x20 /* [r/c] Alarm interrupt occurred (cleared on read) */
#   define CMOS_C_PF       0x40 /* [r/c] Periodic interrupt occurred (cleared on read) */
#   define CMOS_C_IRQF     0x80 /* [r/c] Interrupt request flag (set if RTC caused an interrupt) (cleared on read) */


/* Encode/Decode BCD values. */
#define CMOS_BCD_DECODE(x) (((x) & 0xf) + (((x) >> 4) * 10))
#define CMOS_BCD_ENCODE(x) (((x) % 10) | (((x) / 10) << 4))

#endif /* !_HW_RTC_CMOS_H */
