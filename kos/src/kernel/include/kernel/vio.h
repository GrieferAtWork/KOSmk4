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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_VIO_H
#define GUARD_KERNEL_INCLUDE_KERNEL_VIO_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include "vm.h"

#ifdef CONFIG_VIO
#include <kernel/arch/vio.h>

#ifdef CONFIG_VIO_HAS_INT128_CMPXCH
#include <int128.h>
#endif /* CONFIG_VIO_HAS_INT128_CMPXCH */

DECL_BEGIN


struct vm_futex;
struct vm_datablock_type_vio;
struct vio_args {
	struct vm_datablock_type_vio const *va_type;  /* [1..1][== va_block->db_type->dt_vio] */
	struct vm_datablock                *va_block; /* [1..1] The data block that is being accessed. */
	struct vm_datapart                 *va_part;  /* [0..1] The part that is being accessed. */
	pos_t                          va_access_partoff; /* Offset into `va_block' where `va_access_pageid' is mapped. */
	pageid_t                            va_access_pageid;  /* The accessed page index. */
	struct icpustate                   *va_state; /* [0..1] The CPU state at the time of the access being made (or `NULL' when accessed through other means). */
};


/* VIO and futex:
 *  - In general, using futex operation on VIO memory works the same way it
 *    works for regular memory. No special distinction is made for VIO memory.
 *  - However, vio callbacks are obviously able, and allowed to perform blocking
 *    operations, including both the lookup, and subsequent use of futex functions,
 *    including both the broadcasting of, and waiting for a futex's signal.
 *  - For convenience, you may use `vio_getfutex[_existing]()' in order to access
 *    the futex associated with the address that is being accessed.
 */

/* Return a reference to the futex associated with the accessed address. */
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct vm_futex *KCALL
vio_getfutex(struct vio_args const *__restrict args)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Same as `vio_getfutex()', but don't allocate a new
 * futex object if none already exists for the accessed address
 * @return: * : The futex associated with the accessed address
 * @return: NULL: No futex exists for the accessed address. */
FUNDEF WUNUSED NONNULL((1)) REF struct vm_futex *KCALL
vio_getfutex_existing(struct vio_args const *__restrict args)
		THROWS(E_WOULDBLOCK, E_BADALLOC);


struct vm_datablock_type_vio {
	/* VIO callbacks (`addr' is always relative to the data-block)
	 * NOTE: For unrecognized addresses, VIO should throw
	 *      `E_SEGFAULT_NOTREADABLE' / `E_SEGFAULT_NOTWRITABLE' exceptions. */
	struct {
		NONNULL((1)) u8  (KCALL *f_byte)(struct vio_args *__restrict args, pos_t addr);
		NONNULL((1)) u16 (KCALL *f_word)(struct vio_args *__restrict args, pos_t addr);
		NONNULL((1)) u32 (KCALL *f_dword)(struct vio_args *__restrict args, pos_t addr);
#ifdef CONFIG_VIO_HAS_QWORD
		NONNULL((1)) u64 (KCALL *f_qword)(struct vio_args *__restrict args, pos_t addr);
#endif /* CONFIG_VIO_HAS_QWORD */
	} dtv_read;

