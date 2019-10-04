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
#ifndef _OPTIMIZED_STRING_H
#define _OPTIMIZED_STRING_H 1

#include <__stdinc.h>
#include <hybrid/host.h>

/* Platform-independent, optimized string.h functions. */
#if !defined(__NO_ATTR_FORCEINLINE) && \
    !defined(__NO_builtin_constant_p) && \
     defined(__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS)
#include <libc/slow/string.h>

__SYSDECL_BEGIN
__NAMESPACE_FAST_BEGIN

#ifdef __UINT64_TYPE__
#ifndef __fast_memcpyq_defined
#define __fast_memcpyq_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memcpyq))(void *__restrict __dst,
                                                    void const *__restrict __src,
                                                    __SIZE_TYPE__ __n_qwords) {
	if (__builtin_constant_p(__n_qwords)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch (__n_qwords) {
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
	return __libc_slow_memcpyq(__dst, __src, __n_qwords);
}
#endif /* !__fast_memcpyq_defined */
#endif /* __UINT64_TYPE__ */

#ifndef __fast_memcpyl_defined
#define __fast_memcpyl_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memcpyl))(void *__restrict __dst,
                                                    void const *__restrict __src,
                                                    __SIZE_TYPE__ __n_dwords) {
	if (__builtin_constant_p(__n_dwords)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch (__n_dwords) {
		case 0:
			return (__UINT32_TYPE__ *)__dst;
		case 1:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 2:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
		case 3:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
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
		default: break;
		}
#if defined(__CRT_HAVE_memcpyq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		if (!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_slow_memcpyq(__dst, __src, __n_dwords >> 1);
		__dst = __libc_slow_memcpyq(__dst, __src, __n_dwords >> 1);
		((__UINT32_TYPE__ *)__dst)[__n_dwords-1] = ((__UINT32_TYPE__ const *)__src)[__n_dwords-1];
		return (__UINT32_TYPE__ *)__dst;
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_dwords & 1))
			return __libc_slow_memcpyq(__dst, __src, __n_dwords >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memcpyq && __SIZEOF_BUSINT__ >= 8 */
	}
	return __libc_slow_memcpyl(__dst, __src, __n_dwords);
}
#endif /* !__fast_memcpyl_defined */

#ifndef __fast_memcpyw_defined
#define __fast_memcpyw_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memcpyw))(void *__restrict __dst,
                                                    void const *__restrict __src,
                                                    __SIZE_TYPE__ __n_words) {
	if (__builtin_constant_p(__n_words)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch (__n_words) {
		case 0:
			return (__UINT16_TYPE__ *)__dst;
		case 1:
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
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
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
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
		default: break;
		}
#if defined(__CRT_HAVE_memcpyq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch (__n_words & 3) {
		case 0:
			return (__UINT16_TYPE__ *)__libc_slow_memcpyq(__dst, __src, __n_words >> 2);
		case 1:
			__dst = __libc_slow_memcpyq(__dst, __src, __n_words >> 2);
			((__UINT16_TYPE__ *)__dst)[__n_words-1] = ((__UINT16_TYPE__ const *)__src)[__n_words-1];
			return (__UINT16_TYPE__ *)__dst;
		case 2:
			__dst = __libc_slow_memcpyq(__dst, __src, __n_words >> 2);
			((__UINT32_TYPE__ *)__dst)[(__n_words >> 1)-1] = ((__UINT32_TYPE__ const *)__src)[(__n_words >> 1)-1];
			return (__UINT16_TYPE__ *)__dst;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_words & 7))
			return (__UINT16_TYPE__ *)__libc_slow_memcpyq(__dst, __src, __n_words >> 3);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memcpyq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_memcpyl)
#ifndef __OPTIMIZE_SIZE__
		if (!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_slow_memcpyl(__dst, __src, __n_words >> 1);
		__dst = __libc_slow_memcpyl(__dst, __src, __n_words >> 1);
		((__UINT16_TYPE__ *)__dst)[__n_words-1] = ((__UINT16_TYPE__ const *)__src)[__n_words-1];
		return (__UINT16_TYPE__ *)__dst;
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_words & 1))
			return __libc_slow_memcpyw(__dst, __src, __n_words >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memcpyl */
	}
	return __libc_slow_memcpyw(__dst, __src, __n_words);
}
#endif /* !__fast_memcpyw_defined */


#ifndef __fast_memcpy_defined
#define __fast_memcpy_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memcpy))(void *__restrict __dst,
                                                   void const *__restrict __src,
                                                   __SIZE_TYPE__ __n_bytes) {
	if (__builtin_constant_p(__n_bytes)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
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
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
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
		default: break;
		}
#if defined(__CRT_HAVE_memcpyq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch (__n_bytes & 7) {
		case 0:
			return __libc_slow_memcpyq(__dst, __src, __n_bytes >> 3);
		case 1:
			__dst = __libc_slow_memcpyq(__dst, __src, __n_bytes >> 3);
			((__UINT8_TYPE__ *)__dst)[__n_bytes-1] = ((__UINT8_TYPE__ const *)__src)[__n_bytes-1];
			return __dst;
		case 2:
			__dst = __libc_slow_memcpyq(__dst, __src, __n_bytes >> 3);
			((__UINT16_TYPE__ *)__dst)[(__n_bytes >> 1)-1] = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1)-1];
			return __dst;
		case 4:
			__dst = __libc_slow_memcpyq(__dst, __src, __n_bytes >> 3);
			((__UINT32_TYPE__ *)__dst)[(__n_bytes >> 2)-1] = ((__UINT32_TYPE__ const *)__src)[(__n_bytes >> 2)-1];
			return __dst;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_bytes & 7))
			return __libc_slow_memcpyq(__dst, __src, __n_bytes >> 3);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memcpyq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_memcpyl)
#ifndef __OPTIMIZE_SIZE__
		switch (__n_bytes & 3) {
		case 0:
			return __libc_slow_memcpyl(__dst, __src, __n_bytes >> 2);
		case 1:
			__dst = __libc_slow_memcpyl(__dst, __src, __n_bytes >> 2);
			((__UINT8_TYPE__ *)__dst)[__n_bytes-1] = ((__UINT8_TYPE__ const *)__src)[__n_bytes-1];
			return __dst;
		case 2:
			__dst = __libc_slow_memcpyl(__dst, __src, __n_bytes >> 2);
			((__UINT16_TYPE__ *)__dst)[(__n_bytes >> 1)-1] = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1)-1];
			return __dst;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_bytes & 3))
			return __libc_slow_memcpyl(__dst, __src, __n_bytes >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memcpyl */
#if defined(__CRT_HAVE_memcpyw)
#ifndef __OPTIMIZE_SIZE__
		if (!(__n_bytes & 1))
			return __libc_slow_memcpyw(__dst, __src, __n_bytes >> 1);
		__dst = __libc_slow_memcpyw(__dst, __src, __n_bytes >> 1);
		((__UINT8_TYPE__ *)__dst)[__n_bytes-1] = ((__UINT8_TYPE__ const *)__src)[__n_bytes-1];
		return __dst;
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_bytes & 1))
			return __libc_slow_memcpyw(__dst, __src, __n_bytes >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memcpyw */
	}
	return __libc_slow_memcpy(__dst, __src, __n_bytes);
}
#endif /* !__fast_memcpy_defined */



#ifdef __UINT64_TYPE__
#ifndef __fast_mempcpyq_defined
#define __fast_mempcpyq_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(mempcpyq))(void *__restrict __dst,
                                                     void const *__restrict __src,
                                                     __SIZE_TYPE__ __n_qwords) {
	if (__builtin_constant_p(__n_qwords)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch (__n_qwords) {
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
	return __libc_slow_mempcpyq(__dst, __src, __n_qwords);
}
#endif /* !__fast_mempcpyq_defined */
#endif /* __UINT64_TYPE__ */


#ifndef __fast_mempcpyl_defined
#define __fast_mempcpyl_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(mempcpyl))(void *__restrict __dst,
                                                     void const *__restrict __src,
                                                     __SIZE_TYPE__ __n_dwords) {
	if (__builtin_constant_p(__n_dwords)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch (__n_dwords) {
		case 0:
			return (__UINT32_TYPE__ *)__dst;
		case 1:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 4);
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 2:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 8);
		case 3:
			((__UINT64_TYPE__ *)__dst)[0] = ((__UINT64_TYPE__ const *)__src)[0];
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
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
		default: break;
		}
#if defined(__CRT_HAVE_mempcpyq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		if (!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_slow_mempcpyq(__dst, __src, __n_dwords >> 1);
		__dst = __libc_slow_mempcpyq(__dst, __src, __n_dwords >> 1);
		((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[__n_dwords-1];
		return (__UINT32_TYPE__ *)__dst + 1;
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_dwords & 1))
			return __libc_slow_mempcpyq(__dst, __src, __n_dwords >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempcpyq && __SIZEOF_BUSINT__ >= 8 */
	}
	return __libc_slow_mempcpyl(__dst, __src, __n_dwords);
}
#endif /* !__fast_mempcpyl_defined */


#ifndef __fast_mempcpyw_defined
#define __fast_mempcpyw_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(mempcpyw))(void *__restrict __dst,
                                                     void const *__restrict __src,
                                                     __SIZE_TYPE__ __n_words) {
	if (__builtin_constant_p(__n_words)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
		switch (__n_words) {
		case 0:
			return (__UINT16_TYPE__ *)__dst;
		case 1:
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__UINT8_TYPE__ *)__dst + 2);
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
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
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
		default: break;
		}
#if defined(__CRT_HAVE_mempcpyq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch (__n_words & 3) {
		case 0:
			return (__UINT16_TYPE__ *)__libc_slow_mempcpyq(__dst, __src, __n_words >> 2);
		case 1:
			__dst = __libc_slow_mempcpyq(__dst, __src, __n_words >> 2);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[__n_words-1];
			return (__UINT16_TYPE__ *)__dst + 1;
		case 2:
			__dst = __libc_slow_mempcpyq(__dst, __src, __n_words >> 2);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[(__n_words >> 1)-1];
			return (__UINT16_TYPE__ *)__dst + 2;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_words & 3))
			return (__UINT16_TYPE__ *)__libc_slow_mempcpyq(__dst, __src, __n_words >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempcpyq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_mempcpyl)
