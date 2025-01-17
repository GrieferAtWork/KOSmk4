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
#ifndef GUARD_LIBSERVICE_COM_C
#define GUARD_LIBSERVICE_COM_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/align.h>
#include <hybrid/host.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>
#include <hybrid/sched/atomic-lock.h>
#include <hybrid/sched/preemption.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>

#include <asm/pagesize.h>
#include <kos/except.h>
#include <kos/futex.h>
#include <kos/kernel/types.h>
#include <kos/malloc.h>
#include <kos/refcnt.h>
#include <kos/sys/mman.h>
#include <kos/syscalls.h>
#include <kos/types.h>
#include <kos/unistd.h>
#include <sys/mman.h>
#include <sys/param.h>

#include <assert.h>
#include <atomic.h>
#include <errno.h>
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

#if defined(__i386__) || defined(__x86_64__)
#include "arch/i386/wrapper.h"
#else /* ... */
#error "Unsupported architecture"
#endif /* !... */


/* R/B-tree ABI for `struct service_shm_handle' */
#define RBTREE_LEFT_LEANING
#define RBTREE_OMIT_REMOVE
#define RBTREE_DECL            PRIVATE
#define RBTREE_IMPL            PRIVATE
#define RBTREE(name)           sshtree_##name
#define RBTREE_T               struct service_shm_handle
#define RBTREE_Tkey            void const *
#define RBTREE_CC              FCALL
#define RBTREE_NOTHROW         NOTHROW
#define RBTREE_GETLHS(self)    (self)->ssh_tree_lhs
#define RBTREE_GETRHS(self)    (self)->ssh_tree_rhs
#define RBTREE_SETLHS(self, v) (void)((self)->ssh_tree_lhs = (v))
#define RBTREE_SETRHS(self, v) (void)((self)->ssh_tree_rhs = (v))
#define RBTREE_REDFIELD        ssh_tree_red
#define RBTREE_GETMINKEY(node) ((byte_t *)(node)->ssh_shm)
#define RBTREE_GETMAXKEY(node) ((byte_t *)(node)->ssh_endp - 1)
#include <hybrid/sequence/rbtree-abi.h>

/* R/B-tree ABI for `struct service_shm_free' */
#define RBTREE_LEFT_LEANING
#define RBTREE_DECL          PRIVATE
#define RBTREE_IMPL          PRIVATE
#define RBTREE(name)         sf_##name
#define RBTREE_T             struct service_shm_free
#define RBTREE_Tkey          void const *
#define RBTREE_CC            FCALL
#define RBTREE_NOTHROW       NOTHROW
#define RBTREE_GETNODE(self) (self)->ssf_node
#define RBTREE_REDFIELD      ssf_size
#define RBTREE_REDBIT        SERVICE_SHM_FREE_REDBIT
#define RBTREE_GETMINKEY     service_shm_free_getminaddr
#define RBTREE_GETMAXKEY     service_shm_free_getmaxaddr
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

/* Allocate a  handle  from  the  global  slab
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
		page = mmap(NULL, sh_slab_pagesize, PROT_READ | PROT_WRITE,
		            MAP_PRIVATE | MAP_ANON, -1, 0);
		if (page != MAP_FAILED)
			result = sh_slab_g_alloc_with_new_page_nopr(page);
	}
	return result;
}


INTERN NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL service_shm_handle_free_nopr)(struct service_shm_handle *__restrict self) {
	struct sh_slab *slab;
	unsigned int index, i;
	shift_t shift;
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

INTERN NOBLOCK ATTR_RETNONNULL WUNUSED struct service_shm_handle *FCALL
service_shm_handle_alloc(void) THROWS(E_BADALLOC) {
	preemption_flag_t was;
	struct service_shm_handle *result;
	preemption_pushoff(&was);
	RAII_FINALLY { preemption_pop(&was); };
	result = service_shm_handle_alloc_nopr();
	return result;
}

INTDEF NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL service_shm_handle_free)(struct service_shm_handle *__restrict self) {
	preemption_flag_t was;
	preemption_pushoff(&was);
	service_shm_handle_free_nopr(self);
	preemption_pop(&was);
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
	preemption_flag_t was;
	struct service *svc;
	svc = self->ssh_service;
	preemption_pushoff(&was);
	if (libservice_shmlock_tryacquire_nopr(svc)) {
		sshtree_removenode(&svc->s_shm_tree, self);
		libservice_shmlock_release_nopr(svc);
		service_shm_handle_free_nopr(self);
		preemption_pop(&was);
		return;
	}
	/* Enqueue a lockop to remove `self' from `svc->s_shm_tree' */
	self->ssh_lop.olo_func = &service_shm_handle_destroy_lop;
	oblockop_enqueue(&svc->s_shm_lops, &self->ssh_lop);
	libservice_shmlock_reap_nopr(svc);
	preemption_pop(&was);
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



