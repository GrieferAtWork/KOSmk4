/* HASH CRC-32:0x19dce6dc */
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
#ifndef __local_vsnprintf_defined
#define __local_vsnprintf_defined
#include <__crt.h>
#include <features.h>
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
#ifndef __local___localdep_format_vprintf_defined
#define __local___localdep_format_vprintf_defined
#ifdef __CRT_HAVE_format_vprintf
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,__localdep_format_vprintf,(__pformatprinter __printer, void *__arg, char const *__restrict __format, __builtin_va_list __args),format_vprintf,(__printer,__arg,__format,__args))
#else /* __CRT_HAVE_format_vprintf */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_vprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vprintf __LIBC_LOCAL_NAME(format_vprintf)
#endif /* !__CRT_HAVE_format_vprintf */
#endif /* !__local___localdep_format_vprintf_defined */
__NAMESPACE_LOCAL_END
#ifndef ____format_snprintf_data_defined
#define ____format_snprintf_data_defined
struct __format_snprintf_data {
	char         *__sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
	__SIZE_TYPE__ __sd_bufsiz; /* Remaining buffer size. */
};
#endif /* !____format_snprintf_data_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsnprintf) __ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 0) __ATTR_OUTS(1, 2) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(vsnprintf))(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args) {
	struct __format_snprintf_data __data;
	__STDC_INT_AS_SSIZE_T __result;
	__data.__sd_buffer = __buf;
	__data.__sd_bufsiz = __buflen;
	__result = (__STDC_INT_AS_SSIZE_T)(__NAMESPACE_LOCAL_SYM __localdep_format_vprintf)(&(__NAMESPACE_LOCAL_SYM __localdep_format_snprintf_printer),
	                                               (void *)&__data, __format, __args);
	if (__result >= 0) {
		if (__data.__sd_bufsiz != 0) {
			*__data.__sd_buffer = '\0';
		} else {
			/* Special handling for when the buffer was truncated.
			 *
			 * This part right here isn't mandated by any of the specs and wasn't
			 * implemented in the original version of this function which  simply
			 * left the string without any NUL terminator.
			 *
			 * However, as it turns out `nano(1)' around `/src/help.c:55` has line:
			 * >> int length = help_line_len(ptr);
			 * >> char *oneline = nmalloc(length + 1);
			 * >>
			 * >> snprintf(oneline, length + 1, "%s", ptr);  // <<---- This line
			 * >> free(openfile->current->data);
			 * >> openfile->current->data = oneline;
			 *
			 * Here, it uses a `length' (which is smaller than `strlen(ptr)') as
			 * the limit in a call to snprintf(), using it to essentially copy a
			 * small part of the larger help string into a line-buffer.
			 *
			 * However,  it also expects  and assumes that  this buffer gets NUL
			 * terminated  even when truncated (which isn't explicitly specified
			 * by the specs; i.e. `man 3 snprintf'), and any program that relies
			 * on this relies on system-specific behavior.
			 *
			 * Amazingly enough,  even without  explicitly NUL  terminating it  at
			 * the correct location, nano didn't crash but occasionally  displayed
			 * some garbled lines, as well as the line-feed that always got copied
			 * at the end of a paragraph in its escaped form '^@'.
			 *
			 * But then again, NUL-termination on  truncation seems to be  something
			 * that happens on linux, and after all: KOS tries to be as much API/ABI
			 * compatible with linux as possible, so: in this goes! */
			if (__buflen != 0)
				__buf[__buflen - 1] = '\0';
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vsnprintf_defined
#define __local___localdep_vsnprintf_defined
#define __localdep_vsnprintf __LIBC_LOCAL_NAME(vsnprintf)
#endif /* !__local___localdep_vsnprintf_defined */
#endif /* !__local_vsnprintf_defined */
