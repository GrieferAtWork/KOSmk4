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
#ifndef GUARD_LIBVIO_VIO_C
#define GUARD_LIBVIO_VIO_C 1
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1

#include "vio.h"

#ifdef LIBVIO_CONFIG_ENABLED
#ifndef __KERNEL__

#include <hybrid/atomic.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <kos/anno.h>
#include <kos/except.h>
#include <kos/syscalls.h>
#include <sys/poll.h>

#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <pthread.h>
#include <stddef.h>
#include <unistd.h>

#include <libvio/userviofd.h>

#include "access.h"

DECL_BEGIN

struct uvio_service_startup_args {
	fd_t                        ssa_fd;     /* UVIO fd */
	struct vio_operators const *ssa_ops;    /* [1..1] UVIO callbacks */
	void                       *ssa_cookie; /* [?..?] UVIO callback cookie */
};

/* TODO: vio_args_getstate()  (implement through use of custom hop() operations that
 *                             can be used to get/set the CPU state of a waiting
 *                             thread by use of UVIO request ids `req.uq_reqid') */

PRIVATE void *uvio_service_thread(void *cookie) {
	fd_t fd;
	struct vio_args args;
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
			struct uvio_response_read128 r128;
			struct uvio_response_except rx;
		} resp;
		size_t resp_size;
		/* Read in a request. */
		if (sys_read(fd, &req, sizeof(req)) != sizeof(req))
			break; /* Shouldn't happen... */
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
				libvio_writeb(&args, req.uq_addr, req.uq_bdata[0]);
				resp_size = sizeof(resp.r);
				break;
	
			case UVIO_OPCODE_WRITEW:
				libvio_writew(&args, req.uq_addr, req.uq_wdata[0]);
				resp_size = sizeof(resp.r);
				break;
	
			case UVIO_OPCODE_WRITEL:
				libvio_writel(&args, req.uq_addr, req.uq_ldata[0]);
				resp_size = sizeof(resp.r);
				break;
	
			case UVIO_OPCODE_WRITEQ:
#ifdef LIBVIO_CONFIG_HAVE_QWORD
				libvio_writeq(&args, req.uq_addr, req.uq_qdata[0]);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
				libvio_writel(&args, req.uq_addr + 0, req.uq_ldata[0]);
				libvio_writel(&args, req.uq_addr + 4, req.uq_ldata[1]);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
				resp_size = sizeof(resp.r);
				break;

