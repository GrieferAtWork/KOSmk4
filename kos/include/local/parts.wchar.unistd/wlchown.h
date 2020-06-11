/* HASH CRC-32:0x35f76243 */
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
#ifndef __local_wlchown_defined
#define __local_wlchown_defined 1
#include <__crt.h>
#if defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_wfchownat) || (defined(__CRT_HAVE_DOS$wfchownat) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$wfchownat) && __SIZEOF_WCHAR_T__ == 2))
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wfchownat from parts.wchar.unistd */
#ifndef __local___localdep_wfchownat_defined
#define __local___localdep_wfchownat_defined 1
#ifdef __CRT_HAVE_wfchownat
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_wfchownat,(__fd_t __dfd, __WCHAR_TYPE__ const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),wfchownat,(__dfd,__file,__owner,__group,__flags))
#elif defined(__CRT_HAVE_DOS$wfchownat) && __SIZEOF_WCHAR_T__ == 4
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBCCALL,__localdep_wfchownat,(__fd_t __dfd, __WCHAR_TYPE__ const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),KOS$wfchownat,(__dfd,__file,__owner,__group,__flags))
#elif defined(__CRT_HAVE_DOS$wfchownat) && __SIZEOF_WCHAR_T__ == 2
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBCCALL,__localdep_wfchownat,(__fd_t __dfd, __WCHAR_TYPE__ const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),DOS$wfchownat,(__dfd,__file,__owner,__group,__flags))
#else /* ... */
#undef __local___localdep_wfchownat_defined
#endif /* !... */
#endif /* !__local___localdep_wfchownat_defined */
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__LOCAL_LIBC(wlchown) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wlchown))(__WCHAR_TYPE__ const *__file, __uid_t __owner, __gid_t __group) {
	return __localdep_wfchownat(__CRT_AT_FDCWD, __file, __owner, __group, 0x0100); /* AT_SYMLINK_NOFOLLOW */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wlchown_defined
#define __local___localdep_wlchown_defined 1
#define __localdep_wlchown __LIBC_LOCAL_NAME(wlchown)
#endif /* !__local___localdep_wlchown_defined */
#else /* __CRT_AT_FDCWD && (__CRT_HAVE_wfchownat || (__CRT_HAVE_DOS$wfchownat && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$wfchownat && __SIZEOF_WCHAR_T__ == 2)) */
#undef __local_wlchown_defined
#endif /* !__CRT_AT_FDCWD || (!__CRT_HAVE_wfchownat && (!__CRT_HAVE_DOS$wfchownat || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$wfchownat || !__SIZEOF_WCHAR_T__ == 2)) */
#endif /* !__local_wlchown_defined */
