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
#ifndef GUARD_KERNEL_INCLUDE_DEV_NIC_H
#define GUARD_KERNEL_INCLUDE_DEV_NIC_H 1

#include <kernel/compiler.h>

#include <dev/char.h>
#include <kernel/malloc-defs.h>
#include <kernel/malloc.h>
#include <kernel/types.h>
#include <sched/signal.h>

#include <hybrid/__assert.h>

#include <bits/socket.h>
#include <kos/io.h>
#include <linux/if_ether.h>
#include <network/network.h>

DECL_BEGIN

#ifdef __CC__

struct aio_handle;
struct aio_multihandle;
struct nic_device_stat;
struct nic_device;

#ifndef __aio_buffer_entry_defined
#define __aio_buffer_entry_defined 1
struct aio_buffer_entry {
	USER CHECKED void *ab_base; /* [?..ab_size] Virtual base address of the buffer. */
	size_t             ab_size; /* Buffer size of `ab_base' (in bytes) */
};
#endif /* !__aio_buffer_entry_defined */

struct nic_packet {
	/* NetworkInterfaceCard buffer for outgoing packets.
	 * This buffer is designed to have a reference stored
	 * within some given `struct aio_handle'
	 * NIC packet data should be enumerated as:
	 * #1: np_head...np_headend
	 * #2: np_payloadv[0..np_payloadc]
	 * #3: np_tail...np_tailend */
	WEAK refcnt_t     np_refcnt;   /* Reference counter. */
	byte_t           *np_head;     /* [1..1] Start of headers (grows up) */
	union {
		byte_t       *np_headend;  /* [1..1][const] End of headers */
		byte_t       *np_tail;     /* [1..1][const] Start of tail data. */
	};
	byte_t           *np_tailend;  /* [1..1] End of tail data (grows down) */
	/* TODO: Add a field `REF struct vm *np_payldvm; // [0..1][lock(WRITE_ONCE)]'
	 *       that contains a non-NULL pointer when the VM containing
	 *       the memory regions described by payload entires differs
	 *       from the current VM of the calling thread.
	 * -> Right now, a lot of VM context switching happens as part of
	 *    outbound packet routing, and we could drastically cut down
	 *    on this (especially in cases where the NIC driver back-end
	 *    doesn't even need to access memory directly, but can use
	 *    some sort of DMA access), by having drivers deal with the
	 *    task of selecting the proper VM for accessing the packet
	 *    payload. (This could especially improve performance for
	 *    packets that exist _only_ in kernel-space, such that no VM
	 *    switch would be necessary at all when `np_payloads == 0',
	 *    indicative of the packet only consisting of header+tail
	 *    data, as would be the case for packets created by the kernel
	 *    itself (such as ARP packets, or other packets send by protocols
	 *    directly implemented within the kernel)) */
	size_t            np_payloads; /* [const] Total payload size (in bytes) */
	size_t            np_payloadc; /* [const] # of payload vectors. */
	COMPILER_FLEXIBLE_ARRAY(struct aio_buffer_entry, np_payloadv); /* [const][np_payloadc] Specified payloads */
};

/* Return the amount of free head/tail memory */
#define nic_packet_headfree(self) (size_t)((self)->np_head - (byte_t *)&(self)->np_payloadv[(self)->np_payloadc])
#define nic_packet_tailfree(self) (size_t)(((byte_t *)(self) + kmalloc_usable_size(self)) - (self)->np_tailend)

/* Allocate space for headers/footers.
 * NOTE: The caller is responsible to ensure that the packet was originally
 *       allocated with sufficient space for all headers and footers. */
#define nic_packet_allochead(self, num_bytes)                   \
	(__hybrid_assertf((num_bytes) <= nic_packet_headfree(self), \
	                  "Insufficient head space (%Iu > %Iu)",    \
	                  (num_bytes), nic_packet_headfree(self)),  \
	 (self)->np_head -= (num_bytes))
#define nic_packet_alloctail(self, num_bytes)                   \
	(__hybrid_assertf((num_bytes) <= nic_packet_tailfree(self), \
	                  "Insufficient tail space (%Iu > %Iu)",    \
	                  (num_bytes), nic_packet_tailfree(self)),  \
	 ((self)->np_tailend += (num_bytes)) - (num_bytes))
#define nic_packet_tallochead(self, T) ((T *)nic_packet_allochead(self, sizeof(T)))
#define nic_packet_talloctail(self, T) ((T *)nic_packet_alloctail(self, sizeof(T)))


/* Return the size of some part of a given NIC packet. */
#define nic_packet_headsize(self)     (size_t)((self)->np_headend - (self)->np_head)
#define nic_packet_tailsize(self)     (size_t)((self)->np_tailend - (self)->np_tail)
#define nic_packet_headtailsize(self) (size_t)((self)->np_tailend - (self)->np_head)

/* Return the total size of a give NIC packet. */
#define nic_packet_size(self) \
	(nic_packet_headtailsize(self) + (self)->np_payloads)

