/* HASH CRC-32:0xdccae402 */
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
#ifndef __local_wctrans_l_defined
#define __local_wctrans_l_defined 1
#include <__crt.h>
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wctrans from wctype */
#ifndef __local___localdep_wctrans_defined
#define __local___localdep_wctrans_defined 1
#ifdef __CRT_HAVE_wctrans
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__wctrans_t,__NOTHROW_NCX,__localdep_wctrans,(char const *__prop),wctrans,(__prop))
#else /* __CRT_HAVE_wctrans */
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/wctrans.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wctrans __LIBC_LOCAL_NAME(wctrans)
#endif /* !__CRT_HAVE_wctrans */
#endif /* !__local___localdep_wctrans_defined */
__LOCAL_LIBC(wctrans_l) __ATTR_WUNUSED __ATTR_NONNULL((1)) __wctrans_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wctrans_l))(char const *__prop, __locale_t __locale) {
	(void)__locale;
	__COMPILER_IMPURE();
	return __localdep_wctrans(__prop);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wctrans_l_defined
#define __local___localdep_wctrans_l_defined 1
#define __localdep_wctrans_l __LIBC_LOCAL_NAME(wctrans_l)
#endif /* !__local___localdep_wctrans_l_defined */
#endif /* !__local_wctrans_l_defined */
