/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_DEBUGGER_MEMORY_C
#define GUARD_KERNEL_SRC_DEBUGGER_MEMORY_C 1
#define DISABLE_BRANCH_PROFILING
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/hook.h>
#include <debugger/rt.h>
#include <kernel/mman.h>
#include <kernel/mman/phys.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <sched/task.h>

#include <hybrid/align.h>

#include <kos/except.h>
#include <kos/nopf.h>

#include <alloca.h>
#include <string.h>

DECL_BEGIN


/* Return the page directory of `dbg_current' */
PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_rt_getpagedir")
ATTR_PURE WUNUSED pagedir_phys_t
NOTHROW(KCALL dbg_rt_getpagedir)(void) {
	struct mman *mm;
	if (!dbg_current)
		goto fallback;
	mm = dbg_current->t_mman;
	if (!mm)
		goto fallback;
	return mm->mm_pagedir_p;
fallback:
	return pagedir_kernel_phys;
}

/* Verify that the given page directory isn't corrupt. */
PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_rt_verifypagedir") ATTR_PURE WUNUSED bool
NOTHROW(KCALL dbg_rt_verifypagedir)(pagedir_phys_t pdir) {
#if PAGEDIR_ALIGN > 1
	if (!IS_ALIGNED((uintptr_t)pdir, PAGEDIR_ALIGN))
		return false; /* Badly aligned. */
#endif /* PAGEDIR_ALIGN > 1 */
	/* XXX: Additional (probably arch-specific) checks. */
	COMPILER_IMPURE();
	return true;
}




/* [default(true)]
 * Allow managed memory access to be performed by  `dbg_(read|write)memory'
 * and friends. What this means is that (so-long as the kernel hasn't  been
 * poisoned, and this field is set to `true' (which is is during a debugger
 * reset))  the below functions  can be used to  load lazy memory mappings,
 * and initiate the regular copy-on-write semantics expected by  high-level
 * memory access, and as would  also be done if  the access was being  done
 * directly, rather than through the below functions.
 * This  in turn is mainly useful when debugging user-space programs, where
 * this functionality allows one to  view memory that hasn't been  accessed
 * by the user-space program, yet, or was at one point off-loaded into swap
 * memory. But note  that this field  is ignored once  the kernel has  been
 * poisoned,  as this kind  of functionality may  cause the debugger memory
 * primitives  to call into  possibly faulty kernel  code (such as possibly
 * faulty disk drivers).
 * Also note that VIO memory is _never_ dispatched while in debugger  mode,
 * not  even when accessed  directly. Instead, any  VIO region will instead
 * result in a SEGFAULT, with the exception of the userkern segment,  which
 * simply acts as though it  didn't exist, allowing pass-through access  to
 * the actual kernel (meaning that when passed a kernel-space address, then
 * the below functions will instead read/write memory to/from kernel-space) */
PUBLIC ATTR_DBGBSS bool dbg_memory_managed = false;

#define ALLOW_MANAGED_MEMORY_ACCESS() \
	(dbg_memory_managed && !kernel_poisoned())




/* Get/set memory in the context of `dbg_current'
 * NOTE: These functions will not make use  of copy-on-write or lazy memory  allocations,
 *       but will instead indicate an error, or (in when `force' is true), write directly
 *       to the physical memory backing of the underlying page directory.
 * @return: * : The number of trailing bytes that could not be copied. */
PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_readmemory") size_t
NOTHROW(KCALL dbg_readmemory)(USER UNCHECKED void const *addr,
                              void *__restrict buf,
                              size_t num_bytes) {
	size_t error;
	if (!num_bytes)
		return 0; /* Nothing to do here. */
	/* NOTE: If the kernel hasn't been poisoned yet, we should
	 *       try  to access memory  normally, so-long as we're
	 *       not dealing with VIO memory.
	 *       Otherwise, debugging user-space programs becomes a
	 *       chore since  we'd be  unable to  load lazy  memory
	 *       mappings that haven't been accessed, yet. */
	if (ADDRRANGE_ISKERN(addr, (byte_t *)addr + num_bytes)) {
		error = memcpy_nopf(buf, addr, num_bytes);
		if (unlikely(error != 0) && ALLOW_MANAGED_MEMORY_ACCESS()) {
			size_t ok = num_bytes - error;
			NESTED_TRY {
				memcpy((byte_t *)buf + ok,
				       (byte_t const *)addr + ok,
				       error);
				error = 0;
			} EXCEPT {
			}
		}
	} else {
		pagedir_phys_t pdir;
		pdir = dbg_rt_getpagedir();
		if (!dbg_rt_verifypagedir(pdir))
			return num_bytes;
		/* Leave interrupts unchanged, since we don't have to worry
		 * about being preempted by another thread. (and if we are,
		 * it's up to that thread to properly preserve the  pagedir
		 * register, even if it's different from what's used by our
		 * current VM)
		 * This is  one of  the advantages  of being  in  debug-mode.
		 * Note also that we need to keep preemption enabled in order
		 * for the `memcpy()' below to be able to load unmapped pages
		 * from disk, which  can likely  only be done  as a  blocking
		 * operation.
		 * Also note that if that blocking operation fails, the user
		 *
		 */
		PAGEDIR_P_BEGINUSE_KEEP_PR(pdir) {
			error = memcpy_nopf(buf, addr, num_bytes);
			if (unlikely(error != 0) && ALLOW_MANAGED_MEMORY_ACCESS()) {
				struct mman *old_mm, *new_mm;
				size_t ok;
				NESTED_TRY {
					/* Re-validate   in   case  the   memcpy_nopf()  above
					 * changed something about dbg_current, or its fields. */
					if unlikely(!ADDR_ISKERN(dbg_current))
						goto done_nopanic_copy;
					new_mm = dbg_current->t_mman;
					if unlikely(!ADDR_ISKERN(new_mm))
						goto done_nopanic_copy;
					if (new_mm->mm_pagedir_p != pdir)
						goto done_nopanic_copy;
				} EXCEPT {
					goto done_nopanic_copy;
				}
				old_mm = THIS_MMAN;
				ok     = num_bytes - error;
				PERTASK_SET(this_mman, dbg_current->t_mman);
				NESTED_TRY {
					memcpy((byte_t *)buf + ok,
					       (byte_t const *)addr + ok,
					       error);
					/* If the memcpy() doesn't fail, then there isn't an error. */
					error = 0;
				} EXCEPT {
				}
				PERTASK_SET(this_mman, old_mm);
			}
done_nopanic_copy:
			;
		}
		PAGEDIR_P_ENDUSE_KEEP_PR(pdir);
	}
	return error;
}

PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_writememory") size_t
NOTHROW(KCALL dbg_writememory)(USER UNCHECKED void *addr,
                               void const *__restrict buf,
                               size_t num_bytes, bool force) {
	size_t error;
	pagedir_phys_t pdir;
	if (!num_bytes)
		return 0; /* Nothing to do here. */
	/* NOTE: If the kernel hasn't been poisoned yet, we should
	 *       try  to access memory  normally, so-long as we're
	 *       not dealing with VIO memory.
	 *       Otherwise, debugging user-space programs becomes a
	 *       chore since  we'd be  unable to  load lazy  memory
	 *       mappings that haven't been accessed, yet. */
	if (ADDRRANGE_ISKERN(addr, (byte_t *)addr + num_bytes)) {
again_memcpy_nopf_kernel:
		error = memcpy_nopf(addr, buf, num_bytes);
		if (error != 0) {
			if (ALLOW_MANAGED_MEMORY_ACCESS()) {
				size_t ok = num_bytes - error;
				NESTED_TRY {
					memcpy((byte_t *)buf + ok,
					       (byte_t const *)addr + ok,
					       error);
					return 0;
				} EXCEPT {
				}
			}
			if (force) {
				size_t ok;
				ok        = num_bytes - error;
				addr      = (byte_t *)addr + ok;
				buf       = (byte_t *)buf + ok;
				num_bytes = error;
				if (pagedir_ismapped(addr)) {
					physaddr_t phys;
					size_t copybytes;
					phys      = pagedir_translate(addr);
					copybytes = PAGESIZE - ((uintptr_t)addr & PAGEMASK);
					if (copybytes > num_bytes)
						copybytes = num_bytes;
					copytophys(phys, buf, copybytes);
					if (copybytes >= num_bytes)
						return 0; /* Managed to copy everything */
					addr      = (byte_t *)addr + copybytes;
					buf       = (byte_t *)buf + copybytes;
					num_bytes -= copybytes;
					goto again_memcpy_nopf_kernel;
				}
			}
		}
		return error;
	}
	pdir = dbg_rt_getpagedir();
	if (!dbg_rt_verifypagedir(pdir))
		return num_bytes;
	PAGEDIR_P_BEGINUSE_KEEP_PR(pdir) {
again_memcpy_nopf:
		error = memcpy_nopf(addr, buf, num_bytes);
		if (error != 0) {
			if (ALLOW_MANAGED_MEMORY_ACCESS()) {
				struct mman *old_mm, *new_mm;
				size_t ok;
				NESTED_TRY {
					/* Re-validate   in   case  the   memcpy_nopf()  above
					 * changed something about dbg_current, or its fields. */
					if unlikely(!ADDR_ISKERN(dbg_current))
						goto done_nopanic_copy;
					new_mm = dbg_current->t_mman;
					if unlikely(!ADDR_ISKERN(new_mm))
						goto done_nopanic_copy;
					if (new_mm->mm_pagedir_p != pdir)
						goto done_nopanic_copy;
				} EXCEPT {
					goto done_nopanic_copy;
				}
				old_mm = THIS_MMAN;
				ok     = num_bytes - error;
				PERTASK_SET(this_mman, dbg_current->t_mman);
				NESTED_TRY {
					memcpy((byte_t *)buf + ok,
					       (byte_t const *)addr + ok,
					       error);
					/* If the memcpy() doesn't fail, then there isn't an error. */
					error = 0;
				} EXCEPT {
				}
				PERTASK_SET(this_mman, old_mm);
			}
done_nopanic_copy:
			if (force) {
				size_t ok;
				ok        = num_bytes - error;
				addr      = (byte_t *)addr + ok;
				buf       = (byte_t *)buf + ok;
				num_bytes = error;
				if (pagedir_ismapped(addr)) {
					physaddr_t phys;
					size_t copybytes;
					phys      = pagedir_translate(addr);
					copybytes = PAGESIZE - ((uintptr_t)addr & PAGEMASK);
					if (copybytes > num_bytes)
						copybytes = num_bytes;
					copytophys(phys, buf, copybytes);
					if (copybytes >= num_bytes)
						return 0; /* Managed to copy everything */
					addr      = (byte_t *)addr + copybytes;
					buf       = (byte_t *)buf + copybytes;
					num_bytes -= copybytes;
					goto again_memcpy_nopf;
				}
			}
		}
	}
	PAGEDIR_P_ENDUSE_KEEP_PR(pdir);
	return error;
}

