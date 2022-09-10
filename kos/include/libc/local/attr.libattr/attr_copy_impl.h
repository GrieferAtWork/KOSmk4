/* HASH CRC-32:0x390addff */
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
#ifndef __local_attr_copy_impl_defined
#define __local_attr_copy_impl_defined
#include <__crt.h>
#include <parts/malloca.h>
#if !defined(__NO_MALLOCA) && defined(__CRT_HAVE_llistxattr) && defined(__CRT_HAVE_flistxattr) && defined(__CRT_HAVE_lgetxattr) && defined(__CRT_HAVE_fgetxattr) && defined(__CRT_HAVE_lsetxattr) && defined(__CRT_HAVE_fsetxattr) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <attr/error_context.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_attr_copy_check_permissions_defined
#define __local___localdep_attr_copy_check_permissions_defined
#ifdef __CRT_HAVE_attr_copy_check_permissions
__CREDIRECT(__ATTR_IN(1) __ATTR_INOUT_OPT(2),int,__NOTHROW_NCX,__localdep_attr_copy_check_permissions,(char const *__attr_name, struct error_context *__ctx),attr_copy_check_permissions,(__attr_name,__ctx))
#else /* __CRT_HAVE_attr_copy_check_permissions */
__NAMESPACE_LOCAL_END
#include <libc/local/attr.libattr/attr_copy_check_permissions.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_attr_copy_check_permissions __LIBC_LOCAL_NAME(attr_copy_check_permissions)
#endif /* !__CRT_HAVE_attr_copy_check_permissions */
#endif /* !__local___localdep_attr_copy_check_permissions_defined */
#ifndef __local___localdep_fgetxattr_defined
#define __local___localdep_fgetxattr_defined
__CREDIRECT(__ATTR_IN(2) __ATTR_OUTS(3, 4),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_fgetxattr,(__fd_t __fd, char const *__name, void *__buf, __SIZE_TYPE__ __bufsize),fgetxattr,(__fd,__name,__buf,__bufsize))
#endif /* !__local___localdep_fgetxattr_defined */
#ifndef __local___localdep_flistxattr_defined
#define __local___localdep_flistxattr_defined
__CREDIRECT(__ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_flistxattr,(__fd_t __fd, char *__listbuf, __SIZE_TYPE__ __listbufsize),flistxattr,(__fd,__listbuf,__listbufsize))
#endif /* !__local___localdep_flistxattr_defined */
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
#ifndef __local___localdep_fsetxattr_defined
#define __local___localdep_fsetxattr_defined
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2) __ATTR_INS(3, 4),int,__NOTHROW_RPC,__localdep_fsetxattr,(__fd_t __fd, char const *__name, void const *__buf, __SIZE_TYPE__ __bufsize, __STDC_INT_AS_UINT_T __flags),fsetxattr,(__fd,__name,__buf,__bufsize,__flags))
#endif /* !__local___localdep_fsetxattr_defined */
#ifndef __local___localdep_lgetxattr_defined
#define __local___localdep_lgetxattr_defined
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_OUTS(3, 4),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_lgetxattr,(char const *__path, char const *__name, void *__buf, __SIZE_TYPE__ __bufsize),lgetxattr,(__path,__name,__buf,__bufsize))
#endif /* !__local___localdep_lgetxattr_defined */
#ifndef __local___localdep_llistxattr_defined
#define __local___localdep_llistxattr_defined
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_llistxattr,(char const *__path, char *__listbuf, __SIZE_TYPE__ __listbufsize),llistxattr,(__path,__listbuf,__listbufsize))
#endif /* !__local___localdep_llistxattr_defined */
#ifndef __local___localdep_lsetxattr_defined
#define __local___localdep_lsetxattr_defined
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_INS(3, 4),int,__NOTHROW_RPC,__localdep_lsetxattr,(char const *__path, char const *__name, void const *__buf, __SIZE_TYPE__ __bufsize, __STDC_INT_AS_UINT_T __flags),lsetxattr,(__path,__name,__buf,__bufsize,__flags))
#endif /* !__local___localdep_lsetxattr_defined */
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined
#if __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,(__num_bytes))
#elif defined(__CRT_HAVE___libc_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),__libc_malloc,(__num_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/malloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_malloc __LIBC_LOCAL_NAME(malloc)
#endif /* !... */
#endif /* !__local___localdep_malloc_defined */
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
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined
#ifdef __CRT_HAVE_strend
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __str),strend,(__str))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
#include <bits/crt/inttypes.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(attr_copy_impl) __ATTR_INOUT_OPT(6) __ATTR_IN_OPT(1) __ATTR_IN_OPT(3) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(attr_copy_impl))(char const *__src_path, __fd_t __src_fd, char const *__dst_path, __fd_t __dst_fd, int (__LIBKCALL *__check)(char const *__attr_name, struct error_context *__ctx), struct error_context *__ctx) {
	int __result = 0;
	__SSIZE_TYPE__ __nameslen, __nameslen2;
	char *__namesbuf, *__iter, *__end;
	void *__valbuf = __NULLPTR;
	__SIZE_TYPE__ __valbuflen = 0;
	if (__check == __NULLPTR)
		__check = &(__NAMESPACE_LOCAL_SYM __localdep_attr_copy_check_permissions);

	/* Ask kernel know much space we need for names */
	__nameslen = __src_fd != -1 ? (__NAMESPACE_LOCAL_SYM __localdep_flistxattr)(__src_fd, __NULLPTR, 0)
	                        : (__NAMESPACE_LOCAL_SYM __localdep_llistxattr)(__src_path, __NULLPTR, 0);
	if __unlikely(__nameslen == -1) {
__err_listxattr_failed:
		/* Special handling for ENOSYS, ENOTSUP and EOPNOTSUPP
		 * - ENOSYS indicates that the kernel doesn't support extended attributes
		 * - ENOTSUP and EOPNOTSUPP  indicate that `src_path'  / `src_fd'  don't
		 *   support extended attributes (which we must treat the same as though
		 *   the source file didn't have any attributes at all) */
#ifdef __libc_geterrno
#if defined(__ENOSYS) && (defined(__ENOTSUP) || defined(__EOPNOTSUPP))
		{
			__errno_t __err = __libc_geterrno();
			if (__err == __ENOSYS)
				return 0;
#ifdef __ENOTSUP
			if (__err == __ENOTSUP)
				return 0;
#endif /* __ENOTSUP */
#if defined(__EOPNOTSUPP) && (!defined(__ENOTSUP) || __EOPNOTSUPP != __ENOTSUP)
			if (__err == __EOPNOTSUPP)
				return 0;
#endif /* __EOPNOTSUPP && (!__ENOTSUP || __EOPNOTSUPP != __ENOTSUP) */
		}
#elif defined(__ENOSYS)
		if (__libc_geterrno() == __ENOSYS)
			return 0;
#elif defined(__ENOTSUP) && defined(__EOPNOTSUPP) && __ENOTSUP != __EOPNOTSUPP
		{
			__errno_t __err = __libc_geterrno();
			if (__err == __ENOTSUP || __err == __EOPNOTSUPP)
				return 0;
		}
#elif defined(__ENOTSUP)
		if (__libc_geterrno() == __ENOTSUP)
			return 0;
#elif defined(__EOPNOTSUPP)
		if (__libc_geterrno() == __EOPNOTSUPP)
			return 0;
#endif /* ... */
#endif /* __libc_geterrno */
		{
			char const *__src_path_q = __attr_quote(__ctx, __src_path);
			__attr_error(__ctx, "%s: cannot list attributes: %m", __src_path_q);
			__attr_quote_free(__ctx, __src_path_q);
		}
		return -1;
	}

