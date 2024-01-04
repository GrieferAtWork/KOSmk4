/* HASH CRC-32:0x24db9e5c */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_bsearch_s_defined
#define __local_bsearch_s_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_bsearch_r_defined
#define __local___localdep_bsearch_r_defined
#ifdef __CRT_HAVE_bsearch_r
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void *,__NOTHROW_CB_NCX,__localdep_bsearch_r,(void const *__pkey, void const *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg),bsearch_r,(__pkey,__pbase,__item_count,__item_size,__compar,__arg))
#else /* __CRT_HAVE_bsearch_r */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/bsearch_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bsearch_r __LIBC_LOCAL_NAME(bsearch_r)
#endif /* !__CRT_HAVE_bsearch_r */
#endif /* !__local___localdep_bsearch_r_defined */
__NAMESPACE_LOCAL_END
#ifndef ____invoke_compare_helper_s_defined
#define ____invoke_compare_helper_s_defined
__NAMESPACE_LOCAL_BEGIN
struct __invoke_compare_helper_s_data {
	int (__LIBCCALL *__fun)(void *__arg, void const *__a, void const *__b);
	void            *__arg;
};
__LOCAL_LIBC(__invoke_compare_helper_s) int
(__LIBCCALL __invoke_compare_helper_s)(void const *__a, void const *__b, void *__arg) {
	void *__base_arg = ((struct __invoke_compare_helper_s_data *)__arg)->__arg;
	return (*((struct __invoke_compare_helper_s_data *)__arg)->__fun)(__base_arg, __a, __b);
}
__NAMESPACE_LOCAL_END
#endif /* !____invoke_compare_helper_s_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(bsearch_s) __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)) void *
__NOTHROW_CB_NCX(__LIBCCALL __LIBC_LOCAL_NAME(bsearch_s))(void const *__key, void const *__base, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, int (__LIBCCALL *__compar)(void *__arg, void const *__a, void const *__b), void *__arg) {
	struct __NAMESPACE_LOCAL_SYM __invoke_compare_helper_s_data __data;
	__data.__fun = __compar;
	__data.__arg = __arg;
	return (void *)(__NAMESPACE_LOCAL_SYM __localdep_bsearch_r)(__key, __base, __elem_count, __elem_size,
	                         &__NAMESPACE_LOCAL_SYM __invoke_compare_helper_s,
	                         &__data);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_bsearch_s_defined
#define __local___localdep_bsearch_s_defined
#define __localdep_bsearch_s __LIBC_LOCAL_NAME(bsearch_s)
#endif /* !__local___localdep_bsearch_s_defined */
#endif /* !__local_bsearch_s_defined */
