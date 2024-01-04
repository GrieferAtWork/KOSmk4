/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _HW_USB_UHCI_H
#define _HW_USB_UHCI_H 1

#include <__stdinc.h>

#include <kos/anno.h>
#include <hybrid/__atomic.h>
#include <bits/types.h>
#include <sys/io.h>

__SYSDECL_BEGIN

/* Refs:
 *   - ftp://ftp.netbsd.org/pub/NetBSD/misc/blymn/uhci11d.pdf
 *   - https://github.com/pdoane/osdev/blob/master/usb/uhci.c
 */

/* I/O port offsets. */
#define UHCI_USBCMD    0x00 /* USB command */
#define    UHCI_USBCMD_RS      0x01 /* [bit(0)] Run/Stop */
#define    UHCI_USBCMD_HCRESET 0x02 /* [bit(1)] Host Controller Reset */
#define    UHCI_USBCMD_GRESET  0x04 /* [bit(2)] Global Reset */
#define    UHCI_USBCMD_EGSM    0x08 /* [bit(3)] Enter Global Suspend Mode (See also: notes in `/kos/src/kernel/modusb/uhci.h') */
#define    UHCI_USBCMD_FGR     0x10 /* [bit(4)] Force Global Resume */
#define    UHCI_USBCMD_SWDBG   0x20 /* [bit(5)] Software Debug */
#define    UHCI_USBCMD_CF      0x40 /* [bit(6)] Configure Flag */
#define    UHCI_USBCMD_MAXP    0x80 /* [bit(7)] Max Packet */

#define UHCI_USBSTS    0x02 /* USB status */
#define    UHCI_USBSTS_USBINT 0x01 /* [bit(0)] USB Interrupt  */
#define    UHCI_USBSTS_ERROR  0x02 /* [bit(1)] USB Error Interrupt */
#define    UHCI_USBSTS_RD     0x04 /* [bit(2)] Resume Detected */
#define    UHCI_USBSTS_HSE    0x08 /* [bit(3)] Host System Error */
#define    UHCI_USBSTS_HCPE   0x10 /* [bit(4)] Host Controller Process Error */
#define    UHCI_USBSTS_HCH    0x20 /* [bit(5)] Host Controller Halted */

#define UHCI_USBINTR   0x04 /* Usb Interrupt Enable */
#define    UHCI_USBINTR_TIE  0x01 /* [bit(0)] Timeout/CRC Interrupt Enable */
#define    UHCI_USBINTR_RIE  0x02 /* [bit(1)] Resume Interrupt Enable */
#define    UHCI_USBINTR_IOC  0x04 /* [bit(2)] Interrupt On Complete (IOC) Enable */
#define    UHCI_USBINTR_SPIE 0x08 /* [bit(3)] Short Packet Interrupt Enable */

#define UHCI_FRNUM     0x06 /* Frame number register */
#define    UHCI_FRNUM_FLCIM 0x7ff /* Frame List Current Index/Frame Number */
#define    UHCI_FRNUM_FLCIS 0     /* Frame List Current Index/Frame Number */

#define UHCI_FLBASEADD 0x08 /* Frame list base address */
#define    UHCI_FLBASEADD_BA 0xfffff000 /* Base Address (must be 4K-aligned) */
#define    UHCI_FRAMELIST_ALIGN 4096
#define    UHCI_FRAMELIST_SIZE  4096
#define    UHCI_FRAMELIST_COUNT 1024
/* A frame list is a 1024-element vector of u32 `UHCI_FLE_*'
 * QH: `struct uhci_qh'
 * TD: `struct uhci_td' */
#define       UHCI_FLE_TERM  0x00000001 /* Terminate (Set to 1 of entry is unused) */
#define       UHCI_FLE_QHTD  0x00000002 /* QH/TD Select. 1=QH(QueueHead). 0=TD(TransferDescriptor). */
#define       UHCI_FLE_FLP   0xfffffff0 /* Address mask for physical address of pointed-to QH/TD */
#define       UHCI_FLE_ALIGN 16

#define UHCI_SOFMOD    0x0c /* Start of frame modify */
#define    UHCI_SOFMOD_TV    0x7f /* SOF Timing Value */
#define    UHCI_SOFMOD_DEFAULT 64 /* == 0x40: Default timing value (just set this one during init) */

