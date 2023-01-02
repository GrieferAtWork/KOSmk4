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
#ifndef GUARD_KERNEL_INCLUDE_NETWORK_NETWORK_H
#define GUARD_KERNEL_INCLUDE_NETWORK_NETWORK_H 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/types.h>
#include <sched/sig.h>

#include <hybrid/__assert.h>
#include <hybrid/sched/atomic-lock.h>

#include <kos/aref.h>
#include <linux/if_ether.h>

DECL_BEGIN

#ifdef __CC__

struct nicdev;

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
	WEAK u16      npa_ipgramid;        /* Next IP datagram ID */
};

#define net_peeraddr_destroy(self) kfree(self)
#define net_peeraddr_malloc() \
	((struct net_peeraddr *)kmalloc(sizeof(struct net_peeraddr), GFP_CALLOC))
DEFINE_REFCNT_FUNCTIONS(struct net_peeraddr, npa_refcnt, net_peeraddr_destroy)

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
DEFINE_REFCNT_FUNCTIONS(struct net_peeraddrs, nps_refcnt, net_peeraddrs_destroy)


/* Lookup a peer address descriptor for `ip' and return its pointer.
 * If   no   such   descriptor   exists,   return   `NULL'  instead. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) struct net_peeraddr *
NOTHROW(KCALL net_peeraddrs_lookup_ip)(struct net_peeraddrs *__restrict self, be32 ip);

/* Empty network peer address list. */
DATDEF struct net_peeraddrs net_peeraddrs_empty;

struct ip_datagram;
struct network_ip_datagrams {
	struct atomic_lock  nid_lock;  /* Lock for accessing the datagram vector. */
	size_t              nid_size;  /* Used vector length. */
	size_t              nid_alloc; /* Allocated vector length. */
	/* TODO: Free up datagrams that have timed out as part of system_clearcache()! */
	struct ip_datagram *nid_list;  /* [1..1][lock(nid_lock)][0..nid_size|alloc(nid_alloc)]
	                                * [SORTED][lock(nid_lock)][owned] Vector of incomplete datagrams */
};

/* Helper macros for `struct network_ip_datagrams::nid_lock' */
#define _network_ip_datagrams_reap(self)      (void)0
#define network_ip_datagrams_reap(self)       (void)0
#define network_ip_datagrams_mustreap(self)   0
#define network_ip_datagrams_tryacquire(self) atomic_lock_tryacquire(&(self)->nid_lock)
#define network_ip_datagrams_acquire(self)    atomic_lock_acquire(&(self)->nid_lock)
#define network_ip_datagrams_acquire_nx(self) atomic_lock_acquire_nx(&(self)->nid_lock)
#define _network_ip_datagrams_release(self)   atomic_lock_release(&(self)->nid_lock)
#define network_ip_datagrams_release(self)    (atomic_lock_release(&(self)->nid_lock), network_ip_datagrams_reap(self))
#define network_ip_datagrams_acquired(self)   atomic_lock_acquired(&(self)->nid_lock)
#define network_ip_datagrams_available(self)  atomic_lock_available(&(self)->nid_lock)
#define network_ip_datagrams_waitfor(self)    atomic_lock_waitfor(&(self)->nid_lock)
#define network_ip_datagrams_waitfor_nx(self) atomic_lock_waitfor_nx(&(self)->nid_lock)

#define network_ip_datagrams_init(self)   \
	(atomic_lock_init(&(self)->nid_lock), \
	 (self)->nid_size  = 0,               \
	 (self)->nid_alloc = 0,               \
	 (self)->nid_list  = __NULLPTR)
#define network_ip_datagrams_cinit(self)      \
	(atomic_lock_cinit(&(self)->nid_lock),    \
	 __hybrid_assert((self)->nid_size == 0),  \
	 __hybrid_assert((self)->nid_alloc == 0), \
	 __hybrid_assert((self)->nid_list == __NULLPTR))

/* Finalize a given network IP datagrams descriptor. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL network_ip_datagrams_fini)(struct network_ip_datagrams *__restrict self);


#ifndef __net_peeraddrs_arref_defined
#define __net_peeraddrs_arref_defined
ARREF(net_peeraddrs_arref, net_peeraddrs);
#endif /* !__net_peeraddrs_arref_defined */

struct network {
	/* Generic network descriptor. */
	struct net_peeraddrs_arref  n_peers;   /* [1..1] Known network peers, and their addresses. */
	struct sig                  n_addravl; /* Signal broadcast once a peer mac address becomes available. */
	struct network_ip_datagrams n_ipgrams; /* IP datagrams. */
	u16                         n_ipsize;  /* Max IP fragment size (default initialize to `IP_MSS'; must be divisible by `8'). */
};

/* Ensure that a peer entry exists for `ip', returning its descriptor. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct net_peeraddr *KCALL
nic_device_requireip(struct nicdev *__restrict self, be32 ip)
		THROWS(E_BADALLOC);

/* Initialize a given network descriptor */
#define _network_init_common(self) \
	((self)->n_ipsize = 576 /*IP_MSS*/)
#define network_init(self)                               \
	(incref(&net_peeraddrs_empty),                       \
	 arref_init(&(self)->n_peers, &net_peeraddrs_empty), \
	 sig_init(&(self)->n_addravl),                       \
	 network_ip_datagrams_init(&(self)->n_ipgrams),      \
	 _network_init_common(self))
#define network_cinit(self)                               \
	(incref(&net_peeraddrs_empty),                        \
	 arref_cinit(&(self)->n_peers, &net_peeraddrs_empty), \
	 sig_cinit(&(self)->n_addravl),                       \
	 network_ip_datagrams_cinit(&(self)->n_ipgrams),      \
	 _network_init_common(self))

/* Finalize a given network descriptor */
#define network_fini(self)         \
	(arref_fini(&(self)->n_peers), \
	 network_ip_datagrams_fini(&(self)->n_ipgrams))

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_NETWORK_NETWORK_H */
