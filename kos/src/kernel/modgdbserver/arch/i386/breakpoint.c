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
#ifndef GUARD_MODGDBSERVER_ARCH_I386_BREAKPOINT_C
#define GUARD_MODGDBSERVER_ARCH_I386_BREAKPOINT_C 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/mman/rw.h>
#include <kernel/x86/breakpoint.h>

#include <hybrid/atomic.h>

#include <asm/cpu-flags.h> /* DR_* */

#include <errno.h>
#include <stddef.h>

#include "../../gdb.h"

DECL_BEGIN

#define OP_INT3 0xcc /* int3 opcode */

/*[[[config CONFIG_MODGDBSERVER_SWBREAK_MAXCNT! = 256]]]*/
#ifndef CONFIG_MODGDBSERVER_SWBREAK_MAXCNT
#define CONFIG_MODGDBSERVER_SWBREAK_MAXCNT 256
#endif /* !CONFIG_MODGDBSERVER_SWBREAK_MAXCNT */
/*[[[end]]]*/

struct sw_brk {
	struct mman *sb_vm;   /* [0..1] The VM inside of which this breakpoint exists.
	                     * When  NULL,  then  this  entry  is  not  being  used. */
	byte_t    *sb_addr; /* [1..1][valid_if(sb_vm != NULL)] The breakpointa address. */
	byte_t     sb_prev; /* The breakpoint's previous value. */
	byte_t     sb_pad[sizeof(void *) - 1];
};

/* [lock(append(PRIVATE(GDB_HOST_THREAD)),
 *       remove(PRIVATE(GDB_HOST_THREAD) || wasdestroyed(->sb_vm)))]
 * List of defined software breakpoints. */
PRIVATE struct sw_brk GDBBreak_SwList[CONFIG_MODGDBSERVER_SWBREAK_MAXCNT];

/* [lock(PRIVATE(GDB_HOST_THREAD) || ATOMIC(NEWVAL < OLDVAL))]
 * Index of the lowest sw-breakpoint slot which may be free (sb_vm == NULL) */
PRIVATE size_t GDBBreak_SwMinFree = 0;

/* [lock(PRIVATE(GDB_HOST_THREAD))]
 * Index  of the greatest sw-breakpoint slot which may be in use
 * Note however that the slot itself,  as well as any number  of
 * its predecessors may actually not be in use, however any slot
 * above this value is guarantied to not be in use. */
PRIVATE size_t GDBBreak_SwMaxUsed = 0;

PRIVATE NOBLOCK void
NOTHROW(FCALL GDBBreak_SwMinFree_SetLower)(size_t newval) {
	size_t oldval;
	for (;;) {
		oldval = ATOMIC_READ(GDBBreak_SwMinFree);
		if (newval >= oldval)
			break;
		if (ATOMIC_CMPXCH_WEAK(GDBBreak_SwMinFree, oldval, newval))
			break;
	}
}

/* Check   if  a  given  Sw  breakpoint  exists.
 * NOTE: The caller must be the GDB host thread.
 * @return: true:  An entry already exists.
 * @return: false: No matching entry exists. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL GDBBreak_SwExists)(struct mman const *effective_mm,
                                 byte_t *addr) {
	size_t i;
	for (i = 0; i <= GDBBreak_SwMaxUsed; ++i) {
		if (GDBBreak_SwList[i].sb_vm != effective_mm)
			continue; /* Already in use. */
		if (GDBBreak_SwList[i].sb_addr != addr)
			continue; /* Already in use. */
		return true; /* Found it! */
	}
	return false;
}

/* Push a given software breakpoint onto the SW stack.
 * NOTE: The  caller  must  be  the  GDB  host thread.
 * @return: true:  Successfully create the new SW break entry.
 * @return: false: All slots are already in use. */
