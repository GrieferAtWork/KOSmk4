/* HASH CRC-32:0x5ae94475 */
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
#ifndef __local_strtosigno_defined
#define __local_strtosigno_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: sigabbrev_np from string */
#ifndef __local___localdep_sigabbrev_np_defined
#define __local___localdep_sigabbrev_np_defined 1
#ifdef __CRT_HAVE_sigabbrev_np
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sigabbrev_np(3)
 * Return the name of a given signal, without the leading `SIG*' prefix.
 * If the given `signum' isn't recognized, return `NULL' instead. */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_sigabbrev_np,(__signo_t __signum),sigabbrev_np,(__signum))
#elif defined(__CRT_HAVE_signalname)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sigabbrev_np(3)
 * Return the name of a given signal, without the leading `SIG*' prefix.
 * If the given `signum' isn't recognized, return `NULL' instead. */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_sigabbrev_np,(__signo_t __signum),signalname,(__signum))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/sigabbrev_np.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sigabbrev_np(3)
 * Return the name of a given signal, without the leading `SIG*' prefix.
 * If the given `signum' isn't recognized, return `NULL' instead. */
#define __localdep_sigabbrev_np __LIBC_LOCAL_NAME(sigabbrev_np)
#endif /* !... */
#endif /* !__local___localdep_sigabbrev_np_defined */
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
__NAMESPACE_LOCAL_END
#include <asm/os/signal.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strtosigno(3)
 * Return the signal number for a given name.
 * e.g. `strtosigno("SIGINT") == SIGINT'
 * When `name' isn't recognized, return `0' instead. */
__LOCAL_LIBC(strtosigno) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __signo_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtosigno))(const char *__name) {
	__signo_t __i, __result = 0;
	if (__name[0] != 'S' || __name[1] != 'I' || __name[2] != 'G')
		return 0;
	__name += 3;
	for (__i = 1; __i < __NSIG; ++__i) {
		char const *__s = __localdep_sigabbrev_np(__i);
		if (__likely(__s) && __localdep_strcmp(__s, __name) == 0) {
			__result = __i;
			break;
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
