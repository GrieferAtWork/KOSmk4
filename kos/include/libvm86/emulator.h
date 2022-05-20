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
#ifndef _LIBVM86_EMULATOR_H
#define _LIBVM86_EMULATOR_H 1

#include "api.h"
#include <bits/types.h>

#if defined(__i386__) && !defined(__x86_64__)
#define LIBVM86_TRANSLATE_CC __ATTR_FASTCALL
#else /* __i386__ && !__x86_64__ */
#define LIBVM86_TRANSLATE_CC LIBVM86_CC
#endif /* !__i386__ || __x86_64__ */

__DECL_BEGIN

#define VM86_EFLAGS_CF          0x0001 /* [bit(0)] Carry Flag Status. */
#define VM86_EFLAGS_PF          0x0004 /* [bit(2)] Parity Flag Status. */
#define VM86_EFLAGS_AF          0x0010 /* [bit(4)] Auxiliary Carry Flag Status. */
#define VM86_EFLAGS_ZF          0x0040 /* [bit(6)] Zero Flag Status. */
#define VM86_EFLAGS_SF          0x0080 /* [bit(7)] Sign Flag Status. */
#define VM86_EFLAGS_TF          0x0100 /* [bit(8)] Trap Flag (System). */
#define VM86_EFLAGS_IF          0x0200 /* [bit(9)] Interrupt Enable Flag (System). */
#define VM86_EFLAGS_DF          0x0400 /* [bit(10)] Direction Flag (Control). */
#define VM86_EFLAGS_OF          0x0800 /* [bit(11)] Overflow Flag Status. */
#define VM86_EFLAGS_IOPL(n) (((n)&3) << 12)/* [bit(12,13)] I/O Privilege Level (System). */
#define VM86_EFLAGS_NT          0x4000 /* [bit(14)] Nested Task Flag (System). */

/* Encode/Decode a segmented address. */
#define VM86_ADDR(segment, offset) (((segment) << 4) + (offset))
#define VM86_ADDRSEG(addr)         ((__CCAST(__uintptr_t)(addr) & 0xf0000) >> 4)
#define VM86_ADDROFF(addr)         (__CCAST(__uintptr_t)(addr) & 0xffff)


#ifdef __CC__
#define VM86_REGISTER_GP(id)      \
	union {                       \
		__uint32_t vr_e##id##x;   \
		__uint16_t vr_##id##x;    \
		struct {                  \
			__uint8_t vr_##id##l; \
			__uint8_t vr_##id##h; \
		};                        \
	}
#define VM86_REGISTER_PT(id) \
	union {                  \
		__uint32_t vr_e##id; \
		__uint16_t vr_##id;  \
	}

typedef struct {
	union {
		struct {
			VM86_REGISTER_GP(a);     /* [C] Accumulator register */
			VM86_REGISTER_GP(c);     /* [C] Count register */
			VM86_REGISTER_GP(d);     /* [C] Data register */
			VM86_REGISTER_GP(b);     /* [P] Base register */
			VM86_REGISTER_PT(sp);    /* [P] Stack pointer */
			VM86_REGISTER_PT(bp);    /* [P] Frame base pointer */
			VM86_REGISTER_PT(si);    /* [P] Source pointer */
			VM86_REGISTER_PT(di);    /* [P] Destination pointer */
			VM86_REGISTER_PT(ip);    /* Instruction pointer. */
			VM86_REGISTER_PT(flags); /* Flags register. */
		};
		__uint8_t  vr_regdatab[40];
		__uint16_t vr_regdataw[20];
		__uint32_t vr_regdatal[10];
	};
	union {
		struct {
			__uint16_t    vr_es;     /* E (source) segment register */
			__uint16_t    vr_cs;     /* Code segment */
			__uint16_t    vr_ss;     /* Stack segment */
			__uint16_t    vr_ds;     /* D (destination) segment register */
			__uint16_t    vr_fs;     /* F segment register */
			__uint16_t    vr_gs;     /* G segment register */
		};
		__uint16_t vr_segments[6];
	};
	__uint32_t vr_cr2; /* %cr2 is writable in proper real-mode, but never written to by
	                    * the processor itself (since paging is disabled). As such, code
	                    * may still read/write it explicitly without any effect. */
	__uint32_t vr_cr3; /* Same as with %cr2. */
} vm86_registers_t;
#undef VM86_REGISTER_GP
#undef VM86_REGISTER_PT

typedef struct vm86_state_struct vm86_state_t;

/* Translate  a given linear  memory pointer `ptr' to
 * the real memory location where its data is stored.
 * The returned pointer should be usable for 1-15 byte reads and writes.
 * NOTE: This function is used to translate _any_ kind of pointer, including
 *       the instruction pointer itself, making it a very powerful  function
 *       (though also turning it into a potential bottleneck)
 *       One potential use of this function might be to virtually relocate VM86
 *       code away from the address space bottom, allowing real-mode code to be
 *       mapped anywhere in main memory.
 *       It would be ill advised if this function doesn't execute in O(1) */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) void *
