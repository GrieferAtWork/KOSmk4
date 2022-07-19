/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _OPTIMIZED_STRING_H
#define _OPTIMIZED_STRING_H 1

#include <__stdinc.h>

/* Platform-independent, optimized <string.h> functions. */
#if (!defined(__NO_ATTR_FORCEINLINE) && \
     !defined(__NO_builtin_constant_p))
#include <hybrid/__assert.h>
#include <hybrid/host.h>

#include <libc/core/string.h>

__SYSDECL_BEGIN
__NAMESPACE_FAST_BEGIN

#ifndef __ASSERT_MEMCPY_CT
#if !defined(NDEBUG) && 0 /* Doesn't work correctly and actually causes false positives */
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


#ifdef __UINT64_TYPE__
#ifndef __fast_memcpyq_defined
#define __fast_memcpyq_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memcpyq))(/*aligned(8)*/ void *__restrict __dst,
                                         /*aligned(8)*/ void const *__restrict __src,
                                         __SIZE_TYPE__ __n_qwords) {
	if __untraced(__builtin_constant_p(__dst == __src) && (__dst == __src))
		return (__UINT64_TYPE__ *)__dst;
	__ASSERT_MEMCPY_CT(__dst, __src, __n_qwords * 8);
	if __untraced(__builtin_constant_p(__n_qwords)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_qwords) {
		case 0:
			return (__UINT64_TYPE__ *)__dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 1:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT64_TYPE__ *)__dst;
		case 2:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			return (__UINT64_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 1:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return (__UINT64_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 3:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			return (__UINT64_TYPE__ *)__dst;
		case 4:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			return (__UINT64_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 2:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			return (__UINT64_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
		default: break;
		}
	}
	return __libc_core_memcpyq(__dst, __src, __n_qwords);
}
#endif /* !__fast_memcpyq_defined */
#endif /* __UINT64_TYPE__ */

#ifndef __fast_memcpyl_defined
#define __fast_memcpyl_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memcpyl))(/*aligned(4)*/ void *__restrict __dst,
                                         /*aligned(4)*/ void const *__restrict __src,
                                         __SIZE_TYPE__ __n_dwords) {
	if __untraced(__builtin_constant_p(__dst == __src) && (__dst == __src))
		return (__UINT32_TYPE__ *)__dst;
	__ASSERT_MEMCPY_CT(__dst, __src, __n_dwords * 4);
	if __untraced(__builtin_constant_p(__n_dwords)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_dwords) {
		case 0:
			return (__UINT32_TYPE__ *)__dst;
		case 1:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return (__UINT32_TYPE__ *)__dst;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT32_TYPE__ *)__dst;
		case 4:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			return (__UINT32_TYPE__ *)__dst;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 2:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
		case 3:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT32_TYPE__ *)__dst;
		case 4:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			return (__UINT32_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 2:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return (__UINT32_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

		/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 5:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			return (__UINT32_TYPE__ *)__dst;
		case 6:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			return (__UINT32_TYPE__ *)__dst;
		case 7:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[6] = ((__UINT32_TYPE__ const *)__src)[6];
			return (__UINT32_TYPE__ *)__dst;
		case 8:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			return (__UINT32_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 3:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT32_TYPE__ *)__dst;
		case 4:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			return (__UINT32_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default: break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_memcpyq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_core_memcpyq(__dst, __src, __n_dwords >> 1);
		__dst = __libc_core_memcpyq(__dst, __src, __n_dwords >> 1);
		((__UINT32_TYPE__ *)__dst)[__n_dwords - 1] = ((__UINT32_TYPE__ const *)__src)[__n_dwords - 1];
		return (__UINT32_TYPE__ *)__dst;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_core_memcpyq((__UINT64_TYPE__ *)__dst, __src, __n_dwords >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memcpyq && __SIZEOF_BUSINT__ >= 8 */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_memcpyl(__dst, __src, __n_dwords);
}
#endif /* !__fast_memcpyl_defined */

#ifndef __fast_memcpyw_defined
#define __fast_memcpyw_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memcpyw))(/*aligned(2)*/ void *__restrict __dst,
                                         /*aligned(2)*/ void const *__restrict __src,
                                         __SIZE_TYPE__ __n_words) {
	if __untraced(__builtin_constant_p(__dst == __src) && (__dst == __src))
		return (__UINT16_TYPE__ *)__dst;
	__ASSERT_MEMCPY_CT(__dst, __src, __n_words * 2);
	if __untraced(__builtin_constant_p(__n_words)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_words) {
		case 0:
			return (__UINT16_TYPE__ *)__dst;
		case 1:
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[1] = ((__UINT16_TYPE__ const *)__src)[1];
			return (__UINT16_TYPE__ *)__dst;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[1] = ((__UINT16_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			return (__UINT16_TYPE__ *)__dst;
		case 4:
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[1] = ((__UINT16_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[3] = ((__UINT16_TYPE__ const *)__src)[3];
			return (__UINT16_TYPE__ *)__dst;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		case 2:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 3:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			return (__UINT16_TYPE__ *)__dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 4:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 5:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			return (__UINT16_TYPE__ *)__dst;
		case 6:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT16_TYPE__ *)__dst;
		case 8:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			return (__UINT16_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 4:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return (__UINT16_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 7:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			return (__UINT16_TYPE__ *)__dst;
		case 9:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[8] = ((__UINT16_TYPE__ const *)__src)[8];
			return (__UINT16_TYPE__ *)__dst;
		case 10:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			return (__UINT16_TYPE__ *)__dst;
		case 11:
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4]  = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT16_TYPE__ *)__dst)[10] = ((__UINT16_TYPE__ const *)__src)[10];
			return (__UINT16_TYPE__ *)__dst;
		case 12:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			return (__UINT16_TYPE__ *)__dst;
		case 13:
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2]  = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[12] = ((__UINT16_TYPE__ const *)__src)[12];
			return (__UINT16_TYPE__ *)__dst;
		case 14:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[6] = ((__UINT32_TYPE__ const *)__src)[6];
			return (__UINT16_TYPE__ *)__dst;
		case 16:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			return (__UINT16_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 5:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			return (__UINT16_TYPE__ *)__dst;
		case 6:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT16_TYPE__ *)__dst;
		case 7:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			return (__UINT16_TYPE__ *)__dst;
		case 8:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			return (__UINT16_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default: break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_memcpyq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_words & 3) {
		case 0:
			return (__UINT16_TYPE__ *)__libc_core_memcpyq(__dst, __src, __n_words >> 2);
		case 1:
			__dst = __libc_core_memcpyq(__dst, __src, __n_words >> 2);
			((__UINT16_TYPE__ *)__dst)[__n_words - 1] = ((__UINT16_TYPE__ const *)__src)[__n_words - 1];
			return (__UINT16_TYPE__ *)__dst;
		case 2:
			__dst = __libc_core_memcpyq(__dst, __src, __n_words >> 2);
			((__UINT32_TYPE__ *)__dst)[(__n_words >> 1) - 1] = ((__UINT32_TYPE__ const *)__src)[(__n_words >> 1) - 1];
			return (__UINT16_TYPE__ *)__dst;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_words & 7))
			return (__UINT16_TYPE__ *)__libc_core_memcpyq(__dst, __src, __n_words >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memcpyq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_memcpyl)
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_core_memcpyl(__dst, __src, __n_words >> 1);
		__dst = __libc_core_memcpyl(__dst, __src, __n_words >> 1);
		((__UINT16_TYPE__ *)__dst)[__n_words - 1] = ((__UINT16_TYPE__ const *)__src)[__n_words - 1];
		return (__UINT16_TYPE__ *)__dst;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_core_memcpyl(__dst, __src, __n_words >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memcpyl */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_memcpyw(__dst, __src, __n_words);
}
#endif /* !__fast_memcpyw_defined */


#ifndef __fast_memcpy_defined
#define __fast_memcpy_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(memcpy))(/*aligned(1)*/ void *__restrict __dst,
                                        /*aligned(1)*/ void const *__restrict __src,
                                        __SIZE_TYPE__ __n_bytes) {
	if __untraced(__builtin_constant_p(__dst == __src) && (__dst == __src))
		return __dst;
	__ASSERT_MEMCPY_CT(__dst, __src, __n_bytes);
	if __untraced(__builtin_constant_p(__n_bytes)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_bytes) {
		case 0:
			return __dst;
		case 1:
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			return __dst;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[1] = ((__UINT8_TYPE__ const *)__src)[1];
			return (__UINT8_TYPE__ *)__dst;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[1] = ((__UINT8_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[2] = ((__UINT8_TYPE__ const *)__src)[2];
			return (__UINT8_TYPE__ *)__dst;
		case 4:
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[1] = ((__UINT8_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[2] = ((__UINT8_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[3] = ((__UINT8_TYPE__ const *)__src)[3];
			return (__UINT8_TYPE__ *)__dst;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
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
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
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
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 8:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return __dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
		case 7:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[6]  = ((__UINT8_TYPE__ const *)__src)[6];
			return __dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 11:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT8_TYPE__ *)__dst)[10] = ((__UINT8_TYPE__ const *)__src)[10];
			return __dst;
		case 13:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[12] = ((__UINT8_TYPE__ const *)__src)[12];
			return __dst;
		case 14:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			return __dst;
		case 15:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			((__UINT8_TYPE__ *)__dst)[14] = ((__UINT8_TYPE__ const *)__src)[14];
			return __dst;
		case 17:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[16] = ((__UINT8_TYPE__ const *)__src)[16];
			return __dst;
		case 18:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[8] = ((__UINT16_TYPE__ const *)__src)[8];
			return __dst;
		case 19:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[8] = ((__UINT16_TYPE__ const *)__src)[8];
			((__UINT8_TYPE__ *)__dst)[18] = ((__UINT8_TYPE__ const *)__src)[18];
			return __dst;
		case 20:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			return __dst;
		case 21:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT8_TYPE__ *)__dst)[20] = ((__UINT8_TYPE__ const *)__src)[20];
			return __dst;
		case 22:
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4]  = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT16_TYPE__ *)__dst)[10] = ((__UINT16_TYPE__ const *)__src)[10];
			return __dst;
		case 24:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			return __dst;
		case 25:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[24] = ((__UINT8_TYPE__ const *)__src)[24];
			return __dst;
		case 26:
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2]  = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[12] = ((__UINT16_TYPE__ const *)__src)[12];
			return __dst;
		case 28:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[6] = ((__UINT32_TYPE__ const *)__src)[6];
			return __dst;
		case 32:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			return __dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 9:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[8]  = ((__UINT8_TYPE__ const *)__src)[8];
			return __dst;
		case 10:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			return __dst;
		case 11:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT8_TYPE__ *)__dst)[10] = ((__UINT8_TYPE__ const *)__src)[10];
			return __dst;
		case 12:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return __dst;
		case 13:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[12] = ((__UINT8_TYPE__ const *)__src)[12];
			return __dst;
		case 14:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			return __dst;
		case 16:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			return __dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default: break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_memcpyq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_bytes & 7) {
		case 0:
			return __libc_core_memcpyq(__dst, __src, __n_bytes >> 3);
		case 1:
			__dst = __libc_core_memcpyq(__dst, __src, __n_bytes >> 3);
			((__UINT8_TYPE__ *)__dst)[__n_bytes - 1] = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
			return __dst;
		case 2:
			__dst = __libc_core_memcpyq(__dst, __src, __n_bytes >> 3);
			((__UINT16_TYPE__ *)__dst)[(__n_bytes >> 1) - 1] = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1) - 1];
			return __dst;
		case 4:
			__dst = __libc_core_memcpyq(__dst, __src, __n_bytes >> 3);
			((__UINT32_TYPE__ *)__dst)[(__n_bytes >> 2) - 1] = ((__UINT32_TYPE__ const *)__src)[(__n_bytes >> 2) - 1];
			return __dst;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 7))
			return __libc_core_memcpyq(__dst, __src, __n_bytes >> 3);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memcpyq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_memcpyl)
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_bytes & 3) {
		case 0:
			return __libc_core_memcpyl(__dst, __src, __n_bytes >> 2);
		case 1:
			__dst = __libc_core_memcpyl(__dst, __src, __n_bytes >> 2);
			((__UINT8_TYPE__ *)__dst)[__n_bytes - 1] = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
			return __dst;
		case 2:
			__dst = __libc_core_memcpyl(__dst, __src, __n_bytes >> 2);
			((__UINT16_TYPE__ *)__dst)[(__n_bytes >> 1) - 1] = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1) - 1];
			return __dst;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 3))
			return __libc_core_memcpyl(__dst, __src, __n_bytes >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memcpyl */
#if defined(__CRT_HAVE_memcpyw)
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_bytes & 1))
			return __libc_core_memcpyw(__dst, __src, __n_bytes >> 1);
		__dst = __libc_core_memcpyw(__dst, __src, __n_bytes >> 1);
		((__UINT8_TYPE__ *)__dst)[__n_bytes - 1] = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
		return __dst;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 1))
			return __libc_core_memcpyw(__dst, __src, __n_bytes >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memcpyw */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_memcpy(__dst, __src, __n_bytes);
}
#endif /* !__fast_memcpy_defined */



#ifdef __UINT64_TYPE__
#ifndef __fast_mempcpyq_defined
#define __fast_mempcpyq_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempcpyq))(/*aligned(8)*/ void *__restrict __dst,
                                          /*aligned(8)*/ void const *__restrict __src,
                                          __SIZE_TYPE__ __n_qwords) {
	if __untraced(__builtin_constant_p(__dst == __src) && (__dst == __src))
		return (__UINT64_TYPE__ *)__dst + __n_qwords;
	__ASSERT_MEMCPY_CT(__dst, __src, __n_qwords * 8);
	if __untraced(__builtin_constant_p(__n_qwords)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_qwords) {
		case 0:
			return (__UINT64_TYPE__ *)__dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 1:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
		case 2:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 1:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 3:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 24);
		case 4:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 32);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 2:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
		default: break;
		}
	}
	return __libc_core_mempcpyq(__dst, __src, __n_qwords);
}
#endif /* !__fast_mempcpyq_defined */
#endif /* __UINT64_TYPE__ */


#ifndef __fast_mempcpyl_defined
#define __fast_mempcpyl_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempcpyl))(/*aligned(4)*/ void *__restrict __dst,
                                          /*aligned(4)*/ void const *__restrict __src,
                                          __SIZE_TYPE__ __n_dwords) {
	if __untraced(__builtin_constant_p(__dst == __src) && (__dst == __src))
		return (__UINT32_TYPE__ *)__dst + __n_dwords;
	__ASSERT_MEMCPY_CT(__dst, __src, __n_dwords * 4);
	if __untraced(__builtin_constant_p(__n_dwords)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_dwords) {
		case 0:
			return (__UINT32_TYPE__ *)__dst;
		case 1:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 4);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return (__UINT32_TYPE__ *)__dst + 2;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT32_TYPE__ *)__dst + 3;
		case 4:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			return (__UINT32_TYPE__ *)__dst + 4;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 2:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
		case 3:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 12);
		case 4:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 2:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 5:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 20);
		case 6:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 24);
		case 7:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[6] = ((__UINT32_TYPE__ const *)__src)[6];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 28);
		case 8:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 32);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 3:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 12);
		case 4:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default: break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_mempcpyq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_core_mempcpyq(__dst, __src, __n_dwords >> 1);
		__dst = __libc_core_mempcpyq(__dst, __src, __n_dwords >> 1);
		((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[__n_dwords - 1];
		return (__UINT32_TYPE__ *)__dst + 1;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_core_mempcpyq((__UINT64_TYPE__ *)__dst, __src, __n_dwords >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempcpyq && __SIZEOF_BUSINT__ >= 8 */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_mempcpyl(__dst, __src, __n_dwords);
}
#endif /* !__fast_mempcpyl_defined */


#ifndef __fast_mempcpyw_defined
#define __fast_mempcpyw_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempcpyw))(/*aligned(2)*/ void *__restrict __dst,
                                          /*aligned(2)*/ void const *__restrict __src,
                                          __SIZE_TYPE__ __n_words) {
	if __untraced(__builtin_constant_p(__dst == __src) && (__dst == __src))
		return (__UINT16_TYPE__ *)__dst + __n_words;
	__ASSERT_MEMCPY_CT(__dst, __src, __n_words * 2);
	if __untraced(__builtin_constant_p(__n_words)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_words) {
		case 0:
			return (__UINT16_TYPE__ *)__dst;
		case 1:
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 2);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[1] = ((__UINT16_TYPE__ const *)__src)[1];
			return (__UINT16_TYPE__ *)__dst + 2;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[1] = ((__UINT16_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			return (__UINT16_TYPE__ *)__dst + 3;
		case 4:
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[1] = ((__UINT16_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[3] = ((__UINT16_TYPE__ const *)__src)[3];
			return (__UINT16_TYPE__ *)__dst + 4;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		case 2:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 4);
		case 3:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 6);
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 4:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
		case 5:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 10);
		case 6:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 12);
		case 8:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 4:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
		/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 7:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 14);
		case 9:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[8] = ((__UINT16_TYPE__ const *)__src)[8];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 18);
		case 10:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 20);
		case 11:
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4]  = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT16_TYPE__ *)__dst)[10] = ((__UINT16_TYPE__ const *)__src)[10];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 22);
		case 12:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 24);
		case 13:
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2]  = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[12] = ((__UINT16_TYPE__ const *)__src)[12];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 26);
		case 14:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[6] = ((__UINT32_TYPE__ const *)__src)[6];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 28);
		case 16:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 32);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 5:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 10);
		case 6:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 12);
		case 7:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 14);
		case 8:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default: break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_mempcpyq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_words & 3) {
		case 0:
			return (__UINT16_TYPE__ *)__libc_core_mempcpyq(__dst, __src, __n_words >> 2);
		case 1:
			__dst = __libc_core_mempcpyq(__dst, __src, __n_words >> 2);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[__n_words - 1];
			return (__UINT16_TYPE__ *)__dst + 1;
		case 2:
			__dst = __libc_core_mempcpyq(__dst, __src, __n_words >> 2);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[(__n_words >> 1) - 1];
			return (__UINT16_TYPE__ *)__dst + 2;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_words & 3))
			return (__UINT16_TYPE__ *)__libc_core_mempcpyq(__dst, __src, __n_words >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempcpyq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_mempcpyl)
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_core_mempcpyl(__dst, __src, __n_words >> 1);
		__dst = __libc_core_mempcpyl(__dst, __src, __n_words >> 1);
		((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[__n_words - 1];
		return (__UINT16_TYPE__ *)__dst + 1;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_core_mempcpyl(__dst, __src, __n_words >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempcpyl */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_mempcpyw(__dst, __src, __n_words);
}
#endif /* !__fast_mempcpyw_defined */


#ifndef __fast_mempcpy_defined
#define __fast_mempcpy_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempcpy))(/*aligned(1)*/ void *__restrict __dst,
                                         /*aligned(1)*/ void const *__restrict __src,
                                         __SIZE_TYPE__ __n_bytes) {
	if __untraced(__builtin_constant_p(__dst == __src) && (__dst == __src))
		return (__UINT8_TYPE__ *)__dst + __n_bytes;
	__ASSERT_MEMCPY_CT(__dst, __src, __n_bytes);
	if __untraced(__builtin_constant_p(__n_bytes)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_bytes) {
		case 0:
			return __dst;
		case 1:
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 1;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[1] = ((__UINT8_TYPE__ const *)__src)[1];
			return (__UINT8_TYPE__ *)__dst + 2;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[1] = ((__UINT8_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[2] = ((__UINT8_TYPE__ const *)__src)[2];
			return (__UINT8_TYPE__ *)__dst + 3;
		case 4:
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[1] = ((__UINT8_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[2] = ((__UINT8_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[3] = ((__UINT8_TYPE__ const *)__src)[3];
			return (__UINT8_TYPE__ *)__dst + 4;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
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
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
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
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 8:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return (__UINT8_TYPE__ *)__dst + 8;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
		/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
		case 7:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[6]  = ((__UINT8_TYPE__ const *)__src)[6];
			return (__UINT8_TYPE__ *)__dst + 7;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 11:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT8_TYPE__ *)__dst)[10] = ((__UINT8_TYPE__ const *)__src)[10];
			return (__UINT8_TYPE__ *)__dst + 11;
		case 13:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[12] = ((__UINT8_TYPE__ const *)__src)[12];
			return (__UINT8_TYPE__ *)__dst + 13;
		case 14:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			return (__UINT8_TYPE__ *)__dst + 14;
		case 15:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			((__UINT8_TYPE__ *)__dst)[14] = ((__UINT8_TYPE__ const *)__src)[14];
			return (__UINT8_TYPE__ *)__dst + 15;
		case 17:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[16] = ((__UINT8_TYPE__ const *)__src)[16];
			return (__UINT8_TYPE__ *)__dst + 17;
		case 18:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[8] = ((__UINT16_TYPE__ const *)__src)[8];
			return (__UINT8_TYPE__ *)__dst + 18;
		case 19:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[8] = ((__UINT16_TYPE__ const *)__src)[8];
			((__UINT8_TYPE__ *)__dst)[18] = ((__UINT8_TYPE__ const *)__src)[18];
			return (__UINT8_TYPE__ *)__dst + 19;
		case 20:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			return (__UINT8_TYPE__ *)__dst + 20;
		case 21:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT8_TYPE__ *)__dst)[20] = ((__UINT8_TYPE__ const *)__src)[20];
			return (__UINT8_TYPE__ *)__dst + 21;
		case 22:
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4]  = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT16_TYPE__ *)__dst)[10] = ((__UINT16_TYPE__ const *)__src)[10];
			return (__UINT8_TYPE__ *)__dst + 22;
		case 24:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			return (__UINT8_TYPE__ *)__dst + 24;
		case 25:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[24] = ((__UINT8_TYPE__ const *)__src)[24];
			return (__UINT8_TYPE__ *)__dst + 25;
		case 26:
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2]  = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[12] = ((__UINT16_TYPE__ const *)__src)[12];
			return (__UINT8_TYPE__ *)__dst + 26;
		case 28:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[6] = ((__UINT32_TYPE__ const *)__src)[6];
			return (__UINT8_TYPE__ *)__dst + 28;
		case 32:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			return (__UINT8_TYPE__ *)__dst + 32;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 9:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[8]  = ((__UINT8_TYPE__ const *)__src)[8];
			return (__UINT8_TYPE__ *)__dst + 9;
		case 10:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			return (__UINT8_TYPE__ *)__dst + 10;
		case 11:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT8_TYPE__ *)__dst)[10] = ((__UINT8_TYPE__ const *)__src)[10];
			return (__UINT8_TYPE__ *)__dst + 11;
		case 12:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT8_TYPE__ *)__dst + 12;
		case 13:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[12] = ((__UINT8_TYPE__ const *)__src)[12];
			return (__UINT8_TYPE__ *)__dst + 13;
		case 14:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			return (__UINT8_TYPE__ *)__dst + 14;
		case 16:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			return (__UINT8_TYPE__ *)__dst + 16;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default: break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_mempcpyq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_bytes & 7) {
		case 0:
			return __libc_core_mempcpyq(__dst, __src, __n_bytes >> 3);
		case 1:
			__dst = __libc_core_mempcpyq(__dst, __src, __n_bytes >> 3);
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
			return (__UINT8_TYPE__ *)__dst + 1;
		case 2:
			__dst = __libc_core_mempcpyq(__dst, __src, __n_bytes >> 3);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1) - 1];
			return (__UINT8_TYPE__ *)__dst + 2;
		case 4:
			__dst = __libc_core_mempcpyq(__dst, __src, __n_bytes >> 3);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[(__n_bytes >> 2) - 1];
			return (__UINT8_TYPE__ *)__dst + 4;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 7))
			return __libc_core_mempcpyq(__dst, __src, __n_bytes >> 3);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempcpyq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_mempcpyl)
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_bytes & 3) {
		case 0:
			return __libc_core_mempcpyl(__dst, __src, __n_bytes >> 2);
		case 1:
			__dst = __libc_core_mempcpyl(__dst, __src, __n_bytes >> 2);
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
			return (__UINT8_TYPE__ *)__dst + 1;
		case 2:
			__dst = __libc_core_mempcpyl(__dst, __src, __n_bytes >> 2);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1) - 1];
			return (__UINT8_TYPE__ *)__dst + 2;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 3))
			return __libc_core_mempcpyl(__dst, __src, __n_bytes >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempcpyl */
#if defined(__CRT_HAVE_mempcpyw)
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_bytes & 1))
			return __libc_core_mempcpyw(__dst, __src, __n_bytes >> 1);
		__dst = __libc_core_mempcpyw(__dst, __src, __n_bytes >> 1);
		((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
		return (__UINT8_TYPE__ *)__dst + 1;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 1))
			return __libc_core_mempcpyw(__dst, __src, __n_bytes >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempcpyw */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_mempcpy(__dst, __src, __n_bytes);
}
#endif /* !__fast_mempcpy_defined */


