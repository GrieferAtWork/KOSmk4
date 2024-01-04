/* HASH CRC-32:0x7c24bd82 */
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
/* (#) Portability: libbsd (/include/bsd/string.h) */
#ifndef _BSD_STRING_H
#define _BSD_STRING_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <string.h>
#include <features.h>
#include <bits/types.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __strlcpy_defined
#define __strlcpy_defined
#ifdef __CRT_HAVE_strlcpy
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,strlcpy,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __bufsize),(__dst,__src,__bufsize))
#else /* __CRT_HAVE_strlcpy */
#include <libc/local/string/strlcpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strlcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strlcpy)(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlcpy))(__dst, __src, __bufsize); })
#endif /* !__CRT_HAVE_strlcpy */
#endif /* !__strlcpy_defined */
#ifndef __strlcat_defined
#define __strlcat_defined
#ifdef __CRT_HAVE_strlcat
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,strlcat,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __bufsize),(__dst,__src,__bufsize))
#else /* __CRT_HAVE_strlcat */
#include <libc/local/string/strlcat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strlcat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strlcat)(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlcat))(__dst, __src, __bufsize); })
#endif /* !__CRT_HAVE_strlcat */
#endif /* !__strlcat_defined */
#ifndef __strnstr_defined
#define __strnstr_defined
#ifdef __CRT_HAVE_strnstr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strnstr(3)
 * Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If   found,   return  a   pointer   to  its   location   within  `str',   else   return  `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnstr,(char *__haystack, char const *__needle, __SIZE_TYPE__ __haystack_maxlen),strnstr,(__haystack,__needle,__haystack_maxlen))
/* >> strnstr(3)
 * Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If   found,   return  a   pointer   to  its   location   within  `str',   else   return  `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strnstr,(char const *__haystack, char const *__needle, __SIZE_TYPE__ __haystack_maxlen),strnstr,(__haystack,__needle,__haystack_maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strnstr(3)
 * Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If   found,   return  a   pointer   to  its   location   within  `str',   else   return  `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnstr,(char const *__haystack, char const *__needle, __SIZE_TYPE__ __haystack_maxlen),(__haystack,__needle,__haystack_maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strnstr */
#include <libc/local/string/strnstr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strnstr(3)
 * Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If   found,   return  a   pointer   to  its   location   within  `str',   else   return  `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnstr)(char *__haystack, char const *__needle, __SIZE_TYPE__ __haystack_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnstr))(__haystack, __needle, __haystack_maxlen); }
/* >> strnstr(3)
 * Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If   found,   return  a   pointer   to  its   location   within  `str',   else   return  `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strnstr)(char const *__haystack, char const *__needle, __SIZE_TYPE__ __haystack_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnstr))(__haystack, __needle, __haystack_maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strnstr(3)
 * Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If   found,   return  a   pointer   to  its   location   within  `str',   else   return  `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnstr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnstr)(char const *__haystack, char const *__needle, __SIZE_TYPE__ __haystack_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnstr))(__haystack, __needle, __haystack_maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strnstr */
#endif /* !__strnstr_defined */
#ifndef __strmode_defined
#define __strmode_defined
#ifdef __CRT_HAVE_strmode
/* Generate  a file mode representation similar to what's printed by `ls -l'
 * The representation is written to `p', and `mode' is the value as returned
 * by `stat(2)' in `struct stat::st_mode'
 * The format written is:
 *    p[0]  = <mode & S_IFMT>: { S_IFDIR: 'd', S_IFCHR: 'c', S_IFBLK:  'b',
 *                               S_IFREG: '-', S_IFLNK: 'l', S_IFSOCK: 's',
 *                               S_IFIFO: 'p' }, else: '?';
 *    p[1]  = mode & S_IRUSR ? 'r' : '-';
 *    p[2]  = mode & S_IWUSR ? 'w' : '-';
 *    p[3]  = <mode & S_IXUSR | S_ISUID>: { 0: '-', S_IXUSR: 'x', S_ISUID: 'S',
 *                                          S_IXUSR | S_ISUID: 's' };
 *    p[4] = mode & S_IRGRP ? 'r' : '-';
 *    p[5] = mode & S_IWGRP ? 'w' : '-';
 *    p[6]  = <mode & S_IXGRP | S_ISGID>: { 0: '-', S_IXGRP: 'x', S_ISGID: 'S',
 *                                          S_IXGRP | S_ISGID: 's' };
 *    p[7] = mode & S_IROTH ? 'r' : '-';
 *    p[8] = mode & S_IWOTH ? 'w' : '-';
 *    p[9]  = <mode & S_IXOTH | S_ISVTX>: { 0: '-', S_IXOTH: 'x', S_ISVTX: 'T',
 *                                          S_IXOTH | S_ISVTX: 't' };
 *    p[10] = ' '; // '+', if "alternate or additional access control
 *                 //          methods associated with the inode"
 *    p[11] = '\0'; */
