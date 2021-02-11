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
#ifndef GUARD_MODELFEXEC_ARCH_I386_ELF_C
#define GUARD_MODELFEXEC_ARCH_I386_ELF_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/except.h>
#include <kernel/types.h>
#include <kernel/vm.h>
#include <kernel/x86/gdt.h>
#include <sched/arch/posix-signal.h>

#include <hybrid/host.h>

#include <kos/except/reason/noexec.h>
#include <kos/exec/asm/elf32.h>
#include <kos/exec/bits/elf32.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/gdt.h>

#include <elf.h>
#include <stddef.h>
#include <string.h>

#ifdef __x86_64__
#include <kos/exec/asm/elf64.h>
#include <kos/exec/bits/elf64.h>
#endif /* __x86_64__ */

DECL_BEGIN

#ifdef __x86_64__

/* Initialize user-space for program execution. */
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *KCALL
elfexec_init_entry(struct icpustate *__restrict user_state,
                   Elf64_Ehdr const *__restrict ehdr,
                   USER void *peb_address, USER void *ustack_base,
                   size_t ustack_size, USER void *entry_pc) {
	switch (ehdr->e_ident[EI_OSABI]) {

	case ELFOSABI_SYSV:
	case ELFOSABI_LINUX:
		if (ehdr->e_ident[EI_ABIVERSION] != 0) {
			THROW(E_NOT_EXECUTABLE_FAULTY,
			      E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF,
			      E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADABIVERSION,
			      ehdr->e_ident[EI_OSABI],
			      ehdr->e_ident[EI_ABIVERSION]);
		}
		break;

	case ELFOSABI_STANDALONE:
		break;

	default:
		THROW(E_NOT_EXECUTABLE_FAULTY,
		      E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF,
		      E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADABI,
		      ehdr->e_ident[EI_OSABI]);
		break;
	}
	set_user_gsbase(x86_get_random_userkern_address()); /* re-roll the ukern address. */
	gpregs_setpdx(&user_state->ics_gpregs, (uintptr_t)peb_address); /* ELF_ARCHX86_64_PEB_REGISTER */
	gpregs_setpbp(&user_state->ics_gpregs, (uintptr_t)peb_address); /* ELF_ARCHX86_64_PEB_REGISTER2 */
	icpustate_setpc(user_state, (uintptr_t)entry_pc);
	icpustate_setuserpsp(user_state, (uintptr_t)ustack_base + ustack_size);
	{
		union x86_user_eflags_mask mask;
		mask.uem_word = atomic64_read(&x86_exec_eflags_mask);
		/* Mask eflags for exec() */
		icpustate_mskpflags(user_state, mask.uem_mask, mask.uem_flag);
	}
	icpustate_setcs(user_state, SEGMENT_USER_CODE64_RPL);
	icpustate_setss(user_state, SEGMENT_USER_DATA64_RPL);
	return user_state;
}

