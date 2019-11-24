/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "handle.c"
//#define INSTALL_IN 1
//#define INSTALL_AT 1
#endif


DECL_BEGIN

#ifdef INSTALL_IN
/* Same as `handle_installinto()', but return the old handle
 * (or a HANDLE_TYPE_UNDEFINED) previously bound to that slot. */
PUBLIC WUNUSED NONNULL((1)) REF struct handle FCALL
handle_installxchg(struct handle_manager *__restrict self,
                   unsigned int dst_fd, struct handle hnd)
#elif defined(INSTALL_AT)
/* Similar to `handle_put()', but place the handle in a
 * descriptor slot that is greater than, or equal to `hint'.
 * @throw: E_BADALLOC: Insufficient kernel memory to allocate more handle slots
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS: Too many open handles
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_RANGE: `hint' is outside the allowed handle range.
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked */
FUNDEF NONNULL((1)) unsigned int FCALL
handle_installat(struct handle_manager *__restrict self,
                 unsigned int hint, struct handle hnd)
#else /* INSTALL_AT */
/* Add the given handle to the handle manager and
 * return the handle number of where it was placed.
 * @throw: E_BADALLOC: Insufficient kernel memory to allocate more handle slots
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS: Too many open handles
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_RANGE: Too many open handles
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked */
PUBLIC NONNULL((1)) unsigned int FCALL
handle_install(struct handle_manager *__restrict self,
               struct handle hnd)
