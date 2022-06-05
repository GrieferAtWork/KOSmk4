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
#ifndef _LIBPCIACCESS_PCIACCESS_H
#define _LIBPCIACCESS_PCIACCESS_H 1

#include "api.h"

/* Compatibility header for libpciaccess (with is normally a 3rd party library,
 * but has been re-written  from scratch for the  sole purpose of being  usable
 * from  kernel- and user-space, as well as to be optimized for running on KOS)
 *
 * WARNING: _NO_ binary compatibility is provided for the original libpciaccess
 *          library. Instead, only API-compatibility is given (meaning you need
 *          to rebuild any programs compiled for the regular libpciaccess) */
#ifdef LIBPCIACCESS_SUPPORTED
#include <features.h>

#include <hybrid/__bitfield.h>
#include <hybrid/byteorder.h>

#include <asm/os/mman.h>
#include <bits/types.h>
#include <kos/anno.h>

/* Flags for `pci_device_map_range::map_flags' */
#define PCI_DEV_MAP_FLAG_WRITABLE      (__PROT_WRITE)
#define PCI_DEV_MAP_FLAG_WRITE_COMBINE (__PROT_WRITE << 1)
#define PCI_DEV_MAP_FLAG_CACHABLE      (__PROT_WRITE << 2)

#ifndef __port_t
#define __port_t __CRT_PRIVATE_UINT(__SIZEOF_PORT_T__)
#endif /* !__port_t */

#ifdef __CC__
__DECL_BEGIN

/* PCI Device class (24-bit unsigned integer; == PCI_DEV8 >> 8):
 *     0..7:   s.a.: `PCI_DEV8_PROGIFMASK'
 *     8..15:  s.a.: `PCI_DEV8_SUBCLASSMASK'
 *     16..23: s.a.: `PCI_DEV8_CLASSMASK' */
typedef __uint32_t pciclass_t;

/* PCI configuration address (same as `pci_addr_t'):
 *     0..7:   s.a.: `PCI_ADDR_REGMASK'
 *     8..10:  s.a.: `PCI_ADDR_FUNMASK'
 *     11..15: s.a.: `PCI_ADDR_DEVMASK'
 *     16..23: s.a.: `PCI_ADDR_BUSMASK'
 *     24..30: *unused* (must be 0)
 *     31:     s.a.: `PCI_ADDR_FENABLED' */
typedef __uint32_t pciaddr_t;

struct pci_device;
struct pci_id_match;
struct pci_agp_info;
struct pci_bridge_info;
struct pci_pcmcia_bridge_info;

/* PCI System initialization.
 * NOTE: These functions  are  really  only  of  interest  to  user-space.
 *       Within the kernel, `pci_system_init()' isn't exported to drivers,
 *       and  is unconditionally called during system boot initialization. */
#ifdef __KERNEL__
#ifdef CONFIG_BUILDING_KERNEL_CORE
__INTDEF void __NOTHROW(LIBPCIACCESS_CC pci_system_init)(void);
#endif /* CONFIG_BUILDING_KERNEL_CORE */
#else /* __KERNEL__ */
LIBPCIACCESS_DECL __errno_t __NOTHROW(LIBPCIACCESS_CC pci_system_init)(void);
LIBPCIACCESS_DECL void __NOTHROW(LIBPCIACCESS_CC pci_system_init_dev_mem)(__fd_t fd);
LIBPCIACCESS_DECL __NOBLOCK void __NOTHROW(LIBPCIACCESS_CC pci_system_cleanup)(void);
#endif /* !__KERNEL__ */


/* Special PCI match ID: Match anything. (all 1-bits) */
#define PCI_MATCH_ANY __UINT16_C(0xffff)

/* Check if the given 2 PCI ids are identical.
 * Used internally to compare fields of `struct pci_id_match' and `struct pci_device' */
#define PCI_ID_COMPARE(a, b) \
	((a) == PCI_MATCH_ANY || (a) == (b))

/* Descriptor for a PCI device search query (based on ID) */
struct pci_id_match {
#ifdef __USE_KOS
	union {
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__uint16_t pim_vendor_id;    /* s.a. `PCI_DEV0_VENDORMASK' */
			__uint16_t pim_device_id;    /* s.a. `PCI_DEV0_DEVICEMASK' */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__uint16_t pim_device_id;    /* s.a. `PCI_DEV0_DEVICEMASK' */
			__uint16_t pim_vendor_id;    /* s.a. `PCI_DEV0_VENDORMASK' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
#ifndef __USE_KOS_ALTERATIONS
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__uint16_t vendor_id;    /* s.a. `PCI_DEV0_VENDORMASK' */
			__uint16_t device_id;    /* s.a. `PCI_DEV0_DEVICEMASK' */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__uint16_t device_id;    /* s.a. `PCI_DEV0_DEVICEMASK' */
			__uint16_t vendor_id;    /* s.a. `PCI_DEV0_VENDORMASK' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
#endif /* !__USE_KOS_ALTERATIONS */
		__uint32_t pim_dev0; /* s.a. `PCI_DEV0' */
	};
	union {
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__uint16_t pim_subvendor_id; /* s.a. `PCI_GDEV2C_VENDORMASK' */
			__uint16_t pim_subdevice_id; /* s.a. `PCI_GDEV2C_SSYSIDMASK' */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__uint16_t pim_subdevice_id; /* s.a. `PCI_GDEV2C_SSYSIDMASK' */
			__uint16_t pim_subvendor_id; /* s.a. `PCI_GDEV2C_VENDORMASK' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
#ifndef __USE_KOS_ALTERATIONS
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__uint16_t subvendor_id; /* s.a. `PCI_GDEV2C_VENDORMASK' */
			__uint16_t subdevice_id; /* s.a. `PCI_GDEV2C_SSYSIDMASK' */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__uint16_t subdevice_id; /* s.a. `PCI_GDEV2C_SSYSIDMASK' */
			__uint16_t subvendor_id; /* s.a. `PCI_GDEV2C_VENDORMASK' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
#endif /* !__USE_KOS_ALTERATIONS */
		__uint32_t pim_gdev2c; /* s.a. `PCI_GDEV2C' */
	};
#ifdef __USE_KOS_ALTERATIONS
	pciclass_t pim_device_class;          /* Required class bits */
	pciclass_t pim_device_class_mask;     /* Masked class bits */
#else /* __USE_KOS_ALTERATIONS */
	union {
		pciclass_t pim_device_class;      /* Required class bits */
		pciclass_t device_class;          /* Required class bits */
	};
	union {
		pciclass_t pim_device_class_mask; /* Masked class bits */
		pciclass_t device_class_mask;     /* Masked class bits */
	};
#endif /* !__USE_KOS_ALTERATIONS */
#else /* __USE_KOS */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	__uint16_t vendor_id;    /* s.a. `PCI_DEV0_VENDORMASK' */
	__uint16_t device_id;    /* s.a. `PCI_DEV0_DEVICEMASK' */
	__uint16_t subvendor_id; /* s.a. `PCI_GDEV2C_VENDORMASK' */
	__uint16_t subdevice_id; /* s.a. `PCI_GDEV2C_SSYSIDMASK' */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
	__uint16_t device_id;    /* s.a. `PCI_DEV0_DEVICEMASK' */
	__uint16_t vendor_id;    /* s.a. `PCI_DEV0_VENDORMASK' */
	__uint16_t subdevice_id; /* s.a. `PCI_GDEV2C_SSYSIDMASK' */
	__uint16_t subvendor_id; /* s.a. `PCI_GDEV2C_VENDORMASK' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
	pciclass_t device_class;      /* Required class bits */
	pciclass_t device_class_mask; /* Masked class bits */
#endif /* !__USE_KOS */
#ifndef __USE_KOS_ALTERATIONS
	__intptr_t match_data;        /* User-data (unconditionally ignored) */
#endif /* !__USE_KOS_ALTERATIONS */
};


/* Descriptor for a PCI device search query (based on functionality) */
#ifndef __KERNEL__
struct pci_slot_match {
#ifdef __USE_KOS
	union {
		struct {
			__uint16_t psm_domain; /* Ignored (for now) */
			__uint16_t psm_func;   /* s.a. `PCI_ADDR_FUNMASK' */
			__uint16_t psm_dev;    /* s.a. `PCI_ADDR_DEVMASK' */
			__uint16_t psm_bus;    /* s.a. `PCI_ADDR_BUSMASK' */
		};
#ifndef __USE_KOS_ALTERATIONS
		struct {
			__uint16_t domain; /* Ignored (for now) */
			__uint16_t func;   /* s.a. `PCI_ADDR_FUNMASK' */
			__uint16_t dev;    /* s.a. `PCI_ADDR_DEVMASK' */
			__uint16_t bus;    /* s.a. `PCI_ADDR_BUSMASK' */
		};
#endif /* !__USE_KOS_ALTERATIONS */
	};
#else /* __USE_KOS */
	__uint16_t   domain; /* Ignored (for now) */
	__uint16_t   func;   /* s.a. `PCI_ADDR_FUNMASK' */
	__uint16_t   dev;    /* s.a. `PCI_ADDR_DEVMASK' */
	__uint16_t   bus;    /* s.a. `PCI_ADDR_BUSMASK' */
#endif /* !__USE_KOS */
#ifndef __USE_KOS_ALTERATIONS
	__intptr_t   match_data; /* User-data (unconditionally ignored) */
#endif /* !__USE_KOS_ALTERATIONS */
};
#endif /* !__KERNEL__ */




#ifndef __KERNEL__
/* Lookup the device names matching the given description. */
LIBPCIACCESS_DECL __ATTR_NONNULL((1)) void
__NOTHROW(LIBPCIACCESS_CC pci_get_strings)(/*[1..1]*/ struct pci_id_match const *__restrict match,
                                           /*[0..1]*/ char const **pdevice_name,
                                           /*[0..1]*/ char const **pvendor_name,
                                           /*[0..1]*/ char const **psubdevice_name,
                                           /*[0..1]*/ char const **psubvendor_name);
