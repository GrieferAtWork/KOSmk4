/* HASH CRC-32:0xc0896a92 */
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
#ifndef __local_wsymlink_defined
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wsymlinkat)
#define __local_wsymlink_defined 1
/* Dependency: "wsymlinkat" from "parts.wchar.unistd" */
#ifndef ____localdep_wsymlinkat_defined
#define ____localdep_wsymlinkat_defined 1
#ifdef __CRT_HAVE_wsymlinkat
/* >> wsymlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
__CREDIRECT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,__localdep_wsymlinkat,(__WCHAR_TYPE__ const *__link_text, __fd_t __tofd, __WCHAR_TYPE__ const *__target_path),wsymlinkat,(__link_text,__tofd,__target_path))
#else /* LIBC: wsymlinkat */
#undef ____localdep_wsymlinkat_defined
#endif /* wsymlinkat... */
#endif /* !____localdep_wsymlinkat_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> wsymlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `wsymlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__LOCAL_LIBC(wsymlink) __ATTR_NONNULL((1, 2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wsymlink))(__WCHAR_TYPE__ const *__link_text,
                                                      __WCHAR_TYPE__ const *__target_path) {
#line 1490 "kos/src/libc/magic/unistd.c"
	/* TODO: Header-implementation for `symlink()' on DOS (using the windows API) */
	return __localdep_wsymlinkat(__link_text, __CRT_AT_FDCWD, __target_path);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wsymlinkat) */
#endif /* !__local_wsymlink_defined */
