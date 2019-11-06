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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_PHYS_C
#define GUARD_KERNEL_SRC_MEMORY_VM_PHYS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>

#include <alloca.h>
#include <assert.h>
#include <string.h>

DECL_BEGIN

/* A data part used to describe a single, reserved page. */
INTERN ATTR_PERTASK struct vm_node _this_trampoline_node = {
	/* .vn_node   = */ { NULL, NULL, 0, 0 },
	/* .vn_byaddr = */ LLIST_INITNODE,
	/* .vn_prot   = */ VM_PROT_PRIVATE,
	/* .vn_flags  = */ VM_NODE_FLAG_NOMERGE | VM_NODE_FLAG_PREPARED,
	/* .vn_vm     = */ &vm_kernel,
	/* .vn_part   = */ NULL,
	/* .vn_block  = */ NULL,
	/* .vn_link   = */ { NULL, NULL },
	/* .vn_guard  = */ 0
};


PUBLIC void KCALL
vm_copyfromphys(USER CHECKED void *dst,
                PHYS vm_phys_t src,
                size_t num_bytes)
		THROWS(E_SEGFAULT) {
	uintptr_t backup;
	vm_vpage_t tramp;
	bool is_first;
	if unlikely(!num_bytes) {
		DEFINE_PUBLIC_SYMBOL(_this_trampoline_page,
		                     &_this_trampoline_node.vn_node.a_vmin,
		                     sizeof(vm_vpage_t));
		return;
	}
	is_first = true;
	tramp    = THIS_TRAMPOLINE_PAGE;
	TRY {
		for (;;) {
			vm_ppage_t pageaddr;
			size_t page_bytes;
			pageaddr   = (vm_ppage_t)VM_ADDR2PAGE(src);
			page_bytes = PAGESIZE - (src & (PAGESIZE - 1));
			if (page_bytes > num_bytes)
				page_bytes = num_bytes;
			if (is_first) {
				backup = pagedir_push_mapone(tramp, pageaddr,
				                             PAGEDIR_MAP_FREAD);
			} else {
				pagedir_mapone(tramp, pageaddr,
				               PAGEDIR_MAP_FREAD);
			}
			pagedir_syncone(tramp);
			/* Copy memory. */
			memcpy(dst, (void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(src & (PAGESIZE - 1))),
			       page_bytes);
			if (page_bytes >= num_bytes)
				break;
			num_bytes -= page_bytes;
			src += page_bytes;
			dst = (byte_t *)dst + page_bytes;
		}
	} EXCEPT {
		/* Try-catch is required, because `dst' may be a user-buffer,
		 * in which case access may cause an exception to be thrown. */
		pagedir_pop_mapone(tramp, backup);
		RETHROW();
	}
	pagedir_pop_mapone(tramp, backup);
}

PUBLIC void KCALL
vm_copytophys(PHYS vm_phys_t dst,
              USER CHECKED void const *src,
              size_t num_bytes)
		THROWS(E_SEGFAULT) {
	uintptr_t backup;
	vm_vpage_t tramp;
	bool is_first;
	if unlikely(!num_bytes)
		return;
	is_first = true;
	tramp    = THIS_TRAMPOLINE_PAGE;
	TRY {
		for (;;) {
			vm_ppage_t pageaddr;
			size_t page_bytes;
			pageaddr   = (vm_ppage_t)VM_ADDR2PAGE(dst);
			page_bytes = PAGESIZE - (dst & (PAGESIZE - 1));
			if (page_bytes > num_bytes)
				page_bytes = num_bytes;
			if (is_first) {
				backup = pagedir_push_mapone(tramp, pageaddr,
				                             PAGEDIR_MAP_FWRITE);
			} else {
				pagedir_mapone(tramp, pageaddr,
				               PAGEDIR_MAP_FWRITE);
			}
			pagedir_syncone(tramp);
			/* Copy memory. */
			memcpy((void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(dst & (PAGESIZE - 1))), src,
			       page_bytes);
			if (page_bytes >= num_bytes)
				break;
			num_bytes -= page_bytes;
			dst += page_bytes;
			src = (void *)((byte_t *)src + page_bytes);
		}
	} EXCEPT {
		/* Try-catch is required, because `src' may be a user-buffer,
		 * in which case access may cause an exception to be thrown. */
		pagedir_pop_mapone(tramp, backup);
		RETHROW();
	}
	pagedir_pop_mapone(tramp, backup);
}

