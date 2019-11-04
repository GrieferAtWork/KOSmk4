/* HASH CRC-32:0x6e80c434 */
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
#ifndef __local_valloc_defined
#if defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)
#define __local_valloc_defined 1
#include <hybrid/__limits.h>
/* Dependency: "memalign" from "malloc" */
#ifndef ____localdep_memalign_defined
#define ____localdep_memalign_defined 1
#if defined(__CRT_HAVE_memalign)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_ALIGN(1),void *,__NOTHROW_NCX,__localdep_memalign,(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),memalign,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_aligned_alloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_ALIGN(1),void *,__NOTHROW_NCX,__localdep_memalign,(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),aligned_alloc,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_posix_memalign)
#include <local/malloc/memalign.h>
#define __localdep_memalign (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memalign))
#else /* CUSTOM: memalign */
#undef ____localdep_memalign_defined
#endif /* memalign... */
#endif /* !____localdep_memalign_defined */

/* Dependency: "getpagesize" from "unistd" */
#ifndef ____localdep_getpagesize_defined
#define ____localdep_getpagesize_defined 1
#if defined(__CRT_HAVE_getpagesize)
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_getpagesize,(void),getpagesize,())
#elif defined(__CRT_HAVE___getpagesize)
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_getpagesize,(void),__getpagesize,())
#else /* LIBC: getpagesize */
#include <local/unistd/getpagesize.h>
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
#define __localdep_getpagesize (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getpagesize))
#endif /* getpagesize... */
#endif /* !____localdep_getpagesize_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(valloc) __ATTR_MALL_PAGEALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(valloc))(__SIZE_TYPE__ __n_bytes) {
#line 96 "kos/src/libc/magic/malloc.c"
	return __localdep_memalign(__localdep_getpagesize(), __n_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) */
#endif /* !__local_valloc_defined */
