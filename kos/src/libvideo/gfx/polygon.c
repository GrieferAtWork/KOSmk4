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
#ifndef GUARD_LIBVIDEO_GFX_POLYGON_C
#define GUARD_LIBVIDEO_GFX_POLYGON_C 1
#define __VIDEO_POLYGON_const
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/bitset.h>
#include <hybrid/sequence/bsearch.h>

#include <kos/anno.h>

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <malloc.h>
#include <malloca.h>
#include <minmax.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <libvideo/gfx/polygon.h>
#include <libvideo/point.h>
#include <libvideo/rect.h>
#include <libvideo/types.h>

#include "gfx-debug.h"
#include "polygon.h"

DECL_BEGIN

/* Assert that "video_polygon_asdata()" works */
#define OFFSETOF_CPOLY_START offsetof(struct video_polygon, __video_polygon_data_start)
static_assert(offsetof(struct video_polygon_data, vpd_xmin) == (offsetof(struct video_polygon, vp_xmin) - OFFSETOF_CPOLY_START));
static_assert(offsetof(struct video_polygon_data, vpd_xdim) == (offsetof(struct video_polygon, vp_xdim) - OFFSETOF_CPOLY_START));
static_assert(offsetof(struct video_polygon_data, vpd_ymin) == (offsetof(struct video_polygon, vp_ymin) - OFFSETOF_CPOLY_START));
static_assert(offsetof(struct video_polygon_data, vpd_ydim) == (offsetof(struct video_polygon, vp_ydim) - OFFSETOF_CPOLY_START));
static_assert(offsetof(struct video_polygon_data, vpd_nactive) == (offsetof(struct video_polygon, vp_nactive) - OFFSETOF_CPOLY_START));
static_assert(offsetof(struct video_polygon_data, vpd_nedges) == (offsetof(struct video_polygon, vp_nedges) - OFFSETOF_CPOLY_START));
static_assert(offsetof(struct video_polygon_data, vpd_edges) == (offsetof(struct video_polygon, vp_edges) - OFFSETOF_CPOLY_START));
static_assert(offsetof(struct video_polygon_data, vpd_edges[0]) == (offsetof(struct video_polygon, vp_edges[0]) - OFFSETOF_CPOLY_START));
static_assert(offsetof(struct video_polygon_data, vpd_edges[0].vpe_edge) == (offsetof(struct video_polygon, vp_edges[0].vpe_edge) - OFFSETOF_CPOLY_START));
static_assert(offsetof(struct video_polygon_data, vpd_edges[0].vpe_dir) == (offsetof(struct video_polygon, vp_edges[0].vpe_dir) - OFFSETOF_CPOLY_START));
static_assert(offsetof(struct video_polygon_data, vpd_edges[1].vpe_edge) == (offsetof(struct video_polygon, vp_edges[1].vpe_edge) - OFFSETOF_CPOLY_START));
static_assert(offsetof(struct video_polygon_data, vpd_edges[1].vpe_dir) == (offsetof(struct video_polygon, vp_edges[1].vpe_dir) - OFFSETOF_CPOLY_START));




PRIVATE NONNULL((1)) void CC
generic_polygon_destroy(struct video_polygon *__restrict self) {
	free(self);
}

