/* HASH CRC-32:0x2d54d825 */
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
#ifndef __local_fgets_unlocked_defined
#if ((defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf)))) && (defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc)) && (defined(__CRT_HAVE_ferror_unlocked) || defined(__CRT_HAVE_ferror))
#define __local_fgets_unlocked_defined 1
#include <__crt.h>
#include <kos/anno.h>
#include <parts/errno.h>
/* Dependency: "fgetc_unlocked" from "stdio" */
#ifndef ____localdep_fgetc_unlocked_defined
#define ____localdep_fgetc_unlocked_defined 1
#ifdef __CRT_HAVE_fgetc_unlocked
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),fgetc_unlocked,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_getc_unlocked)
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),getc_unlocked,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),getc,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),fgetc,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),_IO_getc,(__stream)) __THROWS(...)
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)
#include <local/stdio/fgetc_unlocked.h>
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
#define __localdep_fgetc_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc_unlocked))
#else /* CUSTOM: fgetc_unlocked */
#undef ____localdep_fgetc_unlocked_defined
#endif /* fgetc_unlocked... */
#endif /* !____localdep_fgetc_unlocked_defined */

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

/* Dependency: "ungetc_unlocked" from "stdio" */
#ifndef ____localdep_ungetc_unlocked_defined
#define ____localdep_ungetc_unlocked_defined 1
#ifdef __CRT_HAVE_ungetc_unlocked
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc_unlocked,(int __ch, __FILE *__restrict __stream),ungetc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetc_nolock)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc_unlocked,(int __ch, __FILE *__restrict __stream),_ungetc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_ungetc)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc_unlocked,(int __ch, __FILE *__restrict __stream),_IO_ungetc,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetc)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc_unlocked,(int __ch, __FILE *__restrict __stream),ungetc,(__ch,__stream))
#else /* LIBC: ungetc_unlocked */
#undef ____localdep_ungetc_unlocked_defined
#endif /* ungetc_unlocked... */
#endif /* !____localdep_ungetc_unlocked_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `fgets()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__LOCAL_LIBC(fgets_unlocked) __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) char *
(__LIBCCALL __LIBC_LOCAL_NAME(fgets_unlocked))(char *__restrict __buf,
                                               __STDC_INT_AS_SIZE_T __bufsize,
                                               __FILE *__restrict __stream) __THROWS(...) {
#line 1461 "kos/src/libc/magic/stdio.c"
	__SIZE_TYPE__ __n;
	if __unlikely(!__buf || !__bufsize) {
		/* The buffer cannot be empty! */
#ifdef __ERANGE
		__libc_seterrno(__ERANGE);
#endif /* ERANGE */
		return __NULLPTR;
	}
	for (__n = 0; __n < __bufsize - 1; ++__n) {
		int __ch = __localdep_fgetc_unlocked(__stream);
		if (__ch == __EOF) {
			if (__n == 0 || __localdep_ferror_unlocked(__stream))
				return __NULLPTR;
			break;
		}
		if (__ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			__buf[__n++] = '\n';
			__ch = __localdep_fgetc_unlocked(__stream);
			if (__ch == __EOF) {
				if (__n == 0 || __localdep_ferror_unlocked(__stream))
					return __NULLPTR;
				break;
			}
			if (__ch == '\r')
				continue;
			__localdep_ungetc_unlocked(__ch, __stream);
			break;
		}
		__buf[__n] = (char)__ch;
		if (__ch == '\n')
			break;
	}
	__buf[__n] = '\0';
	return __buf;
}
__NAMESPACE_LOCAL_END
#endif /* ((__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread || __CRT_HAVE_fread || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_HAVE_getc && (!__CRT_DOS || !__CRT_HAVE__filbuf)) || (__CRT_HAVE_fgetc && (!__CRT_DOS || !__CRT_HAVE__filbuf)) || (__CRT_HAVE__IO_getc && (!__CRT_DOS || !__CRT_HAVE__filbuf))) && (__CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc) && (__CRT_HAVE_ferror_unlocked || __CRT_HAVE_ferror) */
#endif /* !__local_fgets_unlocked_defined */
