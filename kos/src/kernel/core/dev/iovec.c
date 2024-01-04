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
#ifndef GUARD_KERNEL_SRC_DEV_IOVEC_C
#define GUARD_KERNEL_SRC_DEV_IOVEC_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/iovec.h>
#include <kernel/mman/phys.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/* Verify static offset constants. */
static_assert(offsetof(struct iov_entry, ive_base) == OFFSET_IOV_ENTRY_BASE);
static_assert(offsetof(struct iov_entry, ive_size) == OFFSET_IOV_ENTRY_SIZE);
static_assert(sizeof(struct iov_entry) == SIZEOF_IOV_ENTRY);
static_assert(offsetof(struct iov_buffer, iv_entc) == OFFSET_IOV_BUFFER_ENTC);
static_assert(offsetof(struct iov_buffer, iv_entv) == OFFSET_IOV_BUFFER_ENTV);
static_assert(offsetof(struct iov_buffer, iv_head) == OFFSET_IOV_BUFFER_HEAD);
static_assert(offsetof(struct iov_buffer, iv_last) == OFFSET_IOV_BUFFER_LAST);
static_assert(sizeof(struct iov_buffer) == SIZEOF_IOV_BUFFER);
static_assert(offsetof(struct iov_physentry, ive_base) == OFFSET_IOV_PHYSENTRY_BASE);
static_assert(offsetof(struct iov_physentry, ive_size) == OFFSET_IOV_PHYSENTRY_SIZE);
static_assert(sizeof(struct iov_physentry) == SIZEOF_IOV_PHYSENTRY);
static_assert(offsetof(struct iov_physbuffer, iv_entc) == OFFSET_IOV_PHYSBUFFER_ENTC);
static_assert(offsetof(struct iov_physbuffer, iv_entv) == OFFSET_IOV_PHYSBUFFER_ENTV);
static_assert(offsetof(struct iov_physbuffer, iv_head) == OFFSET_IOV_PHYSBUFFER_HEAD);
static_assert(offsetof(struct iov_physbuffer, iv_last) == OFFSET_IOV_PHYSBUFFER_LAST);
static_assert(sizeof(struct iov_physbuffer) == SIZEOF_IOV_PHYSBUFFER);




/* Read/write/set data associated with IOV buffers. */
PUBLIC ATTR_IN(1) void KCALL
iov_buffer_copyfromphys(struct iov_buffer const *__restrict self,
                        uintptr_t dst_offset, physaddr_t src, size_t num_bytes)
		THROWS(E_SEGFAULT) {
	struct iov_entry ent;
	IOV_BUFFER_FOREACH_N(ent, self) {
		if (dst_offset >= ent.ive_size) {
			dst_offset -= ent.ive_size;
			continue;
		}
		if (ent.ive_size > num_bytes)
			ent.ive_size = num_bytes;
		copyfromphys(ent.ive_base + dst_offset, src, ent.ive_size);
		if (ent.ive_size >= num_bytes)
			break;
		src += ent.ive_size;
		num_bytes -= ent.ive_size;
		dst_offset = 0;
	}
}

PUBLIC ATTR_IN(1) size_t
NOTHROW(KCALL iov_buffer_copyfromphys_nopf)(struct iov_buffer const *__restrict self,
                                            uintptr_t dst_offset, physaddr_t src, size_t num_bytes) {
	size_t error;
	struct iov_entry ent;
	IOV_BUFFER_FOREACH_N(ent, self) {
		if (dst_offset >= ent.ive_size) {
			dst_offset -= ent.ive_size;
			continue;
		}
		if (ent.ive_size > num_bytes)
			ent.ive_size = num_bytes;
		error = copyfromphys_nopf(ent.ive_base + dst_offset, src, ent.ive_size);
		if unlikely(error != 0)
			return error + (num_bytes - ent.ive_size);
		if (ent.ive_size >= num_bytes)
			break;
		src += ent.ive_size;
		num_bytes -= ent.ive_size;
		dst_offset = 0;
	}
	return 0;
}

