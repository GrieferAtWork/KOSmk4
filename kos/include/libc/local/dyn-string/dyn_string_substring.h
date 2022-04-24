/* HASH CRC-32:0xb44ab15b */
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
#ifndef __local_dyn_string_substring_defined
#define __local_dyn_string_substring_defined
#include <__crt.h>
#if defined(__CRT_HAVE_dyn_string_copy) || defined(__CRT_HAVE_dyn_string_resize) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xmalloc_failed)))
#include <features.h>
#include <bits/crt/dyn-string.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dyn_string_copy_defined
#define __local___localdep_dyn_string_copy_defined
#ifdef __CRT_HAVE_dyn_string_copy
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_dyn_string_copy,(struct dyn_string *__dst, struct dyn_string __KOS_FIXED_CONST *__src),dyn_string_copy,(__dst,__src))
#elif defined(__CRT_HAVE_dyn_string_resize) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xmalloc_failed)))
__NAMESPACE_LOCAL_END
#include <libc/local/dyn-string/dyn_string_copy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dyn_string_copy __LIBC_LOCAL_NAME(dyn_string_copy)
#else /* ... */
#undef __local___localdep_dyn_string_copy_defined
#endif /* !... */
#endif /* !__local___localdep_dyn_string_copy_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/__assert.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(dyn_string_substring) __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(dyn_string_substring))(struct dyn_string *__dst, struct dyn_string __KOS_FIXED_CONST *__src, __STDC_INT_AS_SIZE_T __start, __STDC_INT_AS_SIZE_T __end) {
	struct dyn_string __fakesrc;
	__hybrid_assert((__SIZE_TYPE__)__start <= (__SIZE_TYPE__)__end);
	__hybrid_assert((__SIZE_TYPE__)__end <= (__SIZE_TYPE__)__src->length);
	__fakesrc.s      = __src->s + (__SIZE_TYPE__)__start;
	__fakesrc.length = (__STDC_INT_AS_SIZE_T)((__SIZE_TYPE__)__end - (__SIZE_TYPE__)__start);
	return (__NAMESPACE_LOCAL_SYM __localdep_dyn_string_copy)(__dst, &__fakesrc);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_dyn_string_substring_defined
#define __local___localdep_dyn_string_substring_defined
#define __localdep_dyn_string_substring __LIBC_LOCAL_NAME(dyn_string_substring)
#endif /* !__local___localdep_dyn_string_substring_defined */
#else /* __CRT_HAVE_dyn_string_copy || __CRT_HAVE_dyn_string_resize || ((__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_xrealloc || __CRT_HAVE_xmalloc_failed)) */
#undef __local_dyn_string_substring_defined
#endif /* !__CRT_HAVE_dyn_string_copy && !__CRT_HAVE_dyn_string_resize && ((!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_xrealloc && !__CRT_HAVE_xmalloc_failed)) */
#endif /* !__local_dyn_string_substring_defined */
