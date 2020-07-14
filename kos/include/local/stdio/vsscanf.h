/* HASH CRC-32:0x2e72f285 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_vsscanf_defined
#define __local_vsscanf_defined 1
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: format_vscanf from format-printer */
#ifndef __local___localdep_format_vscanf_defined
#define __local___localdep_format_vscanf_defined 1
#ifdef __CRT_HAVE_format_vscanf
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
#include <bits/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
/* Generic scanf implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will call the given `SCANNER' function which in
 * return should successively yield a character at a time from
 * some kind of input source.
 *  - If `SCANNER' returns `< 0', scanning aborts and that value is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may use `SCANNER' to track the last read character to get
 *    additional information about what character caused the scan to fail.
 *  - The given `SCANNER' should also indicate EOF by returning `NUL'
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
__CREDIRECT(__ATTR_LIBC_SCANF(4, 0) __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,__localdep_format_vscanf,(__pformatgetc __pgetc, __pformatungetc __pungetc, void *__arg, char const *__restrict __format, __builtin_va_list __args),format_vscanf,(__pgetc,__pungetc,__arg,__format,__args))
#else /* __CRT_HAVE_format_vscanf */
__NAMESPACE_LOCAL_END
#include <local/format-printer/format_vscanf.h>
__NAMESPACE_LOCAL_BEGIN
/* Generic scanf implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will call the given `SCANNER' function which in
 * return should successively yield a character at a time from
 * some kind of input source.
 *  - If `SCANNER' returns `< 0', scanning aborts and that value is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may use `SCANNER' to track the last read character to get
 *    additional information about what character caused the scan to fail.
 *  - The given `SCANNER' should also indicate EOF by returning `NUL'
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
#define __localdep_format_vscanf __LIBC_LOCAL_NAME(format_vscanf)
#endif /* !__CRT_HAVE_format_vscanf */
#endif /* !__local___localdep_format_vscanf_defined */
/* Dependency: unicode_readutf8 from unicode */
#ifndef __local___localdep_unicode_readutf8_defined
#define __local___localdep_unicode_readutf8_defined 1
#ifdef __CRT_HAVE_unicode_readutf8
/* Read a single Unicode character from a given UTF-8 string */
__CREDIRECT(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,__localdep_unicode_readutf8,(char const **__restrict __ptext),unicode_readutf8,(__ptext))
#else /* __CRT_HAVE_unicode_readutf8 */
__NAMESPACE_LOCAL_END
#include <local/unicode/unicode_readutf8.h>
__NAMESPACE_LOCAL_BEGIN
/* Read a single Unicode character from a given UTF-8 string */
#define __localdep_unicode_readutf8 __LIBC_LOCAL_NAME(unicode_readutf8)
#endif /* !__CRT_HAVE_unicode_readutf8 */
#endif /* !__local___localdep_unicode_readutf8_defined */
/* Dependency: unicode_readutf8_rev from unicode */
#ifndef __local___localdep_unicode_readutf8_rev_defined
#define __local___localdep_unicode_readutf8_rev_defined 1
#ifdef __CRT_HAVE_unicode_readutf8_rev
/* Same as `unicode_readutf8', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__CREDIRECT(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,__localdep_unicode_readutf8_rev,(char const **__restrict __ptext),unicode_readutf8_rev,(__ptext))
#else /* __CRT_HAVE_unicode_readutf8_rev */
__NAMESPACE_LOCAL_END
#include <local/unicode/unicode_readutf8_rev.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `unicode_readutf8', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
#define __localdep_unicode_readutf8_rev __LIBC_LOCAL_NAME(unicode_readutf8_rev)
#endif /* !__CRT_HAVE_unicode_readutf8_rev */
#endif /* !__local___localdep_unicode_readutf8_rev_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/stdio.h>
#include <hybrid/typecore.h>
#include <bits/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsscanf_getc) __SSIZE_TYPE__
(__FORMATPRINTER_CC __vsscanf_getc)(void *__arg) {
	__CHAR32_TYPE__ __result = (__NAMESPACE_LOCAL_SYM __localdep_unicode_readutf8)((char const **)__arg);
	return __result ? __result : __EOF;
}
__LOCAL_LIBC(vsscanf_ungetc) __SSIZE_TYPE__
(__FORMATPRINTER_CC __vsscanf_ungetc)(void *__arg, __CHAR32_TYPE__ __UNUSED(__ch)) {
	(__NAMESPACE_LOCAL_SYM __localdep_unicode_readutf8_rev)((char const **)__arg);
	return 0;
}
__NAMESPACE_LOCAL_END
__NAMESPACE_LOCAL_BEGIN
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__LOCAL_LIBC(vsscanf) __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(vsscanf))(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args) {
	char const *__input_pointer = __input;
	return __localdep_format_vscanf(&__NAMESPACE_LOCAL_SYM __vsscanf_getc,
	                     &__NAMESPACE_LOCAL_SYM __vsscanf_ungetc,
	                     (void *)&__input_pointer, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vsscanf_defined
#define __local___localdep_vsscanf_defined 1
#define __localdep_vsscanf __LIBC_LOCAL_NAME(vsscanf)
#endif /* !__local___localdep_vsscanf_defined */
#endif /* !__local_vsscanf_defined */
