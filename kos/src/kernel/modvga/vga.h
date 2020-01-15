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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODVGA_VGA_H
#define GUARD_MODVGA_VGA_H 1

#include <kernel/compiler.h>

#include <dev/video.h>
#include <kernel/types.h>

#include <hybrid/sync/atomic-rwlock.h>

#include <kos/io/vga.h>
#include <sys/io.h>

#include <libansitty/ansitty.h>

DECL_BEGIN

/* macro for composing an 8-bit VGA register
 * index and value into a single 16-bit quantity */
#define VGA_OUT16VAL(v,r)    (((v) << 8)|(r))

/* decide whether we should enable the faster 16-bit VGA register writes */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define VGA_OUTW_WRITE 1
#endif /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */


/* generic VGA port read/write */
__FORCELOCAL u8 __KCALL vga_r(port_t port) {
	return inb_p(port);
}
__FORCELOCAL void __KCALL vga_w(port_t port, u8 val) {
	outb_p(port, val);
}
__FORCELOCAL void __KCALL vga_w_fast(port_t port, u8 reg, u8 val) {
	outw(port, VGA_OUT16VAL(val, reg));
}

#ifdef VGA_OUTW_WRITE
#if 1
#define __VGA_OUTW_SELECTOR(func,port_i,port_d, reg, val)           func##_fast(port_i, reg, val)
#else
#define __VGA_OUTW_SELECTOR(func,port_i,port_d, reg, val)          ((port_i+1 == port_d) ? func##_fast(port_i, reg, val)         : (func(port_i, reg),func(port_d, val)))
#endif
#else
#define __VGA_OUTW_SELECTOR(func,port_i,port_d, reg, val)          (func(port_i, reg),func(port_d, val))
#endif

/* VGA CRTC register read/write */
LOCAL u8 KCALL vga_rcrt(u8 reg) {
	vga_w(VGA_CRT_IC, reg);
	return vga_r(VGA_CRT_DC);
}
LOCAL void KCALL vga_wcrt(u8 reg, u8 val) {
	__VGA_OUTW_SELECTOR(vga_w, VGA_CRT_IC, VGA_CRT_DC, reg, val);
}

/* VGA sequencer register read/write */
LOCAL u8 KCALL vga_rseq(u8 reg) {
	vga_w(VGA_SEQ_I, reg);
	return vga_r(VGA_SEQ_D);
}
LOCAL void KCALL vga_wseq(u8 reg, u8 val) {
	__VGA_OUTW_SELECTOR(vga_w, VGA_SEQ_I, VGA_SEQ_D, reg, val);
}

/* VGA graphics controller register read/write */
LOCAL u8 KCALL vga_rgfx(u8 reg) {
	vga_w(VGA_GFX_I, reg);
	return vga_r(VGA_GFX_D);
}
LOCAL void KCALL vga_wgfx(u8 reg, u8 val) {
	__VGA_OUTW_SELECTOR(vga_w, VGA_GFX_I, VGA_GFX_D, reg, val);
}

/* VGA attribute controller register read/write */
LOCAL u8 KCALL vga_rattr(u8 reg) {
	vga_w(VGA_ATT_IW, reg);
	return vga_r(VGA_ATT_R);
}
LOCAL void KCALL vga_wattr(u8 reg, u8 val) {
	vga_w(VGA_ATT_IW, reg);
	vga_w(VGA_ATT_W, val);
}






