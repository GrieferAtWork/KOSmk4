/* HASH CRC-32:0x42124ced */
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
#ifndef __local_regasub_defined
#define __local_regasub_defined
#include <__crt.h>
#if defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <bits/crt/regex.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_aprintf_pack_defined
#define __local___localdep_format_aprintf_pack_defined
#ifdef __CRT_HAVE_format_aprintf_pack
__NAMESPACE_LOCAL_END
struct format_aprintf_data;
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
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__FORMATPRINTER_CC,__localdep_format_aprintf_printer,(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen),format_aprintf_printer,(__arg,__data,__datalen))
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
__NAMESPACE_LOCAL_END
#ifndef __format_aprintf_data_defined
#define __format_aprintf_data_defined
struct format_aprintf_data {
	char         *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif /* !__format_aprintf_data_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(regasub) __ATTR_IN(2) __ATTR_IN(4) __ATTR_OUT(1) __ATTR_NONNULL((3)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(regasub))(char **__p_buf, char const *__sed_format, struct __regmatch const *__pmatch, char const *__srcbase) {
	struct format_aprintf_data __pdata;
	__SSIZE_TYPE__ __result;
	char *__resstr;

	/* Setup malloc-based printer. */
	__pdata.ap_base  = __NULLPTR;
	__pdata.ap_avail = 0;
	__pdata.ap_used  = 0;

	/* Do the substitution-print. */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_regsubprint)(&(__NAMESPACE_LOCAL_SYM __localdep_format_aprintf_printer), &__pdata,
	                     __sed_format, __srcbase, 10, __pmatch);
	if __unlikely(__result < 0)
		goto __err;

	/* package the produced string. */
	__resstr = (__NAMESPACE_LOCAL_SYM __localdep_format_aprintf_pack)(&__pdata, (__SIZE_TYPE__ *)&__result);
	*__p_buf = __resstr;
	if __unlikely(!__resstr)
		__result = -1;
	return __result;
__err:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__pdata.ap_base);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	*__p_buf = __NULLPTR;
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_regasub_defined
#define __local___localdep_regasub_defined
#define __localdep_regasub __LIBC_LOCAL_NAME(regasub)
#endif /* !__local___localdep_regasub_defined */
#else /* __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc */
#undef __local_regasub_defined
#endif /* !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc */
#endif /* !__local_regasub_defined */
