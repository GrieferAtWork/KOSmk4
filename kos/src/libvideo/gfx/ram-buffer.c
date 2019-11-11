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
#ifndef GUARD_LIBVIDEO_GFX_RAM_BUFFER_C
#define GUARD_LIBVIDEO_GFX_RAM_BUFFER_C 1

#include "ram-buffer.h"

#include "api.h"

#include <hybrid/compiler.h>
#include <stddef.h>
#include <minmax.h>
#include <malloc.h>

#include "buffer.h"

DECL_BEGIN


#define RAMGFX_DATA   (byte_t *)self->bfx_driver[VIDEO_BUFFER_RAMGFX_DATA]
#define RAMGFX_STRIDE (size_t)self->bfx_driver[VIDEO_BUFFER_RAMGFX_STRIDE]
#define RAMGFX_SIZEX  (size_t)self->bfx_driver[VIDEO_BUFFER_RAMGFX_SIZEX]
#define RAMGFX_SIZEY  (size_t)self->bfx_driver[VIDEO_BUFFER_RAMGFX_SIZEY]


/* GFX functions for memory-based video buffers (without GPU support) */
INTERN video_color_t CC
libvideo_gfx_ramgfx_getcolor(struct video_buffer_gfx *__restrict self,
                             uintptr_t x, uintptr_t y) {
	byte_t *line;
	if (x >= RAMGFX_SIZEX || y >= RAMGFX_SIZEX)
		return 0;
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	return self->bfx_buffer->vb_format.getcolor(line, x);
}

INTERN video_color_t CC
libvideo_gfx_ramgfx_getcolor_with_key(struct video_buffer_gfx *__restrict self,
                                      uintptr_t x, uintptr_t y) {
	byte_t *line;
	video_color_t result;
	if (x >= RAMGFX_SIZEX || y >= RAMGFX_SIZEX)
		return 0;
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	result = self->bfx_buffer->vb_format.getcolor(line, x);
	if (result == self->bfx_colorkey)
		result = 0;
	return result;
}


#if 0 /*< Define as 1 to have the blender round upwards. */
#define div256(x) ((x)+0xfe)/0xff
#else
#define div256(x) (x)/0xff
#endif

#define blend_zero(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)                                       /* lhs* */ 0
#define blend_one(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)                                           lhs
#define blend_src_color(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)                div256((uint32_t)lhs * csrc)
#define blend_one_minus_src_color(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)      div256((uint32_t)lhs * (0xff - csrc))
#define blend_dst_color(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)                div256((uint32_t)lhs * cdst)
#define blend_one_minus_dst_color(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)      div256((uint32_t)lhs * (0xff - cdst))
#define blend_src_alpha(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)                div256((uint32_t)lhs * asrc)
#define blend_one_minus_src_alpha(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)      div256((uint32_t)lhs * (0xff - asrc))
#define blend_dst_alpha(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)                div256((uint32_t)lhs * adst)
#define blend_one_minus_dst_alpha(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)      div256((uint32_t)lhs * (0xff - adst))
#define blend_src_alpha_saturate(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)       div256((uint32_t)lhs * min(asrc, 0xff - adst))
#define blend_constant_color(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)           div256((uint32_t)lhs * cc)
#define blend_one_minus_constant_color(lhs, rhs, csrc, cdst, asrc, adst, cc, ac) div256((uint32_t)lhs * (0xff - cc))
#define blend_constant_alpha(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)           div256((uint32_t)lhs * ac)
#define blend_one_minus_constant_alpha(lhs, rhs, csrc, cdst, asrc, adst, cc, ac) div256((uint32_t)lhs * (0xff - ac))