/* Insert the given free-range into `self'. Only `range->ssf_size'
 * needs  to have been initialized by the caller. All other fields
 * are initialized by this function.
 * @return: * : The area containing `range' (which may have been merged) */
PRIVATE NOBLOCK NOPREEMPT ATTR_RETNONNULL NONNULL((1, 2)) struct service_shm_free *
NOTHROW(FCALL service_insert_freerange)(struct service *__restrict self,
                                        struct service_shm_free *__restrict range) {
	struct service_shm_free_list *freelist;
	struct service_shm_free *neighbor;
again:
	/* Check if we can merge the range with adjacent ranges. */
	neighbor = sf_remove(&self->s_shm_freetree, service_shm_free_getminaddr(range) - 1);
	if (neighbor) {
		LIST_REMOVE(neighbor, ssf_bysize);
		neighbor->ssf_size = service_shm_free_getsize(neighbor) +
		                     service_shm_free_getsize(range);
		range = neighbor;
		goto again;
	}
	neighbor = sf_remove(&self->s_shm_freetree, service_shm_free_getmaxaddr(range) + 1);
	if (neighbor) {
		LIST_REMOVE(neighbor, ssf_bysize);
		range->ssf_size = service_shm_free_getsize(range) +
		                  service_shm_free_getsize(neighbor);
		goto again;
	}

	/* Insert into the free-tree. */
	sf_insert(&self->s_shm_freetree, range);

	/* Insert into the proper free-list */
	freelist = &self->s_shm_freelist[SERVICE_FREE_LIST_INDEX(service_shm_free_getsize(range))];
	LIST_INSERT_HEAD(freelist, range, ssf_bysize);
	return range;
}

/* Insert a free area  into `self'. The caller  must ensure that conformance  to
 * `SERVICE_SHM_ALLOC_*'. Returns the range which contains `base...+=num_bytes'. */
PRIVATE NOBLOCK NOPREEMPT ATTR_RETNONNULL NONNULL((1, 2)) struct service_shm_free *
NOTHROW(FCALL service_insert_freearea)(struct service *__restrict self,
                                       void *__restrict base, size_t num_bytes) {
	struct service_shm_free *range;
	assert(IS_ALIGNED((uintptr_t)base, SERVICE_SHM_ALLOC_ALIGN));
	assert(num_bytes >= SERVICE_SHM_ALLOC_MINSIZE);
	range = (struct service_shm_free *)base;
	range->ssf_size = num_bytes;
	return service_insert_freerange(self, range);
}


PRIVATE NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL reloc_free_tree)(struct service_shm_free **__restrict pself,
                               uintptr_t disp) {
	struct service_shm_free *self;
	assert(*pself);
again:
	*(byte_t **)pself += disp;
	self = *pself;
	if (self->ssf_node.rb_lhs) {
		if (self->ssf_node.rb_rhs)
			reloc_free_tree(&self->ssf_node.rb_rhs, disp);
		pself = &self->ssf_node.rb_lhs;
		goto again;
	}
	if (self->ssf_node.rb_rhs) {
		pself = &self->ssf_node.rb_rhs;
		goto again;
	}
}

PRIVATE NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL reloc_free_list)(struct service_shm_free_list *__restrict self,
                               uintptr_t disp) {
	struct service_shm_free **piter, *iter;
	piter = LIST_PFIRST(self);
	while (*piter) {
		*(byte_t **)piter += disp;
		iter = *piter;
		iter->ssf_bysize.le_prev = piter;
		piter = &iter->ssf_bysize.le_next;
	}
	/* Fix the back-link of the first list element. */
	iter = LIST_FIRST(self);
	if (iter != NULL)
		iter->ssf_bysize.le_prev = LIST_PFIRST(self);
}


/* Assign the used SHM handle, inheriting the given reference and
 * dropping  a reference from the old handle, as well as relocate
 * all pointers into SHM memory to make use of the area described
 * by the given `handle'.
 * This function will initialize:
 *   - handle->ssh_tree_lhs
 *   - handle->ssh_tree_rhs
 *   - handle->ssh_tree_red */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL service_set_shm)(struct service *__restrict self,
                               REF struct service_shm_handle *__restrict handle) {
	unsigned int i;
	REF struct service_shm_handle *oldhand;
	uintptr_t disp;

	/* Assign the new handle. */
	oldhand     = self->s_shm;
	self->s_shm = handle;

	/* Insert the new handle into the handle tree. */
	sshtree_insert(&self->s_shm_tree, handle);

	/* Calculate the relocation disposition. */
	disp = (uintptr_t)(handle->ssh_base - oldhand->ssh_base);

	/* Relocate control structures. */
	reloc_free_tree(&self->s_shm_freetree, disp);
	for (i = 0; i < SERVICE_FREE_LIST_COUNT; ++i)
		reloc_free_list(&self->s_shm_freelist[i], disp);

	decref(oldhand);
}


