/* HASH CRC-32:0x3297f746 */
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
#ifndef __local__cgetws_s_defined
#define __local__cgetws_s_defined
#include <__crt.h>
#include <features.h>
#if ((defined(__CRT_HAVE__getch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getch)) && ((defined(__CRT_HAVE__ungetch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__getwche_defined
#define __local___localdep__getwche_defined
#if defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep__getwche,(void),_getwche_nolock,())
#elif defined(__CRT_HAVE__getwche)
__CREDIRECT(__ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep__getwche,(void),_getwche,())
#else /* ... */
#undef __local___localdep__getwche_defined
#endif /* !... */
#endif /* !__local___localdep__getwche_defined */
#ifndef __local___localdep__ungetwch_defined
#define __local___localdep__ungetwch_defined
#if defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(,__WINT_TYPE__,__NOTHROW_NCX,__localdep__ungetwch,(__WINT_TYPE__ __ch),_ungetwch_nolock,(__ch))
#elif defined(__CRT_HAVE__ungetwch)
__CREDIRECT(,__WINT_TYPE__,__NOTHROW_NCX,__localdep__ungetwch,(__WINT_TYPE__ __ch),_ungetwch,(__ch))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked))
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wconio/_ungetwch.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__ungetwch __LIBC_LOCAL_NAME(_ungetwch)
#else /* ... */
#undef __local___localdep__ungetwch_defined
#endif /* !... */
#endif /* !__local___localdep__ungetwch_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/stdio.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_cgetws_s) __ATTR_NONNULL((1, 3)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_cgetws_s))(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ *__restrict __p_readsize) {
	__WCHAR_TYPE__ __ch;
	if __unlikely(!__bufsize)
		return __ENOSPC;
	__buf[0]      = (__WCHAR_TYPE__)'\0';
	*__p_readsize = 0;
	--__bufsize;
	while (__bufsize && (__ch = (__NAMESPACE_LOCAL_SYM __localdep__getwche)()) != __WEOF) {
		if (__ch == (__WCHAR_TYPE__)'\r') {
			__ch = (__NAMESPACE_LOCAL_SYM __localdep__getwche)();
			if (__ch != __WEOF && __ch != (__WCHAR_TYPE__)'\n')
				(__NAMESPACE_LOCAL_SYM __localdep__ungetwch)(__ch);
			break;
		}
		if (__ch == (__WCHAR_TYPE__)'\n')
			break;
		*__buf++ = __ch;
		*__buf   = (__WCHAR_TYPE__)'\0';
		++*__p_readsize;
		--__bufsize;
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__cgetws_s_defined
#define __local___localdep__cgetws_s_defined
#define __localdep__cgetws_s __LIBC_LOCAL_NAME(_cgetws_s)
#endif /* !__local___localdep__cgetws_s_defined */
#else /* ((__CRT_HAVE__getch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__getch) && ((__CRT_HAVE__ungetch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__ungetch || (__CRT_HAVE_stdtty && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock))) */
#undef __local__cgetws_s_defined
#endif /* ((!__CRT_HAVE__getch_nolock || !__USE_STDIO_UNLOCKED) && !__CRT_HAVE__getch) || ((!__CRT_HAVE__ungetch_nolock || !__USE_STDIO_UNLOCKED) && !__CRT_HAVE__ungetch && (!__CRT_HAVE_stdtty || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock))) */
#endif /* !__local__cgetws_s_defined */
