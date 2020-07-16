/* HASH CRC-32:0x87b97379 */
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
#ifndef _PWD_H
#define _PWD_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <bits/crt/db/passwd.h>

/* Documentation taken from Glibc /usr/include/pwd.h */
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


__SYSDECL_BEGIN

#if defined(__USE_POSIX) && defined(__USE_MISC)
/* Reasonable value for the buffer sized used in the
 * reentrant functions below. But better use `sysconf'. */
#define NSS_BUFLEN_PASSWD  1024
#endif /* __USE_POSIX && __USE_MISC */

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __gid_t_defined
#define __gid_t_defined 1
typedef __gid_t gid_t;
#endif /* !__gid_t_defined */
#ifndef __uid_t_defined
#define __uid_t_defined 1
typedef __uid_t uid_t;
#endif /* !__uid_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#ifndef __std_FILE_defined
#define __std_FILE_defined 1
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __FILE_defined
#define __FILE_defined 1
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
/* Rewind the password-file stream */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,setpwent,(void),())
/* Close the password-file stream */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC_NOKOS,endpwent,(void),())
/* Read an entry from the password-file stream, opening it if necessary */
__CDECLARE_OPT(,struct passwd *,__NOTHROW_RPC,getpwent,(void),())
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */
/* Search for an entry with a matching user ID */
__CDECLARE_OPT(,struct passwd *,__NOTHROW_RPC,getpwuid,(__uid_t __uid),(__uid))
/* Search for an entry with a matching username */
__CDECLARE_OPT(__ATTR_NONNULL((1)),struct passwd *,__NOTHROW_RPC,getpwnam,(const char *__name),(__name))

#ifdef __USE_MISC
/* Read an entry from STREAM */
__CDECLARE_OPT(__ATTR_NONNULL((1)),struct passwd *,__NOTHROW_RPC,fgetpwent,(__FILE *__restrict __stream),(__stream))
#ifdef __CRT_HAVE_putpwent
/* Write the given entry `ent' into the given `stream' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,putpwent,(struct passwd const *__restrict __ent, __FILE *__restrict __stream),(__ent,__stream))
#elif defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
#include <local/pwd/putpwent.h>
/* Write the given entry `ent' into the given `stream' */
__NAMESPACE_LOCAL_USING_OR_IMPL(putpwent, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL putpwent)(struct passwd const *__restrict __ent, __FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putpwent))(__ent, __stream); })
#endif /* ... */
#endif /* __USE_MISC */

