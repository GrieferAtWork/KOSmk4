/* HASH CRC-32:0x9fcc6ef1 */
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
#ifndef __local__vscanf_l_defined
#if (!defined(__NO_STDSTREAMS) && ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)))) && ((defined(__CRT_HAVE_ungetc_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_ungetc)) || (__has_builtin(__builtin_vfscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfscanf)) || (defined(__CRT_HAVE_vfscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE___vfscanf)) || (__has_builtin(__builtin_vscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vscanf)) || (defined(__CRT_HAVE_vscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vscanf) || defined(__CRT_HAVE__vscanf))
#define __local__vscanf_l_defined 1
#include <kos/anno.h>
/* Dependency: "vscanf" from "stdio" */
#ifndef ____localdep_vscanf_defined
#define ____localdep_vscanf_defined 1
#ifdef __std___localdep_vscanf_defined
__NAMESPACE_STD_USING(__localdep_vscanf)
#elif __has_builtin(__builtin_vscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vscanf)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_LIBC_SCANF(1, 0) __STDC_INT_AS_SIZE_T (__LIBCCALL __localdep_vscanf)(char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return __builtin_vscanf(__format, __args); }
#elif defined(__CRT_HAVE_vscanf_unlocked) && (defined(__USE_STDIO_UNLOCKED))
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_LIBC_SCANF(1, 0),__STDC_INT_AS_SIZE_T,,__localdep_vscanf,(char const *__restrict __format, __builtin_va_list __args),vscanf_unlocked,(__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vscanf)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_LIBC_SCANF(1, 0),__STDC_INT_AS_SIZE_T,,__localdep_vscanf,(char const *__restrict __format, __builtin_va_list __args),vscanf,(__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE__vscanf)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_LIBC_SCANF(1, 0),__STDC_INT_AS_SIZE_T,,__localdep_vscanf,(char const *__restrict __format, __builtin_va_list __args),_vscanf,(__format,__args)) __THROWS(...)
#elif !defined(__NO_STDSTREAMS) && ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)))) && ((defined(__CRT_HAVE_ungetc_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_ungetc)) || (__has_builtin(__builtin_vfscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfscanf)) || (defined(__CRT_HAVE_vfscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE___vfscanf))
#include <local/stdio/vscanf.h>
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
#define __localdep_vscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vscanf))
#else /* CUSTOM: vscanf */
#undef ____localdep_vscanf_defined
#endif /* vscanf... */
#endif /* !____localdep_vscanf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_vscanf_l) __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_LIBC_SCANF(1, 3) __STDC_INT_AS_SIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(_vscanf_l))(char const *__restrict __format,
                                          __locale_t __locale,
                                          __builtin_va_list __args) __THROWS(...) {
#line 2162 "kos/src/libc/magic/stdio.c"
	(void)__locale;
	return __localdep_vscanf(__format, __args);
}
__NAMESPACE_LOCAL_END
#endif /* (!defined(__NO_STDSTREAMS) && ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)))) && ((defined(__CRT_HAVE_ungetc_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_ungetc)) || (__has_builtin(__builtin_vfscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfscanf)) || (defined(__CRT_HAVE_vfscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE___vfscanf)) || (__has_builtin(__builtin_vscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vscanf)) || (defined(__CRT_HAVE_vscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vscanf) || defined(__CRT_HAVE__vscanf)) */
#endif /* !__local__vscanf_l_defined */
