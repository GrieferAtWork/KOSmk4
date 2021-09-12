/* HASH CRC-32:0x426a8757 */
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
#ifndef __local_qsort_s_defined
#define __local_qsort_s_defined 1
#include <__crt.h>
#include <kos/anno.h>
#ifndef __dos_compar_d_fn_t_defined
#define __dos_compar_d_fn_t_defined 1
typedef int (__LIBDCALL *__dos_compar_d_fn_t)(void *__arg, void const *__a, void const *__b);
#endif /* !__dos_compar_d_fn_t_defined */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_qsort_r_defined
#define __local___localdep_qsort_r_defined 1
#ifdef __CRT_HAVE_qsort_r
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined 1
typedef int (__LIBKCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NONNULL((1, 4)),__THROWING,__localdep_qsort_r,(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_d_fn_t __cmp, void *__arg),qsort_r,(__pbase,__item_count,__item_size,__cmp,__arg))
#else /* __CRT_HAVE_qsort_r */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/qsort_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_qsort_r __LIBC_LOCAL_NAME(qsort_r)
#endif /* !__CRT_HAVE_qsort_r */
#endif /* !__local___localdep_qsort_r_defined */
__NAMESPACE_LOCAL_END
#ifndef ____invoke_compare_helper_s_defined
#define ____invoke_compare_helper_s_defined 1
__NAMESPACE_LOCAL_BEGIN
struct __invoke_compare_helper_s_data {
	__dos_compar_d_fn_t __fun;
	void               *__arg;
};
__LOCAL_LIBC(__invoke_compare_helper_s) int
(__LIBKCALL __invoke_compare_helper_s)(void const *__a, void const *__b, void *__arg) {
	void *__base_arg = ((struct __invoke_compare_helper_s_data *)__arg)->__arg;
	return (*((struct __invoke_compare_helper_s_data *)__arg)->__fun)(__base_arg, __a, __b);
}
__NAMESPACE_LOCAL_END
#endif /* !____invoke_compare_helper_s_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(qsort_s) __ATTR_NONNULL((1, 4)) void
(__LIBCCALL __LIBC_LOCAL_NAME(qsort_s))(void *__base, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __dos_compar_d_fn_t __compar, void *__arg) __THROWS(...) {
	struct __NAMESPACE_LOCAL_SYM __invoke_compare_helper_s_data __data;
	__data.__fun = __compar;
	__data.__arg = __arg;
	return (__NAMESPACE_LOCAL_SYM __localdep_qsort_r)(__base, __elem_count, __elem_size,
	               &__NAMESPACE_LOCAL_SYM __invoke_compare_helper_s,
	               &__data);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_qsort_s_defined
#define __local___localdep_qsort_s_defined 1
#define __localdep_qsort_s __LIBC_LOCAL_NAME(qsort_s)
#endif /* !__local___localdep_qsort_s_defined */
#endif /* !__local_qsort_s_defined */
