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
#ifndef GUARD_KERNEL_SRC_DEV_NIC_C
#define GUARD_KERNEL_SRC_DEV_NIC_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/nic.h>
#include <kernel/aio.h>
#include <kernel/heap.h>
#include <kernel/iovec.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <kernel/types.h>

#include <linux/if_ether.h>
#include <netinet/in.h>
#include <network/ethernet.h>
#include <network/network.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#define nic_packet_alloc(nic, num_payloads, ht_size)                                      \
	((REF struct nic_packet *)kmalloc(offsetof(struct nic_packet, np_payloadv) +          \
	                                  ((num_payloads) * sizeof(struct aio_buffer_entry)) + \
	                                  (ht_size),                                          \
	                                  (nic)->nd_hdgfp))

/* Allocate a new NIC packet which may be used to send the given payload.
 * Reserve sufficient space for headers and footers of up to the specified
 * sizes to be included alongside the payload. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct nic_packet *KCALL
nic_device_newpacket(struct nic_device const *__restrict self,
                     USER CHECKED void const *payload, size_t payload_size,
                     size_t max_head_size, size_t max_tail_size)
		THROWS(E_BADALLOC) {
	REF struct nic_packet *result;
	result = nic_packet_alloc(self, 1, max_head_size + max_tail_size);
	result->np_refcnt              = 1;
	result->np_payloads            = payload_size;
	result->np_payloadc            = 1;
	result->np_payloadv[0].ab_base = (byte_t *)payload;
	result->np_payloadv[0].ab_size = payload_size;
	result->np_tail    = (byte_t *)&result->np_payloadv[1] + max_head_size;
	result->np_head    = result->np_tail;
	result->np_tailend = result->np_tail;
	return result;
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct nic_packet *KCALL
nic_device_newpacketv(struct nic_device const *__restrict self,
                      struct aio_buffer const *__restrict payload,
                      size_t max_head_size, size_t max_tail_size)
		THROWS(E_BADALLOC) {
	REF struct nic_packet *result;
	size_t i, total;
	result = nic_packet_alloc(self, payload->ab_entc,
	                          max_head_size + max_tail_size);
	result->np_refcnt   = 1;
	result->np_payloadc = payload->ab_entc;
	total = payload->ab_head.ab_size;
	result->np_payloadv[0].ab_base = payload->ab_head.ab_base;
	result->np_payloadv[0].ab_size = total;
	for (i = 1; i < result->np_payloadc; ++i) {
		size_t temp;
		temp = payload->ab_entv[i].ab_size;
		result->np_payloadv[i].ab_base = payload->ab_entv[i].ab_base;
		result->np_payloadv[i].ab_size = temp;
		total += temp;
	}
	result->np_payloads = total;
	result->np_tail     = (byte_t *)&result->np_payloadv[result->np_payloadc] + max_head_size;
	result->np_head     = result->np_tail;
	result->np_tailend  = result->np_tail;
	return result;
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct nic_packet *KCALL
nic_device_newpacketh(struct nic_device const *__restrict self,
                      size_t max_head_size, size_t max_tail_size)
		THROWS(E_BADALLOC) {
	REF struct nic_packet *result;
	result = nic_packet_alloc(self, 0, max_head_size + max_tail_size);
	result->np_refcnt   = 1;
	result->np_payloadc = 0;
	result->np_payloads = 0;
	result->np_tail     = (byte_t *)result->np_payloadv + max_head_size;
	result->np_head     = result->np_tail;
	result->np_tailend  = result->np_tail;
	return result;
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct nic_packet *KCALL
nic_device_newpacketk_impl(struct nic_device const *__restrict self,
                           size_t buffer_size)
		THROWS(E_BADALLOC) {
	REF struct nic_packet *result;
	result = nic_packet_alloc(self, 0, buffer_size);
	result->np_refcnt   = 1;
	result->np_payloadc = 0;
	result->np_payloads = 0;
	result->np_tail     = (byte_t *)result->np_payloadv + buffer_size;
	result->np_head     = (byte_t *)result->np_payloadv;
	result->np_tailend  = result->np_tail;
	return result;
}


PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL nic_packet_destroy)(struct nic_packet *__restrict self) {
	kfree(self);
}




/* Initialize a given NIC device. */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL nic_device_cinit)(struct nic_device *__restrict self,
                                struct nic_device_ops const *__restrict ops) {
	assert(ops);
	assert(ops->nd_send);
	assert(ops->nd_setflags);
	network_cinit(&self->nd_net);
	memcpy(&self->nd_ops, ops, sizeof(struct nic_device_ops));
	self->cd_type.ct_write = &nic_device_write;
	self->cd_type.ct_fini  = &nic_device_fini;
	/* Default-configure the nic's IP address to broadcast, so
	 * we can already send/receive IP packets before acquiring
	 * a proper IP address from DHCP or some other source. */
	self->nd_addr.na_ip = htonl(INADDR_BROADCAST);
}

/* Default finalizer for NIC devices.
 * NOTE: Must be called by drivers when `cd_type.ct_fini' gets overwritten. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL nic_device_fini)(struct character_device *__restrict self) {
	struct nic_device *me;
	me = (struct nic_device *)self,
	network_fini(&me->nd_net);
}



/* Same as `nic_device_send()', however handle _all_ exceptions as AIO-failures
 * WARNING: This function may still clobber exception pointers! */
