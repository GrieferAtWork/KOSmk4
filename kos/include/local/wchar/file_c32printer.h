/* HASH CRC-32:0xa5c58cef */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_file_c32printer_defined
#if defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#define __local_file_c32printer_defined 1
#include <kos/anno.h>
/* Dependency: "fputwc" */
#ifndef ____localdep_fputc32_defined
#define ____localdep_fputc32_defined 1
#if defined(__CRT_HAVE_fputwc) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fputc32,(__CHAR32_TYPE__ __wc, __FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fputc32,(__CHAR32_TYPE__ __wc, __FILE *__stream),putwc,(__wc,__stream))
#else /* LIBC: fputc32 */
#undef ____localdep_fputc32_defined
#endif /* fputc32... */
#endif /* !____localdep_fputc32_defined */

__NAMESPACE_LOCAL_BEGIN
#ifndef __WEOF
#if 4 == 4
#define __WEOF 0xffffffffu
#else /* __SIZEOF_WCHAR_T__ == 4 */
#define __WEOF (__CCAST(__WINT_TYPE__) 0xffff)
#endif /* __SIZEOF_WCHAR_T__ != 4 */
#endif /* !__WEOF */
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__LOCAL_LIBC(file_c32printer) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(file_c32printer))(void *__arg,
                                                __CHAR32_TYPE__ const *__restrict __data,
                                                __SIZE_TYPE__ __datalen) __THROWS(...) {
#line 1141 "kos/src/libc/magic/wchar.c"
	__SIZE_TYPE__ __i;
	for (__i = 0; __i < __datalen; ++__i) {
		if (__localdep_fputc32(__data[__i], (__FILE *)__arg) == __WEOF)
			break;
	}
	return (__SSIZE_TYPE__)__i;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_fputwc || __CRT_HAVE_putwc */
#endif /* !__local_file_c32printer_defined */
