/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBVM86_EMULATOR_H
#define _LIBVM86_EMULATOR_H 1

#include "api.h"
#include <bits/types.h>

#if defined(__i386__) && !defined(__x86_64__)
#define LIBVM86_TRANSLATE_CC  __ATTR_FASTCALL
#else
#define LIBVM86_TRANSLATE_CC  LIBVM86_CC
#endif

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


#define VM86_ADDR(segment,offset) (((segment) << 4) + (offset))


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
	__uint16_t    vr_es;     /* E (source) segment register */
	__uint16_t    vr_cs;     /* Code segment */
	__uint16_t    vr_ss;     /* Stack segment */
	__uint16_t    vr_ds;     /* D (destination) segment register */
	__uint16_t    vr_fs;     /* F segment register */
	__uint16_t    vr_gs;     /* G segment register */
} vm86_registers_t;
#undef VM86_REGISTER_GP
#undef VM86_REGISTER_PT

typedef struct vm86_state_struct vm86_state_t;

/* Translate a given linear memory pointer `ptr' to
 * the real memory location where its data is stored.
 * The returned pointer should be usable for 1-15 byte reads and writes.
 * NOTE: This function is used to translate _any_ kind of pointer, including
 *       the instruction pointer itself, making it a very powerful function
 *       (though also turning it into a potential bottleneck)
 *       One potential use of this function might be to virtually relocate VM86
 *       code away from the address space bottom, allowing real-mode code to be
 *       mapped anywhere in main memory. */
typedef void *(LIBVM86_TRANSLATE_CC *vm86_translate_t)(vm86_state_t *__restrict self, void *ptr);

/* Handle operations on unrecognized I/O ports, where `action' is one of `VM86_HANDLE_IO_*'
 * Note that certain ports (mostly relating to the PIC) are emulated directly and don't
 * cause this callback to be invoked.
 * @return: VM86_SUCCESS: Success.
 * @return: VM86_BADPORT: Bad port. */
typedef int (LIBVM86_CC *vm86_handle_io_t)(vm86_state_t *__restrict self, __uint16_t port,
                                           unsigned int action, void *data);
#define VM86_HANDLE_IO_INB  0 /* *(uint8_t *)data = inb(port); */
#define VM86_HANDLE_IO_INW  1 /* *(uint16_t *)data = inw(port); */
#define VM86_HANDLE_IO_INL  2 /* *(uint32_t *)data = inl(port); */
#define VM86_HANDLE_IO_OUTB 4 /* outb(port,*(uint8_t *)data); */
#define VM86_HANDLE_IO_OUTW 5 /* outw(port,*(uint16_t *)data); */
#define VM86_HANDLE_IO_OUTL 6 /* outl(port,*(uint32_t *)data); */
#define VM86_HANDLE_IO_ISIN(x)  (!((x) & 4))
#define VM86_HANDLE_IO_ISOUT(x)   ((x) & 4)

/* Handle an interrupt by updating `self->vr_regs' to load the associated interrupt handler. */
typedef void (LIBVM86_CC *vm86_handle_intr_t)(vm86_state_t *__restrict self, __uint8_t intno);
#endif /* __CC__ */

#define VM86_STATE_FNORMAL 0x0000
#define VM86_STATE_FINTR   0x0001 /* There are pending interrupts */

#define VM86_PIC_FNORMAL        0x00
#define VM86_PIC_FAUTOEOI       0x01 /* Automatically acknowledge interrupts. */
#define VM86_PIC_FNEEDEOI       0x02 /* End-of-interrupt needs to be acknowledged. */
#define VM86_PIC_STATEMASK      0xf0 /* Mask for the current state of the PIC */
#define VM86_PIC_STATESHIFT        4 /* Shift for the current state of the PIC */
#define VM86_PIC_STATE_RUNNING  0x00 /* The PIC is fully initialized and running. */
#define VM86_PIC_STATE_WORD2    0x01 /* Initialization word #2 is expected. */
#define VM86_PIC_STATE_WORD3    0x02 /* Initialization word #3 is expected. */
#define VM86_PIC_STATE_WORD4    0x03 /* Initialization word #4 is expected. */
#define VM86_PIC_STATE_WORD2_N4 0x04 /* Initialization word #2 is expected (skip word #4). */
#define VM86_PIC_STATE_WORD3_N4 0x05 /* Initialization word #3 is expected (skip word #4). */

