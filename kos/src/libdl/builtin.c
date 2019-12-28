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
#ifndef GUARD_LIBDL_BUILTIN_C
#define GUARD_LIBDL_BUILTIN_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

/* Keep this one the first */
#include "elf.h"
/**/

#include <kos/debugtrap.h>
#include <kos/exec/peb.h>
#include <kos/syscalls.h>
#include <sys/mman.h>

#include <errno.h>
#include <format-printer.h>
#include <malloc.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

DECL_BEGIN

INTERN NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL syslog_printer)(void *arg,
                                     char const *__restrict data,
                                     size_t datalen) {
	return sys_syslog((syscall_ulong_t)arg,
	                  data,
	                  datalen);
}

#ifndef NDEBUG
INTERN uintptr_t __stack_chk_guard = 0x123baf37;
DEFINE_INTERN_ALIAS(__stack_chk_fail,__stack_chk_fail_local);
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



/* ELF-DL error handling. */
INTERN char elf_dlerror_buffer[128];
INTERN char *elf_dlerror_message = NULL;
INTERN char *LIBCCALL libdl_dlerror(void) {
	return ATOMIC_XCH(elf_dlerror_message, NULL);
}


INTERN ATTR_COLD int CC
elf_setdlerror_badmodule(void *modptr) {
	return elf_setdlerrorf("Bad module handle: %p", modptr);
}

INTERN ATTR_COLD int CC
elf_setdlerror_badsection(void *sectptr) {
	return elf_setdlerrorf("Bad section handle: %p", sectptr);
}

PRIVATE char const message_nomem[] = "Insufficient memory";
INTERN ATTR_COLD int CC
elf_setdlerror_nomem(void) {
	memcpy(elf_dlerror_buffer, message_nomem, sizeof(message_nomem));
	ATOMIC_WRITE(elf_dlerror_message, (char *)elf_dlerror_buffer);
	return -1;
}

INTERN ATTR_COLD NONNULL((1)) int VCC
elf_setdlerrorf(char const *__restrict format, ...) {
	int result;
	va_list args;
	va_start(args, format);
	result = elf_vsetdlerrorf(format, args);
	va_end(args);
	return result;
}

INTERN ATTR_COLD NONNULL((1)) int CC
elf_vsetdlerrorf(char const *__restrict format, va_list args) {
	vsnprintf(elf_dlerror_buffer,
	          sizeof(elf_dlerror_buffer),
	          format,
	          args);
	ATOMIC_WRITE(elf_dlerror_message,
	             (char *)elf_dlerror_buffer);
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


INTERN WUNUSED REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *
LIBCCALL libdl_dlopen(char const *filename, int mode) {
	REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *result;
	if unlikely(!filename) {
		/* ... If filename is NULL, then the returned handle is for the main program... */
		result = DlModule_GlobalList;
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
			ATOMIC_WRITE(elf_dlerror_message, NULL);
			result = DlModule_FindFilenameInPathListFromAll(filename);
		}
		if likely(result)
			update_module_flags(result, mode);
	} else {
		if (strchr(filename, '/')) {
			/* Load a module from an absolute filesystem location. */
			result = DlModule_OpenFilename(filename, mode);
		} else {
			ATOMIC_WRITE(elf_dlerror_message, NULL);
			/* Load a module using the LD-library path List */
			result = DlModule_OpenFilenameInPathList(ld_library_path_env,
			                                         filename,
			                                         mode);
		}
	}
	if unlikely(!result) {
		if (!ATOMIC_READ(elf_dlerror_message))
			elf_setdlerrorf("Failed to open module %q", filename);
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
INTERN NONNULL((1)) int LIBCCALL
libdl_dlclose(REF DlModule *self) {
	if unlikely(!ELF_VERIFY_MODULE_HANDLE(self))
		goto err_bad_module;
	/* Don't decref NODELETE modules! */
	if likely(!(self->dm_flags & RTLD_NODELETE))
		DlModule_Decref(self);
	return 0;
err_bad_module:
	return elf_setdlerror_badmodule(self);
}


INTERN NONNULL((1)) int LIBCCALL
libdl_dlexceptaware(DlModule *self) {
	if unlikely(!ELF_VERIFY_MODULE_HANDLE(self))
		goto err_bad_module;
	/* TODO */
	return 1;
err_bad_module:
	return elf_setdlerror_badmodule(self);
}


#define DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NOT_FOUND 0
#define DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_FOUND     1
#define DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NO_MODULE 2
#define DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_ERROR     3
PRIVATE NONNULL((2)) unsigned int LIBCCALL
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
		if (symbol.ds_mod == &ld_rtld_module) {
			/* Special case: Search the RTLD module itself. */
			void *addr;
			addr = dlsym_builtin(name);
			if (addr) {
				*presult = (ElfW(Addr))addr;
				return DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_FOUND;
			}
		}
		symbol.ds_sym = DlModule_GetLocalSymbol(symbol.ds_mod,
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
					if (ELFW(ST_TYPE)(symbol.ds_sym->st_info) == STT_GNU_IFUNC)
						result = (*(ElfW(Addr)(*)(void))(void *)result)();
				}
				*presult = result;
				return DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_FOUND;
			}
		}
	}
	return DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NOT_FOUND;
}

