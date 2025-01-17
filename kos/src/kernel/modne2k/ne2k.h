/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODNE2K_NE2K_H
#define GUARD_MODNE2K_NE2K_H 1

#include <kernel/compiler.h>

#include <dev/nic.h>
#include <kernel/types.h>
#include <sched/sig.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <hybrid/sequence/list.h>

#include <hw/net/ne2k.h>
#include <linux/if_ether.h>
#include <sys/io.h>

DECL_BEGIN

struct ne2k_device;

typedef struct {
	/* The Ne2k-specific AIO-handle data */
	REF struct ne2k_device *pd_device;    /* [1..1][const] The device servicing this packet. */
	REF struct nic_packet  *pd_packet;    /* [0..1][lock(CLEAR_ONCE)] The packet that is being transmit. */
	REF struct mman        *pd_payloadmm; /* [1..1][valid_if(pd_packet)][const] The VM that contains the payload. */
} Ne2kAIOHandleData;

#define Ne2kAIOHandleData_Of(h) ((Ne2kAIOHandleData *)(h)->ah_data)


/* Ne2k NIC async states. */
#define NE2K_STATE_IDLE      0x0000 /* Nothing to do, but receiving packets. */
#define NE2K_STATE_UIO       0x0001 /* User-io lock enabled (automatic send/receive won't be done)
                                     * In this mode, the NIC can be (re-)configured without having
                                     * to worry about async I/O being performed. */
#define NE2K_STATE_UIO_NOINT 0x0002 /* Same   as   `NE2K_STATE_UIO',    but   ignore   all    interrupts
                                     * This  state  is required  since  in order  to  handle interrupts,
                                     * the  current  register page  has to  be changed  to PG0  (even if
                                     * another  device  on  the  same  interrupt  line  was  responsible
                                     * for  the  interrupt).  In  order  to  prevent  such  an interrupt
                                     * from interfering with UIO, this  state means that UIO  guaranties
                                     * that the NIC will not cause an interrupt, thus also ensuring that
                                     * the register page isn't altered unexpectedly. */
#define NE2K_STATE_TX_UPLOAD 0x0003 /* A packet is currently being uploaded
                                     * This is set over  IDLE mode `nk_tranit' is  non-NULL.
                                     * The actual loading of the next pending TX-packet must
                                     * be performed by the async-worker, though! */
#define NE2K_STATE_TX_PKSEND 0x0004 /* A packet is currently being sent */
#define NE2K_STATE_RX_DNLOAD 0x0005 /* A packet is currently being downloaded */
#define NE2K_STATE_OFF       0x0006 /* The  NIC has been turned off. This mode is similar to
                                     * `NE2K_STATE_UIO', however corresponds to the state of
                                     * the `IFF_UP'-bit in `nd_ifflags'. */

/* Ne2k NIC flags. */
#define NE2K_FLAG_NORMAL     0x0000 /* Normal flags */
#define NE2K_FLAG_RXLTCH     0x4000 /* RX vs. TX latch (when set: the next time IDLE is possible
                                     * and RX  is pending,  service receive;  else: service  TX) */
#define NE2K_FLAG_RXPEND     0x8000 /* There is  a packet  pending inside  of the  device's  receive-buffer
                                     * When  this flag is set, RX-interrupt have been masked and `ENISR_RX'
                                     * has not been acknowledged yet, and the next switch to IDLE/TX_UPLOAD
                                     * with REQUIO==0 is superseded  by a switch to  `NE2K_STATE_RX_DNLOAD' */
#define NE2K_FLAG_REQUIO     0x0fff /* Mask for the # of threads that are requesting the async-io
                                     * machinery to switch over to `IDLE' mode such that they can
                                     * then switch over into `NE2K_STATE_UIO'-mode.
                                     * When this flag is set, the next time the NIC is able to switch
                                     * into  IDLE-mode, it will  do so even  if the `nd_tranit' chain
                                     * is non-empty, or the `NE2K_FLAG_RXPEND' bit is set. */
