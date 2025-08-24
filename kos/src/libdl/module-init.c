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
#ifndef GUARD_LIBDL_MODULE_INIT_C
#define GUARD_LIBDL_MODULE_INIT_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

/* Keep this one the first */
#include "api.h"

#include "dl.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/sequence/list.h>

#include <kos/anno.h>
#include <kos/debugtrap.h>
#include <kos/exec/elf-rel.h>
#include <kos/exec/elf.h> /* ELF_ARCH_USESRELA */
#include <kos/exec/peb.h>
#include <kos/syscalls.h>
#include <sys/mman.h>

#include <assert.h>
#include <atomic.h>
#include <dlfcn.h>
#include <elf.h>
#include <errno.h>
#include <malloc.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>

#include <libdl/extension.h>
#include <libdl/module.h>

DECL_BEGIN

LOCAL NONNULL((1)) void
NOTHROW(CC try_add2global)(DlModule *__restrict self) {
	uintptr_t old_flags;
again_old_flags:
	old_flags = atomic_read(&self->dm_flags);
	if (!(old_flags & RTLD_GLOBAL)) {
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
/* FIXME: When hardware-acceleration is enabled, a "movaps"
 *        instruction in libstdc++ called from here faults:
 *        >> movaps %xmm3, 32(%rsp)
 * However, %rsp is properly aligned at this point (see below: 000000000E471E80)
 *
 * - Started happening after GCC15 update
 * - To reproduce:
 *     1: Start KOS for x86_64 with hw acceleration enabled (w/o hw-acceleration, fault doesn't happen)
 *     2: run "gfx"
 *     3: Fault happens during init of libstdc++
 *
[2025-08-24T15:05:17.312537610:warn  ][6][gpf] Assuming Segmentation fault at ? [pc=000000000E2F327C,opcode=0xf29,opflags=0x0]
[2025-08-24T15:05:17.312719562:error ][6][coredump] Creating coredump...
[2025-08-24T15:05:17.313018096:error ][6] exception 0xff0e:0x1 [E_SEGFAULT_UNMAPPED,EFAULT] [cr2:0000800000000000,--uc--]
[2025-08-24T15:05:17.313229120:error ][6] 	pointer[0] = 0000800000000000 (140737488355328)
[2025-08-24T15:05:17.313361589:error ][6] 	pointer[1] = 000000000000000C (12)
[2025-08-24T15:05:17.313472588:error ][6] signal 11 (SIGSEGV: Segmentation violation)
[2025-08-24T15:05:17.313602265:error ][6] 	code:  1 (SEGV_MAPERR: Address not mapped to object)
[2025-08-24T15:05:17.313740991:error ][6] 	errno: 14 (EFAULT: Bad address)
E2F327C [ios_init.cc:78,3:_ZNSt8ios_base4InitC2Ev] faultaddr
E2F327C [ios_init.cc:78,3:_ZNSt8ios_base4InitC2Ev] orig_ustate
Coredump /bin/gfx tid:6
exception 0xff0e:0x1 [E_SEGFAULT_UNMAPPED,EFAULT] [cr2:0000800000000000,--uc--]
	pointer[0] = 0x0000800000000000 (140737488355328)
	pointer[1] = 0x000000000000000C (12)
signal 11 (SIGSEGV: Segmentation violation)
	code:  1 (SEGV_MAPERR: Address not mapped to object)
	errno: 14 (EFAULT: Bad address)
[RT] Cached method `string.casestartswith' in `string' (tp_cache)
E:\c\kls\kos\binutils\x86_64-kos\gcc\x86_64-kos\libstdc++-v3\include\streambuf(475,29) : 000000000E2F327C+5[/lib64/libstdc++.so.6][_ZSt21ios_base_library_initv+69] [faultaddr]
E:\c\kls\kos\binutils\x86_64-kos\gcc\x86_64-kos\libstdc++-v3\include\ext\stdio_sync_filebuf.h(83,54) : 000000000E2F3200+133[/lib64/libstdc++.so.6][_ZSt21ios_base_library_initv+55] [faultaddr]
E:\c\kls\kos\binutils\src\gcc-15.2.0\libstdc++-v3\src\c++98\ios_init.cc(85,54) : 000000000E2F3200+133[/lib64/libstdc++.so.6][_ZSt21ios_base_library_initv+55] [faultaddr]
E:\c\kls\kos\binutils\src\gcc-15.2.0\libstdc++-v3\src\c++98\ios_init.cc(78,3) : 000000000E2F3200+1470[/lib64/libstdc++.so.6][_ZNSt8ios_base4InitC2Ev+55] [faultaddr]
E:\c\kls\kos\binutils\x86_64-kos\gcc\x86_64-kos\libstdc++-v3\include\streambuf(475,29) : 000000000E2F327C+5[/lib64/libstdc++.so.6][_ZSt21ios_base_library_initv+69] [orig_ustate]
E:\c\kls\kos\binutils\x86_64-kos\gcc\x86_64-kos\libstdc++-v3\include\ext\stdio_sync_filebuf.h(83,54) : 000000000E2F3200+133[/lib64/libstdc++.so.6][_ZSt21ios_base_library_initv+55] [orig_ustate]
E:\c\kls\kos\binutils\src\gcc-15.2.0\libstdc++-v3\src\c++98\ios_init.cc(85,54) : 000000000E2F3200+133[/lib64/libstdc++.so.6][_ZSt21ios_base_library_initv+55] [orig_ustate]
E:\c\kls\kos\binutils\src\gcc-15.2.0\libstdc++-v3\src\c++98\ios_init.cc(78,3) : 000000000E2F3200+1470[/lib64/libstdc++.so.6][_ZNSt8ios_base4InitC2Ev+55] [orig_ustate]
> trace
E:\c\kls\kos\binutils\x86_64-kos\gcc\x86_64-kos\libstdc++-v3\include\streambuf(475,29) : 000000000E2F327C+5[/lib64/libstdc++.so.6][_ZSt21ios_base_library_initv+69]
E:\c\kls\kos\binutils\x86_64-kos\gcc\x86_64-kos\libstdc++-v3\include\ext\stdio_sync_filebuf.h(83,54) : 000000000E2F3200+133[/lib64/libstdc++.so.6][_ZSt21ios_base_library_initv+55]
E:\c\kls\kos\binutils\src\gcc-15.2.0\libstdc++-v3\src\c++98\ios_init.cc(85,54) : 000000000E2F3200+133[/lib64/libstdc++.so.6][_ZSt21ios_base_library_initv+55]
E:\c\kls\kos\binutils\src\gcc-15.2.0\libstdc++-v3\src\c++98\ios_init.cc(78,3) : 000000000E2F3200+1470[/lib64/libstdc++.so.6][_ZNSt8ios_base4InitC2Ev+55]
E:\c\kls\kos\binutils\src\gcc-15.2.0\libstdc++-v3\src\c++98\globals_io.cc(80,65) : 000000000E2DE3CB+5[/lib64/libstdc++.so.6][__static_initialization_and_destruction_0+7]
E:\c\kls\kos\binutils\src\gcc-15.2.0\libstdc++-v3\src\c++98\globals_io.cc(118,1) : 000000000E2DE3C0+19[/lib64/libstdc++.so.6][_GLOBAL__sub_I.00090_globals_io.cc+4]
[2025-08-24T15:05:19.530848362:debug ][6][heap] Acquire kernel heap: FFFFFFFFDFFDA000...FFFFFFFFDFFDAFFF
[2025-08-24T15:05:19.531134000:debug ][6][mm] Merge nodes at FFFFFFFFDFFD5000-FFFFFFFFDFFD9FFF and FFFFFFFFDFFDA000-FFFFFFFFDFFDAFFF
[2025-08-24T15:05:19.531349153:debug ][6][heap] Acquire kernel heap: FFFFFFFFDFFD5000...FFFFFFFFDFFD9FFF
E:\c\kls\kos\kos\src\libdl\module-init.c(150,3) : 00000000BF10773C+2[/lib64/libdl.so][DlModule_ElfRunInitializers+231]
E:\c\kls\kos\kos\src\libdl\module-init.c(186,30) : 00000000BF107A8F+5[/lib64/libdl.so][DlModule_RunAllStaticInitializers+528]
> r
    %r15 0000000000000000 %r14 0000000010000A80
    %r13 0000000000000000 %r12 000000000000000B
    %r11 0000000000040202 %r10 0000000000227990
    %r9  0000000010000030 %r8  0000000000000000
    %rdi 000000000E482918 %rsi 00000000BFFFF020
    %rbp 000000007FFFFEF8 %rsp 000000000E471E80
    %rbx 000000000E4833F4 %rdx 000000000E47D4C0
    %rcx 0000000000000000 %rax 000000000E47DE00
    %rip 000000000E2F327C [orig=000000000E2F3278]
        [streambuf] [line=475,29]
        [addq	$0x10, %rax]
    %es 0063 [gdt+0x60,rpl=3,dpl=3,00000000+0xffffffff,--cwa] (USER_DATA+3)
    %ds 0063 [gdt+0x60,rpl=3,dpl=3,00000000+0xffffffff,--cwa] (USER_DATA+3)
    %fs 0063 [gdt+0x60,rpl=3,dpl=3,00000000+0xffffffff,--cwa] (USER_DATA+3)
    %gs 0063 [gdt+0x60,rpl=3,dpl=3,00000000+0xffffffff,--cwa] (USER_DATA+3)
    %cs 005B [gdt+0x58,rpl=3,dpl=3,00000000+0xffffffff,-xcr-] (USER_CODE+3)
    %ss 0053 [gdt+0x50,rpl=3,dpl=3,00000000+0xffffffff,--cw-] (USER_DATA32+3)
    %tr 0008 [gdt+0x08,rpl=0,dpl=0,EEEF2000+0x00003000,sxcra] (CPU_TSS)
    %ldt 0018 [gdt+0x18,rpl=0,dpl=3,EEEEE1C0+0x0000000f,s-cw-] (CPU_LDT)
    %fs.base 00000000100018B0 %gs.base FFFFF62780C27A00 [user]
                  %IA32_KERNEL_GS_BASE FFFFFFFFE2054CE8 [kern]
    %rflags 50206 [-p---] [if,rf,ac] [iopl=0]
    %cr0 00000000E0010033 [pe,mp,et,ne,wp,nw,cd,pg]    %cr2 FFFFFFFFF0A6C1CD
    %cr4 00000000001102B0 [pse,pae,pge,osfxsr,fsgsbase,smep]    %cr3 000000000752B000
    %dr7 0000000000000400    %dr6 00000000FFFF0FF0 [rtm]
    %gdt FFFFFFFFEEEEE140+119
    %idt FFFFFFFF809F0840+4095
 */


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
			atomic_write(&dl_globals.dg_errmsg, NULL);
			if (self->dm_elf.de_runpath) {
				dependency = DlModule_OpenFilenameInPathList(self->dm_elf.de_runpath,
				                                             filename, dep_flags,
				                                             self->dm_filename);
				if (!dependency && atomic_read(&dl_globals.dg_errmsg) == NULL) {
					/* Before  doing more open() system calls, check to see if we've
					 * already   loaded  a  matching   candidate  of  this  library!
					 * We can do this because `dl_globals.dg_libpath' never changes. */
					dependency = DlModule_FindFilenameInPathListFromAll(filename);
					if (dependency) {
						try_add2global(dependency);
					} else if (atomic_read(&dl_globals.dg_errmsg) == NULL) {
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
				} else if (atomic_read(&dl_globals.dg_errmsg) == NULL) {
					dependency = DlModule_OpenFilenameInPathList(dl_globals.dg_libpath,
					                                             filename, dep_flags,
					                                             self->dm_filename);
				}
			}
			if (!dependency) {
				if (atomic_read(&dl_globals.dg_errmsg) == NULL)
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
	if (dl_globals.dg_flags & DLGLOBALS_FLAG_BIND_NOW)
		flags |= DL_MODULE_ELF_INITIALIZE_FBINDNOW;
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
