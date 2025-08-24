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
#ifndef GUARD_LIBDL_BUILTIN_C
#define GUARD_LIBDL_BUILTIN_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#define _KOS_ALTERATIONS_SOURCE 1

/* Keep this one the first */
#include "api.h"

#include "dl.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/__asm.h>
#include <hybrid/align.h>
#include <hybrid/sched/atomic-owner-rwlock.h>
#include <hybrid/sched/atomic-rwlock.h>
#include <hybrid/sequence/list.h>

#include <asm/asmword.h>
#include <kos/anno.h>
#include <kos/debugtrap.h>
#include <kos/exec/elf.h>
#include <kos/exec/peb.h>
#include <kos/kernel/types.h>
#include <kos/syscalls.h>
#include <kos/types.h>
#include <sys/mman.h>
#include <sys/syslog.h>
#include <sys/types.h>

#include <assert.h>
#include <atomic.h>
#include <dlfcn.h>
#include <elf.h>
#include <errno.h>
#include <format-printer.h>
#include <inttypes.h>
#include <link.h>
#include <malloc.h>
#include <signal.h> /* SIGABRT */
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <libdl/api.h>
#include <libdl/bits/dlfcn.h>
#include <libdl/extension.h>
#include <libdl/module.h>
#include <libdl/tls.h>
#include <libzlib/api.h>
#include <libzlib/error.h>
#include <libzlib/inflate.h>

#include "builtin.h"
#include "ucall.h"

DECL_BEGIN

typedef ATTR_CONST_T WUNUSED_T char const *
NOTHROW_T(LIBCCALL *LPSTRERRORNAME_NP)(errno_t errnum);

PRIVATE bool inside_dl_strerrorname_np = false;

/* Try to lookup `strerrorname_np()' and use it to query the name of `error'
 * If no such  symbol exists (i.e.  `libc' hasn't been  loaded), or if  that
 * functions returned `NULL', simply return `NULL', too. */
INTERN WUNUSED char const *FCALL
dl_strerrorname_np(errno_t error) {
	char const *result = NULL;
	if (!inside_dl_strerrorname_np) { /* Protect against recursion */
		LPSTRERRORNAME_NP cb;
		inside_dl_strerrorname_np = true;
		*(void **)&cb = libdl_dlsym((DlModule *)RTLD_DEFAULT, "strerrorname_np");
		if (cb != NULL)
			result = (*cb)(error);
		inside_dl_strerrorname_np = false;
	}
	return result;
}

/* Same as `dl_strerrorname_np()', but automatically provide a fallback mechanism. */
INTERN ATTR_RETNONNULL WUNUSED char const *FCALL
dl_strerrorname_np_s(errno_t error, char fallback_buf[DL_STRERRORNAME_FALLBACK_LEN]) {
	char const *result = dl_strerrorname_np(error);
	if (result == NULL) {
		sprintf(fallback_buf, "error %u", error);
		result = fallback_buf;
	}
	return result;
}


INTERN NONNULL((2)) ssize_t
NOTHROW_RPC(FORMATPRINTER_CC syslog_printer)(void *arg,
                                             NCX char const *data,
                                             size_t datalen)
		THROWS(E_SEGFAULT) {
	return sys_Xsyslog((syscall_ulong_t)arg, data, datalen);
}

#ifndef NDEBUG
INTERN uintptr_t __stack_chk_guard = 0x123baf37;
DEFINE_INTERN_ALIAS(__stack_chk_fail, __stack_chk_fail_local);
INTERN ATTR_NORETURN void __stack_chk_fail_local(void) {
	struct debugtrap_reason r;
	void *pc = __builtin_return_address(0);
	syslog(LOG_ERR, "[rtld] Stack check failure [pc=%p]\n", pc);
	r.dtr_signo  = SIGABRT;
	r.dtr_reason = DEBUGTRAP_REASON_NONE;
	sys_debugtrap(NULL, &r);
	sys_exit_group(EXIT_FAILURE);
}

struct assert_args {
	char const  *expr;
	char const  *file;
	unsigned int line;
	char const  *func;
	char const  *format;
	va_list      args;
	void        *pc;
};

PRIVATE ATTR_NOINLINE ATTR_NORETURN NONNULL((1)) void
/*NOTHROW*/ (LIBCCALL assertion_failure_core)(struct assert_args *__restrict args) {
	syslog(LOG_ERR, "[rtld] Assertion Failure [pc=%p]\n", args->pc);
	syslog(LOG_ERR, "%s(%d) : %s%s%s\n",
	       args->file, args->line,
	       args->func ? args->func : "",
	       args->func ? " : " : "",
	       args->expr);
	if (args->format) {
		va_list vargs;
		va_copy(vargs, args->args);
		format_vprintf(&syslog_printer,
		               SYSLOG_PRINTER_CLOSURE(LOG_ERR),
		               args->format, vargs);
		va_end(vargs);
		syslog(LOG_ERR, "\n");
	}
	{
		struct debugtrap_reason r;
		r.dtr_signo  = SIGABRT;
		r.dtr_reason = DEBUGTRAP_REASON_NONE;
		sys_debugtrap(NULL, &r);
	}
	sys_exit_group(EXIT_FAILURE);
}


INTERN ATTR_COLD ATTR_NORETURN void
/*NOTHROW*/ (LIBCCALL __afail)(char const *expr, char const *file,
                               unsigned int line, char const *func) {
	struct assert_args aargs;
	bzero(&aargs, sizeof(aargs));
	aargs.expr = expr;
	aargs.file = file;
	aargs.line = line;
	aargs.func = func;
	aargs.pc   = __builtin_return_address(0);
	assertion_failure_core(&aargs);
}

INTERN ATTR_COLD ATTR_NORETURN void
/*NOTHROW*/ (VLIBCCALL __afailf)(char const *expr, char const *file,
                                 unsigned int line, char const *func,
                                 char const *format, ...) {
	struct assert_args aargs;
	va_start(aargs.args, format);
	aargs.expr   = expr;
	aargs.file   = file;
	aargs.line   = line;
	aargs.func   = func;
	aargs.format = format;
	aargs.pc     = __builtin_return_address(0);
	assertion_failure_core(&aargs);
	/*va_end(args);*/
}

#endif /* !NDEBUG */



/* Return  and clear the  current libdl error message  string, such that for
 * any error that occurs, this function will only returns non-NULL once. The
 * returned string has a human-readable format and is generated dynamically,
 * meaning that it  may contain  information that  is more  specific than  a
 * simple  `File or directory not found' message, but rather something along
 * the  lines  of  `Symbol "foo" could not be found in library "libfoo.so"'.
 * The implementation of this function looks like:
 * >> return atomic_xch(&error_message_pointer, NULL);
 *
 * Where internally, libdl will set `error_message_pointer' to a non-NULL pointer
 * when an error happens.
 * @return: * :   A pointer  to a  volatile (as  in: the  same memory  area may  be
 *                overwritten once the next dl-error happens in either the calling,
 *                !_or any other thread_!), human-readable description of the  last
 *                error that  happened during  execution of  any of  the  functions
 *                exported from libdl.
 * @return: NULL: No error happened, or the last error has already been consumed. */
INTERN char *NOTHROW(DLFCN_CC libdl_dlerror)(void) {
	return atomic_xch(&dl_globals.dg_errmsg, NULL);
}


INTERN ATTR_COLD int NOTHROW(CC dl_seterror_badptr)(void *ptr) {
	return dl_seterrorf("Bad pointer: %p", ptr);
}

INTERN ATTR_COLD int NOTHROW(CC dl_seterror_badmodule)(void *modptr) {
	return dl_seterrorf("Bad module handle: %p", modptr);
}

INTERN ATTR_COLD int NOTHROW(CC dl_seterror_badsection)(void *sectptr) {
	return dl_seterrorf("Bad section handle: %p", sectptr);
}

INTERN ATTR_COLD NONNULL((1)) int
NOTHROW(CC dl_seterror_header_read_error)(char const *__restrict filename, errno_t error) {
	char buf[DL_STRERRORNAME_FALLBACK_LEN];
	return dl_seterrorf("%q: Failed to read headers: %s",
	                    filename,
	                    dl_strerrorname_np_s(error, buf));
}

INTERN ATTR_COLD NONNULL((1)) int
NOTHROW(CC dl_seterror_notelf)(char const *__restrict filename) {
	return dl_seterrorf("%q: Not an ELF object", filename);
}

INTERN ATTR_COLD NONNULL((1, 2)) int
NOTHROW_NCX(CC dl_seterror_nosect)(NCX DlModule const *self,
                                   NCX char const *name)
		THROWS(E_SEGFAULT) {
	return dl_seterrorf("%q: No such section %q",
	                    self->dm_filename, name);
}

INTERN ATTR_COLD int
NOTHROW(CC dl_seterror_no_mod_at_addr)(NCX void const *static_pointer) {
	return dl_seterrorf("Address %p does not map to any module",
	                    static_pointer);
}

INTERN ATTR_COLD NONNULL((1)) int
NOTHROW_NCX(CC dl_seterror_nosect_index)(NCX DlModule const *self, size_t index)
		THROWS(E_SEGFAULT) {
	return dl_seterrorf("%q: Section index %" PRIuSIZ " is greater than %" PRIuSIZ,
	                    self->dm_filename, index, self->dm_shnum);
}

INTERN ATTR_COLD NONNULL((1)) int
NOTHROW_NCX(CC dl_seterror_nosym_global)(NCX char const *symname)
		THROWS(E_SEGFAULT) {
	return dl_seterrorf("No global module contains a symbol %q", symname);
}

INTERN ATTR_COLD NONNULL((1, 2)) int
NOTHROW_NCX(CC dl_seterror_nosym_next)(DlModule const *__restrict after,
                                       NCX char const *symname)
		THROWS(E_SEGFAULT) {
	return dl_seterrorf("No module loaded after %q contains a symbol %q",
	                    after->dm_filename, symname);
}

INTERN ATTR_COLD NONNULL((1, 2)) int
NOTHROW_NCX(CC dl_seterror_nosym_in)(NCX DlModule const *mod,
                                     NCX char const *symname)
		THROWS(E_SEGFAULT) {
	return dl_seterrorf("%q: Unknown symbol %q",
	                    mod->dm_filename, symname);
}

INTERN ATTR_COLD NONNULL((1)) int
NOTHROW_NCX(CC dl_seterror_nosym_next_badcaller)(NCX char const *symname)
		THROWS(E_SEGFAULT) {
	(void)symname;
	return dl_seterrorf("`RTLD_NEXT' used from externally loaded code");
}

INTERN ATTR_COLD NONNULL((1)) int
NOTHROW_NCX(CC dl_seterror_dlopen_failed)(NCX char const *libname)
		THROWS(E_SEGFAULT) {
	return dl_seterrorf("Failed to open library %q", libname);
}

INTERN ATTR_COLD NONNULL((1, 2)) int
NOTHROW_NCX(CC dl_seterr_section_mmap_failed)(NCX DlModule const *self,
                                              NCX char const *section_filename,
                                              errno_t error)
		THROWS(E_SEGFAULT) {
	char buf[DL_STRERRORNAME_FALLBACK_LEN];
	return dl_seterrorf("%q: Failed to map section %q into memory: %s",
	                    self->dm_filename, section_filename,
	                    dl_strerrorname_np_s(error, buf));
}

INTERN ATTR_COLD NONNULL((1)) int
NOTHROW_NCX(CC dl_seterr_section_index_mmap_failed)(NCX DlModule const *self,
                                                    size_t section_index,
                                                    errno_t error)
		THROWS(E_SEGFAULT) {
	char buf[DL_STRERRORNAME_FALLBACK_LEN];
	return dl_seterrorf("%q: Failed to map section #%" PRIuSIZ " into memory: %s",
	                    self->dm_filename, section_index,
	                    dl_strerrorname_np_s(error, buf));
}



PRIVATE char const message_nomem[] = "Insufficient memory";
INTERN ATTR_COLD int NOTHROW(CC dl_seterror_nomem)(void) {
	memcpy(dl_globals.dg_errbuf, message_nomem, sizeof(message_nomem));
	atomic_write(&dl_globals.dg_errmsg, (char *)dl_globals.dg_errbuf);
	return -1;
}

INTERN ATTR_COLD NONNULL((1)) int
NOTHROW_NCX(VCC dl_seterrorf)(char const *__restrict format, ...) {
	int result;
	va_list args;
	va_start(args, format);
	result = dl_vseterrorf(format, args);
	va_end(args);
	return result;
}

INTERN ATTR_COLD NONNULL((1)) int
NOTHROW_NCX(CC dl_vseterrorf)(char const *__restrict format, va_list args) {
	vsnprintf(dl_globals.dg_errbuf, sizeof(dl_globals.dg_errbuf), format, args);
	atomic_write(&dl_globals.dg_errmsg, (char *)dl_globals.dg_errbuf);
	return -1;
}



/* Lock used to ensure that only a single thread can ever load modules
 * at the same time (used to prevent potential race conditions arising
 * from the fact that various components must be accessed globally). */
PRIVATE struct atomic_owner_rwlock DlModule_LoadLock = ATOMIC_OWNER_RWLOCK_INIT;

INTERN NONNULL((1)) void
NOTHROW(CC DlModule_UpdateFlags)(DlModule *__restrict self, int mode) {
	uintptr_t old_flags;
again_old_flags:
	old_flags = atomic_read(&self->dm_flags);
	if ((mode & RTLD_GLOBAL) && !(old_flags & RTLD_GLOBAL)) {
		/* Make the module global. */
		dlglobals_global_write(&dl_globals);
		if (!atomic_cmpxch_weak(&self->dm_flags, old_flags,
		                        old_flags | RTLD_GLOBAL)) {
			dlglobals_global_endwrite(&dl_globals);
			goto again_old_flags;
		}
		assert(!TAILQ_ISBOUND(self, dm_globals));
		dlglobals_global_add(&dl_globals, self);
		dlglobals_global_endwrite(&dl_globals);
	}
}



/* Function to implement `LD_TRACE_LOADED_OBJECTS' */
#ifdef HAVE_dl_trace_loaded_objects
PRIVATE ssize_t FORMATPRINTER_CC
dl_fd_printer(void *arg, /*utf-8*/ char const *__restrict data, size_t datalen) {
	fd_t fd = (fd_t)(uintptr_t)arg;
	ssize_t result = sys_write(fd, data, datalen);
	while (E_ISOK(result) && (size_t)result < datalen) {
		ssize_t temp;
		temp = sys_write(fd, data + (size_t)result,
		                 datalen - (size_t)result);
		if unlikely(E_ISERR(temp)) {
			result = temp;
			break;
		}
		result += (size_t)temp;
	}
	return result;
}

PRIVATE void VCC dl_printf(char const *format, ...) {
	va_list args;
	va_start(args, format);
	format_vprintf(&dl_fd_printer, (void *)(uintptr_t)STDOUT_FILENO, format, args);
	va_end(args);
}

#undef PRIdotnP
#if __SIZEOF_POINTER__ == 4
#define PRIdotnP ".8"
#elif __SIZEOF_POINTER__ == 8
#define PRIdotnP ".16"
#elif __SIZEOF_POINTER__ == 2
#define PRIdotnP ".4"
#elif __SIZEOF_POINTER__ == 1
#define PRIdotnP ".2"
#else /* __SIZEOF_POINTER__ == ... */
#define PRIdotnP ""
#endif /* __SIZEOF_POINTER__ != ... */

INTERN void CC dl_trace_loaded_objects(void) {
	DlModule *mod;
	for (mod = DLIST_LAST(&dl_globals.dg_alllist, dm_modules);
	     mod != NULL; mod = DLIST_PREV(mod, dm_modules)) {
		char *filename = mod->dm_filename;
		char *name     = strrchrnul(filename, '/') + 1;
		dl_printf("\t%s => %s (%#" PRIdotnP "x)\n",
		          name, filename, mod->dm_loadstart);
	}
	sys_exit_group(0);
}
#endif /* HAVE_dl_trace_loaded_objects */


/* Lazily load a shared library file, and return a handle to said file.
 * @param: filename: The filename of the shared library.
 *                   If  this string contains  at least 1 '/'-character,
 *                   the string will be  interpreted as a raw  filename,
 *                   such that passing it to open(2) would return a file
 *                   handle for the named library file.
 *                   In this case, `filename' may either be an absolute path,
 *                   or a path relative to the current working directory,  as
 *                   set by `chdir(2)'
 *                   If  `filename'  doesn't  contain  any  '/'-characters,  the  string
 *                   is  the  filename  of the  library  (e.g. "libc.so"),  and  will be
 *                   searched for in the set  of system library locations, as  specified
 *                   by  a  ':'-separated string  read  from `getenv("LD_LIBRARY_PATH")'
 *                   at  the time of  the process having been  started, or defaulting to
 *                   a set of paths that include at least "/usr/lib:/lib" in that order.
 *                   When `NULL' is  passed for  this argument,  a handle  for the  main
 *                   executable module  (i.e. the  `readlink /proc/self/exe' binary)  is
 *                   returned.
 * @param: mode:     Exactly  one  of  [RTLD_LAZY, RTLD_NOW],  or'd  with
 *                   exactly one of [RTLD_GLOBAL, RTLD_LOCAL], optionally
 *                   or'd with any of the other `RTLD_*' flags.
 * @return: * :   A handle to the library that got loaded.
 * @return: NULL: Failed to load the library. - Call `dlerror()' to get an error message. */
INTERN WUNUSED REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *DLFCN_CC
libdl_dlopen(NCX char const *filename, int mode)
		THROWS(E_SEGFAULT, ...) {
	REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *result;
	if unlikely(!filename) {
		/* ... If filename is NULL, then the returned handle is for the main program... */
		result = dlglobals_mainapp(&dl_globals);
		assert(result);
		assert(result->dm_flags & RTLD_NODELETE);
		/* Don't incref() the returned module for this case:
		 *   - The main module itself was loaded with `RTLD_NODELETE', meaning
		 *     that attempts to  dlclose() that module  are already no-ops  to
		 *     begin with. */
		return result;
	}
	atomic_owner_rwlock_write(&DlModule_LoadLock);
again:
	if (mode & RTLD_NOLOAD) {
		/* Don't open a new module */
		if (strchr(filename, '/')) {
			result = DlModule_FindFromFilename(filename);
		} else {
			atomic_write(&dl_globals.dg_errmsg, NULL);
			result = DlModule_FindFilenameInPathListFromAll(filename);
		}
		if likely(result)
			DlModule_UpdateFlags(result, mode);
	} else {
		if (strchr(filename, '/')) {
			/* Load a module from an absolute filesystem location. */
			result = DlModule_OpenFilename(filename, mode);
		} else {
			/* Load a module using the LD-library path List */
			atomic_write(&dl_globals.dg_errmsg, NULL);
			result = DlModule_OpenFilenameInPathList(dl_globals.dg_libpath,
			                                         filename, mode, NULL);
		}
	}
	if unlikely(!result) {
		if (!atomic_read(&dl_globals.dg_errmsg))
			dl_seterror_dlopen_failed(filename);
	} else {
		while unlikely(result->dm_flags & RTLD_LOADING) {
			/* The library is still being initialized by another thread. */
			if (atomic_read(&result->dm_refcnt) <= 1) {
				/* The module is supposed to go away! (try to load it again) */
				if (!(result->dm_flags & RTLD_NODELETE))
					decref(result);
				goto again;
			}
			sys_sched_yield();
		}
	}
/*done:*/
	atomic_owner_rwlock_endwrite(&DlModule_LoadLock);
	return result;
}


