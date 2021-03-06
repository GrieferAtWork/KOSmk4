/* HASH CRC-32:0xec5b78c3 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_errc_defined
#define __local_errc_defined 1
#include <__crt.h>
#include <libc/local/program_invocation_name.h>
#include <features.h>
#if defined(__CRT_HAVE_verrc) || ((defined(__CRT_HAVE_vwarnc) || (!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)))
#include <kos/anno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: verrc from err */
#ifndef __local___localdep_verrc_defined
#define __local___localdep_verrc_defined 1
#ifdef __CRT_HAVE_verrc
/* Same as `warnc()', but follow up by calling `exit(status)' */
__CREDIRECT_VOID(__ATTR_NORETURN __ATTR_LIBC_PRINTF(2, 0),__THROWING,__localdep_verrc,(int __status, __errno_t __used_errno, char const *__format, __builtin_va_list __args),verrc,(__status,__used_errno,__format,__args))
#elif (defined(__CRT_HAVE_vwarnc) || (!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit))
__NAMESPACE_LOCAL_END
#include <libc/local/err/verrc.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `warnc()', but follow up by calling `exit(status)' */
#define __localdep_verrc __LIBC_LOCAL_NAME(verrc)
#else /* ... */
#undef __local___localdep_verrc_defined
#endif /* !... */
#endif /* !__local___localdep_verrc_defined */
/* Same as `warnc()', but follow up by calling `exit(status)' */
__LOCAL_LIBC(errc) __ATTR_NORETURN __ATTR_LIBC_PRINTF(2, 3) void
(__VLIBCCALL __LIBC_LOCAL_NAME(errc))(int __status, __errno_t __used_errno, char const *__format, ...) __THROWS(...) {
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__localdep_verrc(__status, __used_errno, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_errc_defined
#define __local___localdep_errc_defined 1
#define __localdep_errc __LIBC_LOCAL_NAME(errc)
#endif /* !__local___localdep_errc_defined */
#else /* __CRT_HAVE_verrc || ((__CRT_HAVE_vwarnc || (!__NO_STDSTREAMS && __LOCAL_program_invocation_short_name && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock))) && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit)) */
#undef __local_errc_defined
#endif /* !__CRT_HAVE_verrc && ((!__CRT_HAVE_vwarnc && (__NO_STDSTREAMS || !__LOCAL_program_invocation_short_name || (!__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_fputc && !__CRT_HAVE_putc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE_putc_unlocked && (!__CRT_DOS || !__CRT_HAVE__flsbuf) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock))) || (!__CRT_HAVE_exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE__exit && !__CRT_HAVE__Exit)) */
#endif /* !__local_errc_defined */
