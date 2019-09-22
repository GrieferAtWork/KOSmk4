/* HASH CRC-32:0x771e36d3 */
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
#ifndef __local_posix_memalign_defined
#if (defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc))
#define __local_posix_memalign_defined 1
#include <parts/errno.h>
/* Dependency: "memalign" from "malloc" */
#ifndef ____localdep_memalign_defined
#define ____localdep_memalign_defined 1
#if defined(__CRT_HAVE_memalign)
__CREDIRECT(__ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)) __ATTR_MALLOC,void *,__NOTHROW_NCX,__localdep_memalign,(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),memalign,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_aligned_alloc)
__CREDIRECT(__ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)) __ATTR_MALLOC,void *,__NOTHROW_NCX,__localdep_memalign,(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),aligned_alloc,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_posix_memalign)
#include <local/malloc/memalign.h>
#define __localdep_memalign (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memalign))
#else /* CUSTOM: memalign */
#undef ____localdep_memalign_defined
#endif /* memalign... */
#endif /* !____localdep_memalign_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(posix_memalign) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(posix_memalign))(void **__restrict __pp,
                                                            __SIZE_TYPE__ __alignment,
                                                            __SIZE_TYPE__ __n_bytes) {
#line 134 "kos/src/libc/magic/malloc.c"
	void *__result;
	__SIZE_TYPE__ __d = __alignment / sizeof(void *);
	__SIZE_TYPE__ __r = __alignment % sizeof(void *);
	if (__r != 0 || !__d || (__d & (__d - 1)) != 0)
		return __EINVAL;
	__result = __localdep_memalign(__alignment, __n_bytes);
	if (!__result)
		return __ENOMEM;
	*__pp = __result;
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)) */
#endif /* !__local_posix_memalign_defined */
