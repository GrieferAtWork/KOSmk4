/* HASH CRC-32:0x9187f2c2 */
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
#ifndef __local_fgetc32s_unlocked_defined
#if (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE__fgetwc_nolock)) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE__ungetwc_nolock)) && (defined(__CRT_HAVE_ferror_unlocked) || defined(__CRT_HAVE_ferror))
#define __local_fgetc32s_unlocked_defined 1
#include <kos/anno.h>
#include <parts/errno.h>
/* Dependency: "fgetwc_unlocked" */
#ifndef ____localdep_fgetc32_unlocked_defined
#define ____localdep_fgetc32_unlocked_defined 1
#if defined(__CRT_HAVE_fgetwc_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#else /* LIBC: fgetc32_unlocked */
#undef ____localdep_fgetc32_unlocked_defined
#endif /* fgetc32_unlocked... */
#endif /* !____localdep_fgetc32_unlocked_defined */

/* Dependency: "ferror_unlocked" from "stdio" */
#ifndef ____localdep_ferror_unlocked_defined
#define ____localdep_ferror_unlocked_defined 1
#ifdef __CRT_HAVE_ferror_unlocked
/* Same as `ferror()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_ferror_unlocked,(__FILE *__restrict __stream),ferror_unlocked,(__stream))
#elif defined(__CRT_HAVE_ferror)
/* Same as `ferror()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_ferror_unlocked,(__FILE *__restrict __stream),ferror,(__stream))
#else /* LIBC: ferror_unlocked */
#undef ____localdep_ferror_unlocked_defined
#endif /* ferror_unlocked... */
#endif /* !____localdep_ferror_unlocked_defined */

/* Dependency: "ungetwc_unlocked" */
#ifndef ____localdep_ungetc32_unlocked_defined
#define ____localdep_ungetc32_unlocked_defined 1
#if defined(__CRT_HAVE_ungetwc_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetc32_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),ungetwc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetwc) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetc32_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),ungetwc,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetwc_nolock) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetc32_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),_ungetwc_nolock,(__ch,__stream))
#else /* LIBC: ungetc32_unlocked */
#undef ____localdep_ungetc32_unlocked_defined
#endif /* ungetc32_unlocked... */
#endif /* !____localdep_ungetc32_unlocked_defined */

__NAMESPACE_LOCAL_BEGIN
#ifndef __WEOF
#if 4 == 4
#define __WEOF 0xffffffffu
#else /* __SIZEOF_WCHAR_T__ == 4 */
#define __WEOF (__CCAST(__WINT_TYPE__) 0xffff)
#endif /* __SIZEOF_WCHAR_T__ != 4 */
#endif /* !__WEOF */
__LOCAL_LIBC(fgetc32s_unlocked) __ATTR_NONNULL((1, 3)) __CHAR32_TYPE__ *
(__LIBCCALL __LIBC_LOCAL_NAME(fgetc32s_unlocked))(__CHAR32_TYPE__ *__restrict __buf,
                                                  __STDC_INT_AS_SIZE_T __bufsize,
                                                  __FILE *__restrict __stream) __THROWS(...) {
#line 1059 "kos/src/libc/magic/wchar.c"
	__SIZE_TYPE__ __n;
	if __unlikely(!__buf || !__bufsize) {
		/* The buffer cannot be empty! */
#ifdef __ERANGE
		__libc_seterrno(__ERANGE);
#endif /* __ERANGE */
		return __NULLPTR;
	}
	for (__n = 0; __n < __bufsize - 1; ++__n) {
		__WINT_TYPE__ __ch = __localdep_fgetc32_unlocked(__stream);
		if (__ch == __WEOF) {
			if (__n == 0 || __localdep_ferror_unlocked(__stream))
				return __NULLPTR;
			break;
		}
		if (__ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			__buf[__n++] = '\n';
			__ch = __localdep_fgetc32_unlocked(__stream);
			if (__ch == __WEOF) {
				if (__n == 0 || __localdep_ferror_unlocked(__stream))
					return __NULLPTR;
				break;
			}
			if (__ch == '\r')
				continue;
			__localdep_ungetc32_unlocked(__ch, __stream);
			break;
		}
		__buf[__n] = (__CHAR32_TYPE__)__ch;
		if (__ch == '\n')
			break;
	}
	__buf[__n] = '\0';
	return __buf;
}
__NAMESPACE_LOCAL_END
#endif /* (__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE__fgetwc_nolock) && (__CRT_HAVE_ungetwc_unlocked || __CRT_HAVE_ungetwc || __CRT_HAVE__ungetwc_nolock) && (__CRT_HAVE_ferror_unlocked || __CRT_HAVE_ferror) */
#endif /* !__local_fgetc32s_unlocked_defined */
