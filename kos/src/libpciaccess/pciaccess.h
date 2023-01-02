/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBPCIACCESS_PCIACCESS_H
#define GUARD_LIBPCIACCESS_PCIACCESS_H 1

#include "api.h"

#include <hybrid/compiler.h>
#ifdef __KERNEL__
#include <kernel/compiler.h>
#endif /* __KERNEL__ */

#include <kos/types.h>

#include <libpciaccess/pciaccess.h>

#ifndef NOBLOCK
#define NOBLOCK __NOBLOCK
#endif /* !NOBLOCK */

DECL_BEGIN

#ifndef __physaddr_t_defined
#define __physaddr_t_defined
typedef __physaddr_t physaddr_t; /* Physical memory address (== physpage_t * PAGESIZE) */
#endif /* !__physaddr_t_defined */

#ifndef __port_t_defined
#define __port_t_defined
typedef __port_t port_t;
#endif /* !__port_t_defined */

/* PCI System initialization.
 * NOTE: These functions  are  really  only  of  interest  to  user-space.
 *       Within the kernel, `pci_system_init()' isn't exported to drivers,
 *       and  is unconditionally called during system boot initialization. */
#ifdef __KERNEL__
INTDEF FREE void NOTHROW(CC libpci_system_init)(void);
#else /* __KERNEL__ */
INTDEF errno_t NOTHROW(CC libpci_system_init)(void);
INTDEF void NOTHROW(CC libpci_system_init_dev_mem)(fd_t fd);
INTDEF NOBLOCK void NOTHROW(CC libpci_system_cleanup)(void);
#endif /* !__KERNEL__ */

#ifndef __KERNEL__
/* Lookup the device names matching the given description. */
INTDEF NONNULL((1)) void
NOTHROW(CC libpci_get_strings)(/*[1..1]*/ struct pci_id_match const *__restrict match,
                               /*[0..1]*/ char const **pdevice_name,
                               /*[0..1]*/ char const **pvendor_name,
                               /*[0..1]*/ char const **psubdevice_name,
                               /*[0..1]*/ char const **psubvendor_name);
#endif /* !__KERNEL__ */

/************************************************************************/
/* PCI Device search API.                                               */
/************************************************************************/
#ifndef __KERNEL__
INTDEF NONNULL((1)) void NOTHROW(CC libpci_slot_match_iterator_init)(struct pci_device_iterator *__restrict self, struct pci_slot_match const *match);
#endif /* !__KERNEL__ */
INTDEF NONNULL((1)) void NOTHROW(CC libpci_id_match_iterator_init)(struct pci_device_iterator *__restrict self, struct pci_id_match const *match);
#ifdef __KERNEL__
INTDEF WUNUSED NONNULL((1)) struct pci_device *NOTHROW(CC libpci_device_next)(/*[1..1]*/ struct pci_device_iterator *__restrict iter);
#else /* __KERNEL__ */
INTDEF WUNUSED struct pci_device *NOTHROW(CC libpci_device_next)(/*[0..1]*/ struct pci_device_iterator *iter);
INTDEF ATTR_MALLOC WUNUSED struct pci_device_iterator *NOTHROW(CC libpci_slot_match_iterator_create)(struct pci_slot_match const *match);
INTDEF ATTR_MALLOC WUNUSED struct pci_device_iterator *NOTHROW(CC libpci_id_match_iterator_create)(struct pci_id_match const *match);
INTDEF NOBLOCK void NOTHROW(CC libpci_iterator_destroy)(/*[0..1]*/ struct pci_device_iterator *iter);
#endif /* !__KERNEL__ */

/************************************************************************/
/* PCI Device API functions.                                            */
/************************************************************************/

/* (Re-)initialize the given PCI device. The caller is responsible
 * to  fill  in  `self->pd_addr'  before  calling  this  function. */
#ifdef __KERNEL__
INTDEF NONNULL((1)) void NOTHROW(CC libpci_device_probe)(struct pci_device *__restrict self);
#else /* __KERNEL__ */
INTDEF NONNULL((1)) errno_t NOTHROW(CC libpci_device_probe)(struct pci_device *__restrict self);
#endif /* !__KERNEL__ */

