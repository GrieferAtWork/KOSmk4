/*[[[magic
// Optimize this file for size
local opt = options.setdefault("GCC.options", []);
opt.removeif([](e) -> e.startswith("-O"));
opt.append("-Os");
]]]*/
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
#ifndef GUARD_LIBVIOCORE_ARCH_I386_VIOCORE_C
#define GUARD_LIBVIOCORE_ARCH_I386_VIOCORE_C 1
#define DISABLE_BRANCH_PROFILING
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <hybrid/host.h>

#ifdef __x86_64__
#define LIBEMU86_CONFIG_WANT_16BIT 0
#define LIBEMU86_CONFIG_WANT_32BIT 1
#define LIBEMU86_CONFIG_WANT_64BIT 1
#else /* __x86_64__ */
#define LIBEMU86_CONFIG_WANT_16BIT 1
#define LIBEMU86_CONFIG_WANT_32BIT 1
#define LIBEMU86_CONFIG_WANT_64BIT 0
#endif /* !__x86_64__ */
#define __LIBEMU86_STATIC 1


#include "../../api.h"

#ifdef LIBVIO_CONFIG_ENABLED

#include <hybrid/atomic.h>

#include <asm/cpu-flags.h>
#include <asm/cpu-msr.h>
#include <asm/intrin-fpu.h>
#include <asm/intrin.h>
#include <asm/registers-compat.h>
#include <asm/registers.h>
#include <kos/anno.h>
#include <kos/except.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/paging.h>
#include <kos/kernel/x86/segment.h>
#include <kos/kernel/types.h>
#include <kos/types.h>
#include <sys/syslog.h>

#include <assert.h>
#include <int128.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>

#include <libemu86/emu86.h>
#include <libinstrlen/instrlen.h>
#include <libvio/access.h>

#include "../../viocore.h"

#ifdef __KERNEL__
#include <kernel/printk.h>
#include <kernel/user.h>
#include <hybrid/sched/preemption.h>
#endif /* __KERNEL__ */

#ifdef __KERNEL__
#define PRINT_WARN(...) printk(KERN_WARNING __VA_ARGS__)
#else /* __KERNEL__ */
#define PRINT_WARN(...) syslog(LOG_WARN, __VA_ARGS__)
#endif /* !__KERNEL__ */


DECL_BEGIN

/* Emulate the instruction pointed-to by `self->vea_args.va_state' and dispatch
 * any memory access made to `self->vea_ptrlo ... self->vea_ptrhi' via the  VIO
 * callback table.
 * Upon success, `self->vea_args.va_state' will point to the updated CPU state,
 * which may  be  placed  at  a  different address  than  it  was  upon  entry.
 * This function is intended to be called from a page fault handler. */
INTDEF void CC libviocore_emulate(struct vio_emulate_args *__restrict self);

#ifdef __KERNEL__
#define CS(x)  icpustate_##x
#define _CS(x) x##_icpustate
#else /* __KERNEL__ */
#define CS(x)  ucpustate_##x
#define _CS(x) x##_ucpustate
#endif /* !__KERNEL__ */

/* Fill in missing exception pointer. */
PRIVATE ATTR_NORETURN NOBLOCK void CC
libviocore_complete_except(struct vio_emulate_args *__restrict self,
                           uintptr_t opcode, emu86_opflags_t op_flags) {
	struct exception_data *data;
	data = except_data();
	if (data->e_class == E_ILLEGAL_INSTRUCTION) {
		if (!data->e_args.e_illegal_instruction.ii_opcode)
			data->e_args.e_illegal_instruction.ii_opcode = opcode;
		if (!data->e_args.e_illegal_instruction.ii_op_flags)
			data->e_args.e_illegal_instruction.ii_op_flags = op_flags;
	} else if (data->e_class == E_SEGFAULT) {
		/* Fix-up the context code for the segmentation fault. */
		/* We're the VIO handler, so check if the fault happened during VIO */
		if ((byte_t *)data->e_args.e_segfault.s_addr >= (byte_t *)self->vea_ptrlo &&
		    (byte_t *)data->e_args.e_segfault.s_addr <= (byte_t *)self->vea_ptrhi)
			data->e_args.e_segfault.s_context |= E_SEGFAULT_CONTEXT_VIO;
#ifdef __KERNEL__
		if (icpustate_isuser(self->vea_args.va_state))
#endif /* __KERNEL__ */
		{
			/* The fault happened due to a user-space access */
			data->e_args.e_segfault.s_context |= E_SEGFAULT_CONTEXT_USERCODE;
		}
#ifdef __x86_64__
		/* The fault uses a non-canonical address (shouldn't actually happen...) */
		if (ADDR_IS_NONCANON(data->e_args.e_segfault.s_addr))
			data->e_args.e_segfault.s_context |= E_SEGFAULT_CONTEXT_NONCANON;
#endif /* __x86_64__ */
	}
	/* Fix-up the PC register and fill in the fault address */
	{
		byte_t const *pc, *next_pc;
		pc      = (byte_t const *)CS(getpc)(self->vea_args.va_state);
		next_pc = instruction_succ_nx(pc, CS(getisa)(self->vea_args.va_state));
		data->e_faultaddr = (void *)pc;
		if (next_pc)
			CS(setpc)(self->vea_args.va_state, next_pc);
	}
	RETHROW();
}

#ifdef __KERNEL__
#define VALRD(addr, num_bytes)                         \
	do {                                               \
		if (icpustate_isuser(self->vea_args.va_state)) \
			validate_readable(addr, num_bytes);        \
	}	__WHILE0
#define VALWR(addr, num_bytes)                         \
	do {                                               \
		if (icpustate_isuser(self->vea_args.va_state)) \
			validate_writable(addr, num_bytes);        \
	}	__WHILE0
#define VALRDWR(addr, num_bytes)                       \
	do {                                               \
		if (icpustate_isuser(self->vea_args.va_state)) \
			validate_readwrite(addr, num_bytes);       \
	}	__WHILE0
#else /* __KERNEL__ */
#define VALRD(addr, num_bytes)   (void)0
#define VALWR(addr, num_bytes)   (void)0
#define VALRDWR(addr, num_bytes) (void)0
#endif /* !__KERNEL__ */

union word16 {
	u16 w;
	u8 b[2];
};
union word32 {
	u32 l;
	u16 w[2];
	u8 b[4];
};
union word64 {
	u64 q;
	u32 l[2];
	u16 w[4];
	u8 b[8];
};



#define GET_VIO_ADDR(self, addr) \
	((self)->vea_addr + (size_t)((byte_t *)(addr) - (byte_t *)(self)->vea_ptrlo))

/* Check if `addr...+=num_bytes' is entirely within the VIO address range. */
#define IS_VIO_ADDR_FULL(self, addr, num_bytes) \
	((addr) >= (self)->vea_ptrlo && ((byte_t *)(addr) + (num_bytes)-1) <= (byte_t *)(self)->vea_ptrhi)

/* Check if `addr...+=num_bytes' is partially within the VIO address range. */
#define IS_VIO_ADDR_PART(self, addr, num_bytes) \
	((addr) <= (self)->vea_ptrhi && ((byte_t *)(addr) + (num_bytes)-1) >= (byte_t *)(self)->vea_ptrlo)

/* Read VIO memory with a partial overlap between `addr...+=num_bytes',
 * and  the  VIO   address  range   `self->vea_ptrlo...self->vea_ptrhi' */
PRIVATE NONNULL((1)) void CC
libviocore_read_with_partial_overlap(struct vio_emulate_args *__restrict self,
                                     __USER __UNCHECKED void const *addr,
                                     size_t num_bytes, void *resbuf) {
	assert(!IS_VIO_ADDR_FULL(self, addr, num_bytes));
	assert(IS_VIO_ADDR_PART(self, addr, num_bytes));
	if (addr < self->vea_ptrlo) {
		/* Read from lower end. */
		size_t before_vio;
		before_vio = (size_t)((byte_t *)self->vea_ptrlo - (byte_t *)addr);
		/*assert(before_vio < num_bytes);*/
		VALRD(addr, before_vio);
		resbuf = mempcpy(resbuf, addr, before_vio);
		/* Copy the remainder from VIO memory */
		vio_copyfromvio(&self->vea_args, self->vea_addr,
		                resbuf, num_bytes - before_vio);
	} else {
		size_t within_vio;
		void const *pafter_vio;
		/* Read from upper end. */
		within_vio = (size_t)((byte_t *)self->vea_ptrhi - (byte_t *)addr) + 1;
		pafter_vio = (byte_t const *)self->vea_ptrhi + 1;
		/*assert(within_vio < num_bytes);*/
		VALRD(pafter_vio, num_bytes - within_vio);
		memcpy((byte_t *)resbuf + within_vio,
		       pafter_vio, num_bytes - within_vio);
		/* Copy the remainder from VIO memory */
		vio_copyfromvio(&self->vea_args, GET_VIO_ADDR(self, addr),
		                resbuf, within_vio);
	}
}

/* Write VIO memory with a partial overlap between `addr...+=num_bytes',
 * and   the   VIO  address   range  `self->vea_ptrlo...self->vea_ptrhi' */
PRIVATE NONNULL((1)) void CC
libviocore_write_with_partial_overlap(struct vio_emulate_args *__restrict self,
                                      __USER __UNCHECKED void *addr,
                                      size_t num_bytes, void const *srcbuf) {
	assert(!IS_VIO_ADDR_FULL(self, addr, num_bytes));
	assert(IS_VIO_ADDR_PART(self, addr, num_bytes));
	if (addr < self->vea_ptrlo) {
		/* Read from lower end. */
		size_t before_vio;
		before_vio = (size_t)((byte_t *)self->vea_ptrlo - (byte_t *)addr);
		/*assert(before_vio < num_bytes);*/
		VALWR(addr, before_vio);
		memcpy(addr, srcbuf, before_vio);
		/* Copy the remainder from VIO memory */
		vio_copytovio(&self->vea_args, self->vea_addr,
		              (byte_t const *)srcbuf + before_vio,
		              num_bytes - before_vio);
	} else {
		size_t within_vio;
		void *pafter_vio;
		/* Read from upper end. */
		within_vio = (size_t)((byte_t *)self->vea_ptrhi - (byte_t *)addr) + 1;
		pafter_vio = (byte_t *)self->vea_ptrhi + 1;
		/*assert(within_vio < num_bytes);*/
		VALRD(pafter_vio, num_bytes - within_vio);
		memcpy(pafter_vio, (byte_t const *)srcbuf + within_vio,
		       num_bytes - within_vio);
		/* Copy the remainder from VIO memory */
		vio_copytovio(&self->vea_args,
		              GET_VIO_ADDR(self, addr),
		              srcbuf, within_vio);
	}
}

/* Read `VIO memory with a partial overlap between `addr...+=num_bytes',
 * and the  VIO address  range `self->vea_ptrlo...self->vea_ptrhi'  into
 * `oldbuf', before copying `newbuf' into the overlap-area.
 * NOTE: `oldbuf' and `newbuf' are not allowed to overlap, or be the same! */
PRIVATE NONNULL((1)) void CC
libviocore_xch_with_partial_overlap(struct vio_emulate_args *__restrict self,
                                    __USER __UNCHECKED void *addr, size_t num_bytes,
                                    void *__restrict oldbuf,
                                    void const *__restrict newbuf) {
	assert(!IS_VIO_ADDR_FULL(self, addr, num_bytes));
	assert(IS_VIO_ADDR_PART(self, addr, num_bytes));
	if (addr < self->vea_ptrlo) {
		/* Read from lower end. */
		size_t before_vio;
		before_vio = (size_t)((byte_t *)self->vea_ptrlo - (byte_t *)addr);
		/*assert(before_vio < num_bytes);*/
		VALWR(addr, before_vio);
		memcpy(oldbuf, addr, before_vio);
		memcpy(addr, newbuf, before_vio);
		/* Copy the remainder from VIO memory */
		vio_xchwithvio(&self->vea_args,
		               self->vea_addr,
		               (byte_t *)oldbuf + before_vio,
		               (byte_t *)newbuf + before_vio,
		               num_bytes - before_vio,
		               false);
	} else {
		size_t within_vio, after_vio;
		void *pafter_vio;
		/* Read from upper end. */
		within_vio = (size_t)((byte_t *)self->vea_ptrhi - (byte_t *)addr) + 1;
		pafter_vio = (byte_t *)self->vea_ptrhi + 1;
		/*assert(within_vio < num_bytes);*/
		after_vio = num_bytes - within_vio;
		VALRD(pafter_vio, after_vio);
		memcpy((byte_t *)oldbuf + within_vio, pafter_vio, after_vio);
		memcpy(pafter_vio, (byte_t *)newbuf + within_vio, after_vio);
		/* Copy the remainder from VIO memory */
		vio_xchwithvio(&self->vea_args,
		               GET_VIO_ADDR(self, addr),
		               oldbuf,
		               newbuf,
		               within_vio,
		               false);
	}
}



#define EMU86_MEMREADB(addr) \
	libviocore_readb(self, (void const *)(uintptr_t)(addr))
PRIVATE NONNULL((1)) u8 CC
libviocore_readb(struct vio_emulate_args *__restrict self,
                 __USER __UNCHECKED void const *addr) {
	u8 result;
	if likely(IS_VIO_ADDR_FULL(self, addr, 1)) {
		result = vio_readb(&self->vea_args, GET_VIO_ADDR(self, addr));
	} else {
		VALRD(addr, 1);
		result = *(u8 const *)addr;
	}
	COMPILER_READ_BARRIER();
	return result;
}


#define EMU86_MEMREADW(addr) \
	libviocore_readw(self, (void const *)(uintptr_t)(addr))
