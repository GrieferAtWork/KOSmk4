/* HASH CRC-32:0x9dfc2dfe */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_printf_defined
#define __local_printf_defined
#include <__crt.h>
#include <features.h>
#include <libc/template/stdstreams.h>
#if defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vprintf_defined
#define __local___localdep_vprintf_defined
#if defined(__CRT_HAVE_vprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 0),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_vprintf,(char const *__restrict __format, __builtin_va_list __args),vprintf_unlocked,(__format,__args))
#elif __has_builtin(__builtin_vprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vprintf)
__CEIREDIRECT(__ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 0),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_vprintf,(char const *__restrict __format, __builtin_va_list __args),vprintf,{ return __builtin_vprintf(__format, __args); })
#elif defined(__CRT_HAVE_vprintf)
__CREDIRECT(__ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 0),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_vprintf,(char const *__restrict __format, __builtin_va_list __args),vprintf,(__format,__args))
#elif defined(__CRT_HAVE_vprintf_s)
__CREDIRECT(__ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 0),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_vprintf,(char const *__restrict __format, __builtin_va_list __args),vprintf_s,(__format,__args))
#elif defined(__CRT_HAVE_vprintf_unlocked)
__CREDIRECT(__ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 0),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_vprintf,(char const *__restrict __format, __builtin_va_list __args),vprintf_unlocked,(__format,__args))
#elif defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/vprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vprintf __LIBC_LOCAL_NAME(vprintf)
#else /* ... */
#undef __local___localdep_vprintf_defined
#endif /* !... */
#endif /* !__local___localdep_vprintf_defined */
__LOCAL_LIBC(printf) __ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 2) __STDC_INT_AS_SSIZE_T
(__VLIBCCALL __LIBC_LOCAL_NAME(printf))(char const *__restrict __format, ...) __THROWS(...) {
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = (__NAMESPACE_LOCAL_SYM __localdep_vprintf)(__format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_printf_defined
#define __local___localdep_printf_defined
#define __localdep_printf __LIBC_LOCAL_NAME(printf)
#endif /* !__local___localdep_printf_defined */
#else /* __CRT_HAVE_vprintf || __CRT_HAVE_vprintf_s || __CRT_HAVE_vprintf_unlocked || (__LOCAL_stdout && (__CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock)) */
#undef __local_printf_defined
#endif /* !__CRT_HAVE_vprintf && !__CRT_HAVE_vprintf_s && !__CRT_HAVE_vprintf_unlocked && (!__LOCAL_stdout || (!__CRT_HAVE_vfprintf && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock)) */
#endif /* !__local_printf_defined */
