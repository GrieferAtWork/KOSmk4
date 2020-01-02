/* HASH CRC-32:0x7ae6bd99 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_sem_timedwait64_defined
#ifdef __CRT_HAVE_sem_timedwait
#define __local_sem_timedwait64_defined 1
/* Dependency: "sem_timedwait32" from "semaphore" */
#ifndef ____localdep_sem_timedwait32_defined
#define ____localdep_sem_timedwait32_defined 1
#ifdef __CRT_HAVE_sem_timedwait
/* Similar to `sem_wait' but wait only until ABSTIME */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_sem_timedwait32,(sem_t *__restrict __sem, struct __timespec32 const *__restrict __abstime),sem_timedwait,(__sem,__abstime))
#else /* LIBC: sem_timedwait */
#undef ____localdep_sem_timedwait32_defined
#endif /* sem_timedwait32... */
#endif /* !____localdep_sem_timedwait32_defined */

__NAMESPACE_LOCAL_BEGIN
/* Similar to `sem_wait' but wait only until ABSTIME */
__LOCAL_LIBC(sem_timedwait64) __ATTR_NONNULL((1, 2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(sem_timedwait64))(sem_t *__restrict __sem,
                                                             struct __timespec64 const *__restrict __abstime) {
#line 106 "kos/src/libc/magic/semaphore.c"
	struct __timespec32 __ts32;
	__ts32.tv_sec = (__time32_t)__abstime->tv_sec;
	__ts32.tv_nsec = __abstime->tv_nsec;
	return __localdep_sem_timedwait32(__sem, &__ts32);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_sem_timedwait */
#endif /* !__local_sem_timedwait64_defined */