PRIVATE NONNULL((1)) u16 CC
libviocore_readw(struct vio_emulate_args *__restrict self,
                 __USER __UNCHECKED void const *addr) {
	u16 result;
	if likely(IS_VIO_ADDR_FULL(self, addr, 2)) {
		result = vio_readw(&self->vea_args, GET_VIO_ADDR(self, addr));
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 2)) {
		libviocore_read_with_partial_overlap(self, addr, 2, &result);
	} else {
		VALRD(addr, 2);
		result = *(u16 const *)addr;
	}
	COMPILER_READ_BARRIER();
	return result;
}

#define EMU86_MEMREADL(addr) \
	libviocore_readl(self, (void const *)(uintptr_t)(addr))
PRIVATE NONNULL((1)) u32 CC
libviocore_readl(struct vio_emulate_args *__restrict self,
                 __USER __UNCHECKED void const *addr) {
	u32 result;
	if likely(IS_VIO_ADDR_FULL(self, addr, 4)) {
		result = vio_readl(&self->vea_args, GET_VIO_ADDR(self, addr));
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 4)) {
		libviocore_read_with_partial_overlap(self, addr, 4, &result);
	} else {
		VALRD(addr, 4);
		result = *(u32 const *)addr;
	}
	COMPILER_READ_BARRIER();
	return result;
}

#ifdef __x86_64__
#define EMU86_MEMREADQ(addr) \
	libviocore_readq(self, (void const *)(uintptr_t)(addr))
PRIVATE NONNULL((1)) u64 CC
libviocore_readq(struct vio_emulate_args *__restrict self,
                 __USER __UNCHECKED void const *addr) {
	u64 result;
	if likely(IS_VIO_ADDR_FULL(self, addr, 8)) {
		result = vio_readq(&self->vea_args, GET_VIO_ADDR(self, addr));
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 8)) {
		libviocore_read_with_partial_overlap(self, addr, 8, &result);
	} else {
		VALRD(addr, 8);
		result = *(u64 const *)addr;
	}
	COMPILER_READ_BARRIER();
	return result;
}
#endif /* __x86_64__ */

#define EMU86_MEMWRITEB(addr, v) \
	libviocore_writeb(self, (void *)(uintptr_t)(addr), v)
PRIVATE NONNULL((1)) void CC
libviocore_writeb(struct vio_emulate_args *__restrict self,
                  __USER __UNCHECKED void *addr, u8 value) {
	if likely(IS_VIO_ADDR_FULL(self, addr, 1)) {
		vio_writeb(&self->vea_args, GET_VIO_ADDR(self, addr), value);
	} else {
		VALWR(addr, 1);
		*(u8 *)addr = value;
	}
	COMPILER_WRITE_BARRIER();
}

#define EMU86_MEMWRITEW(addr, v) \
	libviocore_writew(self, (void *)(uintptr_t)(addr), v)
PRIVATE NONNULL((1)) void CC
libviocore_writew(struct vio_emulate_args *__restrict self,
                  __USER __UNCHECKED void *addr, u16 value) {
	if likely(IS_VIO_ADDR_FULL(self, addr, 2)) {
		vio_writew(&self->vea_args, GET_VIO_ADDR(self, addr), value);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 2)) {
		libviocore_write_with_partial_overlap(self, addr, 2, &value);
	} else {
		VALWR(addr, 2);
		*(u16 *)addr = value;
	}
	COMPILER_WRITE_BARRIER();
}

#define EMU86_MEMWRITEL(addr, v) \
	libviocore_writel(self, (void *)(uintptr_t)(addr), v)
PRIVATE NONNULL((1)) void CC
libviocore_writel(struct vio_emulate_args *__restrict self,
                  __USER __UNCHECKED void *addr, u32 value) {
	if likely(IS_VIO_ADDR_FULL(self, addr, 4)) {
		vio_writel(&self->vea_args, GET_VIO_ADDR(self, addr), value);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 4)) {
		libviocore_write_with_partial_overlap(self, addr, 4, &value);
	} else {
		VALWR(addr, 4);
		*(u32 *)addr = value;
	}
	COMPILER_WRITE_BARRIER();
}

#ifdef __x86_64__
#define EMU86_MEMWRITEQ(addr, v) \
	libviocore_writeq(self, (void *)(uintptr_t)(addr), v)
PRIVATE NONNULL((1)) void CC
libviocore_writeq(struct vio_emulate_args *__restrict self,
                  __USER __UNCHECKED void *addr, u64 value) {
	if likely(IS_VIO_ADDR_FULL(self, addr, 8)) {
		vio_writeq(&self->vea_args, GET_VIO_ADDR(self, addr), value);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 8)) {
		libviocore_write_with_partial_overlap(self, addr, 8, &value);
	} else {
		VALWR(addr, 8);
		*(u64 *)addr = value;
	}
	COMPILER_WRITE_BARRIER();
}
#endif /* __x86_64__ */

#define EMU86_MEM_ATOMIC_XCHB(addr, addend, force_atomic) \
	libviocore_atomic_xchb(self, (void *)(uintptr_t)(addr), addend, force_atomic)
