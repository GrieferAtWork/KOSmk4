/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
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

#define OFFSET_IOV_ENTRY_BASE 0
#define OFFSET_IOV_ENTRY_SIZE __SIZEOF_POINTER__
#define SIZEOF_IOV_ENTRY      (__SIZEOF_POINTER__ + __SIZEOF_SIZE_T__)

#define OFFSET_IOV_BUFFER_ENTC 0
#define OFFSET_IOV_BUFFER_ENTV __SIZEOF_SIZE_T__
#define OFFSET_IOV_BUFFER_HEAD (__SIZEOF_SIZE_T__ + __SIZEOF_POINTER__)
#define OFFSET_IOV_BUFFER_LAST (__SIZEOF_SIZE_T__ + __SIZEOF_POINTER__ + SIZEOF_IOV_ENTRY)
#define SIZEOF_IOV_BUFFER      ((__SIZEOF_SIZE_T__ * 2) + __SIZEOF_POINTER__ + SIZEOF_IOV_ENTRY)

#define OFFSET_IOV_PHYSENTRY_BASE 0
#if __SIZEOF_PHYSADDR_T__ > __SIZEOF_SIZE_T__
#define OFFSET_IOV_PHYSENTRY_SIZE __SIZEOF_PHYSADDR_T__
#define SIZEOF_IOV_PHYSENTRY      (2 * __SIZEOF_PHYSADDR_T__)
#else /* __SIZEOF_PHYSADDR_T__ > __SIZEOF_SIZE_T__ */
#define OFFSET_IOV_PHYSENTRY_SIZE __SIZEOF_SIZE_T__
#define SIZEOF_IOV_PHYSENTRY      (2 * __SIZEOF_SIZE_T__)
#endif /* __SIZEOF_PHYSADDR_T__ <= __SIZEOF_SIZE_T__ */

#define OFFSET_IOV_PHYSBUFFER_ENTC 0
#define OFFSET_IOV_PHYSBUFFER_ENTV __SIZEOF_SIZE_T__
#define OFFSET_IOV_PHYSBUFFER_HEAD (__SIZEOF_SIZE_T__ + __SIZEOF_POINTER__)
#define OFFSET_IOV_PHYSBUFFER_LAST (__SIZEOF_SIZE_T__ + __SIZEOF_POINTER__ + SIZEOF_IOV_PHYSENTRY)
#define __SIZEOF_IOV_PHYSBUFFER    ((__SIZEOF_SIZE_T__ * 2) + __SIZEOF_POINTER__ + SIZEOF_IOV_PHYSENTRY)
#if (__SIZEOF_IOV_PHYSBUFFER % __ALIGNOF_PHYSADDR_T__) != 0
#define SIZEOF_IOV_PHYSBUFFER ((__SIZEOF_IOV_PHYSBUFFER + (__ALIGNOF_PHYSADDR_T__ - 1)) & ~(__ALIGNOF_PHYSADDR_T__ - 1))
#else /* (__SIZEOF_IOV_PHYSBUFFER % __ALIGNOF_PHYSADDR_T__) != 0 */
#define SIZEOF_IOV_PHYSBUFFER __SIZEOF_IOV_PHYSBUFFER
#endif /* (__SIZEOF_IOV_PHYSBUFFER % __ALIGNOF_PHYSADDR_T__) == 0 */

#ifdef __CC__
DECL_BEGIN

#ifndef __iov_entry_defined
#define __iov_entry_defined
struct iov_entry {
	USER CHECKED byte_t *ive_base; /* [?..ive_size] Virtual base address of the buffer. */
	size_t               ive_size; /* Buffer size of `ive_base' (in bytes) */
};
#endif /* !__iov_entry_defined */

