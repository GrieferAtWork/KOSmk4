/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_I386_KOS_BITS_NOPF_H
#define _KOS_I386_KOS_BITS_NOPF_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/host.h>

#include <bits/types.h>
#include <kos/anno.h>

#ifdef __CC__
__DECL_BEGIN

#ifndef __ASMCALL
#define __ASMCALL /* nothing */
#endif /* !__ASMCALL */

#ifndef __COMPILER_ASM_BUFFER
#define __COMPILER_ASM_BUFFER(T, s, p) (*(T *)(p))
#endif /* !__COMPILER_ASM_BUFFER */

/* Figure out how we should call nofp functions. */
#if defined(__KOS__) && defined(__KERNEL__)
#define __X86_NOPF_AVAILABLE
#define __X86_NOPF_CALLASM(name, argno) "call " #name
#define __X86_NOPF_CALLARG(name)        /* nothing */
#elif defined(__CRT_KOS) && defined(__BUILDING_LIBC)
#define __X86_NOPF_AVAILABLE
#define __X86_NOPF_CALLASM(name, argno) "call libc_" #name
#define __X86_NOPF_CALLARG(name)        /* nothing */
#elif defined(__pic__)
#ifdef __x86_64__
/* On x86_64, the PLT doesn't require any special register to be loaded. */
#define __X86_NOPF_CALLASM(name, argno) "call " #name "@PLT"
#define __X86_NOPF_CALLARG(name)        /* nothing */
#elif defined(__HAVE_NO_PLT_RELOCATIONS) /* s.a. `__WANT_NO_PLT_RELOCATIONS' in <__stdinc.h> */
/* This works to  safely (and somewhat  efficiently) call  functions
 * from external libraries. However, sadly this doesn't use the PLT,
 * but  rather  the GOT  (like using  `__attribute__((noplt))'), and
 * thus prevents the use of lazy relocations...
 *
 * The alternative would be to manually load the GOT into %ebx (and
 * mark  %ebx as a  clobber register), though  that might result in
 * duplicate work in case GCC already  loaded the GOT into %ebx  or
 * some other reg. */
#define __X86_NOPF_CALLASM(name, argno) "call %A" #argno
#define __X86_NOPF_CALLARG(name)        , "g" (name)
#else /* ... */
#define __X86_NOPF_CALLASM(name, argno)                     \
	"call 991f\n\t" /* XXX: CFI may break for 1 instr... */ \
	"991: popl %%ebx\n\t"                                   \
	"addl $(_GLOBAL_OFFSET_TABLE_ + (. - 991b)), %%ebx\n\t" \
	"call " #name "@PLT"
#define __X86_NOPF_CALLARG(name) /* nothing */
#define __X86_NOPF_CALLCLB  : "ebx"
#define __X86_NOPF_CALLCLB_ : "ebx",
#endif /* !... */
#else /* ... */
/* Fallback: just call directly. */
#define __X86_NOPF_CALLASM(name, argno) "call " #name
#define __X86_NOPF_CALLARG(name)        /* nothing */
#endif /* !... */

#ifndef __X86_NOPF_CALLCLB
#define __X86_NOPF_CALLCLB  /* nothing */
#define __X86_NOPF_CALLCLB_ :
#endif /* !__X86_NOPF_CALLCLB */


/* All of the x86_nopf_* assembly functions behave as follows:
 *  #1 Clear the direction bit (every function starts with `cld')
 *  #2 Execute the instruction that is apart of function's name.
 *     e.g. `x86_nopf_repe_cmpsb'
 *      will execute `repe cmpsb'
 *  #3 Return to the caller (i.e. `ret')
 *  #4 If a #PF (or non-canon #GP on x86_64) is triggered during
 *     any  of this, the program counter to return to the caller
 *     with all registers unaltered from the point in time  when
 *     the #PF happened.
 *     In general, this means that these functions return  with
 *     with `%[er]cx != 0' when a copy-error happened, and with
 *     `%[er]cx == 0' upon success.
 */