/* Increase  the size of the backing file and  assign a new mapping. If at the
 * point  where the new mapping is assigned  the current mapping is already at
 * least as large as `newsize', discard the new mapping and don't do anything. */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1)) bool FCALL
service_shmbuf_increase_file_size_locked_nopr(struct service *__restrict self,
                                              size_t newsize, bool nx) {
	struct service_shm_handle *newhand;
	void *newbase;
	size_t pagesize = getpagesize();
	size_t extension_size;
	byte_t *extension_base;
	pos_t extension_fpos;
	assert(newsize > self->s_fd_shm_size);
	assert(IS_ALIGNED(newsize, pagesize));
	assert(IS_ALIGNED(self->s_fd_shm_size, pagesize));
	if (nx) {
		if (ftruncate(self->s_fd_shm, newsize) != 0)
			goto fail;
	} else {
		FTruncate(self->s_fd_shm, newsize);
	}

	/* Try to extend the current SHM mapping. */
	assert(service_shm_handle_getsize(self->s_shm) == self->s_fd_shm_size);
	extension_base = self->s_shm->ssh_endp;
	extension_size = newsize - self->s_fd_shm_size;
	extension_fpos = self->s_fd_shm_size;
	if (mmap(extension_base, extension_size, PROT_READ | PROT_WRITE,
	         MAP_SHARED | MAP_FIXED | MAP_FIXED_NOREPLACE | MAP_FILE,
	         self->s_fd_shm, extension_fpos) != MAP_FAILED) {
		/* Successfully inline-increased the current SHM mapping size. */
		atomic_write(&self->s_shm->ssh_endp,
		             self->s_shm->ssh_endp + extension_size);
		self->s_fd_shm_size += extension_size;
		return true;
	}

	/* Must create a new SHM mapping. */
	if (nx) {
		newhand = service_shm_handle_alloc_nopr_nx();
		if unlikely(!newhand)
			goto fail;
	} else {
		newhand = service_shm_handle_alloc_nopr();
	}

	/* Create the mapping for the new SHM */
	if (nx) {
		newbase = mmap(NULL, newsize, PROT_READ | PROT_WRITE,
		               MAP_SHARED | MAP_FILE, self->s_fd_shm, 0);
		if unlikely(newbase == MAP_FAILED) {
			service_shm_handle_free_nopr(newhand);
			goto fail;
		}
	} else {
		TRY {
			newbase = MMap(NULL, newsize, PROT_READ | PROT_WRITE,
			               MAP_SHARED | MAP_FILE, self->s_fd_shm, 0);
		} EXCEPT {
			service_shm_handle_free_nopr(newhand);
			RETHROW();
		}
	}

	/* Initialize the new handle. */
	newhand->ssh_refcnt  = 1;
	newhand->ssh_base    = (byte_t *)newbase;
	newhand->ssh_endp    = (byte_t *)newbase + newsize;
	newhand->ssh_service = self;

	/* Assign the new SHM handle. */
	service_set_shm(self, newhand);
	self->s_fd_shm_size = newsize;

	/* Create a new free range for the file size delta. */
	extension_base = newhand->ssh_base + extension_fpos;
	service_insert_freearea(self, extension_base, extension_size);
	return true;
fail:
	return false;
}