#if (!defined(__fast_bzero_defined) ||  \
     !defined(__fast_bzerow_defined) || \
     !defined(__fast_bzerol_defined) || \
     (!defined(__fast_bzeroq_defined) && defined(__UINT64_TYPE__)))
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__private_bzero_constant)(void *__restrict __dst,
                                        __SIZE_TYPE__ __n_bytes
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#define __private_bzero_constant_ifaligned(n, tt)         tt
#define __private_bzero_constant(dst, n_bytes, alignment) (__private_bzero_constant)(dst, n_bytes)
#else /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#define __private_bzero_constant_ifaligned(n, tt) if (__alignment >= n) tt
                                        ,
                                        __SIZE_TYPE__ __alignment
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
                                        ) {
	switch __untraced(__n_bytes) {

	case 0:
		return;

	case 1:
		((__UINT8_TYPE__ *)__dst)[0] = 0;
		return;

	case 2:
		__private_bzero_constant_ifaligned(2, {
			((__UINT16_TYPE__ *)__dst)[0] = 0;
			return;
		})
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		((__UINT8_TYPE__ *)__dst)[0] =
		((__UINT8_TYPE__ *)__dst)[1] = 0;
		return;
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		break;

	case 3:
		__private_bzero_constant_ifaligned(2, {
			((__UINT16_TYPE__ *)__dst)[0] = 0;
			((__UINT8_TYPE__ *)__dst)[2]  = 0;
			return;
		})
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#ifndef __OPTIMIZE_SIZE__
		((__UINT8_TYPE__ *)__dst)[0] =
		((__UINT8_TYPE__ *)__dst)[1] =
		((__UINT8_TYPE__ *)__dst)[2] = 0;
		return;
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		break;

	case 4:
		__private_bzero_constant_ifaligned(4, {
			((__UINT32_TYPE__ *)__dst)[0] = 0;
			return;
		})
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		__private_bzero_constant_ifaligned(2, {
			((__UINT16_TYPE__ *)__dst)[0] =
			((__UINT16_TYPE__ *)__dst)[1] = 0;
			return;
		})
#ifndef __OPTIMIZE_SIZE__
		((__UINT8_TYPE__ *)__dst)[0] =
		((__UINT8_TYPE__ *)__dst)[1] =
		((__UINT8_TYPE__ *)__dst)[2] =
		((__UINT8_TYPE__ *)__dst)[3] = 0;
		return;
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		break;

	case 5:
		__private_bzero_constant_ifaligned(4, {
			((__UINT32_TYPE__ *)__dst)[0] = 0;
			((__UINT8_TYPE__ *)__dst)[4]  = 0;
			return;
		})
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#ifndef __OPTIMIZE_SIZE__
		__private_bzero_constant_ifaligned(2, {
			((__UINT16_TYPE__ *)__dst)[0] =
			((__UINT16_TYPE__ *)__dst)[1] = 0;
			((__UINT8_TYPE__ *)__dst)[4]  = 0;
			return;
		})
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		break;

	case 6:
		__private_bzero_constant_ifaligned(4, {
			((__UINT32_TYPE__ *)__dst)[0] = 0;
			((__UINT16_TYPE__ *)__dst)[2] = 0;
			return;
		})
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#ifndef __OPTIMIZE_SIZE__
		__private_bzero_constant_ifaligned(2, {
			((__UINT16_TYPE__ *)__dst)[0] =
			((__UINT16_TYPE__ *)__dst)[1] =
			((__UINT16_TYPE__ *)__dst)[2] = 0;
			return;
		})
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		break;

#ifndef __OPTIMIZE_SIZE__
	case 7:
		__private_bzero_constant_ifaligned(4, {
			((__UINT32_TYPE__ *)__dst)[0] = 0;
			((__UINT16_TYPE__ *)__dst)[2] = 0;
			((__UINT8_TYPE__ *)__dst)[6]  = 0;
			return;
		})
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		__private_bzero_constant_ifaligned(2, {
			((__UINT16_TYPE__ *)__dst)[0] =
			((__UINT16_TYPE__ *)__dst)[1] =
			((__UINT16_TYPE__ *)__dst)[2] = 0;
			((__UINT8_TYPE__ *)__dst)[6]  = 0;
			return;
		})
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		break;
#endif /* !__OPTIMIZE_SIZE__ */

	case 8:
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		__private_bzero_constant_ifaligned(8, {
			((__UINT64_TYPE__ *)__dst)[0] = 0;
			return;
		})
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#if !defined(__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS) || __SIZEOF_BUSINT__ < 8 || !defined(__UINT64_TYPE__)
		__private_bzero_constant_ifaligned(4, {
			((__UINT32_TYPE__ *)__dst)[0] =
			((__UINT32_TYPE__ *)__dst)[1] = 0;
			return;
		})
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS || __SIZEOF_BUSINT__ | 8 || !__UINT64_TYPE__ */
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#ifndef __OPTIMIZE_SIZE__
		__private_bzero_constant_ifaligned(2, {
			((__UINT16_TYPE__ *)__dst)[0] =
			((__UINT16_TYPE__ *)__dst)[1] =
			((__UINT16_TYPE__ *)__dst)[2] =
			((__UINT16_TYPE__ *)__dst)[3] = 0;
			return;
		})
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		break;

#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
	case 9:
		__private_bzero_constant_ifaligned(8, {
			((__UINT64_TYPE__ *)__dst)[0] = 0;
			((__UINT8_TYPE__ *)__dst)[8]  = 0;
			return;
		})
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#ifndef __OPTIMIZE_SIZE__
		__private_bzero_constant_ifaligned(4, {
			((__UINT32_TYPE__ *)__dst)[0] =
			((__UINT32_TYPE__ *)__dst)[1] = 0;
			((__UINT8_TYPE__ *)__dst)[8]  = 0;
			return;
		})
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		break;

	case 10:
		__private_bzero_constant_ifaligned(8, {
			((__UINT64_TYPE__ *)__dst)[0] = 0;
			((__UINT16_TYPE__ *)__dst)[4] = 0;
			return;
		})
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#ifndef __OPTIMIZE_SIZE__
		__private_bzero_constant_ifaligned(4, {
			((__UINT32_TYPE__ *)__dst)[0] =
			((__UINT32_TYPE__ *)__dst)[1] = 0;
			((__UINT16_TYPE__ *)__dst)[4] = 0;
			return;
		})
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		break;

	case 12:
		__private_bzero_constant_ifaligned(8, {
			((__UINT64_TYPE__ *)__dst)[0] = 0;
			((__UINT32_TYPE__ *)__dst)[2] = 0;
			return;
		})
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#ifndef __OPTIMIZE_SIZE__
		__private_bzero_constant_ifaligned(4, {
			((__UINT32_TYPE__ *)__dst)[0] =
			((__UINT32_TYPE__ *)__dst)[1] =
			((__UINT32_TYPE__ *)__dst)[2] = 0;
			return;
		})
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		break;

	case 16:
		__private_bzero_constant_ifaligned(8, {
			((__UINT64_TYPE__ *)__dst)[0] =
			((__UINT64_TYPE__ *)__dst)[1] = 0;
			return;
		})
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#ifndef __OPTIMIZE_SIZE__
		__private_bzero_constant_ifaligned(4, {
			((__UINT32_TYPE__ *)__dst)[0] =
			((__UINT32_TYPE__ *)__dst)[1] =
			((__UINT32_TYPE__ *)__dst)[2] =
			((__UINT32_TYPE__ *)__dst)[3] = 0;
			return;
		})
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		break;

#ifndef __OPTIMIZE_SIZE__
	case 11:
		__private_bzero_constant_ifaligned(8, {
			((__UINT64_TYPE__ *)__dst)[0] = 0;
			((__UINT16_TYPE__ *)__dst)[4] = 0;
			((__UINT8_TYPE__ *)__dst)[10] = 0;
			return;
		})
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		__private_bzero_constant_ifaligned(4, {
			((__UINT32_TYPE__ *)__dst)[0] =
			((__UINT32_TYPE__ *)__dst)[1] = 0;
			((__UINT16_TYPE__ *)__dst)[4] = 0;
			((__UINT8_TYPE__ *)__dst)[10] = 0;
			return;
		})
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		break;

	case 13:
		__private_bzero_constant_ifaligned(8, {
			((__UINT64_TYPE__ *)__dst)[0] = 0;
			((__UINT32_TYPE__ *)__dst)[2] = 0;
			((__UINT8_TYPE__ *)__dst)[12] = 0;
			return;
		})
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		__private_bzero_constant_ifaligned(4, {
			((__UINT32_TYPE__ *)__dst)[0] =
			((__UINT32_TYPE__ *)__dst)[1] =
			((__UINT32_TYPE__ *)__dst)[2] = 0;
			((__UINT8_TYPE__ *)__dst)[12] = 0;
			return;
		})
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		break;

	case 14:
		__private_bzero_constant_ifaligned(8, {
			((__UINT64_TYPE__ *)__dst)[0] = 0;
			((__UINT32_TYPE__ *)__dst)[2] = 0;
			((__UINT16_TYPE__ *)__dst)[6] = 0;
			return;
		})
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		__private_bzero_constant_ifaligned(4, {
			((__UINT32_TYPE__ *)__dst)[0] =
			((__UINT32_TYPE__ *)__dst)[1] =
			((__UINT32_TYPE__ *)__dst)[2] = 0;
			((__UINT16_TYPE__ *)__dst)[6] = 0;
			return;
		})
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		break;

	case 15:
		__private_bzero_constant_ifaligned(8, {
			((__UINT64_TYPE__ *)__dst)[0] = 0;
			((__UINT32_TYPE__ *)__dst)[2] = 0;
			((__UINT16_TYPE__ *)__dst)[6] = 0;
			((__UINT8_TYPE__ *)__dst)[14] = 0;
			return;
		})
		break;

	case 17:
		__private_bzero_constant_ifaligned(8, {
			((__UINT64_TYPE__ *)__dst)[0] =
			((__UINT64_TYPE__ *)__dst)[1] = 0;
			((__UINT8_TYPE__ *)__dst)[16] = 0;
			return;
		})
		break;

	case 18:
		__private_bzero_constant_ifaligned(8, {
			((__UINT64_TYPE__ *)__dst)[0] =
			((__UINT64_TYPE__ *)__dst)[1] = 0;
			((__UINT16_TYPE__ *)__dst)[8] = 0;
			return;
		})
		break;

	case 19:
		__private_bzero_constant_ifaligned(8, {
			((__UINT64_TYPE__ *)__dst)[0] =
			((__UINT64_TYPE__ *)__dst)[1] = 0;
			((__UINT16_TYPE__ *)__dst)[8] = 0;
			((__UINT8_TYPE__ *)__dst)[18] = 0;
			return;
		})
		break;

	case 20:
		__private_bzero_constant_ifaligned(8, {
			((__UINT64_TYPE__ *)__dst)[0] =
			((__UINT64_TYPE__ *)__dst)[1] = 0;
			((__UINT32_TYPE__ *)__dst)[4] = 0;
			return;
		})
		break;

	case 21:
		__private_bzero_constant_ifaligned(8, {
			((__UINT64_TYPE__ *)__dst)[0] =
			((__UINT64_TYPE__ *)__dst)[1] = 0;
			((__UINT32_TYPE__ *)__dst)[4] = 0;
			((__UINT8_TYPE__ *)__dst)[20] = 0;
			return;
		})
		break;

	case 22:
		__private_bzero_constant_ifaligned(8, {
			((__UINT64_TYPE__ *)__dst)[0]  =
			((__UINT64_TYPE__ *)__dst)[1]  = 0;
			((__UINT32_TYPE__ *)__dst)[4]  = 0;
			((__UINT16_TYPE__ *)__dst)[10] = 0;
			return;
		})
		break;

	case 24:
		__private_bzero_constant_ifaligned(8, {
			((__UINT64_TYPE__ *)__dst)[0] =
			((__UINT64_TYPE__ *)__dst)[1] =
			((__UINT64_TYPE__ *)__dst)[2] = 0;
			return;
		})
		break;

	case 25:
		__private_bzero_constant_ifaligned(8, {
			((__UINT64_TYPE__ *)__dst)[0] =
			((__UINT64_TYPE__ *)__dst)[1] =
			((__UINT64_TYPE__ *)__dst)[2] = 0;
			((__UINT8_TYPE__ *)__dst)[24] = 0;
			return;
		})
		break;

	case 26:
		__private_bzero_constant_ifaligned(8, {
			((__UINT64_TYPE__ *)__dst)[0]  =
			((__UINT64_TYPE__ *)__dst)[1]  =
			((__UINT64_TYPE__ *)__dst)[2]  = 0;
			((__UINT16_TYPE__ *)__dst)[12] = 0;
			return;
		})
		break;

	case 28:
		__private_bzero_constant_ifaligned(8, {
			((__UINT64_TYPE__ *)__dst)[0] =
			((__UINT64_TYPE__ *)__dst)[1] =
			((__UINT64_TYPE__ *)__dst)[2] = 0;
			((__UINT32_TYPE__ *)__dst)[6] = 0;
			return;
		})
		break;

	case 32:
		__private_bzero_constant_ifaligned(8, {
			((__UINT64_TYPE__ *)__dst)[0] =
			((__UINT64_TYPE__ *)__dst)[1] =
			((__UINT64_TYPE__ *)__dst)[2] =
			((__UINT64_TYPE__ *)__dst)[3] = 0;
			return;
		})
		break;
#endif /* !__OPTIMIZE_SIZE__ */

#else /* __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__) */
#ifndef __OPTIMIZE_SIZE__
	case 9:
		__private_bzero_constant_ifaligned(4, {
			((__UINT32_TYPE__ *)__dst)[0] =
			((__UINT32_TYPE__ *)__dst)[1] = 0;
			((__UINT8_TYPE__ *)__dst)[8]  = 0;
			return;
		})
		break;

	case 10:
		__private_bzero_constant_ifaligned(4, {
			((__UINT32_TYPE__ *)__dst)[0] =
			((__UINT32_TYPE__ *)__dst)[1] = 0;
			((__UINT16_TYPE__ *)__dst)[4] = 0;
			return;
		})
		break;

	case 11:
		__private_bzero_constant_ifaligned(4, {
			((__UINT32_TYPE__ *)__dst)[0] =
			((__UINT32_TYPE__ *)__dst)[1] = 0;
			((__UINT16_TYPE__ *)__dst)[4] = 0;
			((__UINT8_TYPE__ *)__dst)[10] = 0;
			return;
		})
		break;

	case 12:
		__private_bzero_constant_ifaligned(4, {
			((__UINT32_TYPE__ *)__dst)[0] =
			((__UINT32_TYPE__ *)__dst)[1] =
			((__UINT32_TYPE__ *)__dst)[2] = 0;
			return;
		})
		break;

	case 13:
		__private_bzero_constant_ifaligned(4, {
			((__UINT32_TYPE__ *)__dst)[0] =
			((__UINT32_TYPE__ *)__dst)[1] =
			((__UINT32_TYPE__ *)__dst)[2] = 0;
			((__UINT8_TYPE__ *)__dst)[12] = 0;
			return;
		})
		break;

	case 14:
		__private_bzero_constant_ifaligned(4, {
			((__UINT32_TYPE__ *)__dst)[0] =
			((__UINT32_TYPE__ *)__dst)[1] =
			((__UINT32_TYPE__ *)__dst)[2] = 0;
			((__UINT16_TYPE__ *)__dst)[6] = 0;
			return;
		})
		break;

	case 16:
		__private_bzero_constant_ifaligned(4, {
			((__UINT32_TYPE__ *)__dst)[0] =
			((__UINT32_TYPE__ *)__dst)[1] =
			((__UINT32_TYPE__ *)__dst)[2] =
			((__UINT32_TYPE__ *)__dst)[3] = 0;
			return;
		})
		break;
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

	default:
		break;
	}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	if (!(__n_bytes & 7)) {
		__libc_core_bzeroq(__dst, __n_bytes >> 3);
	} else if (!(__n_bytes & 3)) {
		__libc_core_bzerol(__dst, __n_bytes >> 2);
	} else if (!(__n_bytes & 1)) {
		__libc_core_bzerow(__dst, __n_bytes >> 1);
	} else {
		__libc_core_bzero(__dst, __n_bytes);
	}
#else /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	if (!(__n_bytes & 7) && __alignment >= 8) {
		__libc_core_bzeroq(__dst, __n_bytes >> 3);
	} else if (!(__n_bytes & 3) && __alignment >= 4) {
		__libc_core_bzerol(__dst, __n_bytes >> 2);
	} else if (!(__n_bytes & 1) && __alignment >= 2) {
		__libc_core_bzerow(__dst, __n_bytes >> 1);
	} else {
		__libc_core_bzero(__dst, __n_bytes);
	}
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#undef __private_bzero_constant_ifaligned
}
#endif /* !__fast_bzero_defined */


#ifdef __UINT64_TYPE__
#ifndef __fast_bzeroq_defined
#define __fast_bzeroq_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBC_FAST_NAME(bzeroq))(/*aligned(8)*/ void *__restrict __dst,
                                        __SIZE_TYPE__ __n_qwords) {
	if __untraced(__builtin_constant_p(__n_qwords)) {
		__private_bzero_constant(__dst, __n_qwords << 3, 8);
	} else {
		__libc_core_bzeroq(__dst, __n_qwords);
	}
}
#endif /* !__fast_bzeroq_defined */
#endif /* __UINT64_TYPE__ */


#ifndef __fast_bzerol_defined
#define __fast_bzerol_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBC_FAST_NAME(bzerol))(/*aligned(4)*/ void *__restrict __dst,
                                        __SIZE_TYPE__ __n_dwords) {
	if __untraced(__builtin_constant_p(__n_dwords)) {
		__private_bzero_constant(__dst, __n_dwords << 2, 4);
	} else {
		__libc_core_bzerol(__dst, __n_dwords);
	}
}
#endif /* !__fast_bzerol_defined */


#ifndef __fast_bzerow_defined
#define __fast_bzerow_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBC_FAST_NAME(bzerow))(/*aligned(2)*/ void *__restrict __dst,
                                        __SIZE_TYPE__ __n_words) {
	if __untraced(__builtin_constant_p(__n_words)) {
		__private_bzero_constant(__dst, __n_words << 1, 2);
	} else {
		__libc_core_bzerow(__dst, __n_words);
	}
}
#endif /* !__fast_bzerow_defined */

#ifndef __fast_bzero_defined
#define __fast_bzero_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBC_FAST_NAME(bzero))(/*aligned(1)*/ void *__restrict __dst,
                                       __SIZE_TYPE__ __n_bytes) {
	if __untraced(__builtin_constant_p(__n_bytes)) {
		__private_bzero_constant(__dst, __n_bytes, 1);
	} else {
		__libc_core_bzero(__dst, __n_bytes);
	}
}
#endif /* !__fast_bzero_defined */


#ifdef __UINT64_TYPE__
#ifndef __fast_memsetq_defined
#define __fast_memsetq_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memsetq))(/*aligned(8)*/ void *__restrict __dst,
                                         __UINT64_TYPE__ __qword,
                                         __SIZE_TYPE__ __n_qwords) {
	if __untraced(__builtin_constant_p(__qword)) {
		if __untraced(__qword == 0) {
			__LIBC_FAST_NAME(bzeroq)(__dst, __n_qwords);
			return (__UINT64_TYPE__ *)__dst;
		}
		if __untraced(__builtin_constant_p(__n_qwords)) {
			/* Optimizations for small data blocks (those possible with <= 2 assignments). */
			switch __untraced(__n_qwords) {
			case 0:
				return (__UINT64_TYPE__ *)__dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
			case 1:
				((__UINT64_TYPE__ *)__dst)[0] = __qword;
				return (__UINT64_TYPE__ *)__dst;
			case 2:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = __qword;
				return (__UINT64_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
			case 1:
				((__UINT64_TYPE__ *)__dst)[0] = __qword;
				return (__UINT64_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
			case 3:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] = __qword;
				return (__UINT64_TYPE__ *)__dst;
			case 4:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] =
				((__UINT64_TYPE__ *)__dst)[3] = __qword;
				return (__UINT64_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
			case 2:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = __qword;
				return (__UINT64_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
			default: break;
			}
		}
	}
#if !defined(__CRT_HAVE_memsetq) && \
    (defined(__CRT_HAVE_memsetl) || defined(__CRT_HAVE_memsetw) || defined(__CRT_HAVE_memset))
	if __untraced(__builtin_constant_p(__qword)) {
#ifdef __CRT_HAVE_memsetl
		if __untraced((__qword & __UINT32_C(0xffffffff)) == ((__qword >> 32) & __UINT32_C(0xffffffff)))
			return (__UINT64_TYPE__ *)__libc_core_memsetl(__dst, __qword & __UINT32_C(0xffffffff), __n_qwords * 2);
#endif /* __CRT_HAVE_memsetl */
#ifdef __CRT_HAVE_memsetw
		if __untraced((__qword & __UINT16_C(0xffff)) == ((__qword >> 16) & __UINT16_C(0xffff)) &&
		    (__qword & __UINT16_C(0xffff)) == ((__qword >> 32) & __UINT16_C(0xffff)) &&
		    (__qword & __UINT16_C(0xffff)) == ((__qword >> 48) & __UINT16_C(0xffff)))
			return (__UINT64_TYPE__ *)__libc_core_memsetw(__dst, __qword & __UINT16_C(0xffff), __n_qwords * 4);
#endif /* __CRT_HAVE_memsetw */
#ifdef __CRT_HAVE_memset
		if __untraced((__qword & __UINT8_C(0xff)) == ((__qword >> 8) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 16) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 24) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 32) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 40) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 48) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 56) & __UINT8_C(0xff)))
			return (__UINT64_TYPE__ *)__libc_core_memset(__dst, __qword & __UINT8_C(0xff), __n_qwords * 8);
#endif /* __CRT_HAVE_memset */
	}
#elif defined(__CRT_HAVE_memsetl) && __SIZEOF_BUSINT__ < 8
	if __untraced(__builtin_constant_p(__qword) &&
	   (__qword & __UINT32_C(0xffffffff)) == ((__qword >> 32) & __UINT32_C(0xffffffff)))
		return (__UINT64_TYPE__ *)__libc_core_memsetl(__dst, __qword & __UINT32_C(0xffffffff), __n_qwords * 2);
#endif /* !__CRT_HAVE_memsetq && ... */
	return __libc_core_memsetq(__dst, __qword, __n_qwords);
}
#endif /* !__fast_memsetq_defined */
#endif /* __UINT64_TYPE__ */


#ifndef __fast_memsetl_defined
#define __fast_memsetl_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memsetl))(/*aligned(4)*/ void *__restrict __dst,
                                         __UINT32_TYPE__ __dword,
                                         __SIZE_TYPE__ __n_dwords) {
	if __untraced(__builtin_constant_p(__dword)) {
		if __untraced(__dword == 0) {
			__LIBC_FAST_NAME(bzerol)(__dst, __n_dwords);
			return (__UINT32_TYPE__ *)__dst;
		}
		if __untraced(__builtin_constant_p(__n_dwords)) {
			/* Optimizations for small data blocks (those possible with <= 2 assignments). */
			switch __untraced(__n_dwords) {
			case 0:
				return (__UINT32_TYPE__ *)__dst;
			case 1:
				((__UINT32_TYPE__ *)__dst)[0] = __dword;
				return (__UINT32_TYPE__ *)__dst;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
			case 2:
				((__UINT32_TYPE__ *)__dst)[0] = __dword;
				((__UINT32_TYPE__ *)__dst)[1] = __dword;
				return (__UINT32_TYPE__ *)__dst;
#ifndef __OPTIMIZE_SIZE__
			case 3:
				((__UINT32_TYPE__ *)__dst)[0] = __dword;
				((__UINT32_TYPE__ *)__dst)[1] = __dword;
				((__UINT32_TYPE__ *)__dst)[2] = __dword;
				return (__UINT32_TYPE__ *)__dst;
			case 4:
				((__UINT32_TYPE__ *)__dst)[0] = __dword;
				((__UINT32_TYPE__ *)__dst)[1] = __dword;
				((__UINT32_TYPE__ *)__dst)[2] = __dword;
				((__UINT32_TYPE__ *)__dst)[3] = __dword;
				return (__UINT32_TYPE__ *)__dst;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
			case 2:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)__dword * __UINT64_C(0x0000000100000001));
				return (__UINT32_TYPE__ *)__dst;
			case 3:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)__dword * __UINT64_C(0x0000000100000001));
				((__UINT32_TYPE__ *)__dst)[2] = __dword;
				return (__UINT32_TYPE__ *)__dst;
			case 4:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)__dword * __UINT64_C(0x0000000100000001));
				return (__UINT32_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
			case 2:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] = __dword;
				return (__UINT32_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
			case 5:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)__dword * __UINT64_C(0x0000000100000001));
				((__UINT32_TYPE__ *)__dst)[4] = __dword;
				return (__UINT32_TYPE__ *)__dst;
			case 6:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] = (__UINT64_TYPE__)((__UINT64_TYPE__)__dword * __UINT64_C(0x0000000100000001));
				return (__UINT32_TYPE__ *)__dst;
			case 7:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] = (__UINT64_TYPE__)((__UINT64_TYPE__)__dword * __UINT64_C(0x0000000100000001));
				((__UINT32_TYPE__ *)__dst)[6] = __dword;
				return (__UINT32_TYPE__ *)__dst;
			case 8:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] =
				((__UINT64_TYPE__ *)__dst)[3] = (__UINT64_TYPE__)((__UINT64_TYPE__)__dword * __UINT64_C(0x0000000100000001));
				return (__UINT32_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
			case 3:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] =
				((__UINT32_TYPE__ *)__dst)[2] = __dword;
				return (__UINT32_TYPE__ *)__dst;
			case 4:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] =
				((__UINT32_TYPE__ *)__dst)[2] =
				((__UINT32_TYPE__ *)__dst)[3] = __dword;
				return (__UINT32_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
			default: break;
			}
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#ifndef __OPTIMIZE_SIZE__
#if defined(__CRT_HAVE_mempsetq) && __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		void *__temp;
		__temp = __libc_core_mempsetq(__dst,
		                             (__UINT64_TYPE__)((__UINT64_TYPE__)__dword * __UINT64_C(0x0000000100000001)),
		                              __n_dwords >> 1);
		if __untraced(__n_dwords & 1)
			((__UINT32_TYPE__ *)__temp)[0] = __dword;
		return (__UINT32_TYPE__ *)__dst;
#endif /* __CRT_HAVE_mempsetq && __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
#if !defined(__CRT_HAVE_memsetl) && \
    (defined(__CRT_HAVE_memsetw) || defined(__CRT_HAVE_memset))
	if __untraced(__builtin_constant_p(__dword)) {
#ifdef __CRT_HAVE_memsetw
		if __untraced((__dword & __UINT16_C(0xffff)) == ((__dword >> 16) & __UINT16_C(0xffff)))
			return (__UINT32_TYPE__ *)__libc_core_memsetw(__dst, __dword & __UINT16_C(0xffff), __n_dwords * 2);
#endif /* __CRT_HAVE_memsetw */
#ifdef __CRT_HAVE_memset
		if __untraced((__dword & __UINT8_C(0xff)) == ((__dword >> 8) & __UINT8_C(0xff)) &&
		    (__dword & __UINT8_C(0xff)) == ((__dword >> 16) & __UINT8_C(0xff)) &&
		    (__dword & __UINT8_C(0xff)) == ((__dword >> 24) & __UINT8_C(0xff)))
			return (__UINT32_TYPE__ *)__libc_core_memset(__dst, __dword & __UINT8_C(0xff), __n_dwords * 4);
#endif /* __CRT_HAVE_memset */
	}
#endif /* !__CRT_HAVE_memsetl && (__CRT_HAVE_memsetw || __CRT_HAVE_memset) */
	return __libc_core_memsetl(__dst, __dword, __n_dwords);
}
#endif /* !__fast_memsetl_defined */


#ifndef __fast_memsetw_defined
#define __fast_memsetw_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memsetw))(/*aligned(2)*/ void *__restrict __dst,
                                         __UINT16_TYPE__ __word,
                                         __SIZE_TYPE__ __n_words) {
	if __untraced(__builtin_constant_p(__word)) {
		if __untraced(__word == 0) {
			__LIBC_FAST_NAME(bzerow)(__dst, __n_words);
			return (__UINT16_TYPE__ *)__dst;
		}
		if __untraced(__builtin_constant_p(__n_words)) {
			/* Optimizations for small data blocks (those possible with <= 2 assignments). */
			switch __untraced(__n_words) {
			case 0:
				return (__UINT16_TYPE__ *)__dst;
			case 1:
				((__UINT16_TYPE__ *)__dst)[0] = __word;
				return (__UINT16_TYPE__ *)__dst;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
			case 2:
				((__UINT16_TYPE__ *)__dst)[0] =
				((__UINT16_TYPE__ *)__dst)[1] = __word;
				return (__UINT16_TYPE__ *)__dst;
#ifndef __OPTIMIZE_SIZE__
			case 3:
				((__UINT16_TYPE__ *)__dst)[0] =
				((__UINT16_TYPE__ *)__dst)[1] =
				((__UINT16_TYPE__ *)__dst)[2] = __word;
				return (__UINT16_TYPE__ *)__dst;
			case 4:
				((__UINT16_TYPE__ *)__dst)[0] =
				((__UINT16_TYPE__ *)__dst)[1] =
				((__UINT16_TYPE__ *)__dst)[2] =
				((__UINT16_TYPE__ *)__dst)[3] = __word;
				return (__UINT16_TYPE__ *)__dst;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
			case 2:
				((__UINT32_TYPE__ *)__dst)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				return (__UINT16_TYPE__ *)__dst;
			case 3:
				((__UINT32_TYPE__ *)__dst)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				((__UINT16_TYPE__ *)__dst)[2] = __word;
				return (__UINT16_TYPE__ *)__dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
			case 4:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				return (__UINT16_TYPE__ *)__dst;
			case 5:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				((__UINT16_TYPE__ *)__dst)[4] = __word;
				return (__UINT16_TYPE__ *)__dst;
			case 6:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				return (__UINT16_TYPE__ *)__dst;
			case 8:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				return (__UINT16_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
			case 4:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				return (__UINT16_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
			case 7:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				((__UINT16_TYPE__ *)__dst)[6] = __word;
				return (__UINT16_TYPE__ *)__dst;
			case 9:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				((__UINT16_TYPE__ *)__dst)[8] = __word;
				return (__UINT16_TYPE__ *)__dst;
			case 10:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				((__UINT32_TYPE__ *)__dst)[4] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				return (__UINT16_TYPE__ *)__dst;
			case 11:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				((__UINT32_TYPE__ *)__dst)[4] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				((__UINT16_TYPE__ *)__dst)[10] = __word;
				return (__UINT16_TYPE__ *)__dst;
			case 12:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				return (__UINT16_TYPE__ *)__dst;
			case 13:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				((__UINT16_TYPE__ *)__dst)[12] = __word;
				return (__UINT16_TYPE__ *)__dst;
			case 14:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				((__UINT32_TYPE__ *)__dst)[6] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				return (__UINT16_TYPE__ *)__dst;
			case 16:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] =
				((__UINT64_TYPE__ *)__dst)[3] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				return (__UINT16_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
			case 5:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				((__UINT16_TYPE__ *)__dst)[4] = __word;
				return (__UINT16_TYPE__ *)__dst;
			case 6:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] =
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				return (__UINT16_TYPE__ *)__dst;
			case 7:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] =
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				((__UINT16_TYPE__ *)__dst)[6] = __word;
				return (__UINT16_TYPE__ *)__dst;
			case 8:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] =
				((__UINT32_TYPE__ *)__dst)[2] =
				((__UINT32_TYPE__ *)__dst)[3] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				return (__UINT16_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
			default: break;
			}
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#ifndef __OPTIMIZE_SIZE__
#if defined(__CRT_HAVE_mempsetq) && __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		void *__temp;
		__temp = __libc_core_mempsetq(__dst,
		                             (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001)),
		                              __n_words >> 2);
		switch __untraced(__n_words & 3) {
		default: break;
		case 1:
			((__UINT16_TYPE__ *)__temp)[0] = __word;
			break;
		case 2:
			((__UINT32_TYPE__ *)__temp)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
			break;
		case 3:
			((__UINT32_TYPE__ *)__temp)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
			((__UINT16_TYPE__ *)__temp)[2] = __word;
			break;
		}
		return (__UINT16_TYPE__ *)__dst;
#else /* __CRT_HAVE_mempsetq && __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		void *__temp;
		__temp = __libc_core_mempsetl(__dst,
		                             (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001)),
		                              __n_words >> 1);
		if __untraced(__n_words & 1)
			((__UINT16_TYPE__ *)__temp)[0] = __word;
		return (__UINT16_TYPE__ *)__dst;
#endif /* !__CRT_HAVE_mempsetq || __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
#if !defined(__CRT_HAVE_memsetw) && defined(__CRT_HAVE_memset)
	if __untraced(__builtin_constant_p(__word)) {
		if __untraced((__word & __UINT8_C(0xff)) == ((__word >> 8) & __UINT8_C(0xff)))
			return (__UINT16_TYPE__ *)__libc_core_memset(__dst, __word & __UINT8_C(0xff), __n_words * 2);
	}
#endif /* !__CRT_HAVE_memsetw && __CRT_HAVE_memset */
	return __libc_core_memsetw(__dst, __word, __n_words);
}
#endif /* !__fast_memsetw_defined */


