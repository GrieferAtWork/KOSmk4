/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_DRIVERS_PCI_C
#define GUARD_KERNEL_CORE_DRIVERS_PCI_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <drivers/config.h>

#ifdef CONFIG_HAVE_PCI_DRIVER
#include <drivers/pci.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <kernel/types.h>

#include <hybrid/align.h>
#include <hybrid/bit.h>

#include <sys/io.h>

#include <stdlib.h>
#include <string.h>

DECL_BEGIN

/* TODO: Compatibility with Memory mapped PCI (PCI Express; Much faster than I/O ports) */
/* TODO: Compatibility with Configuration Space Access Mechanism #2 */

#define PCI_ADDR_PORT __CCAST(port_t)0xcf8
#define PCI_DATA_PORT __CCAST(port_t)0xcfc

PUBLIC u32 NOTHROW(FCALL pci_readaddr)(pci_addr_t addr) {
	assert(IS_ALIGNED(addr, PCI_ADDR_ALIGN));
	outl(PCI_ADDR_PORT, addr);
	return inl(PCI_DATA_PORT);
}
PUBLIC void NOTHROW(FCALL pci_writeaddr)(pci_addr_t addr, u32 value) {
	assert(IS_ALIGNED(addr, PCI_ADDR_ALIGN));
	outl(PCI_ADDR_PORT, addr);
	outl(PCI_DATA_PORT, value);
}

/* Return a PCI device located at the given
 * `address', or NULL if no such device exists. */
PUBLIC WUNUSED struct pci_device *
NOTHROW(KCALL lookup_pci_device)(pci_addr_t address) {
	struct pci_device *result;
	PCI_FOREACH(result) {
		if (result->pd_base == address)
			break;
	}
	return result;
}


/* [0..1][const] Linked list of discovered PCI devices. */
PUBLIC SLIST(struct pci_device) pci_list = NULL;

PRIVATE ATTR_COLDRODATA char const pci_class_names[][14] = {
	/* [PCI_DEV8_CLASS_STORAGE       - PCI_DEV8_CLASS_STORAGE] = */"storage",
	/* [PCI_DEV8_CLASS_NETWORK       - PCI_DEV8_CLASS_STORAGE] = */"network",
	/* [PCI_DEV8_CLASS_DISPLAY       - PCI_DEV8_CLASS_STORAGE] = */"display",
	/* [PCI_DEV8_CLASS_MUMEDIA       - PCI_DEV8_CLASS_STORAGE] = */"mumedia",
	/* [PCI_DEV8_CLASS_MEMORY        - PCI_DEV8_CLASS_STORAGE] = */"memory",
	/* [PCI_DEV8_CLASS_BRIDGE        - PCI_DEV8_CLASS_STORAGE] = */"bridge",
	/* [PCI_DEV8_CLASS_COMMUNICATION - PCI_DEV8_CLASS_STORAGE] = */"communication",
	/* [PCI_DEV8_CLASS_SYSPERIPHERAL - PCI_DEV8_CLASS_STORAGE] = */"sysperipheral",
	/* [PCI_DEV8_CLASS_INPUT         - PCI_DEV8_CLASS_STORAGE] = */"input",
	/* [PCI_DEV8_CLASS_DOCK          - PCI_DEV8_CLASS_STORAGE] = */"dock",
	/* [PCI_DEV8_CLASS_PROCESSOR     - PCI_DEV8_CLASS_STORAGE] = */"processor",
	/* [PCI_DEV8_CLASS_SERIAL        - PCI_DEV8_CLASS_STORAGE] = */"serial",
	/* [PCI_DEV8_CLASS_WIRELESS      - PCI_DEV8_CLASS_STORAGE] = */"wireless",
	/* [PCI_DEV8_CLASS_INTELL_IO     - PCI_DEV8_CLASS_STORAGE] = */"intell_io",
	/* [PCI_DEV8_CLASS_SATELLITE     - PCI_DEV8_CLASS_STORAGE] = */"satellite",
	/* [PCI_DEV8_CLASS_ENCRYPTION    - PCI_DEV8_CLASS_STORAGE] = */"encryption",
	/* [PCI_DEV8_CLASS_DATASIGNAL    - PCI_DEV8_CLASS_STORAGE] = */"datasignal",
};

PUBLIC WUNUSED char const *
NOTHROW(KCALL pci_getclassname)(u8 classid) {
	if (classid >= PCI_DEV8_CLASS_STORAGE && classid <= PCI_DEV8_CLASS_DATASIGNAL)
		return pci_class_names[classid - 1];
	return NULL;
}



