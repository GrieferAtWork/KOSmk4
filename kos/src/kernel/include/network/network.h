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
#ifndef GUARD_KERNEL_INCLUDE_NETWORK_NETWORK_H
#define GUARD_KERNEL_INCLUDE_NETWORK_NETWORK_H 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/types.h>
#include <misc/atomic-ref.h>
#include <sched/signal.h>

#include <linux/if_ether.h>

DECL_BEGIN

#ifdef __CC__

#define NET_PEERADDR_HAVE_NONE 0x0000
#define NET_PEERADDR_HAVE_MAC  0x0001 /* [lock(SET_ONCE)] `npa_hwmac' is valid. */
struct net_peeraddr {
	WEAK refcnt_t npa_refcnt;          /* Reference counter. */
	union {
		be32      npa_ip;              /* [const] The peer's IP address */
		u32      _npa_hip;             /* [const] The `npa_ip' field (interpreted in host-endian) */
	};
	u16           npa_flags;           /* Peer address flags (set of `NET_PEERADDR_HAVE_*') */
	u8            npa_hwmac[ETH_ALEN]; /* [valid_if(NET_PEERADDR_HAVE_MAC)] The peer's mac address */
};

#define net_peeraddr_destroy(self) kfree(self)
#define net_peeraddr_malloc() \
	((struct net_peeraddr *)kmalloc(sizeof(struct net_peeraddr), GFP_NORMAL))
DEFINE_REFCOUNT_FUNCTIONS(struct net_peeraddr, npa_refcnt, net_peeraddr_destroy)

struct net_peeraddrs {
	WEAK refcnt_t                                      nps_refcnt; /* Reference counter. */
	size_t                                             nps_count;  /* [const] # of addresses */
	COMPILER_FLEXIBLE_ARRAY(REF struct net_peeraddr *, nps_addrs); /* [const][npa_count] Peer addresses (bsearch-sorted by `npa_ip') */
};

/* Destroy the given network peers information vector. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL net_peeraddrs_destroy)(struct net_peeraddrs *__restrict self);

#define net_peeraddrs_free(self) kfree(self)
#define net_peeraddrs_malloc(count)                                                        \
	((struct net_peeraddrs *)kmalloc(__builtin_offsetof(struct net_peeraddrs, nps_addrs) + \
	                                 (count) * sizeof(struct net_peeraddr),                \
	                                 GFP_NORMAL))
DEFINE_REFCOUNT_FUNCTIONS(struct net_peeraddrs, nps_refcnt, net_peeraddrs_destroy)


/* Lookup a peer address descriptor for `ip' and return its pointer.
 * If no such descriptor exists, return `NULL' instead. */
FUNDEF NOBLOCK WUNUSED ATTR_PURE NONNULL((1)) struct net_peeraddr *
NOTHROW(KCALL net_peeraddrs_lookup_ip)(struct net_peeraddrs *__restrict self, be32 ip);

/* Empty network peer address list. */
DATDEF struct net_peeraddrs net_peeraddrs_empty;

struct network {
	/* Generic network descriptor. */
	ATOMIC_REF(struct net_peeraddrs) n_peers;   /* [1..1] Known network peers, and their addresses. */
	struct sig                       n_addravl; /* Signal broadcast once a peer mac address becomes available. */
};

/* Ensure that a peer entry exists for `ip', returning its descriptor. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct net_peeraddr *KCALL
network_peers_requireip(struct network *__restrict self, be32 ip)
		THROWS(E_BADALLOC);

/* Initialize a given network descriptor */
#define network_init(self)                                    \
	(atomic_ref_init(&(self)->n_peers, &net_peeraddrs_empty), \
	 sig_init(&(self)->n_addravl))
#define network_cinit(self)                                    \
	(atomic_ref_cinit(&(self)->n_peers, &net_peeraddrs_empty), \
	 sig_cinit(&(self)->n_addravl))

/* Finalize a given network descriptor */
#define network_fini(self) \
	(atomic_ref_fini(&(self)->n_peers))


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_NETWORK_NETWORK_H */
