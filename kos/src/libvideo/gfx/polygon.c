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

#include <kos/anno.h>

#include <alloca.h>
#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <malloc.h>
#include <stddef.h>
#include <stdlib.h>

#include <libvideo/gfx/polygon.h>
#include <libvideo/point.h>
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
	if (video_line_getp0y(&a->vpe_edge) < video_line_getp0y(&b->vpe_edge))
		return -1;
	if (video_line_getp0y(&a->vpe_edge) > video_line_getp0y(&b->vpe_edge))
		return 1;
	if (video_line_getp0x(&a->vpe_edge) < video_line_getp0x(&b->vpe_edge))
		return -1;
	if (video_line_getp0x(&a->vpe_edge) > video_line_getp0x(&b->vpe_edge))
		return 1;
	return 0;
}

/* Generic polygon object creator (used by ramdomain) */
INTERN WUNUSED NONNULL((1)) ATTR_INS(2, 3) REF struct video_polygon *CC
libvideo_generic_polygon_create(struct video_domain const *__restrict self,
                                struct video_point const *points, size_t npoints) {
	REF struct video_polygon *result;
	size_t i, nedges, sizeof_polygon;
	video_offset_t poly_xend, poly_yend;
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
		if (result->vp_ymin > video_line_getp0y(&edge->vpe_edge))
			result->vp_ymin = video_line_getp0y(&edge->vpe_edge);
		if (poly_yend < video_line_getp1y(&edge->vpe_edge))
			poly_yend = video_line_getp1y(&edge->vpe_edge);
		if (result->vp_xmin > video_line_getp0x(&edge->vpe_edge))
			result->vp_xmin = video_line_getp0x(&edge->vpe_edge);
		if (poly_xend < video_line_getp0x(&edge->vpe_edge))
			poly_xend = video_line_getp0x(&edge->vpe_edge);
		if (result->vp_xmin > video_line_getp1x(&edge->vpe_edge))
			result->vp_xmin = video_line_getp1x(&edge->vpe_edge);
		if (poly_xend < video_line_getp1x(&edge->vpe_edge))
			poly_xend = video_line_getp1x(&edge->vpe_edge);
		++nedges;
	}
	result->vp_xdim = (video_dim_t)(poly_xend - result->vp_xmin);
	result->vp_ydim = (video_dim_t)(poly_yend - result->vp_ymin);

	/* Assert that there are at least 2 edges */
	if unlikely(nedges < 2) {
		errno = EINVAL;
		goto err_r;
	}

	/* Sort edges by [P1.Y ASC, P1.X ASC] */
	qsort(result->vp_edges, nedges,
	      sizeof(struct video_polygon_edge),
	      &polygon_edge_compare);

	/* Fill in remaining fields. */
	result->vp_refcnt = 1;
	result->vp_ops    = _generic_polygon_ops();
	result->vp_domain = self;
	result->vp_nedges = nedges;

	/* Figure out the proper value for "vpd_nactive" */
	{
		bitset_t *active = (bitset_t *)alloca(BITSET_SIZEOF(nedges));
		bitset_clearall(active, nedges);
		result->vp_nactive = 2;
		i = 0;
		do {
			size_t active_edge, n_active;
			video_offset_t scanline_y;
			scanline_y = video_line_getp0y(&result->vp_edges[i].vpe_edge);

			/* Remove edges that are no longer active at "y" */
			bitset_foreach (active_edge, active, nedges) {
				video_offset_t active_end;
				active_end = video_line_getp1y(&result->vp_edges[active_edge].vpe_edge);
				if (scanline_y >= active_end)
					bitset_clear(active, active_edge);
			}

			/* Add new active edge */
			do {
				bitset_set(active, i);
				++i;
			} while (i < nedges && scanline_y == video_line_getp0y(&result->vp_edges[i].vpe_edge));

			/* Check if we reached a new upper bound of active edges */
			n_active = bitset_popcount(active, nedges);
			assertf(n_active >= 2, "Scanline at %" PRIdOFF " has less than 2 active edges (%" PRIuSIZ ")",
			        scanline_y, n_active);
			if (result->vp_nactive < n_active)
				result->vp_nactive = n_active;
		} while (i < nedges);
	}

	return result;
err_r:
	free(result);
err:
	return NULL;
}


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_POLYGON_C */