PRIVATE NONNULL((1)) u8 CC
libviocore_atomic_xchb(struct vio_emulate_args *__restrict self,
                       __USER __UNCHECKED void *addr, u8 value,
                       bool force_atomic) {
	u8 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 1)) {
		result = vio_xchb(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else {
		VALRDWR(addr, 1);
		if (force_atomic) {
			result = ATOMIC_XCH(*(u8 *)addr, value);
		} else {
			result      = *(u8 const *)addr;
			*(u8 *)addr = value;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_MEM_ATOMIC_XCHW(addr, addend, force_atomic) \
	libviocore_atomic_xchw(self, (void *)(uintptr_t)(addr), addend, force_atomic)
PRIVATE NONNULL((1)) u16 CC
libviocore_atomic_xchw(struct vio_emulate_args *__restrict self,
                       __USER __UNCHECKED void *addr, u16 value,
                       bool force_atomic) {
	u16 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 2)) {
		result = vio_xchw(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 2)) {
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 2);
		libviocore_xch_with_partial_overlap(self, addr, 2, &result, &value);
	} else {
		VALRDWR(addr, 2);
		if (force_atomic) {
			result = ATOMIC_XCH(*(u16 *)addr, value);
		} else {
			result       = *(u16 const *)addr;
			*(u16 *)addr = value;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_MEM_ATOMIC_XCHL(addr, addend, force_atomic) \
	libviocore_atomic_xchl(self, (void *)(uintptr_t)(addr), addend, force_atomic)
PRIVATE NONNULL((1)) u32 CC
libviocore_atomic_xchl(struct vio_emulate_args *__restrict self,
                       __USER __UNCHECKED void *addr, u32 value,
                       bool force_atomic) {
	u32 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 4)) {
		result = vio_xchl(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 4)) {
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 4);
		libviocore_xch_with_partial_overlap(self, addr, 4, &result, &value);
	} else {
		VALRDWR(addr, 4);
		if (force_atomic) {
			result = ATOMIC_XCH(*(u32 *)addr, value);
		} else {
			result       = *(u32 const *)addr;
			*(u32 *)addr = value;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#ifdef __x86_64__
#define EMU86_MEM_ATOMIC_XCHQ(addr, addend, force_atomic) \
	libviocore_atomic_xchq(self, (void *)(uintptr_t)(addr), addend, force_atomic)
PRIVATE NONNULL((1)) u64 CC
libviocore_atomic_xchq(struct vio_emulate_args *__restrict self,
                       __USER __UNCHECKED void *addr, u64 value,
                       bool force_atomic) {
	u64 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 8)) {
		result = vio_xchq(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 8)) {
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 8);
		libviocore_xch_with_partial_overlap(self, addr, 7, &result, &value);
	} else {
		VALRDWR(addr, 8);
		if (force_atomic) {
			result = ATOMIC_XCH(*(u64 *)addr, value);
		} else {
			result       = *(u64 const *)addr;
			*(u64 *)addr = value;
		}
	}
	COMPILER_BARRIER();
	return result;
}
#endif /* __x86_64__ */

#define EMU86_MEM_ATOMIC_FETCHADDB(addr, addend, force_atomic) \
	libviocore_atomic_fetchaddb(self, (void *)(uintptr_t)(addr), addend, force_atomic)
PRIVATE NONNULL((1)) u8 CC
libviocore_atomic_fetchaddb(struct vio_emulate_args *__restrict self,
                            __USER __UNCHECKED void *addr, u8 value,
                            bool force_atomic) {
	u8 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 1)) {
		result = vio_addb(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else {
		VALRDWR(addr, 1);
		if (force_atomic) {
			result = ATOMIC_FETCHADD(*(u8 *)addr, value);
		} else {
			result      = *(u8 const *)addr;
			*(u8 *)addr = result + value;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_MEM_ATOMIC_FETCHADDW(addr, addend, force_atomic) \
	libviocore_atomic_fetchaddw(self, (void *)(uintptr_t)(addr), addend, force_atomic)
PRIVATE NONNULL((1)) u16 CC
libviocore_atomic_fetchaddw(struct vio_emulate_args *__restrict self,
                            __USER __UNCHECKED void *addr, u16 value,
                            bool force_atomic) {
	u16 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 2)) {
		result = vio_addw(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 2)) {
		u16 newval;
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 2);
		libviocore_read_with_partial_overlap(self, addr, 2, &result);
		newval = result + value;
		libviocore_write_with_partial_overlap(self, addr, 2, &newval);
	} else {
		VALRDWR(addr, 2);
		if (force_atomic) {
			result = ATOMIC_FETCHADD(*(u16 *)addr, value);
		} else {
			result       = *(u16 const *)addr;
			*(u16 *)addr = result + value;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_MEM_ATOMIC_FETCHADDL(addr, addend, force_atomic) \
	libviocore_atomic_fetchaddl(self, (void *)(uintptr_t)(addr), addend, force_atomic)
PRIVATE NONNULL((1)) u32 CC
libviocore_atomic_fetchaddl(struct vio_emulate_args *__restrict self,
                            __USER __UNCHECKED void *addr, u32 value,
                            bool force_atomic) {
	u32 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 4)) {
		result = vio_addl(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 4)) {
		u32 newval;
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 4);
		libviocore_read_with_partial_overlap(self, addr, 4, &result);
		newval = result + value;
		libviocore_write_with_partial_overlap(self, addr, 4, &newval);
	} else {
		VALRDWR(addr, 4);
		if (force_atomic) {
			result = ATOMIC_FETCHADD(*(u32 *)addr, value);
		} else {
			result       = *(u32 const *)addr;
			*(u32 *)addr = result + value;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#ifdef __x86_64__
#define EMU86_MEM_ATOMIC_FETCHADDQ(addr, addend, force_atomic) \
	libviocore_atomic_fetchaddq(self, (void *)(uintptr_t)(addr), addend, force_atomic)
PRIVATE NONNULL((1)) u64 CC
libviocore_atomic_fetchaddq(struct vio_emulate_args *__restrict self,
                            __USER __UNCHECKED void *addr, u64 value,
                            bool force_atomic) {
	u64 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 8)) {
		result = vio_addq(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 8)) {
		u64 newval;
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 8);
		libviocore_read_with_partial_overlap(self, addr, 8, &result);
		newval = result + value;
		libviocore_write_with_partial_overlap(self, addr, 8, &newval);
	} else {
		VALRDWR(addr, 8);
		if (force_atomic) {
			result = ATOMIC_FETCHADD(*(u64 *)addr, value);
		} else {
			result       = *(u64 const *)addr;
			*(u64 *)addr = result + value;
		}
	}
	COMPILER_BARRIER();
	return result;
}
#endif /* __x86_64__ */

#define EMU86_MEM_ATOMIC_FETCHSUBB(addr, subend, force_atomic) \
	libviocore_atomic_fetchsubb(self, (void *)(uintptr_t)(addr), subend, force_atomic)
PRIVATE NONNULL((1)) u8 CC
libviocore_atomic_fetchsubb(struct vio_emulate_args *__restrict self,
                            __USER __UNCHECKED void *addr, u8 value,
                            bool force_atomic) {
	u8 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 1)) {
		result = vio_subb(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else {
		VALRDWR(addr, 1);
		if (force_atomic) {
			result = ATOMIC_FETCHSUB(*(u8 *)addr, value);
		} else {
			result      = *(u8 const *)addr;
			*(u8 *)addr = result - value;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_MEM_ATOMIC_FETCHSUBW(addr, subend, force_atomic) \
	libviocore_atomic_fetchsubw(self, (void *)(uintptr_t)(addr), subend, force_atomic)
PRIVATE NONNULL((1)) u16 CC
libviocore_atomic_fetchsubw(struct vio_emulate_args *__restrict self,
                            __USER __UNCHECKED void *addr, u16 value,
                            bool force_atomic) {
	u16 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 2)) {
		result = vio_subw(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 2)) {
		u16 newval;
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 2);
		libviocore_read_with_partial_overlap(self, addr, 2, &result);
		newval = result - value;
		libviocore_write_with_partial_overlap(self, addr, 2, &newval);
	} else {
		VALRDWR(addr, 2);
		if (force_atomic) {
			result = ATOMIC_FETCHSUB(*(u16 *)addr, value);
		} else {
			result       = *(u16 const *)addr;
			*(u16 *)addr = result - value;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_MEM_ATOMIC_FETCHSUBL(addr, subend, force_atomic) \
	libviocore_atomic_fetchsubl(self, (void *)(uintptr_t)(addr), subend, force_atomic)
PRIVATE NONNULL((1)) u32 CC
libviocore_atomic_fetchsubl(struct vio_emulate_args *__restrict self,
                            __USER __UNCHECKED void *addr, u32 value,
                            bool force_atomic) {
	u32 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 4)) {
		result = vio_subl(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 4)) {
		u32 newval;
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 4);
		libviocore_read_with_partial_overlap(self, addr, 4, &result);
		newval = result - value;
		libviocore_write_with_partial_overlap(self, addr, 4, &newval);
	} else {
		VALRDWR(addr, 4);
		if (force_atomic) {
			result = ATOMIC_FETCHSUB(*(u32 *)addr, value);
		} else {
			result       = *(u32 const *)addr;
			*(u32 *)addr = result - value;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#ifdef __x86_64__
#define EMU86_MEM_ATOMIC_FETCHSUBQ(addr, subend, force_atomic) \
	libviocore_atomic_fetchsubq(self, (void *)(uintptr_t)(addr), subend, force_atomic)
PRIVATE NONNULL((1)) u64 CC
libviocore_atomic_fetchsubq(struct vio_emulate_args *__restrict self,
                            __USER __UNCHECKED void *addr, u64 value,
                            bool force_atomic) {
	u64 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 8)) {
		result = vio_subq(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 8)) {
		u64 newval;
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 8);
		libviocore_read_with_partial_overlap(self, addr, 8, &result);
		newval = result - value;
		libviocore_write_with_partial_overlap(self, addr, 8, &newval);
	} else {
		VALRDWR(addr, 8);
		if (force_atomic) {
			result = ATOMIC_FETCHSUB(*(u64 *)addr, value);
		} else {
			result       = *(u64 const *)addr;
			*(u64 *)addr = result - value;
		}
	}
	COMPILER_BARRIER();
	return result;
}
#endif /* __x86_64__ */

#define EMU86_MEM_ATOMIC_FETCHANDB(addr, andend, force_atomic) \
	libviocore_atomic_fetchandb(self, (void *)(uintptr_t)(addr), andend, force_atomic)
PRIVATE NONNULL((1)) u8 CC
libviocore_atomic_fetchandb(struct vio_emulate_args *__restrict self,
                            __USER __UNCHECKED void *addr, u8 value,
                            bool force_atomic) {
	u8 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 1)) {
		result = vio_andb(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else {
		VALRDWR(addr, 1);
		if (force_atomic) {
			result = ATOMIC_FETCHAND(*(u8 *)addr, value);
		} else {
			result      = *(u8 const *)addr;
			*(u8 *)addr = result & value;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_MEM_ATOMIC_FETCHANDW(addr, andend, force_atomic) \
	libviocore_atomic_fetchandw(self, (void *)(uintptr_t)(addr), andend, force_atomic)
PRIVATE NONNULL((1)) u16 CC
libviocore_atomic_fetchandw(struct vio_emulate_args *__restrict self,
                            __USER __UNCHECKED void *addr, u16 value,
                            bool force_atomic) {
	u16 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 2)) {
		result = vio_andw(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 2)) {
		u16 newval;
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 2);
		libviocore_read_with_partial_overlap(self, addr, 2, &result);
		newval = result & value;
		libviocore_write_with_partial_overlap(self, addr, 2, &newval);
	} else {
		VALRDWR(addr, 2);
		if (force_atomic) {
			result = ATOMIC_FETCHAND(*(u16 *)addr, value);
		} else {
			result       = *(u16 const *)addr;
			*(u16 *)addr = result & value;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_MEM_ATOMIC_FETCHANDL(addr, andend, force_atomic) \
	libviocore_atomic_fetchandl(self, (void *)(uintptr_t)(addr), andend, force_atomic)
PRIVATE NONNULL((1)) u32 CC
libviocore_atomic_fetchandl(struct vio_emulate_args *__restrict self,
                            __USER __UNCHECKED void *addr, u32 value,
                            bool force_atomic) {
	u32 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 4)) {
		result = vio_andl(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 4)) {
		u32 newval;
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 4);
		libviocore_read_with_partial_overlap(self, addr, 4, &result);
		newval = result & value;
		libviocore_write_with_partial_overlap(self, addr, 4, &newval);
	} else {
		VALRDWR(addr, 4);
		if (force_atomic) {
			result = ATOMIC_FETCHAND(*(u32 *)addr, value);
		} else {
			result       = *(u32 const *)addr;
			*(u32 *)addr = result & value;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#ifdef __x86_64__
#define EMU86_MEM_ATOMIC_FETCHANDQ(addr, andend, force_atomic) \
	libviocore_atomic_fetchandq(self, (void *)(uintptr_t)(addr), andend, force_atomic)
PRIVATE NONNULL((1)) u64 CC
libviocore_atomic_fetchandq(struct vio_emulate_args *__restrict self,
                            __USER __UNCHECKED void *addr, u64 value,
                            bool force_atomic) {
	u64 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 8)) {
		result = vio_andq(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 8)) {
		u64 newval;
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 8);
		libviocore_read_with_partial_overlap(self, addr, 8, &result);
		newval = result & value;
		libviocore_write_with_partial_overlap(self, addr, 8, &newval);
	} else {
		VALRDWR(addr, 8);
		if (force_atomic) {
			result = ATOMIC_FETCHAND(*(u64 *)addr, value);
		} else {
			result       = *(u64 const *)addr;
			*(u64 *)addr = result & value;
		}
	}
	COMPILER_BARRIER();
	return result;
}
#endif /* __x86_64__ */

#define EMU86_MEM_ATOMIC_FETCHORB(addr, orend, force_atomic) \
	libviocore_atomic_fetchorb(self, (void *)(uintptr_t)(addr), orend, force_atomic)
PRIVATE NONNULL((1)) u8 CC
libviocore_atomic_fetchorb(struct vio_emulate_args *__restrict self,
                            __USER __UNCHECKED void *addr, u8 value,
                            bool force_atomic) {
	u8 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 1)) {
		result = vio_orb(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else {
		VALRDWR(addr, 1);
		if (force_atomic) {
			result = ATOMIC_FETCHOR(*(u8 *)addr, value);
		} else {
			result      = *(u8 const *)addr;
			*(u8 *)addr = result | value;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_MEM_ATOMIC_FETCHORW(addr, orend, force_atomic) \
	libviocore_atomic_fetchorw(self, (void *)(uintptr_t)(addr), orend, force_atomic)
PRIVATE NONNULL((1)) u16 CC
libviocore_atomic_fetchorw(struct vio_emulate_args *__restrict self,
                            __USER __UNCHECKED void *addr, u16 value,
                            bool force_atomic) {
	u16 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 2)) {
		result = vio_orw(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 2)) {
		u16 newval;
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 2);
		libviocore_read_with_partial_overlap(self, addr, 2, &result);
		newval = result | value;
		libviocore_write_with_partial_overlap(self, addr, 2, &newval);
	} else {
		VALRDWR(addr, 2);
		if (force_atomic) {
			result = ATOMIC_FETCHOR(*(u16 *)addr, value);
		} else {
			result       = *(u16 const *)addr;
			*(u16 *)addr = result | value;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_MEM_ATOMIC_FETCHORL(addr, orend, force_atomic) \
	libviocore_atomic_fetchorl(self, (void *)(uintptr_t)(addr), orend, force_atomic)
PRIVATE NONNULL((1)) u32 CC
libviocore_atomic_fetchorl(struct vio_emulate_args *__restrict self,
                            __USER __UNCHECKED void *addr, u32 value,
                            bool force_atomic) {
	u32 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 4)) {
		result = vio_orl(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 4)) {
		u32 newval;
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 4);
		libviocore_read_with_partial_overlap(self, addr, 4, &result);
		newval = result | value;
		libviocore_write_with_partial_overlap(self, addr, 4, &newval);
	} else {
		VALRDWR(addr, 4);
		if (force_atomic) {
			result = ATOMIC_FETCHOR(*(u32 *)addr, value);
		} else {
			result       = *(u32 const *)addr;
			*(u32 *)addr = result | value;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#ifdef __x86_64__
#define EMU86_MEM_ATOMIC_FETCHORQ(addr, orend, force_atomic) \
	libviocore_atomic_fetchorq(self, (void *)(uintptr_t)(addr), orend, force_atomic)
PRIVATE NONNULL((1)) u64 CC
libviocore_atomic_fetchorq(struct vio_emulate_args *__restrict self,
                            __USER __UNCHECKED void *addr, u64 value,
                            bool force_atomic) {
	u64 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 8)) {
		result = vio_orq(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 8)) {
		u64 newval;
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 8);
		libviocore_read_with_partial_overlap(self, addr, 8, &result);
		newval = result | value;
		libviocore_write_with_partial_overlap(self, addr, 8, &newval);
	} else {
		VALRDWR(addr, 8);
		if (force_atomic) {
			result = ATOMIC_FETCHOR(*(u64 *)addr, value);
		} else {
			result       = *(u64 const *)addr;
			*(u64 *)addr = result | value;
		}
	}
	COMPILER_BARRIER();
	return result;
}
#endif /* __x86_64__ */

#define EMU86_MEM_ATOMIC_FETCHXORB(addr, xorend, force_atomic) \
	libviocore_atomic_fetchxorb(self, (void *)(uintptr_t)(addr), xorend, force_atomic)
PRIVATE NONNULL((1)) u8 CC
libviocore_atomic_fetchxorb(struct vio_emulate_args *__restrict self,
                            __USER __UNCHECKED void *addr, u8 value,
                            bool force_atomic) {
	u8 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 1)) {
		result = vio_xorb(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else {
		VALRDWR(addr, 1);
		if (force_atomic) {
			result = ATOMIC_FETCHXOR(*(u8 *)addr, value);
		} else {
			result      = *(u8 const *)addr;
			*(u8 *)addr = result ^ value;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_MEM_ATOMIC_FETCHXORW(addr, xorend, force_atomic) \
	libviocore_atomic_fetchxorw(self, (void *)(uintptr_t)(addr), xorend, force_atomic)
PRIVATE NONNULL((1)) u16 CC
libviocore_atomic_fetchxorw(struct vio_emulate_args *__restrict self,
                            __USER __UNCHECKED void *addr, u16 value,
                            bool force_atomic) {
	u16 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 2)) {
		result = vio_xorw(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 2)) {
		u16 newval;
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 2);
		libviocore_read_with_partial_overlap(self, addr, 2, &result);
		newval = result ^ value;
		libviocore_write_with_partial_overlap(self, addr, 2, &newval);
	} else {
		VALRDWR(addr, 2);
		if (force_atomic) {
			result = ATOMIC_FETCHXOR(*(u16 *)addr, value);
		} else {
			result       = *(u16 const *)addr;
			*(u16 *)addr = result ^ value;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_MEM_ATOMIC_FETCHXORL(addr, xorend, force_atomic) \
	libviocore_atomic_fetchxorl(self, (void *)(uintptr_t)(addr), xorend, force_atomic)
PRIVATE NONNULL((1)) u32 CC
libviocore_atomic_fetchxorl(struct vio_emulate_args *__restrict self,
                            __USER __UNCHECKED void *addr, u32 value,
                            bool force_atomic) {
	u32 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 4)) {
		result = vio_xorl(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 4)) {
		u32 newval;
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 4);
		libviocore_read_with_partial_overlap(self, addr, 4, &result);
		newval = result ^ value;
		libviocore_write_with_partial_overlap(self, addr, 4, &newval);
	} else {
		VALRDWR(addr, 4);
		if (force_atomic) {
			result = ATOMIC_FETCHXOR(*(u32 *)addr, value);
		} else {
			result       = *(u32 const *)addr;
			*(u32 *)addr = result ^ value;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#ifdef __x86_64__
#define EMU86_MEM_ATOMIC_FETCHXORQ(addr, xorend, force_atomic) \
	libviocore_atomic_fetchxorq(self, (void *)(uintptr_t)(addr), xorend, force_atomic)
PRIVATE NONNULL((1)) u64 CC
libviocore_atomic_fetchxorq(struct vio_emulate_args *__restrict self,
                            __USER __UNCHECKED void *addr, u64 value,
                            bool force_atomic) {
	u64 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 8)) {
		result = vio_xorq(&self->vea_args, GET_VIO_ADDR(self, addr), value, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 8)) {
		u64 newval;
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 8);
		libviocore_read_with_partial_overlap(self, addr, 8, &result);
		newval = result ^ value;
		libviocore_write_with_partial_overlap(self, addr, 8, &newval);
	} else {
		VALRDWR(addr, 8);
		if (force_atomic) {
			result = ATOMIC_FETCHXOR(*(u64 *)addr, value);
		} else {
			result       = *(u64 const *)addr;
			*(u64 *)addr = result ^ value;
		}
	}
	COMPILER_BARRIER();
	return result;
}
#endif /* __x86_64__ */

#define EMU86_MEM_ATOMIC_CMPXCHB(addr, oldval, newval, force_atomic) \
	libviocore_atomic_cmpxchb(self, (void *)(uintptr_t)(addr), oldval, newval, force_atomic)
PRIVATE NONNULL((1)) u8 CC
libviocore_atomic_cmpxchb(struct vio_emulate_args *__restrict self,
                          __USER __UNCHECKED void *addr,
                          u8 oldval, u8 newval, bool force_atomic) {
	u8 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 1)) {
		result = vio_cmpxchb(&self->vea_args, GET_VIO_ADDR(self, addr), oldval, newval, force_atomic);
	} else {
		VALRDWR(addr, 1);
		if (force_atomic) {
			result = ATOMIC_CMPXCH(*(u8 *)addr, oldval, newval);
		} else {
			result = *(u8 const *)addr;
			COMPILER_READ_BARRIER();
			if (result == oldval)
				*(u8 *)addr = newval;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_MEM_ATOMIC_CMPXCHW(addr, oldval, newval, force_atomic) \
	libviocore_atomic_cmpxchw(self, (void *)(uintptr_t)(addr), oldval, newval, force_atomic)
PRIVATE NONNULL((1)) u16 CC
libviocore_atomic_cmpxchw(struct vio_emulate_args *__restrict self,
                          __USER __UNCHECKED void *addr,
                          u16 oldval, u16 newval, bool force_atomic) {
	u16 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 2)) {
		result = vio_cmpxchw(&self->vea_args, GET_VIO_ADDR(self, addr), oldval, newval, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 2)) {
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 2);
		libviocore_read_with_partial_overlap(self, addr, 2, &result);
		if (result == oldval)
			libviocore_write_with_partial_overlap(self, addr, 2, &newval);
	} else {
		VALRDWR(addr, 2);
		if (force_atomic) {
			result = ATOMIC_CMPXCH(*(u16 *)addr, oldval, newval);
		} else {
			result = *(u16 const *)addr;
			COMPILER_READ_BARRIER();
			if (result == oldval)
				*(u16 *)addr = newval;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_MEM_ATOMIC_CMPXCHL(addr, oldval, newval, force_atomic) \
	libviocore_atomic_cmpxchl(self, (void *)(uintptr_t)(addr), oldval, newval, force_atomic)
PRIVATE NONNULL((1)) u32 CC
libviocore_atomic_cmpxchl(struct vio_emulate_args *__restrict self,
                          __USER __UNCHECKED void *addr,
                          u32 oldval, u32 newval, bool force_atomic) {
	u32 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 4)) {
		result = vio_cmpxchl(&self->vea_args, GET_VIO_ADDR(self, addr), oldval, newval, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 4)) {
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 4);
		libviocore_read_with_partial_overlap(self, addr, 4, &result);
		if (result == oldval)
			libviocore_write_with_partial_overlap(self, addr, 4, &newval);
	} else {
		VALRDWR(addr, 4);
		if (force_atomic) {
			result = ATOMIC_CMPXCH(*(u32 *)addr, oldval, newval);
		} else {
			result = *(u32 const *)addr;
			COMPILER_READ_BARRIER();
			if (result == oldval)
				*(u32 *)addr = newval;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_MEM_ATOMIC_CMPXCHQ(addr, oldval, newval, force_atomic) \
	libviocore_atomic_cmpxchq(self, (void *)(uintptr_t)(addr), oldval, newval, force_atomic)
PRIVATE NONNULL((1)) u64 CC
libviocore_atomic_cmpxchq(struct vio_emulate_args *__restrict self,
                          __USER __UNCHECKED void *addr,
                          u64 oldval, u64 newval, bool force_atomic) {
	u64 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 8)) {
		result = vio_cmpxchq(&self->vea_args, GET_VIO_ADDR(self, addr), oldval, newval, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 8)) {
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 8);
		libviocore_read_with_partial_overlap(self, addr, 8, &result);
		if (result == oldval)
			libviocore_write_with_partial_overlap(self, addr, 8, &newval);
	} else {
		VALRDWR(addr, 8);
		if (force_atomic) {
			result = ATOMIC_CMPXCH(*(u64 *)addr, oldval, newval);
		} else {
			result = *(u64 const *)addr;
			COMPILER_READ_BARRIER();
			if (result == oldval)
				*(u64 *)addr = newval;
		}
	}
	COMPILER_BARRIER();
	return result;
}

