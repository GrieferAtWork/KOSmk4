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
#ifndef GUARD_LIBVIDEO_GFX_GFX_PALETTIZE_C
#define GUARD_LIBVIDEO_GFX_GFX_PALETTIZE_C 1
#define __VIDEO_BUFFER_const /* nothing -- TODO: This shouldn't be in this file! */
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/overflow.h>

#include <kos/types.h>

#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <libvideo/color.h>
#include <libvideo/gfx/api.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/codec/codec.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

#include "codec/codec.h"
#include "gfx-palettize.h"
#include "ramdomain.h"
#include "swgfx.h"

#undef HAVE_LOG
#if 1
#include <sys/syslog.h>
#define LOG(...) syslog(LOG_DEBUG, __VA_ARGS__)
#define HAVE_LOG
#else
#define LOG(...) (void)0
#endif

DECL_BEGIN

union color {
	video_color_t c;
	struct {
		video_channel_t r;
		video_channel_t g;
		video_channel_t b;
		video_channel_t a;
	};
};

#define round_div(x, y) (((x) + ((y) >> 1)) / (y))



/************************************************************************/
/* HISTOGRAM PALETTIZATION (adjusted to avg out lost color bits)        */
/* NOTE: Because of memory constraints, only usable without alpha       */
/************************************************************************/
#undef HIST_USE_32BIT_COUNT
#if 1
#define HIST_USE_32BIT_COUNT
#endif

/* # of color bits encoded as index into histogram */
#define HIST_RBITS 5
#define HIST_GBITS 5
#define HIST_BBITS 5

/* # of color bits lost during histogram index encode (aka. quantization) */
#define HIST_RLOST (8 - HIST_RBITS)
#define HIST_GLOST (8 - HIST_GBITS)
#define HIST_BLOST (8 - HIST_BBITS)

/* # of distinct channel values representable in histogram indices. */
#define HIST_RCOUNT (1 << HIST_RBITS)
#define HIST_GCOUNT (1 << HIST_GBITS)
#define HIST_BCOUNT (1 << HIST_BBITS)

/* Quantize / de-quantize color channels */
#define hist_quantize_r(r)   ((r) >> HIST_RLOST)
#define hist_quantize_g(g)   ((g) >> HIST_RLOST)
#define hist_quantize_b(b)   ((b) >> HIST_RLOST)
#define hist_dequantize_r(r) ((r) << HIST_RLOST)
#define hist_dequantize_g(g) ((g) << HIST_RLOST)
#define hist_dequantize_b(b) ((b) << HIST_RLOST)

/* Return the mask of color bits lost during quantization */
#define hist_remainder_r(r) ((r) & ((1 << HIST_RLOST) - 1))
#define hist_remainder_g(g) ((g) & ((1 << HIST_RLOST) - 1))
#define hist_remainder_b(b) ((b) & ((1 << HIST_RLOST) - 1))

struct hist_bin {
#ifdef HIST_USE_32BIT_COUNT
	uint32_t  hb_count;         /* # of times this histogram bucket was used */
#else /* HIST_USE_32BIT_COUNT */
	uint16_t  hb_count;         /* # of times this histogram bucket was used */
#endif /* !HIST_USE_32BIT_COUNT */
	union {
		video_color_t hb_color; /* After histogram generation: the final output color */
		/* NOTE: Your  run-of-the-mill histogram palettization algorithm won't have this
		 *       right here: sums of lost color bits from quantization. -- These will be
		 *       divided `hb_count' and */
		struct {
			uint16_t  hb_rsum;  /* Sum of least significant "HIST_RLOST" bits of this bucket's all "hb_count" uses */
			uint16_t  hb_gsum;  /* Sum of least significant "HIST_GLOST" bits of this bucket's all "hb_count" uses */
			uint16_t  hb_bsum;  /* Sum of least significant "HIST_BLOST" bits of this bucket's all "hb_count" uses */
#ifdef HIST_USE_32BIT_COUNT
			uint16_t _hb_pad;   /* Padding... */
#endif /* HIST_USE_32BIT_COUNT */
		};
	};
};

