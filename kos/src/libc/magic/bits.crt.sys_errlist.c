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
%(c_prefix){
/*!included_by <unistd.h>*/
}

%[define_replacement(errno_t = __errno_t)]
%[default:section(".text.crt{|.dos}.errno")]


%[insert:prefix(
#include <features.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}


%#if defined(__USE_GNU) || defined(__USE_DOS)
%{
#ifndef _sys_errlist
#ifdef sys_errlist
#define _sys_errlist sys_errlist
#else /* sys_errlist */
}
[[guard, crt_dos_variant]]
[[const, wunused, nothrow, nonnull]]
char const *const *__sys_errlist();
%{
#ifdef ____sys_errlist_defined
#define _sys_errlist (__sys_errlist())
#endif /* ____sys_errlist_defined */
#ifndef _sys_errlist
#if defined(__CRT_HAVE__sys_errlist)
__CSDECLARE2(,char const *const _sys_errlist[],_sys_errlist)
#define _sys_errlist     _sys_errlist
#elif defined(__CRT_HAVE_sys_errlist)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT2(,char const *const _sys_errlist[],_sys_errlist,sys_errlist)
#define _sys_errlist     _sys_errlist
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE2(,char const *const sys_errlist[],sys_errlist)
#define sys_errlist      sys_errlist
#define _sys_errlist     sys_errlist
#endif /* __NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !_sys_errlist */
#endif /* !sys_errlist */
#endif /* !_sys_errlist */
}


%
%{
#ifndef _sys_nerr
#ifdef sys_nerr
#define _sys_nerr sys_nerr
#else /* sys_nerr */
}
[[guard, crt_dos_variant]]
[[const, wunused, nothrow, nonnull]]
int *__sys_nerr();
%{
#ifdef ____sys_nerr_defined
#define _sys_nerr (*__sys_nerr())
#endif /* ____sys_nerr_defined */
#ifndef _sys_nerr
#if defined(__CRT_HAVE__sys_nerr)
__CSDECLARE(,int,_sys_nerr)
#define _sys_nerr _sys_nerr
#elif defined(__CRT_HAVE_sys_nerr)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,int,_sys_nerr,sys_nerr)
#define _sys_nerr _sys_nerr
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(,int,sys_nerr)
#define sys_nerr sys_nerr
#define _sys_nerr sys_nerr
#endif /* __NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !_sys_nerr */
#endif /* !sys_nerr */
#endif /* !_sys_nerr */
}

%#endif /* __USE_GNU || __USE_DOS */


/* NOTE: libc4/5 exports `sys_errlist' under `__USE_BSD', which
 *       implies `__USE_MISC', so we also export it under  that
 *       same SOURCE control macro! */

%
%#if defined(__USE_MISC) || defined(__USE_DOS)
%{
#ifndef sys_errlist
#ifdef _sys_errlist
#define sys_errlist _sys_errlist
#else /* _sys_errlist */
}
%[insert:extern(__sys_errlist)]
%{
#ifdef ____sys_errlist_defined
#define sys_errlist (__sys_errlist())
#endif /* ____sys_errlist_defined */
#ifndef sys_errlist
#if defined(__CRT_HAVE__sys_errlist)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT2(,char const *const sys_errlist[],sys_errlist,_sys_errlist)
#define sys_errlist      sys_errlist
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE2(,char const *const _sys_errlist[],_sys_errlist)
#define _sys_errlist     _sys_errlist
#define sys_errlist      _sys_errlist
#endif /* __NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE_sys_errlist)
__CSDECLARE2(,char const *const sys_errlist[],sys_errlist)
#define sys_errlist      sys_errlist
#endif /* ... */
#endif /* !sys_errlist */
#endif /* !_sys_errlist */
#endif /* !sys_errlist */
}


%
%{
#ifndef sys_nerr
#ifdef _sys_nerr
#define sys_nerr _sys_nerr
#else /* _sys_nerr */
}
%[insert:extern(__sys_nerr)]
%{
#ifdef ____sys_nerr_defined
#define sys_nerr (*__sys_nerr())
#endif /* ____sys_nerr_defined */
#ifndef sys_nerr
#if defined(__CRT_HAVE__sys_nerr)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,int,sys_nerr,_sys_nerr)
#define sys_nerr sys_nerr
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(,int,_sys_nerr)
#define sys_nerr  _sys_nerr
#define _sys_nerr _sys_nerr
#endif /* __NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE_sys_nerr)
__CSDECLARE(,int,sys_nerr)
#define sys_nerr sys_nerr
#endif /* ... */
#endif /* !sys_nerr */
#endif /* !_sys_nerr */
#endif /* !sys_nerr */
}

%#endif /* __USE_MISC || __USE_DOS */

%{

__SYSDECL_END
#endif /* __CC__ */

}
