/* HASH CRC-32:0x1a5d8a18 */
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
#ifndef __local__calloc_dbg_defined
#if defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#define __local__calloc_dbg_defined 1
/* Dependency: "calloc" from "stdlib" */
#ifndef ____localdep_calloc_defined
#define ____localdep_calloc_defined 1
#ifdef __std___localdep_calloc_defined
__NAMESPACE_STD_USING(__localdep_calloc)
#elif __has_builtin(__builtin_calloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_calloc)
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __localdep_calloc)(__SIZE_TYPE__ __count, __SIZE_TYPE__ __n_bytes) { return __builtin_calloc(__count, __n_bytes); }
#elif defined(__CRT_HAVE_calloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,__localdep_calloc,(__SIZE_TYPE__ __count, __SIZE_TYPE__ __n_bytes),calloc,(__count,__n_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#include <local/stdlib/calloc.h>
#define __localdep_calloc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(calloc))
#else /* CUSTOM: calloc */
#undef ____localdep_calloc_defined
#endif /* calloc... */
#endif /* !____localdep_calloc_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_calloc_dbg) __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_calloc_dbg))(__SIZE_TYPE__ __count,
                                                         __SIZE_TYPE__ __num_bytes,
                                                         int __block_type,
                                                         char const *__filename,
                                                         int __line) {
#line 295 "kos/src/libc/magic/crtdbg.c"
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return __localdep_calloc(__count, __num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_posix_memalign || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_malloc */
#endif /* !__local__calloc_dbg_defined */
