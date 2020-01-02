/* HASH CRC-32:0x558d53a9 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
#ifndef __local_mempmoveupl_defined
#define __local_mempmoveupl_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "memmoveupl" from "string" */
#ifndef ____localdep_memmoveupl_defined
#define ____localdep_memmoveupl_defined 1
#ifdef __fast_memmoveupl_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
#define __localdep_memmoveupl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupl))
#elif defined(__CRT_HAVE_memmoveupl)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupl,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords),memmoveupl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 4)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupl,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_memmovel)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupl,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords),memmovel,(__dst,__src,__n_dwords))
#else /* LIBC: memmoveupl */
#include <local/string/memmoveupl.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
#define __localdep_memmoveupl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveupl))
#endif /* memmoveupl... */
#endif /* !____localdep_memmoveupl_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST >= SRC || !N_DWORDS') */
__LOCAL_LIBC(mempmoveupl) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mempmoveupl))(/*aligned(4)*/ void *__dst,
                                                         /*aligned(4)*/ void const *__src,
                                                         __SIZE_TYPE__ __n_dwords) {
#line 1195 "kos/src/libc/magic/string.c"
	return (__UINT32_TYPE__ *)__localdep_memmoveupl(__dst, __src, __n_dwords) + __n_dwords;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_mempmoveupl_defined */
