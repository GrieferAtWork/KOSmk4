/* HASH CRC-32:0x72a07368 */
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
#ifndef __local__getdcwd_defined
#define __local__getdcwd_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_frealpath4) && defined(__AT_FDDRIVE_CWD)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_frealpath4_defined
#define __local___localdep_frealpath4_defined
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_WR_OPT(2),char *,__NOTHROW_RPC,__localdep_frealpath4,(__fd_t __fd, char *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),frealpath4,(__fd,__resolved,__buflen,__flags))
#endif /* !__local___localdep_frealpath4_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_getdcwd) __ATTR_ACCESS_WRS(2, 3) char *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_getdcwd))(int __drive, char *__buf, __SIZE_TYPE__ __bufsize) {
	if __unlikely(__drive < __AT_DOS_DRIVEMIN || __drive > __AT_DOS_DRIVEMAX) {
#ifdef __EINVAL
		(void)__libc_seterrno(__EINVAL);
#else /* __EINVAL */
		(void)__libc_seterrno(1);
#endif /* !__EINVAL */
		return __NULLPTR;
	}
	return (__NAMESPACE_LOCAL_SYM __localdep_frealpath4)(__AT_FDDRIVE_CWD(__drive), __buf, __bufsize, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__getdcwd_defined
#define __local___localdep__getdcwd_defined
#define __localdep__getdcwd __LIBC_LOCAL_NAME(_getdcwd)
#endif /* !__local___localdep__getdcwd_defined */
#else /* __CRT_HAVE_frealpath4 && __AT_FDDRIVE_CWD */
#undef __local__getdcwd_defined
#endif /* !__CRT_HAVE_frealpath4 || !__AT_FDDRIVE_CWD */
#endif /* !__local__getdcwd_defined */
