/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_BITS_VA_LIST_STRUCT64_H
#define _I386_KOS_BITS_VA_LIST_STRUCT64_H 1

#include <__stdinc.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>
#include <hybrid/__pointer.h>
#include <hybrid/__asm.h>
#include <ieee754.h>


/* Required assembly:

----------------------------------------  C:  ----------------------------------------
extern int vfuncf(char const *format, __builtin_va_list args);

int funcf(char const *format, ...) {
	int result;
	__builtin_va_list args;
	__builtin_va_start(args, format);
	result = vfuncf(format, args);
	__builtin_va_end(args);
	return result;
}

----------------------------------------  ASM:  ----------------------------------------
	.globl funcf
	.type  funcf, @function
funcf:
	.cfi_startproc
	subq   $216, %rsp
	.cfi_def_cfa_offset 224
	movq   %rsi, 40(%rsp)     // x86_64_va_list_reg_save_area::rsa_rsi
	movq   %rdx, 48(%rsp)     // x86_64_va_list_reg_save_area::rsa_rdx
	movq   %rcx, 56(%rsp)     // x86_64_va_list_reg_save_area::rsa_rcx
	movq   %r8,  64(%rsp)     // x86_64_va_list_reg_save_area::rsa_r8
	movq   %r9,  72(%rsp)     // x86_64_va_list_reg_save_area::rsa_r9
	testb  %al, %al           // SysV: When a function taking variable-arguments is called,
	                          //       %rax must be set to the total number of floating point
	                          //       parameters passed to the function in vector registers
	je     1f
	movaps %xmm0, 80(%rsp)    //
	movaps %xmm1, 96(%rsp)    //
	movaps %xmm2, 112(%rsp)   //
	movaps %xmm3, 128(%rsp)   //
	movaps %xmm4, 144(%rsp)   //
	movaps %xmm5, 160(%rsp)   //
	movaps %xmm6, 176(%rsp)   //
	movaps %xmm7, 192(%rsp)   //
1:
	movl   $8, 8(%rsp)        // x86_64_va_list_struct::vl_gp_offset
	movl   $48, 12(%rsp)      // x86_64_va_list_struct::vl_fp_offset
	leaq   224(%rsp), %rax
	movq   %rax, 16(%rsp)     // x86_64_va_list_struct::vl_overflow_arg_area
	leaq   32(%rsp), %rax
	movq   %rax, 24(%rsp)     // x86_64_va_list_struct::vl_reg_save_area

	leaq   8(%rsp), %rsi      // vfuncf:args
	call   vfuncf
	addq   $216, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.size funcf, . - funcf
 */


/* All of the specs (SysV for AMD64) say that this should be 16,
 * but  in practice, GCC  always behaves as if  this was 8 (This
 * happens  both in KOS's  own toolchain, as  well as within the
 * standard gcc of an x86_64 linux machine)
 * In case this turns out  to be a weird quirk  of gcc, please make  use
 * of  this macro within hand-written assembly, such that your code will
 * work with X86_64_VA_LIST_XMM_COUNT=8 and X86_64_VA_LIST_XMM_COUNT=16.
 * Other values may be assumed to never be applicable. */
#if 1
#define X86_64_VA_LIST_XMM_COUNT 8
#else
#define X86_64_VA_LIST_XMM_COUNT 16
#endif


#if X86_64_VA_LIST_XMM_COUNT == 8
#define X86_64_VA_LIST_SAVE_XMM(dst) \
	__ASM_BEGIN                      \
	__ASM_L(movaps %xmm0, 0+dst)     \
	__ASM_L(movaps %xmm1, 8+dst)     \
	__ASM_L(movaps %xmm2, 16+dst)    \
	__ASM_L(movaps %xmm3, 24+dst)    \
	__ASM_L(movaps %xmm4, 32+dst)    \
	__ASM_L(movaps %xmm5, 40+dst)    \
	__ASM_L(movaps %xmm6, 48+dst)    \
	__ASM_L(movaps %xmm7, 56+dst)    \
	__ASM_END