/* Lookup a device, given its exact address. */
INTDEF ATTR_PURE WUNUSED struct pci_device *NOTHROW(CC libpci_device_byaddr)(pciaddr_t addr);

/* Fill in information about bridge bus indices (s.a. `PCI_ADDR_BUSMASK') */
INTDEF WUNUSED NONNULL((1, 2, 3, 4)) errno_t
NOTHROW(CC libpci_device_get_bridge_buses)(struct pci_device const *__restrict self,
                                           int *__restrict primary_bus,
                                           int *__restrict secondary_bus,
                                           int *__restrict subordinate_bus);

/* Lookup bridge device information. */
INTDEF WUNUSED NONNULL((1, 2)) errno_t NOTHROW(CC libpci_device_getinfo_agp)(struct pci_device const *__restrict self, struct pci_agp_info *__restrict result);
INTDEF WUNUSED NONNULL((1, 2)) errno_t NOTHROW(CC libpci_device_getinfo_bridge)(struct pci_device const *__restrict self, struct pci_bridge_info *__restrict result);
INTDEF WUNUSED NONNULL((1, 2)) errno_t NOTHROW(CC libpci_device_getinfo_pcmcia_bridge)(struct pci_device const *__restrict self, struct pci_pcmcia_bridge_info *__restrict result);
#ifdef __KERNEL__
INTDEF WUNUSED NONNULL((1)) struct pci_device *NOTHROW(CC libpci_device_get_parent_bridge)(struct pci_device const *__restrict self);
#else /* __KERNEL__ */
INTDEF WUNUSED struct pci_device *NOTHROW(CC libpci_device_get_parent_bridge)(/*[0..1]*/ struct pci_device const *self);
#endif /* !__KERNEL__ */

#ifndef __KERNEL__
/* Map or unmap a specific PCI device region into memory. The given physical address range
 * must be given such that it is a  clean sub-region of exactly one of the device's  BARs.
 * @param: map_flags: Set of `PCI_DEV_MAP_FLAG_*' */
INTDEF WUNUSED NONNULL((5)) errno_t NOTHROW(CC libpci_device_map_range)(struct pci_device *self, physaddr_t base, size_t size, unsigned int map_flags, void **__restrict paddr);
INTDEF WUNUSED NONNULL((2)) errno_t NOTHROW(CC libpci_device_unmap_range)(struct pci_device *self, void *memory, size_t size);

/* Same as `pci_device_map_range()', but don't check that the given range actually belongs
 * to a single BAR of the given device. As a matter of fact, `self' isn't actually used by
 * these functions...
 * @param: map_flags: Set of `PCI_DEV_MAP_FLAG_*' */
INTDEF WUNUSED NONNULL((5)) errno_t NOTHROW(CC libpci_device_map_legacy)(struct pci_device *self, physaddr_t base, size_t size, unsigned int map_flags, void **__restrict paddr);
INTDEF WUNUSED NONNULL((2)) errno_t NOTHROW(CC libpci_device_unmap_legacy)(struct pci_device *self, void *memory, size_t size);

/* Wrappers for `pci_device_getinfo_*()' */
INTDEF WUNUSED NONNULL((1)) struct pci_agp_info const *NOTHROW(CC libpci_device_get_agp_info)(struct pci_device *__restrict self);
INTDEF WUNUSED NONNULL((1)) struct pci_bridge_info const *NOTHROW(CC libpci_device_get_bridge_info)(struct pci_device *__restrict self);
INTDEF WUNUSED NONNULL((1)) struct pci_pcmcia_bridge_info const *NOTHROW(CC libpci_device_get_pcmcia_bridge_info)(struct pci_device *__restrict self);

/* Copy the given device's ROM into the provided buffer. */
INTDEF WUNUSED errno_t
NOTHROW(CC libpci_device_read_rom)(struct pci_device const *self, void *buffer);

/* No-op (for now) */
INTDEF NONNULL((1)) void NOTHROW(CC libpci_device_enable)(struct pci_device *__restrict self);

