/* HASH 0x977647f9 */
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
#ifndef __local_c16symlink_defined
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wsymlinkat)
#define __local_c16symlink_defined 1
/* Dependency: "wsymlinkat" from "parts.wchar.unistd" */
#ifndef ____localdep_c16symlinkat_defined
#define ____localdep_c16symlinkat_defined 1
#if defined(__CRT_HAVE_wsymlinkat) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16symlinkat(3)
 * Create a new symbolic link loaded with `FROM' as link
 * text, at the filesystem location referred to by `TOFD:TO' */
__CREDIRECT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,__localdep_c16symlinkat,(__CHAR16_TYPE__ const *__from, __fd_t __tofd, __CHAR16_TYPE__ const *__to),wsymlinkat,(__from,__tofd,__to))
#elif defined(__CRT_HAVE_DOS$wsymlinkat)
/* >> c16symlinkat(3)
 * Create a new symbolic link loaded with `FROM' as link
 * text, at the filesystem location referred to by `TOFD:TO' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,__localdep_c16symlinkat,(__CHAR16_TYPE__ const *__from, __fd_t __tofd, __CHAR16_TYPE__ const *__to),wsymlinkat,(__from,__tofd,__to))
#else /* LIBC: wsymlinkat */
#undef ____localdep_c16symlinkat_defined
#endif /* c16symlinkat... */
#endif /* !____localdep_c16symlinkat_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> c16symlink(3)
 * Create a new symbolic link loaded with `FROM' as link
 * text, at the filesystem location referred to by `TO'.
 * Same as `c16symlinkat(FROM, AT_FDCWD, TO)' */
__LOCAL_LIBC(c16symlink) __ATTR_NONNULL((1, 2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(c16symlink))(__CHAR16_TYPE__ const *__from,
                                                        __CHAR16_TYPE__ const *__to) {
#line 1421 "kos/src/libc/magic/unistd.c"
	/* TODO: Header-implementation for `symlink()' on DOS (using the windows API) */
	return __localdep_c16symlinkat(__from, __CRT_AT_FDCWD, __to);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wsymlinkat) */
#endif /* !__local_c16symlink_defined */
