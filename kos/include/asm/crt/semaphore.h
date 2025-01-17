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
#ifndef _ASM_CRT_SEMAPHORE_H
#define _ASM_CRT_SEMAPHORE_H 1

#include <__crt.h>

/* #define __ARCH_HAVE_INTERPROCESS_SEMAPHORES
 * >> Defined if `sem_init(3)' with a non-zero value for `pshared'
 *    succeeds,   rather   than  returning   with  `errno=ENOSYS'. */
#if defined(__CRT_KOS) || defined(__CRT_GLC)
#define __ARCH_HAVE_INTERPROCESS_SEMAPHORES 1
#endif /* ... */

/* #define __ARCH_HAVE_NON_UNIQUE_SEM_OPEN
 * >> Defined if  `sem_open(3)' returns  non-unique semaphore  objects
 *    when passed separate names. (current) POSIX requires that  calls
 *    to `sem_open(3)' that use identical values for `name' shall also
 *    return identical  pointers, rather  than allowing  it to  return
 *    different pointer, and simply require those points to be  backed
 *    by identical physical memory. */
#if defined(__CRT_KOS)
#define __ARCH_HAVE_NON_UNIQUE_SEM_OPEN 1
#endif /* ... */

#endif /* !_ASM_CRT_SEMAPHORE_H */