#ifdef CONFIG_VIO_HAS_QWORD
#define VIO_CALLBACK_INIT(b, w, l, q) { b, w, l, q }
#else /* CONFIG_VIO_HAS_QWORD */
#define VIO_CALLBACK_INIT(b, w, l, q) { b, w, l }
#endif /* !CONFIG_VIO_HAS_QWORD */

	struct {
		NONNULL((1)) void (KCALL *f_byte)(struct vio_args *__restrict args, pos_t addr, u8 value);
		NONNULL((1)) void (KCALL *f_word)(struct vio_args *__restrict args, pos_t addr, u16 value);
		NONNULL((1)) void (KCALL *f_dword)(struct vio_args *__restrict args, pos_t addr, u32 value);
#ifdef CONFIG_VIO_HAS_QWORD
		NONNULL((1)) void (KCALL *f_qword)(struct vio_args *__restrict args, pos_t addr, u64 value);
#endif /* CONFIG_VIO_HAS_QWORD */
	} dtv_write;

	struct {
		/* Return the old value (regardless of the compare-exchange having been successful) */
		NONNULL((1)) u8  (KCALL *f_byte)(struct vio_args *__restrict args, pos_t addr, u8 oldvalue, u8 newvalue, bool atomic);
		NONNULL((1)) u16 (KCALL *f_word)(struct vio_args *__restrict args, pos_t addr, u16 oldvalue, u16 newvalue, bool atomic);
		NONNULL((1)) u32 (KCALL *f_dword)(struct vio_args *__restrict args, pos_t addr, u32 oldvalue, u32 newvalue, bool atomic);
#if defined(CONFIG_VIO_HAS_QWORD) || defined(CONFIG_VIO_HAS_QWORD_CMPXCH)
		NONNULL((1)) u64 (KCALL *f_qword)(struct vio_args *__restrict args, pos_t addr, u64 oldvalue, u64 newvalue, bool atomic);
#endif /* CONFIG_VIO_HAS_QWORD || CONFIG_VIO_HAS_QWORD_CMPXCH */
#ifdef CONFIG_VIO_HAS_INT128_CMPXCH
		NONNULL((1)) uint128_t (KCALL *f_int128)(struct vio_args *__restrict args, pos_t addr, uint128_t oldvalue, uint128_t newvalue, bool atomic);
#endif /* CONFIG_VIO_HAS_INT128_CMPXCH */
	} dtv_cmpxch;

	struct {
		/* Return the old value */
		NONNULL((1)) u8  (KCALL *f_byte)(struct vio_args *__restrict args, pos_t addr, u8 newvalue, bool atomic);
		NONNULL((1)) u16 (KCALL *f_word)(struct vio_args *__restrict args, pos_t addr, u16 newvalue, bool atomic);
		NONNULL((1)) u32 (KCALL *f_dword)(struct vio_args *__restrict args, pos_t addr, u32 newvalue, bool atomic);
#ifdef CONFIG_VIO_HAS_QWORD
		NONNULL((1)) u64 (KCALL *f_qword)(struct vio_args *__restrict args, pos_t addr, u64 newvalue, bool atomic);
#endif /* CONFIG_VIO_HAS_QWORD */
	} dtv_xch;

	struct {
		/* Return the old value (prior to be `value' being added) */
		NONNULL((1)) u8  (KCALL *f_byte)(struct vio_args *__restrict args, pos_t addr, u8 value, bool atomic);
		NONNULL((1)) u16 (KCALL *f_word)(struct vio_args *__restrict args, pos_t addr, u16 value, bool atomic);
		NONNULL((1)) u32 (KCALL *f_dword)(struct vio_args *__restrict args, pos_t addr, u32 value, bool atomic);
#ifdef CONFIG_VIO_HAS_QWORD
		NONNULL((1)) u64 (KCALL *f_qword)(struct vio_args *__restrict args, pos_t addr, u64 value, bool atomic);
#endif /* CONFIG_VIO_HAS_QWORD */
	} dtv_add;

	struct {
		/* Return the old value (prior to be `value' being subtracted) */
		NONNULL((1)) u8  (KCALL *f_byte)(struct vio_args *__restrict args, pos_t addr, u8 value, bool atomic);
		NONNULL((1)) u16 (KCALL *f_word)(struct vio_args *__restrict args, pos_t addr, u16 value, bool atomic);
		NONNULL((1)) u32 (KCALL *f_dword)(struct vio_args *__restrict args, pos_t addr, u32 value, bool atomic);
#ifdef CONFIG_VIO_HAS_QWORD
		NONNULL((1)) u64 (KCALL *f_qword)(struct vio_args *__restrict args, pos_t addr, u64 value, bool atomic);
#endif /* CONFIG_VIO_HAS_QWORD */
	} dtv_sub;

	struct {
		/* Return the old value (prior to be `mask' being anded) */
		NONNULL((1)) u8  (KCALL *f_byte)(struct vio_args *__restrict args, pos_t addr, u8 mask, bool atomic);
		NONNULL((1)) u16 (KCALL *f_word)(struct vio_args *__restrict args, pos_t addr, u16 mask, bool atomic);
		NONNULL((1)) u32 (KCALL *f_dword)(struct vio_args *__restrict args, pos_t addr, u32 mask, bool atomic);
#ifdef CONFIG_VIO_HAS_QWORD
		NONNULL((1)) u64 (KCALL *f_qword)(struct vio_args *__restrict args, pos_t addr, u64 mask, bool atomic);
#endif /* CONFIG_VIO_HAS_QWORD */
	} dtv_and;

	struct {
		/* Return the old value (prior to be `mask' being or'd) */
		NONNULL((1)) u8  (KCALL *f_byte)(struct vio_args *__restrict args, pos_t addr, u8 mask, bool atomic);
		NONNULL((1)) u16 (KCALL *f_word)(struct vio_args *__restrict args, pos_t addr, u16 mask, bool atomic);
		NONNULL((1)) u32 (KCALL *f_dword)(struct vio_args *__restrict args, pos_t addr, u32 mask, bool atomic);
#ifdef CONFIG_VIO_HAS_QWORD
		NONNULL((1)) u64 (KCALL *f_qword)(struct vio_args *__restrict args, pos_t addr, u64 mask, bool atomic);
#endif /* CONFIG_VIO_HAS_QWORD */
	} dtv_or;

	struct {
		/* Return the old value (prior to be `mask' being xor'd) */
		NONNULL((1)) u8  (KCALL *f_byte)(struct vio_args *__restrict args, pos_t addr, u8 mask, bool atomic);
		NONNULL((1)) u16 (KCALL *f_word)(struct vio_args *__restrict args, pos_t addr, u16 mask, bool atomic);
		NONNULL((1)) u32 (KCALL *f_dword)(struct vio_args *__restrict args, pos_t addr, u32 mask, bool atomic);
#ifdef CONFIG_VIO_HAS_QWORD
		NONNULL((1)) u64 (KCALL *f_qword)(struct vio_args *__restrict args, pos_t addr, u64 mask, bool atomic);
#endif /* CONFIG_VIO_HAS_QWORD */
	} dtv_xor;

	/* Invoked as the result of the user attempting to call into VIO memory.
	 * When this operator is called, `regs' will have already been updated to
	 * point to the instruction following the call instruction that was used
	 * to execute VIO memory.
	 * USER:
	 * >> void *vio_base;
	 * >> vio_base = mmap(NULL, 0x1000, PROT_READ | PROT_EXEC, MAP_PRIVATE, vio_fd, 0);
	 * >>
	 * >> kernel_function = (int(*)(int, int))((byte_t *)vio_base + 1234);
	 * >>
	 * >> // This function will invoke `dtv_call(..., REGS, 1234)'
	 * >> // REGS: (user-space register state; assuming x86)
	 * >> //    PC: ADDROF(printf)
	 * >> //    SP: { int: 10, int: 20 }
	 * >> // `dtv_call' can then assign the EAX register in `args' (again: assuming x86),
	 * >> // which is the value that's going to be returned to user-space and be assigned
	 * >> // to `x', before being printed.
	 * >> int x = (*kernel_function)(10, 20);
	 * >>
	 * >> printf("x = %d\n", x);
	 * >>
	 * @return: * : A pointer to the new register state that should be restored.
	 *              Usually, this is the same as `regs' */
	struct icpustate *(KCALL *dtv_call)(struct vio_args *__restrict args,
	                                    struct icpustate *__restrict regs,
	                                    pos_t addr);
};

