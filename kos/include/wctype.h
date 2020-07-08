/* HASH CRC-32:0x50af3ad0 */
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
#ifndef _WCTYPE_H
#define _WCTYPE_H 1

#ifdef _CXX_STDONLY_CWCTYPE
#ifdef __CXX_SYSTEM_HEADER
#undef _WCTYPE_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "wctype.h" after "cwctype" */
#ifndef __wint_t_defined
#define __wint_t_defined 1
__NAMESPACE_STD_USING(wint_t)
#endif /* !__wint_t_defined */
#ifndef __wctype_t_defined
#define __wctype_t_defined 1
__NAMESPACE_STD_USING(wctype_t)
#endif /* !__wctype_t_defined */
#if defined(__USE_ISOC99) || defined(__USE_XOPEN2K8)
#ifndef __wctrans_t_defined
#define __wctrans_t_defined 1
__NAMESPACE_STD_USING(wctrans_t)
#endif /* !__wctrans_t_defined */
#endif /* __USE_ISOC99 || __USE_XOPEN2K8 */
__NAMESPACE_STD_USING(iswalnum)
__NAMESPACE_STD_USING(iswalpha)
__NAMESPACE_STD_USING(iswcntrl)
__NAMESPACE_STD_USING(iswdigit)
__NAMESPACE_STD_USING(iswgraph)
__NAMESPACE_STD_USING(iswlower)
__NAMESPACE_STD_USING(iswprint)
__NAMESPACE_STD_USING(iswpunct)
__NAMESPACE_STD_USING(iswspace)
__NAMESPACE_STD_USING(iswupper)
__NAMESPACE_STD_USING(iswxdigit)
#if !defined(__wctrans_defined) && defined(__std_wctrans_defined)
#define __wctrans_defined 1
__NAMESPACE_STD_USING(wctrans)
#endif /* !__wctrans_defined && __std_wctrans_defined */
#if !defined(__towctrans_defined) && defined(__std_towctrans_defined)
#define __towctrans_defined 1
__NAMESPACE_STD_USING(towctrans)
#endif /* !__towctrans_defined && __std_towctrans_defined */
__NAMESPACE_STD_USING(wctype)
__NAMESPACE_STD_USING(iswctype)
#if !defined(__iswblank_defined) && defined(__std_iswblank_defined)
#define __iswblank_defined 1
__NAMESPACE_STD_USING(iswblank)
#endif /* !__iswblank_defined && __std_iswblank_defined */
__NAMESPACE_STD_USING(towlower)
__NAMESPACE_STD_USING(towupper)
#undef _CXX_STDONLY_CWCTYPE
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CWCTYPE */
#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/byteorder.h>
#include <hybrid/typecore.h>

#include <asm/crt/stdio.h> /* __WEOF */
#include <bits/types.h>

#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 || __USE_DOS */

__SYSDECL_BEGIN

#if !defined(WEOF) && defined(__WEOF)
#define WEOF __WEOF
#endif /* !WEOF && __WEOF */

#ifdef __CC__

__NAMESPACE_STD_BEGIN
#ifndef __std_wint_t_defined
#define __std_wint_t_defined 1
typedef __WINT_TYPE__ wint_t;
#endif /* !__std_wint_t_defined */
#ifndef __std_wctype_t_defined
#define __std_wctype_t_defined 1
typedef __WCTYPE_TYPE__ wctype_t;
#endif /* !__std_wctype_t_defined */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#ifndef __wint_t_defined
#define __wint_t_defined 1
__NAMESPACE_STD_USING(wint_t)
#endif /* !__wint_t_defined */
#ifndef __wctype_t_defined
#define __wctype_t_defined 1
__NAMESPACE_STD_USING(wctype_t)
#endif /* !__wctype_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __wchar_t_defined
#define __wchar_t_defined 1
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#ifndef ____wctrans_t_defined
#define ____wctrans_t_defined 1
#ifdef __DOS_COMPAT__
typedef wchar_t __wctrans_t;
#else /* __DOS_COMPAT__ */
typedef __int32_t const *__wctrans_t;
#endif /* !__DOS_COMPAT__ */
#endif /* !____wctrans_t_defined */

