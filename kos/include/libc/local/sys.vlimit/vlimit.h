/* HASH CRC-32:0xe37e933f */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_vlimit_defined
#define __local_vlimit_defined
#include <__crt.h>
#include <asm/os/resource.h>
#include <features.h>
#include <bits/types.h>
#if ((defined(__CRT_HAVE_getrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE___getrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE___libc_getrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE_getrlimit64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__))) && ((defined(__CRT_HAVE_setrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE___setrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE___libc_setrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE_setrlimit64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getrlimit_defined
#define __local___localdep_getrlimit_defined
#if defined(__CRT_HAVE_getrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/rlimit.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getrlimit,(int __resource, struct rlimit *__rlimits),getrlimit,(__resource,__rlimits))
#elif defined(__CRT_HAVE___getrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/rlimit.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getrlimit,(int __resource, struct rlimit *__rlimits),__getrlimit,(__resource,__rlimits))
#elif defined(__CRT_HAVE___libc_getrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/rlimit.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getrlimit,(int __resource, struct rlimit *__rlimits),__libc_getrlimit,(__resource,__rlimits))
#elif defined(__CRT_HAVE_getrlimit64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/rlimit.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getrlimit,(int __resource, struct rlimit *__rlimits),getrlimit64,(__resource,__rlimits))
#else /* ... */
#undef __local___localdep_getrlimit_defined
#endif /* !... */
#endif /* !__local___localdep_getrlimit_defined */
#ifndef __local___localdep_setrlimit_defined
#define __local___localdep_setrlimit_defined
#if defined(__CRT_HAVE_setrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/rlimit.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_NCX,__localdep_setrlimit,(int __resource, struct rlimit const *__rlimits),setrlimit,(__resource,__rlimits))
#elif defined(__CRT_HAVE___setrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/rlimit.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_NCX,__localdep_setrlimit,(int __resource, struct rlimit const *__rlimits),__setrlimit,(__resource,__rlimits))
#elif defined(__CRT_HAVE___libc_setrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/rlimit.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_NCX,__localdep_setrlimit,(int __resource, struct rlimit const *__rlimits),__libc_setrlimit,(__resource,__rlimits))
#elif defined(__CRT_HAVE_setrlimit64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/rlimit.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_NCX,__localdep_setrlimit,(int __resource, struct rlimit const *__rlimits),setrlimit64,(__resource,__rlimits))
#else /* ... */
#undef __local___localdep_setrlimit_defined
#endif /* !... */
#endif /* !__local___localdep_setrlimit_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/vlimit.h>
#include <bits/os/rlimit.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vlimit) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(vlimit))(int __resource, int ___value) {
	struct rlimit __rlim;
	int __rlimit_resource, __result;
#ifdef __LIM_TO_RLIMIT
	__rlimit_resource = __LIM_TO_RLIMIT(__resource);
#else /* __LIM_TO_RLIMIT */
	switch (__resource) {

#if defined(__LIM_CPU) && defined(__RLIMIT_CPU)
	case __LIM_CPU:
		__rlimit_resource = __RLIMIT_CPU;
#endif /* __LIM_CPU && __RLIMIT_CPU */

#if defined(__LIM_FSIZE) && defined(__RLIMIT_FSIZE)
	case __LIM_FSIZE:
		__rlimit_resource = __RLIMIT_FSIZE;
#endif /* __LIM_FSIZE && __RLIMIT_FSIZE */

#if defined(__LIM_DATA) && defined(__RLIMIT_DATA)
	case __LIM_DATA:
		__rlimit_resource = __RLIMIT_DATA;
#endif /* __LIM_DATA && __RLIMIT_DATA */

#if defined(__LIM_STACK) && defined(__RLIMIT_STACK)
	case __LIM_STACK:
		__rlimit_resource = __RLIMIT_STACK;
#endif /* __LIM_STACK && __RLIMIT_STACK */

#if defined(__LIM_CORE) && defined(__RLIMIT_CORE)
	case __LIM_CORE:
		__rlimit_resource = __RLIMIT_CORE;
#endif /* __LIM_CORE && __RLIMIT_CORE */

#if defined(__LIM_MAXRSS) && defined(__RLIMIT_RSS)
	case __LIM_MAXRSS:
		__rlimit_resource = __RLIMIT_RSS;
#endif /* __LIM_MAXRSS && __RLIMIT_RSS */

	default:
#ifdef __EINVAL
		return __libc_seterrno(__EINVAL);
#else /* __EINVAL */
		return __libc_seterrno(1);
#endif /* !__EINVAL */
	}
#endif /* !__LIM_TO_RLIMIT */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_getrlimit)((int)__rlimit_resource, &__rlim);
	if __likely(__result == 0) {
		__rlim.rlim_cur = (__rlim_t)                              /* Cast to correct type. */
		                  (__CRT_PRIVATE_SINT(__SIZEOF_RLIM_T__)) /* Sign expansion... */
		                  (int)___value;
		__result = (__NAMESPACE_LOCAL_SYM __localdep_setrlimit)((int)__rlimit_resource, &__rlim);
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vlimit_defined
#define __local___localdep_vlimit_defined
#define __localdep_vlimit __LIBC_LOCAL_NAME(vlimit)
#endif /* !__local___localdep_vlimit_defined */
#else /* ((__CRT_HAVE_getrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE___getrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE___libc_getrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE_getrlimit64 && (__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__))) && ((__CRT_HAVE_setrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE___setrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE___libc_setrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE_setrlimit64 && (__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__))) */
#undef __local_vlimit_defined
#endif /* ((!__CRT_HAVE_getrlimit || (__USE_FILE_OFFSET64 && __SIZEOF_RLIM32_T__ != __SIZEOF_RLIM64_T__)) && (!__CRT_HAVE___getrlimit || (__USE_FILE_OFFSET64 && __SIZEOF_RLIM32_T__ != __SIZEOF_RLIM64_T__)) && (!__CRT_HAVE___libc_getrlimit || (__USE_FILE_OFFSET64 && __SIZEOF_RLIM32_T__ != __SIZEOF_RLIM64_T__)) && (!__CRT_HAVE_getrlimit64 || (!__USE_FILE_OFFSET64 && __SIZEOF_RLIM32_T__ != __SIZEOF_RLIM64_T__))) || ((!__CRT_HAVE_setrlimit || (__USE_FILE_OFFSET64 && __SIZEOF_RLIM32_T__ != __SIZEOF_RLIM64_T__)) && (!__CRT_HAVE___setrlimit || (__USE_FILE_OFFSET64 && __SIZEOF_RLIM32_T__ != __SIZEOF_RLIM64_T__)) && (!__CRT_HAVE___libc_setrlimit || (__USE_FILE_OFFSET64 && __SIZEOF_RLIM32_T__ != __SIZEOF_RLIM64_T__)) && (!__CRT_HAVE_setrlimit64 || (!__USE_FILE_OFFSET64 && __SIZEOF_RLIM32_T__ != __SIZEOF_RLIM64_T__))) */
#endif /* !__local_vlimit_defined */
