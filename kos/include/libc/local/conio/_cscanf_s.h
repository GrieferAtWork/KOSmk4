/* HASH CRC-32:0x4f7f492f */
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
#ifndef __local__cscanf_s_defined
#define __local__cscanf_s_defined
#include <__crt.h>
#include <features.h>
#if defined(__CRT_HAVE__vcscanf_s) || defined(__CRT_HAVE__vcscanf_s_l) || defined(__CRT_HAVE___conio_common_vcscanf) || (((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche)) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__vcscanf_s_defined
#define __local___localdep__vcscanf_s_defined
#ifdef __CRT_HAVE__vcscanf_s
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep__vcscanf_s,(char const *__format, __builtin_va_list __args),_vcscanf_s,(__format,__args))
#elif defined(__CRT_HAVE__vcscanf_s_l) || defined(__CRT_HAVE___conio_common_vcscanf) || (((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche)) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
__NAMESPACE_LOCAL_END
#include <libc/local/conio/_vcscanf_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vcscanf_s __LIBC_LOCAL_NAME(_vcscanf_s)
#else /* ... */
#undef __local___localdep__vcscanf_s_defined
#endif /* !... */
#endif /* !__local___localdep__vcscanf_s_defined */
__LOCAL_LIBC(_cscanf_s) __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(_cscanf_s))(char const *__format, ...) {
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = (__NAMESPACE_LOCAL_SYM __localdep__vcscanf_s)(__format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__cscanf_s_defined
#define __local___localdep__cscanf_s_defined
#define __localdep__cscanf_s __LIBC_LOCAL_NAME(_cscanf_s)
#endif /* !__local___localdep__cscanf_s_defined */
#else /* __CRT_HAVE__vcscanf_s || __CRT_HAVE__vcscanf_s_l || __CRT_HAVE___conio_common_vcscanf || (((__CRT_HAVE__getwche_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__getwche) && ((__CRT_HAVE__ungetwch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__ungetwch || (__CRT_HAVE_stdtty && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked)))) */
#undef __local__cscanf_s_defined
#endif /* !__CRT_HAVE__vcscanf_s && !__CRT_HAVE__vcscanf_s_l && !__CRT_HAVE___conio_common_vcscanf && (((!__CRT_HAVE__getwche_nolock || !__USE_STDIO_UNLOCKED) && !__CRT_HAVE__getwche) || ((!__CRT_HAVE__ungetwch_nolock || !__USE_STDIO_UNLOCKED) && !__CRT_HAVE__ungetwch && (!__CRT_HAVE_stdtty || (!__CRT_HAVE_ungetwc && !__CRT_HAVE_ungetwc_unlocked)))) */
#endif /* !__local__cscanf_s_defined */
