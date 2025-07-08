/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.removeif(x -> x.startswith("-O"));
gcc_opt.append("-O3"); // Force _all_ optimizations because stuff in here is performance-critical
]]]*/
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


/* How to convert a difference between color channels
 * into  a  weight when  considering  similar colors. */
#if 1 /* Euclidean distance */
#define chan_diff2weight(c, v) (video_twochannels_t)(v * v)
#elif 0 /* Absolute distance in orthogonal space */
#define chan_diff2weight(c, v) abs(v)
#elif 0 /* Euclidean distance (weighted) */
PRIVATE shift_t const chan_weight[4] = { 0, 1, 0, 2 };
#define chan_diff2weight_r(v)  ((video_twochannels_t)(v * v))
#define chan_diff2weight_g(v)  ((video_twochannels_t)(v * v) << 1)
#define chan_diff2weight_b(v)  ((video_twochannels_t)(v * v))
#define chan_diff2weight_a(v)  ((video_twochannels_t)(v * v) << 2)
#define chan_diff2weight(c, v) ((video_twochannels_t)(v * v) << chan_weight[c])
#elif 0 /* Euclidean distance (weighted, inverse) */
PRIVATE shift_t const chan_weight[4] = { 1, 0, 1, 0 };
#define chan_diff2weight_r(v)  ((video_twochannels_t)(v * v) << 1)
#define chan_diff2weight_g(v)  ((video_twochannels_t)(v * v))
#define chan_diff2weight_b(v)  ((video_twochannels_t)(v * v) << 1)
#define chan_diff2weight_a(v)  ((video_twochannels_t)(v * v))
#define chan_diff2weight(c, v) ((video_twochannels_t)(v * v) << chan_weight[c])
#elif 0 /* Euclidean distance (weighted, truncating) */
PRIVATE shift_t const chan_weight[4] = { 1, 0, 1, 0 };
#define chan_diff2weight_r(v)  ((video_twochannels_t)(v * v) >> 1)
#define chan_diff2weight_g(v)  ((video_twochannels_t)(v * v))
#define chan_diff2weight_b(v)  ((video_twochannels_t)(v * v) >> 1)
#define chan_diff2weight_a(v)  ((video_twochannels_t)(v * v))
#define chan_diff2weight(c, v) ((video_twochannels_t)(v * v) >> chan_weight[c])
#endif

#ifndef chan_diff2weight_r
#define chan_diff2weight_r(v) chan_diff2weight(0, v)
#endif /* !chan_diff2weight_r */
#ifndef chan_diff2weight_g
#define chan_diff2weight_g(v) chan_diff2weight(1, v)
#endif /* !chan_diff2weight_g */
#ifndef chan_diff2weight_b
#define chan_diff2weight_b(v) chan_diff2weight(2, v)
#endif /* !chan_diff2weight_b */
#ifndef chan_diff2weight_a
#define chan_diff2weight_a(v) chan_diff2weight(3, v)
#endif /* !chan_diff2weight_a */

LOCAL ATTR_CONST video_twochannels_t CC
abs_color_delta3(video_color_t c1, video_color_t c2) {
	video_stwochannels_t dr = (video_stwochannels_t)VIDEO_COLOR_GET_RED(c1) - VIDEO_COLOR_GET_RED(c2);
	video_stwochannels_t dg = (video_stwochannels_t)VIDEO_COLOR_GET_GREEN(c1) - VIDEO_COLOR_GET_GREEN(c2);
	video_stwochannels_t db = (video_stwochannels_t)VIDEO_COLOR_GET_BLUE(c1) - VIDEO_COLOR_GET_BLUE(c2);
	return chan_diff2weight_r(dr) +
	       chan_diff2weight_g(dg) +
	       chan_diff2weight_b(db);
}

LOCAL ATTR_CONST video_twochannels_t CC
abs_color_delta4(video_color_t c1, video_color_t c2) {
	video_stwochannels_t dr = (video_stwochannels_t)VIDEO_COLOR_GET_RED(c1) - VIDEO_COLOR_GET_RED(c2);
	video_stwochannels_t dg = (video_stwochannels_t)VIDEO_COLOR_GET_GREEN(c1) - VIDEO_COLOR_GET_GREEN(c2);
	video_stwochannels_t db = (video_stwochannels_t)VIDEO_COLOR_GET_BLUE(c1) - VIDEO_COLOR_GET_BLUE(c2);
	video_stwochannels_t da = (video_stwochannels_t)VIDEO_COLOR_GET_ALPHA(c1) - VIDEO_COLOR_GET_ALPHA(c2);
	return chan_diff2weight_r(dr) + chan_diff2weight_g(dg) +
	       chan_diff2weight_b(db) + chan_diff2weight_a(da);
}

