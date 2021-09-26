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
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/host.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sync/atomic-lock.h>

#include <asm/pagesize.h>
#include <kos/except.h>
#include <kos/futex.h>
#include <kos/kernel/types.h>
#include <kos/refcnt.h>
#include <kos/sys/mman.h>
#include <kos/types.h>
#include <sys/mman.h>
#include <sys/param.h>

#include <assert.h>
#include <inttypes.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

#if !defined(PAGESIZE) && defined(__ARCH_PAGESIZE)
#define PAGESIZE __ARCH_PAGESIZE
#endif /* !PAGESIZE && __ARCH_PAGESIZE */

/* SHM-HANDLE slabs look as follows:
 * >> struct sh_slab {
 * >>     struct sh_slab *ss_next;
 * >> };
 */

struct sh_slab {
	SLIST_ENTRY(sh_slab)               ss_link;  /* [lock(!PREEMPTION && sh_slab_lock)] Link in list of non-fully-allocated slabs. */
	COMPILER_FLEXIBLE_ARRAY(uintptr_t, ss_used); /* [lock(!PREEMPTION && sh_slab_lock)][sh_slab_used_count] Bitset of used entries. */
/*	struct service_shm_handle          ss_hand[]; * [sh_slab_hand_count] Array of handles. */
	/* Right here, the struct is just shy of PAGESIZE */
};

/* Helper macros to calculate values relating to the above structure, based on page size */
#define _sh_slab_hand_count_upper(pagesize) (((pagesize)-offsetof(struct sh_slab, ss_used)) / sizeof(struct service_shm_handle))
#define _sh_slab_used_count(pagesize)       CEILDIV(_sh_slab_hand_count_upper(pagesize), sizeof(uintptr_t) * NBBY)
#define _sh_slab_offsetof_hand(pagesize)    (offsetof(struct sh_slab, ss_used) + _sh_slab_used_count(pagesize) * sizeof(uintptr_t))
#define _sh_slab_sizeof_hand(pagesize)      ((pagesize)-_sh_slab_offsetof_hand(pagesize))
#define _sh_slab_hand_count(pagesize)       (_sh_slab_sizeof_hand(pagesize) / sizeof(struct service_shm_handle))

/* Value for the last word of `ss_used' when all entries are in-use. */
#define _sh_slab_used_allones_lastword(pagesize) (((uintptr_t)1 << (_sh_slab_hand_count(pagesize) % (sizeof(uintptr_t) * NBBY))) - 1)

/* Determine slab values. */
#ifdef PAGESIZE
enum {
	v_sh_slab_pagesize      = PAGESIZE,
	v_sh_slab_used_count    = _sh_slab_used_count(PAGESIZE),
	v_sh_slab_offsetof_hand = _sh_slab_offsetof_hand(PAGESIZE),
	v_sh_slab_hand_count    = _sh_slab_hand_count(PAGESIZE),
};
#define sh_slab_pagesize              ((size_t)v_sh_slab_pagesize)
#define sh_slab_used_count            ((size_t)v_sh_slab_used_count)
#define sh_slab_offsetof_hand         ((size_t)v_sh_slab_offsetof_hand)
#define sh_slab_hand_count            ((size_t)v_sh_slab_hand_count)
#define sh_slab_used_allones_lastword _sh_slab_used_allones_lastword(PAGESIZE)
#define sh_slab_init()                (void)0
#else /* PAGESIZE */
PRIVATE size_t sh_slab_pagesize                 = 0;
PRIVATE size_t sh_slab_used_count               = 0;
PRIVATE size_t sh_slab_offsetof_hand            = 0;
PRIVATE size_t sh_slab_hand_count               = 0;
PRIVATE uintptr_t sh_slab_used_allones_lastword = 0;
#define sh_slab_init() (void)(sh_slab_used_allones_lastword || (_sh_slab_init(), 0))
PRIVATE NOBLOCK void NOTHROW(FCALL _sh_slab_init)(void) {
	size_t pagesize       = getpagesize();
	sh_slab_pagesize      = pagesize;
	sh_slab_used_count    = _sh_slab_hand_count(pagesize);
	sh_slab_offsetof_hand = _sh_slab_sizeof_hand(pagesize);
	sh_slab_hand_count    = _sh_slab_used_count(pagesize);
	assertf(sh_slab_hand_count >= 1, "Page size (%" PRIuSIZ ") is _this_ small?", pagesize);
	COMPILER_WRITE_BARRIER();
	sh_slab_used_allones_lastword = _sh_slab_used_allones_lastword(pagesize);
	COMPILER_WRITE_BARRIER();
}
#endif /* !PAGESIZE */

/* Return the slab associated with a given pointer */
#define sh_slab_of(ptr) ((struct sh_slab *)((uintptr_t)(ptr) & ~(sh_slab_pagesize - 1)))

/* Return a pointer to `self->ss_hand' */
#define sh_slab_hand(self) ((struct service_shm_handle *)((byte_t *)(self) + sh_slab_offsetof_hand))