struct hist {
	union {
		struct hist_bin h_bins[HIST_RCOUNT][HIST_GCOUNT][HIST_BCOUNT];
		struct hist_bin h_colors[HIST_RCOUNT * HIST_GCOUNT * HIST_BCOUNT];
	};
};

PRIVATE WUNUSED NONNULL((1)) int __LIBCCALL
hist_bin_cmp(void const *_lhs, void const *_rhs) {
	struct hist_bin const *lhs = (struct hist_bin const *)_lhs;
	struct hist_bin const *rhs = (struct hist_bin const *)_rhs;
	/* negative compare result, so large bins get sorted to the front */
	if (lhs->hb_count < rhs->hb_count)
		return 1;
	if (lhs->hb_count > rhs->hb_count)
		return -1;
	return 0;
}

/* @param: fail_if_too_many_bins: When the  sum of  pixel counts  from the  most
 *                                significant "palsize" entries of the histogram
 *                                is less than 75% of the source image, fail  by
 *                                returning "1" */
PRIVATE ATTR_NOINLINE WUNUSED ATTR_IN(1) ATTR_OUTS(3, 2) int CC
hist_palettize(struct video_gfx const *__restrict self,
               video_pixel_t palsize, video_color_t *pal,
               bool fail_if_too_many_bins) {
	video_pixel_t x, y;
	struct hist *h = (struct hist *)calloc(sizeof(struct hist));
	if unlikely(!h)
		return -1;
	y = self->vx_hdr.vxh_bymin;
	do {
		x = self->vx_hdr.vxh_bxmin;
		do {
			struct hist_bin *bin;
			union color c;
			/* TODO: Check that "self" is SW-based */
			c.c = (*video_swgfx_getcdrv(self)->xsw_getcolor)(self, x, y);
			bin = &h->h_bins[hist_quantize_r(c.r)]
			                [hist_quantize_g(c.g)]
			                [hist_quantize_b(c.b)];
			++bin->hb_count;
			bin->hb_rsum += hist_remainder_r(c.r);
			bin->hb_gsum += hist_remainder_r(c.g);
			bin->hb_bsum += hist_remainder_r(c.b);
		} while (++x < self->vx_hdr.vxh_bxend);
	} while (++y < self->vx_hdr.vxh_byend);

	/* Finalize histogram (re-add lost color bits).
	 *
	 * This needs to be done **before** sorting, as  the
	 * high `HIST_{RGB}BITS' bits of each hitogram bin's
	 * color are actually stored in as part of the bin's
	 * index. */
	{
		video_channel_t r, g, b;
		for (r = 0; r < HIST_RCOUNT; ++r) {
			for (g = 0; g < HIST_GCOUNT; ++g) {
				for (b = 0; b < HIST_BCOUNT; ++b) {
					struct hist_bin *bin = &h->h_bins[r][g][b];
					if (bin->hb_count) {
						video_channel_t rlost_avg = round_div(bin->hb_rsum, bin->hb_count);
						video_channel_t glost_avg = round_div(bin->hb_gsum, bin->hb_count);
						video_channel_t blost_avg = round_div(bin->hb_bsum, bin->hb_count);
						video_channel_t final_r = hist_dequantize_r(r) | rlost_avg;
						video_channel_t final_g = hist_dequantize_g(g) | glost_avg;
						video_channel_t final_b = hist_dequantize_b(b) | blost_avg;
						bin->hb_color = VIDEO_COLOR_RGB(final_r, final_g, final_b);
					}
				}
			}
		}
	}

	/* Sort histogram such that most-used bins come first */
	qsort(h->h_colors, HIST_RCOUNT * HIST_GCOUNT * HIST_BCOUNT,
	      sizeof(struct hist_bin), &hist_bin_cmp);

	/* The first "palsize" entries of the histogram are now the palette */
	if (palsize > (HIST_RCOUNT * HIST_GCOUNT * HIST_BCOUNT))
		palsize = (HIST_RCOUNT * HIST_GCOUNT * HIST_BCOUNT);

	/* XXX: For small palette sizes, I feel like it would be better
	 *      to  not  just pick  the  first N  colors,  but instead:
	 * #1 Take the most prominent color from the histogram and add it to the palette.
	 * #2 while the palette isn't full:
	 *    #2.1 Find  the  color "h"  from  the histogram  with  the greatest
	 *         >> h.hb_count * min(for (c: palette) distance(c, h.hb_color))
	 *    #2.2 Add this color "h" to the palette
	 *
	 * Possibly do something to the "h.hb_count" in the above  multiply,
	 * as it is the weight by how often a color is used, and I feel like
	 * this can be made better  by a curve with  a ceiling equal to  the
	 * number of pixels within the image's  I/O region. iow: a bin  with
	 * a count of  100 should maybe  only multiply the  value by 2x  the
	 * factor of a bin with a count of 10. */

	/* Check if the histogram is usable */
	if (fail_if_too_many_bins) {
		video_dim_t io_sx = video_gfx_getioxdim(self);
		video_dim_t io_sy = video_gfx_getioydim(self);
		size_t io_pixels  = (size_t)io_sx * io_sy;
		video_pixel_t i;
		size_t pal_pixels = 0;
		for (i = 0; i < palsize; ++i)
			pal_pixels += h->h_colors[i].hb_count;

		/* Fail if less than 75% of GFX colors appear in the histogram */
		io_pixels *= 3;
		io_pixels /= 4;
		if (pal_pixels < io_pixels) {
			free(h);
			return 1;
		}
	}

	/* Log info about how good the histogram is */
#ifdef HAVE_LOG
	{
		video_pixel_t i;
		uint64_t pal_pixels_adj;
		size_t pal_pixels = 0;
		video_dim_t io_sx = video_gfx_getioxdim(self);
		video_dim_t io_sy = video_gfx_getioydim(self);
		size_t io_pixels  = (size_t)io_sx * io_sy;
		for (i = 0; i < palsize; ++i) {
			video_color_t c = h->h_colors[i].hb_color;
			LOG("hist[%3u] = {%#.2I8x,%#.2I8x,%#.2I8x} x%u\n",
			    (unsigned int)i,
			    VIDEO_COLOR_GET_RED(c),
			    VIDEO_COLOR_GET_GREEN(c),
			    VIDEO_COLOR_GET_BLUE(c),
			    (unsigned int)h->h_colors[i].hb_count);
			pal_pixels += h->h_colors[i].hb_count;
		}
		pal_pixels_adj = pal_pixels;
		pal_pixels_adj *= 100 * 10000;
		pal_pixels_adj /= io_pixels;
		LOG("hist:coverage: %u.%04u%% (%u / %u)\n",
		    (unsigned int)(pal_pixels_adj / 10000),
		    (unsigned int)(pal_pixels_adj % 10000),
		    (unsigned int)pal_pixels,
		    (unsigned int)io_pixels);
	}
#endif /* HAVE_LOG */

	/* Write the histogram to the output palette */
	{
		video_pixel_t i;
		for (i = 0; i < palsize; ++i)
			pal[i] = h->h_colors[i].hb_color;
	}

	free(h);
	return 0;
}






