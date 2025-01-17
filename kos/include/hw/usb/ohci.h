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
#ifndef _HW_USB_OHCI_H
#define _HW_USB_OHCI_H 1

#include <__stdinc.h>

#include <kos/anno.h>
#include <bits/types.h>

__SYSDECL_BEGIN

/* Refs:
 *   - http://www.scaramanga.co.uk/stuff/qemu-usb/hcir1_0a.pdf
 */


/* OHCI Register offsets. */
#define OHCI_HcRevision         0x00
#define OHCI_HcControl          0x04
#define    OHCI_HcControl_CBSRM    0x00000003 /* [bit(0:1)] ControlBulkServiceRatio */
#define    OHCI_HcControl_CBSRS             0 /* Shift for `OHCI_HcControl_CBSRM' */
#define    OHCI_HcControl_PLE      0x00000004 /* [bit(2)] PeriodicListEnable */
#define    OHCI_HcControl_IE       0x00000008 /* [bit(3)] IsochronousEnable */
#define    OHCI_HcControl_CLE      0x00000010 /* [bit(4)] ControlListEnable */
#define    OHCI_HcControl_BLE      0x00000020 /* [bit(5)] BulkListEnable */
#define    OHCI_HcControl_HCFSM    0x000000c0 /* [bit(6:7)] HostControllerFunctionalState */
#define    OHCI_HcControl_HCFSS             6 /* Shift for `OHCI_HcControl_HCFSM' */
#define       OHCI_HcControl_HCFS_USBRESET       0x00000000
#define       OHCI_HcControl_HCFS_USBRESUME      0x00000040
#define       OHCI_HcControl_HCFS_USBOPERATIONAL 0x00000080
#define       OHCI_HcControl_HCFS_USBSUSPEND     0x000000c0
#define    OHCI_HcControl_IR       0x00000100 /* [bit(8)] InterruptRouting */
#define    OHCI_HcControl_RWC      0x00000200 /* [bit(9)] RemoteWakeupConnected */
#define    OHCI_HcControl_RWE      0x00000400 /* [bit(10)] RemoteWakeupEnable */
#define OHCI_HcCommandStatus    0x08
#define    OHCI_HcCommandStatus_HCR  0x00000001 /* [bit(0)] HostControllerReset */
#define    OHCI_HcCommandStatus_CLF  0x00000002 /* [bit(1)] ControlListFilled */
#define    OHCI_HcCommandStatus_BLF  0x00000004 /* [bit(2)] BulkListFilled */
#define    OHCI_HcCommandStatus_OCR  0x00000008 /* [bit(3)] OwnershipChangeRequest */
#define    OHCI_HcCommandStatus_SOCM 0x00030000 /* [bit(16:17)] SchedulingOverrunCount */
#define    OHCI_HcCommandStatus_SOCS         16 /* Shift for `OHCI_HcCommandStatus_SOCM' */
#define OHCI_HcInterruptStatus  0x0c /* Set of `OHCI_HcInterrupt_*' describing a current interrupt */
#define OHCI_HcInterruptEnable  0x10 /* Writes of `OHCI_HcInterrupt_*' enable that interrupt */
#define OHCI_HcInterruptDisable 0x14 /* Writes of `OHCI_HcInterrupt_*' disable that interrupt */
#define    OHCI_HcInterrupt_SO   0x00000001 /* [bit(0)] SchedulingOverrun */
#define    OHCI_HcInterrupt_WDH  0x00000002 /* [bit(1)] WritebackDoneHead */
#define    OHCI_HcInterrupt_SF   0x00000004 /* [bit(2)] StartofFrame */
#define    OHCI_HcInterrupt_RD   0x00000008 /* [bit(3)] ResumeDetected */
#define    OHCI_HcInterrupt_UE   0x00000010 /* [bit(4)] UnrecoverableError */
#define    OHCI_HcInterrupt_FNO  0x00000020 /* [bit(5)] FrameNumberOverflow */
#define    OHCI_HcInterrupt_RHSC 0x00000040 /* [bit(6)] RootHubStatusChange */
#define    OHCI_HcInterrupt_OC   0x40000000 /* [bit(30)] OwnershipChange */
#define    OHCI_HcInterrupt_MIE  0x80000000 /* [bit(31)] MasterInterruptEnable (must be set for interrupts to happen) */
#define OHCI_HcHCCA             0x18
#define OHCI_HcPeriodCurrentED  0x1c
#define OHCI_HcControlHeadED    0x20
#define OHCI_HcControlCurrentED 0x24
#define OHCI_HcBulkHeadED       0x28
#define OHCI_HcBulkCurrentED    0x2c
#define OHCI_HcDoneHead         0x30
#define OHCI_HcFmInterval       0x34
#define OHCI_HcFmRemaining      0x38
#define OHCI_HcFmNumber         0x3c
#define OHCI_HcPeriodicStart    0x40
#define OHCI_HcLSThreshold      0x44
#define OHCI_HcRhDescriptorA    0x48
#define OHCI_HcRhDescriptorB    0x4c
#define OHCI_HcRhStatus         0x50
/* Warning the specs are dumb and enumerate these from 1 (but  you
 * can just enum them from 0, because _that's_ where arrays start) */
