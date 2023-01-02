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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_UVIO_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_UVIO_H 1

#include <kernel/compiler.h>

#include <libvio/api.h> /* LIBVIO_CONFIG_ENABLED */


/* The user-space VIO pipeline:
 *
 *  - #PF
 *  - Find mnode of faulting address
 *  - If node isn't a VIO node: regular PageFault
 *  - Call into libviocore:viocore_emulate() to implement memory dispatching
 *  - Use libemu86 to emulate the instruction that caused the memory access (on x86)
 *  - Go back into libviocore to filter emulated memory accesses pointing into VIO memory
 *  - Dispatch memory accesses via <libvio/access.h>
 *  - Functions  from <libvio/access.h> invoke kernel-space operators of the
 *    associated mfile's VIO function table (here, that table is `uvio_ops')
 *  - Functions from `uvio_ops' construct a request that is passed to `uvio_request()'
 *  - `uvio_request()' waits for a request slot to become available
 *  - `uvio_request()' stores the request in `struct uvio::uv_req' and broadcasts `uv_reqmore'
 *  - A dedicated user-space thread created alongside the UVIO object is resumed, such that
 *    a read(2) callback invoked by it on the UVIO object returns the request in the format
 *    of a  `struct uvio_request', before  changing the  request's state  to DELIVERED  and
 *    broadcasting `struct uvio::uv_reqdlvr'
 *  - User-space parses the returned request and dispatches it once again through a
 *    user-space  version  of the  `struct vio_ops'  structure that  was  passed to
 *    the dedicated thread upon creation.
 *  - The  actual user-space VIO  callback function performs the  request (if no appropriate
 *    callback   function   was    defined,   an   `E_SEGFAULT'    exception   is    thrown)
 *    Note that the  callback is able  to invoke  special HOP_* callbacks  for UVIO  objects
 *    in order to read/write execution registers of the instruction that caused the  access.
 *    Note  however that using this method to modify registers that may still be used during
 *    later portions of the emulated instruction's execution causes weak undefined behavior.
 *  - If the user-space VIO callback threw an exception or wasn't defined, that exception
 *    is returned in  a `UVIO_OPCODE_EXCEPT'  (or `UVIO_OPCODE_EXCEPT_COMPAT')  response.
 *    Otherwise, user-space returns the result of the VIO operator.
 *    In either case, the result is returned by write(2)ing a `struct uvio_response' to
 *    the userviofd file descriptor.
 *  - Kernel-space performs some validation of the written response structure
 *  - The response's result (or exception) is written back to the appropriate slot
 *    from     `struct uvio::uv_req',     and    `uv_reqdone'     is    broadcast.
 *  - The original faulting thread wakes up (after having previous waited for `uv_reqdone'),
 *    and   looks   at   `struct kernel_uvio_request::kur_status'  of   its   request  slot.
 *  - If the status indicates an exception, that exception is re-thrown (that exception
 *    being   the   original    exception   from   the    user-space   VIO    callback)
 *    Otherwise,  the  correct  VIO  result  value  is  returned  by   `uvio_request()'
 *  - Irregardless of an exception having been thrown, the request slot is marked as
 *    free, and `struct uvio::uv_reqfree' is broadcast.
 *  - In case of an  exception, that exception is  propagated normally with its  fault
 *    address set to the starting address of instruction that caused the original  #PF
 *    Otherwise,  the return value  is passed through to  libviocore, which once again
 *    uses libemu86 to  store/process that  value as appropriate  for the  instruction
 *    that is being emulated. Note that during this phase, additional memory accesses,
 *    including further accesses to VIO memory may occur.
 *
 * NOTES:
 *  - Using  this  model, it  becomes  possible for  kernel-space  to access  user-space VIO
 *    memory (which can  reasonably happen  when user-space  passes pointers  to VIO  memory
 *    to system calls).  When this happens,  the VIO  memory accesses are  handled the  same
 *    way  as  they  would have  been  if the  accessed  had been  performed  by user-space,
 *    with the only exception that all attempts  at accessing the registers of the  faulting
 *    thread  are  denied (or  may  instead return  information  about to  user-space return
 *    location of the thread performing the memory access; in any case: a kernel-only-thread
 *    accessing user-space VIO (which really shouldn't happen to begin with) _always_ causes
 *    an error when user-space attempts to access its registers)
 *  - A  VIO request may be aborted when the faulting thread is interrupted while it is
 *    waiting for its request to be serviced. In this case, the service thread is _not_
 *    notified of this event, and the eventual response is silently discarded.
 *
 */


