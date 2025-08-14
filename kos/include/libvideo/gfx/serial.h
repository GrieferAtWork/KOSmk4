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
#ifndef _LIBVIDEO_GFX_SERIAL_H
#define _LIBVIDEO_GFX_SERIAL_H 1

#include "api.h"
/**/

/************************************************************************/
/* LOW-LEVEL, CLIENT-SIDE VIDEO SERIALIZATION                           */
/************************************************************************/

#ifdef CONFIG_LIBVIDEO_HAVE_SERIALIZATION
#include <__stdinc.h>

#include <bits/types.h>
#include <kos/anno.h>

#include "../types.h"


/************************************************************************/
/* POSSIBLE VALUES FOR `video_serial_proto_t'                           */
/************************************************************************/
/* Serialization types supported by all video buffers */
#define VIDEO_SERIAL_PROTO_PACKET 0x1000 /* Packet-only serialization: no "fd" is shared, and GFX/video-lock commands are sent via */
/* Serialization types only supported by specific video buffers */
#define VIDEO_SERIAL_PROTO_MEMFD  0x1001 /* Same as `VIDEO_SERIAL_PROTO_PACKET', but an mmap-able "fd" may be shared that can be mmap'd to directly access pixels */
/************************************************************************/

#ifdef __CC__
__DECL_BEGIN

/* Video serialization token (for syncing responses by the server) */
typedef __uint32_t video_serial_token_t;
#define VIDEO_SERIAL_TOKEN_OOB     ((video_serial_token_t)-1) /* Token sent by the server for packets that aren't answers */
#define VIDEO_SERIAL_TOKEN_INVALID ((video_serial_token_t)-1) /* Invalid token value that must not be passed to `vdrio_writepacket' */
#define VIDEO_SERIAL_TOKEN_MIN     ((video_serial_token_t)0)  /* First valid general-purpose token */
#define VIDEO_SERIAL_TOKEN_MAX     ((video_serial_token_t)-2) /* Last valid general-purpose token */

/* Video buffer file descriptor info for implementing `VIDEO_SERIAL_PROTO_MEMFD' */
struct video_buffer_fdinfo {
	/* Pixel data for a pixel at <X> and <Y> is accessed like this:
	 * >> video_offset_t x = <X> + vbfdi_cxoff;
	 * >> video_offset_t y = <Y> + vbfdi_cyoff;
	 * >> if (x < 0 || x >= vbfdi_xdim || y < 0 || y >= vbfdi_ydim)
	 * >>     return OUT_OF_BOUNDS;
	 * >> byte_t *base = mmap(NULL, vbfdi_total, MAP_FILE | MAP_SHARED, vbfdi_fd, vbfdi_bxoff);
	 * >> byte_t *line = base + (y * vbfdi_stride);
	 * >> video_pixel_t pixel = (*video_buffer_getcodec(:buffer)->vc_getpixel)(line, vbfdi_bxrem + x);
	 */
	__size_t       vbfdi_total;   /* Total # of bytes that should be mapped, starting *AFTER* `vbfdi_bxoff' */
	__size_t       vbfdi_stride;  /* Scanline stride (in bytes) */
	__size_t       vbfdi_bxoff;   /* Remaining byte-offset before pixel data starts in `vbfdi_fd' */
	video_coord_t  vbfdi_bxrem;   /* Remaining pixel-offset before pixel data starts in `vbfdi_fd' (after `vbfdi_bxoff') */
	__fd_t         vbfdi_fd;      /* File descriptor for sharing via `VIDEO_SERIAL_PROTO_MEMFD' */
	__uint32_t     vbfdi_hwops;   /* Set of `TODO' describing GFX operations that should be performed via
	                               * `VIDEO_SERIAL_PROTO_PACKET' (rather than `vbfdi_fd' and  client-side
	                               * SW-rendering) */
	video_dim_t    vbfdi_xdim;    /* X-dimension  of actual pixel data (same as `video_buffer_getxdim(*)',
	                               * except for `struct region_buffer', where it is the X-dimension of the
	                               * wrapped video buffer)
	                               * When  less than `video_buffer_getxdim(*)',  pixels beyond this dimension
	                               * are considered as out-of-bounds (use `struct region_buffer' to represent
	                               * video buffers using this sort of encoding) */
	video_dim_t    vbfdi_ydim;    /* Like `vbfdi_xdim', but for Y */
	video_offset_t vbfdi_cxoff;   /* [<= 0] Starting X offset of Clip Rect (when negative, the first `-vbfdi_cxoff' pixels are out-of-bounds) */
	video_offset_t vbfdi_cyoff;   /* [<= 0] Starting Y offset of Clip Rect (when negative, the first `-vbfdi_cyoff' pixels are out-of-bounds) */
};


