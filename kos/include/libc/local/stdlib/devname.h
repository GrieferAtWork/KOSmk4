/* HASH CRC-32:0xc66994b5 */
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
#ifndef __local_devname_defined
#define __local_devname_defined
#include <__crt.h>
#ifdef __CRT_HAVE_devname_r
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_devname_r_defined
#define __local___localdep_devname_r_defined
__CREDIRECT(__ATTR_OUTS(3, 4),int,__NOTHROW_NCX,__localdep_devname_r,(__dev_t __dev, __mode_t __type, char *__buf, __SIZE_TYPE__ __len),devname_r,(__dev,__type,__buf,__len))
#endif /* !__local___localdep_devname_r_defined */
__LOCAL_LIBC(devname) __ATTR_CONST char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(devname))(__dev_t __dev, __mode_t __type) {
	static char __buf[64];
	return (__NAMESPACE_LOCAL_SYM __localdep_devname_r)(__dev, __type, __buf, sizeof(__buf)) ? __NULLPTR : __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_devname_defined
#define __local___localdep_devname_defined
#define __localdep_devname __LIBC_LOCAL_NAME(devname)
#endif /* !__local___localdep_devname_defined */
#else /* __CRT_HAVE_devname_r */
#undef __local_devname_defined
#endif /* !__CRT_HAVE_devname_r */
#endif /* !__local_devname_defined */
