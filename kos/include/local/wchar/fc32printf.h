/* HASH CRC-32:0x66a63b1f */
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
#ifndef __local_fc32printf_defined
#if (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf))
#define __local_fc32printf_defined 1
#include <kos/anno.h>
/* Dependency: "vfwprintf" from "wchar" */
#ifndef ____localdep_vfc32printf_defined
#define ____localdep_vfc32printf_defined 1
#if defined(__CRT_HAVE_vfwprintf) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vfc32printf,(__FILE *__restrict __stream, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/vfwprintf.h>
#define __localdep_vfc32printf(stream, format, args) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf))(stream, (__WCHAR_TYPE__ const *)(format), args)
#else /* LIBC: vfc32printf */
#include <local/wchar/vfc32printf.h>
#define __localdep_vfc32printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfc32printf))
#endif /* LIBC: vfc32printf */
#else /* CUSTOM: vfwprintf */
#undef ____localdep_vfc32printf_defined
#endif /* vfc32printf... */
#endif /* !____localdep_vfc32printf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fc32printf) __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(__VLIBCCALL __LIBC_LOCAL_NAME(fc32printf))(__FILE *__restrict __stream,
                                            __CHAR32_TYPE__ const *__restrict __format,
                                            ...) __THROWS(...) {
#line 544 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vfc32printf(__stream, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)) */
#endif /* !__local_fc32printf_defined */
