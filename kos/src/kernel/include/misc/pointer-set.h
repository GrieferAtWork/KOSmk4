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
#ifndef GUARD_KERNEL_INCLUDE_MISC_POINTER_SET_H
#define GUARD_KERNEL_INCLUDE_MISC_POINTER_SET_H 1

#include <kernel/compiler.h>

#include <kernel/malloc-defs.h>
#include <kernel/malloc.h>
#include <kernel/types.h>

#include <hybrid/__assert.h>

#include <libc/string.h>

#ifdef __CC__
DECL_BEGIN

/* A simple heap-based hash-set for pointers
 * Settings are meant to be overwritten on a per-source bases. */
#ifndef POINTER_SET_HASHPTR
#define POINTER_SET_HASHPTR(x) ((x) >> 6)
#endif /* !POINTER_SET_HASHPTR */
#ifndef POINTER_SET_HASHNXT
#define POINTER_SET_HASHNXT(i, perturb) ((i) = (((i) << 2) + (i) + (perturb) + 1), (perturb) >>= 5)
#endif /* !POINTER_SET_HASHNXT */
#ifndef POINTER_SET_BUFSIZE
#define POINTER_SET_BUFSIZE  16
#endif /* !POINTER_SET_BUFSIZE */
#ifndef POINTER_SET_SENTINAL
#define POINTER_SET_SENTINAL 0
#endif /* !POINTER_SET_SENTINAL */

struct pointer_set {
	size_t     ps_size; /* Number of elements contained. */
	size_t     ps_mask; /* Hash-mask for elements. */
	uintptr_t *ps_list; /* [1..ps_mask][owned_if(!= ps_buf)] Hash-vector. */
	uintptr_t  ps_buf[POINTER_SET_BUFSIZE]; /* Small, pre-allocated buffer for fixed pointers. */
};


/* Enumerate all pointers stored with the given pointer-set. */
#define POINTER_SET_FOREACH(ptr, set)                                                              \
	for (size_t _fe_i = 0; _fe_i <= (set)->ps_mask; ++_fe_i)                                       \
		if (((uintptr_t)((ptr) = (__typeof__(ptr))(set)->ps_list[_fe_i])) == POINTER_SET_SENTINAL) \
			;                                                                                      \
		else
#define _POINTER_SET_USABLE_MEMORY(self)       \
	((self)->ps_list == (self)->ps_buf         \
	 ? POINTER_SET_BUFSIZE * sizeof(uintptr_t) \
	 : kmalloc_usable_size((self)->ps_list))
#define _POINTER_SET_ASSERT_USABLE_MEMORY(self)                 \
	__hybrid_assertf(_POINTER_SET_USABLE_MEMORY(self) >=        \
	                 ((self)->ps_mask + 1) * sizeof(uintptr_t), \
	                 "usable: %Iu, used: %Iu",                  \
	                 _POINTER_SET_USABLE_MEMORY(self),          \
	                 ((self)->ps_mask + 1) * sizeof(uintptr_t))




LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pointer_set_init)(struct pointer_set *__restrict self) {
	size_t i;
	self->ps_size = 0;
	self->ps_mask = POINTER_SET_BUFSIZE - 1;
	self->ps_list = self->ps_buf;
	for (i = 0; i < POINTER_SET_BUFSIZE; ++i)
		self->ps_buf[i] = POINTER_SET_SENTINAL;
}
LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pointer_set_fini)(struct pointer_set *__restrict self) {
	if (self->ps_list != self->ps_buf)
		kfree(self->ps_list);
#ifndef NDEBUG
	__libc_memset(self, 0xcc, sizeof(*self));
#endif /* !NDEBUG */
}

LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pointer_set_clear)(struct pointer_set *__restrict self) {
	__libc_memsetc(self->ps_list, POINTER_SET_SENTINAL, self->ps_mask + 1, __SIZEOF_POINTER__);
	self->ps_size = 0;
}


LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL pointer_set_rehash_with)(struct pointer_set *__restrict self,
                                       /*inherit*/ uintptr_t *__restrict new_set,
                                       uintptr_t new_mask) {
	size_t i;
	uintptr_t j, perturb;
	_POINTER_SET_ASSERT_USABLE_MEMORY(self);
#if POINTER_SET_SENTINAL != 0
	for (i = 0; i <= new_mask; ++i)
		new_set[i] = POINTER_SET_SENTINAL;
#endif /* POINTER_SET_SENTINAL != 0 */
	for (i = 0; i <= self->ps_mask; ++i) {
		uintptr_t ptr = self->ps_list[i];
		if (ptr == POINTER_SET_SENTINAL)
			continue;
		j = perturb = POINTER_SET_HASHPTR(ptr) & new_mask;
		for (;; POINTER_SET_HASHNXT(j, perturb)) {
			uintptr_t *slot = &new_set[j & new_mask];
			if (*slot != POINTER_SET_SENTINAL)
				continue;
			*slot = ptr;
			break;
		}
	}
	if (self->ps_list != self->ps_buf)
		kfree(self->ps_list);
	self->ps_list = new_set;
	self->ps_mask = new_mask;
	_POINTER_SET_ASSERT_USABLE_MEMORY(self);
}