/* Initializers for VIO callbacks */
#ifdef CONFIG_VIO_HAS_QWORD
#define VM_DATABLOCK_TYPE_VIO_INIT_READ(b, w, l, q)  { b, w, l, q }
#define VM_DATABLOCK_TYPE_VIO_INIT_WRITE(b, w, l, q) { b, w, l, q }
#define VM_DATABLOCK_TYPE_VIO_INIT_XCH(b, w, l, q)   { b, w, l, q }
#define VM_DATABLOCK_TYPE_VIO_INIT_ADD(b, w, l, q)   { b, w, l, q }
#define VM_DATABLOCK_TYPE_VIO_INIT_SUB(b, w, l, q)   { b, w, l, q }
#define VM_DATABLOCK_TYPE_VIO_INIT_AND(b, w, l, q)   { b, w, l, q }
#define VM_DATABLOCK_TYPE_VIO_INIT_OR(b, w, l, q)    { b, w, l, q }
#define VM_DATABLOCK_TYPE_VIO_INIT_XOR(b, w, l, q)   { b, w, l, q }
#else /* CONFIG_VIO_HAS_QWORD */
#define VM_DATABLOCK_TYPE_VIO_INIT_READ(b, w, l, q)  { b, w, l }
#define VM_DATABLOCK_TYPE_VIO_INIT_WRITE(b, w, l, q) { b, w, l }
#define VM_DATABLOCK_TYPE_VIO_INIT_XCH(b, w, l, q)   { b, w, l }
#define VM_DATABLOCK_TYPE_VIO_INIT_ADD(b, w, l, q)   { b, w, l }
#define VM_DATABLOCK_TYPE_VIO_INIT_SUB(b, w, l, q)   { b, w, l }
#define VM_DATABLOCK_TYPE_VIO_INIT_AND(b, w, l, q)   { b, w, l }
#define VM_DATABLOCK_TYPE_VIO_INIT_OR(b, w, l, q)    { b, w, l }
#define VM_DATABLOCK_TYPE_VIO_INIT_XOR(b, w, l, q)   { b, w, l }
#endif /* !CONFIG_VIO_HAS_QWORD */


