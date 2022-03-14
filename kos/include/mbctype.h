/* HASH CRC-32:0x6b289969 */
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
/* (#) Portability: MinGW        (/mingw-w64-headers/crt/mbctype.h) */
/* (#) Portability: Windows Kits (/ucrt/mbctype.h) */
#ifndef _MBCTYPE_H
#define _MBCTYPE_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <hybrid/typecore.h>
#include <bits/crt/ctype.h>

#ifdef __USE_DOS
#include <crtdefs.h>
#endif /* __USE_DOS */



/* Bits for `_mbctype' */
#define _MS    0x01 /* _ismbbkalnum: ... */
#define _MP    0x02 /* _ismbbkpunct: ... */
#define _M1    0x04 /* _ismbblead: First byte */
#define _M2    0x08 /* _ismbbtrail: Second byte */
#define _SBUP  0x10 /* _ismbcupper (for characters <= 0xff) */
#define _SBLOW 0x20 /* _ismbclower (for characters <= 0xff) */
/*efine        0x40  * ... */
/*efine        0x80  * ... */


/* Values used by `_mbbtype_l(3)' and `_mbsbtype_l(3)' */
#define _MBC_SINGLE  0    /* Single-character byte (~ala `_MS') */
#define _MBC_LEAD    1    /* Lead byte (~ala `_ismbblead(3)') */
#define _MBC_TRAIL   2    /* Trail byte (~ala `_ismbbtrail(3)') */
#define _MBC_ILLEGAL (-1) /* Illegal character. */


/* Values for `_getmbcp(3)' / `_setmbcp(3)' */
#define _MB_CP_LOCALE (-4)
#define _MB_CP_ANSI   (-3)
#define _MB_CP_OEM    (-2)
#define _MB_CP_SBCS   0
#define _KANJI_CP     932
#define _MB_CP_UTF8   65001


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef _mbctype
#ifdef __LOCAL__mbctype
#define _mbctype __LOCAL__mbctype
#elif defined(__CRT_HAVE__mbctype)
extern unsigned char _mbctype[];
#define _mbctype _mbctype
#else /* ... */
#if !defined(____p__mbctype_defined) && defined(__CRT_HAVE___p__mbctype)
#define ____p__mbctype_defined
__CDECLARE(,unsigned char *,__NOTHROW_NCX,__p__mbctype,(void),())
#endif /* !____p__mbctype_defined && __CRT_HAVE___p__mbctype */
#ifdef __CRT_HAVE___p__mbctype
#define _mbctype __p__mbctype()
#endif /* __CRT_HAVE___p__mbctype */
#endif /* !... */
#endif /* !_mbctype */
#ifndef _mbcasemap
#ifdef __LOCAL__mbcasemap
#define _mbcasemap __LOCAL__mbcasemap
#elif defined(__CRT_HAVE__mbcasemap)
extern unsigned char _mbcasemap[];
#define _mbcasemap _mbcasemap
#else /* ... */
__CDECLARE_OPT(,unsigned char *,__NOTHROW_NCX,__p__mbcasemap,(void),())
#ifdef __CRT_HAVE___p__mbcasemap
#define _mbcasemap __p__mbcasemap()
#endif /* __CRT_HAVE___p__mbcasemap */
#endif /* !... */
#endif /* !_mbcasemap */
__CDECLARE_OPT(,int,__NOTHROW_NCX,_setmbcp,(int __cp),(__cp))
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_getmbcp,(void),())


