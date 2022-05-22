/* HASH CRC-32:0x9ee66b82 */
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
#ifndef __local_tfind_defined
#define __local_tfind_defined
#include <__crt.h>
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_tfind_r_defined
#define __local___localdep_tfind_r_defined
#ifdef __CRT_HAVE_tfind_r
__CREDIRECT(__ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((3)),void *,__THROWING,__localdep_tfind_r,(void const *__key, void *const *__vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg),tfind_r,(__key,__vrootp,__compar,__arg))
#else /* __CRT_HAVE_tfind_r */
__NAMESPACE_LOCAL_END
#include <libc/local/search/tfind_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tfind_r __LIBC_LOCAL_NAME(tfind_r)
#endif /* !__CRT_HAVE_tfind_r */
#endif /* !__local___localdep_tfind_r_defined */
__NAMESPACE_LOCAL_END
#ifndef __LIBCCALL_CALLER_CLEANUP
#ifndef ____invoke_compare_helper_defined
__NAMESPACE_LOCAL_BEGIN
#define ____invoke_compare_helper_defined
__LOCAL_LIBC(__invoke_compare_helper) int
(__LIBCCALL __invoke_compare_helper)(void const *__a, void const *__b, void *__arg) {
	return (*(int (__LIBCCALL *)(void const *, void const *))__arg)(__a, __b);
}
__NAMESPACE_LOCAL_END
#endif /* !____invoke_compare_helper_defined */
#endif /* !__LIBCCALL_CALLER_CLEANUP */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(tfind) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((3)) void *
(__LIBCCALL __LIBC_LOCAL_NAME(tfind))(void const *__key, void *const *__vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) {
#ifdef __LIBCCALL_CALLER_CLEANUP
	return (__NAMESPACE_LOCAL_SYM __localdep_tfind_r)(__key, __vrootp, (int (__LIBCCALL *)(void const *, void const *, void *))(void *)__compar, __NULLPTR);
#else /* __LIBCCALL_CALLER_CLEANUP */
	return (__NAMESPACE_LOCAL_SYM __localdep_tfind_r)(__key, __vrootp, &__NAMESPACE_LOCAL_SYM __invoke_compare_helper, (void *)__compar);
#endif /* !__LIBCCALL_CALLER_CLEANUP */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tfind_defined
#define __local___localdep_tfind_defined
#define __localdep_tfind __LIBC_LOCAL_NAME(tfind)
#endif /* !__local___localdep_tfind_defined */
#endif /* !__local_tfind_defined */
