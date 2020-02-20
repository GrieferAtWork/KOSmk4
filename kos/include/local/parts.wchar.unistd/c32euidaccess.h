/* HASH CRC-32:0x827a9a8 */
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
#ifndef __local_c32euidaccess_defined
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wfaccessat)
#define __local_c32euidaccess_defined 1
/* Dependency: "wfaccessat" from "parts.wchar.unistd" */
#ifndef ____localdep_c32faccessat_defined
#define ____localdep_c32faccessat_defined 1
#if defined(__CRT_HAVE_wfaccessat) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32faccessat(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_c32faccessat,(__fd_t __dfd, __CHAR32_TYPE__ const *__file, int __type, __atflag_t __flags),wfaccessat,(__dfd,__file,__type,__flags))
#else /* LIBC: wfaccessat */
#undef ____localdep_c32faccessat_defined
#endif /* c32faccessat... */
#endif /* !____localdep_c32faccessat_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> c32euidaccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__LOCAL_LIBC(c32euidaccess) __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(c32euidaccess))(__CHAR32_TYPE__ const *__file,
                                                           int __type) {
#line 732 "kos/src/libc/magic/unistd.c"
	return __localdep_c32faccessat(__CRT_AT_FDCWD, __file, __type, 0x0200); /* AT_EACCESS */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_AT_FDCWD && __CRT_HAVE_wfaccessat */
#endif /* !__local_c32euidaccess_defined */
