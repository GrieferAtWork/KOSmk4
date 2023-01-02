/* HASH CRC-32:0xd3fe9ed2 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_setegid_defined
#define __local_setegid_defined
#include <__crt.h>
#if defined(__CRT_HAVE_setregid) || defined(__CRT_HAVE___setregid) || defined(__CRT_HAVE___libc_setregid) || defined(__CRT_HAVE_setresgid)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_setregid_defined
#define __local___localdep_setregid_defined
#ifdef __CRT_HAVE_setregid
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_setregid,(__gid_t __rgid, __gid_t __egid),setregid,(__rgid,__egid))
#elif defined(__CRT_HAVE___setregid)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_setregid,(__gid_t __rgid, __gid_t __egid),__setregid,(__rgid,__egid))
#elif defined(__CRT_HAVE___libc_setregid)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_setregid,(__gid_t __rgid, __gid_t __egid),__libc_setregid,(__rgid,__egid))
#elif defined(__CRT_HAVE_setresgid)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/setregid.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_setregid __LIBC_LOCAL_NAME(setregid)
#else /* ... */
#undef __local___localdep_setregid_defined
#endif /* !... */
#endif /* !__local___localdep_setregid_defined */
__LOCAL_LIBC(setegid) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(setegid))(__gid_t __egid) {
	return (__NAMESPACE_LOCAL_SYM __localdep_setregid)((__gid_t)-1, __egid);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_setegid_defined
#define __local___localdep_setegid_defined
#define __localdep_setegid __LIBC_LOCAL_NAME(setegid)
#endif /* !__local___localdep_setegid_defined */
#else /* __CRT_HAVE_setregid || __CRT_HAVE___setregid || __CRT_HAVE___libc_setregid || __CRT_HAVE_setresgid */
#undef __local_setegid_defined
#endif /* !__CRT_HAVE_setregid && !__CRT_HAVE___setregid && !__CRT_HAVE___libc_setregid && !__CRT_HAVE_setresgid */
#endif /* !__local_setegid_defined */
