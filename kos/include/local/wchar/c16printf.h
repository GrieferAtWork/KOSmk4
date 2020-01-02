/* HASH CRC-32:0xbd7b26ef */
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
#ifndef __local_c16printf_defined
#if ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)) && !defined(__NO_STDSTREAMS)) || defined(__CRT_HAVE_vwprintf)
#define __local_c16printf_defined 1
#include <kos/anno.h>
/* Dependency: "vwprintf" from "wchar" */
#ifndef ____localdep_vc16printf_defined
#define ____localdep_vc16printf_defined 1
#if defined(__CRT_HAVE_vwprintf) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)) __ATTR_LIBC_WPRINTF(1, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vc16printf,(__CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vwprintf,(__format,__args))
#elif defined(__CRT_HAVE_DOS$vwprintf)
__CREDIRECT_DOS(__ATTR_NONNULL((1)) __ATTR_LIBC_WPRINTF(1, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vc16printf,(__CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vwprintf,(__format,__args))
#elif (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)) && !defined(__NO_STDSTREAMS)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/vwprintf.h>
#define __localdep_vc16printf(format, args) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwprintf))((__WCHAR_TYPE__ const *)(format), args)
#else /* LIBC: vc16printf */
#include <local/wchar/vc16printf.h>
#define __localdep_vc16printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vc16printf))
#endif /* LIBC: vc16printf */
#else /* CUSTOM: vwprintf */
#undef ____localdep_vc16printf_defined
#endif /* vc16printf... */
#endif /* !____localdep_vc16printf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16printf) __ATTR_NONNULL((1)) __ATTR_LIBC_WPRINTF(1, 2) __STDC_INT_AS_SIZE_T
(__VLIBDCALL __LIBC_LOCAL_NAME(c16printf))(__CHAR16_TYPE__ const *__restrict __format,
                                           ...) __THROWS(...) {
#line 648 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vc16printf(__format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* ((__CRT_HAVE_fputwc || __CRT_HAVE_putwc || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_vfwprintf) && !__NO_STDSTREAMS) || __CRT_HAVE_vwprintf */
#endif /* !__local_c16printf_defined */