/* Check if this is the boot VGA device. (returning non-zero if that is the case) */
INTDEF WUNUSED NONNULL((1)) int NOTHROW(CC libpci_device_is_boot_vga)(struct pci_device const *__restrict self);

/* Check if a driver is attached to the given device. (returning non-zero if that is the case) */
INTDEF WUNUSED NONNULL((1)) int NOTHROW(CC libpci_device_has_kernel_driver)(struct pci_device const *__restrict self);

/* Return device names (retrieved from the "pci.ids" database; only available in user-space) */
INTDEF WUNUSED NONNULL((1)) char const *NOTHROW(CC libpci_device_get_device_name)(struct pci_device const *__restrict self);
INTDEF WUNUSED NONNULL((1)) char const *NOTHROW(CC libpci_device_get_subdevice_name)(struct pci_device const *__restrict self);
INTDEF WUNUSED NONNULL((1)) char const *NOTHROW(CC libpci_device_get_vendor_name)(struct pci_device const *__restrict self);
INTDEF WUNUSED NONNULL((1)) char const *NOTHROW(CC libpci_device_get_subvendor_name)(struct pci_device const *__restrict self);
#endif /* !__KERNEL__ */

/* Read/Write to/from the configuration space of a given PCI device. */
#ifdef __KERNEL__
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(CC libpci_device_readcfg)(struct pci_device const *__restrict self, void *data, uint8_t offset, uint8_t size);
INTDEF NONNULL((1, 2)) size_t NOTHROW_NCX(CC libpci_device_writecfg)(struct pci_device *__restrict self, void const *data, uint8_t offset, uint8_t size);
INTDEF NONNULL((1)) void NOTHROW(CC libpci_device_cfg_write_u8)(struct pci_device *__restrict self, uint8_t data, uint8_t reg);
INTDEF NONNULL((1)) void NOTHROW(CC libpci_device_cfg_write_u16)(struct pci_device *__restrict self, uint16_t data, uint8_t reg);
INTDEF NONNULL((1)) void NOTHROW(CC libpci_device_cfg_write_u32)(struct pci_device *__restrict self, uint32_t data, uint8_t reg);
INTDEF NONNULL((1)) void NOTHROW(CC libpci_device_cfg_write_bits)(struct pci_device *__restrict self, uint32_t mask, uint32_t data, uint8_t reg);
#else /* __KERNEL__ */
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_NCX(CC libpci_device_readcfg)(struct pci_device const *__restrict self, void *data, uint8_t offset, uint8_t size);
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_NCX(CC libpci_device_writecfg)(struct pci_device *__restrict self, void const *data, uint8_t offset, uint8_t size);
INTDEF NONNULL((1)) errno_t NOTHROW(CC libpci_device_cfg_write_u8)(struct pci_device *__restrict self, uint8_t data, uint8_t reg);
INTDEF NONNULL((1)) errno_t NOTHROW(CC libpci_device_cfg_write_u16)(struct pci_device *__restrict self, uint16_t data, uint8_t reg);
INTDEF NONNULL((1)) errno_t NOTHROW(CC libpci_device_cfg_write_u32)(struct pci_device *__restrict self, uint32_t data, uint8_t reg);
INTDEF NONNULL((1)) errno_t NOTHROW(CC libpci_device_cfg_write_bits)(struct pci_device *__restrict self, uint32_t mask, uint32_t data, uint8_t reg);
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(CC libpci_device_cfg_read)(struct pci_device const *__restrict self, void *data, uint8_t offset, uint8_t size, /*[0..1]*/ pciaddr_t *bytes_read);
INTDEF NONNULL((1, 2)) errno_t NOTHROW_NCX(CC libpci_device_cfg_write)(struct pci_device *__restrict self, void const *data, uint8_t offset, uint8_t size, /*[0..1]*/ pciaddr_t *bytes_written);
INTDEF NONNULL((1, 2)) errno_t NOTHROW(CC libpci_device_cfg_read_u8)(struct pci_device const *__restrict self, uint8_t *__restrict data, uint8_t reg);
INTDEF NONNULL((1, 2)) errno_t NOTHROW(CC libpci_device_cfg_read_u16)(struct pci_device const *__restrict self, uint16_t *__restrict data, uint8_t reg);
INTDEF NONNULL((1, 2)) errno_t NOTHROW(CC libpci_device_cfg_read_u32)(struct pci_device const *__restrict self, uint32_t *__restrict data, uint8_t reg);
INTDEF NONNULL((1)) errno_t NOTHROW(CC libpci_device_map_region)(struct pci_device *__restrict self, unsigned int bar_index, int write_enable);
INTDEF errno_t NOTHROW(CC libpci_device_unmap_region)(struct pci_device *self, unsigned int bar_index);
INTDEF NONNULL((1, 5)) errno_t NOTHROW(CC libpci_device_map_memory_range)(struct pci_device *__restrict self, physaddr_t base, size_t size, int write_enable, void **__restrict paddr);
INTDEF errno_t NOTHROW(CC libpci_device_unmap_memory_range)(struct pci_device *self, void *memory, size_t size);
#endif /* !__KERNEL__ */
/* In user-space, these functions will return 0xff[ff[ffff]] on error and set errno to non-zero */
INTDEF NONNULL((1)) uint8_t NOTHROW(CC libpci_device_cfg_readb)(struct pci_device const *__restrict self, uint8_t reg);
INTDEF NONNULL((1)) uint16_t NOTHROW(CC libpci_device_cfg_readw)(struct pci_device const *__restrict self, uint8_t reg);
INTDEF NONNULL((1)) uint32_t NOTHROW(CC libpci_device_cfg_readl)(struct pci_device const *__restrict self, uint8_t reg);





