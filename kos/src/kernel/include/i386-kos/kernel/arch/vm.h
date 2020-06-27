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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_VM_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_VM_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <hybrid/host.h>

#undef CONFIG_VM_ARCH_DEFINES_MEMCPY_NOPF
#define CONFIG_VM_ARCH_DEFINES_MEMCPY_NOPF 1
#undef CONFIG_VM_ARCH_DEFINES_MEMSET_NOPF
#define CONFIG_VM_ARCH_DEFINES_MEMSET_NOPF 1
#undef CONFIG_VM_ARCH_DEFINES_MEMEQ_NOPF
#define CONFIG_VM_ARCH_DEFINES_MEMEQ_NOPF 1
#undef CONFIG_VM_ARCH_DEFINES_READBWLQ_NOPF
#define CONFIG_VM_ARCH_DEFINES_READBWLQ_NOPF 1
#undef CONFIG_VM_ARCH_DEFINES_WRITEBWLQ_NOPF
#define CONFIG_VM_ARCH_DEFINES_WRITEBWLQ_NOPF 1

DECL_BEGIN

#ifdef __CC__

#ifndef __COMPILER_ASM_BUFFER
#define __COMPILER_ASM_BUFFER(T, s, p) (*(T *)(p))
#endif /* !__COMPILER_ASM_BUFFER */



/* Assembly function:
 * >> PUBLIC_FUNCTION(x86_nopf_rep_movsb)
 * >>     cld
 * >>     rep;   movsb
 * >>     ret
 * >> END(x86_nopf_rep_movsb)
 * Yes. - That's literally the implementation,
 * however there is something very special about it:
 *  - Whenever a #PF happens, the kernel will see if it originated from
 *    that `rep movsb' instruction.
 *    If it did, then instead of actually handling the #PF, the kernel will
 *    advance the instruction pointer to the `ret' instruction, causing
 *    the `rep' to be aborted.
 * IN:
 *   - USER CHECKED void       *%edi:  Destination pointer
 *   - USER CHECKED void const *%esi:  Source pointer
 *   - size_t                   %ecx:  Copy size
 * OUT:
 *   - %edi:  == IN(%edi) + (IN(%ecx) - OUT(%ecx))
 *   - %esi:  == IN(%esi) + (IN(%ecx) - OUT(%ecx))
 *   - %ecx:  Number of bytes that were not copied.
 *   - %cr2:  if (OUT(%ecx) == 0)
 *                <UNCHANGED>
 *            else if (OUT(%cr2) == OUT(%edi))
 *                <#PF in `dst'>
 *            else if (OUT(%cr2) == OUT(%esi))
 *                <#PF in `src'>
 */
FUNDEF NOBLOCK void NOTHROW(ASMCALL x86_nopf_rep_movsb)();

/* All of the x86_nopf_* assembly functions behave as follows:
 *  #1 Clear the direction bit (every function starts with `cld')
 *  #2 Execute the instruction that is apart of function's name.
 *     e.g. `x86_nopf_repe_cmpsb'
 *      will execute `repe cmpsb'
 *  #3 Return to the caller (i.e. `ret')
 *  #4 If a #PF (or non-canon #GP on x86_64) is triggered during
 *     any of this, the program counter to return to the caller
 *     with all registers unaltered from the point in time when
 *     the #PF happened.
 *     In general, this means that these functions return with
 *     with `%[er]cx != 0' when a copy-error happened, and with
 *     `%[er]cx == 0' upon success.
 */
FUNDEF NOBLOCK void NOTHROW(ASMCALL x86_nopf_rep_stosb)();
FUNDEF NOBLOCK void NOTHROW(ASMCALL x86_nopf_repe_cmpsb)();
FUNDEF NOBLOCK void NOTHROW(ASMCALL x86_nopf_rep_insb)();
FUNDEF NOBLOCK void NOTHROW(ASMCALL x86_nopf_rep_insw)();
FUNDEF NOBLOCK void NOTHROW(ASMCALL x86_nopf_rep_insl)();
FUNDEF NOBLOCK void NOTHROW(ASMCALL x86_nopf_rep_outsb)();
FUNDEF NOBLOCK void NOTHROW(ASMCALL x86_nopf_rep_outsw)();
FUNDEF NOBLOCK void NOTHROW(ASMCALL x86_nopf_rep_outsl)();

