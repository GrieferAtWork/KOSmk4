/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBSVGA_CHIPSETS_VESA_H
#define _LIBSVGA_CHIPSETS_VESA_H 1

#include "../api.h"
/**/

#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN


#define VBE_BIOSINFO_CAP_DACWIDTH 0x0001 /* clear: DAC is 6-bit; set: DAC is 6 or 8 bit. */
#define VBE_BIOSINFO_CAP_NOVGACOM 0x0002 /* clear: VGA-compat; set: not VGA compat. */
#define VBE_BIOSINFO_CAP_RAMDACOP 0x0004 /* ??? */

/* VBE info structure */
struct __ATTR_PACKED vbe_biosinfo {
	/* https://www.lowlevel.eu/wiki/VESA_BIOS_Extensions */
	char       vbi_signature[4];         /* == { 'V', 'E', 'S', 'A' } */
	__uint16_t vbi_version;              /* Version number (0xff00: major; 0x00ff: minor) */
	__uint16_t vbi_oem_string_off;       /* Far pointer to OEM string */
	__uint16_t vbi_oem_string_seg;       /* *ditto* */
	__uint32_t vbi_capabilities;         /* Set of `VBE_BIOSINFO_CAP_*' */
	__uint16_t vbi_vidmodelist_off;      /* Far pointer to video mode list (Pointes to 0xffff-terminated array of `u16') */
	__uint16_t vbi_vidmodelist_seg;      /* *ditto* */
	__uint16_t vbi_vmemsize;             /* Video memory size in 64K-blocks */
	__uint16_t vbi_oem_software_rev;     /* OEM software revision. */
	__uint16_t vbi_oem_vendor_name_off;  /* Far pointer to OEM vendor name string */
	__uint16_t vbi_oem_vendor_name_seg;  /* *ditto* */
	__uint16_t vbi_oem_product_name_off; /* Far pointer to OEM product name string */
	__uint16_t vbi_oem_product_name_seg; /* *ditto* */
	__uint16_t vbi_oem_product_rev_off;  /* Far pointer to OEM product revision name string */
	__uint16_t vbi_oem_product_rev_seg;  /* *ditto* */
	__byte_t   vbi_reserved[222];        /* Reserved */
	__byte_t   vbi_oemstrings[256];      /* Storage area for OEM strings. */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBSVGA_CHIPSETS_VESA_H */
