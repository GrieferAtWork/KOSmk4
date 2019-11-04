/* HASH CRC-32:0xe87cc397 */
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
#ifndef __local_memmove_s_defined
#define __local_memmove_s_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <parts/errno.h>
/* Dependency: "memmove" from "string" */
#ifndef ____localdep_memmove_defined
#define ____localdep_memmove_defined 1
#ifdef __fast_memmove_defined
/* Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memmove (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmove))
#elif defined(__CRT_HAVE_memmove)
/* Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmove,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,(__dst,__src,__n_bytes))
#else /* LIBC: memmove */
#include <local/string/memmove.h>
/* Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memmove (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmove))
#endif /* memmove... */
#endif /* !____localdep_memmove_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memmove_s) __ATTR_NONNULL((1, 3)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memmove_s))(void *__dst,
                                                       __SIZE_TYPE__ __dstlength,
                                                       void const *__src,
                                                       __SIZE_TYPE__ __srclength) {
#line 4454 "kos/src/libc/magic/string.c"

	if (!__srclength)
		return 0;
	if (!__dst || !__src)
		return __EINVAL;
	if (__dstlength < __srclength)
		return __ERANGE;
	__localdep_memmove(__dst, __src, __srclength);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memmove_s_defined */