#define UHCI_PORTSCMAXCNT 8 /* Max possible number of ports */
#define UHCI_PORTSC(i) (0x10 + (i)*2)
#define UHCI_PORTSC1   0x10 /* Port 1 status/control */
#define UHCI_PORTSC2   0x12 /* Port 2 status/control  */
#define    UHCI_PORTSC_CCS      0x0001 /* [bit(0)][ro]   Current Connect Status */
#define    UHCI_PORTSC_CSC      0x0002 /* [bit(1)][r/wc] Connect Status Change */
#define    UHCI_PORTSC_PED      0x0004 /* [bit(2)][rw]   Port Enabled/Disabled */
#define    UHCI_PORTSC_PEDC     0x0008 /* [bit(3)][r/wc] Port Enable/Disable Change */
#define    UHCI_PORTSC_LS       0x0030 /* [bit(4:5)][ro] Line Status */
#define    UHCI_PORTSC_RD       0x0040 /* [bit(6)][rw]   Resume Detect */
#define    UHCI_PORTSC_R1       0x0080 /* [bit(7)][ro]   Reserved (hardwired to 1) */
#define    UHCI_PORTSC_LSDA     0x0100 /* [bit(8)][ro]   Low Speed Device Attached */
#define    UHCI_PORTSC_RST      0x0200 /* [bit(9)][rw]   Port Reset */
#define    UHCI_PORTSC_SUS      0x1000 /* [bit(12)][rw]  Suspend */


/* Flags for `struct uhci_td::td_lp' */
#define UHCI_TDLP_TERM  0x00000001 /* [bit(0)] Terminate (Set to 1 for end-of-chain) */
#define UHCI_TDLP_QHTD  0x00000002 /* [bit(1)] QH/TD Select. 1=QH(QueueHead). 0=TD(TransferDescriptor). */
#define UHCI_TDLP_DBS   0x00000004 /* [bit(2)] Depth/Breadth Select. (1=Depth first. 0=Breadth first) */
#define UHCI_TDLP_LP    0xfffffff0 /* Link Pointer (16-bit aligned) */

/* Flags for `struct uhci_td::td_cs' */
#define UHCI_TDCS_ACTLEN  0x000007ff /* [bit(0:10)][out] Actual Length. Written by the Host
                                      * Controller  after a USB transaction to indicate the
                                      * actual number of bytes that were transferred */
#define UHCI_TDCS_BSE     0x00020000 /* [bit(17)][out] This bit is set to a 1 by the Host Controller during
                                      * status update to  indicate that the  receive data stream  contained
                                      * a sequence of more than 6 ones in a row. */
#define UHCI_TDCS_CRCTMO  0x00040000 /* [bit(18)][out] Set by the HC: OUT/SETUP: Timeout; IN: CRC error. */
#define UHCI_TDCS_NAKR    0x00080000 /* [bit(19)][out] Set by the HC: NAK Received. */
#define UHCI_TDCS_BABBLE  0x00100000 /* [bit(20)][out] Set by the HC: Babble Detected. */
#define UHCI_TDCS_DBE     0x00200000 /* [bit(21)][out] Set by the HC: Data Buffer Error. */
#define UHCI_TDCS_STALL   0x00400000 /* [bit(22)][out] Set by the HC: Stalled. */
#define UHCI_TDCS_ACTIVE  0x00800000 /* [bit(23)][in|out] Cleared by the HC upon (successful, or `UHCI_TDCS_STALL') completion of the transaction (set by software). */
#define UHCI_TDCS_IOC     0x01000000 /* [bit(24)][in] Interrupt on Complete (even when `UHCI_TDCS_ACTIVE' wasn't set) */
#define UHCI_TDCS_IOS     0x02000000 /* [bit(25)][in] Isochronous Select (If set, always clear `UHCI_TDCS_ACTIVE', even on error) */
#define UHCI_TDCS_LSD     0x04000000 /* [bit(26)][in] Low Speed Device */
#define UHCI_TDCS_ERRCNTM 0x18000000 /* [bit(27:28)][in|out] Remaining number of allowed retries (0-3)
                                      * When non-zero,  HC will  decrement  and write-back  on  error.
                                      * If HC decrements  to 0, write-back  and set  `UHCI_TDCS_STALL'
                                      * When  initialized to 0,  HC will keep  on trying without limit */
#define UHCI_TDCS_ERRCNTS         27 /* Shift for `UHCI_TDCS_ERRCNTM' */
#define UHCI_TDCS_SPD     0x20000000 /* [bit(29)][in] Short Packet Detect */


