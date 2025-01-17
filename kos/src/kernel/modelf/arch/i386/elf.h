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
#ifndef GUARD_MODELF_ARCH_I386_ELF_H
#define GUARD_MODELF_ARCH_I386_ELF_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/host.h>

#include <elf.h>

#ifdef __x86_64__
#define EXEC_ARCH_HEADER_DEFINES_COMPAT_ELFEXEC_INIT_ENTRY
#define EXEC_ARCH_HEADER_DEFINES_COMPAT_ELFEXEC_INIT_RTLD
#define compat_elfexec_init_entry elfexec_init_entry32
#define compat_elfexec_init_rtld  elfexec_init_rtld32
#endif /* __x86_64__ */

#ifdef __CC__
DECL_BEGIN

#ifdef __x86_64__

struct icpustate;
struct path;
struct fdirent;
struct mfile;

/* Initialize user-space for program execution. */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *KCALL
elfexec_init_entry32(struct icpustate *__restrict user_state,
                     Elf32_Ehdr const *__restrict ehdr,
                     NCX void *peb_address, NCX void *ustack_base,
                     size_t ustack_size, NCX void *entry_pc);

/* Initialize the RTLD user-space library for runtime linking. */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 4, 5, 6)) struct icpustate *KCALL
elfexec_init_rtld32(struct icpustate *__restrict user_state,
                    struct path *exec_path,
                    struct fdirent *exec_dentry,
                    struct mfile *__restrict exec_file,
                    Elf32_Ehdr const *__restrict ehdr,
                    Elf32_Phdr const *__restrict phdr_vec, Elf32_Half phdr_cnt,
                    void *application_loadaddr, void *linker_loadaddr,
                    NCX void *peb_address, NCX void *ustack_base,
                    size_t ustack_size, NCX void *entry_pc);
#endif /* __x86_64__ */

DECL_END
#endif /* __CC__ */


#endif /* !GUARD_MODELF_ARCH_I386_ELF_H */
