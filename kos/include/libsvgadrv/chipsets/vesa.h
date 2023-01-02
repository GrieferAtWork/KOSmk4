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
#ifndef _LIBSVGADRV_CHIPSETS_VESA_H
#define _LIBSVGADRV_CHIPSETS_VESA_H 1

#include "../api.h"
/**/

#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

/*
 * VESA driver. Based on:
 * - https://www.lowlevel.eu/wiki/VESA_BIOS_Extensions (german)
 * - http://www.phatcode.net/res/221/files/vbe20.pdf
 */


/* Flags for `struct vbe_biosinfo::vbi_capabilities' */
#define VBE_BIOSINFO_CAP_DACWIDTH 0x0001 /* clear: DAC is 6-bit; set: DAC is 6 or 8 bit. */
#define VBE_BIOSINFO_CAP_NOVGACOM 0x0002 /* clear: VGA-compat; set: not VGA compat. */
#define VBE_BIOSINFO_CAP_RAMDACOP 0x0004 /* ??? */

/* VBE info structure */
struct __ATTR_PACKED vbe_biosinfo {
	char       vbi_signature[4];         /* == { 'V', 'E', 'S', 'A' } */
	__uint16_t vbi_version;              /* Version number (0xff00: major; 0x00ff: minor) */
	__uint16_t vbi_oem_string_off;       /* Far pointer to OEM string */
	__uint16_t vbi_oem_string_seg;       /* *ditto* */
	__uint32_t vbi_capabilities;         /* Set of `VBE_BIOSINFO_CAP_*' */
	__uint16_t vbi_vidmodelist_off;      /* Far pointer to video mode list (Pointes to 0xffff-terminated array of `u16') */
	__uint16_t vbi_vidmodelist_seg;      /* *ditto* */
	__uint16_t vbi_vmemsize;             /* Video memory size in 64K-blocks (starting at `vmi_lfbaddr') */
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


/* Flags for `struct vbe_modeinfo::vmi_attrib' */
#define VBE_MODEINFO_ATTR_SUPPORTED 0x0001 /* Supported mode. (If not set, ignore this mode) */
/*efine VBE_MODEINFO_ATTR_          0x0002  * ... */
#define VBE_MODEINFO_ATTR_BIOSTTY   0x0004 /* BIOS supports TTY functions in this mode. */
#define VBE_MODEINFO_ATTR_COLOR     0x0008 /* This mode supports colors. */
#define VBE_MODEINFO_ATTR_GFX       0x0010 /* This is a graphics-mode (as opposed to text-mode) */
#define VBE_MODEINFO_ATTR_NOVGACOM  0x0020 /* This mode isn't VGA compatible. */
#define VBE_MODEINFO_ATTR_WINDOWED  0x0040 /* Memory from this mode is windowed (accessed as individual pages). */
#define VBE_MODEINFO_ATTR_LFB       0x0080 /* Supports a linear frame buffer. */

/* Flags for `struct vbe_modeinfo::vmi_wina_attr' / `struct vbe_modeinfo::vmi_winb_attr' */
#define VBE_WINATTR_MAYRELOC 0x01 /* Page can be reallocated */
#define VBE_WINATTR_MAYREAD  0x02 /* Page can be read from */
#define VBE_WINATTR_MAYWRITE 0x04 /* Page can be written to */

/* Values for `struct vbe_modeinfo::vmi_memmodel' */
#define VBE_MEMMODEL_TEXT     0x00 /* Text mode */
#define VBE_MEMMODEL_CGA      0x01 /* CGA graphics */
#define VBE_MEMMODEL_HERCULES 0x02 /* Hercules graphics */
#define VBE_MEMMODEL_PLANAR   0x03 /* Planar */
#define VBE_MEMMODEL_PACKED   0x04 /* Packed pixel */
#define VBE_MEMMODEL_NC4_256  0x05 /* Non-chain 4, 256 color */
#define VBE_MEMMODEL_DCOLOR   0x06 /* Direct color */
#define VBE_MEMMODEL_YUV      0x07 /* YUV */

/* Values for `struct vbe_modeinfo::vmi_dcolinfo' */
#define VBE_DCOLINFO_RAMPMOD  0x01 /* Color ramp can be configured */
#define VBE_DCOLINFO_RESAVAIL 0x02 /* Reserved bits (vmi_Xbits, vmi_Xshift) may be clobbered */

/* VBE mode info structure */
struct __ATTR_PACKED vbe_modeinfo {
	__uint16_t vmi_attrib;            /* Mode attributes (set of `VBE_MODEINFO_ATTR_*') */
	__uint8_t  vmi_wina_attr;         /* Window a attributes (set of `VBE_WINATTR_*') */
	__uint8_t  vmi_winb_attr;         /* Window b attributes (set of `VBE_WINATTR_*') */
	__uint16_t vmi_win_granularity;   /* Window granularity in Kb */
	__uint16_t vmi_win_size;          /* Window size in Kb */
	__uint16_t vmi_wina_segment;      /* Window a starting segment (real-mode-style) */
	__uint16_t vmi_winb_segment;      /* Window b starting segment (real-mode-style) */
	__uint16_t vmi_winfuncptr_off;    /* ??? Far pointer to window function */
	__uint16_t vmi_winfuncptr_seg;    /* ??? *ditto* */
	__uint16_t vmi_scanline;          /* Scanline size (in bytes) */
	__uint16_t vmi_resx;              /* Resolution (in X) */
	__uint16_t vmi_resy;              /* Resolution (in Y) */
	__uint8_t  vmi_chrsizex;          /* Text-mode character size (in X) */
	__uint8_t  vmi_chrsizey;          /* Text-mode character size (in Y) */
	__uint8_t  vmi_numplanes;         /* Number of planes */
	__uint8_t  vmi_bpp;               /* Bits per pixel (color-depth) */
	__uint8_t  vmi_numbanks;          /* Number of banks */
	__uint8_t  vmi_memmodel;          /* Memory model (oen of `VBE_MEMMODEL_*') */
	__uint8_t  vmi_banksize;          /* Bank size in Kb */
	__uint8_t  vmi_maximgplanes;      /* Max image plane number (== number of image planes -1) */
	__uint8_t _vmi_res1;              /* ... */
	__uint8_t  vmi_rbits;             /* [valid_if(vmi_memmodel == VBE_MEMMODEL_DCOLOR)] # of red color bits */
	__uint8_t  vmi_rshift;            /* [valid_if(vmi_memmodel == VBE_MEMMODEL_DCOLOR)] Left-shift for red color bits */
	__uint8_t  vmi_gbits;             /* [valid_if(vmi_memmodel == VBE_MEMMODEL_DCOLOR)] # of green color bits */
	__uint8_t  vmi_gshift;            /* [valid_if(vmi_memmodel == VBE_MEMMODEL_DCOLOR)] Left-shift for green color bits */
	__uint8_t  vmi_bbits;             /* [valid_if(vmi_memmodel == VBE_MEMMODEL_DCOLOR)] # of blue color bits */
	__uint8_t  vmi_bshift;            /* [valid_if(vmi_memmodel == VBE_MEMMODEL_DCOLOR)] Left-shift for blue color bits */
	__uint8_t  vmi_Xbits;             /* [valid_if(vmi_memmodel == VBE_MEMMODEL_DCOLOR)] # of reserved color bits */
	__uint8_t  vmi_Xshift;            /* [valid_if(vmi_memmodel == VBE_MEMMODEL_DCOLOR)] Left-shift for reserved color bits */
	__uint8_t  vmi_dcolinfo;          /* [valid_if(vmi_memmodel == VBE_MEMMODEL_DCOLOR)] Set of `VBE_DCOLINFO_*' */
	__uint32_t vmi_lfbaddr;           /* [valid_if(VBE_MODEINFO_ATTR_LFB)] Physical address of LFB buffer. */
	__uint32_t vmi_offscrn_offs;      /* Start of off-screen video memory (TODO: Is this an offset, or a physical address?) */
	__uint16_t vmi_offscrn_size;      /* Size of off-screen video memory */
	/* NOTE: Everything from here on is only available when `vbi_version >= 0x0300' */
	__uint16_t vmi_lfbscanline;       /* [valid_if(VBE_MODEINFO_ATTR_LFB)] Scanline size for LFB (in bytes) */
	__uint8_t  vmi_bnknumimgpages;    /* ??? */
	__uint8_t  vmi_linnumimgpages;    /* [valid_if(VBE_MODEINFO_ATTR_LFB)] ??? */
	__uint8_t  vmi_linrbits;          /* [valid_if(VBE_MODEINFO_ATTR_LFB)] # of red color bits */
	__uint8_t  vmi_linrshift;         /* [valid_if(VBE_MODEINFO_ATTR_LFB)] Left-shift for red color bits */
	__uint8_t  vmi_lingbits;          /* [valid_if(VBE_MODEINFO_ATTR_LFB)] # of green color bits */
	__uint8_t  vmi_lingshift;         /* [valid_if(VBE_MODEINFO_ATTR_LFB)] Left-shift for green color bits */
	__uint8_t  vmi_linbbits;          /* [valid_if(VBE_MODEINFO_ATTR_LFB)] # of blue color bits */
	__uint8_t  vmi_linbshift;         /* [valid_if(VBE_MODEINFO_ATTR_LFB)] Left-shift for blue color bits */
	__uint8_t  vmi_linXbits;          /* [valid_if(VBE_MODEINFO_ATTR_LFB)] # of reserved color bits */
	__uint8_t  vmi_linXshift;         /* [valid_if(VBE_MODEINFO_ATTR_LFB)] Left-shift for reserved color bits */
	__uint32_t vmi_maxpxclock;        /* ??? */
	__byte_t  _vmi_res2[190];         /* ... */
};


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBSVGADRV_CHIPSETS_VESA_H */
