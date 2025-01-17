/* HASH CRC-32:0x77eb766 */
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
#ifndef __local_rename_defined
#define __local_rename_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && (defined(__CRT_HAVE_renameat) || defined(__CRT_HAVE_renameat2))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_renameat_defined
#define __local___localdep_renameat_defined
#ifdef __CRT_HAVE_renameat
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2) __ATTR_IN(4),int,__NOTHROW_RPC,__localdep_renameat,(__fd_t __oldfd, char const *__oldname, __fd_t __newfd, char const *__newname_or_path),renameat,(__oldfd,__oldname,__newfd,__newname_or_path))
#elif defined(__CRT_HAVE_renameat2)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/renameat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_renameat __LIBC_LOCAL_NAME(renameat)
#else /* ... */
#undef __local___localdep_renameat_defined
#endif /* !... */
#endif /* !__local___localdep_renameat_defined */
__LOCAL_LIBC(rename) __ATTR_IN(1) __ATTR_IN(2) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(rename))(char const *__oldname, char const *__newname_or_path) {
	return (__NAMESPACE_LOCAL_SYM __localdep_renameat)(__AT_FDCWD, __oldname, __AT_FDCWD, __newname_or_path);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_rename_defined
#define __local___localdep_rename_defined
#define __localdep_rename __LIBC_LOCAL_NAME(rename)
#endif /* !__local___localdep_rename_defined */
#else /* __AT_FDCWD && (__CRT_HAVE_renameat || __CRT_HAVE_renameat2) */
#undef __local_rename_defined
#endif /* !__AT_FDCWD || (!__CRT_HAVE_renameat && !__CRT_HAVE_renameat2) */
#endif /* !__local_rename_defined */