PUBLIC ATTR_IN(1) void KCALL
iov_buffer_copytophys(struct iov_buffer const *__restrict self,
                      physaddr_t dst, uintptr_t src_offset, size_t num_bytes)
		THROWS(E_SEGFAULT) {
	struct iov_entry ent;
	IOV_BUFFER_FOREACH_N(ent, self) {
		if (src_offset != 0) {
			if (src_offset >= ent.ive_size) {
				src_offset -= ent.ive_size;
				continue;
			}
			ent.ive_base += src_offset;
			ent.ive_size -= src_offset;
			src_offset = 0;
		}
		if (ent.ive_size > num_bytes)
			ent.ive_size = num_bytes;
		copytophys(dst, ent.ive_base, ent.ive_size);
		if (ent.ive_size >= num_bytes)
			break;
		dst += ent.ive_size;
		num_bytes -= ent.ive_size;
	}
}

PUBLIC ATTR_IN(1) size_t
NOTHROW(KCALL iov_buffer_copytophys_nopf)(struct iov_buffer const *__restrict self,
                                          physaddr_t dst, uintptr_t src_offset, size_t num_bytes) {
	size_t error;
	struct iov_entry ent;
	IOV_BUFFER_FOREACH_N(ent, self) {
		if (src_offset != 0) {
			if (src_offset >= ent.ive_size) {
				src_offset -= ent.ive_size;
				continue;
			}
			ent.ive_base += src_offset;
			ent.ive_size -= src_offset;
			src_offset = 0;
		}
		if (ent.ive_size > num_bytes)
			ent.ive_size = num_bytes;
		error = copytophys_nopf(dst, ent.ive_base, ent.ive_size);
		if unlikely(error != 0)
			return error + (num_bytes - ent.ive_size);
		if (ent.ive_size >= num_bytes)
			break;
		dst += ent.ive_size;
		num_bytes -= ent.ive_size;
	}
	return 0;
}

PUBLIC ATTR_IN(1) void KCALL
iov_buffer_memset(struct iov_buffer const *__restrict self,
                  uintptr_t dst_offset,
                  int byte, size_t num_bytes)
		THROWS(E_SEGFAULT) {
	struct iov_entry ent;
	IOV_BUFFER_FOREACH_N(ent, self) {
		if (dst_offset >= ent.ive_size) {
			dst_offset -= ent.ive_size;
			continue;
		}
		if (ent.ive_size > num_bytes)
			ent.ive_size = num_bytes;
		memset(ent.ive_base + dst_offset,
		       byte, ent.ive_size);
		if (ent.ive_size >= num_bytes)
			break;
		num_bytes -= ent.ive_size;
		dst_offset = 0;
	}
}

PUBLIC NOBLOCK ATTR_IN(1) void
NOTHROW(KCALL iov_physbuffer_memset)(struct iov_physbuffer const *__restrict self,
                                     uintptr_t dst_offset, int byte, size_t num_bytes) {
	struct iov_physentry ent;
	IOV_PHYSBUFFER_FOREACH_N(ent, self) {
		if (dst_offset >= ent.ive_size) {
			dst_offset -= ent.ive_size;
			continue;
		}
		if (ent.ive_size > num_bytes)
			ent.ive_size = num_bytes;
		memsetphys(ent.ive_base + dst_offset, byte, ent.ive_size);
		if (ent.ive_size >= num_bytes)
			break;
		num_bytes -= ent.ive_size;
		dst_offset = 0;
	}
}

PUBLIC ATTR_IN(1) void KCALL
iov_buffer_copyfrommem(struct iov_buffer const *__restrict self, uintptr_t dst_offset,
                       NCX void const *__restrict src, size_t num_bytes)
		THROWS(E_SEGFAULT) {
	struct iov_entry ent;
	IOV_BUFFER_FOREACH_N(ent, self) {
		if (dst_offset >= ent.ive_size) {
			dst_offset -= ent.ive_size;
			continue;
		}
		if (ent.ive_size > num_bytes)
			ent.ive_size = num_bytes;
		memcpy(ent.ive_base + dst_offset, src, ent.ive_size);
		if (ent.ive_size >= num_bytes)
			break;
		src = (byte_t const *)src + ent.ive_size;
		num_bytes -= ent.ive_size;
		dst_offset = 0;
	}
}

