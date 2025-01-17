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
#ifndef GUARD_LIBSERVICE_SERVER_H
#define GUARD_LIBSERVICE_SERVER_H 1

#include "api.h"

#include <kos/types.h>

#include <libservice/server.h>

DECL_BEGIN


struct service_api {
	struct service_specs const *sa_specs;  /* [1..1][const] Service specs. */
	fd_t                        sa_server; /* [owned][const] AF_UNIX-socket bound to the service file. */

};



/* Create a service that is reachable under `filename' and exposes the given set of functions.
 * NOTE: The given  set of  functions _must_  be sorted  lexicographically
 *       ascending by name, as binary search is used to locate appropriate
 *       entries during client lookup requests!
 * @throws: E_FSERROR_FILE_ALREADY_EXISTS: The  specified `filename' already exists. Note that
 *                                         this  function uses unix domain sockets internally,
 *                                         which create files during bind that are not removed
 *                                         when the socket is closed. As such, you really need
 *                                         to handle this case by unlink(2)-ing the file prior
 *                                         to calling this function. */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct service_api *CC
libservice_api_create(char const *__restrict filename,
                      struct service_specs const *__restrict specs);
INTDEF WUNUSED NONNULL((1, 2)) struct service_api *
NOTHROW_NCX(CC libservice_api_create_nx)(char const *__restrict filename,
                                         struct service_specs const *__restrict specs);
INTDEF NONNULL((1)) void
NOTHROW(CC libservice_api_destroy)(struct service_api *__restrict self);


/* To-be called  from within  service functions  (service_function::sf_func).
 * This function  returns the  pointer to  the originating  client's  current
 * context, which is a `ss_context_size'-bytes large blob that was originally
 * initialized by `ss_context_init'  and will eventually  be finalized  (once
 * the calling client detaches) when `ss_context_fini' is called.
 * WARNING: Context data is _NOT_ TLS! There may be multiple threads operating
 *          on data within the context area at the same time (especially  when
 *          the client performs multiple simultaneous calls)
 * WARNING: Don't call this function from somewhere other than contexts where
 *          the call originates from within the service API. This requirement
 *          is asserted internally! */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED void *
NOTHROW(CC libservice_api_context)(void);

/* To-be called from  within service functions  (service_function::sf_func).
 * This function returns credentials of the process that originally attached
 * to create the current context, as returned by `service_api_context()'.
 * WARNING: Don't call this function from somewhere other than contexts where
 *          the call originates from within the service API. This requirement
 *          is asserted internally! */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED struct ucred const *
NOTHROW(CC libservice_api_cred)(void);


DECL_END

#endif /* !GUARD_LIBSERVICE_SERVER_H */
