/* HASH CRC-32:0x41609708 */
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
#ifndef __local_signalnumber_defined
#define __local_signalnumber_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: signalname from signal */
#ifndef __local___localdep_signalname_defined
#define __local___localdep_signalname_defined 1
#ifdef __CRT_HAVE_signalname
/* >> signalname(3)
 * Same as `strsignal_s(3)', but don't include the leading
 * `SIG*' prefix normally prepended before the signal name. */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_signalname,(__signo_t __signum),signalname,(__signum))
#else /* __CRT_HAVE_signalname */
__NAMESPACE_LOCAL_END
#include <libc/local/signal/signalname.h>
__NAMESPACE_LOCAL_BEGIN
/* >> signalname(3)
 * Same as `strsignal_s(3)', but don't include the leading
 * `SIG*' prefix normally prepended before the signal name. */
#define __localdep_signalname __LIBC_LOCAL_NAME(signalname)
#endif /* !__CRT_HAVE_signalname */
#endif /* !__local___localdep_signalname_defined */
/* Dependency: strcasecmp from string */
#ifndef __local___localdep_strcasecmp_defined
#define __local___localdep_strcasecmp_defined 1
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),strcasecmp,{ return __builtin_strcasecmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE___strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),__strcasecmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcasecmp __LIBC_LOCAL_NAME(strcasecmp)
#endif /* !... */
#endif /* !__local___localdep_strcasecmp_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/signal.h>
__NAMESPACE_LOCAL_BEGIN
/* >> signalnumber(3)
 * Similar to `strtosigno(3)', however ignore any leading `SIG*'
 * prefix of `name', and do a case-insensitive compare between
 * the given `name', and the signal's actual name.
 * When `name' isn't recognized, return `0' instead. */
__LOCAL_LIBC(signalnumber) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __signo_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(signalnumber))(const char *__name) {
	__signo_t __i, __result = 0;
	if ((__name[0] == 'S' || __name[0] == 's') &&
	    (__name[1] == 'I' || __name[1] == 'i') &&
	    (__name[2] == 'G' || __name[2] == 'g'))
		__name += 3;
	for (__i = 1; __i < __NSIG; ++__i) {
		char const *__s = __localdep_signalname(__i);
		if (__likely(__s) && __localdep_strcasecmp(__s, __name) == 0) {
			__result = __i;
			break;
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_signalnumber_defined
#define __local___localdep_signalnumber_defined 1
#define __localdep_signalnumber __LIBC_LOCAL_NAME(signalnumber)
#endif /* !__local___localdep_signalnumber_defined */
#endif /* !__local_signalnumber_defined */