PRIVATE struct video_polygon_ops generic_polygon_ops = {};
PRIVATE ATTR_RETNONNULL WUNUSED
struct video_polygon_ops const *CC _generic_polygon_ops(void) {
	if (!generic_polygon_ops.vpo_destroy) {
		COMPILER_WRITE_BARRIER();
		generic_polygon_ops.vpo_destroy = &generic_polygon_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &generic_polygon_ops;
}

PRIVATE WUNUSED int __LIBCCALL
polygon_edge_compare(void const *_a, void const *_b) {
	struct video_polygon_edge const *a = (struct video_polygon_edge const *)_a;
	struct video_polygon_edge const *b = (struct video_polygon_edge const *)_b;
	if (video_polygon_edge_getp0y(a) < video_polygon_edge_getp0y(b))
		return -1;
	if (video_polygon_edge_getp0y(a) > video_polygon_edge_getp0y(b))
		return 1;
	if (video_polygon_edge_getp0x(a) < video_polygon_edge_getp0x(b))
		return -1;
	if (video_polygon_edge_getp0x(a) > video_polygon_edge_getp0x(b))
		return 1;
	return 0;
}

PRIVATE WUNUSED int __LIBCCALL
polygon_edge_compare_by_x(void const *_a, void const *_b) {
	struct video_polygon_edge const *a = (struct video_polygon_edge const *)_a;
	struct video_polygon_edge const *b = (struct video_polygon_edge const *)_b;
	video_offset_t a_min_x = min(video_polygon_edge_getp0x(a), video_polygon_edge_getp1x(a));
	video_offset_t b_min_x = min(video_polygon_edge_getp0x(b), video_polygon_edge_getp1x(b));
	if (a_min_x < b_min_x)
		return -1;
	if (a_min_x > b_min_x)
		return 1;
	if (video_polygon_edge_getp0y(a) < video_polygon_edge_getp0y(b))
		return -1;
	if (video_polygon_edge_getp0y(a) > video_polygon_edge_getp0y(b))
		return 1;
	return 0;
}

/* Generic polygon object creator (used by ramdomain) */
INTERN WUNUSED NONNULL((1)) ATTR_INS(2, 3) REF struct video_polygon *CC
libvideo_generic_polygon_create(struct video_domain const *__restrict self,
                                struct video_point const *points, size_t npoints) {
	REF struct video_polygon *result;
	size_t i, nedges, sizeof_polygon;
	size_t poly_xactive;
	video_offset_t poly_xend, poly_yend;
	bitset_t *active;
	sizeof_polygon = offsetof(struct video_polygon, vp_edges) +
	                 (npoints * sizeof(struct video_polygon_edge));
	result = (REF struct video_polygon *)malloc(sizeof_polygon);
	if unlikely(!result)
		goto err;
	result->vp_xmin = VIDEO_OFFSET_MAX;
	result->vp_ymin = VIDEO_OFFSET_MAX;
	poly_xend = VIDEO_OFFSET_MIN;
	poly_yend = VIDEO_OFFSET_MIN;
	for (nedges = i = 0; i < npoints; ++i) {
		struct video_polygon_edge *edge;
		struct video_point const *from = &points[i];
		struct video_point const *to = &points[(i >= (npoints - 1)) ? 0 : (i + 1)];
		if (video_point_gety(from) == video_point_gety(to))
			continue; /* Skip horizontal edges */
		if (video_point_getx(from) == video_point_getx(to)) {
			/* TODO: Optimize adjacent edges that form a continuous line into a single edge */
		}
		edge = &result->vp_edges[nedges];
		if (video_point_gety(from) < video_point_gety(to)) {
			edge->vpe_dir = 1;
			edge->vpe_edge.vl_p0 = *from;
			edge->vpe_edge.vl_p1 = *to;
		} else {
			edge->vpe_dir = -1;
			edge->vpe_edge.vl_p0 = *to;
			edge->vpe_edge.vl_p1 = *from;
		}

		/* Keep track of the min/max bounds of the polygon */
		if (result->vp_ymin > video_polygon_edge_getp0y(edge))
			result->vp_ymin = video_polygon_edge_getp0y(edge);
		if (poly_yend < video_polygon_edge_getp1y(edge))
			poly_yend = video_polygon_edge_getp1y(edge);
		if (result->vp_xmin > video_polygon_edge_getp0x(edge))
			result->vp_xmin = video_polygon_edge_getp0x(edge);
		if (poly_xend < video_polygon_edge_getp0x(edge))
			poly_xend = video_polygon_edge_getp0x(edge);
		if (result->vp_xmin > video_polygon_edge_getp1x(edge))
			result->vp_xmin = video_polygon_edge_getp1x(edge);
		if (poly_xend < video_polygon_edge_getp1x(edge))
			poly_xend = video_polygon_edge_getp1x(edge);
		++nedges;
	}
	result->vp_xdim = (video_dim_t)(poly_xend - result->vp_xmin);
	result->vp_ydim = (video_dim_t)(poly_yend - result->vp_ymin);

