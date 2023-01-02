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
#ifndef _I386_KOS_KOS_EXEC_ASM_ELF32_H
#define _I386_KOS_KOS_EXEC_ASM_ELF32_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#include <elf.h>

#if !defined(__x86_64__) && defined(__i386__)
#define ELF_ARCH_CLASS    ELF_ARCH386_CLASS
#define ELF_ARCH_MACHINE  ELF_ARCH386_MACHINE
#define ELF_ARCH_DATA     ELF_ARCH386_DATA
#define ELF_ARCH_USESRELA ELF_ARCH386_USESRELA
#define ELF_ARCH_LAZYINDX ELF_ARCH386_LAZYINDX
#endif /* !__x86_64__ && __i386__ */

#define ELF_ARCH386_CLASS    ELFCLASS32
#define ELF_ARCH386_MACHINE  EM_386
#define ELF_ARCH386_DATA     ELFDATA2LSB
#define ELF_ARCH386_USESRELA 0 /* i386 doesn't use addend-relocations */
#define ELF_ARCH386_LAZYINDX 0 /* Lazy relocations use offsets, rather than indices */

/* The  user-space  register  holding  a  pointer  to  the   ProcessEnvironmentBlock
 * immediately following the initial transition to user-space after a call to exec()
 * NOTE: This register points to a `struct process_peb' structure. */
#define ELF_ARCH386_PEB_REGISTER ebp

/* When  a dynamic  linker is  loaded, additional  information is passed
 * via user-space registers containing information about how the program
 * must  be  linked  before  it  can  actually  be  executed   properly.
 * The exact structures pointed to by `ELF_ARCH386_DL_RTLDDATA_REGISTER'
 * depend on which DL loader was chosen:
 *   - ELF: `struct process_rtld_elfdata' */
#define ELF_ARCH386_DL_RTLDDATA_REGISTER ecx /* Pointer to a RTLD-specific initialization data. */
#define ELF_ARCH386_DL_LOADADDR_REGISTER edx /* The kernel-chose base-address of the application being loaded. */

#endif /* !_I386_KOS_KOS_EXEC_ASM_ELF32_H */