#endif /* !__KERNEL__ */


/************************************************************************/
/* PCI Device search API.                                               */
/************************************************************************/
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
struct pci_device_iterator {
	struct pci_device *pdi_next; /* [0..1] Next device to enumerate (`NULL' when done) */
	union {
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__uint16_t pdi_vendor_id;         /* [const] s.a. `PCI_DEV0_VENDORMASK' */
			__uint16_t pdi_device_id;         /* [const] s.a. `PCI_DEV0_DEVICEMASK' */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__uint16_t pdi_device_id;         /* [const] s.a. `PCI_DEV0_DEVICEMASK' */
			__uint16_t pdi_vendor_id;         /* [const] s.a. `PCI_DEV0_VENDORMASK' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
		__uint32_t     pdi_dev0;              /* [const] s.a. `PCI_DEV0' */
	};
	union {
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__uint16_t pdi_subvendor_id;      /* [const] s.a. `PCI_GDEV2C_VENDORMASK' */
			__uint16_t pdi_subdevice_id;      /* [const] s.a. `PCI_GDEV2C_SSYSIDMASK' */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__uint16_t pdi_subdevice_id;      /* [const] s.a. `PCI_GDEV2C_SSYSIDMASK' */
			__uint16_t pdi_subvendor_id;      /* [const] s.a. `PCI_GDEV2C_VENDORMASK' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
		__uint32_t     pdi_gdev2c;            /* [const] s.a. `PCI_GDEV2C' */
	};
	pciclass_t         pdi_device_class;      /* [const] Required class bits */
	pciclass_t         pdi_device_class_mask; /* [const] Masked class bits */
#ifndef __KERNEL__
	__uint16_t         pdi_func; /* s.a. `PCI_ADDR_FUNMASK' */
	__uint16_t         pdi_dev;  /* s.a. `PCI_ADDR_DEVMASK' */
	__uint16_t         pdi_bus;  /* s.a. `PCI_ADDR_BUSMASK' */
#endif /* !__KERNEL__ */
};
#else /* __USE_KOS || __USE_KOS_KERNEL */
struct pci_device_iterator; /* opaque... */
#endif /* !__USE_KOS && !__USE_KOS_KERNEL */

#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
#ifndef __KERNEL__
LIBPCIACCESS_DECL __ATTR_NONNULL((1)) void __NOTHROW(LIBPCIACCESS_CC pci_slot_match_iterator_init)(struct pci_device_iterator *__restrict self, struct pci_slot_match const *match);
#endif /* !__KERNEL__ */
LIBPCIACCESS_DECL __ATTR_NONNULL((1)) void __NOTHROW(LIBPCIACCESS_CC pci_id_match_iterator_init)(struct pci_device_iterator *__restrict self, struct pci_id_match const *match);
#endif /* __USE_KOS || __USE_KOS_KERNEL */
#ifdef __KERNEL__
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct pci_device *__NOTHROW(LIBPCIACCESS_CC pci_device_next)(/*[1..1]*/ struct pci_device_iterator *iter);
#else /* __KERNEL__ */
LIBPCIACCESS_DECL __ATTR_WUNUSED struct pci_device *__NOTHROW(LIBPCIACCESS_CC pci_device_next)(/*[0..1]*/ struct pci_device_iterator *iter);
LIBPCIACCESS_DECL __ATTR_MALLOC __ATTR_WUNUSED struct pci_device_iterator *__NOTHROW(LIBPCIACCESS_CC pci_slot_match_iterator_create)(struct pci_slot_match const *match);
LIBPCIACCESS_DECL __ATTR_MALLOC __ATTR_WUNUSED struct pci_device_iterator *__NOTHROW(LIBPCIACCESS_CC pci_id_match_iterator_create)(struct pci_id_match const *match);
LIBPCIACCESS_DECL __NOBLOCK void __NOTHROW(LIBPCIACCESS_CC pci_iterator_destroy)(/*[0..1]*/ struct pci_device_iterator *iter);
#endif /* !__KERNEL__ */



/* PCI Device BAR (BaseAddressRegister) descriptor. */
struct pci_mem_region {
#ifdef __USE_KOS
#ifdef __USE_KOS_ALTERATIONS
	__physaddr_t pmr_addr;                /* [const] BAR base address. (either a physical memory- or an I/O location; s.a. `pmr_is_IO')
	                                       * You  should  use  `pci_device_map_range()'  to  map  this  if  it's  a  memory   location! */
	__size_t     pmr_size;                /* [const] BAR size (in bytes) */
#ifndef __KERNEL__
	pciaddr_t   _pmr_bus_addr;            /* Unused / never initialized */
	void        *pmr_memory;              /* [0..1][lock(WRITE_ONCE)] Mapped address (s.a. `pci_device_map_region()') */
#endif /* !__KERNEL__ */
	__HYBRID_BITFIELD8_T pmr_is_IO : 1;           /* [const] Set to 1 if this is I/O memory. */
	__HYBRID_BITFIELD8_T pmr_is_prefetchable : 1; /* [const] Can memory be prefetched? */
	__HYBRID_BITFIELD8_T pmr_is_64 : 1;           /* [const] Set to 1 if it's a 64-bit address. */
#else /* __USE_KOS_ALTERATIONS */
	union {
		__physaddr_t pmr_addr;            /* [const] BAR base address. (either a physical memory- or an I/O location; s.a. `pmr_is_IO')
		                                   * You  should  use  `pci_device_map_range()'  to  map  this  if  it's  a  memory   location! */
		__physaddr_t base_addr;           /* [const] BAR base address. (either a physical memory- or an I/O location; s.a. `pmr_is_IO')
		                                   * You  should  use  `pci_device_map_range()'  to  map  this  if  it's  a  memory   location! */
	};
	union {
		__size_t     pmr_size;            /* [const] BAR size (in bytes) */
		__size_t     size;                /* [const] BAR size (in bytes) */
	};
#ifndef __KERNEL__
	union {
		pciaddr_t    _pmr_bus_addr;       /* Unused / never initialized */
		pciaddr_t    bus_addr;            /* Unused / never initialized */
	};
	union {
		void        *pmr_memory;          /* [0..1][lock(WRITE_ONCE)] Mapped address (s.a. `pci_device_map_region()') */
		void        *memory;              /* [0..1][lock(WRITE_ONCE)] Mapped address (s.a. `pci_device_map_region()') */
	};
#endif /* !__KERNEL__ */
	union {
		struct {
			__HYBRID_BITFIELD8_T pmr_is_IO : 1;           /* [const] Set to 1 if this is I/O memory. */
			__HYBRID_BITFIELD8_T pmr_is_prefetchable : 1; /* [const] Can memory be prefetched? */
			__HYBRID_BITFIELD8_T pmr_is_64 : 1;           /* [const] Set to 1 if it's a 64-bit address. */
		};
		struct {
			__HYBRID_BITFIELD8_T is_IO : 1;           /* [const] Set to 1 if this is I/O memory. */
			__HYBRID_BITFIELD8_T is_prefetchable : 1; /* [const] Can memory be prefetched? */
			__HYBRID_BITFIELD8_T is_64 : 1;           /* [const] Set to 1 if it's a 64-bit address. */
		};
	};
#endif /* !__USE_KOS_ALTERATIONS */
#else /* __USE_KOS */
	__physaddr_t base_addr;           /* [const] BAR base address. (either a physical memory- or an I/O location; s.a. `is_IO')
	                                   * You should  use  `pci_device_map_range()' to  map  this  if it's  a  memory  location! */
	__size_t     size;                /* [const] BAR size (in bytes) */
#ifndef __KERNEL__
	pciaddr_t    bus_addr;            /* Unused / never initialized */
	void        *memory;              /* [0..1][lock(WRITE_ONCE)] Mapped address (s.a. `pci_device_map_region()') */
#endif /* !__KERNEL__ */
	__HYBRID_BITFIELD8_T is_IO : 1;           /* [const] Set to 1 if this is I/O memory. */
	__HYBRID_BITFIELD8_T is_prefetchable : 1; /* [const] Can memory be prefetched? */
	__HYBRID_BITFIELD8_T is_64 : 1;           /* [const] Set to 1 if it's a 64-bit address. */
#endif /* !__USE_KOS */
};

/* General PCI device descriptor. */
struct pci_device {

	/* PCI Device address. */
#ifdef __USE_KOS
	union {
		pciaddr_t        pd_addr;        /* [const] PCI Device address. (to-be or'd with `PCI_ADDR_REGMASK') */
		struct {
			__uint8_t            __pd_zero1;     /* [const] 0b00000000 (s.a. `PCI_ADDR_REGMASK') */
			__HYBRID_BITFIELD8_T   pd_func: 3;   /* [const] s.a. `PCI_ADDR_FUNMASK' */
			__HYBRID_BITFIELD8_T   pd_dev: 5;    /* [const] s.a. `PCI_ADDR_DEVMASK' */
			__uint8_t              pd_bus;       /* [const] s.a. `PCI_ADDR_BUSMASK' */
			__HYBRID_BITFIELD8_T __pd_zero2 : 7; /* [const] 0b0000000 */
			__HYBRID_BITFIELD8_T __pd_one3 : 1;  /* [const] 0b1 (s.a. `PCI_ADDR_FENABLED') */
		};
#ifndef __USE_KOS_ALTERATIONS
		struct {
			__uint8_t            ___pd_zero1;     /* [const] 0b00000000 (s.a. `PCI_ADDR_REGMASK') */
			__HYBRID_BITFIELD8_T    func: 3;      /* [const] s.a. `PCI_ADDR_FUNMASK' */
			__HYBRID_BITFIELD8_T    dev: 5;       /* [const] s.a. `PCI_ADDR_DEVMASK' */
			__uint8_t               bus;          /* [const] s.a. `PCI_ADDR_BUSMASK' */
			__HYBRID_BITFIELD8_T ___pd_zero2 : 7; /* [const] 0b0000000 */
			__HYBRID_BITFIELD8_T ___pd_one3 : 1;  /* [const] 0b1 (s.a. `PCI_ADDR_FENABLED') */
		};
#endif /* !__USE_KOS_ALTERATIONS */
	};
#else /* __USE_KOS */
	__uint8_t            __pd_zero1;     /* [const] 0b00000000 (s.a. `PCI_ADDR_REGMASK') */
	__HYBRID_BITFIELD8_T   func: 3;      /* [const] s.a. `PCI_ADDR_FUNMASK' */
	__HYBRID_BITFIELD8_T   dev: 5;       /* [const] s.a. `PCI_ADDR_DEVMASK' */
	__uint8_t              bus;          /* [const] s.a. `PCI_ADDR_BUSMASK' */
	__HYBRID_BITFIELD8_T __pd_zero2 : 7; /* [const] 0b0000000 */
	__HYBRID_BITFIELD8_T __pd_one3 : 1;  /* [const] 0b1 (s.a. `PCI_ADDR_FENABLED') */
#endif /* !__USE_KOS */

