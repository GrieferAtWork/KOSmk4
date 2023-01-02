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
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/setjmp.h) */
/* (#) Portability: DJGPP         (/include/setjmp.h) */
/* (#) Portability: DragonFly BSD (/include/setjmp.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/setjmp.h) */
/* (#) Portability: FreeBSD       (/include/setjmp.h) */
/* (#) Portability: GNU C Library (/setjmp/setjmp.h) */
/* (#) Portability: GNU Hurd      (/usr/include/setjmp.h) */
/* (#) Portability: MSVC          (/include/setjmp.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/setjmp.h) */
/* (#) Portability: NetBSD        (/include/setjmp.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/setjmp.h) */
/* (#) Portability: OpenBSD       (/include/setjmp.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/setjmp.h) */
/* (#) Portability: avr-libc      (/include/setjmp.h) */
/* (#) Portability: diet libc     (/include/setjmp.h) */
/* (#) Portability: libc4/5       (/include/setjmp.h) */
/* (#) Portability: libc6         (/include/setjmp.h) */
/* (#) Portability: libcmini      (/include/setjmp.h) */
/* (#) Portability: mintlib       (/include/setjmp.h) */
/* (#) Portability: musl libc     (/include/setjmp.h) */
/* (#) Portability: uClibc        (/include/setjmp.h) */
#ifndef _SETJMP_H
#define _SETJMP_H 1

#ifdef _CXX_STDONLY_CSETJMP
#ifdef __CXX_SYSTEM_HEADER
#undef _SETJMP_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "ctype.h" after "cctype" */
#ifndef __jmp_buf_defined
#define __jmp_buf_defined
__NAMESPACE_STD_USING(jmp_buf)
#endif /* !__jmp_buf_defined */
#if defined(__std_setjmp_defined) && !defined(__setjmp_defined)
#define __setjmp_defined
__NAMESPACE_STD_USING(setjmp)
#endif /* __std_setjmp_defined && !__setjmp_defined */
#if defined(__std_longjmp_defined) && !defined(__longjmp_defined)
#define __longjmp_defined
__NAMESPACE_STD_USING(longjmp)
#endif /* __std_longjmp_defined && !__longjmp_defined */
#undef _CXX_STDONLY_CSETJMP
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CSETJMP */

#include "__stdinc.h"
#include "__crt.h"
/**/

#include <features.h>

#include <bits/crt/setjmp.h>
#include <bits/os/sigset.h>

__SYSDECL_BEGIN

#ifdef __CC__

__NAMESPACE_STD_BEGIN

#ifndef __std_jmp_buf_defined
#define __std_jmp_buf_defined
typedef struct __jmp_buf jmp_buf[1];
#endif /* !__std_jmp_buf_defined */

#ifndef __std_setjmp_defined
#define __std_setjmp_defined
#if defined(__setjmp_defined) && !defined(__COMPILER_HAVE_BUG_BLOATY_CXX_USING)
__NAMESPACE_GLB_USING(setjmp)
#elif defined(__CRT_HAVE_setjmp)
__CDECLARE(__ATTR_RETURNS_TWICE,int,__NOTHROW_NCX,setjmp,(jmp_buf __buf),(__buf))
#elif defined(__CRT_HAVE__setjmp)
__CREDIRECT(__ATTR_RETURNS_TWICE,int,__NOTHROW_NCX,setjmp,(jmp_buf __buf),_setjmp,(__buf))
#else /* ... */
#undef __std_setjmp_defined
#endif /* !... */
#endif /* !__std_setjmp_defined */

