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
#include "exec.c"
#if defined(__x86_64__) && 1
#define MY_PTR(x) __HYBRID_PTR32(x)
#define MY_FUNC(x) compat_##x
#define MY_ELFW COMPAT_ELFW
#define MY_ElfW COMPAT_ElfW
#define MY_EXEC_ARGV_SIZE 1
#define MY_POINTERSIZE 4
#else
#define MY_PTR(x) x *
#define MY_FUNC(x) x
#define MY_ELFW ELFW
#define MY_ElfW ElfW
#define MY_POINTERSIZE __SIZEOF_POINTER__
#endif
#endif /* __INTELLISENSE__ */

DECL_BEGIN

LOCAL WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3, 4, 5, 10)) struct icpustate *KCALL
MY_FUNC(vm_exec_impl)(struct vm *__restrict effective_vm,
                      struct icpustate *__restrict user_state,
                      struct path *__restrict exec_path,
                      struct directory_entry *__restrict exec_dentry,
                      struct regular_node *__restrict exec_node,
                      size_t argc_inject, KERNEL char const *const *argv_inject,
#ifdef MY_EXEC_ARGV_SIZE
                      USER CHECKED void const *argv,
                      USER CHECKED void const *envp,
#else /* MY_EXEC_ARGV_SIZE */
                      USER UNCHECKED MY_PTR(char const) USER CHECKED const *argv,
                      USER UNCHECKED MY_PTR(char const) USER CHECKED const *envp,
#endif /* !MY_EXEC_ARGV_SIZE */
                      MY_ElfW(Ehdr) const *__restrict ehdr
#ifdef MY_EXEC_ARGV_SIZE
                      ,
                      bool argv_is_compat
#endif /* MY_EXEC_ARGV_SIZE */
                      )
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR) {
	MY_ElfW(Phdr) *phdr_vector;
	phdr_vector = (MY_ElfW(Phdr) *)malloca(ehdr->e_phnum * sizeof(MY_ElfW(Phdr)));
	TRY {
		struct vmb builder = VMB_INIT;
		PAGEDIR_PAGEALIGNED UNCHECKED void *peb_base;
		PAGEDIR_PAGEALIGNED UNCHECKED void *stack_base;
		PAGEDIR_PAGEALIGNED UNCHECKED void *linker_base;
		uintptr_t loadstart = (uintptr_t)-1;
		TRY {
			bool need_dyn_linker = false;
			linker_base = (UNCHECKED void *)-1;
			MY_ElfW(Half) i;
			/* Read the program segment header table into memory. */
			inode_readall(exec_node,
			              phdr_vector,
			              ehdr->e_phnum * sizeof(MY_ElfW(Phdr)),
			              (pos_t)ehdr->e_phoff);

			/* Load program headers. */
			for (i = 0; i < ehdr->e_phnum; ++i) {
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
					bss_start        = (void *)(uintptr_t)(phdr_vector[i].p_vaddr + phdr_vector[i].p_filesz);
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
					map_ok = vmb_paged_mapat(&builder,
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
							if unlikely(vmb_getnodeofpageid(&builder, bss_overlap_page) != NULL)
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
						map_ok = vmb_paged_mapat(&builder,
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
				linker_base = vmb_map(&builder,
				                      HINT_GETADDR(KERNEL_VMHINT_USER_DYNLINK),
				                      MY_FUNC(elfexec_system_rtld_size),
				                      PAGESIZE,
#if !defined(NDEBUG) && 1 /* XXX: Remove me */
				                      VM_GETFREE_ABOVE,
#else
				                      HINT_GETMODE(KERNEL_VMHINT_USER_DYNLINK),
#endif
				                      &MY_FUNC(elfexec_system_rtld_file).rf_block,
				                      0,
				                      VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXEC | VM_PROT_PRIVATE,
				                      VM_NODE_FLAG_NORMAL,
				                      0);
			}

#define USER_STACK_NUM_PAGES 8 /* TODO: Don't put this here! */
			/* Allocate a new user-space stack for the calling thread. */
			stack_base = vmb_map(&builder,
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
#ifdef MY_EXEC_ARGV_SIZE
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
			if (argv_is_compat)
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
			if (!argv_is_compat)
#else
#error "Unsupported `__ARCH_COMPAT_SIZEOF_POINTER'"
#endif
			{
				typedef USER UNCHECKED PTR32(char const) USER CHECKED const *vec_t;
#if MY_POINTERSIZE == 4
				peb_base = vmb_alloc_peb32_p32(&builder,
				                               argc_inject,
				                               argv_inject,
				                               (vec_t)argv,
				                               (vec_t)envp);
#else /* MY_POINTERSIZE == 4 */
				peb_base = vmb_alloc_peb64_p32(&builder,
				                               argc_inject,
				                               argv_inject,
				                               (vec_t)argv,
				                               (vec_t)envp);
#endif /* MY_POINTERSIZE != 4 */
			} else {
				typedef USER UNCHECKED PTR64(char const) USER CHECKED const *vec_t;
#if MY_POINTERSIZE == 4
				peb_base = vmb_alloc_peb32_p64(&builder,
				                               argc_inject,
				                               argv_inject,
				                               (vec_t)argv,
				                               (vec_t)envp);
#else /* MY_POINTERSIZE == 4 */
				peb_base = vmb_alloc_peb64_p64(&builder,
				                               argc_inject,
				                               argv_inject,
				                               (vec_t)argv,
				                               (vec_t)envp);
#endif /* MY_POINTERSIZE != 4 */
			}
#else /* MY_EXEC_ARGV_SIZE */
			peb_base = MY_FUNC(vmb_alloc_peb)(&builder,
			                                  argc_inject,
			                                  argv_inject,
			                                  argv,
			                                  envp);
#endif /* !MY_EXEC_ARGV_SIZE */

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
		user_state = MY_FUNC(elfexec_init_entry)(user_state,
		                                         ehdr,
		                                         peb_base,
		                                         stack_base,
		                                         USER_STACK_NUM_PAGES * PAGESIZE,
		                                         (USER void *)(uintptr_t)ehdr->e_entry,
		                                         linker_base != (void *)-1);

		/* Initialize the RTLD portion of the user-space bootstrap process. */
		if (linker_base != (void *)-1) {
			user_state = MY_FUNC(elfexec_init_rtld)(/* user_state:           */ user_state,
			                                        /* exec_path:            */ exec_path,
			                                        /* exec_dentry:          */ exec_dentry,
			                                        /* exec_node:            */ exec_node,
			                                        /* ehdr:                 */ ehdr,
			                                        /* phdr_vec:             */ phdr_vector,
			                                        /* phdr_cnt:             */ ehdr->e_phnum,
			                                        /* application_loadaddr: */ (void *)0,
			                                        /* linker_loadaddr:      */ linker_base);
		}
		{
			/* Initialize the library definitions list to use the PEB
			 * NOTE: When libdl was linked into the mix (see line above), then
			 *       it will override this fairly early on with its own version. */
			struct library_listdef *lld = &FORVM(effective_vm, thisvm_library_listdef);
			memcpy(lld, &peb_based_library_list, sizeof(struct library_listdef));
			lld->lld_first                     = peb_base;
			lld->lld_module_offsetof_loadstart = loadstart;
			/* TODO: Somehow include the RTLD in the initial library list! */
		}
	} EXCEPT {
		freea(phdr_vector);
		RETHROW();
	}
	freea(phdr_vector);
	return user_state;
}

DECL_END

#undef MY_PTR
#undef MY_FUNC
#undef MY_ELFW
#undef MY_ElfW
#undef MY_SYSTEM_RTLD_SIZE
#undef MY_SYSTEM_RTLD_FILE
#undef MY_EXEC_ARGV_SIZE
#undef MY_POINTERSIZE
