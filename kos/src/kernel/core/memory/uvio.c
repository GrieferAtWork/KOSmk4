/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_UVIO_C
#define GUARD_KERNEL_SRC_MEMORY_UVIO_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <libvio/api.h> /* LIBVIO_CONFIG_ENABLED */

#ifdef LIBVIO_CONFIG_ENABLED
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/malloc.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/uvio.h>
#include <kernel/printk.h>
#include <kernel/rand.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <sched/group.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <kos/except/reason/inval.h>
#include <kos/io.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <assert.h>
#include <atomic.h>
#include <stddef.h>
#include <string.h>

#include <libvio/userviofd.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

PRIVATE NOBLOCK WUNUSED u8
NOTHROW(KCALL kernel_uvio_request_randuid)(struct kernel_uvio_request *__restrict self) {
	u32 result;
	result = krand32_r(&self->kur_nextuid_seed);
	/* Merge entropy into the lowest byte. */
	result ^= result >> 16;
	result ^= result >> 8;
	return (u8)result;
}


/* Perform a UVIO request using slow `reqid'
 * NOTE: The caller already acquired a lock to `slot->kur_lock',
 *       and  made  sure   that  `slot->kur_args'  was   `NULL'!
 * NOTE: The caller is responsible to free the slot once this
 *       function returns, even if it returns by throwing  an
 *       exception! */
PRIVATE NONNULL((1, 2, 3, 6)) void KCALL
uvio_request_impl(struct uvio *__restrict self,
                  struct kernel_uvio_request *__restrict slot,
                  /*in|out*/ struct vioargs *__restrict args,
                  vio_addr_t addr, u16 command,
                  /*in|out*/ union kernel_uvio_argument argv_result[2]) THROWS(...) {
	u8 status;

	/* Fill in request information */
	slot->kur_args   = args;
	slot->kur_orig   = THIS_TASK;
	slot->kur_cmd    = command;
	slot->kur_status = KERNEL_UVIO_REQUEST_STATUS_PENDING;
	slot->kur_addr   = addr;
	slot->kur_uid    = kernel_uvio_request_randuid(slot);
	memcpy(slot->kur_argv, argv_result, 2,
	       sizeof(union kernel_uvio_argument));
	/* Unlock the slot. */
	kernel_uvio_request_endwrite(slot);

	/* Signal that a new request has become available. */
	sig_send(&self->uv_reqmore);

	/* Wait for our request to complete. */
	for (;;) {
		status = atomic_read(&slot->kur_status);
		if (status == KERNEL_UVIO_REQUEST_STATUS_COMPLETE ||
		    status == KERNEL_UVIO_REQUEST_STATUS_EXCEPT)
			break; /* Request has completed (either successfully, or with an exception) */
		task_connect_for_poll(&self->uv_reqdone);
		status = atomic_read(&slot->kur_status);
		if (status == KERNEL_UVIO_REQUEST_STATUS_COMPLETE ||
		    status == KERNEL_UVIO_REQUEST_STATUS_EXCEPT) {
			task_disconnectall();
			break; /* Request has completed (either successfully, or with an exception) */
		}

		/* Wait for the request to complete. */
		task_waitfor();
	}

	/* Handle an exception completion status. */
	if (status == KERNEL_UVIO_REQUEST_STATUS_EXCEPT) {
		unsigned int i;
		void const *pc;

		/* Use the program counter from the VIO-args cpu-state as fault address. */
		pc = icpustate_getpc(args->va_state);
		PERTASK_SET(this_exception_data.e_faultaddr, pc);

		/* Fill in the exception code and exception pointers. */
		PERTASK_SET(this_exception_data.e_code, slot->kur_except.kue_code);
		for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i) {
			PERTASK_SET(this_exception_data.e_args.e_pointers[i],
			            slot->kur_except.kue_pointers[i]);
		}
		except_throw_current();
	}

	/* Success-status. -> Copy the request result into `argv_result' */
	memcpy(argv_result, &slot->kur_res, sizeof(union kernel_uvio_argument));
}