#ifndef __OPTIMIZE_SIZE__
		if (!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_slow_mempcpyl(__dst, __src, __n_words >> 1);
		__dst = __libc_slow_mempcpyl(__dst, __src, __n_words >> 1);
		((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[__n_words-1];
		return (__UINT16_TYPE__ *)__dst + 1;
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_slow_mempcpyl(__dst, __src, __n_words >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempcpyl */
	}
	return __libc_slow_mempcpyw(__dst, __src, __n_words);
}
#endif /* !__fast_mempcpyw_defined */


#ifndef __fast_mempcpy_defined
#define __fast_mempcpy_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(mempcpy))(void *__restrict __dst,
                                                    void const *__restrict __src,
                                                    __SIZE_TYPE__ __n_bytes) {
	if (__builtin_constant_p(__n_bytes)) {
		/* Optimizations for small data blocks (those possible with <= 2 assignments). */
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
			((__UINT32_TYPE__ *)__dst)[3] = ((__UINT32_TYPE__ const *)__src)[3];
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
		default: break;
		}
#if defined(__CRT_HAVE_mempcpyq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch (__n_bytes & 7) {
		case 0:
			return __libc_slow_mempcpyq(__dst, __src, __n_bytes >> 3);
		case 1:
			__dst = __libc_slow_mempcpyq(__dst, __src, __n_bytes >> 3);
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[__n_bytes-1];
			return (__UINT8_TYPE__ *)__dst + 1;
		case 2:
			__dst = __libc_slow_mempcpyq(__dst, __src, __n_bytes >> 3);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1)-1];
			return (__UINT8_TYPE__ *)__dst + 2;
		case 4:
			__dst = __libc_slow_mempcpyq(__dst, __src, __n_bytes >> 3);
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[(__n_bytes >> 2)-1];
			return (__UINT8_TYPE__ *)__dst + 4;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_bytes & 7))
			return __libc_slow_mempcpyq(__dst, __src, __n_bytes >> 3);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempcpyq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_mempcpyl)
#ifndef __OPTIMIZE_SIZE__
		switch (__n_bytes & 3) {
		case 0:
			return __libc_slow_mempcpyl(__dst, __src, __n_bytes >> 2);
		case 1:
			__dst = __libc_slow_mempcpyl(__dst, __src, __n_bytes >> 2);
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[__n_bytes-1];
			return (__UINT8_TYPE__ *)__dst + 1;
		case 2:
			__dst = __libc_slow_mempcpyl(__dst, __src, __n_bytes >> 2);
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1)-1];
			return (__UINT8_TYPE__ *)__dst + 2;
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_bytes & 3))
			return __libc_slow_mempcpyl(__dst, __src, __n_bytes >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempcpyl */
#if defined(__CRT_HAVE_mempcpyw)
#ifndef __OPTIMIZE_SIZE__
		if (!(__n_bytes & 1))
			return __libc_slow_mempcpyw(__dst, __src, __n_bytes >> 1);
		__dst = __libc_slow_mempcpyw(__dst, __src, __n_bytes >> 1);
		((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[__n_bytes-1];
		return (__UINT8_TYPE__ *)__dst + 1;
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_bytes & 1))
			return __libc_slow_mempcpyw(__dst, __src, __n_bytes >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempcpyw */
	}
	return __libc_slow_mempcpy(__dst, __src, __n_bytes);
}
#endif /* !__fast_mempcpy_defined */


#ifdef __CRT_HAVE_bzero
#ifndef ____localdep_bzero_defined
#define ____localdep_bzero_defined 1
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,(__dst, __num_bytes))
#endif /* !____localdep_bzero_defined */
#endif /* __CRT_HAVE_bzero */


#ifdef __UINT64_TYPE__
#ifndef __fast_memsetq_defined
#define __fast_memsetq_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memsetq))(void *__restrict __dst,
                                                    __UINT64_TYPE__ __qword,
                                                    __SIZE_TYPE__ __n_qwords) {
	if (__builtin_constant_p(__qword)) {
		if (__builtin_constant_p(__n_qwords)) {
			/* Optimizations for small data blocks (those possible with <= 2 assignments). */
			switch (__n_qwords) {
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
	if (__builtin_constant_p(__qword)) {
#ifdef __CRT_HAVE_memsetl
		if ((__qword & __UINT32_C(0xffffffff)) == ((__qword >> 32) & __UINT32_C(0xffffffff)))
			return (__UINT64_TYPE__ *)__libc_slow_memsetl(__dst, __qword & __UINT32_C(0xffffffff), __n_qwords * 2);
#endif /* __CRT_HAVE_memsetl */
#ifdef __CRT_HAVE_memsetw
		if ((__qword & __UINT16_C(0xffff)) == ((__qword >> 16) & __UINT16_C(0xffff)) &&
		    (__qword & __UINT16_C(0xffff)) == ((__qword >> 32) & __UINT16_C(0xffff)) &&
		    (__qword & __UINT16_C(0xffff)) == ((__qword >> 48) & __UINT16_C(0xffff)))
			return (__UINT64_TYPE__ *)__libc_slow_memsetw(__dst, __qword & __UINT16_C(0xffff), __n_qwords * 4);
#endif /* __CRT_HAVE_memsetw */
#ifdef __CRT_HAVE_memset
		if ((__qword & __UINT8_C(0xff)) == ((__qword >> 8) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 16) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 24) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 32) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 40) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 48) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 56) & __UINT8_C(0xff)))
			return (__UINT64_TYPE__ *)__libc_slow_memset(__dst, __qword & __UINT8_C(0xff), __n_qwords * 8);
#endif /* __CRT_HAVE_memset */
	}
#elif defined(__CRT_HAVE_memsetl) && __SIZEOF_BUSINT__ < 8
	if (__builtin_constant_p(__qword) &&
	   (__qword & __UINT32_C(0xffffffff)) == ((__qword >> 32) & __UINT32_C(0xffffffff)))
		return (__UINT64_TYPE__ *)__libc_slow_memsetl(__dst, __qword & __UINT32_C(0xffffffff), __n_qwords * 2);
#endif /* !__CRT_HAVE_memsetq && ... */
#ifdef __CRT_HAVE_bzero
	if (__builtin_constant_p(__qword) && __qword == 0) {
		__localdep_bzero(__dst, __n_qwords * 8);
		return (__UINT64_TYPE__ *)__dst;
	}
#endif /* __CRT_HAVE_bzero */
	return __libc_slow_memsetq(__dst, __qword, __n_qwords);
}
#endif /* !__fast_memsetq_defined */
#endif /* __UINT64_TYPE__ */


#ifndef __fast_memsetl_defined
#define __fast_memsetl_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memsetl))(void *__restrict __dst,
                                                    __UINT32_TYPE__ __dword,
                                                    __SIZE_TYPE__ __n_dwords) {
	if (__builtin_constant_p(__dword)) {
		if (__builtin_constant_p(__n_dwords)) {
			/* Optimizations for small data blocks (those possible with <= 2 assignments). */
			switch (__n_dwords) {
			case 0:
				return (__UINT32_TYPE__ *)__dst;
			case 1:
				((__UINT32_TYPE__ *)__dst)[0] = __dword;
				return (__UINT32_TYPE__ *)__dst;
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
			default: break;
			}
		}
#ifndef __OPTIMIZE_SIZE__
#if defined(__CRT_HAVE_mempsetq) && __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		void *__temp;
		__temp = __libc_slow_mempsetq(__dst,
		                             (__UINT64_TYPE__)((__UINT64_TYPE__)__dword * __UINT64_C(0x0000000100000001)),
		                              __n_dwords >> 1);
		if (__n_dwords & 1)
			((__UINT32_TYPE__ *)__temp)[0] = __dword;
		return (__UINT32_TYPE__ *)__dst;
#endif /* __CRT_HAVE_mempsetq && __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
	}
#if !defined(__CRT_HAVE_memsetl) && \
    (defined(__CRT_HAVE_memsetw) || defined(__CRT_HAVE_memset))
	if (__builtin_constant_p(__dword)) {
#ifdef __CRT_HAVE_memsetw
		if ((__dword & __UINT16_C(0xffff)) == ((__dword >> 16) & __UINT16_C(0xffff)))
			return (__UINT32_TYPE__ *)__libc_slow_memsetw(__dst, __dword & __UINT16_C(0xffff), __n_dwords * 2);
#endif /* __CRT_HAVE_memsetw */
#ifdef __CRT_HAVE_memset
		if ((__dword & __UINT8_C(0xff)) == ((__dword >> 8) & __UINT8_C(0xff)) &&
		    (__dword & __UINT8_C(0xff)) == ((__dword >> 16) & __UINT8_C(0xff)) &&
		    (__dword & __UINT8_C(0xff)) == ((__dword >> 24) & __UINT8_C(0xff)))
			return (__UINT32_TYPE__ *)__libc_slow_memset(__dst, __dword & __UINT8_C(0xff), __n_dwords * 4);
#endif /* __CRT_HAVE_memset */
	}
#endif /* !__CRT_HAVE_memsetl && (__CRT_HAVE_memsetw || __CRT_HAVE_memset) */
#ifdef __CRT_HAVE_bzero
	if (__builtin_constant_p(__dword) && __dword == 0) {
		__localdep_bzero(__dst, __n_dwords * 4);
		return (__UINT32_TYPE__ *)__dst;
	}
#endif /* __CRT_HAVE_bzero */
	return __libc_slow_memsetl(__dst, __dword, __n_dwords);
}
#endif /* !__fast_memsetl_defined */


#ifndef __fast_memsetw_defined
#define __fast_memsetw_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memsetw))(void *__restrict __dst,
                                                    __UINT16_TYPE__ __word,
                                                    __SIZE_TYPE__ __n_words) {
	if (__builtin_constant_p(__word)) {
		if (__builtin_constant_p(__n_words)) {
			/* Optimizations for small data blocks (those possible with <= 2 assignments). */
			switch (__n_words) {
			case 0:
				return (__UINT16_TYPE__ *)__dst;
			case 1:
				((__UINT16_TYPE__ *)__dst)[0] = __word;
				return (__UINT16_TYPE__ *)__dst;
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
			default: break;
			}
		}
#ifndef __OPTIMIZE_SIZE__
#if defined(__CRT_HAVE_mempsetq) && __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		void *__temp;
		__temp = __libc_slow_mempsetq(__dst,
		                             (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001)),
		                              __n_words >> 2);
		switch (__n_words & 3) {
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
		__temp = __libc_slow_mempsetl(__dst,
		                             (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001)),
		                              __n_words >> 1);
		if (__n_words & 1)
			((__UINT16_TYPE__ *)__temp)[0] = __word;
		return (__UINT16_TYPE__ *)__dst;
#endif /* !__CRT_HAVE_mempsetq || __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
	}
