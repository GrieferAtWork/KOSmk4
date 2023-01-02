/* HASH CRC-32:0x5210300c */
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
#ifndef __local_dn_expand_defined
#define __local_dn_expand_defined
#include <__crt.h>
#ifdef __CRT_HAVE_ns_name_uncompress
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ns_name_uncompress_defined
#define __local___localdep_ns_name_uncompress_defined
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ns_name_uncompress,(unsigned char const *__a, unsigned char const *__b, unsigned char const *__c, char *__d, __SIZE_TYPE__ __e),ns_name_uncompress,(__a,__b,__c,__d,__e))
#endif /* !__local___localdep_ns_name_uncompress_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(dn_expand) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(dn_expand))(unsigned char const *__msg_ptr, unsigned char const *__end_of_msg, unsigned char const *__srcbuf, char *__dstbuf, int __dstbufsize) {
	int __n = (__NAMESPACE_LOCAL_SYM __localdep_ns_name_uncompress)(__msg_ptr, __end_of_msg, __srcbuf,
	                           __dstbuf, (__SIZE_TYPE__)__dstbufsize);
	if (__n > 0 && __dstbuf[0] == '.')
		__dstbuf[0] = '\0';
	return __n;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_dn_expand_defined
#define __local___localdep_dn_expand_defined
#define __localdep_dn_expand __LIBC_LOCAL_NAME(dn_expand)
#endif /* !__local___localdep_dn_expand_defined */
#else /* __CRT_HAVE_ns_name_uncompress */
#undef __local_dn_expand_defined
#endif /* !__CRT_HAVE_ns_name_uncompress */
#endif /* !__local_dn_expand_defined */
