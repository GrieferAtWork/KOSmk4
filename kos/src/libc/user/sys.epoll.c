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
#ifndef GUARD_LIBC_USER_SYS_EPOLL_C
#define GUARD_LIBC_USER_SYS_EPOLL_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include <string.h>

#include "sys.epoll.h"

DECL_BEGIN

/* This function is arch-specific */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED void const *LIBCCALL libc_get_rpc_exec_program(void);

/*[[[head:libc_epoll_create,hash:CRC-32=0x5d5fd124]]]*/
/* >> epoll_create(2)
 * Deprecated alias for `epoll_create1(0)' (the `size' argument is ignored)
 * @return: * : The newly created epoll control descriptor.
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.io.poll") WUNUSED fd_t
NOTHROW_NCX(LIBCCALL libc_epoll_create)(__STDC_INT_AS_SIZE_T size)
/*[[[body:libc_epoll_create]]]*/
{
	fd_t result;
	result = sys_epoll_create((syscall_ulong_t)size);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_epoll_create]]]*/

/*[[[head:libc_epoll_create1,hash:CRC-32=0x72a643a2]]]*/
/* >> epoll_create1(2)
 * Create  a new epoll control descriptor which can be used for
 * monitoring of pollable events happening in registered files.
 * @param: flags: Set of `EPOLL_CLOEXEC | EPOLL_CLOFORK'
 * @return: * :   The newly created epoll control descriptor.
 * @return: -1:   Error (s.a. `errno')
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_FLAG:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CREATE1_FLAGS: [...] */
INTERN ATTR_SECTION(".text.crt.io.poll") WUNUSED fd_t
NOTHROW_NCX(LIBCCALL libc_epoll_create1)(__STDC_INT_AS_UINT_T flags)
/*[[[body:libc_epoll_create1]]]*/
{
	fd_t result;
	result = sys_epoll_create1((syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_epoll_create1]]]*/

/*[[[head:libc_epoll_ctl,hash:CRC-32=0x61688acc]]]*/
/* >> epoll_ctl(2)
 * Manipulate a given  epoll controller  `epfd', as previously  returned by  `epoll_create1(2)'
 * in order to register (`EPOLL_CTL_ADD'), remove (`EPOLL_CTL_DEL') or modify (`EPOLL_CTL_MOD')
 * the file descriptors being monitored
 * @param: op:    One of `EPOLL_CTL_ADD', `EPOLL_CTL_DEL' or `EPOLL_CTL_MOD'
 * @param: fd:    The file descriptor to add/remove/modify
 * @param: event: The new configuration for `fd' (ignored when `op' is `EPOLL_CTL_DEL')
 * @return: 0 :   Success
 * @return: -1:   [errno=EEXIST][op=EPOLL_CTL_ADD] The given `fd' (and its kernel object) has already been registered
 * @return: -1:   [errno=ENOENT][op=EPOLL_CTL_MOD|EPOLL_CTL_DEL] The given `fd' (and its kernel object) aren't registered
 * @return: -1:   Error (s.a. `errno')
 * @throw: E_ILLEGAL_REFERENCE_LOOP: The  given  `fd'  is  another  epoll  that either
 *                                   forms a loop with `epfd', or has too many nested.
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CTL_OP: [...] */
INTERN ATTR_SECTION(".text.crt.io.poll") ATTR_FDARG(1) ATTR_FDARG(3) int
NOTHROW_NCX(LIBCCALL libc_epoll_ctl)(fd_t epfd,
                                     __epoll_ctl_t op,
                                     fd_t fd,
                                     struct epoll_event *event)
/*[[[body:libc_epoll_ctl]]]*/
{
	errno_t result;
	result = sys_epoll_ctl(epfd, (syscall_ulong_t)op, fd, event);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_epoll_ctl]]]*/

/*[[[head:libc_epoll_wait,hash:CRC-32=0xb50754d5]]]*/
/* >> epoll_wait(2)
 * Wait until at least one of the conditions monitored by `epfd' to be met.
 * @param: epfd:      The epoll controller on which to wait.
 * @param: events:    A buffer where the kernel can store information on the
 *                    events that actually took place.
 * @param: maxevents: The # of events that can be stored in `events' (must be >= 1)
 * @param: timeout:   The max amount of time (in milliseconds) before  returning
 *                    in the case where no event occurred in the mean time. When
 *                    set to `-1', wait indefinitely
 * @return: >= 1:     The # of events that happened (written to the first `return'
 *                    items of `events')
 * @return: 0:        No events happened before `timeout' expired.
 * @return: -1:       Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.io.poll") ATTR_FDARG(1) ATTR_OUTS(2, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(LIBCCALL libc_epoll_wait)(fd_t epfd,
                                      struct epoll_event *events,
                                      __STDC_INT_AS_SIZE_T maxevents,
                                      int timeout)
/*[[[body:libc_epoll_wait]]]*/
{
	ssize_t result;
	result = sys_epoll_wait(epfd,
	                        events,
	                        (syscall_ulong_t)maxevents,
	                        (syscall_slong_t)timeout);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_epoll_wait]]]*/