#if !defined(__CRT_HAVE_memsetw) && defined(__CRT_HAVE_memset)
	if (__builtin_constant_p(__word)) {
		if ((__word & __UINT8_C(0xff)) == ((__word >> 8) & __UINT8_C(0xff)))
			return (__UINT16_TYPE__ *)__libc_slow_memset(__dst, __word & __UINT8_C(0xff), __n_words * 2);
	}
#endif /* !__CRT_HAVE_memsetw && __CRT_HAVE_memset */
#ifdef __CRT_HAVE_bzero
	if (__builtin_constant_p(__word) && __word == 0) {
		__localdep_bzero(__dst, __n_words * 2);
		return (__UINT16_TYPE__ *)__dst;
	}
#endif /* __CRT_HAVE_bzero */
	return __libc_slow_memsetw(__dst, __word, __n_words);
}
#endif /* !__fast_memsetw_defined */


#ifndef __fast_memset_defined
#define __fast_memset_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memset))(void *__restrict __dst,
                                                   int __byte,
                                                   __SIZE_TYPE__ __n_bytes) {
	if (__builtin_constant_p(__byte)) {
		if (__builtin_constant_p(__n_bytes)) {
			/* Optimizations for small data blocks (those possible with <= 2 assignments). */
			switch (__n_bytes) {
			case 0:
				return __dst;
			case 1:
				((__UINT8_TYPE__ *)__dst)[0] = (__UINT8_TYPE__)(__byte & __UINT8_C(0xff));
				return __dst;
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
			default: break;
			}
		}
#ifndef __OPTIMIZE_SIZE__
		/* With the fill-value known, split the call into 2:
		 * >> memset(p, 0x12, s);
		 * Compiled as one of:
		 * >> memset(mempsetl(p, 0x12121212, s >> 2), 0x12, s & 3);
		 * >> memset(mempsetq(p, 0x1212121212121212, s >> 3), 0x12, s & 7);
		 */
#if defined(__CRT_HAVE_mempsetq) && __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		void *__temp;
		__temp = __libc_slow_mempsetq(__dst,
		                             (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101)),
		                              __n_bytes >> 3);
		switch (__n_bytes & 7) {
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
		__temp = __libc_slow_mempsetl(__dst,
		                             (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101)),
		                              __n_bytes >> 2);
		switch (__n_bytes & 3) {
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
	}
#ifdef __CRT_HAVE_bzero
	if (__builtin_constant_p(__byte) && __byte == 0) {
		__localdep_bzero(__dst, __n_bytes);
		return __dst;
	}
#endif /* __CRT_HAVE_bzero */
	return __libc_slow_memset(__dst, __byte, __n_bytes);
}
#endif /* !__fast_memset_defined */


#ifdef __UINT64_TYPE__
#ifndef __fast_mempsetq_defined
#define __fast_mempsetq_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(mempsetq))(void *__restrict __dst,
                                                     __UINT64_TYPE__ __qword,
                                                     __SIZE_TYPE__ __n_qwords) {
	if (__builtin_constant_p(__qword)) {
		if (__builtin_constant_p(__n_qwords)) {
			/* Optimizations for small data blocks (those possible with <= 2 assignments). */
			switch (__n_qwords) {
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
	if (__builtin_constant_p(__qword)) {
#if defined(__CRT_HAVE_memsetl) || defined(__CRT_HAVE_mempsetl)
		if ((__qword & __UINT32_C(0xffffffff)) == ((__qword >> 32) & __UINT32_C(0xffffffff)))
			return (__UINT64_TYPE__ *)__libc_slow_mempsetl(__dst, __qword & __UINT32_C(0xffffffff), __n_qwords * 2);
#endif /* __CRT_HAVE_memsetl || __CRT_HAVE_mempsetl */
#if defined(__CRT_HAVE_memsetw) || defined(__CRT_HAVE_mempsetw)
		if ((__qword & __UINT16_C(0xffff)) == ((__qword >> 16) & __UINT16_C(0xffff)) &&
		    (__qword & __UINT16_C(0xffff)) == ((__qword >> 32) & __UINT16_C(0xffff)) &&
		    (__qword & __UINT16_C(0xffff)) == ((__qword >> 48) & __UINT16_C(0xffff)))
			return (__UINT64_TYPE__ *)__libc_slow_mempsetw(__dst, __qword & __UINT16_C(0xffff), __n_qwords * 4);
#endif /* __CRT_HAVE_memsetw || __CRT_HAVE_mempsetw */
#if defined(__CRT_HAVE_memset) || defined(__CRT_HAVE_mempset)
		if ((__qword & __UINT8_C(0xff)) == ((__qword >> 8) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 16) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 24) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 32) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 40) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 48) & __UINT8_C(0xff)) &&
		    (__qword & __UINT8_C(0xff)) == ((__qword >> 56) & __UINT8_C(0xff)))
			return (__UINT64_TYPE__ *)__libc_slow_mempset(__dst, __qword & __UINT8_C(0xff), __n_qwords * 8);
#endif /* __CRT_HAVE_memset || __CRT_HAVE_mempset */
	}
#elif (defined(__CRT_HAVE_memsetl) || defined(__CRT_HAVE_mempsetl)) && __SIZEOF_BUSINT__ < 8
	if (__builtin_constant_p(__qword) &&
	   (__qword & __UINT32_C(0xffffffff)) == ((__qword >> 32) & __UINT32_C(0xffffffff)))
		return (__UINT64_TYPE__ *)__libc_slow_mempsetl(__dst, __qword & __UINT32_C(0xffffffff), __n_qwords * 2);
#endif /* !__CRT_HAVE_memsetq && ... */
#ifdef __CRT_HAVE_bzero
	if (__builtin_constant_p(__qword) && __qword == 0) {
		__localdep_bzero(__dst, __n_qwords * 8);
		return (__UINT64_TYPE__ *)__dst + __n_qwords;
	}
#endif /* __CRT_HAVE_bzero */
	return __libc_slow_mempsetq(__dst, __qword, __n_qwords);
}
#endif /* !__fast_mempsetq_defined */
#endif /* __UINT64_TYPE__ */


#ifndef __fast_mempsetl_defined
#define __fast_mempsetl_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(mempsetl))(void *__restrict __dst,
                                                     __UINT32_TYPE__ __dword,
                                                     __SIZE_TYPE__ __n_dwords) {
	if (__builtin_constant_p(__dword)) {
		if (__builtin_constant_p(__n_dwords)) {
			/* Optimizations for small data blocks (those possible with <= 2 assignments). */
			switch (__n_dwords) {
			case 0:
				return (__UINT32_TYPE__ *)__dst;
			case 1:
				((__UINT32_TYPE__ *)__dst)[0] = __dword;
				return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 4);
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
			default: break;
			}
		}
#ifndef __OPTIMIZE_SIZE__
		/* With the fill-value known, split the call into 2:
		 * >> mempset(p, 0x12, s);
		 * Compiled as one of:
		 * >> mempset(mempsetl(p, 0x12121212, s >> 2), 0x12, s & 3);
		 * >> mempset(mempsetq(p, 0x1212121212121212, s >> 3), 0x12, s & 7);
		 */
#if defined(__CRT_HAVE_mempsetq) && __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		__dst = __libc_slow_mempsetq(__dst,
		                            (__UINT64_TYPE__)((__UINT64_TYPE__)__dword * __UINT64_C(0x0000000100000001)),
		                             __n_dwords >> 1);
		if (__n_dwords & 1) {
			((__UINT16_TYPE__ *)__dst)[0] = (__UINT16_TYPE__)((__UINT16_TYPE__)(__dword & __UINT8_C(0xff)) * __UINT16_C(0x0101));
			return (__UINT32_TYPE__ *)((__UINT8_TYPE__ *)__dst + 2);
		}
		return (__UINT32_TYPE__ *)__dst;
#endif /* __CRT_HAVE_mempsetq && __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
	}
#if !defined(__CRT_HAVE_memsetl) && !defined(__CRT_HAVE_mempsetl) && \
    (defined(__CRT_HAVE_memsetw) || defined(__CRT_HAVE_memset) || \
     defined(__CRT_HAVE_mempsetw) || defined(__CRT_HAVE_mempset))
	if (__builtin_constant_p(__dword)) {
#if defined(__CRT_HAVE_memsetw) || defined(__CRT_HAVE_mempsetw)
		if ((__dword & __UINT16_C(0xffff)) == ((__dword >> 16) & __UINT16_C(0xffff)))
			return (__UINT32_TYPE__ *)__libc_slow_mempsetw(__dst, __dword & __UINT16_C(0xffff), __n_dwords * 2);
#endif /* __CRT_HAVE_memsetw || __CRT_HAVE_mempsetw */
#if defined(__CRT_HAVE_memset) || defined(__CRT_HAVE_mempset)
		if ((__dword & __UINT8_C(0xff)) == ((__dword >> 8) & __UINT8_C(0xff)) &&
		    (__dword & __UINT8_C(0xff)) == ((__dword >> 16) & __UINT8_C(0xff)) &&
		    (__dword & __UINT8_C(0xff)) == ((__dword >> 24) & __UINT8_C(0xff)))
			return (__UINT32_TYPE__ *)__libc_slow_mempset(__dst, __dword & __UINT8_C(0xff), __n_dwords * 4);
#endif /* __CRT_HAVE_memset || __CRT_HAVE_mempset */
	}
#endif /* !__CRT_HAVE_memsetl && ... */
#ifdef __CRT_HAVE_bzero
	if (__builtin_constant_p(__dword) && __dword == 0) {
		__localdep_bzero(__dst, __n_dwords * 4);
		return (__UINT32_TYPE__ *)__dst + __n_dwords;
	}
#endif /* __CRT_HAVE_bzero */
	return __libc_slow_mempsetl(__dst, __dword, __n_dwords);
}
#endif /* !__fast_mempsetl_defined */