#if defined(__USE_ISOC99) || defined(__USE_XOPEN2K8)
#ifndef __std_wctrans_t_defined
#define __std_wctrans_t_defined 1
__NAMESPACE_STD_BEGIN
typedef __wctrans_t wctrans_t;
__NAMESPACE_STD_END
#endif /* !__std_wctrans_t_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __wctrans_t_defined
#define __wctrans_t_defined 1
__NAMESPACE_STD_USING(wctrans_t)
#endif /* !__wctrans_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_ISOC99 || __USE_XOPEN2K8 */


__NAMESPACE_STD_BEGIN
#if __has_builtin(__builtin_iswalnum) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswalnum)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswalnum,(wint_t __wc),{ return __builtin_iswalnum(__wc); })
#elif defined(__CRT_HAVE_iswalnum)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswalnum,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <local/wctype/iswalnum.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(iswalnum, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswalnum)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalnum))(__wc); })
#endif /* !... */
#if __has_builtin(__builtin_iswalpha) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswalpha)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswalpha,(wint_t __wc),{ return __builtin_iswalpha(__wc); })
#elif defined(__CRT_HAVE_iswalpha)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswalpha,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <local/wctype/iswalpha.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(iswalpha, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswalpha)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalpha))(__wc); })
#endif /* !... */
#if __has_builtin(__builtin_iswcntrl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswcntrl)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswcntrl,(wint_t __wc),{ return __builtin_iswcntrl(__wc); })
#elif defined(__CRT_HAVE_iswcntrl)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswcntrl,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <local/wctype/iswcntrl.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(iswcntrl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswcntrl)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswcntrl))(__wc); })
#endif /* !... */
#if __has_builtin(__builtin_iswdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswdigit)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswdigit,(wint_t __wc),{ return __builtin_iswdigit(__wc); })
#elif defined(__CRT_HAVE_iswdigit)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswdigit,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <local/wctype/iswdigit.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(iswdigit, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswdigit)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswdigit))(__wc); })
#endif /* !... */
#if __has_builtin(__builtin_iswgraph) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswgraph)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswgraph,(wint_t __wc),{ return __builtin_iswgraph(__wc); })
#elif defined(__CRT_HAVE_iswgraph)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswgraph,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <local/wctype/iswgraph.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(iswgraph, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswgraph)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswgraph))(__wc); })
#endif /* !... */
#if __has_builtin(__builtin_iswlower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswlower)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswlower,(wint_t __wc),{ return __builtin_iswlower(__wc); })
#elif defined(__CRT_HAVE_iswlower)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswlower,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <local/wctype/iswlower.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(iswlower, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswlower)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswlower))(__wc); })
#endif /* !... */
#if __has_builtin(__builtin_iswprint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswprint)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswprint,(wint_t __wc),{ return __builtin_iswprint(__wc); })
#elif defined(__CRT_HAVE_iswprint)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswprint,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <local/wctype/iswprint.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(iswprint, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswprint)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswprint))(__wc); })
#endif /* !... */
#if __has_builtin(__builtin_iswpunct) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswpunct)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswpunct,(wint_t __wc),{ return __builtin_iswpunct(__wc); })
#elif defined(__CRT_HAVE_iswpunct)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswpunct,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <local/wctype/iswpunct.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(iswpunct, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswpunct)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswpunct))(__wc); })
#endif /* !... */
#if __has_builtin(__builtin_iswspace) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswspace)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswspace,(wint_t __wc),{ return __builtin_iswspace(__wc); })
#elif defined(__CRT_HAVE_iswspace)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswspace,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <local/wctype/iswspace.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(iswspace, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswspace)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswspace))(__wc); })
#endif /* !... */
#if __has_builtin(__builtin_iswupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswupper)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswupper,(wint_t __wc),{ return __builtin_iswupper(__wc); })
#elif defined(__CRT_HAVE_iswupper)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswupper,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <local/wctype/iswupper.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(iswupper, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswupper)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswupper))(__wc); })
#endif /* !... */
#if __has_builtin(__builtin_iswxdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswxdigit)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswxdigit,(wint_t __wc),{ return __builtin_iswxdigit(__wc); })
#elif defined(__CRT_HAVE_iswxdigit)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswxdigit,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <local/wctype/iswxdigit.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(iswxdigit, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswxdigit)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswxdigit))(__wc); })
#endif /* !... */
#ifdef __USE_ISOC99
#ifndef __std_wctrans_defined
#define __std_wctrans_defined 1
#ifdef __wctrans_defined
__NAMESPACE_GLB_USING(wctrans)
#elif defined(__CRT_HAVE_wctrans)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wctrans_t,__NOTHROW_NCX,wctrans,(char const *__prop),(__prop))
#else /* ... */
__NAMESPACE_STD_END
#include <local/wctype/wctrans.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wctrans, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wctrans_t __NOTHROW_NCX(__LIBCCALL wctrans)(char const *__prop) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctrans))(__prop); })
#endif /* !... */
#endif /* !__std_wctrans_defined */
#ifndef __std_towctrans_defined
#define __std_towctrans_defined 1
#ifdef __towctrans_defined
__NAMESPACE_GLB_USING(towctrans)
#elif defined(__CRT_HAVE_towctrans)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,wint_t,__NOTHROW_NCX,towctrans,(wint_t __wc, wctrans_t __desc),(__wc,__desc))
#elif defined(__CRT_HAVE___towctrans)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint_t,__NOTHROW_NCX,towctrans,(wint_t __wc, wctrans_t __desc),__towctrans,(__wc,__desc))
#else /* ... */
__NAMESPACE_STD_END
#include <local/wctype/towctrans.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(towctrans, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint_t __NOTHROW_NCX(__LIBCCALL towctrans)(wint_t __wc, wctrans_t __desc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towctrans))(__wc, __desc); })
#endif /* !... */
#endif /* !__std_towctrans_defined */
#endif /* __USE_ISOC99 */
#ifdef __CRT_HAVE_wctype
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wctype_t,__NOTHROW_NCX,wctype,(char const *__prop),(__prop))
#else /* __CRT_HAVE_wctype */
__NAMESPACE_STD_END
#include <local/wctype/wctype.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wctype, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wctype_t __NOTHROW_NCX(__LIBCCALL wctype)(char const *__prop) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctype))(__prop); })
#endif /* !__CRT_HAVE_wctype */
#ifdef __CRT_HAVE_iswctype
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,iswctype,(wint_t __wc, wctype_t __desc),(__wc,__desc))
#elif defined(__CRT_HAVE_is_wctype)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,iswctype,(wint_t __wc, wctype_t __desc),is_wctype,(__wc,__desc))
#elif defined(__CRT_HAVE___iswctype)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,iswctype,(wint_t __wc, wctype_t __desc),__iswctype,(__wc,__desc))
#else /* ... */
__NAMESPACE_STD_END
#include <local/wctype/iswctype.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(iswctype, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswctype)(wint_t __wc, wctype_t __desc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswctype))(__wc, __desc); })
#endif /* !... */
#ifdef __USE_ISOC99
#ifndef __std_iswblank_defined
#define __std_iswblank_defined 1
#ifdef __iswblank_defined
__NAMESPACE_GLB_USING(iswblank)
#elif __has_builtin(__builtin_iswblank) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswblank)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswblank,(wint_t __wc),{ return __builtin_iswblank(__wc); })
#elif defined(__CRT_HAVE_iswblank)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswblank,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <local/wctype/iswblank.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(iswblank, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswblank)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswblank))(__wc); })
#endif /* !... */
#endif /* !__std_iswblank_defined */
#endif /* __USE_ISOC99 */
#if __has_builtin(__builtin_towlower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_towlower)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,wint_t,__NOTHROW,towlower,(wint_t __wc),{ return __builtin_towlower(__wc); })
#elif defined(__CRT_HAVE_towlower)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,wint_t,__NOTHROW,towlower,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <local/wctype/towlower.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(towlower, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint_t __NOTHROW(__LIBCCALL towlower)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towlower))(__wc); })
#endif /* !... */
#if __has_builtin(__builtin_towupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_towupper)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,wint_t,__NOTHROW,towupper,(wint_t __wc),{ return __builtin_towupper(__wc); })
#elif defined(__CRT_HAVE_towupper)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,wint_t,__NOTHROW,towupper,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <local/wctype/towupper.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(towupper, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint_t __NOTHROW(__LIBCCALL towupper)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towupper))(__wc); })
#endif /* !... */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(iswalnum)
__NAMESPACE_STD_USING(iswalpha)
__NAMESPACE_STD_USING(iswcntrl)
__NAMESPACE_STD_USING(iswdigit)
__NAMESPACE_STD_USING(iswgraph)
__NAMESPACE_STD_USING(iswlower)
__NAMESPACE_STD_USING(iswprint)
__NAMESPACE_STD_USING(iswpunct)
__NAMESPACE_STD_USING(iswspace)
__NAMESPACE_STD_USING(iswupper)
__NAMESPACE_STD_USING(iswxdigit)
#if !defined(__wctrans_defined) && defined(__std_wctrans_defined)
#define __wctrans_defined 1
__NAMESPACE_STD_USING(wctrans)
#endif /* !__wctrans_defined && __std_wctrans_defined */
#if !defined(__towctrans_defined) && defined(__std_towctrans_defined)
#define __towctrans_defined 1
__NAMESPACE_STD_USING(towctrans)
#endif /* !__towctrans_defined && __std_towctrans_defined */
__NAMESPACE_STD_USING(wctype)
__NAMESPACE_STD_USING(iswctype)
#if !defined(__iswblank_defined) && defined(__std_iswblank_defined)
#define __iswblank_defined 1
__NAMESPACE_STD_USING(iswblank)
#endif /* !__iswblank_defined && __std_iswblank_defined */
__NAMESPACE_STD_USING(towlower)
__NAMESPACE_STD_USING(towupper)
#endif /* !__CXX_SYSTEM_HEADER */

