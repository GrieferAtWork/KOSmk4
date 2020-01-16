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
#ifndef GUARD_LIBDL_MODULE_INIT_C
#define GUARD_LIBDL_MODULE_INIT_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

/* Keep this one the first */
#include "dl.h"
/**/

#include <kos/debugtrap.h>
#include <kos/exec/peb.h>
#include <kos/exec/elf.h> /* ELF_ARCH_USESRELA */
#include <kos/syscalls.h>
#include <sys/mman.h>

#include <errno.h>
#include <malloc.h>
#include <signal.h>
#include <syslog.h>


DECL_BEGIN

LOCAL NONNULL((1)) void CC try_add2global(DlModule *__restrict self) {
	uintptr_t old_flags;
again_old_flags:
	old_flags = ATOMIC_READ(self->dm_flags);
	if (!(old_flags & RTLD_GLOBAL)) {
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


/* [1..1][const] The library path set when the program was started */
INTERN char *dl_library_path = NULL;


/* Run library initializers for `self' */
PRIVATE NONNULL((1)) void CC
DlModule_ElfRunInitializers(DlModule *__restrict self) {
	uint16_t dyni;
	size_t i;
	uintptr_t init_func           = 0;
	uintptr_t *preinit_array_base = NULL;
	size_t preinit_array_size     = 0;
	uintptr_t *init_array_base    = NULL;
	size_t init_array_size        = 0;
	for (dyni = 0; dyni < self->dm_elf.de_dyncnt; ++dyni) {
		switch (self->dm_elf.de_dynhdr[dyni].d_tag) {
		case DT_NULL:
			goto done_dyntag;
		case DT_INIT:
			init_func = (uintptr_t)self->dm_elf.de_dynhdr[dyni].d_un.d_ptr;
			break;
		case DT_PREINIT_ARRAY:
			preinit_array_base = (uintptr_t *)(self->dm_loadaddr +
			                                   self->dm_elf.de_dynhdr[dyni].d_un.d_ptr);
			break;
		case DT_PREINIT_ARRAYSZ:
			preinit_array_size = (size_t)self->dm_elf.de_dynhdr[dyni].d_un.d_val / sizeof(void (*)(void));
			break;
		case DT_INIT_ARRAY:
			init_array_base = (uintptr_t *)(self->dm_loadaddr +
			                                self->dm_elf.de_dynhdr[dyni].d_un.d_ptr);
			break;
		case DT_INIT_ARRAYSZ:
			init_array_size = (size_t)self->dm_elf.de_dynhdr[dyni].d_un.d_val / sizeof(void (*)(void));
			break;
		default: break;
		}
	}
done_dyntag:
	for (i = 0; i < preinit_array_size; ++i) {
		(*(void (*)(void))(preinit_array_base[i] /* + self->dm_loadaddr*/))();
	}
	/* Service a init function, if one was specified. */
	if (init_func)
		(*(void (*)(void))(init_func + self->dm_loadaddr))();
	/* Service init-array functions in forward order. */
	for (i = 0; i < init_array_size; ++i) {
		(*(void (*)(void))(init_array_base[i] /* + self->dm_loadaddr*/))();
	}
}

/* Invoke the static initializers of all currently loaded modules.
 * This is called late during initial module startup once the initial
 * set of libraries, + the initial application have been loaded.
 * Note that initializers are invoked in reverse order of those modules
 * appearing within `DlModule_AllList', meaning that the primary
 * application's __attribute__((constructor)) functions are invoked
 * _AFTER_ those from (e.g.) libc. */
INTERN void CC DlModule_RunAllStaticInitializers(void) {
	REF DlModule *primary;
	DlModule *last;
	primary = DlModule_GlobalList;
	assert(primary != &dl_rtld_module);
	DlModule_Incref(primary);
again_search_noinit:
	atomic_rwlock_read(&DlModule_GlobalLock);
	last = primary;
	while (last->dm_globals.ln_next != NULL)
		last = last->dm_globals.ln_next;
	while (!(last->dm_flags & RTLD_NOINIT)) {
		if (last == primary) {
			atomic_rwlock_endread(&DlModule_GlobalLock);
			goto done;
		}
		last = LLIST_PREV(DlModule, last, dm_globals);
	}
	assert(last != &dl_rtld_module);
	last->dm_flags &= ~RTLD_NOINIT;
	DlModule_Incref(last);
	atomic_rwlock_endread(&DlModule_GlobalLock);
	/* TODO: Support for formats other than ELF. */
#if 1 /* This is called during init. - If an exception happens here, it wouldn't even matter... */
	DlModule_ElfRunInitializers(last);
#else
	TRY {
		DlModule_ElfRunInitializers(last);
	} EXCEPT {
		DlModule_Decref(last);
		DlModule_Decref(primary);
		RETHROW();
	}
#endif
	DlModule_Decref(last);
	if (last != primary)
		goto again_search_noinit;
done:
	DlModule_Decref(primary);
}


#if PF_X == PROT_EXEC && PF_W == PROT_WRITE && PF_R == PROT_READ
#define ELF_PF_FLAGS_TO_PROT_FLAGS(x) ((x) & (PF_X | PF_W | PF_R))
#else /* PF_* == PROT_* */
#define ELF_PF_FLAGS_TO_PROT_FLAGS(x)        \
	(((x) & PF_X ? PROT_EXEC : PROT_NONE) |  \
	 ((x) & PF_W ? PROT_WRITE : PROT_NONE) | \
	 ((x) & PF_R ? PROT_READ : PROT_NONE))
#define ELF_PF_FLAGS_TO_PROT_FLAGS_PLUS_WRITE(x) \
	(((x) & PF_X ? PROT_EXEC : PROT_NONE) |      \
	 ((x) & PF_R ? PROT_READ : PROT_NONE) | PROT_WRITE)
#endif /* PF_* != PROT_* */
#ifndef ELF_PF_FLAGS_TO_PROT_FLAGS_PLUS_WRITE
#define ELF_PF_FLAGS_TO_PROT_FLAGS_PLUS_WRITE(x) \
	(ELF_PF_FLAGS_TO_PROT_FLAGS(x) | PROT_WRITE)
#endif /* !ELF_PF_FLAGS_TO_PROT_FLAGS_PLUS_WRITE */


PRIVATE NONNULL((1)) int CC
DlModule_ElfMakeTextWritable(DlModule *__restrict self) {
	ElfW(Half) i;
	errno_t error;
	for (i = 0; i < self->dm_elf.de_phnum; ++i) {
		if (self->dm_elf.de_phdr[i].p_type != PT_LOAD)
			continue;
		if (self->dm_elf.de_phdr[i].p_flags & PF_W)
			continue; /* Already writable */
		error = sys_mprotect((void *)(self->dm_elf.de_phdr[i].p_vaddr + self->dm_loadaddr),
		                     self->dm_elf.de_phdr[i].p_memsz,
		                     ELF_PF_FLAGS_TO_PROT_FLAGS_PLUS_WRITE(self->dm_elf.de_phdr[i].p_flags));
		if unlikely(E_ISERR(error))
			goto err_mprotect_failed;
	}
	return 0;
err_mprotect_failed:
	return dl_seterrorf("%q: Failed to make text writable (errno=%d)",
	                       self->dm_filename, -error);
}

PRIVATE NONNULL((1)) void CC
DlModule_ElfMakeTextReadonly(DlModule *__restrict self) {
	ElfW(Half) i;
	for (i = 0; i < self->dm_elf.de_phnum; ++i) {
		if (self->dm_elf.de_phdr[i].p_type != PT_LOAD)
			continue;
		if (self->dm_elf.de_phdr[i].p_flags & PF_W)
			continue; /* Already writable */
		sys_mprotect((void *)(self->dm_elf.de_phdr[i].p_vaddr + self->dm_loadaddr),
		             self->dm_elf.de_phdr[i].p_memsz,
		             ELF_PF_FLAGS_TO_PROT_FLAGS(self->dm_elf.de_phdr[i].p_flags));
	}
}

/* Apply relocations & execute library initialized within `self'
 * @param: flags: Set of `DL_MODULE_INITIALIZE_F*' */
INTERN NONNULL((1)) int CC
DlModule_ElfInitialize(DlModule *__restrict self, unsigned int flags) {
#if ELF_ARCH_USESRELA
	ElfW(Rela) *rela_base = NULL;
	size_t rela_count   = 0;
	bool jmp_rels_have_addend = false;
#endif /* ELF_ARCH_USESRELA */
	ElfW(Rel) *rel_base = NULL;
	size_t rel_count  = 0;
	ElfW(Rel) *jmp_base = NULL;
	size_t jmp_size  = 0;
	size_t i;
	/* Load dependencies of the module. */
	if (self->dm_depcnt) {
		unsigned int dep_flags;
		size_t count    = self->dm_depcnt;
		self->dm_depcnt = 0;
		self->dm_depvec = (REF DlModule **)malloc(count * sizeof(REF DlModule *));
		if unlikely(!self->dm_depvec)
			goto err_nomem;
		dep_flags = RTLD_GLOBAL | (self->dm_flags & RTLD_NOINIT);
		for (i = 0; i < self->dm_elf.de_dyncnt; ++i) {
			char *filename;
			REF DlModule *dependency;
			if (self->dm_elf.de_dynhdr[i].d_tag == DT_NULL)
				break;
			if (self->dm_elf.de_dynhdr[i].d_tag != DT_NEEDED)
				continue;
			assert(self->dm_depcnt < count);
			filename = self->dm_elf.de_dynstr + self->dm_elf.de_dynhdr[i].d_un.d_ptr;
			/* Load the dependent library. */
			if (self->dm_elf.de_runpath) {
				dependency = DlModule_OpenFilenameInPathList(self->dm_elf.de_runpath,
				                                             filename,
				                                             dep_flags);
				if (!dependency && ATOMIC_READ(dl_error_message) == NULL) {
					/* Before doing more open() system calls, check to see if we've
					 * already loaded a matching candidate of this library!
					 * We can do this because `dl_library_path' never changes. */
					dependency = DlModule_FindFilenameInPathListFromAll(filename);
					if (!dependency) {
						dependency = DlModule_OpenFilenameInPathList(dl_library_path,
						                                             filename,
						                                             dep_flags);
					} else {
						try_add2global(dependency);
					}
				}
			} else {
				/* Before doing more open() system calls, check to see if we've
				 * already loaded a matching candidate of this library!
				 * We can do this because `dl_library_path' never changes. */
				dependency = DlModule_FindFilenameInPathListFromAll(filename);
				if (!dependency) {
					dependency = DlModule_OpenFilenameInPathList(dl_library_path,
					                                             filename,
					                                             dep_flags);
				} else {
					try_add2global(dependency);
				}
			}
			if (!dependency) {
				if (ATOMIC_READ(dl_error_message) == NULL)
					dl_seterrorf("Failed to load dependency %q of %q", filename, self->dm_filename);
				goto err;
			}
			self->dm_depvec[self->dm_depcnt++] = dependency;
		}
	}
	/* Service relocations of the module. */
	for (i = 0; i < self->dm_elf.de_dyncnt; ++i) {
		ElfW(Dyn) tag = self->dm_elf.de_dynhdr[i];
		switch (tag.d_tag) {

		case DT_NULL:
			goto done_dynamic;

		case DT_TEXTREL:
			flags |= DL_MODULE_ELF_INITIALIZE_FTEXTREL;
			break;

		case DT_BIND_NOW:
			flags |= DL_MODULE_ELF_INITIALIZE_FBINDNOW;
			break;

		case DT_FLAGS:
			if (tag.d_un.d_val & DF_SYMBOLIC)
				self->dm_flags |= RTLD_DEEPBIND;
			if (tag.d_un.d_val & DF_TEXTREL)
				flags |= DL_MODULE_ELF_INITIALIZE_FTEXTREL;
			if (tag.d_un.d_val & DF_BIND_NOW)
				flags |= DL_MODULE_ELF_INITIALIZE_FBINDNOW;
			break;

		case DT_SYMBOLIC:
			self->dm_flags |= RTLD_DEEPBIND;
			break;

		case DT_REL:
			rel_base = (ElfW(Rel) *)(self->dm_loadaddr + tag.d_un.d_ptr);
			break;

		case DT_RELSZ:
			rel_count = tag.d_un.d_val / sizeof(ElfW(Rel));
			break;

		case DT_JMPREL:
			jmp_base = (ElfW(Rel) *)(self->dm_loadaddr + tag.d_un.d_ptr);
			break;

		case DT_PLTRELSZ:
			jmp_size = tag.d_un.d_val;
			break;

		case DT_PLTGOT:
			self->dm_elf.de_pltgot = (ElfW(Addr) *)(self->dm_loadaddr + tag.d_un.d_ptr);
			break;

		case DT_FLAGS_1:
			if (tag.d_un.d_val & DF_1_NOW)
				flags |= DL_MODULE_ELF_INITIALIZE_FBINDNOW;
			if (tag.d_un.d_val & DF_1_GLOBAL) {
				if (!(self->dm_flags & RTLD_GLOBAL)) {
					atomic_rwlock_write(&DlModule_GlobalLock);
					self->dm_flags |= RTLD_GLOBAL;
					if (!self->dm_globals.ln_pself)
						DlModule_AddToGlobals(self);
					atomic_rwlock_endwrite(&DlModule_GlobalLock);
				}
			}
			if (tag.d_un.d_val & DF_1_NODELETE)
				self->dm_flags |= RTLD_NODELETE;
			break;

#if ELF_ARCH_USESRELA
		case DT_RELA:
			rela_base = (ElfW(Rela) *)(self->dm_loadaddr + tag.d_un.d_ptr);
			break;

		case DT_RELASZ:
			rela_count = tag.d_un.d_val / sizeof(ElfW(Rela));
			break;

		case DT_PLTREL:
			if (tag.d_un.d_val == DT_RELA)
				jmp_rels_have_addend = true;
			break;
#endif /* ELF_ARCH_USESRELA */

		default: break;
		}
	}
done_dynamic:
	if (flags & DL_MODULE_ELF_INITIALIZE_FTEXTREL) {
		/* Make all sections writable! */
		if unlikely(DlModule_ElfMakeTextWritable(self))
			goto err;
	}

#ifdef ELF_ARCH_IS_R_JMP_SLOT
	/* Enable direct binding when `LD_BIND_NOW' is defined as non-empty */
	{
		char *ld_bind_now;
		ld_bind_now = process_peb_getenv(root_peb, "LD_BIND_NOW");
		if (ld_bind_now && *ld_bind_now)
			flags |= DL_MODULE_ELF_INITIALIZE_FBINDNOW;
	}
#endif /* ELF_ARCH_IS_R_JMP_SLOT */

	/* Apply relocations. */
	if unlikely(DlModule_ApplyRelocations(self, rel_base, rel_count,
	                                      flags | DL_MODULE_ELF_INITIALIZE_FBINDNOW))
		goto err;
#if ELF_ARCH_USESRELA
	if unlikely(DlModule_ApplyRelocationsWithAddend(self, rela_base, rela_count,
		                                            flags | DL_MODULE_ELF_INITIALIZE_FBINDNOW))
		goto err;
#endif /* !ELF_ARCH_USESRELA */

	if (jmp_size) {
#if ELF_ARCH_USESRELA
		if (jmp_rels_have_addend) {
#ifdef ELF_ARCH_IS_R_JMP_SLOT
			if (self->dm_elf.de_pltgot && !(flags & DL_MODULE_ELF_INITIALIZE_FBINDNOW)) {
				/* Lazy binding of jump-relocations! */
				self->dm_elf.de_pltgot[1] = (ElfW(Addr))self;
				self->dm_elf.de_pltgot[2] = (ElfW(Addr))&dl_load_lazy_relocation;
				self->dm_elf.de_jmprela   = (ElfW(Rela) *)jmp_base;
#if ELF_ARCH_LAZYINDX
				self->dm_elf.de_jmpcount  = jmp_size / sizeof(ElfW(Rela));
#else /* ELF_ARCH_LAZYINDX */
				self->dm_elf.de_jmpsize   = jmp_size;
#endif /* !ELF_ARCH_LAZYINDX */
				self->dm_flags    |= RTLD_JMPRELA;
				if unlikely(DlModule_ApplyRelocationsWithAddend(self, (ElfW(Rela) *)jmp_base,
				                                                jmp_size / sizeof(ElfW(Rela)),
				                                                flags))
					goto err;
			} else
#endif /* ELF_ARCH_IS_R_JMP_SLOT */
			{
				/* Directly bind jump-relocations. */
				if unlikely(DlModule_ApplyRelocationsWithAddend(self, (ElfW(Rela) *)jmp_base,
				                                                jmp_size / sizeof(ElfW(Rela)),
				                                                flags | DL_MODULE_ELF_INITIALIZE_FBINDNOW))
					goto err;
			}
		} else
#endif /* ELF_ARCH_USESRELA */
		{
#ifdef ELF_ARCH_IS_R_JMP_SLOT
			if (self->dm_elf.de_pltgot && !(flags & DL_MODULE_ELF_INITIALIZE_FBINDNOW)) {
				/* Lazy binding of jump-relocations! */
				self->dm_elf.de_pltgot[1] = (ElfW(Addr))self;
				self->dm_elf.de_pltgot[2] = (ElfW(Addr))&dl_load_lazy_relocation;
				self->dm_elf.de_jmprel    = jmp_base;
#if ELF_ARCH_LAZYINDX
				self->dm_elf.de_jmpcount  = jmp_size / sizeof(ElfW(Rel));
#else /* ELF_ARCH_LAZYINDX */
				self->dm_elf.de_jmpsize   = jmp_size;
#endif /* !ELF_ARCH_LAZYINDX */
				if unlikely(DlModule_ApplyRelocations(self, jmp_base,
				                                      jmp_size / sizeof(ElfW(Rel)),
				                                      flags))
					goto err;
			} else
#endif /* ELF_ARCH_IS_R_JMP_SLOT */
			{
				/* Directly bind jump-relocations. */
				if unlikely(DlModule_ApplyRelocations(self, jmp_base,
				                                      jmp_size / sizeof(ElfW(Rel)),
				                                      flags | DL_MODULE_ELF_INITIALIZE_FBINDNOW))
					goto err;
			}
		}
	}

	/* Remove writable from read-only sections! */
	if (flags & DL_MODULE_ELF_INITIALIZE_FTEXTREL)
		DlModule_ElfMakeTextReadonly(self);

	/* Signal the initialization of the library to GDB _after_ relocations have been
	 * applied. - Otherwise, GDB may place a breakpoint on an instruction that's going
	 * to be modified by a relocation, causing undefined behavior when the relocation
	 * is applied to the breakpoint-instruction, rather than the original instruction.
	 * However: Still signal init before calling constructors, so that those are invoked
	 *          after GDB has injected potential breakpoints, so-as to allow breakpoints
	 *          to function properly within __attribute__((constructor)) functions. */
	if (!sys_debugtrap_disabled) {
		struct debugtrap_reason r;
		r.dtr_reason = DEBUGTRAP_REASON_LIBRARY;
		r.dtr_signo  = SIGTRAP;
		if (sys_debugtrap(NULL, &r) == -ENOENT)
			sys_debugtrap_disabled = true;
	}

	if (!(self->dm_flags & RTLD_NOINIT)) {
		/* Execute module initializers. */
		DlModule_ElfRunInitializers(self);
	}
	return 0;
err_nomem:
	dl_seterror_nomem();
err:
	return -1;
}


DECL_END

#endif /* !GUARD_LIBDL_MODULE_INIT_C */
