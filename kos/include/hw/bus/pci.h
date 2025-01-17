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
#ifndef _HW_BUS_PCI_H
#define _HW_BUS_PCI_H 1

#include <__stdinc.h>

#include <bits/types.h>
#include <sys/io.h>

#define PCI_ADDR_PORT __IOPORT(0xcf8)
#define PCI_DATA_PORT __IOPORT(0xcfc)

__DECL_BEGIN

#ifdef __CC__
typedef __uint8_t pci_bus_t; /* PCI Bus number. */
typedef __uint8_t pci_dev_t; /* PCI Device number. (Aka. `slot') */
typedef __uint8_t pci_fun_t; /* PCI Function number. */
typedef __uint8_t pci_reg_t; /* PCI Register number (Lowest 2 bits are always ZERO). */
#endif /* __CC__ */

#define PCI_ADDR_FENABLED 0x80000000 /* Address-enabled bit (Must always be set) */
#define PCI_ADDR_BUSMASK  0x00ff0000
#define PCI_ADDR_DEVMASK  0x0000f800
#define PCI_ADDR_FUNMASK  0x00000700
#define PCI_ADDR_FUNCOUNT 8
#define PCI_ADDR_REGMASK  0x000000ff /* Technically `0x000000fc', but lowest 2 bits must always be ZERO. */
#define PCI_ADDR_BUSSHIFT 16
#define PCI_ADDR_DEVSHIFT 11
#define PCI_ADDR_FUNSHIFT 8
#define PCI_ADDR_REGSHIFT 0 /* Assumed to always be ZERO(0). */
#define PCI_ADDR_ALIGN    4 /* 4-byte alignment to always clear lower 2 bits. */
#ifdef __CC__
typedef __uint32_t pci_addr_t; /* PCI Address (Following configuration space mechanism #1) */
#endif /* __CC__ */

/* Build a PCI address using the given arguments.
 * The register number to-be read may then be or'd to the generated number. */
#define PCI_ADDR(bus, dev, fun)                      \
	(__CCAST(pci_addr_t)(bus) << PCI_ADDR_BUSSHIFT | \
	 __CCAST(pci_addr_t)(dev) << PCI_ADDR_DEVSHIFT | \
	 __CCAST(pci_addr_t)(fun) << PCI_ADDR_FUNSHIFT | \
	 PCI_ADDR_FENABLED)
#define PCI_ADDR_GETBUS(x) (((x) & PCI_ADDR_BUSMASK) >> PCI_ADDR_BUSSHIFT)
#define PCI_ADDR_GETDEV(x) (((x) & PCI_ADDR_DEVMASK) >> PCI_ADDR_DEVSHIFT)
#define PCI_ADDR_GETFUN(x) (((x) & PCI_ADDR_FUNMASK) >> PCI_ADDR_FUNSHIFT)
#define PCI_ADDR_GETREG(x) (((x) & PCI_ADDR_REGMASK) >> PCI_ADDR_REGSHIFT)


