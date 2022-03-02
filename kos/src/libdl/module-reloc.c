/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBDL_MODULE_RELOC_C
#define GUARD_LIBDL_MODULE_RELOC_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

/* Keep this one the first */
#include "dl.h"
/**/

#include <hybrid/typecore.h>

#include <kos/exec/peb.h> /* struct process_peb */
#include <kos/syscalls.h>
#include <sys/ioctl.h>

#include <elf.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <termios.h>
#include <unistd.h>

#undef LAZY_TRACE
#if 1
#define LAZY_TRACE 1
#endif

#undef RELSYM_TRACE
#if 0
#define RELSYM_TRACE 1
#endif

#ifdef RELSYM_TRACE
#define TRACE_RESOLVE_FOR_RELOC(name, addr, size, module_filename)                       \
	syslog(LOG_DEBUG, "[rtld] %d:Resolve %q for relocation (to %p+%" PRIuSIZ " from %q)\n", \
	       __LINE__, name, addr, size, module_filename)
#else /* RELSYM_TRACE */
#define TRACE_RESOLVE_FOR_RELOC(name, addr, size, module_filename) (void)0
#endif /* !RELSYM_TRACE */



DECL_BEGIN

struct dl_symbol {
	DlModule        *ds_mod; /* [1..1] The associated module */
	ElfW(Sym) const *ds_sym; /* [1..1] The actual symbol (or its address for custom module). */
	size_t           ds_siz; /* [valid_if(ds_mod->dm_ops)] Symbol size */
};



#define DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NOT_FOUND 0
#define DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_FOUND     1
#define DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NO_MODULE 2
PRIVATE WUNUSED NONNULL((1, 2, 3, 4, 5, 8)) unsigned int CC
dlmodule_find_symbol_in_dependencies(DlModule *__restrict self,
                                     char const *__restrict name,
                                     uintptr_t *__restrict phash_elf,
                                     uintptr_t *__restrict phash_gnu,
                                     ElfW(Addr) *__restrict paddr,
                                     size_t *psize,
                                     DlModule **pmodule,
                                     struct dl_symbol *__restrict pweak_symbol,
                                     size_t depth)
		THROWS(...) {
	struct dl_symbol symbol;
	size_t i;
	if (!self->dm_depcnt)
		return DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NO_MODULE;
	if (depth != 0) {
		unsigned int result;
		--depth;
		result = DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NO_MODULE;
		for (i = 0; i < self->dm_depcnt; ++i) {
			unsigned int error;
			error = dlmodule_find_symbol_in_dependencies(self->dm_depvec[i],
			                                             name,
			                                             phash_elf,
			                                             phash_gnu,
			                                             paddr,
			                                             psize,
			                                             pmodule,
			                                             pweak_symbol,
			                                             depth);
			/* Check if the symbol was found. */
			if (error == DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_FOUND)
				return error;
			/* If at least 1 module was searched, unlock the next depth-level. */
			if (error == DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NOT_FOUND)
				result = DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NOT_FOUND;
		}
		return result;
	}
	for (i = 0; i < self->dm_depcnt; ++i) {
		symbol.ds_mod = self->dm_depvec[i];
		if (symbol.ds_mod->dm_flags & RTLD_GLOBAL)
			continue; /* Already scanned! */
		if (symbol.ds_mod == &dl_rtld_module) {
			/* Special case: Search the RTLD module itself. */
			void *addr;
			addr = dlsym_builtin(name);
			if (addr) {
				*paddr = (ElfW(Addr))addr;
				TRACE_RESOLVE_FOR_RELOC(name, *paddr, dlsym_builtin_size(name),
				                        dl_rtld_module.dm_filename);
				if unlikely(psize)
					*psize = dlsym_builtin_size(name);
				if unlikely(pmodule)
					*pmodule = &dl_rtld_module;
				return DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_FOUND;
			}
			continue;
		}
		if (symbol.ds_mod->dm_ops) {
			int error;
			error = (*symbol.ds_mod->dm_ops->df_dlsym)(symbol.ds_mod,
			                                           name,
			                                           (void **)&symbol.ds_sym,
			                                           &symbol.ds_siz);
			if (error < 0)
				continue;
			/* Found a symbol! */
			if (error > 0) {
				/* Weak definition (remember if this is the first one) */
				if (!pweak_symbol->ds_mod) {
					incref(symbol.ds_mod);
					*pweak_symbol = symbol;
				}
			} else {
				/* Found the real, actual symbol! */
				*paddr = (ElfW(Addr))(void *)symbol.ds_sym;
				TRACE_RESOLVE_FOR_RELOC(name, *paddr, symbol.ds_siz, symbol.ds_mod->dm_filename);
				if unlikely(psize)
					*psize = symbol.ds_siz;
				if unlikely(pmodule)
					*pmodule = symbol.ds_mod;
				return DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_FOUND;
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
				if (!pweak_symbol->ds_mod) {
					incref(symbol.ds_mod);
					*pweak_symbol = symbol;
				}
			} else {
				/* Found the real, actual symbol! */
				ElfW(Addr) addr;
				addr = symbol.ds_sym->st_value;
				if (symbol.ds_sym->st_shndx != SHN_ABS)
					addr += symbol.ds_mod->dm_loadaddr;
				if (ELFW(ST_TYPE)(symbol.ds_sym->st_info) == STT_GNU_IFUNC ||
				    ELFW(ST_TYPE)(symbol.ds_sym->st_info) == STT_KOS_IDATA) {
					TRY {
						addr = (*(ElfW(Addr)(*)(void))(void *)addr)();
					} EXCEPT {
						if (pweak_symbol->ds_mod)
							decref(pweak_symbol->ds_mod);
						RETHROW();
					}
				}
				*paddr = addr;
				TRACE_RESOLVE_FOR_RELOC(name, addr, symbol.ds_sym->st_size,
				                        symbol.ds_mod->dm_filename);
				if unlikely(psize)
					*psize = symbol.ds_sym->st_size;
				if unlikely(pmodule)
					*pmodule = symbol.ds_mod;
				return DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_FOUND;
			}
		}
	}
	return DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NOT_FOUND;
}


