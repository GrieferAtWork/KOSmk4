/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBVIDEO_GFX_CUSTOM_BUFFER_C
#define GUARD_LIBVIDEO_GFX_CUSTOM_BUFFER_C 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <errno.h>
#include <malloc.h>
#include <stddef.h>

#include "buffer.h"
#include "custom-buffer.h"
#include "gfx.h"

DECL_BEGIN

PRIVATE ATTR_INOUT(1) ATTR_OUT(2) int FCC
custom_rlock(struct video_buffer *__restrict self,
             struct video_lock *__restrict result) {
	struct custom_buffer *me = (struct custom_buffer *)self;
	if (me->cb_rlock)
		return (*me->cb_rlock)(me->cb_cookie, result);
	errno = ENOTSUP;
	return -1;
}

PRIVATE ATTR_INOUT(1) ATTR_OUT(2) int FCC
custom_wlock(struct video_buffer *__restrict self,
             struct video_lock *__restrict result) {
	struct custom_buffer *me = (struct custom_buffer *)self;
	if (me->cb_wlock)
		return (*me->cb_wlock)(me->cb_cookie, result);
	errno = ENOTSUP;
	return -1;
}

PRIVATE ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(FCC custom_unlock)(struct video_buffer *__restrict self,
                           struct video_lock *__restrict lock) {
	struct custom_buffer *me = (struct custom_buffer *)self;
	if (me->cb_unlock)
		(*me->cb_unlock)(me->cb_cookie, lock);
}


/* Indices for driver-specific data of "custom" video buffers. */
#define CUSTOM_GFX_GETPIXEL 0
#define CUSTOM_GFX_SETPIXEL 1
#define CUSTOM_GFX_COOKIE   2


PRIVATE ATTR_IN(1) video_pixel_t CC
custom_gfx__getpixel(struct video_gfx const *__restrict self,
                     video_coord_t abs_x, video_coord_t abs_y) {
	video_buffer_custom_getpixel_t cb;
	cb = (video_buffer_custom_getpixel_t)self->_vx_driver[CUSTOM_GFX_GETPIXEL];
	return (*cb)(self->_vx_driver[CUSTOM_GFX_COOKIE], abs_x, abs_y);
}

PRIVATE ATTR_IN(1) void CC
custom_gfx__setpixel(struct video_gfx const *__restrict self,
                     video_coord_t abs_x, video_coord_t abs_y,
                     video_pixel_t pixel) {
	video_buffer_custom_setpixel_t cb;
	cb = (video_buffer_custom_setpixel_t)self->_vx_driver[CUSTOM_GFX_SETPIXEL];
	(*cb)(self->_vx_driver[CUSTOM_GFX_COOKIE], abs_x, abs_y, pixel);
}


PRIVATE ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
custom_initgfx(struct video_gfx *__restrict self) {
	struct custom_buffer *me = (struct custom_buffer *)self->vx_buffer;
	libvideo_gfx_init_fullclip(self);
	self->_vx_driver[CUSTOM_GFX_GETPIXEL] = (void *)me->cb_getpixel;
	self->_vx_driver[CUSTOM_GFX_SETPIXEL] = (void *)me->cb_setpixel;
	self->_vx_driver[CUSTOM_GFX_COOKIE]   = me->cb_cookie;

	/* Default pixel accessors */
	self->_vx_xops.vgfx_getpixel = &custom_gfx__getpixel;
	self->_vx_xops.vgfx_setpixel = &custom_gfx__setpixel;

	/* Load generic operator defaults */
	libvideo_gfx_generic_populate(self);
	return self;
}

PRIVATE NONNULL((1)) void FCC
custom_destroy(struct video_buffer *__restrict self) {
	struct custom_buffer *me = (struct custom_buffer *)self;
	if (me->cb_destroy)
		(*me->cb_destroy)(me->cb_cookie);
	free(self);
}


