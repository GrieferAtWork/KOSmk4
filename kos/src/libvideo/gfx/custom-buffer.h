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
#ifndef GUARD_LIBVIDEO_GFX_CUSTOM_BUFFER_H
#define GUARD_LIBVIDEO_GFX_CUSTOM_BUFFER_H 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>

#include <libvideo/codec/palette.h>
#include <libvideo/gfx/buffer.h>

DECL_BEGIN

struct custom_buffer: video_buffer {
	video_buffer_custom_getpixel_t cb_getpixel; /* [1..1][const] ... */
	video_buffer_custom_setpixel_t cb_setpixel; /* [1..1][const] ... */
	video_buffer_custom_destroy_t  cb_destroy;  /* [0..1][const] ... */
	video_buffer_custom_lock_t     cb_rlock;    /* [0..1][const] ... */
	video_buffer_custom_lock_t     cb_wlock;    /* [0..1][const] ... */
	video_buffer_custom_unlock_t   cb_unlock;   /* [0..1][const] ... */
	void                          *cb_cookie;   /* [?..?][const] ... */
};


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
INTDEF WUNUSED NONNULL((3, 5, 6)) REF struct video_buffer *LIBVIDEO_GFX_CC
libvideo_buffer_forcustom(video_dim_t size_x, video_dim_t size_y,
                          struct video_codec const *codec, struct video_palette *palette,
                          video_buffer_custom_getpixel_t getpixel,
                          video_buffer_custom_setpixel_t setpixel,
                          video_buffer_custom_destroy_t destroy,
                          video_buffer_custom_lock_t rlock,
                          video_buffer_custom_lock_t wlock,
                          video_buffer_custom_unlock_t unlock,
                          void *cookie);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_CUSTOM_BUFFER_H */
