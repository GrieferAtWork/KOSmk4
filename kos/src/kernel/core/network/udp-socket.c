/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_NETWORK_UDP_SOCKET_C
#define GUARD_KERNEL_SRC_NETWORK_UDP_SOCKET_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/nic.h>
#include <sched/task.h>

#include <hybrid/minmax.h>

#include <kos/except/reason/illop.h>
#include <kos/except/reason/inval.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <network/ip.h>
#include <network/network.h>
#include <network/udp-socket.h>
#include <network/udp.h>

#include <assert.h>
#include <atomic.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

PRIVATE USER CHECKED struct sockaddr_in const *KCALL
udp_verify_sockaddr(USER CHECKED struct sockaddr const *addr,
                    socklen_t addr_len) {
	USER CHECKED struct sockaddr_in *in;
	sa_family_t fam;
	if unlikely(addr_len < sizeof(struct sockaddr_in))
		THROW(E_BUFFER_TOO_SMALL, sizeof(struct sockaddr_in), addr_len);
	in = (USER CHECKED struct sockaddr_in *)addr;
	fam = atomic_read(&in->sin_family);
	if (fam != AF_INET) {
		THROW(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY,
		      fam, AF_INET);
	}
	return in;
}

PRIVATE ATTR_RETNONNULL struct nicdev *KCALL
udp_getnic(struct udp_socket *__restrict me) {
	struct nicdev *result;
again:
	result = me->us_dev;
	if (!result) {
		result = nicdev_getdefault();
		if unlikely(!result)
			THROW(E_NO_SUCH_OBJECT);
		if (!atomic_cmpxch(&me->us_dev, NULL, result)) {
			decref_unlikely(result);
			COMPILER_READ_BARRIER();
			goto again;
		}
	}
	return result;
}

PRIVATE void KCALL
udp_autobind_impl(struct udp_socket *__restrict me) {
	static u16 nextport = 10000;
	/* TODO: Do proper port binding! */
	/* TODO: Linux uses a /proc file to specify the range of
	 *       ports  used for dynamic  port allocation by IP:
	 *       /proc/sys/net/ipv4/ip_local_port_range
	 *       We  should  also support  that file  and select
	 *       some port out of that range here. */
	me->us_bindip.s_addr = htonl(0);
	me->us_bindport      = htons(atomic_fetchinc(&nextport));
}

/* Automatically bind the given UDP socket to some unused local port. */
PRIVATE ATTR_NOINLINE void KCALL
udp_autobind(struct udp_socket *__restrict me) {
	uintptr_t state;
again:
	state = atomic_fetchor(&me->us_state, UDP_SOCKET_STATE_F_BINDING);
	if (state & UDP_SOCKET_STATE_F_BOUND)
		return; /* Already bound. */
	if (state & UDP_SOCKET_STATE_F_BINDING) {
		/* Some other thread is also binding right now... */
		task_yield();
		COMPILER_BARRIER();
		goto again;
	}

	/* Do the yield ourself! */
	TRY {
		udp_autobind_impl(me);
	} EXCEPT {
		atomic_and(&me->us_state, ~UDP_SOCKET_STATE_F_BINDING);
		RETHROW();
	}
	atomic_or(&me->us_state, UDP_SOCKET_STATE_F_BOUND);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL udp_fini)(struct socket *__restrict self) {
	struct udp_socket *me;
	me = (struct udp_socket *)self;
	xdecref(me->us_dev);
}

PRIVATE NONNULL((1)) socklen_t KCALL
udp_getsockname(struct socket *__restrict self,
                USER CHECKED struct sockaddr *addr,
                socklen_t addr_len) {
	struct udp_socket *me;
	USER CHECKED struct sockaddr_in *in;
	me = (struct udp_socket *)self;
	in = (USER CHECKED struct sockaddr_in *)addr;
	if likely(addr_len >= offsetafter(struct sockaddr_in, sin_family))
		in->sin_family = AF_INET;
	if likely(addr_len >= offsetafter(struct sockaddr_in, sin_port))
		in->sin_port = me->us_bindport;
	if likely(addr_len >= offsetafter(struct sockaddr_in, sin_addr.s_addr))
		in->sin_addr.s_addr = me->us_bindip.s_addr;
	return sizeof(struct sockaddr_in);
}

PRIVATE NONNULL((1)) socklen_t KCALL
udp_getpeername(struct socket *__restrict self,
                USER CHECKED struct sockaddr *addr,
                socklen_t addr_len)
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY) {
	struct udp_socket *me;
	USER CHECKED struct sockaddr_in *in;
	me = (struct udp_socket *)self;
	in = (USER CHECKED struct sockaddr_in *)addr;
	if (!(me->us_state & UDP_SOCKET_STATE_F_HASPEER)) {
		THROW(E_ILLEGAL_BECAUSE_NOT_READY,
		      E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED);
	}
	if likely(addr_len >= offsetafter(struct sockaddr_in, sin_family))
		in->sin_family = AF_INET;
	if likely(addr_len >= offsetafter(struct sockaddr_in, sin_port))
		in->sin_port = me->us_peerport;
	if likely(addr_len >= offsetafter(struct sockaddr_in, sin_addr.s_addr))
		in->sin_addr.s_addr = me->us_peerip.s_addr;
	return sizeof(struct sockaddr_in);
}


