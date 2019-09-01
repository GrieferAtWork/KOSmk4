/* HASH 0x3c4e53ad */
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
#ifndef GUARD_LIBC_USER_SYS_SHM_H
#define GUARD_LIBC_USER_SYS_SHM_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/shm.h>

DECL_BEGIN

INTDEF int NOTHROW_NCX(LIBCCALL libc_shmctl)(int shmid, int cmd, struct shmid_ds *buf);
INTDEF int NOTHROW_NCX(LIBCCALL libc_shmget)(key_t key, size_t size, int shmflg);
INTDEF void *NOTHROW_NCX(LIBCCALL libc_shmat)(int shmid, void const *shmaddr, int shmflg);
INTDEF int NOTHROW_NCX(LIBCCALL libc_shmdt)(void const *shmaddr);

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SHM_H */
