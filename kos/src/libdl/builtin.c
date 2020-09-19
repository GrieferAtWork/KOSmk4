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
#ifndef GUARD_LIBDL_BUILTIN_C
#define GUARD_LIBDL_BUILTIN_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

/* Keep this one the first */
#include "dl.h"
/**/

#include <hybrid/align.h>

#include <kos/debugtrap.h>
#include <kos/exec/peb.h>
#include <kos/syscalls.h>
#include <sys/mman.h>

#include <errno.h>
#include <format-printer.h>
#include <malloc.h>
#include <sched.h>
#include <signal.h> /* SIGABRT */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

#include <libzlib/error.h>
#include <libzlib/inflate.h>

#include "builtin.h"

DECL_BEGIN

INTERN NONNULL((2)) ssize_t
NOTHROW_RPC(FORMATPRINTER_CC syslog_printer)(void *arg,
                                             char const *__restrict data,
                                             size_t datalen) {
	return sys_syslog((syscall_ulong_t)arg,
	                  data,
	                  datalen);
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

PRIVATE ATTR_NOINLINE ATTR_NORETURN NONNULL((1)) void LIBCCALL
assertion_failure_core(struct assert_args *__restrict args) {
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


INTERN ATTR_COLD ATTR_NORETURN void LIBCCALL
__afail(char const *expr, char const *file,
        unsigned int line, char const *func) {
	struct assert_args aargs;
	memset(&aargs, 0, sizeof(aargs));
	aargs.expr = expr;
	aargs.file = file;
	aargs.line = line;
	aargs.func = func;
	aargs.pc   = __builtin_return_address(0);
	assertion_failure_core(&aargs);
}

INTERN ATTR_COLD ATTR_NORETURN void VLIBCCALL
__afailf(char const *expr, char const *file,
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



/* DL error handling. */
INTERN char dl_error_buffer[128];
INTERN char *dl_error_message = NULL;
INTERN char *DLFCN_CC libdl_dlerror(void) {
	return ATOMIC_XCH(dl_error_message, NULL);
}


INTERN ATTR_COLD int CC
dl_seterror_badptr(void *ptr) {
	return dl_seterrorf("Bad pointer: %p", ptr);
}

INTERN ATTR_COLD int CC
dl_seterror_badmodule(void *modptr) {
	return dl_seterrorf("Bad module handle: %p", modptr);
}

INTERN ATTR_COLD int CC
dl_seterror_badsection(void *sectptr) {
	return dl_seterrorf("Bad section handle: %p", sectptr);
}

PRIVATE char const message_nomem[] = "Insufficient memory";
INTERN ATTR_COLD int CC
dl_seterror_nomem(void) {
	memcpy(dl_error_buffer, message_nomem, sizeof(message_nomem));
	ATOMIC_WRITE(dl_error_message, (char *)dl_error_buffer);
	return -1;
}

INTERN ATTR_COLD NONNULL((1)) int VCC
dl_seterrorf(char const *__restrict format, ...) {
	int result;
	va_list args;
	va_start(args, format);
	result = dl_vseterrorf(format, args);
	va_end(args);
	return result;
}

INTERN ATTR_COLD NONNULL((1)) int CC
dl_vseterrorf(char const *__restrict format, va_list args) {
	vsnprintf(dl_error_buffer,
	          sizeof(dl_error_buffer),
	          format,
	          args);
	ATOMIC_WRITE(dl_error_message,
	             (char *)dl_error_buffer);
	return -1;
}



/* Lock used to ensure that only a single thread can ever load modules
 * at the same time (used to prevent potential race conditions arising
 * from the fact that various components must be accessed globally). */
INTERN struct atomic_owner_rwlock DlModule_LoadLock = ATOMIC_OWNER_RWLOCK_INIT;

LOCAL NONNULL((1)) void CC
update_module_flags(DlModule *__restrict self, int mode) {
	uintptr_t old_flags;
again_old_flags:
	old_flags = ATOMIC_READ(self->dm_flags);
	if ((mode & RTLD_GLOBAL) && !(old_flags & RTLD_GLOBAL)) {
		/* Make the module global. */
		atomic_rwlock_write(&DlModule_GlobalLock);
		if (!ATOMIC_CMPXCH_WEAK(self->dm_flags, old_flags,
		                        old_flags | RTLD_GLOBAL)) {
			atomic_rwlock_endwrite(&DlModule_GlobalLock);
			goto again_old_flags;
		}
		assert(!self->dm_globals.ln_pself);
		DlModule_AddToGlobals(self);
		assert(self->dm_globals.ln_pself);
		atomic_rwlock_endwrite(&DlModule_GlobalLock);
	}
}


INTERN WUNUSED REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *DLFCN_CC
libdl_dlopen(char const *filename, int mode) {
	REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *result;
	if unlikely(!filename) {
		/* ... If filename is NULL, then the returned handle is for the main program... */
		result = DlModule_GlobalList;
		assert(result);
		assert(result->dm_flags & RTLD_NODELETE);
		/* Don't incref() the returned module for this case:
		 *   - The main module itself was loaded with `RTLD_NODELETE', meaning
		 *     that attempts to dlclose() that module are already no-ops to
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
			ATOMIC_WRITE(dl_error_message, NULL);
			result = DlModule_FindFilenameInPathListFromAll(filename);
		}
		if likely(result)
			update_module_flags(result, mode);
	} else {
		if (strchr(filename, '/')) {
			/* Load a module from an absolute filesystem location. */
			result = DlModule_OpenFilename(filename, mode);
		} else {
			ATOMIC_WRITE(dl_error_message, NULL);
			/* Load a module using the LD-library path List */
			result = DlModule_OpenFilenameInPathList(dl_library_path,
			                                         filename,
			                                         mode);
		}
	}
	if unlikely(!result) {
		if (!ATOMIC_READ(dl_error_message))
			dl_seterrorf("Failed to open module %q", filename);
	} else {
		while unlikely(result->dm_flags & RTLD_LOADING) {
			/* The library is still being initialized by another thread. */
			if (ATOMIC_READ(result->dm_refcnt) <= 1) {
				/* The module is supposed to go away! (try to load it again) */
				if (!(result->dm_flags & RTLD_NODELETE))
					DlModule_Decref(result);
				goto again;
			}
			sys_sched_yield();
		}
	}
/*done:*/
	atomic_owner_rwlock_endwrite(&DlModule_LoadLock);
	return result;
}
INTERN NONNULL((1)) int DLFCN_CC
libdl_dlclose(REF DlModule *self) {
	if unlikely(!DL_VERIFY_MODULE_HANDLE(self))
		goto err_bad_module;
	/* Don't decref NODELETE modules! */
	if likely(!(self->dm_flags & RTLD_NODELETE))
		DlModule_Decref(self);
	return 0;
err_bad_module:
	return dl_seterror_badmodule(self);
}


INTERN NONNULL((1)) int DLFCN_CC
libdl_dlexceptaware(DlModule *self) {
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



#define DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NOT_FOUND 0
#define DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_FOUND     1
#define DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NO_MODULE 2
#define DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_ERROR     3
PRIVATE NONNULL((2)) unsigned int CC
dlmodule_search_symbol_in_dependencies(DlModule *__restrict self,
                                       char const *__restrict name,
                                       uintptr_t *__restrict phash_elf,
                                       uintptr_t *__restrict phash_gnu,
                                       ElfW(Addr) *__restrict presult,
                                       struct dl_symbol *__restrict pweak_symbol,
                                       size_t depth) {
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
				ElfW(Addr) result;
				result = symbol.ds_sym->st_value;
				if (ELFW(ST_TYPE)(symbol.ds_sym->st_info) == STT_TLS) {
					void *tlsbase;
					tlsbase = libdl_dltlsaddr(symbol.ds_mod);
					if unlikely(!tlsbase)
						return DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_ERROR;
					result += (ElfW(Addr))tlsbase;
				} else {
					if (symbol.ds_sym->st_shndx != SHN_ABS)
						result += symbol.ds_mod->dm_loadaddr;
					if (ELFW(ST_TYPE)(symbol.ds_sym->st_info) == STT_GNU_IFUNC ||
					    ELFW(ST_TYPE)(symbol.ds_sym->st_info) == STT_KOS_IDATA)
						result = (*(ElfW(Addr)(*)(void))(void *)result)();
				}
				*presult = result;
				return DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_FOUND;
			}
		}
	}
	return DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NOT_FOUND;
}