#if 0 /* Unused... */
#define EMU86_MEM_ATOMIC_CMPXCH_OR_WRITEB(addr, oldval, newval, force_atomic) \
	libviocore_atomic_cmpxch_or_writeb(self, (void *)(uintptr_t)(addr), oldval, newval, force_atomic)
PRIVATE NONNULL((1)) bool CC
libviocore_atomic_cmpxch_or_writeb(struct vio_emulate_args *__restrict self,
                                   __USER __UNCHECKED void *addr,
                                   u8 oldval, u8 newval, bool force_atomic) {
	u8 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 1)) {
		result = vio_cmpxch_or_writeb(&self->vea_args, GET_VIO_ADDR(self, addr), oldval, newval, force_atomic);
	} else {
		VALRDWR(addr, 1);
		if (force_atomic) {
			result = ATOMIC_CMPXCH(*(u8 *)addr, oldval, newval);
		} else {
			*(u8 *)addr = newval;
			return true;
		}
	}
	COMPILER_BARRIER();
	return result == oldval;
}
#else
#define EMU86_MEM_ATOMIC_CMPXCH_OR_WRITEB(addr, oldval, newval, force_atomic) DONT_USE
#endif

#define EMU86_MEM_ATOMIC_CMPXCH_OR_WRITEW(addr, oldval, newval, force_atomic) \
	libviocore_atomic_cmpxch_or_writew(self, (void *)(uintptr_t)(addr), oldval, newval, force_atomic)
PRIVATE NONNULL((1)) bool CC
libviocore_atomic_cmpxch_or_writew(struct vio_emulate_args *__restrict self,
                                   __USER __UNCHECKED void *addr,
                                   u16 oldval, u16 newval, bool force_atomic) {
	u16 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 2)) {
		result = vio_cmpxch_or_writew(&self->vea_args, GET_VIO_ADDR(self, addr), oldval, newval, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 2)) {
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 2);
		libviocore_write_with_partial_overlap(self, addr, 2, &newval);
		return true;
	} else {
		VALRDWR(addr, 2);
		if (force_atomic) {
			result = ATOMIC_CMPXCH(*(u16 *)addr, oldval, newval);
		} else {
			*(u16 *)addr = newval;
			return true;
		}
	}
	COMPILER_BARRIER();
	return result == oldval;
}

#define EMU86_MEM_ATOMIC_CMPXCH_OR_WRITEL(addr, oldval, newval, force_atomic) \
	libviocore_atomic_cmpxch_or_writel(self, (void *)(uintptr_t)(addr), oldval, newval, force_atomic)
PRIVATE NONNULL((1)) bool CC
libviocore_atomic_cmpxch_or_writel(struct vio_emulate_args *__restrict self,
                                   __USER __UNCHECKED void *addr,
                                   u32 oldval, u32 newval, bool force_atomic) {
	u32 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 4)) {
		result = vio_cmpxch_or_writel(&self->vea_args, GET_VIO_ADDR(self, addr), oldval, newval, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 4)) {
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 4);
		libviocore_write_with_partial_overlap(self, addr, 4, &newval);
		return true;
	} else {
		VALRDWR(addr, 4);
		if (force_atomic) {
			result = ATOMIC_CMPXCH(*(u32 *)addr, oldval, newval);
		} else {
			*(u32 *)addr = newval;
			return true;
		}
	}
	COMPILER_BARRIER();
	return result == oldval;
}

#ifdef __x86_64__
#define EMU86_MEM_ATOMIC_CMPXCH_OR_WRITEQ(addr, oldval, newval, force_atomic) \
	libviocore_atomic_cmpxch_or_writeq(self, (void *)(uintptr_t)(addr), oldval, newval, force_atomic)
PRIVATE NONNULL((1)) u64 CC
libviocore_atomic_cmpxch_or_writeq(struct vio_emulate_args *__restrict self,
                                   __USER __UNCHECKED void *addr,
                                   u64 oldval, u64 newval, bool force_atomic) {
	u64 result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 8)) {
		result = vio_cmpxch_or_writeq(&self->vea_args, GET_VIO_ADDR(self, addr), oldval, newval, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 8)) {
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 8);
		libviocore_write_with_partial_overlap(self, addr, 8, &newval);
		return true;
	} else {
		VALRDWR(addr, 8);
		if (force_atomic) {
			result = ATOMIC_CMPXCH(*(u64 *)addr, oldval, newval);
		} else {
			*(u64 *)addr = newval;
			return true;
		}
	}
	COMPILER_BARRIER();
	return result == oldval;
}

#define EMU86_MEM_ATOMIC_CMPXCHX(addr, oldval, newval, force_atomic) \
	libviocore_atomic_cmpxchx(self, addr, oldval, newval, force_atomic)
PRIVATE NONNULL((1)) uint128_t CC
libviocore_atomic_cmpxchx(struct vio_emulate_args *__restrict self,
                          __USER __UNCHECKED void *addr,
                          uint128_t oldval, uint128_t newval, bool force_atomic) {
	uint128_t result;
	COMPILER_BARRIER();
	if likely(IS_VIO_ADDR_FULL(self, addr, 16)) {
		result = vio_cmpxchx(&self->vea_args, GET_VIO_ADDR(self, addr), oldval, newval, force_atomic);
	} else if unlikely(IS_VIO_ADDR_PART(self, addr, 16)) {
		if unlikely(force_atomic)
			THROW(E_SEGFAULT_UNALIGNED, addr, E_SEGFAULT_CONTEXT_VIO, 16);
		libviocore_read_with_partial_overlap(self, addr, 16, &result);
		if (uint128_eq128(result, oldval))
			libviocore_write_with_partial_overlap(self, addr, 16, &newval);
	} else {
		VALRDWR(addr, 16);
		if (force_atomic) {
			result = __lock_cmpxchg16b((uint128_t *)addr, oldval, newval);
		} else {
			result = *(uint128_t *)addr;
			COMPILER_READ_BARRIER();
			if (uint128_eq128(result, oldval))
				*(uint128_t *)addr = newval;
		}
	}
	COMPILER_BARRIER();
	return result;
}
#endif /* __x86_64__ */





#define EMU86_EMULATE_DECL         INTERN
#define EMU86_EMULATE_ATTR         NONNULL((1))
#define EMU86_EMULATE_RETURN()     return
#define EMU86_EMULATE_RETURN_TYPE  void
#define EMU86_EMULATE_NOTHROW      /* nothing */
#define EMU86_EMULATE_CC           CC
#define EMU86_EMULATE_NAME         libviocore_emulate
#define EMU86_EMULATE_ARGS         struct vio_emulate_args *__restrict self
#define EMU86_EMULATE_HELPER_ATTR  NONNULL((1))
#define EMU86_EMULATE_HELPER_ARGS  struct vio_emulate_args *__restrict self
#define EMU86_EMULATE_HELPER_PARAM self
#define EMU86_EMULATE_TRY_SWITCH \
	TRY
#define EMU86_EMULATE_EXCEPT_SWITCH                                     \
	EXCEPT {                                                            \
		libviocore_complete_except(self, _EMU86_GETOPCODE(), op_flags); \
	}
#define EMU86_EMULATE_GETOPFLAGS() _CS(emu86_opflags_from)(self->vea_args.va_state)
#if defined(__x86_64__) || defined(__I386_NO_VM86)
#define EMU86_EMULATE_CONFIG_VM86 0
#else /* __x86_64__ || __I386_NO_VM86 */
#define EMU86_EMULATE_CONFIG_VM86 1
#define EMU86_EMULATE_VM86_GETIF()  0       /* TODO: Get vm86 #IF bit */
#define EMU86_EMULATE_VM86_SETIF(v) (void)0 /* TODO: Set vm86 #IF bit */
/* TODO: vm86 I/O functions (used by ins and outs) */
#endif /* !__x86_64__ && !__I386_NO_VM86 */

#ifdef __KERNEL__
#define EMU86_EMULATE_CONFIG_CHECKUSER 1
#define EMU86_ISUSER()        icpustate_isuser(self->vea_args.va_state)
#if EMU86_EMULATE_CONFIG_VM86
#define EMU86_ISUSER_NOVM86() icpustate_isuser_novm86(self->vea_args.va_state)
#define EMU86_ISVM86()        icpustate_isvm86(self->vea_args.va_state)
#else /* EMU86_EMULATE_CONFIG_VM86 */
#define EMU86_ISUSER_NOVM86() icpustate_isuser(self->vea_args.va_state)
#define EMU86_ISVM86()        0
#endif /* !EMU86_EMULATE_CONFIG_VM86 */
#else /* __KERNEL__ */
#define EMU86_EMULATE_CONFIG_CHECKUSER 0
#define EMU86_ISUSER() 0
#define EMU86_ISUSER_NOVM86() 0
#define EMU86_ISVM86() 0
#endif /* !__KERNEL__ */
#define EMU86_VALIDATE_READABLE(addr, num_bytes)  (void)0 /* read/write validation is performed on a per-access basis */
#define EMU86_VALIDATE_WRITABLE(addr, num_bytes)  (void)0 /* read/write validation is performed on a per-access basis */
#define EMU86_VALIDATE_READWRITE(addr, num_bytes) (void)0 /* read/write validation is performed on a per-access basis */
#define EMU86_VALIDATE_READABLE_IS_NOOP 1
#define EMU86_VALIDATE_WRITABLE_IS_NOOP 1
#define EMU86_VALIDATE_READWRITE_IS_NOOP 1
#define EMU86_GETFLAGS()            CS(getpflags)(self->vea_args.va_state)
#define EMU86_SETFLAGS(v)           CS(setpflags)(self->vea_args.va_state, v)
#define EMU86_MSKFLAGS(mask, value) CS(mskpflags)(self->vea_args.va_state, mask, value)
#define EMU86_GETIPREG()            CS(getpc)(self->vea_args.va_state)
#define EMU86_SETIPREG(v)           CS(setpc)(self->vea_args.va_state, (__uintptr_t)(v))
#define EMU86_GETPCPTR()            (byte_t *)EMU86_GETIPREG()
#define EMU86_SETPCPTR(v)           EMU86_SETIPREG(v)
#define EMU86_GETIP()               (u16)EMU86_GETIPREG()
#define EMU86_SETIP(v)              EMU86_SETIPREG((u16)(v))
#define EMU86_GETEIP()              (u32)EMU86_GETIPREG()
#define EMU86_SETEIP(v)             EMU86_SETIPREG((u32)(v))
#ifdef __x86_64__
#define EMU86_GETRIP()              (u64)EMU86_GETIPREG()
#define EMU86_SETRIP(v)             EMU86_SETIPREG((u64)(v))
#endif /* __x86_64__ */

