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
#ifndef _HW_NET_NE2K_H
#define _HW_NET_NE2K_H 1

#include <__stdinc.h>

#include <hybrid/byteorder.h>

#include <bits/types.h>


/* Interface for NE2K network cards. */


/* Some of the definitions and macros below are taken from
 * linux   sources:    "/drivers/net/ethernet/8390/8390.h"
 * The comment below can be found in the original  source.
 * NOTICE: Changes, as well as additions have been made using the following source(s):
 * >> http://www.ethernut.de/pdf/8019asds.pdf */
/* This file is part of Donald Becker's 8390 drivers, and is distributed
   under the same license. Auto-loading of 8390.o only in v2.2 - Paul G.
   Some of these names and comments originated from the Crynwr
   packet drivers, which are distributed under the GPL. */

#define NE_PROM_SIZE 32 /* Set of the PROM data (which (among other things) contains the MAC address) */

#define E8390_CMD(base) ((base) + 0x00) /* The command register (for all pages) */
#define    E8390_STOP     0x01 /* [bit(0)] E8390_CMD: Stop and reset the chip */
#define    E8390_START    0x02 /* [bit(1)] E8390_CMD: Start the chip, clear reset */
#define    E8390_TRANS    0x04 /* [bit(2)] E8390_CMD: Transmit a frame */
#define    E8390_RREAD    0x08 /* [bit(3)] E8390_CMD: Remote read */
#define    E8390_RWRITE   0x10 /* [bit(4)] E8390_CMD: Remote write  */
#define    E8390_NODMA    0x20 /* [bit(5)] E8390_CMD: Remote DMA */
#define    E8390_PAGE0    0x00 /* [bit(6-7)] E8390_CMD: Select page chip registers */
#define    E8390_PAGE1    0x40 /* [bit(6-7)] E8390_CMD: using the two high-order bits */
#define    E8390_PAGE2    0x80 /* [bit(6-7)] E8390_CMD: Page 3 is invalid. */
#define    E8390_PGMSK    0xc0 /* [bit(6-7)] E8390_CMD: Mask for the current page. */
#define NE_DATAPORT(base) ((base) + 0x10) /* NatSemi-defined port window offset. (for all pages) */
#define NE_RESET(base)    ((base) + 0x1f) /* Issue a read to reset, a write to clear. (for all pages) */