PRIVATE ATTR_NOINLINE WUNUSED NONNULL((1, 3)) bool CC
DlModule_ElfFindSymbol(DlModule *__restrict self, uintptr_t symid,
                       ElfW(Addr) *__restrict paddr,
                       size_t *psize, DlModule **pmodule)
		THROWS(...) {
	struct dl_symbol weak_symbol;
	ElfW(Sym) const *symbol;
	ElfW(Addr) addr;
	char const *name;
	weak_symbol.ds_mod = NULL;
	symbol = self->dm_elf.de_dynsym_tab + symid;
	if ((symbol->st_shndx != SHN_UNDEF) && (self->dm_flags & RTLD_DEEPBIND)) {
		/* Symbol has been defined locally. */
		if (ELFW(ST_BIND)(symbol->st_info) == STB_WEAK) {
			weak_symbol.ds_mod = self;
			weak_symbol.ds_sym = symbol;
			incref(self);
			goto search_external_symbol;
		}
got_local_symbol:
		addr = symbol->st_value;
		if (symbol->st_shndx != SHN_ABS)
			addr += self->dm_loadaddr;
		if (ELFW(ST_TYPE)(symbol->st_info) == STT_GNU_IFUNC ||
		    ELFW(ST_TYPE)(symbol->st_info) == STT_KOS_IDATA)
			addr = (*(ElfW(Addr)(*)(void))(void *)addr)();
		TRACE_RESOLVE_FOR_RELOC(name, addr, symbol->st_size,
		                        self->dm_filename);
		if (ELFW(ST_BIND)(symbol->st_info) != STB_WEAK &&
		    !(self->dm_flags & RTLD_DEEPBIND) &&
		    self == dlglobals_mainapp(&dl_globals)) {
			/* Log a warning when a non-weak symbol from the main
			 * app isn't overwritten  but linked against  itself. */
			syslog(LOG_WARN, "[rtld] Symbol %q at %p+%" PRIuSIZ " linked against itself in %q\n",
			       name, addr, symbol->st_size, self->dm_filename);
		}
		if unlikely(psize)
			*psize = symbol->st_size;
		if unlikely(pmodule)
			*pmodule = self;
	} else {
		REF DlModule *iter, *next;
		uintptr_t hash_elf, hash_gnu;
search_external_symbol:
		name = self->dm_elf.de_dynstr + symbol->st_name;

		/* Search the symbol tables of already loaded modules. */
		hash_elf = hash_gnu = DLMODULE_GETLOCALSYMBOL_HASH_UNSET;
		dlglobals_global_read(&dl_globals);
		iter = TAILQ_FIRST(&dl_globals.dg_globallist);
		for (;;) {
again_search_globals_next:
			assert(iter);
			if (iter == self || unlikely(!tryincref(iter))) {
				iter = TAILQ_NEXT(iter, dm_globals);
				if unlikely(!iter) {
					dlglobals_global_endread(&dl_globals);
					break;
				}
				continue;
			}
			dlglobals_global_endread(&dl_globals);
again_search_globals_module:
			assert(iter != self);
			if (iter == &dl_rtld_module) {
				addr = (ElfW(Addr))dlsym_builtin(name);
				if (addr) {
					if (weak_symbol.ds_mod)
						decref(weak_symbol.ds_mod);
					TRACE_RESOLVE_FOR_RELOC(name, addr, dlsym_builtin_size(name),
					                        dl_rtld_module.dm_filename);
					if unlikely(psize)
						*psize = dlsym_builtin_size(name);
					if unlikely(pmodule)
						*pmodule = &dl_rtld_module;
					goto done;
				}
			} else if (iter->dm_ops) {
				int error;
				size_t symbol_size;
				void *symbol_addr;
				error = (*iter->dm_ops->df_dlsym)(iter, name,
				                                  &symbol_addr,
				                                  &symbol_size);
				if (error >= 0) {
					if (error > 0) {
						if (!weak_symbol.ds_mod) {
							weak_symbol.ds_mod = iter; /* Inherit reference */
							weak_symbol.ds_sym = (ElfW(Sym) const *)symbol_addr;
							weak_symbol.ds_siz = symbol_size;
							dlglobals_global_read(&dl_globals);
							iter = TAILQ_NEXT(iter, dm_globals);
							if unlikely(!iter) {
								dlglobals_global_endread(&dl_globals);
								break;
							}
							goto again_search_globals_next;
						}
					} else {
						/* Found it! */
						if (weak_symbol.ds_mod)
							decref(weak_symbol.ds_mod);
						addr = (ElfW(Addr))symbol_addr;
						TRACE_RESOLVE_FOR_RELOC(name, addr, symbol_size,
						                        iter->dm_filename);
						if unlikely(psize)
							*psize = symbol_size;
						if unlikely(pmodule)
							*pmodule = iter;
						decref(iter);
						goto done;
					}
				}
			} else {
				symbol = DlModule_ElfGetLocalSymbol(iter,
				                                    name,
				                                    &hash_elf,
				                                    &hash_gnu);
				if (symbol && symbol->st_shndx != SHN_UNDEF) {
					if (ELFW(ST_BIND)(symbol->st_info) == STB_WEAK) {
						if (!weak_symbol.ds_mod) {
							weak_symbol.ds_mod = iter; /* Inherit reference */
							weak_symbol.ds_sym = symbol;
							dlglobals_global_read(&dl_globals);
							iter = TAILQ_NEXT(iter, dm_globals);
							if unlikely(!iter) {
								dlglobals_global_endread(&dl_globals);
								break;
							}
							goto again_search_globals_next;
						}
					} else {
						/* Found it! */
						if (weak_symbol.ds_mod)
							decref(weak_symbol.ds_mod);
						addr = symbol->st_value;
						if (symbol->st_shndx != SHN_ABS)
							addr += iter->dm_loadaddr;
						if (ELFW(ST_TYPE)(symbol->st_info) == STT_GNU_IFUNC ||
						    ELFW(ST_TYPE)(symbol->st_info) == STT_KOS_IDATA) {
							TRY {
								addr = (*(ElfW(Addr)(*)(void))(void *)addr)();
							} EXCEPT {
								decref(iter);
								RETHROW();
							}
						}
						TRACE_RESOLVE_FOR_RELOC(name, addr, symbol->st_size,
						                        iter->dm_filename);
						if unlikely(psize)
							*psize = symbol->st_size;
						if unlikely(pmodule)
							*pmodule = iter;
						decref(iter);
						goto done;
					}
				}
			}
			dlglobals_global_read(&dl_globals);
			next = TAILQ_NEXT(iter, dm_globals);
			while (likely(next) && (next == self || unlikely(!tryincref(next))))
				next = TAILQ_NEXT(next, dm_globals);
			dlglobals_global_endread(&dl_globals);
			decref(iter);
			if unlikely(!next)
				break;
			iter = next;
			goto again_search_globals_module;
		}

		/* Search dependencies of the module. */
		{
			size_t depth = 0;
			for (;; ++depth) {
				/* Breadth-first search using a depth counter. */
				unsigned int error;
				error = dlmodule_find_symbol_in_dependencies(self,
				                                             name,
				                                             &hash_elf,
				                                             &hash_gnu,
				                                             paddr,
				                                             psize,
				                                             pmodule,
				                                             &weak_symbol,
				                                             depth);
				if (error == DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_FOUND) {
					if (weak_symbol.ds_mod)
						decref(weak_symbol.ds_mod);
					return true;
				}
				if (error == DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NO_MODULE)
					break;
			}
		}

		if (weak_symbol.ds_mod) {
			size_t symbol_size;
			if (weak_symbol.ds_mod->dm_ops) {
				addr = (ElfW(Addr))weak_symbol.ds_sym;
				symbol_size = weak_symbol.ds_siz;
			} else {
				addr = weak_symbol.ds_sym->st_value;
				if (weak_symbol.ds_sym->st_shndx != SHN_ABS)
					addr += weak_symbol.ds_mod->dm_loadaddr;
				if (ELFW(ST_TYPE)(weak_symbol.ds_sym->st_info) == STT_GNU_IFUNC ||
				    ELFW(ST_TYPE)(weak_symbol.ds_sym->st_info) == STT_KOS_IDATA) {
					TRY {
						addr = (*(ElfW(Addr)(*)(void))(void *)addr)();
					} EXCEPT {
						decref(weak_symbol.ds_mod);
						RETHROW();
					}
				}
				symbol_size = weak_symbol.ds_sym->st_size;
			}
			TRACE_RESOLVE_FOR_RELOC(name, addr, symbol_size,
			                        weak_symbol.ds_mod->dm_filename);
			if unlikely(pmodule)
				*pmodule = weak_symbol.ds_mod;
			if unlikely(psize)
				*psize = symbol_size;
			decref(weak_symbol.ds_mod);
			goto done;
		}

		/* Lastly: Check if the module itself has a valid definition,
		 *         or if the  module allows  for weak  definitions... */
		symbol = self->dm_elf.de_dynsym_tab + symid;
		if (symbol->st_shndx != SHN_UNDEF)
			goto got_local_symbol;
		if (ELFW(ST_BIND)(symbol->st_info) == STB_WEAK) {
			addr = 0;
			if unlikely(psize)
				*psize = symbol->st_size; /* Return 0 instead? */
			if unlikely(pmodule)
				*pmodule = self;
			/* Log a warning when a weak symbol is resolved to NULL. */
			syslog(LOG_WARN, "[rtld] Weak symbol %q resolves to NULL+%" PRIuSIZ " in %q\n",
			       name, symbol->st_size, self->dm_filename);
			goto done;
		}

		/* If the symbol continues to be undefined, set an error. */
		dl_seterrorf("Could not find symbol %q required by %q",
		             name, self->dm_filename);
		return false;
	}
done:
	*paddr = addr;
	return true;
}




