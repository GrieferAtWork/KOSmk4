/* HASH CRC-32:0xd2acacf4 */
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
#ifndef _CTYPE_H
#define _CTYPE_H 1

#ifdef _CXX_STDONLY_CCTYPE
#ifdef __CXX_SYSTEM_HEADER
#undef _CTYPE_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "ctype.h" after "cctype" */
__NAMESPACE_STD_USING(iscntrl)
__NAMESPACE_STD_USING(isspace)
__NAMESPACE_STD_USING(isupper)
__NAMESPACE_STD_USING(islower)
__NAMESPACE_STD_USING(isalpha)
__NAMESPACE_STD_USING(isdigit)
__NAMESPACE_STD_USING(isxdigit)
__NAMESPACE_STD_USING(isalnum)
__NAMESPACE_STD_USING(ispunct)
__NAMESPACE_STD_USING(isgraph)
__NAMESPACE_STD_USING(isprint)
__NAMESPACE_STD_USING(tolower)
__NAMESPACE_STD_USING(toupper)
__NAMESPACE_STD_USING(isblank)
#undef _CXX_STDONLY_CCTYPE
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CCTYPE */
#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#ifdef __USE_XOPEN2K8
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 */

__SYSDECL_BEGIN

#ifdef __CC__
__NAMESPACE_STD_BEGIN
#if __has_builtin(__builtin_iscntrl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iscntrl)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iscntrl,(int __ch),{ return __builtin_iscntrl(__ch); })
#elif defined(__CRT_HAVE_iscntrl)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iscntrl,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <local/ctype/iscntrl.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(iscntrl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iscntrl)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iscntrl))(__ch); })
#endif /* !... */
#if __has_builtin(__builtin_isspace) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isspace)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isspace,(int __ch),{ return __builtin_isspace(__ch); })
#elif defined(__CRT_HAVE_isspace)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isspace,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <local/ctype/isspace.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(isspace, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isspace)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isspace))(__ch); })
#endif /* !... */
#if __has_builtin(__builtin_isupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isupper)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isupper,(int __ch),{ return __builtin_isupper(__ch); })
#elif defined(__CRT_HAVE_isupper)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isupper,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <local/ctype/isupper.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(isupper, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isupper)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isupper))(__ch); })
#endif /* !... */
#if __has_builtin(__builtin_islower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_islower)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,islower,(int __ch),{ return __builtin_islower(__ch); })
#elif defined(__CRT_HAVE_islower)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,islower,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <local/ctype/islower.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(islower, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL islower)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(islower))(__ch); })
#endif /* !... */
#if __has_builtin(__builtin_isalpha) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isalpha)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isalpha,(int __ch),{ return __builtin_isalpha(__ch); })
#elif defined(__CRT_HAVE_isalpha)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isalpha,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <local/ctype/isalpha.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(isalpha, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isalpha)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalpha))(__ch); })
#endif /* !... */
#if __has_builtin(__builtin_isdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isdigit)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isdigit,(int __ch),{ return __builtin_isdigit(__ch); })
#elif defined(__CRT_HAVE_isdigit)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isdigit,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <local/ctype/isdigit.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(isdigit, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isdigit)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isdigit))(__ch); })
#endif /* !... */
#if __has_builtin(__builtin_isxdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isxdigit)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isxdigit,(int __ch),{ return __builtin_isxdigit(__ch); })
#elif defined(__CRT_HAVE_isxdigit)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isxdigit,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <local/ctype/isxdigit.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(isxdigit, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isxdigit)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isxdigit))(__ch); })
#endif /* !... */
#if __has_builtin(__builtin_isalnum) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isalnum)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isalnum,(int __ch),{ return __builtin_isalnum(__ch); })
#elif defined(__CRT_HAVE_isalnum)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isalnum,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <local/ctype/isalnum.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(isalnum, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isalnum)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalnum))(__ch); })
#endif /* !... */
#if __has_builtin(__builtin_ispunct) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ispunct)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,ispunct,(int __ch),{ return __builtin_ispunct(__ch); })
#elif defined(__CRT_HAVE_ispunct)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,ispunct,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <local/ctype/ispunct.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(ispunct, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL ispunct)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ispunct))(__ch); })
#endif /* !... */
#if __has_builtin(__builtin_isgraph) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isgraph)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isgraph,(int __ch),{ return __builtin_isgraph(__ch); })
#elif defined(__CRT_HAVE_isgraph)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isgraph,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <local/ctype/isgraph.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(isgraph, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isgraph)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isgraph))(__ch); })
#endif /* !... */
#if __has_builtin(__builtin_isprint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isprint)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isprint,(int __ch),{ return __builtin_isprint(__ch); })
#elif defined(__CRT_HAVE_isprint)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isprint,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <local/ctype/isprint.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(isprint, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isprint)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isprint))(__ch); })
#endif /* !... */
#if __has_builtin(__builtin_tolower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tolower)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,tolower,(int __ch),{ return __builtin_tolower(__ch); })
#elif defined(__CRT_HAVE_tolower)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,tolower,(int __ch),(__ch))
#elif defined(__CRT_HAVE__tolower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,tolower,(int __ch),_tolower,(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <local/ctype/tolower.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(tolower, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL tolower)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tolower))(__ch); })
#endif /* !... */
#if __has_builtin(__builtin_toupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_toupper)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,toupper,(int __ch),{ return __builtin_toupper(__ch); })
#elif defined(__CRT_HAVE_toupper)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,toupper,(int __ch),(__ch))
#elif defined(__CRT_HAVE__toupper)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,toupper,(int __ch),_toupper,(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <local/ctype/toupper.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(toupper, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL toupper)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(toupper))(__ch); })
#endif /* !... */
#if __has_builtin(__builtin_isblank) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isblank)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isblank,(int __ch),{ return __builtin_isblank(__ch); })
#elif defined(__CRT_HAVE_isblank)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isblank,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <local/ctype/isblank.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(isblank, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isblank)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isblank))(__ch); })
#endif /* !... */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(iscntrl)
__NAMESPACE_STD_USING(isspace)
__NAMESPACE_STD_USING(isupper)
__NAMESPACE_STD_USING(islower)
__NAMESPACE_STD_USING(isalpha)
__NAMESPACE_STD_USING(isdigit)
__NAMESPACE_STD_USING(isxdigit)
__NAMESPACE_STD_USING(isalnum)
__NAMESPACE_STD_USING(ispunct)
__NAMESPACE_STD_USING(isgraph)
__NAMESPACE_STD_USING(isprint)
__NAMESPACE_STD_USING(tolower)
__NAMESPACE_STD_USING(toupper)
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __USE_ISOC99
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(isblank)
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_ISOC99 */