/************************************************************************/
/* MEADIAN-CUT PALETTIZATION                                            */
/************************************************************************/
#if 1
typedef uint32_t mc_index_t;
#else
typedef size_t mc_index_t;
#endif

struct median_io {
	video_color_t (LIBVIDEO_GFX_FCC *mio_getcolor)(void const *cookie, mc_index_t i);
	void const                       *mio_cookie;
};

#define median_io_getcolor(self, i) (*(self)->mio_getcolor)((self)->mio_cookie, i)

PRIVATE WUNUSED NONNULL((1, 2)) int __LIBCCALL
median_cmp_r(void const *_a, void const *_b, void *cookie) {
	struct median_io const *io = (struct median_io const *)cookie;
	video_color_t ca = median_io_getcolor(io, *(mc_index_t const *)_a);
	video_color_t cb = median_io_getcolor(io, *(mc_index_t const *)_b);
	return (int)VIDEO_COLOR_GET_RED(ca) - (int)VIDEO_COLOR_GET_RED(cb);
}

PRIVATE WUNUSED NONNULL((1, 2)) int __LIBCCALL
median_cmp_g(void const *_a, void const *_b, void *cookie) {
	struct median_io const *io = (struct median_io const *)cookie;
	video_color_t ca = median_io_getcolor(io, *(mc_index_t const *)_a);
	video_color_t cb = median_io_getcolor(io, *(mc_index_t const *)_b);
	return (int)VIDEO_COLOR_GET_GREEN(ca) - (int)VIDEO_COLOR_GET_GREEN(cb);
}

