/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBSERVICE_SERVER_C
#define GUARD_LIBSERVICE_SERVER_C 1

#include "api.h"
/**/

#include <kos/except.h>
#include <kos/sys/socket.h>
#include <kos/types.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <libservice/server.h>

#include "server.h"

DECL_BEGIN

/*
 * NOTE: Graceful client disconnect is done as follows:
 *  - Set a marker-flag that prevents the spawning of new client threads,
 *    as well as sleeping threads from consuming pending com descriptors.
 *  - Cancel all still-running service threads for the client.
 *    In turn, any active command completes with status SERVICE_COM_ST_ECHO,
 *    which  a connected client will interpret as the service having exited.
 *  - Once  no more threads  are running for the  purpose of serving client
 *    commands, (meaning that  nothing else is  still accessing the  client
 *    data area), simply close(2) the originally accept(2)'ed client socket
 *    and have the attached client do the rest of the work.
 *  - Cleanup all remaining data, including our primary SHM mapping.
 *
 * NOTE: Forced client disconnect (as the result of a HUP on the originally
 *       accept(2)'ed client socket) is done the same.
 *
 * FIXME: What  about ENOMEM resulting when trying to cancel the worker threads.
 *        As a matter of fact: this is a problem pthread_cancel() faces as well,
 *        but currently simply ignores as though it couldn't happen... */




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
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct service_api *CC
libservice_api_create(char const *__restrict filename,
                      struct service_specs const *__restrict specs) {
	/* TODO */
	(void)filename;
	(void)specs;
	abort();
}

INTERN WUNUSED NONNULL((1, 2)) struct service_api *
NOTHROW_NCX(CC libservice_api_create_nx)(char const *__restrict filename,
                                         struct service_specs const *__restrict specs) {
	NESTED_TRY {
		return libservice_api_create(filename, specs);
	} EXCEPT {
		except_class_t cls = except_class();
		if (EXCEPTCLASS_ISRTLPRIORITY(cls))
			RETHROW();
		errno = except_as_errno(except_data());
	}
	return NULL;
}

INTERN NONNULL((1)) void
NOTHROW(CC libservice_api_destroy)(struct service_api *__restrict self) {
	/* TODO */
	(void)self;
	abort();
}


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
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED void *
NOTHROW(CC libservice_api_context)(void) {
	/* TODO */
	abort();
}

/* To-be called from  within service functions  (service_function::sf_func).
 * This function returns credentials of the process that originally attached
 * to create the current context, as returned by `service_api_context()'.
 * WARNING: Don't call this function from somewhere other than contexts where
 *          the call originates from within the service API. This requirement
 *          is asserted internally! */
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED struct ucred const *
NOTHROW(CC libservice_api_cred)(void) {
	/* TODO */
	abort();
}



/* Exports */
DEFINE_PUBLIC_ALIAS(ServiceApiCreate, libservice_api_create);
DEFINE_PUBLIC_ALIAS(service_api_create, libservice_api_create_nx);
DEFINE_PUBLIC_ALIAS(service_api_destroy, libservice_api_destroy);
DEFINE_PUBLIC_ALIAS(service_api_context, libservice_api_context);
DEFINE_PUBLIC_ALIAS(service_api_cred, libservice_api_cred);


DECL_END

#endif /* !GUARD_LIBSERVICE_SERVER_C */
