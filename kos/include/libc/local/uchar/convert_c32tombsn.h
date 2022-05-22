/* HASH CRC-32:0x5e3443a1 */
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
#ifndef __local_convert_c32tombsn_defined
#define __local_convert_c32tombsn_defined
#include <__crt.h>
#if defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_32to8_defined
#define __local___localdep_format_32to8_defined
#if defined(__CRT_HAVE_format_wto8) && __SIZEOF_WCHAR_T__ == 4 && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_ACCESS_ROS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,__localdep_format_32to8,(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen),format_wto8,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$format_wto8)
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_ACCESS_ROS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,__localdep_format_32to8,(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen),KOS$format_wto8,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <libc/local/unicode/format_wto8.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_32to8 __NAMESPACE_LOCAL_TYPEHAX(__SSIZE_TYPE__(__C32FORMATPRINTER_CC*)(void *,__CHAR32_TYPE__ const *,__SIZE_TYPE__),__SSIZE_TYPE__(__C32FORMATPRINTER_CC&)(void *,__CHAR32_TYPE__ const *,__SIZE_TYPE__),format_wto8)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/format_32to8.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_32to8 __LIBC_LOCAL_NAME(format_32to8)
#endif /* !... */
#endif /* !__local___localdep_format_32to8_defined */
#ifndef __local___localdep_format_aprintf_pack_defined
#define __local___localdep_format_aprintf_pack_defined
#ifdef __CRT_HAVE_format_aprintf_pack
__NAMESPACE_LOCAL_END
struct format_aprintf_data;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ACCESS_RW(1) __ATTR_ACCESS_WR_OPT(2),char *,__NOTHROW_NCX,__localdep_format_aprintf_pack,(struct format_aprintf_data *__restrict __self, __SIZE_TYPE__ *__pstrlen),format_aprintf_pack,(__self,__pstrlen))
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
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_ACCESS_ROS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__FORMATPRINTER_CC,__localdep_format_aprintf_printer,(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen),format_aprintf_printer,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_aprintf_printer.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_aprintf_printer __LIBC_LOCAL_NAME(format_aprintf_printer)
#else /* ... */
#undef __local___localdep_format_aprintf_printer_defined
#endif /* !... */
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
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(convert_c32tombsn) __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 2) __ATTR_ACCESS_WR_OPT(3) char *
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(convert_c32tombsn))(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __len, __SIZE_TYPE__ *__preslen) {
	struct __local_format_wto8_data {
		__pformatprinter __fd_printer;   /* [1..1] Inner printer */
		void            *__fd_arg;       /* Argument for `fd_printer' */



	};
	struct __local_format_aprintf_data {
		char         *__ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
		__SIZE_TYPE__ __ap_avail; /* Unused buffer size */
		__SIZE_TYPE__ __ap_used;  /* Used buffer size */
	};
	struct __local_format_aprintf_data __printer_data = { __NULLPTR, 0, 0 };
	struct __local_format_wto8_data __convert_data;
	__convert_data.__fd_printer   = &(__NAMESPACE_LOCAL_SYM __localdep_format_aprintf_printer);
	__convert_data.__fd_arg       = &__printer_data;



	if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_format_32to8)(&__convert_data, __str, __len) < 0) {
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__printer_data.__ap_base);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
		return __NULLPTR;
	}
	return (__NAMESPACE_LOCAL_SYM __localdep_format_aprintf_pack)((struct format_aprintf_data *)&__printer_data, __preslen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_convert_c32tombsn_defined
#define __local___localdep_convert_c32tombsn_defined
#define __localdep_convert_c32tombsn __LIBC_LOCAL_NAME(convert_c32tombsn)
#endif /* !__local___localdep_convert_c32tombsn_defined */
#else /* __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc */
#undef __local_convert_c32tombsn_defined
#endif /* !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc */
#endif /* !__local_convert_c32tombsn_defined */
