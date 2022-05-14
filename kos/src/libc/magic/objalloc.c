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
%(c_prefix){
/* (#) Portability: EMX kLIBC (/libc/include/objalloc.h) */
/* (#) Portability: libiberty (/include/objalloc.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.libiberty")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/crt/objalloc.h>
)]%{

/* Alignment guarantied for memory allocated by objalloc objects. */
#ifndef OBJALLOC_ALIGN
#define OBJALLOC_ALIGN __LIBC_MALLOC_ALIGNMENT
#endif /* !OBJALLOC_ALIGN */

#ifdef __CC__
__SYSDECL_BEGIN

}

%[define(OBJALLOC_ALIGN = __LIBC_MALLOC_ALIGNMENT)]


@@>> objalloc_create(3)
@@Allocate and initialize a new objalloc object.
@@@return: * :   The new objalloc object
@@@return: NULL: Out of memory
[[decl_include("<bits/crt/objalloc.h>")]]
[[requires_function(malloc)]]
struct objalloc *objalloc_create(void) {
	struct objalloc *result;
	result = (struct objalloc *)malloc(sizeof(struct objalloc));
	if likely(result) {
		struct __objalloc_chunk *first;
		first = (struct __objalloc_chunk *)malloc(__OBJALLOC_CHUNK_SIZE);
		if unlikely(result->@chunks@ == NULL) {
@@pp_if $has_function(free)@@
			free(result);
@@pp_endif@@
			return NULL;
		}
		result->@chunks@        = first;
		first->@__oc_prev@      = NULL;
		first->@__oc_curptr@    = NULL;
		result->@current_ptr@   = (char *)first + __OBJALLOC_CHUNK_HEADER_SIZE;
		result->@current_space@ = __OBJALLOC_CHUNK_SIZE - __OBJALLOC_CHUNK_HEADER_SIZE;
	}
	return result;
}


@@>> _objalloc_alloc(3)
@@Allocate `num_bytes' of memory from `self'
@@@return: * :   The `num_bytes'-large data-blob
@@@return: NULL: Out of memory
[[decl_include("<bits/crt/objalloc.h>", "<hybrid/typecore.h>")]]
[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC, ATTR_ALLOC_SIZE((2))]]
[[requires_function(malloc)]]
void *_objalloc_alloc([[nonnull]] struct objalloc *self,
                      __ULONGPTR_TYPE__ num_bytes) {
	struct __objalloc_chunk *newchunk;
	size_t size = (size_t)num_bytes;
	if unlikely(size == 0)
		size = 1;

	/* Force alignment. */
	size = (size + OBJALLOC_ALIGN - 1) & ~(OBJALLOC_ALIGN - 1);

	/* Check if the current chunk still contains enough space. */
	if (size <= self->@current_space@) {
		void *result;
steal_from_current_chunk:
		result = self->@current_ptr@;
		self->@current_ptr@ += size;
		self->@current_space@ -= size;
		return result;
	}

	/* Check if we should allocate a dedicated chunk for a large request. */
	if (size >= __OBJALLOC_BIG_REQUEST) {
		size_t chunksize = size + __OBJALLOC_CHUNK_HEADER_SIZE;
		if unlikely(chunksize < num_bytes)
			return NULL; /* Overflow */
		newchunk = (struct __objalloc_chunk *)malloc(chunksize);
		if unlikely(!newchunk)
			return NULL;
		newchunk->@__oc_prev@   = (struct __objalloc_chunk *)self->@chunks@;
		newchunk->@__oc_curptr@ = self->@current_ptr@;
		self->@chunks@ = newchunk;
		return (byte_t *)newchunk + __OBJALLOC_CHUNK_HEADER_SIZE;
	}

	/* Allocate a new chunk for "small objects" */
	newchunk = (struct __objalloc_chunk *)malloc(__OBJALLOC_CHUNK_SIZE);
	if unlikely(!newchunk)
		return NULL;
	newchunk->@__oc_prev@   = (struct __objalloc_chunk *)self->@chunks@;
	newchunk->@__oc_curptr@ = NULL; /* small-object chunk! */
	self->@current_ptr@   = (char *)newchunk + __OBJALLOC_CHUNK_HEADER_SIZE;
	self->@current_space@ = __OBJALLOC_CHUNK_SIZE - __OBJALLOC_CHUNK_HEADER_SIZE;
	self->@chunks@        = newchunk;
	goto steal_from_current_chunk;
}


@@>> objalloc_free(3)
@@Free all memory allocated by `self', before also freeing `self'
[[decl_include("<bits/crt/objalloc.h>"), requires_function(free)]]
[[decl_include("<bits/crt/objalloc.h>")]]
void objalloc_free([[nonnull]] struct objalloc *self) {
	struct __objalloc_chunk *iter;
	/* Simply free all chunks, then free `self' */
	for (iter = (struct __objalloc_chunk *)self->@chunks@; iter;) {
		struct __objalloc_chunk *next;
		next = iter->@__oc_prev@;
		free(iter);
		iter = next;
	}
	free(self);
}

