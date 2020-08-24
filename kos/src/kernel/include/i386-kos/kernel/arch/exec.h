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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_EXEC_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_EXEC_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/host.h>

#include <elf.h>

DECL_BEGIN

#ifdef __x86_64__
#define CONFIG_EXEC_ARCH_HEADER_DEFINES_COMPAT_ELFEXEC_SYSTEM_RTLD 1
#define CONFIG_EXEC_ARCH_HEADER_DEFINES_COMPAT_ELFEXEC_SYSTEM_RTLD_FILE 1
#define compat_elfexec_system_rtld      elfexec_system_rtld32
#define compat_elfexec_system_rtld_size elfexec_system_rtld32_size
#define compat_elfexec_system_rtld_file elfexec_system_rtld32_file

#define CONFIG_EXEC_ARCH_HEADER_DEFINES_COMPAT_ELFEXEC_INIT_ENTRY 1
#define CONFIG_EXEC_ARCH_HEADER_DEFINES_COMPAT_ELFEXEC_INIT_RTLD 1
#define compat_elfexec_init_entry       elfexec_init_entry32
#define compat_elfexec_init_rtld        elfexec_init_rtld32
#endif /* __x86_64__ */

#ifdef __CC__

#ifdef __x86_64__

struct icpustate;
struct path;
struct directory_entry;
struct regular_node;

/* Initialize user-space for program execution. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *KCALL
elfexec_init_entry32(struct icpustate *__restrict user_state,
                     Elf32_Ehdr const *__restrict ehdr,
                     USER void *peb_address, USER void *ustack_base,
                     size_t ustack_size, USER void *entry_pc,
                     bool has_rtld);

/* Initialize the RTLD user-space library for runtime linking. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3, 4, 5, 6)) struct icpustate *KCALL
elfexec_init_rtld32(struct icpustate *__restrict user_state,
                    struct path *__restrict exec_path,
                    struct directory_entry *__restrict exec_dentry,
                    struct regular_node *__restrict exec_node,
                    Elf32_Ehdr const *__restrict ehdr,
                    Elf32_Phdr const *__restrict phdr_vec,
                    Elf32_Half phdr_cnt,
                    void *application_loadaddr,
                    void *linker_loadaddr);

/* Base address and size symbols for the system RTLD */
DATDEF byte_t elfexec_system_rtld32[];
#undef elfexec_system_rtld32_size
#ifdef __INTELLISENSE__
DATDEF size_t const elfexec_system_rtld32_size;
#else /* __INTELLISENSE__ */
DATDEF byte_t elfexec_system_rtld32_size[];
#define elfexec_system_rtld32_size ((size_t)elfexec_system_rtld32_size)
#endif /* !__INTELLISENSE__ */

/* A static VM file blob for the building RTLD user-space program.
 * This is a raw ELF binary blob that is hard-linked into the kernel
 * core, and is mapped via copy-on-write into any user-space process
 * that requests the use of a dynamic linker
 * NOTE: The associated source code can be found in `/kos/src/libdl/...' */
DATDEF struct vm_ramfile elfexec_system_rtld32_file;
#endif /* __x86_64__ */

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_EXEC_H */
