/* HASH CRC-32:0xd6208116 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SEMAPHORE_C
#define GUARD_LIBC_AUTO_DOSABI_SEMAPHORE_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/semaphore.h"

DECL_BEGIN

/* Initialize semaphore object SEM to VALUE.
 * If PSHARED then share it with other processes */
INTERN ATTR_SECTION(".text.crt.dos.sched.semaphore") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_sem_init)(sem_t *sem,
                                    int pshared,
                                    unsigned int value) {
	return libc_sem_init(sem, pshared, value);
}
/* Free resources associated with semaphore object SEM */
INTERN ATTR_SECTION(".text.crt.dos.sched.semaphore") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_sem_destroy)(sem_t *sem) {
	return libc_sem_destroy(sem);
}
/* Open a named semaphore NAME with open flags OFLAGS */
INTERN ATTR_SECTION(".text.crt.dos.sched.semaphore") NONNULL((1)) sem_t *
NOTHROW_RPC_KOS(VLIBDCALL libd_sem_open)(char const *name,
                                         oflag_t oflags,
                                         ...) {
	va_list args;
	mode_t v0_mode_t;
	unsigned int v1;
	va_start(args, oflags);
	v0_mode_t = va_arg(args, mode_t);
	v1        = va_arg(args, unsigned int);
	va_end(args);
	return libc_sem_open(name, oflags, v0_mode_t, v1);
}
/* Close descriptor for named semaphore SEM */
INTERN ATTR_SECTION(".text.crt.dos.sched.semaphore") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_sem_close)(sem_t *sem) {
	return libc_sem_close(sem);
}
/* Remove named semaphore NAME */
INTERN ATTR_SECTION(".text.crt.dos.sched.semaphore") NONNULL((1)) int
NOTHROW_RPC_KOS(LIBDCALL libd_sem_unlink)(const char *name) {
	return libc_sem_unlink(name);
}
/* Wait for SEM being posted */
INTERN ATTR_SECTION(".text.crt.dos.sched.semaphore") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_sem_wait)(sem_t *sem) {
	return libc_sem_wait(sem);
}
/* Similar to `sem_wait' but wait only until ABSTIME */
INTERN ATTR_SECTION(".text.crt.dos.sched.semaphore") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_sem_timedwait)(sem_t *__restrict sem,
                                         struct timespec const *__restrict abstime) {
	return libc_sem_timedwait(sem, abstime);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.semaphore") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_sem_timedwait64)(sem_t *__restrict sem,
                                           struct timespec64 const *__restrict abstime) {
	return libc_sem_timedwait64(sem, abstime);
}
/* Test whether SEM is posted */
INTERN ATTR_SECTION(".text.crt.dos.sched.semaphore") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_sem_trywait)(sem_t *sem) {
	return libc_sem_trywait(sem);
}
/* Post SEM */
INTERN ATTR_SECTION(".text.crt.dos.sched.semaphore") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_sem_post)(sem_t *sem) {
	return libc_sem_post(sem);
}
/* Get current value of SEM and store it in *SVAL */
INTERN ATTR_SECTION(".text.crt.dos.sched.semaphore") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_sem_getvalue)(sem_t *__restrict sem,
                                        int *__restrict sval) {
	return libc_sem_getvalue(sem, sval);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$sem_init, libd_sem_init);
DEFINE_PUBLIC_ALIAS(DOS$sem_destroy, libd_sem_destroy);
DEFINE_PUBLIC_ALIAS(DOS$sem_open, libd_sem_open);
DEFINE_PUBLIC_ALIAS(DOS$sem_close, libd_sem_close);
DEFINE_PUBLIC_ALIAS(DOS$sem_unlink, libd_sem_unlink);
DEFINE_PUBLIC_ALIAS(DOS$sem_wait, libd_sem_wait);
DEFINE_PUBLIC_ALIAS(DOS$sem_timedwait, libd_sem_timedwait);
DEFINE_PUBLIC_ALIAS(DOS$sem_timedwait64, libd_sem_timedwait64);
DEFINE_PUBLIC_ALIAS(DOS$sem_trywait, libd_sem_trywait);
DEFINE_PUBLIC_ALIAS(DOS$sem_post, libd_sem_post);
DEFINE_PUBLIC_ALIAS(DOS$sem_getvalue, libd_sem_getvalue);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SEMAPHORE_C */
