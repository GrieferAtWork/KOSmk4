/* HASH CRC-32:0xd438f053 */
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
#ifndef __local_mempset_defined
#define __local_mempset_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "memset" from "string" */
#ifndef ____localdep_memset_defined
#define ____localdep_memset_defined 1
#ifdef __fast_memset_defined
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __localdep_memset (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))
#elif defined(__CRT_HAVE_memset)
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* LIBC: memset */
#include <local/string/memset.h>
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __localdep_memset (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memset))
#endif /* memset... */
#endif /* !____localdep_memset_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memset', but return `DST+N_BYTES', rather than `DST' */
__LOCAL_LIBC(mempset) __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mempset))(void *__restrict __dst,
                                                     int __byte,
                                                     __SIZE_TYPE__ __n_bytes) {
#line 2269 "kos/src/libc/magic/string.c"
	return (void *)((__BYTE_TYPE__ *)__localdep_memset(__dst, __byte, __n_bytes) + __n_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_mempset_defined */
