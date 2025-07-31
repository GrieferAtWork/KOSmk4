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
#ifndef _LIBVIDEO_DRIVER_ADAPTER_H
#define _LIBVIDEO_DRIVER_ADAPTER_H 1

#include "api.h"
/**/

#include <__stdinc.h>
#include <kos/anno.h>

#include <libvideo/gfx/buffer.h>

#ifdef __CC__
__DECL_BEGIN

struct video_adapter;
struct video_monitor;

struct video_adapter_ops {
	/* Unload this video adapter. The  caller is responsible to ensure  that
	 * all video objects created by the adapter have been destroyed already. */
	__ATTR_NONNULL_T((1)) void
	(LIBVIDEO_DRIVER_CC *vdro_close)(struct video_adapter *__restrict __self);

	/* Return a reference to the `__index'th monitor
	 * connected to the  GPU described by  `__self'.
	 * @return: * :   Reference to the `__index'th monitor of `__self'
	 * @return: NULL: [errno=ERANGE] Given `__index' is too large
	 * @return: NULL: [errno=ENODEV] No monitor connected under `__index'
	 * @return: NULL: [errno=ENOMEM] Insufficient memory
	 * @return: NULL: [errno=*] Some other error */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) __REF struct video_monitor *
	(LIBVIDEO_DRIVER_CC *vdro_getmonitor)(struct video_adapter *__restrict __self,
	                                      __size_t __index);
};

struct video_adapter
#ifdef __cplusplus
    : video_domain
#define _video_adapter__vad_domain /* nothing */
#define video_adapter_asdomain     /* nothing */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct video_domain vad_domain;
#define _video_adapter__vad_domain vad_domain.
#define video_adapter_asdomain(self) (&(self)->vad_domain)
#endif /* __cplusplus */
	struct video_adapter_ops const *vad_ops; /* [1..1][const] Driver operators */
};


#ifdef __INTELLISENSE__
/* Unload this video adapter. The  caller is responsible to ensure  that
 * all video objects created by the adapter have been destroyed already. */
extern __ATTR_NONNULL((1)) void
video_adapter_close(struct video_adapter *__restrict __self);

/* Return a reference to the `__index'th monitor
 * connected to the  GPU described by  `__self'.
 * @return: * :   Reference to the `__index'th monitor of `__self'
 * @return: NULL: [errno=ERANGE] Given `__index' is too large
 * @return: NULL: [errno=ENODEV] No monitor connected under `__index'
 * @return: NULL: [errno=ENOMEM] Insufficient memory
 * @return: NULL: [errno=*] Some other error */
extern __ATTR_WUNUSED __ATTR_INOUT(1) __REF struct video_monitor *
video_adapter_getmonitor(struct video_adapter *__restrict __self,
                         __size_t __index);
#else /* __INTELLISENSE__ */
#define video_adapter_close(self)             (*(self)->vad_ops->vdro_close)(self)
#define video_adapter_getmonitor(self, index) (*(self)->vad_ops->vdro_getmonitor)(self, index)
#endif /* !__INTELLISENSE__ */


/* Open the video  adapter indicated  by `__name' (the  filename of  a
 * device file; e.g. `/dev/svga'), or the system default video adapter
 * when `NULL'
 *
 * Note that the kernel enforcing that the same video device can only
 * ever be opened once, by a single process (iow: this function  will
 * block if you, or another process has already opened a device).
 *
 * Also note that this function generally can only be called by root.
 *
 * @return: * : Success (the newly allocated)
 * @return: NULL: [errno=ENOENT] Specified device file doesn't exist
 * @return: NULL: [errno=ENODEV] Specified device file isn't supported, or not a device
 * @return: NULL: [errno=ENOMEM] Insufficient memory
 * @return: NULL: [errno=*] Failed to open adapter for some other reason */
typedef __ATTR_WUNUSED_T struct video_adapter *
(LIBVIDEO_DRIVER_CC *PVIDEO_ADAPTER_OPEN)(char const *__name);
#ifdef LIBVIDEO_DRIVER_WANT_PROTOTYPES
LIBVIDEO_DRIVER_DECL __ATTR_WUNUSED struct video_adapter *
(LIBVIDEO_DRIVER_CC video_adapter_open)(char const *__name);
#endif /* LIBVIDEO_DRIVER_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_DRIVER_ADAPTER_H */
