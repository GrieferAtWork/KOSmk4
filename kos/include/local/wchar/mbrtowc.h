/* HASH CRC-32:0xa8addb9e */
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
#ifndef __local_mbrtowc_defined
#define __local_mbrtowc_defined 1
#include <__crt.h>
#include <parts/errno.h>
/* Dependency: "unicode_c8toc16" from "unicode" */
#ifndef ____localdep_unicode_c8toc16_defined
#define ____localdep_unicode_c8toc16_defined 1
#ifdef __CRT_HAVE_unicode_c8toc16
/* @return: *:          Success (*pc16 was filled; the return value is the number of bytes taken from `s')
 * @return: 0:          Success (*pc16 was filled; `mbs' was modified, but nothing was read from `s'; in this case, a surrogate was written)
 * @return: (size_t)-1: Unicode error (the given input string isn't a valid unicode sequence)
 * @return: (size_t)-2: Success, but no character was generated (s...+=n, together with `mbs' doesn't for a full character, but `mbs' was updated) */
__CREDIRECT(__ATTR_NONNULL((1, 2, 4)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_unicode_c8toc16,(__CHAR16_TYPE__ *__restrict __pc16, /*utf-8*/ char const *__restrict __s, __SIZE_TYPE__ __n, __mbstate_t *__restrict __mbs),unicode_c8toc16,(__pc16,__s,__n,__mbs))
#else /* LIBC: unicode_c8toc16 */
#include <local/unicode/unicode_c8toc16.h>
/* @return: *:          Success (*pc16 was filled; the return value is the number of bytes taken from `s')
 * @return: 0:          Success (*pc16 was filled; `mbs' was modified, but nothing was read from `s'; in this case, a surrogate was written)
 * @return: (size_t)-1: Unicode error (the given input string isn't a valid unicode sequence)
 * @return: (size_t)-2: Success, but no character was generated (s...+=n, together with `mbs' doesn't for a full character, but `mbs' was updated) */
#define __localdep_unicode_c8toc16 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_c8toc16))
#endif /* unicode_c8toc16... */
#endif /* !____localdep_unicode_c8toc16_defined */

/* Dependency: "unicode_c8toc32" from "unicode" */
#ifndef ____localdep_unicode_c8toc32_defined
#define ____localdep_unicode_c8toc32_defined 1
#ifdef __CRT_HAVE_unicode_c8toc32
/* @return: *:          Success (*pc32 was filled; the return value is the number of bytes taken from `s')
 * @return: (size_t)-1: Unicode error (the given input string isn't a valid unicode sequence)
 * @return: (size_t)-2: Success, but no character was generated (s...+=n, together with `mbs' doesn't for a full character, but `mbs' was updated) */
__CREDIRECT(__ATTR_NONNULL((1, 2, 4)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_unicode_c8toc32,(__CHAR32_TYPE__ *__restrict __pc32, /*utf-8*/ char const *__restrict __s, __SIZE_TYPE__ __n, __mbstate_t *__restrict __mbs),unicode_c8toc32,(__pc32,__s,__n,__mbs))
#else /* LIBC: unicode_c8toc32 */
#include <local/unicode/unicode_c8toc32.h>
/* @return: *:          Success (*pc32 was filled; the return value is the number of bytes taken from `s')
 * @return: (size_t)-1: Unicode error (the given input string isn't a valid unicode sequence)
 * @return: (size_t)-2: Success, but no character was generated (s...+=n, together with `mbs' doesn't for a full character, but `mbs' was updated) */
#define __localdep_unicode_c8toc32 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_c8toc32))
#endif /* unicode_c8toc32... */
#endif /* !____localdep_unicode_c8toc32_defined */

__NAMESPACE_LOCAL_BEGIN
#ifndef ____local_mbrtowc_ps_defined
#define ____local_mbrtowc_ps_defined 1
__LOCAL_LIBC_DATA(__mbrtowc_ps) __mbstate_t __mbrtowc_ps = __MBSTATE_INIT;
#endif /* !____local_mbrtowc_ps_defined */
__LOCAL_LIBC(mbrtowc) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mbrtowc))(__WCHAR_TYPE__ *__pwc,
                                                     char const *__restrict __str,
                                                     __SIZE_TYPE__ __maxlen,
                                                     __mbstate_t *__mbs) {
#line 228 "kos/src/libc/magic/wchar.c"
	__SIZE_TYPE__ __error;
	if (!__mbs)
		__mbs = &__mbrtowc_ps;
	if (!__str) {
		__mbs->__word = 0;
		return 0;
	}
	if (!__maxlen || !*__str)
		return 0;
#if __SIZEOF_WCHAR_T__ == 2
	__error = __localdep_unicode_c8toc16((__CHAR16_TYPE__ *)__pwc, __str, __maxlen, __mbs);
#else /* __SIZEOF_WCHAR_T__ == 2 */
	__error = __localdep_unicode_c8toc32((__CHAR32_TYPE__ *)__pwc, __str, __maxlen, __mbs);
#endif /* __SIZEOF_WCHAR_T__ != 2 */
#ifdef __EILSEQ
	if (__error == (__SIZE_TYPE__)-1)
		__libc_seterrno(__EILSEQ);
#endif /* EILSEQ */
	return __error;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_mbrtowc_defined */
