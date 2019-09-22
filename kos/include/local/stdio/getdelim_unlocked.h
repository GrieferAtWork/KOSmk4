/* HASH CRC-32:0x1b30b045 */
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
#ifndef __local_getdelim_unlocked_defined
#if ((__has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)) || defined(__CRT_HAVE_realloc)) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_s)) && (defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE_ungetc))
#define __local_getdelim_unlocked_defined 1
#include <kos/anno.h>
/* Dependency: "realloc" */
#ifndef ____localdep_realloc_defined
#define ____localdep_realloc_defined 1
#ifdef __std___localdep_realloc_defined
__NAMESPACE_STD_USING(__localdep_realloc)
#elif __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__FORCELOCAL __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL __localdep_realloc)(void *__mallptr, __SIZE_TYPE__ __n_bytes) { return __builtin_realloc(__mallptr, __n_bytes); }
#elif defined(__CRT_HAVE_realloc)
__CREDIRECT(__ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __n_bytes),realloc,(__mallptr,__n_bytes))
#else /* LIBC: realloc */
#undef ____localdep_realloc_defined
#endif /* realloc... */
#endif /* !____localdep_realloc_defined */

/* Dependency: "fgetc_unlocked" from "stdio" */
#ifndef ____localdep_fgetc_unlocked_defined
#define ____localdep_fgetc_unlocked_defined 1
#if defined(__CRT_HAVE_fgetc_unlocked)
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
#elif ((defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_s))
#include <local/stdio/fgetc_unlocked.h>
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
#define __localdep_fgetc_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc_unlocked))
#else /* CUSTOM: fgetc_unlocked */
#undef ____localdep_fgetc_unlocked_defined
#endif /* fgetc_unlocked... */
#endif /* !____localdep_fgetc_unlocked_defined */

/* Dependency: "ungetc_unlocked" from "stdio" */
#ifndef ____localdep_ungetc_unlocked_defined
#define ____localdep_ungetc_unlocked_defined 1
#if defined(__CRT_HAVE_ungetc_unlocked)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc_unlocked,(int __ch, __FILE *__restrict __stream),ungetc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetc)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc_unlocked,(int __ch, __FILE *__restrict __stream),ungetc,(__ch,__stream))
#else /* LIBC: ungetc_unlocked */
#undef ____localdep_ungetc_unlocked_defined
#endif /* ungetc_unlocked... */
#endif /* !____localdep_ungetc_unlocked_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getdelim_unlocked) __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)) __SSIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(getdelim_unlocked))(char **__restrict __lineptr,
                                                  __SIZE_TYPE__ *__restrict __pcount,
                                                  int __delimiter,
                                                  __FILE *__restrict __stream) __THROWS(...) {
#line 1774 "kos/src/libc/magic/stdio.c"
	int __ch;
	char *__buffer;
	__SIZE_TYPE__ __bufsize, __result = 0;
	__buffer  = *__lineptr;
	__bufsize = __buffer ? *__pcount : 0;
	for (;;) {
		if (__result + 1 >= __bufsize) {
			/* Allocate more memory. */
			__SIZE_TYPE__ __new_bufsize = __bufsize * 2;
			if (__new_bufsize <= __result + 1)
				__new_bufsize = 16;
			__assert(__new_bufsize > __result + 1);
			__buffer = (char *)__localdep_realloc(__buffer,
			                         __new_bufsize *
			                         sizeof(char));
			if __unlikely(!__buffer)
				return -1;
			*__lineptr = __buffer;
			*__pcount  = __bufsize;
		}
		__ch = __localdep_fgetc_unlocked(__stream);
		if (__ch == __EOF)
			break; /* EOF */
		__buffer[__result++] = (char)__ch;
		if (__ch == __delimiter)
			break; /* Delimiter reached */
		/* Special case for line-delimiter. */
		if (__delimiter == '\n' && __ch == '\r') {
			/* Deal with '\r\n', as well as '\r' */
			__ch = __localdep_fgetc_unlocked(__stream);
			if (__ch != __EOF && __ch != '\n')
				__localdep_ungetc_unlocked(__ch, __stream);
			/* Unify linefeeds (to use POSIX notation) */
			__buffer[__result - 1] = '\n';
			break;
		}
	}
	/* NUL-Terminate the buffer. */
	__buffer[__result] = '\0';
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* ((__has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)) || defined(__CRT_HAVE_realloc)) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_s)) && (defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE_ungetc)) */
#endif /* !__local_getdelim_unlocked_defined */
