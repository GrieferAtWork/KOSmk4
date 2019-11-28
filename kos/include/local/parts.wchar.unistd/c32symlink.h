/* HASH CRC-32:0xb13517a8 */
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
#ifndef __local_c32symlink_defined
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wsymlinkat)
#define __local_c32symlink_defined 1
/* Dependency: "wsymlinkat" from "parts.wchar.unistd" */
#ifndef ____localdep_c32symlinkat_defined
#define ____localdep_c32symlinkat_defined 1
#if defined(__CRT_HAVE_wsymlinkat) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
__CREDIRECT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,__localdep_c32symlinkat,(__CHAR32_TYPE__ const *__link_text, __fd_t __tofd, __CHAR32_TYPE__ const *__target_path),wsymlinkat,(__link_text,__tofd,__target_path))
#else /* LIBC: wsymlinkat */
#undef ____localdep_c32symlinkat_defined
#endif /* c32symlinkat... */
#endif /* !____localdep_c32symlinkat_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> c32symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `c32symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__LOCAL_LIBC(c32symlink) __ATTR_NONNULL((1, 2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(c32symlink))(__CHAR32_TYPE__ const *__link_text,
                                                        __CHAR32_TYPE__ const *__target_path) {
#line 1486 "kos/src/libc/magic/unistd.c"
	/* TODO: Header-implementation for `symlink()' on DOS (using the windows API) */
	return __localdep_c32symlinkat(__link_text, __CRT_AT_FDCWD, __target_path);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_AT_FDCWD && __CRT_HAVE_wsymlinkat */
#endif /* !__local_c32symlink_defined */
