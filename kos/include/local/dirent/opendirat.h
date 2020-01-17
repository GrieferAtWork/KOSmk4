/* HASH CRC-32:0x4fc337dc */
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
#ifdef __CRT_HAVE_fopendirat
#define __local_opendirat_defined 1
/* Dependency: "fopendirat" */
#ifndef ____localdep_fopendirat_defined
#define ____localdep_fopendirat_defined 1
#ifdef __CRT_HAVE_fopendirat
/* Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),DIR *,__NOTHROW_RPC,__localdep_fopendirat,(__fd_t __dirfd, char const *__name, __oflag_t __oflags),fopendirat,(__dirfd,__name,__oflags))
#else /* LIBC: fopendirat */
#undef ____localdep_fopendirat_defined
#endif /* fopendirat... */
#endif /* !____localdep_fopendirat_defined */

__NAMESPACE_LOCAL_BEGIN
/* Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
__LOCAL_LIBC(opendirat) __ATTR_WUNUSED __ATTR_NONNULL((2)) DIR *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(opendirat))(__fd_t __dirfd,
                                                       char const *__name) {
#line 136 "kos/src/libc/magic/dirent.c"
	return __localdep_fopendirat(__dirfd, __name, 0);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_fopendirat */
#endif /* !__local_opendirat_defined */