#ifndef __fast_mempsetw_defined
#define __fast_mempsetw_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(mempsetw))(void *__restrict __dst,
                                                     __UINT16_TYPE__ __word,
                                                     __SIZE_TYPE__ __n_words) {
	if (__builtin_constant_p(__word)) {
		if (__builtin_constant_p(__n_words)) {
			/* Optimizations for small data blocks (those possible with <= 2 assignments). */
			switch (__n_words) {
			case 0:
				return (__UINT16_TYPE__ *)__dst;
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
			default: break;
			}
		}
#ifndef __OPTIMIZE_SIZE__
		/* With the fill-value known, split the call into 2:
		 * >> mempset(p, 0x12, s);
		 * Compiled as one of:
		 * >> mempset(mempsetl(p, 0x12121212, s >> 2), 0x12, s & 3);
		 * >> mempset(mempsetq(p, 0x1212121212121212, s >> 3), 0x12, s & 7);
		 */
#if defined(__CRT_HAVE_mempsetq) && __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		__dst = __libc_slow_mempsetq(__dst,
		                            (__UINT64_TYPE__)((__UINT64_TYPE__)__word * __UINT64_C(0x0001000100010001)),
		                             __n_words >> 2);
		switch (__n_words & 3) {
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
		__dst = __libc_slow_mempsetl(__dst,
		                            (__UINT32_TYPE__)((__UINT32_TYPE__)__word * __UINT32_C(0x00010001)),
		                             __n_words >> 1);
		if (__n_words & 1) {
			((__UINT16_TYPE__ *)__dst)[0] = __word;
			return (__UINT16_TYPE__ *)__dst + 1;
		}
		return (__UINT16_TYPE__ *)__dst;
#endif /* !__CRT_HAVE_mempsetq || __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */
	}
#if !defined(__CRT_HAVE_memsetw) && !defined(__CRT_HAVE_mempsetw) && \
    (defined(__CRT_HAVE_memset) || defined(__CRT_HAVE_mempset))
	if (__builtin_constant_p(__word)) {
		if ((__word & __UINT8_C(0xff)) == ((__word >> 8) & __UINT8_C(0xff)))
			return (__UINT16_TYPE__ *)__libc_slow_mempset(__dst, __word & __UINT8_C(0xff), __n_words * 2);
	}
#endif /* !__CRT_HAVE_memsetw && ... */
#ifdef __CRT_HAVE_bzero
	if (__builtin_constant_p(__word) && __word == 0) {
		__localdep_bzero(__dst, __n_words * 2);
		return (__UINT16_TYPE__ *)__dst + __n_words;
	}
#endif /* __CRT_HAVE_bzero */
	return __libc_slow_mempsetw(__dst, __word, __n_words);
}
#endif /* !__fast_mempsetw_defined */


