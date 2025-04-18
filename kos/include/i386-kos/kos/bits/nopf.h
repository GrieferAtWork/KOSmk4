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
/*!included_by <kos/nopf.h>*/
#ifndef _I386_KOS_KOS_BITS_NOPF_H
#define _I386_KOS_KOS_BITS_NOPF_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#include <bits/types.h>
#include <kos/anno.h>

/* Figure out how we should call nofp functions. */
#if defined(__KOS__) && defined(__KERNEL__)
#define __X86_NOPF_AVAILABLE
#elif defined(__KOS__) && defined(__BUILDING_LIBC)
#define __X86_NOPF_AVAILABLE
#else /* ... */
#include <__crt.h>
#endif /* !... */


#if defined(__CRT_HAVE_x86_nopf_rep_movsb) || defined(__X86_NOPF_AVAILABLE)
#define __arch_memcpy_nopf __arch_memcpy_nopf
#endif /* __CRT_HAVE_x86_nopf_rep_movsb || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_repe_cmpsb) || defined(__X86_NOPF_AVAILABLE)
#define __arch_nopf_memeq __arch_nopf_memeq
#endif /* __CRT_HAVE_x86_nopf_repe_cmpsb || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_rep_insb) || defined(__X86_NOPF_AVAILABLE)
#define __arch_insb_nopf __arch_insb_nopf
#endif /* __CRT_HAVE_x86_nopf_rep_insb || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_rep_insw) || defined(__X86_NOPF_AVAILABLE)
#define __arch_insw_nopf __arch_insw_nopf
#endif /* __CRT_HAVE_x86_nopf_rep_insw || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_rep_insl) || defined(__X86_NOPF_AVAILABLE)
#define __arch_insl_nopf __arch_insl_nopf
#endif /* __CRT_HAVE_x86_nopf_rep_insl || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_rep_outsb) || defined(__X86_NOPF_AVAILABLE)
#define __arch_outsb_nopf __arch_outsb_nopf
#endif /* __CRT_HAVE_x86_nopf_rep_outsb || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_rep_outsw) || defined(__X86_NOPF_AVAILABLE)
#define __arch_outsw_nopf __arch_outsw_nopf
#endif /* __CRT_HAVE_x86_nopf_rep_outsw || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_rep_outsl) || defined(__X86_NOPF_AVAILABLE)
#define __arch_outsl_nopf __arch_outsl_nopf
#endif /* __CRT_HAVE_x86_nopf_rep_outsl || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_movb_Pax_al) || defined(__X86_NOPF_AVAILABLE)
#define __arch_readb_nopf __arch_readb_nopf
#endif /* __CRT_HAVE_x86_nopf_movb_Pax_al || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_movw_Pax_ax) || defined(__X86_NOPF_AVAILABLE)
#define __arch_readw_nopf __arch_readw_nopf
#endif /* __CRT_HAVE_x86_nopf_movw_Pax_ax || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_movl_Pax_eax) || defined(__X86_NOPF_AVAILABLE)
#define __arch_readl_nopf __arch_readl_nopf
#endif /* __CRT_HAVE_x86_nopf_movl_Pax_eax || __X86_NOPF_AVAILABLE */
#if defined(__x86_64__) && (defined(__CRT_HAVE_x86_nopf_movq_Pax_rax) || defined(__X86_NOPF_AVAILABLE))
#define __arch_readq_nopf __arch_readq_nopf
#endif /* __x86_64__ && (__CRT_HAVE_x86_nopf_movq_Pax_rax || __X86_NOPF_AVAILABLE) */
#if defined(__CRT_HAVE_x86_nopf_movb_al_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_writeb_nopf __arch_writeb_nopf
#endif /* __CRT_HAVE_x86_nopf_movb_al_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_movw_ax_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_writew_nopf __arch_writew_nopf
#endif /* __CRT_HAVE_x86_nopf_movw_ax_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_movl_eax_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_writel_nopf __arch_writel_nopf
#endif /* __CRT_HAVE_x86_nopf_movl_eax_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__x86_64__) && (defined(__CRT_HAVE_x86_nopf_movq_rax_Pcx) || defined(__X86_NOPF_AVAILABLE))
#define __arch_writeq_nopf __arch_writeq_nopf
#endif /* __x86_64__ && (__CRT_HAVE_x86_nopf_movq_rax_Pcx || __X86_NOPF_AVAILABLE) */
#if defined(__CRT_HAVE_x86_nopf_rep_stosb) || defined(__X86_NOPF_AVAILABLE)
#define __arch_memset_nopf __arch_memset_nopf
#endif /* __CRT_HAVE_x86_nopf_rep_stosb || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_lock_xchgb_al_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_atomic_xchb_nopf __arch_atomic_xchb_nopf
#endif /* __CRT_HAVE_x86_nopf_lock_xchgb_al_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_lock_xchgw_ax_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_atomic_xchw_nopf __arch_atomic_xchw_nopf
#endif /* __CRT_HAVE_x86_nopf_lock_xchgw_ax_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_lock_xchgl_eax_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_atomic_xchl_nopf __arch_atomic_xchl_nopf
#endif /* __CRT_HAVE_x86_nopf_lock_xchgl_eax_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__x86_64__) && (defined(__CRT_HAVE_x86_nopf_lock_xchgq_rax_Pcx) || defined(__X86_NOPF_AVAILABLE))
#define __arch_atomic_xchq_nopf __arch_atomic_xchq_nopf
#endif /* __x86_64__ && (__CRT_HAVE_x86_nopf_lock_xchgq_rax_Pcx || __X86_NOPF_AVAILABLE) */
#if defined(__CRT_HAVE_x86_nopf_lock_xaddb_al_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_atomic_fetchaddb_nopf __arch_atomic_fetchaddb_nopf
#endif /* __CRT_HAVE_x86_nopf_lock_xaddb_al_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_lock_xaddw_ax_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_atomic_fetchaddw_nopf __arch_atomic_fetchaddw_nopf
#endif /* __CRT_HAVE_x86_nopf_lock_xaddw_ax_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_lock_xaddl_eax_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_atomic_fetchaddl_nopf __arch_atomic_fetchaddl_nopf
#endif /* __CRT_HAVE_x86_nopf_lock_xaddl_eax_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__x86_64__) && (defined(__CRT_HAVE_x86_nopf_lock_xaddq_rax_Pcx) || defined(__X86_NOPF_AVAILABLE))
#define __arch_atomic_fetchaddq_nopf __arch_atomic_fetchaddq_nopf
#endif /* __x86_64__ && (__CRT_HAVE_x86_nopf_lock_xaddq_rax_Pcx || __X86_NOPF_AVAILABLE) */
#if defined(__CRT_HAVE_x86_nopf_lock_orb_al_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_atomic_orb_nopf __arch_atomic_orb_nopf
#endif /* __CRT_HAVE_x86_nopf_lock_orb_al_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_lock_orw_ax_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_atomic_orw_nopf __arch_atomic_orw_nopf
#endif /* __CRT_HAVE_x86_nopf_lock_orw_ax_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_lock_orl_eax_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_atomic_orl_nopf __arch_atomic_orl_nopf
#endif /* __CRT_HAVE_x86_nopf_lock_orl_eax_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__x86_64__) && (defined(__CRT_HAVE_x86_nopf_lock_orq_rax_Pcx) || defined(__X86_NOPF_AVAILABLE))
#define __arch_atomic_orq_nopf __arch_atomic_orq_nopf
#endif /* __x86_64__ && (__CRT_HAVE_x86_nopf_lock_orq_rax_Pcx || __X86_NOPF_AVAILABLE) */
#if defined(__CRT_HAVE_x86_nopf_lock_andb_al_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_atomic_andb_nopf __arch_atomic_andb_nopf
#endif /* __CRT_HAVE_x86_nopf_lock_andb_al_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_lock_andw_ax_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_atomic_andw_nopf __arch_atomic_andw_nopf
#endif /* __CRT_HAVE_x86_nopf_lock_andw_ax_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_lock_andl_eax_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_atomic_andl_nopf __arch_atomic_andl_nopf
#endif /* __CRT_HAVE_x86_nopf_lock_andl_eax_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__x86_64__) && (defined(__CRT_HAVE_x86_nopf_lock_andq_rax_Pcx) || defined(__X86_NOPF_AVAILABLE))
#define __arch_atomic_andq_nopf __arch_atomic_andq_nopf
#endif /* __x86_64__ && (__CRT_HAVE_x86_nopf_lock_andq_rax_Pcx || __X86_NOPF_AVAILABLE) */
#if defined(__CRT_HAVE_x86_nopf_lock_xorb_al_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_atomic_xorb_nopf __arch_atomic_xorb_nopf
#endif /* __CRT_HAVE_x86_nopf_lock_xorb_al_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_lock_xorw_ax_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_atomic_xorw_nopf __arch_atomic_xorw_nopf
#endif /* __CRT_HAVE_x86_nopf_lock_xorw_ax_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_lock_xorl_eax_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_atomic_xorl_nopf __arch_atomic_xorl_nopf
#endif /* __CRT_HAVE_x86_nopf_lock_xorl_eax_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__x86_64__) && (defined(__CRT_HAVE_x86_nopf_lock_xorq_rax_Pcx) || defined(__X86_NOPF_AVAILABLE))
#define __arch_atomic_xorq_nopf __arch_atomic_xorq_nopf
#endif /* __x86_64__ && (__CRT_HAVE_x86_nopf_lock_xorq_rax_Pcx || __X86_NOPF_AVAILABLE) */
#if defined(__CRT_HAVE_x86_nopf_lock_cmpxchgb_dl_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_atomic_cmpxchb_nopf __arch_atomic_cmpxchb_nopf
#endif /* __CRT_HAVE_x86_nopf_lock_cmpxchgb_dl_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_lock_cmpxchgw_dx_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_atomic_cmpxchw_nopf __arch_atomic_cmpxchw_nopf
#endif /* __CRT_HAVE_x86_nopf_lock_cmpxchgw_dx_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_lock_cmpxchgl_edx_Pcx) || defined(__X86_NOPF_AVAILABLE)
#define __arch_atomic_cmpxchl_nopf __arch_atomic_cmpxchl_nopf
#endif /* __CRT_HAVE_x86_nopf_lock_cmpxchgl_edx_Pcx || __X86_NOPF_AVAILABLE */
#if defined(__x86_64__) && (defined(__CRT_HAVE_x86_nopf_lock_cmpxchgq_rdx_Pcx) || defined(__X86_NOPF_AVAILABLE))
#define __arch_atomic_cmpxchq_nopf __arch_atomic_cmpxchq_nopf
#endif /* __x86_64__ && (__CRT_HAVE_x86_nopf_lock_cmpxchgq_rdx_Pcx || __X86_NOPF_AVAILABLE) */