#if defined(CONFIG_VIO_HAS_QWORD) || defined(CONFIG_VIO_HAS_QWORD_CMPXCH)
#ifdef CONFIG_VIO_HAS_INT128_CMPXCH
#define VM_DATABLOCK_TYPE_VIO_INIT_CMPXCH(b, w, l, q, i128) { b, w, l, q, i128 }
#else /* CONFIG_VIO_HAS_INT128_CMPXCH */
#define VM_DATABLOCK_TYPE_VIO_INIT_CMPXCH(b, w, l, q, i128) { b, w, l, q }
#endif /* !CONFIG_VIO_HAS_INT128_CMPXCH */
#else /* CONFIG_VIO_HAS_QWORD || CONFIG_VIO_HAS_QWORD_CMPXCH */
#ifdef CONFIG_VIO_HAS_INT128_CMPXCH
#define VM_DATABLOCK_TYPE_VIO_INIT_CMPXCH(b, w, l, q, i128) { b, w, l, i128 }
#else /* CONFIG_VIO_HAS_INT128_CMPXCH */
#define VM_DATABLOCK_TYPE_VIO_INIT_CMPXCH(b, w, l, q, i128) { b, w, l }
#endif /* !CONFIG_VIO_HAS_INT128_CMPXCH */
#endif /* !CONFIG_VIO_HAS_QWORD && !CONFIG_VIO_HAS_QWORD_CMPXCH */



/* Invoke VIO callbacks, automatically substituting operators for one-another.
 * If an operation is impossible, these functions will throw a SEGFAULT exception.
 * @param: atomic: Throw an error if the operation cannot be performed atomically. */
