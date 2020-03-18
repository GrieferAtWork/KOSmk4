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
#ifndef _LIBVIOCORE_VIOCORE_H
#define _LIBVIOCORE_VIOCORE_H 1

#include "api.h"
#include <libvio/vio.h>


/* TODO: libviocore
 * -> Move all of the VIO logic into a dedicated library that can also be loaded from user-space.
 *    The idea here is to have the library export a function:
 * >> struct vio_descriptor {
 * >>     struct vio_operators *vd_ops;  // [1..1] VIO callback dispatch table                        (`fd' argument of `mmap()')
 * >>     void                 *vd_base; // Base address of the associated VIO segment (< :faultaddr) (return value of `mmap()')
 * >>     pos_t                 vd_voff; // Starting offset of the VIO mapping at `vd_base'           (`offset' argument of `mmap()')
 * >> };
 * >> #ifdef __KERNEL__
 * >> typedef struct icpustate vio_cpustate_t;
 * >> #else
 * >> typedef struct ucpustate vio_cpustate_t;
 * >> #endif
 * >> // Emulate a VIO memory access at `faultaddr' using `self', and update `state'
 * >> vio_cpustate_t *
 * >> viocore_emulate(struct vio_descriptor *self,
 * >>                 void *faultaddr,
 * >>                 vio_cpustate_t *state);
 * This API would then also be exported within a user-space library. This API could then be
 * combined with `memfd_create()', alongside a potential kernel extension that can be used
 * to delegate user-space VIO memory accesses such that the kernel can delegate memory accesses
 * made to user-space VIO as follows:
 *     - Call `sys_write()' with a memory block containing a user-space VIO mapping
 *     - The memory access causes a #PF
 *     - The memory access is handled via kernel-space VIO
 *     - Kernel-space VIO is implemented using a server/client model,
 *       where the client is the kernel-space VIO wrapper, and the
 *       client is some user-space thread.
 * -> Since user-space memory can only ever be accessed when the
 *    kernel isn't actually holding any critical lock/resource, it
 *    is quite possible to have a memory access behave as blocking
 *    until user-space return the proper result!
 * NOTE: In this model, user-space wouldn't even need to be able to emulate X86 instructions!
 *       Since memory access is already broken down to its basic operations, kernel-space
 *       can simply include some operation ID in the request that is send to user-space!
 * >> fd_t userviofd(int flags);
 * The returned fd_t can be used with mmap(). Notifications can be read(2) and responded
 * through use of write(2), as well as poll(2)ed to wait for memory accesses to be requested.
 * A memory request would include the following information:
 *     >> syscall_ulong_t id;    // Unique ID that must be echoed back when responding
 *     >> pid_t           pid;   // PID of the process that made the request
 *     >> void           *vaddr; // Virtual address where the request was made
 *     >> pos_t           addr;  // VIO (file-)offset of the request
 *     >> syscall_ulong_t type;  // Access type (e.g. read, write, atomic_cmpxchg, etc...)
 *     >> ...                    // type-specific operands
 * A memory response would include:
 *     >> syscall_ulong_t id;    // The same `id' from the request
 *     >> syscall_ulong_t type;  // The same `type' from the request
 *     >> ...                    // type-specific results (e.g. a read operation
 *     >>                        // would have the read data-word appear here)
 *     >>                        // NOTE: May also be `VIO_RESPONSE_EXCEPT', in which
 *     >>                        //       case the kernel will raise a given exception
 *     >>                        //       within the waiting thread.
 * The kernel-space VIO implementation would then look like:
 *     >> vio_readl(addr) {
 *     >>     id     = SEND_VIO_REQUEST(READ4, addr);
 *     >>     result = WAITFOR_REQUEST(id);
 *     >>     return result;
 *     >> }
 */


#ifdef __CC__
__DECL_BEGIN

struct vio_emulate_args {
	struct vio_args vea_args; /* [OVERRIDE(.va_state, [1..1])] Underlying VIO arguments. */
	vio_addr_t      vea_addr; /* == vio_args_vioaddr(&.vea_args, .vea_ptr) */
	void           *vea_ptr;  /* Virtual address at which the VIO fault happened. */
};

/* Emulate the instruction pointed-to by `self->vea_args.va_state' and dispatch
 * any memory access made to `self->vea_ptr' by dispatching it using the VIO
 * callback table.
 * Upon success, `self->vea_args.va_state' will point to the updated CPU state,
 * which may be placed at a different address than it was upon entry.
 * This function is intended to be called from a page fault handler. */
typedef void (LIBVIOCORE_CC *PVIOCORE_EMULATE)(struct vio_emulate_args *__restrict self);
#ifdef LIBVIOCORE_WANT_PROTOTYPES
LIBVIOCORE_DECL void LIBVIOCORE_CC viocore_emulate(struct vio_emulate_args *__restrict self);
#endif /* LIBVIOCORE_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIOCORE_VIOCORE_H */
