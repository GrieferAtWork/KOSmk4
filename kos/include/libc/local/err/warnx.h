/* HASH CRC-32:0xbb2506dc */
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
#ifndef __local_warnx_defined
#define __local_warnx_defined 1
#include <__crt.h>
#include <libc/local/program_invocation_name.h>
#if defined(__CRT_HAVE_vwarnx) || (!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: vwarnx from err */
#ifndef __local___localdep_vwarnx_defined
#define __local___localdep_vwarnx_defined 1
#ifdef __CRT_HAVE_vwarnx
/* Print to stderr: `<program_invocation_short_name>: <format...>\n' */
__CREDIRECT_VOID(__ATTR_LIBC_PRINTF(1, 0),__THROWING,__localdep_vwarnx,(char const *__format, __builtin_va_list __args),vwarnx,(__format,__args))
#elif !defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
__NAMESPACE_LOCAL_END
#include <libc/local/err/vwarnx.h>
__NAMESPACE_LOCAL_BEGIN
/* Print to stderr: `<program_invocation_short_name>: <format...>\n' */
#define __localdep_vwarnx __LIBC_LOCAL_NAME(vwarnx)
#else /* ... */
#undef __local___localdep_vwarnx_defined
#endif /* !... */
#endif /* !__local___localdep_vwarnx_defined */
/* Print to stderr: `<program_invocation_short_name>: <format...>\n' */
__LOCAL_LIBC(warnx) __ATTR_LIBC_PRINTF(1, 2) void
(__VLIBCCALL __LIBC_LOCAL_NAME(warnx))(char const *__format, ...) __THROWS(...) {
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__localdep_vwarnx(__format, __args);
	__builtin_va_end(__args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_warnx_defined
#define __local___localdep_warnx_defined 1
#define __localdep_warnx __LIBC_LOCAL_NAME(warnx)
#endif /* !__local___localdep_warnx_defined */
#else /* __CRT_HAVE_vwarnx || (!__NO_STDSTREAMS && __LOCAL_program_invocation_short_name && (__CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock)) */
#undef __local_warnx_defined
#endif /* !__CRT_HAVE_vwarnx && (__NO_STDSTREAMS || !__LOCAL_program_invocation_short_name || (!__CRT_HAVE_fputc && !__CRT_HAVE_putc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE_putc_unlocked && (!__CRT_DOS || !__CRT_HAVE__flsbuf) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock)) */
#endif /* !__local_warnx_defined */