#ifdef LIBVIO_CONFIG_ENABLED
#include <kernel/mman/mfile.h>
#include <kernel/types.h>
#include <sched/sig.h>

#include <hybrid/byteorder.h>
#include <hybrid/sched/atomic-rwlock.h>

#include <libvio/userviofd.h>
#include <libvio/vio.h>

/*[[[config CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS! = 4
 * Max # of UVIO requests  that can be in use  at
 * the same time for any given UVIO mfile object.
 * ]]]*/
#ifndef CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS
#define CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS 4
#endif /* !CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS */
/*[[[end]]]*/


/* 255 is the upper limit on how many parallel requests are physically possible
 * This  limit is imposed  by only 8 bits  being available for  slot IDs in the
 * user-space  UVIO  structure  `struct uvio_request::uq_reqid'  (which,  while
 * actually being 16-bit,  only has the  lower 8 bits  available for slot  IDs,
 * while the upper 8 bits  are used as a version  counter that must be  matched
 * in order to reduce the chance of miss-matching aborted requests) */
#if CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS > 0xff
#undef CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS
#define CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS 0xff
#endif /* CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS > 0xff */


#undef SIZEOF_KERNEL_UVIO_UINTMAX_T
#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
#define SIZEOF_KERNEL_UVIO_UINTMAX_T 16
#elif defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
#define SIZEOF_KERNEL_UVIO_UINTMAX_T 8
#else /* ... */
#define SIZEOF_KERNEL_UVIO_UINTMAX_T 4
#endif /* !... */

#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 16
#include <int128.h>
#endif /* SIZEOF_KERNEL_UVIO_UINTMAX_T >= 16 */

DECL_BEGIN

#ifdef __CC__

#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 16
#define kernel_uvio_argument_initzero(self) uint128_setzero((self)->kua_x)
#elif SIZEOF_KERNEL_UVIO_UINTMAX_T >= 8
#define kernel_uvio_argument_initzero(self) ((self)->kua_q = 0)
#elif SIZEOF_KERNEL_UVIO_UINTMAX_T >= 4
#define kernel_uvio_argument_initzero(self) ((self)->kua_l = 0)
#elif SIZEOF_KERNEL_UVIO_UINTMAX_T >= 2
#define kernel_uvio_argument_initzero(self) ((self)->kua_w = 0)
#else /* SIZEOF_KERNEL_UVIO_UINTMAX_T >= ... */
#define kernel_uvio_argument_initzero(self) ((self)->kua_b = 0)
#endif /* SIZEOF_KERNEL_UVIO_UINTMAX_T < ... */