	/* PCI Device vendor-id / device-id */
#ifdef __USE_KOS
	union {
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__uint16_t pd_vendor_id;    /* [const] s.a. `PCI_DEV0_VENDORMASK' */
			__uint16_t pd_device_id;    /* [const] s.a. `PCI_DEV0_DEVICEMASK' */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__uint16_t pd_device_id;    /* [const] s.a. `PCI_DEV0_DEVICEMASK' */
			__uint16_t pd_vendor_id;    /* [const] s.a. `PCI_DEV0_VENDORMASK' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
#ifndef __USE_KOS_ALTERATIONS
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__uint16_t vendor_id;    /* [const] s.a. `PCI_DEV0_VENDORMASK' */
			__uint16_t device_id;    /* [const] s.a. `PCI_DEV0_DEVICEMASK' */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__uint16_t device_id;    /* [const] s.a. `PCI_DEV0_DEVICEMASK' */
			__uint16_t vendor_id;    /* [const] s.a. `PCI_DEV0_VENDORMASK' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
#endif /* !__USE_KOS_ALTERATIONS */
		__uint32_t pd_dev0; /* [const] s.a. `PCI_DEV0' */
	};
	union {
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__uint16_t pd_subvendor_id; /* [const] s.a. `PCI_GDEV2C_VENDORMASK' */
			__uint16_t pd_subdevice_id; /* [const] s.a. `PCI_GDEV2C_SSYSIDMASK' */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__uint16_t pd_subdevice_id; /* [const] s.a. `PCI_GDEV2C_SSYSIDMASK' */
			__uint16_t pd_subvendor_id; /* [const] s.a. `PCI_GDEV2C_VENDORMASK' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
#ifndef __USE_KOS_ALTERATIONS
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__uint16_t subvendor_id; /* [const] s.a. `PCI_GDEV2C_VENDORMASK' */
			__uint16_t subdevice_id; /* [const] s.a. `PCI_GDEV2C_SSYSIDMASK' */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__uint16_t subdevice_id; /* [const] s.a. `PCI_GDEV2C_SSYSIDMASK' */
			__uint16_t subvendor_id; /* [const] s.a. `PCI_GDEV2C_VENDORMASK' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
#endif /* !__USE_KOS_ALTERATIONS */
		__uint32_t pd_gdev2c; /* [const] s.a. `PCI_GDEV2C' */
	};
#else /* __USE_KOS */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	__uint16_t vendor_id;    /* [const] s.a. `PCI_DEV0_VENDORMASK' */
	__uint16_t device_id;    /* [const] s.a. `PCI_DEV0_DEVICEMASK' */
	__uint16_t subvendor_id; /* [const] s.a. `PCI_GDEV2C_VENDORMASK' */
	__uint16_t subdevice_id; /* [const] s.a. `PCI_GDEV2C_SSYSIDMASK' */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
	__uint16_t device_id;    /* [const] s.a. `PCI_DEV0_DEVICEMASK' */
	__uint16_t vendor_id;    /* [const] s.a. `PCI_DEV0_VENDORMASK' */
	__uint16_t subdevice_id; /* [const] s.a. `PCI_GDEV2C_SSYSIDMASK' */
	__uint16_t subvendor_id; /* [const] s.a. `PCI_GDEV2C_VENDORMASK' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
#endif /* !__USE_KOS */


#ifdef __USE_KOS
	union {
		__uint32_t pd_dev8; /* [const] s.a. `PCI_DEV8' */
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__HYBRID_BITFIELD32_T __pd_revision : 8;      /* [const] s.a. `PCI_DEV8_REVIDMASK' */
			__HYBRID_BITFIELD32_T   pd_device_class : 24; /* [const] s.a. `pciclass_t'. */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__HYBRID_BITFIELD32_T   pd_device_class : 24; /* [const] s.a. `pciclass_t'. */
			__HYBRID_BITFIELD32_T __pd_revision : 8;      /* [const] s.a. `PCI_DEV8_REVIDMASK' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__uint8_t pd_revision;             /* [const] s.a. `PCI_DEV8_REVIDMASK' */
			__uint8_t pd_progif_id;            /* [const] s.a. `PCI_DEV8_PROGIFMASK' */
			__uint8_t pd_subclass_id;          /* [const] s.a. `PCI_DEV8_SUBCLASSMASK' (One of `PCI_DEV8_CLASS_*') */
			__uint8_t pd_class_id;             /* [const] s.a. `PCI_DEV8_CLASSMASK' (One of `PCI_DEV8_CLASS_*') */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__uint8_t pd_class_id;             /* [const] s.a. `PCI_DEV8_CLASSMASK' (One of `PCI_DEV8_CLASS_*') */
			__uint8_t pd_subclass_id;          /* [const] s.a. `PCI_DEV8_SUBCLASSMASK' (One of `PCI_DEV8_CLASS_*') */
			__uint8_t pd_progif_id;            /* [const] s.a. `PCI_DEV8_PROGIFMASK' */
			__uint8_t pd_revision;             /* [const] s.a. `PCI_DEV8_REVIDMASK' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
#ifndef __USE_KOS_ALTERATIONS
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__HYBRID_BITFIELD32_T revision : 8;      /* [const] s.a. `PCI_DEV8_REVIDMASK' */
			__HYBRID_BITFIELD32_T device_class : 24; /* [const] s.a. `pciclass_t'. */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__HYBRID_BITFIELD32_T device_class : 24; /* [const] s.a. `pciclass_t'. */
			__HYBRID_BITFIELD32_T revision : 8;      /* [const] s.a. `PCI_DEV8_REVIDMASK' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
#endif /* !__USE_KOS_ALTERATIONS */
	};
#else /* __USE_KOS */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	__HYBRID_BITFIELD32_T revision : 8;      /* [const] s.a. `PCI_DEV8_REVIDMASK' */
	__HYBRID_BITFIELD32_T device_class : 24; /* [const] s.a. `pciclass_t'. */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
	__HYBRID_BITFIELD32_T device_class : 24; /* [const] s.a. `pciclass_t'. */
	__HYBRID_BITFIELD32_T revision : 8;      /* [const] s.a. `PCI_DEV8_REVIDMASK' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
#endif /* !__USE_KOS */

#ifdef __USE_KOS
#define LIBPCI_DEVICE_ROM_BASE pd_rom_base
#define LIBPCI_DEVICE_ROM_SIZE pd_rom_size
#ifdef __USE_KOS_ALTERATIONS
	struct pci_mem_region pd_regions[6]; /* [const] Descriptors for BAR regions. */
	__physaddr_t          pd_rom_base;   /* [const] Device expansion ROM base address */
	__uint32_t            pd_rom_size;   /* [const] Device expansion ROM size (in bytes) */
	__int16_t             pd_irq;        /* [const] Device IRQ, or -1 if there is none. */
#else /* __USE_KOS_ALTERATIONS */
	union {
		struct pci_mem_region pd_regions[6]; /* [const] Descriptors for BAR regions. */
		struct pci_mem_region regions[6];    /* [const] Descriptors for BAR regions. */
	};
	union {
		__physaddr_t          pd_rom_base;   /* [const] Device expansion ROM base address */
		__physaddr_t        __rom_base;      /* [const] Device expansion ROM base address */
	};
	union {
		__uint32_t            pd_rom_size;   /* [const] Device expansion ROM size (in bytes) */
		__uint32_t            rom_size;      /* [const] Device expansion ROM size (in bytes) */
	};
	union {
		__int16_t             pd_irq;        /* [const] Device IRQ, or -1 if there is none. */
		__int16_t             irq;           /* [const] Device IRQ, or -1 if there is none. */
	};
#endif /* !__USE_KOS_ALTERATIONS */
#else /* __USE_KOS */
#define LIBPCI_DEVICE_ROM_BASE __rom_base
#define LIBPCI_DEVICE_ROM_SIZE rom_size
	struct pci_mem_region regions[6]; /* [const] Descriptors for BAR regions. */
	__physaddr_t        __rom_base;   /* [const] Device expansion ROM base address */
	__uint32_t            rom_size;   /* [const] Device expansion ROM size (in bytes) */
	__int16_t             irq;        /* [const] Device IRQ, or -1 if there is none. */
#endif /* !__USE_KOS */

#ifndef __KERNEL__
#ifdef __USE_KOS
#ifdef __USE_KOS_ALTERATIONS
	union {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		__uint16_t pd_domain_16; /* [const] Always 0xffff */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
		struct {
			__uint16_t __pd_domain_16_pad;
			__uint16_t pd_domain_16; /* [const] Always 0xffff */
		};
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		__uint32_t pd_domain;    /* [const] Always 0xffffffff */
	};
	__intptr_t     pd_user_data; /* Custom user-data */
#else /* __USE_KOS_ALTERATIONS */
	union {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		__uint16_t pd_domain_16; /* [const] Always 0xffff */
		__uint16_t domain_16;    /* [const] Always 0xffff */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
		struct {
			__uint16_t __pd_domain_16_pad;
			union {
				__uint16_t pd_domain_16; /* [const] Always 0xffff */
				__uint16_t domain_16;    /* [const] Always 0xffff */
			};
		};
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		__uint32_t pd_domain;    /* [const] Always 0xffffffff */
		__uint32_t domain;       /* [const] Always 0xffffffff */
	};
	union {
		__intptr_t pd_user_data; /* Custom user-data */
		__intptr_t user_data;    /* Custom user-data */
	};
#endif /* !__USE_KOS_ALTERATIONS */
#else /* __USE_KOS */
	union {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		__uint16_t domain_16;    /* [const] Always 0xffff */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
		struct {
			__uint16_t __domain_16_pad;
			__uint16_t domain_16; /* [const] Always 0xffff */
		};
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		__uint32_t domain;       /* [const] Always 0xffffffff */
	};
	__intptr_t     user_data;    /* Custom user-data */
#endif /* !__USE_KOS */
	struct pci_agp_info           *_pd_info_agp;           /* [0..1][owned][lock(WRITE_ONCE)] Info buffer. */
	struct pci_bridge_info        *_pd_info_bridge;        /* [0..1][owned][lock(WRITE_ONCE)] Info buffer. */
	struct pci_pcmcia_bridge_info *_pd_info_pcmcia_bridge; /* [0..1][owned][lock(WRITE_ONCE)] Info buffer. */
#endif /* !__KERNEL__ */
	struct { /* NOTE: This is an SLIST_ENTRY()-compatible structure! */
		struct pci_device *sle_next;
	} _pd_link;                        /* [0..1][const] Unordered list of all PCI devices. */
	struct pci_device *_pd_next_lo;    /* [0..1][const] Another device (left node of internal LLRB-tree) */
	struct pci_device *_pd_next_hi;    /* [0..1][const] Another device (left node of internal LLRB-tree) */
	__uint8_t          _pd_tree_rd;    /* [const] Red tree leaf. */
#ifdef __USE_KOS
	__uint8_t          pd_header_type; /* [const] Device header type (== `PCI_DEVC_HEADER(pci_device_cfg_readl(PCI_DEVC))').
	                                    * One   of  `PCI_DEVC_HEADER_*',  optionally  or'd  with  `PCI_DEVC_HEADER_MULTIDEV' */
#else /* __USE_KOS */
	__uint8_t         _pd_header_type; /* [const] Device header type (== `PCI_DEVC_HEADER(pci_device_cfg_readl(PCI_DEVC))').
	                                    * One   of  `PCI_DEVC_HEADER_*',  optionally  or'd  with  `PCI_DEVC_HEADER_MULTIDEV' */
#endif /* !__USE_KOS */

#if 0
	int vgaarb_rsrc; /* Currently not defined... */
#endif
};


