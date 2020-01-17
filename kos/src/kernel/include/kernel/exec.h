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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_EXEC_H
#define GUARD_KERNEL_INCLUDE_KERNEL_EXEC_H 1

#include <kernel/compiler.h>

#include <kernel/arch/exec.h>
#include <kernel/types.h>

#include <compat/config.h>
#include <kos/exec/elf.h>

#include <elf.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/exec/elf.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

struct icpustate;
struct path;
struct directory_entry;
struct regular_node;
struct vm_ramfile;

/* Initialize user-space for program execution. */
#ifndef CONFIG_EXEC_ARCH_HEADER_DEFINES_ELFEXEC_INIT_ENTRY
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2)) struct icpustate *KCALL
elfexec_init_entry(struct icpustate *__restrict user_state,
                   KERNEL ElfW(Ehdr) const *__restrict ehdr,
                   USER void *peb_address, USER void *ustack_base,
                   size_t ustack_size, USER void *entry_pc,
                   bool has_rtld);
#endif /* !CONFIG_EXEC_ARCH_HEADER_DEFINES_ELFEXEC_INIT_ENTRY */

/* Initialize the RTLD user-space library for runtime linking. */
#ifndef CONFIG_EXEC_ARCH_HEADER_DEFINES_ELFEXEC_INIT_RTLD
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3, 4, 5, 6)) struct icpustate *KCALL
elfexec_init_rtld(struct icpustate *__restrict user_state,
                  struct path *__restrict exec_path,
                  struct directory_entry *__restrict exec_dentry,
                  struct regular_node *__restrict exec_node,
                  KERNEL ElfW(Ehdr) const *__restrict ehdr,
                  KERNEL ElfW(Phdr) const *__restrict phdr_vec,
                  ElfW(Half) phdr_cnt,
                  void *application_loadaddr,
                  void *linker_loadaddr);
#endif /* !CONFIG_EXEC_ARCH_HEADER_DEFINES_ELFEXEC_INIT_RTLD */

/* Base address and size symbols for the system RTLD */
#ifndef CONFIG_EXEC_ARCH_HEADER_DEFINES_ELFEXEC_SYSTEM_RTLD
DATDEF byte_t elfexec_system_rtld[];

#undef elfexec_system_rtld_size
#ifdef __INTELLISENSE__
DATDEF size_t const elfexec_system_rtld_size;
#else /* __INTELLISENSE__ */
DATDEF byte_t elfexec_system_rtld_size[];
#define elfexec_system_rtld_size  ((size_t)elfexec_system_rtld_size)
#endif /* !__INTELLISENSE__ */
#endif /* !CONFIG_EXEC_ARCH_HEADER_DEFINES_ELFEXEC_SYSTEM_RTLD */

/* A static VM file blob for the building RTLD user-space program.
 * This is a raw ELF binary blob that is hard-linked into the kernel
 * core, and is mapped via copy-on-write into any user-space process
 * that requests the use of a dynamic linker
 * NOTE: The associated source code can be found in `/kos/src/libdl/...' */
#ifndef CONFIG_EXEC_ARCH_HEADER_DEFINES_ELFEXEC_SYSTEM_RTLD_FILE
DATDEF struct vm_ramfile elfexec_system_rtld_file;
#endif /* !CONFIG_EXEC_ARCH_HEADER_DEFINES_ELFEXEC_SYSTEM_RTLD_FILE */


/* Low-level arch-specific exec functions for compatibility mode */

#ifdef __ARCH_HAVE_COMPAT
/* Initialize user-space for program execution. */
#ifndef CONFIG_EXEC_ARCH_HEADER_DEFINES_COMPAT_ELFEXEC_INIT_ENTRY
FUNDEF struct icpustate *KCALL
compat_elfexec_init_entry(struct icpustate *__restrict user_state,
                          KERNEL COMPAT_ElfW(Ehdr) const *__restrict ehdr,
                          USER void *peb_address, USER void *ustack_base,
                          size_t ustack_size, USER void *entry_pc,
                          bool has_rtld);
#endif /* !CONFIG_EXEC_ARCH_HEADER_DEFINES_COMPAT_ELFEXEC_INIT_ENTRY */

/* Initialize the RTLD user-space library for runtime linking. */
#ifndef CONFIG_EXEC_ARCH_HEADER_DEFINES_COMPAT_ELFEXEC_INIT_RTLD
FUNDEF struct icpustate *KCALL
compat_elfexec_init_rtld(struct icpustate *__restrict user_state,
                         struct path *__restrict exec_path,
                         struct directory_entry *__restrict exec_dentry,
                         struct regular_node *__restrict exec_node,
                         KERNEL COMPAT_ElfW(Ehdr) const *__restrict ehdr,
                         KERNEL COMPAT_ElfW(Phdr) const *__restrict phdr_vec,
                         COMPAT_ElfW(Half) phdr_cnt,
                         void *application_loadaddr,
                         void *linker_loadaddr);
#endif /* !CONFIG_EXEC_ARCH_HEADER_DEFINES_COMPAT_ELFEXEC_INIT_RTLD */

/* Base address and size symbols for the system RTLD */
#ifndef CONFIG_EXEC_ARCH_HEADER_DEFINES_COMPAT_ELFEXEC_SYSTEM_RTLD
DATDEF byte_t compat_elfexec_system_rtld[];

#undef compat_elfexec_system_rtld_size
#ifdef __INTELLISENSE__
DATDEF size_t const compat_elfexec_system_rtld_size;
#else /* __INTELLISENSE__ */
DATDEF byte_t compat_elfexec_system_rtld_size[];
#define compat_elfexec_system_rtld_size  ((size_t)compat_elfexec_system_rtld_size)
#endif /* !__INTELLISENSE__ */
#endif /* !CONFIG_EXEC_ARCH_HEADER_DEFINES_COMPAT_ELFEXEC_SYSTEM_RTLD */

/* A static VM file blob for the building RTLD user-space program.
 * This is a raw ELF binary blob that is hard-linked into the kernel
 * core, and is mapped via copy-on-write into any user-space process
 * that requests the use of a dynamic linker
 * NOTE: The associated source code can be found in `/kos/src/libdl/...' */
#ifndef CONFIG_EXEC_ARCH_HEADER_DEFINES_COMPAT_ELFEXEC_SYSTEM_RTLD_FILE
DATDEF struct vm_ramfile compat_elfexec_system_rtld_file;
#endif /* !CONFIG_EXEC_ARCH_HEADER_DEFINES_COMPAT_ELFEXEC_SYSTEM_RTLD_FILE */

#endif /* __ARCH_HAVE_COMPAT */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_EXEC_H */