INTERN NONNULL((2)) void *DLFCN_CC
libdl_dlsym(DlModule *self, char const *__restrict name) {
	ElfW(Addr) result;
	uintptr_t hash_elf, hash_gnu;
	struct dl_symbol symbol;
	struct dl_symbol weak_symbol;
	REF DlModule *next_module;
	hash_elf = hash_gnu = DLMODULE_GETLOCALSYMBOL_HASH_UNSET;
	weak_symbol.ds_mod  = NULL;
	if (self == RTLD_DEFAULT) {
		/* Search all modules in order of being loaded. */
		atomic_rwlock_read(&DlModule_GlobalLock);
		symbol.ds_mod = DlModule_GlobalList;
		assert(symbol.ds_mod);
		for (;;) {
			if unlikely(!DlModule_TryIncref(symbol.ds_mod)) {
again_search_globals_next_noref:
				symbol.ds_mod = symbol.ds_mod->dm_globals.ln_next;
				if unlikely(!symbol.ds_mod) {
					atomic_rwlock_endread(&DlModule_GlobalLock);
					break;
				}
				continue;
			}
			atomic_rwlock_endread(&DlModule_GlobalLock);
again_search_globals_module:
			/* Search this module. */
			if (symbol.ds_mod == &dl_rtld_module) {
				result = (ElfW(Addr))dlsym_builtin(name);
				if (result) {
					DlModule_DecrefNoKill(symbol.ds_mod);
					goto done;
				}
			} else if (symbol.ds_mod->dm_ops) {
				int error;
				error = (*symbol.ds_mod->dm_ops->df_dlsym)(symbol.ds_mod, name,
				                                           (void **)&symbol.ds_sym, NULL);
				if (error >= 0) {
					if (error > 0) {
						/* Weak definition. */
						if (!weak_symbol.ds_mod)
							weak_symbol = symbol; /* First weak def */
						else {
							DlModule_Decref(symbol.ds_mod); /* Second weak def */
						}
					} else {
						/* Found the symbol! */
						if (weak_symbol.ds_mod)
							DlModule_Decref(weak_symbol.ds_mod);
						result = (ElfW(Addr))symbol.ds_sym;
						DlModule_Decref(symbol.ds_mod);
						goto done;
					}
				}
			} else {
				symbol.ds_sym = DlModule_ElfGetLocalSymbol(symbol.ds_mod,
				                                           name,
				                                           &hash_elf,
				                                           &hash_gnu);
				if (symbol.ds_sym &&
				    symbol.ds_sym->st_shndx != SHN_UNDEF) {
					if (ELFW(ST_BIND)(symbol.ds_sym->st_info) == STB_WEAK) {
						/* Weak definition. */
						if (!weak_symbol.ds_mod)
							weak_symbol = symbol; /* First weak def */
						else {
							DlModule_Decref(symbol.ds_mod); /* Second weak def */
						}
					} else {
						/* Found the symbol! */
						if (weak_symbol.ds_mod)
							DlModule_Decref(weak_symbol.ds_mod);
						result = symbol.ds_sym->st_value;
						if (ELFW(ST_TYPE)(symbol.ds_sym->st_info) == STT_TLS) {
							void *tlsbase;
							tlsbase = libdl_dltlsaddr(symbol.ds_mod);
							if unlikely(!tlsbase)
								goto err_symbol_mod;
							result += (ElfW(Addr))tlsbase;
						} else {
							if (symbol.ds_sym->st_shndx != SHN_ABS)
								result += symbol.ds_mod->dm_loadaddr;
							if (ELFW(ST_TYPE)(symbol.ds_sym->st_info) == STT_GNU_IFUNC ||
							    ELFW(ST_TYPE)(symbol.ds_sym->st_info) == STT_KOS_IDATA) {
								TRY {
									result = (*(ElfW(Addr)(*)(void))(void *)result)();
								} EXCEPT {
									DlModule_Decref(symbol.ds_mod);
									RETHROW();
								}
							}
						}
						DlModule_Decref(symbol.ds_mod);
						goto done;
					}
				}
			}
			atomic_rwlock_read(&DlModule_GlobalLock);
			next_module = symbol.ds_mod->dm_globals.ln_next;
			while (likely(next_module) && unlikely(!DlModule_TryIncref(next_module)))
				next_module = next_module->dm_globals.ln_next;
			atomic_rwlock_endread(&DlModule_GlobalLock);
			DlModule_Decref(symbol.ds_mod);
			if unlikely(!next_module)
				break;
			symbol.ds_mod = next_module;
			goto again_search_globals_module;
		}
		/* Check if we found a weak symbol at one point! */
		if likely(weak_symbol.ds_mod) {
			if (weak_symbol.ds_mod->dm_ops) {
				result = (ElfW(Addr))weak_symbol.ds_sym;
			} else {
				result = weak_symbol.ds_sym->st_value;
				if (ELFW(ST_TYPE)(weak_symbol.ds_sym->st_info) == STT_TLS) {
					void *tlsbase;
					tlsbase = libdl_dltlsaddr(weak_symbol.ds_mod);
					if unlikely(!tlsbase)
						goto err_weak_symbol_mod;
					result += (ElfW(Addr))tlsbase;
				} else {
					if (weak_symbol.ds_sym->st_shndx != SHN_ABS)
						result += weak_symbol.ds_mod->dm_loadaddr;
					if (ELFW(ST_TYPE)(weak_symbol.ds_sym->st_info) == STT_GNU_IFUNC ||
					    ELFW(ST_TYPE)(weak_symbol.ds_sym->st_info) == STT_KOS_IDATA) {
						TRY {
							result = (*(ElfW(Addr)(*)(void))(void *)result)();
						} EXCEPT {
							DlModule_Decref(weak_symbol.ds_mod);
							RETHROW();
						}
					}
				}
			}
			DlModule_Decref(weak_symbol.ds_mod);
			goto done;
		}
		if unlikely(self == RTLD_NEXT) {
			symbol.ds_mod = libdl_dlgethandle(__builtin_return_address(0), DLGETHANDLE_FNORMAL);
			if unlikely(!symbol.ds_mod)
				goto err_rtld_next_no_base;
			dl_seterrorf("No module loaded after %q contains a symbol %q",
			             symbol.ds_mod->dm_filename, name);
		} else {
			dl_seterrorf("No loaded module contains a symbol %q", name);
		}
	} else if (self == RTLD_NEXT) {
		symbol.ds_mod = libdl_dlgethandle(__builtin_return_address(0), DLGETHANDLE_FNORMAL);
		/* Search modules loaded after `symbol.ds_mod' */
		if unlikely(!symbol.ds_mod)
			goto err_rtld_next_no_base;
		atomic_rwlock_read(&DlModule_GlobalLock);
		goto again_search_globals_next_noref;
	} else {
		if unlikely(self == &dl_rtld_module) {
			result = (ElfW(Addr))dlsym_builtin(name);
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
				error = (*self->dm_ops->df_dlsym)(self, name, (void **)&symbol.ds_sym, NULL);
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
				                                           name,
				                                           &hash_elf,
				                                           &hash_gnu);
				/* Most likely case: The symbol is already apart of the specified module! */
				if likely(symbol.ds_sym &&
				          symbol.ds_sym->st_shndx != SHN_ABS) {
					if (ELFW(ST_BIND)(symbol.ds_sym->st_info) == STB_WEAK) {
						weak_symbol.ds_mod = self;
						weak_symbol.ds_sym = symbol.ds_sym;
					} else {
						result = symbol.ds_sym->st_value;
						if (ELFW(ST_TYPE)(symbol.ds_sym->st_info) == STT_TLS) {
							void *tlsbase;
							tlsbase = libdl_dltlsaddr(self);
							if unlikely(!tlsbase)
								goto err;
							result += (ElfW(Addr))tlsbase;
						} else {
							if (symbol.ds_sym->st_shndx != SHN_ABS)
								result += self->dm_loadaddr;
							if (ELFW(ST_TYPE)(symbol.ds_sym->st_info) == STT_GNU_IFUNC ||
							    ELFW(ST_TYPE)(symbol.ds_sym->st_info) == STT_KOS_IDATA)
								result = (*(ElfW(Addr)(*)(void))(void *)result)();
						}
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
					                                               name,
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
					result = weak_symbol.ds_sym->st_value;
					if (ELFW(ST_TYPE)(weak_symbol.ds_sym->st_info) == STT_TLS) {
						void *tlsbase;
						tlsbase = libdl_dltlsaddr(weak_symbol.ds_mod);
						if unlikely(!tlsbase)
							goto err;
						result += (ElfW(Addr))tlsbase;
					} else {
						if (weak_symbol.ds_sym->st_shndx != SHN_ABS)
							result += weak_symbol.ds_mod->dm_loadaddr;
						if (ELFW(ST_TYPE)(weak_symbol.ds_sym->st_info) == STT_GNU_IFUNC ||
						    ELFW(ST_TYPE)(weak_symbol.ds_sym->st_info) == STT_KOS_IDATA)
							result = (*(ElfW(Addr)(*)(void))(void *)result)();
					}
				}
				goto done;
			}
		}
		/* Missing symbol... */
		dl_seterrorf("Failed to find symbol %q in %q",
		             name, self->dm_filename);
	}
err:
	return NULL;
err_symbol_mod:
	DlModule_Decref(symbol.ds_mod);
	goto err;
