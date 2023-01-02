/* HASH CRC-32:0xd922ec23 */
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
#ifndef __local__obstack_newchunk_defined
#define __local__obstack_newchunk_defined
#include <__crt.h>
#include <bits/crt/obstack.h>
#if defined(__LOCAL_obstack_alloc_failed_handler) || defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE_xexit)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_exit_defined
#define __local___localdep_exit_defined
#if __has_builtin(__builtin_exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_NORETURN,void,__THROWING,__localdep_exit,(int __status),exit,{ __builtin_exit(__status); })
#elif defined(__CRT_HAVE_exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep_exit,(int __status),exit,(__status))
#elif defined(__CRT_HAVE_quick_exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep_exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE__exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep_exit,(int __status),_exit,(__status))
#elif defined(__CRT_HAVE__Exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep_exit,(int __status),_Exit,(__status))
#elif defined(__CRT_HAVE_xexit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep_exit,(int __status),xexit,(__status))
#else /* ... */
#undef __local___localdep_exit_defined
#endif /* !... */
#endif /* !__local___localdep_exit_defined */
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
__LOCAL_LIBC(_obstack_newchunk) __ATTR_INOUT(1) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_obstack_newchunk))(struct obstack *__self, __SIZE_TYPE__ __num_bytes) {
	void *__curobj;
	struct _obstack_chunk *__ochunk;
	struct _obstack_chunk *__nchunk;
	__SIZE_TYPE__ __osize = (__SIZE_TYPE__)(__self->next_free - __self->object_base);
	__SIZE_TYPE__ __csize = __osize + __num_bytes + (__osize >> 3) + __self->alignment_mask + 100;
	if (__csize < __self->chunk_size)
		__csize = __self->chunk_size;
	/* Allocate the new chunk. */
	__ochunk = __self->chunk;
	__nchunk = (struct _obstack_chunk *)__obstack_malloc(__self, __csize);
	if (!__nchunk) {
		__csize = __osize + __num_bytes + __self->alignment_mask;
		if (__csize < __self->chunk_size)
			__csize = __self->chunk_size;
		__nchunk = (struct _obstack_chunk *)__obstack_malloc(__self, __csize);
		if (!__nchunk) {
#ifdef __LOCAL_obstack_alloc_failed_handler
			(*__LOCAL_obstack_alloc_failed_handler)();
#elif defined(__LOCAL_obstack_exit_failure)
			(__NAMESPACE_LOCAL_SYM __localdep_exit)(__LOCAL_obstack_exit_failure);
#else /* ... */
			(__NAMESPACE_LOCAL_SYM __localdep_exit)(1);
#endif /* !... */
		}
	}
	__nchunk->prev      = __ochunk;
	__nchunk->limit     = (char *)__nchunk + __csize;
	__self->chunk       = __nchunk;
	__self->chunk_limit = __nchunk->limit;
	__curobj = __PTR_ALIGN((char *)__nchunk, __nchunk->contents, __self->alignment_mask);

	/* Copy the current object to the new chunk. */
	(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(__curobj, __self->object_base, __osize);

	/* If the old object was the only one of the old chunk, and if the
	 * old chunk couldn't possibly  have contained an "empty"  object,
	 * then we can free the old chunk. */
	if (!__self->maybe_empty_object &&
	    __self->object_base == __PTR_ALIGN((char *)__ochunk, __ochunk->contents,
	                                       __self->alignment_mask)) {
		__nchunk->prev = __ochunk->prev;
		__obstack_free(__self, __ochunk);
	}

	/* Remember the specs */
	__self->object_base = (char *)__curobj;
	__self->next_free   = (char *)__curobj + __osize;
	__self->maybe_empty_object = 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__obstack_newchunk_defined
#define __local___localdep__obstack_newchunk_defined
#define __localdep__obstack_newchunk __LIBC_LOCAL_NAME(_obstack_newchunk)
#endif /* !__local___localdep__obstack_newchunk_defined */
#else /* __LOCAL_obstack_alloc_failed_handler || __CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit || __CRT_HAVE_xexit */
#undef __local__obstack_newchunk_defined
#endif /* !__LOCAL_obstack_alloc_failed_handler && !__CRT_HAVE_exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE__exit && !__CRT_HAVE__Exit && !__CRT_HAVE_xexit */
#endif /* !__local__obstack_newchunk_defined */