#if defined(__x86_64__) || !defined(__KERNEL__)
#define EMU86_GETSS()     CS(getss)(self->vea_args.va_state)
#define EMU86_SETSS(v)    CS(setss)(self->vea_args.va_state, v)
#define EMU86_GETSPREG()  CS(getpsp)(self->vea_args.va_state)
#define EMU86_SETSPREG(v) CS(setpsp)(self->vea_args.va_state, v)
#else /* __x86_64__ */
#define EMU86_EMULATE_SETUP()          \
	do {                               \
		self->vea_kernel_override = 0; \
	}	__WHILE0
#define EMU86_GETSS()                                                   \
	((self->vea_kernel_override & VIO_EMULATE_ARGS_386_KERNEL_SS_VALID) \
	 ? self->vea_kernel_esp_override                                    \
	 : icpustate32_getss(self->vea_args.va_state))
#define EMU86_GETSPREG()                                                 \
	((self->vea_kernel_override & VIO_EMULATE_ARGS_386_KERNEL_ESP_VALID) \
	 ? self->vea_kernel_esp_override                                     \
	 : icpustate32_getesp(self->vea_args.va_state))
#define EMU86_SETSS(v)                                                            \
	(icpustate32_trysetss(self->vea_args.va_state, v)                             \
	 ? (void)(self->vea_kernel_override &= ~VIO_EMULATE_ARGS_386_KERNEL_SS_VALID) \
	 : (void)(self->vea_kernel_ss_override = (v),                                 \
	          self->vea_kernel_override |= VIO_EMULATE_ARGS_386_KERNEL_SS_VALID))
#define EMU86_SETSPREG(v)                                                          \
	(icpustate32_trysetesp(self->vea_args.va_state, v)                             \
	 ? (void)(self->vea_kernel_override &= ~VIO_EMULATE_ARGS_386_KERNEL_ESP_VALID) \
	 : (void)(self->vea_kernel_esp_override = (v),                                 \
	          self->vea_kernel_override |= VIO_EMULATE_ARGS_386_KERNEL_ESP_VALID))
#endif /* !__x86_64__ */

#undef EMU86_GETSEGBASE_IS_NOOP
#undef EMU86_GETSEGBASE_IS_NOOP_DS
#undef EMU86_GETSEGBASE_IS_NOOP_ES
#undef EMU86_GETSEGBASE_IS_NOOP_CS
#undef EMU86_GETSEGBASE_IS_NOOP_SS
#undef EMU86_GETSEGBASE_IS_NOOP_FS
#undef EMU86_GETSEGBASE_IS_NOOP_GS

#ifdef __KERNEL__
#ifdef __x86_64__
/* x86_64 only supports a flat address space for es, cs, ss, and ds */
#define EMU86_GETSEGBASE_IS_NOOP_ES 1
#define EMU86_GETSEGBASE_IS_NOOP_CS 1
#define EMU86_GETSEGBASE_IS_NOOP_SS 1
#define EMU86_GETSEGBASE_IS_NOOP_DS 1
#define EMU86_GETSEGBASE(segment_regno)          \
	((segment_regno) == EMU86_R_FS               \
	 ? __rdfsbase()                              \
	 : (segment_regno) == EMU86_R_GS             \
	   ? (EMU86_ISUSER()                         \
	      ? (void *)__rdmsr(IA32_KERNEL_GS_BASE) \
	      : __rdgsbase())                        \
	   : 0)
#define EMU86_GETDSBASE() 0
#define EMU86_GETESBASE() 0
#define EMU86_GETCSBASE() 0
#define EMU86_GETSSBASE() 0
#define EMU86_GETFSBASE() __rdfsbase()
#define EMU86_GETGSBASE() (EMU86_ISUSER() ? (void *)__rdmsr(IA32_KERNEL_GS_BASE) : __rdgsbase())
#else /* __x86_64__ */
DECL_END

#include <kernel/x86/gdt.h> /* x86_get_user_(fs|gs)base() */

#include <sched/task.h>

DECL_BEGIN

/* 32-bit mode supports non-zero bases for any segment! */
#define EMU86_GETSEGBASE(segment_regno) \
	i386_getsegment_base(self->vea_args.va_state, segment_regno)
#define EMU86_GETDSBASE() EMU86_GETSEGBASE(EMU86_R_DS)
#define EMU86_GETESBASE() EMU86_GETSEGBASE(EMU86_R_ES)
#define EMU86_GETCSBASE() EMU86_GETSEGBASE(EMU86_R_CS)
#define EMU86_GETSSBASE() EMU86_GETSEGBASE(EMU86_R_SS)
#define EMU86_GETFSBASE() EMU86_GETSEGBASE(EMU86_R_FS)
#define EMU86_GETGSBASE() EMU86_GETSEGBASE(EMU86_R_GS)
PRIVATE WUNUSED NONNULL((1)) u32 CC
i386_getsegment_base(struct icpustate32 *__restrict state,
                     u8 segment_regno) {
	u32 result;
	u16 segment_index;
	preemption_flag_t was;
	struct segment *seg;
	struct desctab dt;

#ifndef __I386_NO_VM86
	if (icpustate_isvm86(state)) {
		switch (segment_regno) {
		case EMU86_R_ES: segment_index = icpustate32_getes_vm86(state); break;
		case EMU86_R_CS: segment_index = icpustate32_getcs(state); break;
		case EMU86_R_SS: segment_index = icpustate32_getss(state); break;
		case EMU86_R_DS: segment_index = icpustate32_getds_vm86(state); break;
		case EMU86_R_FS: segment_index = icpustate32_getfs_vm86(state); break;
		case EMU86_R_GS: segment_index = icpustate32_getgs_vm86(state); break;
		default: __builtin_unreachable();
		}
		return segment_index << 4;
	}
#endif /* !__I386_NO_VM86 */

	/* Determine the segment's index. */
	switch (segment_regno) {
	case EMU86_R_ES: segment_index = icpustate_getes_novm86(state); break;
	case EMU86_R_CS: segment_index = icpustate_getcs(state); break;
	case EMU86_R_SS: segment_index = icpustate_getss(state); break;
	case EMU86_R_DS: segment_index = icpustate_getds_novm86(state); break;
	case EMU86_R_FS: segment_index = icpustate_getfs_novm86(state); break;
	case EMU86_R_GS: segment_index = icpustate_getgs_novm86(state); break;
	default: __builtin_unreachable();
	}

	/* Handle known segment indices without disabling preemption. */
	switch (segment_index & ~3) {

	case SEGMENT_KERNEL_CODE:
	case SEGMENT_KERNEL_DATA:
	case SEGMENT_USER_CODE32:
	case SEGMENT_USER_DATA32:
		return 0;

	case SEGMENT_KERNEL_FSBASE:
		return (u32)THIS_TASK;

	case SEGMENT_USER_FSBASE:
		return x86_get_user_fsbase();

	case SEGMENT_USER_GSBASE:
		return x86_get_user_gsbase();

	default:
		break;
	}

	preemption_pushoff(&was);
	__sgdt(&dt);
	if (segment_index & 4) {
		/* LDT index. */
		u16 ldt = __sldt() & ~7;
		if unlikely(!ldt || ldt > dt.dt_limit) {
			preemption_pop(&was);
			/* Deal with an invalid / disabled LDT by throwing an error indicating an invalid LDT. */
			THROW(E_ILLEGAL_INSTRUCTION_REGISTER,
			      0,                                    /* opcode */
			      0,                                    /* op_flags */
			      E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD, /* what */
			      X86_REGISTER_MISC_LDT,                /* regno */
			      0,                                    /* offset */
			      ldt);                                 /* regval */
		}
		seg = (struct segment *)((byte_t *)dt.dt_base + ldt);
		dt.dt_base  = segment_rdbaseX(seg);
		dt.dt_limit = (uint16_t)segment_rdlimit(seg);
	}
	segment_index &= ~7;
	if (!segment_index || segment_index > dt.dt_limit) {
		preemption_pop(&was);
		THROW(E_ILLEGAL_INSTRUCTION_REGISTER,
		      0,                                       /* opcode */
		      0,                                       /* op_flags */
		      E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD,    /* what */
		      X86_REGISTER_SEGMENT_ES + segment_regno, /* regno */
		      0,                                       /* offset */
		      segment_index);                          /* regval */
	}
	seg = (struct segment *)((byte_t *)dt.dt_base + segment_index);
	result = segment_rdbaseX(seg);
	preemption_pop(&was);
	return result;
}

#if 1 /* Unused */
#define EMU86_SETFSBASE(v) unused_feature;
#define EMU86_SETGSBASE(v) unused_feature;
#else /* Unused */
#define EMU86_SETFSBASE(v) i386_setsegment_base(self->vea_args.va_state, EMU86_R_FS, (u32)(v))
#define EMU86_SETGSBASE(v) i386_setsegment_base(self->vea_args.va_state, EMU86_R_GS, (u32)(v))
PRIVATE WUNUSED NONNULL((1)) void CC
i386_setsegment_base(struct icpustate32 *__restrict state,
                     u8 segment_regno, u32 value) {
	u16 segment_index;

	/* Determine the segment's index. */
	switch (segment_regno) {
	case EMU86_R_ES: segment_index = icpustate_getes(state); break;
	case EMU86_R_CS: segment_index = icpustate_getcs(state); break;
	case EMU86_R_SS: segment_index = icpustate_getss(state); break;
	case EMU86_R_DS: segment_index = icpustate_getds(state); break;
	case EMU86_R_FS: segment_index = icpustate_getfs(state); break;
	case EMU86_R_GS: segment_index = icpustate_getgs(state); break;
	default: __builtin_unreachable();
	}

	/* Only the user fs/gs base register can be modified. */
	switch (segment_index & ~3) {

	case SEGMENT_USER_FSBASE:
		x86_set_user_fsbase(value);
		break;

	case SEGMENT_USER_GSBASE:
		x86_set_user_gsbase(value);
		break;

	default:
		/* Not allowed. */
		THROW(E_ILLEGAL_INSTRUCTION_REGISTER,
		      0,                                       /* opcode */
		      0,                                       /* op_flags */
		      E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,    /* how */
		      X86_REGISTER_SEGMENT_ES + segment_regno, /* regno */
		      value,                                   /* offset */
		      segment_index);                          /* regval */
		break;
	}

	/* Reload manually if user-space %gs was modified.
	 * All other register get automatically reloaded upon return to user-space. */
	if (segment_regno == EMU86_R_GS)
		__wrgs(segment_index);
}
#endif

#endif /* !__x86_64__ */
#else /* __KERNEL__ */

/* If  the base of any of these  segments wasn't 0, then this library
 * couldn't even work (since C expects a flat address space, and this
 * library is written in C) */
#define EMU86_GETSEGBASE_IS_NOOP_ES 1
#define EMU86_GETSEGBASE_IS_NOOP_CS 1
#define EMU86_GETSEGBASE_IS_NOOP_SS 1
#define EMU86_GETSEGBASE_IS_NOOP_DS 1
#define EMU86_GETSEGBASE(segment_regno) \
	((segment_regno) == EMU86_R_FS      \
	 ? __rdfsbase()                     \
	 : (segment_regno) == EMU86_R_GS    \
	   ? __rdgsbase()                   \
	   : 0)
#define EMU86_GETDSBASE()  0
#define EMU86_GETESBASE()  0
#define EMU86_GETCSBASE()  0
#define EMU86_GETSSBASE()  0
#define EMU86_GETFSBASE()  __rdfsbase()
#define EMU86_GETGSBASE()  __rdgsbase()
#define EMU86_SETFSBASE(v) __wrfsbase((void *)(uintptr_t)(v))
#define EMU86_SETGSBASE(v) __wrgsbase((void *)(uintptr_t)(v))
#endif /* !__KERNEL__ */
#define EMU86_SEGADDR(segbase, segoffset) (byte_t *)(uintptr_t)((segbase) + (segoffset))
#ifdef EMU86_GETSEGBASE_IS_NOOP_SS
#define EMU86_GETSTACKPTR()  (byte_t *)EMU86_GETSPREG()
#define EMU86_SETSTACKPTR(v) EMU86_SETSPREG((uintptr_t)(v))
#else /* EMU86_GETSEGBASE_IS_NOOP_SS */
#define EMU86_GETSTACKPTR()  EMU86_SEGADDR(EMU86_GETSSBASE(), EMU86_GETSPREG())
#define EMU86_SETSTACKPTR(v) EMU86_SETSPREG((uintptr_t)(v) - EMU86_GETSSBASE())
#endif /* !EMU86_GETSEGBASE_IS_NOOP_SS */
#define EMU86_GETES()  CS(getes)(self->vea_args.va_state)
#define EMU86_SETES(v) CS(setes)(self->vea_args.va_state, v)
#define EMU86_GETCS()  CS(getcs)(self->vea_args.va_state)
#define EMU86_SETCS(v) CS(setcs)(self->vea_args.va_state, v)
#define EMU86_GETDS()  CS(getds)(self->vea_args.va_state)
#define EMU86_SETDS(v) CS(setds)(self->vea_args.va_state, v)
#define EMU86_GETFS()  CS(getfs)(self->vea_args.va_state)
#define EMU86_SETFS(v) CS(setfs)(self->vea_args.va_state, v)
#define EMU86_GETGS()  CS(getgs)(self->vea_args.va_state)
#define EMU86_SETGS(v) CS(setgs)(self->vea_args.va_state, v)
#define EMU86_EMULATE_PUSH(new_sp, num_bytes) (void)0
#define EMU86_EMULATE_POP(old_sp, num_bytes) (void)0
#if !defined(__x86_64__) && defined(__KERNEL__)
/* Simplifications for accessing VM86 registers. */
#define EMU86_GETCS_VM86()   (self->vea_args.va_state->ics_irregs_v.ir_cs16)
#define EMU86_SETCS_VM86(v)  (self->vea_args.va_state->ics_irregs_v.ir_cs = (u16)(v))
#define EMU86_GETESP_VM86()  (self->vea_args.va_state->ics_irregs_v.ir_esp)
#define EMU86_SETESP_VM86(v) (self->vea_args.va_state->ics_irregs_v.ir_esp = (u32)(v))
#define EMU86_GETSS_VM86()   (self->vea_args.va_state->ics_irregs_v.ir_ss16)
#define EMU86_SETSS_VM86(v)  (self->vea_args.va_state->ics_irregs_v.ir_ss = (u16)(v))
#define EMU86_GETES_VM86()   (self->vea_args.va_state->ics_irregs_v.ir_es16)
#define EMU86_SETES_VM86(v)  (self->vea_args.va_state->ics_irregs_v.ir_es = (u16)(v))
#define EMU86_GETDS_VM86()   (self->vea_args.va_state->ics_irregs_v.ir_ds16)
#define EMU86_SETDS_VM86(v)  (self->vea_args.va_state->ics_irregs_v.ir_ds = (u16)(v))
#define EMU86_GETFS_VM86()   (self->vea_args.va_state->ics_irregs_v.ir_fs16)
#define EMU86_SETFS_VM86(v)  (self->vea_args.va_state->ics_irregs_v.ir_fs = (u16)(v))
#define EMU86_GETGS_VM86()   (self->vea_args.va_state->ics_irregs_v.ir_gs16)
#define EMU86_SETGS_VM86(v)  (self->vea_args.va_state->ics_irregs_v.ir_gs = (u16)(v))
#endif /* !__x86_64__ && __KERNEL__ */


