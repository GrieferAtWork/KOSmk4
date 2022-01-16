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
#ifndef _KOS_EXCEPT_REASON_ILLOP_H
#define _KOS_EXCEPT_REASON_ILLOP_H 1

#include <__stdinc.h>

__DECL_BEGIN

/* Reason codes for `E_ILLEGAL_OPERATION' */

/*[[[enum]]]*/
#ifdef __CC__
enum {
	E_ILLEGAL_OPERATION_CONTEXT_OPEN_S_IFSOCK = 1,       /* E_ILLEGAL_OPERATION: Attempted to open(2) an `S_IFSOCK'-file */
	E_ILLEGAL_OPERATION_CONTEXT_NOT_RTM,                 /* E_ILLEGAL_OPERATION: Attempted to call `rtm_end(2)' outside of RTM mode */
	E_ILLEGAL_OPERATION_CONTEXT_RTM_ALREADY_LOADED,      /* E_ILLEGAL_OPERATION: Attempted to install RTM hooks after they were already loaded */
	E_ILLEGAL_OPERATION_CONTEXT_SETPGID_LEADER,          /* E_ILLEGAL_PROCESS_OPERATION: Attempted to move the leader of a process group into a different process group (`pid2' is the PID of the target process group) */
	E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MONITOR_LOOP,      /* E_ILLEGAL_REFERENCE_LOOP: epoll_ctl(EPOLL_CTL_ADD) failed because a reference loop would have been formed */
	E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MONITOR_SELF_LOOP, /* E_ILLEGAL_REFERENCE_LOOP: epoll_ctl(EPOLL_CTL_ADD) failed because you tried to monitor the epoll controller with itself */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define E_ILLEGAL_OPERATION_CONTEXT_OPEN_S_IFSOCK           E_ILLEGAL_OPERATION_CONTEXT_OPEN_S_IFSOCK           /* E_ILLEGAL_OPERATION: Attempted to open(2) an `S_IFSOCK'-file */
#define E_ILLEGAL_OPERATION_CONTEXT_NOT_RTM                 E_ILLEGAL_OPERATION_CONTEXT_NOT_RTM                 /* E_ILLEGAL_OPERATION: Attempted to call `rtm_end(2)' outside of RTM mode */
#define E_ILLEGAL_OPERATION_CONTEXT_RTM_ALREADY_LOADED      E_ILLEGAL_OPERATION_CONTEXT_RTM_ALREADY_LOADED      /* E_ILLEGAL_OPERATION: Attempted to install RTM hooks after they were already loaded */
#define E_ILLEGAL_OPERATION_CONTEXT_SETPGID_LEADER          E_ILLEGAL_OPERATION_CONTEXT_SETPGID_LEADER          /* E_ILLEGAL_PROCESS_OPERATION: Attempted to move the leader of a process group into a different process group (`pid2' is the PID of the target process group) */
#define E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MONITOR_LOOP      E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MONITOR_LOOP      /* E_ILLEGAL_REFERENCE_LOOP: epoll_ctl(EPOLL_CTL_ADD) failed because a reference loop would have been formed */
#define E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MONITOR_SELF_LOOP E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MONITOR_SELF_LOOP /* E_ILLEGAL_REFERENCE_LOOP: epoll_ctl(EPOLL_CTL_ADD) failed because you tried to monitor the epoll controller with itself */
#else /* __COMPILER_PREFERR_ENUMS */
#define E_ILLEGAL_OPERATION_CONTEXT_OPEN_S_IFSOCK           1 /* E_ILLEGAL_OPERATION: Attempted to open(2) an `S_IFSOCK'-file */
#define E_ILLEGAL_OPERATION_CONTEXT_NOT_RTM                 2 /* E_ILLEGAL_OPERATION: Attempted to call `rtm_end(2)' outside of RTM mode */
#define E_ILLEGAL_OPERATION_CONTEXT_RTM_ALREADY_LOADED      3 /* E_ILLEGAL_OPERATION: Attempted to install RTM hooks after they were already loaded */
#define E_ILLEGAL_OPERATION_CONTEXT_SETPGID_LEADER          4 /* E_ILLEGAL_PROCESS_OPERATION: Attempted to move the leader of a process group into a different process group (`pid2' is the PID of the target process group) */
#define E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MONITOR_LOOP      5 /* E_ILLEGAL_REFERENCE_LOOP: epoll_ctl(EPOLL_CTL_ADD) failed because a reference loop would have been formed */
#define E_ILLEGAL_OPERATION_CONTEXT_EPOLL_MONITOR_SELF_LOOP 6 /* E_ILLEGAL_REFERENCE_LOOP: epoll_ctl(EPOLL_CTL_ADD) failed because you tried to monitor the epoll controller with itself */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/



__DECL_END

#endif /* !_KOS_EXCEPT_REASON_ILLOP_H */
