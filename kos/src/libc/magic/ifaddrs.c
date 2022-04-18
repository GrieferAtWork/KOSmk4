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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/ifaddrs.h) */
/* (#) Portability: FreeBSD       (/include/ifaddrs.h) */
/* (#) Portability: GNU C Library (/inet/ifaddrs.h) */
/* (#) Portability: NetBSD        (/include/ifaddrs.h) */
/* (#) Portability: OpenBSD       (/include/ifaddrs.h) */
/* (#) Portability: libc6         (/include/ifaddrs.h) */
/* (#) Portability: mintlib       (/include/ifaddrs.h) */
/* (#) Portability: musl libc     (/include/ifaddrs.h) */
/* (#) Portability: uClibc        (/include/ifaddrs.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(oflag_t = __oflag_t)]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <bits/crt/ifaddrs.h>
)]%{

#ifdef __USE_GLIBC
#include <sys/socket.h>
#endif /* __USE_GLIBC */

#ifdef __CC__
__SYSDECL_BEGIN

}

@@>> getifaddrs(3)
[[decl_include("<bits/crt/ifaddrs.h>")]]
int getifaddrs(struct ifaddrs **ifap);

@@>> freeifaddrs(3)
[[decl_include("<bits/crt/ifaddrs.h>")]]
void freeifaddrs(struct ifaddrs *ifa);

%{

__SYSDECL_END
#endif /* __CC__ */

}
