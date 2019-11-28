/* HASH CRC-32:0xc78fcd98 */
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
#ifndef __local_tmpnam_r_defined
#ifdef __CRT_HAVE_tmpnam
#define __local_tmpnam_r_defined 1
/* Dependency: "tmpnam" */
#ifndef ____localdep_tmpnam_defined
#define ____localdep_tmpnam_defined 1
#ifdef __CRT_HAVE_tmpnam
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_tmpnam,(char *__buf),tmpnam,(__buf))
#else /* LIBC: tmpnam */
#undef ____localdep_tmpnam_defined
#endif /* tmpnam... */
#endif /* !____localdep_tmpnam_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(tmpnam_r) __ATTR_WUNUSED __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(tmpnam_r))(char *__buf) {
#line 1099 "kos/src/libc/magic/stdio.c"
	return __buf ? __localdep_tmpnam(__buf) : __NULLPTR;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_tmpnam */
#endif /* !__local_tmpnam_r_defined */