#ifndef __fast_mempset_defined
#define __fast_mempset_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(mempset))(void *__restrict __dst,
                                                    int __byte,
                                                    __SIZE_TYPE__ __n_bytes) {
	if (__builtin_constant_p(__byte)) {
		if (__builtin_constant_p(__n_bytes)) {
			/* Optimizations for small data blocks (those possible with <= 2 assignments). */
			switch (__n_bytes) {
			case 0:
				return __dst;
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
			default: break;
			}
		}
#ifndef __OPTIMIZE_SIZE__
		/* With the fill-value known, split the call into 2:
		 * >> mempset(p, 0x12, s);
		 * Compiled as one of:
		 * >> mempset(mempsetl(p, 0x12121212, s >> 2), 0x12, s & 3);
		 * >> mempset(mempsetq(p, 0x1212121212121212, s >> 3), 0x12, s & 7);
		 */
#if defined(__CRT_HAVE_mempsetq) && __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		__dst = __libc_slow_mempsetq(__dst,
		                            (__UINT64_TYPE__)((__UINT64_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT64_C(0x0101010101010101)),
		                             __n_bytes >> 3);
		switch (__n_bytes & 7) {
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
		__dst = __libc_slow_mempsetl(__dst,
		                            (__UINT32_TYPE__)((__UINT32_TYPE__)(__byte & __UINT8_C(0xff)) * __UINT32_C(0x01010101)),
		                             __n_bytes >> 2);
		switch (__n_bytes & 3) {
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
	}
#ifdef __CRT_HAVE_bzero
	if (__builtin_constant_p(__byte) && __byte == 0) {
		__localdep_bzero(__dst, __n_bytes);
		return (__UINT8_TYPE__ *)__dst + __n_bytes;
	}
#endif /* __CRT_HAVE_bzero */
	return __libc_slow_mempset(__dst, __byte, __n_bytes);
}
#endif /* !__fast_mempset_defined */

#ifndef __fast_memchr_defined
#define __fast_memchr_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memchr))(void const *__restrict __haystack,
                                                   int __needle, __SIZE_TYPE__ __n_bytes) {
	if (__builtin_constant_p(__n_bytes)) {
		switch (__n_bytes) {
		case 0:
			return __NULLPTR;
		case 1:
			if (((__UINT8_TYPE__ *)__haystack)[0] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 0;
			return __NULLPTR;
		case 2:
			if (((__UINT8_TYPE__ *)__haystack)[0] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 0;
			if (((__UINT8_TYPE__ *)__haystack)[1] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 1;
			return __NULLPTR;
		case 3:
			if (((__UINT8_TYPE__ *)__haystack)[0] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 0;
			if (((__UINT8_TYPE__ *)__haystack)[1] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 1;
			if (((__UINT8_TYPE__ *)__haystack)[2] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 2;
			return __NULLPTR;
		case 4:
			if (((__UINT8_TYPE__ *)__haystack)[0] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 0;
			if (((__UINT8_TYPE__ *)__haystack)[1] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 1;
			if (((__UINT8_TYPE__ *)__haystack)[2] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 2;
			if (((__UINT8_TYPE__ *)__haystack)[3] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 3;
			return __NULLPTR;
		default: break;
		}
	}
	return __libc_slow_memchr(__haystack, __needle, __n_bytes);
}
#endif /* !__fast_memchr_defined */

#ifndef __fast_memchrw_defined
#define __fast_memchrw_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memchrw))(void const *__restrict __haystack,
                                                    __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) {
	if (__builtin_constant_p(__n_words)) {
		switch (__n_words) {
		case 0:
			return __NULLPTR;
		case 1:
			if (((__UINT16_TYPE__ *)__haystack)[0] == __word)
				return (__UINT16_TYPE__ *)__haystack + 0;
			return __NULLPTR;
		case 2:
			if (((__UINT16_TYPE__ *)__haystack)[0] == __word)
				return (__UINT16_TYPE__ *)__haystack + 0;
			if (((__UINT16_TYPE__ *)__haystack)[1] == __word)
				return (__UINT16_TYPE__ *)__haystack + 1;
			return __NULLPTR;
		case 3:
			if (((__UINT16_TYPE__ *)__haystack)[0] == __word)
				return (__UINT16_TYPE__ *)__haystack + 0;
			if (((__UINT16_TYPE__ *)__haystack)[1] == __word)
				return (__UINT16_TYPE__ *)__haystack + 1;
			if (((__UINT16_TYPE__ *)__haystack)[2] == __word)
				return (__UINT16_TYPE__ *)__haystack + 2;
			return __NULLPTR;
		case 4:
			if (((__UINT16_TYPE__ *)__haystack)[0] == __word)
				return (__UINT16_TYPE__ *)__haystack + 0;
			if (((__UINT16_TYPE__ *)__haystack)[1] == __word)
				return (__UINT16_TYPE__ *)__haystack + 1;
			if (((__UINT16_TYPE__ *)__haystack)[2] == __word)
				return (__UINT16_TYPE__ *)__haystack + 2;
			if (((__UINT16_TYPE__ *)__haystack)[3] == __word)
				return (__UINT16_TYPE__ *)__haystack + 3;
			return __NULLPTR;
		default: break;
		}
	}
	return __libc_slow_memchrw(__haystack, __word, __n_words);
}
#endif /* !__fast_memchrw_defined */

#ifndef __fast_memchrl_defined
#define __fast_memchrl_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memchrl))(void const *__restrict __haystack,
                                                    __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) {
	if (__builtin_constant_p(__n_dwords)) {
		switch (__n_dwords) {
		case 0:
			return __NULLPTR;
		case 1:
			if (((__UINT32_TYPE__ *)__haystack)[0] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 0;
			return __NULLPTR;
		case 2:
			if (((__UINT32_TYPE__ *)__haystack)[0] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 0;
			if (((__UINT32_TYPE__ *)__haystack)[1] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 1;
			return __NULLPTR;
		case 3:
			if (((__UINT32_TYPE__ *)__haystack)[0] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 0;
			if (((__UINT32_TYPE__ *)__haystack)[1] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 1;
			if (((__UINT32_TYPE__ *)__haystack)[2] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 2;
			return __NULLPTR;
		case 4:
			if (((__UINT32_TYPE__ *)__haystack)[0] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 0;
			if (((__UINT32_TYPE__ *)__haystack)[1] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 1;
			if (((__UINT32_TYPE__ *)__haystack)[2] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 2;
			if (((__UINT32_TYPE__ *)__haystack)[3] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 3;
			return __NULLPTR;
		default: break;
		}
	}
	return __libc_slow_memchrl(__haystack, __dword, __n_dwords);
}
#endif /* !__fast_memchrl_defined */

#ifndef __fast_memchrq_defined
#define __fast_memchrq_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memchrq))(void const *__restrict __haystack,
                                                    __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) {
	if (__builtin_constant_p(__n_qwords)) {
		switch (__n_qwords) {
		case 0:
			return __NULLPTR;
		case 1:
			if (((__UINT64_TYPE__ *)__haystack)[0] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 0;
			return __NULLPTR;
		case 2:
			if (((__UINT64_TYPE__ *)__haystack)[0] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 0;
			if (((__UINT64_TYPE__ *)__haystack)[1] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 1;
			return __NULLPTR;
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 3:
			if (((__UINT64_TYPE__ *)__haystack)[0] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 0;
			if (((__UINT64_TYPE__ *)__haystack)[1] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 1;
			if (((__UINT64_TYPE__ *)__haystack)[2] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 2;
			return __NULLPTR;
		case 4:
			if (((__UINT64_TYPE__ *)__haystack)[0] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 0;
			if (((__UINT64_TYPE__ *)__haystack)[1] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 1;
			if (((__UINT64_TYPE__ *)__haystack)[2] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 2;
			if (((__UINT64_TYPE__ *)__haystack)[3] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 3;
			return __NULLPTR;
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		default: break;
		}
	}
	return __libc_slow_memchrq(__haystack, __qword, __n_qwords);
}
#endif /* !__fast_memchrq_defined */

#ifndef __fast_memrchr_defined
#define __fast_memrchr_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memrchr))(void const *__restrict __haystack,
                                                    int __needle, __SIZE_TYPE__ __n_bytes) {
	if (__builtin_constant_p(__n_bytes)) {
		switch (__n_bytes) {
		case 4:
			if (((__UINT8_TYPE__ *)__haystack)[3] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 3;
			__ATTR_FALLTHROUGH
		case 3:
			if (((__UINT8_TYPE__ *)__haystack)[2] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 2;
			__ATTR_FALLTHROUGH
		case 2:
			if (((__UINT8_TYPE__ *)__haystack)[1] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 1;
			__ATTR_FALLTHROUGH
		case 1:
			if (((__UINT8_TYPE__ *)__haystack)[0] == (__UINT8_TYPE__)__needle)
				return (__UINT8_TYPE__ *)__haystack + 0;
			__ATTR_FALLTHROUGH
		case 0:
			return __NULLPTR;
		default: break;
		}
	}
	return __libc_slow_memrchr(__haystack, __needle, __n_bytes);
}
#endif /* !__fast_memrchr_defined */

#ifndef __fast_memrchrw_defined
#define __fast_memrchrw_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memrchrw))(void const *__restrict __haystack,
                                                     __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) {
	if (__builtin_constant_p(__n_words)) {
		switch (__n_words) {
		case 4:
			if (((__UINT16_TYPE__ *)__haystack)[3] == __word)
				return (__UINT16_TYPE__ *)__haystack + 3;
			__ATTR_FALLTHROUGH
		case 3:
			if (((__UINT16_TYPE__ *)__haystack)[2] == __word)
				return (__UINT16_TYPE__ *)__haystack + 2;
			__ATTR_FALLTHROUGH
		case 2:
			if (((__UINT16_TYPE__ *)__haystack)[1] == __word)
				return (__UINT16_TYPE__ *)__haystack + 1;
			__ATTR_FALLTHROUGH
		case 1:
			if (((__UINT16_TYPE__ *)__haystack)[0] == __word)
				return (__UINT16_TYPE__ *)__haystack + 0;
			__ATTR_FALLTHROUGH
		case 0:
			return __NULLPTR;
		default: break;
		}
	}
	return __libc_slow_memrchrw(__haystack, __word, __n_words);
}
#endif /* !__fast_memrchrw_defined */

#ifndef __fast_memrchrl_defined
#define __fast_memrchrl_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1))
__UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memrchrl))(void const *__restrict __haystack,
                                                                      __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) {
	if (__builtin_constant_p(__n_dwords)) {
		switch (__n_dwords) {
		case 4:
			if (((__UINT32_TYPE__ *)__haystack)[3] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 3;
			__ATTR_FALLTHROUGH
		case 3:
			if (((__UINT32_TYPE__ *)__haystack)[2] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 2;
			__ATTR_FALLTHROUGH
		case 2:
			if (((__UINT32_TYPE__ *)__haystack)[1] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 1;
			__ATTR_FALLTHROUGH
		case 1:
			if (((__UINT32_TYPE__ *)__haystack)[0] == __dword)
				return (__UINT32_TYPE__ *)__haystack + 0;
			__ATTR_FALLTHROUGH
		case 0:
			return __NULLPTR;
		default: break;
		}
	}
	return __libc_slow_memrchrl(__haystack, __dword, __n_dwords);
}
#endif /* !__fast_memrchrl_defined */

#ifndef __fast_memrchrq_defined
#define __fast_memrchrq_defined 1
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memrchrq))(void const *__restrict __haystack,
                                                     __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) {
	if (__builtin_constant_p(__n_qwords)) {
		switch (__n_qwords) {
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
		case 4:
			if (((__UINT64_TYPE__ *)__haystack)[3] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 3;
			__ATTR_FALLTHROUGH
		case 3:
			if (((__UINT64_TYPE__ *)__haystack)[2] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 2;
			__ATTR_FALLTHROUGH
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
		case 2:
			if (((__UINT64_TYPE__ *)__haystack)[1] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 1;
			__ATTR_FALLTHROUGH
		case 1:
			if (((__UINT64_TYPE__ *)__haystack)[0] == __qword)
				return (__UINT64_TYPE__ *)__haystack + 0;
			__ATTR_FALLTHROUGH
		case 0:
			return __NULLPTR;
		default: break;
		}
	}
	return __libc_slow_memrchrq(__haystack, __qword, __n_qwords);
}
#endif /* !__fast_memrchrq_defined */

#ifndef __fast_memcmp_defined
#define __fast_memcmp_defined 1
#include <hybrid/byteorder.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memcmp))(void const *__restrict __s1,
                                                   void const *__restrict __s2,
                                                   __SIZE_TYPE__ __n_bytes) {
	/* memcmp() behaves differently from strcmp(), in that memcmp is allowed to assume
	 * both input data blocks contain at least `N_BYTES' of valid data, which
	 * implementation is allowed to access in any order it wishes.
	 * With that in mind, we are allowed to optimize something like:
	 * >> memcmp(a, b, 4) == 0;
	 * Into:
	 * >> *(u32 *)a == *(u32 *)b
	 * For `strcmp()' we can't actually do this, because we must not attempt to access
	 * any bytes of either string following a \0-character.
	 *
	 * Proof of this behavior is hard to come by, but I managed to find this (somewhat
	 * unrelated) stackoverflow question, where all the answers unquestioningly indicate
	 * that using memcmp() to access out-of-bounds data causes undefined behavior, even
	 * if memory leading up to the undefined portion is guarantied to compare non-equal,
	 * thus allowing us to perform this optimization for memcmp()!
	 * https://stackoverflow.com/questions/37782671/comparing-two-strings-using-memcmp-in-c
	 */
	if (__builtin_constant_p(__n_bytes)) {
		/* NOTE: The `__DO_COMPARE()' macro is designed to best allow GCC
		 *       to determine which path is used by which comparison.
		 * For example, `if (memcmp(a, b, 4) < 0) { ... }' can get fully
		 * optimized to `if (*(u32 *)a < *(u32 *)b) { ... }' */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __DO_COMPARE(T, off) \
	{                                \
		T __x1 = *((T *)__s1 + off), \
		  __x2 = *((T *)__s2 + off); \
		if (__x1 < __x2)             \
			return -1;               \
		if (__x1 > __x2)             \
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
		if (__x1 < __x2)                                       \
			return -1;                                         \
		if (__x1 > __x2)                                       \
			return 1;                                          \
	}
#define __DO_COMPARE16(off)                                          \
	{                                                                \
		__UINT16_TYPE__ __x1 = *((__UINT16_TYPE__ *)__s1 + off),     \
		                __x2 = *((__UINT16_TYPE__ *)__s2 + off);     \
		if (__x1 != __x2) {                                          \
			if ((__x1 & __UINT8_C(0xff)) < (__x2 & __UINT8_C(0xff))) \
				return -1;                                           \
			if ((__x1 & __UINT8_C(0xff)) > (__x2 & __UINT8_C(0xff))) \
				return 1;                                            \
			if (__x1 < __x2)                                         \
				return -1;                                           \
			return 1;                                                \
		}                                                            \
	}
#define __DO_COMPARE32(off)                                                    \
	{                                                                          \
		__UINT32_TYPE__ __x1 = *((__UINT32_TYPE__ *)__s1 + off),               \
		                __x2 = *((__UINT32_TYPE__ *)__s2 + off);               \
		if (__x1 != __x2) {                                                    \
			if ((__x1 & __UINT8_C(0xff)) < (__x2 & __UINT8_C(0xff)))           \
				return -1;                                                     \
			if ((__x1 & __UINT8_C(0xff)) > (__x2 & __UINT8_C(0xff)))           \
				return 1;                                                      \
			if ((__x1 & __UINT16_C(0xff00)) < (__x2 & __UINT16_C(0xff00)))     \
				return -1;                                                     \
			if ((__x1 & __UINT16_C(0xff00)) > (__x2 & __UINT16_C(0xff00)))     \
				return 1;                                                      \
			if ((__x1 & __UINT32_C(0xff0000)) < (__x2 & __UINT32_C(0xff0000))) \
				return -1;                                                     \
			if ((__x1 & __UINT32_C(0xff0000)) > (__x2 & __UINT32_C(0xff0000))) \
				return 1;                                                      \
			if (__x1 < __x2)                                                   \
				return -1;                                                     \
			return 1;                                                          \
		}                                                                      \
	}
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
#define __DO_COMPARE64(off)                                                                    \
	{                                                                                          \
		__UINT64_TYPE__ __x1 = *((__UINT64_TYPE__ *)__s1 + off),                               \
		                __x2 = *((__UINT64_TYPE__ *)__s2 + off);                               \
		if (__x1 != __x2) {                                                                    \
			if ((__x1 & __UINT8_C(0xff)) < (__x2 & __UINT8_C(0xff)))                           \
				return -1;                                                                     \
			if ((__x1 & __UINT8_C(0xff)) > (__x2 & __UINT8_C(0xff)))                           \
				return 1;                                                                      \
			if ((__x1 & __UINT16_C(0xff00)) < (__x2 & __UINT16_C(0xff00)))                     \
				return -1;                                                                     \
			if ((__x1 & __UINT16_C(0xff00)) > (__x2 & __UINT16_C(0xff00)))                     \
				return 1;                                                                      \
			if ((__x1 & __UINT32_C(0xff0000)) < (__x2 & __UINT32_C(0xff0000)))                 \
				return -1;                                                                     \
			if ((__x1 & __UINT32_C(0xff0000)) > (__x2 & __UINT32_C(0xff0000)))                 \
				return 1;                                                                      \
			if ((__x1 & __UINT32_C(0xff000000)) < (__x2 & __UINT32_C(0xff000000)))             \
				return -1;                                                                     \
			if ((__x1 & __UINT32_C(0xff000000)) > (__x2 & __UINT32_C(0xff000000)))             \
				return 1;                                                                      \
			if ((__x1 & __UINT64_C(0xff00000000)) < (__x2 & __UINT64_C(0xff00000000)))         \
				return -1;                                                                     \
			if ((__x1 & __UINT64_C(0xff00000000)) > (__x2 & __UINT64_C(0xff00000000)))         \
				return 1;                                                                      \
			if ((__x1 & __UINT64_C(0xff0000000000)) < (__x2 & __UINT64_C(0xff0000000000)))     \
				return -1;                                                                     \
			if ((__x1 & __UINT64_C(0xff0000000000)) > (__x2 & __UINT64_C(0xff0000000000)))     \
				return 1;                                                                      \
			if ((__x1 & __UINT64_C(0xff000000000000)) < (__x2 & __UINT64_C(0xff000000000000))) \
				return -1;                                                                     \
			if ((__x1 & __UINT64_C(0xff000000000000)) > (__x2 & __UINT64_C(0xff000000000000))) \
				return 1;                                                                      \
			if (__x1 < __x2)                                                                   \
				return -1;                                                                     \
			return 1;                                                                          \
		}                                                                                      \
	}
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */

		/* Add constant cases all compares with less than 2 memory lookups. */
		switch (__n_bytes) {
		case 0:
			return 0;
		case 1:
			__DO_COMPARE8(0)
			return 0;
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
		default: break;
		}
#undef __DO_COMPARE64
#undef __DO_COMPARE32
#undef __DO_COMPARE16
#undef __DO_COMPARE8
#undef __DO_COMPARE
	}
	return __libc_slow_memcmp(__s1, __s2, __n_bytes);
}
#endif /* !__fast_memcmp_defined */

#ifndef __fast_memcmpw_defined
#define __fast_memcmpw_defined 1
#include <hybrid/byteorder.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __INT16_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memcmpw))(void const *__restrict __s1,
                                                    void const *__restrict __s2,
                                                    __SIZE_TYPE__ __n_words) {
	if (__builtin_constant_p(__n_words)) {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __DO_COMPARE(T, off)         \
	{                                \
		T __x1 = *((T *)__s1 + off), \
		  __x2 = *((T *)__s2 + off); \
		if (__x1 < __x2)             \
			return -1;               \
		if (__x1 > __x2)             \
			return 1;                \
	}
#define __DO_COMPARE16(off) __DO_COMPARE(__UINT16_TYPE__, off)
#define __DO_COMPARE32(off) __DO_COMPARE(__UINT32_TYPE__, off)
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
#define __DO_COMPARE64(off) __DO_COMPARE(__UINT64_TYPE__, off)
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#define __DO_COMPARE16(off) \
	{                                                            \
		__UINT16_TYPE__ __x1 = *((__UINT16_TYPE__ *)__s1 + off), \
		                __x2 = *((__UINT16_TYPE__ *)__s2 + off); \
		if (__x1 != __x2) {                                      \
			if (__x1 < __x2)                                     \
				return -1;                                       \
			return 1;                                            \
		}                                                        \
	}
#define __DO_COMPARE32(off) \
	{                                                                      \
		__UINT32_TYPE__ __x1 = *((__UINT32_TYPE__ *)__s1 + off),           \
		                __x2 = *((__UINT32_TYPE__ *)__s2 + off);           \
		if (__x1 != __x2) {                                                \
			if ((__x1 & __UINT16_C(0xffff)) < (__x2 & __UINT16_C(0xffff))) \
				return -1;                                                 \
			if ((__x1 & __UINT16_C(0xffff)) > (__x2 & __UINT16_C(0xffff))) \
				return 1;                                                  \
			if (__x1 < __x2)                                               \
				return -1;                                                 \
			return 1;                                                      \
		}                                                                  \
	}
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
#define __DO_COMPARE64(off) \
	{                                                                                      \
		__UINT64_TYPE__ __x1 = *((__UINT64_TYPE__ *)__s1 + off),                           \
		                __x2 = *((__UINT64_TYPE__ *)__s2 + off);                           \
		if (__x1 != __x2) {                                                                \
			if ((__x1 & __UINT16_C(0xffff)) < (__x2 & __UINT16_C(0xffff)))                 \
				return -1;                                                                 \
			if ((__x1 & __UINT16_C(0xffff)) > (__x2 & __UINT16_C(0xffff)))                 \
				return 1;                                                                  \
			if ((__x1 & __UINT32_C(0xffff0000)) < (__x2 & __UINT32_C(0xffff0000)))         \
				return -1;                                                                 \
			if ((__x1 & __UINT32_C(0xffff0000)) > (__x2 & __UINT32_C(0xffff0000)))         \
				return 1;                                                                  \
			if ((__x1 & __UINT64_C(0xffff00000000)) < (__x2 & __UINT64_C(0xffff00000000))) \
				return -1;                                                                 \
			if ((__x1 & __UINT64_C(0xffff00000000)) > (__x2 & __UINT64_C(0xffff00000000))) \
				return 1;                                                                  \
			if (__x1 < __x2)                                                               \
				return -1;                                                                 \
			return 1;                                                                      \
		}                                                                                  \
	}
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */

		/* Add constant cases all compares with less than 2 memory lookups. */
		switch (__n_words) {
		case 0:
			return 0;
		case 1:
			__DO_COMPARE16(0)
			return 0;
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
		default: break;
		}
#undef __DO_COMPARE64
#undef __DO_COMPARE32
#undef __DO_COMPARE16
#undef __DO_COMPARE
	}
	return __libc_slow_memcmpw(__s1, __s2, __n_words);
}
#endif /* !__fast_memcmpw_defined */

#ifndef __fast_memcmpl_defined
#define __fast_memcmpl_defined 1
#include <hybrid/byteorder.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __INT32_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memcmpl))(void const *__restrict __s1,
                                                    void const *__restrict __s2,
                                                    __SIZE_TYPE__ __n_dwords) {
	if (__builtin_constant_p(__n_dwords)) {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __DO_COMPARE(T, off) \
	{                                \
		T __x1 = *((T *)__s1 + off), \
		  __x2 = *((T *)__s2 + off); \
		if (__x1 < __x2)             \
			return -1;               \
		if (__x1 > __x2)             \
			return 1;                \
	}
#define __DO_COMPARE32(off) __DO_COMPARE(__UINT32_TYPE__, off)
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
#define __DO_COMPARE64(off) __DO_COMPARE(__UINT64_TYPE__, off)
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#define __DO_COMPARE32(off) \
	{                                                            \
		__UINT32_TYPE__ __x1 = *((__UINT32_TYPE__ *)__s1 + off), \
		                __x2 = *((__UINT32_TYPE__ *)__s2 + off); \
		if (__x1 != __x2) {                                      \
			if (__x1 < __x2)                                     \
				return -1;                                       \
			return 1;                                            \
		}                                                        \
	}
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
#define __DO_COMPARE64(off) \
	{                                                                              \
		__UINT64_TYPE__ __x1 = *((__UINT64_TYPE__ *)__s1 + off),                   \
		                __x2 = *((__UINT64_TYPE__ *)__s2 + off);                   \
		if (__x1 != __x2) {                                                        \
			if ((__x1 & __UINT32_C(0xffffffff)) < (__x2 & __UINT32_C(0xffffffff))) \
				return -1;                                                         \
			if ((__x1 & __UINT32_C(0xffffffff)) > (__x2 & __UINT32_C(0xffffffff))) \
				return 1;                                                          \
			if (__x1 < __x2)                                                       \
				return -1;                                                         \
			return 1;                                                              \
		}                                                                          \
	}
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */

		/* Add constant cases all compares with less than 2 memory lookups. */
		switch (__n_dwords) {
		case 0:
			return 0;
		case 1:
			__DO_COMPARE32(0)
			return 0;
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
		default:
			break;
		}
#undef __DO_COMPARE64
#undef __DO_COMPARE32
#undef __DO_COMPARE
	}
	return __libc_slow_memcmpl(__s1, __s2, __n_dwords);
}
#endif /* !__fast_memcmpl_defined */

#ifdef __UINT64_TYPE__
#ifndef __fast_memcmpq_defined
#define __fast_memcmpq_defined 1
#include <hybrid/byteorder.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __INT64_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memcmpq))(void const *__restrict __s1,
                                                    void const *__restrict __s2,
                                                    __SIZE_TYPE__ __n_qwords) {
	if (__builtin_constant_p(__n_qwords)) {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __DO_COMPARE(T, off) \
	{                                \
		T __x1 = *((T *)__s1 + off), \
		  __x2 = *((T *)__s2 + off); \
		if (__x1 < __x2)             \
			return -1;               \
		if (__x1 > __x2)             \
			return 1;                \
	}
#define __DO_COMPARE32(off) __DO_COMPARE(__UINT32_TYPE__, off)
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
#define __DO_COMPARE64(off) __DO_COMPARE(__UINT64_TYPE__, off)
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#define __DO_COMPARE32(off) \
	{                                                            \
		__UINT32_TYPE__ __x1 = *((__UINT32_TYPE__ *)__s1 + off), \
		                __x2 = *((__UINT32_TYPE__ *)__s2 + off); \
		if (__x1 != __x2) {                                      \
			if (__x1 < __x2)                                     \
				return -1;                                       \
			return 1;                                            \
		}                                                        \
	}
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
#define __DO_COMPARE64(off) \
	{                                                                              \
		__UINT64_TYPE__ __x1 = *((__UINT64_TYPE__ *)__s1 + off),                   \
		                __x2 = *((__UINT64_TYPE__ *)__s2 + off);                   \
		if (__x1 != __x2) {                                                        \
			if ((__x1 & __UINT32_C(0xffffffff)) < (__x2 & __UINT32_C(0xffffffff))) \
				return -1;                                                         \
			if ((__x1 & __UINT32_C(0xffffffff)) > (__x2 & __UINT32_C(0xffffffff))) \
				return 1;                                                          \
			if (__x1 < __x2)                                                       \
				return -1;                                                         \
			return 1;                                                              \
		}                                                                          \
	}
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
		/* Add constant cases all compares with less than 2 memory lookups. */
		switch (__n_qwords) {
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
	return __libc_slow_memcmpq(__s1, __s2, __n_qwords);
}
#endif /* !__fast_memcmpq_defined */
#endif /* __UINT64_TYPE__ */

#ifdef __UINT64_TYPE__
#ifndef __fast_memmoveq_defined
#define __fast_memmoveq_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memmoveq))(void *__dst,
                                                     void const *__src,
                                                     __SIZE_TYPE__ __n_qwords) {
	if (__builtin_constant_p(__n_qwords)) {
		/* Optimizations when the move can be done using
		 * at most 2 read/writes, and at most 1 temporary. */
		switch (__n_qwords) {
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
		}
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
		/* More optimizations when the move can be done using
		 * at most 4 read/writes, and at most 3 temporaries. */
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
		}
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */

		default:
			break;
		}
	}
	return __libc_slow_memmoveq(__dst, __src, __n_qwords);
}
#endif /* !__fast_memmoveq_defined */
#endif /* __UINT64_TYPE__ */

#ifndef __fast_memmovel_defined
#define __fast_memmovel_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memmovel))(void *__dst,
                                                     void const *__src,
                                                     __SIZE_TYPE__ __n_dwords) {
	if (__builtin_constant_p(__n_dwords)) {
		/* Optimizations when the move can be done using
		 * at most 2 read/writes, and at most 1 temporary. */
		switch (__n_dwords) {
		case 0:
			return (__UINT32_TYPE__ *)__dst;
		case 1:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)__dst;
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
		 * at most 4 read/writes, and at most 3 temporaries. */
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
		}
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */

		default: break;
		}
#if defined(__CRT_HAVE_memmoveq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		if (!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_slow_memmoveq(__dst, __src, __n_dwords >> 1);
		{
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[__n_dwords-1];
			__dst = __libc_slow_memmoveq(__dst, __src, __n_dwords >> 1);
			((__UINT32_TYPE__ *)__dst)[__n_dwords-1] = __temp;
		}
		return (__UINT32_TYPE__ *)__dst;
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_slow_memmoveq(__dst, __src, __n_dwords >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmoveq && __SIZEOF_BUSINT__ >= 8 */
	}
	return __libc_slow_memmovel(__dst, __src, __n_dwords);
}
#endif /* !__fast_memmovel_defined */

#ifndef __fast_memmovew_defined
#define __fast_memmovew_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memmovew))(void *__dst,
                                                     void const *__src,
                                                     __SIZE_TYPE__ __n_words) {
	if (__builtin_constant_p(__n_words)) {
		/* Optimizations when the move can be done using
		 * at most 2 read/writes, and at most 1 temporary. */
		switch (__n_words) {
		case 0:
			return (__UINT16_TYPE__ *)__dst;
		case 1:
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		case 2:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)__dst;
		{
			__UINT16_TYPE__ __temp;
		case 3:
			__temp = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[2] = __temp;
			return (__UINT16_TYPE__ *)__dst;
		}
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
		}
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

		/* More optimizations when the move can be done using
		 * at most 4 read/writes, and at most 3 temporaries. */
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
		}
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */

		default:
			break;
		}
#if defined(__CRT_HAVE_memmoveq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch (__n_words & 3) {
		case 0:
			return (__UINT16_TYPE__ *)__libc_slow_memmoveq(__dst, __src, __n_words >> 2);
		case 1: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[__n_words-1];
			__dst = __libc_slow_memmoveq(__dst, __src, __n_words >> 2);
			((__UINT16_TYPE__ *)__dst)[__n_words-1] = __temp;
			return (__UINT16_TYPE__ *)__dst;
		}	break;

		case 2: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[(__n_words >> 1)-1];
			__dst = __libc_slow_memmoveq(__dst, __src, __n_words >> 2);
			((__UINT32_TYPE__ *)__dst)[(__n_words >> 1)-1] = __temp;
			return (__UINT16_TYPE__ *)__dst;
		}
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_words & 3))
			return (__UINT16_TYPE__ *)__libc_slow_memmoveq(__dst, __src, __n_words >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmoveq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_memmovel)
#ifndef __OPTIMIZE_SIZE__
		if (!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_slow_memmovel(__dst, __src, __n_words >> 1);
		{
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[__n_words-1];
			__dst = __libc_slow_memmovel(__dst, __src, __n_words >> 1);
			((__UINT16_TYPE__ *)__dst)[__n_words-1] = __temp;
		}
		return (__UINT16_TYPE__ *)__dst;
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_slow_memmovel(__dst, __src, __n_words >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmovel */
	}
	return __libc_slow_memmovew(__dst, __src, __n_words);
}
#endif /* !__fast_memmovew_defined */

#ifndef __fast_memmove_defined
#define __fast_memmove_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(memmove))(void *__dst,
                                                    void const *__src,
                                                    __SIZE_TYPE__ __n_bytes) {
	if (__builtin_constant_p(__n_bytes)) {
		/* Optimizations when the move can be done using
		 * at most 2 read/writes, and at most 1 temporary. */
		switch (__n_bytes) {
		case 0:
			return __dst;
		case 1:
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			return __dst;
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
		}
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
		}
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

		/* More optimizations when the move can be done using
		 * at most 4 read/writes, and at most 3 temporaries. */
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
		}
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
		}
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */

		default:
			break;
		}
#if defined(__CRT_HAVE_memmoveq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch (__n_bytes & 7) {
		case 0:
			return __libc_slow_memmoveq(__dst, __src, __n_bytes >> 3);
		case 1: {
			__UINT8_TYPE__ __temp;
			__temp = ((__UINT8_TYPE__ const *)__src)[__n_bytes-1];
			__dst = __libc_slow_memmoveq(__dst, __src, __n_bytes >> 3);
			((__UINT8_TYPE__ *)__dst)[__n_bytes-1] = __temp;
			return __dst;
		}	break;

		case 2: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1)-1];
			__dst = __libc_slow_memmoveq(__dst, __src, __n_bytes >> 3);
			((__UINT16_TYPE__ *)__dst)[(__n_bytes >> 1)-1] = __temp;
			return __dst;
		}	break;

		case 4: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[(__n_bytes >> 2)-1];
			__dst = __libc_slow_memmoveq(__dst, __src, __n_bytes >> 3);
			((__UINT32_TYPE__ *)__dst)[(__n_bytes >> 2)-1] = __temp;
			return __dst;
		}
		default:
			break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_bytes & 7))
			return __libc_slow_memmoveq(__dst, __src, __n_bytes >> 3);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmoveq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_memmovel)
#ifndef __OPTIMIZE_SIZE__
		switch (__n_bytes & 3) {
		case 0:
			return __libc_slow_memmovel(__dst, __src, __n_bytes >> 2);
		case 1: {
			__UINT8_TYPE__ __temp;
			__temp = ((__UINT8_TYPE__ const *)__src)[__n_bytes-1];
			__dst = __libc_slow_memmovel(__dst, __src, __n_bytes >> 2);
			((__UINT8_TYPE__ *)__dst)[__n_bytes-1] = __temp;
			return __dst;
		}	break;

		case 2: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1)-1];
			__dst = __libc_slow_memmovel(__dst, __src, __n_bytes >> 2);
			((__UINT16_TYPE__ *)__dst)[(__n_bytes >> 1)-1] = __temp;
			return __dst;
		}
		default:
			break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_bytes & 3))
			return __libc_slow_memmovel(__dst, __src, __n_bytes >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmovel */
#if defined(__CRT_HAVE_memmovew)
#ifndef __OPTIMIZE_SIZE__
		if (!(__n_bytes & 1))
			return __libc_slow_memmovew(__dst, __src, __n_bytes >> 1);
		{
			__UINT8_TYPE__ __temp;
			__temp = ((__UINT8_TYPE__ const *)__src)[__n_bytes-1];
			__dst = __libc_slow_memmovew(__dst, __src, __n_bytes >> 1);
			((__UINT8_TYPE__ *)__dst)[__n_bytes-1] = __temp;
		}
		return __dst;
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_bytes & 1))
			return __libc_slow_memmovew(__dst, __src, __n_bytes >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_memmovew */
	}
	return __libc_slow_memmove(__dst, __src, __n_bytes);
}
#endif /* !__fast_memmove_defined */

#ifdef __UINT64_TYPE__
#ifndef __fast_mempmoveq_defined
#define __fast_mempmoveq_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(mempmoveq))(void *__dst,
                                                      void const *__src,
                                                      __SIZE_TYPE__ __n_qwords) {
	if (__builtin_constant_p(__n_qwords)) {
		/* Optimizations when the move can be done using
		 * at most 2 read/writes, and at most 1 temporary. */
		switch (__n_qwords) {
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
		}
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

		/* More optimizations when the move can be done using
		 * at most 4 read/writes, and at most 3 temporaries. */
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
		}
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */

		default:
			break;
		}
	}
	return __libc_slow_mempmoveq(__dst, __src, __n_qwords);
}
#endif /* !__fast_mempmoveq_defined */
#endif /* __UINT64_TYPE__ */

