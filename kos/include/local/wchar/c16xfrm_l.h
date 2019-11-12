/* HASH CRC-32:0xd9f6d429 */
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
#ifndef __local_c16xfrm_l_defined
#if 1
#define __local_c16xfrm_l_defined 1
/* Dependency: "wcsxfrm" from "wchar" */
#ifndef ____localdep_c16xfrm_defined
#define ____localdep_c16xfrm_defined 1
#if defined(__CRT_HAVE_wcsxfrm) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16xfrm,(__CHAR16_TYPE__ *__dst, __CHAR16_TYPE__ const *__restrict __src, __SIZE_TYPE__ __maxlen),wcsxfrm,(__dst,__src,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsxfrm)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16xfrm,(__CHAR16_TYPE__ *__dst, __CHAR16_TYPE__ const *__restrict __src, __SIZE_TYPE__ __maxlen),wcsxfrm,(__dst,__src,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsxfrm.h>
#define __localdep_c16xfrm(dst, src, maxlen) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm))((__WCHAR_TYPE__ *)(dst), (__WCHAR_TYPE__ const *)(src), maxlen)
#else /* LIBC: c16xfrm */
#include <local/wchar/c16xfrm.h>
#define __localdep_c16xfrm (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16xfrm))
#endif /* c16xfrm... */
#endif /* !____localdep_c16xfrm_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16xfrm_l) __ATTR_NONNULL((2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16xfrm_l))(__CHAR16_TYPE__ *__dst,
                                                       __CHAR16_TYPE__ const *__restrict __src,
                                                       __SIZE_TYPE__ __maxlen,
                                                       __locale_t __locale) {
#line 456 "kos/src/libc/magic/string.c"
	(void)__locale;
	return __localdep_c16xfrm(__dst, __src, __maxlen);
}
__NAMESPACE_LOCAL_END
#endif /* 1 */
#endif /* !__local_c16xfrm_l_defined */
