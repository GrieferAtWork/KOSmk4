/*[[[magic
local deemon = import("deemon");
local macros = options.setdefault("COMPILE.macros", deemon.Dict(()));
macros["__DATE_YEAR__"] = str(import("time").Time.now().year)[#"Years ":];
]]]*/
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_TIME_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_TIME_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <sched/time.h>

#include <hybrid/sync/atomic-rwlock.h>

#include <sys/io.h>
#include <assert.h>

#ifndef __DATE_YEAR__
#ifdef __INTELLISENSE__
#define __DATE_YEAR__ 2020
#else /* __INTELLISENSE__ */
#error "This should have been defined by the [[[magic]]] tag atop of this file!"
#endif /* !__INTELLISENSE__ */
#endif /* !__DATE_YEAR__ */

DECL_BEGIN

PRIVATE NOBLOCK WUNUSED struct timespec
NOTHROW(KCALL cmos_gettime)(struct realtime_clock_struct *__restrict self);

PUBLIC struct realtime_clock_struct x86_cmos_realtime_clock = {
	/* .rc_refcnt    = */ 2, /* x86_cmos_realtime_clock, realtime_clock.m_ptr */
	/* .rc_driver    = */ &kernel_driver,
	/* .rc_precision = */ { 1, 0 }, /* 1 second */
	/* .rc_gettime   = */ &cmos_gettime,
	/* .rc_settime   = */ NULL, /* TODO: cmos_settime() */
	/* .rc_waitfor   = */ NULL, /* TODO: cmos_waitfor() (yes: cmos actually supports this) */
	/* .rc_fini      = */ NULL,
};

#ifndef CONFIG_NO_SMP
PRIVATE struct atomic_rwlock cmos_lock = ATOMIC_RWLOCK_INIT;
#define CMOS_LOCK_ACQUIRE()  sync_write(&cmos_lock)
#define CMOS_LOCK_RELEASE()  sync_endwrite(&cmos_lock)
#else /* !CONFIG_NO_SMP */
#define CMOS_LOCK_ACQUIRE()  (void)0
#define CMOS_LOCK_RELEASE()  (void)0
#endif /* CONFIG_NO_SMP */

#define CMOS_ADDR __IOPORT(0x70)
#   define CMOS_ADDR_NONMI 0x80 /* Disable non-maskable interrupts. */
#define CMOS_DATA __IOPORT(0x71)
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

#define BCD_DECODE(x) (((x) & 0xf) + (((x) >> 4) * 10))
#define BCD_ENCODE(x) (((x) % 10) | (((x) / 10) << 4))

PRIVATE u8 cmos_cent_reg = 0; /* [const] CMOS century register. */
PRIVATE u8 cmos_state_b  = 0; /* [const] Value of 'CMOS_STATE_B' */

FORCELOCAL NOBLOCK u8
NOTHROW(KCALL cmos_rd)(u8 reg) {
	outb(CMOS_ADDR, reg);
	return inb(CMOS_DATA);
}

FORCELOCAL NOBLOCK void
NOTHROW(KCALL cmos_wr)(u8 reg, u8 val) {
	outb(CMOS_ADDR, reg);
	outb(CMOS_DATA, val);
}


#define LINUX_TIME_START_YEAR  1970

#define SECONDS_PER_DAY        86400

#define DAYS2YEARS(n_days)  ((((n_days) + 1) * 400) / 146097)
#define YEARS2DAYS(n_years) ((((n_years) * 146097) / 400) /* - 1*/) /* rounding error? */
#define ISLEAPYEAR(year)    ((year) % 400 == 0 || ((year) % 100 != 0 && (year) % 4 == 0))

