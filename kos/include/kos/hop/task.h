/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_HOP_TASK_H
#define _KOS_HOP_TASK_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#include "openfd.h"

__DECL_BEGIN


#define __OFFSET_HOP_TASK_JOIN_STRUCT_SIZE     0
#define __OFFSET_HOP_TASK_JOIN_RELTIMEOUT_SEC  8
#define __OFFSET_HOP_TASK_JOIN_RELTIMEOUT_NSEC 16
#define __OFFSET_HOP_TASK_JOIN_STATUS          20
#define __SIZEOF_HOP_TASK_JOIN                 24
#ifdef __CC__
struct hop_task_join /*[PREFIX(tj_)]*/ {
	__uint32_t            tj_struct_size;     /* [== sizeof(struct hop_task_join)]
	                                           * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                           * this value is too small  or doesn't match any  recognized
	                                           * structure version. */
	__uint32_t          __tj_pad1;            /* ... */
	__uint64_t            tj_reltimeout_sec;  /* Relative timeout seconds (or (__uint64_t)-1 to wait indefinitely) */
	__uint32_t            tj_reltimeout_nsec; /* Relative timeout nano seconds (< 1000000000 == 1_000_000_000) */
	__uint32_t            tj_status;          /* [OUT][TYPE(union wait)]  The exit status of the thread.
	                                           * If the thread has yet to exit, this field is set to `0' */
};
#endif /* __CC__ */


/* Return value of hop() for `HOP_TASK_SETPROCESSGROUPLEADER' */
#define HOP_TASK_SETPROCESSGROUPLEADER_SUCCESS 0 /* Successfully added `HOP_TASK_OPEN_PROCESS(thread)' to the process group
                                                  * that `tspgl_leader' is apart of (which is `HOP_TASK_OPEN_PROCESS_GROUP_LEADER(tspgl_leader)'),
                                                  * or make `thread' become its own process group when
                                                  * `HOP_TASK_OPEN_PROCESS(thread) == HOP_TASK_OPEN_PROCESS(tspgl_leader) */
#define HOP_TASK_SETPROCESSGROUPLEADER_LEADER  1 /*  The given `thread' is already the tspgl_leader of its own process group.
                                                  * -> Once promoted to a group leader, a process cannot back out and no longer be one! */
#define HOP_TASK_SETPROCESSGROUPLEADER_EXITED  2 /* The given `tspgl_leader' has already terminated. */
#define __OFFSET_HOP_TASK_SETPROCESSGROUPLEADER_STRUCT_SIZE 0
#define __OFFSET_HOP_TASK_SETPROCESSGROUPLEADER_LEADER      4
#define __OFFSET_HOP_TASK_SETPROCESSGROUPLEADER_OLD_LEADER  8
#define __OFFSET_HOP_TASK_SETPROCESSGROUPLEADER_NEW_LEADER  16
#define __SIZEOF_HOP_TASK_SETPROCESSGROUPLEADER             24
#ifdef __CC__
struct hop_task_setprocessgroupleader /*[PREFIX(tspgl_)]*/ {
	__uint32_t            tspgl_struct_size; /* [== sizeof(struct hop_task_setprocessgroupleader)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small  or doesn't match any  recognized
	                                          * structure version. */
	__uint32_t            tspgl_leader;      /* [IN] Handle for to a thread who's process should be used as leader */
	struct hop_openfd    *tspgl_old_leader;  /* [OUT_OPT][0..1] When non-NULL store a handle to the old process group leader of `HOP_TASK_OPEN_PROCESS(<thread>)'. (NOTE: Only written to on HOP_TASK_SETPROCESSGROUPLEADER_SUCCESS) */
	__HOP_PAD_POINTER  (__tspgl_pad1)        /* ... */
	struct hop_openfd    *tspgl_new_leader;  /* [OUT_OPT][0..1] When non-NULL store a handle to the new process group leader of `HOP_TASK_OPEN_PROCESS(<thread>)'. (NOTE: Only written to on HOP_TASK_SETPROCESSGROUPLEADER_SUCCESS) */
	__HOP_PAD_POINTER  (__tspgl_pad2)        /* ... */

};
#endif /* __CC__ */


/* Return value of hop() for `HOP_TASK_SETPROCESSGROUPLEADER' */
#define HOP_TASK_SETSESSIONLEADER_SUCCESS 0 /* Successfully added `HOP_TASK_OPEN_PROCESS(thread)' (which at that
                                             * point is guarantied to be identical to `HOP_TASK_OPEN_PROCESS_GROUP_LEADER(thread)')
                                             * to the session that `tssl_leader' is apart of (which is
                                             * `HOP_TASK_OPEN_SESSION_LEADER(tssl_leader)'), or  make  `thread'  become  a  new  session  when
                                             * `HOP_TASK_OPEN_PROCESS_GROUP_LEADER(thread) == HOP_TASK_OPEN_PROCESS_GROUP_LEADER(tssl_leader)' */
#define HOP_TASK_SETSESSIONLEADER_LEADER  1 /* The given `thread' is already the leader of a different session than `tssl_leader'.
                                             * -> Once promoted to a session leader, a process group cannot back out and no longer be one! */