#ifndef __fast_memset_defined
#define __fast_memset_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(memset))(/*aligned(1)*/ void *__restrict __dst,
                                        int __byte,
                                        __SIZE_TYPE__ __n_bytes) {
	if __untraced(__builtin_constant_p(__byte)) {
		if __untraced(__byte == 0) {
			__LIBC_FAST_NAME(bzero)(__dst, __n_bytes);
			return __dst;
		}
		if __untraced(__builtin_constant_p(__n_bytes)) {
			/* Optimizations for small data blocks (those possible with <= 2 assignments). */
			switch __untraced(__n_bytes) {
			case 0:
				return __dst;
			case 1:
				((__UINT8_TYPE__ *)__dst)[0] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return __dst;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
			case 2:
				((__UINT8_TYPE__ *)__dst)[0] = __byte;
				((__UINT8_TYPE__ *)__dst)[1] = __byte;
				return (__UINT8_TYPE__ *)__dst;
#ifndef __OPTIMIZE_SIZE__
			case 3:
				((__UINT8_TYPE__ *)__dst)[0] = __byte;
				((__UINT8_TYPE__ *)__dst)[1] = __byte;
				((__UINT8_TYPE__ *)__dst)[2] = __byte;
				return (__UINT8_TYPE__ *)__dst;
			case 4:
				((__UINT8_TYPE__ *)__dst)[0] = __byte;
				((__UINT8_TYPE__ *)__dst)[1] = __byte;
				((__UINT8_TYPE__ *)__dst)[2] = __byte;
				((__UINT8_TYPE__ *)__dst)[3] = __byte;
				return (__UINT8_TYPE__ *)__dst;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
			case 2:
				((__UINT16_TYPE__ *)__dst)[0] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				return __dst;
			case 3:
				((__UINT16_TYPE__ *)__dst)[0] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				((__UINT8_TYPE__ *)__dst)[2] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return __dst;
			case 4:
				((__UINT32_TYPE__ *)__dst)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				return __dst;
			case 5:
				((__UINT32_TYPE__ *)__dst)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT8_TYPE__ *)__dst)[4] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return __dst;
			case 6:
				((__UINT32_TYPE__ *)__dst)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT16_TYPE__ *)__dst)[2] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				return __dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
			case 8:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				return __dst;
			case 9:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT8_TYPE__ *)__dst)[8] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return __dst;
			case 10:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT16_TYPE__ *)__dst)[4] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				return __dst;
			case 12:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				return __dst;
			case 16:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				return __dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
			case 8:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				return __dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
			case 7:
				((__UINT32_TYPE__ *)__dst)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT16_TYPE__ *)__dst)[2] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				((__UINT8_TYPE__ *)__dst)[6] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return __dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
			case 11:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT16_TYPE__ *)__dst)[4] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				((__UINT8_TYPE__ *)__dst)[10] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return __dst;
			case 13:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT8_TYPE__ *)__dst)[12] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return __dst;
			case 14:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT16_TYPE__ *)__dst)[6] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				return __dst;
			case 15:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT16_TYPE__ *)__dst)[6] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				((__UINT8_TYPE__ *)__dst)[14] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return __dst;
			case 17:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT8_TYPE__ *)__dst)[16] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return __dst;
			case 18:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT16_TYPE__ *)__dst)[8] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				return __dst;
			case 19:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT16_TYPE__ *)__dst)[8] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				((__UINT8_TYPE__ *)__dst)[18] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return __dst;
			case 20:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT32_TYPE__ *)__dst)[4] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				return __dst;
			case 21:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT32_TYPE__ *)__dst)[4] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT8_TYPE__ *)__dst)[20] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return __dst;
			case 22:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT32_TYPE__ *)__dst)[4] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT16_TYPE__ *)__dst)[10] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				return __dst;
			case 24:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				return __dst;
			case 25:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT8_TYPE__ *)__dst)[24] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return __dst;
			case 26:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT16_TYPE__ *)__dst)[12] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				return __dst;
			case 28:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT32_TYPE__ *)__dst)[6] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				return __dst;
			case 32:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] =
				((__UINT64_TYPE__ *)__dst)[3] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				return __dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
			case 9:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT8_TYPE__ *)__dst)[8] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return __dst;
			case 10:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT16_TYPE__ *)__dst)[4] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				return __dst;
			case 11:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT16_TYPE__ *)__dst)[4] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				((__UINT8_TYPE__ *)__dst)[10] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return __dst;
			case 12:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] =
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				return __dst;
			case 13:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] =
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT8_TYPE__ *)__dst)[12] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return __dst;
			case 14:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] =
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT16_TYPE__ *)__dst)[6] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				return __dst;
			case 16:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] =
				((__UINT32_TYPE__ *)__dst)[2] =
				((__UINT32_TYPE__ *)__dst)[3] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				return __dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
			default: break;
			}
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#ifndef __OPTIMIZE_SIZE__
		/* With the fill-value known, split the call into 2:
		 * >> memset(p, 0x12, s);
		 * Compiled as one of:
		 * >> memset(mempsetl(p, 0x12121212, s >> 2), 0x12, s & 3);
		 * >> memset(mempsetq(p, 0x1212121212121212, s >> 3), 0x12, s & 7);
		 */
#if defined(__CRT_HAVE_mempsetq) && __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		void *__temp;
		__temp = __libc_core_mempsetq(__dst,
		                             (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101)),
		                              __n_bytes >> 3);
		switch __untraced(__n_bytes & 7) {
		default: break;
		case 1:
			((__UINT8_TYPE__ *)__temp)[0] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
			break;
		case 2:
			((__UINT16_TYPE__ *)__temp)[0] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
			break;
		case 3:
			((__UINT16_TYPE__ *)__temp)[0] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
			((__UINT8_TYPE__ *)__temp)[2] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
			break;
		case 4:
			((__UINT32_TYPE__ *)__temp)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
			break;
		case 5:
			((__UINT32_TYPE__ *)__temp)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
			((__UINT8_TYPE__ *)__temp)[4] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
			break;
		case 6:
			((__UINT32_TYPE__ *)__temp)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
			((__UINT16_TYPE__ *)__temp)[2] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
			break;
		case 7:
			((__UINT32_TYPE__ *)__temp)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
			((__UINT16_TYPE__ *)__temp)[2] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
			((__UINT8_TYPE__ *)__temp)[6] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
			break;
		}
		return __dst;
#else /* __CRT_HAVE_mempsetq && __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		void *__temp;
		__temp = __libc_core_mempsetl(__dst,
		                             (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101)),
		                              __n_bytes >> 2);
		switch __untraced(__n_bytes & 3) {
		default: break;
		case 1:
			((__UINT8_TYPE__ *)__temp)[0] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
			break;
		case 2:
			((__UINT16_TYPE__ *)__temp)[0] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
			break;
		case 3:
			((__UINT16_TYPE__ *)__temp)[0] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
			((__UINT8_TYPE__ *)__temp)[2] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
			break;
		}
		return __dst;
#endif /* !__CRT_HAVE_mempsetq || __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_memset(__dst, __byte, __n_bytes);
}
#endif /* !__fast_memset_defined */


#ifdef __UINT64_TYPE__
#ifndef __fast_mempsetq_defined
#define __fast_mempsetq_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempsetq))(/*aligned(8)*/ void *__restrict __dst,
                                          __UINT64_TYPE__ __qword,
                                          __SIZE_TYPE__ __n_qwords) {
	if __untraced(__builtin_constant_p(__qword)) {
		if __untraced(__qword == 0) {
			__LIBC_FAST_NAME(bzeroq)(__dst, __n_qwords);
			return (__UINT64_TYPE__ *)__dst + __n_qwords;
		}
		if __untraced(__builtin_constant_p(__n_qwords)) {
			/* Optimizations for small data blocks (those possible with <= 2 assignments). */
			switch __untraced(__n_qwords) {
			case 0:
				return (__UINT64_TYPE__ *)__dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
			case 1:
				((__UINT64_TYPE__ *)__dst)[0] = __qword;
				return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
			case 2:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = __qword;
				return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
			case 1:
				((__UINT64_TYPE__ *)__dst)[0] = __qword;
				return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
			case 3:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] = __qword;
				return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 24);
			case 4:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] =
				((__UINT64_TYPE__ *)__dst)[3] = __qword;
				return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 32);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
			case 2:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = __qword;
				return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
			default: break;
			}
		}
	}
#if !defined(__CRT_HAVE_memsetq) && !defined(__CRT_HAVE_mempsetq) && \
    (defined(__CRT_HAVE_memsetl) || defined(__CRT_HAVE_memsetw) || defined(__CRT_HAVE_memset) || \
     defined(__CRT_HAVE_mempsetl) || defined(__CRT_HAVE_mempsetw) || defined(__CRT_HAVE_mempset))
	if __untraced(__builtin_constant_p(__qword)) {
#if defined(__CRT_HAVE_memsetl) || defined(__CRT_HAVE_mempsetl)
		if __untraced((__qword & __UINT32_C(0xffffffff)) == ((__qword >> 32) & __UINT32_C(0xffffffff)))
			return (__UINT64_TYPE__ *)__libc_core_mempsetl(__dst, __qword & __UINT32_C(0xffffffff), __n_qwords * 2);
#endif /* __CRT_HAVE_memsetl || __CRT_HAVE_mempsetl */
#if defined(__CRT_HAVE_memsetw) || defined(__CRT_HAVE_mempsetw)
		if __untraced((__qword & __UINT16_C(0xffff)) == ((__qword >> 16) & __UINT16_C(0xffff)) &&
		    (__qword & __UINT16_C(0xffff)) == ((__qword >> 32) & __UINT16_C(0xffff)) &&
		    (__qword & __UINT16_C(0xffff)) == ((__qword >> 48) & __UINT16_C(0xffff)))
			return (__UINT64_TYPE__ *)__libc_core_mempsetw(__dst, __qword & __UINT16_C(0xffff), __n_qwords * 4);
#endif /* __CRT_HAVE_memsetw || __CRT_HAVE_mempsetw */
#if defined(__CRT_HAVE_memset) || defined(__CRT_HAVE_mempset)
		if __untraced((__qword & __UINT8_C(0xff)) == ((__qword >> 8) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 16) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 24) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 32) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 40) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 48) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 56) & __UINT8_C(0xff)))
			return (__UINT64_TYPE__ *)__libc_core_mempset(__dst, __qword & __UINT8_C(0xff), __n_qwords * 8);
#endif /* __CRT_HAVE_memset || __CRT_HAVE_mempset */
	}
#elif (defined(__CRT_HAVE_memsetl) || defined(__CRT_HAVE_mempsetl)) && __SIZEOF_BUSINT__ < 8
	if __untraced(__builtin_constant_p(__qword) &&
	   (__qword & __UINT32_C(0xffffffff)) == ((__qword >> 32) & __UINT32_C(0xffffffff)))
		return (__UINT64_TYPE__ *)__libc_core_mempsetl(__dst, __qword & __UINT32_C(0xffffffff), __n_qwords * 2);
#endif /* !__CRT_HAVE_memsetq && ... */
	return __libc_core_mempsetq(__dst, __qword, __n_qwords);
}
#endif /* !__fast_mempsetq_defined */
#endif /* __UINT64_TYPE__ */


#ifndef __fast_mempsetl_defined
#define __fast_mempsetl_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempsetl))(/*aligned(4)*/ void *__restrict __dst,
                                          __UINT32_TYPE__ __dword,
                                          __SIZE_TYPE__ __n_dwords) {
	if __untraced(__builtin_constant_p(__dword)) {
		if __untraced(__dword == 0) {
			__LIBC_FAST_NAME(bzerol)(__dst, __n_dwords);
			return (__UINT32_TYPE__ *)__dst + __n_dwords;
		}
		if __untraced(__builtin_constant_p(__n_dwords)) {
			/* Optimizations for small data blocks (those possible with <= 2 assignments). */
			switch __untraced(__n_dwords) {
			case 0:
				return (__UINT32_TYPE__ *)__dst;
			case 1:
				((__UINT32_TYPE__ *)__dst)[0] = __dword;
				return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 4);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
			case 2:
				((__UINT32_TYPE__ *)__dst)[0] = __dword;
				((__UINT32_TYPE__ *)__dst)[1] = __dword;
				return (__UINT32_TYPE__ *)__dst + 2;
#ifndef __OPTIMIZE_SIZE__
			case 3:
				((__UINT32_TYPE__ *)__dst)[0] = __dword;
				((__UINT32_TYPE__ *)__dst)[1] = __dword;
				((__UINT32_TYPE__ *)__dst)[2] = __dword;
				return (__UINT32_TYPE__ *)__dst + 3;
			case 4:
				((__UINT32_TYPE__ *)__dst)[0] = __dword;
				((__UINT32_TYPE__ *)__dst)[1] = __dword;
				((__UINT32_TYPE__ *)__dst)[2] = __dword;
				((__UINT32_TYPE__ *)__dst)[3] = __dword;
				return (__UINT32_TYPE__ *)__dst + 4;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
			case 2:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)__dword * __UINT64_C(0x0000000100000001));
				return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
			case 3:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)__dword * __UINT64_C(0x0000000100000001));
				((__UINT32_TYPE__ *)__dst)[2] = __dword;
				return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 12);
			case 4:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)__dword * __UINT64_C(0x0000000100000001));
				return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
			case 2:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] = __dword;
				return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
			case 5:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)__dword * __UINT64_C(0x0000000100000001));
				((__UINT32_TYPE__ *)__dst)[4] = __dword;
				return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 20);
			case 6:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] = (__UINT64_TYPE__)((__UINT64_TYPE__)__dword * __UINT64_C(0x0000000100000001));
				return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 24);
			case 7:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] = (__UINT64_TYPE__)((__UINT64_TYPE__)__dword * __UINT64_C(0x0000000100000001));
				((__UINT32_TYPE__ *)__dst)[6] = __dword;
				return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 28);
			case 8:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] =
				((__UINT64_TYPE__ *)__dst)[3] = (__UINT64_TYPE__)((__UINT64_TYPE__)__dword * __UINT64_C(0x0000000100000001));
				return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 32);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
			case 3:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] =
				((__UINT32_TYPE__ *)__dst)[2] = __dword;
				return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 12);
			case 4:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] =
				((__UINT32_TYPE__ *)__dst)[2] =
				((__UINT32_TYPE__ *)__dst)[3] = __dword;
				return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
			default: break;
			}
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#ifndef __OPTIMIZE_SIZE__
		/* With the fill-value known, split the call into 2:
		 * >> mempset(p, 0x12, s);
		 * Compiled as one of:
		 * >> mempset(mempsetl(p, 0x12121212, s >> 2), 0x12, s & 3);
		 * >> mempset(mempsetq(p, 0x1212121212121212, s >> 3), 0x12, s & 7);
		 */
#if defined(__CRT_HAVE_mempsetq) && __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		__dst = __libc_core_mempsetq(__dst,
		                            (__UINT64_TYPE__)((__UINT64_TYPE__)__dword * __UINT64_C(0x0000000100000001)),
		                             __n_dwords >> 1);
		if __untraced(__n_dwords & 1) {
			((__UINT16_TYPE__ *)__dst)[0] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__dword & __UINT8_C(0xff)) * __UINT16_C(0x0101));
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 2);
		}
		return (__UINT32_TYPE__ *)__dst;
#endif /* __CRT_HAVE_mempsetq && __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
#if !defined(__CRT_HAVE_memsetl) && !defined(__CRT_HAVE_mempsetl) && \
    (defined(__CRT_HAVE_memsetw) || defined(__CRT_HAVE_memset) || \
     defined(__CRT_HAVE_mempsetw) || defined(__CRT_HAVE_mempset))
	if __untraced(__builtin_constant_p(__dword)) {
#if defined(__CRT_HAVE_memsetw) || defined(__CRT_HAVE_mempsetw)
		if __untraced((__dword & __UINT16_C(0xffff)) == ((__dword >> 16) & __UINT16_C(0xffff)))
			return (__UINT32_TYPE__ *)__libc_core_mempsetw(__dst, __dword & __UINT16_C(0xffff), __n_dwords * 2);
#endif /* __CRT_HAVE_memsetw || __CRT_HAVE_mempsetw */
#if defined(__CRT_HAVE_memset) || defined(__CRT_HAVE_mempset)
		if __untraced((__dword & __UINT8_C(0xff)) == ((__dword >> 8) & __UINT8_C(0xff)) &&
		    (__dword & __UINT8_C(0xff)) == ((__dword >> 16) & __UINT8_C(0xff)) &&
		    (__dword & __UINT8_C(0xff)) == ((__dword >> 24) & __UINT8_C(0xff)))
			return (__UINT32_TYPE__ *)__libc_core_mempset(__dst, __dword & __UINT8_C(0xff), __n_dwords * 4);
#endif /* __CRT_HAVE_memset || __CRT_HAVE_mempset */
	}
#endif /* !__CRT_HAVE_memsetl && ... */
	return __libc_core_mempsetl(__dst, __dword, __n_dwords);
}
#endif /* !__fast_mempsetl_defined */


#ifndef __fast_mempsetw_defined
#define __fast_mempsetw_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempsetw))(/*aligned(2)*/ void *__restrict __dst,
                                          __UINT16_TYPE__ __word,
                                          __SIZE_TYPE__ __n_words) {
	if __untraced(__builtin_constant_p(__word)) {
		if __untraced(__word == 0) {
			__LIBC_FAST_NAME(bzerow)(__dst, __n_words);
			return (__UINT16_TYPE__ *)__dst + __n_words;
		}
		if __untraced(__builtin_constant_p(__n_words)) {
			/* Optimizations for small data blocks (those possible with <= 2 assignments). */
			switch __untraced(__n_words) {
			case 0:
				return (__UINT16_TYPE__ *)__dst;
			case 1:
				((__UINT16_TYPE__ *)__dst)[0] = __word;
				return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 2);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
			case 2:
				((__UINT16_TYPE__ *)__dst)[0] = __word;
				((__UINT16_TYPE__ *)__dst)[1] = __word;
				return (__UINT16_TYPE__ *)__dst + 2;
#ifndef __OPTIMIZE_SIZE__
			case 3:
				((__UINT16_TYPE__ *)__dst)[0] = __word;
				((__UINT16_TYPE__ *)__dst)[1] = __word;
				((__UINT16_TYPE__ *)__dst)[2] = __word;
				return (__UINT16_TYPE__ *)__dst + 3;
			case 4:
				((__UINT16_TYPE__ *)__dst)[0] = __word;
				((__UINT16_TYPE__ *)__dst)[1] = __word;
				((__UINT16_TYPE__ *)__dst)[2] = __word;
				((__UINT16_TYPE__ *)__dst)[3] = __word;
				return (__UINT16_TYPE__ *)__dst + 4;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
			case 2:
				((__UINT32_TYPE__ *)__dst)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 4);
			case 3:
				((__UINT32_TYPE__ *)__dst)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				((__UINT16_TYPE__ *)__dst)[2] = __word;
				return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 6);
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
			case 4:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
			case 5:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				((__UINT16_TYPE__ *)__dst)[4] = __word;
				return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 10);
			case 6:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 12);
			case 8:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
			case 4:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
			case 7:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				((__UINT16_TYPE__ *)__dst)[6] = __word;
				return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 14);
			case 9:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				((__UINT16_TYPE__ *)__dst)[8] = __word;
				return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 18);
			case 10:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				((__UINT32_TYPE__ *)__dst)[4] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 20);
			case 11:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				((__UINT32_TYPE__ *)__dst)[4] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				((__UINT16_TYPE__ *)__dst)[10] = __word;
				return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 22);
			case 12:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 24);
			case 13:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				((__UINT16_TYPE__ *)__dst)[12] = __word;
				return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 26);
			case 14:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				((__UINT32_TYPE__ *)__dst)[6] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 28);
			case 16:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] =
				((__UINT64_TYPE__ *)__dst)[3] = (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001));
				return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 32);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
			case 5:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				((__UINT16_TYPE__ *)__dst)[4] = __word;
				return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 10);
			case 6:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] =
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 12);
			case 7:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] =
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				((__UINT16_TYPE__ *)__dst)[6] = __word;
				return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 14);
			case 8:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] =
				((__UINT32_TYPE__ *)__dst)[2] =
				((__UINT32_TYPE__ *)__dst)[3] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
				return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
			default: break;
			}
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#ifndef __OPTIMIZE_SIZE__
		/* With the fill-value known, split the call into 2:
		 * >> mempset(p, 0x12, s);
		 * Compiled as one of:
		 * >> mempset(mempsetl(p, 0x12121212, s >> 2), 0x12, s & 3);
		 * >> mempset(mempsetq(p, 0x1212121212121212, s >> 3), 0x12, s & 7);
		 */
#if defined(__CRT_HAVE_mempsetq) && __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		__dst = __libc_core_mempsetq(__dst,
		                            (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001)),
		                             __n_words >> 2);
		switch __untraced(__n_words & 3) {
		default: break;
		case 1:
			((__UINT16_TYPE__ *)__dst)[0] = __word;
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 2);
		case 2:
			((__UINT32_TYPE__ *)__dst)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 4);
		case 3:
			((__UINT32_TYPE__ *)__dst)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001));
			((__UINT16_TYPE__ *)__dst)[2] = __word;
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 6);
		}
		return (__UINT16_TYPE__ *)__dst;
#else /* __CRT_HAVE_mempsetq && __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		__dst = __libc_core_mempsetl(__dst,
		                            (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001)),
		                             __n_words >> 1);
		if __untraced(__n_words & 1) {
			((__UINT16_TYPE__ *)__dst)[0] = __word;
			return (__UINT16_TYPE__ *)__dst + 1;
		}
		return (__UINT16_TYPE__ *)__dst;
#endif /* !__CRT_HAVE_mempsetq || __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
#if !defined(__CRT_HAVE_memsetw) && !defined(__CRT_HAVE_mempsetw) && \
    (defined(__CRT_HAVE_memset) || defined(__CRT_HAVE_mempset))
	if __untraced(__builtin_constant_p(__word)) {
		if __untraced((__word & __UINT8_C(0xff)) == ((__word >> 8) & __UINT8_C(0xff)))
			return (__UINT16_TYPE__ *)__libc_core_mempset(__dst, __word & __UINT8_C(0xff), __n_words * 2);
	}
#endif /* !__CRT_HAVE_memsetw && ... */
	return __libc_core_mempsetw(__dst, __word, __n_words);
}
#endif /* !__fast_mempsetw_defined */


#ifndef __fast_mempset_defined
#define __fast_mempset_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempset))(/*aligned(1)*/ void *__restrict __dst,
                                         int __byte,
                                         __SIZE_TYPE__ __n_bytes) {
	if __untraced(__builtin_constant_p(__byte)) {
		if __untraced(__byte == 0) {
			__LIBC_FAST_NAME(bzero)(__dst, __n_bytes);
			return (__UINT8_TYPE__ *)__dst + __n_bytes;
		}
		if __untraced(__builtin_constant_p(__n_bytes)) {
			/* Optimizations for small data blocks (those possible with <= 2 assignments). */
			switch __untraced(__n_bytes) {
			case 0:
				return __dst;
			case 1:
				((__UINT8_TYPE__ *)__dst)[0] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return (__UINT8_TYPE__ *)__dst + 1;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
			case 2:
				((__UINT8_TYPE__ *)__dst)[0] = __byte;
				((__UINT8_TYPE__ *)__dst)[1] = __byte;
				return (__UINT8_TYPE__ *)__dst + 2;
#ifndef __OPTIMIZE_SIZE__
			case 3:
				((__UINT8_TYPE__ *)__dst)[0] = __byte;
				((__UINT8_TYPE__ *)__dst)[1] = __byte;
				((__UINT8_TYPE__ *)__dst)[2] = __byte;
				return (__UINT8_TYPE__ *)__dst + 3;
			case 4:
				((__UINT8_TYPE__ *)__dst)[0] = __byte;
				((__UINT8_TYPE__ *)__dst)[1] = __byte;
				((__UINT8_TYPE__ *)__dst)[2] = __byte;
				((__UINT8_TYPE__ *)__dst)[3] = __byte;
				return (__UINT8_TYPE__ *)__dst + 4;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
			case 2:
				((__UINT16_TYPE__ *)__dst)[0] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				return (__UINT8_TYPE__ *)__dst + 2;
			case 3:
				((__UINT16_TYPE__ *)__dst)[0] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				((__UINT8_TYPE__ *)__dst)[2] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return (__UINT8_TYPE__ *)__dst + 3;
			case 4:
				((__UINT32_TYPE__ *)__dst)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				return (__UINT8_TYPE__ *)__dst + 4;
			case 5:
				((__UINT32_TYPE__ *)__dst)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT8_TYPE__ *)__dst)[4] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return (__UINT8_TYPE__ *)__dst + 5;
			case 6:
				((__UINT32_TYPE__ *)__dst)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT16_TYPE__ *)__dst)[2] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				return (__UINT8_TYPE__ *)__dst + 6;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
			case 8:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				return (__UINT8_TYPE__ *)__dst + 8;
			case 9:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT8_TYPE__ *)__dst)[8] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return (__UINT8_TYPE__ *)__dst + 9;
			case 10:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT16_TYPE__ *)__dst)[4] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				return (__UINT8_TYPE__ *)__dst + 10;
			case 12:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				return (__UINT8_TYPE__ *)__dst + 12;
			case 16:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				return (__UINT8_TYPE__ *)__dst + 16;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
			case 8:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				return (__UINT8_TYPE__ *)__dst + 8;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
			case 7:
				((__UINT32_TYPE__ *)__dst)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT16_TYPE__ *)__dst)[2] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				((__UINT8_TYPE__ *)__dst)[6] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return (__UINT8_TYPE__ *)__dst + 7;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
			case 11:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT16_TYPE__ *)__dst)[4] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				((__UINT8_TYPE__ *)__dst)[10] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return (__UINT8_TYPE__ *)__dst + 11;
			case 13:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT8_TYPE__ *)__dst)[12] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return (__UINT8_TYPE__ *)__dst + 13;
			case 14:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT16_TYPE__ *)__dst)[6] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				return (__UINT8_TYPE__ *)__dst + 14;
			case 15:
				((__UINT64_TYPE__ *)__dst)[0] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT16_TYPE__ *)__dst)[6] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				((__UINT8_TYPE__ *)__dst)[14] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return (__UINT8_TYPE__ *)__dst + 15;
			case 17:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT8_TYPE__ *)__dst)[16] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return (__UINT8_TYPE__ *)__dst + 17;
			case 18:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT16_TYPE__ *)__dst)[8] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				return (__UINT8_TYPE__ *)__dst + 18;
			case 19:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT16_TYPE__ *)__dst)[8] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				((__UINT8_TYPE__ *)__dst)[18] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return (__UINT8_TYPE__ *)__dst + 19;
			case 20:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT32_TYPE__ *)__dst)[4] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				return (__UINT8_TYPE__ *)__dst + 20;
			case 21:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT32_TYPE__ *)__dst)[4] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT8_TYPE__ *)__dst)[20] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return (__UINT8_TYPE__ *)__dst + 21;
			case 22:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT32_TYPE__ *)__dst)[4] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT16_TYPE__ *)__dst)[10] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				return (__UINT8_TYPE__ *)__dst + 22;
			case 24:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				return (__UINT8_TYPE__ *)__dst + 24;
			case 25:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT8_TYPE__ *)__dst)[24] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return (__UINT8_TYPE__ *)__dst + 25;
			case 26:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT16_TYPE__ *)__dst)[12] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				return (__UINT8_TYPE__ *)__dst + 26;
			case 28:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				((__UINT32_TYPE__ *)__dst)[6] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				return (__UINT8_TYPE__ *)__dst + 28;
			case 32:
				((__UINT64_TYPE__ *)__dst)[0] =
				((__UINT64_TYPE__ *)__dst)[1] =
				((__UINT64_TYPE__ *)__dst)[2] =
				((__UINT64_TYPE__ *)__dst)[3] = (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101));
				return (__UINT8_TYPE__ *)__dst + 32;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
			case 9:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT8_TYPE__ *)__dst)[8] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return (__UINT8_TYPE__ *)__dst + 9;
			case 10:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT16_TYPE__ *)__dst)[4] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				return (__UINT8_TYPE__ *)__dst + 10;
			case 11:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT16_TYPE__ *)__dst)[4] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				((__UINT8_TYPE__ *)__dst)[10] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return (__UINT8_TYPE__ *)__dst + 11;
			case 12:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] =
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				return (__UINT8_TYPE__ *)__dst + 12;
			case 13:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] =
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT8_TYPE__ *)__dst)[12] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return (__UINT8_TYPE__ *)__dst + 13;
			case 14:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] =
				((__UINT32_TYPE__ *)__dst)[2] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				((__UINT16_TYPE__ *)__dst)[6] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
				return (__UINT8_TYPE__ *)__dst + 14;
			case 16:
				((__UINT32_TYPE__ *)__dst)[0] =
				((__UINT32_TYPE__ *)__dst)[1] =
				((__UINT32_TYPE__ *)__dst)[2] =
				((__UINT32_TYPE__ *)__dst)[3] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
				return (__UINT8_TYPE__ *)__dst + 16;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
			default: break;
			}
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#ifndef __OPTIMIZE_SIZE__
		/* With the fill-value known, split the call into 2:
		 * >> mempset(p, 0x12, s);
		 * Compiled as one of:
		 * >> mempset(mempsetl(p, 0x12121212, s >> 2), 0x12, s & 3);
		 * >> mempset(mempsetq(p, 0x1212121212121212, s >> 3), 0x12, s & 7);
		 */
#if defined(__CRT_HAVE_mempsetq) && __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		__dst = __libc_core_mempsetq(__dst,
		                            (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101)),
		                             __n_bytes >> 3);
		switch __untraced(__n_bytes & 7) {
		default: break;
		case 1:
			((__UINT8_TYPE__ *)__dst)[0] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
			return (__UINT8_TYPE__ *)__dst + 1;
		case 2:
			((__UINT16_TYPE__ *)__dst)[0] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
			return (__UINT8_TYPE__ *)__dst + 2;
		case 3:
			((__UINT16_TYPE__ *)__dst)[0] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
			((__UINT8_TYPE__ *)__dst)[2] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
			return (__UINT8_TYPE__ *)__dst + 3;
		case 4:
			((__UINT32_TYPE__ *)__dst)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
			return (__UINT8_TYPE__ *)__dst + 4;
		case 5:
			((__UINT32_TYPE__ *)__dst)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
			((__UINT8_TYPE__ *)__dst)[4] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
			return (__UINT8_TYPE__ *)__dst + 5;
		case 6:
			((__UINT32_TYPE__ *)__dst)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
			((__UINT16_TYPE__ *)__dst)[2] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
			return (__UINT8_TYPE__ *)__dst + 6;
		case 7:
			((__UINT32_TYPE__ *)__dst)[0] = (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101));
			((__UINT16_TYPE__ *)__dst)[2] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
			((__UINT8_TYPE__ *)__dst)[6] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
			return (__UINT8_TYPE__ *)__dst + 7;
		}
		return __dst;
