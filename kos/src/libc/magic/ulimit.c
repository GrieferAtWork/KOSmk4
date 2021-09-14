/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: FreeBSD       (/include/ulimit.h) */
/* (#) Portability: GNU C Library (/resource/ulimit.h) */
/* (#) Portability: NetBSD        (/include/ulimit.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/ulimit.h) */
/* (#) Portability: musl libc     (/include/ulimit.h) */
/* (#) Portability: uClibc        (/include/ulimit.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(longptr_t = __LONGPTR_TYPE__)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <asm/os/ulimit.h>
)]%{

__SYSDECL_BEGIN

#if (defined(__UL_GETFSIZE) || defined(__UL_SETFSIZE))
/* Arguments for `ulimit(3)' */
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __UL_GETFSIZE
	UL_GETFSIZE = __UL_GETFSIZE, /* TODO: Doc */
#endif /* __UL_GETFSIZE */
#ifdef __UL_SETFSIZE
	UL_SETFSIZE = __UL_SETFSIZE, /* TODO: Doc */
#endif /* __UL_SETFSIZE */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __UL_GETFSIZE
#define UL_GETFSIZE UL_GETFSIZE /* TODO: Doc */
#endif /* __UL_GETFSIZE */
#ifdef __UL_SETFSIZE
#define UL_SETFSIZE UL_SETFSIZE /* TODO: Doc */
#endif /* __UL_SETFSIZE */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __UL_GETFSIZE
#define UL_GETFSIZE __UL_GETFSIZE /* TODO: Doc */
#endif /* __UL_GETFSIZE */
#ifdef __UL_SETFSIZE
#define UL_SETFSIZE __UL_SETFSIZE /* TODO: Doc */
#endif /* __UL_SETFSIZE */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

#ifdef __CC__
}

@@>> ulimit(2)
@@@param: cmd: One OF `UL_*'
[[vartypes(long), decl_include("<features.h>")]]
$longptr_t ulimit(__STDC_INT_AS_UINT_T cmd, ...);

%{
#endif /* __CC__ */

__SYSDECL_END

}
