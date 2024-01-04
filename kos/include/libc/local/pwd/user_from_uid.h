/* HASH CRC-32:0x72eebc53 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_user_from_uid_defined
#define __local_user_from_uid_defined
#include <__crt.h>
#if defined(__CRT_HAVE_getpwuid) || (defined(__CRT_HAVE_setpwent) && defined(__CRT_HAVE_getpwent))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getpwuid_defined
#define __local___localdep_getpwuid_defined
#ifdef __CRT_HAVE_getpwuid
__NAMESPACE_LOCAL_END
#include <bits/crt/db/passwd.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,struct passwd *,__NOTHROW_RPC,__localdep_getpwuid,(__uid_t __uid),getpwuid,(__uid))
#elif defined(__CRT_HAVE_setpwent) && defined(__CRT_HAVE_getpwent)
__NAMESPACE_LOCAL_END
#include <libc/local/pwd/getpwuid.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getpwuid __LIBC_LOCAL_NAME(getpwuid)
#else /* ... */
#undef __local___localdep_getpwuid_defined
#endif /* !... */
#endif /* !__local___localdep_getpwuid_defined */
#ifndef __local___localdep_sprintf_defined
#define __local___localdep_sprintf_defined
#if __has_builtin(__builtin_sprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sprintf) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_IN(2) __ATTR_LIBC_PRINTF(2, 3) __ATTR_OUT(1),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_sprintf,(char *__restrict __buf, char const *__restrict __format, ...),sprintf,{ return __builtin_sprintf(__buf, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_sprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_IN(2) __ATTR_LIBC_PRINTF(2, 3) __ATTR_OUT(1) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("sprintf");
#elif defined(__CRT_HAVE__IO_sprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_IN(2) __ATTR_LIBC_PRINTF(2, 3) __ATTR_OUT(1) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("_IO_sprintf");
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/sprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sprintf __LIBC_LOCAL_NAME(sprintf)
#endif /* !... */
#endif /* !__local___localdep_sprintf_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/db/passwd.h>
#include <bits/crt/inttypes.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(user_from_uid) __ATTR_WUNUSED char const *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(user_from_uid))(__uid_t __uid, int __nouser) {
	struct passwd *__ent = (__NAMESPACE_LOCAL_SYM __localdep_getpwuid)(__uid);
	if (__ent)
		return __ent->pw_name;
	if (__nouser == 0) {
#if __SIZEOF_UID_T__ == 1
		static char __fallback_strbuf[__COMPILER_LENOF("-128")];
#elif __SIZEOF_UID_T__ == 2
		static char __fallback_strbuf[__COMPILER_LENOF("-32768")];
#elif __SIZEOF_UID_T__ == 4
		static char __fallback_strbuf[__COMPILER_LENOF("-2147483648")];
#else /* ... */
		static char __fallback_strbuf[__COMPILER_LENOF("-9223372036854775808")];
#endif /* !... */
		(__NAMESPACE_LOCAL_SYM __localdep_sprintf)(__fallback_strbuf, "%" __PRIN_PREFIX(__SIZEOF_UID_T__) "d", __uid);
		return __fallback_strbuf;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_user_from_uid_defined
#define __local___localdep_user_from_uid_defined
#define __localdep_user_from_uid __LIBC_LOCAL_NAME(user_from_uid)
#endif /* !__local___localdep_user_from_uid_defined */
#else /* __CRT_HAVE_getpwuid || (__CRT_HAVE_setpwent && __CRT_HAVE_getpwent) */
#undef __local_user_from_uid_defined
#endif /* !__CRT_HAVE_getpwuid && (!__CRT_HAVE_setpwent || !__CRT_HAVE_getpwent) */
#endif /* !__local_user_from_uid_defined */
