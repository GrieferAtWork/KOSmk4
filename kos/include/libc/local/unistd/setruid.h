/* HASH CRC-32:0x2bae589a */
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
#ifndef __local_setruid_defined
#define __local_setruid_defined
#include <__crt.h>
#if defined(__CRT_HAVE_setreuid) || defined(__CRT_HAVE___setreuid) || defined(__CRT_HAVE___libc_setreuid) || defined(__CRT_HAVE_setresuid)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_setreuid_defined
#define __local___localdep_setreuid_defined
#ifdef __CRT_HAVE_setreuid
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_setreuid,(__uid_t __ruid, __uid_t __euid),setreuid,(__ruid,__euid))
#elif defined(__CRT_HAVE___setreuid)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_setreuid,(__uid_t __ruid, __uid_t __euid),__setreuid,(__ruid,__euid))
#elif defined(__CRT_HAVE___libc_setreuid)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_setreuid,(__uid_t __ruid, __uid_t __euid),__libc_setreuid,(__ruid,__euid))
#elif defined(__CRT_HAVE_setresuid)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/setreuid.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_setreuid __LIBC_LOCAL_NAME(setreuid)
#else /* ... */
#undef __local___localdep_setreuid_defined
#endif /* !... */
#endif /* !__local___localdep_setreuid_defined */
__LOCAL_LIBC(setruid) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(setruid))(__uid_t __ruid) {
	return (__NAMESPACE_LOCAL_SYM __localdep_setreuid)(__ruid, (__uid_t)-1);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_setruid_defined
#define __local___localdep_setruid_defined
#define __localdep_setruid __LIBC_LOCAL_NAME(setruid)
#endif /* !__local___localdep_setruid_defined */
#else /* __CRT_HAVE_setreuid || __CRT_HAVE___setreuid || __CRT_HAVE___libc_setreuid || __CRT_HAVE_setresuid */
#undef __local_setruid_defined
#endif /* !__CRT_HAVE_setreuid && !__CRT_HAVE___setreuid && !__CRT_HAVE___libc_setreuid && !__CRT_HAVE_setresuid */
#endif /* !__local_setruid_defined */