/* Try to ensure that the entirety of the given address range is allocated. */
PRIVATE NOBLOCK NOPREEMPT WUNUSED NONNULL((1, 2)) bool
NOTHROW(FCALL service_shmbuf_ensurefree_locked_nopr)(struct service *__restrict self,
                                                     void *ptr, size_t num_bytes) {
	struct service_shm_free *sf;
	size_t headsize;
	sf = sf_locate(self->s_shm_freetree, ptr);
	if (!sf) {
		size_t ptr_offset, new_file_size;
		size_t pagesize;
		ptr_offset = (size_t)((byte_t *)ptr - self->s_shm->ssh_base);
		if (ptr_offset < self->s_fd_shm_size)
			goto fail; /* Already allocated */
		/* Allocation is outside the allocated file area. */
		pagesize = getpagesize();
		if ((ptr_offset & (pagesize - 1)) < SERVICE_SHM_ALLOC_MINSIZE) {
			byte_t *pagebase;
			/* Make sure that the newly allocated page can merge with a preceding free range */
			pagebase = (byte_t *)((uintptr_t)ptr & (pagesize - 1));
			if (sf_locate(self->s_shm_freetree, pagebase) == NULL)
				goto fail;
		}
		new_file_size = ptr_offset + num_bytes;
		new_file_size = CEIL_ALIGN(new_file_size, pagesize);
		return service_shmbuf_increase_file_size_locked_nopr(self, new_file_size, true);
	}

	/* Check if the head area is large enough. */
	headsize = (size_t)((byte_t *)ptr - service_shm_free_getminaddr(sf));
	if (headsize != 0 && headsize < SERVICE_SHM_ALLOC_MINSIZE)
		goto fail;

	/* Check that the free range is large enough, and if it's not, try to
	 * increase the file size  iff the range marks  the end of the  file. */
	if ((byte_t *)ptr + num_bytes - 1 > service_shm_free_getmaxaddr(sf)) {
		byte_t *sf_endaddr;
		size_t sf_rel_endaddr, new_file_size;
		sf_endaddr     = service_shm_free_getmaxaddr(sf) + 1;
		sf_rel_endaddr = (size_t)(sf_endaddr - self->s_shm->ssh_base);
		assert(sf_rel_endaddr <= self->s_fd_shm_size);
		if (sf_rel_endaddr != self->s_fd_shm_size)
			goto fail;
		/* Increase the file size */
		new_file_size = (size_t)((byte_t *)ptr - self->s_shm->ssh_base);
		new_file_size += num_bytes;
		new_file_size = CEIL_ALIGN(new_file_size, getpagesize());
		assert(new_file_size > self->s_fd_shm_size);
		return service_shmbuf_increase_file_size_locked_nopr(self, new_file_size, true);
	}

	return true;
fail:
	return false;
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
INTERN NOBLOCK NOPREEMPT WUNUSED NONNULL((1, 2, 3)) size_t
NOTHROW(FCALL libservice_shmbuf_allocat_nopr)(struct service *__restrict self,
                                              struct service_shm_handle *__restrict shm,
                                              void *ptr, size_t num_bytes) {
	byte_t *realptr;
	struct service_shm_free *sf;
	size_t freesize;
	size_t result;
	assert(IS_ALIGNED((uintptr_t)ptr, SERVICE_SHM_ALLOC_ALIGN));
	num_bytes = CEIL_ALIGN(num_bytes, SERVICE_SHM_ALLOC_ALIGN);
	libservice_shmlock_acquire_nopr(self);
	realptr = self->s_shm->ssh_base + ((byte_t *)ptr - shm->ssh_base);
	if (!service_shmbuf_ensurefree_locked_nopr(self, realptr, num_bytes)) {
		libservice_shmlock_release_nopr(self);
		return 0;
	}
	/* The effective base may have been changed by `service_shmbuf_ensurefree()'! */
	realptr = self->s_shm->ssh_base + ((byte_t *)ptr - shm->ssh_base);
	sf      = sf_remove(&self->s_shm_freetree, realptr);
	LIST_REMOVE(sf, ssf_bysize);
	result   = service_shm_free_getsize(sf);
	freesize = (size_t)(realptr - (byte_t *)sf);
	if (freesize != 0) {
		service_insert_freearea(self, sf, freesize);
		result -= freesize;
	}
	assert(result >= num_bytes);
	freesize = result - num_bytes;
	if (freesize >= SERVICE_SHM_ALLOC_MINSIZE) {
		void *tail = realptr + num_bytes;
		service_insert_freearea(self, tail, freesize);
		result = num_bytes;
	}
	libservice_shmlock_release_nopr(self);
	return result;
}

PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL try_truncate_tail_freerange)(struct service *__restrict self,
                                           struct service_shm_free *tail) {
	if ((size_t)(service_shm_free_getmaxaddr(tail) - self->s_shm->ssh_base) == self->s_fd_shm_size) {
		size_t pagesize       = getpagesize();
		size_t free_area      = service_shm_free_getsize(tail);
		size_t trim_threshold = 8 * pagesize;
		if (free_area >= trim_threshold) {
			size_t headsize;
			byte_t *unmap_base;
			unmap_base = service_shm_free_getminaddr(tail);
			unmap_base = (byte_t *)CEIL_ALIGN((uintptr_t)unmap_base, pagesize);
			headsize   = (size_t)(unmap_base - service_shm_free_getminaddr(tail));
			if (headsize != 0 && headsize < SERVICE_SHM_ALLOC_MINSIZE) {
				headsize += pagesize;
				unmap_base += pagesize;
			}
			if (unmap_base <= service_shm_free_getmaxaddr(tail)) {
				errno_t saved_errno = errno;
				struct service_shm_handle *newhand;
				newhand = service_shm_handle_alloc_nopr_nx();
				if likely(newhand) {
					size_t newsize;
					void *newbase;
					newsize = (size_t)(unmap_base - self->s_shm->ssh_base);

					/* Create a new (truncated) mapping of SHM memory. */
					newbase = mmap(NULL, newsize, PROT_READ | PROT_WRITE,
					               MAP_SHARED | MAP_FILE, self->s_fd_shm, 0);
					if unlikely(newbase == MAP_FAILED) {
						service_shm_handle_free_nopr(newhand);
						return;
					}

					/* Initialize the new handle. */
					newhand->ssh_refcnt  = 1;
					newhand->ssh_base    = (byte_t *)newbase;
					newhand->ssh_endp    = (byte_t *)newbase + newsize;
					newhand->ssh_service = self;

					/* Update accounting. */
					sf_removenode(&self->s_shm_freetree, tail);
					LIST_REMOVE(tail, ssf_bysize);

					/* Re-insert the head area. */
					if (headsize != 0)
						service_insert_freearea(self, tail, headsize);

					/* Assign the new handle */
					service_set_shm(self, newhand);
					self->s_fd_shm_size = newsize;

					/* Free memory */
					ftruncate(self->s_fd_shm, newsize);
				}
				errno = saved_errno;
			}
		}
	}
}


