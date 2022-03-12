/* HASH CRC-32:0x75560e92 */
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
#ifndef __local_sym_ntos_defined
#define __local_sym_ntos_defined
#include <__crt.h>
#include <bits/crt/resolv.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_error_defined
#define __local___localdep_error_defined
#ifdef __CRT_HAVE_error
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_LIBC_PRINTF(3, 4) void (__VLIBCCALL __localdep_error)(int __status, __errno_t __errnum, const char *__format, ...) __THROWS(...) __CASMNAME("error");
#else /* __CRT_HAVE_error */
__NAMESPACE_LOCAL_END
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__LOCAL_stdout) && defined(__LOCAL_stderr) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)) && defined(__LOCAL_program_invocation_short_name)
__NAMESPACE_LOCAL_END
#include <libc/local/error/error.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_error __LIBC_LOCAL_NAME(error)
#else /* __LOCAL_stdout && __LOCAL_stderr && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit) && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) && __LOCAL_program_invocation_short_name */
#undef __local___localdep_error_defined
#endif /* !__LOCAL_stdout || !__LOCAL_stderr || (!__CRT_HAVE_exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE__exit && !__CRT_HAVE__Exit) || (!__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) || !__LOCAL_program_invocation_short_name */
#endif /* !__CRT_HAVE_error */
#endif /* !__local___localdep_error_defined */
#ifndef __local___localdep_sprintf_defined
#define __local___localdep_sprintf_defined
#if __has_builtin(__builtin_sprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sprintf) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_sprintf,(char *__restrict __buf, char const *__restrict __format, ...),sprintf,{ return __builtin_sprintf(__buf, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_sprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("sprintf");
#elif defined(__CRT_HAVE__IO_sprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("_IO_sprintf");
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/sprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sprintf __LIBC_LOCAL_NAME(sprintf)
#endif /* !... */
#endif /* !__local___localdep_sprintf_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sym_ntos) __ATTR_RETNONNULL __ATTR_NONNULL((1)) char const *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sym_ntos))(struct res_sym const *__symbols, int __wanted_number, int *__p_success) {
#if __SIZEOF_INT__ == 4
	static char __fallback_namebuf[__COMPILER_LENOF("-2147483648")];
#elif __SIZEOF_INT__ == 8
	static char __fallback_namebuf[__COMPILER_LENOF("-9223372036854775808")];
#elif __SIZEOF_INT__ == 2
	static char __fallback_namebuf[__COMPILER_LENOF("-32768")];
#elif __SIZEOF_INT__ == 1
	static char __fallback_namebuf[__COMPILER_LENOF("-128")];
#else /* ... */
#error "Unsupported sizeof(int)"
#endif /* !... */
	while (__symbols->name != __NULLPTR) {
		if (__symbols->number == __wanted_number) {
			if (__p_success)
				*__p_success = 1;
			return __symbols->name;
		}
		++__symbols;
	}
	if (__p_success)
		*__p_success = 0;
	(__NAMESPACE_LOCAL_SYM __localdep_sprintf)(__fallback_namebuf, "%d", __wanted_number);
	return __fallback_namebuf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sym_ntos_defined
#define __local___localdep_sym_ntos_defined
#define __localdep_sym_ntos __LIBC_LOCAL_NAME(sym_ntos)
#endif /* !__local___localdep_sym_ntos_defined */
#endif /* !__local_sym_ntos_defined */