#else /* __CRT_HAVE_mempsetq && __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		__dst = __libc_core_mempsetl(__dst,
		                            (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101)),
		                             __n_bytes >> 2);
		switch __untraced(__n_bytes & 3) {
		default: break;
		case 1:
			((__UINT8_TYPE__ *)__dst)[0] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
			return (__UINT8_TYPE__ *)__dst + 1;
		case 2:
			((__UINT16_TYPE__ *)__dst)[0] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
			return (__UINT8_TYPE__ *)__dst + 2;
		case 3:
			((__UINT16_TYPE__ *)__dst)[0] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT16_C(0x0101));
			((__UINT8_TYPE__ *)__dst)[2] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
			return (__UINT8_TYPE__ *)__dst + 3;
		}
		return __dst;
#endif /* !__CRT_HAVE_mempsetq || __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_mempset(__dst, __byte, __n_bytes);
}
#endif /* !__fast_mempset_defined */

#ifndef __fast_memchr_defined
#define __fast_memchr_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(memchr))(/*aligned(1)*/ void const *__restrict __haystack,
                                        int __needle, __SIZE_TYPE__ __n_bytes) {
	if __untraced(__builtin_constant_p(__n_bytes)) {
		switch __untraced(__n_bytes) {
		case 0:
			return __NULLPTR;
		case 1:
			if __untraced(((__UINT8_TYPE__ *)__haystack)[0] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 0;
			return __NULLPTR;
		case 2:
			if __untraced(((__UINT8_TYPE__ *)__haystack)[0] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 0;
			if __untraced(((__UINT8_TYPE__ *)__haystack)[1] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 1;
			return __NULLPTR;
		case 3:
			if __untraced(((__UINT8_TYPE__ *)__haystack)[0] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 0;
			if __untraced(((__UINT8_TYPE__ *)__haystack)[1] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 1;
			if __untraced(((__UINT8_TYPE__ *)__haystack)[2] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 2;
			return __NULLPTR;
		case 4:
			if __untraced(((__UINT8_TYPE__ *)__haystack)[0] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 0;
			if __untraced(((__UINT8_TYPE__ *)__haystack)[1] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 1;
			if __untraced(((__UINT8_TYPE__ *)__haystack)[2] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 2;
			if __untraced(((__UINT8_TYPE__ *)__haystack)[3] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 3;
			return __NULLPTR;
		default: break;
		}
	}
	return __libc_core_memchr(__haystack, __needle, __n_bytes);
}
#endif /* !__fast_memchr_defined */

#ifndef __fast_memchrw_defined
#define __fast_memchrw_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memchrw))(/*aligned(2)*/ void const *__restrict __haystack,
                                         __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) {
	if __untraced(__builtin_constant_p(__n_words)) {
		switch __untraced(__n_words) {
		case 0:
			return __NULLPTR;
		case 1:
			if __untraced(((__UINT16_TYPE__ *)__haystack)[0] == __word)
				return (__UINT16_TYPE__ *)__haystack + 0;
			return __NULLPTR;
		case 2:
			if __untraced(((__UINT16_TYPE__ *)__haystack)[0] == __word)
				return (__UINT16_TYPE__ *)__haystack + 0;
			if __untraced(((__UINT16_TYPE__ *)__haystack)[1] == __word)
				return (__UINT16_TYPE__ *)__haystack + 1;
			return __NULLPTR;
		case 3:
			if __untraced(((__UINT16_TYPE__ *)__haystack)[0] == __word)
				return (__UINT16_TYPE__ *)__haystack + 0;
			if __untraced(((__UINT16_TYPE__ *)__haystack)[1] == __word)
				return (__UINT16_TYPE__ *)__haystack + 1;
			if __untraced(((__UINT16_TYPE__ *)__haystack)[2] == __word)
				return (__UINT16_TYPE__ *)__haystack + 2;
			return __NULLPTR;
		case 4:
			if __untraced(((__UINT16_TYPE__ *)__haystack)[0] == __word)
				return (__UINT16_TYPE__ *)__haystack + 0;
			if __untraced(((__UINT16_TYPE__ *)__haystack)[1] == __word)
				return (__UINT16_TYPE__ *)__haystack + 1;
			if __untraced(((__UINT16_TYPE__ *)__haystack)[2] == __word)
				return (__UINT16_TYPE__ *)__haystack + 2;
			if __untraced(((__UINT16_TYPE__ *)__haystack)[3] == __word)
				return (__UINT16_TYPE__ *)__haystack + 3;
			return __NULLPTR;
		default: break;
		}
	}
	return __libc_core_memchrw(__haystack, __word, __n_words);
}
#endif /* !__fast_memchrw_defined */

#ifndef __fast_memchrl_defined
#define __fast_memchrl_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memchrl))(/*aligned(4)*/ void const *__restrict __haystack,
                                         __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) {
	if __untraced(__builtin_constant_p(__n_dwords)) {
		switch __untraced(__n_dwords) {
		case 0:
			return __NULLPTR;
		case 1:
			if __untraced(((__UINT32_TYPE__ *)__haystack)[0] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 0;
			return __NULLPTR;
		case 2:
			if __untraced(((__UINT32_TYPE__ *)__haystack)[0] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 0;
			if __untraced(((__UINT32_TYPE__ *)__haystack)[1] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 1;
			return __NULLPTR;
		case 3:
			if __untraced(((__UINT32_TYPE__ *)__haystack)[0] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 0;
			if __untraced(((__UINT32_TYPE__ *)__haystack)[1] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 1;
			if __untraced(((__UINT32_TYPE__ *)__haystack)[2] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 2;
			return __NULLPTR;
		case 4:
			if __untraced(((__UINT32_TYPE__ *)__haystack)[0] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 0;
			if __untraced(((__UINT32_TYPE__ *)__haystack)[1] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 1;
			if __untraced(((__UINT32_TYPE__ *)__haystack)[2] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 2;
			if __untraced(((__UINT32_TYPE__ *)__haystack)[3] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 3;
			return __NULLPTR;
		default: break;
		}
	}
	return __libc_core_memchrl(__haystack, __dword, __n_dwords);
}
#endif /* !__fast_memchrl_defined */

#ifndef __fast_memchrq_defined
#define __fast_memchrq_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memchrq))(/*aligned(8)*/ void const *__restrict __haystack,
                                         __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) {
	if __untraced(__builtin_constant_p(__n_qwords)) {
		switch __untraced(__n_qwords) {
		case 0:
			return __NULLPTR;
		case 1:
			if __untraced(((__UINT64_TYPE__ *)__haystack)[0] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 0;
			return __NULLPTR;
		case 2:
			if __untraced(((__UINT64_TYPE__ *)__haystack)[0] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 0;
			if __untraced(((__UINT64_TYPE__ *)__haystack)[1] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 1;
			return __NULLPTR;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 3:
			if __untraced(((__UINT64_TYPE__ *)__haystack)[0] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 0;
			if __untraced(((__UINT64_TYPE__ *)__haystack)[1] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 1;
			if __untraced(((__UINT64_TYPE__ *)__haystack)[2] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 2;
			return __NULLPTR;
		case 4:
			if __untraced(((__UINT64_TYPE__ *)__haystack)[0] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 0;
			if __untraced(((__UINT64_TYPE__ *)__haystack)[1] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 1;
			if __untraced(((__UINT64_TYPE__ *)__haystack)[2] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 2;
			if __untraced(((__UINT64_TYPE__ *)__haystack)[3] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 3;
			return __NULLPTR;
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		default: break;
		}
	}
	return __libc_core_memchrq(__haystack, __qword, __n_qwords);
}
#endif /* !__fast_memchrq_defined */

#ifndef __fast_memrchr_defined
#define __fast_memrchr_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(memrchr))(/*aligned(1)*/ void const *__restrict __haystack,
                                         int __needle, __SIZE_TYPE__ __n_bytes) {
	if __untraced(__builtin_constant_p(__n_bytes)) {
		switch __untraced(__n_bytes) {
		case 4:
			if __untraced(((__UINT8_TYPE__ *)__haystack)[3] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 3;
			__ATTR_FALLTHROUGH
		case 3:
			if __untraced(((__UINT8_TYPE__ *)__haystack)[2] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 2;
			__ATTR_FALLTHROUGH
		case 2:
			if __untraced(((__UINT8_TYPE__ *)__haystack)[1] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 1;
			__ATTR_FALLTHROUGH
		case 1:
			if __untraced(((__UINT8_TYPE__ *)__haystack)[0] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 0;
			__ATTR_FALLTHROUGH
		case 0:
			return __NULLPTR;
		default: break;
		}
	}
	return __libc_core_memrchr(__haystack, __needle, __n_bytes);
}
#endif /* !__fast_memrchr_defined */

#ifndef __fast_memrchrw_defined
#define __fast_memrchrw_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memrchrw))(/*aligned(2)*/ void const *__restrict __haystack,
                                          __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) {
	if __untraced(__builtin_constant_p(__n_words)) {
		switch __untraced(__n_words) {
		case 4:
			if __untraced(((__UINT16_TYPE__ *)__haystack)[3] == __word)
				return (__UINT16_TYPE__ *)__haystack + 3;
			__ATTR_FALLTHROUGH
		case 3:
			if __untraced(((__UINT16_TYPE__ *)__haystack)[2] == __word)
				return (__UINT16_TYPE__ *)__haystack + 2;
			__ATTR_FALLTHROUGH
		case 2:
			if __untraced(((__UINT16_TYPE__ *)__haystack)[1] == __word)
				return (__UINT16_TYPE__ *)__haystack + 1;
			__ATTR_FALLTHROUGH
		case 1:
			if __untraced(((__UINT16_TYPE__ *)__haystack)[0] == __word)
				return (__UINT16_TYPE__ *)__haystack + 0;
			__ATTR_FALLTHROUGH
		case 0:
			return __NULLPTR;
		default: break;
		}
	}
	return __libc_core_memrchrw(__haystack, __word, __n_words);
}
#endif /* !__fast_memrchrw_defined */

#ifndef __fast_memrchrl_defined
#define __fast_memrchrl_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memrchrl))(/*aligned(4)*/ void const *__restrict __haystack,
                                          __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) {
	if __untraced(__builtin_constant_p(__n_dwords)) {
		switch __untraced(__n_dwords) {
		case 4:
			if __untraced(((__UINT32_TYPE__ *)__haystack)[3] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 3;
			__ATTR_FALLTHROUGH
		case 3:
			if __untraced(((__UINT32_TYPE__ *)__haystack)[2] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 2;
			__ATTR_FALLTHROUGH
		case 2:
			if __untraced(((__UINT32_TYPE__ *)__haystack)[1] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 1;
			__ATTR_FALLTHROUGH
		case 1:
			if __untraced(((__UINT32_TYPE__ *)__haystack)[0] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 0;
			__ATTR_FALLTHROUGH
		case 0:
			return __NULLPTR;
		default: break;
		}
	}
	return __libc_core_memrchrl(__haystack, __dword, __n_dwords);
}
#endif /* !__fast_memrchrl_defined */

#ifndef __fast_memrchrq_defined
#define __fast_memrchrq_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memrchrq))(/*aligned(8)*/ void const *__restrict __haystack,
                                          __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) {
	if __untraced(__builtin_constant_p(__n_qwords)) {
		switch __untraced(__n_qwords) {
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 4:
			if __untraced(((__UINT64_TYPE__ *)__haystack)[3] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 3;
			__ATTR_FALLTHROUGH
		case 3:
			if __untraced(((__UINT64_TYPE__ *)__haystack)[2] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 2;
			__ATTR_FALLTHROUGH
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 2:
			if __untraced(((__UINT64_TYPE__ *)__haystack)[1] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 1;
			__ATTR_FALLTHROUGH
		case 1:
			if __untraced(((__UINT64_TYPE__ *)__haystack)[0] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 0;
			__ATTR_FALLTHROUGH
		case 0:
			return __NULLPTR;
		default: break;
		}
	}
	return __libc_core_memrchrq(__haystack, __qword, __n_qwords);
}
#endif /* !__fast_memrchrq_defined */

#ifndef __fast_memcmp_defined
#define __fast_memcmp_defined
#include <hybrid/byteorder.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBC_FAST_NAME(memcmp))(/*aligned(1)*/ void const *__restrict __s1,
                                        /*aligned(1)*/ void const *__restrict __s2,
                                        __SIZE_TYPE__ __n_bytes) {
	if __untraced(__builtin_constant_p(__s1 == __s2) && (__s1 == __s2))
		return 0;
	/* memcmp() behaves differently from strcmp(), in that memcmp is allowed to
	 * assume both input data blocks contain at least `N_BYTES' of valid  data,
	 * which  an implementation  is allowed to  access in any  order it wishes.
	 * With   that  in  mind,  we  are  allowed  to  optimize  something  like:
	 * >> memcmp(a, b, 4) == 0;
	 * Into:
	 * >> *(u32 *)a == *(u32 *)b
	 * For `strcmp()' we can't actually do this, because we must not attempt to access
	 * any bytes of either string following a \0-character.
	 *
	 * Proof  of this behavior is hard to come  by, but I managed to find this (somewhat
	 * unrelated) stackoverflow question, where all the answers unquestioningly indicate
	 * that  using memcmp() to access out-of-bounds data causes undefined behavior, even
	 * if memory leading up to the undefined portion is guarantied to compare non-equal,
	 * thus allowing us to perform this optimization for memcmp()!
	 * https://stackoverflow.com/questions/37782671/comparing-two-strings-using-memcmp-in-c
	 */
	if __untraced(__builtin_constant_p(__n_bytes)) {
		/* NOTE: The `__DO_COMPARE()' macro is designed to best allow GCC
		 *       to determine  which path  is used  by which  comparison.
		 * For example, `if __untraced(memcmp(a, b, 4) == 0) { ... }' can get
		 * fully optimized to `if __untraced(*(u32 *)a == *(u32 *)b) { ... }' */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __DO_COMPARE(T, off)         \
	{                                \
		T __x1 = *((T *)__s1 + off), \
		  __x2 = *((T *)__s2 + off); \
		if __untraced(__x1 < __x2)   \
			return -1;               \
		if __untraced(__x1 > __x2)   \
			return 1;                \
	}
#define __DO_COMPARE8(off)  __DO_COMPARE(__UINT8_TYPE__, off)
#define __DO_COMPARE16(off) __DO_COMPARE(__UINT16_TYPE__, off)
#define __DO_COMPARE32(off) __DO_COMPARE(__UINT32_TYPE__, off)
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
#define __DO_COMPARE64(off) __DO_COMPARE(__UINT64_TYPE__, off)
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#define __DO_COMPARE8(off)                                     \
	{                                                          \
		__UINT8_TYPE__ __x1 = *((__UINT8_TYPE__ *)__s1 + off), \
		               __x2 = *((__UINT8_TYPE__ *)__s2 + off); \
		if __untraced(__x1 < __x2)                             \
			return -1;                                         \
		if __untraced(__x1 > __x2)                             \
			return 1;                                          \
	}
#define __DO_COMPARE16(off)                                                    \
	{                                                                          \
		__UINT16_TYPE__ __x1 = *((__UINT16_TYPE__ *)__s1 + off),               \
		                __x2 = *((__UINT16_TYPE__ *)__s2 + off);               \
		if __untraced(__x1 != __x2) {                                          \
			if __untraced((__x1 & __UINT8_C(0xff)) < (__x2 & __UINT8_C(0xff))) \
				return -1;                                                     \
			if __untraced((__x1 & __UINT8_C(0xff)) > (__x2 & __UINT8_C(0xff))) \
				return 1;                                                      \
			if __untraced(__x1 < __x2)                                         \
				return -1;                                                     \
			return 1;                                                          \
		}                                                                      \
	}
#define __DO_COMPARE32(off)                                                              \
	{                                                                                    \
		__UINT32_TYPE__ __x1 = *((__UINT32_TYPE__ *)__s1 + off),                         \
		                __x2 = *((__UINT32_TYPE__ *)__s2 + off);                         \
		if __untraced(__x1 != __x2) {                                                    \
			if __untraced((__x1 & __UINT8_C(0xff)) < (__x2 & __UINT8_C(0xff)))           \
				return -1;                                                               \
			if __untraced((__x1 & __UINT8_C(0xff)) > (__x2 & __UINT8_C(0xff)))           \
				return 1;                                                                \
			if __untraced((__x1 & __UINT16_C(0xff00)) < (__x2 & __UINT16_C(0xff00)))     \
				return -1;                                                               \
			if __untraced((__x1 & __UINT16_C(0xff00)) > (__x2 & __UINT16_C(0xff00)))     \
				return 1;                                                                \
			if __untraced((__x1 & __UINT32_C(0xff0000)) < (__x2 & __UINT32_C(0xff0000))) \
				return -1;                                                               \
			if __untraced((__x1 & __UINT32_C(0xff0000)) > (__x2 & __UINT32_C(0xff0000))) \
				return 1;                                                                \
			if __untraced(__x1 < __x2)                                                   \
				return -1;                                                               \
			return 1;                                                                    \
		}                                                                                \
	}
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
#define __DO_COMPARE64(off)                                                                              \
	{                                                                                                    \
		__UINT64_TYPE__ __x1 = *((__UINT64_TYPE__ *)__s1 + off),                                         \
		                __x2 = *((__UINT64_TYPE__ *)__s2 + off);                                         \
		if __untraced(__x1 != __x2) {                                                                    \
			if __untraced((__x1 & __UINT8_C(0xff)) < (__x2 & __UINT8_C(0xff)))                           \
				return -1;                                                                               \
			if __untraced((__x1 & __UINT8_C(0xff)) > (__x2 & __UINT8_C(0xff)))                           \
				return 1;                                                                                \
			if __untraced((__x1 & __UINT16_C(0xff00)) < (__x2 & __UINT16_C(0xff00)))                     \
				return -1;                                                                               \
			if __untraced((__x1 & __UINT16_C(0xff00)) > (__x2 & __UINT16_C(0xff00)))                     \
				return 1;                                                                                \
			if __untraced((__x1 & __UINT32_C(0xff0000)) < (__x2 & __UINT32_C(0xff0000)))                 \
				return -1;                                                                               \
			if __untraced((__x1 & __UINT32_C(0xff0000)) > (__x2 & __UINT32_C(0xff0000)))                 \
				return 1;                                                                                \
			if __untraced((__x1 & __UINT32_C(0xff000000)) < (__x2 & __UINT32_C(0xff000000)))             \
				return -1;                                                                               \
			if __untraced((__x1 & __UINT32_C(0xff000000)) > (__x2 & __UINT32_C(0xff000000)))             \
				return 1;                                                                                \
			if __untraced((__x1 & __UINT64_C(0xff00000000)) < (__x2 & __UINT64_C(0xff00000000)))         \
				return -1;                                                                               \
			if __untraced((__x1 & __UINT64_C(0xff00000000)) > (__x2 & __UINT64_C(0xff00000000)))         \
				return 1;                                                                                \
			if __untraced((__x1 & __UINT64_C(0xff0000000000)) < (__x2 & __UINT64_C(0xff0000000000)))     \
				return -1;                                                                               \
			if __untraced((__x1 & __UINT64_C(0xff0000000000)) > (__x2 & __UINT64_C(0xff0000000000)))     \
				return 1;                                                                                \
			if __untraced((__x1 & __UINT64_C(0xff000000000000)) < (__x2 & __UINT64_C(0xff000000000000))) \
				return -1;                                                                               \
			if __untraced((__x1 & __UINT64_C(0xff000000000000)) > (__x2 & __UINT64_C(0xff000000000000))) \
				return 1;                                                                                \
			if __untraced(__x1 < __x2)                                                                   \
				return -1;                                                                               \
			return 1;                                                                                    \
		}                                                                                                \
	}
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */

		/* Add constant cases all compares with less than 2 memory lookups. */
		switch __untraced(__n_bytes) {
		case 0:
			return 0;
		case 1:
			__DO_COMPARE8(0)
			return 0;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			__DO_COMPARE8(0)
			__DO_COMPARE8(1)
			return 0;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			__DO_COMPARE8(0)
			__DO_COMPARE8(1)
			__DO_COMPARE8(2)
			return 0;
		case 4:
			__DO_COMPARE8(0)
			__DO_COMPARE8(1)
			__DO_COMPARE8(2)
			__DO_COMPARE8(3)
			return 0;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		case 2:
			__DO_COMPARE16(0)
			return 0;
		case 3:
			__DO_COMPARE16(0)
			__DO_COMPARE8(2)
			return 0;
		case 4:
			__DO_COMPARE32(0)
			return 0;
		case 5:
			__DO_COMPARE32(0)
			__DO_COMPARE8(4)
			return 0;
		case 6:
			__DO_COMPARE32(0)
			__DO_COMPARE16(2)
			return 0;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 8:
			__DO_COMPARE64(0)
			return 0;
		case 9:
			__DO_COMPARE64(0)
			__DO_COMPARE8(8)
			return 0;
		case 10:
			__DO_COMPARE64(0)
			__DO_COMPARE16(4)
			return 0;
		case 12:
			__DO_COMPARE64(0)
			__DO_COMPARE32(2)
			return 0;
		case 16:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			return 0;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 8:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			return 0;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
		case 7:
			__DO_COMPARE32(0)
			__DO_COMPARE16(2)
			__DO_COMPARE8(6)
			return 0;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 11:
			__DO_COMPARE64(0)
			__DO_COMPARE16(4)
			__DO_COMPARE8(10)
			return 0;
		case 13:
			__DO_COMPARE64(0)
			__DO_COMPARE32(2)
			__DO_COMPARE8(12)
			return 0;
		case 14:
			__DO_COMPARE64(0)
			__DO_COMPARE32(2)
			__DO_COMPARE16(6)
			return 0;
		case 15:
			__DO_COMPARE64(0)
			__DO_COMPARE32(2)
			__DO_COMPARE16(6)
			__DO_COMPARE8(14)
			return 0;
		case 17:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE8(16)
			return 0;
		case 18:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE16(8)
			return 0;
		case 19:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE16(8)
			__DO_COMPARE8(18)
			return 0;
		case 20:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE32(4)
			return 0;
		case 21:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE32(4)
			__DO_COMPARE8(20)
			return 0;
		case 22:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE32(4)
			__DO_COMPARE16(10)
			return 0;
		case 24:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE64(2)
			return 0;
		case 25:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE64(2)
			__DO_COMPARE8(24)
			return 0;
		case 26:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE64(2)
			__DO_COMPARE16(12)
			return 0;
		case 28:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE64(2)
			__DO_COMPARE32(6)
			return 0;
		case 32:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE64(2)
			__DO_COMPARE64(3)
			return 0;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 9:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			__DO_COMPARE8(8)
			return 0;
		case 10:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			__DO_COMPARE16(4)
			return 0;
		case 11:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			__DO_COMPARE16(4)
			__DO_COMPARE8(10)
			return 0;
		case 12:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			__DO_COMPARE32(2)
			return 0;
		case 13:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			__DO_COMPARE32(2)
			__DO_COMPARE8(12)
			return 0;
		case 14:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			__DO_COMPARE32(2)
			__DO_COMPARE16(6)
			return 0;
		case 16:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			__DO_COMPARE32(2)
			__DO_COMPARE32(3)
			return 0;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default: break;
		}
#undef __DO_COMPARE64
#undef __DO_COMPARE32
#undef __DO_COMPARE16
#undef __DO_COMPARE8
#undef __DO_COMPARE
	}
	return __libc_core_memcmp(__s1, __s2, __n_bytes);
}
#endif /* !__fast_memcmp_defined */

#ifndef __fast_memcmpw_defined
#define __fast_memcmpw_defined
#include <hybrid/byteorder.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __INT16_TYPE__
__NOTHROW_NCX(__LIBC_FAST_NAME(memcmpw))(/*aligned(2)*/ void const *__restrict __s1,
                                         /*aligned(2)*/ void const *__restrict __s2,
                                         __SIZE_TYPE__ __n_words) {
	if __untraced(__builtin_constant_p(__s1 == __s2) && (__s1 == __s2))
		return 0;
	if __untraced(__builtin_constant_p(__n_words)) {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __DO_COMPARE(T, off)         \
	{                                \
		T __x1 = *((T *)__s1 + off), \
		  __x2 = *((T *)__s2 + off); \
		if __untraced(__x1 < __x2)   \
			return -1;               \
		if __untraced(__x1 > __x2)   \
			return 1;                \
	}
#define __DO_COMPARE16(off) __DO_COMPARE(__UINT16_TYPE__, off)
#define __DO_COMPARE32(off) __DO_COMPARE(__UINT32_TYPE__, off)
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
#define __DO_COMPARE64(off) __DO_COMPARE(__UINT64_TYPE__, off)
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#define __DO_COMPARE16(off)                                      \
	{                                                            \
		__UINT16_TYPE__ __x1 = *((__UINT16_TYPE__ *)__s1 + off), \
		                __x2 = *((__UINT16_TYPE__ *)__s2 + off); \
		if __untraced(__x1 != __x2) {                            \
			if __untraced(__x1 < __x2)                           \
				return -1;                                       \
			return 1;                                            \
		}                                                        \
	}
#define __DO_COMPARE32(off)                                                          \
	{                                                                                \
		__UINT32_TYPE__ __x1 = *((__UINT32_TYPE__ *)__s1 + off),                     \
		                __x2 = *((__UINT32_TYPE__ *)__s2 + off);                     \
		if __untraced(__x1 != __x2) {                                                \
			if __untraced((__x1 & __UINT16_C(0xffff)) < (__x2 & __UINT16_C(0xffff))) \
				return -1;                                                           \
			if __untraced((__x1 & __UINT16_C(0xffff)) > (__x2 & __UINT16_C(0xffff))) \
				return 1;                                                            \
			if __untraced(__x1 < __x2)                                               \
				return -1;                                                           \
			return 1;                                                                \
		}                                                                            \
	}
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
#define __DO_COMPARE64(off)                                                                          \
	{                                                                                                \
		__UINT64_TYPE__ __x1 = *((__UINT64_TYPE__ *)__s1 + off),                                     \
		                __x2 = *((__UINT64_TYPE__ *)__s2 + off);                                     \
		if __untraced(__x1 != __x2) {                                                                \
			if __untraced((__x1 & __UINT16_C(0xffff)) < (__x2 & __UINT16_C(0xffff)))                 \
				return -1;                                                                           \
			if __untraced((__x1 & __UINT16_C(0xffff)) > (__x2 & __UINT16_C(0xffff)))                 \
				return 1;                                                                            \
			if __untraced((__x1 & __UINT32_C(0xffff0000)) < (__x2 & __UINT32_C(0xffff0000)))         \
				return -1;                                                                           \
			if __untraced((__x1 & __UINT32_C(0xffff0000)) > (__x2 & __UINT32_C(0xffff0000)))         \
				return 1;                                                                            \
			if __untraced((__x1 & __UINT64_C(0xffff00000000)) < (__x2 & __UINT64_C(0xffff00000000))) \
				return -1;                                                                           \
			if __untraced((__x1 & __UINT64_C(0xffff00000000)) > (__x2 & __UINT64_C(0xffff00000000))) \
				return 1;                                                                            \
			if __untraced(__x1 < __x2)                                                               \
				return -1;                                                                           \
			return 1;                                                                                \
		}                                                                                            \
	}
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */

		/* Add constant cases all compares with less than 2 memory lookups. */
		switch __untraced(__n_words) {
		case 0:
			return 0;
		case 1:
			__DO_COMPARE16(0)
			return 0;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			__DO_COMPARE16(0)
			__DO_COMPARE16(1)
			return 0;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			__DO_COMPARE16(0)
			__DO_COMPARE16(1)
			__DO_COMPARE16(2)
			return 0;
		case 4:
			__DO_COMPARE16(0)
			__DO_COMPARE16(1)
			__DO_COMPARE16(2)
			__DO_COMPARE16(3)
			return 0;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		case 2:
			__DO_COMPARE32(0)
			return 0;
		case 3:
			__DO_COMPARE32(0)
			__DO_COMPARE16(2)
			return 0;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 4:
			__DO_COMPARE64(0)
			return 0;
		case 5:
			__DO_COMPARE64(0)
			__DO_COMPARE16(4)
			return 0;
		case 6:
			__DO_COMPARE64(0)
			__DO_COMPARE32(2)
			return 0;
		case 8:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			return 0;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 4:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			return 0;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 7:
			__DO_COMPARE64(0)
			__DO_COMPARE32(2)
			__DO_COMPARE16(6)
			return 0;
		case 9:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE16(8)
			return 0;
		case 10:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE32(4)
			return 0;
		case 11:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE32(4)
			__DO_COMPARE16(10)
			return 0;
		case 12:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE64(2)
			return 0;
		case 13:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE64(2)
			__DO_COMPARE16(12)
			return 0;
		case 14:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE64(2)
			__DO_COMPARE32(6)
			return 0;
		case 16:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE64(2)
			__DO_COMPARE64(3)
			return 0;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 5:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			__DO_COMPARE16(4)
			return 0;
		case 6:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			__DO_COMPARE32(2)
			return 0;
		case 7:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			__DO_COMPARE32(2)
			__DO_COMPARE16(6)
			return 0;
		case 8:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			__DO_COMPARE32(2)
			__DO_COMPARE32(3)
			return 0;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default: break;
		}
#undef __DO_COMPARE64
#undef __DO_COMPARE32
#undef __DO_COMPARE16
#undef __DO_COMPARE
	}
	return __libc_core_memcmpw(__s1, __s2, __n_words);
}
#endif /* !__fast_memcmpw_defined */

#ifndef __fast_memcmpl_defined
#define __fast_memcmpl_defined
#include <hybrid/byteorder.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __INT32_TYPE__
__NOTHROW_NCX(__LIBC_FAST_NAME(memcmpl))(/*aligned(4)*/ void const *__restrict __s1,
                                         /*aligned(4)*/ void const *__restrict __s2,
                                         __SIZE_TYPE__ __n_dwords) {
	if __untraced(__builtin_constant_p(__s1 == __s2) && (__s1 == __s2))
		return 0;
	if __untraced(__builtin_constant_p(__n_dwords)) {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __DO_COMPARE(T, off)         \
	{                                \
		T __x1 = *((T *)__s1 + off), \
		  __x2 = *((T *)__s2 + off); \
		if __untraced(__x1 < __x2)   \
			return -1;               \
		if __untraced(__x1 > __x2)   \
			return 1;                \
	}
#define __DO_COMPARE32(off) __DO_COMPARE(__UINT32_TYPE__, off)
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
#define __DO_COMPARE64(off) __DO_COMPARE(__UINT64_TYPE__, off)
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#define __DO_COMPARE32(off)                                      \
	{                                                            \
		__UINT32_TYPE__ __x1 = *((__UINT32_TYPE__ *)__s1 + off), \
		                __x2 = *((__UINT32_TYPE__ *)__s2 + off); \
		if __untraced(__x1 != __x2) {                            \
			if __untraced(__x1 < __x2)                           \
				return -1;                                       \
			return 1;                                            \
		}                                                        \
	}
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
#define __DO_COMPARE64(off)                                                                  \
	{                                                                                        \
		__UINT64_TYPE__ __x1 = *((__UINT64_TYPE__ *)__s1 + off),                             \
		                __x2 = *((__UINT64_TYPE__ *)__s2 + off);                             \
		if __untraced(__x1 != __x2) {                                                        \
			if __untraced((__x1 & __UINT32_C(0xffffffff)) < (__x2 & __UINT32_C(0xffffffff))) \
				return -1;                                                                   \
			if __untraced((__x1 & __UINT32_C(0xffffffff)) > (__x2 & __UINT32_C(0xffffffff))) \
				return 1;                                                                    \
			if __untraced(__x1 < __x2)                                                       \
				return -1;                                                                   \
			return 1;                                                                        \
		}                                                                                    \
	}
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */

		/* Add constant cases all compares with less than 2 memory lookups. */
		switch __untraced(__n_dwords) {
		case 0:
			return 0;
		case 1:
			__DO_COMPARE32(0)
			return 0;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			return 0;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			__DO_COMPARE32(2)
			return 0;
		case 4:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			__DO_COMPARE32(2)
			__DO_COMPARE32(3)
			return 0;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 2:
			__DO_COMPARE64(0)
			return 0;
		case 3:
			__DO_COMPARE64(0)
			__DO_COMPARE32(2)
			return 0;
		case 4:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			return 0;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 2:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			return 0;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
		/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 5:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE32(4)
			return 0;
		case 6:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE64(2)
			return 0;
		case 7:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE64(2)
			__DO_COMPARE32(6)
			return 0;
		case 8:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE64(2)
			__DO_COMPARE64(3)
			return 0;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 3:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			__DO_COMPARE32(2)
			return 0;
		case 4:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			__DO_COMPARE32(2)
			__DO_COMPARE32(3)
			return 0;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default:
			break;
		}
#undef __DO_COMPARE64
#undef __DO_COMPARE32
#undef __DO_COMPARE
	}
	return __libc_core_memcmpl(__s1, __s2, __n_dwords);
}
#endif /* !__fast_memcmpl_defined */

#ifdef __UINT64_TYPE__
#ifndef __fast_memcmpq_defined
#define __fast_memcmpq_defined
#include <hybrid/byteorder.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __INT64_TYPE__
__NOTHROW_NCX(__LIBC_FAST_NAME(memcmpq))(/*aligned(8)*/ void const *__restrict __s1,
                                         /*aligned(8)*/ void const *__restrict __s2,
                                         __SIZE_TYPE__ __n_qwords) {
	if __untraced(__builtin_constant_p(__s1 == __s2) && (__s1 == __s2))
		return 0;
	if __untraced(__builtin_constant_p(__n_qwords)) {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __DO_COMPARE(T, off)         \
	{                                \
		T __x1 = *((T *)__s1 + off), \
		  __x2 = *((T *)__s2 + off); \
		if __untraced(__x1 < __x2)   \
			return -1;               \
		if __untraced(__x1 > __x2)   \
			return 1;                \
	}
#define __DO_COMPARE32(off) __DO_COMPARE(__UINT32_TYPE__, off)
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
#define __DO_COMPARE64(off) __DO_COMPARE(__UINT64_TYPE__, off)
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#define __DO_COMPARE32(off)                                      \
	{                                                            \
		__UINT32_TYPE__ __x1 = *((__UINT32_TYPE__ *)__s1 + off), \
		                __x2 = *((__UINT32_TYPE__ *)__s2 + off); \
		if __untraced(__x1 != __x2) {                            \
			if __untraced(__x1 < __x2)                           \
				return -1;                                       \
			return 1;                                            \
		}                                                        \
	}
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
#define __DO_COMPARE64(off)                                                                  \
	{                                                                                        \
		__UINT64_TYPE__ __x1 = *((__UINT64_TYPE__ *)__s1 + off),                             \
		                __x2 = *((__UINT64_TYPE__ *)__s2 + off);                             \
		if __untraced(__x1 != __x2) {                                                        \
			if __untraced((__x1 & __UINT32_C(0xffffffff)) < (__x2 & __UINT32_C(0xffffffff))) \
				return -1;                                                                   \
			if __untraced((__x1 & __UINT32_C(0xffffffff)) > (__x2 & __UINT32_C(0xffffffff))) \
				return 1;                                                                    \
			if __untraced(__x1 < __x2)                                                       \
				return -1;                                                                   \
			return 1;                                                                        \
		}                                                                                    \
	}
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
		/* Add constant cases all compares with less than 2 memory lookups. */
		switch __untraced(__n_qwords) {
		case 0:
			return 0;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 1:
			__DO_COMPARE64(0)
			return 0;
		case 2:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			return 0;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 1:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			return 0;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
		/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 3:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE64(2)
			return 0;
		case 4:
			__DO_COMPARE64(0)
			__DO_COMPARE64(1)
			__DO_COMPARE64(2)
			__DO_COMPARE64(3)
			return 0;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 2:
			__DO_COMPARE32(0)
			__DO_COMPARE32(1)
			__DO_COMPARE32(2)
			__DO_COMPARE32(3)
			return 0;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
		default:
			break;
		}
#undef __DO_COMPARE64
#undef __DO_COMPARE32
#undef __DO_COMPARE
	}
	return __libc_core_memcmpq(__s1, __s2, __n_qwords);
}
#endif /* !__fast_memcmpq_defined */
#endif /* __UINT64_TYPE__ */

#undef __OPTIMIZE_STRING_MEMOVE_DIRECTION
/* NOTE: I remember this not correctly working in the past.
 *       I think it was broken back in gcc7
 * EDIT: Nope! It's still broken (complains about the `memmovedown()' in
 *       `/kos/src/libbuffer/packetbuffer.c:lib_pb_buffer_startwrite') */
#if (!defined(__GNUC__) || (defined(__GNUC__) && __GNUC__ > 7)) && 0
#define __OPTIMIZE_STRING_MEMOVE_DIRECTION 1
#endif

#if !defined(NDEBUG) && defined(__OPTIMIZE_STRING_MEMOVE_DIRECTION)
extern __ATTR_ERROR("memmovedown(): The passed dst pointer is greater than src (dst > src) - Use `memmoveup()' instead") void __memmovedown_invalid_pointer_order(void);
extern __ATTR_ERROR("memmoveup(): The passed dst pointer is lower than src (dst < src) - Use `memmovedown()' instead") void __memmoveup_invalid_pointer_order(void);
/* Compile-time ordering assertions */
#define __ASSERT_MEMMOVEDOWN_CT(dst, src)                            \
	if __untraced(__builtin_constant_p(dst <= src) && !(dst <= src)) \
		__memmovedown_invalid_pointer_order()
#define __ASSERT_MEMMOVEDOWN_RT(dst, src)                         \
	if __untraced(!__builtin_constant_p(dst <= src) || dst > src) \
		__hybrid_assertf(dst <= src, "%p < %p", dst, src)
#define __ASSERT_MEMMOVEUP_CT(dst, src)                              \
	if __untraced(__builtin_constant_p(dst >= src) && !(dst >= src)) \
		__memmoveup_invalid_pointer_order()
#define __ASSERT_MEMMOVEUP_RT(dst, src)                           \
	if __untraced(!__builtin_constant_p(dst >= src) || dst < src) \
		__hybrid_assertf(dst >= src, "%p < %p", dst, src)
#else /* !NDEBUG && __OPTIMIZE_STRING_MEMOVE_DIRECTION */
#define __ASSERT_MEMMOVEDOWN_CT(dst, src) /* nothing */
#define __ASSERT_MEMMOVEDOWN_RT(dst, src) /* nothing */
#define __ASSERT_MEMMOVEUP_CT(dst, src)   /* nothing */
#define __ASSERT_MEMMOVEUP_RT(dst, src)   /* nothing */
#endif /* NDEBUG || !__OPTIMIZE_STRING_MEMOVE_DIRECTION */

#ifdef __UINT64_TYPE__
#ifndef __fast_memmovedownq_defined
#define __fast_memmovedownq_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memmovedownq))(/*aligned(8)*/ void *__dst,
                                              /*aligned(8)*/ void const *__src,
                                              __SIZE_TYPE__ __n_qwords) {
	__ASSERT_MEMMOVEDOWN_CT(__dst, __src);
	if __untraced(__builtin_constant_p(__n_qwords)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_qwords) {
		case 0:
			return (__UINT64_TYPE__ *)__dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 1:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT64_TYPE__ *)__dst;
		case 2:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			return (__UINT64_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 1:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return (__UINT64_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 3:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			return (__UINT64_TYPE__ *)__dst;
		case 4:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			return (__UINT64_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 2:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			return (__UINT64_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
		default: break;
		}
	}
	return __libc_core_memmovedownq(__dst, __src, __n_qwords);
}
#endif /* !__fast_memmovedownq_defined */
#endif /* __UINT64_TYPE__ */

#ifndef __fast_memmovedownl_defined
#define __fast_memmovedownl_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memmovedownl))(/*aligned(4)*/ void *__dst,
                                              /*aligned(4)*/ void const *__src,
                                              __SIZE_TYPE__ __n_dwords) {
	__ASSERT_MEMMOVEDOWN_CT(__dst, __src);
	if __untraced(__builtin_constant_p(__n_dwords)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_dwords) {
		case 0:
			return (__UINT32_TYPE__ *)__dst;
		case 1:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return (__UINT32_TYPE__ *)__dst;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT32_TYPE__ *)__dst;
		case 4:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			return (__UINT32_TYPE__ *)__dst;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 2:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
		case 3:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT32_TYPE__ *)__dst;
		case 4:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			return (__UINT32_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 2:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return (__UINT32_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

		/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 5:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			return (__UINT32_TYPE__ *)__dst;
		case 6:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			return (__UINT32_TYPE__ *)__dst;
		case 7:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[6] = ((__UINT32_TYPE__ const *)__src)[6];
			return (__UINT32_TYPE__ *)__dst;
		case 8:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			return (__UINT32_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 3:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT32_TYPE__ *)__dst;
		case 4:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			return (__UINT32_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default: break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_memmovedownq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_core_memmovedownq(__dst, __src, __n_dwords >> 1);
		__dst = __libc_core_memmovedownq(__dst, __src, __n_dwords >> 1);
		((__UINT32_TYPE__ *)__dst)[__n_dwords - 1] = ((__UINT32_TYPE__ const *)__src)[__n_dwords - 1];
		return (__UINT32_TYPE__ *)__dst;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_core_memmovedownq((__UINT64_TYPE__ *)__dst, __src, __n_dwords >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmovedownq && __SIZEOF_BUSINT__ >= 8 */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_memmovedownl(__dst, __src, __n_dwords);
}
#endif /* !__fast_memmovedownl_defined */

#ifndef __fast_memmovedownw_defined
#define __fast_memmovedownw_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memmovedownw))(/*aligned(2)*/ void *__dst,
                                              /*aligned(2)*/ void const *__src,
                                              __SIZE_TYPE__ __n_words) {
	__ASSERT_MEMMOVEDOWN_CT(__dst, __src);
	if __untraced(__builtin_constant_p(__n_words)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_words) {
		case 0:
			return (__UINT16_TYPE__ *)__dst;
		case 1:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[1] = ((__UINT16_TYPE__ const *)__src)[1];
			return (__UINT16_TYPE__ *)__dst;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[1] = ((__UINT16_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			return (__UINT16_TYPE__ *)__dst;
		case 4:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[1] = ((__UINT16_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[3] = ((__UINT16_TYPE__ const *)__src)[3];
			return (__UINT16_TYPE__ *)__dst;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		case 2:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 3:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			return (__UINT16_TYPE__ *)__dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 4:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 5:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			return (__UINT16_TYPE__ *)__dst;
		case 6:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT16_TYPE__ *)__dst;
		case 8:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			return (__UINT16_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 4:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return (__UINT16_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 7:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			return (__UINT16_TYPE__ *)__dst;
		case 9:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[8] = ((__UINT16_TYPE__ const *)__src)[8];
			return (__UINT16_TYPE__ *)__dst;
		case 10:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			return (__UINT16_TYPE__ *)__dst;
		case 11:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4]  = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT16_TYPE__ *)__dst)[10] = ((__UINT16_TYPE__ const *)__src)[10];
			return (__UINT16_TYPE__ *)__dst;
		case 12:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			return (__UINT16_TYPE__ *)__dst;
		case 13:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2]  = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[12] = ((__UINT16_TYPE__ const *)__src)[12];
			return (__UINT16_TYPE__ *)__dst;
		case 14:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[6] = ((__UINT32_TYPE__ const *)__src)[6];
			return (__UINT16_TYPE__ *)__dst;
		case 16:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			return (__UINT16_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 5:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			return (__UINT16_TYPE__ *)__dst;
		case 6:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT16_TYPE__ *)__dst;
		case 7:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			return (__UINT16_TYPE__ *)__dst;
		case 8:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			return (__UINT16_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default: break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_memmovedownq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_words & 3) {
		case 0:
			return (__UINT16_TYPE__ *)__libc_core_memmovedownq(__dst, __src, __n_words >> 2);
		case 1:
			__dst = __libc_core_memmovedownq(__dst, __src, __n_words >> 2);
			((__UINT16_TYPE__ *)__dst)[__n_words - 1] = ((__UINT16_TYPE__ const *)__src)[__n_words - 1];
			return (__UINT16_TYPE__ *)__dst;
		case 2:
			__dst = __libc_core_memmovedownq(__dst, __src, __n_words >> 2);
			((__UINT32_TYPE__ *)__dst)[(__n_words >> 1) - 1] = ((__UINT32_TYPE__ const *)__src)[(__n_words >> 1) - 1];
			return (__UINT16_TYPE__ *)__dst;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_words & 7))
			return (__UINT16_TYPE__ *)__libc_core_memmovedownq(__dst, __src, __n_words >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmovedownq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_memmovedownl)
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_core_memmovedownl(__dst, __src, __n_words >> 1);
		__dst = __libc_core_memmovedownl(__dst, __src, __n_words >> 1);
		((__UINT16_TYPE__ *)__dst)[__n_words - 1] = ((__UINT16_TYPE__ const *)__src)[__n_words - 1];
		return (__UINT16_TYPE__ *)__dst;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_words & 1))
			return __libc_core_memmovedownw(__dst, __src, __n_words >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmovedownl */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_memmovedownw(__dst, __src, __n_words);
}
#endif /* !__fast_memmovedownw_defined */


#ifndef __fast_memmovedown_defined
#define __fast_memmovedown_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(memmovedown))(/*aligned(1)*/ void *__dst,
                                             /*aligned(1)*/ void const *__src,
                                             __SIZE_TYPE__ __n_bytes) {
	__ASSERT_MEMMOVEDOWN_CT(__dst, __src);
	if __untraced(__builtin_constant_p(__n_bytes)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_bytes) {
		case 0:
			return __dst;
		case 1:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			return __dst;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[1] = ((__UINT8_TYPE__ const *)__src)[1];
			return (__UINT8_TYPE__ *)__dst;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[1] = ((__UINT8_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[2] = ((__UINT8_TYPE__ const *)__src)[2];
			return (__UINT8_TYPE__ *)__dst;
		case 4:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[1] = ((__UINT8_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[2] = ((__UINT8_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[3] = ((__UINT8_TYPE__ const *)__src)[3];
			return (__UINT8_TYPE__ *)__dst;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		case 2:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return __dst;
		case 3:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[2] = ((__UINT8_TYPE__ const *)__src)[2];
			return __dst;
		case 4:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return __dst;
		case 5:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[4] = ((__UINT8_TYPE__ const *)__src)[4];
			return __dst;
		case 6:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			return __dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 8:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
		case 9:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[8] = ((__UINT8_TYPE__ const *)__src)[8];
			return __dst;
		case 10:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			return __dst;
		case 12:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return __dst;
		case 16:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			return __dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 8:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return __dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
		case 7:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[6]  = ((__UINT8_TYPE__ const *)__src)[6];
			return __dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 11:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT8_TYPE__ *)__dst)[10] = ((__UINT8_TYPE__ const *)__src)[10];
			return __dst;
		case 13:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[12] = ((__UINT8_TYPE__ const *)__src)[12];
			return __dst;
		case 14:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			return __dst;
		case 15:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			((__UINT8_TYPE__ *)__dst)[14] = ((__UINT8_TYPE__ const *)__src)[14];
			return __dst;
		case 17:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[16] = ((__UINT8_TYPE__ const *)__src)[16];
			return __dst;
		case 18:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[8] = ((__UINT16_TYPE__ const *)__src)[8];
			return __dst;
		case 19:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[8] = ((__UINT16_TYPE__ const *)__src)[8];
			((__UINT8_TYPE__ *)__dst)[18] = ((__UINT8_TYPE__ const *)__src)[18];
			return __dst;
		case 20:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			return __dst;
		case 21:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT8_TYPE__ *)__dst)[20] = ((__UINT8_TYPE__ const *)__src)[20];
			return __dst;
		case 22:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4]  = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT16_TYPE__ *)__dst)[10] = ((__UINT16_TYPE__ const *)__src)[10];
			return __dst;
		case 24:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			return __dst;
		case 25:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[24] = ((__UINT8_TYPE__ const *)__src)[24];
			return __dst;
		case 26:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2]  = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[12] = ((__UINT16_TYPE__ const *)__src)[12];
			return __dst;
		case 28:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[6] = ((__UINT32_TYPE__ const *)__src)[6];
			return __dst;
		case 32:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			return __dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 9:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[8]  = ((__UINT8_TYPE__ const *)__src)[8];
			return __dst;
		case 10:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			return __dst;
		case 11:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT8_TYPE__ *)__dst)[10] = ((__UINT8_TYPE__ const *)__src)[10];
			return __dst;
		case 12:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return __dst;
		case 13:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[12] = ((__UINT8_TYPE__ const *)__src)[12];
			return __dst;
		case 14:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			return __dst;
		case 16:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			return __dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default: break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_memmovedownq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_bytes & 7) {
		case 0:
			return __libc_core_memmovedownq(__dst, __src, __n_bytes >> 3);
		case 1:
			__dst = __libc_core_memmovedownq(__dst, __src, __n_bytes >> 3);
			((__UINT8_TYPE__ *)__dst)[__n_bytes - 1] = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
			return __dst;
		case 2:
			__dst = __libc_core_memmovedownq(__dst, __src, __n_bytes >> 3);
			((__UINT16_TYPE__ *)__dst)[(__n_bytes >> 1) - 1] = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1) - 1];
			return __dst;
		case 4:
			__dst = __libc_core_memmovedownq(__dst, __src, __n_bytes >> 3);
			((__UINT32_TYPE__ *)__dst)[(__n_bytes >> 2) - 1] = ((__UINT32_TYPE__ const *)__src)[(__n_bytes >> 2) - 1];
			return __dst;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 7))
			return __libc_core_memmovedownq(__dst, __src, __n_bytes >> 3);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmovedownq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_memmovedownl)
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_bytes & 3) {
		case 0:
			return __libc_core_memmovedownl(__dst, __src, __n_bytes >> 2);
		case 1:
			__dst = __libc_core_memmovedownl(__dst, __src, __n_bytes >> 2);
			((__UINT8_TYPE__ *)__dst)[__n_bytes - 1] = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
			return __dst;
		case 2:
			__dst = __libc_core_memmovedownl(__dst, __src, __n_bytes >> 2);
			((__UINT16_TYPE__ *)__dst)[(__n_bytes >> 1) - 1] = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1) - 1];
			return __dst;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 3))
			return __libc_core_memmovedownl(__dst, __src, __n_bytes >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmovedownl */
#if defined(__CRT_HAVE_memmovedownw)
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_bytes & 1))
			return __libc_core_memmovedownw(__dst, __src, __n_bytes >> 1);
		__dst = __libc_core_memmovedownw(__dst, __src, __n_bytes >> 1);
		((__UINT8_TYPE__ *)__dst)[__n_bytes - 1] = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
		return __dst;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 1))
			return __libc_core_memmovedownw(__dst, __src, __n_bytes >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmovedownw */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_memmovedown(__dst, __src, __n_bytes);
}
#endif /* !__fast_memmovedown_defined */



#ifdef __UINT64_TYPE__
#ifndef __fast_mempmovedownq_defined
#define __fast_mempmovedownq_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempmovedownq))(/*aligned(8)*/ void *__dst,
                                               /*aligned(8)*/ void const *__src,
                                               __SIZE_TYPE__ __n_qwords) {
	__ASSERT_MEMMOVEDOWN_CT(__dst, __src);
	if __untraced(__builtin_constant_p(__n_qwords)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_qwords) {
		case 0:
			return (__UINT64_TYPE__ *)__dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 1:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
		case 2:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 1:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 3:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 24);
		case 4:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 32);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 2:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
		default: break;
		}
	}
	return __libc_core_mempmovedownq(__dst, __src, __n_qwords);
}
#endif /* !__fast_mempmovedownq_defined */
#endif /* __UINT64_TYPE__ */


#ifndef __fast_mempmovedownl_defined
#define __fast_mempmovedownl_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempmovedownl))(/*aligned(4)*/ void *__dst,
                                               /*aligned(4)*/ void const *__src,
                                               __SIZE_TYPE__ __n_dwords) {
	__ASSERT_MEMMOVEDOWN_CT(__dst, __src);
	if __untraced(__builtin_constant_p(__n_dwords)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_dwords) {
		case 0:
			return (__UINT32_TYPE__ *)__dst;
		case 1:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 4);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return (__UINT32_TYPE__ *)__dst + 2;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT32_TYPE__ *)__dst + 3;
		case 4:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			return (__UINT32_TYPE__ *)__dst + 4;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 2:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
		case 3:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 12);
		case 4:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 2:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 5:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 20);
		case 6:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 24);
		case 7:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[6] = ((__UINT32_TYPE__ const *)__src)[6];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 28);
		case 8:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 32);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 3:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 12);
		case 4:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default: break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_mempmovedownq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_core_mempmovedownq(__dst, __src, __n_dwords >> 1);
		__dst = __libc_core_mempmovedownq(__dst, __src, __n_dwords >> 1);
		((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[__n_dwords - 1];
		return (__UINT32_TYPE__ *)__dst + 1;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_core_mempmovedownq((__UINT64_TYPE__ *)__dst, __src, __n_dwords >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmovedownq && __SIZEOF_BUSINT__ >= 8 */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_mempmovedownl(__dst, __src, __n_dwords);
}
#endif /* !__fast_mempmovedownl_defined */


#ifndef __fast_mempmovedownw_defined
#define __fast_mempmovedownw_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempmovedownw))(/*aligned(2)*/ void *__dst,
                                               /*aligned(2)*/ void const *__src,
                                               __SIZE_TYPE__ __n_words) {
	__ASSERT_MEMMOVEDOWN_CT(__dst, __src);
	if __untraced(__builtin_constant_p(__n_words)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_words) {
		case 0:
			return (__UINT16_TYPE__ *)__dst;
		case 1:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 2);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[1] = ((__UINT16_TYPE__ const *)__src)[1];
			return (__UINT16_TYPE__ *)__dst + 2;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[1] = ((__UINT16_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			return (__UINT16_TYPE__ *)__dst + 3;
		case 4:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[1] = ((__UINT16_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[3] = ((__UINT16_TYPE__ const *)__src)[3];
			return (__UINT16_TYPE__ *)__dst + 4;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		case 2:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 4);
		case 3:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 6);
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 4:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
		case 5:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 10);
		case 6:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 12);
		case 8:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 4:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
		/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 7:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 14);
		case 9:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[8] = ((__UINT16_TYPE__ const *)__src)[8];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 18);
		case 10:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 20);
		case 11:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4]  = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT16_TYPE__ *)__dst)[10] = ((__UINT16_TYPE__ const *)__src)[10];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 22);
		case 12:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 24);
		case 13:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2]  = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[12] = ((__UINT16_TYPE__ const *)__src)[12];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 26);
		case 14:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[6] = ((__UINT32_TYPE__ const *)__src)[6];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 28);
		case 16:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 32);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 5:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 10);
		case 6:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 12);
		case 7:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 14);
		case 8:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default: break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_mempmovedownq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_words & 3) {
		case 0:
			return (__UINT16_TYPE__ *)__libc_core_mempmovedownq(__dst, __src, __n_words >> 2);
		case 1:
			__dst = __libc_core_mempmovedownq(__dst, __src, __n_words >> 2);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[__n_words - 1];
			return (__UINT16_TYPE__ *)__dst + 1;
		case 2:
			__dst = __libc_core_mempmovedownq(__dst, __src, __n_words >> 2);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[(__n_words >> 1) - 1];
			return (__UINT16_TYPE__ *)__dst + 2;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_words & 3))
			return (__UINT16_TYPE__ *)__libc_core_mempmovedownq(__dst, __src, __n_words >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmovedownq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_mempmovedownl)
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_core_mempmovedownl(__dst, __src, __n_words >> 1);
		__dst = __libc_core_mempmovedownl(__dst, __src, __n_words >> 1);
		((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[__n_words - 1];
		return (__UINT16_TYPE__ *)__dst + 1;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_core_mempmovedownl(__dst, __src, __n_words >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmovedownl */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_mempmovedownw(__dst, __src, __n_words);
}
#endif /* !__fast_mempmovedownw_defined */


#ifndef __fast_mempmovedown_defined
#define __fast_mempmovedown_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempmovedown))(/*aligned(1)*/ void *__dst,
                                              /*aligned(1)*/ void const *__src,
                                              __SIZE_TYPE__ __n_bytes) {
	__ASSERT_MEMMOVEDOWN_CT(__dst, __src);
	if __untraced(__builtin_constant_p(__n_bytes)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_bytes) {
		case 0:
			return __dst;
		case 1:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 1;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[1] = ((__UINT8_TYPE__ const *)__src)[1];
			return (__UINT8_TYPE__ *)__dst + 2;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[1] = ((__UINT8_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[2] = ((__UINT8_TYPE__ const *)__src)[2];
			return (__UINT8_TYPE__ *)__dst + 3;
		case 4:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[1] = ((__UINT8_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[2] = ((__UINT8_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[3] = ((__UINT8_TYPE__ const *)__src)[3];
			return (__UINT8_TYPE__ *)__dst + 4;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		case 2:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 2;
		case 3:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[2] = ((__UINT8_TYPE__ const *)__src)[2];
			return (__UINT8_TYPE__ *)__dst + 3;
		case 4:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 4;
		case 5:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[4] = ((__UINT8_TYPE__ const *)__src)[4];
			return (__UINT8_TYPE__ *)__dst + 5;
		case 6:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			return (__UINT8_TYPE__ *)__dst + 6;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 8:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 8;
		case 9:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[8] = ((__UINT8_TYPE__ const *)__src)[8];
			return (__UINT8_TYPE__ *)__dst + 9;
		case 10:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			return (__UINT8_TYPE__ *)__dst + 10;
		case 12:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT8_TYPE__ *)__dst + 12;
		case 16:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			return (__UINT8_TYPE__ *)__dst + 16;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 8:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			return (__UINT8_TYPE__ *)__dst + 8;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
		/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
		case 7:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[6]  = ((__UINT8_TYPE__ const *)__src)[6];
			return (__UINT8_TYPE__ *)__dst + 7;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 11:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT8_TYPE__ *)__dst)[10] = ((__UINT8_TYPE__ const *)__src)[10];
			return (__UINT8_TYPE__ *)__dst + 11;
		case 13:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[12] = ((__UINT8_TYPE__ const *)__src)[12];
			return (__UINT8_TYPE__ *)__dst + 13;
		case 14:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			return (__UINT8_TYPE__ *)__dst + 14;
		case 15:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			((__UINT8_TYPE__ *)__dst)[14] = ((__UINT8_TYPE__ const *)__src)[14];
			return (__UINT8_TYPE__ *)__dst + 15;
		case 17:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[16] = ((__UINT8_TYPE__ const *)__src)[16];
			return (__UINT8_TYPE__ *)__dst + 17;
		case 18:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[8] = ((__UINT16_TYPE__ const *)__src)[8];
			return (__UINT8_TYPE__ *)__dst + 18;
		case 19:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[8] = ((__UINT16_TYPE__ const *)__src)[8];
			((__UINT8_TYPE__ *)__dst)[18] = ((__UINT8_TYPE__ const *)__src)[18];
			return (__UINT8_TYPE__ *)__dst + 19;
		case 20:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			return (__UINT8_TYPE__ *)__dst + 20;
		case 21:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT8_TYPE__ *)__dst)[20] = ((__UINT8_TYPE__ const *)__src)[20];
			return (__UINT8_TYPE__ *)__dst + 21;
		case 22:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[4]  = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT16_TYPE__ *)__dst)[10] = ((__UINT16_TYPE__ const *)__src)[10];
			return (__UINT8_TYPE__ *)__dst + 22;
		case 24:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			return (__UINT8_TYPE__ *)__dst + 24;
		case 25:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[24] = ((__UINT8_TYPE__ const *)__src)[24];
			return (__UINT8_TYPE__ *)__dst + 25;
		case 26:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2]  = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[12] = ((__UINT16_TYPE__ const *)__src)[12];
			return (__UINT8_TYPE__ *)__dst + 26;
		case 28:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[6] = ((__UINT32_TYPE__ const *)__src)[6];
			return (__UINT8_TYPE__ *)__dst + 28;
		case 32:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			return (__UINT8_TYPE__ *)__dst + 32;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 9:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[8]  = ((__UINT8_TYPE__ const *)__src)[8];
			return (__UINT8_TYPE__ *)__dst + 9;
		case 10:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			return (__UINT8_TYPE__ *)__dst + 10;
		case 11:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT8_TYPE__ *)__dst)[10] = ((__UINT8_TYPE__ const *)__src)[10];
			return (__UINT8_TYPE__ *)__dst + 11;
		case 12:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			return (__UINT8_TYPE__ *)__dst + 12;
		case 13:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[12] = ((__UINT8_TYPE__ const *)__src)[12];
			return (__UINT8_TYPE__ *)__dst + 13;
		case 14:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			return (__UINT8_TYPE__ *)__dst + 14;
		case 16:
			__ASSERT_MEMMOVEDOWN_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			return (__UINT8_TYPE__ *)__dst + 16;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default: break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_mempmovedownq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_bytes & 7) {
		case 0:
			return __libc_core_mempmovedownq(__dst, __src, __n_bytes >> 3);
		case 1:
			__dst = __libc_core_mempmovedownq(__dst, __src, __n_bytes >> 3);
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
			return (__UINT8_TYPE__ *)__dst + 1;
		case 2:
			__dst = __libc_core_mempmovedownq(__dst, __src, __n_bytes >> 3);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1) - 1];
			return (__UINT8_TYPE__ *)__dst + 2;
		case 4:
			__dst = __libc_core_mempmovedownq(__dst, __src, __n_bytes >> 3);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[(__n_bytes >> 2) - 1];
			return (__UINT8_TYPE__ *)__dst + 4;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 7))
			return __libc_core_mempmovedownq(__dst, __src, __n_bytes >> 3);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmovedownq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_mempmovedownl)
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_bytes & 3) {
		case 0:
			return __libc_core_mempmovedownl(__dst, __src, __n_bytes >> 2);
		case 1:
			__dst = __libc_core_mempmovedownl(__dst, __src, __n_bytes >> 2);
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
			return (__UINT8_TYPE__ *)__dst + 1;
		case 2:
			__dst = __libc_core_mempmovedownl(__dst, __src, __n_bytes >> 2);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1) - 1];
			return (__UINT8_TYPE__ *)__dst + 2;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 3))
			return __libc_core_mempmovedownl(__dst, __src, __n_bytes >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmovedownl */
#if defined(__CRT_HAVE_mempmovedownw)
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_bytes & 1))
			return __libc_core_mempmovedownw(__dst, __src, __n_bytes >> 1);
		__dst = __libc_core_mempmovedownw(__dst, __src, __n_bytes >> 1);
		((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
		return (__UINT8_TYPE__ *)__dst + 1;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 1))
			return __libc_core_mempmovedownw(__dst, __src, __n_bytes >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmovedownw */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_mempmovedown(__dst, __src, __n_bytes);
}
#endif /* !__fast_mempmovedown_defined */