INTERN NONNULL((2)) void *LIBCCALL
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
			if (symbol.ds_mod == &ld_rtld_module) {
				result = (ElfW(Addr))dlsym_builtin(name);
				if (result) {
					DlModule_DecrefNoKill(symbol.ds_mod);
					goto done;
				}
			} else {
				symbol.ds_sym = DlModule_GetLocalSymbol(symbol.ds_mod,
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
							if (ELFW(ST_TYPE)(symbol.ds_sym->st_info) == STT_GNU_IFUNC) {
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
				if (ELFW(ST_TYPE)(weak_symbol.ds_sym->st_info) == STT_GNU_IFUNC) {
					TRY {
						result = (*(ElfW(Addr)(*)(void))(void *)result)();
					} EXCEPT {
						DlModule_Decref(weak_symbol.ds_mod);
						RETHROW();
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
			elf_setdlerrorf("No module loaded after %q contains a symbol %q",
			                symbol.ds_mod->dm_filename, name);
		} else {
			elf_setdlerrorf("No loaded module contains a symbol %q", name);
		}
	} else if (self == RTLD_NEXT) {
		symbol.ds_mod = libdl_dlgethandle(__builtin_return_address(0), DLGETHANDLE_FNORMAL);
		/* Search modules loaded after `symbol.ds_mod' */
		if unlikely(!symbol.ds_mod)
			goto err_rtld_next_no_base;
		atomic_rwlock_read(&DlModule_GlobalLock);
		goto again_search_globals_next_noref;
	} else {
		if unlikely(self == &ld_rtld_module) {
			result = (ElfW(Addr))dlsym_builtin(name);
			if likely(result)
				goto done;
		} else {
			if unlikely(!ELF_VERIFY_MODULE_HANDLE(self))
				goto err_bad_module;
			/* Scan the given module itself */
			symbol.ds_sym = DlModule_GetLocalSymbol(self,
			                                        name,
			                                        &hash_elf,
			                                        &hash_gnu);
			/* Most likely case: The symbol is already apart of the specified module! */
			if likely(symbol.ds_sym &&
			          symbol.ds_sym->st_shndx != SHN_ABS) {
				if (ELFW(ST_BIND)(symbol.ds_sym->st_info) == STB_WEAK) {
					weak_symbol = symbol;
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
						if (ELFW(ST_TYPE)(symbol.ds_sym->st_info) == STT_GNU_IFUNC)
							result = (*(ElfW(Addr)(*)(void))(void *)result)();
					}
done:
					return (void *)result;
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
					if (ELFW(ST_TYPE)(weak_symbol.ds_sym->st_info) == STT_GNU_IFUNC)
						result = (*(ElfW(Addr)(*)(void))(void *)result)();
				}
				goto done;
			}
		}
		/* Missing symbol... */
		elf_setdlerrorf("Failed to find symbol %q in %q",
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
	elf_setdlerrorf("Can only use `RTLD_NEXT' from dynamically loaded code");
	goto err;
err_bad_module:
	elf_setdlerror_badmodule(self);
	goto err;
}




INTERN WUNUSED
REF_IF(!(return->dm_flags & RTLD_NODELETE) &&
       (flags & DLGETHANDLE_FINCREF)) DlModule *LIBCCALL
libdl_dlgethandle(void const *static_pointer, unsigned int flags) {
	DlModule *result;
	if unlikely(flags & ~(DLGETHANDLE_FINCREF)) {
		elf_setdlerrorf("Invalid flags %#x passed to `dlgethandle()'", flags);
		goto err;
	}
	atomic_rwlock_read(&DlModule_AllLock);
	LLIST_FOREACH(result, DlModule_AllList, dm_modules) {
		uint16_t i;
		if ((uintptr_t)static_pointer < result->dm_loadstart)
			continue;
		if ((uintptr_t)static_pointer >= result->dm_loadend)
			continue;
		/* Make sure that `static_pointer' maps to some program segment. */
		for (i = 0; i < result->dm_phnum; ++i) {
			uintptr_t segment_base;
			if (result->dm_phdr[i].p_type != PT_LOAD)
				continue;
			segment_base = result->dm_loadaddr + result->dm_phdr[i].p_vaddr;
			if ((uintptr_t)static_pointer < segment_base)
				continue;
			if ((uintptr_t)static_pointer >= segment_base + result->dm_phdr[i].p_memsz)
				continue;
			/* Found the segment! */
			if ((flags & DLGETHANDLE_FINCREF) &&
			    !(result->dm_flags & RTLD_NODELETE))
				DlModule_Incref(result);
			goto got_result;
		}
	}
	atomic_rwlock_endread(&DlModule_AllLock);
	elf_setdlerror_nomodataddr(static_pointer);
err:
	return NULL;
got_result:
	atomic_rwlock_endread(&DlModule_AllLock);
	return result;
}

INTERN WUNUSED REF_IF(!(return->dm_flags & RTLD_NODELETE) && (flags & DLGETHANDLE_FINCREF))
DlModule *LIBCCALL libdl_dlgetmodule(char const *name, unsigned int flags) {
	DlModule *result;
	if (!name) {
		result = libdl_dlgethandle(__builtin_return_address(0), flags);
		if unlikely(!result)
			elf_setdlerrorf("Can only call `dlgetmodule(NULL)' from dynamically loaded code");
		return result;
	}
	if unlikely(flags & ~(DLGETHANDLE_FINCREF | DLGETHANDLE_FNOCASE)) {
		elf_setdlerrorf("Invalid flags %#x passed to `dlgetmodule()'", flags);
		goto err;
	}
	atomic_rwlock_read(&DlModule_AllLock);
	LLIST_FOREACH(result, DlModule_AllList, dm_modules) {
		if (strcmp(result->dm_filename, name) == 0)
			goto got_result;
	}
	LLIST_FOREACH(result, DlModule_AllList, dm_modules) {
		char *sep = strrchr(result->dm_filename, '/');
		if (!sep)
			continue;
		if (strcmp(sep + 1, name) == 0)
			goto got_result;
	}
	LLIST_FOREACH(result, DlModule_AllList, dm_modules) {
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
	LLIST_FOREACH(result, DlModule_AllList, dm_modules) {
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
		LLIST_FOREACH(result, DlModule_AllList, dm_modules) {
			if (strcasecmp(result->dm_filename, name) == 0)
				goto got_result;
		}
		LLIST_FOREACH(result, DlModule_AllList, dm_modules) {
			char *sep = strrchr(result->dm_filename, '/');
			if (!sep)
				continue;
			if (strcasecmp(sep + 1, name) == 0)
				goto got_result;
		}
		LLIST_FOREACH(result, DlModule_AllList, dm_modules) {
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
		LLIST_FOREACH(result, DlModule_AllList, dm_modules) {
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
	elf_setdlerrorf("Unknown module %q", name);
err:
	return NULL;
got_result:
	if ((flags & DLGETHANDLE_FINCREF) &&
	    !(result->dm_flags & RTLD_NODELETE))
		DlModule_Incref(result);
	atomic_rwlock_endread(&DlModule_AllLock);
	return result;
}


INTERN NONNULL((2)) int LIBCCALL
libdl_dladdr(void const *address, Dl_info *info) {
	REF DlModule *mod;
	mod = libdl_dlgethandle(address, DLGETHANDLE_FINCREF);
	if unlikely(!mod)
		goto err;
	info->dli_fname = mod->dm_filename;
	info->dli_fbase = (void *)mod->dm_loadaddr;
	info->dli_sname = NULL;
	info->dli_saddr = NULL;
	/* Search for the closest dynamic symbol. */
	if (mod->dm_dynsym_tab && mod->dm_hashtab) {
		ElfW(Sym) *iter, *end;
		uintptr_t winner_distance = (uintptr_t)-1;
		iter = mod->dm_dynsym_tab;
		end  = iter + mod->dm_hashtab->ht_nchains;
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
				if (mod->dm_dynstr)
					info->dli_sname = mod->dm_dynstr + iter->st_name;
				winner_distance = distance;
			}
		}
	}
	if (!(mod->dm_flags & RTLD_NODELETE))
		DlModule_Decref(mod);
	return 0;
err:
	return -1;
}

INTERN WUNUSED fd_t LIBCCALL
libdl_dlmodulefd(DlModule *self) {
	if unlikely(!ELF_VERIFY_MODULE_HANDLE(self))
		goto err_bad_module;
	return DlModule_GetFd(self);
err_bad_module:
	return elf_setdlerror_badmodule(self);
}

INTERN WUNUSED char const *LIBCCALL
libdl_dlmodulename(DlModule *self) {
	if unlikely(!ELF_VERIFY_MODULE_HANDLE(self))
		goto err_bad_module;
	return self->dm_filename;
err_bad_module:
	elf_setdlerror_badmodule(self);
	return NULL;
}

INTERN WUNUSED void *LIBCCALL
libdl_dlmodulebase(DlModule *self) {
	if unlikely(!ELF_VERIFY_MODULE_HANDLE(self))
		goto err_bad_module;
	return (void *)self->dm_loadaddr;
err_bad_module:
	elf_setdlerror_badmodule(self);
	return NULL;
}


INTERN NONNULL((1)) void CC
DlSection_Destroy(DlSection *__restrict self) {
	DlModule *mod;
	if ((self->ds_flags & ELF_DLSECTION_FLAG_OWNED) && (self->ds_data != (void *)-1))
		sys_munmap(self->ds_data, self->ds_size);
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
	if (mod && !(self->ds_flags & ELF_DLSECTION_FLAG_OWNED))
		DlModule_Decref(mod);
	free(self);
}

INTERN WUNUSED REF DlSection *LIBCCALL
libdl_dllocksection(DlModule *self,
                    char const *__restrict name,
                    unsigned int flags) {
	ElfW(Shdr) *sect;
	size_t index;
	REF DlSection *result;
	if unlikely(!ELF_VERIFY_MODULE_HANDLE(self))
		goto err_bad_module;
	if unlikely(flags & ~(DLLOCKSECTION_FINDEX | DLLOCKSECTION_FNODATA))
		goto err_bad_flags;
	if (self == &ld_rtld_module) {
		/* Special case: Lookup a section within the dynamic linker itself. */
		result = flags & DLLOCKSECTION_FINDEX
		         ? dlsec_builtin_index((uintptr_t)name)
		         : dlsec_builtin(name);
		if likely(result) {
			DlSection_Incref(result);
		} else {
			elf_setdlerror_nosect(self, name);
		}
		return result;
	}
	if (flags & DLLOCKSECTION_FINDEX) {
		sect = DlModule_GetShdrs(self);
		if unlikely(!sect)
			goto err;
		if unlikely((uintptr_t)name >= self->dm_shnum) {
			elf_setdlerrorf("%q: Section index %Iu is greater than %Iu",
			                self->dm_filename,
			                (uintptr_t)name,
			                (uintptr_t)self->dm_shnum);
			goto err;
		}
		sect += (uintptr_t)name;
	} else {
		sect = DlModule_GetSection(self, name);
		if unlikely(!sect)
			goto err;
	}
	assert(sect >= self->dm_shdr);
	assert(sect < self->dm_shdr + self->dm_shnum);
	index = (size_t)(sect - self->dm_shdr);
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
		/* Must allocate a descriptor for this section. */
		atomic_rwlock_endread(&self->dm_sections_lock);
		result = (REF DlSection *)malloc(sizeof(DlSection));
		if unlikely(!result)
			goto err_nomem;
		result->ds_size    = sect->sh_size;
		result->ds_entsize = sect->sh_entsize;
		result->ds_link    = sect->sh_link;
		result->ds_info    = sect->sh_info;
		result->ds_refcnt  = 1;
		result->ds_module  = self;
		result->ds_index   = index;
#ifndef CONFIG_NO_DANGLING_DL_SECTIONS
		result->ds_dangling = (REF DlSection *)-1;
#endif /* !CONFIG_NO_DANGLING_DL_SECTIONS */
		atomic_rwlock_init(&result->ds_module_lock);
		if (sect->sh_flags & SHF_ALLOC) {
			/* Section is already allocated in member. */
			result->ds_data  = (void *)(self->dm_loadaddr + sect->sh_addr);
			result->ds_flags = ELF_DLSECTION_FLAG_NORMAL;
			DlModule_Incref(self); /* Reference stored in `result->ds_module' */
		} else {
			result->ds_data  = (void *)-1;
			result->ds_flags = ELF_DLSECTION_FLAG_OWNED;
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
	}
	atomic_rwlock_endread(&self->dm_sections_lock);
	if (result->ds_data == (void *)-1 && !(flags & DLLOCKSECTION_FNODATA) &&
	    (result->ds_flags & ELF_DLSECTION_FLAG_OWNED)) {
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
				elf_setdlerrorf("%q: Failed to map section #%Iu into memory",
				                self->dm_filename, (uintptr_t)name);
			} else {
				elf_setdlerrorf("%q: Failed to map section %q into memory",
				                self->dm_filename, name);
			}
			goto err;
		}
		if unlikely(!ATOMIC_CMPXCH(result->ds_data, (void *)-1, base))
			sys_munmap(base, sect->sh_size);
	}
	return result;
err_nomem:
	elf_setdlerror_nomem();
err:
	return NULL;
err_bad_module:
	elf_setdlerror_badmodule(self);
	goto err;
err_bad_flags:
	elf_setdlerrorf("Invalid flags %#x passed to `dllocksection()'", flags);
	goto err;
}


INTERN int LIBCCALL
libdl_dlunlocksection(REF DlSection *sect) {
	if unlikely(!ELF_VERIFY_SECTION_HANDLE(sect))
		goto err_bad_section;
#ifndef CONFIG_NO_DANGLING_DL_SECTIONS
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
				sect->ds_dangling            = mod->dm_sections_dangling;
				mod->dm_sections_dangling = sect;
				atomic_rwlock_endwrite(&mod->dm_sections_lock);
				DlModule_Decref(mod);
				return 0;
			}
			atomic_rwlock_endwrite(&mod->dm_sections_lock);
			DlModule_Decref(mod);
		}
	}
#endif /* !CONFIG_NO_DANGLING_DL_SECTIONS */
	DlSection_Decref(sect);
	return 0;
err_bad_section:
	return elf_setdlerror_badsection(sect);
}

