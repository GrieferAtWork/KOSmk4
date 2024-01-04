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
#ifndef _LIBSERVICE_SERVER_H
#define _LIBSERVICE_SERVER_H 1

#include "api.h"

#include <bits/types.h>
#include <kos/anno.h>

#include <libservice/bits/com.h>
#include <libservice/types.h>

#ifdef __CC__
__DECL_BEGIN

struct service_api;

struct service_function {
	char const              *sf_name;         /* [1..1] Function name */
	void                    *sf_func;         /* [1..1] Function address (server-side) */
	union service_com_retval sf_error_return; /* Return value by  the non-exception-enabled  client
	                                           * version of  this function  to indicate  invocation
	                                           * failure as the result of  ENOMEM (when it was  not
	                                           * possible to allocate memory for the command desc),
	                                           * or  EINTR (when their thread was interrupted while
	                                           * waiting for us to finish the operation)
	                                           * Unused in exception-enabled function variants, as
	                                           * those will simply throw E_BADALLOC or E_INTERRUPT
	                                           * in these situations. */
	service_typeid_t         sf_return;       /* Function return type code. (one of `SERVICE_TYPE_*') */
	service_typeid_t         sf_params[SERVICE_ARGC_MAX];
	                                          /* Function parameters. (Terminated by first `SERVICE_TYPE_VOID') */
};

/* Initializers for service functions. */
#define SERVICE_FUNCTION_INIT_EX(name, func, error, return_type, ...) \
	{ name, (void *)(func), SERVICE_COM_RETVAL_INIT(error), return_type, { __VA_ARGS__ } }
#ifdef __cplusplus
#define SERVICE_FUNCTION_INIT(name, func)                                     \
	{                                                                         \
		name, (void *)(func),                                                 \
		SERVICE_COM_RETVAL_INIT((int)SERVICE_CXX_FUNINFO(func)::__f_ev::__v), \
		(service_typeid_t)SERVICE_CXX_FUNINFO(func)::__f_rt::__v,             \
		{                                                                     \
			(service_typeid_t)SERVICE_CXX_FUNINFO(func)::__f_a0::__v,         \
			(service_typeid_t)SERVICE_CXX_FUNINFO(func)::__f_a1::__v,         \
			(service_typeid_t)SERVICE_CXX_FUNINFO(func)::__f_a2::__v,         \
			(service_typeid_t)SERVICE_CXX_FUNINFO(func)::__f_a3::__v,         \
			(service_typeid_t)SERVICE_CXX_FUNINFO(func)::__f_a4::__v,         \
			(service_typeid_t)SERVICE_CXX_FUNINFO(func)::__f_a5::__v,         \
			(service_typeid_t)SERVICE_CXX_FUNINFO(func)::__f_a6::__v,         \
			(service_typeid_t)SERVICE_CXX_FUNINFO(func)::__f_a7::__v          \
		}                                                                     \
	}
#endif /* __cplusplus */




struct service_specs {
	/* [1..ss_exportc][const] Export table.
	 * NOTE: _MUST_ be sorted lexicographically ascendingly by `sf_name'! */
	struct service_function const *ss_exportv;

	/* [const] # of exports in `ss_exportv' */
	__size_t ss_exportc;

	/* [const] Per-client context size (s.a. `service_api_context()')
	 * Context  memory  is zero-initialized  by default,  but further
	 * initialization  can be performed by `ss_context_init()', while
	 * finalization can be done by `ss_context_fini' */
	__size_t ss_context_size;

	/* [0..1][const]   Initialize  a  new   context  on  client  attach
	 * This  function is allowed to call `service_api_context()', which
	 * simply  returns `ctx', as  well as `service_api_getpid()', which
	 * will return  the PID  of the  newly attached  client. When  this
	 * function returns with an exception, the client will be forceably
	 * detached, and `ss_context_fini()' will be invoked (if non-NULL). */
	void (LIBSERVICE_CC *ss_context_init)(void *ctx);

