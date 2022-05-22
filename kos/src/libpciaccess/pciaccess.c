/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.removeif([](x) -> x.startswith("-O"));
gcc_opt.append("-O3"); // Force-enable optimizations (mainly for faster pci.ids scanning)
]]]*/
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBPCIACCESS_PCIACCESS_C
#define GUARD_LIBPCIACCESS_PCIACCESS_C 1
#define LIBPHYS_WANT_PROTOTYPES

#include "api.h"

#include <hybrid/compiler.h>

#include <hybrid/align.h>
#include <hybrid/bit.h>
#include <hybrid/overflow.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/unaligned.h>

#include <hw/bus/pci.h>
#include <kos/except.h>
#include <kos/types.h>
#include <sys/io.h>
#include <sys/param.h>

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <libpciaccess/pciaccess.h>
#include <libphys/phys.h>

#ifdef __KERNEL__
#include <kernel/malloc.h>
#include <kernel/printk.h>
#endif /* __KERNEL__ */

/**/
#include "pciaccess.h"

#ifndef __KERNEL__
#define USER_TRY         NESTED_TRY
#define USER_EXCEPT(...) EXCEPT { __VA_ARGS__; }
#else /* !__KERNEL__ */
#define USER_TRY         /* nothing */
#define USER_EXCEPT(...) /* nothing */
#endif /* __KERNEL__ */


DECL_BEGIN

/************************************************************************/
/* Low-level PCI address space accessor functions.                      */
/* NOTE: In user-space, these can throw E_ILLEGAL_INSTRUCTION           */
/************************************************************************/

typedef uint32_t (CC *PPCI_RDADDR)(pciaddr_t addr);
typedef void (CC *PPCI_WRADDR)(pciaddr_t addr, uint32_t value);

/* Dynamically dispatch these functions, since there are 2 ways to implement them! */
PRIVATE PPCI_RDADDR pdyn_pci_rdaddr = NULL;
PRIVATE PPCI_WRADDR pdyn_pci_wraddr = NULL;
#define pci_rdaddr (*pdyn_pci_rdaddr)
#define pci_wraddr (*pdyn_pci_wraddr)

/************************************************************************/
/* Configuration #1                                                     */
PRIVATE uint32_t CC conf1_pci_rdaddr(pciaddr_t addr) {
	assert(IS_ALIGNED(addr, PCI_ADDR_ALIGN));
	outl(PCI_ADDR_PORT, addr);
	return inl(PCI_DATA_PORT);
}
PRIVATE void CC conf1_pci_wraddr(pciaddr_t addr, uint32_t value) {
	assert(IS_ALIGNED(addr, PCI_ADDR_ALIGN));
	outl(PCI_ADDR_PORT, addr);
	outl(PCI_DATA_PORT, value);
}
/************************************************************************/


/************************************************************************/
/* Configuration #2                                                     */
PRIVATE uint32_t CC conf2_pci_rdaddr(pciaddr_t addr) {
	port_t port;
	uint32_t result;
	uint8_t dev, reg, bus, fun;
	assert(IS_ALIGNED(addr, PCI_ADDR_ALIGN));
	dev  = (addr & PCI_ADDR_DEVMASK) >> PCI_ADDR_DEVSHIFT;
	reg  = (addr & PCI_ADDR_REGMASK) >> PCI_ADDR_REGSHIFT;
	bus  = (addr & PCI_ADDR_BUSMASK) >> PCI_ADDR_BUSSHIFT;
	fun  = (addr & PCI_ADDR_FUNMASK) >> PCI_ADDR_FUNSHIFT;
	port = (port_t)(0xc000 | (dev << 8) | reg);
	outb((port_t)0xcf8, 0xf0 | (fun << 1));
	outb((port_t)0xcfa, bus);
	result = inl(port);
	outb((port_t)0xcf8, 0);
	return result;
}

PRIVATE void CC conf2_pci_wraddr(pciaddr_t addr, uint32_t value) {
	port_t port;
	uint8_t dev, reg, bus, fun;
	assert(IS_ALIGNED(addr, PCI_ADDR_ALIGN));
	dev  = (addr & PCI_ADDR_DEVMASK) >> PCI_ADDR_DEVSHIFT;
	reg  = (addr & PCI_ADDR_REGMASK) >> PCI_ADDR_REGSHIFT;
	bus  = (addr & PCI_ADDR_BUSMASK) >> PCI_ADDR_BUSSHIFT;
	fun  = (addr & PCI_ADDR_FUNMASK) >> PCI_ADDR_FUNSHIFT;
	port = (port_t)(0xc000 | (dev << 8) | reg);
	outb((port_t)0xcf8, 0xf0 | (fun << 1));
	outb((port_t)0xcfa, bus);
	outl(port, value);
	outb((port_t)0xcf8, 0);
}
/************************************************************************/


#ifdef __KERNEL__
ATTR_FREETEXT
#endif /* __KERNEL__ */
PRIVATE WUNUSED errno_t NOTHROW(CC conf1_probe)(void) {
	errno_t result = ENODEV;
	USER_TRY {
		uint32_t saved;
		outb((port_t)0xcfb, 0x01); /* ??? */
		saved = inl(PCI_ADDR_PORT);
		outl(PCI_ADDR_PORT, PCI_ADDR_FENABLED);
		if (inl(PCI_ADDR_PORT) == PCI_ADDR_FENABLED)
			result = EOK;
		outl(PCI_ADDR_PORT, saved);
	}
	USER_EXCEPT(result = EACCES)
	return result;
}


#ifdef __KERNEL__
ATTR_FREETEXT
#endif /* __KERNEL__ */
PRIVATE WUNUSED errno_t NOTHROW(CC conf2_probe)(void) {
	errno_t result = ENODEV;
	USER_TRY {
		outb((port_t)0xcfb, 0);
		outb((port_t)0xcf8, 0);
		outb((port_t)0xcfa, 0);
		if (inb((port_t)0xcf8) == 0 && inb((port_t)0xcfa) == 0)
			result = EOK;
	}
	USER_EXCEPT(result = EACCES)
	return result;
}


/************************************************************************/
/* PCI Device listing                                                   */
/************************************************************************/
DECL_END

#define RBTREE_LEFT_LEANING
#define RBTREE_OMIT_REMOVE
#define RBTREE_OMIT_REMOVENODE
#define RBTREE(name)           pcidev_tree_##name
#define RBTREE_T               struct pci_device
#define RBTREE_Tkey            pciaddr_t
#define RBTREE_GETLHS(self)    (self)->_pd_next_lo
#define RBTREE_GETRHS(self)    (self)->_pd_next_hi
#define RBTREE_SETLHS(self, v) (void)((self)->_pd_next_lo = (v))
#define RBTREE_SETRHS(self, v) (void)((self)->_pd_next_hi = (v))
#define RBTREE_GETKEY(self)    (self)->pd_addr
#define RBTREE_REDFIELD        _pd_tree_rd
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN

#ifndef __pci_device_slist_defined
#define __pci_device_slist_defined
SLIST_HEAD(pci_device_slist, pci_device);
#endif /* !__pci_device_slist_defined */


#ifndef __libpci_devices_defined
#define __libpci_devices_defined
#ifdef __KERNEL__
DEFINE_PUBLIC_ALIAS(pci_devices, libpci_devices);
INTERN
#else /* __KERNEL__ */
PRIVATE
#endif /* !__KERNEL__ */
/* [0..n][const] List of PCI devices. (random order) */
struct pci_device_slist libpci_devices = SLIST_HEAD_INITIALIZER(libpci_devices);
#endif /* !__libpci_devices_defined */

/* [0..n][const] Tree of PCI devices. (lookup via `pd_addr') */
PRIVATE LLRBTREE_ROOT(pci_device) libpci_devices_tree = NULL;

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(pci_devices, libpci_devices_getter);
INTERN ATTR_CONST WUNUSED struct pci_device *
NOTHROW(LIBPCIACCESS_CC libpci_devices_getter)(void) {
	return SLIST_FIRST(&libpci_devices);
}
#endif /* !__KERNEL__ */




/************************************************************************/
/* Search for attached PCI devices.                                     */
/************************************************************************/
#ifdef __KERNEL__
#define DECLARE_SCAN_FUNCTION(name, ...) \
	PRIVATE FREE void NOTHROW(CC name)(__VA_ARGS__)
#define BEGIN_SCAN_FUNCTION(name, ...) \
	PRIVATE ATTR_FREETEXT void NOTHROW(CC name)(__VA_ARGS__)
#define END_SCAN_FUNCTION        /* nothing */
#define CALL_SCAN_FUNCTION(expr) expr
#else /* __KERNEL__ */
#define DECLARE_SCAN_FUNCTION(name, ...) \
	PRIVATE WUNUSED errno_t NOTHROW(CC name)(__VA_ARGS__)
#define BEGIN_SCAN_FUNCTION(name, ...) \
	PRIVATE WUNUSED errno_t NOTHROW(CC name)(__VA_ARGS__) {
#define END_SCAN_FUNCTION \
		return EOK;       \
	}
#define CALL_SCAN_FUNCTION(expr)           \
	do {                                   \
		errno_t error;                     \
		if unlikely((error = (expr)) != 0) \
			return error;                  \
	}	__WHILE0
#endif /* !__KERNEL__ */