#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_iscntrl_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iscntrl_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___iscntrl_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iscntrl_l,(int __ch, __locale_t __locale),__iscntrl_l,(__ch,__locale))
#else /* ... */
#include <local/ctype/iscntrl_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(iscntrl_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iscntrl_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iscntrl_l))(__ch, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_isspace_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isspace_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___isspace_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isspace_l,(int __ch, __locale_t __locale),__isspace_l,(__ch,__locale))
#else /* ... */
#include <local/ctype/isspace_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(isspace_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isspace_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isspace_l))(__ch, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_isupper_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isupper_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___isupper_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isupper_l,(int __ch, __locale_t __locale),__isupper_l,(__ch,__locale))
#else /* ... */
#include <local/ctype/isupper_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(isupper_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isupper_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isupper_l))(__ch, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_islower_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,islower_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___islower_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,islower_l,(int __ch, __locale_t __locale),__islower_l,(__ch,__locale))
#else /* ... */
#include <local/ctype/islower_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(islower_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL islower_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(islower_l))(__ch, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_isalpha_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalpha_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___isalpha_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalpha_l,(int __ch, __locale_t __locale),__isalpha_l,(__ch,__locale))
#else /* ... */
#include <local/ctype/isalpha_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(isalpha_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isalpha_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalpha_l))(__ch, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_isdigit_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isdigit_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___isdigit_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isdigit_l,(int __ch, __locale_t __locale),__isdigit_l,(__ch,__locale))
#else /* ... */
#include <local/ctype/isdigit_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(isdigit_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isdigit_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isdigit_l))(__ch, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_isxdigit_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isxdigit_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___isxdigit_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isxdigit_l,(int __ch, __locale_t __locale),__isxdigit_l,(__ch,__locale))
#else /* ... */
#include <local/ctype/isxdigit_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(isxdigit_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isxdigit_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isxdigit_l))(__ch, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_isalnum_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalnum_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___isalnum_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalnum_l,(int __ch, __locale_t __locale),__isalnum_l,(__ch,__locale))
#else /* ... */
#include <local/ctype/isalnum_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(isalnum_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isalnum_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalnum_l))(__ch, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_ispunct_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,ispunct_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___ispunct_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,ispunct_l,(int __ch, __locale_t __locale),__ispunct_l,(__ch,__locale))
#else /* ... */
#include <local/ctype/ispunct_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ispunct_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL ispunct_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ispunct_l))(__ch, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_isgraph_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isgraph_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___isgraph_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isgraph_l,(int __ch, __locale_t __locale),__isgraph_l,(__ch,__locale))
#else /* ... */
#include <local/ctype/isgraph_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(isgraph_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isgraph_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isgraph_l))(__ch, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_isprint_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isprint_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___isprint_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isprint_l,(int __ch, __locale_t __locale),__isprint_l,(__ch,__locale))
#else /* ... */
#include <local/ctype/isprint_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(isprint_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isprint_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isprint_l))(__ch, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_isblank_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isblank_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___isblank_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isblank_l,(int __ch, __locale_t __locale),__isblank_l,(__ch,__locale))
#else /* ... */
#include <local/ctype/isblank_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(isblank_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isblank_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isblank_l))(__ch, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_tolower_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,tolower_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__tolower_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,tolower_l,(int __ch, __locale_t __locale),_tolower_l,(__ch,__locale))
#elif defined(__CRT_HAVE___tolower_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,tolower_l,(int __ch, __locale_t __locale),__tolower_l,(__ch,__locale))
#else /* ... */
#include <local/ctype/tolower_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(tolower_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL tolower_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tolower_l))(__ch, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_toupper_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,toupper_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__toupper_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,toupper_l,(int __ch, __locale_t __locale),_toupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE___toupper_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,toupper_l,(int __ch, __locale_t __locale),__toupper_l,(__ch,__locale))
#else /* ... */
#include <local/ctype/toupper_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(toupper_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL toupper_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(toupper_l))(__ch, __locale); })
#endif /* !... */
#endif /* __USE_XOPEN2K8 */


