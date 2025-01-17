/* HASH CRC-32:0xea7d59c1 */
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
/* (#) Portability: DragonFly BSD (/include/vis.h) */
/* (#) Portability: NetBSD        (/include/vis.h) */
/* (#) Portability: OpenBSD       (/include/vis.h) */
/* (#) Portability: libbsd        (/include/bsd/vis.h) */
#ifndef _VIS_H
#define _VIS_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <asm/crt/vis.h>
#include <hybrid/typecore.h>

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */

/* Flags for `vis(3)' */
#if !defined(VIS_OCTAL) && defined(__VIS_OCTAL)
#define VIS_OCTAL     __VIS_OCTAL     /* Always use octal encoding (e.g. "\123") */
#endif /* !VIS_OCTAL && __VIS_OCTAL */
#if !defined(VIS_CSTYLE) && defined(__VIS_CSTYLE)
#define VIS_CSTYLE    __VIS_CSTYLE    /* Enable support for c-style escape aliases (e.h. "\n" instead of "\012") */
#endif /* !VIS_CSTYLE && __VIS_CSTYLE */
#if !defined(VIS_SP) && defined(__VIS_SP)
#define VIS_SP        __VIS_SP        /* The character " " (space) needs to be \-escaped */
#endif /* !VIS_SP && __VIS_SP */
#if !defined(VIS_TAB) && defined(__VIS_TAB)
#define VIS_TAB       __VIS_TAB       /* The character "\t" (tab) needs to be \-escaped */
#endif /* !VIS_TAB && __VIS_TAB */
#if !defined(VIS_NL) && defined(__VIS_NL)
#define VIS_NL        __VIS_NL        /* The character "\n" (new-line) needs to be \-escaped */
#endif /* !VIS_NL && __VIS_NL */
#if !defined(VIS_SAFE) && defined(__VIS_SAFE)
#define VIS_SAFE      __VIS_SAFE      /* Character "\b", "\a" and "\r" don't need to be escaped */
#endif /* !VIS_SAFE && __VIS_SAFE */
#if !defined(VIS_NOSLASH) && defined(__VIS_NOSLASH)
#define VIS_NOSLASH   __VIS_NOSLASH   /* The character "\\" (backslash) doesn't need to be \-escaped */
#endif /* !VIS_NOSLASH && __VIS_NOSLASH */
#if !defined(VIS_HTTP1808) && defined(__VIS_HTTPSTYLE)
#define VIS_HTTP1808  __VIS_HTTPSTYLE /* Enable support for '%AB'-escape sequences */
#endif /* !VIS_HTTP1808 && __VIS_HTTPSTYLE */
#if !defined(VIS_HTTPSTYLE) && defined(__VIS_HTTPSTYLE)
#define VIS_HTTPSTYLE __VIS_HTTPSTYLE /* Enable support for '%AB'-escape sequences */
#endif /* !VIS_HTTPSTYLE && __VIS_HTTPSTYLE */
#if !defined(VIS_MIMESTYLE) && defined(__VIS_MIMESTYLE)
#define VIS_MIMESTYLE __VIS_MIMESTYLE /* Enable support for '=AB'-escape sequences */
#endif /* !VIS_MIMESTYLE && __VIS_MIMESTYLE */
#if !defined(VIS_HTTP1866) && defined(__VIS_HTTP1866)
#define VIS_HTTP1866  __VIS_HTTP1866  /* Enable support for '&amp;'-escape sequences */
#endif /* !VIS_HTTP1866 && __VIS_HTTP1866 */
#if !defined(VIS_NOESCAPE) && defined(__VIS_NOESCAPE)
#define VIS_NOESCAPE  __VIS_NOESCAPE  /* Disable support for '\'-escape sequences */
#endif /* !VIS_NOESCAPE && __VIS_NOESCAPE */
#if !defined(_VIS_END) && defined(__VIS_END)
#define _VIS_END      __VIS_END       /* s.a. `UNVIS_END' */
#endif /* !_VIS_END && __VIS_END */
#if !defined(VIS_GLOB) && defined(__VIS_GLOB)
#define VIS_GLOB      __VIS_GLOB      /* Characters >>>*?[#<<<                need to be \-escaped */
#endif /* !VIS_GLOB && __VIS_GLOB */
#if !defined(VIS_SHELL) && defined(__VIS_SHELL)
#define VIS_SHELL     __VIS_SHELL     /* Characters >>>'`";&<>()|{}]\\$!^~<<< need to be \-escaped */
#endif /* !VIS_SHELL && __VIS_SHELL */
#if !defined(VIS_NOLOCALE) && defined(__VIS_NOLOCALE)
#define VIS_NOLOCALE  __VIS_NOLOCALE  /* ??? */
#endif /* !VIS_NOLOCALE && __VIS_NOLOCALE */
#if !defined(VIS_DQ) && defined(__VIS_DQ)
#define VIS_DQ        __VIS_DQ        /* The character '"' (double-quote) needs to be \-escaped */
#endif /* !VIS_DQ && __VIS_DQ */
#if !defined(VIS_WHITE) && defined(__VIS_WHITE)
#define VIS_WHITE     __VIS_WHITE     /* Alias for `VIS_SP | VIS_TAB | VIS_NL' */
#endif /* !VIS_WHITE && __VIS_WHITE */
#if !defined(VIS_META) && defined(__VIS_META)
#define VIS_META      __VIS_META      /* Alias for `VIS_WHITE | VIS_GLOB | VIS_SHELL' */
#endif /* !VIS_META && __VIS_META */



