/* HASH CRC-32:0xa83f14df */
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
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/newlib/libc/include/glob.h) */
/* (#) Portability: DJGPP         (/include/glob.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/glob.h) */
/* (#) Portability: FreeBSD       (/include/glob.h) */
/* (#) Portability: GNU C Library (/posix/glob.h) */
/* (#) Portability: MinGW         (/include/glob.h) */
/* (#) Portability: NetBSD        (/include/glob.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/glob.h) */
/* (#) Portability: OpenBSD       (/include/glob.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/glob.h) */
/* (#) Portability: diet libc     (/include/glob.h) */
/* (#) Portability: libc4/5       (/include/glob.h) */
/* (#) Portability: libc6         (/include/glob.h) */
/* (#) Portability: mintlib       (/include/glob.h) */
/* (#) Portability: musl libc     (/include/glob.h) */
/* (#) Portability: uClibc        (/include/glob.h) */
#ifndef _GLOB_H
#define _GLOB_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/crt/glob.h>
#include <bits/crt/glob.h>
#include <bits/types.h>

/* Flags accepted by the `flags' argument of `glob(3)' */
#if !defined(GLOB_ERR) && defined(__GLOB_ERR)
#define GLOB_ERR         __GLOB_ERR         /* ??? */
#endif /* !GLOB_ERR && __GLOB_ERR */
#if !defined(GLOB_MARK) && defined(__GLOB_MARK)
#define GLOB_MARK        __GLOB_MARK        /* ??? */
#endif /* !GLOB_MARK && __GLOB_MARK */
#if !defined(GLOB_NOSORT) && defined(__GLOB_NOSORT)
#define GLOB_NOSORT      __GLOB_NOSORT      /* ??? */
#endif /* !GLOB_NOSORT && __GLOB_NOSORT */
#if !defined(GLOB_DOOFFS) && defined(__GLOB_DOOFFS)
#define GLOB_DOOFFS      __GLOB_DOOFFS      /* ??? */
#endif /* !GLOB_DOOFFS && __GLOB_DOOFFS */
#if !defined(GLOB_NOCHECK) && defined(__GLOB_NOCHECK)
#define GLOB_NOCHECK     __GLOB_NOCHECK     /* ??? */
#endif /* !GLOB_NOCHECK && __GLOB_NOCHECK */
#if !defined(GLOB_APPEND) && defined(__GLOB_APPEND)
#define GLOB_APPEND      __GLOB_APPEND      /* ??? */
#endif /* !GLOB_APPEND && __GLOB_APPEND */
#if !defined(GLOB_NOESCAPE) && defined(__GLOB_NOESCAPE)
#define GLOB_NOESCAPE    __GLOB_NOESCAPE    /* ??? */
#endif /* !GLOB_NOESCAPE && __GLOB_NOESCAPE */
#if !defined(GLOB_PERIOD) && defined(__GLOB_PERIOD)
#define GLOB_PERIOD      __GLOB_PERIOD      /* ??? */
#endif /* !GLOB_PERIOD && __GLOB_PERIOD */

#ifdef __GLOB_ERR
#define __PRIVATE_GLOB_ERR __GLOB_ERR
#else /* __GLOB_ERR */
#define __PRIVATE_GLOB_ERR 0
#endif /* !__GLOB_ERR */
#ifdef __GLOB_MARK
#define __PRIVATE_GLOB_MARK __GLOB_MARK
#else /* __GLOB_MARK */
#define __PRIVATE_GLOB_MARK 0
#endif /* !__GLOB_MARK */
#ifdef __GLOB_NOSORT
#define __PRIVATE_GLOB_NOSORT __GLOB_NOSORT
#else /* __GLOB_NOSORT */
#define __PRIVATE_GLOB_NOSORT 0
#endif /* !__GLOB_NOSORT */
#ifdef __GLOB_DOOFFS
#define __PRIVATE_GLOB_DOOFFS __GLOB_DOOFFS
#else /* __GLOB_DOOFFS */
#define __PRIVATE_GLOB_DOOFFS 0
#endif /* !__GLOB_DOOFFS */
#ifdef __GLOB_NOESCAPE
#define __PRIVATE_GLOB_NOESCAPE __GLOB_NOESCAPE
#else /* __GLOB_NOESCAPE */
#define __PRIVATE_GLOB_NOESCAPE 0
#endif /* !__GLOB_NOESCAPE */
#ifdef __GLOB_NOCHECK
#define __PRIVATE_GLOB_NOCHECK __GLOB_NOCHECK
#else /* __GLOB_NOCHECK */
#define __PRIVATE_GLOB_NOCHECK 0
#endif /* !__GLOB_NOCHECK */
#ifdef __GLOB_APPEND
#define __PRIVATE_GLOB_APPEND __GLOB_APPEND
#else /* __GLOB_APPEND */
#define __PRIVATE_GLOB_APPEND 0
#endif /* !__GLOB_APPEND */
#ifdef __GLOB_PERIOD
#define __PRIVATE_GLOB_PERIOD __GLOB_PERIOD
#else /* __GLOB_PERIOD */
#define __PRIVATE_GLOB_PERIOD 0
#endif /* !__GLOB_PERIOD */

