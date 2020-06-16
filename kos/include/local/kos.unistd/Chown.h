/* HASH CRC-32:0xad625f45 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_Chown_defined
#define __local_Chown_defined 1
#include <__crt.h>
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_FChownAt)
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: FChownAt from kos.unistd */
#ifndef __local___localdep_FChownAt_defined
#define __local___localdep_FChownAt_defined 1
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__CREDIRECT_VOID(__ATTR_NONNULL((2)),__THROWING,__localdep_FChownAt,(__fd_t __dfd, char const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),FChownAt,(__dfd,__file,__owner,__group,__flags))
#endif /* !__local___localdep_FChownAt_defined */
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__LOCAL_LIBC(Chown) __ATTR_NONNULL((1)) void
(__LIBCCALL __LIBC_LOCAL_NAME(Chown))(char const *__file, __uid_t __owner, __gid_t __group) __THROWS(...) {
	__localdep_FChownAt(__CRT_AT_FDCWD, __file, __owner, __group, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_Chown_defined
#define __local___localdep_Chown_defined 1
#define __localdep_Chown __LIBC_LOCAL_NAME(Chown)
#endif /* !__local___localdep_Chown_defined */
#else /* __CRT_AT_FDCWD && __CRT_HAVE_FChownAt */
#undef __local_Chown_defined
#endif /* !__CRT_AT_FDCWD || !__CRT_HAVE_FChownAt */
#endif /* !__local_Chown_defined */
