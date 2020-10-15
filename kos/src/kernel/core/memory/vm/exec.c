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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_EXEC_C
#define GUARD_KERNEL_SRC_MEMORY_VM_EXEC_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/debugtrap.h>
#include <kernel/driver-param.h>
#include <kernel/driver.h>
#include <kernel/execabi.h>
#include <kernel/vm.h>
#include <kernel/vm/exec.h>

#include <kos/except/reason/fs.h>
#include <kos/except/reason/noexec.h>

#include <signal.h>
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

/* List of callbacks that should be invoked after vm_exec()
 * These are called alongside stuff like `handle_manager_cloexec()'
 * NOTE: The passed vm is always `THIS_VM', and is never `&vm_kernel' */
PUBLIC CALLBACK_LIST(void KCALL(void)) vm_onexec_callbacks = CALLBACK_LIST_INIT;

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
 *                       NOTE: When `change_vm_to_effective_vm' is `true', prior to a successful
 *                             return of this function, it will also do a `task_setvm(effective_vm)',
 *                             meaning that the caller will become apart of the given VM.
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
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3, 4, 5)) struct icpustate *KCALL
vm_exec(struct vm *__restrict effective_vm,
        struct icpustate *__restrict user_state,
        struct path *__restrict exec_path,
        struct directory_entry *__restrict exec_dentry,
        struct regular_node *__restrict exec_node,
        bool change_vm_to_effective_vm,
        size_t argc_inject, KERNEL char const *const *argv_inject,
        execabi_strings_t argv, execabi_strings_t envp
        EXECABI_PARAM__argv_is_compat)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR) {
	REF struct execabis_struct *abis;
	size_t i;
	byte_t header[CONFIG_EXECABI_MAXHEADER];
	{
		size_t count;
		/* Load the file header. */
		count = inode_read(exec_node, header, sizeof(header), 0);
		if unlikely(count < CONFIG_EXECABI_MAXHEADER)
			memset(header + count, 0, CONFIG_EXECABI_MAXHEADER - count);
	}
again_getabis:
	abis = execabis.get();
	for (i = 0; i < abis->eas_count; ++i) {
		struct icpustate *result;
		struct execabi *abi = &abis->eas_abis[i];
		/* Check if the magic for this ABI matches. */
		if (memcmp(header, abi->ea_magic, abi->ea_magsiz) != 0)
			continue;
		if (!tryincref(abi->ea_driver))
			continue;
		FINALLY_DECREF_UNLIKELY(abi->ea_driver);
		/* Try to invoke the exec loader of this ABI */
		TRY {
			result = (*abi->ea_exec)(effective_vm,
			                         user_state,
			                         exec_path,
			                         exec_dentry,
			                         exec_node,
			                         header,
			                         change_vm_to_effective_vm,
			                         argc_inject, argv_inject,
			                         argv,
			                         envp
			                         EXECABI_ARG__argv_is_compat);
		} EXCEPT {
			decref_unlikely(abi->ea_driver);
			/* Handle `E_NOT_EXECUTABLE_NOT_A_BINARY' the same as a NULL-return-value
			 * from the `ea_exec' callback, except when appearing in the last ABI, in
			 * which case there aren't any more abis which we could try. */
			if (i >= abis->eas_count - 1 || !was_thrown(E_NOT_EXECUTABLE_NOT_A_BINARY)) {
				decref_unlikely(abis);
				RETHROW();
			}
			continue;
		}
		decref_unlikely(abi->ea_driver);
		if likely(result) {
			decref_unlikely(abis);
			return result; /* Got it! */
		}
	}
	decref_unlikely(abis);
	if unlikely(abis != execabis.m_pointer) {
		/* The available set of ABIs has changed. - Try again. */
		goto again_getabis;
	}
	/* Fallback: File isn't a recognized binary. */
	THROW(E_NOT_EXECUTABLE_NOT_A_BINARY);
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
	                true, /* change_vm_to_effective_vm: Don't matter */
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
