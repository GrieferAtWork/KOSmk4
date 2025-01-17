/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODELF_ELF_C
#define GUARD_MODELF_ELF_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver-param.h>
#include <kernel/driver.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/fs.h>
#include <kernel/fs/node.h>
#include <kernel/fs/path.h>
#include <kernel/malloc.h>
#include <kernel/mman/mfile.h>

#include <compat/config.h>
#include <kos/except.h>
#include <kos/except/reason/noexec.h>

#include <assert.h>
#include <atomic.h>
#include <ctype.h>
#include <format-printer.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/types.h>
#endif /* __ARCH_HAVE_COMPAT */

/**/
#include "shebang.h"

DECL_BEGIN

/* Find the end of the given line (that is: a pointer to the first \r or \n)
 * If no such character exists before `len' bytes have been scanned,  return
 * NULL instead. */
LOCAL ATTR_PURE WUNUSED NONNULL((1)) char *
NOTHROW_NCX(KCALL find_eol)(char *line, size_t len) {
	while (len) {
		char ch = *line;
		if (ch == '\n' || ch == '\r')
			return line;
		++line;
		--len;
	}
	return NULL;
}


struct path_aprinter_data {
	char *pap_buf; /* [0..1] Printer base pointer. */
	char *pap_ptr; /* [0..1] Printer end pointer. */
};

PRIVATE WUNUSED ssize_t FORMATPRINTER_CC
path_aprinter(void *arg, char const *__restrict data, size_t datalen)
		THROWS(E_BADALLOC) {
	struct path_aprinter_data *cookie = (struct path_aprinter_data *)arg;
	size_t usable = kmalloc_usable_size(cookie->pap_buf);
	size_t used   = (size_t)(cookie->pap_ptr - cookie->pap_buf);
	size_t avail  = usable - used;
	if (datalen >= avail) { /* >= because we want space for a trailing \0 */
		char *newbuf;
		size_t needed  = used + datalen;
		size_t newsize = (needed << 1) | 1;
		newbuf = (char *)krealloc_nx(cookie->pap_buf, newsize * sizeof(char), GFP_NORMAL);
		if (!newbuf) {
			newsize = needed + 1; /* +1 because we want space for a trailing \0 */
			newbuf  = (char *)krealloc(cookie->pap_buf, newsize * sizeof(char), GFP_NORMAL);
		}
		cookie->pap_buf = newbuf;
		cookie->pap_ptr = newbuf + used;
	}
	cookie->pap_ptr = (char *)mempcpy(cookie->pap_ptr, data,
	                                  datalen, sizeof(char));
	return (ssize_t)datalen;
}

PRIVATE WUNUSED NONNULL((1)) char *KCALL
path_aprintent_ex(struct path *__restrict self,
                  NCX char const *dentry_name,
                  u16 dentry_namelen, struct path *root)
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_BADALLOC) {
	size_t reqlen;
	char *result;
	struct path_aprinter_data printer;
	bzero(&printer, sizeof(printer));
	TRY {
		path_printent(self, dentry_name, dentry_namelen,
		              &path_aprinter, &printer,
		              AT_PATHPRINT_INCTRAIL, root);
		reqlen = (size_t)(printer.pap_ptr - printer.pap_buf);
		result = (char *)krealloc(printer.pap_buf, (reqlen + 1) * sizeof(char), GFP_NORMAL);
	} EXCEPT {
		kfree(printer.pap_buf);
		RETHROW();
	}
	result[reqlen] = '\0';
	return result;
}


PRIVATE WUNUSED NONNULL((1)) char *KCALL
path_aprintent(struct path *__restrict self,
               NCX char const *dentry_name,
               u16 dentry_namelen)
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_BADALLOC) {
	REF struct path *root = fs_getroot(THIS_FS);
	FINALLY_DECREF_UNLIKELY(root);
	return path_aprintent_ex(self, dentry_name, dentry_namelen, root);
}