#if !defined(__USE_POSIX2) || defined(__USE_MISC)
#if !defined(GLOB_MAGCHAR) && defined(__GLOB_MAGCHAR)
#define GLOB_MAGCHAR     __GLOB_MAGCHAR     /* ??? */
#endif /* !GLOB_MAGCHAR && __GLOB_MAGCHAR */
#if !defined(GLOB_ALTDIRFUNC) && defined(__GLOB_ALTDIRFUNC)
#define GLOB_ALTDIRFUNC  __GLOB_ALTDIRFUNC  /* ??? */
#endif /* !GLOB_ALTDIRFUNC && __GLOB_ALTDIRFUNC */
#if !defined(GLOB_BRACE) && defined(__GLOB_BRACE)
#define GLOB_BRACE       __GLOB_BRACE       /* ??? */
#endif /* !GLOB_BRACE && __GLOB_BRACE */
#if !defined(GLOB_NOMAGIC) && defined(__GLOB_NOMAGIC)
#define GLOB_NOMAGIC     __GLOB_NOMAGIC     /* ??? */
#endif /* !GLOB_NOMAGIC && __GLOB_NOMAGIC */
#if !defined(GLOB_TILDE) && defined(__GLOB_TILDE)
#define GLOB_TILDE       __GLOB_TILDE       /* ??? */
#endif /* !GLOB_TILDE && __GLOB_TILDE */
#if !defined(GLOB_ONLYDIR) && defined(__GLOB_ONLYDIR)
#define GLOB_ONLYDIR     __GLOB_ONLYDIR     /* ??? */
#endif /* !GLOB_ONLYDIR && __GLOB_ONLYDIR */
#if !defined(GLOB_TILDE_CHECK) && defined(__GLOB_TILDE_CHECK)
#define GLOB_TILDE_CHECK __GLOB_TILDE_CHECK /* ??? */
#endif /* !GLOB_TILDE_CHECK && __GLOB_TILDE_CHECK */

