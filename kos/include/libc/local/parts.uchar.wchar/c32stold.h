/* HASH CRC-32:0x9fb8b177 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c32stold_defined
#define __local_c32stold_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: format_scanf from format-printer */
#ifndef __local___localdep_format_scanf_defined
#define __local___localdep_format_scanf_defined 1
#ifdef __CRT_HAVE_format_scanf
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> format_scanf(3), format_vscanf(3)
 * Generic scanf implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will call the given `pgetc' function which in
 * return should successively yield a character at a time from
 * some kind of input source.
 *  - If `pgetc' returns `< 0', scanning aborts and that value is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may use `pgetc' to track the last read character to get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier reads a `size_t' from the argument list,
 *                    that specifies the size of the following string buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
__LIBC __ATTR_LIBC_SCANF(4, 5) __ATTR_NONNULL((1, 2, 4)) __SSIZE_TYPE__ (__VLIBCCALL __localdep_format_scanf)(__pformatgetc __pgetc, __pformatungetc __pungetc, void *__arg, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("format_scanf");
#else /* __CRT_HAVE_format_scanf */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_scanf.h>
__NAMESPACE_LOCAL_BEGIN
/* >> format_scanf(3), format_vscanf(3)
 * Generic scanf implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will call the given `pgetc' function which in
 * return should successively yield a character at a time from
 * some kind of input source.
 *  - If `pgetc' returns `< 0', scanning aborts and that value is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may use `pgetc' to track the last read character to get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier reads a `size_t' from the argument list,
 *                    that specifies the size of the following string buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
#define __localdep_format_scanf __LIBC_LOCAL_NAME(format_scanf)
#endif /* !__CRT_HAVE_format_scanf */
#endif /* !__local___localdep_format_scanf_defined */
/* Dependency: unicode_readutf16 from unicode */
#ifndef __local___localdep_unicode_readutf16_defined
#define __local___localdep_unicode_readutf16_defined 1
#ifdef __CRT_HAVE_unicode_readutf16
/* >> unicode_readutf16(3)
 * Read a single Unicode character from a given UTF-16 string */
__CREDIRECT(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,__localdep_unicode_readutf16,(__CHAR16_TYPE__ const **__restrict __ptext),unicode_readutf16,(__ptext))
#else /* __CRT_HAVE_unicode_readutf16 */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_readutf16.h>
__NAMESPACE_LOCAL_BEGIN
/* >> unicode_readutf16(3)
 * Read a single Unicode character from a given UTF-16 string */
#define __localdep_unicode_readutf16 __LIBC_LOCAL_NAME(unicode_readutf16)
#endif /* !__CRT_HAVE_unicode_readutf16 */
#endif /* !__local___localdep_unicode_readutf16_defined */
/* Dependency: unicode_readutf16_rev from unicode */
#ifndef __local___localdep_unicode_readutf16_rev_defined
#define __local___localdep_unicode_readutf16_rev_defined 1
#ifdef __CRT_HAVE_unicode_readutf16_rev
/* >> unicode_readutf16_rev(3)
 * Same as `unicode_readutf16', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__CREDIRECT(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,__localdep_unicode_readutf16_rev,(__CHAR16_TYPE__ const **__restrict __ptext),unicode_readutf16_rev,(__ptext))
#else /* __CRT_HAVE_unicode_readutf16_rev */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_readutf16_rev.h>
__NAMESPACE_LOCAL_BEGIN
/* >> unicode_readutf16_rev(3)
 * Same as `unicode_readutf16', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
#define __localdep_unicode_readutf16_rev __LIBC_LOCAL_NAME(unicode_readutf16_rev)
#endif /* !__CRT_HAVE_unicode_readutf16_rev */
#endif /* !__local___localdep_unicode_readutf16_rev_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/stdio.h>
__NAMESPACE_LOCAL_BEGIN














__NAMESPACE_LOCAL_END




__NAMESPACE_LOCAL_BEGIN














__NAMESPACE_LOCAL_END


#ifndef ____vsc32scanf_getc_defined
#define ____vsc32scanf_getc_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc32scanf_getc) __SSIZE_TYPE__
(__FORMATPRINTER_CC __vsc32scanf_getc)(void *__arg) {
	__CHAR32_TYPE__ const *__reader = *(__CHAR32_TYPE__ const **)__arg;
	__CHAR32_TYPE__ __result = *__reader++;
	if (!__result)
		return __EOF;
	*(__CHAR32_TYPE__ const **)__arg = __reader;
	return __result;
}
__LOCAL_LIBC(vsc32scanf_ungetc) __SSIZE_TYPE__
(__FORMATPRINTER_CC __vsc32scanf_ungetc)(void *__arg, __CHAR32_TYPE__ __UNUSED(__ch)) {
	--*(__CHAR32_TYPE__ const **)__arg;
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsc32scanf_getc_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32stold) __ATTR_LEAF __ATTR_NONNULL((1)) __LONGDOUBLE
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32stold))(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr) {
	__LONGDOUBLE __result;
	__CHAR32_TYPE__ const *__text_pointer = __nptr;











	if (!__localdep_format_scanf(&__NAMESPACE_LOCAL_SYM __vsc32scanf_getc,
	                  &__NAMESPACE_LOCAL_SYM __vsc32scanf_ungetc,
	                  (void *)&__text_pointer, "%Lf", &__result))
		__result = 0.0L;

	if (__endptr)
		*__endptr = (__CHAR32_TYPE__ *)__text_pointer;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32stold_defined
#define __local___localdep_c32stold_defined 1
#define __localdep_c32stold __LIBC_LOCAL_NAME(c32stold)
#endif /* !__local___localdep_c32stold_defined */
#endif /* !__local_c32stold_defined */