PRIVATE NOBLOCK bool
NOTHROW(FCALL GDBBreak_SwPush)(struct mman *effective_mm,
                               byte_t *addr, byte_t prev) {
	size_t i, start;
	start = ATOMIC_READ(GDBBreak_SwMinFree);
again:
	for (i = start;
	     i < CONFIG_MODGDBSERVER_SWBREAK_MAXCNT; ++i) {
		if (GDBBreak_SwList[i].sb_vm)
			continue; /* Already in use. */
		/* Use this slot! */
		GDBBreak_SwList[i].sb_vm   = effective_mm;
		GDBBreak_SwList[i].sb_addr = addr;
		GDBBreak_SwList[i].sb_prev = prev;
		if (GDBBreak_SwMaxUsed < i)
			GDBBreak_SwMaxUsed = i;
		ATOMIC_CMPXCH(GDBBreak_SwMinFree, start, i + 1);
		return true;
	}
	i = ATOMIC_READ(GDBBreak_SwMinFree);
	if (start != i) {
		start = i;
		goto again;
	}
	return false;
}

/* Pop a given software breakpoint from the SW stack.
 * NOTE: The  caller  must  be the  GDB  host thread.
 * @return: true:  Successfully removed the new SW break entry.
 * @return: false: No slot matching the given VM and ADDR exists. */
PRIVATE NOBLOCK bool
NOTHROW(FCALL GDBBreak_SwPop)(struct mman *effective_mm,
                              byte_t *addr,
                              byte_t *__restrict pprev) {
	size_t i;
	for (i = 0; i <= GDBBreak_SwMaxUsed; ++i) {
		if (GDBBreak_SwList[i].sb_vm != effective_mm)
			continue; /* Already in use. */
		if (GDBBreak_SwList[i].sb_addr != addr)
			continue; /* Already in use. */
		/* Use this slot! */
		*pprev = GDBBreak_SwList[i].sb_prev;
		if (i == GDBBreak_SwMaxUsed) {
			while (GDBBreak_SwMaxUsed != 0) {
				--GDBBreak_SwMaxUsed;
				if (GDBBreak_SwList[GDBBreak_SwMaxUsed].sb_vm != NULL)
					break;
			}
		}
		/* Return the old prev-value for the slot. */
		*pprev = GDBBreak_SwList[i].sb_prev;
		GDBBreak_SwList[i].sb_vm = NULL;
		GDBBreak_SwMinFree_SetLower(i);
		return true;
	}
	return false;
}

PRIVATE NOBLOCK errno_t
NOTHROW(FCALL GDB_AddSwBreak)(struct mman *__restrict effective_mm, byte_t *addr) {
	byte_t prev;
	byte_t op_int3[] = { OP_INT3 };
	if unlikely(GDBBreak_SwExists(effective_mm, addr))
		return EALREADY;
	if unlikely(GDB_MMan_ReadMemory(effective_mm, addr, &prev, 1) != 0)
		return EFAULT; /* Faulty memory */
	if unlikely(!GDBBreak_SwPush(effective_mm, addr, prev))
		return ENOMEM; /* Too many breakpoints already */
	/* Override the target location. */
	if unlikely(GDB_MMan_WriteMemoryWithoutSwBreak(effective_mm, addr, op_int3, 1) != 0) {
		GDBBreak_SwPop(effective_mm, addr, &prev);
		return EFAULT; /* Faulty memory */
	}
	return EOK;
}

PRIVATE NOBLOCK errno_t
NOTHROW(FCALL GDB_DelSwBreak)(struct mman *__restrict effective_mm, byte_t *addr) {
	byte_t prev;
	if (!GDBBreak_SwPop(effective_mm, (byte_t *)addr, &prev))
		return ENOENT; /* No breakpoint at this location */
	/* Restore what was originally written at the given address. */
	if unlikely(GDB_MMan_WriteMemoryWithoutSwBreak(effective_mm, addr, &prev, 1) != 0)
		return EFAULT; /* Faulty memory */
	return EOK;
}