__malloc_again:
	__namesbuf = (char *)__malloca(((__SIZE_TYPE__)__nameslen + 1) * sizeof(char));
#ifdef __malloca_mayfail
	if __unlikely(!__namesbuf)
		return -1;
#endif /* __malloca_mayfail */

	/* Load names form kernel-space */
	__nameslen2 = __src_fd != -1 ? (__NAMESPACE_LOCAL_SYM __localdep_flistxattr)(__src_fd, __namesbuf, (__SIZE_TYPE__)__nameslen)
	                         : (__NAMESPACE_LOCAL_SYM __localdep_llistxattr)(__src_path, __namesbuf, (__SIZE_TYPE__)__nameslen);
	if __unlikely(__nameslen2 == -1) {
		__freea(__namesbuf);
		goto __err_listxattr_failed;
	}
	if __unlikely((__SIZE_TYPE__)__nameslen2 > (__SIZE_TYPE__)__nameslen) {
		__freea(__namesbuf);
		goto __malloc_again;
	}

	/* Ensure that the names-buffer is NUL terminated */
	__namesbuf[(__SIZE_TYPE__)__nameslen2] = '\0';
	__end = __namesbuf + __nameslen2;

	/* Allocate an initial buffer */
	if (__nameslen2) {

		__valbuf = (__NAMESPACE_LOCAL_SYM __localdep_malloc)(512);



		if __likely(__valbuf)
			__valbuflen = 512;
	}

	/* Enumerate attribute names */
	for (__iter = __namesbuf; __iter < __end; __iter = (__NAMESPACE_LOCAL_SYM __localdep_strend)(__iter) + 1) {
		__SSIZE_TYPE__ __attrlen;
		int __seterr;
		if __unlikely(!*__iter)
			continue; /* Skip empty names (shouldn't happen) */
		if (!(*__check)(__iter, __ctx))
			continue; /* Skip attributes which our caller doesn't want us to copy. */

		/* Ask the kernel for the attribute's value */
__again_read_attr:
		__attrlen = __src_fd != -1 ? (__NAMESPACE_LOCAL_SYM __localdep_fgetxattr)(__src_fd, __iter, __valbuf, __valbuflen)
		                       : (__NAMESPACE_LOCAL_SYM __localdep_lgetxattr)(__src_path, __iter, __valbuf, __valbuflen);
		if (__attrlen == -1) {
			char const *__src_path_q = __attr_quote(__ctx, __src_path);
			char const *__iter_q     = __attr_quote(__ctx, __iter);
			__attr_error(__ctx, "%s: failed to get attribute %s: %m", __src_path_q, __iter_q);
			__attr_quote_free(__ctx, __iter_q);
			__attr_quote_free(__ctx, __src_path_q);
			__result = -1;
			continue;
		}

		/* Handle case where our buffer is too small. */
		if ((__SIZE_TYPE__)__attrlen > __valbuflen) {
			void *__new_valbuf;
			__new_valbuf = (__NAMESPACE_LOCAL_SYM __localdep_realloc)(__valbuf, (__SIZE_TYPE__)__attrlen);
			if __unlikely(!__new_valbuf) {
				char const *__src_path_q = __attr_quote(__ctx, __src_path);
				char const *__iter_q     = __attr_quote(__ctx, __iter);
				__attr_error(__ctx, "%s: failed to allocate %" __PRIN_PREFIX(__SIZEOF_SIZE_T__) "u "
				                  "bytes for attribute %s: %m",
				             __src_path_q, (__SIZE_TYPE__)__attrlen, __iter_q);
				__attr_quote_free(__ctx, __iter_q);
				__attr_quote_free(__ctx, __src_path_q);
				__result = -1;
				continue;
			}
			__valbuf    = __new_valbuf;
			__valbuflen = (__SIZE_TYPE__)__attrlen;
			goto __again_read_attr;
		}

		__seterr = __dst_fd != -1 ? (__NAMESPACE_LOCAL_SYM __localdep_fsetxattr)(__dst_fd, __iter, __valbuf, __valbuflen, 0)
		                      : (__NAMESPACE_LOCAL_SYM __localdep_lsetxattr)(__dst_path, __iter, __valbuf, __valbuflen, 0);
		if __unlikely(__seterr != 0) {
			char const *__dst_path_q = __attr_quote(__ctx, __dst_path);
			char const *__iter_q     = __attr_quote(__ctx, __iter);
			__attr_error(__ctx, "%s: failed to set attribute %s: %m", __dst_path_q, __iter_q);
			__attr_quote_free(__ctx, __iter_q);
			__attr_quote_free(__ctx, __dst_path_q);
			__result = -1;
		}
	}

#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__valbuf);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	__freea(__namesbuf);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_attr_copy_impl_defined
#define __local___localdep_attr_copy_impl_defined
#define __localdep_attr_copy_impl __LIBC_LOCAL_NAME(attr_copy_impl)
#endif /* !__local___localdep_attr_copy_impl_defined */
#else /* !__NO_MALLOCA && __CRT_HAVE_llistxattr && __CRT_HAVE_flistxattr && __CRT_HAVE_lgetxattr && __CRT_HAVE_fgetxattr && __CRT_HAVE_lsetxattr && __CRT_HAVE_fsetxattr && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#undef __local_attr_copy_impl_defined
#endif /* __NO_MALLOCA || !__CRT_HAVE_llistxattr || !__CRT_HAVE_flistxattr || !__CRT_HAVE_lgetxattr || !__CRT_HAVE_fgetxattr || !__CRT_HAVE_lsetxattr || !__CRT_HAVE_fsetxattr || (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
#endif /* !__local_attr_copy_impl_defined */
