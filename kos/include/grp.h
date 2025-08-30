/* HASH CRC-32:0x6e89ac79 */
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
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/grp.h) */
/* (#) Portability: DJGPP         (/include/grp.h) */
/* (#) Portability: DragonFly BSD (/include/grp.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/grp.h) */
/* (#) Portability: FreeBSD       (/include/grp.h) */
/* (#) Portability: GNU C Library (/nss/grp.h) */
/* (#) Portability: GNU Hurd      (/usr/include/grp.h) */
/* (#) Portability: NetBSD        (/include/grp.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/grp.h) */
/* (#) Portability: OpenBSD       (/include/grp.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/grp.h) */
/* (#) Portability: diet libc     (/include/grp.h) */
/* (#) Portability: libbsd        (/include/bsd/grp.h) */
/* (#) Portability: libc4/5       (/include/grp.h) */
/* (#) Portability: libc6         (/include/grp.h) */
/* (#) Portability: mintlib       (/include/grp.h) */
/* (#) Portability: musl libc     (/include/grp.h) */
/* (#) Portability: uClibc        (/include/grp.h) */
#ifndef _GRP_H
#define _GRP_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <bits/crt/db/group.h>
#include <bits/types.h>

#ifdef __INTELLISENSE__
#include <bits/types/FILE.h>
#include <bits/types/size_t.h>
#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#include <bits/types/gid_t.h>
#endif /* __USE_XOPEN || __USE_XOPEN2K */
#endif /* __INTELLISENSE__ */

#if defined(__USE_POSIX) && defined(__USE_MISC)
#define NSS_BUFLEN_GROUP 1024
#endif /* __USE_POSIX && __USE_MISC */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __gid_t_defined
#define __gid_t_defined
typedef __gid_t gid_t;
#endif /* !__gid_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#ifndef __FILE_defined
#define __FILE_defined
typedef __FILE FILE;
#endif /* !__FILE_defined */

#ifdef __CRT_HAVE_getgrgid
/* >> getgrgid(3), getgrgid_r(3) */
__CDECLARE(__ATTR_WUNUSED,struct group *,__NOTHROW_RPC,getgrgid,(__gid_t __gid),(__gid))
#elif defined(__CRT_HAVE_setgrent) && defined(__CRT_HAVE_getgrent)
#include <libc/local/grp/getgrgid.h>
/* >> getgrgid(3), getgrgid_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getgrgid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED struct group *__NOTHROW_RPC(__LIBCCALL getgrgid)(__gid_t __gid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getgrgid))(__gid); })
#endif /* ... */
#ifdef __CRT_HAVE_getgrnam
/* >> getgrnam(3), getgrnam_r(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),struct group *,__NOTHROW_RPC,getgrnam,(char const *__restrict __name),(__name))
#elif defined(__CRT_HAVE_setgrent) && defined(__CRT_HAVE_getgrent)
#include <libc/local/grp/getgrnam.h>
/* >> getgrnam(3), getgrnam_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getgrnam, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) struct group *__NOTHROW_RPC(__LIBCCALL getgrnam)(char const *__restrict __name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getgrnam))(__name); })
#endif /* ... */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
/* >> setgrent(3) */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,setgrent,(void),())
/* >> endgrent(3) */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC_NOKOS,endgrent,(void),())
/* >> getgrent(3), getgrent_r(3) */
__CDECLARE_OPT(__ATTR_WUNUSED,struct group *,__NOTHROW_RPC,getgrent,(void),())
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

#ifdef __USE_GNU
#ifdef __CRT_HAVE_putgrent
/* >> putgrent(3)
 * Write the given entry `ent' into the given `stream'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(__ATTR_IN(1) __ATTR_INOUT(2),int,__NOTHROW_CB_NCX,putgrent,(struct group const *__restrict __entry, __FILE *__restrict __stream),(__entry,__stream))
#elif defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <libc/local/grp/putgrent.h>
/* >> putgrent(3)
 * Write the given entry `ent' into the given `stream'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(putgrent, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_INOUT(2) int __NOTHROW_CB_NCX(__LIBCCALL putgrent)(struct group const *__restrict __entry, __FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putgrent))(__entry, __stream); })
#endif /* ... */
#endif /* __USE_GNU */

