/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (>) Standard: POSIX.1-2004 (Issue 6, IEEE Std 1003.1-2004) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/un.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/un.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/un.h) */
/* (#) Portability: FreeBSD       (/sys/sys/un.h) */
/* (#) Portability: GNU C Library (/socket/sys/un.h) */
/* (#) Portability: NetBSD        (/sys/sys/un.h) */
/* (#) Portability: OpenBSD       (/sys/sys/un.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/un.h) */
/* (#) Portability: diet libc     (/include/sys/un.h) */
/* (#) Portability: libc4/5       (/include/sys/un.h) */
/* (#) Portability: mintlib       (/include/sys/un.h) */
/* (#) Portability: musl libc     (/include/sys/un.h) */
/* (#) Portability: uClibc        (/include/sys/un.h) */
#ifndef _SYS_UN_H
#define _SYS_UN_H 1

#include <__stdinc.h>

#include <asm/os/socket.h> /* __AF_LOCAL */

#ifdef __AF_LOCAL
#include <features.h>

#include <bits/os/sockaddr-common.h> /* __SOCKADDR_COMMON */
#include <bits/types.h>
#ifdef __USE_MISC
#include <libc/string.h>
#endif /* __USE_MISC */

#ifdef __CC__
__DECL_BEGIN

#ifndef __sa_family_t_defined
#define __sa_family_t_defined
typedef __sa_family_t sa_family_t; /* One of `AF_*' */
#endif /* !__sa_family_t_defined */

#ifndef __sockaddr_un_defined
#define __sockaddr_un_defined
struct sockaddr_un {
	__SOCKADDR_COMMON(sun_);
	char sun_path[108]; /* Path name. */
};
#endif /* !__sockaddr_un_defined */

#ifdef __USE_KOS
#define DEFINE_SOCKADDR_UN(name, path)         \
	struct {                                   \
		__SOCKADDR_COMMON(sun_);               \
		char sun_path[__COMPILER_LENOF(path)]; \
	} name = { __AF_LOCAL, path }
#endif /* __USE_KOS */

#ifdef __USE_MISC
#define SUN_LEN(ptr) \
	(__builtin_offsetof(struct sockaddr_un, sun_path) + __libc_strlen((ptr)->sun_path))
#endif /* __USE_MISC */

__DECL_END
#endif /* __CC__ */
#endif /* __AF_LOCAL */

#endif /* !_SYS_UN_H */