/* Return values for `unvis(3)' */
#if !defined(UNVIS_ERROR) && defined(__UNVIS_ERROR)
#define UNVIS_ERROR     __UNVIS_ERROR     /* /unused/ */
#endif /* !UNVIS_ERROR && __UNVIS_ERROR */
#if !defined(UNVIS_SYNBAD) && defined(__UNVIS_SYNBAD)
#define UNVIS_SYNBAD    __UNVIS_SYNBAD    /* Syntax error */
#endif /* !UNVIS_SYNBAD && __UNVIS_SYNBAD */
#if !defined(UNVIS_VALID) && defined(__UNVIS_VALID)
#define UNVIS_VALID     __UNVIS_VALID     /* Output byte produced; consume input byte */
#endif /* !UNVIS_VALID && __UNVIS_VALID */
#if !defined(UNVIS_VALIDPUSH) && defined(__UNVIS_VALIDPUSH)
#define UNVIS_VALIDPUSH __UNVIS_VALIDPUSH /* Output byte produced */
#endif /* !UNVIS_VALIDPUSH && __UNVIS_VALIDPUSH */
#if !defined(UNVIS_NOCHAR) && defined(__UNVIS_NOCHAR)
#define UNVIS_NOCHAR    __UNVIS_NOCHAR    /* Consume input byte */
#endif /* !UNVIS_NOCHAR && __UNVIS_NOCHAR */

/* Extra flags for `unvis(3)' */
#if !defined(UNVIS_END) && defined(__UNVIS_END)
#define UNVIS_END __UNVIS_END /* Special marker for `unvis()' flush and pending character. */
#endif /* !UNVIS_END && __UNVIS_END */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */


/* Figure out which parameter-order the caller wants for `strnvis(3)' and `strnunvis(3)' */
#if defined(LIBBSD_OPENBSD_VIS)
#undef LIBBSD_NETBSD_VIS
#elif defined(LIBBSD_NETBSD_VIS)
/*#undef LIBBSD_OPENBSD_VIS*/
#elif defined(__CRT_NETBSD)
#define LIBBSD_NETBSD_VIS
#elif defined(__CRT_OPENBSD)
#define LIBBSD_OPENBSD_VIS
#elif defined(__NetBSD__) || defined(__MacOS__) || defined(__OSX__)
#define LIBBSD_NETBSD_VIS
#elif defined(__KOS__)
#define LIBBSD_NETBSD_VIS /* I personally like NetBSD's argument-order more, so make it the default on KOS */
#elif defined(__OpenBSD__) || defined(__solaris__)
#define LIBBSD_OPENBSD_VIS
#else /* ... */
#define LIBBSD_NETBSD_VIS /*  */
/*[[[warning(warn("
	Unable to determine which parameter-order to use for `strnvis(3)' and `strnunvis(3)'
	Please define one of `LIBBSD_NETBSD_VIS' or `LIBBSD_OPENBSD_VIS' (now proceeding as
	though `LIBBSD_NETBSD_VIS' had been defined)
"))]]]*/
#ifndef __NO_WARNINGS
#ifdef __PREPROCESSOR_HAVE_WARNING
#warning "\
Unable to determine which parameter-order to use for `strnvis(3)' and `strnunvis(3)' \
Please define one of `LIBBSD_NETBSD_VIS' or `LIBBSD_OPENBSD_VIS' (now proceeding as \
though `LIBBSD_NETBSD_VIS' had been defined)"
#elif defined(__PREPROCESSOR_HAVE_PRAGMA_WARNING)
#pragma warning("\
Unable to determine which parameter-order to use for `strnvis(3)' and `strnunvis(3)' \
Please define one of `LIBBSD_NETBSD_VIS' or `LIBBSD_OPENBSD_VIS' (now proceeding as \
though `LIBBSD_NETBSD_VIS' had been defined)")
#endif /* ... */
#endif /* !__NO_WARNINGS */
/*[[[end]]]*/
#endif /* !... */


