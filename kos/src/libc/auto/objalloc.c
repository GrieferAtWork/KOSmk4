/* HASH CRC-32:0xfd1a8cc3 */
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
#ifndef GUARD_LIBC_AUTO_OBJALLOC_C
#define GUARD_LIBC_AUTO_OBJALLOC_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "objalloc.h"
#include "../user/stdlib.h"

DECL_BEGIN

#ifndef __KERNEL__
/* >> objalloc_create(3)
 * Allocate and initialize a new objalloc object.
 * @return: * :   The new objalloc object
 * @return: NULL: Out of memory */
INTERN ATTR_SECTION(".text.crt.libiberty") struct objalloc *
NOTHROW_NCX(LIBCCALL libc_objalloc_create)(void) {
	struct objalloc *result;
	result = (struct objalloc *)libc_malloc(sizeof(struct objalloc));
	if likely(result) {
		struct __objalloc_chunk *first;
		first = (struct __objalloc_chunk *)libc_malloc(__OBJALLOC_CHUNK_SIZE);
		if unlikely(result->chunks == NULL) {

			libc_free(result);

			return NULL;
		}
		result->chunks        = first;
		first->__oc_prev      = NULL;
		first->__oc_curptr    = NULL;
		result->current_ptr   = (char *)first + __OBJALLOC_CHUNK_HEADER_SIZE;
		result->current_space = __OBJALLOC_CHUNK_SIZE - __OBJALLOC_CHUNK_HEADER_SIZE;
	}
	return result;
}
/* >> _objalloc_alloc(3)
 * Allocate `num_bytes' of memory from `self'
 * @return: * :   The `num_bytes'-large data-blob
 * @return: NULL: Out of memory */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_INOUT(1) void *
NOTHROW_NCX(LIBCCALL libc__objalloc_alloc)(struct objalloc *self,
                                           __ULONGPTR_TYPE__ num_bytes) {
	struct __objalloc_chunk *newchunk;
	size_t size = (size_t)num_bytes;
	if unlikely(size == 0)
		size = 1;

	/* Force alignment. */
	size = (size + __LIBC_MALLOC_ALIGNMENT - 1) & ~(__LIBC_MALLOC_ALIGNMENT - 1);

	/* Check if the current chunk still contains enough space. */
	if (size <= self->current_space) {
		void *result;
steal_from_current_chunk:
		result = self->current_ptr;
		self->current_ptr += size;
		self->current_space -= size;
		return result;
	}

	/* Check if we should allocate a dedicated chunk for a large request. */
	if (size >= __OBJALLOC_BIG_REQUEST) {
		size_t chunksize = size + __OBJALLOC_CHUNK_HEADER_SIZE;
		if unlikely(chunksize < num_bytes)
			return NULL; /* Overflow */
		newchunk = (struct __objalloc_chunk *)libc_malloc(chunksize);
		if unlikely(!newchunk)
			return NULL;
		newchunk->__oc_prev   = (struct __objalloc_chunk *)self->chunks;
		newchunk->__oc_curptr = self->current_ptr;
		self->chunks = newchunk;
		return (byte_t *)newchunk + __OBJALLOC_CHUNK_HEADER_SIZE;
	}

	/* Allocate a new chunk for "small objects" */
	newchunk = (struct __objalloc_chunk *)libc_malloc(__OBJALLOC_CHUNK_SIZE);
	if unlikely(!newchunk)
		return NULL;
	newchunk->__oc_prev   = (struct __objalloc_chunk *)self->chunks;
	newchunk->__oc_curptr = NULL; /* small-object chunk! */
	self->current_ptr   = (char *)newchunk + __OBJALLOC_CHUNK_HEADER_SIZE;
	self->current_space = __OBJALLOC_CHUNK_SIZE - __OBJALLOC_CHUNK_HEADER_SIZE;
	self->chunks        = newchunk;
	goto steal_from_current_chunk;
}
/* >> objalloc_free(3)
 * Free all memory allocated by `self', before also freeing `self' */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_INOUT(1) void
NOTHROW_NCX(LIBCCALL libc_objalloc_free)(struct objalloc *self) {
	struct __objalloc_chunk *iter;
	/* Simply free all chunks, then free `self' */
	for (iter = (struct __objalloc_chunk *)self->chunks; iter;) {
		struct __objalloc_chunk *next;
		next = iter->__oc_prev;
		libc_free(iter);
		iter = next;
	}
	libc_free(self);
}
#include <bits/crt/objalloc.h>
#include <hybrid/__assert.h>
/* >> objalloc_free_block(3)
 * Free a given `ptr', as well as everything allocated since. */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_INOUT(1) NONNULL((2)) void
NOTHROW_NCX(LIBCCALL libc_objalloc_free_block)(struct objalloc *self,
                                               void *ptr) {
	struct __objalloc_chunk *iter;
	for (;;) {
		iter = (struct __objalloc_chunk *)self->chunks;
		__hybrid_assertf(iter, "Unable to find chunk for %p -- not allocated by this objalloc?", ptr);
		if (iter->__oc_curptr) {
			/* small-object chunk. */
			if ((byte_t *)ptr >= (byte_t *)iter &&
			    (byte_t *)ptr < (byte_t *)iter + __OBJALLOC_CHUNK_SIZE) {
				/* Found it! */
				self->current_ptr   = (char *)ptr;
				self->current_space = ((byte_t *)iter + __OBJALLOC_CHUNK_SIZE) - (byte_t *)ptr;
				break;
			}
		} else {
			/* large-(single-)object chunk */
			if ((byte_t *)ptr == (byte_t *)iter + __OBJALLOC_CHUNK_HEADER_SIZE) {
				struct __objalloc_chunk *prev_small_chunk;
				self->chunks      = iter->__oc_prev;
				self->current_ptr = iter->__oc_curptr;
				libc_free(iter);

				/* Find the preceding small-chunk into which `self->@current_ptr@' points.
				 * Because of  constraints, that  is guarantied  to be  the  most-recently
				 * allocated small-chunk, meaning  we only have  to skip additional  large
				 * chunks allocated at this point. */
				prev_small_chunk = (struct __objalloc_chunk *)self->chunks;
				while (prev_small_chunk->__oc_curptr != NULL) {
					__hybrid_assert(prev_small_chunk->__oc_prev);
					__hybrid_assert(prev_small_chunk->__oc_curptr == self->current_ptr);
					prev_small_chunk = prev_small_chunk->__oc_prev;
				}
				__hybrid_assert((byte_t *)self->current_ptr >= (byte_t *)prev_small_chunk);
				__hybrid_assert((byte_t *)self->current_ptr < ((byte_t *)prev_small_chunk + __OBJALLOC_CHUNK_SIZE));
				self->current_space = (size_t)(((byte_t *)prev_small_chunk + __OBJALLOC_CHUNK_SIZE) -
				                                 ((byte_t *)self->current_ptr));
				break;
			}
		}

		/* Discard this chunk. */
		self->chunks = iter->__oc_prev;
		libc_free(iter);
	}

}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(objalloc_create, libc_objalloc_create);
DEFINE_PUBLIC_ALIAS(_objalloc_alloc, libc__objalloc_alloc);
DEFINE_PUBLIC_ALIAS(objalloc_free, libc_objalloc_free);
DEFINE_PUBLIC_ALIAS(objalloc_free_block, libc_objalloc_free_block);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_OBJALLOC_C */