err_weak_symbol_mod:
	DlModule_Decref(weak_symbol.ds_mod);
	goto err;
err_rtld_next_no_base:
	dl_seterrorf("Can only use `RTLD_NEXT' from dynamically loaded code");
	goto err;
err_bad_module:
	dl_seterror_badmodule(self);
	goto err;
}




INTERN WUNUSED REF_IF(!(return->dm_flags & RTLD_NODELETE) &&
                      (flags & DLGETHANDLE_FINCREF))
DlModule *DLFCN_CC
libdl_dlgethandle(void const *static_pointer, unsigned int flags) {
	DlModule *result;
	if unlikely(flags & ~(DLGETHANDLE_FINCREF)) {
		dl_seterrorf("Invalid flags %#x passed to `dlgethandle()'", flags);
		goto err;
	}
	atomic_rwlock_read(&DlModule_AllLock);
	DlModule_AllList_FOREACH(result) {
		uint16_t i;
		if ((uintptr_t)static_pointer < result->dm_loadstart)
			continue;
		if ((uintptr_t)static_pointer >= result->dm_loadend)
			continue;
		/* Support for formats other than ELF. */
		if (result->dm_ops) {
			if (!(*result->dm_ops->df_ismapped)(result,
			                                    (uintptr_t)static_pointer -
			                                    result->dm_loadaddr))
				continue;
			goto got_result;
		}
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
	atomic_rwlock_endread(&DlModule_AllLock);
	dl_seterror_no_mod_at_addr(static_pointer);
err:
	return NULL;
got_result:
	/* Found the module! */
	if ((flags & DLGETHANDLE_FINCREF) &&
	    !(result->dm_flags & RTLD_NODELETE))
		DlModule_Incref(result);
	atomic_rwlock_endread(&DlModule_AllLock);
	return result;
}

INTERN WUNUSED REF_IF(!(return->dm_flags & RTLD_NODELETE) &&
                      (flags & DLGETHANDLE_FINCREF))
DlModule *DLFCN_CC
libdl_dlgetmodule(char const *name, unsigned int flags) {
	DlModule *result;
	if (!name) {
		result = libdl_dlgethandle(__builtin_return_address(0), flags);
		if unlikely(!result)
			dl_seterrorf("Can only call `dlgetmodule(NULL)' from dynamically loaded code");
		return result;
	}
	if unlikely(flags & ~(DLGETHANDLE_FINCREF | DLGETHANDLE_FNOCASE)) {
		dl_seterrorf("Invalid flags %#x passed to `dlgetmodule()'", flags);
		goto err;
	}
	atomic_rwlock_read(&DlModule_AllLock);
	DlModule_AllList_FOREACH(result) {
		if (strcmp(result->dm_filename, name) == 0)
			goto got_result;
	}
	DlModule_AllList_FOREACH(result) {
		char *sep = strrchr(result->dm_filename, '/');
		if (!sep)
			continue;
		if (strcmp(sep + 1, name) == 0)
			goto got_result;
	}
	DlModule_AllList_FOREACH(result) {
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
		if (memcmp(sep, name, namelen * sizeof(char)) == 0 &&
		    name[namelen] == '\0')
			goto got_result;
	}
	DlModule_AllList_FOREACH(result) {
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
		if (memcmp(sep, name, namelen * sizeof(char)) == 0 &&
		    name[namelen] == '\0')
			goto got_result;
	}
	if (flags & DLGETHANDLE_FNOCASE) {
		DlModule_AllList_FOREACH(result) {
			if (strcasecmp(result->dm_filename, name) == 0)
				goto got_result;
		}
		DlModule_AllList_FOREACH(result) {
			char *sep = strrchr(result->dm_filename, '/');
			if (!sep)
				continue;
			if (strcasecmp(sep + 1, name) == 0)
				goto got_result;
		}
		DlModule_AllList_FOREACH(result) {
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
		DlModule_AllList_FOREACH(result) {
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
	atomic_rwlock_endread(&DlModule_AllLock);
	dl_seterrorf("Unknown module %q", name);
err:
	return NULL;
got_result:
	if ((flags & DLGETHANDLE_FINCREF) &&
	    !(result->dm_flags & RTLD_NODELETE))
		DlModule_Incref(result);
	atomic_rwlock_endread(&DlModule_AllLock);
	return result;
}


INTERN NONNULL((2)) int DLFCN_CC
libdl_dladdr(void const *address, Dl_info *info) {
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
			DlModule_Decref(mod);
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
done:
	if (!(mod->dm_flags & RTLD_NODELETE))
		DlModule_Decref(mod);
	return 0;
err:
	return -1;
}

INTERN WUNUSED NONNULL((1)) fd_t DLFCN_CC
libdl_dlmodulefd(DlModule *self) {
	if unlikely(!DL_VERIFY_MODULE_HANDLE(self))
		goto err_bad_module;
	return DlModule_GetFd(self);
err_bad_module:
	return dl_seterror_badmodule(self);
}

INTERN WUNUSED NONNULL((1)) char const *DLFCN_CC
libdl_dlmodulename(DlModule *self) {
	if unlikely(!DL_VERIFY_MODULE_HANDLE(self))
		goto err_bad_module;
	return self->dm_filename;
err_bad_module:
	dl_seterror_badmodule(self);
	return NULL;
}

INTERN WUNUSED NONNULL((1)) void *DLFCN_CC
libdl_dlmodulebase(DlModule *self) {
	if unlikely(!DL_VERIFY_MODULE_HANDLE(self))
		goto err_bad_module;
	return (void *)self->dm_loadaddr;
err_bad_module:
	dl_seterror_badmodule(self);
	return NULL;
}


INTERN NONNULL((1)) void CC
DlSection_Destroy(DlSection *__restrict self) {
	DlModule *mod;
	/* Unmap section data. */
	if ((self->ds_flags & DLSECTION_FLAG_OWNED) && (self->ds_data != (void *)-1))
		sys_munmap(self->ds_data, self->ds_size);
	/* Unmap decompressed section data. */
	if (self->ds_cdata != (void *)-1 && self->ds_cdata != self->ds_data)
		sys_munmap(self->ds_cdata, self->ds_csize);
again:
	atomic_rwlock_write(&self->ds_module_lock);
	mod = self->ds_module;
	if (mod) {
		if (!atomic_rwlock_trywrite(&mod->dm_sections_lock)) {
			bool hasref;
			hasref = DlModule_TryIncref(mod);
			atomic_rwlock_endwrite(&self->ds_module_lock);
			if (hasref) {
				atomic_rwlock_write(&mod->dm_sections_lock);
				atomic_rwlock_endwrite(&mod->dm_sections_lock);
				DlModule_Decref(mod);
			}
			goto again;
		}
		assert(mod->dm_sections);
		assert(self->ds_index < mod->dm_shnum);
		assert(mod->dm_sections[self->ds_index] == self);
		mod->dm_sections[self->ds_index] = NULL;
		atomic_rwlock_endwrite(&mod->dm_sections_lock);
		self->ds_module = NULL;
	}
	atomic_rwlock_endwrite(&self->ds_module_lock);
	/* Drop the reference stored in `ds_module' */
	if (mod && !(self->ds_flags & DLSECTION_FLAG_OWNED))
		DlModule_Decref(mod);
	free(self);
}

INTERN WUNUSED REF DlSection *DLFCN_CC
libdl_dllocksection(DlModule *self,
                    char const *__restrict name,
                    unsigned int flags) {
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
		atomic_rwlock_read(&self->dm_sections_lock);
		if (!self->dm_sections) {
			DlSection **sec_vec;
			/* Must allocate the initial sections vector. */
			atomic_rwlock_endread(&self->dm_sections_lock);
			sec_vec = (DlSection **)calloc(self->dm_shnum,
			                               sizeof(DlSection *));
			if unlikely(!sec_vec)
				goto err_nomem;
			atomic_rwlock_write(&self->dm_sections_lock);
			COMPILER_READ_BARRIER();
			if likely(!self->dm_sections) {
				self->dm_sections = sec_vec;
			} else {
				atomic_rwlock_endwrite(&self->dm_sections_lock);
				free(sec_vec);
				COMPILER_READ_BARRIER();
				goto again_lock_sections;
			}
			atomic_rwlock_downgrade(&self->dm_sections_lock);
		}
again_read_section:
		result = self->dm_sections[index];
		if (!result || !DlSection_TryIncref(result)) {
			int error;
			/* Must allocate a descriptor for this section. */
			atomic_rwlock_endread(&self->dm_sections_lock);
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
				/* Section is already allocated in member. */
				result->ds_data  = info.dsi_addr;
				result->ds_flags = DLSECTION_FLAG_NORMAL;
				DlModule_Incref(self); /* Reference stored in `result->ds_module' */
			} else {
				result->ds_data  = (void *)-1;
				result->ds_flags = DLSECTION_FLAG_OWNED;
			}
			atomic_rwlock_write(&self->dm_sections_lock);
			if likely(!self->dm_sections[index]) {
				self->dm_sections[index] = result;
			} else {
				/* Race condition: The section was already allocated in a different thread. */
				atomic_rwlock_endwrite(&self->dm_sections_lock);
				free(result);
				atomic_rwlock_read(&self->dm_sections_lock);
				goto again_read_section;
			}
			atomic_rwlock_downgrade(&self->dm_sections_lock);
		} else {
			info.dsi_size = 0;
		}
		atomic_rwlock_endread(&self->dm_sections_lock);
		if (result->ds_data == (void *)-1 && !(flags & DLLOCKSECTION_FNODATA) &&
		    (result->ds_flags & DLSECTION_FLAG_OWNED)) {
			void *base;
			if (info.dsi_size == 0) {
				int error;
				error = (*self->dm_ops->df_dlsectinfo)(self, index, &info);
				if unlikely(error != 0)
					goto err;
			}

			/* Must load section data. */
			base = sys_mmap(NULL,
			                info.dsi_size,
			                PROT_READ | PROT_WRITE,
			                MAP_PRIVATE | MAP_FILE,
			                self->dm_file,
			                info.dsi_offset);
			if (E_ISERR(base)) {
				DlSection_Decref(result);
				if (flags & DLLOCKSECTION_FINDEX) {
					dl_seterrorf("%q: Failed to map section #%Iu into memory",
					                self->dm_filename, (uintptr_t)name);
				} else {
					dl_seterrorf("%q: Failed to map section %q into memory",
					                self->dm_filename, name);
				}
				goto err;
			}
			if unlikely(!ATOMIC_CMPXCH(result->ds_data, (void *)-1, base))
				sys_munmap(base, info.dsi_size);
		}
	} else {
		size_t index;
		ElfW(Shdr) *sect;
		if (flags & DLLOCKSECTION_FINDEX) {
			sect = DlModule_ElfGetShdrs(self);
			if unlikely(!sect)
				goto err;
			if unlikely((uintptr_t)name >= self->dm_shnum) {
				dl_seterror_nosect_index(self, (size_t)name);
				goto err;
			}
			sect += (uintptr_t)name;
		} else {
			sect = DlModule_ElfGetSection(self, name);
			if unlikely(!sect)
				goto err;
		}
		assert(sect >= self->dm_elf.de_shdr);
		assert(sect < self->dm_elf.de_shdr + self->dm_shnum);
		index = (size_t)(sect - self->dm_elf.de_shdr);
again_lock_elf_sections:
		atomic_rwlock_read(&self->dm_sections_lock);
		if (!self->dm_sections) {
			DlSection **sec_vec;
			/* Must allocate the initial sections vector. */
			atomic_rwlock_endread(&self->dm_sections_lock);
			sec_vec = (DlSection **)calloc(self->dm_shnum,
			                               sizeof(DlSection *));
			if unlikely(!sec_vec)
				goto err_nomem;
			atomic_rwlock_write(&self->dm_sections_lock);
			COMPILER_READ_BARRIER();
			if likely(!self->dm_sections) {
				self->dm_sections = sec_vec;
			} else {
				atomic_rwlock_endwrite(&self->dm_sections_lock);
				free(sec_vec);
				COMPILER_READ_BARRIER();
				goto again_lock_elf_sections;
			}
			atomic_rwlock_downgrade(&self->dm_sections_lock);
		}
again_read_elf_section:
		result = self->dm_sections[index];
		if (!result || !DlSection_TryIncref(result)) {
			/* Must allocate a descriptor for this section. */
			atomic_rwlock_endread(&self->dm_sections_lock);
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
				/* Section is already allocated in member. */
				result->ds_data  = (void *)(self->dm_loadaddr + sect->sh_addr);
				result->ds_flags = DLSECTION_FLAG_NORMAL;
				DlModule_Incref(self); /* Reference stored in `result->ds_module' */
			} else {
				result->ds_data  = (void *)-1;
				result->ds_flags = DLSECTION_FLAG_OWNED;
			}
			atomic_rwlock_write(&self->dm_sections_lock);
			if likely(!self->dm_sections[index]) {
				self->dm_sections[index] = result;
			} else {
				/* Race condition: The section was already allocated in a different thread. */
				atomic_rwlock_endwrite(&self->dm_sections_lock);
				free(result);
				atomic_rwlock_read(&self->dm_sections_lock);
				goto again_read_elf_section;
			}
			atomic_rwlock_downgrade(&self->dm_sections_lock);
		}
		atomic_rwlock_endread(&self->dm_sections_lock);
		if (result->ds_data == (void *)-1 && !(flags & DLLOCKSECTION_FNODATA) &&
		    (result->ds_flags & DLSECTION_FLAG_OWNED)) {
			void *base;
			/* Must load section data. */
			base = sys_mmap(NULL,
			                sect->sh_size,
			                PROT_READ | PROT_WRITE,
			                MAP_PRIVATE | MAP_FILE,
			                self->dm_file,
			                sect->sh_offset);
			if (E_ISERR(base)) {
				DlSection_Decref(result);
				if (flags & DLLOCKSECTION_FINDEX) {
					dl_seterrorf("%q: Failed to map section #%Iu into memory",
					                self->dm_filename, (uintptr_t)name);
				} else {
					dl_seterrorf("%q: Failed to map section %q into memory",
					                self->dm_filename, name);
				}
				goto err;
			}
			if unlikely(!ATOMIC_CMPXCH(result->ds_data, (void *)-1, base))
				sys_munmap(base, sect->sh_size);
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
	dl_seterrorf("Invalid flags %#x passed to `dllocksection()'", flags);
	goto err;
}


INTERN NONNULL((1)) int DLFCN_CC
libdl_dlunlocksection(REF DlSection *sect) {
	if unlikely(!DL_VERIFY_SECTION_HANDLE(sect))
		goto err_bad_section;
	{
		refcnt_t refcnt;
		do {
			refcnt = ATOMIC_READ(sect->ds_refcnt);
			assert(refcnt != 0);
			if (refcnt == 1)
				goto set_dangling_section;
		} while (!ATOMIC_CMPXCH_WEAK(sect->ds_refcnt, refcnt, refcnt - 1));
		return 0;
	}
	{
		REF DlModule *mod;
set_dangling_section:
		atomic_rwlock_read(&sect->ds_module_lock);
		mod = sect->ds_module;
		if (mod && !DlModule_TryIncref(mod))
			mod = NULL;
		atomic_rwlock_endread(&sect->ds_module_lock);
		if (mod) {
			atomic_rwlock_write(&mod->dm_sections_lock);
			/* Insert the section into the set of dangling sections of this module. */
			if likely(sect->ds_dangling == (REF DlSection *)-1) {
				sect->ds_dangling         = mod->dm_sections_dangling;
				mod->dm_sections_dangling = sect;
				atomic_rwlock_endwrite(&mod->dm_sections_lock);
				DlModule_Decref(mod);
				return 0;
			}
			atomic_rwlock_endwrite(&mod->dm_sections_lock);
			DlModule_Decref(mod);
		}
	}
	DlSection_Decref(sect);
	return 0;
err_bad_section:
	return dl_seterror_badsection(sect);
}

INTERN NONNULL((1)) char const *DLFCN_CC
libdl_dlsectionname(DlSection *sect) {
	char const *result;
	REF DlModule *mod;
	if unlikely(!DL_VERIFY_SECTION_HANDLE(sect))
		goto err_bad_section;
	atomic_rwlock_read(&sect->ds_module_lock);
	mod = sect->ds_module;
	if (!mod || !DlModule_TryIncref(mod)) {
		atomic_rwlock_endread(&sect->ds_module_lock);
err_mod_unloaded:
		dl_seterrorf("Module associated with section was unloaded");
		goto err;
	}
	atomic_rwlock_endread(&sect->ds_module_lock);
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
			if unlikely(!mod->dm_ops->df_dlsectname)
				result = "?";
			else {
				result = (*mod->dm_ops->df_dlsectname)(mod, sect->ds_index);
			}
		} else {
			assert(mod->dm_elf.de_shdr != NULL);
			assert(mod->dm_elf.de_shstrtab != NULL);
			result  = mod->dm_elf.de_shstrtab;
			result += mod->dm_elf.de_shdr[sect->ds_index].sh_name;
		}
	}
	if unlikely(!DlModule_Decref(mod))
		goto err_mod_unloaded;
	return result;
err_bad_section:
	dl_seterror_badsection(sect);
err:
	return NULL;
}

INTERN NONNULL((1)) size_t DLFCN_CC
libdl_dlsectionindex(DlSection *sect) {
	size_t result;
	if unlikely(!DL_VERIFY_SECTION_HANDLE(sect))
		goto err_bad_section;
	result = sect->ds_index;
	return result;
err_bad_section:
	dl_seterror_badsection(sect);
	return (size_t)-1;
}


INTERN NONNULL((1)) DlModule *DLFCN_CC
libdl_dlsectionmodule(DlSection *sect, unsigned int flags) {
	DlModule *mod;
	if unlikely(!DL_VERIFY_SECTION_HANDLE(sect))
		goto err_bad_section;
	if unlikely(flags & ~(DLGETHANDLE_FINCREF)) {
		dl_seterrorf("Invalid flags %#x passed to `dlsectionmodule()'", flags);
		goto err;
	}
	atomic_rwlock_read(&sect->ds_module_lock);
	mod = sect->ds_module;
	if (!mod || ((flags & DLGETHANDLE_FINCREF)
	             ? !DlModule_TryIncref(mod)
	             : !ATOMIC_READ(mod->dm_refcnt))) {
		atomic_rwlock_endread(&sect->ds_module_lock);
		dl_seterrorf("Module associated with section was unloaded");
		goto err;
	}
	atomic_rwlock_endread(&sect->ds_module_lock);
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


LOCAL bool CC init_zlib(void) {
	if (!pdyn_zlib_reader_init) {
		REF DlModule *libzlib;
		libzlib = libdl_dlopen(LIBZLIB_LIBRARY_NAME,
		                       RTLD_LOCAL);
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
		memset((byte_t *)dst + (size_t)error, 0, dst_size - error);
	return ZLIB_ERROR_OK;
}


LOCAL WUNUSED NONNULL((1, 2, 4)) void *CC
inflate_compressed_section(DlSection *sect,
                           void const *section_data,
                           size_t section_size,
                           size_t *psection_csize) {
	ElfW(Chdr) *chdr;
	void *result;
	chdr = (ElfW(Chdr) *)section_data;
	/* Verify the compressed-section header. */
	if unlikely(section_size < sizeof(*chdr))
		goto err_bad_section_size;
	if unlikely(chdr->ch_type != ELFCOMPRESS_ZLIB)
		goto err_wrong_chdr_type;
	/* Allocate memory for the compressed section. */
	*psection_csize = ATOMIC_READ(chdr->ch_size);
	result = sys_mmap(NULL, *psection_csize,
	                  PROT_READ | PROT_WRITE,
	                  MAP_PRIVATE | MAP_ANON,
	                  -1, 0);
	if unlikely(E_ISERR(result))
		goto err_mmap_failed;
	/* Lazily load libzlib.so */
	if unlikely(!init_zlib())
		goto err_munmap;
	{
		unsigned int inflate_error;
		/* Decompress section data. */
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
	dl_seterrorf("Failed to allocate decompressed buffer for compressed section %s:%s",
	             libdl_dlmodulename(libdl_dlsectionmodule(sect, 0)),
	             libdl_dlsectionname(sect));
	goto err;
err_wrong_chdr_type:
	dl_seterrorf("Compressed section %s:%s uses an unknown compression scheme %u",
	             libdl_dlmodulename(libdl_dlsectionmodule(sect, 0)),
	             libdl_dlsectionname(sect),
	             (unsigned int)chdr->ch_type);
	goto err;
err_bad_section_size:
	dl_seterrorf("Compressed section %s:%s is too small to be compressed",
	             libdl_dlmodulename(libdl_dlsectionmodule(sect, 0)),
	             libdl_dlsectionname(sect));
	goto err;
err_munmap:
	sys_munmap(result, *psection_csize);
err:
	return (void *)-1;
}


INTERN WUNUSED NONNULL((1)) void *DLFCN_CC
libdl_dlinflatesection(DlSection *sect, size_t *psize) {
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
			ATOMIC_STORE(sect->ds_csize, csize); /* This must be written first! */
			if unlikely(!ATOMIC_CMPXCH(sect->ds_cdata, (void *)-1, cdata)) {
				/* Race condition: Some other thread also did the inflate,
				 * and now we've got the inflated data twice. - Fix this by
				 * simply deleting our duplicate and using the version that's
				 * already stored in the section descriptor. */
				sys_munmap(cdata, csize);
			}
		}
	}
	if (psize)
		*psize = sect->ds_csize;
	return sect->ds_cdata;
err_no_section_data:
	dl_seterrorf("Section data not loaded for %s:%s",
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
DlModule_InvokeDlCacheFunctions(DlModule *__restrict self) {
	int result = 0;
	DlSection *sect;
	sect = libdl_dllocksection(self, ".dl_caches",
	                           DLLOCKSECTION_FNORMAL);
	if unlikely(!sect)
		goto done;
	if likely(!(sect->ds_size & (sizeof(void *) - 1))) {
		size_t i;
		typedef int (*cache_func_t)(void);
		for (i = 0; i < sect->ds_size; i += sizeof(void *)) {
			cache_func_t func;
			func = (cache_func_t)(void *)(self->dm_loadaddr +
			                              *(uintptr_t *)((byte_t *)sect->ds_data + i));
			if ((*func)())
				result = 1;
		}
	}
	DlSection_Decref(sect);
done:
	return result;
}

INTERN int DLFCN_CC libdl_dlclearcaches(void) {
	int result = 0;
	/* TODO: Guard against recursive calls:
	 *  - Within the same thread:
	 *    - Immediately return `0'
	 *  - From another thread:
	 *    - Wait for the first thread to finish, then mirror
	 *      its return value and don't re-execute this function.
	 */

	/* Try to execute function pointers from `.dl_caches' sections. */
	{
		DlModule *module_iter;
again_clear_modules:
		atomic_rwlock_read(&DlModule_AllLock);
		DlModule_AllList_FOREACH(module_iter) {
			refcnt_t refcnt;
			if (!DlModule_TryIncref(module_iter))
				continue;
			atomic_rwlock_endread(&DlModule_AllLock);
			if (DlModule_InvokeDlCacheFunctions(module_iter))
				result = 1;
again_try_descref_module_iter:
			refcnt = ATOMIC_READ(module_iter->dm_refcnt);
			if (refcnt <= 1) {
				DlModule_Decref(module_iter);
				goto again_clear_modules;
			}
			atomic_rwlock_read(&DlModule_AllLock);
			if (!ATOMIC_CMPXCH_WEAK(module_iter->dm_refcnt, refcnt, refcnt - 1)) {
				atomic_rwlock_endread(&DlModule_AllLock);
				goto again_try_descref_module_iter;
			}
		}
		atomic_rwlock_endread(&DlModule_AllLock);
	}
	{
		DlModule *module_iter;
		/* Delete dangling sections. */
again_lock_global:
		atomic_rwlock_read(&DlModule_AllLock);
		DlModule_AllList_FOREACH(module_iter) {
			REF DlSection *temp;
			if (!ATOMIC_READ(module_iter->dm_sections_dangling))
				continue;
			if (!atomic_rwlock_trywrite(&module_iter->dm_sections_lock)) {
				bool hasref;
				hasref = DlModule_TryIncref(module_iter);
				atomic_rwlock_endread(&DlModule_AllLock);
				if (hasref) {
					atomic_rwlock_write(&module_iter->dm_sections_lock);
					atomic_rwlock_endwrite(&module_iter->dm_sections_lock);
					DlModule_Decref(module_iter);
				}
				goto again_lock_global;
			}
			COMPILER_READ_BARRIER();
			temp = module_iter->dm_sections_dangling;
			if likely(temp) {
				/* Steal a reference to this section. */
				module_iter->dm_sections_dangling = temp->ds_dangling;
				temp->ds_dangling                 = (REF DlSection *)-1;
				atomic_rwlock_endwrite(&module_iter->dm_sections_lock);
				atomic_rwlock_endread(&DlModule_AllLock);
				/* Drop this reference. */
				DlSection_Decref(temp);
				result = 1;
				goto again_lock_global;
			}
			atomic_rwlock_endwrite(&module_iter->dm_sections_lock);
		}
		atomic_rwlock_endread(&DlModule_AllLock);
	}
	/* Also trim malloc memory from our heap implementation. */
	if (malloc_trim(0))
		result = 1;
	return result;
}


PRIVATE void DLFCN_CC
DlModule_RunAllModuleFinalizers(void) {
	DlModule *mod;
again:
	atomic_rwlock_read(&DlModule_AllLock);
	DlModule_AllList_FOREACH(mod) {
		size_t i, fini_array_size;
		uintptr_t fini_func;
		uintptr_t *fini_array_base;
		/* Skip finalizers if the module was never
		 * initialized or has already been finalized. */
		if (ATOMIC_FETCHOR(mod->dm_flags, (RTLD_NOINIT /*| RTLD_NODELETE*/)) & RTLD_NOINIT)
			continue;
		if unlikely(!DlModule_TryIncref(mod))
			continue;
		atomic_rwlock_endread(&DlModule_AllLock);
		/* Invoke dynamically regsitered module finalizers (s.a. `__cxa_atexit()') */
		if (mod->dm_finalize)
			dlmodule_finalizers_run(mod->dm_finalize);
		/* TODO: Support for formats other than ELF. */
		if (mod->dm_ops) {
			if (mod->dm_ops->df_run_finalizers) {
				TRY {
					(*mod->dm_ops->df_run_finalizers)(mod);
				} EXCEPT {
					DlModule_Decref(mod);
					RETHROW();
				}
			}
			goto decref_module_and_continue;
		}
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
		TRY {
			while (fini_array_size--)
				(*(void (*)(void))(fini_array_base[fini_array_size] /* + self->dm_loadaddr*/))();
			/* Service a fini function, if one was specified. */
			if (fini_func)
				(*(void (*)(void))(fini_func + mod->dm_loadaddr))();
		} EXCEPT {
			DlModule_Decref(mod);
			RETHROW();
		}
decref_module_and_continue:
		DlModule_Decref(mod);
		goto again;
	}
	atomic_rwlock_endread(&DlModule_AllLock);
}



INTERN void *DLFCN_CC
libdl_dlauxctrl(DlModule *self, unsigned int cmd, ...) {
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

	default:
		break;
	}
	if (!self)
		self = DlModule_GlobalList;
	else if unlikely(!DL_VERIFY_MODULE_HANDLE(self)) {
		dl_seterror_badmodule(self);
		goto err;
	}
	switch (cmd) {

	case DLAUXCTRL_ADD_FINALIZER: {
		struct dlmodule_finalizers *flz;
		void (LIBDL_CC *func)(void *);
		void *arg;
		func = va_arg(args, void (LIBDL_CC *)(void *));
		arg  = va_arg(args, void *);
again_add_finalizer_read_list:
		flz = ATOMIC_READ(self->dm_finalize);
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
			if (!ATOMIC_CMPXCH(self->dm_finalize, NULL, flz)) {
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
			dl_seterrorf("Invalid `sizeof_dlmodule_format': %Iu; current version is %Iu",
			             sizeof_dlmodule_format, sizeof(struct dlmodule_format));
			goto err;
		}
		if (sizeof_dlcore_ops != sizeof(struct dlcore_ops)) {
			dl_seterrorf("Invalid `sizeof_dlcore_ops': %Iu; current version is %Iu",
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
		ATOMIC_OR(extmod->dm_flags, RTLD_NODELETE);
		/* Fill in the coreops V-table pointer. */
		extension->df_core = dl_getcoreops();
		/* Register the extension. */
		COMPILER_BARRIER();
		do {
			next = ATOMIC_READ(dl_extensions);
			extension->df_next = next;
			COMPILER_WRITE_BARRIER();
		} while (!ATOMIC_CMPXCH_WEAK(dl_extensions, next, extension));
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

	case DLAUXCTRL_ELF_GET_PHDR: {
		size_t *pcount;
		/* Check that this is an ELF module. */
		if unlikely(self->dm_ops)
			goto err_notelf;
		pcount = va_arg(args, size_t *);
		result = self->dm_elf.de_phdr;
		if (pcount)
			*pcount = (size_t)self->dm_elf.de_phnum;
	}	break;

	case DLAUXCTRL_ELF_GET_SHDR: {
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

	default:
		dl_seterrorf("Invalid auxctrl command %#x", cmd);
		goto err;
	}
done:
	va_end(args);
	return result;
err_notelf:
	dl_seterror_notelf(self);
	goto err;
err_nomem:
	dl_seterror_nomem();
err:
	result = NULL;
	goto done;
}

PRIVATE int CC
DlModule_IteratePhdr(DlModule *__restrict self,
                     __dl_iterator_callback callback, void *arg) {
	int result;
	struct dl_phdr_info info;
	info.dlpi_addr      = self->dm_loadaddr;
	info.dlpi_name      = self->dm_filename;
	info.dlpi_adds      = 0; /* ??? */
	info.dlpi_subs      = 0; /* ??? */
	info.dlpi_tls_modid = (size_t)(uintptr_t)self;
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
		info.dlpi_phnum = COMPILER_LENOF(ph);
		result = (*self->dm_ops->df_lsphdrs)(self, &info, callback, arg);
	}
	return result;
}


/* Enumerate all loaded modules, as well as information about them.
 * Enumeration stops when `*CALLBACK' returns a non-zero value, which
 * will then also be returned by this function. Otherwise, `0' will
 * be returned after all modules have been enumerated. */
INTERN int DLFCN_CC
libdl_iterate_phdr(__dl_iterator_callback callback, void *arg) {
	int result = 0;
	REF DlModule *current, *next;
	atomic_rwlock_read(&DlModule_AllLock);
	current = DlModule_AllList;
	while (current) {
		if (!tryincref(current)) {
			current = current->dm_modules_next;
			continue;
		}
		atomic_rwlock_endread(&DlModule_AllLock);
got_current:
		TRY {
			result = DlModule_IteratePhdr(current, callback, arg);
		} EXCEPT {
			decref_unlikely(current);
			RETHROW();
		}
		if (result != 0) {
			decref_unlikely(current);
			break;
		}
		/* Try to lock the next module. */
		atomic_rwlock_read(&DlModule_AllLock);
		next = current->dm_modules_next;
		while (next && !tryincref(next))
			next = next->dm_modules_next;
		atomic_rwlock_endread(&DlModule_AllLock);
		/* Continue enumerating the next module. */
		decref_unlikely(current);
		if (!next)
			break;
		current = next;
		goto got_current;
	}
	atomic_rwlock_endread(&DlModule_AllLock);
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




/* List of builtin ELF functions.
 * NOTE: After changing this List's contents, you must re-run the following command:
 * $ deemon -F kos/src/libdl/builtin.c
 */
#define ELF_BUILTIN_FUNCTIONS                                             \
	{                                                                     \
		"dlopen"          : "result = (void *)&libdl_dlopen;",            \
		"dlfopen"         : "result = (void *)&libdl_dlfopen;",           \
		"dlclose"         : "result = (void *)&libdl_dlclose;",           \
		"dlexceptaware"   : "result = (void *)&libdl_dlexceptaware;",     \
		"dlsym"           : "result = (void *)&libdl_dlsym;",             \
		"dlerror"         : "result = (void *)&libdl_dlerror;",           \
		"dlgethandle"     : "result = (void *)&libdl_dlgethandle;",       \
		"dlgetmodule"     : "result = (void *)&libdl_dlgetmodule;",       \
		"dladdr"          : "result = (void *)&libdl_dladdr;",            \
		"dlmodulefd"      : "result = (void *)&libdl_dlmodulefd;",        \
		"dlmodulename"    : "result = (void *)&libdl_dlmodulename;",      \
		"dlmodulebase"    : "result = (void *)&libdl_dlmodulebase;",      \
		"dllocksection"   : "result = (void *)&libdl_dllocksection;",     \
		"dlunlocksection" : "result = (void *)&libdl_dlunlocksection;",   \
		"dlsectionname"   : "result = (void *)&libdl_dlsectionname;",     \
		"dlsectionindex"  : "result = (void *)&libdl_dlsectionindex;",    \
		"dlsectionmodule" : "result = (void *)&libdl_dlsectionmodule;",   \
		"dlinflatesection" : "result = (void *)&libdl_dlinflatesection;", \
		"dlclearcaches"   : "result = (void *)&libdl_dlclearcaches;",     \
		"___tls_get_addr" : {                                             \
			"result = (void *)&libdl____tls_get_addr;",                   \
			"defined(__i386__) && !defined(__x86_64__)"                   \
		},                                                                \
		"__tls_get_addr"  : "result = (void *)&libdl___tls_get_addr;",    \
		"dltlsallocseg"   : "result = (void *)&libdl_dltlsallocseg;",     \
		"dltlsfreeseg"    : "result = (void *)&libdl_dltlsfreeseg;",      \
		"dltlsalloc"      : "result = (void *)&libdl_dltlsalloc;",        \
		"dltlsfree"       : "result = (void *)&libdl_dltlsfree;",         \
		"dltlsaddr"       : "result = (void *)&libdl_dltlsaddr;",         \
		"dltlsaddr2"      : "result = (void *)&libdl_dltlsaddr2;",        \
		"dlauxctrl"       : "result = (void *)&libdl_dlauxctrl;",         \
		"dl_iterate_phdr" : "result = (void *)&libdl_iterate_phdr;",      \
		"__peb"           : "result = (void *)root_peb;",                 \
		"environ"         : "result = (void *)&root_peb->pp_envp;",       \
		"_environ"        : "result = (void *)&root_peb->pp_envp;",       \
		"__environ"       : "result = (void *)&root_peb->pp_envp;",       \
		"__argc"          : "result = (void *)&root_peb->pp_argc;",       \
		"__argv"          : "result = (void *)&root_peb->pp_argv;",       \
		"_pgmptr"         : "result = (void *)&root_peb->pp_argv[0];",    \
		"__progname_full" : "result = (void *)&root_peb->pp_argv[0];",    \
		"program_invocation_name" : "result = (void *)&root_peb->pp_argv[0];", \
		"__progname"      : "result = (void *)dlget_p_program_invocation_short_name();", \
		"program_invocation_short_name" : "result = (void *)dlget_p_program_invocation_short_name();", \
	}



PRIVATE char *dl_program_invocation_short_name = NULL;
PRIVATE WUNUSED char **FCALL dlget_p_program_invocation_short_name(void) {
	if (!dl_program_invocation_short_name) {
		char *progname = root_peb->pp_argv
		                 ? root_peb->pp_argv[0]
		                 : NULL;
		if (progname) {
			char *end;
			end = strrchr(progname, '/');
			if (end)
				progname = end + 1;
		}
		ATOMIC_CMPXCH(dl_program_invocation_short_name,
		              NULL, progname);
	}
	return &dl_program_invocation_short_name;
}



/* XXX: The function `dlsym_builtin()' is extremely large (3.41K bytes)!
 *      Instead of implementing it in C, we should use assembly
 *      to make use of `.wordrel' for encoding function pointers! */

/* Return the address of a builtin function (e.g. `dlopen()') */
INTERN ATTR_PURE WUNUSED NONNULL((1)) void *FCALL
dlsym_builtin(char const *__restrict name) {
	void *result = NULL;
/*[[[deemon
import * from ...misc.libgen.stringswitch;
stringSwitch("name",
	for (local name, mapping: ELF_BUILTIN_FUNCTIONS)
		(name + "\0", mapping));
]]]*/
	if (name[0] == '_') {
		if (name[1] == '_') {
#if defined(__i386__) && !defined(__x86_64__)
			if (name[2] == '_') {
				if (name[3] == 't' && name[4] == 'l' && name[5] == 's' &&
				    name[6] == '_' && name[7] == 'g' && name[8] == 'e' &&
				    name[9] == 't' && name[10] == '_' && name[11] == 'a' &&
				    name[12] == 'd' && name[13] == 'd' && name[14] == 'r' &&
				    name[15] == '\0') {
					/* case "___tls_get_addr": ... */
					result = (void *)&libdl____tls_get_addr;
				}
			} else
#endif /* defined(__i386__) && !defined(__x86_64__) */
			if (name[2] == 'a') {
				if (name[3] == 'r') {
					if (name[4] == 'g') {
						if (name[5] == 'c') {
							if (name[6] == '\0') {
								/* case "__argc": ... */
								result = (void *)&root_peb->pp_argc;
							}
						} else if (name[5] == 'v') {
							if (name[6] == '\0') {
								/* case "__argv": ... */
								result = (void *)&root_peb->pp_argv;
							}
						}
					}
				}
			} else if (name[2] == 'e') {
				if (name[3] == 'n' && name[4] == 'v' && name[5] == 'i' &&
				    name[6] == 'r' && name[7] == 'o' && name[8] == 'n' &&
				    name[9] == '\0') {
					/* case "__environ": ... */
					result = (void *)&root_peb->pp_envp;
				}
			} else if (name[2] == 'p') {
				if (name[3] == 'e') {
					if (name[4] == 'b' && name[5] == '\0') {
						/* case "__peb": ... */
						result = (void *)root_peb;
					}
				} else if (name[3] == 'r') {
					if (name[4] == 'o') {
						if (name[5] == 'g') {
							if (name[6] == 'n') {
								if (name[7] == 'a') {
									if (name[8] == 'm') {
										if (name[9] == 'e') {
											if (name[10] == '\0') {
												/* case "__progname": ... */
												result = (void *)dlget_p_program_invocation_short_name();
											} else if (name[10] == '_') {
												if (name[11] == 'f' && name[12] == 'u' && name[13] == 'l' &&
												    name[14] == 'l' && name[15] == '\0') {
													/* case "__progname_full": ... */
													result = (void *)&root_peb->pp_argv[0];
												}
											}
										}
									}
								}
							}
						}
					}
				}
			} else if (name[2] == 't') {
				if (name[3] == 'l' && name[4] == 's' && name[5] == '_' &&
				    name[6] == 'g' && name[7] == 'e' && name[8] == 't' &&
				    name[9] == '_' && name[10] == 'a' && name[11] == 'd' &&
				    name[12] == 'd' && name[13] == 'r' && name[14] == '\0') {
					/* case "__tls_get_addr": ... */
					result = (void *)&libdl___tls_get_addr;
				}
			}
		} else if (name[1] == 'e') {
			if (name[2] == 'n' && name[3] == 'v' && name[4] == 'i' &&
			    name[5] == 'r' && name[6] == 'o' && name[7] == 'n' &&
			    name[8] == '\0') {
				/* case "_environ": ... */
				result = (void *)&root_peb->pp_envp;
			}
		} else if (name[1] == 'p') {
			if (name[2] == 'g' && name[3] == 'm' && name[4] == 'p' &&
			    name[5] == 't' && name[6] == 'r' && name[7] == '\0') {
				/* case "_pgmptr": ... */
				result = (void *)&root_peb->pp_argv[0];
			}
		}
	} else if (name[0] == 'd') {
		if (name[1] == 'l') {
			switch (name[2]) {

			case '_':
				if (name[3] == 'i' && name[4] == 't' && name[5] == 'e' &&
				    name[6] == 'r' && name[7] == 'a' && name[8] == 't' &&
				    name[9] == 'e' && name[10] == '_' && name[11] == 'p' &&
				    name[12] == 'h' && name[13] == 'd' && name[14] == 'r' &&
				    name[15] == '\0') {
					/* case "dl_iterate_phdr": ... */
					result = (void *)&libdl_iterate_phdr;
				}
				break;

			case 'a':
				if (name[3] == 'd') {
					if (name[4] == 'd' && name[5] == 'r' && name[6] == '\0') {
						/* case "dladdr": ... */
						result = (void *)&libdl_dladdr;
					}
				} else if (name[3] == 'u') {
					if (name[4] == 'x' && name[5] == 'c' && name[6] == 't' &&
					    name[7] == 'r' && name[8] == 'l' && name[9] == '\0') {
						/* case "dlauxctrl": ... */
						result = (void *)&libdl_dlauxctrl;
					}
				}
				break;

			case 'c':
				if (name[3] == 'l') {
					if (name[4] == 'e') {
						if (name[5] == 'a' && name[6] == 'r' && name[7] == 'c' &&
						    name[8] == 'a' && name[9] == 'c' && name[10] == 'h' &&
						    name[11] == 'e' && name[12] == 's' && name[13] == '\0') {
							/* case "dlclearcaches": ... */
							result = (void *)&libdl_dlclearcaches;
						}
					} else if (name[4] == 'o') {
						if (name[5] == 's' && name[6] == 'e' && name[7] == '\0') {
							/* case "dlclose": ... */
							result = (void *)&libdl_dlclose;
						}
					}
				}
				break;

			case 'e':
				if (name[3] == 'r') {
					if (name[4] == 'r' && name[5] == 'o' && name[6] == 'r' &&
					    name[7] == '\0') {
						/* case "dlerror": ... */
						result = (void *)&libdl_dlerror;
					}
				} else if (name[3] == 'x') {
					if (name[4] == 'c' && name[5] == 'e' && name[6] == 'p' &&
					    name[7] == 't' && name[8] == 'a' && name[9] == 'w' &&
					    name[10] == 'a' && name[11] == 'r' && name[12] == 'e' &&
					    name[13] == '\0') {
						/* case "dlexceptaware": ... */
						result = (void *)&libdl_dlexceptaware;
					}
				}
				break;

			case 'f':
				if (name[3] == 'o' && name[4] == 'p' && name[5] == 'e' &&
				    name[6] == 'n' && name[7] == '\0') {
					/* case "dlfopen": ... */
					result = (void *)&libdl_dlfopen;
				}
				break;

			case 'g':
				if (name[3] == 'e') {
					if (name[4] == 't') {
						if (name[5] == 'h') {
							if (name[6] == 'a' && name[7] == 'n' && name[8] == 'd' &&
							    name[9] == 'l' && name[10] == 'e' && name[11] == '\0') {
								/* case "dlgethandle": ... */
								result = (void *)&libdl_dlgethandle;
							}
						} else if (name[5] == 'm') {
							if (name[6] == 'o' && name[7] == 'd' && name[8] == 'u' &&
							    name[9] == 'l' && name[10] == 'e' && name[11] == '\0') {
								/* case "dlgetmodule": ... */
								result = (void *)&libdl_dlgetmodule;
							}
						}
					}
				}
				break;

			case 'i':
				if (name[3] == 'n' && name[4] == 'f' && name[5] == 'l' &&
				    name[6] == 'a' && name[7] == 't' && name[8] == 'e' &&
				    name[9] == 's' && name[10] == 'e' && name[11] == 'c' &&
				    name[12] == 't' && name[13] == 'i' && name[14] == 'o' &&
				    name[15] == 'n' && name[16] == '\0') {
					/* case "dlinflatesection": ... */
					result = (void *)&libdl_dlinflatesection;
				}
				break;

			case 'l':
				if (name[3] == 'o' && name[4] == 'c' && name[5] == 'k' &&
				    name[6] == 's' && name[7] == 'e' && name[8] == 'c' &&
				    name[9] == 't' && name[10] == 'i' && name[11] == 'o' &&
				    name[12] == 'n' && name[13] == '\0') {
					/* case "dllocksection": ... */
					result = (void *)&libdl_dllocksection;
				}
				break;

			case 'm':
				if (name[3] == 'o') {
					if (name[4] == 'd') {
						if (name[5] == 'u') {
							if (name[6] == 'l') {
								if (name[7] == 'e') {
									if (name[8] == 'b') {
										if (name[9] == 'a' && name[10] == 's' && name[11] == 'e' &&
										    name[12] == '\0') {
											/* case "dlmodulebase": ... */
											result = (void *)&libdl_dlmodulebase;
										}
									} else if (name[8] == 'f') {
										if (name[9] == 'd' && name[10] == '\0') {
											/* case "dlmodulefd": ... */
											result = (void *)&libdl_dlmodulefd;
										}
									} else if (name[8] == 'n') {
										if (name[9] == 'a' && name[10] == 'm' && name[11] == 'e' &&
										    name[12] == '\0') {
											/* case "dlmodulename": ... */
											result = (void *)&libdl_dlmodulename;
										}
									}
								}
							}
						}
					}
				}
				break;

			case 'o':
				if (name[3] == 'p' && name[4] == 'e' && name[5] == 'n' &&
				    name[6] == '\0') {
					/* case "dlopen": ... */
					result = (void *)&libdl_dlopen;
				}
				break;

			case 's':
				if (name[3] == 'e') {
					if (name[4] == 'c') {
						if (name[5] == 't') {
							if (name[6] == 'i') {
								if (name[7] == 'o') {
									if (name[8] == 'n') {
										if (name[9] == 'i') {
											if (name[10] == 'n' && name[11] == 'd' && name[12] == 'e' &&
											    name[13] == 'x' && name[14] == '\0') {
												/* case "dlsectionindex": ... */
												result = (void *)&libdl_dlsectionindex;
											}
										} else if (name[9] == 'm') {
											if (name[10] == 'o' && name[11] == 'd' && name[12] == 'u' &&
											    name[13] == 'l' && name[14] == 'e' && name[15] == '\0') {
												/* case "dlsectionmodule": ... */
												result = (void *)&libdl_dlsectionmodule;
											}
										} else if (name[9] == 'n') {
											if (name[10] == 'a' && name[11] == 'm' && name[12] == 'e' &&
											    name[13] == '\0') {
												/* case "dlsectionname": ... */
												result = (void *)&libdl_dlsectionname;
											}
										}
									}
								}
							}
						}
					}
				} else if (name[3] == 'y') {
					if (name[4] == 'm' && name[5] == '\0') {
						/* case "dlsym": ... */
						result = (void *)&libdl_dlsym;
					}
				}
				break;

			case 't':
				if (name[3] == 'l') {
					if (name[4] == 's') {
						if (name[5] == 'a') {
							if (name[6] == 'd') {
								if (name[7] == 'd') {
									if (name[8] == 'r') {
										if (name[9] == '\0') {
											/* case "dltlsaddr": ... */
											result = (void *)&libdl_dltlsaddr;
										} else if (name[9] == '2') {
											if (name[10] == '\0') {
												/* case "dltlsaddr2": ... */
												result = (void *)&libdl_dltlsaddr2;
											}
										}
									}
								}
							} else if (name[6] == 'l') {
								if (name[7] == 'l') {
									if (name[8] == 'o') {
										if (name[9] == 'c') {
											if (name[10] == '\0') {
												/* case "dltlsalloc": ... */
												result = (void *)&libdl_dltlsalloc;
											} else if (name[10] == 's') {
												if (name[11] == 'e' && name[12] == 'g' && name[13] == '\0') {
													/* case "dltlsallocseg": ... */
													result = (void *)&libdl_dltlsallocseg;
												}
											}
										}
									}
								}
							}
						} else if (name[5] == 'f') {
							if (name[6] == 'r') {
								if (name[7] == 'e') {
									if (name[8] == 'e') {
										if (name[9] == '\0') {
											/* case "dltlsfree": ... */
											result = (void *)&libdl_dltlsfree;
										} else if (name[9] == 's') {
											if (name[10] == 'e' && name[11] == 'g' && name[12] == '\0') {
												/* case "dltlsfreeseg": ... */
												result = (void *)&libdl_dltlsfreeseg;
											}
										}
									}
								}
							}
						}
					}
				}
				break;

			case 'u':
				if (name[3] == 'n' && name[4] == 'l' && name[5] == 'o' &&
				    name[6] == 'c' && name[7] == 'k' && name[8] == 's' &&
				    name[9] == 'e' && name[10] == 'c' && name[11] == 't' &&
				    name[12] == 'i' && name[13] == 'o' && name[14] == 'n' &&
				    name[15] == '\0') {
					/* case "dlunlocksection": ... */
					result = (void *)&libdl_dlunlocksection;
				}
				break;
			default: break;
			}
		}
	} else if (name[0] == 'e') {
		if (name[1] == 'n' && name[2] == 'v' && name[3] == 'i' &&
		    name[4] == 'r' && name[5] == 'o' && name[6] == 'n' &&
		    name[7] == '\0') {
			/* case "environ": ... */
			result = (void *)&root_peb->pp_envp;
		}
	} else if (name[0] == 'p') {
		if (name[1] == 'r') {
			if (name[2] == 'o') {
				if (name[3] == 'g') {
					if (name[4] == 'r') {
						if (name[5] == 'a') {
							if (name[6] == 'm') {
								if (name[7] == '_') {
									if (name[8] == 'i') {
										if (name[9] == 'n') {
											if (name[10] == 'v') {
												if (name[11] == 'o') {
													if (name[12] == 'c') {
														if (name[13] == 'a') {
															if (name[14] == 't') {
																if (name[15] == 'i') {
																	if (name[16] == 'o') {
																		if (name[17] == 'n') {
																			if (name[18] == '_') {
																				if (name[19] == 'n') {
																					if (name[20] == 'a' && name[21] == 'm' && name[22] == 'e' &&
																					    name[23] == '\0') {
																						/* case "program_invocation_name": ... */
																						result = (void *)&root_peb->pp_argv[0];
																					}
																				} else if (name[19] == 's') {
																					if (name[20] == 'h' && name[21] == 'o' && name[22] == 'r' &&
																					    name[23] == 't' && name[24] == '_' && name[25] == 'n' &&
																					    name[26] == 'a' && name[27] == 'm' && name[28] == 'e' &&
																					    name[29] == '\0') {
																						/* case "program_invocation_short_name": ... */
																						result = (void *)dlget_p_program_invocation_short_name();
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
//[[[end]]]
	return result;
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
		.ds_flags = DLSECTION_FLAG_OWNED,                                                                              \
		.ds_index = index,                                                                                             \
	}




INTERN WUNUSED ATTR_CONST DlSection *FCALL
dlsec_builtin_index(size_t sect_index) {
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

INTERN WUNUSED ATTR_CONST char const *FCALL
dlsec_builtin_name(size_t sect_index) {
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


INTERN ATTR_PURE WUNUSED NONNULL((1)) DlSection *FCALL
dlsec_builtin(char const *__restrict name) {
	size_t sect_index;
	char const *sect_name;
	for (sect_index = 0;; ++sect_index) {
		sect_name = dlsec_builtin_name(sect_index);
		if (!sect_name)
			break; /* Unknown section name. */
		if (!strcmp(sect_name, name))
			break; /* Found it. */
	}
	return dlsec_builtin_index(sect_index);
}


/* Return the address of a function `name' that is required by the RTLD core
 * and must be defined by one of the loaded libraries. - If no such function
 * is defined, log an error message to the system log and terminate the hosted
 * application ungracefully. */
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) void *FCALL
dl_require_global(char const *__restrict name) {
	void *result;
	/* Search all globally loaded modules for the symbol. */
	result = libdl_dlsym((DlModule *)RTLD_DEFAULT, name);
	if unlikely(!result) {
		struct debugtrap_reason r;
		syslog(LOG_ERR, "[rtld] Required function %q not found (%q)\n",
		       name, dl_error_message);
		r.dtr_signo  = SIGABRT;
		r.dtr_reason = DEBUGTRAP_REASON_NONE;
		sys_debugtrap(NULL, &r);
		sys_exit_group(EXIT_FAILURE);
	}
	return result;
}



DECL_END

#endif /* !GUARD_LIBDL_BUILTIN_C */
