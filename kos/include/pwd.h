/* HASH CRC-32:0x43b3dd82 */
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
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/pwd.h) */
/* (#) Portability: DJGPP         (/include/pwd.h) */
/* (#) Portability: DragonFly BSD (/include/pwd.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/pwd.h) */
/* (#) Portability: FreeBSD       (/include/pwd.h) */
/* (#) Portability: GNU C Library (/pwd/pwd.h) */
/* (#) Portability: GNU Hurd      (/usr/include/pwd.h) */
/* (#) Portability: NetBSD        (/include/pwd.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/pwd.h) */
/* (#) Portability: OpenBSD       (/include/pwd.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/pwd.h) */
/* (#) Portability: diet libc     (/include/pwd.h) */
/* (#) Portability: libbsd        (/include/bsd/pwd.h) */
/* (#) Portability: libc4/5       (/include/pwd.h) */
/* (#) Portability: libc6         (/include/pwd.h) */
/* (#) Portability: mintlib       (/include/pwd.h) */
/* (#) Portability: musl libc     (/include/pwd.h) */
/* (#) Portability: uClibc        (/include/pwd.h) */
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
#include <kos/anno.h>

__SYSDECL_BEGIN

#if defined(__USE_POSIX) && defined(__USE_MISC)
/* Ignore this value. It's  just some nonsensical constant  here
 * for  historic  purposes and  posix compliance.  All functions
 * found in this header are able to operate on arbitrarily-sized
 * user password database entries,  and so should your  program,
 * meaning this value is entirely pointless and should  actually
 * be considered as INFINITE.
 * Also: there's a `_SC_GETPW_R_SIZE_MAX' which also just returns
 *       this value, so it's just as useless. */
#define NSS_BUFLEN_PASSWD 1024
#endif /* __USE_POSIX && __USE_MISC */

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __gid_t_defined
#define __gid_t_defined
typedef __gid_t gid_t;
#endif /* !__gid_t_defined */
#ifndef __uid_t_defined
#define __uid_t_defined
typedef __uid_t uid_t;
#endif /* !__uid_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#ifndef __std_FILE_defined
#define __std_FILE_defined
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __FILE_defined
#define __FILE_defined
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
/* >> setpwent(3)
 * Rewind the password-file stream */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,setpwent,(void),())
/* >> endpwent(3)
 * Close the password-file stream */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC_NOKOS,endpwent,(void),())
/* >> getpwent(3)
 * Read an entry from the password-file stream, opening it if necessary
 * @return: * :                         A pointer to the read password entry
 * @return: NULL: (errno = <unchanged>) The last  entry  has  already  been  read
 *                                      (use `setpwent()' to rewind the database)
 * @return: NULL: (errno = <changed>)   Error (s.a. `errno') */
__CDECLARE_OPT(,struct passwd *,__NOTHROW_RPC,getpwent,(void),())
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */
#ifdef __CRT_HAVE_getpwuid
/* >> getpwuid(3)
 * Search for an entry with a matching user ID
 * @return: * :                         A pointer to the read password entry
 * @return: NULL: (errno = <unchanged>) No entry for `uid' exists
 * @return: NULL: (errno = <changed>)   Error (s.a. `errno') */
__CDECLARE(__ATTR_WUNUSED,struct passwd *,__NOTHROW_RPC,getpwuid,(__uid_t __uid),(__uid))
#elif defined(__CRT_HAVE_setpwent) && defined(__CRT_HAVE_getpwent)
#include <libc/local/pwd/getpwuid.h>
/* >> getpwuid(3)
 * Search for an entry with a matching user ID
 * @return: * :                         A pointer to the read password entry
 * @return: NULL: (errno = <unchanged>) No entry for `uid' exists
 * @return: NULL: (errno = <changed>)   Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(getpwuid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED struct passwd *__NOTHROW_RPC(__LIBCCALL getpwuid)(__uid_t __uid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getpwuid))(__uid); })
#endif /* ... */
#ifdef __CRT_HAVE_getpwnam
/* >> getpwnam(3)
 * Search for an entry with a matching username
 * @return: * :                         A pointer to the read password entry
 * @return: NULL: (errno = <unchanged>) No entry for `name' exists
 * @return: NULL: (errno = <changed>)   Error (s.a. `errno') */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),struct passwd *,__NOTHROW_RPC,getpwnam,(char const *__name),(__name))
