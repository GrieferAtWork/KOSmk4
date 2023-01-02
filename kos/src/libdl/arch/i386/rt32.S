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
#ifndef GUARD_LIBDL_ARCH_I386_RT32_S
#define GUARD_LIBDL_ARCH_I386_RT32_S 1
#define __ASSEMBLER__ 1

#include "../../api.h"
/**/

#include <hybrid/compiler.h>

#include <cfi.h>

#include "../../builtin.h"
/**/

INTERN(dl_require_global)

#define DEFINE_GLOBAL_SYMBOL_IMPORT(name)                 \
	.section .rodata.str.1;                               \
	991: .asciz #name;                                    \
	.section .text;                                       \
	INTERN_FUNCTION(name);                                \
		.cfi_startproc;                                   \
		pushl       $(0);   /* RETURN_PC_OVERRIDE */      \
		pushfl_cfi_r;                                     \
		pushl_cfi_r %eax;                                 \
		pushl_cfi_r %ecx;                                 \
		pushl_cfi_r %edx;                                 \
		call   1f;                                        \
	1:	.cfi_adjust_cfa_offset 4;                         \
		popl   %ecx;                                      \
		.cfi_adjust_cfa_offset -4;                        \
		addl   $(_GLOBAL_OFFSET_TABLE_ + (. - 1b)), %ecx; \
		leal   991b@GOTOFF(%ecx), %ecx;                   \
		call   dl_require_global;                         \
		movl   %eax, 16(%esp); /* RETURN_PC_OVERRIDE */   \
		.cfi_rel_offset %eip, 16;                         \
		popl_cfi_r %edx;                                  \
		popl_cfi_r %ecx;                                  \
		popl_cfi_r %eax;                                  \
		popfl_cfi_r;                                      \
		ret;                                              \
		.cfi_endproc;                                     \
	END(name)
BUILTIN_GLOBALS_ENUMERATE(DEFINE_GLOBAL_SYMBOL_IMPORT)
#undef DEFINE_GLOBAL_SYMBOL_IMPORT


	/* Same as `___tls_get_addr()', but uses CDECL instead of REGPARAM(1),
	 * meaning  that the pointer  to the tls_index  structure is stored at
	 * 4(%esp) upon entry, rather than within %eax */
.section .text
INTERN_FUNCTION(libdl___tls_get_addr)
	.cfi_startproc
	/* >> typedef struct {
	 * >>     uintptr_t ti_module;
	 * >>     uintptr_t ti_offset;
	 * >> } tls_index;
	 * ARGS: tls_index *4(%esp);
	 * RETURN: Address of the indicated object. */

	/* Load the TLS base address for the given object. */
	movl   4(%esp), %eax

INTERN_FUNCTION(libdl____tls_get_addr)
	pushl_cfi 4(%eax)

	/* Load the TLS base address for the given object. */
	movl   0(%eax), %ecx
	INTERN(libdl_dltlsbase)
	call   libdl_dltlsbase

	/* Add the offset of the pointed-to symbol. */
	popl_cfi %ecx
	addl   %ecx, %eax

	ret
END(libdl____tls_get_addr)
	.cfi_endproc
END(libdl___tls_get_addr)
DEFINE_PUBLIC_ALIAS(__tls_get_addr, libdl___tls_get_addr)
DEFINE_PUBLIC_ALIAS(___tls_get_addr, libdl____tls_get_addr)


.section .text
	/* The heart-piece of lazy symbol relocations:
	 *   - This function is called by user-code the first time an R_386_JMP_SLOT
	 *     relocation is accessed,  at which point  the relocation is  resolved.
	 *   - See the explanation about `PLTGOT' below for how this actually works.
	 */
