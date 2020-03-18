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
#ifndef _LIBVIO_VIO_H
#define _LIBVIO_VIO_H 1

#include "api.h"
#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __KERNEL__
struct icpustate;
typedef struct icpustate vio_cpustate_t;
#else /* __KERNEL__ */
struct ucpustate;
typedef struct ucpustate vio_cpustate_t;
#endif /* !__KERNEL__ */
#ifdef __KERNEL__
struct vm_datablock;
struct vm_datapart;
#endif /* __KERNEL__ */
struct vio_operators;

/* Argument structure passed to VIO callbacks. */
struct vio_args {
	struct vio_operators const *va_ops;          /* [1..1][== va_block->db_type->dt_vio] */
	__pos64_t                   va_acmap_offset; /* [== vm_datapart_startbyte(va_part)]
	                                              * VIO file offset at `va_acmap_page' (== mmap:offset). */
	void                       *va_acmap_page;   /* Virtual base address of the accessed mapping (== mmap:return). */
	vio_cpustate_t             *va_state;        /* [0..1][in|out] The CPU state at the time of the access being made (or `NULL' when accessed through other means). */
#ifdef __KERNEL__
	struct vm_datablock        *va_block;        /* [1..1] The data block that is being accessed. */
	struct vm_datapart         *va_part;         /* [0..1] The part that is being accessed. */
#else /* __KERNEL__ */
	void                       *va_cookie;       /* [?..?] The cookie registered alongside the VIO mapping. */
#endif /* !__KERNEL__ */
};


#ifdef LIBVIO_CONFIG_HAVE_QWORD
#define VIO_CALLBACK_INIT(b, w, l, q) { b, w, l, q }
#else /* LIBVIO_CONFIG_HAVE_QWORD */
#define VIO_CALLBACK_INIT(b, w, l, q) { b, w, l }
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */

struct vio_operators {
	/* VIO callbacks (`addr' is always relative to the data-block)
	 * NOTE: For unrecognized addresses, VIO should throw
	 *      `E_SEGFAULT_NOTREADABLE' / `E_SEGFAULT_NOTWRITABLE' exceptions. */
	struct {
		/* [0..1] Read memory */
		__ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *f_byte)(struct vio_args *__restrict args, __pos64_t addr);
		__ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *f_word)(struct vio_args *__restrict args, __pos64_t addr);
		__ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *f_dword)(struct vio_args *__restrict args, __pos64_t addr);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		__ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *f_qword)(struct vio_args *__restrict args, __pos64_t addr);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
	} vo_read;

	struct {
		/* [0..1] Write memory */
		__ATTR_NONNULL((1)) void (LIBVIO_CC *f_byte)(struct vio_args *__restrict args, __pos64_t addr, __uint8_t value);
		__ATTR_NONNULL((1)) void (LIBVIO_CC *f_word)(struct vio_args *__restrict args, __pos64_t addr, __uint16_t value);
		__ATTR_NONNULL((1)) void (LIBVIO_CC *f_dword)(struct vio_args *__restrict args, __pos64_t addr, __uint32_t value);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		__ATTR_NONNULL((1)) void (LIBVIO_CC *f_qword)(struct vio_args *__restrict args, __pos64_t addr, __uint64_t value);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
	} vo_write;

	struct {
		/* [0..1] Return the old value (regardless of the compare-exchange having been successful) */
		__ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *f_byte)(struct vio_args *__restrict args, __pos64_t addr, __uint8_t oldvalue, __uint8_t newvalue, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *f_word)(struct vio_args *__restrict args, __pos64_t addr, __uint16_t oldvalue, __uint16_t newvalue, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *f_dword)(struct vio_args *__restrict args, __pos64_t addr, __uint32_t oldvalue, __uint32_t newvalue, __BOOL atomic);
#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
		__ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *f_qword)(struct vio_args *__restrict args, __pos64_t addr, __uint64_t oldvalue, __uint64_t newvalue, __BOOL atomic);
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
#ifdef LIBVIO_CONFIG_HAVE_INT128_CMPXCH
		__ATTR_NONNULL((1)) uint128_t (LIBVIO_CC *f_int128)(struct vio_args *__restrict args, __pos64_t addr, uint128_t oldvalue, uint128_t newvalue, __BOOL atomic);