/* Initialize the RTLD user-space library for runtime linking. */
INTERN struct icpustate *KCALL
elfexec_init_rtld(struct icpustate *__restrict user_state,
                  struct path *__restrict exec_path,
                  struct directory_entry *__restrict exec_dentry,
                  struct regular_node *__restrict UNUSED(exec_node),
                  KERNEL Elf64_Ehdr const *__restrict ehdr,
                  KERNEL Elf64_Phdr const *__restrict phdr_vec, Elf64_Half phdr_cnt,
                  void *application_loadaddr, void *linker_loadaddr,
                  USER void *peb_address, USER void *ustack_base,
                  size_t ustack_size, USER void *entry_pc) {
	/* The application-level entry point is stored
	 * stored at the base of the user-space stack. */
	uintptr_t user_state_sp;
	size_t buflen;
	USER struct elfexec_info64 *dl_data;

	switch (ehdr->e_ident[EI_OSABI]) {

	case ELFOSABI_SYSV:
	case ELFOSABI_LINUX:
		if (ehdr->e_ident[EI_ABIVERSION] != 0) {
			THROW(E_NOT_EXECUTABLE_FAULTY,
			      E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF,
			      E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADABIVERSION,
			      ehdr->e_ident[EI_OSABI],
			      ehdr->e_ident[EI_ABIVERSION]);
		}
		break;

	case ELFOSABI_STANDALONE:
		break;

	default:
		THROW(E_NOT_EXECUTABLE_FAULTY,
		      E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF,
		      E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADABI,
		      ehdr->e_ident[EI_OSABI]);
		break;
	}

	/* Figure out where the stack should start. */
	user_state_sp = (uintptr_t)ustack_base + ustack_size;

	/* Push the application-level entry point (usually `_start')
	 * This will later become `dl_data->ei_entry' */
	user_state_sp -= 8;
	*(u64 *)user_state_sp = (u64)(uintptr_t)entry_pc;

	/* Print the application filename to the user-space stack. */
	buflen = 0;
	for (;;) {
		size_t reqlen;
		reqlen = path_sprintent((USER char *)user_state_sp - buflen,
		                        buflen,
		                        exec_path,
		                        exec_dentry->de_name,
		                        exec_dentry->de_namelen);
		if (reqlen <= buflen)
			break;
		buflen = (reqlen + 7) & ~7;
	}
	user_state_sp -= buflen;
	dl_data = (USER struct elfexec_info64 *)(user_state_sp -
	                                         ((phdr_cnt * sizeof(Elf64_Phdr)) +
	                                          offsetof(struct elfexec_info64, ei_phdr)));
	memcpy(dl_data->ei_phdr, phdr_vec, phdr_cnt, sizeof(Elf64_Phdr));
	dl_data->ei_rtldaddr = (u64)(uintptr_t)linker_loadaddr;
	dl_data->ei_pnum     = phdr_cnt;
	dl_data->ei_abi      = ehdr->e_ident[EI_OSABI];
	dl_data->ei_abiver   = ehdr->e_ident[EI_ABIVERSION];
	COMPILER_BARRIER();
	/* ===== Point of no return
	 * This is where we begin to modify user-level registers.
	 * This  may  _only_ happen  _after_ we're  done touching
	 * user-space memory! */

	set_user_gsbase(x86_get_random_userkern_address());                      /* re-roll the ukern address. */
	gpregs_setpdi(&user_state->ics_gpregs, (uintptr_t)dl_data);              /* ELF_ARCHX86_64_DL_RTLDDATA_REGISTER */
	gpregs_setpsi(&user_state->ics_gpregs, (uintptr_t)application_loadaddr); /* ELF_ARCHX86_64_DL_LOADADDR_REGISTER */
	gpregs_setpdx(&user_state->ics_gpregs, (uintptr_t)peb_address);          /* ELF_ARCHX86_64_PEB_REGISTER */
	gpregs_setpbp(&user_state->ics_gpregs, (uintptr_t)peb_address);          /* ELF_ARCHX86_64_PEB_REGISTER2 */
	icpustate_setuserpsp(user_state, (uintptr_t)dl_data);
	icpustate_setpc(user_state, (uintptr_t)linker_loadaddr); /* Entry point is at offset=0 */
	{
		union x86_user_eflags_mask mask;
		mask.uem_word = atomic64_read(&x86_exec_eflags_mask);
		/* Mask eflags for exec() */
		icpustate_mskpflags(user_state, mask.uem_mask, mask.uem_flag);
	}
	icpustate_setcs(user_state, SEGMENT_USER_CODE64_RPL);
	icpustate_setss(user_state, SEGMENT_USER_DATA64_RPL);
	return user_state;
}

#else /* __x86_64__ */
#define elfexec_init_entry32 elfexec_init_entry
#define elfexec_init_rtld32  elfexec_init_rtld
#endif /* !__x86_64__ */