#ifndef __fast_mempmovel_defined
#define __fast_mempmovel_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(mempmovel))(void *__dst,
                                                      void const *__src,
                                                      __SIZE_TYPE__ __n_dwords) {
	if (__builtin_constant_p(__n_dwords)) {
		/* Optimizations when the move can be done using
		 * at most 2 read/writes, and at most 1 temporary. */
		switch (__n_dwords) {
		case 0:
			return (__UINT32_TYPE__ *)__dst;
		case 1:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT32_TYPE__ *)((__BYTE_TYPE__ *)__dst + 4);
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
		}
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

		/* More optimizations when the move can be done using
		 * at most 4 read/writes, and at most 3 temporaries. */
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
		}
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */

		default:
			break;
		}
#if defined(__CRT_HAVE_mempmoveq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		if (!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_slow_mempmoveq(__dst, __src, __n_dwords >> 1);
		{
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[__n_dwords-1];
			__dst = __libc_slow_mempmoveq(__dst, __src, __n_dwords >> 1);
			((__UINT32_TYPE__ *)__dst)[0] = __temp;
		}
		return (__UINT32_TYPE__ *)__dst + 1;
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_dwords & 1))
			return (__UINT32_TYPE__ *)__libc_slow_mempmoveq(__dst, __src, __n_dwords >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmoveq && __SIZEOF_BUSINT__ >= 8 */
	}
	return __libc_slow_mempmovel(__dst, __src, __n_dwords);
}
#endif /* !__fast_mempmovel_defined */