#ifdef ELF_ARCH_IS_R_JMP_SLOT
/* Assert  that the offset/info fields of relocation descriptors are at the
 * same location, regardless if the relocation has, or hasn't got an addend */
STATIC_ASSERT(offsetof(Elf32_Rel, r_offset) == offsetof(Elf32_Rela, r_offset));
STATIC_ASSERT(offsetof(Elf64_Rel, r_offset) == offsetof(Elf64_Rela, r_offset));
STATIC_ASSERT(offsetof(Elf32_Rel, r_info) == offsetof(Elf32_Rela, r_info));
STATIC_ASSERT(offsetof(Elf64_Rel, r_info) == offsetof(Elf64_Rela, r_info));

#ifndef ELF_ARCH_NAME_R_JMP_SLOT
#ifdef ELF_ARCH_R_JMP_SLOT
#define ELF_ARCH_NAME_R_JMP_SLOT PP_STR(ELF_ARCH_R_JMP_SLOT)
#else /* ELF_ARCH_R_JMP_SLOT */
#define ELF_ARCH_NAME_R_JMP_SLOT "R_" ELF_EMNAME(ELF_ARCH_MACHINE) "_JMP_SLOT"
#endif /* !ELF_ARCH_R_JMP_SLOT */
#endif /* !ELF_ARCH_NAME_R_JMP_SLOT */

