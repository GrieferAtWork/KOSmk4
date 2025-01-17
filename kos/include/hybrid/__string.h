/* Copyright (byte) 2019-2025 Griefer@Work                                    *
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
 *    Portions Copyright (byte) 2019-2025 Griefer@Work                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID___MEMSET_H
#define __GUARD_HYBRID___MEMSET_H 1

#include "../__stdinc.h"

#ifdef __CC__
#ifdef __INTELLISENSE__
#include "typecore.h"
__DECL_BEGIN
void __hybrid_memmove(void *__dst, void const *__src, __SIZE_TYPE__ __num_bytes);
void __hybrid_memmoveup(void *__dst, void const *__src, __SIZE_TYPE__ __num_bytes);
void __hybrid_memmovedown(void *__dst, void const *__src, __SIZE_TYPE__ __num_bytes);
void __hybrid_memcpy(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __num_bytes);
void __hybrid_memset(void *__dst, int __byte, __SIZE_TYPE__ __num_bytes);
int __hybrid_bcmp(void const *__lhs, void const *__rhs, __SIZE_TYPE__ __num_bytes);
__DECL_END
#define __hybrid_memmove(dst, src, num_bytes)     __hybrid_memmove(dst, src, num_bytes)
#define __hybrid_memmoveup(dst, src, num_bytes)   __hybrid_memmoveup(dst, src, num_bytes)
#define __hybrid_memmovedown(dst, src, num_bytes) __hybrid_memmovedown(dst, src, num_bytes)
#define __hybrid_memcpy(dst, src, num_bytes)      __hybrid_memcpy(dst, src, num_bytes)
#define __hybrid_memset(dst, byte, num_bytes)     __hybrid_memset(dst, byte, num_bytes)
#define __hybrid_bcmp(lhs, rhs, num_bytes)        __hybrid_bcmp(lhs, rhs, num_bytes)
#elif defined(__KOS_SYSTEM_HEADERS__)
#include <libc/string.h>
#define __hybrid_memcpy(dst, src, num_bytes)        (void)__libc_memcpy(dst, src, num_bytes)
#define __hybrid_memcpyw(dst, src, num_words)       (void)__libc_memcpyw((__UINT16_TYPE__ *)(dst), (__UINT16_TYPE__ const *)(src), num_words)
#define __hybrid_memcpyl(dst, src, num_dwords)      (void)__libc_memcpyl((__UINT32_TYPE__ *)(dst), (__UINT32_TYPE__ const *)(src), num_dwords)
#define __hybrid_memmove(dst, src, num_bytes)       (void)__libc_memmove(dst, src, num_bytes)
#define __hybrid_memmovew(dst, src, num_words)      (void)__libc_memmovew((__UINT16_TYPE__ *)(dst), (__UINT16_TYPE__ const *)(src), num_words)
#define __hybrid_memmovel(dst, src, num_dwords)     (void)__libc_memmovel((__UINT32_TYPE__ *)(dst), (__UINT32_TYPE__ const *)(src), num_dwords)
#define __hybrid_memmoveup(dst, src, num_bytes)     (void)__libc_memmoveup(dst, src, num_bytes)
#define __hybrid_memmoveupw(dst, src, num_words)    (void)__libc_memmoveupw((__UINT16_TYPE__ *)(dst), (__UINT16_TYPE__ const *)(src), num_words)
#define __hybrid_memmoveupl(dst, src, num_dwords)   (void)__libc_memmoveupl((__UINT32_TYPE__ *)(dst), (__UINT32_TYPE__ const *)(src), num_dwords)
#define __hybrid_memmovedown(dst, src, num_bytes)   (void)__libc_memmovedown(dst, src, num_bytes)
#define __hybrid_memmovedownw(dst, src, num_words)  (void)__libc_memmovedownw((__UINT16_TYPE__ *)(dst), (__UINT16_TYPE__ const *)(src), num_words)
#define __hybrid_memmovedownl(dst, src, num_dwords) (void)__libc_memmovedownl((__UINT32_TYPE__ *)(dst), (__UINT32_TYPE__ const *)(src), num_dwords)
#define __hybrid_memset(dst, byte, num_bytes)       (void)__libc_memset(dst, byte, num_bytes)
#define __hybrid_bzero(dst, num_bytes)              __libc_bzero(dst, num_bytes)
#define __hybrid_bzerow(dst, num_words)             __libc_bzerow((__UINT16_TYPE__ *)(dst), num_words)
#define __hybrid_bzerol(dst, num_dwords)            __libc_bzerol((__UINT32_TYPE__ *)(dst), num_dwords)
#define __hybrid_bcmp(lhs, rhs, num_bytes)          __libc_bcmp(lhs, rhs, num_bytes)
#include "typecore.h"
#ifdef __UINT64_TYPE__
#define __hybrid_memcpyq(dst, src, num_qwords)      (void)__libc_memcpyq((__UINT64_TYPE__ *)(dst), (__UINT64_TYPE__ const *)(src), num_qwords)
#define __hybrid_memmoveq(dst, src, num_qwords)     (void)__libc_memmoveq((__UINT64_TYPE__ *)(dst), (__UINT64_TYPE__ const *)(src), num_qwords)
#define __hybrid_memmoveupq(dst, src, num_qwords)   (void)__libc_memmoveupq((__UINT64_TYPE__ *)(dst), (__UINT64_TYPE__ const *)(src), num_qwords)
#define __hybrid_memmovedownq(dst, src, num_qwords) (void)__libc_memmovedownq((__UINT64_TYPE__ *)(dst), (__UINT64_TYPE__ const *)(src), num_qwords)
#define __hybrid_bzeroq(dst, num_qwords)            __libc_bzeroq((__UINT64_TYPE__ *)(dst), num_bytes)
#endif /* __UINT64_TYPE__ */
#else /* __KOS_SYSTEM_HEADERS__ */

