/* HASH CRC-32:0x9090034c */
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
#ifndef __local_strtoerrno_defined
#define __local_strtoerrno_defined
#include <__crt.h>
#include <asm/os/errno.h>
#if defined(__CRT_HAVE_errno_max) || defined(__ECOUNT)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_errno_max_defined
#define __local___localdep_errno_max_defined
#ifdef __CRT_HAVE_errno_max
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_errno_max,(void),errno_max,())
#elif defined(__ECOUNT)
__NAMESPACE_LOCAL_END
#include <libc/local/libiberty/errno_max.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_errno_max __LIBC_LOCAL_NAME(errno_max)
#else /* ... */
#undef __local___localdep_errno_max_defined
#endif /* !... */
#endif /* !__local___localdep_errno_max_defined */
#ifndef __local___localdep_strcmp_defined
#define __local___localdep_strcmp_defined
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcmp __LIBC_LOCAL_NAME(strcmp)
#endif /* !... */
#endif /* !__local___localdep_strcmp_defined */
#ifndef __local___localdep_strerrorname_np_defined
#define __local___localdep_strerrorname_np_defined
#ifdef __CRT_HAVE_strerrorname_np
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_strerrorname_np,(__errno_t __errnum),strerrorname_np,(__errnum))
#elif defined(__CRT_HAVE_strerrno)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_strerrorname_np,(__errno_t __errnum),strerrno,(__errnum))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strerrorname_np.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strerrorname_np __LIBC_LOCAL_NAME(strerrorname_np)
#endif /* !... */
#endif /* !__local___localdep_strerrorname_np_defined */
__LOCAL_LIBC(strtoerrno) __ATTR_PURE __ATTR_WUNUSED __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtoerrno))(char const *__name) {
	__errno_t __result = 0;
	if (__name) {
		__errno_t __max = (__NAMESPACE_LOCAL_SYM __localdep_errno_max)();
		for (;; ++__result) {
			char const *__sysname;
			if (__result > __max) {
				__result = 0;
				break;
			}
			__sysname = (__NAMESPACE_LOCAL_SYM __localdep_strerrorname_np)(__result);
			if (__sysname && (__NAMESPACE_LOCAL_SYM __localdep_strcmp)(__sysname, __name) == 0)
				break;
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtoerrno_defined
#define __local___localdep_strtoerrno_defined
#define __localdep_strtoerrno __LIBC_LOCAL_NAME(strtoerrno)
#endif /* !__local___localdep_strtoerrno_defined */
#else /* __CRT_HAVE_errno_max || __ECOUNT */
#undef __local_strtoerrno_defined
#endif /* !__CRT_HAVE_errno_max && !__ECOUNT */
#endif /* !__local_strtoerrno_defined */
