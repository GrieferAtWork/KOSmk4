/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_AIO_H
#define GUARD_KERNEL_INCLUDE_KERNEL_AIO_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <kernel/except.h>
#include <sched/signal.h>
#include <libc/string.h>
#include <hybrid/__assert.h>
#include <hybrid/typecore.h>

#ifndef CONFIG_NO_SMP
#include <hybrid/sync/atomic-rwlock.h>
#endif /* !CONFIG_NO_SMP */

#ifndef NDEBUG
#include <libc/string.h>
#endif /* !NDEBUG */

DECL_BEGIN

#ifdef __CC__

struct aio_buffer_entry {
	USER CHECKED VIRT void  *ab_base; /* Virtual base address of the target buffer. */
	USER CHECKED VIRT size_t ab_size; /* Number of bytes that should be written at `ab_base' */
};
struct aio_buffer {
	size_t                         ab_entc; /* [!0] Number of entries. */
	struct aio_buffer_entry const *ab_entv; /* [1..ab_entc] Vector of entries. */
	struct aio_buffer_entry        ab_head; /* Override for `ab_entv[0]' */
	size_t                         ab_last; /* Override for `ab_entv[ab_entc - 1].ab_size' */
};
struct aio_pbuffer_entry {
	USER CHECKED VIRT vm_phys_t ab_base; /* Physical base address of the target buffer. */
	USER CHECKED VIRT size_t    ab_size; /* Number of bytes that should be written at `ab_base' */
#if __SIZEOF_VM_PHYS_T__ > __SIZEOF_SIZE_T__
	byte_t ab_pad[__SIZEOF_VM_PHYS_T__ - __SIZEOF_SIZE_T__]; /* ... */
#endif
};
struct aio_pbuffer {
	size_t                          ab_entc; /* [!0] Number of entries. */
	struct aio_pbuffer_entry const *ab_entv; /* [1..ab_entc] Vector of entries. */
	struct aio_pbuffer_entry        ab_head; /* Override for `ab_entv[0]' */
	size_t                          ab_last; /* Override for `ab_entv[ab_entc - 1].ab_size' */
};

/* >> struct aio_buffer_entry ent;
 * >> AIO_BUFFER_FOREACH(ent,buf) {
 * >>     ...
 * >> }
 */
#define AIO_BUFFER_FOREACH(ent,self) \
	for (size_t _abf_i = 0; _abf_i < (self)->ab_entc; ++_abf_i) \
	if (((_abf_i) == 0 \
	   ? (void)((ent) = (self)->ab_head) \
	   : (void)((ent).ab_base = (self)->ab_entv[_abf_i].ab_base, \
	            (ent).ab_size = _abf_i == (self)->ab_entc - 1 ? (self)->ab_last : \
	                                      (self)->ab_entv[_abf_i].ab_size),0)); \
	else
#define AIO_BUFFER_FOREACH_N(ent,self) \
	for (size_t _abf_i = 0;; ++_abf_i) \
	if (((__hybrid_assert(_abf_i < (self)->ab_entc)), \
	     (_abf_i) == 0 \
	   ? (void)((ent) = (self)->ab_head) \
	   : (void)((ent).ab_base = (self)->ab_entv[_abf_i].ab_base, \
	            (ent).ab_size = _abf_i == (self)->ab_entc - 1 ? (self)->ab_last : \
	                                      (self)->ab_entv[_abf_i].ab_size),0)); \
	else
#define AIO_PBUFFER_FOREACH(ent,self) \
        AIO_BUFFER_FOREACH(ent,self)
#define AIO_PBUFFER_FOREACH_N(ent,self) \
        AIO_BUFFER_FOREACH_N(ent,self)


#define AIO_BUFFER_GETENT(result,self,i) \
	((i) == 0 \
	  ? (void)((result) = (self)->ab_head) \
	  : (void)((result).ab_base = (self)->ab_entv[i].ab_base, \
	           (result).ab_size = (i) == (self)->ab_entc - 1 ? (self)->ab_last : \
	                                     (self)->ab_entv[i].ab_size))