union kernel_uvio_argument {
#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 16
	uint128_t kua_x;  /* First argument (128-bit) */
	u64 kua_x_as_q[2];  /* First argument (128-bit; as 64-bit vector) */
	u32 kua_x_as_l[4];  /* First argument (128-bit; as 32-bit vector) */
	u16 kua_x_as_w[8];  /* First argument (128-bit; as 16-bit vector) */
	u8  kua_x_as_b[16]; /* First argument (128-bit; as 8-bit vector) */
#endif /* SIZEOF_KERNEL_UVIO_UINTMAX_T >= 16 */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 8
	u64 kua_q;          /* First argument (64-bit) */
	u32 kua_q_as_l[2];  /* First argument (64-bit; as 32-bit vector) */
	u16 kua_q_as_w[4];  /* First argument (64-bit; as 16-bit vector) */
	u8  kua_q_as_b[8];  /* First argument (64-bit; as 8-bit vector) */
#endif /* SIZEOF_KERNEL_UVIO_UINTMAX_T >= 8 */
#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 4
	u32 kua_l;          /* First argument (32-bit) */
	u16 kua_l_as_w[2];  /* First argument (32-bit; as 16-bit vector) */
	u8  kua_l_as_b[4];  /* First argument (32-bit; as 8-bit vector) */
#endif /* SIZEOF_KERNEL_UVIO_UINTMAX_T >= 4 */
#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 2
	u16 kua_w;          /* First argument (16-bit) */
	u8  kua_w_as_b[2];  /* First argument (16-bit; as 8-bit vector) */
#endif /* SIZEOF_KERNEL_UVIO_UINTMAX_T >= 2 */
#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 1
	u8  kua_b;          /* First argument (8-bit) */
#endif /* SIZEOF_KERNEL_UVIO_UINTMAX_T >= 1 */
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 2
	struct {
		u8  _kua_b_pad[(SIZEOF_KERNEL_UVIO_UINTMAX_T / 1) - 1]; /* ... */
		u8   kua_b;  /* First argument (8-bit) */
	}; /* TODO: #ifndef __COMPILER_HAVE_TRANSPARENT_STRUCT */
#elif SIZEOF_KERNEL_UVIO_UINTMAX_T >= 1
	u8   kua_b;  /* First argument (8-bit) */
#endif /* ... */
#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 4
	struct {
		u16 _kua_w_pad[(SIZEOF_KERNEL_UVIO_UINTMAX_T / 2) - 1]; /* ... */
		union {
			u16 kua_w;         /* First argument (16-bit) */
			u8  kua_w_as_b[2]; /* First argument (16-bit; as 8-bit vector) */
		}; /* TODO: #ifndef __COMPILER_HAVE_TRANSPARENT_UNION */
	}; /* TODO: #ifndef __COMPILER_HAVE_TRANSPARENT_STRUCT */
#elif SIZEOF_KERNEL_UVIO_UINTMAX_T >= 2
	u16 kua_w;         /* First argument (16-bit) */
	u8  kua_w_as_b[2]; /* First argument (16-bit; as 8-bit vector) */
#endif /* ... */
#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 8
	struct {
		u32 _kua_l_pad[(SIZEOF_KERNEL_UVIO_UINTMAX_T / 4) - 1]; /* ... */
		union {
			u32 kua_l;         /* First argument (32-bit) */
			u16 kua_l_as_w[2]; /* First argument (32-bit; as 16-bit vector) */
			u8  kua_l_as_b[4]; /* First argument (32-bit; as 8-bit vector) */
		}; /* TODO: #ifndef __COMPILER_HAVE_TRANSPARENT_UNION */
	}; /* TODO: #ifndef __COMPILER_HAVE_TRANSPARENT_STRUCT */
#elif SIZEOF_KERNEL_UVIO_UINTMAX_T >= 4
	u32 kua_l;         /* First argument (32-bit) */
	u16 kua_l_as_w[2]; /* First argument (32-bit; as 16-bit vector) */
	u8  kua_l_as_b[4]; /* First argument (32-bit; as 8-bit vector) */
#endif /* ... */
#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 16
	struct {
		u64 _kua_q_pad[(SIZEOF_KERNEL_UVIO_UINTMAX_T / 8) - 1]; /* ... */
		union {
			u64 kua_q;         /* First argument (64-bit) */
			u32 kua_q_as_l[2]; /* First argument (64-bit; as 32-bit vector) */
			u16 kua_q_as_w[4]; /* First argument (64-bit; as 16-bit vector) */
			u8  kua_q_as_b[8]; /* First argument (64-bit; as 8-bit vector) */
		};
	}; /* TODO: #ifndef __COMPILER_HAVE_TRANSPARENT_STRUCT */
#elif SIZEOF_KERNEL_UVIO_UINTMAX_T >= 8
	u64 kua_q;         /* First argument (64-bit) */
	u32 kua_q_as_l[2]; /* First argument (64-bit; as 32-bit vector) */
	u16 kua_q_as_w[4]; /* First argument (64-bit; as 16-bit vector) */
	u8  kua_q_as_b[8]; /* First argument (64-bit; as 8-bit vector) */
#endif /* ... */
#else /* __BYTE_ORDER__ == ... */
#error "Unsupported endian"
#endif /* __BYTE_ORDER__ != ... */
};


