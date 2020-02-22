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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_IOVEC_H
#define GUARD_KERNEL_INCLUDE_KERNEL_IOVEC_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/__assert.h>

#ifndef __INTELLISENSE__
#include <libc/string.h>
#endif /* !__INTELLISENSE__ */

DECL_BEGIN

#ifdef __CC__

#ifndef __aio_buffer_entry_defined
#define __aio_buffer_entry_defined 1
struct aio_buffer_entry {
	USER CHECKED void *ab_base; /* [?..ab_size] Virtual base address of the buffer. */
	size_t             ab_size; /* Buffer size of `ab_base' (in bytes) */
};
#endif /* !__aio_buffer_entry_defined */

struct aio_buffer {
	size_t                         ab_entc; /* [!0] Number of entries. */
	struct aio_buffer_entry const *ab_entv; /* [1..ab_entc] Vector of entries. */
	struct aio_buffer_entry        ab_head; /* Override for `ab_entv[0]' */
	size_t                         ab_last; /* Override for `ab_entv[ab_entc - 1].ab_size' */
};

struct aio_pbuffer_entry {
	vm_phys_t ab_base; /* [?..ab_size] Physical base address of the target buffer. */
#if __SIZEOF_VM_PHYS_T__ > __SIZEOF_SIZE_T__
	byte_t    ab_pad[__SIZEOF_VM_PHYS_T__ - __SIZEOF_SIZE_T__]; /* ... */
#endif /* __SIZEOF_VM_PHYS_T__ > __SIZEOF_SIZE_T__ */
	size_t    ab_size; /* Number of bytes that should be written at `ab_base' */
};

struct aio_pbuffer {
	size_t                          ab_entc; /* [!0] Number of entries. */
	struct aio_pbuffer_entry const *ab_entv; /* [1..ab_entc] Vector of entries. */
	struct aio_pbuffer_entry        ab_head; /* Override for `ab_entv[0]' */
	size_t                          ab_last; /* Override for `ab_entv[ab_entc - 1].ab_size' */
};

/* >> struct aio_buffer_entry ent;
 * >> AIO_BUFFER_FOREACH(ent, buf) {
 * >>     ...
 * >> }
 */
#define AIO_BUFFER_FOREACH(ent, self)                                     \
	for (size_t _abf_i = 0; _abf_i < (self)->ab_entc; ++_abf_i)           \
		if (((_abf_i) == 0                                                \
		     ? (void)((ent) = (self)->ab_head)                            \
		     : (void)((ent).ab_base = (self)->ab_entv[_abf_i].ab_base,    \
		              (ent).ab_size = _abf_i == (self)->ab_entc - 1       \
		                              ? (self)->ab_last                   \
		                              : (self)->ab_entv[_abf_i].ab_size), \
		     0))                                                          \
			;                                                             \
		else
#define AIO_BUFFER_FOREACH_N(ent, self)                                   \
	for (size_t _abf_i = 0;; ++_abf_i)                                    \
		if (((__hybrid_assert(_abf_i < (self)->ab_entc)),                 \
		     (_abf_i) == 0                                                \
		     ? (void)((ent) = (self)->ab_head)                            \
		     : (void)((ent).ab_base = (self)->ab_entv[_abf_i].ab_base,    \
		              (ent).ab_size = _abf_i == (self)->ab_entc - 1       \
		                              ? (self)->ab_last                   \
		                              : (self)->ab_entv[_abf_i].ab_size), \
		     0))                                                          \
			;                                                             \
		else
#define AIO_PBUFFER_FOREACH(ent, self) \
	AIO_BUFFER_FOREACH(ent, self)
#define AIO_PBUFFER_FOREACH_N(ent, self) \
	AIO_BUFFER_FOREACH_N(ent, self)


#define AIO_BUFFER_GETENT(result, self, i)                   \
	((i) == 0                                                \
	 ? (void)((result) = (self)->ab_head)                    \
	 : (void)((result).ab_base = (self)->ab_entv[i].ab_base, \
	          (result).ab_size = (i) == (self)->ab_entc - 1  \
	                             ? (self)->ab_last           \
	                             : (self)->ab_entv[i].ab_size))
#define AIO_PBUFFER_GETENT(result, self, i) \
	AIO_BUFFER_GETENT(result, self, i)