#elif defined(__CRT_HAVE_setpwent) && defined(__CRT_HAVE_getpwent)
#include <libc/local/pwd/getpwnam.h>
/* >> getpwnam(3)
 * Search for an entry with a matching username
 * @return: * :                         A pointer to the read password entry
 * @return: NULL: (errno = <unchanged>) No entry for `name' exists
 * @return: NULL: (errno = <changed>)   Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(getpwnam, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) struct passwd *__NOTHROW_RPC(__LIBCCALL getpwnam)(char const *__name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getpwnam))(__name); })
#endif /* ... */

#ifdef __USE_MISC
/* >> fgetpwent(3)
 * Read an entry from `stream'
 * @return: * :                         A pointer to the read password entry
 * @return: NULL: (errno = <unchanged>) The last entry has already been read
 *                                      (use `rewind(stream)' to rewind the database)
 * @return: NULL: (errno = <changed>)   Error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_INOUT(1),struct passwd *,__NOTHROW_RPC,fgetpwent,(__FILE *__restrict __stream),(__stream))
#ifdef __CRT_HAVE_putpwent
/* >> putpwent(3)
 * Write the given entry `ent' into the given `stream'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(__ATTR_IN(1) __ATTR_INOUT(2),int,__NOTHROW_CB,putpwent,(struct passwd const *__restrict __ent, __FILE *__restrict __stream),(__ent,__stream))
#elif defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <libc/local/pwd/putpwent.h>
/* >> putpwent(3)
 * Write the given entry `ent' into the given `stream'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(putpwent, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_INOUT(2) int __NOTHROW_CB(__LIBCCALL putpwent)(struct passwd const *__restrict __ent, __FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putpwent))(__ent, __stream); })
#endif /* ... */
#endif /* __USE_MISC */

#ifdef __USE_POSIX
/* >> getpwuid_r(3)
 * Search for an entry with a matching user ID
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `uid'
 * @return: * : Error (one of `E*' from `<errno.h>') */
__CDECLARE_OPT(__ATTR_OUT(2) __ATTR_OUT(5) __ATTR_OUTS(3, 4),__errno_t,__NOTHROW_RPC,getpwuid_r,(__uid_t __uid, struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result),(__uid,__resultbuf,__buffer,__buflen,__result))
/* >> getpwnam_r(3)
 * Search for an entry with a matching username
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `name'
 * @return: * : Error (one of `E*' from `<errno.h>') */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2) __ATTR_OUT(5) __ATTR_OUTS(3, 4),__errno_t,__NOTHROW_RPC,getpwnam_r,(char const *__restrict __name, struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result),(__name,__resultbuf,__buffer,__buflen,__result))
#ifdef __USE_MISC
/* >> getpwent_r(3)
 * Read an entry from the password-file stream, opening it if necessary.
 * @return: 0 :     Success (`*result' is made to point at `resultbuf')
 * @return: ENOENT: The last entry has already been read (use `setpwent()' to rewind the database)
 * @return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
 * @return: * :     Error (one of `E*' from `<errno.h>') */
__CDECLARE_OPT(__ATTR_OUT(1) __ATTR_OUT(4) __ATTR_OUTS(2, 3),__errno_t,__NOTHROW_RPC,getpwent_r,(struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result),(__resultbuf,__buffer,__buflen,__result))
#ifdef __CRT_HAVE_fgetpwent_r
/* >> fgetpwent_r(3)
 * Read an entry from `stream'. This function is not standardized and probably never will be.
 * @return: 0 :     Success (`*result' is made to point at `resultbuf')
 * @return: ENOENT: The last entry has already been read (use `rewind(stream)' to rewind the database)
 * @return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
 * @return: * :     Error (one of `E*' from `<errno.h>') */
__CDECLARE(__ATTR_INOUT(1) __ATTR_OUT(2) __ATTR_OUT(5) __ATTR_OUTS(3, 4),__errno_t,__NOTHROW_RPC,fgetpwent_r,(__FILE *__restrict __stream, struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result),(__stream,__resultbuf,__buffer,__buflen,__result))
#else /* __CRT_HAVE_fgetpwent_r */
#include <bits/crt/stdio.h>
#if (defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE___ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)) && (defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || (defined(__SEEK_SET) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE___fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)))) && (defined(__CRT_HAVE_fparseln) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && (defined(__CRT_HAVE_feof) || defined(__CRT_HAVE__IO_feof) || defined(__CRT_HAVE_feof_unlocked))
#include <libc/local/pwd/fgetpwent_r.h>
/* >> fgetpwent_r(3)
 * Read an entry from `stream'. This function is not standardized and probably never will be.
 * @return: 0 :     Success (`*result' is made to point at `resultbuf')
 * @return: ENOENT: The last entry has already been read (use `rewind(stream)' to rewind the database)
 * @return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
 * @return: * :     Error (one of `E*' from `<errno.h>') */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetpwent_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_OUT(2) __ATTR_OUT(5) __ATTR_OUTS(3, 4) __errno_t __NOTHROW_RPC(__LIBCCALL fgetpwent_r)(__FILE *__restrict __stream, struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetpwent_r))(__stream, __resultbuf, __buffer, __buflen, __result); })
