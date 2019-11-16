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
#ifndef _I386_KOS_KOS_BITS_PROCESS32_H
#define _I386_KOS_KOS_BITS_PROCESS32_H 1

#include <__stdinc.h>
#include <features.h>
#include <bits/types.h>

#include <libc/string.h>
#include <hybrid/host.h>

#include <elf.h>

#ifdef __KERNEL__
#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/types.h>
#include <sched/iopl.h>

#include <kos/kernel/cpu-state32.h>
#endif /* __KERNEL__ */


#ifndef __x86_64__
#define ELF_HOST_REQUIRED_CLASS        ELF_386_HOST_REQUIRED_CLASS
#define ELF_HOST_REQUIRED_CLASS_S      ELF_386_HOST_REQUIRED_CLASS_S
#define ELF_HOST_REQUIRED_MACHINE      ELF_386_HOST_REQUIRED_MACHINE
#define ELF_HOST_REQUIRED_MACHINE_S    ELF_386_HOST_REQUIRED_MACHINE_S
#define ELF_HOST_REQUIRED_DATA         ELF_386_HOST_REQUIRED_DATA
#define ELF_HOST_REQUIRED_DATA_S       ELF_386_HOST_REQUIRED_DATA_S
#define ELF_HOST_MAXPROGRAMHEADERCOUNT ELF_386_HOST_MAXPROGRAMHEADERCOUNT
#define ELF_HOST_PLATFORM              ELF_386_HOST_PLATFORM
#define ELF_HOST_ISVALID_CLASS         ELF_386_HOST_ISVALID_CLASS
#define ELF_HOST_ISVALID_MACHINE       ELF_386_HOST_ISVALID_MACHINE
#define ELF_HOST_ISVALID_DATA          ELF_386_HOST_ISVALID_DATA
#define EXEC_PEB_REGISTER              EXEC_386_PEB_REGISTER
#define EXEC_PEB_REGISTER_S            EXEC_386_PEB_REGISTER_S
#define EXEC_DL_RTLDDATA_REGISTER      EXEC_386_DL_RTLDDATA_REGISTER
#define EXEC_DL_LOADADDR_REGISTER      EXEC_386_DL_LOADADDR_REGISTER
#define EXEC_DL_RTLDDATA_REGISTER_S    EXEC_386_DL_RTLDDATA_REGISTER_S
#define EXEC_DL_LOADADDR_REGISTER_S    EXEC_386_DL_LOADADDR_REGISTER_S
#define __OFFSET_PROCESS_RTLD_ELF_RTLDADDR  __OFFSET_PROCESS_RTLD_ELF32_RTLDADDR
#define __OFFSET_PROCESS_RTLD_ELF_NUM       __OFFSET_PROCESS_RTLD_ELF32_NUM
#define __OFFSET_PROCESS_RTLD_ELF_PHDR      __OFFSET_PROCESS_RTLD_ELF32_PHDR
#define process_rtld_elf32 process_rtld_elf
#define process_rtld_elf_filename process_rtld_elf32_filename
#define process_rtld_elf_entry    process_rtld_elf32_entry
#ifdef __KERNEL__
#define exec_initialize_entry     exec_initialize_entry32
#define exec_initialize_elf_rtld  exec_initialize_elf_rtld32
#endif /* __KERNEL__ */
#endif /* !__x86_64__ */


__DECL_BEGIN

#define ELF_386_HOST_REQUIRED_CLASS      ELFCLASS32
#define ELF_386_HOST_REQUIRED_CLASS_S   "ELFCLASS32"
#define ELF_386_HOST_REQUIRED_MACHINE    EM_386
#define ELF_386_HOST_REQUIRED_MACHINE_S "EM_386"
#define ELF_386_HOST_REQUIRED_DATA       ELFDATA2LSB
#define ELF_386_HOST_REQUIRED_DATA_S    "ELFDATA2LSB"
#define ELF_386_HOST_MAXPROGRAMHEADERCOUNT 64

#define ELF_386_HOST_PLATFORM           "i386"

#define ELF_386_HOST_ISVALID_CLASS(x)   ((x) == ELF_386_HOST_REQUIRED_CLASS)
#define ELF_386_HOST_ISVALID_MACHINE(x) ((x) == ELF_386_HOST_REQUIRED_MACHINE)
#define ELF_386_HOST_ISVALID_DATA(x)    ((x) == ELF_386_HOST_REQUIRED_DATA)


/* The user-space register holding a pointer to the ProcessEnvironmentBlock
 * immediately following the initial transition to user-space after a call
 * to exec()
 * NOTE: This register points to a `struct process_peb' structure. */
#define EXEC_386_PEB_REGISTER     ebp
#define EXEC_386_PEB_REGISTER_S  "ebp"


/* When a dynamic linker is loaded, additional information is passed
 * via user-space registers containing information about how the program
 * must be linked before it can actually be executed properly.
 * The exact structures pointed to by `EXEC_386_DL_RTLDDATA_REGISTER'
 * depend on which DL loader was chosen:
 *   - ELF: `struct process_rtld_elfdata'
 */
#define EXEC_386_DL_RTLDDATA_REGISTER    ecx /* Pointer to a RTLD-specific initialization data. */
#define EXEC_386_DL_LOADADDR_REGISTER    edx /* The kernel-chose base-address of the application being loaded. */
#define EXEC_386_DL_RTLDDATA_REGISTER_S "ecx"
#define EXEC_386_DL_LOADADDR_REGISTER_S "edx"


