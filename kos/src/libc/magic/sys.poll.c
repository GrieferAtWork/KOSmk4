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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[define_replacement(nfds_t = __UINTPTR_TYPE__)]
%[define_replacement(sigset_t = struct __sigset_struct)]
%[define_replacement(fd_t = __fd_t)]
%[define_replacement(time_t   = __TM_TYPE(time))]
%[define_replacement(time32_t = __time32_t)]
%[define_replacement(time64_t = __time64_t)]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[default_impl_section(.text.crt.io.poll)]


%{
#include <features.h>
#include <bits/types.h>
#include <bits/poll.h>
#include <hybrid/typecore.h>
#ifdef __USE_GNU
#include <bits/sigset.h>
#include <bits/timespec.h>
#endif /* __USE_GNU */

__SYSDECL_BEGIN

#ifdef __CC__
#ifndef __nfds_t_defined
#define __nfds_t_defined 1
typedef __UINTPTR_TYPE__ nfds_t;
#endif /* !__nfds_t_defined */

#ifndef __pollfd_defined
#define __pollfd_defined 1
}%[push_macro @undef { fd events revents }]%{
struct pollfd {
	__fd_t         fd;      /* File descriptor to poll.  */
	__INT16_TYPE__ events;  /* Types of events poller cares about (Set of 'POLL*'). */
	__INT16_TYPE__ revents; /* Types of events that actually occurred (Set of 'POLL*'). */
};
}%[pop_macro]%{
#endif /* !__pollfd_defined */

}

%(user){
DECL_END
#include <bits/sigset.h>
DECL_BEGIN

#ifndef __sigset_t_defined
#define __sigset_t_defined 1
typedef __sigset_t sigset_t;
#endif /* !__sigset_t_defined */

}

@@@param timeout: Timeout in milliseconds (or negative for infinity)
[export_alias(__poll)][cp]
poll:([inp(nfds)] struct pollfd *fds, nfds_t nfds, int timeout) -> int;

%#ifdef __USE_GNU

[cp][ignore]
ppoll32:([inp(nfds)] struct pollfd *fds, nfds_t nfds,
         [nullable] struct $timespec32 const *timeout,
         [nullable] $sigset_t const *ss) -> int = ppoll?;

[cp][noexport]
[if(defined(__USE_TIME_BITS64)),preferred_alias(ppoll)]
[if(!defined(__USE_TIME_BITS64)),preferred_alias(ppoll64)]
[requires(defined(__CRT_HAVE_ppoll) || defined(__CRT_HAVE_ppoll64))]
ppoll:([inp(nfds)] struct pollfd *fds, nfds_t nfds,
       [nullable] struct timespec const *timeout,
       [nullable] $sigset_t const *ss) -> int {
#ifdef __CRT_HAVE_ppoll
	struct timespec32 tmo32;
	if (!timeout)
		return ppoll32(fds,nfds,NULL,ss);
	tmo32.@tv_sec@  = (time32_t)timeout->@tv_sec@;
	tmo32.@tv_nsec@ = timeout->@tv_nsec@;
	return ppoll32(fds,nfds,&tmo32,ss);
#else
	struct timespec64 tmo64;
	if (!timeout)
		return ppoll64(fds,nfds,NULL,ss);
	tmo64.@tv_sec@  = (time64_t)timeout->@tv_sec@;
	tmo64.@tv_nsec@ = timeout->@tv_nsec@;
	return ppoll64(fds,nfds,&tmo64,ss);
#endif
}

%
%#ifdef __USE_TIME64
[time64_variant_of(ppoll)]
[cp][noexport][requires($has_function(ppoll32))]
ppoll64:([inp(nfds)] struct pollfd *fds, nfds_t nfds,
         [nullable] struct timespec64 const *timeout,
         [nullable] $sigset_t const *ss) -> int {
	struct timespec32 tmo32;
	if (!timeout)
		return ppoll32(fds,nfds,NULL,ss);
	tmo32.@tv_sec@  = (time32_t)timeout->@tv_sec@;
	tmo32.@tv_nsec@ = timeout->@tv_nsec@;
	return ppoll32(fds,nfds,&tmo32,ss);
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_GNU */

%{
#endif /* __CC__ */

__SYSDECL_END

}
