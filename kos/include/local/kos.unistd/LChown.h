/* HASH CRC-32:0x44327f6 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_LChown_defined
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_FChownAt)
#define __local_LChown_defined 1
#include <kos/anno.h>
/* Dependency: "FChownAt" */
#ifndef ____localdep_FChownAt_defined
#define ____localdep_FChownAt_defined 1
#if defined(__CRT_HAVE_FChownAt)
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__CREDIRECT_VOID(__ATTR_NONNULL((2)),,__localdep_FChownAt,(__fd_t __dfd, char const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),FChownAt,(__dfd,__file,__owner,__group,__flags)) __THROWS(...)
#else /* LIBC: FChownAt */
#undef ____localdep_FChownAt_defined
#endif /* FChownAt... */
#endif /* !____localdep_FChownAt_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__LOCAL_LIBC(LChown) __ATTR_NONNULL((1)) void
(__LIBCCALL __LIBC_LOCAL_NAME(LChown))(char const *__file,
                                       __uid_t __owner,
                                       __gid_t __group) __THROWS(...) {
#line 441 "kos/src/libc/magic/kos.unistd.c"
	__localdep_FChownAt(__CRT_AT_FDCWD, __file, __owner, __group, 0x0100); /* AT_SYMLINK_NOFOLLOW */
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_FChownAt) */
#endif /* !__local_LChown_defined */
