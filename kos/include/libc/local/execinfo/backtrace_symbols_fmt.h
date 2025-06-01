/* HASH CRC-32:0x4ec822e6 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_backtrace_symbols_fmt_defined
#define __local_backtrace_symbols_fmt_defined
#include <__crt.h>
#if defined(__CRT_HAVE_backtrace_symbol_printf) && (defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_backtrace_symbol_printf_defined
#define __local___localdep_backtrace_symbol_printf_defined
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_backtrace_symbol_printf,(__pformatprinter __printer, void *__arg, void const *__address, char const *__format),backtrace_symbol_printf,(__printer,__arg,__address,__format))
#endif /* !__local___localdep_backtrace_symbol_printf_defined */
#ifndef __local___localdep_format_aprintf_alloc_defined
#define __local___localdep_format_aprintf_alloc_defined
#ifdef __CRT_HAVE_format_aprintf_alloc
__NAMESPACE_LOCAL_END
struct format_aprintf_data;
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_INOUT(1),char *,__NOTHROW_NCX,__localdep_format_aprintf_alloc,(struct format_aprintf_data *__restrict __self, __SIZE_TYPE__ __num_chars),format_aprintf_alloc,(__self,__num_chars))
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_aprintf_alloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_aprintf_alloc __LIBC_LOCAL_NAME(format_aprintf_alloc)
#else /* ... */
#undef __local___localdep_format_aprintf_alloc_defined
#endif /* !... */
#endif /* !__local___localdep_format_aprintf_alloc_defined */
#ifndef __local___localdep_format_aprintf_pack_defined
#define __local___localdep_format_aprintf_pack_defined
#ifdef __CRT_HAVE_format_aprintf_pack
__NAMESPACE_LOCAL_END
struct format_aprintf_data;
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT_OPT(2),char *,__NOTHROW_NCX,__localdep_format_aprintf_pack,(struct format_aprintf_data *__restrict __self, __SIZE_TYPE__ *__pstrlen),format_aprintf_pack,(__self,__pstrlen))
#else /* __CRT_HAVE_format_aprintf_pack */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_aprintf_pack.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_aprintf_pack __LIBC_LOCAL_NAME(format_aprintf_pack)
#endif /* !__CRT_HAVE_format_aprintf_pack */
#endif /* !__local___localdep_format_aprintf_pack_defined */
#ifndef __local___localdep_format_aprintf_printer_defined
#define __local___localdep_format_aprintf_printer_defined
#ifdef __CRT_HAVE_format_aprintf_printer
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__FORMATPRINTER_CC,__localdep_format_aprintf_printer,(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen),format_aprintf_printer,(__arg,__data,__datalen))
#else /* __CRT_HAVE_format_aprintf_printer */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_aprintf_printer.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_aprintf_printer __LIBC_LOCAL_NAME(format_aprintf_printer)
#endif /* !__CRT_HAVE_format_aprintf_printer */
#endif /* !__local___localdep_format_aprintf_printer_defined */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined
#ifdef __CRT_HAVE_strend
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __str),strend,(__str))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#ifndef __format_aprintf_data_defined
#define __format_aprintf_data_defined
struct format_aprintf_data {
	char         *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size (including space for trailing NUL) */
	__SIZE_TYPE__ ap_used;  /* Used buffer size (excluding trailing NUL, which only gets added during pack) */
};
#endif /* !__format_aprintf_data_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(backtrace_symbols_fmt) __ATTR_INS(1, 2) __ATTR_IN_OPT(3) char **
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(backtrace_symbols_fmt))(void *const *__array, __STDC_INT_AS_SIZE_T __size, char const *__format) {
	char **__result;
	struct format_aprintf_data __printer;
	__SIZE_TYPE__ __i;
	__printer.ap_base  = __NULLPTR;
	__printer.ap_avail = 0;
	__printer.ap_used  = 0;

	/* Make space for the string array itself. */
	if __unlikely(!(__NAMESPACE_LOCAL_SYM __localdep_format_aprintf_alloc)(&__printer,
	                                  (((__size + 1) * sizeof(char *)) +
	                                   sizeof(char) - 1) /
	                                  sizeof(char)))
		goto __err;

	for (__i = 0; __i < (__SIZE_TYPE__)__size; ++__i) {
		if (__i != 0) {
			/* NUL-terminate  the  preceding string  (the last  string will
			 * be automatically NUL-terminated by `format_aprintf_pack()'!) */
			if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_format_aprintf_printer)(&__printer, "", 1) < 0)
				goto __err;
		}
		/* Print the backtrack string. */
		if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_backtrace_symbol_printf)(&(__NAMESPACE_LOCAL_SYM __localdep_format_aprintf_printer),
		                                    &__printer,
		                                    __array[__i],
		                                    __format) < 0)
			goto __err;
	}

	/* Pack together the buffer */
	__result = (char **)(__NAMESPACE_LOCAL_SYM __localdep_format_aprintf_pack)(&__printer, __NULLPTR);
	if __likely(__result) {
		char *__strings;
		__strings = (char *)((__BYTE_TYPE__ *)__result + ((__SIZE_TYPE__)__size * sizeof(char *)));
		for (__i = 0; __i < (__SIZE_TYPE__)__size; ++__i) {
			__result[__i] = __strings;
			__strings = (__NAMESPACE_LOCAL_SYM __localdep_strend)(__strings) + 1;
		}
		__result[__i] = __NULLPTR;
	}
	return __result;
__err:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__printer.ap_base);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_backtrace_symbols_fmt_defined
#define __local___localdep_backtrace_symbols_fmt_defined
#define __localdep_backtrace_symbols_fmt __LIBC_LOCAL_NAME(backtrace_symbols_fmt)
#endif /* !__local___localdep_backtrace_symbols_fmt_defined */
#else /* __CRT_HAVE_backtrace_symbol_printf && (__CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#undef __local_backtrace_symbols_fmt_defined
#endif /* !__CRT_HAVE_backtrace_symbol_printf || (!__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
#endif /* !__local_backtrace_symbols_fmt_defined */
