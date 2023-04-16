/* HASH CRC-32:0x2aa1c4c9 */
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
#ifndef __local_WriteAll_defined
#define __local_WriteAll_defined
#include <__crt.h>
#ifdef __CRT_HAVE_Write
#include <kos/anno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_Write_defined
#define __local___localdep_Write_defined
__CREDIRECT(__ATTR_INS(2, 3),__SIZE_TYPE__,__THROWING,__localdep_Write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),Write,(__fd,__buf,__bufsize))
#endif /* !__local___localdep_Write_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(WriteAll) __ATTR_INS(2, 3) __SIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(WriteAll))(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize) __THROWS(...) {
	__SIZE_TYPE__ __result, __temp;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_Write)(__fd, __buf, __bufsize);
	if (__result > 0 && (__SIZE_TYPE__)__result < __bufsize) {
		/* Keep on writing */
		for (;;) {
			__temp = (__NAMESPACE_LOCAL_SYM __localdep_Write)(__fd,
			             (__BYTE_TYPE__ *)__buf + (__SIZE_TYPE__)__result,
			             __bufsize - (__SIZE_TYPE__)__result);
			if (__temp == 0) {
				__result = 0;
				break;
			}
			__result += __temp;
			if (__result >= __bufsize)
				break;
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_WriteAll_defined
#define __local___localdep_WriteAll_defined
#define __localdep_WriteAll __LIBC_LOCAL_NAME(WriteAll)
#endif /* !__local___localdep_WriteAll_defined */
#else /* __CRT_HAVE_Write */
#undef __local_WriteAll_defined
#endif /* !__CRT_HAVE_Write */
#endif /* !__local_WriteAll_defined */
