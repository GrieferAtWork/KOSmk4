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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_IOPERM_C
#define GUARD_KERNEL_CORE_ARCH_I386_IOPERM_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/syscall.h>
#include <kernel/tss.h>
#include <kernel/types.h>
#include <sched/cpu.h>
#include <sched/iobm.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <kos/except-inval.h>

#include <assert.h>
#include <errno.h>
#include <string.h>

DECL_BEGIN

LOCAL void KCALL
iob_maskbyte(byte_t *pbyte, u8 byte_mask, u8 byte_flag) {
	u8 oldval;
	do {
		oldval = ATOMIC_READ(*pbyte);
	} while (!ATOMIC_CMPXCH_WEAK(*pbyte, oldval, (oldval & byte_mask) | byte_flag));
}

LOCAL void KCALL
iob_maskbyte_c(byte_t *pbyte,
               unsigned int minbit,
               unsigned int bitcnt,
               bool turn_on) {
	u8 bitmask;
	assert((minbit + bitcnt) <= 8);
	bitmask = (u8)(((1 << bitcnt) - 1) << minbit);
	iob_maskbyte(pbyte, ~bitmask,
	             turn_on ? 0 : bitmask);
}

/* Turn permission bits for a given range on/off. */
LOCAL void KCALL
iob_setrange(byte_t *iob, u16 minport, u16 maxport, bool turn_on) {
	size_t minbyte, maxbyte;
	unsigned int minbit, bitcnt;
	assert(maxport >= minport);
	minbyte = FLOORDIV(minport, 8);
	maxbyte = CEILDIV(maxport + 1, 8) - 1;
	assert(maxbyte >= minbyte);
	if (maxbyte == minbyte) {
		/* Special case: only a single byte is getting modified. */
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
	struct cpu *mycpu;
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
	/* Manipulate the IOBM of our own thread through use of the `x86_cpuiob' vector.
	 * Access to said vector is directly granted so-long as we keep the TASK_FKEEPCORE flag set. */
	old_thread_flags = ATOMIC_FETCHOR(THIS_TASK->t_flags, TASK_FKEEPCORE);
	TRY {
		mycpu = THIS_CPU;
		iob   = &FORCPU(mycpu, x86_cpuiob[0]);
		/* Update bits for the given range. */
		iob_setrange(iob,
		             (u16)from,
		             (u16)from + num - 1,
		             turn_on != 0);
	} EXCEPT {
		if (!(old_thread_flags & TASK_FKEEPCORE))
			ATOMIC_FETCHAND(THIS_TASK->t_flags, ~TASK_FKEEPCORE);
		RETHROW();
	}
	return -EOK;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_IOPERM_C */