DECLARE_SCAN_FUNCTION(pci_scan_function, pciaddr_t addr);
DECLARE_SCAN_FUNCTION(pci_scan_device, pciaddr_t addr);
DECLARE_SCAN_FUNCTION(pci_scan_bus, pciaddr_t addr);
DECLARE_SCAN_FUNCTION(pci_scan_system, void);



BEGIN_SCAN_FUNCTION(pci_scan_function, pciaddr_t addr) {
	/* Check if a device has already been registered. */
	if (pcidev_tree_locate(libpci_devices_tree, addr) == NULL) {
		struct pci_device *dev;
#ifdef __KERNEL__
		dev = (struct pci_device *)kmalloc(sizeof(struct pci_device),
		                                   GFP_LOCKED | GFP_PREFLT);
#else /* __KERNEL__ */
		dev = (struct pci_device *)malloc(sizeof(struct pci_device));
		if unlikely(!dev)
			return ENOMEM;
#endif /* !__KERNEL__ */
		dev->pd_addr = addr;

		/* Probe the features of the device. */
#ifdef __KERNEL__
		libpci_device_probe(dev);
#else /* __KERNEL__ */
		{
			errno_t error;
			error = libpci_device_probe(dev);
			if unlikely(error != EOK) {
				free(dev);
				return error;
			}
		}
#endif /* !__KERNEL__ */

#ifdef __KERNEL__
		/* Write a system log entry for the detected device. */
		printk(FREESTR(KERN_INFO
		               "[pci] Device at %" PRIp32 " located "
		               "[vendor:%#.4" PRIx16 ",%#.4" PRIx16 ","
		               " device:%#.4" PRIx16 ",%#.4" PRIx16 ","
		               " class:%#.2" PRIx8 ".%#.2" PRIx8 ".%#.2" PRIx8 ".%#.2" PRIx8 "]\n"),
		       dev->pd_addr,
		       dev->pd_vendor_id, dev->pd_subvendor_id,
		       dev->pd_device_id, dev->pd_subdevice_id,
		       dev->pd_class_id, dev->pd_subclass_id,
		       dev->pd_progif_id, dev->pd_revision);
#endif /* __KERNEL__ */

		/* Insert the device into the tree of known devices. */
		pcidev_tree_insert(&libpci_devices_tree, dev);
		SLIST_INSERT(&libpci_devices, dev, _pd_link);
		if ((dev->pd_header_type & PCI_DEVC_HEADER_TYPEMASK) == PCI_DEVC_HEADER_BRIDGE ||
		    (dev->pd_header_type & PCI_DEVC_HEADER_TYPEMASK) == PCI_DEVC_HEADER_CARDBUS) {
			/* Recursively enumerate a bridge devices. */
			uint32_t bdev18 = pci_rdaddr(addr | PCI_BDEV18);
			uint8_t bus     = PCI_BDEV18_SECONDARY_BUS(bdev18);
			CALL_SCAN_FUNCTION(pci_scan_bus(PCI_ADDR(bus, 0, 0)));
		}
	}
}
END_SCAN_FUNCTION

BEGIN_SCAN_FUNCTION(pci_scan_device, pciaddr_t addr) {
	uint32_t dev0 = pci_rdaddr(addr | PCI_DEV0);
	if (PCI_DEV0_VENDOR(dev0) != PCI_DEV0_VENDOR_NODEV) {
		uint32_t devc;
		CALL_SCAN_FUNCTION(pci_scan_function(addr));
		devc = pci_rdaddr(addr | PCI_DEVC);
		if (PCI_DEVC_HEADER(devc) & PCI_DEVC_HEADER_MULTIDEV) {
			unsigned int i; /* Recursively check secondary functions of a multi-device. */
			for (i = 0; i < PCI_ADDR_FUNCOUNT; ++i, addr += 1 << PCI_ADDR_FUNSHIFT) {
				dev0 = pci_rdaddr(addr | PCI_DEV0);
				if (PCI_DEV0_VENDOR(dev0) != PCI_DEV0_VENDOR_NODEV) {
					CALL_SCAN_FUNCTION(pci_scan_function(addr));
				}
			}
		}
	}
}
END_SCAN_FUNCTION

BEGIN_SCAN_FUNCTION(pci_scan_bus, pciaddr_t addr) {
	uint8_t dev;
	for (dev = 0; dev < 32; dev++) {
		CALL_SCAN_FUNCTION(pci_scan_device(addr | (dev << PCI_ADDR_DEVSHIFT)));
	}
}
END_SCAN_FUNCTION

BEGIN_SCAN_FUNCTION(pci_scan_system, void) {
	USER_TRY {
		uint32_t resp = pci_rdaddr(PCI_ADDR(0, 0, 0) | PCI_DEVC);
		if (PCI_DEVC_HEADER(resp) & PCI_DEVC_HEADER_MULTIDEV) {
			/* Single controller. */
			CALL_SCAN_FUNCTION(pci_scan_bus(PCI_ADDR(0, 0, 0)));
		} else {
			/* Multiple controllers. */
			pci_fun_t fun = 0;
			for (; fun < PCI_ADDR_FUNCOUNT; ++fun) {
				pciaddr_t addr = PCI_ADDR(0, 0, fun);
				uint32_t dev0  = pci_rdaddr(addr | PCI_DEV0);
				if (PCI_DEV0_VENDOR(dev0) == PCI_DEV0_VENDOR_NODEV)
					continue;
				CALL_SCAN_FUNCTION(pci_scan_bus(PCI_ADDR(fun, 0, 0)));
			}
		}
	}
	USER_EXCEPT(return EACCES)
}
END_SCAN_FUNCTION






/* PCI System initialization.
 * NOTE: These functions  are  really  only  of  interest  to  user-space.
 *       Within the kernel, `pci_system_init()' isn't exported to drivers,
 *       and  is unconditionally called during system boot initialization. */
#ifdef __KERNEL__
DEFINE_INTERN_ALIAS(pci_system_init, libpci_system_init);
INTERN ATTR_FREETEXT void NOTHROW(CC libpci_system_init)(void)
#else /* __KERNEL__ */
DEFINE_PUBLIC_ALIAS(pci_system_init, libpci_system_init);
INTERN errno_t NOTHROW(CC libpci_system_init)(void)
#endif /* !__KERNEL__ */
{
#ifndef __KERNEL__
	errno_t error;
	/* Return immediately when already initialized. */
	if (libpci_devices_tree != NULL)
		return EOK;

	/* Enable I/O permissions access for all ports. */
	{
		errno_t saved_errno;
		saved_errno = errno;
		if (iopl(3) != 0) {
			error = errno;
			errno = saved_errno;
			return error;
		}
	}
#endif /* !__KERNEL__ */

	/* Check configuration method #1 */
#ifdef __KERNEL__
	if (conf1_probe() == EOK)
#else /* __KERNEL__ */
	if ((error = conf1_probe()) == EOK)
#endif /* !__KERNEL__ */
	{
		pdyn_pci_rdaddr = &conf1_pci_rdaddr;
		pdyn_pci_wraddr = &conf1_pci_wraddr;
#ifdef __KERNEL__
		printk(FREESTR(KERN_INFO "[pci] Using configuration method #1\n"));
#endif /* __KERNEL__ */
	} else

	/* Check configuration method #2 */
#ifdef __KERNEL__
	if (conf2_probe() == EOK)
#else /* __KERNEL__ */
	if ((error = conf2_probe()) == EOK)
#endif /* !__KERNEL__ */
	{
		pdyn_pci_rdaddr = &conf2_pci_rdaddr;
		pdyn_pci_wraddr = &conf2_pci_wraddr;
#ifdef __KERNEL__
		printk(FREESTR(KERN_INFO "[pci] Using configuration method #2\n"));
#endif /* __KERNEL__ */
	} else {
#ifndef __KERNEL__
		return error;
#else /* !__KERNEL__ */
		printk(FREESTR(KERN_NOTICE "[pci] Unsupported\n"));
		return;
#endif /* __KERNEL__ */
	}

	/* Enumerate PCI devices. */
#ifdef __KERNEL__
	pci_scan_system();
#else /* __KERNEL__ */
	if ((error = pci_scan_system()) != EOK) {
		libpci_system_cleanup();
		return error;
	}
#endif /* !__KERNEL__ */

	/* Done! */
#ifndef __KERNEL__
	return EOK;
#endif /* !__KERNEL__ */
}

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(pci_system_init_dev_mem, libpci_system_init_dev_mem);
INTERN void NOTHROW(CC libpci_system_init_dev_mem)(fd_t fd) {
	/* We  use libphys for /dev/mem access, but  we will make use of `fd'
	 * in case our program is otherwise unable to access /dev/mem through
	 * normal means (useful in case our caller acquired `fd' through some
	 * unconventional methods, such as a unix domain socket) */
	if (fd != -1 && getdevmem() == -1)
		setdevmem(fd);
	libpci_system_init();
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(CC pci_device_destroy)(struct pci_device *__restrict self) {
	unsigned int i;

	/* Cleanup lazy mappings of physical memory. */
	for (i = 0; i < COMPILER_LENOF(self->pd_regions); ++i) {
		if (self->pd_regions[i].pmr_memory != NULL) {
			munmapphys(self->pd_regions[i].pmr_memory,
			           self->pd_regions[i].pmr_size);
		}
	}

	/* Free dynamically allocated data. */
	free(self->_pd_info_agp);
	free(self->_pd_info_bridge);
	free(self->_pd_info_pcmcia_bridge);
	free(self);
}

DEFINE_PUBLIC_ALIAS(pci_system_cleanup, libpci_system_cleanup);
INTERN NOBLOCK void NOTHROW(CC libpci_system_cleanup)(void) {
	/* Cleanup the list of known PCI devices. */
	libpci_devices_tree = NULL;
	while (!SLIST_EMPTY(&libpci_devices)) {
		struct pci_device *dev;
		dev = SLIST_FIRST(&libpci_devices);
		SLIST_REMOVE_HEAD(&libpci_devices, _pd_link);
		pci_device_destroy(dev);
	}

	/* Disable I/O permissions access for all ports. */
	iopl(0);
}
#endif /* !__KERNEL__ */



/************************************************************************/
/* PCI Device search API.                                               */
/************************************************************************/
PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) bool
NOTHROW(CC iterator_matches_device)(struct pci_device_iterator const *__restrict self,
                                    struct pci_device const *__restrict dev) {
	if (!PCI_ID_COMPARE(self->pdi_vendor_id, dev->pd_vendor_id))
		goto nope;
	if (!PCI_ID_COMPARE(self->pdi_device_id, dev->pd_device_id))
		goto nope;
	if (!PCI_ID_COMPARE(self->pdi_subvendor_id, dev->pd_subvendor_id))
		goto nope;
	if (!PCI_ID_COMPARE(self->pdi_subdevice_id, dev->pd_subdevice_id))
		goto nope;
	if ((dev->pd_device_class & self->pdi_device_class_mask) != self->pdi_device_class)
		goto nope;
#ifndef __KERNEL__
	if (!PCI_ID_COMPARE(self->pdi_func, dev->pd_func))
		goto nope;
	if (!PCI_ID_COMPARE(self->pdi_dev, dev->pd_dev))
		goto nope;
	if (!PCI_ID_COMPARE(self->pdi_bus, dev->pd_bus))
		goto nope;
#endif /* !__KERNEL__ */
	return true;
nope:
	return false;
}


