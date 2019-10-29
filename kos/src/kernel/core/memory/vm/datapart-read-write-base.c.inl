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
#ifdef __INTELLISENSE__
#include "datapart-read-write.c"
//#define DEFINE_IO_READ 1
#define DEFINE_IO_WRITE 1
//#define DEFINE_IO_PHYS 1
#endif

DECL_BEGIN

#if defined(DEFINE_IO_READ) && defined(DEFINE_IO_PHYS)
#define FUNC0(x) x##read_phys
#elif defined(DEFINE_IO_READ)
#define FUNC0(x) x##read
#elif defined(DEFINE_IO_PHYS)
#define FUNC0(x) x##write_phys
#else
#define FUNC0(x) x##write
#endif

/* Directly copy memory to/from the given buffer and `self'
 * NOTE: These functions automatically deal with page properties, such
 *       that `vm_datapart_do_read()' will ensure INITIALIZED pages, whilst
 *       `vm_datapart_do_write()' ensures HASCHANGED pages (so-long as the
 *       TRACKCHANGES bit is set)
 * NOTE: The caller must be holding a read-lock to `self', as well as ensure
 *       that `self' is either INCORE or LOCKED */
PUBLIC NONNULL((1)) void KCALL
FUNC0(vm_datapart_do_)(struct vm_datapart *__restrict self,
#ifdef DEFINE_IO_PHYS
                       vm_phys_t buf,
#elif defined(DEFINE_IO_READ)
                       USER CHECKED void *buf,
#else
                       USER CHECKED void const *buf,
#endif
                       size_t num_bytes,
                       vm_daddr_t offset)
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
			size_t max_io, page_offset;
			vm_phys_t data_base;
			page_offset = (size_t)(offset & (data_pagesize - 1));
			max_io      = data_pagesize - page_offset;
			if (max_io > num_bytes)
				max_io = num_bytes;
			data_base = vm_datapart_loaddatapage(self,
			                                     (vm_dpage_t)(offset >> VM_DATABLOCK_ADDRSHIFT(self->dp_block)),
#ifdef DEFINE_IO_READ
			                                     false
#else /* DEFINE_IO_READ */
			                                     true
#endif /* !DEFINE_IO_READ */
			                                     );
			/* Copy data to/from the data part memory back-end */
#ifdef DEFINE_IO_PHYS
#ifdef DEFINE_IO_READ
			vm_copyinphys(buf, (vm_phys_t)(data_base + page_offset), max_io);
#else /* DEFINE_IO_READ */
			vm_copyinphys((vm_phys_t)(data_base + page_offset), buf, max_io);
#endif /* !DEFINE_IO_READ */
#else /* DEFINE_IO_PHYS */
#ifdef DEFINE_IO_READ
			vm_copyfromphys(buf, (vm_phys_t)(data_base + page_offset), max_io);
#else /* DEFINE_IO_READ */
			vm_copytophys((vm_phys_t)(data_base + page_offset), buf, max_io);
#endif /* !DEFINE_IO_READ */
#endif /* !DEFINE_IO_PHYS */
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
}



#ifdef DEFINE_IO_PHYS
PUBLIC NONNULL((1)) size_t KCALL
FUNC0(vm_datapart_)(struct vm_datapart *__restrict self,
                    vm_phys_t buf,
                    size_t num_bytes,
#ifdef DEFINE_IO_WRITE
                    size_t split_bytes,
#endif /* DEFINE_IO_WRITE */
                    vm_daddr_t offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...)
#else /* DEFINE_IO_PHYS */
/* Same as the `vm_datapart_(read|write)', however make the assumption that the
 * memory backing is `safe' (i.e. access could never cause a #PF attempting to
 * acquire a lock to `self' when doing so is impossible) */
PUBLIC NONNULL((1, 2)) size_t KCALL
#ifdef DEFINE_IO_READ
vm_datapart_read_unsafe(struct vm_datapart *__restrict self,
                        void *__restrict buf,
                        size_t num_bytes,
                        vm_daddr_t offset)
#else /* DEFINE_IO_READ */
vm_datapart_write_unsafe(struct vm_datapart *__restrict self,
                         void const *__restrict buf,
                         size_t num_bytes,
                         size_t split_bytes,
                         vm_daddr_t offset)
#endif /* !DEFINE_IO_READ */
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...)
#endif /* !DEFINE_IO_PHYS */
{
	size_t result;
	vm_datapart_lockread_setcore(self);
#ifndef DEFINE_IO_READ
	/* Special case: Must also unshare copy-on-write mappings. */
	if likely(!self->dp_crefs) {
		incref(self);
	} else {
		vm_vpage64_t part_start_vpage;
		REF struct vm_datapart *newpart;
		size_t num_vpages;
		vm_vpage64_t base_vpage = (vm_vpage64_t)(offset / PAGESIZE);
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
		if unlikely(offset >= (vm_daddr_t)vm_datapart_numbytes(self))
			result = 0;
		else {
			result = (size_t)((vm_daddr_t)vm_datapart_numbytes(self) - offset); /* XXX: Overflow? */
			if (result > num_bytes)
				result = num_bytes;
#if defined(DEFINE_IO_READ) && defined(DEFINE_IO_PHYS)
			vm_datapart_do_read_phys(self, buf, result, offset);
#elif defined(DEFINE_IO_READ)
			vm_datapart_do_read(self, buf, result, offset);
#elif defined(DEFINE_IO_PHYS)
			vm_datapart_do_write_phys(self, buf, result, offset);
#else
			vm_datapart_do_write(self, buf, result, offset);
#endif
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
	return result;
}


DECL_END

#undef FUNC0
#undef DEFINE_IO_PHYS
#undef DEFINE_IO_READ
#undef DEFINE_IO_WRITE
