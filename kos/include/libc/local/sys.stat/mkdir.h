/* HASH CRC-32:0x1fce4b60 */
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
#ifndef __local_mkdir_defined
#define __local_mkdir_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if (defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir)) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_mkdirat) || defined(__CRT_HAVE_fmkdirat)))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_dos_mkdir_defined) && defined(__CRT_HAVE__mkdir)
#define __local___localdep_dos_mkdir_defined
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,__localdep_dos_mkdir,(char const *__pathname),_mkdir,(__pathname))
#endif /* !__local___localdep_dos_mkdir_defined && __CRT_HAVE__mkdir */
#ifndef __local___localdep_mkdirat_defined
#define __local___localdep_mkdirat_defined
#ifdef __CRT_HAVE_mkdirat
__CREDIRECT(__ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,__localdep_mkdirat,(__fd_t __dirfd, char const *__pathname, __mode_t __mode),mkdirat,(__dirfd,__pathname,__mode))
#elif defined(__CRT_HAVE_fmkdirat)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.stat/mkdirat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mkdirat __LIBC_LOCAL_NAME(mkdirat)
#else /* ... */
#undef __local___localdep_mkdirat_defined
#endif /* !... */
#endif /* !__local___localdep_mkdirat_defined */
__LOCAL_LIBC(mkdir) __ATTR_ACCESS_RO(1) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(mkdir))(char const *__pathname, __mode_t __mode) {
#if defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir)
	(void)__mode;
	return (__NAMESPACE_LOCAL_SYM __localdep_dos_mkdir)(__pathname);
#else /* __CRT_DOS_PRIMARY && __CRT_HAVE__mkdir */
	return (__NAMESPACE_LOCAL_SYM __localdep_mkdirat)(__AT_FDCWD, __pathname, __mode);
#endif /* !__CRT_DOS_PRIMARY || !__CRT_HAVE__mkdir */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mkdir_defined
#define __local___localdep_mkdir_defined
#define __localdep_mkdir __LIBC_LOCAL_NAME(mkdir)
#endif /* !__local___localdep_mkdir_defined */
#else /* (__CRT_DOS_PRIMARY && __CRT_HAVE__mkdir) || (__AT_FDCWD && (__CRT_HAVE_mkdirat || __CRT_HAVE_fmkdirat)) */
#undef __local_mkdir_defined
#endif /* (!__CRT_DOS_PRIMARY || !__CRT_HAVE__mkdir) && (!__AT_FDCWD || (!__CRT_HAVE_mkdirat && !__CRT_HAVE_fmkdirat)) */
#endif /* !__local_mkdir_defined */