#ifdef __UINT64_TYPE__
#ifndef __fast_memmoveupq_defined
#define __fast_memmoveupq_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memmoveupq))(/*aligned(8)*/ void *__dst,
                                            /*aligned(8)*/ void const *__src,
                                            __SIZE_TYPE__ __n_qwords) {
	__ASSERT_MEMMOVEUP_CT(__dst, __src);
	if __untraced(__builtin_constant_p(__n_qwords)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_qwords) {
		case 0:
			return (__UINT64_TYPE__ *)__dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 1:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT64_TYPE__ *)__dst;
		case 2:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT64_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 1:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT64_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 3:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT64_TYPE__ *)__dst;
		case 4:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT64_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 2:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT64_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
		default: break;
		}
	}
	return __libc_core_memmoveupq(__dst, __src, __n_qwords);
}
#endif /* !__fast_memmoveupq_defined */
#endif /* __UINT64_TYPE__ */

#ifndef __fast_memmoveupl_defined
#define __fast_memmoveupl_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memmoveupl))(/*aligned(4)*/ void *__dst,
                                            /*aligned(4)*/ void const *__src,
                                            __SIZE_TYPE__ __n_dwords) {
	__ASSERT_MEMMOVEUP_CT(__dst, __src);
	if __untraced(__builtin_constant_p(__n_dwords)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_dwords) {
		case 0:
			return (__UINT32_TYPE__ *)__dst;
		case 1:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
		case 4:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 2:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
		case 3:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
		case 4:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 2:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

		/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 5:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
		case 6:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
		case 7:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[6] = ((__UINT32_TYPE__ const *)__src)[6];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
		case 8:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 3:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
		case 4:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default: break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_memmoveupq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_core_memmoveupq(__dst, __src, __n_dwords >> 1);
		__dst = __libc_core_memmoveupq(__dst, __src, __n_dwords >> 1);
		((__UINT32_TYPE__ *)__dst)[__n_dwords - 1] = ((__UINT32_TYPE__ const *)__src)[__n_dwords - 1];
		return (__UINT32_TYPE__ *)__dst;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_core_memmoveupq((__UINT64_TYPE__ *)__dst, __src, __n_dwords >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmoveupq && __SIZEOF_BUSINT__ >= 8 */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_memmoveupl(__dst, __src, __n_dwords);
}
#endif /* !__fast_memmoveupl_defined */

#ifndef __fast_memmoveupw_defined
#define __fast_memmoveupw_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memmoveupw))(/*aligned(2)*/ void *__dst,
                                            /*aligned(2)*/ void const *__src,
                                            __SIZE_TYPE__ __n_words) {
	__ASSERT_MEMMOVEUP_CT(__dst, __src);
	if __untraced(__builtin_constant_p(__n_words)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_words) {
		case 0:
			return (__UINT16_TYPE__ *)__dst;
		case 1:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[1] = ((__UINT16_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[1] = ((__UINT16_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 4:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[3] = ((__UINT16_TYPE__ const *)__src)[3];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[1] = ((__UINT16_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		case 2:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 3:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 4:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 5:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 6:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 8:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 4:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 7:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 9:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[8] = ((__UINT16_TYPE__ const *)__src)[8];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 10:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 11:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[10] = ((__UINT16_TYPE__ const *)__src)[10];
			((__UINT32_TYPE__ *)__dst)[4]  = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 12:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 13:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[12] = ((__UINT16_TYPE__ const *)__src)[12];
			((__UINT64_TYPE__ *)__dst)[2]  = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 14:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[6] = ((__UINT32_TYPE__ const *)__src)[6];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 16:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 5:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 6:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 7:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 8:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default: break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_memmoveupq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_words & 3) {
		case 0:
			return (__UINT16_TYPE__ *)__libc_core_memmoveupq(__dst, __src, __n_words >> 2);
		case 1:
			__dst = __libc_core_memmoveupq(__dst, __src, __n_words >> 2);
			((__UINT16_TYPE__ *)__dst)[__n_words - 1] = ((__UINT16_TYPE__ const *)__src)[__n_words - 1];
			return (__UINT16_TYPE__ *)__dst;
		case 2:
			__dst = __libc_core_memmoveupq(__dst, __src, __n_words >> 2);
			((__UINT32_TYPE__ *)__dst)[(__n_words >> 1) - 1] = ((__UINT32_TYPE__ const *)__src)[(__n_words >> 1) - 1];
			return (__UINT16_TYPE__ *)__dst;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_words & 7))
			return (__UINT16_TYPE__ *)__libc_core_memmoveupq(__dst, __src, __n_words >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmoveupq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_memmoveupl)
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_core_memmoveupl(__dst, __src, __n_words >> 1);
		__dst = __libc_core_memmoveupl(__dst, __src, __n_words >> 1);
		((__UINT16_TYPE__ *)__dst)[__n_words - 1] = ((__UINT16_TYPE__ const *)__src)[__n_words - 1];
		return (__UINT16_TYPE__ *)__dst;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_words & 1))
			return __libc_core_memmoveupw(__dst, __src, __n_words >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmoveupl */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_memmoveupw(__dst, __src, __n_words);
}
#endif /* !__fast_memmoveupw_defined */


#ifndef __fast_memmoveup_defined
#define __fast_memmoveup_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(memmoveup))(/*aligned(1)*/ void *__dst,
                                           /*aligned(1)*/ void const *__src,
                                           __SIZE_TYPE__ __n_bytes) {
	__ASSERT_MEMMOVEUP_CT(__dst, __src);
	if __untraced(__builtin_constant_p(__n_bytes)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_bytes) {
		case 0:
			return __dst;
		case 1:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			return __dst;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[1] = ((__UINT8_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[2] = ((__UINT8_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[1] = ((__UINT8_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst;
		case 4:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[3] = ((__UINT8_TYPE__ const *)__src)[3];
			((__UINT8_TYPE__ *)__dst)[2] = ((__UINT8_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[1] = ((__UINT8_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		case 2:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return __dst;
		case 3:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[2] = ((__UINT8_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return __dst;
		case 4:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return __dst;
		case 5:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[4] = ((__UINT8_TYPE__ const *)__src)[4];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return __dst;
		case 6:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return __dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 8:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
		case 9:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[8] = ((__UINT8_TYPE__ const *)__src)[8];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
		case 10:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
		case 12:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
		case 16:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 8:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return __dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
		case 7:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[6]  = ((__UINT8_TYPE__ const *)__src)[6];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return __dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 11:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[10] = ((__UINT8_TYPE__ const *)__src)[10];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
		case 13:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[12] = ((__UINT8_TYPE__ const *)__src)[12];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
		case 14:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
		case 15:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[14] = ((__UINT8_TYPE__ const *)__src)[14];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
		case 17:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[16] = ((__UINT8_TYPE__ const *)__src)[16];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
		case 18:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[8] = ((__UINT16_TYPE__ const *)__src)[8];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
		case 19:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[18] = ((__UINT8_TYPE__ const *)__src)[18];
			((__UINT16_TYPE__ *)__dst)[8] = ((__UINT16_TYPE__ const *)__src)[8];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
		case 20:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
		case 21:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[20] = ((__UINT8_TYPE__ const *)__src)[20];
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
		case 22:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[10] = ((__UINT16_TYPE__ const *)__src)[10];
			((__UINT32_TYPE__ *)__dst)[4]  = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
		case 24:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
		case 25:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[24] = ((__UINT8_TYPE__ const *)__src)[24];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
		case 26:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[12] = ((__UINT16_TYPE__ const *)__src)[12];
			((__UINT64_TYPE__ *)__dst)[2]  = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
		case 28:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[6] = ((__UINT32_TYPE__ const *)__src)[6];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
		case 32:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 9:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[8]  = ((__UINT8_TYPE__ const *)__src)[8];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return __dst;
		case 10:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return __dst;
		case 11:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[10] = ((__UINT8_TYPE__ const *)__src)[10];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return __dst;
		case 12:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return __dst;
		case 13:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[12] = ((__UINT8_TYPE__ const *)__src)[12];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return __dst;
		case 14:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return __dst;
		case 16:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return __dst;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default: break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_memmoveupq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_bytes & 7) {
		case 0:
			return __libc_core_memmoveupq(__dst, __src, __n_bytes >> 3);
		case 1:
			__dst = __libc_core_memmoveupq(__dst, __src, __n_bytes >> 3);
			((__UINT8_TYPE__ *)__dst)[__n_bytes - 1] = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
			return __dst;
		case 2:
			__dst = __libc_core_memmoveupq(__dst, __src, __n_bytes >> 3);
			((__UINT16_TYPE__ *)__dst)[(__n_bytes >> 1) - 1] = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1) - 1];
			return __dst;
		case 4:
			__dst = __libc_core_memmoveupq(__dst, __src, __n_bytes >> 3);
			((__UINT32_TYPE__ *)__dst)[(__n_bytes >> 2) - 1] = ((__UINT32_TYPE__ const *)__src)[(__n_bytes >> 2) - 1];
			return __dst;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 7))
			return __libc_core_memmoveupq(__dst, __src, __n_bytes >> 3);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmoveupq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_memmoveupl)
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_bytes & 3) {
		case 0:
			return __libc_core_memmoveupl(__dst, __src, __n_bytes >> 2);
		case 1:
			__dst = __libc_core_memmoveupl(__dst, __src, __n_bytes >> 2);
			((__UINT8_TYPE__ *)__dst)[__n_bytes - 1] = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
			return __dst;
		case 2:
			__dst = __libc_core_memmoveupl(__dst, __src, __n_bytes >> 2);
			((__UINT16_TYPE__ *)__dst)[(__n_bytes >> 1) - 1] = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1) - 1];
			return __dst;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 3))
			return __libc_core_memmoveupl(__dst, __src, __n_bytes >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmoveupl */
#if defined(__CRT_HAVE_memmoveupw)
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_bytes & 1))
			return __libc_core_memmoveupw(__dst, __src, __n_bytes >> 1);
		__dst = __libc_core_memmoveupw(__dst, __src, __n_bytes >> 1);
		((__UINT8_TYPE__ *)__dst)[__n_bytes - 1] = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
		return __dst;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 1))
			return __libc_core_memmoveupw(__dst, __src, __n_bytes >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmoveupw */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_memmoveup(__dst, __src, __n_bytes);
}
#endif /* !__fast_memmoveup_defined */



#ifdef __UINT64_TYPE__
#ifndef __fast_mempmoveupq_defined
#define __fast_mempmoveupq_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempmoveupq))(/*aligned(8)*/ void *__dst,
                                             /*aligned(8)*/ void const *__src,
                                             __SIZE_TYPE__ __n_qwords) {
	__ASSERT_MEMMOVEUP_CT(__dst, __src);
	if __untraced(__builtin_constant_p(__n_qwords)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_qwords) {
		case 0:
			return (__UINT64_TYPE__ *)__dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 1:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
		case 2:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 1:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 3:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 24);
		case 4:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 32);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 2:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT64_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
		default: break;
		}
	}
	return __libc_core_mempmoveupq(__dst, __src, __n_qwords);
}
#endif /* !__fast_mempmoveupq_defined */
#endif /* __UINT64_TYPE__ */


#ifndef __fast_mempmoveupl_defined
#define __fast_mempmoveupl_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempmoveupl))(/*aligned(4)*/ void *__dst,
                                             /*aligned(4)*/ void const *__src,
                                             __SIZE_TYPE__ __n_dwords) {
	__ASSERT_MEMMOVEUP_CT(__dst, __src);
	if __untraced(__builtin_constant_p(__n_dwords)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_dwords) {
		case 0:
			return (__UINT32_TYPE__ *)__dst;
		case 1:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 4);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst + 2;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst + 3;
		case 4:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst + 4;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 2:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
		case 3:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 12);
		case 4:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 2:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
			/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 5:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 20);
		case 6:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 24);
		case 7:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[6] = ((__UINT32_TYPE__ const *)__src)[6];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 28);
		case 8:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 32);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 3:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 12);
		case 4:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default: break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_mempmoveupq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_core_mempmoveupq(__dst, __src, __n_dwords >> 1);
		__dst = __libc_core_mempmoveupq(__dst, __src, __n_dwords >> 1);
		((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[__n_dwords - 1];
		return (__UINT32_TYPE__ *)__dst + 1;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_core_mempmoveupq((__UINT64_TYPE__ *)__dst, __src, __n_dwords >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmoveupq && __SIZEOF_BUSINT__ >= 8 */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_mempmoveupl(__dst, __src, __n_dwords);
}
#endif /* !__fast_mempmoveupl_defined */


#ifndef __fast_mempmoveupw_defined
#define __fast_mempmoveupw_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempmoveupw))(/*aligned(2)*/ void *__dst,
                                             /*aligned(2)*/ void const *__src,
                                             __SIZE_TYPE__ __n_words) {
	__ASSERT_MEMMOVEUP_CT(__dst, __src);
	if __untraced(__builtin_constant_p(__n_words)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_words) {
		case 0:
			return (__UINT16_TYPE__ *)__dst;
		case 1:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 2);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[1] = ((__UINT16_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst + 2;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[1] = ((__UINT16_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst + 3;
		case 4:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[3] = ((__UINT16_TYPE__ const *)__src)[3];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[1] = ((__UINT16_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst + 4;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		case 2:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 4);
		case 3:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 6);
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 4:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
		case 5:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 10);
		case 6:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 12);
		case 8:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 4:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
		/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 7:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 14);
		case 9:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[8] = ((__UINT16_TYPE__ const *)__src)[8];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 18);
		case 10:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 20);
		case 11:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[10] = ((__UINT16_TYPE__ const *)__src)[10];
			((__UINT32_TYPE__ *)__dst)[4]  = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 22);
		case 12:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 24);
		case 13:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[12] = ((__UINT16_TYPE__ const *)__src)[12];
			((__UINT64_TYPE__ *)__dst)[2]  = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 26);
		case 14:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[6] = ((__UINT32_TYPE__ const *)__src)[6];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 28);
		case 16:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 32);
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 5:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 10);
		case 6:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 12);
		case 7:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 14);
		case 8:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 16);
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default: break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_mempmoveupq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_words & 3) {
		case 0:
			return (__UINT16_TYPE__ *)__libc_core_mempmoveupq(__dst, __src, __n_words >> 2);
		case 1:
			__dst = __libc_core_mempmoveupq(__dst, __src, __n_words >> 2);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[__n_words - 1];
			return (__UINT16_TYPE__ *)__dst + 1;
		case 2:
			__dst = __libc_core_mempmoveupq(__dst, __src, __n_words >> 2);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[(__n_words >> 1) - 1];
			return (__UINT16_TYPE__ *)__dst + 2;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_words & 3))
			return (__UINT16_TYPE__ *)__libc_core_mempmoveupq(__dst, __src, __n_words >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmoveupq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_mempmoveupl)
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_core_mempmoveupl(__dst, __src, __n_words >> 1);
		__dst = __libc_core_mempmoveupl(__dst, __src, __n_words >> 1);
		((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[__n_words - 1];
		return (__UINT16_TYPE__ *)__dst + 1;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_core_mempmoveupl(__dst, __src, __n_words >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmoveupl */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_mempmoveupw(__dst, __src, __n_words);
}
#endif /* !__fast_mempmoveupw_defined */


#ifndef __fast_mempmoveup_defined
#define __fast_mempmoveup_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempmoveup))(/*aligned(1)*/ void *__dst,
                                            /*aligned(1)*/ void const *__src,
                                            __SIZE_TYPE__ __n_bytes) {
	__ASSERT_MEMMOVEUP_CT(__dst, __src);
	if __untraced(__builtin_constant_p(__n_bytes)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch __untraced(__n_bytes) {
		case 0:
			return __dst;
		case 1:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 1;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[1] = ((__UINT8_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 2;
#ifndef __OPTIMIZE_SIZE__
		case 3:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[2] = ((__UINT8_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[1] = ((__UINT8_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 3;
		case 4:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[3] = ((__UINT8_TYPE__ const *)__src)[3];
			((__UINT8_TYPE__ *)__dst)[2] = ((__UINT8_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[1] = ((__UINT8_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 4;
#endif /* !__OPTIMIZE_SIZE__ */
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		case 2:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 2;
		case 3:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[2] = ((__UINT8_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 3;
		case 4:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 4;
		case 5:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[4] = ((__UINT8_TYPE__ const *)__src)[4];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 5;
		case 6:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 6;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 8:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 8;
		case 9:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[8] = ((__UINT8_TYPE__ const *)__src)[8];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 9;
		case 10:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 10;
		case 12:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 12;
		case 16:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 16;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 8:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 8;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
		/* More optimizations for small data blocks that require more assignments (though no more than 4). */
#ifndef __OPTIMIZE_SIZE__
		case 7:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[6]  = ((__UINT8_TYPE__ const *)__src)[6];
			((__UINT16_TYPE__ *)__dst)[2] = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 7;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 11:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[10] = ((__UINT8_TYPE__ const *)__src)[10];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 11;
		case 13:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[12] = ((__UINT8_TYPE__ const *)__src)[12];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 13;
		case 14:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 14;
		case 15:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[14] = ((__UINT8_TYPE__ const *)__src)[14];
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 15;
		case 17:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[16] = ((__UINT8_TYPE__ const *)__src)[16];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 17;
		case 18:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[8] = ((__UINT16_TYPE__ const *)__src)[8];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 18;
		case 19:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[18] = ((__UINT8_TYPE__ const *)__src)[18];
			((__UINT16_TYPE__ *)__dst)[8] = ((__UINT16_TYPE__ const *)__src)[8];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 19;
		case 20:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 20;
		case 21:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[20] = ((__UINT8_TYPE__ const *)__src)[20];
			((__UINT32_TYPE__ *)__dst)[4] = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 21;
		case 22:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[10] = ((__UINT16_TYPE__ const *)__src)[10];
			((__UINT32_TYPE__ *)__dst)[4]  = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 22;
		case 24:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 24;
		case 25:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[24] = ((__UINT8_TYPE__ const *)__src)[24];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 25;
		case 26:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[12] = ((__UINT16_TYPE__ const *)__src)[12];
			((__UINT64_TYPE__ *)__dst)[2]  = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1]  = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 26;
		case 28:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[6] = ((__UINT32_TYPE__ const *)__src)[6];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 28;
		case 32:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT64_TYPE__ *)__dst)[3] = ((__UINT64_TYPE__ const *)__src)[3];
			((__UINT64_TYPE__ *)__dst)[2] = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[1] = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 32;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 9:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[8]  = ((__UINT8_TYPE__ const *)__src)[8];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 9;
		case 10:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 10;
		case 11:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[10] = ((__UINT8_TYPE__ const *)__src)[10];
			((__UINT16_TYPE__ *)__dst)[4] = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 11;
		case 12:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 12;
		case 13:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT8_TYPE__ *)__dst)[12] = ((__UINT8_TYPE__ const *)__src)[12];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 13;
		case 14:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT16_TYPE__ *)__dst)[6] = ((__UINT16_TYPE__ const *)__src)[6];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 14;
		case 16:
			__ASSERT_MEMMOVEUP_RT(__dst, __src);
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
			((__UINT32_TYPE__ *)__dst)[2] = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[1] = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT8_TYPE__ *)__dst + 16;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		default: break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_mempmoveupq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_bytes & 7) {
		case 0:
			return __libc_core_mempmoveupq(__dst, __src, __n_bytes >> 3);
		case 1:
			__dst = __libc_core_mempmoveupq(__dst, __src, __n_bytes >> 3);
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
			return (__UINT8_TYPE__ *)__dst + 1;
		case 2:
			__dst = __libc_core_mempmoveupq(__dst, __src, __n_bytes >> 3);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1) - 1];
			return (__UINT8_TYPE__ *)__dst + 2;
		case 4:
			__dst = __libc_core_mempmoveupq(__dst, __src, __n_bytes >> 3);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[(__n_bytes >> 2) - 1];
			return (__UINT8_TYPE__ *)__dst + 4;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 7))
			return __libc_core_mempmoveupq(__dst, __src, __n_bytes >> 3);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmoveupq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_mempmoveupl)
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_bytes & 3) {
		case 0:
			return __libc_core_mempmoveupl(__dst, __src, __n_bytes >> 2);
		case 1:
			__dst = __libc_core_mempmoveupl(__dst, __src, __n_bytes >> 2);
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
			return (__UINT8_TYPE__ *)__dst + 1;
		case 2:
			__dst = __libc_core_mempmoveupl(__dst, __src, __n_bytes >> 2);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1) - 1];
			return (__UINT8_TYPE__ *)__dst + 2;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 3))
			return __libc_core_mempmoveupl(__dst, __src, __n_bytes >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmoveupl */
#if defined(__CRT_HAVE_mempmoveupw)
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_bytes & 1))
			return __libc_core_mempmoveupw(__dst, __src, __n_bytes >> 1);
		__dst = __libc_core_mempmoveupw(__dst, __src, __n_bytes >> 1);
		((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
		return (__UINT8_TYPE__ *)__dst + 1;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 1))
			return __libc_core_mempmoveupw(__dst, __src, __n_bytes >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmoveupw */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_mempmoveup(__dst, __src, __n_bytes);
}
#endif /* !__fast_mempmoveup_defined */


