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
#ifdef __INTELLISENSE__
#ifndef __LIBEMU86_STATIC
#define LIBEMU86_WANT_PROTOTYPES 1
#define __LIBEMU86_STATIC 1
#define CONFIG_LIBEMU86_WANT_16BIT 1
#define CONFIG_LIBEMU86_WANT_32BIT 1
#ifdef __x86_64__
#define CONFIG_LIBEMU86_WANT_64BIT 1
#endif /* __x86_64__ */
#endif /* !__LIBEMU86_STATIC */
#endif /* __INTELLISENSE__ */

#include <hybrid/__atomic.h>
#include <hybrid/__rotate.h>
#include <hybrid/host.h>
#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <i386-kos/asm/cpu-flags.h>
#include <i386-kos/asm/registers-compat.h>
#include <i386-kos/asm/registers.h>
#include <kos/except.h>
#include <kos/except/inval.h>
#include <kos/kernel/types.h>
#include <kos/types.h>

#include <stdbool.h>
#include <stdint.h>

#include "eflags.h"
#include "emu86.h"
#include "helpers.h"

#if defined(__x86_64__) || defined(__i386__)
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#ifdef __KERNEL__
#include <sched/cred.h>
#endif /* __KERNEL__ */
#endif /* __x86_64__ || __i386__ */

#if CONFIG_LIBEMU86_WANT_64BIT
#include <int128.h>
#endif /* CONFIG_LIBEMU86_WANT_64BIT */

__DECL_BEGIN

/* Declaration visibility of `emu86_emulate()' */
#ifndef EMU86_EMULATE_DECL
#define EMU86_EMULATE_DECL __PRIVATE
#endif /* !EMU86_EMULATE_DECL */

/* Attributes applied to `emu86_emulate()' */
#ifndef EMU86_EMULATE_ATTR
#define EMU86_EMULATE_ATTR __ATTR_NONNULL((1))
#endif /* !EMU86_EMULATE_ATTR */

/* How and what `emu86_emulate()' should return */
#ifndef EMU86_EMULATE_RETURN
#define EMU86_EMULATE_RETURN      return _state
#define EMU86_EMULATE_RETURN_TYPE struct icpustate *
#endif /* !EMU86_EMULATE_RETURN */

/* Return in the event of an unrecognized instruction.
 * @param: faultaddr: The starting address of the faulting instruction
 * @param: opcode:    The unknown instruction's opcode
 * @param: op_flags:  Instruction flags (set of `EMU86_F_*') */
#ifndef EMU86_EMULATE_RETURN_UNKNOWN_INSTRUCTION
#define EMU86_EMULATE_RETURN_UNKNOWN_INSTRUCTION(faultaddr, opcode, op_flags) \
	EMU86_EMULATE_RETURN
#endif /* !EMU86_EMULATE_RETURN_UNKNOWN_INSTRUCTION */

/* The NOTHROW annotation of `emu86_emulate()' */
#ifndef EMU86_EMULATE_NOTHROW
#define EMU86_EMULATE_NOTHROW /* nothing */
#endif /* !EMU86_EMULATE_NOTHROW */

/* The calling convention of `emu86_emulate()' */
#ifndef EMU86_EMULATE_CC
#define EMU86_EMULATE_CC LIBEMU86_CC
#endif /* !EMU86_EMULATE_CC */

/* An override for the name of `emu86_emulate()' */
#ifndef EMU86_EMULATE_NAME
#define EMU86_EMULATE_NAME emu86_emulate
#endif /* !EMU86_EMULATE_NAME */

/* Declaration visibility of helper functions */
#ifndef EMU86_EMULATE_HELPER_DECL
#define EMU86_EMULATE_HELPER_DECL __PRIVATE
#endif /* !EMU86_EMULATE_HELPER_DECL */

/* Transform the name of helper functions */
#ifndef EMU86_EMULATE_HELPER_NAME
#define EMU86_EMULATE_HELPER_NAME(x) x
#endif /* !EMU86_EMULATE_HELPER_NAME */

/* A list of arguments taken by `emu86_emulate()' */
#ifndef EMU86_EMULATE_ARGS
#define EMU86_EMULATE_ARGS          struct icpustate *__restrict _state
#endif /* !EMU86_EMULATE_ARGS */

/* Hint at a spin-loop that may not necessarily break on its own.
 * This is placed in `do { READ(); } while (!ATOMIC_CMPXCH());'
 * loops after the every time that the `ATOMIC_CMPXCH()' fails.
 * For kernel-space, this should contain a call to `task_serve()'
 * in order to allow the calling thread to be terminated in the
 * event that the backing memory is set-up to return random values
 * for every invocation. */
#ifndef EMU86_EMULATE_LOOPHINT
#ifdef __KERNEL__
#include <sched/rpc.h>
#include <sched/task.h>
#define EMU86_EMULATE_LOOPHINT() (task_serve(), task_yield())
#else /* __KERNEL__ */
#include <hybrid/sched/__yield.h>
#define EMU86_EMULATE_LOOPHINT() __hybrid_yield()
#endif /* !__KERNEL__ */
#endif /* !EMU86_EMULATE_LOOPHINT */

/* Arguments taken by helper functions */
#ifndef EMU86_EMULATE_HELPER_ARGS
#define EMU86_EMULATE_HELPER_ATTR   __ATTR_NONNULL((1))
#define EMU86_EMULATE_HELPER_ARGS   struct icpustate *__restrict _state   /* Arguments for helper functions */
#define EMU86_EMULATE_HELPER_PARAM  _state /* Parameters passed to helper functions */
#endif /* !EMU86_EMULATE_HELPER_ARGS */
#ifndef EMU86_EMULATE_HELPER_ARGS_
#define EMU86_EMULATE_HELPER_ARGS_  EMU86_EMULATE_HELPER_ARGS,
#define EMU86_EMULATE_HELPER_PARAM_ EMU86_EMULATE_HELPER_PARAM,
#endif /* !EMU86_EMULATE_HELPER_ARGS_ */

/* Additional attributes for annotating helper functions */
#ifndef EMU86_EMULATE_HELPER_ATTR
#define EMU86_EMULATE_HELPER_ATTR /* nothing */
#endif /* !EMU86_EMULATE_HELPER_ATTR */

/* Declare additional variables used during emulation */
#ifndef EMU86_EMULATE_VARIABLES
#define EMU86_EMULATE_VARIABLES /* nothing */
#endif /* !EMU86_EMULATE_VARIABLES */

/* Additional code to be executed before starting emulation */
#ifndef EMU86_EMULATE_SETUP
#define EMU86_EMULATE_SETUP do { } __WHILE0
#endif /* !EMU86_EMULATE_SETUP */

/* May be used to add a TRY ... EXCEPT block around emulation */
/* #define EMU86_EMULATE_TRY           TRY */
/* #define EMU86_EMULATE_EXCEPT        EXCEPT { ... } */
/* #define EMU86_EMULATE_TRY_DECODE    TRY */
/* #define EMU86_EMULATE_TRY_SWITCH    EXCEPT { ... } */
/* #define EMU86_EMULATE_EXCEPT_DECODE TRY */
/* #define EMU86_EMULATE_EXCEPT_SWITCH EXCEPT { ... } */

/* Define to implement support for the `bound' instruction on 16-/32-bit */
#ifndef EMU86_EMULATE_THROW_BOUNDERR
#define EMU86_EMULATE_THROW_BOUNDERR(bound_idx, bound_min, bound_max) \
	THROW(E_INDEX_ERROR_OUT_OF_BOUNDS, bound_idx, bound_min, bound_max)
#endif /* !EMU86_EMULATE_THROW_BOUNDERR */

/* Allow E_DIVIDE_BY_ZERO to be rethrown natively, rather than having
 * to be handled by use of `EMU86_EMULATE_THROW_DIVIDE_ERROR[B|W|L|Q]()'
 * In case the aforementioned macros only ever throw the same exception,
 * this can get rid of unnecessary bloat. */
#ifndef EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW
#define EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW 0
#endif /* !EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW */

/* Throw an exception indicative of a privileged instruction
 * Only used when `EMU86_EMULATE_CHECKUSER' is enabled. */
#ifndef EMU86_EMULATE_THROW_PRIVILEGED_INSTRUCTION
#define EMU86_EMULATE_THROW_PRIVILEGED_INSTRUCTION(opcode) \
	THROW(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE, opcode)
#endif /* !EMU86_EMULATE_THROW_PRIVILEGED_INSTRUCTION */

/* An optional, special return expression to be evaluated following
 * an `sti' instruction that turned on EFLAGS.IF (may be used to
 * implement special handling in order to delay interrupt checks
 * until after the next instruction)
 * NOTE: This expression mustn't return normally! (but should
 *       normally contain a `THROW()' or `return' statement) */
/* #define EMU86_EMULATE_RETURN_AFTER_STI ... */

/* Same as `EMU86_EMULATE_RETURN_AFTER_STI', but used for vm86 instead. */
/* #define EMU86_EMULATE_RETURN_AFTER_STI_VM86 ... */

/* An optional, special return expression to be evaluated following
 * an `hlt' instruction (with #IF=0 or #IF=1 respectively)
 * When not defined, `hlt' will simply return normally.
 * See also: `EMU86_EMULATE_RETURN_AFTER_HLT_VM86' when vm86 is supported. */
/* #define EMU86_EMULATE_RETURN_AFTER_HLT_IF0 ... */
/* #define EMU86_EMULATE_RETURN_AFTER_HLT_IF1 ... */


#ifndef EMU86_EMULATE_THROW_DIVIDE_BY_ZEROB
#ifndef EMU86_EMULATE_THROW_DIVIDE_ERROR
#define EMU86_EMULATE_THROW_DIVIDE_ERROR() THROW(E_DIVIDE_BY_ZERO)
#endif /* !EMU86_EMULATE_THROW_DIVIDE_ERROR */
#ifndef EMU86_EMULATE_THROW_SIGNED_DIVIDE_BY_ZERO
#define EMU86_EMULATE_THROW_SIGNED_DIVIDE_BY_ZERO() EMU86_EMULATE_THROW_DIVIDE_ERROR()
#endif /* !EMU86_EMULATE_THROW_SIGNED_DIVIDE_BY_ZERO */
#define EMU86_EMULATE_THROW_DIVIDE_BY_ZEROB(/*u16*/ lhs) EMU86_EMULATE_THROW_DIVIDE_ERROR()
#define EMU86_EMULATE_THROW_DIVIDE_BY_ZEROW(/*u32*/ lhs) EMU86_EMULATE_THROW_DIVIDE_ERROR()
#define EMU86_EMULATE_THROW_DIVIDE_BY_ZEROL(/*u64*/ lhs) EMU86_EMULATE_THROW_DIVIDE_ERROR()
#define EMU86_EMULATE_THROW_SIGNED_DIVIDE_BY_ZEROB(/*s16*/ lhs) EMU86_EMULATE_THROW_SIGNED_DIVIDE_BY_ZERO()
#define EMU86_EMULATE_THROW_SIGNED_DIVIDE_BY_ZEROW(/*s32*/ lhs) EMU86_EMULATE_THROW_SIGNED_DIVIDE_BY_ZERO()
#define EMU86_EMULATE_THROW_SIGNED_DIVIDE_BY_ZEROL(/*s64*/ lhs) EMU86_EMULATE_THROW_SIGNED_DIVIDE_BY_ZERO()
#if CONFIG_LIBEMU86_WANT_64BIT && defined(__UINT128_TYPE__)
#define EMU86_EMULATE_THROW_DIVIDE_BY_ZEROQ(/*uint128_t*/ lhs) EMU86_EMULATE_THROW_DIVIDE_ERROR()
#define EMU86_EMULATE_THROW_SIGNED_DIVIDE_BY_ZEROQ(/*int128_t*/ lhs) EMU86_EMULATE_THROW_SIGNED_DIVIDE_BY_ZERO()
#endif /* CONFIG_LIBEMU86_WANT_64BIT && __UINT128_TYPE__ */
#endif /* !EMU86_EMULATE_THROW_DIVIDE_ERROR */
#ifndef EMU86_EMULATE_THROW_DIVIDE_OVERFLOWB
#define EMU86_EMULATE_THROW_DIVIDE_OVERFLOWB(/*u16*/ lhs, /*u8*/ rhs, /*u16*/ exact_result) EMU86_EMULATE_THROW_DIVIDE_BY_ZEROB(lhs)
#define EMU86_EMULATE_THROW_DIVIDE_OVERFLOWW(/*u32*/ lhs, /*u16*/ rhs, /*u32*/ exact_result) EMU86_EMULATE_THROW_DIVIDE_BY_ZEROW(lhs)
#define EMU86_EMULATE_THROW_DIVIDE_OVERFLOWL(/*u64*/ lhs, /*u32*/ rhs, /*u64*/ exact_result) EMU86_EMULATE_THROW_DIVIDE_BY_ZEROL(lhs)
#define EMU86_EMULATE_THROW_SIGNED_DIVIDE_OVERFLOWB(/*s16*/ lhs, /*s8*/ rhs, /*s16*/ exact_result) EMU86_EMULATE_THROW_SIGNED_DIVIDE_BY_ZEROB(lhs)
#define EMU86_EMULATE_THROW_SIGNED_DIVIDE_OVERFLOWW(/*s32*/ lhs, /*s16*/ rhs, /*s32*/ exact_result) EMU86_EMULATE_THROW_SIGNED_DIVIDE_BY_ZEROW(lhs)
#define EMU86_EMULATE_THROW_SIGNED_DIVIDE_OVERFLOWL(/*s64*/ lhs, /*s32*/ rhs, /*s64*/ exact_result) EMU86_EMULATE_THROW_SIGNED_DIVIDE_BY_ZEROL(lhs)
#if CONFIG_LIBEMU86_WANT_64BIT && defined(__UINT128_TYPE__)
#define EMU86_EMULATE_THROW_DIVIDE_OVERFLOWQ(/*uint128_t*/ lhs, /*u64*/ rhs, /*uint128_t*/ exact_result) EMU86_EMULATE_THROW_DIVIDE_BY_ZEROQ(lhs)
#define EMU86_EMULATE_THROW_SIGNED_DIVIDE_OVERFLOWQ(/*int128_t*/ lhs, /*s64*/ rhs, /*int128_t*/ exact_result) EMU86_EMULATE_THROW_SIGNED_DIVIDE_BY_ZEROQ(lhs)
#endif /* CONFIG_LIBEMU86_WANT_64BIT && __UINT128_TYPE__ */
#endif /* !EMU86_EMULATE_THROW_DIVIDE_OVERFLOWB */