PUBLIC ATTR_IN(1) void KCALL
iov_physbuffer_copyfrommem(struct iov_physbuffer const *__restrict self,
                           uintptr_t dst_offset,
                           NCX void const *src, size_t num_bytes)
		THROWS(E_SEGFAULT) {
	struct iov_physentry ent;
	IOV_PHYSBUFFER_FOREACH_N(ent, self) {
		if (dst_offset >= ent.ive_size) {
			dst_offset -= ent.ive_size;
			continue;
		}
		if (ent.ive_size > num_bytes)
			ent.ive_size = num_bytes;
		copytophys(ent.ive_base + dst_offset, src, ent.ive_size);
		if (ent.ive_size >= num_bytes)
			break;
		src = (byte_t const *)src + ent.ive_size;
		num_bytes -= ent.ive_size;
		dst_offset = 0;
	}
}

PUBLIC ATTR_IN(1) void KCALL
iov_buffer_copytomem(struct iov_buffer const *__restrict self,
                     NCX void *__restrict dst,
                     uintptr_t src_offset, size_t num_bytes)
		THROWS(E_SEGFAULT) {
	struct iov_entry ent;
	IOV_BUFFER_FOREACH_N(ent, self) {
		if (src_offset != 0) {
			if (src_offset >= ent.ive_size) {
				src_offset -= ent.ive_size;
				continue;
			}
			ent.ive_base += src_offset;
			ent.ive_size -= src_offset;
			src_offset = 0;
		}
		if (ent.ive_size > num_bytes)
			ent.ive_size = num_bytes;
		memcpy(dst, ent.ive_base, ent.ive_size);
		if (ent.ive_size >= num_bytes)
			break;
		dst = (byte_t *)dst + ent.ive_size;
		num_bytes -= ent.ive_size;
	}
}

PUBLIC ATTR_IN(1) void KCALL
iov_physbuffer_copytomem(struct iov_physbuffer const *__restrict self,
                         NCX void *dst,
                         uintptr_t src_offset, size_t num_bytes)
       THROWS(E_SEGFAULT) {
	struct iov_physentry ent;
	IOV_PHYSBUFFER_FOREACH_N(ent, self) {
		if (src_offset != 0) {
			if (src_offset >= ent.ive_size) {
				src_offset -= ent.ive_size;
				continue;
			}
			ent.ive_base += src_offset;
			ent.ive_size -= src_offset;
			src_offset = 0;
		}
		if (ent.ive_size > num_bytes)
			ent.ive_size = num_bytes;
		copyfromphys(dst, ent.ive_base, ent.ive_size);
		if (ent.ive_size >= num_bytes)
			break;
		dst = (byte_t *)dst + ent.ive_size;
		num_bytes -= ent.ive_size;
	}
}

PUBLIC NOBLOCK ATTR_IN(1) void
NOTHROW(KCALL iov_physbuffer_copyfromphys)(struct iov_physbuffer const *__restrict self,
                                           uintptr_t dst_offset,
                                           physaddr_t src, size_t num_bytes) {
	struct iov_physentry ent;
	IOV_PHYSBUFFER_FOREACH_N(ent, self) {
		if (dst_offset != 0) {
			if (dst_offset >= ent.ive_size) {
				dst_offset -= ent.ive_size;
				continue;
			}
			ent.ive_base += dst_offset;
			ent.ive_size -= dst_offset;
			dst_offset = 0;
		}
		if (ent.ive_size > num_bytes)
			ent.ive_size = num_bytes;
		copyinphys(ent.ive_base, src, ent.ive_size);
		if (ent.ive_size >= num_bytes)
			break;
		src += ent.ive_size;
		num_bytes -= ent.ive_size;
	}
}

