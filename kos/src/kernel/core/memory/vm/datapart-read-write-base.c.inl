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
#include "datapart-read-write.c"
//#define DEFINE_IO_READ 1
#define DEFINE_IO_WRITE 1
//#define DEFINE_IO_PHYS 1
#define DEFINE_IO_NOPF 1
#endif

#include <kernel/except.h>
#include <kernel/vm/phys.h>

#include <limits.h> /* SSIZE_MAX */

DECL_BEGIN

#if defined(DEFINE_IO_READ) && defined(DEFINE_IO_PHYS)
#define FUNC0(x) x##read_phys
#elif defined(DEFINE_IO_READ) && defined(DEFINE_IO_NOPF)
#define FUNC0(x) x##read_nopf
#elif defined(DEFINE_IO_READ)
#define FUNC0(x) x##read
#elif defined(DEFINE_IO_PHYS)
#define FUNC0(x) x##write_phys
#elif defined(DEFINE_IO_NOPF)
#define FUNC0(x) x##write_nopf
#else
#define FUNC0(x) x##write
#endif

#ifdef DEFINE_IO_READ
#define IFELSE_RW(ifr, ifw) ifr
#else /* DEFINE_IO_READ */
#define IFELSE_RW(ifr, ifw) ifw
#endif /* !DEFINE_IO_READ */


/* Directly copy memory to/from the given buffer and `self'
 * NOTE: These functions automatically deal with page properties, such
 *       that `vm_datapart_do_read()' will ensure INITIALIZED pages, whilst
 *       `vm_datapart_do_write()' ensures HASCHANGED pages (so-long as the
 *       TRACKCHANGES bit is set)
 * NOTE: The caller must be holding a read-lock to `self', as well as ensure
 *       that `self' is either INCORE or LOCKED */
#ifdef DEFINE_IO_NOPF
PUBLIC NONNULL((1)) size_t KCALL
#else /* DEFINE_IO_NOPF */
PUBLIC NONNULL((1)) void KCALL
#endif /* !DEFINE_IO_NOPF */
FUNC0(vm_datapart_do_)(struct vm_datapart *__restrict self,
#ifdef DEFINE_IO_PHYS
                       physaddr_t buf,
#elif defined(DEFINE_IO_READ)
                       USER CHECKED void *buf,
#else
                       USER CHECKED void const *buf,
#endif
                       size_t num_bytes,
                       size_t offset)
#ifdef DEFINE_IO_PHYS
		THROWS(...)
#else /* DEFINE_IO_PHYS */
		THROWS(E_SEGFAULT, ...)
#endif /* !DEFINE_IO_PHYS */
{
	size_t data_pagesize;
	assert(sync_reading(self) || !isshared(self) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1));
	assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
	       self->dp_state == VM_DATAPART_STATE_LOCKED);
	data_pagesize = VM_DATABLOCK_PAGESIZE(self->dp_block);
	if likely(num_bytes) {
		for (;;) {
#ifdef DEFINE_IO_NOPF
			size_t transferr_error;
#endif /* DEFINE_IO_NOPF */
			size_t max_io, page_offset;
			physaddr_t data_base;
			page_offset = (size_t)(offset & (data_pagesize - 1));
			max_io      = data_pagesize - page_offset;
			if (max_io > num_bytes)
				max_io = num_bytes;
			data_base = vm_datapart_loaddatapage(self,
			                                     offset >> VM_DATABLOCK_ADDRSHIFT(self->dp_block),
			                                     IFELSE_RW(false, true));
			/* Copy data to/from the data part memory back-end */
#ifdef DEFINE_IO_PHYS
			IFELSE_RW(vm_copyinphys(buf, (physaddr_t)(data_base + page_offset), max_io),
			          vm_copyinphys((physaddr_t)(data_base + page_offset), buf, max_io));
#elif defined(DEFINE_IO_NOPF)
			transferr_error = IFELSE_RW(vm_copyfromphys_nopf(buf, (physaddr_t)(data_base + page_offset), max_io),
			                            vm_copytophys_nopf((physaddr_t)(data_base + page_offset), buf, max_io));
			/* Check if the data transfer failed. */
			if unlikely(transferr_error != 0) {
				size_t transfer_ok;
				/* Figure out how many bytes could be transferred. */
				assert(transferr_error <= max_io);
				transfer_ok = max_io - transferr_error;
				/* Figure out how many bytes still haven't been transferred. */
				assert(transfer_ok < num_bytes);
				return num_bytes - transfer_ok;
			}
#else /* ... */
			IFELSE_RW(vm_copyfromphys(buf, (physaddr_t)(data_base + page_offset), max_io),
			          vm_copytophys((physaddr_t)(data_base + page_offset), buf, max_io));
#endif /* !... */
			if (max_io >= num_bytes)
				break;
			num_bytes -= max_io;
			offset += max_io;
#ifdef DEFINE_IO_PHYS
			buf += max_io;
#else /* DEFINE_IO_PHYS */
			buf = (byte_t *)buf + max_io;
#endif /* !DEFINE_IO_PHYS */
		}
	}