#define BLEND_SWITCH(kind, callback)                                                                  \
	do {                                                                                              \
		switch (kind) {                                                                               \
		case GFX_BLENDMODE_ONE:                      callback(blend_one); break;                      \
		case GFX_BLENDMODE_SRC_COLOR:                callback(blend_src_color); break;                \
		case GFX_BLENDMODE_ONE_MINUS_SRC_COLOR:      callback(blend_one_minus_src_color); break;      \
		case GFX_BLENDMODE_DST_COLOR:                callback(blend_dst_color); break;                \
		case GFX_BLENDMODE_ONE_MINUS_DST_COLOR:      callback(blend_one_minus_dst_color); break;      \
		case GFX_BLENDMODE_SRC_ALPHA:                callback(blend_src_alpha); break;                \
		case GFX_BLENDMODE_ONE_MINUS_SRC_ALPHA:      callback(blend_one_minus_src_alpha); break;      \
		case GFX_BLENDMODE_DST_ALPHA:                callback(blend_dst_alpha); break;                \
		case GFX_BLENDMODE_ONE_MINUS_DST_ALPHA:      callback(blend_one_minus_dst_alpha); break;      \
		case GFX_BLENDMODE_SRC_ALPHA_SATURATE:       callback(blend_src_alpha_saturate); break;       \
		case GFX_BLENDMODE_CONSTANT_COLOR:           callback(blend_constant_color); break;           \
		case GFX_BLENDMODE_ONE_MINUS_CONSTANT_COLOR: callback(blend_one_minus_constant_color); break; \
		case GFX_BLENDMODE_CONSTANT_ALPHA:           callback(blend_constant_alpha); break;           \
		case GFX_BLENDMODE_ONE_MINUS_CONSTANT_ALPHA: callback(blend_one_minus_constant_alpha); break; \
		default:                                     callback(blend_zero); break;                     \
		}                                                                                             \
	} __WHILE0

#define func_add(a,b)              a + b
#define func_subtract(a,b)         a - b
#define func_reverse_subtract(a,b) b - a
#define FUNC_SWITCH(kind, callback)                                                  \
	do {                                                                             \
		switch (kind) {                                                              \
		case GFX_BLENDFUNC_SUBTRACT:         callback(func_subtract); break;         \
		case GFX_BLENDFUNC_REVERSE_SUBTRACT: callback(func_reverse_subtract); break; \
		case GFX_BLENDFUNC_MIN:              callback(min); break;                   \
		case GFX_BLENDFUNC_MAX:              callback(max); break;                   \
		default:                             callback(func_add); break;              \
		}                                                                            \
	} __WHILE0