#ifdef __CC__
struct vm86_state_struct {
	vm86_registers_t   vr_regs;      /* Register state. */
	vm86_translate_t   vr_trans;     /* [0..1][const] Translate address (or NULL for 1-on-1 translation). */
	vm86_handle_io_t   vr_io;        /* [0..1][const] I/O handler (or NULL to make undefined I/O illegal). */
	vm86_handle_intr_t vr_intr;      /* [0..1][const] Interrupt handling (or NULL to read from an IDT stored at address 0) */
	__uintptr_t        vr_intr_pending[256/(sizeof(__uintptr_t)*8)]; /* Bitset of pending interrupts */
	__uintptr_t        vr_stateflags;/* State flags (Set of VM86_STATE_F*) */
	__uint8_t          vr_pic1_base; /* Base address of the PIC#1 (Defaults to `0x08') */
	__uint8_t          vr_pic1_mode; /* PIC#1 executino mode (set of `VM86_PIC_F*') */
	__uint8_t          vr_pic1_mask; /* Mask of pending PIC#1 interrupts */
	__uint8_t          vr_pic1_ignr; /* Mask of disabled PIC#1 interrupts. */
	__uint8_t          vr_pic2_base; /* Base address of the PIC#2 (Defaults to `0x70') */
	__uint8_t          vr_pic2_mode; /* PIC#2 executino mode (set of `VM86_PIC_F*') */
	__uint8_t          vr_pic2_mask; /* Mask of pending PIC#2 interrupts */
	__uint8_t          vr_pic2_ignr; /* Mask of disabled PIC#2 interrupts. */
};

/* realmode/vm86 is _always_ constrained to 0xffff register offsets.
 * s.a. `https://wiki.osdev.org/Real_Mode#Addressing_Modes' */
#define vm86_state_hasstack(self, num_bytes) ((self)->vr_regs.vr_sp < (__uint16_t)((__uint16_t)0-(num_bytes)))
#define vm86_state_sp(self)  VM86_ADDR((self)->vr_regs.vr_ss, (self)->vr_regs.vr_sp)
#define vm86_state_ip(self)  VM86_ADDR((self)->vr_regs.vr_cs, (self)->vr_regs.vr_ip)
#define vm86_state_di(self)  VM86_ADDR((self)->vr_regs.vr_ds, (self)->vr_regs.vr_di)
#define vm86_state_si(self)  VM86_ADDR((self)->vr_regs.vr_es, (self)->vr_regs.vr_si)

#endif /* __CC__ */


#define VM86_SUCCESS         0  /* Success */
#define VM86_HALTED          1  /* Emulation was halted by `hlt' without any pending interrupts. */
#define VM86_STOPPED         2  /* Emulation returned gracefully (by jumping to 0xffff:0xffff) */
#define VM86_INTR_ENABLED   99  /* Success (interrupts were re-enabled but shouldn't be checked until after the next instruction) */
#define VM86_FROZEN        (-1) /* Emulation was frozen by `hlt' without #IF */
#define VM86_DOUBLE_FAULT  (-2) /* A double fault was caused. */
#define VM86_SEGFAULT      (-3) /* Segmentation fault. */
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
 * @return: VM86_SUCCESS: The single instruction was successfully executed.
 * @return: VM86_STOPPED: The program counter was already placed at 0xffff:0xffff
 * @return: * :           One of `VM86_*' */
typedef int (LIBVM86_CC *PVM86_STEP)(vm86_state_t *__restrict self);
#ifdef LIBVM86_WANT_PROTOTYPES
LIBVM86_DECL int LIBVM86_CC vm86_step(vm86_state_t *__restrict self);
#endif /* LIBVM86_WANT_PROTOTYPES */

/* Same as `vm86_step()', but also check for pending interrupts beforehand. */
typedef int (LIBVM86_CC *PVM86_FULLSTEP)(vm86_state_t *__restrict self);
#ifdef LIBVM86_WANT_PROTOTYPES
LIBVM86_DECL int LIBVM86_CC vm86_fullstep(vm86_state_t *__restrict self);
#endif /* LIBVM86_WANT_PROTOTYPES */

/* Execute VM86 emulator code until that code finishes execution. */
typedef int (LIBVM86_CC *PVM86_EXEC)(vm86_state_t *__restrict self);
#ifdef LIBVM86_WANT_PROTOTYPES
LIBVM86_DECL int LIBVM86_CC vm86_exec(vm86_state_t *__restrict self);
#endif /* LIBVM86_WANT_PROTOTYPES */

