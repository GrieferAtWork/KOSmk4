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
#ifndef _LIBVIDEO_GFX_BUFFER_DUMMY_H
#define _LIBVIDEO_GFX_BUFFER_DUMMY_H 1

#include "../api.h"
/**/

#include <hybrid/__atomic.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/refcnt.h>

#ifdef __CC__
__DECL_BEGIN

struct video_buffer_dummy {
	__byte_t   *vbd_data;   /* [1..vbd_size][owned][const]  mmap'd,  anonymous  memory.
	                         * Anything written to this memory may be lost or discarded
	                         * at an arbitrary point in time, and reads yield undefined
	                         * data. */
	__size_t    vbd_size;   /* [const] Dummy data blob size (in bytes) */
	__uintptr_t vbd_refcnt; /* Reference counter */
	__ATTR_NONNULL_T((1))   /* [1..1][const] Destructor callback */
	void (LIBVIDEO_GFX_CC *vbd_destroy)(struct video_buffer_dummy *__restrict __self);
};

#define video_buffer_dummy_destroy(self) (*(self)->vbd_destroy)(self)
#define video_buffer_dummy_incref(self) \
	__hybrid_atomic_inc(&(self)->vbd_refcnt, __ATOMIC_SEQ_CST)
#define video_buffer_dummy_decref(self)                                       \
	(void)(__hybrid_atomic_decfetch(&(self)->vbd_refcnt, __ATOMIC_SEQ_CST) || \
	       (video_buffer_dummy_destroy(self), 0))
__DEFINE_REFCNT_FUNCTIONS(struct video_buffer_dummy, vbd_refcnt, video_buffer_dummy_destroy)


/* Return a video buffer dummy representing at least `__num_bytes' bytes of data
 * @return: * : A reference to a dummy buffer able to substitute at least `__num_bytes' bytes
 * @return: NULL: Insufficient memory */
typedef __ATTR_WUNUSED_T __REF struct video_buffer_dummy *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_GETDUMMY)(__size_t __num_bytes);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __REF struct video_buffer_dummy *
(LIBVIDEO_GFX_CC video_buffer_getdummy)(__size_t __num_bytes);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_BUFFER_DUMMY_H */