#ifdef __USE_POSIX
/* Search for an entry with a matching user ID */
__CDECLARE_OPT(__ATTR_NONNULL((2, 3, 5)),int,__NOTHROW_RPC,getpwuid_r,(__uid_t __uid, struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result),(__uid,__resultbuf,__buffer,__buflen,__result))
/* Search for an entry with a matching username */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 3, 5)),int,__NOTHROW_RPC,getpwnam_r,(const char *__restrict __name, struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result),(__name,__resultbuf,__buffer,__buflen,__result))
#ifdef __USE_MISC
/* Read an entry from the password-file stream, opening it if necessary */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 4)),__errno_t,__NOTHROW_RPC,getpwent_r,(struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result),(__resultbuf,__buffer,__buflen,__result))
#ifdef __CRT_HAVE_fgetpwent_r
/* Read an entry from STREAM. This function is not standardized and probably never will */
__CDECLARE(__ATTR_NONNULL((1, 2, 3, 5)),__errno_t,__NOTHROW_RPC,fgetpwent_r,(__FILE *__restrict __stream, struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result),(__stream,__resultbuf,__buffer,__buflen,__result))
#else /* __CRT_HAVE_fgetpwent_r */
#include <asm/stdio.h>
#if (defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock) || defined(__CRT_HAVE__IO_ftell)) && (defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || (defined(__SEEK_SET) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)))) && (defined(__CRT_HAVE_fparseln) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && defined(__CRT_HAVE_realloc)))
#include <local/pwd/fgetpwent_r.h>
/* Read an entry from STREAM. This function is not standardized and probably never will */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetpwent_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3, 5)) __errno_t __NOTHROW_RPC(__LIBCCALL fgetpwent_r)(__FILE *__restrict __stream, struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetpwent_r))(__stream, __resultbuf, __buffer, __buflen, __result); })
#endif /* (__CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE__ftelli64 || __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked || __CRT_HAVE_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock || __CRT_HAVE__IO_ftell) && (__CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || (__SEEK_SET && (__CRT_HAVE_fseeko64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock))) && (__CRT_HAVE_fparseln || ((__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && __CRT_HAVE_realloc)) */
#endif /* !__CRT_HAVE_fgetpwent_r */
#ifdef __USE_KOS
#ifdef __CRT_HAVE_fgetpwuid_r
/* Search for an entry with a matching user ID */
__CDECLARE(__ATTR_NONNULL((1, 3, 4, 6)),__errno_t,__NOTHROW_RPC,fgetpwuid_r,(__FILE *__restrict __stream, __uid_t __uid, struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result),(__stream,__uid,__resultbuf,__buffer,__buflen,__result))
#else /* __CRT_HAVE_fgetpwuid_r */
#include <asm/stdio.h>
#if (defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock) || defined(__CRT_HAVE__IO_ftell)) && (defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || (defined(__SEEK_SET) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)))) && (defined(__CRT_HAVE_fparseln) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && defined(__CRT_HAVE_realloc)))
#include <local/pwd/fgetpwuid_r.h>
/* Search for an entry with a matching user ID */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetpwuid_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3, 4, 6)) __errno_t __NOTHROW_RPC(__LIBCCALL fgetpwuid_r)(__FILE *__restrict __stream, __uid_t __uid, struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetpwuid_r))(__stream, __uid, __resultbuf, __buffer, __buflen, __result); })
#endif /* (__CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE__ftelli64 || __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked || __CRT_HAVE_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock || __CRT_HAVE__IO_ftell) && (__CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || (__SEEK_SET && (__CRT_HAVE_fseeko64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock))) && (__CRT_HAVE_fparseln || ((__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && __CRT_HAVE_realloc)) */
#endif /* !__CRT_HAVE_fgetpwuid_r */
#ifdef __CRT_HAVE_fgetpwnam_r
/* Search for an entry with a matching username */
__CDECLARE(__ATTR_NONNULL((1, 2, 3, 4, 6)),__errno_t,__NOTHROW_RPC,fgetpwnam_r,(__FILE *__restrict __stream, const char *__restrict __name, struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result),(__stream,__name,__resultbuf,__buffer,__buflen,__result))
#else /* __CRT_HAVE_fgetpwnam_r */
#include <asm/stdio.h>
#if (defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock) || defined(__CRT_HAVE__IO_ftell)) && (defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || (defined(__SEEK_SET) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)))) && (defined(__CRT_HAVE_fparseln) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && defined(__CRT_HAVE_realloc)))
#include <local/pwd/fgetpwnam_r.h>
/* Search for an entry with a matching username */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetpwnam_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3, 4, 6)) __errno_t __NOTHROW_RPC(__LIBCCALL fgetpwnam_r)(__FILE *__restrict __stream, const char *__restrict __name, struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetpwnam_r))(__stream, __name, __resultbuf, __buffer, __buflen, __result); })
#endif /* (__CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE__ftelli64 || __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked || __CRT_HAVE_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock || __CRT_HAVE__IO_ftell) && (__CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || (__SEEK_SET && (__CRT_HAVE_fseeko64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock))) && (__CRT_HAVE_fparseln || ((__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && __CRT_HAVE_realloc)) */
#endif /* !__CRT_HAVE_fgetpwnam_r */
#endif /* __USE_KOS */
#endif /* __USE_MISC */
#endif	/* __USE_POSIX */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_getpw
/* Re-construct the password-file line for the given uid in the
 * given buffer. This knows the format that the caller will
 * expect, but this need not be the format of the password file */
__CDECLARE(,int,__NOTHROW_RPC,getpw,(__uid_t __uid, char *__buffer),(__uid,__buffer))
#elif defined(__CRT_HAVE_getpwuid)
#include <local/pwd/getpw.h>
/* Re-construct the password-file line for the given uid in the
 * given buffer. This knows the format that the caller will
 * expect, but this need not be the format of the password file */
__NAMESPACE_LOCAL_USING_OR_IMPL(getpw, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL getpw)(__uid_t __uid, char *__buffer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getpw))(__uid, __buffer); })
#endif /* ... */
#endif /* __USE_GNU */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PWD_H */
