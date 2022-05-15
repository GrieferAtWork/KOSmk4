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
#ifndef _LIBVIO_VIO_H
#define _LIBVIO_VIO_H 1

#include "api.h"

#include <bits/types.h>

#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
#include <hybrid/int128.h>
#endif /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */
#ifdef __KERNEL__
#include <kernel/compiler.h>
#ifndef __pos_t_defined
#include <hybrid/__altint.h>
#endif /* !__pos_t_defined */
#endif /* __KERNEL__ */

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
struct mpart;
struct mfile;
#endif /* __KERNEL__ */
struct vio_ops;

#ifdef __KERNEL__
#ifndef __pos_t_defined
#define __pos_t_defined
__HYBRID_ALTINT_TYPEDEF(__pos64_t, pos_t, false); /* File/device position */
#endif /* !__pos_t_defined */
typedef pos_t vio_addr_t;
#else /* __KERNEL__ */
typedef __pos64_t vio_addr_t;
#endif /* !__KERNEL__ */



/* Argument structure passed to VIO callbacks. */
struct vioargs {
	struct vio_ops const *va_ops;          /* [1..1][== va_file->mf_ops->dt_vio] */
	void                       *va_acmap_page;   /* Page-aligned virtual base address of the accessed mapping (== mmap:return). */
	vio_addr_t                  va_acmap_offset; /* VIO file offset at `va_acmap_page' (== mmap:offset). */
	vio_cpustate_t             *va_state;        /* [0..1][in|out] The CPU  state at the  time of the  access
	                                              * being made (or `NULL' when accessed through other means). */
#ifdef __KERNEL__
	struct mfile               *va_file;         /* [1..1] The mem-file that is being accessed. */
#else /* __KERNEL__ */
	void                       *va_cookie;       /* [?..?] The cookie registered alongside the VIO mapping. */
#endif /* !__KERNEL__ */
};

/* Return the effective fault address for a given VIO address. */
#ifdef __INTELLISENSE__
void *vioargs_faultaddr(struct vioargs const *__restrict self, vio_addr_t vio_addr);
vio_addr_t vioargs_vioaddr(struct vioargs const *__restrict self, void *virtaddr);
#else /* __INTELLISENSE__ */
#define vioargs_faultaddr(self, vio_addr) \
	(void *)((__byte_t *)(self)->va_acmap_page + (__size_t)((vio_addr) - (self)->va_acmap_offset))
#define vioargs_vioaddr(self, virtaddr) \
	((self)->va_acmap_offset + (size_t)((__byte_t *)(virtaddr) - (__byte_t *)(self)->va_acmap_page))
#endif /* !__INTELLISENSE__ */

#ifndef __KERNEL__
/* Return  a pointer to  the modifiable CPU state  of the thread that
 * is requesting the memory access. If the thread is currently inside
 * of kernel-space  (such that  its CPU  state cannot  be  accessed),
 * return `NULL' instead. */
typedef __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) vio_cpustate_t *
/*__NOTHROW_NCX*/ (LIBVIO_CC *PVIOARGS_GETSTATE)(struct vioargs *__restrict self);
#ifdef LIBVIO_WANT_PROTOTYPES
LIBVIO_DECL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) vio_cpustate_t *
__NOTHROW_NCX(LIBVIO_CC vioargs_getstate)(struct vioargs *__restrict self);
#endif /* LIBVIO_WANT_PROTOTYPES */
#else /* __KERNEL__ */
#define vioargs_getstate(self) ((self)->va_state)
#endif /* !__KERNEL__ */


#ifdef LIBVIO_CONFIG_HAVE_QWORD
#define VIO_CALLBACK_INIT(b, w, l, q) { b, w, l, q }
#else /* LIBVIO_CONFIG_HAVE_QWORD */
#define VIO_CALLBACK_INIT(b, w, l, q) { b, w, l }
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */

