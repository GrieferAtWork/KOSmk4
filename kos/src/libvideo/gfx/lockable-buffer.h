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
#ifndef GUARD_LIBVIDEO_GFX_LOCKABLE_BUFFER_H
#define GUARD_LIBVIDEO_GFX_LOCKABLE_BUFFER_H 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>
#include <stddef.h>

#include <libvideo/gfx/buffer.h>

DECL_BEGIN

struct lockable_buffer: video_buffer {
	REF struct video_buffer *lb_base;   /* [1..1][const] Underlying video buffer */
	byte_t                  *lb_data;   /* [0..vl_size][owned][lock(WRITE_ONCE)] Cached video data */
	size_t                   lb_stride; /* [valid_if(lb_data)] Scanline width (in bytes) */
	byte_t                  *lb_edata;  /* [valid_if(lb_data)] End of lock data */
};

/* Check if `buffer' is lockable. If so re-return "buffer" and
 * initialize `self' such that `libvideo_buffer_lockable_fini'
 * does nothing. Else, wrap it using `buffer' and return  *it*
 * instead. */
INTDEF WUNUSED ATTR_OUT(1) NONNULL((2)) struct video_buffer *CC
libvideo_buffer_lockable_init(struct lockable_buffer *self,
                              struct video_buffer *__restrict buffer);
INTDEF NONNULL((1)) void
NOTHROW(CC libvideo_buffer_lockable_fini)(struct lockable_buffer *__restrict self);



/* When `__self' isn't known to unconditionally support read/write  locks,
 * wrap it using a proxy video buffer that implements these operations as:
 * - Attempt the lock on the underlying buffer.
 * - If that fails:
 *   - Allocate a heap buffer matching requirements of the buffer's codec
 *   - If that fails, return from vi_rlock/vi_wlock with -1,errno=ENOMEM
 *   - On success, use a GFX context to read pixel data and store it in
 *     the heap buffer.
 *   - Return said heap buffer from vi_rlock/vi_wlock
 * - In case `vi_wlock' was called, the matching `vi_unlock' will  then
 *   once again use a GFX context to at least all modified (or possibly
 *   just all) pixels back to the underlying buffer.
 * @param: __self:  The video buffer to wrap
 * @return: * :     The video buffer wrapper (having the same codec/dimensions as `__self')
 * @return: __self: The given `__self' is already known to have vi_rlock/vi_wlock operators
 *                  that either never fail, or can only fail with errno=ENOMEM for the same
 *                  reason that the  "lockable" wrapper could  also fail. (generally,  this
 *                  means that this is a no-op when `__self' is a ram-buffer, or is already
 *                  a "lockable" video buffer). */
INTDEF WUNUSED ATTR_INOUT(1) REF struct video_buffer *CC
libvideo_buffer_lockable(struct video_buffer *__restrict self);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_LOCKABLE_BUFFER_H */