#ifndef __fast_mempmovew_defined
#define __fast_mempmovew_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(mempmovew))(void *__dst,
                                                      void const *__src,
                                                      __SIZE_TYPE__ __n_words) {
	if (__builtin_constant_p(__n_words)) {
		/* Optimizations when the move can be done using
		 * at most 2 read/writes, and at most 1 temporary. */
		switch (__n_words) {
		case 0:
			return (__UINT16_TYPE__ *)__dst;
		case 1:
			((__UINT16_TYPE__ *)__dst)[0] = ((__UINT16_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 2);
		case 2:
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 4);
		case 3: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[2];
			((__UINT32_TYPE__ *)__dst)[0] = ((__UINT32_TYPE__ const *)__src)[0];
			((__UINT16_TYPE__ *)__dst)[2] = __temp;
			return (__UINT16_TYPE__ *)((__BYTE_TYPE__ *)__dst + 6);
		}
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
		}
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

		/* More optimizations when the move can be done using
		 * at most 4 read/writes, and at most 3 temporaries. */
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
		}
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */

		default:
			break;
		}
#if defined(__CRT_HAVE_mempmoveq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch (__n_words & 3) {
		case 0:
			return (__UINT16_TYPE__ *)__libc_slow_mempmoveq(__dst, __src, __n_words >> 2);
		case 1: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[__n_words-1];
			__dst = __libc_slow_mempmoveq(__dst, __src, __n_words >> 2);
			((__UINT16_TYPE__ *)__dst)[0] = __temp;
			return (__UINT16_TYPE__ *)__dst + 1;
		}	break;

		case 2: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[(__n_words >> 1)-1];
			__dst = __libc_slow_mempmoveq(__dst, __src, __n_words >> 2);
			((__UINT32_TYPE__ *)__dst)[0] = __temp;
			return (__UINT16_TYPE__ *)__dst + 2;
		}
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_words & 3))
			return (__UINT16_TYPE__ *)__libc_slow_mempmoveq(__dst, __src, __n_words >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmoveq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_mempmovel)