PUBLIC NOBLOCK ATTR_IN(1) void
NOTHROW(KCALL iov_physbuffer_copytophys)(struct iov_physbuffer const *__restrict self,
                                         physaddr_t dst,
                                         uintptr_t src_offset, size_t num_bytes) {
	struct iov_physentry ent;
	IOV_PHYSBUFFER_FOREACH_N(ent, self) {
		if (src_offset != 0) {
			if (src_offset >= ent.ive_size) {
				src_offset -= ent.ive_size;
				continue;
			}
			ent.ive_base += src_offset;
			ent.ive_size -= src_offset;
			src_offset = 0;
		}
		if (ent.ive_size > num_bytes)
			ent.ive_size = num_bytes;
		copyinphys(dst, ent.ive_base, ent.ive_size);
		if (ent.ive_size >= num_bytes)
			break;
		dst += ent.ive_size;
		num_bytes -= ent.ive_size;
	}
}

PUBLIC ATTR_IN(1) void KCALL
iov_buffer_copytovmem(struct iov_buffer const *__restrict src,
                      struct iov_buffer const *__restrict dst,
                      uintptr_t dst_offset, uintptr_t src_offset,
                      size_t num_bytes)
		THROWS(E_SEGFAULT) {
	struct iov_entry dstent;
	assert(iov_buffer_size(src) >= src_offset + num_bytes);
	assert(iov_buffer_size(dst) >= dst_offset + num_bytes);
	IOV_BUFFER_FOREACH_N(dstent, dst) {
		size_t partcopy;
		if (dst_offset != 0) {
			if (dst_offset >= dstent.ive_size) {
				dst_offset -= dstent.ive_size;
				continue;
			}
			dstent.ive_base += dst_offset;
			dstent.ive_size -= dst_offset;
			dst_offset = 0;
		}
		partcopy = dstent.ive_size;
		if (partcopy > num_bytes)
			partcopy = num_bytes;
		iov_buffer_copytomem(src,
		                     dstent.ive_base,
		                     src_offset,
		                     partcopy);
		if (partcopy >= num_bytes)
			break;
		num_bytes  -= partcopy;
		src_offset += partcopy;
	}
}

PUBLIC ATTR_IN(1) void KCALL
iov_buffer_copytovphys(struct iov_buffer const *__restrict src,
                       struct iov_physbuffer const *__restrict dst,
                       uintptr_t dst_offset, uintptr_t src_offset,
                       size_t num_bytes)
		THROWS(E_SEGFAULT) {
	struct iov_physentry dstent;
	assert(iov_buffer_size(src) >= src_offset + num_bytes);
	assert(iov_physbuffer_size(dst) >= dst_offset + num_bytes);
	IOV_PHYSBUFFER_FOREACH_N(dstent, dst) {
		size_t partcopy;
		if (dst_offset != 0) {
			if (dst_offset >= dstent.ive_size) {
				dst_offset -= dstent.ive_size;
				continue;
			}
			dstent.ive_base += dst_offset;
			dstent.ive_size -= dst_offset;
			dst_offset = 0;
		}
		partcopy = dstent.ive_size;
		if (partcopy > num_bytes)
			partcopy = num_bytes;
		iov_buffer_copytophys(src,
		                      dstent.ive_base,
		                      src_offset,
		                      partcopy);
		if (partcopy >= num_bytes)
			break;
		num_bytes  -= partcopy;
		src_offset += partcopy;
	}
}

PUBLIC ATTR_IN(1) void KCALL
iov_physbuffer_copytovmem(struct iov_physbuffer const *__restrict src,
                          struct iov_buffer const *__restrict dst,
                          uintptr_t dst_offset,
                          uintptr_t src_offset,
                          size_t num_bytes)
		THROWS(E_SEGFAULT) {
	struct iov_entry dstent;
	assert(iov_physbuffer_size(src) >= src_offset + num_bytes);
	assert(iov_buffer_size(dst) >= dst_offset + num_bytes);
	IOV_BUFFER_FOREACH_N(dstent, dst) {
		size_t partcopy;
		if (dst_offset != 0) {
			if (dst_offset >= dstent.ive_size) {
				dst_offset -= dstent.ive_size;
				continue;
			}
			dstent.ive_base += dst_offset;
			dstent.ive_size -= dst_offset;
			dst_offset = 0;
		}
		partcopy = dstent.ive_size;
		if (partcopy > num_bytes)
			partcopy = num_bytes;
		iov_physbuffer_copytomem(src,
		                      dstent.ive_base,
		                      src_offset,
		                      partcopy);
		if (partcopy >= num_bytes)
			break;
		num_bytes  -= partcopy;
		src_offset += partcopy;
	}
}