#ifdef __USE_POSIX
/* >> getgrgid(3), getgrgid_r(3) */
__CDECLARE_OPT(__ATTR_OUT(2) __ATTR_OUT(5) __ATTR_OUTS(3, 4),int,__NOTHROW_RPC,getgrgid_r,(__gid_t __gid, struct group *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct group **__restrict __result),(__gid,__resultbuf,__buffer,__buflen,__result))
/* >> getgrnam(3), getgrnam_r(3) */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2) __ATTR_OUT(5) __ATTR_OUTS(3, 4),int,__NOTHROW_RPC,getgrnam_r,(char const *__restrict __name, struct group *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct group **__restrict __result),(__name,__resultbuf,__buffer,__buflen,__result))

#ifdef __USE_GNU
/* >> getgrent(3), getgrent_r(3) */
__CDECLARE_OPT(__ATTR_OUT(1) __ATTR_OUT(4) __ATTR_OUTS(2, 3),int,__NOTHROW_RPC,getgrent_r,(struct group *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct group **__restrict __result),(__resultbuf,__buffer,__buflen,__result))
#endif /* __USE_GNU */

#ifdef __USE_MISC
#ifdef __CRT_HAVE_fgetgrent_r
/* >> fgetgrent(3), fgetgrent_r(3) */
__CDECLARE(__ATTR_INOUT(1) __ATTR_OUT(2) __ATTR_OUT(5) __ATTR_OUTS(3, 4),int,__NOTHROW_CB_NCX,fgetgrent_r,(__FILE *__restrict __stream, struct group *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct group **__restrict __result),(__stream,__resultbuf,__buffer,__buflen,__result))
#else /* __CRT_HAVE_fgetgrent_r */
#include <bits/crt/stdio.h>
#if (defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE___ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)) && (defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || (defined(__SEEK_SET) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE___fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)))) && (defined(__CRT_HAVE_fparseln) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && (defined(__CRT_HAVE_feof) || defined(__CRT_HAVE__IO_feof) || defined(__CRT_HAVE_feof_unlocked))
#include <libc/local/grp/fgetgrent_r.h>
/* >> fgetgrent(3), fgetgrent_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetgrent_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_OUT(2) __ATTR_OUT(5) __ATTR_OUTS(3, 4) int __NOTHROW_CB_NCX(__LIBCCALL fgetgrent_r)(__FILE *__restrict __stream, struct group *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct group **__restrict __result) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetgrent_r))(__stream, __resultbuf, __buffer, __buflen, __result); })
#endif /* (__CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_ftello64 || __CRT_HAVE___ftello64 || __CRT_HAVE_ftell64 || __CRT_HAVE__ftelli64 || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE_ftell64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked || __CRT_HAVE_ftell || __CRT_HAVE__IO_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock) && (__CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || (__SEEK_SET && (__CRT_HAVE_fseeko64 || __CRT_HAVE___fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock))) && (__CRT_HAVE_fparseln || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && (__CRT_HAVE_feof || __CRT_HAVE__IO_feof || __CRT_HAVE_feof_unlocked) */
#endif /* !__CRT_HAVE_fgetgrent_r */
#ifdef __USE_KOS
#ifdef __CRT_HAVE_fgetgrgid_r
/* >> fgetgrgid_r(3)
 * Search for an entry with a matching user ID
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `gid'
 * @return: * : Error (one of `E*' from `<errno.h>') */