PRIVATE NONNULL((1)) void KCALL
udp_bind(struct socket *__restrict self,
         USER CHECKED struct sockaddr const *addr,
         socklen_t addr_len)
		THROWS(E_ILLEGAL_BECAUSE_NOT_READY) {
	struct udp_socket *me;
	USER CHECKED struct sockaddr_in const *in;
	me = (struct udp_socket *)self;
	in = udp_verify_sockaddr(addr, addr_len);

	/* Switch to binding-mode */
	if (atomic_fetchor(&me->us_state, UDP_SOCKET_STATE_F_BINDING) & UDP_SOCKET_STATE_F_BINDING)
		THROW(E_ILLEGAL_BECAUSE_NOT_READY, E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND);
	TRY {
		/* Assign a port and  */
		COMPILER_BARRIER();
		me->us_bindip.s_addr = in->sin_addr.s_addr;
		me->us_bindport      = in->sin_port;
		COMPILER_BARRIER();

		/* TODO: Actually register `me' as the recipient of UDP packets where:
		 *       (PACKET.IP.DST_IP & (-1 << ffs(me->us_bindip.s_addr))) == me->us_bindip.s_addr &&
		 *       PACKET.UDP.DST_PORT == me->us_bindport;
		 *       Where `me->us_bindip.s_addr == 0' causes the ip-check to be skipped,
		 *       as though the mask resulting from `(-1 << ffs(me->us_bindip.s_addr)'
		 *       evaluated to  `0'  (reminder:  ffs(x)  is  FindFirstSet,  such  that
		 *       `(x & (1 << ffs(x))) != 0' so-long as `x != 0') */
	} EXCEPT {
		atomic_and(&me->us_state, ~UDP_SOCKET_STATE_F_BINDING);
		RETHROW();
	}

	/* Indicate that the socket has now been fully bound. */
	atomic_or(&me->us_state, UDP_SOCKET_STATE_F_BOUND);
}


PRIVATE NONNULL((1, 4)) void KCALL
udp_connect(struct socket *__restrict self,
            USER CHECKED struct sockaddr const *addr, socklen_t addr_len,
            /*out*/ struct aio_handle *__restrict aio) {
	struct udp_socket *me;
	USER CHECKED struct sockaddr_in const *in;
	me = (struct udp_socket *)self;
	in = udp_verify_sockaddr(addr, addr_len);

	/* Set the given address as peer address */
	me->us_peerip.s_addr = read_once(&in->sin_addr.s_addr);
	me->us_peerport      = read_once(&in->sin_port);

	/* Mark the socket as having a peer */
	atomic_or(&me->us_state, UDP_SOCKET_STATE_F_HASPEER);

	/* The man page for ip(7) says that connect() will also
	 * cause the socket to become bound to some local port. */
	if unlikely(!(me->us_state & UDP_SOCKET_STATE_F_BOUND))
		udp_autobind(me);

	/* Indicate successful AIO completion. */
	aio_handle_init_noop(aio, AIO_COMPLETION_SUCCESS);
}