#ifdef __USE_KOS
/* Special macro: `PCI_FOREACH_DEVICE()' which can be used for easy enumeration of all PCI devices:
 * >> struct pci_device *dev;
 * >> PCI_FOREACH_DEVICE (dev) {
 * >>     ...
 * >> }
 */
#ifdef __KERNEL__
#ifndef __pci_device_slist_defined
#define __pci_device_slist_defined
/* SLIST_HEAD(pci_device_slist, pci_device); */
struct pci_device_slist {
#ifdef GUARD_LIBPCIACCESS_PCIACCESS_C
	struct pci_device *slh_first; /* [0..1] List head */
#else /* GUARD_LIBPCIACCESS_PCIACCESS_C */
	struct pci_device *const slh_first; /* [0..1] List head */
#endif /* !GUARD_LIBPCIACCESS_PCIACCESS_C */
};
#endif /* !__pci_device_slist_defined */

LIBPCIACCESS_DECL struct pci_device_slist const pci_devices; /* [0..n][const] Singly-linked list of all PCI devices. */
#define PCI_FOREACH_DEVICE(dev) \
	for ((dev) = pci_devices.slh_first; (dev) != __NULLPTR; (dev) = (dev)->_pd_link.sle_next)
#else /* __KERNEL__ */
__COMPILER_REDIRECT(LIBPCIACCESS_DECL,__ATTR_WUNUSED __ATTR_CONST,struct pci_device *,__NOTHROW,LIBPCIACCESS_CC,__pci_devices,(void),pci_devices,())
#define PCI_FOREACH_DEVICE(dev) \
	for ((dev) = __pci_devices(); (dev) != __NULLPTR; (dev) = (dev)->_pd_link.sle_next)
#endif /* !__KERNEL__ */
/* Another helper macro: only enumerate devices matching the given class- and subclass IDs. */
#define PCI_FOREACH_DEVICE_CLASS(dev, class_id, subclass_id) \
	PCI_FOREACH_DEVICE(dev)                                  \
	if (!((dev)->pd_class_id == (class_id) &&                \
	      (dev)->pd_subclass_id == (subclass_id)))           \
		;                                                    \
	else
#endif /* __USE_KOS */


/************************************************************************/
/* PCI Device API functions.                                            */
/************************************************************************/

/* (Re-)initialize the given PCI device. The caller is responsible
 * to  fill  in  `self->pd_addr'  before  calling  this  function. */
#ifdef __KERNEL__
LIBPCIACCESS_DECL __ATTR_NONNULL((1)) void __NOTHROW(LIBPCIACCESS_CC pci_device_probe)(struct pci_device *__restrict self);
#else /* __KERNEL__ */
LIBPCIACCESS_DECL __ATTR_NONNULL((1)) __errno_t __NOTHROW(LIBPCIACCESS_CC pci_device_probe)(struct pci_device *__restrict self);
#endif /* !__KERNEL__ */

/* Lookup a device, given its exact address. */
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
LIBPCIACCESS_DECL __ATTR_PURE __ATTR_WUNUSED struct pci_device *__NOTHROW(LIBPCIACCESS_CC pci_device_byaddr)(pciaddr_t addr);
#define __pci_device_byaddr pci_device_byaddr
#else /* __USE_KOS || __USE_KOS_KERNEL */
__COMPILER_REDIRECT(LIBPCIACCESS_DECL,__ATTR_PURE __ATTR_WUNUSED,struct pci_device *,__NOTHROW,LIBPCIACCESS_CC,__pci_device_byaddr,(pciaddr_t addr),pci_device_byaddr,(addr))
#endif /* !__USE_KOS && !__USE_KOS_KERNEL */
#ifdef __INTELLISENSE__
__ATTR_PURE __ATTR_WUNUSED struct pci_device *
__NOTHROW(LIBPCIACCESS_CC pci_device_find_by_slot)(__uint32_t domain, __uint8_t bus,
                                             __uint8_t dev, __uint8_t func);
#else /* __INTELLISENSE__ */
#define pci_device_find_by_slot(domain, bus, dev, func)              \
	__pci_device_byaddr(((pciaddr_t)__UINT32_C(0x80000000)) |        \
	                    (((pciaddr_t)(__uint8_t)(bus)&0xff) << 16) | \
	                    (((pciaddr_t)(__uint8_t)(dev)&0x1f) << 11) | \
	                    (((pciaddr_t)(__uint8_t)(func)&0x7) << 8))
#endif /* !__INTELLISENSE__ */

/* Fill in information about bridge bus indices (s.a. `PCI_ADDR_BUSMASK') */
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3, 4)) __errno_t
__NOTHROW(LIBPCIACCESS_CC pci_device_get_bridge_buses)(struct pci_device const *__restrict self,
                                                       int *__restrict primary_bus,
                                                       int *__restrict secondary_bus,
                                                       int *__restrict subordinate_bus);

/* Lookup bridge device information. */
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __errno_t __NOTHROW(LIBPCIACCESS_CC pci_device_getinfo_agp)(struct pci_device const *__restrict self, struct pci_agp_info *__restrict result);
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __errno_t __NOTHROW(LIBPCIACCESS_CC pci_device_getinfo_bridge)(struct pci_device const *__restrict self, struct pci_bridge_info *__restrict result);
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __errno_t __NOTHROW(LIBPCIACCESS_CC pci_device_getinfo_pcmcia_bridge)(struct pci_device const *__restrict self, struct pci_pcmcia_bridge_info *__restrict result);
#endif /* __USE_KOS || __USE_KOS_KERNEL */

#ifdef __KERNEL__
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct pci_device *__NOTHROW(LIBPCIACCESS_CC pci_device_get_parent_bridge)(struct pci_device *__restrict self);
#else /* __KERNEL__ */
LIBPCIACCESS_DECL __ATTR_WUNUSED struct pci_device *__NOTHROW(LIBPCIACCESS_CC pci_device_get_parent_bridge)(/*[0..1]*/ struct pci_device *self);
#endif /* !__KERNEL__ */

#ifndef __KERNEL__
/* Map or unmap a specific PCI device region into memory. The given physical address range
 * must be given such that it is a  clean sub-region of exactly one of the device's  BARs.
 * @param: map_flags: Set of `PCI_DEV_MAP_FLAG_*' */
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((5)) __errno_t __NOTHROW(LIBPCIACCESS_CC pci_device_map_range)(struct pci_device *self, __physaddr_t base, __size_t size, unsigned int map_flags, void **__restrict paddr);
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((2)) __errno_t __NOTHROW(LIBPCIACCESS_CC pci_device_unmap_range)(struct pci_device *self, void *memory, __size_t size);

/* Same as `pci_device_map_range()', but don't check that the given range actually belongs
 * to a single BAR of the given device. As a matter of fact, `self' isn't actually used by
 * these functions...
 * @param: map_flags: Set of `PCI_DEV_MAP_FLAG_*' */
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((5)) __errno_t __NOTHROW(LIBPCIACCESS_CC pci_device_map_legacy)(struct pci_device *self, __physaddr_t base, __size_t size, unsigned int map_flags, void **__restrict paddr);
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((2)) __errno_t __NOTHROW(LIBPCIACCESS_CC pci_device_unmap_legacy)(struct pci_device *self, void *memory, __size_t size);

