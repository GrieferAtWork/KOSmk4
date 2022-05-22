/* HASH CRC-32:0x21f694cb */
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
#ifndef __local_getpw_defined
#define __local_getpw_defined
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
__CEIREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1) __ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_sprintf,(char *__restrict __buf, char const *__restrict __format, ...),sprintf,{ return __builtin_sprintf(__buf, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_sprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("sprintf");
#elif defined(__CRT_HAVE__IO_sprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("_IO_sprintf");
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/sprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sprintf __LIBC_LOCAL_NAME(sprintf)
#endif /* !... */
#endif /* !__local___localdep_sprintf_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/inttypes.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getpw) __ATTR_ACCESS_WR(2) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(getpw))(__uid_t __uid, char *__buffer) {
	struct passwd *__ent;
	__ent = (__NAMESPACE_LOCAL_SYM __localdep_getpwuid)(__uid);
	if __unlikely(!__ent)
		goto __err;
	(__NAMESPACE_LOCAL_SYM __localdep_sprintf)(__buffer,
	        "%s:%s:"
	        "%" __PRIN_PREFIX(__SIZEOF_UID_T__) "u:"
	        "%" __PRIN_PREFIX(__SIZEOF_GID_T__) "u:"
	        "%s:%s:%s\n",
	        __ent->pw_name,
	        __ent->pw_passwd,
	        __ent->pw_uid,
	        __ent->pw_gid,
	        __ent->pw_gecos,
	        __ent->pw_dir,
	        __ent->pw_shell);
	return 0;
__err:
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getpw_defined
#define __local___localdep_getpw_defined
#define __localdep_getpw __LIBC_LOCAL_NAME(getpw)
#endif /* !__local___localdep_getpw_defined */
#else /* __CRT_HAVE_getpwuid || (__CRT_HAVE_setpwent && __CRT_HAVE_getpwent) */
#undef __local_getpw_defined
#endif /* !__CRT_HAVE_getpwuid && (!__CRT_HAVE_setpwent || !__CRT_HAVE_getpwent) */
#endif /* !__local_getpw_defined */
