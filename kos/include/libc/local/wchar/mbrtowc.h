/* HASH CRC-32:0x68f5924c */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_mbrtowc_defined
#define __local_mbrtowc_defined
#include <__crt.h>
#include <bits/crt/mbstate.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_unicode_c8toc16_defined
#define __local___localdep_unicode_c8toc16_defined
#ifdef __CRT_HAVE_unicode_c8toc16
__CREDIRECT(__ATTR_ACCESS_ROS(2, 3) __ATTR_ACCESS_RW(4) __ATTR_ACCESS_WR(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_unicode_c8toc16,(__CHAR16_TYPE__ *__restrict __pc16, char const *__restrict __s, __SIZE_TYPE__ __n, struct __mbstate *__restrict __mbs),unicode_c8toc16,(__pc16,__s,__n,__mbs))
#else /* __CRT_HAVE_unicode_c8toc16 */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_c8toc16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_c8toc16 __LIBC_LOCAL_NAME(unicode_c8toc16)
#endif /* !__CRT_HAVE_unicode_c8toc16 */
#endif /* !__local___localdep_unicode_c8toc16_defined */
#ifndef __local___localdep_unicode_c8toc32_defined
#define __local___localdep_unicode_c8toc32_defined
#ifdef __CRT_HAVE_unicode_c8toc32
__CREDIRECT(__ATTR_ACCESS_ROS(2, 3) __ATTR_ACCESS_RW(4) __ATTR_ACCESS_WR(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_unicode_c8toc32,(__CHAR32_TYPE__ *__restrict __pc32, char const *__restrict __s, __SIZE_TYPE__ __n, struct __mbstate *__restrict __mbs),unicode_c8toc32,(__pc32,__s,__n,__mbs))
#else /* __CRT_HAVE_unicode_c8toc32 */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_c8toc32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_c8toc32 __LIBC_LOCAL_NAME(unicode_c8toc32)
#endif /* !__CRT_HAVE_unicode_c8toc32 */
#endif /* !__local___localdep_unicode_c8toc32_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(mbrtowc) __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW_OPT(4) __ATTR_ACCESS_WR_OPT(1) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mbrtowc))(__WCHAR_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs) {
	__SIZE_TYPE__ __error;
	__WCHAR_TYPE__ __fallback_wc;
	if (__mbs == __NULLPTR) {
		/* TODO: For whatever reason, libc4/5 exported this `mbrtowc_ps' as `_mb_shift' */
		static struct __mbstate __mbrtowc_ps = __MBSTATE_INIT;
		__mbs = &__mbrtowc_ps;
	}
	if (__str == __NULLPTR) {
		__mbstate_init(__mbs);
		return 0;
	}
	if (__maxlen == 0 || *__str == '\0')
		return 0;
	if __unlikely(__pwc == __NULLPTR)
		__pwc = &__fallback_wc;
#if __SIZEOF_WCHAR_T__ == 2
	__error = (__NAMESPACE_LOCAL_SYM __localdep_unicode_c8toc16)((__CHAR16_TYPE__ *)__pwc, __str, __maxlen, __mbs);
#else /* __SIZEOF_WCHAR_T__ == 2 */
	__error = (__NAMESPACE_LOCAL_SYM __localdep_unicode_c8toc32)((__CHAR32_TYPE__ *)__pwc, __str, __maxlen, __mbs);
#endif /* __SIZEOF_WCHAR_T__ != 2 */
#ifdef __EILSEQ
	if (__error == (__SIZE_TYPE__)-1)
		(void)__libc_seterrno(__EILSEQ);
#endif /* __EILSEQ */
	return __error;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mbrtowc_defined
#define __local___localdep_mbrtowc_defined
#define __localdep_mbrtowc __LIBC_LOCAL_NAME(mbrtowc)
#endif /* !__local___localdep_mbrtowc_defined */
#endif /* !__local_mbrtowc_defined */
