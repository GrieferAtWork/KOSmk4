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
#include "elf.c"
#if defined(__x86_64__) && 1
#define LOCAL_PTR(x) __HYBRID_PTR32(x)
#define LOCAL_FUNC(x) compat_##x
#define LOCAL_ELFW COMPAT_ELFW
#define LOCAL_ElfW COMPAT_ElfW
#define LOCAL_EXEC_ARGV_SIZE 1
#define LOCAL_POINTERSIZE 4
#else /* __x86_64__ */
#define LOCAL_PTR(x) x *
#define LOCAL_FUNC(x) x
#define LOCAL_ELFW ELFW
#define LOCAL_ElfW ElfW
#define LOCAL_POINTERSIZE __SIZEOF_POINTER__
#endif /* !__x86_64__ */
#endif /* __INTELLISENSE__ */

#include <kernel/execabi.h>
#include <kernel/mman/execinfo.h>
#include <kernel/mman/flags.h>
#include <kernel/mman/ramfile.h>

#ifdef LOCAL_EXEC_ARGV_SIZE
#define LOCAL_STRINGARRAY_TYPE USER CHECKED void const *
#else /* LOCAL_EXEC_ARGV_SIZE */
#define LOCAL_STRINGARRAY_TYPE USER UNCHECKED LOCAL_PTR(char const) USER CHECKED const *
#endif /* !LOCAL_EXEC_ARGV_SIZE */

DECL_BEGIN