/* ASCII-only, inline variants. */
#ifndef __NO_ATTR_INLINE
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_iscntrl)(int __ch) { return (__UINT8_TYPE__)__ch <= 0x1f || (__UINT8_TYPE__)__ch == 0x7f; }
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_isspace)(int __ch) { return ((__UINT8_TYPE__)__ch >= 0x09 && (__UINT8_TYPE__)__ch <= 0x0d) || (__UINT8_TYPE__)__ch == 0x20; }
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_isupper)(int __ch) { return (__UINT8_TYPE__)__ch >= 0x41 && (__UINT8_TYPE__)__ch <= 0x5a; }
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_islower)(int __ch) { return (__UINT8_TYPE__)__ch >= 0x61 && (__UINT8_TYPE__)__ch <= 0x7a; }
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_isalpha)(int __ch) { return __ascii_isupper(__ch) || __ascii_islower(__ch); }
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_isdigit)(int __ch) { return (__UINT8_TYPE__)__ch >= 0x30 && (__UINT8_TYPE__)__ch <= 0x39; }
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_isxdigit)(int __ch) { return __ascii_isdigit(__ch) || ((__UINT8_TYPE__)__ch >= 0x41 && (__UINT8_TYPE__)__ch <= 0x46) || ((__UINT8_TYPE__)__ch >= 0x61 && (__UINT8_TYPE__)__ch <= 0x66); }
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_isalnum)(int __ch) { return __ascii_isupper(__ch) || __ascii_islower(__ch) || __ascii_isdigit(__ch); }
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_ispunct)(int __ch) { return ((__UINT8_TYPE__)__ch >= 0x21 && (__UINT8_TYPE__)__ch <= 0x2f) || ((__UINT8_TYPE__)__ch >= 0x3a && (__UINT8_TYPE__)__ch <= 0x40) || ((__UINT8_TYPE__)__ch >= 0x5b && (__UINT8_TYPE__)__ch <= 0x60) || ((__UINT8_TYPE__)__ch >= 0x7b && (__UINT8_TYPE__)__ch <= 0x7e); }
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_isgraph)(int __ch) { return (__UINT8_TYPE__)__ch >= 0x21 && (__UINT8_TYPE__)__ch <= 0x7e; }
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_isprint)(int __ch) { return (__UINT8_TYPE__)__ch >= 0x20 && (__UINT8_TYPE__)__ch <= 0x7e; }
__LOCAL __ATTR_WUNUSED __ATTR_CONST int __NOTHROW(__LIBCCALL __ascii_tolower)(int __ch) { return __ascii_isupper(__ch) ? ((__UINT8_TYPE__)__ch+0x20) : __ch; }
__LOCAL __ATTR_WUNUSED __ATTR_CONST int __NOTHROW(__LIBCCALL __ascii_toupper)(int __ch) { return __ascii_islower(__ch) ? ((__UINT8_TYPE__)__ch-0x20) : __ch; }
#ifdef __USE_ISOC99
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_isblank)(int __ch) { return (__UINT8_TYPE__)__ch == 0x09 || (__UINT8_TYPE__)__ch == 0x20; }
#endif /* __USE_ISOC99 */
#elif !defined(__NO_XBLOCK)
#define __ascii_iscntrl(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN __ac_ch <= 0x1f || __ac_ch == 0x7f; })
#define __ascii_isspace(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN (__ac_ch >= 0x09 && __ac_ch <= 0x0d) || __ac_ch == 0x20; })
#define __ascii_isupper(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN __ac_ch >= 0x41 && __ac_ch <= 0x5a; })
#define __ascii_islower(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN __ac_ch >= 0x61 && __ac_ch <= 0x7a; })
#define __ascii_isalpha(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN __ascii_isupper(__ac_ch) || __ascii_islower(__ac_ch); })
#define __ascii_isdigit(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN __ac_ch >= 0x30 && __ac_ch <= 0x39; })
#define __ascii_isxdigit(ch) __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN __ascii_isdigit(__ac_ch) || (__ac_ch >= 0x41 && __ac_ch <= 0x46) || (__ac_ch >= 0x61 && __ac_ch <= 0x66); })
#define __ascii_isalnum(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN __ascii_isupper(__ac_ch) || __ascii_islower(__ac_ch) || __ascii_isdigit(__ac_ch); })
#define __ascii_ispunct(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN (__ac_ch >= 0x21 && __ac_ch <= 0x2f) || (__ac_ch >= 0x3a && __ac_ch <= 0x40) || (__ac_ch >= 0x5b && __ac_ch <= 0x60) || (__ac_ch >= 0x7b && __ac_ch <= 0x7e); })
#define __ascii_isgraph(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN __ac_ch >= 0x21 && __ac_ch <= 0x7e; })
#define __ascii_isprint(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN __ac_ch >= 0x20 && __ac_ch <= 0x7e; })
#define __ascii_tolower(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN (int)(__ascii_isupper(ch) ? (__ac_ch+0x20) : __ac_ch); })
#define __ascii_toupper(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN (int)(__ascii_islower(ch) ? (__ac_ch-0x20) : __ac_ch); })
#ifdef __USE_ISOC99
#define __ascii_isblank(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN __ac_ch == 0x09 || __ac_ch == 0x20; })
#endif /* __USE_ISOC99 */
#else
#define __ascii_iscntrl(ch)  ((__UINT8_TYPE__)(ch) <= 0x1f || (__UINT8_TYPE__)(ch) == 0x7f)
#define __ascii_isspace(ch) (((__UINT8_TYPE__)(ch) >= 0x09 && (__UINT8_TYPE__)(ch) <= 0x0d) || \
                              (__UINT8_TYPE__)(ch) == 0x20)