#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(pci_slot_match_iterator_init, libpci_slot_match_iterator_init);
INTERN NONNULL((1)) void
NOTHROW(CC libpci_slot_match_iterator_init)(struct pci_device_iterator *__restrict self,
                                            struct pci_slot_match const *match) {
	self->pdi_next = SLIST_FIRST(&libpci_devices);
	self->pdi_device_class      = 0;
	self->pdi_device_class_mask = 0;
	self->pdi_vendor_id         = PCI_MATCH_ANY;
	self->pdi_device_id         = PCI_MATCH_ANY;
	self->pdi_subvendor_id      = PCI_MATCH_ANY;
	self->pdi_subdevice_id      = PCI_MATCH_ANY;
	if (match) {
		self->pdi_func = match->psm_func;
		self->pdi_dev  = match->psm_dev;
		self->pdi_bus  = match->psm_bus;
		if (self->pdi_func <= 7 && self->pdi_dev <= 31 && self->pdi_bus <= 0xff) {
			struct pci_device *dev;
			pciaddr_t addr;
			addr = (self->pdi_func << 8) |
			       (self->pdi_dev << 11) |
			       (self->pdi_bus << 16);
			dev = pcidev_tree_locate(libpci_devices_tree, addr);
			if (dev) {
				/* Set-up impossible device class requirements (there is no `x', such that `(x & 0) == 1') */
				self->pdi_device_class      = 1;
				self->pdi_device_class_mask = 0;

				/* Have the first call to `pci_device_next()' return the requested device. */
				self->pdi_next = dev;
				return;
			}
		}

		/* Scan for the first matching device. */
		while (self->pdi_next && !iterator_matches_device(self, self->pdi_next))
			self->pdi_next = SLIST_NEXT(self->pdi_next, _pd_link);
	} else {
		self->pdi_func = PCI_MATCH_ANY;
		self->pdi_dev  = PCI_MATCH_ANY;
		self->pdi_bus  = PCI_MATCH_ANY;
	}
}
#endif /* !__KERNEL__ */

DEFINE_PUBLIC_ALIAS(pci_id_match_iterator_init, libpci_id_match_iterator_init);
INTERN NONNULL((1)) void
NOTHROW(CC libpci_id_match_iterator_init)(struct pci_device_iterator *__restrict self,
                                          struct pci_id_match const *match) {
	self->pdi_next = SLIST_FIRST(&libpci_devices);
	if (match) {
		self->pdi_device_class      = match->pim_device_class;
		self->pdi_device_class_mask = match->pim_device_class_mask;
		self->pdi_vendor_id         = match->pim_vendor_id;
		self->pdi_device_id         = match->pim_device_id;
		self->pdi_subvendor_id      = match->pim_subvendor_id;
		self->pdi_subdevice_id      = match->pim_subdevice_id;
		while (self->pdi_next && !iterator_matches_device(self, self->pdi_next))
			self->pdi_next = SLIST_NEXT(self->pdi_next, _pd_link);
	} else {
		self->pdi_device_class      = 0;
		self->pdi_device_class_mask = 0;
		self->pdi_vendor_id         = PCI_MATCH_ANY;
		self->pdi_device_id         = PCI_MATCH_ANY;
		self->pdi_subvendor_id      = PCI_MATCH_ANY;
		self->pdi_subdevice_id      = PCI_MATCH_ANY;
	}
#ifndef __KERNEL__
	self->pdi_func = PCI_MATCH_ANY;
	self->pdi_dev  = PCI_MATCH_ANY;
	self->pdi_bus  = PCI_MATCH_ANY;
#endif /* !__KERNEL__ */
}

DEFINE_PUBLIC_ALIAS(pci_device_next, libpci_device_next);
#ifdef __KERNEL__
INTERN WUNUSED NONNULL((1)) struct pci_device *
NOTHROW(CC libpci_device_next)(/*[1..1]*/ struct pci_device_iterator *__restrict iter)
#else /* __KERNEL__ */
INTERN WUNUSED struct pci_device *
NOTHROW(CC libpci_device_next)(/*[0..1]*/ struct pci_device_iterator *iter)
#endif /* !__KERNEL__ */
{
	struct pci_device *result, *next;
#ifndef __KERNEL__
	if unlikely(!iter)
		return NULL;
#endif /* !__KERNEL__ */
	result = iter->pdi_next;
	if (result) {
		/* Load the next device that should be enumerated. */
		for (next = SLIST_NEXT(result, _pd_link); next; next = SLIST_NEXT(next, _pd_link)) {
			if (iterator_matches_device(iter, next))
				break;
		}
		iter->pdi_next = next;
	}
	return result;
}

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(pci_slot_match_iterator_create, libpci_slot_match_iterator_create);
INTERN ATTR_MALLOC WUNUSED struct pci_device_iterator *
NOTHROW(CC libpci_slot_match_iterator_create)(struct pci_slot_match const *match) {
	struct pci_device_iterator *result;
	result = (struct pci_device_iterator *)malloc(sizeof(struct pci_device_iterator));
	if likely(result)
		libpci_slot_match_iterator_init(result, match);
	return result;
}

DEFINE_PUBLIC_ALIAS(pci_id_match_iterator_create, libpci_id_match_iterator_create);
INTERN ATTR_MALLOC WUNUSED struct pci_device_iterator *
NOTHROW(CC libpci_id_match_iterator_create)(struct pci_id_match const *match) {
	struct pci_device_iterator *result;
	result = (struct pci_device_iterator *)malloc(sizeof(struct pci_device_iterator));
	if likely(result)
		libpci_id_match_iterator_init(result, match);
	return result;
}

DEFINE_PUBLIC_ALIAS(pci_iterator_destroy, libpci_iterator_destroy);
INTERN NOBLOCK void
NOTHROW(CC libpci_iterator_destroy)(/*[0..1]*/ struct pci_device_iterator *iter) {
	free(iter);
}
#endif /* !__KERNEL__ */



/************************************************************************/
/* PCI Device API functions.                                            */
/************************************************************************/

/* (Re-)initialize the given PCI device. The caller is responsible
 * to  fill  in  `self->pd_addr'  before  calling  this  function. */
