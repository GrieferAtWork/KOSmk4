/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_IOCTL_CLOCK_H
#define _KOS_IOCTL_CLOCK_H 1

/* KOS-specific clock-device system interface. */

#include <__stdinc.h>
#include <asm/ioctl.h>
#include <bits/types.h>

/* Clock device time base constants */
#define CLOCK_DEVICE_TIMEBASE_UTC          0 /* Clock produces real time UTC (01.01.1970) */
#define CLOCK_DEVICE_TIMEBASE_LOCALTIME    1 /* Clock produces local time (01.01.1970) */
#define CLOCK_DEVICE_TIMEBASE_MACH_POWERON 2 /* Clock produces time since machine power-on */
#define CLOCK_DEVICE_TIMEBASE_CPU_POWERON  3 /* Clock produces time since cpu power-on */
#define CLOCK_DEVICE_TIMEBASE_UNSPECIFIED  4 /* Clock produces time passed since some unspecified point in time */

#ifdef __CC__
struct clock_timestamp {
	__uint64_t   ct_seconds;          /* Amount of whole seconds passed */
	__uint64_t   ct_ticks;            /* Number of sub-second ticks passed */
	__uint64_t   ct_ticks_per_second; /* [!0] Number of ticks per second (when 1, the clock
	                                   * doesn't allow provide for sub-second precision)
	                                   * WARNING: This number may change over time! */
};
#endif /* __CC__ */

/* Clock device I/O constants. */
#define CDIO_GETTIME       _IOR('C', 0x00, struct clock_timestamp) /* Get the current time */
#define CDIO_SETTIME       _IOW('C', 0x00, struct clock_timestamp) /* Set the current time */
#define CDIO_GETBASE       _IOR('C', 0x02, __uint32_t)             /* Return the clock timer base value (one of `CLOCK_DEVICE_TIMEBASE_*') */
#define CDIO_SETWALLCLOCK   _IO('C', 0x03)                         /* Set this clock as the default system clock (the one used by `time(2)') */

#endif /* !_KOS_IOCTL_CLOCK_H */