#ifdef __GLOB_ALTDIRFUNC
#define __PRIVATE_GLOB_ALTDIRFUNC __GLOB_ALTDIRFUNC
#else /* __GLOB_ALTDIRFUNC */
#define __PRIVATE_GLOB_ALTDIRFUNC 0
#endif /* !__GLOB_ALTDIRFUNC */
#ifdef __GLOB_BRACE
#define __PRIVATE_GLOB_BRACE __GLOB_BRACE
#else /* __GLOB_BRACE */
#define __PRIVATE_GLOB_BRACE 0
#endif /* !__GLOB_BRACE */
#ifdef __GLOB_NOMAGIC
#define __PRIVATE_GLOB_NOMAGIC __GLOB_NOMAGIC
#else /* __GLOB_NOMAGIC */
#define __PRIVATE_GLOB_NOMAGIC 0
#endif /* !__GLOB_NOMAGIC */
#ifdef __GLOB_TILDE
#define __PRIVATE_GLOB_TILDE __GLOB_TILDE
#else /* __GLOB_TILDE */
#define __PRIVATE_GLOB_TILDE 0
#endif /* !__GLOB_TILDE */
#ifdef __GLOB_ONLYDIR
#define __PRIVATE_GLOB_ONLYDIR __GLOB_ONLYDIR
#else /* __GLOB_ONLYDIR */
#define __PRIVATE_GLOB_ONLYDIR 0
#endif /* !__GLOB_ONLYDIR */
#ifdef __GLOB_TILDE_CHECK
#define __PRIVATE_GLOB_TILDE_CHECK __GLOB_TILDE_CHECK
#else /* __GLOB_TILDE_CHECK */
#define __PRIVATE_GLOB_TILDE_CHECK 0
#endif /* !__GLOB_TILDE_CHECK */
#define __GLOB_FLAGS                                                                            \
	(__PRIVATE_GLOB_ERR | __PRIVATE_GLOB_MARK | __PRIVATE_GLOB_NOSORT | __PRIVATE_GLOB_DOOFFS | \
	 __PRIVATE_GLOB_NOESCAPE | __PRIVATE_GLOB_NOCHECK | __PRIVATE_GLOB_APPEND |                 \
	 __PRIVATE_GLOB_PERIOD | __PRIVATE_GLOB_ALTDIRFUNC | __PRIVATE_GLOB_BRACE |                 \
	 __PRIVATE_GLOB_NOMAGIC | __PRIVATE_GLOB_TILDE | __PRIVATE_GLOB_ONLYDIR |                   \
	 __PRIVATE_GLOB_TILDE_CHECK)
#else /* !__USE_POSIX2 || __USE_MISC */
#define __GLOB_FLAGS                                                                            \
	(__PRIVATE_GLOB_ERR | __PRIVATE_GLOB_MARK | __PRIVATE_GLOB_NOSORT | __PRIVATE_GLOB_DOOFFS | \
	 __PRIVATE_GLOB_NOESCAPE | __PRIVATE_GLOB_NOCHECK | __PRIVATE_GLOB_APPEND |                 \
	 __PRIVATE_GLOB_PERIOD)
#endif /* __USE_POSIX2 && !__USE_MISC */

/* Returns values for `glob(3)' */
#if !defined(GLOB_NOSPACE) && defined(__GLOB_NOSPACE)
#define GLOB_NOSPACE __GLOB_NOSPACE /* ??? */
#endif /* !GLOB_NOSPACE && __GLOB_NOSPACE */
#if !defined(GLOB_ABORTED) && defined(__GLOB_ABORTED)
#define GLOB_ABORTED __GLOB_ABORTED /* ??? */
#endif /* !GLOB_ABORTED && __GLOB_ABORTED */
#if !defined(GLOB_NOMATCH) && defined(__GLOB_NOMATCH)
#define GLOB_NOMATCH __GLOB_NOMATCH /* ??? */
#endif /* !GLOB_NOMATCH && __GLOB_NOMATCH */
#if !defined(GLOB_NOSYS) && defined(__GLOB_NOSYS)
#define GLOB_NOSYS   __GLOB_NOSYS   /* ??? */
#endif /* !GLOB_NOSYS && __GLOB_NOSYS */

#ifdef __USE_GNU
#if !defined(GLOB_ABEND) && defined(__GLOB_ABORTED)
#define GLOB_ABEND __GLOB_ABORTED /* Old alias */
#endif /* !GLOB_ABEND && __GLOB_ABORTED */
#endif /* __USE_GNU */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

typedef struct __glob_struct glob_t;
#ifdef __USE_LARGEFILE64
typedef struct __glob64_struct glob64_t;
#endif /* __USE_LARGEFILE64 */

#ifndef ____glob_errfunc_t_defined
#define ____glob_errfunc_t_defined
#endif /* !____glob_errfunc_t_defined */

