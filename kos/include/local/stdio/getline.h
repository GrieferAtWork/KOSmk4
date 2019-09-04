/* HASH 0x9d546147 */
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
#ifndef __local_getline_defined
#if ((__has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)) || defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)))) && ((defined(__CRT_HAVE_ungetc_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_ungetc)) || defined(__CRT_HAVE_getdelim) || defined(__CRT_HAVE_getdelim_unlocked))
#define __local_getline_defined 1
#include <kos/anno.h>
/* Dependency: "getdelim" from "stdio" */
#ifndef ____localdep_getdelim_defined
#define ____localdep_getdelim_defined 1
#if defined(__CRT_HAVE_getdelim_unlocked) && (defined(__USE_STDIO_UNLOCKED))
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,,__localdep_getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),getdelim_unlocked,(__lineptr,__pcount,__delimiter,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_getdelim)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,,__localdep_getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),getdelim,(__lineptr,__pcount,__delimiter,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_getdelim_unlocked)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,,__localdep_getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),getdelim_unlocked,(__lineptr,__pcount,__delimiter,__stream)) __THROWS(...)
#elif (__has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)) || defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)))) && ((defined(__CRT_HAVE_ungetc_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_ungetc))
#include <local/stdio/getdelim.h>
#define __localdep_getdelim (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getdelim))
#else /* CUSTOM: getdelim */
#undef ____localdep_getdelim_defined
#endif /* getdelim... */
#endif /* !____localdep_getdelim_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getline) __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)) __SSIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(getline))(char **__restrict __lineptr,
                                        __SIZE_TYPE__ *__restrict __pcount,
                                        __FILE *__restrict __stream) __THROWS(...) {
#line 1270 "kos/src/libc/magic/stdio.c"
	return __localdep_getdelim(__lineptr, __pcount, '\n', __stream);
}
__NAMESPACE_LOCAL_END
#endif /* ((__has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)) || defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)))) && ((defined(__CRT_HAVE_ungetc_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_ungetc)) || defined(__CRT_HAVE_getdelim) || defined(__CRT_HAVE_getdelim_unlocked)) */
#endif /* !__local_getline_defined */
