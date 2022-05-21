/* HASH CRC-32:0xb65ac39d */
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
#ifndef __local__getdcwd_dbg_defined
#define __local__getdcwd_dbg_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE__getdcwd) || defined(__CRT_HAVE__getdcwd_nolock) || (defined(__CRT_HAVE_frealpath4) && defined(__AT_FDDRIVE_CWD))
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__getdcwd_defined
#define __local___localdep__getdcwd_defined
#ifdef __CRT_HAVE__getdcwd
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),char *,__NOTHROW_RPC,__localdep__getdcwd,(int __drive, char *__buf, __SIZE_TYPE__ __bufsize),_getdcwd,(__drive,__buf,__bufsize))
#elif defined(__CRT_HAVE__getdcwd_nolock)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),char *,__NOTHROW_RPC,__localdep__getdcwd,(int __drive, char *__buf, __SIZE_TYPE__ __bufsize),_getdcwd_nolock,(__drive,__buf,__bufsize))
#elif defined(__CRT_HAVE_frealpath4) && defined(__AT_FDDRIVE_CWD)
__NAMESPACE_LOCAL_END
#include <libc/local/direct/_getdcwd.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__getdcwd __LIBC_LOCAL_NAME(_getdcwd)
#else /* ... */
#undef __local___localdep__getdcwd_defined
#endif /* !... */
#endif /* !__local___localdep__getdcwd_defined */
__LOCAL_LIBC(_getdcwd_dbg) __ATTR_WUNUSED __ATTR_ACCESS_WRS(2, 3) char *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_getdcwd_dbg))(int __driveno, char *__buf, __STDC_INT_AS_SIZE_T __bufsize, int __block_type, char const *__filename, int __line) {
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return (__NAMESPACE_LOCAL_SYM __localdep__getdcwd)(__driveno, __buf, __bufsize);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__getdcwd_dbg_defined
#define __local___localdep__getdcwd_dbg_defined
#define __localdep__getdcwd_dbg __LIBC_LOCAL_NAME(_getdcwd_dbg)
#endif /* !__local___localdep__getdcwd_dbg_defined */
#else /* __CRT_HAVE__getdcwd || __CRT_HAVE__getdcwd_nolock || (__CRT_HAVE_frealpath4 && __AT_FDDRIVE_CWD) */
#undef __local__getdcwd_dbg_defined
#endif /* !__CRT_HAVE__getdcwd && !__CRT_HAVE__getdcwd_nolock && (!__CRT_HAVE_frealpath4 || !__AT_FDDRIVE_CWD) */
#endif /* !__local__getdcwd_dbg_defined */
