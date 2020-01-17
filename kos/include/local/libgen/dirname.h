/* HASH CRC-32:0xc5587d49 */
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
#ifndef __local_dirname_defined
#define __local_dirname_defined 1
/* Dependency: "strrchr" from "string" */
#ifndef ____localdep_strrchr_defined
#define ____localdep_strrchr_defined 1
#if __has_builtin(__builtin_strrchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strrchr)
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__EXTERNINLINE __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL __localdep_strrchr)(char const *__restrict __haystack, int __needle) { return __builtin_strrchr(__haystack, __needle); }
#elif defined(__CRT_HAVE_strrchr)
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strrchr,(char const *__restrict __haystack, int __needle),strrchr,(__haystack,__needle))
#else /* LIBC: strrchr */
#include <local/string/strrchr.h>
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
#define __localdep_strrchr (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchr))
#endif /* strrchr... */
#endif /* !____localdep_strrchr_defined */

/* Dependency: "memrchr" from "string" */
#ifndef ____localdep_memrchr_defined
#define ____localdep_memrchr_defined 1
#ifdef __CRT_HAVE_memrchr
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memrchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrchr,(__haystack,__needle,__n_bytes))
#else /* LIBC: memrchr */
#include <local/string/memrchr.h>
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memrchr (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr))
#endif /* memrchr... */
#endif /* !____localdep_memrchr_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return directory part of PATH or "." if none is available */
__LOCAL_LIBC(dirname) __ATTR_RETNONNULL char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(dirname))(char *__path) {
#line 34 "kos/src/libc/magic/libgen.c"
	/* NOTE: This implementation is taken from GLibc */
	/* dirname - return directory part of PATH.
	   Copyright (C) 1996-2017 Free Software Foundation, Inc.
	   This file is part of the GNU C Library.
	   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1996.
	
	   The GNU C Library is free software; you can redistribute it and/or
	   modify it under the terms of the GNU Lesser General Public
	   License as published by the Free Software Foundation; either
	   version 2.1 of the License, or (at your option) any later version.
	
	   The GNU C Library is distributed in the hope that it will be useful,
	   but WITHOUT ANY WARRANTY; without even the implied warranty of
	   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	   Lesser General Public License for more details.
	
	   You should have received a copy of the GNU Lesser General Public
	   License along with the GNU C Library; if not, see
	   <http://www.gnu.org/licenses/>.  */
	char *__last_slash;
	__last_slash = __path ? __localdep_strrchr(__path, '/') : __NULLPTR;
	if (__last_slash && __last_slash != __path && __last_slash[1] == '\0') {
		char *__runp;
		for (__runp = __last_slash; __runp != __path; --__runp) {
			if (__runp[-1] != '/')
				break;
		}
		if (__runp != __path)
			__last_slash = (char *)__localdep_memrchr(__path, '/', (__SIZE_TYPE__)(__runp - __path));
	}
	if (__last_slash) {
		char *__runp;
		for (__runp = __last_slash; __runp != __path; --__runp) {
			if (__runp[-1] != '/')
				break;
		}
		if (__runp == __path) {
			if (__last_slash == __path + 1)
				++__last_slash;
			else {
				__last_slash = __path + 1;
			}
		} else {
			__last_slash = __runp;
		}
		__last_slash[0] = '\0';
	} else {
		__path = (char *)".";
	}
	return __path;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_dirname_defined */
