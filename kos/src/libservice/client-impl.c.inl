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
#ifdef __INTELLISENSE__
#include "client.c"
#define LOCAL_DEFINE_NOEXCEPT
#endif /* __INTELLISENSE__ */

DECL_BEGIN

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
#ifdef LOCAL_DEFINE_NOEXCEPT
INTERN WUNUSED NONNULL((1)) void *
NOTHROW(CC libservice_buffer_malloc_nx)(struct service *__restrict self,
                                        size_t num_bytes)
#else /* LOCAL_DEFINE_NOEXCEPT */
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) void *CC
libservice_buffer_malloc(struct service *__restrict self, size_t num_bytes)
		THROWS(E_BADALLOC)
#endif /* !LOCAL_DEFINE_NOEXCEPT */
{
	service_buf_t buf;
	preemption_flag_t was;
	num_bytes += SERVICE_SHM_ALLOC_ALIGN - 1;
	num_bytes &= ~(SERVICE_SHM_ALLOC_ALIGN - 1);
	num_bytes += SERVICE_SHM_ALLOC_EXTRA;
	if (num_bytes < SERVICE_SHM_ALLOC_MINSIZE)
		num_bytes = SERVICE_SHM_ALLOC_MINSIZE;
	/* Allocate a new blob. */
	preemption_pushoff(&was);
#ifdef LOCAL_DEFINE_NOEXCEPT
	buf = libservice_shmbuf_alloc_nopr_nx(self, num_bytes);
	preemption_pop(&was);
#else /* LOCAL_DEFINE_NOEXCEPT */
	{
		RAII_FINALLY { preemption_pop(&was); };
		buf = libservice_shmbuf_alloc_nopr(self, num_bytes);
	}
#endif /* !LOCAL_DEFINE_NOEXCEPT */
	assert(libservice_shmbuf_get_total_size(service_buf_getptr(buf)) >= num_bytes);
	DBG_memset(service_buf_getptr(buf), 0xcc, libservice_shmbuf_get_usable_size(service_buf_getptr(buf)));
	return service_buf_getptr(buf);
}


#ifdef LOCAL_DEFINE_NOEXCEPT
INTERN WUNUSED NONNULL((1)) void *
NOTHROW(CC libservice_buffer_calloc_nx)(struct service *__restrict self,
                                        size_t num_bytes)
#else /* LOCAL_DEFINE_NOEXCEPT */
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) void *CC
libservice_buffer_calloc(struct service *__restrict self, size_t num_bytes)
		THROWS(E_BADALLOC)
#endif /* !LOCAL_DEFINE_NOEXCEPT */
{
	void *result;
#ifdef LOCAL_DEFINE_NOEXCEPT
	result = libservice_buffer_malloc_nx(self, num_bytes);
	if likely(result)
#else /* LOCAL_DEFINE_NOEXCEPT */
	result = libservice_buffer_malloc(self, num_bytes);
#endif /* !LOCAL_DEFINE_NOEXCEPT */
	{
		bzero(result, libservice_shmbuf_get_usable_size(result));
	}
	return result;
}



#ifdef LOCAL_DEFINE_NOEXCEPT
INTERN WUNUSED NONNULL((1)) void *
NOTHROW(CC libservice_buffer_realloc_nx)(struct service *__restrict self,
                                         void *ptr, size_t num_bytes)
#else /* LOCAL_DEFINE_NOEXCEPT */
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) void *CC
libservice_buffer_realloc(struct service *__restrict self, void *ptr, size_t num_bytes)
		THROWS(E_BADALLOC)
#endif /* !LOCAL_DEFINE_NOEXCEPT */
{
	size_t oldsize;
	if (!ptr) {
#ifdef LOCAL_DEFINE_NOEXCEPT
		return libservice_buffer_malloc_nx(self, num_bytes);
#else /* LOCAL_DEFINE_NOEXCEPT */
		return libservice_buffer_malloc(self, num_bytes);
#endif /* !LOCAL_DEFINE_NOEXCEPT */
	}
	num_bytes += SERVICE_SHM_ALLOC_ALIGN - 1;
	num_bytes &= ~(SERVICE_SHM_ALLOC_ALIGN - 1);
	num_bytes += SERVICE_SHM_ALLOC_EXTRA;
	if (num_bytes < SERVICE_SHM_ALLOC_MINSIZE)
		num_bytes = SERVICE_SHM_ALLOC_MINSIZE;
	oldsize = libservice_shmbuf_get_total_size(ptr);
	if (oldsize > num_bytes) {
		size_t num_free;
		num_free = oldsize - num_bytes;
		if (num_free >= SERVICE_SHM_ALLOC_MINSIZE) {
			struct service_shm_handle *shm;
			preemption_flag_t was;
			preemption_pushoff(&was);
			shm = libservice_shm_handle_ataddr_nopr(self, ptr);
			assertf(shm, "service_buffer_realloc(%p): Invalid pointer", ptr);
			libservice_shmbuf_free_nopr(self, shm, ptr);
			preemption_pop(&was);
			libservice_shmbuf_set_total_size(ptr, num_bytes);
		}
	} else if (oldsize < num_bytes) {
		struct service_shm_handle *shm;
		preemption_flag_t was;
		size_t extra;
		preemption_pushoff(&was);
		shm = libservice_shm_handle_ataddr_nopr(self, ptr);
		assertf(shm, "service_buffer_realloc(%p): Invalid pointer", ptr);
		extra = num_bytes - oldsize;
		extra = libservice_shmbuf_allocat_nopr(self, shm, (byte_t *)ptr + oldsize, extra);
		if (extra != 0) {
			assert(extra >= (num_bytes - oldsize));
			oldsize += extra;
			libservice_shmbuf_set_total_size(ptr, oldsize);
			preemption_pop(&was);
		} else {
			service_buf_t buf;
			/* Allocate a new blob. */
#ifdef LOCAL_DEFINE_NOEXCEPT
			buf = libservice_shmbuf_alloc_nopr_nx(self, num_bytes);
#else /* LOCAL_DEFINE_NOEXCEPT */
			RAII_FINALLY { preemption_pop(&was); };
			buf = libservice_shmbuf_alloc_nopr(self, num_bytes);
#endif /* !LOCAL_DEFINE_NOEXCEPT */
			assert(libservice_shmbuf_get_total_size(service_buf_getptr(buf)) >= num_bytes);
			memcpy(service_buf_getptr(buf), ptr, oldsize);
			libservice_shmbuf_freeat_nopr(self, shm, libservice_shmbuf_get_base_addr(ptr), oldsize);
#ifdef LOCAL_DEFINE_NOEXCEPT
			preemption_pop(&was);
#endif /* LOCAL_DEFINE_NOEXCEPT */
			return service_buf_getptr(buf);
		}
	}
	return ptr;
}


DECL_END

#undef LOCAL_DEFINE_NOEXCEPT
