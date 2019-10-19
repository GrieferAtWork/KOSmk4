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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_PERSONALITY_H
#define GUARD_KERNEL_INCLUDE_KERNEL_PERSONALITY_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <kos/personality.h>

DECL_BEGIN

#ifdef __CC__

/* Kernel personality bitmap */
DATDEF byte_t kernel_personality[(KP_COUNT + 7) / 8];

/* Check if the kernel has given personality enabled.
 * @param: name: One of `KP_*' (from <kos/personality.h>) */
#define has_kernel_personality(name) \
	((kernel_personality[(name) / 8] & (1 << ((name) % 8))) != 0)

/* Check if the calling process has a given personality enabled.
 * @param: name: One of `KP_*' (from <kos/personality.h>) */
#define has_personality(name) \
	has_kernel_personality(name)

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_PERSONALITY_H */