/* Close  a  previously  opened  dynamic  module  handle,  as  returned by
 * `dlopen(3D)',  and  some of  the other  functions  found in  this file.
 * Note  that  this call  is implemented  as  a decref()  operation, since
 * multiple calls to `dlopen(3D)' for the same library will try to  ensure
 * that  only  a single  instance of  some unique  library is  ever loaded
 * at the same time. However, every call to `dlopen(3D)' should eventually
 * be followed by a call to `dlclose(3D)' with that same handle, such that
 * once some specific handle is closed for the last time, the library  can
 * be unloaded.
 * Note  also that  if this function  does actually unload  a library, user-
 * defined callbacks may be invoked, including `__attribute__((destructor))'
 * callbacks,  as well  as callbacks  registered dynamically  through use of
 * `DLAUXCTRL_ADD_FINALIZER' (which in turn is used by `__cxa_atexit()')
 * @return: 0 : Successfully closed the given handle.
 * @return: * : Failed to close the handle  (which is likely to simply  be
 *              invalid; s.a. `dlerror()') Warning: Don't just willy-nilly
 *              pass invalid handles  to this function.  Depending on  how
 *              libdl  was  configured,  only  minimal  validation  may be
 *              performed.  The  only guaranty  made is  that NULL-handles
 *              are always handled as fail-safe! */
INTERN NONNULL((1)) int DLFCN_CC
libdl_dlclose(NCX REF_IF(!(self->dm_flags & RTLD_NODELETE)) DlModule *self)
		THROWS(E_SEGFAULT, ...) {
	if unlikely(!DL_VERIFY_MODULE_HANDLE(self))
		goto err_bad_module;
	/* Don't decref NODELETE modules! */
	if likely(!(self->dm_flags & RTLD_NODELETE))
		decref(self);
	return 0;
err_bad_module:
	return dl_seterror_badmodule(self);
}


/* Check if a given module is exception aware.
 * TODO: Figure out how we want to detect this condition...
 * @param: handle: The module to check
 * @return: 1 : The given module is exception aware
 * @return: 0 : The given module isn't exception aware
 * @return: * : The given module handler is invalid (s.a. `dlerror()') */
INTERN WUNUSED NONNULL((1)) int
NOTHROW_NCX(DLFCN_CC libdl_dlexceptaware)(NCX DlModule *self) THROWS(E_SEGFAULT) {
	if unlikely(!DL_VERIFY_MODULE_HANDLE(self))
		goto err_bad_module;
	/* TODO */
	return 1;
err_bad_module:
	return dl_seterror_badmodule(self);
}

struct dl_symbol {
	DlModule        *ds_mod; /* [1..1] The associated module */
	ElfW(Sym) const *ds_sym; /* [1..1] The actual symbol (or its address for custom module). */
};


typedef ElfW(Addr) (*dl_indirect_resolver_t)(void);

PRIVATE ATTR_NOINLINE WUNUSED ATTR_OUT(2) NONNULL((1, 3)) int CC
dl_symbol_resolve_indirect(struct dl_symbol const *__restrict symbol,
                           ElfW(Addr) *__restrict p_result,
                           dl_indirect_resolver_t resolver) {
	/* TODO: Remember saved value?
	 *
	 * Note that ".dynsym" is generally read-only, meaning we can't just do what
	 * the kernel's module ELF loader  does, and override the ".dynsym"  entries
	 * with STT_FUNC/STT_OBJECT entries!
	 *
	 * There needs to be a lookup table of indirect symbols and their known
	 * resolve addresses. */
	(void)symbol;
	*p_result = (ElfW(Addr))libdl_ucall0(resolver);
	return 0;
}

PRIVATE WUNUSED ATTR_OUT(2) NONNULL((1)) int CC
dl_symbol_resolve(struct dl_symbol const *__restrict symbol,
                  ElfW(Addr) *__restrict p_result) {
	ElfW(Sym) const *esym = symbol->ds_sym;
	ElfW(Addr) result = esym->st_value;
	switch (ELFW(ST_TYPE)(esym->st_info)) {

	case STT_TLS: {
		void *tlsbase = libdl_dltlsaddr(symbol->ds_mod);
		if unlikely(!tlsbase)
			goto err;
		result += (ElfW(Addr))tlsbase;
	}	break;

	case STT_GNU_IFUNC:
	case STT_KOS_IDATA:
		if (esym->st_shndx != SHN_ABS)
			result += symbol->ds_mod->dm_loadaddr;
		return dl_symbol_resolve_indirect(symbol, p_result, (dl_indirect_resolver_t)result);

	default:
		if (esym->st_shndx != SHN_ABS)
			result += symbol->ds_mod->dm_loadaddr;
		break;
	}
	*p_result = result;
	return 0;
err:
	return -1;
}


#define DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NOT_FOUND 0
#define DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_FOUND     1
#define DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NO_MODULE 2
#define DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_ERROR     3
PRIVATE NONNULL((1, 2, 3, 4, 5, 6)) unsigned int CC
dlmodule_search_symbol_in_dependencies(DlModule *__restrict self,
                                       NCX char const *name,
                                       uintptr_t *__restrict phash_elf,
                                       uintptr_t *__restrict phash_gnu,
                                       ElfW(Addr) *__restrict presult,
                                       struct dl_symbol *__restrict pweak_symbol,
                                       size_t depth)
		THROWS(E_SEGFAULT, ...) {
	struct dl_symbol symbol;
	size_t i;
	if (!self->dm_depcnt)
		return DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NO_MODULE;
	if (depth != 0) {
		unsigned int result, error;
		--depth;
		result = DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NO_MODULE;
		for (i = 0; i < self->dm_depcnt; ++i) {
			error = dlmodule_search_symbol_in_dependencies(self->dm_depvec[i],
			                                               name,
			                                               phash_elf,
			                                               phash_gnu,
			                                               presult,
			                                               pweak_symbol,
			                                               depth);
			/* Check if the symbol was found. */
			if (error == DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_FOUND ||
			    error == DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_ERROR)
				return error;
			/* If at least 1 module was searched, unlock the next depth-level. */
			if (error == DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NOT_FOUND)
				result = DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NOT_FOUND;
		}
		return result;
	}
	for (i = 0; i < self->dm_depcnt; ++i) {
		symbol.ds_mod = self->dm_depvec[i];
		if (symbol.ds_mod == &dl_rtld_module) {
			/* Special case: Search the RTLD module itself. */
			void *addr;
			addr = dlsym_builtin(name);
			if (addr) {
				*presult = (ElfW(Addr))addr;
				return DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_FOUND;
			}
			continue;
		}
		if (symbol.ds_mod->dm_ops) {
			int error;
			error = (*symbol.ds_mod->dm_ops->df_dlsym)(symbol.ds_mod, name,
			                                           (void **)&symbol.ds_sym, NULL);
			if (error >= 0) {
				/* Found a symbol! */
				if (error > 0) {
					/* Weak definition (remember if this is the first one) */
					if (!pweak_symbol->ds_mod)
						*pweak_symbol = symbol;
				} else {
					/* Found the real, actual symbol! */
					*presult = (ElfW(Addr))symbol.ds_sym;
					return DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_FOUND;
				}
			}
			continue;
		}
		symbol.ds_sym = DlModule_ElfGetLocalSymbol(symbol.ds_mod,
		                                           name,
		                                           phash_elf,
		                                           phash_gnu);
		if (symbol.ds_sym &&
		    symbol.ds_sym->st_shndx != SHN_UNDEF) {
			/* Found a symbol! */
			if (ELFW(ST_BIND)(symbol.ds_sym->st_info) == STB_WEAK) {
				/* Weak definition (remember if this is the first one) */
				if (!pweak_symbol->ds_mod)
					*pweak_symbol = symbol;
			} else {
				/* Found the real, actual symbol! */
				if unlikely(dl_symbol_resolve(&symbol, presult))
					return DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_ERROR;
				return DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_FOUND;
			}
		}
	}
	return DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NOT_FOUND;
}

/* Lookup the load address of a  symbol within a shared library  `handle',
 * given  its `symbol_name'. If no such symbol exists, `NULL' is returned,
 * and `dlerror(3D)' is modified to return a human-readable error message.
 * WARNING: If  the actual address of the symbol is `NULL', then this
 *          function will still return `NULL', though will not modify
 *          the return value of `dlerror(3D)'.
 *          In normal applications, this would normally never be the case,
 *          as  libdl, as well as `ld', will  take care not to link object
 *          files such that symbols could end up overlapping with  `NULL'.
 *          However, with the existence of `STT_GNU_IFUNC' (as usable  via
 *          `__attribute__((ifunc("resolver")))'), it  is easily  possible
 *          to force some symbol to overlap with NULL.
 *          Also note that upon success,  `dlerror(3D)' will not have  been
 *          modified, meaning that if a prior error has yet to be consumed,
 *          a NULL return value, and a non-NULL `dlerror(3D)' may still not
 *          guaranty that the symbol really doesn't exist. To be absolutely
 *          certain  that  NULL  would  be  correct,  use  the   following:
 *          >> void *result;
 *          >> dlerror(); // Clear preceding error
 *          >> result = dlsym(handle, symbol_name);
 *          >> if (result == NULL) {
 *          >>     char *message = dlerror();
 *          >>     if (message != NULL) // Symbol lookup really failed.
 *          >>         fprintf(stderr, "dlerror: %s\n", message);
 *          >> }
 * @param: handle: The dynamic library handle of  the library which should  be
 *                 searched  for the specified `symbol_name', before moving on
 *                 to also search all of those libraries' dependencies for the
 *                 same `symbol_name', and  so on,  following a  breadth-first
 *                 search approach.
 *                 Alternatively, you may also pass `RTLD_DEFAULT' or `RTLD_NEXT'
 *                 to make use  of special symbol  lookup resolutions  documented
 *                 more extensively alongside these constants.
 * @return: * :    The address of the symbol in question.
 * @return: NULL:  No such symbol  (`dlerror() != NULL'), or the  symbol has  been
 *                 linked to be loaded at the address `NULL' (`dlerror() == NULL') */
INTERN WUNUSED NONNULL((2)) void *DLFCN_CC
libdl_dlsym(NCX DlModule *self, NCX char const *symbol_name)
		THROWS(E_SEGFAULT, ...) {
	ElfW(Addr) result;
	uintptr_t hash_elf, hash_gnu;
	struct dl_symbol symbol;
	struct dl_symbol weak_symbol;
	REF DlModule *next_module;
	hash_elf = hash_gnu = DLMODULE_GETLOCALSYMBOL_HASH_UNSET;
	weak_symbol.ds_mod  = NULL;
	if (self == RTLD_DEFAULT) {
		/* Search all modules in order of being loaded. */
		dlglobals_global_read(&dl_globals);
		symbol.ds_mod = TAILQ_FIRST(&dl_globals.dg_globallist);
		assert(symbol.ds_mod);
		for (;;) {
			if unlikely(!tryincref(symbol.ds_mod)) {
again_search_globals_next_noref:
				symbol.ds_mod = TAILQ_NEXT(symbol.ds_mod, dm_globals);
				if unlikely(!symbol.ds_mod) {
					dlglobals_global_endread(&dl_globals);
					break;
				}
				continue;
			}
			dlglobals_global_endread(&dl_globals);
again_search_globals_module:
			/* Search this module. */
			if (symbol.ds_mod == &dl_rtld_module) {
				result = (ElfW(Addr))dlsym_builtin(symbol_name);
				if (result) {
					decref_nokill(symbol.ds_mod);
					goto done;
				}
			} else if (symbol.ds_mod->dm_ops) {
				int error;
				error = (*symbol.ds_mod->dm_ops->df_dlsym)(symbol.ds_mod, symbol_name,
				                                           (void **)&symbol.ds_sym, NULL);
				if (error >= 0) {
					if (error > 0) {
						/* Weak definition. */
						if (!weak_symbol.ds_mod) {
							weak_symbol = symbol; /* First weak def */
						} else {
							decref(symbol.ds_mod); /* Second weak def */
						}
					} else {
						/* Found the symbol! */
						if (weak_symbol.ds_mod)
							decref(weak_symbol.ds_mod);
						result = (ElfW(Addr))symbol.ds_sym;
						decref(symbol.ds_mod);
						goto done;
					}
				}
			} else {
				symbol.ds_sym = DlModule_ElfGetLocalSymbol(symbol.ds_mod,
				                                           symbol_name,
				                                           &hash_elf,
				                                           &hash_gnu);
				if (symbol.ds_sym &&
				    symbol.ds_sym->st_shndx != SHN_UNDEF) {
					if (ELFW(ST_BIND)(symbol.ds_sym->st_info) == STB_WEAK) {
						/* Weak definition. */
						if (!weak_symbol.ds_mod) {
							weak_symbol = symbol; /* First weak def */
						} else {
							decref(symbol.ds_mod); /* Second weak def */
						}
					} else {
						/* Found the symbol! */
						if (weak_symbol.ds_mod)
							decref(weak_symbol.ds_mod);
						RAII_FINALLY { decref(symbol.ds_mod); };
						if unlikely(dl_symbol_resolve(&symbol, &result))
							goto err;
						goto done;
					}
				}
			}
			dlglobals_global_read(&dl_globals);
			next_module = TAILQ_NEXT(symbol.ds_mod, dm_globals);
			while (likely(next_module) && unlikely(!tryincref(next_module)))
				next_module = TAILQ_NEXT(next_module, dm_globals);
			dlglobals_global_endread(&dl_globals);
			decref(symbol.ds_mod);
			if unlikely(!next_module)
				break;
			symbol.ds_mod = next_module;
			goto again_search_globals_module;
		}
		/* Check if we found a weak symbol at one point! */
		if likely(weak_symbol.ds_mod) {
			RAII_FINALLY { decref(weak_symbol.ds_mod); };
			if (weak_symbol.ds_mod->dm_ops) {
				result = (ElfW(Addr))weak_symbol.ds_sym;
			} else {
				if unlikely(dl_symbol_resolve(&weak_symbol, &result))
					goto err;
			}
			goto done;
		}
		if unlikely(self == RTLD_NEXT) {
			symbol.ds_mod = libdl_dlgethandle(__builtin_return_address(0), DLGETHANDLE_FNORMAL);
			if unlikely(!symbol.ds_mod)
				goto err_rtld_next_no_base;
			dl_seterror_nosym_next(symbol.ds_mod, symbol_name);
		} else {
			dl_seterror_nosym_global(symbol_name);
		}
	} else if (self == RTLD_NEXT) {
		symbol.ds_mod = libdl_dlgethandle(__builtin_return_address(0), DLGETHANDLE_FNORMAL);
		/* Search modules loaded after `symbol.ds_mod' */
		if unlikely(!symbol.ds_mod)
			goto err_rtld_next_no_base;
		dlglobals_global_read(&dl_globals);
		goto again_search_globals_next_noref;
	} else {
		if unlikely(self == &dl_rtld_module) {
			result = (ElfW(Addr))dlsym_builtin(symbol_name);
			if likely(result)
				goto done;
		} else {
#ifdef RTLD_SELF
			__STATIC_IF(DL_VERIFY_MODULE_HANDLE(RTLD_SELF)) {
				if unlikely(self == RTLD_SELF)
					self = libdl_dlgethandle(__builtin_return_address(0), DLGETHANDLE_FNORMAL);
			}
#endif /* RTLD_SELF */
			if unlikely(!DL_VERIFY_MODULE_HANDLE(self)) {
#ifdef RTLD_SELF
				__STATIC_IF(!DL_VERIFY_MODULE_HANDLE(RTLD_SELF)) {
					if unlikely(self == RTLD_SELF) {
						self = libdl_dlgethandle(__builtin_return_address(0), DLGETHANDLE_FNORMAL);
					} else {
						goto err_bad_module;
					}
				} __STATIC_ELSE(!DL_VERIFY_MODULE_HANDLE(RTLD_SELF))
#endif /* RTLD_SELF */
				{
					goto err_bad_module;
				}
			}
			if unlikely(self->dm_ops) {
				/* Scan the given module itself */
				int error;
				error = (*self->dm_ops->df_dlsym)(self, symbol_name, (void **)&symbol.ds_sym, NULL);
				/* Most likely case: The symbol is already apart of the specified module! */
				if likely(error >= 0) {
					if (error > 0) {
						weak_symbol.ds_mod = self;
						weak_symbol.ds_sym = symbol.ds_sym;
					} else {
						result = (ElfW(Addr))symbol.ds_sym;
						goto done;
					}
				}
			} else {
				/* Scan the given module itself */
				symbol.ds_sym = DlModule_ElfGetLocalSymbol(self,
				                                           symbol_name,
				                                           &hash_elf,
				                                           &hash_gnu);
				/* Most likely case: The symbol is already apart of the specified module! */
				if likely(symbol.ds_sym && symbol.ds_sym->st_shndx != SHN_ABS) {
					symbol.ds_mod = self;
					if (ELFW(ST_BIND)(symbol.ds_sym->st_info) == STB_WEAK) {
						weak_symbol = symbol;
					} else {
						if unlikely(dl_symbol_resolve(&symbol, &result))
							goto err;
done:
						return (void *)result;
					}
				}
			}
			/* Search dependencies of the module. */
			{
				size_t depth = 0;
				unsigned int error;
				for (;; ++depth) {
					/* Breadth-first search using a depth counter. */
					error = dlmodule_search_symbol_in_dependencies(self,
					                                               symbol_name,
					                                               &hash_elf,
					                                               &hash_gnu,
					                                               &result,
					                                               &weak_symbol,
					                                               depth);
					if (error == DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_FOUND)
						goto done;
					if (error == DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_ERROR)
						goto err;
					if (error == DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NO_MODULE)
						break;
				}
			}
			/* Check if we found a weak symbol at one point. */
			if (weak_symbol.ds_mod) {
				if (weak_symbol.ds_mod->dm_ops) {
					result = (ElfW(Addr))weak_symbol.ds_sym;
				} else {
					if unlikely(dl_symbol_resolve(&weak_symbol, &result))
						goto err;
				}
				goto done;
			}
		}
		/* Missing symbol... */
		dl_seterror_nosym_in(self, symbol_name);
	}
err:
	return NULL;
err_rtld_next_no_base:
	dl_seterror_nosym_next_badcaller(symbol_name);
	goto err;
err_bad_module:
	dl_seterror_badmodule(self);
	goto err;
}




/* Return the handle of an already loaded library, given a static data/text pointer
 * @param: flags: Set of `DLGETHANDLE_F*' */
