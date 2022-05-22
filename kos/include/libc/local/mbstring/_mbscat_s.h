/* HASH CRC-32:0x979b5969 */
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
#ifndef __local__mbscat_s_defined
#define __local__mbscat_s_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__mbscat_s_l_defined
#define __local___localdep__mbscat_s_l_defined
#ifdef __CRT_HAVE__mbscat_s_l
__CREDIRECT(__ATTR_IN(3) __ATTR_INOUTS(1, 2),__errno_t,__NOTHROW_NCX,__localdep__mbscat_s_l,(unsigned char *__buf, __SIZE_TYPE__ __true_bufsize, unsigned char const *__src, __locale_t __locale),_mbscat_s_l,(__buf,__true_bufsize,__src,__locale))
#else /* __CRT_HAVE__mbscat_s_l */
__NAMESPACE_LOCAL_END
#include <libc/local/mbstring/_mbscat_s_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__mbscat_s_l __LIBC_LOCAL_NAME(_mbscat_s_l)
#endif /* !__CRT_HAVE__mbscat_s_l */
#endif /* !__local___localdep__mbscat_s_l_defined */
__LOCAL_LIBC(_mbscat_s) __ATTR_IN(3) __ATTR_INOUTS(1, 2) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbscat_s))(unsigned char *__buf, __SIZE_TYPE__ __true_bufsize, unsigned char const *__src) {
	return (__NAMESPACE_LOCAL_SYM __localdep__mbscat_s_l)(__buf, __true_bufsize, __src, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbscat_s_defined
#define __local___localdep__mbscat_s_defined
#define __localdep__mbscat_s __LIBC_LOCAL_NAME(_mbscat_s)
#endif /* !__local___localdep__mbscat_s_defined */
#endif /* !__local__mbscat_s_defined */
