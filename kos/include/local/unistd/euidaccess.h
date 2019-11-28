/* HASH CRC-32:0x2d36a3a7 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef __local_euidaccess_defined
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_faccessat)
#define __local_euidaccess_defined 1
/* Dependency: "faccessat" */
#ifndef ____localdep_faccessat_defined
#define ____localdep_faccessat_defined 1
#ifdef __CRT_HAVE_faccessat
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_faccessat,(__fd_t __dfd, char const *__file, int __type, __atflag_t __flags),faccessat,(__dfd,__file,__type,__flags))
#else /* LIBC: faccessat */
#undef ____localdep_faccessat_defined
#endif /* faccessat... */
#endif /* !____localdep_faccessat_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__LOCAL_LIBC(euidaccess) __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(euidaccess))(char const *__file,
                                                        int __type) {
#line 732 "kos/src/libc/magic/unistd.c"
	return __localdep_faccessat(__CRT_AT_FDCWD, __file, __type, 0x0200); /* AT_EACCESS */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_AT_FDCWD && __CRT_HAVE_faccessat */
#endif /* !__local_euidaccess_defined */
