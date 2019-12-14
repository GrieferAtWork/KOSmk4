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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_EXEC_C
#define GUARD_KERNEL_SRC_MEMORY_VM_EXEC_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <kernel/debugtrap.h>
#include <kernel/driver-param.h>
#include <kernel/except.h>
#include <kernel/vm.h>
#include <kernel/vm/builder.h>
#include <kernel/vm/exec.h>
#include <kernel/vm/library.h>
#include <kernel/vm/phys.h>

#include <hybrid/align.h>

#include <kos/library-listdef.h>
#include <kos/process.h>

#include <assert.h>
#include <elf.h>
#include <malloca.h>
#include <string.h>

#include "vm-nodeapi.h"

DECL_BEGIN

DEFINE_PERVM_FINI(pervm_fini_execinfo);
INTERN NONNULL((1)) void
NOTHROW(KCALL pervm_fini_execinfo)(struct vm *__restrict self) {
	struct vm_execinfo_struct *execinfo;
	execinfo = &FORVM(self, thisvm_execinfo);
	xdecref(execinfo->ei_node);
	xdecref(execinfo->ei_dent);
	xdecref(execinfo->ei_path);
}

PUBLIC ATTR_PERVM struct vm_execinfo_struct thisvm_execinfo = {
	/* .ei_node = */ NULL,
	/* .ei_dent = */ NULL,
	/* .ei_path = */ NULL
};


#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x

INTDEF byte_t __x86_kernel_ld_elf_startpage[];
INTDEF byte_t __x86_kernel_ld_elf_numpages[];

INTERN struct vm_ramfile kernel_ld_elf_ramfile =
	VM_RAMFILE_INIT((pageptr_t)__x86_kernel_ld_elf_startpage - KERNEL_BASE_PAGE,
	                (size_t)__x86_kernel_ld_elf_numpages);


/* List of callbacks that should be invoked after vm_exec()
 * These are called alongside stuff like `handle_manager_cloexec()'
 * NOTE: The passed vm is always `THIS_VM', and is never `&vm_kernel' */
PUBLIC CALLBACK_LIST(void KCALL(void)) vm_onexec_callbacks = CALLBACK_LIST_INIT;

/* Library listing definition, using a process's PEB as data source.
 * For this we set up the list definition to later load the filename
 * from using an expression equal to `PEB.pp_argv[0]', allowing the
 * name to be overwritten as one of:
 *   - PEB.pp_argv    = POINTER_TO_POINTER_TO_NAME;
 *   - PEB.pp_argv[0] = POINTER_TO_NAME;
 */
PRIVATE struct library_listdef const peb_based_library_list = {
	.lld_size                      = sizeof(struct library_listdef),
	.lld_sizeof_pointer            = sizeof(void *),
	.lld_flags                     = LIBRARY_LISTDEF_FPELEMENT |
	                                 LIBRARY_LISTDEF_FRELFILENAME |
	                                 LIBRARY_LISTDEF_FSINGLE,
	.lld_first                     = 0, /* Filled below */
	.lld_count                     = NULL, /* Unused */
	.lld_module_offsetof_filename  = 0, /* Always use argv[0] */
	.lld_module_offsetof_loadaddr  = 0, /* Always ZERO */
	.lld_module_offsetof_loadstart = 0, /* Filled below */
	.lld_entry_offsetof_next       = 0, /* Unused */
	.lld_entry_offsetof_module     = offsetof(struct process_peb, pp_argv)
};



