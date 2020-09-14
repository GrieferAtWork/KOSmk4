/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
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
#ifndef GUARD_KERNEL_SRC_DEBUGGER_MEMORY_C
#define GUARD_KERNEL_SRC_DEBUGGER_MEMORY_C 1
#define DISABLE_BRANCH_PROFILING 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER
#include <debugger/hook.h>
#include <debugger/rt.h>
#include <kernel/paging.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>

#include <hybrid/align.h>

#include <string.h>

DECL_BEGIN


/* Return the page directory of `dbg_current' */
PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_getpagedir")
ATTR_PURE WUNUSED pagedir_phys_t
NOTHROW(KCALL dbg_getpagedir)(void) {
	struct vm *v;
	if (!dbg_current)
		goto fallback;
	v = dbg_current->t_vm;
	if (!v)
		goto fallback;
	return v->v_pdir_phys;
fallback:
	return pagedir_kernel_phys;
}

/* Verify that the given page directory isn't corrupt. */
PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_verifypagedir") ATTR_PURE WUNUSED bool
NOTHROW(KCALL dbg_verifypagedir)(pagedir_phys_t pdir) {
#if PAGEDIR_ALIGN > 1
	if (!IS_ALIGNED((uintptr_t)pdir, PAGEDIR_ALIGN))
		return false; /* Badly aligned. */
#endif /* PAGEDIR_ALIGN > 1 */
	/* XXX: Additional (probably arch-specific) checks. */
	COMPILER_IMPURE();
	return true;
}



#ifdef __INTELLISENSE__
#define PAGEDIR_P_BEGIN(self) do
#define PAGEDIR_P_END(self)   __WHILE0
#else /* __INTELLISENSE__ */
#define PAGEDIR_P_BEGIN(self)                                 \
	do {                                                      \
		pagedir_phys_t _old_pdir;                         \
		pflag_t _p_was = PREEMPTION_PUSHOFF();                \
		assert(IS_ALIGNED((uintptr_t)(self), PAGEDIR_ALIGN)); \
		_old_pdir = pagedir_get();                            \
		if (_old_pdir != (self))                              \
			pagedir_set(self);                                \
		do
#define PAGEDIR_P_END(self)         \
		__WHILE0;                   \
		if (_old_pdir != (self))    \
			pagedir_set(_old_pdir); \
		PREEMPTION_POP(_p_was);     \
	} __WHILE0
#endif /* !__INTELLISENSE__ */


/* Get/set memory in the context of `dbg_current'
 * NOTE: These functions will not make use of copy-on-write or lazy memory allocations,
 *       but will instead indicate an error, or (in when `force' is true), write directly
 *       to the physical memory backing of the underlying page directory.
 * @return: * : The number of trailing bytes that could not be copied. */
PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_readmemory") size_t
NOTHROW(KCALL dbg_readmemory)(void const *addr,
                              void *__restrict buf,
                              size_t num_bytes) {
	size_t error;
	pagedir_phys_t pdir;
	if (ADDRRANGE_ISKERN(addr, (byte_t *)addr + num_bytes))
		return memcpy_nopf(buf, addr, num_bytes);
	pdir = dbg_getpagedir();
	if (!dbg_verifypagedir(pdir))
		return num_bytes;
	PAGEDIR_P_BEGINUSE(pdir) {
		error = memcpy_nopf(buf, addr, num_bytes);
	}
	PAGEDIR_P_ENDUSE(pdir);
	return error;
}

PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_writememory") size_t
NOTHROW(KCALL dbg_writememory)(void *addr,
                               void const *__restrict buf,
                               size_t num_bytes, bool force) {
	size_t error;
	pagedir_phys_t pdir;
	if (!num_bytes)
		return 0; /* Nothing to do here. */
	if (ADDRRANGE_ISKERN(addr, (byte_t *)addr + num_bytes)) {
again_memcpy_nopf_kernel:
		error = memcpy_nopf(addr, buf, num_bytes);
		if (error != 0 && force) {
			size_t okcount;
			okcount   = num_bytes - error;
			addr      = (byte_t *)addr + okcount;
			buf       = (byte_t *)buf + okcount;
			num_bytes = error;
			if (pagedir_ismapped(addr)) {
				physaddr_t phys;
				size_t copybytes;
				phys      = pagedir_translate(addr);
				copybytes = PAGESIZE - ((uintptr_t)addr & PAGEMASK);
				if (copybytes > num_bytes)
					copybytes = num_bytes;
				vm_copytophys(phys, buf, copybytes);
				if (copybytes >= num_bytes)
					return 0; /* Managed to copy everything */
				addr      = (byte_t *)addr + copybytes;
				buf       = (byte_t *)buf + copybytes;
				num_bytes -= copybytes;
				goto again_memcpy_nopf_kernel;
			}
		}
		return error;
	}
	pdir = dbg_getpagedir();
	if (!dbg_verifypagedir(pdir))
		return num_bytes;
again_memcpy_nopf:
	PAGEDIR_P_BEGINUSE(pdir) {
		error = memcpy_nopf(addr, buf, num_bytes);
	}
	PAGEDIR_P_ENDUSE(pdir);
	if (error != 0 && force) {
		size_t okcount;
		okcount   = num_bytes - error;
		addr      = (byte_t *)addr + okcount;
		buf       = (byte_t *)buf + okcount;
		num_bytes = error;
		if (pagedir_ismapped_p(pdir, addr)) {
			physaddr_t phys;
			size_t copybytes;
			phys      = pagedir_translate_p(pdir, addr);
			copybytes = PAGESIZE - ((uintptr_t)addr & PAGEMASK);
			if (copybytes > num_bytes)
				copybytes = num_bytes;
			vm_copytophys(phys, buf, copybytes);
			if (copybytes >= num_bytes)
				return 0; /* Managed to copy everything */
			addr      = (byte_t *)addr + copybytes;
			buf       = (byte_t *)buf + copybytes;
			num_bytes -= copybytes;
			goto again_memcpy_nopf;
		}
	}
	return error;
}


DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_MEMORY_C */
