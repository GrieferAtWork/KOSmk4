/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_IOVEC_H
#define GUARD_KERNEL_INCLUDE_KERNEL_IOVEC_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/__assert.h>

#include <kos/kernel/memory.h>

#ifndef __INTELLISENSE__
#include <libc/string.h>
#endif /* !__INTELLISENSE__ */

DECL_BEGIN


#ifndef __ALIGNOF_PHYSADDR_T__
#if __SIZEOF_PHYSADDR_T__ == 8
#define __ALIGNOF_PHYSADDR_T__ __ALIGNOF_INT64__
#else /* __SIZEOF_PHYSADDR_T__ == 8 */
#define __ALIGNOF_PHYSADDR_T__ __SIZEOF_PHYSADDR_T__
#endif /* __SIZEOF_PHYSADDR_T__ != 8 */
#endif /* !__ALIGNOF_PHYSADDR_T__ */


#define OFFSET_AIO_BUFFER_ENTRY_BASE 0
#define OFFSET_AIO_BUFFER_ENTRY_SIZE __SIZEOF_POINTER__
#define SIZEOF_AIO_BUFFER_ENTRY      (__SIZEOF_POINTER__ + __SIZEOF_SIZE_T__)

#define OFFSET_AIO_BUFFER_ENTC 0
#define OFFSET_AIO_BUFFER_ENTV __SIZEOF_SIZE_T__
#define OFFSET_AIO_BUFFER_HEAD (__SIZEOF_SIZE_T__ + __SIZEOF_POINTER__)
#define OFFSET_AIO_BUFFER_LAST (__SIZEOF_SIZE_T__ + __SIZEOF_POINTER__ + SIZEOF_AIO_BUFFER_ENTRY)
#define SIZEOF_AIO_BUFFER      ((__SIZEOF_SIZE_T__ * 2) + __SIZEOF_POINTER__ + SIZEOF_AIO_BUFFER_ENTRY)

#define OFFSET_AIO_PBUFFER_ENTRY_BASE 0
#if __SIZEOF_PHYSADDR_T__ > __SIZEOF_SIZE_T__
#define OFFSET_AIO_PBUFFER_ENTRY_SIZE __SIZEOF_PHYSADDR_T__
#define SIZEOF_AIO_PBUFFER_ENTRY      (2 * __SIZEOF_PHYSADDR_T__)
#else /* __SIZEOF_PHYSADDR_T__ > __SIZEOF_SIZE_T__ */
#define OFFSET_AIO_PBUFFER_ENTRY_SIZE __SIZEOF_SIZE_T__
#define SIZEOF_AIO_PBUFFER_ENTRY      (2 * __SIZEOF_SIZE_T__)
#endif /* __SIZEOF_PHYSADDR_T__ <= __SIZEOF_SIZE_T__ */

#define OFFSET_AIO_PBUFFER_ENTC 0
#define OFFSET_AIO_PBUFFER_ENTV __SIZEOF_SIZE_T__
#define OFFSET_AIO_PBUFFER_HEAD (__SIZEOF_SIZE_T__ + __SIZEOF_POINTER__)
#define OFFSET_AIO_PBUFFER_LAST (__SIZEOF_SIZE_T__ + __SIZEOF_POINTER__ + SIZEOF_AIO_PBUFFER_ENTRY)
#define __SIZEOF_AIO_PBUFFER    ((__SIZEOF_SIZE_T__ * 2) + __SIZEOF_POINTER__ + SIZEOF_AIO_PBUFFER_ENTRY)
#if (__SIZEOF_AIO_PBUFFER % __ALIGNOF_PHYSADDR_T__) != 0
#define SIZEOF_AIO_PBUFFER ((__SIZEOF_AIO_PBUFFER + (__ALIGNOF_PHYSADDR_T__ - 1)) & ~(__ALIGNOF_PHYSADDR_T__ - 1))
#else /* (__SIZEOF_AIO_PBUFFER % __ALIGNOF_PHYSADDR_T__) != 0 */
#define SIZEOF_AIO_PBUFFER __SIZEOF_AIO_PBUFFER
#endif /* (__SIZEOF_AIO_PBUFFER % __ALIGNOF_PHYSADDR_T__) == 0 */

#ifdef __CC__