#define AIO_PBUFFER_GETENT(result,self,i) \
        AIO_BUFFER_GETENT(result,self,i)


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
LOCAL NOBLOCK WUNUSED NONNULL((1)) size_t
NOTHROW(KCALL aio_buffer_size)(struct aio_buffer const *__restrict self) {
	size_t i, result;
	result = self->ab_last + self->ab_head.ab_size;
	for (i = 1; i < self->ab_entc - 1; ++i)
		result += self->ab_entv[i].ab_size;
	return result;
}

LOCAL NOBLOCK WUNUSED NONNULL((1)) size_t
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



struct aio_handle;
struct aio_handle_stat {
	size_t hs_completed; /* Amount of units (usually bytes) currently completed. */
	size_t hs_total;     /* Total amount of units (usually bytes) that are entailed by the operation. */
};

struct aio_handle_type {
	/* [1..1] Finalizer for this AIO handle. */
	NOBLOCK NONNULL((1)) void /*NOTHROW*/(KCALL *ht_fini)(struct aio_handle *__restrict self);
	/* [1..1] Cancel execution of the given AIO operation.
	 * NOTE: This function is required to _immediatly_ cancel the operation associated
	 *       with the given handle, so long as that operation hasn't yet completed.
	 *       If the first holds true, the associated handle function must be invoked
	 *       with `AIO_COMPLETION_CANCEL' before this operator may return. */
	NOBLOCK NONNULL((1)) void /*NOTHROW*/(KCALL *ht_cancel)(struct aio_handle *__restrict self);
	/* [0..1] An optional operator which can be used to query the operation progress
	 *        in order to determine how much has already been done, and how much is
	 *        still left to be done.
	 * @param: stat: Filled in by this operator.
	 * @return: * :  One of `AIO_PROGRESS_STATUS_*' */
	NOBLOCK NONNULL((1, 2)) unsigned int /*NOTHROW*/(KCALL *ht_progress)(struct aio_handle *__restrict self,
	                                                                     struct aio_handle_stat *__restrict stat);
#define AIO_PROGRESS_STATUS_PENDING    0x0000 /* The operation is still pending execution. */
#define AIO_PROGRESS_STATUS_INPROGRESS 0x0001 /* The operation is currently being performed. */
#define AIO_PROGRESS_STATUS_COMPLETED  0x0002 /* The operation has finished (either due to being canceled, failing, or succeeding)
                                               * Note however that when this value is returned, it is not guarantied whether or
                                               * not the completion function has already been called, or has already returned. */
	/* [0..1] An optional operator for AIO protocols that can consume/produce variable
	 *        amounts of data (e.g. the USB protocol).
	 *        For such cases, this operator returns the actual amount of transferred
	 *        data (in bytes) once AIO operation has completed successfully.
	 *        Calling this operator at any time other than after/during the completion
	 *        function was called with `AIO_COMPLETION_SUCCESS' causes undefined behavior. */
	NOBLOCK WUNUSED NONNULL((1)) size_t /*NOTHROW*/(KCALL *ht_retsize)(struct aio_handle *__restrict self);
};



#define AIO_COMPLETION_SUCCESS  1 /* AIO operation has successfully completed. */
#define AIO_COMPLETION_CANCEL   2 /* AIO operation was canceled manually. */
#define AIO_COMPLETION_FAILURE  3 /* AIO operation has failed.
                                   * When this status is passed, `THIS_EXCEPTION_INFO->ei_data'
                                   * has been filled with more details on what exactly
                                   * has went wrong, at which point it is the callback's
                                   * job to take that information and do with it as it
                                   * pleases (usually propagating it to whoever is waiting
                                   * for the operation to be completed, or to dump it to
                                   * the system log when noone is waiting) */

/* AIO completion callback. Guarantied to always be invoked _exactly_
 * once for each AIO operation started at any point before then.
 * @param: self:   The associated AIO operations handle.
 *                 When this function is invoked, this handle has already been
 *                 unbound from the AIO-capable device's chain of pending AIO
 *                 commands, meaning that this function is also responsible to
 *                 either pass ownership of `self' to some waiter, or to destroy
 *                `self' on its own.
 * @param: status: One of `AIO_COMPLETION_*', explaining how the operation ended. */
typedef NOBLOCK NONNULL((1)) void /*NOTHROW*/(KCALL *aio_completion_t)(struct aio_handle *__restrict self,
                                                                       unsigned int status);

/* Number of pointers available for drivers
 * to store data inline within AIO handles. */