LOCAL video_color_t CC
blend_color(video_color_t dst, video_color_t src, gfx_blendmode_t mode) {
	uint8_t new_lhs_r, new_lhs_g, new_lhs_b, new_lhs_a;
	uint8_t new_rhs_r, new_rhs_g, new_rhs_b, new_rhs_a;
	uint8_t dst_r, dst_g, dst_b, dst_a;
	uint8_t src_r, src_g, src_b, src_a;
	dst_r = VIDEO_COLOR_GET_RED(dst);
	dst_g = VIDEO_COLOR_GET_GREEN(dst);
	dst_b = VIDEO_COLOR_GET_BLUE(dst);
	dst_a = VIDEO_COLOR_GET_ALPHA(dst);
	src_r = VIDEO_COLOR_GET_RED(src);
	src_g = VIDEO_COLOR_GET_GREEN(src);
	src_b = VIDEO_COLOR_GET_BLUE(src);
	src_a = VIDEO_COLOR_GET_ALPHA(src);
#define blend_rgb_src(fun) \
	{                                                                                                                                 \
		new_lhs_r = (uint8_t)(fun(src_r, dst_r, src_r, dst_r, src_a, dst_a, GFX_BLENDINFO_GET_CR(mode), GFX_BLENDINFO_GET_CA(mode))); \
		new_lhs_g = (uint8_t)(fun(src_g, dst_g, src_g, dst_g, src_a, dst_a, GFX_BLENDINFO_GET_CG(mode), GFX_BLENDINFO_GET_CA(mode))); \
		new_lhs_b = (uint8_t)(fun(src_b, dst_b, src_b, dst_b, src_a, dst_a, GFX_BLENDINFO_GET_CB(mode), GFX_BLENDINFO_GET_CA(mode))); \
	}
#define blend_a_src(fun) \
	{                                                                                                                                 \
		new_lhs_a = (uint8_t)(fun(src_a, dst_a, src_a, dst_a, src_a, dst_a, GFX_BLENDINFO_GET_CA(mode), GFX_BLENDINFO_GET_CA(mode))); \
	}
#define blend_rgb_dst(fun) \
	{                                                                                                                                 \
		new_rhs_r = (uint8_t)(fun(dst_r, src_r, src_r, dst_r, src_a, dst_a, GFX_BLENDINFO_GET_CR(mode), GFX_BLENDINFO_GET_CA(mode))); \
		new_rhs_g = (uint8_t)(fun(dst_g, src_g, src_g, dst_g, src_a, dst_a, GFX_BLENDINFO_GET_CG(mode), GFX_BLENDINFO_GET_CA(mode))); \
		new_rhs_b = (uint8_t)(fun(dst_b, src_b, src_b, dst_b, src_a, dst_a, GFX_BLENDINFO_GET_CB(mode), GFX_BLENDINFO_GET_CA(mode))); \
	}
#define blend_a_dst(fun) \
	{                                                                                                                                 \
		new_rhs_a = (uint8_t)(fun(dst_a, src_a, src_a, dst_a, src_a, dst_a, GFX_BLENDINFO_GET_CA(mode), GFX_BLENDINFO_GET_CA(mode))); \
	}
	BLEND_SWITCH(GFX_BLENDINFO_GET_SRCRGB(mode), blend_rgb_src);
	BLEND_SWITCH(GFX_BLENDINFO_GET_SRCA(mode), blend_a_src);
	BLEND_SWITCH(GFX_BLENDINFO_GET_DSTRGB(mode), blend_rgb_dst);
	BLEND_SWITCH(GFX_BLENDINFO_GET_DSTA(mode), blend_a_dst);
#undef blend_a_dst
#undef blend_rgb_dst
#undef blend_a_src
#undef blend_rgb_src
#define func_rgb(fun) \
	{                                                 \
		dst_r = (uint8_t)(fun(new_lhs_r, new_rhs_r)); \
		dst_g = (uint8_t)(fun(new_lhs_g, new_rhs_g)); \
		dst_b = (uint8_t)(fun(new_lhs_b, new_rhs_b)); \
	}
#define func_a(fun) \
	{                                                 \
		dst_a = (uint8_t)(fun(new_lhs_a, new_rhs_a)); \
	}
	FUNC_SWITCH(GFX_BLENDINFO_GET_FUNRGB(mode), func_rgb);
	FUNC_SWITCH(GFX_BLENDINFO_GET_FUNA(mode), func_a);
#undef func_a
#undef func_rgb
	return VIDEO_COLOR_RGBA(dst_r, dst_g, dst_b, dst_a);
}



INTERN void CC
libvideo_gfx_ramgfx_putcolor(struct video_buffer_gfx *__restrict self,
                             uintptr_t x, uintptr_t y, video_color_t color) {
	byte_t *line;
	struct video_buffer *buffer;
	video_color_t o, n;
	if (x >= RAMGFX_SIZEX || y >= RAMGFX_SIZEX)
		return;
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	buffer = self->bfx_buffer;
	/* Perform full color blending. */
	o = buffer->vb_format.getcolor(line, x);
	n = blend_color(o, color, self->bfx_blend);
	buffer->vb_format.setcolor(line, x, n);
}

INTERN void CC
libvideo_gfx_ramgfx_putcolor_noblend(struct video_buffer_gfx *__restrict self,
                                     uintptr_t x, uintptr_t y, video_color_t color) {
	byte_t *line;
	struct video_buffer *buffer;
	if (x >= RAMGFX_SIZEX || y >= RAMGFX_SIZEX)
		return;
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	buffer = self->bfx_buffer;
	buffer->vb_format.setcolor(line, x, color);
}

INTERN void CC
libvideo_gfx_ramgfx_putcolor_alphablend(struct video_buffer_gfx *__restrict self,
                                        uintptr_t x, uintptr_t y, video_color_t color) {
	byte_t *line;
	struct video_buffer *buffer;
	video_color_t o, n;
	if (x >= RAMGFX_SIZEX || y >= RAMGFX_SIZEX)
		return;
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	buffer = self->bfx_buffer;
	o = buffer->vb_format.getcolor(line, x);
	n = blend_color(o, color, GFX_BLENDINFO_ALPHA);
	buffer->vb_format.setcolor(line, x, n);
}


/* NOTE: GFX functions not implemented explicitly
 *       use the default implementations from `gfx.c' */