#if (__has_include(<string.h>) ||                                                              \
     (defined(__NO_has_include) &&                                                             \
      !(defined(__STDC_HOSTED__) && (__STDC_HOSTED__ + 0) == 0) &&                             \
      !defined(CONFIG_NO_STRING_H) &&                                                          \
      !(defined(CONFIG_HAVE_STRING_H) && (-CONFIG_HAVE_STRING_H - 1) != -1) &&                 \
      !defined(CONFIG_NO_INCLUDE_STRING_H) &&                                                  \
      !(defined(CONFIG_HAVE_INCLUDE_STRING_H) && (-CONFIG_HAVE_INCLUDE_STRING_H - 1) != -1) && \
      !defined(NO_STRING_H) && !defined(NO_HAVE_STRING_H) &&                                   \
      !(defined(HAVE_STRING_H) && (-HAVE_STRING_H - 1) != -1) &&                               \
      !defined(NO_INCLUDE_STRING_H) && !defined(NO_HAVE_INCLUDE_STRING_H) &&                   \
      !(defined(HAVE_INCLUDE_STRING_H) && (-HAVE_INCLUDE_STRING_H - 1) != -1)))
#include <string.h>
#if (!defined(CONFIG_NO_memcpy) && !defined(CONFIG_NO_MEMCPY) &&           \
     !defined(NO_memcpy) && !defined(NO_MEMCPY) &&                         \
     !(defined(CONFIG_HAVE_memcpy) || (- CONFIG_HAVE_memcpy - 1) != -1) && \
     !(defined(CONFIG_HAVE_MEMCPY) || (- CONFIG_HAVE_MEMCPY - 1) != -1) && \
     !(defined(HAVE_memcpy) || (- HAVE_memcpy - 1) != -1) &&               \
     !(defined(HAVE_MEMCPY) || (- HAVE_MEMCPY - 1) != -1))
#define __hybrid_memcpy(dst, src, num_bytes) (void)memcpy(dst, src, num_bytes)
#endif /* ... */
#if (!defined(CONFIG_NO_memmove) && !defined(CONFIG_NO_MEMMOVE) &&           \
     !defined(NO_memmove) && !defined(NO_MEMMOVE) &&                         \
     !(defined(CONFIG_HAVE_memmove) || (- CONFIG_HAVE_memmove - 1) != -1) && \
     !(defined(CONFIG_HAVE_MEMMOVE) || (- CONFIG_HAVE_MEMMOVE - 1) != -1) && \
     !(defined(HAVE_memmove) || (- HAVE_memmove - 1) != -1) &&               \
     !(defined(HAVE_MEMMOVE) || (- HAVE_MEMMOVE - 1) != -1))
