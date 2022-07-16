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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_ATOMIC64_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_ATOMIC64_H 1

#include <kernel/compiler.h>
#include <hybrid/host.h>

#undef ARCH_HAVE_ATOMIC64_SUPPORT_NEVER
#undef ARCH_HAVE_ATOMIC64_SUPPORT_ALWAYS
#undef ARCH_HAVE_ATOMIC64_SUPPORT_DYNAMIC

#ifdef __x86_64__
#define ARCH_HAVE_ATOMIC64_SUPPORT_ALWAYS /* There always is an instruction `cmpxchgq' */
#else /* __x86_64__ */
#define ARCH_HAVE_ATOMIC64_SUPPORT_DYNAMIC /* Dynamically determine support for `cmpxchg8b' */

#include <kernel/types.h>

#define ARCH_HAVE_ATOMIC64_PROTOTYPES
#ifdef __CC__
DECL_BEGIN

#ifdef __atomic64_t_defined
#error "atomic64_t already defined"
#endif /* __atomic64_t_defined */

#define __atomic64_t_defined
#ifdef __INTELLISENSE__
typedef struct {
	u64 _a_val;
} atomic64_t;
#define _atomic64_val(self) (self)._a_val
#define ATOMIC64_INIT(v) { v }
#else /* __INTELLISENSE__ */
typedef u64 atomic64_t;
#define _atomic64_val(self) self
#define ATOMIC64_INIT(v) v
#endif /* !__INTELLISENSE__ */

#define atomic64_init(self, v) (void)(_atomic64_val(*(self)) = (v))
#define atomic64_cinit(self, v)                     \
	(__hybrid_assert(_atomic64_val(*(self)) == 0), \
	 (__builtin_constant_p(v) && (v) == 0)          \
	 ? (void)0                                      \
	 : (void)(_atomic64_val(*(self)) = (v)))


/* Atomically read a 64-bit data word from `self' */
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL ATTR_PURE WUNUSED NONNULL((1)) u64
NOTHROW(atomic64_read)(atomic64_t const *__restrict self) {
	__register u64 __eax_edx;
	__register u32 __ecx, __ebx;
	/* >> __i386_atomic64_read
	 * IN:      %edi = (atomic64_t *)self
	 * OUT:     %eax = (u32)(RETURN & 0xffffffff)
	 *          %edx = (u32)(RETURN & 0xffffffff00000000) >> 32
	 * CLOBBER: %eflags, %ebx, %ecx */
	__asm__("call __i386_atomic64_read"
	        : "=A" (__eax_edx)
	        , "=&c" (__ecx)
	        , "=&b" (__ebx)
	        : "D" (self)
	        , "m" (_atomic64_val(*self))
	        : "cc");
	return __eax_edx;
}

/* Atomically write a 64-bit data word to `self' */
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL NONNULL((1)) void
NOTHROW(atomic64_write)(atomic64_t *__restrict self, u64 value) {
	__register u32 __eax;
	__register u32 __edx;
	/* >> __i386_atomic64_write
	 * IN:      %edi = (atomic64_t *)self
	 *          %ebx = (u32)(value & 0xffffffff)
	 *          %ecx = (u32)(value & 0xffffffff00000000) >> 32
	 * OUT:     -
	 * CLOBBER: %eflags, %eax, %edx */
	__asm__("call __i386_atomic64_write"
	        : "=&a" (__eax)
	        , "=&d" (__edx)
	        , "=m" (_atomic64_val(*self))
	        : "D" (self)
	        , "b" ((u32)(value))
	        , "c" ((u32)(value >> 32))
	        : "cc");
}

/* Atomically compare-exchange a 64-bit data word from `self' */
#ifdef __OPTIMIZE__
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL NONNULL((1)) u64
NOTHROW(atomic64_cmpxch_val)(atomic64_t *__restrict self,
                             u64 oldval, u64 newval) {
	/* >> __i386_atomic64_cmpxch
	 * IN:      %edi = (atomic64_t *)self
	 *          %eax = (u32)(oldval & 0x00000000ffffffff)
	 *          %edx = (u32)(oldval & 0xffffffff00000000) >> 32
	 *          %ebx = (u32)(newval & 0x00000000ffffffff)
	 *          %ecx = (u32)(newval & 0xffffffff00000000) >> 32
	 * OUT:     %eax = (u32)(REAL_OLD_VALUE & 0x00000000ffffffff)
	 *          %edx = (u32)(REAL_OLD_VALUE & 0xffffffff00000000) >> 32
	 *          %eflags.ZF = (REAL_OLD_VALUE == oldval) ? 1 : 0
	 * CLOBBER: %eflags\ZF */
	__register u64 __eax_edx;
	__asm__("call __i386_atomic64_cmpxch"
	        : "=A" (__eax_edx)
	        , "+m" (_atomic64_val(*self))
	        : "D" (self)
	        , "0" (oldval)
	        , "b" ((u32)(newval))
	        , "c" ((u32)(newval >> 32))
	        : "cc");
	return __eax_edx;
}
#else /* __OPTIMIZE__ */
/* Because gcc refuses to properly compile the inline-assembly wrappers
 * when not  building  with  __OPTIMIZE__,  we need  to  link  a  C-ABI
 * compatible wrapper instead. (ugh...) */