/* Mark a given UVIO request slot as free. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL uvio_freerequest)(struct uvio *__restrict self,
                                unsigned int reqid) {
	struct kernel_uvio_request *slot;
	slot = &self->uv_req[reqid];
	/* Acquire a write-lock to the request so-as to ensure that no
	 * other  thread is still trying to make use of `kur_args', or
	 * any of the other pointers within the request descriptor.
	 * NOTE: By having  `uvio_request()' require  that preemption  be
	 *       enabled (which it  needs to be  anyways, because if  the
	 *       request handling server is running in user-space we need
	 *       to have preemption enabled in order to be able to switch
	 *       execute to the server thread), we can safely make use of
	 *       `task_yield()' here  to  wait  for the  lock  to  become
	 *       available. */
	assert(PREEMPTION_ENABLED());
	kernel_uvio_request_write(slot);

	/* Mark as free */
	atomic_write(&slot->kur_args, NULL);
	DBG_memset(&slot->kur_orig, 0xcc,
	           sizeof(struct kernel_uvio_request) -
	           offsetof(struct kernel_uvio_request, kur_orig));
	kernel_uvio_request_endwrite(slot);

	/* Signal that a free slot became available */
	sig_send(&self->uv_reqfree);
}


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
PUBLIC BLOCKING NONNULL((1, 4)) void KCALL
uvio_request(/*in|out*/ struct vioargs *__restrict args, vio_addr_t addr, u16 command,
             /*in|out*/ union kernel_uvio_argument argv_result[2]) THROWS(...) {
	struct uvio *self;
	unsigned int reqid;
	struct kernel_uvio_request *slot;
	assert(!task_wasconnected());
	self = (struct uvio *)args->va_file;
	assert(self->mf_ops == &uvio_mfile_ops);
	assert(self->mf_ops->mo_vio == &uvio_ops);

	/* UVIO request have a _mandatory_ dependency on preemption being enabled.
	 * If  preemption  were disabled,  `uvio_freerequest()'  could deadlock... */
	if unlikely(!PREEMPTION_ENABLED())
		THROW(E_WOULDBLOCK_PREEMPTED);
again:

	/* Find a free request slot and try to allocate it. */
	for (reqid = 0; reqid < CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS; ++reqid) {
		slot = &self->uv_req[reqid];
		kernel_uvio_request_write(slot);
		if (self->uv_req[reqid].kur_args) {
			kernel_uvio_request_endwrite(slot);
			continue; /* Already in use. */
		}

got_free_slot:
		/* Found (and allocated) a free slot.
		 * Now use this slot for the request. */
		RAII_FINALLY {
			/* Always mark the slot as free before returning! */
			uvio_freerequest(self, reqid);
		};
		uvio_request_impl(self, slot, args,
		                  addr, command,
		                  argv_result);
		return;
	}

	/* Wait for more slots to become available. */
	task_connect(&self->uv_reqfree);
	TRY {
		for (reqid = 0; reqid < CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS; ++reqid) {
			slot = &self->uv_req[reqid];
			kernel_uvio_request_write(slot);
			if (self->uv_req[reqid].kur_args) {
				kernel_uvio_request_endwrite(slot);
				continue; /* Already in use. */
			}

			/* Unlikely case: A free slot was discovered during interlocked re-check */
			task_disconnectall();
			goto got_free_slot;
		}
	} EXCEPT {
		task_disconnectall();
		RETHROW();
	}

	/* Wait for the a slot to become free. */
	task_waitfor();
	goto again;
}

#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 1
PUBLIC BLOCKING NONNULL((1)) uint8_t KCALL
uvio_requestb(/*in|out*/ struct vioargs *__restrict args,
              vio_addr_t addr, u16 command,
              uint8_t arg0, uint8_t arg1) THROWS(...) {
	union kernel_uvio_argument argv_result[2];
	kernel_uvio_argument_initzero(&argv_result[0]);
	kernel_uvio_argument_initzero(&argv_result[1]);
	argv_result[0].kua_b = arg0;
	argv_result[1].kua_b = arg1;
	uvio_request(args, addr, command, argv_result);
	return argv_result[0].kua_b;
}
#endif /* SIZEOF_KERNEL_UVIO_UINTMAX_T >= 1 */

#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 2
PUBLIC BLOCKING NONNULL((1)) uint16_t KCALL
uvio_requestw(/*in|out*/ struct vioargs *__restrict args,
              vio_addr_t addr, u16 command,
              uint16_t arg0, uint16_t arg1) THROWS(...) {
	union kernel_uvio_argument argv_result[2];
	kernel_uvio_argument_initzero(&argv_result[0]);
	kernel_uvio_argument_initzero(&argv_result[1]);
	argv_result[0].kua_w = arg0;
	argv_result[1].kua_w = arg1;
	uvio_request(args, addr, command, argv_result);
	return argv_result[0].kua_w;
}
#endif /* SIZEOF_KERNEL_UVIO_UINTMAX_T >= 2 */

#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 4
PUBLIC BLOCKING NONNULL((1)) uint32_t KCALL
uvio_requestl(/*in|out*/ struct vioargs *__restrict args,
              vio_addr_t addr, u16 command,
              uint32_t arg0, uint32_t arg1) THROWS(...) {
	union kernel_uvio_argument argv_result[2];
	kernel_uvio_argument_initzero(&argv_result[0]);
	kernel_uvio_argument_initzero(&argv_result[1]);
	argv_result[0].kua_l = arg0;
	argv_result[1].kua_l = arg1;
	uvio_request(args, addr, command, argv_result);
	return argv_result[0].kua_l;
}
#endif /* SIZEOF_KERNEL_UVIO_UINTMAX_T >= 4 */

#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 8
PUBLIC BLOCKING NONNULL((1)) uint64_t KCALL
uvio_requestq(/*in|out*/ struct vioargs *__restrict args,
              vio_addr_t addr, u16 command,
              uint64_t arg0, uint64_t arg1) THROWS(...) {
	union kernel_uvio_argument argv_result[2];
	kernel_uvio_argument_initzero(&argv_result[0]);
	kernel_uvio_argument_initzero(&argv_result[1]);
	argv_result[0].kua_q = arg0;
	argv_result[1].kua_q = arg1;
	uvio_request(args, addr, command, argv_result);
	return argv_result[0].kua_q;
}
#endif /* SIZEOF_KERNEL_UVIO_UINTMAX_T >= 8 */

#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 16
PUBLIC BLOCKING NONNULL((1)) uint128_t KCALL
uvio_requestx(/*in|out*/ struct vioargs *__restrict args,
              vio_addr_t addr, u16 command,
              uint128_t arg0, uint128_t arg1) THROWS(...) {
	union kernel_uvio_argument argv_result[2];
	kernel_uvio_argument_initzero(&argv_result[0]);
	kernel_uvio_argument_initzero(&argv_result[1]);
	argv_result[0].kua_x = arg0;
	argv_result[1].kua_x = arg1;
	uvio_request(args, addr, command, argv_result);
	return argv_result[0].kua_x;
}
#endif /* SIZEOF_KERNEL_UVIO_UINTMAX_T >= 16 */


