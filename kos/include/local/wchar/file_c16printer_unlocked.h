/* HASH CRC-32:0x9417de2c */
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
#ifndef __local_file_c16printer_unlocked_defined
#if defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)
#define __local_file_c16printer_unlocked_defined 1
#include <kos/anno.h>
/* Dependency: "fputwc_unlocked" */
#ifndef ____localdep_fputc16_unlocked_defined
#define ____localdep_fputc16_unlocked_defined 1
#if defined(__CRT_HAVE_fputwc_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fputc16_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fputc16_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$_fputwc_nolock)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fputc16_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$_fputwc_nolock)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fputc16_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#else /* LIBC: fputc16_unlocked */
#undef ____localdep_fputc16_unlocked_defined
#endif /* fputc16_unlocked... */
#endif /* !____localdep_fputc16_unlocked_defined */

__NAMESPACE_LOCAL_BEGIN
#ifndef __WEOF
#if 2 == 4
#define __WEOF 0xffffffffu
#else /* __SIZEOF_WCHAR_T__ == 4 */
#define __WEOF (__CCAST(__WINT_TYPE__) 0xffff)
#endif /* __SIZEOF_WCHAR_T__ != 4 */
#endif /* !__WEOF */
/* Same as `file_c16printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__LOCAL_LIBC(file_c16printer_unlocked) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__
(__LIBDCALL __LIBC_LOCAL_NAME(file_c16printer_unlocked))(void *__arg,
                                                         __CHAR16_TYPE__ const *__restrict __data,
                                                         __SIZE_TYPE__ __datalen) __THROWS(...) {
#line 1154 "kos/src/libc/magic/wchar.c"
	__SIZE_TYPE__ __i;
	for (__i = 0; __i < __datalen; ++__i) {
		if (__localdep_fputc16_unlocked(__data[__i], (__FILE *)__arg) == __WEOF)
			break;
	}
	return (__SSIZE_TYPE__)__i;
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) */
#endif /* !__local_file_c16printer_unlocked_defined */
