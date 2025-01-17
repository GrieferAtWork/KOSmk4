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
#ifndef _LIBSERVICE_CLIENT_H
#define _LIBSERVICE_CLIENT_H 1

#include "api.h"

/* A  user-space library with  which it is  possible for processes to
 * declare an inter-process function export table that can be  loaded
 * by  other processes, which  in turn are then  able to invoke those
 * functions within said export  table like normal C-functions,  only
 * that pointers  taken/returned  by  such  functions  point  into  a
 * special region of memory shared between this the client and server
 * instances of this library.
 *
 * EXAMPLE:
 *
 * Client:
 * >> #include <libservice/client.h>
 * >>
 * >> int main() {
 * >>     int (*func)(int, int);
 * >>     struct service *svc;
 * >>     int result;
 * >>     printf("[client] Loading service...\n");
 * >>     svc             = service_open("/tmp/service");
 * >>     *(void **)&func = service_dlsym(svc, "func");
 * >>     printf("[client] Calling service function...\n");
 * >>     result          = (*func)(10, 20);
 * >>     service_close(svc);
 * >>     printf("[client] result = %d\n", result);
 * >> }
 *
 * Server (possibly in a different process):
 * >> #include <libservice/server.h>
 * >> #include <stdio.h>
 * >>
 * >> static int exported_func(int x, int y) {
 * >>     char procname[64];
 * >>     sprintf(procname, "/proc/%d/exe", service_api_getpid());
 * >>     procname[readlink(procname, procname, sizeof(procname))] = 0;
 * >>     printf("[server] exported_func(%d, %d)\n", x, y);
 * >>     printf("[server]     called from: %q (%d)\n", procname, service_api_getpid());
 * >>     printf("[server]     context:     %p\n", service_api_context());
 * >>     return x + y;
 * >> }
 * >>
 * >> static void on_attach(void *) {
 * >>     char procname[64];
 * >>     sprintf(procname, "/proc/%d/exe", service_api_getpid());
 * >>     procname[readlink(procname, procname, sizeof(procname))] = 0;
 * >>     printf("[server] attach: %q (%d)\n", procname, service_api_getpid());
 * >> }
 * >>
 * >> static void on_detach(void *) {
 * >>     char procname[64];
 * >>     sprintf(procname, "/proc/%d/exe", service_api_getpid());
 * >>     procname[readlink(procname, procname, sizeof(procname))] = 0;
 * >>     printf("[server] detach: %q (%d)\n", procname, service_api_getpid());
 * >> }
 * >>
 * >> static struct service_function const functions[] = {
 * >>     SERVICE_FUNCTION_INIT("func", &exported_func),
 * >> };
 * >>
 * >> static struct service_specs const specs = {
 * >>     .ss_exportv      = functions,
 * >>     .ss_exportc      = lengthof(functions),
 * >>     .ss_context_init = &on_attach,
 * >>     .ss_context_fini = &on_detach,
 * >> };
 * >>
 * >> int main() {
 * >>     struct service_api *svc;
 * >>     unlink("/tmp/service");
 * >>     svc = service_api_create("/tmp/service", &specs);
 * >>     pause();
 * >>     service_api_destroy(svc);
 * >> }
 *
 * Output (example):
 * $ ./server &
 * $ ./client
 * [client] Loading service...
 * [server] attach /tmp/client (42)                      # Depending on scheduling, this line
 * [client] Calling server function...                   # ... and this one may be swapped!
 * [server] exported_func(10, 20)
 * [server]     called from: /tmp/client (42)
 * [server]     context:     70BC2DE0
 * [client] result = 30
 * [server] detach /tmp/client (42)
 *
 */

#include <bits/types.h>
#include <kos/anno.h>

#ifdef __CC__
__DECL_BEGIN

struct service;

/* Client API interface for service. Note that opening the same
 * service more than once will return unique handles each time,
 * and  also establish individual connections to the associated
 * server!
 *
 * @return: * :   Opaque handle for the service. In this case,  the
 *                server is/has/will have created a context for the
 *                current process.
 * @return: NULL: [errno=ENOENT] No function exists with the given name.
 * @return: NULL: [errno=EINTR]  The calling thread was interrupted.
 * @return: NULL: [errno=ENOMEM] Insufficient memory. */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) struct service *
__NOTHROW_RPC_T(LIBSERVICE_CC *PSERVICE_OPEN)(char const *filename);
#ifdef LIBSERVICE_WANT_PROTOTYPES
LIBSERVICE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct service *
__NOTHROW_RPC(LIBSERVICE_CC service_open)(char const *filename);
#endif /* LIBSERVICE_WANT_PROTOTYPES */

