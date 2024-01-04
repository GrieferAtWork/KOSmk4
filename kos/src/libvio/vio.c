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
#ifndef GUARD_LIBVIO_VIO_C
#define GUARD_LIBVIO_VIO_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1

#include "api.h"
/**/

#ifdef LIBVIO_CONFIG_ENABLED
#ifndef __KERNEL__
#include <hybrid/byteorder.h>
#include <hybrid/sched/atomic-rwlock.h>

#include <kos/anno.h>
#include <kos/except.h>
#include <kos/kernel/types.h>
#include <kos/syscalls.h>
#include <kos/types.h>
#include <sys/poll.h>

#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

#include <libvio/userviofd.h>

#include "access.h"
#include "vio.h"

DECL_BEGIN

struct uvio_service_startup_args {
	fd_t                  ssa_fd;     /* UVIO fd */
	struct vio_ops const *ssa_ops;    /* [1..1] UVIO callbacks */
	void                 *ssa_cookie; /* [?..?] UVIO callback cookie */
};

union qword {
	u64 q;
	u32 l[2];
};

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define LSW 0 /* LeastSignificantWord */
#define MSW 1 /* MosttSignificantWord */
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define LSW 1 /* LeastSignificantWord */
#define MSW 0 /* MosttSignificantWord */
#endif /* __BYTE_ORDER__ == ... */


/* TODO: vioargs_getstate()
 * -> implement  through  use of  custom  ioctl() operations
 *    that can be used to get/set the CPU state of a waiting
 *    thread by use of UVIO request ids `req.uq_reqid' */

