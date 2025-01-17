/* HASH CRC-32:0x84d0b1b8 */
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
#ifndef __local_tmpnam_s_defined
#define __local_tmpnam_s_defined
#include <__crt.h>
#ifdef __CRT_HAVE_tmpnam
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_tmpnam_defined
#define __local___localdep_tmpnam_defined
__CREDIRECT(__ATTR_WUNUSED __ATTR_OUT(1),char *,__NOTHROW_NCX,__localdep_tmpnam,(char *__buf),tmpnam,(__buf))
#endif /* !__local___localdep_tmpnam_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(tmpnam_s) __ATTR_OUTS(1, 2) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(tmpnam_s))(char *__restrict __buf, __SIZE_TYPE__ __bufsize) {
	if __unlikely(!__buf) {
#ifdef __EINVAL
		return __EINVAL;
#else /* __EINVAL */
		return 1;
#endif /* !__EINVAL */
	}
	if __unlikely(__bufsize < __L_tmpnam) {
#ifdef __ERANGE
		return __ERANGE; /* XXX: Is this what dos does? */
#else /* __ERANGE */
		return 1;
#endif /* !__ERANGE */
	}
	if __unlikely(!(__NAMESPACE_LOCAL_SYM __localdep_tmpnam)(__buf))
		return __libc_geterrno_or(1);
	return __EOK;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tmpnam_s_defined
#define __local___localdep_tmpnam_s_defined
#define __localdep_tmpnam_s __LIBC_LOCAL_NAME(tmpnam_s)
#endif /* !__local___localdep_tmpnam_s_defined */
#else /* __CRT_HAVE_tmpnam */
#undef __local_tmpnam_s_defined
#endif /* !__CRT_HAVE_tmpnam */
#endif /* !__local_tmpnam_s_defined */