__CDECLARE(__ATTR_INOUT(1) __ATTR_OUT(3) __ATTR_OUT(6) __ATTR_OUTS(4, 5),__errno_t,__NOTHROW_CB_NCX,fgetgrgid_r,(__FILE *__restrict __stream, __gid_t __gid, struct group *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct group **__restrict __result),(__stream,__gid,__resultbuf,__buffer,__buflen,__result))
#else /* __CRT_HAVE_fgetgrgid_r */
#include <bits/crt/stdio.h>
#if (defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE___ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)) && (defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || (defined(__SEEK_SET) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE___fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)))) && (defined(__CRT_HAVE_fparseln) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && (defined(__CRT_HAVE_feof) || defined(__CRT_HAVE__IO_feof) || defined(__CRT_HAVE_feof_unlocked))
#include <libc/local/grp/fgetgrgid_r.h>
/* >> fgetgrgid_r(3)
 * Search for an entry with a matching user ID
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `gid'
 * @return: * : Error (one of `E*' from `<errno.h>') */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetgrgid_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_OUT(3) __ATTR_OUT(6) __ATTR_OUTS(4, 5) __errno_t __NOTHROW_CB_NCX(__LIBCCALL fgetgrgid_r)(__FILE *__restrict __stream, __gid_t __gid, struct group *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct group **__restrict __result) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetgrgid_r))(__stream, __gid, __resultbuf, __buffer, __buflen, __result); })
#endif /* (__CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_ftello64 || __CRT_HAVE___ftello64 || __CRT_HAVE_ftell64 || __CRT_HAVE__ftelli64 || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE_ftell64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked || __CRT_HAVE_ftell || __CRT_HAVE__IO_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock) && (__CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || (__SEEK_SET && (__CRT_HAVE_fseeko64 || __CRT_HAVE___fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock))) && (__CRT_HAVE_fparseln || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && (__CRT_HAVE_feof || __CRT_HAVE__IO_feof || __CRT_HAVE_feof_unlocked) */
#endif /* !__CRT_HAVE_fgetgrgid_r */
#ifdef __CRT_HAVE_fgetgrnam_r
/* >> fgetgrnam_r(3)
 * Search for an entry with a matching username
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `name'
 * @return: * : Error (one of `E*' from `<errno.h>') */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_OUT(3) __ATTR_OUT(6) __ATTR_OUTS(4, 5),__errno_t,__NOTHROW_CB_NCX,fgetgrnam_r,(__FILE *__restrict __stream, char const *__restrict __name, struct group *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct group **__restrict __result),(__stream,__name,__resultbuf,__buffer,__buflen,__result))
#else /* __CRT_HAVE_fgetgrnam_r */
#include <bits/crt/stdio.h>
#if (defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE___ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)) && (defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || (defined(__SEEK_SET) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE___fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)))) && (defined(__CRT_HAVE_fparseln) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && (defined(__CRT_HAVE_feof) || defined(__CRT_HAVE__IO_feof) || defined(__CRT_HAVE_feof_unlocked))
#include <libc/local/grp/fgetgrnam_r.h>
/* >> fgetgrnam_r(3)
 * Search for an entry with a matching username
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `name'
 * @return: * : Error (one of `E*' from `<errno.h>') */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetgrnam_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_OUT(3) __ATTR_OUT(6) __ATTR_OUTS(4, 5) __errno_t __NOTHROW_CB_NCX(__LIBCCALL fgetgrnam_r)(__FILE *__restrict __stream, char const *__restrict __name, struct group *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct group **__restrict __result) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetgrnam_r))(__stream, __name, __resultbuf, __buffer, __buflen, __result); })
#endif /* (__CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_ftello64 || __CRT_HAVE___ftello64 || __CRT_HAVE_ftell64 || __CRT_HAVE__ftelli64 || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE_ftell64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked || __CRT_HAVE_ftell || __CRT_HAVE__IO_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock) && (__CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || (__SEEK_SET && (__CRT_HAVE_fseeko64 || __CRT_HAVE___fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock))) && (__CRT_HAVE_fparseln || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && (__CRT_HAVE_feof || __CRT_HAVE__IO_feof || __CRT_HAVE_feof_unlocked) */
#endif /* !__CRT_HAVE_fgetgrnam_r */
#endif /* __USE_KOS */
#endif /* __USE_MISC */
#endif /* __USE_POSIX */