/* Define wrappers for operators from `uvio_ops' */
#define DEFINE_UNARY_VIO_OPERATOR(name, bwlqx, T, opcode)                          \
	PRIVATE NONNULL((1)) T LIBVIO_CC                                               \
	name(struct vioargs *__restrict args, vio_addr_t addr) {                       \
		return uvio_request##bwlqx(args, addr,                                     \
		                           KERNEL_UVIO_COMMAND(opcode,                     \
		                                               UVIO_REQUEST_FLAG_NORMAL)); \
	}
#define DEFINE_BINARY_VIO_OPERATOR_VOID(name, bwlqx, T, opcode)            \
	PRIVATE NONNULL((1)) void LIBVIO_CC                                    \
	name(struct vioargs *__restrict args, vio_addr_t addr, T arg0) {       \
		uvio_request##bwlqx(args, addr,                                    \
		                    KERNEL_UVIO_COMMAND(opcode,                    \
		                                        UVIO_REQUEST_FLAG_NORMAL), \
		                    arg0);                                         \
	}
#define DEFINE_BINARY_VIO_OPERATOR_ATOMIC(name, bwlqx, T, opcode)                          \
	PRIVATE NONNULL((1)) T LIBVIO_CC                                                       \
	name(struct vioargs *__restrict args, vio_addr_t addr, T arg0, bool atomic) {          \
		return uvio_request##bwlqx(args, addr,                                             \
		                           KERNEL_UVIO_COMMAND(opcode,                             \
		                                               atomic ? UVIO_REQUEST_FLAG_ATOMIC   \
		                                                      : UVIO_REQUEST_FLAG_NORMAL), \
		                           arg0);                                                  \
	}

#define DEFINE_TRINARY_VIO_OPERATOR_ATOMIC(name, bwlqx, T, opcode)                         \
	PRIVATE NONNULL((1)) T LIBVIO_CC                                                       \
	name(struct vioargs *__restrict args, vio_addr_t addr, T arg0, T arg1, bool atomic) {  \
		return uvio_request##bwlqx(args, addr,                                             \
		                           KERNEL_UVIO_COMMAND(opcode,                             \
		                                               atomic ? UVIO_REQUEST_FLAG_ATOMIC   \
		                                                      : UVIO_REQUEST_FLAG_NORMAL), \
		                           arg0, arg1);                                            \
	}

DEFINE_UNARY_VIO_OPERATOR(uvio_operator_readb, b, uint8_t, UVIO_OPCODE_READB)
DEFINE_UNARY_VIO_OPERATOR(uvio_operator_readw, w, uint16_t, UVIO_OPCODE_READW)
DEFINE_UNARY_VIO_OPERATOR(uvio_operator_readl, l, uint32_t, UVIO_OPCODE_READL)
#ifdef LIBVIO_CONFIG_HAVE_QWORD
DEFINE_UNARY_VIO_OPERATOR(uvio_operator_readq, q, uint64_t, UVIO_OPCODE_READQ)
#endif /* LIBVIO_CONFIG_HAVE_QWORD */

DEFINE_BINARY_VIO_OPERATOR_VOID(uvio_operator_writeb, b, uint8_t, UVIO_OPCODE_WRITEB)
DEFINE_BINARY_VIO_OPERATOR_VOID(uvio_operator_writew, w, uint16_t, UVIO_OPCODE_WRITEW)
DEFINE_BINARY_VIO_OPERATOR_VOID(uvio_operator_writel, l, uint32_t, UVIO_OPCODE_WRITEL)
#ifdef LIBVIO_CONFIG_HAVE_QWORD
DEFINE_BINARY_VIO_OPERATOR_VOID(uvio_operator_writeq, q, uint64_t, UVIO_OPCODE_WRITEQ)
#endif /* LIBVIO_CONFIG_HAVE_QWORD */

DEFINE_TRINARY_VIO_OPERATOR_ATOMIC(uvio_operator_cmpxchb, b, uint8_t, UVIO_OPCODE_CMPXCHB)
DEFINE_TRINARY_VIO_OPERATOR_ATOMIC(uvio_operator_cmpxchw, w, uint16_t, UVIO_OPCODE_CMPXCHW)
DEFINE_TRINARY_VIO_OPERATOR_ATOMIC(uvio_operator_cmpxchl, l, uint32_t, UVIO_OPCODE_CMPXCHL)
#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
DEFINE_TRINARY_VIO_OPERATOR_ATOMIC(uvio_operator_cmpxchq, q, uint64_t, UVIO_OPCODE_CMPXCHQ)
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
DEFINE_TRINARY_VIO_OPERATOR_ATOMIC(uvio_operator_cmpxchx, x, uint128_t, UVIO_OPCODE_CMPXCHX)
#endif /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */

DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_xchb, b, uint8_t, UVIO_OPCODE_XCHB)
DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_xchw, w, uint16_t, UVIO_OPCODE_XCHW)
DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_xchl, l, uint32_t, UVIO_OPCODE_XCHL)
#ifdef LIBVIO_CONFIG_HAVE_QWORD
DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_xchq, q, uint64_t, UVIO_OPCODE_XCHQ)
#endif /* LIBVIO_CONFIG_HAVE_QWORD */

DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_addb, b, uint8_t, UVIO_OPCODE_ADDB)
DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_addw, w, uint16_t, UVIO_OPCODE_ADDW)
DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_addl, l, uint32_t, UVIO_OPCODE_ADDL)
#ifdef LIBVIO_CONFIG_HAVE_QWORD
DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_addq, q, uint64_t, UVIO_OPCODE_ADDQ)
#endif /* LIBVIO_CONFIG_HAVE_QWORD */

DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_subb, b, uint8_t, UVIO_OPCODE_SUBB)
DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_subw, w, uint16_t, UVIO_OPCODE_SUBW)
DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_subl, l, uint32_t, UVIO_OPCODE_SUBL)
#ifdef LIBVIO_CONFIG_HAVE_QWORD
DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_subq, q, uint64_t, UVIO_OPCODE_SUBQ)
#endif /* LIBVIO_CONFIG_HAVE_QWORD */

DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_andb, b, uint8_t, UVIO_OPCODE_ANDB)
DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_andw, w, uint16_t, UVIO_OPCODE_ANDW)
DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_andl, l, uint32_t, UVIO_OPCODE_ANDL)
#ifdef LIBVIO_CONFIG_HAVE_QWORD
DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_andq, q, uint64_t, UVIO_OPCODE_ANDQ)
#endif /* LIBVIO_CONFIG_HAVE_QWORD */

DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_orb, b, uint8_t, UVIO_OPCODE_ORB)
DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_orw, w, uint16_t, UVIO_OPCODE_ORW)
DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_orl, l, uint32_t, UVIO_OPCODE_ORL)
#ifdef LIBVIO_CONFIG_HAVE_QWORD
DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_orq, q, uint64_t, UVIO_OPCODE_ORQ)
#endif /* LIBVIO_CONFIG_HAVE_QWORD */

DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_xorb, b, uint8_t, UVIO_OPCODE_XORB)
DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_xorw, w, uint16_t, UVIO_OPCODE_XORW)
DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_xorl, l, uint32_t, UVIO_OPCODE_XORL)
#ifdef LIBVIO_CONFIG_HAVE_QWORD
DEFINE_BINARY_VIO_OPERATOR_ATOMIC(uvio_operator_xorq, q, uint64_t, UVIO_OPCODE_XORQ)
#endif /* LIBVIO_CONFIG_HAVE_QWORD */

#undef DEFINE_UNARY_VIO_OPERATOR
#undef DEFINE_BINARY_VIO_OPERATOR_VOID
#undef DEFINE_BINARY_VIO_OPERATOR_ATOMIC
#undef DEFINE_TRINARY_VIO_OPERATOR_ATOMIC


/* VIO operator callbacks for UVIO mfiles. */
PUBLIC_CONST struct vio_ops const uvio_ops = {
	.vo_read  = VIO_CALLBACK_INIT(&uvio_operator_readb, &uvio_operator_readw, &uvio_operator_readl, &uvio_operator_readq),
	.vo_write = VIO_CALLBACK_INIT(&uvio_operator_writeb, &uvio_operator_writew, &uvio_operator_writel, &uvio_operator_writeq),
	.vo_cmpxch = {
		&uvio_operator_cmpxchb,
		&uvio_operator_cmpxchw,
		&uvio_operator_cmpxchl,
#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
		&uvio_operator_cmpxchq,
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
		&uvio_operator_cmpxchx,
#endif /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */
	},
	.vo_xch = VIO_CALLBACK_INIT(&uvio_operator_xchb, &uvio_operator_xchw, &uvio_operator_xchl, &uvio_operator_xchq),
	.vo_add = VIO_CALLBACK_INIT(&uvio_operator_addb, &uvio_operator_addw, &uvio_operator_addl, &uvio_operator_addq),
	.vo_sub = VIO_CALLBACK_INIT(&uvio_operator_subb, &uvio_operator_subw, &uvio_operator_subl, &uvio_operator_subq),
	.vo_and = VIO_CALLBACK_INIT(&uvio_operator_andb, &uvio_operator_andw, &uvio_operator_andl, &uvio_operator_andq),
	.vo_or  = VIO_CALLBACK_INIT(&uvio_operator_orb, &uvio_operator_orw, &uvio_operator_orl, &uvio_operator_orq),
	.vo_xor = VIO_CALLBACK_INIT(&uvio_operator_xorb, &uvio_operator_xorw, &uvio_operator_xorl, &uvio_operator_xorq),
};






/* Perform a volatile check for requests with the given `status' */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(KCALL uvio_server_has_request_with_status)(struct uvio const *__restrict self,
                                                   u8 status) {
	unsigned int i;
	for (i = 0; i < CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS; ++i) {
		u8 slot_status;
		struct kernel_uvio_request const *slot;
		slot = &self->uv_req[i];
		if (!atomic_read(&slot->kur_args))
			continue; /* Unused slot */

		/* NOTE: The status this following line reads may already be garbage!
		 *       Between the previous line and this one, the request may have
		 *       gotten freed, at which point its `kur_status' field would no
		 *       longer be valid.
		 * However, this case can be  handled as weak undefined behavior,  with
		 * the worst case being that ppoll(2) arbitrarily returns for a request
		 * that has completed in  the mean time, or  has been canceled, all  of
		 * which ppoll(2) is permitted to do! */
		slot_status = atomic_read(&slot->kur_status);
		if (slot_status == status)
			return true; /* Found one! */
	}
	return false;
}