struct video_deserializer_io {
	/* [1..1] Called by the associated video_buffer when it is destroyed */
	__ATTR_NONNULL_T((1))
	void (LIBVIDEO_GFX_CC *vdrio_destroy)(struct video_deserializer_io *__restrict self);
	/* [1..1] Read the next pending packet of data from the serial connection's server end.
	 * @param: __p_fd:  When non-NULL, optionally store a  file descriptor attached to the  packet
	 *                  here. If there is no file descriptor, just leave this parameter untouched,
	 *                  as  the caller will  pre-assign `-1' and check  after-wards if a different
	 *                  value has been written.
	 * @param: __token: Filter incoming (or already-received) packets  and only return ones  matching
	 *                  this token. When receiving responses to preceding packets sent by the client,
	 *                  use the same token as was passed to `vdrio_writepacket'. To receive  messages
	 *                  sent by the  server that  aren't responses to  client packets,  you may  pass
	 *                  `VIDEO_SERIAL_TOKEN_OOB' to this function.
	 * @return: * : The # of bytes read from the packet. You may assume that the passed "__num_bytes"
	 *              is  always large enough to hold every possible packet. But if there actually does
	 *              end up being a packet even larger, then this operator may do whatever it wants:
	 *              - The over-large packet may be discarded
	 *              - The over-large packet may be truncated
	 *              - The over-large packet may be ...
	 * @return: -1: I/O error -- failed to read packet (s.a. `errno') */
	__ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __ATTR_OUTS_T(2, 3)
	__ssize_t (LIBVIDEO_GFX_CC *vdrio_readpacket)(struct video_deserializer_io *__restrict self,
	                                              void *__buf, __size_t __num_bytes, __fd_t *__p_fd,
	                                              video_serial_token_t __token);
	/* [1..1] Send a packet to whomever is hosting the server.
	 * @param: __token: Request token (for filtering server-side responses).
	 *                  Every packet should have a different token that  any
	 *                  that came before, and used  tokens must be in  range
	 *                  [VIDEO_SERIAL_TOKEN_MIN,VIDEO_SERIAL_TOKEN_MAX]. To
	 *                  accomplish  this,  simply increment  a  counter that
	 *                  loops  around  once VIDEO_SERIAL_TOKEN_MAX  would be
	 *                  exceeded.
	 * @return: 0 : Success
	 * @return: -1: I/O error -- failed to send packet (s.a. `errno') */
	__ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __ATTR_INS_T(2, 3)
	int (LIBVIDEO_GFX_CC *vdrio_writepacket)(struct video_deserializer_io *__restrict self,
	                                         void const *__buf, __size_t __num_bytes,
	                                         video_serial_token_t __token);
};

#ifdef __INTELLISENSE__
/* Called by the associated video_buffer when it is destroyed */
extern void video_deserializer_io_destroy(struct video_deserializer_io *__restrict self);

/* Read the next pending packet of data from the serial connection's server end.
 * @param: __p_fd:  When non-NULL, optionally store a  file descriptor attached to the  packet
 *                  here. If there is no file descriptor, just leave this parameter untouched,
 *                  as  the caller will  pre-assign `-1' and check  after-wards if a different
 *                  value has been written.
 * @param: __token: Filter incoming (or already-received) packets  and only return ones  matching
 *                  this token. When receiving responses to preceding packets sent by the client,
 *                  use the  same token  as  was passed  to  `video_deserializer_io_writepacket'.
 *                  To  receive  messages sent  by  the server  that  aren't responses  to client
 *                  packets, you may pass `VIDEO_SERIAL_TOKEN_OOB' to this function.
 * @return: * : The # of bytes read from the packet. You may assume that the passed "__num_bytes"
 *              is  always large enough to hold every possible packet. But if there actually does
 *              end up being a packet even larger, then this operator may do whatever it wants:
 *              - The over-large packet may be discarded
 *              - The over-large packet may be truncated
 *              - The over-large packet may be ...
 * @return: -1: I/O error -- failed to read packet (s.a. `errno') */
extern __ATTR_WUNUSED_T __ATTR_NONNULL((1)) __ATTR_OUTS(2, 3) __ssize_t
video_deserializer_io_readpacket(struct video_deserializer_io *__restrict self,
                                 void *__buf, __size_t __num_bytes, __fd_t *__p_fd,
                                 video_serial_token_t __token);

/* Send a packet to whomever is hosting the server.
 * @param: __token: Request token (for filtering server-side responses).
 *                  Every packet should have a different token that  any
 *                  that came before, and used  tokens must be in  range
 *                  [VIDEO_SERIAL_TOKEN_MIN,VIDEO_SERIAL_TOKEN_MAX]. To
 *                  accomplish  this,  simply increment  a  counter that
 *                  loops  around  once VIDEO_SERIAL_TOKEN_MAX  would be
 *                  exceeded.
 * @return: 0 : Success
 * @return: -1: I/O error -- failed to send packet (s.a. `errno') */
extern __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_OUTS(2, 3) int
video_deserializer_io_writepacket(struct video_deserializer_io *__restrict self,
                                  void const *__buf, __size_t __num_bytes,
                                  video_serial_token_t __token);
#else /* __INTELLISENSE__ */
#define video_deserializer_io_destroy(self) (*(self)->vdrio_destroy)(self)
#define video_deserializer_io_readpacket(self, buf, num_bytes, p_fd, token) \
	(*(self)->vdrio_readpacket)(self, buf, num_bytes, p_fd, token)
#define video_deserializer_io_writepacket(self, buf, num_bytes, token) \
	(*(self)->vdrio_writepacket)(self, buf, num_bytes, token)
#endif /* !__INTELLISENSE__ */

__DECL_END
#endif /* __CC__ */
#endif /* CONFIG_LIBVIDEO_HAVE_SERIALIZATION */

#endif /* !_LIBVIDEO_GFX_SERIAL_H */
