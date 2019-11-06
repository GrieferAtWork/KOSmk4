/* HASH CRC-32:0xfb19c1db */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBC_SLOW_CTYPE_H
#define _LIBC_SLOW_CTYPE_H 1

#include <__stdinc.h>
#include <__crt.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#ifndef ____libc_slow_iscntrl_defined
#define ____libc_slow_iscntrl_defined 1
#if __has_builtin(__builtin_iscntrl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iscntrl)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_slow_iscntrl)(int __ch) { return __builtin_iscntrl(__ch); }
#elif defined(__CRT_HAVE_iscntrl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_slow_iscntrl,(int __ch),iscntrl,(__ch))
#else /* LIBC: iscntrl */
#include <local/ctype/iscntrl.h>
#define __libc_slow_iscntrl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iscntrl))
#endif /* iscntrl... */
#endif /* !____libc_slow_iscntrl_defined */
#ifndef ____libc_slow_isspace_defined
#define ____libc_slow_isspace_defined 1
#if __has_builtin(__builtin_isspace) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isspace)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_slow_isspace)(int __ch) { return __builtin_isspace(__ch); }
#elif defined(__CRT_HAVE_isspace)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_slow_isspace,(int __ch),isspace,(__ch))
#else /* LIBC: isspace */
#include <local/ctype/isspace.h>
#define __libc_slow_isspace (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isspace))
#endif /* isspace... */
#endif /* !____libc_slow_isspace_defined */
#ifndef ____libc_slow_isupper_defined
#define ____libc_slow_isupper_defined 1
#if __has_builtin(__builtin_isupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isupper)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_slow_isupper)(int __ch) { return __builtin_isupper(__ch); }
#elif defined(__CRT_HAVE_isupper)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_slow_isupper,(int __ch),isupper,(__ch))
#else /* LIBC: isupper */
#include <local/ctype/isupper.h>
#define __libc_slow_isupper (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isupper))
#endif /* isupper... */
#endif /* !____libc_slow_isupper_defined */
#ifndef ____libc_slow_islower_defined
#define ____libc_slow_islower_defined 1
#if __has_builtin(__builtin_islower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_islower)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_slow_islower)(int __ch) { return __builtin_islower(__ch); }
#elif defined(__CRT_HAVE_islower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_slow_islower,(int __ch),islower,(__ch))
#else /* LIBC: islower */
#include <local/ctype/islower.h>
#define __libc_slow_islower (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(islower))
#endif /* islower... */
#endif /* !____libc_slow_islower_defined */
#ifndef ____libc_slow_isalpha_defined
#define ____libc_slow_isalpha_defined 1
#if __has_builtin(__builtin_isalpha) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isalpha)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_slow_isalpha)(int __ch) { return __builtin_isalpha(__ch); }
#elif defined(__CRT_HAVE_isalpha)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_slow_isalpha,(int __ch),isalpha,(__ch))
#else /* LIBC: isalpha */
#include <local/ctype/isalpha.h>
#define __libc_slow_isalpha (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalpha))
#endif /* isalpha... */
#endif /* !____libc_slow_isalpha_defined */
#ifndef ____libc_slow_isdigit_defined
#define ____libc_slow_isdigit_defined 1
#if __has_builtin(__builtin_isdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isdigit)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_slow_isdigit)(int __ch) { return __builtin_isdigit(__ch); }
#elif defined(__CRT_HAVE_isdigit)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_slow_isdigit,(int __ch),isdigit,(__ch))
#else /* LIBC: isdigit */
#include <local/ctype/isdigit.h>
#define __libc_slow_isdigit (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isdigit))
#endif /* isdigit... */
#endif /* !____libc_slow_isdigit_defined */
#ifndef ____libc_slow_isxdigit_defined
#define ____libc_slow_isxdigit_defined 1
#if __has_builtin(__builtin_isxdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isxdigit)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_slow_isxdigit)(int __ch) { return __builtin_isxdigit(__ch); }
#elif defined(__CRT_HAVE_isxdigit)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_slow_isxdigit,(int __ch),isxdigit,(__ch))
#else /* LIBC: isxdigit */
#include <local/ctype/isxdigit.h>
#define __libc_slow_isxdigit (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isxdigit))
#endif /* isxdigit... */
#endif /* !____libc_slow_isxdigit_defined */
#ifndef ____libc_slow_isalnum_defined
#define ____libc_slow_isalnum_defined 1
#if __has_builtin(__builtin_isalnum) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isalnum)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_slow_isalnum)(int __ch) { return __builtin_isalnum(__ch); }
#elif defined(__CRT_HAVE_isalnum)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_slow_isalnum,(int __ch),isalnum,(__ch))
#else /* LIBC: isalnum */
#include <local/ctype/isalnum.h>
#define __libc_slow_isalnum (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalnum))
#endif /* isalnum... */
#endif /* !____libc_slow_isalnum_defined */
#ifndef ____libc_slow_ispunct_defined
#define ____libc_slow_ispunct_defined 1
#if __has_builtin(__builtin_ispunct) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ispunct)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_slow_ispunct)(int __ch) { return __builtin_ispunct(__ch); }
#elif defined(__CRT_HAVE_ispunct)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_slow_ispunct,(int __ch),ispunct,(__ch))
#else /* LIBC: ispunct */
#include <local/ctype/ispunct.h>
#define __libc_slow_ispunct (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ispunct))
#endif /* ispunct... */
#endif /* !____libc_slow_ispunct_defined */
#ifndef ____libc_slow_isgraph_defined
#define ____libc_slow_isgraph_defined 1
#if __has_builtin(__builtin_isgraph) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isgraph)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_slow_isgraph)(int __ch) { return __builtin_isgraph(__ch); }
#elif defined(__CRT_HAVE_isgraph)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_slow_isgraph,(int __ch),isgraph,(__ch))
#else /* LIBC: isgraph */
#include <local/ctype/isgraph.h>
#define __libc_slow_isgraph (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isgraph))
#endif /* isgraph... */
#endif /* !____libc_slow_isgraph_defined */
#ifndef ____libc_slow_isprint_defined
#define ____libc_slow_isprint_defined 1
#if __has_builtin(__builtin_isprint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isprint)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_slow_isprint)(int __ch) { return __builtin_isprint(__ch); }
#elif defined(__CRT_HAVE_isprint)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_slow_isprint,(int __ch),isprint,(__ch))
#else /* LIBC: isprint */
#include <local/ctype/isprint.h>
#define __libc_slow_isprint (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isprint))
#endif /* isprint... */
#endif /* !____libc_slow_isprint_defined */
#ifndef ____libc_slow_tolower_defined
#define ____libc_slow_tolower_defined 1
#if __has_builtin(__builtin_tolower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tolower)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_slow_tolower)(int __ch) { return __builtin_tolower(__ch); }
#elif defined(__CRT_HAVE_tolower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_slow_tolower,(int __ch),tolower,(__ch))
#elif defined(__CRT_HAVE__tolower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_slow_tolower,(int __ch),_tolower,(__ch))
#else /* LIBC: tolower */
#include <local/ctype/tolower.h>
#define __libc_slow_tolower (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tolower))
#endif /* tolower... */
#endif /* !____libc_slow_tolower_defined */
#ifndef ____libc_slow_toupper_defined
#define ____libc_slow_toupper_defined 1
#if __has_builtin(__builtin_toupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_toupper)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_slow_toupper)(int __ch) { return __builtin_toupper(__ch); }
#elif defined(__CRT_HAVE_toupper)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_slow_toupper,(int __ch),toupper,(__ch))
#elif defined(__CRT_HAVE__toupper)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_slow_toupper,(int __ch),_toupper,(__ch))
#else /* LIBC: toupper */
#include <local/ctype/toupper.h>
#define __libc_slow_toupper (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(toupper))
#endif /* toupper... */
#endif /* !____libc_slow_toupper_defined */
#ifndef ____libc_slow_isblank_defined
#define ____libc_slow_isblank_defined 1
#if __has_builtin(__builtin_isblank) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isblank)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_slow_isblank)(int __ch) { return __builtin_isblank(__ch); }
#elif defined(__CRT_HAVE_isblank)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__libc_slow_isblank,(int __ch),isblank,(__ch))
#else /* LIBC: isblank */
#include <local/ctype/isblank.h>
#define __libc_slow_isblank (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isblank))
#endif /* isblank... */
#endif /* !____libc_slow_isblank_defined */

__SYSDECL_END

#endif /* !_LIBC_SLOW_CTYPE_H */
