/* HASH CRC-32:0xbfda11a0 */
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
#ifndef _SYS_SHM_H
#define _SYS_SHM_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <sys/ipc.h>
#include <bits/shm.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifdef __USE_XOPEN
#ifndef __pid_t_defined
#define __pid_t_defined 1
typedef __pid_t pid_t;
#endif /* __pid_t_defined */
#endif /* __USE_XOPEN */

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __key_t_defined
#define __key_t_defined 1
typedef __key_t key_t;
#endif /* !__key_t_defined */

#ifndef __time_t_defined
#define __time_t_defined 1
typedef __TM_TYPE(time) time_t;
#endif /* !__time_t_defined */

__CDECLARE_OPT(,int,__NOTHROW_NCX,shmctl,(int __shmid, __STDC_INT_AS_UINT_T __cmd, struct shmid_ds *__buf),(__shmid,__cmd,__buf))
__CDECLARE_OPT(,int,__NOTHROW_NCX,shmget,(key_t __key, size_t __size, __STDC_INT_AS_UINT_T __shmflg),(__key,__size,__shmflg))
__CDECLARE_OPT(,void *,__NOTHROW_NCX,shmat,(int __shmid, void const *__shmaddr, __STDC_INT_AS_UINT_T __shmflg),(__shmid,__shmaddr,__shmflg))
__CDECLARE_OPT(,int,__NOTHROW_NCX,shmdt,(void const *__shmaddr),(__shmaddr))

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_SHM_H */