#define __ascii_isupper(ch)  ((__UINT8_TYPE__)(ch) >= 0x41 && (__UINT8_TYPE__)(ch) <= 0x5a)
#define __ascii_islower(ch)  ((__UINT8_TYPE__)(ch) >= 0x61 && (__UINT8_TYPE__)(ch) <= 0x7a)
#define __ascii_isalpha(ch)  (__ascii_isupper(ch) || __ascii_islower(ch))
#define __ascii_isdigit(ch)  ((__UINT8_TYPE__)(ch) >= 0x30 && (__UINT8_TYPE__)(ch) <= 0x39)
#define __ascii_isxdigit(ch)  (__ascii_isdigit(ch) || \
                             ((__UINT8_TYPE__)(ch) >= 0x41 && (__UINT8_TYPE__)(ch) <= 0x46) || \
                             ((__UINT8_TYPE__)(ch) >= 0x61 && (__UINT8_TYPE__)(ch) <= 0x66))
#define __ascii_isalnum(ch)   (__ascii_isupper(ch) || __ascii_islower(ch) || __ascii_isdigit(ch))
#define __ascii_ispunct(ch) (((__UINT8_TYPE__)(ch) >= 0x21 && (__UINT8_TYPE__)(ch) <= 0x2f) || \
                             ((__UINT8_TYPE__)(ch) >= 0x3a && (__UINT8_TYPE__)(ch) <= 0x40) || \
                             ((__UINT8_TYPE__)(ch) >= 0x5b && (__UINT8_TYPE__)(ch) <= 0x60) || \
                             ((__UINT8_TYPE__)(ch) >= 0x7b && (__UINT8_TYPE__)(ch) <= 0x7e))
#define __ascii_isgraph(ch)  ((__UINT8_TYPE__)(ch) >= 0x21 && (__UINT8_TYPE__)(ch) <= 0x7e)
#define __ascii_isprint(ch)  ((__UINT8_TYPE__)(ch) >= 0x20 && (__UINT8_TYPE__)(ch) <= 0x7e)
#define __ascii_tolower(ch)  ((int)(__ascii_isupper(ch) ? ((ch)+0x20) : (ch)))
#define __ascii_toupper(ch)  ((int)(__ascii_islower(ch) ? ((ch)-0x20) : (ch)))
#ifdef __USE_ISOC99
#define __ascii_isblank(ch)  ((__UINT8_TYPE__)(ch) == 0x09 || (__UINT8_TYPE__)(ch) == 0x20)
#endif /* __USE_ISOC99 */
#endif


#if (!defined(__cplusplus) || defined(__USE_CTYPE_MACROS)) && !defined(__CXX_SYSTEM_HEADER)

