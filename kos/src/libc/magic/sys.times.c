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
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/times.h) */
/* (#) Portability: DJGPP         (/include/sys/times.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/times.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/times.h) */
/* (#) Portability: FreeBSD       (/sys/sys/times.h) */
/* (#) Portability: GNU C Library (/posix/sys/times.h) */
/* (#) Portability: NetBSD        (/sys/sys/times.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/times.h) */
/* (#) Portability: OpenBSD       (/sys/sys/times.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/times.h) */
/* (#) Portability: diet libc     (/include/sys/times.h) */
/* (#) Portability: libc4/5       (/include/sys/times.h) */
/* (#) Portability: mintlib       (/include/sys/times.h) */
/* (#) Portability: musl libc     (/include/sys/times.h) */
/* (#) Portability: uClibc        (/include/sys/times.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(clock_t = __clock_t)]

%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <bits/os/tms.h> /* struct tms */
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __clock_t_defined
#define __clock_t_defined
typedef __clock_t clock_t;
#endif /* !__clock_t_defined */

}

@@>> times(2)
[[decl_include("<bits/types.h>", "<bits/os/tms.h>")]]
[[export_alias("__times", "__libc_times")]]
clock_t times([[out_opt]] struct tms *buffer);

%{

__SYSDECL_END
#endif /* __CC__ */

}