#ifdef __x86_64__
#define X86_GPREGCOUNT 16
#else /* __x86_64__ */
#define X86_GPREGCOUNT 8
#endif /* !__x86_64__ */

#ifdef __KERNEL__
#ifdef __x86_64__
PRIVATE u8 const CS_breg_offsets[16] = {
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
PRIVATE u8 const CS_reg_offsets[16] = {
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
PRIVATE u8 const CS_breg_offsets[8] = {
	/* [EMU86_R_AL] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX,     /* %al */
	/* [EMU86_R_CL] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ECX,     /* %cl */
	/* [EMU86_R_DL] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDX,     /* %dl */
	/* [EMU86_R_BL] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBX,     /* %bl */
	/* [EMU86_R_AH] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX + 1, /* %ah */
	/* [EMU86_R_CH] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ECX + 1, /* %ch */
	/* [EMU86_R_DH] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDX + 1, /* %dh */
	/* [EMU86_R_BH] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBX + 1, /* %bh */
};
PRIVATE u8 const CS_reg_offsets[8] = {
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
#else /* __KERNEL__ */
PRIVATE u8 const CS_breg_offsets[X86_GPREGCOUNT] = {
	/* [EMU86_R_AL] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PAX,     /* %al */
	/* [EMU86_R_CL] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PCX,     /* %cl */
	/* [EMU86_R_DL] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PDX,     /* %dl */
	/* [EMU86_R_BL] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PBX,     /* %bl */
	/* [EMU86_R_AH] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PAX + 1, /* %ah */
	/* [EMU86_R_CH] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PCX + 1, /* %ch */
	/* [EMU86_R_DH] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PDX + 1, /* %dh */
	/* [EMU86_R_BH] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PBX + 1, /* %bh */
#ifdef __x86_64__
	/* [EMU86_R_R8L]  = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R8,    /* %r8l */
	/* [EMU86_R_R9L]  = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R9,    /* %r9l */
	/* [EMU86_R_R10L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R10,   /* %r10l */
	/* [EMU86_R_R11L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R11,   /* %r11l */
	/* [EMU86_R_R12L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R12,   /* %r12l */
	/* [EMU86_R_R13L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R13,   /* %r13l */
	/* [EMU86_R_R14L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R14,   /* %r14l */
	/* [EMU86_R_R15L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R15,   /* %r15l */
#endif /* __x86_64__ */
};
PRIVATE u8 const CS_reg_offsets[X86_GPREGCOUNT] = {
	/* [EMU86_R_EAX] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PAX,  /* %(e|r)ax */
	/* [EMU86_R_ECX] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PCX,  /* %(e|r)cx */
	/* [EMU86_R_EDX] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PDX,  /* %(e|r)dx */
	/* [EMU86_R_EBX] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PBX,  /* %(e|r)bx */
	/* [EMU86_R_ESP] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PSP,  /* %(e|r)sp */
	/* [EMU86_R_EBP] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PBP,  /* %(e|r)bp */
	/* [EMU86_R_ESI] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PSI,  /* %(e|r)si */
	/* [EMU86_R_EDI] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PDI,  /* %(e|r)di */
#ifdef __x86_64__
	/* [EMU86_R_R8L]  = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R8,  /* %r8 */
	/* [EMU86_R_R9L]  = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R9,  /* %r9 */
	/* [EMU86_R_R10L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R10, /* %r10 */
	/* [EMU86_R_R11L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R11, /* %r11 */
	/* [EMU86_R_R12L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R12, /* %r12 */
	/* [EMU86_R_R13L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R13, /* %r13 */
	/* [EMU86_R_R14L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R14, /* %r14 */
	/* [EMU86_R_R15L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R15, /* %r15 */
#endif /* __x86_64__ */
};
#endif /* !__KERNEL__ */


#ifdef __x86_64__
#define EMU86_GETREGB(regno, op_flags) \
	CS_getregb(self->vea_args.va_state, regno, op_flags)
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) u8
NOTHROW(CC CS_getregb)(vio_cpustate_t const *__restrict state,
                       u8 regno, emu86_opflags_t op_flags) {
	regno &= (X86_GPREGCOUNT - 1);
	if (op_flags & EMU86_F_HASREX) {
#ifdef __KERNEL__
		if (regno == EMU86_R_SPL)
			return (u8)icpustate64_getrsp(state);
#endif /* __KERNEL__ */
		return *(u8 const *)((byte_t const *)state + CS_reg_offsets[regno]);
	}
	return *(u8 const *)((byte_t const *)state + CS_breg_offsets[regno]);
}
#define EMU86_SETREGB(regno, value, op_flags) \
	CS_setregb(self->vea_args.va_state, regno, value, op_flags)
PRIVATE NONNULL((1)) void
NOTHROW(CC CS_setregb)(vio_cpustate_t *__restrict state,
                       u8 regno, u8 value, emu86_opflags_t op_flags) {
	regno &= (X86_GPREGCOUNT - 1);
	if (op_flags & EMU86_F_HASREX) {
#ifdef __KERNEL__
		if (regno == EMU86_R_SPL) {
			icpustate64_setrsp(state,
			                   (u64)(icpustate64_getrsp(state) & ~0xff) |
			                   (u64)value);
		} else
#endif /* __KERNEL__ */
		{
			*(u8 *)((byte_t *)state + CS_reg_offsets[regno]) = value;
		}
	} else {
		*(u8 *)((byte_t *)state + CS_breg_offsets[regno]) = value;
	}
}
#else /* __x86_64__ */
#define EMU86_GETREGB(regno, ...) \
	(*(u8 const *)((byte_t const *)self->vea_args.va_state + CS_breg_offsets[(regno) & (X86_GPREGCOUNT - 1)]))
#define EMU86_SETREGB(regno, value, ...) \
	(*(u8 *)((byte_t *)self->vea_args.va_state + CS_breg_offsets[(regno) & (X86_GPREGCOUNT - 1)]) = (value))
#endif /* !__x86_64__ */

#define _EMU86_GETREGW(state, regno)        (*(u16 const *)((byte_t const *)state + CS_reg_offsets[regno]))
#define _EMU86_GETREGL(state, regno)        (*(u32 const *)((byte_t const *)state + CS_reg_offsets[regno]))
#define _EMU86_SETREGW(state, regno, value) (*(u16 *)((byte_t *)state + CS_reg_offsets[regno]) = (u16)(value))
#define _EMU86_SETREGL(state, regno, value) (*(uintptr_t *)((byte_t *)state + CS_reg_offsets[regno]) = (uintptr_t)(u32)(value))
#ifdef __x86_64__
#define _EMU86_GETREGQ(state, regno)        (*(u64 const *)((byte_t const *)state + CS_reg_offsets[regno]))
#define _EMU86_SETREGQ(state, regno, value) (*(uintptr_t *)((byte_t *)state + CS_reg_offsets[regno]) = (u64)(value))
#endif /* __x86_64__ */

#ifdef __KERNEL__
#define EMU86_GETREGW(regno) CS_getregw(self->vea_args.va_state, regno)
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) u16
NOTHROW(CC CS_getregw)(vio_cpustate_t *__restrict state, u8 regno) {
	regno &= (X86_GPREGCOUNT - 1);
	if (regno == EMU86_R_SP) {
		return (u16)icpustate_getpsp(state);
	} else {
		return _EMU86_GETREGW(state, regno);
	}
}
#define EMU86_GETREGL(regno) CS_getregl(self->vea_args.va_state, regno)
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) u32
NOTHROW(CC CS_getregl)(vio_cpustate_t *__restrict state, u8 regno) {
	regno &= (X86_GPREGCOUNT - 1);
	if (regno == EMU86_R_ESP) {
		return (u32)icpustate_getpsp(state);
	} else {
		return _EMU86_GETREGL(state, regno);
	}
}
#ifdef __x86_64__
#define EMU86_GETREGQ(regno)        CS_getregq(self->vea_args.va_state, regno)
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) u64
NOTHROW(CC CS_getregq)(vio_cpustate_t *__restrict state, u8 regno) {
	regno &= (X86_GPREGCOUNT - 1);
	if (regno == EMU86_R_RSP) {
		return icpustate64_getrsp(state);
	} else {
		return _EMU86_GETREGQ(state, regno);
	}
}
#define EMU86_SETREGW(regno, value) CS_setregw(self->vea_args.va_state, regno, value)
PRIVATE ATTR_LEAF WUNUSED NONNULL((1)) void
NOTHROW(CC CS_setregw)(vio_cpustate_t *__restrict state, u8 regno, u16 value) {
	regno &= (X86_GPREGCOUNT - 1);
	if (regno == EMU86_R_SP) {
		icpustate64_setrsp(state, (icpustate64_getrsp(state) & ~0xffff) | (u64)value);
	} else {
		_EMU86_SETREGW(state, regno, value);
	}
}
#define EMU86_SETREGL(regno, value) CS_setregl(self->vea_args.va_state, regno, value)
PRIVATE ATTR_LEAF WUNUSED NONNULL((1)) void
NOTHROW(CC CS_setregl)(vio_cpustate_t *__restrict state, u8 regno, u32 value) {
	regno &= (X86_GPREGCOUNT - 1);
	if (regno == EMU86_R_ESP) {
		icpustate64_setrsp(state, (u64)value);
	} else {
		_EMU86_SETREGL(state, regno, value);
	}
}
#define EMU86_SETREGQ(regno, value) CS_setregq(self->vea_args.va_state, regno, value)
PRIVATE ATTR_LEAF WUNUSED NONNULL((1)) void
NOTHROW(CC CS_setregq)(vio_cpustate_t *__restrict state, u8 regno, u64 value) {
	regno &= (X86_GPREGCOUNT - 1);
	if (regno == EMU86_R_RSP) {
		icpustate64_setrsp(state, value);
	} else {
		_EMU86_SETREGQ(state, regno, value);
	}
}
#else /* __x86_64__ */
#define EMU86_SETREGW(regno, value) CS_setregw(self, regno, value)
PRIVATE ATTR_LEAF WUNUSED NONNULL((1)) void
NOTHROW(CC CS_setregw)(struct vio_emulate_args *__restrict self, u8 regno, u16 value) {
	regno &= (X86_GPREGCOUNT - 1);
	if (regno == EMU86_R_SP) {
		u32 new_esp = icpustate32_getesp(self->vea_args.va_state);
		new_esp     = (new_esp & ~0xffff) | value;
		self->vea_args.va_state = icpustate32_setesp_p(self->vea_args.va_state, new_esp);
	} else {
		_EMU86_SETREGW(self->vea_args.va_state, regno, value);
	}
}
#define EMU86_SETREGL(regno, value) CS_setregl(self, regno, value)
PRIVATE ATTR_LEAF WUNUSED NONNULL((1)) void
NOTHROW(CC CS_setregl)(struct vio_emulate_args *__restrict self, u8 regno, u32 value) {
	regno &= (X86_GPREGCOUNT - 1);
	if (regno == EMU86_R_ESP) {
		self->vea_args.va_state = icpustate32_setesp_p(self->vea_args.va_state, (u64)value);
	} else {
		_EMU86_SETREGL(self->vea_args.va_state, regno, value);
	}
}
#endif /* __x86_64__ */
#else /* __KERNEL__ */
#define EMU86_GETREGW(regno)        _EMU86_GETREGW(self->vea_args.va_state, (regno) & (X86_GPREGCOUNT - 1))
#define EMU86_SETREGW(regno, value) _EMU86_SETREGW(self->vea_args.va_state, (regno) & (X86_GPREGCOUNT - 1), value)
#define EMU86_GETREGL(regno)        _EMU86_GETREGL(self->vea_args.va_state, (regno) & (X86_GPREGCOUNT - 1))
#define EMU86_SETREGL(regno, value) _EMU86_SETREGL(self->vea_args.va_state, (regno) & (X86_GPREGCOUNT - 1), value)
#ifdef __x86_64__
#define EMU86_GETREGQ(regno)        _EMU86_GETREGQ(self->vea_args.va_state, (regno) & (X86_GPREGCOUNT - 1))
#define EMU86_SETREGQ(regno, value) _EMU86_SETREGQ(self->vea_args.va_state, (regno) & (X86_GPREGCOUNT - 1), value)
#endif /* __x86_64__ */
#endif /* !__KERNEL__ */

