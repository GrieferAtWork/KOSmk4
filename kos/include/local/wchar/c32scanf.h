/* HASH CRC-32:0xa179cf09 */
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
#ifndef __local_c32scanf_defined
#if (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)) || defined(__CRT_HAVE_vwscanf)
#define __local_c32scanf_defined 1
#include <__crt.h>
#include <kos/anno.h>
/* Dependency: "vwscanf" from "wchar" */
#ifndef ____localdep_vc32scanf_defined
#define ____localdep_vc32scanf_defined 1
#if defined(__CRT_HAVE_vwscanf) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vc32scanf,(__CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vwscanf,(__format,__args))
#elif defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/vwscanf.h>
#define __localdep_vc32scanf (*(__STDC_INT_AS_SIZE_T(__LIBCCALL*)(__CHAR32_TYPE__ const *__restrict, __builtin_va_list))&(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf)))
#else /* LIBC: vc32scanf */
#include <local/wchar/vc32scanf.h>
#define __localdep_vc32scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vc32scanf))
#endif /* LIBC: vc32scanf */
#else /* CUSTOM: vwscanf */
#undef ____localdep_vc32scanf_defined
#endif /* vc32scanf... */
#endif /* !____localdep_vc32scanf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32scanf) __ATTR_LIBC_WSCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T
(__VLIBCCALL __LIBC_LOCAL_NAME(c32scanf))(__CHAR32_TYPE__ const *__restrict __format,
                                          ...) __THROWS(...) {
#line 707 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vc32scanf(__format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* (__CRT_HAVE_vfwscanf && !__NO_STDSTREAMS) || __CRT_HAVE_vwscanf */
#endif /* !__local_c32scanf_defined */