/* Return the initial set of opcode flags. */
#ifndef EMU86_EMULATE_GETOPFLAGS
#ifdef CONFIG_LIBEMU86_NEED_ARCHMODE
#define EMU86_EMULATE_GETOPFLAGS() emu86_opflagsof_icpustate(_state)
#else /* CONFIG_LIBEMU86_NEED_ARCHMODE */
#define EMU86_EMULATE_GETOPFLAGS() EMU86_F_NORMAL
#endif /* !CONFIG_LIBEMU86_NEED_ARCHMODE */
#endif /* !EMU86_EMULATE_GETOPFLAGS */

/* Define to only emulate instructions that access memory. (used to implement VIO) */
/* #define EMU86_EMULATE_ONLY_MEMORY 1 */

/* Translate a memory address to its real counterpart.
 * This macro is invoked prior to any kind of memory access made
 * by hosted code, and can be used to implement software paging,
 * or some kind of addend added to any kind of memory access. */
#ifndef EMU86_EMULATE_TRANSLATEADDR
#define EMU86_EMULATE_TRANSLATEADDR_IS_NOOP 1
#ifdef __INTELLISENSE__
#define EMU86_EMULATE_TRANSLATEADDR(addr) (void *)(addr)
#else /* __INTELLISENSE__ */
#define EMU86_EMULATE_TRANSLATEADDR(addr) (addr)
#endif /* !__INTELLISENSE__ */
#endif /* !EMU86_EMULATE_TRANSLATEADDR */


/* Enable emulation of VM86 helpers */
#ifndef EMU86_EMULATE_VM86
#define EMU86_EMULATE_VM86 (!CONFIG_LIBEMU86_WANT_64BIT && CONFIG_LIBEMU86_WANT_16BIT)
#endif /* !EMU86_EMULATE_VM86 */

#if EMU86_EMULATE_VM86 && CONFIG_LIBEMU86_WANT_64BIT
#error "Cannot emulate vm86 together with 64-bit support!"
#endif /* EMU86_EMULATE_VM86 && CONFIG_LIBEMU86_WANT_64BIT */

/* These functions are used only when emulating an instruction for vm86
 * They are _not_ used by libvm86 (which is a full realmode emulator that
 * doesn't actually make use of vm86, so-as to also work on x86_64!)
 * These functions are used by  */
#if EMU86_EMULATE_VM86
#ifndef EMU86_EMULATE_VM86_GETIF
#define EMU86_EMULATE_VM86_GETIF() 0
#endif /* !EMU86_EMULATE_VM86_GETIF */
#ifndef EMU86_EMULATE_VM86_SETIF
#define EMU86_EMULATE_VM86_SETIF(v) (void)0
#endif /* !EMU86_EMULATE_VM86_SETIF */
#ifndef EMU86_EMULATE_RETURN_AFTER_HLT_VM86
#define EMU86_EMULATE_RETURN_AFTER_HLT_VM86 goto done
#endif /* !EMU86_EMULATE_RETURN_AFTER_HLT_VM86 */
#endif /* EMU86_EMULATE_VM86 */



/* Read/write memory
 * NOTE: These functions aren't used when it comes to reading from PC-relative memory. */
#ifndef EMU86_EMULATE_READB
#define EMU86_EMULATE_READB(addr)     (*(u8 const *)EMU86_EMULATE_TRANSLATEADDR(addr))
#define EMU86_EMULATE_READW(addr)     UNALIGNED_GET16((u16 *)EMU86_EMULATE_TRANSLATEADDR(addr))
#define EMU86_EMULATE_READL(addr)     UNALIGNED_GET32((u32 *)EMU86_EMULATE_TRANSLATEADDR(addr))
#define EMU86_EMULATE_WRITEB(addr, v) (*(u8 *)EMU86_EMULATE_TRANSLATEADDR(addr) = (v))
#define EMU86_EMULATE_WRITEW(addr, v) UNALIGNED_SET16((u16 *)EMU86_EMULATE_TRANSLATEADDR(addr), v)
#define EMU86_EMULATE_WRITEL(addr, v) UNALIGNED_SET32((u32 *)EMU86_EMULATE_TRANSLATEADDR(addr), v)
#define EMU86_EMULATE_ATOMIC_XCHB(addr, addend, force_atomic) __hybrid_atomic_xch(*(u8 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_XCHW(addr, addend, force_atomic) __hybrid_atomic_xch(*(u16 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_XCHL(addr, addend, force_atomic) __hybrid_atomic_xch(*(u32 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_FETCHADDB(addr, addend, force_atomic) __hybrid_atomic_fetchadd(*(u8 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_FETCHADDW(addr, addend, force_atomic) __hybrid_atomic_fetchadd(*(u16 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_FETCHADDL(addr, addend, force_atomic) __hybrid_atomic_fetchadd(*(u32 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_FETCHSUBB(addr, addend, force_atomic) __hybrid_atomic_fetchsub(*(u8 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_FETCHSUBW(addr, addend, force_atomic) __hybrid_atomic_fetchsub(*(u16 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_FETCHSUBL(addr, addend, force_atomic) __hybrid_atomic_fetchsub(*(u32 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_FETCHANDB(addr, addend, force_atomic) __hybrid_atomic_fetchand(*(u8 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_FETCHANDW(addr, addend, force_atomic) __hybrid_atomic_fetchand(*(u16 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_FETCHANDL(addr, addend, force_atomic) __hybrid_atomic_fetchand(*(u32 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_FETCHORB(addr, addend, force_atomic) __hybrid_atomic_fetchor(*(u8 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_FETCHORW(addr, addend, force_atomic) __hybrid_atomic_fetchor(*(u16 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_FETCHORL(addr, addend, force_atomic) __hybrid_atomic_fetchor(*(u32 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_FETCHXORB(addr, addend, force_atomic) __hybrid_atomic_fetchxor(*(u8 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_FETCHXORW(addr, addend, force_atomic) __hybrid_atomic_fetchxor(*(u16 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_FETCHXORL(addr, addend, force_atomic) __hybrid_atomic_fetchxor(*(u32 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_CMPXCHB(addr, oldval, newval, force_atomic) __hybrid_atomic_cmpxch(*(u8 *)EMU86_EMULATE_TRANSLATEADDR(addr), oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_CMPXCHW(addr, oldval, newval, force_atomic) __hybrid_atomic_cmpxch(*(u16 *)EMU86_EMULATE_TRANSLATEADDR(addr), oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_CMPXCHL(addr, oldval, newval, force_atomic) __hybrid_atomic_cmpxch(*(u32 *)EMU86_EMULATE_TRANSLATEADDR(addr), oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_CMPXCHQ(addr, oldval, newval, force_atomic) __hybrid_atomic_cmpxch(*(u64 *)EMU86_EMULATE_TRANSLATEADDR(addr), oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_CMPXCH_OR_WRITEB(addr, oldval, newval, force_atomic) __hybrid_atomic_cmpxch(*(u8 *)EMU86_EMULATE_TRANSLATEADDR(addr), oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_CMPXCH_OR_WRITEW(addr, oldval, newval, force_atomic) __hybrid_atomic_cmpxch(*(u16 *)EMU86_EMULATE_TRANSLATEADDR(addr), oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_CMPXCH_OR_WRITEL(addr, oldval, newval, force_atomic) __hybrid_atomic_cmpxch(*(u32 *)EMU86_EMULATE_TRANSLATEADDR(addr), oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#if CONFIG_LIBEMU86_WANT_64BIT
#define EMU86_EMULATE_READQ(addr)     UNALIGNED_GET64((u64 const *)EMU86_EMULATE_TRANSLATEADDR(addr))
#define EMU86_EMULATE_WRITEQ(addr, v) UNALIGNED_SET64((u64 *)EMU86_EMULATE_TRANSLATEADDR(addr), v)
#define EMU86_EMULATE_ATOMIC_XCHQ(addr, addend, force_atomic) __hybrid_atomic_xch(*(u64 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_FETCHADDQ(addr, addend, force_atomic) __hybrid_atomic_fetchadd(*(u64 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_FETCHSUBQ(addr, addend, force_atomic) __hybrid_atomic_fetchsub(*(u64 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_FETCHANDQ(addr, addend, force_atomic) __hybrid_atomic_fetchand(*(u64 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_FETCHORQ(addr, addend, force_atomic) __hybrid_atomic_fetchor(*(u64 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_FETCHXORQ(addr, addend, force_atomic) __hybrid_atomic_fetchxor(*(u64 *)EMU86_EMULATE_TRANSLATEADDR(addr), addend, __ATOMIC_SEQ_CST)
#define EMU86_EMULATE_ATOMIC_CMPXCH_OR_WRITEQ(addr, oldval, newval, force_atomic) __hybrid_atomic_cmpxch(*(u64 *)EMU86_EMULATE_TRANSLATEADDR(addr), oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
/*  #define EMU86_EMULATE_ATOMIC_CMPXCH128(addr, oldval, newval, force_atomic)  */
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
#endif /* !EMU86_EMULATE_READB */

#ifndef EMU86_EMULATE_READLASW
#if 1
#define EMU86_EMULATE_READLASW(addr) EMU86_EMULATE_READW(addr)
#else
#define EMU86_EMULATE_READLASW(addr) (u16)EMU86_EMULATE_READL(addr)
#endif
#endif /* !EMU86_EMULATE_READLASW */

#ifndef EMU86_EMULATE_WRITELASW
#if 1
#define EMU86_EMULATE_WRITELASW(addr, value) EMU86_EMULATE_WRITEW(addr, value)
#else
#define EMU86_EMULATE_WRITELASW(addr, value) EMU86_EMULATE_WRITEL(addr, value)
#endif
#endif /* !EMU86_EMULATE_WRITELASW */

#if CONFIG_LIBEMU86_WANT_64BIT
#ifndef EMU86_EMULATE_READQASW
#if 1
#define EMU86_EMULATE_READQASW(addr) EMU86_EMULATE_READW(addr)
#else
#define EMU86_EMULATE_READQASW(addr) (u16)EMU86_EMULATE_READQ(addr)
#endif
#endif /* !EMU86_EMULATE_READQASW */
#ifndef EMU86_EMULATE_READQASL
#if 1
#define EMU86_EMULATE_READQASL(addr) EMU86_EMULATE_READL(addr)
#else
#define EMU86_EMULATE_READQASL(addr) (u32)EMU86_EMULATE_READQ(addr)
#endif
#endif /* !EMU86_EMULATE_READQASL */
#ifndef EMU86_EMULATE_WRITEQASW
#if 1
#define EMU86_EMULATE_WRITEQASW(addr, value) EMU86_EMULATE_WRITEW(addr, value)
#else
#define EMU86_EMULATE_WRITEQASW(addr, value) EMU86_EMULATE_WRITEQ(addr, value)
#endif
#endif /* !EMU86_EMULATE_WRITEQASW */
#ifndef EMU86_EMULATE_WRITEQASL
#if 1
#define EMU86_EMULATE_WRITEQASL(addr, value) EMU86_EMULATE_WRITEL(addr, value)
#else
#define EMU86_EMULATE_WRITEQASL(addr, value) EMU86_EMULATE_WRITEQ(addr, value)
#endif
#endif /* !EMU86_EMULATE_WRITEQASL */
#endif /* CONFIG_LIBEMU86_WANT_64BIT */

/* Define to `0' to have `xchg' require a lock prefix in order to be considered atomic.
 * Real hardware always has xchg behave as atomic, regardless of the presence of an
 * optional lock-prefix, however this also makes it impossible to implement non-atomic
 * xchg in VIO. (though VIO is default configured to still match the hardware standard,
 * meaning that this is only a convenience option that isn't actually ever altered) */
#ifndef EMU86_EMULATE_ATOMIC_XCHG_REQUIRES_LOCK
#define EMU86_EMULATE_ATOMIC_XCHG_REQUIRES_LOCK 1
#endif /* !EMU86_EMULATE_ATOMIC_XCHG_REQUIRES_LOCK */

/* Define to non-zero if user access checks should be performed. */
#ifndef EMU86_EMULATE_CHECKUSER
#if defined(__KERNEL__) || defined(__INTELLISENSE__)
#define EMU86_EMULATE_CHECKUSER 1
#else /* __KERNEL__ */
#define EMU86_EMULATE_CHECKUSER 0
#endif /* !__KERNEL__ */
#endif /* !EMU86_EMULATE_CHECKUSER */

/* Return non-zero if user access checks should be performed for the caller. */
#ifndef EMU86_ISUSER
#define EMU86_ISUSER() icpustate_isuser(_state)
#endif /* !EMU86_ISUSER */
#ifndef EMU86_ISUSER_NOVM86
#if EMU86_EMULATE_VM86
#define EMU86_ISUSER_NOVM86() icpustate_isuser_novm86(_state)
#else /* EMU86_EMULATE_VM86 */
#define EMU86_ISUSER_NOVM86() EMU86_ISUSER()
#endif /* !EMU86_EMULATE_VM86 */
#endif /* !EMU86_ISUSER_NOVM86 */
#ifndef EMU86_ISVM86
#ifdef EMU86_EMULATE_VM86
#define EMU86_ISVM86() (EMU86_GETFLAGS() & EFLAGS_VM)
#else /* EMU86_EMULATE_VM86 */
#define EMU86_ISVM86() 0
#endif /* !EMU86_EMULATE_VM86 */
#endif /* !EMU86_ISVM86 */

/* Validate that `addr ... += num_bytes' is a user-space address range. */
#ifndef EMU86_VALIDATE_READABLE
#ifdef __KERNEL__
#include <kernel/user.h>
#define EMU86_VALIDATE_READABLE(addr, num_bytes) validate_readable((void const *)(uintptr_t)(addr), num_bytes)
#define EMU86_VALIDATE_WRITABLE(addr, num_bytes) validate_writable((void *)(uintptr_t)(addr), num_bytes)
#else /* __KERNEL__ */
#define EMU86_VALIDATE_READABLE(addr, num_bytes) (void)0
#define EMU86_VALIDATE_WRITABLE(addr, num_bytes) (void)0
#endif /* !__KERNEL__ */
#endif /* !EMU86_VALIDATE_READABLE */

/* Get/Set the value of the EFLAGS register. */
#ifndef EMU86_GETFLAGS
#define EMU86_GETFLAGS()            icpustate_getpflags(_state)
#define EMU86_SETFLAGS(v)           icpustate_setpflags(_state, v)
#define EMU86_MSKFLAGS(mask, value) icpustate_mskpflags(_state, mask, value)
#endif /* !EMU86_GETFLAGS */
#ifndef EMU86_MSKFLAGS
#define EMU86_MSKFLAGS(mask, value) \
	EMU86_SETFLAGS((EMU86_GETFLAGS() & (mask)) | (value))
