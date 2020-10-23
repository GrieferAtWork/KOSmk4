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
#ifndef GUARD_MODELFEXEC_ELF_C
#define GUARD_MODELFEXEC_ELF_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/debugtrap.h>
#include <kernel/driver-param.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/execabi.h>
#include <kernel/vm.h>
#include <kernel/vm/builder.h>
#include <kernel/vm/exec.h>
#include <kernel/vm/phys.h>

#include <hybrid/align.h>
#include <hybrid/pointer.h>

#include <compat/config.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/noexec.h>
#include <kos/exec/elf.h>
#include <kos/exec/peb.h>

#include <assert.h>
#include <elf.h>
#include <malloca.h>
#include <signal.h> /* SIGTRAP */
#include <stddef.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/exec/elf.h>
#endif /* __ARCH_HAVE_COMPAT */

/**/
#include "elf.h"

DECL_BEGIN

#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x

LOCAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
NOTHROW(KCALL elf_validate_ehdr)(ElfW(Ehdr) const *__restrict ehdr) {
	uintptr_t result;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADCLASS;
	if unlikely(ehdr->e_ident[EI_CLASS] != ELF_ARCH_CLASS)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADORDER;
	if unlikely(ehdr->e_ident[EI_DATA] != ELF_ARCH_DATA)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION;
	if unlikely(ehdr->e_ident[EI_VERSION] != EV_CURRENT)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION2;
	if unlikely(ehdr->e_version != EV_CURRENT)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADTYPE;
	if unlikely(ehdr->e_type != ET_EXEC)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADMACH;
	if unlikely(ehdr->e_machine != ELF_ARCH_MACHINE)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADHEADER;
	if unlikely(ehdr->e_ehsize < offsetafter(ElfW(Ehdr), e_phnum))
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOSEGMENTS;
	if unlikely(!ehdr->e_phnum)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADSEGMENTS;
	if unlikely(ehdr->e_phentsize != sizeof(ElfW(Phdr)))
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_TOOMANYSEGMENTS;
	if unlikely(ehdr->e_phnum > ELF_ARCH_MAXPHCOUNT)
		goto done; /* Too many program headers. */
	result = 0;
done:
	return result;
}

#ifdef __ARCH_HAVE_COMPAT
LOCAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
NOTHROW(KCALL compat_elf_validate_ehdr)(COMPAT_ElfW(Ehdr) const *__restrict ehdr) {
	uintptr_t result;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADCLASS;
	if unlikely(ehdr->e_ident[EI_CLASS] != COMPAT_ELF_ARCH_CLASS)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADORDER;
	if unlikely(ehdr->e_ident[EI_DATA] != COMPAT_ELF_ARCH_DATA)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION;
	if unlikely(ehdr->e_ident[EI_VERSION] != EV_CURRENT)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION2;
	if unlikely(ehdr->e_version != EV_CURRENT)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADTYPE;
	if unlikely(ehdr->e_type != ET_EXEC)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADMACH;
	if unlikely(ehdr->e_machine != COMPAT_ELF_ARCH_MACHINE)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADHEADER;
	if unlikely(ehdr->e_ehsize < offsetafter(COMPAT_ElfW(Ehdr), e_phnum))
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOSEGMENTS;
	if unlikely(!ehdr->e_phnum)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADSEGMENTS;
	if unlikely(ehdr->e_phentsize != sizeof(COMPAT_ElfW(Phdr)))
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_TOOMANYSEGMENTS;
	if unlikely(ehdr->e_phnum > COMPAT_ELF_ARCH_MAXPHCOUNT)
		goto done; /* Too many program headers. */
	result = 0;
done:
	return result;
}
#endif /* __ARCH_HAVE_COMPAT */

LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1)) struct vm_node *KCALL
create_bss_overlap_node(struct regular_node *__restrict exec_node,
                        pos_t file_data_offset,
                        size_t bss_start_page_offset,
                        size_t bss_num_bytes) {
	struct vm_node *result_node;
	struct vm_datapart *result_part;
	physpage_t overlap_page;
	result_node = (struct vm_node *)kmalloc(sizeof(struct vm_node),
	                                        GFP_LOCKED | GFP_PREFLT);
	TRY {
		result_part = (struct vm_datapart *)kmalloc(sizeof(struct vm_datapart),
		                                            GFP_LOCKED | GFP_PREFLT);
		TRY {
			overlap_page = page_mallocone();
			if unlikely(overlap_page == PHYSPAGE_INVALID)
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
			TRY {
				/* Load the overlapping file data into memory. */
				inode_readall_phys(exec_node, physpage2addr(overlap_page),
				                   bss_start_page_offset,
				                   file_data_offset);
				/* Check if we must zero-initialize the BSS portion. */
				if (!page_iszero(overlap_page)) {
					/* Zero-initialize the BSS portion */
					vm_memsetphys(physpage2addr(overlap_page) + bss_start_page_offset,
					              0, bss_num_bytes);
				}
			} EXCEPT {
				page_free(overlap_page, 1);
				RETHROW();
			}
		} EXCEPT {
			kfree(result_part);
			RETHROW();
		}
	} EXCEPT {
		kfree(result_node);
		RETHROW();
	}
	result_part->dp_refcnt = 1;
	shared_rwlock_init(&result_part->dp_lock);
	result_part->dp_tree.a_vmin                = 0;
	result_part->dp_tree.a_vmax                = 0;
	result_part->dp_crefs                      = NULL;
	result_part->dp_srefs                      = NULL;
	result_part->dp_stale                      = NULL;
	result_part->dp_block                      = incref(&vm_datablock_anonymous_zero);
	result_part->dp_flags                      = VM_DATAPART_FLAG_NORMAL;
	result_part->dp_state                      = VM_DATAPART_STATE_INCORE;
	result_part->dp_ramdata.rd_blockv          = &result_part->dp_ramdata.rd_block0;
	result_part->dp_ramdata.rd_block0.rb_start = overlap_page;
	result_part->dp_ramdata.rd_block0.rb_size  = 1;
	result_part->dp_pprop                      = VM_DATAPART_PPP_INITIALIZED << (0 * VM_DATAPART_PPP_BITS);
	result_part->dp_futex                      = NULL;
	/* result_node->vn_node.a_vmin = ...; // Initialized by the caller */
	/* result_node->vn_node.a_vmax = ...; // Initialized by the caller */
	/* result_node->vn_prot        = ...; // Initialized by the caller */
	result_node->vn_flags = VM_NODE_FLAG_NORMAL;
	/* result_node->vn_vm          = ...; // Unused by vmb */
	result_node->vn_part   = result_part; /* Inherit reference */
	result_node->vn_block  = incref(&vm_datablock_anonymous_zero);
	result_node->vn_fspath = NULL;
	result_node->vn_fsname = NULL;
	/* result_node->vn_link        = ...; // Unused by vmb */
	result_node->vn_guard = 0;
	return result_node;
}


#ifndef __INTELLISENSE__
DECL_END
#define LOCAL_PTR(x)      x *
#define LOCAL_FUNC(x)     x
#define LOCAL_ELFW        ELFW
#define LOCAL_ElfW        ElfW
#define LOCAL_POINTERSIZE __SIZEOF_POINTER__
#ifdef __ARCH_HAVE_COMPAT
#define LOCAL_EXEC_ARGV_SIZE 1
#endif /* __ARCH_HAVE_COMPAT */
#include "elf-exec.c.inl"

#ifdef __ARCH_HAVE_COMPAT
#define LOCAL_PTR            __ARCH_COMPAT_PTR
#define LOCAL_FUNC(x)        compat_##x
#define LOCAL_ELFW           COMPAT_ELFW
#define LOCAL_ElfW           COMPAT_ElfW
#define LOCAL_POINTERSIZE    __ARCH_COMPAT_SIZEOF_POINTER
#define LOCAL_EXEC_ARGV_SIZE 1
#include "elf-exec.c.inl"
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN
#else /* !__INTELLISENSE__ */
LOCAL WUNUSED NONNULL((1)) unsigned int FCALL
elf_exec_impl(/*in|out*/ struct execargs *__restrict args)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR);
#ifdef __ARCH_HAVE_COMPAT
LOCAL WUNUSED NONNULL((1)) unsigned int FCALL
compat_elf_exec_impl(/*in|out*/ struct execargs *__restrict args)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR);
#endif /* __ARCH_HAVE_COMPAT */
#endif /* __INTELLISENSE__ */

/* Exec-abi callback for ELF files */
INTERN WUNUSED NONNULL((1)) unsigned int FCALL
elfabi_exec(/*in|out*/ struct execargs *__restrict args) {
	STATIC_ASSERT(CONFIG_EXECABI_MAXHEADER >= sizeof(ElfW(Ehdr)));
#ifdef __ARCH_HAVE_COMPAT
	STATIC_ASSERT(CONFIG_EXECABI_MAXHEADER >= sizeof(COMPAT_ElfW(Ehdr)));
#endif /* __ARCH_HAVE_COMPAT */
	uintptr_t reason;
	reason = elf_validate_ehdr((ElfW(Ehdr) *)args->ea_header);
	if (reason == 0)
		return elf_exec_impl(args);
#ifdef __ARCH_HAVE_COMPAT
	reason = compat_elf_validate_ehdr((COMPAT_ElfW(Ehdr) *)args->ea_header);
	if (reason == 0)
		return compat_elf_exec_impl(args);
#endif /* __ARCH_HAVE_COMPAT */
	THROW(E_NOT_EXECUTABLE_FAULTY,
	      E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF,
	      reason);
}

#ifndef CONFIG_BUILDING_KERNEL_CORE
PRIVATE struct execabi elfabi = EXECABI_INIT_ELF;
PRIVATE DRIVER_INIT void KCALL init(void) {
	execabis_register(&elfabi);
}
#endif /* CONFIG_BUILDING_KERNEL_CORE */

DECL_END

#endif /* !GUARD_MODELFEXEC_ELF_C */
