/* HASH CRC-32:0x9ac26c5b */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__wctomb_l_defined
#define __local__wctomb_l_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wctomb_defined
#define __local___localdep_wctomb_defined
#ifdef __CRT_HAVE_wctomb
__CREDIRECT(__ATTR_OUT_OPT(1),int,__NOTHROW_NCX,__localdep_wctomb,(char *__str, __WCHAR_TYPE__ __wc),wctomb,(__str,__wc))
#else /* __CRT_HAVE_wctomb */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/wctomb.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wctomb __LIBC_LOCAL_NAME(wctomb)
#endif /* !__CRT_HAVE_wctomb */
#endif /* !__local___localdep_wctomb_defined */
__LOCAL_LIBC(_wctomb_l) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wctomb_l))(char *__buf, __WCHAR_TYPE__ __wc, __locale_t __locale) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_wctomb)(__buf, __wc);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wctomb_l_defined
#define __local___localdep__wctomb_l_defined
#define __localdep__wctomb_l __LIBC_LOCAL_NAME(_wctomb_l)
#endif /* !__local___localdep__wctomb_l_defined */
#endif /* !__local__wctomb_l_defined */