/* Mark the given buffer range as free.
 * @assume(num_bytes >= SERVICE_SHM_ALLOC_MINSIZE);
 * @assume(IS_ALIGNED(ptr, SERVICE_SHM_ALLOC_ALIGN));
 * @assume(shm == libservice_shm_handle_ataddr_nopr(self, ptr)); */
INTERN NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) void
NOTHROW(FCALL libservice_shmbuf_freeat_nopr)(struct service *__restrict self,
                                             REF struct service_shm_handle *__restrict shm,
                                             void *ptr, size_t num_bytes) {
	struct service_shm_free *tail;
	assert(num_bytes >= SERVICE_SHM_ALLOC_MINSIZE);
	assert(IS_ALIGNED((uintptr_t)ptr, SERVICE_SHM_ALLOC_ALIGN));
	assert(shm == libservice_shm_handle_ataddr_nopr(self, ptr));
	libservice_shmlock_acquire_nopr(self);
	/* Convert `ptr' into the current SHM address. */
	if unlikely(self->s_shm != shm)
		ptr = self->s_shm->ssh_base + ((byte_t *)ptr - shm->ssh_base);
	/* If the last free range has grown large enough, then we truncate the SHM file. */
	tail = service_insert_freearea(self, ptr, num_bytes);
	try_truncate_tail_freerange(self, tail);
	libservice_shmlock_release_nopr(self);
	decref(shm); /* Drop the caller-given reference from `shm' */
}

/* Same as `libservice_shmbuf_freeat_nopr()', but don't try to truncate the SHM file. */
INTERN NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) void
NOTHROW(FCALL libservice_shmbuf_freeat_fast_nopr)(struct service *__restrict self,
                                                  REF struct service_shm_handle *__restrict shm,
                                                  void *ptr, size_t num_bytes) {
	assert(num_bytes >= SERVICE_SHM_ALLOC_MINSIZE);
	assert(IS_ALIGNED((uintptr_t)ptr, SERVICE_SHM_ALLOC_ALIGN));
	assert(shm == libservice_shm_handle_ataddr_nopr(self, ptr));
	libservice_shmlock_acquire_nopr(self);
	/* Convert `ptr' into the current SHM address. */
	if unlikely(self->s_shm != shm)
		ptr = self->s_shm->ssh_base + ((byte_t *)ptr - shm->ssh_base);
	service_insert_freearea(self, ptr, num_bytes);
	assert(self->s_shm_freetree != NULL);
	libservice_shmlock_release_nopr(self);
	decref(shm); /* Drop the caller-given reference from `shm' */
}



/* Search for a function entry that may be referring to `name'
 * If not found, return `NULL'. */
PRIVATE WUNUSED NONNULL((1, 2)) struct service_function_entry *
NOTHROW_NCX(CC service_dlsym_lookup)(struct service *__restrict self,
                                     char const *__restrict name)
		THROWS(E_SEGFAULT) {
	struct service_function_entry *result;
	size_t lo, hi;
	lo = 0;
	hi = self->s_funcc;
	while (lo < hi) {
		int cmp;
		size_t index;
		index  = (lo + hi) / 2;
		result = self->s_funcv[index];
		assert(result);
		cmp = strcmp(name, result->sfe_name);
		if (cmp < 0) {
			hi = index;
		} else if (cmp > 0) {
			lo = index + 1;
		} else {
			goto foundit;
		}
	}
	result = NULL;
foundit:
	return result;
}

/* Insert the given `entry' into the function vector. The caller must ensure that
 * the vector has been  resized to allow  for an additional  entry to be  fitted. */
PRIVATE NONNULL((1, 2)) void
NOTHROW_NCX(CC service_dlsym_insert)(struct service *__restrict self,
                                     struct service_function_entry *__restrict entry) {
	size_t lo, hi, index;
	lo = 0;
	hi = self->s_funcc;
	for (;;) {
		struct service_function_entry *other;
		int cmp;
		index = (lo + hi) / 2;
		if (lo >= hi)
			break;
		other = self->s_funcv[index];
		assert(other);
		cmp = strcmp(entry->sfe_name, other->sfe_name);
		if (cmp < 0) {
			hi = index;
		} else if (cmp > 0) {
			lo = index + 1;
		} else {
			break;
		}
	}
	/* Insert at `index' */
	memmoveup(&self->s_funcv[index + 1],
	          &self->s_funcv[index],
	          self->s_funcc - index,
	          sizeof(struct service_function_entry *));
	self->s_funcv[index] = entry;
	++self->s_funcc;
}