	/* Assert that there are at least 2 edges */
	if unlikely(nedges < 2) {
		errno = EINVAL;
		goto err_r;
	}

	active = (bitset_t *)malloca(BITSET_SIZEOF(nedges));
	if unlikely(!active)
		goto err_r;

	/* Sort edges by [MIN(P0.X, P1.X) ASC, P0.Y ASC] */
	qsort(result->vp_edges, nedges,
	      sizeof(struct video_polygon_edge),
	      &polygon_edge_compare_by_x);

	/* Figure out the max # of edges ever active when casting vertical scanlines.
	 * This value is needed to calculate how many total edges are needed in order
	 * to create a sub-clip-polygon from this one. */
	bitset_clearall(active, nedges);
	poly_xactive = 2;
	i = 0;
	do {
		size_t active_edge, n_active;
		video_offset_t scanline_x;
		scanline_x = min(video_polygon_edge_getp0x(&result->vp_edges[i]),
		                 video_polygon_edge_getp1x(&result->vp_edges[i]));

		/* Remove edges that are no longer active at "x" */
		bitset_foreach (active_edge, active, nedges) {
			video_offset_t active_end;
			active_end = max(video_polygon_edge_getp0x(&result->vp_edges[active_edge]),
			                 video_polygon_edge_getp1x(&result->vp_edges[active_edge]));
			if (scanline_x >= active_end)
				bitset_clear(active, active_edge);
		}

		/* Add new active edge */
		do {
			if (scanline_x != max(video_polygon_edge_getp0x(&result->vp_edges[i]),
			                      video_polygon_edge_getp1x(&result->vp_edges[i])))
				bitset_set(active, i);
			++i;
		} while (i < nedges && scanline_x == min(video_polygon_edge_getp0x(&result->vp_edges[i]),
		                                         video_polygon_edge_getp1x(&result->vp_edges[i])));

		/* Check if we reached a new upper bound of active edges */
		n_active = bitset_popcount(active, nedges);
		if (poly_xactive < n_active)
			poly_xactive = n_active;
	} while (i < nedges);

	/* Sort edges by [P0.Y ASC, P0.X ASC] */
	qsort(result->vp_edges, nedges,
	      sizeof(struct video_polygon_edge),
	      &polygon_edge_compare);

	/* Figure out the proper value for "vp_nactive" */
	bitset_clearall(active, nedges);
	result->vp_nactive = 2;
	i = 0;
	do {
		size_t active_edge, n_active;
		video_offset_t scanline_y;
		scanline_y = video_polygon_edge_getp0y(&result->vp_edges[i]);

		/* Remove edges that are no longer active at "y" */
		bitset_foreach (active_edge, active, nedges) {
			video_offset_t active_end;
			active_end = video_polygon_edge_getp1y(&result->vp_edges[active_edge]);
			if (scanline_y >= active_end)
				bitset_clear(active, active_edge);
		}

		/* Add new active edge */
		do {
			bitset_set(active, i);
			++i;
		} while (i < nedges && scanline_y == video_polygon_edge_getp0y(&result->vp_edges[i]));

		/* Check if we reached a new upper bound of active edges */
		n_active = bitset_popcount(active, nedges);
		assertf(n_active >= 2, "Scanline at %" PRIdOFF " has less than 2 active edges (%" PRIuSIZ ")",
		        scanline_y, n_active);
		if (result->vp_nactive < n_active)
			result->vp_nactive = n_active;
	} while (i < nedges);