/* Invoke `cb(USER CHECKED void *base, size_t num_bytes)' (where `num_bytes' may be 0)
 * over each of the different parts of the given packet.
 * TODO: Get rid of this macro. - Instead, add a helper for enumerating
 *       I/O segments containing data for packet payload parts. */
#define nic_packet_print(self, cb)                                                    \
	do {                                                                              \
		size_t _npp_i;                                                                \
		cb((self)->np_head, nic_packet_headsize(self));                               \
		for (_npp_i = 0; _npp_i < (self)->np_payloadc; ++_npp_i) {                    \
			cb(self->np_payloadv[_npp_i].ab_base, self->np_payloadv[_npp_i].ab_size); \
		}                                                                             \
		cb((self)->np_tail, nic_packet_tailsize(self));                               \
	} __WHILE0

/* Destroy a given network packet. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL nic_packet_destroy)(struct nic_packet *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct nic_packet, np_refcnt, nic_packet_destroy)


struct nic_device_ops {
	/* [1..1] Send a packet.
	 * WARNING: Any NIC packet can only ever be sent _once_ at the same time!
	 *          Don't call this function multiple times for the same packet
	 *          before a previous call has indicated completion through `aio'!
	 * WARNING: The given `packet' must have been allocated via `nic_device_newpacket()'
	 *          for the _same_ NIC device as `self'. Don't go mix-and-matching packets
	 *          from different NIC devices, as packet buffer may get allocated with
	 *          differing storage .
	 * However, you are allowed (and encouraged) to drop your own reference to
	 * `packet' after calling this function. If the implementation requires its
	 * own reference to `packet' for the purpose of enqueuing a pending transmit
	 * operation, then it will acquire its own reference! */
	void (KCALL *nd_send)(struct nic_device *__restrict self,
	                      struct nic_packet *__restrict packet,
	                      /*out*/ struct aio_handle *__restrict aio);
	/* [1..1] Set the value of `self->nd_flags' to `new_flags',
	 *        using ATOMIC_CMPXCH() semantics with `old_flags'
	 * @return: true:  Flags were successfully updated
	 * @return: false: `old_flags' didn't match `self->nd_flags'
	 * This is mainly used to turn on the NIC on/off using `IFF_UP' */
	bool (KCALL *nd_setflags)(struct nic_device *__restrict self,
	                          uintptr_t old_flags, uintptr_t new_flags);
};

struct nic_device_stat {
	WEAK size_t nds_rx_packets;       /* # of packets received. */
	WEAK size_t nds_tx_packets;       /* # of packets transmitted. */
	WEAK size_t nds_rx_bytes;         /* # of bytes received. */
	WEAK size_t nds_tx_bytes;         /* # of bytes transmitted. */
	WEAK size_t nds_rx_dropped;       /* # of dropped incoming packets. */
	WEAK size_t nds_rx_frame_errors;  /* # of receive frame errors. */
	WEAK size_t nds_rx_crc_errors;    /* # of receive crc errors. */
	WEAK size_t nds_rx_miss_errors;   /* # of receive missed errors. */
	WEAK size_t nds_rx_length_errors; /* # of receive length errors. */
};

#define NIC_ADDR_HAVE_NONE 0x0000
#define NIC_ADDR_HAVE_IP   0x0001 /* `na_ip' has been configured. */
struct nic_addresses {
	u8   na_hwmac[ETH_ALEN]; /* [const] The device's a hardware (mac) address */
	u16  na_flags;           /* Flags used to describe configured addresses (set of `NIC_ADDR_HAVE_*') */
	be32 na_ip;              /* [valid_if(NIC_ADDR_HAVE_IP)] IP Address.
	                          * NOTE: `:nd_net.n_addravl' is broadcast when this becomes available! */
};

struct nic_device
#ifdef __cplusplus
    : character_device
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct character_device nd_base;    /* The underlying character device */
#endif /* !__cplusplus */
	struct nic_device_ops   nd_ops;     /* Device operators. */
	WEAK uintptr_t          nd_ifflags; /* [lock(INTERN)] Netword interface flags (set of `IFF_*') */
	struct nic_device_stat  nd_stat;    /* Usage statistics */
	gfp_t                   nd_hdgfp;   /* [const] Additional GFP flags for packet header/tail buffers.
	                                     * This is mainly useful in case the driver can be written more
	                                     * efficiently if header/tail memory is allocated as `GFP_LOCKED'. */
	struct nic_addresses    nd_addr;    /* Network addresses. */
	struct network          nd_net;     /* A description of the attached network. */
};