FUNDEF NONNULL((1)) u8  KCALL vio_readb(struct vio_args *__restrict args, pos_t addr);
FUNDEF NONNULL((1)) u16 KCALL vio_readw(struct vio_args *__restrict args, pos_t addr);
FUNDEF NONNULL((1)) u32 KCALL vio_readl(struct vio_args *__restrict args, pos_t addr);
FUNDEF NONNULL((1)) void KCALL vio_writeb(struct vio_args *__restrict args, pos_t addr, u8  value);
FUNDEF NONNULL((1)) void KCALL vio_writew(struct vio_args *__restrict args, pos_t addr, u16 value);
FUNDEF NONNULL((1)) void KCALL vio_writel(struct vio_args *__restrict args, pos_t addr, u32 value);
FUNDEF NONNULL((1)) u8  KCALL vio_cmpxchb(struct vio_args *__restrict args, pos_t addr, u8  oldvalue, u8  newvalue, bool atomic);
FUNDEF NONNULL((1)) u16 KCALL vio_cmpxchw(struct vio_args *__restrict args, pos_t addr, u16 oldvalue, u16 newvalue, bool atomic);
FUNDEF NONNULL((1)) u32 KCALL vio_cmpxchl(struct vio_args *__restrict args, pos_t addr, u32 oldvalue, u32 newvalue, bool atomic);
FUNDEF NONNULL((1)) u8  KCALL vio_cmpxch_or_writeb(struct vio_args *__restrict args, pos_t addr, u8  oldvalue, u8  newvalue, bool atomic);
FUNDEF NONNULL((1)) u16 KCALL vio_cmpxch_or_writew(struct vio_args *__restrict args, pos_t addr, u16 oldvalue, u16 newvalue, bool atomic);
FUNDEF NONNULL((1)) u32 KCALL vio_cmpxch_or_writel(struct vio_args *__restrict args, pos_t addr, u32 oldvalue, u32 newvalue, bool atomic);
FUNDEF NONNULL((1)) u8  KCALL vio_xchb(struct vio_args *__restrict args, pos_t addr, u8  newvalue, bool atomic);
FUNDEF NONNULL((1)) u16 KCALL vio_xchw(struct vio_args *__restrict args, pos_t addr, u16 newvalue, bool atomic);
FUNDEF NONNULL((1)) u32 KCALL vio_xchl(struct vio_args *__restrict args, pos_t addr, u32 newvalue, bool atomic);
FUNDEF NONNULL((1)) u8  KCALL vio_addb(struct vio_args *__restrict args, pos_t addr, u8  value, bool atomic);
FUNDEF NONNULL((1)) u16 KCALL vio_addw(struct vio_args *__restrict args, pos_t addr, u16 value, bool atomic);
FUNDEF NONNULL((1)) u32 KCALL vio_addl(struct vio_args *__restrict args, pos_t addr, u32 value, bool atomic);
FUNDEF NONNULL((1)) u8  KCALL vio_subb(struct vio_args *__restrict args, pos_t addr, u8  value, bool atomic);
FUNDEF NONNULL((1)) u16 KCALL vio_subw(struct vio_args *__restrict args, pos_t addr, u16 value, bool atomic);
FUNDEF NONNULL((1)) u32 KCALL vio_subl(struct vio_args *__restrict args, pos_t addr, u32 value, bool atomic);
FUNDEF NONNULL((1)) u8  KCALL vio_andb(struct vio_args *__restrict args, pos_t addr, u8  mask, bool atomic);
FUNDEF NONNULL((1)) u16 KCALL vio_andw(struct vio_args *__restrict args, pos_t addr, u16 mask, bool atomic);
FUNDEF NONNULL((1)) u32 KCALL vio_andl(struct vio_args *__restrict args, pos_t addr, u32 mask, bool atomic);
FUNDEF NONNULL((1)) u8  KCALL vio_orb(struct vio_args *__restrict args, pos_t addr, u8  mask, bool atomic);
FUNDEF NONNULL((1)) u16 KCALL vio_orw(struct vio_args *__restrict args, pos_t addr, u16 mask, bool atomic);
FUNDEF NONNULL((1)) u32 KCALL vio_orl(struct vio_args *__restrict args, pos_t addr, u32 mask, bool atomic);
FUNDEF NONNULL((1)) u8  KCALL vio_xorb(struct vio_args *__restrict args, pos_t addr, u8  mask, bool atomic);
FUNDEF NONNULL((1)) u16 KCALL vio_xorw(struct vio_args *__restrict args, pos_t addr, u16 mask, bool atomic);
FUNDEF NONNULL((1)) u32 KCALL vio_xorl(struct vio_args *__restrict args, pos_t addr, u32 mask, bool atomic);