	/* Fill in remaining fields. */
	result->vp_refcnt = 1;
	result->vp_ops    = _generic_polygon_ops();
	result->vp_domain = self;
	result->vp_nedges = nedges;

	/* To create a new polygon from an arbitrary sub-rect, we need:
	 * - Possibly all edges from the original polygon (in case none end up out-of-bounds)
	 * - 2 times "poly_xactive / 2" edges (one for left, one for right) to represent
	 *   additional vertical edges at the left/right for spikes that may have gotten
	 *   their tips cut off.
	 *
	 * Worst case:
	 * >> \--\
	 * >>  \  \--\
	 * >>   \     \--\
	 * >>    \  +---------------------+
	 * >>     \ |         \--\        |
	 * >>      \|             \--\    |
	 * >>       |                 \--\|
	 * >>       |\                    |--\
	 * >>       | \                   |   \--\
	 * >>       +---------------------+       \--\
	 * >>           \                             \--\
	 * >>            \--------------------------------\
	 *
	 *
	 * Clip result:
	 * >>       +---------
	 * >>       |         \--\
	 * >>       |             \--\
	 * >>       |                 \--\
	 * >>        \                    |
	 * >>         \                   |
	 * >>          -------------------+
	 *
	 * After disregarding horizontal edges  (here: 2), the above  polygon
	 * still  only has 4 edges, which is the  result of the # of edges of
	 * the original polygon (2), plus the max. # of edges in any vertical
	 * scanline (which is also 2).
	 */
	result->vp_cedges = nedges + poly_xactive;
	freea(active);
	return result;
err_r:
	free(result);
err:
	return NULL;
}


/* Add a new edge to "self". Caller must ensure that Y coord of "edge" are sorted */
PRIVATE NONNULL((1, 2)) void CC
video_polygon_data_addedge(struct video_polygon_data *__restrict self,
                           struct video_polygon_edge const *__restrict edge) {
	assert(video_polygon_edge_getp0y(edge) <= video_polygon_edge_getp1y(edge));
	if unlikely(video_polygon_edge_getp0y(edge) == video_polygon_edge_getp1y(edge))
		return; /* Skip horizontal edges */
	if (video_polygon_edge_getp0x(edge) == video_polygon_edge_getp1x(edge)) {
		size_t i;
		/* Check if the previous edge that  this one form a vertical  line
		 * that touches our's. For this purpose, all continuous-line edges
		 * are kept near the head of the edge-array. */
		for (i = 0; i < self->vpd_nedges; ++i) {
			struct video_polygon_edge *prev = &self->vpd_edges[i];
			if (video_polygon_edge_getp0x(prev) != video_polygon_edge_getp1x(prev))
				break;
			if (video_polygon_edge_getp0x(prev) != video_polygon_edge_getp0x(edge))
				continue; /* Some other vertical bar (but not at our X coord) */

			/* Both  edges are at the same X  coord. Now check if they can
			 * actually be continuous: When  their direction is the  same,
			 * then extension is possible, when they differ, then previous
			 * edge may be truncated. */
			if (prev->vpe_dir == edge->vpe_dir) {
				/* Try to extend previous edge */
				if (video_polygon_edge_getp0y(prev) == video_polygon_edge_getp1y(edge)) {
					/* Extend upwards */
					video_polygon_edge_setp0y(prev, video_polygon_edge_getp0y(edge));
					assert(video_polygon_edge_getp0y(prev) < video_polygon_edge_getp1y(prev));
					return;
				} else if (video_polygon_edge_getp1y(prev) == video_polygon_edge_getp0y(edge)) {
					/* Extend downwards */
					video_polygon_edge_setp1y(prev, video_polygon_edge_getp1y(edge));
					assert(video_polygon_edge_getp0y(prev) < video_polygon_edge_getp1y(prev));
					return;
				}
			} else {
				assert((prev->vpe_dir + edge->vpe_dir) == 0);
				/* Try to truncate previous edge */
				if (video_polygon_edge_getp0y(prev) == video_polygon_edge_getp0y(edge)) {
					/* Truncate top */
					video_polygon_edge_setp0y(prev, video_polygon_edge_getp1y(edge));
remove_empty_prev_and_done:
					if (video_polygon_edge_getp0y(prev) > video_polygon_edge_getp1y(prev)) {
						/* Flip direction of edge */
						struct video_point temp = prev->vpe_edge.vl_p0;
						prev->vpe_edge.vl_p0 = prev->vpe_edge.vl_p1;
						prev->vpe_edge.vl_p1 = temp;
						prev->vpe_dir = -prev->vpe_dir;
					} else if unlikely(video_polygon_edge_getp0y(prev) == video_polygon_edge_getp1y(prev)) {
						/* Remove vertical bar if it became empty. */
						--self->vpd_nedges;
						memmovedown(prev, prev + 1,
						            self->vpd_nedges - i,
						            sizeof(*prev));
					}
					return;
				} else if (video_polygon_edge_getp1y(prev) == video_polygon_edge_getp1y(edge)) {
					/* Truncate bottom */
					video_polygon_edge_setp1y(prev, video_polygon_edge_getp0y(edge));
					goto remove_empty_prev_and_done;
				}
			}
		}
		memmoveup(&self->vpd_edges[i + 1],
		          &self->vpd_edges[i],
		          self->vpd_nedges - i,
		          sizeof(*self->vpd_edges));
		self->vpd_edges[i] = *edge;
		++self->vpd_nedges;
		return;
	}

