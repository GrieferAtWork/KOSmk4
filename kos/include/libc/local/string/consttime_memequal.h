/* HASH CRC-32:0xc7644764 */
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
#ifndef __local_consttime_memequal_defined
#define __local_consttime_memequal_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_timingsafe_memcmp_defined
#define __local___localdep_timingsafe_memcmp_defined
#ifdef __CRT_HAVE_timingsafe_memcmp
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 3) __ATTR_ACCESS_ROS(2, 3),int,__NOTHROW_NCX,__localdep_timingsafe_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),timingsafe_memcmp,(__s1,__s2,__n_bytes))
#else /* __CRT_HAVE_timingsafe_memcmp */
__NAMESPACE_LOCAL_END
#include <libc/local/string/timingsafe_memcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_timingsafe_memcmp __LIBC_LOCAL_NAME(timingsafe_memcmp)
#endif /* !__CRT_HAVE_timingsafe_memcmp */
#endif /* !__local___localdep_timingsafe_memcmp_defined */
__LOCAL_LIBC(consttime_memequal) __ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 3) __ATTR_ACCESS_ROS(2, 3) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(consttime_memequal))(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) {
	return (__NAMESPACE_LOCAL_SYM __localdep_timingsafe_memcmp)(__s1, __s2, __n_bytes) == 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_consttime_memequal_defined
#define __local___localdep_consttime_memequal_defined
#define __localdep_consttime_memequal __LIBC_LOCAL_NAME(consttime_memequal)
#endif /* !__local___localdep_consttime_memequal_defined */
#endif /* !__local_consttime_memequal_defined */