#ifdef __x86_64__
#define _EMU86_REGP_MASK(op_flags)            (EMU86_F_IS64(op_flags) ? (u64)UINT64_MAX : (u64)UINT32_MAX)
#define EMU86_GETREGP(regno, op_flags)        (EMU86_GETREGQ(regno) & _EMU86_REGP_MASK(op_flags))
#define EMU86_SETREGP(regno, value, op_flags) (EMU86_SETREGQ(regno, (value) & _EMU86_REGP_MASK(op_flags)))
#else /* __x86_64__ */
#define _EMU86_REGP_MASK(op_flags)            (EMU86_F_IS32(op_flags) ? (u32)UINT32_MAX : (u32)UINT16_MAX)
#define EMU86_GETREGP(regno, op_flags)        (EMU86_GETREGL(regno) & _EMU86_REGP_MASK(op_flags))
#define EMU86_SETREGP(regno, value, op_flags) (EMU86_SETREGL(regno, (value) & _EMU86_REGP_MASK(op_flags)))
#endif /* !__x86_64__ */

#ifdef __KERNEL__
#define _CPUSTATE_GPREGS self->vea_args.va_state->ics_gpregs
#else /* __KERNEL__ */
#define _CPUSTATE_GPREGS self->vea_args.va_state->ucs_gpregs
#endif /* !__KERNEL__ */

#define EMU86_GETAL()       ((u8)_CPUSTATE_GPREGS.gp_Pax)
#define EMU86_GETCL()       ((u8)_CPUSTATE_GPREGS.gp_Pcx)
#define EMU86_GETDL()       ((u8)_CPUSTATE_GPREGS.gp_Pdx)
#define EMU86_GETBL()       ((u8)_CPUSTATE_GPREGS.gp_Pbx)
#define EMU86_GETAH()       ((u8)(_CPUSTATE_GPREGS.gp_Pax >> 8))
#define EMU86_GETCH()       ((u8)(_CPUSTATE_GPREGS.gp_Pcx >> 8))
#define EMU86_GETDH()       ((u8)(_CPUSTATE_GPREGS.gp_Pdx >> 8))
#define EMU86_GETBH()       ((u8)(_CPUSTATE_GPREGS.gp_Pbx >> 8))
#define EMU86_SETAL(value)  (((u8 *)&_CPUSTATE_GPREGS.gp_Pax)[0] = (u8)(value))
#define EMU86_SETCL(value)  (((u8 *)&_CPUSTATE_GPREGS.gp_Pcx)[0] = (u8)(value))
#define EMU86_SETDL(value)  (((u8 *)&_CPUSTATE_GPREGS.gp_Pdx)[0] = (u8)(value))
#define EMU86_SETBL(value)  (((u8 *)&_CPUSTATE_GPREGS.gp_Pbx)[0] = (u8)(value))
#define EMU86_SETAH(value)  (((u8 *)&_CPUSTATE_GPREGS.gp_Pax)[1] = (u8)(value))
#define EMU86_SETCH(value)  (((u8 *)&_CPUSTATE_GPREGS.gp_Pcx)[1] = (u8)(value))
#define EMU86_SETDH(value)  (((u8 *)&_CPUSTATE_GPREGS.gp_Pdx)[1] = (u8)(value))
#define EMU86_SETBH(value)  (((u8 *)&_CPUSTATE_GPREGS.gp_Pbx)[1] = (u8)(value))
#define EMU86_GETAX()       ((u16)_CPUSTATE_GPREGS.gp_Pax)
#define EMU86_GETCX()       ((u16)_CPUSTATE_GPREGS.gp_Pcx)
#define EMU86_GETDX()       ((u16)_CPUSTATE_GPREGS.gp_Pdx)
#define EMU86_GETBX()       ((u16)_CPUSTATE_GPREGS.gp_Pbx)
#define EMU86_GETSP()       ((u16)EMU86_GETSPREG())
#define EMU86_GETBP()       ((u16)_CPUSTATE_GPREGS.gp_Pbp)
#define EMU86_GETSI()       ((u16)_CPUSTATE_GPREGS.gp_Psi)
#define EMU86_GETDI()       ((u16)_CPUSTATE_GPREGS.gp_Pdi)
#define EMU86_SETAX(value)  (_CPUSTATE_GPREGS.gp_Pax = (uintptr_t)(u16)(value))
#define EMU86_SETCX(value)  (_CPUSTATE_GPREGS.gp_Pcx = (uintptr_t)(u16)(value))
#define EMU86_SETDX(value)  (_CPUSTATE_GPREGS.gp_Pdx = (uintptr_t)(u16)(value))
#define EMU86_SETBX(value)  (_CPUSTATE_GPREGS.gp_Pbx = (uintptr_t)(u16)(value))
#define EMU86_SETSP(value)  EMU86_SETSPREG((uintptr_t)(u16)(value))
#define EMU86_SETBP(value)  (_CPUSTATE_GPREGS.gp_Pbp = (uintptr_t)(u16)(value))
#define EMU86_SETSI(value)  (_CPUSTATE_GPREGS.gp_Psi = (uintptr_t)(u16)(value))
#define EMU86_SETDI(value)  (_CPUSTATE_GPREGS.gp_Pdi = (uintptr_t)(u16)(value))
#define EMU86_GETEAX()      ((u32)_CPUSTATE_GPREGS.gp_Pax)
#define EMU86_GETECX()      ((u32)_CPUSTATE_GPREGS.gp_Pcx)
#define EMU86_GETEDX()      ((u32)_CPUSTATE_GPREGS.gp_Pdx)
#define EMU86_GETEBX()      ((u32)_CPUSTATE_GPREGS.gp_Pbx)
#define EMU86_GETESP()      ((u32)EMU86_GETSPREG())
#define EMU86_GETEBP()      ((u32)_CPUSTATE_GPREGS.gp_Pbp)
#define EMU86_GETESI()      ((u32)_CPUSTATE_GPREGS.gp_Psi)
#define EMU86_GETEDI()      ((u32)_CPUSTATE_GPREGS.gp_Pdi)
#define EMU86_SETEAX(value) (_CPUSTATE_GPREGS.gp_Pax = (uintptr_t)(u32)(value))
#define EMU86_SETECX(value) (_CPUSTATE_GPREGS.gp_Pcx = (uintptr_t)(u32)(value))
#define EMU86_SETEDX(value) (_CPUSTATE_GPREGS.gp_Pdx = (uintptr_t)(u32)(value))
#define EMU86_SETEBX(value) (_CPUSTATE_GPREGS.gp_Pbx = (uintptr_t)(u32)(value))
#define EMU86_SETESP(value) EMU86_SETSPREG((uintptr_t)(u32)(value))
#define EMU86_SETEBP(value) (_CPUSTATE_GPREGS.gp_Pbp = (uintptr_t)(u32)(value))
#define EMU86_SETESI(value) (_CPUSTATE_GPREGS.gp_Psi = (uintptr_t)(u32)(value))
#define EMU86_SETEDI(value) (_CPUSTATE_GPREGS.gp_Pdi = (uintptr_t)(u32)(value))
#ifdef __x86_64__
#define EMU86_GETSPL()      ((u8)EMU86_GETSPREG())
#define EMU86_GETBPL()      ((u8)_CPUSTATE_GPREGS.gp_rbp)
#define EMU86_GETSIL()      ((u8)_CPUSTATE_GPREGS.gp_rsi)
#define EMU86_GETDIL()      ((u8)_CPUSTATE_GPREGS.gp_rdi)
#define EMU86_SETSPL(value) EMU86_SETSPREG((EMU86_GETSPREG() & ~0xff) | (u8)(value))
#define EMU86_SETBPL(value) (_CPUSTATE_GPREGS.gp_rbp = (_CPUSTATE_GPREGS.gp_rbp & ~0xff) | (u8)(value))
#define EMU86_SETSIL(value) (_CPUSTATE_GPREGS.gp_rsi = (_CPUSTATE_GPREGS.gp_rsi & ~0xff) | (u8)(value))
#define EMU86_SETDIL(value) (_CPUSTATE_GPREGS.gp_rdi = (_CPUSTATE_GPREGS.gp_rdi & ~0xff) | (u8)(value))
#define EMU86_GETRAX()      ((u64)_CPUSTATE_GPREGS.gp_rax)
#define EMU86_GETRCX()      ((u64)_CPUSTATE_GPREGS.gp_rcx)
#define EMU86_GETRDX()      ((u64)_CPUSTATE_GPREGS.gp_rdx)
#define EMU86_GETRBX()      ((u64)_CPUSTATE_GPREGS.gp_rbx)
#define EMU86_GETRSP()      ((u64)EMU86_GETSPREG())
#define EMU86_GETRBP()      ((u64)_CPUSTATE_GPREGS.gp_rbp)
#define EMU86_GETRSI()      ((u64)_CPUSTATE_GPREGS.gp_rsi)
#define EMU86_GETRDI()      ((u64)_CPUSTATE_GPREGS.gp_rdi)
#define EMU86_SETRAX(value) (_CPUSTATE_GPREGS.gp_rax = (u64)(value))
#define EMU86_SETRCX(value) (_CPUSTATE_GPREGS.gp_rcx = (u64)(value))
#define EMU86_SETRDX(value) (_CPUSTATE_GPREGS.gp_rdx = (u64)(value))
#define EMU86_SETRBX(value) (_CPUSTATE_GPREGS.gp_rbx = (u64)(value))
#define EMU86_SETRSP(value) EMU86_SETSPREG((u64)(value))
#define EMU86_SETRBP(value) (_CPUSTATE_GPREGS.gp_rbp = (u64)(value))
#define EMU86_SETRSI(value) (_CPUSTATE_GPREGS.gp_rsi = (u64)(value))
#define EMU86_SETRDI(value) (_CPUSTATE_GPREGS.gp_rdi = (u64)(value))
#endif /* __x86_64__ */
#define EMU86_GETPAX(op_flags)        ((uintptr_t)(_CPUSTATE_GPREGS.gp_Pax & _EMU86_REGP_MASK(op_flags)))
#define EMU86_GETPCX(op_flags)        ((uintptr_t)(_CPUSTATE_GPREGS.gp_Pcx & _EMU86_REGP_MASK(op_flags)))
#define EMU86_GETPDX(op_flags)        ((uintptr_t)(_CPUSTATE_GPREGS.gp_Pdx & _EMU86_REGP_MASK(op_flags)))
#define EMU86_GETPBX(op_flags)        ((uintptr_t)(_CPUSTATE_GPREGS.gp_Pbx & _EMU86_REGP_MASK(op_flags)))
#define EMU86_GETPBP(op_flags)        ((uintptr_t)(_CPUSTATE_GPREGS.gp_Pbp & _EMU86_REGP_MASK(op_flags)))
#define EMU86_GETPSI(op_flags)        ((uintptr_t)(_CPUSTATE_GPREGS.gp_Psi & _EMU86_REGP_MASK(op_flags)))
#define EMU86_GETPDI(op_flags)        ((uintptr_t)(_CPUSTATE_GPREGS.gp_Pdi & _EMU86_REGP_MASK(op_flags)))
#define EMU86_SETPAX(value, op_flags) (_CPUSTATE_GPREGS.gp_Pax = (uintptr_t)(value) & _EMU86_REGP_MASK(op_flags))
#define EMU86_SETPCX(value, op_flags) (_CPUSTATE_GPREGS.gp_Pcx = (uintptr_t)(value) & _EMU86_REGP_MASK(op_flags))
#define EMU86_SETPDX(value, op_flags) (_CPUSTATE_GPREGS.gp_Pdx = (uintptr_t)(value) & _EMU86_REGP_MASK(op_flags))
#define EMU86_SETPBX(value, op_flags) (_CPUSTATE_GPREGS.gp_Pbx = (uintptr_t)(value) & _EMU86_REGP_MASK(op_flags))
#define EMU86_SETPBP(value, op_flags) (_CPUSTATE_GPREGS.gp_Pbp = (uintptr_t)(value) & _EMU86_REGP_MASK(op_flags))
#define EMU86_SETPSI(value, op_flags) (_CPUSTATE_GPREGS.gp_Psi = (uintptr_t)(value) & _EMU86_REGP_MASK(op_flags))
#define EMU86_SETPDI(value, op_flags) (_CPUSTATE_GPREGS.gp_Pdi = (uintptr_t)(value) & _EMU86_REGP_MASK(op_flags))


/* Configure general library implementation */
#define EMU86_EMULATE_CONFIG_ONLY_MEMORY     1 /* _ONLY_ emulate memory-based instructions! */
#define EMU86_EMULATE_CONFIG_CHECKERROR      0 /* Don't emulate error checks for instructions that are disabled */
#define EMU86_EMULATE_CONFIG_ONLY_CHECKERROR 0 /* Enable instruction emulator by default (though only for memory-based instruction) */
#define EMU86_EMULATE_CONFIG_CHECKLOCK       1 /* Make sure that lock prefixes are used properly */