#define NE2K_FLAG_REQUIO_SHIFT 0    /* Shift for REQUIO. */
#define NE2K_FLAG_REQUIO1    (1 << NE2K_FLAG_REQUIO_SHIFT) /* A single REQUIO ticket. */

/* Encode/decode the alt-signal value send over `nd_uioint' in UIO-mode */
#define NE2K_UIOINT_ENCODE_ISR(isr_val) ((struct sig *)(0x100 | (uintptr_t)(u8)(isr_val)))
#define NE2K_UIOINT_DECODE_ISR(sig_val) ((u8)(sig_val)))

typedef union {
	WEAK uintptr_t ns_word; /* State control word */
	struct {
		WEAK uintptr_half_t ns_state; /* Ne2k state (one of `NE2K_STATE_*') */
		WEAK uintptr_half_t ns_flags; /* Ne2k flags (set of `NE2K_FLAG_*') */
	};
} Ne2kState;

typedef struct ne2k_device: nicdev {
	/* NOTE: Ne2k uses an async worker to:
	 *  TX_UPLOAD:
	 *    - Load the first AIO handle from `nk_tranit' into `nk_current'
	 *    - Upload packet data to the NIC
	 *    - Set the send-timeout (s.a. `nk_cursendtmo')
	 *    - Switch state to TX_PKSEND
	 *  TX_PKSEND:
	 *    - Setup a watchdog to handle timeouts (s.a. `nk_cursendtmo')
	 *  RX_DNLOAD:
	 *    - Download & route all pending packets
	 *    - Switch state to IDLE (or RX_SEND or RX_DNLOAD)
	 */
	struct pci_device      *nk_pcidev;        /* [1..1][const] The associated PCI device. */
	WEAK struct aio_handle *nk_current;       /* [0..1][valid_if(NE2K_STATE_TX_UPLOAD || NE2K_STATE_TX_PKSEND)]
	                                           * The current outgoing packet. */
	WEAK struct aio_handle *nk_tranit;        /* [0..1] Linked list of pending DMA packets. */
	WEAK Ne2kState          nk_state;         /* Ne2k state control word */
	ktime_t                 nk_cursendtmo;    /* [lock(NE2K_STATE_TX_PKSEND)] Timeout for the current TX_PKSEND */
	struct sig              nk_stidle;        /* Signal broadcast when the NIC switches to IDLE or OFF */
	struct sig              nk_stpkld;        /* Signal broadcast when the NIC switches to TX_UPLOAD or RX_DNLOAD */
	struct sig              nk_uioint;        /* Signal broadcast upon interrupt while in UIO-mode
	                                           * NOTE: The signal delivered here is:
	                                           *      `NE2K_UIOINT_ENCODE_ISR(inb(EN0_ISR(me->nd_iobase)))' */
	port_t                  nk_iobase;        /* [const] I/O base address. */
	/* NOTE: Ne2k pages consist of 256 bytes! */
	u8                      nk_tx_start;      /* [const] Transmit buffer start page */
	u8                      nk_tx_end;        /* [const] Transmit buffer end page */
	u8                      nk_rx_start;      /* [const] Receive buffer start page */
	u8                      nk_rx_end;        /* [const] Receive buffer end page */
	u8                      nk_rx_nxt;        /* [lock(NE2K_STATE_RX_DNLOAD)] Next unread incoming packet. */
} Ne2kDevice;

#define nicdev_asne2k(self)  ((Ne2kDevice *)(self))
#define chrdev_asne2k(self)  nicdev_asne2k(chrdev_asnic(self))
#define device_asne2k(self)  nicdev_asne2k(device_asnic(self))
#define devnode_asne2k(self) nicdev_asne2k(devnode_asnic(self))
#define fnode_asne2k(self)   nicdev_asne2k(fnode_asnic(self))
#define mfile_asne2k(self)   nicdev_asne2k(mfile_asnic(self))

/* Reset the network card via `NE_RESET()'. */
INTDEF void KCALL Ne2k_ResetCard(port_t iobase) THROWS(E_IOERROR_TIMEOUT);


DECL_END

#endif /* !GUARD_MODNE2K_NE2K_H */
