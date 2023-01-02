/* HASH CRC-32:0x4c92cb63 */
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
#ifndef __local_argz_add_sep_defined
#define __local_argz_add_sep_defined
#include <__crt.h>
#if defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <bits/types.h>
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
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),__libc_realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __local___localdep_realloc_defined
#endif /* !... */
#endif /* !__local___localdep_realloc_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(argz_add_sep) __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(argz_add_sep))(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char const *__restrict __string, int __sep) {
	char *__result_string, *__dst;
	__SIZE_TYPE__ __oldlen;
	__SIZE_TYPE__ __slen = (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__string);
	if __unlikely(!__slen)
		return 0;
	__oldlen = *__pargz_len;
	/* Note that Glibc actually has a bug here that causes it to write `NULL'
	 * into  the given  `*pargz' pointer  when the  allocation fails, instead
	 * of leaving that  pointer in  its original state  (allowing the  caller
	 * to cleanup  the argz-array,  instead of  forcing the  array to  become
	 * a memory leak)
	 * -> That bug is fixed here!
	 * Glibc's  version  of this:
	 * >> *argz = (char *) realloc (*argz, *argz_len + nlen); // <<< Right here!
	 * >> if (*argz == NULL)
	 * >>   return ENOMEM;
	 * As reference that the intended behavior in the ENOMEM-branch is an
	 * unmodified `*pargz' pointer (or at the very least, a  simultaneous
	 * setting of the `*pargz_len' pointer  to ZERO(0)), you may look  at
	 * Glibc's version  of `argz_append()',  which handles  that case  as
	 * leaving all pointers unmodified (just as one should)
	 */
	__result_string = (char *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(*__pargz, (__oldlen + (__slen + 1)) * sizeof(char));
	if __unlikely(!__result_string) {
#ifdef __ENOMEM
		return __ENOMEM;
#else /* __ENOMEM */
		return 1;
#endif /* !__ENOMEM */
	}
	*__pargz = __result_string;
	__dst    = __result_string + __oldlen;
	for (;;) {
		char __ch;
		__ch = *__string++;
__again_check_ch:
		if (!__ch)
			break;
		if (__ch != (char)(unsigned char)(unsigned int)__sep) {
			*__dst++ = __ch;
			continue;
		}
		/* Split the string. */
		*__dst++ = '\0';
		/* Skip consecutive `sep'-characters in `string' */
		do {
			__ch = *__string++;
		} while (__ch == (char)(unsigned char)(unsigned int)__sep);
		goto __again_check_ch;
	}
	if __unlikely(__dst == __result_string) {
		/* Empty string. (this can happen if `string' only consisted of `sep' characters) */
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__result_string);
		*__pargz     = __NULLPTR;
		*__pargz_len = 0;
		return 0;
	}
	/* Write the terminating NUL-byte (if there isn't one already) */
	if (__dst[-1] != '\0')
		*__dst++ = '\0';
	*__pargz_len = (__SIZE_TYPE__)(__dst - __result_string);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_argz_add_sep_defined
#define __local___localdep_argz_add_sep_defined
#define __localdep_argz_add_sep __LIBC_LOCAL_NAME(argz_add_sep)
#endif /* !__local___localdep_argz_add_sep_defined */
#else /* __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc */
#undef __local_argz_add_sep_defined
#endif /* !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc */
#endif /* !__local_argz_add_sep_defined */