#endif /* !INSTALL_AT */
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE) {
#ifndef INSTALL_IN
	unsigned int dst_fd;
#endif /* !INSTALL_IN */
	assert(hnd.h_type != HANDLE_TYPE_UNDEFINED);
	sync_write(&self->hm_lock);
again_locked:
	handle_manager_assert_integrity(self);
#ifndef INSTALL_IN
#ifndef INSTALL_AT
	dst_fd = self->hm_minfree;
#else /* !INSTALL_AT */
	dst_fd = hint;
#endif /* INSTALL_AT */
#endif /* !INSTALL_IN */

#ifdef INSTALL_IN
	/* Check if we must override an existing handle. */
	{
		REF struct handle old_handle;
		if (self->hm_mode == HANDLE_MANAGER_MODE_LINEAR) {
			if (dst_fd < self->hm_linear.hm_alloc) {
				old_handle                        = self->hm_linear.hm_vector[dst_fd];
				self->hm_linear.hm_vector[dst_fd] = incref(hnd);
update_old_handle:
				/* Update counters according to the change in handle binding. */
				if (old_handle.h_type == HANDLE_TYPE_UNDEFINED) {
					/* No handle was loaded before */
					++self->hm_count;
				} else {
					/* No need to update `hm_count': The total change is -1+1==0 */
					assert(self->hm_count != 0);
					if (old_handle.h_mode & IO_CLOEXEC) {
						assert(self->hm_cloexec_count);
						--self->hm_cloexec_count;
					}
					if (old_handle.h_mode & IO_CLOFORK) {
						assert(self->hm_clofork_count);
						--self->hm_clofork_count;
					}
				}
				if (hnd.h_mode & IO_CLOEXEC)
					++self->hm_cloexec_count;
				if (hnd.h_mode & IO_CLOFORK)
					++self->hm_clofork_count;
				handle_manager_assert_integrity(self);
				sync_endwrite(&self->hm_lock);
				return old_handle;
			}
		} else {
			unsigned int i, perturb;
			i = perturb = dst_fd & self->hm_hashvector.hm_hashmsk;
			for (;; handle_manager_hashnext(i, perturb)) {
				struct handle_hashent ent;
				unsigned int vecid;
				ent = self->hm_hashvector.hm_hashvec[i & self->hm_hashvector.hm_hashmsk];
				if (ent.hh_handle_id == HANDLE_HASHENT_SENTINEL_ID)
					break;
				vecid = ent.hh_vector_index;
				assert(vecid < self->hm_hashvector.hm_alloc);
				if (vecid == (unsigned int)-1) {
					old_handle.h_type = HANDLE_TYPE_UNDEFINED;
					old_handle.h_mode = IO_GENERIC;
					old_handle.h_data = NULL;
				} else {
					old_handle = self->hm_linear.hm_vector[vecid];
				}
				self->hm_linear.hm_vector[vecid] = incref(hnd);
				goto update_old_handle;
			}
		}
	}
#endif /* INSTALL_IN */

	/* Make sure that we're not exceeding our allowed limit count */
	if unlikely(self->hm_count >= self->hm_cntlimit) {
		unsigned int cnt = self->hm_count;
		unsigned int lim = self->hm_cntlimit;
		COMPILER_READ_BARRIER();
		sync_endwrite(&self->hm_lock);
		THROW(E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS, 1, cnt, lim);
	}
	/* Search for the first unused slot. */
#ifndef INSTALL_IN
	if (self->hm_mode == HANDLE_MANAGER_MODE_LINEAR) {
		/* Scan for the next unused handle slot. */
		assert(self->hm_count <= self->hm_linear.hm_alloc);
		while (dst_fd < self->hm_linear.hm_alloc &&
		       self->hm_linear.hm_vector[dst_fd].h_type != HANDLE_TYPE_UNDEFINED)
			++dst_fd;
	} else {
		assert(self->hm_mode == HANDLE_MANAGER_MODE_HASHVECTOR);
		assert(self->hm_count <= self->hm_hashvector.hm_alloc);
		for (;;) {
			unsigned int j, perturb;
#if !defined(INSTALL_AT) && !defined(INSTALL_IN)
			assertf(dst_fd <= self->hm_hashvector.hm_hashmsk,
			        "There needs to be a free entry before `hm_hashmsk', as this "
			        "is a requirement for how hash-vectors work (mask >= count)\n"
			        "dst_fd                         = %u\n"
			        "self->hm_hashvector.hm_hashmsk = %u\n",
			        dst_fd, self->hm_hashvector.hm_hashmsk);
			j = perturb = dst_fd;
#else /* !INSTALL_AT && !INSTALL_IN */
			j = perturb = dst_fd & self->hm_hashvector.hm_hashmsk;
#endif /* INSTALL_AT || INSTALL_IN */
			for (;; handle_manager_hashnext(j, perturb)) {
				struct handle_hashent *ent;
				ent = &self->hm_hashvector.hm_hashvec[j & self->hm_hashvector.hm_hashmsk];
				if (ent->hh_handle_id == HANDLE_HASHENT_SENTINEL_ID)
					goto got_result_slot; /* File descriptor index is unused */
				if (ent->hh_handle_id == dst_fd &&
				    ent->hh_vector_index != (unsigned int)-1)
					break; /* File descriptor index is used */
			}
			++dst_fd;
		}
	}
#endif /* !INSTALL_IN */
got_result_slot:

	/* Make sure that we're not exceeding our allowed limit ceiling */
	if unlikely(dst_fd > self->hm_maxlimit) {
		unsigned int cnt, lim;
		lim = self->hm_maxlimit;
		cnt = self->hm_mode == HANDLE_MANAGER_MODE_LINEAR
		      ? handle_manager_get_max_linear_fd_plus_one(self)
		      : handle_manager_get_max_hashvector_fd_plus_one(self);
		COMPILER_READ_BARRIER();
		sync_endwrite(&self->hm_lock);
		THROW(E_BADALLOC_INSUFFICIENT_HANDLE_RANGE, dst_fd, cnt, lim);
	}

	/* Now that we've got an appropriate handle
	 * number, install the handle into that slot! */
	if (self->hm_mode == HANDLE_MANAGER_MODE_LINEAR) {
#if defined(INSTALL_AT) || defined(INSTALL_IN)
		unsigned int how;
		how = handle_manage_switch_to_hashmode_for_handle(self, dst_fd);
		if (how == HANDLE_MANAGE_SWITCH_TO_HASHMODE_FOR_HANDLE_NOT_CHANGED_UNLOCKED ||
		    how == HANDLE_MANAGE_SWITCH_TO_HASHMODE_FOR_HANDLE_CHANGED_UNLOCKED)
			goto again_locked;
		if (how == HANDLE_MANAGE_SWITCH_TO_HASHMODE_FOR_HANDLE_CHANGED_LOCKED)
			goto install_hash_handle;
#else /* INSTALL_AT || INSTALL_IN */
		assert(dst_fd <= self->hm_linear.hm_alloc);
#endif /* !INSTALL_AT && !INSTALL_IN */
		if (dst_fd >= self->hm_linear.hm_alloc) {
			struct handle *new_vector;
			unsigned int new_alloc;
#if !defined(INSTALL_AT) && !defined(INSTALL_IN)
			assertf(dst_fd == self->hm_count,
			        "If this isn't true, then there must be unused "
			        "slots somewhere, which we should have picked up on\n"
			        "dst_fd           = %u\n"
			        "self->hm_count   = %u\n"
			        "self->hm_minfree = %u\n"
			        "self->hm_mode    = %u\n",
			        dst_fd, self->hm_count, self->hm_minfree, self->hm_mode);
#endif /* !INSTALL_AT && !INSTALL_IN */
			new_alloc = dst_fd + 16;
			if unlikely(new_alloc > self->hm_maxlimit)
				new_alloc = self->hm_maxlimit;
			assert(new_alloc > dst_fd);
			new_vector = (struct handle *)krealloc_nx(self->hm_linear.hm_vector,
			                                          new_alloc * sizeof(struct handle),
			                                          GFP_PREFLT |
			                                          GFP_ATOMIC
#if HANDLE_TYPE_UNDEFINED == 0
			                                          |
			                                          GFP_CALLOC
#endif /* HANDLE_TYPE_UNDEFINED == 0 */
			                                          );
#if HANDLE_TYPE_UNDEFINED == 0
			assert(!new_vector ||
			       new_vector[new_alloc - 1].h_type == HANDLE_TYPE_UNDEFINED);
#endif /* HANDLE_TYPE_UNDEFINED == 0 */
			if unlikely(!new_vector) {
				/* Try again with a smaller increment. */
				new_vector = (struct handle *)krealloc_nx(self->hm_linear.hm_vector,
				                                          (dst_fd + 1) * sizeof(struct handle),
				                                          GFP_PREFLT |
				                                          GFP_ATOMIC
#if HANDLE_TYPE_UNDEFINED == 0
				                                          |
				                                          GFP_CALLOC
#endif /* HANDLE_TYPE_UNDEFINED == 0 */
				                                          );
				if (new_vector)
					new_alloc = dst_fd + 1;
				else {
					/* Must manually allocate a larger vector,
					 * whilst not holding a lock to the handle manager! */
					handle_manager_assert_integrity(self);
					sync_endwrite(&self->hm_lock);
					new_vector = (struct handle *)kmalloc_nx(new_alloc * sizeof(struct handle),
					                                         GFP_PREFLT
#if HANDLE_TYPE_UNDEFINED == 0
					                                         |
					                                         GFP_CALLOC
#endif /* HANDLE_TYPE_UNDEFINED == 0 */
					                                         );
					if unlikely(!new_vector) {
						new_alloc  = dst_fd + 1;
						new_vector = (struct handle *)kmalloc(new_alloc * sizeof(struct handle),
						                                      GFP_PREFLT
#if HANDLE_TYPE_UNDEFINED == 0
						                                      |
						                                      GFP_CALLOC
#endif /* HANDLE_TYPE_UNDEFINED == 0 */
						                                      );
					}
					TRY {
						sync_write(&self->hm_lock);
					} EXCEPT {
						kfree(new_vector);
						RETHROW();
					}
					/* Install the (larger) vector */
					if unlikely(self->hm_mode != HANDLE_MANAGER_MODE_LINEAR ||
					            self->hm_linear.hm_alloc >= new_alloc) {
						kfree(new_vector);
					} else {
#if HANDLE_TYPE_UNDEFINED != 0
						memset(new_vector + self->hm_linear.hm_alloc, HANDLE_TYPE_UNDEFINED & 0xff,
						       (new_alloc - self->hm_linear.hm_alloc) * sizeof(struct handle));
#endif /* HANDLE_TYPE_UNDEFINED != 0 */
						memcpy(new_vector,
						       self->hm_linear.hm_vector,
						       self->hm_linear.hm_alloc,
						       sizeof(struct handle));
						/* Install the new vector and free the old one. */
						assert(new_vector != self->hm_linear.hm_vector);
						kfree(self->hm_linear.hm_vector);
						self->hm_linear.hm_vector = new_vector;
						self->hm_linear.hm_alloc  = new_alloc;
					}
					goto again_locked;
				}
			}
#if HANDLE_TYPE_UNDEFINED != 0
			memset(new_vector + self->hm_linear.hm_alloc, HANDLE_TYPE_UNDEFINED & 0xff,
			       (new_alloc - self->hm_linear.hm_alloc) * sizeof(struct handle));
#endif /* HANDLE_TYPE_UNDEFINED != 0 */
			assert(new_alloc != 0);
			assert(new_vector[new_alloc - 1].h_type == HANDLE_TYPE_UNDEFINED);

			/* Install the krealloc()-ated vector. */
			self->hm_linear.hm_vector = new_vector;
			self->hm_linear.hm_alloc  = new_alloc;
			handle_manager_assert_integrity(self);
		}
		/* Store the given handle within its designated slot. */
		self->hm_linear.hm_vector[dst_fd] = incref(hnd);
		assert(self->hm_count <= self->hm_linear.hm_alloc);
	} else {
		unsigned int how;
		unsigned int j, perturb;
		unsigned int vector_index;
		struct handle_hashent *ent;
#if defined(INSTALL_AT) || defined(INSTALL_IN)
install_hash_handle:
#endif /* INSTALL_AT || INSTALL_IN */
		/* Figure out where we want to put the new handle within the indirection handle-vector. */
		vector_index = self->hm_hashvector.hm_vecfree;
		assert(vector_index <= self->hm_count);
		while (vector_index < self->hm_count &&
		       self->hm_hashvector.hm_vector[vector_index].h_type != HANDLE_TYPE_UNDEFINED)
			++vector_index;
		assert(vector_index <= self->hm_count);
		assert(vector_index <= self->hm_hashvector.hm_alloc);
		if (vector_index >= self->hm_hashvector.hm_alloc) {
			struct handle *new_vector;
			unsigned int new_alloc;
			assert(vector_index == self->hm_hashvector.hm_alloc);
			assert(self->hm_count == self->hm_hashvector.hm_alloc);
			/* Extend the handle-vector. */
			new_alloc  = self->hm_hashvector.hm_alloc + 16;
			new_vector = (struct handle *)krealloc_nx(self->hm_hashvector.hm_vector,
			                                          new_alloc * sizeof(struct handle),
			                                          GFP_PREFLT |
			                                          GFP_ATOMIC
#if HANDLE_TYPE_UNDEFINED == 0
			                                          |
			                                          GFP_CALLOC
#endif /* HANDLE_TYPE_UNDEFINED == 0 */
			                                          );
			if (!new_vector) {
				new_alloc  = vector_index + 1;
				new_vector = (struct handle *)krealloc_nx(self->hm_hashvector.hm_vector,
				                                          new_alloc * sizeof(struct handle),
				                                          GFP_PREFLT |
				                                          GFP_ATOMIC
#if HANDLE_TYPE_UNDEFINED == 0
				                                          |
				                                          GFP_CALLOC
#endif /* HANDLE_TYPE_UNDEFINED == 0 */
				                                          );
				if unlikely(!new_vector) {
					/* Unlock, then allocate with blocking */
					new_alloc = self->hm_hashvector.hm_alloc + 16;
					handle_manager_assert_integrity(self);
					sync_endwrite(&self->hm_lock);
					new_vector = (struct handle *)kmalloc_nx(new_alloc * sizeof(struct handle),
					                                         GFP_PREFLT
#if HANDLE_TYPE_UNDEFINED == 0
					                                         |
					                                         GFP_CALLOC
#endif /* HANDLE_TYPE_UNDEFINED == 0 */
					                                         );
					if unlikely(!new_vector) {
						new_alloc  = vector_index + 1;
						new_vector = (struct handle *)kmalloc(new_alloc * sizeof(struct handle),
						                                      GFP_PREFLT
#if HANDLE_TYPE_UNDEFINED == 0
						                                      |
						                                      GFP_CALLOC
#endif /* HANDLE_TYPE_UNDEFINED == 0 */
						                                      );
					}
					TRY {
						sync_write(&self->hm_lock);
					} EXCEPT {
						kfree(new_vector);
						RETHROW();
					}
					if unlikely(self->hm_mode != HANDLE_MANAGER_MODE_HASHVECTOR ||
					            self->hm_hashvector.hm_alloc >= new_alloc) {
						kfree(new_vector);
					} else {
#if HANDLE_TYPE_UNDEFINED != 0
						memset(new_vector + self->hm_hashvector.hm_alloc, HANDLE_TYPE_UNDEFINED & 0xff,
						       (new_alloc - self->hm_hashvector.hm_alloc) * sizeof(struct handle));
#endif /* HANDLE_TYPE_UNDEFINED != 0 */
						memcpy(new_vector,
						       self->hm_hashvector.hm_vector,
						       self->hm_hashvector.hm_alloc,
						       sizeof(struct handle));
						/* Install the new vector and free the old one. */
						assert(new_vector != self->hm_hashvector.hm_vector);
						kfree(self->hm_hashvector.hm_vector);
						self->hm_hashvector.hm_vector = new_vector;
						self->hm_hashvector.hm_alloc  = new_alloc;
					}
					goto again_locked;
				}
			}
#if HANDLE_TYPE_UNDEFINED != 0
			memset(new_vector + self->hm_hashvector.hm_alloc, HANDLE_TYPE_UNDEFINED & 0xff,
			       (new_alloc - self->hm_hashvector.hm_alloc) * sizeof(struct handle));
#endif /* HANDLE_TYPE_UNDEFINED != 0 */
			/* Install the krealloc()-ated vector. */
			self->hm_hashvector.hm_vector = new_vector;
			self->hm_hashvector.hm_alloc  = new_alloc;
		}
		assert(vector_index < self->hm_hashvector.hm_alloc);

#if defined(INSTALL_AT) || defined(INSTALL_IN)
		j = perturb = dst_fd & self->hm_hashvector.hm_hashmsk;
#else /* INSTALL_AT || INSTALL_IN */
		assert(dst_fd <= self->hm_hashvector.hm_hashmsk);
		j = perturb = dst_fd;
#endif /* !INSTALL_AT && !INSTALL_IN */
		assert(dst_fd != HANDLE_HASHENT_SENTINEL_ID);
		assert(vector_index != (unsigned int)-1);
		for (;; handle_manager_hashnext(j, perturb)) {
			ent = &self->hm_hashvector.hm_hashvec[j & self->hm_hashvector.hm_hashmsk];
			if (ent->hh_handle_id == HANDLE_HASHENT_SENTINEL_ID) {
				/* Append to the sentinel */
				how = handle_manage_rehash(self);
				if (how != HANDLE_MANAGE_REHASH_UNCHANGED_LOCKED) {
					if (how == HANDLE_MANAGE_REHASH_REHASHED_LOCKED)
						goto got_result_slot;
					goto again_locked;
				}
				assert(ent->hh_handle_id == HANDLE_HASHENT_SENTINEL_ID);
				++self->hm_hashvector.hm_hashuse;
				break;
			}
			if (ent->hh_vector_index == (unsigned int)-1) {
				/* Re-use a previously deleted entry. */
				break;
			}
			assertf(ent->hh_handle_id != dst_fd,
			        "Handle %u already in use",
			        dst_fd);
		}
		ent->hh_handle_id    = dst_fd;
		ent->hh_vector_index = vector_index;
		/* Insert the given handle into the vector. */
		assert(self->hm_hashvector.hm_vector[vector_index].h_type == HANDLE_TYPE_UNDEFINED);
		self->hm_hashvector.hm_vector[vector_index] = incref(hnd);
		assert(self->hm_count <= self->hm_hashvector.hm_alloc);
		assert(self->hm_count + 1 <= self->hm_hashvector.hm_hashuse);
	}

	/* Keep track of the number of used handles. */
	++self->hm_count;
	if (hnd.h_mode & IO_CLOEXEC)
		++self->hm_cloexec_count;
	if (hnd.h_mode & IO_CLOFORK)
		++self->hm_clofork_count;
#if !defined(INSTALL_AT) && !defined(INSTALL_IN)
	self->hm_minfree = dst_fd + 1;
#endif /* !INSTALL_AT && !INSTALL_IN */
	handle_manager_assert_integrity(self);
	sync_endwrite(&self->hm_lock);
#ifdef INSTALL_IN
	{
		REF struct handle old_handle;
		old_handle.h_type = HANDLE_TYPE_UNDEFINED;
		old_handle.h_mode = IO_GENERIC;
		old_handle.h_data = NULL;
		return old_handle;
	}
#else /* INSTALL_IN */
	return dst_fd;
#endif /* !INSTALL_IN */
}


#undef INSTALL_IN
#undef INSTALL_AT

DECL_END