#if defined(__CRT_HAVE_x86_nopf_rep_movsb) || defined(__X86_NOPF_AVAILABLE)
/* Assembly function:
 * >> PUBLIC_FUNCTION(x86_nopf_rep_movsb)
 * >>     cld
 * >>     rep;   movsb
 * >>     ret
 * >> END(x86_nopf_rep_movsb)
 * Yes. - That's literally the implementation.
 *
 * However there is something very special about it:
 *  - Whenever a #PF happens, the kernel will see if it originated from
 *    that `rep movsb' instruction.
 *    If it did, then instead of actually handling the #PF, the kernel will
 *    advance the  instruction pointer  to the  `ret' instruction,  causing
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
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_rep_movsb)(void);

/* Copy memory from `src' to `dst', but  stop if any sort of #PF  happens,
 * regardless of that #PF being handleable or not (aka: load-on-access, or
 * copy-on-write  will never be  triggered by this  function, and the same
 * also goes for VIO)
 * This function can be used to copy user-space memory whilst holding  an
 * atomic lock, allowing the caller to handle the PF by handling the next
 * data byte/word/etc. individually after releasing the atomic lock, thus
 * allowing a necessary #PF to run its course without the caller  holding
 * an atomic lock.
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transferred.
 *              The affected memory ranges are:
 *               - `dst + num_bytes - return ... dst + num_bytes - 1'
 *               - `src + num_bytes - return ... src + num_bytes - 1' */
#define __memcpy_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __size_t
__NOTHROW(memcpy_nopf)(__USER __CHECKED void *__dst,
                       __USER __CHECKED void const *__src,
                       __size_t __num_bytes) {
	__register __size_t __result;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_rep_movsb, 6)
	                     : "+D" (__dst)
	                     , "+S" (__src)
	                     , "=c" (__result)
	                     , "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __num_bytes, __dst))
	                     : "m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __num_bytes, __src))
	                     , "2" (__num_bytes)
	                     __X86_NOPF_CALLARG(x86_nopf_rep_movsb)
	                     __X86_NOPF_CALLCLB);
	return __result;
}
#endif /* __CRT_HAVE_x86_nopf_rep_movsb */




#if defined(__CRT_HAVE_x86_nopf_repe_cmpsb) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_repe_cmpsb)(void);
/* Compare the data pointed to by 2 potentially faulty memory buffers.
 * @return: >0: The contents of the 2 buffers differ from each other.
 * @return:  0: The contents of the 2 buffers are identical.
 * @return: <0: At least one of the 2 buffers is faulty. */
#define __memeq_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ssize_t
__NOTHROW(memeq_nopf)(__USER __CHECKED void const *__lhs,
                      __USER __CHECKED void const *__rhs,
                      __size_t __num_bytes) {
	__register __size_t __result;
	__BOOL __are_equal;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_repe_cmpsb, 7)
	                     : "+D" (__lhs)
	                     , "+S" (__rhs)
	                     , "=c" (__result)
	                     , "=@cce" (__are_equal)
	                     : "2" (__num_bytes)
	                     , "m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __num_bytes, __lhs))
	                     , "m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __num_bytes, __rhs))
	                     __X86_NOPF_CALLARG(x86_nopf_repe_cmpsb)
	                     __X86_NOPF_CALLCLB_ "cc");
	if __unlikely(__result)
		return -1;
	if (__are_equal)
		return 0;
	return 1;
}
#endif /* __CRT_HAVE_x86_nopf_repe_cmpsb */


#if defined(__CRT_HAVE_x86_nopf_rep_insb) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_rep_insb)(void);
/* @return: * : The # of bytes that could not be accessed */
#define __insb_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __size_t
__NOTHROW(insb_nopf)(__port_t __port, __USER __CHECKED void *__buf, __size_t __num_bytes) {
	__register __size_t __result;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_rep_insb, 5)
	                     : "+D" (__buf)
	                     , "=c" (__result)
	                     , "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __num_bytes, __buf))
	                     : "d" ((__uint16_t)__port)
	                     , "1" (__num_bytes)
	                     __X86_NOPF_CALLARG(x86_nopf_rep_insb)
	                     __X86_NOPF_CALLCLB);
	return __result;
}
#endif /* __CRT_HAVE_x86_nopf_rep_insb */

