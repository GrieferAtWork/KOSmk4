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
#include <sched/rpc.h> /* task_serve() */

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
 * @param: args:             Exec arguments
 * @throw: E_BADALLOC:       Insufficient memory
 * @throw: E_SEGFAULT:       The given `argv', `envp', or one of their pointed-to strings is faulty
 * @throw: E_NOT_EXECUTABLE: The given `exec_node' was not recognized as an acceptable binary. */
PUBLIC NONNULL((1)) void KCALL
vm_exec(/*in|out*/ struct execargs *__restrict args)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR) {
	REF struct execabis_struct *abis;
	size_t i;
	{
		size_t read_bytes;
		/* Load the file header. */
		read_bytes = inode_read(args->ea_xnode, args->ea_header, sizeof(args->ea_header), 0);
		if unlikely(read_bytes < CONFIG_EXECABI_MAXHEADER)
			memset(args->ea_header + read_bytes, 0, CONFIG_EXECABI_MAXHEADER - read_bytes);
	}
again_getabis:
	abis = execabis.get();
again_searchabis:
	for (i = 0; i < abis->eas_count; ++i) {
		unsigned int status;
		struct execabi *abi = &abis->eas_abis[i];
		/* Check if the magic for this ABI matches. */
		if (memcmp(args->ea_header, abi->ea_magic, abi->ea_magsiz) != 0)
			continue;
		if (!tryincref(abi->ea_driver))
			continue;
		/* Try to invoke the exec loader of this ABI */
		TRY {
			status = (*abi->ea_exec)(args);
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
		if (status == EXECABI_EXEC_SUCCESS) {
			decref_unlikely(abis);
			return; /* Got it! */
		}
		/* If requested to, restart the exec process.
		 * This is used to implement interpreter redirection, as used by #!-scripts. */
		if (status == EXECABI_EXEC_RESTART) {
			/* Make sure to service RPC functions before restarting.
			 * A malicious user may have set-up #!-files in a loop, and
			 * we must ensure that some other user remains the ability
			 * to kill(2) or CTRL+C our process (in order words: we must
			 * guaranty to be able to service RPCs when looping back) */
			task_serve();
			goto again_searchabis;
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
	struct execargs args;
	memset(&args, 0, sizeof(args)); /* For fields which we don't use */
	args.ea_xnode = (REF struct regular_node *)path_traversefull(THIS_FS,
	                                                             kernel_init_binary,
	                                                             true,
	                                                             FS_MODE_FNORMAL,
	                                                             NULL,
	                                                             &args.ea_xpath,
	                                                             NULL,
	                                                             &args.ea_xdentry);
	/* Can only execute regular files. */
	vm_exec_assert_regular(args.ea_xnode);

	/* Fill in the remaining fields of `args' (which we make use of) */
	args.ea_vm          = THIS_VM;
	args.ea_argc_inject = 1;
	args.ea_argv_inject = (char **)kmalloc(1 * sizeof(char *), GFP_NORMAL);
	{
		size_t binlen = (strlen(kernel_init_binary) + 1) * sizeof(char);
		args.ea_argv_inject[0] = (char *)memcpy(kmalloc(binlen, GFP_NORMAL),
		                                        kernel_init_binary, binlen);
	}

	/* Do the actual exec */
	args.ea_state = state;
	vm_exec(&args);
	state = args.ea_state;

	/* Finalize exec arguments. */
	execargs_fini(&args);

	if (kernel_debugtrap_enabled()) {
		struct debugtrap_reason r;
		r.dtr_signo  = SIGTRAP;
		r.dtr_reason = DEBUGTRAP_REASON_EXEC;
		/* FIXME: Should re-print the path using `path_sprintent()', since the path
		 *        given by the bootloader may be ambiguous (or contain/be a symlink) */
		r.dtr_strarg = kernel_init_binary;
		state = kernel_debugtrap_r(state, &r);
	}
	return state;
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_EXEC_C */
