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
#ifndef _LIBVIDEO_COMPOSITOR_SERIAL_H
#define _LIBVIDEO_COMPOSITOR_SERIAL_H 1

#include "api.h"
/**/

#include <__stdinc.h>

#include <bits/types.h>
#include <kos/anno.h>

#include <libvideo/gfx/serial.h>

/************************************************************************/
/* LOW-LEVEL, SERVER-SIDE VIDEO SERIALIZATION                           */
/************************************************************************/

#ifdef CONFIG_LIBVIDEO_HAVE_SERIALIZATION

/* Serialization classifications (only allowed in `video_buffer_serialize()') */
#define VIDEO_SERIAL_CLASS_ANY  0x0000 /* Use whatever serialization method is fastest */
#define VIDEO_SERIAL_CLASS_NOFD 0x0001 /* Use whatever serialization method is fastest, but don't require use of an FD */

#ifdef __CC__
__DECL_BEGIN

struct video_serializer_io {
	/* [1..1] Send a packet to whomever is hosting the video buffer.
	 * @param: __fd: File descriptor attached to the packet, or `-1' if there is none.
	 *               Serializes that don't support file descriptors can simply  ignore
	 *               this parameter.
	 * @return: 0 : Success
	 * @return: -1: I/O error trying to send packet. */
	int (LIBVIDEO_COMPOSITOR_CC *vsrio_writepacket)(struct video_serializer_io *__restrict self,
	                                                void const *__buf, __size_t __num_bytes, __fd_t __fd);
	/* [1..1] Called by the associated video_serializer when it is destroyed */
	void (LIBVIDEO_COMPOSITOR_CC *vsrio_destroy)(struct video_serializer_io *__restrict self);
};

/* TODO: Macro wrappers for invoking operators of `struct video_serializer_io' */

struct video_serializer {
	__REF struct video_buffer  *vsr_buffer; /* [1..1][const] The video buffer that is being serialized */
	struct video_serializer_io *vsr_serial; /* [1..1][const] Associated serialization I/O methods */
	video_serial_proto_t        vsr_proto;  /* [lock(...)] Serialization protocol used (might change during `vsr_packet()') */
	__uintptr_t                 vsr_refcnt; /* Reference counter */
	/* [1..1] Called when the serializer's reference counter hits 0 */
	void (LIBVIDEO_COMPOSITOR_CC *vsr_destroy)(struct video_serializer *__restrict self);
	/* [1..1] Called in order to handle a packet that was received from the client
	 * NOTE: Malformed packets are logged to syslog(2), but cause "0" to be returned here.
	 * @return: 0 : Success
	 * @return: -1: I/O error when trying to respond to packet */
	int (LIBVIDEO_COMPOSITOR_CC *vsr_packet)(struct video_serializer *__restrict self,
	                                         void const *__buf, __size_t __num_bytes);
};

/* TODO: Macro wrappers for invoking operators of `struct video_serializer' */


/* Create a new serializer for interacting with "buffer"
 * @param: __buffer: The video buffer that should be serialized.
 * @param: __io:     I/O callbacks for sending packets to the serialization client.
 * @param: __proto:  Initial serialization protocol to use (might change later)
 *                   You  are also allowed to pass `VIDEO_SERIAL_CLASS_*' here,
 *                   which  will give the  internal implementation more options
 *                   in regard to selecting the optimal protocol.
 * @return: * : Serialization descriptor. Call its `vsr_packet()' operator to have
 *              it  receive  client-side instructions  and potentially  respond by
 *              sending answer packets via operators in `__io'.
 * @return: NULL: [errno=ENOMEM] Insufficient memory.
 * @return: NULL: [errno=EINVAL] Given protocol `__proto' is not supported by `__buffer'
 * @return: NULL: [errno=*] Failed to create serializer for some other reason */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 2)) __REF struct video_serializer *
(LIBVIDEO_COMPOSITOR_CC *PVIDEO_BUFFER_SERIALIZE)(struct video_buffer *__restrict __buffer,
                                                  /*inherit(on_success)*/ struct video_serializer_io *__restrict __io,
                                                  video_serial_proto_t __proto);
#ifdef LIBVIDEO_COMPOSITOR_WANT_PROTOTYPES
LIBVIDEO_COMPOSITOR_DECL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __REF struct video_serializer *LIBVIDEO_COMPOSITOR_CC
video_buffer_serialize(struct video_buffer *__restrict __buffer,
                       /*inherit(on_success)*/ struct video_serializer_io *__restrict __io,
                       video_serial_proto_t __proto);
#endif /* LIBVIDEO_COMPOSITOR_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */
#endif /* CONFIG_LIBVIDEO_HAVE_SERIALIZATION */

#endif /* !_LIBVIDEO_COMPOSITOR_SERIAL_H */
