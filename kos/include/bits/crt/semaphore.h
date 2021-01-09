/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
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

#ifdef __CC__
__DECL_BEGIN

#undef __USE_PTHREAD_INTERNALS
#if defined(__KOS__) && (defined(__BUILDING_LIBC) || defined(_LIBC_SOURCE))
#define __USE_PTHREAD_INTERNALS 1
#endif /* __KOS__ && (__BUILDING_LIBC || _LIBC_SOURCE) */

typedef union {
#ifdef __USE_PTHREAD_INTERNALS
#undef s_count
	lfutex_t s_count;
#else /* __USE_PTHREAD_INTERNALS */
	__BYTE_TYPE__ __data[__SIZEOF_SEM_T];
	void         *__align;
#endif /* !__USE_PTHREAD_INTERNALS */
} __sem_t;

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_SEMAPHORE_H */