/* TODO: Add optimizations for same-codec blits */
INTDEF void CC libvideo_gfx_ramgfx_line(struct video_buffer_gfx *__restrict self, intptr_t x1, intptr_t y1, intptr_t x2, intptr_t y2, video_color_t color);
INTDEF void CC libvideo_gfx_ramgfx_vline(struct video_buffer_gfx *__restrict self, uintptr_t x, uintptr_t y1, uintptr_t y2, video_color_t color);
INTDEF void CC libvideo_gfx_ramgfx_hline(struct video_buffer_gfx *__restrict self, uintptr_t y, uintptr_t x1, uintptr_t x2, video_color_t color);
INTDEF void CC libvideo_gfx_ramgfx_fill(struct video_buffer_gfx *__restrict self, uintptr_t x, uintptr_t y, size_t size_x, size_t size_y, video_color_t color);
INTDEF void CC libvideo_gfx_ramgfx_rect(struct video_buffer_gfx *__restrict self, uintptr_t x, uintptr_t y, size_t size_x, size_t size_y, video_color_t color);
INTDEF void CC libvideo_gfx_ramgfx_blit(struct video_buffer_gfx *__restrict self, intptr_t dst_x, intptr_t dst_y, struct video_buffer_gfx *__restrict src, intptr_t src_x, intptr_t src_y, size_t size_x, size_t size_y);
INTDEF void CC libvideo_gfx_ramgfx_stretch(struct video_buffer_gfx *__restrict self, intptr_t dst_x, intptr_t dst_y, size_t dst_size_x, size_t dst_size_y, struct video_buffer_gfx *__restrict src, intptr_t src_x, intptr_t src_y, size_t src_size_x, size_t src_size_y);




PRIVATE struct video_buffer_ops rambuffer_ops;

PRIVATE void CC
rambuffer_destroy(struct video_buffer *__restrict self) {
	struct video_rambuffer *me;
	me = (struct video_rambuffer *)self;
	assert(me->vb_ops == &rambuffer_ops);
	free(me->vb_data);
	free(me);
}

PRIVATE NONNULL((1, 2)) int CC
rambuffer_lock(struct video_buffer *__restrict self,
               struct video_lock *__restrict result) {
	struct video_rambuffer *me;
	me = (struct video_rambuffer *)self;
	assert(me->vb_ops == &rambuffer_ops);
	result->vl_stride = me->vb_stride;
	result->vl_size   = me->vb_total;
	result->vl_data   = me->vb_data;
	return 0;
}

PRIVATE NONNULL((1, 2)) void CC
rambuffer_unlock(struct video_buffer *__restrict self,
                 struct video_lock const *__restrict lock) {
#ifndef NDEBUG
	struct video_rambuffer *me;
	me = (struct video_rambuffer *)self;
	assert(me->vb_ops == &rambuffer_ops);
	assert(lock->vl_stride == me->vb_stride);
	assert(lock->vl_size == me->vb_total);
	assert(lock->vl_data == me->vb_data);
#endif /* !NDEBUG */
	(void)self;
	(void)lock;
}

LOCAL bool CC is_add_subtract_or_max(unsigned int func) {
	return func == GFX_BLENDFUNC_ADD ||
	       func == GFX_BLENDFUNC_SUBTRACT ||
	       func == GFX_BLENDFUNC_MAX;
}