INTERN WUNUSED NONNULL((1)) ElfW(Addr) FCALL
dl_bind_lazy_relocation(DlModule *__restrict self,
#if ELF_ARCH_LAZYINDX
                        uintptr_t jmp_rel_index
#else /* ELF_ARCH_LAZYINDX */
                        uintptr_t jmp_rel_offset
#endif /* !ELF_ARCH_LAZYINDX */
                        )
		THROWS(...) {
	ElfW(Rel) *rel;
	byte_t *reladdr;
	ElfW(Addr) addr;
#ifdef LAZY_TRACE
	DlModule *link_module;
#endif /* LAZY_TRACE */
#if ELF_ARCH_LAZYINDX
	if unlikely(jmp_rel_index >= self->dm_elf.de_jmpcount)
#else /* ELF_ARCH_LAZYINDX */
	if unlikely(jmp_rel_offset >= self->dm_elf.de_jmpsize)
#endif /* !ELF_ARCH_LAZYINDX */
	{
#if ELF_ARCH_LAZYINDX
		syslog(LOG_ERROR, "[rtld] Invalid jmp-relocation index %" PRIuPTR " > %" PRIuSIZ " in %q\n",
		       jmp_rel_index, self->dm_elf.de_jmpcount, self->dm_filename);
#else /* ELF_ARCH_LAZYINDX */
		syslog(LOG_ERROR, "[rtld] Invalid jmp-relocation offset %" PRIuPTR " > %" PRIuSIZ " in %q\n",
		       jmp_rel_offset, self->dm_elf.de_jmpsize, self->dm_filename);
#endif /* !ELF_ARCH_LAZYINDX */
		sys_exit_group(EXIT_FAILURE);
	}
#if ELF_ARCH_LAZYINDX
#if ELF_ARCH_USESRELA
	rel = (ElfW(Rel) *)((uintptr_t)self->dm_elf.de_jmprel +
	                    (self->dm_flags & RTLD_JMPRELA
	                     ? (jmp_rel_index * sizeof(ElfW(Rela)))
	                     : (jmp_rel_index * sizeof(ElfW(Rel)))));
#else /* ELF_ARCH_USESRELA */
	rel = (ElfW(Rel) *)((uintptr_t)self->dm_elf.de_jmprel +
	                    (jmp_rel_index * sizeof(ElfW(Rel))));
#endif /* !ELF_ARCH_USESRELA */
#else /* ELF_ARCH_LAZYINDX */
	rel = (ElfW(Rel) *)((uintptr_t)self->dm_elf.de_jmprel + jmp_rel_offset);
#endif /* !ELF_ARCH_LAZYINDX */
	if unlikely(!ELF_ARCH_IS_R_JMP_SLOT(ELFW(R_TYPE)(rel->r_info))) {
		syslog(LOG_ERROR, "[rtld] Invalid jmp-relocation at DT_JMPREL+%" PRIuSIZ " (index:%" PRIuPTR ") "
		                  "[r_offset=%#" PRIxPTR ",r_info=%#" PRIxPTR
#if !ELF_ARCH_USESRELA
		                  "] isn't `" ELF_ARCH_NAME_R_JMP_SLOT "' in %q\n"
#endif /* !ELF_ARCH_USESRELA */
		       ,
#if ELF_ARCH_LAZYINDX
		       (size_t)((byte_t *)rel - (byte_t *)self->dm_elf.de_jmprel),
		       jmp_rel_index,
#else /* ELF_ARCH_LAZYINDX */
		       (size_t)jmp_rel_offset,
#if ELF_ARCH_USESRELA
		       self->dm_flags & RTLD_JMPRELA ? (uintptr_t)((ElfW(Rela) *)rel - self->dm_elf.de_jmprela)
		                                     : (uintptr_t)(rel - self->dm_elf.de_jmprel),
#else /* ELF_ARCH_USESRELA */
		       (uintptr_t)(rel - self->dm_elf.de_jmprel),
#endif /* ELF_ARCH_USESRELA */
#endif /* !ELF_ARCH_LAZYINDX */
		       (uintptr_t)rel->r_offset,
		       (uintptr_t)rel->r_info
#if !ELF_ARCH_USESRELA
		       ,
		       self->dm_filename
#endif /* !ELF_ARCH_USESRELA */
		       );
#if ELF_ARCH_USESRELA
		if (self->dm_flags & RTLD_JMPRELA)
			syslog(LOG_ERROR, ",r_addend=%" PRIdPTR, (intptr_t)((ElfW(Rela) *)rel)->r_addend);
		syslog(LOG_ERROR, "] isn't `" ELF_ARCH_NAME_R_JMP_SLOT "' in %q\n", self->dm_filename);
#endif /* ELF_ARCH_USESRELA */
		sys_exit_group(EXIT_FAILURE);
	}
	reladdr = (byte_t *)self->dm_loadaddr + rel->r_offset;
	/* Resolve the symbol now. */
#ifdef LAZY_TRACE
	if unlikely(!DlModule_ElfFindSymbol(self, ELFW(R_SYM)(rel->r_info), &addr,
	                                    NULL, &link_module))
#else /* LAZY_TRACE */
	if unlikely(!DlModule_ElfFindSymbol(self, ELFW(R_SYM)(rel->r_info), &addr,
	                                    NULL, NULL))
#endif /* !LAZY_TRACE */
	{
		ElfW(Sym) const *sym = self->dm_elf.de_dynsym_tab + ELFW(R_SYM)(rel->r_info);
		char const *symname  = self->dm_elf.de_dynstr + sym->st_name;
		syslog(LOG_ERROR, "[rtld] Unable to resolve symbol %q in %q\n",
		       symname, self->dm_filename);
		/* If STDERR is  a tty,  also print the  error message  there.
		 * Don't  do so  when STDERR  is something  different (such as
		 * a file) in order to  not accidentally inject an  unexpected
		 * error message into an error stream that wouldn't understand
		 * such an error. */
		{
			struct termios ios;
			if (sys_ioctl(STDERR_FILENO, TCGETA, &ios) >= 0) {
				sys_write(STDERR_FILENO, "DL: ", 4);
				sys_write(STDERR_FILENO, "Unresolved symbol '", 19);
				sys_write(STDERR_FILENO, symname, strlen(symname));
				sys_write(STDERR_FILENO, "' in '", 6);
				sys_write(STDERR_FILENO, self->dm_filename, strlen(self->dm_filename));
				sys_write(STDERR_FILENO, "'\n", 2);
			}
		}
		sys_exit_group(EXIT_FAILURE);
	}
#if ELF_ARCH_USESRELA
	/* Extend the relocation result with its addend */
	if (self->dm_flags & RTLD_JMPRELA)
		addr += ((ElfW(Rela) *)rel)->r_addend;
#endif /* ELF_ARCH_USESRELA */
#ifdef LAZY_TRACE
	syslog(LOG_DEBUG, "[rtld] Lazy resolve %q in %q (to %p from %q)\n",
	       self->dm_elf.de_dynstr + self->dm_elf.de_dynsym_tab[ELFW(R_SYM)(rel->r_info)].st_name,
	       self->dm_filename, addr, link_module->dm_filename);
#endif /* LAZY_TRACE */
	*(ElfW(Addr) *)reladdr = addr;
	return addr;
}
#endif /* ELF_ARCH_IS_R_JMP_SLOT */

DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_DlModule_ApplyRelocations
#include "module-reloc-impl.c.inl"
#if ELF_ARCH_USESRELA
#define DEFINE_DlModule_ApplyRelocationsWithAddend
#include "module-reloc-impl.c.inl"
#endif /* ELF_ARCH_USESRELA */
#endif /* !__INTELLISENSE__ */


#endif /* !GUARD_LIBDL_MODULE_RELOC_C */