/* X86-specific nopf read/write with fs/gs segment */
#if defined(__CRT_HAVE_x86_nopf_movb_al_fsPcx) || defined(__X86_NOPF_AVAILABLE)
#define __x86_writefsb_nopf __x86_writefsb_nopf
#endif /* __CRT_HAVE_x86_nopf_movb_al_fsPcx || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_movb_fsPax_al) || defined(__X86_NOPF_AVAILABLE)
#define __x86_readfsb_nopf __x86_readfsb_nopf
#endif /* __CRT_HAVE_x86_nopf_movb_fsPax_al || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_movw_fsPax_ax) || defined(__X86_NOPF_AVAILABLE)
#define __x86_readfsw_nopf __x86_readfsw_nopf
#endif /* __CRT_HAVE_x86_nopf_movw_fsPax_ax || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_movw_ax_fsPcx) || defined(__X86_NOPF_AVAILABLE)
#define __x86_writefsw_nopf __x86_writefsw_nopf
#endif /* __CRT_HAVE_x86_nopf_movw_ax_fsPcx || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_movl_fsPax_eax) || defined(__X86_NOPF_AVAILABLE)
#define __x86_readfsl_nopf __x86_readfsl_nopf
#endif /* __CRT_HAVE_x86_nopf_movl_fsPax_eax || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_movl_eax_fsPcx) || defined(__X86_NOPF_AVAILABLE)
#define __x86_writefsl_nopf __x86_writefsl_nopf
#endif /* __CRT_HAVE_x86_nopf_movl_eax_fsPcx || __X86_NOPF_AVAILABLE */
#if defined(__x86_64__) && (defined(__CRT_HAVE_x86_nopf_movq_fsPax_rax) || defined(__X86_NOPF_AVAILABLE))
#define __x86_readfsq_nopf __x86_readfsq_nopf
#endif /* __x86_64__ && (__CRT_HAVE_x86_nopf_movq_fsPax_rax || __X86_NOPF_AVAILABLE) */
#if defined(__x86_64__) && (defined(__CRT_HAVE_x86_nopf_movq_rax_fsPcx) || defined(__X86_NOPF_AVAILABLE))
#define __x86_writefsq_nopf __x86_writefsq_nopf
#endif /* __x86_64__ && (__CRT_HAVE_x86_nopf_movq_rax_fsPcx || __X86_NOPF_AVAILABLE) */