#if defined(__CRT_GLC) && defined(__CRT_HAVE___ctype_b_loc)  /* ---- GLIBC */
#include <hybrid/byteorder.h>
__NAMESPACE_INT_BEGIN
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__UINT16_TYPE__ const **,__NOTHROW,__ctype_b_loc,(void),())
#ifndef __NO_XBLOCK
#ifdef __CRT_HAVE___ctype_tolower_loc
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__INT32_TYPE__ const **,__NOTHROW,__ctype_tolower_loc,(void),())
#endif /* __CRT_HAVE___ctype_tolower_loc */
#ifdef __CRT_HAVE___ctype_toupper_loc
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__INT32_TYPE__ const **,__NOTHROW,__ctype_toupper_loc,(void),())
#endif /* __CRT_HAVE___ctype_toupper_loc */
#endif /* !__NO_XBLOCK */
__NAMESPACE_INT_END
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __inline_isupper(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 0))
#define __inline_islower(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 1))
#define __inline_isalpha(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 2))
#define __inline_isdigit(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 3))
#define __inline_isxdigit(ch) ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 4))
#define __inline_isspace(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 5))
#define __inline_isprint(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 6))
#define __inline_isgraph(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 7))
#define __inline_iscntrl(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 9))
#define __inline_ispunct(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 10))
#define __inline_isalnum(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 11))
#ifdef __USE_ISOC99
#define __inline_isblank(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 8))
#endif /* __USE_ISOC99 */
#ifndef __USE_XOPEN2K8
#define __inline_isupper_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 0))
#define __inline_islower_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 1))
#define __inline_isalpha_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 2))
#define __inline_isdigit_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 3))
#define __inline_isxdigit_l(ch, locale) ((locale)->__ctype_b[ch] & (1 << 4))
#define __inline_isspace_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 5))
#define __inline_isprint_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 6))
#define __inline_isgraph_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 7))
#define __inline_iscntrl_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 9))
#define __inline_ispunct_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 10))
#define __inline_isalnum_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 11))
#define __inline_isblank_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 8))
#endif /* !__USE_XOPEN2K8 */
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#define __inline_isupper(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 8))
#define __inline_islower(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 9))
#define __inline_isalpha(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 10))
#define __inline_isdigit(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 11))
#define __inline_isxdigit(ch) ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 12))
#define __inline_isspace(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 13))
#define __inline_isprint(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 14))
#define __inline_isgraph(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 15))
#define __inline_iscntrl(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 1))
#define __inline_ispunct(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 2))
#define __inline_isalnum(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 3))
#ifdef __USE_ISOC99
#define __inline_isblank(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 0))
#endif /* __USE_ISOC99 */
#ifdef __USE_XOPEN2K8
#define __inline_isupper_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 8))
#define __inline_islower_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 9))
#define __inline_isalpha_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 10))
#define __inline_isdigit_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 11))
#define __inline_isxdigit_l(ch, locale) ((locale)->__ctype_b[(int)(ch)] & (1 << 12))
#define __inline_isspace_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 13))
#define __inline_isprint_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 14))
#define __inline_isgraph_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 15))
#define __inline_iscntrl_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 1))
#define __inline_ispunct_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 2))
#define __inline_isalnum_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 3))
#define __inline_isblank_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 0))
#endif /* !__USE_XOPEN2K8 */
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#ifndef __NO_XBLOCK
#ifdef __CRT_HAVE___ctype_tolower_loc
#define __inline_tolower(ch)  __XBLOCK({ int __tol_ch = (int)(ch); __XRETURN __tol_ch >= -128 && __tol_ch < 256 ? (*__ctype_tolower_loc())[__tol_ch] : __tol_ch; })
#endif /* __CRT_HAVE___ctype_tolower_loc */
#ifdef __CRT_HAVE___ctype_toupper_loc
#define __inline_toupper(ch)  __XBLOCK({ int __tol_ch = (int)(ch); __XRETURN __tol_ch >= -128 && __tol_ch < 256 ? (*__ctype_toupper_loc())[__tol_ch] : __tol_ch; })
#endif /* __CRT_HAVE___ctype_toupper_loc */
#endif /* !__NO_XBLOCK */
#elif defined(__CRT_CYG) && defined(__CRT_HAVE___locale_ctype_ptr)  /* ---- CYGWIN */
__NAMESPACE_INT_BEGIN
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char const *,__NOTHROW,__locale_ctype_ptr,(void),())
#ifdef __CRT_HAVE___locale_ctype_ptr_l
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED,char const *,__NOTHROW_NCX,__locale_ctype_ptr_l,(__locale_t __locale),(__locale))
#endif /* __CRT_HAVE___locale_ctype_ptr_l */
__NAMESPACE_INT_END
#define __chtype_lookup(ch)           ((__NAMESPACE_INT_SYM __locale_ctype_ptr()+1)[(int)(ch)])
#ifdef __CRT_HAVE___locale_ctype_ptr_l
#define __chtype_lookup_l(ch, locale) ((__NAMESPACE_INT_SYM __locale_ctype_ptr_l(locale)+1)[(int)(ch)])
#else /* __CRT_HAVE___locale_ctype_ptr_l */
#define __chtype_lookup_l(ch, locale) ((__NAMESPACE_INT_SYM __locale_ctype_ptr(locale)+1)[(int)(ch)])
#endif /* !__CRT_HAVE___locale_ctype_ptr_l */
#define __inline_isalpha(ch)           (__chtype_lookup(ch)&3)
#define __inline_isupper(ch)          ((__chtype_lookup(ch)&3)==1)
#define __inline_islower(ch)          ((__chtype_lookup(ch)&3)==2)
#define __inline_isdigit(ch)           (__chtype_lookup(ch)&4)
#define __inline_isxdigit(ch)          (__chtype_lookup(ch)&014)
#define __inline_isspace(ch)           (__chtype_lookup(ch)&010)
#define __inline_ispunct(ch)           (__chtype_lookup(ch)&020)
#define __inline_isalnum(ch)           (__chtype_lookup(ch)&7)
#define __inline_isprint(ch)           (__chtype_lookup(ch)&0227)
#define __inline_isgraph(ch)           (__chtype_lookup(ch)&027)
#define __inline_iscntrl(ch)           (__chtype_lookup(ch)&040)
#ifdef __USE_XOPEN2K8
#define __inline_isalpha_l(ch, locale)  (__chtype_lookup_l(ch, locale)&3)
#define __inline_isupper_l(ch, locale) ((__chtype_lookup_l(ch, locale)&3)==1)
#define __inline_islower_l(ch, locale) ((__chtype_lookup_l(ch, locale)&3)==2)
#define __inline_isdigit_l(ch, locale)  (__chtype_lookup_l(ch, locale)&4)
#define __inline_isxdigit_l(ch, locale) (__chtype_lookup_l(ch, locale)&014)
#define __inline_isspace_l(ch, locale)  (__chtype_lookup_l(ch, locale)&010)
#define __inline_ispunct_l(ch, locale)  (__chtype_lookup_l(ch, locale)&020)
#define __inline_isalnum_l(ch, locale)  (__chtype_lookup_l(ch, locale)&7)
#define __inline_isprint_l(ch, locale)  (__chtype_lookup_l(ch, locale)&0227)
#define __inline_isgraph_l(ch, locale)  (__chtype_lookup_l(ch, locale)&027)
#define __inline_iscntrl_l(ch, locale)  (__chtype_lookup_l(ch, locale)&040)
#endif /* __USE_XOPEN2K8 */
#ifdef __USE_ISOC99
#ifndef __NO_XBLOCK
#define __inline_isblank(ch)           __XBLOCK({ int __x = (ch); __XRETURN (__chtype_lookup(__x) & 0200) || (__x) == '\t'; })
#define __inline_isblank_l(ch, locale) __XBLOCK({ int __x = (ch); __XRETURN (__chtype_lookup_l(__x, locale) & 0200) || (__x) == '\t'; })
#endif /* !__NO_XBLOCK */
#endif /* __USE_ISOC99 */
#elif defined(__CRT_DOS) && defined(__CRT_HAVE__isctype) /* ---- DOS (MSVC) */
__NAMESPACE_INT_BEGIN
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,_isctype,(int __ch, int __mask),(__ch,__mask))
#ifdef __CRT_HAVE__isctype_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isctype_l,(int __ch, int __mask, __locale_t __locale),(__ch,__mask,__locale))
#endif /* __CRT_HAVE__isctype_l */
__NAMESPACE_INT_END
#define __dos_isctype(ch, mask)      (__NAMESPACE_INT_SYM _isctype)(ch, mask)
#ifdef __CRT_HAVE__isctype_l
#define _isctype_l(ch, mask, locale) (__NAMESPACE_INT_SYM _isctype_l)(ch, mask, locale)
#else /* __CRT_HAVE__isctype_l */
#define _isctype_l(ch, mask, locale) (__NAMESPACE_INT_SYM _isctype)(ch, mask)
#endif /* !__CRT_HAVE__isctype_l */
#define __inline_isalnum(ch)            __dos_isctype((ch), 0x0107)
#define __inline_isalpha(ch)            __dos_isctype((ch), 0x0103)
#define __inline_isupper(ch)            __dos_isctype((ch), 0x0001)
#define __inline_islower(ch)            __dos_isctype((ch), 0x0002)
#define __inline_isdigit(ch)            __dos_isctype((ch), 0x0004)
#define __inline_isxdigit(ch)           __dos_isctype((ch), 0x0080)
#define __inline_isspace(ch)            __dos_isctype((ch), 0x0008)
#define __inline_ispunct(ch)            __dos_isctype((ch), 0x0010)
#define __inline_isprint(ch)            __dos_isctype((ch), 0x0157)
#define __inline_isgraph(ch)            __dos_isctype((ch), 0x0117)
#define __inline_iscntrl(ch)            __dos_isctype((ch), 0x0020)
#ifdef __USE_XOPEN2K8
#define __inline_isalnum_l(ch, locale)   _isctype_l((ch), 0x0107, (locale))
#define __inline_isalpha_l(ch, locale)   _isctype_l((ch), 0x0103, (locale))
#define __inline_isupper_l(ch, locale)   _isctype_l((ch), 0x0001, (locale))
#define __inline_islower_l(ch, locale)   _isctype_l((ch), 0x0002, (locale))
#define __inline_isdigit_l(ch, locale)   _isctype_l((ch), 0x0004, (locale))
#define __inline_isxdigit_l(ch, locale)  _isctype_l((ch), 0x0080, (locale))
#define __inline_isspace_l(ch, locale)   _isctype_l((ch), 0x0008, (locale))
#define __inline_ispunct_l(ch, locale)   _isctype_l((ch), 0x0010, (locale))
#define __inline_isprint_l(ch, locale)   _isctype_l((ch), 0x0157, (locale))
#define __inline_isgraph_l(ch, locale)   _isctype_l((ch), 0x0117, (locale))
#define __inline_iscntrl_l(ch, locale)   _isctype_l((ch), 0x0020, (locale))
#endif /* __USE_XOPEN2K8 */
#endif /* CRT... */

