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
#ifndef GUARD_LIBVIDEO_DRIVER_ADAPTER_H
#define GUARD_LIBVIDEO_DRIVER_ADAPTER_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <libvideo/driver/adapter.h>

DECL_BEGIN

/* Open  the  video adapter  indicated by  `name'  (the filename  of a
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
INTDEF WUNUSED struct video_adapter *CC
libvideo_adapter_open(char const *name);

DECL_END

#endif /* !GUARD_LIBVIDEO_DRIVER_ADAPTER_H */
