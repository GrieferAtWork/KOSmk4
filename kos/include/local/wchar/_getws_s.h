/* HASH CRC-32:0xb0dc6363 */
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__getws_s_defined
#define __local__getws_s_defined 1
#include <__crt.h>
#if ((defined(__CRT_HAVE_DOS$fgetws_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$fgetws_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_DOS$_fgetws_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_fgetws_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_fgetws) || (defined(__CRT_HAVE_DOS$fgetws) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$fgetws) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_fgetws_unlocked) || (defined(__CRT_HAVE_DOS$fgetws_unlocked) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$fgetws_unlocked) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE__fgetws_nolock) || (defined(__CRT_HAVE_DOS$_fgetws_nolock) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_fgetws_nolock) && __SIZEOF_WCHAR_T__ == 2) || ((defined(__CRT_HAVE_fgetwc) || (defined(__CRT_HAVE_DOS$fgetwc) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$fgetwc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_getwc) || (defined(__CRT_HAVE_DOS$getwc) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$getwc) && __SIZEOF_WCHAR_T__ == 2)) && ((defined(__CRT_HAVE_DOS$ungetwc_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$ungetwc_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_ungetwc) || (defined(__CRT_HAVE_DOS$ungetwc) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$ungetwc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_ungetwc_unlocked) || (defined(__CRT_HAVE_DOS$ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)))) && !defined(__NO_STDSTREAMS)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fgetws from wchar */
#ifndef __local___localdep_fgetws_defined
#define __local___localdep_fgetws_defined 1
#if defined(__CRT_HAVE_fgetws_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__WCHAR_TYPE__ *,__THROWING,__localdep_fgetws,(__WCHAR_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$fgetws_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__CHAR32_TYPE__ *,__THROWING,__localdep_fgetws,(__CHAR32_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$fgetws_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__CHAR16_TYPE__ *,__THROWING,__localdep_fgetws,(__CHAR16_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__WCHAR_TYPE__ *,__THROWING,__localdep_fgetws,(__WCHAR_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$_fgetws_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__CHAR32_TYPE__ *,__THROWING,__localdep_fgetws,(__CHAR32_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$_fgetws_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__CHAR16_TYPE__ *,__THROWING,__localdep_fgetws,(__CHAR16_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__WCHAR_TYPE__ *,__THROWING,__localdep_fgetws,(__WCHAR_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$fgetws) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__CHAR32_TYPE__ *,__THROWING,__localdep_fgetws,(__CHAR32_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$fgetws) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__CHAR16_TYPE__ *,__THROWING,__localdep_fgetws,(__CHAR16_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws_unlocked)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__WCHAR_TYPE__ *,__THROWING,__localdep_fgetws,(__WCHAR_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$fgetws_unlocked) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__CHAR32_TYPE__ *,__THROWING,__localdep_fgetws,(__CHAR32_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$fgetws_unlocked) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__CHAR16_TYPE__ *,__THROWING,__localdep_fgetws,(__CHAR16_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__WCHAR_TYPE__ *,__THROWING,__localdep_fgetws,(__WCHAR_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$_fgetws_nolock) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__CHAR32_TYPE__ *,__THROWING,__localdep_fgetws,(__CHAR32_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$_fgetws_nolock) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__CHAR16_TYPE__ *,__THROWING,__localdep_fgetws,(__CHAR16_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif (defined(__CRT_HAVE_fgetwc) || (defined(__CRT_HAVE_DOS$fgetwc) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$fgetwc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_getwc) || (defined(__CRT_HAVE_DOS$getwc) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$getwc) && __SIZEOF_WCHAR_T__ == 2)) && ((defined(__CRT_HAVE_DOS$ungetwc_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$ungetwc_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_ungetwc) || (defined(__CRT_HAVE_DOS$ungetwc) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$ungetwc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_ungetwc_unlocked) || (defined(__CRT_HAVE_DOS$ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))
__NAMESPACE_LOCAL_END
#include <local/wchar/fgetws.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fgetws __LIBC_LOCAL_NAME(fgetws)
#else /* ... */
#undef __local___localdep_fgetws_defined
#endif /* !... */
#endif /* !__local___localdep_fgetws_defined */
__NAMESPACE_LOCAL_END
#include <local/stdstreams.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_getws_s) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_getws_s))(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __buflen) {
	return __localdep_fgetws(__buf, __buflen, __LOCAL_stdin);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__getws_s_defined