FUNDEF NOBLOCK NONNULL((1)) u64
NOTHROW(KCALL atomic64_cmpxch_val)(atomic64_t *__restrict self,
                                   u64 oldval, u64 newval);
#endif /* !__OPTIMIZE__ */

/* Atomically compare-exchange a 64-bit data word from `self' */
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL NONNULL((1)) __BOOL
NOTHROW(atomic64_cmpxch)(atomic64_t *__restrict self,
                         u64 oldval, u64 newval) {
	/* >> __i386_atomic64_cmpxch
	 * IN:      %edi = (atomic64_t *)self
	 *          %eax = (u32)(oldval & 0x00000000ffffffff)
	 *          %edx = (u32)(oldval & 0xffffffff00000000) >> 32
	 *          %ebx = (u32)(newval & 0x00000000ffffffff)
	 *          %ecx = (u32)(newval & 0xffffffff00000000) >> 32
	 * OUT:     %eax = (u32)(REAL_OLD_VALUE & 0x00000000ffffffff)
	 *          %edx = (u32)(REAL_OLD_VALUE & 0xffffffff00000000) >> 32
	 *          %eflags.ZF = (REAL_OLD_VALUE == oldval) ? 1 : 0
	 * CLOBBER: %eflags\ZF */
	__register u64 __eax_edx;
	__BOOL __res;
#ifdef __OPTIMIZE__
	__asm__("call __i386_atomic64_cmpxch"
	        : "=A" (__eax_edx)
	        , "=@cce" (__res)
	        , "+m" (_atomic64_val(*self))
	        : "D" (self)
	        , "0" (oldval)
	        , "b" ((u32)(newval))
	        , "c" ((u32)(newval >> 32))
	        : "cc");
#else /* __OPTIMIZE__ */
	__eax_edx = atomic64_cmpxch_val(self, oldval, newval);
	__res     = __eax_edx == oldval;
#endif /* !__OPTIMIZE__ */
	return __res;
}

/* Atomically exchange a 64-bit data word from `self' */
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL NONNULL((1)) u64
NOTHROW(atomic64_xch)(atomic64_t *__restrict self,
                      u64 addend) {
	__register u64 __eax_edx;
	/* >> __i386_atomic64_xch
	 * IN:      %edi = (atomic64_t *)self
	 *          %ebx = (u32)(addend & 0xffffffff)
	 *          %ecx = (u32)(addend & 0xffffffff00000000) >> 32
	 * OUT:     %eax = (u32)(oldval & 0x00000000ffffffff)
	 *          %edx = (u32)(oldval & 0xffffffff00000000) >> 32
	 * CLOBBER: %eflags */
	__asm__("call __i386_atomic64_xch"
	        : "=A" (__eax_edx)
	        , "+m" (_atomic64_val(*self))
	        : "D" (self)
	        , "b" ((u32)(addend))
	        , "c" ((u32)(addend >> 32))
	        : "cc");
	return __eax_edx;
}

/* Atomically fetch-and-add a 64-bit data word from `self' */
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL NONNULL((1)) u64
NOTHROW(atomic64_fetchadd)(atomic64_t *__restrict self,
                           u64 addend) {
	__register u64 __eax_edx;
	__register u32 __ebx;
	__register u32 __ecx;
	/* >> __i386_atomic64_fetchadd
	 * IN:      %edi = (atomic64_t *)self
	 *          %ebx = (u32)(addend & 0xffffffff)
	 *          %ecx = (u32)(addend & 0xffffffff00000000) >> 32
	 * OUT:     %eax = (u32)(oldval & 0x00000000ffffffff)
	 *          %edx = (u32)(oldval & 0xffffffff00000000) >> 32
	 * CLOBBER: %eflags, %ebx, %ecx */
	__asm__("call __i386_atomic64_fetchadd"
	        : "=A" (__eax_edx)
	        , "=&b" (__ebx)
	        , "=&c" (__ecx)
	        , "+m" (_atomic64_val(*self))
	        : "D" (self)
	        , "1" ((u32)(addend))
	        , "2" ((u32)(addend >> 32))
	        : "cc");
	return __eax_edx;
}