INTERN char const *LIBCCALL
libdl_dlsectionname(DlSection *sect) {
	char const *result;
	REF DlModule *mod;
	if unlikely(!sect)
		goto err_bad_section;
	atomic_rwlock_read(&sect->ds_module_lock);
	mod = sect->ds_module;
	if (!mod || !DlModule_TryIncref(mod)) {
		atomic_rwlock_endread(&sect->ds_module_lock);
err_mod_unloaded:
		elf_setdlerrorf("Module associated with section was unloaded");
		goto err;
	}
	atomic_rwlock_endread(&sect->ds_module_lock);
	if (mod == &ld_rtld_module) {
		/* Special case: the RTLD driver module. */
		assert(sect->ds_index < BUILTIN_SECTIONS_COUNT);
		result = dlsec_builtin_name(sect->ds_index);
		assert(result != NULL);
	} else {
		/* Regular module. */
		assert(sect->ds_index < mod->dm_shnum);
		assert(mod->dm_shdr != NULL);
		assert(mod->dm_shstrtab != NULL);
		result  = mod->dm_shstrtab;
		result += mod->dm_shdr[sect->ds_index].sh_name;
	}
	if unlikely(!DlModule_Decref(mod))
		goto err_mod_unloaded;
	return result;
err_bad_section:
	elf_setdlerror_badsection(sect);
err:
	return NULL;
}