#define OHCI_HcRhPortStatus(i)  (0x54+((i)*4))




/* Required alignment for `struct ohci_ed' */
#define OHCI_ED_ALIGN 16

/* Flags for `struct ohci_ed::ed_fl' */
#define OHCI_EDFL_FAM  0x0000007f /* [bit(0:6)] FunctionAddress (device address, as set by `USB_REQUEST_SET_ADDRESS') */
#define OHCI_EDFL_FAS           0 /* Shift for `OHCI_EDFL_FAM' */
#define OHCI_EDFL_ENM  0x00000780 /* [bit(7:10)] EndpointNumber */
#define OHCI_EDFL_ENS           7 /* Shift for `OHCI_EDFL_ENM' */
#define OHCI_EDFL_DM   0x00001800 /* [bit(11:12)] Direction */
#define OHCI_EDFL_DS           11 /* Shift for `OHCI_EDFL_DM' */
#define    OHCI_EDFL_D_GTD  0x00000000 /* Get from TD */
#define    OHCI_EDFL_D_OUT  0x00000800 /* In direction */
#define    OHCI_EDFL_D_IN   0x00001000 /* Out direction */
#define    OHCI_EDFL_D_GTD2 0x00001800 /* Alias for `OHCI_EDFL_D_GTD' */
#define OHCI_EDFL_LS   0x00002000 /* [bit(13)] Low-speed device (flag) */
#define OHCI_EDFL_SKP  0x00004000 /* [bit(14)] Skip this ED (making it inactive; should be used as a lock to prevent
                                   *           hardware access when modifying the physical pointers of the ED, most
                                   *           notably: modifications made to `ed_hp') */
#define OHCI_EDFL_ISO  0x00008000 /* [bit(15)] The Isochronous TD format is used. (called the `F' bit by the specs)
                                   * When clear, `ed_hp' points to a `struct ohci_td'.
                                   * Otherwise, `ed_hp' points to `struct ohci_itd' */
#define OHCI_EDFL_MPSM 0x07ff0000 /* [bit(16:26)] Max packet size */
#define OHCI_EDFL_MPSS         16 /* Shift for `OHCI_EDFL_MPSM' */


/* Flags for `struct ohci_ed::ed_hp' */
#define OHCI_EDHP_HLT  0x00000001 /* [bit(0)][out] Set by the HC to halt processing (usually due to an error) */
#define OHCI_EDHP_CAR  0x00000002 /* [bit(1)][in|out] Data toggle carry bit (ohci version of `UHCI_TDTOK_DTOGGM') */


/* Required alignment for `struct ohci_td' */
#define OHCI_TD_ALIGN 16

/* Flags for `struct ohci_td::td_fl' */
#define OHCI_TDFL_SHRT    0x00040000 /* [bit(18)][in] Allow the last packet to be smaller than the required buffer size.
                                      * The OHCI specs call this the `R' bit, for `bufferRounding' */
