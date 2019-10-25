/* HASH CRC-32:0x6b5a3ce8 */
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
#ifndef __local_Valloc_defined
#if defined(__CRT_HAVE_Memalign)
#define __local_Valloc_defined 1
#include <hybrid/__limits.h>
/* Dependency: "Memalign" */
#ifndef ____localdep_Memalign_defined
#define ____localdep_Memalign_defined 1
#if defined(__CRT_HAVE_Memalign)
/* @throws: E_BADALLOC: ... */
__CREDIRECT(__ATTR_MALLOC __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_ALIGN(1),void *,__NOTHROW_NCX,__localdep_Memalign,(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),Memalign,(__alignment,__n_bytes))
#else /* LIBC: Memalign */
#undef ____localdep_Memalign_defined
#endif /* Memalign... */
#endif /* !____localdep_Memalign_defined */

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
/* @throws: E_BADALLOC: ... */
__LOCAL_LIBC(Valloc) __ATTR_MALL_PAGEALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(Valloc))(__SIZE_TYPE__ __n_bytes) {
#line 64 "kos/src/libc/magic/kos.malloc.c"
	return __localdep_Memalign(__localdep_getpagesize(), __n_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_Memalign) */
#endif /* !__local_Valloc_defined */