#endif /* !EMU86_MSKFLAGS */

/* Get/set the program counter (IP/EIP/RIP) register (including CS.BASE)
 * Note that `EMU86_EMULATE_GETPC() == EMU86_SEGADDR(EMU86_GETCSBASE(), EMU86_EMULATE_GETIP())'  */
#ifndef EMU86_EMULATE_GETPC
#define EMU86_EMULATE_GETPC()  icpustate_getpc(_state)
#define EMU86_EMULATE_SETPC(v) icpustate_setpc(_state, (__uintptr_t)(v))
#endif /* !EMU86_EMULATE_GETPC */

/* Same as `EMU86_EMULATE_SETPC()', but don't account for
 * segment offsets, but simply set the raw %(e|r)ip register. */
#ifndef EMU86_EMULATE_GETIP
#define EMU86_EMULATE_GETIP()  EMU86_EMULATE_GETPC()
#define EMU86_EMULATE_SETIP(v) EMU86_EMULATE_SETPC(v)
#endif /* !EMU86_EMULATE_GETIP */

/* Get/set the %(|e|r)ip register */
#ifndef EMU86_GETIP
#define EMU86_GETIP()  ((u16)EMU86_EMULATE_GETIP())
#define EMU86_SETIP(v) EMU86_EMULATE_SETIP((u16)(v))
#endif /* !EMU86_GETIP */
#ifndef EMU86_GETEIP
#define EMU86_GETEIP()  ((u32)EMU86_EMULATE_GETIP())
#define EMU86_SETEIP(v) EMU86_EMULATE_SETIP((u32)(v))
#endif /* !EMU86_GETEIP */
#if CONFIG_LIBEMU86_WANT_64BIT
#ifndef EMU86_GETRIP
#define EMU86_GETRIP()  ((u64)EMU86_EMULATE_GETIP())
#define EMU86_SETRIP(v) EMU86_EMULATE_SETIP((u64)(v))
#endif /* !EMU86_GETRIP */
#endif /* CONFIG_LIBEMU86_WANT_64BIT */

/* Get/Set the SP/ESP/RSP register (including SS.BASE)
 * Note that `EMU86_GETSP() == EMU86_SEGADDR(EMU86_GETSSBASE(), EMU86_GETSP_RAW())' */
#ifndef EMU86_GETSP
#define EMU86_GETSP()  icpustate_getsp(_state)
#ifdef __x86_64__
#define EMU86_SETSP(v) icpustate64_setrsp(_state, (__uintptr_t)(v))
#else /* __x86_64__ */
#define EMU86_SETSP(v) (_state = icpustate_setsp_p(_state, (__uintptr_t)(v)))
#endif /* !__x86_64__ */
#endif /* !EMU86_GETSP */

/* Same as `EMU86_EMULATE_GETIP()' is for `EMU86_EMULATE_GETPC()', but for `EMU86_GETSP()' */
#ifndef EMU86_GETSP_RAW
#define EMU86_GETSP_RAW()  EMU86_GETSP()
#define EMU86_SETSP_RAW(v) EMU86_SETSP(v)
#endif /* !EMU86_GETSP_RAW */

/* Return the base address address for a given segment */
#ifndef EMU86_GETSEGBASE
#define EMU86_GETSEGBASE_IS_NOOP_ES 1
#define EMU86_GETSEGBASE_IS_NOOP_CS 1
#define EMU86_GETSEGBASE_IS_NOOP_SS 1
#define EMU86_GETSEGBASE_IS_NOOP_DS 1
#define EMU86_GETSEGBASE_IS_NOOP_FS 1
#define EMU86_GETSEGBASE_IS_NOOP_GS 1
#define EMU86_GETSEGBASE(segment_regno) 0
#endif /* !EMU86_GETSEGBASE */

#if (defined(EMU86_GETSEGBASE_IS_NOOP_ES) || \
     defined(EMU86_GETSEGBASE_IS_NOOP_CS) || \
     defined(EMU86_GETSEGBASE_IS_NOOP_SS) || \
     defined(EMU86_GETSEGBASE_IS_NOOP_DS) || \
     defined(EMU86_GETSEGBASE_IS_NOOP_FS) || \
     defined(EMU86_GETSEGBASE_IS_NOOP_GS))
#if (defined(EMU86_GETSEGBASE_IS_NOOP_ES) && \
     defined(EMU86_GETSEGBASE_IS_NOOP_CS) && \
     defined(EMU86_GETSEGBASE_IS_NOOP_SS) && \
     defined(EMU86_GETSEGBASE_IS_NOOP_DS) && \
     defined(EMU86_GETSEGBASE_IS_NOOP_FS) && \
     defined(EMU86_GETSEGBASE_IS_NOOP_GS))
#define EMU86_GETSEGBASE_IS_NOOP_ALL 1
#define EMU86_GETSEGBASE_IS_NOOP(regno) 1
#else /* All-noop */
#ifdef EMU86_GETSEGBASE_IS_NOOP_ES
#define __EMU86_GETSEGBASE_IS_NOOP_ES 1
#else /* EMU86_GETSEGBASE_IS_NOOP_ES */
#define __EMU86_GETSEGBASE_IS_NOOP_ES 0
#endif /* !EMU86_GETSEGBASE_IS_NOOP_ES */
#ifdef EMU86_GETSEGBASE_IS_NOOP_CS
#define __EMU86_GETSEGBASE_IS_NOOP_CS 2
#else /* EMU86_GETSEGBASE_IS_NOOP_CS */
#define __EMU86_GETSEGBASE_IS_NOOP_CS 0
#endif /* !EMU86_GETSEGBASE_IS_NOOP_CS */
#ifdef EMU86_GETSEGBASE_IS_NOOP_SS
#define __EMU86_GETSEGBASE_IS_NOOP_SS 4
#else /* EMU86_GETSEGBASE_IS_NOOP_SS */
#define __EMU86_GETSEGBASE_IS_NOOP_SS 0
#endif /* !EMU86_GETSEGBASE_IS_NOOP_SS */
#ifdef EMU86_GETSEGBASE_IS_NOOP_DS
#define __EMU86_GETSEGBASE_IS_NOOP_DS 8
#else /* EMU86_GETSEGBASE_IS_NOOP_DS */
#define __EMU86_GETSEGBASE_IS_NOOP_DS 0
#endif /* !EMU86_GETSEGBASE_IS_NOOP_DS */
#ifdef EMU86_GETSEGBASE_IS_NOOP_FS
#define __EMU86_GETSEGBASE_IS_NOOP_FS 16
#else /* EMU86_GETSEGBASE_IS_NOOP_FS */
#define __EMU86_GETSEGBASE_IS_NOOP_FS 0
#endif /* !EMU86_GETSEGBASE_IS_NOOP_FS */
#ifdef EMU86_GETSEGBASE_IS_NOOP_GS
#define __EMU86_GETSEGBASE_IS_NOOP_GS 32
#else /* EMU86_GETSEGBASE_IS_NOOP_GS */
#define __EMU86_GETSEGBASE_IS_NOOP_GS 0
#endif /* !EMU86_GETSEGBASE_IS_NOOP_GS */
#define __EMU86_GETSEGBASE_IS_NOOP                                   \
	(__EMU86_GETSEGBASE_IS_NOOP_ES | __EMU86_GETSEGBASE_IS_NOOP_CS | \
	 __EMU86_GETSEGBASE_IS_NOOP_SS | __EMU86_GETSEGBASE_IS_NOOP_DS | \
	 __EMU86_GETSEGBASE_IS_NOOP_FS | __EMU86_GETSEGBASE_IS_NOOP_GS)
#define EMU86_GETSEGBASE_IS_NOOP_ANY 1
#define EMU86_GETSEGBASE_IS_NOOP(regno) \
	((__EMU86_GETSEGBASE_IS_NOOP >> (regno)) & 1)
#endif /* !All-noop */
#else /* Any-noop */
#define EMU86_GETSEGBASE_IS_NOOP(regno) 0
#endif /* !Any-noop */


#ifndef EMU86_GETDSBASE
#define EMU86_GETDSBASE() EMU86_GETSEGBASE(EMU86_R_DS)
#endif /* !EMU86_GETDSBASE */
#ifndef EMU86_GETESBASE
#define EMU86_GETESBASE() EMU86_GETSEGBASE(EMU86_R_ES)
#endif /* !EMU86_GETESBASE */
#ifndef EMU86_GETCSBASE
#define EMU86_GETCSBASE() EMU86_GETSEGBASE(EMU86_R_CS)
#endif /* !EMU86_GETCSBASE */
#ifndef EMU86_GETSSBASE
#define EMU86_GETSSBASE() EMU86_GETSEGBASE(EMU86_R_SS)
#endif /* !EMU86_GETSSBASE */
#ifndef EMU86_GETFSBASE
#define EMU86_GETFSBASE() EMU86_GETSEGBASE(EMU86_R_FS)
#endif /* !EMU86_GETFSBASE */
#ifndef EMU86_GETGSBASE
#define EMU86_GETGSBASE() EMU86_GETSEGBASE(EMU86_R_GS)
#endif /* !EMU86_GETGSBASE */

/* Form a memory address from a segment, and an offset to that segment */
#ifndef EMU86_SEGADDR
#define EMU86_SEGADDR(segbase, segoffset) ((segbase) + (segoffset))
#endif /* !EMU86_SEGADDR */

/* Get/Set the %es register */
#ifndef EMU86_GETES
#define EMU86_GETES()  icpustate_getes(_state)
#define EMU86_SETES(v) icpustate_setes(_state, v)
#endif /* !EMU86_GETES */

/* Get/Set the %cs register */
#ifndef EMU86_GETCS
#define EMU86_GETCS()  icpustate_getcs(_state)
#define EMU86_SETCS(v) icpustate_setcs(_state, v)
#endif /* !EMU86_GETCS */

/* Get/Set the %ss register */
#ifndef EMU86_GETSS
#define EMU86_GETSS()  icpustate_getss(_state)
#ifdef icpustate_setss
#define EMU86_SETSS(v) icpustate_setss(_state, v)
#else /* icpustate_setss */
#define EMU86_SETSS(v) icpustate_trysetss(_state, v) /* Override me to handle failure! */
#endif /* !icpustate_setss */
#endif /* !EMU86_GETSP */

/* Get/Set the %ds register */
#ifndef EMU86_GETDS
#define EMU86_GETDS()  icpustate_getds(_state)
#define EMU86_SETDS(v) icpustate_setds(_state, v)
#endif /* !EMU86_GETDS */

/* Get/Set the %fs register */
#ifndef EMU86_GETFS
#define EMU86_GETFS()  icpustate_getfs(_state)
#define EMU86_SETFS(v) icpustate_setfs(_state, v)
#endif /* !EMU86_GETFS */

/* Get/Set the %gs register */
#ifndef EMU86_GETGS
#define EMU86_GETGS()  icpustate_getgs(_state)
#define EMU86_SETGS(v) icpustate_setgs(_state, v)
#endif /* !EMU86_GETGS */

/* Notify that the instruction is about to push/pop the indicated number of bytes.
 * @param: new_sp: The new SP value (offset from `EMU86_GETSP()')
 * @param: old_sp: The old SP value (as returned by `EMU86_GETSP()') */
#ifndef EMU86_EMULATE_PUSH
#define EMU86_EMULATE_PUSH(new_sp, num_bytes) (void)0
#endif /* !EMU86_EMULATE_PUSH */
#ifndef EMU86_EMULATE_POP
#define EMU86_EMULATE_POP(old_sp, num_bytes) (void)0
#endif /* !EMU86_EMULATE_POP */

/* Verify user access to a specified I/O port range. (requires `EMU86_EMULATE_CHECKUSER') */
#ifndef EMU86_VALIDATE_IO
#define EMU86_VALIDATE_IO(portno, num_ports) (void)0
#endif /* !EMU86_VALIDATE_IO */

/* Access I/O ports. */
#ifndef EMU86_EMULATE_INB
#include <sys/io.h>
#define EMU86_EMULATE_INB(portno)         inb(portno)
#define EMU86_EMULATE_INW(portno)         inw(portno)
#define EMU86_EMULATE_INL(portno)         inl(portno)
#define EMU86_EMULATE_OUTB(portno, value) outb(portno, value)
#define EMU86_EMULATE_OUTW(portno, value) outw(portno, value)
#define EMU86_EMULATE_OUTL(portno, value) outl(portno, value)
#ifdef __KERNEL__
/* Define these to allow for some minor optimizations, when it is known
 * that in/out emulation can never throw an exception (Note that this
 * isn't the case for user-space, where use of these instructions can
 * result in an `E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE' exception) */
#define EMU86_EMULATE_IN_IS_NOEXCEPT 1
#define EMU86_EMULATE_OUT_IS_NOEXCEPT 1
#endif /* __KERNEL__ */
#endif /* !EMU86_EMULATE_INB */



/* Get a segment register by index
 * @param: regno: One of `EMU86_R_ES', `EMU86_R_CS', ... */
#ifndef EMU86_GETSEG
#define EMU86_GETSEG(regno) \
	(EMU86_EMULATE_HELPER_NAME(emu86_getseg)(EMU86_EMULATE_HELPER_PARAM_ regno))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED __ATTR_WUNUSED __ATTR_PURE EMU86_EMULATE_HELPER_ATTR u16
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_getseg))(EMU86_EMULATE_HELPER_ARGS_
                                                                                u8 regno) {
	u16 result;
	switch (regno) {
	case EMU86_R_ES: result = EMU86_GETES(); break;
	case EMU86_R_CS: result = EMU86_GETCS(); break;
	case EMU86_R_SS: result = EMU86_GETSS(); break;
	case EMU86_R_DS: result = EMU86_GETDS(); break;
	case EMU86_R_FS: result = EMU86_GETFS(); break;
	case EMU86_R_GS: result = EMU86_GETGS(); break;
	default: __builtin_unreachable();
	}
	return result;
}
#endif /* !EMU86_GETSEG */

/* Set a segment register by index
 * @param: regno: One of `EMU86_R_ES', `EMU86_R_CS', ... */
