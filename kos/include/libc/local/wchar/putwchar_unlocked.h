/* HASH CRC-32:0x777718e */
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
#ifndef __local_putwchar_unlocked_defined
#define __local_putwchar_unlocked_defined
#include <__crt.h>
#include <libc/template/stdstreams.h>
#if defined(__LOCAL_stdout) && (defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked) || defined(__CRT_HAVE__putwc_nolock) || defined(__CRT_HAVE__fputwc_nolock))
#include <hybrid/typecore.h>
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fputwc_unlocked_defined
#define __local___localdep_fputwc_unlocked_defined
#ifdef __CRT_HAVE_fputwc_unlocked
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,__localdep_fputwc_unlocked,(__WCHAR_TYPE__ __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc_unlocked)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,__localdep_fputwc_unlocked,(__WCHAR_TYPE__ __wc, __FILE *__restrict __stream),putwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE__putwc_nolock)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,__localdep_fputwc_unlocked,(__WCHAR_TYPE__ __wc, __FILE *__restrict __stream),_putwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,__localdep_fputwc_unlocked,(__WCHAR_TYPE__ __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#else /* ... */
#undef __local___localdep_fputwc_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_fputwc_unlocked_defined */
__LOCAL_LIBC(putwchar_unlocked) __WINT_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(putwchar_unlocked))(__WCHAR_TYPE__ __wc) __THROWS(...) {
	return (__NAMESPACE_LOCAL_SYM __localdep_fputwc_unlocked)(__wc, __LOCAL_stdout);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_putwchar_unlocked_defined
#define __local___localdep_putwchar_unlocked_defined
#define __localdep_putwchar_unlocked __LIBC_LOCAL_NAME(putwchar_unlocked)
#endif /* !__local___localdep_putwchar_unlocked_defined */
#else /* __LOCAL_stdout && (__CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked || __CRT_HAVE__putwc_nolock || __CRT_HAVE__fputwc_nolock) */
#undef __local_putwchar_unlocked_defined
#endif /* !__LOCAL_stdout || (!__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE_putwc_unlocked && !__CRT_HAVE__putwc_nolock && !__CRT_HAVE__fputwc_nolock) */
#endif /* !__local_putwchar_unlocked_defined */