PRIVATE void *uvio_service_thread(void *cookie) {
	fd_t fd;
	struct vioargs args;
	{
		struct uvio_service_startup_args *ptr;
		ptr = (struct uvio_service_startup_args *)cookie;
		fd             = ptr->ssa_fd;
		args.va_ops    = ptr->ssa_ops;
		args.va_cookie = ptr->ssa_cookie;
		free(ptr);
	}
	for (;;) {
		struct uvio_request req;
		union {
			struct uvio_response r;
			struct uvio_response_readb rb;
			struct uvio_response_readw rw;
			struct uvio_response_readl rl;
			struct uvio_response_readq rq;
			struct uvio_response_readx r128;
			struct uvio_response_except rx;
		} resp;
		size_t resp_size;

		/* Read in a request. */
		if (sys_read(fd, &req, sizeof(req)) != sizeof(req))
			break; /* Shouldn't happen... */

		/* Dispatch the request. */
		TRY {
			resp.r.ur_opcode     = req.uq_opcode;
			resp.r.ur_respflags  = UVIO_RESPONSE_FLAG_NORMAL;
			resp.r.ur_respid     = req.uq_reqid;
			args.va_acmap_page   = (void *)req.uq_mapaddr;
			args.va_acmap_offset = (vio_addr_t)req.uq_mapoffs;
			switch (req.uq_opcode) {
#define FORCE_ATOMIC() ((req.uq_reqflags & UVIO_REQUEST_FLAG_ATOMIC) != 0)

			case UVIO_OPCODE_READB:
				resp.rb.ur_result = libvio_readb(&args, req.uq_addr);
				resp_size = sizeof(resp.rb);
				break;

			case UVIO_OPCODE_READW:
				resp.rw.ur_result = libvio_readw(&args, req.uq_addr);
				resp_size = sizeof(resp.rw);
				break;

			case UVIO_OPCODE_READL:
				resp.rl.ur_result = libvio_readl(&args, req.uq_addr);
				resp_size = sizeof(resp.rl);
				break;

			case UVIO_OPCODE_READQ:
#ifdef LIBVIO_CONFIG_HAVE_QWORD
				resp.rq.ur_result = libvio_readq(&args, req.uq_addr);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
				resp.rq.ur_lresult[0] = libvio_readl(&args, req.uq_addr);
				resp.rq.ur_lresult[1] = libvio_readl(&args, req.uq_addr + 4);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
				resp_size = sizeof(resp.rq);
				break;

			case UVIO_OPCODE_WRITEB:
				libvio_writeb(&args, req.uq_addr, req.uq_args[0].ura_b);
				resp_size = sizeof(resp.r);
				break;

			case UVIO_OPCODE_WRITEW:
				libvio_writew(&args, req.uq_addr, req.uq_args[0].ura_w);
				resp_size = sizeof(resp.r);
				break;

			case UVIO_OPCODE_WRITEL:
				libvio_writel(&args, req.uq_addr, req.uq_args[0].ura_l);
				resp_size = sizeof(resp.r);
				break;

			case UVIO_OPCODE_WRITEQ:
#ifdef LIBVIO_CONFIG_HAVE_QWORD
				libvio_writeq(&args, req.uq_addr, req.uq_args[0].ura_q);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
				libvio_writel(&args, req.uq_addr + 0, req.uq_args[0].ura_q_as_l[0]);
				libvio_writel(&args, req.uq_addr + 4, req.uq_args[0].ura_q_as_l[1]);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
				resp_size = sizeof(resp.r);
				break;

			case UVIO_OPCODE_XCHB:
				resp.rb.ur_result = libvio_xchb(&args, req.uq_addr,
				                                req.uq_args[0].ura_b,
				                                FORCE_ATOMIC());
				resp_size = sizeof(resp.rb);
				break;

			case UVIO_OPCODE_XCHW:
				resp.rw.ur_result = libvio_xchw(&args, req.uq_addr,
				                                req.uq_args[0].ura_w,
				                                FORCE_ATOMIC());
				resp_size = sizeof(resp.rw);
				break;

			case UVIO_OPCODE_XCHL:
				resp.rl.ur_result = libvio_xchl(&args, req.uq_addr,
				                                req.uq_args[0].ura_l,
				                                FORCE_ATOMIC());
				resp_size = sizeof(resp.rl);
				break;

			case UVIO_OPCODE_XCHQ: {
#ifdef LIBVIO_CONFIG_HAVE_QWORD
				resp.rq.ur_result = libvio_xchq(&args, req.uq_addr,
				                                req.uq_args[0].ura_q,
				                                FORCE_ATOMIC());
#elif defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
				union qword q;
				for (;;) {
					q.l[0] = libvio_readl(&args, req.uq_addr + 0);
					q.l[1] = libvio_readl(&args, req.uq_addr + 4);
					if (libvio_cmpxchq(&args, req.uq_addr, q.q,
					                   req.uq_args[0].ura_q,
					                   FORCE_ATOMIC()))
						break;
					pthread_yield();
				}
				resp.rq.ur_lresult[0] = q.l[0];
				resp.rq.ur_lresult[1] = q.l[1];
#else /* ... */
				if (FORCE_ATOMIC()) {
					THROW(E_SEGFAULT_NOTATOMIC,
					      vioargs_faultaddr(&args, req.uq_addr),
					      0,
					      8,
					      libvio_readl(&args, req.uq_addr + 4 * LSW),
					      libvio_readl(&args, req.uq_addr + 4 * MSW),
					      req.uq_args[0].ura_q_as_l[LSW],
					      req.uq_args[0].ura_q_as_l[MSW]);
				}
				resp.rq.ur_lresult[0] = libvio_xchl(&args, req.uq_addr + 0, req.uq_args[0].ura_q_as_l[0], false);
				resp.rq.ur_lresult[1] = libvio_xchl(&args, req.uq_addr + 4, req.uq_args[0].ura_q_as_l[1], false);
#endif /* !... */
				resp_size = sizeof(resp.rq);
			}	break;

#define DEFINE_UVIO_OPERATION_BWL(add, ADD)                               \
			case UVIO_OPCODE_##ADD##B:                                    \
				resp.rb.ur_result = libvio_##add##b(&args, req.uq_addr,   \
				                                    req.uq_args[0].ura_b, \
				                                    FORCE_ATOMIC());      \
				resp_size = sizeof(resp.rb);                              \
				break;                                                    \
			                                                              \
			case UVIO_OPCODE_##ADD##W:                                    \
				resp.rw.ur_result = libvio_##add##w(&args, req.uq_addr,   \
				                                    req.uq_args[0].ura_w, \
				                                    FORCE_ATOMIC());      \
				resp_size = sizeof(resp.rw);                              \
				break;                                                    \
			                                                              \
			case UVIO_OPCODE_##ADD##L:                                    \
				resp.rl.ur_result = libvio_##add##l(&args, req.uq_addr,   \
				                                    req.uq_args[0].ura_l, \
				                                    FORCE_ATOMIC());      \
				resp_size = sizeof(resp.rl);                              \
				break;

#ifdef LIBVIO_CONFIG_HAVE_QWORD
#define DEFINE_UVIO_OPERATION_Q(add, ADD, op)                             \
			case UVIO_OPCODE_##ADD##Q:                                    \
				resp.rq.ur_result = libvio_##add##q(&args, req.uq_addr,   \
				                                    req.uq_args[0].ura_q, \
				                                    FORCE_ATOMIC());      \
				resp_size = sizeof(resp.rq);                              \
				break;
