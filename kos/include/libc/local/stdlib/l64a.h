/* HASH CRC-32:0xea959d43 */
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
#ifndef __local_l64a_defined
#define __local_l64a_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: l64a_r from stdlib */
#ifndef __local___localdep_l64a_r_defined
#define __local___localdep_l64a_r_defined 1
#ifdef __CRT_HAVE_l64a_r
/* >> l64a_r(3)
 * Reentrant variant of `l64a(3)'. Note that the max required buffer size
 * @param: buf:     Target buffer (with a size of `bufsize' bytes)
 * @param: bufsize: Buffer size (including a trailing NUL-character)
 * @return: 0 : Success
 * @return: -1: Buffer too small (`errno' was not modified) */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_l64a_r,(long __n, char *__buf, __STDC_INT_AS_SIZE_T __bufsize),l64a_r,(__n,__buf,__bufsize))
#else /* __CRT_HAVE_l64a_r */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/l64a_r.h>
__NAMESPACE_LOCAL_BEGIN
/* >> l64a_r(3)
 * Reentrant variant of `l64a(3)'. Note that the max required buffer size
 * @param: buf:     Target buffer (with a size of `bufsize' bytes)
 * @param: bufsize: Buffer size (including a trailing NUL-character)
 * @return: 0 : Success
 * @return: -1: Buffer too small (`errno' was not modified) */
#define __localdep_l64a_r __LIBC_LOCAL_NAME(l64a_r)
#endif /* !__CRT_HAVE_l64a_r */
#endif /* !__local___localdep_l64a_r_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> l64a(3), a64l(3)
 * Convert between `long' and base-64 encoded integer strings. */
__LOCAL_LIBC(l64a) __ATTR_RETNONNULL __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(l64a))(long __n) {
	/* l64a_r() encodes 6 bytes from `n' into 1 character, followed
	 * by 1 trailing NUL-character. So we can can calculate the max
	 * required buffer size here, based on `sizeof(long)'! */
	static char __buf[(((sizeof(long) * __CHAR_BIT__) + 5) / 6) + 1];
	__localdep_l64a_r(__n, __buf, sizeof(__buf));
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_l64a_defined
#define __local___localdep_l64a_defined 1
#define __localdep_l64a __LIBC_LOCAL_NAME(l64a)
#endif /* !__local___localdep_l64a_defined */
#endif /* !__local_l64a_defined */
