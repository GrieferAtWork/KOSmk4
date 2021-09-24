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
#ifndef GUARD_LIBSERVICE_COM_C
#define GUARD_LIBSERVICE_COM_C 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/host.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sync/atomic-lock.h>

#include <kos/except.h>
#include <kos/futex.h>
#include <kos/kernel/types.h>
#include <kos/refcnt.h>
#include <kos/types.h>

#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdlib.h>

#include <libc/signal.h>
#include <libservice/bits/com.h>
#include <libservice/types.h>

#include "com.h"


/* R/B-tree ABI for `struct service_shm_handle' */

#define RBTREE_LEFT_LEANING
#define RBTREE_OMIT_REMOVE
#define RBTREE_DECL                PRIVATE
#define RBTREE_IMPL                PRIVATE
#define RBTREE(name)               sshtree_##name
#define RBTREE_T                   struct service_shm_handle
#define RBTREE_Tkey                void const *
#define RBTREE_CC                  FCALL
#define RBTREE_NOTHROW             NOTHROW
#define RBTREE_GETLHS(self)        (self)->ssh_tree_lhs
#define RBTREE_GETRHS(self)        (self)->ssh_tree_rhs
#define RBTREE_SETLHS(self, v)     (void)((self)->ssh_tree_lhs = (v))
#define RBTREE_SETRHS(self, v)     (void)((self)->ssh_tree_rhs = (v))
#define RBTREE_ISRED(self)         ((self)->ssh_tree_red)
#define RBTREE_SETRED(self)        (void)((self)->ssh_tree_red = 1)
#define RBTREE_SETBLACK(self)      (void)((self)->ssh_tree_red = 0)
#define RBTREE_FLIPCOLOR(self)     (void)((self)->ssh_tree_red ^= (uintptr_t)-1)
#define RBTREE_COPYCOLOR(dst, src) (void)((dst)->ssh_tree_red = (src)->ssh_tree_red)
#define RBTREE_GETMINKEY(node)     ((byte_t *)(node)->ssh_shm)
#define RBTREE_GETMAXKEY(node)     ((byte_t *)(node)->ssh_endp - 1)
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN


/* Destroy the given handle.
 * HINT: This function uses lockops to remove `self' from `self->ssh_service->s_shm_tree'! */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL service_shm_handle_destroy)(struct service_shm_handle *__restrict self) {
	/* TODO */
	(void)self;
	abort();
}


/* Reap lock operations of `self->s_shmlock_lop' */
INTERN NOBLOCK WUNUSED NONNULL((1)) void
NOTHROW(CC _libservice_shmlock_reap)(struct service *__restrict self) {
	/* TODO */
	(void)self;
	abort();
}


/* Lookup a function exported by the service, and if not already loaded, ask the
 * server for information about the function before creating a wrapper for it,
 * which is then cached before also being returned. */
INTERN WUNUSED NONNULL((1, 2)) void *CC
libservice_dlsym_lookup_or_create(struct service *__restrict self,
                                  char const *__restrict name,
                                  bool uses_exceptions)
		THROWS(E_NO_SUCH_OBJECT, E_BADALLOC, E_INTERRUPT) {
	/* TODO */
	(void)self;
	(void)name;
	(void)uses_exceptions;
	abort();
}

/* Ask the server for information about the function `name', and store it in `*info' */
INTERN NONNULL((1, 2, 3)) void CC
libservice_dlsym_getinfo(struct service *__restrict self, char const *__restrict name,
                         /*out*/ struct service_com_funinfo *__restrict info)
		THROWS(E_NO_SUCH_OBJECT, E_BADALLOC, E_INTERRUPT) {
	/* TODO */
	(void)self;
	(void)name;
	(void)info;
	abort();
}


/* Abort the given command by trying to CMPXCH the command code of `com'
 * from `orig_code' to `SERVICE_COM_NOOP', before sending an interrupt to
 * the server and forcing the thread currently serving this command to
 * restart (at which point the NOOP will be able to complete without any
 * further blocking)
 * This function then waits until the operation stops blocking doing that,
 * and only returns once it is safe to deallocate `com'
 * @return: true:  The command was aborted.
 * @return: false: The command complete before it could be aborted. */
INTERN WUNUSED NONNULL((1, 2)) bool
NOTHROW(FCALL libservice_aux_com_abort)(struct service *__restrict self,
                                        struct service_com *__restrict com,
                                        uintptr_t orig_code) {
	/* TODO */
	(void)self;
	(void)com;
	(void)orig_code;
	abort();
}





/* Return the SHM base address of the region that contains
 * `addr'. If no  such SHM region  exists, return  `NULL'. */
INTERN NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) struct service_shm_handle *
NOTHROW(FCALL libservice_shm_handle_ataddr_nopr)(struct service *__restrict self,
                                                 void const *addr) {
	struct service_shm_handle *result;
	libservice_shmlock_acquire_nopr(self);
	result = sshtree_locate(self->s_shm_tree, addr);
	libservice_shmlock_release_nopr(self);
	return result;
}



/* Try to allocate at least  `num_bytes' at `shm', returning  the
 * number of actually allocated bytes  on success, or `0' if  the
 * allocation was impossible because the target address range  is
 * already allocated, or attempting to mmap it failed. Note  that
 * this function doesn't impose any restrictions on minimal alloc
 * size,  and that it _will_ allocate less than the usual minimum
 * of `SERVICE_SHM_ALLOC_MINSIZE' (if possible), meaning that the
 * caller  is responsible to only call this function if they will
 * follow-up by merging the  resulting region with a  neighboring
 * previously-allocated buffer!
 *
 * This function is simply used to implement `service_buffer_realloc'. */
INTERN NOBLOCK NOPREEMPT WUNUSED NONNULL((1, 3)) size_t
NOTHROW(FCALL libservice_shmbuf_allocat_nopr)(struct service *__restrict self,
                                              struct service_shm_handle *__restrict shm,
                                              void *ptr, size_t num_bytes) {
	/* TODO */
	(void)self;
	(void)shm;
	(void)ptr;
	(void)num_bytes;
	abort();
}


/* Mark the given buffer range as free.
 * @assume(num_bytes >= SERVICE_SHM_ALLOC_MINSIZE);
 * @assume(IS_ALIGNED(ptr, SERVICE_SHM_ALLOC_ALIGN));
 * @assume(shm == libservice_shm_handle_ataddr_nopr(self, ptr)); */
INTERN NOBLOCK NOPREEMPT NONNULL((1, 3)) void
NOTHROW(FCALL libservice_shmbuf_freeat_nopr)(struct service *__restrict self,
                                             REF struct service_shm_handle *__restrict shm,
                                             void *ptr, size_t num_bytes) {
	assert(num_bytes >= SERVICE_SHM_ALLOC_MINSIZE);
	assert(IS_ALIGNED((uintptr_t)ptr, SERVICE_SHM_ALLOC_ALIGN));
	assert(shm == libservice_shm_handle_ataddr_nopr(self, ptr));


	/* TODO */
	(void)self;
	(void)shm;
	(void)ptr;
	(void)num_bytes;
	abort();
}


DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_libservice_shmbuf_alloc_nopr
#include "com-shmbuf-alloc.c.inl"
#define DEFINE_libservice_shmbuf_alloc_nopr_nx
#include "com-shmbuf-alloc.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_LIBSERVICE_COM_C */
