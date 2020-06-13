/* HASH CRC-32:0x6aad3364 */
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
#ifndef __local_euidaccess_defined
#define __local_euidaccess_defined 1
#include <__crt.h>
#include <asm/fcntl.h>
#if defined(__CRT_AT_FDCWD) && defined(__AT_EACCESS) && defined(__CRT_HAVE_faccessat)
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: faccessat from unistd */
#if !defined(__local___localdep_faccessat_defined) && defined(__CRT_HAVE_faccessat)
#define __local___localdep_faccessat_defined 1
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_faccessat,(__fd_t __dfd, char const *__file, __STDC_INT_AS_UINT_T __type, __atflag_t __flags),faccessat,(__dfd,__file,__type,__flags))
#endif /* !__local___localdep_faccessat_defined && __CRT_HAVE_faccessat */
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__LOCAL_LIBC(euidaccess) __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(euidaccess))(char const *__file, __STDC_INT_AS_UINT_T __type) {
	return __localdep_faccessat(__CRT_AT_FDCWD, __file, __type, __AT_EACCESS);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_euidaccess_defined
#define __local___localdep_euidaccess_defined 1
#define __localdep_euidaccess __LIBC_LOCAL_NAME(euidaccess)
#endif /* !__local___localdep_euidaccess_defined */
#else /* __CRT_AT_FDCWD && __AT_EACCESS && __CRT_HAVE_faccessat */
#undef __local_euidaccess_defined
#endif /* !__CRT_AT_FDCWD || !__AT_EACCESS || !__CRT_HAVE_faccessat */
#endif /* !__local_euidaccess_defined */
