/* HASH CRC-32:0xf8c6ba9a */
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
#ifndef __local_open_memstream_defined
#define __local_open_memstream_defined
#include <__crt.h>
#include <bits/types.h>
#if (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2)) && (defined(__CRT_HAVE_recalloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_bzero_defined
#define __local___localdep_bzero_defined
#ifdef __CRT_HAVE_bzero
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__dst,__num_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/bzero.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bzero __LIBC_LOCAL_NAME(bzero)
#endif /* !... */
#endif /* !__local___localdep_bzero_defined */
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
#ifndef __local___localdep_funopen2_64_defined
#define __local___localdep_funopen2_64_defined
#if defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen2_64,(void const *__cookie, __SSIZE_TYPE__ (__LIBKCALL *__readfn)(void *__cookie, void *__buf, __SIZE_TYPE__ __num_bytes), __SSIZE_TYPE__ (__LIBKCALL *__writefn)(void *__cookie, void const *__buf, __SIZE_TYPE__ __num_bytes), __off64_t (__LIBKCALL *__seekfn)(void *__cookie, __off64_t __off, int __whence), int (__LIBKCALL *__flushfn)(void *__cookie), int (__LIBKCALL *__closefn)(void *__cookie)),funopen2,(__cookie,__readfn,__writefn,__seekfn,__flushfn,__closefn))
#elif defined(__CRT_HAVE_funopen2_64)
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen2_64,(void const *__cookie, __SSIZE_TYPE__ (__LIBKCALL *__readfn)(void *__cookie, void *__buf, __SIZE_TYPE__ __num_bytes), __SSIZE_TYPE__ (__LIBKCALL *__writefn)(void *__cookie, void const *__buf, __SIZE_TYPE__ __num_bytes), __off64_t (__LIBKCALL *__seekfn)(void *__cookie, __off64_t __off, int __whence), int (__LIBKCALL *__flushfn)(void *__cookie), int (__LIBKCALL *__closefn)(void *__cookie)),funopen2_64,(__cookie,__readfn,__writefn,__seekfn,__flushfn,__closefn))
#elif defined(__CRT_HAVE_funopen2)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/funopen2_64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_funopen2_64 __LIBC_LOCAL_NAME(funopen2_64)
#else /* ... */
#undef __local___localdep_funopen2_64_defined
#endif /* !... */
#endif /* !__local___localdep_funopen2_64_defined */
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined
#if __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,(__num_bytes))
#elif defined(__CRT_HAVE___libc_malloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),__libc_malloc,(__num_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/malloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_malloc __LIBC_LOCAL_NAME(malloc)
#else /* ... */
#undef __local___localdep_malloc_defined
#endif /* !... */
#endif /* !__local___localdep_malloc_defined */
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined
#ifdef __CRT_HAVE_memcpy
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE___libc_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),__libc_realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __local___localdep_realloc_defined
#endif /* !... */
#endif /* !__local___localdep_realloc_defined */
#ifndef __local___localdep_recalloc_defined
#define __local___localdep_recalloc_defined
#ifdef __CRT_HAVE_recalloc
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_recalloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),recalloc,(__mallptr,__num_bytes))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
__NAMESPACE_LOCAL_END
#include <libc/local/malloc/recalloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_recalloc __LIBC_LOCAL_NAME(recalloc)
#else /* ... */
#undef __local___localdep_recalloc_defined
#endif /* !... */
#endif /* !__local___localdep_recalloc_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
#include <asm/os/stdio.h>
#include <hybrid/__overflow.h>
__NAMESPACE_LOCAL_BEGIN
struct __memstream_file {
	__BYTE_TYPE__ **__mf_pbase; /* [1..1] Pointer to the user-defined base field. */
	__SIZE_TYPE__  *__mf_psize; /* [1..1] Pointer to the user-defined size field. */
	__BYTE_TYPE__  *__mf_base;  /* [0..1][owned] Allocated base pointer. */
	__BYTE_TYPE__  *__mf_ptr;   /* [0..1] Current read/write pointer (May be located beyond `mf_end'; allocated lazily during writes). */
	__BYTE_TYPE__  *__mf_end;   /* [0..1] Allocated buffer end pointer. */
};

