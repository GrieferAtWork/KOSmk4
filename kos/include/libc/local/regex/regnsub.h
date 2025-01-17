/* HASH CRC-32:0x744befcf */
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
#ifndef __local_regnsub_defined
#define __local_regnsub_defined
#include <__crt.h>
#include <bits/crt/regex.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_snprintf_printer_defined
#define __local___localdep_format_snprintf_printer_defined
#ifdef __CRT_HAVE_format_snprintf_printer
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__FORMATPRINTER_CC,__localdep_format_snprintf_printer,(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen),format_snprintf_printer,(__arg,__data,__datalen))
#else /* __CRT_HAVE_format_snprintf_printer */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_snprintf_printer.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_snprintf_printer __LIBC_LOCAL_NAME(format_snprintf_printer)
#endif /* !__CRT_HAVE_format_snprintf_printer */
#endif /* !__local___localdep_format_snprintf_printer_defined */
#ifndef __local___localdep_regsubprint_defined
#define __local___localdep_regsubprint_defined
#ifdef __CRT_HAVE_regsubprint
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(3) __ATTR_INS(6, 5) __ATTR_NONNULL((1, 4)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_regsubprint,(__pformatprinter __printer, void *__arg, char const *__sed_format, void const *__srcbase, __SIZE_TYPE__ __nmatch, struct __regmatch const __pmatch[__restrict_arr]),regsubprint,(__printer,__arg,__sed_format,__srcbase,__nmatch,__pmatch))
#else /* __CRT_HAVE_regsubprint */
__NAMESPACE_LOCAL_END
#include <libc/local/regex/regsubprint.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_regsubprint __LIBC_LOCAL_NAME(regsubprint)
#endif /* !__CRT_HAVE_regsubprint */
#endif /* !__local___localdep_regsubprint_defined */
__LOCAL_LIBC(regnsub) __ATTR_IN(3) __ATTR_IN(5) __ATTR_OUTS(1, 2) __ATTR_NONNULL((4)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(regnsub))(char *__buf, __SIZE_TYPE__ __len, char const *__sed_format, struct __regmatch const *__pmatch, char const *__srcbase) {
	__SIZE_TYPE__ __result;
	struct __local_format_snprintf_data {
		char  *__sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
		__SIZE_TYPE__ __sd_bufsiz; /* Remaining buffer size. */
	} __pdata;
	__pdata.__sd_buffer = __buf;
	__pdata.__sd_bufsiz = __len;

	/* Do the substitution-print. */
	__result = (__SIZE_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_regsubprint)(&(__NAMESPACE_LOCAL_SYM __localdep_format_snprintf_printer), &__pdata,
	                             __sed_format, __srcbase, 10, __pmatch);

	/* Append trailing NUL-terminator (if there is still space for it). */
	if (__pdata.__sd_bufsiz)
		*__pdata.__sd_buffer = '\0';

	/* Return required buffer size (excluding the trailing NUL) */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_regnsub_defined
#define __local___localdep_regnsub_defined
#define __localdep_regnsub __LIBC_LOCAL_NAME(regnsub)
#endif /* !__local___localdep_regnsub_defined */
#endif /* !__local_regnsub_defined */