#if defined(__USE_KOS) || defined(__USE_DOS)
#ifdef __CRT_HAVE_iswascii
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswascii,(__WINT_TYPE__ __wc),(__wc))
#else /* __CRT_HAVE_iswascii */
#include <local/wctype/iswascii.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(iswascii, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswascii)(__WINT_TYPE__ __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswascii))(__wc); })
#endif /* !__CRT_HAVE_iswascii */
#endif /* __USE_KOS || __USE_DOS */

#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_iswalnum_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswalnum_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE__iswalnum_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswalnum_l,(__WINT_TYPE__ __wc, __locale_t __locale),_iswalnum_l,(__wc,__locale))
#elif defined(__CRT_HAVE___iswalnum_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswalnum_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswalnum_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswalnum_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(iswalnum_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswalnum_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalnum_l))(__wc, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_iswalpha_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswalpha_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE__iswalpha_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswalpha_l,(__WINT_TYPE__ __wc, __locale_t __locale),_iswalpha_l,(__wc,__locale))
#elif defined(__CRT_HAVE___iswalpha_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswalpha_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswalpha_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswalpha_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(iswalpha_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswalpha_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalpha_l))(__wc, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_iswcntrl_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswcntrl_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE__iswcntrl_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswcntrl_l,(__WINT_TYPE__ __wc, __locale_t __locale),_iswcntrl_l,(__wc,__locale))
#elif defined(__CRT_HAVE___iswcntrl_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswcntrl_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswcntrl_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswcntrl_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(iswcntrl_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswcntrl_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswcntrl_l))(__wc, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_iswdigit_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswdigit_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE__iswdigit_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswdigit_l,(__WINT_TYPE__ __wc, __locale_t __locale),_iswdigit_l,(__wc,__locale))
#elif defined(__CRT_HAVE___iswdigit_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswdigit_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswdigit_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswdigit_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(iswdigit_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswdigit_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswdigit_l))(__wc, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_iswgraph_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswgraph_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE__iswgraph_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswgraph_l,(__WINT_TYPE__ __wc, __locale_t __locale),_iswgraph_l,(__wc,__locale))
#elif defined(__CRT_HAVE___iswgraph_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswgraph_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswgraph_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswgraph_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(iswgraph_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswgraph_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswgraph_l))(__wc, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_iswlower_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE__iswlower_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),_iswlower_l,(__wc,__locale))
#elif defined(__CRT_HAVE___iswlower_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswlower_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswlower_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(iswlower_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswlower_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswlower_l))(__wc, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_iswprint_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswprint_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE__iswprint_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswprint_l,(__WINT_TYPE__ __wc, __locale_t __locale),_iswprint_l,(__wc,__locale))
#elif defined(__CRT_HAVE___iswprint_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswprint_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswprint_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswprint_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(iswprint_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswprint_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswprint_l))(__wc, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_iswpunct_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswpunct_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE__iswpunct_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswpunct_l,(__WINT_TYPE__ __wc, __locale_t __locale),_iswpunct_l,(__wc,__locale))
#elif defined(__CRT_HAVE___iswpunct_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswpunct_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswpunct_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswpunct_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(iswpunct_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswpunct_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswpunct_l))(__wc, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_iswspace_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswspace_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE__iswspace_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswspace_l,(__WINT_TYPE__ __wc, __locale_t __locale),_iswspace_l,(__wc,__locale))
#elif defined(__CRT_HAVE___iswspace_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswspace_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswspace_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswspace_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(iswspace_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswspace_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswspace_l))(__wc, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_iswupper_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswupper_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE__iswupper_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswupper_l,(__WINT_TYPE__ __wc, __locale_t __locale),_iswupper_l,(__wc,__locale))
#elif defined(__CRT_HAVE___iswupper_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswupper_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswupper_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswupper_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(iswupper_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswupper_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswupper_l))(__wc, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_iswxdigit_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswxdigit_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE__iswxdigit_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswxdigit_l,(__WINT_TYPE__ __wc, __locale_t __locale),_iswxdigit_l,(__wc,__locale))
#elif defined(__CRT_HAVE___iswxdigit_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswxdigit_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswxdigit_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswxdigit_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(iswxdigit_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswxdigit_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswxdigit_l))(__wc, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_iswblank_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswblank_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE__iswblank_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswblank_l,(__WINT_TYPE__ __wc, __locale_t __locale),_iswblank_l,(__wc,__locale))
#elif defined(__CRT_HAVE___iswblank_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswblank_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswblank_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswblank_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(iswblank_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswblank_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswblank_l))(__wc, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_iswctype_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswctype_l,(__WINT_TYPE__ __wc, __WCTYPE_TYPE__ __type, __locale_t __locale),(__wc,__type,__locale))
#elif defined(__CRT_HAVE__iswctype_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswctype_l,(__WINT_TYPE__ __wc, __WCTYPE_TYPE__ __type, __locale_t __locale),_iswctype_l,(__wc,__type,__locale))
#elif defined(__CRT_HAVE___iswctype_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswctype_l,(__WINT_TYPE__ __wc, __WCTYPE_TYPE__ __type, __locale_t __locale),__iswctype_l,(__wc,__type,__locale))
#else /* ... */
#include <local/wctype/iswctype_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(iswctype_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswctype_l)(__WINT_TYPE__ __wc, __WCTYPE_TYPE__ __type, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswctype_l))(__wc, __type, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_towupper_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towupper_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE__towupper_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towupper_l,(__WINT_TYPE__ __wc, __locale_t __locale),_towupper_l,(__wc,__locale))
#elif defined(__CRT_HAVE___towupper_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towupper_l,(__WINT_TYPE__ __wc, __locale_t __locale),__towupper_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/towupper_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(towupper_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL towupper_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towupper_l))(__wc, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_towlower_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE__towlower_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),_towlower_l,(__wc,__locale))
#elif defined(__CRT_HAVE___towlower_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),__towlower_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/towlower_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(towlower_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL towlower_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towlower_l))(__wc, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wctype_l
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__WCTYPE_TYPE__,__NOTHROW_NCX,wctype_l,(char const *__prop, __locale_t __locale),(__prop,__locale))
#elif defined(__CRT_HAVE___wctype_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__WCTYPE_TYPE__,__NOTHROW_NCX,wctype_l,(char const *__prop, __locale_t __locale),__wctype_l,(__prop,__locale))
#else /* ... */
#include <local/wctype/wctype_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wctype_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __WCTYPE_TYPE__ __NOTHROW_NCX(__LIBCCALL wctype_l)(char const *__prop, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctype_l))(__prop, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wctrans_l
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__wctrans_t,__NOTHROW_NCX,wctrans_l,(char const *__prop, __locale_t __locale),(__prop,__locale))
#elif defined(__CRT_HAVE___wctrans_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__wctrans_t,__NOTHROW_NCX,wctrans_l,(char const *__prop, __locale_t __locale),__wctrans_l,(__prop,__locale))
#else /* ... */
#include <local/wctype/wctrans_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wctrans_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __wctrans_t __NOTHROW_NCX(__LIBCCALL wctrans_l)(char const *__prop, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctrans_l))(__prop, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_towctrans_l
__CDECLARE(__ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towctrans_l,(__WINT_TYPE__ __wc, __wctrans_t __desc, __locale_t __locale),(__wc,__desc,__locale))
#elif defined(__CRT_HAVE___towctrans_l)
__CREDIRECT(__ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towctrans_l,(__WINT_TYPE__ __wc, __wctrans_t __desc, __locale_t __locale),__towctrans_l,(__wc,__desc,__locale))
#else /* ... */
#include <local/wctype/towctrans_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(towctrans_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL towctrans_l)(__WINT_TYPE__ __wc, __wctrans_t __desc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towctrans_l))(__wc, __desc, __locale); })
#endif /* !... */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_DOS
#ifndef __wctype_t_defined
#define __wctype_t_defined 1
__NAMESPACE_STD_USING(wctype_t)
#endif /* !__wctype_t_defined */
#ifndef _WCTYPE_DEFINED
#define _WCTYPE_DEFINED 1
#ifdef __CRT_HAVE_iswalnum_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswalnum_l,(__WINT_TYPE__ __wc, __locale_t __locale),iswalnum_l,(__wc,__locale))
#elif defined(__CRT_HAVE__iswalnum_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswalnum_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE___iswalnum_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswalnum_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswalnum_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswalnum_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswalnum_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalnum_l))(__wc, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_iswalpha_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswalpha_l,(__WINT_TYPE__ __wc, __locale_t __locale),iswalpha_l,(__wc,__locale))
#elif defined(__CRT_HAVE__iswalpha_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswalpha_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE___iswalpha_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswalpha_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswalpha_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswalpha_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswalpha_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalpha_l))(__wc, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_iswcntrl_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswcntrl_l,(__WINT_TYPE__ __wc, __locale_t __locale),iswcntrl_l,(__wc,__locale))
#elif defined(__CRT_HAVE__iswcntrl_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswcntrl_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE___iswcntrl_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswcntrl_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswcntrl_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswcntrl_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswcntrl_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswcntrl_l))(__wc, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_iswdigit_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswdigit_l,(__WINT_TYPE__ __wc, __locale_t __locale),iswdigit_l,(__wc,__locale))
#elif defined(__CRT_HAVE__iswdigit_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswdigit_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE___iswdigit_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswdigit_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswdigit_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswdigit_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswdigit_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswdigit_l))(__wc, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_iswgraph_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswgraph_l,(__WINT_TYPE__ __wc, __locale_t __locale),iswgraph_l,(__wc,__locale))
#elif defined(__CRT_HAVE__iswgraph_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswgraph_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE___iswgraph_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswgraph_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswgraph_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswgraph_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswgraph_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswgraph_l))(__wc, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_iswlower_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),iswlower_l,(__wc,__locale))
#elif defined(__CRT_HAVE__iswlower_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE___iswlower_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswlower_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswlower_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswlower_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswlower_l))(__wc, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_iswprint_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswprint_l,(__WINT_TYPE__ __wc, __locale_t __locale),iswprint_l,(__wc,__locale))
#elif defined(__CRT_HAVE__iswprint_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswprint_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE___iswprint_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswprint_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswprint_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswprint_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswprint_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswprint_l))(__wc, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_iswpunct_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswpunct_l,(__WINT_TYPE__ __wc, __locale_t __locale),iswpunct_l,(__wc,__locale))
#elif defined(__CRT_HAVE__iswpunct_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswpunct_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE___iswpunct_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswpunct_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswpunct_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswpunct_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswpunct_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswpunct_l))(__wc, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_iswspace_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswspace_l,(__WINT_TYPE__ __wc, __locale_t __locale),iswspace_l,(__wc,__locale))
#elif defined(__CRT_HAVE__iswspace_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswspace_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE___iswspace_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswspace_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswspace_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswspace_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswspace_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswspace_l))(__wc, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_iswupper_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswupper_l,(__WINT_TYPE__ __wc, __locale_t __locale),iswupper_l,(__wc,__locale))
#elif defined(__CRT_HAVE__iswupper_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswupper_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE___iswupper_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswupper_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswupper_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswupper_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswupper_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswupper_l))(__wc, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_iswxdigit_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswxdigit_l,(__WINT_TYPE__ __wc, __locale_t __locale),iswxdigit_l,(__wc,__locale))
#elif defined(__CRT_HAVE__iswxdigit_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswxdigit_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE___iswxdigit_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswxdigit_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswxdigit_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswxdigit_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswxdigit_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswxdigit_l))(__wc, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_iswblank_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswblank_l,(__WINT_TYPE__ __wc, __locale_t __locale),iswblank_l,(__wc,__locale))
#elif defined(__CRT_HAVE__iswblank_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswblank_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE___iswblank_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswblank_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswblank_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/iswblank_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswblank_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswblank_l))(__wc, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_towupper_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,_towupper_l,(__WINT_TYPE__ __wc, __locale_t __locale),towupper_l,(__wc,__locale))
#elif defined(__CRT_HAVE__towupper_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,_towupper_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE___towupper_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,_towupper_l,(__WINT_TYPE__ __wc, __locale_t __locale),__towupper_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/towupper_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL _towupper_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towupper_l))(__wc, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_towlower_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,_towlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),towlower_l,(__wc,__locale))
#elif defined(__CRT_HAVE__towlower_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,_towlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#elif defined(__CRT_HAVE___towlower_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,_towlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),__towlower_l,(__wc,__locale))
#else /* ... */
#include <local/wctype/towlower_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL _towlower_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towlower_l))(__wc, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_iswctype_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswctype_l,(__WINT_TYPE__ __wc, __WCTYPE_TYPE__ __type, __locale_t __locale),iswctype_l,(__wc,__type,__locale))
#elif defined(__CRT_HAVE__iswctype_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswctype_l,(__WINT_TYPE__ __wc, __WCTYPE_TYPE__ __type, __locale_t __locale),(__wc,__type,__locale))
#elif defined(__CRT_HAVE___iswctype_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswctype_l,(__WINT_TYPE__ __wc, __WCTYPE_TYPE__ __type, __locale_t __locale),__iswctype_l,(__wc,__type,__locale))
#else /* ... */
#include <local/wctype/iswctype_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswctype_l)(__WINT_TYPE__ __wc, __WCTYPE_TYPE__ __type, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswctype_l))(__wc, __type, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_iswctype
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,is_wctype,(wint_t __wc, wctype_t __desc),iswctype,(__wc,__desc))
#elif defined(__CRT_HAVE_is_wctype)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,is_wctype,(wint_t __wc, wctype_t __desc),(__wc,__desc))
#elif defined(__CRT_HAVE___iswctype)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,is_wctype,(wint_t __wc, wctype_t __desc),__iswctype,(__wc,__desc))
#else /* ... */
#include <local/wctype/iswctype.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL is_wctype)(wint_t __wc, wctype_t __desc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswctype))(__wc, __desc); }
#endif /* !... */

