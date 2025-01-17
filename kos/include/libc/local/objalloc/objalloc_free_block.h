/* HASH CRC-32:0xb1ee428a */
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
#ifndef __local_objalloc_free_block_defined
#define __local_objalloc_free_block_defined
#include <__crt.h>
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
#include <bits/crt/objalloc.h>
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
__NAMESPACE_LOCAL_END
#include <hybrid/__assert.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(objalloc_free_block) __ATTR_INOUT(1) __ATTR_NONNULL((2)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(objalloc_free_block))(struct objalloc *__self, void *__ptr) {
	struct __objalloc_chunk *__iter;
	for (;;) {
		__iter = (struct __objalloc_chunk *)__self->chunks;
		__hybrid_assertf(__iter, "Unable to find chunk for %p -- not allocated by this objalloc?", __ptr);
		if (__iter->__oc_curptr) {
			/* small-object chunk. */
			if ((__BYTE_TYPE__ *)__ptr >= (__BYTE_TYPE__ *)__iter &&
			    (__BYTE_TYPE__ *)__ptr < (__BYTE_TYPE__ *)__iter + __OBJALLOC_CHUNK_SIZE) {
				/* Found it! */
				__self->current_ptr   = (char *)__ptr;
				__self->current_space = ((__BYTE_TYPE__ *)__iter + __OBJALLOC_CHUNK_SIZE) - (__BYTE_TYPE__ *)__ptr;
				break;
			}
		} else {
			/* large-(single-)object chunk */
			if ((__BYTE_TYPE__ *)__ptr == (__BYTE_TYPE__ *)__iter + __OBJALLOC_CHUNK_HEADER_SIZE) {
				struct __objalloc_chunk *__prev_small_chunk;
				__self->chunks      = __iter->__oc_prev;
				__self->current_ptr = __iter->__oc_curptr;
				(__NAMESPACE_LOCAL_SYM __localdep_free)(__iter);

				/* Find the preceding small-chunk into which `self->@current_ptr@' points.
				 * Because of  constraints, that  is guarantied  to be  the  most-recently
				 * allocated small-chunk, meaning  we only have  to skip additional  large
				 * chunks allocated at this point. */
				__prev_small_chunk = (struct __objalloc_chunk *)__self->chunks;
				while (__prev_small_chunk->__oc_curptr != __NULLPTR) {
					__hybrid_assert(__prev_small_chunk->__oc_prev);
					__hybrid_assert(__prev_small_chunk->__oc_curptr == __self->current_ptr);
					__prev_small_chunk = __prev_small_chunk->__oc_prev;
				}
				__hybrid_assert((__BYTE_TYPE__ *)__self->current_ptr >= (__BYTE_TYPE__ *)__prev_small_chunk);
				__hybrid_assert((__BYTE_TYPE__ *)__self->current_ptr < ((__BYTE_TYPE__ *)__prev_small_chunk + __OBJALLOC_CHUNK_SIZE));
				__self->current_space = (__SIZE_TYPE__)(((__BYTE_TYPE__ *)__prev_small_chunk + __OBJALLOC_CHUNK_SIZE) -
				                                 ((__BYTE_TYPE__ *)__self->current_ptr));
				break;
			}
		}

		/* Discard this chunk. */
		__self->chunks = __iter->__oc_prev;
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__iter);
	}

}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_objalloc_free_block_defined
#define __local___localdep_objalloc_free_block_defined
#define __localdep_objalloc_free_block __LIBC_LOCAL_NAME(objalloc_free_block)
#endif /* !__local___localdep_objalloc_free_block_defined */
#else /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
#undef __local_objalloc_free_block_defined
#endif /* !__CRT_HAVE_free && !__CRT_HAVE_cfree && !__CRT_HAVE___libc_free */
#endif /* !__local_objalloc_free_block_defined */
