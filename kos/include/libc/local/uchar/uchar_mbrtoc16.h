/* HASH CRC-32:0xfd35e0f0 */
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
#ifndef __local_uchar_mbrtoc16_defined
#define __local_uchar_mbrtoc16_defined 1
#include <__crt.h>
#include <bits/crt/mbstate.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: unicode_c8toc16 from unicode */
#ifndef __local___localdep_unicode_c8toc16_defined
#define __local___localdep_unicode_c8toc16_defined 1
#ifdef __CRT_HAVE_unicode_c8toc16
/* >> unicode_c8toc16(3)
 * @return: *:          Success (*pc16 was filled; the return value is the number of bytes taken from `s')
 * @return: 0:          Success (*pc16 was filled; `mbs' was modified, but nothing was read from `s'; in this case, a surrogate was written)
 * @return: (size_t)-1: Unicode error (the given input string isn't a valid unicode sequence)
 * @return: (size_t)-2: Success, but no character was generated (s...+=n, together with `mbs' doesn't for a full character, but `mbs' was updated) */
__CREDIRECT(__ATTR_NONNULL((1, 2, 4)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_unicode_c8toc16,(__CHAR16_TYPE__ *__restrict __pc16, char const *__restrict __s, __SIZE_TYPE__ __n, struct __mbstate *__restrict __mbs),unicode_c8toc16,(__pc16,__s,__n,__mbs))
#else /* __CRT_HAVE_unicode_c8toc16 */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_c8toc16.h>
__NAMESPACE_LOCAL_BEGIN
/* >> unicode_c8toc16(3)
 * @return: *:          Success (*pc16 was filled; the return value is the number of bytes taken from `s')
 * @return: 0:          Success (*pc16 was filled; `mbs' was modified, but nothing was read from `s'; in this case, a surrogate was written)
 * @return: (size_t)-1: Unicode error (the given input string isn't a valid unicode sequence)
 * @return: (size_t)-2: Success, but no character was generated (s...+=n, together with `mbs' doesn't for a full character, but `mbs' was updated) */
#define __localdep_unicode_c8toc16 __LIBC_LOCAL_NAME(unicode_c8toc16)
#endif /* !__CRT_HAVE_unicode_c8toc16 */
#endif /* !__local___localdep_unicode_c8toc16_defined */
/* Dependency: unicode_c8toc32 from unicode */
#ifndef __local___localdep_unicode_c8toc32_defined
#define __local___localdep_unicode_c8toc32_defined 1
#ifdef __CRT_HAVE_unicode_c8toc32
/* >> unicode_c8toc32(3)
 * @return: *:          Success (*pc32 was filled; the return value is the number of bytes taken from `s')
 * @return: (size_t)-1: Unicode error (the given input string isn't a valid unicode sequence)
 * @return: (size_t)-2: Success, but no character was generated (s...+=n, together with `mbs' doesn't for a full character, but `mbs' was updated) */
__CREDIRECT(__ATTR_NONNULL((1, 2, 4)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_unicode_c8toc32,(__CHAR32_TYPE__ *__restrict __pc32, char const *__restrict __s, __SIZE_TYPE__ __n, struct __mbstate *__restrict __mbs),unicode_c8toc32,(__pc32,__s,__n,__mbs))
#else /* __CRT_HAVE_unicode_c8toc32 */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_c8toc32.h>
__NAMESPACE_LOCAL_BEGIN
/* >> unicode_c8toc32(3)
 * @return: *:          Success (*pc32 was filled; the return value is the number of bytes taken from `s')
 * @return: (size_t)-1: Unicode error (the given input string isn't a valid unicode sequence)
 * @return: (size_t)-2: Success, but no character was generated (s...+=n, together with `mbs' doesn't for a full character, but `mbs' was updated) */
#define __localdep_unicode_c8toc32 __LIBC_LOCAL_NAME(unicode_c8toc32)
#endif /* !__CRT_HAVE_unicode_c8toc32 */
#endif /* !__local___localdep_unicode_c8toc32_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(uchar_mbrtoc16) __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(uchar_mbrtoc16))(__CHAR16_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs) {
	__SIZE_TYPE__ __error;
	if (!__mbs) {
		static struct __mbstate __mbrtowc_ps = __MBSTATE_INIT;
		__mbs = &__mbrtowc_ps;
	}
	if (!__str) {
		__mbstate_init(__mbs);
		return 0;
	}
	if (!__maxlen || !*__str)
		return 0;

	__error = __localdep_unicode_c8toc16((__CHAR16_TYPE__ *)__pwc, __str, __maxlen, __mbs);



#ifdef __EILSEQ
	if (__error == (__SIZE_TYPE__)-1)
		(void)__libc_seterrno(__EILSEQ);
#endif /* __EILSEQ */
	return __error;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_uchar_mbrtoc16_defined
#define __local___localdep_uchar_mbrtoc16_defined 1
#define __localdep_uchar_mbrtoc16 __LIBC_LOCAL_NAME(uchar_mbrtoc16)
#endif /* !__local___localdep_uchar_mbrtoc16_defined */
#endif /* !__local_uchar_mbrtoc16_defined */