PRIVATE time_t const time_monthstart_yday[2][13] = {
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
	{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
};

#define MONTH_STARTING_DAY_OF_YEAR(leap_year, month) \
	time_monthstart_yday[!!(leap_year)][month]


LOCAL NOBLOCK WUNUSED time_t
NOTHROW(KCALL cmos_unix_time)(void) {
	u8 cmos_second, cmos_minute, cmos_hour, temp;
	u8 cmos_day, cmos_month, cmos_year, cmos_cent;
	unsigned int timeout;
	u16 year;
	time_t result;
	assert(!PREEMPTION_ENABLED());
	CMOS_LOCK_ACQUIRE();
	timeout = 1000000;
	while (cmos_rd(CMOS_STATE_A) & CMOS_A_UPDATING) {
		if unlikely(!timeout)
			break; /* You wan'na be that way? fine! */
		--timeout;
		task_pause();
	}
	cmos_second = cmos_rd(CMOS_SECOND);
	cmos_minute = cmos_rd(CMOS_MINUTE);
	cmos_hour   = cmos_rd(CMOS_HOUR);
	cmos_day    = cmos_rd(CMOS_DAY);
	cmos_month  = cmos_rd(CMOS_MONTH);
	cmos_year   = cmos_rd(CMOS_YEAR);
	cmos_cent   = 0;
	if (cmos_cent_reg)
		cmos_cent = cmos_rd(cmos_cent_reg);
	/* re-read the second register to ensure that it didn't change in the mean time. */
	temp = cmos_rd(CMOS_SECOND);
	if likely(temp == cmos_second)
		goto got_time;
	cmos_second = temp;
	/* Same for minute */
	temp = cmos_rd(CMOS_MINUTE);
	if likely(cmos_minute == temp)
		goto got_time;
	cmos_minute = temp;
	/* Same for hour */
	temp = cmos_rd(CMOS_HOUR);
	if likely(cmos_hour == temp)
		goto got_time;
	cmos_hour = temp;
	/* Same for day */
	temp = cmos_rd(CMOS_DAY);
	if likely(cmos_day == temp)
		goto got_time;
	cmos_day = temp;
	/* Same for month */
	temp = cmos_rd(CMOS_MONTH);
	if likely(cmos_month == temp)
		goto got_time;
	cmos_month = temp;
	/* Same for year */
	temp = cmos_rd(CMOS_YEAR);
	if likely(cmos_year == temp)
		goto got_time;
	cmos_year = temp;
	if (cmos_cent_reg)
		cmos_cent = cmos_rd(cmos_cent_reg);
got_time:
	CMOS_LOCK_RELEASE();
	/* Fix BCD time information. */
	if (!(cmos_state_b & CMOS_B_NOBCD)) {
		cmos_second = BCD_DECODE(cmos_second);
		cmos_minute = BCD_DECODE(cmos_minute);
		cmos_hour   = BCD_DECODE(cmos_hour & 0x7f) | (cmos_hour & 0x80);
		cmos_day    = BCD_DECODE(cmos_day);
		cmos_month  = BCD_DECODE(cmos_month);
		cmos_year   = BCD_DECODE(cmos_year);
		cmos_cent   = BCD_DECODE(cmos_cent);
	}
	/* Fix 12-hour time information. */
	if (!(cmos_state_b & CMOS_B_24H) && (cmos_hour & 0x80) != 0)
		cmos_hour = ((cmos_hour & 0x7f) + 12) % 24; 
	/* Figure out the proper year. */
	year = cmos_year;
	if (cmos_cent_reg)
		year += (u16)cmos_cent * 100;
	else {
		if (year < (__DATE_YEAR__ % 100))
			year += 100; /* 100 years into the future. */
		year += (__DATE_YEAR__ / 100) * 100;
		year = __DATE_YEAR__;
	}
	result = YEARS2DAYS((time_t)((s32)year - 1970));
	result += MONTH_STARTING_DAY_OF_YEAR(ISLEAPYEAR(year), (u8)(cmos_month - 1) % 12);
	result += cmos_day - 1;
	result *= SECONDS_PER_DAY;
	result += cmos_hour * 60 * 60;
	result += cmos_minute * 60;
	result += cmos_second;
	return result;
}



PRIVATE NOBLOCK WUNUSED struct timespec
NOTHROW(KCALL cmos_gettime)(struct realtime_clock_struct *__restrict UNUSED(self)) {
	struct timespec result;
	result.tv_sec  = cmos_unix_time();
	result.tv_nsec = 0;
	return result;
}

INTERN ATTR_FREETEXT void NOTHROW(KCALL x86_initialize_cmos)(void) {
	cmos_state_b = cmos_rd(CMOS_STATE_B);
	//cmos_cent_reg = ...; /* TODO: This can be read from the ACPI descriptor table. */
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_TIME_C */
