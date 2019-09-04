/* HASH 0x271fb354 */
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
#ifndef __local_renameat_defined
#if defined(__CRT_HAVE_frenameat)
#define __local_renameat_defined 1
/* Dependency: "frenameat" */
#ifndef ____localdep_frenameat_defined
#define ____localdep_frenameat_defined 1
#if defined(__CRT_HAVE_frenameat)
/* @param flags: Set of `0|AT_DOSPATH' */
__CREDIRECT(__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,__localdep_frenameat,(__fd_t __oldfd, char const *__oldname, __fd_t __newfd, char const *__newname_or_path, __atflag_t __flags),frenameat,(__oldfd,__oldname,__newfd,__newname_or_path,__flags))
#else /* LIBC: frenameat */
#undef ____localdep_frenameat_defined
#endif /* frenameat... */
#endif /* !____localdep_frenameat_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(renameat) __ATTR_NONNULL((2, 4)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(renameat))(__fd_t __oldfd,
                                                      char const *__oldname,
                                                      __fd_t __newfd,
                                                      char const *__newname_or_path) {
#line 1033 "kos/src/libc/magic/stdio.c"
	return __localdep_frenameat(__oldfd, __oldname, __newfd, __newname_or_path, 0);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_frenameat) */
#endif /* !__local_renameat_defined */
