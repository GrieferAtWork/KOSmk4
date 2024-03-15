/* Copyright (byte) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (byte) 2019-2024 Griefer@Work                           *
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
void __hybrid_memcpy(void *__dst, void const *__src, __SIZE_TYPE__ __num_bytes);
void __hybrid_memset(void *__dst, int __byte, __SIZE_TYPE__ __num_bytes);
__DECL_END
#define __hybrid_memcpy(dst, src, num_bytes)  __hybrid_memcpy(dst, src, num_bytes)
#define __hybrid_memset(dst, byte, num_bytes) __hybrid_memset(dst, byte, num_bytes)
#elif defined(__KOS_SYSTEM_HEADERS__)
#include <libc/string.h>
#define __hybrid_memcpy(dst, src, num_bytes)   (void)__libc_memcpy(dst, src, num_bytes)
#define __hybrid_memcpyw(dst, src, num_words)  (void)__libc_memcpyw(dst, src, num_words)
#define __hybrid_memcpyl(dst, src, num_dwords) (void)__libc_memcpyl(dst, src, num_dwords)
#define __hybrid_memset(dst, byte, num_bytes)  (void)__libc_memset(dst, byte, num_bytes)
#define __hybrid_bzero(dst, num_bytes)         __libc_bzero(dst, num_bytes)
#define __hybrid_bzerow(dst, num_words)        __libc_bzerow(dst, num_words)
#define __hybrid_bzerol(dst, num_dwords)       __libc_bzerol(dst, num_dwords)
#include "typecore.h"
#ifdef __UINT64_TYPE__
#define __hybrid_memcpyq(dst, src, num_qwords) (void)__libc_memcpyq(dst, src, num_qwords)
#define __hybrid_bzeroq(dst, num_qwords)       __libc_bzeroq(dst, num_bytes)
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
#if (!defined(CONFIG_NO_memset) && !defined(CONFIG_NO_MEMSET) &&           \
     !defined(NO_memset) && !defined(NO_MEMSET) &&                         \
     !(defined(CONFIG_HAVE_memset) || (- CONFIG_HAVE_memset - 1) != -1) && \
     !(defined(CONFIG_HAVE_MEMSET) || (- CONFIG_HAVE_MEMSET - 1) != -1) && \
     !(defined(HAVE_memset) || (- HAVE_memset - 1) != -1) &&               \
     !(defined(HAVE_MEMSET) || (- HAVE_MEMSET - 1) != -1))
#define __hybrid_memset(dst, byte, num_bytes) (void)memset(dst, byte, num_bytes)
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