#define AIO_HANDLE_DRIVER_POINTER_COUNT 6
#define AIO_HANDLE_ALIGNMENT __SIZEOF_POINTER__

struct ATTR_ALIGNED(AIO_HANDLE_ALIGNMENT) aio_handle {
#define AIO_HANDLE_HEAD                                                                        \
	struct aio_handle      *ah_next; /* [0..1][lock(INTERNAL)] Pointer to the next AIO handle. \
	                                  * This field is only used internally in order to easily  \
	                                  * chain pending AIO operations */                        \
	struct aio_handle_type *ah_type; /* [1..1][lock(WRITE_ONCE)]                               \
	                                  * AIO usage type (set by a driver implementing AIO       \
	                                  * such that operations can continue even after the       \
	                                  * associated callbacks return). */                       \
	aio_completion_t        ah_func; /* [1..1][const] AIO completion callback. */              \
	void *ah_data[AIO_HANDLE_DRIVER_POINTER_COUNT]; /* Driver/device-specific handle data pointers. */
/**/
	AIO_HANDLE_HEAD
	/* ... Handle-specific data goes here. */
};

/* No-op AIO handle type (intended for synchronous operations) */
DATDEF struct aio_handle_type aio_noop_type;

/* Initialize the given AIO handle with a type-specific v-table. */
#define aio_handle_init(self, type) \
	((self)->ah_type = (type))

/* Finalize a fully initialized AIO handle. */
#define aio_handle_fini(self) (*(self)->ah_type->ht_fini)(self)

/* Cancel execution */
#define aio_handle_cancel(self) (*(self)->ah_type->ht_cancel)(self)

/* Indicate AIO execution completion. */
#define aio_handle_success(self) (*(self)->ah_func)(self, AIO_COMPLETION_SUCCESS)

/* Indicate AIO execution failure due to the currently set exception. */
#define aio_handle_fail(self) (*(self)->ah_func)(self, AIO_COMPLETION_FAILURE)






/* AIO execution order:
 * >> struct aio_handle_generic handle;
 * >> aio_handle_generic_init(&handle);
 * >> // NOTE: Don't put `block_device_aread_sector()' inside of the TRY!
 * >> //       Initialization done by `aio_handle_generic_init()' is only
 * >> //       preliminary, and only the initialization done by actually
 * >> //       using the AIO handle with some the async I/O function will
 * >> //       actually initialize it to the point where it must be
 * >> //       finalized.
 * >> //       If you were to call `aio_handle_generic_fini(...)' on a
 * >> //       handle that hasn't actually be used with any sort of async
 * >> //       I/O function, you'd end up with undefined behavior!
 * >> block_device_aread_sector(dev, phys_dest, virt_dest, 2, 0, &handle);
 * >> TRY {
 * >>     aio_handle_generic_waitfor(&handle);
 * >>     aio_handle_generic_checkerror(&handle);
 * >> } EXCEPT {
 * >>     aio_handle_generic_fini(&handle);
 * >>     RETHROW();
 * >> }
 * >> aio_handle_generic_fini(&handle);
 */

/* A general purpose AIO handle that can be used for synchronizing for completion. */
struct ATTR_ALIGNED(AIO_HANDLE_ALIGNMENT) aio_handle_generic
#ifdef __cplusplus
	: aio_handle
#endif
{
#ifndef __cplusplus
	AIO_HANDLE_HEAD
#endif
	struct sig            hg_signal; /* Signal broadcast when `ah_func' is called. */
	unsigned int          hg_status; /* Acknowledged AIO completion status (or 0 if still in progress) */
	struct exception_data hg_error;  /* [valid_if(hg_status == AIO_COMPLETION_FAILURE)] AIO failure error. */
};

#define aio_handle_generic_fini(self) aio_handle_fini(self)

/* Callback for `aio_handle_generic' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_handle_generic_func)(struct aio_handle *__restrict self,
                                       unsigned int status);

LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_handle_generic_init)(struct aio_handle_generic *__restrict self) {
#ifndef NDEBUG
	__libc_memset(self, 0xcc, sizeof(*self));
#endif /* !NDEBUG */
	self->ah_func   = &aio_handle_generic_func;
	self->hg_status = 0;
	sig_init(&self->hg_signal);
}