/* Try to read one request into `*req' */
PRIVATE WUNUSED NONNULL((1)) bool KCALL
uvio_server_readone_nonblock(struct uvio *__restrict self,
                             NCX struct uvio_request *req) THROWS(...) {
	unsigned int reqid;
	struct kernel_uvio_request *slot;
	for (reqid = 0; reqid < CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS; ++reqid) {
		slot = &self->uv_req[reqid];
		if (!atomic_read(&slot->kur_args))
			continue; /* Unused slot. */
		if (atomic_read(&slot->kur_status) != KERNEL_UVIO_REQUEST_STATUS_PENDING)
			continue; /* Slot isn't pending. */

		/* This is likely going to be our slot. - Fill in `*req' */
		COMPILER_BARRIER();
		req->uq_addr  = (u64)slot->kur_addr;
		req->uq_cmd   = (u16)slot->kur_cmd;
		req->uq_reqid = (u16)reqid | (slot->kur_uid << 8);
#if SIZEOF_KERNEL_UVIO_UINTMAX_T >= 16
		{
			static_assert(sizeof(union uvio_request_argument) == 16);
			static_assert(sizeof(union kernel_uvio_argument) == 16);
			memcpy(req->uq_args, slot->kur_argv, 2, 16);
		}
#elif SIZEOF_KERNEL_UVIO_UINTMAX_T >= 8
		req->uq_args[0].ura_q = slot->kur_argv[0].kua_q;
		req->uq_args[1].ura_q = slot->kur_argv[1].kua_q;
#elif SIZEOF_KERNEL_UVIO_UINTMAX_T >= 4
		req->uq_args[0].ura_l = slot->kur_argv[0].kua_l;
		req->uq_args[1].ura_l = slot->kur_argv[1].kua_l;
#elif SIZEOF_KERNEL_UVIO_UINTMAX_T >= 2
		req->uq_args[0].ura_w = slot->kur_argv[0].kua_w;
		req->uq_args[1].ura_w = slot->kur_argv[1].kua_w;
#else /* SIZEOF_KERNEL_UVIO_UINTMAX_T >= ... */
		req->uq_args[0].ura_b = slot->kur_argv[0].kua_b;
		req->uq_args[1].ura_b = slot->kur_argv[1].kua_b;
#endif /* SIZEOF_KERNEL_UVIO_UINTMAX_T < ... */
		{
			void *acmap_page;
			vio_addr_t acmap_offset;
			struct vioargs *args;
			pid_t sender_pid;
			COMPILER_READ_BARRIER();
			kernel_uvio_request_read(slot);
			args = atomic_read(&slot->kur_args);
			if unlikely(!args)
				goto badslot;
			acmap_page   = args->va_acmap_page;
			acmap_offset = args->va_acmap_offset;
			sender_pid   = task_getpid_of_s(slot->kur_orig);
			kernel_uvio_request_endread(slot);
			COMPILER_READ_BARRIER();
			req->uq_mapaddr = (u64)(uintptr_t)acmap_page;
			req->uq_mapoffs = (u64)acmap_offset;
			req->uq_pid     = (u32)sender_pid;
		}
		COMPILER_BARRIER();

		/* (Try to) change the status of the slot. */
		kernel_uvio_request_read(slot);
		if unlikely(!atomic_read(&slot->kur_args))
			goto badslot;
		if unlikely(!atomic_cmpxch(&slot->kur_status,
		                           KERNEL_UVIO_REQUEST_STATUS_PENDING,
		                           KERNEL_UVIO_REQUEST_STATUS_DELIVERED)) {
badslot:
			kernel_uvio_request_endread(slot);
			continue;
		}
		kernel_uvio_request_endread(slot);

		/* Status got changed to DELIVERED.
		 * -> This condition must be broadcast via `uv_reqdlvr' */
		sig_broadcast(&self->uv_reqdlvr);
		return true;
	}
	return false;
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
uvio_server_read(struct mfile *__restrict self,
                 NCX void *dst,
                 size_t num_bytes, iomode_t mode) THROWS(...) {
	struct uvio *me = mfile_asuvio(self);
	NCX struct uvio_request *req;
	assert(!task_wasconnected());

	/* Have the caller check for (IO_NONBLOCK), or wait (!IO_NONBLOCK)  until
	 * a UVIO request has become available, at which point the request should
	 * be copied into `dst', and be marked as delivered-but-not-completed  in
	 * the UVIO controller.
	 * s.a. `struct uvio_request' */
	if unlikely(num_bytes < sizeof(struct uvio_request)) {
		/* Buffer too small! */
		THROW(E_BUFFER_TOO_SMALL,
		      sizeof(struct uvio_request),
		      num_bytes);
	}
	req = (NCX struct uvio_request *)dst;
try_readone:
	if (uvio_server_readone_nonblock(me, req))
		return sizeof(struct uvio_request);

	/* TODO: Check for `UVIO_OPCODE_GETUCMD' */

	/* No requests available right now (behavior here depends on IO_NONBLOCK) */
	if (mode & IO_NONBLOCK) {
		if (mode & IO_NODATAZERO)
			return 0;
		THROW(E_WOULDBLOCK_WAITFORSIGNAL);
	}

	/* Wait for data to become available. */
	task_connect(&me->uv_reqmore);
	if (uvio_server_has_request_with_status(me, KERNEL_UVIO_REQUEST_STATUS_PENDING)) {
		task_disconnectall();
		goto try_readone;
	}

	/* Wait for the request. */
	task_waitfor();
	goto try_readone;
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
uvio_server_write(struct mfile *__restrict self,
                  NCX void const *src,
                  size_t num_bytes,
                  iomode_t UNUSED(mode)) THROWS(...) {
	struct uvio *me = mfile_asuvio(self);
	struct uvio_response response_header;
	struct kernel_uvio_request *slot;
	size_t result;

	/* Parse a UVIO response to a previous performed request.
	 * s.a. `struct uvio_response' */
	if unlikely(num_bytes < sizeof(response_header)) {
		/* Buffer too small! */
		THROW(E_BUFFER_TOO_SMALL,
		      sizeof(response_header),
		      num_bytes);
	}

	/* Copy the header into kernel-space */
	memcpy(&response_header, src, sizeof(response_header));
	COMPILER_READ_BARRIER();

	/* No opcode currently makes use of the flags field.
	 * As such, we can simply assert that field to be ZERO for all opcodes! */
	if (response_header.ur_respflags != UVIO_RESPONSE_FLAG_NORMAL) {
		THROW(E_INVALID_ARGUMENT_UNKNOWN_FLAG,
		      E_INVALID_ARGUMENT_CONTEXT_UVIO_BAD_RESPFLAGS,
		      response_header.ur_respflags,
		      UVIO_RESPONSE_FLAG_NORMAL,
		      UVIO_RESPONSE_FLAG_NORMAL);
	}
	switch (response_header.ur_opcode) {
#define VERIFY_SLOT(slot, response_header)                        \
	((slot)->kur_args &&                                          \
	 (slot)->kur_uid == (u8)((response_header).ur_respid >> 8) && \
	 (slot)->kur_opcode == (response_header).ur_opcode)


#if 0
	case UVIO_OPCODE_PUTUCMD:
		/* TODO: Deal with `UVIO_OPCODE_PUTUCMD' */
		break;
#endif

	case UVIO_OPCODE_EXCEPT: {
		struct kernel_uvio_except except;
		NCX struct uvio_response_except *full_response;
		static_assert(sizeof(except_code_t) == sizeof(uintptr_t));
		result = sizeof(struct uvio_response_except);
		if unlikely(num_bytes < result) {
err_buffer_too_small:
			THROW(E_BUFFER_TOO_SMALL,
			      result, num_bytes);
		}
		/* Read exception data. */
		COMPILER_READ_BARRIER();
		full_response = (NCX struct uvio_response_except *)src;
		except.kue_code = (except_code_t)full_response->ur_except_code;
		memcpy(except.kue_pointers, full_response->ur_except_ptrs,
		       EXCEPTION_DATA_POINTERS, sizeof(uintptr_t));
		COMPILER_READ_BARRIER();
#ifdef __ARCH_HAVE_COMPAT
complete_slot_with_except:
#endif /* __ARCH_HAVE_COMPAT */

		/* Verify the response ID */
		slot = &me->uv_req[response_header.ur_respid & 0xff];
		kernel_uvio_request_read(slot);

		/* Ignore responses to requests that may have been aborted. */
		if unlikely(!VERIFY_SLOT(slot, response_header))
			goto unlock_slot_and_ignore;

		/* Fill in the exception to-be re-thrown. */
		memcpy(&slot->kur_except, &except,
		       sizeof(struct kernel_uvio_except));
		atomic_write(&slot->kur_status, KERNEL_UVIO_REQUEST_STATUS_EXCEPT);
		goto complete_slot_nostatus;

#ifdef __ARCH_HAVE_COMPAT
	case UVIO_OPCODE_EXCEPT_COMPAT: {
		unsigned int i;
		NCX struct uvio_response_except_compat *full_response;
		result = sizeof(struct uvio_response_except_compat);
		if unlikely(num_bytes < result)
			goto err_buffer_too_small;
		/* Read exception data. */
		COMPILER_READ_BARRIER();
		full_response = (NCX struct uvio_response_except_compat *)src;
		except.kue_code = (except_code_t)full_response->ur_except_code;
		for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i)
			except.kue_pointers[i] = (uintptr_t)full_response->ur_except_ptrs[i];
		COMPILER_READ_BARRIER();
		goto complete_slot_with_except;
	}	break;
#endif /* __ARCH_HAVE_COMPAT */
	}	break;

		/* extended_data_size == 0 */
	case UVIO_OPCODE_WRITEB:
	case UVIO_OPCODE_WRITEW:
	case UVIO_OPCODE_WRITEL:
#ifdef LIBVIO_CONFIG_HAVE_QWORD
	case UVIO_OPCODE_WRITEQ:
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
		result = sizeof(response_header);
		if unlikely((response_header.ur_respid & 0xff) >= CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS) {
err_bad_respid_lowbyte:
			THROW(E_INDEX_ERROR_OUT_OF_BOUNDS,
			      response_header.ur_respid & 0xff, 0,
			      CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS - 1);
		}

		/* Verify the response ID */
		slot = &me->uv_req[response_header.ur_respid & 0xff];
		kernel_uvio_request_read(slot);

		/* Ignore responses to requests that may have been aborted. */
		if unlikely(!VERIFY_SLOT(slot, response_header)) {
unlock_slot_and_ignore:
			printk(KERN_WARNING "[uvio] Ignore bad/aborted response\n");
			kernel_uvio_request_endread(slot);
			goto done;
		}
complete_slot:
		atomic_write(&slot->kur_status, KERNEL_UVIO_REQUEST_STATUS_COMPLETE);
complete_slot_nostatus:
		kernel_uvio_request_endread(slot);

		/* Signal that a request has been completed. */
		sig_broadcast(&me->uv_reqdone);
		break;

		/* extended_data_size == 1 */
	case UVIO_OPCODE_READB:
	case UVIO_OPCODE_XCHB:
	case UVIO_OPCODE_ADDB:
	case UVIO_OPCODE_SUBB:
	case UVIO_OPCODE_ANDB:
	case UVIO_OPCODE_ORB:
	case UVIO_OPCODE_XORB:
	case UVIO_OPCODE_CMPXCHB: {
		uint8_t retval;
		NCX struct uvio_response_readb *full_response;
		result = sizeof(struct uvio_response_readb);
		if unlikely(num_bytes < result)
			goto err_buffer_too_small;
		if unlikely((response_header.ur_respid & 0xff) >= CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS)
			goto err_bad_respid_lowbyte;

		/* Read in the return value. */
		COMPILER_READ_BARRIER();
		full_response = (NCX struct uvio_response_readb *)src;
		retval        = full_response->ur_result;
		COMPILER_READ_BARRIER();

		/* Verify the response ID */
		slot = &me->uv_req[response_header.ur_respid & 0xff];
		kernel_uvio_request_read(slot);

		/* Ignore responses to requests that may have been aborted. */
		if unlikely(!VERIFY_SLOT(slot, response_header))
			goto unlock_slot_and_ignore;

		/* Fill in the return value. */
		slot->kur_res.kua_b = retval;
		goto complete_slot;
	}

		/* extended_data_size == 2 */
	case UVIO_OPCODE_READW:
	case UVIO_OPCODE_XCHW:
	case UVIO_OPCODE_ADDW:
	case UVIO_OPCODE_SUBW:
	case UVIO_OPCODE_ANDW:
	case UVIO_OPCODE_ORW:
	case UVIO_OPCODE_XORW:
	case UVIO_OPCODE_CMPXCHW: {
		uint16_t retval;
		NCX struct uvio_response_readw *full_response;
		result = sizeof(struct uvio_response_readw);
		if unlikely(num_bytes < result)
			goto err_buffer_too_small;
		if unlikely((response_header.ur_respid & 0xff) >= CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS)
			goto err_bad_respid_lowbyte;

		/* Read in the return value. */
		COMPILER_READ_BARRIER();
		full_response = (NCX struct uvio_response_readw *)src;
		retval        = full_response->ur_result;
		COMPILER_READ_BARRIER();

		/* Verify the response ID */
		slot = &me->uv_req[response_header.ur_respid & 0xff];
		kernel_uvio_request_read(slot);

		/* Ignore responses to requests that may have been aborted. */
		if unlikely(!VERIFY_SLOT(slot, response_header))
			goto unlock_slot_and_ignore;

		/* Fill in the return value. */
		slot->kur_res.kua_w = retval;
		goto complete_slot;
	}

		/* extended_data_size == 4 */
	case UVIO_OPCODE_READL:
	case UVIO_OPCODE_XCHL:
	case UVIO_OPCODE_ADDL:
	case UVIO_OPCODE_SUBL:
	case UVIO_OPCODE_ANDL:
	case UVIO_OPCODE_ORL:
	case UVIO_OPCODE_XORL:
	case UVIO_OPCODE_CMPXCHL: {
		uint32_t retval;
		NCX struct uvio_response_readl *full_response;
		result = sizeof(struct uvio_response_readl);
		if unlikely(num_bytes < result)
			goto err_buffer_too_small;
		if unlikely((response_header.ur_respid & 0xff) >= CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS)
			goto err_bad_respid_lowbyte;

		/* Read in the return value. */
		COMPILER_READ_BARRIER();
		full_response = (NCX struct uvio_response_readl *)src;
		retval        = full_response->ur_result;
		COMPILER_READ_BARRIER();

		/* Verify the response ID */
		slot = &me->uv_req[response_header.ur_respid & 0xff];
		kernel_uvio_request_read(slot);

		/* Ignore responses to requests that may have been aborted. */
		if unlikely(!VERIFY_SLOT(slot, response_header))
			goto unlock_slot_and_ignore;

		/* Fill in the return value. */
		slot->kur_res.kua_l = retval;
		goto complete_slot;
	}

		/* extended_data_size == 8 */
#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
#ifdef LIBVIO_CONFIG_HAVE_QWORD
	case UVIO_OPCODE_READQ:
	case UVIO_OPCODE_XCHQ:
	case UVIO_OPCODE_ADDQ:
	case UVIO_OPCODE_SUBQ:
	case UVIO_OPCODE_ANDQ:
	case UVIO_OPCODE_ORQ:
	case UVIO_OPCODE_XORQ:
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
#ifdef LIBVIO_CONFIG_HAVE_QWORD_CMPXCH
	case UVIO_OPCODE_CMPXCHQ:
#endif /* LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
	{
		uint64_t retval;
		NCX struct uvio_response_readq *full_response;
		result = sizeof(struct uvio_response_readq);
		if unlikely(num_bytes < result)
			goto err_buffer_too_small;
		if unlikely((response_header.ur_respid & 0xff) >= CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS)
			goto err_bad_respid_lowbyte;

		/* Read in the return value. */
		COMPILER_READ_BARRIER();
		full_response = (NCX struct uvio_response_readq *)src;
		retval        = full_response->ur_result;
		COMPILER_READ_BARRIER();

		/* Verify the response ID */
		slot = &me->uv_req[response_header.ur_respid & 0xff];
		kernel_uvio_request_read(slot);

		/* Ignore responses to requests that may have been aborted. */
		if unlikely(!VERIFY_SLOT(slot, response_header))
			goto unlock_slot_and_ignore;

		/* Fill in the return value. */
		slot->kur_res.kua_q = retval;
		goto complete_slot;
	}
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */

		/* extended_data_size == 16 */
#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
	case UVIO_OPCODE_CMPXCHX: {
		uint128_t retval;
		NCX struct uvio_response_readx *full_response;
		result = sizeof(struct uvio_response_readx);
		if unlikely(num_bytes < result)
			goto err_buffer_too_small;
		if unlikely((response_header.ur_respid & 0xff) >= CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS)
			goto err_bad_respid_lowbyte;

		/* Read in the return value. */
		COMPILER_READ_BARRIER();
		full_response = (NCX struct uvio_response_readx *)src;
		retval        = full_response->ur_result;
		COMPILER_READ_BARRIER();

		/* Verify the response ID */
		slot = &me->uv_req[response_header.ur_respid & 0xff];
		kernel_uvio_request_read(slot);

		/* Ignore responses to requests that may have been aborted. */
		if unlikely(!VERIFY_SLOT(slot, response_header))
			goto unlock_slot_and_ignore;

		/* Fill in the return value. */
		slot->kur_res.kua_x = retval;
		goto complete_slot;
	}
#endif /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_UVIO_BAD_OPCODE,
		      response_header.ur_opcode);
		break;
	}
done:
	return result;
}