#ifndef EMU86_SETSEG
#define EMU86_SETSEG(regno, value) \
	(EMU86_EMULATE_HELPER_NAME(emu86_setseg)(EMU86_EMULATE_HELPER_PARAM_ regno, value))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED EMU86_EMULATE_HELPER_ATTR void
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_setseg))(EMU86_EMULATE_HELPER_ARGS_
                                                                                u8 regno, u16 value) {
	switch (regno) {
	case EMU86_R_ES: EMU86_SETES(value); break;
	case EMU86_R_CS: EMU86_SETCS(value); break;
	case EMU86_R_SS: EMU86_SETSS(value); break;
	case EMU86_R_DS: EMU86_SETDS(value); break;
	case EMU86_R_FS: EMU86_SETFS(value); break;
	case EMU86_R_GS: EMU86_SETGS(value); break;
	default: __builtin_unreachable();
	}
}
#endif /* !EMU86_SETSEG */



/* Get/set a general purpose register by index
 * @param: regno:    One of `EMU86_R_AL', `EMU86_R_CL', ...
 * @param: op_flags: Set of `0 | EMU86_F_HASREX' (only for 8-bit registers when 64-bit support is enabled) */
#if !defined(EMU86_GETREGB) || !defined(EMU86_SETREGB)
#ifdef __x86_64__
PRIVATE u8 const EMU86_EMULATE_HELPER_NAME(emu86_regb_offsets)[16] = {
	/* [EMU86_R_AL]   = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RAX,     /* %al */
	/* [EMU86_R_CL]   = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RCX,     /* %cl */
	/* [EMU86_R_DL]   = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RDX,     /* %dl */
	/* [EMU86_R_BL]   = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RBX,     /* %bl */
	/* [EMU86_R_AH]   = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RAX + 1, /* %ah */
	/* [EMU86_R_CH]   = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RCX + 1, /* %ch */
	/* [EMU86_R_DH]   = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RDX + 1, /* %dh */
	/* [EMU86_R_BH]   = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RBX + 1, /* %bh */
	/* [EMU86_R_R8L]  = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R8,      /* %r8l */
	/* [EMU86_R_R9L]  = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R9,      /* %r9l */
	/* [EMU86_R_R10L] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R10,     /* %r10l */
	/* [EMU86_R_R11L] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R11,     /* %r11l */
	/* [EMU86_R_R12L] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R12,     /* %r12l */
	/* [EMU86_R_R13L] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R13,     /* %r13l */
	/* [EMU86_R_R14L] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R14,     /* %r14l */
	/* [EMU86_R_R15L] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R15,     /* %r15l */
};
#else /* __x86_64__ */
PRIVATE u8 const EMU86_EMULATE_HELPER_NAME(emu86_regb_offsets)[8] = {
	/* [EMU86_R_AL] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX,     /* %al */
	/* [EMU86_R_CL] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ECX,     /* %cl */
	/* [EMU86_R_DL] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDX,     /* %dl */
	/* [EMU86_R_BL] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBX,     /* %bl */
	/* [EMU86_R_AH] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX + 1, /* %ah */
	/* [EMU86_R_CH] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ECX + 1, /* %ch */
	/* [EMU86_R_DH] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDX + 1, /* %dh */
	/* [EMU86_R_BH] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBX + 1, /* %bh */
};
#endif /* !__x86_64__ */
#endif /* !EMU86_GETREGB || !EMU86_SETREGB */

#if (!defined(EMU86_GETREGW) || !defined(EMU86_SETREGW) ||   \
     !defined(EMU86_GETREGL) || !defined(EMU86_SETREGL) ||   \
     (CONFIG_LIBEMU86_WANT_64BIT &&                          \
      (!defined(EMU86_GETREGB) || !defined(EMU86_SETREGB) || \
       !defined(EMU86_GETREGQ) || !defined(EMU86_SETREGQ))))
#ifdef __x86_64__
PRIVATE u8 const EMU86_EMULATE_HELPER_NAME(emu86_reg_offsets)[16] = {
	/* [EMU86_R_RAX] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RAX, /* %rax */
	/* [EMU86_R_RCX] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RCX, /* %rcx */
	/* [EMU86_R_RDX] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RDX, /* %rdx */
	/* [EMU86_R_RBX] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RBX, /* %rbx */
	/* [EMU86_R_RSP] = */ 0,                                                 /* %rsp */
	/* [EMU86_R_RBP] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RBP, /* %rbp */
	/* [EMU86_R_RSI] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RSI, /* %rsi */
	/* [EMU86_R_RDI] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RDI, /* %rdi */
	/* [EMU86_R_R8]  = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R8,  /* %r8 */
	/* [EMU86_R_R9]  = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R9,  /* %r9 */
	/* [EMU86_R_R10] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R10, /* %r10 */
	/* [EMU86_R_R11] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R11, /* %r11 */
	/* [EMU86_R_R12] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R12, /* %r12 */
	/* [EMU86_R_R13] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R13, /* %r13 */
	/* [EMU86_R_R14] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R14, /* %r14 */
	/* [EMU86_R_R15] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R15, /* %r15 */
};
#else /* __x86_64__ */
PRIVATE u8 const EMU86_EMULATE_HELPER_NAME(emu86_reg_offsets)[8] = {
	/* [EMU86_R_EAX] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX, /* %eax */
	/* [EMU86_R_ECX] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ECX, /* %ecx */
	/* [EMU86_R_EDX] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDX, /* %edx */
	/* [EMU86_R_EBX] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBX, /* %ebx */
	/* [EMU86_R_ESP] = */ 0,                                           /* %esp */
	/* [EMU86_R_EBP] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBP, /* %ebp */
	/* [EMU86_R_ESI] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ESI, /* %esi */
	/* [EMU86_R_EDI] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDI, /* %edi */
};
#endif /* !__x86_64__ */
#endif /* Need `emu86_reg_offsets' */

#ifdef __x86_64__
#define __EMU86_GPREG_MASK 0xf
#else /* __x86_64__ */
#define __EMU86_GPREG_MASK 0x7
#endif /* !__x86_64__ */


#ifndef EMU86_GETREGB
#if CONFIG_LIBEMU86_WANT_64BIT
#define EMU86_GETREGB(regno, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_getregb)(EMU86_EMULATE_HELPER_PARAM_ regno, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED __ATTR_WUNUSED __ATTR_PURE EMU86_EMULATE_HELPER_ATTR u8
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_getregb))(EMU86_EMULATE_HELPER_ARGS_
                                                                                 u8 regno,
                                                                                 emu86_opflags_t op_flags)
#else /* CONFIG_LIBEMU86_WANT_64BIT */
#define EMU86_GETREGB(regno, ...) \
	(EMU86_EMULATE_HELPER_NAME(emu86_getregb)(EMU86_EMULATE_HELPER_PARAM_ regno))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED __ATTR_WUNUSED __ATTR_PURE EMU86_EMULATE_HELPER_ATTR u8
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_getregb))(EMU86_EMULATE_HELPER_ARGS_
                                                                                 u8 regno)
#endif /* !CONFIG_LIBEMU86_WANT_64BIT */
{
	regno &= __EMU86_GPREG_MASK;
#if CONFIG_LIBEMU86_WANT_64BIT
	if (op_flags & EMU86_F_HASREX) {
		if (regno == EMU86_R_SPL)
			return (u8)EMU86_GETSP();
		return *(u8 const *)((byte_t const *)_state + EMU86_EMULATE_HELPER_NAME(emu86_reg_offsets)[regno]);
	}
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
	return *(u8 const *)((byte_t const *)_state + EMU86_EMULATE_HELPER_NAME(emu86_regb_offsets)[regno]);
}
#endif /* !EMU86_GETREGB */

#ifndef EMU86_SETREGB
#if CONFIG_LIBEMU86_WANT_64BIT
#define EMU86_SETREGB(regno, value, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_setregb)(EMU86_EMULATE_HELPER_PARAM_ regno, value, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED EMU86_EMULATE_HELPER_ATTR void
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_setregb))(EMU86_EMULATE_HELPER_ARGS_
                                                                                 u8 regno, u8 value,
                                                                                 emu86_opflags_t op_flags)
#else /* CONFIG_LIBEMU86_WANT_64BIT */
#define EMU86_SETREGB(regno, value, ...) \
	(EMU86_EMULATE_HELPER_NAME(emu86_setregb)(EMU86_EMULATE_HELPER_PARAM_ regno, value))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED EMU86_EMULATE_HELPER_ATTR void
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_setregb))(EMU86_EMULATE_HELPER_ARGS_
                                                                                 u8 regno, u8 value)
#endif /* !CONFIG_LIBEMU86_WANT_64BIT */
{
	regno &= __EMU86_GPREG_MASK;
#if CONFIG_LIBEMU86_WANT_64BIT
	if (op_flags & EMU86_F_HASREX) {
		if (regno == EMU86_R_SPL) {
			EMU86_SETSP((EMU86_GETSP() & ~0xff) | value);
		} else {
			*(u8 *)((byte_t *)_state + EMU86_EMULATE_HELPER_NAME(emu86_reg_offsets)[regno]) = value;
		}
	} else
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
	{
		*(u8 *)((byte_t *)_state + EMU86_EMULATE_HELPER_NAME(emu86_regb_offsets)[regno]) = value;
	}
}
#endif /* !EMU86_SETREGB */

#ifndef EMU86_GETREGW
#define EMU86_GETREGW(regno) \
	(EMU86_EMULATE_HELPER_NAME(emu86_getregw)(EMU86_EMULATE_HELPER_PARAM_ regno))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED __ATTR_WUNUSED __ATTR_PURE EMU86_EMULATE_HELPER_ATTR u16
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_getregw))(EMU86_EMULATE_HELPER_ARGS_
                                                                                 u8 regno) {
	regno &= __EMU86_GPREG_MASK;
	if (regno == EMU86_R_SP)
		return EMU86_GETSP();
	return (u16)*(uintptr_t const *)((byte_t *)_state + EMU86_EMULATE_HELPER_NAME(emu86_reg_offsets)[regno]);
}
#endif /* !EMU86_GETREGW */

#ifndef EMU86_SETREGW
#define EMU86_SETREGW(regno, value) \
	(EMU86_EMULATE_HELPER_NAME(emu86_setregw)(EMU86_EMULATE_HELPER_PARAM_ regno, value))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED EMU86_EMULATE_HELPER_ATTR void
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_setregw))(EMU86_EMULATE_HELPER_ARGS_
                                                                                 u8 regno, u16 value) {
	regno &= __EMU86_GPREG_MASK;
	if (regno == EMU86_R_SP) {
		EMU86_SETSP((uintptr_t)value);
	} else {
		*(uintptr_t *)((byte_t *)_state + EMU86_EMULATE_HELPER_NAME(emu86_reg_offsets)[regno]) = (uintptr_t)value;
	}
}
#endif /* !EMU86_SETREGW */

#ifndef EMU86_GETREGL
#define EMU86_GETREGL(regno) \
	(EMU86_EMULATE_HELPER_NAME(emu86_getregl)(EMU86_EMULATE_HELPER_PARAM_ regno))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED __ATTR_WUNUSED __ATTR_PURE EMU86_EMULATE_HELPER_ATTR u32
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_getregl))(EMU86_EMULATE_HELPER_ARGS_
                                                                                 u8 regno) {
	regno &= __EMU86_GPREG_MASK;
	if (regno == EMU86_R_SP)
		return EMU86_GETSP();
	return (u32)*(uintptr_t const *)((byte_t const *)_state + EMU86_EMULATE_HELPER_NAME(emu86_reg_offsets)[regno]);
}
#endif /* !EMU86_GETREGL */

#ifndef EMU86_SETREGL
#define EMU86_SETREGL(regno, value) \
	(EMU86_EMULATE_HELPER_NAME(emu86_setregl)(EMU86_EMULATE_HELPER_PARAM_ regno, value))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED EMU86_EMULATE_HELPER_ATTR void
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_setregl))(EMU86_EMULATE_HELPER_ARGS_
                                                                                 u8 regno, u32 value) {
	regno &= __EMU86_GPREG_MASK;
	if (regno == EMU86_R_SP) {
		EMU86_SETSP((uintptr_t)value);
	} else {
		*(uintptr_t *)((byte_t *)_state + EMU86_EMULATE_HELPER_NAME(emu86_reg_offsets)[regno]) = (uintptr_t)value;
	}
}
#endif /* !EMU86_SETREGL */

#if CONFIG_LIBEMU86_WANT_64BIT
#ifndef EMU86_GETREGQ
#define EMU86_GETREGQ(regno) \
	(EMU86_EMULATE_HELPER_NAME(emu86_getregq)(EMU86_EMULATE_HELPER_PARAM_ regno))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED __ATTR_WUNUSED __ATTR_PURE EMU86_EMULATE_HELPER_ATTR u64
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_getregq))(EMU86_EMULATE_HELPER_ARGS_
                                                                                 u8 regno) {
	regno &= __EMU86_GPREG_MASK;
	if (regno == EMU86_R_SP)
		return (u64)EMU86_GETSP();
	return (u64)*(uintptr_t const *)((byte_t const *)_state + EMU86_EMULATE_HELPER_NAME(emu86_reg_offsets)[regno]);
}
#endif /* !EMU86_GETREGQ */

#ifndef EMU86_SETREGQ
#define EMU86_SETREGQ(regno, value) \
	(EMU86_EMULATE_HELPER_NAME(emu86_setregq)(EMU86_EMULATE_HELPER_PARAM_ regno, value))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED EMU86_EMULATE_HELPER_ATTR void
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_setregq))(EMU86_EMULATE_HELPER_ARGS_
                                                                                 u8 regno, u64 value) {
	regno &= __EMU86_GPREG_MASK;
	if (regno == EMU86_R_SP) {
		EMU86_SETSP((uintptr_t)value);
	} else {
		*(uintptr_t *)((byte_t *)_state + EMU86_EMULATE_HELPER_NAME(emu86_reg_offsets)[regno]) = (uintptr_t)value;
	}
}
#endif /* !EMU86_SETREGQ */
#endif /* CONFIG_LIBEMU86_WANT_64BIT */


/* Get/set a pointer-sized general purpose register by index
 * @param: regno: One of `EMU86_R_AX', `EMU86_R_EAX', `EMU86_R_RAX', `EMU86_R_CX', ... */