/* PCI Device data structure (Accessed as registers of any PCI-compliant device). */
#define PCI_DEV0                       0x0 /* Device/Vendor IDs. */
#define    PCI_DEV0_DEVICEMASK         0xffff0000
#define    PCI_DEV0_VENDORMASK         0x0000ffff
#define    PCI_DEV0_DEVICESHIFT        16
#define    PCI_DEV0_VENDORSHIFT        0
#define    PCI_DEV0_DEVICE(x)          (((x) & PCI_DEV0_DEVICEMASK) >> PCI_DEV0_DEVICESHIFT)
#define    PCI_DEV0_VENDOR(x)          ((x) & PCI_DEV0_VENDORMASK)
#define    PCI_DEV0_VENDOR_NODEV       0xffff /* Returned by non-existent devices. */
#define PCI_DEV4                       0x4 /* Status/Command register. */
#define    PCI_DEV4_STAT(x)            (((x) & PCI_DEV4_STATMASK) >> PCI_DEV4_STATSHIFT)
#define    PCI_DEV4_STATMASK           0xffff0000
#define    PCI_DEV4_STATSHIFT          16
#define       PCI_CDEV4_STAT_DETECT_PARITY_ERROR 0x8000 /* Set on parity error. */
#define       PCI_CDEV4_STAT_SIGNAL_SYSTEM_ERROR 0x4000 /* Set when SERR# is asserted. */
#define       PCI_CDEV4_STAT_MASTER_ABORT        0x2000 /* Set by the master when a transaction is aborted with Master-Abort. */
#define       PCI_CDEV4_STAT_TARGET_ABORT        0x1000 /* Set by the master when a transaction is aborted with Target-Abort. */
#define       PCI_CDEV4_STAT_SIGNAL_TARGET_ABORT 0x0800 /* Set when the target terminates a transaction with Target-Abort. */
#define       PCI_CDEV4_STAT_DEVSEL              0x0600 /* Mask for device selection timings. */
#define          PCI_CDEV4_STAT_DEVSEL_LO        0x0400 /* Slow. */
#define          PCI_CDEV4_STAT_DEVSEL_MD        0x0200 /* medium. */
#define          PCI_CDEV4_STAT_DEVSEL_HI        0x0000 /* Fast. */
#define       PCI_CDEV4_STAT_PARITY_ERROR        0x0100 /* Set on parity error when `PCI_CDEV4_PARITIY_ERROR' is enabled. */
#define       PCI_CDEV4_STAT_FAST_B2B            0x0080 /* The device is capable of fast back-to-back transactions. */
#define       PCI_CDEV4_STAT_66MHZ               0x0020 /* The device is capable of running at 66 MHZ rather than 33. */
#define       PCI_CDEV4_STAT_HAVE_CAPLINK_34     0x0010 /* The device implements a capability list as offset 0x34. */
#define       PCI_CDEV4_STAT_IRQ_STATUS          0x0004 /* When set alongside `PCI_CDEV4_NOIRQ' being disabled, interrupts can be generated. */
#define    PCI_DEV4_CMDMASK            0x0000ffff
#define    PCI_DEV4_CMDSHIFT           0
#define       PCI_DEV4_CMD_DISCONNECT  0 /* When written to `PCI_DEV_STATCMD_CMDMASK', disconnect the device from the PCI bus. */
#define       PCI_CDEV4_NOIRQ          0x0400 /* Interrupt disabled. */
#define       PCI_CDEV4_FAST_B2B       0x0200 /* Allow fast back-to-back transactions. */
#define       PCI_CDEV4_SERR_ENABLED   0x0100 /* SERR# Enabled. */
#define       PCI_CDEV4_PARITIY_ERROR  0x0080 /* Set `PCI_CDEV4_STAT_PARITY_ERROR' on parity error. */
#define       PCI_CDEV4_VGA_PALLSNOOP  0x0020 /* Don't respond to VGA palette writes, but snoop data. */
#define       PCI_CDEV4_ALLOW_MEMWRITE 0x0010 /* Allow the device write-access to main memory. */
#define       PCI_CDEV4_SPECIAL_CYCLES 0x0008 /* Allow the device to monitor Special Cycle operations. */
#define       PCI_CDEV4_BUSMASTER      0x0004 /* Allow the device to behave as bus Master. */
#define       PCI_CDEV4_ALLOW_MEMTOUCH 0x0002 /* Allow the device to receive notifications when the CPU touches memory. */
#define       PCI_CDEV4_ALLOW_IOTOUCH  0x0001 /* Allow the device to receive notifications when the CPU writes to I/O space. */
#define PCI_DEV8                       0x8 /* Class code, subclass, Prog IF and Revision ID. */
#define    PCI_DEV8_CLASS(x)           (((x) & PCI_DEV8_CLASSMASK) >> PCI_DEV8_CLASSSHIFT)
#define    PCI_DEV8_CLASSMASK          0xff000000
#define       PCI_DEV8_CLASS_NOCLASS       0x00 /* Device was built prior definition of the class code field. */
#define       PCI_DEV8_CLASS_STORAGE       0x01 /* Mass Storage Controller. */
#define       PCI_DEV8_CLASS_NETWORK       0x02 /* Network Controller. */
#define       PCI_DEV8_CLASS_DISPLAY       0x03 /* Display Controller. */
#define       PCI_DEV8_CLASS_MUMEDIA       0x04 /* Multimedia Controller. */
#define       PCI_DEV8_CLASS_MEMORY        0x05 /* Memory Controller. */
#define       PCI_DEV8_CLASS_BRIDGE        0x06 /* Bridge Device. */
#define       PCI_DEV8_CLASS_COMMUNICATION 0x07 /* Simple Communication Controllers. */
#define       PCI_DEV8_CLASS_SYSPERIPHERAL 0x08 /* Base System Peripherals. */
#define       PCI_DEV8_CLASS_INPUT         0x09 /* Input Devices. */
#define       PCI_DEV8_CLASS_DOCK          0x0a /* Docking Stations. */
#define       PCI_DEV8_CLASS_PROCESSOR     0x0b /* Processors. */
#define       PCI_DEV8_CLASS_SERIAL        0x0c /* Serial Bus Controllers. */
#define       PCI_DEV8_CLASS_WIRELESS      0x0d /* Wireless Controllers. */
#define       PCI_DEV8_CLASS_INTELL_IO     0x0e /* Intelligent I/O Controllers. */
#define       PCI_DEV8_CLASS_SATELLITE     0x0f /* Satellite Communication Controllers. */
#define       PCI_DEV8_CLASS_ENCRYPTION    0x10 /* Encryption/Decryption Controllers. */
#define       PCI_DEV8_CLASS_DATASIGNAL    0x11 /* Data Acquisition and Signal Processing Controllers. */
#define       PCI_DEV8_CLASS_OTHER         0xff /* Device does not fit any defined class. */
#define    PCI_DEV8_SUBCLASS(x)        (((x) & PCI_DEV8_SUBCLASSMASK) >> PCI_DEV8_SUBCLASSSHIFT)
#define    PCI_DEV8_SUBCLASSMASK       0x00ff0000
#define    PCI_DEV8_PROGIF(x)          (((x) & PCI_DEV8_PROGIFMASK) >> PCI_DEV8_PROGIFSHIFT)
#define    PCI_DEV8_PROGIFMASK         0x0000ff00
#define    PCI_DEV8_REVIDMASK          0x000000ff
#define    PCI_DEV8_CLASSSHIFT         24
#define    PCI_DEV8_SUBCLASSSHIFT      16
#define    PCI_DEV8_PROGIFSHIFT        8
#define    PCI_DEV8_REVIDSHIFT         0
#define PCI_DEVC                       0xc
#define    PCI_DEVC_BISTMASK           0xff000000 /* Built-in self test. */
#define       PCI_DEVC_BIST_CAPABLE    0x80 /* FLAG: The device is capable of performing a self-test. */
#define       PCI_DEVC_BIST_START      0x40 /* FLAG: Set to start a self-test. (Unset on completion; When waiting, timeout after 2 seconds) */
#define       PCI_DEVC_BIST_EXITCODE   0x0f /* MASK: Self-test exit code. */
#define       PCI_DEVC_BIST_EXITCODE_OK 0   /* Return value: self-test was successful. */
#define    PCI_DEVC_HEADERMASK         0x00ff0000 /* Header type (Determines layout of register 0x10 onwards). */
#define    PCI_DEVC_HEADER(x)          (((x) & PCI_DEVC_HEADERMASK) >> PCI_DEVC_HEADERSHIFT)
#define       PCI_DEVC_HEADER_GENERIC  0x00 /* General device (PCI_GDEV*). */
#define       PCI_DEVC_HEADER_BRIDGE   0x01 /* PCI-to-PCI bridge (PCI_BDEV*). */
#define       PCI_DEVC_HEADER_CARDBUS  0x02 /* CardBus bridge (PCI_CDEV*). */
/*            PCI_DEVC_HEADER_...      0x03  */
#define       PCI_DEVC_HEADER_TYPEMASK 0x7f /* Mask for device types. */
#define       PCI_DEVC_HEADER_MULTIDEV 0x80 /* FLAG: Set if the device fulfills multiple functions. */
#define    PCI_DEVC_LATENCY_TIMERMASK  0x0000ff00 /* latency timer in units of PCI bus clocks. */
#define    PCI_DEVC_CACHELINESIZEMASK  0x000000ff /* System cache line size. */
#define    PCI_DEVC_BISTSHIFT          24
#define    PCI_DEVC_HEADERSHIFT        16
#define    PCI_DEVC_LATENCY_TIMERSHIFT 8
#define    PCI_DEVC_CACHELINESIZESHIFT 0

