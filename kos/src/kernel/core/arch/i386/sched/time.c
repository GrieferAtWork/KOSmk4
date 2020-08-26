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
#define CONFIG_WANT_CMOS_REALTIME_CLOCK_AS_STRUCT 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/x86/nmi.h>
#include <sched/signal.h>
#include <sched/time.h>
#include <sched/x86/cmos.h>

#include <hybrid/atomic.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <hw/rtc/cmos.h>
#include <sys/io.h>

#include <stdint.h>
#include <assert.h>

#ifndef __DATE_YEAR__
#ifdef __INTELLISENSE__
#define __DATE_YEAR__ 2020
#else /* __INTELLISENSE__ */
#error "This should have been defined by the [[[magic]]] tag atop of this file!"
#endif /* !__INTELLISENSE__ */
#endif /* !__DATE_YEAR__ */

DECL_BEGIN

/* Get/Set NMI (non-maskable interrupt) being enabled
 * These interrupts should normally be enabled in all situations,
 * and should only be disabled momentarily, and when absolutely
 * necessary.
 * Also note that NMI enable/disable is controlled globally, and
 * not, say, per-CPU!
 * @param: enabled: The new nmi-enabled state (if different from `return',
 *                  the state was changed)
 * @return: * :     The NMI-enabled state prior to the call being made. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(KCALL x86_get_nmi_enabled)(void) {
	u8 nmi;
	nmi = ATOMIC_READ(cmos_realtime_clock.cr_nmi);
	return nmi & CMOS_ADDR_NONMI ? false : true;
}

FUNDEF NOPREEMPT NOBLOCK bool
NOTHROW(KCALL x86_set_nmi_enabled_nopr)(bool enabled) {
	u8 old_nmi, new_nmi;
	new_nmi = enabled ? 0 : CMOS_ADDR_NONMI;
	assert(!PREEMPTION_ENABLED());
#ifndef CONFIG_NO_SMP
	while (!sync_trywrite(&cmos_realtime_clock.cr_lock)) {
		u8 nmi = ATOMIC_READ(cmos_realtime_clock.cr_nmi);
		if (nmi == new_nmi)
			return enabled; /* Unchanged */
		task_pause();
	}
#endif /* !CONFIG_NO_SMP */
	old_nmi = ATOMIC_XCH(cmos_realtime_clock.cr_nmi, new_nmi);
	if (old_nmi != new_nmi)
		outb(CMOS_ADDR, new_nmi); /* Update hardware */
#ifndef CONFIG_NO_SMP
	sync_endwrite(&cmos_realtime_clock.cr_lock);
#endif /* !CONFIG_NO_SMP */
	return old_nmi & CMOS_ADDR_NONMI ? false : true;
}




PRIVATE NOBLOCK WUNUSED struct timespec
NOTHROW(KCALL cmos_gettime)(struct realtime_clock_struct *__restrict self);
/*
PRIVATE bool
NOTHROW(KCALL cmos_waitfor)(struct realtime_clock_struct *__restrict self,
                            struct timespec const *__restrict abs_time);*/


/* The CMOS realtime clock driver descriptor structure */
PUBLIC struct cmos_realtime_clock_struct cmos_realtime_clock = {
	/* .cr_clock = */ {
		/* .rc_refcnt    = */ 2, /* cmos_realtime_clock, realtime_clock.m_ptr */
		/* .rc_driver    = */ &kernel_driver,
		/* .rc_precision = */ { 1, 0 }, /* 1 second */
		/* .rc_gettime   = */ &cmos_gettime,
		/* .rc_settime   = */ NULL, /* TODO: &cmos_settime */
		/* .rc_waitfor   = */ NULL, /* TODO: &cmos_waitfor */
		/* .rc_fini      = */ NULL
	},
#ifndef CONFIG_NO_SMP
	/* .cr_lock         = */ ATOMIC_RWLOCK_INIT,
#endif /* !CONFIG_NO_SMP */
	/* .cr_century      = */ 0,
	/* .cr_stb          = */ 0,
	/* .cr_nmi          = */ 0,
	/* ._cr_pad         = */ 0,
	/* .cr_alarm_second = */ 0xff,
	/* .cr_alarm_minute = */ 0xff,
	/* .cr_alarm_hour   = */ 0xff,
	/* .cr_stc          = */ 0,
	/* .cr_irq          = */ SIG_INIT,
	/* .cr_alarm        = */ INT64_MAX
};




#define LINUX_TIME_START_YEAR 1970
#define SECONDS_PER_DAY       86400