#ifndef EMU86_GETREGP
#ifndef CONFIG_LIBEMU86_NEED_ARCHMODE
#if CONFIG_LIBEMU86_WANT_16BIT
#define EMU86_GETREGP(regno, ...) EMU86_GETREGW(regno)
#elif CONFIG_LIBEMU86_WANT_32BIT
#define EMU86_GETREGP(regno, ...) EMU86_GETREGL(regno)
#elif CONFIG_LIBEMU86_WANT_64BIT
#define EMU86_GETREGP(regno, ...) EMU86_GETREGQ(regno)
#else /* ... */
#error "Invalid configuration"
#endif /* !... */
#else /* !CONFIG_LIBEMU86_NEED_ARCHMODE */
#define EMU86_GETREGP(regno, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_getregp)(EMU86_EMULATE_HELPER_PARAM_ regno, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED __ATTR_WUNUSED __ATTR_PURE EMU86_EMULATE_HELPER_ATTR uintptr_t
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_getregp))(EMU86_EMULATE_HELPER_ARGS_
                                                                                 u8 regno,
                                                                                 emu86_opflags_t op_flags) {
#if CONFIG_LIBEMU86_WANT_64BIT
	if (EMU86_F_IS64(op_flags))
		return (uintptr_t)EMU86_GETREGQ(regno);
#if CONFIG_LIBEMU86_WANT_16BIT && CONFIG_LIBEMU86_WANT_32BIT
	if (EMU86_F_IS32(op_flags))
		return (uintptr_t)EMU86_GETREGL(regno);
	return (uintptr_t)EMU86_GETREGW(regno);
#elif CONFIG_LIBEMU86_WANT_16BIT
	return (uintptr_t)EMU86_GETREGW(regno);
#elif CONFIG_LIBEMU86_WANT_32BIT
	return (uintptr_t)EMU86_GETREGL(regno);
#else
#error "Invalid configuration"
#endif
#else /* CONFIG_LIBEMU86_WANT_64BIT */
	if (EMU86_F_IS32(op_flags))
		return (uintptr_t)EMU86_GETREGL(regno);
	return (uintptr_t)EMU86_GETREGW(regno);
#endif /* !CONFIG_LIBEMU86_WANT_64BIT */
}
#endif /* CONFIG_LIBEMU86_NEED_ARCHMODE */
#endif /* !EMU86_GETREGP */

#ifndef EMU86_SETREGP
#ifndef CONFIG_LIBEMU86_NEED_ARCHMODE
#if CONFIG_LIBEMU86_WANT_16BIT
#define EMU86_SETREGP(regno, value, ...) EMU86_SETREGW(regno, value)
#elif CONFIG_LIBEMU86_WANT_32BIT
#define EMU86_SETREGP(regno, value, ...) EMU86_SETREGL(regno, value)
#elif CONFIG_LIBEMU86_WANT_64BIT
#define EMU86_SETREGP(regno, value, ...) EMU86_SETREGQ(regno, value)
#else /* ... */
#error "Invalid configuration"
#endif /* !... */
#else /* !CONFIG_LIBEMU86_NEED_ARCHMODE */
#define EMU86_SETREGP(regno, value, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_setregp)(EMU86_EMULATE_HELPER_PARAM_ regno, value, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED __ATTR_WUNUSED __ATTR_PURE EMU86_EMULATE_HELPER_ATTR uintptr_t
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_setregp))(EMU86_EMULATE_HELPER_ARGS_
                                                                                 u8 regno, uintptr_t value,
                                                                                 emu86_opflags_t op_flags) {
#if CONFIG_LIBEMU86_WANT_64BIT
	if (EMU86_F_IS64(op_flags)) {
		EMU86_SETREGQ(regno, (u64)value);
		return;
	}
#if CONFIG_LIBEMU86_WANT_16BIT && CONFIG_LIBEMU86_WANT_32BIT
	if (EMU86_F_IS32(op_flags)) {
		EMU86_SETREGL(regno, (u32)value);
		return;
	}
	EMU86_SETREGW(regno, (u16)value);
#elif CONFIG_LIBEMU86_WANT_16BIT
	EMU86_SETREGW(regno, (u16)value);
#elif CONFIG_LIBEMU86_WANT_32BIT
	EMU86_SETREGL(regno, (u32)value);
#else
#error "Invalid configuration"
#endif
#else /* CONFIG_LIBEMU86_WANT_64BIT */
	if (EMU86_F_IS32(op_flags)) {
		EMU86_SETREGL(regno, (u32)value);
	} else {
		EMU86_SETREGW(regno, (u16)value);
	}
#endif /* !CONFIG_LIBEMU86_WANT_64BIT */
}
#endif /* CONFIG_LIBEMU86_NEED_ARCHMODE */
#endif /* !EMU86_SETREGP */


/* Get/set specific registers */
#ifndef EMU86_GETAL
#define EMU86_GETAL() EMU86_GETREGB(EMU86_R_AL, 0)
#define EMU86_GETCL() EMU86_GETREGB(EMU86_R_CL, 0)
#define EMU86_GETDL() EMU86_GETREGB(EMU86_R_DL, 0)
#define EMU86_GETBL() EMU86_GETREGB(EMU86_R_BL, 0)
#endif /* !EMU86_GETAL */
#ifndef EMU86_SETAL
#define EMU86_SETAL(value) EMU86_SETREGB(EMU86_R_AL, value, 0)
#define EMU86_SETCL(value) EMU86_SETREGB(EMU86_R_CL, value, 0)
#define EMU86_SETDL(value) EMU86_SETREGB(EMU86_R_DL, value, 0)
#define EMU86_SETBL(value) EMU86_SETREGB(EMU86_R_BL, value, 0)
#endif /* !EMU86_SETAL */
#ifndef EMU86_GETAH
#define EMU86_GETAH() EMU86_GETREGB(EMU86_R_AH, 0)
#define EMU86_GETCH() EMU86_GETREGB(EMU86_R_CH, 0)
#define EMU86_GETDH() EMU86_GETREGB(EMU86_R_DH, 0)
#define EMU86_GETBH() EMU86_GETREGB(EMU86_R_BH, 0)
#endif /* !EMU86_GETAH */
#ifndef EMU86_SETAH
#define EMU86_SETAH(value) EMU86_SETREGB(EMU86_R_AH, value, 0)
#define EMU86_SETCH(value) EMU86_SETREGB(EMU86_R_CH, value, 0)
#define EMU86_SETDH(value) EMU86_SETREGB(EMU86_R_DH, value, 0)
#define EMU86_SETBH(value) EMU86_SETREGB(EMU86_R_BH, value, 0)
#endif /* !EMU86_SETAH */
#ifndef EMU86_GETAX
#define EMU86_GETAX() EMU86_GETREGW(EMU86_R_AX)
#define EMU86_GETCX() EMU86_GETREGW(EMU86_R_CX)
#define EMU86_GETDX() EMU86_GETREGW(EMU86_R_DX)
#define EMU86_GETBX() EMU86_GETREGW(EMU86_R_BX)
#define EMU86_GETSPREG() EMU86_GETREGW(EMU86_R_SP)
#define EMU86_GETBP() EMU86_GETREGW(EMU86_R_BP)
#define EMU86_GETSI() EMU86_GETREGW(EMU86_R_SI)
#define EMU86_GETDI() EMU86_GETREGW(EMU86_R_DI)
#endif /* !EMU86_GETAX */
#ifndef EMU86_SETAX
#define EMU86_SETAX(value) EMU86_SETREGW(EMU86_R_AX, value)
#define EMU86_SETCX(value) EMU86_SETREGW(EMU86_R_CX, value)
#define EMU86_SETDX(value) EMU86_SETREGW(EMU86_R_DX, value)
#define EMU86_SETBX(value) EMU86_SETREGW(EMU86_R_BX, value)
#define EMU86_SETSPREG(value) EMU86_SETREGW(EMU86_R_SP, value)
#define EMU86_SETBP(value) EMU86_SETREGW(EMU86_R_BP, value)
#define EMU86_SETSI(value) EMU86_SETREGW(EMU86_R_SI, value)
#define EMU86_SETDI(value) EMU86_SETREGW(EMU86_R_DI, value)
#endif /* !EMU86_SETAX */
#ifndef EMU86_GETEAX
#define EMU86_GETEAX() EMU86_GETREGL(EMU86_R_EAX)
#define EMU86_GETECX() EMU86_GETREGL(EMU86_R_ECX)
#define EMU86_GETEDX() EMU86_GETREGL(EMU86_R_EDX)
#define EMU86_GETEBX() EMU86_GETREGL(EMU86_R_EBX)
#define EMU86_GETESP() EMU86_GETREGL(EMU86_R_ESP)
#define EMU86_GETEBP() EMU86_GETREGL(EMU86_R_EBP)
#define EMU86_GETESI() EMU86_GETREGL(EMU86_R_ESI)
#define EMU86_GETEDI() EMU86_GETREGL(EMU86_R_EDI)
#endif /* !EMU86_GETEAX */
#ifndef EMU86_SETEAX
#define EMU86_SETEAX(value) EMU86_SETREGL(EMU86_R_EAX, value)
#define EMU86_SETECX(value) EMU86_SETREGL(EMU86_R_ECX, value)
#define EMU86_SETEDX(value) EMU86_SETREGL(EMU86_R_EDX, value)
#define EMU86_SETEBX(value) EMU86_SETREGL(EMU86_R_EBX, value)
#define EMU86_SETESP(value) EMU86_SETREGL(EMU86_R_ESP, value)
#define EMU86_SETEBP(value) EMU86_SETREGL(EMU86_R_EBP, value)
#define EMU86_SETESI(value) EMU86_SETREGL(EMU86_R_ESI, value)
#define EMU86_SETEDI(value) EMU86_SETREGL(EMU86_R_EDI, value)
#endif /* !EMU86_SETEAX */
#if CONFIG_LIBEMU86_WANT_64BIT
#ifndef EMU86_GETSPL
#define EMU86_GETSPL() EMU86_GETREGB(EMU86_R_SP, EMU86_F_HASREX)
#define EMU86_GETBPL() EMU86_GETREGB(EMU86_R_BP, EMU86_F_HASREX)
#define EMU86_GETSIL() EMU86_GETREGB(EMU86_R_SI, EMU86_F_HASREX)
#define EMU86_GETDIL() EMU86_GETREGB(EMU86_R_DI, EMU86_F_HASREX)
#endif /* !EMU86_GETSPL */
#ifndef EMU86_SETSPL
#define EMU86_SETSPL(value) EMU86_SETREGB(EMU86_R_SP, value, EMU86_F_HASREX)
#define EMU86_SETBPL(value) EMU86_SETREGB(EMU86_R_BP, value, EMU86_F_HASREX)
#define EMU86_SETSIL(value) EMU86_SETREGB(EMU86_R_SI, value, EMU86_F_HASREX)
#define EMU86_SETDIL(value) EMU86_SETREGB(EMU86_R_DI, value, EMU86_F_HASREX)
#endif /* !EMU86_SETSPL */
#ifndef EMU86_GETRAX
#define EMU86_GETRAX() EMU86_GETREGQ(EMU86_R_RAX)
#define EMU86_GETRCX() EMU86_GETREGQ(EMU86_R_RCX)
#define EMU86_GETRDX() EMU86_GETREGQ(EMU86_R_RDX)
#define EMU86_GETRBX() EMU86_GETREGQ(EMU86_R_RBX)
#define EMU86_GETRSP() EMU86_GETREGQ(EMU86_R_RSP)
#define EMU86_GETRBP() EMU86_GETREGQ(EMU86_R_RBP)
#define EMU86_GETRSI() EMU86_GETREGQ(EMU86_R_RSI)
#define EMU86_GETRDI() EMU86_GETREGQ(EMU86_R_RDI)
#endif /* !EMU86_GETRAX */
#ifndef EMU86_SETRAX
#define EMU86_SETRAX(value) EMU86_SETREGQ(EMU86_R_RAX, value)
#define EMU86_SETRCX(value) EMU86_SETREGQ(EMU86_R_RCX, value)
#define EMU86_SETRDX(value) EMU86_SETREGQ(EMU86_R_RDX, value)
#define EMU86_SETRBX(value) EMU86_SETREGQ(EMU86_R_RBX, value)
#define EMU86_SETRSP(value) EMU86_SETREGQ(EMU86_R_RSP, value)
#define EMU86_SETRBP(value) EMU86_SETREGQ(EMU86_R_RBP, value)
#define EMU86_SETRSI(value) EMU86_SETREGQ(EMU86_R_RSI, value)
#define EMU86_SETRDI(value) EMU86_SETREGQ(EMU86_R_RDI, value)
#endif /* !EMU86_SETRAX */
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
#ifndef EMU86_GETPAX
#define EMU86_GETPAX(op_flags) EMU86_GETREGP(EMU86_R_AX, op_flags)
#define EMU86_GETPCX(op_flags) EMU86_GETREGP(EMU86_R_CX, op_flags)
#define EMU86_GETPDX(op_flags) EMU86_GETREGP(EMU86_R_DX, op_flags)
#define EMU86_GETPBX(op_flags) EMU86_GETREGP(EMU86_R_BX, op_flags)
#define EMU86_GETPSP(op_flags) EMU86_GETREGP(EMU86_R_SP, op_flags)
#define EMU86_GETPBP(op_flags) EMU86_GETREGP(EMU86_R_BP, op_flags)
#define EMU86_GETPSI(op_flags) EMU86_GETREGP(EMU86_R_SI, op_flags)
#define EMU86_GETPDI(op_flags) EMU86_GETREGP(EMU86_R_DI, op_flags)
#endif /* !EMU86_GETPAX */
#ifndef EMU86_SETPAX
#define EMU86_SETPAX(value, op_flags) EMU86_SETREGP(EMU86_R_AX, value, op_flags)
#define EMU86_SETPCX(value, op_flags) EMU86_SETREGP(EMU86_R_CX, value, op_flags)
#define EMU86_SETPDX(value, op_flags) EMU86_SETREGP(EMU86_R_DX, value, op_flags)
#define EMU86_SETPBX(value, op_flags) EMU86_SETREGP(EMU86_R_BX, value, op_flags)
#define EMU86_SETPSP(value, op_flags) EMU86_SETREGP(EMU86_R_SP, value, op_flags)
#define EMU86_SETPBP(value, op_flags) EMU86_SETREGP(EMU86_R_BP, value, op_flags)
#define EMU86_SETPSI(value, op_flags) EMU86_SETREGP(EMU86_R_SI, value, op_flags)
#define EMU86_SETPDI(value, op_flags) EMU86_SETREGP(EMU86_R_DI, value, op_flags)
#endif /* !EMU86_SETPAX */