#elif defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
#define DEFINE_UVIO_OPERATION_Q(add, ADD, op)                       \
			case UVIO_OPCODE_##ADD##Q: {                            \
				union qword q;                                      \
				for (;;) {                                          \
					q.l[0] = libvio_readl(&args, req.uq_addr + 0);  \
					q.l[1] = libvio_readl(&args, req.uq_addr + 4);  \
					if (libvio_cmpxchq(&args, req.uq_addr, q.q,     \
					                   q.q op req.uq_args[0].ura_q, \
					                   FORCE_ATOMIC()))             \
						break;                                      \
					pthread_yield();                                \
				}                                                   \
				resp.rq.ur_lresult[0] = q.l[0];                     \
				resp.rq.ur_lresult[1] = q.l[1];                     \
				resp_size = sizeof(resp.rq);                        \
			}	break;
#else /* LIBVIO_CONFIG_HAVE_QWORD */
#define DEFINE_UVIO_OPERATION_Q(add, ADD, op)                       \
			case UVIO_OPCODE_##ADD##Q: {                            \
				union qword oldval, newval;                         \
				oldval.l[0] = libvio_readl(&args, req.uq_addr + 0); \
				oldval.l[1] = libvio_readl(&args, req.uq_addr + 4); \
				newval.q    = oldval.q op req.uq_args[0].ura_q;     \
				if (FORCE_ATOMIC()) {                               \
					THROW(E_SEGFAULT_NOTATOMIC,                     \
					      vioargs_faultaddr(&args, req.uq_addr),    \
					      0,                                        \
					      8,                                        \
					      oldval.l[0 + LSW],                        \
					      oldval.l[0 + MSW],                        \
					      newval.l[2 + LSW],                        \
					      newval.l[2 + MSW]);                       \
				}                                                   \
				libvio_writel(&args, req.uq_addr + 0, newval.l[0]); \
				libvio_writel(&args, req.uq_addr + 4, newval.l[1]); \
				resp_size = sizeof(resp.rq);                        \
			}	break;
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
#define DEFINE_UVIO_OPERATION(add, ADD, op) \
	DEFINE_UVIO_OPERATION_BWL(add, ADD)     \
	DEFINE_UVIO_OPERATION_Q(add, ADD, +)
			DEFINE_UVIO_OPERATION(add, ADD, +)
			DEFINE_UVIO_OPERATION(sub, SUB, -)
			DEFINE_UVIO_OPERATION(and, AND, &)
			DEFINE_UVIO_OPERATION(or, OR, |)
			DEFINE_UVIO_OPERATION(xor, XOR, ^)