#if defined(__CRT_HAVE_x86_nopf_movb_al_gsPcx) || defined(__X86_NOPF_AVAILABLE)
#define __x86_writegsb_nopf __x86_writegsb_nopf
#endif /* __CRT_HAVE_x86_nopf_movb_al_gsPcx || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_movb_gsPax_al) || defined(__X86_NOPF_AVAILABLE)
#define __x86_readgsb_nopf __x86_readgsb_nopf
#endif /* __CRT_HAVE_x86_nopf_movb_gsPax_al || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_movw_gsPax_ax) || defined(__X86_NOPF_AVAILABLE)
#define __x86_readgsw_nopf __x86_readgsw_nopf
#endif /* __CRT_HAVE_x86_nopf_movw_gsPax_ax || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_movw_ax_gsPcx) || defined(__X86_NOPF_AVAILABLE)
#define __x86_writegsw_nopf __x86_writegsw_nopf
#endif /* __CRT_HAVE_x86_nopf_movw_ax_gsPcx || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_movl_gsPax_eax) || defined(__X86_NOPF_AVAILABLE)
#define __x86_readgsl_nopf __x86_readgsl_nopf
#endif /* __CRT_HAVE_x86_nopf_movl_gsPax_eax || __X86_NOPF_AVAILABLE */
#if defined(__CRT_HAVE_x86_nopf_movl_eax_gsPcx) || defined(__X86_NOPF_AVAILABLE)
#define __x86_writegsl_nopf __x86_writegsl_nopf
#endif /* __CRT_HAVE_x86_nopf_movl_eax_gsPcx || __X86_NOPF_AVAILABLE */
#if defined(__x86_64__) && (defined(__CRT_HAVE_x86_nopf_movq_gsPax_rax) || defined(__X86_NOPF_AVAILABLE))
#define __x86_readgsq_nopf __x86_readgsq_nopf
#endif /* __x86_64__ && (__CRT_HAVE_x86_nopf_movq_gsPax_rax || __X86_NOPF_AVAILABLE) */
#if defined(__x86_64__) && (defined(__CRT_HAVE_x86_nopf_movq_rax_gsPcx) || defined(__X86_NOPF_AVAILABLE))
#define __x86_writegsq_nopf __x86_writegsq_nopf
#endif /* __x86_64__ && (__CRT_HAVE_x86_nopf_movq_rax_gsPcx || __X86_NOPF_AVAILABLE) */


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
#define __X86_NOPF_CALLASM(name, argno) "call " #name
#define __X86_NOPF_CALLARG(name)        /* nothing */
#elif defined(__CRT_KOS) && defined(__BUILDING_LIBC)
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
#define __X86_NOPF_DEFFUN(name)         __LIBC __NOBLOCK void __NOTHROW(__ASMCALL name)(void);
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
#ifndef __X86_NOPF_DEFFUN
#define __X86_NOPF_DEFFUN(name) /* nothing */
#endif /* !__X86_NOPF_DEFFUN */


/* All of the x86_nopf_* assembly functions behave as follows:
 *  #1 Clear the carry bit (every function (except `*rep*' ones) starts with `clc')
 *  #2 Execute the instruction that is apart of function's name.
 *     e.g. `x86_nopf_repe_cmpsb'
 *      will execute `repe cmpsb'
 *  #3 Return to the caller (i.e. `ret')
 *  #4 If a #PF (or non-canon  #GP on x86_64) is triggered  during
 *     any  of this, the  program counter to  return to the caller
 *     with all registers  unaltered from the  point in time  when
 *     the #PF happened (except that non-*rep* functions set stc).
 *     In general,  this means  that these  functions return  with
 *     with `%[er]cx != 0' when  a copy-error  happened, and  with
 *     `%[er]cx == 0' upon success.
 */