#ifdef __CRT_HAVE_vis
__CDECLARE(__ATTR_NONNULL((1)),char *,__NOTHROW_NCX,vis,(char *__dst, int __c, int __flags, int __nextc),(__dst,__c,__flags,__nextc))
#else /* __CRT_HAVE_vis */
#include <libc/local/vis/vis.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vis, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL vis)(char *__dst, int __c, int __flags, int __nextc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vis))(__dst, __c, __flags, __nextc); })
#endif /* !__CRT_HAVE_vis */
#ifdef __CRT_HAVE_nvis
__CDECLARE(__ATTR_OUTS(1, 2),char *,__NOTHROW_NCX,nvis,(char *__dst, size_t __dstsize, int __c, int __flags, int __nextc),(__dst,__dstsize,__c,__flags,__nextc))
#else /* __CRT_HAVE_nvis */
#include <libc/local/vis/nvis.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(nvis, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(1, 2) char *__NOTHROW_NCX(__LIBCCALL nvis)(char *__dst, size_t __dstsize, int __c, int __flags, int __nextc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nvis))(__dst, __dstsize, __c, __flags, __nextc); })
#endif /* !__CRT_HAVE_nvis */
#ifdef __CRT_HAVE_svis
__CDECLARE(__ATTR_IN(5) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,svis,(char *__dst, int __c, int __flags, int __nextc, char const *__mbextra),(__dst,__c,__flags,__nextc,__mbextra))
#else /* __CRT_HAVE_svis */
#include <libc/local/vis/svis.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(svis, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(5) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL svis)(char *__dst, int __c, int __flags, int __nextc, char const *__mbextra) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(svis))(__dst, __c, __flags, __nextc, __mbextra); })
#endif /* !__CRT_HAVE_svis */
#ifdef __CRT_HAVE_snvis
__CDECLARE(__ATTR_IN(6) __ATTR_OUTS(1, 2),char *,__NOTHROW_NCX,snvis,(char *__dst, size_t __dstsize, int __c, int __flags, int __nextc, char const *__mbextra),(__dst,__dstsize,__c,__flags,__nextc,__mbextra))
#else /* __CRT_HAVE_snvis */
#include <libc/local/vis/snvis.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(snvis, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(6) __ATTR_OUTS(1, 2) char *__NOTHROW_NCX(__LIBCCALL snvis)(char *__dst, size_t __dstsize, int __c, int __flags, int __nextc, char const *__mbextra) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(snvis))(__dst, __dstsize, __c, __flags, __nextc, __mbextra); })
#endif /* !__CRT_HAVE_snvis */
#ifdef __CRT_HAVE_strvis
__CDECLARE(__ATTR_IN(2) __ATTR_NONNULL((1)),int,__NOTHROW_NCX,strvis,(char *__dst, char const *__src, int __flags),(__dst,__src,__flags))
#else /* __CRT_HAVE_strvis */
#include <libc/local/vis/strvis.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strvis, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL strvis)(char *__dst, char const *__src, int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strvis))(__dst, __src, __flags); })
#endif /* !__CRT_HAVE_strvis */
#ifdef __CRT_HAVE_stravis
__CDECLARE(__ATTR_IN_OPT(2) __ATTR_OUT(1),int,__NOTHROW_NCX,stravis,(char **__p_resstr, char const *__src, int __flags),(__p_resstr,__src,__flags))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/vis/stravis.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(stravis, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(2) __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL stravis)(char **__p_resstr, char const *__src, int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stravis))(__p_resstr, __src, __flags); })
#endif /* ... */
#ifdef LIBBSD_NETBSD_VIS
#if defined(__CRT_HAVE_strnvis) && defined(__CRT_NETBSD)
__CDECLARE(__ATTR_OUTS(1, 2),int,__NOTHROW_NCX,strnvis,(char *__dst, size_t __dstsize, char const *__src, int __flags),(__dst,__dstsize,__src,__flags))
#elif defined(__CRT_HAVE_strnvis_netbsd)
__CREDIRECT(__ATTR_OUTS(1, 2),int,__NOTHROW_NCX,strnvis,(char *__dst, size_t __dstsize, char const *__src, int __flags),strnvis_netbsd,(__dst,__dstsize,__src,__flags))
#else /* ... */
#include <libc/local/vis/strnvis_netbsd.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(1, 2) int __NOTHROW_NCX(__LIBCCALL strnvis)(char *__dst, size_t __dstsize, char const *__src, int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnvis_netbsd))(__dst, __dstsize, __src, __flags); }
#endif /* !... */
#else /* LIBBSD_NETBSD_VIS */
#if defined(__CRT_HAVE_strnvis) && !defined(__CRT_NETBSD)
__CDECLARE(__ATTR_OUTS(1, 3),int,__NOTHROW_NCX,strnvis,(char *__dst, char const *__src, size_t __dstsize, int __flags),(__dst,__src,__dstsize,__flags))
#else /* __CRT_HAVE_strnvis && !__CRT_NETBSD */
#include <libc/local/vis/strnvis.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnvis, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(1, 3) int __NOTHROW_NCX(__LIBCCALL strnvis)(char *__dst, char const *__src, size_t __dstsize, int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnvis))(__dst, __src, __dstsize, __flags); })
#endif /* !__CRT_HAVE_strnvis || __CRT_NETBSD */
#endif /* !LIBBSD_NETBSD_VIS */
#ifdef __CRT_HAVE_strsvis
__CDECLARE(__ATTR_IN(4) __ATTR_IN_OPT(2) __ATTR_NONNULL((1)),int,__NOTHROW_NCX,strsvis,(char *__dst, char const *__src, int __flags, char const *__mbextra),(__dst,__src,__flags,__mbextra))
#else /* __CRT_HAVE_strsvis */
#include <libc/local/vis/strsvis.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strsvis, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(4) __ATTR_IN_OPT(2) __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL strsvis)(char *__dst, char const *__src, int __flags, char const *__mbextra) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strsvis))(__dst, __src, __flags, __mbextra); })
#endif /* !__CRT_HAVE_strsvis */
#ifdef __CRT_HAVE_strsnvis
__CDECLARE(__ATTR_IN(5) __ATTR_IN_OPT(3) __ATTR_OUTS(1, 2),int,__NOTHROW_NCX,strsnvis,(char *__dst, size_t __dstsize, char const *__src, int __flags, char const *__mbextra),(__dst,__dstsize,__src,__flags,__mbextra))
#else /* __CRT_HAVE_strsnvis */
#include <libc/local/vis/strsnvis.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strsnvis, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(5) __ATTR_IN_OPT(3) __ATTR_OUTS(1, 2) int __NOTHROW_NCX(__LIBCCALL strsnvis)(char *__dst, size_t __dstsize, char const *__src, int __flags, char const *__mbextra) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strsnvis))(__dst, __dstsize, __src, __flags, __mbextra); })
#endif /* !__CRT_HAVE_strsnvis */
#ifdef __CRT_HAVE_strvisx
__CDECLARE(__ATTR_INS(2, 3) __ATTR_NONNULL((1)),int,__NOTHROW_NCX,strvisx,(char *__dst, char const *__src, size_t __srclen, int __flags),(__dst,__src,__srclen,__flags))
#else /* __CRT_HAVE_strvisx */
#include <libc/local/vis/strvisx.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strvisx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL strvisx)(char *__dst, char const *__src, size_t __srclen, int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strvisx))(__dst, __src, __srclen, __flags); })
#endif /* !__CRT_HAVE_strvisx */
#ifdef __CRT_HAVE_strnvisx
__CDECLARE(__ATTR_INS(3, 4) __ATTR_OUTS(1, 2),int,__NOTHROW_NCX,strnvisx,(char *__dst, size_t __dstsize, char const *__src, size_t __srclen, int __flags),(__dst,__dstsize,__src,__srclen,__flags))
#else /* __CRT_HAVE_strnvisx */
#include <libc/local/vis/strnvisx.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnvisx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) int __NOTHROW_NCX(__LIBCCALL strnvisx)(char *__dst, size_t __dstsize, char const *__src, size_t __srclen, int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnvisx))(__dst, __dstsize, __src, __srclen, __flags); })
#endif /* !__CRT_HAVE_strnvisx */
#ifdef __CRT_HAVE_strenvisx
__CDECLARE(__ATTR_INS(3, 4) __ATTR_OUTS(1, 2) __ATTR_OUT_OPT(6),int,__NOTHROW_NCX,strenvisx,(char *__dst, size_t __dstsize, char const *__src, size_t __srclen, int __flags, int *__cerr_ptr),(__dst,__dstsize,__src,__srclen,__flags,__cerr_ptr))
#else /* __CRT_HAVE_strenvisx */
#include <libc/local/vis/strenvisx.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strenvisx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) __ATTR_OUT_OPT(6) int __NOTHROW_NCX(__LIBCCALL strenvisx)(char *__dst, size_t __dstsize, char const *__src, size_t __srclen, int __flags, int *__cerr_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strenvisx))(__dst, __dstsize, __src, __srclen, __flags, __cerr_ptr); })
#endif /* !__CRT_HAVE_strenvisx */
#ifdef __CRT_HAVE_strsvisx
__CDECLARE(__ATTR_IN(5) __ATTR_NONNULL((1)),int,__NOTHROW_NCX,strsvisx,(char *__dst, char const *__src, size_t __srclen, int __flags, char const *__mbextra),(__dst,__src,__srclen,__flags,__mbextra))
#else /* __CRT_HAVE_strsvisx */
#include <libc/local/vis/strsvisx.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strsvisx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(5) __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL strsvisx)(char *__dst, char const *__src, size_t __srclen, int __flags, char const *__mbextra) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strsvisx))(__dst, __src, __srclen, __flags, __mbextra); })
#endif /* !__CRT_HAVE_strsvisx */
#ifdef __CRT_HAVE_strsnvisx
__CDECLARE(__ATTR_IN(6) __ATTR_INS(3, 4) __ATTR_OUTS(1, 2),int,__NOTHROW_NCX,strsnvisx,(char *__dst, size_t __dstsize, char const *__src, size_t __srclen, int __flags, char const *__mbextra),(__dst,__dstsize,__src,__srclen,__flags,__mbextra))
#else /* __CRT_HAVE_strsnvisx */
#include <libc/local/vis/strsnvisx.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strsnvisx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(6) __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) int __NOTHROW_NCX(__LIBCCALL strsnvisx)(char *__dst, size_t __dstsize, char const *__src, size_t __srclen, int __flags, char const *__mbextra) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strsnvisx))(__dst, __dstsize, __src, __srclen, __flags, __mbextra); })
#endif /* !__CRT_HAVE_strsnvisx */
#ifdef __CRT_HAVE_strsenvisx
__CDECLARE(__ATTR_IN(6) __ATTR_INS(3, 4) __ATTR_OUTS(1, 2),int,__NOTHROW_NCX,strsenvisx,(char *__dst, size_t __dstsize, char const *__src, size_t __srclen, int __flags, char const *__mbextra, int *__cerr_ptr),(__dst,__dstsize,__src,__srclen,__flags,__mbextra,__cerr_ptr))
#else /* __CRT_HAVE_strsenvisx */
#include <libc/local/vis/strsenvisx.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strsenvisx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(6) __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) int __NOTHROW_NCX(__LIBCCALL strsenvisx)(char *__dst, size_t __dstsize, char const *__src, size_t __srclen, int __flags, char const *__mbextra, int *__cerr_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strsenvisx))(__dst, __dstsize, __src, __srclen, __flags, __mbextra, __cerr_ptr); })
#endif /* !__CRT_HAVE_strsenvisx */
#ifdef __CRT_HAVE_strunvis
__CDECLARE(__ATTR_IN(2) __ATTR_NONNULL((1)),int,__NOTHROW_NCX,strunvis,(char *__dst, char const *__src),(__dst,__src))
#else /* __CRT_HAVE_strunvis */
#include <libc/local/vis/strunvis.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strunvis, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL strunvis)(char *__dst, char const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strunvis))(__dst, __src); })
#endif /* !__CRT_HAVE_strunvis */
#ifdef LIBBSD_NETBSD_VIS
#if defined(__CRT_HAVE_strnunvis) && defined(__CRT_NETBSD)
__CDECLARE(__ATTR_IN(3) __ATTR_OUTS(1, 2),int,__NOTHROW_NCX,strnunvis,(char *__dst, size_t __dstsize, char const *__src),(__dst,__dstsize,__src))
#elif defined(__CRT_HAVE_strnunvis_netbsd)
__CREDIRECT(__ATTR_IN(3) __ATTR_OUTS(1, 2),int,__NOTHROW_NCX,strnunvis,(char *__dst, size_t __dstsize, char const *__src),strnunvis_netbsd,(__dst,__dstsize,__src))
#else /* ... */
#include <libc/local/vis/strnunvis_netbsd.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_OUTS(1, 2) int __NOTHROW_NCX(__LIBCCALL strnunvis)(char *__dst, size_t __dstsize, char const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnunvis_netbsd))(__dst, __dstsize, __src); }
#endif /* !... */
#else /* LIBBSD_NETBSD_VIS */
#if defined(__CRT_HAVE_strnunvis) && !defined(__CRT_NETBSD)
__CDECLARE(__ATTR_IN(2) __ATTR_OUTS(1, 3),int,__NOTHROW_NCX,strnunvis,(char *__dst, char const *__src, size_t __dstsize),(__dst,__src,__dstsize))
#else /* __CRT_HAVE_strnunvis && !__CRT_NETBSD */
#include <libc/local/vis/strnunvis.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnunvis, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUTS(1, 3) int __NOTHROW_NCX(__LIBCCALL strnunvis)(char *__dst, char const *__src, size_t __dstsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnunvis))(__dst, __src, __dstsize); })
#endif /* !__CRT_HAVE_strnunvis || __CRT_NETBSD */
#endif /* !LIBBSD_NETBSD_VIS */
#ifdef __CRT_HAVE_strunvisx
__CDECLARE(__ATTR_IN(2) __ATTR_NONNULL((1)),int,__NOTHROW_NCX,strunvisx,(char *__dst, char const *__src, int __flags),(__dst,__src,__flags))
#else /* __CRT_HAVE_strunvisx */
#include <libc/local/vis/strunvisx.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strunvisx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL strunvisx)(char *__dst, char const *__src, int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strunvisx))(__dst, __src, __flags); })
#endif /* !__CRT_HAVE_strunvisx */
#ifdef __CRT_HAVE_strnunvisx
__CDECLARE(__ATTR_IN(3) __ATTR_OUTS(1, 2),int,__NOTHROW_NCX,strnunvisx,(char *__dst, size_t __dstsize, char const *__src, int __flags),(__dst,__dstsize,__src,__flags))
#else /* __CRT_HAVE_strnunvisx */
#include <libc/local/vis/strnunvisx.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnunvisx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_OUTS(1, 2) int __NOTHROW_NCX(__LIBCCALL strnunvisx)(char *__dst, size_t __dstsize, char const *__src, int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnunvisx))(__dst, __dstsize, __src, __flags); })
#endif /* !__CRT_HAVE_strnunvisx */
#ifdef __CRT_HAVE_unvis
/* >> unvis(3)
 * WARNING: When returning `UNVIS_NOCHAR', `*p_outbyte' may be part of the internal state  and
 *          has to be copied alongside `*p_state' if you wish to state (and later restore) the
 *          state of this function!
 * @param: flags: Set of `VIS_HTTP1808 | VIS_MIMESTYLE | VIS_HTTP1866 | VIS_NOESCAPE | UNVIS_END'
 * @return: UNVIS_SYNBAD:    [...]
 * @return: UNVIS_VALID:     [...]
 * @return: UNVIS_VALIDPUSH: [...]
 * @return: UNVIS_NOCHAR:    [...] */
