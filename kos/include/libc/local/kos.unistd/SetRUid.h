/* HASH CRC-32:0x6e3e42d0 */
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
#ifndef __local_SetRUid_defined
#define __local_SetRUid_defined
#include <__crt.h>
#ifdef __CRT_HAVE_SetREUid
#include <kos/anno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_SetREUid_defined
#define __local___localdep_SetREUid_defined
__CREDIRECT_VOID(,__THROWING,__localdep_SetREUid,(__uid_t __ruid, __uid_t __euid),SetREUid,(__ruid,__euid))
#endif /* !__local___localdep_SetREUid_defined */
__LOCAL_LIBC(SetRUid) void
(__LIBCCALL __LIBC_LOCAL_NAME(SetRUid))(__uid_t __ruid) __THROWS(...) {
	(__NAMESPACE_LOCAL_SYM __localdep_SetREUid)(__ruid, (__uid_t)-1);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_SetRUid_defined
#define __local___localdep_SetRUid_defined
#define __localdep_SetRUid __LIBC_LOCAL_NAME(SetRUid)
#endif /* !__local___localdep_SetRUid_defined */
#else /* __CRT_HAVE_SetREUid */
#undef __local_SetRUid_defined
#endif /* !__CRT_HAVE_SetREUid */
#endif /* !__local_SetRUid_defined */
