/* HASH CRC-32:0xeec42276 */
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
#ifndef __local_expandargv_defined
#define __local_expandargv_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <features.h>
#if (defined(__CRT_HAVE_mapfile) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_fmapfileat) || (defined(__O_RDONLY) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_fmapfile) || ((defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))))) || (defined(__O_RDONLY) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fmapfile) || ((defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))) && (defined(__CRT_HAVE_xrealloc) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && defined(__CRT_HAVE_xmalloc_failed))) && (defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_buildargv_defined
#define __local___localdep_buildargv_defined
#ifdef __CRT_HAVE_buildargv
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN_OPT(1),char **,__NOTHROW_NCX,__localdep_buildargv,(char const *__cmdline),buildargv,(__cmdline))
#else /* __CRT_HAVE_buildargv */
__NAMESPACE_LOCAL_END
#include <libc/local/libiberty/buildargv.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_buildargv __LIBC_LOCAL_NAME(buildargv)
#endif /* !__CRT_HAVE_buildargv */
#endif /* !__local___localdep_buildargv_defined */
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
#ifndef __local___localdep_mapfile_defined
#define __local___localdep_mapfile_defined
#ifdef __CRT_HAVE_mapfile
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <bits/crt/mapfile.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_mapfile,(struct mapfile *__restrict __mapping, char const *__filename, __pos64_t __offset, __SIZE_TYPE__ __min_bytes, __SIZE_TYPE__ __max_bytes, __SIZE_TYPE__ __num_trailing_nulbytes, unsigned int __flags),mapfile,(__mapping,__filename,__offset,__min_bytes,__max_bytes,__num_trailing_nulbytes,__flags))
#elif (defined(__AT_FDCWD) && (defined(__CRT_HAVE_fmapfileat) || (defined(__O_RDONLY) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_fmapfile) || ((defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))))) || (defined(__O_RDONLY) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fmapfile) || ((defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))
__NAMESPACE_LOCAL_END
#include <libc/local/sys.mman/mapfile.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mapfile __LIBC_LOCAL_NAME(mapfile)
#else /* ... */
#undef __local___localdep_mapfile_defined
#endif /* !... */
#endif /* !__local___localdep_mapfile_defined */
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined
#ifdef __CRT_HAVE_memcpy
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
#ifndef __local___localdep_memcpyc_defined
#define __local___localdep_memcpyc_defined
#ifdef __CRT_HAVE_memcpyc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,__localdep_memcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memcpyc */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpyc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpyc __LIBC_LOCAL_NAME(memcpyc)
#endif /* !__CRT_HAVE_memcpyc */
#endif /* !__local___localdep_memcpyc_defined */
#ifndef __local___localdep_memmoveupc_defined
#define __local___localdep_memmoveupc_defined
#ifdef __CRT_HAVE_memmoveupc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,__localdep_memmoveupc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmoveupc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memmoveupc */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memmoveupc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memmoveupc __LIBC_LOCAL_NAME(memmoveupc)
#endif /* !__CRT_HAVE_memmoveupc */
#endif /* !__local___localdep_memmoveupc_defined */
#ifndef __local___localdep_unmapfile_defined
#define __local___localdep_unmapfile_defined
#ifdef __CRT_HAVE_unmapfile
__NAMESPACE_LOCAL_END
#include <bits/crt/mapfile.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,__localdep_unmapfile,(struct mapfile *__restrict __mapping),unmapfile,(__mapping))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.mman/unmapfile.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unmapfile __LIBC_LOCAL_NAME(unmapfile)
#else /* ... */
#undef __local___localdep_unmapfile_defined
#endif /* !... */
#endif /* !__local___localdep_unmapfile_defined */
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
#if !defined(__local___localdep_xmalloc_failed_defined) && defined(__CRT_HAVE_xmalloc_failed)
#define __local___localdep_xmalloc_failed_defined
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep_xmalloc_failed,(__SIZE_TYPE__ __num_bytes),xmalloc_failed,(__num_bytes))
#endif /* !__local___localdep_xmalloc_failed_defined && __CRT_HAVE_xmalloc_failed */
#ifndef __local___localdep_xrealloc_defined
#define __local___localdep_xrealloc_defined
#ifdef __CRT_HAVE_xrealloc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_xrealloc,(void *__ptr, __SIZE_TYPE__ __num_bytes),xrealloc,(__ptr,__num_bytes))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && defined(__CRT_HAVE_xmalloc_failed)
__NAMESPACE_LOCAL_END
#include <libc/local/libiberty/xrealloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_xrealloc __LIBC_LOCAL_NAME(xrealloc)
#else /* ... */
#undef __local___localdep_xrealloc_defined
#endif /* !... */
#endif /* !__local___localdep_xrealloc_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
#include <hybrid/__assert.h>
#include <bits/crt/mapfile.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(expandargv) __ATTR_INOUT(1) __ATTR_INOUT(2) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(expandargv))(int *__p_argc, char ***__p_argv) {
	__SIZE_TYPE__ __i, ___argc = (__SIZE_TYPE__)*__p_argc;
	char **___argv = *__p_argv;
	for (__i = 0; __i < ___argc; ++__i) {
		struct mapfile __mf;
		char *__arg = ___argv[__i];
		char **__inject_argv;
		__SIZE_TYPE__ __inject_argc;
		if (__arg[0] != '@')
			continue;
		++__arg;

		/* Map  the specified file  into memory. -  If doing so fails,
		 * (due to something other than out-of-memory), then we simply
		 * ignore the @-directive. */
		if ((__NAMESPACE_LOCAL_SYM __localdep_mapfile)(&__mf, __arg, 0, 0, (__SIZE_TYPE__)-1, 1, 0) != 0) {
#if defined(__libc_geterrno) && defined(__CRT_HAVE_xmalloc_failed)
			if (__libc_geterrno() == __ENOMEM)
				(__NAMESPACE_LOCAL_SYM __localdep_xmalloc_failed)(1);
#endif /* __libc_geterrno && __CRT_HAVE_xmalloc_failed */
			continue;
		}

		/* Build an argument vector from the file.
		 * Note the forced trailing NUL-byte we requested for the mapping! */
		__inject_argv = (__NAMESPACE_LOCAL_SYM __localdep_buildargv)((char *)__mf.mf_addr);
#if defined(__CRT_HAVE_unmapfile) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
		(__NAMESPACE_LOCAL_SYM __localdep_unmapfile)(&__mf);
#endif /* __CRT_HAVE_unmapfile || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */

		/* Count the # of injected arguments. */
		__hybrid_assert(__inject_argv);
		for (__inject_argc = 0; __inject_argv[__inject_argc]; ++__inject_argc)
			;

		/* Resize the argument vector. */
		if (___argv == *__p_argv) {
			__SIZE_TYPE__ __size;
			__size = (___argc + __inject_argc + 1) * sizeof(char *);
			___argv = (char **)(__NAMESPACE_LOCAL_SYM __localdep_memcpy)((__NAMESPACE_LOCAL_SYM __localdep_xmalloc)(__size), ___argv, __size - sizeof(char *));
			___argv[___argc] = __NULLPTR; /* Sentinel */
		} else {
			___argv = (char **)(__NAMESPACE_LOCAL_SYM __localdep_xrealloc)(___argv, (___argc + __inject_argc + 1) * sizeof(char *));
		}
		/* Inject arguments */
		(__NAMESPACE_LOCAL_SYM __localdep_memmoveupc)(___argv + __i + __inject_argc,
		           ___argv + __i,
		           ___argc - __i, sizeof(char *));
		(__NAMESPACE_LOCAL_SYM __localdep_memcpyc)(___argv + __i, __inject_argv, __inject_argc, sizeof(char *));
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__inject_argv);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
		___argc += __inject_argc;
		__i += __inject_argc;
	}
	*__p_argc = (int)(unsigned int)___argc;
	*__p_argv = ___argv;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_expandargv_defined
