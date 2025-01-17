/* HASH CRC-32:0xaf722c8 */
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
#ifndef __local_setregid_defined
#define __local_setregid_defined
#include <__crt.h>
#ifdef __CRT_HAVE_setresgid
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_setresgid_defined
#define __local___localdep_setresgid_defined
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_setresgid,(__gid_t __rgid, __gid_t __egid, __gid_t __sgid),setresgid,(__rgid,__egid,__sgid))
#endif /* !__local___localdep_setresgid_defined */
__LOCAL_LIBC(setregid) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(setregid))(__gid_t __rgid, __gid_t __egid) {
	return (__NAMESPACE_LOCAL_SYM __localdep_setresgid)(__rgid, __egid, (__gid_t)-1);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_setregid_defined
#define __local___localdep_setregid_defined
#define __localdep_setregid __LIBC_LOCAL_NAME(setregid)
#endif /* !__local___localdep_setregid_defined */
#else /* __CRT_HAVE_setresgid */
#undef __local_setregid_defined
#endif /* !__CRT_HAVE_setresgid */
#endif /* !__local_setregid_defined */
