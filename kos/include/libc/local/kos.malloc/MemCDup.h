/* HASH CRC-32:0x1b225d4f */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_MemCDup_defined
#define __local_MemCDup_defined
#include <__crt.h>
#if defined(__CRT_HAVE_MemDup) || defined(__CRT_HAVE_Malloc)
#include <kos/anno.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_MemDup_defined
#define __local___localdep_MemDup_defined
#ifdef __CRT_HAVE_MemDup
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_INS(1, 2),void *,__THROWING(E_BADALLOC),__localdep_MemDup,(void const *__restrict __ptr, __SIZE_TYPE__ __num_bytes),MemDup,(__ptr,__num_bytes))
#elif defined(__CRT_HAVE_Malloc)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.malloc/MemDup.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_MemDup __LIBC_LOCAL_NAME(MemDup)
#else /* ... */
#undef __local___localdep_MemDup_defined
#endif /* !... */
#endif /* !__local___localdep_MemDup_defined */
#ifndef __local___localdep_memchr_defined
#define __local___localdep_memchr_defined
#ifdef __CRT_HAVE_memchr
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memchr,(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memchr */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memchr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memchr __LIBC_LOCAL_NAME(memchr)
#endif /* !__CRT_HAVE_memchr */
#endif /* !__local___localdep_memchr_defined */
__LOCAL_LIBC(MemCDup) __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) void *
(__LIBCCALL __LIBC_LOCAL_NAME(MemCDup))(void const *__restrict __ptr, int __needle, __SIZE_TYPE__ __num_bytes) __THROWS(E_BADALLOC) {
	if __likely(__num_bytes) {
		void const *__endaddr;
		__endaddr = (__NAMESPACE_LOCAL_SYM __localdep_memchr)(__ptr, __needle, __num_bytes - 1);
		if (__endaddr)
			__num_bytes = ((__UINTPTR_TYPE__)__endaddr - (__UINTPTR_TYPE__)__ptr) + 1;
	}
	return (__NAMESPACE_LOCAL_SYM __localdep_MemDup)(__ptr, __num_bytes);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_MemCDup_defined
#define __local___localdep_MemCDup_defined
#define __localdep_MemCDup __LIBC_LOCAL_NAME(MemCDup)
#endif /* !__local___localdep_MemCDup_defined */
#else /* __CRT_HAVE_MemDup || __CRT_HAVE_Malloc */
#undef __local_MemCDup_defined
#endif /* !__CRT_HAVE_MemDup && !__CRT_HAVE_Malloc */
#endif /* !__local_MemCDup_defined */
