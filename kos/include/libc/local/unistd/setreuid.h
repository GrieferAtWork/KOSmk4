/* HASH CRC-32:0xf9a158e1 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_setreuid_defined
#define __local_setreuid_defined
#include <__crt.h>
#ifdef __CRT_HAVE_setresuid
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_setresuid_defined
#define __local___localdep_setresuid_defined
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_setresuid,(__uid_t __ruid, __uid_t __euid, __uid_t __suid),setresuid,(__ruid,__euid,__suid))
#endif /* !__local___localdep_setresuid_defined */
__LOCAL_LIBC(setreuid) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(setreuid))(__uid_t __ruid, __uid_t __euid) {
	return (__NAMESPACE_LOCAL_SYM __localdep_setresuid)(__ruid, __euid, (__uid_t)-1);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_setreuid_defined
#define __local___localdep_setreuid_defined
#define __localdep_setreuid __LIBC_LOCAL_NAME(setreuid)
#endif /* !__local___localdep_setreuid_defined */
#else /* __CRT_HAVE_setresuid */
#undef __local_setreuid_defined
#endif /* !__CRT_HAVE_setresuid */
#endif /* !__local_setreuid_defined */