/* Compare the data pointed to by 2 potentially faulty memory buffers.
 * @return: >0: The contents of the 2 buffers differ from each other.
 * @return:  0: The contents of the 2 buffers are identical.
 * @return: <0: At least one of the 2 buffers is faulty. */
FORCELOCAL NOBLOCK WUNUSED ssize_t
NOTHROW(KCALL memeq_nopf)(USER CHECKED void const *lhs,
                          USER CHECKED void const *rhs,
                          size_t num_bytes) {
	__register size_t result;
	__BOOL are_equal;
	__asm__ __volatile__("call x86_nopf_repe_cmpsb"
	                     : "+D" (lhs)
	                     , "+S" (rhs)
	                     , "=c" (result)
	                     , "=@cce" (are_equal)
	                     : "2" (num_bytes)
	                     , "m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, num_bytes, lhs))
	                     , "m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, num_bytes, rhs))
	                     : "cc");
	if unlikely(result)
		return -1;
	if (are_equal)
		return 0;
	return 1;
}

/* @return: * : The # of bytes that could not be accessed */
FORCELOCAL NOBLOCK WUNUSED size_t
NOTHROW(KCALL insb_nopf)(port_t port, void *buf, size_t num_bytes) {
	__register size_t result;
	__asm__ __volatile__("call x86_nopf_rep_insb"
	                     : "+D" (buf)
	                     , "=c" (result)
	                     , "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, num_bytes, buf))
	                     : "d" ((u16)port)
	                     , "1" (num_bytes));
	return result;
}

/* @return: * : The # of bytes that could not be accessed */
FORCELOCAL NOBLOCK WUNUSED size_t
NOTHROW(KCALL insw_nopf)(port_t port, void *buf, size_t num_words) {
	__register size_t result;
	__asm__ __volatile__("call x86_nopf_rep_insw"
	                     : "+D" (buf)
	                     , "=c" (result)
	                     , "=m" (__COMPILER_ASM_BUFFER(__UINT16_TYPE__, num_words, buf))
	                     : "d" ((u16)port)
	                     , "1" (num_words));
	return result;
}

/* @return: * : The # of bytes that could not be accessed */
FORCELOCAL NOBLOCK WUNUSED size_t
NOTHROW(KCALL insl_nopf)(port_t port, void *buf, size_t num_dwords) {
	__register size_t result;
	__asm__ __volatile__("call x86_nopf_rep_insl"
	                     : "+D" (buf)
	                     , "=c" (result)
	                     , "=m" (__COMPILER_ASM_BUFFER(__UINT32_TYPE__, num_dwords, buf))
	                     : "d" ((u16)port)
	                     , "1" (num_dwords));
	return result;
}

/* @return: * : The # of bytes that could not be accessed */
FORCELOCAL NOBLOCK WUNUSED size_t
NOTHROW(KCALL outsb_nopf)(port_t port, void const *buf, size_t num_bytes) {
	__register size_t result;
	__asm__ __volatile__("call x86_nopf_rep_outsb"
	                     : "+S" (buf)
	                     , "=c" (result)
	                     , "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, num_bytes, buf))
	                     : "d" ((u16)port)
	                     , "1" (num_bytes));
	return result;
}

/* @return: * : The # of bytes that could not be accessed */
FORCELOCAL NOBLOCK WUNUSED size_t
NOTHROW(KCALL outsw_nopf)(port_t port, void const *buf, size_t num_words) {
	__register size_t result;
	__asm__ __volatile__("call x86_nopf_rep_outsw"
	                     : "+S" (buf)
	                     , "=c" (result)
	                     , "=m" (__COMPILER_ASM_BUFFER(__UINT16_TYPE__, num_words, buf))
	                     : "d" ((u16)port)
	                     , "1" (num_words));
	return result;
}

/* @return: * : The # of bytes that could not be accessed */
FORCELOCAL NOBLOCK WUNUSED size_t
NOTHROW(KCALL outsl_nopf)(port_t port, void const *buf, size_t num_dwords) {
	__register size_t result;
	__asm__ __volatile__("call x86_nopf_rep_outsl"
	                     : "+S" (buf)
	                     , "=c" (result)
	                     , "=m" (__COMPILER_ASM_BUFFER(__UINT32_TYPE__, num_dwords, buf))
	                     : "d" ((u16)port)
	                     , "1" (num_dwords));
	return result;
}


