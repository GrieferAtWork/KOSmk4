/* HASH CRC-32:0x69e0b7b3 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_removeat_defined
#define __local_removeat_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#include <asm/os/errno.h>
#if defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat) && (defined(__AT_REMOVEREG) || (defined(__EISDIR) && defined(__ENOTDIR)))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_unlinkat_defined
#define __local___localdep_unlinkat_defined
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_unlinkat,(__fd_t __dfd, char const *__name, __atflag_t __flags),unlinkat,(__dfd,__name,__flags))
#endif /* !__local___localdep_unlinkat_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(removeat) __ATTR_NONNULL((2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(removeat))(__fd_t __dirfd, char const *__filename) {
#ifdef __AT_REMOVEREG
	return (__NAMESPACE_LOCAL_SYM __localdep_unlinkat)(__dirfd, __filename, __AT_REMOVEREG | __AT_REMOVEDIR);
#else /* __AT_REMOVEREG */
	int __result;
	for (;;) {
		__result = (__NAMESPACE_LOCAL_SYM __localdep_unlinkat)(__dirfd, __filename, 0);
		if (__result == 0 || __libc_geterrno_or(0) != __EISDIR)
			break;
		__result = (__NAMESPACE_LOCAL_SYM __localdep_unlinkat)(__dirfd, __filename, __AT_REMOVEDIR);
		if (__result == 0 || __libc_geterrno_or(0) != __ENOTDIR)
			break;
	}
	return __result;
#endif /* !__AT_REMOVEREG */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_removeat_defined
#define __local___localdep_removeat_defined
#define __localdep_removeat __LIBC_LOCAL_NAME(removeat)
#endif /* !__local___localdep_removeat_defined */
#else /* __AT_REMOVEDIR && __CRT_HAVE_unlinkat && (__AT_REMOVEREG || (__EISDIR && __ENOTDIR)) */
#undef __local_removeat_defined
#endif /* !__AT_REMOVEDIR || !__CRT_HAVE_unlinkat || (!__AT_REMOVEREG && (!__EISDIR || !__ENOTDIR)) */
#endif /* !__local_removeat_defined */