struct iov_buffer {
	size_t                  iv_entc; /* [!0] Number of entries. */
	struct iov_entry const *iv_entv; /* [1..iv_entc] Vector of entries. */
	struct iov_entry        iv_head; /* Override for `iv_entv[0]' */
	size_t                  iv_last; /* Override for `iv_entv[iv_entc - 1].ive_size' */
};
#define iov_buffer_initone(self, base, size)                   \
	((self)->iv_entc          = 1,                             \
	 (self)->iv_entv          = &(self)->iv_head,              \
	 (self)->iv_head.ive_base = (USER CHECKED byte_t *)(base), \
	 (self)->iv_head.ive_size = (size),                        \
	 (self)->iv_last          = (size))


struct iov_physentry {
	physaddr_t ive_base; /* [?..ive_size] Physical base address of the target buffer. */
	size_t     ive_size; /* Number of bytes that should be written at `ive_base' */
#if __SIZEOF_PHYSADDR_T__ > __SIZEOF_SIZE_T__
	byte_t    _ive_pad[__SIZEOF_PHYSADDR_T__ - __SIZEOF_SIZE_T__]; /* ... */
#endif /* __SIZEOF_PHYSADDR_T__ > __SIZEOF_SIZE_T__ */
};

struct iov_physbuffer {
	size_t                      iv_entc; /* [!0] Number of entries. */
	struct iov_physentry const *iv_entv; /* [1..iv_entc] Vector of entries. */
	struct iov_physentry        iv_head; /* Override for `iv_entv[0]' */
	size_t                      iv_last; /* Override for `iv_entv[iv_entc - 1].ive_size' */
#if (__SIZEOF_IOV_PHYSBUFFER % __ALIGNOF_PHYSADDR_T__) != 0
	__byte_t _iv_pad[__ALIGNOF_PHYSADDR_T__ - (__SIZEOF_IOV_PHYSBUFFER % __ALIGNOF_PHYSADDR_T__)]; /* ... */
#endif /* (__SIZEOF_IOV_PHYSBUFFER % __ALIGNOF_PHYSADDR_T__) != 0 */
};
#define iov_physbuffer_initone(self, base, size)               \
	((self)->iv_entc          = 1,                             \
	 (self)->iv_entv          = &(self)->iv_head,              \
	 (self)->iv_head.ive_base = (USER CHECKED byte_t *)(base), \
	 (self)->iv_head.ive_size = (size),                        \
	 (self)->iv_last          = (size))


/* >> struct iov_entry ent;
 * >> IOV_BUFFER_FOREACH(ent, buf) {
 * >>     ...
 * >> }
 */
#define IOV_BUFFER_FOREACH(ent, self)                                       \
	for (size_t _abf_i = 0; _abf_i < (self)->iv_entc; ++_abf_i)             \
		if (((_abf_i) == 0                                                  \
		     ? (void)((ent) = (self)->iv_head)                              \
		     : (void)((ent).ive_base = (self)->iv_entv[_abf_i].ive_base,    \
		              (ent).ive_size = _abf_i == (self)->iv_entc - 1        \
		                               ? (self)->iv_last                    \
		                               : (self)->iv_entv[_abf_i].ive_size), \
		     0))                                                            \
			;                                                               \
		else
#define IOV_BUFFER_FOREACH_N(ent, self)                                     \
	for (size_t _abf_i = 0;; ++_abf_i)                                      \
		if (((__hybrid_assert(_abf_i < (self)->iv_entc)),                   \
		     (_abf_i) == 0                                                  \
		     ? (void)((ent) = (self)->iv_head)                              \
		     : (void)((ent).ive_base = (self)->iv_entv[_abf_i].ive_base,    \
		              (ent).ive_size = _abf_i == (self)->iv_entc - 1        \
		                               ? (self)->iv_last                    \
		                               : (self)->iv_entv[_abf_i].ive_size), \
		     0))                                                            \
			;                                                               \
		else
#define IOV_PHYSBUFFER_FOREACH(ent, self) \
	IOV_BUFFER_FOREACH(ent, self)
