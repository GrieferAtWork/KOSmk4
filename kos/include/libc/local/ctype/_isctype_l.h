/* HASH CRC-32:0xb80c9fc8 */
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
#ifndef __local__isctype_l_defined
#define __local__isctype_l_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__isctype_defined
#define __local___localdep__isctype_defined
#ifdef __CRT_HAVE__isctype
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep__isctype,(int __ch, int __mask),_isctype,(__ch,__mask))
#elif defined(__CRT_HAVE__chvalidator)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep__isctype,(int __ch, int __mask),_chvalidator,(__ch,__mask))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/_isctype.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__isctype __LIBC_LOCAL_NAME(_isctype)
#endif /* !... */
#endif /* !__local___localdep__isctype_defined */
__LOCAL_LIBC(_isctype_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_isctype_l))(int __ch, int __mask, __locale_t __locale) {
	__COMPILER_IMPURE();
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep__isctype)(__ch, __mask);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__isctype_l_defined
#define __local___localdep__isctype_l_defined
#define __localdep__isctype_l __LIBC_LOCAL_NAME(_isctype_l)
#endif /* !__local___localdep__isctype_l_defined */
#endif /* !__local__isctype_l_defined */