#if defined(__CRT_HAVE_x86_nopf_rep_insw) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_rep_insw)(void);
/* @return: * : The # of words that could not be accessed */
#define __insw_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __size_t
__NOTHROW(insw_nopf)(__port_t __port, __USER __CHECKED void *__buf, __size_t __num_words) {
	__register __size_t __result;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_rep_insw, 5)
	                     : "+D" (__buf)
	                     , "=c" (__result)
	                     , "=m" (__COMPILER_ASM_BUFFER(__UINT16_TYPE__, __num_words, __buf))
	                     : "d" ((__uint16_t)__port)
	                     , "1" (__num_words)
	                     __X86_NOPF_CALLARG(x86_nopf_rep_insw)
	                     __X86_NOPF_CALLCLB);
	return __result;
}
#endif /* __CRT_HAVE_x86_nopf_rep_insw */

#if defined(__CRT_HAVE_x86_nopf_rep_insl) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_rep_insl)(void);
/* @return: * : The # of d-words that could not be accessed */
#define __insl_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __size_t
__NOTHROW(insl_nopf)(__port_t __port, __USER __CHECKED void *__buf, __size_t __num_dwords) {
	__register __size_t __result;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_rep_insl, 5)
	                     : "+D" (__buf)
	                     , "=c" (__result)
	                     , "=m" (__COMPILER_ASM_BUFFER(__UINT32_TYPE__, __num_dwords, __buf))
	                     : "d" ((__uint16_t)__port)
	                     , "1" (__num_dwords)
	                     __X86_NOPF_CALLARG(x86_nopf_rep_insl)
	                     __X86_NOPF_CALLCLB);
	return __result;
}
#endif /* __CRT_HAVE_x86_nopf_rep_insl */

#if defined(__CRT_HAVE_x86_nopf_rep_outsb) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_rep_outsb)(void);
/* @return: * : The # of bytes that could not be accessed */
#define __outsb_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __size_t
__NOTHROW(outsb_nopf)(__port_t __port, __USER __CHECKED void const *__buf, __size_t __num_bytes) {
	__register __size_t __result;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_rep_outsb, 5)
	                     : "+S" (__buf)
	                     , "=c" (__result)
	                     , "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __num_bytes, __buf))
	                     : "d" ((__uint16_t)__port)
	                     , "1" (__num_bytes)
	                     __X86_NOPF_CALLARG(x86_nopf_rep_outsb)
	                     __X86_NOPF_CALLCLB);
	return __result;
}
#endif /* __CRT_HAVE_x86_nopf_rep_outsb */

#if defined(__CRT_HAVE_x86_nopf_rep_outsw) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_rep_outsw)(void);
/* @return: * : The # of words that could not be accessed */
#define __outsw_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __size_t
__NOTHROW(outsw_nopf)(__port_t __port, __USER __CHECKED void const *__buf, __size_t __num_words) {
	__register __size_t __result;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_rep_outsw, 5)
	                     : "+S" (__buf)
	                     , "=c" (__result)
	                     , "=m" (__COMPILER_ASM_BUFFER(__UINT16_TYPE__, __num_words, __buf))
	                     : "d" ((__uint16_t)__port)
	                     , "1" (__num_words)
	                     __X86_NOPF_CALLARG(x86_nopf_rep_outsw)
	                     __X86_NOPF_CALLCLB);
	return __result;
}
#endif /* __CRT_HAVE_x86_nopf_rep_outsw */

#if defined(__CRT_HAVE_x86_nopf_rep_outsl) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_rep_outsl)(void);
/* @return: * : The # of d-words that could not be accessed */
#define __outsl_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __size_t
__NOTHROW(outsl_nopf)(__port_t __port, __USER __CHECKED void const *__buf, __size_t __num_dwords) {
	__register __size_t __result;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_rep_outsl, 5)
	                     : "+S" (__buf)
	                     , "=c" (__result)
	                     , "=m" (__COMPILER_ASM_BUFFER(__UINT32_TYPE__, __num_dwords, __buf))
	                     : "d" ((__uint16_t)__port)
	                     , "1" (__num_dwords)
	                     __X86_NOPF_CALLARG(x86_nopf_rep_outsl)
	                     __X86_NOPF_CALLCLB);
	return __result;
}
#endif /* __CRT_HAVE_x86_nopf_rep_outsl */


/* Read/write a single user-space data word to/from (Pax|Pcx)<-->(rax|eax|ax|al)
 * NOTE: Upon success, EFLAGS.CF is cleared; Upon __error, EFLAGS.CF is set. */