DEFINE_PUBLIC_ALIAS(pci_device_probe, libpci_device_probe);
#ifdef __KERNEL__
INTERN NONNULL((1)) void
#else /* __KERNEL__ */
INTERN NONNULL((1)) errno_t
#endif /* !__KERNEL__ */
NOTHROW(CC libpci_device_probe)(struct pci_device *__restrict self) {
	USER_TRY {
		pciaddr_t addr;
		uint32_t devc, dev4_bits;
		uint8_t romreg;
		unsigned int i, barcount;
		addr = self->pd_addr;
		bzero(self, sizeof(*self));
		self->pd_addr = addr;

		/* Simple fields... */
		self->pd_dev0 = pci_rdaddr(addr | PCI_DEV0);
		self->pd_dev8 = pci_rdaddr(addr | PCI_DEV8);
#ifndef __KERNEL__
		self->pd_domain = UINT32_C(0xffffffff);
#endif /* !__KERNEL__ */

		/* Fill in device-dependent information. */
		devc                  = pci_rdaddr(addr | PCI_DEVC);
		barcount              = 0;
		self->pd_irq          = -1;
		romreg                = 0xff;
		self->pd_subvendor_id = PCI_DEV0_VENDOR_NODEV;
		self->pd_subdevice_id = PCI_DEV0_VENDOR_NODEV;
		self->pd_header_type  = PCI_DEVC_HEADER(devc);
		switch (self->pd_header_type & PCI_DEVC_HEADER_TYPEMASK) {
		case PCI_DEVC_HEADER_GENERIC: {
			uint32_t dev3c;
			self->pd_gdev2c = pci_rdaddr(addr | PCI_GDEV2C);
			dev3c           = pci_rdaddr(addr | PCI_GDEV3C);
			self->pd_irq    = PCI_GDEV3C_IRQLINE(dev3c);
			barcount        = 6;
			romreg          = PCI_GDEV_EXPROM;
		}	break;

		case PCI_DEVC_HEADER_BRIDGE:
			barcount = 2;
			romreg   = PCI_BDEV_EXPROM;
			break;

		case PCI_DEVC_HEADER_CARDBUS:
			barcount = 1;
			break;

		default:
			break;
		}

		/* Load ROM memory location information. */
		dev4_bits = 0;
		if (romreg != 0xff) {
			uint32_t val1, val2;
			val1 = pci_rdaddr(addr | romreg);
			pci_wraddr(addr | romreg, UINT32_C(0xfffff800));
			val2 = pci_rdaddr(addr | romreg);
			self->pd_rom_size = (~val2) + 1;
			self->pd_rom_base = val1 & val2;
			if (self->pd_rom_size != 0)
				val1 |= 1; /* Enable the address decode */
			pci_wraddr(addr | romreg, val1);

			/* Enable memory access notifications for the device. */
			dev4_bits |= PCI_CDEV4_ALLOW_MEMTOUCH;
		}

		/* Load device BARs */
		for (i = 0; i < barcount; ++i) {
			pciaddr_t baraddr = addr | (PCI_GDEV_BAR0 + (i * (PCI_GDEV_BAR1 - PCI_GDEV_BAR0)));
			uint32_t val1, val2;
			val1 = pci_rdaddr(baraddr);
			pci_wraddr(baraddr, UINT32_C(0xffffffff));
			val2 = pci_rdaddr(baraddr);
			pci_wraddr(baraddr, val1);
			if (PCI_BAR_SPACEISMEM(val1)) {
				if (val1 & PCI_MBAR_PREFETCHABLE)
					self->pd_regions[i].pmr_is_prefetchable = 1;
				if (val1 & PCI_MBAR_64BIT) {
					self->pd_regions[i].pmr_is_64 = 1;
					++i; /* This one consumes 2 BARs! */
				}
				val1 &= PCI_MBAR_ADDRMASK;
				val2 &= PCI_MBAR_ADDRMASK;
				dev4_bits |= PCI_CDEV4_ALLOW_MEMTOUCH;
			} else {
				self->pd_regions[i].pmr_is_IO = 1;
				val1 &= PCI_IBAR_ADDRMASK;
				val2 &= PCI_IBAR_ADDRMASK;
				dev4_bits |= PCI_CDEV4_ALLOW_IOTOUCH;
			}
			val2 = (~val2) + 1;
			if unlikely(!IS_POWER_OF_TWO(val2)) {
				/* NOTE: `IS_POWER_OF_TWO(0) == true', so we don't get here when `val2 == 0' */
				val2 = (uint32_t)1 << CTZ(val2);
			}
			self->pd_regions[i].pmr_addr = val1;
			self->pd_regions[i].pmr_size = val2;
		}

		/* Enable requested device feature bits. */
		if (dev4_bits != 0) {
			uint32_t dev4;
			dev4 = pci_rdaddr(addr | PCI_DEV4);
			if ((dev4 & dev4_bits) != dev4_bits)
				pci_wraddr(addr | PCI_DEV4, dev4 | dev4_bits);
		}
	}
	USER_EXCEPT(return EACCES)
#ifndef __KERNEL__
	return EOK;
#endif /* !__KERNEL__ */
}

/* Lookup a device, given its exact address. */
DEFINE_PUBLIC_ALIAS(pci_device_byaddr, libpci_device_byaddr);
INTERN ATTR_PURE WUNUSED struct pci_device *
NOTHROW(CC libpci_device_byaddr)(pciaddr_t addr) {
	return pcidev_tree_locate(libpci_devices_tree, addr);
}

/* Fill in information about bridge bus indices (s.a. `PCI_ADDR_BUSMASK') */
DEFINE_PUBLIC_ALIAS(pci_device_get_bridge_buses, libpci_device_get_bridge_buses);
INTERN WUNUSED NONNULL((1, 2, 3, 4)) errno_t
NOTHROW(CC libpci_device_get_bridge_buses)(struct pci_device const *__restrict self,
                                           int *__restrict primary_bus,
                                           int *__restrict secondary_bus,
                                           int *__restrict subordinate_bus) {
	*primary_bus     = -1;
	*secondary_bus   = -1;
	*subordinate_bus = -1;
	if (self->pd_class_id != PCI_DEV8_CLASS_BRIDGE)
		return ENODEV;
	*primary_bus = self->pd_bus;
	switch (self->pd_header_type & PCI_DEVC_HEADER_TYPEMASK) {

	case PCI_DEVC_HEADER_BRIDGE:
	case PCI_DEVC_HEADER_CARDBUS: {
		uint32_t bdev18;
		USER_TRY {
			bdev18 = pci_rdaddr(self->pd_addr | PCI_BDEV18);
		}
		USER_EXCEPT(return EACCES)
		*primary_bus     = PCI_BDEV18_PRIMARY_BUS(bdev18);
		*secondary_bus   = PCI_BDEV18_SECONDARY_BUS(bdev18);
		*subordinate_bus = PCI_BDEV18_SUBORDINATE_BUS(bdev18);
	}	break;

	default:
		break;
	}
	return EOK;
}

/* Lookup bridge device information. */
DEFINE_PUBLIC_ALIAS(pci_device_getinfo_agp, libpci_device_getinfo_agp);
INTERN WUNUSED NONNULL((1, 2)) errno_t
NOTHROW(CC libpci_device_getinfo_agp)(struct pci_device const *__restrict self,
                                      struct pci_agp_info *__restrict result) {
	USER_TRY {
		uint32_t dev4;
		uint8_t capptr;
		byte_t visited_offsets[CEILDIV((0xff + 1) / 4, NBBY)];
#define VISITED_OFFSETS_OP(capptr, op) \
	(visited_offsets[((capptr) / 4) / NBBY] op (1 << (((capptr) / 4) % NBBY)))

		/* Check if the device has a capabilities pointer at offset 0x34 */
		dev4 = pci_rdaddr(self->pd_addr | PCI_DEV4);
		if (!(PCI_DEV4_STAT(dev4) & PCI_CDEV4_STAT_HAVE_CAPLINK_34))
			return ENOSYS; /* Not supported */
		capptr = PCI_GDEV_RES0_CAPPTR(pci_rdaddr(self->pd_addr | 0x34));
		bzero(visited_offsets, sizeof(visited_offsets));
		visited_offsets[0] = 1 | 2 | 4 | 8; /* The first 4 control words can't be capabilities (because they're PCI_DEV0...PCI_DEVC) */
		while (!VISITED_OFFSETS_OP(capptr, &)) {
			uint32_t capword;
			VISITED_OFFSETS_OP(capptr, |=);
			capword = pci_rdaddr(self->pd_addr | capptr);
			if (PCI_CAPPTR_CAPID(capword) == PCI_CAPID_AGP) {
				result->pai_config_offset = capptr;
				result->pai_cfg2          = PCI_CAPPTR_VERSION(capword);
				result->_pai_cfg4_mod     = pci_rdaddr(self->pd_addr | (capptr + 4));
				if (result->pai_rates & 0x8) /* AGP3 support */
					result->pai_rates <<= 2;
				result->pai_async_req_size           = 4 + (1 << ((result->_pai_cfg4_mod & 0xe000) >> 13));
				result->pai_calibration_cycle_timing = (result->_pai_cfg4_mod & 0x1c00) >> 10;
				result->pai_max_requests             = 1 + ((result->_pai_cfg4_mod & 0xff000000) >> 24);
				return EOK;
			}
			capptr = PCI_CAPPTR_NEXT(capword);
		}
#undef VISITED_OFFSETS_OP
	}
	USER_EXCEPT(return EACCES)
	return ENOSYS;
}