/* Calculate the memory address of a given modrm */
#ifndef EMU86_MODRM_MEMADDR
#define EMU86_MODRM_MEMADDR(modrm, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_modrm_memaddr)(EMU86_EMULATE_HELPER_PARAM_ modrm, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED __ATTR_WUNUSED ATTR_PURE EMU86_EMULATE_HELPER_ATTR byte_t *
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_modrm_memaddr))(EMU86_EMULATE_HELPER_ARGS_
                                                                                       struct emu86_modrm const *__restrict modrm,
                                                                                       emu86_opflags_t op_flags) {
	uintptr_t result;
	(void)op_flags;
	result = modrm->mi_offset;
	if (modrm->mi_rm != 0xff)
		result += EMU86_GETREGP(modrm->mi_rm, op_flags);
	if (modrm->mi_index != 0xff)
		result += EMU86_GETREGP(modrm->mi_index, op_flags) << modrm->mi_shift;
#ifndef EMU86_GETSEGBASE_IS_NOOP_ALL
	{
		u8 reg = EMU86_F_SEGREG(op_flags);
		if (!EMU86_GETSEGBASE_IS_NOOP(reg)) {
			uintptr_t segment_base;
			segment_base = (uintptr_t)EMU86_GETSEGBASE(reg);
			result       = (uintptr_t)EMU86_SEGADDR(segment_base, result);
		}
	}
#endif /* !EMU86_GETSEGBASE_IS_NOOP_ALL */
	return (byte_t *)result;
}
#endif /* !EMU86_MODRM_MEMADDR */

#ifndef EMU86_MODRM_MEMADDR_NOSEGBASE
#ifdef EMU86_GETSEGBASE_IS_NOOP_ALL
#define EMU86_MODRM_MEMADDR_NOSEGBASE(modrm, op_flags) \
	EMU86_MODRM_MEMADDR(modrm, op_flags)
#else /* EMU86_GETSEGBASE_IS_NOOP_ALL */
#define EMU86_MODRM_MEMADDR_NOSEGBASE(modrm, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_modrm_memaddr_nosegbase)(EMU86_EMULATE_HELPER_PARAM_ modrm, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED __ATTR_WUNUSED ATTR_PURE EMU86_EMULATE_HELPER_ATTR byte_t *
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_modrm_memaddr_nosegbase))(EMU86_EMULATE_HELPER_ARGS_
                                                                                                 struct emu86_modrm const *__restrict modrm,
                                                                                                 emu86_opflags_t op_flags) {
	uintptr_t result;
	(void)op_flags;
	result = modrm->mi_offset;
	if (modrm->mi_rm != 0xff)
		result += EMU86_GETREGP(modrm->mi_rm, op_flags);
	if (modrm->mi_index != 0xff)
		result += EMU86_GETREGP(modrm->mi_index, op_flags) << modrm->mi_shift;
	return (byte_t *)result;
}
#endif /* !EMU86_GETSEGBASE_IS_NOOP_ALL */
#endif /* !EMU86_MODRM_MEMADDR_NOSEGBASE */





/* Get/Set the R/M operand from a given modrm */
#ifndef EMU86_GETMODRM_RMB
#define EMU86_GETMODRM_RMB(modrm, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_getmodrm_rmb)(EMU86_EMULATE_HELPER_PARAM_ modrm, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED __ATTR_WUNUSED __ATTR_PURE EMU86_EMULATE_HELPER_ATTR u8
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_getmodrm_rmb))(EMU86_EMULATE_HELPER_ARGS_
                                                                                      struct emu86_modrm const *__restrict modrm,
                                                                                      emu86_opflags_t op_flags) {
	byte_t *addr;
#ifndef EMU86_EMULATE_ONLY_MEMORY
	if (EMU86_MODRM_ISREG(modrm->mi_type))
		return EMU86_GETREGB(modrm->mi_rm, op_flags);
#endif /* !EMU86_EMULATE_ONLY_MEMORY */
	addr = EMU86_MODRM_MEMADDR(modrm, op_flags);
#if EMU86_EMULATE_CHECKUSER
	if (EMU86_ISUSER())
		EMU86_VALIDATE_READABLE(addr, 1);
#endif /* EMU86_EMULATE_CHECKUSER */
	return EMU86_EMULATE_READB(addr);
}
#endif /* !EMU86_GETMODRM_RMB */

#ifndef EMU86_SETMODRM_RMB
#define EMU86_SETMODRM_RMB(modrm, value, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_setmodrm_rmb)(EMU86_EMULATE_HELPER_PARAM_ modrm, value, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED EMU86_EMULATE_HELPER_ATTR void
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_setmodrm_rmb))(EMU86_EMULATE_HELPER_ARGS_
                                                                                      struct emu86_modrm const *__restrict modrm,
                                                                                      u8 value, emu86_opflags_t op_flags) {
#ifndef EMU86_EMULATE_ONLY_MEMORY
	if (EMU86_MODRM_ISREG(modrm->mi_type)) {
		EMU86_SETREGB(modrm->mi_rm, value, op_flags);
	} else
#endif /* !EMU86_EMULATE_ONLY_MEMORY */
	{
		byte_t *addr;
		addr = EMU86_MODRM_MEMADDR(modrm, op_flags);
#if EMU86_EMULATE_CHECKUSER
		if (EMU86_ISUSER())
			EMU86_VALIDATE_WRITABLE(addr, 1);
#endif /* EMU86_EMULATE_CHECKUSER */
		EMU86_EMULATE_WRITEB(addr, value);
	}
}
#endif /* !EMU86_SETMODRM_RMB */

#ifndef EMU86_GETMODRM_RMW
#define EMU86_GETMODRM_RMW(modrm, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_getmodrm_rmw)(EMU86_EMULATE_HELPER_PARAM_ modrm, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED __ATTR_WUNUSED __ATTR_PURE EMU86_EMULATE_HELPER_ATTR u16
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_getmodrm_rmw))(EMU86_EMULATE_HELPER_ARGS_
                                                                                      struct emu86_modrm const *__restrict modrm,
                                                                                      emu86_opflags_t op_flags) {
	byte_t *addr;
#ifndef EMU86_EMULATE_ONLY_MEMORY
	if (EMU86_MODRM_ISREG(modrm->mi_type))
		return EMU86_GETREGW(modrm->mi_rm);
#endif /* !EMU86_EMULATE_ONLY_MEMORY */
	addr = EMU86_MODRM_MEMADDR(modrm, op_flags);
#if EMU86_EMULATE_CHECKUSER
	if (EMU86_ISUSER())
		EMU86_VALIDATE_READABLE(addr, 2);
#endif /* EMU86_EMULATE_CHECKUSER */
	return EMU86_EMULATE_READW(addr);
}
#endif /* !EMU86_GETMODRM_RMW */

#ifndef EMU86_SETMODRM_RMW
#define EMU86_SETMODRM_RMW(modrm, value, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_setmodrm_rmw)(EMU86_EMULATE_HELPER_PARAM_ modrm, value, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED EMU86_EMULATE_HELPER_ATTR void
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_setmodrm_rmw))(EMU86_EMULATE_HELPER_ARGS_
                                                                                      struct emu86_modrm const *__restrict modrm,
                                                                                      u16 value, emu86_opflags_t op_flags) {
#ifndef EMU86_EMULATE_ONLY_MEMORY
	if (EMU86_MODRM_ISREG(modrm->mi_type)) {
		EMU86_SETREGW(modrm->mi_rm, value);
	} else
#endif /* !EMU86_EMULATE_ONLY_MEMORY */
	{
		byte_t *addr;
		addr = EMU86_MODRM_MEMADDR(modrm, op_flags);
#if EMU86_EMULATE_CHECKUSER
		if (EMU86_ISUSER())
			EMU86_VALIDATE_WRITABLE(addr, 2);
#endif /* EMU86_EMULATE_CHECKUSER */
		EMU86_EMULATE_WRITEW(addr, value);
	}
}
#endif /* !EMU86_SETMODRM_RMW */

#ifndef EMU86_GETMODRM_RML
#define EMU86_GETMODRM_RML(modrm, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_getmodrm_rml)(EMU86_EMULATE_HELPER_PARAM_ modrm, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED __ATTR_WUNUSED __ATTR_PURE EMU86_EMULATE_HELPER_ATTR u32
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_getmodrm_rml))(EMU86_EMULATE_HELPER_ARGS_
                                                                                      struct emu86_modrm const *__restrict modrm,
                                                                                      emu86_opflags_t op_flags) {
	byte_t *addr;
#ifndef EMU86_EMULATE_ONLY_MEMORY
	if (EMU86_MODRM_ISREG(modrm->mi_type))
		return EMU86_GETREGL(modrm->mi_rm);
#endif /* !EMU86_EMULATE_ONLY_MEMORY */
	addr = EMU86_MODRM_MEMADDR(modrm, op_flags);
#if EMU86_EMULATE_CHECKUSER
	if (EMU86_ISUSER())
		EMU86_VALIDATE_READABLE(addr, 4);
#endif /* EMU86_EMULATE_CHECKUSER */
	return EMU86_EMULATE_READL(addr);
}
#endif /* !EMU86_GETMODRM_RML */

#ifndef EMU86_SETMODRM_RML
#define EMU86_SETMODRM_RML(modrm, value, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_setmodrm_rml)(EMU86_EMULATE_HELPER_PARAM_ modrm, value, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED EMU86_EMULATE_HELPER_ATTR void
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_setmodrm_rml))(EMU86_EMULATE_HELPER_ARGS_
                                                                                      struct emu86_modrm const *__restrict modrm,
                                                                                      u32 value, emu86_opflags_t op_flags) {
#ifndef EMU86_EMULATE_ONLY_MEMORY
	if (EMU86_MODRM_ISREG(modrm->mi_type)) {
		EMU86_SETREGL(modrm->mi_rm, value);
	} else
#endif /* !EMU86_EMULATE_ONLY_MEMORY */
	{
		byte_t *addr;
		addr = EMU86_MODRM_MEMADDR(modrm, op_flags);
#if EMU86_EMULATE_CHECKUSER
		if (EMU86_ISUSER())
			EMU86_VALIDATE_WRITABLE(addr, 4);
#endif /* EMU86_EMULATE_CHECKUSER */
		EMU86_EMULATE_WRITEL(addr, value);
	}
}
#endif /* !EMU86_SETMODRM_RML */

#if CONFIG_LIBEMU86_WANT_64BIT
#ifndef EMU86_GETMODRM_RMQ
#define EMU86_GETMODRM_RMQ(modrm, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_getmodrm_rmq)(EMU86_EMULATE_HELPER_PARAM_ modrm, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED __ATTR_WUNUSED __ATTR_PURE EMU86_EMULATE_HELPER_ATTR u64
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_getmodrm_rmq))(EMU86_EMULATE_HELPER_ARGS_
                                                                                      struct emu86_modrm const *__restrict modrm,
                                                                                      emu86_opflags_t op_flags) {
	byte_t *addr;
#ifndef EMU86_EMULATE_ONLY_MEMORY
	if (EMU86_MODRM_ISREG(modrm->mi_type))
		return EMU86_GETREGQ(modrm->mi_rm);
#endif /* !EMU86_EMULATE_ONLY_MEMORY */
	addr = EMU86_MODRM_MEMADDR(modrm, op_flags);
#if EMU86_EMULATE_CHECKUSER
	if (EMU86_ISUSER())
		EMU86_VALIDATE_READABLE(addr, 8);
#endif /* EMU86_EMULATE_CHECKUSER */
	return EMU86_EMULATE_READQ(addr);
}
#endif /* !EMU86_GETMODRM_RMQ */

#ifndef EMU86_SETMODRM_RMQ
#define EMU86_SETMODRM_RMQ(modrm, value, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_setmodrm_rmq)(EMU86_EMULATE_HELPER_PARAM_ modrm, value, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED EMU86_EMULATE_HELPER_ATTR void
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_setmodrm_rmq))(EMU86_EMULATE_HELPER_ARGS_
                                                                                      struct emu86_modrm const *__restrict modrm,
                                                                                      u64 value, emu86_opflags_t op_flags) {
#ifndef EMU86_EMULATE_ONLY_MEMORY
	if (EMU86_MODRM_ISREG(modrm->mi_type)) {
		EMU86_SETREGQ(modrm->mi_rm, value);
	} else
#endif /* !EMU86_EMULATE_ONLY_MEMORY */
	{
		byte_t *addr;
		addr = EMU86_MODRM_MEMADDR(modrm, op_flags);
#if EMU86_EMULATE_CHECKUSER
		if (EMU86_ISUSER())
			EMU86_VALIDATE_WRITABLE(addr, 8);
#endif /* EMU86_EMULATE_CHECKUSER */
		EMU86_EMULATE_WRITEQ(addr, value);
	}
}
#endif /* !EMU86_SETMODRM_RMQ */
#endif /* CONFIG_LIBEMU86_WANT_64BIT */



/* Get/Set the R/M operand from a given modrm (when the modrm is known to be memory) */
#ifndef EMU86_EMULATE_ONLY_MEMORY
#ifndef EMU86_GETMODRM_RMMEMB
#define EMU86_GETMODRM_RMMEMB(modrm, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_getmodrm_rmmemb)(EMU86_EMULATE_HELPER_PARAM_ modrm, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED __ATTR_WUNUSED __ATTR_PURE EMU86_EMULATE_HELPER_ATTR u8
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_getmodrm_rmmemb))(EMU86_EMULATE_HELPER_ARGS_
                                                                                         struct emu86_modrm const *__restrict modrm,
                                                                                         emu86_opflags_t op_flags) {
	byte_t *addr;
	addr = EMU86_MODRM_MEMADDR(modrm, op_flags);
#if EMU86_EMULATE_CHECKUSER
	if (EMU86_ISUSER())
		EMU86_VALIDATE_READABLE(addr, 1);
#endif /* EMU86_EMULATE_CHECKUSER */
	return EMU86_EMULATE_READB(addr);
}
#endif /* !EMU86_GETMODRM_RMMEMB */

#ifndef EMU86_SETMODRM_RMMEMB
#define EMU86_SETMODRM_RMMEMB(modrm, value, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_setmodrm_rmmemb)(EMU86_EMULATE_HELPER_PARAM_ modrm, value, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED EMU86_EMULATE_HELPER_ATTR void
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_setmodrm_rmmemb))(EMU86_EMULATE_HELPER_ARGS_
                                                                                         struct emu86_modrm const *__restrict modrm,
                                                                                         u8 value, emu86_opflags_t op_flags) {
	byte_t *addr;
	addr = EMU86_MODRM_MEMADDR(modrm, op_flags);
#if EMU86_EMULATE_CHECKUSER
	if (EMU86_ISUSER())
		EMU86_VALIDATE_WRITABLE(addr, 1);
#endif /* EMU86_EMULATE_CHECKUSER */
	EMU86_EMULATE_WRITEB(addr, value);
}
#endif /* !EMU86_SETMODRM_RMMEMB */

