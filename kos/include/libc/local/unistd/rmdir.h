/* HASH CRC-32:0x2eaa9e */
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
#ifndef __local_rmdir_defined
#define __local_rmdir_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_unlinkat_defined
#define __local___localdep_unlinkat_defined
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_RPC,__localdep_unlinkat,(__fd_t __dfd, char const *__name, __atflag_t __flags),unlinkat,(__dfd,__name,__flags))
#endif /* !__local___localdep_unlinkat_defined */
__LOCAL_LIBC(rmdir) __ATTR_IN(1) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(rmdir))(char const *__path) {
	return (__NAMESPACE_LOCAL_SYM __localdep_unlinkat)(__AT_FDCWD, __path, __AT_REMOVEDIR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_rmdir_defined
#define __local___localdep_rmdir_defined
#define __localdep_rmdir __LIBC_LOCAL_NAME(rmdir)
#endif /* !__local___localdep_rmdir_defined */
#else /* __AT_FDCWD && __AT_REMOVEDIR && __CRT_HAVE_unlinkat */
#undef __local_rmdir_defined
#endif /* !__AT_FDCWD || !__AT_REMOVEDIR || !__CRT_HAVE_unlinkat */
#endif /* !__local_rmdir_defined */