#endif /* LIBVIO_CONFIG_HAVE_INT128_CMPXCH */
	} vo_cmpxch;

	struct {
		/* [0..1] Return the old value */
		__ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *f_byte)(struct vio_args *__restrict args, __pos64_t addr, __uint8_t newvalue, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *f_word)(struct vio_args *__restrict args, __pos64_t addr, __uint16_t newvalue, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *f_dword)(struct vio_args *__restrict args, __pos64_t addr, __uint32_t newvalue, __BOOL atomic);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		__ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *f_qword)(struct vio_args *__restrict args, __pos64_t addr, __uint64_t newvalue, __BOOL atomic);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
	} vo_xch;

	struct {
		/* [0..1] Return the old value (prior to be `value' being added) */
		__ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *f_byte)(struct vio_args *__restrict args, __pos64_t addr, __uint8_t value, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *f_word)(struct vio_args *__restrict args, __pos64_t addr, __uint16_t value, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *f_dword)(struct vio_args *__restrict args, __pos64_t addr, __uint32_t value, __BOOL atomic);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		__ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *f_qword)(struct vio_args *__restrict args, __pos64_t addr, __uint64_t value, __BOOL atomic);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
	} vo_add;

	struct {
		/* [0..1] Return the old value (prior to be `value' being subtracted) */
		__ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *f_byte)(struct vio_args *__restrict args, __pos64_t addr, __uint8_t value, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *f_word)(struct vio_args *__restrict args, __pos64_t addr, __uint16_t value, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *f_dword)(struct vio_args *__restrict args, __pos64_t addr, __uint32_t value, __BOOL atomic);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		__ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *f_qword)(struct vio_args *__restrict args, __pos64_t addr, __uint64_t value, __BOOL atomic);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
	} vo_sub;

	struct {
		/* [0..1] Return the old value (prior to be `mask' being anded) */
		__ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *f_byte)(struct vio_args *__restrict args, __pos64_t addr, __uint8_t mask, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *f_word)(struct vio_args *__restrict args, __pos64_t addr, __uint16_t mask, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *f_dword)(struct vio_args *__restrict args, __pos64_t addr, __uint32_t mask, __BOOL atomic);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		__ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *f_qword)(struct vio_args *__restrict args, __pos64_t addr, __uint64_t mask, __BOOL atomic);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
	} vo_and;

	struct {
		/* [0..1] Return the old value (prior to be `mask' being or'd) */
		__ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *f_byte)(struct vio_args *__restrict args, __pos64_t addr, __uint8_t mask, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *f_word)(struct vio_args *__restrict args, __pos64_t addr, __uint16_t mask, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *f_dword)(struct vio_args *__restrict args, __pos64_t addr, __uint32_t mask, __BOOL atomic);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		__ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *f_qword)(struct vio_args *__restrict args, __pos64_t addr, __uint64_t mask, __BOOL atomic);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
	} vo_or;

	struct {
		/* [0..1] Return the old value (prior to be `mask' being xor'd) */
		__ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *f_byte)(struct vio_args *__restrict args, __pos64_t addr, __uint8_t mask, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *f_word)(struct vio_args *__restrict args, __pos64_t addr, __uint16_t mask, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *f_dword)(struct vio_args *__restrict args, __pos64_t addr, __uint32_t mask, __BOOL atomic);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		__ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *f_qword)(struct vio_args *__restrict args, __pos64_t addr, __uint64_t mask, __BOOL atomic);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
	} vo_xor;

	/* [0..1]
	 * Invoked as the result of the user attempting to call into VIO memory.
	 * When this operator is called, `regs' will have already been updated to
	 * point to the instruction following the call instruction that was used
	 * to execute VIO memory.
	 * USER:
	 * >> void *vio_base;
	 * >> vio_base = mmap(NULL, 0x1000, PROT_READ | PROT_EXEC, MAP_PRIVATE, vio_fd, 0);
	 * >>
	 * >> kernel_function = (int(*)(int, int))((byte_t *)vio_base + 1234);
	 * >>
	 * >> // This function will invoke `vo_call(..., REGS, 1234)'
	 * >> // REGS: (user-space register state; assuming x86)
	 * >> //    PC: ADDROF(printf)
	 * >> //    SP: { int: 10, int: 20 }
	 * >> // `vo_call' can then assign the EAX register in `args' (again: assuming x86),
	 * >> // which is the value that's going to be returned to user-space and be assigned
	 * >> // to `x', before being printed.
	 * >> int x = (*kernel_function)(10, 20);
	 * >>
	 * >> printf("x = %d\n", x); */
	void (LIBVIO_CC *vo_call)(struct vio_args *__restrict args, __pos64_t addr);
};


/* High-level user-space VIO library functions. */
#ifndef __KERNEL__

/* vio_create(3):
 * >> fd_t vio_create(struct vio_operators *ops, void *cookie, oflag_t flags);
 * @param: flags:  Set of `0 | O_CLOEXEC | O_CLOFORK'
 * @param: cookie: A cookie pointer that is available as `args->va_cookie'
 * Desc:
 *     Create an mmap(2)able VIO object where memory accesses
 *     made to the object are serviced by dispatching them via
 *     the given `ops' table.
 *     The returned file descriptor mustn't be deleted by `close(2)',
 *     but rather through use of `vio_destroy(3)'.
 *     Note that callbacks in `ops' may be invoked in the context
 *     of a different thread than the one that performed the memory
 *     access. Also note that the returned `fd_t' can be shared with
 *     other processes, but still function as expected. (when shared
 *     with a different process, that process should once again make
 *     use of `close(2)' for cleanup, rather than `vio_destroy(3)')
 * Impl:
 *     Call `userviofd()' and store the returned handle in a list
 *     of active VIO objects. If the list becomes non-empty, start
 *     a background thread that poll(2)s from all registered `userviofd()'
 *     objects, and services the requests by dispatching them through
 *     the ops-table originally passed to `vio_create()' */
typedef __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t
/*__NOTHROW_NCX*/ (LIBVIO_CC *PVIO_CREATE)(struct vio_operators const *ops, void *cookie, __oflag_t flags);
#ifdef LIBVIO_WANT_PROTOTYPES
LIBVIO_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t
__NOTHROW_NCX(LIBVIO_CC vio_create)(struct vio_operators const *ops, void *cookie, __oflag_t flags);
#endif /* LIBVIO_WANT_PROTOTYPES */


/* vio_destroy(3):
 * >> int vio_destroy(fd_t fd);
 * Desc:
 *     Destroy a VIO file descriptor previously created by `vio_create(3)'
 * Impl:
 *     Remove `fd' from the set of active userfd handles. If all
 *     handles get closed, stop the background thread used to
 *     service VIO requests. */
#ifdef LIBVIO_WANT_PROTOTYPES
typedef int /*__NOTHROW_NCX*/ (LIBVIO_CC *PVIO_DESTROY)(__fd_t fd);
LIBVIO_DECL int __NOTHROW_NCX(LIBVIO_CC vio_destroy)(__fd_t fd);
#endif /* LIBVIO_WANT_PROTOTYPES */

#endif /* !__KERNEL__ */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIO_VIO_H */
