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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUG_MALLOC_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUG_MALLOC_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/driver-param.h>

#if defined(CONFIG_DEBUG_MALLOC) || defined(CONFIG_DEBUG_HEAP)
DECL_BEGIN

PRIVATE ATTR_FREETEXT void KCALL inject_jmp(void *from, void *to) {
	if (from == to)
		return; /* Ignore. */
	*((byte_t *)from + 0) = 0xe9;
	*(s32 *)((byte_t *)from + 1) = (s32)((byte_t *)to - ((byte_t *)from + 5));
}

PRIVATE ATTR_FREETEXT void KCALL inject_ret(void *at, u16 n_bytes) {
	(void)n_bytes;
#ifndef __x86_64__
	if (n_bytes != 0) {
		*((byte_t *)at + 0)        = 0xc2;
		*(u16 *)((byte_t *)at + 1) = n_bytes;
	} else
#endif /* !__x86_64__ */
	{
		*((byte_t *)at + 0) = 0xc3;
	}
}

struct lcpustate;
INTDEF ATTR_WEAK void
NOTHROW(KCALL debug_malloc_generate_traceback)(void **__restrict buffer, size_t buflen,
                                               struct lcpustate *__restrict state);

PRIVATE void
NOTHROW(KCALL noop_generate_traceback)(void **__restrict buffer, size_t buflen,
                                       struct lcpustate *__restrict UNUSED(state)) {
	if (buflen)
		*buffer = NULL;
}


INTERN ATTR_FREETEXT void KCALL
kernel_disable_debug_malloc(void) {

	/* `heap_validate_all()' takes up quite a bit of execution time, since
	 * it has to scan a whole bunch of memory for potential faults.
	 * By overriding it to become a no-op, we can speed up execution time
	 * of kernel builds with this feature enabled by quite a lot. */
	inject_ret((void *)&heap_validate_all, 0);
	inject_ret((void *)&heap_validate, 4);

	/* The generate-traceback function used by debug_malloc to store a small
	 * portion of the backtrace associated with any given allocation is the
	 * other major factor when it comes to the getting rid of the slow-down
	 * associated with mall debugging enabled.
	 * If that function as defined (we check for this by weakly linking it),
	 * then redirect it against a no-op traceback generator function. */
	if (debug_malloc_generate_traceback) {
		inject_jmp((void *)&debug_malloc_generate_traceback,
		           (void *)&noop_generate_traceback);
	}
}

DEFINE_VERY_EARLY_KERNEL_COMMANDLINE_OPTION(kernel_disable_debug_malloc,
                                            KERNEL_COMMANDLINE_OPTION_TYPE_PRESENT,
                                            "nomall");


DECL_END

#endif /* CONFIG_DEBUG_MALLOC || CONFIG_DEBUG_HEAP */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUG_MALLOC_C */