PRIVATE NONNULL((1, 2, 8)) void KCALL
udp_sendtov(struct socket *__restrict self,
            struct iov_buffer const *__restrict buf, size_t bufsize,
            /*?..1*/ USER CHECKED struct sockaddr const *addr, socklen_t addr_len,
            struct ancillary_message const *msg_control, syscall_ulong_t msg_flags,
            /*out*/ struct aio_handle *__restrict aio) {
	struct udp_socket *me;
	struct nicdev *dev;
	USER CHECKED struct sockaddr_in const *in;
	REF struct nic_packet *packet;
	(void)msg_flags;

	/* TODO: Support for `msg_flags & MSG_DONTROUTE' (don't use a gateway,
	 *       but only send to directly  reachable peers; this is what  KOS
	 *       currently does for every outbound packet; there is no concept
	 *       of gateways as of yet...) */
	/* TODO: Support for `msg_flags & MSG_MORE' (don't immediately transmit
	 *       the datagram. Wait for more  data for up to 200  milliseconds) */

	me = (struct udp_socket *)self;
	in = udp_verify_sockaddr(addr, addr_len);
	/* TODO: From what I  understand, network cards  should actually  be
	 *       selected  based on `in->sin_addr.s_addr' (i.e. the target's
	 *       IP address). As such, there needs to be a routing table for
	 *       mapping IP addresses to NIC devices, rather than having one
	 *       default adapter for _everything_.
	 *       However, a way to have one particular socket be bound to
	 *       a specific device should still exist, so-as to allow for
	 *       use of `(get|set)sockopt(SOL_SOCKET, SO_BINDTODEVICE)'! */
	dev = udp_getnic(me);

	/* Automatically bind to some local port if not done already! */
	if unlikely(!(me->us_state & UDP_SOCKET_STATE_F_BOUND))
		udp_autobind(me);
	if (msg_control != NULL)
		THROW(E_NOT_IMPLEMENTED_TODO); /* TODO: IP Control message packets (can be used to set IP.TOS, etc.) */
	if unlikely(bufsize > (0xffff - sizeof(struct udphdr)))
		THROW(E_NET_MESSAGE_TOO_LONG, bufsize, 0xffff - sizeof(struct udphdr));

	/* Construct the UDP packet to-be sent. */
	packet = nicdev_newpacketv(dev, buf,
	                               UDP_PACKET_HEADSIZE,
	                               UDP_PACKET_TAILSIZE);
	(void)bufsize;
	assert(packet->np_payloads == bufsize);
	FINALLY_DECREF(packet);
	{
		/* Fill in UDP and IP headers. */
		struct iphdr *ip;
		struct udphdr *udp;
		udp = nic_packet_tallochead(packet, struct udphdr);
		ip  = nic_packet_tallochead(packet, struct iphdr);

		/* Fill in UDP header fields. */
		udp->uh_sport = me->us_bindport;
		udp->uh_dport = read_once(&in->sin_port);
		udp->uh_ulen  = htons((u16)bufsize + sizeof(struct udphdr));
		udp->uh_sum   = htons(0); /* TODO? */

		/* Fill in IP header fields, as required by `ip_senddatagram()' */
		ip->ip_hl         = 5;
		ip->ip_tos        = 0; /* ??? */
		ip->ip_off        = htons(0);
		ip->ip_ttl        = 64;
		ip->ip_p          = IPPROTO_UDP;

		/* TODO: Wait for DHCP/zero-conf/etc. before using our IP */
		ip->ip_src.s_addr = dev->nd_addr.na_ip;
		ip->ip_dst.s_addr = read_once(&in->sin_addr.s_addr);
	}

	/* Actually send the packet over IP */
	ip_senddatagram(dev, packet, aio);
}


PRIVATE NONNULL((1, 2)) size_t KCALL
udp_recvfromv(struct socket *__restrict self,
              struct iov_buffer const *__restrict buf, size_t bufsize,
              /*?..1*/ USER CHECKED struct sockaddr *addr, socklen_t addr_len,
              /*?..1*/ USER CHECKED socklen_t *preq_addr_len,
              /*0..1*/ USER CHECKED u32 *presult_flags,
              struct ancillary_rmessage const *msg_control,
              syscall_ulong_t msg_flags,
              ktime_t abs_timeout)
		THROWS(E_NET_CONNECTION_REFUSED, E_NET_TIMEOUT, E_WOULDBLOCK) {
	struct udp_socket *me;
	me = (struct udp_socket *)self;

	/* TODO: Implement once we've got routing of incoming UDP packets. */
	/* Reminder: When the received packet is larger than the given buffer,
	 *           then  we  must  set  `*presult_flags & MSG_TRUNC'  before
	 *           completion! */
	(void)me;
	(void)buf;
	(void)bufsize;
	(void)addr;
	(void)addr_len;
	(void)preq_addr_len;
	(void)presult_flags;
	(void)msg_control;
	(void)msg_flags;
	(void)abs_timeout;
	THROW(E_NOT_IMPLEMENTED_TODO);
}


/* Socket operators for UDP sockets. */
PUBLIC struct socket_ops udp_socket_ops = {
	.so_family      = AF_INET,
	.so_fini        = &udp_fini,
	.so_pollconnect = NULL, /* TODO: Wait for incoming packets */
	.so_polltest    = NULL, /* TODO: Wait for incoming packets */
	.so_getsockname = &udp_getsockname,
	.so_getpeername = &udp_getpeername,
	.so_bind        = &udp_bind,
	.so_connect     = &udp_connect,
	.so_sendtov     = &udp_sendtov,
	.so_recvfromv   = &udp_recvfromv,
	.so_getsockopt  = NULL, /* TODO: There are _many_ options that are specific to UDP */
	.so_setsockopt  = NULL, /* TODO: There are _many_ options that are specific to UDP */
};


/* Construct a new UDP socket. */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct socket *KCALL
udp_socket_create(void) {
	REF struct udp_socket *result;
	result = (REF struct udp_socket *)kmalloc(sizeof(struct udp_socket), GFP_CALLOC);
	socket_cinit(result, &udp_socket_ops, SOCK_DGRAM, IPPROTO_UDP);
	return result;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_NETWORK_UDP_SOCKET_C */