#define __hybrid_memmove(dst, src, num_bytes) (void)memmove(dst, src, num_bytes)
#endif /* ... */
#if (!defined(CONFIG_NO_memset) && !defined(CONFIG_NO_MEMSET) &&           \
     !defined(NO_memset) && !defined(NO_MEMSET) &&                         \
     !(defined(CONFIG_HAVE_memset) || (- CONFIG_HAVE_memset - 1) != -1) && \
     !(defined(CONFIG_HAVE_MEMSET) || (- CONFIG_HAVE_MEMSET - 1) != -1) && \
     !(defined(HAVE_memset) || (- HAVE_memset - 1) != -1) &&               \
     !(defined(HAVE_MEMSET) || (- HAVE_MEMSET - 1) != -1))
#define __hybrid_memset(dst, byte, num_bytes) (void)memset(dst, byte, num_bytes)
#endif /* ... */
#if defined(CONFIG_HAVE_bcmp)
#define __hybrid_bcmp(lhs, rhs, num_bytes) bcmp(lhs, rhs, num_bytes)
#elif (!defined(CONFIG_NO_memcmp) && !defined(CONFIG_NO_MEMCMP) &&           \
     !defined(NO_memcmp) && !defined(NO_MEMCMP) &&                         \
     !(defined(CONFIG_HAVE_memcmp) || (- CONFIG_HAVE_memcmp - 1) != -1) && \
     !(defined(CONFIG_HAVE_MEMCMP) || (- CONFIG_HAVE_MEMCMP - 1) != -1) && \
     !(defined(HAVE_memcmp) || (- HAVE_memcmp - 1) != -1) &&               \
     !(defined(HAVE_MEMCMP) || (- HAVE_MEMCMP - 1) != -1))
#define __hybrid_bcmp(lhs, rhs, num_bytes) memcmp(lhs, rhs, num_bytes)
#endif /* ... */
#endif /* __has_include(<string.h>) || (__NO_has_include && !...) */

#if !defined(__hybrid_memcpyq) && defined(_MSC_VER)
#include "host.h"
#ifdef __x86_64__
__DECL_BEGIN
extern void __movsq(unsigned long long *, unsigned long long const *, unsigned __int64);
#define __hybrid_memcpyq(dst, src, num_qwords)               \
	__movsq((unsigned long long *)(void *)(dst),             \
	        (unsigned long long const *)(void const *)(src), \
	        (unsigned __int64)(num_qwords))
#pragma intrinsic(__movsq)
__DECL_END
#endif /* __x86_64__ */
#endif /* !__hybrid_memcpyq && _MSC_VER */

#if !defined(__hybrid_memcpyl) && defined(_MSC_VER)
#include "host.h"
#if defined(__i386__) || defined(__x86_64__)
__DECL_BEGIN
#ifdef __x86_64__
extern void __movsd(unsigned long *, unsigned long const *, unsigned __int64);
#define __hybrid_memcpyl(dst, src, num_dwords)          \
	__movsd((unsigned long *)(void *)(dst),             \
	        (unsigned long const *)(void const *)(src), \
	        (unsigned __int64)(num_dwords))
#else /* __x86_64__ */
extern void __movsd(unsigned long *, unsigned long const *, unsigned int);
#define __hybrid_memcpyl(dst, src, num_dwords)          \
	__movsd((unsigned long *)(void *)(dst),             \
	        (unsigned long const *)(void const *)(src), \
	        (unsigned int)(num_dwords))
#endif /* !__x86_64__ */
#pragma intrinsic(__movsd)
__DECL_END
#endif /* __i386__ || __x86_64__ */
#endif /* !__hybrid_memcpyl && _MSC_VER */

#if !defined(__hybrid_memcpyw) && defined(_MSC_VER)
#include "host.h"
#if defined(__i386__) || defined(__x86_64__)
__DECL_BEGIN
#ifdef __x86_64__
extern void __movsw(unsigned short *, unsigned short const *, unsigned __int64);
#define __hybrid_memcpyw(dst, src, num_words)            \
	__movsw((unsigned short *)(void *)(dst),             \
	        (unsigned short const *)(void const *)(src), \
	        (unsigned __int64)(num_words))
