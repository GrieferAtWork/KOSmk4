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
#ifndef _LIBVIDEO_GFX_POLYGON_H
#define _LIBVIDEO_GFX_POLYGON_H 1

#include "api.h"
/**/

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <kos/refcnt.h>

#include "../line.h"
#include "../types.h"
#ifdef LIBVIDEO_GFX_EXPOSE_INTERNALS
#include "../cline.h"
#endif /* LIBVIDEO_GFX_EXPOSE_INTERNALS */

#ifdef __CC__
__DECL_BEGIN

struct video_point;
struct video_cpoint;
struct video_line;
struct video_cline;
struct video_polygon;

struct video_polygon_ops {
	/* Called when `vp_refcnt' reaches 0 */
	__ATTR_NONNULL_T((1)) void
	(LIBVIDEO_GFX_CC *vpo_destroy)(struct video_polygon *__restrict __self);
};

struct video_polygon_edge {
	struct video_line vpe_edge; /* Line describing this edge ("vl_p1" is non-inclusive) */
	video_offset_t    vpe_dir;  /* "-1" if points in "vpe_edge" were swapped, else "1" */
};

struct video_polygon {
	__UINTPTR_TYPE__                vp_refcnt;  /* Reference counter */
	struct video_polygon_ops const *vp_ops;     /* [1..1][const] Operator table of this polygon */
	struct video_domain const      *vp_domain;  /* [1..1][const] Domain linked to this polygon */
	video_offset_t                  vp_xmin;    /* [const] Lowest "vp_edges[i].vpe_edge.vl_p{0|1}.vp_x" */
	video_offset_t                  vp_ymin;    /* [const] Lowest "vp_edges[i].vpe_edge.vl_p{0|1}.vp_y" */
	video_offset_t                  vp_xend;    /* [const] Greatest "vp_edges[i].vpe_edge.vl_p{0|1}.vp_x + 1" */
	video_offset_t                  vp_yend;    /* [const] Greatest "vp_edges[i].vpe_edge.vl_p{0|1}.vp_y + 1" */
	__SIZE_TYPE__                   vp_nactive; /* [>= 2 && <= vp_nedges][const] Max # of edges that can be active at the same time */
	__SIZE_TYPE__                   vp_nedges;  /* [>= 2][const] # of edges in this polygon */
	__COMPILER_FLEXIBLE_ARRAY(struct video_polygon_edge,
	                                vp_edges);  /* [1..vp_npoints][const] Polygon edges (sorted by [vl_p0.vp_y ASC, vl_p0.vp_x ASC];
	                                             * because  "video_line" is also sorted, this means  this array sorts edges by their
	                                             * starting Y coords). Horizontal edges are excluded from here! */
};

#define video_polygon_destroy(self) (*(self)->vp_ops->vpo_destroy)(self)
#define video_polygon_incref(self) \
	__hybrid_atomic_inc(&(self)->vp_refcnt, __ATOMIC_SEQ_CST)
#define video_polygon_decref(self)                                           \
	(void)(__hybrid_atomic_decfetch(&(self)->vp_refcnt, __ATOMIC_SEQ_CST) || \
	       (video_polygon_destroy(self), 0))
#define video_polygon_xincref(self) (void)(!(self) || (video_polygon_incref(self), 0))
#define video_polygon_xdecref(self) (void)(!(self) || (video_polygon_decref(self), 0))
__DEFINE_REFCNT_FUNCTIONS(struct video_polygon, vp_refcnt, video_polygon_destroy)



#ifdef LIBVIDEO_GFX_EXPOSE_INTERNALS
struct video_polygon_data {
	video_offset_t            vpd_xmin;    /* [const] Lowest "vpd_edges[i].vpe_edge.vcl_p{0|1}.vcp_x" */
	video_offset_t            vpd_ymin;    /* [const] Lowest "vpd_edges[i].vpe_edge.vcl_p{0|1}.vcp_y" */
	video_offset_t            vpd_xend;    /* [const] Greatest "vpd_edges[i].vpe_edge.vcl_p{0|1}.vcp_x + 1" */
	video_offset_t            vpd_yend;    /* [const] Greatest "vpd_edges[i].vpe_edge.vcl_p{0|1}.vcp_y + 1" */
	__SIZE_TYPE__             vpd_nactive; /* [>= 2 && <= vpd_nedges][const] Max # of edges that can be active at the same time */
	__SIZE_TYPE__             vpd_nedges;  /* [>= 3][const] # of edges in this polygon */
	__COMPILER_FLEXIBLE_ARRAY(struct video_polygon_edge,
	                          vpd_edges); /* [1..vcp_npoints][const] Polygon edges (sorted by [vl_p0.vcp_y ASC, vl_p0.vcp_x ASC];
	                                       * because "video_line" is  also sorted,  this means this  array sorts  edges by  their
	                                       * starting Y coords). Horizontal edges are excluded from here! */
};

#define __video_polygon_data_start vp_xmin
#define video_polygon_asdata(self) ((struct video_polygon_data *)&(self)->__video_polygon_data_start)
#endif /* LIBVIDEO_GFX_EXPOSE_INTERNALS */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_POLYGON_H */