#elif X86_64_VA_LIST_XMM_COUNT == 16
#define X86_64_VA_LIST_SAVE_XMM(dst) \
	__ASM_BEGIN                      \
	__ASM_L(movaps %xmm0,  0+dst)    \
	__ASM_L(movaps %xmm1,  8+dst)    \
	__ASM_L(movaps %xmm2,  16+dst)   \
	__ASM_L(movaps %xmm3,  24+dst)   \
	__ASM_L(movaps %xmm4,  32+dst)   \
	__ASM_L(movaps %xmm5,  40+dst)   \
	__ASM_L(movaps %xmm6,  48+dst)   \
	__ASM_L(movaps %xmm7,  56+dst)   \
	__ASM_L(movaps %xmm8,  64+dst)   \
	__ASM_L(movaps %xmm9,  72+dst)   \
	__ASM_L(movaps %xmm10, 80+dst)   \
	__ASM_L(movaps %xmm11, 88+dst)   \
	__ASM_L(movaps %xmm12, 96+dst)   \
	__ASM_L(movaps %xmm13, 104+dst)  \
	__ASM_L(movaps %xmm14, 112+dst)  \
	__ASM_L(movaps %xmm15, 120+dst)  \
	__ASM_END
#else /* X86_64_VA_LIST_XMM_COUNT == ... */
#error "Unsupported `X86_64_VA_LIST_XMM_COUNT'"
#endif /* X86_64_VA_LIST_XMM_COUNT != ... */




/* typedef struct va_list_struct *va_list; */
#ifdef __x86_64__
#define x86_64_va_list_struct va_list_struct
#endif /* __x86_64__ */



#define OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_RDI 0
#define OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_RSI 8
#define OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_RDX 16
#define OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_RCX 24
#define OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_R8  32
#define OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_R9  40
#define OFFSET_X86_64_VA_LIST_REG_SAVE_AREA_XMM(i) (48 + (i) * 16)
#if X86_64_VA_LIST_XMM_COUNT == 8
#define SIZEOF_X86_64_VA_LIST_REG_SAVE_AREA     176
#elif X86_64_VA_LIST_XMM_COUNT == 16
#define SIZEOF_X86_64_VA_LIST_REG_SAVE_AREA     304
#else /* X86_64_VA_LIST_XMM_COUNT == ... */
#define SIZEOF_X86_64_VA_LIST_REG_SAVE_AREA    (48 + X86_64_VA_LIST_XMM_COUNT * 16)
#endif /* X86_64_VA_LIST_XMM_COUNT != ... */

#define OFFSET_X86_64_VA_LIST_STRUCT_GP_OFFSET         0
#define OFFSET_X86_64_VA_LIST_STRUCT_FP_OFFSET         4
#define OFFSET_X86_64_VA_LIST_STRUCT_OVERFLOW_ARG_AREA 8
#define OFFSET_X86_64_VA_LIST_STRUCT_REG_SAVE_AREA     16
#define SIZEOF_X86_64_VA_LIST_STRUCT                   24

#ifdef __CC__
__DECL_BEGIN

struct x86_64_va_list_reg_save_area /*[PREFIX(rsa_)]*/ {
	__UINT64_TYPE__           rsa_rdi; /* 1st argument */
	__UINT64_TYPE__           rsa_rsi; /* 2nd argument */
	__UINT64_TYPE__           rsa_rdx; /* 3rd argument */
	__UINT64_TYPE__           rsa_rcx; /* 4th argument */
	__UINT64_TYPE__           rsa_r8;  /* 5th argument */
	__UINT64_TYPE__           rsa_r9;  /* 6th argument */
	union ieee854_long_double rsa_xmm[X86_64_VA_LIST_XMM_COUNT];
};

struct x86_64_va_list_struct /*[PREFIX(vl_)]*/ {
	/* From here:
	 * https://stackoverflow.com/questions/4958384/what-is-the-format-of-the-x86-64-va-list-structure */
	__UINT32_TYPE__ vl_gp_offset;         /* This element holds the  offset in bytes from  vl_reg_save_area
	                                       * to the place where the next available general purpose argument
	                                       * register is saved.  In case all  argument registers have  been
	                                       * exhausted, it is set to the value 48 (6 * 8). */
	__UINT32_TYPE__ vl_fp_offset;         /* This  element holds  the offset  in bytes  from vl_reg_save_area to
	                                       * the place where the next available floating point argument register
	                                       * is  saved.  In case  all  argument registers  have  been exhausted,
	                                       * it is set to the value 304 (6 * 8 + 16 * 16). */
	__HYBRID_PTR64(__BYTE_TYPE__)
	                vl_overflow_arg_area; /* This  pointer is used  to fetch arguments  passed on the stack.
	                                       * It is initialized with the address of the first argument passed
	                                       * on  the stack, if any, and then  always updated to point to the
	                                       * start of the next argument on the stack. */
	__HYBRID_PTR64(struct x86_64_va_list_reg_save_area)
	                vl_reg_save_area;     /* The element points to the start of the register save area */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_BITS_VA_LIST_STRUCT64_H */
