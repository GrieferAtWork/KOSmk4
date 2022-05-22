/* HASH CRC-32:0xb514ec11 */
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
#ifndef __local_choose_tmpdir_defined
#define __local_choose_tmpdir_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_access) || defined(__CRT_HAVE__access) || defined(__CRT_HAVE___access) || defined(__CRT_HAVE___libc_access) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_faccessat))) && (defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))) && !defined(_WIN32) && defined(__X_OK) && defined(__W_OK) && defined(__R_OK)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_access_defined
#define __local___localdep_access_defined
#ifdef __CRT_HAVE_access
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,__localdep_access,(char const *__file, __STDC_INT_AS_UINT_T __type),access,(__file,__type))
#elif defined(__CRT_HAVE__access)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,__localdep_access,(char const *__file, __STDC_INT_AS_UINT_T __type),_access,(__file,__type))
#elif defined(__CRT_HAVE___access)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,__localdep_access,(char const *__file, __STDC_INT_AS_UINT_T __type),__access,(__file,__type))
#elif defined(__CRT_HAVE___libc_access)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,__localdep_access,(char const *__file, __STDC_INT_AS_UINT_T __type),__libc_access,(__file,__type))
#elif defined(__AT_FDCWD) && defined(__CRT_HAVE_faccessat)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/access.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_access __LIBC_LOCAL_NAME(access)
#else /* ... */
#undef __local___localdep_access_defined
#endif /* !... */
#endif /* !__local___localdep_access_defined */
#ifndef __local___localdep_getenv_defined
#define __local___localdep_getenv_defined
#ifdef __CRT_HAVE_getenv
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_getenv,(char const *__varname),getenv,(__varname))
#else /* __CRT_HAVE_getenv */
__NAMESPACE_LOCAL_END
#include <libc/template/environ.h>
__NAMESPACE_LOCAL_BEGIN
#ifdef __LOCAL_environ
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/getenv.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getenv __LIBC_LOCAL_NAME(getenv)
#else /* __LOCAL_environ */
#undef __local___localdep_getenv_defined
#endif /* !__LOCAL_environ */
#endif /* !__CRT_HAVE_getenv */
#endif /* !__local___localdep_getenv_defined */
#ifndef __local___localdep_mempcpyc_defined
#define __local___localdep_mempcpyc_defined
#ifdef __CRT_HAVE_mempcpyc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,__localdep_mempcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_mempcpyc */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempcpyc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempcpyc __LIBC_LOCAL_NAME(mempcpyc)
#endif /* !__CRT_HAVE_mempcpyc */
#endif /* !__local___localdep_mempcpyc_defined */
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
#ifndef __local___localdep_xmalloc_defined
#define __local___localdep_xmalloc_defined
#ifdef __CRT_HAVE_xmalloc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_xmalloc,(__SIZE_TYPE__ __num_bytes),xmalloc,(__num_bytes))
#elif defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
__NAMESPACE_LOCAL_END
#include <libc/local/libiberty/xmalloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_xmalloc __LIBC_LOCAL_NAME(xmalloc)
#else /* ... */
#undef __local___localdep_xmalloc_defined
#endif /* !... */
#endif /* !__local___localdep_xmalloc_defined */
__LOCAL_LIBC(choose_tmpdir) __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED char const *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(choose_tmpdir))(void) {
	static char const *__result = __NULLPTR;
	if (__result == __NULLPTR) {
		char const *__path;
		__SIZE_TYPE__ __pathlen;
		char *__pathcopy, *__ptr;
		__SIZE_TYPE__ __i;
#ifdef __KOS__
		static char const __defdir_names[][10] = { "/tmp", "/var/tmp", "/usr/tmp" };
#else /* __KOS__ */
		static char const __defdir_names[][10] = { "/var/tmp", "/usr/tmp", "/tmp" };
#endif /* !__KOS__ */
#if defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)
		static char const __envvar_names[][8] = { "TMPDIR", "TMP", "TEMP" };
		for (__i = 0; __i < __COMPILER_LENOF(__envvar_names); ++__i) {
			__path = (__NAMESPACE_LOCAL_SYM __localdep_getenv)(__envvar_names[__i]);
			if (__path && (__NAMESPACE_LOCAL_SYM __localdep_access)(__path, __X_OK | __W_OK | __R_OK) == 0)
				goto __got_tmppath;
		}
#endif /* __CRT_HAVE_getenv || __LOCAL_environ */
		for (__i = 0; __i < __COMPILER_LENOF(__defdir_names); ++__i) {
			__path = __defdir_names[__i];
			if ((__NAMESPACE_LOCAL_SYM __localdep_access)(__path, __X_OK | __W_OK | __R_OK) == 0)
				goto __got_tmppath;
		}

		/* Fallback: use the current directory. */
		__path = ".";
__got_tmppath:

		__pathlen = (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__path);




		while (__pathlen && __path[__pathlen - 1] == '/')
			--__pathlen;


		/* Force-append a trailing slash. */
		__pathcopy = (char *)(__NAMESPACE_LOCAL_SYM __localdep_xmalloc)((__pathlen + 2) * sizeof(char));
		__ptr = (char *)(__NAMESPACE_LOCAL_SYM __localdep_mempcpyc)(__pathcopy, __path, __pathlen, sizeof(char));



		*__ptr++ = '/';

		*__ptr++ = '\0';
		__result = __pathcopy;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_choose_tmpdir_defined
#define __local___localdep_choose_tmpdir_defined
#define __localdep_choose_tmpdir __LIBC_LOCAL_NAME(choose_tmpdir)
#endif /* !__local___localdep_choose_tmpdir_defined */
#else /* (__CRT_HAVE_access || __CRT_HAVE__access || __CRT_HAVE___access || __CRT_HAVE___libc_access || (__AT_FDCWD && __CRT_HAVE_faccessat)) && (__CRT_HAVE_xmalloc || __CRT_HAVE_xrealloc || __CRT_HAVE_xcalloc || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && __CRT_HAVE_xmalloc_failed)) && !_WIN32 && __X_OK && __W_OK && __R_OK */
#undef __local_choose_tmpdir_defined
#endif /* (!__CRT_HAVE_access && !__CRT_HAVE__access && !__CRT_HAVE___access && !__CRT_HAVE___libc_access && (!__AT_FDCWD || !__CRT_HAVE_faccessat)) || (!__CRT_HAVE_xmalloc && !__CRT_HAVE_xrealloc && !__CRT_HAVE_xcalloc && ((!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || !__CRT_HAVE_xmalloc_failed)) || _WIN32 || !__X_OK || !__W_OK || !__R_OK */
#endif /* !__local_choose_tmpdir_defined */