PRIVATE NONNULL((1)) void KCALL
uvio_server_pollconnect(struct mfile *__restrict self,
                        poll_mode_t what) THROWS(...) {
	struct uvio *me = mfile_asuvio(self);

	/* Poll for pending UVIO requests (read) and delivered-but-not-completed requests (write) */
	if (what & (POLLINMASK | POLLOUTMASK))
		task_connect_for_poll(&me->uv_reqmore);
}

PRIVATE WUNUSED NONNULL((1)) poll_mode_t
NOTHROW(KCALL uvio_server_polltest)(struct mfile *__restrict self,
                                    poll_mode_t what) THROWS(...) {
	struct uvio *me = mfile_asuvio(self);
	poll_mode_t result = 0;

	/* Poll for pending UVIO requests (read) and delivered-but-not-completed requests (write) */
	if ((what & POLLINMASK) && uvio_server_has_request_with_status(me, KERNEL_UVIO_REQUEST_STATUS_PENDING))
		result |= POLLINMASK;
	if ((what & POLLOUTMASK) && uvio_server_has_request_with_status(me, KERNEL_UVIO_REQUEST_STATUS_DELIVERED))
		result |= POLLOUTMASK;
	return result;
}


/* The mfile type used by UVIO objects. */
PRIVATE struct mfile_stream_ops const uvio_v_stream_ops = {
	.mso_read        = &uvio_server_read,
	.mso_write       = &uvio_server_write,
	.mso_pollconnect = &uvio_server_pollconnect,
	.mso_polltest    = &uvio_server_polltest,
};
PUBLIC_CONST struct mfile_ops const uvio_mfile_ops = {
	.mo_stream = &uvio_v_stream_ops,
	.mo_vio    = &uvio_ops,
};