/* Allocate a new NIC packet which may be used to send the given payload.
 * Reserve sufficient space for headers and footers of up to the specified
 * sizes to be included alongside the payload. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct nic_packet *KCALL
nic_device_newpacket(struct nic_device const *__restrict self,
                     USER CHECKED void const *payload, size_t payload_size,
                     size_t max_head_size, size_t max_tail_size)
		THROWS(E_BADALLOC);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct nic_packet *KCALL
nic_device_newpacketv(struct nic_device const *__restrict self,
                      struct aio_buffer const *__restrict payload,
                      size_t max_head_size, size_t max_tail_size)
		THROWS(E_BADALLOC);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct nic_packet *KCALL
nic_device_newpacketh(struct nic_device const *__restrict self,
                      size_t max_head_size, size_t max_tail_size)
		THROWS(E_BADALLOC);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct nic_packet *KCALL
nic_device_newpacketk_impl(struct nic_device const *__restrict self,
                           size_t buffer_size)
		THROWS(E_BADALLOC);
LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct nic_packet *KCALL
nic_device_newpacketk(struct nic_device const *__restrict self,
                      /*out*/ void **__restrict pbuffer,
                      size_t buffer_size)
		THROWS(E_BADALLOC) {
	REF struct nic_packet *result;
	result   = nic_device_newpacketk_impl(self, buffer_size);
	*pbuffer = result->np_head;
	return result;
}

/* Initialize a given NIC device. */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL nic_device_cinit)(struct nic_device *__restrict self,
                                struct nic_device_ops const *__restrict ops);

/* Default finalizer for NIC devices.
 * NOTE: Must be called by drivers when `cd_type.ct_fini' gets overwritten. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL nic_device_fini)(struct character_device *__restrict self);

/* Check if a given character device is a NIC. */
#define character_device_isanic(self)                    \
	((self)->cd_heapsize >= sizeof(struct nic_device) && \
	 (self)->cd_type.ct_write == &nic_device_write)

/* Default write-operator for NIC devices. */
FUNDEF NONNULL((1)) size_t KCALL
nic_device_write(struct character_device *__restrict self,
                 USER CHECKED void const *src,
                 size_t num_bytes, iomode_t mode) THROWS(...);

/* Send a given packet */
LOCAL NONNULL((1, 2, 3)) void KCALL
nic_device_send(struct nic_device *__restrict self,
                struct nic_packet *__restrict packet,
                /*out*/ struct aio_handle *__restrict aio) {
	(*self->nd_ops.nd_send)(self, packet, aio);
}

/* Same as `nic_device_send()', however handle _all_ exceptions as AIO-failures
 * WARNING: This function may still clobber exception pointers! */
FUNDEF NONNULL((1, 2, 3)) void
NOTHROW(KCALL nic_device_send_nx)(struct nic_device *__restrict self,
                                  struct nic_packet *__restrict packet,
                                  /*out*/ struct aio_handle *__restrict aio);

/* Send the given packet in the background (s.a. `aio_handle_async_alloc()')
 * NOTE: Transmit errors get logged, but are silently discarded. */
FUNDEF NONNULL((1, 2)) void KCALL
nic_device_send_background(struct nic_device *__restrict self,
                           struct nic_packet *__restrict packet);

/* Same as `nic_device_send_background()', however handle _all_ exceptions as AIO-failures
 * WARNING: This function may still clobber exception pointers! */
FUNDEF NONNULL((1, 2)) void
NOTHROW(KCALL nic_device_send_background_nx)(struct nic_device *__restrict self,
                                             struct nic_packet *__restrict packet);


/* Routable packet buffer. */
struct nic_rpacket {
	size_t                          rp_size;  /* Max packet size (in bytes) */
	COMPILER_FLEXIBLE_ARRAY(byte_t, rp_data); /* [rp_size] Packet data buffer. */
};

/* Allocate a buffer for a routable NIC packet for use with `nic_device_routepacket()'
 * @param: max_packet_size: The max packet size that the returned buffer must be able to hold.
 *                          The guaranty here is that: `return->rp_size >= max_packet_size'
 *                          NOTE: Must be at least `ETH_ZLEN' */
FUNDEF ATTR_RETNONNULL struct nic_rpacket *KCALL
nic_rpacket_alloc(size_t max_packet_size) THROWS(E_BADALLOC);

/* Free a routable NIC packet. */
FUNDEF NOBLOCK void NOTHROW(KCALL nic_rpacket_free)(struct nic_rpacket *__restrict self);

/* Inherit a routable NIC packet and route it.
 * Routing may either be done synchronously (i.e. before this function returns),
 * or asynchronously (i.e. at some future point in time by some other thread)
 * If the caller _needs_ routing to be performed immediately, they should instead
 * make use of `eth_routepacket()', followed by `nic_rpacket_free()'
 * @param: real_packet_size: The actual used packet size (`<= packet->rp_size')
 *                     NOTE: The caller must ensure that this is at least `ETH_ZLEN' */
FUNDEF NOBLOCK NONNULL((1, 2)) void KCALL
nic_device_routepacket(struct nic_device *__restrict self,
                       /*inherit(always)*/ struct nic_rpacket *__restrict packet,
                       size_t real_packet_size);


/* Get/set the the default NIC device. */
FUNDEF WUNUSED REF struct nic_device *
NOTHROW(KCALL nic_device_getdefault)(void);
FUNDEF NONNULL((1)) void
NOTHROW(KCALL nic_device_setdefault)(struct nic_device *__restrict dev);


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_DEV_NIC_H */
