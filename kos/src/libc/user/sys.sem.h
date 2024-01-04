/* HASH CRC-32:0xe6e1b567 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_SEM_H
#define GUARD_LIBC_USER_SYS_SEM_H 1

#include "../api.h"
#include "../auto/sys.sem.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/sem.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Semaphore control operation. */
INTDEF int NOTHROW_NCX(VLIBDCALL libd_semctl)(int semid, __STDC_INT_AS_UINT_T semnum, __STDC_INT_AS_UINT_T cmd, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Semaphore control operation. */
INTDEF int NOTHROW_NCX(VLIBCCALL libc_semctl)(int semid, __STDC_INT_AS_UINT_T semnum, __STDC_INT_AS_UINT_T cmd, ...);
/* Get semaphore */
INTDEF int NOTHROW_NCX(LIBCCALL libc_semget)(key_t key, __STDC_INT_AS_UINT_T nsems, __STDC_INT_AS_UINT_T semflg);
/* Operate on semaphore */
INTDEF int NOTHROW_NCX(LIBCCALL libc_semop)(int semid, struct sembuf *sops, size_t nsops);
/* Operate on semaphore with timeout */
INTDEF int NOTHROW_NCX(LIBCCALL libc_semtimedop)(int semid, struct sembuf *sops, size_t nsops, struct timespec const *timeout);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SEM_H */
