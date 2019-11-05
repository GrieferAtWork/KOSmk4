/* HASH CRC-32:0xb1a79095 */
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
#ifndef __local__aligned_offset_malloc_defined
#if defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#define __local__aligned_offset_malloc_defined 1
/* Dependency: "malloc" from "stdlib" */
#ifndef ____localdep_malloc_defined
#define ____localdep_malloc_defined 1
#ifdef __std___localdep_malloc_defined
__NAMESPACE_STD_USING(__localdep_malloc)
#elif __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL __localdep_malloc)(__SIZE_TYPE__ __n_bytes) { return __builtin_malloc(__n_bytes); }
#elif defined(__CRT_HAVE_malloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __n_bytes),malloc,(__n_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)
#include <local/stdlib/malloc.h>
#define __localdep_malloc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(malloc))
#else /* CUSTOM: malloc */
#undef ____localdep_malloc_defined
#endif /* malloc... */
#endif /* !____localdep_malloc_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_aligned_offset_malloc) __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_aligned_offset_malloc))(__SIZE_TYPE__ __num_bytes,
                                                                    __SIZE_TYPE__ __min_alignment,
                                                                    __SIZE_TYPE__ __offset) {
#line 2431 "kos/src/libc/magic/stdlib.c"
	void *__result;
	__offset &= (__min_alignment - 1);
	__result = __localdep_malloc(__num_bytes + 2 * sizeof(void *) + __min_alignment - 1 + (__min_alignment - __offset));
	if (__result) {
		void *__base = (void *)((((__UINTPTR_TYPE__)__result + (__min_alignment - 1)) & ~(__min_alignment - 1)) + __offset);
		((void **)__base)[-1] = __result;
		((void **)__base)[-2] = (void *)__num_bytes;
		__result = __base;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc) */
#endif /* !__local__aligned_offset_malloc_defined */