#define UVIO_OPCODE_XCHB      0x18 /* req(value:uq_bdata[0])   resp(oldval:uvio_response_readb) */
#define UVIO_OPCODE_XCHW      0x19 /* req(value:uq_wdata[0])   resp(oldval:uvio_response_readw) */
#define UVIO_OPCODE_XCHL      0x1a /* req(value:uq_ldata[0])   resp(oldval:uvio_response_readl) */
#define UVIO_OPCODE_XCHQ      0x1b /* req(value:uq_qdata[0])   resp(oldval:uvio_response_readq) */
#define UVIO_OPCODE_ADDB      0x1c /* req(value:uq_bdata[0])   resp(oldval:uvio_response_readb) */
#define UVIO_OPCODE_ADDW      0x1d /* req(value:uq_wdata[0])   resp(oldval:uvio_response_readw) */
#define UVIO_OPCODE_ADDL      0x1e /* req(value:uq_ldata[0])   resp(oldval:uvio_response_readl) */
#define UVIO_OPCODE_ADDQ      0x1f /* req(value:uq_qdata[0])   resp(oldval:uvio_response_readq) */
#define UVIO_OPCODE_SUBB      0x20 /* req(value:uq_bdata[0])   resp(oldval:uvio_response_readb) */
#define UVIO_OPCODE_SUBW      0x21 /* req(value:uq_wdata[0])   resp(oldval:uvio_response_readw) */
#define UVIO_OPCODE_SUBL      0x22 /* req(value:uq_ldata[0])   resp(oldval:uvio_response_readl) */
#define UVIO_OPCODE_SUBQ      0x23 /* req(value:uq_qdata[0])   resp(oldval:uvio_response_readq) */
#define UVIO_OPCODE_ANDB      0x24 /* req(value:uq_bdata[0])   resp(oldval:uvio_response_readb) */
#define UVIO_OPCODE_ANDW      0x25 /* req(value:uq_wdata[0])   resp(oldval:uvio_response_readw) */
#define UVIO_OPCODE_ANDL      0x26 /* req(value:uq_ldata[0])   resp(oldval:uvio_response_readl) */
#define UVIO_OPCODE_ANDQ      0x27 /* req(value:uq_qdata[0])   resp(oldval:uvio_response_readq) */
#define UVIO_OPCODE_ORB       0x28 /* req(value:uq_bdata[0])   resp(oldval:uvio_response_readb) */
#define UVIO_OPCODE_ORW       0x29 /* req(value:uq_wdata[0])   resp(oldval:uvio_response_readw) */
#define UVIO_OPCODE_ORL       0x2a /* req(value:uq_ldata[0])   resp(oldval:uvio_response_readl) */
#define UVIO_OPCODE_ORQ       0x2b /* req(value:uq_qdata[0])   resp(oldval:uvio_response_readq) */
#define UVIO_OPCODE_XORB      0x2c /* req(value:uq_bdata[0])   resp(oldval:uvio_response_readb) */
#define UVIO_OPCODE_XORW      0x2d /* req(value:uq_wdata[0])   resp(oldval:uvio_response_readw) */
#define UVIO_OPCODE_XORL      0x2e /* req(value:uq_ldata[0])   resp(oldval:uvio_response_readl) */
#define UVIO_OPCODE_XORQ      0x2f /* req(value:uq_qdata[0])   resp(oldval:uvio_response_readq) */
#define UVIO_OPCODE_CMPXCHB   0x30 /* req(oldval:uq_bdata[0], newval:uq_bdata[16])    resp(real_oldval:uvio_response_readb) */
#define UVIO_OPCODE_CMPXCHW   0x31 /* req(oldval:uq_wdata[0], newval:uq_wdata[8])     resp(real_oldval:uvio_response_readw) */
#define UVIO_OPCODE_CMPXCHL   0x32 /* req(oldval:uq_ldata[0], newval:uq_ldata[4])     resp(real_oldval:uvio_response_readl) */
#define UVIO_OPCODE_CMPXCHQ   0x33 /* req(oldval:uq_qdata[0], newval:uq_qdata[2])     resp(real_oldval:uvio_response_readq) */

			case UVIO_OPCODE_CMPXCH128:
#ifdef LIBVIO_CONFIG_HAVE_INT128_CMPXCH
				resp.r128.ur_result = libvio_cmpxch128(&args, req.uq_addr,
				                                       req.uq_data128[0],
				                                       req.uq_data128[1],
				                                       FORCE_ATOMIC());
#else /* LIBVIO_CONFIG_HAVE_INT128_CMPXCH */
				if (FORCE_ATOMIC()) {
					THROW(E_SEGFAULT_NOTATOMIC,
					      vio_args_faultaddr(&args, req.uq_addr),
					      E_SEGFAULT_CONTEXT_WRITING,
					      16,
					      (uintptr_t)req.uq_qdata[0],
					      (uintptr_t)req.uq_qdata[1],
					      (uintptr_t)req.uq_qdata[2],
					      (uintptr_t)req.uq_qdata[3]);
				}
#ifdef LIBVIO_CONFIG_HAVE_QWORD
				resp.r128.ur_qresult[0] = libvio_readq(&args, req.uq_addr + 0);
				resp.r128.ur_qresult[1] = libvio_readq(&args, req.uq_addr + 8);
				if (resp.r128.ur_qresult[0] == req.uq_qdata[0] &&
				    resp.r128.ur_qresult[1] == req.uq_qdata[1]) {
					libvio_writeq(&args, req.uq_addr + 0, req.uq_qdata[2]);
					libvio_writeq(&args, req.uq_addr + 8, req.uq_qdata[3]);
				}
