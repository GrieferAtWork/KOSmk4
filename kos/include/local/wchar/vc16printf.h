/* HASH CRC-32:0x99d71b5c */
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
#ifndef __local_vc16printf_defined
#if (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)) && !defined(__NO_STDSTREAMS)
#define __local_vc16printf_defined 1
#include <kos/anno.h>
#include <local/stdstreams.h>
/* Dependency: "vfwprintf" from "wchar" */
#ifndef ____localdep_vfc16printf_defined
#define ____localdep_vfc16printf_defined 1
#if defined(__CRT_HAVE_vfwprintf) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1, 2)) __ATTR_LIBC_WPRINTF(2, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vfc16printf,(__FILE *__restrict __stream, __CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_DOS$vfwprintf)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)) __ATTR_LIBC_WPRINTF(2, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vfc16printf,(__FILE *__restrict __stream, __CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/vfwprintf.h>
#define __localdep_vfc16printf(stream, format, args) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf))(stream, (__WCHAR_TYPE__ const *)(format), args)
#else /* LIBC: vfc16printf */
#include <local/wchar/vfc16printf.h>
#define __localdep_vfc16printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfc16printf))
#endif /* LIBC: vfc16printf */
#else /* CUSTOM: vfwprintf */
#undef ____localdep_vfc16printf_defined
#endif /* vfc16printf... */
#endif /* !____localdep_vfc16printf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vc16printf) __ATTR_NONNULL((1)) __ATTR_LIBC_WPRINTF(1, 0) __STDC_INT_AS_SIZE_T
(__LIBDCALL __LIBC_LOCAL_NAME(vc16printf))(__CHAR16_TYPE__ const *__restrict __format,
                                           __builtin_va_list __args) __THROWS(...) {
#line 655 "kos/src/libc/magic/wchar.c"
	return __localdep_vfc16printf(__LOCAL_stdout, __format, __args);
}
__NAMESPACE_LOCAL_END
#endif /* (__CRT_HAVE_fputwc || __CRT_HAVE_putwc || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_vfwprintf) && !__NO_STDSTREAMS */
#endif /* !__local_vc16printf_defined */