LOCAL NOBLOCK WUNUSED NONNULL((1)) uintptr_t
NOTHROW(KCALL elf_validate_ehdr)(Elf_Ehdr *__restrict ehdr) {
	uintptr_t result;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADCLASS;
	if	unlikely(!ELF_HOST_ISVALID_CLASS(ehdr->e_ident[EI_CLASS]))
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADORDER;
	if	unlikely(!ELF_HOST_ISVALID_DATA(ehdr->e_ident[EI_DATA]))
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION;
	if	unlikely(ehdr->e_ident[EI_VERSION] != EV_CURRENT)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION2;
	if	unlikely(ehdr->e_version != EV_CURRENT)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADTYPE;
	if	unlikely(ehdr->e_type != ET_EXEC)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADMACH;
	if	unlikely(!ELF_HOST_ISVALID_MACHINE(ehdr->e_machine))
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADHEADER;
	if	unlikely(ehdr->e_ehsize < offsetafter(Elf_Ehdr,e_phnum))
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOSEGMENTS;
	if	unlikely(!ehdr->e_phnum)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADSEGMENTS;
	if	unlikely(ehdr->e_phentsize != sizeof(Elf_Phdr))
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_TOOMANYSEGMENTS;
	if	unlikely(ehdr->e_phnum > ELF_HOST_MAXPROGRAMHEADERCOUNT)
		goto done; /* Too many program headers. */
	result = 0;
done:
	return result;
}


