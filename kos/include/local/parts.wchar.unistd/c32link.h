/* HASH CRC-32:0x4284e708 */
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
#ifndef __local_c32link_defined
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wlinkat)
#define __local_c32link_defined 1
/* Dependency: "wlinkat" from "parts.wchar.unistd" */
#ifndef ____localdep_c32linkat_defined
#define ____localdep_c32linkat_defined 1
#if defined(__CRT_HAVE_wlinkat) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
__CREDIRECT(__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,__localdep_c32linkat,(__fd_t __fromfd, __CHAR32_TYPE__ const *__from, __fd_t __tofd, __CHAR32_TYPE__ const *__to, __atflag_t __flags),wlinkat,(__fromfd,__from,__tofd,__to,__flags))
#else /* LIBC: wlinkat */
#undef ____localdep_c32linkat_defined
#endif /* c32linkat... */
#endif /* !____localdep_c32linkat_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> c32link(2)
 * Create a hard link from `FROM', leading to `TO' */
__LOCAL_LIBC(c32link) __ATTR_NONNULL((1, 2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(c32link))(__CHAR32_TYPE__ const *__from,
                                                     __CHAR32_TYPE__ const *__to) {
#line 528 "kos/src/libc/magic/unistd.c"
	/* TODO: Header-implementation for `link()' on DOS (using the windows API) */
	return __localdep_c32linkat(__CRT_AT_FDCWD, __from, __CRT_AT_FDCWD, __to, 0);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wlinkat) */
#endif /* !__local_c32link_defined */