LOCAL NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL pointer_set_do_insert)(struct pointer_set *__restrict self,
                                     uintptr_t ptr) {
	size_t i, perturb;
	uintptr_t *slot;
	_POINTER_SET_ASSERT_USABLE_MEMORY(self);
	i = perturb = POINTER_SET_HASHPTR(ptr) & self->ps_mask;
	for (;; POINTER_SET_HASHNXT(i, perturb)) {
		slot = &self->ps_list[i & self->ps_mask];
		if (*slot == POINTER_SET_SENTINAL)
			break;
		if (*slot == ptr)
			return false;
	}
	*slot = ptr;
	++self->ps_size;
	return true;
}


/* Insert the given `ptr' into the set.
 * @return: true:  `ptr' has been added to the set.
 * @return: false: `ptr' was already apart of the set. */
LOCAL ATTR_BLOCKLIKE_GFP(flags) NONNULL((1)) bool KCALL
pointer_set_insert(struct pointer_set *__restrict self,
                   void *ptr, gfp_t flags DFL(GFP_NORMAL))
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	if (((self->ps_size + 1) * 3) / 2 >= self->ps_mask) {
		uintptr_t new_mask;
		uintptr_t *new_map;
		new_mask = (self->ps_mask << 1) | 1;
		new_map  = (uintptr_t *)kmalloc_nx((new_mask + 1) * sizeof(uintptr_t),
#if POINTER_SET_SENTINAL == 0
		                                   GFP_CALLOC |
#endif /* POINTER_SET_SENTINAL == 0 */
		                                   flags);
		if likely(new_map) {
do_rehash_with:
			pointer_set_rehash_with(self, new_map, new_mask);
		} else if (self->ps_size >= self->ps_mask) {
			new_map = (uintptr_t *)kmalloc((new_mask + 1) * sizeof(uintptr_t),
#if POINTER_SET_SENTINAL == 0
			                               GFP_CALLOC |
#endif /* POINTER_SET_SENTINAL == 0 */
			                               flags);
			goto do_rehash_with;
		}
	}
	return pointer_set_do_insert(self, (uintptr_t)ptr);
}


#define POINTER_SET_INSERT_NX_FAILED  (-1) /* Failed to rehash the set */
#define POINTER_SET_INSERT_NX_EXISTS    0  /* `ptr' was already apart of the set. */
#define POINTER_SET_INSERT_NX_SUCCESS   1  /* `ptr' has been added to the set. */
/* Insert the given `ptr' into the set.
 * @return: * : One of `POINTER_SET_INSERT_NX_*' */
LOCAL ATTR_BLOCKLIKE_GFP(flags) NONNULL((1)) int
NOTHROW(KCALL pointer_set_insert_nx)(struct pointer_set *__restrict self,
                                     void *ptr, gfp_t flags DFL(GFP_NORMAL)) {
	if (((self->ps_size + 1) * 3) / 2 >= self->ps_mask) {
		uintptr_t new_mask;
		uintptr_t *new_map;
		new_mask = (self->ps_mask << 1) | 1;
		new_map  = (uintptr_t *)kmalloc_nx((new_mask + 1) * sizeof(uintptr_t),
#if POINTER_SET_SENTINAL == 0
		                                   GFP_CALLOC |
#endif /* POINTER_SET_SENTINAL == 0 */
		                                   flags);
		if likely(new_map) {
			pointer_set_rehash_with(self, new_map, new_mask);
		} else if (self->ps_size >= self->ps_mask) {
			return POINTER_SET_INSERT_NX_FAILED;
		}
	}
	return pointer_set_do_insert(self, (uintptr_t)ptr)
	       ? POINTER_SET_INSERT_NX_SUCCESS
	       : POINTER_SET_INSERT_NX_EXISTS;
}

LOCAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(KCALL pointer_set_contains)(struct pointer_set const *__restrict self,
                                    void *ptr) {
	size_t i, perturb;
	_POINTER_SET_ASSERT_USABLE_MEMORY(self);
	i = perturb = POINTER_SET_HASHPTR((uintptr_t)ptr) & self->ps_mask;
	for (;; POINTER_SET_HASHNXT(i, perturb)) {
		uintptr_t ent = self->ps_list[i & self->ps_mask];
		if (ent == POINTER_SET_SENTINAL)
			return false;
		if (ent == (uintptr_t)ptr)
			return true;
	}
}




