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
#include <kernel/types.h>

#include <bits/socket.h>
#include <kos/io.h>

DECL_BEGIN

#ifdef __CC__

struct aio_handle;
struct nic_device_stat;
struct nic_device;

struct nic_packet {
	USER CHECKED void *np_head;   /* [0..np_headsz] Packet head */
	size_t             np_headsz; /* Packet head size */
	struct nic_packet *np_inner;  /* [0..1] Wrapped, inner packet. */
	USER CHECKED void *np_tail;   /* [0..np_tailsz] Packet tail */
	size_t             np_tailsz; /* Packet tail size */
	size_t             np_total;  /* [== np_headsz + np_tailsz + (np_inner ? np_inner->np_total : 0)]
	                               * Total packet size */
};


struct nic_device_ops {
	/* [1..1] Send a packet. */
	void (KCALL *nd_send)(struct nic_device *__restrict self,
	                      struct nic_packet const *__restrict packet,
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
	WEAK size_t nds_rx_packets; /* # of packets received. */
	WEAK size_t nds_tx_packets; /* # of packets transmitted. */
	WEAK size_t nds_rx_bytes;   /* # of bytes received. */
	WEAK size_t nds_tx_bytes;   /* # of bytes transmitted. */
	WEAK size_t nds_rx_dropped; /* # of dropped incoming packets. */
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
};

#define nic_device_cinit(self, ops)     \
	((self)->nd_ops           = *(ops), \
	 (self)->cd_type.ct_write = &nic_device_write)

#define nic_device_fini(self) \
	(void)0

/* Check if a given character device is a NIC. */
#define character_device_isanic(self)                    \
	((self)->cd_heapsize >= sizeof(struct nic_device) && \
	 (self)->cd_type.ct_write == &nic_device_write)

/* Default write-operator for NIC devices. */
FUNDEF NONNULL((1)) size_t KCALL
nic_device_write(struct character_device *__restrict self,
                 USER CHECKED void const *src,
                 size_t num_bytes, iomode_t mode) THROWS(...);


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_DEV_NIC_H */