/* Construct a UVIO command.
 * @param: opcode: One of `UVIO_OPCODE_*'
 * @param: flags:  Set of `UVIO_REQUEST_FLAG_*' */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define KERNEL_UVIO_COMMAND(opcode, flags) ((u16)(opcode) | (u16)(flags) << 8)
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define KERNEL_UVIO_COMMAND(opcode, flags) ((u16)(opcode) << 8 | (u16)(flags))
#else /* __BYTE_ORDER__ == ... */
#error "Unsupported endian"
#endif /* __BYTE_ORDER__ != ... */

/* Codes for `struct kernel_uvio_request::kur_status' */
#define KERNEL_UVIO_REQUEST_STATUS_PENDING   0 /* Request is pending */
#define KERNEL_UVIO_REQUEST_STATUS_DELIVERED 1 /* The request was sent to the user-space server */
#define KERNEL_UVIO_REQUEST_STATUS_COMPLETE  2 /* The request has completed successfully. */
#define KERNEL_UVIO_REQUEST_STATUS_EXCEPT    3 /* The request has completed with an exception. */

struct kernel_uvio_except {
	except_code_t kue_code;                              /* Exception code (one of `EXCEPT_CODEOF(*)') */
	uintptr_t     kue_pointers[EXCEPTION_DATA_POINTERS]; /* Exception pointers */
};

struct kernel_uvio_request {
	struct atomic_rwlock  kur_lock;        /* Lock for this request
	                                        * If a request is aborted, this lock is temporarily  acquired
	                                        * in write-mode to ensure that no other thread is still using
	                                        * the below pointer, before `kur_args' is cleared to `NULL' */
	WEAK u32              kur_nextuid_seed;/* [lock(ATOMIC)] Pseudo-random seed for the next `kur_uid' */
#if __SIZEOF_POINTER__ > 4
	u8                    kur_pad[__SIZEOF_POINTER__ - 4]; /* ... */
#endif /* __SIZEOF_POINTER__ > 4 */
	struct vioargs       *kur_args;        /* [0..1][lock(kur_lock)] VIO arguments.
	                                        * When set to `NULL', the request is considered to be free. */
	struct task          *kur_orig;        /* [1..1][valid_if(kur_args)][lock(kur_lock)] The sender thread. */
	union {
		u16               kur_cmd;         /* [valid_if(kur_args)][lock(kur_lock)] The request command (construct using `KERNEL_UVIO_COMMAND') */
		struct {
			u8            kur_opcode;      /* [valid_if(kur_args)][lock(kur_lock)] The request opcode (one of `UVIO_OPCODE_*') */
			u8            kur_reqflags;    /* [valid_if(kur_args)][lock(kur_lock)] Request flags (set of `UVIO_REQUEST_FLAG_*') */
		};
	};
	u8                    kur_status;      /* [valid_if(kur_args)] Request status (one of `KERNEL_UVIO_REQUEST_STATUS_*') */
	u8                    kur_uid;         /* [valid_if(kur_args)] (Pseudo-)unique request ID (to reduce the risk of miss-matching responses to aborted requests) */
#if __SIZEOF_POINTER__ > 4
	u8                    kur_pad2[__SIZEOF_POINTER__ - 4]; /* ... */
#endif /* __SIZEOF_POINTER__ > 4 */
	vio_addr_t            kur_addr;        /* [valid_if(kur_args)][lock(kur_lock)] The address being accessed. */
	union {
		union kernel_uvio_argument kur_res;     /* [valid_if(KERNEL_UVIO_REQUEST_STATUS_COMPLETE)] Request result. */
		union kernel_uvio_argument kur_argv[2]; /* [valid_if(KERNEL_UVIO_REQUEST_STATUS_PENDING || KERNEL_UVIO_REQUEST_STATUS_DELIVERED)] Request arguments. */
		struct kernel_uvio_except  kur_except;  /* [valid_if(KERNEL_UVIO_REQUEST_STATUS_EXCEPT)] Request exception. */
	};
};

