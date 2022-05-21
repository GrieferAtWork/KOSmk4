/* HASH CRC-32:0xfd9fddaa */
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
#ifndef __local__conio_getpass_defined
#define __local__conio_getpass_defined
#include <__crt.h>
#include <asm/os/stdio.h>
#if defined(__CRT_HAVE_getpass_r) || defined(__CRT_HAVE_getpassfd) || defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read) || defined(__CRT_HAVE_readpassphrase)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getpass_r_defined
#define __local___localdep_getpass_r_defined
#ifdef __CRT_HAVE_getpass_r
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,char *,__NOTHROW_RPC,__localdep_getpass_r,(char const *__prompt, char *__buf, __SIZE_TYPE__ __bufsize),getpass_r,(__prompt,__buf,__bufsize))
#elif defined(__CRT_HAVE_getpassfd) || defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read) || defined(__CRT_HAVE_readpassphrase)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/getpass_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getpass_r __LIBC_LOCAL_NAME(getpass_r)
#else /* ... */
#undef __local___localdep_getpass_r_defined
#endif /* !... */
#endif /* !__local___localdep_getpass_r_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__LOCAL_LIBC(_conio_getpass) __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_conio_getpass))(const char *__prompt, char *__str) {
	unsigned char __buflen = (unsigned char)__str[0];
	char *__result = (__NAMESPACE_LOCAL_SYM __localdep_getpass_r)(__prompt, &__str[2], __buflen);
	if (__result != __NULLPTR) {
		__str[1] = (unsigned char)(__NAMESPACE_LOCAL_SYM __localdep_strlen)(__result);
		__result = __str;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__conio_getpass_defined
#define __local___localdep__conio_getpass_defined
#define __localdep__conio_getpass __LIBC_LOCAL_NAME(_conio_getpass)
#endif /* !__local___localdep__conio_getpass_defined */
#else /* __CRT_HAVE_getpass_r || __CRT_HAVE_getpassfd || __CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read || __CRT_HAVE_readpassphrase */
#undef __local__conio_getpass_defined
#endif /* !__CRT_HAVE_getpass_r && !__CRT_HAVE_getpassfd && !__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read && !__CRT_HAVE_readpassphrase */
#endif /* !__local__conio_getpass_defined */