#define aio_handle_generic_hascompleted(self) \
	(__hybrid_atomic_load((self)->hg_status,__ATOMIC_ACQUIRE) != 0)

/* Check if the AIO operation failed, and propagate the error if it did. */
LOCAL NONNULL((1)) void KCALL
aio_handle_generic_checkerror(struct aio_handle_generic *__restrict self)
		THROWS(E_IOERROR, ...) {
	if unlikely(self->hg_status == AIO_COMPLETION_FAILURE) {
		__libc_memcpy(&THIS_EXCEPTION_INFO.ei_data,
		              &self->hg_error, sizeof(self->hg_error));
		error_throw_current();
	}
}

/* Connect to the given AIO handle. */
LOCAL NONNULL((1)) void KCALL
aio_handle_generic_connect(struct aio_handle_generic *__restrict self)
		THROWS(E_BADALLOC) {
	task_connect(&self->hg_signal);
}

LOCAL NONNULL((1)) void KCALL
aio_handle_generic_connect_ghost(struct aio_handle_generic *__restrict self)
		THROWS(E_BADALLOC) {
	task_connect_ghost(&self->hg_signal);
}

LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL aio_handle_generic_connect_c)(struct task_connection *__restrict con,
                                            struct aio_handle_generic *__restrict self) {
	task_connect_c(con, &self->hg_signal);
}

LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL aio_handle_generic_connect_ghost_c)(struct task_connection *__restrict con,
                                                  struct aio_handle_generic *__restrict self) {
	task_connect_ghost_c(con, &self->hg_signal);
}

LOCAL NONNULL((1)) void KCALL
aio_handle_generic_waitfor(struct aio_handle_generic *__restrict self)
		THROWS(E_WOULDBLOCK, ...) {
	__hybrid_assert(!task_isconnected());
	while (!aio_handle_generic_hascompleted(self)) {
		TRY {
			task_connect(&self->hg_signal);
			if unlikely(aio_handle_generic_hascompleted(self)) {
				task_disconnectall();
				break;
			}
			task_waitfor();
		} EXCEPT {
			aio_handle_cancel(self);
			RETHROW();
		}
	}
}




struct aio_multihandle;
struct ATTR_ALIGNED(AIO_HANDLE_ALIGNMENT) aio_handle_multiple
#ifdef __cplusplus
	: aio_handle
#endif /* __cplusplus */
{
#ifndef __cplusplus
	AIO_HANDLE_HEAD
#endif /* __cplusplus */
#define AIO_HANDLE_MULTIPLE_CONTROLLER_UNUSED_IS_ZERO 1
#define AIO_HANDLE_MULTIPLE_CONTROLLER_UNUSED   ((struct aio_multihandle *)0)  /* Unused entry */
#define AIO_HANDLE_MULTIPLE_CONTROLLER_COMPLETE ((struct aio_multihandle *)-1) /* Completed/Cancelled entry */
	struct aio_multihandle *hg_controller; /* [0..1][lock(WRITE_ONCE(AIO_HANDLE_MULTIPLE_CONTROLLER_COMPLETE))]
	                                        * Associated controller. Set to `AIO_HANDLE_MULTIPLE_CONTROLLER_COMPLETE'
	                                        * after this handle's operation has completed. */
};

/* Callback for `aio_handle_multiple' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_handle_multiple_func)(struct aio_handle *__restrict self,
                                        unsigned int status);

/* Callback for `aio_multihandle' (called under the same context as `aio_completion_t') */
typedef NOBLOCK NONNULL((1)) void
/*NOTHROW*/(KCALL *aio_multiple_completion_t)(struct aio_multihandle *__restrict self,
                                              unsigned int status);
#define AIO_MULTIHANDLE_IVECLIMIT  2    /* Max number of inline-allocated handles. */
#define AIO_MULTIHANDLE_XVECLIMIT  8    /* Max number of heap-allocated handles per extension. */

#define AIO_MULTIHANDLE_STATUS_FAILED     0x40000000 /* FLAG: Set once if an operation unrelated to I/O failed. */
#define AIO_MULTIHANDLE_STATUS_ALLRUNNING 0x80000000 /* FLAG: Set once all commands have been issued. */
#define AIO_MULTIHANDLE_STATUS_STATUSMASK 0x0f000000 /* Mask for the most significant run status. */
#define AIO_MULTIHANDLE_STATUS_STATUSSHFT 24         /* Shift for the most significant run status. */
#define AIO_MULTIHANDLE_STATUS_RUNMASK    0x00ffffff /* Mask for the number of running handles. */