INTERN WUNUSED REF_IF(!(return->dm_flags & RTLD_NODELETE) && (flags & DLGETHANDLE_FINCREF)) DlModule *
NOTHROW(DLFCN_CC libdl_dlgethandle)(void const *static_pointer, unsigned int flags) {
	DlModule *result;
	if unlikely(flags & ~(DLGETHANDLE_FINCREF)) {
		dl_seterrorf("Invalid flags %#x passed to `dlgethandle(3D)'", flags);
		goto err;
	}
	dlglobals_all_read(&dl_globals);
	DLIST_FOREACH (result, &dl_globals.dg_alllist, dm_modules) {
		uint16_t i;
		if ((uintptr_t)static_pointer < result->dm_loadstart)
			continue;
		if ((uintptr_t)static_pointer >= result->dm_loadend)
			continue;
		if (result->dm_ops) {
			/* Support for formats other than ELF. */
			if ((*result->dm_ops->df_ismapped)(result,
			                                   (uintptr_t)static_pointer -
			                                   result->dm_loadaddr))
				goto got_result;
		} else {
			/* Make sure that `static_pointer' maps to some program segment. */
			for (i = 0; i < result->dm_elf.de_phnum; ++i) {
				uintptr_t segment_base;
				if (result->dm_elf.de_phdr[i].p_type != PT_LOAD)
					continue;
				segment_base = result->dm_loadaddr + result->dm_elf.de_phdr[i].p_vaddr;
				if ((uintptr_t)static_pointer < segment_base)
					continue;
				if ((uintptr_t)static_pointer >= segment_base + result->dm_elf.de_phdr[i].p_memsz)
					continue;
				goto got_result;
			}
		}
	}
	dlglobals_all_endread(&dl_globals);
	dl_seterror_no_mod_at_addr(static_pointer);
err:
	return NULL;
got_result:
	/* Found the module! */
	if ((flags & DLGETHANDLE_FINCREF) &&
	    !(result->dm_flags & RTLD_NODELETE))
		incref(result);
	dlglobals_all_endread(&dl_globals);
	return result;
}


/* Return the handle of an already loaded library, given its name
 * @param: name:  One of the following (checked in this order):
 *                 - "/lib/libc.so"
 *                 - "libc.so"
 *                 - "libc"
 *                 - "c"
 *                 - "/LIB/LIBC.SO"  (requires `DLGETHANDLE_FNOCASE')
 *                 - "LIBC.SO"       (requires `DLGETHANDLE_FNOCASE')
 *                 - "LIBC"          (requires `DLGETHANDLE_FNOCASE')
 *                 - "C"             (requires `DLGETHANDLE_FNOCASE')
 *                Alternatively, `NULL' can be passed to return a handle for the caller's module.
 * @param: flags: Set of `DLGETHANDLE_F*' */
INTERN WUNUSED REF_IF(!(return->dm_flags & RTLD_NODELETE) && (flags & DLGETHANDLE_FINCREF)) DlModule *
NOTHROW_NCX(DLFCN_CC libdl_dlgetmodule)(NCX char const *name, unsigned int flags) THROWS(E_SEGFAULT) {
	DlModule *result;
	if (!name) {
		result = libdl_dlgethandle(__builtin_return_address(0), flags);
		if unlikely(!result)
			dl_seterrorf("Can only call `dlgetmodule(NULL)' from dynamically loaded code");
		return result;
	}
	if unlikely(flags & ~(DLGETHANDLE_FINCREF | DLGETHANDLE_FNOCASE)) {
		dl_seterrorf("Invalid flags %#x passed to `dlgetmodule(3D)'", flags);
		goto err;
	}
	dlglobals_all_read(&dl_globals);
	DLIST_FOREACH (result, &dl_globals.dg_alllist, dm_modules) {
		if (strcmp(result->dm_filename, name) == 0)
			goto got_result;
	}
	DLIST_FOREACH (result, &dl_globals.dg_alllist, dm_modules) {
		char *sep = strrchr(result->dm_filename, '/');
		if (!sep)
			continue;
		if (strcmp(sep + 1, name) == 0)
			goto got_result;
	}
	DLIST_FOREACH (result, &dl_globals.dg_alllist, dm_modules) {
		char *sep = strrchr(result->dm_filename, '/');
		char *col;
		size_t namelen;
		if (!sep)
			continue;
		++sep;
		col = strchr(sep, '.');
		if (!col)
			continue;
		namelen = (size_t)(col - sep);
		if (bcmp(sep, name, namelen, sizeof(char)) == 0 &&
		    name[namelen] == '\0')
			goto got_result;
	}
	DLIST_FOREACH (result, &dl_globals.dg_alllist, dm_modules) {
		char *sep = strrchr(result->dm_filename, '/');
		char *col;
		size_t namelen;
		if (!sep)
			continue;
		if (sep[1] != 'l' || sep[2] != 'i' || sep[3] != 'b')
			continue;
		sep += 4;
		col = strchr(sep, '.');
		if (!col)
			continue;
		namelen = (size_t)(col - sep);
		if (bcmp(sep, name, namelen, sizeof(char)) == 0 &&
		    name[namelen] == '\0')
			goto got_result;
	}
	if (flags & DLGETHANDLE_FNOCASE) {
		DLIST_FOREACH (result, &dl_globals.dg_alllist, dm_modules) {
			if (strcasecmp(result->dm_filename, name) == 0)
				goto got_result;
		}
		DLIST_FOREACH (result, &dl_globals.dg_alllist, dm_modules) {
			char *sep = strrchr(result->dm_filename, '/');
			if (!sep)
				continue;
			if (strcasecmp(sep + 1, name) == 0)
				goto got_result;
		}
		DLIST_FOREACH (result, &dl_globals.dg_alllist, dm_modules) {
			char *sep = strrchr(result->dm_filename, '/');
			char *col;
			size_t namelen;
			if (!sep)
				continue;
			col = strchr(sep, '.');
			if (!col)
				continue;
			++sep;
			namelen = (size_t)(col - sep);
			if (memcasecmp(sep, name, namelen * sizeof(char)) == 0 &&
			    name[namelen] == '\0')
				goto got_result;
		}
		DLIST_FOREACH (result, &dl_globals.dg_alllist, dm_modules) {
			char *sep = strrchr(result->dm_filename, '/');
			char *col;
			size_t namelen;
			if (!sep)
				continue;
			col = strchr(sep, '.');
			if (!col)
				continue;
			if (sep[1] != 'l' || sep[2] != 'i' || sep[3] != 'b')
				continue;
			sep += 4;
			namelen = (size_t)(col - sep);
			if (memcasecmp(sep, name, namelen * sizeof(char)) == 0 &&
			    name[namelen] == '\0')
				goto got_result;
		}
	}
	dlglobals_all_endread(&dl_globals);
	dl_seterrorf("Unknown module %q", name);
err:
	return NULL;
got_result:
	if ((flags & DLGETHANDLE_FINCREF) &&
	    !(result->dm_flags & RTLD_NODELETE))
		incref(result);
	dlglobals_all_endread(&dl_globals);
	return result;
}


/* >> dladdr(3D)
 * Query information on the symbol/module associated with a given `address'
 * @param: address: The address to query information about.
 * @param: info:    Output buffer for where to put information.
 * @return: 1 : Success. (yes: this function returns boolean-style)
 * @return: 0 : Error (s.a. `dlerror(3D)') */
INTERN NONNULL((2)) int
NOTHROW_NCX(DLFCN_CC libdl_dladdr)(void const *address,
                                   NCX Dl_info *info)
		THROWS(E_SEGFAULT) {
	REF DlModule *mod;
	mod = libdl_dlgethandle(address, DLGETHANDLE_FINCREF);
	if unlikely(!mod)
		goto err;
	info->dli_fname = mod->dm_filename;
	info->dli_fbase = (void *)mod->dm_loadaddr;
	info->dli_sname = NULL;
	info->dli_saddr = NULL;

	/* Support for formats other than ELF. */
	if (mod->dm_ops) {
		int result;
		if (!mod->dm_ops->df_dladdr)
			goto done;
		result = (*mod->dm_ops->df_dladdr)(mod,
		                                   (uintptr_t)address - mod->dm_loadaddr,
		                                   info);
		if (!(mod->dm_flags & RTLD_NODELETE))
			decref(mod);
		return result;
	}

	/* Search for the closest dynamic symbol. */
	if (mod->dm_elf.de_dynsym_tab) {
		ElfW(Sym) const *iter, *end;
		uintptr_t winner_distance = (uintptr_t)-1;
		iter = mod->dm_elf.de_dynsym_tab;
		end  = iter + DlModule_ElfGetDynSymCnt(mod);
		for (; iter < end; ++iter) {
			uintptr_t addr, distance;
			if (iter->st_shndx == SHN_UNDEF)
				continue;
			if (ELFW(ST_TYPE)(iter->st_info) == STT_TLS)
				continue; /* Don't include TLS symbols */
			addr = iter->st_value;
			if (iter->st_shndx != SHN_ABS)
				addr += mod->dm_loadaddr;
			if (addr >= (uintptr_t)address)
				continue;
			distance = (uintptr_t)address - addr;
			if (distance < winner_distance) {
				info->dli_saddr = (void *)addr;
				if (mod->dm_elf.de_dynstr)
					info->dli_sname = mod->dm_elf.de_dynstr + iter->st_name;
				winner_distance = distance;
			}
		}
	}
	/* XXX: set dl error? */
	return 0;
done:
	if (!(mod->dm_flags & RTLD_NODELETE))
		decref(mod);
	return 1;
err:
	return 0;
}


/* >> dlinfo(3)
 * Query auxiliary information on `handle', according to `request'
 * @param: request: One of `RTLD_DI_*'.
 * @param: arg:     Request-specific data (see docs of `RTLD_DI_*' codes).
 * @return: 0 : Success.
 * @return: -1: Error (s.a. `dlerror()') */
INTERN NONNULL((1)) int
NOTHROW_NCX(DLFCN_CC libdl_dlinfo)(NCX DlModule *self, int request,
                                   NCX void *arg) {
	if unlikely(!DL_VERIFY_MODULE_HANDLE(self))
		goto err_bad_module;
	switch (request) {

	case RTLD_DI_LINKMAP:   /* On KOS, our handles are designed to be castable to `struct link_map' */
	case RTLD_DI_TLS_MODID: /* On KOS, we simply use module pointers as TLS IDs. */
		*(void **)arg = self;
		break;

	case RTLD_DI_SERINFO:
	case RTLD_DI_SERINFOSIZE: {
		size_t pathcount, pathlen;
		char const *libpath, *iter;
		char *sbuf;
		Dl_serinfo *info = (Dl_serinfo *)arg;
		if (self->dm_ops != NULL) {
			/* TODO: Support for formats other than ELF? */
			libpath = NULL;
		} else {
			libpath = self->dm_elf.de_runpath;
		}
		if (libpath == NULL)
			libpath = dl_globals.dg_libpath;
		for (iter = libpath, pathcount = 0, pathlen = 0;;) {
			size_t partlen = stroff(iter, ':');
			pathcount += 1;
			pathlen += partlen;
			iter += partlen;
			if (!*iter)
				break;
			++iter; /* Skip ':' */
		}
		info->dls_cnt  = (unsigned int)pathcount;
		info->dls_size = offsetof(Dl_serinfo, dls_serpath) +
		                 pathcount * sizeof(Dl_serpath) +
		                 (pathlen + pathcount) * sizeof(char);
		if (request == RTLD_DI_SERINFOSIZE)
			break; /* Only supposed to fill in `dls_cnt' and `dls_size' */
		sbuf = (char *)((byte_t *)info +
		                offsetof(Dl_serinfo, dls_serpath) +
		                pathcount * sizeof(Dl_serpath));
		for (iter = libpath, pathcount = 0;; ++pathcount) {
			size_t partlen = stroff(iter, ':');
			/* Fill in pointers. */
			info->dls_serpath[pathcount].dls_name  = sbuf;
			info->dls_serpath[pathcount].dls_flags = 0; /* ??? */
			/* Copy string */
			sbuf = (char *)mempcpy(sbuf, iter, partlen, sizeof(char));
			*sbuf++ = '\0';
			iter += partlen;
			if (!*iter)
				break;
			++iter; /* Skip ':' */
		}
	}	break;

	case RTLD_DI_ORIGIN: {
		/* Copy the origin path (without a trailing '/')
		 * XXX: I think Glibc also doesn't include the '/', but I haven't checked... */
		size_t dirlen;
		dirlen = strroff(self->dm_filename, '/');
		if (dirlen != (size_t)-1)
			arg = mempcpy(arg, self->dm_filename, dirlen, sizeof(char));
		*(char *)arg = '\0';
	}	break;

	case RTLD_DI_TLS_DATA:
		*(void **)arg = DlModule_TryGetTLSAddr(self);
		break;

	case RTLD_DI_PHDR:
		if unlikely(self->dm_ops)
			goto err_notelf;
		*(ElfW(Phdr) const **)arg = self->dm_elf.de_phdr;
		return (int)(unsigned int)self->dm_elf.de_phnum;

	case RTLD_DI_CONFIGADDR: {
		Dl_info *info = (Dl_info *)arg;
		info->dli_fname = self->dm_filename;
		info->dli_fbase = (void *)self->dm_loadstart;
	}	break;

	case RTLD_DI_ARGSINFO: {
		static auxv_t const null_auxv = { 0, { 0 } };
		Dl_argsinfo_t *info = (Dl_argsinfo_t *)arg;
		info->dla_argc = (typeof(info->dla_argc))dl_globals.dg_peb->pp_argc;
		info->dla_argv = dl_globals.dg_peb->pp_argv;
		info->dla_envp = dl_globals.dg_peb->pp_envp;
		info->dla_auxv = (auxv_t *)&null_auxv;
	}	break;

	default:
		return dl_seterrorf("dlinfo: unknown request: %d", request);
	}
	return 0;
err_notelf:
	return dl_seterror_notelf(self->dm_filename);
err_bad_module:
	return dl_seterror_badmodule(self);
}


/* Return the internally used file descriptor for the given module `handle'
 * Note  however that this  descriptor is usually  only opened for reading!
 * @param: handle: A handle returned by `dlopen(3D)'.
 * @return: * : An open file descriptor for the given module `handle'
 *              WARNING: Attempting  to  close()  this  handle  may  cause  future
 *                       operations  performed with the associated module to fail!
 *                       Additionally, using dlclose() to close `handle' after the
 *                       module's fd was already  closed will attempt to  re-close
 *                       that same fd, possibly closing  some other handle if  the
 *                       same slot was re-used in the mean time.
 * @return: -1: Error (s.a. `dlerror()') */
INTERN WUNUSED NONNULL((1)) fd_t
NOTHROW_NCX(DLFCN_CC libdl_dlmodulefd)(NCX DlModule *self)
		THROWS(E_SEGFAULT) {
	if unlikely(!DL_VERIFY_MODULE_HANDLE(self))
		goto err_bad_module;
	return DlModule_GetFd(self);
err_bad_module:
	return dl_seterror_badmodule(self);
}

/* Return the internally  used filename for  the given module  `handle'
 * Note that this path is an absolute, canonical (realpath()) filename.
 * @param: handle: A handle returned by `dlopen(3D)'.
 * @return: * :    The absolute, unambiguous filename for the given module `handle'
 * @return: NULL:  Error (s.a. `dlerror()') */
INTERN WUNUSED NONNULL((1)) char const *
NOTHROW_NCX(DLFCN_CC libdl_dlmodulename)(NCX DlModule *self)
		THROWS(E_SEGFAULT) {
	if unlikely(!DL_VERIFY_MODULE_HANDLE(self))
		goto err_bad_module;
	return self->dm_filename;
err_bad_module:
	dl_seterror_badmodule(self);
	return NULL;
}

/* Return the base address offset chosen by ASLR, which is added to addresses of the given module `handle'.
 * WARNING: This function  usually returns  `NULL' for  the root  executable, in  which case  dlerror()
 *          is not  modified, meaning  that  in order  to  safely use  this  function, you  must  first
 *          call `dlerror()'  in  order  to clear  any  existing  errors, then  invoke  this  function,
 *          and call `dlerror()'  again when NULL  is returned to  check if an  error really  occurred.
 *          Or alternatively,  you  can  simply  make  sure that  `handle'  isn't  invalid,  since  the
 *          only case  when this  function  can ever  fail  is when  `handle'  was already  closed,  is
 *          `NULL', or isn't a pointer returned by `dlopen(3D)', `dlgetmodule(3D)' or `dlgethandle(3D)'
 * @param: handle: A handle returned by `dlopen(3D)'.
 * @return: * : The load address / module base for the given `handle'.
 * @return: 0 : Error (s.a. `dlerror()'), or load-address of ZERO */
INTERN WUNUSED NONNULL((1)) uintptr_t
NOTHROW_NCX(DLFCN_CC libdl_dlmodulebase)(NCX DlModule *self)
		THROWS(E_SEGFAULT) {
	if unlikely(!DL_VERIFY_MODULE_HANDLE(self))
		goto err_bad_module;
	return self->dm_loadaddr;
err_bad_module:
	dl_seterror_badmodule(self);
	return 0;
}


INTERN NONNULL((1)) void
NOTHROW_NCX(CC DlSection_Destroy)(NCX DlSection *self)
		THROWS(E_SEGFAULT) {
	DlModule *mod;

	/* Unmap section data. */
	if ((self->ds_flags & DLSECTION_FLAG_OWNED) && (self->ds_data != (void *)-1))
		(void)sys_munmap(self->ds_data, self->ds_size);

	/* Unmap decompressed section data. */
	if (self->ds_cdata != (void *)-1 && self->ds_cdata != self->ds_data)
		(void)sys_munmap(self->ds_cdata, self->ds_csize);
again:
	DlSection_ModuleWrite(self);
	mod = self->ds_module;
	if (mod) {
		if (!DlModule_SectionsTryWrite(mod)) {
			bool hasref;
			hasref = tryincref(mod);
			DlSection_ModuleEndWrite(self);
			if (hasref) {
				DlModule_SectionsWaitWrite(mod);
				decref(mod);
			}
			goto again;
		}
		assert(mod->dm_sections);
		assert(self->ds_index < mod->dm_shnum);
		assert(mod->dm_sections[self->ds_index] == self);
		mod->dm_sections[self->ds_index] = NULL;
		DlModule_SectionsEndWrite(mod);
		self->ds_module = NULL;
	}
	DlSection_ModuleEndWrite(self);
	/* Drop the reference stored in `ds_module' */
	if (mod && !(self->ds_flags & DLSECTION_FLAG_OWNED))
		decref(mod);
	free(self);
}





PRIVATE ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW_NCX(CC aux_section_ismapped_file)(NCX DlModule const *self,
                                          syscall_ulong_t file_offset,
                                          uintptr_t module_rel_addr,
                                          size_t num_bytes)
		THROWS(E_SEGFAULT) {
	ElfW(Word) i;
again:
	for (i = 0; i < self->dm_elf.de_phnum; ++i) {
		size_t num_loaded;
		uintptr_t endaddr;
		uintptr_t segment_file_offset;
		if (self->dm_elf.de_phdr[i].p_type != PT_LOAD)
			continue;
		if (module_rel_addr < self->dm_elf.de_phdr[i].p_vaddr)
			continue;
		endaddr = self->dm_elf.de_phdr[i].p_vaddr +
		          self->dm_elf.de_phdr[i].p_filesz;
		if (module_rel_addr >= endaddr)
			continue;
		segment_file_offset = self->dm_elf.de_phdr[i].p_offset;
		segment_file_offset += module_rel_addr;
		segment_file_offset -= self->dm_elf.de_phdr[i].p_vaddr;
		if (segment_file_offset != file_offset)
			continue;
		num_loaded = endaddr - module_rel_addr;
		if (num_loaded >= num_bytes)
			return true; /* All loaded! */

		/* Parts are loaded; check if the rest is, too. */
		file_offset += num_loaded;
		module_rel_addr += num_loaded;
		num_bytes -= num_loaded;
		goto again;
	}
	return false;
}

/* Search for a mapping of the given file range and
 * return  the module-relative offset  to it. If no
 * such mapping exists, return (uintptr_t)-1 */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