__CDECLARE_VOID(__ATTR_OUT(2),__NOTHROW_NCX,strmode,(__mode_t __mode, char __p[12]),(__mode,__p))
#else /* __CRT_HAVE_strmode */
#include <libc/local/string/strmode.h>
/* Generate  a file mode representation similar to what's printed by `ls -l'
 * The representation is written to `p', and `mode' is the value as returned
 * by `stat(2)' in `struct stat::st_mode'
 * The format written is:
 *    p[0]  = <mode & S_IFMT>: { S_IFDIR: 'd', S_IFCHR: 'c', S_IFBLK:  'b',
 *                               S_IFREG: '-', S_IFLNK: 'l', S_IFSOCK: 's',
 *                               S_IFIFO: 'p' }, else: '?';
 *    p[1]  = mode & S_IRUSR ? 'r' : '-';
 *    p[2]  = mode & S_IWUSR ? 'w' : '-';
 *    p[3]  = <mode & S_IXUSR | S_ISUID>: { 0: '-', S_IXUSR: 'x', S_ISUID: 'S',
 *                                          S_IXUSR | S_ISUID: 's' };
 *    p[4] = mode & S_IRGRP ? 'r' : '-';
 *    p[5] = mode & S_IWGRP ? 'w' : '-';
 *    p[6]  = <mode & S_IXGRP | S_ISGID>: { 0: '-', S_IXGRP: 'x', S_ISGID: 'S',
 *                                          S_IXGRP | S_ISGID: 's' };
 *    p[7] = mode & S_IROTH ? 'r' : '-';
 *    p[8] = mode & S_IWOTH ? 'w' : '-';
 *    p[9]  = <mode & S_IXOTH | S_ISVTX>: { 0: '-', S_IXOTH: 'x', S_ISVTX: 'T',
 *                                          S_IXOTH | S_ISVTX: 't' };
 *    p[10] = ' '; // '+', if "alternate or additional access control
 *                 //          methods associated with the inode"
 *    p[11] = '\0'; */
__NAMESPACE_LOCAL_USING_OR_IMPL(strmode, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) void __NOTHROW_NCX(__LIBCCALL strmode)(__mode_t __mode, char __p[12]) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strmode))(__mode, __p); })
#endif /* !__CRT_HAVE_strmode */
#endif /* !__strmode_defined */
#ifndef __explicit_bzero_defined
#define __explicit_bzero_defined
#ifdef __CRT_HAVE_bzero
/* >> explicit_bzero(3)
 * Same  as  `bzero(dst, n_bytes)', however  compilers will  not optimize
 * away uses of this function when they (think) that clearing the  memory
 * wouldn't  have  any  visible side-effects  (though  those side-effects
 * may be a security-conscious application trying to wipe sensitive data) */
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,explicit_bzero,(void *__dst, size_t __n_bytes),bzero,(__dst,__n_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
/* >> explicit_bzero(3)
 * Same  as  `bzero(dst, n_bytes)', however  compilers will  not optimize
 * away uses of this function when they (think) that clearing the  memory
 * wouldn't  have  any  visible side-effects  (though  those side-effects
 * may be a security-conscious application trying to wipe sensitive data) */
__CDECLARE_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,explicit_bzero,(void *__dst, size_t __n_bytes),(__dst,__n_bytes))
#elif defined(__CRT_HAVE___bzero)
/* >> explicit_bzero(3)
 * Same  as  `bzero(dst, n_bytes)', however  compilers will  not optimize
 * away uses of this function when they (think) that clearing the  memory
 * wouldn't  have  any  visible side-effects  (though  those side-effects
 * may be a security-conscious application trying to wipe sensitive data) */
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,explicit_bzero,(void *__dst, size_t __n_bytes),__bzero,(__dst,__n_bytes))
#else /* ... */
#include <libc/local/strings/explicit_bzero.h>
/* >> explicit_bzero(3)
 * Same  as  `bzero(dst, n_bytes)', however  compilers will  not optimize
 * away uses of this function when they (think) that clearing the  memory
 * wouldn't  have  any  visible side-effects  (though  those side-effects
 * may be a security-conscious application trying to wipe sensitive data) */
__NAMESPACE_LOCAL_USING_OR_IMPL(explicit_bzero, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(1, 2) void __NOTHROW_NCX(__LIBCCALL explicit_bzero)(void *__dst, size_t __n_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(explicit_bzero))(__dst, __n_bytes); })
#endif /* !... */
#endif /* !__explicit_bzero_defined */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BSD_STRING_H */
