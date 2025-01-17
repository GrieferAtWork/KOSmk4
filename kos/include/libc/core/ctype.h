/* HASH CRC-32:0x64d3e2f0 */
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
#ifndef _LIBC_CORE_CTYPE_H
#define _LIBC_CORE_CTYPE_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#include <bits/crt/ctype.h>
#if defined(__crt_iscntrl) && defined(__CRT_HAVE_iscntrl)
/* >> iscntrl(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_iscntrl,(int __ch),iscntrl,{ return __crt_iscntrl(__ch); })
#elif defined(__crt_iscntrl)
/* >> iscntrl(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_core_iscntrl)(int __ch) { return __crt_iscntrl(__ch); }
#elif __has_builtin(__builtin_iscntrl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iscntrl)
/* >> iscntrl(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_iscntrl,(int __ch),iscntrl,{ return __builtin_iscntrl(__ch); })
#elif defined(__CRT_HAVE_iscntrl)
/* >> iscntrl(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_iscntrl,(int __ch),iscntrl,(__ch))
#else /* ... */
#include <libc/local/ctype/iscntrl.h>
/* >> iscntrl(3) */
#define __libc_core_iscntrl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iscntrl)
#endif /* !... */
#if defined(__crt_isspace) && defined(__CRT_HAVE_isspace)
/* >> isspace(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isspace,(int __ch),isspace,{ return __crt_isspace(__ch); })
#elif defined(__crt_isspace)
/* >> isspace(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_core_isspace)(int __ch) { return __crt_isspace(__ch); }
#elif __has_builtin(__builtin_isspace) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isspace)
/* >> isspace(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isspace,(int __ch),isspace,{ return __builtin_isspace(__ch); })
#elif defined(__CRT_HAVE_isspace)
/* >> isspace(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isspace,(int __ch),isspace,(__ch))
#else /* ... */
#include <libc/local/ctype/isspace.h>
/* >> isspace(3) */
#define __libc_core_isspace __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isspace)
#endif /* !... */
#if defined(__crt_isupper) && defined(__CRT_HAVE_isupper)
/* >> isupper(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isupper,(int __ch),isupper,{ return __crt_isupper(__ch); })
#elif defined(__crt_isupper)
/* >> isupper(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_core_isupper)(int __ch) { return __crt_isupper(__ch); }
#elif __has_builtin(__builtin_isupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isupper)
/* >> isupper(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isupper,(int __ch),isupper,{ return __builtin_isupper(__ch); })
#elif defined(__CRT_HAVE_isupper)
/* >> isupper(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isupper,(int __ch),isupper,(__ch))
#else /* ... */
#include <libc/local/ctype/isupper.h>
/* >> isupper(3) */
#define __libc_core_isupper __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isupper)
#endif /* !... */
#if defined(__crt_islower) && defined(__CRT_HAVE_islower)
/* >> islower(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_islower,(int __ch),islower,{ return __crt_islower(__ch); })
#elif defined(__crt_islower)
/* >> islower(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_core_islower)(int __ch) { return __crt_islower(__ch); }
#elif __has_builtin(__builtin_islower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_islower)
/* >> islower(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_islower,(int __ch),islower,{ return __builtin_islower(__ch); })
#elif defined(__CRT_HAVE_islower)
/* >> islower(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_islower,(int __ch),islower,(__ch))
#else /* ... */
#include <libc/local/ctype/islower.h>
/* >> islower(3) */
#define __libc_core_islower __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(islower)
#endif /* !... */
#if defined(__crt_isalpha) && defined(__CRT_HAVE_isalpha)
/* >> isalpha(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isalpha,(int __ch),isalpha,{ return __crt_isalpha(__ch); })
#elif defined(__crt_isalpha)
/* >> isalpha(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_core_isalpha)(int __ch) { return __crt_isalpha(__ch); }
#elif __has_builtin(__builtin_isalpha) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isalpha)
/* >> isalpha(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isalpha,(int __ch),isalpha,{ return __builtin_isalpha(__ch); })
#elif defined(__CRT_HAVE_isalpha)
/* >> isalpha(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isalpha,(int __ch),isalpha,(__ch))
#else /* ... */
#include <libc/local/ctype/isalpha.h>
/* >> isalpha(3) */
#define __libc_core_isalpha __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalpha)
#endif /* !... */
#if defined(__crt_isdigit) && defined(__CRT_HAVE_isdigit)
/* >> isdigit(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isdigit,(int __ch),isdigit,{ return __crt_isdigit(__ch); })
#elif defined(__crt_isdigit)
/* >> isdigit(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_core_isdigit)(int __ch) { return __crt_isdigit(__ch); }
#elif __has_builtin(__builtin_isdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isdigit)
/* >> isdigit(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isdigit,(int __ch),isdigit,{ return __builtin_isdigit(__ch); })
#elif defined(__CRT_HAVE_isdigit)
/* >> isdigit(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isdigit,(int __ch),isdigit,(__ch))
#else /* ... */
#include <libc/local/ctype/isdigit.h>
/* >> isdigit(3) */
#define __libc_core_isdigit __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isdigit)
#endif /* !... */
#if defined(__crt_isxdigit) && defined(__CRT_HAVE_isxdigit)
/* >> isxdigit(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isxdigit,(int __ch),isxdigit,{ return __crt_isxdigit(__ch); })
#elif defined(__crt_isxdigit)
/* >> isxdigit(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_core_isxdigit)(int __ch) { return __crt_isxdigit(__ch); }
#elif __has_builtin(__builtin_isxdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isxdigit)
/* >> isxdigit(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isxdigit,(int __ch),isxdigit,{ return __builtin_isxdigit(__ch); })
#elif defined(__CRT_HAVE_isxdigit)
/* >> isxdigit(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isxdigit,(int __ch),isxdigit,(__ch))
#else /* ... */
#include <libc/local/ctype/isxdigit.h>
/* >> isxdigit(3) */
#define __libc_core_isxdigit __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isxdigit)
#endif /* !... */
#if defined(__crt_isalnum) && defined(__CRT_HAVE_isalnum)
/* >> isalnum(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isalnum,(int __ch),isalnum,{ return __crt_isalnum(__ch); })
#elif defined(__crt_isalnum)
/* >> isalnum(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_core_isalnum)(int __ch) { return __crt_isalnum(__ch); }
#elif __has_builtin(__builtin_isalnum) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isalnum)
/* >> isalnum(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isalnum,(int __ch),isalnum,{ return __builtin_isalnum(__ch); })
#elif defined(__CRT_HAVE_isalnum)
/* >> isalnum(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isalnum,(int __ch),isalnum,(__ch))
#else /* ... */
#include <libc/local/ctype/isalnum.h>
/* >> isalnum(3) */
#define __libc_core_isalnum __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalnum)
#endif /* !... */
#if defined(__crt_ispunct) && defined(__CRT_HAVE_ispunct)
/* >> ispunct(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_ispunct,(int __ch),ispunct,{ return __crt_ispunct(__ch); })
#elif defined(__crt_ispunct)
/* >> ispunct(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_core_ispunct)(int __ch) { return __crt_ispunct(__ch); }
#elif __has_builtin(__builtin_ispunct) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ispunct)
/* >> ispunct(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_ispunct,(int __ch),ispunct,{ return __builtin_ispunct(__ch); })
#elif defined(__CRT_HAVE_ispunct)
/* >> ispunct(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_ispunct,(int __ch),ispunct,(__ch))
#else /* ... */
#include <libc/local/ctype/ispunct.h>
/* >> ispunct(3) */
#define __libc_core_ispunct __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ispunct)
#endif /* !... */
#if defined(__crt_isgraph) && defined(__CRT_HAVE_isgraph)
/* >> isgraph(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isgraph,(int __ch),isgraph,{ return __crt_isgraph(__ch); })
#elif defined(__crt_isgraph)
/* >> isgraph(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_core_isgraph)(int __ch) { return __crt_isgraph(__ch); }
#elif __has_builtin(__builtin_isgraph) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isgraph)
/* >> isgraph(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isgraph,(int __ch),isgraph,{ return __builtin_isgraph(__ch); })
#elif defined(__CRT_HAVE_isgraph)
/* >> isgraph(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isgraph,(int __ch),isgraph,(__ch))
#else /* ... */
#include <libc/local/ctype/isgraph.h>
/* >> isgraph(3) */
#define __libc_core_isgraph __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isgraph)
#endif /* !... */
#if defined(__crt_isprint) && defined(__CRT_HAVE_isprint)
/* >> isprint(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isprint,(int __ch),isprint,{ return __crt_isprint(__ch); })
#elif defined(__crt_isprint)
/* >> isprint(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_core_isprint)(int __ch) { return __crt_isprint(__ch); }
#elif __has_builtin(__builtin_isprint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isprint)
/* >> isprint(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isprint,(int __ch),isprint,{ return __builtin_isprint(__ch); })
#elif defined(__CRT_HAVE_isprint)
/* >> isprint(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isprint,(int __ch),isprint,(__ch))
#else /* ... */
#include <libc/local/ctype/isprint.h>
/* >> isprint(3) */
#define __libc_core_isprint __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isprint)
#endif /* !... */
#if defined(__crt_tolower) && defined(__CRT_HAVE_tolower)
/* >> tolower(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_tolower,(int __ch),tolower,{ return __crt_tolower(__ch); })
#elif defined(__crt_tolower)
/* >> tolower(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_core_tolower)(int __ch) { return __crt_tolower(__ch); }
#elif __has_builtin(__builtin_tolower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tolower)
/* >> tolower(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_tolower,(int __ch),tolower,{ return __builtin_tolower(__ch); })
#elif defined(__CRT_HAVE_tolower)
/* >> tolower(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_tolower,(int __ch),tolower,(__ch))
#else /* ... */
#include <libc/local/ctype/tolower.h>
/* >> tolower(3) */
#define __libc_core_tolower __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tolower)
#endif /* !... */
#if defined(__crt_toupper) && defined(__CRT_HAVE_toupper)
/* >> toupper(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_toupper,(int __ch),toupper,{ return __crt_toupper(__ch); })
#elif defined(__crt_toupper)
/* >> toupper(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_core_toupper)(int __ch) { return __crt_toupper(__ch); }
#elif __has_builtin(__builtin_toupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_toupper)
/* >> toupper(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_toupper,(int __ch),toupper,{ return __builtin_toupper(__ch); })
#elif defined(__CRT_HAVE_toupper)
/* >> toupper(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_toupper,(int __ch),toupper,(__ch))
#else /* ... */
#include <libc/local/ctype/toupper.h>
/* >> toupper(3) */
#define __libc_core_toupper __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(toupper)
#endif /* !... */
#if defined(__crt_isblank) && defined(__CRT_HAVE_isblank)
/* >> isblank(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isblank,(int __ch),isblank,{ return __crt_isblank(__ch); })
#elif defined(__crt_isblank)
/* >> isblank(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_core_isblank)(int __ch) { return __crt_isblank(__ch); }
#elif __has_builtin(__builtin_isblank) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isblank)
/* >> isblank(3) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isblank,(int __ch),isblank,{ return __builtin_isblank(__ch); })
#elif defined(__CRT_HAVE_isblank)
/* >> isblank(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_core_isblank,(int __ch),isblank,(__ch))
#else /* ... */
#include <libc/local/ctype/isblank.h>
/* >> isblank(3) */
#define __libc_core_isblank __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isblank)
#endif /* !... */

__SYSDECL_END

#endif /* __CC__ */

#endif /* !_LIBC_CORE_CTYPE_H */
