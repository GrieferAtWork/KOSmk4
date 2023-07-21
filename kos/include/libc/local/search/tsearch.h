/* HASH CRC-32:0x2a6c493a */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_tsearch_defined
#define __local_tsearch_defined
#include <__crt.h>
#if defined(__CRT_HAVE_tsearch_r) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_tsearch_r_defined
#define __local___localdep_tsearch_r_defined
#ifdef __CRT_HAVE_tsearch_r
__CREDIRECT(__ATTR_INOUT_OPT(2) __ATTR_IN_OPT(1) __ATTR_NONNULL((3)),void *,__NOTHROW_CB_NCX,__localdep_tsearch_r,(void const *__key, void **__vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg),tsearch_r,(__key,__vrootp,__compar,__arg))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/search/tsearch_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tsearch_r __LIBC_LOCAL_NAME(tsearch_r)
#else /* ... */
#undef __local___localdep_tsearch_r_defined
#endif /* !... */
#endif /* !__local___localdep_tsearch_r_defined */
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
__LOCAL_LIBC(tsearch) __ATTR_INOUT_OPT(2) __ATTR_IN_OPT(1) __ATTR_NONNULL((3)) void *
__NOTHROW_CB_NCX(__LIBCCALL __LIBC_LOCAL_NAME(tsearch))(void const *__key, void **__vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) {
#ifdef __LIBCCALL_CALLER_CLEANUP
	return (__NAMESPACE_LOCAL_SYM __localdep_tsearch_r)(__key, __vrootp, (int (__LIBCCALL *)(void const *, void const *, void *))(void *)__compar, __NULLPTR);
#else /* __LIBCCALL_CALLER_CLEANUP */
	return (__NAMESPACE_LOCAL_SYM __localdep_tsearch_r)(__key, __vrootp, &__NAMESPACE_LOCAL_SYM __invoke_compare_helper, (void *)__compar);
#endif /* !__LIBCCALL_CALLER_CLEANUP */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tsearch_defined
#define __local___localdep_tsearch_defined
#define __localdep_tsearch __LIBC_LOCAL_NAME(tsearch)
#endif /* !__local___localdep_tsearch_defined */
#else /* __CRT_HAVE_tsearch_r || __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
#undef __local_tsearch_defined
#endif /* !__CRT_HAVE_tsearch_r && !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign */
#endif /* !__local_tsearch_defined */
