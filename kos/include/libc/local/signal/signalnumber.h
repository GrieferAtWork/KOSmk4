/* HASH CRC-32:0x4eb9ea24 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_signalnumber_defined
#define __local_signalnumber_defined
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memcasecmp_defined
#define __local___localdep_memcasecmp_defined
#ifdef __CRT_HAVE_memcasecmp
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),memcasecmp,(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE_memicmp)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),memicmp,(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE__memicmp)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),_memicmp,(__s1,__s2,__num_chars))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcasecmp __LIBC_LOCAL_NAME(memcasecmp)
#endif /* !... */
#endif /* !__local___localdep_memcasecmp_defined */
#ifndef __local___localdep_sigabbrev_np_defined
#define __local___localdep_sigabbrev_np_defined
#ifdef __CRT_HAVE_sigabbrev_np
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_sigabbrev_np,(__signo_t __signo),sigabbrev_np,(__signo))
#elif defined(__CRT_HAVE_signalname)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_sigabbrev_np,(__signo_t __signo),signalname,(__signo))
#elif defined(__CRT_HAVE_strsigno)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_sigabbrev_np,(__signo_t __signo),strsigno,(__signo))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/sigabbrev_np.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sigabbrev_np __LIBC_LOCAL_NAME(sigabbrev_np)
#endif /* !... */
#endif /* !__local___localdep_sigabbrev_np_defined */
#ifndef __local___localdep_strcasecmp_defined
#define __local___localdep_strcasecmp_defined
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),strcasecmp,{ return __builtin_strcasecmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE___strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),__strcasecmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcasecmp __LIBC_LOCAL_NAME(strcasecmp)
#endif /* !... */
#endif /* !__local___localdep_strcasecmp_defined */
#ifndef __local___localdep_strtou32_defined
#define __local___localdep_strtou32_defined
#ifdef __CRT_HAVE_strtou32
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && __SIZEOF_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && __SIZEOF_LONG_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && __SIZEOF_LONG_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtouq) && __SIZEOF_LONG_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && __SIZEOF_INTMAX_T__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoumax,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtou32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtou32 __LIBC_LOCAL_NAME(strtou32)
#endif /* !... */
#endif /* !__local___localdep_strtou32_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/signal.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(signalnumber) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __signo_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(signalnumber))(const char *__name) {
	__signo_t __result;

	/* Skip "SIG" prefix. */
	if ((__name[0] == 'S' || __name[0] == 's') &&
	    (__name[1] == 'I' || __name[1] == 'i') &&
	    (__name[2] == 'G' || __name[2] == 'g'))
		__name += 3;

	/* Check for known signal names. */
	for (__result = 1; __result < __NSIG; ++__result) {
		char const *__s = (__NAMESPACE_LOCAL_SYM __localdep_sigabbrev_np)(__result);
		if (__likely(__s) && (__NAMESPACE_LOCAL_SYM __localdep_strcasecmp)(__name, __s) == 0)
			return __result;
	}

	/* Signal alias names. */
#ifdef __SIGCHLD
	if ((__NAMESPACE_LOCAL_SYM __localdep_strcasecmp)(__name, "CLD") == 0)
		return __SIGCHLD;
#endif /* __SIGCHLD */
#ifdef __SIGRPC
	if ((__NAMESPACE_LOCAL_SYM __localdep_strcasecmp)(__name, "RPC") == 0)
		return __SIGRPC;
#endif /* __SIGRPC */
#ifdef __SIGPOLL
	if ((__NAMESPACE_LOCAL_SYM __localdep_strcasecmp)(__name, "POLL") == 0)
		return __SIGPOLL;
#endif /* __SIGPOLL */

	/* SIGRT* with offset. e.g. "RTMIN+1", "RTMAX-1" */
#if defined(__SIGRTMIN) && defined(__SIGRTMAX)
	if ((__NAMESPACE_LOCAL_SYM __localdep_memcasecmp)(__name, "RTMIN+", 6 * sizeof(char)) == 0) {
		__name += 6;
		__result = __SIGRTMIN + (__signo_t)(__NAMESPACE_LOCAL_SYM __localdep_strtou32)(__name, (char **)&__name, 10);
__return_rt_signal:
		if (*__name != '\0' || (__result < __SIGRTMIN || __result > __SIGRTMAX))
			__result = 0;
		return __result;
	}
	if ((__NAMESPACE_LOCAL_SYM __localdep_memcasecmp)(__name, "RTMAX-", 6 * sizeof(char)) == 0) {
		__name += 6;
		__result = __SIGRTMAX - (__signo_t)(__NAMESPACE_LOCAL_SYM __localdep_strtou32)(__name, (char **)&__name, 10);
		goto __return_rt_signal;
	}
#endif /* __SIGRTMIN && __SIGRTMAX */

	/* Special case: the signal number itself. */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_strtou32)(__name, (char **)&__name, 10);
	if (*__name != '\0' || (__result <= 0 || __result >= __NSIG))
		__result = 0;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_signalnumber_defined
#define __local___localdep_signalnumber_defined
#define __localdep_signalnumber __LIBC_LOCAL_NAME(signalnumber)
#endif /* !__local___localdep_signalnumber_defined */
#endif /* !__local_signalnumber_defined */