#ifdef __arch_memcpy_nopf
/* Assembly function:
 * >> PUBLIC_FUNCTION(x86_nopf_rep_movsb)
 * >> #ifdef __KERNEL__
 * >>     cld
 * >> #endif // __KERNEL__
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
 *   - NCX void       *%Pdi:  Destination pointer
 *   - NCX void const *%Psi:  Source pointer
 *   - size_t          %Pcx:  Copy size
 * OUT:
 *   - %Pdi:  == IN(%Pdi) + (IN(%Pcx) - OUT(%Pcx))
 *   - %Psi:  == IN(%Psi) + (IN(%Pcx) - OUT(%Pcx))
 *   - %Pcx:  Number of bytes that were not copied.
 *   - %cr2:  if (OUT(%Pcx) == 0)
 *                <UNCHANGED>
 *            else if (OUT(%cr2) == OUT(%Pdi))
 *                <#PF in `dst'>
 *            else if (OUT(%cr2) == OUT(%Psi))
 *                <#PF in `src'>
 */
__X86_NOPF_DEFFUN(x86_nopf_rep_movsb)

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
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __size_t
__NOTHROW(__arch_memcpy_nopf)(__NCX void *__dst,
                              __NCX void const *__src,
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
#endif /* __arch_memcpy_nopf */




#ifdef __arch_nopf_memeq
__X86_NOPF_DEFFUN(x86_nopf_repe_cmpsb)
/* Compare the data pointed to by 2 potentially faulty memory buffers.
 * @return: >0: The contents of the 2 buffers differ from each other.
 * @return:  0: The contents of the 2 buffers are identical.
 * @return: <0: At least one of the 2 buffers is faulty. */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ssize_t
__NOTHROW(__arch_nopf_memeq)(__NCX void const *__lhs,
                             __NCX void const *__rhs,
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
#endif /* __arch_nopf_memeq */


#ifdef __arch_insb_nopf
__X86_NOPF_DEFFUN(x86_nopf_rep_insb)
/* @return: * : The # of bytes that could not be accessed */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __size_t
__NOTHROW(__arch_insb_nopf)(__port_t __port, __NCX void *__buf, __size_t __num_bytes) {
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
#endif /* __arch_insb_nopf */

#ifdef __arch_insw_nopf
__X86_NOPF_DEFFUN(x86_nopf_rep_insw)
/* @return: * : The # of words that could not be accessed */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __size_t
__NOTHROW(__arch_insw_nopf)(__port_t __port, __NCX void *__buf, __size_t __num_words) {
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
#endif /* __arch_insw_nopf */

#ifdef __arch_insl_nopf
__X86_NOPF_DEFFUN(x86_nopf_rep_insl)
/* @return: * : The # of d-words that could not be accessed */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __size_t
__NOTHROW(__arch_insl_nopf)(__port_t __port, __NCX void *__buf, __size_t __num_dwords) {
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
#endif /* __arch_insl_nopf */

#ifdef __arch_outsb_nopf
__X86_NOPF_DEFFUN(x86_nopf_rep_outsb)
/* @return: * : The # of bytes that could not be accessed */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __size_t
__NOTHROW(__arch_outsb_nopf)(__port_t __port, __NCX void const *__buf, __size_t __num_bytes) {
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
#endif /* __arch_outsb_nopf */

#ifdef __arch_outsw_nopf
__X86_NOPF_DEFFUN(x86_nopf_rep_outsw)
/* @return: * : The # of words that could not be accessed */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __size_t
__NOTHROW(__arch_outsw_nopf)(__port_t __port, __NCX void const *__buf, __size_t __num_words) {
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
#endif /* __arch_outsw_nopf */

#ifdef __arch_outsl_nopf
__X86_NOPF_DEFFUN(x86_nopf_rep_outsl)
/* @return: * : The # of d-words that could not be accessed */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __size_t
__NOTHROW(__arch_outsl_nopf)(__port_t __port, __NCX void const *__buf, __size_t __num_dwords) {
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
#endif /* __arch_outsl_nopf */


/* Read/write a single user-space data word to/from (Pax|Pcx)<-->(rax|eax|ax|al)
 * NOTE: Upon success, EFLAGS.CF is cleared; Upon error, EFLAGS.CF is set. */


#ifdef __arch_readb_nopf
__X86_NOPF_DEFFUN(x86_nopf_movb_Pax_al) /* movb (%Pax), %al  (read byte) */
/* Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __BOOL
__NOTHROW(__arch_readb_nopf)(__NCX void const *__addr, __uint8_t *__presult) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movb_Pax_al, 3)
	                     : "=a" (*__presult)
	                     , "=@ccc" (__error)
	                     : "a" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_movb_Pax_al)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __arch_readb_nopf */

#ifdef __arch_readw_nopf
__X86_NOPF_DEFFUN(x86_nopf_movw_Pax_ax) /* movw (%Pax), %ax  (read word) */
/* Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __BOOL
__NOTHROW(__arch_readw_nopf)(__NCX void const *__addr, __uint16_t *__presult) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movw_Pax_ax, 3)
	                     : "=a" (*__presult)
	                     , "=@ccc" (__error)
	                     : "a" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_movw_Pax_ax)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __arch_readw_nopf */

#ifdef __arch_readl_nopf
__X86_NOPF_DEFFUN(x86_nopf_movl_Pax_eax) /* movl (%Pax), %eax  (read dword) */
/* Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __BOOL
__NOTHROW(__arch_readl_nopf)(__NCX void const *__addr, __uint32_t *__presult) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movl_Pax_eax, 3)
	                     : "=a" (*__presult)
	                     , "=@ccc" (__error)
	                     : "a" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_movl_Pax_eax)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __arch_readl_nopf */

#ifdef __arch_readq_nopf
__X86_NOPF_DEFFUN(x86_nopf_movq_Pax_rax) /* movq (%Pax), %rax  (read qword) */

/* Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __BOOL
__NOTHROW(__arch_readq_nopf)(__NCX void const *__addr, __uint64_t *__presult) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movq_Pax_rax, 3)
	                     : "=a" (*__presult)
	                     , "=@ccc" (__error)
	                     : "a" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_movq_Pax_rax)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __arch_readq_nopf */

#ifdef __arch_writeb_nopf
__X86_NOPF_DEFFUN(x86_nopf_movb_al_Pcx)  /* movb %al, (%Pcx)  (write byte) */
/* Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_writeb_nopf)(__NCX void *__addr, __uint8_t __val) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movb_al_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__val)
	                     __X86_NOPF_CALLARG(x86_nopf_movb_al_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __arch_writeb_nopf */

#ifdef __arch_writew_nopf
__X86_NOPF_DEFFUN(x86_nopf_movw_ax_Pcx)  /* movw %ax, (%Pcx)  (write word) */
/* Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_writew_nopf)(__NCX void *__addr, __uint16_t __val) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movw_ax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__val)
	                     __X86_NOPF_CALLARG(x86_nopf_movw_ax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __arch_writew_nopf */

#ifdef __arch_writel_nopf
__X86_NOPF_DEFFUN(x86_nopf_movl_eax_Pcx) /* movl %eax, (%Pcx)  (write dword) */
/* Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_writel_nopf)(__NCX void *__addr, __uint32_t __val) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movl_eax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__val)
	                     __X86_NOPF_CALLARG(x86_nopf_movl_eax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __arch_writel_nopf */

#ifdef __arch_writeq_nopf
__X86_NOPF_DEFFUN(x86_nopf_movq_rax_Pcx) /* movq %rax, (%Pcx)  (write qword) */

/* Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_writeq_nopf)(__NCX void *__addr, __uint64_t __val) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movq_rax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__val)
	                     __X86_NOPF_CALLARG(x86_nopf_movq_rax_Pcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __arch_writeq_nopf */

#ifdef __arch_memset_nopf
__X86_NOPF_DEFFUN(x86_nopf_rep_stosb)
/* @return: * : The # of bytes that could not be accessed */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __size_t
__NOTHROW(__arch_memset_nopf)(__NCX void *__dst, int __byte, __size_t __num_bytes) {
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
#endif /* __arch_memset_nopf */


/* Atomic *_nopf operations.
 * NOTE: Upon success, EFLAGS.CF is cleared; Upon __error, EFLAGS.CF is set. */


#ifdef __arch_atomic_xchb_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_xchgb_al_Pcx) /* lock xchgb %al, (%Pcx) -- atomic_xch((uint8_t *)%Pcx, %al) */
/* Try  to atomic_xch  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL
__NOTHROW(__arch_atomic_xchb_nopf)(__NCX void const *__addr,
                                   __uint8_t __newval, __uint8_t *__poldval) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xchgb_al_Pcx, 4)
	                     : "=a" (*__poldval)
	                     , "=@ccc" (__error)
	                     : "a" (__newval)
	                     , "c" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xchgb_al_Pcx)
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_xchb_nopf */

#ifdef __arch_atomic_xchw_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_xchgw_ax_Pcx) /* lock xchgw %ax, (%Pcx) -- atomic_xch((uint16_t *)%Pcx, %ax) */
/* Try  to atomic_xch  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL
__NOTHROW(__arch_atomic_xchw_nopf)(__NCX void const *__addr,
                                   __uint16_t __newval, __uint16_t *__poldval) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xchgw_ax_Pcx, 4)
	                     : "=a" (*__poldval)
	                     , "=@ccc" (__error)
	                     : "a" (__newval)
	                     , "c" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xchgw_ax_Pcx)
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_xchw_nopf */

#ifdef __arch_atomic_xchl_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_xchgl_eax_Pcx) /* lock xchgl %eax, (%Pcx) -- atomic_xch((uint32_t *)%Pcx, %eax) */
/* Try  to atomic_xch  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL
__NOTHROW(__arch_atomic_xchl_nopf)(__NCX void const *__addr,
                                   __uint32_t __newval, __uint32_t *__poldval) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xchgl_eax_Pcx, 4)
	                     : "=a" (*__poldval)
	                     , "=@ccc" (__error)
	                     : "a" (__newval)
	                     , "c" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xchgl_eax_Pcx)
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_xchl_nopf */

#ifdef __arch_atomic_xchq_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_xchgq_rax_Pcx) /* lock xchgq %rax, (%Pcx) -- atomic_xch((uint64_t *)%Pcx, %rax) */
/* Try  to atomic_xch  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL
__NOTHROW(__arch_atomic_xchq_nopf)(__NCX void const *__addr,
                                   __uint64_t __newval, __uint64_t *__poldval) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xchgq_rax_Pcx, 4)
	                     : "=a" (*__poldval)
	                     , "=@ccc" (__error)
	                     : "a" (__newval)
	                     , "c" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xchgq_rax_Pcx)
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_xchq_nopf */


#ifdef __arch_atomic_fetchaddb_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_xaddb_al_Pcx) /* lock xaddb %al, (%Pcx) -- atomic_fetchadd((uint8_t *)%Pcx, %al) */
/* Try to atomic_fetchadd  at a possibly  faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored __val
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL
__NOTHROW(__arch_atomic_fetchaddb_nopf)(__NCX void const *__addr,
                                        __uint8_t __addend, __uint8_t *__poldval) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xaddb_al_Pcx, 4)
	                     : "=a" (*__poldval)
	                     , "=@ccc" (__error)
	                     : "a" (__addend)
	                     , "c" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xaddb_al_Pcx)
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_fetchaddb_nopf */

#ifdef __arch_atomic_fetchaddw_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_xaddw_ax_Pcx) /* lock xaddw %ax, (%Pcx) -- atomic_fetchadd((uint16_t *)%Pcx, %ax) */
/* Try to atomic_fetchadd  at a possibly  faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored __val
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL
__NOTHROW(__arch_atomic_fetchaddw_nopf)(__NCX void const *__addr,
                                        __uint16_t __addend, __uint16_t *__poldval) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xaddw_ax_Pcx, 4)
	                     : "=a" (*__poldval)
	                     , "=@ccc" (__error)
	                     : "a" (__addend)
	                     , "c" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xaddw_ax_Pcx)
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_fetchaddw_nopf */

#ifdef __arch_atomic_fetchaddl_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_xaddl_eax_Pcx) /* lock xaddl %eax, (%Pcx) -- atomic_fetchadd((uint32_t *)%Pcx, %eax) */
/* Try to atomic_fetchadd  at a possibly  faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored __val
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL
__NOTHROW(__arch_atomic_fetchaddl_nopf)(__NCX void const *__addr,
                                        __uint32_t __addend, __uint32_t *__poldval) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xaddl_eax_Pcx, 4)
	                     : "=a" (*__poldval)
	                     , "=@ccc" (__error)
	                     : "a" (__addend)
	                     , "c" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xaddl_eax_Pcx)
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_fetchaddl_nopf */

#ifdef __arch_atomic_fetchaddq_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_xaddq_rax_Pcx) /* lock xaddq %rax, (%Pcx) -- atomic_fetchadd((uint64_t *)%Pcx, %rax) */
/* Try to atomic_fetchadd  at a possibly  faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored __val
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL
__NOTHROW(__arch_atomic_fetchaddq_nopf)(__NCX void const *__addr,
                                        __uint64_t __addend, __uint64_t *__poldval) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xaddq_rax_Pcx, 4)
	                     : "=a" (*__poldval)
	                     , "=@ccc" (__error)
	                     : "a" (__addend)
	                     , "c" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xaddq_rax_Pcx)
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_fetchaddq_nopf */

#ifdef __arch_atomic_orb_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_orb_al_Pcx) /* lock orb %al, (%Pcx) -- atomic_or((uint8_t *)%Pcx, %al) */
/* Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_atomic_orb_nopf)(__NCX void *__addr, __uint8_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_orb_al_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_orb_al_Pcx)
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_orb_nopf */

#ifdef __arch_atomic_orw_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_orw_ax_Pcx) /* lock orw %ax, (%Pcx) -- atomic_or((uint16_t *)%Pcx, %ax) */
/* Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_atomic_orw_nopf)(__NCX void *__addr, __uint16_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_orw_ax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_orw_ax_Pcx)
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_orw_nopf */

#ifdef __arch_atomic_orl_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_orl_eax_Pcx) /* lock orl %eax, (%Pcx) -- atomic_or((uint32_t *)%Pcx, %eax) */
/* Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_atomic_orl_nopf)(__NCX void *__addr, __uint32_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_orl_eax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_orl_eax_Pcx)
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_orl_nopf */

#ifdef __arch_atomic_orq_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_orq_rax_Pcx) /* lock orq %rax, (%Pcx) -- atomic_or((uint64_t *)%Pcx, %rax) */
/* Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_atomic_orq_nopf)(__NCX void *__addr, __uint64_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_orq_rax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_orq_rax_Pcx)
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_orq_nopf */

#ifdef __arch_atomic_andb_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_andb_al_Pcx) /* lock andb %al, (%Pcx) -- atomic_and((uint8_t *)%Pcx, %al) */
/* Try to atomically __mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_atomic_andb_nopf)(__NCX void *__addr, __uint8_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_andb_al_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_andb_al_Pcx)
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_andb_nopf */

#ifdef __arch_atomic_andw_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_andw_ax_Pcx) /* lock andw %ax, (%Pcx) -- atomic_and((uint16_t *)%Pcx, %ax) */
/* Try to atomically __mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_atomic_andw_nopf)(__NCX void *__addr, __uint16_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_andw_ax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_andw_ax_Pcx)
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_andw_nopf */

#ifdef __arch_atomic_andl_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_andl_eax_Pcx) /* lock andl %eax, (%Pcx) -- atomic_and((uint32_t *)%Pcx, %eax) */
/* Try to atomically __mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_atomic_andl_nopf)(__NCX void *__addr, __uint32_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_andl_eax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_andl_eax_Pcx)
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_andl_nopf */

#ifdef __arch_atomic_andq_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_andq_rax_Pcx) /* lock andq %rax, (%Pcx) -- atomic_and((uint64_t *)%Pcx, %rax) */
/* Try to atomically __mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_atomic_andq_nopf)(__NCX void *__addr, __uint64_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_andq_rax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_andq_rax_Pcx)
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_andq_nopf */

#ifdef __arch_atomic_xorb_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_xorb_al_Pcx) /* lock xorb %al, (%Pcx) -- atomic_xor((uint8_t *)%Pcx, %al) */
/* Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_atomic_xorb_nopf)(__NCX void *__addr, __uint8_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xorb_al_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xorb_al_Pcx)
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_xorb_nopf */

#ifdef __arch_atomic_xorw_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_xorw_ax_Pcx) /* lock xorw %ax, (%Pcx) -- atomic_xor((uint16_t *)%Pcx, %ax) */
/* Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_atomic_xorw_nopf)(__NCX void *__addr, __uint16_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xorw_ax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xorw_ax_Pcx)
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_xorw_nopf */

#ifdef __arch_atomic_xorl_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_xorl_eax_Pcx) /* lock xorl %eax, (%Pcx) -- atomic_xor((uint32_t *)%Pcx, %eax) */
/* Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_atomic_xorl_nopf)(__NCX void *__addr, __uint32_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xorl_eax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xorl_eax_Pcx)
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_xorl_nopf */

#ifdef __arch_atomic_xorq_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_xorq_rax_Pcx) /* lock xorq %rax, (%Pcx) -- atomic_xor((uint64_t *)%Pcx, %rax) */
/* Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_atomic_xorq_nopf)(__NCX void *__addr, __uint64_t __mask) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_lock_xorq_rax_Pcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__mask)
	                     __X86_NOPF_CALLARG(x86_nopf_lock_xorq_rax_Pcx)
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_xorq_nopf */

#ifdef __arch_atomic_cmpxchb_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_cmpxchgb_dl_Pcx) /* lock cmpxchgb %dl, (%Pcx) -- atomic_cmpxch((uint8_t *)%Pcx, %al, %dl) */
/* Try to do an atomic-compare-exchange at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((4)) __BOOL
__NOTHROW(__arch_atomic_cmpxchb_nopf)(__NCX void *__addr,
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
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_cmpxchb_nopf */

#ifdef __arch_atomic_cmpxchw_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_cmpxchgw_dx_Pcx) /* lock cmpxchgw %dx, (%Pcx) -- atomic_cmpxch((uint16_t *)%Pcx, %ax, %dx) */
/* Try to do an atomic-compare-exchange at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((4)) __BOOL
__NOTHROW(__arch_atomic_cmpxchw_nopf)(__NCX void *__addr,
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
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_cmpxchw_nopf */

#ifdef __arch_atomic_cmpxchl_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_cmpxchgl_edx_Pcx) /* lock cmpxchgl %edx, (%Pcx) -- atomic_cmpxch((uint32_t *)%Pcx, %eax, %edx) */
/* Try to do an atomic-compare-exchange at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((4)) __BOOL
__NOTHROW(__arch_atomic_cmpxchl_nopf)(__NCX void *__addr,
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
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_cmpxchl_nopf */

#ifdef __arch_atomic_cmpxchq_nopf
__X86_NOPF_DEFFUN(x86_nopf_lock_cmpxchgq_rdx_Pcx) /* lock cmpxchgq %rdx, (%Pcx) -- atomic_cmpxch((uint64_t *)%Pcx, %rax, %rdx) */
/* Try to do an atomic-compare-exchange at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((4)) __BOOL
__NOTHROW(__arch_atomic_cmpxchq_nopf)(__NCX void *__addr,
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
	                     __X86_NOPF_CALLCLB_ "memory", "cc");
	return !__error;
}
#endif /* __arch_atomic_cmpxchq_nopf */


/* X86-specific nopf read/write with fs/gs segment */
#ifdef __x86_readfsb_nopf
__X86_NOPF_DEFFUN(x86_nopf_movb_fsPax_al) /* movb %fs:(%Pax), %al  (read byte) */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __BOOL
__NOTHROW(__x86_readfsb_nopf)(__NCX void const *__addr, __uint8_t *__presult) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movb_fsPax_al, 3)
	                     : "=a" (*__presult)
	                     , "=@ccc" (__error)
	                     : "a" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_movb_fsPax_al)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __x86_readfsb_nopf */

#ifdef __x86_readfsw_nopf
__X86_NOPF_DEFFUN(x86_nopf_movw_fsPax_ax) /* movw %fs:(%Pax), %ax  (read word) */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __BOOL
__NOTHROW(__x86_readfsw_nopf)(__NCX void const *__addr, __uint16_t *__presult) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movw_fsPax_ax, 3)
	                     : "=a" (*__presult)
	                     , "=@ccc" (__error)
	                     : "a" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_movw_fsPax_ax)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __x86_readfsw_nopf */

#ifdef __x86_readfsl_nopf
__X86_NOPF_DEFFUN(x86_nopf_movl_fsPax_eax) /* movl %fs:(%Pax), %eax  (read dword) */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __BOOL
__NOTHROW(__x86_readfsl_nopf)(__NCX void const *__addr, __uint32_t *__presult) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movl_fsPax_eax, 3)
	                     : "=a" (*__presult)
	                     , "=@ccc" (__error)
	                     : "a" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_movl_fsPax_eax)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __x86_readfsl_nopf */

#ifdef __x86_readfsq_nopf
__X86_NOPF_DEFFUN(x86_nopf_movq_fsPax_rax) /* movq %fs:(%Pax), %rax  (read qword) */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __BOOL
__NOTHROW(__x86_readfsq_nopf)(__NCX void const *__addr, __uint64_t *__presult) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movq_fsPax_rax, 3)
	                     : "=a" (*__presult)
	                     , "=@ccc" (__error)
	                     : "a" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_movq_fsPax_rax)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __x86_readfsq_nopf */

#ifdef __x86_writefsb_nopf
__X86_NOPF_DEFFUN(x86_nopf_movb_al_fsPcx)  /* movb %al, %fs:(%Pcx)  (write byte) */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__x86_writefsb_nopf)(__NCX void *__addr, __uint8_t __val) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movb_al_fsPcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__val)
	                     __X86_NOPF_CALLARG(x86_nopf_movb_al_fsPcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __x86_writefsb_nopf */

#ifdef __x86_writefsw_nopf
__X86_NOPF_DEFFUN(x86_nopf_movw_ax_fsPcx)  /* movw %ax, %fs:(%Pcx)  (write word) */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__x86_writefsw_nopf)(__NCX void *__addr, __uint16_t __val) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movw_ax_fsPcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__val)
	                     __X86_NOPF_CALLARG(x86_nopf_movw_ax_fsPcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __x86_writefsw_nopf */

#ifdef __x86_writefsl_nopf
__X86_NOPF_DEFFUN(x86_nopf_movl_eax_fsPcx) /* movl %eax, %fs:(%Pcx)  (write dword) */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__x86_writefsl_nopf)(__NCX void *__addr, __uint32_t __val) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movl_eax_fsPcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__val)
	                     __X86_NOPF_CALLARG(x86_nopf_movl_eax_fsPcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __x86_writefsl_nopf */

#ifdef __x86_writefsq_nopf
__X86_NOPF_DEFFUN(x86_nopf_movq_rax_fsPcx) /* movq %rax, %fs:(%Pcx)  (write qword) */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__x86_writefsq_nopf)(__NCX void *__addr, __uint64_t __val) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movq_rax_fsPcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__val)
	                     __X86_NOPF_CALLARG(x86_nopf_movq_rax_fsPcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __x86_writefsq_nopf */

#ifdef __x86_readgsb_nopf
__X86_NOPF_DEFFUN(x86_nopf_movb_gsPax_al) /* movb %gs:(%Pax), %al  (read byte) */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __BOOL
__NOTHROW(__x86_readgsb_nopf)(__NCX void const *__addr, __uint8_t *__presult) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movb_gsPax_al, 3)
	                     : "=a" (*__presult)
	                     , "=@ccc" (__error)
	                     : "a" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_movb_gsPax_al)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __x86_readgsb_nopf */

