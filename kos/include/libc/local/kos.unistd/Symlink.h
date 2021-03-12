/* HASH CRC-32:0x9a29eff */
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
#ifndef __local_Symlink_defined
#define __local_Symlink_defined 1
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_SymlinkAt)
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: SymlinkAt from kos.unistd */
#ifndef __local___localdep_SymlinkAt_defined
#define __local___localdep_SymlinkAt_defined 1
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `link_text' as link
 * text, at the filesystem location referred to by `tofd:target_path' */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__THROWING,__localdep_SymlinkAt,(char const *__link_text, __fd_t __tofd, char const *__target_path),SymlinkAt,(__link_text,__tofd,__target_path))
#endif /* !__local___localdep_SymlinkAt_defined */
/* >> symlink(3)
 * Create a new symbolic link loaded with `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
__LOCAL_LIBC(Symlink) __ATTR_NONNULL((1, 2)) void
(__LIBCCALL __LIBC_LOCAL_NAME(Symlink))(char const *__link_text, char const *__target_path) __THROWS(...) {
	__localdep_SymlinkAt(__link_text, __AT_FDCWD, __target_path);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_Symlink_defined
#define __local___localdep_Symlink_defined 1
#define __localdep_Symlink __LIBC_LOCAL_NAME(Symlink)
#endif /* !__local___localdep_Symlink_defined */
#else /* __AT_FDCWD && __CRT_HAVE_SymlinkAt */
#undef __local_Symlink_defined
#endif /* !__AT_FDCWD || !__CRT_HAVE_SymlinkAt */
#endif /* !__local_Symlink_defined */
