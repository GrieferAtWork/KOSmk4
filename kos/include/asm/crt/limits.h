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
#ifndef _ASM_CRT_LIMITS_H
#define _ASM_CRT_LIMITS_H 1

/* Libc configuration parameters and limits */
#include <__crt.h>

#if defined(__CRT_KOS_PRIMARY)
#include <hybrid/limitcore.h> /* __INT_MAX__ */

#define __PTHREAD_KEYS_MAX    (-1)        /* <pthread.h>: The # of data keys per process. */
#define __PTHREAD_STACK_MIN   16384       /* <pthread.h>: Minimum size for a thread. */
#define __PTHREAD_THREADS_MAX (-1)        /* <pthread.h>: The # of threads per process. */
#define __LOGIN_NAME_MAX      256         /* Maximum login name length. This is arbitrary. */
#define __COLL_WEIGHTS_MAX    255         /* The maximum number of weights that can be assigned to an entry of the LC_COLLATE `order' keyword in the locale definition file. */
#define __CHARCLASS_NAME_MAX  2048        /* The maximum number of repeated occurrences of a regular expression permitted when using the interval notation `\{M,N\}'. */
#define __RE_DUP_MAX          (-1)        /* The maximum number of bytes in a character class name. */
#define __NL_ARGMAX           (-1)        /* Maximum number of positional arguments (e.g. "%1$d") in calls to `printf' or `scanf'. */
#define __NL_LANGMAX          (-1)        /* <libintl.h>: Maximum number of bytes in a `LANG' name. */
#define __NL_MSGMAX           (-1)        /* Maximum message number. */
#define __NL_NMAX             (-1)        /* Maximum number of bytes in N-to-1 collation mapping. */
#define __NL_SETMAX           (-1)        /* Maximum set number. */
#define __NL_TEXTMAX          (-1)        /* Maximum number of bytes in a message. */
#define __STREAM_MAX          (-1)        /* <stdio.h>: Number of streams a process can have open at once. */
#define __SEM_NSEMS_MAX       (-1)        /* <semaphore.h>: Number of semaphores a process can have. */
#define __SEM_VALUE_MAX       __INT_MAX__ /* <semaphore.h>: Maximum value the semaphore can have. */

#elif defined(__CRT_GLC_PRIMARY)

#define __PTHREAD_KEYS_MAX    1024       /* <pthread.h>: The # of data keys per process. */
#define __PTHREAD_STACK_MIN   16384      /* <pthread.h>: Minimum size for a thread. */
#define __PTHREAD_THREADS_MAX (-1)       /* <pthread.h>: The # of threads per process. */
#define __LOGIN_NAME_MAX      256        /* Maximum login name length. This is arbitrary. */
#define __SEM_VALUE_MAX       2147483647 /* <semaphore.h>: Maximum value the semaphore can have. */
#define __COLL_WEIGHTS_MAX    255        /* The maximum number of weights that can be assigned to an entry of the LC_COLLATE `order' keyword in the locale definition file. */
#define __CHARCLASS_NAME_MAX  2048       /* The maximum number of repeated occurrences of a regular expression permitted when using the interval notation `\{M,N\}'. */
#define __RE_DUP_MAX          (-1)       /* The maximum number of bytes in a character class name. */
#define __NL_ARGMAX           (-1)       /* Maximum value of `digit' in calls to the `printf' and `scanf' functions. */
#define __NL_LANGMAX          (-1)       /* <libintl.h>: Maximum number of bytes in a `LANG' name. */
#define __NL_MSGMAX           (-1)       /* Maximum message number. */
#define __NL_NMAX             (-1)       /* Maximum number of bytes in N-to-1 collation mapping. */
#define __NL_SETMAX           (-1)       /* Maximum set number. */
#define __NL_TEXTMAX          (-1)       /* Maximum number of bytes in a message. */

#endif


#endif /* !_ASM_CRT_LIMITS_H */