/* Try to realloc a text range  buffer. When `range' is equal  to
 * the first element of `self->s_txranges' or `self->s_ehranges',
 * then don't munmap `range' if an inplace-realloc failed. */
PRIVATE WUNUSED NONNULL((1)) struct service_text_range *CC
service_realloc_textrange(struct service *__restrict self,
                          struct service_text_range *range,
                          size_t freesize, unsigned int prot)
		THROWS(E_BADALLOC) {
	size_t pagesize = getpagesize();
	size_t newsize, moresize;
	struct service_text_range *result;
	if (!range)
		goto alloc_new_range;
	assert(freesize > range->str_free);

	/* Try to inplace increase the size of the mapping. */
	newsize  = (range->str_size - range->str_free) + freesize;
	newsize  = CEIL_ALIGN(newsize, pagesize);
	moresize = newsize - range->str_size;
	if (mmap((byte_t *)range + range->str_size, moresize, prot,
	         MAP_FILE | MAP_FIXED_NOREPLACE | MAP_PRIVATE | MAP_ANON, -1, 0) != MAP_FAILED) {
		range->str_size += moresize;
		range->str_free += moresize;
		return range;
	}

	/* Must allocate a new range. */
alloc_new_range:
	freesize         = CEIL_ALIGN(freesize, pagesize);
	result           = (struct service_text_range *)MMap(NULL, freesize, prot, MAP_PRIVATE | MAP_ANON, -1, 0);
	result->str_size = freesize;
	result->str_free = freesize;

	if (range != NULL &&
	    range != SLIST_FIRST(&self->s_txranges) &&
	    range != SLIST_FIRST(&self->s_ehranges))
		munmap(range, range->str_size); /* Free the old range. */

	return result;
}


/* The # of bytes that  must not be freed  past the end of  the
 * .eh_frame section These act as a sentinel marker for unwind. */
#define EH_FRAME_SENTINAL_SIZE 4


/* Free a text range buffer. When `range' is equal to the first
 * element  of `self->s_txranges' or `self->s_ehranges', try to
 * truncate the range to its  used size. Otherwise unmap it  in
 * its entirety. */
PRIVATE NONNULL((1)) void
NOTHROW(CC service_free_textrange)(struct service *__restrict self,
                                   struct service_text_range *range) {
	if unlikely(range == NULL)
		return;
	if (range == SLIST_FIRST(&self->s_txranges) ||
	    range == SLIST_FIRST(&self->s_ehranges)) {
		size_t pagesize = getpagesize();
		size_t unmap_size;
		unmap_size = range->str_free;
		if (range == SLIST_FIRST(&self->s_ehranges)) {
			/* Special case: the  .eh_frame section's trailing 4 bytes must always
			 *               be kept as they represent sentinel storage which must
			 *               not be freed. */
			if (OVERFLOW_USUB(unmap_size, EH_FRAME_SENTINAL_SIZE, &unmap_size))
				unmap_size = 0;
		}
		unmap_size = FLOOR_ALIGN(unmap_size, pagesize);
		if (unmap_size != 0) {
			byte_t *unmap_base;
			unmap_base = (byte_t *)range + range->str_size - unmap_size;
			munmap(unmap_base, unmap_size);
		}
	} else {
		munmap(range, range->str_size);
	}
}


__LIBC void __LIBCCALL __register_frame(void *begin);

/* Lookup a function exported by the service, and if not already loaded, ask the
 * server for information about the function  before creating a wrapper for  it,
 * which is then cached before also being returned.
 * @param: kind: One of `SERVICE_FUNCTION_ENTRY_KIND_*' */