#ifndef __std_longjmp_defined
#define __std_longjmp_defined
#if defined(__longjmp_defined) && !defined(__COMPILER_HAVE_BUG_BLOATY_CXX_USING)
__NAMESPACE_GLB_USING(longjmp)
#elif defined(__CRT_HAVE_longjmp)
#if defined(__CRT_HAVE___fast_longjmp) && !defined(__NO_builtin_constant_p) && !defined(__NO_EXTERN_INLINE)
#ifdef __INTELLISENSE__
__ATTR_NORETURN void __NOTHROW_NCX(__LIBCCALL longjmp)(jmp_buf __buf, int __sig);
#else /* __INTELLISENSE__ */
__CDECLARE_VOID(__ATTR_NORETURN,__NOTHROW_NCX,__fast_longjmp,(jmp_buf __buf, int __sig),(__buf,__sig))
__CREDIRECT_VOID(__ATTR_NORETURN,__NOTHROW_NCX,__slow_longjmp,(jmp_buf __buf, int __sig),longjmp,(__buf,__sig))
__CEIDECLARE(__ATTR_NORETURN,void,__NOTHROW_NCX,longjmp,(jmp_buf __buf, int __sig),{
	if (__builtin_constant_p(__sig != 0) && (__sig != 0))
		__fast_longjmp(__buf, __sig);
	__slow_longjmp(__buf, __sig);
})
#endif /* !__INTELLISENSE__ */
#else /* __CRT_HAVE___fast_longjmp */
__CDECLARE_VOID(__ATTR_NORETURN,__NOTHROW_NCX,longjmp,(jmp_buf __buf, int __sig),(__buf,__sig))
#endif /* !__CRT_HAVE___fast_longjmp */
#elif defined(__CRT_HAVE__longjmp)
__CREDIRECT_VOID(__ATTR_NORETURN,__NOTHROW_NCX,longjmp,(jmp_buf __buf, int __sig),_longjmp,(__buf,__sig))
#else /* ... */
#undef __std_longjmp_defined
#endif /* !... */
#endif /* !__std_longjmp_defined */