	/* Add additional edge as-is */
	self->vpd_edges[self->vpd_nedges++] = *edge;
}


/* Calculate a new sub-polygon by clipping edges to the given `rect'.
 * @param: result: New polygon data with storage for at least `POLY_OF(self)->vp_cedges' edges.
 * @param: rect:   The clip rect to apply, with coords relative to those used by `self'
 * @return: * : Always re-returns `result' */
DEFINE_PUBLIC_ALIAS(video_polygon_data_clip, libvideo_polygon_data_clip);
INTERN ATTR_RETNONNULL ATTR_IN(1) ATTR_OUT(2) ATTR_IN(3) struct video_polygon_data *CC
libvideo_polygon_data_clip(struct video_polygon_data const *__restrict self,
                           struct video_polygon_data *__restrict result,
                           struct video_rect const *__restrict rect) {
	size_t i;
	video_offset_t result_xend, result_yend;
	result->vpd_xmin = max(self->vpd_xmin, video_rect_getxmin(rect));
	result->vpd_ymin = max(self->vpd_ymin, video_rect_getymin(rect));
	result_xend = min(self->vpd_xmin + self->vpd_xdim, video_rect_getxend(rect));
	result_yend = min(self->vpd_ymin + self->vpd_ydim, video_rect_getyend(rect));
	result->vpd_xdim = result_xend - result->vpd_xmin;
	result->vpd_ydim = result_yend - result->vpd_ymin;
	result->vpd_nactive = self->vpd_nactive;
	result->vpd_nedges = 0;

