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
/* (#) Portability: FreeBSD       (/sys/sys/acct.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/acct.h) */
/* (#) Portability: NetBSD        (/sys/sys/acct.h) */
/* (#) Portability: OpenBSD       (/sys/sys/acct.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/acct.h) */
/* (#) Portability: musl libc     (/include/sys/acct.h) */
}

%[define_replacement(fd_t = __fd_t)]

%{
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/os/acct.h>
#include <bits/types.h>

#ifdef __USE_GLIBC
#include <sys/types.h>
#include <endian.h>
#endif /* __USE_GLIBC */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __time_t_defined
#define __time_t_defined
typedef __TM_TYPE(time) time_t;
#endif /* !__time_t_defined */

}

@@Switch process accounting on and off
[[cp, section(".text.crt{|.dos}.fs.modify")]]
[[export_alias("__acct", "__libc_acct")]]
int acct([[in_opt]] const char *filename);

%{

__SYSDECL_END
#endif /* __CC__ */

}
