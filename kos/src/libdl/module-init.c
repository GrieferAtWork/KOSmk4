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
#ifndef GUARD_LIBDL_MODULE_INIT_C
#define GUARD_LIBDL_MODULE_INIT_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

/* Keep this one the first */
#include "elf.h"
/**/

#include <bits/elf.h> /* ELF_HOST_RELA_UNUSED */
#include <kos/debugtrap.h>
#include <kos/exec/peb.h>
#include <kos/syscalls.h>
#include <sys/mman.h>

#include <errno.h>
#include <malloc.h>
#include <signal.h>
#include <syslog.h>


DECL_BEGIN

LOCAL void CC try_add2global(DlModule *__restrict self) {
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
INTERN char *ld_library_path_env = NULL;


/* Invoke the static initializers of all currently loaded modules.
 * This is called late during initial module startup once the initial
 * set of libraries, + the initial application have been loaded.
 * Note that initializers are invoked in reverse order of those modules
 * appearing within `DlModule_AllList', meaning that the primary
 * application's __attribute__((constructor)) functions are invoked
 * _AFTER_ those from (e.g.) libc. */
INTERN void LIBCCALL DlModule_RunAllStaticInitializers(void) {
	REF DlModule *primary;
	DlModule *last;
	primary = DlModule_GlobalList;
	assert(primary != &ld_rtld_module);
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
	assert(last != &ld_rtld_module);
	last->dm_flags &= ~RTLD_NOINIT;
	DlModule_Incref(last);
	atomic_rwlock_endread(&DlModule_GlobalLock);
#if 1 /* This is called during init. - If an exception happens here, it wouldn't matter at all... */
	DlModule_RunInitializers(last);
#else
	TRY {
		DlModule_RunInitializers(last);
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


/* Run library initializers for `self' */
INTERN void CC
DlModule_RunInitializers(DlModule *__restrict self) {
	uint16_t dyni;
	size_t i;
	uintptr_t init_func           = 0;
	uintptr_t *preinit_array_base = NULL;
	size_t preinit_array_size     = 0;
	uintptr_t *init_array_base    = NULL;
	size_t init_array_size        = 0;
	for (dyni = 0; dyni < self->dm_dyncnt; ++dyni) {
		switch (self->dm_dynhdr[dyni].d_tag) {
		case DT_NULL:
			goto done_dyntag;
		case DT_INIT:
			init_func = (uintptr_t)self->dm_dynhdr[dyni].d_un.d_ptr;
			break;
		case DT_PREINIT_ARRAY:
			preinit_array_base = (uintptr_t *)(self->dm_loadaddr +
			                                   self->dm_dynhdr[dyni].d_un.d_ptr);
			break;
		case DT_PREINIT_ARRAYSZ:
			preinit_array_size = (size_t)self->dm_dynhdr[dyni].d_un.d_val / sizeof(void (*)(void));
			break;
		case DT_INIT_ARRAY:
			init_array_base = (uintptr_t *)(self->dm_loadaddr +
			                                self->dm_dynhdr[dyni].d_un.d_ptr);
			break;
		case DT_INIT_ARRAYSZ:
			init_array_size = (size_t)self->dm_dynhdr[dyni].d_un.d_val / sizeof(void (*)(void));
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

#if PF_X == PROT_EXEC && PF_W == PROT_WRITE && PF_R == PROT_READ
#define ELF_PF_FLAGS_TO_PROT_FLAGS(x) ((x) & (PF_X | PF_W | PF_R))
#else
#define ELF_PF_FLAGS_TO_PROT_FLAGS(x)        \
	(((x) & PF_X ? PROT_EXEC : PROT_NONE) |  \
	 ((x) & PF_W ? PROT_WRITE : PROT_NONE) | \
	 ((x) & PF_R ? PROT_READ : PROT_NONE))
#define ELF_PF_FLAGS_TO_PROT_FLAGS_PLUS_WRITE(x) \
	(((x) & PF_X ? PROT_EXEC : PROT_NONE) |      \
	 ((x) & PF_R ? PROT_READ : PROT_NONE) | PROT_WRITE)
#endif
#ifndef ELF_PF_FLAGS_TO_PROT_FLAGS_PLUS_WRITE
#define ELF_PF_FLAGS_TO_PROT_FLAGS_PLUS_WRITE(x) \
	(ELF_PF_FLAGS_TO_PROT_FLAGS(x) | PROT_WRITE)
#endif /* !ELF_PF_FLAGS_TO_PROT_FLAGS_PLUS_WRITE */


INTERN int CC
DlModule_MakeTextWritable(DlModule *__restrict self) {
	Elf_Half i;
	errno_t error;
	for (i = 0; i < self->dm_phnum; ++i) {
		if (self->dm_phdr[i].p_type != PT_LOAD)
			continue;
		if (self->dm_phdr[i].p_flags & PF_W)
			continue; /* Already writable */
		error = sys_mprotect((void *)(self->dm_phdr[i].p_vaddr + self->dm_loadaddr),
		                     self->dm_phdr[i].p_memsz,
		                     ELF_PF_FLAGS_TO_PROT_FLAGS_PLUS_WRITE(self->dm_phdr[i].p_flags));
		if unlikely(E_ISERR(error))
			goto err_mprotect_failed;
	}
	return 0;
err_mprotect_failed:
	elf_setdlerrorf("%q: Failed to make text writable (errno=%d)",
	                self->dm_filename, -error);
	return -1;
}

INTERN void CC
DlModule_MakeTextReadonly(DlModule *__restrict self) {
	Elf_Half i;
	for (i = 0; i < self->dm_phnum; ++i) {
		if (self->dm_phdr[i].p_type != PT_LOAD)
			continue;
		if (self->dm_phdr[i].p_flags & PF_W)
			continue; /* Already writable */
		sys_mprotect((void *)(self->dm_phdr[i].p_vaddr + self->dm_loadaddr),
		             self->dm_phdr[i].p_memsz,
		             ELF_PF_FLAGS_TO_PROT_FLAGS(self->dm_phdr[i].p_flags));
	}
}

/* Apply relocations & execute library initialized within `self'
 * @param: flags: Set of `DL_MODULE_INITIALIZE_F*' */
INTERN int CC
DlModule_Initialize(DlModule *__restrict self, unsigned int flags) {
#ifndef ELF_HOST_RELA_UNUSED
	Elf_Rela *rela_base = NULL;
	size_t rela_count   = 0;
	bool jmp_rels_have_addend = false;
#endif /* !ELF_HOST_RELA_UNUSED */
	Elf_Rel *rel_base = NULL;
	size_t rel_count  = 0;
	Elf_Rel *jmp_base = NULL;
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
		for (i = 0; i < self->dm_dyncnt; ++i) {
			char *filename;
			REF DlModule *dependency;
			if (self->dm_dynhdr[i].d_tag == DT_NULL)
				break;
			if (self->dm_dynhdr[i].d_tag != DT_NEEDED)
				continue;
			assert(self->dm_depcnt < count);
			filename = self->dm_dynstr + self->dm_dynhdr[i].d_un.d_ptr;
			/* Load the dependent library. */
			if (self->dm_runpath) {
				dependency = DlModule_OpenFilenameInPathList(self->dm_runpath,
				                                             filename,
				                                             dep_flags);
				if (!dependency && ATOMIC_READ(elf_dlerror_message) == NULL) {
					/* Before doing more open() system calls, check to see if we've
					 * already loaded a matching candidate of this library!
					 * We can do this because `ld_library_path_env' never changes. */
					dependency = DlModule_FindFilenameInPathListFromAll(filename);
					if (!dependency) {
						dependency = DlModule_OpenFilenameInPathList(ld_library_path_env,
						                                             filename,
						                                             dep_flags);
					} else {
						try_add2global(dependency);
					}
				}
			} else {
				/* Before doing more open() system calls, check to see if we've
				 * already loaded a matching candidate of this library!
				 * We can do this because `ld_library_path_env' never changes. */
				dependency = DlModule_FindFilenameInPathListFromAll(filename);
				if (!dependency) {
					dependency = DlModule_OpenFilenameInPathList(ld_library_path_env,
					                                             filename,
					                                             dep_flags);
				} else {
					try_add2global(dependency);
				}
			}
			if (!dependency) {
				if (ATOMIC_READ(elf_dlerror_message) == NULL)
					elf_setdlerrorf("Failed to load dependency %q of %q", filename, self->dm_filename);
				goto err;
			}
			self->dm_depvec[self->dm_depcnt++] = dependency;
		}
	}
	/* Service relocations of the module. */
	for (i = 0; i < self->dm_dyncnt; ++i) {
		Elf_Dyn tag = self->dm_dynhdr[i];
		switch (tag.d_tag) {

		case DT_NULL:
			goto done_dynamic;

		case DT_TEXTREL:
			flags |= DL_MODULE_INITIALIZE_FTEXTREL;
			break;

		case DT_BIND_NOW:
			flags |= DL_MODULE_INITIALIZE_FBINDNOW;
			break;

		case DT_FLAGS:
			if (tag.d_un.d_val & DF_SYMBOLIC)
				self->dm_flags |= RTLD_DEEPBIND;
			if (tag.d_un.d_val & DF_TEXTREL)
				flags |= DL_MODULE_INITIALIZE_FTEXTREL;
			if (tag.d_un.d_val & DF_BIND_NOW)
				flags |= DL_MODULE_INITIALIZE_FBINDNOW;
			break;

		case DT_SYMBOLIC:
			self->dm_flags |= RTLD_DEEPBIND;
			break;

		case DT_REL:
			rel_base = (Elf_Rel *)(self->dm_loadaddr + tag.d_un.d_ptr);
			break;

		case DT_RELSZ:
			rel_count = tag.d_un.d_val / sizeof(Elf_Rel);
			break;

		case DT_JMPREL:
			jmp_base = (Elf_Rel *)(self->dm_loadaddr + tag.d_un.d_ptr);
			break;

		case DT_PLTRELSZ:
			jmp_size = tag.d_un.d_val;
			break;

		case DT_PLTGOT:
			self->dm_pltgot = (Elf_Addr *)(self->dm_loadaddr + tag.d_un.d_ptr);
			break;

#ifndef ELF_HOST_RELA_UNUSED
		case DT_RELA:
			rela_base = (Elf_Rela *)(self->dm_loadaddr + tag.d_un.d_ptr);
			break;

		case DT_RELASZ:
			rela_count = tag.d_un.d_val / sizeof(Elf_Rela);
			break;

		case DT_PLTREL:
			if (tag.d_un.d_val == DT_RELA)
				jmp_rels_have_addend = true;
			break;
#endif /* !ELF_HOST_RELA_UNUSED */

		default: break;
		}
	}
done_dynamic:
	if (flags & DL_MODULE_INITIALIZE_FTEXTREL) {
		/* Make all sections writable! */
		if unlikely(DlModule_MakeTextWritable(self))
			goto err;
	}

#ifdef R_JMP_SLOT
	/* Enable direct binding when `LD_BIND_NOW' is defined as non-empty */
	{
		char *ld_bind_now;
		ld_bind_now = process_peb_getenv(root_peb, "LD_BIND_NOW");
		if (ld_bind_now && *ld_bind_now)
			flags |= DL_MODULE_INITIALIZE_FBINDNOW;
	}
#endif /* R_JMP_SLOT */

	/* Apply relocations. */
	if unlikely(DlModule_ApplyRelocations(self, rel_base, rel_count,
	                                      flags | DL_MODULE_INITIALIZE_FBINDNOW))
		goto err;
#ifndef ELF_HOST_RELA_UNUSED
	if unlikely(DlModule_ApplyRelocationsWithAddend(self, rela_base, rela_count,
		                                            flags | DL_MODULE_INITIALIZE_FBINDNOW))
		goto err;
#endif /* ELF_HOST_RELA_UNUSED */

	if (jmp_size) {
#ifndef ELF_HOST_RELA_UNUSED
		if (jmp_rels_have_addend) {
#ifdef R_JMP_SLOT
			if (self->dm_pltgot && !(flags & DL_MODULE_INITIALIZE_FBINDNOW)) {
				/* Lazy binding of jump-relocations! */
				self->dm_pltgot[1] = (Elf_Addr)self;
				self->dm_pltgot[2] = (Elf_Addr)&libdl_load_lazy_relocation;
				self->dm_jmprela   = (Elf_Rela *)jmp_base;
				self->dm_jmpsize   = jmp_size;
				self->dm_flags    |= RTLD_JMPRELA;
				if unlikely(DlModule_ApplyRelocationsWithAddend(self, (Elf_Rela *)jmp_base,
				                                                jmp_size / sizeof(Elf_Rela),
				                                                flags))
					goto err;
			} else
#endif /* R_JMP_SLOT */
			{
				/* Directly bind jump-relocations. */
				if unlikely(DlModule_ApplyRelocationsWithAddend(self, (Elf_Rela *)jmp_base,
				                                                jmp_size / sizeof(Elf_Rela),
				                                                flags | DL_MODULE_INITIALIZE_FBINDNOW))
					goto err;
			}
		} else
#endif /* !ELF_HOST_RELA_UNUSED */
		{
#ifdef R_JMP_SLOT
			if (self->dm_pltgot && !(flags & DL_MODULE_INITIALIZE_FBINDNOW)) {
				/* Lazy binding of jump-relocations! */
				self->dm_pltgot[1] = (Elf_Addr)self;
				self->dm_pltgot[2] = (Elf_Addr)&libdl_load_lazy_relocation;
				self->dm_jmprel    = jmp_base;
				self->dm_jmpsize   = jmp_size;
				if unlikely(DlModule_ApplyRelocations(self, jmp_base,
				                                      jmp_size / sizeof(Elf_Rel),
				                                      flags))
					goto err;
			} else
#endif /* R_JMP_SLOT */
			{
				/* Directly bind jump-relocations. */
				if unlikely(DlModule_ApplyRelocations(self, jmp_base,
				                                      jmp_size / sizeof(Elf_Rel),
				                                      flags | DL_MODULE_INITIALIZE_FBINDNOW))
					goto err;
			}
		}
	}

	/* Remove writable from read-only sections! */
	if (flags & DL_MODULE_INITIALIZE_FTEXTREL)
		DlModule_MakeTextReadonly(self);

	/* Signal the initialization of the library to GDB _after_ relocations have been
	 * applied. - Otherwise, GCC may place a breakpoint on an instruction that's going
	 * to be modified by a relocation, causing undefined behavior when the relocation
	 * is applied to the breakpoint-instruction, rather than the original instruction.
	 * However: Still signal init before calling constructors, so that those are invoked
	 *          after GCC has injected potential breakpoints, so-as to allow breakpoints
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
		DlModule_RunInitializers(self);
	}
	return 0;
err_nomem:
	elf_setdlerror_nomem();
err:
	return -1;
}


DECL_END

#endif /* !GUARD_LIBDL_MODULE_INIT_C */