#if defined(__CRT_HAVE_glob) && (!defined(__USE_FILE_OFFSET64) || defined(__GLOB32_MATCHES_GLOB64))
/* >> glob(3), glob64(3)
 * @param: flags: Set of `GLOB_ERR | GLOB_MARK  | GLOB_NOSORT | GLOB_DOOFFS  |
 *                GLOB_NOCHECK  | GLOB_APPEND |  GLOB_NOESCAPE | GLOB_PERIOD |
 *                GLOB_MAGCHAR | GLOB_ALTDIRFUNC | GLOB_BRACE | GLOB_NOMAGIC |
 *                GLOB_TILDE | GLOB_ONLYDIR | GLOB_TILDE_CHECK'
 * @return: GLOB_NOSPACE : ...
 * @return: GLOB_ABORTED : ...
 * @return: GLOB_NOMATCH : ...
 * @return: GLOB_NOSYS   : ... */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(4),int,__NOTHROW_NCX,glob,(char const *__restrict __pattern, __STDC_INT_AS_UINT_T __flags, int (__LIBKCALL *__errfunc)(char const *__path, int __flags), glob_t *__restrict __pglob),(__pattern,__flags,__errfunc,__pglob))
#elif defined(__CRT_HAVE_glob64) && (defined(__USE_FILE_OFFSET64) || defined(__GLOB32_MATCHES_GLOB64))
/* >> glob(3), glob64(3)
 * @param: flags: Set of `GLOB_ERR | GLOB_MARK  | GLOB_NOSORT | GLOB_DOOFFS  |
 *                GLOB_NOCHECK  | GLOB_APPEND |  GLOB_NOESCAPE | GLOB_PERIOD |
 *                GLOB_MAGCHAR | GLOB_ALTDIRFUNC | GLOB_BRACE | GLOB_NOMAGIC |
 *                GLOB_TILDE | GLOB_ONLYDIR | GLOB_TILDE_CHECK'
 * @return: GLOB_NOSPACE : ...
 * @return: GLOB_ABORTED : ...
 * @return: GLOB_NOMATCH : ...
 * @return: GLOB_NOSYS   : ... */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(4),int,__NOTHROW_NCX,glob,(char const *__restrict __pattern, __STDC_INT_AS_UINT_T __flags, int (__LIBKCALL *__errfunc)(char const *__path, int __flags), glob_t *__restrict __pglob),glob64,(__pattern,__flags,__errfunc,__pglob))
#else /* ... */
#include <libc/local/glob/glob.h>
/* >> glob(3), glob64(3)
 * @param: flags: Set of `GLOB_ERR | GLOB_MARK  | GLOB_NOSORT | GLOB_DOOFFS  |
 *                GLOB_NOCHECK  | GLOB_APPEND |  GLOB_NOESCAPE | GLOB_PERIOD |
 *                GLOB_MAGCHAR | GLOB_ALTDIRFUNC | GLOB_BRACE | GLOB_NOMAGIC |
 *                GLOB_TILDE | GLOB_ONLYDIR | GLOB_TILDE_CHECK'
 * @return: GLOB_NOSPACE : ...
 * @return: GLOB_ABORTED : ...
 * @return: GLOB_NOMATCH : ...
 * @return: GLOB_NOSYS   : ... */
__NAMESPACE_LOCAL_USING_OR_IMPL(glob, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(4) int __NOTHROW_NCX(__LIBCCALL glob)(char const *__restrict __pattern, __STDC_INT_AS_UINT_T __flags, int (__LIBKCALL *__errfunc)(char const *__path, int __flags), glob_t *__restrict __pglob) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(glob))(__pattern, __flags, __errfunc, __pglob); })
#endif /* !... */
#if defined(__CRT_HAVE_globfree) && (!defined(__USE_FILE_OFFSET64) || defined(__GLOB32_MATCHES_GLOB64))
/* >> globfree(3), globfree64(3) */
__CDECLARE_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,globfree,(glob_t *__pglob),(__pglob))
#elif defined(__CRT_HAVE_globfree64) && (defined(__USE_FILE_OFFSET64) || defined(__GLOB32_MATCHES_GLOB64))
/* >> globfree(3), globfree64(3) */
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,globfree,(glob_t *__pglob),globfree64,(__pglob))
#else /* ... */
#include <libc/local/glob/globfree.h>
/* >> globfree(3), globfree64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(globfree, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) void __NOTHROW_NCX(__LIBCCALL globfree)(glob_t *__pglob) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(globfree))(__pglob); })
#endif /* !... */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_glob) && defined(__GLOB32_MATCHES_GLOB64)
/* >> glob(3), glob64(3)
 * @param: flags: Set of `GLOB_ERR | GLOB_MARK  | GLOB_NOSORT | GLOB_DOOFFS  |
 *                GLOB_NOCHECK  | GLOB_APPEND |  GLOB_NOESCAPE | GLOB_PERIOD |
 *                GLOB_MAGCHAR | GLOB_ALTDIRFUNC | GLOB_BRACE | GLOB_NOMAGIC |
 *                GLOB_TILDE | GLOB_ONLYDIR | GLOB_TILDE_CHECK'
 * @return: GLOB_NOSPACE : ...
 * @return: GLOB_ABORTED : ...
 * @return: GLOB_NOMATCH : ...
 * @return: GLOB_NOSYS   : ... */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(4),int,__NOTHROW_NCX,glob64,(const char *__restrict __pattern, __STDC_INT_AS_UINT_T __flags, int (__LIBKCALL *__errfunc)(char const *__path, int __flags), struct __glob64_struct *__restrict __pglob),glob,(__pattern,__flags,__errfunc,__pglob))
