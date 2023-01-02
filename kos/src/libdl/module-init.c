/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
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
#include <kos/exec/elf.h> /* ELF_ARCH_USESRELA */
#include <kos/exec/peb.h>
#include <kos/syscalls.h>
#include <sys/mman.h>

#include <errno.h>
#include <malloc.h>
#include <signal.h>
#include <syslog.h>


DECL_BEGIN

LOCAL NONNULL((1)) void
NOTHROW(CC try_add2global)(DlModule *__restrict self) {
	uintptr_t old_flags;
again_old_flags:
	old_flags = ATOMIC_READ(self->dm_flags);
	if (!(old_flags & RTLD_GLOBAL)) {
		/* Make the module global. */
		dlglobals_global_write(&dl_globals);
		if (!ATOMIC_CMPXCH_WEAK(self->dm_flags, old_flags,
		                        old_flags | RTLD_GLOBAL)) {
			dlglobals_global_endwrite(&dl_globals);
			goto again_old_flags;
		}
		assert(!TAILQ_ISBOUND(self, dm_globals));
		dlglobals_global_add(&dl_globals, self);
		dlglobals_global_endwrite(&dl_globals);
	}
}


/* This is the prototype by which ELF initializer callbacks are invoked.
 * For this purpose, calling them is essentially the same as calling the
 * primary program's main()  function, only that  these are expected  to
 * return without doing the program's main task! */
typedef void (*elf_init_t)(int argc, char *argv[], char *envp[]) THROWS(...);

/* Apparently,  global  initializer  functions   take
 * the same arguments as  are also passed to  main():
 * >> void (*)(int argc, char *argv[], char *envp[]);
 *
 * As  such, call them like that, rather than without any arguments!
 * HINT: We can take all of the required information from `dl_globals.dg_peb' */
#define CALLINIT(funptr)                                 \
	((*(elf_init_t)(funptr))(dl_globals.dg_peb->pp_argc, \
	                         dl_globals.dg_peb->pp_argv, \
	                         dl_globals.dg_peb->pp_envp))


/* Run library initializers for `self' */
PRIVATE NONNULL((1)) void CC
DlModule_ElfRunInitializers(DlModule *__restrict self) THROWS(...) {
	size_t i, dyni;
	uintptr_t init_func           = 0;
	uintptr_t *preinit_array_base = NULL;
	size_t preinit_array_size     = 0;
	uintptr_t *init_array_base    = NULL;
	size_t init_array_size        = 0;
	for (dyni = 0; dyni < self->dm_elf.de_dyncnt; ++dyni) {
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
			preinit_array_size = (size_t)self->dm_dynhdr[dyni].d_un.d_val /
			                     sizeof(elf_init_t);
			break;

		case DT_INIT_ARRAY:
			init_array_base = (uintptr_t *)(self->dm_loadaddr +
			                                self->dm_dynhdr[dyni].d_un.d_ptr);
			break;

		case DT_INIT_ARRAYSZ:
			init_array_size = (size_t)self->dm_dynhdr[dyni].d_un.d_val /
			                  sizeof(elf_init_t);
			break;

		default: break;
		}
	}
done_dyntag:
	for (i = 0; i < preinit_array_size; ++i)
		CALLINIT(preinit_array_base[i] /* + self->dm_loadaddr*/);

	/* Service an init function, if one was specified. */
	if (init_func)
		CALLINIT(init_func + self->dm_loadaddr);

	/* Service init-array functions in forward order. */
	for (i = 0; i < init_array_size; ++i)
		CALLINIT(init_array_base[i] /* + self->dm_loadaddr*/);
}

/* Invoke the  static initializers  of  all currently  loaded  modules.
 * This is called late during  initial module startup once the  initial
 * set of  libraries,  +  the initial  application  have  been  loaded.
 * Note that initializers are invoked in reverse order of those modules
 * appearing within `dl_globals.dg_alllist',  meaning that the  primary
 * application's  __attribute__((constructor))  functions  are  invoked
 * _AFTER_ those from (e.g.) libc. */