	for (i = 0; i < self->vpd_nedges; ++i) {
		struct video_polygon_edge edge = self->vpd_edges[i];
		if (video_polygon_edge_getp1y(&edge) <= video_rect_getymin(rect))
			continue; /* Skip edge that lies above clip rect */
		if (video_polygon_edge_getp0y(&edge) >= video_rect_getyend(rect))
			continue; /* Skip edge that lies below clip rect */
		if (video_polygon_edge_getp0y(&edge) < video_rect_getymin(rect)) {
			/* Clamp P0 against top clip rect border (no need to create extra edges here) */
			video_polygon_edge_setp0x(&edge, video_polygon_edge_getxat(&edge, video_rect_getymin(rect)));
			video_polygon_edge_setp0y(&edge, video_rect_getymin(rect));
		}
		if (video_polygon_edge_getp1y(&edge) > video_rect_getyend(rect)) {
			/* Clamp P1 against bottom clip rect border (no need to create extra edges here) */
			video_polygon_edge_setp1x(&edge, video_polygon_edge_getxat(&edge, video_rect_getyend(rect)));
			video_polygon_edge_setp1y(&edge, video_rect_getyend(rect));
		}

		/* Clamp left side (and possibly generate an extra vertical edge) */
		if (video_polygon_edge_getp0x(&edge) < video_rect_getxmin(rect)) {
			if (video_polygon_edge_getp1x(&edge) < video_rect_getxmin(rect)) {
				/* >> P0       | CLIP
				 * >>   \      |
				 * >>    \     |
				 * >>     \    |
				 * >>      P1  | */
				video_polygon_edge_setp0x(&edge, video_rect_getxmin(rect));
				video_polygon_edge_setp1x(&edge, video_rect_getxmin(rect));
			} else {
				/* >> P0 | CLIP
				 * >>   \|
				 * >>    |
				 * >>    |\
				 * >>    | P1 */
				video_dim_t ydim = (video_dim_t)(video_polygon_edge_getp1y(&edge) -
				                                 video_polygon_edge_getp0y(&edge));
				video_dim_t xdim = (video_dim_t)(video_polygon_edge_getp1x(&edge) -
				                                 video_polygon_edge_getp0x(&edge));
				video_dim_t xoff = (video_dim_t)(video_rect_getxmin(rect) -
				                                 video_polygon_edge_getp0x(&edge));
				video_coord_t yrel = (video_coord_t)(((__UINT_FAST64_TYPE__)xoff * ydim) / xdim);
				video_offset_t yhit = video_polygon_edge_getp0y(&edge) + yrel;
				struct video_polygon_edge vedge;
				vedge.vpe_dir = edge.vpe_dir;
				video_polygon_edge_setp0x(&vedge, video_rect_getxmin(rect));
				video_polygon_edge_setp0y(&vedge, video_polygon_edge_getp0y(&edge));
				video_polygon_edge_setp1x(&vedge, video_rect_getxmin(rect));
				video_polygon_edge_setp1y(&vedge, yhit);
				video_polygon_data_addedge(result, &vedge);
				video_polygon_edge_setp0x(&edge, video_rect_getxmin(rect));
				video_polygon_edge_setp0y(&edge, yhit);
			}
		} else if (video_polygon_edge_getp1x(&edge) < video_rect_getxmin(rect)) {
			/* >>    | P0
			 * >>    |/
			 * >>    |
			 * >>   /|
			 * >> P1 | CLIP */
			video_dim_t ydim = (video_dim_t)(video_polygon_edge_getp1y(&edge) -
			                                 video_polygon_edge_getp0y(&edge));
			video_dim_t xdim = (video_dim_t)(video_polygon_edge_getp0x(&edge) -
			                                 video_polygon_edge_getp1x(&edge));
			video_dim_t xoff = (video_dim_t)(video_rect_getxmin(rect) -
			                                 video_polygon_edge_getp1x(&edge));
			video_coord_t yrel = (video_coord_t)(((__UINT_FAST64_TYPE__)xoff * ydim) / xdim);
			video_offset_t yhit = video_polygon_edge_getp1y(&edge) - yrel;
			struct video_polygon_edge vedge;
			vedge.vpe_dir = edge.vpe_dir;
			video_polygon_edge_setp0x(&vedge, video_rect_getxmin(rect));
			video_polygon_edge_setp0y(&vedge, yhit);
			video_polygon_edge_setp1x(&vedge, video_rect_getxmin(rect));
			video_polygon_edge_setp1y(&vedge, video_polygon_edge_getp1y(&edge));
			video_polygon_data_addedge(result, &vedge);
			video_polygon_edge_setp1x(&edge, video_rect_getxmin(rect));
			video_polygon_edge_setp1y(&edge, yhit);
		}

		/* Clamp right side (and possibly generate an extra vertical edge) */
		if (video_polygon_edge_getp0x(&edge) > video_rect_getxend(rect)) {
			if (video_polygon_edge_getp1x(&edge) > video_rect_getxend(rect)) {
				/* >>      |   P0
				 * >>      |     \
				 * >>      |      \
				 * >>      |       \
				 * >> CLIP |        P1 */
				video_polygon_edge_setp0x(&edge, video_rect_getxend(rect));
				video_polygon_edge_setp1x(&edge, video_rect_getxend(rect));
			} else {
				/* >> CLIP | P0
				 * >>      |/
				 * >>      |
				 * >>     /|
				 * >>   P1 | */
				video_dim_t ydim = (video_dim_t)(video_polygon_edge_getp1y(&edge) -
				                                 video_polygon_edge_getp0y(&edge));
				video_dim_t xdim = (video_dim_t)(video_polygon_edge_getp0x(&edge) -
				                                 video_polygon_edge_getp1x(&edge));
				video_dim_t xoff = (video_dim_t)(video_rect_getxend(rect) -
				                                 video_polygon_edge_getp1x(&edge));
				video_coord_t yrel = (video_coord_t)(((__UINT_FAST64_TYPE__)xoff * ydim) / xdim);
				video_offset_t yhit = video_polygon_edge_getp1y(&edge) - yrel;
				struct video_polygon_edge vedge;
				vedge.vpe_dir = edge.vpe_dir;
				video_polygon_edge_setp0x(&vedge, video_rect_getxend(rect));
				video_polygon_edge_setp0y(&vedge, video_polygon_edge_getp0y(&edge));
				video_polygon_edge_setp1x(&vedge, video_rect_getxend(rect));
				video_polygon_edge_setp1y(&vedge, yhit);
				video_polygon_data_addedge(result, &vedge);
				video_polygon_edge_setp0x(&edge, video_rect_getxend(rect));
				video_polygon_edge_setp0y(&edge, yhit);
			}
		} else if (video_polygon_edge_getp1x(&edge) > video_rect_getxend(rect)) {
			/* >>   P0 |
			 * >>     \|
			 * >>      |
			 * >>      |\
			 * >> CLIP | P1 */
			video_dim_t ydim = (video_dim_t)(video_polygon_edge_getp1y(&edge) -
			                                 video_polygon_edge_getp0y(&edge));
			video_dim_t xdim = (video_dim_t)(video_polygon_edge_getp1x(&edge) -
			                                 video_polygon_edge_getp0x(&edge));
			video_dim_t xoff = (video_dim_t)(video_rect_getxend(rect) -
			                                 video_polygon_edge_getp0x(&edge));
			video_coord_t yrel = (video_coord_t)(((__UINT_FAST64_TYPE__)xoff * ydim) / xdim);
			video_offset_t yhit = video_polygon_edge_getp0y(&edge) + yrel;
			struct video_polygon_edge vedge;
			vedge.vpe_dir = edge.vpe_dir;
			video_polygon_edge_setp0x(&vedge, video_rect_getxend(rect));
			video_polygon_edge_setp0y(&vedge, yhit);
			video_polygon_edge_setp1x(&vedge, video_rect_getxend(rect));
			video_polygon_edge_setp1y(&vedge, video_polygon_edge_getp1y(&edge));
			video_polygon_data_addedge(result, &vedge);
			video_polygon_edge_setp1x(&edge, video_rect_getxend(rect));
			video_polygon_edge_setp1y(&edge, yhit);
		}

		/* Add edge to result */
		video_polygon_data_addedge(result, &edge);
	}

	/* Sort edges by [P0.Y ASC, P0.X ASC] */
	qsort(result->vpd_edges, result->vpd_nedges,
	      sizeof(struct video_polygon_edge),
	      &polygon_edge_compare);
	return result;
}


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_POLYGON_C */