/* ABI exec function for #! */
INTERN WUNUSED NONNULL((1)) unsigned int FCALL
shebang_exec(struct execargs *__restrict args) {
	char *ext_header;
	char *execfile, *execline_end;
	char *execfile_end;
	char *optarg_start;

	/* shebang can't be used without an execution path! */
	if unlikely(!args->ea_xpath)
		return EXECABI_EXEC_NOTBIN;

	/* Syntax: `#! <path-relative-to(exec_path)>[ <optional_argument>] LF'
	 *            ^                              ^                    ^
	 *            Optional                       Mandatory            Optional
	 *            whitespace                     whitespace           whitespace */
	ext_header = NULL;
	RAII_FINALLY { kfree_unlikely(ext_header); };

	/* Check for simple case: the linefeed is already apart of the pre-loaded `exec_header' */
	execfile     = (char *)args->ea_header + 2;
	execline_end = find_eol(execfile, EXECABI_MAXHEADER - 2);
	if unlikely(!execline_end) {
		size_t extlen;
		char *ptr;
		/* The end of the leading line may be apart of an extended header. */
		ext_header = (char *)kmalloc(CONFIG_MODSHEBANG_INTERPRETER_LINEMAX, GFP_NORMAL);
		ptr        = (char *)mempcpy(ext_header, args->ea_header + 2, EXECABI_MAXHEADER - 2);
#define MAX_EXTSIZE (CONFIG_MODSHEBANG_INTERPRETER_LINEMAX - (EXECABI_MAXHEADER - 2))
		extlen = mfile_read(args->ea_xfile, ptr, MAX_EXTSIZE, (pos_t)(EXECABI_MAXHEADER - 2));
		if (extlen < MAX_EXTSIZE)
			bzero(ptr + extlen, MAX_EXTSIZE - extlen);
#undef MAX_EXTSIZE
		execfile     = ext_header;
		execline_end = find_eol(execfile, CONFIG_MODSHEBANG_INTERPRETER_LINEMAX);
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
#define HAS_SCRIPT_MAKEABS()    (args->ea_xdentry != NULL)
	{
		/* Load the interpreter program. */
		REF struct path /*   */ *interp_path;
		REF struct fdirent /**/ *interp_dentry;
		REF struct fnode /*  */ *interp_node;
		{
			u32 lnks = atomic_read(&THIS_FS->fs_lnkmax);
			interp_node = path_traversefull_ex(args->ea_xpath, &lnks, execfile, 0,
			                                   &interp_path, &interp_dentry);
		}
		TRY {
			char *inject_arg0, *inject_arg1, *inject_arg2;
			size_t more_argc;

			/* In order to allow for execution, the file itself must support mmaping.
			 * It's  not OK if the file can be mmap'd indirectly, or if mmap has been
			 * disabled for the file. */
			if unlikely(!mfile_hasrawio(interp_node))
				THROW(E_NOT_EXECUTABLE_NOT_REGULAR);

			/* Check for execute permissions? */
			fnode_access(interp_node, R_OK | X_OK);

			/* Construct a new set to arguments to-be injected. */
			more_argc = 1;
			if (HAS_OPTIONAL_ARGUMENT())
				++more_argc;
			if (HAS_SCRIPT_MAKEABS())
				++more_argc;
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

			inject_arg2 = NULL;
			if (HAS_SCRIPT_MAKEABS()) {
				TRY {
					/* The absolute pathname of the interpreter. */
					inject_arg2 = path_aprintent(args->ea_xpath,
					                             args->ea_xdentry->fd_name,
					                             args->ea_xdentry->fd_namelen);
				} EXCEPT {
					kfree(inject_arg1);
					kfree(inject_arg0);
					RETHROW();
				}

				/* Clip the first element of the original argument vector,
				 * because we replace that argument with an absolute path. */
#ifdef __ARCH_HAVE_COMPAT
				if (args->ea_argv_is_compat) {
					args->ea_argv = (execabi_strings_t)((uintptr_t)args->ea_argv + sizeof(compat_uintptr_t));
				} else
#endif /* __ARCH_HAVE_COMPAT */
				{
					args->ea_argv = (execabi_strings_t)((uintptr_t)args->ea_argv + sizeof(uintptr_t));
				}
			}

			/* Keep arguments that were already supposed to be
			 * injected, however inject  those after the  ones
			 * that we're supposed to inject. */
			memmoveup(args->ea_argv_inject + more_argc,
			          args->ea_argv_inject,
			          args->ea_argc_inject,
			          sizeof(char *));

			/* Actually inject the 1-3 arguments. */
			{
				char **dst = args->ea_argv_inject;
				*dst++ = inject_arg0;
				if (inject_arg1 != NULL)
					*dst++ = inject_arg1;
				if (inject_arg2 != NULL)
					*dst++ = inject_arg2;
				assertf(dst == args->ea_argv_inject + more_argc,
				        "Wrong number of injected arguments "
				        "(expected: %" PRIuSIZ ", got: %" PRIuSIZ ")",
				        more_argc, (size_t)(dst - args->ea_argv_inject));
			}
			args->ea_argc_inject += more_argc;
		} EXCEPT {
			decref_unlikely(interp_path);
			decref_unlikely(interp_dentry);
			decref_unlikely(interp_node);
			RETHROW();
		}

		/* Replace the exec-path with that of the interpreter. */
		decref_unlikely(args->ea_xpath);
		xdecref_unlikely(args->ea_xdentry);
		decref_unlikely(args->ea_xfile);
		args->ea_xpath   = interp_path;   /* Inherit reference */
		args->ea_xdentry = interp_dentry; /* Inherit reference */
		args->ea_xfile   = interp_node;   /* Inherit reference */
	}
#undef HAS_OPTIONAL_ARGUMENT
#undef HAS_SCRIPT_MAKEABS

	/* Tell our caller to restart interpretation. */
	return EXECABI_EXEC_RESTART;
}



#ifndef BUILDING_KERNEL_CORE
PRIVATE struct execabi bangabi = EXECABI_INIT_SHEBANG;
PRIVATE DRIVER_INIT void KCALL init(void) {
	execabis_register(&bangabi);
}
#endif /* BUILDING_KERNEL_CORE */

DECL_END

#endif /* !GUARD_MODELF_ELF_C */
