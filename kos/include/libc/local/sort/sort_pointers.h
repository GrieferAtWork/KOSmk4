/* HASH CRC-32:0xcbb33aa1 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_sort_pointers_defined
#define __local_sort_pointers_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_qsort_defined
#define __local___localdep_qsort_defined
#ifdef __CRT_HAVE_qsort
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NONNULL((1, 4)),__THROWING,__localdep_qsort,(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),qsort,(__pbase,__item_count,__item_size,__compar))
#else /* __CRT_HAVE_qsort */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/qsort.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_qsort __LIBC_LOCAL_NAME(qsort)
#endif /* !__CRT_HAVE_qsort */
#endif /* !__local___localdep_qsort_defined */
__NAMESPACE_LOCAL_END
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sort_pointers_compar) __ATTR_PURE int
(__LIBCCALL __sort_pointers_compar)(void const *__a, void const *__b) {
	__BYTE_TYPE__ *__lhs = *(__BYTE_TYPE__ **)__a;
	__BYTE_TYPE__ *__rhs = *(__BYTE_TYPE__ **)__b;
#if __SIZEOF_POINTER__ < __SIZEOF_INT__
	return (int)(__UINTPTR_TYPE__)__lhs - (int)(__UINTPTR_TYPE__)__rhs;
#else /* __SIZEOF_POINTER__ < __SIZEOF_INT__ */
	if (__lhs < __rhs)
		return -1;
	if (__lhs > __rhs)
		return 1;
	return 0;
#endif /* __SIZEOF_POINTER__ >= __SIZEOF_INT__ */
}
__NAMESPACE_LOCAL_END
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sort_pointers) __ATTR_NONNULL((2, 3)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sort_pointers))(__SIZE_TYPE__ __count, void **__sortme, void **__work) {
	(void)__work; /* unused by this implementation */
	(__NAMESPACE_LOCAL_SYM __localdep_qsort)(__sortme, __count, sizeof(void *), &__NAMESPACE_LOCAL_SYM __sort_pointers_compar);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sort_pointers_defined
#define __local___localdep_sort_pointers_defined
#define __localdep_sort_pointers __LIBC_LOCAL_NAME(sort_pointers)
#endif /* !__local___localdep_sort_pointers_defined */
#endif /* !__local_sort_pointers_defined */