#endif /* (__CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_ftello64 || __CRT_HAVE___ftello64 || __CRT_HAVE_ftell64 || __CRT_HAVE__ftelli64 || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE_ftell64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked || __CRT_HAVE_ftell || __CRT_HAVE__IO_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock) && (__CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || (__SEEK_SET && (__CRT_HAVE_fseeko64 || __CRT_HAVE___fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock))) && (__CRT_HAVE_fparseln || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && (__CRT_HAVE_feof || __CRT_HAVE__IO_feof || __CRT_HAVE_feof_unlocked) */
#endif /* !__CRT_HAVE_fgetpwent_r */
#ifdef __USE_KOS
#ifdef __CRT_HAVE_fgetpwuid_r
/* >> fgetpwuid_r(3)
 * Search for an entry with a matching user ID
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `uid'
 * @return: * : Error (one of `E*' from `<errno.h>') */
__CDECLARE(__ATTR_INOUT(1) __ATTR_OUT(3) __ATTR_OUT(6) __ATTR_OUTS(4, 5),__errno_t,__NOTHROW_RPC,fgetpwuid_r,(__FILE *__restrict __stream, __uid_t __uid, struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result),(__stream,__uid,__resultbuf,__buffer,__buflen,__result))
#else /* __CRT_HAVE_fgetpwuid_r */
#include <bits/crt/stdio.h>
#if (defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE___ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)) && (defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || (defined(__SEEK_SET) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE___fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)))) && (defined(__CRT_HAVE_fparseln) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && (defined(__CRT_HAVE_feof) || defined(__CRT_HAVE__IO_feof) || defined(__CRT_HAVE_feof_unlocked))
#include <libc/local/pwd/fgetpwuid_r.h>
/* >> fgetpwuid_r(3)
 * Search for an entry with a matching user ID
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `uid'
 * @return: * : Error (one of `E*' from `<errno.h>') */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetpwuid_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_OUT(3) __ATTR_OUT(6) __ATTR_OUTS(4, 5) __errno_t __NOTHROW_RPC(__LIBCCALL fgetpwuid_r)(__FILE *__restrict __stream, __uid_t __uid, struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetpwuid_r))(__stream, __uid, __resultbuf, __buffer, __buflen, __result); })
#endif /* (__CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_ftello64 || __CRT_HAVE___ftello64 || __CRT_HAVE_ftell64 || __CRT_HAVE__ftelli64 || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE_ftell64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked || __CRT_HAVE_ftell || __CRT_HAVE__IO_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock) && (__CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || (__SEEK_SET && (__CRT_HAVE_fseeko64 || __CRT_HAVE___fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock))) && (__CRT_HAVE_fparseln || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && (__CRT_HAVE_feof || __CRT_HAVE__IO_feof || __CRT_HAVE_feof_unlocked) */
#endif /* !__CRT_HAVE_fgetpwuid_r */
#ifdef __CRT_HAVE_fgetpwnam_r
/* >> fgetpwnam_r(3)
 * Search for an entry with a matching username
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `name'
 * @return: * : Error (one of `E*' from `<errno.h>') */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_OUT(3) __ATTR_OUT(6) __ATTR_OUTS(4, 5),__errno_t,__NOTHROW_RPC,fgetpwnam_r,(__FILE *__restrict __stream, char const *__restrict __name, struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result),(__stream,__name,__resultbuf,__buffer,__buflen,__result))
#else /* __CRT_HAVE_fgetpwnam_r */
#include <bits/crt/stdio.h>
#if (defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE___ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)) && (defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || (defined(__SEEK_SET) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE___fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)))) && (defined(__CRT_HAVE_fparseln) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && (defined(__CRT_HAVE_feof) || defined(__CRT_HAVE__IO_feof) || defined(__CRT_HAVE_feof_unlocked))
#include <libc/local/pwd/fgetpwnam_r.h>
/* >> fgetpwnam_r(3)
 * Search for an entry with a matching username
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `name'
 * @return: * : Error (one of `E*' from `<errno.h>') */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetpwnam_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_OUT(3) __ATTR_OUT(6) __ATTR_OUTS(4, 5) __errno_t __NOTHROW_RPC(__LIBCCALL fgetpwnam_r)(__FILE *__restrict __stream, char const *__restrict __name, struct passwd *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct passwd **__restrict __result) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetpwnam_r))(__stream, __name, __resultbuf, __buffer, __buflen, __result); })