#define OHCI_TDFL_DPM     0x00180000 /* [bit(19:20)][in] Transfer direction */
#define OHCI_TDFL_DPS             19 /* Shift for `OHCI_TDFL_DPM' */
#define    OHCI_TDFL_DP_SETUP 0x00000000 /* Setup packet */
#define    OHCI_TDFL_DP_OUT   0x00080000 /* Out packet */
#define    OHCI_TDFL_DP_IN    0x00100000 /* In packet */
#define OHCI_TDFL_DIM     0x00e00000 /* [bit(21:23)][in] DelayInterrupt (Number of frames to wait before causing an interrupt)
                                      * When set set to `OHCI_TDFL_DI_NOINT', never generate an
                                      * interrupt (used as the opposite of `UHCI_TDCS_IOC') */
#define OHCI_TDFL_DIS             21 /* Shift for `OHCI_TDFL_DPM' */
#define    OHCI_TDFL_DI_NOINT 0x00e00000 /* Don't generate an interrupt on completion of this TD */
#define OHCI_TDFL_T_STATE 0x01000000 /* [bit(24)][in|out] The data-toggle state (s.a. `OHCI_TDFL_T_AVAIL') */
#define OHCI_TDFL_T_AVAIL 0x02000000 /* [bit(25)][in|out] When set, use `OHCI_TDFL_T_STATE' as data-toggle bit. - Else, use `OHCI_EDHP_CAR'
                                      * Note that this, and `OHCI_TDFL_T_STATE' are maintained by the HC to allow
                                      * for a single TD to be used multiple times for transmission of larger packets.
                                      * As such, both  this, and  `OHCI_TDFL_T_STATE' should be  initialized to  `0',
                                      * and software should simply ignore them at all times. */
#define OHCI_TDFL_ECM     0x0c000000 /* [bit(26:27)][in|out] Number of consecutive errors (used by hardware; just initialize it to `0') */
#define OHCI_TDFL_CCM     0xf0000000 /* [bit(28:31)][out] Condition code (open error, filled with that error before a TD is placed in the done queue) (One of `OHCI_CC_*') */
#define OHCI_TDFL_CCS             28 /* Shift for `OHCI_TDFL_CCM' */


/* Required alignment for `struct ohci_itd' */
#define OHCI_ITD_ALIGN 32

/* Flags for `struct ohci_itd::td_fl' */
#define OHCI_ITDFL_SF      0x0000ffff /* [bit(0:15)][in] Starting Frame number (first frame when data of this TD is sent) */
#define OHCI_ITDFL_DIM     0x00e00000 /* [bit(21:23)][in] DelayInterrupt (Number of frames to wait before causing an interrupt)
                                      * When set set to `OHCI_ITDFL_DI_NOINT', never generate an
                                      * interrupt (used as the opposite of `UHCI_TDCS_IOC') */
#define OHCI_ITDFL_DIS             21 /* Shift for `OHCI_TDFL_DPM' */
#define    OHCI_ITDFL_DI_NOINT 0x00e00000 /* Don't generate an interrupt on completion of this TD */
#define OHCI_ITDFL_FCM     0x07000000 /* [bit(24:26)][in] Frame count - 1 (Number of data packets) */
#define OHCI_ITDFL_FCS             24 /* Shift for `OHCI_ITDFL_FCM' */
#define OHCI_ITDFL_CCM     0xf0000000 /* [bit(28:31)][out] Condition code (open error, filled with that error before a TD is placed in the done queue) (One of `OHCI_CC_*') */
#define OHCI_ITDFL_CCS             28 /* Shift for `OHCI_ITDFL_CCM' */


/* Flags for `struct ohci_itd::itd_psw[n]' */
#define OHCI_ITD_PSW_SZM   0x07ff /* [bit(0:10)] Buffer size. */
#define OHCI_ITD_PSW_SZS        0 /* Shift for `OHCI_ITD_PSW_OFM' */
#define OHCI_ITD_PSW_CCM   0xf000 /* [bit(12:15)] Buffer status code. (One of `OHCI_CC_*') */
#define OHCI_ITD_PSW_CCS       12 /* Shift for `OHCI_ITD_PSW_CCM' */