(LIBVM86_TRANSLATE_CC *vm86_translate_t)(vm86_state_t *__restrict self, void *ptr);

/* Handle operations on unrecognized I/O ports, where `action' is one of `VM86_HANDLE_IO_*'
 * Note that certain ports  (mostly relating to  the PIC) are  emulated directly and  don't
 * cause this callback to be invoked.
 * @return: VM86_SUCCESS: Success.
 * @return: VM86_BADPORT: Bad port. */
typedef __ATTR_NONNULL_T((1, 4)) int
(LIBVM86_CC *vm86_handle_io_t)(vm86_state_t *__restrict self, __uint16_t port,
                               unsigned int action, void *__restrict data);
#define VM86_HANDLE_IO_INB  0 /* *(uint8_t *)data = inb(port); */
#define VM86_HANDLE_IO_INW  1 /* *(uint16_t *)data = inw(port); */
#define VM86_HANDLE_IO_INL  2 /* *(uint32_t *)data = inl(port); */
#define VM86_HANDLE_IO_OUTB 4 /* outb(port, *(uint8_t const *)data); */
#define VM86_HANDLE_IO_OUTW 5 /* outw(port, *(uint16_t const *)data); */
#define VM86_HANDLE_IO_OUTL 6 /* outl(port, *(uint32_t const *)data); */
#define VM86_HANDLE_IO_ISIN(x)  (((x) & 4) == 0)
#define VM86_HANDLE_IO_ISOUT(x) (((x) & 4) != 0)

/* Handle an interrupt by updating `self->vr_regs' to load the associated interrupt handler. */
typedef __ATTR_NONNULL_T((1)) void
(LIBVM86_CC *vm86_handle_intr_t)(vm86_state_t *__restrict self, __uint8_t intno);
#endif /* __CC__ */

#ifdef __CC__
struct vm86_state_struct {
	vm86_registers_t   vr_regs;  /* Register state. */
	vm86_translate_t   vr_trans; /* [0..1][const] Translate address (or NULL for 1-on-1 translation). */
	vm86_handle_io_t   vr_io;    /* [0..1][const] I/O handler (or NULL to make undefined I/O illegal). */
	vm86_handle_intr_t vr_intr;  /* [0..1][const] Interrupt handling (or NULL to read from an IDT stored at address 0) */
};

/* realmode/vm86 is _always_ constrained to 0xffff register offsets.
 * s.a.          `https://wiki.osdev.org/Real_Mode#Addressing_Modes' */
#define vm86_state_canpush(self, num_bytes) ((self)->vr_regs.vr_sp < (__uint16_t)((__uint16_t)0-(num_bytes)))
#define vm86_state_canpop(self, num_bytes)  ((self)->vr_regs.vr_sp >= (__uint16_t)(num_bytes))
#define vm86_state_sp(self)  VM86_ADDR((self)->vr_regs.vr_ss, (self)->vr_regs.vr_sp)
#define vm86_state_si(self)  VM86_ADDR((self)->vr_regs.vr_ds, (self)->vr_regs.vr_si)
#define vm86_state_di(self)  VM86_ADDR((self)->vr_regs.vr_es, (self)->vr_regs.vr_di)
#define vm86_state_ip(self)  VM86_ADDR((self)->vr_regs.vr_cs, (self)->vr_regs.vr_ip)

#endif /* __CC__ */


#define VM86_SUCCESS         0  /* Success */
#define VM86_HALTED          1  /* Emulation was halted by `hlt' with #IF set */
#define VM86_STOPPED         2  /* Emulation returned gracefully (by jumping to 0xffff:0xffff) */
#define VM86_INTR_ENABLED   99  /* Success (interrupts were re-enabled but shouldn't be checked until after the next instruction) */
#define VM86_FROZEN        (-1) /* Emulation was frozen by `hlt' without #IF set */
#define VM86_DOUBLE_FAULT  (-2) /* A double fault was caused. */
#define VM86_SEGFAULT      (-3) /* Segmentation fault. (or more specifically:  #PF)
                                 * Because that exception didn't exist in realmode,
                                 * it's handled as a fatal error. */
#define VM86_BADPORT       (-4) /* Attempted to access an invalid port. */