NOTHROW_NCX(CC find_file_mapping)(NCX DlModule const *self,
                                  syscall_ulong_t file_offset,
                                  size_t num_bytes)
		THROWS(E_SEGFAULT) {
	ElfW(Word) i;
	for (i = 0; i < self->dm_elf.de_phnum; ++i) {
		size_t num_loaded;
		uintptr_t endoffset;
		uintptr_t result;
		if (self->dm_elf.de_phdr[i].p_type != PT_LOAD)
			continue;
		if (file_offset < self->dm_elf.de_phdr[i].p_offset)
			continue;
		endoffset = self->dm_elf.de_phdr[i].p_offset +
		            self->dm_elf.de_phdr[i].p_filesz;
		if (file_offset >= endoffset)
			continue;
		result = self->dm_elf.de_phdr[i].p_vaddr;
		result += file_offset;
		result -= self->dm_elf.de_phdr[i].p_offset;
		num_loaded = endoffset - file_offset;
		if (num_loaded >= num_bytes)
			return result; /* All loaded! */
		/* Check if the rest may be loaded by other segments. */
		if (aux_section_ismapped_file(self,
		                              file_offset + num_loaded,
		                              result + num_loaded,
		                              num_bytes - num_loaded))
			return result;
	}
	return false;
}

/* Return the # of bytes consecutively mapped starting at `module_rel_addr' */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(CC sizeof_addr_mapping)(NCX DlModule const *self,
                                    uintptr_t module_rel_addr)
		THROWS(E_SEGFAULT) {
	size_t result;
	ElfW(Word) i;
	result = 0;
again:
	for (i = 0; i < self->dm_elf.de_phnum; ++i) {
		size_t num_loaded;
		uintptr_t endaddr;
		if (self->dm_elf.de_phdr[i].p_type != PT_LOAD)
			continue;
		if (module_rel_addr < self->dm_elf.de_phdr[i].p_vaddr)
			continue;
		endaddr = self->dm_elf.de_phdr[i].p_vaddr +
		          self->dm_elf.de_phdr[i].p_memsz;
		if (module_rel_addr >= endaddr)
			continue;
		num_loaded = endaddr - module_rel_addr;
		result += num_loaded;
		module_rel_addr += num_loaded;
		goto again;
	}
	return result;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW_NCX(CC aux_section_ismapped)(NCX DlModule const *self,
                                     uintptr_t module_rel_addr,
                                     size_t num_bytes)
		THROWS(E_SEGFAULT) {
	ElfW(Word) i;
again:
	for (i = 0; i < self->dm_elf.de_phnum; ++i) {
		size_t num_loaded;
		uintptr_t endaddr;
		if (self->dm_elf.de_phdr[i].p_type != PT_LOAD)
			continue;
		if (module_rel_addr < self->dm_elf.de_phdr[i].p_vaddr)
			continue;
		endaddr = self->dm_elf.de_phdr[i].p_vaddr +
		          self->dm_elf.de_phdr[i].p_memsz;
		if (module_rel_addr >= endaddr)
			continue;
		num_loaded = endaddr - module_rel_addr;
		if (num_loaded >= num_bytes)
			return true; /* All loaded! */
		/* Parts are loaded; check if the rest is, too. */
		module_rel_addr += num_loaded;
		num_bytes -= num_loaded;
		goto again;
	}
	return false;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) ElfW(Dyn) const *
NOTHROW_NCX(CC get_dynamic_tag)(NCX DlModule const *self, ElfW(Sword) tag)
		THROWS(E_SEGFAULT) {
	size_t i;
	for (i = 0; i < self->dm_elf.de_dyncnt; ++i) {
		if (self->dm_dynhdr[i].d_tag == DT_NULL)
			break;
		if (self->dm_dynhdr[i].d_tag == tag)
			return &self->dm_dynhdr[i];
	}
	return NULL;
}




/* Auxiliary section definitions
 * These are special sections that can be locked by-name, but
 * rather than reference the SHDR table, they address special
 * program headers that are detected by-type and/or flags. */
struct aux_section_def {
	char       asd_name[18];         /* Section name. */
	byte_t     asd_phdr_flags_mask;  /* Masked program header flags. */
	byte_t     asd_phdr_flags_flag;  /* Required program header flags. */
	ElfW(Word) asd_phdr_type;        /* Required program header type. */
};

/* Auxiliary section detection rules. (sort by most-useful) */
PRIVATE struct aux_section_def const aux_sections[] = {
	/* clang-format off */
	{ ".eh_frame_hdr", 0,                  0,                  PT_GNU_EH_FRAME },
	{ ".text",         PF_X | PF_W | PF_R, PF_X | PF_R,        PT_LOAD },
	{ ".rodata",       PF_X | PF_W | PF_R, PF_R,               PT_LOAD },
	{ ".data",         PF_X | PF_W | PF_R, PF_W | PF_R,        PT_LOAD },
	{ ".dynamic",      0,                  0,                  PT_DYNAMIC },
	{ ".interp",       0,                  0,                  PT_INTERP },
	{ ".tdata",        PF_X | PF_W | PF_R, PF_W | PF_R,        PT_TLS },
	{ ".note",         0,                  0,                  PT_NOTE },
	{ ".xdata",        PF_X | PF_W | PF_R, PF_X | PF_W | PF_R, PT_LOAD },
	/* clang-format on */
#define _AUX_SECTION_MIN      9
#define AUX_SECTION_ELF_EHDR  (_AUX_SECTION_MIN + 0)
#define AUX_SECTION_ELF_SHDRS (_AUX_SECTION_MIN + 1)
#define AUX_SECTION_ELF_PHDRS (_AUX_SECTION_MIN + 2)
#define AUX_SECTION_SHSTRTAB  (_AUX_SECTION_MIN + 3)
#define AUX_SECTION_HASH      (_AUX_SECTION_MIN + 4)
#define AUX_SECTION_GNU_HASH  (_AUX_SECTION_MIN + 5)
#define AUX_SECTION_DYNSYM    (_AUX_SECTION_MIN + 6)
#define AUX_SECTION_DYNSTR    (_AUX_SECTION_MIN + 7)
	[AUX_SECTION_ELF_EHDR]  = { ".elf.ehdr", 0, 0, PT_NULL },
	[AUX_SECTION_ELF_SHDRS] = { ".elf.shdrs", 0, 0, PT_NULL },
	[AUX_SECTION_ELF_PHDRS] = { ".elf.phdrs", 0, 0, PT_NULL },
	[AUX_SECTION_SHSTRTAB]  = { ".shstrtab", 0, 0, PT_NULL },
	[AUX_SECTION_HASH]      = { ".hash", 0, 0, PT_NULL },
	[AUX_SECTION_GNU_HASH]  = { ".gnu.hash", 0, 0, PT_NULL },
	[AUX_SECTION_DYNSYM]    = { ".dynsym", 0, 0, PT_NULL },
	[AUX_SECTION_DYNSTR]    = { ".dynstr", 0, 0, PT_NULL },
#define AUX_SECTION_INIT_ARRAY    (_AUX_SECTION_MIN + 8)
#define AUX_SECTION_FINI_ARRAY    (_AUX_SECTION_MIN + 9)
#define AUX_SECTION_PREINIT_ARRAY (_AUX_SECTION_MIN + 10)
	[AUX_SECTION_INIT_ARRAY]    = { ".init_array", DT_INIT_ARRAY, DT_INIT_ARRAYSZ, PT_NULL },
	[AUX_SECTION_FINI_ARRAY]    = { ".fini_array", DT_FINI_ARRAY, DT_FINI_ARRAYSZ, PT_NULL },
	[AUX_SECTION_PREINIT_ARRAY] = { ".preinit_array", DT_PREINIT_ARRAY, DT_PREINIT_ARRAYSZ, PT_NULL },
};


/* Try to create an auxiliary section. This function must initialize:
 *   - return->ds_data
 *   - return->ds_size
 *   - return->ds_entsize
 *   - return->ds_link
 *   - return->ds_info
 *   - return->ds_elfflags
 *   - return->ds_flags
 * @return: NULL:            Error (dlerror was set)
 * @return: (DlSection *)-1: The indexed section doesn't exist. */
PRIVATE WUNUSED NONNULL((1)) REF DlSection *
NOTHROW_NCX(CC create_aux_section)(NCX DlModule *self,
                                   unsigned int index,
                                   unsigned int flags)
		THROWS(E_SEGFAULT) {
	REF DlSection *result;
	ElfW(Word) phdr;
	struct aux_section_def const *rules;
	uintptr_t section_addr;
	size_t section_size;
	syscall_ulong_t section_offset;

	/* Figure out which program header to map as this section. */
	rules = &aux_sections[index];
	for (phdr = 0;; ++phdr) {
		if (phdr >= self->dm_elf.de_phnum) {
			if (rules->asd_phdr_type == PT_NULL)
				break; /* Custom rule. */
unknown_section:
			return (DlSection *)-1;
		}
		if (self->dm_elf.de_phdr[phdr].p_type != rules->asd_phdr_type)
			continue;
		if ((self->dm_elf.de_phdr[phdr].p_flags & rules->asd_phdr_flags_mask) != rules->asd_phdr_flags_flag)
			continue;
		break; /* Found it! */
	}

	if (rules->asd_phdr_type == PT_NULL) {
		/* Check if the section exists for this module. */
		switch (index) {
		case AUX_SECTION_ELF_SHDRS:
			if (self->dm_elf.de_shnum == 0)
				goto unknown_section;
			break;
		case AUX_SECTION_ELF_PHDRS:
			if (self->dm_elf.de_phnum == 0)
				goto unknown_section;
			break;
		case AUX_SECTION_SHSTRTAB:
			if (self->dm_elf.de_shstrndx >= self->dm_elf.de_shnum)
				goto unknown_section;
			break;
		case AUX_SECTION_HASH:
			if (self->dm_elf.de_hashtab == NULL)
				goto unknown_section;
			break;
		case AUX_SECTION_GNU_HASH:
			if (self->dm_elf.de_gnuhashtab == NULL)
				goto unknown_section;
			break;
		case AUX_SECTION_DYNSYM:
			if (self->dm_elf.de_dynsym_tab == NULL)
				goto unknown_section;
			break;
		case AUX_SECTION_DYNSTR:
			if (self->dm_elf.de_dynstr == NULL)
				goto unknown_section;
			break;
		case AUX_SECTION_INIT_ARRAY:
		case AUX_SECTION_FINI_ARRAY:
		case AUX_SECTION_PREINIT_ARRAY:
			if (!get_dynamic_tag(self, rules->asd_phdr_flags_mask))
				goto unknown_section;
			break;
		default: break;
		}
	}

	/* Construct the new section object. */
	result = (REF DlSection *)malloc(sizeof(DlSection));
	if unlikely(!result)
		goto err_nomem;
	result->ds_entsize  = 0;
	result->ds_link     = 0;
	result->ds_info     = 0;
	result->ds_elfflags = 0;
	result->ds_flags    = DLSECTION_FLAG_NORMAL;

	if (rules->asd_phdr_type == PT_NULL) {
		/* Figure out where this section should map to. */
		switch (index) {

		case AUX_SECTION_ELF_EHDR: /* .elf.ehdr */
			section_offset = 0;
			section_size   = sizeof(ElfW(Ehdr));
/*create_section_from_offset:*/
			section_addr   = find_file_mapping(self, section_offset, section_size);
			break;

		case AUX_SECTION_ELF_SHDRS: /* .elf.shdrs */
			result->ds_data = DlModule_ElfGetShdrs(self);
			if unlikely(!result->ds_data)
				goto err_r;
			result->ds_size = self->dm_elf.de_shnum * sizeof(ElfW(Shdr));
			return result;

		case AUX_SECTION_ELF_PHDRS: /* .elf.phdrs */
			result->ds_data = self->dm_elf.de_phdr;
			result->ds_size = self->dm_elf.de_phnum;
			return result;

		case AUX_SECTION_SHSTRTAB: /* .shstrtab */
			result->ds_data = DlModule_ElfGetShstrtab(self);
			if unlikely(!result->ds_data)
				goto err_r;
			result->ds_size = self->dm_elf.de_shdr[self->dm_elf.de_shstrndx].sh_size;
			return result;

		case AUX_SECTION_HASH: /* .hash */
			result->ds_data = (void *)self->dm_elf.de_hashtab;
create_section_from_addr:
			result->ds_size = sizeof_addr_mapping(self,
			                                      (uintptr_t)result->ds_data -
			                                      self->dm_loadaddr);
			return result;

		case AUX_SECTION_GNU_HASH: /* .gnu.hash */
			result->ds_data = (void *)self->dm_elf.de_gnuhashtab;
			goto create_section_from_addr;

		case AUX_SECTION_DYNSYM: /* .dynsym */
			result->ds_data    = (void *)self->dm_elf.de_dynsym_tab;
			result->ds_size    = sizeof(ElfW(Sym)) * DlModule_ElfGetDynSymCnt(self);
			result->ds_entsize = sizeof(ElfW(Sym));
			return result;

		case AUX_SECTION_DYNSTR: /* .dynstr */
			result->ds_data = (void *)self->dm_elf.de_dynstr;
			goto create_section_from_addr;

		case AUX_SECTION_INIT_ARRAY:
		case AUX_SECTION_FINI_ARRAY:
		case AUX_SECTION_PREINIT_ARRAY: {
			ElfW(Dyn) const *tag;
			tag = get_dynamic_tag(self, rules->asd_phdr_flags_mask);
			assert(tag); /* Already asserted above. */
			result->ds_entsize = sizeof(void (*)());
			result->ds_data    = (void *)(self->dm_loadaddr + tag->d_un.d_ptr);
			/* Check if the array is explicitly sized. */
			tag = get_dynamic_tag(self, rules->asd_phdr_flags_flag);
			if (!tag)
				goto create_section_from_addr;
			result->ds_size = tag->d_un.d_val;
			return result;
		}	break;

		default:
			__builtin_unreachable();
		}
	} else {
		if (self->dm_elf.de_phdr[phdr].p_flags & PF_W)
			result->ds_elfflags |= SHF_WRITE;
		if (self->dm_elf.de_phdr[phdr].p_flags & PF_X)
			result->ds_elfflags |= SHF_EXECINSTR;
		if (self->dm_elf.de_phdr[phdr].p_type == PT_TLS)
			result->ds_elfflags |= SHF_TLS;

		/* Figure out where this section should map to. */
		section_addr   = self->dm_elf.de_phdr[phdr].p_vaddr;
		section_size   = self->dm_elf.de_phdr[phdr].p_filesz;
		section_offset = self->dm_elf.de_phdr[phdr].p_offset;
	}

	/* Check if this section was loaded by PT_LOAD */
	result->ds_size = section_size;
	if (self->dm_elf.de_phdr[phdr].p_type == PT_LOAD ||
	    aux_section_ismapped(self, section_addr, section_size)) {
		result->ds_data = (void *)(self->dm_loadaddr + section_addr);
	} else {
		void *base;
		fd_t modfd = libdl_dlmodulefd(self);
		unsigned int prot;
		if unlikely(modfd < 0)
			goto err_r;

		/* Manually mmap() this section. */
		prot = PROT_READ;
		if (result->ds_elfflags & SHF_WRITE)
			prot |= PROT_WRITE;
		base = sys_mmap(NULL, section_size, prot,
		                MAP_PRIVATE | MAP_FILE,
		                modfd, section_offset);
		if unlikely(E_ISERR(base)) {
			errno_t error = -(errno_t)(uintptr_t)base;
			if (flags & DLLOCKSECTION_FINDEX) {
				dl_seterr_section_index_mmap_failed(self, (size_t)self->dm_elf.de_shnum + index, error);
			} else {
				dl_seterr_section_mmap_failed(self, rules->asd_name, error);
			}
			goto err_r;
		}
		result->ds_data  = base;
		result->ds_flags = DLSECTION_FLAG_OWNED;
	}
	return result;
err_r:
	free(result);
	goto err;
err_nomem:
	dl_seterror_nomem();
err:
	return NULL;
}

PRIVATE WUNUSED NONNULL((1)) void
NOTHROW(CC destroy_aux_section)(DlSection *__restrict self) {
	/* Unmap section data. */
	if ((self->ds_flags & DLSECTION_FLAG_OWNED) && (self->ds_data != (void *)-1))
		(void)sys_munmap(self->ds_data, self->ds_size);
	free(self);
}


PRIVATE ATTR_PURE WUNUSED NONNULL((1)) unsigned int
NOTHROW_NCX(CC get_aux_section_def)(NCX char const *name,
                                    unsigned int flags)
		THROWS(E_SEGFAULT) {
	unsigned int i;
	if (flags & DLLOCKSECTION_FINDEX) {
		/* Special case: section index. */
		uintptr_t index = (uintptr_t)name;
		if (index >= lengthof(aux_sections))
			return (unsigned int)-1;
		return (unsigned int)index;
	}
	for (i = 0; i < lengthof(aux_sections); ++i) {
		if (strcmp(aux_sections[i].asd_name, name) == 0)
			return i;
	}
	return (unsigned int)-1;
}

/* Returns `NULL'            on error     (w/ dlerror() set)
 * Returns `(DlSection *)-1' if not found (w/o dlerror() set) */
PRIVATE WUNUSED NONNULL((1)) REF DlSection *
NOTHROW_NCX(CC libdl_dllocksection_aux)(DlModule *__restrict self,
                                        NCX char const *name,
                                        unsigned int flags)
		THROWS(E_SEGFAULT) {
	REF DlSection *result;
	unsigned int index;
	size_t real_index;
	index = get_aux_section_def(name, flags);
	if unlikely(index == (unsigned int)-1)
		return (DlSection *)-1;

	/* Check if this section had already been loaded. */
	real_index = (size_t)self->dm_elf.de_shnum + index;
	DlModule_SectionsRead(self);
	if ((real_index < self->dm_shnum) &&
	    (result = self->dm_sections[real_index]) != NULL &&
	    DlSection_TryIncref(result)) {
		DlModule_SectionsEndRead(self);
		return result;
	}
	DlModule_SectionsEndRead(self);

	/* Must create the section from scratch (or at least try to) */
	result = create_aux_section(self, index, flags);
	if (!result || result == (REF DlSection *)-1)
		return result;

	/* Save the newly created section */
again_save_results:
	DlModule_SectionsWrite(self);
	if (real_index >= self->dm_shnum) {
		/* Must allocate a larger section vector. */
		DlSection **newvec, **oldvec;
		DlModule_SectionsEndWrite(self);
		newvec = (DlSection **)calloc(real_index + 1, sizeof(DlSection *));
		if unlikely(!newvec) {
			destroy_aux_section(result);
			dl_seterror_nomem();
			return NULL;
		}
		DlModule_SectionsWrite(self);
		if unlikely(real_index < self->dm_shnum) {
			oldvec = newvec;
		} else {
			/* Install the new vector. */
			oldvec = self->dm_sections;
			memcpy(newvec, oldvec, self->dm_shnum, sizeof(DlSection *));
			self->dm_sections = newvec;
			self->dm_shnum    = real_index + 1;
		}
		DlModule_SectionsEndWrite(self);
		/* Free the old vector. */
		free(oldvec);
		goto again_save_results;
	}
	if unlikely(self->dm_sections[real_index] != NULL &&
	            DlSection_TryIncref(self->dm_sections[real_index])) {
		REF DlSection *real_result;
		real_result = self->dm_sections[real_index];
		DlModule_SectionsEndWrite(self);
		destroy_aux_section(result);
		return real_result;
	}
	/* Fill in remaining fields and store in the sections vector. */
/*	result->ds_data     = ...; */ /* Done by `create_aux_section()' */
/*	result->ds_size     = ...; */ /* Done by `create_aux_section()' */
/*	result->ds_entsize  = ...; */ /* Done by `create_aux_section()' */
/*	result->ds_link     = ...; */ /* Done by `create_aux_section()' */
/*	result->ds_info     = ...; */ /* Done by `create_aux_section()' */
/*	result->ds_elfflags = ...; */ /* Done by `create_aux_section()' */
	result->ds_refcnt   = 1;
	atomic_rwlock_init(&result->ds_module_lock);
	result->ds_module   = self;
	if (!(result->ds_flags & DLSECTION_FLAG_OWNED))
		incref(self);
	result->ds_dangling = (REF DlSection *)-1;
/*	result->ds_flags    = ...; */ /* Done by `create_aux_section()' */
	result->ds_index    = (uintptr_half_t)real_index;
	result->ds_cdata    = (void *)-1;
	result->ds_csize    = 0;
	self->dm_sections[real_index] = result;
	DlModule_SectionsEndWrite(self);
	return result;
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1, 2)) char const *
NOTHROW(CC libdl_dlsectionname_aux)(NCX DlSection *UNUSED(self),
                                    NCX DlModule *UNUSED(mod),
                                    size_t index) {
	assert(index < lengthof(aux_sections));
	return aux_sections[index].asd_name;
}


