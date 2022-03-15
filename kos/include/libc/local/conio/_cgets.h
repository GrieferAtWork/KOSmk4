/* HASH CRC-32:0xb64e48d3 */
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
#ifndef __local__cgets_defined
#define __local__cgets_defined
#include <__crt.h>
#include <features.h>
#if defined(__CRT_HAVE__cgets_s) || (((defined(__CRT_HAVE__getch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getch)) && ((defined(__CRT_HAVE__ungetch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__cgets_s_defined
#define __local___localdep__cgets_s_defined
#ifdef __CRT_HAVE__cgets_s
__CREDIRECT(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,__localdep__cgets_s,(char *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ *__restrict __p_readsize),_cgets_s,(__buf,__bufsize,__p_readsize))
#elif ((defined(__CRT_HAVE__getch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getch)) && ((defined(__CRT_HAVE__ungetch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))))
__NAMESPACE_LOCAL_END
#include <libc/local/conio/_cgets_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__cgets_s __LIBC_LOCAL_NAME(_cgets_s)
#else /* ... */
#undef __local___localdep__cgets_s_defined
#endif /* !... */
#endif /* !__local___localdep__cgets_s_defined */
__LOCAL_LIBC(_cgets) __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_cgets))(char *__restrict __buf) {
	char *__result = __buf + 2;
	__SIZE_TYPE__ __readsize;
	if ((__NAMESPACE_LOCAL_SYM __localdep__cgets_s)(__result, __buf[0], &__readsize) != 0)
		__result = __NULLPTR;
	__buf[1] = (char)(unsigned char)__readsize;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__cgets_defined
#define __local___localdep__cgets_defined
#define __localdep__cgets __LIBC_LOCAL_NAME(_cgets)
#endif /* !__local___localdep__cgets_defined */
#else /* __CRT_HAVE__cgets_s || (((__CRT_HAVE__getch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__getch) && ((__CRT_HAVE__ungetch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__ungetch || (__CRT_HAVE_stdtty && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock)))) */
#undef __local__cgets_defined
#endif /* !__CRT_HAVE__cgets_s && (((!__CRT_HAVE__getch_nolock || !__USE_STDIO_UNLOCKED) && !__CRT_HAVE__getch) || ((!__CRT_HAVE__ungetch_nolock || !__USE_STDIO_UNLOCKED) && !__CRT_HAVE__ungetch && (!__CRT_HAVE_stdtty || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock)))) */
#endif /* !__local__cgets_defined */
