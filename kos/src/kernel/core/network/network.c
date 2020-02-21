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
#ifndef GUARD_KERNEL_SRC_NETWORK_NETWORK_C
#define GUARD_KERNEL_SRC_NETWORK_NETWORK_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>
#include <kernel/except.h>

#include <dev/nic.h>

#include <hybrid/sequence/bsearch.h>

#include <network/network.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

/* Empty network peer address list. */
PUBLIC struct net_peeraddrs net_peeraddrs_empty = {
	/* .npa_refcnt = */ 1, /* +1: net_peeraddrs_empty */
	/* .npa_count  = */ 0
};


/* Lookup a peer address descriptor for `ip' and return its pointer.
 * If no such descriptor exists, return `NULL' instead. */
PUBLIC NOBLOCK WUNUSED ATTR_PURE NONNULL((1)) struct net_peeraddr *
NOTHROW(KCALL net_peeraddrs_lookup_ip)(struct net_peeraddrs *__restrict self, be32 ip) {
	size_t index;
	BSEARCH(index, self->nps_addrs, self->nps_count, ->_npa_hip, (u32)ip) {
		return self->nps_addrs[index];
	}
	return NULL;
}

/* Destroy the given network peers information vector. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL net_peeraddrs_destroy)(struct net_peeraddrs *__restrict self) {
	size_t i;
	for (i = 0; i < self->nps_count; ++i)
		decref_unlikely(self->nps_addrs[i]);
	net_peeraddrs_free(self);
}



/* Ensure that a peer entry exists for `ip', returning its descriptor. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct net_peeraddr *KCALL
network_peers_requireip(struct network *__restrict self, be32 ip)
		THROWS(E_BADALLOC) {
	size_t i, lo, hi;
	REF struct net_peeraddr *result;
	REF struct net_peeraddrs *old_peers;
	REF struct net_peeraddrs *new_peers;
again:
	old_peers = self->n_peers.get();
	BSEARCH_EX(i, lo, hi, old_peers->nps_addrs, old_peers->nps_count, ->_npa_hip, (u32)ip) {
		/* Already exists. */
		result = incref(old_peers->nps_addrs[i]);
		decref_unlikely(old_peers);
		return result;
	}
	/* Allocate a new peer address vector. */
	assert(lo == hi);
	new_peers = net_peeraddrs_malloc(old_peers->nps_count + 1);
	TRY {
		result = net_peeraddr_malloc();
	} EXCEPT {
		net_peeraddrs_free(new_peers);
		RETHROW();
	}
	new_peers->nps_refcnt = 1;
	new_peers->nps_count  = old_peers->nps_count + 1;
	memcpy(new_peers->nps_addrs, old_peers->nps_addrs, lo, sizeof(REF struct net_peeraddr *));
	memcpy(new_peers->nps_addrs + lo + 1, old_peers->nps_addrs + lo,
	       old_peers->nps_count - lo, sizeof(REF struct net_peeraddr *));
	/* Acquire references to existing peer descriptors. */
	for (i = 0; i < old_peers->nps_count; ++i)
		incref(old_peers->nps_addrs[i]);
	decref_unlikely(old_peers);

	result->npa_refcnt = 2; /* +1: result, +1: new_peers->nps_addrs[lo] */
	result->npa_ip     = ip;
	result->npa_flags  = NET_PEERADDR_HAVE_NONE;
	new_peers->nps_addrs[lo] = result; /* Inherit reference */
	/* Try to install the new peers vector. */
	if unlikely(!self->n_peers.cmpxch_inherit_new(old_peers, new_peers)) {
		assert(!wasdestroyed(new_peers));
		assert(!isshared(new_peers));
		assert(!wasdestroyed(new_peers));
		assert(isshared(new_peers));
		destroy(new_peers);
		assert(!wasdestroyed(result));
		assert(!isshared(result));
		destroy(result);
		goto again;
	}
	return result; /* Inherit reference */
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_NETWORK_NETWORK_C */