PRIVATE WUNUSED NONNULL((1, 2)) int __LIBCCALL
median_cmp_b(void const *_a, void const *_b, void *cookie) {
	struct median_io const *io = (struct median_io const *)cookie;
	video_color_t ca = median_io_getcolor(io, *(mc_index_t const *)_a);
	video_color_t cb = median_io_getcolor(io, *(mc_index_t const *)_b);
	return (int)VIDEO_COLOR_GET_BLUE(ca) - (int)VIDEO_COLOR_GET_BLUE(cb);
}

PRIVATE WUNUSED NONNULL((1, 2)) int __LIBCCALL
median_cmp_a(void const *_a, void const *_b, void *cookie) {
	struct median_io const *io = (struct median_io const *)cookie;
	video_color_t ca = median_io_getcolor(io, *(mc_index_t const *)_a);
	video_color_t cb = median_io_getcolor(io, *(mc_index_t const *)_b);
	return (int)VIDEO_COLOR_GET_ALPHA(ca) - (int)VIDEO_COLOR_GET_ALPHA(cb);
}

PRIVATE ATTR_IN(1) NONNULL((2, 5)) void
median_cut(struct median_io const *io,
           mc_index_t *gfx_indices, mc_index_t gfx_start, mc_index_t gfx_end,
           video_color_t *pal, video_pixel_t pal_index, shift_t depth, shift_t max_depth,
           video_color_t constant_alpha) {
	int (__LIBCCALL *compar)(void const *_a, void const *_b, void *cookie);
	video_channel_t rmin = VIDEO_CHANNEL_MAX, rmax = VIDEO_CHANNEL_MIN;
	video_channel_t gmin = VIDEO_CHANNEL_MAX, gmax = VIDEO_CHANNEL_MIN;
	video_channel_t bmin = VIDEO_CHANNEL_MAX, bmax = VIDEO_CHANNEL_MIN;
	video_channel_t amin = VIDEO_CHANNEL_MAX, amax = VIDEO_CHANNEL_MIN;
	video_channel_t rrange, grange, brange, arange;
	uint_fast32_t rsum, gsum, bsum, asum;
	mc_index_t i, gfx_count, median;
	if (pal_index >= ((video_pixel_t)1 << max_depth))
		return;
	assert(gfx_end >= gfx_start);
	gfx_count = gfx_end - gfx_start;
	if (gfx_count <= 0)
		return;

	/* Calculate average of colors from specified index-range. */
	rsum = gsum = bsum = asum = 0;
//	LOG("median_cut(%u, %u, %u, %u): START sum\n", gfx_start, gfx_end, pal_index, depth);
	for (i = gfx_start; i < gfx_end; ++i) {
		mc_index_t trans_i = gfx_indices[i];
		video_color_t gfx_color = median_io_getcolor(io, trans_i) | constant_alpha;
		video_channel_t r = VIDEO_COLOR_GET_RED(gfx_color);
		video_channel_t g = VIDEO_COLOR_GET_GREEN(gfx_color);
		video_channel_t b = VIDEO_COLOR_GET_BLUE(gfx_color);
		video_channel_t a = VIDEO_COLOR_GET_ALPHA(gfx_color);
#define HANDLE_CHANNEL(x) \
		if (x##min > x)   \
			x##min = x;   \
		if (x##max < x)   \
			x##max = x;   \
		x##sum += x
		HANDLE_CHANNEL(r);
		HANDLE_CHANNEL(g);
		HANDLE_CHANNEL(b);
		HANDLE_CHANNEL(a);
#undef HANDLE_CHANNEL
	}
//	LOG("median_cut(%u, %u, %u, %u): END sum\n", gfx_start, gfx_end, pal_index, depth);

	/* Fill in the next palette entry as the average of this range. */
	{
		video_channel_t r = round_div(rsum, gfx_count);
		video_channel_t g = round_div(gsum, gfx_count);
		video_channel_t b = round_div(bsum, gfx_count);
		video_channel_t a = round_div(asum, gfx_count);
		pal[pal_index] = VIDEO_COLOR_RGBA(r, g, b, a);
	}

	/* Check if we're done now. */
	if (depth >= max_depth || gfx_count <= 1)
		return;

	/* Sort indices based on most dominant color channel. */
	rrange = rmax - rmin;
	grange = gmax - gmin;
	brange = bmax - bmin;
	arange = amax - amin;
	if (rrange >= grange && rrange >= brange && rrange >= arange) {
		compar = &median_cmp_r;
	} else if (grange >= brange && grange >= arange) {
		compar = &median_cmp_g;
	} else if (brange >= arange) {
		compar = &median_cmp_b;
	} else {
		compar = &median_cmp_a;
	}

//	LOG("median_cut(%u, %u, %u, %u): START qsort\n", gfx_start, gfx_end, pal_index, depth);
	qsort_r(gfx_indices + gfx_start, gfx_count,
	        sizeof(mc_index_t), compar, (void *)io);
//	LOG("median_cut(%u, %u, %u, %u): END qsort\n", gfx_start, gfx_end, pal_index, depth);

	/* Partition at the median and recursive */
	median = gfx_start + (gfx_count >> 1);
	median_cut(io, gfx_indices, gfx_start, median, pal,
	           pal_index * 2 + 1, depth + 1, max_depth, constant_alpha);
	median_cut(io, gfx_indices, median, gfx_end, pal,
	           pal_index * 2 + 2, depth + 1, max_depth, constant_alpha);
}

PRIVATE ATTR_IN(1) NONNULL((2)) void CC
median_cut_start_impl(struct median_io const *__restrict io,
                      mc_index_t *gfx_indices, mc_index_t io_pixels,
                      video_color_t *pal, shift_t pal_depth,
                      video_color_t constant_alpha) {
#if 1
	median_cut(io, gfx_indices, 0, io_pixels, pal,
	           0, 0, pal_depth, constant_alpha);
#else
	for (;;) {
		struct timeval start, end;
		mc_index_t i;
		for (i = 0; i < io_pixels; ++i)
			gfx_indices[i] = i;
		gettimeofday(&start, NULL);
		median_cut(io, gfx_indices, 0, io_pixels, pal,
		           0, 0, pal_depth, constant_alpha);
		gettimeofday(&end, NULL);
		uint64_t total = end.tv_sec - start.tv_sec;
		total *= 1000000;
		total += end.tv_usec;
		total -= start.tv_usec;
		syslog(LOG_DEBUG, "runtime: %u.%06u\n",
		       (unsigned int)(total / 1000000),
		       (unsigned int)(total % 1000000));
	}
#endif
}

PRIVATE WUNUSED ATTR_PURE video_color_t LIBVIDEO_GFX_FCC
median_io_gfx(void const *cookie, mc_index_t i) {
	/* Fallback median-cut I/O callback using direct GFX color reads (slow) */
	struct video_gfx const *self = (struct video_gfx const *)cookie;
	video_dim_t io_sx = video_gfx_getioxdim(self);
	video_coord_t y = self->vx_hdr.vxh_bymin + (i / io_sx);
	video_coord_t x = self->vx_hdr.vxh_bxmin + (i % io_sx);
	/* TODO: Check that "self" is SW-based */
	return (*video_swgfx_getcdrv(self)->xsw_getcolor)(self, x, y);
}

PRIVATE WUNUSED ATTR_PURE video_color_t LIBVIDEO_GFX_FCC
median_io_buf(void const *cookie, mc_index_t i) {
	return ((video_color_t const *)cookie)[i];
}

PRIVATE ATTR_IN(1) NONNULL((2)) void CC
median_cut_start(struct video_gfx const *__restrict self,
                 mc_index_t *gfx_indices, mc_index_t io_pixels,
                 video_color_t *pal, shift_t pal_depth,
                 video_color_t constant_alpha) {
	struct median_io io;
	if (video_gfx_issurfio(self) &&
	    /* TODO: This actually works for any XXXX8888 codec. Just need to
	     *       "video_gfx_getcodec(self)->vc_color2pixel" the  produced
	     *       palette  entries afterwards, and always pass the codec's
	     *       alpha-mask instead of "constant_alpha". */
	    video_gfx_getcodec(self)->vc_codec == VIDEO_CODEC_RGBA8888) {
		struct video_lock lock;
		if (video_buffer_rlock(video_gfx_getbuffer(self), &lock) == 0) {
			if (lock.vl_stride == (self->vx_hdr.vxh_byend * 4)) {
				io.mio_cookie = lock.vl_data;
				io.mio_getcolor = &median_io_buf;
				median_cut_start_impl(&io, gfx_indices, io_pixels,
				                      pal, pal_depth, constant_alpha);
				video_buffer_unlock(video_gfx_getbuffer(self), &lock);
				return;
			}
			video_buffer_unlock(video_gfx_getbuffer(self), &lock);
		}
	}

	io.mio_cookie = self;
	io.mio_getcolor = &median_io_gfx;
	median_cut_start_impl(&io, gfx_indices, io_pixels,
	                      pal, pal_depth, constant_alpha);
}

/* @param: constant_alpha: Constant alpha addend. Either 0 (include alpha in palette),  or
 *                         `VIDEO_COLOR_ALPHA_MASK' (all palette colors have this as their
 *                         alpha) */
PRIVATE ATTR_NOINLINE WUNUSED ATTR_IN(1) ATTR_OUTS(3, 2) int CC
median_cut_palettize(struct video_gfx const *__restrict self,
                     video_pixel_t palsize, video_color_t *pal,
                     video_color_t constant_alpha) {
	/* This works, and it /is/ technically O(n log n), but JEESH; this is still **really** slow...
	 * Q: It seems like most time is spent inside qsort() -- given that our libc is still  using
	 *    a qsort-compatible sorting function (rather than the *real* qsort), replace qsort with
	 *    a real, compliant impl and see if that speeds things up.
	 * A: I tried by briefly copying some other qsort impls and pasting them at the top of  this
	 *    file, but that didn't end up making this any faster. For my test image (1431x2048) and
	 *    a  palette size of 64 colors, this **always** takes ~2.75sec, no matter what I do with
	 *    qsort...
	 *
	 * TODO: Do a more scientific test of performance by comparing my qsort against
	 *       glibc, both running on an actual linux machine, rather than within KOS
	 * TODO: See if I can dig up someone else's median-cut impl somewhere and compare
	 *       its speed against mine (maybe mine just sucks?)
	 * TODO: Live with median_cut being slow, and adjust documentation accordingly. */
	mc_index_t i, io_pixels, *gfx_indices;
	video_dim_t io_sx = video_gfx_getioxdim(self);
	video_dim_t io_sy = video_gfx_getioydim(self);
	shift_t pal_depth;
	if (OVERFLOW_UMUL(io_sx, io_sy, &io_pixels)) {
		errno = EOVERFLOW;
		return -1;
	}

	/* Figure out how many index bits can fit into the palette.
	 *
	 * This may cause some trailing palette entries to go  unused,
	 * only using those masked by the greatest power-of-2(-1) that
	 * is still smaller than "palsize" */
	for (pal_depth = 0; palsize > ((video_pixel_t)1 << pal_depth); ++pal_depth)
		;

	/* Color index table */
	gfx_indices = (mc_index_t *)malloc(io_pixels, sizeof(mc_index_t));
	if unlikely(!gfx_indices)
		return -1;
	for (i = 0; i < io_pixels; ++i)
		gfx_indices[i] = i;

	/* Clear unused palette entries. */
	{
		video_pixel_t pal_used = (video_pixel_t)1 << pal_depth;
		assert(pal_used <= palsize);
		bzero(pal + pal_used, palsize - pal_used, sizeof(*pal));
	}

	/* Start doing the median-cut. */
	median_cut_start(self, gfx_indices, io_pixels, pal,
	                 pal_depth, constant_alpha);

	free(gfx_indices);
	return 0;
}






/************************************************************************/
/* K-MEANS PALETTIZATION                                                */
/************************************************************************/

/* @param: constant_alpha: Constant alpha addend. Either 0 (include alpha in palette),  or
 *                         `VIDEO_COLOR_ALPHA_MASK' (all palette colors have this as their
 *                         alpha) */
PRIVATE ATTR_NOINLINE WUNUSED ATTR_IN(1) ATTR_OUTS(3, 2) int CC
k_means_palettize(struct video_gfx const *__restrict self,
                  video_pixel_t palsize, video_color_t *pal,
                  video_color_t constant_alpha) {
	(void)constant_alpha;
	/* TODO */
	return hist_palettize(self, palsize, pal, false);
}






/* Construct a (visually pleasing) palette from the pixel area denoted
 * by the I/O region of `self'. The produced palette is stored in  the
 * provided buffer `pal' and consists of exactly `palsize' colors.
 * @param: method: How to calculate the palette
 * @return: 0 : Success
 * @return: -1: [errno=ENOMEM] Insufficient memory for temporaries needed during calculation
 * @return: -1: [errno=EINVAL] Attempted to use "VIDEO_GFX_PALETTIZE_METHOD_F_ALPHA" with
 *                             a  palettization method that doesn't support alpha values.
 * @return: -1: [errno=EINVAL] Invalid `method' and/or `palsize' */
INTERN WUNUSED ATTR_IN(1) ATTR_OUTS(3, 2) int CC
libvideo_gfx_palettize(struct video_gfx const *__restrict self,
                       video_pixel_t palsize, video_color_t *pal,
                       unsigned int method) {
	/* Check for special case: empty palette / GFX I/O area */
	if unlikely(!palsize)
		goto empty_pal;
	if unlikely(self->vx_hdr.vxh_bxmin >= self->vx_hdr.vxh_bxend)
		goto empty_io;
	if unlikely(self->vx_hdr.vxh_bymin >= self->vx_hdr.vxh_byend)
		goto empty_io;

	switch (method) {
	case VIDEO_GFX_PALETTIZE_METHOD_AUTO: {
		/* When "method" is "AUTO", do this:
		 * - Try to use "VIDEO_GFX_PALETTIZE_METHOD_HISTOGRAM"
		 * - Move on to "VIDEO_GFX_PALETTIZE_METHOD_MEDIAN_CUT" if
		 *   it turns out the histogram  covers too little of  the
		 *   image's color space. */
		int hist_status = hist_palettize(self, palsize, pal, true);
		if (hist_status != 1)
			return hist_status;
	}	ATTR_FALLTHROUGH
	case VIDEO_GFX_PALETTIZE_METHOD_MEDIAN_CUT:
		return median_cut_palettize(self, palsize, pal, VIDEO_COLOR_ALPHA_MASK);

	case VIDEO_GFX_PALETTIZE_METHOD_HISTOGRAM:
		return hist_palettize(self, palsize, pal, false);

		/* Since HIST doesn't support alpha, treat AUTO+ALPHA like MEDIAN_CUT+ALPHA */
	case VIDEO_GFX_PALETTIZE_METHOD_AUTO | VIDEO_GFX_PALETTIZE_METHOD_F_ALPHA:
	case VIDEO_GFX_PALETTIZE_METHOD_MEDIAN_CUT | VIDEO_GFX_PALETTIZE_METHOD_F_ALPHA:
		return median_cut_palettize(self, palsize, pal, 0);

	case VIDEO_GFX_PALETTIZE_METHOD_K_MEANS:
		return k_means_palettize(self, palsize, pal, VIDEO_COLOR_ALPHA_MASK);

	case VIDEO_GFX_PALETTIZE_METHOD_K_MEANS | VIDEO_GFX_PALETTIZE_METHOD_F_ALPHA:
		return k_means_palettize(self, palsize, pal, 0);

	default: break;
	}

	/* Unsupported palettization method. */
	errno = EINVAL;
	return -1;
empty_io:
	bzero(pal, palsize, sizeof(*pal));
empty_pal:
	return 0;
}

DEFINE_PUBLIC_ALIAS(video_gfx_palettize, libvideo_gfx_palettize);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_PALETTIZE_C */
