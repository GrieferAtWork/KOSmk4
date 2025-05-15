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
#ifndef GUARD_MODELF_ELF_H
#define GUARD_MODELF_ELF_H 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/execabi.h>

#include <hybrid/host.h>

#include <compat/config.h>
#include <kos/exec/elf.h>

#include <elf.h>
#include <stddef.h>

#if defined(__i386__) || defined(__x86_64__)
#include "arch/i386/elf.h"
#endif /* Arch... */

DECL_BEGIN

struct icpustate;
struct path;
struct fdirent;
struct mfile;

/* Initialize user-space for program execution. */
#ifndef CONFIG_EXEC_ARCH_HEADER_DEFINES_ELFEXEC_INIT_ENTRY
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *KCALL
elfexec_init_entry(struct icpustate *__restrict user_state,
                   KERNEL ElfW(Ehdr) const *__restrict ehdr,
                   NCX void *peb_address, NCX void *ustack_base,
                   size_t ustack_size, NCX void const *entry_pc);
#endif /* !CONFIG_EXEC_ARCH_HEADER_DEFINES_ELFEXEC_INIT_ENTRY */

/* Initialize the RTLD user-space library for runtime linking. */
#ifndef CONFIG_EXEC_ARCH_HEADER_DEFINES_ELFEXEC_INIT_RTLD
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 4, 5, 6)) struct icpustate *KCALL
elfexec_init_rtld(struct icpustate *__restrict user_state,
                  struct path *exec_path,
                  struct fdirent *exec_dentry,
                  struct mfile *__restrict exec_file,
                  KERNEL ElfW(Ehdr) const *__restrict ehdr,
                  KERNEL ElfW(Phdr) const *__restrict phdr_vec,
                  ElfW(Half) phdr_cnt,
                  void *application_loadaddr, void *linker_loadaddr,
                  NCX void *peb_address, NCX void *ustack_base,
                  size_t ustack_size, NCX void const *entry_pc);
#endif /* !CONFIG_EXEC_ARCH_HEADER_DEFINES_ELFEXEC_INIT_RTLD */

/* Low-level arch-specific exec functions for compatibility mode */

#ifdef __ARCH_HAVE_COMPAT
/* Initialize user-space for program execution. */
#ifndef EXEC_ARCH_HEADER_DEFINES_COMPAT_ELFEXEC_INIT_ENTRY
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *KCALL
compat_elfexec_init_entry(struct icpustate *__restrict user_state,
                          KERNEL COMPAT_ElfW(Ehdr) const *__restrict ehdr,
                          NCX void *peb_address, NCX void *ustack_base,
                          size_t ustack_size, NCX void const *entry_pc);
#endif /* !EXEC_ARCH_HEADER_DEFINES_COMPAT_ELFEXEC_INIT_ENTRY */

/* Initialize the RTLD user-space library for runtime linking. */
#ifndef EXEC_ARCH_HEADER_DEFINES_COMPAT_ELFEXEC_INIT_RTLD
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 4, 5, 6)) struct icpustate *KCALL
compat_elfexec_init_rtld(struct icpustate *__restrict user_state,
                         struct path *exec_path,
                         struct fdirent *exec_dentry,
                         struct mfile *__restrict exec_file,
                         KERNEL COMPAT_ElfW(Ehdr) const *__restrict ehdr,
                         KERNEL COMPAT_ElfW(Phdr) const *__restrict phdr_vec,
                         COMPAT_ElfW(Half) phdr_cnt,
                         void *application_loadaddr, void *linker_loadaddr,
                         NCX void *peb_address, NCX void *ustack_base,
                         size_t ustack_size, NCX void const *entry_pc);
#endif /* !EXEC_ARCH_HEADER_DEFINES_COMPAT_ELFEXEC_INIT_RTLD */
#endif /* __ARCH_HAVE_COMPAT */




/* Populate a given `effective_vm' by loading an ELF executable file. */
INTDEF WUNUSED NONNULL((1)) unsigned int FCALL
elfabi_exec(/*in|out*/ struct execargs *__restrict args);

/* ExecABI initializer for ELF. */
#define EXECABI_INIT_ELF                                     \
	{                                                        \
		.ea_driver = &drv_self,                              \
		.ea_magsiz = SELFMAG,                                \
		.ea_magic  = { ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3 }, \
		.ea_exec   = &elfabi_exec,                           \
	}



DECL_END

#endif /* !GUARD_MODELF_ELF_H */