DEFINE_PUBLIC_ALIAS(pci_device_getinfo_bridge, libpci_device_getinfo_bridge);
INTERN WUNUSED NONNULL((1, 2)) errno_t
NOTHROW(CC libpci_device_getinfo_bridge)(struct pci_device const *__restrict self,
                                         struct pci_bridge_info *__restrict result) {
	if ((self->pd_header_type & PCI_DEVC_HEADER_TYPEMASK) != PCI_DEVC_HEADER_BRIDGE)
		return ENOENT;
	USER_TRY {
		/* Read in bridge control words. */
		uint32_t bdev18 = pci_rdaddr(self->pd_addr | PCI_BDEV18);
		uint32_t bdev1c = pci_rdaddr(self->pd_addr | PCI_BDEV1C);
		uint32_t bdev20 = pci_rdaddr(self->pd_addr | PCI_BDEV20);
		uint32_t bdev24 = pci_rdaddr(self->pd_addr | PCI_BDEV24);
		uint32_t bdev30 = pci_rdaddr(self->pd_addr | PCI_BDEV30);
		uint32_t bdev3c = pci_rdaddr(self->pd_addr | PCI_BDEV3C);

		/* Extract information bits. */
		result->pbi_primary_bus             = PCI_BDEV18_PRIMARY_BUS(bdev18);
		result->pbi_secondary_bus           = PCI_BDEV18_SECONDARY_BUS(bdev18);
		result->pbi_subordinate_bus         = PCI_BDEV18_SUBORDINATE_BUS(bdev18);
		result->pbi_secondary_latency_timer = PCI_BDEV18_SECONDARY_LATENCY_TIMER(bdev18);
		result->pbi_io_type                 = PCI_BDEV1C_IOBASE(bdev1c) & 0xf;
		result->pbi_mem_type                = PCI_BDEV20_MEMBASE(bdev20) & 0xf;
		result->pbi_prefetch_mem_type       = PCI_BDEV24_PREFETCH_MEMBASE(bdev24) & 0xf;
		result->pbi_secondary_status        = PCI_BDEV1C_SECONDARY_STATUS(bdev1c);
		result->pbi_bridge_control          = PCI_BDEV3C_BRIDGECONTROL(bdev3c);
		result->pbi_io_base                 = ((PCI_BDEV1C_IOBASE(bdev1c) & 0xf0) << 8) | (PCI_BDEV30_IOBASE_HI16(bdev30) << 16);
		result->pbi_io_limit                = 0xfff | ((PCI_BDEV1C_IOLIMIT(bdev1c) & 0xf0) << 8) | (PCI_BDEV30_IOLIMIT_HI16(bdev30) << 16);
		result->pbi_mem_base                = (PCI_BDEV20_MEMBASE(bdev20) & 0xfff0) << 16;
		result->pbi_mem_limit               = 0xfff | (PCI_BDEV20_MEMLIMIT(bdev20) & 0xf0) << 16;

		/* Prefetch information is a bit more complicated. */
		result->pbi_prefetch_mem_base = (uint64_t)((PCI_BDEV24_PREFETCH_MEMBASE(bdev24) & 0xfff0) << 16) |
		                                ((uint64_t)pci_rdaddr(self->pd_addr | PCI_BDEV_PREFETCHBASE_HI32) << 32);
		result->pbi_prefetch_mem_limit = (uint64_t)(0xfff | (PCI_BDEV24_PREFETCH_MEMLIMIT(bdev24) & 0xf0) << 16) |
		                                 ((uint64_t)pci_rdaddr(self->pd_addr | PCI_BDEV_PREFETCHLIMIT_HI32) << 32);
	}
	USER_EXCEPT(EACCES)
	return EOK;
}

DEFINE_PUBLIC_ALIAS(pci_device_getinfo_pcmcia_bridge, libpci_device_getinfo_pcmcia_bridge);
INTERN WUNUSED NONNULL((1, 2)) errno_t
NOTHROW(CC libpci_device_getinfo_pcmcia_bridge)(struct pci_device const *__restrict self,
                                                struct pci_pcmcia_bridge_info *__restrict result) {
	if ((self->pd_header_type & PCI_DEVC_HEADER_TYPEMASK) != PCI_DEVC_HEADER_CARDBUS)
		return ENOENT;
	USER_TRY {
		/* Read in bridge control words. */
		uint32_t cdev14 = pci_rdaddr(self->pd_addr | PCI_CDEV14);
		uint32_t cdev18 = pci_rdaddr(self->pd_addr | PCI_CDEV18);
		uint32_t cdev3c = pci_rdaddr(self->pd_addr | PCI_CDEV3C);

		/* Extract information bits. */
		result->pcbi_primary_bus           = PCI_CDEV18_PRIMARY_BUS(cdev18);
		result->pcbi_card_bus              = PCI_CDEV18_CARD_BUS(cdev18);
		result->pcbi_subordinate_bus       = PCI_CDEV18_SUBORDINATE_BUS(cdev18);
		result->pcbi_cardbus_latency_timer = PCI_CDEV18_CARDBUS_LATENCY_TIMER(cdev18);
		result->pcbi_secondary_status      = PCI_CDEV14_SECONDARY_STATUS(cdev14);
		result->pcbi_bridge_control        = PCI_CDEV3C_BRIDGECONTROL(cdev3c);
		result->pcbi_mem[0].m_base         = pci_rdaddr(self->pd_addr | PCI_CDEV_MEMBASE0);
		result->pcbi_mem[0].m_limit        = pci_rdaddr(self->pd_addr | PCI_CDEV_MEMLIMIT0);
		result->pcbi_mem[1].m_base         = pci_rdaddr(self->pd_addr | PCI_CDEV_MEMBASE1);
		result->pcbi_mem[1].m_limit        = pci_rdaddr(self->pd_addr | PCI_CDEV_MEMLIMIT1);
		result->pcbi_io[0].i_base          = pci_rdaddr(self->pd_addr | PCI_CDEV_IOBASE0);
		result->pcbi_io[0].i_limit         = pci_rdaddr(self->pd_addr | PCI_CDEV_IOLIMIT0);
		result->pcbi_io[1].i_base          = pci_rdaddr(self->pd_addr | PCI_CDEV_IOBASE1);
		result->pcbi_io[1].i_limit         = pci_rdaddr(self->pd_addr | PCI_CDEV_IOLIMIT1);
	}
	USER_EXCEPT(EACCES)
	return EOK;
}

DEFINE_PUBLIC_ALIAS(pci_device_get_parent_bridge, libpci_device_get_parent_bridge);
#ifdef __KERNEL__
INTERN WUNUSED NONNULL((1)) struct pci_device *
NOTHROW(CC libpci_device_get_parent_bridge)(struct pci_device const *__restrict self)
#else /* __KERNEL__ */
INTERN WUNUSED struct pci_device *
NOTHROW(CC libpci_device_get_parent_bridge)(/*[0..1]*/ struct pci_device const *self)
#endif /* !__KERNEL__ */
{
	struct pci_device *iter;
#ifndef __KERNEL__
	if unlikely(!self)
		return NULL;
#endif /* !__KERNEL__ */
	SLIST_FOREACH (iter, &libpci_devices, _pd_link) {
		if ((iter->pd_header_type & PCI_DEVC_HEADER_TYPEMASK) != PCI_DEVC_HEADER_BRIDGE)
			continue;
		/* Search for a the appropriate PCI device. */
		USER_TRY {
			uint32_t bdev18 = pci_rdaddr(iter->pd_addr | PCI_BDEV18);
			if (PCI_BDEV18_SECONDARY_BUS(bdev18) == self->pd_bus)
				return iter;
		}
		USER_EXCEPT(NULL)
	}
	return NULL;
}

#ifndef __KERNEL__
/* Map or unmap a specific PCI device region into memory. The given physical address range
 * must be given such that it is a  clean sub-region of exactly one of the device's  BARs.
 * @param: map_flags: Set of `PCI_DEV_MAP_FLAG_*' */
DEFINE_PUBLIC_ALIAS(pci_device_map_range, libpci_device_map_range);
INTERN WUNUSED NONNULL((1, 5)) errno_t
NOTHROW(CC libpci_device_map_range)(struct pci_device *__restrict self, physaddr_t base,
                                    size_t size, unsigned int map_flags, void **__restrict paddr) {
	unsigned int i;
	if unlikely(!self)
		return EFAULT;
	for (i = 0;; ++i) {
		if (i >= COMPILER_LENOF(self->pd_regions))
			return ENOENT;
		if (self->pd_regions[i].pmr_is_IO)
			continue;
		if (base >= self->pd_regions[i].pmr_addr &&
		    base < (self->pd_regions[i].pmr_addr +
		            self->pd_regions[i].pmr_size)) {
			if ((base + size) < base ||
			    (base + size) > (self->pd_regions[i].pmr_addr +
			                     self->pd_regions[i].pmr_size))
				return E2BIG;
			/* Found it! */
			break;
		}
	}
	return libpci_device_map_legacy(self, base, size, map_flags, paddr);
}

DEFINE_PUBLIC_ALIAS(pci_device_unmap_range, libpci_device_unmap_legacy);
DEFINE_INTERN_ALIAS(libpci_device_unmap_range, libpci_device_unmap_legacy);

/* Same as `pci_device_map_range()', but don't check that the given range actually belongs
 * to a single BAR of the given device. As a matter of fact, `self' isn't actually used by
 * these functions...
 * @param: map_flags: Set of `PCI_DEV_MAP_FLAG_*' */
DEFINE_PUBLIC_ALIAS(pci_device_map_legacy, libpci_device_map_legacy);
INTERN WUNUSED NONNULL((5)) errno_t
NOTHROW(CC libpci_device_map_legacy)(struct pci_device *self, physaddr_t base,
                                     size_t size, unsigned int map_flags, void **__restrict paddr) {
	errno_t saved_errno;
	void *addr;
	if unlikely(!self)
		return EFAULT;
	(void)map_flags;
	saved_errno = errno;
	addr        = mmapphys(base, size);
	if unlikely(addr == MAP_FAILED) {
		errno_t error;
		error = errno;
		errno = saved_errno;
		return error;
	}
	*paddr = addr;
	return EOK;
}

DEFINE_PUBLIC_ALIAS(pci_device_unmap_legacy, libpci_device_unmap_legacy);
INTERN WUNUSED NONNULL((2)) errno_t
NOTHROW(CC libpci_device_unmap_legacy)(struct pci_device *self,
                                       void *memory, size_t size) {
	if unlikely(!self)
		return EFAULT;
	munmapphys(memory, size);
	return EOK;
}

