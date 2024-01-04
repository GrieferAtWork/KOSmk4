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
#ifndef _I386_KOS_OPTIMIZED_STRING_H
#define _I386_KOS_OPTIMIZED_STRING_H 1

#include <__stdinc.h>
#include <__crt.h>

/* Platform-dependent, optimized string.h functions. */
#if !defined(__NO_ATTR_FORCEINLINE) && \
    !defined(__NO_builtin_constant_p)
#include <hybrid/host.h>
#ifndef _LIBC_CORE_STRING_H
#include <libc/core/string.h>
#endif /* !_LIBC_CORE_STRING_H */
#ifndef __COMPILER_HAVE_GCC_ASM
#include <asm/intrin.h>
#endif /* !__COMPILER_HAVE_GCC_ASM */

#ifndef __COMPILER_ASM_BUFFER
#define __COMPILER_ASM_BUFFER(T, s, p) (*(T *)(p))
#endif /* !__COMPILER_ASM_BUFFER */


__SYSDECL_BEGIN
__NAMESPACE_FAST_BEGIN

#ifndef __ASSERT_MEMCPY_CT
#if !defined(NDEBUG) && 0 /* Doesn't work... */
extern __ATTR_ERROR("memcpy(): The `dst' and `src' buffers overlap - Use `memmove()' instead") void __memcpy_overlapping_buffers(void);
/* Compile-time overlap assertions */
#define __ASSERT_MEMCPY_CT_DOES_OVERLAP(dst, src, num_bytes) \
	((dst) + (num_bytes) > (src) &&                          \
	 (src) + (num_bytes) > (dst))
#define __ASSERT_MEMCPY_CT(dst, src, num_bytes)                                                 \
	if __untraced(__builtin_constant_p(__ASSERT_MEMCPY_CT_DOES_OVERLAP(dst, src, num_bytes)) && \
	              __ASSERT_MEMCPY_CT_DOES_OVERLAP(dst, src, num_bytes))                         \
		__memcpy_overlapping_buffers()
#else /* !NDEBUG */
#define __ASSERT_MEMCPY_CT(dst, src, num_bytes) /* nothing */
#endif /* NDEBUG */
#endif /* !__ASSERT_MEMCPY_CT */


#define __fast_memcpy_defined
/* Copy memory between non-overlapping memory blocks. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBC_FAST_NAME(memcpy))(void *__restrict __dst,
                                        void const *__restrict __src,
                                        __SIZE_TYPE__ __n_bytes) {
	__ASSERT_MEMCPY_CT(__dst, __src, __n_bytes);
#if 1 /* Work-around for a weird GCC-bug... */
	if __untraced(__builtin_constant_p(__n_bytes * 2))
#else
	if __untraced(__builtin_constant_p(__n_bytes))