/* Check if the given slab is fully allocated. */
PRIVATE NOBLOCK NOPREEMPT ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL sh_slab_isfull)(struct sh_slab const *__restrict self) {
	unsigned int index;
	uintptr_t word;
	for (index = 0; index < sh_slab_used_count - 1; ++index) {
		word = self->ss_used[index];
		if (word != (uintptr_t)-1)
			return false;
	}
	/* Check the last word. */
	word = self->ss_used[index];
	return word >= sh_slab_used_allones_lastword;
}

/* Check if the given slab is empty. */
PRIVATE NOBLOCK NOPREEMPT ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL sh_slab_isempty)(struct sh_slab const *__restrict self) {
	unsigned int index;
	uintptr_t word;
	for (index = 0; index < sh_slab_used_count - 1; ++index) {
		word = self->ss_used[index];
		if (word != 0)
			return false;
	}
	/* Check the last word. */
	word = self->ss_used[index];
	if (word & sh_slab_used_allones_lastword)
		return false;
	return true;
}

SLIST_HEAD(sh_slab_slist, sh_slab);

/* [0..n][lock(sh_slab_lock)] List of non-fully-allocated slabs. */
PRIVATE struct sh_slab_slist sh_slab_list = SLIST_HEAD_INITIALIZER(sh_slab_list);

/* Lock for accessing the slab sub-system. */
PRIVATE struct atomic_lock sh_slab_lock = ATOMIC_LOCK_INIT;

PRIVATE NOBLOCK NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1)) struct service_shm_handle *
NOTHROW(FCALL sh_slab_allocate_from_non_full)(struct sh_slab *__restrict self) {
	unsigned int index, addend;
	uintptr_t word, mask;
	for (index = 0; index < sh_slab_used_count - 1; ++index) {
		word = self->ss_used[index];
		if (word != (uintptr_t)-1)
			goto allocate_from_word;
	}
	/* Check the last word. */
	word = self->ss_used[index];
	assertf(word < sh_slab_used_allones_lastword,
	        "But this one is fully allocated?");
allocate_from_word:
	addend = 0;
	mask   = 1;
	while (word & mask) {
		++addend;
		mask <<= 1;
	}
	self->ss_used[index] = word | mask;
	index *= sizeof(uintptr_t) * NBBY;
	index += addend;
	return &sh_slab_hand(self)[index];
}

/* Allocate a handle from the global slab
 * cache, or return `NULL' if doing so failed. */
PRIVATE NOBLOCK NOPREEMPT WUNUSED struct service_shm_handle *
NOTHROW(FCALL sh_slab_g_alloc_nopr)(void) {
	struct sh_slab *slab;
	struct service_shm_handle *result = NULL;
	atomic_lock_acquire_nopr(&sh_slab_lock);
	slab = SLIST_FIRST(&sh_slab_list);
	if (slab != NULL) {
		result = sh_slab_allocate_from_non_full(slab);
		/* Check for special case: when the slab got fully allocated,
		 * then we must remove it from the non-fullly-allocated list. */
		if unlikely(sh_slab_isfull(slab))
			SLIST_REMOVE_HEAD(&sh_slab_list, ss_link);
	}
	atomic_lock_release(&sh_slab_lock);
	return result;
}

PRIVATE NOBLOCK NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1)) struct service_shm_handle *
NOTHROW(FCALL sh_slab_g_alloc_with_new_page_nopr)(void *page) {
	struct sh_slab *slab;
	struct service_shm_handle *result = NULL;
	atomic_lock_acquire_nopr(&sh_slab_lock);
	slab = SLIST_FIRST(&sh_slab_list);
	if likely(slab == NULL) {
		/* Initialize the new caller-given page. */
		slab = (struct sh_slab *)page;

		/* Mark all items as free. */
		memsetc(slab->ss_used, 0, sh_slab_used_count, sizeof(uintptr_t));
		assert(sh_slab_isempty(slab));

		/* Allocate the first item. */
		slab->ss_used[0] |= 1;
		result = &sh_slab_hand(slab)[0];
		assert(!sh_slab_isempty(slab));

		/* Insert into the list of non-full slabs. */
		if unlikely(sh_slab_hand_count == 1) {
			assert(sh_slab_isfull(slab));
		} else {
			assert(!sh_slab_isfull(slab));
			SLIST_INSERT(&sh_slab_list, slab, ss_link);
		}
		atomic_lock_release(&sh_slab_lock);
	} else {
		/* Someone else allocated more in the mean time. */
		result = sh_slab_allocate_from_non_full(slab);
		if unlikely(sh_slab_isfull(slab))
			SLIST_REMOVE_HEAD(&sh_slab_list, ss_link);
		atomic_lock_release(&sh_slab_lock);
		/* Don't need the new caller-given page. */
		munmap(page, sh_slab_pagesize);
	}
	return result;
}