/* Lock a named section of a given dynamic library into memory.
 * @param: handle: Handle for the library who's section `name' should be locked & loaded.
 * @param: name:   Name of the section to load into memory.
 * @return: * :    A reference to a locked section object (s.a. the exposed portion of the struct above),
 *                 and allows the user to access the contents of the section, as it is loaded in  memory.
 *                 Note however that the actual  section data is usually mapped  as read-only, or at  the
 *                 very least `MAP_PRIVATE', meaning that writes aren't written back to the library file!
 * @return: NULL:  Error (s.a. `dlerror()'; usually: unknown section) */
INTERN WUNUSED NONNULL((2)) REF DlSection *
NOTHROW_NCX(DLFCN_CC libdl_dllocksection)(NCX DlModule *self,
                                          NCX char const *name,
                                          unsigned int flags)
		THROWS(E_SEGFAULT) {
	REF DlSection *result;
	if unlikely(!DL_VERIFY_MODULE_HANDLE(self))
		goto err_bad_module;
	if unlikely(flags & ~(DLLOCKSECTION_FINDEX | DLLOCKSECTION_FNODATA))
		goto err_bad_flags;
	if (self == &dl_rtld_module) {
		/* Special case: Lookup a section within the dynamic linker itself. */
		result = flags & DLLOCKSECTION_FINDEX
		         ? dlsec_builtin_index((uintptr_t)name)
		         : dlsec_builtin(name);
		if likely(result) {
			DlSection_Incref(result);
		} else {
err_unknown_section:
			if (!(flags & DLLOCKSECTION_FINDEX)) {
				dl_seterror_nosect_index(self, (size_t)name);
			} else {
				dl_seterror_nosect(self, name);
			}
			goto err;
		}
		return result;
	}

	/* Support for formats other than ELF. */
	if unlikely(self->dm_ops) {
		size_t index;
		struct dl_sect_info info;
		if unlikely(!self->dm_ops->df_dlsectindex ||
		            !self->dm_ops->df_dlsectinfo)
			goto err_unknown_section;
		if (!(flags & DLLOCKSECTION_FINDEX)) {
			index = (*self->dm_ops->df_dlsectindex)(self, name);
			if (index >= self->dm_shnum)
				goto err_unknown_section;
		} else {
			index = (size_t)name;
		}
again_lock_sections:
		DlModule_SectionsRead(self);
		if (!self->dm_sections) {
			DlSection **sec_vec;
			size_t shnum = self->dm_shnum;
			/* Must allocate the initial sections vector. */
			DlModule_SectionsEndRead(self);
			sec_vec = (DlSection **)calloc(shnum, sizeof(DlSection *));
			if unlikely(!sec_vec)
				goto err_nomem;
			DlModule_SectionsWrite(self);
			COMPILER_READ_BARRIER();
			if likely(!self->dm_sections && self->dm_shnum == shnum) {
				self->dm_sections = sec_vec;
			} else {
				DlModule_SectionsEndWrite(self);
				free(sec_vec);
				COMPILER_READ_BARRIER();
				goto again_lock_sections;
			}
			DlModule_SectionsDowngrade(self);
		}
again_read_section:
		result = self->dm_sections[index];
		if (!result || !DlSection_TryIncref(result)) {
			int error;
			/* Must allocate a descriptor for this section. */
			DlModule_SectionsEndRead(self);
			result = (REF DlSection *)malloc(sizeof(DlSection));
			if unlikely(!result)
				goto err_nomem;
			error = (*self->dm_ops->df_dlsectinfo)(self, index, &info);
			if unlikely(error != 0) {
				free(result);
				goto err;
			}

			result->ds_size     = info.dsi_size;
			result->ds_entsize  = info.dsi_entsize;
			result->ds_link     = info.dsi_link;
			result->ds_info     = info.dsi_info;
			result->ds_elfflags = info.dsi_elfflags;
			result->ds_refcnt   = 1;
			result->ds_module   = self;
			result->ds_index    = index;
			result->ds_dangling = (REF DlSection *)-1;
			result->ds_cdata    = (void *)-1;
			atomic_rwlock_init(&result->ds_module_lock);
			if (info.dsi_addr) {
				/* Section is already loaded in memory. */
				result->ds_data  = info.dsi_addr;
				result->ds_flags = DLSECTION_FLAG_NORMAL;
				incref(self); /* Reference stored in `result->ds_module' */
			} else {
				result->ds_data  = (void *)-1;
				result->ds_flags = DLSECTION_FLAG_OWNED;
			}
			DlModule_SectionsWrite(self);
			if likely(!self->dm_sections[index]) {
				self->dm_sections[index] = result;
			} else {
				/* Race condition: The section was already allocated in a different thread. */
				DlModule_SectionsEndWrite(self);
				free(result);
				DlModule_SectionsRead(self);
				goto again_read_section;
			}
			DlModule_SectionsDowngrade(self);
		} else {
			info.dsi_size = 0;
		}
		DlModule_SectionsEndRead(self);
		if (result->ds_data == (void *)-1 && !(flags & DLLOCKSECTION_FNODATA) &&
		    (result->ds_flags & DLSECTION_FLAG_OWNED)) {
			unsigned int prot;
			void *base;
			if (info.dsi_size == 0) {
				int error;
				error = (*self->dm_ops->df_dlsectinfo)(self, index, &info);
				if unlikely(error != 0)
					goto err;
			}

			/* Must load section data. */
			prot = PROT_READ;
			if (result->ds_elfflags & SHF_WRITE)
				prot |= PROT_WRITE;
			base = sys_mmap(NULL, info.dsi_size, prot,
			                MAP_PRIVATE | MAP_FILE,
			                self->dm_file, info.dsi_offset);
			if (E_ISERR(base)) {
				errno_t error = -(errno_t)(uintptr_t)base;
				DlSection_Decref(result);
				if (flags & DLLOCKSECTION_FINDEX) {
					dl_seterr_section_index_mmap_failed(self, (size_t)(uintptr_t)name, error);
				} else {
					dl_seterr_section_mmap_failed(self, name, error);
				}
				goto err;
			}
			if unlikely(!atomic_cmpxch(&result->ds_data, (void *)-1, base))
				(void)sys_munmap(base, info.dsi_size);
		}
	} else {
		size_t index;
		ElfW(Shdr) *sect;
		if (flags & DLLOCKSECTION_FINDEX) {
			sect = DlModule_ElfGetShdrs(self);
			if unlikely(!sect)
				goto err;
			if ((uintptr_t)name >= self->dm_elf.de_shnum) {
				/* Check for auxiliary sections. */
				result = libdl_dllocksection_aux(self,
				                                 (char const *)((uintptr_t)name -
				                                                self->dm_elf.de_shnum),
				                                 flags);
				if (result == (REF DlSection *)-1) {
					dl_seterror_nosect_index(self, (size_t)name);
					goto err;
				}
				return result;
			}
			sect += (uintptr_t)name;
		} else {
			sect = DlModule_ElfGetSection(self, name);
			if unlikely(!sect)
				goto err;
			if (sect == (ElfW(Shdr) *)-1) {
				/* Check for auxiliary sections. */
				result = libdl_dllocksection_aux(self, name, flags);
				if (result == (REF DlSection *)-1) {
					dl_seterror_nosect(self, name);
					goto err;
				}
				return result;
			}
		}
		assert(self->dm_elf.de_shnum != (ElfW(Half))-1);
		assert(sect >= self->dm_elf.de_shdr);
		assert(sect < self->dm_elf.de_shdr + self->dm_elf.de_shnum);
		index = (size_t)(sect - self->dm_elf.de_shdr);
again_lock_elf_sections:
		DlModule_SectionsRead(self);
		if (!self->dm_sections || self->dm_elf.de_shnum > self->dm_shnum) {
			DlSection **sec_vec;
			/* Must allocate the initial sections vector. */
			DlModule_SectionsEndRead(self);
			sec_vec = (DlSection **)calloc(self->dm_elf.de_shnum,
			                               sizeof(DlSection *));
			if unlikely(!sec_vec)
				goto err_nomem;
			DlModule_SectionsWrite(self);
			COMPILER_READ_BARRIER();
			if likely(!self->dm_sections) {
				self->dm_sections = sec_vec;
				self->dm_shnum    = self->dm_elf.de_shnum;
			} else if (self->dm_elf.de_shnum > self->dm_shnum) {
				DlSection **old_vec = self->dm_sections;
				memcpy(sec_vec, old_vec, self->dm_shnum, sizeof(DlSection *));
				self->dm_sections = sec_vec;
				self->dm_shnum    = self->dm_elf.de_shnum;
				DlModule_SectionsEndWrite(self);
				free(old_vec);
				goto again_lock_elf_sections;
			} else {
				DlModule_SectionsEndWrite(self);
				free(sec_vec);
				goto again_lock_elf_sections;
			}
			DlModule_SectionsDowngrade(self);
		}
again_read_elf_section:
		result = self->dm_sections[index];
		if (!result || !DlSection_TryIncref(result)) {
			/* Must allocate a descriptor for this section. */
			DlModule_SectionsEndRead(self);
			result = (REF DlSection *)malloc(sizeof(DlSection));
			if unlikely(!result)
				goto err_nomem;
			result->ds_size     = sect->sh_size;
			result->ds_entsize  = sect->sh_entsize;
			result->ds_link     = sect->sh_link;
			result->ds_info     = sect->sh_info;
			result->ds_elfflags = sect->sh_flags;
			result->ds_refcnt   = 1;
			result->ds_module   = self;
			result->ds_index    = index;
			result->ds_dangling = (REF DlSection *)-1;
			result->ds_cdata    = (void *)-1;
			atomic_rwlock_init(&result->ds_module_lock);
			if (sect->sh_flags & SHF_ALLOC) {
				/* Section is already loaded in memory. */
				result->ds_data  = (void *)(self->dm_loadaddr + sect->sh_addr);
				result->ds_flags = DLSECTION_FLAG_NORMAL;
				incref(self); /* Reference stored in `result->ds_module' */
			} else {
				result->ds_data  = (void *)-1;
				result->ds_flags = DLSECTION_FLAG_OWNED;
			}
			DlModule_SectionsWrite(self);
			if likely(!self->dm_sections[index]) {
				self->dm_sections[index] = result;
			} else {
				/* Race condition: The section was already allocated in a different thread. */
				DlModule_SectionsEndWrite(self);
				free(result);
				DlModule_SectionsRead(self);
				goto again_read_elf_section;
			}
			DlModule_SectionsDowngrade(self);
		}
		DlModule_SectionsEndRead(self);
		if (result->ds_data == (void *)-1 && !(flags & DLLOCKSECTION_FNODATA) &&
		    (result->ds_flags & DLSECTION_FLAG_OWNED)) {
			unsigned int prot;
			void *base;
			/* Must load section data. */
			prot = PROT_READ;
			if (result->ds_elfflags & SHF_WRITE)
				prot |= PROT_WRITE;
			base = sys_mmap(NULL, sect->sh_size, prot,
			                MAP_PRIVATE | MAP_FILE,
			                self->dm_file, sect->sh_offset);
			if (E_ISERR(base)) {
				errno_t error = -(errno_t)(uintptr_t)base;
				DlSection_Decref(result);
				if (flags & DLLOCKSECTION_FINDEX) {
					dl_seterr_section_index_mmap_failed(self, (size_t)(uintptr_t)name, error);
				} else {
					dl_seterr_section_mmap_failed(self, name, error);
				}
				goto err;
			}
			if unlikely(!atomic_cmpxch(&result->ds_data, (void *)-1, base))
				(void)sys_munmap(base, sect->sh_size);
		}
	}
	return result;
err_nomem:
	dl_seterror_nomem();
err:
	return NULL;
err_bad_module:
	dl_seterror_badmodule(self);
	goto err;
err_bad_flags:
	dl_seterrorf("Invalid flags %#x passed to `dllocksection(3D)'", flags);
	goto err;
}


/* Unlock a locked section, as previously returned by `dllocksection(3D)'
 * HINT: Think of this function as a decref(), where `dllocksection(3D)'
 *       returns a reference you inherit as the caller
 * @return: 0 : Successfully unlocked the given section `sect'
 * @return: * : Error (s.a. `dlerror()') */
INTERN NONNULL((1)) int
NOTHROW_NCX(DLFCN_CC libdl_dlunlocksection)(NCX REF DlSection *sect)
		THROWS(E_SEGFAULT) {
	if unlikely(!DL_VERIFY_SECTION_HANDLE(sect))
		goto err_bad_section;
	{
		refcnt_t refcnt;
		do {
			refcnt = atomic_read(&sect->ds_refcnt);
			assert(refcnt != 0);
			if (refcnt == 1)
				goto set_dangling_section;
		} while (!atomic_cmpxch_weak(&sect->ds_refcnt, refcnt, refcnt - 1));
		return 0;
	}
	{
		REF DlModule *mod;
set_dangling_section:
		DlSection_ModuleRead(sect);
		mod = sect->ds_module;
		if (mod && !tryincref(mod))
			mod = NULL;
		DlSection_ModuleEndRead(sect);
		if (mod) {
			DlModule_SectionsWrite(mod);
			/* Insert the section into the set of dangling sections of this module. */
			if likely(sect->ds_dangling == (REF DlSection *)-1) {
				sect->ds_dangling         = mod->dm_sections_dangling;
				mod->dm_sections_dangling = sect;
				DlModule_SectionsEndWrite(mod);
				decref(mod);
				return 0;
			}
			DlModule_SectionsEndWrite(mod);
			decref(mod);
		}
	}
	DlSection_Decref(sect);
	return 0;
err_bad_section:
	return dl_seterror_badsection(sect);
}

/* Return the name of a given section, or NULL on error
 * WARNING: The name of a section can no longer be queried after the associated
 *          module  has been unloaded! If this has happened, `NULL' is returned
 *          and dlerror() is set accordingly.
 *          Because the names  of sections  are stored  alongside the  module, if  you
 *          can't guaranty that  the module  associated with the  section doesn't  get
 *          unloaded while you're accessing the section's name, you must first acquire
 *          your own reference  to that module  through use of  `dlsectionmodule(3D)':
 *          >> void *mod = dlsectionmodule(my_sect, DLGETHANDLE_FINCREF);
 *          >> char const *name = dlsectionname(my_sect);
 *          >> // Make use of `name' (also check if `name' is NULL; if it is, `mod'
 *          >> // will probably also be NULL if the module had already been unloaded)
 *          >> ...
 *          >> dlclose(mod); */
INTERN WUNUSED NONNULL((1)) char const *
NOTHROW_NCX(DLFCN_CC libdl_dlsectionname)(NCX DlSection *sect)
		THROWS(E_SEGFAULT) {
	char const *result;
	REF DlModule *mod;
	if unlikely(!DL_VERIFY_SECTION_HANDLE(sect))
		goto err_bad_section;
	DlSection_ModuleRead(sect);
	mod = sect->ds_module;
	if (!mod || !tryincref(mod)) {
		DlSection_ModuleEndRead(sect);
err_mod_unloaded:
		dl_seterrorf("Module associated with section was unloaded");
		goto err;
	}
	DlSection_ModuleEndRead(sect);
	if (mod == &dl_rtld_module) {
		/* Special case: the RTLD driver module. */
		assert(sect->ds_index < BUILTIN_SECTIONS_COUNT);
		result = dlsec_builtin_name(sect->ds_index);
		assert(result != NULL);
	} else {
		/* Regular module. */
		assert(sect->ds_index < mod->dm_shnum);
		/* Support for formats other than ELF. */
		if (mod->dm_ops) {
			if unlikely(!mod->dm_ops->df_dlsectname) {
				result = "?";
			} else {
				result = (*mod->dm_ops->df_dlsectname)(mod, sect->ds_index);
			}
		} else {
			assert(mod->dm_elf.de_shnum != (ElfW(Half)) - 1);
			if (sect->ds_index < mod->dm_elf.de_shnum) {
				assert(mod->dm_elf.de_shdr != NULL);
				assert(mod->dm_elf.de_shstrtab != NULL);
				result = mod->dm_elf.de_shstrtab;
				result += mod->dm_elf.de_shdr[sect->ds_index].sh_name;
			} else {
				result = libdl_dlsectionname_aux(sect, mod,
				                                 sect->ds_index -
				                                 mod->dm_elf.de_shnum);
			}
		}
	}
	if unlikely(atomic_decfetch(&mod->dm_refcnt) == 0) {
		destroy(mod);
		goto err_mod_unloaded;
	}
	return result;
err_bad_section:
	dl_seterror_badsection(sect);
err:
	return NULL;
}

/* Returns  the index of a given section, or `(size_t)-1' on error. */
INTERN WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(DLFCN_CC libdl_dlsectionindex)(NCX DlSection *sect)
		THROWS(E_SEGFAULT) {
	size_t result;
	if unlikely(!DL_VERIFY_SECTION_HANDLE(sect))
		goto err_bad_section;
	result = sect->ds_index;
	return result;
err_bad_section:
	dl_seterror_badsection(sect);
	return (size_t)-1;
}


/* Return the module associated with a given section, or `NULL' on error.
 * @param: flags: Set of `DLGETHANDLE_F*'
 * @return: * :   A pointer, or reference to the module handle (when `DLGETHANDLE_FINCREF' was given)
 * @return: NULL: Error (s.a. `dlerror()'; usually, the module was already unloaded) */
