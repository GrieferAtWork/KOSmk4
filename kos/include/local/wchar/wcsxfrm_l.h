/* HASH CRC-32:0x4f32c377 */
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
#ifndef __local_wcsxfrm_l_defined
#define __local_wcsxfrm_l_defined 1
#include <__crt.h>
/* Dependency: "wcsxfrm" from "wchar" */
#ifndef ____localdep_wcsxfrm_defined
#define ____localdep_wcsxfrm_defined 1
#ifdef __std___localdep_wcsxfrm_defined
__NAMESPACE_STD_USING(__localdep_wcsxfrm)
#elif defined(__CRT_HAVE_wcsxfrm)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsxfrm,(__WCHAR_TYPE__ *__dst, __WCHAR_TYPE__ const *__restrict __src, __SIZE_TYPE__ __maxlen),wcsxfrm,(__dst,__src,__maxlen))
#else /* LIBC: wcsxfrm */
#include <local/wchar/wcsxfrm.h>
#define __localdep_wcsxfrm (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm))
#endif /* wcsxfrm... */
#endif /* !____localdep_wcsxfrm_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcsxfrm_l) __ATTR_NONNULL((2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsxfrm_l))(__WCHAR_TYPE__ *__dst,
                                                       __WCHAR_TYPE__ const *__restrict __src,
                                                       __SIZE_TYPE__ __maxlen,
                                                       __locale_t __locale) {
#line 511 "kos/src/libc/magic/string.c"
	(void)__locale;
	return __localdep_wcsxfrm(__dst, __src, __maxlen);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcsxfrm_l_defined */
