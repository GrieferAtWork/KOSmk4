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
#ifndef GUARD_LIBVIDEO_GFX_EMPTY_BUFFER_C
#define GUARD_LIBVIDEO_GFX_EMPTY_BUFFER_C 1
#define _KOS_SOURCE 1

#include "empty-buffer.h"

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

#include "buffer.h"
#include "gfx.h"

DECL_BEGIN


PRIVATE struct video_buffer_ops empty_video_buffer_ops;
PRIVATE struct video_buffer empty_video_buffer;
PRIVATE byte_t const empty_video_buffer_data[1] = { 0 };


/* Stub GFX functions for the empty video buffer. */
PRIVATE video_color_t CC
empty_video_buffer_gfx_getcolor(struct video_buffer_gfx *__restrict self,
                                uintptr_t UNUSED(x), uintptr_t UNUSED(y)) {
	assert(self->bfx_buffer == &empty_video_buffer);
	(void)self;
	return 0;
}

PRIVATE void CC
empty_video_buffer_gfx_putcolor(struct video_buffer_gfx *__restrict self,
                                uintptr_t UNUSED(x), uintptr_t UNUSED(y),
                                video_color_t UNUSED(color)) {
	assert(self->bfx_buffer == &empty_video_buffer);
	(void)self;
}

PRIVATE void CC
empty_video_buffer_gfx_line(struct video_buffer_gfx *__restrict self,
                            intptr_t UNUSED(x1), intptr_t UNUSED(y1),
                            intptr_t UNUSED(x2), intptr_t UNUSED(y2),
                            video_color_t UNUSED(color)) {
	assert(self->bfx_buffer == &empty_video_buffer);
	(void)self;
}

PRIVATE void CC
empty_video_buffer_gfx_vline(struct video_buffer_gfx *__restrict self,
                             uintptr_t UNUSED(x),
                             uintptr_t UNUSED(y1), uintptr_t UNUSED(y2),
                             video_color_t UNUSED(color)) {
	assert(self->bfx_buffer == &empty_video_buffer);
	(void)self;
}

PRIVATE void CC
empty_video_buffer_gfx_hline(struct video_buffer_gfx *__restrict self,
                             uintptr_t UNUSED(y),
                             uintptr_t UNUSED(x1), uintptr_t UNUSED(x2),
                             video_color_t UNUSED(color)) {
	assert(self->bfx_buffer == &empty_video_buffer);
	(void)self;
}

PRIVATE void CC
empty_video_buffer_gfx_fill(struct video_buffer_gfx *__restrict self,
                            uintptr_t UNUSED(x), uintptr_t UNUSED(y),
                            size_t UNUSED(size_x), size_t UNUSED(size_y),
                            video_color_t UNUSED(color)) {
	assert(self->bfx_buffer == &empty_video_buffer);
	(void)self;
}

PRIVATE void CC
empty_video_buffer_gfx_rect(struct video_buffer_gfx *__restrict self,
                            uintptr_t UNUSED(x), uintptr_t UNUSED(y),
                            size_t UNUSED(size_x), size_t UNUSED(size_y),
                            video_color_t UNUSED(color)) {
	assert(self->bfx_buffer == &empty_video_buffer);
	(void)self;
}

PRIVATE void CC
empty_video_buffer_gfx_blit(struct video_buffer_gfx *__restrict self,
                            intptr_t UNUSED(dst_x), intptr_t UNUSED(dst_y),
                            struct video_buffer_gfx *__restrict UNUSED(src),
                            intptr_t UNUSED(src_x), intptr_t UNUSED(src_y),
                            size_t UNUSED(size_x), size_t UNUSED(size_y)) {
	assert(self->bfx_buffer == &empty_video_buffer);
	(void)self;
}