struct vio_ops {
	/* VIO callbacks (`addr' is always relative to the data-block)
	 * NOTE:  For   unrecognized  addresses,   VIO  should   throw
	 *      `E_SEGFAULT_NOTREADABLE' / `E_SEGFAULT_NOTWRITABLE' exceptions.
	 * NOTE: Call operators are allowed to assume that the given `addr' has ~natural~ alignment:
	 *       f_byte:  No assumptions may be made
	 *       f_word:  Can assume that  `addr' is a multiple  of `2' (aka. `(addr & 1) == 0')
	 *       f_dword: Can assume that `addr' is  a multiple of `4' (aka.  `(addr & 3) == 0')
	 *       f_qword: Can assume that `addr' is  a multiple of `8' (aka.  `(addr & 7) == 0')
	 *       f_xword: Can assume that `addr' is a multiple of `16' (aka. `(addr & 15) == 0')
	 */
	struct {
		/* [0..1] Read memory */
		__ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *f_byte)(struct vioargs *__restrict args, vio_addr_t addr);
		__ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *f_word)(struct vioargs *__restrict args, vio_addr_t addr);
		__ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *f_dword)(struct vioargs *__restrict args, vio_addr_t addr);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		__ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *f_qword)(struct vioargs *__restrict args, vio_addr_t addr);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
	} vo_read;

	struct {
		/* [0..1] Write memory */
		__ATTR_NONNULL((1)) void (LIBVIO_CC *f_byte)(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t value);
		__ATTR_NONNULL((1)) void (LIBVIO_CC *f_word)(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t value);
		__ATTR_NONNULL((1)) void (LIBVIO_CC *f_dword)(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t value);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		__ATTR_NONNULL((1)) void (LIBVIO_CC *f_qword)(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t value);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
	} vo_write;

	struct {
		/* [0..1] Return the old value (regardless of the compare-exchange having been successful) */
		__ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *f_byte)(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t oldvalue, __uint8_t newvalue, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *f_word)(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t oldvalue, __uint16_t newvalue, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *f_dword)(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t oldvalue, __uint32_t newvalue, __BOOL atomic);
#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
		__ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *f_qword)(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t oldvalue, __uint64_t newvalue, __BOOL atomic);
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
		__ATTR_NONNULL((1)) __hybrid_uint128_t (LIBVIO_CC *f_xword)(struct vioargs *__restrict args, vio_addr_t addr, __hybrid_uint128_t oldvalue, __hybrid_uint128_t newvalue, __BOOL atomic);
#endif /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */
	} vo_cmpxch;

	struct {
		/* [0..1] Return the old value */
		__ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *f_byte)(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t newvalue, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *f_word)(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t newvalue, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *f_dword)(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t newvalue, __BOOL atomic);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		__ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *f_qword)(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t newvalue, __BOOL atomic);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
	} vo_xch;

	struct {
		/* [0..1] Return the old value (prior to be `value' being added) */
		__ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *f_byte)(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t value, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *f_word)(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t value, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *f_dword)(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t value, __BOOL atomic);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		__ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *f_qword)(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t value, __BOOL atomic);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
	} vo_add;

	struct {
		/* [0..1] Return the old value (prior to be `value' being subtracted) */
		__ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *f_byte)(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t value, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *f_word)(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t value, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *f_dword)(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t value, __BOOL atomic);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		__ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *f_qword)(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t value, __BOOL atomic);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
	} vo_sub;

	struct {
		/* [0..1] Return the old value (prior to be `mask' being anded) */
		__ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *f_byte)(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t mask, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *f_word)(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t mask, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *f_dword)(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t mask, __BOOL atomic);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		__ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *f_qword)(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t mask, __BOOL atomic);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
	} vo_and;

	struct {
		/* [0..1] Return the old value (prior to be `mask' being or'd) */
		__ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *f_byte)(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t mask, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *f_word)(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t mask, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *f_dword)(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t mask, __BOOL atomic);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		__ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *f_qword)(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t mask, __BOOL atomic);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
	} vo_or;

	struct {
		/* [0..1] Return the old value (prior to be `mask' being xor'd) */
		__ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *f_byte)(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t mask, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *f_word)(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t mask, __BOOL atomic);
		__ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *f_dword)(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t mask, __BOOL atomic);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		__ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *f_qword)(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t mask, __BOOL atomic);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
	} vo_xor;

	/* [0..1]
	 * Invoked as the result of the user attempting to call into VIO  memory.
	 * When this operator is called, `regs' will have already been updated to
	 * point  to the instruction following the call instruction that was used
	 * to execute VIO memory.
	 * USER:
	 * >> void *vio_base;
	 * >> vio_base = mmap(NULL, 0x1000, PROT_READ | PROT_EXEC, MAP_PRIVATE, vio_fd, 0);
	 * >>
	 * >> int (*vio_function)(int, int);
	 * >> *(void **)&vio_function = (byte_t *)vio_base + 1234;
	 * >>
	 * >> // This function will invoke `vo_call(args, 1234)'
	 * >> // vioargs_getstate(): (user-space register state; assuming i386)
	 * >> //    eip: RETURN_ADDRESS (here: ADDR_OF(ASSIGNMENT_TO_X))
	 * >> //    esp: [+0: (int)10, +4: (int)20]
	 * >> // `vo_call' can then assign the EAX register in `args' (again: assuming i386),
	 * >> // which is the value that's going to be returned to user-space and be assigned
	 * >> // to `x', before being printed.
	 * >> int x = (*vio_function)(10, 20);
	 * >>
	 * >> printf("x = %d\n", x); */
	void (LIBVIO_CC *vo_call)(struct vioargs *__restrict args, vio_addr_t addr);
};

