/* HASH CRC-32:0xdba75ba5 */
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
#ifndef __local_remove_defined
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_removeat)
#define __local_remove_defined 1
/* Dependency: "removeat" */
#ifndef ____localdep_removeat_defined
#define ____localdep_removeat_defined 1
#if defined(__CRT_HAVE_removeat)
/* Remove a file or directory `FILENAME' relative to a given base directory `DIRFD' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_removeat,(__fd_t __dirfd, char const *__filename),removeat,(__dirfd,__filename))
#else /* LIBC: removeat */
#undef ____localdep_removeat_defined
#endif /* removeat... */
#endif /* !____localdep_removeat_defined */

__NAMESPACE_LOCAL_BEGIN
/* Remove a file or directory `FILENAME' */
__LOCAL_LIBC(remove) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(remove))(char const *__filename) {
#line 324 "kos/src/libc/magic/stdio.c"
	return __localdep_removeat(__CRT_AT_FDCWD, __filename);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_removeat) */
#endif /* !__local_remove_defined */
