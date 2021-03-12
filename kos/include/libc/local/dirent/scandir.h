/* HASH CRC-32:0x2cbf74d8 */
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
#ifndef __local_scandir_defined
#define __local_scandir_defined 1
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && ((defined(__CRT_HAVE_scandirat) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))) || (defined(__CRT_HAVE_scandirat64) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))))
#include <features.h>
#include <bits/os/dirent.h>
#ifndef ____scandir_selector_t_defined
#define ____scandir_selector_t_defined 1
typedef int (*__scandir_selector_t)(struct dirent const *);
typedef int (*__scandir_cmp_t)(struct dirent const **, struct dirent const **);
#endif /* !____scandir_selector_t_defined */
__NAMESPACE_LOCAL_BEGIN
/* Dependency: scandirat from dirent */
#ifndef __local___localdep_scandirat_defined
#define __local___localdep_scandirat_defined 1
#if defined(__CRT_HAVE_scandirat) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> scandirat(3), scandirat64(3)
 * Scan a directory `dirfd:dir' for all contained directory entries */
__CREDIRECT(__ATTR_NONNULL((2, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_scandirat,(__fd_t __dirfd, char const *__restrict __dir, struct dirent ***__restrict __namelist, __scandir_selector_t __selector, __scandir_cmp_t __cmp),scandirat,(__dirfd,__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandirat64) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> scandirat(3), scandirat64(3)
 * Scan a directory `dirfd:dir' for all contained directory entries */
__CREDIRECT(__ATTR_NONNULL((2, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_scandirat,(__fd_t __dirfd, char const *__restrict __dir, struct dirent ***__restrict __namelist, __scandir_selector_t __selector, __scandir_cmp_t __cmp),scandirat64,(__dirfd,__dir,__namelist,__selector,__cmp))
#else /* ... */
#undef __local___localdep_scandirat_defined
#endif /* !... */
#endif /* !__local___localdep_scandirat_defined */
/* >> scandir(3), scandir64(3)
 * Scan a directory `dir' for all contained directory entries */
__LOCAL_LIBC(scandir) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(scandir))(char const *__restrict __dir, struct dirent ***__restrict __namelist, __scandir_selector_t __selector, __scandir_cmp_t __cmp) {
	return __localdep_scandirat(__AT_FDCWD, __dir, __namelist, __selector, __cmp);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_scandir_defined
#define __local___localdep_scandir_defined 1
#define __localdep_scandir __LIBC_LOCAL_NAME(scandir)
#endif /* !__local___localdep_scandir_defined */
#else /* __AT_FDCWD && ((__CRT_HAVE_scandirat && (!__USE_FILE_OFFSET64 || _DIRENT_MATCHES_DIRENT64)) || (__CRT_HAVE_scandirat64 && (__USE_FILE_OFFSET64 || _DIRENT_MATCHES_DIRENT64))) */
#undef __local_scandir_defined
#endif /* !__AT_FDCWD || ((!__CRT_HAVE_scandirat || (__USE_FILE_OFFSET64 && !_DIRENT_MATCHES_DIRENT64)) && (!__CRT_HAVE_scandirat64 || (!__USE_FILE_OFFSET64 && !_DIRENT_MATCHES_DIRENT64))) */
#endif /* !__local_scandir_defined */
