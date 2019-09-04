/* HASH 0x3dd112f1 */
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
#ifndef __local__vfscanf_l_defined
#if (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock))) && ((defined(__CRT_HAVE_ungetc_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_ungetc)) || (__has_builtin(__builtin_vfscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfscanf)) || (defined(__CRT_HAVE_vfscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s))
#define __local__vfscanf_l_defined 1
#include <kos/anno.h>
/* Dependency: "vfscanf" from "stdio" */
#ifndef ____localdep_vfscanf_defined
#define ____localdep_vfscanf_defined 1
#ifdef __std___localdep_vfscanf_defined
__NAMESPACE_STD_USING(__localdep_vfscanf)
#elif __has_builtin(__builtin_vfscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfscanf)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__FORCELOCAL __ATTR_LIBC_SCANF(2, 0) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL __localdep_vfscanf)(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return __builtin_vfscanf(__stream, __format, __args); }
#elif defined(__CRT_HAVE_vfscanf_unlocked) && (defined(__USE_STDIO_UNLOCKED))
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_LIBC_SCANF(2, 0) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,,__localdep_vfscanf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfscanf_unlocked,(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vfscanf)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_LIBC_SCANF(2, 0) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,,__localdep_vfscanf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfscanf,(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE__vfscanf)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_LIBC_SCANF(2, 0) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,,__localdep_vfscanf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_vfscanf,(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE__vfscanf_s)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_LIBC_SCANF(2, 0) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,,__localdep_vfscanf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_vfscanf_s,(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock))) && ((defined(__CRT_HAVE_ungetc_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_ungetc))
#include <local/stdio/vfscanf.h>
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
#define __localdep_vfscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfscanf))
#else /* CUSTOM: vfscanf */
#undef ____localdep_vfscanf_defined
#endif /* vfscanf... */
#endif /* !____localdep_vfscanf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_vfscanf_l) __ATTR_LIBC_SCANF(2, 4) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(_vfscanf_l))(__FILE *__restrict __stream,
                                           char const *__restrict __format,
                                           __locale_t __locale,
                                           __builtin_va_list __args) __THROWS(...) {
#line 2054 "kos/src/libc/magic/stdio.c"
	(void)__locale;
	return __localdep_vfscanf(__stream, __format, __args);
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock))) && ((defined(__CRT_HAVE_ungetc_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_ungetc)) || (__has_builtin(__builtin_vfscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfscanf)) || (defined(__CRT_HAVE_vfscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s)) */
#endif /* !__local__vfscanf_l_defined */
