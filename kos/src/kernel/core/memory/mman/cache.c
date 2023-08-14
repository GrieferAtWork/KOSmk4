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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_CACHE_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_CACHE_C 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/mman/cache.h>
#include <kernel/mman/cc.h>

/* TODO: EVERYTHING IN HERE IS DEPRECATED! (use <kernel/mman/cc.h> instead) */

DECL_BEGIN

PUBLIC NOBLOCK size_t
NOTHROW(KCALL syscache_clear)(void) {
	struct ccinfo cci;
	ccinfo_init(&cci, GFP_ATOMIC, 0);
	if (system_cc(&cci) && cci.ci_bytes == 0)
		cci.ci_bytes = 1;
	return cci.ci_bytes;
}

PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(KCALL syscache_clear_s)(syscache_version_t *__restrict pversion) {
	struct ccinfo cci;
	ccinfo_init(&cci, GFP_ATOMIC, 0);
	cci._ci_state = *pversion;
	if (system_cc(&cci) && cci.ci_bytes == 0)
		cci.ci_bytes = 1;
	*pversion = cci._ci_state;
	return cci.ci_bytes;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_CACHE_C */
