/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_EXEC_EXECABI_C
#define GUARD_KERNEL_CORE_ARCH_I386_EXEC_EXECABI_C 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */

#include <kernel/compiler.h>

#include <kernel/execabi.h>
#include <kernel/vm.h>

DECL_BEGIN

/* Define the RTLD file(s). */
INTDEF byte_t execabi_system_rtld_startpageptr[];
INTDEF byte_t execabi_system_rtld_numpages[];

#ifdef CONFIG_USE_NEW_VM
PUBLIC struct mramfile execabi_system_rtld_file =
MRAMFILE_INIT(execabi_system_rtld_file,
              (physpage_t)execabi_system_rtld_startpageptr,
              (size_t)execabi_system_rtld_numpages,
              execabi_system_rtld_size);
#else /* CONFIG_USE_NEW_VM */
PUBLIC struct vm_ramfile execabi_system_rtld_file =
VM_RAMFILE_INIT((physpage_t)execabi_system_rtld_startpageptr,
                (size_t)execabi_system_rtld_numpages);
#endif /* !CONFIG_USE_NEW_VM */

#ifdef __x86_64__
INTDEF byte_t execabi_system_rtld32_startpageptr[];
INTDEF byte_t execabi_system_rtld32_numpages[];
#ifdef CONFIG_USE_NEW_VM
PUBLIC struct mramfile execabi_system_rtld32_file =
MRAMFILE_INIT((physpage_t)execabi_system_rtld32_startpageptr,
              (size_t)execabi_system_rtld32_numpages,
              execabi_system_rtld32_size);
#else /* CONFIG_USE_NEW_VM */
PUBLIC struct vm_ramfile execabi_system_rtld32_file =
VM_RAMFILE_INIT((physpage_t)execabi_system_rtld32_startpageptr,
                (size_t)execabi_system_rtld32_numpages);
#endif /* !CONFIG_USE_NEW_VM */
#endif /* __x86_64__ */

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_EXEC_EXECABI_C */