/* PCI Header-type (PCI_DEVC_HEADERMASK) specific registers. */
#define PCI_GDEV_BAR0    0x10 /* Base address #0. */
#define PCI_GDEV_BAR1    0x14 /* Base address #1. */
#define PCI_GDEV_BAR2    0x18 /* Base address #2. */
#define PCI_GDEV_BAR3    0x1c /* Base address #3. */
#define PCI_GDEV_BAR4    0x20 /* Base address #4. */
#define PCI_GDEV_BAR5    0x24 /* Base address #5. */
#define PCI_GDEV_CARDCIS 0x28 /* Cardbus CIS Pointer. */
#define PCI_GDEV2C       0x2c /* Subsystem ID / Subsystem Vendor ID. */
#define    PCI_GDEV2C_SSYSIDMASK  0xffff0000
#define    PCI_GDEV2C_VENDORMASK  0x0000ffff
#define    PCI_GDEV2C_SSYSIDSHIFT 16
#define    PCI_GDEV2C_VENDORSHIFT 0
#define PCI_GDEV_EXPROM  0x30 /* Expansion ROM base address. */
#define PCI_GDEV_RES0    0x34 /* Reserved + Capabilities pointer. */
#define    PCI_GDEV_RES0_CAPPTR(x)   (((x) & PCI_GDEV_RES0_CAPPTRMASK) >> PCI_GDEV_RES0_CAPPTRSHIFT)
#define    PCI_GDEV_RES0_CAPPTRMASK  0x000000fc
#define    PCI_GDEV_RES0_CAPPTRSHIFT 0
#define PCI_GDEV_RES1    0x38 /* Reserved. */
#define PCI_GDEV3C       0x3c
#define    PCI_GDEV3C_MAXLATENCY(x)   (((x) & PCI_GDEV3C_MAXLATENCYMASK) >> PCI_GDEV3C_MAXLATENCYSHIFT)
#define    PCI_GDEV3C_MAXLATENCYMASK  0xff000000 /* Specifies how often the device needs access to the PCI bus (in 1/4 microsecond units). */
#define    PCI_GDEV3C_MAXLATENCYSHIFT 24
#define    PCI_GDEV3C_MINGRANT(x)     (((x) & PCI_GDEV3C_MINGRANTMASK) >> PCI_GDEV3C_MINGRANTSHIFT)
#define    PCI_GDEV3C_MINGRANTMASK    0x00ff0000 /* Specifies the burst period length, in 1/4 microsecond units, that the device needs (assuming a 33 MHz clock rate). */
#define    PCI_GDEV3C_MINGRANTSHIFT   16
#define    PCI_GDEV3C_IRQPIN(x)       (((x) & PCI_GDEV3C_IRQPINMASK) > PCI_GDEV3C_IRQPINSHIFT)
#define    PCI_GDEV3C_IRQPINMASK      0x0000ff00 /* Interrupt pin number. */
#define    PCI_GDEV3C_IRQPINSHIFT     8
#define    PCI_GDEV3C_IRQLINE(x)      (((x) & PCI_GDEV3C_IRQLINEMASK) >> PCI_GDEV3C_IRQLINESHIFT)
#define    PCI_GDEV3C_IRQLINEMASK     0x000000ff /* Interrupt line number. */
#define    PCI_GDEV3C_IRQLINESHIFT    0