/* Copy memory to/from VIO */
FUNDEF NONNULL((1)) void KCALL vio_copyfromvio(struct vio_args *__restrict args, pos_t offset, USER CHECKED void *buf, size_t num_bytes) THROWS(E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL vio_copytovio(struct vio_args *__restrict args, pos_t offset, USER CHECKED void const *buf, size_t num_bytes) THROWS(E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL vio_memset(struct vio_args *__restrict args, pos_t offset, int byte, size_t num_bytes) THROWS(E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL vio_copyfromvio_to_phys(struct vio_args *__restrict args, pos_t offset, vm_phys_t buf, size_t num_bytes) THROWS(...);
FUNDEF NONNULL((1)) void KCALL vio_copytovio_from_phys(struct vio_args *__restrict args, pos_t offset, vm_phys_t buf, size_t num_bytes) THROWS(...);


#if defined(CONFIG_VIO_HAS_QWORD) || defined(CONFIG_VIO_HAS_QWORD_CMPXCH)
FUNDEF NONNULL((1)) u64 KCALL vio_cmpxchq(struct vio_args *__restrict args, pos_t addr, u64 oldvalue, u64 newvalue, bool atomic);
#endif /* CONFIG_VIO_HAS_QWORD || CONFIG_VIO_HAS_QWORD_CMPXCH */
#ifdef CONFIG_VIO_HAS_INT128_CMPXCH
FUNDEF NONNULL((1)) uint128_t KCALL vio_cmpxch128(struct vio_args *__restrict args, pos_t addr, uint128_t oldvalue, uint128_t newvalue, bool atomic);
#endif /* CONFIG_VIO_HAS_INT128_CMPXCH */
#ifdef CONFIG_VIO_HAS_QWORD
FUNDEF NONNULL((1)) u64 KCALL vio_cmpxch_or_writeq(struct vio_args *__restrict args, pos_t addr, u64 oldvalue, u64 newvalue, bool atomic);
FUNDEF NONNULL((1)) u64 KCALL vio_readq(struct vio_args *__restrict args, pos_t addr);
FUNDEF NONNULL((1)) void KCALL vio_writeq(struct vio_args *__restrict args, pos_t addr, u64 value);
FUNDEF NONNULL((1)) u64 KCALL vio_xchq(struct vio_args *__restrict args, pos_t addr, u64 newvalue, bool atomic);
FUNDEF NONNULL((1)) u64 KCALL vio_addq(struct vio_args *__restrict args, pos_t addr, u64 value, bool atomic);
FUNDEF NONNULL((1)) u64 KCALL vio_subq(struct vio_args *__restrict args, pos_t addr, u64 value, bool atomic);
FUNDEF NONNULL((1)) u64 KCALL vio_andq(struct vio_args *__restrict args, pos_t addr, u64 mask, bool atomic);
FUNDEF NONNULL((1)) u64 KCALL vio_orq(struct vio_args *__restrict args, pos_t addr, u64 mask, bool atomic);
FUNDEF NONNULL((1)) u64 KCALL vio_xorq(struct vio_args *__restrict args, pos_t addr, u64 mask, bool atomic);
#endif /* CONFIG_VIO_HAS_QWORD */

/* Same as the function above, but these require the address to be aligned by the data type. */
FUNDEF NONNULL((1)) u8  KCALL vio_readb_aligned(struct vio_args *__restrict args, pos_t addr) ASMNAME("vio_readb");
FUNDEF NONNULL((1)) u16 KCALL vio_readw_aligned(struct vio_args *__restrict args, pos_t addr);
FUNDEF NONNULL((1)) u32 KCALL vio_readl_aligned(struct vio_args *__restrict args, pos_t addr);
FUNDEF NONNULL((1)) void KCALL vio_writeb_aligned(struct vio_args *__restrict args, pos_t addr, u8  value) ASMNAME("vio_writeb");
FUNDEF NONNULL((1)) void KCALL vio_writew_aligned(struct vio_args *__restrict args, pos_t addr, u16 value);
FUNDEF NONNULL((1)) void KCALL vio_writel_aligned(struct vio_args *__restrict args, pos_t addr, u32 value);
#ifdef CONFIG_VIO_HAS_QWORD
FUNDEF NONNULL((1)) u64 KCALL vio_readq_aligned(struct vio_args *__restrict args, pos_t addr);
FUNDEF NONNULL((1)) void KCALL vio_writeq_aligned(struct vio_args *__restrict args, pos_t addr, u64 value);
#endif /* CONFIG_VIO_HAS_QWORD */


DECL_END
#endif /* CONFIG_VIO */


#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_VIO_H */
