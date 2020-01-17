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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_ILLEGAL_INSTRUCTION_BITOPS_H
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_ILLEGAL_INSTRUCTION_BITOPS_H 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <asm/cpu-flags.h>

#define CF EFLAGS_CF
#define PF EFLAGS_PF
#define AF EFLAGS_AF
#define ZF EFLAGS_ZF
#define SF EFLAGS_SF
#define TF EFLAGS_TF
#define IF EFLAGS_IF
#define DF EFLAGS_DF
#define OF EFLAGS_OF

DECL_BEGIN

/* NOTE: Sadly, we can't just use <hybrid/bit.h> functions, since
 *       those themself may have been linked to make use of the
 *       very instructions which we're trying to emulate... */
#define DEFINE_POPCOUNT(n, T)                                                \
	LOCAL ATTR_LEAF unsigned int                                             \
	NOTHROW(KCALL simple_popcnt##n)(T i, uintptr_t *__restrict pflags) {     \
		unsigned int result = 0;                                             \
		T mask              = 1;                                             \
		*pflags &= ~(OF | SF | ZF | AF | CF | PF | ZF);                      \
		if (!i)                                                              \
			*pflags |= ZF;                                                   \
		for (;; mask <<= 1) {                                                \
			if (((T)i) & mask)                                               \
				++result;                                                    \
			if (!(mask < (T)i && !(mask & ((T)1 << ((sizeof(T) * 8) - 1))))) \
				break;                                                       \
		}                                                                    \
		return result;                                                       \
	}
#define DEFINE_TZCOUNT(n, T)                                                     \
	LOCAL ATTR_LEAF unsigned int                                                 \
	NOTHROW(KCALL simple_tzcnt##n)(T i, uintptr_t *__restrict pflags) {          \
		unsigned int result = 0;                                                 \
		T mask              = 1;                                                 \
		*pflags &= ~(CF | ZF);                                                   \
		if (!i)                                                                  \
			*pflags |= CF;                                                       \
		for (; !((T)(i)&mask) && result < (sizeof(T) * 8); mask <<= 1, ++result) \
			;                                                                    \
		if (!result)                                                             \
			*pflags |= ZF;                                                       \
		return result;                                                           \
	}
#define DEFINE_LZCOUNT(n, T)                                            \
	LOCAL ATTR_LEAF unsigned int                                        \
	NOTHROW(KCALL simple_lzcnt##n)(T i, uintptr_t *__restrict pflags) { \
		unsigned int result = 0;                                        \
		T mask = (T)1 << ((sizeof(T) * 8) - 1);                         \
		*pflags &= ~(CF | ZF);                                          \
		if (!i)                                                         \
			*pflags |= CF;                                              \
		for (; !((T)(i)&mask) && mask; mask >>= 1, ++result)            \
			;                                                           \
		if (!result)                                                    \
			*pflags |= ZF;                                              \
		return result;                                                  \
	}


/*DEFINE_POPCOUNT(8, u8)*/
DEFINE_POPCOUNT(16, u16)
DEFINE_POPCOUNT(32, u32)
/*DEFINE_TZCOUNT(8, u8)*/
DEFINE_TZCOUNT(16, u16)
DEFINE_TZCOUNT(32, u32)
/*DEFINE_LZCOUNT(8, u8)*/
DEFINE_LZCOUNT(16, u16)
DEFINE_LZCOUNT(32, u32)

#ifdef __x86_64__
DEFINE_POPCOUNT(64, u64)
DEFINE_TZCOUNT(64, u64)
DEFINE_LZCOUNT(64, u64)
#endif /* __x86_64__ */

#undef DEFINE_LZCOUNT
#undef DEFINE_TZCOUNT
#undef DEFINE_POPCOUNT

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_ILLEGAL_INSTRUCTION_BITOPS_H */