	/* [0..1][const] Similar  to `ss_context_init()'.  Note that  while
	 * this function *should* not return with an exception (if it does,
	 * the exception is written to the system log, before  finalization
	 * continues as though no exception had been thrown), this function
	 * _is_ allowed to block and generally perform any blocking  action
	 * it may wish to do.
	 *
	 * As far as  data races go,  this function should  be used to  get
	 * rid of global references to `ctx', following the assumption that
	 * `ctx' may no longer be accessed once this function returns.
	 *
	 * This function is allowed to call `service_api_context()', which
	 * simply  returns `ctx', as well as `service_api_getpid()', which
	 * returns the PID of the client that originally attached. */
	void __NOTHROW_T(LIBSERVICE_CC *ss_context_fini)(void *ctx);
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
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 2)) struct service_api *
__NOTHROW_NCX_T(LIBSERVICE_CC *PSERVICE_API_CREATE)(char const *__restrict filename,
                                                    struct service_specs const *__restrict specs);
typedef __ATTR_NONNULL_T((1)) void
__NOTHROW_T(LIBSERVICE_CC *PSERVICE_API_DESTROY)(struct service_api *__restrict self);
#ifdef LIBSERVICE_WANT_PROTOTYPES
LIBSERVICE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) struct service_api *
__NOTHROW_NCX(LIBSERVICE_CC service_api_create)(char const *__restrict filename,
                                                struct service_specs const *__restrict specs);
LIBSERVICE_DECL __ATTR_NONNULL((1)) void
__NOTHROW(LIBSERVICE_CC service_api_destroy)(struct service_api *__restrict self);
#endif /* LIBSERVICE_WANT_PROTOTYPES */


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
typedef __ATTR_CONST_T __ATTR_RETNONNULL_T __ATTR_WUNUSED_T void *
__NOTHROW_T(LIBSERVICE_CC *PSERVICE_API_CONTEXT)(void);
#ifdef LIBSERVICE_WANT_PROTOTYPES
LIBSERVICE_DECL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED void *
__NOTHROW(LIBSERVICE_CC service_api_context)(void);
#endif /* LIBSERVICE_WANT_PROTOTYPES */

struct ucred;

/* To-be called from  within service functions  (service_function::sf_func).
 * This function returns credentials of the process that originally attached
 * to create the current context, as returned by `service_api_context()'.
 * WARNING: Don't call this function from somewhere other than contexts where
 *          the call originates from within the service API. This requirement
 *          is asserted internally! */
typedef __ATTR_CONST_T __ATTR_RETNONNULL_T __ATTR_WUNUSED_T struct ucred const *
__NOTHROW_T(LIBSERVICE_CC *PSERVICE_API_CRED)(void);
#ifdef LIBSERVICE_WANT_PROTOTYPES
LIBSERVICE_DECL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED struct ucred const *
__NOTHROW(LIBSERVICE_CC service_api_cred)(void);
#endif /* LIBSERVICE_WANT_PROTOTYPES */



/* Exception-enabled variants of the above functions. */
typedef __ATTR_RETNONNULL_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 2)) struct service_api *
(LIBSERVICE_CC *PSERVICEAPICREATE)(char const *__restrict filename,
                                   struct service_specs const *__restrict specs);
#ifdef LIBSERVICE_WANT_PROTOTYPES
LIBSERVICE_DECL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) struct service_api *
(LIBSERVICE_CC ServiceApiCreate)(char const *__restrict filename,
                                 struct service_specs const *__restrict specs);
__COMPILER_REDIRECT_VOID(LIBSERVICE_DECL, __ATTR_NONNULL((1)), __NOTHROW, LIBSERVICE_CC,
                         ServiceApiDestroy, (struct service_api * __restrict self), service_api_destroy, (self))
__COMPILER_REDIRECT(LIBSERVICE_DECL, __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED, void *, __NOTHROW, LIBSERVICE_CC,
                    ServiceApiContext, (void), service_api_context, ())
__COMPILER_REDIRECT(LIBSERVICE_DECL, __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED, struct ucred const *, __NOTHROW, LIBSERVICE_CC,
                    ServiceApiCred, (void), service_api_getpid, ())
#endif /* LIBSERVICE_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBSERVICE_SERVER_H */