#undef DEFINE_UVIO_OPERATION_BWL
#undef DEFINE_UVIO_OPERATION_Q
#undef DEFINE_UVIO_OPERATION

			case UVIO_OPCODE_CMPXCHB: {
				resp.rb.ur_result = libvio_cmpxchb(&args, req.uq_addr,
				                                   req.uq_args[0].ura_b,
				                                   req.uq_args[1].ura_b,
				                                   FORCE_ATOMIC());
				resp_size = sizeof(resp.rb);
			}	break;

			case UVIO_OPCODE_CMPXCHW: {
				resp.rw.ur_result = libvio_cmpxchw(&args, req.uq_addr,
				                                   req.uq_args[0].ura_w,
				                                   req.uq_args[1].ura_w,
				                                   FORCE_ATOMIC());
				resp_size = sizeof(resp.rw);
			}	break;

			case UVIO_OPCODE_CMPXCHL: {
				resp.rl.ur_result = libvio_cmpxchl(&args, req.uq_addr,
				                                   req.uq_args[0].ura_l,
				                                   req.uq_args[1].ura_l,
				                                   FORCE_ATOMIC());
				resp_size = sizeof(resp.rl);
			}	break;

			case UVIO_OPCODE_CMPXCHQ: {
#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
				resp.rq.ur_result = libvio_cmpxchq(&args, req.uq_addr,
				                                   req.uq_args[0].ura_q,
				                                   req.uq_args[1].ura_q,
				                                   FORCE_ATOMIC());
				resp_size = sizeof(resp.rq);
#else /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
#endif /* !LIBVIO_CONFIG_HAVE_QWORD && !LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
				if (FORCE_ATOMIC()) {
					THROW(E_SEGFAULT_NOTATOMIC,
					      vioargs_faultaddr(&args, req.uq_addr),
					      0,
					      8,
					      (uintptr_t)req.uq_args[0].ura_q_as_l[LSW],
					      (uintptr_t)req.uq_args[0].ura_q_as_l[MSW],
					      (uintptr_t)req.uq_args[1].ura_q_as_l[LSW],
					      (uintptr_t)req.uq_args[1].ura_q_as_l[MSW]);
				}
			}	break;

			case UVIO_OPCODE_CMPXCHX: {
#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
				resp.r128.ur_result = libvio_cmpxchx(&args, req.uq_addr,
				                                     req.uq_args[0].ura_x,
				                                     req.uq_args[1].ura_x,
				                                     FORCE_ATOMIC());
#else /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */
				if (FORCE_ATOMIC()) {
					THROW(E_SEGFAULT_NOTATOMIC,
					      vioargs_faultaddr(&args, req.uq_addr),
					      0,
					      16,
					      (uintptr_t)req.uq_args[0].ura_x_as_q[LSW],
					      (uintptr_t)req.uq_args[0].ura_x_as_q[MSW],
					      (uintptr_t)req.uq_args[1].ura_x_as_q[LSW],
					      (uintptr_t)req.uq_args[1].ura_x_as_q[MSW]);
				}
#ifdef LIBVIO_CONFIG_HAVE_QWORD
				resp.r128.ur_qresult[0] = libvio_readq(&args, req.uq_addr + 0);
				resp.r128.ur_qresult[1] = libvio_readq(&args, req.uq_addr + 8);
				if (resp.r128.ur_qresult[0] == req.uq_args[0].ura_x_as_q[0] &&
				    resp.r128.ur_qresult[1] == req.uq_args[0].ura_x_as_q[1]) {
					libvio_writeq(&args, req.uq_addr + 0, req.uq_args[1].ura_x_as_q[0]);
					libvio_writeq(&args, req.uq_addr + 8, req.uq_args[1].ura_x_as_q[0]);
				}
#else /* LIBVIO_CONFIG_HAVE_QWORD */
				resp.r128.ur_lresult[0] = libvio_readl(&args, req.uq_addr + 0x0);
				resp.r128.ur_lresult[1] = libvio_readl(&args, req.uq_addr + 0x4);
				resp.r128.ur_lresult[2] = libvio_readl(&args, req.uq_addr + 0x8);
				resp.r128.ur_lresult[3] = libvio_readl(&args, req.uq_addr + 0xc);
				if (resp.r128.ur_lresult[0] == req.uq_args[0].ura_x_as_l[0] &&
				    resp.r128.ur_lresult[1] == req.uq_args[0].ura_x_as_l[1] &&
				    resp.r128.ur_lresult[2] == req.uq_args[0].ura_x_as_l[2] &&
				    resp.r128.ur_lresult[3] == req.uq_args[0].ura_x_as_l[3]) {
					libvio_writel(&args, req.uq_addr + 0x0, req.uq_args[1].ura_x_as_l[0]);
					libvio_writel(&args, req.uq_addr + 0x4, req.uq_args[1].ura_x_as_l[1]);
					libvio_writel(&args, req.uq_addr + 0x8, req.uq_args[1].ura_x_as_l[2]);
					libvio_writel(&args, req.uq_addr + 0xc, req.uq_args[1].ura_x_as_l[3]);
				}
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
#endif /* !LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */
				resp_size = sizeof(resp.r128);
			}	break;

			case UVIO_OPCODE_GETUCMD:
				/* User command */
				if (req.uq_reqid == UVIO_OPCODE_UCMD_STOP &&
				    (pid_t)req.uq_pid == getpid())
					goto done; /* Calling process sent us a stop command */
				resp_size = sizeof(resp.r); /* ??? */
				break;