INTERN WUNUSED NONNULL((1, 2)) void *CC
libservice_dlsym_lookup_or_create(struct service *__restrict self,
                                  char const *__restrict name,
                                  unsigned int kind)
		THROWS(E_NO_SUCH_OBJECT, E_BADALLOC, E_INTERRUPT) {
	struct com_generator cg;
	struct service_function_entry *entry;
	struct service_text_range *tx_range, *eh_range;
	size_t tx_bufsize, eh_bufsize;
	byte_t *tx_base, *eh_base;

	assert(kind == SERVICE_FUNCTION_ENTRY_KIND_NORMAL ||
	       kind == SERVICE_FUNCTION_ENTRY_KIND_EXCEPT);

	/* Check if the requested function had already been queried in the past. */
	service_textlock_read(self);
	{
		RAII_FINALLY { service_textlock_endread(self); };
		entry = service_dlsym_lookup(self, name);
	}
	if (entry && entry->sfe_entries[kind] != NULL)
		goto done;

	/* Ask the server about information regarding this symbol. */
	libservice_dlsym_getinfo(self, name, &cg.cg_info);

	/* Initialize the com generator. */
	comgen_init(&cg, self, kind == SERVICE_FUNCTION_ENTRY_KIND_EXCEPT);

	/* Compile the wrapper function. */
	tx_bufsize = COM_GENERATOR_INITIAL_TX_BUFSIZ;
	eh_bufsize = COM_GENERATOR_INITIAL_EH_BUFSIZ;
	service_textlock_write(self);
	tx_range = SLIST_FIRST(&self->s_txranges);
	eh_range = SLIST_FIRST(&self->s_ehranges);
	TRY {

		/* Check once again if the function is available.
		 * It may be if another thread created it while the server was telling us about it. */
		entry = service_dlsym_lookup(self, name);
		if unlikely(entry && entry->sfe_entries[kind] != NULL) {
			service_textlock_endwrite(self);
			goto done;
		}

		for (;;) {
			/* Resize .text and .eh_frame buffers */
			if (!tx_range || (tx_bufsize + offsetof(struct service_text_range, str_data)) > tx_range->str_free)
				tx_range = service_realloc_textrange(self, tx_range, tx_bufsize + offsetof(struct service_text_range, str_data), PROT_READ | PROT_WRITE | PROT_EXEC);
			if (!eh_range || (eh_bufsize + offsetof(struct service_text_range, str_data)) > eh_range->str_free)
				eh_range = service_realloc_textrange(self, eh_range, eh_bufsize + offsetof(struct service_text_range, str_data), PROT_READ | PROT_WRITE);
			assert((tx_bufsize + offsetof(struct service_text_range, str_data)) <= tx_range->str_free);
			assert((eh_bufsize + offsetof(struct service_text_range, str_data)) <= eh_range->str_free);
			tx_bufsize = tx_range->str_free - offsetof(struct service_text_range, str_data);
			eh_bufsize = eh_range->str_free - offsetof(struct service_text_range, str_data);
			tx_base = (byte_t *)tx_range->str_data + tx_range->str_size - tx_bufsize;
			eh_base = (byte_t *)eh_range->str_data + eh_range->str_size - eh_bufsize;
			comgen_reset(&cg,
			             tx_base, tx_base + tx_bufsize,
			             eh_base, eh_base + eh_bufsize);
			if (comgen_compile(&cg))
				break;
			assert(comgen_compile_st_moretx(&cg) ||
			       comgen_compile_st_moreeh(&cg));
			if (comgen_compile_st_moretx(&cg))
				tx_bufsize *= 2;
			if (comgen_compile_st_moreeh(&cg))
				eh_bufsize *= 2;
		}

		/* Calculate actually used buffer sizes. */
		tx_bufsize = comgen_compile_txused(&cg);
		eh_bufsize = comgen_compile_ehused(&cg);
		assert((tx_bufsize + offsetof(struct service_text_range, str_data)) <= tx_range->str_free);
		assert((eh_bufsize + offsetof(struct service_text_range, str_data)) <= eh_range->str_free);

		if (!entry) {
			/* Create a new function entry. */
			size_t usable_vector_size;
			size_t namelen = strlen(name);
			entry = (struct service_function_entry *)Malloc(offsetof(struct service_function_entry, sfe_name) +
			                                                (namelen + 1) * sizeof(char));
			usable_vector_size = malloc_usable_size(self->s_funcv) / sizeof(struct service_function_entry *);
			assert(self->s_funcc <= usable_vector_size);
			if (self->s_funcc >= usable_vector_size) {
				size_t new_alloc;
				new_alloc     = (self->s_funcc + 1) * sizeof(struct service_function_entry *);
				TRY {
					self->s_funcv = (struct service_function_entry **)Realloc(self->s_funcv, new_alloc);
				} EXCEPT {
					free(entry);
					RETHROW();
				}
			}

			/* Initialize the new entry. */
			memcpy(entry->sfe_name, name, namelen + 1, sizeof(char));
			bzero(entry->sfe_entries, sizeof(entry->sfe_entries));

			/* Insert at the proper location. */
			service_dlsym_insert(self, entry);
		}

		/* Safe the wrapper function base address. */
		assert(entry->sfe_entries[kind] == NULL);
		entry->sfe_entries[kind] = tx_base;
	} EXCEPT {
		service_free_textrange(self, tx_range);
		service_free_textrange(self, eh_range);
		service_textlock_endwrite(self);
		RETHROW();
	}

	/* Insert new .text/.eh_frame buffers into the list of ranges. */
	assert(tx_range != SLIST_FIRST(&self->s_ehranges));
	assert(eh_range != SLIST_FIRST(&self->s_txranges));
	if (tx_range != SLIST_FIRST(&self->s_txranges))
		SLIST_INSERT(&self->s_txranges, tx_range, str_link);
	if (eh_range != SLIST_FIRST(&self->s_ehranges)) {
		SLIST_INSERT(&self->s_ehranges, eh_range, str_link);
		service_textlock_endwrite(self);
		/* First-time use of this .eh_frame range: register for use by libunwind! */
		__register_frame(eh_range->str_data);
	} else {
		service_textlock_endwrite(self);
	}
done:
	return entry->sfe_entries[kind];
}



