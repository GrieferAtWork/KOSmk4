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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_C
#define GUARD_LIBVIDEO_GFX_BUFFER_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>

#include <assert.h>
#include <errno.h>
#include <stddef.h>

#include <libvideo/gfx/buffer.h>

#include "buffer.h"
#include "swgfx.h"

DECL_BEGIN

/* Generic implementations for video buffer operators. */
INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
libvideo_buffer_swgfx_updategfx(struct video_gfx *__restrict self, unsigned int what) {
	libvideo_swgfx_update(self, what);
	return self;
}

INTERN WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) int FCC
libvideo_buffer_notsup_lock(struct video_buffer *__restrict self,
                            struct video_lock *__restrict lock) {
	(void)self;
	(void)lock;
	errno = ENOTSUP;
	return -1;
}

INTERN ATTR_INOUT(1) NONNULL((2)) void
NOTHROW(FCC libvideo_buffer_noop_unlock)(struct video_buffer *__restrict self,
                                         struct video_lock *__restrict lock) {
	(void)self;
	(void)lock;
	COMPILER_IMPURE();
}


INTERN WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) int FCC
libvideo_buffer_generic_rlockregion(struct video_buffer *__restrict self,
                                    struct video_regionlock *__restrict lock) {
	int result = video_buffer_rlock(self, &lock->vrl_lock);
	/*if likely(result == 0)*/ {
		lock->vrl_xbas = lock->_vrl_rect.vcr_xmin;
		lock->vrl_lock.vl_data += lock->_vrl_rect.vcr_ymin * lock->vrl_lock.vl_stride;
	}
	return result;
}

INTERN WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) int FCC
libvideo_buffer_generic_wlockregion(struct video_buffer *__restrict self,
                                    struct video_regionlock *__restrict lock) {
	int result = video_buffer_wlock(self, &lock->vrl_lock);
	/*if likely(result == 0)*/ {
		lock->vrl_xbas = lock->_vrl_rect.vcr_xmin;
		lock->vrl_lock.vl_data += lock->_vrl_rect.vcr_ymin * lock->vrl_lock.vl_stride;
	}
	return result;
}

INTERN ATTR_INOUT(1) NONNULL((2)) void
NOTHROW(FCC libvideo_buffer_generic_unlockregion)(struct video_buffer *__restrict self,
                                                  struct video_regionlock *__restrict lock) {
	lock->vrl_lock.vl_data -= lock->_vrl_rect.vcr_ymin * lock->vrl_lock.vl_stride;
	video_buffer_unlock(self, &lock->vrl_lock);
}








/* Convert `self' into the specified domain and format.
 *
 * If `self' specifies rotation/etc. in its GFX flags, and that rotation  differs
 * from whatever is specified by `format' (including the case where the state  of
 * the `VIDEO_GFX_F_XYSWAP' flag  differs, meaning dimensions  of `self' and  the
 * returned buffer won't match up), that rotation info is materialized, such that
 * this function can also be  used to rotate the actual  V-mem of a video  buffer
 * whilst at the same time copying/converting it into a different format.
 *
 * @return: * : The converted video buffer.
 * @return: NULL: [errno=ENOMEM]  Insufficient memory (either regular RAM, or V-RAM)
 * @return: NULL: [errno=ENOTSUP] Given `format->vbf_codec' is not supported by `domain ?: video_surface_getdomain(self)'
 * @return: NULL: [errno=*] Failed to convert buffer for some reason (s.a. `errno') */
DEFINE_PUBLIC_ALIAS(video_surface_convert, libvideo_surface_convert);
DEFINE_PUBLIC_ALIAS(video_surface_convert_distinct, libvideo_surface_convert_distinct);
INTERN WUNUSED ATTR_IN(1) NONNULL((2)) ATTR_IN(3) REF struct video_buffer *CC
libvideo_surface_convert(struct video_surface const *__restrict self,
                         struct video_domain const *domain,
                         struct video_buffer_format const *format) {
	/* Check for simple case: buffer is already in the expected format. */
	if (video_surface_getdomain(self) == domain) {
		struct video_buffer *buffer = video_surface_getbuffer(self);
		if (video_buffer_hasformat(buffer, format)) {
			video_buffer_incref(buffer);
			return buffer;
		}
	}
	return libvideo_surface_convert_distinct(self, domain, format);
}

INTERN WUNUSED ATTR_IN(1) NONNULL((2)) ATTR_IN(3) REF struct video_buffer *CC
libvideo_surface_convert_distinct(struct video_surface const *__restrict self,
                                  struct video_domain const *domain,
                                  struct video_buffer_format const *format) {
	REF struct video_buffer *result;
	struct video_gfx src_gfx, dst_gfx;
	video_surface_getgfx(self, &src_gfx, GFX_BLENDMODE_OVERRIDE);

	/* Create a new video buffer. */
	result = video_domain_newbuffer(domain, format,
	                                video_gfx_getxdim(&src_gfx),
	                                video_gfx_getydim(&src_gfx),
	                                VIDEO_DOMAIN_NEWBUFFER_F_NORMAL);
	if likely(result) {
		/* Blit the entirety of the source buffer into the target buffer. */
		video_buffer_getgfx(result, &dst_gfx, GFX_BLENDMODE_OVERRIDE);

		/* At this point, XYSWAP flags should once again cancel out */
		assert(video_gfx_getxdim(&dst_gfx) == video_gfx_getxdim(&src_gfx));
		assert(video_gfx_getydim(&dst_gfx) == video_gfx_getydim(&src_gfx));

		/* Do the blit (which will also do any format conversion for us) */
		video_gfx_bitblit(&dst_gfx, 0, 0,
		                  &src_gfx, 0, 0,
		                  video_gfx_getxdim(&dst_gfx),
		                  video_gfx_getydim(&dst_gfx));
	}
	return result;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_C */