#define IOV_PHYSBUFFER_FOREACH_N(ent, self) \
	IOV_BUFFER_FOREACH_N(ent, self)


#define IOV_BUFFER_GETENT(result, self, i)                     \
	((i) == 0                                                  \
	 ? (void)((result) = (self)->iv_head)                      \
	 : (void)((result).ive_base = (self)->iv_entv[i].ive_base, \
	          (result).ive_size = (i) == (self)->iv_entc - 1   \
	                              ? (self)->iv_last            \
	                              : (self)->iv_entv[i].ive_size))
#define IOV_PHYSBUFFER_GETENT(result, self, i) \
	IOV_BUFFER_GETENT(result, self, i)


/* Determine the number of bytes inside of the given buffer. */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) size_t NOTHROW(KCALL iov_buffer_size)(struct iov_buffer const *__restrict self);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) size_t NOTHROW(KCALL iov_physbuffer_size)(struct iov_physbuffer const *__restrict self);

/* Initialize a given IOV buffer as a view of memory of another. */
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL iov_buffer_init_view_before)(struct iov_buffer *__restrict self, struct iov_buffer const *__restrict base, uintptr_t end_offset);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL iov_buffer_init_view_after)(struct iov_buffer *__restrict self, struct iov_buffer const *__restrict base, uintptr_t start_offset);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL iov_buffer_init_view)(struct iov_buffer *__restrict self, struct iov_buffer const *__restrict base, uintptr_t start_offset, size_t num_bytes);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL iov_physbuffer_init_view_before)(struct iov_physbuffer *__restrict self, struct iov_physbuffer const *__restrict base, uintptr_t end_offset);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL iov_physbuffer_init_view_after)(struct iov_physbuffer *__restrict self, struct iov_physbuffer const *__restrict base, uintptr_t start_offset);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL iov_physbuffer_init_view)(struct iov_physbuffer *__restrict self, struct iov_physbuffer const *__restrict base, uintptr_t start_offset, size_t num_bytes);

/* Read/write/set data associated with IOV buffers. */
FUNDEF NONNULL((1)) void KCALL iov_buffer_memset(struct iov_buffer const *__restrict self, uintptr_t dst_offset, int byte, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) void KCALL iov_buffer_copyfrommem(struct iov_buffer const *__restrict self, uintptr_t dst_offset, USER CHECKED void const *__restrict src, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) void KCALL iov_buffer_copytomem(struct iov_buffer const *__restrict self, USER CHECKED void *__restrict dst, uintptr_t src_offset, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) void KCALL iov_buffer_copyfromphys(struct iov_buffer const *__restrict self, uintptr_t dst_offset, physaddr_t src, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) size_t NOTHROW(KCALL iov_buffer_copyfromphys_nopf)(struct iov_buffer const *__restrict self, uintptr_t dst_offset, physaddr_t src, size_t num_bytes);
FUNDEF NONNULL((1)) void KCALL iov_buffer_copytophys(struct iov_buffer const *__restrict self, physaddr_t dst, uintptr_t src_offset, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) size_t NOTHROW(KCALL iov_buffer_copytophys_nopf)(struct iov_buffer const *__restrict self, physaddr_t dst, uintptr_t src_offset, size_t num_bytes);
FUNDEF NONNULL((1)) void KCALL iov_buffer_copytovmem(struct iov_buffer const *__restrict src, struct iov_buffer const *__restrict dst, uintptr_t dst_offset, uintptr_t src_offset, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) void KCALL iov_buffer_copytovphys(struct iov_buffer const *__restrict src, struct iov_physbuffer const *__restrict dst, uintptr_t dst_offset, uintptr_t src_offset, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL iov_physbuffer_memset)(struct iov_physbuffer const *__restrict self, uintptr_t dst_offset, int byte, size_t num_bytes);
FUNDEF NONNULL((1)) void KCALL iov_physbuffer_copyfrommem(struct iov_physbuffer const *__restrict self, uintptr_t dst_offset, USER CHECKED void const *src, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) void KCALL iov_physbuffer_copytomem(struct iov_physbuffer const *__restrict self, USER CHECKED void *dst, uintptr_t src_offset, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NONNULL((1)) void KCALL iov_physbuffer_copytovmem(struct iov_physbuffer const *__restrict src, struct iov_buffer const *__restrict dst, uintptr_t dst_offset, uintptr_t src_offset, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL iov_physbuffer_copyfromphys)(struct iov_physbuffer const *__restrict self, uintptr_t dst_offset, physaddr_t src, size_t num_bytes);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL iov_physbuffer_copytophys)(struct iov_physbuffer const *__restrict self, physaddr_t dst, uintptr_t src_offset, size_t num_bytes);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL iov_physbuffer_copytovphys)(struct iov_physbuffer const *__restrict src, struct iov_physbuffer const *__restrict dst, uintptr_t dst_offset, uintptr_t src_offset, size_t num_bytes);

