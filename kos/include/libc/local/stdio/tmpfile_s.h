/* HASH CRC-32:0x73b8f343 */
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
#ifndef __local_tmpfile_s_defined
#define __local_tmpfile_s_defined
#include <__crt.h>
#include <asm/os/oflags.h>
#if (defined(__CRT_HAVE_tmpfile) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_tmpfile64)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_tmpfile64_defined
#define __local___localdep_tmpfile64_defined
#if defined(__CRT_HAVE_tmpfile) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_RPC,__localdep_tmpfile64,(void),tmpfile,())
#elif defined(__CRT_HAVE_tmpfile64)
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_RPC,__localdep_tmpfile64,(void),tmpfile64,())
#else /* ... */
#undef __local___localdep_tmpfile64_defined
#endif /* !... */
#endif /* !__local___localdep_tmpfile64_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(tmpfile_s) __ATTR_OUT(1) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(tmpfile_s))(__FILE **__pstream) {
	if (!__pstream) {
#ifdef __EINVAL
		return __EINVAL;
#else /* __EINVAL */
		return 1;
#endif /* !__EINVAL */
	}
	*__pstream = (__NAMESPACE_LOCAL_SYM __localdep_tmpfile64)();
	if (!*__pstream) {
#ifdef __ENOMEM
		return __libc_geterrno_or(__ENOMEM);
#else /* __ENOMEM */
		return __libc_geterrno_or(1);
#endif /* !__ENOMEM */
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tmpfile_s_defined
#define __local___localdep_tmpfile_s_defined
#define __localdep_tmpfile_s __LIBC_LOCAL_NAME(tmpfile_s)
#endif /* !__local___localdep_tmpfile_s_defined */
#else /* (__CRT_HAVE_tmpfile && (!__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_tmpfile64 */
#undef __local_tmpfile_s_defined
#endif /* (!__CRT_HAVE_tmpfile || (__O_LARGEFILE && __O_LARGEFILE)) && !__CRT_HAVE_tmpfile64 */
#endif /* !__local_tmpfile_s_defined */