/*[[[head:libc_epoll_pwait,hash:CRC-32=0xf6b4677e]]]*/
/* >> epoll_pwait(2)
 * Same as `epoll_wait(2)', but change the calling thread's signal mask to `ss' while
 * waiting.  Wait until at least one of the conditions monitored by `epfd' to be met.
 * @param: epfd:      The epoll controller on which to wait.
 * @param: events:    A buffer where the kernel can store information on the
 *                    events that actually took place.
 * @param: maxevents: The # of events that can be stored in `events' (must be >= 1)
 * @param: timeout:   The max amount of time (in milliseconds) before  returning
 *                    in the case where no event occurred in the mean time. When
 *                    set to `-1', wait indefinitely
 * @param: ss:        The signal mask to apply while waiting for an event to happen.
 * @return: >= 1:     The # of events that happened (written to the first `return'
 *                    items of `events')
 * @return: 0:        No events happened before `timeout' expired.
 * @return: -1:       Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.io.poll") ATTR_FDARG(1) ATTR_OUTS(2, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(LIBCCALL libc_epoll_pwait)(fd_t epfd,
                                       struct epoll_event *events,
                                       __STDC_INT_AS_SIZE_T maxevents,
                                       int timeout,
                                       sigset_t const *ss)
/*[[[body:libc_epoll_pwait]]]*/
{
	ssize_t result;
	result = sys_epoll_pwait(epfd,
	                         events,
	                         (syscall_ulong_t)maxevents,
	                         (syscall_slong_t)timeout,
	                         ss,
	                         sizeof(sigset_t));
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_epoll_pwait]]]*/

/*[[[head:libc_epoll_rpc_exec,hash:CRC-32=0x79ff5670]]]*/
/* >> epoll_rpc_exec(3)
 * Helper wrapper for  `EPOLL_CTL_RPC_PROG' that  automatically provides  the
 * necessary arch-specific RPC program to invoke `func(..., event->data.ptr)'
 * as  soon as any of `event->events' become  raised in `fd'. The monitor for
 * this is associated with `epfd' and the RPC (if not already delivered)  can
 * be canceled  by `epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL)'.  Note that  as
 * soon  as the RPC  is send, the associated  monitor will have automatically
 * been deleted.
 *
 * This  function can be used to implement asynchronous notification of file
 * events to-be  delivered  to  arbitrary threads.  Using  this,  you  could
 * implement asynchronous, non-blocking I/O by sending RPCs to an I/O worker
 * thread  that will perform  reads/writes as soon  as they become possible.
 * @param: epfd:       Epoll controller file descriptor
 * @param: fd:         The file to monitor for events
 * @param: event:      Epoll event information, including monitored  events,
 *                     and the cookie argument that will be passed to `func'
 * @param: target_tid: The TID of the targeted thread
 * @param: mode:       One of `RPC_SYNCMODE_*',  optionally or'd  with
 *                     one of `RPC_SYSRESTART_*', optionally or'd with
 *                     one of `RPC_DOMAIN_*'
 * @param: func:       The function executed by the RPC
 * @return: 0 :                Success
 * @return: -1: [errno=ESRCH]  The  target  thread has  already  terminated, or
 *                             doesn't exist. Note  though that  if the  target
 *                             thread  exits prior to  any monitored file event
 *                             happening, the epoll  monitor will still  remain
 *                             intact, and the  RPC will be  discarded as  soon
 *                             as an attempt to send it is made, or the monitor
 *                             is manually deleted via `EPOLL_CTL_DEL' */
INTERN ATTR_SECTION(".text.crt.io.poll") ATTR_FDARG(1) ATTR_FDARG(2) ATTR_IN(3) NONNULL((6)) int
NOTHROW_NCX(LIBCCALL libc_epoll_rpc_exec)(fd_t epfd,
                                          fd_t fd,
                                          struct epoll_event const *event,
                                          pid_t target_tid,
                                          unsigned int mode,
                                          prpc_exec_callback_t func)
/*[[[body:libc_epoll_rpc_exec]]]*/
{
	void *args[2];
	struct epoll_rpc_program pinfo;
	struct epoll_event rpc_event;

	/* Arguments for the arch-specific RPC program */
	args[0] = (void *)func;
	args[1] = (void *)event->data.ptr;

	/* Fill in EPOLL RPC program information. */
	pinfo.erp_target          = (uint64_t)target_tid;
	pinfo.erp_mode            = (uint64_t)(syscall_ulong_t)mode;
	pinfo.erp_prog            = (uint64_t)(uintptr_t)libc_get_rpc_exec_program();
	pinfo.erp_params          = (uint64_t)(uintptr_t)args;
	pinfo.erp_max_param_count = 2;

	/* Fill in an epoll event descriptor for RPC_PROG */
	bzero(&rpc_event.data, sizeof(rpc_event.data));
	rpc_event.data.ptr = &pinfo;
	rpc_event.events   = event->events;

	/* Do the actual epoll control command. */
	return libc_epoll_ctl(epfd, EPOLL_CTL_RPC_PROG, fd, &rpc_event);
}
/*[[[end:libc_epoll_rpc_exec]]]*/





/*[[[start:exports,hash:CRC-32=0x9879653f]]]*/
DEFINE_PUBLIC_ALIAS(epoll_create, libc_epoll_create);
DEFINE_PUBLIC_ALIAS(epoll_create1, libc_epoll_create1);
DEFINE_PUBLIC_ALIAS(epoll_ctl, libc_epoll_ctl);
DEFINE_PUBLIC_ALIAS(epoll_wait, libc_epoll_wait);
DEFINE_PUBLIC_ALIAS(epoll_pwait, libc_epoll_pwait);
DEFINE_PUBLIC_ALIAS(epoll_rpc_exec, libc_epoll_rpc_exec);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_EPOLL_C */
