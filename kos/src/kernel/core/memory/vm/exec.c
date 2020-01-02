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
#include <kernel/rtld.h>
#include <kernel/vm.h>
#include <kernel/vm/builder.h>
#include <kernel/vm/exec.h>
#include <kernel/vm/library.h>
#include <kernel/vm/phys.h>

#include <hybrid/align.h>
#include <hybrid/pointer.h>

#include <compat/config.h>
#include <kos/except-fs.h>
#include <kos/except-noexec.h>
#include <kos/exec/elf.h>
#include <kos/exec/library-listdef.h>
#include <kos/exec/peb.h>

#include <assert.h>
#include <elf.h>
#include <malloca.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <kos/exec/asm/elf-compat.h>
#endif /* __ARCH_HAVE_COMPAT */

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
NOTHROW(KCALL elf_validate_ehdr)(ElfW(Ehdr) *__restrict ehdr) {
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
	if unlikely(ehdr->e_ehsize < offsetafter(ElfW(Ehdr),e_phnum))
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
LOCAL NOBLOCK WUNUSED NONNULL((1)) uintptr_t
NOTHROW(KCALL __ARCH_COMPAT(elf_validate_ehdr))(COMPAT_ElfW(Ehdr) *__restrict ehdr) {
	uintptr_t result;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADCLASS;
	if unlikely(ehdr->e_ident[EI_CLASS] != ELF_ARCHCOMPAT_CLASS)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADORDER;
	if unlikely(ehdr->e_ident[EI_DATA] != ELF_ARCHCOMPAT_DATA)
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
	if unlikely(ehdr->e_machine != ELF_ARCHCOMPAT_MACHINE)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADHEADER;
	if unlikely(ehdr->e_ehsize < offsetafter(COMPAT_ElfW(Ehdr),e_phnum))
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOSEGMENTS;
	if unlikely(!ehdr->e_phnum)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADSEGMENTS;
	if unlikely(ehdr->e_phentsize != sizeof(COMPAT_ElfW(Phdr)))
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_TOOMANYSEGMENTS;
	if unlikely(ehdr->e_phnum > ELF_ARCH_MAXPHCOUNT)
		goto done; /* Too many program headers. */
	result = 0;
done:
	return result;
}
#endif /* __ARCH_HAVE_COMPAT */

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
			overlap_page = page_mallocone();
			if unlikely(overlap_page == PAGEPTR_INVALID)
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
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


#ifndef __INTELLISENSE__
DECL_END
#define MY_PTR(x) x *
#define MY_FUNC(x) x
#define MY_ELFW ELFW
#define MY_ElfW ElfW
#define MY_SYSTEM_RTLD_SIZE system_rtld_size
#define MY_SYSTEM_RTLD_FILE system_rtld_file
#define MY_POINTERSIZE __SIZEOF_POINTER__
#ifdef __ARCH_HAVE_COMPAT
#define MY_EXEC_ARGV_SIZE 1
#endif /* __ARCH_HAVE_COMPAT */
#include "exec-impl.c.inl"

#ifdef __ARCH_HAVE_COMPAT
#define MY_PTR              __ARCH_COMPAT_PTR
#define MY_FUNC             __ARCH_COMPAT
#define MY_ELFW             COMPAT_ELFW
#define MY_ElfW             COMPAT_ElfW
#define MY_SYSTEM_RTLD_SIZE PP_CAT2(__ARCH_COMPAT(system_rtld), _size)
#define MY_SYSTEM_RTLD_FILE PP_CAT2(__ARCH_COMPAT(system_rtld), _file)
#define MY_POINTERSIZE      __ARCH_COMPAT_SIZEOF_POINTER
#define MY_EXEC_ARGV_SIZE 1
#include "exec-impl.c.inl"
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN
#else /* !__INTELLISENSE__ */
LOCAL WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3, 4, 5, 10)) struct icpustate *KCALL
vm_exec_impl(struct vm *__restrict effective_vm,
             struct icpustate *__restrict user_state,
             struct path *__restrict exec_path,
             struct directory_entry *__restrict exec_dentry,
             struct regular_node *__restrict exec_node,
             size_t argc_inject, KERNEL char const *const *argv_inject,
#ifdef __ARCH_HAVE_COMPAT
             USER CHECKED void const *argv,
             USER CHECKED void const *envp,
#else /* __ARCH_HAVE_COMPAT */
             USER UNCHECKED char const *USER CHECKED const *argv,
             USER UNCHECKED char const *USER CHECKED const *envp,
#endif /* !__ARCH_HAVE_COMPAT */
             ElfW(Ehdr) const *__restrict ehdr
#ifdef __ARCH_HAVE_COMPAT
             ,
             bool argv_is_compat
#endif /* __ARCH_HAVE_COMPAT */
             )
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR);
#ifdef __ARCH_HAVE_COMPAT
LOCAL WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3, 4, 5, 10)) struct icpustate *KCALL
__ARCH_COMPAT(vm_exec_impl)(struct vm *__restrict effective_vm,
                            struct icpustate *__restrict user_state,
                            struct path *__restrict exec_path,
                            struct directory_entry *__restrict exec_dentry,
                            struct regular_node *__restrict exec_node,
                            size_t argc_inject, KERNEL char const *const *argv_inject,
                            USER CHECKED void const *argv,
                            USER CHECKED void const *envp,
                            COMPAT_ElfW(Ehdr) const *__restrict ehdr,
                            bool argv_is_compat)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR);