#undef __ASSERT_MEMMOVEUP_RT
#undef __ASSERT_MEMMOVEDOWN_RT


#ifdef __UINT64_TYPE__
#ifndef __fast_memmoveq_defined
#define __fast_memmoveq_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(8)*/ __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memmoveq))(/*aligned(8)*/ void *__dst,
                                          /*aligned(8)*/ void const *__src,
                                          __SIZE_TYPE__ __n_qwords) {
	if __untraced(__builtin_constant_p(__dst == __src) && (__dst == __src))
		return (__UINT64_TYPE__ *)__dst;
#ifdef __OPTIMIZE_STRING_MEMOVE_DIRECTION
	if __untraced(__builtin_constant_p(__dst >= __src) && (__dst >= __src))
		return (__LIBC_FAST_NAME(memmoveupq))(__dst, __src, __n_qwords);
	if __untraced(__builtin_constant_p(__dst <= __src) && (__dst <= __src))
		return (__LIBC_FAST_NAME(memmovedownq))(__dst, __src, __n_qwords);
#endif /* __OPTIMIZE_STRING_MEMOVE_DIRECTION */
	if __untraced(__builtin_constant_p(__n_qwords)) {
		/* Optimizations  when the move  can be done using
		 * at most 2 read/writes, and at most 1 temporary. */
		switch __untraced(__n_qwords) {
		case 0:
			return (__UINT64_TYPE__ *)__dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 1:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT64_TYPE__ *)__dst;
		case 2: {
			__UINT64_TYPE__ __temp;
			__temp = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp;
			return (__UINT64_TYPE__ *)__dst;
		}	break;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 1: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp;
			return (__UINT64_TYPE__ *)__dst;
		}	break;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
		/* More optimizations when the move can be done using
		 * at most 4 read/writes, and at most 3  temporaries. */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 3: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			return (__UINT64_TYPE__ *)__dst;
		}	break;

		case 4: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__UINT64_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT64_TYPE__ const *)__src)[3];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			((__UINT64_TYPE__ *)__dst)[3] = __temp3;
			return (__UINT64_TYPE__ *)__dst;
		}	break;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 2: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT32_TYPE__ __temp3;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT32_TYPE__ const *)__src)[3];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			((__UINT32_TYPE__ *)__dst)[3] = __temp3;
			return (__UINT64_TYPE__ *)__dst;
		}	break;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */

		default:
			break;
		}
	}
	return __libc_core_memmoveq(__dst, __src, __n_qwords);
}
#endif /* !__fast_memmoveq_defined */
#endif /* __UINT64_TYPE__ */

#ifndef __fast_memmovel_defined
#define __fast_memmovel_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memmovel))(/*aligned(4)*/ void *__dst,
                                          /*aligned(4)*/ void const *__src,
                                          __SIZE_TYPE__ __n_dwords) {
	if __untraced(__builtin_constant_p(__dst == __src) && (__dst == __src))
		return (__UINT32_TYPE__ *)__dst;
#ifdef __OPTIMIZE_STRING_MEMOVE_DIRECTION
	if __untraced(__builtin_constant_p(__dst >= __src) && (__dst >= __src))
		return (__LIBC_FAST_NAME(memmoveupl))(__dst, __src, __n_dwords);
	if __untraced(__builtin_constant_p(__dst <= __src) && (__dst <= __src))
		return (__LIBC_FAST_NAME(memmovedownl))(__dst, __src, __n_dwords);
#endif /* __OPTIMIZE_STRING_MEMOVE_DIRECTION */
	if __untraced(__builtin_constant_p(__n_dwords)) {
		/* Optimizations  when the move  can be done using
		 * at most 2 read/writes, and at most 1 temporary. */
		switch __untraced(__n_dwords) {
		case 0:
			return (__UINT32_TYPE__ *)__dst;
		case 1:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp;
			return (__UINT32_TYPE__ *)__dst;
		}	break;
		case 3: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			return (__UINT32_TYPE__ *)__dst;
		}	break;
		case 4: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT32_TYPE__ __temp3;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT32_TYPE__ const *)__src)[3];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			((__UINT32_TYPE__ *)__dst)[3] = __temp3;
			return (__UINT32_TYPE__ *)__dst;
		}	break;
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 2:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
		case 3: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = __temp;
			return (__UINT32_TYPE__ *)__dst;
		}	break;

		case 4: {
			__UINT64_TYPE__ __temp;
			__temp = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp;
			return (__UINT32_TYPE__ *)__dst;
		}	break;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 2: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp;
			return (__UINT32_TYPE__ *)__dst;
		}	break;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

		/* More optimizations when the move can be done using
		 * at most 4 read/writes, and at most 3  temporaries. */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 5: {
			__UINT64_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[4] = __temp2;
			return (__UINT32_TYPE__ *)__dst;
		}	break;

		case 6: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			return (__UINT32_TYPE__ *)__dst;
		}	break;

		case 7: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__UINT32_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT32_TYPE__ const *)__src)[6];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			((__UINT32_TYPE__ *)__dst)[6] = __temp3;
			return (__UINT32_TYPE__ *)__dst;
		}	break;

		case 8: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__UINT64_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT64_TYPE__ const *)__src)[3];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			((__UINT64_TYPE__ *)__dst)[3] = __temp3;
			return (__UINT32_TYPE__ *)__dst;
		}	break;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 3: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			return (__UINT32_TYPE__ *)__dst;
		}	break;

		case 4: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT32_TYPE__ __temp3;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT32_TYPE__ const *)__src)[3];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			((__UINT32_TYPE__ *)__dst)[3] = __temp3;
			return (__UINT32_TYPE__ *)__dst;
		}	break;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */

		default: break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_memmoveq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_core_memmoveq(__dst, __src, __n_dwords >> 1);
		{
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[__n_dwords - 1];
			__dst = __libc_core_memmoveq(__dst, __src, __n_dwords >> 1);
			((__UINT32_TYPE__ *)__dst)[__n_dwords - 1] = __temp;
		}
		return (__UINT32_TYPE__ *)__dst;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_core_memmoveq(__dst, __src, __n_dwords >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmoveq && __SIZEOF_BUSINT__ >= 8 */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_memmovel(__dst, __src, __n_dwords);
}
#endif /* !__fast_memmovel_defined */

