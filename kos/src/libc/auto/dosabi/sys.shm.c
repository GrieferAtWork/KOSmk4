/* HASH CRC-32:0x9d653981 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SYS_SHM_C
#define GUARD_LIBC_AUTO_DOSABI_SYS_SHM_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/sys.shm.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.utility.shm") int
NOTHROW_NCX(LIBDCALL libd_shmctl)(int shmid,
                                  __STDC_INT_AS_UINT_T cmd,
                                  struct shmid_ds *buf) {
	return libc_shmctl(shmid, cmd, buf);
}
INTERN ATTR_SECTION(".text.crt.dos.utility.shm") int
NOTHROW_NCX(LIBDCALL libd_shmget)(key_t key,
                                  size_t size,
                                  __STDC_INT_AS_UINT_T shmflg) {
	return libc_shmget(key, size, shmflg);
}
INTERN ATTR_SECTION(".text.crt.dos.utility.shm") void *
NOTHROW_NCX(LIBDCALL libd_shmat)(int shmid,
                                 void const *shmaddr,
                                 __STDC_INT_AS_UINT_T shmflg) {
	return libc_shmat(shmid, shmaddr, shmflg);
}
INTERN ATTR_SECTION(".text.crt.dos.utility.shm") int
NOTHROW_NCX(LIBDCALL libd_shmdt)(void const *shmaddr) {
	return libc_shmdt(shmaddr);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$shmctl, libd_shmctl);
DEFINE_PUBLIC_ALIAS(DOS$shmget, libd_shmget);
DEFINE_PUBLIC_ALIAS(DOS$shmat, libd_shmat);
DEFINE_PUBLIC_ALIAS(DOS$shmdt, libd_shmdt);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SYS_SHM_C */