#endif
	{
		switch (__n_bytes) {

		case 0:
			return __dst;

		case 1:
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			return __dst;

		case 2:
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return __dst;

		case 3:
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[2] = ((__UINT8_TYPE__ const *)__src)[2];
			return __dst;

		case 4:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return __dst;

		case 5:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[4] = ((__UINT8_TYPE__ const *)__src)[4];
			return __dst;

		case 6:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			return __dst;

#ifdef __x86_64__
		case 8:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;

		case 9:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[8] = ((__UINT8_TYPE__ const *)__src)[8];
			return __dst;

		case 10:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			return __dst;

		case 12:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return __dst;

		case 16:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			return __dst;
#else /* __x86_64__ */
		case 8:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return __dst;
#endif /* !__x86_64__ */
		default:
			break;
		}
#ifdef __COMPILER_HAVE_GCC_ASM
		{
			__register __ULONGPTR_TYPE__ __386_esi = (__ULONGPTR_TYPE__)__src;
			__register __ULONGPTR_TYPE__ __386_edi = (__ULONGPTR_TYPE__)__dst;
#ifdef __x86_64__
			if __untraced(__n_bytes >= 5 * 8) {
				__register __ULONGPTR_TYPE__ __386_ecx;
				__asm__ __volatile__(
#ifdef __KERNEL__
				                     "cld\n\t"
#endif /* __KERNEL__ */
				                     "rep; movsq\n\t"
				                     ".if (%a8 & 4)\n\t"
				                     "movsl\n\t"
				                     ".endif\n\t"
				                     ".if (%a8 & 2)\n\t"
				                     "movsw\n\t"
				                     ".endif\n\t"
				                     ".if (%a8 & 1)\n\t"
				                     "movsb\n\t"
				                     ".endif"
				                     : "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __n_bytes, __dst))
				                     , "=&c" (__386_ecx)
				                     , "=&D" (__386_edi)
				                     , "=&S" (__386_esi)
				                     : "m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __n_bytes, __src))
				                     , "1" (__n_bytes >> 3)
				                     , "2" (__386_edi)
				                     , "3" (__386_esi)
#if 1 /* Work-around for GCC bug */
				                     , "X" (__n_bytes)
#else
				                     , "i" (__n_bytes)
#endif
				                     );
			} else {
				__asm__ __volatile__(
#ifdef __KERNEL__
				                     "cld\n\t"
#endif /* __KERNEL__ */
				                     ".if (%a6 >= 32)\n\t"
				                     "movsq\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 >= 24)\n\t"
				                     "movsq\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 >= 16)\n\t"
				                     "movsq\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 >= 8)\n\t"
				                     "movsq\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 & 4)\n\t"
				                     "movsl\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 & 2)\n\t"
				                     "movsw\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 & 1)\n\t"
				                     "movsb\n\t"
				                     ".endif"
				                     : "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __n_bytes, __dst))
				                     , "=&D" (__386_edi)
				                     , "=&S" (__386_esi)
				                     : "m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __n_bytes, __src))
				                     , "1" (__386_edi)
				                     , "2" (__386_esi)
#if 1 /* Work-around for GCC bug */
				                     , "X" (__n_bytes)
#else
				                     , "i" (__n_bytes)
#endif
				                     );
			}
#else /* __x86_64__ */
			if __untraced(__n_bytes >= 5 * 4) {
				__register __ULONGPTR_TYPE__ __386_ecx;
				__asm__ __volatile__(
#ifdef __KERNEL__
				                     "cld\n\t"
#endif /* __KERNEL__ */
				                     "rep; movsl\n\t"
				                     ".if (%a8 & 2)\n\t"
				                     "movsw\n\t"
				                     ".endif\n\t"
				                     ".if (%a8 & 1)\n\t"
				                     "movsb\n\t"
				                     ".endif"
				                     : "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __n_bytes, __dst))
				                     , "=&c" (__386_ecx)
				                     , "=&D" (__386_edi)
				                     , "=&S" (__386_esi)
				                     : "m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __n_bytes, __src))
				                     , "1" (__n_bytes >> 2)
				                     , "2" (__386_edi)
				                     , "3" (__386_esi)
#if 1 /* Work-around for GCC bug */
				                     , "X" (__n_bytes)
#else
				                     , "i" (__n_bytes)
#endif
				                     );
			} else {
				__asm__ __volatile__(
#ifdef __KERNEL__
				                     "cld\n\t"
#endif /* __KERNEL__ */
				                     ".if (%a6 >= 16)\n\t"
				                     "movsl\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 >= 12)\n\t"
				                     "movsl\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 >= 8)\n\t"
				                     "movsl\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 >= 4)\n\t"
				                     "movsl\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 & 2)\n\t"
				                     "movsw\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 & 1)\n\t"
				                     "movsb\n\t"
				                     ".endif"
				                     : "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __n_bytes, __dst))
				                     , "=&D" (__386_edi)
				                     , "=&S" (__386_esi)
				                     : "m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __n_bytes, __src))
				                     , "1" (__386_edi)
				                     , "2" (__386_esi)
#if 1 /* Work-around for GCC bug */
				                     , "X" (__n_bytes)
#else
				                     , "i" (__n_bytes)
#endif
				                     );
			}
#endif /* !__x86_64__ */
			return __dst;
		}
#else /* __COMPILER_HAVE_GCC_ASM */
		/* XXX: Implement using intrinsic functions? */
#endif /* !__COMPILER_HAVE_GCC_ASM */
	}
	return __libc_core_memcpy(__dst, __src, __n_bytes);
}

