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
#ifndef GUARD_LIBDL_MODULE_RELOC_C
#define GUARD_LIBDL_MODULE_RELOC_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

/* Keep this one the first */
#include "elf.h"
/**/

#include <hybrid/typecore.h>

#include <kos/exec/peb.h> /* struct process_peb */
#include <kos/syscalls.h>

#include <elf.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

DECL_BEGIN

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) ElfW(Word) CC
builtin_symbol_size(char const *__restrict name) {
	if (!strcmp(name, "program_invocation_name"))
		return sizeof(void *);
	if (!strcmp(name, "program_invocation_short_name"))
		return sizeof(void *);
	if (*name == '_') {
		++name;
		if (!strcmp(name, "pgmptr"))
			return sizeof(void *);
		if (*name == '_') {
			++name;
			if (!strcmp(name, "peb"))
				return sizeof(struct process_peb);
			if (!strcmp(name, "argc"))
				return sizeof(size_t);
			if (!strcmp(name, "argv"))
				return sizeof(void *);
			if (!strcmp(name, "progname"))
				return sizeof(void *);
			if (!strcmp(name, "progname_full"))
				return sizeof(void *);
		}
	}
	if (!strcmp(name, "environ"))
		return sizeof(void *);
	return 0;
}

#define DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NOT_FOUND 0
#define DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_FOUND     1
#define DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NO_MODULE 2
PRIVATE NONNULL((2)) unsigned int LIBCCALL
dlmodule_find_symbol_in_dependencies(DlModule *__restrict self,
                                     char const *__restrict name,
                                     uintptr_t *__restrict phash_elf,
                                     uintptr_t *__restrict phash_gnu,
                                     ElfW(Addr) *__restrict presult,
                                     ElfW(Word) *psize,
                                     DlModule **pmodule,
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
			error = dlmodule_find_symbol_in_dependencies(self->dm_depvec[i],
			                                             name,
			                                             phash_elf,
			                                             phash_gnu,
			                                             presult,
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
		if (symbol.ds_mod == &ld_rtld_module) {
			/* Special case: Search the RTLD module itself. */
			void *addr;
			addr = dlsym_builtin(name);
			if (addr) {
				*presult = (ElfW(Addr))addr;
				if unlikely(psize)
					*psize = builtin_symbol_size(name);
				if unlikely(pmodule)
					*pmodule = &ld_rtld_module;
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
				if (!pweak_symbol->ds_mod) {
					DlModule_Incref(symbol.ds_mod);
					*pweak_symbol = symbol;
				}
			} else {
				/* Found the real, actual symbol! */
				ElfW(Addr) result;
				result = symbol.ds_sym->st_value;
				if (symbol.ds_sym->st_shndx != SHN_ABS)
					result += symbol.ds_mod->dm_loadaddr;
				if (ELFW(ST_TYPE)(symbol.ds_sym->st_info) == STT_GNU_IFUNC) {
					TRY {
						result = (*(ElfW(Addr)(*)(void))(void *)result)();
					} EXCEPT {
						if (pweak_symbol->ds_mod)
							DlModule_Decref(pweak_symbol->ds_mod);
						RETHROW();
					}
				}
				*presult = result;
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


PRIVATE ATTR_NOINLINE bool CC
DlModule_FindSymbol(DlModule *__restrict self, uintptr_t symid,
                    ElfW(Addr) *__restrict presult,
                    ElfW(Word) *psize,
                    DlModule **pmodule) {
	struct dl_symbol weak_symbol;
	ElfW(Sym) const *symbol;
	ElfW(Addr) result;
	char *name;
	weak_symbol.ds_mod = NULL;
	symbol             = self->dm_dynsym_tab + symid;
	if ((symbol->st_shndx != SHN_UNDEF) && (self->dm_flags & RTLD_DEEPBIND)) {
		/* Symbol has been defined locally. */
		if (ELFW(ST_BIND)(symbol->st_info) == STB_WEAK) {
			weak_symbol.ds_mod = self;
			weak_symbol.ds_sym = symbol;
			DlModule_Incref(self);
			goto search_external_symbol;
		}
got_local_symbol:
		result = symbol->st_value;
		if (symbol->st_shndx != SHN_ABS)
			result += self->dm_loadaddr;
		if (ELFW(ST_TYPE)(symbol->st_info) == STT_GNU_IFUNC)
			result = (*(ElfW(Addr)(*)(void))(void *)result)();
		if unlikely(psize)
			*psize = symbol->st_size;
		if unlikely(pmodule)
			*pmodule = self;
	} else {
		REF DlModule *iter, *next;
		uintptr_t hash_elf, hash_gnu;
search_external_symbol:
		name = self->dm_dynstr + symbol->st_name;

		/* Search the symbol tables of already loaded modules. */
		hash_elf = hash_gnu = DLMODULE_GETLOCALSYMBOL_HASH_UNSET;
		atomic_rwlock_read(&DlModule_GlobalLock);
		iter = DlModule_GlobalList;
		for (;;) {
again_search_globals_next:
			assert(iter);
			if (iter == self || unlikely(!DlModule_TryIncref(iter))) {
				iter = iter->dm_globals.ln_next;
				if unlikely(!iter) {
					atomic_rwlock_endread(&DlModule_GlobalLock);
					break;
				}
				continue;
			}
			atomic_rwlock_endread(&DlModule_GlobalLock);
again_search_globals_module:
			assert(iter != self);
			if (iter == &ld_rtld_module) {
				result = (ElfW(Addr))dlsym_builtin(name);
				if (result) {
					if (weak_symbol.ds_mod)
						DlModule_Decref(weak_symbol.ds_mod);
					if unlikely(psize)
						*psize = builtin_symbol_size(name);
					if unlikely(pmodule)
						*pmodule = &ld_rtld_module;
					goto done_result;
				}
			} else {
				symbol = DlModule_GetLocalSymbol(iter,
				                                 name,
				                                 &hash_elf,
				                                 &hash_gnu);
				if (symbol && symbol->st_shndx != SHN_UNDEF) {
					if (ELFW(ST_BIND)(symbol->st_info) == STB_WEAK) {
						if (!weak_symbol.ds_mod) {
							weak_symbol.ds_mod = iter; /* Inherit reference */
							weak_symbol.ds_sym = symbol;
							atomic_rwlock_read(&DlModule_GlobalLock);
							iter = iter->dm_globals.ln_next;
							if unlikely(!iter) {
								atomic_rwlock_endread(&DlModule_GlobalLock);
								break;
							}
							goto again_search_globals_next;
						}
					} else {
						/* Found it! */
						if (weak_symbol.ds_mod)
							DlModule_Decref(weak_symbol.ds_mod);
						result = symbol->st_value;
						if (symbol->st_shndx != SHN_ABS)
							result += iter->dm_loadaddr;
						if (ELFW(ST_TYPE)(symbol->st_info) == STT_GNU_IFUNC) {
							TRY {
								result = (*(ElfW(Addr)(*)(void))(void *)result)();
							} EXCEPT {
								DlModule_Decref(iter);
								RETHROW();
							}
						}
						if unlikely(psize)
							*psize = symbol->st_size;
						if unlikely(pmodule)
							*pmodule = iter;
						DlModule_Decref(iter);
						goto done_result;
					}
				}
			}
			atomic_rwlock_read(&DlModule_GlobalLock);
			next = iter->dm_globals.ln_next;
			while (likely(next) && (next == self || unlikely(!DlModule_TryIncref(next))))
				next = next->dm_globals.ln_next;
			atomic_rwlock_endread(&DlModule_GlobalLock);
			DlModule_Decref(iter);
			if unlikely(!next)
				break;
			iter = next;
			goto again_search_globals_module;
		}

		/* Search dependencies of the module. */
		{
			size_t depth = 0;
			unsigned int error;
			for (;; ++depth) {
				/* Breadth-first search using a depth counter. */
				error = dlmodule_find_symbol_in_dependencies(self,
				                                             name,
				                                             &hash_elf,
				                                             &hash_gnu,
				                                             presult,
				                                             psize,
				                                             pmodule,
				                                             &weak_symbol,
				                                             depth);
				if (error == DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_FOUND) {
					if (weak_symbol.ds_mod)
						DlModule_Decref(weak_symbol.ds_mod);
					return true;
				}
				if (error == DLMODULE_SEARCH_SYMBOL_IN_DEPENDENCIES_NO_MODULE)
					break;
			}
		}

		if (weak_symbol.ds_mod) {
			result = weak_symbol.ds_sym->st_value;
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
			if unlikely(psize)
				*psize = weak_symbol.ds_sym->st_size;
			if unlikely(pmodule)
				*pmodule = weak_symbol.ds_mod;
			DlModule_Decref(weak_symbol.ds_mod);
			goto done_result;
		}

		/* Lastly: Check if the module itself has a valid definition... */
		symbol = self->dm_dynsym_tab + symid;
		if (symbol->st_shndx != SHN_UNDEF)
			goto got_local_symbol;

		/* If the symbol continues to be undefined, set an error. */
		elf_setdlerrorf("Could not find symbol %q required by %q", name, self->dm_filename);
		return false;
	}
done_result:
	*presult = result;
	return true;
}




#ifdef R_JMP_SLOT
#undef LAZY_TRACE
#if 1
#define LAZY_TRACE 1
#endif

/* Assert that the offset/info fields of relocation descriptors are at the
 * same location, regardless if the relocation has, or hasn't got an addend */
STATIC_ASSERT(offsetof(Elf32_Rel, r_offset) == offsetof(Elf32_Rela, r_offset));
STATIC_ASSERT(offsetof(Elf64_Rel, r_offset) == offsetof(Elf64_Rela, r_offset));
STATIC_ASSERT(offsetof(Elf32_Rel, r_info) == offsetof(Elf32_Rela, r_info));
STATIC_ASSERT(offsetof(Elf64_Rel, r_info) == offsetof(Elf64_Rela, r_info));


INTERN ElfW(Addr) ATTR_FASTCALL
libdl_bind_lazy_relocation(DlModule *__restrict self,
                           uintptr_t jmp_rel_offset) {
	ElfW(Rel) *rel;
	byte_t *reladdr;
	ElfW(Addr) result;
#ifdef LAZY_TRACE
	DlModule *link_module;
#endif /* LAZY_TRACE */
	if unlikely(jmp_rel_offset >= self->dm_jmpsize) {
		syslog(LOG_ERROR, "[ld] Invalid jmp-relocation offset %Iu > %Iu in %q\n",
		       jmp_rel_offset, self->dm_jmpsize, self->dm_filename);
		sys_exit_group(EXIT_FAILURE);
	}
	rel = (ElfW(Rel) *)((uintptr_t)self->dm_jmprel + jmp_rel_offset);
	if unlikely(ELFW(R_TYPE)(rel->r_info) != R_JMP_SLOT) {
#ifdef ELF_HOST_RELA_UNUSED
		syslog(LOG_ERROR, "[ld] Invalid jmp-relocation at DT_JMPREL+%Iu "
		                  "[r_offset=%#Ix,r_info=%#I32x] isn't `" PP_PRIVATE_STR(R_JMP_SLOT) "' in %q\n",
		       jmp_rel_offset, rel->r_offset, rel->r_info, self->dm_filename);
#else /* ELF_HOST_RELA_UNUSED */
		syslog(LOG_ERROR, "[ld] Invalid jmp-relocation at DT_JMPREL+%Iu "
		                  "[r_offset=%#Ix,r_info=%#I32x",
		       jmp_rel_offset, rel->r_offset, rel->r_info);
		if (self->dm_flags & RTLD_JMPRELA)
			syslog(LOG_ERROR, ",r_addend=%Id\n", (ssize_t)((ElfW(Rela) *)rel)->r_addend);
		syslog(LOG_ERROR, "] isn't `" PP_PRIVATE_STR(R_JMP_SLOT) "' in %q\n", self->dm_filename);
#endif /* !ELF_HOST_RELA_UNUSED */
		sys_exit_group(EXIT_FAILURE);
	}
	reladdr = (byte_t *)self->dm_loadaddr + rel->r_offset;
	/* Resolve the symbol now. */
#ifdef LAZY_TRACE
	if unlikely(!DlModule_FindSymbol(self, ELFW(R_SYM)(rel->r_info), &result,
	                                 NULL, &link_module))
#else /* LAZY_TRACE */
	if unlikely(!DlModule_FindSymbol(self, ELFW(R_SYM)(rel->r_info), &result,
	                                 NULL, NULL))
#endif /* !LAZY_TRACE */
	{
		ElfW(Sym) *sym = self->dm_dynsym_tab + ELFW(R_SYM)(rel->r_info);
		syslog(LOG_ERROR, "[ld] Unable to resolve symbol %q in %q\n",
		       self->dm_dynstr + sym->st_name,
		       self->dm_filename);
		sys_exit_group(EXIT_FAILURE);
	}
#ifndef ELF_HOST_RELA_UNUSED
	/* Extend the relocation result with its addend */
	if (self->dm_flags & RTLD_JMPRELA)
		result += ((ElfW(Rela) *)rel)->r_addend;
#endif /* !ELF_HOST_RELA_UNUSED */
#ifdef LAZY_TRACE
	syslog(LOG_DEBUG, "[ld] Lazy resolve %q in %q (to %p from %q)\n",
	       self->dm_dynstr + self->dm_dynsym_tab[ELFW(R_SYM)(rel->r_info)].st_name,
	       self->dm_filename, result, link_module->dm_filename);
#endif /* LAZY_TRACE */
	*(ElfW(Addr) *)reladdr = result;
	return result;
}
#endif /* R_JMP_SLOT */

DECL_END

#ifndef __INTELLISENSE__
#undef APPLY_RELA
#include "module-reloc-impl.c.inl"
#ifndef ELF_HOST_RELA_UNUSED
#define APPLY_RELA 1
#include "module-reloc-impl.c.inl"
#endif /* !ELF_HOST_RELA_UNUSED */
#endif /* !__INTELLISENSE__ */


#endif /* !GUARD_LIBDL_MODULE_RELOC_C */
