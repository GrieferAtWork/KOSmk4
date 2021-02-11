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
#include "readwrite.c"
//#define COPY_USER2KERNEL 1
//#define COPY_KERNEL2USER 1
#define VM_MEMSET_IMPL 1
#endif

#include <kernel/printk.h>
#include <kernel/vm/phys.h>
#include <sched/pid.h>

#include <hybrid/atomic.h>

#include <libvio/access.h>

#if (defined(COPY_USER2KERNEL) + defined(COPY_KERNEL2USER) + defined(VM_MEMSET_IMPL)) != 1
#error "Must #define COPY_USER2KERNEL or COPY_KERNEL2USER or VM_MEMSET_IMPL before #include-ing this file"
#endif


DECL_BEGIN


#ifdef COPY_USER2KERNEL
#define IS_READING 1
LOCAL void KCALL
copy_kernelspace_from_vm(struct vm *__restrict self,
                         UNCHECKED void const *addr,
                         KERNEL CHECKED void *buf,
                         size_t num_bytes,
                         bool force_accessible)
#else /* COPY_USER2KERNEL */
#define IS_WRITING 1
#ifdef VM_MEMSET_IMPL
LOCAL void KCALL
memset_into_vm(struct vm *__restrict self,
               UNCHECKED void *addr,
               int byte,
               size_t num_bytes,
               bool force_accessible)
#else /* VM_MEMSET_IMPL */
LOCAL void KCALL
copy_kernelspace_into_vm(struct vm *__restrict self,
                         UNCHECKED void *addr,
                         KERNEL CHECKED void const *buf,
                         size_t num_bytes,
                         bool force_accessible)