#undef FORCE_ATOMIC
			default: {
				/* Unknown request (shouldn't happen...)
				 * Respond  with   an   empty   response */
				resp_size = sizeof(resp.r);
			}	break;

			}
		} EXCEPT {
			unsigned int i;
			struct exception_data *data;
			except_class_t cls = except_class();

			/* Always propagate RTL-priority exceptions. */
			if (EXCEPTCLASS_ISRTLPRIORITY(cls)) {
				(void)sys_close(fd);
				RETHROW();
			}

			/* Respond with an exception */
			data                   = except_data();
			resp.rx.ur_opcode      = UVIO_OPCODE_EXCEPT;
			resp.rx.ur_except_code = data->e_code;
			for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i)
				resp.rx.ur_except_ptrs[i] = data->e_args.e_pointers[i];
			resp_size = sizeof(resp.rx);
		}
		sys_write(fd, &resp, resp_size);
	}
done:
	(void)sys_close(fd);
	return NULL;
}

/* Start a uservio FD service thread
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
PRIVATE int CC
spawn_uvio_service_thread(fd_t fd,
                          struct vio_ops const *ops,
                          void *cookie) {
	int error;
	pthread_t thread;
	struct uvio_service_startup_args *args;
	args = (struct uvio_service_startup_args *)malloc(sizeof(struct uvio_service_startup_args));
	if unlikely(!args)
		goto err;
	args->ssa_fd     = fd;
	args->ssa_ops    = ops;
	args->ssa_cookie = cookie;
	error = pthread_create(&thread, NULL,
	                       &uvio_service_thread,
	                       args /* inherit */);
	if (error != EOK)
		goto err_args;

	/* Let the thread do its thing... */
	pthread_detach(thread);
	return 0;
err_args:
	free(args);
	errno = error;
err:
	return -1;
}





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
INTERN WUNUSED NONNULL((1)) fd_t
NOTHROW_NCX(CC libvio_create)(struct vio_ops const *ops, void *cookie,
                              size_t initial_size, oflag_t flags) {
	fd_t result;

	/* Validate the given `flags'
	 * NOTE: The kernel accepts more flags than this, but we don't! */
	if unlikely(flags & ~(O_CLOEXEC | O_CLOFORK)) {
		errno = EINVAL;
		goto err;
	}

	/* Construct the user-vio FD */
	result = sys_userviofd(initial_size, flags);
	if unlikely(E_ISERR(result)) {
		errno = -result;
		goto err;
	}
	if unlikely(spawn_uvio_service_thread(result,
	                                      ops,
	                                      cookie) != 0) {
		sys_close(result);
		goto err;
	}
	return result;
err:
	return -1;
}


/* vio_destroy(3):
 * >> int vio_destroy(fd_t fd);
 * Destroy a VIO file descriptor previously created by `vio_create(3)' */
INTDEF ATTR_FDARG(1) int
NOTHROW(CC libvio_destroy)(fd_t fd) {
	struct uvio_response resp;
	resp.ur_opcode    = UVIO_OPCODE_PUTUCMD;
	resp.ur_respflags = UVIO_RESPONSE_FLAG_NORMAL;
	resp.ur_respid    = UVIO_OPCODE_UCMD_STOP;
	return sys_write(fd, &resp, sizeof(resp)) >= 0;
}


DEFINE_PUBLIC_ALIAS(vio_create, libvio_create);
DEFINE_PUBLIC_ALIAS(vio_destroy, libvio_destroy);

DECL_END

#endif /* !__KERNEL__ */
#endif /* LIBVIO_CONFIG_ENABLED */


#endif /* !GUARD_LIBVIO_VIO_C */
