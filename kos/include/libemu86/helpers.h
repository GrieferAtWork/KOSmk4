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
#ifndef _LIBEMU86_HELPERS_H
#define _LIBEMU86_HELPERS_H 1

#include "api.h"

#include <bits/types.h>
#include <i386-kos/asm/cpu-flags.h>

/* Misc. helper functions */
#ifdef __CC__
__DECL_BEGIN

#define EMU86_DEFINE_TZCNT(bwlq, Nbits)                                                       \
	__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((2)) unsigned int                                   \
	__NOTHROW(LIBEMU86_CC emu86_tzcnt##bwlq)(__uint##Nbits##_t i,                             \
	                                         /*out:CF|ZF*/ __uint32_t * __restrict peflags) { \
		unsigned int result    = 0;                                                           \
		__uint##Nbits##_t mask = 1;                                                           \
		*peflags               = 0;                                                           \
		if (!i)                                                                               \
			*peflags |= EFLAGS_CF;                                                            \
		for (; !((__uint##Nbits##_t)(i)&mask) && result < Nbits;                              \
		     mask <<= 1, ++result)                                                            \
			;                                                                                 \
		if (!result)                                                                          \
			*peflags |= EFLAGS_ZF;                                                            \
		return result;                                                                        \
	}

#define EMU86_DEFINE_LZCNT(bwlq, Nbits)                                                       \
	__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((2)) unsigned int                                   \
	__NOTHROW(LIBEMU86_CC emu86_lzcnt##bwlq)(__uint##Nbits##_t i,                             \
	                                         /*out:CF|ZF*/ __uint32_t * __restrict peflags) { \
		unsigned int result    = 0;                                                           \
		__uint##Nbits##_t mask = (__uint##Nbits##_t)1 << (Nbits - 1);                         \
		*peflags               = 0;                                                           \
		if (!i)                                                                               \
			*peflags |= EFLAGS_CF;                                                            \
		for (; !((__uint##Nbits##_t)(i)&mask) && mask;                                        \
		     mask >>= 1, ++result)                                                            \
			;                                                                                 \
		if (!result)                                                                          \
			*peflags |= EFLAGS_ZF;                                                            \
		return result;                                                                        \
	}

EMU86_DEFINE_TZCNT(b, 8)
EMU86_DEFINE_TZCNT(w, 16)
EMU86_DEFINE_TZCNT(l, 32)
EMU86_DEFINE_LZCNT(b, 8)
EMU86_DEFINE_LZCNT(w, 16)
EMU86_DEFINE_LZCNT(l, 32)
#if CONFIG_LIBEMU86_WANT_64BIT
EMU86_DEFINE_TZCNT(q, 64)
EMU86_DEFINE_LZCNT(q, 64)
#endif /* CONFIG_LIBEMU86_WANT_64BIT */

#undef EMU86_DEFINE_LZCNT
#undef EMU86_DEFINE_TZCNT

__DECL_END
#endif /* __CC__ */


#endif /* !_LIBEMU86_HELPERS_H */