#ifdef __USE_MISC
/* >> fgetgrent(3), fgetgrent_r(3) */
__CDECLARE_OPT(__ATTR_INOUT(1),struct group *,__NOTHROW_CB_NCX,fgetgrent,(__FILE *__restrict __stream),(__stream))
#ifndef __setgroups_defined
#define __setgroups_defined
#ifdef __CRT_HAVE_setgroups
/* >> setgroups(2) */
__CDECLARE(__ATTR_INS(2, 1),int,__NOTHROW_RPC,setgroups,(size_t __count, __gid_t const *__groups),(__count,__groups))
#elif defined(__CRT_HAVE___setgroups)
/* >> setgroups(2) */
__CREDIRECT(__ATTR_INS(2, 1),int,__NOTHROW_RPC,setgroups,(size_t __count, __gid_t const *__groups),__setgroups,(__count,__groups))
#elif defined(__CRT_HAVE___libc_setgroups)
/* >> setgroups(2) */
__CREDIRECT(__ATTR_INS(2, 1),int,__NOTHROW_RPC,setgroups,(size_t __count, __gid_t const *__groups),__libc_setgroups,(__count,__groups))
#else /* ... */
#undef __setgroups_defined
#endif /* !... */
#endif /* !__setgroups_defined */
#ifndef __getgrouplist_defined
#define __getgrouplist_defined
#ifdef __CRT_HAVE_getgrouplist
/* >> getgrouplist(3)
 * Use the groups database to find the GIDs of all of the groups which `user'
 * is apart of. In case this list doesn't already include `group', it will be
 * inserted into the list (thus making sure that it is always a member).
 * @param: user:    The name to seach for in the member lists of groups.
 * @param: group:   Usually, the default group of `user' (as retrieved from  the
 *                  functions from `<pwd.h>'). This group will always be made to
 *                  be a member of the list of GIDs written to `*groups'
 * @param: groups:  Output buffer for GIDs
 * @param: ngroups: [in]  The buffer length (max #  of elements) that can be  stored
 *                        in the given buffer before it become full. When this limit
 *                  [out] The required buffer size (in elements). Upon success, the
 *                        value written  here is  identical  to the  return  value.
 * @return: * : [== *ngroups] The number of items written to `groups'
 * @return: -1: More than `IN(*ngroups)' elements would have been written to  `groups'.
 *              In this case, `OUT(*ngroups)' specifies the number of required elements
 *              in terms of buffer  size to write  all groups (use  this to resize  the
 *              buffer you're passing for `groups').
 *              Note that standards don't say anything about `errno' in this case,
 *              so the KOS implementation of this function simply leaves its value
 *              untouched when this happens (other implementations might set it to
 *              `ERANGE' for example...) */
__CDECLARE(__ATTR_IN(1) __ATTR_INOUT(4) __ATTR_OUT(3),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,getgrouplist,(char const *__user, __gid_t __group, __gid_t *__groups, __STDC_INT_AS_SIZE_T *__ngroups),(__user,__group,__groups,__ngroups))
#elif defined(__CRT_HAVE_setgrent) && defined(__CRT_HAVE_getgrent)
#include <libc/local/grp/getgrouplist.h>
/* >> getgrouplist(3)
 * Use the groups database to find the GIDs of all of the groups which `user'
 * is apart of. In case this list doesn't already include `group', it will be
 * inserted into the list (thus making sure that it is always a member).
 * @param: user:    The name to seach for in the member lists of groups.
 * @param: group:   Usually, the default group of `user' (as retrieved from  the
 *                  functions from `<pwd.h>'). This group will always be made to
 *                  be a member of the list of GIDs written to `*groups'
 * @param: groups:  Output buffer for GIDs
 * @param: ngroups: [in]  The buffer length (max #  of elements) that can be  stored
 *                        in the given buffer before it become full. When this limit
 *                  [out] The required buffer size (in elements). Upon success, the
 *                        value written  here is  identical  to the  return  value.
 * @return: * : [== *ngroups] The number of items written to `groups'
 * @return: -1: More than `IN(*ngroups)' elements would have been written to  `groups'.
 *              In this case, `OUT(*ngroups)' specifies the number of required elements
 *              in terms of buffer  size to write  all groups (use  this to resize  the
 *              buffer you're passing for `groups').
 *              Note that standards don't say anything about `errno' in this case,
 *              so the KOS implementation of this function simply leaves its value
 *              untouched when this happens (other implementations might set it to
 *              `ERANGE' for example...) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getgrouplist, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_INOUT(4) __ATTR_OUT(3) __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__LIBCCALL getgrouplist)(char const *__user, __gid_t __group, __gid_t *__groups, __STDC_INT_AS_SIZE_T *__ngroups) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getgrouplist))(__user, __group, __groups, __ngroups); })
#else /* ... */
#undef __getgrouplist_defined
#endif /* !... */
#endif /* !__getgrouplist_defined */
#ifndef __initgroups_defined
#define __initgroups_defined
#ifdef __CRT_HAVE_initgroups
/* >> initgroups(3)
 * A helper function that combines `getgrouplist(3)' with `setgroups(2)',
 * and can be used to set the calling process's group list to that of the
 * given user, whilst always being guarantied to also include `group'!
 * @return: 0 : Success
 * @return: -1: [errno=ENOMEM] Out of member
 * @return: -1: [errno=EPERM]  You're not allowed  to call  `setgroups(2)',
 *                             or at least not in the way you're trying to. */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,initgroups,(char const *__user, __gid_t __group),(__user,__group))