#ifdef __cplusplus
typedef struct: video_device
#else
typedef struct
#endif
{
#ifndef __cplusplus
	struct video_device     v_dev;       /* The underlying ansi video device. */
#endif
	struct atomic_rwlock    v_lock;      /* Lock for accessing the VGA Hardware. */
	PHYS vm_phys_t          v_vram_addr; /* [const] VRAM base address (physical). */
	VIRT byte_t            *v_vram;      /* [const] VRAM base address (virtual). */
	size_t                  v_vram_size; /* [const] VRAM size (in bytes). */
	/* VGA color/mono registers (Determined by `vga_r(v_mmio, VGA_MIS_R) & VGA_MIS_COLOR') */
	port_t                  v_crt_i;     /* [const] CRT Controller Index (Either `VGA_CRT_IC' or `VGA_CRT_IM') */
	port_t                  v_crt_d;     /* [const] CRT Controller Data Register (Either `VGA_CRT_DC' or `VGA_CRT_DM') */
	port_t                  v_is1_r;     /* [const] Input Status Register 1 (Either `VGA_IS1_RC' or `VGA_IS1_RM') */
#define VGA_STATE_FNORMAL    0x0000 /* Normal VGA state flags. */
#define VGA_STATE_FSCREENOFF 0x0001 /* The screen has been turned off. */
#define VGA_STATE_FGRAPHICS  0x0002 /* Graphics mode enabled. */
#define VGA_STATE_FCURSOR    0x0004 /* Cursor is being shown. */
	u16                     v_state;     /* [lock(v_lock)] VGA state flags (Set of `VGA_STATE_F*'). */
	struct vga_font        *v_savedfont; /* [0..1][owned][lock(v_lock)] Saved text-mode font while in graphics-mode */
	struct atomic_rwlock    v_textlock;  /* Lock for accessing the text pointers. */
	u16                    *v_textbase_real; /* [1..1][const] The real base pointer for the VGA text-mode buffer. */
	WEAK u16               *v_textbase;  /* [1..1][owned_if(VGA_STATE_FGRAPHICS)][lock(v_textlock)] Base pointer for the VGA text-mode buffer.
	                                      * When in graphics-mode, this is a heap-allocated memory block to still allow for
	                                      * display rendering when that rendering should simply be invisible. */
	WEAK u16               *v_text2line; /* [1..1][lock(v_textlock)] Pointer to the start of the second text-mode line. */
	WEAK u16               *v_textlline; /* [1..1][lock(v_textlock)] Pointer to the start of the last text-mode line. */
	WEAK u16               *v_textend;   /* [1..1][lock(v_textlock)] Pointer to the end of the VGA text-mode buffer. */
	WEAK u16               *v_textptr;   /* [1..1][lock(v_textlock)] Pointer to the character that will be written next. */
	WEAK u16               *v_scrlbase;  /* [1..1][lock(v_textlock)] Pointer to the start of the scroll region. */
	WEAK u16               *v_scrl2lin;  /* [1..1][lock(v_textlock)] Pointer to the start of the second line of the scroll region. */
	WEAK u16               *v_scrlllin;  /* [1..1][lock(v_textlock)] Pointer to the start of the last line of the scroll region. */
	WEAK u16               *v_scrlend;   /* [1..1][lock(v_textlock)] Pointer to the end of the scroll region. */
	WEAK size_t             v_scrlsize;  /* Number of characters that get moved during a 1-line scroll operation. */
	WEAK size_t             v_textsizex; /* Text-mode screen size in X */
	WEAK size_t             v_textsizey; /* Text-mode screen size in Y */
	char32_t                v_lastch;    /* Last-written text-mode character. */
} VGA;

INTDEF struct vga_mode       const vga_ansitty_mode; /* 80x25 color text mode (w/ modified palette indices). */
INTDEF struct vga_palette16  const vga_ansitty_pal;  /* Palette for ansi terminal color codes. */
INTDEF struct vga_mode       const vga_mode_gfx320x200_256;
INTDEF struct vga_mode       const vga_mode_gfx640x480_16;
INTDEF struct vga_palette256 const vga_pal_gfx256;
INTDEF struct vga_palette64  const vga_pal_gfx16;


INTDEF void KCALL VGA_SetMode(VGA *__restrict self, struct vga_mode const *__restrict mode);
INTDEF void KCALL VGA_GetMode(VGA *__restrict self, struct vga_mode *__restrict mode);
INTDEF void KCALL VGA_SetPalette(VGA *__restrict self, USER CHECKED void const *__restrict pal, size_t color_count);
INTDEF void KCALL VGA_GetPalette(VGA *__restrict self, USER CHECKED void *__restrict pal, size_t color_count);
INTDEF void KCALL VGA_ScreenOn(VGA *__restrict self);
INTDEF void KCALL VGA_ScreenOff(VGA *__restrict self);

INTDEF void KCALL VGA_SetFont(VGA *__restrict self, USER CHECKED struct vga_font const *__restrict font);
INTDEF void KCALL VGA_GetFont(VGA *__restrict self, USER CHECKED struct vga_font *__restrict font);


DECL_END

#endif /* !GUARD_MODVGA_VGA_H */
