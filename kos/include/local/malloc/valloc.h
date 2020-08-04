/* HASH CRC-32:0xa35bcadf */
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_valloc_defined
#define __local_valloc_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: getpagesize from unistd */
#ifndef __local___localdep_getpagesize_defined
#define __local___localdep_getpagesize_defined 1
#ifdef __CRT_HAVE_getpagesize
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_getpagesize,(void),getpagesize,())
#elif defined(__CRT_HAVE___getpagesize)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_getpagesize,(void),__getpagesize,())
#else /* ... */
__NAMESPACE_LOCAL_END
#include <asm/pagesize.h>
__NAMESPACE_LOCAL_BEGIN
#ifdef __ARCH_PAGESIZE
__NAMESPACE_LOCAL_END
#include <local/unistd/getpagesize.h>
__NAMESPACE_LOCAL_BEGIN
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
#define __localdep_getpagesize __LIBC_LOCAL_NAME(getpagesize)
#else /* __ARCH_PAGESIZE */
#undef __local___localdep_getpagesize_defined
#endif /* !__ARCH_PAGESIZE */
#endif /* !... */
#endif /* !__local___localdep_getpagesize_defined */
/* Dependency: memalign from malloc */
#ifndef __local___localdep_memalign_defined
#define __local___localdep_memalign_defined 1
#if __has_builtin(__builtin_aligned_alloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_aligned_alloc)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_memalign,(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),aligned_alloc,{ return __builtin_aligned_alloc(__alignment, __n_bytes); })
#elif defined(__CRT_HAVE_memalign)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_memalign,(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),memalign,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_aligned_alloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_memalign,(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),aligned_alloc,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <local/malloc/memalign.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memalign __LIBC_LOCAL_NAME(memalign)
#else /* ... */
#undef __local___localdep_memalign_defined
#endif /* !... */
#endif /* !__local___localdep_memalign_defined */
__LOCAL_LIBC(valloc) __ATTR_MALL_PAGEALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(valloc))(__SIZE_TYPE__ __n_bytes) {
	return __localdep_memalign(__localdep_getpagesize(), __n_bytes);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_valloc_defined
#define __local___localdep_valloc_defined 1
#define __localdep_valloc __LIBC_LOCAL_NAME(valloc)
#endif /* !__local___localdep_valloc_defined */
#else /* __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign */
#undef __local_valloc_defined
#endif /* !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE_posix_memalign */
#endif /* !__local_valloc_defined */
