/* HASH CRC-32:0x69bf8ae5 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_remove_defined
#define __local_remove_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#include <asm/os/errno.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_removeat) || (defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat) && (defined(__AT_REMOVEREG) || (defined(__EISDIR) && defined(__ENOTDIR)))))) || (defined(__EISDIR) && defined(__ENOTDIR) && (defined(__CRT_HAVE_unlink) || defined(__CRT_HAVE__unlink) || defined(__CRT_HAVE___unlink) || defined(__CRT_HAVE___libc_unlink) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat))) && (defined(__CRT_HAVE_rmdir) || defined(__CRT_HAVE__rmdir) || defined(__CRT_HAVE___rmdir) || defined(__CRT_HAVE___libc_rmdir) || (defined(__AT_FDCWD) && defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_removeat_defined
#define __local___localdep_removeat_defined
#ifdef __CRT_HAVE_removeat
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_RPC,__localdep_removeat,(__fd_t __dirfd, char const *__filename),removeat,(__dirfd,__filename))
#elif defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat) && (defined(__AT_REMOVEREG) || (defined(__EISDIR) && defined(__ENOTDIR)))
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/removeat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_removeat __LIBC_LOCAL_NAME(removeat)
#else /* ... */
#undef __local___localdep_removeat_defined
#endif /* !... */
#endif /* !__local___localdep_removeat_defined */
#ifndef __local___localdep_rmdir_defined
#define __local___localdep_rmdir_defined
#ifdef __CRT_HAVE_rmdir
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_rmdir,(char const *__path),rmdir,(__path))
#elif defined(__CRT_HAVE__rmdir)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_rmdir,(char const *__path),_rmdir,(__path))
#elif defined(__CRT_HAVE___rmdir)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_rmdir,(char const *__path),__rmdir,(__path))
#elif defined(__CRT_HAVE___libc_rmdir)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_rmdir,(char const *__path),__libc_rmdir,(__path))
#elif defined(__AT_FDCWD) && defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/rmdir.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_rmdir __LIBC_LOCAL_NAME(rmdir)
#else /* ... */
#undef __local___localdep_rmdir_defined
#endif /* !... */
#endif /* !__local___localdep_rmdir_defined */
#ifndef __local___localdep_unlink_defined
#define __local___localdep_unlink_defined
#ifdef __CRT_HAVE_unlink
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_unlink,(char const *__file),unlink,(__file))
#elif defined(__CRT_HAVE__unlink)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_unlink,(char const *__file),_unlink,(__file))
#elif defined(__CRT_HAVE___unlink)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_unlink,(char const *__file),__unlink,(__file))
#elif defined(__CRT_HAVE___libc_unlink)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_unlink,(char const *__file),__libc_unlink,(__file))
#elif defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/unlink.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unlink __LIBC_LOCAL_NAME(unlink)
#else /* ... */
#undef __local___localdep_unlink_defined
#endif /* !... */
#endif /* !__local___localdep_unlink_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(remove) __ATTR_IN(1) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(remove))(char const *__filename) {
#if defined(__AT_FDCWD) && (defined(__CRT_HAVE_removeat) || (defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat) && (defined(__AT_REMOVEREG) || (defined(__EISDIR) && defined(__ENOTDIR)))))
	return (__NAMESPACE_LOCAL_SYM __localdep_removeat)(__AT_FDCWD, __filename);
#else /* __AT_FDCWD && (__CRT_HAVE_removeat || (__AT_REMOVEDIR && __CRT_HAVE_unlinkat && (__AT_REMOVEREG || (__EISDIR && __ENOTDIR)))) */
	int __result;
	for (;;) {
		__result = (__NAMESPACE_LOCAL_SYM __localdep_unlink)(__filename);
		if (__result == 0 || __libc_geterrno_or(0) != __EISDIR)
			break;
		__result = (__NAMESPACE_LOCAL_SYM __localdep_rmdir)(__filename);
		if (__result == 0 || __libc_geterrno_or(0) != __ENOTDIR)
			break;
	}
	return __result;
#endif /* !__AT_FDCWD || (!__CRT_HAVE_removeat && (!__AT_REMOVEDIR || !__CRT_HAVE_unlinkat || (!__AT_REMOVEREG && (!__EISDIR || !__ENOTDIR)))) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_remove_defined
#define __local___localdep_remove_defined
#define __localdep_remove __LIBC_LOCAL_NAME(remove)
#endif /* !__local___localdep_remove_defined */
#else /* (__AT_FDCWD && (__CRT_HAVE_removeat || (__AT_REMOVEDIR && __CRT_HAVE_unlinkat && (__AT_REMOVEREG || (__EISDIR && __ENOTDIR))))) || (__EISDIR && __ENOTDIR && (__CRT_HAVE_unlink || __CRT_HAVE__unlink || __CRT_HAVE___unlink || __CRT_HAVE___libc_unlink || (__AT_FDCWD && __CRT_HAVE_unlinkat)) && (__CRT_HAVE_rmdir || __CRT_HAVE__rmdir || __CRT_HAVE___rmdir || __CRT_HAVE___libc_rmdir || (__AT_FDCWD && __AT_REMOVEDIR && __CRT_HAVE_unlinkat))) */
#undef __local_remove_defined
#endif /* (!__AT_FDCWD || (!__CRT_HAVE_removeat && (!__AT_REMOVEDIR || !__CRT_HAVE_unlinkat || (!__AT_REMOVEREG && (!__EISDIR || !__ENOTDIR))))) && (!__EISDIR || !__ENOTDIR || (!__CRT_HAVE_unlink && !__CRT_HAVE__unlink && !__CRT_HAVE___unlink && !__CRT_HAVE___libc_unlink && (!__AT_FDCWD || !__CRT_HAVE_unlinkat)) || (!__CRT_HAVE_rmdir && !__CRT_HAVE__rmdir && !__CRT_HAVE___rmdir && !__CRT_HAVE___libc_rmdir && (!__AT_FDCWD || !__AT_REMOVEDIR || !__CRT_HAVE_unlinkat))) */
#endif /* !__local_remove_defined */
