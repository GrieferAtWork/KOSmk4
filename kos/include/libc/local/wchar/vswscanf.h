/* HASH CRC-32:0x6d05aa91 */
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
#ifndef __local_vswscanf_defined
#define __local_vswscanf_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_vwscanf_defined
#define __local___localdep_format_vwscanf_defined
#ifdef __CRT_HAVE_format_vwscanf
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(4) __ATTR_LIBC_WSCANF(4, 0) __ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_CB,__localdep_format_vwscanf,(__pformatgetc __pgetc, __pformatungetc __pungetc, void *__arg, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),format_vwscanf,(__pgetc,__pungetc,__arg,__format,__args))
#else /* __CRT_HAVE_format_vwscanf */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.format-printer/format_vwscanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vwscanf __LIBC_LOCAL_NAME(format_vwscanf)
#endif /* !__CRT_HAVE_format_vwscanf */
#endif /* !__local___localdep_format_vwscanf_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
#include <asm/crt/stdio.h>
#ifndef ____vswscanf_getc_defined
#define ____vswscanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vswscanf_getc) __format_word_t
(__FORMATPRINTER_CC __vswscanf_getc)(void *__arg) {
	__WCHAR_TYPE__ const *__reader = *(__WCHAR_TYPE__ const **)__arg;
	__WCHAR_TYPE__ __result        = *__reader++;
	if (!__result)
		return __EOF;
	*(__WCHAR_TYPE__ const **)__arg = __reader;
	return (__format_word_t)__result;
}
__LOCAL_LIBC(vswscanf_ungetc) __SSIZE_TYPE__
(__FORMATPRINTER_CC __vswscanf_ungetc)(void *__arg, __format_word_t __UNUSED(__word)) {
	--(*(__WCHAR_TYPE__ const **)__arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vswscanf_getc_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vswscanf) __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __ATTR_LIBC_WSCANF(2, 0) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(vswscanf))(__WCHAR_TYPE__ const *__restrict __input, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args) {
	return (__NAMESPACE_LOCAL_SYM __localdep_format_vwscanf)(&__NAMESPACE_LOCAL_SYM __vswscanf_getc,
	                      &__NAMESPACE_LOCAL_SYM __vswscanf_ungetc,
	                      (void *)&__input, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vswscanf_defined
#define __local___localdep_vswscanf_defined
#define __localdep_vswscanf __LIBC_LOCAL_NAME(vswscanf)
#endif /* !__local___localdep_vswscanf_defined */
#endif /* !__local_vswscanf_defined */