/* OHCI Condition codes. */
#define OHCI_CC_NOERROR             0x0
#define OHCI_CC_CRC                 0x1
#define OHCI_CC_BITSTUFFING         0x2
#define OHCI_CC_DATATOGGLEMISMATCH  0x3
#define OHCI_CC_STALL               0x4
#define OHCI_CC_DEVICENOTRESPONDING 0x5
#define OHCI_CC_PIDCHECKFAILURE     0x6
#define OHCI_CC_UNDEXPETEDPID       0x7
#define OHCI_CC_DATAOVERRUN         0x8
#define OHCI_CC_DATAUNDERRUN        0x9
/*      OHCI_CC_RESERVED            0xa */
/*      OHCI_CC_RESERVED            0xb */
#define OHCI_CC_BUFFEROVERRUN       0xc
#define OHCI_CC_BUFFERUNDERRUN      0xd
#define OHCI_CC_NOTACCESSED         0xe /* Never set by hardware */
#define OHCI_CC_NOTACCESSED2        0xf /* Never set by hardware */



#ifdef __CC__

struct /*__ATTR_ALIGNED(OHCI_ED_ALIGN)*/ ohci_ed {
	__uint32_t        ed_fl;  /* [in] Flags (Set of `OHCI_EDFL_*') */
	__PHYS __uint32_t ed_tp;  /* [in] TD queue tail pointer (16-byte aligned)
	                           * Used to compare against `ed_hp'; it equal, stop processing. */
	__PHYS __uint32_t ed_hp;  /* [in|out] Points to the next TD to be processed for this endpoint
	                           *          (16-byte aligned); or'd with `OHCI_EDHP_*'
	                           * Note that this is either `struct ohci_td' or `struct ohci_itd',
	                           * depending   on   the   state  of   the   `OHCI_EDFL_ISO'  flag. */
	__PHYS __uint32_t ed_ned; /* [in] If non-zero, next Endpoint Descriptor (`ohci_ed') (16-byte aligned) */
};

struct /*__ATTR_ALIGNED(OHCI_TD_ALIGN)*/ ohci_td {
	__uint32_t        td_fl;  /* [in] Flags (Set of `OHCI_TDFL_*') */
	__PHYS __uint32_t td_cbp; /* [in|out] Pointer to the next unwritten buffer location (or 0 if the buffer is empty)
	                           * Note that the buffer described  by this and `ed_be' may  only cross a physical  page
	                           * boundary once, meaning  that the  max buffer size  is 2*4096=8192  bytes, though  in
	                           * practice, the safest bet is  to just require a max  buffer size of 4096 bytes,  thus
	                           * preventing  the need to fiddle around with  buffer alignment, this that limit allows
	                           * for any arbitrary buffer alignment. */
	__PHYS __uint32_t td_ntd; /* [in] Next Transfer Descriptor (or `ed_tp' for end) (16-byte aligned) */
	__PHYS __uint32_t td_be;  /* [in] Buffer end (or rather: max; as in: last byte written) pointer. */
};

struct /*__ATTR_ALIGNED(OHCI_ITD_ALIGN)*/ ohci_itd_ {
	__uint32_t        itd_fl;     /* [in] Flags (Set of `OHCI_ITDFL_*') */
	__PHYS __uint32_t itd_buf;    /* [in] Page-aligned base address of the buffer (yes: you can only use whole pages for this) */
	__PHYS __uint32_t itd_ntd;    /* [in] Next Transfer Descriptor (or `ed_tp' for end) (16-byte aligned) */
	__PHYS __uint32_t itd_be;     /* [in] Buffer end (or rather: max; as in: last byte written) pointer. */
	__uint16_t        itd_psw[8]; /* [in|out] On input:  Offset to the nth's packet's buffer (s.a. `OHCI_ITDFL_FCM')
	                               *                     MINADDR: itd_buf + itd_of[n]
	                               *                     MAXADDR: IS_LAST_PACKET(n) ? (itd_be) : (itd_buf + itd_of[n + 1] - 1)
	                               *          On output: Buffer status codes (set of `OHCI_ITD_PSW_*') */
};

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_HW_USB_OHCI_H */
