/* HASH CRC-32:0xb1afea3c */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__ismbckata_l_defined
#define __local__ismbckata_l_defined
#include <__crt.h>
#ifdef __CRT_HAVE__getmbcp
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__getmbcp_l_defined
#define __local___localdep__getmbcp_l_defined
__NAMESPACE_LOCAL_END
#include <libc/local/mbctype/_getmbcp_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__getmbcp_l __LIBC_LOCAL_NAME(_getmbcp_l)
#endif /* !__local___localdep__getmbcp_l_defined */
__LOCAL_LIBC(_ismbckata_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_ismbckata_l))(unsigned int __ch, __locale_t __locale) {
	/* Extrapolated from reverse engineering. */
	if ((__NAMESPACE_LOCAL_SYM __localdep__getmbcp_l)(__locale) != 932)
		return 0;
	if (__ch > 0x833f && __ch < 0x8397 && __ch != 0x837f)
		return 1;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__ismbckata_l_defined
#define __local___localdep__ismbckata_l_defined
#define __localdep__ismbckata_l __LIBC_LOCAL_NAME(_ismbckata_l)
#endif /* !__local___localdep__ismbckata_l_defined */
#else /* __CRT_HAVE__getmbcp */
#undef __local__ismbckata_l_defined
#endif /* !__CRT_HAVE__getmbcp */
#endif /* !__local__ismbckata_l_defined */