#ifdef __CRT_HAVE_isleadbyte
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,isleadbyte,(int __wc),(__wc))
#else /* __CRT_HAVE_isleadbyte */
#include <local/wctype/isleadbyte.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(isleadbyte, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isleadbyte)(int __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isleadbyte))(__wc); })
#endif /* !__CRT_HAVE_isleadbyte */
#ifdef __CRT_HAVE__isleadbyte_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isleadbyte_l,(int __wc, __locale_t __locale),(__wc,__locale))
#else /* __CRT_HAVE__isleadbyte_l */
#include <local/wctype/_isleadbyte_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_isleadbyte_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isleadbyte_l)(int __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_isleadbyte_l))(__wc, __locale); })
#endif /* !__CRT_HAVE__isleadbyte_l */
#ifdef __CRT_HAVE___iswcsymf
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__iswcsymf,(__WINT_TYPE__ __wc),(__wc))
#else /* __CRT_HAVE___iswcsymf */
#include <local/wctype/__iswcsymf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__iswcsymf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL __iswcsymf)(__WINT_TYPE__ __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__iswcsymf))(__wc); })
#endif /* !__CRT_HAVE___iswcsymf */
#ifdef __CRT_HAVE___iswcsym
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__iswcsym,(__WINT_TYPE__ __wc),(__wc))
#else /* __CRT_HAVE___iswcsym */
#include <local/wctype/__iswcsym.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__iswcsym, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL __iswcsym)(__WINT_TYPE__ __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__iswcsym))(__wc); })
#endif /* !__CRT_HAVE___iswcsym */

#ifdef __CRT_HAVE__iswcsymf_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswcsymf_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#else /* __CRT_HAVE__iswcsymf_l */
#include <local/wctype/_iswcsymf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_iswcsymf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswcsymf_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_iswcsymf_l))(__wc, __locale); })
#endif /* !__CRT_HAVE__iswcsymf_l */
#ifdef __CRT_HAVE__iswcsym_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswcsym_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#else /* __CRT_HAVE__iswcsym_l */
#include <local/wctype/_iswcsym_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_iswcsym_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswcsym_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_iswcsym_l))(__wc, __locale); })
#endif /* !__CRT_HAVE__iswcsym_l */
#endif /* !_WCTYPE_DEFINED */
#endif /* __USE_DOS */

#endif /* __CC__ */

__SYSDECL_END

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CWCTYPE 1
#undef _WCTYPE_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CWCTYPE */
#endif /* !_WCTYPE_H */
