/* HASH CRC-32:0xe362ec99 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_opendirat_defined
#define __local_opendirat_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_fopendirat) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
struct __dirstream;
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fopendirat from dirent */
#ifndef __local___localdep_fopendirat_defined
#define __local___localdep_fopendirat_defined 1
#ifdef __CRT_HAVE_fopendirat
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> fopendirat(3)
 * Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),struct __dirstream *,__NOTHROW_RPC,__localdep_fopendirat,(__fd_t __dirfd, char const *__name, __oflag_t __oflags),fopendirat,(__dirfd,__name,__oflags))
#elif defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))
__NAMESPACE_LOCAL_END
#include <libc/local/dirent/fopendirat.h>
__NAMESPACE_LOCAL_BEGIN
/* >> fopendirat(3)
 * Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
#define __localdep_fopendirat __LIBC_LOCAL_NAME(fopendirat)
#else /* ... */
#undef __local___localdep_fopendirat_defined
#endif /* !... */
#endif /* !__local___localdep_fopendirat_defined */
/* >> opendirat(3)
 * Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
__LOCAL_LIBC(opendirat) __ATTR_WUNUSED __ATTR_NONNULL((2)) struct __dirstream *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(opendirat))(__fd_t __dirfd, char const *__name) {
	return __localdep_fopendirat(__dirfd, __name, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_opendirat_defined
#define __local___localdep_opendirat_defined 1
#define __localdep_opendirat __LIBC_LOCAL_NAME(opendirat)
#endif /* !__local___localdep_opendirat_defined */
#else /* __CRT_HAVE_fopendirat || (__CRT_HAVE_fdopendir && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#undef __local_opendirat_defined
#endif /* !__CRT_HAVE_fopendirat && (!__CRT_HAVE_fdopendir || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)) */
#endif /* !__local_opendirat_defined */
