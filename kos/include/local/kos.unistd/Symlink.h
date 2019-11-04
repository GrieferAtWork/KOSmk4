/* HASH CRC-32:0xd69c7f07 */
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
#ifndef __local_Symlink_defined
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_SymlinkAt)
#define __local_Symlink_defined 1
#include <kos/anno.h>
/* Dependency: "SymlinkAt" */
#ifndef ____localdep_SymlinkAt_defined
#define ____localdep_SymlinkAt_defined 1
#ifdef __CRT_HAVE_SymlinkAt
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),,__localdep_SymlinkAt,(char const *__link_text, __fd_t __tofd, char const *__target_path),SymlinkAt,(__link_text,__tofd,__target_path)) __THROWS(...)
#else /* LIBC: SymlinkAt */
#undef ____localdep_SymlinkAt_defined
#endif /* SymlinkAt... */
#endif /* !____localdep_SymlinkAt_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__LOCAL_LIBC(Symlink) __ATTR_NONNULL((1, 2)) void
(__LIBCCALL __LIBC_LOCAL_NAME(Symlink))(char const *__link_text,
                                        char const *__target_path) __THROWS(...) {
#line 522 "kos/src/libc/magic/kos.unistd.c"
	__localdep_SymlinkAt(__link_text, __CRT_AT_FDCWD, __target_path);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_SymlinkAt) */
#endif /* !__local_Symlink_defined */