/* Initializers for VIO callbacks */
#ifdef LIBVIO_CONFIG_HAVE_QWORD
#define VIO_CALLBACK_INIT_READ(b, w, l, q)  { b, w, l, q }
#define VIO_CALLBACK_INIT_WRITE(b, w, l, q) { b, w, l, q }
#define VIO_CALLBACK_INIT_XCH(b, w, l, q)   { b, w, l, q }
#define VIO_CALLBACK_INIT_ADD(b, w, l, q)   { b, w, l, q }
#define VIO_CALLBACK_INIT_SUB(b, w, l, q)   { b, w, l, q }
#define VIO_CALLBACK_INIT_AND(b, w, l, q)   { b, w, l, q }
#define VIO_CALLBACK_INIT_OR(b, w, l, q)    { b, w, l, q }
#define VIO_CALLBACK_INIT_XOR(b, w, l, q)   { b, w, l, q }
#else /* LIBVIO_CONFIG_HAVE_QWORD */
#define VIO_CALLBACK_INIT_READ(b, w, l, q)  { b, w, l }
#define VIO_CALLBACK_INIT_WRITE(b, w, l, q) { b, w, l }
#define VIO_CALLBACK_INIT_XCH(b, w, l, q)   { b, w, l }
#define VIO_CALLBACK_INIT_ADD(b, w, l, q)   { b, w, l }
#define VIO_CALLBACK_INIT_SUB(b, w, l, q)   { b, w, l }
#define VIO_CALLBACK_INIT_AND(b, w, l, q)   { b, w, l }
#define VIO_CALLBACK_INIT_OR(b, w, l, q)    { b, w, l }
#define VIO_CALLBACK_INIT_XOR(b, w, l, q)   { b, w, l }
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */

#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
#define VIO_CALLBACK_INIT_CMPXCH(b, w, l, q, i128) { b, w, l, q, i128 }
#else /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */
#define VIO_CALLBACK_INIT_CMPXCH(b, w, l, q, i128) { b, w, l, q }
#endif /* !LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */
#else /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
#define VIO_CALLBACK_INIT_CMPXCH(b, w, l, q, i128) { b, w, l, i128 }
#else /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */
#define VIO_CALLBACK_INIT_CMPXCH(b, w, l, q, i128) { b, w, l }
#endif /* !LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */
#endif /* !LIBVIO_CONFIG_HAVE_QWORD && !LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */

/* Initialize a set of VIO operators.
 * @param: *_callbacks: Initialize using `VIO_CALLBACK_INIT_*()' */
