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
#ifndef GUARD_MODGDB_ARCH_I386_BREAKPOINT_C
#define GUARD_MODGDB_ARCH_I386_BREAKPOINT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>
#include <kernel/breakpoint.h>
#include <kernel/vm.h>
#include <kernel/types.h>
#include <kernel/except.h>
#include <errno.h>
#include <string.h>

#include "../../gdb.h"

DECL_BEGIN

#ifndef CONFIG_SWBREAK_MAX_COUNT
#define CONFIG_SWBREAK_MAX_COUNT 256
#endif /* !CONFIG_SWBREAK_MAX_COUNT */

#ifndef CONFIG_NO_SMP
PRIVATE struct atomic_rwlock GDB_SwBreakLock = ATOMIC_RWLOCK_INIT;
#define GDBSWBREAK_ACQUIRE_BUFFER_LOCK()                  \
	do {                                                  \
		pflag_t _pflag_was;                               \
		COMPILER_BARRIER();                               \
		_pflag_was = PREEMPTION_PUSHOFF();                \
		while (!atomic_rwlock_trywrite(&GDB_SwBreakLock)) \
			task_pause();                                 \
		do

#define GDBSWBREAK_BREAK_BUFFER_LOCK()         \
	(COMPILER_BARRIER(),                       \
	 atomic_rwlock_endwrite(&GDB_SwBreakLock), \
	 PREEMPTION_POP(_pflag_was))
#else /* !CONFIG_NO_SMP */
#define GDBSWBREAK_ACQUIRE_BUFFER_LOCK()   \
	do {                                   \
		pflag_t _pflag_was;                \
		COMPILER_BARRIER();                \
		_pflag_was = PREEMPTION_PUSHOFF(); \
		do
#define GDBSWBREAK_BREAK_BUFFER_LOCK() \
	(COMPILER_BARRIER(),               \
	 PREEMPTION_POP(_pflag_was))
#endif /* CONFIG_NO_SMP */
#define GDBSWBREAK_RELEASE_BUFFER_LOCK() \
		__WHILE0;                        \
		GDBSWBREAK_BREAK_BUFFER_LOCK();  \
	} __WHILE0


typedef struct {
	struct vm *sb_vm;   /* [0..1] The VM inside of which this breakpoint exists.
	                     * When NULL, then this entry is not being used. */
	byte_t    *sb_addr; /* [1..1][valid_if(sb_vm != NULL)] The breakpointa address. */
	byte_t     sb_prev; /* The breakpoint's previous value. */
	byte_t     sb_pad[sizeof(void *) - 1];
} GDB_SwBreak;

/* [lock(GDB_SwBreakLock)] List of defined software breakpoints. */
PRIVATE GDB_SwBreak GDB_SwBreakList[CONFIG_SWBREAK_MAX_COUNT];

PRIVATE NOBLOCK bool
NOTHROW(FCALL GDB_HasSwBreak)(struct vm *effective_vm,
                              byte_t *addr) {
	bool result = false;
	GDBSWBREAK_ACQUIRE_BUFFER_LOCK() {
		unsigned int i;
		for (i = 0; i < CONFIG_SWBREAK_MAX_COUNT; ++i) {
			struct vm *v = GDB_SwBreakList[i].sb_vm;
			if (v != effective_vm) {
				if (!v)
					break;
				continue;
			}
			if (GDB_SwBreakList[i].sb_addr != addr)
				continue;
			result = true;
			break;
		}
	}
	GDBSWBREAK_RELEASE_BUFFER_LOCK();
	return result;
}

PRIVATE NOBLOCK bool
NOTHROW(FCALL GDB_PushSwBreak)(struct vm *effective_vm,
                               byte_t *addr, byte_t prev) {
	bool result = false;
	GDBSWBREAK_ACQUIRE_BUFFER_LOCK() {
		unsigned int i;
		for (i = 0; i < CONFIG_SWBREAK_MAX_COUNT; ++i) {
			if (GDB_SwBreakList[i].sb_vm)
				continue;
			GDB_SwBreakList[i].sb_vm   = effective_vm;
			GDB_SwBreakList[i].sb_addr = addr;
			GDB_SwBreakList[i].sb_prev = prev;
			result = true;
			break;
		}
	}
	GDBSWBREAK_RELEASE_BUFFER_LOCK();
	return result;
}

PRIVATE NOBLOCK bool
NOTHROW(FCALL GDB_PopSwBreak)(struct vm *effective_vm,
                              byte_t *addr,
                              byte_t *__restrict pprev) {
	bool result = false;
	GDBSWBREAK_ACQUIRE_BUFFER_LOCK() {
		unsigned int i;
		for (i = 0; i < CONFIG_SWBREAK_MAX_COUNT; ++i) {
			struct vm *v = GDB_SwBreakList[i].sb_vm;
			if (v != effective_vm) {
				if (!v)
					break;
				continue;
			}
			if (GDB_SwBreakList[i].sb_addr != addr)
				continue;
			*pprev = GDB_SwBreakList[i].sb_prev;
			GDB_SwBreakList[i].sb_vm = NULL;
			{
				unsigned int last_used;
				/* Shift the list of sw breakpoints to always
				 * ensure that the first entry with `sb_vm == NULL'
				 * can be used as a premature terminator for the list. */
				++i;
				last_used = i;
				while (last_used < CONFIG_SWBREAK_MAX_COUNT &&
				       GDB_SwBreakList[last_used].sb_vm != NULL)
					++last_used;
				memmove(&GDB_SwBreakList[i - 1],
				        &GDB_SwBreakList[i],
				        (last_used - i) * sizeof(GDB_SwBreak));
				if (last_used < CONFIG_SWBREAK_MAX_COUNT)
					GDB_SwBreakList[last_used].sb_vm = NULL;
			}
			result = true;
			break;
		}
	}
	GDBSWBREAK_RELEASE_BUFFER_LOCK();
	return result;
}


/* Include (insert) or exclude (remove) SwBreak instruction overrides
 * defined within the range `addr...+=bufsize' with the given `buf'
 * This is used to hide/expose software breakpoint bytes from GDB, since
 * I have seen cases where GDB will first set a breakpoint, then read the
 * memory location, reading back `0xcc', then remove the breakpoint, and
 * finally trick itself into thinking that the target memory location was
 * actually an 0xcc byte all along (causing it to adjust PC=ADDR+1 when
 * resuming from the memory location, thus breaking execution by placing
 * the instruction pointer in the middle of the actual instruction)
 * NOTE: When calling `GDB_IncludeSwBreak()', saved restore memory for
 *       software breakpoints is overwritten with memory taken from `buf',
 *       meaning that when using these functions along side read/write,
 *       writing overtop of a software breakpoint will actually write into
 *       the restore buffer and only into main memory once the breakpoint
 *       is removed. */
INTERN NONNULL((2)) void
NOTHROW(FCALL GDB_IncludeSwBreak)(vm_virt_t addr, void *buf, size_t bufsize) {
	byte_t *start, *end;
	struct vm *effective_vm = &vm_kernel;
    if (addr < (vm_virt_t)KERNEL_BASE)
		effective_vm = GDB_GetCurrentThread()->t_vm;
	start = (byte_t *)addr;
	end   = (byte_t *)addr + bufsize;
	GDBSWBREAK_ACQUIRE_BUFFER_LOCK() {
		unsigned int i;
		for (i = 0; i < CONFIG_SWBREAK_MAX_COUNT; ++i) {
			struct vm *v = GDB_SwBreakList[i].sb_vm;
			if (v != effective_vm) {
				if (!v)
					break;
				continue;
			}
			if (GDB_SwBreakList[i].sb_addr >= start &&
			    GDB_SwBreakList[i].sb_addr < end) {
				size_t reloff;
				reloff = (size_t)(GDB_SwBreakList[i].sb_addr - start);
				/* Override the restore location, and include a breakpoint in the buffer. */
				GDB_SwBreakList[i].sb_prev = ((byte_t *)buf)[reloff];
				((byte_t *)buf)[reloff]    = 0xcc;
			}
		}
	}
	GDBSWBREAK_RELEASE_BUFFER_LOCK();
}

INTERN NONNULL((2)) void
NOTHROW(FCALL GDB_ExcludeSwBreak)(vm_virt_t addr, void *buf, size_t bufsize) {
	byte_t *start, *end;
	struct vm *effective_vm = &vm_kernel;
    if (addr < (vm_virt_t)KERNEL_BASE)
		effective_vm = GDB_GetCurrentThread()->t_vm;
	start = (byte_t *)addr;
	end   = (byte_t *)addr + bufsize;
	GDBSWBREAK_ACQUIRE_BUFFER_LOCK() {
		unsigned int i;
		for (i = 0; i < CONFIG_SWBREAK_MAX_COUNT; ++i) {
			struct vm *v = GDB_SwBreakList[i].sb_vm;
			if (v != effective_vm) {
				if (!v)
					break;
				continue;
			}
			if (GDB_SwBreakList[i].sb_addr >= start &&
			    GDB_SwBreakList[i].sb_addr < end) {
				size_t reloff;
				reloff = (size_t)(GDB_SwBreakList[i].sb_addr - start);
				/* Remove the breakpoint from the memory buffer. */
				((byte_t *)buf)[reloff] = GDB_SwBreakList[i].sb_prev;
			}
		}
	}
	GDBSWBREAK_RELEASE_BUFFER_LOCK();
}



PRIVATE byte_t const opcode_int3[] = { 0xcc };

PRIVATE NOBLOCK errno_t
NOTHROW(FCALL GDB_AddSwBreak)(void *addr) {
	byte_t prev;
	struct vm *effective_vm = &vm_kernel;
	if (ADDR_IS_USER(addr))
		effective_vm = GDB_GetCurrentThread()->t_vm;
	if unlikely(GDB_HasSwBreak(effective_vm, (byte_t *)addr))
		return EALREADY;
	if unlikely(GDB_ReadMemory((vm_virt_t)addr, &prev, 1, true) != 0)
		return EFAULT; /* Faulty memory */
	if (!GDB_PushSwBreak(effective_vm, (byte_t *)addr, prev))
		return ENOMEM; /* Too many breakpoints already */
	/* Override the target location. */
	if unlikely(GDB_WriteMemory((vm_virt_t)addr, opcode_int3, 1, true) != 0) {
		GDB_PopSwBreak(effective_vm, (byte_t *)addr, &prev);
		return EFAULT; /* Faulty memory */
	}
	return EOK;
}

PRIVATE NOBLOCK errno_t
NOTHROW(FCALL GDB_DelSwBreak)(void *addr) {
	byte_t prev;
	struct vm *effective_vm = &vm_kernel;
	if (ADDR_IS_USER(addr))
		effective_vm = GDB_GetCurrentThread()->t_vm;
	if (!GDB_PopSwBreak(effective_vm, (byte_t *)addr, &prev))
		return ENOENT; /* No breakpoint at this location */
	/* Restore what was originally written at the given address. */
	if unlikely(GDB_WriteMemory((vm_virt_t)addr, &prev, 1, true) != 0)
		return EFAULT; /* Faulty memory */
	return EOK;
}



/* GDB breakpoint API */
INTERN WUNUSED errno_t
NOTHROW(FCALL GDB_AddBreak)(unsigned int type, void *addr, unsigned int kind) {
	struct vm *effective_vm = &vm_kernel;
	unsigned int cond;
	if (type == GDB_BREAKPOINT_TYPE_SWBREAK)
		return GDB_AddSwBreak(addr);
	if (ADDR_IS_USER(addr))
		effective_vm = GDB_GetCurrentThread()->t_vm;
	if (type == GDB_BREAKPOINT_TYPE_HWBREAK)
		cond = DR_CEXEC;
	else if (type == GDB_BREAKPOINT_TYPE_WRITE)
		cond = DR_CWRITE;
	else {
		cond = DR_CREADWRITE;
	}
	if (!vm_addhwbreak(effective_vm, addr, cond, DR_S1))
		return ENOMEM;
	return EOK;
}

INTERN WUNUSED errno_t
NOTHROW(FCALL GDB_DelBreak)(unsigned int type, void *addr, unsigned int kind) {
	struct vm *effective_vm = &vm_kernel;
	unsigned int cond;
	if (type == GDB_BREAKPOINT_TYPE_SWBREAK)
		return GDB_DelSwBreak(addr);
	if (ADDR_IS_USER(addr))
		effective_vm = GDB_GetCurrentThread()->t_vm;
	if (type == GDB_BREAKPOINT_TYPE_HWBREAK)
		cond = DR_CEXEC;
	else if (type == GDB_BREAKPOINT_TYPE_WRITE)
		cond = DR_CWRITE;
	else {
		cond = DR_CREADWRITE;
	}
	if (!vm_addhwbreak(effective_vm, addr, cond, DR_S1))
		return ENOENT;
	return EOK;
}

INTERN void
NOTHROW(FCALL GDB_RemoveAllBreakpoints)(void) {
again:
	GDBSWBREAK_ACQUIRE_BUFFER_LOCK() {
		unsigned int i;
		for (i = 0; i < CONFIG_SWBREAK_MAX_COUNT; ++i) {
			struct vm *thatvm;
			byte_t *addr, prev;
			thatvm = GDB_SwBreakList[i].sb_vm;
			if (!thatvm)
				continue;
			addr = GDB_SwBreakList[i].sb_addr;
			prev = GDB_SwBreakList[i].sb_prev;
			GDB_SwBreakList[i].sb_vm = NULL;
			GDBSWBREAK_BREAK_BUFFER_LOCK();
			/* Restore the original memory from the given location. */
			TRY {
				vm_write(thatvm, addr, &prev, 1, true);
			} EXCEPT {
			}
			goto again;
		}
	}
	GDBSWBREAK_RELEASE_BUFFER_LOCK();
}

/* Remove all saved user-space breakpoints from the given VM.
 * However, don't actually modify memory (since this function
 * is only called during exec()) */
INTERN void
NOTHROW(FCALL GDB_ClearAllKernelAndUserBreakpointsFromVM)(struct vm *__restrict effective_vm) {
again:
	GDBSWBREAK_ACQUIRE_BUFFER_LOCK() {
		unsigned int i;
		for (i = 0; i < CONFIG_SWBREAK_MAX_COUNT; ++i) {
			if (GDB_SwBreakList[i].sb_vm == effective_vm) {
				GDB_SwBreakList[i].sb_vm = NULL;
				continue;
			}
			if (GDB_SwBreakList[i].sb_vm == &vm_kernel) {
				/* Since GDB thinks that the kernel is a dynamic library that gets
				 * loaded into user-space programs, running exec() will make GDB
				 * think that all memory has gotten re-set back to its original
				 * state in regards to software breakpoints.
				 * So to account for that (and not make GDB think that the original
				 * memory at some given location was a 0xcc byte) */
				struct vm *thatvm;
				byte_t *addr, prev;
				thatvm = GDB_SwBreakList[i].sb_vm;
				if (!thatvm)
					continue;
				addr = GDB_SwBreakList[i].sb_addr;
				prev = GDB_SwBreakList[i].sb_prev;
				GDB_SwBreakList[i].sb_vm = NULL;
				GDBSWBREAK_BREAK_BUFFER_LOCK();
				/* Restore the original memory from the given location. */
				TRY {
					vm_write(thatvm, addr, &prev, 1, true);
				} EXCEPT {
				}
				goto again;
			}
		}
	}
	GDBSWBREAK_RELEASE_BUFFER_LOCK();
}


DECL_END

#endif /* !GUARD_MODGDB_ARCH_I386_BREAKPOINT_C */
