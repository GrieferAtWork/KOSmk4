/* HASH CRC-32:0x6f7567ec */
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
#ifndef __local_c16gethostname_defined
#define __local_c16gethostname_defined
#include <__crt.h>
#if defined(__CRT_HAVE_uname) || defined(__CRT_HAVE___uname) || defined(__CRT_HAVE___libc_uname)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_8to16_defined
#define __local___localdep_format_8to16_defined
#if defined(__CRT_HAVE_format_8tow) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,,__SSIZE_TYPE__,__NOTHROW_NCX,__FORMATPRINTER_CC,__localdep_format_8to16,(void *__arg, char const *__data, __SIZE_TYPE__ __datalen),format_8tow,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$format_8tow) && defined(__LIBDCALL_IS_FORMATPRINTER_CC)
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(,__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_8to16,(void *__arg, char const *__data, __SIZE_TYPE__ __datalen),format_8tow,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/format_8tow.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_8to16 __LIBC_LOCAL_NAME(format_8tow)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/format_8to16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_8to16 __LIBC_LOCAL_NAME(format_8to16)
#endif /* !... */
#endif /* !__local___localdep_format_8to16_defined */
#ifndef __local___localdep_format_c16snprintf_printer_defined
#define __local___localdep_format_c16snprintf_printer_defined
#if defined(__CRT_HAVE_format_wsnprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,__C16FORMATPRINTER_CC,__localdep_format_c16snprintf_printer,(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),format_wsnprintf_printer,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$format_wsnprintf_printer)
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,__C16FORMATPRINTER_CC,__localdep_format_c16snprintf_printer,(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),DOS$format_wsnprintf_printer,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
#include <libc/local/parts.wchar.format-printer/format_wsnprintf_printer.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_c16snprintf_printer __NAMESPACE_LOCAL_TYPEHAX(__SSIZE_TYPE__(__C16FORMATPRINTER_CC*)(void *,__CHAR16_TYPE__ const *__restrict,__SIZE_TYPE__),__SSIZE_TYPE__(__C16FORMATPRINTER_CC&)(void *,__CHAR16_TYPE__ const *__restrict,__SIZE_TYPE__),format_wsnprintf_printer)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.format-printer/format_c16snprintf_printer.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_c16snprintf_printer __LIBC_LOCAL_NAME(format_c16snprintf_printer)
#endif /* !... */
#endif /* !__local___localdep_format_c16snprintf_printer_defined */
#ifndef __local___localdep_strnlen_defined
#define __local___localdep_strnlen_defined
#if __has_builtin(__builtin_strnlen) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strnlen)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),strnlen,{ return __builtin_strnlen(__str, __maxlen); })
#elif defined(__CRT_HAVE_strnlen)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),strnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE___strncnt)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),__strncnt,(__str,__maxlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strnlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strnlen __LIBC_LOCAL_NAME(strnlen)
#endif /* !... */
#endif /* !__local___localdep_strnlen_defined */
#ifndef __local___localdep_uname_defined
#define __local___localdep_uname_defined
#ifdef __CRT_HAVE_uname
__NAMESPACE_LOCAL_END
#include <bits/os/utsname.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_uname,(struct utsname *__name),uname,(__name))
#elif defined(__CRT_HAVE___uname)
__NAMESPACE_LOCAL_END
#include <bits/os/utsname.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_uname,(struct utsname *__name),__uname,(__name))
#elif defined(__CRT_HAVE___libc_uname)
__NAMESPACE_LOCAL_END
#include <bits/os/utsname.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_uname,(struct utsname *__name),__libc_uname,(__name))
#else /* ... */
#undef __local___localdep_uname_defined
#endif /* !... */
#endif /* !__local___localdep_uname_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <bits/crt/mbstate.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16gethostname) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16gethostname))(__CHAR16_TYPE__ *__name, __SIZE_TYPE__ __buflen) {
	struct __LOCAL_format_wsnprintf_data {
		__CHAR16_TYPE__      *__sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
		__SIZE_TYPE__ __sd_bufsiz; /* Remaining buffer size. */
	};
	struct __LOCAL_format_8tow_data {
		__pc16formatprinter __fd_printer;    /* [1..1] Inner printer */
		void             *__fd_arg;        /* Argument for `fd_printer' */
		struct __mbstate  __fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	};
	struct utsname __uts;
	int __result = (__NAMESPACE_LOCAL_SYM __localdep_uname)(&__uts);
	if __likely(__result == 0) {
		struct __LOCAL_format_wsnprintf_data __printer_data;
		struct __LOCAL_format_8tow_data __convert_data;
		__SIZE_TYPE__ __len = (__NAMESPACE_LOCAL_SYM __localdep_strnlen)(__uts.nodename, __COMPILER_LENOF(__uts.nodename));
		__SSIZE_TYPE__ __width;
		__printer_data.__sd_buffer  = __name;
		__printer_data.__sd_bufsiz  = __buflen;
		__convert_data.__fd_arg     = &__printer_data;
		__convert_data.__fd_printer = &(__NAMESPACE_LOCAL_SYM __localdep_format_c16snprintf_printer);
		__mbstate_init(&__convert_data.__fd_incomplete);
		__width = (__NAMESPACE_LOCAL_SYM __localdep_format_8to16)(&__convert_data, __uts.nodename, __len);
		if __unlikely(__width < 0)
			return -1;
		if ((__SIZE_TYPE__)__width >= __buflen) {
#ifdef __ERANGE
			return __libc_seterrno(__ERANGE);
#else /* __ERANGE */
			return __libc_seterrno(1);
#endif /* !__ERANGE */
		}
		*__printer_data.__sd_buffer = '\0'; /* NUL-terminate */
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16gethostname_defined
#define __local___localdep_c16gethostname_defined
#define __localdep_c16gethostname __LIBC_LOCAL_NAME(c16gethostname)
#endif /* !__local___localdep_c16gethostname_defined */
#else /* __CRT_HAVE_uname || __CRT_HAVE___uname || __CRT_HAVE___libc_uname */
#undef __local_c16gethostname_defined
#endif /* !__CRT_HAVE_uname && !__CRT_HAVE___uname && !__CRT_HAVE___libc_uname */
#endif /* !__local_c16gethostname_defined */