#if defined(__CRT_HAVE_x86_nopf_movb_Pax_al) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_movb_Pax_al)(void); /* movb (%Pax), %al  (read byte) */
/* Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
#define __readb_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __BOOL
__NOTHROW(readb_nopf)(__USER __CHECKED void const *__addr, __uint8_t *__presult) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movb_Pax_al, 3)
	                     : "=a" (*__presult)
	                     , "=@ccc" (__error)
	                     : "a" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_movb_Pax_al)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_movb_Pax_al */

#if defined(__CRT_HAVE_x86_nopf_movw_Pax_ax) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_movw_Pax_ax)(void); /* movw (%Pax), %ax  (read word) */
/* Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
#define __readw_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __BOOL
__NOTHROW(readw_nopf)(__USER __CHECKED void const *__addr, __uint16_t *__presult) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movw_Pax_ax, 3)
	                     : "=a" (*__presult)
	                     , "=@ccc" (__error)
	                     : "a" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_movw_Pax_ax)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_movw_Pax_ax */

#if defined(__CRT_HAVE_x86_nopf_movl_Pax_eax) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_movl_Pax_eax)(void); /* movl (%Pax), %eax  (read dword) */
/* Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
#define __readl_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __BOOL
__NOTHROW(readl_nopf)(__USER __CHECKED void const *__addr, __uint32_t *__presult) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movl_Pax_eax, 3)
	                     : "=a" (*__presult)
	                     , "=@ccc" (__error)
	                     : "a" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_movl_Pax_eax)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_movl_Pax_eax */


#if (defined(__x86_64__)                                                            \
     ? (defined(__CRT_HAVE_x86_nopf_movq_Pax_rax) || defined(__X86_NOPF_AVAILABLE)) \
     : defined(__readl_nopf_defined))
#ifdef __x86_64__
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_movq_Pax_rax)(void); /* movq (%Pax), %rax  (read qword) */
#endif /* __x86_64__ */

/* Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
#define __readq_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __BOOL
__NOTHROW(readq_nopf)(__USER __CHECKED void const *__addr, __uint64_t *__presult) {
#ifdef __x86_64__
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movq_Pax_rax, 3)
	                     : "=a" (*__presult)
	                     , "=@ccc" (__error)
	                     : "a" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_movq_Pax_rax)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
#else /* __x86_64__ */
	return readl_nopf(__addr, (__uint32_t *)__presult) &&
	       readl_nopf((__BYTE_TYPE__ *)__addr + 4, (__uint32_t *)__presult + 1);
#endif /* !__x86_64__ */
}
#endif /* ... */

#if defined(__CRT_HAVE_x86_nopf_movb_al_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_movb_al_Pcx)(void);  /* movb %al, (%Pcx)  (write byte) */
/* Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
#define __writeb_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(writeb_nopf)(__USER __CHECKED void *__addr, __uint8_t __val) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movb_al_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__val)
	                     __X86_NOPF_CALLARG(x86_nopf_movb_al_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_movb_al_Pcx */

#if defined(__CRT_HAVE_x86_nopf_movw_ax_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_movw_ax_Pcx)(void);  /* movw %ax, (%Pcx)  (write word) */
/* Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
#define __writew_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(writew_nopf)(__USER __CHECKED void *__addr, __uint16_t __val) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movw_ax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__val)
	                     __X86_NOPF_CALLARG(x86_nopf_movw_ax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_movw_ax_Pcx */

#if defined(__CRT_HAVE_x86_nopf_movl_eax_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_movl_eax_Pcx)(void); /* movl %eax, (%Pcx)  (write dword) */
/* Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
#define __writel_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(writel_nopf)(__USER __CHECKED void *__addr, __uint32_t __val) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movl_eax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__val)
	                     __X86_NOPF_CALLARG(x86_nopf_movl_eax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_movl_eax_Pcx */

#if (defined(__x86_64__)                                                            \
     ? (defined(__CRT_HAVE_x86_nopf_movq_rax_Pcx) || defined(__X86_NOPF_AVAILABLE)) \
     : defined(__writel_nopf_defined))
#ifdef __x86_64__
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_movq_rax_Pcx)(void); /* movq %rax, (%Pcx)  (write qword) */
#endif /* __x86_64__ */
/* Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
#define __writeq_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(writeq_nopf)(__USER __CHECKED void *__addr, __uint64_t __val) {
#ifdef __x86_64__
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movq_rax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__val)
	                     __X86_NOPF_CALLARG(x86_nopf_movq_rax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
#else /* __x86_64__ */
	union {
		__uint64_t __q;
		__uint32_t __l[2];
	} __temp;
	__temp.__q = __val;
	return !writel_nopf(__addr, __temp.__l[0]) &&
	       !writel_nopf((__BYTE_TYPE__ *)__addr + 4, __temp.__l[1]);