#endif /* !VM_MEMSET_IMPL */
#endif /* !COPY_USER2KERNEL */
		THROWS(E_SEGFAULT, E_WOULDBLOCK)
{
	size_t error;
again:
	/* Try to perform the copy without page faults. */
#if defined(COPY_USER2KERNEL)
	error = copy_kernelspace_from_vm_nopf(self, addr, buf, num_bytes);
#elif defined(COPY_KERNEL2USER)
	error = copy_kernelspace_into_vm_nopf(self, addr, buf, num_bytes);
#elif defined(VM_MEMSET_IMPL)
	error = memset_into_vm_nopf(self, addr, byte, num_bytes);
#endif
	if (!error)
		return;
	addr = (byte_t *)addr + num_bytes - error;
#ifndef VM_MEMSET_IMPL
	buf = (byte_t *)buf + num_bytes - error;
#endif /* !VM_MEMSET_IMPL */
	num_bytes = error;
	{
		struct vm_node *node;
		REF struct vm_datapart *part;
#ifdef IS_WRITING
		bool did_unshare;
#endif /* IS_WRITING */
		pageid_t pageid;
		size_t transfer_bytes;
		size_t node_vpage_offset; /* Offset (in vpages) of the accessed page from the start of `node' */
		uintptr_half_t node_prot;
		pageid = PAGEID_ENCODE(addr);
		/* Must manually copy data by explicitly locking the user-space VM and
		 * looking  at what kind of VM node  is mapped at the target location. */
again_lookup_node:
		sync_read(self);
#ifdef IS_WRITING
		did_unshare = false;
#endif /* IS_WRITING */
		node = vm_getnodeofpageid(self, pageid);
		if unlikely(!node || !node->vn_part) {
			sync_endread(self);
#ifdef LIBVIO_CONFIG_ENABLED
throw_segfault:
#endif /* LIBVIO_CONFIG_ENABLED */
#ifdef IS_WRITING
			THROW(E_SEGFAULT_UNMAPPED, addr,
			      E_SEGFAULT_CONTEXT_FAULT | E_SEGFAULT_CONTEXT_WRITING);
#else /* IS_WRITING */
			THROW(E_SEGFAULT_UNMAPPED, addr,
			      E_SEGFAULT_CONTEXT_FAULT);
#endif /* !IS_WRITING */
		}
		if (node->vn_guard) {
			/* TODO: Map a new guard above/below this node! */
		}
		assert(!wasdestroyed(node->vn_part));
		part              = incref(node->vn_part);
		node_prot         = node->vn_prot;
		node_vpage_offset = (size_t)(pageid - vm_node_getminpageid(node));

		/* Figure out how many bytes to transfer */
		transfer_bytes = vm_node_getsize(node) - node_vpage_offset;
		if (transfer_bytes > num_bytes)
			transfer_bytes = num_bytes;

		assert(vm_node_getpagecount(node) == vm_datapart_numvpages(part));
#ifdef LIBVIO_CONFIG_ENABLED
		/* Check for a VIO memory segment */
		if (part->dp_state == VM_DATAPART_STATE_VIOPRT) {
			struct vioargs args;
			pos_t vio_addr;
			COMPILER_READ_BARRIER();
			sync_endread(self);
			TRY {
				sync_read(part);
			} EXCEPT {
				decref(part);
				RETHROW();
			}
			args.va_file = incref(part->dp_block);
			args.va_acmap_offset = ((pos_t)(node_vpage_offset + vm_datapart_mindpage(part))
			                        << VM_DATABLOCK_ADDRSHIFT(args.va_file));
			/* Figure out the staring VIO address that is being accessed. */
			vio_addr = ((pos_t)vm_datapart_mindpage(part) << VM_DATABLOCK_ADDRSHIFT(args.va_file)) +
			            (pos_t)((byte_t *)addr - (byte_t *)vm_node_getminaddr(node));

			sync_endread(part);
			args.va_ops = args.va_file->db_vio;
			if unlikely(!args.va_ops) {
				decref_unlikely(args.va_file);
				decref_unlikely(part);
				goto throw_segfault;
			}
			args.va_acmap_page = (void *)FLOOR_ALIGN((uintptr_t)addr, PAGESIZE);
			args.va_state      = NULL;
			/* Make sure that the segment was mapped with the proper protection */
#ifdef IS_READING
			if unlikely(!force_accessible && !(node_prot & VM_PROT_READ))
#else /* IS_READING */
			if unlikely(!force_accessible && !(node_prot & VM_PROT_WRITE))
#endif /* !IS_READING */
			{
				decref_unlikely(args.va_file);
				decref_unlikely(part);
#ifdef IS_READING
				THROW(E_SEGFAULT_NOTREADABLE, addr, 0);
#else /* IS_READING */
				THROW(E_SEGFAULT_READONLY, addr, E_SEGFAULT_CONTEXT_WRITING);
#endif /* !IS_READING */
			}
			FINALLY_DECREF_UNLIKELY(args.va_file);
			FINALLY_DECREF_UNLIKELY(part);
#ifdef IS_READING
			vio_copyfromvio(&args, vio_addr, buf, transfer_bytes);
#elif !defined(VM_MEMSET_IMPL)
			vio_copytovio(&args, vio_addr, buf, transfer_bytes);
#else /* IS_READING */
			vio_memset(&args, vio_addr, byte, transfer_bytes);
#endif /* !IS_READING */
			goto done_part_transfer;
		}
#endif /* LIBVIO_CONFIG_ENABLED */
		sync_endread(self);
		TRY {
			/* Make sure the desired user-space access is actually allowed! */
#ifdef IS_WRITING
			if unlikely(!force_accessible && !(node_prot & VM_PROT_WRITE))
				THROW(E_SEGFAULT_READONLY, addr, E_SEGFAULT_CONTEXT_WRITING); /* Read-only memory */
#else /* IS_WRITING */
			if unlikely(!force_accessible && !(node_prot & VM_PROT_READ))
				THROW(E_SEGFAULT_NOTREADABLE, addr, 0); /* Memory isn't readable... */
#endif /* !IS_WRITING */
			/* Lock the datapart for the desired access */
#ifdef IS_WRITING
			if (!vm_lock_and_unshare_datapart_for_writing(self,
			                                              &part,
			                                              addr,
			                                              node,
			                                              node_prot,
			                                              node_vpage_offset,
			                                              1,
			                                              &did_unshare)) {
				decref_unlikely(part);
				goto again_lookup_node;
			}
#else /* IS_WRITING */
			vm_datapart_lockread_setcore(part);
			COMPILER_READ_BARRIER();
			/* Check if  the  part  still  includes  the  accessed  page.
			 * This is required  to ensure that  `vm_datapart_loadpage()'
			 * can be called safely (the part may have been split between
			 * the time of us acquiring a read-lock to it, and the  point
			 * when we released our write-lock to the effected VM) */
			if unlikely(node_vpage_offset >= vm_datapart_numvpages(part)) {
				sync_endread(part);
				decref_unlikely(part);
				goto again_lookup_node;
			}
			/* Load the affected page into the core. */
			assert(part->dp_state != VM_DATAPART_STATE_ABSENT);
			assert(node_vpage_offset < vm_datapart_numvpages(part));
#endif /* !IS_WRITING */
			{
				bool has_changed;
				physpage_t ppage;
				size_t page_remainder;
				uintptr_t page_offset;
				page_offset    = (uintptr_t)addr & PAGEMASK;
				page_remainder = PAGESIZE - page_offset;
				/* Make sure not to copy beyond the associated page. */
				if (transfer_bytes > page_remainder)
					transfer_bytes = page_remainder;
#ifdef IS_READING
				has_changed = false;
#else /* IS_READING */
				has_changed = true;
#endif /* !IS_READING */
				TRY {
					ppage = vm_datapart_loadpage(part,
					                             node_vpage_offset,
					                             &has_changed);
				} EXCEPT {
					sync_endread(part);
					RETHROW();
				}
				/* Actually transfer low-level RAM data. */
#ifdef IS_READING
				vm_copyfromphys(buf,
				                physpage2addr(ppage) + page_offset,
				                transfer_bytes);
#elif !defined(VM_MEMSET_IMPL)
				vm_copytophys(physpage2addr(ppage) + page_offset,
				              buf,
				              transfer_bytes);
#else /* IS_READING */
				vm_memsetphys(physpage2addr(ppage) + page_offset,
				              byte,
				              transfer_bytes);
#endif /* !IS_READING */
				/* Unlock the affected part. */
				sync_endread(part);
			}
		} EXCEPT {
			decref_unlikely(part);
			RETHROW();
		}
#ifdef IS_WRITING
		if (did_unshare)
			vm_datapart_decref_and_merge(part);
		else
#endif /* IS_WRITING */
		{
			decref_unlikely(part);
		}
#ifdef LIBVIO_CONFIG_ENABLED
done_part_transfer:
#endif /* LIBVIO_CONFIG_ENABLED */
		assert(transfer_bytes <= num_bytes);
		if (transfer_bytes >= num_bytes)
			return;
		num_bytes -= transfer_bytes;
		addr = (byte_t *)addr + transfer_bytes;
#ifndef VM_MEMSET_IMPL
		buf = (byte_t *)buf + transfer_bytes;
#endif /* !VM_MEMSET_IMPL */
		goto again;
	}
}


#undef VM_MEMSET_IMPL
#undef COPY_USER2KERNEL
#undef COPY_KERNEL2USER
#undef IS_READING
#undef IS_WRITING


DECL_END
