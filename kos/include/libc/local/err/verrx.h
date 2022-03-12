/* HASH CRC-32:0xf77e0f89 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_verrx_defined
#define __local_verrx_defined
#include <__crt.h>
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#include <features.h>
#if (defined(__CRT_HAVE_vwarnx) || (defined(__LOCAL_stderr) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit))
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_exit_defined
#define __local___localdep_exit_defined
#if __has_builtin(__builtin_exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exit)
__CEIREDIRECT(__ATTR_NORETURN,void,__THROWING,__localdep_exit,(int __status),exit,{ __builtin_exit(__status); })
#elif defined(__CRT_HAVE_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep_exit,(int __status),exit,(__status))
#elif defined(__CRT_HAVE_quick_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep_exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE__exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep_exit,(int __status),_exit,(__status))
#elif defined(__CRT_HAVE__Exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep_exit,(int __status),_Exit,(__status))
#else /* ... */
#undef __local___localdep_exit_defined
#endif /* !... */
#endif /* !__local___localdep_exit_defined */
#ifndef __local___localdep_vwarnx_defined
#define __local___localdep_vwarnx_defined
#ifdef __CRT_HAVE_vwarnx
__CREDIRECT_VOID(__ATTR_LIBC_PRINTF(1, 0),__THROWING,__localdep_vwarnx,(char const *__format, __builtin_va_list __args),vwarnx,(__format,__args))
#elif defined(__LOCAL_stderr) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
__NAMESPACE_LOCAL_END
#include <libc/local/err/vwarnx.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vwarnx __LIBC_LOCAL_NAME(vwarnx)
#else /* ... */
#undef __local___localdep_vwarnx_defined
#endif /* !... */
#endif /* !__local___localdep_vwarnx_defined */
__LOCAL_LIBC(verrx) __ATTR_NORETURN __ATTR_LIBC_PRINTF(2, 0) void
(__LIBCCALL __LIBC_LOCAL_NAME(verrx))(int __status, char const *__format, __builtin_va_list __args) __THROWS(...) {
	(__NAMESPACE_LOCAL_SYM __localdep_vwarnx)(__format, __args);
	(__NAMESPACE_LOCAL_SYM __localdep_exit)(__status);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_verrx_defined
#define __local___localdep_verrx_defined
#define __localdep_verrx __LIBC_LOCAL_NAME(verrx)
#endif /* !__local___localdep_verrx_defined */
#else /* (__CRT_HAVE_vwarnx || (__LOCAL_stderr && __LOCAL_program_invocation_short_name && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock))) && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit) */
#undef __local_verrx_defined
#endif /* (!__CRT_HAVE_vwarnx && (!__LOCAL_stderr || !__LOCAL_program_invocation_short_name || (!__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock))) || (!__CRT_HAVE_exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE__exit && !__CRT_HAVE__Exit) */
#endif /* !__local_verrx_defined */