#else /* __x86_64__ */
extern void __movsw(unsigned short *, unsigned short const *, unsigned int);
#define __hybrid_memcpyw(dst, src, num_words)            \
	__movsw((unsigned short *)(void *)(dst),             \
	        (unsigned short const *)(void const *)(src), \
	        (unsigned int)(num_words))
#endif /* !__x86_64__ */
#pragma intrinsic(__movsw)
__DECL_END
#endif /* __i386__ || __x86_64__ */
#endif /* !__hybrid_memcpyw && _MSC_VER */

#ifndef __hybrid_bcmp
#include "typecore.h"
__DECL_BEGIN
#define __hybrid_bcmp __hybrid_bcmp
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__hybrid_bcmp(void const *__lhs, void const *__rhs, size_t __num_bytes) {
	__BYTE_TYPE__ const *__p1 = (__BYTE_TYPE__ const *)__lhs;
	__BYTE_TYPE__ const *__p2 = (__BYTE_TYPE__ const *)__rhs;
	while (__num_bytes--) {
		if (*__p1 != *__p2)
			return 1;
		++__p1;
		++__p2;
	}
	return 0;
}
__DECL_END
#endif /* !__hybrid_bcmp */
#endif /* !__KOS_SYSTEM_HEADERS__ */



#if defined(__hybrid_memcpyw) && defined(__hybrid_memcpyl) && defined(__hybrid_memcpyq)
#define __hybrid_memcpyc(dst, src, elem_count, elem_size) \
	((elem_size) == 2                                     \
	 ? (void *)__hybrid_memcpyw(dst, src, elem_count)     \
	 : (elem_size) == 4                                   \
	   ? (void *)__hybrid_memcpyl(dst, src, elem_count)   \
	   : (elem_size) == 8                                 \
	     ? (void *)__hybrid_memcpyq(dst, src, elem_count) \
	     : __hybrid_memcpy(dst, src, (__SIZE_TYPE__)(elem_count) * (__SIZE_TYPE__)(elem_size)))
#elif defined(__hybrid_memcpyw) && defined(__hybrid_memcpyl)
#define __hybrid_memcpyc(dst, src, elem_count, elem_size) \
	((elem_size) == 2                                     \
	 ? (void *)__hybrid_memcpyw(dst, src, elem_count)     \
	 : (elem_size) == 4                                   \
	   ? (void *)__hybrid_memcpyl(dst, src, elem_count)   \
	   : __hybrid_memcpy(dst, src, (__SIZE_TYPE__)(elem_count) * (__SIZE_TYPE__)(elem_size)))
#elif defined(__hybrid_memcpyw) && defined(__hybrid_memcpyq)
#define __hybrid_memcpyc(dst, src, elem_count, elem_size) \
	((elem_size) == 2                                     \
	 ? (void *)__hybrid_memcpyw(dst, src, elem_count)     \
	 : (elem_size) == 8                                   \
	   ? (void *)__hybrid_memcpyq(dst, src, elem_count)   \
	   : __hybrid_memcpy(dst, src, (__SIZE_TYPE__)(elem_count) * (__SIZE_TYPE__)(elem_size)))
#elif defined(__hybrid_memcpyl) && defined(__hybrid_memcpyq)
#define __hybrid_memcpyc(dst, src, elem_count, elem_size) \
	((elem_size) == 4                                     \
	 ? (void *)__hybrid_memcpyl(dst, src, elem_count)     \
	 : (elem_size) == 8                                   \
	   ? (void *)__hybrid_memcpyq(dst, src, elem_count)   \
	   : __hybrid_memcpy(dst, src, (__SIZE_TYPE__)(elem_count) * (__SIZE_TYPE__)(elem_size)))
#elif defined(__hybrid_memcpyq)
#define __hybrid_memcpyc(dst, src, elem_count, elem_size) \
	((elem_size) == 8                                     \
	 ? (void *)__hybrid_memcpyq(dst, src, elem_count)     \
	 : __hybrid_memcpy(dst, src, (__SIZE_TYPE__)(elem_count) * (__SIZE_TYPE__)(elem_size)))