PRIVATE void NOTHROW(KCALL pci_check_function)(pci_addr_t addr);
PRIVATE void NOTHROW(KCALL pci_check_device)(pci_bus_t bus, pci_dev_t dev);
PRIVATE void NOTHROW(KCALL pci_check_bus)(pci_bus_t bus);


PRIVATE ATTR_FREETEXT struct pci_device *
NOTHROW(KCALL RegisterPCIDevice)(pci_addr_t addr) {
	struct pci_device *result;
	u32 maxsize, state;
	struct pci_resource *iter;
	unsigned int i;
	result = NULL;
	TRY {
		result = (struct pci_device *)kmalloc(sizeof(struct pci_device),
		                                      GFP_CALLOC | GFP_LOCKED |
		                                      GFP_PREFLT | GFP_BARELY);
		result->pd_base = addr;
		/* Read fields. */
		result->pd_dev0 = pci_read(addr, PCI_DEV0);
		result->pd_dev8 = pci_read(addr, PCI_DEV8);
		result->pd_devc = pci_read(addr, PCI_DEVC);

		iter = result->pd_res;
		switch (result->pd_header) {

		case PCI_DEVC_HEADER_GENERIC:
			for (i = 0; i < 6; ++i, ++iter) {
				pci_reg_t reg = PCI_GDEV_BAR0 + i * (PCI_GDEV_BAR1 - PCI_GDEV_BAR0);
				state         = pci_read(addr, reg);
				if (!(state & ~0xf))
					continue; /* Unused. */
//				pci_write(addr,reg,(u32)-1);
				maxsize = pci_read(addr, reg);
				if (state & 1) {
					/* I/O range. */
					iter->pr_start = state & ~0x3;
					iter->pr_size  = (~(maxsize & ~0x3)) + 1;
					iter->pr_flags |= PCI_RESOURCE_FIO;
				} else {
					/* Memory range. */
					iter->pr_start = state & ~0xf;
					iter->pr_size  = (~(maxsize & ~0xf)) + 1;
					iter->pr_flags |= PCI_RESOURCE_FMEM;
					iter->pr_flags |= (state & 0x6); /* Memory type. */
					/* A 64-bit memory range takes up 2 BARs. */
					if (iter->pr_flags & PCI_RESOURCE_FMEM64 && !(i & 1))
						++i, ++iter;
				}
				if (iter->pr_size)
					iter->pr_align = 1 << (FFS(iter->pr_size) - 1);
				else
					iter->pr_flags = 0; /* Ignore this case */
				/* Allocate PCI resources */
				if (reg <= PCI_GDEV_BAR5) {
					//TODO: AllocatePCIDeviceRessource(result,iter);
					state = (u32)((state & 1) | iter->pr_start);
#if __SIZEOF_POINTER__ > 4
					if ((iter->pr_flags & PCI_RESOURCE_FMEM64) && !(i & 1)) {
//						pci_write(addr,reg+(PCI_GDEV_BAR1-PCI_GDEV_BAR0),
//						          (u32)((state & 1) | (iter->pr_start >> 32)));
					}
#endif
				}
//				pci_write(addr,reg,state);
			}
			break;

		case PCI_DEVC_HEADER_BRIDGE:
			for (i = 0; i < 2; ++i, ++iter) {
				pci_reg_t reg = PCI_BDEV_BAR0 + i * (PCI_BDEV_BAR1 - PCI_BDEV_BAR0);
				state         = pci_read(addr, reg);
				if (!(state & ~0xf))
					continue; /* Unused. */
//				pci_write(addr,reg,(u32)-1);
				maxsize = pci_read(addr, reg);
				if (state & 1) {
					/* I/O range. */
					iter->pr_start = state & ~0x3;
					iter->pr_size  = (~(maxsize & 0x3)) + 1;
					iter->pr_flags |= PCI_RESOURCE_FIO;
				} else {
					/* Memory range. */
					iter->pr_start = state & ~0xf;
					iter->pr_size  = (~(maxsize & 0xf)) + 1;
					iter->pr_flags |= PCI_RESOURCE_FMEM;
					iter->pr_flags |= (state & 0x6); /* Memory type. */
					/* A 64-bit memory range takes up 2 BARs. */
					if ((iter->pr_flags & PCI_RESOURCE_FMEM64) && !(i & 1))
						++i, ++iter;
				}
				if (iter->pr_size)
					iter->pr_align = 1 << (FFS(iter->pr_size) - 1);
				/* Allocate PCI resources */
				// TODO: AllocatePCIDeviceRessource(result,iter);
				state = (u32)((state & 1) | iter->pr_start);
#if __SIZEOF_POINTER__ > 4
				if ((iter->pr_flags & PCI_RESOURCE_FMEM64) && !(i & 1) &&
				    reg <= PCI_GDEV_BAR5) {
//					pci_write(addr,reg+(PCI_BDEV_BAR1-PCI_BDEV_BAR0),
//					         (u32)((state&1)|(iter->pr_start >> 32)));
				}
#endif
//				pci_write(addr,reg,state);
			}
			break;

		case PCI_DEVC_HEADER_CARDBUS:
			/* XXX: `PCI_CDEV_MEMBASE0' and friends? */
			break;

		default: break;
		}

		{
			char const *class_name;
			class_name = pci_getclassname(result->pd_classid);
			if (!class_name)
				class_name = FREESTR("?");
			printk(FREESTR(KERN_INFO
			               "PCI Device at %I32p located "
			               "(vendor/device %.4I16x:%.4I16x) "
			               "(class: %s:%.2I8x.%.2I8x.%.2I8x.%.2I8x)\n"),
			       addr,
			       result->pd_vendorid,
			       result->pd_deviceid,
			       class_name,
			       result->pd_classid,
			       result->pd_subclassid,
			       result->pd_progifid,
			       result->pd_revid);
		}
		SLIST_INSERT(pci_list, result, pd_chain);
		return result;
	} EXCEPT {
		if (!was_thrown(E_BADALLOC))
			RETHROW();
		printk(FREESTR(KERN_ERR "Failed to allocate descriptor for PCI device\n"));
		kfree(result);
		result = NULL;
	}
	return NULL;
}