__LOCAL_LIBC(memstream_read) __ATTR_OUTS(2, 3) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __memstream_read)(void *__cookie, void *__buf, __SIZE_TYPE__ __num_bytes) {
	struct __memstream_file *__me;
	__SIZE_TYPE__ __maxread;
	__me = (struct __memstream_file *)__cookie;
	__maxread = __me->__mf_end - __me->__mf_ptr;
	if (__maxread > __num_bytes)
		__maxread = __num_bytes;
	(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(__buf, __me->__mf_ptr, __maxread);
	__me->__mf_ptr += __maxread;
	return (__SSIZE_TYPE__)__maxread;
}

__LOCAL_LIBC(memstream_write) __ATTR_INS(2, 3) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __memstream_write)(void *__cookie, void const *__buf, __SIZE_TYPE__ __num_bytes) {
	struct __memstream_file *__me;
	__SIZE_TYPE__ __new_alloc, __result = 0;
	__BYTE_TYPE__ *__new_buffer;
	__me = (struct __memstream_file *)__cookie;
	if __likely(__me->__mf_ptr < __me->__mf_end) {
		__result = __me->__mf_end - __me->__mf_ptr;
		if (__result > __num_bytes)
			__result = __num_bytes;
		(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(__me->__mf_ptr, __buf, __num_bytes);
		__me->__mf_ptr += __result;
		__buf = (__BYTE_TYPE__ const *)__buf + __result;
		__num_bytes -= __result;
	}
	if (!__num_bytes)
		goto __done;
	/* Allocate more memory. */
	__new_alloc = (__SIZE_TYPE__)(__me->__mf_ptr - __me->__mf_base);
	if __unlikely(__hybrid_overflow_uadd(__new_alloc, __num_bytes, &__new_alloc))
		goto __err_EOVERFLOW;
#if defined(__CRT_HAVE_recalloc) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize)))
	/* Try  to use  recalloc() to  do the  zero-initialization for us.
	 * Since this is the only place where a buffer is ever  allocated,
	 * this also means that any newly allocated buffer space is always
	 * zero-initialized, and we  don't have to  worry about any  delta
	 * between `end - base' and `malloc_usable_size()'. */
	__new_buffer = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_recalloc)(__me->__mf_base,
	                                (__new_alloc + 1) *
	                                sizeof(char));
	if __unlikely(!__new_buffer)
		goto __err;
#else /* __CRT_HAVE_recalloc || ((__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_malloc_usable_size || __CRT_HAVE__msize)) */
	__new_buffer = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__me->__mf_base,
	                               (__new_alloc + 1) *
	                               sizeof(char));
	if __unlikely(!__new_buffer)
		goto __err;
	{
		/* Zero-initialize newly allocated memory (that won't be overwritten in a moment) */
		__SIZE_TYPE__ __oldsiz, __baspos;
		__oldsiz = (__SIZE_TYPE__)(__me->__mf_end - __me->__mf_base);
		__baspos = (__SIZE_TYPE__)(__me->__mf_ptr - __me->__mf_base);
		if (__baspos > __oldsiz)
			(__NAMESPACE_LOCAL_SYM __localdep_bzero)(__new_buffer + __oldsiz, (__baspos - __oldsiz) * sizeof(char));
	}
#endif /* !__CRT_HAVE_recalloc && ((!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_malloc_usable_size && !__CRT_HAVE__msize)) */
	__me->__mf_ptr  = __new_buffer + (__me->__mf_ptr - __me->__mf_base);
	__me->__mf_base = __new_buffer;
	__me->__mf_end  = __new_buffer + __new_alloc;
	/* Copy data into the new portion of the buf. */
	(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(__me->__mf_ptr, __buf, __num_bytes);
	*__me->__mf_end = 0; /* NUL-termination. */
	__result += __num_bytes;
	/* Update the user-given pointer locations with buf parameters. */
	*__me->__mf_pbase = __me->__mf_base;
	*__me->__mf_psize = (__SIZE_TYPE__)(__me->__mf_end - __me->__mf_base);
__done:
	return (__SSIZE_TYPE__)__result;
__err_EOVERFLOW:
#ifdef __EOVERFLOW
	__libc_seterrno(__EOVERFLOW);
#else /* __EOVERFLOW */
	__libc_seterrno(1);
#endif /* !__EOVERFLOW */
__err:
	return -1;
}