#elif defined(__hybrid_memcpyl)
#define __hybrid_memcpyc(dst, src, elem_count, elem_size) \
	((elem_size) == 4                                     \
	 ? (void *)__hybrid_memcpyl(dst, src, elem_count)     \
	 : __hybrid_memcpy(dst, src, (__SIZE_TYPE__)(elem_count) * (__SIZE_TYPE__)(elem_size)))
#elif defined(__hybrid_memcpyw)
#define __hybrid_memcpyc(dst, src, elem_count, elem_size) \
	((elem_size) == 2                                     \
	 ? (void *)__hybrid_memcpyw(dst, src, elem_count)     \
	 : __hybrid_memcpy(dst, src, (__SIZE_TYPE__)(elem_count) * (__SIZE_TYPE__)(elem_size)))
#else /* ... */
#define __hybrid_memcpyc(dst, src, elem_count, elem_size) \
	__hybrid_memcpy(dst, src, (__SIZE_TYPE__)(elem_count) * (__SIZE_TYPE__)(elem_size))
#endif /* !... */



#ifndef __hybrid_memcpyq
#ifdef __hybrid_memcpyl
#define __hybrid_memcpyq(dst, src, num_qwords) __hybrid_memcpyl(dst, src, (__SIZE_TYPE__)(num_qwords) << 1)
#elif defined(__hybrid_memcpyw)
#define __hybrid_memcpyq(dst, src, num_qwords) __hybrid_memcpyw(dst, src, (__SIZE_TYPE__)(num_qwords) << 2)
#elif defined(__hybrid_memcpy)
#define __hybrid_memcpyq(dst, src, num_qwords) __hybrid_memcpy(dst, src, (__SIZE_TYPE__)(num_qwords) << 3)
#else /* ... */
#include "typecore.h"
#if (__SIZEOF_BUSINT__ >= 8) && defined(__UINT64_TYPE__)
#define __hybrid_memcpyq(dst, src, num_qwords)                                         \
	do {                                                                               \
		__UINT64_TYPE__ *__hmc_d       = (__UINT64_TYPE__ *)(void *)(dst);             \
		__UINT64_TYPE__ const *__hmc_s = (__UINT64_TYPE__ const *)(void const *)(src); \
		__SIZE_TYPE__ __hmc_n          = (__SIZE_TYPE__)(num_qwords);                  \
		while (__hmc_n) {                                                              \
			*__hmc_d = *__hmc_s;                                                       \
			--__hmc_n;                                                                 \
			++__hmc_s;                                                                 \
			++__hmc_d;                                                                 \
		}                                                                              \
	}	__WHILE0
#else /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */
#define __hybrid_memcpyq(dst, src, num_qwords)                                         \
	do {                                                                               \
		__UINT32_TYPE__ *__hmc_d       = (__UINT32_TYPE__ *)(void *)(dst);             \
		__UINT32_TYPE__ const *__hmc_s = (__UINT32_TYPE__ const *)(void const *)(src); \
		__SIZE_TYPE__ __hmc_n          = (__SIZE_TYPE__)(num_qwords) << 1;             \
		while (__hmc_n) {                                                              \
			*__hmc_d = *__hmc_s;                                                       \
			--__hmc_n;                                                                 \
			++__hmc_s;                                                                 \
			++__hmc_d;                                                                 \
		}                                                                              \
	}	__WHILE0
#endif /* __SIZEOF_BUSINT__ < 8 || !__UINT64_TYPE__ */
#endif /* !... */
#endif /* !__hybrid_memcpyq */

#ifndef __hybrid_memcpyl
#ifdef __hybrid_memcpyw
#define __hybrid_memcpyl(dst, src, num_dwords) __hybrid_memcpyw(dst, src, (num_dwords) << 1)
#elif defined(__hybrid_memcpy)
#define __hybrid_memcpyl(dst, src, num_dwords) __hybrid_memcpy(dst, src, (num_dwords) << 2)
#else /* ... */
#include "typecore.h"
#define __hybrid_memcpyl(dst, src, num_dwords)                                         \
	do {                                                                               \
		__UINT32_TYPE__ *__hmc_d       = (__UINT32_TYPE__ *)(void *)(dst);             \
		__UINT32_TYPE__ const *__hmc_s = (__UINT32_TYPE__ const *)(void const *)(src); \
		__SIZE_TYPE__ __hmc_n          = (__SIZE_TYPE__)(num_dwords);                  \
		while (__hmc_n) {                                                              \
			*__hmc_d = *__hmc_s;                                                       \
			--__hmc_n;                                                                 \
			++__hmc_s;                                                                 \
			++__hmc_d;                                                                 \
		}                                                                              \
	}	__WHILE0
