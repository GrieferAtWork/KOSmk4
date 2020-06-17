/* HASH CRC-32:0xdbe1be3a */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SYS_SEM_C
#define GUARD_LIBC_AUTO_DOSABI_SYS_SEM_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/sys.sem.h"

DECL_BEGIN

/* Get semaphore */
INTERN ATTR_SECTION(".text.crt.dos.io.poll") int
NOTHROW_NCX(LIBDCALL libd_semget)(key_t key,
                                  __STDC_INT_AS_UINT_T nsems,
                                  __STDC_INT_AS_UINT_T semflg) {
	return libc_semget(key, nsems, semflg);
}
/* Operate on semaphore */
INTERN ATTR_SECTION(".text.crt.dos.io.poll") int
NOTHROW_NCX(LIBDCALL libd_semop)(int semid,
                                 struct sembuf *sops,
                                 size_t nsops) {
	return libc_semop(semid, sops, nsops);
}
/* Operate on semaphore with timeout */
INTERN ATTR_SECTION(".text.crt.dos.io.poll") int
NOTHROW_NCX(LIBDCALL libd_semtimedop)(int semid,
                                      struct sembuf *sops,
                                      size_t nsops,
                                      struct timespec const *timeout) {
	return libc_semtimedop(semid, sops, nsops, timeout);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$semget, libd_semget);
DEFINE_PUBLIC_ALIAS(DOS$semop, libd_semop);
DEFINE_PUBLIC_ALIAS(DOS$semtimedop, libd_semtimedop);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SYS_SEM_C */