/* Wrappers for `pci_device_getinfo_*()' */
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct pci_agp_info const *__NOTHROW(LIBPCIACCESS_CC pci_device_get_agp_info)(struct pci_device *__restrict self);
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct pci_bridge_info const *__NOTHROW(LIBPCIACCESS_CC pci_device_get_bridge_info)(struct pci_device *__restrict self);
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct pci_pcmcia_bridge_info const *__NOTHROW(LIBPCIACCESS_CC pci_device_get_pcmcia_bridge_info)(struct pci_device *__restrict self);

/* Copy the given device's ROM into the provided buffer. */
LIBPCIACCESS_DECL __ATTR_WUNUSED __errno_t
__NOTHROW(LIBPCIACCESS_CC pci_device_read_rom)(struct pci_device const *self, void *buffer);

/* No-op (for now) */
LIBPCIACCESS_DECL __ATTR_NONNULL((1)) void __NOTHROW(LIBPCIACCESS_CC pci_device_enable)(struct pci_device *__restrict self);

/* Check if this is the boot VGA device. (returning non-zero if that is the case) */
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW(LIBPCIACCESS_CC pci_device_is_boot_vga)(struct pci_device const *__restrict self);

/* Check if a driver is attached to the given device. (returning non-zero if that is the case) */
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW(LIBPCIACCESS_CC pci_device_has_kernel_driver)(struct pci_device const *__restrict self);

/* Return device names (retrieved from the "pci.ids" database; only available in user-space) */
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW(LIBPCIACCESS_CC pci_device_get_device_name)(struct pci_device const *__restrict self);
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW(LIBPCIACCESS_CC pci_device_get_subdevice_name)(struct pci_device const *__restrict self);
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW(LIBPCIACCESS_CC pci_device_get_vendor_name)(struct pci_device const *__restrict self);
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW(LIBPCIACCESS_CC pci_device_get_subvendor_name)(struct pci_device const *__restrict self);
#else /* !__KERNEL__ */
#define pci_device_read_rom(self, buffer) \
	copyfromphys(buffer, (self)->LIBPCI_DEVICE_ROM_BASE, (self)->LIBPCI_DEVICE_ROM_SIZE)
#endif /* __KERNEL__ */

/* Read/Write to/from the configuration space of a given PCI device. */
#ifdef __KERNEL__
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
LIBPCIACCESS_DECL __ATTR_NONNULL((1, 2)) __size_t __NOTHROW_NCX(LIBPCIACCESS_CC pci_device_readcfg)(struct pci_device const *__restrict self, void *data, __uint8_t offset, __uint8_t size);
LIBPCIACCESS_DECL __ATTR_NONNULL((1, 2)) __size_t __NOTHROW_NCX(LIBPCIACCESS_CC pci_device_writecfg)(struct pci_device *__restrict self, void const *data, __uint8_t offset, __uint8_t size);
#endif /* __USE_KOS || __USE_KOS_KERNEL */
LIBPCIACCESS_DECL __ATTR_NONNULL((1)) void __NOTHROW(LIBPCIACCESS_CC pci_device_cfg_write_u8)(struct pci_device *__restrict self, __uint8_t data, __uint8_t reg);
LIBPCIACCESS_DECL __ATTR_NONNULL((1)) void __NOTHROW(LIBPCIACCESS_CC pci_device_cfg_write_u16)(struct pci_device *__restrict self, __uint16_t data, __uint8_t reg);
LIBPCIACCESS_DECL __ATTR_NONNULL((1)) void __NOTHROW(LIBPCIACCESS_CC pci_device_cfg_write_u32)(struct pci_device *__restrict self, __uint32_t data, __uint8_t reg);
LIBPCIACCESS_DECL __ATTR_NONNULL((1)) void __NOTHROW(LIBPCIACCESS_CC pci_device_cfg_write_bits)(struct pci_device *__restrict self, __uint32_t mask, __uint32_t data, __uint8_t reg);
#else /* __KERNEL__ */
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
LIBPCIACCESS_DECL __ATTR_NONNULL((1, 2)) __ssize_t __NOTHROW_NCX(LIBPCIACCESS_CC pci_device_readcfg)(struct pci_device const *__restrict self, void *data, __uint8_t offset, __uint8_t size);
LIBPCIACCESS_DECL __ATTR_NONNULL((1, 2)) __ssize_t __NOTHROW_NCX(LIBPCIACCESS_CC pci_device_writecfg)(struct pci_device *__restrict self, void const *data, __uint8_t offset, __uint8_t size);
#endif /* __USE_KOS || __USE_KOS_KERNEL */
LIBPCIACCESS_DECL __ATTR_NONNULL((1)) __errno_t __NOTHROW(LIBPCIACCESS_CC pci_device_cfg_write_u8)(struct pci_device *__restrict self, __uint8_t data, __uint8_t reg);
LIBPCIACCESS_DECL __ATTR_NONNULL((1)) __errno_t __NOTHROW(LIBPCIACCESS_CC pci_device_cfg_write_u16)(struct pci_device *__restrict self, __uint16_t data, __uint8_t reg);
LIBPCIACCESS_DECL __ATTR_NONNULL((1)) __errno_t __NOTHROW(LIBPCIACCESS_CC pci_device_cfg_write_u32)(struct pci_device *__restrict self, __uint32_t data, __uint8_t reg);
LIBPCIACCESS_DECL __ATTR_NONNULL((1)) __errno_t __NOTHROW(LIBPCIACCESS_CC pci_device_cfg_write_bits)(struct pci_device *__restrict self, __uint32_t mask, __uint32_t data, __uint8_t reg);
LIBPCIACCESS_DECL __ATTR_NONNULL((1, 2)) __errno_t __NOTHROW_NCX(LIBPCIACCESS_CC pci_device_cfg_read)(struct pci_device const *__restrict self, void *data, __uint8_t offset, __uint8_t size, /*[0..1]*/ pciaddr_t *bytes_read);
LIBPCIACCESS_DECL __ATTR_NONNULL((1, 2)) __errno_t __NOTHROW_NCX(LIBPCIACCESS_CC pci_device_cfg_write)(struct pci_device *__restrict self, void const *data, __uint8_t offset, __uint8_t size, /*[0..1]*/ pciaddr_t *bytes_written);
LIBPCIACCESS_DECL __ATTR_NONNULL((1, 2)) __errno_t __NOTHROW(LIBPCIACCESS_CC pci_device_cfg_read_u8)(struct pci_device const *__restrict self, __uint8_t *__restrict data, __uint8_t reg);
LIBPCIACCESS_DECL __ATTR_NONNULL((1, 2)) __errno_t __NOTHROW(LIBPCIACCESS_CC pci_device_cfg_read_u16)(struct pci_device const *__restrict self, __uint16_t *__restrict data, __uint8_t reg);
LIBPCIACCESS_DECL __ATTR_NONNULL((1, 2)) __errno_t __NOTHROW(LIBPCIACCESS_CC pci_device_cfg_read_u32)(struct pci_device const *__restrict self, __uint32_t *__restrict data, __uint8_t reg);
LIBPCIACCESS_DECL __ATTR_DEPRECATED_ __ATTR_NONNULL((1)) __errno_t __NOTHROW(LIBPCIACCESS_CC pci_device_map_region)(struct pci_device *__restrict self, unsigned int bar_index, int write_enable);
LIBPCIACCESS_DECL __ATTR_DEPRECATED_ __errno_t __NOTHROW(LIBPCIACCESS_CC pci_device_unmap_region)(struct pci_device *self, unsigned int bar_index);
LIBPCIACCESS_DECL __ATTR_DEPRECATED_ __ATTR_NONNULL((1, 5)) __errno_t __NOTHROW(LIBPCIACCESS_CC pci_device_map_memory_range)(struct pci_device *__restrict self, __physaddr_t base, __size_t size, int write_enable, void **__restrict paddr);
LIBPCIACCESS_DECL __ATTR_DEPRECATED_ __errno_t __NOTHROW(LIBPCIACCESS_CC pci_device_unmap_memory_range)(struct pci_device *self, void *memory, __size_t size);
#endif /* !__KERNEL__ */
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
/* In user-space, these functions will return 0xff[ff[ffff]] on error and set errno to non-zero */
LIBPCIACCESS_DECL __ATTR_NONNULL((1)) __uint8_t __NOTHROW(LIBPCIACCESS_CC pci_device_cfg_readb)(struct pci_device const *__restrict self, __uint8_t reg);
LIBPCIACCESS_DECL __ATTR_NONNULL((1)) __uint16_t __NOTHROW(LIBPCIACCESS_CC pci_device_cfg_readw)(struct pci_device const *__restrict self, __uint8_t reg);
LIBPCIACCESS_DECL __ATTR_NONNULL((1)) __uint32_t __NOTHROW(LIBPCIACCESS_CC pci_device_cfg_readl)(struct pci_device const *__restrict self, __uint8_t reg);
#define pci_device_cfg_writeb(self, reg, data) pci_device_cfg_write_u8(self, data, reg)
#define pci_device_cfg_writew(self, reg, data) pci_device_cfg_write_u16(self, data, reg)
#define pci_device_cfg_writel(self, reg, data) pci_device_cfg_write_u32(self, data, reg)
#endif /* __USE_KOS || __USE_KOS_KERNEL */



