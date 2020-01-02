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
#ifndef _SYS_UN_H
#define _SYS_UN_H 1

#include <__stdinc.h>
#include <features.h>
#include <bits/sockaddr.h>
#ifdef __USE_MISC
#include <libc/string.h>
#endif /* __USE_MISC */

__SYSDECL_BEGIN

#ifdef __CC__
#ifndef __sockaddr_un_defined
#define __sockaddr_un_defined 1
struct sockaddr_un {
	__SOCKADDR_COMMON(sun_);
	char sun_path[108]; /* Path name. */
};
#endif /* !__sockaddr_un_defined */

#ifdef __USE_KOS
#define DEFINE_SOCKADDR_UN(name,path) \
    struct { __SOCKADDR_COMMON(sun_); char sun_path[sizeof(path)]; } \
    name = { AF_UNIX, path }
#endif

#ifdef __USE_MISC
#define SUN_LEN(ptr)   ((size_t)(((struct sockaddr_un *)0)->sun_path)+__libc_strlen((ptr)->sun_path))
#endif /* __USE_MISC */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_UN_H */
