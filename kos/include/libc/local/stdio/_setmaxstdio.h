/* HASH CRC-32:0x558ea302 */
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
#ifndef __local__setmaxstdio_defined
#define __local__setmaxstdio_defined
#include <__crt.h>
#include <asm/os/resource.h>
#include <features.h>
#include <bits/types.h>
#if defined(__RLIMIT_NOFILE) && ((defined(__CRT_HAVE_getrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE___getrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE___libc_getrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE_getrlimit64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__))) && ((defined(__CRT_HAVE_setrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE___setrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE___libc_setrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE_setrlimit64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)))
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
#include <bits/os/rlimit.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_setmaxstdio) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_setmaxstdio))(int __newmaxval) {
	struct rlimit __rlim;
	if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_getrlimit)((int)__RLIMIT_NOFILE, &__rlim) != 0)
		goto __err;
	__rlim.rlim_cur = (__rlim_t)__newmaxval;
	if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_setrlimit)((int)__RLIMIT_NOFILE, &__rlim) != 0) {
__err:
		__rlim.rlim_cur = (__rlim_t)-1;
	}
	return (int)__rlim.rlim_cur;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__setmaxstdio_defined
#define __local___localdep__setmaxstdio_defined
#define __localdep__setmaxstdio __LIBC_LOCAL_NAME(_setmaxstdio)
#endif /* !__local___localdep__setmaxstdio_defined */
#else /* __RLIMIT_NOFILE && ((__CRT_HAVE_getrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE___getrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE___libc_getrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE_getrlimit64 && (__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__))) && ((__CRT_HAVE_setrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE___setrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE___libc_setrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE_setrlimit64 && (__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__))) */
#undef __local__setmaxstdio_defined
#endif /* !__RLIMIT_NOFILE || ((!__CRT_HAVE_getrlimit || (__USE_FILE_OFFSET64 && __SIZEOF_RLIM32_T__ != __SIZEOF_RLIM64_T__)) && (!__CRT_HAVE___getrlimit || (__USE_FILE_OFFSET64 && __SIZEOF_RLIM32_T__ != __SIZEOF_RLIM64_T__)) && (!__CRT_HAVE___libc_getrlimit || (__USE_FILE_OFFSET64 && __SIZEOF_RLIM32_T__ != __SIZEOF_RLIM64_T__)) && (!__CRT_HAVE_getrlimit64 || (!__USE_FILE_OFFSET64 && __SIZEOF_RLIM32_T__ != __SIZEOF_RLIM64_T__))) || ((!__CRT_HAVE_setrlimit || (__USE_FILE_OFFSET64 && __SIZEOF_RLIM32_T__ != __SIZEOF_RLIM64_T__)) && (!__CRT_HAVE___setrlimit || (__USE_FILE_OFFSET64 && __SIZEOF_RLIM32_T__ != __SIZEOF_RLIM64_T__)) && (!__CRT_HAVE___libc_setrlimit || (__USE_FILE_OFFSET64 && __SIZEOF_RLIM32_T__ != __SIZEOF_RLIM64_T__)) && (!__CRT_HAVE_setrlimit64 || (!__USE_FILE_OFFSET64 && __SIZEOF_RLIM32_T__ != __SIZEOF_RLIM64_T__))) */
#endif /* !__local__setmaxstdio_defined */