__CDECLARE(__ATTR_INOUT(3) __ATTR_NONNULL((1)),int,__NOTHROW_NCX,unvis,(char *__p_outbyte, int __inbyte, int *__p_state, int __flags),(__p_outbyte,__inbyte,__p_state,__flags))
#else /* __CRT_HAVE_unvis */
#include <libc/local/vis/unvis.h>
/* >> unvis(3)
 * WARNING: When returning `UNVIS_NOCHAR', `*p_outbyte' may be part of the internal state  and
 *          has to be copied alongside `*p_state' if you wish to state (and later restore) the
 *          state of this function!
 * @param: flags: Set of `VIS_HTTP1808 | VIS_MIMESTYLE | VIS_HTTP1866 | VIS_NOESCAPE | UNVIS_END'
 * @return: UNVIS_SYNBAD:    [...]
 * @return: UNVIS_VALID:     [...]
 * @return: UNVIS_VALIDPUSH: [...]
 * @return: UNVIS_NOCHAR:    [...] */
__NAMESPACE_LOCAL_USING_OR_IMPL(unvis, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(3) __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL unvis)(char *__p_outbyte, int __inbyte, int *__p_state, int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unvis))(__p_outbyte, __inbyte, __p_state, __flags); })
#endif /* !__CRT_HAVE_unvis */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_VIS_H */