/************************************************************************/
/* Special information for specific PCI device types.                   */
/************************************************************************/
struct pci_agp_info {
#ifdef __USE_KOS
#ifdef __USE_KOS_ALTERATIONS
	__uint8_t            pai_config_offset; /* PCI_ADDR_REGMASK-style offset for the capability matrix.  */
#else /* __USE_KOS_ALTERATIONS */
	union {
		__uint8_t        pai_config_offset; /* PCI_ADDR_REGMASK-style offset for the capability matrix.  */
		__uint8_t        config_offset;     /* PCI_ADDR_REGMASK-style offset for the capability matrix.  */
	};
#endif /* !__USE_KOS_ALTERATIONS */
	union {
		__uint8_t        pai_cfg2;          /* == `pci_device_cfg_readb(config_offset + 2)' */
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__HYBRID_BITFIELD8_T pai_minor_version : 4; /* == `pci_device_cfg_readb(config_offset + 2) & 0xf' */
			__HYBRID_BITFIELD8_T pai_major_version : 4; /* == `(pci_device_cfg_readb(config_offset + 2) & 0xf0) >> 4' */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__HYBRID_BITFIELD8_T pai_major_version : 4; /* == `(pci_device_cfg_readb(config_offset + 2) & 0xf0) >> 4' */
			__HYBRID_BITFIELD8_T pai_minor_version : 4; /* == `pci_device_cfg_readb(config_offset + 2) & 0xf' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
#ifndef __USE_KOS_ALTERATIONS
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__HYBRID_BITFIELD8_T minor_version : 4; /* == `pci_device_cfg_readb(config_offset + 2) & 0xf' */
			__HYBRID_BITFIELD8_T major_version : 4; /* == `(pci_device_cfg_readb(config_offset + 2) & 0xf0) >> 4' */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__HYBRID_BITFIELD8_T major_version : 4; /* == `(pci_device_cfg_readb(config_offset + 2) & 0xf0) >> 4' */
			__HYBRID_BITFIELD8_T minor_version : 4; /* == `pci_device_cfg_readb(config_offset + 2) & 0xf' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
#endif /* !__USE_KOS_ALTERATIONS */
	};
	union {
		__uint32_t   _pai_cfg4_mod;         /* Slightly modified `pci_device_cfg_readl(config_offset + 4)' */
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__HYBRID_BITFIELD8_T pai_rates : 4;         /* Bitset of supported rates (1: 1x, 2: 2x, 4: 4x and 8:8x)  */
			__HYBRID_BITFIELD8_T pai_fast_writes : 1;   /* Support for fast-writes. */
			__HYBRID_BITFIELD8_T pai_addr64 : 1;        /* ... */
			__HYBRID_BITFIELD8_T pai_htrans : 1;        /* ... */
			__HYBRID_BITFIELD8_T pai_gart64 : 1;        /* ... */
			__HYBRID_BITFIELD8_T pai_coherent : 1;      /* ... */
			__HYBRID_BITFIELD8_T pai_sideband : 1;      /* Support for side-band addressing. */
			__HYBRID_BITFIELD8_T __pai_pad : 6;         /* ... */
			__HYBRID_BITFIELD8_T pai_isochronus : 1;    /* ... */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__HYBRID_BITFIELD8_T pai_isochronus : 1;    /* ... */
			__HYBRID_BITFIELD8_T __pai_pad : 6;         /* ... */
			__HYBRID_BITFIELD8_T pai_sideband : 1;      /* Support for side-band addressing. */
			__HYBRID_BITFIELD8_T pai_coherent : 1;      /* ... */
			__HYBRID_BITFIELD8_T pai_gart64 : 1;        /* ... */
			__HYBRID_BITFIELD8_T pai_htrans : 1;        /* ... */
			__HYBRID_BITFIELD8_T pai_addr64 : 1;        /* ... */
			__HYBRID_BITFIELD8_T pai_fast_writes : 1;   /* Support for fast-writes. */
			__HYBRID_BITFIELD8_T pai_rates : 4;         /* Bitset of supported rates (1: 1x, 2: 2x, 4: 4x and 8:8x)  */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
#ifndef __USE_KOS_ALTERATIONS
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__HYBRID_BITFIELD8_T rates : 4;         /* Bitset of supported rates (1: 1x, 2: 2x, 4: 4x and 8:8x)  */
			__HYBRID_BITFIELD8_T fast_writes : 1;   /* Support for fast-writes. */
			__HYBRID_BITFIELD8_T addr64 : 1;        /* ... */
			__HYBRID_BITFIELD8_T htrans : 1;        /* ... */
			__HYBRID_BITFIELD8_T gart64 : 1;        /* ... */
			__HYBRID_BITFIELD8_T coherent : 1;      /* ... */
			__HYBRID_BITFIELD8_T sideband : 1;      /* Support for side-band addressing. */
			__HYBRID_BITFIELD8_T __pad : 6;         /* ... */
			__HYBRID_BITFIELD8_T isochronus : 1;    /* ... */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__HYBRID_BITFIELD8_T isochronus : 1;    /* ... */
			__HYBRID_BITFIELD8_T __pad : 6;         /* ... */
			__HYBRID_BITFIELD8_T sideband : 1;      /* Support for side-band addressing. */
			__HYBRID_BITFIELD8_T coherent : 1;      /* ... */
			__HYBRID_BITFIELD8_T gart64 : 1;        /* ... */
			__HYBRID_BITFIELD8_T htrans : 1;        /* ... */
			__HYBRID_BITFIELD8_T addr64 : 1;        /* ... */
			__HYBRID_BITFIELD8_T fast_writes : 1;   /* Support for fast-writes. */
			__HYBRID_BITFIELD8_T rates : 4;         /* Bitset of supported rates (1: 1x, 2: 2x, 4: 4x and 8:8x)  */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
#endif /* !__USE_KOS_ALTERATIONS */
	};
#ifdef __USE_KOS_ALTERATIONS
	__uint8_t    pai_async_req_size;           /* ... */
	__uint8_t    pai_calibration_cycle_timing; /* ... */
	__uint8_t    pai_max_requests;             /* ... */
#else /* __USE_KOS_ALTERATIONS */
	union {
		__uint8_t    pai_async_req_size;       /* ... */
		__uint8_t    async_req_size;           /* ... */
	};
	union {
		__uint8_t    pai_calibration_cycle_timing; /* ... */
		__uint8_t    calibration_cycle_timing; /* ... */
	};
	union {
		__uint8_t    pai_max_requests;         /* ... */
		__uint8_t    max_requests;             /* ... */
	};
#endif /* !__USE_KOS_ALTERATIONS */
#else /* __USE_KOS */
	__uint8_t            config_offset;            /* PCI_ADDR_REGMASK-style offset for the capability matrix.  */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	__HYBRID_BITFIELD8_T minor_version : 4;        /* == `pci_device_cfg_readb(config_offset + 2) & 0xf' */
	__HYBRID_BITFIELD8_T major_version : 4;        /* == `(pci_device_cfg_readb(config_offset + 2) & 0xf0) >> 4' */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
	__HYBRID_BITFIELD8_T major_version : 4;        /* == `(pci_device_cfg_readb(config_offset + 2) & 0xf0) >> 4' */
	__HYBRID_BITFIELD8_T minor_version : 4;        /* == `pci_device_cfg_readb(config_offset + 2) & 0xf' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	__HYBRID_BITFIELD8_T rates : 4;                /* Bitset of supported rates (1: 1x, 2: 2x, 4: 4x and 8:8x)  */
	__HYBRID_BITFIELD8_T fast_writes : 1;          /* Support for fast-writes. */
	__HYBRID_BITFIELD8_T addr64 : 1;               /* ... */
	__HYBRID_BITFIELD8_T htrans : 1;               /* ... */
	__HYBRID_BITFIELD8_T gart64 : 1;               /* ... */
	__HYBRID_BITFIELD8_T coherent : 1;             /* ... */
	__HYBRID_BITFIELD8_T sideband : 1;             /* Support for side-band addressing. */
	__HYBRID_BITFIELD8_T __pad : 6;                /* ... */
	__HYBRID_BITFIELD8_T isochronus : 1;           /* ... */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
	__HYBRID_BITFIELD8_T isochronus : 1;           /* ... */
	__HYBRID_BITFIELD8_T __pad : 6;                /* ... */
	__HYBRID_BITFIELD8_T sideband : 1;             /* Support for side-band addressing. */
	__HYBRID_BITFIELD8_T coherent : 1;             /* ... */
	__HYBRID_BITFIELD8_T gart64 : 1;               /* ... */
	__HYBRID_BITFIELD8_T htrans : 1;               /* ... */
	__HYBRID_BITFIELD8_T addr64 : 1;               /* ... */
	__HYBRID_BITFIELD8_T fast_writes : 1;          /* Support for fast-writes. */
	__HYBRID_BITFIELD8_T rates : 4;                /* Bitset of supported rates (1: 1x, 2: 2x, 4: 4x and 8:8x)  */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
	__uint8_t            async_req_size;           /* ... */
	__uint8_t            calibration_cycle_timing; /* ... */
	__uint8_t            max_requests;             /* ... */
#endif /* !__USE_KOS */
};