INTERN WUNUSED NONNULL((1)) DlModule *
NOTHROW_NCX(DLFCN_CC libdl_dlsectionmodule)(NCX DlSection *sect, unsigned int flags)
		THROWS(E_SEGFAULT) {
	DlModule *mod;
	if unlikely(!DL_VERIFY_SECTION_HANDLE(sect))
		goto err_bad_section;
	if unlikely(flags & ~(DLGETHANDLE_FINCREF)) {
		dl_seterrorf("Invalid flags %#x passed to `dlsectionmodule(3D)'", flags);
		goto err;
	}
	DlSection_ModuleRead(sect);
	mod = sect->ds_module;
	if (!mod || ((flags & DLGETHANDLE_FINCREF)
	             ? !tryincref(mod)
	             : !atomic_read(&mod->dm_refcnt))) {
		DlSection_ModuleEndRead(sect);
		dl_seterrorf("Module associated with section was unloaded");
		goto err;
	}
	DlSection_ModuleEndRead(sect);
	return mod;
err_bad_section:
	dl_seterror_badsection(sect);
err:
	return NULL;
}






/* Lazlily linked function pointers from libzlib.so */
PRIVATE PZLIB_READER_INIT pdyn_zlib_reader_init = NULL;
PRIVATE PZLIB_READER_READ pdyn_zlib_reader_read = NULL;
PRIVATE PZLIB_READER_FINI pdyn_zlib_reader_fini = NULL;
#define zlib_reader_init (*pdyn_zlib_reader_init)
#define zlib_reader_read (*pdyn_zlib_reader_read)
#define zlib_reader_fini (*pdyn_zlib_reader_fini)


PRIVATE WUNUSED bool NOTHROW(CC init_zlib)(void) {
	if (!pdyn_zlib_reader_init) {
		REF DlModule *libzlib;
		libzlib = libdl_dlopen(LIBZLIB_LIBRARY_NAME, RTLD_LOCAL);
		if unlikely(!libzlib)
			goto err;
		if ((*(void **)&pdyn_zlib_reader_fini = libdl_dlsym(libzlib, "zlib_reader_fini")) == NULL)
			goto err;
		if ((*(void **)&pdyn_zlib_reader_read = libdl_dlsym(libzlib, "zlib_reader_read")) == NULL)
			goto err;
		COMPILER_BARRIER();
		if ((*(void **)&pdyn_zlib_reader_init = libdl_dlsym(libzlib, "zlib_reader_init")) == NULL)
			goto err;
		COMPILER_BARRIER();
	}
	return true;
err:
	return false;
}

/* Decompress section data.
 * @return: * : One of `ZLIB_ERROR_*' */
PRIVATE ATTR_NOINLINE int
NOTHROW(CC decompress_section_data)(void *dst, size_t dst_size,
                                    void const *src, size_t src_size) {
	ssize_t error;
	struct zlib_reader reader;
	zlib_reader_init(&reader, src, src_size);
	error = zlib_reader_read(&reader, dst, dst_size);
#if 0 /* Can't be enabled at the moment */
	if (error >= 0 && !zlib_reader_eof(&reader))
		error = ZLIB_ERROR_BAD_LENGTH; /* More data exists after the stream... */
#endif
	zlib_reader_fini(&reader);
	if unlikely(error < 0)
		return (int)error; /* Inflate error. */
	/* clear all trailing data that could not be read. */
	if ((size_t)error < dst_size)
		bzero((byte_t *)dst + (size_t)error, dst_size - error);
	return ZLIB_ERROR_OK;
}


PRIVATE WUNUSED NONNULL((1, 2, 4)) void *
NOTHROW_NCX(CC inflate_compressed_section)(NCX DlSection *sect,
                                           void const *section_data,
                                           size_t section_size,
                                           size_t *__restrict psection_csize)
		THROWS(E_SEGFAULT) {
	ElfW(Chdr) *chdr;
	void *result;
	chdr = (ElfW(Chdr) *)section_data;

	/* Verify the compressed-section header. */
	if unlikely(section_size < sizeof(*chdr))
		goto err_bad_section_size;
	if unlikely(chdr->ch_type != ELFCOMPRESS_ZLIB)
		goto err_wrong_chdr_type;

	/* Allocate memory for the compressed section. */
	*psection_csize = atomic_read(&chdr->ch_size);
	result = sys_mmap(NULL, *psection_csize,
	                  PROT_READ | PROT_WRITE,
	                  MAP_PRIVATE | MAP_ANON,
	                  -1, 0);
	if unlikely(E_ISERR(result))
		goto err_mmap_failed;

	/* Lazily load libzlib.so */
	if unlikely(!init_zlib())
		goto err_munmap;

	/* Decompress section data. */
	{
		unsigned int inflate_error;
		inflate_error = decompress_section_data(result, *psection_csize, chdr + 1,
		                                        section_size - sizeof(*chdr));
		if unlikely(inflate_error != ZLIB_ERROR_OK) {
			/* Inflate error. */
			dl_seterrorf("Failed to inflate compressed section %s:%s (error: %u)",
			             libdl_dlmodulename(libdl_dlsectionmodule(sect, 0)),
			             libdl_dlsectionname(sect), inflate_error);
			goto err_munmap;
		}
	}

	/* Success! */
	return result;
err_mmap_failed:
	dl_seterrorf("%q: Failed to allocate decompressed buffer for compressed section %q",
	             libdl_dlmodulename(libdl_dlsectionmodule(sect, 0)),
	             libdl_dlsectionname(sect));
	goto err;
err_wrong_chdr_type:
	dl_seterrorf("%q: Compressed section %q uses an unknown compression scheme %u",
	             libdl_dlmodulename(libdl_dlsectionmodule(sect, 0)),
	             libdl_dlsectionname(sect),
	             (unsigned int)chdr->ch_type);
	goto err;
err_bad_section_size:
	dl_seterrorf("%q: Compressed section %q is too small to be compressed",
	             libdl_dlmodulename(libdl_dlsectionmodule(sect, 0)),
	             libdl_dlsectionname(sect));
	goto err;
err_munmap:
	(void)sys_munmap(result, *psection_csize);
err:
	return (void *)-1;
}


/* Try to inflate compressed  module sections (`SHF_COMPRESSED'), returning  a
 * pointer  to a decompressed  data blob that is  lazily allocated for `sect',
 * and will be freed once the section ends up being unloaded. The given `sect'
 * may  not be loaded  with `DLLOCKSECTION_FNODATA' if  this function shall be
 * used  later; if the (compressed) data used  for backing `sect' has not been
 * loaded, this function will fail.
 * When the given `sect' isn't actually compressed, this function will simply
 * return  a pointer to `sect->ds_data', and fill `*psize' (if non-NULL) with
 * `ds_size'. Otherwise, inflated data and its size are returned.
 * NOTE: This function requires libdl to lazily load the KOS system library
 *       `libzlib.so', as found apart of  the KOS source tree. Should  that
 *       library not be loaded already,  or should loading of said  library
 *       fail for any reason, this function will also fail, and `dlerror()'
 *       will reflect what went wrong when trying to load said library.
 * NOTE: The backing memory for the deflated data blob is allocated lazily and
 *       will not be freed before `sect' is `dlunlocksection(3D)'ed the same #
 *       of times that it was `dllocksection(3D)'ed.
 * @param: psize: When non-NULL, store the size of the inflated (decompressed)
 *                data blob that is returned.
 * @return: * :   A pointer to the inflated data that is backing `sect'. When
 *                `sect'  isn't compressed, this  function will simply return
 *                the section's normal data blob, that is `sect->ds_data'
 * @return: NULL: Error (s.a. `dlerror()') */
INTERN WUNUSED NONNULL((1)) void *
NOTHROW_NCX(DLFCN_CC libdl_dlinflatesection)(NCX DlSection *sect,
                                             NCX size_t *psize)
		THROWS(E_SEGFAULT) {
	if unlikely(!DL_VERIFY_SECTION_HANDLE(sect))
		goto err_bad_section;

	/* Check for simple case: Was inflated data already loaded? */
	if (sect->ds_cdata == (void *)-1) {
		/* Verify that section data has been loaded. */
		if unlikely(sect->ds_data == (void *)-1)
			goto err_no_section_data;

		/* Check for simple case: The section isn't actually compressed. */
		if (!(sect->ds_elfflags & SHF_COMPRESSED)) {
			sect->ds_csize = sect->ds_size;
			COMPILER_WRITE_BARRIER();
			sect->ds_cdata = sect->ds_data;
			COMPILER_WRITE_BARRIER();
		} else {
			/* Must actually inflate data. */
			void *cdata;
			size_t csize;
			cdata = inflate_compressed_section(sect,
			                                   sect->ds_data,
			                                   sect->ds_size,
			                                   &csize);
			if unlikely(cdata == (void *)-1)
				goto err;
			/* Save the results. */
			atomic_store(&sect->ds_csize, csize); /* This must be written first! */
			if unlikely(!atomic_cmpxch(&sect->ds_cdata, (void *)-1, cdata)) {
				/* Race condition: Some  other thread also  did the  inflate,
				 * and now we've got the inflated  data twice. - Fix this  by
				 * simply deleting our duplicate and using the version that's
				 * already stored in the section descriptor. */
				(void)sys_munmap(cdata, csize);
			}
		}
	}
	if (psize)
		*psize = sect->ds_csize;
	return sect->ds_cdata;
err_no_section_data:
	dl_seterrorf("%q: Section data not loaded for %q",
	             libdl_dlmodulename(libdl_dlsectionmodule(sect, 0)),
	             libdl_dlsectionname(sect));
	goto err;
err_bad_section:
	dl_seterror_badsection(sect);
err:
	if (psize)
		*psize = 0;
	return NULL;
}


PRIVATE NONNULL((1)) int CC
DlModule_InvokeDlCacheFunctions(DlModule *__restrict self)
		THROWS(...) {
	int result = 0;
	DlSection *sect;
	sect = libdl_dllocksection(self, ".dl_caches", DLLOCKSECTION_FNORMAL);
	if unlikely(!sect)
		goto done;
	if likely(!(sect->ds_size & (sizeof(void *) - 1))) {
		size_t i;
		typedef int (*cache_func_t)(void);
		for (i = 0; i < sect->ds_size; i += sizeof(void *)) {
			byte_t *ptraddr   = (byte_t *)sect->ds_data + i;
			cache_func_t func = (cache_func_t)(void *)(ptraddr + *(uintptr_t *)ptraddr);
			if ((*func)())
				result = 1;
		}
	}
	DlSection_Decref(sect);
done:
	return result;
}


/* Clear internal caches used by loaded modules in order to free  up
 * available memory. This function  is automatically called by  libc
 * when `mmap(2)' fails due to lack of available virtual or physical
 * memory. For more information, see `DL_REGISTER_CACHE(3D)'
 * @return: 0: No optional memory could be released.
 * @return: 1: Some optional memory was released. */
INTERN int DLFCN_CC libdl_dlclearcaches(void) THROWS(...) {
	int result = 0;
	/* TODO: Guard against recursive calls:
	 *  - Within the same thread:
	 *    - Immediately return `0'
	 *  - From another thread:
	 *    - Wait for  the first  thread to  finish, then  mirror
	 *      its return value and don't re-execute this function.
	 */

	/* Try to execute function pointers from `.dl_caches' sections. */
	{
		DlModule *module_iter;
again_clear_modules:
		dlglobals_all_read(&dl_globals);
		DLIST_FOREACH (module_iter, &dl_globals.dg_alllist, dm_modules) {
			refcnt_t refcnt;
			if (!tryincref(module_iter))
				continue;
			dlglobals_all_endread(&dl_globals);
			if (DlModule_InvokeDlCacheFunctions(module_iter))
				result = 1;
again_try_descref_module_iter:
			refcnt = atomic_read(&module_iter->dm_refcnt);
			if (refcnt <= 1) {
				decref(module_iter);
				goto again_clear_modules;
			}
			dlglobals_all_read(&dl_globals);
			if (!atomic_cmpxch_weak(&module_iter->dm_refcnt, refcnt, refcnt - 1)) {
				dlglobals_all_endread(&dl_globals);
				goto again_try_descref_module_iter;
			}
		}
		dlglobals_all_endread(&dl_globals);
	}
	{
		DlModule *module_iter;
		/* Delete dangling sections. */
again_lock_global:
		dlglobals_all_read(&dl_globals);
		DLIST_FOREACH (module_iter, &dl_globals.dg_alllist, dm_modules) {
			REF DlSection *temp;
			if (!atomic_read(&module_iter->dm_sections_dangling))
				continue;
			if (!DlModule_SectionsTryWrite(module_iter)) {
				bool hasref;
				hasref = tryincref(module_iter);
				dlglobals_all_endread(&dl_globals);
				if (hasref) {
					DlModule_SectionsWaitWrite(module_iter);
					decref(module_iter);
				}
				goto again_lock_global;
			}
			COMPILER_READ_BARRIER();
			temp = module_iter->dm_sections_dangling;
			if likely(temp) {
				/* Steal a reference to this section. */
				module_iter->dm_sections_dangling = temp->ds_dangling;
				temp->ds_dangling                 = (REF DlSection *)-1;
				DlModule_SectionsEndWrite(module_iter);
				dlglobals_all_endread(&dl_globals);
				/* Drop this reference. */
				DlSection_Decref(temp);
				result = 1;
				goto again_lock_global;
			}
			DlModule_SectionsEndWrite(module_iter);
		}
		dlglobals_all_endread(&dl_globals);
	}

	/* Also trim malloc memory from our heap implementation. */
	if (malloc_trim(0))
		result = 1;
	return result;
}


PRIVATE void CC
DlModule_RunAllModuleFinalizers(void)
		THROWS(...) {
	DlModule *mod;
again:
	dlglobals_all_read(&dl_globals);
	DLIST_FOREACH (mod, &dl_globals.dg_alllist, dm_modules) {
		/* Skip finalizers  if the  module was  never
		 * initialized or has already been finalized. */
		if (atomic_fetchor(&mod->dm_flags, (RTLD_NOINIT /*| RTLD_NODELETE*/)) & RTLD_NOINIT)
			continue;
		if unlikely(!tryincref(mod))
			continue;
		dlglobals_all_endread(&dl_globals);

		TRY {
			/* Invoke dynamically registered module finalizers (s.a. `__cxa_atexit()') */
			if (mod->dm_finalize)
				dlmodule_finalizers_run(mod->dm_finalize);
			if (mod->dm_ops) {
				if (mod->dm_ops->df_run_finalizers)
					(*mod->dm_ops->df_run_finalizers)(mod);
			} else {
				size_t i, fini_array_size;
				uintptr_t fini_func;
				uintptr_t *fini_array_base;
				fini_func       = 0;
				fini_array_base = NULL;
				fini_array_size = 0;
				for (i = 0; i < mod->dm_elf.de_dyncnt; ++i) {
					switch (mod->dm_dynhdr[i].d_tag) {

					case DT_NULL:
						goto done_dyntag;

					case DT_FINI:
						fini_func = (uintptr_t)mod->dm_dynhdr[i].d_un.d_ptr;
						break;

					case DT_FINI_ARRAY:
						fini_array_base = (uintptr_t *)(mod->dm_loadaddr +
						                                mod->dm_dynhdr[i].d_un.d_ptr);
						break;

					case DT_FINI_ARRAYSZ:
						fini_array_size = (size_t)mod->dm_dynhdr[i].d_un.d_val / sizeof(void (*)(void));
						break;

					default: break;
					}
				}
done_dyntag:
				/* Service fini-array functions in reverse order. */
				while (fini_array_size--)
					(*(void (*)(void))(fini_array_base[fini_array_size] /* + self->dm_loadaddr*/))();

				/* Service a fini function, if one was specified. */
				if (fini_func)
					(*(void (*)(void))(fini_func + mod->dm_loadaddr))();
			}
		} EXCEPT {
			decref(mod);
			RETHROW();
		}
		decref(mod);
		goto again;
	}
	dlglobals_all_endread(&dl_globals);
}


/* Return a pointer to the main thread's  TLS segment. The caller must ensure  that
 * this segment has not, and will not be deleted. Otherwise, behavior is undefined. */
PRIVATE ATTR_PURE ATTR_RETNONNULL WUNUSED void *CC
libdl_dlmainsegment(void) {
	struct dltls_segment *result;
	dlglobals_tls_segment_read(&dl_globals);
	result = LIST_FIRST(&dl_globals.dg_tls_segment_list);
	while (LIST_NEXT(result, ts_threads) != NULL)
		result = LIST_NEXT(result, ts_threads);
	dlglobals_tls_segment_endread(&dl_globals);
	return result;
}

/* Return the # of allocated TLS segments. */
PRIVATE ATTR_PURE WUNUSED size_t CC libdl_dltlssegcount(void) {
	size_t result;
	dlglobals_tls_segment_read(&dl_globals);
	result = LIST_COUNT(&dl_globals.dg_tls_segment_list, ts_threads);
	dlglobals_tls_segment_endread(&dl_globals);
	return result;
}

/* Return the # of allocated TLS segments. */
PRIVATE ATTR_PURE WUNUSED bool CC
libdl_dltlssegvalid(struct dltls_segment *seg) {
	bool result = false;
	if likely(seg) {
		struct dltls_segment *iter;
		dlglobals_tls_segment_read(&dl_globals);
		LIST_FOREACH (iter, &dl_globals.dg_tls_segment_list, ts_threads) {
			if (iter == seg) {
				result = true;
				break;
			}
		}
		dlglobals_tls_segment_endread(&dl_globals);
	}
	return result;
}



/* Perform an auxiliary control command about a given module `handle'
 * This function is used internally, and invocation requirements for different values
 * for `cmd' may change in the future. - It's purpose is to provide access to binary-
 * specific information about loaded modules.
 * @param: handle:   Handle of the module for which to query information,
 *                   or  NULL  to   query  for   the  root   application.
 *                   Some commands  may not  make use  of this  argument.
 * @param: cmd:      The command with which information should be requested.
 * @return: NULL: No information available, or no buffer was provided (depending on `cmd')
 * @return: NULL: Error: Unknown `cmd' (s.a. dlerror())
 * @return: NULL: Error: Invalid `handle' (s.a. dlerror()) */
