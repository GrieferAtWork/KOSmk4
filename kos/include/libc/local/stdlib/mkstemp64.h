/* HASH CRC-32:0xbde4d637 */
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
#ifndef __local_mkstemp64_defined
#define __local_mkstemp64_defined
#include <__crt.h>
#include <asm/os/oflags.h>
#include <features.h>
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_mkstemps) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkstemps64) || (defined(__CRT_HAVE_mkostemps) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkostemps64) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mkstemps64_defined
#define __local___localdep_mkstemps64_defined
#if defined(__CRT_HAVE_mkstemps) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__fd_t,__NOTHROW_RPC,__localdep_mkstemps64,(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen),mkstemps,(__template_,__suffixlen))
#elif defined(__CRT_HAVE_mkstemps64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__fd_t,__NOTHROW_RPC,__localdep_mkstemps64,(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen),mkstemps64,(__template_,__suffixlen))
#elif (defined(__CRT_HAVE_mkostemps) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkostemps64) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/mkstemps64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mkstemps64 __LIBC_LOCAL_NAME(mkstemps64)
#else /* ... */
#undef __local___localdep_mkstemps64_defined
#endif /* !... */
#endif /* !__local___localdep_mkstemps64_defined */
__LOCAL_LIBC(mkstemp64) __ATTR_WUNUSED __ATTR_INOUT(1) __fd_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(mkstemp64))(char *__template_) {
	return (__NAMESPACE_LOCAL_SYM __localdep_mkstemps64)(__template_, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mkstemp64_defined
#define __local___localdep_mkstemp64_defined
#define __localdep_mkstemp64 __LIBC_LOCAL_NAME(mkstemp64)
#endif /* !__local___localdep_mkstemp64_defined */
#else /* (__CRT_HAVE_mkstemps && (!__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_mkstemps64 || (__CRT_HAVE_mkostemps && (!__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_mkostemps64 || __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#undef __local_mkstemp64_defined
#endif /* (!__CRT_HAVE_mkstemps || (__O_LARGEFILE && __O_LARGEFILE)) && !__CRT_HAVE_mkstemps64 && (!__CRT_HAVE_mkostemps || (__O_LARGEFILE && __O_LARGEFILE)) && !__CRT_HAVE_mkostemps64 && !__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)) */
#endif /* !__local_mkstemp64_defined */