#ifdef __cplusplus
/* Helper overloads */
extern "C++" {
FUNDEF NOBLOCK WUNUSED NONNULL((1)) size_t NOTHROW(KCALL iov_buffer_size)(struct iov_physbuffer const *__restrict self) ASMNAME("iov_physbuffer_size");
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL iov_buffer_init_view_before)(struct iov_physbuffer *__restrict self, struct iov_physbuffer const *__restrict base, uintptr_t end_offset) ASMNAME("iov_physbuffer_init_view_before");
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL iov_buffer_init_view_after)(struct iov_physbuffer *__restrict self, struct iov_physbuffer const *__restrict base, uintptr_t start_offset) ASMNAME("iov_physbuffer_init_view_after");
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(KCALL iov_buffer_init_view)(struct iov_physbuffer *__restrict self, struct iov_physbuffer const *__restrict base, uintptr_t start_offset, size_t num_bytes) ASMNAME("iov_physbuffer_init_view");
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL iov_buffer_memset)(struct iov_physbuffer const *__restrict self, uintptr_t dst_offset, int byte, size_t num_bytes) ASMNAME("iov_physbuffer_memset");
FUNDEF NONNULL((1)) void KCALL iov_buffer_copyfrommem(struct iov_physbuffer const *__restrict self, uintptr_t dst_offset, USER CHECKED void const *src, size_t num_bytes) THROWS(E_SEGFAULT) ASMNAME("iov_physbuffer_copyfrommem");
FUNDEF NONNULL((1)) void KCALL iov_buffer_copytomem(struct iov_physbuffer const *__restrict self, USER CHECKED void *dst, uintptr_t src_offset, size_t num_bytes) THROWS(E_SEGFAULT) ASMNAME("iov_physbuffer_copytomem");
FUNDEF NONNULL((1)) void KCALL iov_buffer_copytovmem(struct iov_physbuffer const *__restrict src, struct iov_buffer const *__restrict dst, uintptr_t dst_offset, uintptr_t src_offset, size_t num_bytes) THROWS(E_SEGFAULT) ASMNAME("iov_physbuffer_copytovmem");
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL iov_buffer_copyfromphys)(struct iov_physbuffer const *__restrict self, uintptr_t dst_offset, physaddr_t src, size_t num_bytes) ASMNAME("iov_physbuffer_copyfromphys");
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL iov_buffer_copytophys)(struct iov_physbuffer const *__restrict self, physaddr_t dst, uintptr_t src_offset, size_t num_bytes) ASMNAME("iov_physbuffer_copytophys");
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL iov_buffer_copytovphys)(struct iov_physbuffer const *__restrict src, struct iov_physbuffer const *__restrict dst, uintptr_t dst_offset, uintptr_t src_offset, size_t num_bytes) ASMNAME("iov_physbuffer_copytovphys");
} /* extern "C++" */
#endif /* __cplusplus */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_IOVEC_H */