#ifndef __fast_memmovew_defined
#define __fast_memmovew_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(memmovew))(/*aligned(2)*/ void *__dst,
                                          /*aligned(2)*/ void const *__src,
                                          __SIZE_TYPE__ __n_words) {
	if __untraced(__builtin_constant_p(__dst == __src) && (__dst == __src))
		return (__UINT16_TYPE__ *)__dst;
#ifdef __OPTIMIZE_STRING_MEMOVE_DIRECTION
	if __untraced(__builtin_constant_p(__dst >= __src) && (__dst >= __src))
		return (__LIBC_FAST_NAME(memmoveupw))(__dst, __src, __n_words);
	if __untraced(__builtin_constant_p(__dst <= __src) && (__dst <= __src))
		return (__LIBC_FAST_NAME(memmovedownw))(__dst, __src, __n_words);
#endif /* __OPTIMIZE_STRING_MEMOVE_DIRECTION */
	if __untraced(__builtin_constant_p(__n_words)) {
		/* Optimizations  when the move  can be done using
		 * at most 2 read/writes, and at most 1 temporary. */
		switch __untraced(__n_words) {
		case 0:
			return (__UINT16_TYPE__ *)__dst;
		case 1:
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[1] = __temp;
			return (__UINT16_TYPE__ *)__dst;
		}	break;
		case 3: {
			__UINT16_TYPE__ __temp1;
			__UINT16_TYPE__ __temp2;
			__temp1 = ((__UINT16_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[1] = __temp1;
			((__UINT16_TYPE__ *)__dst)[2] = __temp2;
			return (__UINT16_TYPE__ *)__dst;
		}	break;
		case 4: {
			__UINT16_TYPE__ __temp1;
			__UINT16_TYPE__ __temp2;
			__UINT16_TYPE__ __temp3;
			__temp1 = ((__UINT16_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT16_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT16_TYPE__ const *)__src)[3];
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[1] = __temp1;
			((__UINT16_TYPE__ *)__dst)[2] = __temp2;
			((__UINT16_TYPE__ *)__dst)[3] = __temp3;
			return (__UINT16_TYPE__ *)__dst;
		}	break;
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		case 2:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 3: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[2] = __temp;
			return (__UINT16_TYPE__ *)__dst;
		}	break;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 4:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 5: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[4] = __temp;
			return (__UINT16_TYPE__ *)__dst;
		}	break;

		case 6: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = __temp;
			return (__UINT16_TYPE__ *)__dst;
		}	break;

		case 8: {
			__UINT64_TYPE__ __temp;
			__temp = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp;
			return (__UINT16_TYPE__ *)__dst;
		}	break;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 4: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp;
			return (__UINT16_TYPE__ *)__dst;
		}	break;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

		/* More optimizations when the move can be done using
		 * at most 4 read/writes, and at most 3  temporaries. */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 9: {
			__UINT64_TYPE__ __temp1;
			__UINT16_TYPE__ __temp2;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT16_TYPE__ const *)__src)[8];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT16_TYPE__ *)__dst)[8] = __temp2;
			return (__UINT16_TYPE__ *)__dst;
		}	break;

		case 10: {
			__UINT64_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[4] = __temp2;
			return (__UINT16_TYPE__ *)__dst;
		}	break;

		case 11: {
			__UINT64_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT16_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[4];
			__temp3 = ((__UINT16_TYPE__ const *)__src)[10];
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = __temp1;
			((__UINT32_TYPE__ *)__dst)[4]  = __temp2;
			((__UINT16_TYPE__ *)__dst)[10] = __temp3;
			return (__UINT16_TYPE__ *)__dst;
		}	break;

		case 12: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			return (__UINT16_TYPE__ *)__dst;
		}	break;

		case 13: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__UINT16_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT16_TYPE__ const *)__src)[12];
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = __temp1;
			((__UINT64_TYPE__ *)__dst)[2]  = __temp2;
			((__UINT16_TYPE__ *)__dst)[12] = __temp3;
			return (__UINT16_TYPE__ *)__dst;
		}	break;

		case 14: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__UINT32_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT32_TYPE__ const *)__src)[6];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			((__UINT32_TYPE__ *)__dst)[6] = __temp3;
			return (__UINT16_TYPE__ *)__dst;
		}	break;

		case 16: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__UINT64_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT64_TYPE__ const *)__src)[3];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			((__UINT64_TYPE__ *)__dst)[3] = __temp3;
			return (__UINT16_TYPE__ *)__dst;
		}	break;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 5: {
			__UINT32_TYPE__ __temp1;
			__UINT16_TYPE__ __temp2;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT16_TYPE__ *)__dst)[4] = __temp2;
			return (__UINT16_TYPE__ *)__dst;
		}	break;

		case 6: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			return (__UINT16_TYPE__ *)__dst;
		}	break;

		case 7: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT16_TYPE__ __temp3;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT16_TYPE__ const *)__src)[6];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			((__UINT16_TYPE__ *)__dst)[6] = __temp3;
			return (__UINT16_TYPE__ *)__dst;
		}	break;

		case 8: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT32_TYPE__ __temp3;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT32_TYPE__ const *)__src)[3];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			((__UINT32_TYPE__ *)__dst)[3] = __temp3;
			return (__UINT16_TYPE__ *)__dst;
		}	break;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */

		default:
			break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_memmoveq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_words & 3) {
		case 0:
			return (__UINT16_TYPE__ *)__libc_core_memmoveq(__dst, __src, __n_words >> 2);
		case 1: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[__n_words - 1];
			__dst = __libc_core_memmoveq(__dst, __src, __n_words >> 2);
			((__UINT16_TYPE__ *)__dst)[__n_words - 1] = __temp;
			return (__UINT16_TYPE__ *)__dst;
		}	break;

		case 2: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[(__n_words >> 1) - 1];
			__dst = __libc_core_memmoveq(__dst, __src, __n_words >> 2);
			((__UINT32_TYPE__ *)__dst)[(__n_words >> 1) - 1] = __temp;
			return (__UINT16_TYPE__ *)__dst;
		}
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_words & 3))
			return (__UINT16_TYPE__ *)__libc_core_memmoveq(__dst, __src, __n_words >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmoveq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_memmovel)
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_core_memmovel(__dst, __src, __n_words >> 1);
		{
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[__n_words - 1];
			__dst = __libc_core_memmovel(__dst, __src, __n_words >> 1);
			((__UINT16_TYPE__ *)__dst)[__n_words - 1] = __temp;
		}
		return (__UINT16_TYPE__ *)__dst;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_core_memmovel(__dst, __src, __n_words >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmovel */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_memmovew(__dst, __src, __n_words);
}
#endif /* !__fast_memmovew_defined */

#ifndef __fast_memmove_defined
#define __fast_memmove_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(memmove))(/*aligned(1)*/ void *__dst,
                                         /*aligned(1)*/ void const *__src,
                                         __SIZE_TYPE__ __n_bytes) {
	if __untraced(__builtin_constant_p(__dst == __src) && (__dst == __src))
		return __dst;
#ifdef __OPTIMIZE_STRING_MEMOVE_DIRECTION
	if __untraced(__builtin_constant_p(__dst >= __src) && (__dst >= __src))
		return (__LIBC_FAST_NAME(memmoveup))(__dst, __src, __n_bytes);
	if __untraced(__builtin_constant_p(__dst <= __src) && (__dst <= __src))
		return (__LIBC_FAST_NAME(memmovedown))(__dst, __src, __n_bytes);
#endif /* __OPTIMIZE_STRING_MEMOVE_DIRECTION */
	if __untraced(__builtin_constant_p(__n_bytes)) {
		/* Optimizations  when the move  can be done using
		 * at most 2 read/writes, and at most 1 temporary. */
		switch __untraced(__n_bytes) {
		case 0:
			return __dst;
		case 1:
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			return __dst;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2: {
			__UINT8_TYPE__ __temp;
			__temp = ((__UINT8_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[1] = __temp;
			return (__UINT8_TYPE__ *)__dst;
		}	break;
		case 3: {
			__UINT8_TYPE__ __temp1;
			__UINT8_TYPE__ __temp2;
			__temp1 = ((__UINT8_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT8_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[1] = __temp1;
			((__UINT8_TYPE__ *)__dst)[2] = __temp2;
			return (__UINT8_TYPE__ *)__dst;
		}	break;
		case 4: {
			__UINT8_TYPE__ __temp1;
			__UINT8_TYPE__ __temp2;
			__UINT8_TYPE__ __temp3;
			__temp1 = ((__UINT8_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT8_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT8_TYPE__ const *)__src)[3];
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[1] = __temp1;
			((__UINT8_TYPE__ *)__dst)[2] = __temp2;
			((__UINT8_TYPE__ *)__dst)[3] = __temp3;
			return (__UINT8_TYPE__ *)__dst;
		}	break;
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		case 2:
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return __dst;

		case 3: {
			__UINT8_TYPE__ __temp;
			__temp = ((__UINT8_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[2] = __temp;
			return __dst;
		}	break;

		case 4:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return __dst;

		case 5: {
			__UINT8_TYPE__ __temp;
			__temp = ((__UINT8_TYPE__ const *)__src)[4];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[4] = __temp;
			return __dst;
		}	break;

		case 6: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[2] = __temp;
			return __dst;
		}	break;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 8:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return __dst;
		case 9: {
			__UINT8_TYPE__ __temp;
			__temp = ((__UINT8_TYPE__ const *)__src)[8];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[8] = __temp;
			return __dst;
		}	break;

		case 10: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[4] = __temp;
			return __dst;
		}	break;

		case 12: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = __temp;
			return __dst;
		}	break;

		case 16: {
			__UINT64_TYPE__ __temp;
			__temp = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp;
			return __dst;
		}	break;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 8: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp;
			return __dst;
		}	break;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

		/* More optimizations when the move can be done using
		 * at most 4 read/writes, and at most 3  temporaries. */
#ifndef __OPTIMIZE_SIZE__
		case 7: {
			__UINT16_TYPE__ __temp1;
			__UINT8_TYPE__ __temp2;
			__temp1 = ((__UINT16_TYPE__ const *)__src)[2];
			__temp2 = ((__UINT8_TYPE__ const *)__src)[6];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[2] = __temp1;
			((__UINT8_TYPE__ *)__dst)[6] = __temp2;
			return __dst;
		}	break;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 11: {
			__UINT16_TYPE__ __temp1;
			__UINT8_TYPE__ __temp2;
			__temp1 = ((__UINT16_TYPE__ const *)__src)[4];
			__temp2 = ((__UINT8_TYPE__ const *)__src)[10];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[4] = __temp1;
			((__UINT8_TYPE__ *)__dst)[10] = __temp2;
			return __dst;
		}	break;

		case 13: {
			__UINT32_TYPE__ __temp1;
			__UINT8_TYPE__ __temp2;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp2 = ((__UINT8_TYPE__ const *)__src)[12];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = __temp1;
			((__UINT8_TYPE__ *)__dst)[12] = __temp2;
			return __dst;
		}	break;

		case 14: {
			__UINT32_TYPE__ __temp1;
			__UINT16_TYPE__ __temp2;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp2 = ((__UINT16_TYPE__ const *)__src)[6];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = __temp1;
			((__UINT16_TYPE__ *)__dst)[6] = __temp2;
			return __dst;
		}	break;

		case 15: {
			__UINT32_TYPE__ __temp1;
			__UINT16_TYPE__ __temp2;
			__UINT8_TYPE__ __temp3;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp2 = ((__UINT16_TYPE__ const *)__src)[6];
			__temp3 = ((__UINT8_TYPE__ const *)__src)[14];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = __temp1;
			((__UINT16_TYPE__ *)__dst)[6] = __temp2;
			((__UINT8_TYPE__ *)__dst)[14] = __temp3;
			return __dst;
		}	break;

		case 17: {
			__UINT64_TYPE__ __temp1;
			__UINT8_TYPE__ __temp2;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT8_TYPE__ const *)__src)[16];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT8_TYPE__ *)__dst)[16] = __temp2;
			return __dst;
		}	break;

		case 18: {
			__UINT64_TYPE__ __temp1;
			__UINT16_TYPE__ __temp2;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT16_TYPE__ const *)__src)[8];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT16_TYPE__ *)__dst)[8] = __temp2;
			return __dst;
		}	break;

		case 19: {
			__UINT64_TYPE__ __temp1;
			__UINT16_TYPE__ __temp2;
			__UINT8_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT16_TYPE__ const *)__src)[8];
			__temp3 = ((__UINT8_TYPE__ const *)__src)[18];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT16_TYPE__ *)__dst)[8] = __temp2;
			((__UINT8_TYPE__ *)__dst)[18] = __temp3;
			return __dst;
		}	break;

		case 20: {
			__UINT64_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[4] = __temp2;
			return __dst;
		}	break;

		case 21: {
			__UINT64_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT8_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[4];
			__temp3 = ((__UINT8_TYPE__ const *)__src)[20];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[4] = __temp2;
			((__UINT8_TYPE__ *)__dst)[20] = __temp3;
			return __dst;
		}	break;

		case 22: {
			__UINT64_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT16_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[4];
			__temp3 = ((__UINT16_TYPE__ const *)__src)[10];
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = __temp1;
			((__UINT32_TYPE__ *)__dst)[4]  = __temp2;
			((__UINT16_TYPE__ *)__dst)[10] = __temp3;
			return __dst;
		}	break;

		case 24: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			return __dst;
		}	break;

		case 25: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__UINT8_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT8_TYPE__ const *)__src)[24];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			((__UINT8_TYPE__ *)__dst)[24] = __temp3;
			return __dst;
		}	break;

		case 26: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__UINT16_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT16_TYPE__ const *)__src)[12];
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = __temp1;
			((__UINT64_TYPE__ *)__dst)[2]  = __temp2;
			((__UINT16_TYPE__ *)__dst)[12] = __temp3;
			return __dst;
		}	break;

		case 28: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__UINT32_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT32_TYPE__ const *)__src)[6];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			((__UINT32_TYPE__ *)__dst)[6] = __temp3;
			return __dst;
		}	break;

		case 32: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__UINT64_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT64_TYPE__ const *)__src)[3];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			((__UINT64_TYPE__ *)__dst)[3] = __temp3;
			return __dst;
		}	break;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 9: {
			__UINT32_TYPE__ __temp1;
			__UINT8_TYPE__ __temp2;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT8_TYPE__ const *)__src)[8];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT8_TYPE__ *)__dst)[8]  = __temp2;
			return __dst;
		}	break;

		case 10: {
			__UINT32_TYPE__ __temp1;
			__UINT16_TYPE__ __temp2;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT16_TYPE__ *)__dst)[4] = __temp2;
			return __dst;
		}	break;

		case 11: {
			__UINT32_TYPE__ __temp1;
			__UINT16_TYPE__ __temp2;
			__UINT8_TYPE__ __temp3;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT16_TYPE__ const *)__src)[4];
			__temp3 = ((__UINT8_TYPE__ const *)__src)[10];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT16_TYPE__ *)__dst)[4] = __temp2;
			((__UINT8_TYPE__ *)__dst)[10] = __temp3;
			return __dst;
		}	break;

		case 12: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			return __dst;
		}	break;

		case 13: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT8_TYPE__ __temp3;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT8_TYPE__ const *)__src)[12];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			((__UINT8_TYPE__ *)__dst)[12] = __temp3;
			return __dst;
		}	break;

		case 14: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT16_TYPE__ __temp3;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT16_TYPE__ const *)__src)[6];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			((__UINT16_TYPE__ *)__dst)[6] = __temp3;
			return __dst;
		}	break;

		case 16: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT32_TYPE__ __temp3;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT32_TYPE__ const *)__src)[3];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			((__UINT32_TYPE__ *)__dst)[3] = __temp3;
			return __dst;
		}	break;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */

		default:
			break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_memmoveq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_bytes & 7) {
		case 0:
			return __libc_core_memmoveq(__dst, __src, __n_bytes >> 3);
		case 1: {
			__UINT8_TYPE__ __temp;
			__temp = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
			__dst = __libc_core_memmoveq(__dst, __src, __n_bytes >> 3);
			((__UINT8_TYPE__ *)__dst)[__n_bytes - 1] = __temp;
			return __dst;
		}	break;

		case 2: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1) - 1];
			__dst = __libc_core_memmoveq(__dst, __src, __n_bytes >> 3);
			((__UINT16_TYPE__ *)__dst)[(__n_bytes >> 1) - 1] = __temp;
			return __dst;
		}	break;

		case 4: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[(__n_bytes >> 2) - 1];
			__dst = __libc_core_memmoveq(__dst, __src, __n_bytes >> 3);
			((__UINT32_TYPE__ *)__dst)[(__n_bytes >> 2) - 1] = __temp;
			return __dst;
		}
		default:
			break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 7))
			return __libc_core_memmoveq(__dst, __src, __n_bytes >> 3);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmoveq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_memmovel)
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_bytes & 3) {
		case 0:
			return __libc_core_memmovel(__dst, __src, __n_bytes >> 2);
		case 1: {
			__UINT8_TYPE__ __temp;
			__temp = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
			__dst = __libc_core_memmovel(__dst, __src, __n_bytes >> 2);
			((__UINT8_TYPE__ *)__dst)[__n_bytes - 1] = __temp;
			return __dst;
		}	break;

		case 2: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1) - 1];
			__dst = __libc_core_memmovel(__dst, __src, __n_bytes >> 2);
			((__UINT16_TYPE__ *)__dst)[(__n_bytes >> 1) - 1] = __temp;
			return __dst;
		}
		default:
			break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 3))
			return __libc_core_memmovel(__dst, __src, __n_bytes >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmovel */
#if defined(__CRT_HAVE_memmovew)
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_bytes & 1))
			return __libc_core_memmovew(__dst, __src, __n_bytes >> 1);
		{
			__UINT8_TYPE__ __temp;
			__temp = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
			__dst = __libc_core_memmovew(__dst, __src, __n_bytes >> 1);
			((__UINT8_TYPE__ *)__dst)[__n_bytes - 1] = __temp;
		}
		return __dst;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 1))
			return __libc_core_memmovew(__dst, __src, __n_bytes >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmovew */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_memmove(__dst, __src, __n_bytes);
}
#endif /* !__fast_memmove_defined */

#ifdef __UINT64_TYPE__
#ifndef __fast_mempmoveq_defined
#define __fast_mempmoveq_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempmoveq))(/*aligned(8)*/ void *__dst,
                                           /*aligned(8)*/ void const *__src,
                                           __SIZE_TYPE__ __n_qwords) {
	if __untraced(__builtin_constant_p(__dst == __src) && (__dst == __src))
		return (__UINT64_TYPE__ *)__dst + __n_qwords;
#ifdef __OPTIMIZE_STRING_MEMOVE_DIRECTION
	if __untraced(__builtin_constant_p(__dst >= __src) && (__dst >= __src))
		return (__LIBC_FAST_NAME(mempmoveupq))(__dst, __src, __n_qwords);
	if __untraced(__builtin_constant_p(__dst <= __src) && (__dst <= __src))
		return (__LIBC_FAST_NAME(memmovedownq))(__dst, __src, __n_qwords);
#endif /* __OPTIMIZE_STRING_MEMOVE_DIRECTION */
	if __untraced(__builtin_constant_p(__n_qwords)) {
		/* Optimizations  when the move  can be done using
		 * at most 2 read/writes, and at most 1 temporary. */
		switch __untraced(__n_qwords) {
		case 0:
			return (__UINT64_TYPE__ *)__dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 1:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT64_TYPE__ *)((__BYTE_TYPE__ *)__dst + 8);
		case 2: {
			__UINT64_TYPE__ __temp;
			__temp = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp;
			return (__UINT64_TYPE__ *)((__BYTE_TYPE__ *)__dst + 16);
		}	break;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 1: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp;
			return (__UINT64_TYPE__ *)((__BYTE_TYPE__ *)__dst + 8);
		}	break;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

		/* More optimizations when the move can be done using
		 * at most 4 read/writes, and at most 3  temporaries. */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 3: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			return (__UINT64_TYPE__ *)((__BYTE_TYPE__ *)__dst + 24);
		}	break;

		case 4: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__UINT64_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT64_TYPE__ const *)__src)[3];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			((__UINT64_TYPE__ *)__dst)[3] = __temp3;
			return (__UINT64_TYPE__ *)((__BYTE_TYPE__ *)__dst + 32);
		}	break;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 2: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT32_TYPE__ __temp3;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT32_TYPE__ const *)__src)[3];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			((__UINT32_TYPE__ *)__dst)[3] = __temp3;
			return (__UINT64_TYPE__ *)((__BYTE_TYPE__ *)__dst + 16);
		}	break;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */

		default:
			break;
		}
	}
	return __libc_core_mempmoveq(__dst, __src, __n_qwords);
}
#endif /* !__fast_mempmoveq_defined */
#endif /* __UINT64_TYPE__ */

#ifndef __fast_mempmovel_defined
#define __fast_mempmovel_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(4)*/ __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempmovel))(/*aligned(4)*/ void *__dst,
                                           /*aligned(4)*/ void const *__src,
                                           __SIZE_TYPE__ __n_dwords) {
	if __untraced(__builtin_constant_p(__dst == __src) && (__dst == __src))
		return (__UINT32_TYPE__ *)__dst + __n_dwords;
#ifdef __OPTIMIZE_STRING_MEMOVE_DIRECTION
	if __untraced(__builtin_constant_p(__dst >= __src) && (__dst >= __src))
		return (__LIBC_FAST_NAME(mempmoveupl))(__dst, __src, __n_dwords);
	if __untraced(__builtin_constant_p(__dst <= __src) && (__dst <= __src))
		return (__LIBC_FAST_NAME(memmovedownl))(__dst, __src, __n_dwords);
#endif /* __OPTIMIZE_STRING_MEMOVE_DIRECTION */
	if __untraced(__builtin_constant_p(__n_dwords)) {
		/* Optimizations  when the move  can be done using
		 * at most 2 read/writes, and at most 1 temporary. */
		switch __untraced(__n_dwords) {
		case 0:
			return (__UINT32_TYPE__ *)__dst;
		case 1:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)((__BYTE_TYPE__ *)__dst + 4);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp;
			return (__UINT32_TYPE__ *)__dst + 2;
		}	break;
		case 3: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			return (__UINT32_TYPE__ *)__dst + 3;
		}	break;
		case 4: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT32_TYPE__ __temp3;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT32_TYPE__ const *)__src)[3];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			((__UINT32_TYPE__ *)__dst)[3] = __temp3;
			return (__UINT32_TYPE__ *)__dst + 4;
		}	break;
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 2:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)((__BYTE_TYPE__ *)__dst + 8);
		case 3: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = __temp;
			return (__UINT32_TYPE__ *)((__BYTE_TYPE__ *)__dst + 12);
		}	break;

		case 4: {
			__UINT64_TYPE__ __temp;
			__temp = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp;
			return (__UINT32_TYPE__ *)((__BYTE_TYPE__ *)__dst + 16);
		}	break;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 2: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp;
			return (__UINT32_TYPE__ *)((__BYTE_TYPE__ *)__dst + 8);
		}	break;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

		/* More optimizations when the move can be done using
		 * at most 4 read/writes, and at most 3  temporaries. */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 5: {
			__UINT64_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[4] = __temp2;
			return (__UINT32_TYPE__ *)((__BYTE_TYPE__ *)__dst + 20);
		}	break;

		case 6: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			return (__UINT32_TYPE__ *)((__BYTE_TYPE__ *)__dst + 24);
		}	break;

		case 7: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__UINT32_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT32_TYPE__ const *)__src)[6];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			((__UINT32_TYPE__ *)__dst)[6] = __temp3;
			return (__UINT32_TYPE__ *)((__BYTE_TYPE__ *)__dst + 28);
		}	break;

		case 8: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__UINT64_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT64_TYPE__ const *)__src)[3];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			((__UINT64_TYPE__ *)__dst)[3] = __temp3;
			return (__UINT32_TYPE__ *)((__BYTE_TYPE__ *)__dst + 32);
		}	break;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 3: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			return (__UINT32_TYPE__ *)((__BYTE_TYPE__ *)__dst + 12);
		}	break;

		case 4: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT32_TYPE__ __temp3;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT32_TYPE__ const *)__src)[3];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			((__UINT32_TYPE__ *)__dst)[3] = __temp3;
			return (__UINT32_TYPE__ *)((__BYTE_TYPE__ *)__dst + 16);
		}	break;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */

		default:
			break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_mempmoveq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_core_mempmoveq(__dst, __src, __n_dwords >> 1);
		{
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[__n_dwords - 1];
			__dst = __libc_core_mempmoveq(__dst, __src, __n_dwords >> 1);
			((__UINT32_TYPE__ *)__dst)[0] = __temp;
		}
		return (__UINT32_TYPE__ *)__dst + 1;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_core_mempmoveq(__dst, __src, __n_dwords >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmoveq && __SIZEOF_BUSINT__ >= 8 */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_mempmovel(__dst, __src, __n_dwords);
}
#endif /* !__fast_mempmovel_defined */

#ifndef __fast_mempmovew_defined
#define __fast_mempmovew_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(2)*/ __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempmovew))(/*aligned(2)*/ void *__dst,
                                           /*aligned(2)*/ void const *__src,
                                           __SIZE_TYPE__ __n_words) {
	if __untraced(__builtin_constant_p(__dst == __src) && (__dst == __src))
		return (__UINT16_TYPE__ *)__dst + __n_words;
#ifdef __OPTIMIZE_STRING_MEMOVE_DIRECTION
	if __untraced(__builtin_constant_p(__dst >= __src) && (__dst >= __src))
		return (__LIBC_FAST_NAME(mempmoveupw))(__dst, __src, __n_words);
	if __untraced(__builtin_constant_p(__dst <= __src) && (__dst <= __src))
		return (__LIBC_FAST_NAME(memmovedownw))(__dst, __src, __n_words);
#endif /* __OPTIMIZE_STRING_MEMOVE_DIRECTION */
	if __untraced(__builtin_constant_p(__n_words)) {
		/* Optimizations  when the move  can be done using
		 * at most 2 read/writes, and at most 1 temporary. */
		switch __untraced(__n_words) {
		case 0:
			return (__UINT16_TYPE__ *)__dst;
		case 1:
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 2);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[1];
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[1] = __temp;
			return (__UINT16_TYPE__ *)__dst + 2;
		}	break;
		case 3: {
			__UINT16_TYPE__ __temp1;
			__UINT16_TYPE__ __temp2;
			__temp1 = ((__UINT16_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[1] = __temp1;
			((__UINT16_TYPE__ *)__dst)[2] = __temp2;
			return (__UINT16_TYPE__ *)__dst + 3;
		}	break;
		case 4: {
			__UINT16_TYPE__ __temp1;
			__UINT16_TYPE__ __temp2;
			__UINT16_TYPE__ __temp3;
			__temp1 = ((__UINT16_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT16_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT16_TYPE__ const *)__src)[3];
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[1] = __temp1;
			((__UINT16_TYPE__ *)__dst)[2] = __temp2;
			((__UINT16_TYPE__ *)__dst)[3] = __temp3;
			return (__UINT16_TYPE__ *)__dst + 4;
		}	break;
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		case 2:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 4);
		case 3: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[2] = __temp;
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 6);
		}	break;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 4:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 8);
		case 5: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[4] = __temp;
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 10);
		}	break;

		case 6: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = __temp;
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 12);
		}	break;

		case 8: {
			__UINT64_TYPE__ __temp;
			__temp = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp;
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 16);
		}	break;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 4: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp;
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 8);
		}	break;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

		/* More optimizations when the move can be done using
		 * at most 4 read/writes, and at most 3  temporaries. */
#ifndef __OPTIMIZE_SIZE__
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 9: {
			__UINT64_TYPE__ __temp1;
			__UINT16_TYPE__ __temp2;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT16_TYPE__ const *)__src)[8];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT16_TYPE__ *)__dst)[8] = __temp2;
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 18);
		}	break;

		case 10: {
			__UINT64_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[4] = __temp2;
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 20);
		}	break;

		case 11: {
			__UINT64_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT16_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[4];
			__temp3 = ((__UINT16_TYPE__ const *)__src)[10];
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = __temp1;
			((__UINT32_TYPE__ *)__dst)[4]  = __temp2;
			((__UINT16_TYPE__ *)__dst)[10] = __temp3;
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 22);
		}	break;

		case 12: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 24);
		}	break;

		case 13: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__UINT16_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT16_TYPE__ const *)__src)[12];
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = __temp1;
			((__UINT64_TYPE__ *)__dst)[2]  = __temp2;
			((__UINT16_TYPE__ *)__dst)[12] = __temp3;
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 26);
		}	break;

		case 14: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__UINT32_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT32_TYPE__ const *)__src)[6];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			((__UINT32_TYPE__ *)__dst)[6] = __temp3;
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 28);
		}	break;

		case 16: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__UINT64_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT64_TYPE__ const *)__src)[3];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			((__UINT64_TYPE__ *)__dst)[3] = __temp3;
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 32);
		}	break;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 5: {
			__UINT32_TYPE__ __temp1;
			__UINT16_TYPE__ __temp2;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT16_TYPE__ *)__dst)[4] = __temp2;
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 10);
		}	break;

		case 6: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 12);
		}	break;

		case 7: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT16_TYPE__ __temp3;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT16_TYPE__ const *)__src)[6];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			((__UINT16_TYPE__ *)__dst)[6] = __temp3;
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 14);
		}	break;

		case 8: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT32_TYPE__ __temp3;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT32_TYPE__ const *)__src)[3];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			((__UINT32_TYPE__ *)__dst)[3] = __temp3;
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 16);
		}	break;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */

		default:
			break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_mempmoveq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_words & 3) {
		case 0:
			return (__UINT16_TYPE__ *)__libc_core_mempmoveq(__dst, __src, __n_words >> 2);
		case 1: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[__n_words - 1];
			__dst = __libc_core_mempmoveq(__dst, __src, __n_words >> 2);
			((__UINT16_TYPE__ *)__dst)[0] = __temp;
			return (__UINT16_TYPE__ *)__dst + 1;
		}	break;

		case 2: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[(__n_words >> 1) - 1];
			__dst = __libc_core_mempmoveq(__dst, __src, __n_words >> 2);
			((__UINT32_TYPE__ *)__dst)[0] = __temp;
			return (__UINT16_TYPE__ *)__dst + 2;
		}
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_words & 3))
			return (__UINT16_TYPE__ *)__libc_core_mempmoveq(__dst, __src, __n_words >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmoveq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_mempmovel)
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_core_mempmovel(__dst, __src, __n_words >> 1);
		{
			__UINT16_TYPE__ __temp = ((__UINT16_TYPE__ const *)__src)[__n_words - 1];
			__dst = __libc_core_mempmovel(__dst, __src, __n_words >> 1);
			((__UINT16_TYPE__ *)__dst)[0] = __temp;
		}
		return (__UINT16_TYPE__ *)__dst + 1;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_core_mempmovel(__dst, __src, __n_words >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmovel */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_mempmovew(__dst, __src, __n_words);
}
#endif /* !__fast_mempmovew_defined */