#ifndef __inline_isalnum
#define __inline_isalnum(ch) (isalnum)(ch)
#endif /* !__inline_isalnum */
#ifndef __inline_isalpha
#define __inline_isalpha(ch) (isalpha)(ch)
#endif /* !__inline_isalpha */
#ifndef __inline_isupper
#define __inline_isupper(ch) (isupper)(ch)
#endif /* !__inline_isupper */
#ifndef __inline_islower
#define __inline_islower(ch) (islower)(ch)
#endif /* !__inline_islower */
#ifndef __inline_isdigit
#define __inline_isdigit(ch) (isdigit)(ch)
#endif /* !__inline_isdigit */
#ifndef __inline_isxdigit
#define __inline_isxdigit(ch) (isxdigit)(ch)
#endif /* !__inline_isxdigit */
#ifndef __inline_isspace
#define __inline_isspace(ch) (isspace)(ch)
#endif /* !__inline_isspace */
#ifndef __inline_ispunct
#define __inline_ispunct(ch) (ispunct)(ch)
#endif /* !__inline_ispunct */
#ifndef __inline_isprint
#define __inline_isprint(ch) (isprint)(ch)
#endif /* !__inline_isprint */
#ifndef __inline_isgraph
#define __inline_isgraph(ch) (isgraph)(ch)
#endif /* !__inline_isgraph */
#ifndef __inline_iscntrl
#define __inline_iscntrl(ch) (iscntrl)(ch)
#endif /* !__inline_iscntrl */
#ifdef __USE_ISOC99
#ifndef __inline_isblank
#define __inline_isblank(ch) (isblank)(ch)
#endif /* !__inline_isblank */
#endif /* __USE_ISOC99 */

