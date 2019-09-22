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
#ifndef GUARD_LIBC_USER_SEMAPHORE_C
#define GUARD_LIBC_USER_SEMAPHORE_C 1

#include "../api.h"
#include "semaphore.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:sem_init,hash:CRC-32=0x9b49de17]]]*/
/* Initialize semaphore object SEM to VALUE.
 * If PSHARED then share it with other processes */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.semaphore.sem_init") int
NOTHROW_NCX(LIBCCALL libc_sem_init)(sem_t *sem,
                                    int pshared,
                                    unsigned int value)
/*[[[body:sem_init]]]*/
{
	CRT_UNIMPLEMENTED("sem_init"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:sem_init]]]*/

/*[[[head:sem_destroy,hash:CRC-32=0xbc662e37]]]*/
/* Free resources associated with semaphore object SEM */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.semaphore.sem_destroy") int
NOTHROW_NCX(LIBCCALL libc_sem_destroy)(sem_t *sem)
/*[[[body:sem_destroy]]]*/
{
	CRT_UNIMPLEMENTED("sem_destroy"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:sem_destroy]]]*/

/*[[[head:sem_open,hash:CRC-32=0x6e6740d]]]*/
/* Open a named semaphore NAME with open flags OFLAG */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.semaphore.sem_open") sem_t *
NOTHROW_RPC_KOS(VLIBCCALL libc_sem_open)(char const *name,
                                         oflag_t oflag,
                                         ...)
/*[[[body:sem_open]]]*/
{
	CRT_UNIMPLEMENTED("sem_open"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:sem_open]]]*/

/*[[[head:sem_close,hash:CRC-32=0xbe535676]]]*/
/* Close descriptor for named semaphore SEM */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.semaphore.sem_close") int
NOTHROW_NCX(LIBCCALL libc_sem_close)(sem_t *sem)
/*[[[body:sem_close]]]*/
{
	CRT_UNIMPLEMENTED("sem_close"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:sem_close]]]*/

/*[[[head:sem_unlink,hash:CRC-32=0xb789d603]]]*/
/* Remove named semaphore NAME */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.semaphore.sem_unlink") int
NOTHROW_RPC_KOS(LIBCCALL libc_sem_unlink)(const char *name)
/*[[[body:sem_unlink]]]*/
{
	CRT_UNIMPLEMENTED("sem_unlink"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:sem_unlink]]]*/

/*[[[head:sem_wait,hash:CRC-32=0x57284335]]]*/
/* Wait for SEM being posted */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.semaphore.sem_wait") int
NOTHROW_RPC(LIBCCALL libc_sem_wait)(sem_t *sem)
/*[[[body:sem_wait]]]*/
{
	CRT_UNIMPLEMENTED("sem_wait"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:sem_wait]]]*/

/*[[[head:sem_timedwait,hash:CRC-32=0xe2bd3d49]]]*/
/* Similar to `sem_wait' but wait only until ABSTIME */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.semaphore.sem_timedwait") int
NOTHROW_RPC(LIBCCALL libc_sem_timedwait)(sem_t *__restrict sem,
                                         struct timespec const *__restrict abstime)
/*[[[body:sem_timedwait]]]*/
{
	CRT_UNIMPLEMENTED("sem_timedwait"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:sem_timedwait]]]*/

/*[[[head:sem_timedwait64,hash:CRC-32=0x77a1bf9b]]]*/
/* Similar to `sem_wait' but wait only until ABSTIME */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_sem_timedwait64, libc_sem_timedwait);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.semaphore.sem_timedwait64") int
NOTHROW_RPC(LIBCCALL libc_sem_timedwait64)(sem_t *__restrict sem,
                                           struct timespec64 const *__restrict abstime)
/*[[[body:sem_timedwait64]]]*/
{
	CRT_UNIMPLEMENTED("sem_timedwait64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:sem_timedwait64]]]*/

/*[[[head:sem_trywait,hash:CRC-32=0x8c0b11f3]]]*/
/* Test whether SEM is posted */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.semaphore.sem_trywait") int
NOTHROW_NCX(LIBCCALL libc_sem_trywait)(sem_t *sem)
/*[[[body:sem_trywait]]]*/
{
	CRT_UNIMPLEMENTED("sem_trywait"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:sem_trywait]]]*/

/*[[[head:sem_post,hash:CRC-32=0xb4a241a8]]]*/
/* Post SEM */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.semaphore.sem_post") int
NOTHROW_NCX(LIBCCALL libc_sem_post)(sem_t *sem)
/*[[[body:sem_post]]]*/
{
	CRT_UNIMPLEMENTED("sem_post"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:sem_post]]]*/

/*[[[head:sem_getvalue,hash:CRC-32=0x80176003]]]*/
/* Get current value of SEM and store it in *SVAL */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.semaphore.sem_getvalue") int
NOTHROW_NCX(LIBCCALL libc_sem_getvalue)(sem_t *__restrict sem,
                                        int *__restrict sval)
/*[[[body:sem_getvalue]]]*/
{
	CRT_UNIMPLEMENTED("sem_getvalue"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:sem_getvalue]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x5d60f078]]]*/
#undef sem_open
DEFINE_PUBLIC_WEAK_ALIAS(sem_init, libc_sem_init);
DEFINE_PUBLIC_WEAK_ALIAS(sem_destroy, libc_sem_destroy);
DEFINE_PUBLIC_WEAK_ALIAS(sem_open, libc_sem_open);
DEFINE_PUBLIC_WEAK_ALIAS(sem_close, libc_sem_close);
DEFINE_PUBLIC_WEAK_ALIAS(sem_unlink, libc_sem_unlink);
DEFINE_PUBLIC_WEAK_ALIAS(sem_wait, libc_sem_wait);
DEFINE_PUBLIC_WEAK_ALIAS(sem_timedwait, libc_sem_timedwait);
DEFINE_PUBLIC_WEAK_ALIAS(sem_timedwait64, libc_sem_timedwait64);
DEFINE_PUBLIC_WEAK_ALIAS(sem_trywait, libc_sem_trywait);
DEFINE_PUBLIC_WEAK_ALIAS(sem_post, libc_sem_post);
DEFINE_PUBLIC_WEAK_ALIAS(sem_getvalue, libc_sem_getvalue);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SEMAPHORE_C */
