/* HASH CRC-32:0xaf29806b */
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
#ifndef __local__mbsbtype_defined
#define __local__mbsbtype_defined
#include <__crt.h>
#ifdef __CRT_HAVE__mbsbtype_l
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__mbsbtype_l_defined
#define __local___localdep__mbsbtype_l_defined
__CREDIRECT(,int,__NOTHROW_NCX,__localdep__mbsbtype_l,(unsigned char const *__str, __SIZE_TYPE__ __pos, __locale_t __locale),_mbsbtype_l,(__str,__pos,__locale))
#endif /* !__local___localdep__mbsbtype_l_defined */
__LOCAL_LIBC(_mbsbtype) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbsbtype))(unsigned char const *__str, __SIZE_TYPE__ __pos) {
	return (__NAMESPACE_LOCAL_SYM __localdep__mbsbtype_l)(__str, __pos, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbsbtype_defined
#define __local___localdep__mbsbtype_defined
#define __localdep__mbsbtype __LIBC_LOCAL_NAME(_mbsbtype)
#endif /* !__local___localdep__mbsbtype_defined */
#else /* __CRT_HAVE__mbsbtype_l */
#undef __local__mbsbtype_defined
#endif /* !__CRT_HAVE__mbsbtype_l */
#endif /* !__local__mbsbtype_defined */