#endif /* !... */
#endif /* !__hybrid_memcpyl */

#ifndef __hybrid_memcpyw
#ifdef __hybrid_memcpy
#define __hybrid_memcpyw(dst, src, num_words) __hybrid_memcpy(dst, src, (num_words) << 1)
#else /* __hybrid_memcpy */
#include "typecore.h"
#define __hybrid_memcpyw(dst, src, num_words)                                          \
	do {                                                                               \
		__UINT16_TYPE__ *__hmc_d       = (__UINT16_TYPE__ *)(void *)(dst);             \
		__UINT16_TYPE__ const *__hmc_s = (__UINT16_TYPE__ const *)(void const *)(src); \
		__SIZE_TYPE__ __hmc_n          = (__SIZE_TYPE__)(num_words);                   \
		while (__hmc_n) {                                                              \
			*__hmc_d = *__hmc_s;                                                       \
			--__hmc_n;                                                                 \
			++__hmc_s;                                                                 \
			++__hmc_d;                                                                 \
		}                                                                              \
	}	__WHILE0
#endif /* !__hybrid_memcpy */
#endif /* !__hybrid_memcpyw */

#ifndef __hybrid_memcpy
#include "typecore.h"
#define __hybrid_memcpy(dst, src, num_bytes)                                       \
	do {                                                                           \
		__BYTE_TYPE__ *__hmc_d       = (__BYTE_TYPE__ *)(void *)(dst);             \
		__BYTE_TYPE__ const *__hmc_s = (__BYTE_TYPE__ const *)(void const *)(src); \
		__SIZE_TYPE__ __hmc_n        = (__SIZE_TYPE__)(num_bytes);                 \
		while (__hmc_n) {                                                          \
			*__hmc_d = *__hmc_s;                                                   \
			--__hmc_n;                                                             \
			++__hmc_s;                                                             \
			++__hmc_d;                                                             \
		}                                                                          \
	}	__WHILE0
#endif /* !__hybrid_memcpy */

#ifndef __hybrid_memmoveup
#ifdef __hybrid_memmove
#define __hybrid_memmoveup(dst, src, num_bytes) __hybrid_memmove(dst, src, num_bytes)
#else /* __hybrid_memmove */
#include "typecore.h"
#define __hybrid_memmoveup(dst, src, num_bytes)                                     \
	do {                                                                            \
		__BYTE_TYPE__ *__hmmu_d       = (__BYTE_TYPE__ *)(void *)(dst);             \
		__BYTE_TYPE__ const *__hmmu_s = (__BYTE_TYPE__ const *)(void const *)(src); \
		__SIZE_TYPE__ __hmmu_n        = (__SIZE_TYPE__)(num_bytes);                 \
		while (__hmmu_n) {                                                          \
			--__hmmu_n;                                                             \
			__hmmu_d[__hmmu_n] = __hmmu_s[__hmmu_n];                                \
		}                                                                           \
	}	__WHILE0
#endif /* !__hybrid_memmove */
#endif /* !__hybrid_memmoveup */

#ifndef __hybrid_memmovedown
#ifdef __hybrid_memmove
#define __hybrid_memmovedown(dst, src, num_bytes) __hybrid_memmove(dst, src, num_bytes)
#else /* __hybrid_memmove */
#include "typecore.h"
#define __hybrid_memmovedown(dst, src, num_bytes)                                   \
	do {                                                                            \
		__BYTE_TYPE__ *__hmmd_d       = (__BYTE_TYPE__ *)(void *)(dst);             \
		__BYTE_TYPE__ const *__hmmd_s = (__BYTE_TYPE__ const *)(void const *)(src); \
		__SIZE_TYPE__ __hmmd_n        = (__SIZE_TYPE__)(num_bytes);                 \
		while (__hmmd_n) {                                                          \
			*__hmmd_d = *__hmmd_s;                                                  \
			--__hmmd_n;                                                             \
			++__hmmd_s;                                                             \
			++__hmmd_d;                                                             \
		}                                                                           \
	}	__WHILE0