#endif /* (__CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_ftello64 || __CRT_HAVE___ftello64 || __CRT_HAVE_ftell64 || __CRT_HAVE__ftelli64 || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE_ftell64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked || __CRT_HAVE_ftell || __CRT_HAVE__IO_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock) && (__CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || (__SEEK_SET && (__CRT_HAVE_fseeko64 || __CRT_HAVE___fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock))) && (__CRT_HAVE_fparseln || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && (__CRT_HAVE_feof || __CRT_HAVE__IO_feof || __CRT_HAVE_feof_unlocked) */
#endif /* !__CRT_HAVE_fgetpwnam_r */
#endif /* __USE_KOS */
#endif /* __USE_MISC */
#endif	/* __USE_POSIX */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_getpw
/* >> getpw(3)
 * Re-construct the password-file line for the given uid in the
 * given  buffer. This  knows the  format that  the caller will
 * expect, but this need not be the format of the password file */
__CDECLARE(__ATTR_OUT(2),int,__NOTHROW_RPC,getpw,(__uid_t __uid, char *__buffer),(__uid,__buffer))
#elif defined(__CRT_HAVE_getpwuid) || (defined(__CRT_HAVE_setpwent) && defined(__CRT_HAVE_getpwent))
#include <libc/local/pwd/getpw.h>
/* >> getpw(3)
 * Re-construct the password-file line for the given uid in the
 * given  buffer. This  knows the  format that  the caller will
 * expect, but this need not be the format of the password file */
__NAMESPACE_LOCAL_USING_OR_IMPL(getpw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) int __NOTHROW_RPC(__LIBCCALL getpw)(__uid_t __uid, char *__buffer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getpw))(__uid, __buffer); })
#endif /* ... */
#endif /* __USE_GNU */

#ifdef __USE_BSD
#ifdef __CRT_HAVE_setpassent
__CDECLARE(,int,__NOTHROW_NCX,setpassent,(int __keep_open),(__keep_open))
#elif defined(__CRT_HAVE_setpwent)
#include <libc/local/pwd/setpassent.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(setpassent, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL setpassent)(int __keep_open) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setpassent))(__keep_open); })
#endif /* ... */
#ifndef __uid_from_user_defined
#define __uid_from_user_defined
#ifdef __CRT_HAVE_uid_from_user
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,uid_from_user,(char const *__name, uid_t *__p_uid),(__name,__p_uid))
#elif defined(__CRT_HAVE_getpwnam) || (defined(__CRT_HAVE_setpwent) && defined(__CRT_HAVE_getpwent))
#include <libc/local/pwd/uid_from_user.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(uid_from_user, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL uid_from_user)(char const *__name, uid_t *__p_uid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(uid_from_user))(__name, __p_uid); })
#else /* ... */
#undef __uid_from_user_defined
#endif /* !... */
#endif /* !__uid_from_user_defined */
#ifndef __user_from_uid_defined
#define __user_from_uid_defined
#ifdef __CRT_HAVE_user_from_uid
__CDECLARE(__ATTR_WUNUSED,char const *,__NOTHROW_NCX,user_from_uid,(uid_t __uid, int __nouser),(__uid,__nouser))
#elif defined(__CRT_HAVE_getpwuid) || (defined(__CRT_HAVE_setpwent) && defined(__CRT_HAVE_getpwent))
#include <libc/local/pwd/user_from_uid.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(user_from_uid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED char const *__NOTHROW_NCX(__LIBCCALL user_from_uid)(uid_t __uid, int __nouser) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(user_from_uid))(__uid, __nouser); })
#else /* ... */
#undef __user_from_uid_defined
#endif /* !... */
#endif /* !__user_from_uid_defined */
#ifdef __CRT_HAVE_pw_dup
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),struct passwd *,__NOTHROW_NCX,pw_dup,(struct passwd const *__ent),(__ent))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/pwd/pw_dup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(pw_dup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) struct passwd *__NOTHROW_NCX(__LIBCCALL pw_dup)(struct passwd const *__ent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pw_dup))(__ent); })
#endif /* ... */
#endif /* __USE_BSD */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PWD_H */