/* PCI Header-type (PCI_DEVC_HEADER_BRIDGE) specific registers. */
#define PCI_BDEV_BAR0    0x10 /* Base address #0. */
#define PCI_BDEV_BAR1    0x14 /* Base address #1. */
#define PCI_BDEV18       0x18
#define    PCI_BDEV18_SECONDARY_LATENCY_TIMER(x)   (((x) & PCI_BDEV18_SECONDARY_LATENCY_TIMERMASK) >> PCI_BDEV18_SECONDARY_LATENCY_TIMERSHIFT)
#define    PCI_BDEV18_SECONDARY_LATENCY_TIMERMASK  0xff000000
#define    PCI_BDEV18_SUBORDINATE_BUS(x)           (((x) & PCI_BDEV18_SUBORDINATE_BUSMASK) >> PCI_BDEV18_SUBORDINATE_BUSSHIFT)
#define    PCI_BDEV18_SUBORDINATE_BUSMASK          0x00ff0000
#define    PCI_BDEV18_SECONDARY_BUS(x)             (((x) & PCI_BDEV18_SECONDARY_BUSMASK) >> PCI_BDEV18_SECONDARY_BUSSHIFT)
#define    PCI_BDEV18_SECONDARY_BUSMASK            0x0000ff00
#define    PCI_BDEV18_PRIMARY_BUS(x)               ((x) & PCI_BDEV18_PRIMARY_BUSMASK)
#define    PCI_BDEV18_PRIMARY_BUSMASK              0x000000ff
#define    PCI_BDEV18_SECONDARY_LATENCY_TIMERSHIFT 24
#define    PCI_BDEV18_SUBORDINATE_BUSSHIFT         16
#define    PCI_BDEV18_SECONDARY_BUSSHIFT           8
#define    PCI_BDEV18_PRIMARY_BUSSHIFT             0
#define PCI_BDEV1C       0x1c
#define    PCI_BDEV1C_SECONDARY_STATUS(x)    (((x) & PCI_BDEV1C_SECONDARY_STATUSMASK) >> PCI_BDEV1C_SECONDARY_STATUSSHIFT)
#define    PCI_BDEV1C_SECONDARY_STATUSMASK   0xffff0000
#define    PCI_BDEV1C_SECONDARY_STATUSSHIFT  16
#define    PCI_BDEV1C_IOLIMIT(x)             (((x) & PCI_BDEV1C_IOLIMITMASK) >> PCI_BDEV1C_IOLIMITSHIFT)
#define    PCI_BDEV1C_IOLIMITMASK            0x0000ff00
#define    PCI_BDEV1C_IOLIMITSHIFT           8
#define    PCI_BDEV1C_IOBASE(x)              (((x) & PCI_BDEV1C_IOBASEMASK) >> PCI_BDEV1C_IOBASESHIFT)
#define    PCI_BDEV1C_IOBASEMASK             0x000000ff
#define    PCI_BDEV1C_IOBASESHIFT            0
#define PCI_BDEV20       0x20
#define    PCI_BDEV20_MEMLIMIT(x)   (((x) & PCI_BDEV20_MEMLIMITMASK) >> PCI_BDEV20_MEMLIMITSHIFT)
#define    PCI_BDEV20_MEMLIMITMASK  0xffff0000
#define    PCI_BDEV20_MEMLIMITSHIFT 16
#define    PCI_BDEV20_MEMBASE(x)    (((x) & PCI_BDEV20_MEMBASEMASK) >> PCI_BDEV20_MEMBASESHIFT)
#define    PCI_BDEV20_MEMBASEMASK   0x0000ffff
#define    PCI_BDEV20_MEMBASESHIFT  0
#define PCI_BDEV24       0x24
#define    PCI_BDEV24_PREFETCH_MEMLIMIT(x)   (((x) & PCI_BDEV24_PREFETCH_MEMLIMITMASK) >> PCI_BDEV24_PREFETCH_MEMLIMITSHIFT)
#define    PCI_BDEV24_PREFETCH_MEMLIMITMASK  0xffff0000
#define    PCI_BDEV24_PREFETCH_MEMLIMITSHIFT 16
#define    PCI_BDEV24_PREFETCH_MEMBASE(x)    (((x) & PCI_BDEV24_PREFETCH_MEMBASEMASK) >> PCI_BDEV24_PREFETCH_MEMBASESHIFT)
#define    PCI_BDEV24_PREFETCH_MEMBASEMASK   0x0000ffff
#define    PCI_BDEV24_PREFETCH_MEMBASESHIFT  0
#define PCI_BDEV_PREFETCHBASE_HI32  0x28
#define PCI_BDEV_PREFETCHLIMIT_HI32 0x2c
#define PCI_BDEV30 0x30
#define    PCI_BDEV30_IOLIMIT_HI16(x)   (((x) & PCI_BDEV30_IOLIMIT_HI16MASK) >> PCI_BDEV30_IOLIMIT_HI16SHIFT)
#define    PCI_BDEV30_IOLIMIT_HI16MASK  0xffff0000
#define    PCI_BDEV30_IOLIMIT_HI16SHIFT 16
#define    PCI_BDEV30_IOBASE_HI16(x)    (((x) & PCI_BDEV30_IOBASE_HI16MASK) >> PCI_BDEV30_IOBASE_HI16SHIFT)
#define    PCI_BDEV30_IOBASE_HI16MASK   0x0000ffff
#define    PCI_BDEV30_IOBASE_HI16SHIFT  0
#define PCI_BDEV_RES0    0x34 /* Reserved + Capabilities pointer. */
#define    PCI_BDEV_RES0_CAPPTRMASK  0x000000ff
#define    PCI_BDEV_RES0_CAPPTRSHIFT 0
#define PCI_BDEV_EXPROM  0x38 /* Expansion ROM base address. */
#define PCI_BDEV3C       0x3c
#define    PCI_BDEV3C_BRIDGECONTROL(x)   (((x) & PCI_BDEV3C_BRIDGECONTROLMASK) >> PCI_BDEV3C_BRIDGECONTROLSHIFT)
#define    PCI_BDEV3C_BRIDGECONTROLMASK  0xffff0000 /* Bridge control. */
#define    PCI_BDEV3C_BRIDGECONTROLSHIFT 16
#define    PCI_BDEV3C_IRQPINMASK         0x0000ff00 /* Interrupt pin number. */
#define    PCI_BDEV3C_IRQPINSHIFT        8
#define    PCI_BDEV3C_IRQLINEMASK        0x000000ff /* Interrupt line number. */
#define    PCI_BDEV3C_IRQLINESHIFT       0

