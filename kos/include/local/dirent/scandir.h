/* HASH CRC-32:0xd4a5a710 */
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
#ifndef __local_scandir_defined
#if defined(__CRT_AT_FDCWD) && ((defined(__CRT_HAVE_scandirat) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))) || (defined(__CRT_HAVE_scandirat64) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))))
#define __local_scandir_defined 1
/* Dependency: "scandirat" */
#ifndef ____localdep_scandirat_defined
#define ____localdep_scandirat_defined 1
#if defined(__CRT_HAVE_scandirat) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* Scan a directory `DIRFD:DIR' for all contained directory entries */
__CREDIRECT(__ATTR_NONNULL((2, 3)),int,__NOTHROW_RPC,__localdep_scandirat,(__fd_t __dirfd, char const *__restrict __dir, struct dirent ***__restrict __namelist, __scandir_selector_t __selector, __scandir_cmp_t __cmp),scandirat,(__dirfd,__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandirat64) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* Scan a directory `DIRFD:DIR' for all contained directory entries */
__CREDIRECT(__ATTR_NONNULL((2, 3)),int,__NOTHROW_RPC,__localdep_scandirat,(__fd_t __dirfd, char const *__restrict __dir, struct dirent ***__restrict __namelist, __scandir_selector_t __selector, __scandir_cmp_t __cmp),scandirat64,(__dirfd,__dir,__namelist,__selector,__cmp))
#else /* LIBC: scandirat */
#undef ____localdep_scandirat_defined
#endif /* scandirat... */
#endif /* !____localdep_scandirat_defined */

__NAMESPACE_LOCAL_BEGIN
/* Scan a directory `DIR' for all contained directory entries */
__LOCAL_LIBC(scandir) __ATTR_NONNULL((1, 2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(scandir))(char const *__restrict __dir,
                                                     struct dirent ***__restrict __namelist,
                                                     __scandir_selector_t __selector,
                                                     __scandir_cmp_t __cmp) {
#line 224 "kos/src/libc/magic/dirent.c"
	return __localdep_scandirat(__CRT_AT_FDCWD, __dir, __namelist, __selector, __cmp);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_AT_FDCWD && ((__CRT_HAVE_scandirat && (!__USE_FILE_OFFSET64 || _DIRENT_MATCHES_DIRENT64)) || (__CRT_HAVE_scandirat64 && (__USE_FILE_OFFSET64 || _DIRENT_MATCHES_DIRENT64))) */
#endif /* !__local_scandir_defined */