PUBLIC NONNULL((1, 2, 3)) void
NOTHROW(KCALL nic_device_send_nx)(struct nic_device *__restrict self,
                                  struct nic_packet *__restrict packet,
                                  /*out*/ struct aio_handle *__restrict aio) {
	TRY {
		nic_device_send(self, packet, aio);
	} EXCEPT {
		aio_handle_init_noop(aio, AIO_COMPLETION_FAILURE);
	}
}

/* Send the given packet in the background (s.a. `aio_handle_async_alloc()')
 * NOTE: Transmit errors get logged, but are silently discarded. */
PUBLIC NONNULL((1, 2)) void KCALL
nic_device_send_background(struct nic_device *__restrict self,
                           struct nic_packet *__restrict packet) {
	struct aio_handle *aio;
	aio = aio_handle_async_alloc();
	TRY {
		/* NOTE: `aio' is inherited on success. */
		nic_device_send(self, packet, aio);
	} EXCEPT {
		aio_handle_async_free(aio);
		RETHROW();
	}
}


/* Default write-operator for NIC devices. */
PUBLIC NONNULL((1)) size_t KCALL
nic_device_write(struct character_device *__restrict self,
                 USER CHECKED void const *src,
                 size_t num_bytes, iomode_t UNUSED(mode))
		THROWS(...) {
	REF struct nic_packet *packet;
	struct nic_device *me;
	struct aio_handle_generic aio;
	me = (struct nic_device *)self;
	aio_handle_generic_init(&aio);

	/* Send a simple packet. */
	packet = nic_device_newpacket(me, src, num_bytes, 0, 0);
	{
		FINALLY_DECREF_UNLIKELY(packet);
		nic_device_send(me, packet, &aio);
	}

	/* Wait for the send to finish. */
	TRY {
		aio_handle_generic_waitfor_tms(&aio);
		aio_handle_generic_checkerror(&aio);
	} EXCEPT {
		aio_handle_generic_fini(&aio);
		RETHROW();
	}
	aio_handle_generic_fini(&aio);
	return num_bytes;
}



/* Allocate a buffer for a routable NIC packet for use with `nic_device_routepacket()'
 * @param: max_packet_size: The max packet size that the returned buffer must be able to hold.
 *                          The guaranty here is that: `return->rp_size >= max_packet_size'
 *                          NOTE: Must be at least `ETH_ZLEN' */
PUBLIC ATTR_RETNONNULL struct nic_rpacket *KCALL
nic_rpacket_alloc(size_t max_packet_size) THROWS(E_BADALLOC) {
	struct nic_rpacket *result;
	struct heapptr resptr;
	assertf(max_packet_size >= ETH_ZLEN,
	        "Packets must always have a max size of at least "
	        "ETH_ZLEN(%" PRIuSIZ ") bytes (but %" PRIuSIZ " is less than that)",
	        (size_t)ETH_ZLEN, max_packet_size);
	/* XXX: Pre-cache a certain number of specifically-sized packets. */
	resptr = heap_alloc(&kernel_default_heap,
	                    offsetof(struct nic_rpacket, rp_data) +
	                    max_packet_size,
	                    GFP_NORMAL);
	result = (struct nic_rpacket *)resptr.hp_ptr;
	result->rp_size = resptr.hp_siz;
	return result;
}

/* Free a routable NIC packet. */
PUBLIC NOBLOCK void
NOTHROW(KCALL nic_rpacket_free)(struct nic_rpacket *__restrict self) {
	/* XXX: Pre-cache a certain number of specifically-sized packets. */
	heap_free(&kernel_default_heap, self, self->rp_size, GFP_NORMAL);
}

/* Inherit a routable NIC packet and route it.
 * Routing may either be done synchronously (i.e. before this function returns),
 * or asynchronously (i.e. at some future point in time by some other thread)
 * If the caller _needs_ routing to be performed immediately, they should instead
 * make use of `eth_routepacket()', followed by `nic_rpacket_free()'
 * @param: real_packet_size: The actual used packet size (`<= packet->rp_size')
 *                     NOTE: The caller must ensure that this is at least `ETH_ZLEN' */
PUBLIC NOBLOCK NONNULL((1, 2)) void KCALL
nic_device_routepacket(struct nic_device *__restrict self,
                       /*inherit(always)*/ struct nic_rpacket *__restrict packet,
                       size_t real_packet_size) {
	assert(real_packet_size <= packet->rp_size);
	assert(real_packet_size >= ETH_ZLEN);
	/* XXX: Option to have the routing be done asynchronously! */
	TRY {
		eth_routepacket(self, packet->rp_data, real_packet_size);
	} EXCEPT {
		nic_rpacket_free(packet); /* Always inherit `packet' */
		RETHROW();
	}
	nic_rpacket_free(packet);
}



/* [0..1] The default NIC device. */
PRIVATE XATOMIC_REF(struct nic_device) default_nic_device = XATOMIC_REF_INIT(NULL);

/* Get/set the the default NIC device. */
PUBLIC WUNUSED REF struct nic_device *
NOTHROW(KCALL nic_device_getdefault)(void) {
	return default_nic_device.get();
}

PUBLIC NONNULL((1)) void
NOTHROW(KCALL nic_device_setdefault)(struct nic_device *__restrict dev) {
	REF struct nic_device *old_device;
	old_device = default_nic_device.exchange(dev);
	xdecref(old_device);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_NIC_C */