/* Construct a new UVIO object.
 * Note that UVIO is derived from `struct mfile', so the returned
 * object can be stored in  a handle slot as  `HANDLE_TYPE_MFILE' */
PUBLIC REF struct uvio *KCALL uvio_create(void) THROWS(E_BADALLOC) {
	REF struct uvio *result;
	result = (REF struct uvio *)kmalloc(sizeof(struct uvio), GFP_NORMAL);
	_mfile_init(result, &uvio_mfile_ops, PAGESHIFT, PAGESHIFT);
	result->mf_parts = NULL;
	SLIST_INIT(&result->mf_changed);
	result->mf_flags = MFILE_F_NORMAL;
	atomic64_init(&result->mf_filesize, 0);
	result->mf_atime = realtime();
	result->mf_mtime = result->mf_atime;
	result->mf_ctime = result->mf_atime;
	result->mf_btime = result->mf_atime;
	sig_init(&result->uv_reqmore);
	sig_init(&result->uv_reqdlvr);
	sig_init(&result->uv_reqdone);
	sig_init(&result->uv_reqfree);
	{
		unsigned int reqid;
		for (reqid = 0; reqid < CONFIG_KERNEL_UVIO_MAX_PARALLEL_REQUESTS; ++reqid) {
			atomic_rwlock_init(&result->uv_req[reqid].kur_lock);
			result->uv_req[reqid].kur_nextuid_seed = krand32();
			result->uv_req[reqid].kur_args         = NULL; /* Free slot */
			DBG_memset(&result->uv_req[reqid].kur_orig, 0xcc,
			           sizeof(struct kernel_uvio_request) -
			           offsetof(struct kernel_uvio_request, kur_orig));
		}
	}
	return result;
}