/* Initialize user-space for program execution. */
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *KCALL
elfexec_init_entry32(struct icpustate *__restrict user_state,
                     Elf32_Ehdr const *__restrict ehdr,
                     USER void *peb_address, USER void *ustack_base,
                     size_t ustack_size, USER void *entry_pc) {
	switch (ehdr->e_ident[EI_OSABI]) {

	case ELFOSABI_SYSV:
	case ELFOSABI_LINUX:
		if (ehdr->e_ident[EI_ABIVERSION] != 0) {
			THROW(E_NOT_EXECUTABLE_FAULTY,
			      E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF,
			      E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADABIVERSION,
			      ehdr->e_ident[EI_OSABI],
			      ehdr->e_ident[EI_ABIVERSION]);
		}
		/* Work-around to get applications compiled for linux running.
		 * The crt0 wrapper generated by  glibc starts by doing  this:
		 * >> popl %esi
		 * This  is in  compliance with the  SVR4/i386 ABI, and  it is actually
		 * KOS  that does this  part wrong. Essentially,  SysV wants kernels to
		 * place `argv' and `environ' on the stack of a program's main  thread.
		 * However, KOS uses a specific PEB memory mapping to keep the stack of
		 * the primary  thread  clean  (on KOS,  `_start'  would  actually  get
		 * executed with an entirely empty stack if it wasn't for the 4  unused
		 * bytes allocated right here)...
		 * FIXME: For ELF binaries marked as `ELFOSABI_SYSV', we really
		 *        should  push a copy of the PEB's `envp' and `argv' in
		 *        compliance with SysV requirements! */
		ustack_size -= 4;
		break;

	case ELFOSABI_STANDALONE:
		break;

	default:
		THROW(E_NOT_EXECUTABLE_FAULTY,
		      E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF,
		      E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADABI,
		      ehdr->e_ident[EI_OSABI]);
		break;
	}
	set_user_fsbase(x86_get_random_userkern_address32()); /* re-roll the ukern address. */
	gpregs_setpbp(&user_state->ics_gpregs, (uintptr_t)peb_address); /* ELF_ARCH386_PEB_REGISTER */
	icpustate_setpc(user_state, (uintptr_t)entry_pc);
	icpustate_setuserpsp(user_state, (uintptr_t)ustack_base + ustack_size);
	{
		union x86_user_eflags_mask mask;
		mask.uem_word = atomic64_read(&x86_exec_eflags_mask);
		/* Mask eflags for exec() */
		icpustate_mskpflags(user_state, mask.uem_mask, mask.uem_flag);
	}
#ifdef __x86_64__
	icpustate_setcs(user_state, SEGMENT_USER_CODE32_RPL);
	icpustate_setss(user_state, SEGMENT_USER_DATA32_RPL);
#endif /* __x86_64__ */
	return user_state;
}