/* Determine the number of bytes inside of the given buffer. */
LOCAL NOBLOCK WUNUSED NONNULL((1)) size_t NOTHROW(KCALL aio_buffer_size)(struct aio_buffer const *__restrict self);
LOCAL NOBLOCK WUNUSED NONNULL((1)) size_t NOTHROW(KCALL aio_pbuffer_size)(struct aio_pbuffer const *__restrict self);

/* Initialize a given AIO buffer as a view of memory of another. */
LOCAL NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL aio_buffer_init_view_before)(struct aio_buffer *__restrict self, struct aio_buffer const *__restrict base, uintptr_t end_offset);
LOCAL NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL aio_pbuffer_init_view_before)(struct aio_pbuffer *__restrict self, struct aio_pbuffer const *__restrict base, uintptr_t end_offset);
LOCAL NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL aio_buffer_init_view_after)(struct aio_buffer *__restrict self, struct aio_buffer const *__restrict base, uintptr_t start_offset);
LOCAL NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL aio_pbuffer_init_view_after)(struct aio_pbuffer *__restrict self, struct aio_pbuffer const *__restrict base, uintptr_t start_offset);
LOCAL NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL aio_buffer_init_view)(struct aio_buffer *__restrict self, struct aio_buffer const *__restrict base, uintptr_t start_offset, size_t num_bytes);
LOCAL NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL aio_pbuffer_init_view)(struct aio_pbuffer *__restrict self, struct aio_pbuffer const *__restrict base, uintptr_t start_offset, size_t num_bytes);

/* Read/write/set data associated with AIO buffers. */
LOCAL NONNULL((1)) void KCALL aio_buffer_memset(struct aio_buffer const *__restrict self, uintptr_t dst_offset, int byte, size_t num_bytes) THROWS(E_SEGFAULT);
LOCAL NONNULL((1)) void KCALL aio_buffer_copyfrommem(struct aio_buffer const *__restrict self, uintptr_t dst_offset, USER CHECKED void const *__restrict src, size_t num_bytes) THROWS(E_SEGFAULT);
LOCAL NONNULL((1)) void KCALL aio_buffer_copytomem(struct aio_buffer const *__restrict self, USER CHECKED void *__restrict dst, uintptr_t src_offset, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) void KCALL aio_buffer_copyfromphys(struct aio_buffer const *__restrict self, uintptr_t dst_offset, vm_phys_t src, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) void KCALL aio_buffer_copytophys(struct aio_buffer const *__restrict self, vm_phys_t dst, uintptr_t src_offset, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) void KCALL aio_buffer_copytovphys(struct aio_buffer const *__restrict src, struct aio_pbuffer const *__restrict dst, uintptr_t dst_offset, uintptr_t src_offset, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL aio_pbuffer_memset)(struct aio_pbuffer const *__restrict self, uintptr_t dst_offset, int byte, size_t num_bytes);
FUNDEF NONNULL((1)) void KCALL aio_pbuffer_copyfrommem(struct aio_pbuffer const *__restrict self, uintptr_t dst_offset, USER CHECKED void const *src, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) void KCALL aio_pbuffer_copytomem(struct aio_pbuffer const *__restrict self, USER CHECKED void *dst, uintptr_t src_offset, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) void KCALL aio_pbuffer_copytovmem(struct aio_pbuffer const *__restrict src, struct aio_buffer const *__restrict dst, uintptr_t dst_offset, uintptr_t src_offset, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL aio_pbuffer_copyfromphys)(struct aio_pbuffer const *__restrict self, uintptr_t dst_offset, vm_phys_t src, size_t num_bytes);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL aio_pbuffer_copytophys)(struct aio_pbuffer const *__restrict self, vm_phys_t dst, uintptr_t src_offset, size_t num_bytes);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL aio_pbuffer_copytovphys)(struct aio_pbuffer const *__restrict src, struct aio_pbuffer const *__restrict dst, uintptr_t dst_offset, uintptr_t src_offset, size_t num_bytes);


#ifndef __INTELLISENSE__
LOCAL NOBLOCK WUNUSED ATTR_PURE NONNULL((1)) size_t
NOTHROW(KCALL aio_buffer_size)(struct aio_buffer const *__restrict self) {
	size_t i, result;
	result = self->ab_last + self->ab_head.ab_size;
	for (i = 1; i < self->ab_entc - 1; ++i)
		result += self->ab_entv[i].ab_size;
	return result;
}