LOCAL WUNUSED NONNULL((1)) unsigned int FCALL
LOCAL_FUNC(elf_exec_impl)(/*in|out*/ struct execargs *__restrict args)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR) {
	LOCAL_ElfW(Ehdr) *ehdr;
	LOCAL_ElfW(Phdr) *phdr_vector;
	ehdr        = (LOCAL_ElfW(Ehdr) *)args->ea_header;
	phdr_vector = (LOCAL_ElfW(Phdr) *)malloca(ehdr->e_phnum * sizeof(LOCAL_ElfW(Phdr)));
	TRY {
		struct mbuilder builder;
		PAGEDIR_PAGEALIGNED UNCHECKED void *peb_base;
		PAGEDIR_PAGEALIGNED UNCHECKED void *stack_base;
		PAGEDIR_PAGEALIGNED UNCHECKED void *linker_base;
		uintptr_t loadstart = (uintptr_t)-1;
		mbuilder_init(&builder);
		TRY {
			bool need_dyn_linker = false;
			linker_base = (UNCHECKED void *)-1;
			LOCAL_ElfW(Half) i;
			/* Read the program segment header table into memory. */
			inode_readall(args->ea_xnode,
			              phdr_vector,
			              ehdr->e_phnum * sizeof(LOCAL_ElfW(Phdr)),
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
					byte_t *loadaddr;
					size_t fil_bytes, mem_bytes;
					uintptr_half_t prot;
					size_t adjusted_filsize;
					size_t adjusted_memsize;
					void *bss_start;
					/* Load entry into memory. */
					if ((phdr_vector[i].p_offset & PAGEMASK) !=
					    (phdr_vector[i].p_vaddr & PAGEMASK)) {
						THROW(E_NOT_EXECUTABLE_FAULTY,
						      E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF,
						      E_NOT_EXECUTABLE_FAULTY_REASON_ELF_UNALIGNEDSEGMENT);
					}
					loadaddr = (byte_t *)((uintptr_t)phdr_vector[i].p_vaddr & ~PAGEMASK);
					if (loadstart > phdr_vector[i].p_vaddr)
						loadstart = phdr_vector[i].p_vaddr;
					adjusted_filsize = (size_t)phdr_vector[i].p_filesz + (phdr_vector[i].p_vaddr & PAGEMASK);
					adjusted_memsize = (size_t)phdr_vector[i].p_memsz + (phdr_vector[i].p_vaddr & PAGEMASK);
					fil_bytes        = CEIL_ALIGN(adjusted_filsize, PAGESIZE);
					mem_bytes        = CEIL_ALIGN(adjusted_memsize, PAGESIZE);
					bss_start        = (void *)(uintptr_t)(phdr_vector[i].p_vaddr + phdr_vector[i].p_filesz);
					/* Check if we're going to need a .bss overlap fixup page */
					if (adjusted_memsize > adjusted_filsize) {
						if (((uintptr_t)bss_start & PAGEMASK) != 0)
							fil_bytes -= PAGESIZE;
					}
					prot = prot_from_elfpf(phdr_vector[i].p_flags);
					if (fil_bytes != 0) {
						TRY {
							mbuilder_map(&builder, loadaddr, fil_bytes, prot,
							             MAP_FIXED | MAP_FIXED_NOREPLACE,
							             args->ea_xnode,
							             args->ea_xpath,
							             args->ea_xdentry,
							             (pos_t)(phdr_vector[i].p_offset & ~PAGEMASK));
						} EXCEPT {
							if (was_thrown(E_BADALLOC_ADDRESS_ALREADY_EXISTS))
								goto err_overlap;
							RETHROW();
						}
					}
					if (mem_bytes > fil_bytes) {
						/* LD  sometimes produces really  weird .bss sections  that are neither whole
						 * pages,  nor are placed such that they exist at the end of some given file.
						 * Because  of  this, we  must  manually check  for  segments that  end  in a
						 * small (< PAGESIZE) section of bss memory when that segment doesn't hug the
						 * end of the actual file, and memset() it to all ZEROes.
						 *
						 * Example (filesize == 0x22060):
						 *     Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align
						 *     LOAD           0x000000 0x00000000 0x00000000 0x0e224 0x0e224 R E 0x1000
						 *     LOAD           0x00e224 0x0000f224 0x0000f224 0x000ec 0x000fc RW  0x1000
						 *     DYNAMIC        0x00e228 0x0000f228 0x0000f228 0x000a8 0x000a8 RW  0x4
						 *
						 * The second segment contains  a BSS area  of 0xfc-0xec ==  0x10 bytes at  0xf310...0xf31f
						 * Since this range is still part of the page that gets loaded from disk as a file mapping,
						 * the  associated file mapping at 0xf224...0xf30f is extended to the end of the associated
						 * page at 0xffff (which includes (in this case) the entire .bss section).
						 *
						 * In a case like this where the .bss  area overlaps with the extended file mapping, the  first
						 * page of the .bss area must be re-mapped  as writable (if not already), followed by the  area
						 * `START_OF_BSS ... MIN(MAX_BSS_BYTE, MAX_BYTE_OF_PAGE(PAGE_OF(START_OF_BSS)))' being forcibly
						 * initialized to all ZEROes, causing the page to be faulted and become initialized properly.
						 */
						if (((uintptr_t)bss_start & PAGEMASK) != 0) {
							PAGEDIR_PAGEALIGNED byte_t *bss_overlap_addr;
							size_t bss_start_offset, bss_overlap, bss_total_size;
							struct mbnode *overlap_node;
							assert(phdr_vector[i].p_memsz > phdr_vector[i].p_filesz);
							bss_total_size = phdr_vector[i].p_memsz -
							                 phdr_vector[i].p_filesz;
							bss_start_offset = (size_t)((uintptr_t)bss_start & PAGEMASK);
							bss_overlap = PAGESIZE - bss_start_offset;
							if (bss_overlap > bss_total_size)
								bss_overlap = bss_total_size;
							bss_overlap_addr = loadaddr + fil_bytes;
							if unlikely(mbuilder_mappings_locate(&builder, bss_overlap_addr) != NULL) {
err_overlap:
								/* Already in use... */
								THROW(E_NOT_EXECUTABLE_FAULTY,
								      E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF,
								      E_NOT_EXECUTABLE_FAULTY_REASON_ELF_SEGMENTOVERLAP);
							}
							overlap_node = create_bss_overlap_mbnode(args->ea_xnode,
							                                         (pos_t)(phdr_vector[i].p_offset +
							                                                 phdr_vector[i].p_filesz -
							                                                 bss_start_offset),
							                                         bss_start_offset,
							                                         bss_overlap);
							/* Fill in remaining fields of `overlap_node' */
							overlap_node->mbn_minaddr = bss_overlap_addr;
							overlap_node->mbn_maxaddr = bss_overlap_addr + PAGESIZE - 1;
							overlap_node->mbn_flags   = prot;
							mbuilder_insert_fmnode(&builder, overlap_node);
							fil_bytes += PAGESIZE; /* Adjust to not map the first (special) page of .bss */
							if unlikely(fil_bytes >= mem_bytes)
								goto done_PT_LOAD_bss;
						}
						/* Map BSS as anonymous, zero-initialized memory. */
						TRY {
							mbuilder_map(&builder, loadaddr + fil_bytes,
							             mem_bytes - fil_bytes, prot,
							             MAP_FIXED | MAP_FIXED_NOREPLACE,
							             &mfile_zero);
						} EXCEPT {
							if (was_thrown(E_BADALLOC_ADDRESS_ALREADY_EXISTS))
								goto err_overlap;
							RETHROW();
						}
done_PT_LOAD_bss:
						;
					}
				}	break;

				default:
					need_dyn_linker = true;
					break;
				}
			}
			/* If necessary, load the dynamic linker. */
			if (need_dyn_linker) {
				linker_base = mbuilder_map(/* self:        */ &builder,
				                           /* hint:        */ MHINT_GETADDR(KERNEL_MHINT_USER_DYNLINK),
				                           /* num_bytes:   */ LOCAL_FUNC(execabi_system_rtld_size),
				                           /* prot:        */ PROT_READ | PROT_WRITE | PROT_EXEC,
#if !defined(NDEBUG) && 1 /* XXX: Remove me */
				                           /* flags:       */ MAP_GROWSUP | MAP_NOASLR,
#else
				                           /* flags:       */ MHINT_GETMODE(KERNEL_MHINT_USER_DYNLINK),
#endif
				                           /* file:        */ &LOCAL_FUNC(execabi_system_rtld_file).mrf_file,
				                           /* file_fspath: */ NULL,
				                           /* file_fsname: */ NULL,
				                           /* file_pos:    */ 0);
			}

#define USER_STACK_SIZE (64 * PAGESIZE) /* TODO: Don't put this here! */
			/* Allocate a new user-space stack for the calling thread. */
			stack_base = mbuilder_map(/* self:      */ &builder,
			                          /* hint:      */ MHINT_GETADDR(KERNEL_MHINT_USER_STACK),
			                          /* num_bytes: */ USER_STACK_SIZE,
			                          /* prot:      */ PROT_READ | PROT_WRITE,
			                          /* flags:     */ MHINT_GETMODE(KERNEL_MHINT_USER_STACK),
			                          /* file:      */ &mfile_zero);

			/* Create a memory mapping for the PEB containing `args->ea_argv' and `args->ea_envp' */
#ifdef LOCAL_EXEC_ARGV_SIZE
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
			if (args->ea_argv_is_compat)
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
			if (!args->ea_argv_is_compat)
#else /* __ARCH_COMPAT_SIZEOF_POINTER == ... */
#error "Unsupported `__ARCH_COMPAT_SIZEOF_POINTER'"
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != ... */
			{
				typedef USER UNCHECKED PTR32(char const) USER CHECKED const *vec_t;
#if LOCAL_POINTERSIZE == 4
				peb_base = mbuilder_alloc_peb32_p32(&builder,
				                                    args->ea_argc_inject,
				                                    args->ea_argv_inject,
				                                    (vec_t)args->ea_argv,
				                                    (vec_t)args->ea_envp);
#else /* LOCAL_POINTERSIZE == 4 */
				peb_base = mbuilder_alloc_peb64_p32(&builder,
				                                    args->ea_argc_inject,
				                                    args->ea_argv_inject,
				                                    (vec_t)args->ea_argv,
				                                    (vec_t)args->ea_envp);
#endif /* LOCAL_POINTERSIZE != 4 */
			} else {
				typedef USER UNCHECKED PTR64(char const) USER CHECKED const *vec_t;
#if LOCAL_POINTERSIZE == 4
				peb_base = mbuilder_alloc_peb32_p64(&builder,
				                                    args->ea_argc_inject,
				                                    args->ea_argv_inject,
				                                    (vec_t)args->ea_argv,
				                                    (vec_t)args->ea_envp);
#else /* LOCAL_POINTERSIZE == 4 */
				peb_base = mbuilder_alloc_peb64_p64(&builder,
				                                    args->ea_argc_inject,
				                                    args->ea_argv_inject,
				                                    (vec_t)args->ea_argv,
				                                    (vec_t)args->ea_envp);
#endif /* LOCAL_POINTERSIZE != 4 */
			}
#else /* LOCAL_EXEC_ARGV_SIZE */
			peb_base = LOCAL_FUNC(mbuilder_alloc_peb)(&builder,
			                                          args->ea_argc_inject,
			                                          args->ea_argv_inject,
			                                          (LOCAL_STRINGARRAY_TYPE)args->ea_argv,
			                                          (LOCAL_STRINGARRAY_TYPE)args->ea_envp);
#endif /* !LOCAL_EXEC_ARGV_SIZE */

			/* Apply  the newly  loaded binary  to the  given VM and
			 * terminate all threads using it except for the caller. */
			{
				struct mexecinfo ei;
				ei.mei_node = args->ea_xnode;
				ei.mei_dent = args->ea_xdentry;
				ei.mei_path = args->ea_xpath;
				ei.mei_peb  = peb_base;
#ifdef __ARCH_HAVE_COMPAT
				ei.mei_peb_iscompat = LOCAL_POINTERSIZE != __SIZEOF_POINTER__;
#endif /* __ARCH_HAVE_COMPAT */
				mbuilder_apply(&builder,
				               args->ea_mman,
				               MBUILDER_APPLY_AA_TERMTHREADS |
				               MBUILDER_APPLY_AA_SETEXECINFO,
				               &ei);
			}
		} EXCEPT {
			mbuilder_fini(&builder);
			RETHROW();
		}
		mbuilder_fini(&builder);

		{
			REF struct mman *oldmman = THIS_MMAN;
			/* Change the calling thread's mman to `args->ea_mman' */
			if (oldmman != args->ea_mman) {
				incref(oldmman);
				task_setmman(args->ea_mman);
			}
			TRY {
				size_t ustack_size;
				USER void *entry_pc;
				ustack_size = USER_STACK_SIZE;
				entry_pc    = (USER void *)(uintptr_t)ehdr->e_entry;
				if (linker_base != (void *)-1) {
					/* Initialize such that we make use of the dynamic linker. */
					args->ea_state = LOCAL_FUNC(elfexec_init_rtld)(/* user_state:           */ args->ea_state,
					                                               /* exec_path:            */ args->ea_xpath,
					                                               /* exec_dentry:          */ args->ea_xdentry,
					                                               /* exec_node:            */ args->ea_xnode,
					                                               /* ehdr:                 */ ehdr,
					                                               /* phdr_vec:             */ phdr_vector,
					                                               /* phdr_cnt:             */ ehdr->e_phnum,
					                                               /* application_loadaddr: */ (void *)0,
					                                               /* linker_loadaddr:      */ linker_base,
					                                               /* peb_address:          */ peb_base,
					                                               /* ustack_base:          */ stack_base,
					                                               /* ustack_size:          */ ustack_size,
					                                               /* entry_pc:             */ entry_pc);
				} else {
					/* Set the entry point for the loaded binary. */
					args->ea_state = LOCAL_FUNC(elfexec_init_entry)(args->ea_state,
					                                                ehdr,
					                                                peb_base,
					                                                stack_base,
					                                                ustack_size,
					                                                entry_pc);
				}
			} EXCEPT {
				if (oldmman != args->ea_mman)
					task_setmman_inherit(oldmman);
				RETHROW();
			}
			if (oldmman != args->ea_mman) {
				if unlikely(!args->ea_change_mman_to_effective_mman)
					task_setmman(oldmman);
				decref(oldmman);
			}
		}
	} EXCEPT {
		freea(phdr_vector);
		RETHROW();
	}
	freea(phdr_vector);
	return EXECABI_EXEC_SUCCESS;
}

DECL_END

#undef LOCAL_STRINGARRAY_TYPE
#undef LOCAL_PTR
#undef LOCAL_FUNC
#undef LOCAL_ELFW
#undef LOCAL_ElfW
#undef LOCAL_SYSTEM_RTLD_SIZE
#undef LOCAL_SYSTEM_RTLD_FILE
#undef LOCAL_EXEC_ARGV_SIZE
#undef LOCAL_POINTERSIZE