#endif /* !__x86_64__ */
}
#endif /* ... */

#if defined(__CRT_HAVE_x86_nopf_rep_stosb) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_rep_stosb)(void);
/* @return: * : The # of bytes that could not be accessed */
#define __memset_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __size_t
__NOTHROW(memset_nopf)(__USER __CHECKED void *__dst, int __byte, __size_t __num_bytes) {
	__register __size_t __result;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_rep_stosb, 5)
	                     : "+D" (__dst)
	                     , "=c" (__result)
	                     , "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __num_bytes, __dst))
	                     : "a" ((__uint8_t)(unsigned int)__byte)
	                     , "1" (__num_bytes)
	                     __X86_NOPF_CALLARG(x86_nopf_rep_stosb)
	                     __X86_NOPF_CALLCLB);
	return __result;
}
#endif /* __CRT_HAVE_x86_nopf_rep_stosb */


/* Atomic *_nopf operations.
 * NOTE: Upon success, EFLAGS.CF is cleared; Upon __error, EFLAGS.CF is set. */


#if defined(__CRT_HAVE_x86_nopf_lock_xchgb_al_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_xchgb_al_Pcx)(void); /* lock xchgb %al, (%Pcx) -- ATOMIC_XCH(*(__uint8_t *)%Pcx, %al) */
/* Try  to ATOMIC_XCH  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
#define __atomic_xchb_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL
__NOTHROW(atomic_xchb_nopf)(__USER __CHECKED void const *__addr,
                            __uint8_t __newval, __uint8_t *__poldval) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xchgb_al_Pcx, 4)
	                     : "=a" (*__poldval)
	                     , "=@ccc" (__error)
	                     : "a" (__newval)
	                     , "c" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xchgb_al_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_lock_xchgb_al_Pcx */

#if defined(__CRT_HAVE_x86_nopf_lock_xchgw_ax_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_xchgw_ax_Pcx)(void); /* lock xchgw %ax, (%Pcx) -- ATOMIC_XCH(*(__uint16_t *)%Pcx, %ax) */
/* Try  to ATOMIC_XCH  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
#define __atomic_xchw_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL
__NOTHROW(atomic_xchw_nopf)(__USER __CHECKED void const *__addr,
                            __uint16_t __newval, __uint16_t *__poldval) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xchgw_ax_Pcx, 4)
	                     : "=a" (*__poldval)
	                     , "=@ccc" (__error)
	                     : "a" (__newval)
	                     , "c" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xchgw_ax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_lock_xchgw_ax_Pcx */

#if defined(__CRT_HAVE_x86_nopf_lock_xchgl_eax_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_xchgl_eax_Pcx)(void); /* lock xchgl %eax, (%Pcx) -- ATOMIC_XCH(*(__uint32_t *)%Pcx, %eax) */
/* Try  to ATOMIC_XCH  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
#define __atomic_xchl_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL
__NOTHROW(atomic_xchl_nopf)(__USER __CHECKED void const *__addr,
                            __uint32_t __newval, __uint32_t *__poldval) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xchgl_eax_Pcx, 4)
	                     : "=a" (*__poldval)
	                     , "=@ccc" (__error)
	                     : "a" (__newval)
	                     , "c" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xchgl_eax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_lock_xchgl_eax_Pcx */

#if defined(__x86_64__) && (defined(__CRT_HAVE_x86_nopf_lock_xchgq_rax_Pcx) || defined(__X86_NOPF_AVAILABLE))
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_xchgq_rax_Pcx)(void); /* lock xchgq %rax, (%Pcx) -- ATOMIC_XCH(*(__uint64_t *)%Pcx, %rax) */
/* Try  to ATOMIC_XCH  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
#define __atomic_xchq_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL
__NOTHROW(atomic_xchq_nopf)(__USER __CHECKED void const *__addr,
                            __uint64_t __newval, __uint64_t *__poldval) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xchgq_rax_Pcx, 4)
	                     : "=a" (*__poldval)
	                     , "=@ccc" (__error)
	                     : "a" (__newval)
	                     , "c" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xchgq_rax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* ... */