#ifndef __OPTIMIZE_SIZE__
		if (!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_slow_mempmovel(__dst, __src, __n_words >> 1);
		{
			__UINT16_TYPE__ __temp = ((__UINT16_TYPE__ const *)__src)[__n_words-1];
			__dst = __libc_slow_mempmovel(__dst, __src, __n_words >> 1);
			((__UINT16_TYPE__ *)__dst)[0] = __temp;
		}
		return (__UINT16_TYPE__ *)__dst + 1;
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_words & 1))
			return (__UINT16_TYPE__ *)__libc_slow_mempmovel(__dst, __src, __n_words >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmovel */
	}
	return __libc_slow_mempmovew(__dst, __src, __n_words);
}
#endif /* !__fast_mempmovew_defined */

#ifndef __fast_mempmove_defined
#define __fast_mempmove_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(mempmove))(void *__dst,
                                                     void const *__src,
                                                     __SIZE_TYPE__ __n_bytes) {
	if (__builtin_constant_p(__n_bytes)) {
		/* Optimizations when the move can be done using
		 * at most 2 read/writes, and at most 1 temporary. */
		switch (__n_bytes) {
		case 0:
			return __dst;
		case 1:
			((__UINT8_TYPE__ *)__dst)[0] = ((__UINT8_TYPE__ const *)__src)[0];
			return (__BYTE_TYPE__ *)__dst + 1;
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
		}
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
		}
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */

		/* More optimizations when the move can be done using
		 * at most 4 read/writes, and at most 3 temporaries. */
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
		}
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
		}
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !__OPTIMIZE_SIZE__ */

		default:
			break;
		}
#if defined(__CRT_HAVE_mempmoveq) && __SIZEOF_BUSINT__ >= 8
#ifndef __OPTIMIZE_SIZE__
		switch (__n_bytes & 7) {
		case 0:
			return __libc_slow_mempmoveq(__dst, __src, __n_bytes >> 3);
		case 1: {
			__UINT8_TYPE__ __temp;
			__temp = ((__UINT8_TYPE__ const *)__src)[__n_bytes-1];
			__dst = __libc_slow_mempmoveq(__dst, __src, __n_bytes >> 3);
			((__UINT8_TYPE__ *)__dst)[0] = __temp;
			return (__BYTE_TYPE__ *)__dst + 1;
		}	break;

		case 2: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1)-1];
			__dst = __libc_slow_mempmoveq(__dst, __src, __n_bytes >> 3);
			((__UINT16_TYPE__ *)__dst)[0] = __temp;
			return (__BYTE_TYPE__ *)__dst + 2;
		}	break;

		case 4: {
			__UINT32_TYPE__ __temp;
			__temp = ((__UINT32_TYPE__ const *)__src)[(__n_bytes >> 2)-1];
			__dst = __libc_slow_mempmoveq(__dst, __src, __n_bytes >> 3);
			((__UINT32_TYPE__ *)__dst)[0] = __temp;
			return (__BYTE_TYPE__ *)__dst + 4;
		}
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_bytes & 7))
			return __libc_slow_mempmoveq(__dst, __src, __n_bytes >> 3);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmoveq && __SIZEOF_BUSINT__ >= 8 */
#if defined(__CRT_HAVE_mempmovel)
#ifndef __OPTIMIZE_SIZE__
		switch (__n_bytes & 3) {
		case 0:
			return __libc_slow_mempmovel(__dst, __src, __n_bytes >> 2);
		case 1: {
			__UINT8_TYPE__ __temp;
			__temp = ((__UINT8_TYPE__ const *)__src)[__n_bytes-1];
			__dst = __libc_slow_mempmovel(__dst, __src, __n_bytes >> 2);
			((__UINT8_TYPE__ *)__dst)[0] = __temp;
			return (__BYTE_TYPE__ *)__dst + 1;
		}	break;

		case 2: {
			__UINT16_TYPE__ __temp;
			__temp = ((__UINT16_TYPE__ const *)__src)[(__n_bytes >> 1)-1];
			__dst = __libc_slow_mempmovel(__dst, __src, __n_bytes >> 2);
			((__UINT16_TYPE__ *)__dst)[0] = __temp;
			return (__BYTE_TYPE__ *)__dst + 2;
		}
		default: break;
		}
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_bytes & 3))
			return __libc_slow_mempmovel(__dst, __src, __n_bytes >> 2);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmovel */
#if defined(__CRT_HAVE_mempmovew)
#ifndef __OPTIMIZE_SIZE__
		if (!(__n_bytes & 1))
			return __libc_slow_mempmovew(__dst, __src, __n_bytes >> 1);
		{
			__UINT8_TYPE__ __temp = ((__UINT8_TYPE__ const *)__src)[__n_bytes-1];
			__dst = __libc_slow_mempmovew(__dst, __src, __n_bytes >> 1);
			((__UINT8_TYPE__ *)__dst)[0] = __temp;
		}
		return (__BYTE_TYPE__ *)__dst + 1;
#else /* !__OPTIMIZE_SIZE__ */
		if (!(__n_bytes & 1))
			return __libc_slow_mempmovew(__dst, __src, __n_bytes >> 1);
#endif /* __OPTIMIZE_SIZE__ */
#endif /* __CRT_HAVE_mempmovew */
	}
	return __libc_slow_mempmove(__dst, __src, __n_bytes);
}
#endif /* !__fast_mempmove_defined */

#ifndef __fast_mempatw_defined
#define __fast_mempatw_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(mempatw))(void *__restrict __dst,
                                                    __UINT16_TYPE__ __pattern,
                                                    __SIZE_TYPE__ __n_bytes) {
	if (__builtin_constant_p(__pattern)) {
		/* Optimization: Check for same-byte patterns, which allow this to be turned into a memset() call */
		if ((__pattern & __UINT8_C(0xff)) == ((__pattern >> 8) & __UINT8_C(0xff)))
			return __LIBC_FAST_NAME(memset)(__dst, __pattern & __UINT8_C(0xff), __n_bytes);
	}
	if (__builtin_constant_p(__n_bytes)) {
		if (__n_bytes == 0)
			return __dst;
	}
	return __libc_slow_mempatw(__dst, __pattern, __n_bytes);
}
#endif /* !__fast_mempatw_defined */

#ifndef __fast_mempatl_defined
#define __fast_mempatl_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(mempatl))(void *__restrict __dst,
                                                    __UINT32_TYPE__ __pattern,
                                                    __SIZE_TYPE__ __n_bytes) {
	if (__builtin_constant_p(__pattern)) {
		/* Optimization: Check for same-byte patterns, which allow this to be turned into a memset() call */
		if ((__pattern & __UINT8_C(0xff)) == ((__pattern >> 8) & __UINT8_C(0xff)) &&
		    (__pattern & __UINT8_C(0xff)) == ((__pattern >> 16) & __UINT8_C(0xff)) &&
		    (__pattern & __UINT8_C(0xff)) == ((__pattern >> 24) & __UINT8_C(0xff)))
			return __LIBC_FAST_NAME(memset)(__dst, __pattern & __UINT8_C(0xff), __n_bytes);
	}
	if (__builtin_constant_p(__n_bytes)) {
		if (__n_bytes == 0)
			return __dst;
	}
	return __libc_slow_mempatl(__dst, __pattern, __n_bytes);
}
#endif /* !__fast_mempatw_defined */

#ifdef __UINT64_TYPE__
#ifndef __fast_mempatq_defined
#define __fast_mempatq_defined 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_FAST_NAME(mempatq))(void *__restrict __dst,
                                                    __UINT64_TYPE__ __pattern,
                                                    __SIZE_TYPE__ __n_bytes) {
	if (__builtin_constant_p(__pattern)) {
		/* Optimization: Check for same-byte patterns, which allow this to be turned into a memset() call */
		if ((__pattern & __UINT8_C(0xff)) == ((__pattern >> 8) & __UINT8_C(0xff)) &&
		    (__pattern & __UINT8_C(0xff)) == ((__pattern >> 16) & __UINT8_C(0xff)) &&
		    (__pattern & __UINT8_C(0xff)) == ((__pattern >> 24) & __UINT8_C(0xff)) &&
		    (__pattern & __UINT8_C(0xff)) == ((__pattern >> 32) & __UINT8_C(0xff)) &&
		    (__pattern & __UINT8_C(0xff)) == ((__pattern >> 40) & __UINT8_C(0xff)) &&
		    (__pattern & __UINT8_C(0xff)) == ((__pattern >> 48) & __UINT8_C(0xff)) &&
		    (__pattern & __UINT8_C(0xff)) == ((__pattern >> 56) & __UINT8_C(0xff)))
			return __LIBC_FAST_NAME(memset)(__dst, __pattern & __UINT8_C(0xff), __n_bytes);
	}
	if (__builtin_constant_p(__n_bytes)) {
		if (__n_bytes == 0)
			return __dst;
	}
	return __libc_slow_mempatq(__dst, __pattern, __n_bytes);
}
#endif /* !__fast_mempatw_defined */
#endif /* __UINT64_TYPE__ */

__NAMESPACE_FAST_END
__SYSDECL_END
#endif /* !__NO_ATTR_FORCEINLINE && __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */

#endif /* !_OPTIMIZED_STRING_H */