/* no-#PF variants of `vm_copy(from|to)phys()'.
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transfered.
 *              The affected memory range is:
 *               - `(dst|src) + num_bytes - return ... (dst|src) + num_bytes - 1' */
PUBLIC size_t
NOTHROW(KCALL vm_copyfromphys_nopf)(USER CHECKED void *dst,
                                    PHYS vm_phys_t src,
                                    size_t num_bytes) {
	size_t result = 0;
	uintptr_t backup;
	vm_vpage_t tramp;
	bool is_first;
	if unlikely(!num_bytes)
		goto done;
	is_first = true;
	tramp    = THIS_TRAMPOLINE_PAGE;
	TRY {
		for (;;) {
			vm_ppage_t pageaddr;
			size_t page_bytes, copy_error;
			pageaddr   = (vm_ppage_t)VM_ADDR2PAGE(src);
			page_bytes = PAGESIZE - (src & (PAGESIZE - 1));
			if (page_bytes > num_bytes)
				page_bytes = num_bytes;
			if (is_first) {
				backup = pagedir_push_mapone(tramp, pageaddr,
				                             PAGEDIR_MAP_FREAD);
			} else {
				pagedir_mapone(tramp, pageaddr,
				               PAGEDIR_MAP_FREAD);
			}
			pagedir_syncone(tramp);
			/* Copy memory. */
			copy_error = memcpy_nopf(dst, (void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(src & (PAGESIZE - 1))),
			                         page_bytes);
			if (copy_error != 0) {
				assert(copy_error <= page_bytes);
				result = copy_error + (num_bytes - page_bytes);
				assert(result <= num_bytes);
				break;
			}
			if (page_bytes >= num_bytes)
				break;
			num_bytes -= page_bytes;
			src += page_bytes;
			dst = (byte_t *)dst + page_bytes;
		}
	} EXCEPT {
		/* Try-catch is required, because `dst' may be a user-buffer,
		 * in which case access may cause an exception to be thrown. */
		pagedir_pop_mapone(tramp, backup);
		RETHROW();
	}
	pagedir_pop_mapone(tramp, backup);
done:
	return result;
}

PUBLIC size_t
NOTHROW(KCALL vm_copytophys_nopf)(PHYS vm_phys_t dst,
                                  USER CHECKED void const *src,
                                  size_t num_bytes) {
	size_t result = 0;
	uintptr_t backup;
	vm_vpage_t tramp;
	bool is_first;
	if unlikely(!num_bytes)
		goto done;
	is_first = true;
	tramp    = THIS_TRAMPOLINE_PAGE;
	TRY {
		for (;;) {
			vm_ppage_t pageaddr;
			size_t page_bytes, copy_error;
			pageaddr   = (vm_ppage_t)VM_ADDR2PAGE(dst);
			page_bytes = PAGESIZE - (dst & (PAGESIZE - 1));
			if (page_bytes > num_bytes)
				page_bytes = num_bytes;
			if (is_first) {
				backup = pagedir_push_mapone(tramp, pageaddr,
				                             PAGEDIR_MAP_FWRITE);
			} else {
				pagedir_mapone(tramp, pageaddr,
				               PAGEDIR_MAP_FWRITE);
			}
			pagedir_syncone(tramp);
			/* Copy memory. */
			copy_error = memcpy_nopf((void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(dst & (PAGESIZE - 1))), src,
			                         page_bytes);
			if (copy_error != 0) {
				assert(copy_error <= page_bytes);
				result = copy_error + (num_bytes - page_bytes);
				assert(result <= num_bytes);
				break;
			}
			if (page_bytes >= num_bytes)
				break;
			num_bytes -= page_bytes;
			dst += page_bytes;
			src = (void *)((byte_t *)src + page_bytes);
		}
	} EXCEPT {
		/* Try-catch is required, because `src' may be a user-buffer,
		 * in which case access may cause an exception to be thrown. */
		pagedir_pop_mapone(tramp, backup);
		RETHROW();
	}
	pagedir_pop_mapone(tramp, backup);
done:
	return result;
}