/* PCI Header-type (PCI_DEVC_HEADER_CARDBUS) specific registers. */
#define PCI_CDEV_SOCKET_BASEADDR  0x10 /* CardBus socket / ExCa base address. */
#define PCI_CDEV14       0x14
#define    PCI_CDEV14_SECONDARY_STATUS(x)    (((x) & PCI_CDEV14_SECONDARY_STATUSMASK) >> PCI_CDEV14_SECONDARY_STATUSSHIFT)
#define    PCI_CDEV14_SECONDARY_STATUSMASK   0xffff0000
#define    PCI_CDEV14_SECONDARY_STATUSSHIFT  16
#define    PCI_CDEV14_CAPPTR(x)              (((x) & PCI_CDEV14_CAPPTRMASK) >> PCI_CDEV14_CAPPTRSHIFT)
#define    PCI_CDEV14_CAPPTRMASK             0x000000ff
#define    PCI_CDEV14_CAPPTRSHIFT            0
#define PCI_CDEV18       0x18
#define    PCI_CDEV18_CARDBUS_LATENCY_TIMER(x)    (((x) & PCI_CDEV18_CARDBUS_LATENCY_TIMERMASK) >> PCI_CDEV18_CARDBUS_LATENCY_TIMERSHIFT)
#define    PCI_CDEV18_CARDBUS_LATENCY_TIMERMASK   0xff000000
#define    PCI_CDEV18_CARDBUS_LATENCY_TIMERSHIFT  24
#define    PCI_CDEV18_SUBORDINATE_BUS(x)          (((x) & PCI_CDEV18_SUBORDINATE_BUSMASK) >> PCI_CDEV18_SUBORDINATE_BUSSHIFT)
#define    PCI_CDEV18_SUBORDINATE_BUSMASK         0x00ff0000
#define    PCI_CDEV18_SUBORDINATE_BUSSHIFT        16
#define    PCI_CDEV18_CARD_BUS(x)                 (((x) & PCI_CDEV18_CARD_BUSMASK) >> PCI_CDEV18_CARD_BUSSHIFT)
#define    PCI_CDEV18_CARD_BUSMASK                0x0000ff00
#define    PCI_CDEV18_CARD_BUSSHIFT               8
#define    PCI_CDEV18_PRIMARY_BUS(x)              ((x) & PCI_CDEV18_PRIMARY_BUSMASK)
#define    PCI_CDEV18_PRIMARY_BUSMASK             0x000000ff
#define    PCI_CDEV18_PRIMARY_BUSSHIFT            0
#define PCI_CDEV_MEMBASE0   0x1c
#define PCI_CDEV_MEMLIMIT0  0x20
#define PCI_CDEV_MEMBASE1   0x24
#define PCI_CDEV_MEMLIMIT1  0x28
#define PCI_CDEV_IOBASE0    0x2c
#define PCI_CDEV_IOLIMIT0   0x30
#define PCI_CDEV_IOBASE1    0x34
#define PCI_CDEV_IOLIMIT1   0x38
#define PCI_CDEV3C          0x3c
#define    PCI_CDEV3C_BRIDGECONTROL(x)   (((x) & PCI_CDEV3C_BRIDGECONTROLMASK) >> PCI_CDEV3C_BRIDGECONTROLSHIFT)
#define    PCI_CDEV3C_BRIDGECONTROLMASK  0xffff0000 /* Bridge control. */
#define    PCI_CDEV3C_BRIDGECONTROLSHIFT 16
#define    PCI_CDEV3C_IRQPIN(x)          (((x) & PCI_CDEV3C_IRQPINMASK) >> PCI_CDEV3C_IRQPINSHIFT)
#define    PCI_CDEV3C_IRQPINMASK         0x0000ff00 /* Interrupt pin number. */
#define    PCI_CDEV3C_IRQPINSHIFT        8
#define    PCI_CDEV3C_IRQLINE(x)         (((x) & PCI_CDEV3C_IRQLINEMASK) >> PCI_CDEV3C_IRQLINESHIFT)
#define    PCI_CDEV3C_IRQLINEMASK        0x000000ff /* Interrupt line number. */
#define    PCI_CDEV3C_IRQLINESHIFT       0
#define PCI_CDEV40          0x40 /* Subsystem ID / Subsystem Vendor ID. */
#define    PCI_CDEV40_SSYSIDMASK  0xffff0000
#define    PCI_CDEV40_VENDORMASK  0x0000ffff
#define    PCI_CDEV40_SSYSIDSHIFT 16
#define    PCI_CDEV40_VENDORSHIFT 0
#define PCI_CDEV_LEGACY_BASEADDR16 0x44 /* 16-bit PC Card legacy mode base address. */