struct pci_bridge_info {
#ifdef __USE_KOS
#ifdef __USE_KOS_ALTERATIONS
	__uint8_t  pbi_primary_bus;             /* == `pci_device_cfg_readb(0x18)' */
	__uint8_t  pbi_secondary_bus;           /* == `pci_device_cfg_readb(0x19)' */
	__uint8_t  pbi_subordinate_bus;         /* == `pci_device_cfg_readb(0x1a)' */
	__uint8_t  pbi_secondary_latency_timer; /* == `pci_device_cfg_readb(0x1b)' */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	__HYBRID_BITFIELD8_T pbi_io_type : 4;           /* == `pci_device_cfg_readb(0x1c) & 0xf' */
	__HYBRID_BITFIELD8_T pbi_mem_type : 4;          /* == `pci_device_cfg_readb(0x20) & 0xf' */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
	__HYBRID_BITFIELD8_T pbi_mem_type : 4;          /* == `pci_device_cfg_readb(0x20) & 0xf' */
	__HYBRID_BITFIELD8_T pbi_io_type : 4;           /* == `pci_device_cfg_readb(0x1c) & 0xf' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	__HYBRID_BITFIELD8_T pbi_prefetch_mem_type : 4; /* == `pci_device_cfg_readb(0x24) & 0xf' */
	__HYBRID_BITFIELD8_T __pbi_pad : 4;             /* ... */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
	__HYBRID_BITFIELD8_T __pbi_pad : 4;             /* ... */
	__HYBRID_BITFIELD8_T pbi_prefetch_mem_type : 4; /* == `pci_device_cfg_readb(0x24) & 0xf' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
	__uint16_t pbi_secondary_status;        /* == `pci_device_cfg_readw(0x1e)' */
	__uint16_t pbi_bridge_control;          /* == `pci_device_cfg_readw(0x3e)' */
	__uint16_t __pbi_pad2;                  /* ... */
	__uint32_t pbi_io_base;                 /* == `((pci_device_cfg_readw(0x1c) & 0xf0) << 8) | (pci_device_cfg_readw(0x30) << 16)' */
	__uint32_t pbi_io_limit;                /* == `0xfff | ((pci_device_cfg_readb(0x1d) & 0xf0) << 8) | (pci_device_cfg_readw(0x32) << 16)' */
	__uint32_t pbi_mem_base;                /* == `(pci_device_cfg_readw(0x20) & 0xfff0) << 16' */
	__uint32_t pbi_mem_limit;               /* == `0xfff | (pci_device_cfg_readw(0x22) & 0xf0) << 16' */
	__uint64_t pbi_prefetch_mem_base;       /* == `((pci_device_cfg_readw(0x24) & 0xfff0) << 16) | (pci_device_cfg_readl(0x28) << 32)' */
	__uint64_t pbi_prefetch_mem_limit;      /* == `(0xfff | (pci_device_cfg_readw(0x26) & 0xf0) << 16) | (pci_device_cfg_readl(0x2c) << 32)' */
#else /* __USE_KOS_ALTERATIONS */
	union {
		__uint8_t  pbi_primary_bus;         /* == `pci_device_cfg_readb(0x18)' */
		__uint8_t  primary_bus;             /* == `pci_device_cfg_readb(0x18)' */
	};
	union {
		__uint8_t  pbi_secondary_bus;       /* == `pci_device_cfg_readb(0x19)' */
		__uint8_t  secondary_bus;           /* == `pci_device_cfg_readb(0x19)' */
	};
	union {
		__uint8_t  pbi_subordinate_bus;     /* == `pci_device_cfg_readb(0x1a)' */
		__uint8_t  subordinate_bus;         /* == `pci_device_cfg_readb(0x1a)' */
	};
	union {
		__uint8_t  pbi_secondary_latency_timer; /* == `pci_device_cfg_readb(0x1b)' */
		__uint8_t  secondary_latency_timer; /* == `pci_device_cfg_readb(0x1b)' */
	};
	union {
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__HYBRID_BITFIELD8_T pbi_io_type : 4;           /* == `pci_device_cfg_readb(0x1c) & 0xf' */
			__HYBRID_BITFIELD8_T pbi_mem_type : 4;          /* == `pci_device_cfg_readb(0x20) & 0xf' */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__HYBRID_BITFIELD8_T pbi_mem_type : 4;          /* == `pci_device_cfg_readb(0x20) & 0xf' */
			__HYBRID_BITFIELD8_T pbi_io_type : 4;           /* == `pci_device_cfg_readb(0x1c) & 0xf' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__HYBRID_BITFIELD8_T io_type : 4;           /* == `pci_device_cfg_readb(0x1c) & 0xf' */
			__HYBRID_BITFIELD8_T mem_type : 4;          /* == `pci_device_cfg_readb(0x20) & 0xf' */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__HYBRID_BITFIELD8_T mem_type : 4;          /* == `pci_device_cfg_readb(0x20) & 0xf' */
			__HYBRID_BITFIELD8_T io_type : 4;           /* == `pci_device_cfg_readb(0x1c) & 0xf' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
	};
	union {
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__HYBRID_BITFIELD8_T pbi_prefetch_mem_type : 4; /* == `pci_device_cfg_readb(0x24) & 0xf' */
			__HYBRID_BITFIELD8_T __pbi_pad : 4;             /* ... */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__HYBRID_BITFIELD8_T __pbi_pad : 4;             /* ... */
			__HYBRID_BITFIELD8_T pbi_prefetch_mem_type : 4; /* == `pci_device_cfg_readb(0x24) & 0xf' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__HYBRID_BITFIELD8_T prefetch_mem_type : 4; /* == `pci_device_cfg_readb(0x24) & 0xf' */
			__HYBRID_BITFIELD8_T __pad : 4;             /* ... */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__HYBRID_BITFIELD8_T __pad : 4;             /* ... */
			__HYBRID_BITFIELD8_T prefetch_mem_type : 4; /* == `pci_device_cfg_readb(0x24) & 0xf' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
	};
	union {
		__uint16_t pbi_secondary_status;    /* == `pci_device_cfg_readw(0x1e)' */
		__uint16_t secondary_status;        /* == `pci_device_cfg_readw(0x1e)' */
	};
	union {
		__uint16_t pbi_bridge_control;      /* == `pci_device_cfg_readw(0x3e)' */
		__uint16_t bridge_control;          /* == `pci_device_cfg_readw(0x3e)' */
	};
	__uint16_t __pbi_pad2;                  /* ... */
	union {
		__uint32_t pbi_io_base;             /* == `((pci_device_cfg_readw(0x1c) & 0xf0) << 8) | (pci_device_cfg_readw(0x30) << 16)' */
		__uint32_t io_base;                 /* == `((pci_device_cfg_readw(0x1c) & 0xf0) << 8) | (pci_device_cfg_readw(0x30) << 16)' */
	};
	union {
		__uint32_t pbi_io_limit;            /* == `0xfff | ((pci_device_cfg_readb(0x1d) & 0xf0) << 8) | (pci_device_cfg_readw(0x32) << 16)' */
		__uint32_t io_limit;                /* == `0xfff | ((pci_device_cfg_readb(0x1d) & 0xf0) << 8) | (pci_device_cfg_readw(0x32) << 16)' */
	};
	union {
		__uint32_t pbi_mem_base;            /* == `(pci_device_cfg_readw(0x20) & 0xfff0) << 16' */
		__uint32_t mem_base;                /* == `(pci_device_cfg_readw(0x20) & 0xfff0) << 16' */
	};
	union {
		__uint32_t pbi_mem_limit;           /* == `0xfff | (pci_device_cfg_readw(0x22) & 0xf0) << 16' */
		__uint32_t mem_limit;               /* == `0xfff | (pci_device_cfg_readw(0x22) & 0xf0) << 16' */
	};
	union {
		__uint64_t pbi_prefetch_mem_base;   /* == `((pci_device_cfg_readw(0x24) & 0xfff0) << 16) | (pci_device_cfg_readl(0x28) << 32)' */
		__uint64_t prefetch_mem_base;       /* == `((pci_device_cfg_readw(0x24) & 0xfff0) << 16) | (pci_device_cfg_readl(0x28) << 32)' */
	};
	union {
		__uint64_t pbi_prefetch_mem_limit;  /* == `(0xfff | (pci_device_cfg_readw(0x26) & 0xf0) << 16) | (pci_device_cfg_readl(0x2c) << 32)' */
		__uint64_t prefetch_mem_limit;      /* == `(0xfff | (pci_device_cfg_readw(0x26) & 0xf0) << 16) | (pci_device_cfg_readl(0x2c) << 32)' */
	};
#endif /* !__USE_KOS_ALTERATIONS */
#else /* __USE_KOS */
	__uint8_t  primary_bus;             /* == `pci_device_cfg_readb(0x18)' */
	__uint8_t  secondary_bus;           /* == `pci_device_cfg_readb(0x19)' */
	__uint8_t  subordinate_bus;         /* == `pci_device_cfg_readb(0x1a)' */
	__uint8_t  secondary_latency_timer; /* == `pci_device_cfg_readb(0x1b)' */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	__HYBRID_BITFIELD8_T io_type : 4;           /* == `pci_device_cfg_readb(0x1c) & 0xf' */
	__HYBRID_BITFIELD8_T mem_type : 4;          /* == `pci_device_cfg_readb(0x20) & 0xf' */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
	__HYBRID_BITFIELD8_T mem_type : 4;          /* == `pci_device_cfg_readb(0x20) & 0xf' */
	__HYBRID_BITFIELD8_T io_type : 4;           /* == `pci_device_cfg_readb(0x1c) & 0xf' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	__HYBRID_BITFIELD8_T prefetch_mem_type : 4; /* == `pci_device_cfg_readb(0x24) & 0xf' */
	__HYBRID_BITFIELD8_T __pad : 4;             /* ... */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
	__HYBRID_BITFIELD8_T __pad : 4;             /* ... */
	__HYBRID_BITFIELD8_T prefetch_mem_type : 4; /* == `pci_device_cfg_readb(0x24) & 0xf' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
	__uint16_t secondary_status;        /* == `pci_device_cfg_readw(0x1e)' */
	__uint16_t bridge_control;          /* == `pci_device_cfg_readw(0x3e)' */
	__uint16_t __pad2;                  /* ... */
	__uint32_t io_base;                 /* == `((pci_device_cfg_readw(0x1c) & 0xf0) << 8) | (pci_device_cfg_readw(0x30) << 16)' */
	__uint32_t io_limit;                /* == `0xfff | ((pci_device_cfg_readb(0x1d) & 0xf0) << 8) | (pci_device_cfg_readw(0x32) << 16)' */
	__uint32_t mem_base;                /* == `(pci_device_cfg_readw(0x20) & 0xfff0) << 16' */
	__uint32_t mem_limit;               /* == `0xfff | (pci_device_cfg_readw(0x22) & 0xf0) << 16' */
	__uint64_t prefetch_mem_base;       /* == `((pci_device_cfg_readw(0x24) & 0xfff0) << 16) | (pci_device_cfg_readl(0x28) << 32)' */
	__uint64_t prefetch_mem_limit;      /* == `(0xfff | (pci_device_cfg_readw(0x26) & 0xf0) << 16) | (pci_device_cfg_readl(0x2c) << 32)' */
#endif /* !__USE_KOS */
};