#define __OFFSET_PROCESS_RTLD_ELF32_RTLDADDR 0
#define __OFFSET_PROCESS_RTLD_ELF32_PNUM     4
#define __OFFSET_PROCESS_RTLD_ELF32_PHDR     8

#ifdef __CC__
struct process_rtld_elf32 /*[PREFIX(pr_)]*/ {
	__uint32_t pr_rtldaddr;    /* Load address of the RTLD itself. */
	Elf32_Half pr_pnum;        /* Amount of ELF program headers. */
	Elf32_Half pr_ppad;        /* ... */
	Elf32_Phdr pr_phdr[1024];  /* [pr_pnum] Vector of ELF program headers.
	                            * All of these have already been loaded into memory. */
//	char       pr_filename[*]; /* NUL-terminated filename of the loaded binary. */
//	char       pr_align[*];    /* Align to next 4 byte boundary. */
//	__uint32_t pr_entry;       /* The final entry point for the program. */
//	byte_t     pr_entry_sp[];  /* Entry stack address (set the address of this field as
//	                            * stack-pointer when handing control to the hosted application) */
};
#define process_rtld_elf32_filename(x) ((char *)&(x)->pr_phdr[(x)->pr_pnum])
#define process_rtld_elf32_entry(x)    (*(__uint32_t *)((__uint32_t)(__libc_strend(process_rtld_elf_filename(x)) + 1 + 3) & ~3))



#ifdef __KERNEL__
LOCAL struct icpustate *KCALL
exec_initialize_entry32(struct icpustate *__restrict user_state,
                        USER void *peb_address, USER void *ustack_base,
                        __size_t ustack_size, USER void *entry_pc) {
	irregs_wrip(&user_state->ics_irregs, (__uintptr_t)entry_pc);
#ifdef __x86_64__
	irregs_wrsp(&user_state->ics_irregs, (__uint64_t)ustack_base + ustack_size);
	user_state->ics_gpregs.gp_rbp = (__uint64_t)peb_address;
	if (!x86_iopl_keep_after_exec)
		user_state->ics_irregs.ir_pflags &= ~0x3000; /* EFLAGS_IOPLMASK */
#else /* __x86_64__ */
	user_state->ics_gpregs.gp_ebp   = (__uint32_t)peb_address;
	user_state->ics_irregs_u.ir_esp = (__uint32_t)ustack_base + ustack_size;
	if (!x86_iopl_keep_after_exec)
		user_state->ics_irregs.ir_eflags &= ~0x3000; /* EFLAGS_IOPLMASK */
#endif /* !__x86_64__ */
	return user_state;
}

LOCAL struct icpustate *KCALL
exec_initialize_elf_rtld32(struct icpustate *__restrict user_state,
                           struct path *__restrict exec_path,
                           struct directory_entry *__restrict exec_dentry,
                           struct regular_node *__restrict UNUSED(exec_node),
                           __uint32_t application_loadaddr,
                           __uint32_t linker_loadaddr,
                           KERNEL Elf32_Phdr *__restrict phdr_vec,
                           Elf32_Half phdr_cnt) {
	USER struct process_rtld_elf32 *dl_data;
	__size_t reqlen, buflen;
	/* The application-level entry point is stored
	 * stored at the base of the user-space stack. */
	uintptr_t user_state_sp;
#ifdef __x86_64__
	user_state_sp = irregs_rdsp(&user_state->ics_irregs);
#else /* __x86_64__ */
	user_state_sp = user_state->ics_irregs_u.ir_esp;
#endif /* !__x86_64__ */

	user_state_sp -= 4;
	*(__uint32_t *)user_state_sp = (__uint32_t)irregs_rdip(&user_state->ics_irregs); /* dl_data->pr_entry */
	/* Print the application filename to the user-space stack. */
	buflen = 0;
	for (;;) {
		reqlen = path_sprintent((USER char *)user_state_sp - buflen,
		                        buflen,
		                        exec_path,
		                        exec_dentry);
		if (reqlen <= buflen)
			break;
		buflen = (reqlen + 3) & ~3;
	}
	user_state_sp -= buflen;

	dl_data = (USER struct process_rtld_elf32 *)(user_state_sp -
	                                             ((phdr_cnt * sizeof(Elf32_Phdr)) +
	                                              offsetof(struct process_rtld_elf32, pr_phdr)));
	__libc_memcpy(dl_data->pr_phdr, phdr_vec, phdr_cnt * sizeof(Elf32_Phdr));
	dl_data->pr_rtldaddr = (__uint32_t)linker_loadaddr;
	dl_data->pr_pnum     = phdr_cnt;
#ifdef __x86_64__
	user_state->ics_gpregs.gp_rcx = (__uint64_t)dl_data;
	user_state->ics_gpregs.gp_rdx = (__uint64_t)application_loadaddr;
	irregs_wrsp(&user_state->ics_irregs, (__uint64_t)dl_data);
#else /* __x86_64__ */
	user_state->ics_gpregs.gp_ecx   = (__uint32_t)dl_data;
	user_state->ics_gpregs.gp_edx   = (__uint32_t)application_loadaddr;
	user_state->ics_irregs_u.ir_esp = (__uint32_t)dl_data;
#endif /* !__x86_64__ */
	irregs_wrip(&user_state->ics_irregs, (__uintptr_t)linker_loadaddr); /* Entry point is at offset=0 */
#undef USER_STATE_SP
	return user_state;
}

#endif /* __KERNEL__ */
#endif /* __CC__ */

__DECL_END

#endif /* !_I386_KOS_KOS_BITS_PROCESS32_H */