LOCAL NOBLOCK WUNUSED ATTR_PURE NONNULL((1)) size_t
NOTHROW(KCALL aio_pbuffer_size)(struct aio_pbuffer const *__restrict self) {
	size_t i, result;
	result = self->ab_last + self->ab_head.ab_size;
	for (i = 1; i < self->ab_entc - 1; ++i)
		result += self->ab_entv[i].ab_size;
	return result;
}


LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL aio_buffer_init_view_before)(struct aio_buffer *__restrict self,
                                           struct aio_buffer const *__restrict base,
                                           uintptr_t end_offset) {
	size_t i;
	uintptr_t total = 0;
	__hybrid_assert(end_offset != 0);
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
	__hybrid_assert(total + base->ab_last >= end_offset);
	self->ab_entc = i;
	self->ab_last = end_offset - total;
}

LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL aio_pbuffer_init_view_before)(struct aio_pbuffer *__restrict self,
                                            struct aio_pbuffer const *__restrict base,
                                            uintptr_t end_offset) {
	size_t i;
	uintptr_t total = 0;
	__hybrid_assert(end_offset != 0);
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
	__hybrid_assert(total + base->ab_last >= end_offset);
	self->ab_entc = i;
	self->ab_last = end_offset - total;
}

LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL aio_buffer_init_view_after)(struct aio_buffer *__restrict self,
                                          struct aio_buffer const *__restrict base,
                                          uintptr_t start_offset) {
	self->ab_last = base->ab_last;
	if (start_offset < base->ab_head.ab_size) {
		self->ab_entc         = base->ab_entc;
		self->ab_entv         = base->ab_entv;
		self->ab_head.ab_base = (byte_t *)base->ab_head.ab_base + start_offset;
		self->ab_head.ab_size = base->ab_head.ab_size - start_offset;
	} else {
		size_t i;
		start_offset -= base->ab_head.ab_size;
		for (i = 1;; ++i) {
			__hybrid_assert(i < base->ab_entc);
			if (start_offset < base->ab_entv[i].ab_size) {
				self->ab_entc         = base->ab_entc - i;
				self->ab_entv         = base->ab_entv + i;
				self->ab_head         = self->ab_entv[0];
				self->ab_head.ab_base = (byte_t *)self->ab_head.ab_base + start_offset;
				self->ab_head.ab_size -= start_offset;
				return;
			}
			start_offset -= base->ab_entv[i].ab_size;
		}
	}
}

LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL aio_pbuffer_init_view_after)(struct aio_pbuffer *__restrict self,
                                           struct aio_pbuffer const *__restrict base,
                                           uintptr_t start_offset) {
	self->ab_last = base->ab_last;
	if (start_offset < base->ab_head.ab_size) {
		self->ab_entc         = base->ab_entc;
		self->ab_entv         = base->ab_entv;
		self->ab_head.ab_base = base->ab_head.ab_base + start_offset;
		self->ab_head.ab_size = base->ab_head.ab_size - start_offset;
	} else {
		size_t i;
		start_offset -= base->ab_head.ab_size;
		for (i = 1;; ++i) {
			__hybrid_assert(i < base->ab_entc);
			if (start_offset < base->ab_entv[i].ab_size) {
				self->ab_entc = base->ab_entc - i;
				self->ab_entv = base->ab_entv + i;
				self->ab_head = self->ab_entv[0];
				self->ab_head.ab_base += start_offset;
				self->ab_head.ab_size -= start_offset;
				return;
			}
			start_offset -= base->ab_entv[i].ab_size;
		}
	}
}

LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL aio_buffer_init_view)(struct aio_buffer *__restrict self,
                                    struct aio_buffer const *__restrict base,
                                    uintptr_t start_offset, size_t num_bytes) {
	size_t i, entc_after_start;
	uintptr_t total;
	__hybrid_assert(num_bytes != 0);
	if (start_offset < base->ab_head.ab_size) {
		entc_after_start      = base->ab_entc;
		self->ab_entv         = base->ab_entv;
		self->ab_head.ab_base = (byte_t *)base->ab_head.ab_base + start_offset;
		self->ab_head.ab_size = base->ab_head.ab_size - start_offset;
	} else {
		start_offset -= base->ab_head.ab_size;
		for (i = 1;; ++i) {
			__hybrid_assert(i < base->ab_entc);
			if (start_offset < base->ab_entv[i].ab_size) {
				entc_after_start      = base->ab_entc - i;
				self->ab_entv         = base->ab_entv + i;
				self->ab_head         = self->ab_entv[0];
				self->ab_head.ab_base = (byte_t *)self->ab_head.ab_base + start_offset;
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
	__hybrid_assert(total + base->ab_last >= num_bytes);
	self->ab_entc = i;
	self->ab_last = num_bytes - total;
}

LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL aio_pbuffer_init_view)(struct aio_pbuffer *__restrict self,
                                     struct aio_pbuffer const *__restrict base,
                                     uintptr_t start_offset, size_t num_bytes) {
	size_t i, entc_after_start;
	uintptr_t total;
	__hybrid_assert(num_bytes != 0);
	if (start_offset < base->ab_head.ab_size) {
		entc_after_start      = base->ab_entc;
		self->ab_entv         = base->ab_entv;
		self->ab_head.ab_base = base->ab_head.ab_base + start_offset;
		self->ab_head.ab_size = base->ab_head.ab_size - start_offset;
	} else {
		start_offset -= base->ab_head.ab_size;
		for (i = 1;; ++i) {
			__hybrid_assert(i < base->ab_entc);
			if (start_offset < base->ab_entv[i].ab_size) {
				entc_after_start = base->ab_entc - i;
				self->ab_entv    = base->ab_entv + i;
				self->ab_head    = self->ab_entv[0];
				self->ab_head.ab_base += start_offset;
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
	__hybrid_assert(total + base->ab_last >= num_bytes);
	self->ab_entc = i;
	self->ab_last = num_bytes - total;
}


LOCAL NONNULL((1)) void KCALL
aio_buffer_memset(struct aio_buffer const *__restrict self,
                  uintptr_t dst_offset,
                  int byte, size_t num_bytes)
		THROWS(E_SEGFAULT) {
	struct aio_buffer_entry ent;
	AIO_BUFFER_FOREACH_N(ent, self) {
		if (dst_offset >= ent.ab_size) {
			dst_offset -= ent.ab_size;
			continue;
		}
		if (ent.ab_size > num_bytes)
			ent.ab_size = num_bytes;
		__libc_memset((byte_t *)ent.ab_base + dst_offset, byte, ent.ab_size);
		if (ent.ab_size >= num_bytes)
			break;
		num_bytes -= ent.ab_size;
		dst_offset = 0;
	}
}

LOCAL NONNULL((1)) void KCALL
aio_buffer_copyfrommem(struct aio_buffer const *__restrict self, uintptr_t dst_offset,
                       USER CHECKED void const *__restrict src, size_t num_bytes)
		THROWS(E_SEGFAULT) {
	struct aio_buffer_entry ent;
	AIO_BUFFER_FOREACH_N(ent, self) {
		if (dst_offset >= ent.ab_size) {
			dst_offset -= ent.ab_size;
			continue;
		}
		if (ent.ab_size > num_bytes)
			ent.ab_size = num_bytes;
		__libc_memcpy((byte_t *)ent.ab_base + dst_offset, src, ent.ab_size);
		if (ent.ab_size >= num_bytes)
			break;
		src = (byte_t *)src + ent.ab_size;
		num_bytes -= ent.ab_size;
		dst_offset = 0;
	}
}
LOCAL NONNULL((1)) void KCALL
aio_buffer_copytomem(struct aio_buffer const *__restrict self,
                     USER CHECKED void *__restrict dst,
                     uintptr_t src_offset, size_t num_bytes)
		THROWS(E_SEGFAULT) {
	struct aio_buffer_entry ent;
	AIO_BUFFER_FOREACH_N(ent, self) {
		if (src_offset >= ent.ab_size) {
			src_offset -= ent.ab_size;
			continue;
		}
		if (ent.ab_size > num_bytes)
			ent.ab_size = num_bytes;
		__libc_memcpy(dst, (byte_t *)ent.ab_base + src_offset, ent.ab_size);
		if (ent.ab_size >= num_bytes)
			break;
		dst = (byte_t *)dst + ent.ab_size;
		num_bytes -= ent.ab_size;
		src_offset = 0;
	}
}
#endif /* !__INTELLISENSE__ */


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_IOVEC_H */
