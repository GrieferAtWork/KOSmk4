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
#ifndef _LIBVGASTATE_VGA_H
#define _LIBVGASTATE_VGA_H 1

#include "api.h"
/**/

#include <bits/types.h>
#include <hw/video/vga.h>
#ifdef __KERNEL__
#include <kos/kernel/memory.h>
#endif /* __KERNEL__ */

/* libvgastate:
 *
 * A (from the outside) simple utility library that only has 4 functions:
 *
 * Save whatever the current display mode might be, such that it can
 * be  restored at  a later  point in  time using `vga_state_load()'
 * This includes extended VGA modes, such as VESA, and the like,  as
 * well as the contents of display  memory (at least those that  may
 * be modified by text-mode font data, as well as text memory;  s.a.
 * the function `vga_state_text()' below)
 *  - unsigned int vga_state_save(struct vga_state *self);
 *
 * Restore the VGA state, as previously saved by `vga_state_save()'
 *  - unsigned int vga_state_load(struct vga_state const *self);
 *
 * Finalize a vga_state previously initialized by `vga_state_save()'
 *  - void vga_state_fini(struct vga_state *self);
 *
 * Force the display into 80x25, ANSI-compliant text-mode. The VGA
 * buffer itself  can  be  found in  physical  memory  at  0xb8000
 *  - unsigned int vga_state_text(void);
 *
 * unsigned int-return values are one of `VGA_STATE_ERROR_*'
 */


#define VGA_STATE_ERROR_SUCCESS 0 /* Success */
#define VGA_STATE_ERROR_NOMEM   1 /* Insufficient memory */

#define VGA_BIOS_FEAT_NONE      0x0000 /* ... */
#define VGA_BIOS_FEAT_VESA_MODE 0x0001 /* vb_vesa_mode */

#ifdef __CC__
__DECL_BEGIN

#ifdef __KERNEL__
typedef physaddr_t vga_bios_buf_t;
#else /* __KERNEL__ */
typedef __byte_t *vga_bios_buf_t;
#endif /* !__KERNEL__ */

struct vga_bios {
	vga_bios_buf_t vb_vesa_statebuf; /* [0..vb_vesa_statesiz][owned]   int10:ax=4F04h */
	__size_t       vb_vesa_statesiz; /* sizeof(vb_vesa_statebuf)       int10:ax=4F04h */
	__uint16_t     vb_features;      /* Available VGA BIOS features. (Set of `VGA_BIOS_FEAT_*') */
	__uint16_t     vb_vesa_mode;     /* [valid_if(VGA_BIOS_FEAT_SVGA)] int10:ax=4F03h */
};

struct vga_state {
	struct vga_mode       vs_mode;          /* VGA display mode. */
	struct vga_palette256 vs_pal;           /* VGA palette. */
	struct vga_font       vs_font;          /* VGA font memory. */
	__uint16_t            vs_text[80 * 25]; /* VGA text memory. */
	struct vga_bios       vs_bios;          /* VGA BIOS mode features. */
	/* TODO: Extended VGA modes (VESA, etc...) */
};


/* Save/Load the current VGA display state, or set the display state to 80x25 text mode.
 * @return: * : One of `VGA_STATE_ERROR_*' */
typedef __ATTR_NONNULL((1)) unsigned int /*__NOTHROW_KERNEL*/ (LIBVGASTATE_CC *PVGA_STATE_SAVE)(struct vga_state *__restrict self);
typedef __ATTR_NONNULL((1)) unsigned int /*__NOTHROW_KERNEL*/ (LIBVGASTATE_CC *PVGA_STATE_LOAD)(struct vga_state const *__restrict self);
typedef __ATTR_NONNULL((1)) void /*__NOTHROW_KERNEL*/ (LIBVGASTATE_CC *PVGA_STATE_FINI)(struct vga_state const *__restrict self);
typedef unsigned int /*__NOTHROW_KERNEL*/ (LIBVGASTATE_CC *PVGA_STATE_TEXT)(void);
#ifdef LIBVGASTATE_WANT_PROTOTYPES
LIBVGASTATE_DECL __ATTR_NONNULL((1)) unsigned int __NOTHROW_KERNEL(LIBVGASTATE_CC vga_state_save)(struct vga_state *__restrict self);
LIBVGASTATE_DECL __ATTR_NONNULL((1)) unsigned int __NOTHROW_KERNEL(LIBVGASTATE_CC vga_state_load)(struct vga_state const *__restrict self);
LIBVGASTATE_DECL __ATTR_NONNULL((1)) void __NOTHROW_KERNEL(LIBVGASTATE_CC vga_state_fini)(struct vga_state const *__restrict self);
LIBVGASTATE_DECL unsigned int __NOTHROW_KERNEL(LIBVGASTATE_CC vga_state_text)(void);
#endif /* LIBVGASTATE_WANT_PROTOTYPES */


/* Encode a given unicode character and return the VGA codepage ordinal with
 * which that character should be represented. As a fallback for glyphs that
 * don't appear in the VGA codepage, the ordinal of a replacement  character
 * will be returned instead.
 * This function also does some internal transliteration in order to provide
 * more support for similar-looking unicode characters (e.g. ► and ▶)
 * Unknown characters are mapped to 0x00, which (if displayed on-screen)
 * appears as a replacement character. */
typedef __ATTR_CONST __byte_t /*__NOTHROW*/ (LIBVGASTATE_CC *PVGA_STATE_ENCODE)(__CHAR32_TYPE__ ch);
#ifdef LIBVGASTATE_WANT_PROTOTYPES
LIBVGASTATE_DECL __ATTR_CONST __byte_t __NOTHROW(LIBVGASTATE_CC vga_state_encode)(__CHAR32_TYPE__ ch);
#endif /* LIBVGASTATE_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVGASTATE_VGA_H */
