/* HASH CRC-32:0xba4e76bd */
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
#ifndef __local_dn_skipname_defined
#define __local_dn_skipname_defined
#include <__crt.h>
#ifdef __CRT_HAVE_ns_name_skip
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ns_name_skip_defined
#define __local___localdep_ns_name_skip_defined
__CREDIRECT(__ATTR_INOUT(1) __ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ns_name_skip,(unsigned char const **__p_msg_ptr, unsigned char const *__msg_end),ns_name_skip,(__p_msg_ptr,__msg_end))
#endif /* !__local___localdep_ns_name_skip_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(dn_skipname) __ATTR_IN(1) __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(dn_skipname))(unsigned char const *__msg_ptr, unsigned char const *__end_of_msg) {
	unsigned char const *__orig_msg_ptr = __msg_ptr;
	if ((__NAMESPACE_LOCAL_SYM __localdep_ns_name_skip)(&__msg_ptr, __end_of_msg) == -1)
		return -1;
	return (int)(unsigned int)(__SIZE_TYPE__)(__msg_ptr - __orig_msg_ptr);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_dn_skipname_defined
#define __local___localdep_dn_skipname_defined
#define __localdep_dn_skipname __LIBC_LOCAL_NAME(dn_skipname)
#endif /* !__local___localdep_dn_skipname_defined */
#else /* __CRT_HAVE_ns_name_skip */
#undef __local_dn_skipname_defined
#endif /* !__CRT_HAVE_ns_name_skip */
#endif /* !__local_dn_skipname_defined */
