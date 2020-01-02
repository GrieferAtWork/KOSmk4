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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_RAND_H
#define GUARD_KERNEL_INCLUDE_KERNEL_RAND_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>

DECL_BEGIN

#ifdef __CC__

/* Generate and return a 32-bit, pseudo-random integer. */
FUNDEF NOBLOCK WUNUSED u32 NOTHROW(KCALL krand)(void);
LOCAL NOBLOCK WUNUSED u64 NOTHROW(KCALL krand64)(void) { return (u64)krand() | (u64)krand() << 32; }
FUNDEF NOBLOCK WUNUSED u32 NOTHROW(KCALL krand_r)(u32 *__restrict pseed);

#ifdef __INTELLISENSE__
FUNDEF NOBLOCK WUNUSED uintptr_t NOTHROW(KCALL krandptr)(void);
#elif __SIZEOF_POINTER__ <= 4
#define krandptr()   krand()
#else
#define krandptr()   krand64()
#endif

/* The current kernel seed. */
DATDEF WEAK u32 krand_seed;


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_RAND_H */