/* Wrappers for `pci_device_getinfo_*()' */
DEFINE_PUBLIC_ALIAS(pci_device_get_agp_info, libpci_device_get_agp_info);
INTERN WUNUSED NONNULL((1)) struct pci_agp_info const *
NOTHROW(CC libpci_device_get_agp_info)(struct pci_device *__restrict self) {
	if (!self->_pd_info_agp) {
		struct pci_agp_info info, *infop;
		if (libpci_device_getinfo_agp(self, &info) == EOK &&
		    (infop = (struct pci_agp_info *)malloc(sizeof(struct pci_agp_info))) != NULL)
			self->_pd_info_agp = (struct pci_agp_info *)memcpy(infop, &info, sizeof(info));
	}
	return self->_pd_info_agp;
}

DEFINE_PUBLIC_ALIAS(pci_device_get_bridge_info, libpci_device_get_bridge_info);
INTERN WUNUSED NONNULL((1)) struct pci_bridge_info const *
NOTHROW(CC libpci_device_get_bridge_info)(struct pci_device *__restrict self) {
	if (!self->_pd_info_bridge) {
		struct pci_bridge_info info, *infop;
		if (libpci_device_getinfo_bridge(self, &info) == EOK &&
		    (infop = (struct pci_bridge_info *)malloc(sizeof(struct pci_bridge_info))) != NULL)
			self->_pd_info_bridge = (struct pci_bridge_info *)memcpy(infop, &info, sizeof(info));
	}
	return self->_pd_info_bridge;
}

DEFINE_PUBLIC_ALIAS(pci_device_get_pcmcia_bridge_info, libpci_device_get_pcmcia_bridge_info);
INTERN WUNUSED NONNULL((1)) struct pci_pcmcia_bridge_info const *
NOTHROW(CC libpci_device_get_pcmcia_bridge_info)(struct pci_device *__restrict self) {
	if (!self->_pd_info_pcmcia_bridge) {
		struct pci_pcmcia_bridge_info info, *infop;
		if (libpci_device_getinfo_pcmcia_bridge(self, &info) == EOK &&
		    (infop = (struct pci_pcmcia_bridge_info *)malloc(sizeof(struct pci_pcmcia_bridge_info))) != NULL)
			self->_pd_info_pcmcia_bridge = (struct pci_pcmcia_bridge_info *)memcpy(infop, &info, sizeof(info));
	}
	return self->_pd_info_pcmcia_bridge;
}


/* Copy the given device's ROM into the provided buffer. */
DEFINE_PUBLIC_ALIAS(pci_device_read_rom, libpci_device_read_rom);
INTERN WUNUSED errno_t
NOTHROW(CC libpci_device_read_rom)(struct pci_device const *self, void *buffer) {
	if (!self || !buffer)
		return EFAULT;
	copyfromphys(buffer, self->pd_rom_base, self->pd_rom_size);
	return EOK;
}

/* No-op (for now) */
DEFINE_PUBLIC_ALIAS(pci_device_enable, libpci_device_enable);
INTERN NONNULL((1)) void
NOTHROW(CC libpci_device_enable)(struct pci_device *__restrict self) {
	COMPILER_IMPURE();
	(void)self;
}

/* Check if this is the boot VGA device. (returning non-zero if that is the case) */
DEFINE_PUBLIC_ALIAS(pci_device_is_boot_vga, libpci_device_is_boot_vga);
INTERN WUNUSED NONNULL((1)) int
NOTHROW(CC libpci_device_is_boot_vga)(struct pci_device const *__restrict self) {
	COMPILER_IMPURE();
	(void)self;
	return 0;
}

/* Check if a driver is attached to the given device. (returning non-zero if that is the case) */
DEFINE_PUBLIC_ALIAS(pci_device_has_kernel_driver, libpci_device_has_kernel_driver);
INTERN WUNUSED NONNULL((1)) int
NOTHROW(CC libpci_device_has_kernel_driver)(struct pci_device const *__restrict self) {
	COMPILER_IMPURE();
	(void)self;
	return 0;
}
#endif /* !__KERNEL__ */


/* Read/Write to/from the configuration space of a given PCI device. */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(pci_device_cfg_read, libpci_device_cfg_read);
INTERN NONNULL((1, 2)) errno_t
NOTHROW_NCX(CC libpci_device_cfg_read)(struct pci_device const *__restrict self,
                                       void *data, uint8_t offset, uint8_t size,
                                       /*[0..1]*/ pciaddr_t *bytes_read) {
	ssize_t result;
	result = libpci_device_readcfg(self, data, offset, size);
	if (result < 0)
		return -(errno_t)result;
	if (bytes_read)
		*bytes_read = (pciaddr_t)(size_t)result;
	return EOK;
}

DEFINE_PUBLIC_ALIAS(pci_device_cfg_write, libpci_device_cfg_write);
INTERN NONNULL((1, 2)) errno_t
NOTHROW_NCX(CC libpci_device_cfg_write)(struct pci_device *__restrict self,
                                        void const *data, uint8_t offset, uint8_t size,
                                        /*[0..1]*/ pciaddr_t *bytes_written) {
	ssize_t result;
	result = libpci_device_writecfg(self, data, offset, size);
	if (result < 0)
		return -(errno_t)result;
	if (bytes_written)
		*bytes_written = (pciaddr_t)(size_t)result;
	return EOK;
}

DEFINE_PUBLIC_ALIAS(pci_device_cfg_read_u8, libpci_device_cfg_read_u8);
INTERN NONNULL((1, 2)) errno_t
NOTHROW(CC libpci_device_cfg_read_u8)(struct pci_device const *__restrict self,
                                      uint8_t *__restrict data, uint8_t reg) {
	uint32_t word;
	NESTED_TRY {
		word = pci_rdaddr(self->pd_addr | (reg & ~3));
	} EXCEPT {
		return EACCES;
	}
	word >>= (reg & 3) * 8;
	*data = (uint8_t)word;
	return EOK;
}

DEFINE_PUBLIC_ALIAS(pci_device_cfg_read_u16, libpci_device_cfg_read_u16);
INTERN NONNULL((1, 2)) errno_t
NOTHROW(CC libpci_device_cfg_read_u16)(struct pci_device const *__restrict self,
                                       uint16_t *__restrict data, uint8_t reg) {
	if likely((reg & 1) == 0) {
		uint32_t word;
		NESTED_TRY {
			word = pci_rdaddr(self->pd_addr | (reg & ~3));
		} EXCEPT {
			return EACCES;
		}
		word >>= (reg & 2) * 8;
		*data = (uint16_t)word;
	} else {
		union {
			uint16_t w;
			uint8_t b[2];
		} word;
		errno_t error;
		error = libpci_device_cfg_read_u8(self, &word.b[0], reg);
		if unlikely(error != EOK)
			return error;
		error = libpci_device_cfg_read_u8(self, &word.b[1], reg + 1);
		if unlikely(error != EOK)
			return error;
		*data = word.w;
	}
	return EOK;
}

DEFINE_PUBLIC_ALIAS(pci_device_cfg_read_u32, libpci_device_cfg_read_u32);
INTERN NONNULL((1, 2)) errno_t
NOTHROW(CC libpci_device_cfg_read_u32)(struct pci_device const *__restrict self,
                                       uint32_t *__restrict data, uint8_t reg) {
	if likely((reg & 3) == 0) {
		uint32_t word;
		NESTED_TRY {
			word = pci_rdaddr(self->pd_addr | reg);
		} EXCEPT {
			return EACCES;
		}
		*data = word;
	} else {
		union {
			uint32_t l;
			uint16_t w[2];
		} word;
		errno_t error;
		error = libpci_device_cfg_read_u16(self, &word.w[0], reg);
		if unlikely(error != EOK)
			return error;
		error = libpci_device_cfg_read_u16(self, &word.w[1], reg + 2);
		if unlikely(error != EOK)
			return error;
		*data = word.l;
	}
	return EOK;
}

DEFINE_PUBLIC_ALIAS(pci_device_map_region, libpci_device_map_region);
INTERN NONNULL((1)) errno_t
NOTHROW(CC libpci_device_map_region)(struct pci_device *__restrict self,
                                     unsigned int bar_index, int write_enable) {
	if (bar_index >= 6 || self->pd_regions[bar_index].pmr_size == 0)
		return ENOENT;
	if (self->pd_regions[bar_index].pmr_memory != NULL)
		return EOK;
	return libpci_device_map_memory_range(self, self->pd_regions[bar_index].pmr_addr,
	                                      self->pd_regions[bar_index].pmr_size, write_enable,
	                                      &self->pd_regions[bar_index].pmr_memory);
}

DEFINE_PUBLIC_ALIAS(pci_device_unmap_region, libpci_device_unmap_region);
INTERN errno_t
NOTHROW(CC libpci_device_unmap_region)(struct pci_device *self,
                                       unsigned int bar_index) {
	errno_t result;
	if unlikely(!self)
		return EFAULT;
	if (bar_index >= 6 || self->pd_regions[bar_index].pmr_size == 0)
		return ENOENT;
	result = libpci_device_unmap_memory_range(self,
	                                          self->pd_regions[bar_index].pmr_memory,
	                                          self->pd_regions[bar_index].pmr_size);
	if likely(result == EOK) {
		self->pd_regions[bar_index].pmr_memory = NULL;
	}
	return result;
}

