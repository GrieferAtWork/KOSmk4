/* HASH CRC-32:0x6349a3c5 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__chdrive_defined
#define __local__chdrive_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_fchdir) || defined(__CRT_HAVE___fchdir) || defined(__CRT_HAVE___libc_fchdir)) && defined(__AT_FDDRIVE_ROOT)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fchdir_defined
#define __local___localdep_fchdir_defined
#ifdef __CRT_HAVE_fchdir
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_RPC,__localdep_fchdir,(__fd_t __fd),fchdir,(__fd))
#elif defined(__CRT_HAVE___fchdir)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_RPC,__localdep_fchdir,(__fd_t __fd),__fchdir,(__fd))
#elif defined(__CRT_HAVE___libc_fchdir)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_RPC,__localdep_fchdir,(__fd_t __fd),__libc_fchdir,(__fd))
#else /* ... */
#undef __local___localdep_fchdir_defined
#endif /* !... */
#endif /* !__local___localdep_fchdir_defined */
#ifndef __local___localdep_toupper_defined
#define __local___localdep_toupper_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_toupper) && defined(__CRT_HAVE_toupper)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_toupper,(int __ch),toupper,{ return __crt_toupper(__ch); })
#elif defined(__crt_toupper)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_toupper)(int __ch) { return __crt_toupper(__ch); }
#elif __has_builtin(__builtin_toupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_toupper)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_toupper,(int __ch),toupper,{ return __builtin_toupper(__ch); })
#elif defined(__CRT_HAVE_toupper)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_toupper,(int __ch),toupper,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/toupper.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_toupper __LIBC_LOCAL_NAME(toupper)
#endif /* !... */
#endif /* !__local___localdep_toupper_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_chdrive) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_chdrive))(int __drive) {
	__drive = (unsigned char)(__NAMESPACE_LOCAL_SYM __localdep_toupper)((unsigned char)__drive);
	if __unlikely(__drive < __AT_DOS_DRIVEMIN || __drive > __AT_DOS_DRIVEMAX) {
#ifdef __EINVAL
		return __libc_seterrno(__EINVAL);
#else /* __EINVAL */
		return __libc_seterrno(1);
#endif /* !__EINVAL */
	}
	return (__NAMESPACE_LOCAL_SYM __localdep_fchdir)(__AT_FDDRIVE_ROOT(__drive));
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__chdrive_defined
#define __local___localdep__chdrive_defined
#define __localdep__chdrive __LIBC_LOCAL_NAME(_chdrive)
#endif /* !__local___localdep__chdrive_defined */
#else /* (__CRT_HAVE_fchdir || __CRT_HAVE___fchdir || __CRT_HAVE___libc_fchdir) && __AT_FDDRIVE_ROOT */
#undef __local__chdrive_defined
#endif /* (!__CRT_HAVE_fchdir && !__CRT_HAVE___fchdir && !__CRT_HAVE___libc_fchdir) || !__AT_FDDRIVE_ROOT */
#endif /* !__local__chdrive_defined */