PRIVATE NONNULL((1, 2)) void CC
rambuffer_getgfx(struct video_buffer *__restrict self,
                 struct video_buffer_gfx *__restrict result,
                 gfx_blendmode_t blendmode, uintptr_t flags,
                 video_color_t colorkey) {
	struct video_rambuffer *me;
	me = (struct video_rambuffer *)self;
	assert(me->vb_ops == &rambuffer_ops);
	result->bfx_ops.fxo_getcolor = (colorkey & VIDEO_COLOR_ALPHA_MASK) != 0
	                               ? &libvideo_gfx_ramgfx_getcolor_with_key
	                               : &libvideo_gfx_ramgfx_getcolor;
	/* Detect special blend modes. */
	if (blendmode == GFX_BLENDINFO_OVERRIDE) {
		result->bfx_ops.fxo_putcolor = &libvideo_gfx_ramgfx_putcolor_noblend;
	} else if (blendmode == GFX_BLENDINFO_ALPHA) {
		result->bfx_ops.fxo_putcolor = &libvideo_gfx_ramgfx_putcolor_alphablend;
	} else if (GFX_BLENDINFO_GET_SRCRGB(blendmode) == GFX_BLENDMODE_ONE &&
	           GFX_BLENDINFO_GET_SRCA(blendmode) == GFX_BLENDMODE_ONE &&
	           GFX_BLENDINFO_GET_DSTRGB(blendmode) == GFX_BLENDMODE_ZERO &&
	           GFX_BLENDINFO_GET_DSTA(blendmode) == GFX_BLENDMODE_ZERO &&
	           is_add_subtract_or_max(GFX_BLENDINFO_GET_FUNRGB(blendmode)) &&
	           is_add_subtract_or_max(GFX_BLENDINFO_GET_FUNA(blendmode))) {
		result->bfx_ops.fxo_putcolor = &libvideo_gfx_ramgfx_putcolor_noblend;
	} else {
		result->bfx_ops.fxo_putcolor = &libvideo_gfx_ramgfx_putcolor;
	}
	result->bfx_ops.fxo_line     = &libvideo_gfx_ramgfx_line;
	result->bfx_ops.fxo_vline    = &libvideo_gfx_ramgfx_vline;
	result->bfx_ops.fxo_hline    = &libvideo_gfx_ramgfx_hline;
	result->bfx_ops.fxo_fill     = &libvideo_gfx_ramgfx_fill;
	result->bfx_ops.fxo_rect     = &libvideo_gfx_ramgfx_rect;
	result->bfx_ops.fxo_blit     = &libvideo_gfx_ramgfx_blit;
	result->bfx_ops.fxo_stretch  = &libvideo_gfx_ramgfx_stretch;

	result->bfx_buffer   = me;
	result->bfx_blend    = blendmode;
	result->bfx_flags    = flags;
	result->bfx_colorkey = colorkey;

	result->bfx_driver[VIDEO_BUFFER_RAMGFX_DATA]   = me->vb_data;
	result->bfx_driver[VIDEO_BUFFER_RAMGFX_STRIDE] = (void *)(uintptr_t)me->vb_stride;
	result->bfx_driver[VIDEO_BUFFER_RAMGFX_SIZEX]  = (void *)(uintptr_t)me->vb_size_x;
	result->bfx_driver[VIDEO_BUFFER_RAMGFX_SIZEY]  = (void *)(uintptr_t)me->vb_size_y;
}



LOCAL struct video_buffer_ops *CC get_rambuffer_ops(void) {
	struct video_buffer_ops *result;
	result = &rambuffer_ops;
	if (!result->vi_destroy) {
		result->vi_lock   = &rambuffer_lock;
		result->vi_unlock = &rambuffer_unlock;
		result->vi_getgfx = &rambuffer_getgfx;
		COMPILER_WRITE_BARRIER();
		result->vi_destroy = &rambuffer_destroy;
	}
	return result;
}



/* Create a new RAM-based video buffer */
INTERN WUNUSED /*REF*/ struct video_buffer *CC
libvideo_rambuffer_create(size_t size_x, size_t size_y,
                          struct video_codec *__restrict codec,
                          struct video_palette *palette) {
	/*REF*/ struct video_rambuffer *result;
	struct video_rambuffer_requirements req;
	assert(codec);
	/* Figure out buffer requirements. */
	(*codec->vc_rambuffer_requirements)(size_x, size_y, &req);

	/* Allocate heap memory for the buffer */
	result = (/*REF*/ struct video_rambuffer *)malloc(sizeof(struct video_rambuffer));
	if unlikely(!result)
		goto err;
	result->vb_data = (byte_t *)calloc(1, req.vbs_bufsize);
	if unlikely(!result->vb_data)
		goto err_result;
	result->vb_stride          = req.vbs_stride;
	result->vb_total           = req.vbs_bufsize;
	result->vb_refcnt          = 1;
	result->vb_ops             = get_rambuffer_ops();
	result->vb_format.vf_codec = codec;
	result->vb_format.vf_pal   = palette;
	result->vb_size_x          = size_x;
	result->vb_size_y          = size_y;
	return result;
err_result:
	free(result);
err:
	return NULL;
}




DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_RAM_BUFFER_C */
