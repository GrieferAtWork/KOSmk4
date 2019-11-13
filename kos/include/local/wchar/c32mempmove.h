/* HASH CRC-32:0x45d3fc3f */
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
#ifndef __local_c32mempmove_defined
#define __local_c32mempmove_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "mempmovew" from "string" */
#ifndef ____localdep_mempmovew_defined
#define ____localdep_mempmovew_defined 1
#ifdef __fast_mempmovew_defined
/* Same as `memmovew', but return `DST+N_WORDS', rather than `DST' */
#define __localdep_mempmovew (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovew))
#elif defined(__CRT_HAVE_mempmovew)
/* Same as `memmovew', but return `DST+N_WORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempmovew,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),mempmovew,(__dst,__src,__n_words))
#else /* LIBC: mempmovew */
#include <local/string/mempmovew.h>
/* Same as `memmovew', but return `DST+N_WORDS', rather than `DST' */
#define __localdep_mempmovew (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovew))
#endif /* mempmovew... */
#endif /* !____localdep_mempmovew_defined */

/* Dependency: "mempmovel" from "string" */
#ifndef ____localdep_mempmovel_defined
#define ____localdep_mempmovel_defined 1
#ifdef __fast_mempmovel_defined
/* Same as `memmovew', but return `DST+N_DWORDS', rather than `DST' */
#define __localdep_mempmovel (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovel))
#elif defined(__CRT_HAVE_mempmovel)
/* Same as `memmovew', but return `DST+N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempmovel,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),mempmovel,(__dst,__src,__n_dwords))
#else /* LIBC: mempmovel */
#include <local/string/mempmovel.h>
/* Same as `memmovew', but return `DST+N_DWORDS', rather than `DST' */
#define __localdep_mempmovel (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovel))
#endif /* mempmovel... */
#endif /* !____localdep_mempmovel_defined */

/* Dependency: "mempmove" from "string" */
#ifndef ____localdep_mempmove_defined
#define ____localdep_mempmove_defined 1
#ifdef __fast_mempmove_defined
/* Same as `memmove', but return `DST+N_BYTES', rather than `DST' */
#define __localdep_mempmove (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmove))
#elif defined(__CRT_HAVE_mempmove)
/* Same as `memmove', but return `DST+N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempmove,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmove,(__dst,__src,__n_bytes))
#else /* LIBC: mempmove */
#include <local/string/mempmove.h>
/* Same as `memmove', but return `DST+N_BYTES', rather than `DST' */
#define __localdep_mempmove (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmove))
#endif /* mempmove... */
#endif /* !____localdep_mempmove_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32mempmove) __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32mempmove))(__CHAR32_TYPE__ *__dst,
                                                         __CHAR32_TYPE__ const *__src,
                                                         __SIZE_TYPE__ __num_chars) {
#line 945 "kos/src/libc/magic/wchar.c"
#if 4 == 2
	return (__CHAR32_TYPE__ *)__localdep_mempmovew(__dst, __src, __num_chars);
#elif 4 == 4
	return (__CHAR32_TYPE__ *)__localdep_mempmovel(__dst, __src, __num_chars);
#else
	return (__CHAR32_TYPE__ *)__localdep_mempmove(__dst, __src, __num_chars * sizeof(__CHAR32_TYPE__));
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c32mempmove_defined */