/* Page 0 register offsets. */
#define EN0_CLDALO(base)   ((base) + 0x01) /* Low byte of current local dma addr RD */
#define EN0_STARTPG(base)  ((base) + 0x01) /* Starting page of ring bfr WR */
#define EN0_CLDAHI(base)   ((base) + 0x02) /* High byte of current local dma addr RD */
#define EN0_STOPPG(base)   ((base) + 0x02) /* Ending page +1 of ring bfr WR */
#define EN0_BOUNDARY(base) ((base) + 0x03) /* Boundary page of ring bfr RD WR */
#define EN0_TSR(base)      ((base) + 0x04) /* Transmit status reg RD */
#define    ENTSR_PTX      0x01 /* EN0_TSR: Packet transmitted without error */
#define    ENTSR_ND       0x02 /* EN0_TSR: The transmit wasn't deferred. */
#define    ENTSR_COL      0x04 /* EN0_TSR: The transmit collided at least once. */
#define    ENTSR_ABT      0x08 /* EN0_TSR: The transmit collided 16 times, and was deferred. */
#define    ENTSR_CRS      0x10 /* EN0_TSR: The carrier sense was lost. */
#define    ENTSR_FU       0x20 /* EN0_TSR: A "FIFO underrun" occurred during transmit. */
#define    ENTSR_CDH      0x40 /* EN0_TSR: The collision detect "heartbeat" signal was lost. */
#define    ENTSR_OWC      0x80 /* EN0_TSR: There was an out-of-window collision. */
#define    ENTSR_EMSK     0xfe /* EN0_TSR: Mask for error bits */
#define EN0_TPSR(base)     ((base) + 0x04) /* Transmit starting page WR */
#define EN0_NCR(base)      ((base) + 0x05) /* Number of collision reg RD */
#define EN0_TCNTLO(base)   ((base) + 0x05) /* Low byte of tx byte count WR */
#define EN0_FIFO(base)     ((base) + 0x06) /* FIFO RD */
#define EN0_TCNTHI(base)   ((base) + 0x06) /* High byte of tx byte count WR */
#define EN0_ISR(base)      ((base) + 0x07) /* Interrupt status reg RD WR */
#define    ENISR_RX       0x01 /* EN0_ISR: Receiver, no error */
#define    ENISR_TX       0x02 /* EN0_ISR: Transmitter, no error */
#define    ENISR_RX_ERR   0x04 /* EN0_ISR: Receiver, with error */
#define    ENISR_TX_ERR   0x08 /* EN0_ISR: Transmitter, with error */
#define    ENISR_OVER     0x10 /* EN0_ISR: Receiver overwrote the ring */
#define    ENISR_COUNTERS 0x20 /* EN0_ISR: Counters need emptying */
#define    ENISR_RDC      0x40 /* EN0_ISR: remote dma complete */
#define    ENISR_RESET    0x80 /* EN0_ISR: Reset completed (s.a. `NE_RESET()') */
#define    ENISR_ALL      0x3f /* EN0_ISR: Interrupts we will enable */
#define    E8390_TX_IRQ_MASK 0x0a /* For register EN0_ISR */
#define    E8390_RX_IRQ_MASK 0x05
#define EN0_CRDALO(base)   ((base) + 0x08) /* low byte of current remote dma address RD */
#define EN0_RSARLO(base)   ((base) + 0x08) /* Remote start address reg 0 */
#define EN0_CRDAHI(base)   ((base) + 0x09) /* high byte, current remote dma address RD */
#define EN0_RSARHI(base)   ((base) + 0x09) /* Remote start address reg 1 */
#define EN0_RCNTLO(base)   ((base) + 0x0a) /* Remote byte count reg WR */
#define EN0_RCNTHI(base)   ((base) + 0x0b) /* Remote byte count reg WR */
#define EN0_RSR(base)      ((base) + 0x0c) /* rx status reg RD */
#define    ENRSR_RXOK     0x01 /* EN0_RSR: Received a good packet */
#define    ENRSR_CRC      0x02 /* EN0_RSR: CRC error */
#define    ENRSR_FAE      0x04 /* EN0_RSR: frame alignment error */
#define    ENRSR_FO       0x08 /* EN0_RSR: FIFO overrun */
#define    ENRSR_MPA      0x10 /* EN0_RSR: missed pkt */
#define    ENRSR_PHY      0x20 /* EN0_RSR: physical/multicast address */
#define    ENRSR_DIS      0x40 /* EN0_RSR: receiver disable. set in monitor mode */
#define    ENRSR_DEF      0x80 /* EN0_RSR: deferring */
#define EN0_RXCR(base)     ((base) + 0x0c) /* RX configuration reg WR */
#define    ERXCR_SEP      0x01 /* EN0_RXCR: Accept packages with receive errors. */
#define    ERXCR_AR       0x02 /* EN0_RXCR: Accept packages smaller than 64 bytes. */
#define    ERXCR_AB       0x04 /* EN0_RXCR: Accept broadcast packages. */
#define    ERXCR_AM       0x08 /* EN0_RXCR: Accept multicast packages. */
#define    ERXCR_PRO      0x10 /* EN0_RXCR: Accept all packets with physical destination address. */
#define    ERXCR_MON      0x20 /* EN0_RXCR: Check incoming packages, but don't buffer them. */
#define EN0_TXCR(base)     ((base) + 0x0d) /* TX configuration reg WR */
#define    ETXCR_CRC      0x01 /* EN0_TXCR: Set to inhibit CRC within the transmitter. */
#define    ETXCR_LB0      0x02 /* EN0_TXCR: Loopback mode bit 0. */
#define    ETXCR_LB1      0x04 /* EN0_TXCR: Loopback mode bit 1. */
#define       ETXCR_LOOPBACK_NORMAL  0x00 /* EN0_TXCR: ... */
#define       ETXCR_LOOPBACK_INTERN  ETXCR_LB0 /* EN0_TXCR: Transmitter off */
#define       ETXCR_LOOPBACK_EXTERN  ETXCR_LB1 /* EN0_TXCR: ... */
#define       ETXCR_LOOPBACK_EXTERN2 (ETXCR_LB0 | ETXCR_LB1) /* EN0_TXCR: Same behavior as 'ETXCR_LOOPBACK_EXTERN' */
#define    ETXCR_ATD      0x08 /* EN0_TXCR: Auto Transmit Disable. (Leave at ZERO) */
#define    ETXCR_OFST     0x10 /* EN0_TXCR: Collision Offset Enable. */
#define EN0_COUNTER0(base) ((base) + 0x0d) /* Rcv alignment error counter RD */
#define EN0_DCFG(base)     ((base) + 0x0e) /* Data configuration reg WR */
#define    ENDCFG_WTS     0x01 /* EN0_DCFG: Word-transfer select (0: byte-wide, 1: word-wide) */
#define    ENDCFG_BOS     0x02 /* EN0_DCFG: Byte order select (Leave at ZERO) */
#define    ENDCFG_LAS     0x04 /* EN0_DCFG: Leave at ZERO */
#define    ENDCFG_LS      0x08 /* EN0_DCFG: Loopback Select. (Set to 1 for Normal Operation) */
#define    ENDCFG_ARM     0x10 /* EN0_DCFG: Auto-initialize Remote. (1: Send Packet Command executed) */
#define    ENDCFG_FT0     0x20 /* EN0_DCFG: FIFO threshold select bit 0. */
#define    ENDCFG_FT1     0x40 /* EN0_DCFG: FIFO threshold select bit 1. */
#define EN0_COUNTER1(base) ((base) + 0x0e) /* Rcv CRC error counter RD */
#define EN0_IMR(base)      ((base) + 0x0f) /* Interrupt mask reg WR */
#define EN0_COUNTER2(base) ((base) + 0x0f) /* Rcv missed frame error counter RD */

/* Bits in EN0_DCFG - Data Configuration Register. */

/* Page 1 register offsets. */
#define EN1_PHYS(base)          ((base) + 0x01)    /* This board's physical enet addr RD WR */
#define EN1_PHYS_SHIFT(base, i) ((base) + (i) + 1) /* Get and set mac address */
#define EN1_CURPAG(base)        ((base) + 0x07)    /* Current memory page RD WR */
#define EN1_MULT(base)          ((base) + 0x08)    /* Multicast filter mask array (8 bytes) RD WR */
#define EN1_MULT_SHIFT(base, i) ((base) + (i) + 8) /* Get and set multicast filter */

#ifdef __CC__
__DECL_BEGIN

struct e8390_pkt_hdr {
	__uint8_t  ph_status; /* Status byte (unused / not well defined; just ignore it...) */
	__uint8_t  ph_next;   /* Page # of the next header. */
	__uint16_t ph_count;  /* Length of this header + the actual packet. */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_HW_NET_NE2K_H */
