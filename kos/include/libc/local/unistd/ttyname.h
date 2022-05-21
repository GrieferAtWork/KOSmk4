/* HASH CRC-32:0xdda79822 */
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
#ifndef __local_ttyname_defined
#define __local_ttyname_defined
#include <__crt.h>
#ifdef __CRT_HAVE_ttyname_r
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ttyname_r_defined
#define __local___localdep_ttyname_r_defined
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),int,__NOTHROW_RPC,__localdep_ttyname_r,(__fd_t __fd, char *__buf, __SIZE_TYPE__ __buflen),ttyname_r,(__fd,__buf,__buflen))
#endif /* !__local___localdep_ttyname_r_defined */
__LOCAL_LIBC(ttyname) __ATTR_WUNUSED char *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(ttyname))(__fd_t __fd) {
	static char __buf[32];
	if __likely((__NAMESPACE_LOCAL_SYM __localdep_ttyname_r)(__fd, __buf, __COMPILER_LENOF(__buf)) == 0)
		return __buf;
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ttyname_defined
#define __local___localdep_ttyname_defined
#define __localdep_ttyname __LIBC_LOCAL_NAME(ttyname)
#endif /* !__local___localdep_ttyname_defined */
#else /* __CRT_HAVE_ttyname_r */
#undef __local_ttyname_defined
#endif /* !__CRT_HAVE_ttyname_r */
#endif /* !__local_ttyname_defined */