PUBLIC NOBLOCK void
NOTHROW(KCALL vm_copyinphys)(PHYS vm_phys_t dst,
                             PHYS vm_phys_t src,
                             size_t num_bytes) {
	/* Copy data using a temporary buffer. */
	byte_t *buf;
	size_t bufsize;
	if unlikely(!num_bytes)
		return;
	bufsize = stack_avail() / 2;
	/* `512*(4|8)' bytes is more than enough of a reservation to
	 * be made, considering that the #PF handler for is guarantied
	 * to never actually be called because of us, since `buf' is
	 * allocated on a kernel stack, where kernel stacks are always
	 * LOCKED into memory. */
	if (bufsize > 512 * sizeof(void *))
		bufsize -= 512 * sizeof(void *);
	else {
		bufsize = 128 * sizeof(void *);
	}
	if (bufsize > num_bytes)
		bufsize = num_bytes;
	else {
		if unlikely(!bufsize)
			bufsize = pagedir_pagesize();
		/* XXX: Try to acquire a lock to the kernel VM and try to temporarily
		 *      make use of some unused region of virtual memory to temporarily
		 *      map both `dst' and `src', allowing us to transfer data directly.
		 *   -> Since access to both source and target buffers is known not to
		 *      cause any visible side-effects in terms of special behavior such
		 *      as page-faults, or VIO memory access, doing this is possible in
		 *      this case, though this wouldn't be possible in the case of
		 *      copy(to|from)phys, as those operate with virtual buffers which
		 *      may have side-effects. */
	}
	assert(bufsize != 0);
	buf = (byte_t *)alloca(bufsize);
	for (;;) {
		size_t transfer_size;
		transfer_size = bufsize;
		if (transfer_size > num_bytes)
			transfer_size = num_bytes;
		vm_copyfromphys(buf, src, transfer_size);
		vm_copytophys(dst, buf, transfer_size);
		if (transfer_size >= num_bytes)
			break;
		dst += transfer_size;
		src += transfer_size;
		num_bytes -= transfer_size;
	}
}

PUBLIC NOBLOCK void
NOTHROW(KCALL vm_memsetphys)(PHYS vm_phys_t dst, int byte, size_t num_bytes) {
	uintptr_t backup;
	vm_vpage_t tramp;
	bool is_first;
	if unlikely(!num_bytes)
		return;
	is_first = true;
	tramp    = THIS_TRAMPOLINE_PAGE;
	for (;;) {
		vm_ppage_t pageaddr;
		size_t page_bytes;
		pageaddr   = (vm_ppage_t)VM_ADDR2PAGE(dst);
		page_bytes = PAGESIZE - (dst & (PAGESIZE - 1));
		if (page_bytes > num_bytes)
			page_bytes = num_bytes;
		if (is_first) {
			backup = pagedir_push_mapone(tramp, pageaddr,
			                             PAGEDIR_MAP_FWRITE);
		} else {
			pagedir_mapone(tramp, pageaddr,
			               PAGEDIR_MAP_FWRITE);
		}
		pagedir_syncone(tramp);
		/* Copy memory. */
		memset((void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(dst & (PAGESIZE - 1))), byte,
		       page_bytes);
		if (page_bytes >= num_bytes)
			break;
		num_bytes -= page_bytes;
		dst += page_bytes;
	}
	pagedir_pop_mapone(tramp, backup);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_PHYS_C */