PRIVATE void CC
empty_video_buffer_gfx_stretch(struct video_buffer_gfx *__restrict self,
                               intptr_t UNUSED(dst_x), intptr_t UNUSED(dst_y),
                               size_t UNUSED(dst_size_x), size_t UNUSED(dst_size_y),
                               struct video_buffer_gfx *__restrict UNUSED(src),
                               intptr_t UNUSED(src_x), intptr_t UNUSED(src_y),
                               size_t UNUSED(src_size_x), size_t UNUSED(src_size_y)) {
	assert(self->bfx_buffer == &empty_video_buffer);
	(void)self;
}




PRIVATE void LIBVIDEO_GFX_CC
empty_video_buffer_destroy(struct video_buffer *__restrict self) {
	(void)self;
	__assertion_failedf("empty_video_buffer_destroy()",
	                    "Must never get here!");
}

PRIVATE NONNULL((1, 2)) int CC
empty_video_buffer_lock(struct video_buffer *__restrict self,
                        struct video_lock *__restrict result) {
	assert(self == &empty_video_buffer);
	/* Must assign a valid, non-NULL, but empty buffer.
	 * Technically, any arbitrary non-NULL address would work, but
	 * set an actual, read-only buffer so-as to catch bad writes. */
	(void)self;
	result->vl_data   = (byte_t *)empty_video_buffer_data;
	result->vl_size   = 0;
	result->vl_stride = 0;
	return 0;
}

PRIVATE NONNULL((1, 2)) void CC
empty_video_buffer_unlock(struct video_buffer *__restrict self,
                          struct video_lock const *__restrict lock) {
	assert(self == &empty_video_buffer);
	assert(lock->vl_data == (byte_t *)empty_video_buffer_data);
	assert(lock->vl_size == 0);
	assert(lock->vl_stride == 0);
	(void)self;
	(void)lock;
}

PRIVATE void CC
empty_video_buffer_getgfx(struct video_buffer *__restrict self,
                          struct video_buffer_gfx *__restrict result,
                          gfx_blendmode_t blendmode, uintptr_t flags,
                          video_color_t colorkey) {
	assert(self == &empty_video_buffer);
	result->bfx_ops.fxo_getcolor = &empty_video_buffer_gfx_getcolor;
	result->bfx_ops.fxo_putcolor = &empty_video_buffer_gfx_putcolor;
	result->bfx_ops.fxo_line     = &empty_video_buffer_gfx_line;
	result->bfx_ops.fxo_vline    = &empty_video_buffer_gfx_vline;
	result->bfx_ops.fxo_hline    = &empty_video_buffer_gfx_hline;
	result->bfx_ops.fxo_fill     = &empty_video_buffer_gfx_fill;
	result->bfx_ops.fxo_rect     = &empty_video_buffer_gfx_rect;
	result->bfx_ops.fxo_blit     = &empty_video_buffer_gfx_blit;
	result->bfx_ops.fxo_stretch  = &empty_video_buffer_gfx_stretch;
	result->bfx_buffer           = self;
	result->bfx_blend            = blendmode;
	result->bfx_flags            = flags;
	result->bfx_colorkey         = colorkey;
	memset(result->bfx_driver, 0, sizeof(result->bfx_driver));
}

INTERN ATTR_RETNONNULL struct video_buffer *CC
get_empty_video_buffer(void) {
	struct video_buffer *result;
	result = &empty_video_buffer;
	if (!result->vb_ops) {
		empty_video_buffer_ops.vi_destroy = &empty_video_buffer_destroy;
		empty_video_buffer_ops.vi_lock    = &empty_video_buffer_lock;
		empty_video_buffer_ops.vi_unlock  = &empty_video_buffer_unlock;
		empty_video_buffer_ops.vi_getgfx  = &empty_video_buffer_getgfx;
		result->vb_refcnt                 = 1;
		result->vb_size_x                 = 0;
		result->vb_size_y                 = 0;
		/* The codec doesn't really matter, but use the most common one (RGBA8888) */
		result->vb_format.vf_codec = video_codec_lookup(VIDEO_CODEC_RGBA8888);
		result->vb_format.vf_pal   = NULL;
		COMPILER_WRITE_BARRIER();
		result->vb_ops = &empty_video_buffer_ops;
	}
	return result;
}


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_EMPTY_BUFFER_C */