struct aio_multihandle_extension {
	struct aio_multihandle_extension *ame_next; /* [0..1][owned] Next extension. */
	struct aio_handle_multiple        ame_handles[AIO_MULTIHANDLE_XVECLIMIT]; /* Associated handles. */
};

struct aio_multihandle {
	aio_multiple_completion_t  am_func;    /* [1..1][const] AIO completion callback. */
	WEAK uintptr_t             am_status;  /* Set of `AIO_MULTIHANDLE_STATUS_*'. */
	struct exception_data      am_error;   /* [lock(WRITE_ONCE)] AIO failure error. */
	struct aio_multihandle_extension
	                          *am_ext;     /* [0..1][owned] Vector of additional, heap-allocated handles. */
	struct aio_handle_multiple am_ivec[AIO_MULTIHANDLE_IVECLIMIT];
	                                       /* Small inline vector for the first couple of handles. */
	/* ... Additional data can go here. */
};

/* Initialize the given AIO multi-handle */
LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL aio_multihandle_init)(struct aio_multihandle *__restrict self,
                                    aio_multiple_completion_t func) {
	unsigned int i;
#ifndef NDEBUG
	__libc_memset(&self->am_error, 0xcc, sizeof(self->am_error));
	__libc_memset(self->am_ivec, 0xcc, sizeof(self->am_ivec));
#endif /* !NDEBUG */
	self->am_func   = func;
	self->am_status = (uintptr_t)AIO_COMPLETION_SUCCESS << AIO_MULTIHANDLE_STATUS_STATUSSHFT;
	self->am_ext    = __NULLPTR;
	for (i = 0; i < AIO_MULTIHANDLE_IVECLIMIT; ++i)
		self->am_ivec[i].hg_controller = AIO_HANDLE_MULTIPLE_CONTROLLER_UNUSED;
}

/* Finalize the given AIO multi-handle */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_fini)(struct aio_multihandle *__restrict self);


/* Handle the current exception using the given AIO multi-handle.
 * NOTE: This function will also call `aio_multihandle_cancel()' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_fail)(struct aio_multihandle *__restrict self);

/* Allocate handles for the purpose of AIO completion.
 * WARNING: Don't free a handle after you already started using it in the context of an AIO parameter.
 * NOTE: `aio_multihandle_allochandle()' calls `aio_multihandle_fail()' upon
 *       error, before returning propagating an error / returning `NULL'. */
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) struct aio_handle *KCALL
aio_multihandle_allochandle(struct aio_multihandle *__restrict self)
		THROWS(E_BADALLOC);
FUNDEF WUNUSED NONNULL((1)) struct aio_handle *
NOTHROW(KCALL aio_multihandle_allochandle_nx)(struct aio_multihandle *__restrict self);

/* Cancel all currently running handles of `self' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_cancel)(struct aio_multihandle *__restrict self);

/* Indicate that no further handles will be allocated, meaning that `self->am_func'
 * is now allowed to be called once all initiated operations have finished (which
 * may be immediately).
 * WARNING: This function should not be called more than once! */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_done)(struct aio_multihandle *__restrict self);



/* AIO multihandle syncing execution order:
 * >> struct aio_multihandle_generic multihandle;
 * >> aio_multihandle_generic_init(&multihandle);
 * >> TRY {
 * >>     block_device_aread_sector(dev, dst1, 2, 0, aio_multihandle_allochandle(&multihandle));
 * >>     block_device_aread_sector(dev, dst2, 2, 8, aio_multihandle_allochandle(&multihandle));
 * >> } EXCEPT {
 * >>     aio_multihandle_fail(&multihandle);
 * >> }
 * >> aio_multihandle_done(&multihandle);
 * >> TRY {
 * >>     aio_multihandle_generic_waitfor(&multihandle);
 * >>     aio_multihandle_generic_checkerror(&multihandle);
 * >> } EXCEPT {
 * >>     aio_multihandle_generic_fini(&multihandle);
 * >>     RETHROW();
 * >> }
 * >> aio_multihandle_generic_fini(&multihandle);
 */