#endif /* !__hybrid_memmove */
#endif /* !__hybrid_memmovedown */

#ifndef __hybrid_memmove
#include "typecore.h"
#define __hybrid_memmove(dst, src, num_bytes)                                      \
	do {                                                                           \
		__BYTE_TYPE__ *__hmm_d       = (__BYTE_TYPE__ *)(void *)(dst);             \
		__BYTE_TYPE__ const *__hmm_s = (__BYTE_TYPE__ const *)(void const *)(src); \
		__SIZE_TYPE__ __hmm_n        = (__SIZE_TYPE__)(num_bytes);                 \
		if (__hmm_d <= __hmm_s) {                                                  \
			while (__hmm_n) {                                                      \
				*__hmm_d = *__hmm_s;                                               \
				--__hmm_n;                                                         \
				++__hmm_s;                                                         \
				++__hmm_d;                                                         \
			}                                                                      \
		} else {                                                                   \
			while (__hmm_n) {                                                      \
				--__hmm_n;                                                         \
				__hmm_d[__hmm_n] = __hmm_s[__hmm_n];                               \
			}                                                                      \
		}                                                                          \
	}	__WHILE0
#endif /* !__hybrid_memmove */

#ifndef __hybrid_memmoveq
#ifdef __hybrid_memmovel
#define __hybrid_memmoveq(dst, src, num_qwords) __hybrid_memmovel(dst, src, (num_qwords) << 1)
#elif defined(__hybrid_memmovew)
#define __hybrid_memmoveq(dst, src, num_qwords) __hybrid_memmovew(dst, src, (num_qwords) << 2)
#else /* ... */
#define __hybrid_memmoveq(dst, src, num_qwords) __hybrid_memmove(dst, src, (num_qwords) << 3)
#endif /* !... */
#endif /* !__hybrid_memmoveq */

#ifndef __hybrid_memmovel
#ifdef __hybrid_memmovew
#define __hybrid_memmovel(dst, src, num_dwords) __hybrid_memmovew(dst, src, (num_dwords) << 1)
#else /* __hybrid_memmovew */
#define __hybrid_memmovel(dst, src, num_dwords) __hybrid_memmove(dst, src, (num_dwords) << 2)
#endif /* !__hybrid_memmovew */
#endif /* !__hybrid_memmovel */

#ifndef __hybrid_memmovew
#define __hybrid_memmovew(dst, src, num_words) __hybrid_memmove(dst, src, (num_words) << 1)
#endif /* !__hybrid_memmovew */

#ifndef __hybrid_memmoveupq
#ifdef __hybrid_memmoveupl
#define __hybrid_memmoveupq(dst, src, num_qwords) __hybrid_memmoveupl(dst, src, (num_qwords) << 1)
#elif defined(__hybrid_memmoveupw)
#define __hybrid_memmoveupq(dst, src, num_qwords) __hybrid_memmoveupw(dst, src, (num_qwords) << 2)
#else /* ... */
#define __hybrid_memmoveupq(dst, src, num_qwords) __hybrid_memmoveup(dst, src, (num_qwords) << 3)
#endif /* !... */
#endif /* !__hybrid_memmoveupq */

#ifndef __hybrid_memmoveupl
#ifdef __hybrid_memmoveupw
#define __hybrid_memmoveupl(dst, src, num_dwords) __hybrid_memmoveupw(dst, src, (num_dwords) << 1)
#else /* __hybrid_memmoveupw */
#define __hybrid_memmoveupl(dst, src, num_dwords) __hybrid_memmoveup(dst, src, (num_dwords) << 2)
#endif /* !__hybrid_memmoveupw */
#endif /* !__hybrid_memmoveupl */

#ifndef __hybrid_memmovedownw
#define __hybrid_memmovedownw(dst, src, num_words) __hybrid_memmovedown(dst, src, (num_words) << 1)
#endif /* !__hybrid_memmovedownw */