/* GDB breakpoint API
 * @param: kind: arch-specific
 * @return: EOK:      Success
 * @return: ENOSYS:   The specified breakpoint type isn't supported, or breakpoints aren't supported in general
 * @return: EALREADY: [GDB_AddBreak] A breakpoint already exists for the specified location.
 * @return: ENOMEM:   [GDB_AddBreak] Failed to add the breakpoint (too many breakpoints already defined)
 * @return: EFAULT:   [GDB_AddBreak] Attempted to define a software-breakpoint at a faulty memory location.
 * @return: ENOENT:   [GDB_DelBreak] The specified breakpoint doesn't exist. */
INTERN WUNUSED errno_t
NOTHROW(FCALL GDB_MMan_AddBreak)(struct mman *__restrict effective_mm,
                                 unsigned int type, VIRT void *addr,
                                 unsigned int kind) {
	unsigned int cond;
	(void)kind;
	if (type == GDB_BREAKPOINT_TYPE_SWBREAK)
		return GDB_AddSwBreak(effective_mm, (byte_t *)addr);
	if (type == GDB_BREAKPOINT_TYPE_HWBREAK) {
		cond = DR_CEXEC;
	} else if (type == GDB_BREAKPOINT_TYPE_WRITE) {
		cond = DR_CWRITE;
	} else {
		cond = DR_CREADWRITE;
	}
	if (!mman_addhwbreak(effective_mm, addr, cond, DR_S1))
		return ENOMEM;
	return EOK;
}

INTERN WUNUSED errno_t
NOTHROW(FCALL GDB_MMan_DelBreak)(struct mman *__restrict effective_mm,
                                 unsigned int type, VIRT void *addr,
                                 unsigned int kind) {
	unsigned int cond;
	(void)kind;
	if (type == GDB_BREAKPOINT_TYPE_SWBREAK)
		return GDB_DelSwBreak(effective_mm, (byte_t *)addr);
	if (type == GDB_BREAKPOINT_TYPE_HWBREAK) {
		cond = DR_CEXEC;
	} else if (type == GDB_BREAKPOINT_TYPE_WRITE) {
		cond = DR_CWRITE;
	} else {
		cond = DR_CREADWRITE;
	}
	if (!mman_addhwbreak(effective_mm, addr, cond, DR_S1))
		return ENOENT;
	return EOK;
}

/* Remove all breakpoints from any sort of VM */
INTERN void
NOTHROW(FCALL GDB_RemoveAllBreakpoints)(void) {
	size_t i;
	for (i = 0; i <= GDBBreak_SwMaxUsed; ++i) {
		byte_t *addr, prev;
		struct mman *thatvm;
		thatvm = GDBBreak_SwList[i].sb_vm;
		if (!thatvm)
			continue;
		addr = GDBBreak_SwList[i].sb_addr;
		prev = GDBBreak_SwList[i].sb_prev;
		GDBBreak_SwList[i].sb_vm = NULL;
		TRY {
			mman_write(thatvm, addr, &prev, 1, true);
		} EXCEPT {
		}
	}
	GDBBreak_SwMaxUsed = 0;
	GDBBreak_SwMinFree = 0;
}

/* Delete all internal knowledge of breakpoints concerning `effective_mm'.
 * Note  that this function may be called  from threads other than the GDB
 * host thread, as it is invoked as part of `mman_onfini_callbacks()'! */
INTERN void
NOTHROW(FCALL GDB_ClearAllBreakpointsOfMMan)(struct mman *__restrict effective_mm) {
	size_t i, maxused;
	bool isfirst = true;
	maxused = ATOMIC_READ(GDBBreak_SwMaxUsed);
	for (i = 0; i <= maxused; ++i) {
		if (GDBBreak_SwList[i].sb_vm != effective_mm)
			continue; /* Already in use. */
		/* Try to delete this slot. */
		if (!ATOMIC_CMPXCH(GDBBreak_SwList[i].sb_vm, effective_mm, NULL))
			continue;
		if (isfirst) {
			GDBBreak_SwMinFree_SetLower(i);
			isfirst = false;
		}
	}
}

