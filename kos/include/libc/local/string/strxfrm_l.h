/* HASH CRC-32:0xc9428ff7 */
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
#ifndef __local_strxfrm_l_defined
#define __local_strxfrm_l_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strxfrm_defined
#define __local___localdep_strxfrm_defined
#ifdef __CRT_HAVE_strxfrm
__CREDIRECT(__ATTR_ACCESS_ROS(2, 3) __ATTR_ACCESS_WRS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strxfrm,(char *__dst, char const *__restrict __src, __SIZE_TYPE__ __buflen),strxfrm,(__dst,__src,__buflen))
#else /* __CRT_HAVE_strxfrm */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strxfrm.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strxfrm __LIBC_LOCAL_NAME(strxfrm)
#endif /* !__CRT_HAVE_strxfrm */
#endif /* !__local___localdep_strxfrm_defined */
__LOCAL_LIBC(strxfrm_l) __ATTR_ACCESS_ROS(2, 3) __ATTR_ACCESS_WRS(1, 3) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strxfrm_l))(char *__dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_strxfrm)(__dst, __src, __buflen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strxfrm_l_defined
#define __local___localdep_strxfrm_l_defined
#define __localdep_strxfrm_l __LIBC_LOCAL_NAME(strxfrm_l)
#endif /* !__local___localdep_strxfrm_l_defined */
#endif /* !__local_strxfrm_l_defined */
