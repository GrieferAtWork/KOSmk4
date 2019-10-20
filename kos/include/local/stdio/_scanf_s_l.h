/* HASH CRC-32:0x11321f44 */
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
#ifndef __local__scanf_s_l_defined
#if (defined(__CRT_HAVE__vscanf_s_l) || defined(__CRT_HAVE__vscanf_l) || (!defined(__NO_STDSTREAMS) && ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)))) && ((defined(__CRT_HAVE_ungetc_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_ungetc)) || (__has_builtin(__builtin_vfscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfscanf)) || (defined(__CRT_HAVE_vfscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s)) || (__has_builtin(__builtin_vscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vscanf)) || (defined(__CRT_HAVE_vscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vscanf) || defined(__CRT_HAVE__vscanf)))
#define __local__scanf_s_l_defined 1
#include <kos/anno.h>
/* Dependency: "_vscanf_s_l" from "stdio" */
#ifndef ____localdep__vscanf_s_l_defined
#define ____localdep__vscanf_s_l_defined 1
#if defined(__CRT_HAVE__vscanf_s_l)
__CREDIRECT(__ATTR_LIBC_SCANF(1, 3) __ATTR_WUNUSED __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,,__localdep__vscanf_s_l,(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),_vscanf_s_l,(__format,__locale,__args)) __THROWS(...)
#elif defined(__CRT_HAVE__vscanf_l)
__CREDIRECT(__ATTR_LIBC_SCANF(1, 3) __ATTR_WUNUSED __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,,__localdep__vscanf_s_l,(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),_vscanf_l,(__format,__locale,__args)) __THROWS(...)
#elif (!defined(__NO_STDSTREAMS) && ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)))) && ((defined(__CRT_HAVE_ungetc_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_ungetc)) || (__has_builtin(__builtin_vfscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfscanf)) || (defined(__CRT_HAVE_vfscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s)) || (__has_builtin(__builtin_vscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vscanf)) || (defined(__CRT_HAVE_vscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vscanf) || defined(__CRT_HAVE__vscanf))
#include <local/stdio/_vscanf_l.h>
#define __localdep__vscanf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscanf_l))
#else /* CUSTOM: _vscanf_l */
#undef ____localdep__vscanf_s_l_defined
#endif /* _vscanf_s_l... */
#endif /* !____localdep__vscanf_s_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_scanf_s_l) __ATTR_LIBC_SCANF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T
(__VLIBCCALL __LIBC_LOCAL_NAME(_scanf_s_l))(char const *__restrict __format,
                                            __locale_t __locale,
                                            ...) __THROWS(...) {
#line 2158 "kos/src/libc/magic/stdio.c"
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __locale);
	__result = __localdep__vscanf_s_l(__format, __locale, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE__vscanf_s_l) || defined(__CRT_HAVE__vscanf_l) || (!defined(__NO_STDSTREAMS) && ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)))) && ((defined(__CRT_HAVE_ungetc_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_ungetc)) || (__has_builtin(__builtin_vfscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfscanf)) || (defined(__CRT_HAVE_vfscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s)) || (__has_builtin(__builtin_vscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vscanf)) || (defined(__CRT_HAVE_vscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vscanf) || defined(__CRT_HAVE__vscanf))) */
#endif /* !__local__scanf_s_l_defined */