#elif (defined(__CRT_HAVE_getgrouplist) || (defined(__CRT_HAVE_setgrent) && defined(__CRT_HAVE_getgrent))) && (defined(__CRT_HAVE_setgroups) || defined(__CRT_HAVE___setgroups) || defined(__CRT_HAVE___libc_setgroups)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/grp/initgroups.h>
/* >> initgroups(3)
 * A helper function that combines `getgrouplist(3)' with `setgroups(2)',
 * and can be used to set the calling process's group list to that of the
 * given user, whilst always being guarantied to also include `group'!
 * @return: 0 : Success
 * @return: -1: [errno=ENOMEM] Out of member
 * @return: -1: [errno=EPERM]  You're not allowed  to call  `setgroups(2)',
 *                             or at least not in the way you're trying to. */
__NAMESPACE_LOCAL_USING_OR_IMPL(initgroups, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL initgroups)(char const *__user, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(initgroups))(__user, __group); })
#else /* ... */
#undef __initgroups_defined
#endif /* !... */
#endif /* !__initgroups_defined */
#endif /* __USE_MISC */

#ifdef __USE_BSD
#ifdef __CRT_HAVE_setgroupent
__CDECLARE(,int,__NOTHROW_NCX,setgroupent,(int __keep_open),(__keep_open))
#elif defined(__CRT_HAVE_setgrent)
#include <libc/local/grp/setgroupent.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(setgroupent, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL setgroupent)(int __keep_open) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setgroupent))(__keep_open); })
#endif /* ... */
#ifndef __gid_from_group_defined
#define __gid_from_group_defined
#ifdef __CRT_HAVE_gid_from_group
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,gid_from_group,(char const *__name, gid_t *__p_gid),(__name,__p_gid))
#elif defined(__CRT_HAVE_getgrnam) || (defined(__CRT_HAVE_setgrent) && defined(__CRT_HAVE_getgrent))
#include <libc/local/grp/gid_from_group.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(gid_from_group, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL gid_from_group)(char const *__name, gid_t *__p_gid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gid_from_group))(__name, __p_gid); })
#else /* ... */
#undef __gid_from_group_defined
#endif /* !... */
#endif /* !__gid_from_group_defined */
#ifndef __group_from_gid_defined
#define __group_from_gid_defined
#ifdef __CRT_HAVE_group_from_gid
__CDECLARE(__ATTR_WUNUSED,char const *,__NOTHROW_NCX,group_from_gid,(gid_t __gid, int __nogroup),(__gid,__nogroup))
#elif defined(__CRT_HAVE_getgrgid) || (defined(__CRT_HAVE_setgrent) && defined(__CRT_HAVE_getgrent))
#include <libc/local/grp/group_from_gid.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(group_from_gid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED char const *__NOTHROW_NCX(__LIBCCALL group_from_gid)(gid_t __gid, int __nogroup) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(group_from_gid))(__gid, __nogroup); })
#else /* ... */
#undef __group_from_gid_defined
#endif /* !... */
#endif /* !__group_from_gid_defined */
#endif /* __USE_BSD */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_GRP_H */
