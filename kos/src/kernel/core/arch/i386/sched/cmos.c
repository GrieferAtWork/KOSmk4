/*[[[magic
local deemon = import("deemon");
local macros = options.setdefault("COMPILE.macros", deemon.Dict(()));
macros["__DATE_YEAR__"] = str(import("time").Time.now().year)[#"Years ":];
]]]*/
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_CMOS_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_CMOS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/x86/pit.h> /* X86_PIT_EARLY_HZ */
#include <sched/cpu.h>
#include <sched/sig.h>
#include <sched/tsc.h>
#include <sched/x86/cmos.h>

#include <hybrid/atomic.h>
#include <hybrid/sched/atomic-rwlock.h>

#include <hw/rtc/cmos.h>
#include <sys/io.h>

#include <assert.h>
#include <stdint.h>
#include <time.h>

#ifndef __DATE_YEAR__
#ifdef __INTELLISENSE__
#define __DATE_YEAR__ 2020
#else /* __INTELLISENSE__ */
#error "This should have been defined by the [[[magic]]] tag atop of this file!"
#endif /* !__INTELLISENSE__ */
#endif /* !__DATE_YEAR__ */

DECL_BEGIN

/* The CMOS realtime clock driver descriptor structure */
PUBLIC struct x86_cmos_struct x86_cmos = {
#ifndef CONFIG_NO_SMP
	.cr_lock = ATOMIC_LOCK_INIT,
#endif /* !CONFIG_NO_SMP */
	.cr_century      = 0,
	.cr_stb          = 0,
	.cr_nmi          = 0,
	.cr_alarm_second = 0xff,
	.cr_alarm_minute = 0xff,
	.cr_alarm_hour   = 0xff,
};



#define UNIX_TIME_START_YEAR 1970
#define SECONDS_PER_DAY      86400
#define DAYS2YEARS(n_days)   __daystoyears(n_days)
#define YEARS2DAYS(n_years)  __yearstodays(n_years)
#define ISLEAPYEAR(year)     __isleap(year)


