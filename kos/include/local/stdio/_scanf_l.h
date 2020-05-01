/* HASH CRC-32:0x11682fca */
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
#ifndef __local__scanf_l_defined
#if (!defined(__NO_STDSTREAMS) && ((((defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf))) || defined(__CRT_HAVE_vscanf) || defined(__CRT_HAVE__vscanf) || defined(__CRT_HAVE_vscanf_unlocked) || defined(__CRT_HAVE__vscanf_l) || defined(__CRT_HAVE__vscanf_s_l)
#define __local__scanf_l_defined 1
#include <__crt.h>
#include <kos/anno.h>
/* Dependency: "_vscanf_l" from "stdio" */
#ifndef ____localdep__vscanf_l_defined
#define ____localdep__vscanf_l_defined 1
#ifdef __CRT_HAVE__vscanf_l
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 3) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,,__localdep__vscanf_l,(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),_vscanf_l,(__format,__locale,__args)) __THROWS(...)
#elif defined(__CRT_HAVE__vscanf_s_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 3) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,,__localdep__vscanf_l,(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),_vscanf_s_l,(__format,__locale,__args)) __THROWS(...)
#elif (!defined(__NO_STDSTREAMS) && ((((defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf))) || defined(__CRT_HAVE_vscanf) || defined(__CRT_HAVE__vscanf) || defined(__CRT_HAVE_vscanf_unlocked)
#include <local/stdio/_vscanf_l.h>
#define __localdep__vscanf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscanf_l))
#else /* CUSTOM: _vscanf_l */
#undef ____localdep__vscanf_l_defined
#endif /* _vscanf_l... */
#endif /* !____localdep__vscanf_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_scanf_l) __ATTR_LIBC_SCANF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T
(__VLIBCCALL __LIBC_LOCAL_NAME(_scanf_l))(char const *__restrict __format,
                                          __locale_t __locale,
                                          ...) __THROWS(...) {
#line 2340 "kos/src/libc/magic/stdio.c"
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __locale);
	__result = __localdep__vscanf_l(__format, __locale, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* (!__NO_STDSTREAMS && ((((__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread || __CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock)) || __CRT_HAVE_vfscanf || __CRT_HAVE__vfscanf || __CRT_HAVE__vfscanf_s || __CRT_HAVE__IO_vfscanf || __CRT_HAVE_vfscanf_unlocked || __CRT_HAVE___vfscanf)) || __CRT_HAVE_vscanf || __CRT_HAVE__vscanf || __CRT_HAVE_vscanf_unlocked || __CRT_HAVE__vscanf_l || __CRT_HAVE__vscanf_s_l */
#endif /* !__local__scanf_l_defined */
