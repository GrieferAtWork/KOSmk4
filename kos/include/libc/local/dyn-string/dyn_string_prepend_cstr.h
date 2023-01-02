/* HASH CRC-32:0x7394591a */
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
#ifndef __local_dyn_string_prepend_cstr_defined
#define __local_dyn_string_prepend_cstr_defined
#include <__crt.h>
#if defined(__CRT_HAVE_dyn_string_insert_cstr) || defined(__CRT_HAVE_dyn_string_insert) || defined(__CRT_HAVE_dyn_string_resize) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xmalloc_failed)))
#include <bits/crt/dyn-string.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dyn_string_insert_cstr_defined
#define __local___localdep_dyn_string_insert_cstr_defined
#ifdef __CRT_HAVE_dyn_string_insert_cstr
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(3) __ATTR_INOUT(1),int,__NOTHROW_NCX,__localdep_dyn_string_insert_cstr,(struct dyn_string *__dst, __STDC_INT_AS_SIZE_T __index, char const *__src),dyn_string_insert_cstr,(__dst,__index,__src))
#elif defined(__CRT_HAVE_dyn_string_insert) || defined(__CRT_HAVE_dyn_string_resize) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xmalloc_failed)))
__NAMESPACE_LOCAL_END
#include <libc/local/dyn-string/dyn_string_insert_cstr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dyn_string_insert_cstr __LIBC_LOCAL_NAME(dyn_string_insert_cstr)
#else /* ... */
#undef __local___localdep_dyn_string_insert_cstr_defined
#endif /* !... */
#endif /* !__local___localdep_dyn_string_insert_cstr_defined */
__LOCAL_LIBC(dyn_string_prepend_cstr) __ATTR_IN(2) __ATTR_INOUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(dyn_string_prepend_cstr))(struct dyn_string *__dst, char const *__src) {
	return (__NAMESPACE_LOCAL_SYM __localdep_dyn_string_insert_cstr)(__dst, 0, __src);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_dyn_string_prepend_cstr_defined
#define __local___localdep_dyn_string_prepend_cstr_defined
#define __localdep_dyn_string_prepend_cstr __LIBC_LOCAL_NAME(dyn_string_prepend_cstr)
#endif /* !__local___localdep_dyn_string_prepend_cstr_defined */
#else /* __CRT_HAVE_dyn_string_insert_cstr || __CRT_HAVE_dyn_string_insert || __CRT_HAVE_dyn_string_resize || ((__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_xrealloc || __CRT_HAVE_xmalloc_failed)) */
#undef __local_dyn_string_prepend_cstr_defined
#endif /* !__CRT_HAVE_dyn_string_insert_cstr && !__CRT_HAVE_dyn_string_insert && !__CRT_HAVE_dyn_string_resize && ((!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_xrealloc && !__CRT_HAVE_xmalloc_failed)) */
#endif /* !__local_dyn_string_prepend_cstr_defined */