#ifdef __USE_XOPEN2K8
#ifdef __inline_isalnum_l
#define isalnum_l(ch, locale)  __inline_isalnum_l(ch, locale)
#endif /* __inline_isalnum_l */
#ifdef __inline_isalpha_l
#define isalpha_l(ch, locale)  __inline_isalpha_l(ch, locale)
#endif /* __inline_isalpha_l */
#ifdef __inline_isupper_l
#define isupper_l(ch, locale)  __inline_isupper_l(ch, locale)
#endif /* __inline_isupper_l */
#ifdef __inline_islower_l
#define islower_l(ch, locale)  __inline_islower_l(ch, locale)
#endif /* __inline_islower_l */
#ifdef __inline_isdigit_l
#define isdigit_l(ch, locale)  __inline_isdigit_l(ch, locale)
#endif /* __inline_isdigit_l */
#ifdef __inline_isxdigit_l
#define isxdigit_l(ch, locale) __inline_isxdigit_l(ch, locale)
#endif /* __inline_isxdigit_l */
#ifdef __inline_isspace_l
#define isspace_l(ch, locale)  __inline_isspace_l(ch, locale)
#endif /* __inline_isspace_l */
#ifdef __inline_ispunct_l
#define ispunct_l(ch, locale)  __inline_ispunct_l(ch, locale)
#endif /* __inline_ispunct_l */
#ifdef __inline_isprint_l
#define isprint_l(ch, locale)  __inline_isprint_l(ch, locale)
#endif /* __inline_isprint_l */
#ifdef __inline_isgraph_l
#define isgraph_l(ch, locale)  __inline_isgraph_l(ch, locale)
#endif /* __inline_isgraph_l */
#ifdef __inline_iscntrl_l
#define iscntrl_l(ch, locale)  __inline_iscntrl_l(ch, locale)
#endif /* __inline_iscntrl_l */
#endif /* __USE_XOPEN2K8 */

