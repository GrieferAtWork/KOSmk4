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

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.io.poll")]

%{
#include <features.h>

#include <bits/os/sem.h>
#include <bits/os/sembuf.h>
#include <bits/os/timespec.h>

#ifdef __USE_GLIBC
#include <sys/ipc.h>

#include <stddef.h>
#endif /* __USE_GLIBC */

#ifdef __CC__

__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __key_t_defined
#define __key_t_defined 1
typedef __key_t key_t;
#endif /* !__key_t_defined */

}

@@Semaphore control operation.  
[[decl_include("<features.h>")]]
int semctl(int semid,
           __STDC_INT_AS_UINT_T semnum,
           __STDC_INT_AS_UINT_T cmd, ...);

@@Get semaphore
[[decl_include("<features.h>")]]
int semget(key_t key,
           __STDC_INT_AS_UINT_T nsems,
           __STDC_INT_AS_UINT_T semflg);

@@Operate on semaphore
[[decl_include("<bits/os/sembuf.h>")]]
int semop(int semid, struct sembuf *sops, size_t nsops);

%#ifdef __USE_GNU
@@Operate on semaphore with timeout
[[decl_include("<bits/os/sembuf.h>")]]
[[decl_include("<bits/os/timespec.h>")]]
int semtimedop(int semid,
               struct sembuf *sops, size_t nsops,
               struct timespec const *timeout);
/* TODO: semtimedop64(..., struct timespec64 const *timeout) */
%#endif /* __USE_GNU */

%{
#endif /* __CC__ */

__SYSDECL_END

}