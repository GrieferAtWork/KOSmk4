/* HASH CRC-32:0x308e2d18 */
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_opendirat_defined
#if (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_openat64) || (defined(__CRT_HAVE_openat) && !defined(__USE_FILE_OFFSET64)))) || defined(__CRT_HAVE_fopendirat)
#define __local_opendirat_defined 1
struct __dirstream;
struct __dirstream;
/* Dependency: "fopendirat" from "dirent" */
#ifndef ____localdep_fopendirat_defined
#define ____localdep_fopendirat_defined 1
#ifdef __CRT_HAVE_fopendirat
/* Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),struct __dirstream *,__NOTHROW_RPC,__localdep_fopendirat,(__fd_t __dirfd, char const *__name, __oflag_t __oflags),fopendirat,(__dirfd,__name,__oflags))
#elif defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_openat64) || (defined(__CRT_HAVE_openat) && !defined(__USE_FILE_OFFSET64)))
#include <local/dirent/fopendirat.h>
/* Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
#define __localdep_fopendirat (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fopendirat))
#else /* CUSTOM: fopendirat */
#undef ____localdep_fopendirat_defined
#endif /* fopendirat... */
#endif /* !____localdep_fopendirat_defined */

__NAMESPACE_LOCAL_BEGIN
/* Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
__LOCAL_LIBC(opendirat) __ATTR_WUNUSED __ATTR_NONNULL((2)) struct __dirstream *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(opendirat))(__fd_t __dirfd,
                                                       char const *__name) {
#line 146 "kos/src/libc/magic/dirent.c"
	return __localdep_fopendirat(__dirfd, __name, 0);
}
__NAMESPACE_LOCAL_END
#endif /* (__CRT_HAVE_fdopendir && (__CRT_HAVE_openat64 || (__CRT_HAVE_openat && !__USE_FILE_OFFSET64))) || __CRT_HAVE_fopendirat */
#endif /* !__local_opendirat_defined */