LOCAL WUNUSED ATTR_RETNONNULL NONNULL((1)) struct vm_node *KCALL
create_bss_overlap_node(struct regular_node *__restrict exec_node,
                        pos_t file_data_offset,
                        size_t bss_start_page_offset,
                        size_t bss_num_bytes) {
	struct vm_node *result_node;
	struct vm_datapart *result_part;
	pageptr_t overlap_page;
	result_node = (struct vm_node *)kmalloc(sizeof(struct vm_node),
	                                        GFP_LOCKED | GFP_PREFLT);
	TRY {
		result_part = (struct vm_datapart *)kmalloc(sizeof(struct vm_datapart),
		                                            GFP_LOCKED | GFP_PREFLT);
		TRY {
			overlap_page = page_malloc(1);
			if unlikely(overlap_page == PAGEPTR_INVALID)
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
			TRY {
				/* Load the overlapping file data into memory. */
				inode_readall_phys(exec_node, page2addr(overlap_page),
				                   bss_start_page_offset,
				                   file_data_offset);
				/* Check if we must zero-initialize the BSS portion. */
				if (!page_iszero(overlap_page)) {
					/* Zero-initialize the BSS portion */
					vm_memsetphys(page2addr(overlap_page) + bss_start_page_offset,
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
	result_node->vn_part  = result_part; /* Inherit reference */
	result_node->vn_block = incref(&vm_datablock_anonymous_zero);
	/* result_node->vn_link        = ...; // Unused by vmb */
	result_node->vn_guard = 0;
	return result_node;
}


/* Load an executable binary `exec_node' into a temporary, emulated VM.
 * If this succeeds, clear all of the mappings from `effective_vm', and
 * replace them with the contents of the temporary, emulated VM (such
 * that the entire process of mapping the new contents is always able
 * to either seamlessly restore the old memory mappings, or not even
 * touch them at all upon error)
 * -> This function is used to implement the exec() family of system calls
 *    in such that exec() is always able to allow the calling program to
 *    handle load errors (at least so long as those errors aren't caused
 *    by the executable's initialization, such as missing libraries)
 * NOTE: Upon successful return, all threads using the given `effective_vm' (excluding
 *       the caller themself if they are using the VM, too) will have been terminated.
 * @param: effective_vm: The VM into which to map the executable.
 *                       This must not be the kernel VM, which causes an assertion failure.
 * @param: user_state:   The user-space CPU state to update upon success in a manner that
 *                       proper execution of the loaded binary is possible.
 *                       Note however that in the case of a dynamic binary, a dynamic linker
 *                       may be injected to perform dynamic linking whilst already in user-space.
 * @param: exec_path:    Filesystem path for the directory inside of which `exec_node' is located.
 * @param: exec_dentry:  Directory entry containing the filename of `exec_node'
 * @param: exec_node:    The filesystem node which should be loaded as an executable binary.
 * @param: argc_inject:  The number of arguments from `argv_inject' to inject at the beginning of the user-space argc/argv vector.
 * @param: argv_inject:  Vector of arguments to inject at the beginning of the user-space argc/argv vector.
 * @param: argv:         NULL-terminated vector of arguments to-be passed to program being loaded.
 * @param: envp:         NULL-terminated vector of environment variables to-be passed to program being loaded.
 * @return: * :          A pointer to the user-space register state to-be loaded in order to start
 *                       execution of the newly loaded binary (usually equal to `user_state')
 * @throw: E_BADALLOC:   Insufficient memory
 * @throw: E_SEGFAULT:   The given `argv', `envp', or one of their pointed-to strings is faulty
 * @throw: E_NOT_EXECUTABLE: The given `exec_node' was not recognized as an acceptable binary. */
PUBLIC WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3, 4, 5)) struct icpustate *KCALL
vm_exec(struct vm *__restrict effective_vm,
        struct icpustate *__restrict user_state,
        struct path *__restrict exec_path,
        struct directory_entry *__restrict exec_dentry,
        struct regular_node *__restrict exec_node,
        size_t argc_inject, KERNEL char const *const *argv_inject,
        USER UNCHECKED char const *USER CHECKED const *argv,
        USER UNCHECKED char const *USER CHECKED const *envp)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR) {
	Elf_Ehdr ehdr;
	Elf_Phdr *phdr_vector;
	/* TODO: Support for Shebang */
	/* TODO: Support for PE */
	inode_readall(exec_node, &ehdr, sizeof(ehdr), 0);
	if unlikely(ehdr.e_ident[EI_MAG0] != ELFMAG0 ||
	            ehdr.e_ident[EI_MAG1] != ELFMAG1 ||
	            ehdr.e_ident[EI_MAG2] != ELFMAG2 ||
	            ehdr.e_ident[EI_MAG3] != ELFMAG3)
		THROW(E_NOT_EXECUTABLE_NOT_A_BINARY);
	/* Validate the executable header. */
	{
		uintptr_t reason;
		reason = elf_validate_ehdr(&ehdr);
		if unlikely(reason != 0)
			THROW(E_NOT_EXECUTABLE_FAULTY,
			      E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF,
			      reason);
	}
	phdr_vector = (Elf_Phdr *)malloca(ehdr.e_phnum * sizeof(Elf_Phdr));
	TRY {
		struct vmb builder = VMB_INIT;
		PAGEDIR_PAGEALIGNED UNCHECKED void *peb_base;
		PAGEDIR_PAGEALIGNED UNCHECKED void *stack_base;
		PAGEDIR_PAGEALIGNED UNCHECKED void *linker_base;
		uintptr_t loadstart = (uintptr_t)-1;
		TRY {
			bool need_dyn_linker = false;
			linker_base = (UNCHECKED void *)-1;
			Elf_Half i;
			/* Read the program segment header table into memory. */
			inode_readall(exec_node,
			              phdr_vector,
			              ehdr.e_phnum * sizeof(Elf_Phdr),
			              (pos_t)ehdr.e_phoff);

			/* Load program headers. */
			for (i = 0; i < ehdr.e_phnum; ++i) {
				switch (phdr_vector[i].p_type) {

				case PT_NULL:
					/* Unused entry. */
					break;
				case PT_NOTE:
				case PT_PHDR:
					break;

				case PT_LOAD: {
					pageid_t page_index;
					size_t num_pages, num_total;
					uintptr_half_t prot;
					size_t adjusted_filsize;
					size_t adjusted_memsize;
					void *bss_start;
					bool map_ok;
					/* Load entry into memory. */
					if ((phdr_vector[i].p_offset & PAGEMASK) !=
					    (phdr_vector[i].p_vaddr & PAGEMASK)) {
						THROW(E_NOT_EXECUTABLE_FAULTY,
						      E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF,
						      E_NOT_EXECUTABLE_FAULTY_REASON_ELF_UNALIGNEDSEGMENT);
					}
					page_index = PAGEID_ENCODE(phdr_vector[i].p_vaddr);
					if (loadstart > phdr_vector[i].p_vaddr)
						loadstart = phdr_vector[i].p_vaddr;
					adjusted_filsize = phdr_vector[i].p_filesz + (phdr_vector[i].p_vaddr & PAGEMASK);
					adjusted_memsize = phdr_vector[i].p_memsz + (phdr_vector[i].p_vaddr & PAGEMASK);
					num_pages        = CEILDIV(adjusted_filsize, PAGESIZE);
					num_total        = CEILDIV(adjusted_memsize, PAGESIZE);
					bss_start        = (void *)(phdr_vector[i].p_vaddr + phdr_vector[i].p_filesz);
					/* Check if we're going to need a .bss overlap fixup page */
					if (adjusted_memsize > adjusted_filsize) {
						if (((uintptr_t)bss_start & PAGEMASK) != 0)
							--num_pages;
					}
#if PF_X == VM_PROT_EXEC && PF_W == VM_PROT_WRITE && PF_R == VM_PROT_READ
					prot = phdr_vector[i].p_flags & (PF_X | PF_W | PF_R);
#else
					prot = VM_PROT_NONE;
					if (phdr_vector[i].p_flags & PF_X)
						prot |= VM_PROT_EXEC;
					if (phdr_vector[i].p_flags & PF_W)
						prot |= VM_PROT_WRITE;
					if (phdr_vector[i].p_flags & PF_R)
						prot |= VM_PROT_READ;
#endif
					map_ok = vmb_mapat(&builder,
					                   page_index,
					                   num_pages,
					                   exec_node,
					                   (vm_vpage64_t)(phdr_vector[i].p_offset / PAGESIZE),
					                   prot | VM_PROT_PRIVATE);
					if unlikely(!map_ok) {
err_overlap:
						THROW(E_NOT_EXECUTABLE_FAULTY,
						      E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF,
						      E_NOT_EXECUTABLE_FAULTY_REASON_ELF_SEGMENTOVERLAP);
					}
					if (num_total > num_pages) {
						/* LD sometimes produces really weird .bss sections that are neither whole
						 * pages, nor are placed such that they exist at the end of some given file.
						 * Because of this, we must manually check for segments that end in a
						 * small (< PAGESIZE) section of bss memory when that segment doesn't hug the
						 * end of the actual file, and memset() it to all ZEROes.
						 *
						 * Example (filesize == 0x22060):
						 *     Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align
						 *     LOAD           0x000000 0x00000000 0x00000000 0x0e224 0x0e224 R E 0x1000
						 *     LOAD           0x00e224 0x0000f224 0x0000f224 0x000ec 0x000fc RW  0x1000
						 *     DYNAMIC        0x00e228 0x0000f228 0x0000f228 0x000a8 0x000a8 RW  0x4
						 *
						 * The second segment contains a BSS area of 0xfc-0xec == 0x10 bytes at 0xf310...0xf31f
						 * Since this range is still part of the page that gets loaded from disk as a file mapping,
						 * the associated file mapping at 0xf224...0xf30f is extended to the end of the associated
						 * page at 0xffff (which includes (in this case) the entire .bss section).
						 *
						 * In a case like this where the .bss area overlaps with the extended file mapping, the first
						 * page of the .bss area must be re-mapped as writable (if not already), followed by the area
						 * `START_OF_BSS ... MIN(MAX_BSS_BYTE, MAX_BYTE_OF_PAGE(PAGE_OF(START_OF_BSS)))' being forcibly
						 * initialized to all ZEROes, causing the page to be faulted and become initialized properly.
						 */
						if (((uintptr_t)bss_start & PAGEMASK) != 0) {
							pageid_t bss_overlap_page;
							size_t bss_start_offset, bss_overlap, bss_total_size;
							struct vm_node *overlap_node;
							assert(phdr_vector[i].p_memsz > phdr_vector[i].p_filesz);
							bss_total_size = phdr_vector[i].p_memsz -
							                 phdr_vector[i].p_filesz;
							bss_start_offset = (size_t)((uintptr_t)bss_start & PAGEMASK);
							bss_overlap = PAGESIZE - bss_start_offset;
							if (bss_overlap > bss_total_size)
								bss_overlap = bss_total_size;
							bss_overlap_page = page_index + num_pages;
							assert(bss_overlap_page == PAGEID_ENCODE(bss_start));
							if unlikely(vmb_getnodeof(&builder, bss_overlap_page) != NULL)
								goto err_overlap; /* Already in use... */
							overlap_node = create_bss_overlap_node(exec_node,
							                                       (pos_t)(phdr_vector[i].p_offset +
							                                               phdr_vector[i].p_filesz -
							                                               bss_start_offset),
							                                       bss_start_offset,
							                                       bss_overlap);
							overlap_node->vn_node.a_vmin = bss_overlap_page;
							overlap_node->vn_node.a_vmax = bss_overlap_page;
							assert(overlap_node->vn_part);
							assert(overlap_node->vn_part->dp_block == &vm_datablock_anonymous_zero ||
							       overlap_node->vn_part->dp_block == &vm_datablock_anonymous);
							overlap_node->vn_prot = prot | VM_PROT_PRIVATE;
							vmb_node_insert(&builder, overlap_node);
							++num_pages; /* Adjust to not map the first (special) page of .bss */
						}
						/* Map BSS as anonymous, zero-initialized memory. */
						map_ok = vmb_mapat(&builder,
						                   page_index + num_pages,
						                   num_total - num_pages,
						                   &vm_datablock_anonymous_zero,
						                   0,
						                   prot | VM_PROT_PRIVATE);
						if unlikely(!map_ok)
							goto err_overlap;
					}
				}	break;

				default:
					need_dyn_linker = true;
					break;
				}
			}
			/* If necessary, load the dynamic linker. */
			if (need_dyn_linker) {
				linker_base = nvmb_map(&builder,
				                       HINT_GETADDR(KERNEL_VMHINT_USER_DYNLINK),
				                       kernel_ld_elf_ramfile.rf_data.rb_size * PAGESIZE,
				                       PAGESIZE,
#if !defined(NDEBUG) && 1 /* XXX: Remove me */
				                       VM_GETFREE_ABOVE,
#else
				                       HINT_GETMODE(KERNEL_VMHINT_USER_DYNLINK),
#endif
				                       &kernel_ld_elf_ramfile.rf_block,
				                       0,
				                       VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXEC | VM_PROT_PRIVATE,
				                       VM_NODE_FLAG_NORMAL,
				                       0);
			}

#define USER_STACK_NUM_PAGES 8 /* TODO: Don't put this here! */
			/* Allocate a new user-space stack for the calling thread. */
			stack_base = nvmb_map(&builder,
			                      HINT_GETADDR(KERNEL_VMHINT_USER_STACK),
			                      USER_STACK_NUM_PAGES * PAGESIZE,
			                      PAGESIZE,
			                      HINT_GETMODE(KERNEL_VMHINT_USER_STACK),
			                      &vm_datablock_anonymous_zero, /* XXX: Use memory with a debug initializer? */
			                      0,
			                      VM_PROT_READ | VM_PROT_WRITE,
			                      VM_NODE_FLAG_NORMAL,
			                      0);

			/* Create a memory mapping for the PEB containing `argv' and `envp' */
			peb_base = vmb_alloc_peb(&builder,
			                         argc_inject,
			                         argv_inject,
			                         argv,
			                         envp);

			/* Apply the newly loaded binary to the given VM and
			 * terminate all threads using it except for the caller. */
			{
				struct vm_execinfo_struct ei;
				ei.ei_node = exec_node;
				ei.ei_dent = exec_dentry;
				ei.ei_path = exec_path;
				vmb_apply(&builder,
				          effective_vm,
				          VMB_APPLY_AA_TERMTHREADS |
				          VMB_APPLY_AA_SETEXECINFO,
				          &ei);
			}
		} EXCEPT {
			vmb_fini(&builder);
			RETHROW();
		}

		/* Set the entry point for the loaded binary. */
		user_state = exec_initialize_entry(user_state,
		                                   peb_base,
		                                   stack_base,
		                                   USER_STACK_NUM_PAGES * PAGESIZE,
		                                   (USER void *)ehdr.e_entry);

		/* Initialize the RTLD portion of the user-space bootstrap process. */
		if (linker_base != (void *)-1) {
			user_state = exec_initialize_elf_rtld(/* user_state:           */ user_state,
			                                      /* exec_path:            */ exec_path,
			                                      /* exec_dentry:          */ exec_dentry,
			                                      /* exec_node:            */ exec_node,
			                                      /* application_loadaddr: */ (uintptr_t)0,
			                                      /* linker_loadaddr:      */ (uintptr_t)linker_base,
			                                      /* phdr_vec:             */ phdr_vector,
			                                      /* phdr_cnt:             */ ehdr.e_phnum);
		}
		{
			/* Initialize the library definitions list to use the PEB
			 * NOTE: When libdl was linked into the mix (see line above), then
			 *       it will override this fairly early on with its own version. */
			struct library_listdef *lld = &FORVM(effective_vm, thisvm_library_listdef);
			memcpy(lld, &peb_based_library_list, sizeof(struct library_listdef));
			lld->lld_first                     = peb_base;
			lld->lld_module_offsetof_loadstart = loadstart;
		}
	} EXCEPT {
		freea(phdr_vector);
		RETHROW();
	}
	freea(phdr_vector);
	return user_state;
}



/* Assert that `self' is a regular node for the purpose of being used as the
 * file to-be executed in an exec() system call, by throwing one of the annotated
 * exceptions if this isn't the case. */
PUBLIC NONNULL((1)) void KCALL
vm_exec_assert_regular(struct inode *__restrict self)
		THROWS(E_FSERROR_IS_A_DIRECTORY,
		       E_FSERROR_IS_A_SYMBOLIC_LINK,
		       E_NOT_EXECUTABLE_NOT_REGULAR) {
	if unlikely(!INODE_ISREG(self)) {
		if (INODE_ISDIR(self))
			THROW(E_FSERROR_IS_A_DIRECTORY, E_FILESYSTEM_IS_A_DIRECTORY_EXEC);
		if (INODE_ISLNK(self))
			THROW(E_FSERROR_IS_A_SYMBOLIC_LINK, E_FILESYSTEM_IS_A_SYMBOLIC_LINK_EXEC);
		THROW(E_NOT_EXECUTABLE_NOT_REGULAR);
	}
}


#ifndef CONFIG_DEFAULT_USERSPACE_INIT
#define CONFIG_DEFAULT_USERSPACE_INIT "/bin/init"
#endif /* !CONFIG_DEFAULT_USERSPACE_INIT */

/* Commandline configuration for the initial user-space binary to execute. */
INTERN_CONST ATTR_FREERODATA char const kernel_init_binary_default[] = CONFIG_DEFAULT_USERSPACE_INIT;
INTERN ATTR_FREEDATA char const *kernel_init_binary = kernel_init_binary_default;
DEFINE_KERNEL_COMMANDLINE_OPTION(kernel_init_binary,
                                 KERNEL_COMMANDLINE_OPTION_TYPE_STRING, "init");


/* Update the given cpu state to start executing /bin/init, or whatever
 * was passed as argument in a `init=...' kernel commandline option. */
INTERN ATTR_FREETEXT ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(KCALL kernel_initialize_exec_init)(struct icpustate *__restrict state) {
	REF struct path *init_path;
	REF struct inode *init_node;
	REF struct directory_entry *init_dentry;
	char const *init_argv[] = { kernel_init_binary };
	init_node = path_traversefull(THIS_FS,
	                              kernel_init_binary,
	                              true,
	                              FS_MODE_FNORMAL,
	                              NULL,
	                              &init_path,
	                              NULL,
	                              &init_dentry);
	/* Can only execute regular files. */
	vm_exec_assert_regular(init_node);
	/* Load the given INode as an executable. */
	state = vm_exec(THIS_VM,
	                state,
	                init_path,
	                init_dentry,
	                (struct regular_node *)init_node,
	                COMPILER_LENOF(init_argv),
	                init_argv,
	                NULL,
	                NULL);
	if (kernel_debugtrap_enabled()) {
		struct debugtrap_reason r;
		r.dtr_signo  = SIGTRAP;
		r.dtr_reason = DEBUGTRAP_REASON_EXEC;
		/* FIXME: Should re-print the path using `path_sprintent()', since the path
		 *        given by the bootloader may be ambiguous (or contain/be a symlink) */
		r.dtr_strarg = kernel_init_binary;
		state = kernel_debugtrap_r(state, &r);
	}
	decref(init_dentry);
	decref(init_path);
	decref(init_node);
	return state;
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_EXEC_C */