#ifndef __aio_buffer_entry_defined
#define __aio_buffer_entry_defined 1
struct aio_buffer_entry {
	USER CHECKED byte_t *ab_base; /* [?..ab_size] Virtual base address of the buffer. */
	size_t               ab_size; /* Buffer size of `ab_base' (in bytes) */
};
#endif /* !__aio_buffer_entry_defined */

struct aio_buffer {
	size_t                         ab_entc; /* [!0] Number of entries. */
	struct aio_buffer_entry const *ab_entv; /* [1..ab_entc] Vector of entries. */
	struct aio_buffer_entry        ab_head; /* Override for `ab_entv[0]' */
	size_t                         ab_last; /* Override for `ab_entv[ab_entc - 1].ab_size' */
};

struct aio_pbuffer_entry {
	physaddr_t ab_base; /* [?..ab_size] Physical base address of the target buffer. */
	size_t     ab_size; /* Number of bytes that should be written at `ab_base' */
#if __SIZEOF_PHYSADDR_T__ > __SIZEOF_SIZE_T__
	byte_t    _ab_pad[__SIZEOF_PHYSADDR_T__ - __SIZEOF_SIZE_T__]; /* ... */
#endif /* __SIZEOF_PHYSADDR_T__ > __SIZEOF_SIZE_T__ */
};

struct aio_pbuffer {
	size_t                          ab_entc; /* [!0] Number of entries. */
	struct aio_pbuffer_entry const *ab_entv; /* [1..ab_entc] Vector of entries. */
	struct aio_pbuffer_entry        ab_head; /* Override for `ab_entv[0]' */
	size_t                          ab_last; /* Override for `ab_entv[ab_entc - 1].ab_size' */
#if (__SIZEOF_AIO_PBUFFER % __ALIGNOF_PHYSADDR_T__) != 0
	__byte_t _ab_pad[__ALIGNOF_PHYSADDR_T__ - (__SIZEOF_AIO_PBUFFER % __ALIGNOF_PHYSADDR_T__)]; /* ... */
#endif /* (__SIZEOF_AIO_PBUFFER % __ALIGNOF_PHYSADDR_T__) != 0 */
};

/* >> struct aio_buffer_entry ent;
 * >> AIO_BUFFER_FOREACH(ent, buf) {
 * >>     ...
 * >> }
 */
#define AIO_BUFFER_FOREACH(ent, self)                                     \
	for (size_t _abf_i = 0; _abf_i < (self)->ab_entc; ++_abf_i)           \
		if (((_abf_i) == 0                                                \
		     ? (void)((ent) = (self)->ab_head)                            \
		     : (void)((ent).ab_base = (self)->ab_entv[_abf_i].ab_base,    \
		              (ent).ab_size = _abf_i == (self)->ab_entc - 1       \
		                              ? (self)->ab_last                   \
		                              : (self)->ab_entv[_abf_i].ab_size), \
		     0))                                                          \
			;                                                             \
		else
#define AIO_BUFFER_FOREACH_N(ent, self)                                   \
	for (size_t _abf_i = 0;; ++_abf_i)                                    \
		if (((__hybrid_assert(_abf_i < (self)->ab_entc)),                 \
		     (_abf_i) == 0                                                \
		     ? (void)((ent) = (self)->ab_head)                            \
		     : (void)((ent).ab_base = (self)->ab_entv[_abf_i].ab_base,    \
		              (ent).ab_size = _abf_i == (self)->ab_entc - 1       \
		                              ? (self)->ab_last                   \
		                              : (self)->ab_entv[_abf_i].ab_size), \
		     0))                                                          \
			;                                                             \
		else
#define AIO_PBUFFER_FOREACH(ent, self) \
	AIO_BUFFER_FOREACH(ent, self)
#define AIO_PBUFFER_FOREACH_N(ent, self) \
	AIO_BUFFER_FOREACH_N(ent, self)


#define AIO_BUFFER_GETENT(result, self, i)                   \
	((i) == 0                                                \
	 ? (void)((result) = (self)->ab_head)                    \
	 : (void)((result).ab_base = (self)->ab_entv[i].ab_base, \
	          (result).ab_size = (i) == (self)->ab_entc - 1  \
	                             ? (self)->ab_last           \
	                             : (self)->ab_entv[i].ab_size))