/* Allocate a new SHM handle. Note that these functions are non-blocking
 * because  they make use of a custom slab-style allocator. They're also
 * reentrance-safe because they must be called with preemption disabled. */
INTERN NOBLOCK NOPREEMPT ATTR_RETNONNULL WUNUSED struct service_shm_handle *FCALL
service_shm_handle_alloc_nopr(void) THROWS(E_BADALLOC) {
	struct service_shm_handle *result;
	result = sh_slab_g_alloc_nopr();
	if (result == NULL) {
		void *page;
		sh_slab_init();
		page   = MMap(NULL, sh_slab_pagesize, PROT_READ | PROT_WRITE, MAP_ANON, -1, 0);
		result = sh_slab_g_alloc_with_new_page_nopr(page);
	}
	return result;
}

INTERN NOBLOCK NOPREEMPT WUNUSED struct service_shm_handle *
NOTHROW(FCALL service_shm_handle_alloc_nopr_nx)(void) {
	struct service_shm_handle *result;
	result = sh_slab_g_alloc_nopr();
	if (result == NULL) {
		void *page;
		sh_slab_init();
		page = mmap(NULL, sh_slab_pagesize, PROT_READ | PROT_WRITE, MAP_ANON, -1, 0);
		if (page != MAP_FAILED)
			result = sh_slab_g_alloc_with_new_page_nopr(page);
	}
	return result;
}


INTERN NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL service_shm_handle_free_nopr)(struct service_shm_handle *__restrict self) {
	struct sh_slab *slab;
	unsigned int index, i, shift;
	slab  = sh_slab_of(self);
	index = (unsigned int)(self - sh_slab_hand(slab));
	assertf(&sh_slab_hand(slab)[index] == self,
	        "Unaligned pointer %p", self);
	i     = index / (sizeof(uintptr_t) * NBBY);
	shift = index % (sizeof(uintptr_t) * NBBY);
	assertf(slab->ss_used[i] & ((uintptr_t)1 << shift),
	        "Pointer at %p already marked as free", self);
	atomic_lock_acquire_nopr(&sh_slab_lock);
	/* Special case: if the slab was full, then we must add it to the non-full list. */
	if (sh_slab_isfull(slab)) {
		slab->ss_used[i] &= ~((uintptr_t)1 << shift);
		SLIST_INSERT(&sh_slab_list, slab, ss_link);
	} else {
		slab->ss_used[i] &= ~((uintptr_t)1 << shift);
	}
	if (sh_slab_isempty(slab)) {
		/* Special case: the slab became empty.
		 * Remove from the non-full list and munmap() it. */
		SLIST_REMOVE(&sh_slab_list, slab, ss_link);
		atomic_lock_release(&sh_slab_lock);
		munmap(slab, sh_slab_pagesize);
		return;
	}
	atomic_lock_release(&sh_slab_lock);
}


PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC service_shm_handle_destroy_postlop)(Tobpostlockop(service) *__restrict self,
                                                      struct service *__restrict UNUSED(obj)) {
	struct service_shm_handle *me;
	me = container_of(self, struct service_shm_handle, ssh_plop);
	service_shm_handle_free_nopr(me);
}

PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) Tobpostlockop(service) *
NOTHROW(LOCKOP_CC service_shm_handle_destroy_lop)(Toblockop(service) *__restrict self,
                                                  struct service *__restrict obj) {
	struct service_shm_handle *me;
	me = container_of(self, struct service_shm_handle, ssh_lop);
	sshtree_removenode(&obj->s_shm_tree, me);
	me->ssh_plop.oplo_func = &service_shm_handle_destroy_postlop;
	return &me->ssh_plop;
}

/* Destroy the given handle.
 * HINT: This function uses lockops to remove `self' from `self->ssh_service->s_shm_tree'! */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL service_shm_handle_destroy)(struct service_shm_handle *__restrict self) {
	pflag_t was;
	struct service *svc;
	svc = self->ssh_service;
	was = PREEMPTION_PUSHOFF();
	if (libservice_shmlock_tryacquire_nopr(svc)) {
		sshtree_removenode(&svc->s_shm_tree, self);
		libservice_shmlock_release_nopr(svc);
		service_shm_handle_free_nopr(self);
		PREEMPTION_POP(was);
		return;
	}
	/* Enqueue a lockop to remove `self' from `svc->s_shm_tree' */
	self->ssh_lop.olo_func = &service_shm_handle_destroy_lop;
	oblockop_enqueue(&svc->s_shm_lops, &self->ssh_lop);
	libservice_shmlock_reap_nopr(svc);
	PREEMPTION_POP(was);
}


/* Lookup a function exported by the service, and if not already loaded, ask the
 * server for information about the function  before creating a wrapper for  it,
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


/* Abort the given command by trying to CMPXCH the command code of  `com'
 * from `orig_code' to `SERVICE_COM_NOOP', before sending an interrupt to
 * the  server and forcing  the thread currently  serving this command to
 * restart (at which point the NOOP will be able to complete without  any
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
