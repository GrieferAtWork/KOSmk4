/* HASH CRC-32:0xafdd1a6a */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fgetc32s_defined
#define __local_fgetc32s_defined 1
#include <__crt.h>
#include <features.h>
#if ((defined(__CRT_HAVE_fgetwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fgetwc) || (defined(__CRT_HAVE_getwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$getwc)) && ((defined(__CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$ungetwc) || (defined(__CRT_HAVE_ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))
#include <kos/anno.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: ferror from stdio */
#ifndef __local___localdep_ferror_defined
#define __local___localdep_ferror_defined 1
#if defined(__CRT_HAVE_ferror_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Check if an I/O error occurred in `STREAM' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_ferror,(__FILE __KOS_FIXED_CONST *__restrict __stream),ferror_unlocked,(__stream))
#elif defined(__CRT_HAVE_ferror)
/* Check if an I/O error occurred in `STREAM' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_ferror,(__FILE __KOS_FIXED_CONST *__restrict __stream),ferror,(__stream))
#elif defined(__CRT_HAVE__IO_ferror)
/* Check if an I/O error occurred in `STREAM' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_ferror,(__FILE __KOS_FIXED_CONST *__restrict __stream),_IO_ferror,(__stream))
#elif defined(__CRT_HAVE_ferror_unlocked)
/* Check if an I/O error occurred in `STREAM' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_ferror,(__FILE __KOS_FIXED_CONST *__restrict __stream),ferror_unlocked,(__stream))
#else /* ... */
#undef __local___localdep_ferror_defined
#endif /* !... */
#endif /* !__local___localdep_ferror_defined */
/* Dependency: fgetc32 from parts.uchar.stdio */
#ifndef __local___localdep_fgetc32_defined
#define __local___localdep_fgetc32_defined 1
#if defined(__CRT_HAVE_fgetwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,__localdep_fgetc32,(__FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_KOS$fgetwc)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,__localdep_fgetc32,(__FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_getwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,__localdep_fgetc32,(__FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_KOS$getwc)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,__localdep_fgetc32,(__FILE *__restrict __stream),getwc,(__stream))
#else /* ... */
#undef __local___localdep_fgetc32_defined
#endif /* !... */
#endif /* !__local___localdep_fgetc32_defined */
/* Dependency: ungetc32 from parts.uchar.stdio */
#ifndef __local___localdep_ungetc32_defined
#define __local___localdep_ungetc32_defined 1
#if defined(__CRT_HAVE_ungetwc_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetc32,(__WINT_TYPE__ __wc, __FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_KOS$ungetwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT_KOS(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetc32,(__WINT_TYPE__ __wc, __FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetc32,(__WINT_TYPE__ __wc, __FILE *__stream),ungetwc,(__wc,__stream))
#elif defined(__CRT_HAVE_KOS$ungetwc)
__CREDIRECT_KOS(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetc32,(__WINT_TYPE__ __wc, __FILE *__stream),ungetwc,(__wc,__stream))
#elif defined(__CRT_HAVE_ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetc32,(__WINT_TYPE__ __wc, __FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_KOS$ungetwc_unlocked)
__CREDIRECT_KOS(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetc32,(__WINT_TYPE__ __wc, __FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#else /* ... */
#undef __local___localdep_ungetc32_defined
#endif /* !... */
#endif /* !__local___localdep_ungetc32_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
#include <asm/crt/stdio.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fgetc32s) __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __CHAR32_TYPE__ *
(__LIBKCALL __LIBC_LOCAL_NAME(fgetc32s))(__CHAR32_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream) __THROWS(...) {
	__SIZE_TYPE__ __n;
	if __unlikely(!__buf || !__bufsize) {
		/* The buffer cannot be empty! */
#ifdef __ERANGE
		__libc_seterrno(__ERANGE);
#endif /* __ERANGE */
		return __NULLPTR;
	}
	for (__n = 0; __n < __bufsize - 1; ++__n) {
		__WINT_TYPE__ __ch = __localdep_fgetc32(__stream);
		if (__ch == __WEOF32) {
			if (__n == 0 || __localdep_ferror(__stream))
				return __NULLPTR;
			break;
		}
		if (__ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			__buf[__n++] = '\n';
			__ch = __localdep_fgetc32(__stream);
			if (__ch == __WEOF32) {
				if (__n == 0 || __localdep_ferror(__stream))
					return __NULLPTR;
				break;
			}
			if (__ch == '\r')
				continue;
			__localdep_ungetc32(__ch, __stream);
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
#ifndef __local___localdep_fgetc32s_defined
#define __local___localdep_fgetc32s_defined 1
#define __localdep_fgetc32s __LIBC_LOCAL_NAME(fgetc32s)
#endif /* !__local___localdep_fgetc32s_defined */
#else /* ((__CRT_HAVE_fgetwc && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$fgetwc || (__CRT_HAVE_getwc && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$getwc) && ((__CRT_HAVE_ungetwc && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$ungetwc || (__CRT_HAVE_ungetwc_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$ungetwc_unlocked) && (__CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked) */
#undef __local_fgetc32s_defined
#endif /* ((!__CRT_HAVE_fgetwc || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$fgetwc && (!__CRT_HAVE_getwc || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$getwc) || ((!__CRT_HAVE_ungetwc || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$ungetwc && (!__CRT_HAVE_ungetwc_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$ungetwc_unlocked) || (!__CRT_HAVE_ferror && !__CRT_HAVE__IO_ferror && !__CRT_HAVE_ferror_unlocked) */
#endif /* !__local_fgetc32s_defined */