#if defined(__CRT_HAVE_x86_nopf_lock_xaddb_al_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_xaddb_al_Pcx)(void); /* lock xaddb %al, (%Pcx) -- ATOMIC_FETCHADD(*(__uint8_t *)%Pcx, %al) */
/* Try to ATOMIC_FETCHADD  at a possibly  faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored __val
 * Return `true' on success, `false' on fault */
#define __atomic_fetchaddb_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL
__NOTHROW(atomic_fetchaddb_nopf)(__USER __CHECKED void const *__addr,
                                 __uint8_t __addend, __uint8_t *__poldval) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xaddb_al_Pcx, 4)
	                     : "=a" (*__poldval)
	                     , "=@ccc" (__error)
	                     : "a" (__addend)
	                     , "c" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xaddb_al_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_lock_xaddb_al_Pcx */

#if defined(__CRT_HAVE_x86_nopf_lock_xaddw_ax_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_xaddw_ax_Pcx)(void); /* lock xaddw %ax, (%Pcx) -- ATOMIC_FETCHADD(*(__uint16_t *)%Pcx, %ax) */
/* Try to ATOMIC_FETCHADD  at a possibly  faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored __val
 * Return `true' on success, `false' on fault */
#define __atomic_fetchaddw_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL
__NOTHROW(atomic_fetchaddw_nopf)(__USER __CHECKED void const *__addr,
                                 __uint16_t __addend, __uint16_t *__poldval) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xaddw_ax_Pcx, 4)
	                     : "=a" (*__poldval)
	                     , "=@ccc" (__error)
	                     : "a" (__addend)
	                     , "c" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xaddw_ax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_lock_xaddw_ax_Pcx */

#if defined(__CRT_HAVE_x86_nopf_lock_xaddl_eax_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_xaddl_eax_Pcx)(void); /* lock xaddl %eax, (%Pcx) -- ATOMIC_FETCHADD(*(__uint32_t *)%Pcx, %eax) */
/* Try to ATOMIC_FETCHADD  at a possibly  faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored __val
 * Return `true' on success, `false' on fault */
#define __atomic_fetchaddl_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL
__NOTHROW(atomic_fetchaddl_nopf)(__USER __CHECKED void const *__addr,
                                 __uint32_t __addend, __uint32_t *__poldval) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xaddl_eax_Pcx, 4)
	                     : "=a" (*__poldval)
	                     , "=@ccc" (__error)
	                     : "a" (__addend)
	                     , "c" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xaddl_eax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_lock_xaddl_eax_Pcx */

#if defined(__x86_64__) && (defined(__CRT_HAVE_x86_nopf_lock_xaddq_rax_Pcx) || defined(__X86_NOPF_AVAILABLE))
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_xaddq_rax_Pcx)(void); /* lock xaddq %rax, (%Pcx) -- ATOMIC_FETCHADD(*(__uint64_t *)%Pcx, %rax) */
/* Try to ATOMIC_FETCHADD  at a possibly  faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored __val
 * Return `true' on success, `false' on fault */
#define __atomic_fetchaddq_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL
__NOTHROW(atomic_fetchaddq_nopf)(__USER __CHECKED void const *__addr,
                                 __uint64_t __addend, __uint64_t *__poldval) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xaddq_rax_Pcx, 4)
	                     : "=a" (*__poldval)
	                     , "=@ccc" (__error)
	                     : "a" (__addend)
	                     , "c" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xaddq_rax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* ... */

#if defined(__CRT_HAVE_x86_nopf_lock_orb_al_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_orb_al_Pcx)(void); /* lock orb %al, (%Pcx) -- ATOMIC_OR(*(__uint8_t *)%Pcx, %al) */
/* Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define __atomic_orb_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(atomic_orb_nopf)(__USER __CHECKED void *__addr, __uint8_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_orb_al_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_orb_al_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_lock_orb_al_Pcx */

#if defined(__CRT_HAVE_x86_nopf_lock_orw_ax_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_orw_ax_Pcx)(void); /* lock orw %ax, (%Pcx) -- ATOMIC_OR(*(__uint16_t *)%Pcx, %ax) */
/* Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define __atomic_orw_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(atomic_orw_nopf)(__USER __CHECKED void *__addr, __uint16_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_orw_ax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_orw_ax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_lock_orw_ax_Pcx */

