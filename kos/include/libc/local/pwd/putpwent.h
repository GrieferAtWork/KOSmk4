/* HASH CRC-32:0x522e215e */
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
#ifndef __local_putpwent_defined
#define __local_putpwent_defined
#include <__crt.h>
#if defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <bits/crt/db/passwd.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_flockfile_defined
#define __local___localdep_flockfile_defined
#ifdef __CRT_HAVE_flockfile
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_RPC,__localdep_flockfile,(__FILE *__restrict __stream),flockfile,(__stream))
#elif defined(__CRT_HAVE__lock_file)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_RPC,__localdep_flockfile,(__FILE *__restrict __stream),_lock_file,(__stream))
#elif defined(__CRT_HAVE__IO_flockfile)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_RPC,__localdep_flockfile,(__FILE *__restrict __stream),_IO_flockfile,(__stream))
#else /* ... */
#undef __local___localdep_flockfile_defined
#endif /* !... */
#endif /* !__local___localdep_flockfile_defined */
#ifndef __local___localdep_fprintf_unlocked_defined
#define __local___localdep_fprintf_unlocked_defined
#if __has_builtin(__builtin_fprintf_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fprintf_unlocked) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SSIZE_T,__NOTHROW_CB_NCX,__localdep_fprintf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, ...),fprintf_unlocked,{ return __builtin_fprintf_unlocked(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_fprintf_unlocked)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T __NOTHROW_CB_NCX(__VLIBCCALL __localdep_fprintf_unlocked)(__FILE *__restrict __stream, char const *__restrict __format, ...) __CASMNAME("fprintf_unlocked");
#elif defined(__CRT_HAVE_fprintf_s)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T __NOTHROW_CB_NCX(__VLIBCCALL __localdep_fprintf_unlocked)(__FILE *__restrict __stream, char const *__restrict __format, ...) __CASMNAME("fprintf_s");
#elif defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fprintf_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fprintf_unlocked __LIBC_LOCAL_NAME(fprintf_unlocked)
#else /* ... */
#undef __local___localdep_fprintf_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_fprintf_unlocked_defined */
#ifndef __local___localdep_funlockfile_defined
#define __local___localdep_funlockfile_defined
#ifdef __CRT_HAVE_funlockfile
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__localdep_funlockfile,(__FILE *__restrict __stream),funlockfile,(__stream))
#elif defined(__CRT_HAVE__unlock_file)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__localdep_funlockfile,(__FILE *__restrict __stream),_unlock_file,(__stream))
#elif defined(__CRT_HAVE__IO_funlockfile)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__localdep_funlockfile,(__FILE *__restrict __stream),_IO_funlockfile,(__stream))
#else /* ... */
#undef __local___localdep_funlockfile_defined
#endif /* !... */
#endif /* !__local___localdep_funlockfile_defined */
#ifndef __local___localdep_nss_checkfield_defined
#define __local___localdep_nss_checkfield_defined
__NAMESPACE_LOCAL_END
#include <libc/local/pwd/nss_checkfield.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_nss_checkfield __LIBC_LOCAL_NAME(nss_checkfield)
#endif /* !__local___localdep_nss_checkfield_defined */
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
#include <bits/crt/inttypes.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(putpwent) __ATTR_IN(1) __ATTR_INOUT(2) int
__NOTHROW_CB_NCX(__LIBCCALL __LIBC_LOCAL_NAME(putpwent))(struct passwd const *__restrict __ent, __FILE *__restrict __stream) {
	__STDC_INT_AS_SSIZE_T __error;
#if __SIZEOF_GID_T__ == 1
	char __gidbuf[__COMPILER_LENOF("255")];
#elif __SIZEOF_GID_T__ == 2
	char __gidbuf[__COMPILER_LENOF("65535")];
#elif __SIZEOF_GID_T__ == 4
	char __gidbuf[__COMPILER_LENOF("4294967295")];
#else /* ... */
	char __gidbuf[__COMPILER_LENOF("18446744073709551615")];
#endif /* !... */
#if __SIZEOF_UID_T__ == 1
	char __uidbuf[__COMPILER_LENOF("255")];
#elif __SIZEOF_UID_T__ == 2
	char __uidbuf[__COMPILER_LENOF("65535")];
#elif __SIZEOF_UID_T__ == 4
	char __uidbuf[__COMPILER_LENOF("4294967295")];
#else /* ... */
	char __uidbuf[__COMPILER_LENOF("18446744073709551615")];
#endif /* !... */

	/* Validate arguments. */
	if __unlikely(!__ent)
		goto __err_inval;
	if __unlikely(!__stream)
		goto __err_inval;
	if __unlikely(!__ent->pw_name)
		goto __err_inval;
	if __unlikely(!(__NAMESPACE_LOCAL_SYM __localdep_nss_checkfield)(__ent->pw_name))
		goto __err_inval;
	if __unlikely(!(__NAMESPACE_LOCAL_SYM __localdep_nss_checkfield)(__ent->pw_passwd))
		goto __err_inval;
	if __unlikely(!(__NAMESPACE_LOCAL_SYM __localdep_nss_checkfield)(__ent->pw_dir))
		goto __err_inval;
	if __unlikely(!(__NAMESPACE_LOCAL_SYM __localdep_nss_checkfield)(__ent->pw_shell))
		goto __err_inval;
	if __unlikely(!(__NAMESPACE_LOCAL_SYM __localdep_nss_checkfield)(__ent->pw_gecos)) /* TODO: Replace invalid characters with ' ' */
		goto __err_inval;

	/* Generate the UID+GID strings. */
	(__NAMESPACE_LOCAL_SYM __localdep_sprintf)(__uidbuf, "%" __PRIN_PREFIX(__SIZEOF_UID_T__) "u", __ent->pw_uid);
	(__NAMESPACE_LOCAL_SYM __localdep_sprintf)(__gidbuf, "%" __PRIN_PREFIX(__SIZEOF_GID_T__) "u", __ent->pw_gid);
	if (__ent->pw_name[0] == '+' || __ent->pw_name[0] == '-') {
		__uidbuf[0] = '\0';
		__gidbuf[0] = '\0';
	}

	/* Generate the entry. */
#if (defined(__CRT_HAVE_flockfile) || defined(__CRT_HAVE__lock_file) || defined(__CRT_HAVE__IO_flockfile)) && (defined(__CRT_HAVE_funlockfile) || defined(__CRT_HAVE__unlock_file) || defined(__CRT_HAVE__IO_funlockfile))
	(__NAMESPACE_LOCAL_SYM __localdep_flockfile)(__stream);
#endif /* (__CRT_HAVE_flockfile || __CRT_HAVE__lock_file || __CRT_HAVE__IO_flockfile) && (__CRT_HAVE_funlockfile || __CRT_HAVE__unlock_file || __CRT_HAVE__IO_funlockfile) */
	__error = (__NAMESPACE_LOCAL_SYM __localdep_fprintf_unlocked)(__stream,
	                         "%s:%s:%s:%s:%s:%s:%s\n",
	                         __ent->pw_name,
	                         __ent->pw_passwd ? __ent->pw_passwd : "",
	                         __uidbuf,
	                         __gidbuf,
	                         __ent->pw_gecos ? __ent->pw_gecos : "",
	                         __ent->pw_dir ? __ent->pw_dir : "",
	                         __ent->pw_shell ? __ent->pw_shell : "");
#if (defined(__CRT_HAVE_flockfile) || defined(__CRT_HAVE__lock_file) || defined(__CRT_HAVE__IO_flockfile)) && (defined(__CRT_HAVE_funlockfile) || defined(__CRT_HAVE__unlock_file) || defined(__CRT_HAVE__IO_funlockfile))
	(__NAMESPACE_LOCAL_SYM __localdep_funlockfile)(__stream);
#endif /* (__CRT_HAVE_flockfile || __CRT_HAVE__lock_file || __CRT_HAVE__IO_flockfile) && (__CRT_HAVE_funlockfile || __CRT_HAVE__unlock_file || __CRT_HAVE__IO_funlockfile) */

	return __likely(__error >= 0) ? 0 : -1;
__err_inval:
#ifdef __EINVAL
	return __libc_seterrno(__EINVAL);
#else /* __EINVAL */
	return __libc_seterrno(1);
#endif /* !__EINVAL */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_putpwent_defined
#define __local___localdep_putpwent_defined
#define __localdep_putpwent __LIBC_LOCAL_NAME(putpwent)
#endif /* !__local___localdep_putpwent_defined */
#else /* __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_fprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_HAVE_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_HAVE_fgetc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock */
#undef __local_putpwent_defined
#endif /* !__CRT_HAVE_fprintf_unlocked && !__CRT_HAVE_fprintf_s && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && !__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock */
#endif /* !__local_putpwent_defined */
