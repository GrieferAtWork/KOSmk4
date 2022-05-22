/* HASH CRC-32:0xa35b4b4f */
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
#ifndef __local_vsc32scanf_defined
#define __local_vsc32scanf_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_vc32scanf_defined
#define __local___localdep_format_vc32scanf_defined
#if defined(__CRT_HAVE_format_vwscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(4) __ATTR_LIBC_C32SCANF(4, 0) __ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_format_vc32scanf,(__pformatgetc __pgetc, __pformatungetc __pungetc, void *__arg, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),format_vwscanf,(__pgetc,__pungetc,__arg,__format,__args))
#elif defined(__CRT_HAVE_KOS$format_vwscanf)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_IN(4) __ATTR_LIBC_C32SCANF(4, 0) __ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_format_vc32scanf,(__pformatgetc __pgetc, __pformatungetc __pungetc, void *__arg, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),format_vwscanf,(__pgetc,__pungetc,__arg,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.format-printer/format_vwscanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vc32scanf __NAMESPACE_LOCAL_TYPEHAX(__SSIZE_TYPE__(__LIBKCALL*)(__pformatgetc,__pformatungetc,void *,__CHAR32_TYPE__ const *__restrict,__builtin_va_list),__SSIZE_TYPE__(__LIBKCALL&)(__pformatgetc,__pformatungetc,void *,__CHAR32_TYPE__ const *__restrict,__builtin_va_list),format_vwscanf)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.format-printer/format_vc32scanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vc32scanf __LIBC_LOCAL_NAME(format_vc32scanf)
#endif /* !... */
#endif /* !__local___localdep_format_vc32scanf_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
#include <asm/crt/stdio.h>
#ifndef ____vsc32scanf_getc_defined
#define ____vsc32scanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc32scanf_getc) __format_word_t
(__FORMATPRINTER_CC __vsc32scanf_getc)(void *__arg) {
	__CHAR32_TYPE__ const *__reader = *(__CHAR32_TYPE__ const **)__arg;
	__CHAR32_TYPE__ __result        = *__reader++;
	if (!__result)
		return __EOF;
	*(__CHAR32_TYPE__ const **)__arg = __reader;
	return (__format_word_t)__result;
}
__LOCAL_LIBC(vsc32scanf_ungetc) __SSIZE_TYPE__
(__FORMATPRINTER_CC __vsc32scanf_ungetc)(void *__arg, __format_word_t __UNUSED(__word)) {
	--(*(__CHAR32_TYPE__ const **)__arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsc32scanf_getc_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc32scanf) __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __ATTR_LIBC_C32SCANF(2, 0) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(vsc32scanf))(__CHAR32_TYPE__ const *__restrict __input, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args) {
	return (__NAMESPACE_LOCAL_SYM __localdep_format_vc32scanf)(&__NAMESPACE_LOCAL_SYM __vsc32scanf_getc,
	                      &__NAMESPACE_LOCAL_SYM __vsc16scanf_ungetc,
	                      (void *)&__input, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vsc32scanf_defined
#define __local___localdep_vsc32scanf_defined
#define __localdep_vsc32scanf __LIBC_LOCAL_NAME(vsc32scanf)
#endif /* !__local___localdep_vsc32scanf_defined */
#endif /* !__local_vsc32scanf_defined */