/* KOS extension: convert a multi-byte character to/from unicode (UTF-32) */
#ifdef __USE_KOS
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED,__CHAR32_TYPE__,__NOTHROW_NCX,_mbctouni_l,(unsigned int __ch, __locale_t __locale),(__ch,__locale))
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED,unsigned int,__NOTHROW_NCX,_unitombc_l,(__CHAR32_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#endif /* __USE_KOS */
#ifdef __CRT_HAVE__ismbbkalnum
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbkalnum,(unsigned int __ch),(__ch))
#elif defined(__CRT_HAVE__ismbbkalnum_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbkalnum.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbkalnum, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbkalnum)(unsigned int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbkalnum))(__ch); })
#endif /* ... */
#ifdef __CRT_HAVE__ismbbkana
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbkana,(unsigned int __ch),(__ch))
#elif defined(__CRT_HAVE__ismbbkprint)
/* @param: ch: Should actually be `unsigned char ch' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbkana,(unsigned int __ch),_ismbbkprint,(__ch))
#elif defined(__CRT_HAVE__ismbbkana_l) || defined(__CRT_HAVE__ismbbkprint_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbkana.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbkana, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbkana)(unsigned int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbkana))(__ch); })
#endif /* ... */
#ifdef __CRT_HAVE__ismbbkpunct
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbkpunct,(unsigned int __ch),(__ch))
#elif defined(__CRT_HAVE__ismbbkpunct_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbkpunct.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbkpunct, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbkpunct)(unsigned int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbkpunct))(__ch); })
#endif /* ... */
#ifdef __CRT_HAVE__ismbbkana
/* @param: ch: Should actually be `unsigned char ch' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbkprint,(unsigned int __ch),_ismbbkana,(__ch))
#elif defined(__CRT_HAVE__ismbbkprint)
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbkprint,(unsigned int __ch),(__ch))
#elif defined(__CRT_HAVE__ismbbkana_l) || defined(__CRT_HAVE__ismbbkprint_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbkana.h>
/* @param: ch: Should actually be `unsigned char ch' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbkprint)(unsigned int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbkana))(__ch); }
#endif /* ... */
#ifdef __CRT_HAVE__ismbbalpha
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbalpha,(unsigned int __ch),(__ch))
#elif defined(__CRT_HAVE__ismbbalpha_l) || defined(__CRT_HAVE__ismbbkalnum_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbalpha.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbalpha, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbalpha)(unsigned int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbalpha))(__ch); })
#endif /* ... */
#ifdef __CRT_HAVE__ismbbpunct
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbpunct,(unsigned int __ch),(__ch))
#elif defined(__CRT_HAVE__ismbbpunct_l) || defined(__CRT_HAVE__ismbbkpunct_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbpunct.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbpunct, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbpunct)(unsigned int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbpunct))(__ch); })
#endif /* ... */
#ifdef __CRT_HAVE__ismbbblank
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbblank,(unsigned int __ch),(__ch))
#else /* __CRT_HAVE__ismbbblank */
#include <libc/local/mbctype/_ismbbblank.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbblank, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbblank)(unsigned int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbblank))(__ch); })
#endif /* !__CRT_HAVE__ismbbblank */
#ifdef __CRT_HAVE__ismbbalnum
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbalnum,(unsigned int __ch),(__ch))
#elif defined(__CRT_HAVE__ismbbalnum_l) || defined(__CRT_HAVE__ismbbkalnum_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbalnum.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbalnum, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbalnum)(unsigned int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbalnum))(__ch); })
#endif /* ... */
#ifdef __CRT_HAVE__ismbbprint
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbprint,(unsigned int __ch),(__ch))
#elif defined(__CRT_HAVE__ismbbprint_l) || defined(__CRT_HAVE__ismbbkana_l) || defined(__CRT_HAVE__ismbbkprint_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbprint.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbprint, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbprint)(unsigned int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbprint))(__ch); })
#endif /* ... */
#ifdef __CRT_HAVE__ismbbgraph
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbgraph,(unsigned int __ch),(__ch))
#elif defined(__CRT_HAVE__ismbbgraph_l) || defined(__CRT_HAVE__ismbbkana_l) || defined(__CRT_HAVE__ismbbkprint_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbgraph.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbgraph, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbgraph)(unsigned int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbgraph))(__ch); })
#endif /* ... */
#ifndef ___ismbblead_defined
#define ___ismbblead_defined
#ifdef __CRT_HAVE__ismbblead
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbblead,(unsigned int __ch),(__ch))
#elif defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbblead.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbblead, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbblead)(unsigned int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbblead))(__ch); })
#else /* ... */
#undef ___ismbblead_defined
#endif /* !... */
#endif /* !___ismbblead_defined */
#ifndef ___ismbbtrail_defined
#define ___ismbbtrail_defined
#ifdef __CRT_HAVE__ismbbtrail
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbtrail,(unsigned int __ch),(__ch))
#elif defined(__CRT_HAVE__ismbbtrail_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbtrail.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbtrail, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbtrail)(unsigned int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbtrail))(__ch); })
#else /* ... */
#undef ___ismbbtrail_defined
#endif /* !... */
#endif /* !___ismbbtrail_defined */
#ifndef ___ismbslead_defined
#define ___ismbslead_defined
#ifdef __CRT_HAVE__ismbslead
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_ismbslead,(unsigned char const *__str, unsigned char const *__pos),(__str,__pos))
#elif defined(__CRT_HAVE__ismbslead_l) || defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbstring/_ismbslead.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbslead, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _ismbslead)(unsigned char const *__str, unsigned char const *__pos) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbslead))(__str, __pos); })
#else /* ... */
#undef ___ismbslead_defined
#endif /* !... */
#endif /* !___ismbslead_defined */
#ifndef ___ismbstrail_defined
#define ___ismbstrail_defined
#ifdef __CRT_HAVE__ismbstrail
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_ismbstrail,(unsigned char const *__str, unsigned char const *__pos),(__str,__pos))
#elif defined(__CRT_HAVE__ismbstrail_l) || defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbstring/_ismbstrail.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbstrail, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _ismbstrail)(unsigned char const *__str, unsigned char const *__pos) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbstrail))(__str, __pos); })
#else /* ... */
#undef ___ismbstrail_defined
#endif /* !... */
#endif /* !___ismbstrail_defined */
#ifndef ___ismbblead_l_defined
#define ___ismbblead_l_defined
#ifdef __CRT_HAVE__ismbblead_l
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbblead_l,(unsigned int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbblead_l.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbblead_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbblead_l)(unsigned int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbblead_l))(__ch, __locale); })
#else /* ... */
#undef ___ismbblead_l_defined
#endif /* !... */
#endif /* !___ismbblead_l_defined */
#ifndef ___ismbbtrail_l_defined
#define ___ismbbtrail_l_defined
#ifdef __CRT_HAVE__ismbbtrail_l
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbtrail_l,(unsigned int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbtrail_l.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbtrail_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbtrail_l)(unsigned int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbtrail_l))(__ch, __locale); })
#else /* ... */
#undef ___ismbbtrail_l_defined
#endif /* !... */
#endif /* !___ismbbtrail_l_defined */
#ifdef __CRT_HAVE__ismbbkalnum_l
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbkalnum_l,(unsigned int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbkalnum_l.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbkalnum_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbkalnum_l)(unsigned int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbkalnum_l))(__ch, __locale); })
#endif /* ... */
#ifdef __CRT_HAVE__ismbbkana_l
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbkana_l,(unsigned int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__ismbbkprint_l)
/* @param: ch: Should actually be `unsigned char ch' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbkana_l,(unsigned int __ch, __locale_t __locale),_ismbbkprint_l,(__ch,__locale))
#elif defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbkana_l.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbkana_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbkana_l)(unsigned int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbkana_l))(__ch, __locale); })
#endif /* ... */
#ifdef __CRT_HAVE__ismbbkpunct_l
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbkpunct_l,(unsigned int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbkpunct_l.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbkpunct_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbkpunct_l)(unsigned int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbkpunct_l))(__ch, __locale); })
#endif /* ... */
#ifdef __CRT_HAVE__ismbbkana_l
/* @param: ch: Should actually be `unsigned char ch' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbkprint_l,(unsigned int __ch, __locale_t __locale),_ismbbkana_l,(__ch,__locale))
#elif defined(__CRT_HAVE__ismbbkprint_l)
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbkprint_l,(unsigned int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbkana_l.h>
/* @param: ch: Should actually be `unsigned char ch' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbkprint_l)(unsigned int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbkana_l))(__ch, __locale); }
#endif /* ... */
#ifdef __CRT_HAVE__ismbbalpha_l
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbalpha_l,(unsigned int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__ismbbkalnum_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbalpha_l.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbalpha_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbalpha_l)(unsigned int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbalpha_l))(__ch, __locale); })
#endif /* ... */
#ifdef __CRT_HAVE__ismbbpunct_l
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbpunct_l,(unsigned int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__ismbbkpunct_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbpunct_l.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbpunct_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbpunct_l)(unsigned int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbpunct_l))(__ch, __locale); })
#endif /* ... */
#ifdef __CRT_HAVE__ismbbblank_l
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbblank_l,(unsigned int __ch, __locale_t __locale),(__ch,__locale))
#else /* __CRT_HAVE__ismbbblank_l */
#include <libc/local/mbctype/_ismbbblank_l.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbblank_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbblank_l)(unsigned int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbblank_l))(__ch, __locale); })
#endif /* !__CRT_HAVE__ismbbblank_l */
#ifdef __CRT_HAVE__ismbbalnum_l
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbalnum_l,(unsigned int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__ismbbkalnum_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbalnum_l.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbalnum_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbalnum_l)(unsigned int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbalnum_l))(__ch, __locale); })
#endif /* ... */
#ifdef __CRT_HAVE__ismbbprint_l
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbprint_l,(unsigned int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__ismbbkana_l) || defined(__CRT_HAVE__ismbbkprint_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbprint_l.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbprint_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbprint_l)(unsigned int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbprint_l))(__ch, __locale); })
#endif /* ... */
#ifdef __CRT_HAVE__ismbbgraph_l
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbgraph_l,(unsigned int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__ismbbkana_l) || defined(__CRT_HAVE__ismbbkprint_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbgraph_l.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbgraph_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbgraph_l)(unsigned int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbgraph_l))(__ch, __locale); })
#endif /* ... */
#ifndef ___ismbblead_l_defined
#define ___ismbblead_l_defined
#ifdef __CRT_HAVE__ismbblead_l
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbblead_l,(unsigned int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbblead_l.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbblead_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbblead_l)(unsigned int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbblead_l))(__ch, __locale); })
#else /* ... */
#undef ___ismbblead_l_defined
#endif /* !... */
#endif /* !___ismbblead_l_defined */
#ifndef ___ismbbtrail_l_defined
#define ___ismbbtrail_l_defined
#ifdef __CRT_HAVE__ismbbtrail_l
/* @param: ch: Should actually be `unsigned char ch' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ismbbtrail_l,(unsigned int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbctype/_ismbbtrail_l.h>
/* @param: ch: Should actually be `unsigned char ch' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbbtrail_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ismbbtrail_l)(unsigned int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbbtrail_l))(__ch, __locale); })
#else /* ... */
#undef ___ismbbtrail_l_defined
#endif /* !... */
#endif /* !___ismbbtrail_l_defined */
#ifndef ___ismbslead_l_defined
#define ___ismbslead_l_defined
#ifdef __CRT_HAVE__ismbslead_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_ismbslead_l,(unsigned char const *__str, unsigned char const *__pos, __locale_t __locale),(__str,__pos,__locale))
#elif defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbstring/_ismbslead_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbslead_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _ismbslead_l)(unsigned char const *__str, unsigned char const *__pos, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbslead_l))(__str, __pos, __locale); })
#else /* ... */
#undef ___ismbslead_l_defined
#endif /* !... */
#endif /* !___ismbslead_l_defined */
#ifndef ___ismbstrail_l_defined
#define ___ismbstrail_l_defined
#ifdef __CRT_HAVE__ismbstrail_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_ismbstrail_l,(unsigned char const *__str, unsigned char const *__pos, __locale_t __locale),(__str,__pos,__locale))
#elif defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <libc/local/mbstring/_ismbstrail_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ismbstrail_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _ismbstrail_l)(unsigned char const *__str, unsigned char const *__pos, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ismbstrail_l))(__str, __pos, __locale); })
#else /* ... */
#undef ___ismbstrail_l_defined
#endif /* !... */
#endif /* !___ismbstrail_l_defined */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_MBCTYPE_H */