/* Zero-based day-of-year values for the first of any given month. */
PRIVATE time_t const time_monthstart_yday[2][13] = {
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
	{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
};

#define MONTH_STARTING_DAY_OF_YEAR(leap_year, month) \
	time_monthstart_yday[!!(leap_year)][month]

LOCAL NOBLOCK NOPREEMPT WUNUSED time_t
NOTHROW(KCALL cmos_gettime)(bool lock) {
	u8 cmos_second, cmos_minute, cmos_hour, temp;
	u8 cmos_day, cmos_month, cmos_year, cmos_cent;
	unsigned int timeout;
	u16 year;
	time_t result;
	assert(!PREEMPTION_ENABLED());
	if (lock)
		x86_cmos_lock_acquire_nopr();
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
	if (x86_cmos.cr_century)
		cmos_cent = cmos_rd(x86_cmos.cr_century);

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
	if (x86_cmos.cr_century)
		cmos_cent = cmos_rd(x86_cmos.cr_century);
got_time:
	if (lock)
		x86_cmos_lock_release_nopr();

	/* Fix BCD time information. */
	if ((x86_cmos.cr_stb & CMOS_B_DM) == CMOS_B_DM_BCD) {
		cmos_second = CMOS_BCD_DECODE(cmos_second);
		cmos_minute = CMOS_BCD_DECODE(cmos_minute);
		cmos_hour   = CMOS_BCD_DECODE(cmos_hour & 0x7f) | (cmos_hour & 0x80);
		cmos_day    = CMOS_BCD_DECODE(cmos_day);
		cmos_month  = CMOS_BCD_DECODE(cmos_month);
		cmos_year   = CMOS_BCD_DECODE(cmos_year);
		cmos_cent   = CMOS_BCD_DECODE(cmos_cent);
	}

	/* Fix 12-hour time information. */
	if ((x86_cmos.cr_stb & CMOS_B_2412) == CMOS_B_2412_12H && (cmos_hour & 0x80) != 0)
		cmos_hour = ((cmos_hour & 0x7f) + 12) % 24;

	/* Figure out the proper year. */
	year = cmos_year;
	if (x86_cmos.cr_century) {
		year += (u16)cmos_cent * 100;
	} else {
		if (year < (__DATE_YEAR__ % 100))
			year += 100; /* 100 years into the future. */
		year += (__DATE_YEAR__ - (__DATE_YEAR__ % 100));
	}
	result = YEARS2DAYS((time_t)((s32)year)) -
	         YEARS2DAYS(UNIX_TIME_START_YEAR);
	result += MONTH_STARTING_DAY_OF_YEAR(ISLEAPYEAR(year), (u8)(cmos_month - 1) % 12);
	result += cmos_day - 1;
	result *= SECONDS_PER_DAY;
	result += cmos_hour * 60 * 60;
	result += cmos_minute * 60;
	result += cmos_second;
	if unlikely(x86_cmos.cr_stb & CMOS_B_DSE) {
		/* TODO:
		 *   - If current time is not
		 *     (now >= 03:00:00 on the last Sunday of April) &&
		 *     (now < 02:00:00 on the last Sunday in  October),
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
		 * The CMOS chip would probably run into the same issue, and  somehow
		 * needs to remember not to turn back the clock again when it reaches
		 * 01:59:59 a second time. I don't know if that bit is standardized
		 * anywhere (or can be read at all...), but we could keep track  of
		 * this  ourselves, and turn  the clock forward  if KOS was already
		 * running before the RTC got turned back.
		 */
	}
	return result;
}


/* The max error by which `tsc_resync_realtime()' may be off. */
PUBLIC_CONST ktime_t const tsc_realtime_err = NSEC_PER_SEC; /* 1 second */

/* Retrieve the current realtime, as read from an external clock source.
 * This function's implementation is  arch-specific, and should only  be
 * called from within `tsc_resync_interrupt()' in order to determine the
 * actual current realtime timestamp. */
PUBLIC NOBLOCK NOPREEMPT ktime_t NOTHROW(FCALL tsc_resync_realtime)(void) {
	return (ktime_t)(cmos_gettime(true) - boottime.tv_sec) * NSEC_PER_SEC;
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
	if ((x86_cmos.cr_stb & CMOS_B_2412) == CMOS_B_2412_12H && cmos_hour >= 12)
		cmos_hour = (cmos_hour - 12) | 0x80;
	if ((x86_cmos.cr_stb & CMOS_B_DM) == CMOS_B_DM_BCD) {
		cmos_second = CMOS_BCD_ENCODE(cmos_second);
		cmos_minute = CMOS_BCD_ENCODE(cmos_minute);
		cmos_hour   = CMOS_BCD_ENCODE(cmos_hour & 0x7f) | (cmos_hour & 0x80);
	}

	/* Store  new alarm values,  but only do  so if they've changed.
	 * This is done since the hour-value isn't that likely to change
	 * all too often, so  we can gain a  bit of performance by  only
	 * changing it when we have to.
	 * The same goes for the other registers, too. (though admittedly,
	 * the   second  register  will  probably  change  every  time...) */
	if (x86_cmos.cr_alarm_hour != cmos_hour) {
		cmos_wr(CMOS_ALARM_HOUR, cmos_hour);
		x86_cmos.cr_alarm_hour = cmos_hour;
	}
	if (x86_cmos.cr_alarm_minute != cmos_minute) {
		cmos_wr(CMOS_ALARM_MINUTE, cmos_minute);
		x86_cmos.cr_alarm_minute = cmos_minute;
	}
	if (x86_cmos.cr_alarm_second != cmos_second) {
		cmos_wr(CMOS_ALARM_SECOND, cmos_second);
		x86_cmos.cr_alarm_second = cmos_second;
	}
}


#ifndef CONFIG_NO_SMP
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL cmos_resync_ipi)(struct icpustate *__restrict state,
                               void *args[CPU_IPI_ARGCOUNT]) {
	ktime_t now;
#if __SIZEOF_POINTER__ >= 8
	now = (ktime_t)(uintptr_t)args[0];
#else /* __SIZEOF_POINTER__ >= 8 */
	now = (ktime_t)(uintptr_t)args[0] |
	      (ktime_t)(uintptr_t)args[1] << 32;
#endif /* __SIZEOF_POINTER__ < 8 */
	tsc_resync_interrupt(now);
	return state;
}
#endif /* !CONFIG_NO_SMP */

