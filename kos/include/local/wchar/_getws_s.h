/* HASH CRC-32:0x2848471a */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
#ifndef __local__getws_s_defined
#if (((defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE_ferror_unlocked) || defined(__CRT_HAVE__IO_ferror))) || defined(__CRT_HAVE_fgetws) || defined(__CRT_HAVE_fgetws_unlocked) || defined(__CRT_HAVE__fgetws_nolock)) && !defined(__NO_STDSTREAMS)
#define __local__getws_s_defined 1
#include <kos/anno.h>
/* Dependency: "fgetws" from "wchar" */
#ifndef ____localdep_fgetws_defined
#define ____localdep_fgetws_defined 1
#ifdef __std___localdep_fgetws_defined
__NAMESPACE_STD_USING(__localdep_fgetws)
#elif defined(__CRT_HAVE_fgetws_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__WCHAR_TYPE__ *,,__localdep_fgetws,(__WCHAR_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fgetws_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__WCHAR_TYPE__ *,,__localdep_fgetws,(__WCHAR_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fgetws)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__WCHAR_TYPE__ *,,__localdep_fgetws,(__WCHAR_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fgetws_unlocked)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__WCHAR_TYPE__ *,,__localdep_fgetws,(__WCHAR_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fgetws_nolock)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__WCHAR_TYPE__ *,,__localdep_fgetws,(__WCHAR_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream)) __THROWS(...)
#elif (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE_ferror_unlocked) || defined(__CRT_HAVE__IO_ferror))
#include <local/wchar/fgetws.h>
#define __localdep_fgetws (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetws))
#else /* CUSTOM: fgetws */
#undef ____localdep_fgetws_defined
#endif /* fgetws... */
#endif /* !____localdep_fgetws_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_getws_s) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_getws_s))(__WCHAR_TYPE__ *__buf,
                                                      __SIZE_TYPE__ __buflen) {
#line 2197 "kos/src/libc/magic/wchar.c"
	return __localdep_fgetws(__buf, __buflen, __LOCAL_stdin);
}
__NAMESPACE_LOCAL_END
#endif /* (((__CRT_HAVE_fgetwc || __CRT_HAVE_getwc) && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked) && (__CRT_HAVE_ferror || __CRT_HAVE_ferror_unlocked || __CRT_HAVE__IO_ferror)) || __CRT_HAVE_fgetws || __CRT_HAVE_fgetws_unlocked || __CRT_HAVE__fgetws_nolock) && !__NO_STDSTREAMS */
#endif /* !__local__getws_s_defined */