#undef custom_ops
PRIVATE struct video_buffer_ops custom_ops = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _custom_ops(void) {
	if unlikely(!custom_ops.vi_destroy) {
		custom_ops.vi_rlock      = &custom_rlock;
		custom_ops.vi_wlock      = &custom_wlock;
		custom_ops.vi_unlock     = &custom_unlock;
		custom_ops.vi_initgfx    = &custom_initgfx;
		custom_ops.vi_updategfx  = &libvideo_buffer_generic_updategfx;
		custom_ops.vi_noblendgfx = &libvideo_buffer_generic_noblend;
		COMPILER_WRITE_BARRIER();
		custom_ops.vi_destroy = &custom_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &custom_ops;
}
#define custom_ops (*_custom_ops())


/* Construct a special video buffer which, rather than being backed by memory
 * or implemented using hardware acceleration,  does all its pixel I/O  using
 * the provided function pointers.
 *
 * WARNING: The  given  `getpixel'  / `setpixel'  callbacks  better be
 *          fast, or any GFX on the returned buffer will take forever!
 *
 * @param: size_x:   X dimension of the returned video buffer
 * @param: size_y:   Y dimension of the returned video buffer
 * @param: codec:    [1..1] Video codec used for color<=>pixel conversion, as
 *                          well  as  pixel  I/O (when  rlock/wlock  is given
 *                          and returns `0')
 * @param: palette:  [0..1] Palette to-be used with `codec' (if needed)
 * @param: getpixel: [1..1] Mandatory pixel read operator (passed coords are absolute and guarantied in-bounds)
 * @param: setpixel: [1..1] Mandatory pixel write operator (passed coords are absolute and guarantied in-bounds)
 * @param: destroy:  [0..1] Optional callback invoked when the returned buffer is destroyed
 * @param: rlock:    [0..1] Optional callback to lock video memory for reading (when missing, or doesn't return `0', `getpixel' is used)
 * @param: wlock:    [0..1] Optional callback to lock video memory for writing (when missing, or doesn't return `0', `setpixel' is used)
 * @param: unlock:   [0..1] Optional callback invoked to release video locks previously acquired by `rlock' or `wlock'
 * @param: cookie:   [?..?] Cookie argument passed to all user-supplied operators */
DEFINE_PUBLIC_ALIAS(video_buffer_forcustom, libvideo_buffer_forcustom);
INTERN WUNUSED NONNULL((3, 5, 6)) REF struct video_buffer *LIBVIDEO_GFX_CC
libvideo_buffer_forcustom(video_dim_t size_x, video_dim_t size_y,
                          struct video_codec const *codec, struct video_palette *palette,
                          video_buffer_custom_getpixel_t getpixel,
                          video_buffer_custom_setpixel_t setpixel,
                          video_buffer_custom_destroy_t destroy,
                          video_buffer_custom_lock_t rlock,
                          video_buffer_custom_lock_t wlock,
                          video_buffer_custom_unlock_t unlock,
                          void *cookie) {
	REF struct custom_buffer *result;
	result = (REF struct custom_buffer *)malloc(sizeof(struct custom_buffer));
	if unlikely(!result)
		goto err;
	if (!(codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL))
		palette = NULL;
	result->vb_ops = &custom_ops;
	result->vb_format.vf_codec = codec;
	result->vb_format.vf_pal   = palette;
	if (palette)
		video_palette_incref(palette);
	result->vb_xdim     = size_x;
	result->vb_ydim     = size_y;
	result->vb_refcnt   = 1;
	result->cb_getpixel = getpixel;
	result->cb_setpixel = setpixel;
	result->cb_destroy  = destroy;
	result->cb_rlock    = rlock ? rlock : wlock;
	result->cb_wlock    = wlock;
	result->cb_unlock   = unlock;
	result->cb_cookie   = cookie;
	return result;
err:
	return NULL;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_CUSTOM_BUFFER_C */