#ifndef __KERNEL__
/************************************************************************/
/* VGA Arbiter support                                                  */
/************************************************************************/
INTDEF errno_t NOTHROW(CC libpci_device_vgaarb_init)(void);
INTDEF void NOTHROW(CC libpci_device_vgaarb_fini)(void);
INTDEF int NOTHROW(CC libpci_device_vgaarb_set_target)(struct pci_device *__restrict self);
INTDEF int NOTHROW(CC libpci_device_vgaarb_decodes)(int new_vga_rsrc);
INTDEF int NOTHROW(CC libpci_device_vgaarb_lock)(void);
INTDEF int NOTHROW(CC libpci_device_vgaarb_trylock)(void);
INTDEF int NOTHROW(CC libpci_device_vgaarb_unlock)(void);
INTDEF NONNULL((2)) errno_t
NOTHROW(CC libpci_device_vgaarb_get_info)(struct pci_device const *self, int *vga_count,
                                          /*[valid_if(self != NULL)]*/ int *rsrc_decodes);

/************************************************************************/
/* General purpose I/O accessors.                                       */
/************************************************************************/
INTDEF WUNUSED NONNULL((1)) struct pci_io_handle *NOTHROW(CC libpci_device_open_io)(struct pci_device *__restrict self, port_t base, port_t size);
INTDEF WUNUSED NONNULL((1)) struct pci_io_handle *NOTHROW(CC libpci_legacy_open_io)(struct pci_device *__restrict self, port_t base, port_t size);
INTDEF void NOTHROW(CC libpci_device_close_io)(struct pci_device *self, struct pci_io_handle *handle);
INTDEF uint8_t NOTHROW(CC libpci_io_read8)(struct pci_io_handle *handle, port_t reg);
INTDEF uint16_t NOTHROW(CC libpci_io_read16)(struct pci_io_handle *handle, port_t reg);
INTDEF uint32_t NOTHROW(CC libpci_io_read32)(struct pci_io_handle *handle, port_t reg);
INTDEF void NOTHROW(CC libpci_io_write8)(struct pci_io_handle *handle, port_t reg, uint8_t data);
INTDEF void NOTHROW(CC libpci_io_write16)(struct pci_io_handle *handle, port_t reg, uint16_t data);
INTDEF void NOTHROW(CC libpci_io_write32)(struct pci_io_handle *handle, port_t reg, uint32_t data);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBPCIACCESS_PCIACCESS_H */
