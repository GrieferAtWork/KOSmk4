/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "iovec.c"
#define DEFINE_FOR_IOV_BUFFER 1
//#define DEFINE_FOR_IOV_PHYSBUFFER 1
#endif /* __INTELLISENSE__ */

DECL_BEGIN

#if (defined(DEFINE_FOR_IOV_BUFFER) + defined(DEFINE_FOR_IOV_PHYSBUFFER)) != 1
#error "Must #define exactly one of `DEFINE_FOR_IOV_BUFFER', `DEFINE_FOR_IOV_PHYSBUFFER'"
#endif /* ... */


#ifdef DEFINE_FOR_IOV_BUFFER
#define STRUCT_IOV_BUFFER     struct iov_buffer
#define STRUCT_IOV_ENTRY      struct iov_entry
#define IOV_ARITH_TYPE        byte_t *
#define IOV_BUFFER_FUNC(name) iov_buffer_##name
#else /* DEFINE_FOR_IOV_BUFFER */
#define STRUCT_IOV_BUFFER     struct iov_physbuffer
#define STRUCT_IOV_ENTRY      struct iov_physentry
#define IOV_ARITH_TYPE        physaddr_t
#define IOV_BUFFER_FUNC(name) iov_physbuffer_##name
#endif /* !DEFINE_FOR_IOV_BUFFER */


/* Helper functions */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW(KCALL IOV_BUFFER_FUNC(size))(STRUCT_IOV_BUFFER const *__restrict self) {
	size_t i, result;
	result = self->iv_last + self->iv_head.ive_size;
	for (i = 1; i < self->iv_entc - 1; ++i)
		result += self->iv_entv[i].ive_size;
	return result;
}


PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL IOV_BUFFER_FUNC(init_view_before))(STRUCT_IOV_BUFFER *__restrict self,
                                                 STRUCT_IOV_BUFFER const *__restrict base,
                                                 uintptr_t end_offset) {
	size_t i;
	uintptr_t total = 0;
	assert(end_offset != 0);
	self->iv_entv = base->iv_entv;
	self->iv_head = base->iv_head;
	for (i = 0; i < base->iv_entc - 1; ++i) {
		size_t entsize;
		entsize = i ? base->iv_entv[i].ive_size
		            : base->iv_head.ive_size;
		total += entsize;
		if (total >= end_offset) {
			self->iv_entc = i;
			total -= entsize;
			self->iv_last = (size_t)(end_offset - total);
			return;
		}
	}
	assert(total + base->iv_last >= end_offset);
	self->iv_entc = i;
	self->iv_last = end_offset - total;
}

PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL IOV_BUFFER_FUNC(init_view_after))(STRUCT_IOV_BUFFER *__restrict self,
                                                STRUCT_IOV_BUFFER const *__restrict base,
                                                uintptr_t start_offset) {
	self->iv_last = base->iv_last;
	if (start_offset < base->iv_head.ive_size) {
		self->iv_entc         = base->iv_entc;
		self->iv_entv         = base->iv_entv;
		self->iv_head.ive_base = (IOV_ARITH_TYPE)base->iv_head.ive_base + start_offset;
		self->iv_head.ive_size = base->iv_head.ive_size - start_offset;
	} else {
		size_t i;
		start_offset -= base->iv_head.ive_size;
		for (i = 1;; ++i) {
			assert(i < base->iv_entc);
			if (start_offset < base->iv_entv[i].ive_size) {
				self->iv_entc = base->iv_entc - i;
				self->iv_entv = base->iv_entv + i;
				self->iv_head = self->iv_entv[0];
				self->iv_head.ive_base = (IOV_ARITH_TYPE)self->iv_head.ive_base + start_offset;
				self->iv_head.ive_size -= start_offset;
				return;
			}
			start_offset -= base->iv_entv[i].ive_size;
		}
	}
}

PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL IOV_BUFFER_FUNC(init_view))(STRUCT_IOV_BUFFER *__restrict self,
                                          STRUCT_IOV_BUFFER const *__restrict base,
                                          uintptr_t start_offset, size_t num_bytes) {
	size_t i, entc_after_start;
	uintptr_t total;
	assert(num_bytes != 0);
	if (start_offset < base->iv_head.ive_size) {
		entc_after_start       = base->iv_entc;
		self->iv_entv          = base->iv_entv;
		self->iv_head.ive_base = (IOV_ARITH_TYPE)base->iv_head.ive_base + start_offset;
		self->iv_head.ive_size = base->iv_head.ive_size - start_offset;
	} else {
		start_offset -= base->iv_head.ive_size;
		for (i = 1;; ++i) {
			assert(i < base->iv_entc);
			if (start_offset < base->iv_entv[i].ive_size) {
				entc_after_start       = base->iv_entc - i;
				self->iv_entv          = base->iv_entv + i;
				self->iv_head          = self->iv_entv[0];
				self->iv_head.ive_base = (IOV_ARITH_TYPE)self->iv_head.ive_base + start_offset;
				self->iv_head.ive_size -= start_offset;
				return;
			}
			start_offset -= base->iv_entv[i].ive_size;
		}
	}
	total = 0;
	for (i = 0; i < entc_after_start - 1; ++i) {
		size_t entsize;
		entsize = i ? self->iv_entv[i].ive_size
		            : self->iv_head.ive_size;
		total += entsize;
		if (total >= num_bytes) {
			self->iv_entc = i;
			total -= entsize;
			self->iv_last = (size_t)(num_bytes - total);
			return;
		}
	}
	assert(total + base->iv_last >= num_bytes);
	self->iv_entc = i;
	self->iv_last = num_bytes - total;
}

#undef IOV_BUFFER_FUNC
#undef IOV_ARITH_TYPE
#undef STRUCT_IOV_ENTRY
#undef STRUCT_IOV_BUFFER

DECL_END

#undef DEFINE_FOR_IOV_PHYSBUFFER
#undef DEFINE_FOR_IOV_BUFFER
