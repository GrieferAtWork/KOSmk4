/* HASH CRC-32:0x98ed1dbb */
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
#ifndef __local_putchar32_unlocked_defined
#define __local_putchar32_unlocked_defined
#include <__crt.h>
#include <libc/template/stdstreams.h>
#if defined(__LOCAL_stdout) && ((defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc_unlocked) || (defined(__CRT_HAVE_putwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$putwc_unlocked) || (defined(__CRT_HAVE__putwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_putwc_nolock) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_fputwc_nolock) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$putwc) || (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fputc32_unlocked_defined
#define __local___localdep_fputc32_unlocked_defined
#if defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT32_TYPE__,__NOTHROW_CB,__localdep_fputc32_unlocked,(__CHAR32_TYPE__ __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_KOS$fputwc_unlocked)
__CREDIRECT_KOS(__ATTR_INOUT(2),__WINT32_TYPE__,__NOTHROW_CB,__localdep_fputc32_unlocked,(__CHAR32_TYPE__ __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT32_TYPE__,__NOTHROW_CB,__localdep_fputc32_unlocked,(__CHAR32_TYPE__ __wc, __FILE *__restrict __stream),putwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_KOS$putwc_unlocked)
__CREDIRECT_KOS(__ATTR_INOUT(2),__WINT32_TYPE__,__NOTHROW_CB,__localdep_fputc32_unlocked,(__CHAR32_TYPE__ __wc, __FILE *__restrict __stream),putwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE__putwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT32_TYPE__,__NOTHROW_CB,__localdep_fputc32_unlocked,(__CHAR32_TYPE__ __wc, __FILE *__restrict __stream),_putwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_KOS$_putwc_nolock)
__CREDIRECT_KOS(__ATTR_INOUT(2),__WINT32_TYPE__,__NOTHROW_CB,__localdep_fputc32_unlocked,(__CHAR32_TYPE__ __wc, __FILE *__restrict __stream),_putwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT32_TYPE__,__NOTHROW_CB,__localdep_fputc32_unlocked,(__CHAR32_TYPE__ __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_KOS$_fputwc_nolock)
__CREDIRECT_KOS(__ATTR_INOUT(2),__WINT32_TYPE__,__NOTHROW_CB,__localdep_fputc32_unlocked,(__CHAR32_TYPE__ __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT32_TYPE__,__NOTHROW_CB,__localdep_fputc32_unlocked,(__CHAR32_TYPE__ __wc, __FILE *__restrict __stream),putwc,(__wc,__stream))
#elif defined(__CRT_HAVE_KOS$putwc)
__CREDIRECT_KOS(__ATTR_INOUT(2),__WINT32_TYPE__,__NOTHROW_CB,__localdep_fputc32_unlocked,(__CHAR32_TYPE__ __wc, __FILE *__restrict __stream),putwc,(__wc,__stream))
#elif defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT32_TYPE__,__NOTHROW_CB,__localdep_fputc32_unlocked,(__CHAR32_TYPE__ __wc, __FILE *__restrict __stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_KOS$fputwc)
__CREDIRECT_KOS(__ATTR_INOUT(2),__WINT32_TYPE__,__NOTHROW_CB,__localdep_fputc32_unlocked,(__CHAR32_TYPE__ __wc, __FILE *__restrict __stream),fputwc,(__wc,__stream))
#else /* ... */
#undef __local___localdep_fputc32_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_fputc32_unlocked_defined */
__LOCAL_LIBC(putchar32_unlocked) __WINT32_TYPE__
__NOTHROW_CB(__LIBKCALL __LIBC_LOCAL_NAME(putchar32_unlocked))(__CHAR32_TYPE__ __wc) {
	return (__NAMESPACE_LOCAL_SYM __localdep_fputc32_unlocked)(__wc, __LOCAL_stdout);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_putchar32_unlocked_defined
#define __local___localdep_putchar32_unlocked_defined
#define __localdep_putchar32_unlocked __LIBC_LOCAL_NAME(putchar32_unlocked)
#endif /* !__local___localdep_putchar32_unlocked_defined */
#else /* __LOCAL_stdout && ((__CRT_HAVE_fputwc_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$fputwc_unlocked || (__CRT_HAVE_putwc_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$putwc_unlocked || (__CRT_HAVE__putwc_nolock && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_putwc_nolock || (__CRT_HAVE__fputwc_nolock && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_fputwc_nolock || (__CRT_HAVE_putwc && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$putwc || (__CRT_HAVE_fputwc && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$fputwc) */
#undef __local_putchar32_unlocked_defined
#endif /* !__LOCAL_stdout || ((!__CRT_HAVE_fputwc_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$fputwc_unlocked && (!__CRT_HAVE_putwc_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$putwc_unlocked && (!__CRT_HAVE__putwc_nolock || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_putwc_nolock && (!__CRT_HAVE__fputwc_nolock || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_fputwc_nolock && (!__CRT_HAVE_putwc || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$putwc && (!__CRT_HAVE_fputwc || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$fputwc) */
#endif /* !__local_putchar32_unlocked_defined */
