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

/*[[[head:shmctl,hash:0xb95fd8d5]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.shm.shmctl") int
NOTHROW_NCX(LIBCCALL libc_shmctl)(int shmid,
                                  int cmd,
                                  struct shmid_ds *buf)
/*[[[body:shmctl]]]*/
{
	CRT_UNIMPLEMENTED("shmctl"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:shmctl]]]*/

/*[[[head:shmget,hash:0x6e126270]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.shm.shmget") int
NOTHROW_NCX(LIBCCALL libc_shmget)(key_t key,
                                  size_t size,
                                  int shmflg)
/*[[[body:shmget]]]*/
{
	CRT_UNIMPLEMENTED("shmget"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:shmget]]]*/

/*[[[head:shmat,hash:0xe7f83112]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.shm.shmat") void *
NOTHROW_NCX(LIBCCALL libc_shmat)(int shmid,
                                 void const *shmaddr,
                                 int shmflg)
/*[[[body:shmat]]]*/
{
	CRT_UNIMPLEMENTED("shmat"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:shmat]]]*/

/*[[[head:shmdt,hash:0xbaf250a]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.shm.shmdt") int
NOTHROW_NCX(LIBCCALL libc_shmdt)(void const *shmaddr)
/*[[[body:shmdt]]]*/
{
	CRT_UNIMPLEMENTED("shmdt"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:shmdt]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0x8fa8e858]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(shmctl, libc_shmctl);
DEFINE_PUBLIC_WEAK_ALIAS(shmget, libc_shmget);
DEFINE_PUBLIC_WEAK_ALIAS(shmat, libc_shmat);
DEFINE_PUBLIC_WEAK_ALIAS(shmdt, libc_shmdt);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SHM_C */
