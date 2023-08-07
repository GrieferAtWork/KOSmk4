/* HASH CRC-32:0xa4c50857 */
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
#ifndef __local__putwch_defined
#define __local__putwch_defined
#include <__crt.h>
#include <features.h>
#if defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fputwc_defined
#define __local___localdep_fputwc_defined
#if defined(__CRT_HAVE_fputwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__NOTHROW_CB,__localdep_fputwc,(__WCHAR_TYPE__ __wc, __FILE *__stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__NOTHROW_CB,__localdep_fputwc,(__WCHAR_TYPE__ __wc, __FILE *__stream),putwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_fputwc)
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__NOTHROW_CB,__localdep_fputwc,(__WCHAR_TYPE__ __wc, __FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc)
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__NOTHROW_CB,__localdep_fputwc,(__WCHAR_TYPE__ __wc, __FILE *__stream),putwc,(__wc,__stream))
#elif defined(__CRT_HAVE_fputwc_unlocked)
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__NOTHROW_CB,__localdep_fputwc,(__WCHAR_TYPE__ __wc, __FILE *__stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc_unlocked)
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__NOTHROW_CB,__localdep_fputwc,(__WCHAR_TYPE__ __wc, __FILE *__stream),putwc_unlocked,(__wc,__stream))
#else /* ... */
#undef __local___localdep_fputwc_defined
#endif /* !... */
#endif /* !__local___localdep_fputwc_defined */
__NAMESPACE_LOCAL_END
#include <libc/template/stdtty.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_putwch) __WINT_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_putwch))(__WCHAR_TYPE__ __ch) {
	return (__NAMESPACE_LOCAL_SYM __localdep_fputwc)(__ch, __LOCAL_stdtty);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__putwch_defined
#define __local___localdep__putwch_defined
#define __localdep__putwch __LIBC_LOCAL_NAME(_putwch)
#endif /* !__local___localdep__putwch_defined */
#else /* __CRT_HAVE_stdtty && (__CRT_HAVE_fputwc || __CRT_HAVE_putwc || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked) */
#undef __local__putwch_defined
#endif /* !__CRT_HAVE_stdtty || (!__CRT_HAVE_fputwc && !__CRT_HAVE_putwc && !__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE_putwc_unlocked) */
#endif /* !__local__putwch_defined */
