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

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.except.io.utility")]
%[default:nodos]

%[define_decl_include_implication("<bits/os/epoll.h>" => ["<bits/types.h>"])]
%[define_decl_include("<bits/os/epoll.h>": ["union epoll_data", "struct epoll_event"])]

%[define_decl_include_implication("<bits/os/sigset.h>" => ["<hybrid/typecore.h>"])]
%[define_decl_include("<bits/os/sigset.h>": ["struct __sigset_struct"])]
%[define_replacement(sigset_t = "struct __sigset_struct")]

%[insert:prefix(
#include <sys/epoll.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __sigset_t_defined
#define __sigset_t_defined
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

}


[[throws, doc_alias("epoll_create")]]
[[wunused, decl_include("<features.h>", "<bits/types.h>")]]
$fd_t EPollCreate(__STDC_INT_AS_SIZE_T size);

[[throws, doc_alias("epoll_create1")]]
[[wunused, decl_include("<features.h>", "<bits/types.h>")]]
$fd_t EPollCreate1(__STDC_INT_AS_UINT_T flags);


[[throws, doc_alias("epoll_ctl")]]
[[decl_include("<bits/os/epoll.h>")]]
void EPollCtl($fd_t epfd, __epoll_ctl_t op,
              $fd_t fd, struct epoll_event *event);

[[cp, throws, doc_alias("epoll_wait")]]
[[decl_include("<features.h>", "<bits/os/epoll.h>")]]
__STDC_UINT_AS_SIZE_T EPollWait($fd_t epfd, [[inout(maxevents)]] struct epoll_event *events,
                                __STDC_UINT_AS_SIZE_T maxevents, int timeout);

[[cp, throws, doc_alias("epoll_pwait")]]
[[decl_include("<features.h>", "<bits/os/epoll.h>")]]
__STDC_UINT_AS_SIZE_T EPollPWait($fd_t epfd, [[inout(maxevents)]] struct epoll_event *events,
                                 __STDC_UINT_AS_SIZE_T maxevents, int timeout,
                                 [[in_opt]] sigset_t const *ss);

%
%#ifdef __USE_KOS
%{
#ifndef __prpc_exec_callback_t_defined
#define __prpc_exec_callback_t_defined
#ifndef PRPC_EXEC_CALLBACK_CC
#ifdef __KERNEL__
typedef struct icpustate rpc_cpustate_t;
#define PRPC_EXEC_CALLBACK_CC __FCALL
#else /* __KERNEL__ */
typedef struct ucpustate rpc_cpustate_t;
#define PRPC_EXEC_CALLBACK_CC __LIBKCALL
#endif /* !__KERNEL__ */
#endif /* !PRPC_EXEC_CALLBACK_CC */
struct rpc_context;
typedef __ATTR_NONNULL_T((1)) void
(PRPC_EXEC_CALLBACK_CC *prpc_exec_callback_t)(struct rpc_context *__restrict __ctx, void *__cookie)
		__THROWS(...);
#endif /* !__prpc_exec_callback_t_defined */
}

[[throws, doc_alias("epoll_rpc_exec")]]
[[decl_include("<bits/os/epoll.h>")]]
void EPollRpcExec($fd_t epfd, $fd_t fd,
                  [[in]] struct epoll_event const *event,
                  $pid_t target_tid, unsigned int mode,
                  [[nonnull]] prpc_exec_callback_t func);
%#endif /* __USE_KOS */


%{

__SYSDECL_END
#endif /* __CC__ */

}
