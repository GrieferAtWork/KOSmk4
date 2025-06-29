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
#ifndef GUARD_LIBVIDEO_GFX_ANIM_C
#define GUARD_LIBVIDEO_GFX_ANIM_C 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/sched/shared-lock.h>

#include <assert.h>
#include <atomic.h>
#include <malloc.h>
#include <stddef.h>
#include <string.h>

#include <libvideo/codec/format.h>
#include <libvideo/codec/palette.h>
#include <libvideo/gfx/anim.h>
#include <libvideo/gfx/buffer.h>

#include "anim.h"
#include "buffer.h"
#include "ram-buffer.h"

DECL_BEGIN

struct oneframe_anim: video_anim {
	REF struct video_buffer *ofa_frame; /* [1..1][const] The one-and-only frame */
};

PRIVATE NONNULL((1)) void CC
oneframe_anim_destroy(struct video_anim *__restrict self) {
	struct oneframe_anim *me = (struct oneframe_anim *)self;
	video_buffer_decref(me->ofa_frame);
	free(me);
}

PRIVATE ATTR_OUT(1) void CC
oneframe_anim_populate_info(struct video_anim_frameinfo *__restrict info) {
	info->vafi_frameid         = 0;
	info->vafi_showfor.tv_sec  = 999999;
	info->vafi_showfor.tv_usec = 999999;
}

PRIVATE WUNUSED ATTR_IN(1) ATTR_OUT(2) REF struct video_buffer *CC
oneframe_anim_firstframe(struct video_anim const *__restrict self,
                         struct video_anim_frameinfo *__restrict info) {
	struct oneframe_anim *me = (struct oneframe_anim *)self;
	oneframe_anim_populate_info(info);
	video_buffer_incref(me->ofa_frame);
	return me->ofa_frame;
}

PRIVATE WUNUSED ATTR_IN(1) ATTR_INOUT(2) ATTR_INOUT(3) REF struct video_buffer *CC
oneframe_anim_nextframe(struct video_anim const *__restrict self,
                        /*inherit(on_success)*/ REF struct video_buffer *__restrict buf,
                        struct video_anim_frameinfo *__restrict info) {
	/* These is no next frame -- indicate that the caller
	 * should  sleep really long,  and don't do anything. */
	(void)self;
	oneframe_anim_populate_info(info);
	return buf;
}


