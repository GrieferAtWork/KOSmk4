/* HASH CRC-32:0x43ad696 */
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
#ifndef __local_c32chown_defined
#define __local_c32chown_defined 1
#include <__crt.h>
#if defined(__CRT_AT_FDCWD) && ((defined(__CRT_HAVE_wfchownat) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || (defined(__CRT_HAVE_DOS$wfchownat) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$KOS$wfchownat))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32fchownat from parts.uchar.unistd */
#ifndef __local___localdep_c32fchownat_defined
#define __local___localdep_c32fchownat_defined 1
#if defined(__CRT_HAVE_wfchownat) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBKCALL,__localdep_c32fchownat,(__fd_t __dfd, __CHAR32_TYPE__ const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),wfchownat,(__dfd,__file,__owner,__group,__flags))
#elif defined(__CRT_HAVE_DOS$wfchownat) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_c32fchownat,(__fd_t __dfd, __CHAR32_TYPE__ const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),wfchownat,(__dfd,__file,__owner,__group,__flags))
#elif defined(__CRT_HAVE_DOS$KOS$wfchownat)
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_c32fchownat,(__fd_t __dfd, __CHAR32_TYPE__ const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),KOS$wfchownat,(__dfd,__file,__owner,__group,__flags))
#else /* ... */
#undef __local___localdep_c32fchownat_defined
#endif /* !... */
#endif /* !__local___localdep_c32fchownat_defined */
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__LOCAL_LIBC(c32chown) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBKCALL __LIBC_LOCAL_NAME(c32chown))(__CHAR32_TYPE__ const *__file, __uid_t __owner, __gid_t __group) {
	return __localdep_c32fchownat(__CRT_AT_FDCWD, __file, __owner, __group, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32chown_defined
#define __local___localdep_c32chown_defined 1
#define __localdep_c32chown __LIBC_LOCAL_NAME(c32chown)
#endif /* !__local___localdep_c32chown_defined */
#else /* __CRT_AT_FDCWD && ((__CRT_HAVE_wfchownat && (__SIZEOF_WCHAR_T__ == 4) && __LIBCCALL_IS_LIBKCALL) || (__CRT_HAVE_DOS$wfchownat && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_DOS$KOS$wfchownat) */
#undef __local_c32chown_defined
#endif /* !__CRT_AT_FDCWD || ((!__CRT_HAVE_wfchownat || !(__SIZEOF_WCHAR_T__ == 4) || !__LIBCCALL_IS_LIBKCALL) && (!__CRT_HAVE_DOS$wfchownat || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_DOS$KOS$wfchownat) */
#endif /* !__local_c32chown_defined */
