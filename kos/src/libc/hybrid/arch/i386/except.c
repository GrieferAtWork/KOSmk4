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
#ifndef GUARD_LIBC_HYBRID_ARCH_I386_EXCEPT_C
#define GUARD_LIBC_HYBRID_ARCH_I386_EXCEPT_C 1

#include <hybrid/compiler.h>

#include <hybrid/host.h>

/**/
#include "except.h"

#if defined(__KERNEL__) || defined(__INTELLISENSE__)
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

DECL_BEGIN

struct icpustate;

INTERN ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL x86_except_badusage_throw_current_icpustate)(struct icpustate const *__restrict state) {
	struct kcpustate kst;
	icpustate_to_kcpustate(state, &kst);
	libc_except_badusage_throw_current(&kst);
}

DECL_END
#endif /* __KERNEL__ */

#endif /* !GUARD_LIBC_HYBRID_ARCH_I386_EXCEPT_C */
