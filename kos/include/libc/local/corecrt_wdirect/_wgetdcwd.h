/* HASH CRC-32:0x19022acb */
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
#ifndef __local__wgetdcwd_defined
#define __local__wgetdcwd_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_wfrealpath4) || (defined(__CRT_HAVE_frealpath4) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))) && defined(__AT_FDDRIVE_CWD)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wfrealpath4_defined
#define __local___localdep_wfrealpath4_defined
#ifdef __CRT_HAVE_wfrealpath4
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3),__WCHAR_TYPE__ *,__NOTHROW_RPC,__localdep_wfrealpath4,(__fd_t __fd, __WCHAR_TYPE__ *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),wfrealpath4,(__fd,__resolved,__buflen,__flags))
#elif defined(__CRT_HAVE_frealpath4) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.stdlib/wfrealpath4.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wfrealpath4 __LIBC_LOCAL_NAME(wfrealpath4)
#else /* ... */
#undef __local___localdep_wfrealpath4_defined
#endif /* !... */
#endif /* !__local___localdep_wfrealpath4_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_wgetdcwd) __ATTR_OUTS(2, 3) __WCHAR_TYPE__ *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_wgetdcwd))(int __drive, __WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __size) {
	if __unlikely(__drive < __AT_DOS_DRIVEMIN || __drive > __AT_DOS_DRIVEMAX) {
#ifdef __EINVAL
		(void)__libc_seterrno(__EINVAL);
#else /* __EINVAL */
		(void)__libc_seterrno(1);
#endif /* !__EINVAL */
		return __NULLPTR;
	}
	return (__NAMESPACE_LOCAL_SYM __localdep_wfrealpath4)(__AT_FDDRIVE_CWD(__drive), __buf, __size, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wgetdcwd_defined
#define __local___localdep__wgetdcwd_defined
#define __localdep__wgetdcwd __LIBC_LOCAL_NAME(_wgetdcwd)
#endif /* !__local___localdep__wgetdcwd_defined */
#else /* (__CRT_HAVE_wfrealpath4 || (__CRT_HAVE_frealpath4 && (__CRT_HAVE_convert_mbstowcs || __CRT_HAVE_convert_mbstowcsn || ((__CRT_HAVE_format_waprintf_printer || __CRT_HAVE_format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))))) && __AT_FDDRIVE_CWD */
#undef __local__wgetdcwd_defined
#endif /* (!__CRT_HAVE_wfrealpath4 && (!__CRT_HAVE_frealpath4 || (!__CRT_HAVE_convert_mbstowcs && !__CRT_HAVE_convert_mbstowcsn && ((!__CRT_HAVE_format_waprintf_printer && !__CRT_HAVE_format_waprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_format_waprintf_pack && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))))) || !__AT_FDDRIVE_CWD */
#endif /* !__local__wgetdcwd_defined */
