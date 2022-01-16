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
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[define_replacement(time_t   = "__TM_TYPE(time)")]
%[define_replacement(time32_t = __time32_t)]
%[define_replacement(time64_t = __time64_t)]
%[define_replacement(__SOCKADDR_ARG       = "struct sockaddr *__restrict")]
%[define_replacement(__CONST_SOCKADDR_ARG = "struct sockaddr const *__restrict")]
%[default:nodos]
%[default:section(".text.crt.except.net.socket")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <sys/socket.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}


[[throws, doc_alias("socket")]]
[[wunused, decl_include("<features.h>", "<bits/types.h>")]]
$fd_t Socket(__STDC_INT_AS_UINT_T domain, __STDC_INT_AS_UINT_T type,
             __STDC_INT_AS_UINT_T protocol);

[[throws, doc_alias("socketpair")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
void SocketPair(__STDC_INT_AS_UINT_T domain, __STDC_INT_AS_UINT_T type,
                __STDC_INT_AS_UINT_T protocol, [[nonnull]] $fd_t fds[2]);

[[throws, doc_alias("bind")]]
[[decl_include("<bits/types.h>", "<bits/os/sockaddr.h>")]]
void Bind($fd_t sockfd, [[inp(addr_len)]] __CONST_SOCKADDR_ARG addr,
          socklen_t addr_len);

[[throws, doc_alias("getsockname")]]
[[decl_include("<bits/types.h>", "<bits/os/sockaddr.h>")]]
void GetSockName($fd_t sockfd, [[outp(*addr_len)]] __SOCKADDR_ARG addr,
                 [[nonnull]] socklen_t *__restrict addr_len);

[[cp, throws, doc_alias("connect")]]
[[decl_include("<bits/types.h>", "<bits/os/sockaddr.h>")]]
void Connect($fd_t sockfd, [[inp(addr_len)]] __CONST_SOCKADDR_ARG addr,
             socklen_t addr_len);

[[throws, doc_alias("getpeername")]]
[[decl_include("<bits/types.h>", "<bits/os/sockaddr.h>")]]
void GetPeerName($fd_t sockfd, [[outp(*addr_len)]] __SOCKADDR_ARG addr,
                 [[nonnull]] socklen_t *__restrict addr_len);

[[cp, throws, doc_alias("send")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
size_t Send($fd_t sockfd, [[inp(bufsize)]] void const *buf,
            size_t bufsize, __STDC_INT_AS_UINT_T msg_flags);

[[cp, throws, doc_alias("recv")]]
[[wunused, decl_include("<features.h>", "<bits/types.h>")]]
size_t Recv($fd_t sockfd, [[outp(bufsize)]] void *buf,
            size_t bufsize, __STDC_INT_AS_UINT_T msg_flags);

[[cp, throws, doc_alias("sendto")]]
[[decl_include("<features.h>", "<bits/types.h>", "<bits/os/sockaddr.h>")]]
size_t SendTo($fd_t sockfd, [[inp(bufsize)]] void const *buf,
              size_t bufsize, __STDC_INT_AS_UINT_T msg_flags,
              [[inp_opt(addr_len)]] __CONST_SOCKADDR_ARG addr,
              socklen_t addr_len);

[[cp, throws, doc_alias("recvfrom")]]
[[wunused, decl_include("<features.h>", "<bits/types.h>", "<bits/os/sockaddr.h>")]]
size_t RecvFrom($fd_t sockfd, [[outp(bufsize)]] void *__restrict buf,
                size_t bufsize, __STDC_INT_AS_UINT_T msg_flags,
                [[outp_opt(*addr_len)]] __SOCKADDR_ARG addr,
                [[nullable]] socklen_t *__restrict addr_len);

[[cp, throws, doc_alias("sendmsg")]]
[[decl_include("<features.h>", "<bits/types.h>", "<bits/os/msghdr.h>")]]
size_t SendMsg($fd_t sockfd, [[nonnull]] struct msghdr const *message,
               __STDC_INT_AS_UINT_T msg_flags);

[[cp, throws, doc_alias("recvmsg")]]
[[wunused, decl_include("<features.h>", "<bits/types.h>", "<bits/os/msghdr.h>")]]
size_t RecvMsg($fd_t sockfd, [[nonnull]] struct msghdr *message,
               __STDC_INT_AS_UINT_T msg_flags);

[[throws, doc_alias("getsockopt")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
void GetSockOpt($fd_t sockfd, __STDC_INT_AS_UINT_T level, __STDC_INT_AS_UINT_T optname,
                [[outp(*optlen)]] void *__restrict optval, [[nonnull]] socklen_t *__restrict optlen);

[[throws, doc_alias("setsockopt")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
void SetSockOpt($fd_t sockfd, __STDC_INT_AS_UINT_T level, __STDC_INT_AS_UINT_T optname,
                [[inp(optlen)]] void const *optval, socklen_t optlen);

[[throws, doc_alias("listen")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
void Listen($fd_t sockfd, __STDC_INT_AS_UINT_T max_backlog);

[[cp, throws, doc_alias("accept")]]
[[decl_include("<bits/types.h>", "<bits/os/sockaddr.h>")]]
$fd_t Accept($fd_t sockfd, [[outp_opt(*addr_len)]] __SOCKADDR_ARG addr,
             socklen_t *__restrict addr_len);

[[throws, doc_alias("shutdown")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
void Shutdown($fd_t sockfd, __STDC_INT_AS_UINT_T how);

%
%#ifdef __USE_GNU
[[cp, throws, doc_alias("accept4")]]
[[decl_include("<features.h>", "<bits/types.h>", "<bits/os/sockaddr.h>")]]
$fd_t Accept4($fd_t sockfd, [[outp_opt(*addr_len)]] __SOCKADDR_ARG addr,
              socklen_t *__restrict addr_len, __STDC_INT_AS_UINT_T sock_flags);

[[cp, throws, doc_alias("sendmmsg")]]
[[decl_include("<features.h>", "<bits/types.h>", "<bits/os/mmsghdr.h>")]]
size_t SendMMsg($fd_t sockfd, [[nonnull]] struct mmsghdr *vmessages,
                __STDC_UINT_AS_SIZE_T vlen, __STDC_INT_AS_UINT_T msg_flags);

[[cp, throws, doc_alias("recvmmsg"), ignore, nocrt, alias("recvmmsg")]]
[[decl_include("<features.h>", "<bits/types.h>", "<bits/os/mmsghdr.h>", "<bits/os/timespec.h>")]]
size_t RecvMMsg32($fd_t sockfd, [[inp(vlen)]] struct mmsghdr *vmessages,
                  __STDC_UINT_AS_SIZE_T vlen, __STDC_INT_AS_UINT_T msg_flags,
                  [[nullable]] struct $timespec32 *tmo);

[[cp, throws, doc_alias("recvmmsg"), decl_include("<features.h>", "<bits/types.h>", "<bits/os/mmsghdr.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("RecvMMsg")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("RecvMMsg64")]]
[[userimpl, requires($has_function(RecvMMsg32) || $has_function(RecvMMsg64))]]
size_t RecvMMsg($fd_t sockfd, [[inp(vlen)]] struct mmsghdr *vmessages,
                __STDC_UINT_AS_SIZE_T vlen, __STDC_INT_AS_UINT_T msg_flags,
                [[nullable]] struct timespec *tmo) {
@@pp_if $has_function(RecvMMsg64)@@
	struct timespec64 tmo64;
	if (!tmo)
		return RecvMMsg64(sockfd, vmessages, vlen, msg_flags, NULL);
	tmo64.tv_sec  = (time64_t)tmo->tv_sec,
	tmo64.tv_nsec = tmo->tv_nsec;
	return RecvMMsg64(sockfd, vmessages, vlen, msg_flags, &tmo64);
@@pp_else@@
	struct timespec32 tmo32;
	if (!tmo)
		return RecvMMsg32(sockfd, vmessages, vlen, msg_flags, NULL);
	tmo32.tv_sec  = (time32_t)tmo->tv_sec,
	tmo32.tv_nsec = tmo->tv_nsec;
	return RecvMMsg32(sockfd, vmessages, vlen, msg_flags, &tmo32);
@@pp_endif@@
}

%#ifdef __USE_TIME64
[[cp, throws, preferred_time64_variant_of(RecvMMsg), doc_alias("recvmmsg")]]
[[userimpl, requires_function(RecvMMsg32)]]
[[decl_include("<features.h>", "<bits/types.h>", "<bits/os/mmsghdr.h>", "<bits/os/timespec.h>")]]
size_t RecvMMsg64($fd_t sockfd, [[inp(vlen)]] struct mmsghdr *vmessages,
                  __STDC_UINT_AS_SIZE_T vlen, __STDC_INT_AS_UINT_T msg_flags,
                  [[nullable]] struct timespec64 *tmo) {
	struct timespec32 tmo32;
	if (!tmo)
		return RecvMMsg32(sockfd, vmessages, vlen, msg_flags, NULL);
	tmo32.tv_sec  = (time32_t)tmo->tv_sec,
	tmo32.tv_nsec = tmo->tv_nsec;
	return RecvMMsg32(sockfd, vmessages, vlen, msg_flags, &tmo32);
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_GNU */


%{

__SYSDECL_END
#endif /* __CC__ */

}
