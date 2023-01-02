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
#ifndef GUARD_LIBDL_ARCH_I386__START64_S
#define GUARD_LIBDL_ARCH_I386__START64_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

.section .text.linker_entry
INTERN_FUNCTION(linker_entry)
	/* Low-level linker entry point (this is the initial user-level
	 * entry point that gets called by the kernel when  dynamically
	 * linked binaries are invoked)
	 *
	 * Note that  at this  point we're  already in  user-space, so  no
	 * more screwing around with `iret' or direct access of preemption
	 * control or IO from here on \^w^/
	 */

	/* The current (expected) register/stack state looks like this:
	 *   %rdi:  struct elfexec_info *info;     // Information about execution context (see the struct for more  details)
	 *                                         // Note that this struct is actually allocated on the stack, with its end
	 *                                         // marking the base of the user-space stack
	 *   %rsi:  uintptr_t            loadaddr; // Loadaddr (load offset) of the main binary (usually
	 *                                         // 0,  since that binary probably can't be relocated)
	 *   %rdx:  struct process_peb  *peb;      // Points to the process environment block (contains argc+argv[] and environ[])
	 */
	INTERN(linker_main)
	call   linker_main
	movq   %rax, %rsp  /* %rax == &(struct elfexec_info)::pr_entry */
	/* Run user-level initializers */
	INTERN(DlModule_RunAllStaticInitializers)
	call   DlModule_RunAllStaticInitializers
	ret                /* >> SP = &(struct elfexec_info)::pr_entry_sp;
	                    * >> PC = (struct elfexec_info)::pr_entry; */
END(linker_entry)

#endif /* !GUARD_LIBDL_ARCH_I386__START64_S */