/* Ask the server for information about the function `name', and store it in `*info' */
INTERN NONNULL((1, 2, 3)) void CC
libservice_dlsym_getinfo(struct service *__restrict self, char const *__restrict name,
                         /*out*/ struct service_com_funinfo *__restrict info)
		THROWS(E_NO_SUCH_OBJECT, E_BADALLOC, E_INTERRUPT) {
	size_t namsize;
	size_t comsize;
	service_buf_t buf;
	struct service_comdesc *com;
	struct service_shm_handle *shm;
	uintptr_t com_reladdr;
	uintptr_t com_nxtaddr;
	struct service_shm *shm_ctl;

	namsize = (strlen(name) + 1) * sizeof(char);
	comsize = offsetof(struct service_comdesc, scd_com.sc_dlsym.dl_name) + namsize;

	/* Make sure that there's enough space for us to receive a
	 * success  response,  as well  as an  exception response. */
#define DLSYM_COM_MINSIZE                                                \
	MAX_C(offsetafter(struct service_comdesc, scd_com.sc_dlsym_success), \
	      offsetafter(struct service_comdesc, scd_com.sc_except))
	if (comsize < DLSYM_COM_MINSIZE)
		comsize = DLSYM_COM_MINSIZE;
#undef DLSYM_COM_MINSIZE

	/* Adjust `comsize' such that it is accepted by `libservice_shmbuf_alloc_nopr()' */
	comsize = CEIL_ALIGN(comsize, SERVICE_SHM_ALLOC_ALIGN);
	comsize += SERVICE_SHM_ALLOC_EXTRA;
	if (comsize < SERVICE_SHM_ALLOC_MINSIZE)
		comsize = SERVICE_SHM_ALLOC_MINSIZE;

	/* Allocate a com object to-be used for the request. */
	buf = libservice_shmbuf_alloc_nopr(self, comsize);
	com = (struct service_comdesc *)service_buf_getptr(buf);
	shm = service_buf_getshm(buf);
	RAII_FINALLY { libservice_shmbuf_free_fast_nopr(self, shm, com); };

	/* Fill in the com descriptor. */
	com->scd_com.sc_code = SERVICE_COM_DLSYM;
	memcpy(com->scd_com.sc_dlsym.dl_name, name, namsize);

	/* Add the service_comdesc to the list of active commands `service->s_active_list' */
	/* TODO */

	/* Post the request to the server */
	shm_ctl     = shm->ssh_shm;
	com_reladdr = (uintptr_t)((byte_t *)&com->scd_com - (byte_t *)shm_ctl);
	do {
		com_nxtaddr = shm_ctl->s_commands;
		/* TODO: Check for `SERVICE_SHM_COMMANDS_SHUTDOWN' */
		com->scd_com.sc_link = com_nxtaddr;
		COMPILER_WRITE_BARRIER();
	} while (!atomic_cmpxch_weak(&shm_ctl->s_commands,
	                             com_nxtaddr, com_reladdr));

	/* Wake up the server. */
	sys_lfutex(&shm_ctl->s_commands, LFUTEX_WAKE, 1, NULL, 0);

	/* Wake for the server to respond. */
	TRY {
		sys_Xlfutex(&com->scd_com.sc_code, LFUTEX_WAIT_WHILE,
		            SERVICE_COM_DLSYM, NULL, 0);
	} EXCEPT {
		except_class_t cls = except_class();
		/* Abort the command. */
		if (libservice_aux_com_abort(self, com, SERVICE_COM_DLSYM))
			RETHROW();
		if (EXCEPTCLASS_ISRTLPRIORITY(cls))
			RETHROW();
	}

	/* Remove the service_comdesc to the list of active commands `service->s_active_list' */
	/* TODO */

	/* Check return status. */
	if (com->scd_com.sc_code != SERVICE_COM_ST_SUCCESS) {
		struct exception_data *e = except_data();
		assert(e->e_code == EXCEPT_CODEOF(E_OK));
		if (com->scd_com.sc_code == SERVICE_COM_ST_EXCEPT) {
			e->e_code = com->scd_com.sc_except.e_code;
			memcpy(&e->e_args, &com->scd_com.sc_except.e_args,
			       sizeof(union exception_data_pointers));
		} else {
			e->e_code = EXCEPT_CODEOF(E_NO_SUCH_OBJECT);
			bzero(&e->e_args, sizeof(e->e_args));
		}
		except_throw_current();
	}

	/* On success, copy back function information */
	memcpy(info, &com->scd_com.sc_dlsym_success,
	       sizeof(struct service_com_funinfo));
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
                                        struct service_comdesc *__restrict com,
                                        uintptr_t orig_code) {
	/* Remove the service_comdesc to the list of active commands `service->s_active_list' */
	/* TODO */

	/* Cancel the command */
	/* TODO */
	(void)self;
	(void)com;
	(void)orig_code;
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
