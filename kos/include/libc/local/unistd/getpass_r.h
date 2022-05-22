/* HASH CRC-32:0xe4401dbc */
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
#ifndef __local_getpass_r_defined
#define __local_getpass_r_defined
#include <__crt.h>
#include <asm/os/stdio.h>
#if defined(__CRT_HAVE_getpassfd) || defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read) || defined(__CRT_HAVE_readpassphrase)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getpassfd_defined
#define __local___localdep_getpassfd_defined
#ifdef __CRT_HAVE_getpassfd
__NAMESPACE_LOCAL_END
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN_OPT(1) __ATTR_IN_OPT(4) __ATTR_OUT_OPT(2),char *,__NOTHROW_RPC,__localdep_getpassfd,(char const *__prompt, char *__buf, __SIZE_TYPE__ __buflen, __fd_t __fds[3], __STDC_INT_AS_UINT_T __flags, int __timeout_in_seconds),getpassfd,(__prompt,__buf,__buflen,__fds,__flags,__timeout_in_seconds))
#elif defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/getpassfd.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getpassfd __LIBC_LOCAL_NAME(getpassfd)
#else /* ... */
#undef __local___localdep_getpassfd_defined
#endif /* !... */
#endif /* !__local___localdep_getpassfd_defined */
#ifndef __local___localdep_readpassphrase_defined
#define __local___localdep_readpassphrase_defined
#ifdef __CRT_HAVE_readpassphrase
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(1) __ATTR_OUTS(2, 3),char *,__NOTHROW_NCX,__localdep_readpassphrase,(char const *__prompt, char *__buf, __SIZE_TYPE__ __bufsize, __STDC_INT_AS_UINT_T __flags),readpassphrase,(__prompt,__buf,__bufsize,__flags))
#elif defined(__STDIN_FILENO) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read))
__NAMESPACE_LOCAL_END
#include <libc/local/readpassphrase/readpassphrase.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_readpassphrase __LIBC_LOCAL_NAME(readpassphrase)
#else /* ... */
#undef __local___localdep_readpassphrase_defined
#endif /* !... */
#endif /* !__local___localdep_readpassphrase_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/getpassfd.h>
#include <asm/crt/readpassphrase.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getpass_r) __ATTR_WUNUSED __ATTR_IN_OPT(1) __ATTR_OUT_OPT(2) char *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(getpass_r))(char const *__prompt, char *__buf, __SIZE_TYPE__ __bufsize) {
#if defined(__CRT_HAVE_getpassfd) || defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)
	/* Prefer using `getpassfd(3)' because I feel like that one's more
	 * user-friendly.  - But if it's not available, fall back on using
	 * the regular, old `readpassphrase(3)' */
#ifdef __GETPASS_ECHO_NL
	return (__NAMESPACE_LOCAL_SYM __localdep_getpassfd)(__prompt, __buf, __bufsize, __NULLPTR, __GETPASS_ECHO_NL, 0);
#else /* __GETPASS_ECHO_NL */
	return (__NAMESPACE_LOCAL_SYM __localdep_getpassfd)(__prompt, __buf, __bufsize, __NULLPTR, 0, 0);
#endif /* !__GETPASS_ECHO_NL */
#else /* __CRT_HAVE_getpassfd || __CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read */
#ifdef __RPP_ECHO_OFF
	return (__NAMESPACE_LOCAL_SYM __localdep_readpassphrase)(__prompt, __buf, __bufsize, __RPP_ECHO_OFF);
#else /* __RPP_ECHO_OFF */
	return (__NAMESPACE_LOCAL_SYM __localdep_readpassphrase)(__prompt, __buf, __bufsize, 0);
#endif /* !__RPP_ECHO_OFF */
#endif /* !__CRT_HAVE_getpassfd && !__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getpass_r_defined
#define __local___localdep_getpass_r_defined
#define __localdep_getpass_r __LIBC_LOCAL_NAME(getpass_r)
#endif /* !__local___localdep_getpass_r_defined */
#else /* __CRT_HAVE_getpassfd || __CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read || __CRT_HAVE_readpassphrase */
#undef __local_getpass_r_defined
#endif /* !__CRT_HAVE_getpassfd && !__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read && !__CRT_HAVE_readpassphrase */
#endif /* !__local_getpass_r_defined */
