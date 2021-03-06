/* HASH CRC-32:0xf712c6ba */
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
#ifndef __local_bzeroc_defined
#define __local_bzeroc_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: bzero from string */
#ifndef __local___localdep_bzero_defined
#define __local___localdep_bzero_defined 1
#ifdef __CRT_HAVE_bzero
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__dst,__num_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/bzero.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bzero __LIBC_LOCAL_NAME(bzero)
#endif /* !... */
#endif /* !__local___localdep_bzero_defined */
/* Dependency: bzerol from string */
#ifndef __local___localdep_bzerol_defined
#define __local___localdep_bzerol_defined 1
#ifdef __CRT_HAVE_bzerol
__CREDIRECT_VOID(__ATTR_LEAF __ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_bzerol,(void *__restrict __dst, __SIZE_TYPE__ __num_dwords),bzerol,(__dst,__num_dwords))
#else /* __CRT_HAVE_bzerol */
__NAMESPACE_LOCAL_END
#include <libc/local/string/bzerol.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bzerol __LIBC_LOCAL_NAME(bzerol)
#endif /* !__CRT_HAVE_bzerol */
#endif /* !__local___localdep_bzerol_defined */
/* Dependency: bzeroq from string */
#ifndef __local___localdep_bzeroq_defined
#define __local___localdep_bzeroq_defined 1
#ifdef __CRT_HAVE_bzeroq
__CREDIRECT_VOID(__ATTR_LEAF __ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_bzeroq,(void *__restrict __dst, __SIZE_TYPE__ __num_qwords),bzeroq,(__dst,__num_qwords))
#else /* __CRT_HAVE_bzeroq */
__NAMESPACE_LOCAL_END
#include <libc/local/string/bzeroq.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bzeroq __LIBC_LOCAL_NAME(bzeroq)
#endif /* !__CRT_HAVE_bzeroq */
#endif /* !__local___localdep_bzeroq_defined */
/* Dependency: bzerow from string */
#ifndef __local___localdep_bzerow_defined
#define __local___localdep_bzerow_defined 1
#ifdef __CRT_HAVE_bzerow
__CREDIRECT_VOID(__ATTR_LEAF __ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_bzerow,(void *__restrict __dst, __SIZE_TYPE__ __num_words),bzerow,(__dst,__num_words))
#else /* __CRT_HAVE_bzerow */
__NAMESPACE_LOCAL_END
#include <libc/local/string/bzerow.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bzerow __LIBC_LOCAL_NAME(bzerow)
#endif /* !__CRT_HAVE_bzerow */
#endif /* !__local___localdep_bzerow_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/host.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(bzeroc) __ATTR_LEAF __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(bzeroc))(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (__elem_size) {

	case 1:
		__localdep_bzero(__dst, __elem_count);
		break;

	case 2:
		__localdep_bzerow(__dst, __elem_count);
		break;

	case 4:
		__localdep_bzerol(__dst, __elem_count);
		break;

#ifdef __UINT64_TYPE__
	case 8:
		__localdep_bzeroq(__dst, __elem_count);
		break;
#endif /* __UINT64_TYPE__ */

	default:
		__localdep_bzero(__dst, __elem_count * __elem_size);
		break;
	}
#else /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	__localdep_bzero(__dst, __elem_count * __elem_size);
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_bzeroc_defined
#define __local___localdep_bzeroc_defined 1
#define __localdep_bzeroc __LIBC_LOCAL_NAME(bzeroc)
#endif /* !__local___localdep_bzeroc_defined */
#endif /* !__local_bzeroc_defined */
