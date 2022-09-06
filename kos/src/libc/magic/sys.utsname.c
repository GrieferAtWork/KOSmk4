/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/utsname.h) */
/* (#) Portability: DJGPP         (/include/sys/utsname.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/utsname.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/utsname.h) */
/* (#) Portability: FreeBSD       (/sys/sys/utsname.h) */
/* (#) Portability: GNU C Library (/posix/sys/utsname.h) */
/* (#) Portability: NetBSD        (/sys/sys/utsname.h) */
/* (#) Portability: OpenBSD       (/sys/sys/utsname.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/utsname.h) */
/* (#) Portability: diet libc     (/include/sys/utsname.h) */
/* (#) Portability: libc4/5       (/include/sys/utsname.h) */
/* (#) Portability: mintlib       (/include/sys/utsname.h) */
/* (#) Portability: musl libc     (/include/sys/utsname.h) */
/* (#) Portability: uClibc        (/include/sys/utsname.h) */
}

%[define_replacement(fd_t = __fd_t)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/os/utsname.h>
)]%{

/* Note that SVID assumes all members have the same size. */
#ifdef __USE_MISC
#define SYS_NMLN _UTSNAME_LENGTH
#endif /* __USE_MISC */

#ifndef _UN_LEN
#define _UN_LEN _UTSNAME_LENGTH /* From EMX kLIBC */
#endif /* !_UN_LEN */

#ifdef __CC__
__SYSDECL_BEGIN

}

@@>> uname(2)
@@Put information about the system in `name'
@@@return: 0:  Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/os/utsname.h>")]]
[[export_alias("__uname", "__libc_uname")]]
int uname([[out]] struct utsname *name);

%{

__SYSDECL_END
#endif /* __CC__ */

}