INTERN void *DLFCN_CC
libdl_dlauxctrl(NCX DlModule *self, unsigned int cmd, ...)
		THROWS(E_SEGFAULT, ...) {
	void *result;
	va_list args;
	va_start(args, cmd);
	switch (cmd) {

	case DLAUXCTRL_RUNFINI:
		DlModule_RunAllModuleFinalizers();
		goto err;

	case DLAUXCTRL_RUNTLSFINI:
		DlModule_RunAllTlsFinalizers();
		goto err;

	case DLAUXCTRL_GET_MAIN_TLSSEG:
		va_end(args);
		return libdl_dlmainsegment();

	case DLAUXCTRL_GET_TLSSEG_COUNT:
		va_end(args);
		return (void *)(uintptr_t)libdl_dltlssegcount();

	case DLAUXCTRL_GET_TLSSEG_VALID: {
		bool isvalid;
		struct dltls_segment *seg;
		seg = va_arg(args, struct dltls_segment *);
		va_end(args);
		isvalid = libdl_dltlssegvalid(seg);
		return (void *)(uintptr_t)(isvalid ? 1 : 0);
	}	break;

	case DLAUXCTRL_FOREACH_TLSSEG: {
		struct dltls_segment *iter;
		typedef void *(__DLFCN_CC *ptlsenum_cb_t)(void *cookie, void *tls_segment);
		ptlsenum_cb_t cb = va_arg(args, ptlsenum_cb_t);
		void *cookie = va_arg(args, void *);
		va_end(args);
		result = NULL;
		dlglobals_tls_segment_read(&dl_globals);
		LIST_FOREACH (iter, &dl_globals.dg_tls_segment_list, ts_threads) {
			result = (*cb)(cookie, iter);
			if (result != NULL)
				break;
		}
		dlglobals_tls_segment_endread(&dl_globals);
		return result;
	}	break;

	default:
		break;
	}
	if (!self) {
		self = dlglobals_mainapp(&dl_globals);
		assert(self);
	} else if unlikely(!DL_VERIFY_MODULE_HANDLE(self)) {
		dl_seterror_badmodule(self);
		goto err;
	}
	switch (cmd) {

	case DLAUXCTRL_MOD_INCREF:
		incref(self);
		result = self;
		break;

	case DLAUXCTRL_MOD_DECREF:
		decref(self);
		result = self;
		break;

	case DLAUXCTRL_MOD_WEAKINCREF:
		weakincref(self);
		result = self;
		break;

	case DLAUXCTRL_MOD_WEAKDECREF:
		weakdecref(self);
		result = self;
		break;

	case DLAUXCTRL_MOD_TRYINCREF:
		result = self;
		if (!tryincref(self))
			result = NULL;
		break;

	case DLAUXCTRL_MOD_NOTDESTROYED:
		result = self;
		if (wasdestroyed(self))
			result = NULL;
		break;

#if defined(__i386__) && !defined(__x86_64__)
		/* Special case for data-base on i386:
		 * For reference, see Glibc: `/sysdeps/generic/unwind-dw2-fde-glibc.c' */
#define DEFINED_DLAUXCTRL_GET_DATABASE
	case DLAUXCTRL_GET_DATABASE:
		/* Must return the relocated value for `DT_PLTGOT'.
		 * This we already keep track of (s.a. module-init.c:DlModule_ElfInitialize) */
		result = self->dm_elf.de_pltgot;
		break;
#endif /* __i386__ && !__x86_64__ */

	case DLAUXCTRL_GET_TEXTBASE: {
		ElfW(Half) i;
		ElfW(Word) rwx;
		rwx = PF_R | PF_X;
#ifndef DEFINED_DLAUXCTRL_GET_DATABASE
		__IF0 {
	case DLAUXCTRL_GET_DATABASE:
			rwx = PF_R | PF_W;
		}
#endif /* !DEFINED_DLAUXCTRL_GET_DATABASE */
		if unlikely(self->dm_ops) {
			result = NULL;
			break;
		}
		/* Search for the lowest program header with the correct flags. */
		for (result = (void *)-1, i = 0; i < self->dm_elf.de_phnum; ++i) {
			uintptr_t hdraddr;
			if (self->dm_elf.de_phdr[i].p_type != PT_LOAD)
				continue;
			if ((self->dm_elf.de_phdr[i].p_flags & (PF_R | PF_W | PF_X)) != rwx)
				continue;
			hdraddr = self->dm_loadaddr + self->dm_elf.de_phdr[i].p_vaddr;
			if ((uintptr_t)result > hdraddr)
				result = (void *)hdraddr;
		}
		if (result == (void *)-1)
			result = NULL;
	}	break;

	case DLAUXCTRL_GET_LOADSTART:
		result = (void *)self->dm_loadstart;
		break;

	case DLAUXCTRL_GET_LOADEND:
		result = (void *)self->dm_loadend;
		break;

	case DLAUXCTRL_ADD_FINALIZER: {
		struct dlmodule_finalizers *flz;
		void (DLFCN_CC *func)(void *);
		void *arg;
		func = va_arg(args, void (DLFCN_CC *)(void *));
		arg  = va_arg(args, void *);
again_add_finalizer_read_list:
		flz = atomic_read(&self->dm_finalize);
		if (!flz) {
			/* Lazily allocate dynamic finalizers. */
			flz = (struct dlmodule_finalizers *)malloc(sizeof(struct dlmodule_finalizers));
			if unlikely(!flz)
				goto err_nomem;
			flz->df_list = (struct dlmodule_finalizer *)malloc(1 * sizeof(struct dlmodule_finalizer));
			if unlikely(!flz->df_list) {
				free(flz);
				goto err_nomem;
			}
			atomic_rwlock_init(&flz->df_lock);
			flz->df_list[0].df_func = func;
			flz->df_list[0].df_arg  = arg;
			flz->df_size            = 1;
			if (!atomic_cmpxch(&self->dm_finalize, NULL, flz)) {
				free(flz);
				goto again_add_finalizer_read_list;
			}
		} else {
			struct dlmodule_finalizer *new_vector;
			/* Append to an existing finalizer list. */
			while (!atomic_rwlock_trywrite(&flz->df_lock)) {
				if (atomic_rwlock_reading(&flz->df_lock)) {
					/* Callbacks have already been serviced!
					 * -> Invoke the one given immediately. */
					(*func)(arg);
					goto done_add_finalizer;
				}
				sys_sched_yield();
			}
			new_vector = (struct dlmodule_finalizer *)realloc(flz->df_list,
			                                                  (flz->df_size + 1) *
			                                                  sizeof(struct dlmodule_finalizer));
			if unlikely(!new_vector) {
				atomic_rwlock_endwrite(&flz->df_lock);
				goto err_nomem;
			}
			flz->df_list = new_vector;
			/* Append to the end. */
			new_vector += flz->df_size++;
			new_vector->df_func = func;
			new_vector->df_arg  = arg;
			atomic_rwlock_endwrite(&flz->df_lock);
		}
done_add_finalizer:
		result = self;
	}	break;

	case DLAUXCTRL_REGISTER_EXTENSION: {
		struct dlmodule_format *extension, *next;
		size_t sizeof_dlmodule_format;
		size_t sizeof_dlcore_ops;
		REF DlModule *extmod;
		extension              = va_arg(args, struct dlmodule_format *);
		sizeof_dlmodule_format = va_arg(args, size_t);
		sizeof_dlcore_ops      = va_arg(args, size_t);
		if (sizeof_dlmodule_format != sizeof(struct dlmodule_format)) {
			dl_seterrorf("Invalid `sizeof_dlmodule_format': %" PRIuSIZ "; current version is %" PRIuSIZ,
			             sizeof_dlmodule_format, sizeof(struct dlmodule_format));
			goto err;
		}
		if (sizeof_dlcore_ops != sizeof(struct dlcore_ops)) {
			dl_seterrorf("Invalid `sizeof_dlcore_ops': %" PRIuSIZ "; current version is %" PRIuSIZ,
			             sizeof_dlcore_ops, sizeof(struct dlcore_ops));
			goto err;
		}
		if unlikely(!extension ||
		            !IS_ALIGNED((uintptr_t)extension, alignof(struct dlmodule_format))) {
			dl_seterror_badptr(extension);
			goto err;
		}

		/* Lookup which module it is that defines this extension. */
		extmod = libdl_dlgethandle((void *)extension->df_open, DLGETHANDLE_FINCREF);
		if unlikely(!extmod)
			goto err;

		/* Mark the declaring module as NODELETE. */
		atomic_or(&extmod->dm_flags, RTLD_NODELETE);

		/* Fill in the coreops V-table pointer. */
		extension->df_core = dl_getcoreops();

		/* Register the extension. */
		COMPILER_BARRIER();
		do {
			next = atomic_read(&dl_extensions);
			extension->df_next = next;
			COMPILER_WRITE_BARRIER();
		} while (!atomic_cmpxch_weak(&dl_extensions, next, extension));

		/* Re-return a pointer to the given handle. */
		result = self;
	}	break;

	case DLAUXCTRL_GET_DEPENDS: {
		size_t *pcount;
		pcount = va_arg(args, size_t *);
		result = self->dm_depvec;
		if (pcount)
			*pcount = self->dm_depcnt;
	}	break;

	case DLAUXCTRL_ELF_CHECK: {
		if (self->dm_ops)
			goto err;
		result = self;
	}	break;

	case DLAUXCTRL_ELF_GET_PHDRS: {
		size_t *pcount;
		/* Check that this is an ELF module. */
		if unlikely(self->dm_ops)
			goto err_notelf;
		pcount = va_arg(args, size_t *);
		result = self->dm_elf.de_phdr;
		if (pcount)
			*pcount = (size_t)self->dm_elf.de_phnum;
	}	break;

	case DLAUXCTRL_ELF_GET_SHDRS: {
		size_t *pcount;
		/* Check that this is an ELF module. */
		if unlikely(self->dm_ops)
			goto err_notelf;
		pcount = va_arg(args, size_t *);
		result = DlModule_ElfGetShdrs(self);
		if (result && pcount)
			*pcount = (size_t)self->dm_elf.de_phnum;
	}	break;

	case DLAUXCTRL_ELF_GET_DYN: {
		size_t *pcount;
		/* Check that this is an ELF module. */
		if unlikely(self->dm_ops)
			goto err_notelf;
		pcount = va_arg(args, size_t *);
		result = (void *)self->dm_dynhdr;
		if (pcount)
			*pcount = (size_t)self->dm_elf.de_dyncnt;
	}	break;

	case DLAUXCTRL_ELF_GET_DYNSYM: {
		size_t *pcount;
		/* Check that this is an ELF module. */
		if unlikely(self->dm_ops)
			goto err_notelf;
		pcount = va_arg(args, size_t *);
		result = (void *)self->dm_elf.de_dynsym_tab;
		if (pcount) {
			if unlikely(!result) {
				/* Special case: No `.dynsym' table. */
				*pcount = 0;
			} else {
				size_t count;
				count = DlModule_ElfGetDynSymCnt(self);
				if unlikely(!count)
					goto err;
				*pcount = count;
			}
		}
	}	break;

	case DLAUXCTRL_ELF_GET_DYNSTR:
		/* Check that this is an ELF module. */
		if unlikely(self->dm_ops)
			goto err_notelf;
		result = (void *)self->dm_elf.de_dynstr;
		break;

	case DLAUXCTRL_ELF_GET_SHSTRTAB:
		/* Check that this is an ELF module. */
		if unlikely(self->dm_ops)
			goto err_notelf;
		result = DlModule_ElfGetShstrtab(self);
		break;

	case DLAUXCTRL_ELF_GET_LSYMBOL: {
		NCX char const *name;
		uintptr_t elf_hash = DLMODULE_GETLOCALSYMBOL_HASH_UNSET;
		uintptr_t gnu_hash = DLMODULE_GETLOCALSYMBOL_HASH_UNSET;
		/* Check that this is an ELF module. */
		if unlikely(self->dm_ops)
			goto err_notelf;
		name   = va_arg(args, NCX char const *);
		result = (void *)DlModule_ElfGetLocalSymbol(self, name, &elf_hash, &gnu_hash);
	}	break;

	case DLAUXCTRL_ELF_SYMADDR: {
		struct dl_symbol sym;
		/* Check that this is an ELF module. */
		if unlikely(self->dm_ops)
			goto err_notelf;
		sym.ds_mod = self;
		sym.ds_sym = va_arg(args, NCX ElfW(Sym) const *);
		if (sym.ds_sym == NULL || sym.ds_sym->st_shndx == SHN_UNDEF) {
			result = NULL;
		} else {
			TRY {
				if unlikely(dl_symbol_resolve(&sym, (ElfW(Addr) *)&result))
					goto err;
			} EXCEPT {
				va_end(args);
				RETHROW();
			}
		}
	}	break;

	default:
		/* Allow extensions to implement their own auxiliary control commands. */
		if (self->dm_ops && self->dm_ops->df_dlauxctrl) {
			result = (*self->dm_ops->df_dlauxctrl)(self, cmd, args);
			break;
		}
		dl_seterrorf("Invalid auxctrl command %#x", cmd);
		goto err;
	}
done:
	va_end(args);
	return result;
err_notelf:
	dl_seterror_notelf(self->dm_filename);
	goto err;
err_nomem:
	dl_seterror_nomem();
err:
	result = NULL;
	goto done;
}

PRIVATE NONNULL((1, 2)) int CC
DlModule_IteratePhdr(DlModule *__restrict self,
                     NCX __dl_iterator_callback callback,
                     NCX void *arg)
		THROWS(...) {
	int result;
	struct dl_phdr_info info;
	info.dlpi_addr      = self->dm_loadaddr;
	info.dlpi_name      = self->dm_filename;
	info.dlpi_adds      = 0; /* ??? */
	info.dlpi_subs      = 0; /* ??? */
	info.dlpi_tls_modid = self->dm_tlsmsize ? (size_t)(uintptr_t)self : 0;
	info.dlpi_tls_data  = DlModule_TryGetTLSAddr(self);
	if likely(!self->dm_ops) {
		info.dlpi_phdr  = self->dm_elf.de_phdr;
		info.dlpi_phnum = self->dm_elf.de_phnum;
		result = (*callback)(&info, sizeof(info), arg);
	} else if (self->dm_ops->df_lsphdrs) {
		result = (*self->dm_ops->df_lsphdrs)(self, &info, callback, arg);
	} else {
		/* Single-program-header emulation. */
		ElfW(Phdr) ph[1];
		ph[0].p_type    = PT_LOAD;
		ph[0].p_offset  = 0;
		ph[0].p_vaddr   = self->dm_loadstart - self->dm_loadaddr;
		ph[0].p_paddr   = ph[0].p_vaddr;
		ph[0].p_filesz  = self->dm_loadend - self->dm_loadstart;
		ph[0].p_memsz   = ph[0].p_filesz;
		ph[0].p_flags   = PF_X | PF_W | PF_R;
		ph[0].p_align   = 1;
		info.dlpi_phdr  = ph;
		info.dlpi_phnum = lengthof(ph);
		result = (*callback)(&info, sizeof(info), arg);
	}
	return result;
}


/* Enumerate all loaded modules, as  well as information about  them.
 * Enumeration stops when `*callback' returns a non-zero value, which
 * will then also be returned  by this function. Otherwise, `0'  will
 * be returned after all modules have been enumerated. */
INTERN NONNULL((1)) int DLFCN_CC
libdl_iterate_phdr(NCX __dl_iterator_callback callback, NCX void *arg)
		THROWS(E_SEGFAULT, ...) {
	int result = 0;
	REF DlModule *current, *next;
	dlglobals_all_read(&dl_globals);
	current = DLIST_FIRST(&dl_globals.dg_alllist);
	while (current) {
		if (!tryincref(current)) {
			current = DLIST_NEXT(current, dm_modules);
			continue;
		}
		dlglobals_all_endread(&dl_globals);
got_current:
		TRY {
			result = DlModule_IteratePhdr(current, callback, arg);
		} EXCEPT {
			decref_unlikely(current);
			RETHROW();
		}
		if (result != 0) {
			decref_unlikely(current);
			goto done;
		}

		/* Try to lock the next module. */
		dlglobals_all_read(&dl_globals);
		next = DLIST_NEXT(current, dm_modules);
		while (next && !tryincref(next))
			next = DLIST_NEXT(next, dm_modules);
		dlglobals_all_endread(&dl_globals);

		/* Continue enumerating the next module. */
		decref_unlikely(current);
		if (!next)
			goto done;
		current = next;
		goto got_current;
	}
	dlglobals_all_endread(&dl_globals);
done:
	return result;
}






DEFINE_PUBLIC_ALIAS(dlopen, libdl_dlopen);
DEFINE_PUBLIC_ALIAS(dlclose, libdl_dlclose);
DEFINE_PUBLIC_ALIAS(dlexceptaware, libdl_dlexceptaware);
DEFINE_PUBLIC_ALIAS(dlsym, libdl_dlsym);
DEFINE_PUBLIC_ALIAS(dlerror, libdl_dlerror);
DEFINE_PUBLIC_ALIAS(dlgethandle, libdl_dlgethandle);
DEFINE_PUBLIC_ALIAS(dlgetmodule, libdl_dlgetmodule);
DEFINE_PUBLIC_ALIAS(dladdr, libdl_dladdr);
DEFINE_PUBLIC_ALIAS(dlmodulefd, libdl_dlmodulefd);
DEFINE_PUBLIC_ALIAS(dlmodulename, libdl_dlmodulename);
DEFINE_PUBLIC_ALIAS(dlmodulebase, libdl_dlmodulebase);
DEFINE_PUBLIC_ALIAS(dllocksection, libdl_dllocksection);
DEFINE_PUBLIC_ALIAS(dlunlocksection, libdl_dlunlocksection);
DEFINE_PUBLIC_ALIAS(dlsectionname, libdl_dlsectionname);
DEFINE_PUBLIC_ALIAS(dlsectionindex, libdl_dlsectionindex);
DEFINE_PUBLIC_ALIAS(dlsectionmodule, libdl_dlsectionmodule);
DEFINE_PUBLIC_ALIAS(dlinflatesection, libdl_dlinflatesection);
DEFINE_PUBLIC_ALIAS(dlclearcaches, libdl_dlclearcaches);
DEFINE_PUBLIC_ALIAS(dlauxctrl, libdl_dlauxctrl);
DEFINE_PUBLIC_ALIAS(dl_iterate_phdr, libdl_iterate_phdr);
DEFINE_PUBLIC_ALIAS(dlinfo, libdl_dlinfo);



__ASM_BEGIN
__ASM_L(.macro .word_noreloc value:req)
#ifdef __ARCH_HAVE_wordrel
#define word_noreloc_decode(p_ptr) (void *)(dl_rtld_module.dm_loadaddr + *(p_ptr))
__ASM_L(	.wordrel __ASM_ARG(\value))
#elif defined(__ARCH_HAVE_wordoff)
#define word_noreloc_decode(p_ptr) (void *)((byte_t *)(p_ptr) + *(p_ptr))
__ASM_L(	.wordoff __ASM_ARG(\value))
#elif !defined(__DEEMON__)
#error "No way to encode relative pointers"
#endif /* ... */
__ASM_L(.endm)
__ASM_END


