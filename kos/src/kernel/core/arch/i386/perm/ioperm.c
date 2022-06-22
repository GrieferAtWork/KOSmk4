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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_IOPERM_C
#define GUARD_KERNEL_CORE_ARCH_I386_IOPERM_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/task.h>
#include <sched/x86/iobm.h>
#include <sched/x86/tss.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <kos/except/reason/inval.h>

#include <assert.h>
#include <errno.h>
#include <string.h>

DECL_BEGIN

LOCAL NONNULL((1)) void KCALL
iob_maskbyte(byte_t *pbyte, u8 byte_mask, u8 byte_flag) {
	u8 oldval;
	do {
		oldval = ATOMIC_READ(*pbyte);
		/* FIXME: A rare (and random) E_SEGFAULT has been observed that originates from the following line:
		 * >> [2022-06-19T15:19:18.457399057:trace ][16] sys_ioperm(from: 1016, num: 1, turn_on: 1)
		 * >> [2022-06-19T15:19:18.458021345:debug ][16][segfault] Fault at FFFFFFFF8095907F (page FFFFFFFF80959000) [pc=FFFFFFFF803D7B9C,FFFFFFFF803D7BA0] [ecode=0x3]
		 * >> [2022-06-19T15:19:18.458376352:trace ][16][except] Translate exception 0xff0e:0x2,E_SEGFAULT_READONLY[0xffffffff8095907f,0x3] into errno=-EFAULT
		 */
	} while (!ATOMIC_CMPXCH_WEAK(*pbyte, oldval, (oldval & byte_mask) | byte_flag));
}

LOCAL NONNULL((1)) void KCALL
iob_maskbyte_c(byte_t *pbyte, shift_t minbit, shift_t bitcnt, bool turn_on) {
	u8 bitmask;
	assert((minbit + bitcnt) <= 8);
	bitmask = (u8)(((1 << bitcnt) - 1) << minbit);
	iob_maskbyte(pbyte, ~bitmask,
	             turn_on ? 0 : bitmask);
}

LOCAL ATTR_PURE WUNUSED NONNULL((1)) bool KCALL
iob_isenabled(byte_t const *iob, u16 port) {
	return (iob[FLOORDIV(port, 8)] & (1 << (port & 7))) != 0;
}

/* Turn permission bits for a given range on/off. */
LOCAL NONNULL((1)) void KCALL
iob_setrange(byte_t *iob, u16 minport, u16 maxport, bool turn_on) {
	size_t minbyte, maxbyte;
	shift_t minbit;
	assert(maxport >= minport);
	minbyte = FLOORDIV(minport, 8);
	maxbyte = CEILDIV(maxport + 1, 8) - 1;
	assert(maxbyte >= minbyte);

	/* Special case: only a single byte is getting modified. */
	if (maxbyte == minbyte) {
		shift_t bitcnt;
		minbit = minport & 7;
		bitcnt = (maxport - minport) + 1;

		/* Update the bitmap mask. */
		iob_maskbyte_c(iob + minbyte,
		               minbit, bitcnt,
		               turn_on);
		return;
	}

	/* Update the bitsets for the first and last affected bitset byte */
	minbit = minport & 7;
	iob_maskbyte_c(iob + minbyte, minbit, 8 - minbit, turn_on);
	iob_maskbyte_c(iob + maxbyte, 0, (maxport & 7) + 1, turn_on);

	/* Fill in all intermediate bytes. */
	if (minbyte + 1 < maxbyte) {
		memset(iob + minbyte,
		       turn_on ? 0x00 : 0xff,
		       (maxbyte - minbyte) - 1);
	}
}


DEFINE_SYSCALL3(errno_t, ioperm,
                syscall_ulong_t, from,
                syscall_ulong_t, num,
                syscall_ulong_t, turn_on) {
	uintptr_t old_thread_flags;
	struct task *caller;
	struct cpu *me;
	byte_t *iob;
	if unlikely(!num)
		return -EOK;
	if unlikely((syscall_ulong_t)(from + num) < from ||
	            (syscall_ulong_t)(from + num) > 0x10000) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_IOPERM_RANGE,
		      0x10000);
	}
	if (turn_on != 0 && turn_on != 1) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_IOPERM_TURNON,
		      turn_on);
	}

	/* Manipulate the  IOBM of  our own  thread  through use  of the  `thiscpu_x86_iob'  vector.
	 * Access to said vector is directly granted so-long as we keep the TASK_FKEEPCORE flag set. */
	caller           = THIS_TASK;
	old_thread_flags = ATOMIC_FETCHOR(caller->t_flags, TASK_FKEEPCORE);
	RAII_FINALLY {
		if (!(old_thread_flags & TASK_FKEEPCORE))
			ATOMIC_AND(caller->t_flags, ~TASK_FKEEPCORE);
	};
	COMPILER_READ_BARRIER();
	me  = caller->t_cpu;
	iob = &FORCPU(me, thiscpu_x86_iob[0]);

	/* Ensure that the caller is allowed hardware port access.
	 * This essentially enforces that:
	 *  - Anyone is allowed to disable ports (or keep them enabled)
	 *  - As such, we must only throw an insufficient-rights exception
	 *    if the calling  thread doesn't have  permissions to turn  on
	 *    permissions for some specific port. */
#ifndef CONFIG_EVERYONE_IS_ROOT
	if (turn_on && !capable(CAP_SYS_RAWIO)) {
		u32 i, end = (u32)(u16)from + (u32)(u16)num;
		for (i = (u32)(u16)from; i < end; ++i) {
			if (!iob_isenabled(iob, i))
				THROW(E_INSUFFICIENT_RIGHTS, CAP_SYS_RAWIO);
		}
	} else
#endif /* !CONFIG_EVERYONE_IS_ROOT */
	{
		/* Update bits for the given range. */
		iob_setrange(iob,
		             (u16)from,
		             (u16)from + (u16)num - 1,
		             turn_on != 0);
	}
	return -EOK;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_IOPERM_C */
