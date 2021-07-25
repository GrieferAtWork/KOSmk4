/* HASH CRC-32:0xedf281ac */
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
#ifndef __local_dcgettext_defined
#define __local_dcgettext_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(dcgettext) __ATTR_PURE __ATTR_WUNUSED __ATTR_FORMAT_ARG(2) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(dcgettext))(char const *__domainname, char const *__msgid, int __category) {
	/* Generic no-op that works, but doesn't actually support languages */
	__COMPILER_IMPURE();
	(void)__domainname;
	(void)__category;
	return (char *)__msgid;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_dcgettext_defined
#define __local___localdep_dcgettext_defined 1
#define __localdep_dcgettext __LIBC_LOCAL_NAME(dcgettext)
#endif /* !__local___localdep_dcgettext_defined */
#endif /* !__local_dcgettext_defined */