#elif defined(__CRT_HAVE_glob64)
/* >> glob(3), glob64(3)
 * @param: flags: Set of `GLOB_ERR | GLOB_MARK  | GLOB_NOSORT | GLOB_DOOFFS  |
 *                GLOB_NOCHECK  | GLOB_APPEND |  GLOB_NOESCAPE | GLOB_PERIOD |
 *                GLOB_MAGCHAR | GLOB_ALTDIRFUNC | GLOB_BRACE | GLOB_NOMAGIC |
 *                GLOB_TILDE | GLOB_ONLYDIR | GLOB_TILDE_CHECK'
 * @return: GLOB_NOSPACE : ...
 * @return: GLOB_ABORTED : ...
 * @return: GLOB_NOMATCH : ...
 * @return: GLOB_NOSYS   : ... */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(4),int,__NOTHROW_NCX,glob64,(const char *__restrict __pattern, __STDC_INT_AS_UINT_T __flags, int (__LIBKCALL *__errfunc)(char const *__path, int __flags), struct __glob64_struct *__restrict __pglob),(__pattern,__flags,__errfunc,__pglob))
#else /* ... */
#include <libc/local/glob/glob64.h>
/* >> glob(3), glob64(3)
 * @param: flags: Set of `GLOB_ERR | GLOB_MARK  | GLOB_NOSORT | GLOB_DOOFFS  |
 *                GLOB_NOCHECK  | GLOB_APPEND |  GLOB_NOESCAPE | GLOB_PERIOD |
 *                GLOB_MAGCHAR | GLOB_ALTDIRFUNC | GLOB_BRACE | GLOB_NOMAGIC |
 *                GLOB_TILDE | GLOB_ONLYDIR | GLOB_TILDE_CHECK'
 * @return: GLOB_NOSPACE : ...
 * @return: GLOB_ABORTED : ...
 * @return: GLOB_NOMATCH : ...
 * @return: GLOB_NOSYS   : ... */
__NAMESPACE_LOCAL_USING_OR_IMPL(glob64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(4) int __NOTHROW_NCX(__LIBCCALL glob64)(const char *__restrict __pattern, __STDC_INT_AS_UINT_T __flags, int (__LIBKCALL *__errfunc)(char const *__path, int __flags), struct __glob64_struct *__restrict __pglob) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(glob64))(__pattern, __flags, __errfunc, __pglob); })
#endif /* !... */
#if defined(__CRT_HAVE_globfree) && defined(__GLOB32_MATCHES_GLOB64)
/* >> globfree(3), globfree64(3) */
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,globfree64,(struct __glob64_struct *__pglob),globfree,(__pglob))
#elif defined(__CRT_HAVE_globfree64)
/* >> globfree(3), globfree64(3) */
__CDECLARE_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,globfree64,(struct __glob64_struct *__pglob),(__pglob))
#else /* ... */
#include <libc/local/glob/globfree64.h>
/* >> globfree(3), globfree64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(globfree64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) void __NOTHROW_NCX(__LIBCCALL globfree64)(struct __glob64_struct *__pglob) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(globfree64))(__pglob); })
#endif /* !... */
#endif /* __USE_LARGEFILE64 */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_GLOB_H */
