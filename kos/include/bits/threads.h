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
#ifndef _BITS_THREADS_H
#define _BITS_THREADS_H 1

#include <__stdinc.h>
#include <__crt.h>

#include <hybrid/typecore.h>
#include <bits/pthreadtypesizes.h>

__SYSDECL_BEGIN

#ifdef __CC__

typedef __TYPEFOR_INTIB(__SIZEOF_PTHREAD_KEY_T) __tss_t;
typedef __TYPEFOR_UINTIB(__SIZEOF_PTHREAD_T) __thrd_t;
typedef void (__LIBCCALL *__tss_dtor_t)(void *__arg);
typedef int (__LIBCCALL *__thrd_start_t)(void *__obj);
typedef void (__LIBCCALL *__once_func_t)(void);

typedef struct {
	__TYPEFOR_INTIB(__SIZEOF_PTHREAD_ONCE_T) __data;
} __once_flag;
#define __ONCE_FLAG_INIT { 0 }

typedef union {
	__BYTE_TYPE__ __size[__SIZEOF_PTHREAD_MUTEX_T];
	__INTPTR_TYPE__ __align;
} __mtx_t;

typedef union {
	__BYTE_TYPE__ __size[__SIZEOF_PTHREAD_COND_T];
	__INT64_TYPE__ __align;
} __cnd_t;

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_BITS_THREADS_H */