__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#ifndef __jmp_buf_defined
#define __jmp_buf_defined
__NAMESPACE_STD_USING(jmp_buf)
#endif /* !__jmp_buf_defined */
#if defined(__std_setjmp_defined) && !defined(__setjmp_defined)
#define __setjmp_defined
__NAMESPACE_STD_USING(setjmp)
#endif /* __std_setjmp_defined && !__setjmp_defined */
#if defined(__std_longjmp_defined) && !defined(__longjmp_defined)
#define __longjmp_defined
__NAMESPACE_STD_USING(longjmp)
#endif /* __std_longjmp_defined && !__longjmp_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifdef __USE_POSIX
#if defined(__CRT_HAVE__setjmpex) || defined(__CRT_HAVE_sigsetjmp) || defined(__CRT_HAVE___sigsetjmp)
typedef struct __sigjmp_buf sigjmp_buf[1];
#ifdef __CRT_HAVE_sigsetjmp
__CDECLARE(__ATTR_RETURNS_TWICE,int,__NOTHROW_NCX,sigsetjmp,(sigjmp_buf __buf, int __savemask),(__buf,__savemask))
#elif defined(__CRT_HAVE___sigsetjmp)
__CREDIRECT(__ATTR_RETURNS_TWICE,int,__NOTHROW_NCX,sigsetjmp,(sigjmp_buf __buf, int __savemask),__sigsetjmp,(__buf,__savemask))
#else /* ... */
__CDECLARE(__ATTR_RETURNS_TWICE,int,__NOTHROW_NCX,_setjmpex,(sigjmp_buf __buf),(__buf))
#ifdef __cplusplus
#define sigsetjmp(buf,safemask)   ((void)(safemask),::_setjmpex(buf))
#else /* __cplusplus */
#define sigsetjmp(buf,safemask)   ((void)(safemask),_setjmpex(buf))
#endif /* !__cplusplus */
#endif /* !... */
#ifdef __CRT_HAVE_siglongjmp
__CDECLARE_VOID(__ATTR_NORETURN,__NOTHROW_NCX,siglongjmp,(sigjmp_buf __buf, int __sig),(__buf,__sig))
#elif defined(__CRT_HAVE___siglongjmp)
__CREDIRECT_VOID(__ATTR_NORETURN,__NOTHROW_NCX,siglongjmp,(sigjmp_buf __buf, int __sig),__siglongjmp,(__buf,__sig))
#else /* ... */
#ifdef __cplusplus
#define siglongjmp(buf,sig) (__NAMESPACE_STD_SYM longjmp)((struct ::__jmp_buf *)(buf),sig)
#else /* __cplusplus */
#define siglongjmp(buf,sig) (__NAMESPACE_STD_SYM longjmp)((struct __jmp_buf *)(buf),sig)
#endif /* !__cplusplus */
#endif /* !... */
#else /* __CRT_HAVE__setjmpex || __CRT_HAVE_sigsetjmp */
typedef struct __jmp_buf sigjmp_buf[1];
#ifdef __std_setjmp_defined
#define sigsetjmp(buf,safemask)   ((void)(safemask),(__NAMESPACE_STD_SYM setjmp)(buf))
#endif /* __std_setjmp_defined */
#ifdef __std_longjmp_defined
#define siglongjmp(buf,sig)       (__NAMESPACE_STD_SYM longjmp)(buf,sig)
#endif /* __std_longjmp_defined */
#endif /* !__CRT_HAVE__setjmpex && !__CRT_HAVE_sigsetjmp */
#endif /* __USE_POSIX */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
/* Alias for `longjmp()' */
#ifdef __CRT_HAVE_longjmp
#if defined(__CRT_HAVE___fast_longjmp) && !defined(__NO_builtin_constant_p) && !defined(__NO_EXTERN_INLINE)
#ifdef __INTELLISENSE__
__ATTR_NORETURN void __NOTHROW_NCX(__LIBCCALL _longjmp)(__NAMESPACE_STD_SYM jmp_buf __buf, int __sig);
#else /* __INTELLISENSE__ */
__CDECLARE_VOID(__ATTR_NORETURN,__NOTHROW_NCX,__fast_longjmp,(__NAMESPACE_STD_SYM jmp_buf __buf, int __sig),(__buf,__sig))
__CREDIRECT_VOID(__ATTR_NORETURN,__NOTHROW_NCX,__slow_longjmp,(__NAMESPACE_STD_SYM jmp_buf __buf, int __sig),longjmp,(__buf,__sig))
__CEIREDIRECT(__ATTR_NORETURN,void,__NOTHROW_NCX,_longjmp,(__NAMESPACE_STD_SYM jmp_buf __buf, int __sig),longjmp,{
	if (__builtin_constant_p(__sig != 0) && (__sig != 0))
		__fast_longjmp(__buf, __sig);
	__slow_longjmp(__buf, __sig);
})
#endif /* !__INTELLISENSE__ */
#else /* __CRT_HAVE___fast_longjmp */
__CREDIRECT_VOID(__ATTR_NORETURN,__NOTHROW_NCX,_longjmp,(__NAMESPACE_STD_SYM jmp_buf __buf, int __sig),longjmp,(__buf,__sig))
#endif /* !__CRT_HAVE___fast_longjmp */
#elif defined(__CRT_HAVE__longjmp)
__CDECLARE_VOID(__ATTR_NORETURN,__NOTHROW_NCX,_longjmp,(__NAMESPACE_STD_SYM jmp_buf __buf, int __sig),(__buf,__sig))
#else /* __CRT_HAVE_longjmp */
#undef __std_longjmp_defined
#endif /* !__CRT_HAVE_longjmp */

/* Alias for `setjmp()' (but is guarantied  to never save the signal  mask,
 * irregardless of how the C library, or the linked program was configured) */
#if defined(__CRT_HAVE__setjmp)
__CDECLARE(__ATTR_RETURNS_TWICE,int,__NOTHROW_NCX,_setjmp,(__NAMESPACE_STD_SYM jmp_buf __buf),(__buf))
#elif defined(__CRT_HAVE_setjmp)
__CREDIRECT(__ATTR_RETURNS_TWICE,int,__NOTHROW_NCX,_setjmp,(__NAMESPACE_STD_SYM jmp_buf __buf),setjmp,(__buf))
#endif /* ... */
#endif /* __USE_MISC || __USE_XOPEN */

#endif /* __CC__ */

__SYSDECL_END

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CSETJMP
#undef _SETJMP_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CSETJMP */
#endif /* !_SETJMP_H */
