/* HASH CRC-32:0x5b53a79d */
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
#ifndef __local_putchar16_unlocked_defined
#define __local_putchar16_unlocked_defined
#include <__crt.h>
#include <libc/template/stdstreams.h>
#if defined(__LOCAL_stdout) && ((defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc_unlocked) || (defined(__CRT_HAVE_putwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$putwc_unlocked) || (defined(__CRT_HAVE__putwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_putwc_nolock) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_fputwc_nolock) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$putwc) || (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fputc16_unlocked_defined
#define __local___localdep_fputc16_unlocked_defined
#if defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$fputwc_unlocked)
__CREDIRECT_DOS(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),putwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$putwc_unlocked)
__CREDIRECT_DOS(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),putwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE__putwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),_putwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$_putwc_nolock)
__CREDIRECT_DOS(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),_putwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$_fputwc_nolock)
__CREDIRECT_DOS(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),putwc,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$putwc)
__CREDIRECT_DOS(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),putwc,(__wc,__stream))
#elif defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$fputwc)
__CREDIRECT_DOS(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),fputwc,(__wc,__stream))
#else /* ... */
#undef __local___localdep_fputc16_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_fputc16_unlocked_defined */
__LOCAL_LIBC(putchar16_unlocked) __WINT16_TYPE__
__NOTHROW_CB_NCX(__LIBDCALL __LIBC_LOCAL_NAME(putchar16_unlocked))(__CHAR16_TYPE__ __wc) {
	return (__NAMESPACE_LOCAL_SYM __localdep_fputc16_unlocked)(__wc, __LOCAL_stdout);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_putchar16_unlocked_defined
#define __local___localdep_putchar16_unlocked_defined
#define __localdep_putchar16_unlocked __LIBC_LOCAL_NAME(putchar16_unlocked)
#endif /* !__local___localdep_putchar16_unlocked_defined */
#else /* __LOCAL_stdout && ((__CRT_HAVE_fputwc_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$fputwc_unlocked || (__CRT_HAVE_putwc_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$putwc_unlocked || (__CRT_HAVE__putwc_nolock && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$_putwc_nolock || (__CRT_HAVE__fputwc_nolock && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$_fputwc_nolock || (__CRT_HAVE_putwc && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$putwc || (__CRT_HAVE_fputwc && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$fputwc) */
#undef __local_putchar16_unlocked_defined
#endif /* !__LOCAL_stdout || ((!__CRT_HAVE_fputwc_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$fputwc_unlocked && (!__CRT_HAVE_putwc_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$putwc_unlocked && (!__CRT_HAVE__putwc_nolock || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$_putwc_nolock && (!__CRT_HAVE__fputwc_nolock || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$_fputwc_nolock && (!__CRT_HAVE_putwc || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$putwc && (!__CRT_HAVE_fputwc || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$fputwc) */
#endif /* !__local_putchar16_unlocked_defined */
