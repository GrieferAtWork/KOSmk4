/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_CMOS_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_CMOS_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/sig.h>
#include <sched/task.h>

#include <hybrid/__atomic.h>

#include <hw/rtc/cmos.h>
#include <sys/io.h>

#ifndef CONFIG_NO_SMP
#include <hybrid/sched/atomic-lock.h>
#endif /* !CONFIG_NO_SMP */

#ifdef __CC__
DECL_BEGIN

struct x86_cmos_struct {
#ifndef CONFIG_NO_SMP
	struct atomic_lock cr_lock;         /* CMOS SMP lock. */
#endif /* !CONFIG_NO_SMP */
	u8                 cr_century;      /* [const] CMOS century register. (or 0 if unknown) */
	u8                 cr_stb;          /* [const] Configured BIOS value for `CMOS_STATE_B' */
	WEAK u8            cr_nmi;          /* [lock(cr_lock)] 0 if NMIs are enabled; `CMOS_ADDR_NONMI' otherwise */
	u8                _cr_pad1;         /* ... */
	u8                 cr_alarm_second; /* [lock(cr_lock)] Last value written to `CMOS_ALARM_SECOND' */
	u8                 cr_alarm_minute; /* [lock(cr_lock)] Last value written to `CMOS_ALARM_MINUTE' */
	u8                 cr_alarm_hour;   /* [lock(cr_lock)] Last value written to `CMOS_ALARM_HOUR' */
	u8                _cr_pad2;         /* ... */
};

DATDEF struct x86_cmos_struct x86_cmos;

#ifndef CONFIG_NO_SMP
#define x86_cmos_lock_acquire_nopr() atomic_lock_acquire_nopr(&x86_cmos.cr_lock)
#define x86_cmos_lock_release_nopr() atomic_lock_release_nopr(&x86_cmos.cr_lock)
#else /* !CONFIG_NO_SMP */
#define x86_cmos_lock_acquire_nopr() (void)0
#define x86_cmos_lock_release_nopr() (void)0
#endif /* CONFIG_NO_SMP */
#define x86_cmos_lock_acquire() atomic_lock_acquire_smp(&x86_cmos.cr_lock)
#define x86_cmos_lock_release() atomic_lock_release_smp(&x86_cmos.cr_lock)
#define x86_cmos_lock_break()   atomic_lock_release_smp_b(&x86_cmos.cr_lock)

/* Read CMOS control register `reg' */
#define cmos_rd(reg)                           \
	(outb(CMOS_ADDR, (reg) | x86_cmos.cr_nmi), \
	 inb(CMOS_DATA))

/* Write CMOS control register `reg' */
#define cmos_wr(reg, val)                      \
	(outb(CMOS_ADDR, (reg) | x86_cmos.cr_nmi), \
	 outb(CMOS_DATA, (val)))


/* Get/Set NMI (non-maskable interrupt) being enabled
 * These interrupts should normally be enabled in all situations,
 * and should only be  disabled momentarily, and when  absolutely
 * necessary.
 * Also note that NMI enable/disable is controlled globally, and
 * not, say, per-CPU!
 * @param: enabled: The new nmi-enabled state (if different from `return',
 *                  the state was changed)
 * @return: * :     The NMI-enabled state prior to the call being made. */
#define x86_get_nmi_enabled() \
	((__hybrid_atomic_load(&x86_cmos.cr_nmi, __ATOMIC_ACQUIRE) & CMOS_ADDR_NONMI) == 0)
LOCAL NOBLOCK NOPREEMPT __BOOL
NOTHROW(KCALL x86_set_nmi_enabled_nopr)(__BOOL enabled) {
	u8 old_nmi, new_nmi;
	new_nmi = enabled ? 0 : CMOS_ADDR_NONMI;
	x86_cmos_lock_acquire_nopr();
	old_nmi = __hybrid_atomic_xch(&x86_cmos.cr_nmi, new_nmi, __ATOMIC_SEQ_CST);
	if (old_nmi != new_nmi)
		outb(CMOS_ADDR, new_nmi); /* Update hardware */
	x86_cmos_lock_release_nopr();
	return (old_nmi & CMOS_ADDR_NONMI) == 0;
}
LOCAL NOBLOCK NOPREEMPT __BOOL
NOTHROW(KCALL x86_set_nmi_enabled)(__BOOL enabled) {
	u8 old_nmi, new_nmi;
	new_nmi = enabled ? 0 : CMOS_ADDR_NONMI;
	x86_cmos_lock_acquire();
	old_nmi = __hybrid_atomic_xch(&x86_cmos.cr_nmi, new_nmi, __ATOMIC_SEQ_CST);
	if (old_nmi != new_nmi)
		outb(CMOS_ADDR, new_nmi); /* Update hardware */
	x86_cmos_lock_release();
	return (old_nmi & CMOS_ADDR_NONMI) == 0;
}



DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_CMOS_H */