/* Initialize the RTLD user-space library for runtime linking. */
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3, 4, 5, 6)) struct icpustate *KCALL
elfexec_init_rtld32(struct icpustate *__restrict user_state,
                    struct path *__restrict exec_path,
                    struct directory_entry *__restrict exec_dentry,
                    struct regular_node *__restrict UNUSED(exec_node),
                    KERNEL Elf32_Ehdr const *__restrict ehdr,
                    KERNEL Elf32_Phdr const *__restrict phdr_vec, Elf32_Half phdr_cnt,
                    void *application_loadaddr, void *linker_loadaddr,
                    USER void *peb_address, USER void *ustack_base,
                    size_t ustack_size, USER void *entry_pc) {
	/* The application-level entry point is stored
	 * stored at the base of the user-space stack. */
	uintptr_t user_state_sp;
	size_t buflen;
	USER struct elfexec_info32 *dl_data;

	switch (ehdr->e_ident[EI_OSABI]) {

	case ELFOSABI_SYSV:
	case ELFOSABI_LINUX:
		if (ehdr->e_ident[EI_ABIVERSION] != 0) {
			THROW(E_NOT_EXECUTABLE_FAULTY,
			      E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF,
			      E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADABIVERSION,
			      ehdr->e_ident[EI_OSABI],
			      ehdr->e_ident[EI_ABIVERSION]);
		}
		/* Work-around to get applications compiled for linux running.
		 * The crt0 wrapper generated by  glibc starts by doing  this:
		 * >> popl %esi
		 * This  is in  compliance with the  SVR4/i386 ABI, and  it is actually
		 * KOS  that does this  part wrong. Essentially,  SysV wants kernels to
		 * place `argv' and `environ' on the stack of a program's main  thread.
		 * However, KOS uses a specific PEB memory mapping to keep the stack of
		 * the primary  thread  clean  (on KOS,  `_start'  would  actually  get
		 * executed with an entirely empty stack if it wasn't for the 4  unused
		 * bytes allocated right here)...
		 * FIXME: For ELF binaries marked as `ELFOSABI_SYSV', we really
		 *        should  push a copy of the PEB's `envp' and `argv' in
		 *        compliance with SysV requirements! */
		ustack_size -= 4;
		break;

	case ELFOSABI_STANDALONE:
		break;

	default:
		THROW(E_NOT_EXECUTABLE_FAULTY,
		      E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF,
		      E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADABI,
		      ehdr->e_ident[EI_OSABI]);
		break;
	}

	/* Figure out where the stack should start. */
	user_state_sp = (uintptr_t)ustack_base + ustack_size;

	/* Push the application-level entry point (usually `_start')
	 * This will later become `dl_data->ei_entry' */
	user_state_sp -= 4;
	*(u32 *)user_state_sp = (u32)(uintptr_t)entry_pc; /* dl_data->ei_entry */

	/* Print the application filename to the user-space stack. */
	buflen = 0;
	for (;;) {
		size_t reqlen;
		reqlen = path_sprintent((USER char *)user_state_sp - buflen,
		                        buflen,
		                        exec_path,
		                        exec_dentry->de_name,
		                        exec_dentry->de_namelen);
		if (reqlen <= buflen)
			break;
		buflen = (reqlen + 3) & ~3;
	}
	user_state_sp -= buflen;
	dl_data = (USER struct elfexec_info32 *)(user_state_sp -
	                                         ((phdr_cnt * sizeof(Elf32_Phdr)) +
	                                          offsetof(struct elfexec_info32, ei_phdr)));
	memcpy(dl_data->ei_phdr, phdr_vec, phdr_cnt, sizeof(Elf32_Phdr));
	dl_data->ei_rtldaddr = (u32)(uintptr_t)linker_loadaddr;
	dl_data->ei_pnum     = phdr_cnt;
	dl_data->ei_abi      = ehdr->e_ident[EI_OSABI];
	dl_data->ei_abiver   = ehdr->e_ident[EI_ABIVERSION];
	COMPILER_BARRIER();
	/* ===== Point of no return
	 * This is where we begin to modify user-level registers.
	 * This  may  _only_ happen  _after_ we're  done touching
	 * user-space memory! */

	set_user_fsbase(x86_get_random_userkern_address32());                    /* re-roll the ukern address. */
	gpregs_setpcx(&user_state->ics_gpregs, (uintptr_t)dl_data);              /* ELF_ARCH386_DL_RTLDDATA_REGISTER */
	gpregs_setpdx(&user_state->ics_gpregs, (uintptr_t)application_loadaddr); /* ELF_ARCH386_DL_LOADADDR_REGISTER */
	gpregs_setpbp(&user_state->ics_gpregs, (uintptr_t)peb_address);          /* ELF_ARCH386_PEB_REGISTER */
	icpustate_setuserpsp(user_state, (uintptr_t)dl_data);
	icpustate_setpc(user_state, (uintptr_t)linker_loadaddr);        /* Entry point is at offset=0 */
	{
		union x86_user_eflags_mask mask;
		mask.uem_word = atomic64_read(&x86_exec_eflags_mask);
		/* Mask eflags for exec() */
		icpustate_mskpflags(user_state, mask.uem_mask, mask.uem_flag);
	}
#ifdef __x86_64__
	icpustate_setcs(user_state, SEGMENT_USER_CODE32_RPL);
	icpustate_setss(user_state, SEGMENT_USER_DATA32_RPL);
#endif /* __x86_64__ */
	return user_state;
}



DECL_END

#endif /* !GUARD_MODELFEXEC_ARCH_I386_ELF_C */