/* Helper macros for working with `struct kernel_uvio_request::kur_lock' */
#define _kernel_uvio_request_reap(self)        (void)0
#define kernel_uvio_request_reap(self)         (void)0
#define kernel_uvio_request_mustreap(self)     0
#define kernel_uvio_request_write(self)        atomic_rwlock_write(&(self)->kur_lock)
#define kernel_uvio_request_write_nx(self)     atomic_rwlock_write_nx(&(self)->kur_lock)
#define kernel_uvio_request_trywrite(self)     atomic_rwlock_trywrite(&(self)->kur_lock)
#define kernel_uvio_request_endwrite(self)     (atomic_rwlock_endwrite(&(self)->kur_lock), kernel_uvio_request_reap(self))
#define _kernel_uvio_request_endwrite(self)    atomic_rwlock_endwrite(&(self)->kur_lock)
#define kernel_uvio_request_read(self)         atomic_rwlock_read(&(self)->kur_lock)
#define kernel_uvio_request_read_nx(self)      atomic_rwlock_read_nx(&(self)->kur_lock)
#define kernel_uvio_request_tryread(self)      atomic_rwlock_tryread(&(self)->kur_lock)
#define _kernel_uvio_request_endread(self)     atomic_rwlock_endread(&(self)->kur_lock)
#define kernel_uvio_request_endread(self)      (void)(atomic_rwlock_endread(&(self)->kur_lock) && (kernel_uvio_request_reap(self), 0))
#define _kernel_uvio_request_end(self)         atomic_rwlock_end(&(self)->kur_lock)
#define kernel_uvio_request_end(self)          (void)(atomic_rwlock_end(&(self)->kur_lock) && (kernel_uvio_request_reap(self), 0))
#define kernel_uvio_request_upgrade(self)      atomic_rwlock_upgrade(&(self)->kur_lock)
#define kernel_uvio_request_upgrade_nx(self)   atomic_rwlock_upgrade_nx(&(self)->kur_lock)
#define kernel_uvio_request_tryupgrade(self)   atomic_rwlock_tryupgrade(&(self)->kur_lock)
#define kernel_uvio_request_downgrade(self)    atomic_rwlock_downgrade(&(self)->kur_lock)
#define kernel_uvio_request_reading(self)      atomic_rwlock_reading(&(self)->kur_lock)
#define kernel_uvio_request_writing(self)      atomic_rwlock_writing(&(self)->kur_lock)
#define kernel_uvio_request_canread(self)      atomic_rwlock_canread(&(self)->kur_lock)
#define kernel_uvio_request_canwrite(self)     atomic_rwlock_canwrite(&(self)->kur_lock)
#define kernel_uvio_request_waitread(self)     atomic_rwlock_waitread(&(self)->kur_lock)
#define kernel_uvio_request_waitwrite(self)    atomic_rwlock_waitwrite(&(self)->kur_lock)
#define kernel_uvio_request_waitread_nx(self)  atomic_rwlock_waitread_nx(&(self)->kur_lock)
#define kernel_uvio_request_waitwrite_nx(self) atomic_rwlock_waitwrite_nx(&(self)->kur_lock)


struct uvio
#ifdef __cplusplus
    : mfile                                /* The underlying mem-file */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct mfile               uv_file;    /* The underlying mem-file */
#endif /* __cplusplus */
	struct sig                 uv_reqmore; /* Signal send when a new request becomes `KERNEL_UVIO_REQUEST_STATUS_PENDING'. */
	struct sig                 uv_reqdlvr; /* Signal broadcast when a new request becomes `KERNEL_UVIO_REQUEST_STATUS_DELIVERED'. */
	struct sig                 uv_reqdone; /* Signal broadcast when a new request becomes `KERNEL_UVIO_REQUEST_STATUS_COMPLETE' or `KERNEL_UVIO_REQUEST_STATUS_EXCEPT'. */
	struct sig                 uv_reqfree; /* Signal send when a request slot is freed. */
	struct kernel_uvio_request uv_req[CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS]; /* Vector of UVIO requests. */
};

