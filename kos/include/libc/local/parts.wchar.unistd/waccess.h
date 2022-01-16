/* HASH CRC-32:0x7cc4d38a */
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
#ifndef __local_waccess_defined
#define __local_waccess_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_wfaccessat)
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wfaccessat_defined
#define __local___localdep_wfaccessat_defined
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_wfaccessat,(__fd_t __dfd, __WCHAR_TYPE__ const *__file, __STDC_INT_AS_UINT_T __type, __atflag_t __flags),wfaccessat,(__dfd,__file,__type,__flags))
#endif /* !__local___localdep_wfaccessat_defined */
__LOCAL_LIBC(waccess) __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(waccess))(__WCHAR_TYPE__ const *__file, __STDC_INT_AS_UINT_T __type) {
	return (__NAMESPACE_LOCAL_SYM __localdep_wfaccessat)(__AT_FDCWD, __file, __type, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_waccess_defined
#define __local___localdep_waccess_defined
#define __localdep_waccess __LIBC_LOCAL_NAME(waccess)
#endif /* !__local___localdep_waccess_defined */
#else /* __AT_FDCWD && __CRT_HAVE_wfaccessat */
#undef __local_waccess_defined
#endif /* !__AT_FDCWD || !__CRT_HAVE_wfaccessat */
#endif /* !__local_waccess_defined */