#else /* LIBVIO_CONFIG_HAVE_QWORD */
				resp.r128.ur_lresult[0] = libvio_readl(&args, req.uq_addr + 0x0);
				resp.r128.ur_lresult[1] = libvio_readl(&args, req.uq_addr + 0x4);
				resp.r128.ur_lresult[2] = libvio_readl(&args, req.uq_addr + 0x8);
				resp.r128.ur_lresult[3] = libvio_readl(&args, req.uq_addr + 0xc);
				if (resp.r128.ur_lresult[0] == req.uq_ldata[0] &&
				    resp.r128.ur_lresult[1] == req.uq_ldata[1] &&
				    resp.r128.ur_lresult[2] == req.uq_ldata[2] &&
				    resp.r128.ur_lresult[3] == req.uq_ldata[3]) {
					libvio_writel(&args, req.uq_addr + 0x0, req.uq_ldata[4]);
					libvio_writel(&args, req.uq_addr + 0x4, req.uq_ldata[5]);
					libvio_writel(&args, req.uq_addr + 0x8, req.uq_ldata[6]);
					libvio_writel(&args, req.uq_addr + 0xc, req.uq_ldata[7]);
				}
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
#endif /* !LIBVIO_CONFIG_HAVE_INT128_CMPXCH */
				resp_size = sizeof(resp.r128);
				break;

			case UVIO_OPCODE_GETUCMD:
				/* User command */
				if (req.uq_reqid == UVIO_OPCODE_UCMD_STOP &&
				    (pid_t)req.uq_pid == getpid())
					goto done; /* Calling process sent us a stop command */
				break;

#undef FORCE_ATOMIC
			default: {
				/* Unknown request (shouldn't happen...)
				 * Respond with an empty response */
				resp_size = sizeof(resp.r);
			}	break;
			}
		} EXCEPT {
			unsigned int i;
			struct exception_data *data;
			/* Respond with an exception */
			data                   = error_data();
			resp.rx.ur_opcode      = UVIO_OPCODE_EXCEPT;
			resp.rx.ur_except_code = data->e_code;
			for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i)
				resp.rx.ur_except_ptrs[i] = data->e_pointers[i];
			resp_size = sizeof(resp.rx);
		}
		sys_write(fd, &resp, resp_size);
	}
done:
	sys_close(fd);
	return NULL;
}

/* Start a uservio FD service thread
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
PRIVATE int CC
spawn_uvio_service_thread(fd_t fd,
                          struct vio_operators const *ops,
                          void *cookie) {
	int error;
	pthread_t thread;
	struct uvio_service_startup_args *args;
	args = (struct uvio_service_startup_args *)malloc(sizeof(struct uvio_service_startup_args));
	if unlikely(!args)
		goto err0;
	args->ssa_fd     = fd;
	args->ssa_ops    = ops;
	args->ssa_cookie = cookie;
	error = pthread_create(&thread, NULL,
	                       &uvio_service_thread,
	                       args /* inherit */);
	if (error != EOK)
		goto err_args;
	pthread_detach(thread);
	return 0;
err_args:
	free(args);
	errno = error;
err0:
	return -1;
}





/* vio_create(3):
 * >> fd_t vio_create(struct vio_operators *ops, void *cookie,
 * >>                 size_t initial_size, oflag_t flags);
 * Create an mmap(2)able VIO object where memory accesses
 * made to the object are serviced by dispatching them via
 * the given `ops' table.
 * The returned file descriptor mustn't be deleted by `close(2)',
 * but rather through use of `vio_destroy(3)'.
 * Note that callbacks in `ops' may be invoked in the context
 * of a different thread than the one that performed the memory
 * access. Also note that the returned `fd_t' can be shared with
 * other processes, but still function as expected. (when shared
 * with a different process, that process should once again make
 * use of `close(2)' for cleanup, rather than `vio_destroy(3)')
 * @param: flags:        Set of `0 | O_CLOEXEC | O_CLOFORK'
 * @param: cookie:       A cookie pointer that is available as `args->va_cookie'
 * @param: initial_size: The initial mmap(2)able size of the returned handle.
 *                       This size may be altered at a later point in time
 *                       through use of `ftruncate(return)' */
INTERN WUNUSED NONNULL((1)) fd_t
NOTHROW_NCX(CC libvio_create)(struct vio_operators const *ops, void *cookie,
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
INTDEF int
NOTHROW_NCX(CC libvio_destroy)(fd_t fd) {
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
