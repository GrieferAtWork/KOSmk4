/* HASH CRC-32:0xc33958d2 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strtosigno_defined
#define __local_strtosigno_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strcmp from string */
#ifndef __local___localdep_strcmp_defined
#define __local___localdep_strcmp_defined 1
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcmp.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __localdep_strcmp __LIBC_LOCAL_NAME(strcmp)
#endif /* !... */
#endif /* !__local___localdep_strcmp_defined */
/* Dependency: strsignal_s from string */
#ifndef __local___localdep_strsignal_s_defined
#define __local___localdep_strsignal_s_defined 1
#ifdef __CRT_HAVE_strsignal_s
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_strsignal_s,(__signo_t __signum),strsignal_s,(__signum))
#else /* __CRT_HAVE_strsignal_s */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strsignal_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strsignal_s __LIBC_LOCAL_NAME(strsignal_s)
#endif /* !__CRT_HAVE_strsignal_s */
#endif /* !__local___localdep_strsignal_s_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/signal.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strtosigno(3)
 * Return the signal number for a given name.
 * e.g. `strtosigno("SIGINT") == SIGINT' */
__LOCAL_LIBC(strtosigno) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __signo_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtosigno))(const char *__name) {
	__signo_t __i, __result = 0;
	if __likely(__name) {
		for (__i = 1; __i < __NSIG; ++__i) {
			char const *__s = __localdep_strsignal_s(__i);
			if (__likely(__s) && __localdep_strcmp(__s, __name) == 0) {
				__result = __i;
				break;
			}
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtosigno_defined
#define __local___localdep_strtosigno_defined 1
#define __localdep_strtosigno __LIBC_LOCAL_NAME(strtosigno)
#endif /* !__local___localdep_strtosigno_defined */
#endif /* !__local_strtosigno_defined */