#ifdef __CC__
/* Emulate a single instruction and update the program counter to point
 * to the next instruction.
 *  - In the case of string instructions, execute a single loop and place
 *    the program counter back at the start after updating loop counters.
 *  - This function does not check for pending interrupts prior to execution
 *    of any single instruction.
 *  - When `VM86_FROZEN' is returned, the program counter is also reset to
 *    the start of the responsible instruction.
 * @return: VM86_SUCCESS:      The single instruction was successfully executed.
 * @return: VM86_STOPPED:      The program counter was already placed at 0xffff:0xffff, or has jumped to that location.
 * @return: VM86_INTR_ENABLED: Interrupts should be enabled after the next call to `vm86_step()'
 * @return: * :                One of `VM86_*' */
typedef __ATTR_NONNULL_T((1)) int
(LIBVM86_CC *PVM86_STEP)(vm86_state_t *__restrict self);
#ifdef LIBVM86_WANT_PROTOTYPES
LIBVM86_DECL __ATTR_NONNULL((1)) int LIBVM86_CC
vm86_step(vm86_state_t *__restrict self);
#endif /* LIBVM86_WANT_PROTOTYPES */

/* Execute VM86 emulator code until that code finishes execution. */
typedef __ATTR_NONNULL_T((1)) int
(LIBVM86_CC *PVM86_EXEC)(vm86_state_t *__restrict self);
#ifdef LIBVM86_WANT_PROTOTYPES
LIBVM86_DECL __ATTR_NONNULL((1)) int LIBVM86_CC
vm86_exec(vm86_state_t *__restrict self);
#endif /* LIBVM86_WANT_PROTOTYPES */

/* Trigger an interrupt.
 * @return: VM86_SUCCESS:      Success.
 * @return: VM86_DOUBLE_FAULT: Stack overflow.
 * @return: VM86_SEGFAULT:     Segmentation fault. */
typedef __ATTR_NONNULL_T((1)) int (LIBVM86_CC *PVM86_INTR)(vm86_state_t *__restrict self, __uint8_t intno);
#ifdef LIBVM86_WANT_PROTOTYPES
LIBVM86_DECL __ATTR_NONNULL((1)) int LIBVM86_CC vm86_intr(vm86_state_t *__restrict self, __uint8_t intno);
#endif /* LIBVM86_WANT_PROTOTYPES */

/* Read/Write values to/from an emulated IO port.
 * @return: VM86_SUCCESS: Success.
 * @return: VM86_BADPORT: Bad port. */
typedef __ATTR_NONNULL_T((1, 3)) int (LIBVM86_CC *PVM86_INB)(vm86_state_t *__restrict self, __uint16_t port, __uint8_t *__restrict presult);
typedef __ATTR_NONNULL_T((1, 3)) int (LIBVM86_CC *PVM86_INW)(vm86_state_t *__restrict self, __uint16_t port, __uint16_t *__restrict presult);
typedef __ATTR_NONNULL_T((1, 3)) int (LIBVM86_CC *PVM86_INL)(vm86_state_t *__restrict self, __uint16_t port, __uint32_t *__restrict presult);
typedef __ATTR_NONNULL_T((1)) int (LIBVM86_CC *PVM86_OUTB)(vm86_state_t *__restrict self, __uint16_t port, __uint8_t value);
typedef __ATTR_NONNULL_T((1)) int (LIBVM86_CC *PVM86_OUTW)(vm86_state_t *__restrict self, __uint16_t port, __uint16_t value);
typedef __ATTR_NONNULL_T((1)) int (LIBVM86_CC *PVM86_OUTL)(vm86_state_t *__restrict self, __uint16_t port, __uint32_t value);
#ifdef LIBVM86_WANT_PROTOTYPES
LIBVM86_DECL __ATTR_NONNULL((1, 3)) int LIBVM86_CC vm86_inb(vm86_state_t *__restrict self, __uint16_t port, __uint8_t *__restrict presult);
LIBVM86_DECL __ATTR_NONNULL((1, 3)) int LIBVM86_CC vm86_inw(vm86_state_t *__restrict self, __uint16_t port, __uint16_t *__restrict presult);
LIBVM86_DECL __ATTR_NONNULL((1, 3)) int LIBVM86_CC vm86_inl(vm86_state_t *__restrict self, __uint16_t port, __uint32_t *__restrict presult);
LIBVM86_DECL __ATTR_NONNULL((1)) int LIBVM86_CC vm86_outb(vm86_state_t *__restrict self, __uint16_t port, __uint8_t value);
LIBVM86_DECL __ATTR_NONNULL((1)) int LIBVM86_CC vm86_outw(vm86_state_t *__restrict self, __uint16_t port, __uint16_t value);
LIBVM86_DECL __ATTR_NONNULL((1)) int LIBVM86_CC vm86_outl(vm86_state_t *__restrict self, __uint16_t port, __uint32_t value);
#endif /* LIBVM86_WANT_PROTOTYPES */

#endif /* __CC__ */


__DECL_END

#endif /* !_LIBVM86_EMULATOR_H */
