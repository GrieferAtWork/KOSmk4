/* HASH CRC-32:0x813c4c02 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fwprintf_s_defined
#if defined(__CRT_HAVE_vfwprintf_s)
#define __local_fwprintf_s_defined 1
/* Dependency: "vfwprintf_s" */
#ifndef ____localdep_vfwprintf_s_defined
#define ____localdep_vfwprintf_s_defined 1
#if defined(__CRT_HAVE_vfwprintf_s)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_vfwprintf_s,(__FILE *__stream, __WCHAR_TYPE__ const *__format, __builtin_va_list __args),vfwprintf_s,(__stream,__format,__args))
#else /* LIBC: vfwprintf_s */
#undef ____localdep_vfwprintf_s_defined
#endif /* vfwprintf_s... */
#endif /* !____localdep_vfwprintf_s_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fwprintf_s) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(fwprintf_s))(__FILE *__stream,
                                                         __WCHAR_TYPE__ const *__format,
                                                         ...) {
#line 1701 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vfwprintf_s(__stream, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_vfwprintf_s) */
#endif /* !__local_fwprintf_s_defined */
