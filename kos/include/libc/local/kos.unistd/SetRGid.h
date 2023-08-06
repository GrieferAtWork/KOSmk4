/* HASH CRC-32:0x1f782eb8 */
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
#ifndef __local_SetRGid_defined
#define __local_SetRGid_defined
#include <__crt.h>
#ifdef __CRT_HAVE_SetREGid
#include <kos/anno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_SetREGid_defined
#define __local___localdep_SetREGid_defined
__CREDIRECT_VOID(,__THROWING(...),__localdep_SetREGid,(__gid_t __rgid, __gid_t __egid),SetREGid,(__rgid,__egid))
#endif /* !__local___localdep_SetREGid_defined */
__LOCAL_LIBC(SetRGid) void
(__LIBCCALL __LIBC_LOCAL_NAME(SetRGid))(__gid_t __rgid) __THROWS(...) {
	(__NAMESPACE_LOCAL_SYM __localdep_SetREGid)(__rgid, (__gid_t)-1);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_SetRGid_defined
#define __local___localdep_SetRGid_defined
#define __localdep_SetRGid __LIBC_LOCAL_NAME(SetRGid)
#endif /* !__local___localdep_SetRGid_defined */
#else /* __CRT_HAVE_SetREGid */
#undef __local_SetRGid_defined
#endif /* !__CRT_HAVE_SetREGid */
#endif /* !__local_SetRGid_defined */