/************************************************************************/
/* sys_userviofd(2)                                                     */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_USERVIOFD
DEFINE_SYSCALL2(fd_t, userviofd,
                size_t, initial_size,
                syscall_ulong_t, flags) {
	fd_t resfd;
	iomode_t mode;
	REF struct uvio *vio;
	struct handle_install_data install;
	VALIDATE_FLAGSET(flags, O_NONBLOCK | O_CLOEXEC | O_CLOFORK,
	                 E_INVALID_ARGUMENT_CONTEXT_USERVIOFD_FLAGS);

	/* Allocate a new handle. */
	resfd = handles_install_begin(&install);

	/* Construct the UVIO object. */
	TRY {
		vio = uvio_create();
	} EXCEPT {
		handles_install_rollback(&install);
		RETHROW();
	}
	atomic64_init(&vio->mf_filesize, initial_size);

	/* Need to be able to read & write to implement the server/client
	 * architecture that  is  used  to  drive  the  UVIO  sub-system. */
	mode = IO_RDWR | IO_FROM_OPENFLAG(flags);
	handles_install_commit_inherit(&install, vio, mode);
	return (fd_t)resfd;
}
#endif /* __ARCH_WANT_SYSCALL_USERVIOFD */



DECL_END
#endif /* LIBVIO_CONFIG_ENABLED */

#endif /* !GUARD_KERNEL_SRC_MEMORY_UVIO_C */
