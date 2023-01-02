/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_SHM_C
#define GUARD_LIBC_USER_SYS_SHM_C 1

#include "../api.h"
/**/

#include "sys.shm.h"

DECL_BEGIN

/*[[[head:libc_shmctl,hash:CRC-32=0x8db49986]]]*/
INTERN ATTR_SECTION(".text.crt.utility.shm") int
NOTHROW_NCX(LIBCCALL libc_shmctl)(int shmid,
                                  __STDC_INT_AS_UINT_T cmd,
                                  struct shmid_ds *buf)
/*[[[body:libc_shmctl]]]*/
/*AUTO*/{
	(void)shmid;
	(void)cmd;
	(void)buf;
	CRT_UNIMPLEMENTEDF("shmctl(shmid: %x, cmd: %x, buf: %p)", shmid, cmd, buf); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_shmctl]]]*/

/*[[[head:libc_shmget,hash:CRC-32=0x6e5fbd86]]]*/
INTERN ATTR_SECTION(".text.crt.utility.shm") int
NOTHROW_NCX(LIBCCALL libc_shmget)(key_t key,
                                  size_t size,
                                  __STDC_INT_AS_UINT_T shmflg)
/*[[[body:libc_shmget]]]*/
/*AUTO*/{
	(void)key;
	(void)size;
	(void)shmflg;
	CRT_UNIMPLEMENTEDF("shmget(key: %" PRIxN(__SIZEOF_KEY_T__) ", size: %Ix, shmflg: %x)", key, size, shmflg); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_shmget]]]*/

/*[[[head:libc_shmat,hash:CRC-32=0x182af4ff]]]*/
INTERN ATTR_SECTION(".text.crt.utility.shm") void *
NOTHROW_NCX(LIBCCALL libc_shmat)(int shmid,
                                 void const *shmaddr,
                                 __STDC_INT_AS_UINT_T shmflg)
/*[[[body:libc_shmat]]]*/
/*AUTO*/{
	(void)shmid;
	(void)shmaddr;
	(void)shmflg;
	CRT_UNIMPLEMENTEDF("shmat(shmid: %x, shmaddr: %p, shmflg: %x)", shmid, shmaddr, shmflg); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_shmat]]]*/

/*[[[head:libc_shmdt,hash:CRC-32=0xca4775e1]]]*/
INTERN ATTR_SECTION(".text.crt.utility.shm") int
NOTHROW_NCX(LIBCCALL libc_shmdt)(void const *shmaddr)
/*[[[body:libc_shmdt]]]*/
/*AUTO*/{
	(void)shmaddr;
	CRT_UNIMPLEMENTEDF("shmdt(shmaddr: %p)", shmaddr); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_shmdt]]]*/


/*[[[start:exports,hash:CRC-32=0x8b4a25ab]]]*/
DEFINE_PUBLIC_ALIAS(shmctl, libc_shmctl);
DEFINE_PUBLIC_ALIAS(shmget, libc_shmget);
DEFINE_PUBLIC_ALIAS(shmat, libc_shmat);
DEFINE_PUBLIC_ALIAS(shmdt, libc_shmdt);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SHM_C */