#define DAYS2YEARS(n_days)  ((((n_days) + 1) * 400) / 146097)
#define YEARS2DAYS(n_years) ((((n_years) * 146097) / 400) /* - 1*/) /* rounding error? */
#define ISLEAPYEAR(year)    ((year) % 400 == 0 || ((year) % 100 != 0 && (year) % 4 == 0))

/* Zero-based day-of-year values for the first of any given month. */
PRIVATE time_t const time_monthstart_yday[2][13] = {
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
	{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
};

#define MONTH_STARTING_DAY_OF_YEAR(leap_year, month) \
	time_monthstart_yday[!!(leap_year)][month]

LOCAL NOBLOCK NOPREEMPT WUNUSED time_t
NOTHROW(KCALL cmos_unix_time)(bool lock) {
	u8 cmos_second, cmos_minute, cmos_hour, temp;
	u8 cmos_day, cmos_month, cmos_year, cmos_cent;
	unsigned int timeout;
	u16 year;
	time_t result;
	assert(!PREEMPTION_ENABLED());
	(void)lock;
#ifndef CONFIG_NO_SMP
	if (lock) {
		while (!sync_trywrite(&cmos_realtime_clock.cr_lock))
			task_pause();
	}
#endif /* !CONFIG_NO_SMP */
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
	if (cmos_realtime_clock.cr_century)
		cmos_cent = cmos_rd(cmos_realtime_clock.cr_century);
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
	if (cmos_realtime_clock.cr_century)
		cmos_cent = cmos_rd(cmos_realtime_clock.cr_century);
got_time:
#ifndef CONFIG_NO_SMP
	if (lock)
		sync_endwrite(&cmos_realtime_clock.cr_lock);
#endif /* !CONFIG_NO_SMP */
	/* Fix BCD time information. */
	if ((cmos_realtime_clock.cr_stb & CMOS_B_DM) == CMOS_B_DM_BCD) {
		cmos_second = CMOS_BCD_DECODE(cmos_second);
		cmos_minute = CMOS_BCD_DECODE(cmos_minute);
		cmos_hour   = CMOS_BCD_DECODE(cmos_hour & 0x7f) | (cmos_hour & 0x80);
		cmos_day    = CMOS_BCD_DECODE(cmos_day);
		cmos_month  = CMOS_BCD_DECODE(cmos_month);
		cmos_year   = CMOS_BCD_DECODE(cmos_year);
		cmos_cent   = CMOS_BCD_DECODE(cmos_cent);
	}
	/* Fix 12-hour time information. */
	if ((cmos_realtime_clock.cr_stb & CMOS_B_2412) == CMOS_B_2412_12H && (cmos_hour & 0x80) != 0)
		cmos_hour = ((cmos_hour & 0x7f) + 12) % 24; 
	/* Figure out the proper year. */
	year = cmos_year;
	if (cmos_realtime_clock.cr_century)
		year += (u16)cmos_cent * 100;
	else {
		if (year < (__DATE_YEAR__ % 100))
			year += 100; /* 100 years into the future. */
		year += (__DATE_YEAR__ - (__DATE_YEAR__ % 100));
	}
	result = YEARS2DAYS((time_t)((s32)year - 1970));
	result += MONTH_STARTING_DAY_OF_YEAR(ISLEAPYEAR(year), (u8)(cmos_month - 1) % 12);
	result += cmos_day - 1;
	result *= SECONDS_PER_DAY;
	result += cmos_hour * 60 * 60;
	result += cmos_minute * 60;
	result += cmos_second;
	if unlikely(cmos_realtime_clock.cr_stb & CMOS_B_DSE) {
		/* TODO:
		 *   - If current time is not
		 *     (now >= 03:00:00 on the last Sunday of April) &&
		 *     (now <  02:00:00 on the last Sunday in October),
		 *     add 1 hour to the result
		 *   - This only leaves the undefined case for the single
		 *     hour in October that is run twice:
		 *                     RTC         OUT          CORRECT(nodst)
		 *       Sun, October: 01:00:00    01:00:00     01:00:00   -- OK
		 *       Sun, October: 01:30:00    01:30:00     01:30:00   -- OK
		 *       Sun, October: 01:59:99    01:59:59     01:59:59   -- OK
		 *       Sun, October: 01:00:00    01:00:00     02:00:00   -- Wrong
		 *       Sun, October: 01:30:00    01:30:00     02:30:00   -- Wrong
		 *       Sun, October: 01:59:99    01:59:59     02:59:59   -- Wrong
		 *       Sun, October: 02:00:00    03:00:00     03:00:00   -- OK
		 *
		 * The CMOS chip would probably run into the same issue, and somehow
		 * needs to remember not to turn back the clock again when it reaches
		 * 01:59:59 a second time. I don't know if that bit is standardized
		 * anywhere (or can be read at all...), but we could keep track of
		 * this ourselves, and turn the clock forward if KOS was already
		 * running before the RTC got turned back.
		 */
	}
	return result;
}




PRIVATE NOBLOCK NOPREEMPT WUNUSED struct timespec
NOTHROW(KCALL cmos_gettime)(struct realtime_clock_struct *__restrict UNUSED(self)) {
	struct timespec result;
	result.tv_sec  = cmos_unix_time(true);
	result.tv_nsec = 0;
	return result;
}


/* Set CMOS registers:
 *   - CMOS_ALARM_SECOND
 *   - CMOS_ALARM_MINUTE
 *   - CMOS_ALARM_HOUR
 * to point to the given `time'
 * The caller is responsible to ensure that the
 * CMOS is ready to accept a new alarm timeout. */
LOCAL NOBLOCK NOPREEMPT void
NOTHROW(KCALL cmos_setalarm)(time_t time) {
	u8 cmos_second, cmos_minute, cmos_hour;
	cmos_second = time % 60;
	time /= 60;
	cmos_minute = time % 60;
	time /= 60;
	cmos_hour = time % 24;
	if ((cmos_realtime_clock.cr_stb & CMOS_B_2412) == CMOS_B_2412_12H && cmos_hour >= 12)
		cmos_hour = (cmos_hour - 12) | 0x80; 
	if ((cmos_realtime_clock.cr_stb & CMOS_B_DM) == CMOS_B_DM_BCD) {
		cmos_second = CMOS_BCD_ENCODE(cmos_second);
		cmos_minute = CMOS_BCD_ENCODE(cmos_minute);
		cmos_hour   = CMOS_BCD_ENCODE(cmos_hour & 0x7f) | (cmos_hour & 0x80);
	}
	/* Store new alarm values, but only do so if they've changed.
	 * This is done since the hour-value isn't that likely to change
	 * all too often, so we can gain a bit of performance by only
	 * changing it when we have to.
	 * The same goes for the other registers, too. (though admittedly,
	 * the second register will probably change every time...) */
	if (cmos_realtime_clock.cr_alarm_hour != cmos_hour) {
		cmos_wr(CMOS_ALARM_HOUR, cmos_hour);
		cmos_realtime_clock.cr_alarm_hour = cmos_hour;
	}
	if (cmos_realtime_clock.cr_alarm_minute != cmos_minute) {
		cmos_wr(CMOS_ALARM_MINUTE, cmos_minute);
		cmos_realtime_clock.cr_alarm_minute = cmos_minute;
	}
	if (cmos_realtime_clock.cr_alarm_second != cmos_second) {
		cmos_wr(CMOS_ALARM_SECOND, cmos_second);
		cmos_realtime_clock.cr_alarm_second = cmos_second;
	}
}



#if 0 /* TODO */
PRIVATE bool
NOTHROW(KCALL cmos_waitfor)(struct realtime_clock_struct *__restrict UNUSED(self),
                            struct timespec const *__restrict abs_time) {
	time_t alarm;
	time_t cmos_now;
	assert(PREEMPTION_ENABLED());
	assert(!task_isconnected());
	alarm = abs_time->tv_sec;

	/* Connect to the interrupt pin of the RTC. */
	task_connect(&cmos_realtime_clock.cr_irq);
	/* Configure the chip for the given timeout. */
	PREEMPTION_DISABLE();
#ifndef CONFIG_NO_SMP
	while (!sync_trywrite(&cmos_realtime_clock.cr_lock))
		task_pause();
#endif /* !CONFIG_NO_SMP */
	/* Check: Does the currently set alarm expire before the new one? */
	if (alarm >= cmos_realtime_clock.cr_alarm &&
	    cmos_realtime_clock.cr_alarm != INT64_MAX)
		goto wait_for_interrupt;
	/* Figure out how much time must still pass
	 * before `abs_time' has been reached. */
	cmos_now = cmos_unix_time(false);
	if (alarm <= cmos_now) {
		/* Timeout has already expired! */
#ifndef CONFIG_NO_SMP
		sync_endwrite(&cmos_realtime_clock.cr_lock);
#endif /* !CONFIG_NO_SMP */
		return true;
	}


#ifndef CONFIG_NO_SMP
	sync_endwrite(&cmos_realtime_clock.cr_lock);
#endif /* !CONFIG_NO_SMP */
wait_for_interrupt:

	return true;
}
#endif

INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_cmos)(void) {
	cmos_realtime_clock.cr_stb = cmos_rd(CMOS_STATE_B);
	//cmos_cent_reg = ...; /* TODO: This can be read from the ACPI descriptor table. */
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_TIME_C */