/* Trigger an interrupt.
 * vm86_sw_intr:
 *   - Always trigger the interrupt
 * vm86_hw_intr:
 *   - Check if #IF is set
 *     - Yes: Trigger the interrupt by invoking `vm86_sw_intr(intno)'
 *     - No:  Mark the interrupt as pending
 * vm86_pic_intr:
 *   - `pic_intno' must be `>= 0 && <= 15', where 0..7 maps to PIC#1 and 8..15 to PIC#2
 *   #1: Determine which PIC is addressed.
 *   #2: If the interrupt is being ignored, returning immediately.
 *   #3: If the interrupt is already pending, returning immediately.
 *   #4: If `VM86_PIC_FNEEDEOI' is set, mark the interrupt and pending and returning immediately.
 *   #5: Set the `VM86_PIC_FNEEDEOI' flag (unless `VM86_PIC_FAUTOEOI' is also set)
 *   #6: Invoke `vm86_hw_intr()' with the pic_intno adjusted
 *       relative to the base of the associated PIC:
 *       >> intno = pic_intno >= 8 ? (vr_pic2_base + (pic_intno - 8)) : (vr_pic1_base + pic_intno);
 * @return: VM86_SUCCESS:      Success.
 * @return: VM86_DOUBLE_FAULT: Stack overflow.
 * @return: VM86_SEGFAULT:     Segmentation fault. */
typedef int (LIBVM86_CC *PVM86_SW_INTR)(vm86_state_t *__restrict self, __uint8_t intno);
typedef int (LIBVM86_CC *PVM86_HW_INTR)(vm86_state_t *__restrict self, __uint8_t intno);
typedef int (LIBVM86_CC *PVM86_PIC_INTR)(vm86_state_t *__restrict self, __uint8_t pic_intno);
#ifdef LIBVM86_WANT_PROTOTYPES
LIBVM86_DECL int (LIBVM86_CC vm86_sw_intr)(vm86_state_t *__restrict self, __uint8_t intno);
LIBVM86_DECL int (LIBVM86_CC vm86_hw_intr)(vm86_state_t *__restrict self, __uint8_t intno);
LIBVM86_DECL int (LIBVM86_CC vm86_pic_intr)(vm86_state_t *__restrict self, __uint8_t pic_intno);
#endif /* LIBVM86_WANT_PROTOTYPES */

/* Read/Write values to/from an emulated VIO port.
 * @return: VM86_SUCCESS: Success.
 * @return: VM86_BADPORT: Bad port. */
typedef int (LIBVM86_CC *PVM86_INB)(vm86_state_t *__restrict self, __uint16_t port, __uint8_t *__restrict presult);
typedef int (LIBVM86_CC *PVM86_INW)(vm86_state_t *__restrict self, __uint16_t port, __uint16_t *__restrict presult);
typedef int (LIBVM86_CC *PVM86_INL)(vm86_state_t *__restrict self, __uint16_t port, __uint32_t *__restrict presult);
typedef int (LIBVM86_CC *PVM86_OUTB)(vm86_state_t *__restrict self, __uint16_t port, __uint8_t value);
typedef int (LIBVM86_CC *PVM86_OUTW)(vm86_state_t *__restrict self, __uint16_t port, __uint16_t value);
typedef int (LIBVM86_CC *PVM86_OUTL)(vm86_state_t *__restrict self, __uint16_t port, __uint32_t value);
#ifdef LIBVM86_WANT_PROTOTYPES
LIBVM86_DECL int (LIBVM86_CC vm86_inb)(vm86_state_t *__restrict self, __uint16_t port, __uint8_t *__restrict presult);
LIBVM86_DECL int (LIBVM86_CC vm86_inw)(vm86_state_t *__restrict self, __uint16_t port, __uint16_t *__restrict presult);
LIBVM86_DECL int (LIBVM86_CC vm86_inl)(vm86_state_t *__restrict self, __uint16_t port, __uint32_t *__restrict presult);
LIBVM86_DECL int (LIBVM86_CC vm86_outb)(vm86_state_t *__restrict self, __uint16_t port, __uint8_t value);
LIBVM86_DECL int (LIBVM86_CC vm86_outw)(vm86_state_t *__restrict self, __uint16_t port, __uint16_t value);
LIBVM86_DECL int (LIBVM86_CC vm86_outl)(vm86_state_t *__restrict self, __uint16_t port, __uint32_t value);
#endif /* LIBVM86_WANT_PROTOTYPES */

#endif /* __CC__ */


__DECL_END

#endif /* !_LIBVM86_EMULATOR_H */
