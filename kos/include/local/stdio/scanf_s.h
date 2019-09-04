/* HASH 0x11886d2e */
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
#ifndef __local_scanf_s_defined
#if defined(__CRT_HAVE_vscanf_s)
#define __local_scanf_s_defined 1
#include <kos/anno.h>
/* Dependency: "vscanf_s" */
#ifndef ____localdep_vscanf_s_defined
#define ____localdep_vscanf_s_defined 1
#if defined(__CRT_HAVE_vscanf_s)
__CREDIRECT(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,,__localdep_vscanf_s,(char const *__restrict __format, __builtin_va_list __args),vscanf_s,(__format,__args)) __THROWS(...)
#else /* LIBC: vscanf_s */
#undef ____localdep_vscanf_s_defined
#endif /* vscanf_s... */
#endif /* !____localdep_vscanf_s_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(scanf_s) __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T
(__VLIBCCALL __LIBC_LOCAL_NAME(scanf_s))(char const *__restrict __format,
                                         ...) __THROWS(...) {
#line 2489 "kos/src/libc/magic/stdio.c"
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vscanf_s(__format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_vscanf_s) */
#endif /* !__local_scanf_s_defined */
