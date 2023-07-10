/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODPE_PE_C
#define GUARD_MODPE_PE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/execabi.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/fs.h>
#include <kernel/fs/path.h>
#include <kernel/mman/execinfo.h>
#include <kernel/mman/flags.h>
#include <kernel/mman/mbuilder.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/ramfile.h>
#include <kernel/printk.h>
#include <kernel/rand.h>
#include <kernel/x86/gdt.h>
#include <sched/x86/eflags-mask.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <kos/except.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <nt/pe.h>

#include <assert.h>
#include <format-printer.h>
#include <inttypes.h>
#include <malloca.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/**/
#include "pe.h"

DECL_BEGIN

/* Check if a given `PIMAGE_SECTION_HEADER x' should be mapped. */
#define SHOULD_USE_IMAGE_SECTION_HEADER(x)                                  \
	(((x)->VirtualAddress + (x)->Misc.VirtualSize) > (x)->VirtualAddress && \
	 !((x)->Characteristics & (IMAGE_SCN_LNK_INFO | IMAGE_SCN_LNK_REMOVE)))


/* Populate a given `effective_vm' by loading an PE executable file. */
INTERN WUNUSED NONNULL((1)) unsigned int FCALL
peabi_exec(/*in|out*/ struct execargs *__restrict args) {
	struct mbuilder builder;
	uint32_t e_lfanew; /* IMAGE_DOS_HEADER::e_lfanew */
	IMAGE_NT_HEADERSX nt;
	size_t nthdr_size;
	PIMAGE_SECTION_HEADER shdr;
	pos_t shdr_off;
	size_t i;
	uintptr_t loadaddr;
	uintptr_t load_minaddr;
	uintptr_t load_maxaddr;
#ifdef __x86_64__
	size_t sizeof_pointer = 8;
#define IS_NATIVE (sizeof_pointer & 8)
#define HAS_OPTIONAL_HEADER(field)                                                                 \
	(IS_NATIVE ? nt.FileHeader.SizeOfOptionalHeader >= offsetafter(IMAGE_OPTIONAL_HEADER64, field) \
	           : nt.FileHeader.SizeOfOptionalHeader >= offsetafter(IMAGE_OPTIONAL_HEADER32, field))
#define GET_OPTIONAL_HEADER(field) (IS_NATIVE ? nt.OptionalHeader64.field : nt.OptionalHeader32.field)
#else /* __x86_64__ */
#define sizeof_pointer             sizeof(void *)
#define HAS_OPTIONAL_HEADER(field) (nt.FileHeader.SizeOfOptionalHeader >= offsetafter(IMAGE_OPTIONAL_HEADER32, field))
#define GET_OPTIONAL_HEADER(field) (nt.OptionalHeader32.field)
#endif /* !__x86_64__ */

	/* Base addresses for user-space. */
	USER CHECKED void *libdl_base;
	USER CHECKED void *peb_base;
	USER CHECKED void *stack_base;

	/* Read offset of NT header */
	mfile_readall(args->ea_xfile, &e_lfanew, sizeof(e_lfanew),
	              (pos_t)offsetof(IMAGE_DOS_HEADER, e_lfanew));
	nthdr_size = mfile_read(args->ea_xfile, &nt, sizeof(nt), (pos_t)e_lfanew);
	if (nthdr_size < offsetof(IMAGE_NT_HEADERSX, OptionalHeader32))
		return EXECABI_EXEC_NOTBIN;

	/* Check the NT header. */
	if (nt.Signature != IMAGE_NT_SIGNATURE)
		return EXECABI_EXEC_NOTBIN;
	if (nt.FileHeader.Machine != IMAGE_FILE_MACHINE_HOST) {
#ifdef __x86_64__
		sizeof_pointer = 4;
		if (nt.FileHeader.Machine != IMAGE_FILE_MACHINE_I386)
#endif /* __x86_64__ */
		{
			return EXECABI_EXEC_NOTBIN; /* TODO: THROW */
		}
	}

	 /* Make sure there are sections. */
	if (nt.FileHeader.NumberOfSections == 0)
		return EXECABI_EXEC_NOTBIN; /* TODO: THROW */

	/* Limit the max number of sections. */
	if (nt.FileHeader.NumberOfSections > 0xff)
		return EXECABI_EXEC_NOTBIN; /* TODO: THROW */

	/* Load section headers. */
	shdr = (PIMAGE_SECTION_HEADER)malloca(nt.FileHeader.NumberOfSections,
	                                      sizeof(IMAGE_SECTION_HEADER));
	RAII_FINALLY { freea(shdr); };
	shdr_off = (pos_t)e_lfanew;
	shdr_off += offsetof(IMAGE_NT_HEADERSX, OptionalHeader32);
	shdr_off += nt.FileHeader.SizeOfOptionalHeader;
	mfile_readall(args->ea_xfile, shdr,
	              nt.FileHeader.NumberOfSections *
	              sizeof(IMAGE_SECTION_HEADER),
	              shdr_off);

	/* Figure out how many optional headers we got. */
	nthdr_size -= offsetof(IMAGE_NT_HEADERSX, OptionalHeader32);
	if (nt.FileHeader.SizeOfOptionalHeader > nthdr_size)
		nt.FileHeader.SizeOfOptionalHeader = nthdr_size;

	/* ASLR support */
	{
		uintptr_t min_okaddr;
		uintptr_t max_okaddr;
		size_t total_size;
		load_minaddr = (uintptr_t)-1;
		load_maxaddr = (uintptr_t)0;
		for (i = 0; i < nt.FileHeader.NumberOfSections; ++i) {
			uintptr_t sect_minaddr, sect_maxaddr;
			PIMAGE_SECTION_HEADER section = &shdr[i];
			if (!SHOULD_USE_IMAGE_SECTION_HEADER(section))
				continue; /* Skip! */
			sect_minaddr = section->VirtualAddress;
			sect_maxaddr = sect_minaddr;
			if (OVERFLOW_UADD(sect_maxaddr, section->Misc.VirtualSize - 1, &sect_maxaddr))
				sect_maxaddr = (uintptr_t)-1;
			if (load_minaddr > sect_minaddr)
				load_minaddr = sect_minaddr;
			if (load_maxaddr < sect_maxaddr)
				load_maxaddr = sect_maxaddr;
		}
		load_minaddr = FLOOR_ALIGN(load_minaddr, PAGESIZE);
		load_maxaddr = CEIL_ALIGN(load_maxaddr + 1, PAGESIZE) - 1;
		total_size   = (load_maxaddr + 1) - load_minaddr;
#ifdef KERNELSPACE_HIGHMEM
		min_okaddr = 0;
#ifdef __x86_64__
		if (OVERFLOW_USUB(IS_NATIVE ? USERSPACE_END
		                            : COMPAT_USERSPACE_END,
		                  total_size, &max_okaddr))
			return EXECABI_EXEC_NOTBIN; /* TODO: THROW */
#else /* __x86_64__ */
		if (OVERFLOW_USUB(USERSPACE_END, total_size, &max_okaddr))
			return EXECABI_EXEC_NOTBIN; /* TODO: THROW */
#endif /* !__x86_64__ */
#else /* KERNELSPACE_HIGHMEM */
#error "Invalid configuration"
#endif /* !KERNELSPACE_HIGHMEM */

		loadaddr = 0;
		if (HAS_OPTIONAL_HEADER(ImageBase))
			loadaddr = load_minaddr + GET_OPTIONAL_HEADER(ImageBase);
		if (!(nt.FileHeader.Characteristics & IMAGE_FILE_RELOCS_STRIPPED) &&
		    (loadaddr == 0 || ((krand() & 7) <= 2))) {
			if (loadaddr == 0)
				loadaddr = 0x08048000;
			/* Choose a random address, centered around `loadaddr'. */
			/* TODO */
		}
		if (loadaddr < min_okaddr)
			loadaddr = min_okaddr;
		if (loadaddr > max_okaddr)
			loadaddr = max_okaddr;

		/* Adjust load address for start of first section. */
		loadaddr -= load_minaddr;
	}

	/* Map sections */
	mbuilder_init(&builder);
	{
		struct mramfile *libdl;
		RAII_FINALLY { mbuilder_fini(&builder); };
		if (load_minaddr != 0) {
			/* Must inject another section to map file contents
			 * starting  at `0' and going up to `load_minaddr'.
			 *
			 * Some PE programs will directly access their own program headers,
			 * even though the values of those headers could as well have  just
			 * been hard-coded, but whatever... This  is needed to get  certain
			 * programs running. */
			mbuilder_map(&builder, (void *)loadaddr,
			             load_minaddr, PROT_READ,
			             MAP_FIXED | MAP_FIXED_NOREPLACE,
			             args->ea_xfile, args->ea_xpath,
			             args->ea_xdentry, (pos_t)0);
		}

		for (i = 0; i < nt.FileHeader.NumberOfSections; ++i) {
			unsigned int prot;
			PIMAGE_SECTION_HEADER section = &shdr[i];
			uintptr_t sectaddr;
			if (!SHOULD_USE_IMAGE_SECTION_HEADER(section))
				continue; /* Skip! */

			/* Force page alignment. */
			if (section->VirtualAddress & PAGEMASK) {
				section->Misc.VirtualSize += section->VirtualAddress & PAGEMASK;
				if (section->SizeOfRawData) {
					section->PointerToRawData -= section->VirtualAddress & PAGEMASK;
					section->SizeOfRawData += section->VirtualAddress & PAGEMASK;
				}
				section->VirtualAddress &= ~PAGEMASK;
			}
			if (section->Misc.VirtualSize & PAGEMASK) {
				bool was_ge;
				size_t addend;
				addend = PAGESIZE - (section->Misc.VirtualSize & PAGEMASK);
				was_ge = section->SizeOfRawData >= section->Misc.VirtualSize;
				section->Misc.VirtualSize += addend;
				if (was_ge)
					section->SizeOfRawData = section->Misc.VirtualSize;
			}
			if (section->SizeOfRawData > section->Misc.VirtualSize)
				section->SizeOfRawData = section->Misc.VirtualSize;

			/* Determine section protection. */
			prot = IMAGE_SCN_ASPROT(section->Characteristics);
			prot |= PROT_WRITE; /* Write protection is later removed by `libdl-pe.so' */

			/* Map section */
			sectaddr = loadaddr + section->VirtualAddress;
			assert(IS_ALIGNED((uintptr_t)sectaddr, PAGESIZE));
			printk(KERN_DEBUG "[pe] section[%" PRIuSIZ "] = %q @ %p-%p (%c%c%c%c)\n",
			       i, section->Name, sectaddr, sectaddr + section->Misc.VirtualSize - 1,
			       prot & PROT_READ ? 'r' : '-', prot & PROT_WRITE ? 'w' : '-',
			       prot & PROT_EXEC ? 'x' : '-', prot & PROT_SHARED ? 's' : 'p');
			if (section->Misc.VirtualSize > section->SizeOfRawData) {
				uintptr_t bss_start = section->SizeOfRawData;
				uintptr_t bss_size  = section->Misc.VirtualSize - section->SizeOfRawData;
				if (bss_start & PAGEMASK) {
					struct mbnode *node;
					pos_t head_fpos;
					byte_t *addr;
					section->SizeOfRawData &= ~PAGEMASK; /* Adjust for leading page. */
					addr = (byte_t *)(sectaddr + section->SizeOfRawData);
					node = mbuilder_mappings_locate(&builder, addr);
					if unlikely(node != NULL) {
						THROW(E_BADALLOC_ADDRESS_ALREADY_EXISTS,
						      addr, addr + PAGEMASK,
						      node->mbn_minaddr, node->mbn_maxaddr);
					}

					/* Construct partial bss page. */
					head_fpos = (pos_t)section->PointerToRawData + section->SizeOfRawData;
					node = mbnode_create_partialbss(args->ea_xfile, head_fpos,
					                                bss_start & PAGEMASK);

					/* Fill in missing fields. */
					node->mbn_minaddr = addr;
					node->mbn_maxaddr = addr + PAGEMASK;
					node->mbn_flags   = mnodeflags_from_prot(prot);
					mbuilder_insert_fmnode(&builder, node);

					/* Everything after the partial-bss page is mapped as normal .bss */
					bss_start += PAGEMASK;
					bss_start &= ~PAGEMASK;
					if (bss_start >= section->Misc.VirtualSize)
						goto done_bss;
					bss_size = section->Misc.VirtualSize - bss_start;
				}

				/* Map normal .bss */
				mbuilder_map(&builder, (void *)(sectaddr + bss_start),
				             bss_size, prot & ~PROT_SHARED,
				             MAP_FIXED | MAP_FIXED_NOREPLACE,
				             &mfile_zero);
			}
done_bss:
			if (section->SizeOfRawData) {
				pos_t offset = (pos_t)section->PointerToRawData;
				if (offset & PAGEMASK) {
					/* Custom mfile to lazily load data from a miss-aligned file offset. */
					REF struct mfile *wrapper;
					wrapper = mfile_create_misaligned_wrapper(args->ea_xfile, offset);
					FINALLY_DECREF_UNLIKELY(wrapper);
					mbuilder_map(&builder, (void *)sectaddr,
					             section->SizeOfRawData, prot,
					             MAP_FIXED | MAP_FIXED_NOREPLACE,
					             wrapper, args->ea_xpath,
					             args->ea_xdentry, (pos_t)0);
				} else {
					mbuilder_map(&builder, (void *)sectaddr,
					             section->SizeOfRawData, prot,
					             MAP_FIXED | MAP_FIXED_NOREPLACE,
					             args->ea_xfile, args->ea_xpath,
					             args->ea_xdentry,
					             (pos_t)offset);
				}
			}
		}

		/* Load libdl and tell it  to dispatch library loading to  a
		 * secondary helper library (libdl-pe.so) that represents an
		 * extension  to libdl, as well as handles all of the module
		 * initialization.
		 *
		 * NOTE: Unlike for ELF, in  the case of PE  we can do this  entirely
		 *       unconditional. You might argue that  a PE program that  does
		 *       not include any import dependencies, loaded at its preferred
		 *       address or simply not including any relocation, wouldn't  be
		 *       needing a dynamic linker. -- But you'd be wrong:
		 * The primary entry of PE programs is allowed to return normally, in
		 * which case it must trigger a  call to `_Exit(%Pax)'. For this,  we
		 * need a user-space  support library that  provides the landing  pad
		 * where a returning entry point function will jump to. So even if it
		 * wasn't for the fact that figuring out the need of dynamic  linking
		 * is a super complicated  thing to do for  PE, we'd still need  more
		 * user-space support for full compliance.
		 *
		 * -> In the end, it's just easier to always load the dynamic linker,
		 *    especially  since doing  most of  the work  in user-space makes
		 *    writing code easier (because driver  code like this comment  is
		 *    part of is much more prone to errors, which more often than not
		 *    can go so far as to turn into security problems). */
		libdl = &execabi_system_rtld_file;
#ifdef __x86_64__
		if (!IS_NATIVE)
			libdl = &compat_execabi_system_rtld_file;
#endif /* __x86_64__ */

		libdl_base = mbuilder_map(/* self:        */ &builder,
		                          /* hint:        */ MHINT_GETADDR(KERNEL_MHINT_USER_DYNLINK),
		                          /* num_bytes:   */ (size_t)_atomic64_val(libdl->mrf_file.mf_filesize),
		                          /* prot:        */ PROT_READ | PROT_WRITE | PROT_EXEC,
#if !defined(NDEBUG) && 1 /* XXX: Remove me */
		                          /* flags:       */ MAP_GROWSUP | MAP_NOASLR,
#else
		                          /* flags:       */ MHINT_GETMODE(KERNEL_MHINT_USER_DYNLINK),
#endif
		                          /* file:        */ &libdl->mrf_file,
		                          /* file_fspath: */ NULL,
		                          /* file_fsname: */ NULL,
		                          /* file_pos:    */ 0);

		/* Allocate the PEB */
#ifdef __x86_64__
		peb_base = IS_NATIVE
		           ? mbuilder_alloc_peb_from_execargs(&builder, args)
		           : mbuilder_alloc_compatpeb_from_execargs(&builder, args);
#else /* __x86_64__ */
		peb_base = mbuilder_alloc_peb_from_execargs(&builder, args);
#endif /* !__x86_64__ */

		/* Allocate a new user-space stack for the calling thread. */
#define USER_STACK_SIZE (64 * PAGESIZE) /* TODO: Don't put this here! */
		stack_base = mbuilder_map(/* self:      */ &builder,
		                          /* hint:      */ MHINT_GETADDR(KERNEL_MHINT_USER_STACK),
		                          /* num_bytes: */ USER_STACK_SIZE,
		                          /* prot:      */ PROT_READ | PROT_WRITE,
		                          /* flags:     */ MHINT_GETMODE(KERNEL_MHINT_USER_STACK),
		                          /* file:      */ &mfile_zero);

		/* Apply  the newly  loaded binary  to the  given VM and
		 * terminate all threads using it except for the caller. */
		{
			struct mexecinfo ei;
			ei.mei_file = args->ea_xfile;
			ei.mei_dent = args->ea_xdentry;
			ei.mei_path = args->ea_xpath;
			ei.mei_peb  = peb_base;
#ifdef __ARCH_HAVE_COMPAT
			ei.mei_peb_iscompat = !IS_NATIVE;
#endif /* __ARCH_HAVE_COMPAT */
			mbuilder_apply(&builder,
			               args->ea_mman,
			               MBUILDER_APPLY_AA_TERMTHREADS |
			               MBUILDER_APPLY_AA_SETEXECINFO,
			               &ei);
		}
	} /* Scope (for `mbuilder_fini()') */

	{
		byte_t USER CHECKED *stack_end;
		REF struct mman *oldmman = THIS_MMAN;
		struct icpustate *state;

		/* Change the calling thread's mman to `args->ea_mman' */
		if (oldmman != args->ea_mman) {
			incref(oldmman);
			task_setmman(args->ea_mman);
		}
		TRY {
			size_t buflen;
			void *entrypoint;
			/* Pass important information onto the stack
			 * and set-up the user-space register state. */
			stack_end = (byte_t USER CHECKED *)stack_base + USER_STACK_SIZE;
#ifdef __x86_64__
#define PUSHP(val)                                                                        \
	(stack_end -= sizeof_pointer,                                                         \
	 IS_NATIVE ? (void)(*(USER CHECKED uint64_t *)stack_end = (uint64_t)(uintptr_t)(val)) \
	           : (void)(*(USER CHECKED uint32_t *)stack_end = (uint32_t)(uintptr_t)(val)))
#else /* __x86_64__ */
#define PUSHP(val) (void)(stack_end -= sizeof(uintptr_t), *(USER CHECKED uintptr_t *)stack_end = (uintptr_t)(val))
#endif /* !__x86_64__ */


			/* Push: `struct peexec_info::ei_entry' */
			entrypoint = (void *)(loadaddr + GET_OPTIONAL_HEADER(AddressOfEntryPoint));
			if unlikely(!HAS_OPTIONAL_HEADER(AddressOfEntryPoint))
				entrypoint = (void *)(loadaddr + load_minaddr);
			PUSHP(entrypoint);

			/* Push: `struct peexec_info::pi_pe.pd_name' */
			buflen = 0;
			for (;;) {
				bool ok;
				size_t reqlen;
				if (args->ea_xpath && args->ea_xdentry) {
					REF struct path *myroot = fs_getroot(THIS_FS);
					FINALLY_DECREF_UNLIKELY(myroot);
					reqlen = path_sprintent(args->ea_xpath,
					                        args->ea_xdentry->fd_name,
					                        args->ea_xdentry->fd_namelen,
					                        (USER char *)stack_end - buflen,
					                        buflen, AT_PATHPRINT_INCTRAIL, myroot);
				} else if (args->ea_xdentry) {
					reqlen = snprintf((USER char *)stack_end - buflen, buflen,
					                  "%$s", (size_t)args->ea_xdentry->fd_namelen,
					                  args->ea_xdentry->fd_name) +
					         1;
				} else {
					reqlen = 1;
					if (buflen)
						((USER char *)stack_end - buflen)[0] = '\0';
				}
				ok     = reqlen <= buflen;
				buflen = (reqlen + sizeof_pointer - 1) & ~(sizeof_pointer - 1);
				if (ok)
					break;
			}
			stack_end -= buflen;

			/* Push: `struct peexec_info::pi_pe.pd_sect' */
			stack_end -= nt.FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER);
			memcpy(stack_end, shdr, nt.FileHeader.NumberOfSections, sizeof(IMAGE_SECTION_HEADER));

			/* Push: `struct peexec_info::pi_pe.pd_nt' */
			buflen = offsetof(IMAGE_NT_HEADERSX, OptionalHeader32) + nt.FileHeader.SizeOfOptionalHeader;
			stack_end -= CEIL_ALIGN(buflen, sizeof_pointer);
			memcpy(stack_end, &nt, buflen);

			/* Push: `struct peexec_info::pi_pe.pd_loadmax' */
			PUSHP(loadaddr + load_maxaddr);

			/* Push: `struct peexec_info::pi_pe.pd_loadmin' */
			PUSHP(loadaddr /* + load_minaddr*/);

			/* Push: `struct peexec_info::pi_pnum' and `pi_libdl_pe' */
#ifdef __x86_64__
			if (IS_NATIVE) {
				static char const libdl_pe[] = "\xFF\xFF" /* pi_pnum */
				                               "/lib64/libdl-pe.so";
				stack_end -= CEIL_ALIGN(sizeof(libdl_pe), 8);
				memcpy(stack_end, libdl_pe, sizeof(libdl_pe));
			} else
#endif /* __x86_64__ */
			{
				static char const libdl_pe[] = "\xFF\xFF" /* pi_pnum */
				                               "/lib/libdl-pe.so";
				stack_end -= CEIL_ALIGN(sizeof(libdl_pe), 4);
				memcpy(stack_end, libdl_pe, sizeof(libdl_pe));
			}

			/* Push: `struct peexec_info::pi_rtldaddr' */
			PUSHP(libdl_base);
		} EXCEPT {
			if (oldmman != args->ea_mman)
				task_setmman_inherit(oldmman);
			RETHROW();
		}

		COMPILER_BARRIER();
		/* ===== Point of no return
		 * This is where we begin to modify user-level registers.
		 * This  may  _only_ happen  _after_ we're  done touching
		 * user-space memory! */
		state = args->ea_state;
#ifdef __x86_64__
		if (IS_NATIVE) {
			uint64_t addr = x86_get_random_userkern_address();
			x86_set_user_gsbase(addr);                               /* re-roll the ukern address. */
			gpregs_setpdi(&state->ics_gpregs, (uintptr_t)stack_end); /* ELF_ARCHX86_64_DL_RTLDDATA_REGISTER */
			gpregs_setpsi(&state->ics_gpregs, (uintptr_t)loadaddr);  /* ELF_ARCHX86_64_DL_LOADADDR_REGISTER */
			gpregs_setpdx(&state->ics_gpregs, (uintptr_t)peb_base);  /* ELF_ARCHX86_64_PEB_REGISTER */
			gpregs_setpbp(&state->ics_gpregs, (uintptr_t)peb_base);  /* ELF_ARCHX86_64_PEB_REGISTER2 */
		} else
#endif /* __x86_64__ */
		{
			uint32_t addr = x86_get_random_userkern_address32();
			x86_set_user_fsbase(addr);                                /* re-roll the ukern address. */
			gpregs_setpcx(&state->ics_gpregs, (uintptr_t)stack_end);  /* ELF_ARCH386_DL_RTLDDATA_REGISTER */
			gpregs_setpdx(&state->ics_gpregs, (uintptr_t)loadaddr);   /* ELF_ARCH386_DL_LOADADDR_REGISTER */
			gpregs_setpbp(&state->ics_gpregs, (uintptr_t)peb_base);   /* ELF_ARCH386_PEB_REGISTER */
		}
		icpustate_setusersp(state, stack_end);
		icpustate_setpc(state, libdl_base); /* Entry point is at offset=0 */
		{
			union x86_user_eflags_mask_union mask;
			mask.uem_word = atomic64_read(&x86_exec_eflags_mask);
			/* Mask eflags for exec() */
			icpustate_mskpflags(state, mask.uem_mask, mask.uem_flag);
		}

#ifdef __x86_64__
		if (IS_NATIVE) {
			icpustate_setcs(state, SEGMENT_USER_CODE64_RPL);
			icpustate_setss(state, SEGMENT_USER_DATA64_RPL);
		} else {
			icpustate_setcs(state, SEGMENT_USER_CODE32_RPL);
			icpustate_setss(state, SEGMENT_USER_DATA32_RPL);
		}
#endif /* __x86_64__ */

		if (oldmman != args->ea_mman) {
			if unlikely(!args->ea_change_mman_to_effective_mman)
				task_setmman(oldmman);
			decref(oldmman);
		}
	}
	return EXECABI_EXEC_SUCCESS;
}



#ifndef BUILDING_KERNEL_CORE
PRIVATE struct execabi peabi = EXECABI_INIT_PE;
PRIVATE DRIVER_INIT void KCALL init(void) {
	execabis_register(&peabi);
}
#endif /* BUILDING_KERNEL_CORE */

DECL_END

#endif /* !GUARD_MODPE_PE_C */
