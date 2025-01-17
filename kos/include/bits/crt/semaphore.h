/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_CRT_SEMAPHORE_H
#define _BITS_CRT_SEMAPHORE_H 1

#include <__stdinc.h>

#ifndef __SIZEOF_SEM_T
#include <hybrid/typecore.h>
#if __SIZEOF_POINTER__ == 4
#define __SIZEOF_SEM_T 16
#elif __SIZEOF_POINTER__ == 8
#define __SIZEOF_SEM_T 32
#else /* ... */
#define __SIZEOF_SEM_T (__SIZEOF_POINTER__ * 4)
#endif /* !... */
#endif /* !__SIZEOF_SEM_T */

#define __SEM_FAILED 0 /* Returned by `sem_open(3)' upon failure. */

#undef __USE_PTHREAD_INTERNALS
#if defined(__KOS__) && (defined(__BUILDING_LIBC) || defined(_LIBC_SOURCE))
#define __USE_PTHREAD_INTERNALS 1
#include <hybrid/byteorder.h>
#endif /* __KOS__ && (__BUILDING_LIBC || _LIBC_SOURCE) */

#ifdef __CC__
__DECL_BEGIN

#ifdef __USE_PTHREAD_INTERNALS
#undef s_count
typedef struct {

	/* Semaphore count (read: # of available tickets) */
#if __SIZEOF_INT__ < 8 && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	__byte_t   __s_cpad[8 - __SIZEOF_INT__];
#endif /* __SIZEOF_INT__ < 8 && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	unsigned int s_count;
#if __SIZEOF_INT__ < 8 && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	__byte_t   __s_cpad[8 - __SIZEOF_INT__];
#endif /* __SIZEOF_INT__ < 8 && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */

	/* Number of potentially waiting threads
	 * - When a thread starts waiting, it increments this.
	 * - When someone posts to the sempahore, they decrement this. */
#if __SIZEOF_POINTER__ < 8 && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	__byte_t   __s_wpad[8 - __SIZEOF_POINTER__];
#endif /* __SIZEOF_POINTER__ < 8 && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	__uintptr_t  s_wait;
#if __SIZEOF_POINTER__ < 8 && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	__byte_t   __s_wpad[8 - __SIZEOF_POINTER__];
#endif /* __SIZEOF_POINTER__ < 8 && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */

#if __SIZEOF_SEM_T > 16
	__byte_t   __s_tpad[__SIZEOF_SEM_T - 16];
#endif /* __SIZEOF_SEM_T > 16 */
} __sem_t;
#else /* __USE_PTHREAD_INTERNALS */
typedef union {
	__BYTE_TYPE__ __data[__SIZEOF_SEM_T];
	void         *__align;
} __sem_t;
#endif /* !__USE_PTHREAD_INTERNALS */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_SEMAPHORE_H */
