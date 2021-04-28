/* HASH CRC-32:0xb355a075 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_getpass_r_defined
#define __local_getpass_r_defined 1
#include <__crt.h>
#include <asm/os/stdio.h>
#if defined(__CRT_HAVE_getpassfd) || defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE_readpassphrase)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: getpassfd from unistd */
#ifndef __local___localdep_getpassfd_defined
#define __local___localdep_getpassfd_defined 1
#ifdef __CRT_HAVE_getpassfd
__NAMESPACE_LOCAL_END
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> getpassfd(3)
 * This function behaves similar to `readpassphrase(3)', but is still
 * quite distinct from that function in how this one behaves, vs. how
 * that other function behaves. In general, this function is a bit more
 * user-friendly, in that it offers more (but different) `flags' to
 * control how the password prompt is generated, with the main advantage
 * of this function being that it implements some "advanced" readline
 * functionality, such as deleting typed characters without relying on
 * the system TTY canonical buffer (which `readpassphrase(3)' needs,
 * since it doesn't include support for _any_ control characters other
 * that CR/LF as indicators to stop reading text)
 * Which of the 2 functions should be used is a matter of taste, but
 * personally, I prefer this one over `readpassphrase(3)'.
 * @param: prompt:  [0..1]      Text-prompt to display to the user, or `NULL'
 * @param: buf:     [0..buflen] Buffer that will receive the user's password.
 *                              When set to `NULL', a dynamically allocated
 *                              buffer will be used and returned.
 * @param: buflen:              Size of `buf' (in characters) (ignored when `buf == NULL')
 * @param: fds:     [0..1]      When non-NULL, an [stdin,stdout,stderr] triple
 *                              of files, used for [read,write,beep] operations.
 *                              When `NULL', try to use `/dev/tty' instead, and
 *                              if that fails, use `STDIN_FILENO,STDERR_FILENO,
 *                              STDERR_FILENO' as final fallback.
 *                              When `GETPASS_NEED_TTY' is set, the function
 *                              will fail with `errno=ENOTTY' if the actually
 *                              used `fds[0]' (iow: stdin) isn't a TTY device
 *                              s.a. `isatty(3)'
 * @param: flags:               Set of `GETPASS_*' flags (from <unistd.h>)
 * @param: timeout_in_seconds:  When non-0, timeout (in seconds) to wait for the
 *                              user to type each character of their password. If
 *                              this timeout expires, fail with `errno=ETIMEDOUT'
 *                              Negative values result in weak undefined behavior.
 * @return: * :   [buf == NULL] Success (dynamically allocated buffer; must be `free(3)'d)
 * @return: buf:                Success
 * @return: NULL: [ETIMEDOUT]   The given `timeout_in_seconds' has expired.
 * @return: NULL: [EINVAL]      `buf' is non-`NULL', but `buflen' is `0'
 * @return: NULL: [ENOTTY]      `GETPASS_NEED_TTY' was given, but not a tty
 * @return: NULL: [ENOMEM]      Insufficient memory
 * @return: NULL: [ENODATA]     End-of-file while reading, and `GETPASS_FAIL_EOF' was set.
 * @return: NULL: [*]           Error */
__CREDIRECT(__ATTR_WUNUSED,char *,__NOTHROW_RPC,__localdep_getpassfd,(char const *__prompt, char *__buf, __SIZE_TYPE__ __buflen, __fd_t __fds[3], __STDC_INT_AS_UINT_T __flags, int __timeout_in_seconds),getpassfd,(__prompt,__buf,__buflen,__fds,__flags,__timeout_in_seconds))
#elif defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/getpassfd.h>
__NAMESPACE_LOCAL_BEGIN
/* >> getpassfd(3)
 * This function behaves similar to `readpassphrase(3)', but is still
 * quite distinct from that function in how this one behaves, vs. how
 * that other function behaves. In general, this function is a bit more
 * user-friendly, in that it offers more (but different) `flags' to
 * control how the password prompt is generated, with the main advantage
 * of this function being that it implements some "advanced" readline
 * functionality, such as deleting typed characters without relying on
 * the system TTY canonical buffer (which `readpassphrase(3)' needs,
 * since it doesn't include support for _any_ control characters other
 * that CR/LF as indicators to stop reading text)
 * Which of the 2 functions should be used is a matter of taste, but
 * personally, I prefer this one over `readpassphrase(3)'.
 * @param: prompt:  [0..1]      Text-prompt to display to the user, or `NULL'
 * @param: buf:     [0..buflen] Buffer that will receive the user's password.
 *                              When set to `NULL', a dynamically allocated
 *                              buffer will be used and returned.
 * @param: buflen:              Size of `buf' (in characters) (ignored when `buf == NULL')
 * @param: fds:     [0..1]      When non-NULL, an [stdin,stdout,stderr] triple
 *                              of files, used for [read,write,beep] operations.
 *                              When `NULL', try to use `/dev/tty' instead, and
 *                              if that fails, use `STDIN_FILENO,STDERR_FILENO,
 *                              STDERR_FILENO' as final fallback.
 *                              When `GETPASS_NEED_TTY' is set, the function
 *                              will fail with `errno=ENOTTY' if the actually
 *                              used `fds[0]' (iow: stdin) isn't a TTY device
 *                              s.a. `isatty(3)'
 * @param: flags:               Set of `GETPASS_*' flags (from <unistd.h>)
 * @param: timeout_in_seconds:  When non-0, timeout (in seconds) to wait for the
 *                              user to type each character of their password. If
 *                              this timeout expires, fail with `errno=ETIMEDOUT'
 *                              Negative values result in weak undefined behavior.
 * @return: * :   [buf == NULL] Success (dynamically allocated buffer; must be `free(3)'d)
 * @return: buf:                Success
 * @return: NULL: [ETIMEDOUT]   The given `timeout_in_seconds' has expired.
 * @return: NULL: [EINVAL]      `buf' is non-`NULL', but `buflen' is `0'
 * @return: NULL: [ENOTTY]      `GETPASS_NEED_TTY' was given, but not a tty
 * @return: NULL: [ENOMEM]      Insufficient memory
 * @return: NULL: [ENODATA]     End-of-file while reading, and `GETPASS_FAIL_EOF' was set.
 * @return: NULL: [*]           Error */
#define __localdep_getpassfd __LIBC_LOCAL_NAME(getpassfd)
#else /* ... */
#undef __local___localdep_getpassfd_defined
#endif /* !... */
#endif /* !__local___localdep_getpassfd_defined */
/* Dependency: readpassphrase from readpassphrase */
#ifndef __local___localdep_readpassphrase_defined
#define __local___localdep_readpassphrase_defined 1
#ifdef __CRT_HAVE_readpassphrase
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* >> readpassphrase(3)
 * @param: flags: Set of `RPP_*' (from `<readpassphrase.h>')
 * @return: buf:  Success
 * @return: NULL: Error (s.a. `errno') */
__CREDIRECT(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,__localdep_readpassphrase,(char const *__prompt, char *__buf, __SIZE_TYPE__ __bufsize, __STDC_INT_AS_UINT_T __flags),readpassphrase,(__prompt,__buf,__bufsize,__flags))
#elif defined(__STDIN_FILENO) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read))
__NAMESPACE_LOCAL_END
#include <libc/local/readpassphrase/readpassphrase.h>
__NAMESPACE_LOCAL_BEGIN
/* >> readpassphrase(3)
 * @param: flags: Set of `RPP_*' (from `<readpassphrase.h>')
 * @return: buf:  Success
 * @return: NULL: Error (s.a. `errno') */
#define __localdep_readpassphrase __LIBC_LOCAL_NAME(readpassphrase)
#else /* ... */
#undef __local___localdep_readpassphrase_defined
#endif /* !... */
#endif /* !__local___localdep_readpassphrase_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/getpassfd.h>
#include <asm/crt/readpassphrase.h>
__NAMESPACE_LOCAL_BEGIN
/* >> getpass_r(3) */
__LOCAL_LIBC(getpass_r) __ATTR_WUNUSED char *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(getpass_r))(char const *__prompt, char *__buf, __SIZE_TYPE__ __bufsize) {
#if defined(__CRT_HAVE_getpassfd) || defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)
	/* Prefer using `getpassfd(3)' because I feel like that one's more
	 * user-friendly.  - But it it's not available, fall back on using
	 * the regular, old `readpassphrase(3)' */
#ifdef __GETPASS_ECHO_NL
	return __localdep_getpassfd(__prompt, __buf, __bufsize, __NULLPTR, __GETPASS_ECHO_NL, 0);
#else /* __GETPASS_ECHO_NL */
	return __localdep_getpassfd(__prompt, __buf, __bufsize, __NULLPTR, 0, 0);
#endif /* !__GETPASS_ECHO_NL */
#else /* __CRT_HAVE_getpassfd || __CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read */
#ifdef __RPP_ECHO_OFF
	return __localdep_readpassphrase(__prompt, __buf, __bufsize, __RPP_ECHO_OFF);
#else /* __RPP_ECHO_OFF */
	return __localdep_readpassphrase(__prompt, __buf, __bufsize, 0);
#endif /* !__RPP_ECHO_OFF */
#endif /* !__CRT_HAVE_getpassfd && !__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getpass_r_defined
#define __local___localdep_getpass_r_defined 1
#define __localdep_getpass_r __LIBC_LOCAL_NAME(getpass_r)
#endif /* !__local___localdep_getpass_r_defined */
#else /* __CRT_HAVE_getpassfd || __CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE_readpassphrase */
#undef __local_getpass_r_defined
#endif /* !__CRT_HAVE_getpassfd && !__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE_readpassphrase */
#endif /* !__local_getpass_r_defined */