/* Read/write a single user-space data word to/from (Pax|Pcx)<-->(rax|eax|ax|al)
 * NOTE: Upon success, EFLAGS.CF is cleared; Upon error, EFLAGS.CF is set. */
FUNDEF NOBLOCK void NOTHROW(ASMCALL x86_nopf_movb_Pax_al)();  /* movb (%eax), %al  (read byte) */
FUNDEF NOBLOCK void NOTHROW(ASMCALL x86_nopf_movw_Pax_ax)();  /* movw (%eax), %ax  (read word) */
FUNDEF NOBLOCK void NOTHROW(ASMCALL x86_nopf_movl_Pax_eax)(); /* movl (%eax), %eax (read dword) */
FUNDEF NOBLOCK void NOTHROW(ASMCALL x86_nopf_movb_al_Pcx)();  /* movb %al, (%ecx)  (write byte) */
FUNDEF NOBLOCK void NOTHROW(ASMCALL x86_nopf_movw_ax_Pcx)();  /* movw %ax, (%ecx)  (write word) */
FUNDEF NOBLOCK void NOTHROW(ASMCALL x86_nopf_movl_eax_Pcx)(); /* movl %eax, (%ecx) (write dword) */
#ifdef __x86_64__
FUNDEF NOBLOCK void NOTHROW(ASMCALL x86_nopf_movq_Pax_rax)(); /* movq (%rax), %rax (read qword) */
FUNDEF NOBLOCK void NOTHROW(ASMCALL x86_nopf_movq_rax_Pcx)(); /* movq %rax, (%rcx) (write qword) */
#endif /* __x86_64__ */

/* Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on error */
FORCELOCAL NOBLOCK WUNUSED bool
NOTHROW(KCALL readb_nopf)(USER CHECKED void const *addr,
                          u8 *presult) {
	bool error;
	__asm__ __volatile__("call x86_nopf_movb_Pax_al"
	                     : "=a" (*presult)
	                     , "=@ccc" (error)
	                     : "a" (addr)
	                     : "cc");
	return !error;
}

/* Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on error */
FORCELOCAL NOBLOCK WUNUSED bool
NOTHROW(KCALL readw_nopf)(USER CHECKED void const *addr,
                          u16 *presult) {
	bool error;
	__asm__ __volatile__("call x86_nopf_movw_Pax_ax"
	                     : "=a" (*presult)
	                     , "=@ccc" (error)
	                     : "a" (addr)
	                     : "cc");
	return !error;
}

/* Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on error */
FORCELOCAL NOBLOCK WUNUSED bool
NOTHROW(KCALL readl_nopf)(USER CHECKED void const *addr,
                          u32 *presult) {
	bool error;
	__asm__ __volatile__("call x86_nopf_movl_Pax_eax"
	                     : "=a" (*presult)
	                     , "=@ccc" (error)
	                     : "a" (addr)
	                     : "cc");
	return !error;
}

/* Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on error */
FORCELOCAL NOBLOCK WUNUSED bool
NOTHROW(KCALL readq_nopf)(USER CHECKED void const *addr,
                          u64 *presult) {
#ifdef __x86_64__
	bool error;
	__asm__ __volatile__("call x86_nopf_movq_Pax_rax"
	                     : "=a" (*presult)
	                     , "=@ccc" (error)
	                     : "a" (addr)
	                     : "cc");
	return !error;
#else /* __x86_64__ */
	return readl_nopf(addr, (u32 *)presult) &&
	       readl_nopf((byte_t *)addr + 4, (u32 *)presult + 1);
#endif /* !__x86_64__ */
}

/* Try to write `value' into a possibly faulty `addr'
 * Return `true' on success, `false' on error */
FORCELOCAL NOBLOCK WUNUSED bool
NOTHROW(KCALL writeb_nopf)(USER CHECKED void *addr,
                           u8 value) {
	bool error;
	__asm__ __volatile__("call x86_nopf_movb_al_Pcx"
	                     : "=@ccc" (error)
	                     : "c" (addr)
	                     , "a" (value)
	                     : "cc");
	return !error;
}

/* Try to write `value' into a possibly faulty `addr'
 * Return `true' on success, `false' on error */
FORCELOCAL NOBLOCK WUNUSED bool
NOTHROW(KCALL writew_nopf)(USER CHECKED void *addr,
                           u16 value) {
	bool error;
	__asm__ __volatile__("call x86_nopf_movw_ax_Pcx"
	                     : "=@ccc" (error)
	                     : "c" (addr)
	                     , "a" (value)
	                     : "cc");
	return !error;
}