#ifndef __fast_mempmove_defined
#define __fast_mempmove_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) /*aligned(1)*/ void *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempmove))(/*aligned(1)*/ void *__dst,
                                          /*aligned(1)*/ void const *__src,
                                          __SIZE_TYPE__ __n_bytes) {
	if __untraced(__builtin_constant_p(__dst == __src) && (__dst == __src))
		return (__UINT8_TYPE__ *)__dst + __n_bytes;
#ifdef __OPTIMIZE_STRING_MEMOVE_DIRECTION
	if __untraced(__builtin_constant_p(__dst >= __src) && (__dst >= __src))
		return (__LIBC_FAST_NAME(mempmoveup))(__dst, __src, __n_bytes);
	if __untraced(__builtin_constant_p(__dst <= __src) && (__dst <= __src))
		return (__LIBC_FAST_NAME(memmovedown))(__dst, __src, __n_bytes);
#endif /* __OPTIMIZE_STRING_MEMOVE_DIRECTION */
	if __untraced(__builtin_constant_p(__n_bytes)) {
		/* Optimizations  when the move  can be done using
		 * at most 2 read/writes, and at most 1 temporary. */
		switch __untraced(__n_bytes) {
		case 0:
			return __dst;
		case 1:
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			return (__BYTE_TYPE__ *)__dst + 1;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		case 2: {
			__UINT8_TYPE__ __temp;
			__temp = ((__UINT8_TYPE__ const *)__src)[1];
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[1] = __temp;
			return (__UINT8_TYPE__ *)__dst + 2;
		}	break;
		case 3: {
			__UINT8_TYPE__ __temp1;
			__UINT8_TYPE__ __temp2;
			__temp1 = ((__UINT8_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT8_TYPE__ const *)__src)[2];
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[1] = __temp1;
			((__UINT8_TYPE__ *)__dst)[2] = __temp2;
			return (__UINT8_TYPE__ *)__dst + 3;
		}	break;
		case 4: {
			__UINT8_TYPE__ __temp1;
			__UINT8_TYPE__ __temp2;
			__UINT8_TYPE__ __temp3;
			__temp1 = ((__UINT8_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT8_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT8_TYPE__ const *)__src)[3];
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[1] = __temp1;
			((__UINT8_TYPE__ *)__dst)[2] = __temp2;
			((__UINT8_TYPE__ *)__dst)[3] = __temp3;
			return (__UINT8_TYPE__ *)__dst + 4;
		}	break;
#else /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		case 2:
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__BYTE_TYPE__ *)__dst + 2;
		case 3: {
			__UINT8_TYPE__ __temp;
			__temp = ((__UINT8_TYPE__ const *)__src)[2];
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[2] = __temp;
			return (__BYTE_TYPE__ *)__dst + 3;
		}	break;

		case 4:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__BYTE_TYPE__ *)__dst + 4;
		case 5: {
			__UINT8_TYPE__ __temp;
			__temp = ((__UINT8_TYPE__ const *)__src)[4];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[4] = __temp;
			return (__BYTE_TYPE__ *)__dst + 5;
		}	break;

		case 6: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[2] = __temp;
			return (__BYTE_TYPE__ *)__dst + 6;
		}	break;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 8:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__BYTE_TYPE__ *)__dst + 8;
		case 9: {
			__UINT8_TYPE__ __temp;
			__temp = ((__UINT8_TYPE__ const *)__src)[8];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT8_TYPE__ *)__dst)[8] = __temp;
			return (__BYTE_TYPE__ *)__dst + 9;
		}	break;

		case 10: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[4] = __temp;
			return (__BYTE_TYPE__ *)__dst + 10;
		}	break;

		case 12: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = __temp;
			return (__BYTE_TYPE__ *)__dst + 12;
		}	break;

		case 16: {
			__UINT64_TYPE__ __temp;
			__temp = ((__UINT64_TYPE__ const *)__src)[1];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp;
			return (__BYTE_TYPE__ *)__dst + 16;
		}	break;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 8: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[1];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp;
			return (__BYTE_TYPE__ *)__dst + 8;
		}	break;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

		/* More optimizations when the move can be done using
		 * at most 4 read/writes, and at most 3  temporaries. */
#ifndef __OPTIMIZE_SIZE__
		case 7: {
			__UINT16_TYPE__ __temp1;
			__UINT8_TYPE__ __temp2;
			__temp1 = ((__UINT16_TYPE__ const *)__src)[2];
			__temp2 = ((__UINT8_TYPE__ const *)__src)[6];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[2] = __temp1;
			((__UINT8_TYPE__ *)__dst)[6] = __temp2;
			return (__BYTE_TYPE__ *)__dst + 7;
		}	break;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 11: {
			__UINT16_TYPE__ __temp1;
			__UINT8_TYPE__ __temp2;
			__temp1 = ((__UINT16_TYPE__ const *)__src)[4];
			__temp2 = ((__UINT8_TYPE__ const *)__src)[10];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[4] = __temp1;
			((__UINT8_TYPE__ *)__dst)[10] = __temp2;
			return (__BYTE_TYPE__ *)__dst + 11;
		}	break;

		case 13: {
			__UINT32_TYPE__ __temp1;
			__UINT8_TYPE__ __temp2;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp2 = ((__UINT8_TYPE__ const *)__src)[12];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = __temp1;
			((__UINT8_TYPE__ *)__dst)[12] = __temp2;
			return (__BYTE_TYPE__ *)__dst + 13;
		}	break;

		case 14: {
			__UINT32_TYPE__ __temp1;
			__UINT16_TYPE__ __temp2;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp2 = ((__UINT16_TYPE__ const *)__src)[6];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = __temp1;
			((__UINT16_TYPE__ *)__dst)[6] = __temp2;
			return (__BYTE_TYPE__ *)__dst + 14;
		}	break;

		case 15: {
			__UINT32_TYPE__ __temp1;
			__UINT16_TYPE__ __temp2;
			__UINT8_TYPE__ __temp3;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp2 = ((__UINT16_TYPE__ const *)__src)[6];
			__temp3 = ((__UINT8_TYPE__ const *)__src)[14];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[2] = __temp1;
			((__UINT16_TYPE__ *)__dst)[6] = __temp2;
			((__UINT8_TYPE__ *)__dst)[14] = __temp3;
			return (__BYTE_TYPE__ *)__dst + 15;
		}	break;

		case 17: {
			__UINT64_TYPE__ __temp1;
			__UINT8_TYPE__ __temp2;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT8_TYPE__ const *)__src)[16];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT8_TYPE__ *)__dst)[16] = __temp2;
			return (__BYTE_TYPE__ *)__dst + 17;
		}	break;

		case 18: {
			__UINT64_TYPE__ __temp1;
			__UINT16_TYPE__ __temp2;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT16_TYPE__ const *)__src)[8];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT16_TYPE__ *)__dst)[8] = __temp2;
			return (__BYTE_TYPE__ *)__dst + 18;
		}	break;

		case 19: {
			__UINT64_TYPE__ __temp1;
			__UINT16_TYPE__ __temp2;
			__UINT8_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT16_TYPE__ const *)__src)[8];
			__temp3 = ((__UINT8_TYPE__ const *)__src)[18];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT16_TYPE__ *)__dst)[8] = __temp2;
			((__UINT8_TYPE__ *)__dst)[18] = __temp3;
			return (__BYTE_TYPE__ *)__dst + 19;
		}	break;

		case 20: {
			__UINT64_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[4];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[4] = __temp2;
			return (__BYTE_TYPE__ *)__dst + 20;
		}	break;

		case 21: {
			__UINT64_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT8_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[4];
			__temp3 = ((__UINT8_TYPE__ const *)__src)[20];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[4] = __temp2;
			((__UINT8_TYPE__ *)__dst)[20] = __temp3;
			return (__BYTE_TYPE__ *)__dst + 21;
		}	break;

		case 22: {
			__UINT64_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT16_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[4];
			__temp3 = ((__UINT16_TYPE__ const *)__src)[10];
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = __temp1;
			((__UINT32_TYPE__ *)__dst)[4]  = __temp2;
			((__UINT16_TYPE__ *)__dst)[10] = __temp3;
			return (__BYTE_TYPE__ *)__dst + 22;
		}	break;

		case 24: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			return (__BYTE_TYPE__ *)__dst + 24;
		}	break;

		case 25: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__UINT8_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT8_TYPE__ const *)__src)[24];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			((__UINT8_TYPE__ *)__dst)[24] = __temp3;
			return (__BYTE_TYPE__ *)__dst + 25;
		}	break;

		case 26: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__UINT16_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT16_TYPE__ const *)__src)[12];
			((__UINT64_TYPE__ *)__dst)[0]  = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1]  = __temp1;
			((__UINT64_TYPE__ *)__dst)[2]  = __temp2;
			((__UINT16_TYPE__ *)__dst)[12] = __temp3;
			return (__BYTE_TYPE__ *)__dst + 26;
		}	break;

		case 28: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__UINT32_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT32_TYPE__ const *)__src)[6];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			((__UINT32_TYPE__ *)__dst)[6] = __temp3;
			return (__BYTE_TYPE__ *)__dst + 28;
		}	break;

		case 32: {
			__UINT64_TYPE__ __temp1;
			__UINT64_TYPE__ __temp2;
			__UINT64_TYPE__ __temp3;
			__temp1 = ((__UINT64_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT64_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT64_TYPE__ const *)__src)[3];
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT64_TYPE__ *)__dst)[1] = __temp1;
			((__UINT64_TYPE__ *)__dst)[2] = __temp2;
			((__UINT64_TYPE__ *)__dst)[3] = __temp3;
			return (__BYTE_TYPE__ *)__dst + 32;
		}	break;
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 9: {
			__UINT32_TYPE__ __temp1;
			__UINT8_TYPE__ __temp2;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT8_TYPE__ const *)__src)[8];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT8_TYPE__ *)__dst)[8]  = __temp2;
			return (__BYTE_TYPE__ *)__dst + 9;
		}	break;

		case 10: {
			__UINT32_TYPE__ __temp1;
			__UINT16_TYPE__ __temp2;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT16_TYPE__ const *)__src)[4];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT16_TYPE__ *)__dst)[4] = __temp2;
			return (__BYTE_TYPE__ *)__dst + 10;
		}	break;

		case 11: {
			__UINT32_TYPE__ __temp1;
			__UINT16_TYPE__ __temp2;
			__UINT8_TYPE__ __temp3;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT16_TYPE__ const *)__src)[4];
			__temp3 = ((__UINT8_TYPE__ const *)__src)[10];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT16_TYPE__ *)__dst)[4] = __temp2;
			((__UINT8_TYPE__ *)__dst)[10] = __temp3;
			return (__BYTE_TYPE__ *)__dst + 11;
		}	break;

		case 12: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			return (__BYTE_TYPE__ *)__dst + 12;
		}	break;

		case 13: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT8_TYPE__ __temp3;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT8_TYPE__ const *)__src)[12];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			((__UINT8_TYPE__ *)__dst)[12] = __temp3;
			return (__BYTE_TYPE__ *)__dst + 13;
		}	break;

		case 14: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT16_TYPE__ __temp3;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT16_TYPE__ const *)__src)[6];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			((__UINT16_TYPE__ *)__dst)[6] = __temp3;
			return (__BYTE_TYPE__ *)__dst + 14;
		}	break;

		case 16: {
			__UINT32_TYPE__ __temp1;
			__UINT32_TYPE__ __temp2;
			__UINT32_TYPE__ __temp3;
			__temp1 = ((__UINT32_TYPE__ const *)__src)[1];
			__temp2 = ((__UINT32_TYPE__ const *)__src)[2];
			__temp3 = ((__UINT32_TYPE__ const *)__src)[3];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[1] = __temp1;
			((__UINT32_TYPE__ *)__dst)[2] = __temp2;
			((__UINT32_TYPE__ *)__dst)[3] = __temp3;
			return (__BYTE_TYPE__ *)__dst + 16;
		}	break;
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */

		default:
			break;
		}
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__CRT_HAVE_mempmoveq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_bytes & 7) {
		case 0:
			return __libc_core_mempmoveq(__dst, __src, __n_bytes >> 3);
		case 1: {
			__UINT8_TYPE__ __temp;
			__temp = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
			__dst = __libc_core_mempmoveq(__dst, __src, __n_bytes >> 3);
			((__UINT8_TYPE__ *)__dst)[0] = __temp;
			return (__BYTE_TYPE__ *)__dst + 1;
		}	break;

		case 2: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1) - 1];
			__dst = __libc_core_mempmoveq(__dst, __src, __n_bytes >> 3);
			((__UINT16_TYPE__ *)__dst)[0] = __temp;
			return (__BYTE_TYPE__ *)__dst + 2;
		}	break;

		case 4: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[(__n_bytes >> 2) - 1];
			__dst = __libc_core_mempmoveq(__dst, __src, __n_bytes >> 3);
			((__UINT32_TYPE__ *)__dst)[0] = __temp;
			return (__BYTE_TYPE__ *)__dst + 4;
		}
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 7))
			return __libc_core_mempmoveq(__dst, __src, __n_bytes >> 3);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmoveq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_mempmovel)
#ifndef __OPTIMIZE_SIZE__
		switch __untraced(__n_bytes & 3) {
		case 0:
			return __libc_core_mempmovel(__dst, __src, __n_bytes >> 2);
		case 1: {
			__UINT8_TYPE__ __temp;
			__temp = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
			__dst = __libc_core_mempmovel(__dst, __src, __n_bytes >> 2);
			((__UINT8_TYPE__ *)__dst)[0] = __temp;
			return (__BYTE_TYPE__ *)__dst + 1;
		}	break;

		case 2: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1) - 1];
			__dst = __libc_core_mempmovel(__dst, __src, __n_bytes >> 2);
			((__UINT16_TYPE__ *)__dst)[0] = __temp;
			return (__BYTE_TYPE__ *)__dst + 2;
		}
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 3))
			return __libc_core_mempmovel(__dst, __src, __n_bytes >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmovel */
#if defined(__CRT_HAVE_mempmovew)
#ifndef __OPTIMIZE_SIZE__
		if __untraced(!(__n_bytes & 1))
			return __libc_core_mempmovew(__dst, __src, __n_bytes >> 1);
		{
			__UINT8_TYPE__ __temp = ((__UINT8_TYPE__ const *)__src)[__n_bytes - 1];
			__dst = __libc_core_mempmovew(__dst, __src, __n_bytes >> 1);
			((__UINT8_TYPE__ *)__dst)[0] = __temp;
		}
		return (__BYTE_TYPE__ *)__dst + 1;
#else /* !__OPTIMIZE_SIZE__ */
		if __untraced(!(__n_bytes & 1))
			return __libc_core_mempmovew(__dst, __src, __n_bytes >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmovew */
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	}
	return __libc_core_mempmove(__dst, __src, __n_bytes);
}
#endif /* !__fast_mempmove_defined */

#ifndef __fast_mempatw_defined
#define __fast_mempatw_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempatw))(void *__restrict __dst,
                                         __UINT16_TYPE__ __pattern,
                                         __SIZE_TYPE__ __n_bytes) {
	if __untraced(__builtin_constant_p(__pattern)) {
		/* Optimization: Check for same-byte patterns, which allow this to be turned into a memset() call */
		if __untraced((__pattern & __UINT8_C(0xff)) == ((__pattern >> 8) & __UINT8_C(0xff)))
			return __LIBC_FAST_NAME(memset)(__dst, __pattern & __UINT8_C(0xff), __n_bytes);
	}
	if __untraced(__builtin_constant_p(__n_bytes)) {
		if __untraced(__n_bytes == 0)
			return __dst;
	}
	return __libc_core_mempatw(__dst, __pattern, __n_bytes);
}
#endif /* !__fast_mempatw_defined */

#ifndef __fast_mempatl_defined
#define __fast_mempatl_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempatl))(void *__restrict __dst,
                                         __UINT32_TYPE__ __pattern,
                                         __SIZE_TYPE__ __n_bytes) {
	if __untraced(__builtin_constant_p(__pattern)) {
		/* Optimization: Check for same-byte patterns, which allow this to be turned into a memset() call */
		if __untraced((__pattern & __UINT8_C(0xff)) == ((__pattern >> 8) & __UINT8_C(0xff)) &&
		    (__pattern & __UINT8_C(0xff)) == ((__pattern >> 16) & __UINT8_C(0xff)) &&
		    (__pattern & __UINT8_C(0xff)) == ((__pattern >> 24) & __UINT8_C(0xff)))
			return __LIBC_FAST_NAME(memset)(__dst, __pattern & __UINT8_C(0xff), __n_bytes);
	}
	if __untraced(__builtin_constant_p(__n_bytes)) {
		if __untraced(__n_bytes == 0)
			return __dst;
	}
	return __libc_core_mempatl(__dst, __pattern, __n_bytes);
}
#endif /* !__fast_mempatw_defined */

#ifdef __UINT64_TYPE__
#ifndef __fast_mempatq_defined
#define __fast_mempatq_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBC_FAST_NAME(mempatq))(void *__restrict __dst,
                                         __UINT64_TYPE__ __pattern,
                                         __SIZE_TYPE__ __n_bytes) {
	if __untraced(__builtin_constant_p(__pattern)) {
		/* Optimization: Check for same-byte patterns, which allow this to be turned into a memset() call */
		if __untraced((__pattern & __UINT8_C(0xff)) == ((__pattern >> 8) & __UINT8_C(0xff)) &&
		    (__pattern & __UINT8_C(0xff)) == ((__pattern >> 16) & __UINT8_C(0xff)) &&
		    (__pattern & __UINT8_C(0xff)) == ((__pattern >> 24) & __UINT8_C(0xff)) &&
		    (__pattern & __UINT8_C(0xff)) == ((__pattern >> 32) & __UINT8_C(0xff)) &&
		    (__pattern & __UINT8_C(0xff)) == ((__pattern >> 40) & __UINT8_C(0xff)) &&
		    (__pattern & __UINT8_C(0xff)) == ((__pattern >> 48) & __UINT8_C(0xff)) &&
		    (__pattern & __UINT8_C(0xff)) == ((__pattern >> 56) & __UINT8_C(0xff)))
			return __LIBC_FAST_NAME(memset)(__dst, __pattern & __UINT8_C(0xff), __n_bytes);
	}
	if __untraced(__builtin_constant_p(__n_bytes)) {
		if __untraced(__n_bytes == 0)
			return __dst;
	}
	return __libc_core_mempatq(__dst, __pattern, __n_bytes);
}
#endif /* !__fast_mempatw_defined */
#endif /* __UINT64_TYPE__ */




#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#ifdef __UINT64_TYPE__
#define __DEFINE_FAST_MEMCPYC_FUNCTION(memcpyc, memcpy, memcpyw, memcpyl, memcpyq, __restrict, noop_return) \
	__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *                          \
	__NOTHROW_NCX(__LIBC_FAST_NAME(memcpyc))(void *__restrict __dst,                                        \
	                                         void const *__restrict __src,                                  \
	                                         __SIZE_TYPE__ __elem_count,                                    \
	                                         __SIZE_TYPE__ __elem_size) {                                   \
		if __untraced(__builtin_constant_p(__elem_size)) {                                                  \
			switch __untraced(__elem_size) {                                                                \
			case 1: return (memcpy)(__dst, __src, __elem_count);                                            \
			case 2: return (memcpyw)(__dst, __src, __elem_count);                                           \
			case 4: return (memcpyl)(__dst, __src, __elem_count);                                           \
			case 8: return (memcpyq)(__dst, __src, __elem_count);                                           \
			default: break;                                                                                 \
			}                                                                                               \
			if __untraced(__elem_size >= 8 && (__elem_size & 7) == 0)                                       \
				return (memcpyq)(__dst, __src, __elem_count * (__elem_size / 8));                           \
			if __untraced(__elem_size >= 4 && (__elem_size & 3) == 0)                                       \
				return (memcpyl)(__dst, __src, __elem_count * (__elem_size / 4));                           \
			if __untraced(__elem_size >= 2 && (__elem_size & 1) == 0)                                       \
				return (memcpyw)(__dst, __src, __elem_count * (__elem_size / 2));                           \
		}                                                                                                   \
		if __untraced(__builtin_constant_p(__elem_count)) {                                                 \
			switch __untraced(__elem_count) {                                                               \
			case 1: return (memcpy)(__dst, __src, __elem_size);                                             \
			case 2: return (memcpyw)(__dst, __src, __elem_size);                                            \
			case 4: return (memcpyl)(__dst, __src, __elem_size);                                            \
			case 8: return (memcpyq)(__dst, __src, __elem_size);                                            \
			default: break;                                                                                 \
			}                                                                                               \
			if __untraced(__elem_count >= 8 && (__elem_count & 7) == 0)                                     \
				return (memcpyq)(__dst, __src, __elem_size * (__elem_count / 8));                           \
			if __untraced(__elem_count >= 4 && (__elem_count & 3) == 0)                                     \
				return (memcpyl)(__dst, __src, __elem_size * (__elem_count / 4));                           \
			if __untraced(__elem_count >= 2 && (__elem_count & 1) == 0)                                     \
				return (memcpyw)(__dst, __src, __elem_size * (__elem_count / 2));                           \
		}                                                                                                   \
		return (memcpy)(__dst, __src, __elem_count * __elem_size);                                          \
	}
#else /* __UINT64_TYPE__ */
#define __DEFINE_FAST_MEMCPYC_FUNCTION(memcpyc, memcpy, memcpyw, memcpyl, memcpyq, __restrict, noop_return) \
	__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *                          \
	__NOTHROW_NCX(__LIBC_FAST_NAME(memcpyc))(void *__restrict __dst,                                        \
	                                         void const *__restrict __src,                                  \
	                                         __SIZE_TYPE__ __elem_count,                                    \
	                                         __SIZE_TYPE__ __elem_size) {                                   \
		if __untraced(__builtin_constant_p(__elem_size)) {                                                  \
			switch __untraced(__elem_size) {                                                                \
			case 1: return (memcpy)(__dst, __src, __elem_count);                                            \
			case 2: return (memcpyw)(__dst, __src, __elem_count);                                           \
			case 4: return (memcpyl)(__dst, __src, __elem_count);                                           \
			default: break;                                                                                 \
			}                                                                                               \
			if __untraced(__elem_size >= 4 && (__elem_size & 3) == 0)                                       \
				return (memcpyl)(__dst, __src, __elem_count * (__elem_size / 4));                           \
			if __untraced(__elem_size >= 2 && (__elem_size & 1) == 0)                                       \
				return (memcpyw)(__dst, __src, __elem_count * (__elem_size / 2));                           \
		}                                                                                                   \
		if __untraced(__builtin_constant_p(__elem_count)) {                                                 \
			switch __untraced(__elem_count) {                                                               \
			case 1: return (memcpy)(__dst, __src, __elem_size);                                             \
			case 2: return (memcpyw)(__dst, __src, __elem_size);                                            \
			case 4: return (memcpyl)(__dst, __src, __elem_size);                                            \
			default: break;                                                                                 \
			}                                                                                               \
			if __untraced(__elem_count >= 4 && (__elem_count & 3) == 0)                                     \
				return (memcpyl)(__dst, __src, __elem_size * (__elem_count / 4));                           \
			if __untraced(__elem_count >= 2 && (__elem_count & 1) == 0)                                     \
				return (memcpyw)(__dst, __src, __elem_size * (__elem_count / 2));                           \
		}                                                                                                   \
		return (memcpy)(__dst, __src, __elem_count * __elem_size);                                          \
	}
#endif /* !__UINT64_TYPE__ */
#else /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#ifdef __OPTIMIZE_SIZE__
#define __DEFINE_FAST_MEMCPYC_FUNCTION(memcpyc, memcpy, memcpyw, memcpyl, memcpyq, __restrict, noop_return) \
	__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *                          \
	__NOTHROW_NCX(__LIBC_FAST_NAME(memcpyc))(void *__restrict __dst,                                        \
	                                         void const *__restrict __src,                                  \
	                                         __SIZE_TYPE__ __elem_count,                                    \
	                                         __SIZE_TYPE__ __elem_size) {                                   \
		if __untraced(__builtin_constant_p(__elem_size)) {                                                  \
			if __untraced(__elem_size == 1)                                                                 \
				return (memcpy)(__dst, __src, __elem_count);                                                \
			if __untraced(__builtin_constant_p(__elem_count))                                               \
				return (memcpy)(__dst, __src, __elem_count * __elem_size);                                  \
		} else if __untraced(__builtin_constant_p(__elem_count)) {                                          \
			if __untraced(__elem_count == 1)                                                                \
				return (memcpy)(__dst, __src, __elem_size);                                                 \
		}                                                                                                   \
		if __untraced(__builtin_constant_p(__dst == __src) && (__dst == __src))                             \
			return noop_return;                                                                             \
		return (__libc_core_##memcpyc)(__dst, __src, __elem_count, __elem_size);                            \
	}
#else /* __OPTIMIZE_SIZE__ */
#define __DEFINE_FAST_MEMCPYC_FUNCTION(memcpyc, memcpy, memcpyw, memcpyl, memcpyq, __restrict, noop_return) \
	__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *                          \
	__NOTHROW_NCX(__LIBC_FAST_NAME(memcpyc))(void *__restrict __dst,                                        \
	                                         void const *__restrict __src,                                  \
	                                         __SIZE_TYPE__ __elem_count,                                    \
	                                         __SIZE_TYPE__ __elem_size) {                                   \
		return (memcpy)(__dst, __src, __elem_count * __elem_size);                                          \
	}
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */

#ifndef __fast_memcpyc_defined
#define __fast_memcpyc_defined
__DEFINE_FAST_MEMCPYC_FUNCTION(memcpyc,
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyw),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyl),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyq),
                               __restrict, __dst)
#endif /* !__fast_memcpyc_defined */

#ifndef __fast_mempcpyc_defined
#define __fast_mempcpyc_defined
__DEFINE_FAST_MEMCPYC_FUNCTION(mempcpyc,
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpy),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyw),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyl),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyq),
                               __restrict, (__UINT8_TYPE__ *)__dst + (__elem_count * __elem_size))
#endif /* !__fast_mempcpyc_defined */

#ifndef __fast_memmovec_defined
#define __fast_memmovec_defined
__DEFINE_FAST_MEMCPYC_FUNCTION(memmovec,
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmove),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovew),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovel),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveq),
                               /*__restrict*/, __dst)
#endif /* !__fast_memmovec_defined */

#ifndef __fast_mempmovec_defined
#define __fast_mempmovec_defined
__DEFINE_FAST_MEMCPYC_FUNCTION(mempmovec,
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmove),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovew),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovel),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveq),
                               /*__restrict*/, (__UINT8_TYPE__ *)__dst + (__elem_count * __elem_size))
#endif /* !__fast_mempmovec_defined */

#ifndef __fast_memmoveupc_defined
#define __fast_memmoveupc_defined
__DEFINE_FAST_MEMCPYC_FUNCTION(memmoveupc,
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveup),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupw),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupl),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupq),
                               /*__restrict*/, __dst)
#endif /* !__fast_memmoveupc_defined */

#ifndef __fast_mempmoveupc_defined
#define __fast_mempmoveupc_defined
__DEFINE_FAST_MEMCPYC_FUNCTION(mempmoveupc,
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveup),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupw),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupl),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupq),
                               /*__restrict*/, (__UINT8_TYPE__ *)__dst + (__elem_count * __elem_size))
#endif /* !__fast_mempmoveupc_defined */

#ifndef __fast_memmovedownc_defined
#define __fast_memmovedownc_defined
__DEFINE_FAST_MEMCPYC_FUNCTION(memmovedownc,
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedown),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownw),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownl),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownq),
                               /*__restrict*/, __dst)
#endif /* !__fast_memmovedownc_defined */

#ifndef __fast_mempmovedownc_defined
#define __fast_mempmovedownc_defined
__DEFINE_FAST_MEMCPYC_FUNCTION(mempmovedownc,
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedown),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownw),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownl),
                               __NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownq),
                               /*__restrict*/, (__UINT8_TYPE__ *)__dst + (__elem_count * __elem_size))
#endif /* !__fast_mempmovedownc_defined */

#undef __DEFINE_FAST_MEMCPYC_FUNCTION

__NAMESPACE_FAST_END
__SYSDECL_END
#endif /* !__NO_ATTR_FORCEINLINE && !__NO_builtin_constant_p */

#endif /* !_OPTIMIZED_STRING_H */
