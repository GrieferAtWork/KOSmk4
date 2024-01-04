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
#ifdef __INTELLISENSE__
#include "com.c"
//#define DEFINE_libservice_shmbuf_alloc_nopr
#define DEFINE_libservice_shmbuf_alloc_nopr_nx
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE_libservice_shmbuf_alloc_nopr) + defined(DEFINE_libservice_shmbuf_alloc_nopr_nx)) != 1
#error "Must #define exactly one of `DEFINE_libservice_shmbuf_alloc_nopr', `DEFINE_libservice_shmbuf_alloc_nopr_nx'"
#endif /* ... */

DECL_BEGIN

/* Allocate SHM memory.
 * @param: num_bytes_with_extra: Lower bound for number of bytes to allocate, plus extra space:
 * >> num_bytes_with_extra = MAX(SERVICE_SHM_ALLOC_MINSIZE,
 * >>                            CEIL_ALIGN(num_bytes, SERVICE_SHM_ALLOC_ALIGN) +
 * >>                            SERVICE_SHM_ALLOC_EXTRA); */
#ifdef DEFINE_libservice_shmbuf_alloc_nopr_nx
INTERN NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) service_buf_t
NOTHROW(FCALL libservice_shmbuf_alloc_nopr_nx)(struct service *__restrict self,
                                               size_t num_bytes_with_extra)
#else /* DEFINE_libservice_shmbuf_alloc_nopr_nx */
INTERN NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) service_buf_t FCALL
libservice_shmbuf_alloc_nopr(struct service *__restrict self,
                             size_t num_bytes_with_extra)
		THROWS(E_BADALLOC)
#endif /* !DEFINE_libservice_shmbuf_alloc_nopr_nx */
{
	unsigned int bucket_index;
	struct service_shm_free *range;
	void *result_ptr;
	size_t result_siz;
	REF struct service_shm_handle *result_shm;
	bucket_index = SERVICE_FREE_LIST_INDEX(num_bytes_with_extra);
	libservice_shmlock_acquire_nopr(self);
again:
	do {
		range = LIST_FIRST(&self->s_shm_freelist[bucket_index]);
		if (range) {
			/* Allocate from `range' */
			size_t unused;
			result_siz = service_shm_free_getsize(range);
			assert(result_siz >= num_bytes_with_extra);
			unused = result_siz - num_bytes_with_extra;
			if (unused >= SERVICE_SHM_ALLOC_MINSIZE) {
				result_ptr = range;
				result_siz = num_bytes_with_extra;
				/* Re-insert unused memory into the heap buffer. */
				service_insert_freearea(self, (byte_t *)result_ptr + result_siz, unused);
			} else {
				/* Allocate the entire range. */
				result_ptr = range;
			}
			goto done;
		}
	} while (++bucket_index < SERVICE_FREE_LIST_COUNT);

	/* Must increase the SHM file's size. */
	{
		size_t pagesize = getpagesize();
		size_t newsize;
		newsize = self->s_fd_shm_size + num_bytes_with_extra;
		newsize = CEIL_ALIGN(newsize, pagesize);
#ifdef DEFINE_libservice_shmbuf_alloc_nopr_nx
		if (!service_shmbuf_increase_file_size_locked_nopr(self, newsize, true)) {
			libservice_shmlock_release_nopr(self);
			return service_buf_make(NULL, NULL);
		}
#else /* DEFINE_libservice_shmbuf_alloc_nopr_nx */
		TRY {
			service_shmbuf_increase_file_size_locked_nopr(self, newsize, false);
		} EXCEPT {
			libservice_shmlock_release_nopr(self);
			RETHROW();
		}
#endif /* !DEFINE_libservice_shmbuf_alloc_nopr_nx */
	}

	/* Search for the newly added free range. */
	bucket_index = SERVICE_FREE_LIST_INDEX(num_bytes_with_extra);
	goto again;

done:
	/* Every allocation comes with an implicit reference to its associated
	 * SHM.  Technically we there's no point in us actually returning this
	 * pointer, as it can be determined by the buffer pointer alone  (s.a.
	 * `libservice_shm_handle_ataddr_nopr()'), but that operation runs  in
	 * O(log2(n)) time, so passing this  reference along can speed  things
	 * up a little bit. */
	result_shm = incref(self->s_shm);
	libservice_shmlock_release_nopr(self);
	*(size_t *)result_ptr = result_siz;
	result_ptr = (byte_t *)result_ptr + sizeof(size_t);
	return service_buf_make(result_ptr, result_shm);
}

DECL_END

#undef DEFINE_libservice_shmbuf_alloc_nopr_nx
#undef DEFINE_libservice_shmbuf_alloc_nopr
