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
#ifndef GUARD_MODNE2K_NE2K_H
#define GUARD_MODNE2K_NE2K_H 1

#include <kernel/compiler.h>

#include <dev/nic.h>
#include <kernel/types.h>
#include <sched/rwlock.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <hybrid/sync/atomic-rwlock.h>
#include <sched/semaphore.h>

#include <kos/io/ne2k.h>
#include <linux/if_ether.h>
#include <sys/io.h>

DECL_BEGIN

typedef struct: nic_device {
	struct pci_device   *nd_pcidev;        /* [1..1][const] The associated PCI device. */
	struct rwlock        nd_iolock;        /* Lock for configuring I/O (TODO: Remove me & use async workers) */
	struct semaphore     nd_txisr;         /* Transmit-complete interrupt counter. (TODO: Remove me & use async workers) */
	port_t               nd_iobase;        /* [const] I/O base address. */
	u8                   nd_mac[ETH_ALEN]; /* [const] The original mac address */
	/* NOTE: Ne2k pages consist of 256 bytes! */
	u8                   nd_tx_start;      /* [const] Transmit buffer start page */
	u8                   nd_tx_end;        /* [const] Transmit buffer end page */
	u8                   nd_rx_start;      /* [const] Receive buffer start page */
	u8                   nd_rx_end;        /* [const] Receive buffer end page */
	u8                   nd_rx_nxt;        /* [const] Next unread incoming packet. */
} Ne2kDevice;

/* Reset the network card via `NE_RESET()'. */
INTDEF void KCALL Ne2k_ResetCard(port_t iobase) THROWS(E_IOERROR_TIMEOUT);

DECL_END

#endif /* !GUARD_MODNE2K_NE2K_H */