PUBLIC NOBLOCK ATTR_IN(1) void
NOTHROW(KCALL iov_physbuffer_copytovphys)(struct iov_physbuffer const *__restrict src,
                                          struct iov_physbuffer const *__restrict dst,
                                          uintptr_t dst_offset,
                                          uintptr_t src_offset,
                                          size_t num_bytes) {
	struct iov_physentry dstent;
	assert(iov_physbuffer_size(src) >= src_offset + num_bytes);
	assert(iov_physbuffer_size(dst) >= dst_offset + num_bytes);
	IOV_PHYSBUFFER_FOREACH_N(dstent, dst) {
		size_t partcopy;
		if (dst_offset != 0) {
			if (dst_offset >= dstent.ive_size) {
				dst_offset -= dstent.ive_size;
				continue;
			}
			dstent.ive_base += dst_offset;
			dstent.ive_size -= dst_offset;
			dst_offset = 0;
		}
		partcopy = dstent.ive_size;
		if (partcopy > num_bytes)
			partcopy = num_bytes;
		iov_physbuffer_copytophys(src,
		                       dstent.ive_base,
		                       src_offset,
		                       partcopy);
		if (partcopy >= num_bytes)
			break;
		num_bytes  -= partcopy;
		src_offset += partcopy;
	}
}

DECL_END



#undef IOV_BUFFER_BINARY_COMPATIBLE_IOV_PHYSBUFFER
#if (OFFSET_IOV_BUFFER_LAST == OFFSET_IOV_PHYSBUFFER_LAST && \
     OFFSET_IOV_BUFFER_HEAD == OFFSET_IOV_PHYSBUFFER_HEAD && \
     OFFSET_IOV_BUFFER_ENTC == OFFSET_IOV_PHYSBUFFER_ENTC && \
     SIZEOF_IOV_ENTRY == SIZEOF_IOV_PHYSENTRY &&             \
     OFFSET_IOV_ENTRY_SIZE == OFFSET_IOV_PHYSENTRY_SIZE)
#define IOV_BUFFER_BINARY_COMPATIBLE_IOV_PHYSBUFFER 1
#endif /* BINARY_COMPATIBLE(iov_physbuffer, iov_buffer)... */


#ifndef __INTELLISENSE__
#define DEFINE_FOR_IOV_BUFFER 1
#include "iovec-aio-buffer.c.inl"

#ifdef IOV_BUFFER_BINARY_COMPATIBLE_IOV_PHYSBUFFER
DECL_BEGIN

DEFINE_PUBLIC_ALIAS(iov_physbuffer_size, iov_buffer_size);
DEFINE_PUBLIC_ALIAS(iov_physbuffer_init_view_before, iov_buffer_init_view_before);
DEFINE_PUBLIC_ALIAS(iov_physbuffer_init_view_after, iov_buffer_init_view_after);
DEFINE_PUBLIC_ALIAS(iov_physbuffer_init_view, iov_buffer_init_view);

DECL_END
#else /* IOV_BUFFER_BINARY_COMPATIBLE_IOV_PHYSBUFFER */
#define DEFINE_FOR_IOV_PHYSBUFFER 1
#include "iovec-aio-buffer.c.inl"
#endif /* !IOV_BUFFER_BINARY_COMPATIBLE_IOV_PHYSBUFFER */
#endif /* !__INTELLISENSE__ */


#endif /* !GUARD_KERNEL_SRC_DEV_IOVEC_C */