/* Configure ISA extensions */
#define EMU86_EMULATE_CONFIG_FSGSBASE_32BIT       1 /* [enabled] Allow use of (rd|wr)(fs|gs)base from 32-bit */
#define EMU86_EMULATE_CONFIG_ALLOW_USER_STAC_CLAC 1 /* [enabled] Allow user-space use of stac/clac */
#ifdef CONFIG_X86ISA_ENABLE_LOCK_EXTENSIONS
#define EMU86_EMULATE_CONFIG_LOCK_SHIFT           1 /* [enabled] Accept `lock' for shl/shr/sal/sar/rol/ror/rcl/rcr */
#define EMU86_EMULATE_CONFIG_LOCK_SHIFT2          1 /* [enabled] Accept `lock' for shld/shrd */
#define EMU86_EMULATE_CONFIG_LOCK_ARPL            1 /* [enabled] Accept `lock' for arpl */
#else /* CONFIG_X86ISA_ENABLE_LOCK_EXTENSIONS */
#define EMU86_EMULATE_CONFIG_LOCK_SHIFT           0 /* [not enabled] Accept `lock' for shl/shr/sal/sar/rol/ror/rcl/rcr */
#define EMU86_EMULATE_CONFIG_LOCK_SHIFT2          0 /* [not enabled] Accept `lock' for shld/shrd */
#define EMU86_EMULATE_CONFIG_LOCK_ARPL            0 /* [not enabled] Accept `lock' for arpl */
#endif /* !CONFIG_X86ISA_ENABLE_LOCK_EXTENSIONS */


/* Enable support for protected-mode instructions
 * This is required because all of these instructions can take
 * a memory location as operand, thus allowing them to trigger
 * a #PF that may require VIO emulation... */
#define EMU86_EMULATE_CONFIG_WANT_SLDT 1
#define EMU86_EMULATE_CONFIG_WANT_LLDT 1
#define EMU86_EMULATE_CONFIG_WANT_STR  1
#define EMU86_EMULATE_CONFIG_WANT_LTR  1
#define EMU86_EMULATE_CONFIG_WANT_SGDT 1
#define EMU86_EMULATE_CONFIG_WANT_LGDT 1
#define EMU86_EMULATE_CONFIG_WANT_SIDT 1
#define EMU86_EMULATE_CONFIG_WANT_LIDT 1
#define EMU86_EMULATE_CONFIG_WANT_VERR 1
#define EMU86_EMULATE_CONFIG_WANT_VERW 1
#define EMU86_EMULATE_CONFIG_WANT_SMSW 1
#define EMU86_EMULATE_CONFIG_WANT_LMSW 1
#define EMU86_EMULATE_CONFIG_WANT_INVLPG 0 /* This one shouldn't be able to cause a segfault! */
#define EMU86_EMULATE_CONFIG_WANT_LAR 1
#define EMU86_EMULATE_CONFIG_WANT_LSL 1


/* Implementations of  the  P-mode  instructions  that
 * must be enabled due to being able to access memory. */
#define EMU86_EMULATE_SLDT()              __sldt()
#define EMU86_EMULATE_LLDT(segment_index) __lldt(segment_index)
#define EMU86_EMULATE_STR()               __str()
#define EMU86_EMULATE_LTR(segment_index)  __ltr(segment_index)
#define EMU86_EMULATE_VERR(segment_index) __verr(segment_index)
#define EMU86_EMULATE_VERW(segment_index) __verw(segment_index)
#define EMU86_EMULATE_SGDT(limit, base)        \
	do {                                       \
		struct desctab dt;                     \
		__sgdt(&dt);                           \
		(limit) = (u16)dt.dt_limit;            \
		(base)  = (EMU86_UREG_TYPE)dt.dt_base; \
	}	__WHILE0
#define EMU86_EMULATE_LGDT(limit, base) \
	__lgdt(limit, (void *)(uintptr_t)(base))
#define EMU86_EMULATE_SIDT(limit, base)        \
	do {                                       \
		struct desctab dt;                     \
		__sidt(&dt);                           \
		(limit) = (u16)dt.dt_limit;            \
		(base)  = (EMU86_UREG_TYPE)dt.dt_base; \
	}	__WHILE0
#define EMU86_EMULATE_LIDT(limit, base) \
	__lidt(limit, (void *)(uintptr_t)(base))
#define EMU86_EMULATE_SMSW()                     __smsw()
#define EMU86_EMULATE_LMSW(value)                __lmsw(value)
#define EMU86_EMULATE_LAR(segment_index, result) __lar(segment_index, &(result))
#define EMU86_EMULATE_LSL(segment_index, result) __lsl(segment_index, &(result))


#define EMU86_EMULATE_CONFIG_WANT_LDMXCSR 1
#define EMU86_EMULATE_CONFIG_WANT_STMXCSR 1
#define EMU86_EMULATE_STMXCSR()      __stmxcsr()
#define EMU86_EMULATE_LDMXCSR(mxcsr) __ldmxcsr(mxcsr)


PRIVATE ATTR_NORETURN void CC
libviocore_throw_unknown_instruction(struct vio_emulate_args *__restrict self,
                                     except_code_t code, uintptr_t opcode,
                                     uintptr_t op_flags, uintptr_t ptr2,
                                     uintptr_t ptr3, uintptr_t ptr4,
                                     uintptr_t ptr5, uintptr_t ptr6) {
	struct exception_data *data;
	byte_t const *pc, *next_pc;
	unsigned int i;
	pc      = (byte_t const *)CS(getpc)(self->vea_args.va_state);
	next_pc = instruction_succ_nx(pc, CS(getisa)(self->vea_args.va_state));
	if (next_pc)
		CS(setpc)(self->vea_args.va_state, next_pc);
	PRINT_WARN("[vio] Illegal instruction %p:%#" PRIxPTR " "
	           "[cr2=%p:%#" PRIx64 ",code="
	           "%" PRIxN(__SIZEOF_EXCEPT_CLASS_T__) ":"
	           "%" PRIxN(__SIZEOF_EXCEPT_SUBCLASS_T__) "]\n",
	           pc, opcode, self->vea_ptrlo, (u64)self->vea_addr,
	           EXCEPT_CLASS(code), EXCEPT_SUBCLASS(code));
	/* Throw an exception detailing an unsupported opcode. */
	data = except_data();
	data->e_code               = code;
	data->e_faultaddr          = (void *)pc;
	data->e_args.e_pointers[0] = opcode;
	data->e_args.e_pointers[1] = op_flags;
	data->e_args.e_pointers[2] = ptr2;
	data->e_args.e_pointers[3] = ptr3;
	data->e_args.e_pointers[4] = ptr4;
	data->e_args.e_pointers[5] = ptr5;
	data->e_args.e_pointers[6] = ptr6;
	for (i = 7; i < EXCEPTION_DATA_POINTERS; ++i)
		data->e_args.e_pointers[i] = 0;
	except_throw_current();
}

PRIVATE ATTR_NORETURN void CC
libviocore_throw_exception(struct vio_emulate_args *__restrict self,
                           except_code_t code, uintptr_t ptr0,
                           uintptr_t ptr1, uintptr_t ptr2) {
	struct exception_data *data;
	byte_t const *pc, *next_pc;
	unsigned int i;
	pc      = (byte_t const *)CS(getpc)(self->vea_args.va_state);
	next_pc = instruction_succ_nx(pc, CS(getisa)(self->vea_args.va_state));
	if (next_pc)
		CS(setpc)(self->vea_args.va_state, next_pc);
	data = except_data();
	data->e_code               = code;
	data->e_faultaddr          = (void *)pc;
	data->e_args.e_pointers[0] = ptr0;
	data->e_args.e_pointers[1] = ptr1;
	data->e_args.e_pointers[2] = ptr2;
	for (i = 3; i < EXCEPTION_DATA_POINTERS; ++i)
		data->e_args.e_pointers[i] = 0;
	except_throw_current();
}



/* Define how we want to handle exceptions */
#define EMU86_EMULATE_RETURN_UNKNOWN_INSTRUCTION()                                              \
	libviocore_throw_unknown_instruction(self, EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPCODE), \
	                                     _EMU86_GETOPCODE(), op_flags, 0, 0, 0, 0, 0)
#define EMU86_EMULATE_RETURN_UNKNOWN_INSTRUCTION_RMREG()                                        \
	libviocore_throw_unknown_instruction(self, EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPCODE), \
	                                     _EMU86_GETOPCODE_RMREG(), op_flags, 0, 0, 0, 0, 0)
#define EMU86_EMULATE_RETURN_PRIVILEGED_INSTRUCTION()                                                  \
	libviocore_throw_unknown_instruction(self, EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE), \
	                                     _EMU86_GETOPCODE(), op_flags, 0, 0, 0, 0, 0)
#define EMU86_EMULATE_RETURN_PRIVILEGED_INSTRUCTION_RMREG()                                            \
	libviocore_throw_unknown_instruction(self, EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE), \
	                                     _EMU86_GETOPCODE_RMREG(), op_flags, 0, 0, 0, 0, 0)
#define EMU86_EMULATE_RETURN_EXPECTED_MEMORY_MODRM()                                             \
	libviocore_throw_unknown_instruction(self, EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND), \
	                                     _EMU86_GETOPCODE(), op_flags,                           \
	                                     E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_REGISTER,  \
	                                     _EMU86_GETMODRM_RM_GPREGNO(), 0, _EMU86_GETMODRM_RM_GPREGVAL(), 0)
#define EMU86_EMULATE_RETURN_EXPECTED_MEMORY_MODRM_RMREG()                                       \
	libviocore_throw_unknown_instruction(self, EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND), \
	                                     _EMU86_GETOPCODE_RMREG(), op_flags,                     \
	                                     E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_REGISTER,  \
	                                     _EMU86_GETMODRM_RM_GPREGNO(), 0, _EMU86_GETMODRM_RM_GPREGVAL(), 0)
#define EMU86_EMULATE_RETURN_EXPECTED_REGISTER_MODRM()                                           \
	libviocore_throw_unknown_instruction(self, EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND), \
	                                     _EMU86_GETOPCODE(), op_flags,                           \
	                                     E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_MEMORY,    \
	                                     0, _EMU86_GETMODRM_RM_MEMADDR(), 0, 0)
#define EMU86_EMULATE_RETURN_EXPECTED_REGISTER_MODRM_RMREG()                                     \
	libviocore_throw_unknown_instruction(self, EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND), \
	                                     _EMU86_GETOPCODE_RMREG(), op_flags,                     \
	                                     E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_MEMORY,    \
	                                     0, _EMU86_GETMODRM_RM_MEMADDR(), 0, 0)
#define EMU86_EMULATE_RETURN_UNEXPECTED_PREFIX()                                                    \
	libviocore_throw_unknown_instruction(self, EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX), \
	                                     _EMU86_GETOPCODE(), op_flags, 0, 0, 0, 0, 0)
#define EMU86_EMULATE_RETURN_UNEXPECTED_PREFIX_RMREG()                                              \
	libviocore_throw_unknown_instruction(self, EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX), \
	                                     _EMU86_GETOPCODE_RMREG(), op_flags, 0, 0, 0, 0, 0)
#define EMU86_EMULATE_RETURN_UNSUPPORTED_INSTRUCTION()                                                  \
	libviocore_throw_unknown_instruction(self, EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE), \
	                                     _EMU86_GETOPCODE(), op_flags, 0, 0, 0, 0, 0)
#define EMU86_EMULATE_RETURN_UNSUPPORTED_INSTRUCTION_RMREG()                                            \
	libviocore_throw_unknown_instruction(self, EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE), \
	                                     _EMU86_GETOPCODE_RMREG(), op_flags, 0, 0, 0, 0, 0)
#define EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(how, regno, offset, regval, regval2) \
	libviocore_throw_unknown_instruction(self, EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER), \
	                                     /* opcode:   */ _EMU86_GETOPCODE(),                  \
	                                     /* op_flags: */ op_flags,                            \
	                                     /* how:      */ how,                                 \
	                                     /* regno:    */ regno,                               \
	                                     /* offset:   */ offset,                              \
	                                     /* regval:   */ regval,                              \
	                                     /* regval2:  */ regval2)
#define EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER_RMREG(how, regno, offset, regval, regval2) \
	libviocore_throw_unknown_instruction(self, EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER),       \
	                                     /* opcode:   */ _EMU86_GETOPCODE_RMREG(),                  \
	                                     /* op_flags: */ op_flags,                                  \
	                                     /* how:      */ how,                                       \
	                                     /* regno:    */ regno,                                     \
	                                     /* offset:   */ offset,                                    \
	                                     /* regval:   */ regval,                                    \
	                                     /* regval2:  */ regval2)
#define EMU86_EMULATE_THROW_BOUNDERR(bound_idx, bound_min, bound_max)            \
	libviocore_throw_exception(self, EXCEPT_CODEOF(E_INDEX_ERROR_OUT_OF_BOUNDS), \
	                           (uintptr_t)(bound_idx),                           \
	                           (uintptr_t)(bound_min),                           \
	                           (uintptr_t)(bound_max))
#define EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW 0
#define EMU86_EMULATE_THROW_DIVIDE_ERROR() \
	libviocore_throw_exception(self, EXCEPT_CODEOF(E_DIVIDE_BY_ZERO), 0, 0, 0)


DECL_END

/* Use relative include to force rebuild on change, and prevent -Wsystem-headers */
#if 1
#include "../../../../include/libemu86/emulate.c.inl"
#else
#include <libemu86/emulate.c.inl>
#endif


DECL_BEGIN
DEFINE_PUBLIC_ALIAS(viocore_emulate, libviocore_emulate);
DECL_END

#endif /* LIBVIO_CONFIG_ENABLED */

#endif /* !GUARD_LIBVIOCORE_ARCH_I386_VIOCORE_C */