/*[[[deemon
import * from deemon;
local BUILTIN_SYMBOLS = {
	"dlopen"           : "libdl_dlopen",
	"dlfopen"          : "libdl_dlfopen",
	"dlclose"          : "libdl_dlclose",
	"dlexceptaware"    : "libdl_dlexceptaware",
	"dlsym"            : "libdl_dlsym",
	"dlerror"          : "libdl_dlerror",
	"dlgethandle"      : "libdl_dlgethandle",
	"dlgetmodule"      : "libdl_dlgetmodule",
	"dladdr"           : "libdl_dladdr",
	"dlmodulefd"       : "libdl_dlmodulefd",
	"dlmodulename"     : "libdl_dlmodulename",
	"dlmodulebase"     : "libdl_dlmodulebase",
	"dllocksection"    : "libdl_dllocksection",
	"dlunlocksection"  : "libdl_dlunlocksection",
	"dlsectionname"    : "libdl_dlsectionname",
	"dlsectionindex"   : "libdl_dlsectionindex",
	"dlsectionmodule"  : "libdl_dlsectionmodule",
	"dlinflatesection" : "libdl_dlinflatesection",
	"dlclearcaches"    : "libdl_dlclearcaches",
	"___tls_get_addr"  : ("libdl____tls_get_addr", "defined(__i386__) && !defined(__x86_64__)"),
	"__tls_get_addr"   : "libdl___tls_get_addr",
	"dltlsallocseg"    : "libdl_dltlsallocseg",
	"dltlsfreeseg"     : "libdl_dltlsfreeseg",
	"dltlsalloc"       : "libdl_dltlsalloc",
	"dltlsfree"        : "libdl_dltlsfree",
	"dltlsaddr"        : "libdl_dltlsaddr",
	"dltlsaddr2"       : "libdl_dltlsaddr2",
	"dlauxctrl"        : "libdl_dlauxctrl",
	"dl_iterate_phdr"  : "libdl_iterate_phdr",
	"dlinfo"           : "libdl_dlinfo",
};
local names = BUILTIN_SYMBOLS.keys.sorted();
function printDb(longestNameLen: int) {
	print("#define DLSYM_BUILTIN_NAMELEN ", longestNameLen);
	for (local n: names) {
		local target = BUILTIN_SYMBOLS[n];
		local adjn = n.ljust(longestNameLen, "\0");
		if (target !is string) {
			local targetn, cond = target...;
			print("#if ", cond);
			print("__ASM_L(.ascii ", repr adjn, "; .word_noreloc ", targetn, ")");
			print("#endif /" "* ... *" "/");
		} else {
			print("__ASM_L(.ascii ", repr adjn, "; .word_noreloc ", target, ")");
		}
	}
}
local longest_name_len = (names.each.length > ...) + 1;
local aligned4 = (longest_name_len + 1 + 3) & ~3;
local aligned8 = (longest_name_len + 1 + 7) & ~7;
local baseCount = 0;
local plusNConditions = Dict();
for (local none, map: BUILTIN_SYMBOLS) {
	if (map is string) {
		++baseCount;
	} else {
		local cond = map.last;
		plusNConditions[cond] = plusNConditions.get(cond, 0) + 1;
	}
}
if (!plusNConditions) {
	print("#define DLSYM_BUILTIN_COUNT ", baseCount);
} else {
	print("enum { DLSYM_BUILTIN_COUNT = ", baseCount);
	for (local cond: plusNConditions.keys.sorted()) {
		print("#if ", cond);
		print("                             + ", plusNConditions[cond]);
		print("#endif /" "* ... *" "/");
	}
	print("};");
}
print("__ASM_BEGIN");
print("__ASM_L(.pushsection .rodata)");
print("__ASM_L(.align __SIZEOF_POINTER__)");
print("__ASM_L(.type dlsym_builtin_table, \"object\")");
print("__ASM_L(dlsym_builtin_table:)");
if (aligned4 == aligned8) {
	printDb(aligned4);
} else {
	print("#if __SIZEOF_POINTER__ == 4");
	printDb(aligned4);
	print("#elif __SIZEOF_POINTER__ == 8");
	printDb(aligned8);
	print("#elif !defined(__DEEMON__)");
	print("#error \"Unsupported __SIZEOF_POINTER__\"");
	print("#endif /" "* ... *" "/");
}
print("__ASM_L(.size dlsym_builtin_table, . - dlsym_builtin_table)");
print("__ASM_L(.popsection)");
print("__ASM_END");
]]]*/
enum { DLSYM_BUILTIN_COUNT = 29
#if defined(__i386__) && !defined(__x86_64__)
                             + 1
#endif /* ... */
};
__ASM_BEGIN
__ASM_L(.pushsection .rodata)
__ASM_L(.align __SIZEOF_POINTER__)
__ASM_L(.type dlsym_builtin_table, "object")
__ASM_L(dlsym_builtin_table:)
#if __SIZEOF_POINTER__ == 4
#define DLSYM_BUILTIN_NAMELEN 20
#if defined(__i386__) && !defined(__x86_64__)
__ASM_L(.ascii "___tls_get_addr\0\0\0\0\0"; .word_noreloc libdl____tls_get_addr)
#endif /* ... */
__ASM_L(.ascii "__tls_get_addr\0\0\0\0\0\0"; .word_noreloc libdl___tls_get_addr)
__ASM_L(.ascii "dl_iterate_phdr\0\0\0\0\0"; .word_noreloc libdl_iterate_phdr)
__ASM_L(.ascii "dladdr\0\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dladdr)
__ASM_L(.ascii "dlauxctrl\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlauxctrl)
__ASM_L(.ascii "dlclearcaches\0\0\0\0\0\0\0"; .word_noreloc libdl_dlclearcaches)
__ASM_L(.ascii "dlclose\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlclose)
__ASM_L(.ascii "dlerror\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlerror)
__ASM_L(.ascii "dlexceptaware\0\0\0\0\0\0\0"; .word_noreloc libdl_dlexceptaware)
__ASM_L(.ascii "dlfopen\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlfopen)
__ASM_L(.ascii "dlgethandle\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlgethandle)
__ASM_L(.ascii "dlgetmodule\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlgetmodule)
__ASM_L(.ascii "dlinflatesection\0\0\0\0"; .word_noreloc libdl_dlinflatesection)
__ASM_L(.ascii "dlinfo\0\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlinfo)
__ASM_L(.ascii "dllocksection\0\0\0\0\0\0\0"; .word_noreloc libdl_dllocksection)
__ASM_L(.ascii "dlmodulebase\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlmodulebase)
__ASM_L(.ascii "dlmodulefd\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlmodulefd)
__ASM_L(.ascii "dlmodulename\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlmodulename)
__ASM_L(.ascii "dlopen\0\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlopen)
__ASM_L(.ascii "dlsectionindex\0\0\0\0\0\0"; .word_noreloc libdl_dlsectionindex)
__ASM_L(.ascii "dlsectionmodule\0\0\0\0\0"; .word_noreloc libdl_dlsectionmodule)
__ASM_L(.ascii "dlsectionname\0\0\0\0\0\0\0"; .word_noreloc libdl_dlsectionname)
__ASM_L(.ascii "dlsym\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlsym)
__ASM_L(.ascii "dltlsaddr\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dltlsaddr)
__ASM_L(.ascii "dltlsaddr2\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dltlsaddr2)
__ASM_L(.ascii "dltlsalloc\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dltlsalloc)
__ASM_L(.ascii "dltlsallocseg\0\0\0\0\0\0\0"; .word_noreloc libdl_dltlsallocseg)
__ASM_L(.ascii "dltlsfree\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dltlsfree)
__ASM_L(.ascii "dltlsfreeseg\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dltlsfreeseg)
__ASM_L(.ascii "dlunlocksection\0\0\0\0\0"; .word_noreloc libdl_dlunlocksection)
#elif __SIZEOF_POINTER__ == 8
#define DLSYM_BUILTIN_NAMELEN 24
#if defined(__i386__) && !defined(__x86_64__)
__ASM_L(.ascii "___tls_get_addr\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl____tls_get_addr)
#endif /* ... */
__ASM_L(.ascii "__tls_get_addr\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl___tls_get_addr)
__ASM_L(.ascii "dl_iterate_phdr\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_iterate_phdr)
__ASM_L(.ascii "dladdr\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dladdr)
__ASM_L(.ascii "dlauxctrl\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlauxctrl)
__ASM_L(.ascii "dlclearcaches\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlclearcaches)
__ASM_L(.ascii "dlclose\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlclose)
__ASM_L(.ascii "dlerror\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlerror)
__ASM_L(.ascii "dlexceptaware\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlexceptaware)
__ASM_L(.ascii "dlfopen\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlfopen)
__ASM_L(.ascii "dlgethandle\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlgethandle)
__ASM_L(.ascii "dlgetmodule\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlgetmodule)
__ASM_L(.ascii "dlinflatesection\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlinflatesection)
__ASM_L(.ascii "dlinfo\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlinfo)
__ASM_L(.ascii "dllocksection\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dllocksection)
__ASM_L(.ascii "dlmodulebase\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlmodulebase)
__ASM_L(.ascii "dlmodulefd\0\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlmodulefd)
__ASM_L(.ascii "dlmodulename\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlmodulename)
__ASM_L(.ascii "dlopen\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlopen)
__ASM_L(.ascii "dlsectionindex\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlsectionindex)
__ASM_L(.ascii "dlsectionmodule\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlsectionmodule)
__ASM_L(.ascii "dlsectionname\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlsectionname)
__ASM_L(.ascii "dlsym\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlsym)
__ASM_L(.ascii "dltlsaddr\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dltlsaddr)
__ASM_L(.ascii "dltlsaddr2\0\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dltlsaddr2)
__ASM_L(.ascii "dltlsalloc\0\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dltlsalloc)
__ASM_L(.ascii "dltlsallocseg\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dltlsallocseg)
__ASM_L(.ascii "dltlsfree\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dltlsfree)
__ASM_L(.ascii "dltlsfreeseg\0\0\0\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dltlsfreeseg)
__ASM_L(.ascii "dlunlocksection\0\0\0\0\0\0\0\0\0"; .word_noreloc libdl_dlunlocksection)
#elif !defined(__DEEMON__)
#error "Unsupported __SIZEOF_POINTER__"
#endif /* ... */
__ASM_L(.size dlsym_builtin_table, . - dlsym_builtin_table)
__ASM_L(.popsection)
__ASM_END
/*[[[end]]]*/

struct dlsym_builtin_symbol {
	char      dbs_name[DLSYM_BUILTIN_NAMELEN]; /* Symbol name */
	uintptr_t dbs_addr;                        /* Symbol address (either module-, or self-relative) */
};

INTDEF struct dlsym_builtin_symbol const dlsym_builtin_table[DLSYM_BUILTIN_COUNT];



/* WARNING: If you intend to rename this `dl_program_invocation_short_name'
 *          variable, make sure to also  update the special handling  found
 *          in moddbx's `cexpr_load_special_libdl_symbol()' function, which
 *          contains special handling for binding against this symbol! */
PRIVATE char *dl_program_invocation_short_name = NULL;
PRIVATE ATTR_RETNONNULL WUNUSED char **
NOTHROW_NCX(FCALL dlget_p_program_invocation_short_name)(void) {
	if (!dl_program_invocation_short_name) {
		char *progname = dl_globals.dg_peb->pp_argv
		                 ? dl_globals.dg_peb->pp_argv[0]
		                 : NULL;
		if (progname)
			progname = strrchrnul(progname, '/') + 1;
		atomic_cmpxch(&dl_program_invocation_short_name,
		              NULL, progname);
	}
	return &dl_program_invocation_short_name;
}



/* Return the address of a builtin function (e.g. `dlopen(3D)') */
INTERN ATTR_PURE WUNUSED NONNULL((1)) void *
NOTHROW_NCX(CC dlsym_builtin)(NCX char const *name) {
	size_t lo, hi;
	/* Do a binary search across `dlsym_builtin_table' */
	lo = 0;
	hi = lengthof(dlsym_builtin_table);
	while (lo < hi) {
		int cmp;
		size_t index;
		index = (lo + hi) / 2;
		cmp   = strcmp(name, dlsym_builtin_table[index].dbs_name);
		if (cmp < 0) {
			hi = index;
		} else if (cmp > 0) {
			lo = index + 1;
		} else {
			/* Found it! */
			return word_noreloc_decode(&dlsym_builtin_table[index].dbs_addr);
		}
	}

	/* Check for special symbols. */
	switch (*name++) {

	case '_':
		switch (*name++) {
		case 'e':
			goto check_nviron; /* char **_environ */

		case 'p':
			if (strcmp(name, "gmptr") == 0) /* char *_pgmptr */
				goto return_program_invocation_name;
			break;

		case '_':
			switch (*name++) {

			case 'e':
				goto check_nviron; /* char **__environ */

			case 'a':
				if (*name++ != 'r')
					break;
				if (*name++ != 'g')
					break;
				if (name[0] == '\0' || name[1] != '\0')
					break;
				if (*name == 'c') { /* int __argc */
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
					return &dl_globals.dg_peb->pp_argc;
#elif __SIZEOF_INT__ < __SIZEOF_SIZE_T__
					/* Must return a pointer to the least significant bits */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
					return &dl_globals.dg_peb->pp_argc;
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
					return (byte_t *)&dl_globals.dg_peb->pp_argc + (__SIZEOF_SIZE_T__ - __SIZEOF_INT__);
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
#else /* __SIZEOF_INT__ <= __SIZEOF_SIZE_T__ */
#error "Unsupported configuration: `int' doesn't fit into `size_t'"
#endif /* __SIZEOF_INT__ > __SIZEOF_SIZE_T__ */
				}
				if (*name == 'v') /* char **__argv */
					return &dl_globals.dg_peb->pp_argv;
				break;

			case 'p':
				if (bcmp(name, "rogname", 7, sizeof(char)) == 0) {
					name += 7;
					if (*name == '\0') /* char *__progname */
						goto return_program_invocation_short_name;
					if (strcmp(name, "_full") == 0) /* char *__progname_full */
						goto return_program_invocation_name;
				} else if (strcmp(name, "eb") == 0) { /* struct process_peb __peb */
					return dl_globals.dg_peb;
				}
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
		break;

	case 'e':
check_nviron:
		if (strcmp(name, "nviron") == 0) /* char **environ */
			return &dl_globals.dg_peb->pp_envp;
		break;

	case 'p':
		if (bcmp(name, "rogram_invocation_", 18, sizeof(char)) == 0) {
			name += 18;
			if (strcmp(name, "name") == 0) { /* char *program_invocation_name */
return_program_invocation_name:
				return &dl_globals.dg_peb->pp_argv[0];
			}
			if (strcmp(name, "short_name") == 0) { /* char *program_invocation_short_name */
return_program_invocation_short_name:
				return dlget_p_program_invocation_short_name();
			}
		}
		break;

	default:
		break;
	}
	return NULL;
}


/* Used internally for some relocations: the "size" of libdl builtin symbols. */
INTERN ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(CC dlsym_builtin_size)(NCX char const *name) {
	/* Only a couple of symbols should actually have a non-zero size value. */
	switch (*name++) {

	case '_':
		switch (*name++) {
		case 'e':
			goto check_environ; /* char **_environ */

		case 'p':
			if (strcmp(name, "gmptr") == 0) /* char *_pgmptr */
				goto return_pointer;
			break;

		case '_':
			switch (*name++) {

			case 'e':
				goto check_environ; /* char **__environ */

			case 'a':
				if (*name++ != 'r')
					break;
				if (*name++ != 'g')
					break;
				if (name[0] == '\0' || name[1] != '\0')
					break;
				if (*name == 'c') { /* int __argc */
#if __SIZEOF_POINTER__ == __SIZEOF_INT__
					goto return_pointer;
#else /* __SIZEOF_POINTER__ == __SIZEOF_INT__ */
					return sizeof(int);
#endif /* __SIZEOF_POINTER__ != __SIZEOF_INT__ */
				}
				if (*name == 'v') /* char **__argv */
					goto return_pointer;
				break;

			case 'p':
				if (bcmp(name, "rogname", 7, sizeof(char)) == 0) {
					name += 7;
					if (*name == '\0') /* char *__progname */
						goto return_pointer;
					if (strcmp(name, "_full") == 0) /* char *__progname_full */
						goto return_pointer;
				} else if (strcmp(name, "eb") == 0) { /* struct process_peb __peb */
					return sizeof(struct process_peb);
				}
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
		break;

	case 'e':
check_environ:
		if (strcmp(name, "nviron") == 0) /* char **environ */
			goto return_pointer;
		break;

	case 'p':
		if (bcmp(name, "rogram_invocation_", 18, sizeof(char)) == 0) {
			name += 18;
			if (strcmp(name, "name") == 0) /* char *program_invocation_name */
				goto return_pointer;
			if (strcmp(name, "short_name") == 0) /* char *program_invocation_short_name */
				goto return_pointer;
		}
		break;

	default:
		break;
	}
	return 0;
return_pointer:
	return sizeof(void *);
}



#define INIT_RTLD_SECTION(index, link_name, elf_type, elf_flags)                                                       \
	{                                                                                                                  \
		.ds_data        = NULL, /* Initialized later */                                                                \
		.ds_size        = 0,    /* Initialized later (even though it could be here if ld/gcc weren't quite as dumb) */ \
		.ds_entsize     = 0,                                                                                           \
		.ds_link        = 0,                                                                                           \
		.ds_info        = 0,                                                                                           \
		.ds_elfflags    = elf_flags,                                                                                   \
		.ds_refcnt      = 1,                                                                                           \
		.ds_module_lock = ATOMIC_RWLOCK_INIT,                                                                          \
		.ds_module      = NULL, /* Initialized later */                                                                \
		.ds_dangling    = NULL,                                                                                        \
		.ds_flags       = DLSECTION_FLAG_OWNED,                                                                        \
		.ds_index       = index,                                                                                       \
	}




INTERN ATTR_CONST WUNUSED DlSection *
NOTHROW(CC dlsec_builtin_index)(size_t sect_index) {
	DlSection *result;
	switch (sect_index) {
#define DEFINE_BUILTIN_SECTION(index, sect_name, link_name, elf_type, elf_flags)                            \
	case index: {                                                                                           \
		INTDEF byte_t __rtld_##link_name##_start[];                                                         \
		INTDEF byte_t __rtld_##link_name##_end[];                                                           \
		PRIVATE DlSection rtld_sect_##link_name = INIT_RTLD_SECTION(index, link_name, elf_type, elf_flags); \
		result = &rtld_sect_##link_name;                                                                    \
		if (!result->ds_module) {                                                                           \
			result->ds_data = (void *)(__rtld_##link_name##_start);                                         \
			result->ds_size = (size_t)(__rtld_##link_name##_end - __rtld_##link_name##_start);              \
			COMPILER_WRITE_BARRIER();                                                                       \
			result->ds_module = &dl_rtld_module;                                                            \
		}                                                                                                   \
	}	break;
	BUILTIN_SECTIONS_ENUMERATE(DEFINE_BUILTIN_SECTION)
#undef DEFINE_BUILTIN_SECTION
	default:
		result = NULL;
		break;
	}
	return result;
}

INTERN ATTR_CONST WUNUSED char const *
NOTHROW(CC dlsec_builtin_name)(size_t sect_index) {
	char const *result;
	switch (sect_index) {
#define DEFINE_BUILTIN_SECTION(index, sect_name, link_name, elf_type, elf_flags) \
	case index:                                                                  \
		result = sect_name;                                                      \
		break;
	BUILTIN_SECTIONS_ENUMERATE(DEFINE_BUILTIN_SECTION)
#undef DEFINE_BUILTIN_SECTION
	default:
		result = NULL;
		break;
	}
	return result;
}


INTERN ATTR_PURE WUNUSED NONNULL((1)) DlSection *
NOTHROW_NCX(CC dlsec_builtin)(NCX char const *name) {
	size_t sect_index;
	char const *sect_name;
	for (sect_index = 0;; ++sect_index) {
		sect_name = dlsec_builtin_name(sect_index);
		if (!sect_name)
			break; /* Unknown section name. */
		if (strcmp(sect_name, name) == 0)
			break; /* Found it. */
	}
	return dlsec_builtin_index(sect_index);
}


/* Return the address of a function `name'  that is required by the RTLD  core
 * and  must be defined by one of the  loaded libraries. - If no such function
 * is defined, log an error message to the system log and terminate the hosted
 * application ungracefully. */
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) void *
NOTHROW(FCALL dl_require_global)(char const *__restrict name) {
	void *result;
	/* Search all globally loaded modules for the symbol. */
	result = libdl_dlsym((DlModule *)RTLD_DEFAULT, name);
	if unlikely(!result) {
		struct debugtrap_reason r;
		syslog(LOG_ERR, "[rtld] Required function %q not found (%q)\n",
		       name, dl_globals.dg_errmsg);
		r.dtr_signo  = SIGABRT;
		r.dtr_reason = DEBUGTRAP_REASON_NONE;
		sys_debugtrap(NULL, &r);
		sys_exit_group(EXIT_FAILURE);
	}
	return result;
}



DECL_END

#endif /* !GUARD_LIBDL_BUILTIN_C */