#define mfile_asuvio(self) ((struct uvio *)(self))


/* The mfile type used by UVIO objects. */
DATDEF struct mfile_ops const uvio_mfile_ops;

/* VIO operator callbacks for UVIO mfiles. */
DATDEF struct vio_ops const uvio_ops;

/* Construct a new UVIO object.
 * Note that UVIO is derived from `struct mfile', so the returned
 * object can be stored in  a handle slot as  `HANDLE_TYPE_MFILE' */
FUNDEF REF struct uvio *KCALL uvio_create(void) THROWS(E_BADALLOC);

/* Perform a remove VIO request.
 * @param: args:        VIO arguments (`va_file' must be a `struct uvio')
 * @param: addr:        The VIO address being accessed.
 * @param: command:     Constructed using `KERNEL_UVIO_COMMAND()'
 * @param: argv_result: [in]  VIO arguments
 *                            WARNING: copied to user-space; caller must
 *                                     ensure that unused bytes are initialized!
 *                      [out] First item contains the request result.
 *                            WARNING: copied from user-space; unused bits/bytes
 *                                     must be ignored in this value.
 * @throws: ...:        If  user-space  returned  with  `UVIO_OPCODE_EXCEPT',
 *                      that is exception will be re-thrown by this function. */
FUNDEF BLOCKING NONNULL((1, 4)) void KCALL
uvio_request(/*in|out*/ struct vioargs *__restrict args, vio_addr_t addr, u16 command,
             /*in|out*/ union kernel_uvio_argument argv_result[2]) THROWS(...);


/* Helper wrappers for `uvio_request()' */
#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 1
FUNDEF BLOCKING NONNULL((1)) uint8_t KCALL
uvio_requestb(/*in|out*/ struct vioargs *__restrict args, vio_addr_t addr, u16 command,
              uint8_t arg0 DFL(0), uint8_t arg1 DFL(0)) THROWS(...);
#endif /* SIZEOF_KERNEL_UVIO_UINTMAX_T >= 1 */

#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 2
FUNDEF BLOCKING NONNULL((1)) uint16_t KCALL
uvio_requestw(/*in|out*/ struct vioargs *__restrict args, vio_addr_t addr, u16 command,
              uint16_t arg0 DFL(0), uint16_t arg1 DFL(0)) THROWS(...);
#endif /* SIZEOF_KERNEL_UVIO_UINTMAX_T >= 2 */

#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 4
FUNDEF BLOCKING NONNULL((1)) uint32_t KCALL
uvio_requestl(/*in|out*/ struct vioargs *__restrict args, vio_addr_t addr, u16 command,
              uint32_t arg0 DFL(0), uint32_t arg1 DFL(0)) THROWS(...);
#endif /* SIZEOF_KERNEL_UVIO_UINTMAX_T >= 4 */

#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 8
FUNDEF BLOCKING NONNULL((1)) uint64_t KCALL
uvio_requestq(/*in|out*/ struct vioargs *__restrict args, vio_addr_t addr, u16 command,
              uint64_t arg0 DFL(0), uint64_t arg1 DFL(0)) THROWS(...);
#endif /* SIZEOF_KERNEL_UVIO_UINTMAX_T >= 8 */

#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 16
#ifdef __UINT128_TYPE__
FUNDEF BLOCKING NONNULL((1)) uint128_t KCALL
uvio_requestx(/*in|out*/ struct vioargs *__restrict args, vio_addr_t addr, u16 command,
              uint128_t arg0 DFL(0), uint128_t arg1 DFL(0)) THROWS(...);
#else /* __UINT128_TYPE__ */
FUNDEF BLOCKING NONNULL((1)) uint128_t KCALL
uvio_requestx(/*in|out*/ struct vioargs *__restrict args, vio_addr_t addr, u16 command,
              uint128_t arg0, uint128_t arg1) THROWS(...);
#endif /* !__UINT128_TYPE__ */
#endif /* SIZEOF_KERNEL_UVIO_UINTMAX_T >= 16 */


#endif /* __CC__ */

DECL_END

#endif /* LIBVIO_CONFIG_ENABLED */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_UVIO_H */
