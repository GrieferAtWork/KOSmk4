/* HASH CRC-32:0x1a84273d */
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
#ifndef __local_thr_min_stack_defined
#define __local_thr_min_stack_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: sysconf from unistd */
#ifndef __local___localdep_sysconf_defined
#define __local___localdep_sysconf_defined 1
#ifdef __CRT_HAVE_sysconf
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sysconf(2)
 * @param: NAME: One of `_SC_*' from <asm/crt/confname.h>
 * Return a system configuration value `NAME'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] `NAME' refers to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__CREDIRECT(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_RPC,__localdep_sysconf,(__STDC_INT_AS_UINT_T __name),sysconf,(__name))
#elif defined(__CRT_HAVE__sysconf)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sysconf(2)
 * @param: NAME: One of `_SC_*' from <asm/crt/confname.h>
 * Return a system configuration value `NAME'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] `NAME' refers to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__CREDIRECT(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_RPC,__localdep_sysconf,(__STDC_INT_AS_UINT_T __name),_sysconf,(__name))
#elif defined(__CRT_HAVE___sysconf)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sysconf(2)
 * @param: NAME: One of `_SC_*' from <asm/crt/confname.h>
 * Return a system configuration value `NAME'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] `NAME' refers to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__CREDIRECT(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_RPC,__localdep_sysconf,(__STDC_INT_AS_UINT_T __name),__sysconf,(__name))
#else /* ... */
#undef __local___localdep_sysconf_defined
#endif /* !... */
#endif /* !__local___localdep_sysconf_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/confname.h>
#include <asm/crt/limits.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(thr_min_stack) __ATTR_CONST __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(thr_min_stack))(void) {
#if (defined(__CRT_HAVE_sysconf) || defined(__CRT_HAVE__sysconf) || defined(__CRT_HAVE___sysconf)) && defined(_SC_THREAD_STACK_MIN)
	__LONGPTR_TYPE__ __result;
	__result = __localdep_sysconf(_SC_THREAD_STACK_MIN);
	if (__result != -1)
		return (__SIZE_TYPE__)__result;
#endif /* (__CRT_HAVE_sysconf || __CRT_HAVE__sysconf || __CRT_HAVE___sysconf) && _SC_THREAD_STACK_MIN */
#ifdef __PTHREAD_STACK_MIN
	return __PTHREAD_STACK_MIN;
#else /* __PTHREAD_STACK_MIN */
	return 8192;
#endif /* !__PTHREAD_STACK_MIN */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_thr_min_stack_defined
#define __local___localdep_thr_min_stack_defined 1
#define __localdep_thr_min_stack __LIBC_LOCAL_NAME(thr_min_stack)
#endif /* !__local___localdep_thr_min_stack_defined */
#endif /* !__local_thr_min_stack_defined */
