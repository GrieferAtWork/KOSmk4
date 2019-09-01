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
#ifndef _I386_KOS_ASM_INTRIN_SEGARITH_H
#define _I386_KOS_ASM_INTRIN_SEGARITH_H 1

#include <__stdinc.h>
#include <hybrid/host.h>
#include <hybrid/__atomic.h>
#include <hybrid/typecore.h>

/* Segment-relative arithmetic */

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __x86_64__
#define __INTRIN_LOCK_IF_X86_64(...) __VA_ARGS__
#else /* __x86_64__ */
#define __INTRIN_LOCK_IF_X86_64(...) /* nothing */
#endif /* !__x86_64__ */


#define __DEFINE_ARTH_UNARY_SEG(name, seg) \
	__FORCELOCAL void (__##name##seg##b)(__ULONGPTR_TYPE__ __offset) { \
		__asm__(#name "b %%" #seg ":%b0"                               \
		        :                                                      \
		        : "m" (*(__UINT8_TYPE__ *)__offset)                    \
		        : "cc", "memory");                                     \
	}                                                                  \
	__FORCELOCAL void (__##name##seg##w)(__ULONGPTR_TYPE__ __offset) { \
		__asm__(#name "w %%" #seg ":%w0"                               \
		        :                                                      \
		        : "m" (*(__UINT16_TYPE__ *)__offset)                   \
		        : "cc", "memory");                                     \
	}                                                                  \
	__FORCELOCAL void (__##name##seg##l)(__ULONGPTR_TYPE__ __offset) { \
		__asm__(#name "l %%" #seg ":%k0"                               \
		        :                                                      \
		        : "m" (*(__UINT32_TYPE__ *)__offset)                   \
		        : "cc", "memory");                                     \
	}
#define __DEFINE_ARTH_BINARY_SEG(name, seg) \
	__FORCELOCAL void (__##name##seg##b)(__ULONGPTR_TYPE__ __offset, __UINT8_TYPE__ __val) {  \
		__asm__(#name "b %%" #seg ":%b1, %b0"                                                 \
		        :                                                                             \
		        : "m" (*(__UINT8_TYPE__ *)__offset), "q" (__val)                              \
		        : "cc", "memory");                                                            \
	}                                                                                         \
	__FORCELOCAL void (__##name##seg##w)(__ULONGPTR_TYPE__ __offset, __UINT16_TYPE__ __val) { \
		__asm__(#name "w %%" #seg ":%w1, %w0"                                                 \
		        :                                                                             \
		        : "m" (*(__UINT16_TYPE__ *)__offset), "r" (__val)                             \
		        : "cc", "memory");                                                            \
	}                                                                                         \
	__FORCELOCAL void (__##name##seg##l)(__ULONGPTR_TYPE__ __offset, __UINT32_TYPE__ __val) { \
		__asm__(#name "l %%" #seg ":%k1, %k0"                                                 \
		        :                                                                             \
		        : "m" (*(__UINT32_TYPE__ *)__offset), "r" (__val)                             \
		        : "cc", "memory");                                                            \
	}
#define __DEFINE_WITH_SEGMENTS(callback, name) \
	callback(name, ds) \
	callback(name, es) \
	callback(name, fs) \
	callback(name, gs) \
	callback(name, cs) \
	callback(name, ss)
__DEFINE_WITH_SEGMENTS(__DEFINE_ARTH_BINARY_SEG, add)
__DEFINE_WITH_SEGMENTS(__DEFINE_ARTH_BINARY_SEG, sub)
__DEFINE_WITH_SEGMENTS(__DEFINE_ARTH_UNARY_SEG, inc)
__DEFINE_WITH_SEGMENTS(__DEFINE_ARTH_UNARY_SEG, dec)
#undef __DEFINE_ARTH_BINARY_SEG
#undef __DEFINE_ARTH_UNARY_SEG
#undef __INTRIN_LOCK_IF_X86_64

__SYSDECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_ASM_INTRIN_SEGARITH_H */
