/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBVIO_VIO_H
#define GUARD_LIBVIO_VIO_H 1

#include "api.h"

#include <kos/types.h>

#include <libvio/vio.h>

DECL_BEGIN

#ifdef LIBVIO_CONFIG_ENABLED
#ifndef __KERNEL__

/* vio_create(3):
 * >> fd_t vio_create(struct vio_operators *ops, void *cookie, oflag_t flags);
 * @param: flags:  Set of `0 | O_CLOEXEC | O_CLOFORK'
 * @param: cookie: A cookie pointer that is available as `args->va_cookie'
 * Desc:
 *     Create an mmap(2)able VIO object where memory accesses
 *     made to the object are serviced by dispatching them via
 *     the given `ops' table.
 *     The returned file descriptor mustn't be deleted by `close(2)',
 *     but rather through use of `vio_destroy(3)'.
 *     Note that callbacks in `ops' may be invoked in the context
 *     of a different thread than the one that performed the memory
 *     access. Also note that the returned `fd_t' can be shared with
 *     other processes, but still function as expected. (when shared
 *     with a different process, that process should once again make
 *     use of `close(2)' for cleanup, rather than `vio_destroy(3)')
 * Impl:
 *     Call `userviofd()' and store the returned handle in a list
 *     of active VIO objects. If the list becomes non-empty, start
 *     a background thread that poll(2)s from all registered `userviofd()'
 *     objects, and services the requests by dispatching them through
 *     the ops-table originally passed to `vio_create()' */
INTDEF WUNUSED NONNULL((1)) fd_t
NOTHROW_NCX(CC libvio_create)(struct vio_operators const *ops,
                              void *cookie, oflag_t flags);


/* vio_destroy(3):
 * >> int vio_destroy(fd_t fd);
 * Desc:
 *     Destroy a VIO file descriptor previously created by `vio_create(3)'
 * Impl:
 *     Remove `fd' from the set of active userfd handles. If all
 *     handles get closed, stop the background thread used to
 *     service VIO requests. */
INTDEF int NOTHROW_NCX(CC libvio_destroy)(fd_t fd);

#endif /* !__KERNEL__ */
#endif /* LIBVIO_CONFIG_ENABLED */

DECL_END

#endif /* !GUARD_LIBVIO_VIO_H */