#endif /* __ARCH_HAVE_COMPAT */
#endif /* __INTELLISENSE__ */

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
#ifdef __ARCH_HAVE_COMPAT
        USER CHECKED void const *argv,
        USER CHECKED void const *envp,
        bool argv_is_compat
#else /* __ARCH_HAVE_COMPAT */
        USER UNCHECKED char const *USER CHECKED const *argv,
        USER UNCHECKED char const *USER CHECKED const *envp
#endif /* !__ARCH_HAVE_COMPAT */
        )
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR) {
	uintptr_t reason;
	union {
		ElfW(Ehdr)        e;
#ifdef __ARCH_HAVE_COMPAT
		COMPAT_ElfW(Ehdr) c;
#endif /* __ARCH_HAVE_COMPAT */
	} ehdr;
	/* Read in the ELF header. */
	inode_readall(exec_node, &ehdr, sizeof(ehdr), 0);

	/* TODO: Support for Shebang */
	/* TODO: Support for PE */

	/* Validate the ELF header. */
	if unlikely(ehdr.e.e_ident[EI_MAG0] != ELFMAG0 ||
	            ehdr.e.e_ident[EI_MAG1] != ELFMAG1 ||
	            ehdr.e.e_ident[EI_MAG2] != ELFMAG2 ||
	            ehdr.e.e_ident[EI_MAG3] != ELFMAG3)
		THROW(E_NOT_EXECUTABLE_NOT_A_BINARY);
	reason = elf_validate_ehdr(&ehdr.e);
	if (reason == 0) {
		user_state = vm_exec_impl(effective_vm,
		                          user_state,
		                          exec_path,
		                          exec_dentry,
		                          exec_node,
		                          argc_inject,
		                          argv_inject,
		                          argv,
		                          envp,
		                          &ehdr.e
#ifdef __ARCH_HAVE_COMPAT
		                          ,
		                          argv_is_compat
#endif /* __ARCH_HAVE_COMPAT */
		                          );
		return user_state;
	}
#ifdef __ARCH_HAVE_COMPAT
	reason = __ARCH_COMPAT(elf_validate_ehdr)(&ehdr.c);
	if (reason == 0) {
		user_state = __ARCH_COMPAT(vm_exec_impl)(effective_vm,
		                                         user_state,
		                                         exec_path,
		                                         exec_dentry,
		                                         exec_node,
		                                         argc_inject, argv_inject,
		                                         argv,
		                                         envp,
		                                         &ehdr.c,
		                                         argv_is_compat);
		return user_state;
	}
#endif /* __ARCH_HAVE_COMPAT */
	THROW(E_NOT_EXECUTABLE_FAULTY,
	      E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF,
	      reason);
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