/* Generic multi-handle that is capable of being used as a signal source.
 * This is to `aio_multihandle' the same that `aio_handle_generic' is to `aio_handle' */
struct aio_multihandle_generic
#ifdef __cplusplus
	: aio_multihandle
#endif
{
#ifndef __cplusplus
	struct aio_multihandle mg_base;   /* The underlying multi-handle. */
#endif
	struct sig             mg_signal; /* Signal broadcast upon completion. */
};

FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_generic_func)(struct aio_multihandle *__restrict self,
                                            unsigned int status);

LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_generic_init)(struct aio_multihandle_generic *__restrict self) {
	aio_multihandle_init(self, &aio_multihandle_generic_func);
	sig_init(&self->mg_signal);
}

#define aio_multihandle_generic_fini(self) \
	aio_multihandle_fini(self)

/* NOTE: Returns `false' if `aio_multihandle_done' hasn't been called, yet. */
#define aio_multihandle_generic_hascompleted(self)                                                 \
	(((self)->am_status & (AIO_MULTIHANDLE_STATUS_ALLRUNNING | AIO_MULTIHANDLE_STATUS_RUNMASK)) == \
	                       AIO_MULTIHANDLE_STATUS_ALLRUNNING)

/* Check if the AIO operation failed, and propagate the error if it did. */
LOCAL NONNULL((1)) void KCALL
aio_multimultihandle_generic_checkerror(struct aio_multihandle_generic *__restrict self)
		THROWS(E_IOERROR, ...) {
	if unlikely((self->am_status & ~(AIO_MULTIHANDLE_STATUS_ALLRUNNING | AIO_MULTIHANDLE_STATUS_FAILED)) == AIO_COMPLETION_FAILURE) {
		__libc_memcpy(&THIS_EXCEPTION_INFO.ei_data,
		              &self->am_error, sizeof(self->am_error));
		error_throw_current();
	}
}

/* Connect to the given AIO multihandle. */
LOCAL NONNULL((1)) void KCALL
aio_multihandle_generic_connect(struct aio_multihandle_generic *__restrict self)
		THROWS(E_BADALLOC) {
	task_connect(&self->mg_signal);
}
LOCAL NONNULL((1)) void KCALL
aio_multihandle_generic_connect_ghost(struct aio_multihandle_generic *__restrict self)
		THROWS(E_BADALLOC) {
	task_connect_ghost(&self->mg_signal);
}
LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL aio_multihandle_generic_connect_c)(struct task_connection *__restrict con,
                                                 struct aio_multihandle_generic *__restrict self) {
	task_connect_c(con, &self->mg_signal);
}
LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL aio_multihandle_generic_connect_ghost_c)(struct task_connection *__restrict con,
                                                       struct aio_multihandle_generic *__restrict self) {
	task_connect_ghost_c(con, &self->mg_signal);
}

/* Check if the AIO operation failed, and propagate the error if it did. */
LOCAL NONNULL((1)) void KCALL
aio_multihandle_generic_checkerror(struct aio_multihandle_generic *__restrict self)
		THROWS(E_IOERROR, ...) {
	if unlikely((self->am_status & AIO_MULTIHANDLE_STATUS_STATUSMASK) ==
	           ((uintptr_t)AIO_COMPLETION_FAILURE << AIO_MULTIHANDLE_STATUS_STATUSSHFT)) {
		__libc_memcpy(&THIS_EXCEPTION_INFO.ei_data, &self->am_error, sizeof(self->am_error));
		error_throw_current();
	}
}

LOCAL NONNULL((1)) void KCALL
aio_multihandle_generic_waitfor(struct aio_multihandle_generic *__restrict self)
		THROWS(E_WOULDBLOCK, ...) {
	__hybrid_assert(!task_isconnected());
	while (!aio_multihandle_generic_hascompleted(self)) {
		TRY {
			task_connect(&self->mg_signal);
			if unlikely(aio_multihandle_generic_hascompleted(self)) {
				task_disconnectall();
				break;
			}
			task_waitfor();
		} EXCEPT {
			aio_multihandle_cancel(self);
			RETHROW();
		}
	}
}

#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_AIO_H */