#ifdef DEFINE_IO_NOPF
	return 0;
#endif /* DEFINE_IO_NOPF */
}



#if defined(DEFINE_IO_NOPF)
/* Read/Write memory to/from the given data part without causing a #PF due
 * to access made to the given `dst'/`src' buffers (s.a. `memcpy_nopf()').
 * @assume(num_bytes <= SSIZE_MAX);
 * @return: >= 0:
 *     Successfully transferred all possible data in regards to the actual size
 *     of `self' encountered when the lock associated with it was held. This may
 *     be less than num_bytes' in case the data part ended up being smaller that
 *     the given buffer, where it should be noted that a data part can shrink at
 *     any time that its lock isn't being held due to possibly getting split by
 *     another thread.
 * @return: < 0:
 *     Failed to read/write the last `-return' bytes of the given buffer,
 *     as accessing them triggers a #PF for the range:
 *         `(dst|src) + (num_bytes - (size_t)(-return)) ... (dst|src) + num_bytes - 1'
 *     As such, the first `num_bytes - (size_t)(-return)' bytes were successfully
 *     read/written, and the caller should not attempt to read/write them again, but
 *     should instead manually read/write at least 1 byte starting at:
 *         `((byte_t *)(dst|src))[num_bytes - (size_t)(-return)]'
 *     using a temporary buffer, in order to allow the associated memory mapping to
 *     be faulted while not holding any locks to VM control structures, also allowing
 *     for the proper handling in case the memory associated with `dst'/`src' is backed
 *     by a VIO memory mapping. */
PUBLIC NONNULL((1, 2)) ssize_t KCALL
#ifdef DEFINE_IO_READ
vm_datapart_read_nopf(struct vm_datapart *__restrict self,
                      USER CHECKED void *buf,
                      size_t num_bytes,
                      size_t offset)
#else /* DEFINE_IO_READ */
vm_datapart_write_nopf(struct vm_datapart *__restrict self,
                       USER CHECKED void const *buf,
                       size_t num_bytes,
                       size_t split_bytes,
                       size_t offset)
#endif /* !DEFINE_IO_READ */
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...)
#elif defined(DEFINE_IO_PHYS)
/* Read/write data to/from the given data part.
 * NOTE: When given a virtual memory buffer, these functions automatically
 *       check if the memory backing that buffer could potentially overlap
 *       with `self', in which case reading is performed using an intermediate
 *       buffer, so-as to prevent a possible dead-lock when `self' is already
 *       locked, whilst a #PF caused by writing to the target buffer attempts
 *       to acquire another lock to `self'
 * NOTE: The caller must _NOT_ be holding any lock to `self', the associated
 *       block, or any VM-tree when calling this function.
 * @param: split_bytes: The number of bytes after which to split the part in
 *                      order to minimize the memory impact of copy-on-write.
 *                      Usually the same as `num_bytes'
 * @return: * : The number of read/written bytes (limited by `num_bytes',
 *              and `vm_datapart_numbytes(self) - (src|dst)_offset'). */
PUBLIC NONNULL((1)) size_t KCALL
FUNC0(vm_datapart_)(struct vm_datapart *__restrict self,
                    physaddr_t buf,
                    size_t num_bytes,
#ifdef DEFINE_IO_WRITE
                    size_t split_bytes,
#endif /* DEFINE_IO_WRITE */
                    size_t offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...)
#else /* ... */
/* Same as the `vm_datapart_(read|write)', however make the assumption that the
 * memory backing is `safe' (i.e. access could never cause a #PF attempting to
 * acquire a lock to `self' when doing so is impossible; i.e. `dst'/`src' are
 * guarantied to not be apart of a mapping of `self', or be otherwise accessed
 * by code called from a page-fault handler) */
PUBLIC NONNULL((1, 2)) size_t KCALL
#ifdef DEFINE_IO_READ
vm_datapart_read_unsafe(struct vm_datapart *__restrict self,
                        void *__restrict buf,
                        size_t num_bytes,
                        size_t offset)
#else /* DEFINE_IO_READ */
vm_datapart_write_unsafe(struct vm_datapart *__restrict self,
                         void const *__restrict buf,
                         size_t num_bytes,
                         size_t split_bytes,
                         size_t offset)