/* Atomically fetch-and-and a 64-bit data word from `self' */
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL NONNULL((1)) u64
NOTHROW(atomic64_fetchand)(atomic64_t *__restrict self,
                           u64 addend) {
	__register u64 __eax_edx;
	__register u32 __ebx;
	__register u32 __ecx;
	/* >> __i386_atomic64_fetchand
	 * IN:      %edi = (atomic64_t *)self
	 *          %ebx = (u32)(addend & 0xffffffff)
	 *          %ecx = (u32)(addend & 0xffffffff00000000) >> 32
	 * OUT:     %eax = (u32)(oldval & 0x00000000ffffffff)
	 *          %edx = (u32)(oldval & 0xffffffff00000000) >> 32
	 * CLOBBER: %eflags, %ebx, %ecx */
	__asm__("call __i386_atomic64_fetchand"
	        : "=A" (__eax_edx)
	        , "=&b" (__ebx)
	        , "=&c" (__ecx)
	        , "+m" (_atomic64_val(*self))
	        : "D" (self)
	        , "1" ((u32)(addend))
	        , "2" ((u32)(addend >> 32))
	        : "cc");
	return __eax_edx;
}

/* Atomically fetch-and-or a 64-bit data word from `self' */
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL NONNULL((1)) u64
NOTHROW(atomic64_fetchor)(atomic64_t *__restrict self,
                          u64 addend) {
	__register u64 __eax_edx;
	__register u32 __ebx;
	__register u32 __ecx;
	/* >> __i386_atomic64_fetchor
	 * IN:      %edi = (atomic64_t *)self
	 *          %ebx = (u32)(addend & 0xffffffff)
	 *          %ecx = (u32)(addend & 0xffffffff00000000) >> 32
	 * OUT:     %eax = (u32)(oldval & 0x00000000ffffffff)
	 *          %edx = (u32)(oldval & 0xffffffff00000000) >> 32
	 * CLOBBER: %eflags, %ebx, %ecx */
	__asm__("call __i386_atomic64_fetchor"
	        : "=A" (__eax_edx)
	        , "=&b" (__ebx)
	        , "=&c" (__ecx)
	        , "+m" (_atomic64_val(*self))
	        : "D" (self)
	        , "1" ((u32)(addend))
	        , "2" ((u32)(addend >> 32))
	        : "cc");
	return __eax_edx;
}

/* Atomically fetch-and-xor a 64-bit data word from `self' */
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL NONNULL((1)) u64
NOTHROW(atomic64_fetchxor)(atomic64_t *__restrict self,
                           u64 addend) {
	__register u64 __eax_edx;
	__register u32 __ebx;
	__register u32 __ecx;
	/* >> __i386_atomic64_fetchxor
	 * IN:      %edi = (atomic64_t *)self
	 *          %ebx = (u32)(addend & 0xffffffff)
	 *          %ecx = (u32)(addend & 0xffffffff00000000) >> 32
	 * OUT:     %eax = (u32)(oldval & 0x00000000ffffffff)
	 *          %edx = (u32)(oldval & 0xffffffff00000000) >> 32
	 * CLOBBER: %eflags, %ebx, %ecx */
	__asm__("call __i386_atomic64_fetchxor"
	        : "=A" (__eax_edx)
	        , "=&b" (__ebx)
	        , "=&c" (__ecx)
	        , "+m" (_atomic64_val(*self))
	        : "D" (self)
	        , "1" ((u32)(addend))
	        , "2" ((u32)(addend >> 32))
	        : "cc");
	return __eax_edx;
}

#define atomic64_add(self, value) (void)atomic64_fetchadd(self, value)
#define atomic64_and(self, value) (void)atomic64_fetchand(self, value)
#define atomic64_or(self, value)  (void)atomic64_fetchor(self, value)
#define atomic64_xor(self, value) (void)atomic64_fetchxor(self, value)
#define atomic64_cmpxch_weak      atomic64_cmpxch

DECL_END
#endif /* __CC__ */
#endif /* !__x86_64__ */


#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_ATOMIC64_H */