__LOCAL_LIBC(memstream_seek) __off64_t
__NOTHROW(__LIBCCALL __memstream_seek)(void *__cookie, __off64_t __off, int __whence) {
	struct __memstream_file *__me;
	__off64_t __new_pos;
	__me = (struct __memstream_file *)__cookie;
	__new_pos = (__off64_t)(__pos64_t)(__SIZE_TYPE__)(__me->__mf_ptr - __me->__mf_base);
	switch (__whence) {

	case __SEEK_SET:
		__new_pos = __off;
		break;

	case __SEEK_CUR:
		__new_pos += __off;
		break;

	case __SEEK_END:
		__new_pos = (__SIZE_TYPE__)(__me->__mf_end - __me->__mf_base) + __off;
		break;

	default:
#ifdef __EINVAL
		return (__off64_t)__libc_seterrno(__EINVAL);
#else /* __EINVAL */
		return (__off64_t)__libc_seterrno(1);
#endif /* !__EINVAL */
	}
	if __unlikely(__new_pos < 0)
		goto __err_EOVERFLOW;
	/* Update the actual buffer read/write pointer. */
	if __unlikely(__hybrid_overflow_uadd((__UINTPTR_TYPE__)__me->__mf_base,
	                                   (__pos64_t)__new_pos,
	                                   (__UINTPTR_TYPE__ *)&__me->__mf_ptr))
		goto __err_EOVERFLOW;
	return (__off64_t)__new_pos;
__err_EOVERFLOW:
#ifdef __EOVERFLOW
	return (__off64_t)__libc_seterrno(__EOVERFLOW);
#else /* __EOVERFLOW */
	return (__off64_t)__libc_seterrno(1);
#endif /* !__EOVERFLOW */
}

__LOCAL_LIBC(memstream_close) int
__NOTHROW(__LIBCCALL __memstream_close)(void *__cookie) {
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__cookie);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return 0;
}

__NAMESPACE_LOCAL_END
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(open_memstream) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __FILE *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(open_memstream))(char **__bufloc, __SIZE_TYPE__ *__sizeloc) {
	__FILE *__result;
	struct __NAMESPACE_LOCAL_SYM __memstream_file *__magic;
	__magic = (struct __NAMESPACE_LOCAL_SYM __memstream_file *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(sizeof(struct __NAMESPACE_LOCAL_SYM __memstream_file));
	if __unlikely(!__magic)
		return __NULLPTR;
	__magic->__mf_pbase = (__BYTE_TYPE__ **)__bufloc;
	__magic->__mf_psize = __sizeloc;
	__magic->__mf_base  = __NULLPTR;
	__magic->__mf_ptr   = __NULLPTR;
	__magic->__mf_end   = __NULLPTR;
	/* Open a custom file-stream. */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_funopen2_64)(__magic,
	                     &__NAMESPACE_LOCAL_SYM __memstream_read,
	                     &__NAMESPACE_LOCAL_SYM __memstream_write,
	                     &__NAMESPACE_LOCAL_SYM __memstream_seek,
	                     __NULLPTR,
	                     &__NAMESPACE_LOCAL_SYM __memstream_close);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	if __unlikely(!__result)
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__magic);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_open_memstream_defined
#define __local___localdep_open_memstream_defined
#define __localdep_open_memstream __LIBC_LOCAL_NAME(open_memstream)
#endif /* !__local___localdep_open_memstream_defined */
#else /* (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && ((__CRT_HAVE_funopen2 && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || __CRT_HAVE_funopen2_64 || __CRT_HAVE_funopen2) && (__CRT_HAVE_recalloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#undef __local_open_memstream_defined
#endif /* (!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_funopen2_64 && !__CRT_HAVE_funopen2) || (!__CRT_HAVE_recalloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
#endif /* !__local_open_memstream_defined */