/* Capabilities pointer data layout descriptor. (s.a. `PCI_GDEV_RES0' and `PCI_CDEV4_STAT_HAVE_CAPLINK_34') */
#define PCI_CAPPTR_CAPID(x)      (((x) & PCI_CAPPTR_CAPIDMASK) >> PCI_CAPPTR_CAPIDSHIFT)
#define PCI_CAPPTR_CAPIDMASK     0x000000ff /* Capability ID (one of `PCI_CAPID_*') */
#define PCI_CAPPTR_CAPIDSHIFT    0
#define    PCI_CAPID_AGP         2
#define PCI_CAPPTR_NEXT(x)       (((x) & PCI_CAPPTR_NEXTMASK) >> PCI_CAPPTR_NEXTSHIFT)
#define PCI_CAPPTR_NEXTMASK      0x0000fc00 /* Register index for the next capability */
#define PCI_CAPPTR_NEXTSHIFT     8
#define PCI_CAPPTR_VERSION(x)    (((x) & PCI_CAPPTR_VERSIONMASK) >> PCI_CAPPTR_VERSIONSHIFT)
#define PCI_CAPPTR_VERSIONMASK   0x00ff0000 /* Capability version number */
#define PCI_CAPPTR_VERSIONSHIFT  16


/* BAR data layout descriptor. */
#define PCI_BAR_SPACEMASK     0x00000001 /* BAR address space indicator (one of `PCI_BAR_SPACE_*') */
#define PCI_BAR_SPACESHIFT    0          /* ... */
#define    PCI_BAR_SPACE_MEM  0          /* Physical memory */
#define    PCI_BAR_SPACE_IO   1          /* I/O space */
#define PCI_BAR_SPACEISMEM(x) (((x) & PCI_BAR_SPACEMASK) == (PCI_BAR_SPACE_MEM << PCI_BAR_SPACESHIFT))
#define PCI_MBAR_RESERVED     0x00000002 /* FLAG: Reserved. */
#define PCI_MBAR_64BIT        0x00000004 /* FLAG: 64-bit BAR register (the next BAR is included as part of this bar) */
#define PCI_MBAR_PREFETCHABLE 0x00000008 /* FLAG: Memory may be prefetched */
#define PCI_MBAR_ADDRMASK     0xfffffff0 /* Mask: 16-bit aligned physical memory base address. */
#define PCI_IBAR_ADDRMASK     0xfffffffc /* Mask: 4-bit aligned I/O base address. */


__DECL_END

#endif /* !_HW_BUS_PCI_H */