/* Flags for `struct uhci_td::td_tok' */
#define UHCI_TDTOK_PID      0x000000ff /* [bit(0:7)] Packet Identification (PID). */
#define    UHCI_TDTOK_PID_IN      0x69 /* IN:    Read data from the device (by the way: ~nice~...) */
#define    UHCI_TDTOK_PID_OUT     0xe1 /* OUT:   Write data to the device */
#define    UHCI_TDTOK_PID_SETUP   0x2d /* SETUP: Write data to the device (for configuration) */
#define UHCI_TDTOK_DEVM     0x00007f00 /* [bit(8:14)] Device Address. */
#define UHCI_TDTOK_DEVS              8 /* Shift for `UHCI_TDTOK_DEVM'. */
#define UHCI_TDTOK_ENDPTM   0x00078000 /* [bit(15:18)] Endpoint (pipe channel index for device). */
#define UHCI_TDTOK_ENDPTS           15 /* Shift for `UHCI_TDTOK_ENDPTM'. */
#define UHCI_TDTOK_DTOGGM   0x00080000 /* [bit(19)] Data Toggle (used for synchronization; always 0 when `UHCI_TDCS_IOS' is set). */
#define UHCI_TDTOK_DTOGGS           19 /* Shift for `UHCI_TDTOK_DTOGGMs' */
#define UHCI_TDTOK_MAXLENM  0xffe00000 /* [bit(21:31)] Maximum Length (size of the buffer pointed by `td_buf') */
#define UHCI_TDTOK_MAXLENS          21 /* Shift for `UHCI_TDTOK_MAXLENM' */



/* Flags for `struct uhci_qh::qh_hp' */
#define UHCI_QHHP_TERM  0x00000001 /* [bit(0)] Terminate (Set to 1 for end-of-chain) */
#define UHCI_QHHP_QHTD  0x00000002 /* [bit(1)] QH/TD Select. 1=QH(QueueHead). 0=TD(TransferDescriptor). */
#define UHCI_QHHP_LP    0xfffffff0 /* Link Pointer (16-bit aligned) */

/* Flags for `struct uhci_qh::qh_ep' */
#define UHCI_QHEP_TERM  0x00000001 /* [bit(0)] Terminate (Set to 1 for end-of-chain) */
#define UHCI_QHEP_QHTD  0x00000002 /* [bit(1)] QH/TD Select. 1=QH(QueueHead). 0=TD(TransferDescriptor). */
#define UHCI_QHEP_LP    0xfffffff0 /* Link Pointer (16-bit aligned) */


#ifdef __CC__
struct /*__ATTR_ALIGNED(16)*/ uhci_td {
	/* Transfer descriptor. */
	__PHYS __uint32_t td_lp;  /* [in] TD link pointer (set of `UHCI_TDLP_*') */
	__uint32_t        td_cs;  /* [in|out] TD control and status (set of `UHCI_TDCS_*') */
	__uint32_t        td_tok; /* [in] TD token (set of `UHCI_TDTOK_*') */
	__PHYS __uint32_t td_buf; /* [in] TD buffer address (any alignment is fine) */
	/* Software may place more fields here... (e.g. a `struct sig') */
};
#define uhci_td_actlen(self) \
	((__hybrid_atomic_load(&(self)->td_cs, __ATOMIC_ACQUIRE) & UHCI_TDCS_ACTLEN) + 1)
#define uhci_td_maxlen(self)                                               \
	(((((self)->td_tok & UHCI_TDTOK_MAXLENM) >> UHCI_TDTOK_MAXLENS) + 1) & \
	 (UHCI_TDTOK_MAXLENM >> UHCI_TDTOK_MAXLENS))

struct /*__ATTR_ALIGNED(16)*/ uhci_qh {
	/* Queue head descriptor. */
	__PHYS __uint32_t qh_hp;  /* [in]     Queue head link pointer (set of `UHCI_QHHP_*') */
	__PHYS __uint32_t qh_ep;  /* [in|out] Queue element link pointer  (set of `UHCI_QHEP_*') */
	/* Software may place more fields here... (e.g. a `struct sig') */
};
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_HW_USB_UHCI_H */