#ifdef __x86_readgsw_nopf
__X86_NOPF_DEFFUN(x86_nopf_movw_gsPax_ax) /* movw %gs:(%Pax), %ax  (read word) */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __BOOL
__NOTHROW(__x86_readgsw_nopf)(__NCX void const *__addr, __uint16_t *__presult) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movw_gsPax_ax, 3)
	                     : "=a" (*__presult)
	                     , "=@ccc" (__error)
	                     : "a" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_movw_gsPax_ax)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __x86_readgsw_nopf */

#ifdef __x86_readgsl_nopf
__X86_NOPF_DEFFUN(x86_nopf_movl_gsPax_eax) /* movl %gs:(%Pax), %eax  (read dword) */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __BOOL
__NOTHROW(__x86_readgsl_nopf)(__NCX void const *__addr, __uint32_t *__presult) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movl_gsPax_eax, 3)
	                     : "=a" (*__presult)
	                     , "=@ccc" (__error)
	                     : "a" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_movl_gsPax_eax)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __x86_readgsl_nopf */

#ifdef __x86_readgsq_nopf
__X86_NOPF_DEFFUN(x86_nopf_movq_gsPax_rax) /* movq %gs:(%Pax), %rax  (read qword) */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __BOOL
__NOTHROW(__x86_readgsq_nopf)(__NCX void const *__addr, __uint64_t *__presult) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movq_gsPax_rax, 3)
	                     : "=a" (*__presult)
	                     , "=@ccc" (__error)
	                     : "a" (__addr)
	                     __X86_NOPF_CALLARG(x86_nopf_movq_gsPax_rax)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __x86_readgsq_nopf */

