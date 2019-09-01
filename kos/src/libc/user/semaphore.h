/* HASH 0x39f73f76 */
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
#ifndef GUARD_LIBC_USER_SEMAPHORE_H
#define GUARD_LIBC_USER_SEMAPHORE_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <semaphore.h>

DECL_BEGIN

/* Initialize semaphore object SEM to VALUE.
 * If PSHARED then share it with other processes */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sem_init)(sem_t *sem, int pshared, unsigned int value);
/* Free resources associated with semaphore object SEM */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sem_destroy)(sem_t *sem);
/* Open a named semaphore NAME with open flags OFLAG */
INTDEF NONNULL((1)) sem_t *NOTHROW_RPC_KOS(VLIBCCALL libc_sem_open)(char const *name, oflag_t oflag, ...);
/* Close descriptor for named semaphore SEM */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sem_close)(sem_t *sem);
/* Remove named semaphore NAME */
INTDEF NONNULL((1)) int NOTHROW_RPC_KOS(LIBCCALL libc_sem_unlink)(const char *name);
/* Wait for SEM being posted */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_sem_wait)(sem_t *sem);
/* Similar to `sem_wait' but wait only until ABSTIME */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_sem_timedwait)(sem_t *__restrict sem, struct timespec const *__restrict abstime);
/* Similar to `sem_wait' but wait only until ABSTIME */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_sem_timedwait64)(sem_t *__restrict sem, struct timespec64 const *__restrict abstime);
/* Test whether SEM is posted */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sem_trywait)(sem_t *sem);
/* Post SEM */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sem_post)(sem_t *sem);
/* Get current value of SEM and store it in *SVAL */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_sem_getvalue)(sem_t *__restrict sem, int *__restrict sval);

DECL_END

#endif /* !GUARD_LIBC_USER_SEMAPHORE_H */