DEFINE_PUBLIC_ALIAS(pci_device_map_memory_range, libpci_device_map_memory_range);
INTERN NONNULL((1, 5)) errno_t
NOTHROW(CC libpci_device_map_memory_range)(struct pci_device *__restrict self,
                                           physaddr_t base, size_t size,
                                           int write_enable, void **__restrict paddr) {
	return libpci_device_map_range(self, base, size,
	                               write_enable ? PCI_DEV_MAP_FLAG_WRITABLE : 0,
	                               paddr);
}

DEFINE_PUBLIC_ALIAS(pci_device_unmap_memory_range, libpci_device_unmap_range);
DEFINE_INTERN_ALIAS(libpci_device_unmap_memory_range, libpci_device_unmap_range);
#endif /* !__KERNEL__ */



DEFINE_PUBLIC_ALIAS(pci_device_readcfg, libpci_device_readcfg);
#ifdef __KERNEL__
INTERN NONNULL((1, 2)) size_t
#else /* __KERNEL__ */
INTERN NONNULL((1, 2)) ssize_t
#endif /* !__KERNEL__ */
NOTHROW_NCX(CC libpci_device_readcfg)(struct pci_device const *__restrict self,
                                      void *data, uint8_t offset, uint8_t size) {
	size_t result = 0;
	USER_TRY {
		if (offset & 3) {
			uint32_t word = pci_rdaddr(self->pd_addr | (offset & ~3));
			uint8_t bytes = 4 - (offset & 3);
			if (bytes > size)
				bytes = size;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			word >>= (offset & 3) * 8;
#endif  /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			memcpy(data, &word, bytes);
			result += bytes;
			if (bytes >= size)
				goto done;
			data = (byte_t *)data + bytes;
			size -= bytes;
			if (OVERFLOW_UADD(offset, bytes, &offset))
				goto done;
		}
		while (size >= 4) {
			uint32_t word = pci_rdaddr(self->pd_addr | offset);
			UNALIGNED_SET32((uint32_t *)data, word);
			result += 4;
			if (OVERFLOW_UADD(offset, 4, &offset))
				goto done;
			data = (byte_t *)data + 4;
			size -= 4;
		}
		if (size) {
			uint32_t word = pci_rdaddr(self->pd_addr | offset);
			memcpy(data, &word, size);
			result += size;
		}
	}
	USER_EXCEPT(return -except_as_errno(except_data()))
done:
	return result;
}


DEFINE_PUBLIC_ALIAS(pci_device_writecfg, libpci_device_writecfg);
#ifdef __KERNEL__
INTERN NONNULL((1, 2)) size_t
#else /* __KERNEL__ */
INTERN NONNULL((1, 2)) ssize_t
#endif /* !__KERNEL__ */
NOTHROW_NCX(CC libpci_device_writecfg)(struct pci_device *__restrict self,
                                       void const *data, uint8_t offset, uint8_t size) {
	size_t result = 0;
	USER_TRY {
		if (offset & 3) {
			uint32_t word;
			uint8_t bytes = 4 - (offset & 3);
			word = pci_rdaddr(self->pd_addr | (offset & ~3));
			if (bytes > size)
				bytes = size;
			memcpy((byte_t *)&word + (offset & 3), data, bytes);
			pci_wraddr(self->pd_addr | (offset & ~3), word);
			result += bytes;
			if (bytes >= size)
				goto done;
			data = (byte_t const *)data + bytes;
			size -= bytes;
			if (OVERFLOW_UADD(offset, bytes, &offset))
				goto done;
		}
		while (size >= 4) {
			uint32_t word;
			word = UNALIGNED_GET32((uint32_t const *)data);
			pci_wraddr(self->pd_addr | offset, word);
			result += 4;
			if (OVERFLOW_UADD(offset, 4, &offset))
				goto done;
			data = (byte_t const *)data + 4;
			size -= 4;
		}
		if (size) {
			uint32_t word;
			word = pci_rdaddr(self->pd_addr | offset);
			memcpy(&word, data, size);
			pci_wraddr(self->pd_addr | offset, word);
			result += size;
		}
	}
	USER_EXCEPT(return -except_as_errno(except_data()))
done:
	return result;
}


/* In user-space, these functions will return 0xff[ff[ffff]] on error and set errno to non-zero */
DEFINE_PUBLIC_ALIAS(pci_device_cfg_readb, libpci_device_cfg_readb);
INTERN NONNULL((1)) uint8_t
NOTHROW(CC libpci_device_cfg_readb)(struct pci_device const *__restrict self, uint8_t reg) {
	uint8_t result;
	USER_TRY {
		uint32_t word;
		word = pci_rdaddr(self->pd_addr | (reg & ~3));
		word >>= (reg & 3) * 8;
		result = (uint8_t)(word & UINT8_C(0xff));
	}
	USER_EXCEPT(result = UINT8_C(0xff))
	return result;
}

DEFINE_PUBLIC_ALIAS(pci_device_cfg_readw, libpci_device_cfg_readw);
INTERN NONNULL((1)) uint16_t
NOTHROW(CC libpci_device_cfg_readw)(struct pci_device const *__restrict self, uint8_t reg) {
	if likely((reg & 1) == 0) {
		uint32_t word;
		USER_TRY {
			word = pci_rdaddr(self->pd_addr | (reg & ~3));
		}
		USER_EXCEPT(return UINT16_C(0xffff))
		word >>= (reg & 2) * 8;
		return (uint16_t)word;
	} else {
		union {
			uint16_t w;
			uint8_t b[2];
		} word;
		word.b[0] = libpci_device_cfg_readb(self, reg + 0);
		word.b[1] = libpci_device_cfg_readb(self, reg + 1);
		return word.w;
	}
}

DEFINE_PUBLIC_ALIAS(pci_device_cfg_readl, libpci_device_cfg_readl);
INTERN NONNULL((1)) uint32_t
NOTHROW(CC libpci_device_cfg_readl)(struct pci_device const *__restrict self, uint8_t reg) {
	if likely((reg & 3) == 0) {
		uint32_t word;
		USER_TRY {
			word = pci_rdaddr(self->pd_addr | reg);
		}
		USER_EXCEPT(return UINT32_C(0xffffffff))
		return word;
	} else {
		union {
			uint32_t l;
			uint16_t w[2];
		} word;
		word.w[0] = libpci_device_cfg_readw(self, reg + 0);
		word.w[1] = libpci_device_cfg_readw(self, reg + 2);
		return word.l;
	}
}


#ifdef __KERNEL__
#define PCI_CFG_WRITE_RETURN_TYPE void
#define PCI_CFG_WRITE_START       /* nothing */
#define PCI_CFG_WRITE_END         (void)0
#else /* __KERNEL__ */
#define PCI_CFG_WRITE_RETURN_TYPE errno_t
#define PCI_CFG_WRITE_START \
	NESTED_TRY
#define PCI_CFG_WRITE_END \
	EXCEPT {              \
		return EACCES;    \
	}                     \
	return EOK
#endif /* !__KERNEL__ */


DEFINE_PUBLIC_ALIAS(pci_device_cfg_write_u8, libpci_device_cfg_write_u8);
INTERN NONNULL((1)) PCI_CFG_WRITE_RETURN_TYPE
NOTHROW(CC libpci_device_cfg_write_u8)(struct pci_device *__restrict self,
                                       uint8_t data, uint8_t reg) {
	PCI_CFG_WRITE_START {
		union {
			uint32_t l;
			uint8_t b[4];
		} word;
		word.l = pci_rdaddr(self->pd_addr | (reg & ~3));
		word.b[reg & 3] = data;
		pci_wraddr(self->pd_addr | (reg & ~3), word.l);
	}
	PCI_CFG_WRITE_END;
}

DEFINE_PUBLIC_ALIAS(pci_device_cfg_write_u16, libpci_device_cfg_write_u16);
INTERN NONNULL((1)) PCI_CFG_WRITE_RETURN_TYPE
NOTHROW(CC libpci_device_cfg_write_u16)(struct pci_device *__restrict self,
                                        uint16_t data, uint8_t reg) {
	if likely((reg & 1) == 0) {
		PCI_CFG_WRITE_START {
			union {
				uint32_t l;
				uint16_t w[2];
			} word;
			word.l = pci_rdaddr(self->pd_addr | (reg & ~3));
			word.w[(reg & 2) >> 1] = data;
			pci_wraddr(self->pd_addr | (reg & ~3), word.l);
		}
		PCI_CFG_WRITE_END;
	} else {
		union {
			uint16_t w;
			uint8_t b[2];
		} word;
#ifdef __KERNEL__
		word.w = data;
		libpci_device_cfg_write_u8(self, word.b[0], reg + 0);
		libpci_device_cfg_write_u8(self, word.b[1], reg + 1);
#else /* __KERNEL__ */
		errno_t error;
		word.w = data;
		error = libpci_device_cfg_write_u8(self, word.b[0], reg + 0);
		if likely(error == EOK)
			error = libpci_device_cfg_write_u8(self, word.b[1], reg + 1);
		return error;
#endif /* !__KERNEL__ */
	}
}

