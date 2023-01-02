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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_EMULOCK_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_EMULOCK_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>

#ifdef __x86_64__
#define ARCH_X86_HAVE_EMULOCK_CMPXCHX 1
/* No need to emulate 8-64 bit atomics on x86_64 */
#else /* __x86_64__ */
#define ARCH_X86_HAVE_EMULOCK_CMPXCHB 1
#define ARCH_X86_HAVE_EMULOCK_CMPXCHW 1
#define ARCH_X86_HAVE_EMULOCK_CMPXCHL 1
#define ARCH_X86_HAVE_EMULOCK_CMPXCHQ 1
/* No 16-byte atomic instruction exists on i386, so no need to emulate one! */
#endif /* !__x86_64__ */


#undef ARCH_X86_HAVE_EMULOCK
#if (defined(ARCH_X86_HAVE_EMULOCK_CMPXCHB) || \
     defined(ARCH_X86_HAVE_EMULOCK_CMPXCHW) || \
     defined(ARCH_X86_HAVE_EMULOCK_CMPXCHL) || \
     defined(ARCH_X86_HAVE_EMULOCK_CMPXCHQ) || \
     defined(ARCH_X86_HAVE_EMULOCK_CMPXCHX))
#define ARCH_X86_HAVE_EMULOCK 1
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCH... */

#ifdef ARCH_X86_HAVE_EMULOCK_CMPXCHX
#include <int128.h>
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCHX */

#ifdef __CC__
#ifdef ARCH_X86_HAVE_EMULOCK
DECL_BEGIN

/* Definitions for emulating lock-prefixed instructions in software
 * Mainly intended to be used  when the hardware doesn't lock  some
 * specific lock instruction, at which  point we'll try to  emulate
 * it  in  software  (mainly  effects  `cmpxchg8b'  on  i386,   and
 * `cmpxchg16b' on x86_64)
 * NOTE: The  given `pstate' is used if the behavior is emulated using
 *       a VIO operation, as well as a descriptor for figuring out how
 *       exactly an E_SEGFAULT exception should be thrown (if any) */

struct icpustate;

#ifdef ARCH_X86_HAVE_EMULOCK_CMPXCHB
FUNDEF u8 KCALL
x86_emulock_cmpxchb(struct icpustate **__restrict pstate,
                    USER CHECKED u8 *addr, u8 oldval, u8 newval);
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCHB */

#ifdef ARCH_X86_HAVE_EMULOCK_CMPXCHW
FUNDEF u16 KCALL
x86_emulock_cmpxchw(struct icpustate **__restrict pstate,
                    USER CHECKED u16 *addr, u16 oldval, u16 newval);
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCHW */

#ifdef ARCH_X86_HAVE_EMULOCK_CMPXCHL
FUNDEF u32 KCALL
x86_emulock_cmpxchl(struct icpustate **__restrict pstate,
                    USER CHECKED u32 *addr, u32 oldval, u32 newval);
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCHL */

#ifdef ARCH_X86_HAVE_EMULOCK_CMPXCHQ
FUNDEF u64 KCALL
x86_emulock_cmpxchq(struct icpustate **__restrict pstate,
                    USER CHECKED u64 *addr, u64 oldval, u64 newval);
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCHQ */

#ifdef ARCH_X86_HAVE_EMULOCK_CMPXCHX
FUNDEF uint128_t KCALL
x86_emulock_cmpxchx(struct icpustate **__restrict pstate,
                    USER CHECKED uint128_t *addr,
                    uint128_t oldval,
                    uint128_t newval);
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCHX */

DECL_END
#endif /* ARCH_X86_HAVE_EMULOCK */
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_EMULOCK_H */
