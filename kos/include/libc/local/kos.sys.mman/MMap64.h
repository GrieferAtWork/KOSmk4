/* HASH CRC-32:0x9f95f5d2 */
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
#ifndef __local_MMap64_defined
#define __local_MMap64_defined
#include <__crt.h>
#ifdef __CRT_HAVE_MMap
#include <kos/anno.h>
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_MMap32_defined
#define __local___localdep_MMap32_defined
__CREDIRECT(__ATTR_ACCESS_NONE(1),void *,__THROWING,__localdep_MMap32,(void *__addr, __SIZE_TYPE__ __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __pos32_t __offset),MMap,(__addr,__len,__prot,__flags,__fd,__offset))
#endif /* !__local___localdep_MMap32_defined */
__LOCAL_LIBC(MMap64) __ATTR_WUNUSED __ATTR_ACCESS_NONE(1) void *
(__LIBCCALL __LIBC_LOCAL_NAME(MMap64))(void *__addr, __SIZE_TYPE__ __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __pos64_t __offset) __THROWS(...) {
	return (__NAMESPACE_LOCAL_SYM __localdep_MMap32)(__addr, __len, __prot, __flags, __fd, (__pos32_t)__offset);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_MMap64_defined
#define __local___localdep_MMap64_defined
#define __localdep_MMap64 __LIBC_LOCAL_NAME(MMap64)
#endif /* !__local___localdep_MMap64_defined */
#else /* __CRT_HAVE_MMap */
#undef __local_MMap64_defined
#endif /* !__CRT_HAVE_MMap */
#endif /* !__local_MMap64_defined */