PRIVATE struct video_anim_ops oneframe_anim_ops = {};
PRIVATE struct video_anim_ops *CC _oneframe_anim_ops(void) {
	if (!oneframe_anim_ops.vao_destroy) {
		oneframe_anim_ops.vao_nextframe  = &oneframe_anim_nextframe;
		oneframe_anim_ops.vao_firstframe = &oneframe_anim_firstframe;
		COMPILER_WRITE_BARRIER();
		oneframe_anim_ops.vao_destroy = &oneframe_anim_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &oneframe_anim_ops;
}


/* Create a single-frame video animation from a given buffer.
 * The  returned  animation object  always  re-return `frame'
 * when a call is made to `video_anim_firstframe', and trying
 * to load any  other frame via  `video_anim_nextframe' is  a
 * no-op.
 * @return: * :   The controller for the single-frame video animation
 * @return: NULL: Out of memory. */
DEFINE_PUBLIC_ALIAS(video_anim_fromframe, libvideo_anim_fromframe);
INTERN WUNUSED ATTR_INOUT(1) REF struct video_anim *CC
libvideo_anim_fromframe(struct video_buffer *__restrict frame) {
	REF struct oneframe_anim *result;
	result = (REF struct oneframe_anim *)malloc(sizeof(struct oneframe_anim));
	if unlikely(!result)
		goto err;
	result->va_refcnt = 1;
	result->va_ops    = _oneframe_anim_ops();
	result->va_xdim = frame->vb_xdim;
	result->va_ydim = frame->vb_ydim;
	result->ofa_frame = frame;
	video_buffer_incref(frame);
	return result;
err:
	return NULL;
}







struct cached_frame {
	REF struct video_buffer    *cf_frame;     /* [1..1][const] The cached frame */
	struct video_anim_frameinfo cf_frameinfo; /* [const] Information about `cf_frame' */
};

struct cached_anim: video_anim {
	struct shared_lock       ca_lock;    /* Lock for the cache */
	video_anim_frame_id      ca_framec;  /* [if(!ca_base, [>= 1])][const_if(!ca_base)][lock(ca_lock)] # of cached frames */
	struct cached_frame     *ca_framev;  /* [0..ca_framec][const_if(!ca_base)][owned][lock(ca_lock)] # Cached frames */
	struct video_format      ca_fmt;     /* [lock(ca_lock)] Video format override for caches (unused when `.vf_codec' is `NULL') */
	REF struct video_anim   *ca_base;    /* [0..1][lock(WRITE(ca_lock && CLEAR_ONCE), READ(ca_lock || ATOMIC))] Base animation, or "NULL" once fully cached */
	REF struct video_buffer *ca_bbuf;    /* [0..1][lock(ca_lock)] Base animation work buffer, or "NULL" if not loaded or done */
	unsigned int             ca_type;    /* [const] Type of buffer used by caches */
};

PRIVATE NONNULL((1)) void CC
cached_anim_destroy(struct video_anim *__restrict self) {
	video_anim_frame_id i;
	struct cached_anim *me = (struct cached_anim *)self;
	for (i = 0; i < me->ca_framec; ++i)
		video_buffer_decref(me->ca_framev[i].cf_frame);
	if (me->ca_fmt.vf_pal)
		video_palette_decref(me->ca_fmt.vf_pal);
	if (me->ca_base)
		video_anim_decref(me->ca_base);
	if (me->ca_bbuf)
		video_buffer_decref(me->ca_bbuf);
	free(me->ca_framev);
	free(me);
}

PRIVATE WUNUSED ATTR_IN(1) ATTR_OUT(2) REF struct video_buffer *CC
cached_anim_firstframe(struct video_anim const *__restrict self,
                       struct video_anim_frameinfo *__restrict info) {
	REF struct video_buffer *result;
	struct cached_frame *frame;
	struct video_format *frame_format;
	struct cached_anim *me = (struct cached_anim *)self;

	/* Check for special case: animation was already fully loaded */
	if (!atomic_read(&me->ca_base)) {
		assert(me->ca_framec >= 1);
		frame = &me->ca_framev[0];
		memcpy(info, &frame->cf_frameinfo,
		       sizeof(struct video_anim_frameinfo));
		video_buffer_incref(frame->cf_frame);
		return frame->cf_frame;
	}

	/* Acquire lock */
	shared_lock_acquire(&me->ca_lock);

	/* Check if first frame was already allocated */
	if unlikely(me->ca_framec >= 1) {
		frame = &me->ca_framev[0];
		goto unlock_and_return_frame;
	}

	/* Allocate a frame for the first time. */
	assert(me->ca_base);
	assert(!me->ca_bbuf);
	frame = (struct cached_frame *)malloc(sizeof(struct cached_frame));
	if unlikely(!frame)
		goto err_lock;
	me->ca_bbuf = video_anim_firstframe(me->ca_base, &frame->cf_frameinfo);
	if unlikely(!me->ca_bbuf)
		goto err_lock_frame;
	frame_format = &me->ca_bbuf->vb_format;
	if (me->ca_fmt.vf_codec)
		frame_format = &me->ca_fmt;
	frame->cf_frame = libvideo_buffer_convert_or_copy(me->ca_bbuf, frame_format->vf_codec,
	                                                  frame_format->vf_pal, me->ca_type);
	if unlikely(!frame->cf_frame)
		goto err_lock_frame_bbuf;

	/* Remember the first frame */
	me->ca_framec = 1;
	me->ca_framev = frame;

	/* Return the now-cached frame */
unlock_and_return_frame:
	memcpy(info, &frame->cf_frameinfo,
	       sizeof(struct video_anim_frameinfo));
	result = frame->cf_frame;
	video_buffer_incref(result);
	shared_lock_release(&me->ca_lock);
	return result;
err_lock_frame_bbuf:
	video_buffer_decref(me->ca_bbuf);
	me->ca_bbuf = NULL;
err_lock_frame:
	free(frame);
err_lock:
	shared_lock_release(&me->ca_lock);
	return NULL;
}

PRIVATE WUNUSED ATTR_IN(1) ATTR_INOUT(2) ATTR_INOUT(3) REF struct video_buffer *CC
cached_anim_nextframe(struct video_anim const *__restrict self,
                      /*inherit(on_success)*/ REF struct video_buffer *__restrict buf,
                      struct video_anim_frameinfo *__restrict info) {
	REF struct video_buffer *result;
	REF struct video_buffer *next_frame;
	struct video_format *frame_format;
	struct cached_frame *frame;
	struct cached_anim *me = (struct cached_anim *)self;
	video_anim_frame_id next_id = info->vafi_frameid + 1;

	/* Check for special case: animation was already fully loaded */
	if (!atomic_read(&me->ca_base)) {
		assert(me->ca_framec >= 1);
		if (next_id >= me->ca_framec)
			next_id = 0;
		assert(buf == me->ca_framev[info->vafi_frameid].cf_frame);
return_next_cached_frame:
		frame = &me->ca_framev[next_id];
		memcpy(info, &frame->cf_frameinfo,
		       sizeof(struct video_anim_frameinfo));
		video_buffer_incref(frame->cf_frame);
		assertf(atomic_read(&buf->vb_refcnt) >= 2, "1 by the cache, and one by the caller");
		atomic_dec(&buf->vb_refcnt);
		return frame->cf_frame;
	}

	/* Acquire lock */
	shared_lock_acquire(&me->ca_lock);
	assert(info->vafi_frameid < me->ca_framec);
	assert(me->ca_framev);
	assert(buf == me->ca_framev[info->vafi_frameid].cf_frame);

	/* Check for special case: the specific frame requested was already loaded. */
	if (next_id < me->ca_framec) {
		frame = &me->ca_framev[next_id];
		goto unlock_and_return_frame;
	}

	/* Check for special case: animation has been
	 * fully  loaded now, and  we must start over */
	if unlikely(!me->ca_base) {
		assert(!me->ca_bbuf);
		frame = &me->ca_framev[0];
		goto unlock_and_return_frame;
	}

	/* Make sure the "ca_framev" vector has space. */
	frame = (struct cached_frame *)realloc(me->ca_framev,
	                                       me->ca_framec + 1,
	                                       sizeof(struct cached_frame));
	if unlikely(!frame)
		goto err_lock;
	me->ca_framev = frame;
	frame += me->ca_framec;

	/* Check for special case: was the output buffer lost? */
	if (!me->ca_bbuf) {
		video_anim_frame_id n_skip;
		me->ca_bbuf = video_anim_firstframe(me->ca_base, info);
		if unlikely(!me->ca_bbuf)
			goto err_lock;
		n_skip = me->ca_framec;
		assert(n_skip >= 1);
		do {
			REF struct video_buffer *next_frame;
			next_frame = video_anim_nextframe(me->ca_base, me->ca_bbuf, info);
			if unlikely(!next_frame)
				goto err_lock_bbuf;
			me->ca_bbuf = next_frame;
		} while (--n_skip);
	}

	/* Load the next frame in line */
	assert(me->ca_base);
	assert(me->ca_bbuf);
	memcpy(&frame->cf_frameinfo, &frame[-1].cf_frameinfo,
	       sizeof(struct video_anim_frameinfo));
	next_frame = video_anim_nextframe(me->ca_base, me->ca_bbuf, &frame->cf_frameinfo);
	if unlikely(!next_frame)
		goto err_lock;
	me->ca_bbuf = next_frame;

	/* Check for special case: animation has rewound itself (meaning we are done) */
	if (frame->cf_frameinfo.vafi_frameid < frame[-1].cf_frameinfo.vafi_frameid) {
		REF struct video_buffer *old_bbuf;
		REF struct video_anim *old_base;
		frame = (struct cached_frame *)realloc(me->ca_framev, me->ca_framec,
		                                       sizeof(struct cached_frame));
		if likely(frame)
			me->ca_framev = frame;
		old_bbuf = me->ca_bbuf;
		old_base = me->ca_base;
		me->ca_bbuf = NULL;
		me->ca_base = NULL;
		shared_lock_release(&me->ca_lock);
		video_buffer_decref(old_bbuf);
		video_anim_decref(old_base);
		next_id = 0;
		goto return_next_cached_frame;
	}

	/* Convert output buffer formats. */
	frame_format = &me->ca_bbuf->vb_format;
	if (me->ca_fmt.vf_codec)
		frame_format = &me->ca_fmt;
	frame->cf_frame = libvideo_buffer_convert_or_copy(me->ca_bbuf, frame_format->vf_codec,
	                                                  frame_format->vf_pal, me->ca_type);
	if unlikely(!frame->cf_frame) {
		/* Failed to convert frame -> must reset output
		 * buffer since it's not 1 frame too far  ahead */
		REF struct video_buffer *old_bbuf;
err_lock_bbuf:
		old_bbuf = me->ca_bbuf;
		me->ca_bbuf = NULL;
		shared_lock_release(&me->ca_lock);
		video_buffer_decref(old_bbuf);
		goto err;
	}

	/* Remember that another frame has been loaded. */
	++me->ca_framec;
unlock_and_return_frame:
	memcpy(info, &frame->cf_frameinfo,
	       sizeof(struct video_anim_frameinfo));
	result = frame->cf_frame;
	video_buffer_incref(result);
	shared_lock_release(&me->ca_lock);
	assertf(atomic_read(&buf->vb_refcnt) >= 2, "1 by the cache, and one by the caller");
	atomic_dec(&buf->vb_refcnt);
	return result;
err_lock:
	shared_lock_release(&me->ca_lock);
err:
	return NULL;
}


PRIVATE struct video_anim_ops cached_anim_ops = {};
PRIVATE ATTR_RETNONNULL WUNUSED struct video_anim_ops *CC _cached_anim_ops(void) {
	if (!cached_anim_ops.vao_destroy) {
		cached_anim_ops.vao_nextframe  = &cached_anim_nextframe;
		cached_anim_ops.vao_firstframe = &cached_anim_firstframe;
		COMPILER_WRITE_BARRIER();
		cached_anim_ops.vao_destroy = &cached_anim_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &cached_anim_ops;
}



/* Return  a wrapper  for `self'  that caches  animation frames during
 * the first loop, and simply replays them during any subsequent loop.
 * @param: codec:   When non-null,  animation frames  are converted  into
 *                  this pixel format, rather than being copied verbatim.
 * @param: palette: Used with `codec' (if non-NULL)
 * @param: type:    The type of video buffer to use for cached images. */
DEFINE_PUBLIC_ALIAS(video_anim_cached, libvideo_anim_cached);
INTERN WUNUSED ATTR_INOUT(1) ATTR_IN_OPT(2) ATTR_IN_OPT(3) REF struct video_anim *CC
libvideo_anim_cached(struct video_anim *__restrict self,
                     struct video_codec const *codec,
                     struct video_palette *palette,
                     unsigned int type) {
	REF struct cached_anim *result;
	if (codec && !(codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL))
		palette = NULL;

	if (self->va_ops == &cached_anim_ops) {
		/* Check for special case: `self' is already cached and uses a compatible format */
		struct cached_anim *me = (struct cached_anim *)self;
		if (!codec && (type == VIDEO_BUFFER_AUTO || me->ca_type == type)) {
			video_anim_incref(me);
			return me;
		}
	} else if (self->va_ops == &oneframe_anim_ops) {
		/* Check for special case: Single-frame animations */
		REF struct video_anim *oneframe_result;
		REF struct video_buffer *converted;
		struct oneframe_anim *me = (struct oneframe_anim *)self;
		struct video_buffer *frame = me->ofa_frame;
		if (codec == NULL)
			codec = frame->vb_format.vf_codec;
		if (palette == NULL)
			palette = frame->vb_format.vf_pal;
		if (frame->vb_format.vf_codec == codec &&
		    frame->vb_format.vf_pal == palette &&
		    (type == VIDEO_BUFFER_AUTO || (type == VIDEO_BUFFER_RAM &&
		                                   frame->vb_ops == &rambuffer_ops))) {
			video_anim_incref(me);
			return me;
		}
		converted = libvideo_buffer_convert(frame, codec, palette, type);
		if unlikely(!converted)
			goto err;
		oneframe_result = libvideo_anim_fromframe(converted);
		video_buffer_decref(converted);
		return oneframe_result;
	}

	result = (REF struct cached_anim *)malloc(sizeof(struct cached_anim));
	if unlikely(!result)
		goto err;
	result->va_refcnt = 1;
	result->va_ops    = _cached_anim_ops();
	result->va_xdim = self->va_xdim;
	result->va_ydim = self->va_ydim;
	shared_lock_init(&result->ca_lock);
	result->ca_framec = 0;
	result->ca_framev = NULL;
	result->ca_fmt.vf_codec = NULL;
	result->ca_fmt.vf_pal   = NULL;
	if (codec) {
		if (palette)
			video_palette_incref(palette);
		result->ca_fmt.vf_codec = codec;
		result->ca_fmt.vf_pal   = palette;
	}
	video_anim_incref(self);
	result->ca_base = self;
	result->ca_bbuf = NULL;
	result->ca_type = type;
	return result;
err:
	return NULL;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_ANIM_C */
