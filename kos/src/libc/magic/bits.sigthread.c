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

%[define_replacement(sigset_t = "struct __sigset_struct")]
%[default_impl_section(.text.crt.sched.pthread)]


%(user){
DECL_END
#include <pthread.h>
#include <bits/sigset.h>
DECL_BEGIN

#ifndef __sigset_t_defined
#define __sigset_t_defined 1
typedef __sigset_t sigset_t;
#endif /* !__sigset_t_defined */

}

%{
#include <features.h>
#include <bits/pthreadtypes.h>
#include <bits/sigval.h> /* union sigval */

__SYSDECL_BEGIN

#ifdef __CC__

struct __sigset_struct;

}

[guard] pthread_sigmask:(int how, $sigset_t const *__restrict newmask, $sigset_t *__restrict oldmask) -> int;
[guard] pthread_kill:($pthread_t threadid, int signo) -> int;

%#ifdef __USE_GNU
[guard] pthread_sigqueue:($pthread_t threadid, int signo, union sigval const value) -> int;
%#endif /* __USE_GNU */

%{
#endif /* __CC__ */

__SYSDECL_END

}