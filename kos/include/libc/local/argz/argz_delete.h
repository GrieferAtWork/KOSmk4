/* HASH CRC-32:0xfb26801d */
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
#ifndef __local_argz_delete_defined
#define __local_argz_delete_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#ifndef __local___localdep_memmovedownc_defined
#define __local___localdep_memmovedownc_defined
#ifdef __CRT_HAVE_memmovedownc
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,__localdep_memmovedownc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmovedownc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memmovedownc */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memmovedownc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memmovedownc __LIBC_LOCAL_NAME(memmovedownc)
#endif /* !__CRT_HAVE_memmovedownc */
#endif /* !__local___localdep_memmovedownc_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__LOCAL_LIBC(argz_delete) __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_IN_OPT(3) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(argz_delete))(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char *__entry) {
	__SIZE_TYPE__ __entrylen, __newlen;
	if __unlikely(!__entry)
		return;
	__entrylen  = (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__entry) + 1;
	__newlen    = *__pargz_len - __entrylen;
	*__pargz_len = __newlen;
	if __unlikely(__newlen == 0) {
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
		(__NAMESPACE_LOCAL_SYM __localdep_free)(*__pargz);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
		*__pargz = __NULLPTR;
		return;
	}
	(__NAMESPACE_LOCAL_SYM __localdep_memmovedownc)(__entry, __entry + __entrylen,
	             (__newlen - (__SIZE_TYPE__)(__entry - *__pargz)),
	             sizeof(char));
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_argz_delete_defined
#define __local___localdep_argz_delete_defined
#define __localdep_argz_delete __LIBC_LOCAL_NAME(argz_delete)
#endif /* !__local___localdep_argz_delete_defined */
#endif /* !__local_argz_delete_defined */