#define __OFFSET_HOP_TASK_SETSESSIONLEADER_STRUCT_SIZE    0
#define __OFFSET_HOP_TASK_SETSESSIONLEADER_LEADER         4
#define __OFFSET_HOP_TASK_SETSESSIONLEADER_OLD_GRP_LEADER 8
#define __OFFSET_HOP_TASK_SETSESSIONLEADER_OLD_LEADER     16
#define __OFFSET_HOP_TASK_SETSESSIONLEADER_NEW_LEADER     24
#define __SIZEOF_HOP_TASK_SETSESSIONLEADER                32
#ifdef __CC__
struct hop_task_setsessionleader /*[PREFIX(tssl_)]*/ {
	__uint32_t            tssl_struct_size;    /* [== sizeof(struct hop_task_setsessionleader)]
	                                             * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                             * this value is too small or doesn't match any recognized
	                                             * structure version. */
	__uint32_t            tssl_leader;         /* [IN] Handle for to a thread who's process should be used as leader */
	struct hop_openfd    *tssl_old_grp_leader; /* [OUT_OPT][0..1] When non-NULL store a handle to the old process group leader of `HOP_TASK_OPEN_PROCESS(<thread>)'. (NOTE: Only written to on HOP_TASK_SETSESSIONLEADER_SUCCESS) */
	__HOP_PAD_POINTER  (__tspgl_pad1)          /* ... */
	struct hop_openfd    *tssl_old_leader;     /* [OUT_OPT][0..1] When non-NULL store a handle to the old session leader of `HOP_TASK_OPEN_PROCESS(<thread>)'. (NOTE: Only written to on HOP_TASK_SETSESSIONLEADER_SUCCESS) */
	__HOP_PAD_POINTER  (__tspgl_pad2)          /* ... */
	struct hop_openfd    *tssl_new_leader;     /* [OUT_OPT][0..1] When non-NULL store a handle to the new session leader of `HOP_TASK_OPEN_PROCESS(<thread>)'. (NOTE: Only written to on HOP_TASK_SETSESSIONLEADER_SUCCESS) */
	__HOP_PAD_POINTER  (__tspgl_pad3)          /* ... */

};
#endif /* __CC__ */





/* For HANDLE_TYPE_TASK */
#define HOP_TASK_JOIN                             0x00090001 /* [struct hop_task_join *data] Join a given thread
                                                              * HINT: You may also use a task handle with poll() to wait for the thread to terminate.
                                                              * @return: 0:          The thread has terminated. (Its exit status was written to `data->tj_status')
                                                              * @return: -ETIMEDOUT: The given timeout has expired. (data->tj_status was set to 0) */
#define HOP_TASK_GETTID                           0x00090002 /* hop() returns the TID of the given thread */
#define HOP_TASK_GETPID                           0x00090003 /* hop() returns the process ID of the given thread
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_GETPPID                          0x00090004 /* hop() returns the parent process ID of the given thread
                                                              * If the thread doesn't have  a parent, return 0  instead
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_GETPGID                          0x00090005 /* hop() returns the process group ID of the given thread
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_GETSID                           0x00090006 /* hop() returns the session ID of the given thread
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_OPEN_PROCESS                     0x00090007 /* [struct hop_openfd *result] Open the process leader of the given thread.
                                                              * @throw: E_PROCESS_EXITED: [...]
                                                              * @return: == result->of_hint */
#define HOP_TASK_OPEN_PROCESS_PARENT              0x00090008 /* [struct hop_openfd *result] Open the parent process of the given thread.
                                                              * If the thread doesn't have a parent, return 0 instead
                                                              * @throw: E_NO_SUCH_PROCESS: The thread was detached from its parent process.
                                                              * @throw: E_PROCESS_EXITED:  [...]
                                                              * @return: == result->of_hint */
#define HOP_TASK_OPEN_PROCESS_GROUP_LEADER        0x00090009 /* [struct hop_openfd *result] Open the process group leader of the given thread.
                                                              * @throw: E_PROCESS_EXITED: [...]
                                                              * @return: == result->of_hint */
#define HOP_TASK_OPEN_SESSION_LEADER              0x0009000a /* [struct hop_openfd *result] Open the process group leader of the given thread.
                                                              * @throw: E_PROCESS_EXITED: [...]
                                                              * @return: == result->of_hint */
#define HOP_TASK_IS_PROCESS_LEADER                0x0009000b /* hop() returns 0/1 indicating if the thread is a process leader
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_IS_PROCESS_GROUP_LEADER          0x0009000c /* hop() returns 0/1 indicating if the thread is a process group leader
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_IS_SESSION_LEADER                0x0009000d /* hop() returns 0/1 indicating if the thread is a session leader
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_DETACH                           0x0009000e /* Detach the given thread from its parent
                                                              * @return: true:  Successfully detached the given thread'
                                                              * @return: false: The given thread had already been detached.
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_DETACH_CHILDREN                  0x0009000f /* Detach all child threads/processes of the given process
                                                              * @return: * : The number of detached children.
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_SETPROCESSGROUPLEADER            0x00090010 /* [struct hop_task_setprocessgroupleader *data]
                                                              * Set the group leader for the process of the given thread.
                                                              * NOTE: If the given leader isn't a process leader,
                                                              *      `HOP_TASK_OPEN_PROCESS(leader)' will be used instead.
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_SETSESSIONLEADER                 0x00090011 /* [struct hop_task_setsessionleader *data]
                                                              * Set the session leader for the process of the given thread.
                                                              * NOTE: If the given leader isn't a process leader,
                                                              *      `HOP_TASK_OPEN_PROCESS(leader)' will be used instead.
                                                              * @throw: E_PROCESS_EXITED: [...] */
/* TODO: HOP_TASK_SIGNAL -- FD-interface for the kill() and friends */
/* TODO: HOP_TASK_SIGNAL -- This should also include a function to raise a signal with a custom CPU context. */
/* TODO: HOP_TASK_RPC -- FD-interface for the `rpc_schedule()' system call */



__DECL_END

#endif /* !_KOS_HOP_TASK_H */
