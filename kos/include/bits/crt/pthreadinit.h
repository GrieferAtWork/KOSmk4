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
#ifndef _BITS_CRT_PTHREADINIT_H
#define _BITS_CRT_PTHREADINIT_H 1

#include <__stdinc.h>

#include <hybrid/byteorder.h>
#include <hybrid/typecore.h>

#include <asm/crt/pthreadvalues.h>
#include <bits/crt/pthreadtypes.h>

#ifndef __PTHREAD_SPINS
#define __PTHREAD_SPINS { 0, 0 }
#endif /* !__PTHREAD_SPINS */

#ifndef __PTHREAD_RWLOCK_ELISION_EXTRA
#define __PTHREAD_RWLOCK_ELISION_EXTRA 0
#endif /* !__PTHREAD_RWLOCK_ELISION_EXTRA */

#ifndef __PTHREAD_RWLOCK_INT_FLAGS_SHARED
#include <bits/wordsize.h>
#if __WORDSIZE == 64
#define __PTHREAD_RWLOCK_INT_FLAGS_SHARED 1
#endif /* __WORDSIZE == 64 */
#endif /* !__PTHREAD_RWLOCK_INT_FLAGS_SHARED */

#ifdef __PTHREAD_MUTEX_HAVE_PREV
#define __PTHREAD_MUTEX_INITIALIZER            { { 0, 0, 0, 0, 0, __PTHREAD_SPINS, { 0, 0 } } }
#define __PTHREAD_RECURSIVE_MUTEX_INITIALIZER  { { 0, 0, 0, 0, __PTHREAD_MUTEX_RECURSIVE_NP, __PTHREAD_SPINS, { 0, 0 } } }
#define __PTHREAD_ERRORCHECK_MUTEX_INITIALIZER { { 0, 0, 0, 0, __PTHREAD_MUTEX_ERRORCHECK_NP, __PTHREAD_SPINS, { 0, 0 } } }
#define __PTHREAD_ADAPTIVE_MUTEX_INITIALIZER   { { 0, 0, 0, 0, __PTHREAD_MUTEX_ADAPTIVE_NP, __PTHREAD_SPINS, { 0, 0 } } }
#else /* __PTHREAD_MUTEX_HAVE_PREV */
#define __PTHREAD_MUTEX_INITIALIZER            { { 0, 0, 0, 0, 0, { __PTHREAD_SPINS } } }
#define __PTHREAD_RECURSIVE_MUTEX_INITIALIZER  { { 0, 0, 0, __PTHREAD_MUTEX_RECURSIVE, 0, { __PTHREAD_SPINS } } }
#define __PTHREAD_ERRORCHECK_MUTEX_INITIALIZER { { 0, 0, 0, __PTHREAD_MUTEX_ERRORCHECK, 0, { __PTHREAD_SPINS } } }
#define __PTHREAD_ADAPTIVE_MUTEX_INITIALIZER   { { 0, 0, 0, __PTHREAD_MUTEX_ADAPTIVE, 0, { __PTHREAD_SPINS } } }
#endif /* !__PTHREAD_MUTEX_HAVE_PREV */

#define __PTHREAD_RWLOCK_INITIALIZER { { 0, 0, 0, 0, 0, 0, 0, 0, __PTHREAD_RWLOCK_ELISION_EXTRA, 0, 0 } }
#ifdef __PTHREAD_RWLOCK_INT_FLAGS_SHARED
#define __PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER { { 0, 0, 0, 0, 0, 0, 0, 0, __PTHREAD_RWLOCK_ELISION_EXTRA, 0, __PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE } }
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define __PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER { { 0, 0, 0, 0, 0, 0, __PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE, 0, __PTHREAD_RWLOCK_ELISION_EXTRA, 0, 0 } }
#else /* ... */
#define __PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER { { 0, 0, 0, 0, 0, 0, 0, 0, 0, __PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE, 0 } }
#endif /* !... */

#define __PTHREAD_COND_INITIALIZER { { 0, 0, 0, 0, 0, (void *) 0, 0, 0 } }


#endif /* !_BITS_CRT_PTHREADINIT_H */