#ifndef __hybrid_memmovedownq
#ifdef __hybrid_memmovedownl
#define __hybrid_memmovedownq(dst, src, num_qwords) __hybrid_memmovedownl(dst, src, (num_qwords) << 1)
#elif defined(__hybrid_memmovedownw)
#define __hybrid_memmovedownq(dst, src, num_qwords) __hybrid_memmovedownw(dst, src, (num_qwords) << 2)
#else /* ... */
#define __hybrid_memmovedownq(dst, src, num_qwords) __hybrid_memmovedown(dst, src, (num_qwords) << 3)
#endif /* !... */
#endif /* !__hybrid_memmovedownq */

#ifndef __hybrid_memmovedownl
#ifdef __hybrid_memmovedownw
#define __hybrid_memmovedownl(dst, src, num_dwords) __hybrid_memmovedownw(dst, src, (num_dwords) << 1)
#else /* __hybrid_memmovedownw */
#define __hybrid_memmovedownl(dst, src, num_dwords) __hybrid_memmovedown(dst, src, (num_dwords) << 2)
#endif /* !__hybrid_memmovedownw */
#endif /* !__hybrid_memmovedownl */

#ifndef __hybrid_memmovedownw
#define __hybrid_memmovedownw(dst, src, num_words) __hybrid_memmovedown(dst, src, (num_words) << 1)
#endif /* !__hybrid_memmovedownw */

#ifndef __hybrid_memset
#include "typecore.h"
#define __hybrid_memset(dst, byte, num_bytes)                              \
	do {                                                                   \
		__BYTE_TYPE__ *__hms_p = (__BYTE_TYPE__ *)(void *)(dst);           \
		__BYTE_TYPE__ __hms_c  = (__BYTE_TYPE__)(unsigned int)(int)(byte); \
		__SIZE_TYPE__ __hms_n  = (__SIZE_TYPE__)(num_bytes);               \
		while (__hms_n) {                                                  \
			*__hms_p = __hms_c;                                            \
			--__hms_n;                                                     \
			++__hms_p;                                                     \
		}                                                                  \
	}	__WHILE0
#define __hybrid_bzero(dst, num_bytes)                       \
	do {                                                     \
		__BYTE_TYPE__ *__hbz_p = (__BYTE_TYPE__ *)(dst);     \
		__SIZE_TYPE__ __hbz_n  = (__SIZE_TYPE__)(num_bytes); \
		while (__hbz_n) {                                    \
			*__hbz_p = 0;                                    \
			--__hbz_n;                                       \
			++__hbz_p;                                       \
		}                                                    \
	}	__WHILE0
#endif /* !__hybrid_memset */

#ifndef __hybrid_bzeroq
#ifdef __hybrid_bzerol
#define __hybrid_bzeroq(dst, num_qwords) __hybrid_bzerol(dst, (__SIZE_TYPE__)(num_qwords) << 1)
#elif defined(__hybrid_bzerow)
#define __hybrid_bzeroq(dst, num_qwords) __hybrid_bzerow(dst, (__SIZE_TYPE__)(num_qwords) << 2)
#else /* ... */
#define __hybrid_bzeroq(dst, num_qwords) __hybrid_bzero(dst, (__SIZE_TYPE__)(num_qwords) << 3)
#endif /* !... */
#endif /* !__hybrid_bzeroq */

#ifndef __hybrid_bzerol
#ifdef __hybrid_bzerow
#define __hybrid_bzerol(dst, num_dwords) __hybrid_bzerow(dst, (__SIZE_TYPE__)(num_dwords) << 1)
#else /* __hybrid_bzerow */
#define __hybrid_bzerol(dst, num_dwords) __hybrid_bzero(dst, (__SIZE_TYPE__)(num_dwords) << 2)
#endif /* !__hybrid_bzerow */
#endif /* !__hybrid_bzerol */

#ifndef __hybrid_bzerow
#define __hybrid_bzerow(dst, num_words) __hybrid_bzero(dst, (__SIZE_TYPE__)(num_words) << 1)
#endif /* !__hybrid_bzerow */

#ifndef __hybrid_bzero
#define __hybrid_bzero(dst, num_bytes) __hybrid_memset(dst, 0, num_bytes)
#endif /* !__hybrid_bzero */
#endif /* __CC__ */

#endif /* !__GUARD_HYBRID___MEMSET_H */
