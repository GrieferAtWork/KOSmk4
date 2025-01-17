/* HASH CRC-32:0x1ee46ebb */
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
#ifndef __local_putchar16_defined
#define __local_putchar16_defined
#include <__crt.h>
#include <libc/template/stdstreams.h>
#include <features.h>
#if defined(__LOCAL_stdout) && ((defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$putwc) || (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc_unlocked) || (defined(__CRT_HAVE_putwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$putwc_unlocked))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fputc16_defined
#define __local___localdep_fputc16_defined
#if defined(__CRT_HAVE_fputwc_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16,(__CHAR16_TYPE__ __wc, __FILE *__stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$fputwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT_DOS(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16,(__CHAR16_TYPE__ __wc, __FILE *__stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16,(__CHAR16_TYPE__ __wc, __FILE *__stream),putwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$putwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT_DOS(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16,(__CHAR16_TYPE__ __wc, __FILE *__stream),putwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16,(__CHAR16_TYPE__ __wc, __FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$fputwc)
__CREDIRECT_DOS(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16,(__CHAR16_TYPE__ __wc, __FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16,(__CHAR16_TYPE__ __wc, __FILE *__stream),putwc,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$putwc)
__CREDIRECT_DOS(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16,(__CHAR16_TYPE__ __wc, __FILE *__stream),putwc,(__wc,__stream))
#elif defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16,(__CHAR16_TYPE__ __wc, __FILE *__stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$fputwc_unlocked)
__CREDIRECT_DOS(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16,(__CHAR16_TYPE__ __wc, __FILE *__stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16,(__CHAR16_TYPE__ __wc, __FILE *__stream),putwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$putwc_unlocked)
__CREDIRECT_DOS(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fputc16,(__CHAR16_TYPE__ __wc, __FILE *__stream),putwc_unlocked,(__wc,__stream))
#else /* ... */
#undef __local___localdep_fputc16_defined
#endif /* !... */
#endif /* !__local___localdep_fputc16_defined */
__LOCAL_LIBC(putchar16) __WINT16_TYPE__
__NOTHROW_CB_NCX(__LIBDCALL __LIBC_LOCAL_NAME(putchar16))(__CHAR16_TYPE__ __wc) {
	return (__NAMESPACE_LOCAL_SYM __localdep_fputc16)(__wc, __LOCAL_stdout);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_putchar16_defined
#define __local___localdep_putchar16_defined
#define __localdep_putchar16 __LIBC_LOCAL_NAME(putchar16)
#endif /* !__local___localdep_putchar16_defined */
#else /* __LOCAL_stdout && ((__CRT_HAVE_fputwc && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$fputwc || (__CRT_HAVE_putwc && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$putwc || (__CRT_HAVE_fputwc_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$fputwc_unlocked || (__CRT_HAVE_putwc_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$putwc_unlocked) */
#undef __local_putchar16_defined
#endif /* !__LOCAL_stdout || ((!__CRT_HAVE_fputwc || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$fputwc && (!__CRT_HAVE_putwc || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$putwc && (!__CRT_HAVE_fputwc_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$fputwc_unlocked && (!__CRT_HAVE_putwc_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$putwc_unlocked) */
#endif /* !__local_putchar16_defined */
