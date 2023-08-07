/* HASH CRC-32:0x71f3e4de */
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
#ifndef __local_strtold_defined
#define __local_strtold_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_scanf_defined
#define __local___localdep_format_scanf_defined
#ifdef __CRT_HAVE_format_scanf
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_IN(4) __ATTR_LIBC_SCANF(4, 5) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_CB(__VLIBCCALL __localdep_format_scanf)(__pformatgetc __pgetc, __pformatungetc __pungetc, void *__arg, char const *__restrict __format, ...) __CASMNAME("format_scanf");
#else /* __CRT_HAVE_format_scanf */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_scanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_scanf __LIBC_LOCAL_NAME(format_scanf)
#endif /* !__CRT_HAVE_format_scanf */
#endif /* !__local___localdep_format_scanf_defined */
#ifndef __local___localdep_unicode_readutf8_defined
#define __local___localdep_unicode_readutf8_defined
#ifdef __CRT_HAVE_unicode_readutf8
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__CHAR32_TYPE__,__NOTHROW_NCX,__localdep_unicode_readutf8,(char const **__restrict __ptext),unicode_readutf8,(__ptext))
#else /* __CRT_HAVE_unicode_readutf8 */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_readutf8.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_readutf8 __LIBC_LOCAL_NAME(unicode_readutf8)
#endif /* !__CRT_HAVE_unicode_readutf8 */
#endif /* !__local___localdep_unicode_readutf8_defined */
#ifndef __local___localdep_unicode_readutf8_rev_defined
#define __local___localdep_unicode_readutf8_rev_defined
#ifdef __CRT_HAVE_unicode_readutf8_rev
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),__CHAR32_TYPE__,__NOTHROW_NCX,__localdep_unicode_readutf8_rev,(char const **__restrict __ptext),unicode_readutf8_rev,(__ptext))
#else /* __CRT_HAVE_unicode_readutf8_rev */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_readutf8_rev.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_readutf8_rev __LIBC_LOCAL_NAME(unicode_readutf8_rev)
#endif /* !__CRT_HAVE_unicode_readutf8_rev */
#endif /* !__local___localdep_unicode_readutf8_rev_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/stdio.h>
#if __SIZEOF_CHAR__ == 1
#ifndef ____vsscanf_getc_defined
#define ____vsscanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsscanf_getc) __format_word_t
__NOTHROW_NCX(__FORMATPRINTER_CC __vsscanf_getc)(void *__arg) {
	unsigned char const *__reader = *(unsigned char const **)__arg;
	unsigned char __result        = *__reader++;
	if (!__result)
		return __EOF;
	*(unsigned char const **)__arg = __reader;
	return (__format_word_t)__result;
}
__LOCAL_LIBC(vsscanf_ungetc) __SSIZE_TYPE__
__NOTHROW(__FORMATPRINTER_CC __vsscanf_ungetc)(void *__arg, __format_word_t __UNUSED(__word)) {
	--(*(unsigned char const **)__arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsscanf_getc_defined */

#elif __SIZEOF_CHAR__ == 2
#ifndef ____vsc16scanf_getc_defined
#define ____vsc16scanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc16scanf_getc) __format_word_t
(__FORMATPRINTER_CC __vsc16scanf_getc)(void *__arg) {
	__CHAR16_TYPE__ const *__reader = *(__CHAR16_TYPE__ const **)__arg;
	__CHAR16_TYPE__ __result        = *__reader++;
	if (!__result)
		return __EOF;
	*(__CHAR16_TYPE__ const **)__arg = __reader;
	return (__format_word_t)__result;
}
__LOCAL_LIBC(vsc16scanf_ungetc) __SSIZE_TYPE__
(__FORMATPRINTER_CC __vsc16scanf_ungetc)(void *__arg, __format_word_t __UNUSED(__word)) {
	--(*(__CHAR16_TYPE__ const **)__arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsc16scanf_getc_defined */

#else /* ... */
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

#endif /* !... */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strtold) __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGDOUBLE
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtold))(char const *__restrict __nptr, char **__endptr) {
	__LONGDOUBLE __result;
	char const *__text_pointer = __nptr;

	if (!(__NAMESPACE_LOCAL_SYM __localdep_format_scanf)(&__NAMESPACE_LOCAL_SYM __vsscanf_getc,
	                  &__NAMESPACE_LOCAL_SYM __vsscanf_ungetc,
	                  (void *)&__text_pointer, "%Lf", &__result))
		__result = 0.0L;











	if (__endptr)
		*__endptr = (char *)__text_pointer;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtold_defined
#define __local___localdep_strtold_defined
#define __localdep_strtold __LIBC_LOCAL_NAME(strtold)
#endif /* !__local___localdep_strtold_defined */
#endif /* !__local_strtold_defined */
