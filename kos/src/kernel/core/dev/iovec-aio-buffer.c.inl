/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "iovec.c"
#define DEFINE_FOR_AIO_BUFFER 1
//#define DEFINE_FOR_AIO_PBUFFER 1
#endif /* __INTELLISENSE__ */

DECL_BEGIN

#if (defined(DEFINE_FOR_AIO_BUFFER) + defined(DEFINE_FOR_AIO_PBUFFER)) != 1
#error "Must #define exactly one of `DEFINE_FOR_AIO_BUFFER', `DEFINE_FOR_AIO_PBUFFER'"
#endif /* ... */


#ifdef DEFINE_FOR_AIO_BUFFER
#define STRUCT_AIO_BUFFER       struct aio_buffer
#define STRUCT_AIO_BUFFER_ENTRY struct aio_buffer_entry
#define AIO_ARITH_TYPE          byte_t *
#define AIO_BUFFER_FUNC(name)   aio_buffer_##name
#else /* DEFINE_FOR_AIO_BUFFER */
#define STRUCT_AIO_BUFFER       struct aio_pbuffer
#define STRUCT_AIO_BUFFER_ENTRY struct aio_pbuffer_entry
#define AIO_ARITH_TYPE          physaddr_t
#define AIO_BUFFER_FUNC(name)   aio_pbuffer_##name
#endif /* !DEFINE_FOR_AIO_BUFFER */


/* Helper functions */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW(KCALL AIO_BUFFER_FUNC(size))(STRUCT_AIO_BUFFER const *__restrict self) {
	size_t i, result;
	result = self->ab_last + self->ab_head.ab_size;
	for (i = 1; i < self->ab_entc - 1; ++i)
		result += self->ab_entv[i].ab_size;
	return result;
}


PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL AIO_BUFFER_FUNC(init_view_before))(STRUCT_AIO_BUFFER *__restrict self,
                                                 STRUCT_AIO_BUFFER const *__restrict base,
                                                 uintptr_t end_offset) {
	size_t i;
	uintptr_t total = 0;
	assert(end_offset != 0);
	self->ab_entv = base->ab_entv;
	self->ab_head = base->ab_head;
	for (i = 0; i < base->ab_entc - 1; ++i) {
		size_t entsize;
		entsize = i ? base->ab_entv[i].ab_size
		            : base->ab_head.ab_size;
		total += entsize;
		if (total >= end_offset) {
			self->ab_entc = i;
			total -= entsize;
			self->ab_last = (size_t)(end_offset - total);
			return;
		}
	}
	assert(total + base->ab_last >= end_offset);
	self->ab_entc = i;
	self->ab_last = end_offset - total;
}

PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL AIO_BUFFER_FUNC(init_view_after))(STRUCT_AIO_BUFFER *__restrict self,
                                                STRUCT_AIO_BUFFER const *__restrict base,
                                                uintptr_t start_offset) {
	self->ab_last = base->ab_last;
	if (start_offset < base->ab_head.ab_size) {
		self->ab_entc         = base->ab_entc;
		self->ab_entv         = base->ab_entv;
		self->ab_head.ab_base = (AIO_ARITH_TYPE)base->ab_head.ab_base + start_offset;
		self->ab_head.ab_size = base->ab_head.ab_size - start_offset;
	} else {
		size_t i;
		start_offset -= base->ab_head.ab_size;
		for (i = 1;; ++i) {
			assert(i < base->ab_entc);
			if (start_offset < base->ab_entv[i].ab_size) {
				self->ab_entc = base->ab_entc - i;
				self->ab_entv = base->ab_entv + i;
				self->ab_head = self->ab_entv[0];
				self->ab_head.ab_base = (AIO_ARITH_TYPE)self->ab_head.ab_base + start_offset;
				self->ab_head.ab_size -= start_offset;
				return;
			}
			start_offset -= base->ab_entv[i].ab_size;
		}
	}
}

PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL AIO_BUFFER_FUNC(init_view))(STRUCT_AIO_BUFFER *__restrict self,
                                          STRUCT_AIO_BUFFER const *__restrict base,
                                          uintptr_t start_offset, size_t num_bytes) {
	size_t i, entc_after_start;
	uintptr_t total;
	assert(num_bytes != 0);
	if (start_offset < base->ab_head.ab_size) {
		entc_after_start      = base->ab_entc;
		self->ab_entv         = base->ab_entv;
		self->ab_head.ab_base = (AIO_ARITH_TYPE)base->ab_head.ab_base + start_offset;
		self->ab_head.ab_size = base->ab_head.ab_size - start_offset;
	} else {
		start_offset -= base->ab_head.ab_size;
		for (i = 1;; ++i) {
			assert(i < base->ab_entc);
			if (start_offset < base->ab_entv[i].ab_size) {
				entc_after_start      = base->ab_entc - i;
				self->ab_entv         = base->ab_entv + i;
				self->ab_head         = self->ab_entv[0];
				self->ab_head.ab_base = (AIO_ARITH_TYPE)self->ab_head.ab_base + start_offset;
				self->ab_head.ab_size -= start_offset;
				return;
			}
			start_offset -= base->ab_entv[i].ab_size;
		}
	}
	total = 0;
	for (i = 0; i < entc_after_start - 1; ++i) {
		size_t entsize;
		entsize = i ? self->ab_entv[i].ab_size
		            : self->ab_head.ab_size;
		total += entsize;
		if (total >= num_bytes) {
			self->ab_entc = i;
			total -= entsize;
			self->ab_last = (size_t)(num_bytes - total);
			return;
		}
	}
	assert(total + base->ab_last >= num_bytes);
	self->ab_entc = i;
	self->ab_last = num_bytes - total;
}

#undef AIO_BUFFER_FUNC
#undef AIO_ARITH_TYPE
#undef STRUCT_AIO_BUFFER_ENTRY
#undef STRUCT_AIO_BUFFER

DECL_END

#undef DEFINE_FOR_AIO_PBUFFER
#undef DEFINE_FOR_AIO_BUFFER