/* Try to write `value' into a possibly faulty `addr'
 * Return `true' on success, `false' on error */
FORCELOCAL NOBLOCK WUNUSED bool
NOTHROW(KCALL writel_nopf)(USER CHECKED void *addr,
                           u32 value) {
	bool error;
	__asm__ __volatile__("call x86_nopf_movl_eax_Pcx"
	                     : "=@ccc" (error)
	                     : "c" (addr)
	                     , "a" (value)
	                     : "cc");
	return !error;
}

/* Try to write `value' into a possibly faulty `addr'
 * Return `true' on success, `false' on error */
FORCELOCAL NOBLOCK WUNUSED bool
NOTHROW(KCALL writeq_nopf)(USER CHECKED void *addr,
                           u64 value) {
#ifdef __x86_64__
	bool error;
	__asm__ __volatile__("call x86_nopf_movq_rax_Pcx"
	                     : "=@ccc" (error)
	                     : "c" (addr)
	                     , "a" (value)
	                     : "cc");
	return !error;
#else /* __x86_64__ */
	union {
		u64 q;
		u32 l[2];
	} val;
	val.q = value;
	return !writel_nopf(addr, val.l[0]) &&
	       !writel_nopf((byte_t *)addr + 4, val.l[1]);
#endif /* !__x86_64__ */
}



/* Copy memory from `src' to `dst', but stop if any sort of #PF happens,
 * regardless of that #PF being handleable or not (aka: load-on-access, or
 * copy-on-write will never be triggered by this function, and the same
 * also goes for VIO)
 * This function can be used to copy user-space memory whilst holding an
 * atomic lock, allowing the caller to handle the PF by handling the next
 * data byte/word/etc. individually after releasing the atomic lock, thus
 * allowing a necessary #PF to run its course without the caller holding
 * an atomic lock.
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transfered.
 *              The affected memory ranges are:
 *               - `dst + num_bytes - return ... dst + num_bytes - 1'
 *               - `src + num_bytes - return ... src + num_bytes - 1' */
FORCELOCAL NOBLOCK WUNUSED size_t
NOTHROW(KCALL memcpy_nopf)(USER CHECKED void *dst,
                           USER CHECKED void const *src,
                           size_t num_bytes) {
	__register size_t result;
	__asm__ __volatile__("call x86_nopf_rep_movsb"
	                     : "+D" (dst)
	                     , "+S" (src)
	                     , "=c" (result)
	                     , "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, num_bytes, dst))
	                     : "m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, num_bytes, src))
	                     , "2" (num_bytes));
	return result;
}

/* @return: * : The # of bytes that could not be accessed */
FORCELOCAL NOBLOCK WUNUSED size_t
NOTHROW(KCALL memset_nopf)(USER CHECKED void *dst,
                           int byte,
                           size_t num_bytes) {
	__register size_t result;
	__asm__ __volatile__("call x86_nopf_rep_stosb"
	                     : "+D" (dst)
	                     , "=c" (result)
	                     , "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, num_bytes, dst))
	                     : "a" ((u8)(unsigned int)byte)
	                     , "1" (num_bytes));
	return result;
}





DATDEF byte_t x86_nopf_begin[];   /* Start address for NOPF memory access PC values */
DATDEF byte_t x86_nopf_end_clc[]; /* End of NOPF handlers that should return to `x86_nopf_ret_stc' */
DATDEF byte_t x86_nopf_end[];     /* End address for NOPF memory access PC values */
DATDEF byte_t x86_nopf_ret_stc[]; /* Set the carry bit and return to the caller */
DATDEF byte_t x86_nopf_ret[];     /* Return PC for #PF with `x86_nopf_check(pc) == true' */

/* Return the #PF-execution-resume address for a #PF that happened at `pc', where
 * pc is apart of a x86_nopf_* function, as indicated by `x86_nopf_check(pc) == true' */
#define x86_nopf_retof(pc)                         \
	((uintptr_t)(pc) < (uintptr_t)x86_nopf_end_clc \
	 ? (uintptr_t)x86_nopf_ret_stc                 \
	 : (uintptr_t)x86_nopf_ret)

#define x86_nopf_check(pc)                           \
	((uintptr_t)(pc) >= (uintptr_t)x86_nopf_begin && \
	 (uintptr_t)(pc) < (uintptr_t)x86_nopf_end)


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_VM_H */
