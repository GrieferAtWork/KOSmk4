/* HASH CRC-32:0x85a66c3c */
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
#ifndef __local_qsort_s_defined
#define __local_qsort_s_defined 1
#include <kos/anno.h>
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined 1
typedef int (__LIBCCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
#ifndef __dos_compar_d_fn_t_defined
#define __dos_compar_d_fn_t_defined 1
typedef int (__LIBCCALL *__dos_compar_d_fn_t)(void *__arg, void const *__a, void const *__b);
#endif /* !__dos_compar_d_fn_t_defined */
/* Dependency: "qsort_r" from "stdlib" */
#ifndef ____localdep_qsort_r_defined
#define ____localdep_qsort_r_defined 1
#ifdef __CRT_HAVE_qsort_r
__CREDIRECT_VOID(__ATTR_NONNULL((1, 4)),,__localdep_qsort_r,(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_d_fn_t __cmp, void *__arg),qsort_r,(__pbase,__item_count,__item_size,__cmp,__arg)) __THROWS(...)
#else /* LIBC: qsort_r */
#include <local/stdlib/qsort_r.h>
#define __localdep_qsort_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qsort_r))
#endif /* qsort_r... */
#endif /* !____localdep_qsort_r_defined */

__NAMESPACE_LOCAL_BEGIN
#ifndef ____invoke_compare_helper_s_defined
#define ____invoke_compare_helper_s_defined 1
struct __invoke_compare_helper_s_data {
	__dos_compar_d_fn_t __fun;
	void               *__arg;
};
__PRIVATE int (__LIBCCALL __invoke_compare_helper_s)(void const *__a, void const *__b, void *__arg) {
	return (*((struct __invoke_compare_helper_s_data *)__arg)->__fun)(((struct __invoke_compare_helper_s_data *)__arg)->__arg, __a, __b);
}
#endif /* !____invoke_compare_helper_defined */
__LOCAL_LIBC(qsort_s) __ATTR_NONNULL((1, 4)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(qsort_s))(void *__base,
                                                     __SIZE_TYPE__ __nmemb,
                                                     __SIZE_TYPE__ __size,
                                                     __dos_compar_d_fn_t __compar,
                                                     void *__arg) {
#line 2080 "kos/src/libc/magic/stdlib.c"
	struct __invoke_compare_helper_s_data __data;
	__data.__fun = __compar;
	__data.__arg = __arg;
	return __localdep_qsort_r(__base, __nmemb, __size, &__invoke_compare_helper_s, &__data);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_qsort_s_defined */
