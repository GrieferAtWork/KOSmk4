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
#ifndef GUARD_LIBC_USER_SYS_SHM_C
#define GUARD_LIBC_USER_SYS_SHM_C 1

#include "../api.h"
#include "sys.shm.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:shmctl,hash:CRC-32=0x63ba5214]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.shm.shmctl") int
NOTHROW_NCX(LIBCCALL libc_shmctl)(int shmid,
                                  int cmd,
                                  struct shmid_ds *buf)
/*[[[body:shmctl]]]*/
{
	(void)shmid;
	(void)cmd;
	(void)buf;
	CRT_UNIMPLEMENTED("shmctl"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:shmctl]]]*/

/*[[[head:shmget,hash:CRC-32=0x5f93079d]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.shm.shmget") int
NOTHROW_NCX(LIBCCALL libc_shmget)(key_t key,
                                  size_t size,
                                  int shmflg)
/*[[[body:shmget]]]*/
{
	(void)key;
	(void)size;
	(void)shmflg;
	CRT_UNIMPLEMENTED("shmget"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:shmget]]]*/

/*[[[head:shmat,hash:CRC-32=0xd354a954]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.shm.shmat") void *
NOTHROW_NCX(LIBCCALL libc_shmat)(int shmid,
                                 void const *shmaddr,
                                 int shmflg)
/*[[[body:shmat]]]*/
{
	(void)shmid;
	(void)shmaddr;
	(void)shmflg;
	CRT_UNIMPLEMENTED("shmat"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:shmat]]]*/

/*[[[head:shmdt,hash:CRC-32=0x98fc4352]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.shm.shmdt") int
NOTHROW_NCX(LIBCCALL libc_shmdt)(void const *shmaddr)
/*[[[body:shmdt]]]*/
{
	(void)shmaddr;
	CRT_UNIMPLEMENTED("shmdt"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:shmdt]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xa4c16ee9]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(shmctl, libc_shmctl);
DEFINE_PUBLIC_WEAK_ALIAS(shmget, libc_shmget);
DEFINE_PUBLIC_WEAK_ALIAS(shmat, libc_shmat);
DEFINE_PUBLIC_WEAK_ALIAS(shmdt, libc_shmdt);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SHM_C */
