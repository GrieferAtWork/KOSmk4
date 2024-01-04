/* HASH CRC-32:0xaf894fc2 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_backtrace_symbols_defined
#define __local_backtrace_symbols_defined
#include <__crt.h>
#if defined(__CRT_HAVE_backtrace_symbols_fmt) || defined(__CRT_HAVE___backtrace_symbols) || (defined(__CRT_HAVE_backtrace_symbol_printf) && (defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_backtrace_symbols_fmt_defined
#define __local___localdep_backtrace_symbols_fmt_defined
#ifdef __CRT_HAVE_backtrace_symbols_fmt
__CREDIRECT(__ATTR_INS(1, 2) __ATTR_IN_OPT(3),char **,__NOTHROW_NCX,__localdep_backtrace_symbols_fmt,(void *const *__array, __STDC_INT_AS_SIZE_T __size, char const *__format),backtrace_symbols_fmt,(__array,__size,__format))
#elif defined(__CRT_HAVE___backtrace_symbols)
__CREDIRECT(__ATTR_INS(1, 2) __ATTR_IN_OPT(3),char **,__NOTHROW_NCX,__localdep_backtrace_symbols_fmt,(void *const *__array, __STDC_INT_AS_SIZE_T __size, char const *__format),__backtrace_symbols,(__array,__size,__format))
#elif defined(__CRT_HAVE_backtrace_symbol_printf) && (defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
__NAMESPACE_LOCAL_END
#include <libc/local/execinfo/backtrace_symbols_fmt.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_backtrace_symbols_fmt __LIBC_LOCAL_NAME(backtrace_symbols_fmt)
#else /* ... */
#undef __local___localdep_backtrace_symbols_fmt_defined
#endif /* !... */
#endif /* !__local___localdep_backtrace_symbols_fmt_defined */
__LOCAL_LIBC(backtrace_symbols) __ATTR_INS(1, 2) char **
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(backtrace_symbols))(void *const *__array, __STDC_INT_AS_SIZE_T __size) {
	return (__NAMESPACE_LOCAL_SYM __localdep_backtrace_symbols_fmt)(__array, __size, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_backtrace_symbols_defined
#define __local___localdep_backtrace_symbols_defined
#define __localdep_backtrace_symbols __LIBC_LOCAL_NAME(backtrace_symbols)
#endif /* !__local___localdep_backtrace_symbols_defined */
#else /* __CRT_HAVE_backtrace_symbols_fmt || __CRT_HAVE___backtrace_symbols || (__CRT_HAVE_backtrace_symbol_printf && (__CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#undef __local_backtrace_symbols_defined
#endif /* !__CRT_HAVE_backtrace_symbols_fmt && !__CRT_HAVE___backtrace_symbols && (!__CRT_HAVE_backtrace_symbol_printf || (!__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
#endif /* !__local_backtrace_symbols_defined */
