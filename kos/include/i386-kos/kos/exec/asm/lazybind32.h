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
/*!replace_with_include <kos/exec/lazybind.h>*/
#ifndef _I386_KOS_KOS_EXEC_ASM_LAZYBIND32_H
#define _I386_KOS_KOS_EXEC_ASM_LAZYBIND32_H 1

#include <__stdinc.h>
#include <hybrid/__asm.h>

#if defined(__pic__) || defined(__PIC__) || \
    defined(__pie__) || defined(__PIE__)
#define __I386_IF_PIC(x)  x
#define __I386_NIF_PIC(x) /* nothing */
#else
#define __I386_IF_PIC(x)  /* nothing */
#define __I386_NIF_PIC(x) x
#endif

#define __I386_DEFINE_LAZYBIND_RUNTIME()                                                                    \
	__ASM_L(.ifndef __x86_lazybind)                                                                         \
	__ASM_L(.pushsection .text.__x86.lazybind,"axG",@progbits,__x86_lazybind,comdat)                        \
	__ASM_L(__x86_lazybind:)                                                                                \
	__ASM_L(	.cfi_startproc)                                                                             \
	__ASM_L(	xchgl  0(%esp), %eax)                                                                       \
	__ASM_L(	.cfi_rel_offset %eax, 0)                                                                    \
	__ASM_L(	.cfi_register %eip, %eax)                                                                   \
	__ASM_L(	pushl  %ecx)                                                                                \
	__ASM_L(	.cfi_adjust_cfa_offset 4)                                                                   \
	__ASM_L(	.cfi_rel_offset %ecx, 0)                                                                    \
	__ASM_L(	pushl  %edx)                                                                                \
	__ASM_L(	.cfi_adjust_cfa_offset 4)                                                                   \
	__ASM_L(	.cfi_rel_offset %edx, 0)                                                                    \
	__ASM_L(	pushfl)                                                                                     \
	__ASM_L(	.cfi_adjust_cfa_offset 4)                                                                   \
	__ASM_L(	.cfi_rel_offset %eflags, 0)                                                                 \
	__ASM_L(	pushl  %eax)               /* ADDR_OF_RELATIVE_GETADDR */                                   \
	__ASM_L(	.cfi_adjust_cfa_offset 4)                                                                   \
	__ASM_L(	.cfi_rel_offset %eip, 0)                                                                    \
	__I386_IF_PIC(__ASM_L(addl (%eax), %eax))                                                               \
	__ASM_L(	call   *%eax)              /* Invoke `getaddr()' */                                         \
	__ASM_L(	.cfi_register %eip, %eax)                                                                   \
	__ASM_L(	popl   %ecx)                                                                                \
	__ASM_L(	.cfi_adjust_cfa_offset -4)                                                                  \
	__ASM_L(	subl   $(5), %ecx)         /* %ecx == OPERAND_OF(jmp 1f) + 4 */                             \
	__ASM_L(	movl   %eax, %edx)         /* %edx == RETURN_OF_GETADDR */                                  \
	__ASM_L(	subl   %ecx, %edx)         /* %edx == DISP(RETURN_OF_GETADDR)@(OPERAND_OF(jmp 1f) + 4) */   \
	__ASM_L(	lock;  xchgl (%ecx), %edx) /* Override the jmp target of binding (using an atomic write) */ \
	__ASM_L(	xchgl  12(%esp), %eax)     /* Save return address */                                        \
	__ASM_L(	.cfi_rel_offset %eip, 12)                                                                   \
	__ASM_L(	.cfi_same_value %eax)                                                                       \
	__ASM_L(	popfl)                                                                                      \
	__ASM_L(	.cfi_adjust_cfa_offset -4)                                                                  \
	__ASM_L(	.cfi_same_value %eflags)                                                                    \
	__ASM_L(	popl   %edx)                                                                                \
	__ASM_L(	.cfi_adjust_cfa_offset -4)                                                                  \
	__ASM_L(	.cfi_same_value %edx)                                                                       \
	__ASM_L(	popl   %ecx)                                                                                \
	__ASM_L(	.cfi_adjust_cfa_offset -4)                                                                  \
	__ASM_L(	.cfi_same_value %ecx)                                                                       \
	__ASM_L(	ret)                       /* Return to the resolved address */                             \
	__ASM_L(	.cfi_endproc)                                                                               \
	__ASM_L(.size __x86_lazybind, . - __x86_lazybind)                                                       \
	__ASM_L(.popsection))                                                                                   \
	__ASM_L(.endif) /* __x86_lazybind */

/* >> __I386_DO_LAZYBIND(SYMBOL name, void *getaddr(void))
 * Define  a self-modifying  function that lazily  invokes `getaddr()', then  uses that function's
 * return  value as a text location to jump to, permanently re-writing itself such that any future
 * calls to `name' will always be forwarded to the initially returned address, without `getaddr()'
 * having to be called ever again. */
#define __I386_DO_LAZYBIND(name, getaddr, ...)                                                    \
	__ASM_BEGIN                                                                                   \
	__I386_DEFINE_LAZYBIND_RUNTIME()                                                              \
	__ASM_L(.pushsection .xdata)                                                                  \
	__ASM_L(.type name, @function __VA_ARGS__)                                                    \
	__ASM_L(.set name, .)                                                                         \
	__ASM_L(.byte 0xe9; .long 0)                                        /* jmp 1f; 1: */          \
	__ASM_L(.byte 0xe8; .reloc ., R_386_PC32, __x86_lazybind; .long -4) /* call __x86_lazybind */ \
	__I386_IF_PIC(__ASM_L(.reloc ., R_386_PC32, getaddr; .long 0))                                \
	__I386_NIF_PIC(__ASM_L(.long getaddr))                                                        \
	__ASM_L(.size name, . - name)                                                                 \
	__ASM_L(.popsection)                                                                          \
	__ASM_END


#endif /* !_I386_KOS_KOS_EXEC_ASM_LAZYBIND32_H */
