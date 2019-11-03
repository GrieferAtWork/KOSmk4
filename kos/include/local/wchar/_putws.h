/* HASH CRC-32:0x9b813af9 */
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
#ifndef __local__putws_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputws) || defined(__CRT_HAVE_fputws_unlocked) || defined(__CRT_HAVE__fputws_nolock)) && !defined(__NO_STDSTREAMS)
#define __local__putws_defined 1
/* Dependency: "fputws" from "wchar" */
#ifndef ____localdep_fputws_defined
#define ____localdep_fputws_defined 1
#ifdef __std___localdep_fputws_defined
__NAMESPACE_STD_USING(__localdep_fputws)
#elif defined(__CRT_HAVE_fputws_unlocked) && (defined(__USE_STDIO_UNLOCKED))
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,,__localdep_fputws,(__WCHAR_TYPE__ const *__restrict __string, __FILE *__restrict __stream),fputws_unlocked,(__string,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fputws_nolock) && (defined(__USE_STDIO_UNLOCKED))
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,,__localdep_fputws,(__WCHAR_TYPE__ const *__restrict __string, __FILE *__restrict __stream),_fputws_nolock,(__string,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fputws)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,,__localdep_fputws,(__WCHAR_TYPE__ const *__restrict __string, __FILE *__restrict __stream),fputws,(__string,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fputws_unlocked)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,,__localdep_fputws,(__WCHAR_TYPE__ const *__restrict __string, __FILE *__restrict __stream),fputws_unlocked,(__string,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fputws_nolock)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,,__localdep_fputws,(__WCHAR_TYPE__ const *__restrict __string, __FILE *__restrict __stream),_fputws_nolock,(__string,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked)
#include <local/wchar/fputws.h>
#define __localdep_fputws (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputws))
#else /* CUSTOM: fputws */
#undef ____localdep_fputws_defined
#endif /* fputws... */
#endif /* !____localdep_fputws_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_putws) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_putws))(__WCHAR_TYPE__ const *__string) {
#line 2090 "kos/src/libc/magic/wchar.c"
	return __localdep_fputws(__string, __LOCAL_stdout);
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputws) || defined(__CRT_HAVE_fputws_unlocked) || defined(__CRT_HAVE__fputws_nolock)) && !defined(__NO_STDSTREAMS) */
#endif /* !__local__putws_defined */
