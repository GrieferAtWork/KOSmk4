/* HASH CRC-32:0xe3f4b2fe */
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
#ifndef __local_abortf_defined
#define __local_abortf_defined
#include <__crt.h>
#include <asm/os/stdio.h>
#include <asm/os/syslog.h>
#include <libc/template/program_invocation_name.h>
#include <asm/os/tty.h>
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#if defined(__STDERR_FILENO) && defined(__LOG_ERR) && defined(__LOCAL_program_invocation_name) && (defined(__CRT_HAVE_isatty) || defined(__CRT_HAVE__isatty) || defined(__CRT_HAVE___isatty) || defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_writeall) || (defined(__CRT_HAVE_write_printer) && defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__) || defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && defined(__CRT_HAVE_syslog_printer) && (defined(__CRT_HAVE_abort) || defined(__CRT_HAVE__ZSt9terminatev) || defined(__CRT_HAVE_terminate) || defined(__CRT_HAVE___chk_fail) || defined(__CRT_HAVE_$Qterminate$A$AYAXXZ) || defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_abort_defined
#define __local___localdep_abort_defined
#if __has_builtin(__builtin_abort) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_abort)
__CEIREDIRECT(__ATTR_NORETURN,void,,__localdep_abort,(void),abort,{ __builtin_abort(); })
#elif defined(__CRT_HAVE_abort)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep_abort,(void),abort,())
#elif defined(__CRT_HAVE__ZSt9terminatev)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep_abort,(void),_ZSt9terminatev,())
#elif defined(__CRT_HAVE_terminate)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep_abort,(void),terminate,())
#elif defined(__CRT_HAVE___chk_fail)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep_abort,(void),__chk_fail,())
#elif defined(__CRT_HAVE_$Qterminate$A$AYAXXZ)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep_abort,(void),?terminate@@YAXXZ,())
#elif defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/abort.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_abort __LIBC_LOCAL_NAME(abort)
#else /* ... */
#undef __local___localdep_abort_defined
#endif /* !... */
#endif /* !__local___localdep_abort_defined */
#ifndef __local___localdep_format_vprintf_defined
#define __local___localdep_format_vprintf_defined
#ifdef __CRT_HAVE_format_vprintf
__CREDIRECT(__ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,__localdep_format_vprintf,(__pformatprinter __printer, void *__arg, char const *__restrict __format, __builtin_va_list __args),format_vprintf,(__printer,__arg,__format,__args))
#else /* __CRT_HAVE_format_vprintf */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_vprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vprintf __LIBC_LOCAL_NAME(format_vprintf)
#endif /* !__CRT_HAVE_format_vprintf */
#endif /* !__local___localdep_format_vprintf_defined */
#ifndef __local___localdep_isatty_defined
#define __local___localdep_isatty_defined
#ifdef __CRT_HAVE_isatty
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_isatty,(__fd_t __fd),isatty,(__fd))
#elif defined(__CRT_HAVE__isatty)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_isatty,(__fd_t __fd),_isatty,(__fd))
#elif defined(__CRT_HAVE___isatty)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_isatty,(__fd_t __fd),__isatty,(__fd))
#elif defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/isatty.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isatty __LIBC_LOCAL_NAME(isatty)
#else /* ... */
#undef __local___localdep_isatty_defined
#endif /* !... */
#endif /* !__local___localdep_isatty_defined */
#ifndef __local___localdep_strchr_defined
#define __local___localdep_strchr_defined
#if __has_builtin(__builtin_strchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strchr)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
#elif __has_builtin(__builtin_index) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_index)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),index,{ return __builtin_index(__haystack, __needle); })
#elif defined(__CRT_HAVE_strchr)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
#elif defined(__CRT_HAVE_index)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),index,(__haystack,__needle))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strchr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strchr __LIBC_LOCAL_NAME(strchr)
#endif /* !... */
#endif /* !__local___localdep_strchr_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
#ifndef __local___localdep_syslog_printer_defined
#define __local___localdep_syslog_printer_defined
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__FORMATPRINTER_CC,__localdep_syslog_printer,(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen),syslog_printer,(__arg,__data,__datalen))
#endif /* !__local___localdep_syslog_printer_defined */
#ifndef __local___localdep_writeall_defined
#define __local___localdep_writeall_defined
#ifdef __CRT_HAVE_writeall
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_writeall,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),writeall,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE_write_printer) && defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_writeall,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),write_printer,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/writeall.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_writeall __LIBC_LOCAL_NAME(writeall)
#else /* ... */
#undef __local___localdep_writeall_defined
#endif /* !... */
#endif /* !__local___localdep_writeall_defined */
__NAMESPACE_LOCAL_END
__NAMESPACE_LOCAL_BEGIN
struct __vabortmsgf_data {
	char const *__vamfd_ptag_str; /* [1..vamfd_ptag_len] Program tag. */
	__SIZE_TYPE__      __vamfd_ptag_len; /* Length of the program tag. */
	__BOOL        __vamfd_isatty;   /* True if STDERR_FILENO is a tty. */
	__BOOL        __vamfd_at_sol;   /* True if at the start of a line. */
	__BOOL        __vamfd_rp_brk;   /* True if a closing ']' must be replaced with ": " on stderr */
};
__LOCAL_LIBC(vabortmsgf_printer) __SSIZE_TYPE__
__NOTHROW_NCX(__FORMATPRINTER_CC __abortf_printer)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) {
	__SSIZE_TYPE__ __result = (__SSIZE_TYPE__)__datalen;
	struct __vabortmsgf_data *__cookie = (struct __vabortmsgf_data *)__arg;
	while (__datalen) {
		char __tailchar;
		__SIZE_TYPE__ __block_len;
		if (__cookie->__vamfd_at_sol) {
			__cookie->__vamfd_at_sol = 0;
			__cookie->__vamfd_rp_brk = 0;
			(void)(__NAMESPACE_LOCAL_SYM __localdep_syslog_printer)((void *)(__UINTPTR_TYPE__)__LOG_ERR, "[", 1);
			(void)(__NAMESPACE_LOCAL_SYM __localdep_syslog_printer)((void *)(__UINTPTR_TYPE__)__LOG_ERR, __cookie->__vamfd_ptag_str, __cookie->__vamfd_ptag_len);
			(void)(__NAMESPACE_LOCAL_SYM __localdep_syslog_printer)((void *)(__UINTPTR_TYPE__)__LOG_ERR, "] ", __data[0] == '[' ? 1 : 2);
			if (__cookie->__vamfd_isatty) {
				(void)(__NAMESPACE_LOCAL_SYM __localdep_writeall)(__STDERR_FILENO, __cookie->__vamfd_ptag_str, __cookie->__vamfd_ptag_len);
				(void)(__NAMESPACE_LOCAL_SYM __localdep_writeall)(__STDERR_FILENO, ": ", 2);
				if (__data[0] == '[') {
					__cookie->__vamfd_rp_brk = 1;
					(void)(__NAMESPACE_LOCAL_SYM __localdep_syslog_printer)((void *)(__UINTPTR_TYPE__)__LOG_ERR, "[", 1);
					++__data;
					--__datalen;
				}
			}
		}
		for (__block_len = 0;;) {
			for (; __block_len < __datalen; ++__block_len) {
				if ((__NAMESPACE_LOCAL_SYM __localdep_strchr)("\r\n]", __data[__block_len]))
					break;
			}
			if (__block_len >= __datalen)
				break;
			if (__data[__block_len] != ']')
				break;
			if (__cookie->__vamfd_rp_brk)
				break;
		}
		__tailchar = '\0';
		if (__block_len < __datalen)
			__tailchar = __data[__block_len];
		if (__tailchar == '\n') {
			__cookie->__vamfd_at_sol = 1;
			++__block_len;
		}
		(void)(__NAMESPACE_LOCAL_SYM __localdep_syslog_printer)((void *)(__UINTPTR_TYPE__)__LOG_ERR, __data, __block_len);
		if (__cookie->__vamfd_isatty)
			(void)(__NAMESPACE_LOCAL_SYM __localdep_writeall)(__STDERR_FILENO, __data, __block_len);
		__data += __block_len;
		__datalen -= __block_len;
		if (__tailchar == ']') {
			(void)(__NAMESPACE_LOCAL_SYM __localdep_syslog_printer)((void *)(__UINTPTR_TYPE__)__LOG_ERR, "]", 1);
			if (__cookie->__vamfd_isatty)
				(void)(__NAMESPACE_LOCAL_SYM __localdep_writeall)(__STDERR_FILENO, ":", 1);
			++__data;
			--__datalen;
			__cookie->__vamfd_rp_brk = 0;
		} else if (__tailchar == '\r') {
			++__data;
			--__datalen;
			if (__datalen && *__data == '\n') {
				++__data;
				--__datalen;
			}
			(void)(__NAMESPACE_LOCAL_SYM __localdep_syslog_printer)((void *)(__UINTPTR_TYPE__)__LOG_ERR, "\n", 1);
			if (__cookie->__vamfd_isatty)
				(void)(__NAMESPACE_LOCAL_SYM __localdep_writeall)(__STDERR_FILENO, "\n", 1);
			__cookie->__vamfd_at_sol = 1;
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(abortf) __ATTR_NORETURN __ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 2) void
(__VLIBCCALL __LIBC_LOCAL_NAME(abortf))(char const *__format, ...) {
	struct __NAMESPACE_LOCAL_SYM __vabortmsgf_data __data;
	__builtin_va_list __args;
	__data.__vamfd_ptag_str = __LOCAL_program_invocation_name;
	if (__data.__vamfd_ptag_str == __NULLPTR)
		__data.__vamfd_ptag_str = "?";
	__data.__vamfd_ptag_len = (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__data.__vamfd_ptag_str);
	__data.__vamfd_isatty   = (__NAMESPACE_LOCAL_SYM __localdep_isatty)(__STDERR_FILENO) != 0;
	__data.__vamfd_at_sol   = 1;
	__data.__vamfd_rp_brk   = 0;
	__builtin_va_start(__args, __format);
	(void)(__NAMESPACE_LOCAL_SYM __localdep_format_vprintf)(&__NAMESPACE_LOCAL_SYM __abortf_printer, &__data, __format, __args);
	if (!__data.__vamfd_at_sol)
		(void)__NAMESPACE_LOCAL_SYM __abortf_printer(&__data, "\n", 1);
	__builtin_va_end(__args);
	(__NAMESPACE_LOCAL_SYM __localdep_abort)();
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_abortf_defined
#define __local___localdep_abortf_defined
#define __localdep_abortf __LIBC_LOCAL_NAME(abortf)
#endif /* !__local___localdep_abortf_defined */
#else /* __STDERR_FILENO && __LOG_ERR && __LOCAL_program_invocation_name && (__CRT_HAVE_isatty || __CRT_HAVE__isatty || __CRT_HAVE___isatty || __CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_writeall || (__CRT_HAVE_write_printer && __LIBCCALL_IS_FORMATPRINTER_CC && __SIZEOF_INT__ == __SIZEOF_POINTER__) || __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && __CRT_HAVE_syslog_printer && (__CRT_HAVE_abort || __CRT_HAVE__ZSt9terminatev || __CRT_HAVE_terminate || __CRT_HAVE___chk_fail || __CRT_HAVE_$Qterminate$A$AYAXXZ || __CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) */
#undef __local_abortf_defined
#endif /* !__STDERR_FILENO || !__LOG_ERR || !__LOCAL_program_invocation_name || (!__CRT_HAVE_isatty && !__CRT_HAVE__isatty && !__CRT_HAVE___isatty && !__CRT_HAVE_tcgetattr && !__CRT_HAVE___tcgetattr && ((!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || !__TCGETA)) || (!__CRT_HAVE_writeall && (!__CRT_HAVE_write_printer || !__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_INT__ != __SIZEOF_POINTER__) && !__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write) || !__CRT_HAVE_syslog_printer || (!__CRT_HAVE_abort && !__CRT_HAVE__ZSt9terminatev && !__CRT_HAVE_terminate && !__CRT_HAVE___chk_fail && !__CRT_HAVE_$Qterminate$A$AYAXXZ && !__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) */
#endif /* !__local_abortf_defined */
