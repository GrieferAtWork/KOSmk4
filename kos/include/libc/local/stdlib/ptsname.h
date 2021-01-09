/* HASH CRC-32:0x3abca81f */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_ptsname_defined
#define __local_ptsname_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_ptsname_r
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: ptsname_r from stdlib */
#ifndef __local___localdep_ptsname_r_defined
#define __local___localdep_ptsname_r_defined 1
/* Returns the name of the PTY slave (Pseudo TTY slave)
 * associated with the master descriptor `FD' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ptsname_r,(__fd_t __fd, char *__buf, __SIZE_TYPE__ __buflen),ptsname_r,(__fd,__buf,__buflen))
#endif /* !__local___localdep_ptsname_r_defined */
/* Returns the name of the PTY slave (Pseudo TTY slave)
 * associated with the master descriptor `FD' */
__LOCAL_LIBC(ptsname) __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ptsname))(__fd_t __fd) {
	static char __buf[64];
	if __unlikely(__localdep_ptsname_r(__fd, __buf, sizeof(__buf)))
		return __NULLPTR;
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ptsname_defined
#define __local___localdep_ptsname_defined 1
#define __localdep_ptsname __LIBC_LOCAL_NAME(ptsname)
#endif /* !__local___localdep_ptsname_defined */
#else /* __CRT_HAVE_ptsname_r */
#undef __local_ptsname_defined
#endif /* !__CRT_HAVE_ptsname_r */
#endif /* !__local_ptsname_defined */