PUBLIC size_t
NOTHROW(KCALL dbg_setmemory)(USER UNCHECKED void *addr, byte_t byte,
                             size_t num_bytes, bool force) {
	byte_t *buf;
	size_t buflen = num_bytes;
	if (buflen > 128)
		buflen = 128;
	buf = (byte_t *)alloca(buflen);
	memset(buf, byte, buflen);
	while (num_bytes) {
		size_t temp, error;
		temp = num_bytes;
		/* Limit the # of bytes written at once based on the local buffer size. */
		if (temp > buflen)
			temp = buflen;
		/* Account for what we intend to write. */
		num_bytes -= temp;
		/* Do the actual write. */
		error = dbg_writememory(addr, buf, temp, force);
		/* Account of write errors. */
		if unlikely(error != 0)
			return num_bytes + error;
		/* Advance the destination pointer. */
		addr = (byte_t *)addr + temp;
	}
	return 0;
}

/* Move memory from `src', and write it back to `dst' */
PUBLIC size_t
NOTHROW(KCALL dbg_movememory)(USER UNCHECKED void *dst,
                              USER UNCHECKED void const *src,
                              size_t num_bytes, bool force) {
	byte_t *buf;
	size_t buflen = num_bytes;
	if (buflen > 128)
		buflen = 128;
	buf = (byte_t *)alloca(buflen);
	if (dst <= src) {
		while (num_bytes) {
			size_t temp, error;
			temp = num_bytes;
			if (temp > buflen)
				temp = buflen;
			num_bytes -= temp;
			error = dbg_readmemory(src, buf, temp);
			if unlikely(error != 0)
				return num_bytes + error;
			error = dbg_writememory(dst, buf, temp, force);
			if unlikely(error != 0)
				return num_bytes + error;
			dst = (byte_t *)dst + temp;
			src = (byte_t *)src + temp;
		}
	} else {
		src = (byte_t *)src + num_bytes;
		dst = (byte_t *)dst + num_bytes;
		while (num_bytes) {
			size_t temp, error;
			temp = num_bytes;
			if (temp > buflen)
				temp = buflen;
			dst = (byte_t *)dst - temp;
			src = (byte_t *)src - temp;
			num_bytes -= temp;
			error = dbg_readmemory(src, buf, temp);
			if unlikely(error != 0)
				return num_bytes + error;
			error = dbg_writememory(dst, buf, temp, force);
			if unlikely(error != 0)
				return num_bytes + error;
		}
	}
	return 0;
}



DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_MEMORY_C */
