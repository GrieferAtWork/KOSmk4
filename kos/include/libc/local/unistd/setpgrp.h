/* HASH CRC-32:0xe703ae83 */
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
#ifndef __local_setpgrp_defined
#define __local_setpgrp_defined
#include <__crt.h>
#if defined(__CRT_HAVE_setpgid) || defined(__CRT_HAVE___setpgid) || defined(__CRT_HAVE___libc_setpgid)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_setpgid_defined
#define __local___localdep_setpgid_defined
#ifdef __CRT_HAVE_setpgid
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_setpgid,(__pid_t __pid, __pid_t __pgid),setpgid,(__pid,__pgid))
#elif defined(__CRT_HAVE___setpgid)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_setpgid,(__pid_t __pid, __pid_t __pgid),__setpgid,(__pid,__pgid))
#elif defined(__CRT_HAVE___libc_setpgid)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_setpgid,(__pid_t __pid, __pid_t __pgid),__libc_setpgid,(__pid,__pgid))
#else /* ... */
#undef __local___localdep_setpgid_defined
#endif /* !... */
#endif /* !__local___localdep_setpgid_defined */
__LOCAL_LIBC(setpgrp) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(setpgrp))(void) {
	return (__NAMESPACE_LOCAL_SYM __localdep_setpgid)(0, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_setpgrp_defined
#define __local___localdep_setpgrp_defined
#define __localdep_setpgrp __LIBC_LOCAL_NAME(setpgrp)
#endif /* !__local___localdep_setpgrp_defined */
#else /* __CRT_HAVE_setpgid || __CRT_HAVE___setpgid || __CRT_HAVE___libc_setpgid */
#undef __local_setpgrp_defined
#endif /* !__CRT_HAVE_setpgid && !__CRT_HAVE___setpgid && !__CRT_HAVE___libc_setpgid */
#endif /* !__local_setpgrp_defined */