/* Copy all breakpoint definitions of `oldmm' to also exist in `newmm' (called during `mman_fork()') */
INTERN void
NOTHROW(FCALL GDB_CloneAllBreakpointsFromMMan)(struct mman *__restrict newmm,
                                               struct mman *__restrict oldmm) {
	size_t i, maxused;
	maxused = ATOMIC_READ(GDBBreak_SwMaxUsed);
	for (i = 0; i <= maxused; ++i) {
		byte_t *addr, prev;
		if (GDBBreak_SwList[i].sb_vm != oldmm)
			continue; /* Already in use. */
		/* Add a new breakpoint for `newmm' */
		addr = GDBBreak_SwList[i].sb_addr;
		prev = GDBBreak_SwList[i].sb_prev;
		GDBBreak_SwPush(newmm, addr, prev);
	}
}


/* Include  (insert)  or exclude  (remove) SwBreak  instruction overrides
 * defined within  the  range  `addr...+=bufsize' with  the  given  `buf'
 * This  is used to hide/expose software breakpoint bytes from GDB, since
 * I have seen cases where GDB will first set a breakpoint, then read the
 * memory location, reading back `0xcc', then remove the breakpoint,  and
 * finally trick itself into thinking that the target memory location was
 * actually an 0xcc byte all along  (causing it to adjust PC=ADDR+1  when
 * resuming from the memory location, thus breaking execution by  placing
 * the instruction pointer in the middle of the overwritten  instruction)
 * NOTE: When  calling  `GDB_IncludeSwBreak()', saved  restore  memory for
 *       software breakpoints is overwritten with memory taken from `buf',
 *       meaning that when  using these functions  along side  read/write,
 *       writing overtop of a software breakpoint will actually write into
 *       the  restore buffer and only into main memory once the breakpoint
 *       is removed. */
INTERN NONNULL((1, 3)) void
NOTHROW(FCALL GDB_IncludeSwBreak)(struct mman *__restrict effective_mm,
                                  VIRT void const *addr,
                                  void *buf, size_t bufsize) {
	size_t i;
	byte_t *start, *end;
	start = (byte_t *)addr;
	end   = (byte_t *)addr + bufsize;
	for (i = 0; i <= GDBBreak_SwMaxUsed; ++i) {
		if (GDBBreak_SwList[i].sb_vm != effective_mm)
			continue;
		if (GDBBreak_SwList[i].sb_addr >= start &&
		    GDBBreak_SwList[i].sb_addr < end) {
			size_t reloff;
			reloff = (size_t)(GDBBreak_SwList[i].sb_addr - start);
			/* Override the restore location, and include a breakpoint in the buffer. */
			GDBBreak_SwList[i].sb_prev = ((byte_t *)buf)[reloff];
			((byte_t *)buf)[reloff]    = OP_INT3;
		}
	}
}

INTERN NONNULL((1, 3)) void
NOTHROW(FCALL GDB_ExcludeSwBreak)(struct mman *__restrict effective_mm,
                                  VIRT void const *addr,
                                  void *buf, size_t bufsize) {
	size_t i;
	byte_t *start, *end;
	start = (byte_t *)addr;
	end   = (byte_t *)addr + bufsize;
	for (i = 0; i <= GDBBreak_SwMaxUsed; ++i) {
		if (GDBBreak_SwList[i].sb_vm != effective_mm)
			continue;
		if (GDBBreak_SwList[i].sb_addr >= start &&
		    GDBBreak_SwList[i].sb_addr < end) {
			size_t reloff;
			reloff = (size_t)(GDBBreak_SwList[i].sb_addr - start);
			/* Remove the breakpoint from the memory buffer. */
			((byte_t *)buf)[reloff] = GDBBreak_SwList[i].sb_prev;
		}
	}
}

DECL_END

#endif /* !GUARD_MODGDBSERVER_ARCH_I386_BREAKPOINT_C */
