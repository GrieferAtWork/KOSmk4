/* HASH CRC-32:0xf951e6df */
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
#ifndef __local_errx_defined
#define __local_errx_defined 1
#include <__crt.h>
#include <libc/local/program_invocation_name.h>
#include <features.h>
#if defined(__CRT_HAVE_verrx) || ((defined(__CRT_HAVE_vwarnx) || (!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)))
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: verrx from err */
#ifndef __local___localdep_verrx_defined
#define __local___localdep_verrx_defined 1
#ifdef __CRT_HAVE_verrx
/* Same as `warnx()', but follow up by calling `exit(status)' */
__CREDIRECT_VOID(__ATTR_NORETURN __ATTR_LIBC_PRINTF(2, 0),__THROWING,__localdep_verrx,(int __status, char const *__format, __builtin_va_list __args),verrx,(__status,__format,__args))
#elif (defined(__CRT_HAVE_vwarnx) || (!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit))
__NAMESPACE_LOCAL_END
#include <libc/local/err/verrx.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `warnx()', but follow up by calling `exit(status)' */
#define __localdep_verrx __LIBC_LOCAL_NAME(verrx)
#else /* ... */
#undef __local___localdep_verrx_defined
#endif /* !... */
#endif /* !__local___localdep_verrx_defined */
/* Same as `warnx()', but follow up by calling `exit(status)' */
__LOCAL_LIBC(errx) __ATTR_NORETURN __ATTR_LIBC_PRINTF(2, 3) void
(__VLIBCCALL __LIBC_LOCAL_NAME(errx))(int __status, char const *__format, ...) __THROWS(...) {
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__localdep_verrx(__status, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_errx_defined
#define __local___localdep_errx_defined 1
#define __localdep_errx __LIBC_LOCAL_NAME(errx)
#endif /* !__local___localdep_errx_defined */
#else /* __CRT_HAVE_verrx || ((__CRT_HAVE_vwarnx || (!__NO_STDSTREAMS && __LOCAL_program_invocation_short_name && (__CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock))) && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit)) */
#undef __local_errx_defined
#endif /* !__CRT_HAVE_verrx && ((!__CRT_HAVE_vwarnx && (__NO_STDSTREAMS || !__LOCAL_program_invocation_short_name || (!__CRT_HAVE_fputc && !__CRT_HAVE_putc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE_putc_unlocked && (!__CRT_DOS || !__CRT_HAVE__flsbuf) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock))) || (!__CRT_HAVE_exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE__exit && !__CRT_HAVE__Exit)) */
#endif /* !__local_errx_defined */
