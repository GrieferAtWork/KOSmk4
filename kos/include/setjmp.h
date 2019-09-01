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
#ifndef _SETJMP_H
#define _SETJMP_H 1

#include <__stdinc.h>
#if defined(_CXX_CSETJMP) && !defined(__CXX_SYSTEM_HEADER)
/* Import all symbols into the global namespace when re-including "setjmp.h" after "csetjmp" */
#ifndef __jmp_buf_defined
#define __jmp_buf_defined 1
__NAMESPACE_STD_USING(jmp_buf)
#endif /* !__jmp_buf_defined */
#if defined(__std_setjmp_defined) && !defined(__setjmp_defined)
#define __setjmp_defined 1
__NAMESPACE_STD_USING(setjmp)
#endif /* __std_setjmp_defined && !__setjmp_defined */
#if defined(__std_longjmp_defined) && !defined(__longjmp_defined)
#define __longjmp_defined 1
__NAMESPACE_STD_USING(longjmp)
#endif /* __std_longjmp_defined && !__longjmp_defined */
#else /* _CXX_CSETJMP && !__CXX_SYSTEM_HEADER */
#include <__crt.h>
#include <features.h>
#include <bits/setjmp.h>
#include <bits/sigset.h>

__SYSDECL_BEGIN

#ifdef __CC__

__NAMESPACE_STD_BEGIN

#ifndef __std_jmp_buf_defined
#define __std_jmp_buf_defined 1
typedef struct __jmp_buf jmp_buf[1];
#endif /* !__std_jmp_buf_defined */

#ifndef __std_setjmp_defined
#define __std_setjmp_defined 1
#ifdef __setjmp_defined
__NAMESPACE_GLB_USING(setjmp)
#elif defined(__CRT_HAVE_setjmp)
__CDECLARE(__ATTR_RETURNS_TWICE,int,__NOTHROW_NCX,setjmp,(jmp_buf __buf),(__buf))
#elif defined(__CRT_HAVE__setjmp)
#ifndef __NO_ASMNAME
__CREDIRECT(__ATTR_RETURNS_TWICE,int,__NOTHROW_NCX,setjmp,(jmp_buf __buf),_setjmp,(__buf))
#else /* !__NO_ASMNAME */
__CDECLARE(__ATTR_RETURNS_TWICE,int,__NOTHROW_NCX,_setjmp,(jmp_buf __buf),(__buf))
#define setjmp   _setjmp
#endif /* __NO_ASMNAME */
#else
#undef __std_setjmp_defined
#endif
#endif /* !__std_setjmp_defined */

#ifndef __std_longjmp_defined
#define __std_longjmp_defined 1
#ifdef __longjmp_defined
__NAMESPACE_GLB_USING(longjmp)
#elif defined(__CRT_HAVE_longjmp)
#if defined(__CRT_HAVE___fast_longjmp) && !defined(__NO_builtin_constant_p)
__CDECLARE_VOID(__ATTR_NORETURN,__NOTHROW_NCX,__fast_longjmp,(jmp_buf __buf, int __sig),(__buf,__sig))
__CREDIRECT_VOID(__ATTR_NORETURN,__NOTHROW_NCX,__slow_longjmp,(jmp_buf __buf, int __sig),longjmp,(__buf,__sig))
__FORCELOCAL __ATTR_NORETURN void __NOTHROW_NCX(__LIBCCALL longjmp)(jmp_buf __buf, int __sig) {
	return __builtin_constant_p(__sig != 0) && (__sig != 0)
	       ? __fast_longjmp(__buf, __sig)
	       : __slow_longjmp(__buf, __sig);
}
#else /* __CRT_HAVE___fast_longjmp */
__CDECLARE_VOID(__ATTR_NORETURN,__NOTHROW_NCX,longjmp,(jmp_buf __buf, int __sig),(__buf,__sig))
#endif /* !__CRT_HAVE___fast_longjmp */
#else /* __CRT_HAVE_longjmp */
#undef __std_longjmp_defined
#endif /* !__CRT_HAVE_longjmp */
#endif /* !__std_longjmp_defined */

__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#ifndef __jmp_buf_defined
#define __jmp_buf_defined 1
__NAMESPACE_STD_USING(jmp_buf)
#endif /* !__jmp_buf_defined */
#if defined(__std_setjmp_defined) && !defined(__setjmp_defined)
#define __setjmp_defined 1
__NAMESPACE_STD_USING(setjmp)
#endif /* __std_setjmp_defined && !__setjmp_defined */
#if defined(__std_longjmp_defined) && !defined(__longjmp_defined)
#define __longjmp_defined 1
__NAMESPACE_STD_USING(longjmp)
#endif /* __std_longjmp_defined && !__longjmp_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifdef __USE_POSIX
#if defined(__CRT_HAVE__setjmpex) || defined(__CRT_HAVE_sigsetjmp)
typedef struct __sigjmp_buf sigjmp_buf[1];
#ifdef __CRT_HAVE_sigsetjmp
__CDECLARE(__ATTR_RETURNS_TWICE,int,__NOTHROW_NCX,sigsetjmp,(sigjmp_buf __buf, int __savemask),(__buf,__savemask))
#else /* __CRT_HAVE_sigsetjmp */
__CDECLARE(__ATTR_RETURNS_TWICE,int,__NOTHROW_NCX,_setjmpex,(sigjmp_buf __buf),(__buf))
#ifdef __cplusplus
#define sigsetjmp(buf,safemask)   ((void)(safemask),::_setjmpex(buf))
#else /* __cplusplus */
#define sigsetjmp(buf,safemask)   ((void)(safemask),_setjmpex(buf))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE_sigsetjmp */
#ifdef __CRT_HAVE_siglongjmp
__CDECLARE_VOID(__ATTR_NORETURN,__NOTHROW_NCX,siglongjmp,(sigjmp_buf __buf, int __sig),(__buf,__sig))
#else /* __CRT_HAVE_siglongjmp */
#ifdef __cplusplus
#define siglongjmp(buf,sig) (__NAMESPACE_STD_SYM longjmp)((struct ::__jmp_buf *)(buf),sig)
#else /* __cplusplus */
#define siglongjmp(buf,sig) (__NAMESPACE_STD_SYM longjmp)((struct __jmp_buf *)(buf),sig)
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE_siglongjmp */
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

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_CXX_CSETJMP || __CXX_SYSTEM_HEADER */
#endif /* !_SETJMP_H */
