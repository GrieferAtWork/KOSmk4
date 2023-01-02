/* HASH CRC-32:0x88e1a4ce */
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
#ifndef __local__obstack_begin_1_defined
#define __local__obstack_begin_1_defined
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
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_obstack_begin_1) __ATTR_OUT(1) __ATTR_NONNULL((4, 5)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_obstack_begin_1))(struct obstack *__self, __SIZE_TYPE__ __min_chunk_size, __SIZE_TYPE__ __min_object_alignment, void *(*__ob_malloc)(void *__arg, __SIZE_TYPE__ __num_bytes), void (*__ob_free)(void *__arg, void *__ptr), void *__arg) {
	struct _obstack_chunk *__nchunk;
	if (__min_object_alignment < __ALIGNOF_MAX_ALIGN_T__)
		__min_object_alignment = __ALIGNOF_MAX_ALIGN_T__;
	if (__min_chunk_size == 0) {
		/* This is what the source material does in this case.
		 * We don't want to break the ABI, so we do the  same. */
		__SIZE_TYPE__ __extra = ((((12 + sizeof(__MAX_ALIGN_TYPE__) - 1) &
		                  ~(sizeof(__MAX_ALIGN_TYPE__) - 1)) +
		                 4 + sizeof(__MAX_ALIGN_TYPE__) - 1) &
		                ~(sizeof(__MAX_ALIGN_TYPE__) - 1));
		__min_chunk_size = 4096 - __extra;
	}

	__self->chunkfun.extra = (void *(__LIBCCALL *)(void *, __SIZE_TYPE__))__ob_malloc;
	__self->freefun.extra  = (void (__LIBCCALL *)(void *, void *))__ob_free;
	__self->chunk_size       = __min_chunk_size;
	__self->alignment_mask   = __min_object_alignment - 1;

	__nchunk = (struct _obstack_chunk *)((*__ob_malloc)(__arg, __min_chunk_size));
	if (!__nchunk) {
#ifdef __LOCAL_obstack_alloc_failed_handler
		(*__LOCAL_obstack_alloc_failed_handler)();
#elif defined(__LOCAL_obstack_exit_failure)
		(__NAMESPACE_LOCAL_SYM __localdep_exit)(__LOCAL_obstack_exit_failure);
#else /* ... */
		(__NAMESPACE_LOCAL_SYM __localdep_exit)(1);
#endif /* !... */
	}
	__self->chunk       = __nchunk;
	__self->object_base = __PTR_ALIGN((char *)__nchunk, __nchunk->contents, __min_object_alignment - 1);
	__self->next_free   = __self->object_base;
	__nchunk->limit     = (char *)__nchunk + __min_chunk_size;
	__self->chunk_limit = __nchunk->limit;
	__nchunk->prev      = __NULLPTR;
	__self->extra_arg   = __arg;
	__self->use_extra_arg      = 1;
	__self->maybe_empty_object = 0;
	__self->alloc_failed       = 0;
	return 1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__obstack_begin_1_defined
#define __local___localdep__obstack_begin_1_defined
#define __localdep__obstack_begin_1 __LIBC_LOCAL_NAME(_obstack_begin_1)
#endif /* !__local___localdep__obstack_begin_1_defined */
#else /* __LOCAL_obstack_alloc_failed_handler || __CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit || __CRT_HAVE_xexit */
#undef __local__obstack_begin_1_defined
#endif /* !__LOCAL_obstack_alloc_failed_handler && !__CRT_HAVE_exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE__exit && !__CRT_HAVE__Exit && !__CRT_HAVE_xexit */
#endif /* !__local__obstack_begin_1_defined */
