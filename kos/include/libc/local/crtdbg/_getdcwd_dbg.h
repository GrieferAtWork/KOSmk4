/* HASH CRC-32:0x63c09c69 */
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
#ifndef __local__getdcwd_dbg_defined
#define __local__getdcwd_dbg_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE__getdcwd
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: _getdcwd from direct */
#ifndef __local___localdep__getdcwd_defined
#define __local___localdep__getdcwd_defined 1
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,char *,__NOTHROW_RPC,__localdep__getdcwd,(int __drive, char *__buf, __SIZE_TYPE__ __size),_getdcwd,(__drive,__buf,__size))
#endif /* !__local___localdep__getdcwd_defined */
__LOCAL_LIBC(_getdcwd_dbg) __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_getdcwd_dbg))(int __driveno, char *__buf, __STDC_INT_AS_SIZE_T __bufsize, int __block_type, char const *__filename, int __line) {
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return __localdep__getdcwd(__driveno, __buf, __bufsize);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__getdcwd_dbg_defined
#define __local___localdep__getdcwd_dbg_defined 1
#define __localdep__getdcwd_dbg __LIBC_LOCAL_NAME(_getdcwd_dbg)
#endif /* !__local___localdep__getdcwd_dbg_defined */
#else /* __CRT_HAVE__getdcwd */
#undef __local__getdcwd_dbg_defined
#endif /* !__CRT_HAVE__getdcwd */
#endif /* !__local__getdcwd_dbg_defined */
