/* HASH CRC-32:0x2ba471c7 */
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
#ifndef __local_symlink_defined
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_symlinkat)
#define __local_symlink_defined 1
/* Dependency: "symlinkat" */
#ifndef ____localdep_symlinkat_defined
#define ____localdep_symlinkat_defined 1
#if defined(__CRT_HAVE_symlinkat)
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
__CREDIRECT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,__localdep_symlinkat,(char const *__link_text, __fd_t __tofd, char const *__target_path),symlinkat,(__link_text,__tofd,__target_path))
#else /* LIBC: symlinkat */
#undef ____localdep_symlinkat_defined
#endif /* symlinkat... */
#endif /* !____localdep_symlinkat_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__LOCAL_LIBC(symlink) __ATTR_NONNULL((1, 2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(symlink))(char const *__link_text,
                                                     char const *__target_path) {
#line 1490 "kos/src/libc/magic/unistd.c"
	/* TODO: Header-implementation for `symlink()' on DOS (using the windows API) */
	return __localdep_symlinkat(__link_text, __CRT_AT_FDCWD, __target_path);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_symlinkat) */
#endif /* !__local_symlink_defined */
