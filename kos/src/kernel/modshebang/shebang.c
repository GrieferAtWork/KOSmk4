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
#ifndef GUARD_MODELFEXEC_ELF_C
#define GUARD_MODELFEXEC_ELF_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/vfs.h>

#include <hybrid/atomic.h>

#include <kos/except/reason/noexec.h>

#include <ctype.h>
#include <string.h>

/**/
#include "shebang.h"

DECL_BEGIN

/* Find the end of the given line (that is: a pointer to the first \r or \n)
 * If no such character exists before `len' bytes have been scanned,  return
 * NULL instead. */
LOCAL ATTR_PURE NONNULL((1)) char *KCALL
find_eol(char *line, size_t len) {
	while (len) {
		char ch = *line;
		if (ch == '\n' || ch == '\r')
			return line;
		++line;
		--len;
	}
	return NULL;
}


/* ABI exec function for #! */
INTERN WUNUSED NONNULL((1)) unsigned int FCALL
shebang_exec(struct execargs *__restrict args) {
	/* Syntax: `#! <path-relative-to(exec_path)>[ <optional_argument>] LF'
	 *            ^                              ^                    ^
	 *            Optional                       Mandatory            Optional
	 *            whitespace                     whitespace           whitespace */
	char *ext_header = NULL;

	/* Check for simple case: the linefeed is already apart of the pre-loaded `exec_header' */
	TRY {
		char *execfile, *execline_end;
		char *execfile_end;
		char *optarg_start;
		execfile     = (char *)args->ea_header + 2;
		execline_end = find_eol(execfile, CONFIG_EXECABI_MAXHEADER - 2);
		if unlikely(!execline_end) {
			size_t extlen;
			char *ptr;
			/* The end of the leading line may be apart of an extended header. */
			ext_header = (char *)kmalloc(CONFIG_SHEBANG_INTERPRETER_LINE_MAX, GFP_NORMAL);
			ptr        = (char *)mempcpy(ext_header, args->ea_header + 2, CONFIG_EXECABI_MAXHEADER - 2);
#define MAX_EXTSIZE (CONFIG_SHEBANG_INTERPRETER_LINE_MAX - (CONFIG_EXECABI_MAXHEADER - 2))
			extlen = inode_read(args->ea_xnode, ptr, MAX_EXTSIZE, (pos_t)(CONFIG_EXECABI_MAXHEADER - 2));
			if (extlen < MAX_EXTSIZE)
				memset(ptr + extlen, 0, MAX_EXTSIZE - extlen);
#undef MAX_EXTSIZE
			execfile     = ext_header;
			execline_end = find_eol(execfile, CONFIG_SHEBANG_INTERPRETER_LINE_MAX);
			if unlikely(!execline_end) {
				/* NOTE: `kfree(ext_header);' is called by an EXCEPT below! */
				THROW(E_NOT_EXECUTABLE_FAULTY,
				      E_NOT_EXECUTABLE_FAULTY_FORMAT_SHEBANG,
				      E_NOT_EXECUTABLE_FAULTY_REASON_SHEBANG_TRUNC);
			}
		}
		/* Trim leading+trailing space characters. */
		for (;;) {
			if unlikely(execfile >= execline_end) {
				/* Empty interpreter line. */
				THROW(E_NOT_EXECUTABLE_FAULTY,
				      E_NOT_EXECUTABLE_FAULTY_FORMAT_SHEBANG,
				      E_NOT_EXECUTABLE_FAULTY_REASON_SHEBANG_NO_INTERP);
			}
			if (isspace(execfile[0])) {
				++execfile;
				continue;
			}
			if (isspace(execline_end[-1])) {
				--execline_end;
				continue;
			}
			break;
		}
		/* Figure out where the filename of the executable ends. */
		execfile_end = execfile + 1;
		while (execfile_end < execline_end) {
			if (isspace(*execfile_end))
				break;
			++execfile_end;
		}
		*execfile_end = '\0'; /* Terminate the interpreter name. */
		optarg_start = execfile_end + 1;
		/* Strip leading space from the optional argument. */
		while (optarg_start < execline_end) {
			if (!isspace(*optarg_start))
				break;
			++optarg_start;
		}
		/* At this point:
		 *   FILENAME      = [execfile, execfile_end)
		 *   OPTARG_EXISTS = optarg_start < execline_end
		 *   OPTARG        = [optarg_start, execline_end) */
#define HAS_OPTIONAL_ARGUMENT() (optarg_start < execline_end)
		{
			/* Load the interpreter program. */
			REF struct path /*           */ *interp_path;
			REF struct directory_entry /**/ *interp_dentry;
			REF struct regular_node /*   */ *interp_node;
			{
				struct fs *myfs = THIS_FS;
				REF struct path *search_root;
				sync_read(&myfs->f_pathlock);
				search_root = incref(myfs->f_root);
				sync_endread(&myfs->f_pathlock);
				FINALLY_DECREF_UNLIKELY(search_root);
				/* NOTE: Relative paths are  interpreted relative  to the  directory
				 *       containing the script file itself.  I feel like that  makes
				 *       more sense that using the calling process's current working
				 *       directory. */
				interp_node = (REF struct regular_node *)path_traversefull_ex(myfs,
				                                                              args->ea_xpath,
				                                                              search_root,
				                                                              execfile,
				                                                              true,
				                                                              ATOMIC_READ(myfs->f_mode.f_atflag),
				                                                              NULL,
				                                                              &interp_path,
				                                                              NULL,
				                                                              &interp_dentry);
			}
			TRY {
				char *inject_arg0, *inject_arg1;
				size_t more_argc;
				/* Assert that the specified node is a regular file. */
#if 0 /* TODO */
				vm_exec_assert_regular(interp_node);
#endif

				/* Check for execute permissions? */
				inode_access(interp_node, R_OK | X_OK);

				/* Construct a new set to arguments to-be injected. */
				more_argc = 1;
				if (HAS_OPTIONAL_ARGUMENT())
					more_argc = 2;
				args->ea_argv_inject = (char **)krealloc(args->ea_argv_inject,
				                                         (args->ea_argc_inject +
				                                          more_argc) *
				                                         sizeof(char *),
				                                         GFP_NORMAL);
				/* Duplicate the 1-2 arguments we want to inject. */
				inject_arg0 = (char *)kmalloc((size_t)((execfile_end - execfile) + 1) *
				                              sizeof(char),
				                              GFP_NORMAL);
				*(char *)mempcpy(inject_arg0, execfile,
				                 (size_t)(execfile_end - execfile),
				                 sizeof(char)) = '\0';
				inject_arg1 = NULL;
				if (HAS_OPTIONAL_ARGUMENT()) {
					TRY {
						inject_arg1 = (char *)kmalloc((size_t)((execline_end - optarg_start) + 1) *
						                              sizeof(char),
						                              GFP_NORMAL);
						*(char *)mempcpy(inject_arg1, optarg_start,
						                 (size_t)(execline_end - optarg_start),
						                 sizeof(char)) = '\0';
					} EXCEPT {
						kfree(inject_arg0);
						RETHROW();
					}
				}

				/* Keep arguments that were already supposed to be
				 * injected, however inject  those after the  ones
				 * that we're supposed to inject. */
				memmoveup(args->ea_argv_inject + more_argc,
				          args->ea_argv_inject,
				          args->ea_argc_inject,
				          sizeof(char *));

				/* Actually inject the 2 arguments. */
				args->ea_argv_inject[0] = inject_arg0;
				if (inject_arg1)
					args->ea_argv_inject[1] = inject_arg1;
				args->ea_argc_inject += more_argc;
			} EXCEPT {
				decref_unlikely(interp_path);
				decref_unlikely(interp_dentry);
				decref_unlikely(interp_node);
				RETHROW();
			}

			/* Replace the exec-path with that of the interpreter. */
			decref_unlikely(args->ea_xpath);
			decref_unlikely(args->ea_xdentry);
			decref_unlikely(args->ea_xnode);
			args->ea_xpath   = interp_path;   /* Inherit reference */
			args->ea_xdentry = interp_dentry; /* Inherit reference */
			args->ea_xnode   = interp_node;   /* Inherit reference */
		}
#undef HAS_OPTIONAL_ARGUMENT
	} EXCEPT {
		kfree(ext_header);
		RETHROW();
	}
#ifndef __OPTIMIZE_SIZE__
	if unlikely(ext_header != NULL)
#endif /* !__OPTIMIZE_SIZE__ */
	{
		kfree(ext_header);
	}
	/* Tell our caller to restart interpretation. */
	return EXECABI_EXEC_RESTART;
}



#ifndef CONFIG_BUILDING_KERNEL_CORE
PRIVATE struct execabi bangabi = EXECABI_INIT_SHEBANG;
PRIVATE DRIVER_INIT void KCALL init(void) {
	execabis_register(&bangabi);
}
#endif /* CONFIG_BUILDING_KERNEL_CORE */

DECL_END

#endif /* !GUARD_MODELFEXEC_ELF_C */