PRIVATE ATTR_FREETEXT void
NOTHROW(KCALL pci_check_function)(pci_addr_t addr) {
	struct pci_device *dev;
	if (lookup_pci_device(addr))
		return; /* Already registered. */
	dev = RegisterPCIDevice(addr);
	if (!dev)
		return;
	if (dev->pd_classid == PCI_DEV8_CLASS_BRIDGE/* &&
	    dev->pd_subclassid == PCI_DEV8_CLASS_MUMEDIA*/) {
		/* Recursively enumerate a bridge device. */
		pci_check_bus(PCI_BDEV18_SECONDARY_BUS(pci_read(addr, PCI_BDEV18)));
	}
}
PRIVATE ATTR_FREETEXT void
NOTHROW(KCALL pci_check_device)(pci_bus_t bus, pci_dev_t dev) {
	pci_addr_t addr = PCI_ADDR(bus, dev, 0);
	if (PCI_DEV0_VENDOR(pci_read(addr, PCI_DEV0)) == PCI_DEV0_VENDOR_NODEV)
		return;
	pci_check_function(addr);
	if (PCI_DEVC_HEADER(pci_read(addr, PCI_DEVC)) &
	    PCI_DEVC_HEADER_MULTIDEV) {
		u8 i; /* Recursively check secondary functions of a multi-device. */
		for (i = 0; i < PCI_ADDR_FUNCOUNT; ++i, addr += 1 << PCI_ADDR_FUNSHIFT) {
			if (PCI_DEV0_VENDOR(pci_read(addr, PCI_DEV0)) == PCI_DEV0_VENDOR_NODEV)
				continue;
			pci_check_function(addr);
		}
	}
}
PRIVATE ATTR_FREETEXT void
NOTHROW(KCALL pci_check_bus)(pci_bus_t bus) {
	u8 device;
	for (device = 0; device < 32; device++)
		pci_check_device(bus, device);
}

INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_pci_driver)(void) {

	/* TODO: Check if PCI is even available? */
	/* TODO: Check which Configuration Space Access Mechanism can/must be used. */

	/* Perform a simple PCI device discovery. */
#if 1
	/* Recursive scanner. */
	u32 resp = pci_read(PCI_ADDR(0, 0, 0), PCI_DEVC);
	if (PCI_DEVC_HEADER(resp) & PCI_DEVC_HEADER_MULTIDEV) {
		/* Single controller. */
		pci_check_bus(0);
	} else {
		/* Multiple controllers. */
		pci_fun_t fun = 0;
		for (; fun < PCI_ADDR_FUNCOUNT; ++fun) {
			pci_addr_t addr = PCI_ADDR(0, 0, fun);
			if (PCI_DEV0_VENDOR(pci_read(addr, PCI_DEV0)) == PCI_DEV0_VENDOR_NODEV)
				continue;
			pci_check_bus(addr);
		}
	}
#else
	/* Brute-force scanner (TODO: Add a commandline option for this). */
	u8 bus = 0;
	for (;;) {
		check_bus(bus);
		if (bus == 0xff)
			break;
		++bus;
	}
#endif
}


DECL_END

#endif /* CONFIG_HAVE_PCI_DRIVER */

#endif /* !GUARD_KERNEL_CORE_DRIVERS_PCI_C */
