/* HASH CRC-32:0xa460ffa8 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_Valloc_defined
#define __local_Valloc_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_Memalign
#include <kos/anno.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: Memalign from kos.malloc */
#ifndef __local___localdep_Memalign_defined
#define __local___localdep_Memalign_defined 1
__CREDIRECT(__ATTR_MALLOC __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__THROWING,__localdep_Memalign,(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __num_bytes),Memalign,(__alignment,__num_bytes))
#endif /* !__local___localdep_Memalign_defined */
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
#include <libc/local/unistd/getpagesize.h>
__NAMESPACE_LOCAL_BEGIN
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
#define __localdep_getpagesize __LIBC_LOCAL_NAME(getpagesize)
#else /* __ARCH_PAGESIZE */
#undef __local___localdep_getpagesize_defined
#endif /* !__ARCH_PAGESIZE */
#endif /* !... */
#endif /* !__local___localdep_getpagesize_defined */
__LOCAL_LIBC(Valloc) __ATTR_MALLOC __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_MALL_PAGEALIGNED __ATTR_ALLOC_SIZE((1)) void *
(__LIBCCALL __LIBC_LOCAL_NAME(Valloc))(__SIZE_TYPE__ __num_bytes) __THROWS(__E_BADALLOC) {
	return __localdep_Memalign(__localdep_getpagesize(), __num_bytes);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_Valloc_defined
#define __local___localdep_Valloc_defined 1
#define __localdep_Valloc __LIBC_LOCAL_NAME(Valloc)
#endif /* !__local___localdep_Valloc_defined */
#else /* __CRT_HAVE_Memalign */
#undef __local_Valloc_defined
#endif /* !__CRT_HAVE_Memalign */
#endif /* !__local_Valloc_defined */