#endif /* !DEFINE_IO_READ */
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...)
#endif /* !... */
{
	size_t result;
#ifdef DEFINE_IO_NOPF
	assert(num_bytes <= (size_t)SSIZE_MAX);
#endif /* DEFINE_IO_NOPF */
	vm_datapart_lockread_setcore(self);
#ifndef DEFINE_IO_READ
	/* Special case: Must also unshare copy-on-write mappings. */
	if likely(!self->dp_crefs) {
		incref(self);
	} else {
		pageid64_t part_start_vpage;
		REF struct vm_datapart *newpart;
		size_t num_vpages;
		pageid64_t base_vpage = (pageid64_t)(offset / PAGESIZE);
		part_start_vpage      = vm_datapart_startvpage(self);
		if (part_start_vpage != base_vpage) {
			size_t diff;
			sync_endread(self);
			diff    = (size_t)(base_vpage - part_start_vpage);
			newpart = vm_datapart_split(self, diff);
			self    = newpart; /* Inherit reference */
			TRY {
				vm_datapart_lockread_setcore(self);
			} EXCEPT {
				vm_datapart_decref_and_merge(self);
				RETHROW();
			}
			offset -= diff * PAGESIZE;
			if unlikely(!ATOMIC_READ(self->dp_crefs))
				goto do_has_part;
		} else {
			incref(self);
		}
		num_vpages = CEILDIV(split_bytes, PAGESIZE);
		if (vm_datapart_numvpages(self) > num_vpages) {
			sync_endread(self);
			TRY {
				decref(vm_datapart_split(self, num_vpages));
				vm_datapart_lockread_setcore(self);
			} EXCEPT {
				vm_datapart_decref_and_merge(self);
				RETHROW();
			}
			if unlikely(!ATOMIC_READ(self->dp_crefs))
				goto do_has_part;
		}
		assert(vm_datapart_startvpage(self) <= base_vpage);
		assert(vm_datapart_numvpages(self) <= num_vpages);
		sync_endread(self);
		/* Re-acquire a read-lock whilst unsharing copy-on-write mappings. */
		TRY {
			vm_datapart_lockread_setcore_unsharecow(self);
		} EXCEPT {
			vm_datapart_decref_and_merge(self);
			RETHROW();
		}
	}
do_has_part:
#endif /* !DEFINE_IO_READ */
	TRY {
		if unlikely(offset >= vm_datapart_numbytes(self))
			result = 0;
		else {
#ifdef DEFINE_IO_NOPF
			size_t transferr_error;
#endif /* DEFINE_IO_NOPF */
#if __SIZEOF_SIZE_T__ >= 8
			result = (size_t)(vm_datapart_numbytes(self) - offset);
#else /* __SIZEOF_SIZE_T__ >= 8 */
			if (OVERFLOW_USUB(vm_datapart_numbytes(self), offset, &result))
				result = (size_t)-1; /* Handle overflows */
#endif /* __SIZEOF_SIZE_T__ < 8 */
			if (result > num_bytes)
				result = num_bytes;
#ifdef DEFINE_IO_NOPF
			assert((ssize_t)result >= 0);
#endif /* DEFINE_IO_NOPF */
#if defined(DEFINE_IO_NOPF)
			transferr_error = IFELSE_RW(vm_datapart_do_read_nopf(self, buf, result, offset),
			                            vm_datapart_do_write_nopf(self, buf, result, offset));
#elif defined(DEFINE_IO_PHYS)
			IFELSE_RW(vm_datapart_do_read_phys(self, buf, result, offset),
			          vm_datapart_do_write_phys(self, buf, result, offset));
#else
			IFELSE_RW(vm_datapart_do_read(self, buf, result, offset),
			          vm_datapart_do_write(self, buf, result, offset));
#endif
#ifdef DEFINE_IO_NOPF
			if unlikely(transferr_error != 0) {
				assert(transferr_error <= result);
				/* The last `transferr_error' bytes could not be transferred. */
				result = (size_t)-(ssize_t)transferr_error;
			}
#endif /* DEFINE_IO_NOPF */
		}
	} EXCEPT {
		sync_endread(self);
#ifndef DEFINE_IO_READ
		vm_datapart_decref_and_merge(self);
#endif /* !DEFINE_IO_READ */
		RETHROW();
	}
	sync_endread(self);
#ifndef DEFINE_IO_READ
	vm_datapart_decref_and_merge(self);
#endif /* !DEFINE_IO_READ */
#ifdef DEFINE_IO_NOPF
	return (ssize_t)result;
#else /* DEFINE_IO_NOPF */
	return result;
#endif /* !DEFINE_IO_NOPF */
}


DECL_END

#undef IFELSE_RW
#undef FUNC0
#undef DEFINE_IO_PHYS
#undef DEFINE_IO_READ
#undef DEFINE_IO_WRITE
#undef DEFINE_IO_NOPF
