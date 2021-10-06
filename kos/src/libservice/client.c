/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBSERVICE_CLIENT_C
#define GUARD_LIBSERVICE_CLIENT_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/align.h>

#include <kos/except.h>
#include <kos/malloc.h>
#include <kos/sys/mman.h>
#include <kos/sys/socket.h>
#include <kos/types.h>
#include <kos/unistd.h>
#include <sys/un.h>

#include <alloca.h>
#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <libservice/client.h>

#include "client.h"
#include "com.h"

DECL_BEGIN

#ifndef NDEBUG
#define DBG_memset memset
#else /* !NDEBUG */
#define DBG_memset(...) (void)0
#endif /* NDEBUG */

/* Exception-enabled version of `libservice_open_nx()'. */
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct service *CC
libservice_open(char const *filename) THROWS(E_FSERROR, E_BADALLOC, E_INTERRUPT) {
	struct service *result;
	REF struct service_shm_handle *shm;
	result = (struct service *)Malloc(sizeof(struct service));
	TRY {
		atomic_lock_init(&result->s_shm_lock);
		SLIST_INIT(&result->s_shm_lops);
		shm = service_shm_handle_alloc();
		TRY {
			shm->ssh_refcnt    = 1;
			shm->ssh_tree_lhs  = NULL;
			shm->ssh_tree_rhs  = NULL;
			shm->ssh_tree_red  = 1; /* Singular leaf is always red */
			shm->ssh_service   = result;
			result->s_shm      = shm;
			result->s_shm_tree = shm;
			atomic_rwlock_init(&result->s_textlock);
			SLIST_INIT(&result->s_txranges);
			SLIST_INIT(&result->s_ehranges);
			result->s_funcc = 0;
			result->s_funcv = NULL;

			/* Create the socket which we're going to use to communicate with the server. */
			result->s_fd_srv = Socket(AF_UNIX, SOCK_STREAM, PF_UNIX);
			TRY {
				struct sockaddr_un *sa;
				socklen_t sa_len;
				size_t filename_size;

				/* Connect to a unix domain socket bound to the given file. */
				filename_size  = (strlen(filename) + 1) * sizeof(char);
				sa_len         = offsetof(struct sockaddr_un, sun_path) + filename_size;
				sa             = (struct sockaddr_un *)alloca(sa_len);
				sa->sun_family = AF_UNIX;
				memcpy(sa->sun_path, filename, filename_size);
				Connect(result->s_fd_srv, (struct sockaddr *)sa, sa_len);

				/* TODO: Server handshake + acquire SHM handle. */

				(void)filename;
				abort();

				TRY {
					struct service_shm_free *allfree;
					size_t pagesize = getpagesize();
					size_t shm_size = pagesize * 4;
					byte_t *shm_base;
					unsigned int bucket;

					/* This really shouldn't happen, but we mustn't assume anything about `getpagesize()'!
					 * Note that in all likelihood, the compiler will just optimize this away,  especially
					 * when `getpagesize()' expands to a constant integer. */
					if unlikely(shm_size < SERVICE_SHM_ALLOC_MINSIZE)
						shm_size = CEIL_ALIGN(SERVICE_SHM_ALLOC_MINSIZE, pagesize);

					/* Allocate the initial SHM buffer. */
					FTruncate(result->s_fd_shm, shm_size);
					result->s_fd_shm_size = shm_size;

					/* Create the initial SHM mapping. */
					shm_base = (byte_t *)MMap(NULL, shm_size, PROT_READ | PROT_WRITE,
					                          MAP_SHARED | MAP_FILE, result->s_fd_shm,
					                          0);

					/* Fill in the mapping location for the initial SHM region. */
					shm->ssh_base = shm_base;
					shm->ssh_endp = shm_base + shm_size;

					/* Register everything about the SHM control header as free memory. */
					allfree           = (struct service_shm_free *)shm->ssh_shm->s_data;
					allfree->ssf_size = (shm_size - offsetof(struct service_shm, s_data)) |
					                    SERVICE_SHM_FREE_REDBIT; /* Singular leaf is always red */
					allfree->ssf_node.rb_lhs = NULL;
					allfree->ssf_node.rb_rhs = NULL;
					result->s_shm_freetree = allfree;

					bucket = SERVICE_FREE_LIST_INDEX(shm_size);
					allfree->ssf_bysize.le_prev = &result->s_shm_freelist[bucket].lh_first;
					allfree->ssf_bysize.le_next = NULL;
					result->s_shm_freelist[bucket].lh_first = allfree;
				} EXCEPT {
					close(result->s_fd_shm);
					RETHROW();
				}
			} EXCEPT {
				close(result->s_fd_srv);
				RETHROW();
			}
		} EXCEPT {
			service_shm_handle_free(shm);
			RETHROW();
		}
	} EXCEPT {
		free(result);
		RETHROW();
	}
	return result;
}


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
INTERN WUNUSED NONNULL((1)) struct service *
NOTHROW_RPC(CC libservice_open_nx)(char const *filename) {
	TRY {
		return libservice_open(filename);
	} EXCEPT {
		error_class_t cls = error_class();
		if (ERRORCLASS_ISRTLPRIORITY(cls))
			RETHROW();
		errno = error_as_errno(error_data());
	}
	return NULL;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(CC destroy_shm_handle)(struct service_shm_handle *__restrict self) {
	struct service_shm_handle *lhs, *rhs;
again:
	lhs = self->ssh_tree_lhs;
	rhs = self->ssh_tree_rhs;

	/* Unmap this SHM mapping. */
	munmap(self->ssh_base, service_shm_handle_getsize(self));

	/* Free the handle descriptor itself. */
	service_shm_handle_free_nopr(self);
	if (lhs) {
		if (rhs)
			destroy_shm_handle(rhs);
		self = lhs;
		goto again;
	}
	if (rhs) {
		self = rhs;
		goto again;
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(CC unmap_text_range_list)(struct service_text_range_slist *__restrict self) {
	struct service_text_range *iter;
	SLIST_FOREACH_SAFE (iter, self, str_link) {
		munmap(iter, iter->str_size);
	}
}

__LIBC void __LIBCCALL __deregister_frame(void *begin);

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(CC unregister_text_range_list)(struct service_text_range_slist *__restrict self) {
	struct service_text_range *iter;
	SLIST_FOREACH (iter, self, str_link) {
		__deregister_frame(iter->str_data);
	}
}

/* Close/detach a given service. WARNING: After this function was called,
 * all function pointers  returned by `service_dlsym()'  will point  into
 * the void /  into unmapped memory.  As such, it  is up to  the user  to
 * ensure that no part  of the process  is still using  a service at  the
 * time of it being closed.
 * Services not closed when the calling process exits, or makes a call
 * to one  of the  `exec()' functions  will be  closed  automatically. */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(CC libservice_close)(struct service *__restrict self) {
	size_t i;

	/* Destroy all SHM handles. */
	destroy_shm_handle(self->s_shm);

	/* Close internal file descriptors. */
	close(self->s_fd_srv);
	close(self->s_fd_shm);

	/* Free Function descriptor */
	for (i = 0; i < self->s_funcc; ++i)
		free(self->s_funcv[i]);
	free(self->s_funcv);

	/* Unregister unwind information */
	unregister_text_range_list(&self->s_ehranges);

	/* Free .text/.eh_frame buffers */
	unmap_text_range_list(&self->s_txranges);
	unmap_text_range_list(&self->s_ehranges);

	/* Free the main control structure. */
	free(self);
}


/* The heart-piece of all of libservice:  lookup a symbol exported by  the
 * given service `self', dynamically generate a callback wrapper function,
 * and finally return the address of said wrapper function which can  then
 * be called like any other C-function (using `CC' calling
 * convention, which is guarantied to be the default calling convention
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
INTERN WUNUSED NONNULL((1, 2)) void *
NOTHROW_RPC(CC libservice_dlsym_nx)(struct service *__restrict self,
                                    char const *__restrict symname) {
	void *result;
	TRY {
		result = libservice_dlsym_lookup_or_create(self, symname, SERVICE_FUNCTION_ENTRY_KIND_NORMAL);
	} EXCEPT {
		error_class_t cls = error_class();
		if (ERRORCLASS_ISRTLPRIORITY(cls))
			RETHROW();
		errno  = error_as_errno(error_data());
		result = NULL;
	}
	return result;
}

INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) void *CC
libservice_dlsym(struct service *__restrict self, char const *__restrict symname)
		THROWS(E_NO_SUCH_OBJECT, E_BADALLOC, E_INTERRUPT) {
	void *result;
	result = libservice_dlsym_lookup_or_create(self, symname, SERVICE_FUNCTION_ENTRY_KIND_EXCEPT);
	return result;
}






INTERN NOBLOCK NONNULL((1)) void
NOTHROW(CC libservice_buffer_free)(struct service *__restrict self,
                                   void *ptr) {
	struct service_shm_handle *shm;
	pflag_t was;
	if (!ptr)
		return;
	was = PREEMPTION_PUSHOFF();
	shm = libservice_shm_handle_ataddr_nopr(self, ptr);
	assertf(shm, "service_buffer_free(%p): Invalid pointer", ptr);
	libservice_shmbuf_free_nopr(self, shm, ptr);
	PREEMPTION_POP(was);
}


/* Returns the usable size of the given `ptr'. */
INTERN NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW(CC libservice_buffer_malloc_usable_size)(struct service *__restrict self,
                                                 void *ptr) {
	(void)self;
	if (!ptr)
		return 0;
	return libservice_shmbuf_get_usable_size(ptr);
}

#ifndef __INTELLISENSE__
DECL_END
#include "client-impl.c.inl"
#define LOCAL_DEFINE_NOEXCEPT
#include "client-impl.c.inl"
DECL_BEGIN
#endif /* !__INTELLISENSE__ */






/* Exports */
DEFINE_PUBLIC_ALIAS(service_open, libservice_open_nx);
DEFINE_PUBLIC_ALIAS(service_close, libservice_close);
DEFINE_PUBLIC_ALIAS(service_dlsym, libservice_dlsym_nx);
DEFINE_PUBLIC_ALIAS(service_buffer_malloc, libservice_buffer_malloc_nx);
DEFINE_PUBLIC_ALIAS(service_buffer_calloc, libservice_buffer_calloc_nx);
DEFINE_PUBLIC_ALIAS(service_buffer_realloc, libservice_buffer_realloc_nx);
DEFINE_PUBLIC_ALIAS(service_buffer_free, libservice_buffer_free);
DEFINE_PUBLIC_ALIAS(service_buffer_malloc_usable_size, libservice_buffer_malloc_usable_size);
DEFINE_PUBLIC_ALIAS(ServiceOpen, libservice_open);
DEFINE_PUBLIC_ALIAS(ServiceDlSym, libservice_dlsym);
DEFINE_PUBLIC_ALIAS(ServiceBufferMalloc, libservice_buffer_malloc);
DEFINE_PUBLIC_ALIAS(ServiceBufferCalloc, libservice_buffer_calloc);
DEFINE_PUBLIC_ALIAS(ServiceBufferRealloc, libservice_buffer_realloc);

DECL_END

#endif /* !GUARD_LIBSERVICE_CLIENT_C */