#define AIO_PBUFFER_GETENT(result, self, i) \
	AIO_BUFFER_GETENT(result, self, i)


/* Determine the number of bytes inside of the given buffer. */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) size_t NOTHROW(KCALL aio_buffer_size)(struct aio_buffer const *__restrict self);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) size_t NOTHROW(KCALL aio_pbuffer_size)(struct aio_pbuffer const *__restrict self);

/* Initialize a given AIO buffer as a view of memory of another. */
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL aio_buffer_init_view_before)(struct aio_buffer *__restrict self, struct aio_buffer const *__restrict base, uintptr_t end_offset);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL aio_pbuffer_init_view_before)(struct aio_pbuffer *__restrict self, struct aio_pbuffer const *__restrict base, uintptr_t end_offset);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL aio_buffer_init_view_after)(struct aio_buffer *__restrict self, struct aio_buffer const *__restrict base, uintptr_t start_offset);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL aio_pbuffer_init_view_after)(struct aio_pbuffer *__restrict self, struct aio_pbuffer const *__restrict base, uintptr_t start_offset);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL aio_buffer_init_view)(struct aio_buffer *__restrict self, struct aio_buffer const *__restrict base, uintptr_t start_offset, size_t num_bytes);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL aio_pbuffer_init_view)(struct aio_pbuffer *__restrict self, struct aio_pbuffer const *__restrict base, uintptr_t start_offset, size_t num_bytes);

/* Read/write/set data associated with AIO buffers. */
FUNDEF NONNULL((1)) void KCALL aio_buffer_memset(struct aio_buffer const *__restrict self, uintptr_t dst_offset, int byte, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) void KCALL aio_buffer_copyfrommem(struct aio_buffer const *__restrict self, uintptr_t dst_offset, USER CHECKED void const *__restrict src, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) void KCALL aio_buffer_copytomem(struct aio_buffer const *__restrict self, USER CHECKED void *__restrict dst, uintptr_t src_offset, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) void KCALL aio_buffer_copyfromphys(struct aio_buffer const *__restrict self, uintptr_t dst_offset, physaddr_t src, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) size_t NOTHROW(KCALL aio_buffer_copyfromphys_nopf)(struct aio_buffer const *__restrict self, uintptr_t dst_offset, physaddr_t src, size_t num_bytes);
FUNDEF NONNULL((1)) void KCALL aio_buffer_copytophys(struct aio_buffer const *__restrict self, physaddr_t dst, uintptr_t src_offset, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) size_t NOTHROW(KCALL aio_buffer_copytophys_nopf)(struct aio_buffer const *__restrict self, physaddr_t dst, uintptr_t src_offset, size_t num_bytes);
FUNDEF NONNULL((1)) void KCALL aio_buffer_copytovphys(struct aio_buffer const *__restrict src, struct aio_pbuffer const *__restrict dst, uintptr_t dst_offset, uintptr_t src_offset, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL aio_pbuffer_memset)(struct aio_pbuffer const *__restrict self, uintptr_t dst_offset, int byte, size_t num_bytes);
FUNDEF NONNULL((1)) void KCALL aio_pbuffer_copyfrommem(struct aio_pbuffer const *__restrict self, uintptr_t dst_offset, USER CHECKED void const *src, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) void KCALL aio_pbuffer_copytomem(struct aio_pbuffer const *__restrict self, USER CHECKED void *dst, uintptr_t src_offset, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) void KCALL aio_pbuffer_copytovmem(struct aio_pbuffer const *__restrict src, struct aio_buffer const *__restrict dst, uintptr_t dst_offset, uintptr_t src_offset, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL aio_pbuffer_copyfromphys)(struct aio_pbuffer const *__restrict self, uintptr_t dst_offset, physaddr_t src, size_t num_bytes);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL aio_pbuffer_copytophys)(struct aio_pbuffer const *__restrict self, physaddr_t dst, uintptr_t src_offset, size_t num_bytes);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL aio_pbuffer_copytovphys)(struct aio_pbuffer const *__restrict src, struct aio_pbuffer const *__restrict dst, uintptr_t dst_offset, uintptr_t src_offset, size_t num_bytes);

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_IOVEC_H */
