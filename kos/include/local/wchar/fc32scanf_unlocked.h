/* HASH CRC-32:0x2074731d */
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
#ifndef __local_fc32scanf_unlocked_defined
#if defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf)
#define __local_fc32scanf_unlocked_defined 1
#include <kos/anno.h>
/* Dependency: "vfwscanf_unlocked" */
#ifndef ____localdep_vfc32scanf_unlocked_defined
#define ____localdep_vfc32scanf_unlocked_defined 1
#if defined(__CRT_HAVE_vfwscanf_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vfc32scanf_unlocked,(__FILE *__restrict __stream, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwscanf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfwscanf) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vfc32scanf_unlocked,(__FILE *__restrict __stream, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#else /* LIBC: vfc32scanf_unlocked */
#undef ____localdep_vfc32scanf_unlocked_defined
#endif /* vfc32scanf_unlocked... */
#endif /* !____localdep_vfc32scanf_unlocked_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fc32scanf_unlocked) __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(__VLIBCCALL __LIBC_LOCAL_NAME(fc32scanf_unlocked))(__FILE *__restrict __stream,
                                                    __CHAR32_TYPE__ const *__restrict __format,
                                                    ...) __THROWS(...) {
#line 1223 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vfc32scanf_unlocked(__stream, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_vfwscanf_unlocked || __CRT_HAVE_vfwscanf */
#endif /* !__local_fc32scanf_unlocked_defined */