#ifndef EMU86_GETMODRM_RMMEMW
#define EMU86_GETMODRM_RMMEMW(modrm, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_getmodrm_rmmemw)(EMU86_EMULATE_HELPER_PARAM_ modrm, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED __ATTR_WUNUSED __ATTR_PURE EMU86_EMULATE_HELPER_ATTR u16
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_getmodrm_rmmemw))(EMU86_EMULATE_HELPER_ARGS_
                                                                                         struct emu86_modrm const *__restrict modrm,
                                                                                         emu86_opflags_t op_flags) {
	byte_t *addr;
	addr = EMU86_MODRM_MEMADDR(modrm, op_flags);
#if EMU86_EMULATE_CHECKUSER
	if (EMU86_ISUSER())
		EMU86_VALIDATE_READABLE(addr, 2);
#endif /* EMU86_EMULATE_CHECKUSER */
	return EMU86_EMULATE_READW(addr);
}
#endif /* !EMU86_GETMODRM_RMMEMW */

#ifndef EMU86_SETMODRM_RMMEMW
#define EMU86_SETMODRM_RMMEMW(modrm, value, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_setmodrm_rmmemw)(EMU86_EMULATE_HELPER_PARAM_ modrm, value, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED EMU86_EMULATE_HELPER_ATTR void
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_setmodrm_rmmemw))(EMU86_EMULATE_HELPER_ARGS_
                                                                                         struct emu86_modrm const *__restrict modrm,
                                                                                         u16 value, emu86_opflags_t op_flags) {
	byte_t *addr;
	addr = EMU86_MODRM_MEMADDR(modrm, op_flags);
#if EMU86_EMULATE_CHECKUSER
	if (EMU86_ISUSER())
		EMU86_VALIDATE_WRITABLE(addr, 2);
#endif /* EMU86_EMULATE_CHECKUSER */
	EMU86_EMULATE_WRITEW(addr, value);
}
#endif /* !EMU86_SETMODRM_RMMEMW */

#ifndef EMU86_GETMODRM_RMMEML
#define EMU86_GETMODRM_RMMEML(modrm, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_getmodrm_rml)(EMU86_EMULATE_HELPER_PARAM_ modrm, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED __ATTR_WUNUSED __ATTR_PURE EMU86_EMULATE_HELPER_ATTR u32
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_getmodrm_rmmeml))(EMU86_EMULATE_HELPER_ARGS_
                                                                                         struct emu86_modrm const *__restrict modrm,
                                                                                         emu86_opflags_t op_flags) {
	byte_t *addr;
	addr = EMU86_MODRM_MEMADDR(modrm, op_flags);
#if EMU86_EMULATE_CHECKUSER
	if (EMU86_ISUSER())
		EMU86_VALIDATE_READABLE(addr, 4);
#endif /* EMU86_EMULATE_CHECKUSER */
	return EMU86_EMULATE_READL(addr);
}
#endif /* !EMU86_GETMODRM_RMMEML */

#ifndef EMU86_SETMODRM_RMMEML
#define EMU86_SETMODRM_RMMEML(modrm, value, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_setmodrm_rmmeml)(EMU86_EMULATE_HELPER_PARAM_ modrm, value, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED EMU86_EMULATE_HELPER_ATTR void
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_setmodrm_rmmeml))(EMU86_EMULATE_HELPER_ARGS_
                                                                                         struct emu86_modrm const *__restrict modrm,
                                                                                         u32 value, emu86_opflags_t op_flags) {
	byte_t *addr;
	addr = EMU86_MODRM_MEMADDR(modrm, op_flags);
#if EMU86_EMULATE_CHECKUSER
	if (EMU86_ISUSER())
		EMU86_VALIDATE_WRITABLE(addr, 4);
#endif /* EMU86_EMULATE_CHECKUSER */
	EMU86_EMULATE_WRITEL(addr, value);
}
#endif /* !EMU86_SETMODRM_RMMEML */

#if CONFIG_LIBEMU86_WANT_64BIT
#ifndef EMU86_GETMODRM_RMMEMQ
#define EMU86_GETMODRM_RMMEMQ(modrm, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_getmodrm_rmmemq)(EMU86_EMULATE_HELPER_PARAM_ modrm, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED __ATTR_WUNUSED __ATTR_PURE EMU86_EMULATE_HELPER_ATTR u64
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_getmodrm_rmmemq))(EMU86_EMULATE_HELPER_ARGS_
                                                                                         struct emu86_modrm const *__restrict modrm,
                                                                                         emu86_opflags_t op_flags) {
	byte_t *addr;
	addr = EMU86_MODRM_MEMADDR(modrm, op_flags);
#if EMU86_EMULATE_CHECKUSER
	if (EMU86_ISUSER())
		EMU86_VALIDATE_READABLE(addr, 8);
#endif /* EMU86_EMULATE_CHECKUSER */
	return EMU86_EMULATE_READQ(addr);
}
#endif /* !EMU86_GETMODRM_RMMEMQ */

#ifndef EMU86_SETMODRM_RMMEMQ
#define EMU86_SETMODRM_RMMEMQ(modrm, value, op_flags) \
	(EMU86_EMULATE_HELPER_NAME(emu86_setmodrm_rmmemq)(EMU86_EMULATE_HELPER_PARAM_ modrm, value, op_flags))
EMU86_EMULATE_HELPER_DECL __ATTR_UNUSED EMU86_EMULATE_HELPER_ATTR void
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(emu86_setmodrm_rmmemq))(EMU86_EMULATE_HELPER_ARGS_
                                                                                         struct emu86_modrm const *__restrict modrm,
                                                                                         u64 value, emu86_opflags_t op_flags) {
	byte_t *addr;
	addr = EMU86_MODRM_MEMADDR(modrm, op_flags);
#if EMU86_EMULATE_CHECKUSER
	if (EMU86_ISUSER())
		EMU86_VALIDATE_WRITABLE(addr, 8);
#endif /* EMU86_EMULATE_CHECKUSER */
	EMU86_EMULATE_WRITEQ(addr, value);
}
#endif /* !EMU86_SETMODRM_RMMEMQ */
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
#endif /* !EMU86_EMULATE_ONLY_MEMORY */



#ifdef __INTELLISENSE__
#ifndef EMU86_EMULATE_TRANSLATEADDR_IS_NOOP
#define _EMU86_INTELLISENSE_BEGIN_REAL_START_PC , *real_start_pc
#else /* !EMU86_EMULATE_TRANSLATEADDR_IS_NOOP */
#define _EMU86_INTELLISENSE_BEGIN_REAL_START_PC /* nothing */
#endif /* EMU86_EMULATE_TRANSLATEADDR_IS_NOOP */
#define EMU86_INTELLISENSE_BEGIN(name)                                                                \
	__DECL_BEGIN                                                                                      \
	EMU86_EMULATE_DECL EMU86_EMULATE_RETURN_TYPE                                                      \
	EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_HELPER_NAME(_i##name))(EMU86_EMULATE_ARGS) { \
		byte_t const *start_pc, *pc _EMU86_INTELLISENSE_BEGIN_REAL_START_PC;                          \
		u32 opcode;                                                                                   \
		emu86_opflags_t op_flags;                                                                     \
		struct emu86_modrm modrm;                                                                     \
		switch (opcode)
#define EMU86_INTELLISENSE_END \
done:                          \
done_dont_set_pc:              \
return_unknown_instruction:    \
		;                      \
	}                          \
	__DECL_END
#else /* __INTELLISENSE__ */
#define EMU86_INTELLISENSE_BEGIN(name) /* nothing */
#define EMU86_INTELLISENSE_END         /* nothing */
#endif /* !__INTELLISENSE__ */