#define __local___localdep_expandargv_defined
#define __localdep_expandargv __LIBC_LOCAL_NAME(expandargv)
#endif /* !__local___localdep_expandargv_defined */
#else /* (__CRT_HAVE_mapfile || (__AT_FDCWD && (__CRT_HAVE_fmapfileat || (__O_RDONLY && (__CRT_HAVE_openat64 || __CRT_HAVE_openat) && (__CRT_HAVE_fmapfile || ((__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))))) || (__O_RDONLY && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fmapfile || ((__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))))) && (__CRT_HAVE_xrealloc || ((__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __CRT_HAVE_xmalloc_failed)) && (__CRT_HAVE_xmalloc || __CRT_HAVE_xrealloc || __CRT_HAVE_xcalloc || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && __CRT_HAVE_xmalloc_failed)) */
#undef __local_expandargv_defined
#endif /* (!__CRT_HAVE_mapfile && (!__AT_FDCWD || (!__CRT_HAVE_fmapfileat && (!__O_RDONLY || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat) || (!__CRT_HAVE_fmapfile && ((!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)))))) && (!__O_RDONLY || (!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_fmapfile && ((!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))))) || (!__CRT_HAVE_xrealloc && ((!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || !__CRT_HAVE_xmalloc_failed)) || (!__CRT_HAVE_xmalloc && !__CRT_HAVE_xrealloc && !__CRT_HAVE_xcalloc && ((!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || !__CRT_HAVE_xmalloc_failed)) */
#endif /* !__local_expandargv_defined */