/* Close/detach a given service. WARNING: After this function was called,
 * all function pointers  returned by `service_dlsym()'  will point  into
 * the void /  into unmapped memory.  As such, it  is up to  the user  to
 * ensure that no part  of the process  is still using  a service at  the
 * time of it being closed.
 * Services not closed when the calling process exits, or makes a call
 * to one  of the  `exec()' functions  will be  closed  automatically. */
typedef __NOBLOCK __ATTR_NONNULL_T((1)) void
__NOTHROW_T(LIBSERVICE_CC *PSERVICE_CLOSE)(struct service *__restrict self);
#ifdef LIBSERVICE_WANT_PROTOTYPES
LIBSERVICE_DECL __NOBLOCK __ATTR_NONNULL((1)) void
__NOTHROW(LIBSERVICE_CC service_close)(struct service *__restrict self);
#endif /* LIBSERVICE_WANT_PROTOTYPES */


/* The heart-piece of all of libservice:  lookup a symbol exported by  the
 * given service `self', dynamically generate a callback wrapper function,
 * and finally return the address of said wrapper function which can  then
 * be called  like any  other  C-function (using  `LIBSERVICE_CC'  calling
 * convention, which is  guarantied to be  the default calling  convention
 * for the current architecture)
 *
 * Note that server functions like those generated by this API are always
 * re-entrance safe, in that they can  be invoked from any context  (esp.
 * including signal handler) and by  any number of threads,  irregardless
 * of how  the server-side  implementation of  the function  looks  like!
 * Generally  speaking, you  can think  of service  functions like system
 * calls,  and as a matter of fact:  the entire idea of service functions
 * stems from the idea of having a user-space API to expose inter-process
 * functions which can be called from an arbitrary context similar to how
 * system calls also can!
 *
 * @return: * :   Pointer to the service wrapper function.
 * @return: NULL: [errno=ENOENT] No function exists with the given name.
 * @return: NULL: [errno=EINTR]  The calling thread was interrupted.
 * @return: NULL: [errno=ENOMEM] Insufficient memory. */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 2)) void *
__NOTHROW_RPC_T(LIBSERVICE_CC *PSERVICE_DLSYM)(struct service *__restrict self,
                                               char const *__restrict symname);
#ifdef LIBSERVICE_WANT_PROTOTYPES
LIBSERVICE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) void *
__NOTHROW_RPC(LIBSERVICE_CC service_dlsym)(struct service *__restrict self,
                                           char const *__restrict symname);
#endif /* LIBSERVICE_WANT_PROTOTYPES */



/* Service interface buffer alloc/free. These functions will allocate memory
 * in very special locations can be serialized/deserialized much faster when
 * passed as arguments to server functions than when using buffers allocated
 * by other means.
 * Use these functions for creating/freeing buffers for the purpose of holding
 * large  quantities of  data to-be shared  with the server.  Note that memory
 * returned  by these functions  is literally shared  with the server, meaning
 * that  you really don't want to store any information in here that you don't
 * want to share with the server!
 * NOTE: These  functions only  guaranty that  returned pointers  are aligned by
 *       sizeof(void *), rather than `__ALIGNOF_MAX_ALIGN_T__', as is guarantied
 *       by the regular `malloc'!
 * @return: * :   Base address of the buffer.
 * @return: NULL: [errno=ENOMEM] Insufficient memory. */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) void *
__NOTHROW_T(LIBSERVICE_CC *PSERVICE_BUFFER_MALLOC)(struct service *__restrict self,
                                                   __size_t num_bytes);
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) void *
__NOTHROW_T(LIBSERVICE_CC *PSERVICE_BUFFER_CALLOC)(struct service *__restrict self,
                                                   __size_t num_bytes);
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) void *
__NOTHROW_T(LIBSERVICE_CC *PSERVICE_BUFFER_REALLOC)(struct service *__restrict self,
                                                    void *ptr, __size_t num_bytes);
typedef __NOBLOCK __ATTR_NONNULL_T((1)) void
__NOTHROW_T(LIBSERVICE_CC *PSERVICE_BUFFER_FREE)(struct service *__restrict self,
                                                 void *ptr);
#ifdef LIBSERVICE_WANT_PROTOTYPES
LIBSERVICE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *
__NOTHROW(LIBSERVICE_CC service_buffer_malloc)(struct service *__restrict self,
                                               __size_t num_bytes);
