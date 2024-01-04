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
#ifndef GUARD_LIBC_HYBRID_ARCH_I386_EXCEPT_S
#define GUARD_LIBC_HYBRID_ARCH_I386_EXCEPT_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <cfi.h>
#include <asm/instr/compat.h>
#include <kos/bits/exception_info.h>
#include <kos/except.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>

#ifdef __KERNEL__
EXTERN(this_exception_code)
EXTERN(this_exception_flags)
EXTERN(this_exception_trace)
EXTERN(this_exception_args)
EXTERN(this_exception_faultaddr)
EXTERN(this_exception_state)

#define FIELD_EXCEPT_CODE          %segtls:this_exception_code
#define FIELD_ERROR_FLAGS          %segtls:this_exception_flags
#define FIELD_ERROR_TRACE(off)     %segtls:this_exception_trace + (off)
#define FIELD_ERROR_POINTERS(off)  %segtls:this_exception_args + (off)
#define FIELD_ERROR_FAULTADDR      %segtls:this_exception_faultaddr
#define FIELD_ERROR_REGISTERS(off) %segtls:this_exception_state + (off)
#define SECTION_EXCEPT_TEXT        .text
#else /* __KERNEL__ */
#define FIELD_EXCEPT_CODE          OFFSET_EXCEPTION_INFO_CODE(%Pax)
#define FIELD_ERROR_FLAGS          OFFSET_EXCEPTION_INFO_FLAGS(%Pax)
#define FIELD_ERROR_POINTERS(off)  (OFFSET_EXCEPTION_INFO_POINTERS + (off))(%Pax)
#define FIELD_ERROR_FAULTADDR      (OFFSET_EXCEPTION_INFO_DATA + __OFFSET_EXCEPTION_DATA_FAULTADDR)(%Pax)
#define FIELD_ERROR_TRACE(off)     (OFFSET_EXCEPTION_INFO_TRACE + (off))(%Pax)
#define FIELD_ERROR_REGISTERS(off) (OFFSET_EXCEPTION_INFO_STATE + (off))(%Pax)
#define SECTION_EXCEPT_TEXT        .text.crt.except
#endif /* !__KERNEL__ */

#ifdef __KERNEL__
#define IK(...) __VA_ARGS__
#define IU(...) /* nothing */
#else /* __KERNEL__ */
#define IK(...) /* nothing */
#define IU(...) __VA_ARGS__
#endif /* !__KERNEL__ */


.section SECTION_EXCEPT_TEXT
DEFINE_PUBLIC_ALIAS(_except_check_no_nesting, libc__except_check_no_nesting)
DEFINE_PUBLIC_ALIAS(_except_badusage_no_nesting, libc__except_badusage_no_nesting)
INTERN_FUNCTION(libc__except_check_no_nesting)
	.cfi_startproc
IU(	INTERN(libc_except_info))
IU(	call   libc_except_info)
	cmpP   $(EXCEPT_CODEOF(E_OK)), FIELD_EXCEPT_CODE
	jne    libc__except_badusage_no_nesting /* ERROR: Illegal TRY-nesting */
	ret
INTERN_FUNCTION(libc__except_badusage_no_nesting)
	ASM_PUSH_KCPUSTATE_AFTER_PIP_CFI_R
	movP   %Psp, %R_fcall0P
	EXTERN(libc_except_badusage_no_nesting)
	call   libc_except_badusage_no_nesting
	nop    /* For unwinding... */
END(libc__except_badusage_no_nesting)
	.cfi_endproc
END(libc__except_check_no_nesting)


#endif /* !GUARD_LIBC_HYBRID_ARCH_I386_EXCEPT_S */