DEFINE_PUBLIC_ALIAS(pci_device_cfg_write_u32, libpci_device_cfg_write_u32);
INTERN NONNULL((1)) PCI_CFG_WRITE_RETURN_TYPE
NOTHROW(CC libpci_device_cfg_write_u32)(struct pci_device *__restrict self,
                                        uint32_t data, uint8_t reg) {
	if likely((reg & 3) == 0) {
		PCI_CFG_WRITE_START {
			pci_wraddr(self->pd_addr | reg, data);
		}
		PCI_CFG_WRITE_END;
	} else {
		union {
			uint32_t l;
			uint16_t w[2];
		} word;
#ifdef __KERNEL__
		word.l = data;
		libpci_device_cfg_write_u16(self, word.w[0], reg + 0);
		libpci_device_cfg_write_u16(self, word.w[1], reg + 2);
#else /* __KERNEL__ */
		errno_t error;
		word.l = data;
		error = libpci_device_cfg_write_u16(self, word.w[0], reg + 0);
		if likely(error == EOK)
			error = libpci_device_cfg_write_u16(self, word.w[1], reg + 2);
		return error;
#endif /* !__KERNEL__ */
	}
}



DEFINE_PUBLIC_ALIAS(pci_device_cfg_write_bits, libpci_device_cfg_write_bits);
#ifdef __KERNEL__
INTERN NONNULL((1)) void
NOTHROW(CC libpci_device_cfg_write_bits)(struct pci_device *__restrict self,
                                         uint32_t mask, uint32_t data, uint8_t reg) {
	uint32_t word;
	word = libpci_device_cfg_readl(self, reg);
	word &= mask;
	word |= data;
	libpci_device_cfg_write_u32(self, word, reg);
}
#else /* __KERNEL__ */
INTERN NONNULL((1)) errno_t
NOTHROW(CC libpci_device_cfg_write_bits)(struct pci_device *__restrict self,
                                         uint32_t mask, uint32_t data, uint8_t reg) {
	uint32_t word;
	errno_t error;
	error = libpci_device_cfg_read_u32(self, &word, reg);
	if (error == EOK) {
		word &= mask;
		word |= data;
		error = libpci_device_cfg_write_u32(self, word, reg);
	}
	return error;
}
#endif /* !__KERNEL__ */





#ifndef __KERNEL__
/************************************************************************/
/* VGA Arbiter support                                                  */
/************************************************************************/
DEFINE_PUBLIC_ALIAS(pci_device_vgaarb_init, libpci_device_vgaarb_init);
INTERN errno_t
NOTHROW(CC libpci_device_vgaarb_init)(void) {
	COMPILER_IMPURE();
	/* TODO */
	return ENOSYS;
}

DEFINE_PUBLIC_ALIAS(pci_device_vgaarb_fini, libpci_device_vgaarb_fini);
INTERN void
NOTHROW(CC libpci_device_vgaarb_fini)(void) {
	COMPILER_IMPURE();
	/* TODO */
}

DEFINE_PUBLIC_ALIAS(pci_device_vgaarb_set_target, libpci_device_vgaarb_set_target);
INTERN int
NOTHROW(CC libpci_device_vgaarb_set_target)(struct pci_device *__restrict self) {
	COMPILER_IMPURE();
	(void)self;
	/* TODO */
	return -1;
}

DEFINE_PUBLIC_ALIAS(pci_device_vgaarb_decodes, libpci_device_vgaarb_decodes);
INTERN int
NOTHROW(CC libpci_device_vgaarb_decodes)(int new_vga_rsrc) {
	COMPILER_IMPURE();
	(void)new_vga_rsrc;
	/* TODO */
	return -1;
}

DEFINE_PUBLIC_ALIAS(pci_device_vgaarb_lock, libpci_device_vgaarb_lock);
INTERN int
NOTHROW(CC libpci_device_vgaarb_lock)(void) {
	COMPILER_IMPURE();
	/* TODO */
	return -1;
}

DEFINE_PUBLIC_ALIAS(pci_device_vgaarb_trylock, libpci_device_vgaarb_trylock);
INTERN int
NOTHROW(CC libpci_device_vgaarb_trylock)(void) {
	COMPILER_IMPURE();
	/* TODO */
	return -1;
}

DEFINE_PUBLIC_ALIAS(pci_device_vgaarb_unlock, libpci_device_vgaarb_unlock);
INTERN int
NOTHROW(CC libpci_device_vgaarb_unlock)(void) {
	COMPILER_IMPURE();
	/* TODO */
	return -1;
}

DEFINE_PUBLIC_ALIAS(pci_device_vgaarb_get_info, libpci_device_vgaarb_get_info);
INTERN NONNULL((2)) errno_t
NOTHROW(CC libpci_device_vgaarb_get_info)(struct pci_device const *self, int *vga_count,
                                          /*[valid_if(self != NULL)]*/ int *rsrc_decodes) {
	COMPILER_IMPURE();
	(void)self;
	(void)vga_count;
	(void)rsrc_decodes;
	/* TODO */
	return ENOSYS;
}


/************************************************************************/
/* General purpose I/O accessors.                                       */
/************************************************************************/
#if __SIZEOF_POINTER__ == 4
#define _PCI_IO_HANDLE_HIBIT UINT32_C(0x80000000)
#elif __SIZEOF_POINTER__ == 8
#define _PCI_IO_HANDLE_HIBIT UINT64_C(0x8000000000000000)
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported __SIZEOF_POINTER__"
#endif /* __SIZEOF_POINTER__ != ... */

#define PCI_IO_HANDLE_MAKE(base) ((struct pci_io_handle *)((uintptr_t)(port_t)(base) | _PCI_IO_HANDLE_HIBIT))
#define PCI_IO_HANDLE_BASE(io)   ((port_t)(uintptr_t)(io))

INTERN WUNUSED NONNULL((1)) struct pci_io_handle *
NOTHROW(CC libpci_device_open_io)(struct pci_device *__restrict self, port_t base, port_t size) {
	unsigned int i;
	COMPILER_IMPURE();
	for (i = 0;; ++i) {
		if (i >= COMPILER_LENOF(self->pd_regions))
			return NULL;
		if (!self->pd_regions[i].pmr_is_IO)
			continue;
		if (base >= (port_t)self->pd_regions[i].pmr_addr &&
		    base < (port_t)(self->pd_regions[i].pmr_addr +
		                    self->pd_regions[i].pmr_size)) {
			if ((port_t)(base + size) < base ||
			    (port_t)(base + size) > (port_t)(self->pd_regions[i].pmr_addr +
			                                     self->pd_regions[i].pmr_size))
				return NULL;
			/* Found it! */
			break;
		}
	}
	return PCI_IO_HANDLE_MAKE(base);
}

DEFINE_PUBLIC_ALIAS(pci_legacy_open_io, libpci_legacy_open_io);
INTERN WUNUSED NONNULL((1)) struct pci_io_handle *
NOTHROW(CC libpci_legacy_open_io)(struct pci_device *__restrict self, port_t base, port_t size) {
	COMPILER_IMPURE();
	(void)self;
	(void)size;
	return PCI_IO_HANDLE_MAKE(base);
}

DEFINE_PUBLIC_ALIAS(pci_device_close_io, libpci_device_close_io);
INTERN void
NOTHROW(CC libpci_device_close_io)(struct pci_device *self, struct pci_io_handle *handle) {
	(void)self;
	(void)handle;
	COMPILER_IMPURE();
}

DEFINE_PUBLIC_ALIAS(pci_io_read8, libpci_io_read8);
INTERN uint8_t
NOTHROW(CC libpci_io_read8)(struct pci_io_handle *handle, port_t reg) {
	NESTED_TRY {
		return inb(PCI_IO_HANDLE_BASE(handle) + reg);
	} EXCEPT {
	}
	return UINT8_C(0xff);
}

DEFINE_PUBLIC_ALIAS(pci_io_read16, libpci_io_read16);
INTERN uint16_t
NOTHROW(CC libpci_io_read16)(struct pci_io_handle *handle, port_t reg) {
	NESTED_TRY {
		return inw(PCI_IO_HANDLE_BASE(handle) + reg);
	} EXCEPT {
	}
	return UINT16_C(0xff);
}

DEFINE_PUBLIC_ALIAS(pci_io_read32, libpci_io_read32);
INTERN uint32_t
NOTHROW(CC libpci_io_read32)(struct pci_io_handle *handle, port_t reg) {
	NESTED_TRY {
		return inl(PCI_IO_HANDLE_BASE(handle) + reg);
	} EXCEPT {
	}
	return UINT32_C(0xff);
}

DEFINE_PUBLIC_ALIAS(pci_io_write8, libpci_io_write8);
INTERN void
NOTHROW(CC libpci_io_write8)(struct pci_io_handle *handle, port_t reg, uint8_t data) {
	NESTED_TRY {
		outb(PCI_IO_HANDLE_BASE(handle) + reg, data);
	} EXCEPT {
	}
}

DEFINE_PUBLIC_ALIAS(pci_io_write16, libpci_io_write16);
INTERN void
NOTHROW(CC libpci_io_write16)(struct pci_io_handle *handle, port_t reg, uint16_t data) {
	NESTED_TRY {
		outw(PCI_IO_HANDLE_BASE(handle) + reg, data);
	} EXCEPT {
	}
}

DEFINE_PUBLIC_ALIAS(pci_io_write32, libpci_io_write32);
INTERN void
NOTHROW(CC libpci_io_write32)(struct pci_io_handle *handle, port_t reg, uint32_t data) {
	NESTED_TRY {
		outl(PCI_IO_HANDLE_BASE(handle) + reg, data);
	} EXCEPT {
	}
}

#endif /* !__KERNEL__ */

DECL_END

#ifndef __INTELLISENSE__
#include "pci.ids.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_LIBPCIACCESS_PCIACCESS_C */