#ifndef __NO_builtin_constant_p
#ifndef __NO_builtin_choose_expr
#define isalnum(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isalnum(ch), __inline_isalnum(ch))
#define isalpha(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isalpha(ch), __inline_isalpha(ch))
#define isupper(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isupper(ch), __inline_isupper(ch))
#define islower(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_islower(ch), __inline_islower(ch))
#define isdigit(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isdigit(ch), __inline_isdigit(ch))
#define isxdigit(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isxdigit(ch), __inline_isxdigit(ch))
#define isspace(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isspace(ch), __inline_isspace(ch))
#define ispunct(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_ispunct(ch), __inline_ispunct(ch))
#define isprint(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isprint(ch), __inline_isprint(ch))
#define isgraph(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isgraph(ch), __inline_isgraph(ch))
#define iscntrl(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_iscntrl(ch), __inline_iscntrl(ch))
#ifdef __USE_ISOC99
#define isblank(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isblank(ch), __inline_isblank(ch))
#endif /* __USE_ISOC99 */
#else /* !__NO_builtin_choose_expr */
#define isalnum(ch)  (__builtin_constant_p(ch) ? __ascii_isalnum(ch) : __inline_isalnum(ch))
#define isalpha(ch)  (__builtin_constant_p(ch) ? __ascii_isalpha(ch) : __inline_isalpha(ch))
#define isupper(ch)  (__builtin_constant_p(ch) ? __ascii_isupper(ch) : __inline_isupper(ch))
#define islower(ch)  (__builtin_constant_p(ch) ? __ascii_islower(ch) : __inline_islower(ch))
#define isdigit(ch)  (__builtin_constant_p(ch) ? __ascii_isdigit(ch) : __inline_isdigit(ch))
#define isxdigit(ch) (__builtin_constant_p(ch) ? __ascii_isxdigit(ch) : __inline_isxdigit(ch))
#define isspace(ch)  (__builtin_constant_p(ch) ? __ascii_isspace(ch) : __inline_isspace(ch))
#define ispunct(ch)  (__builtin_constant_p(ch) ? __ascii_ispunct(ch) : __inline_ispunct(ch))
#define isprint(ch)  (__builtin_constant_p(ch) ? __ascii_isprint(ch) : __inline_isprint(ch))
#define isgraph(ch)  (__builtin_constant_p(ch) ? __ascii_isgraph(ch) : __inline_isgraph(ch))
#define iscntrl(ch)  (__builtin_constant_p(ch) ? __ascii_iscntrl(ch) : __inline_iscntrl(ch))
#ifdef __USE_ISOC99
#define isblank(ch)  (__builtin_constant_p(ch) ? __ascii_isblank(ch) : __inline_isblank(ch))
#endif /* __USE_ISOC99 */
#endif /* __NO_builtin_choose_expr */
#else /* !__NO_builtin_constant_p */
#define isalnum(ch)  __inline_isalnum(ch)
#define isalpha(ch)  __inline_isalpha(ch)
#define isupper(ch)  __inline_isupper(ch)
#define islower(ch)  __inline_islower(ch)
#define isdigit(ch)  __inline_isdigit(ch)
#define isxdigit(ch) __inline_isxdigit(ch)
#define isspace(ch)  __inline_isspace(ch)
#define ispunct(ch)  __inline_ispunct(ch)
#define isprint(ch)  __inline_isprint(ch)
#define isgraph(ch)  __inline_isgraph(ch)
#define iscntrl(ch)  __inline_iscntrl(ch)
#ifdef __USE_ISOC99
#define isblank(ch)  __inline_isblank(ch)
#endif /* __USE_ISOC99 */
#endif /* __NO_builtin_constant_p */

#endif /* (!__cplusplus || __USE_CTYPE_MACROS) && !__CXX_SYSTEM_HEADER */


#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifdef __CRT_HAVE_isascii
/* Returns non-zero if `(C & ~0x7f) == 0' */
__CDECLARE(__ATTR_CONST,int,__NOTHROW,isascii,(int __c),(__c))
#else /* __CRT_HAVE_isascii */
#include <local/ctype/isascii.h>
/* Returns non-zero if `(C & ~0x7f) == 0' */
__NAMESPACE_LOCAL_USING_OR_IMPL(isascii, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST int __NOTHROW(__LIBCCALL isascii)(int __c) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isascii))(__c); })
#endif /* !__CRT_HAVE_isascii */
#ifdef __CRT_HAVE_toascii
/* Re-returns `C & 0x7f' */
__CDECLARE(__ATTR_CONST,int,__NOTHROW,toascii,(int __c),(__c))
#else /* __CRT_HAVE_toascii */
#include <local/ctype/toascii.h>
/* Re-returns `C & 0x7f' */
__NAMESPACE_LOCAL_USING_OR_IMPL(toascii, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST int __NOTHROW(__LIBCCALL toascii)(int __c) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(toascii))(__c); })
#endif /* !__CRT_HAVE_toascii */
#if (!defined(__cplusplus) || defined(__USE_CTYPE_MACROS)) && !defined(__CXX_SYSTEM_HEADER)
#define isascii(c) (((c) & ~0x7f) == 0)
#define toascii(c) ((c) & 0x7f)
#endif /* (!__cplusplus || __USE_CTYPE_MACROS) && !__CXX_SYSTEM_HEADER */

#endif /* __USE_MISC || __USE_XOPEN */


#endif /* __CC__ */

__SYSDECL_END

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CCTYPE 1
#undef _CTYPE_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CCTYPE */
#endif /* !_CTYPE_H */
