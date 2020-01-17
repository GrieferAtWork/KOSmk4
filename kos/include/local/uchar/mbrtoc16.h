/* HASH CRC-32:0xa5008366 */
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
#ifndef __local_mbrtoc16_defined
#define __local_mbrtoc16_defined 1
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

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__mbrtoc16_mbs) __mbstate_t __mbrtoc16_mbs = __MBSTATE_INIT;
__LOCAL_LIBC(mbrtoc16) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mbrtoc16))(__CHAR16_TYPE__ *__restrict __pc16,
                                                      char const *__restrict __s,
                                                      __SIZE_TYPE__ __n,
                                                      __mbstate_t *__restrict __mbs) {
#line 97 "kos/src/libc/magic/uchar.c"
	__CHAR16_TYPE__ __c16;
	__SIZE_TYPE__ __result;
	if (!__s) {
		if (__mbs)
			__mbs->__word = 0;
		return 0;
	}
	if (!__mbs)
		__mbs = &__mbrtoc16_mbs;
	if (!__pc16)
		__pc16 = &__c16;
	__result = __localdep_unicode_c8toc16(__pc16, __s, __n, __mbs);
#ifdef __EILSEQ
	if __unlikely(__result == (__SIZE_TYPE__)-1)
		__libc_seterrno(__EILSEQ);
#endif /* __EILSEQ */
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_mbrtoc16_defined */