/* Set the given pointer_set  and re-hash it to  be
 * able to sustain at least `min_allocation' items. */
LOCAL ATTR_BLOCKLIKE_GFP(flags) NONNULL((1)) void KCALL
pointer_set_clear_and_rehash(struct pointer_set *__restrict self,
                             size_t min_allocation,
                             gfp_t flags DFL(GFP_NORMAL))
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	size_t new_mask;
	uintptr_t *old_map;
	uintptr_t *new_map;
	_POINTER_SET_ASSERT_USABLE_MEMORY(self);
	new_mask = 1;
	while (new_mask <= (min_allocation * 3) / 2)
		new_mask = (new_mask << 1) | 1;
	old_map = self->ps_list;
	if (self->ps_list == self->ps_buf)
		old_map = __NULLPTR;
	new_map = (uintptr_t *)krealloc_nx(old_map,
	                                   (new_mask + 1) * sizeof(uintptr_t),
#if POINTER_SET_SENTINAL == 0
	                                   GFP_CALLOC |
#endif /* POINTER_SET_SENTINAL == 0 */
	                                   flags);
	if unlikely(!new_map) {
		new_mask = 1;
		while (new_mask <= min_allocation)
			new_mask = (new_mask << 1) | 1;
		new_map = (uintptr_t *)krealloc(old_map,
		                                (new_mask + 1) * sizeof(uintptr_t),
#if POINTER_SET_SENTINAL == 0
		                                GFP_CALLOC |
#endif /* POINTER_SET_SENTINAL == 0 */
		                                flags);
	}
	/* NULL-out pointers from the already-allocated pointer set area. */
	__libc_memsetc(new_map, POINTER_SET_SENTINAL, self->ps_mask + 1, __SIZEOF_POINTER__);
#ifndef NDEBUG
	{
		size_t i;
		for (i = 0; i <= new_mask; ++i)
			__hybrid_assert(new_map[i] == POINTER_SET_SENTINAL);
	}
#endif /* !NDEBUG */
	self->ps_list = new_map;
	self->ps_mask = new_mask;
	self->ps_size = 0;
	_POINTER_SET_ASSERT_USABLE_MEMORY(self);
}

LOCAL ATTR_BLOCKLIKE_GFP(flags) NONNULL((1)) bool
NOTHROW(KCALL pointer_set_clear_and_rehash_nx)(struct pointer_set *__restrict self,
                                               size_t min_allocation,
                                               gfp_t flags DFL(GFP_NORMAL)) {
	size_t new_mask;
	uintptr_t *new_map;
	uintptr_t *old_map;
	_POINTER_SET_ASSERT_USABLE_MEMORY(self);
	new_mask = 1;
	while (new_mask <= (min_allocation * 3) / 2)
		new_mask = (new_mask << 1) | 1;
	old_map = self->ps_list;
	if (self->ps_list == self->ps_buf)
		old_map = __NULLPTR;
	new_map = (uintptr_t *)krealloc_nx(old_map,
	                                   (new_mask + 1) *
	                                   sizeof(uintptr_t),
#if POINTER_SET_SENTINAL == 0
	                                   GFP_CALLOC |
#endif /* POINTER_SET_SENTINAL == 0 */
	                                   flags);
	if unlikely(!new_map) {
		new_mask = 1;
		while (new_mask <= min_allocation)
			new_mask = (new_mask << 1) | 1;
		new_map = (uintptr_t *)krealloc_nx(old_map,
		                                   (new_mask + 1) * sizeof(uintptr_t),
#if POINTER_SET_SENTINAL == 0
		                                   GFP_CALLOC |
#endif /* POINTER_SET_SENTINAL == 0 */
		                                   flags);
		if unlikely(!new_map)
			return false;
	}
	/* NULL-out pointers from the already-allocated pointer set area. */
	__libc_memsetc(new_map, POINTER_SET_SENTINAL, self->ps_mask + 1, __SIZEOF_POINTER__);
#ifndef NDEBUG
	{
		size_t i;
		for (i = 0; i <= new_mask; ++i)
			__hybrid_assert(new_map[i] == POINTER_SET_SENTINAL);
	}
#endif /* !NDEBUG */
	self->ps_list = new_map;
	self->ps_mask = new_mask;
	self->ps_size = 0;
	_POINTER_SET_ASSERT_USABLE_MEMORY(self);
	return true;
}





DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_MISC_POINTER_SET_H */