typedef ATTR_PURE_T WUNUSED_T ATTR_IN_T((1)) video_pixel_t
NOTHROW_T(CC *PVIDEO_PALETTE_COLOR2PIXEL)(struct video_palette const *__restrict self,
                                          video_color_t color);

PRIVATE ATTR_PURE WUNUSED ATTR_IN((1)) video_pixel_t
NOTHROW(CC video_palette_color2pixel_0)(struct video_palette const *__restrict self,
                                        video_color_t color) {
	(void)self;
	(void)color;
	COMPILER_IMPURE();
	return 0;
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN((1)) video_pixel_t
NOTHROW(CC video_palette_color2pixel_1)(struct video_palette const *__restrict self,
                                        video_color_t color) {
	(void)self;
	(void)color;
	return self->vp_pal[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN((1)) video_pixel_t
NOTHROW(CC video_palette_color2pixel_2_c3)(struct video_palette const *__restrict self,
                                           video_color_t color) {
	video_twochannels_t delta0 = abs_color_delta3(self->vp_pal[0], color);
	video_twochannels_t delta1 = abs_color_delta3(self->vp_pal[1], color);
	return delta0 < delta1 ? 0 : 1;
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN((1)) video_pixel_t
NOTHROW(CC video_palette_color2pixel_2_c4)(struct video_palette const *__restrict self,
                                           video_color_t color) {
	video_twochannels_t delta0 = abs_color_delta4(self->vp_pal[0], color);
	video_twochannels_t delta1 = abs_color_delta4(self->vp_pal[1], color);
	return delta0 < delta1 ? 0 : 1;
}

LOCAL ATTR_CONST WUNUSED PVIDEO_PALETTE_COLOR2PIXEL
NOTHROW(CC video_palette_get_special_color2pixel)(video_pixel_t n_colors) {
	switch (n_colors) {
	case 0:
		return &video_palette_color2pixel_0;
	case 1:
		return &video_palette_color2pixel_1;
	case 2:
		return &video_palette_color2pixel_2_c4;
	default: break;
	}
	return NULL;
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN((1)) video_pixel_t
NOTHROW(CC linear_video_palette_color2pixel)(struct video_palette const *__restrict self,
                                             video_color_t color) {
	video_pixel_t i, winner = 0;
	video_twochannels_t winner_delta = (video_twochannels_t)-1;
	for (i = 0; i < self->vp_cnt; ++i) {
		video_color_t pal_color = self->vp_pal[i];
		video_twochannels_t delta = abs_color_delta4(pal_color, color);
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
		video_color_t   vpt_color;        /* Color */
		video_channel_t vpt_chans[4];     /* Channels */
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
libvideo_palette_create(video_pixel_t count) {
	REF struct video_palette *result;
	uintptr_t treeoff = offsetof(struct video_palette, vp_pal) +
	                    (count * sizeof(video_color_t));
	result = (REF struct video_palette *)malloc(treeoff +
	                                            (count * sizeof(struct video_palette_tree)));
	if unlikely(!result)
		goto err;
	result->vp_color2pixel = video_palette_get_special_color2pixel(count)
	                         ?: &linear_video_palette_color2pixel;
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


PRIVATE WUNUSED NONNULL((1, 2)) int __LIBCCALL
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
		video_twochannels_t weight;                                             \
		video_stwochannels_t diff;                                              \
		union {                                                                 \
			video_color_t color;                                                \
			video_channel_t chans[4];                                           \
		} color_data;                                                           \
		delta = abs_color_delta##N(color, node->vpt_color);                     \
		if (result->ktr_delta > delta) {                                        \
			result->ktr_delta = delta;                                          \
			result->ktr_pixel = node->vpt_pixel;                                \
		}                                                                       \
		                                                                        \
		__builtin_assume(chan_id < N);                                          \
		color_data.color = color;                                               \
		diff = (video_stwochannels_t)color_data.chans[chan_id] -                \
		       (video_stwochannels_t)node->vpt_chans[chan_id];                  \
		weight = chan_diff2weight(chan_id, diff);                               \
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
		if (weight < result->ktr_delta) {                                       \
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

PRIVATE WUNUSED NONNULL((1, 2)) int __LIBCCALL
compare_color(void const *_a, void const *_b) {
	struct pal_item const *a = (struct pal_item const *)_a;
	struct pal_item const *b = (struct pal_item const *)_b;
	if (a->pi_color < b->pi_color)
		return -1;
	if (a->pi_color > b->pi_color)
		return 1;
	return 0;
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
	video_pixel_t i, count = self->vp_cnt;
	struct pal_item *items;
	struct video_palette_tree *p_alloc;
	struct video_palette_tree *root;
	unsigned int n_chans = 3;
	PVIDEO_PALETTE_COLOR2PIXEL spec;

	/* Calculate palette flags */
	self->vp_flags = VIDEO_PALETTE_F_NORMAL;
	for (i = 0 ; i < count; ++i) {
		video_color_t c = self->vp_pal[i];
		if (VIDEO_COLOR_GET_ALPHA(c) != VIDEO_CHANNEL_MAX)
			self->vp_flags |= VIDEO_PALETTE_F_ALPHA;
	}

	/* Special handling for certain small palettes */
	spec = video_palette_get_special_color2pixel(count);
	if unlikely(spec) {
		if (spec == &video_palette_color2pixel_2_c4 &&
		    VIDEO_COLOR_GET_ALPHA(self->vp_pal[0]) == VIDEO_CHANNEL_MAX &&
		    VIDEO_COLOR_GET_ALPHA(self->vp_pal[1]) == VIDEO_CHANNEL_MAX)
			spec = &video_palette_color2pixel_2_c3;
		self->vp_color2pixel = spec;
		goto done;
	}
	items = (struct pal_item *)malloca(count, sizeof(struct pal_item));
	if unlikely(!items)
		goto fail;
	for (i = 0; i < count; ++i) {
		items[i].pi_color = self->vp_pal[i];
		items[i].pi_pixel = i;
		if (items[i].pi_chans[3] != 0xff)
			n_chans = 4; /* Need to account for alpha channel */
	}

	/* Sort "items" for whole colors (so we can detect duplicates) */
	qsort(items, count, sizeof(struct pal_item), &compare_color);

	/* Remove duplicate colors from "items" (for palettes that  are
	 * padded with repeats of previous colors, or just with a bunch
	 * of trailing 0es) */
	for (i = 1; i < count; ++i) {
		video_color_t color = items[i - 1].pi_color;
		struct pal_item *curr = &items[i];
		video_pixel_t duplicates = 0;
		while (color == curr[duplicates].pi_color) {
			++duplicates;
			if (i + duplicates >= count)
				break;
		}
		if (duplicates > 1) {
			video_pixel_t after = count - (i + duplicates);
			memmovedown(curr, curr + duplicates,
			            after, sizeof(struct pal_item));
			count -= duplicates;
		}
	}

	/* Special handling for certain small palettes */
	spec = video_palette_get_special_color2pixel(count);
	if unlikely(spec) {
		if (spec == &video_palette_color2pixel_2_c4 && n_chans == 3)
			spec = &video_palette_color2pixel_2_c3;
		self->vp_color2pixel = spec;
		goto done;
	}

	/* TODO: When "n_chans == 3", it might be even faster to use an "oct-tree" */

	/* Build the K/D tree */
	p_alloc = self->_vp_tree;
	root = vp_build_kd_tree(&p_alloc, items, count, 0, n_chans);
	assert(root == self->_vp_tree);
	assert(p_alloc > self->_vp_tree && p_alloc <= (self->_vp_tree + count));
	(void)root;
	self->vp_color2pixel = n_chans == 4 ? &vp_kd_tree4_color2pixel
	                                    : &vp_kd_tree3_color2pixel;
	return self;
fail:
	self->vp_color2pixel = &linear_video_palette_color2pixel;
done:
	return self;
}

DEFINE_PUBLIC_ALIAS(video_palette_create, libvideo_palette_create);
DEFINE_PUBLIC_ALIAS(video_palette_optimize, libvideo_palette_optimize);

DECL_END

#endif /* !GUARD_LIBVIDEO_CODEC_PALETTE_C */
