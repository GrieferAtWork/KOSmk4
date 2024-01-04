/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_OS_KOS_TIMEX_H
#define _ASM_OS_KOS_TIMEX_H 1

#include <__stdinc.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

/* Mode code flags (for `struct timex::mode') */
#define __ADJ_OFFSET            0x0001 /* ??? */
#define __ADJ_FREQUENCY         0x0002 /* ??? */
#define __ADJ_MAXERROR          0x0004 /* ??? */
#define __ADJ_ESTERROR          0x0008 /* ??? */
#define __ADJ_STATUS            0x0010 /* ??? */
#define __ADJ_TIMECONST         0x0020 /* ??? */
#define __ADJ_TAI               0x0080 /* ??? */
#define __ADJ_SETOFFSET         0x0100 /* ??? */
#define __ADJ_MICRO             0x1000 /* ??? */
#define __ADJ_NANO              0x2000 /* ??? */
#define __ADJ_TICK              0x4000 /* ??? */
#define __ADJ_OFFSET_SINGLESHOT 0x8001 /* ??? */
#define __ADJ_OFFSET_SS_READ    0xa001 /* ??? */

/* Status code flags (for `struct timex::status') */
#define __STA_PLL       0x0001 /* ??? */
#define __STA_PPSFREQ   0x0002 /* ??? */
#define __STA_PPSTIME   0x0004 /* ??? */
#define __STA_FLL       0x0008 /* ??? */
#define __STA_INS       0x0010 /* ??? */
#define __STA_DEL       0x0020 /* ??? */
#define __STA_UNSYNC    0x0040 /* ??? */
#define __STA_FREQHOLD  0x0080 /* ??? */
#define __STA_PPSSIGNAL 0x0100 /* ??? */
#define __STA_PPSJITTER 0x0200 /* ??? */
#define __STA_PPSWANDER 0x0400 /* ??? */
#define __STA_PPSERROR  0x0800 /* ??? */
#define __STA_CLOCKERR  0x1000 /* ??? */
#define __STA_NANO      0x2000 /* ??? */
#define __STA_MODE      0x4000 /* ??? */
#define __STA_CLK       0x8000 /* ??? */

/* Read-only bits */
#define __STA_RONLY                                                         \
	(__STA_PPSSIGNAL | __STA_PPSJITTER | __STA_PPSWANDER | __STA_PPSERROR | \
	 __STA_CLOCKERR | __STA_NANO | __STA_MODE | __STA_CLK)



#endif /* !_ASM_OS_KOS_TIMEX_H */
