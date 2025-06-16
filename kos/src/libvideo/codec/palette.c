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
#ifndef GUARD_LIBVIDEO_CODEC_PALETTE_C
#define GUARD_LIBVIDEO_CODEC_PALETTE_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "palette.h"

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <assert.h>
#include <atomic.h>
#include <malloc.h>
#include <malloca.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <libvideo/codec/palette.h>

DECL_BEGIN

LOCAL ATTR_CONST video_twochannels_t CC
abs_color_delta(video_color_t c1, video_color_t c2) {
	video_stwochannels_t dr = (video_stwochannels_t)VIDEO_COLOR_GET_RED(c1) - VIDEO_COLOR_GET_RED(c2);
	video_stwochannels_t dg = (video_stwochannels_t)VIDEO_COLOR_GET_GREEN(c1) - VIDEO_COLOR_GET_GREEN(c2);
	video_stwochannels_t db = (video_stwochannels_t)VIDEO_COLOR_GET_BLUE(c1) - VIDEO_COLOR_GET_BLUE(c2);
	video_stwochannels_t da = (video_stwochannels_t)VIDEO_COLOR_GET_ALPHA(c1) - VIDEO_COLOR_GET_ALPHA(c2);
	/* Euclidean distance */
	return (video_twochannels_t)(dr * dr) +
	       (video_twochannels_t)(dg * dg) +
	       (video_twochannels_t)(db * db) +
	       (video_twochannels_t)(da * da);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN((1)) video_pixel_t
NOTHROW(CC linear_video_palette_color2pixel)(struct video_palette const *__restrict self,
                                             video_color_t color) {
	video_pixel_t i, winner = 0;
	video_twochannels_t winner_delta = (video_twochannels_t)-1;
	for (i = 0; i < self->vp_cnt; ++i) {
		video_color_t pal_color = self->vp_pal[i];
		video_twochannels_t delta = abs_color_delta(pal_color, color);
		if (winner_delta > delta) {
			winner_delta = delta;
			winner       = i;
			if (winner_delta == 0)
				break;
		}
	}
	return winner;
}


PRIVATE NONNULL((1)) void
NOTHROW(CC default_video_palette_destroy)(struct video_palette *__restrict self) {
	free(self);
}


struct video_palette_tree {
	union {
		video_color_t   vpt_color;           /* Color */
		video_channel_t vpt_chans[4];        /* Channels */
	};
	video_pixel_t              vpt_pixel; /* Pixel */
	struct video_palette_tree *vpt_lhs;   /* [0..1] Left node */
	struct video_palette_tree *vpt_rhs;   /* [0..1] Right node */
};


/* Create a new (uninitialized) palette for `count' colors.
 *
 * This function is allowed to allocate a larger palette  than
 * requested if doing  so improves  performances, though  when
 * this is done, all additional palette entries will have been
 * initialized to `0'
 *
 * On success, the caller must initialize:
 * - return->vp_pal[0]
 * - return->vp_pal[1]
 * - ...
 * - return->vp_pal[count - 2]
 * - return->vp_pal[count - 1]
 *
 * @return: * :   The newly created palette
 * @return: NULL: Out of memory */
INTERN WUNUSED REF struct video_palette *CC
libvideo_palette_create(size_t count) {
	REF struct video_palette *result;
	uintptr_t treeoff = offsetof(struct video_palette, vp_pal) +
	                    (count * sizeof(video_color_t));
	result = (REF struct video_palette *)malloc(treeoff +
	                                            (count * sizeof(struct video_palette_tree)));
	if unlikely(!result)
		goto err;
	result->vp_color2pixel = &linear_video_palette_color2pixel;
	result->vp_destroy     = &default_video_palette_destroy;
	result->vp_refcnt      = 1;
	result->vp_cnt         = count;
	result->_vp_tree = (struct video_palette_tree *)((byte_t *)result + treeoff);
	/*result->vp_pal[...] = ...;*/ /* To-be initialized by the caller... */
	return result;
err:
	return NULL;
}

struct pal_item {
	union {
		video_color_t   pi_color;
		video_channel_t pi_chans[4];
	};
	video_pixel_t pi_pixel;
};


PRIVATE int __LIBCCALL
compare_chan(void const *_a, void const *_b, void *_chan_id) {
	struct pal_item const *a = (struct pal_item const *)_a;
	struct pal_item const *b = (struct pal_item const *)_b;
	unsigned int chan_id = (unsigned int)(uintptr_t)_chan_id;
	return (int)a->pi_chans[chan_id] - (int)b->pi_chans[chan_id];
}

/* @param: chan_id: Channel ID (index into `pi_chans') */
PRIVATE WUNUSED NONNULL((1)) ATTR_INOUTS(2, 3) struct video_palette_tree *CC
vp_build_kd_tree(struct video_palette_tree **p_alloc, struct pal_item *items,
                 video_pixel_t n, unsigned int chan_id, unsigned int n_chans) {
	struct video_palette_tree *node;
	video_pixel_t mid;
	if (n <= 0)
		return NULL;
	qsort_r(items, n, sizeof(struct pal_item),
	        &compare_chan, (void *)(uintptr_t)chan_id);

	/* Allocate a node for the center-most color when sorting by "chan_id" */
	mid  = n >> 1;
	node = (*p_alloc)++;
	node->vpt_pixel = items[mid].pi_pixel;
	node->vpt_color = items[mid].pi_color;

	/* Move on to the next color channel and use it to
	 * recursively  build the left- and right leafs of
	 * the k-d tree */
	__builtin_assume(n_chans == 3 || n_chans == 4);
	chan_id = (chan_id + 1) % n_chans;
	node->vpt_lhs = vp_build_kd_tree(p_alloc, items, mid, chan_id, n_chans);
	node->vpt_rhs = vp_build_kd_tree(p_alloc, items + mid + 1, n - mid - 1, chan_id, n_chans);
	return node;
}

struct kd_tree_result {
	video_pixel_t       ktr_pixel;
	video_twochannels_t ktr_delta;
};

#define DEFINE_vp_kd_treeN_find(N)                                              \
	LOCAL void                                                                  \
	NOTHROW(CC vp_kd_tree##N##_find)(struct video_palette_tree const *node,     \
	                                 video_color_t color, unsigned int chan_id, \
	                                 struct kd_tree_result *result) {           \
		struct video_palette_tree const *near;                                  \
		struct video_palette_tree const *far;                                   \
		video_twochannels_t delta;                                              \
		video_stwochannels_t diff;                                              \
		union {                                                                 \
			video_color_t color;                                                \
			video_channel_t chans[4];                                           \
		} color_data;                                                           \
		delta = abs_color_delta(color, node->vpt_color);                        \
		if (result->ktr_delta > delta) {                                        \
			result->ktr_delta = delta;                                          \
			result->ktr_pixel = node->vpt_pixel;                                \
		}                                                                       \
		                                                                        \
		__builtin_assume(chan_id < N);                                          \
		color_data.color = color;                                               \
		diff = (video_stwochannels_t)color_data.chans[chan_id] -                \
		       (video_stwochannels_t)node->vpt_chans[chan_id];                  \
		if (diff < 0) {                                                         \
			near = node->vpt_lhs;                                               \
			far  = node->vpt_rhs;                                               \
		} else {                                                                \
			near = node->vpt_rhs;                                               \
			far  = node->vpt_lhs;                                               \
		}                                                                       \
		if (++chan_id >= N)                                                     \
			chan_id = 0;                                                        \
		if (near)                                                               \
			vp_kd_tree##N##_find(near, color, chan_id, result);                 \
		if ((video_twochannels_t)(diff * diff) < result->ktr_delta) {           \
			if (far)                                                            \
				vp_kd_tree##N##_find(far, color, chan_id, result);              \
		}                                                                       \
	}
DEFINE_vp_kd_treeN_find(3) /* 3 channels: RGB */
DEFINE_vp_kd_treeN_find(4) /* 4 channels: RGBA */
#undef DEFINE_vp_kd_treeN_find

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t
NOTHROW(CC vp_kd_tree3_color2pixel)(struct video_palette const *__restrict self,
                                    video_color_t color) {
	struct kd_tree_result result;
	result.ktr_delta = (video_twochannels_t)-1;
	result.ktr_pixel = 0;
	vp_kd_tree3_find(self->_vp_tree, color, 0, &result);
	return result.ktr_pixel;
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t
NOTHROW(CC vp_kd_tree4_color2pixel)(struct video_palette const *__restrict self,
                                    video_color_t color) {
	struct kd_tree_result result;
	result.ktr_delta = (video_twochannels_t)-1;
	result.ktr_pixel = 0;
	vp_kd_tree4_find(self->_vp_tree, color, 0, &result);
	return result.ktr_pixel;
}


/* Optimize lookup times for `self', making `self->vp_color2pixel'
 * execute in sub-linear time (if possible). This function must be
 * called whenever `vp_pal' was  modified, and was called  before.
 * Prior  to being called, `self->vp_color2pixel' still works, but
 * executed in linear time (so you really want to call this one to
 * speed up palette lookups)
 *
 * This  function  is NOT  thread-safe,  so `self->vp_color2pixel'
 * must not be called by other threads until this function returns
 * @return: * : The optimized color palette */
INTERN ATTR_RETNONNULL WUNUSED ATTR_INOUT(1) REF struct video_palette *CC
libvideo_palette_optimize(REF struct video_palette *__restrict self) {
	video_pixel_t i;
	struct pal_item *items;
	struct video_palette_tree *p_alloc;
	struct video_palette_tree *root;
	unsigned int n_chans = 3;
	if unlikely(!self->vp_cnt)
		goto fail; /* TODO: Special optimization for 1- and 2-color palettes */
	items = (struct pal_item *)malloca(self->vp_cnt, sizeof(struct pal_item));
	if unlikely(!items)
		goto fail;
	for (i = 0; i < self->vp_cnt; ++i) {
		items[i].pi_color = self->vp_pal[i];
		items[i].pi_pixel = i;
		if (items[i].pi_chans[3] != 0xff)
			n_chans = 4; /* Need to account for alpha channel */
	}

	/* TODO: Remove duplicate colors from "items" (for palettes that are padded with repeats of previous colors) */
	/* TODO: Special  handling for 1- and 2-color palettes needs
	 *       to happen again AFTER duplicate colors were removed */

	p_alloc = self->_vp_tree;
	root = vp_build_kd_tree(&p_alloc, items, self->vp_cnt, 0, n_chans);
	assert(root == self->_vp_tree);
	assert(p_alloc > self->_vp_tree && p_alloc <= (self->_vp_tree + self->vp_cnt));
	(void)root;
	self->vp_color2pixel = n_chans == 4 ? &vp_kd_tree4_color2pixel
	                                    : &vp_kd_tree3_color2pixel;
	return self;
fail:
	self->vp_color2pixel = &linear_video_palette_color2pixel;
	return self;
}

DEFINE_PUBLIC_ALIAS(video_palette_create, libvideo_palette_create);
DEFINE_PUBLIC_ALIAS(video_palette_optimize, libvideo_palette_optimize);

DECL_END

#endif /* !GUARD_LIBVIDEO_CODEC_PALETTE_C */