struct pci_pcmcia_bridge_info {
#ifdef __USE_KOS
#ifdef __USE_KOS_ALTERATIONS
	__uint8_t  pcbi_primary_bus;           /* == `pci_device_cfg_readb(0x18)' */
	__uint8_t  pcbi_card_bus;              /* == `pci_device_cfg_readb(0x19)' */
	__uint8_t  pcbi_subordinate_bus;       /* == `pci_device_cfg_readb(0x1a)' */
	__uint8_t  pcbi_cardbus_latency_timer; /* == `pci_device_cfg_readb(0x1b)' */
	__uint16_t pcbi_secondary_status;      /* == `pci_device_cfg_readw(0x16)' */
	__uint16_t pcbi_bridge_control;        /* == `pci_device_cfg_readw(0x3e)' */
	struct {
		__uint32_t m_base;                 /* == `pci_device_cfg_readl(0x1c <=> 0x24)' */
		__uint32_t m_limit;                /* == `pci_device_cfg_readl(0x20 <=> 0x28)' */
	} pcbi_mem[2];
	struct {
		__uint32_t i_base;                 /* == `pci_device_cfg_readl(0x2c <=> 0x34)' */
		__uint32_t i_limit;                /* == `pci_device_cfg_readl(0x30 <=> 0x38)' */
	} pcbi_io[2];
#else /* __USE_KOS_ALTERATIONS */
	union {
		__uint8_t  pcbi_primary_bus;        /* == `pci_device_cfg_readb(0x18)' */
		__uint8_t  primary_bus;             /* == `pci_device_cfg_readb(0x18)' */
	};
	union {
		__uint8_t  pcbi_card_bus;           /* == `pci_device_cfg_readb(0x19)' */
		__uint8_t  card_bus;                /* == `pci_device_cfg_readb(0x19)' */
	};
	union {
		__uint8_t  pcbi_subordinate_bus;    /* == `pci_device_cfg_readb(0x1a)' */
		__uint8_t  subordinate_bus;         /* == `pci_device_cfg_readb(0x1a)' */
	};
	union {
		__uint8_t  pcbi_cardbus_latency_timer; /* == `pci_device_cfg_readb(0x1b)' */
		__uint8_t  cardbus_latency_timer;   /* == `pci_device_cfg_readb(0x1b)' */
	};
	union {
		__uint16_t pcbi_secondary_status;   /* == `pci_device_cfg_readw(0x16)' */
		__uint16_t secondary_status;        /* == `pci_device_cfg_readw(0x16)' */
	};
	union {
		__uint16_t pcbi_bridge_control;     /* == `pci_device_cfg_readw(0x3e)' */
		__uint16_t bridge_control;          /* == `pci_device_cfg_readw(0x3e)' */
	};
	union {
		struct {
			__uint32_t m_base;              /* == `pci_device_cfg_readl(0x1c <=> 0x24)' */
			__uint32_t m_limit;             /* == `pci_device_cfg_readl(0x20 <=> 0x28)' */
		} pcbi_mem[2];
		struct {
			__uint32_t base;                /* == `pci_device_cfg_readl(0x1c <=> 0x24)' */
			__uint32_t limit;               /* == `pci_device_cfg_readl(0x20 <=> 0x28)' */
		} mem[2];
	};
	union {
		struct {
			__uint32_t m_base;              /* == `pci_device_cfg_readl(0x2c <=> 0x34)' */
			__uint32_t m_limit;             /* == `pci_device_cfg_readl(0x30 <=> 0x38)' */
		} pcbi_io[2];
		struct {
			__uint32_t base;                /* == `pci_device_cfg_readl(0x2c <=> 0x34)' */
			__uint32_t limit;               /* == `pci_device_cfg_readl(0x30 <=> 0x38)' */
		} io[2];
	};
#endif /* !__USE_KOS_ALTERATIONS */
#else /* __USE_KOS */
	__uint8_t  primary_bus;             /* == `pci_device_cfg_readb(0x18)' */
	__uint8_t  card_bus;                /* == `pci_device_cfg_readb(0x19)' */
	__uint8_t  subordinate_bus;         /* == `pci_device_cfg_readb(0x1a)' */
	__uint8_t  cardbus_latency_timer;   /* == `pci_device_cfg_readb(0x1b)' */
	__uint16_t secondary_status;        /* == `pci_device_cfg_readw(0x16)' */
	__uint16_t bridge_control;          /* == `pci_device_cfg_readw(0x3e)' */
	struct {
		__uint32_t base;                /* == `pci_device_cfg_readl(0x1c <=> 0x24)' */
		__uint32_t limit;               /* == `pci_device_cfg_readl(0x20 <=> 0x28)' */
	} mem[2];
	struct {
		__uint32_t base;                /* == `pci_device_cfg_readl(0x2c <=> 0x34)' */
		__uint32_t limit;               /* == `pci_device_cfg_readl(0x30 <=> 0x38)' */
	} io[2];
#endif /* !__USE_KOS */
};



#ifndef __KERNEL__
/************************************************************************/
/* VGA Arbiter support                                                  */
/************************************************************************/
#define VGA_ARB_RSRC_NONE       0x00
#define VGA_ARB_RSRC_LEGACY_IO  0x01
#define VGA_ARB_RSRC_LEGACY_MEM 0x02
#define VGA_ARB_RSRC_NORMAL_IO  0x04
#define VGA_ARB_RSRC_NORMAL_MEM 0x08
LIBPCIACCESS_DECL __errno_t __NOTHROW(LIBPCIACCESS_CC pci_device_vgaarb_init)(void);
LIBPCIACCESS_DECL void __NOTHROW(LIBPCIACCESS_CC pci_device_vgaarb_fini)(void);
LIBPCIACCESS_DECL int __NOTHROW(LIBPCIACCESS_CC pci_device_vgaarb_set_target)(struct pci_device *__restrict self);
LIBPCIACCESS_DECL int __NOTHROW(LIBPCIACCESS_CC pci_device_vgaarb_decodes)(int new_vga_rsrc);
LIBPCIACCESS_DECL int __NOTHROW(LIBPCIACCESS_CC pci_device_vgaarb_lock)(void);
LIBPCIACCESS_DECL int __NOTHROW(LIBPCIACCESS_CC pci_device_vgaarb_trylock)(void);
LIBPCIACCESS_DECL int __NOTHROW(LIBPCIACCESS_CC pci_device_vgaarb_unlock)(void);
LIBPCIACCESS_DECL __ATTR_NONNULL((2)) __errno_t
__NOTHROW(LIBPCIACCESS_CC pci_device_vgaarb_get_info)(struct pci_device const *self, int *vga_count,
                                                      /*[valid_if(self != NULL)]*/ int *rsrc_decodes);
#endif /* !__KERNEL__ */


/************************************************************************/
/* General purpose I/O accessors.                                       */
/************************************************************************/
struct pci_io_handle;
#ifdef __KERNEL__
__DECL_END
#include <sys/io.h>
__DECL_BEGIN
#define pci_device_open_io(self, base, size) ((struct pci_io_handle *)(__uintptr_t)(__port_t)(base))
#define pci_legacy_open_io(self, base, size) ((struct pci_io_handle *)(__uintptr_t)(__port_t)(base))
#define pci_device_close_io(self, handle)    (void)0
#define pci_io_read8(handle, reg)            inb((__port_t)(__uintptr_t)(handle) + (reg))
#define pci_io_read16(handle, reg)           inw((__port_t)(__uintptr_t)(handle) + (reg))
#define pci_io_read32(handle, reg)           inl((__port_t)(__uintptr_t)(handle) + (reg))
#ifdef __USE_KOS_ALTERATIONS
#define pci_io_write8(handle, reg, data)  outb((__port_t)(__uintptr_t)(handle) + (reg), data)
#define pci_io_write16(handle, reg, data) outw((__port_t)(__uintptr_t)(handle) + (reg), data)
#define pci_io_write32(handle, reg, data) outl((__port_t)(__uintptr_t)(handle) + (reg), data)
#else /* __USE_KOS_ALTERATIONS */
#define pci_io_write8(handle, reg, data)  outb(data, (__port_t)(__uintptr_t)(handle) + (reg))
#define pci_io_write16(handle, reg, data) outw(data, (__port_t)(__uintptr_t)(handle) + (reg))
#define pci_io_write32(handle, reg, data) outl(data, (__port_t)(__uintptr_t)(handle) + (reg))
#endif /* !__USE_KOS_ALTERATIONS */
#else /* __KERNEL__ */
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct pci_io_handle *__NOTHROW(LIBPCIACCESS_CC pci_device_open_io)(struct pci_device *__restrict self, __port_t base, __port_t size);
LIBPCIACCESS_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct pci_io_handle *__NOTHROW(LIBPCIACCESS_CC pci_legacy_open_io)(struct pci_device *__restrict self, __port_t base, __port_t size);
LIBPCIACCESS_DECL void __NOTHROW(LIBPCIACCESS_CC pci_device_close_io)(struct pci_device *self, struct pci_io_handle *handle);
LIBPCIACCESS_DECL __uint8_t __NOTHROW(LIBPCIACCESS_CC pci_io_read8)(struct pci_io_handle *handle, __port_t reg);
LIBPCIACCESS_DECL __uint16_t __NOTHROW(LIBPCIACCESS_CC pci_io_read16)(struct pci_io_handle *handle, __port_t reg);
LIBPCIACCESS_DECL __uint32_t __NOTHROW(LIBPCIACCESS_CC pci_io_read32)(struct pci_io_handle *handle, __port_t reg);
LIBPCIACCESS_DECL void __NOTHROW(LIBPCIACCESS_CC pci_io_write8)(struct pci_io_handle *handle, __port_t reg, __uint8_t data);
LIBPCIACCESS_DECL void __NOTHROW(LIBPCIACCESS_CC pci_io_write16)(struct pci_io_handle *handle, __port_t reg, __uint16_t data);
LIBPCIACCESS_DECL void __NOTHROW(LIBPCIACCESS_CC pci_io_write32)(struct pci_io_handle *handle, __port_t reg, __uint32_t data);
#endif /* !__KERNEL__ */

__DECL_END
#endif /* __CC__ */
#endif /* LIBPCIACCESS_SUPPORTED */

#endif /* !_LIBPCIACCESS_PCIACCESS_H */
