/* HASH CRC-32:0xb85a4ba5 */
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
#ifndef __local__getc16s_defined
#define __local__getc16s_defined
#include <__crt.h>
#include <libc/template/stdstreams.h>
#include <features.h>
#if (defined(__CRT_HAVE__getws_s) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_getws_s) || (defined(__LOCAL_stdin) && (defined(__CRT_HAVE_fgetws) || defined(__CRT_HAVE_fgetws_unlocked) || defined(__CRT_HAVE__fgetws_nolock) || ((defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)))) && __SIZEOF_WCHAR_T__ == 2) || (defined(__LOCAL_stdin) && ((defined(__CRT_HAVE_fgetws) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fgetws) || (defined(__CRT_HAVE_fgetws_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fgetws_unlocked) || (defined(__CRT_HAVE__fgetws_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_fgetws_nolock) || ((defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_fgetwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fgetwc) || (defined(__CRT_HAVE_getwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$getwc)) && ((defined(__CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$ungetwc) || (defined(__CRT_HAVE_ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)))))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__getc16s_s_defined
#define __local___localdep__getc16s_s_defined
#if defined(__CRT_HAVE__getws_s) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(,__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep__getc16s_s,(__CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __buflen),_getws_s,(__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$_getws_s)
__CREDIRECT_DOS(,__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep__getc16s_s,(__CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __buflen),_getws_s,(__buf,__buflen))
#elif defined(__LOCAL_stdin) && (defined(__CRT_HAVE_fgetws) || defined(__CRT_HAVE_fgetws_unlocked) || defined(__CRT_HAVE__fgetws_nolock) || ((defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)))) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wstdio/_getws_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__getc16s_s __NAMESPACE_LOCAL_TYPEHAX(__CHAR16_TYPE__ *(__LIBDCALL*)(__CHAR16_TYPE__ *,__SIZE_TYPE__),__CHAR16_TYPE__ *(__LIBDCALL&)(__CHAR16_TYPE__ *,__SIZE_TYPE__),_getws_s)
#elif defined(__LOCAL_stdin) && ((defined(__CRT_HAVE_fgetws) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fgetws) || (defined(__CRT_HAVE_fgetws_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fgetws_unlocked) || (defined(__CRT_HAVE__fgetws_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_fgetws_nolock) || ((defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_fgetwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fgetwc) || (defined(__CRT_HAVE_getwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$getwc)) && ((defined(__CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$ungetwc) || (defined(__CRT_HAVE_ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdio/_getc16s_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__getc16s_s __LIBC_LOCAL_NAME(_getc16s_s)
#else /* ... */
#undef __local___localdep__getc16s_s_defined
#endif /* !... */
#endif /* !__local___localdep__getc16s_s_defined */
__LOCAL_LIBC(_getc16s) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_getc16s))(__CHAR16_TYPE__ *__buf) {
	return (__NAMESPACE_LOCAL_SYM __localdep__getc16s_s)(__buf, (__SIZE_TYPE__)-1);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__getc16s_defined
#define __local___localdep__getc16s_defined
#define __localdep__getc16s __LIBC_LOCAL_NAME(_getc16s)
#endif /* !__local___localdep__getc16s_defined */
#else /* (__CRT_HAVE__getws_s && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$_getws_s || (__LOCAL_stdin && (__CRT_HAVE_fgetws || __CRT_HAVE_fgetws_unlocked || __CRT_HAVE__fgetws_nolock || ((__CRT_HAVE_fgetwc || __CRT_HAVE_getwc) && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked) && (__CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked))) && __SIZEOF_WCHAR_T__ == 2) || (__LOCAL_stdin && ((__CRT_HAVE_fgetws && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$fgetws || (__CRT_HAVE_fgetws_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$fgetws_unlocked || (__CRT_HAVE__fgetws_nolock && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$_fgetws_nolock || ((__CRT_HAVE_fgetwc || __CRT_HAVE_getwc) && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked) && (__CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked) && __SIZEOF_WCHAR_T__ == 2) || (((__CRT_HAVE_fgetwc && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$fgetwc || (__CRT_HAVE_getwc && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$getwc) && ((__CRT_HAVE_ungetwc && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$ungetwc || (__CRT_HAVE_ungetwc_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$ungetwc_unlocked) && (__CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked)))) */
#undef __local__getc16s_defined
#endif /* (!__CRT_HAVE__getws_s || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$_getws_s && (!__LOCAL_stdin || (!__CRT_HAVE_fgetws && !__CRT_HAVE_fgetws_unlocked && !__CRT_HAVE__fgetws_nolock && ((!__CRT_HAVE_fgetwc && !__CRT_HAVE_getwc) || (!__CRT_HAVE_ungetwc && !__CRT_HAVE_ungetwc_unlocked) || (!__CRT_HAVE_ferror && !__CRT_HAVE__IO_ferror && !__CRT_HAVE_ferror_unlocked))) || __SIZEOF_WCHAR_T__ != 2) && (!__LOCAL_stdin || ((!__CRT_HAVE_fgetws || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$fgetws && (!__CRT_HAVE_fgetws_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$fgetws_unlocked && (!__CRT_HAVE__fgetws_nolock || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$_fgetws_nolock && ((!__CRT_HAVE_fgetwc && !__CRT_HAVE_getwc) || (!__CRT_HAVE_ungetwc && !__CRT_HAVE_ungetwc_unlocked) || (!__CRT_HAVE_ferror && !__CRT_HAVE__IO_ferror && !__CRT_HAVE_ferror_unlocked) || __SIZEOF_WCHAR_T__ != 2) && (((!__CRT_HAVE_fgetwc || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$fgetwc && (!__CRT_HAVE_getwc || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$getwc) || ((!__CRT_HAVE_ungetwc || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$ungetwc && (!__CRT_HAVE_ungetwc_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$ungetwc_unlocked) || (!__CRT_HAVE_ferror && !__CRT_HAVE__IO_ferror && !__CRT_HAVE_ferror_unlocked)))) */
#endif /* !__local__getc16s_defined */
