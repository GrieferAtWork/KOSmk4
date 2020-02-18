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
#ifndef GUARD_KERNEL_INCLUDE_DRIVERS_PCI_H
#define GUARD_KERNEL_INCLUDE_DRIVERS_PCI_H 1

#include <kernel/compiler.h>

#include <drivers/config.h>

#ifdef CONFIG_HAVE_PCI_DRIVER
#include <kernel/types.h>

#include <hybrid/__assert.h>
#include <hybrid/byteorder.h>
#include <hybrid/sequence/list.h>

#include <kos/io/pci.h>

DECL_BEGIN

#ifdef __CC__
/* Remove from a given PCI address. */
FUNDEF NOBLOCK u32
NOTHROW(FCALL pci_readaddr)(pci_addr_t addr);

/* Write to a given PCI address. */
FUNDEF NOBLOCK void
NOTHROW(FCALL pci_writeaddr)(pci_addr_t addr, u32 value);

FORCELOCAL NOBLOCK u32
NOTHROW(FCALL pci_read)(pci_addr_t base, pci_reg_t reg) {
	__hybrid_assert(!(base & PCI_ADDR_REGMASK));
	return pci_readaddr(base | reg);
}

FORCELOCAL NOBLOCK void NOTHROW(FCALL pci_write)(pci_addr_t base, pci_reg_t reg, u32 value) {
	__hybrid_assert(!(base & PCI_ADDR_REGMASK));
	pci_writeaddr(base | reg, value);
}
#endif /* __CC__ */



#define PCI_RESOURCE_FUNUSED 0x0000 /* Resource isn't being used. */
#define PCI_RESOURCE_FMEM    0x0001 /* Memory resource. */
#define PCI_RESOURCE_FMEM16  0x0002 /* Needs a 16-bit memory address. */
#define PCI_RESOURCE_FMEM32  0x0001 /* Needs a 32-bit memory address. */
#define PCI_RESOURCE_FMEM64  0x0004 /* Needs a 64-bit memory address. */
#define PCI_RESOURCE_FIO     0x8000 /* I/O resource. */
#define PCI_RESOURCE_ISIO(x)    ((x)&PCI_RESOURCE_FIO)
#define PCI_RESOURCE_ISMEM(x) (!((x)&PCI_RESOURCE_FIO))
#ifdef __CC__
struct pci_resource {
	PHYS uintptr_t pr_start; /* Base address of the resource (either in I/O, or in memory) */
	size_t         pr_size;  /* Resource size (in bytes). */
	size_t         pr_align; /* Resource alignment (in bytes). */
	uintptr_t      pr_flags; /* Resource flags (Set of `PCI_RESOURCE_F*'). */
};
#endif /* __CC__ */

/* PCI Resource IDs. */
#define PD_RESOURCE_BAR(i) i
#define PD_RESOURCE_BAR0   0
#define PD_RESOURCE_BAR1   1
#define PD_RESOURCE_BAR2   2
#define PD_RESOURCE_BAR3   3
#define PD_RESOURCE_BAR4   4
#define PD_RESOURCE_BAR5   5
#define PD_RESOURCE_EXPROM 6
#define PD_RESOURCE_COUNT  7
#ifdef __CC__
struct pci_device {
	SLIST_NODE(struct pci_device) pd_chain;      /* Chain of discovered PCI devices. */
	struct pci_resource           pd_res[PD_RESOURCE_COUNT]; /* [const] Resources. */
	pci_addr_t                    pd_base;       /* [const] Base address of this PCI device. */
	union ATTR_PACKED {
		struct ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			u16                  pd_vendorid;   /* Vendor ID. */
			u16                  pd_deviceid;   /* Device ID. */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			u16                  pd_deviceid;   /* Device ID. */
			u16                  pd_vendorid;   /* Vendor ID. */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
		u32                      pd_dev0;       /* Value of the PCI register `PCI_DEV0' */
	};
	union ATTR_PACKED {
		struct ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			u8                   pd_revid;      /* Revision ID. */
			u8                   pd_progifid;   /* Prog-IF ID. */
			u8                   pd_subclassid; /* Device sub-class (One of `PCI_DEV8_CLASS_*') */
			u8                   pd_classid;    /* Device class (One of `PCI_DEV8_CLASS_*') */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			u8                   pd_classid;    /* Device class (One of `PCI_DEV8_CLASS_*') */
			u8                   pd_subclassid; /* Device sub-class (One of `PCI_DEV8_CLASS_*') */
			u8                   pd_progifid;   /* Prog-IF ID. */
			u8                   pd_revid;      /* Revision ID. */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
		u32                      pd_dev8;       /* Value of the PCI register `PCI_DEV8' */
	};
	union ATTR_PACKED {
		struct ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			u8                 __pd_pad0;       /* ... */
			u8                 __pd_pad1;       /* ... */
			u8                   pd_header;     /* PCI_DEVC_HEADERMASK */
			u8                 __pd_pad2;       /* ... */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			u8                 __pd_pad0;       /* ... */
			u8                   pd_header;     /* PCI_DEVC_HEADERMASK */
			u8                 __pd_pad1;       /* ... */
			u8                 __pd_pad2;       /* ... */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
		u32                      pd_devc;       /* Value of the PCI register `PCI_DEVC' */
	};
};
#endif /* __CC__ */


#ifdef __CC__
/* [0..1][const] Linked list of discovered PCI devices. */
DATDEF SLIST(struct pci_device) pci_list;

/* Return a PCI device located at the given
 * `address', or NULL if no such device exists. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED struct pci_device *
NOTHROW(KCALL lookup_pci_device)(pci_addr_t address);

/* Returns the name of a given PCI class `classid', or `NULL' if unknown.
 * @param: classid: One of `PCI_DEV8_CLASS_*'
 * @return: * :   The name of the class.
 * @return: NULL: The name of the class could not be determined. */
FUNDEF ATTR_CONST WUNUSED char const *
NOTHROW(KCALL pci_getclassname)(u8 classid);


/* Enumerate all PCI devices. */
#define PCI_FOREACH(dev) \
	SLIST_FOREACH(dev, pci_list, pd_chain)

/* Enumerate all PCI devices matching the given class and subclass ID. */
#define PCI_FOREACH_CLASS(dev, classid, subclassid) \
	PCI_FOREACH(dev)                                \
	if (!((dev)->pd_classid == (classid) &&         \
	      (dev)->pd_subclassid == (subclassid)));   \
	else

#endif /* __CC__ */


DECL_END

#endif /* CONFIG_HAVE_PCI_DRIVER */

#endif /* !GUARD_KERNEL_INCLUDE_DRIVERS_PCI_H */