INTERN size_t LIBCCALL
libdl_dlsectionindex(DlSection *sect) {
	size_t result;
	if unlikely(!ELF_VERIFY_SECTION_HANDLE(sect))
		goto err_bad_section;
	result = sect->ds_index;
	return result;
err_bad_section:
	elf_setdlerror_badsection(sect);
	return (size_t)-1;
}


INTERN DlModule *LIBCCALL
libdl_dlsectionmodule(DlSection *sect, unsigned int flags) {
	DlModule *mod;
	if unlikely(!ELF_VERIFY_SECTION_HANDLE(sect))
		goto err_bad_section;
	if unlikely(flags & ~(DLGETHANDLE_FINCREF)) {
		elf_setdlerrorf("Invalid flags %#x passed to `dlsectionmodule()'", flags);
		goto err;
	}

	atomic_rwlock_read(&sect->ds_module_lock);
	mod = sect->ds_module;
	if (!mod || ((flags & DLGETHANDLE_FINCREF)
	             ? !DlModule_TryIncref(mod)
	             : !ATOMIC_READ(mod->dm_refcnt))) {
		atomic_rwlock_endread(&sect->ds_module_lock);
		elf_setdlerrorf("Module associated with section was unloaded");
		goto err;
	}
	atomic_rwlock_endread(&sect->ds_module_lock);
	return mod;
err_bad_section:
	elf_setdlerror_badsection(sect);
err:
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

INTERN int LIBCCALL libdl_dlclearcaches(void) {
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
		for (module_iter = DlModule_AllList; module_iter;
		     module_iter = module_iter->dm_modules.ln_next) {
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
#ifndef CONFIG_NO_DANGLING_DL_SECTIONS
	{
		DlModule *module_iter;
		/* Delete dangling sections. */
again_lock_global:
		atomic_rwlock_read(&DlModule_AllLock);
		for (module_iter = DlModule_AllList; module_iter;
		     module_iter = module_iter->dm_modules.ln_next) {
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
#endif /* !CONFIG_NO_DANGLING_DL_SECTIONS */
	/* Also trim malloc memory from our heap implementation. */
	if (malloc_trim(0))
		result = 1;
	return result;
}


INTERN void *LIBCCALL
libdl_dlauxinfo(DlModule *self, unsigned int type,
                void *buf, size_t *pauxvlen) {
	void *result;
	if (!self)
		self = DlModule_GlobalList;
	else if unlikely(!ELF_VERIFY_MODULE_HANDLE(self)) {
		elf_setdlerror_badmodule(self);
		goto err;
	}
	(void)buf;
	switch (type) {

	case DLAUXINFO_ELF_PHDR:
		result = self->dm_phdr;
		if (pauxvlen)
			*pauxvlen = (size_t)self->dm_phnum;
		break;

	case DLAUXINFO_ELF_SHDR:
		result = DlModule_GetShdrs(self);
		if (pauxvlen)
			*pauxvlen = (size_t)self->dm_phnum;
		break;

	case DLAUXINFO_ELF_DYN:
		result = self->dm_dynhdr;
		if (pauxvlen)
			*pauxvlen = (size_t)self->dm_dyncnt;
		break;

	case DLAUXINFO_ELF_DYNSYM:
		result = self->dm_dynsym_tab;
		if (pauxvlen) {
			*pauxvlen = self->dm_hashtab
			            ? (size_t)self->dm_hashtab->ht_nchains
			            : (size_t)-1;
		}
		break;

	case DLAUXINFO_ELF_DYNSTR:
		result = self->dm_dynstr;
		break;

	case DLAUXINFO_ELF_SHSTRTAB:
		result = DlModule_GetShstrtab(self);
		break;

	case DLAUXINFO_ELF_DEPENDS:
		result = self->dm_depvec;
		if (pauxvlen)
			*pauxvlen = self->dm_depcnt;
		break;

	default:
		elf_setdlerrorf("Invalid info type %#x", type);
		goto err;
	}
	return result;
err:
	return NULL;
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
DEFINE_PUBLIC_ALIAS(dlclearcaches, libdl_dlclearcaches);
DEFINE_PUBLIC_ALIAS(dlauxinfo, libdl_dlauxinfo);




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
		"dlauxinfo"       : "result = (void *)&libdl_dlauxinfo;",         \
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



/* Return the address of a builtin function (e.g. `dlopen()') */
INTERN WUNUSED ATTR_PURE NONNULL((1)) void *FCALL
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
						if (name[5] == 'v') {
							if (name[6] == '\0') {
								/* case "__argv": ... */
								result = (void *)&root_peb->pp_argv;
							}
						} else if (name[5] == 'c') {
							if (name[6] == '\0') {
								/* case "__argc": ... */
								result = (void *)&root_peb->pp_argc;
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
				if (name[3] == 'r') {
					if (name[4] == 'o') {
						if (name[5] == 'g') {
							if (name[6] == 'n') {
								if (name[7] == 'a') {
									if (name[8] == 'm') {
										if (name[9] == 'e') {
											if (name[10] == '_') {
												if (name[11] == 'f' && name[12] == 'u' && name[13] == 'l' &&
												    name[14] == 'l' && name[15] == '\0') {
													/* case "__progname_full": ... */
													result = (void *)&root_peb->pp_argv[0];
												}
											} else if (name[10] == '\0') {
												/* case "__progname": ... */
												result = (void *)dlget_p_program_invocation_short_name();
											}
										}
									}
								}
							}
						}
					}
				} else if (name[3] == 'e') {
					if (name[4] == 'b' && name[5] == '\0') {
						/* case "__peb": ... */
						result = (void *)root_peb;
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

			case 'a':
				if (name[3] == 'u') {
					if (name[4] == 'x' && name[5] == 'i' && name[6] == 'n' &&
					    name[7] == 'f' && name[8] == 'o' && name[9] == '\0') {
						/* case "dlauxinfo": ... */
						result = (void *)&libdl_dlauxinfo;
					}
				} else if (name[3] == 'd') {
					if (name[4] == 'd' && name[5] == 'r' && name[6] == '\0') {
						/* case "dladdr": ... */
						result = (void *)&libdl_dladdr;
					}
				}
				break;

			case 'c':
				if (name[3] == 'l') {
					if (name[4] == 'o') {
						if (name[5] == 's' && name[6] == 'e' && name[7] == '\0') {
							/* case "dlclose": ... */
							result = (void *)&libdl_dlclose;
						}
					} else if (name[4] == 'e') {
						if (name[5] == 'a' && name[6] == 'r' && name[7] == 'c' &&
						    name[8] == 'a' && name[9] == 'c' && name[10] == 'h' &&
						    name[11] == 'e' && name[12] == 's' && name[13] == '\0') {
							/* case "dlclearcaches": ... */
							result = (void *)&libdl_dlclearcaches;
						}
					}
				}
				break;

			case 'e':
				if (name[3] == 'x') {
					if (name[4] == 'c' && name[5] == 'e' && name[6] == 'p' &&
					    name[7] == 't' && name[8] == 'a' && name[9] == 'w' &&
					    name[10] == 'a' && name[11] == 'r' && name[12] == 'e' &&
					    name[13] == '\0') {
						/* case "dlexceptaware": ... */
						result = (void *)&libdl_dlexceptaware;
					}
				} else if (name[3] == 'r') {
					if (name[4] == 'r' && name[5] == 'o' && name[6] == 'r' &&
					    name[7] == '\0') {
						/* case "dlerror": ... */
						result = (void *)&libdl_dlerror;
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
						if (name[5] == 'm') {
							if (name[6] == 'o' && name[7] == 'd' && name[8] == 'u' &&
							    name[9] == 'l' && name[10] == 'e' && name[11] == '\0') {
								/* case "dlgetmodule": ... */
								result = (void *)&libdl_dlgetmodule;
							}
						} else if (name[5] == 'h') {
							if (name[6] == 'a' && name[7] == 'n' && name[8] == 'd' &&
							    name[9] == 'l' && name[10] == 'e' && name[11] == '\0') {
								/* case "dlgethandle": ... */
								result = (void *)&libdl_dlgethandle;
							}
						}
					}
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
				if (name[3] == 'y') {
					if (name[4] == 'm' && name[5] == '\0') {
						/* case "dlsym": ... */
						result = (void *)&libdl_dlsym;
					}
				} else if (name[3] == 'e') {
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
				}
				break;

			case 't':
				if (name[3] == 'l') {
					if (name[4] == 's') {
						if (name[5] == 'f') {
							if (name[6] == 'r') {
								if (name[7] == 'e') {
									if (name[8] == 'e') {
										if (name[9] == 's') {
											if (name[10] == 'e' && name[11] == 'g' && name[12] == '\0') {
												/* case "dltlsfreeseg": ... */
												result = (void *)&libdl_dltlsfreeseg;
											}
										} else if (name[9] == '\0') {
											/* case "dltlsfree": ... */
											result = (void *)&libdl_dltlsfree;
										}
									}
								}
							}
						} else if (name[5] == 'a') {
							if (name[6] == 'l') {
								if (name[7] == 'l') {
									if (name[8] == 'o') {
										if (name[9] == 'c') {
											if (name[10] == 's') {
												if (name[11] == 'e' && name[12] == 'g' && name[13] == '\0') {
													/* case "dltlsallocseg": ... */
													result = (void *)&libdl_dltlsallocseg;
												}
											} else if (name[10] == '\0') {
												/* case "dltlsalloc": ... */
												result = (void *)&libdl_dltlsalloc;
											}
										}
									}
								}
							} else if (name[6] == 'd') {
								if (name[7] == 'd' && name[8] == 'r' && name[9] == '\0') {
									/* case "dltlsaddr": ... */
									result = (void *)&libdl_dltlsaddr;
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
																				if (name[19] == 's') {
																					if (name[20] == 'h' && name[21] == 'o' && name[22] == 'r' &&
																					    name[23] == 't' && name[24] == '_' && name[25] == 'n' &&
																					    name[26] == 'a' && name[27] == 'm' && name[28] == 'e' &&
																					    name[29] == '\0') {
																						/* case "program_invocation_short_name": ... */
																						result = (void *)dlget_p_program_invocation_short_name();
																					}
																				} else if (name[19] == 'n') {
																					if (name[20] == 'a' && name[21] == 'm' && name[22] == 'e' &&
																					    name[23] == '\0') {
																						/* case "program_invocation_name": ... */
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


#ifndef CONFIG_NO_DANGLING_DL_SECTIONS
#define IFNDEF_NO_DANGLING_DL_SECTIONS(...) __VA_ARGS__
#else /* !CONFIG_NO_DANGLING_DL_SECTIONS */
#define IFNDEF_NO_DANGLING_DL_SECTIONS(...) /* nothing */
#endif /* CONFIG_NO_DANGLING_DL_SECTIONS */

#define INIT_RTLD_SECTION(index, link_name)                                                                            \
	{                                                                                                                  \
		.ds_data        = NULL, /* Initialized later */                                                                \
		.ds_size        = 0,    /* Initialized later (even though it could be here if ld/gcc weren't quite as dumb) */ \
		.ds_entsize     = 0,                                                                                           \
		.ds_link        = 0,                                                                                           \
		.ds_info        = 0,                                                                                           \
		.ds_refcnt      = 1,                                                                                           \
		.ds_module_lock = ATOMIC_RWLOCK_INIT,                                                                          \
		.ds_module      = NULL, /* Initialized later */                                                                \
		IFNDEF_NO_DANGLING_DL_SECTIONS(.ds_dangling = NULL, )                                                          \
		.ds_flags = ELF_DLSECTION_FLAG_OWNED,                                                                          \
		.ds_index = index,                                                                                             \
	}




INTERN WUNUSED ATTR_CONST struct elf_dlsection *FCALL
dlsec_builtin_index(size_t sect_index) {
	struct elf_dlsection *result;
	switch (sect_index) {
#define DEFINE_BUILTIN_SECTION(index, sect_name, link_name)                                       \
	case index: {                                                                                 \
		INTDEF byte_t __rtld_##link_name##_start[];                                               \
		INTDEF byte_t __rtld_##link_name##_end[];                                                 \
		PRIVATE struct elf_dlsection rtld_sect_##link_name = INIT_RTLD_SECTION(index, link_name); \
		result = &rtld_sect_##link_name;                                                          \
		if (!result->ds_module) {                                                                 \
			result->ds_data = (void *)(__rtld_##link_name##_start);                               \
			result->ds_size = (size_t)(__rtld_##link_name##_end - __rtld_##link_name##_start);    \
			COMPILER_WRITE_BARRIER();                                                             \
			result->ds_module = &ld_rtld_module;                                                  \
		}                                                                                         \
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
#define DEFINE_BUILTIN_SECTION(index, sect_name, link_name) \
	case index:                                             \
		result = sect_name;                                 \
		break;
	BUILTIN_SECTIONS_ENUMERATE(DEFINE_BUILTIN_SECTION)
#undef DEFINE_BUILTIN_SECTION
	default:
		result = NULL;
		break;
	}
	return result;
}


INTERN WUNUSED ATTR_PURE NONNULL((1)) struct elf_dlsection *FCALL
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
INTERN WUNUSED ATTR_RETNONNULL NONNULL((1)) void *FCALL
require_global(char const *__restrict name) {
	void *result;
	/* Search all globally loaded modules for the symbol. */
	result = libdl_dlsym((DlModule *)RTLD_DEFAULT, name);
	if unlikely(!result) {
		struct debugtrap_reason r;
		syslog(LOG_ERR, "[rtld] Required function %q not found (%q)\n",
		       name, elf_dlerror_message);
		r.dtr_signo  = SIGABRT;
		r.dtr_reason = DEBUGTRAP_REASON_NONE;
		sys_debugtrap(NULL, &r);
		sys_exit_group(EXIT_FAILURE);
	}
	return result;
}



DECL_END

#endif /* !GUARD_LIBDL_BUILTIN_C */