EMU86_EMULATE_DECL EMU86_EMULATE_ATTR EMU86_EMULATE_RETURN_TYPE
EMU86_EMULATE_NOTHROW(EMU86_EMULATE_CC EMU86_EMULATE_NAME)(EMU86_EMULATE_ARGS) {
	EMU86_EMULATE_VARIABLES
#ifndef EMU86_EMULATE_TRANSLATEADDR_IS_NOOP
	byte_t const *real_start_pc;
#endif /* !EMU86_EMULATE_TRANSLATEADDR_IS_NOOP */
	byte_t const *start_pc, *pc;
	emu86_opflags_t op_flags;
	u32 opcode;
	EMU86_EMULATE_SETUP;
	op_flags = EMU86_EMULATE_GETOPFLAGS();
#ifdef EMU86_EMULATE_TRANSLATEADDR_IS_NOOP
	start_pc = (byte_t const *)EMU86_EMULATE_GETPC();
#else /* EMU86_EMULATE_TRANSLATEADDR_IS_NOOP */
	real_start_pc = (byte_t const *)EMU86_EMULATE_GETPC();
	start_pc      = (byte_t const *)EMU86_EMULATE_TRANSLATEADDR(real_start_pc);
#endif /* !EMU86_EMULATE_TRANSLATEADDR_IS_NOOP */
#ifdef EMU86_EMULATE_TRANSLATEADDR_IS_NOOP
#define REAL_START_IP() (uintptr_t)start_pc
#define REAL_IP()       (uintptr_t)pc
#else /* EMU86_EMULATE_TRANSLATEADDR_IS_NOOP */
#define REAL_START_IP() (uintptr_t)real_start_pc
#define REAL_IP()       (uintptr_t)(real_start_pc + (size_t)(pc - start_pc))
#endif /* !EMU86_EMULATE_TRANSLATEADDR_IS_NOOP */

#ifdef EMU86_EMULATE_TRY
	EMU86_EMULATE_TRY
#endif /* EMU86_EMULATE_TRY */
	{
		/* Decode the instruction */
#ifdef EMU86_EMULATE_TRY_DECODE
		EMU86_EMULATE_TRY_DECODE
#endif /* EMU86_EMULATE_TRY_DECODE */
		{
			pc = emu86_opcode_decode(start_pc, &opcode, &op_flags);
		}
#ifdef EMU86_EMULATE_EXCEPT_DECODE
		EMU86_EMULATE_EXCEPT_DECODE;
#endif /* EMU86_EMULATE_EXCEPT_DECODE */

		/* Execute the instruction */
#ifdef EMU86_EMULATE_TRY_SWITCH
		EMU86_EMULATE_TRY_SWITCH
#endif /* EMU86_EMULATE_TRY_SWITCH */
		{
			struct emu86_modrm modrm;
			switch (opcode) {

#if CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_16BIT
#define IF_16BIT_OR_32BIT(...) __VA_ARGS__
#else /* CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_16BIT */
#define IF_16BIT_OR_32BIT(...) /* nothing */
#endif /* !CONFIG_LIBEMU86_WANT_32BIT && !CONFIG_LIBEMU86_WANT_16BIT */


#if CONFIG_LIBEMU86_WANT_64BIT
#define IS_64BIT()    (op_flags & EMU86_F_REX_W)
#define IF_64BIT(...) __VA_ARGS__
#else /* CONFIG_LIBEMU86_WANT_64BIT */
#define IS_64BIT()    0
#define IF_64BIT(...) /* nothing */
#endif /* !CONFIG_LIBEMU86_WANT_64BIT */
#if CONFIG_LIBEMU86_WANT_16BIT
#define IS_16BIT() (EMU86_F_IS16(op_flags) ? (op_flags & EMU86_F_OP16) == 0 : (op_flags & EMU86_F_OP16) != 0)
#else /* CONFIG_LIBEMU86_WANT_16BIT */
#define IS_16BIT() (op_flags & EMU86_F_OP16)
#endif /* !CONFIG_LIBEMU86_WANT_16BIT */

#define MODRM_DECODE_MEMONLY()                         \
	do {                                               \
		pc = emu86_modrm_decode(pc, &modrm, op_flags); \
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))         \
			goto return_unknown_instruction;           \
	} __WHILE0
#ifdef EMU86_EMULATE_ONLY_MEMORY
#define MODRM_DECODE() \
	MODRM_DECODE_MEMONLY()
#else /* EMU86_EMULATE_ONLY_MEMORY */
#define MODRM_DECODE() \
	(pc = emu86_modrm_decode(pc, &modrm, op_flags))
#endif /* !EMU86_EMULATE_ONLY_MEMORY */

	/* Invoke all necessary callbacks for read/write access to memory
	 * who's address has been derived  */
#ifndef EMU86_READ_USER_MEMORY
#if EMU86_EMULATE_CHECKUSER
#define EMU86_READ_USER_MEMORY(addr, num_bytes)       \
	do {                                              \
		if (EMU86_ISUSER())                           \
			EMU86_VALIDATE_READABLE(addr, num_bytes); \
	} __WHILE0
#define EMU86_WRITE_USER_MEMORY(addr, num_bytes)      \
	do {                                              \
		if (EMU86_ISUSER())                           \
			EMU86_VALIDATE_WRITABLE(addr, num_bytes); \
	} __WHILE0
#else /* EMU86_EMULATE_CHECKUSER */
#define EMU86_READ_USER_MEMORY(addr, num_bytes)  (void)0
#define EMU86_WRITE_USER_MEMORY(addr, num_bytes) (void)0
#endif /* !EMU86_EMULATE_CHECKUSER */
#endif /* !EMU86_READ_USER_MEMORY */

#if CONFIG_LIBEMU86_WANT_64BIT
#define EMU86_UREG_TYPE u64
#define EMU86_SREG_TYPE s64
#else /* CONFIG_LIBEMU86_WANT_64BIT */
#define EMU86_UREG_TYPE u32
#define EMU86_SREG_TYPE s32
#endif /* !CONFIG_LIBEMU86_WANT_64BIT */


#ifdef EMU86_EMULATE_ONLY_MEMORY
#define IF_ONLY_MEMORY(...)  __VA_ARGS__
#define NIF_ONLY_MEMORY(...) /* nothing */
#else /* EMU86_EMULATE_ONLY_MEMORY */
#define IF_ONLY_MEMORY(...)  /* nothing */
#define NIF_ONLY_MEMORY(...) __VA_ARGS__
#endif /* !EMU86_EMULATE_ONLY_MEMORY */

#define MODRM_MEMADDR()           EMU86_MODRM_MEMADDR(&modrm, op_flags)
#define MODRM_MEMADDR_NOSEGBASE() EMU86_MODRM_MEMADDR_NOSEGBASE(&modrm, op_flags)
#define MODRM_GETRMB()   EMU86_GETMODRM_RMB(&modrm, op_flags)
#define MODRM_GETRMW()   EMU86_GETMODRM_RMW(&modrm, op_flags)
#define MODRM_GETRML()   EMU86_GETMODRM_RML(&modrm, op_flags)
#define MODRM_SETRMB(v)  EMU86_SETMODRM_RMB(&modrm, v, op_flags)
#define MODRM_SETRMW(v)  EMU86_SETMODRM_RMW(&modrm, v, op_flags)
#define MODRM_SETRML(v)  EMU86_SETMODRM_RML(&modrm, v, op_flags)
#if CONFIG_LIBEMU86_WANT_64BIT
#define MODRM_GETRMQ()   EMU86_GETMODRM_RMQ(&modrm, op_flags)
#define MODRM_SETRMQ(v)  EMU86_SETMODRM_RMQ(&modrm, v, op_flags)
#endif /* CONFIG_LIBEMU86_WANT_64BIT */

#ifdef EMU86_EMULATE_ONLY_MEMORY
#define MODRM_GETRMMEMB()   EMU86_GETMODRM_RMB(&modrm, op_flags)
#define MODRM_GETRMMEMW()   EMU86_GETMODRM_RMW(&modrm, op_flags)
#define MODRM_GETRMMEML()   EMU86_GETMODRM_RML(&modrm, op_flags)
#define MODRM_SETRMMEMB(v)  EMU86_SETMODRM_RMB(&modrm, v, op_flags)
#define MODRM_SETRMMEMW(v)  EMU86_SETMODRM_RMW(&modrm, v, op_flags)
#define MODRM_SETRMMEML(v)  EMU86_SETMODRM_RML(&modrm, v, op_flags)
#if CONFIG_LIBEMU86_WANT_64BIT
#define MODRM_GETRMMEMQ()   EMU86_GETMODRM_RMQ(&modrm, op_flags)
#define MODRM_SETRMMEMQ(v)  EMU86_SETMODRM_RMQ(&modrm, v, op_flags)
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
#else /* EMU86_EMULATE_ONLY_MEMORY */
#define MODRM_GETRMMEMB()   EMU86_GETMODRM_RMMEMB(&modrm, op_flags)
#define MODRM_GETRMMEMW()   EMU86_GETMODRM_RMMEMW(&modrm, op_flags)
#define MODRM_GETRMMEML()   EMU86_GETMODRM_RMMEML(&modrm, op_flags)
#define MODRM_SETRMMEMB(v)  EMU86_SETMODRM_RMMEMB(&modrm, v, op_flags)
#define MODRM_SETRMMEMW(v)  EMU86_SETMODRM_RMMEMW(&modrm, v, op_flags)
#define MODRM_SETRMMEML(v)  EMU86_SETMODRM_RMMEML(&modrm, v, op_flags)
#if CONFIG_LIBEMU86_WANT_64BIT
#define MODRM_GETRMMEMQ()   EMU86_GETMODRM_RMMEMQ(&modrm, op_flags)
#define MODRM_SETRMMEMQ(v)  EMU86_SETMODRM_RMMEMQ(&modrm, v, op_flags)
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
#endif /* !EMU86_EMULATE_ONLY_MEMORY */

#define MODRM_GETRMREGB()   EMU86_GETREGB(modrm.mi_rm, op_flags)
#define MODRM_GETRMREGW()   EMU86_GETREGW(modrm.mi_rm)
#define MODRM_GETRMREGL()   EMU86_GETREGL(modrm.mi_rm)
#define MODRM_SETRMREGB(v)  EMU86_SETREGB(modrm.mi_rm, v, op_flags)
#define MODRM_SETRMREGW(v)  EMU86_SETREGW(modrm.mi_rm, v)
#define MODRM_SETRMREGL(v)  EMU86_SETREGL(modrm.mi_rm, v)
#if CONFIG_LIBEMU86_WANT_64BIT
#define MODRM_GETRMREGQ()   EMU86_GETREGQ(modrm.mi_rm)
#define MODRM_SETRMREGQ(v)  EMU86_SETREGQ(modrm.mi_rm, v)
#endif /* CONFIG_LIBEMU86_WANT_64BIT */

#define MODRM_GETREGB()  EMU86_GETREGB(modrm.mi_reg, op_flags)
#define MODRM_GETREGW()  EMU86_GETREGW(modrm.mi_reg)
#define MODRM_GETREGL()  EMU86_GETREGL(modrm.mi_reg)
#define MODRM_SETREGB(v) EMU86_SETREGB(modrm.mi_reg, v, op_flags)
#define MODRM_SETREGW(v) EMU86_SETREGW(modrm.mi_reg, v)
#define MODRM_SETREGL(v) EMU86_SETREGL(modrm.mi_reg, v)
#if CONFIG_LIBEMU86_WANT_64BIT
#define MODRM_GETREGQ()  EMU86_GETREGQ(modrm.mi_reg)
#define MODRM_SETREGQ(v) EMU86_SETREGQ(modrm.mi_reg, v)
#endif /* CONFIG_LIBEMU86_WANT_64BIT */

#define VEX_GETREGB()  EMU86_GETREGB(EMU86_F_VEX_VVVVV(op_flags), op_flags)
#define VEX_GETREGW()  EMU86_GETREGW(EMU86_F_VEX_VVVVV(op_flags))
#define VEX_GETREGL()  EMU86_GETREGL(EMU86_F_VEX_VVVVV(op_flags))
#define VEX_SETREGB(v) EMU86_SETREGB(EMU86_F_VEX_VVVVV(op_flags), v, op_flags)
#define VEX_SETREGW(v) EMU86_SETREGW(EMU86_F_VEX_VVVVV(op_flags), v)
#define VEX_SETREGL(v) EMU86_SETREGL(EMU86_F_VEX_VVVVV(op_flags), v)
#if CONFIG_LIBEMU86_WANT_64BIT
#define VEX_GETREGQ()  EMU86_GETREGQ(EMU86_F_VEX_VVVVV(op_flags))
#define VEX_SETREGQ(v) EMU86_SETREGQ(EMU86_F_VEX_VVVVV(op_flags), v)
#endif /* CONFIG_LIBEMU86_WANT_64BIT */

#ifdef EMU86_GETSEGBASE_IS_NOOP_ALL
#define SEGMENT_ADDR2(segment_regno, offset) (byte_t *)(uintptr_t)(offset)
#define SEGMENT_ADDR(offset)                 (byte_t *)(uintptr_t)(offset)
#elif defined(EMU86_GETSEGBASE_IS_NOOP_ANY)
#define SEGMENT_ADDR2(segment_regno, offset) \
	(EMU86_GETSEGBASE_IS_NOOP(segment_regno) \
	 ? (byte_t *)(uintptr_t)(offset)         \
	 : (byte_t *)EMU86_SEGADDR((uintptr_t)EMU86_GETSEGBASE(segment_regno), (uintptr_t)(offset)))
#define SEGMENT_ADDR(offset) \
	SEGMENT_ADDR2(EMU86_F_SEGREG(op_flags), offset)
#else /* EMU86_GETSEGBASE_IS_NOOP */
#define SEGMENT_ADDR2(segment_regno, offset) \
	(byte_t *)EMU86_SEGADDR((uintptr_t)EMU86_GETSEGBASE(segment_regno), (uintptr_t)(offset))
#define SEGMENT_ADDR(offset) \
	SEGMENT_ADDR2(EMU86_F_SEGREG(op_flags), offset)
#endif /* !EMU86_GETSEGBASE_IS_NOOP */



#if CONFIG_LIBEMU86_WANT_64BIT && (CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT)
#define EMU86_ADDRSIZE_SWITCH(do64, do32, do16)                                                  \
	if (EMU86_F_IS64(op_flags) && !(op_flags & EMU86_F_67)) {                                    \
		/* 64-bit address size */                                                                \
		do64;                                                                                    \
	} else if ((EMU86_F_IS64(op_flags) || EMU86_F_IS16(op_flags)) ^ !!(op_flags & EMU86_F_67)) { \
		/* 32-bit address size */                                                                \
		do32;                                                                                    \
	} else {                                                                                     \
		/* 16-bit address size */                                                                \
		do16;                                                                                    \
	}
#elif !CONFIG_LIBEMU86_WANT_64BIT
#define EMU86_ADDRSIZE_SWITCH(do64, do32, do16)                 \
	if (!!EMU86_F_IS16(op_flags) ^ !!(op_flags & EMU86_F_67)) { \
		/* 32-bit address size */                               \
		do32;                                                   \
	} else {                                                    \
		/* 16-bit address size */                               \
		do16;                                                   \
	}
#elif CONFIG_LIBEMU86_WANT_64BIT && !(CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT)
#define EMU86_ADDRSIZE_SWITCH(do64, do32, do16)               \
	if (EMU86_F_IS64(op_flags) && !(op_flags & EMU86_F_67)) { \
		/* 64-bit address size */                             \
		do64;                                                 \
	} else {                                                  \
		/* 32-bit address size */                             \
		do32;                                                 \
	}
#else
#error "Invalid configuration"
#endif




		/* Pull in emulated instructions. */
#ifndef __INTELLISENSE__
#ifdef EMU86_EMULATE_IMPL_HEADER
/* Allow the user to specify a custom header that gets included for
 * the purpose of defining actually emulated instructions, thus
 * allowing the user to restrict the set of instructions being
 * emulated.
 * This is used by the KOS kernel #UD handler in order to emulate
 * certain instructions which may not be supported by the real host,
 * without pulling in a large number of instructions that are always
 * expected to have native support. */
#include EMU86_EMULATE_IMPL_HEADER
#else /* EMU86_EMULATE_IMPL_HEADER */
#include "emu/arith.c.inl"
#include "emu/arith2.c.inl"
#include "emu/bcd.c.inl"
#include "emu/bitscan.c.inl"
#include "emu/bittest.c.inl"
#include "emu/bound.c.inl"
#include "emu/calljmp.c.inl"
#include "emu/clisti.c.inl"
#include "emu/cmovcc.c.inl"
#include "emu/cmpxchg.c.inl"
#include "emu/cmpxchgb.c.inl"
#include "emu/flush.c.inl"
#include "emu/hlt.c.inl"
#include "emu/incdec.c.inl"
#include "emu/io.c.inl"
#include "emu/iret.c.inl"
#include "emu/lea.c.inl"
#include "emu/leave.c.inl"
#include "emu/misc.c.inl"
#include "emu/mov.c.inl"
#include "emu/nop.c.inl"
#include "emu/pushapopa.c.inl"
#include "emu/pushfpopf.c.inl"
#include "emu/pushpop.c.inl"
#include "emu/ret.c.inl"
#include "emu/shift.c.inl"
#include "emu/shift2.c.inl"
#include "emu/xadd.c.inl"
#include "emu/xchg.c.inl"
#endif /* !EMU86_EMULATE_IMPL_HEADER */
#endif /* !__INTELLISENSE__ */

			/* TODO: [rep] lods */
			/* TODO: [rep] movs */
			/* TODO: [rep] stos */
			/* TODO: [repe|repne] scas */
			/* TODO: [repe|repne] cmps */
			/* TODO: lret */
			/* TODO: enter */
			/* TODO: cpuid */
			/* TODO: arpl */
			/* TODO: jcc */
			/* TODO: cbw */
			/* TODO: cwd */
			/* TODO: cdq */
			/* TODO: sahf */
			/* TODO: lahf */
			/* TODO: int, int3, into, int1 */
			/* TODO: salc */
			/* TODO: xlatb */
			/* TODO: loop, loopz, loopnz */
			/* TODO: jcxz, jecxz, jrcxz */
			/* TODO: cmc */
			/* TODO: clc */
			/* TODO: stc */
			/* TODO: cld */
			/* TODO: std */
			/* TODO: sldt */
			/* TODO: str */
			/* TODO: lldt */
			/* TODO: ltr */
			/* TODO: verr */
			/* TODO: verw */
			/* TODO: sgdt */
			/* TODO: lgdt */
			/* TODO: smsw */
			/* TODO: lmsw */
			/* TODO: invlpg */
			/* TODO: swapgs */
			/* TODO: rdtscp */
			/* TODO: lar */
			/* TODO: lsl */
			/* TODO: syscall */
			/* TODO: clts */
			/* TODO: sysret */
			/* TODO: invd */
			/* TODO: wbinvd */
			/* TODO: cflsh */
			/* TODO: prefetchw */
			/* TODO: prefetchnta */
			/* TODO: prefetcht0 */
			/* TODO: prefetcht1 */
			/* TODO: prefetcht2 */
			/* TODO: cldemote */
			/* TODO: mov (%crN) */
			/* TODO: wrmsr */
			/* TODO: rdtsc */
			/* TODO: rdmsr */
			/* TODO: rdpmc */
			/* TODO: sysenter */
			/* TODO: sysexit */
			/* TODO: rdfsbase */
			/* TODO: rdgsbase */
			/* TODO: wrfsbase */
			/* TODO: wrgsbase */
			/* TODO: lfence */
			/* TODO: mfence */
			/* TODO: sfence */
			/* TODO: les */
			/* TODO: lds */
			/* TODO: lss */
			/* TODO: lfs */
			/* TODO: lgs */
			/* TODO: bswap */
			/* TODO: crc32 */
			/* TODO: movbe */
			/* TODO: popcnt */
			/* TODO: andn */
			/* TODO: blsr */
			/* TODO: blsmsk */
			/* TODO: blsi */
			/* TODO: bzhi */
			/* TODO: pext */
			/* TODO: pdep */
			/* TODO: adcx */
			/* TODO: adox */
			/* TODO: mulx */
			/* TODO: bextr */
			/* TODO: shlx */
			/* TODO: sarx */
			/* TODO: shrx */
			/* TODO: movdir64b */
			/* TODO: rorx */
			/* TODO: rdrand */
			/* TODO: rdseed */
			/* TODO: rdpid */


			default:
				goto return_unknown_instruction;
			}
		}
#ifdef EMU86_EMULATE_EXCEPT_SWITCH
		EMU86_EMULATE_EXCEPT_SWITCH;
#endif /* EMU86_EMULATE_EXCEPT_SWITCH */
	}
#ifdef EMU86_EMULATE_EXCEPT
	EMU86_EMULATE_EXCEPT;
#endif /* EMU86_EMULATE_EXCEPT */
done:
	/* Set the new instruction pointer. */
	EMU86_EMULATE_SETPC(REAL_IP());
done_dont_set_pc:
	EMU86_EMULATE_RETURN;
return_unknown_instruction:
	EMU86_EMULATE_RETURN_UNKNOWN_INSTRUCTION(REAL_START_IP(),
	                                         opcode,
	                                         op_flags);
#ifndef __INTELLISENSE__
#undef REAL_START_IP
#undef REAL_IP
#undef MODRM
#endif /* !__INTELLISENSE__ */
}

__DECL_END
