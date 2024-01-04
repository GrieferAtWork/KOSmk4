/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_RAND_H
#define GUARD_KERNEL_INCLUDE_KERNEL_RAND_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>

#ifdef __CC__
DECL_BEGIN

/* Generate and return a 32-bit, pseudo-random integer. */
FUNDEF NOBLOCK WUNUSED ATTR_LEAF u32
NOTHROW(KCALL krand32)(void);

/* Same as `krand32()', but use `*pseed' instead of `krand_seed'
 * WARNING: Unlike `krand32()', `*pseed' is _NOT_ modified atomically!
 *          This means that `krand32_r(&krand_seed)' is _NOT_ equal to
 *          a call to `krand32()', since the call would result in weak
 *          undefined behavior when  called from  multiple threads  at
 *          the same time */
FUNDEF NOBLOCK WUNUSED ATTR_LEAF NONNULL((1)) u32
NOTHROW(KCALL krand32_r)(u32 *__restrict pseed);

LOCAL NOBLOCK WUNUSED ATTR_LEAF u64 NOTHROW(KCALL krand64)(void) {
	return (u64)krand32() | (u64)krand32() << 32;
}

/* Produce a pointer-sized random number. */
#ifdef __INTELLISENSE__
FUNDEF NOBLOCK WUNUSED uintptr_t NOTHROW(KCALL krand)(void);
#elif __SIZEOF_POINTER__ <= 4
#define krand() krand32()
#else /* ... */
#define krand() krand64()
#endif /* !... */

/* Produce a random number with at least as many bits as also found in `T' */
#ifdef __NO_builtin_choose_expr
#define KRAND(T) (sizeof(T) <= 4 ? krand32() : krand64())
#else /* __NO_builtin_choose_expr */
#define KRAND(T) __builtin_choose_expr(sizeof(T) <= 4, krand32(), krand64())
#endif /* !__NO_builtin_choose_expr */

/* The current kernel seed. (modified by `krand(|32|64)') */
DATDEF WEAK u32 krand_seed;

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_RAND_H */