#define __local___localdep__getws_s_defined 1
#define __localdep__getws_s __LIBC_LOCAL_NAME(_getws_s)
#endif /* !__local___localdep__getws_s_defined */
#else /* ((__CRT_HAVE_DOS$fgetws_unlocked && __USE_STDIO_UNLOCKED && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$fgetws_unlocked && __USE_STDIO_UNLOCKED && __SIZEOF_WCHAR_T__ == 2) || (__CRT_HAVE_DOS$_fgetws_nolock && __USE_STDIO_UNLOCKED && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$_fgetws_nolock && __USE_STDIO_UNLOCKED && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_fgetws || (__CRT_HAVE_DOS$fgetws && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$fgetws && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_fgetws_unlocked || (__CRT_HAVE_DOS$fgetws_unlocked && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$fgetws_unlocked && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE__fgetws_nolock || (__CRT_HAVE_DOS$_fgetws_nolock && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$_fgetws_nolock && __SIZEOF_WCHAR_T__ == 2) || ((__CRT_HAVE_fgetwc || (__CRT_HAVE_DOS$fgetwc && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$fgetwc && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_getwc || (__CRT_HAVE_DOS$getwc && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$getwc && __SIZEOF_WCHAR_T__ == 2)) && ((__CRT_HAVE_DOS$ungetwc_unlocked && __USE_STDIO_UNLOCKED && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$ungetwc_unlocked && __USE_STDIO_UNLOCKED && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_ungetwc || (__CRT_HAVE_DOS$ungetwc && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$ungetwc && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_ungetwc_unlocked || (__CRT_HAVE_DOS$ungetwc_unlocked && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$ungetwc_unlocked && __SIZEOF_WCHAR_T__ == 2)) && (__CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked))) && !__NO_STDSTREAMS */
#undef __local__getws_s_defined
#endif /* ((!__CRT_HAVE_DOS$fgetws_unlocked || !__USE_STDIO_UNLOCKED || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$fgetws_unlocked || !__USE_STDIO_UNLOCKED || !__SIZEOF_WCHAR_T__ == 2) && (!__CRT_HAVE_DOS$_fgetws_nolock || !__USE_STDIO_UNLOCKED || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$_fgetws_nolock || !__USE_STDIO_UNLOCKED || !__SIZEOF_WCHAR_T__ == 2) && !__CRT_HAVE_fgetws && (!__CRT_HAVE_DOS$fgetws || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$fgetws || !__SIZEOF_WCHAR_T__ == 2) && !__CRT_HAVE_fgetws_unlocked && (!__CRT_HAVE_DOS$fgetws_unlocked || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$fgetws_unlocked || !__SIZEOF_WCHAR_T__ == 2) && !__CRT_HAVE__fgetws_nolock && (!__CRT_HAVE_DOS$_fgetws_nolock || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$_fgetws_nolock || !__SIZEOF_WCHAR_T__ == 2) && ((!__CRT_HAVE_fgetwc && (!__CRT_HAVE_DOS$fgetwc || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$fgetwc || !__SIZEOF_WCHAR_T__ == 2) && !__CRT_HAVE_getwc && (!__CRT_HAVE_DOS$getwc || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$getwc || !__SIZEOF_WCHAR_T__ == 2)) || ((!__CRT_HAVE_DOS$ungetwc_unlocked || !__USE_STDIO_UNLOCKED || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$ungetwc_unlocked || !__USE_STDIO_UNLOCKED || !__SIZEOF_WCHAR_T__ == 2) && !__CRT_HAVE_ungetwc && (!__CRT_HAVE_DOS$ungetwc || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$ungetwc || !__SIZEOF_WCHAR_T__ == 2) && !__CRT_HAVE_ungetwc_unlocked && (!__CRT_HAVE_DOS$ungetwc_unlocked || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$ungetwc_unlocked || !__SIZEOF_WCHAR_T__ == 2)) || (!__CRT_HAVE_ferror && !__CRT_HAVE__IO_ferror && !__CRT_HAVE_ferror_unlocked))) || __NO_STDSTREAMS */
#endif /* !__local__getws_s_defined */
