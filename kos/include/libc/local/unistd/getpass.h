/* HASH CRC-32:0x9646cf1b */
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
#ifndef __local_getpass_defined
#define __local_getpass_defined 1
#include <__crt.h>
#include <asm/os/stdio.h>
#if defined(__CRT_HAVE_readpassphrase) || (defined(__STDIN_FILENO) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)))
__NAMESPACE_LOCAL_BEGIN
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
__CREDIRECT(__ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_readpassphrase,(char const *__prompt, char *__buf, __SIZE_TYPE__ __bufsize, __STDC_INT_AS_UINT_T __flags),readpassphrase,(__prompt,__buf,__bufsize,__flags))
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
#include <asm/crt/readpassphrase.h>
__NAMESPACE_LOCAL_BEGIN
/* >> getpass(3) */
__LOCAL_LIBC(getpass) __ATTR_WUNUSED __ATTR_NONNULL((1)) char *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(getpass))(char const *__restrict __prompt) {
	static char __buf[129]; /* 129 == _PASSWORD_LEN + 1 */
#ifdef __RPP_ECHO_OFF
	return __localdep_readpassphrase(__prompt, __buf, sizeof(__buf), __RPP_ECHO_OFF);
#else /* __RPP_ECHO_OFF */
	return __localdep_readpassphrase(__prompt, __buf, sizeof(__buf), 0);
#endif /* !__RPP_ECHO_OFF */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getpass_defined
#define __local___localdep_getpass_defined 1
#define __localdep_getpass __LIBC_LOCAL_NAME(getpass)
#endif /* !__local___localdep_getpass_defined */
#else /* __CRT_HAVE_readpassphrase || (__STDIN_FILENO && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read)) */
#undef __local_getpass_defined
#endif /* !__CRT_HAVE_readpassphrase && (!__STDIN_FILENO || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read)) */
#endif /* !__local_getpass_defined */