INTERN NOBLOCK NOPREEMPT void
NOTHROW(KCALL x86_cmos_interrupt)(void) {
	time_t cmos_now, then;
	ktime_t now;

	/* Still need to acquire a lock here in SMP-mode in case
	 * some other CPU is currently doing `tsc_resync_init()'
	 * which calls `tsc_resync_realtime()'
	 *
	 * If we're not careful, some other CPU might also access
	 * the  CMOS at the  same time as us,  in which case they
	 * might  alter the selected  register while we're trying
	 * to update the alarm. We might then accidentally change
	 * the  system time  which would  result in  all sorts of
	 * troubles if the scheduler ends up thinking a couple of
	 * years  just passed over  the span of  just a couple of
	 * TSC ticks... */
	x86_cmos_lock_acquire_nopr();

	/* Clear pending interrupt flags. */
	cmos_rd(CMOS_STATE_C);
	cmos_now = cmos_gettime(false);
	x86_cmos_lock_release_nopr();
again:
	now = (ktime_t)(cmos_now - boottime.tv_sec) * NSEC_PER_SEC;

	/* Re-sync TSC timings. */
	tsc_resync_interrupt(now);

	/* Also re-sync TSC timings on other CPUs. */
#ifndef CONFIG_NO_SMP
	{
		void *args[CPU_IPI_ARGCOUNT];
#if __SIZEOF_POINTER__ >= 8
		args[0] = (void *)(uintptr_t)now;
#else /* __SIZEOF_POINTER__ >= 8 */
		args[0] = (void *)(uintptr_t)(now & 0xffffffff);
		args[1] = (void *)(uintptr_t)((now >> 32) & 0xffffffff);
#endif /* __SIZEOF_POINTER__ < 8 */
		cpu_broadcastipi_notthis(&cmos_resync_ipi, args,
		                         CPU_IPI_FNORMAL);
	}
#endif /* !CONFIG_NO_SMP */

	/* Like above: need to acquire the CMOS lock to prevent other CPUs
	 *             from changing the  currently selected register  and
	 *             possibly causing us to change the system time. */
	x86_cmos_lock_acquire_nopr();

	/* Set the new alarm for 2 seconds from the original read.
	 * TODO: This interval should be configurable via a commandline option! */
	cmos_now += 2;
	cmos_setalarm(cmos_now);

	/* Prime the alarm. */
	cmos_wr(CMOS_STATE_B, x86_cmos.cr_stb);

	/* Re-read  the current RTC time to see  if the alarm might have already
	 * expired. (very unlikely, we have to ensure that we don't accidentally
	 * miss it firing!) */
	then = cmos_gettime(false);
	x86_cmos_lock_release_nopr();

	/* Check for the unlikely case that the alarm has already expired. */
	if unlikely(then >= cmos_now) {
		cmos_now = then;
		goto again;
	}
}






DATDEF struct timespec boottime_ ASMNAME("boottime");

INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_cmos)(void) {
	x86_cmos.cr_stb = cmos_rd(CMOS_STATE_B);
	if unlikely(x86_cmos.cr_stb & (CMOS_B_UIE | CMOS_B_AIE |
	                               CMOS_B_PIE | CMOS_B_SET)) {
		x86_cmos.cr_stb &= ~(CMOS_B_UIE | CMOS_B_AIE | CMOS_B_PIE | CMOS_B_SET);
		cmos_wr(CMOS_STATE_B, x86_cmos.cr_stb);
		cmos_rd(CMOS_STATE_C);
	}
	/* Set-up the initial PIT counter. */
	outb(PIT_COMMAND,
	     PIT_COMMAND_SELECT_F0 |
	     PIT_COMMAND_ACCESS_FLOHI |
	     PIT_COMMAND_MODE_FRATEGEN |
	     PIT_COMMAND_FBINARY);
	outb_p(PIT_DATA0, PIT_HZ_DIV(X86_PIT_EARLY_HZ) & 0xff);
	outb(PIT_DATA0, (PIT_HZ_DIV(X86_PIT_EARLY_HZ) >> 8) & 0xff);

	//x86_cmos.cr_century = ...; /* TODO: This can be read from the ACPI descriptor table. */
	/* Initialize the initial system boot timestamp. */
	boottime_.tv_sec  = cmos_gettime(false);
	boottime_.tv_nsec = 0;
}


INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_tsc_resync)(void) {
	/* Initialize the RTC interrupt to perform periodic re-sync.
	 * Also enable use of realtime() for retrieving the  actual,
	 * current system time. */
	time_t then;
	PREEMPTION_DISABLE();
	x86_cmos_lock_acquire_nopr();
	x86_cmos.cr_alarm_hour   = cmos_rd(CMOS_ALARM_HOUR);
	x86_cmos.cr_alarm_minute = cmos_rd(CMOS_ALARM_MINUTE);
	x86_cmos.cr_alarm_second = cmos_rd(CMOS_ALARM_SECOND);
	x86_cmos.cr_stb = cmos_rd(CMOS_STATE_B);
	x86_cmos.cr_stb &= ~(CMOS_B_UIE | CMOS_B_AIE | CMOS_B_PIE | CMOS_B_SET);
	x86_cmos.cr_stb |= CMOS_B_AIE;
	then = cmos_gettime(false);
	cmos_setalarm(then + 1);
	cmos_wr(CMOS_STATE_B, x86_cmos.cr_stb);
	for (;;) {
		time_t then2 = cmos_gettime(false);
		if likely(then2 <= then)
			break;
		/* Alarm may not have triggered! */
		then = then2;
		cmos_setalarm(then + 1);
		cmos_wr(CMOS_STATE_B, x86_cmos.cr_stb);
	}
	x86_cmos_lock_release_nopr();
	PREEMPTION_ENABLE();
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_CMOS_C */
