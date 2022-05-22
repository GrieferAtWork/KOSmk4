/* HASH CRC-32:0x6156f3d5 */
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
#ifndef __local_mknodat_defined
#define __local_mknodat_defined
#include <__crt.h>
#ifdef __CRT_HAVE_fmknodat
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fmknodat_defined
#define __local___localdep_fmknodat_defined
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_RPC,__localdep_fmknodat,(__fd_t __dirfd, char const *__nodename, __mode_t __mode, __dev_t __dev, __atflag_t __flags),fmknodat,(__dirfd,__nodename,__mode,__dev,__flags))
#endif /* !__local___localdep_fmknodat_defined */
__LOCAL_LIBC(mknodat) __ATTR_IN(2) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(mknodat))(__fd_t __dirfd, char const *__nodename, __mode_t __mode, __dev_t __dev) {
	return (__NAMESPACE_LOCAL_SYM __localdep_fmknodat)(__dirfd, __nodename, __mode, __dev, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mknodat_defined
#define __local___localdep_mknodat_defined
#define __localdep_mknodat __LIBC_LOCAL_NAME(mknodat)
#endif /* !__local___localdep_mknodat_defined */
#else /* __CRT_HAVE_fmknodat */
#undef __local_mknodat_defined
#endif /* !__CRT_HAVE_fmknodat */
#endif /* !__local_mknodat_defined */