#if defined(__CRT_HAVE_x86_nopf_lock_orl_eax_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_orl_eax_Pcx)(void); /* lock orl %eax, (%Pcx) -- ATOMIC_OR(*(__uint32_t *)%Pcx, %eax) */
/* Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define __atomic_orl_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(atomic_orl_nopf)(__USER __CHECKED void *__addr, __uint32_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_orl_eax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_orl_eax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_lock_orl_eax_Pcx */

#if defined(__x86_64__) && (defined(__CRT_HAVE_x86_nopf_lock_orq_rax_Pcx) || defined(__X86_NOPF_AVAILABLE))
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_orq_rax_Pcx)(void); /* lock orq %rax, (%Pcx) -- ATOMIC_OR(*(__uint64_t *)%Pcx, %rax) */
/* Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define __atomic_orq_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(atomic_orq_nopf)(__USER __CHECKED void *__addr, __uint64_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_orq_rax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_orq_rax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* ... */

#if defined(__CRT_HAVE_x86_nopf_lock_andb_al_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_andb_al_Pcx)(void); /* lock andb %al, (%Pcx) -- ATOMIC_AND(*(__uint8_t *)%Pcx, %al) */
/* Try to atomically __mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define __atomic_andb_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(atomic_andb_nopf)(__USER __CHECKED void *__addr, __uint8_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_andb_al_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_andb_al_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_lock_andb_al_Pcx */

#if defined(__CRT_HAVE_x86_nopf_lock_andw_ax_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_andw_ax_Pcx)(void); /* lock andw %ax, (%Pcx) -- ATOMIC_AND(*(__uint16_t *)%Pcx, %ax) */
/* Try to atomically __mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define __atomic_andw_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(atomic_andw_nopf)(__USER __CHECKED void *__addr, __uint16_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_andw_ax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_andw_ax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_lock_andw_ax_Pcx */

#if defined(__CRT_HAVE_x86_nopf_lock_andl_eax_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_andl_eax_Pcx)(void); /* lock andl %eax, (%Pcx) -- ATOMIC_AND(*(__uint32_t *)%Pcx, %eax) */
/* Try to atomically __mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define __atomic_andl_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(atomic_andl_nopf)(__USER __CHECKED void *__addr, __uint32_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_andl_eax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_andl_eax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_lock_andl_eax_Pcx */

#if defined(__x86_64__) && (defined(__CRT_HAVE_x86_nopf_lock_andq_rax_Pcx) || defined(__X86_NOPF_AVAILABLE))
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_andq_rax_Pcx)(void); /* lock andq %rax, (%Pcx) -- ATOMIC_AND(*(__uint64_t *)%Pcx, %rax) */
/* Try to atomically __mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define __atomic_andq_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(atomic_andq_nopf)(__USER __CHECKED void *__addr, __uint64_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_andq_rax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_andq_rax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* ... */

#if defined(__CRT_HAVE_x86_nopf_lock_xorb_al_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_xorb_al_Pcx)(void); /* lock xorb %al, (%Pcx) -- ATOMIC_XOR(*(__uint8_t *)%Pcx, %al) */
/* Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define __atomic_xorb_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(atomic_xorb_nopf)(__USER __CHECKED void *__addr, __uint8_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xorb_al_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xorb_al_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_lock_xorb_al_Pcx */

#if defined(__CRT_HAVE_x86_nopf_lock_xorw_ax_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_xorw_ax_Pcx)(void); /* lock xorw %ax, (%Pcx) -- ATOMIC_XOR(*(__uint16_t *)%Pcx, %ax) */
/* Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define __atomic_xorw_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(atomic_xorw_nopf)(__USER __CHECKED void *__addr, __uint16_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xorw_ax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xorw_ax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_lock_xorw_ax_Pcx */

#if defined(__CRT_HAVE_x86_nopf_lock_xorl_eax_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_xorl_eax_Pcx)(void); /* lock xorl %eax, (%Pcx) -- ATOMIC_XOR(*(__uint32_t *)%Pcx, %eax) */
/* Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define __atomic_xorl_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(atomic_xorl_nopf)(__USER __CHECKED void *__addr, __uint32_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xorl_eax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xorl_eax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_lock_xorl_eax_Pcx */

