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
#ifndef GUARD_LIBC_USER_SYS_SEM_C
#define GUARD_LIBC_USER_SYS_SEM_C 1

#include "../api.h"
#include "sys.sem.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:semctl,hash:CRC-32=0x56758402]]]*/
/* Semaphore control operation. */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.io.poll.semctl") int
NOTHROW_NCX(VLIBCCALL libc_semctl)(int semid,
                                   int semnum,
                                   int cmd,
                                   ...)
/*[[[body:semctl]]]*/
{
	(void)semid;
	(void)semnum;
	(void)cmd;
	CRT_UNIMPLEMENTED("semctl"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:semctl]]]*/

/*[[[head:semget,hash:CRC-32=0x917e441b]]]*/
/* Get semaphore */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.io.poll.semget") int
NOTHROW_NCX(LIBCCALL libc_semget)(key_t key,
                                  int nsems,
                                  int semflg)
/*[[[body:semget]]]*/
{
	(void)key;
	(void)nsems;
	(void)semflg;
	CRT_UNIMPLEMENTED("semget"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:semget]]]*/

/*[[[head:semop,hash:CRC-32=0x565dbfe7]]]*/
/* Operate on semaphore */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.io.poll.semop") int
NOTHROW_NCX(LIBCCALL libc_semop)(int semid,
                                 struct sembuf *sops,
                                 size_t nsops)
/*[[[body:semop]]]*/
{
	(void)semid;
	(void)sops;
	(void)nsops;
	CRT_UNIMPLEMENTED("semop"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:semop]]]*/

/*[[[head:semtimedop,hash:CRC-32=0x1b735898]]]*/
/* Operate on semaphore with timeout */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.io.poll.semtimedop") int
NOTHROW_NCX(LIBCCALL libc_semtimedop)(int semid,
                                      struct sembuf *sops,
                                      size_t nsops,
                                      struct timespec const *timeout)
/*[[[body:semtimedop]]]*/
{
	(void)semid;
	(void)sops;
	(void)nsops;
	(void)timeout;
	CRT_UNIMPLEMENTED("semtimedop"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:semtimedop]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x4a7d4fff]]]*/
#undef semctl
DEFINE_PUBLIC_WEAK_ALIAS(semctl, libc_semctl);
DEFINE_PUBLIC_WEAK_ALIAS(semget, libc_semget);
DEFINE_PUBLIC_WEAK_ALIAS(semop, libc_semop);
DEFINE_PUBLIC_WEAK_ALIAS(semtimedop, libc_semtimedop);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SEM_C */