#define __fast_mempcpy_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempcpy))(void *__restrict __dst,
                                         void const *__restrict __src,
                                         __SIZE_TYPE__ __n_bytes) {
	__ASSERT_MEMCPY_CT(__dst, __src, __n_bytes);
#if 1 /* Work-around for a weird GCC-bug... */
	if __untraced(__builtin_constant_p(__n_bytes * 2))
#else
	if __untraced(__builtin_constant_p(__n_bytes))
#endif
	{
		switch (__n_bytes) {

		case 0:
			return __dst;

		case 1:
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 1;

		case 2:
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 2;

		case 3:
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[2] = ((__UINT8_TYPE__ const *)__src)[2];
			return (__UINT8_TYPE__ *)__dst + 3;

		case 4:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 4;

		case 5:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[4] = ((__UINT8_TYPE__ const *)__src)[4];
			return (__UINT8_TYPE__ *)__dst + 5;

		case 6:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			return (__UINT8_TYPE__ *)__dst + 6;

#ifdef __x86_64__
		case 8:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 8;

		case 9:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[8] = ((__UINT8_TYPE__ const *)__src)[8];
			return (__UINT8_TYPE__ *)__dst + 9;

		case 10:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			return (__UINT8_TYPE__ *)__dst + 10;

		case 12:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT8_TYPE__ *)__dst + 12;

		case 16:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			return (__UINT8_TYPE__ *)__dst + 16;
#else /* __x86_64__ */
		case 8:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return (__UINT8_TYPE__ *)__dst + 8;
#endif /* !__x86_64__ */

		default:
			break;
		}
#ifdef __COMPILER_HAVE_GCC_ASM
		{
			__register __ULONGPTR_TYPE__ __386_esi = (__ULONGPTR_TYPE__)__src;
			__register __ULONGPTR_TYPE__ __386_edi = (__ULONGPTR_TYPE__)__dst;
#ifdef __x86_64__
			if __untraced(__n_bytes >= 5 * 8) {
				__register __ULONGPTR_TYPE__ __386_ecx;
				__asm__ __volatile__(
#ifdef __KERNEL__
				                     "cld\n\t"
#endif /* __KERNEL__ */
				                     "rep; movsq\n\t"
				                     ".if (%a8 & 4)\n\t"
				                     "movsl\n\t"
				                     ".endif\n\t"
				                     ".if (%a8 & 2)\n\t"
				                     "movsw\n\t"
				                     ".endif\n\t"
				                     ".if (%a8 & 1)\n\t"
				                     "movsb\n\t"
				                     ".endif"
				                     : "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __n_bytes, __dst))
				                     , "=&c" (__386_ecx)
				                     , "=&D" (__386_edi)
				                     , "=&S" (__386_esi)
				                     : "m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __n_bytes, __src))
				                     , "1" (__n_bytes >> 3)
				                     , "2" (__386_edi)
				                     , "3" (__386_esi)
#if 1 /* Work-around for GCC bug */
				                     , "X" (__n_bytes)
#else
				                     , "i" (__n_bytes)
#endif
				                     );
			} else {
				__asm__ __volatile__(
#ifdef __KERNEL__
				                     "cld\n\t"
#endif /* __KERNEL__ */
				                     ".if (%a6 >= 32)\n\t"
				                     "movsq\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 >= 24)\n\t"
				                     "movsq\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 >= 16)\n\t"
				                     "movsq\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 >= 8)\n\t"
				                     "movsq\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 & 4)\n\t"
				                     "movsl\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 & 2)\n\t"
				                     "movsw\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 & 1)\n\t"
				                     "movsb\n\t"
				                     ".endif"
				                     : "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __n_bytes, __dst))
				                     , "=&D" (__386_edi)
				                     , "=&S" (__386_esi)
				                     : "m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __n_bytes, __src))
				                     , "1" (__386_edi)
				                     , "2" (__386_esi)
#if 1 /* Work-around for GCC bug */
				                     , "X" (__n_bytes)
#else
				                     , "i" (__n_bytes)
#endif
				                     );
			}
#else /* __x86_64__ */
			if __untraced(__n_bytes >= 5 * 4) {
				__register __ULONGPTR_TYPE__ __386_ecx;
				__asm__ __volatile__(
#ifdef __KERNEL__
				                     "cld\n\t"
#endif /* __KERNEL__ */
				                     "rep; movsl\n\t"
				                     ".if (%a8 & 2)\n\t"
				                     "movsw\n\t"
				                     ".endif\n\t"
				                     ".if (%a8 & 1)\n\t"
				                     "movsb\n\t"
				                     ".endif"
				                     : "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __n_bytes, __dst))
				                     , "=&c" (__386_ecx)
				                     , "=&D" (__386_edi)
				                     , "=&S" (__386_esi)
				                     : "m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __n_bytes, __src))
				                     , "1" (__n_bytes >> 2)
				                     , "2" (__386_edi)
				                     , "3" (__386_esi)
#if 1 /* Work-around for GCC bug */
				                     , "X" (__n_bytes)
#else
				                     , "i" (__n_bytes)
#endif
				                     );
			} else {
				__asm__ __volatile__(
#ifdef __KERNEL__
				                     "cld\n\t"
#endif /* __KERNEL__ */
				                     ".if (%a6 >= 16)\n\t"
				                     "movsl\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 >= 12)\n\t"
				                     "movsl\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 >= 8)\n\t"
				                     "movsl\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 >= 4)\n\t"
				                     "movsl\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 & 2)\n\t"
				                     "movsw\n\t"
				                     ".endif\n\t"
				                     ".if (%a6 & 1)\n\t"
				                     "movsb\n\t"
				                     ".endif"
				                     : "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __n_bytes, __dst))
				                     , "=&D" (__386_edi)
				                     , "=&S" (__386_esi)
				                     : "m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __n_bytes, __src))
				                     , "1" (__386_edi)
				                     , "2" (__386_esi)
#if 1 /* Work-around for GCC bug */
				                     , "X" (__n_bytes)
#else
				                     , "i" (__n_bytes)
#endif
				                     );
			}
#endif /* !__x86_64__ */
			__builtin_assume(__386_edi == (__ULONGPTR_TYPE__)__dst + __n_bytes);
			return (void *)__386_edi;
		}
#else /* __COMPILER_HAVE_GCC_ASM */
		/* XXX: Implement using intrinsic functions? */
#endif /* !__COMPILER_HAVE_GCC_ASM */
	}
	return __libc_core_mempcpy(__dst, __src, __n_bytes);
}

/* TODO: memcpy[w/l/q] */
/* TODO: mempcpy[w/l/q] */

__NAMESPACE_FAST_END
__SYSDECL_END

#ifdef __PREPROCESSOR_HAVE_INCLUDE_NEXT
#include_next <optimized/string.h>
#else /* __PREPROCESSOR_HAVE_INCLUDE_NEXT */
#include "../../optimized/string.h"
#endif /* !__PREPROCESSOR_HAVE_INCLUDE_NEXT */
#endif /* !__NO_ATTR_FORCEINLINE && __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */

#endif /* !_I386_KOS_OPTIMIZED_STRING_H */