#if defined(__x86_64__) && (defined(__CRT_HAVE_x86_nopf_lock_xorq_rax_Pcx) || defined(__X86_NOPF_AVAILABLE))
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_xorq_rax_Pcx)(void); /* lock xorq %rax, (%Pcx) -- ATOMIC_XOR(*(__uint64_t *)%Pcx, %rax) */
/* Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define __atomic_xorq_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(atomic_xorq_nopf)(__USER __CHECKED void *__addr, __uint64_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xorq_rax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xorq_rax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* ... */

#if defined(__CRT_HAVE_x86_nopf_lock_cmpxchgb_dl_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_cmpxchgb_dl_Pcx)(void); /* lock cmpxchgb %dl, (%Pcx) -- ATOMIC_CMPXCH(*(__uint8_t *)%Pcx, %al, %dl) */
/* Try to do an atomic-compare-exchange at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define __atomic_cmpxchb_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((4)) __BOOL
__NOTHROW(atomic_cmpxchb_nopf)(__USER __CHECKED void *__addr,
                               __uint8_t __oldval, __uint8_t __newval,
                               __uint8_t *__preal_oldval) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_cmpxchgb_dl_Pcx, 5)
	                     : "=a" (*__preal_oldval)
	                     , "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__oldval)
	                     , "d" (__newval)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_cmpxchgb_dl_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_lock_cmpxchgb_dl_Pcx */

#if defined(__CRT_HAVE_x86_nopf_lock_cmpxchgw_dx_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_cmpxchgw_dx_Pcx)(void); /* lock cmpxchgw %dx, (%Pcx) -- ATOMIC_CMPXCH(*(__uint16_t *)%Pcx, %ax, %dx) */
/* Try to do an atomic-compare-exchange at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define __atomic_cmpxchw_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((4)) __BOOL
__NOTHROW(atomic_cmpxchw_nopf)(__USER __CHECKED void *__addr,
                               __uint16_t __oldval, __uint16_t __newval,
                               __uint16_t *__preal_oldval) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_cmpxchgw_dx_Pcx, 5)
	                     : "=a" (*__preal_oldval)
	                     , "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__oldval)
	                     , "d" (__newval)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_cmpxchgw_dx_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_lock_cmpxchgw_dx_Pcx */

#if defined(__CRT_HAVE_x86_nopf_lock_cmpxchgl_edx_Pcx) || defined(__X86_NOPF_AVAILABLE)
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_cmpxchgl_edx_Pcx)(void); /* lock cmpxchgl %edx, (%Pcx) -- ATOMIC_CMPXCH(*(__uint32_t *)%Pcx, %eax, %edx) */
/* Try to do an atomic-compare-exchange at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define __atomic_cmpxchl_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((4)) __BOOL
__NOTHROW(atomic_cmpxchl_nopf)(__USER __CHECKED void *__addr,
                               __uint32_t __oldval, __uint32_t __newval,
                               __uint32_t *__preal_oldval) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_cmpxchgl_edx_Pcx, 5)
	                     : "=a" (*__preal_oldval)
	                     , "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__oldval)
	                     , "d" (__newval)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_cmpxchgl_edx_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __CRT_HAVE_x86_nopf_lock_cmpxchgl_edx_Pcx */

#if defined(__x86_64__) && (defined(__CRT_HAVE_x86_nopf_lock_cmpxchgq_rdx_Pcx) || defined(__X86_NOPF_AVAILABLE))
__LIBC __NOBLOCK void __NOTHROW(__ASMCALL x86_nopf_lock_cmpxchgq_rdx_Pcx)(void); /* lock cmpxchgq %rdx, (%Pcx) -- ATOMIC_CMPXCH(*(__uint64_t *)%Pcx, %rax, %rdx) */
/* Try to do an atomic-compare-exchange at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define __atomic_cmpxchq_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((4)) __BOOL
__NOTHROW(atomic_cmpxchq_nopf)(__USER __CHECKED void *__addr,
                               __uint64_t __oldval, __uint64_t __newval,
                               __uint64_t *__preal_oldval) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_cmpxchgq_rdx_Pcx, 5)
	                     : "=a" (*__preal_oldval)
	                     , "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__oldval)
	                     , "d" (__newval)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_cmpxchgq_rdx_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* ... */

#undef __X86_NOPF_CALLASM
#undef __X86_NOPF_CALLARG
#undef __X86_NOPF_CALLCLB
#undef __X86_NOPF_CALLCLB_

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_I386_KOS_BITS_NOPF_H */