#define VIO_OPERATORS_INIT(read_callbacks, write_callbacks)                                                 \
	{                                                                                                       \
		/* .vo_read   = */ read_callbacks,                                                                  \
		/* .vo_write  = */ write_callbacks,                                                                 \
		/* .vo_cmpxch = */ VIO_CALLBACK_INIT_CMPXCH(__NULLPTR, __NULLPTR, __NULLPTR, __NULLPTR, __NULLPTR), \
		/* .vo_xch    = */ VIO_CALLBACK_INIT_XCH(__NULLPTR, __NULLPTR, __NULLPTR, __NULLPTR),               \
		/* .vo_add    = */ VIO_CALLBACK_INIT_ADD(__NULLPTR, __NULLPTR, __NULLPTR, __NULLPTR),               \
		/* .vo_sub    = */ VIO_CALLBACK_INIT_SUB(__NULLPTR, __NULLPTR, __NULLPTR, __NULLPTR),               \
		/* .vo_and    = */ VIO_CALLBACK_INIT_AND(__NULLPTR, __NULLPTR, __NULLPTR, __NULLPTR),               \
		/* .vo_or     = */ VIO_CALLBACK_INIT_OR(__NULLPTR, __NULLPTR, __NULLPTR, __NULLPTR),                \
		/* .vo_xor    = */ VIO_CALLBACK_INIT_XOR(__NULLPTR, __NULLPTR, __NULLPTR, __NULLPTR),               \
		/* .vo_call   = */ __NULLPTR                                                                        \
	}
#define VIO_OPERATORS_INIT_EX(read_callbacks,   \
                              write_callbacks,  \
                              cmpxch_callbacks, \
                              xch_callbacks,    \
                              add_callbacks,    \
                              sub_callbacks,    \
                              and_callbacks,    \
                              or_callbacks,     \
                              xor_callbacks,    \
                              call_callback)    \
	{                                           \
		/* .vo_read   = */ read_callbacks,      \
		/* .vo_write  = */ write_callbacks,     \
		/* .vo_cmpxch = */ cmpxch_callbacks,    \
		/* .vo_xch    = */ xch_callbacks,       \
		/* .vo_add    = */ add_callbacks,       \
		/* .vo_sub    = */ sub_callbacks,       \
		/* .vo_and    = */ and_callbacks,       \
		/* .vo_or     = */ or_callbacks,        \
		/* .vo_xor    = */ xor_callbacks,       \
		/* .vo_call   = */ call_callback        \
	}



/* High-level user-space VIO library functions. */
#ifndef __KERNEL__

/* vio_create(3):
 * >> fd_t vio_create(struct vio_ops *ops, void *cookie,
 * >>                 size_t initial_size, oflag_t flags);
 * Create  an mmap(2)able VIO object where memory accesses
 * made to the object are serviced by dispatching them via
 * the given `ops' table.
 * The returned file descriptor mustn't be deleted by `close(2)',
 * but rather through use of `vio_destroy(3)'.
 * Note  that callbacks in  `ops' may be  invoked in the context
 * of  a different thread than the one that performed the memory
 * access. Also note that the returned `fd_t' can be shared with
 * other processes, but still function as expected. (when shared
 * with a different process, that process should once again make
 * use  of `close(2)' for cleanup, rather than `vio_destroy(3)')
 * @param: flags:        Set of `0 | O_CLOEXEC | O_CLOFORK'
 * @param: cookie:       A cookie pointer that is available as `args->va_cookie'
 * @param: initial_size: The initial mmap(2)able size of the returned handle.
 *                       This  size may be  altered at a  later point in time
 *                       through use of `ftruncate(return)' */
typedef __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t
/*__NOTHROW_NCX*/ (LIBVIO_CC *PVIO_CREATE)(struct vio_ops const *ops, void *cookie,
                                           __size_t initial_size, __oflag_t flags);
#ifdef LIBVIO_WANT_PROTOTYPES
LIBVIO_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t
__NOTHROW_NCX(LIBVIO_CC vio_create)(struct vio_ops const *ops, void *cookie,
                                    __size_t initial_size, __oflag_t flags);
#endif /* LIBVIO_WANT_PROTOTYPES */


/* vio_destroy(3):
 * >> int vio_destroy(fd_t fd);
 * Destroy a VIO file descriptor previously created by `vio_create(3)' */
typedef int /*__NOTHROW_NCX*/ (LIBVIO_CC *PVIO_DESTROY)(__fd_t fd);
#ifdef LIBVIO_WANT_PROTOTYPES
LIBVIO_DECL int __NOTHROW_NCX(LIBVIO_CC vio_destroy)(__fd_t fd);
#endif /* LIBVIO_WANT_PROTOTYPES */

#endif /* !__KERNEL__ */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIO_VIO_H */