INTERN void CC DlModule_RunAllStaticInitializers(void) THROWS(...) {
	REF DlModule *primary;
	DlModule *last;
	primary = TAILQ_FIRST(&dl_globals.dg_globallist);
	assert(primary != &dl_rtld_module);
	incref(primary);
again_search_noinit:
	dlglobals_global_read(&dl_globals);
	last = TAILQ_LAST(&dl_globals.dg_globallist);
	while (!(last->dm_flags & RTLD_NOINIT)) {
		if (last == primary) {
			dlglobals_global_endread(&dl_globals);
			goto done;
		}
		last = TAILQ_PREV(last, dm_globals);
	}
	assert(last != &dl_rtld_module);
	last->dm_flags &= ~RTLD_NOINIT;
	incref(last);
	dlglobals_global_endread(&dl_globals);

	/* Support for formats other than ELF. */
	if (last->dm_ops) {
		if (last->dm_ops->df_run_initializers)
			(*last->dm_ops->df_run_initializers)(last);
	} else {
		DlModule_ElfRunInitializers(last);
	}

	decref(last);
	if (last != primary)
		goto again_search_noinit;
done:
	decref(primary);
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


PRIVATE NONNULL((1)) int
NOTHROW(CC DlModule_ElfMakeTextWritable)(DlModule *__restrict self) {
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
	return dl_seterrorf("%q: Failed to make text writable (errno=%u)",
	                    self->dm_filename, (unsigned int)-error);
}

PRIVATE NONNULL((1)) void
NOTHROW(CC DlModule_ElfMakeTextReadonly)(DlModule *__restrict self) {
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
DlModule_ElfInitialize(DlModule *__restrict self, unsigned int flags)
		THROWS(...) {
#if ELF_ARCH_USESRELA
	ElfW(Rela) *rela_base     = NULL;
	size_t rela_count         = 0;
	bool jmp_rels_have_addend = false;
#endif /* ELF_ARCH_USESRELA */
	ElfW(Rel) *rel_base = NULL;
	size_t rel_count    = 0;
	ElfW(Rel) *jmp_base = NULL;
	size_t jmp_size     = 0;
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
			char const *filename;
			REF DlModule *dependency;
			if (self->dm_dynhdr[i].d_tag == DT_NULL)
				break;
			if (self->dm_dynhdr[i].d_tag != DT_NEEDED)
				continue;
			assert(self->dm_depcnt < count);
			filename = self->dm_elf.de_dynstr + self->dm_dynhdr[i].d_un.d_ptr;
			/* Load the dependent library. */
			ATOMIC_WRITE(dl_globals.dg_errmsg, NULL);
			if (self->dm_elf.de_runpath) {
				dependency = DlModule_OpenFilenameInPathList(self->dm_elf.de_runpath,
				                                             filename, dep_flags,
				                                             self->dm_filename);
				if (!dependency && ATOMIC_READ(dl_globals.dg_errmsg) == NULL) {
					/* Before  doing more open() system calls, check to see if we've
					 * already   loaded  a  matching   candidate  of  this  library!
					 * We can do this because `dl_globals.dg_libpath' never changes. */
					dependency = DlModule_FindFilenameInPathListFromAll(filename);
					if (dependency) {
						try_add2global(dependency);
					} else if (ATOMIC_READ(dl_globals.dg_errmsg) == NULL) {
						dependency = DlModule_OpenFilenameInPathList(dl_globals.dg_libpath,
						                                             filename, dep_flags,
						                                             self->dm_filename);
					}
				}
			} else {
				/* Before  doing more open() system calls, check to see if we've
				 * already   loaded  a  matching   candidate  of  this  library!
				 * We can do this because `dl_globals.dg_libpath' never changes. */
				dependency = DlModule_FindFilenameInPathListFromAll(filename);
				if (dependency) {
					try_add2global(dependency);
				} else if (ATOMIC_READ(dl_globals.dg_errmsg) == NULL) {
					dependency = DlModule_OpenFilenameInPathList(dl_globals.dg_libpath,
					                                             filename, dep_flags,
					                                             self->dm_filename);
				}
			}
			if (!dependency) {
				if (ATOMIC_READ(dl_globals.dg_errmsg) == NULL)
					dl_seterrorf("Failed to load dependency %q of %q",
					             filename, self->dm_filename);
				goto err;
			}
			self->dm_depvec[self->dm_depcnt++] = dependency; /* Inherit reference */
		}
	}
	/* Service relocations of the module. */
	for (i = 0; i < self->dm_elf.de_dyncnt; ++i) {
		ElfW(Dyn) tag = self->dm_dynhdr[i];
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
					dlglobals_global_write(&dl_globals);
					self->dm_flags |= RTLD_GLOBAL;
					if (!TAILQ_ISBOUND(self, dm_globals))
						dlglobals_global_add(&dl_globals, self);
					dlglobals_global_endwrite(&dl_globals);
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
		ld_bind_now = process_peb_getenv(dl_globals.dg_peb, "LD_BIND_NOW");
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
				self->dm_flags |= RTLD_JMPRELA;
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

	/* Signal the initialization of the library  to GDB _after_ relocations have  been
	 * applied. - Otherwise, GDB may place a breakpoint on an instruction that's going
	 * to be modified by a relocation, causing undefined behavior when the  relocation
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
