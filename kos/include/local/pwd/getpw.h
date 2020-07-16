/* HASH CRC-32:0x1f55ecc7 */
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
#ifndef __local_getpw_defined
#define __local_getpw_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_getpwuid
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: getpwuid from pwd */
#ifndef __local___localdep_getpwuid_defined
#define __local___localdep_getpwuid_defined 1
__NAMESPACE_LOCAL_END
#include <bits/crt/db/passwd.h>
__NAMESPACE_LOCAL_BEGIN
/* Search for an entry with a matching user ID */
__CREDIRECT(,struct passwd *,__NOTHROW_RPC,__localdep_getpwuid,(__uid_t __uid),getpwuid,(__uid))
#endif /* !__local___localdep_getpwuid_defined */
/* Dependency: sprintf from stdio */
#ifndef __local___localdep_sprintf_defined
#define __local___localdep_sprintf_defined 1
#if __has_builtin(__builtin_sprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sprintf) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__CEIREDIRECT(__ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_sprintf,(char *__restrict __buf, char const *__restrict __format, ...),sprintf,{ return __builtin_sprintf(__buf, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_sprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("sprintf");
#elif defined(__CRT_HAVE__IO_sprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("_IO_sprintf");
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/stdio/sprintf.h>
__NAMESPACE_LOCAL_BEGIN
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
#define __localdep_sprintf __LIBC_LOCAL_NAME(sprintf)
#endif /* !... */
#endif /* !__local___localdep_sprintf_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/inttypes.h>
__NAMESPACE_LOCAL_BEGIN
/* Re-construct the password-file line for the given uid in the
 * given buffer. This knows the format that the caller will
 * expect, but this need not be the format of the password file */
__LOCAL_LIBC(getpw) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(getpw))(__uid_t __uid, char *__buffer) {
	struct passwd *__ent;
	__ent = __localdep_getpwuid(__uid);
	if __unlikely(!__ent)
		goto __err;
	__localdep_sprintf(__buffer,
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
#define __local___localdep_getpw_defined 1
#define __localdep_getpw __LIBC_LOCAL_NAME(getpw)
#endif /* !__local___localdep_getpw_defined */
#else /* __CRT_HAVE_getpwuid */
#undef __local_getpw_defined
#endif /* !__CRT_HAVE_getpwuid */
#endif /* !__local_getpw_defined */