INTERN_FUNCTION(dl_load_lazy_relocation)
	/* Called from PLTGOT:
	 * >> 00025ad0 <.plt>:
	 * >>    25ad0:	ff b3 04 00 00 00    	pushl  0x4(%ebx)
	 * >>    25ad6:	ff a3 08 00 00 00    	jmp    *0x8(%ebx)
	 * >>    25adc:	00 00                	add    %al,(%eax)
	 * >>    ...
	 * >>
	 * >> 00025b20 <dlsym@plt>:
	 * >>    25b20:	ff a3 1c 00 00 00    	jmp    *0x1c(%ebx)
	 * >>    25b26:	68 20 00 00 00       	push   $0x20
	 * >>    25b2b:	e9 a0 ff ff ff       	jmp    25ad0 <.plt>
	 *
	 * DL Initialization:
	 *  - *(u32 *)((byte_t *)MODULE->dm_elf.de_pltgot + 0x4) == MODULE
	 *  - *(u32 *)((byte_t *)MODULE->dm_elf.de_pltgot + 0x8) == &dl_load_lazy_relocation
	 *  - *(u32 *)((byte_t *)MODULE->dm_elf.de_pltgot + 0xc) == 0x25b26 (Pointer to the `push   $0x20')
	 *
	 * Lazy linkage procedure:
	 *  - User-code calls `dlsym(3D)', which is compiled as `call dlsym@plt'
	 *    Additionally,  user-code will have  set up `%ebx'  to point to the
	 *    associated module's PLT/GOT.
	 *  - Within `dlsym@plt', read a pointer from `GOT + 0x1c' and jump
	 *    to the address contained within.
	 *  - During module  initialization,  that  address  will  have  been  set
	 *    up to point to the address of the `push $0x20' immediately following
	 *    the `jmp *0x1c(%ebx)' instruction at the start of `dlsym@plt'
	 *    - This is done simply by resolving R_386_JMP_SLOT as:
	 *      >> *(u32 *)reladdr += module->dm_loadaddr;
	 *      Where `reladdr' is equal to `0x1c(%ebx)', which the linker will
	 *      have pre-initialized to be equal to the module-relative  offset
	 *      of the PLT/GOT entry to that push instruction.
	 *  - `push   $0x20' will then store 0x20 ontop of the stack
	 *    - This is an  offset into  the vector of  jmp-relocations, which  we
	 *      store in  `module->dm_elf.de_jmprel', and  can  be read  from  the
	 *      module's .dynamic section, where it is stored within a `DT_JMPREL'
	 *      tag.
	 *  - Next, execution jumps to the start of the PLT, where a piece of code
	 *    that  is common to  all jump-relocations pushes  the value stored at
	 *    `4(%ebp)'  (again: %ebp  points to the  PLT/GOT which by  the way is
	 *    referenced by a .dynamic tag `DT_PLTGOT').
	 *     - The  offset `4'  here is constant,  which we have  previously filled in
	 *       to be the address of the `DlModule' structure of the associated module.
	 *  - Finally, execution jumps to an address stored within `8(%ebp)',  which
	 *    is another fixed location which we've already filled in to contain the
	 *    address of this very function (`&dl_load_lazy_relocation')
	 *  - During the  process of  this function,  we override  `*0x1c(%ebx)'  such
	 *    that  the next call  to `dlsym@plt' will immediately  jump to the linked
	 *    symbol, rather than having to jump through all of the hoops to get here.
	 *
	 * So in other words, when we get here, our
	 * register/stack state  looks  like  this:
	 *  - 0(%esp)      == MODULE
	 *  - 4(%esp)      == 0x20   (Offset added to `self->dm_elf.de_jmprel' for the associated jump relocation)
	 *  - 8(%esp)      == User-return-address
	 *  - 12 + ?(%esp) == Undefined/user-owned
	 *  - %ebx         == MODULE->dm_elf.de_pltgot   (Though this detail is unimportant)
	 *
	 * Also note that since we don't know anything about the calling  convention
	 * with which the user intends to invoke the lazily linked function, we must
	 * make sure that we don't clobber any of their registers!
	 *
	 * HINT: In Glibc, this function's equivalent is called `_dl_runtime_resolve'
	 */
	.cfi_startproc
	.cfi_adjust_cfa_offset 8 /* MODULE + JMPREL_offset */

	/* Save registers */
	pushl_cfi_r %eax
	pushl_cfi_r %ecx
	pushl_cfi_r %edx

	pushfl_cfi_r

	movl   (16 + 0)(%esp), %ecx /* MODULE */
	movl   (16 + 4)(%esp), %edx /* JMPREL_offset */

	/* Patch the relocation. */
	INTERN(dl_bind_lazy_relocation)
	call   dl_bind_lazy_relocation

	popfl_cfi_r
	.cfi_register %eip, %eax

	popl_cfi_r %edx
	popl_cfi_r %ecx

	xchgl  %eax, (%esp) /* RESTORE(EAX); 0(%esp) = RESOLVED_ADDRESS */
	.cfi_same_value %eax
	.cfi_rel_offset %eip, 0
	ret    $(8)         /* EIP = [ESP]; ESP += (4 + 8);
	                     * Cleanup: RESOLVED_ADDRESS + MODULE + JMPREL_offset */
	.cfi_endproc
END(dl_load_lazy_relocation)

#endif /* !GUARD_LIBDL_ARCH_I386_RT32_S */