@@>> objalloc_free_block(3)
@@Free a given `ptr', as well as everything allocated since.
[[decl_include("<bits/crt/objalloc.h>")]]
[[impl_include("<bits/crt/objalloc.h>", "<hybrid/__assert.h>")]]
[[requires_function(free)]]
void objalloc_free_block([[nonnull]] struct objalloc *self,
                         [[nonnull]] void *ptr) {
	struct __objalloc_chunk *iter;
	for (;;) {
		iter = (struct __objalloc_chunk *)self->@chunks@;
		__hybrid_assertf(iter, "Unable to find chunk for %p -- not allocated by this objalloc?", ptr);
		if (iter->@__oc_curptr@) {
			/* small-object chunk. */
			if ((byte_t *)ptr >= (byte_t *)iter &&
			    (byte_t *)ptr < (byte_t *)iter + __OBJALLOC_CHUNK_SIZE) {
				/* Found it! */
				self->@current_ptr@   = (char *)ptr;
				self->@current_space@ = ((byte_t *)iter + __OBJALLOC_CHUNK_SIZE) - (byte_t *)ptr;
				break;
			}
		} else {
			/* large-(single-)object chunk */
			if ((byte_t *)ptr == (byte_t *)iter + __OBJALLOC_CHUNK_HEADER_SIZE) {
				struct __objalloc_chunk *prev_small_chunk;
				self->@chunks@      = iter->@__oc_prev@;
				self->@current_ptr@ = iter->@__oc_curptr@;
				free(iter);

				/* Find the preceding small-chunk into which `self->@current_ptr@' points.
				 * Because of  constraints, that  is guarantied  to be  the  most-recently
				 * allocated small-chunk, meaning  we only have  to skip additional  large
				 * chunks allocated at this point. */
				prev_small_chunk = (struct __objalloc_chunk *)self->@chunks@;
				while (prev_small_chunk->@__oc_curptr@ != NULL) {
					__hybrid_assert(prev_small_chunk->@__oc_prev@);
					__hybrid_assert(prev_small_chunk->@__oc_curptr@ == self->@current_ptr@);
					prev_small_chunk = prev_small_chunk->@__oc_prev@;
				}
				__hybrid_assert((byte_t *)self->@current_ptr@ >= (byte_t *)prev_small_chunk);
				__hybrid_assert((byte_t *)self->@current_ptr@ < ((byte_t *)prev_small_chunk + __OBJALLOC_CHUNK_SIZE));
				self->@current_space@ = (size_t)(((byte_t *)prev_small_chunk + __OBJALLOC_CHUNK_SIZE) -
				                                 ((byte_t *)self->@current_ptr@));
				break;
			}
		}

		/* Discard this chunk. */
		self->@chunks@ = iter->@__oc_prev@;
		free(iter);
	}

}



%[insert:pp_if($has_function(_objalloc_alloc))]
%{
#ifndef __NO_XBLOCK
#define objalloc_alloc(self, num_bytes)                                                 \
	__XBLOCK({                                                                          \
		struct objalloc *__oa_self       = (self);                                      \
		__ULONGPTR_TYPE__ __oa_num_bytes = (num_bytes);                                 \
		if (__oa_num_bytes == 0)                                                        \
			__oa_num_bytes = 1;                                                         \
		__oa_num_bytes = (__oa_num_bytes + OBJALLOC_ALIGN - 1) & ~(OBJALLOC_ALIGN - 1); \
		__XRETURN __oa_num_bytes != 0 && __oa_num_bytes <= __oa_self->current_space     \
		          ? (__oa_self->current_ptr += __oa_num_bytes,                          \
		             __oa_self->current_space -= __oa_num_bytes,                        \
		             (void *)(__oa_self->current_ptr - __oa_num_bytes))                 \
		          : _objalloc_alloc(__oa_self, __oa_num_bytes);                         \
	})
#else /* !__NO_XBLOCK */
#define objalloc_alloc(self, num_bytes) _objalloc_alloc(self, num_bytes)
#endif /* __NO_XBLOCK */
}
%[insert:pp_endif]


%{

__SYSDECL_END
#endif /* __CC__ */

}
