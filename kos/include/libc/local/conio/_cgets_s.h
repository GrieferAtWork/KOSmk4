/* HASH CRC-32:0x9e4e08a4 */
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
#ifndef __local__cgets_s_defined
#define __local__cgets_s_defined
#include <__crt.h>
#include <features.h>
#if ((defined(__CRT_HAVE__getch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getch)) && ((defined(__CRT_HAVE__ungetch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__getche_defined
#define __local___localdep__getche_defined
#if defined(__CRT_HAVE__getche_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__getche,(void),_getche_nolock,())
#elif defined(__CRT_HAVE__getche)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__getche,(void),_getche,())
#else /* ... */
#undef __local___localdep__getche_defined
#endif /* !... */
#endif /* !__local___localdep__getche_defined */
#ifndef __local___localdep__ungetch_defined
#define __local___localdep__ungetch_defined
#if defined(__CRT_HAVE__ungetch_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep__ungetch,(int __ch),_ungetch_nolock,(__ch))
#elif defined(__CRT_HAVE__ungetch)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep__ungetch,(int __ch),_ungetch,(__ch))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))
__NAMESPACE_LOCAL_END
#include <libc/local/conio/_ungetch.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__ungetch __LIBC_LOCAL_NAME(_ungetch)
#else /* ... */
#undef __local___localdep__ungetch_defined
#endif /* !... */
#endif /* !__local___localdep__ungetch_defined */
__LOCAL_LIBC(_cgets_s) __ATTR_NONNULL((1, 3)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_cgets_s))(char *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ *__restrict __p_readsize) {
	int __ch;
	if __unlikely(!__bufsize)
		return 28;
	__buf[0]      = '\0';
	*__p_readsize = 0;
	--__bufsize;
	while (__bufsize && (__ch = (__NAMESPACE_LOCAL_SYM __localdep__getche)()) != -1) {
		if (__ch == '\r') {
			__ch = (__NAMESPACE_LOCAL_SYM __localdep__getche)();
			if (__ch != -1 && __ch != '\n')
				(__NAMESPACE_LOCAL_SYM __localdep__ungetch)(__ch);
			break;
		}
		if (__ch == '\n')
			break;
		*__buf++ = (char)(unsigned char)(unsigned int)__ch;
		*__buf   = '\0';
		++*__p_readsize;
		--__bufsize;
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__cgets_s_defined
#define __local___localdep__cgets_s_defined
#define __localdep__cgets_s __LIBC_LOCAL_NAME(_cgets_s)
#endif /* !__local___localdep__cgets_s_defined */
#else /* ((__CRT_HAVE__getch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__getch) && ((__CRT_HAVE__ungetch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__ungetch || (__CRT_HAVE_stdtty && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock))) */
#undef __local__cgets_s_defined
#endif /* ((!__CRT_HAVE__getch_nolock || !__USE_STDIO_UNLOCKED) && !__CRT_HAVE__getch) || ((!__CRT_HAVE__ungetch_nolock || !__USE_STDIO_UNLOCKED) && !__CRT_HAVE__ungetch && (!__CRT_HAVE_stdtty || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock))) */
#endif /* !__local__cgets_s_defined */
