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
#ifndef GUARD_KERNEL_SRC_DEV_IOVEC_C
#define GUARD_KERNEL_SRC_DEV_IOVEC_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/iovec.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

/* Read/write/set data associated with AIO buffers. */
PUBLIC NONNULL((1)) void KCALL
aio_buffer_copyfromphys(struct aio_buffer const *__restrict self,
                        uintptr_t dst_offset, vm_phys_t src, size_t num_bytes)
		THROWS(E_SEGFAULT) {
	struct aio_buffer_entry ent;
	AIO_BUFFER_FOREACH_N(ent, self) {
		if (dst_offset >= ent.ab_size) {
			dst_offset -= ent.ab_size;
			continue;
		}
		if (ent.ab_size > num_bytes)
			ent.ab_size = num_bytes;
		vm_copyfromphys((byte_t *)ent.ab_base + dst_offset, src, ent.ab_size);
		if (ent.ab_size >= num_bytes)
			break;
		src += ent.ab_size;
		num_bytes -= ent.ab_size;
		dst_offset = 0;
	}
}

PUBLIC NONNULL((1)) void KCALL
aio_buffer_copytophys(struct aio_buffer const *__restrict self,
                      vm_phys_t dst, uintptr_t src_offset, size_t num_bytes)
		THROWS(E_SEGFAULT) {
	struct aio_buffer_entry ent;
	AIO_BUFFER_FOREACH_N(ent, self) {
		if (src_offset >= ent.ab_size) {
			src_offset -= ent.ab_size;
			continue;
		}
		if (ent.ab_size > num_bytes)
			ent.ab_size = num_bytes;
		vm_copytophys(dst, (byte_t *)ent.ab_base + src_offset, ent.ab_size);
		if (ent.ab_size >= num_bytes)
			break;
		dst += ent.ab_size;
		num_bytes -= ent.ab_size;
		src_offset = 0;
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_pbuffer_memset)(struct aio_pbuffer const *__restrict self,
                                  uintptr_t dst_offset, int byte, size_t num_bytes) {
	struct aio_pbuffer_entry ent;
	AIO_PBUFFER_FOREACH_N(ent, self) {
		if (dst_offset >= ent.ab_size) {
			dst_offset -= ent.ab_size;
			continue;
		}
		if (ent.ab_size > num_bytes)
			ent.ab_size = num_bytes;
		vm_memsetphys(ent.ab_base + dst_offset, byte, ent.ab_size);
		if (ent.ab_size >= num_bytes)
			break;
		num_bytes -= ent.ab_size;
		dst_offset = 0;
	}
}

PUBLIC NONNULL((1)) void KCALL
aio_pbuffer_copyfrommem(struct aio_pbuffer const *__restrict self,
                        uintptr_t dst_offset,
                        USER CHECKED void const *src, size_t num_bytes)
		THROWS(E_SEGFAULT) {
	struct aio_pbuffer_entry ent;
	AIO_PBUFFER_FOREACH_N(ent, self) {
		if (dst_offset >= ent.ab_size) {
			dst_offset -= ent.ab_size;
			continue;
		}
		if (ent.ab_size > num_bytes)
			ent.ab_size = num_bytes;
		vm_copytophys(ent.ab_base + dst_offset, src, ent.ab_size);
		if (ent.ab_size >= num_bytes)
			break;
		src = (byte_t *)src + ent.ab_size;
		num_bytes -= ent.ab_size;
		dst_offset = 0;
	}
}

PUBLIC NONNULL((1)) void KCALL
aio_pbuffer_copytomem(struct aio_pbuffer const *__restrict self,
                      USER CHECKED void *dst,
                      uintptr_t src_offset, size_t num_bytes)
       THROWS(E_SEGFAULT) {
	struct aio_pbuffer_entry ent;
	AIO_PBUFFER_FOREACH_N(ent, self) {
		if (src_offset >= ent.ab_size) {
			src_offset -= ent.ab_size;
			continue;
		}
		if (ent.ab_size > num_bytes)
			ent.ab_size = num_bytes;
		vm_copyfromphys(dst, (vm_phys_t)(ent.ab_base + src_offset), ent.ab_size);
		if (ent.ab_size >= num_bytes)
			break;
		dst = (byte_t *)dst + ent.ab_size;
		num_bytes -= ent.ab_size;
		src_offset = 0;
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_pbuffer_copyfromphys)(struct aio_pbuffer const *__restrict self,
                                        uintptr_t dst_offset,
                                        vm_phys_t src, size_t num_bytes) {
	struct aio_pbuffer_entry ent;
	AIO_PBUFFER_FOREACH_N(ent, self) {
		if (dst_offset >= ent.ab_size) {
			dst_offset -= ent.ab_size;
			continue;
		}
		if (ent.ab_size > num_bytes)
			ent.ab_size = num_bytes;
		vm_copyinphys(ent.ab_base + dst_offset, src, ent.ab_size);
		if (ent.ab_size >= num_bytes)
			break;
		src += ent.ab_size;
		num_bytes -= ent.ab_size;
		dst_offset = 0;
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_pbuffer_copytophys)(struct aio_pbuffer const *__restrict self,
                                      vm_phys_t dst,
                                      uintptr_t src_offset, size_t num_bytes) {
	struct aio_pbuffer_entry ent;
	AIO_PBUFFER_FOREACH_N(ent, self) {
		if (src_offset >= ent.ab_size) {
			src_offset -= ent.ab_size;
			continue;
		}
		if (ent.ab_size > num_bytes)
			ent.ab_size = num_bytes;
		vm_copyinphys(dst, ent.ab_base + src_offset, ent.ab_size);
		if (ent.ab_size >= num_bytes)
			break;
		dst += ent.ab_size;
		num_bytes -= ent.ab_size;
		src_offset = 0;
	}
}

PUBLIC NONNULL((1)) void KCALL
aio_buffer_copytovphys(struct aio_buffer const *__restrict src,
                       struct aio_pbuffer const *__restrict dst,
                       uintptr_t dst_offset,
                       uintptr_t src_offset,
                       size_t num_bytes)
		THROWS(E_SEGFAULT) {
	struct aio_pbuffer_entry dstent;
	assert(aio_buffer_size(src) >= src_offset + num_bytes);
	assert(aio_pbuffer_size(dst) >= dst_offset + num_bytes);
	AIO_PBUFFER_FOREACH_N(dstent, dst) {
		size_t partcopy;
		if (dst_offset != 0) {
			if (dst_offset >= dstent.ab_size) {
				dst_offset -= dstent.ab_size;
				continue;
			}
			dstent.ab_base += dst_offset;
			dstent.ab_size -= dst_offset;
			dst_offset = 0;
		}
		partcopy = dstent.ab_size;
		if (partcopy > num_bytes)
			partcopy = num_bytes;
		aio_buffer_copytophys(src,
		                      dstent.ab_base,
		                      src_offset,
		                      partcopy);
		if (partcopy >= num_bytes)
			break;
		num_bytes  -= partcopy;
		src_offset += partcopy;
	}
}

PUBLIC NONNULL((1)) void KCALL
aio_pbuffer_copytovmem(struct aio_pbuffer const *__restrict src,
                       struct aio_buffer const *__restrict dst,
                       uintptr_t dst_offset,
                       uintptr_t src_offset,
                       size_t num_bytes)
		THROWS(E_SEGFAULT) {
	struct aio_buffer_entry dstent;
	assert(aio_pbuffer_size(src) >= src_offset + num_bytes);
	assert(aio_buffer_size(dst) >= dst_offset + num_bytes);
	AIO_BUFFER_FOREACH_N(dstent, dst) {
		size_t partcopy;
		if (dst_offset != 0) {
			if (dst_offset >= dstent.ab_size) {
				dst_offset -= dstent.ab_size;
				continue;
			}
			dstent.ab_base = (byte_t *)dstent.ab_base + dst_offset;
			dstent.ab_size -= dst_offset;
			dst_offset = 0;
		}
		partcopy = dstent.ab_size;
		if (partcopy > num_bytes)
			partcopy = num_bytes;
		aio_pbuffer_copytomem(src,
		                      dstent.ab_base,
		                      src_offset,
		                      partcopy);
		if (partcopy >= num_bytes)
			break;
		num_bytes  -= partcopy;
		src_offset += partcopy;
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_pbuffer_copytovphys)(struct aio_pbuffer const *__restrict src,
                                       struct aio_pbuffer const *__restrict dst,
                                       uintptr_t dst_offset,
                                       uintptr_t src_offset,
                                       size_t num_bytes) {
	struct aio_pbuffer_entry dstent;
	assert(aio_pbuffer_size(src) >= src_offset + num_bytes);
	assert(aio_pbuffer_size(dst) >= dst_offset + num_bytes);
	AIO_PBUFFER_FOREACH_N(dstent, dst) {
		size_t partcopy;
		if (dst_offset != 0) {
			if (dst_offset >= dstent.ab_size) {
				dst_offset -= dstent.ab_size;
				continue;
			}
			dstent.ab_base += dst_offset;
			dstent.ab_size -= dst_offset;
			dst_offset = 0;
		}
		partcopy = dstent.ab_size;
		if (partcopy > num_bytes)
			partcopy = num_bytes;
		aio_pbuffer_copytophys(src,
		                       dstent.ab_base,
		                       src_offset,
		                       partcopy);
		if (partcopy >= num_bytes)
			break;
		num_bytes  -= partcopy;
		src_offset += partcopy;
	}
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_IOVEC_C */
