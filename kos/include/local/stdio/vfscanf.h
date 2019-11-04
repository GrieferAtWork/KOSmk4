/* HASH CRC-32:0xaeac2bd6 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_vfscanf_defined
#if (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)))) && ((defined(__CRT_HAVE_ungetc_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_ungetc))
#define __local_vfscanf_defined 1
#include <kos/anno.h>
#include <bits/format-printer.h>
/* Dependency: "format_vscanf" from "format-printer" */
#ifndef ____localdep_format_vscanf_defined
#define ____localdep_format_vscanf_defined 1
#ifdef __CRT_HAVE_format_vscanf
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
__CREDIRECT(__ATTR_NONNULL((1, 2, 4)) __ATTR_LIBC_SCANF(4, 0),__SSIZE_TYPE__,,__localdep_format_vscanf,(__pformatgetc __pgetc, __pformatungetc __pungetc, void *__arg, char const *__restrict __format, __builtin_va_list __args),format_vscanf,(__pgetc,__pungetc,__arg,__format,__args)) __THROWS(...)
#else /* LIBC: format_vscanf */
#include <local/format-printer/format_vscanf.h>
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
#define __localdep_format_vscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_vscanf))
#endif /* format_vscanf... */
#endif /* !____localdep_format_vscanf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vfscanf_ungetc) __SSIZE_TYPE__ (__LIBCCALL __vfscanf_ungetc)(void *__arg, __CHAR32_TYPE__ __ch) {
	return ungetc((int)(unsigned int)__ch, (__FILE *)__arg);
}
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__LOCAL_LIBC(vfscanf) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __ATTR_LIBC_SCANF(2, 0) __STDC_INT_AS_SIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(vfscanf))(__FILE *__restrict __stream,
                                        char const *__restrict __format,
                                        __builtin_va_list __args) __THROWS(...) {
#line 838 "kos/src/libc/magic/stdio.c"
	return __localdep_format_vscanf((__pformatgetc)&fgetc, &__vfscanf_ungetc, (void *)__stream, __format, __args);
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)))) && ((defined(__CRT_HAVE_ungetc_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_ungetc)) */
#endif /* !__local_vfscanf_defined */
