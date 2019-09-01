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
#ifndef _BITS_SEMAPHORE_H
#define _BITS_SEMAPHORE_H 1

#include <__stdinc.h>

#ifndef __SIZEOF_SEM_T
#include <hybrid/typecore.h>
#if __SIZEOF_POINTER__ == 4
#define __SIZEOF_SEM_T   16
#elif __SIZEOF_POINTER__ == 8
#define __SIZEOF_SEM_T   32
#else
#define __SIZEOF_SEM_T   (__SIZEOF_POINTER__ * 4)
#endif
#endif /* !__SIZEOF_SEM_T */

__SYSDECL_BEGIN

/* Value returned by `sem_open' upon failure. */
#define SEM_FAILED      (__CCAST(sem_t *)0)

#ifdef __CC__
#ifndef __sem_t_defined
#define __sem_t_defined 1
typedef union {
	__BYTE_TYPE__ __data[__SIZEOF_SEM_T];
	void         *__align;
} sem_t;
#endif /* !__sem_t_defined */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_BITS_SEMAPHORE_H */