#ifdef __x86_writegsb_nopf
__X86_NOPF_DEFFUN(x86_nopf_movb_al_gsPcx)  /* movb %al, %gs:(%Pcx)  (write byte) */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__x86_writegsb_nopf)(__NCX void *__addr, __uint8_t __val) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movb_al_gsPcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__val)
	                     __X86_NOPF_CALLARG(x86_nopf_movb_al_gsPcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __x86_writegsb_nopf */

#ifdef __x86_writegsw_nopf
__X86_NOPF_DEFFUN(x86_nopf_movw_ax_gsPcx)  /* movw %ax, %gs:(%Pcx)  (write word) */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__x86_writegsw_nopf)(__NCX void *__addr, __uint16_t __val) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movw_ax_gsPcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__val)
	                     __X86_NOPF_CALLARG(x86_nopf_movw_ax_gsPcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __x86_writegsw_nopf */

#ifdef __x86_writegsl_nopf
__X86_NOPF_DEFFUN(x86_nopf_movl_eax_gsPcx) /* movl %eax, %gs:(%Pcx)  (write dword) */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__x86_writegsl_nopf)(__NCX void *__addr, __uint32_t __val) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movl_eax_gsPcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__val)
	                     __X86_NOPF_CALLARG(x86_nopf_movl_eax_gsPcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __x86_writegsl_nopf */

#ifdef __x86_writegsq_nopf
__X86_NOPF_DEFFUN(x86_nopf_movq_rax_gsPcx) /* movq %rax, %gs:(%Pcx)  (write qword) */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __BOOL
__NOTHROW(__x86_writegsq_nopf)(__NCX void *__addr, __uint64_t __val) {
	__BOOL __error;
	__asm__ __volatile__(__X86_NOPF_CALLASM(x86_nopf_movq_rax_gsPcx, 3)
	                     : "=@ccc" (__error)
	                     : "c" (__addr)
	                     , "a" (__val)
	                     __X86_NOPF_CALLARG(x86_nopf_movq_rax_gsPcx)
	                     __X86_NOPF_CALLCLB_ "cc");
	return !__error;
}
#endif /* __x86_writegsq_nopf */

#undef __X86_NOPF_CALLASM
#undef __X86_NOPF_CALLARG
#undef __X86_NOPF_CALLCLB
#undef __X86_NOPF_CALLCLB_

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_BITS_NOPF_H */
