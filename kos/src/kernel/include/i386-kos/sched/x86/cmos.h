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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_CMOS_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_CMOS_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/arch/time.h>
#include <sched/signal.h>
#include <sched/time.h>

#include <hw/rtc/cmos.h>
#include <sys/io.h>

#ifndef CONFIG_NO_SMP
#include <hybrid/sync/atomic-rwlock.h>
#endif /* !CONFIG_NO_SMP */

#ifdef __CC__
DECL_BEGIN

struct cmos_realtime_clock_struct
#if defined(__cplusplus) && !defined(CONFIG_WANT_CMOS_REALTIME_CLOCK_AS_STRUCT)
    : realtime_clock_struct
#endif /* __cplusplus && !CONFIG_WANT_CMOS_REALTIME_CLOCK_AS_STRUCT */
{
#if !defined(__cplusplus) || defined(CONFIG_WANT_CMOS_REALTIME_CLOCK_AS_STRUCT)
	struct realtime_clock_struct cr_clock;   /* The underlying clock. */
#endif /* !__cplusplus || CONFIG_WANT_CMOS_REALTIME_CLOCK_AS_STRUCT */
#ifndef CONFIG_NO_SMP
	struct atomic_rwlock cr_lock;    /* CMOS SMP lock. */
#endif /* !CONFIG_NO_SMP */
	u8                   cr_century;      /* [const] CMOS century register. (or 0 if unknown) */
	u8                   cr_stb;          /* [const] Configured BIOS value for `CMOS_STATE_B' */
	WEAK u8              cr_nmi;          /* [lock(cr_lock)] 0 if NMIs are enabled; `CMOS_ADDR_NONMI' otherwise */
	u8                  _cr_pad;          /* ... */
	u8                   cr_alarm_second; /* [lock(cr_lock)] Last value written to `CMOS_ALARM_SECOND' */
	u8                   cr_alarm_minute; /* [lock(cr_lock)] Last value written to `CMOS_ALARM_MINUTE' */
	u8                   cr_alarm_hour;   /* [lock(cr_lock)] Last value written to `CMOS_ALARM_HOUR' */
	WEAK u8              cr_stc;          /* [lock(ATOMIC)] Or'd together bits describing triggered interrupts (set of `CMOS_C_*')
	                                       * Bits in this set are atomically turned on just before `cr_irq' is broadcast */
	struct sig           cr_irq;          /* Signal broadcast when `X86_INTNO_PIC2_CMOS' is fired, and `cr_stc' changed. */
	time_t               cr_alarm;        /* [lock(cr_lock)] The currently programmed alarm timeout (or `INT64_MAX' if not programmed) */
};


/* Read CMOS control register `reg' */
FORCELOCAL ATTR_ARTIFICIAL NOBLOCK u8
NOTHROW(KCALL cmos_rd)(u8 reg) {
	outb(CMOS_ADDR, reg | cmos_realtime_clock.cr_nmi);
	return inb(CMOS_DATA);
}

/* Write CMOS control register `reg' */
FORCELOCAL ATTR_ARTIFICIAL NOBLOCK void
NOTHROW(KCALL cmos_wr)(u8 reg, u8 val) {
	outb(CMOS_ADDR, reg | cmos_realtime_clock.cr_nmi);
	outb(CMOS_DATA, val);
}


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_CMOS_H */