LIBSERVICE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *
__NOTHROW(LIBSERVICE_CC service_buffer_calloc)(struct service *__restrict self,
                                               __size_t num_bytes);
LIBSERVICE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *
__NOTHROW(LIBSERVICE_CC service_buffer_realloc)(struct service *__restrict self,
                                                void *ptr, __size_t num_bytes);
LIBSERVICE_DECL __NOBLOCK __ATTR_NONNULL((1)) void
__NOTHROW(LIBSERVICE_CC service_buffer_free)(struct service *__restrict self,
                                             void *ptr);
#endif /* LIBSERVICE_WANT_PROTOTYPES */

/* Returns the usable size of the given `ptr'. */
typedef __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __size_t
__NOTHROW_T(LIBSERVICE_CC *PSERVICE_BUFFER_MALLOC_USABLE_SIZE)(struct service *__restrict self,
                                                                  void *ptr);
#ifdef LIBSERVICE_WANT_PROTOTYPES
LIBSERVICE_DECL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __size_t
__NOTHROW(LIBSERVICE_CC service_buffer_malloc_usable_size)(struct service *__restrict self,
                                                           void *ptr);
#endif /* LIBSERVICE_WANT_PROTOTYPES */



/* Exception-enabled versions of the above. */
typedef __ATTR_RETNONNULL_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) struct service *
(LIBSERVICE_CC *PSERVICEOPEN)(char const *filename)
		__THROWS(E_FSERROR, E_BADALLOC, E_INTERRUPT);
typedef __ATTR_RETNONNULL_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 2)) void *
(LIBSERVICE_CC *PSERVICEDLSYM)(struct service *__restrict self,
                             char const *__restrict symname)
		__THROWS(E_NO_SUCH_OBJECT, E_BADALLOC, E_INTERRUPT);
typedef __ATTR_RETNONNULL_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) void *
(LIBSERVICE_CC *PSERVICEBUFFERMALLOC)(struct service *__restrict self, __size_t num_bytes)
		__THROWS(E_BADALLOC);
typedef __ATTR_RETNONNULL_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) void *
(LIBSERVICE_CC *PSERVICEBUFFERCALLOC)(struct service *__restrict self, __size_t num_bytes)
		__THROWS(E_BADALLOC);
typedef __ATTR_RETNONNULL_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) void *
(LIBSERVICE_CC *PSERVICEBUFFERREALLOC)(struct service *__restrict self, void *ptr, __size_t num_bytes)
		__THROWS(E_BADALLOC);
#ifdef LIBSERVICE_WANT_PROTOTYPES
LIBSERVICE_DECL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct service *
(LIBSERVICE_CC ServiceOpen)(char const *filename)
		__THROWS(E_FSERROR, E_BADALLOC, E_INTERRUPT);
LIBSERVICE_DECL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) void *
(LIBSERVICE_CC ServiceDlSym)(struct service *__restrict self,
                             char const *__restrict symname)
		__THROWS(E_NO_SUCH_OBJECT, E_BADALLOC, E_INTERRUPT);
__COMPILER_REDIRECT_VOID(LIBSERVICE_DECL, __ATTR_NONNULL((1)), __NOTHROW, LIBSERVICE_CC,
                         ServiceClose, (struct service * __restrict self),
                         service_close, (self))
LIBSERVICE_DECL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *
(LIBSERVICE_CC ServiceBufferMalloc)(struct service *__restrict self, __size_t num_bytes)
		__THROWS(E_BADALLOC);
LIBSERVICE_DECL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *
(LIBSERVICE_CC ServiceBufferCalloc)(struct service *__restrict self, __size_t num_bytes)
		__THROWS(E_BADALLOC);
LIBSERVICE_DECL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *
(LIBSERVICE_CC ServiceBufferRealloc)(struct service *__restrict self, void *ptr, __size_t num_bytes)
		__THROWS(E_BADALLOC);
__COMPILER_REDIRECT_VOID(LIBSERVICE_DECL, __NOBLOCK __ATTR_NONNULL((1)), __NOTHROW, LIBSERVICE_CC,
                         ServiceBufferFree, (struct service * __restrict self, void *ptr),
                         service_buffer_free, (self, ptr))
__COMPILER_REDIRECT(LIBSERVICE_DECL, __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),
                    __size_t, __NOTHROW, LIBSERVICE_CC,
                    ServiceBufferMallocUsableSize, (struct service * __restrict self, void *ptr),
                    service_buffer_malloc_usable_size, (self, ptr))
#endif /* LIBSERVICE_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBSERVICE_CLIENT_H */
