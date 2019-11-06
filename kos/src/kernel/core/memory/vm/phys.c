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
#define __OMIT_PHYS_COPY_CONSTANT_P_WRAPPERS 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>

#include <hybrid/minmax.h>
#include <alloca.h>
#include <assert.h>
#include <string.h>

#ifndef PHYS_IS_IDENTITY
#ifndef __INTELLISENSE__
#define NO_PHYS_IDENTITY 1
#endif /* !__INTELLISENSE__ */
#define PHYS_IS_IDENTITY(addr, num_bytes) 0
#define PHYS_TO_IDENTITY(addr) (void *)0
#endif /* !PHYS_IS_IDENTITY */

#ifndef PHYS_IS_IDENTITY_PAGE
#define PHYS_IS_IDENTITY_PAGE(pageno) \
	PHYS_IS_IDENTITY(VM_PPAGE2ADDR(pageno), pagedir_pagesize())
#define PHYS_TO_IDENTITY_PAGE(addr) \
	PHYS_TO_IDENTITY(VM_PPAGE2ADDR(pageno))
#endif /* !PHYS_IS_IDENTITY_PAGE */


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
	size_t pagesize;
	uintptr_t backup;
	vm_vpage_t tramp;
	bool is_first;
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(src, num_bytes)) {
		memcpy(dst, PHYS_TO_IDENTITY(src), num_bytes);
		return;
	}
#endif /* !NO_PHYS_IDENTITY */
	if unlikely(!num_bytes) {
		DEFINE_PUBLIC_SYMBOL(_this_trampoline_page,
		                     &_this_trampoline_node.vn_node.a_vmin,
		                     sizeof(vm_vpage_t));
		return;
	}
	pagesize = pagedir_pagesize();
	is_first = true;
	tramp    = THIS_TRAMPOLINE_PAGE;
	TRY {
		for (;;) {
			vm_ppage_t pageaddr;
			size_t page_bytes;
			pageaddr   = (vm_ppage_t)VM_ADDR2PAGE(src);
			page_bytes = pagesize - (src & (pagesize - 1));
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
			memcpy(dst, (void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(src & (pagesize - 1))),
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
	size_t pagesize;
	uintptr_t backup;
	vm_vpage_t tramp;
	bool is_first;
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(src, num_bytes)) {
		memcpy(PHYS_TO_IDENTITY(dst), src, num_bytes);
		return;
	}
#endif /* !NO_PHYS_IDENTITY */
	if unlikely(!num_bytes)
		return;
	pagesize = pagedir_pagesize();
	is_first = true;
	tramp    = THIS_TRAMPOLINE_PAGE;
	TRY {
		for (;;) {
			vm_ppage_t pageaddr;
			size_t page_bytes;
			pageaddr   = (vm_ppage_t)VM_ADDR2PAGE(dst);
			page_bytes = pagesize - (dst & (pagesize - 1));
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
			memcpy((void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(dst & (pagesize - 1))), src,
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
PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL vm_copyfromphys_nopf)(USER CHECKED void *dst,
                                    PHYS vm_phys_t src,
                                    size_t num_bytes) {
	size_t pagesize;
	size_t result = 0;
	uintptr_t backup;
	vm_vpage_t tramp;
	bool is_first;
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(src, num_bytes))
		return memcpy_nopf(dst, PHYS_TO_IDENTITY(src), num_bytes);
#endif /* !NO_PHYS_IDENTITY */
	if unlikely(!num_bytes)
		goto done;
	pagesize = pagedir_pagesize();
	is_first = true;
	tramp    = THIS_TRAMPOLINE_PAGE;
	TRY {
		for (;;) {
			vm_ppage_t pageaddr;
			size_t page_bytes, copy_error;
			pageaddr   = (vm_ppage_t)VM_ADDR2PAGE(src);
			page_bytes = pagesize - (src & (pagesize - 1));
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
			copy_error = memcpy_nopf(dst, (void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(src & (pagesize - 1))),
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

PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL vm_copytophys_nopf)(PHYS vm_phys_t dst,
                                  USER CHECKED void const *src,
                                  size_t num_bytes) {
	size_t pagesize;
	size_t result = 0;
	uintptr_t backup;
	vm_vpage_t tramp;
	bool is_first;
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(src, num_bytes))
		return memcpy_nopf(PHYS_TO_IDENTITY(dst), src, num_bytes);
#endif /* !NO_PHYS_IDENTITY */
	if unlikely(!num_bytes)
		goto done;
	pagesize = pagedir_pagesize();
	is_first = true;
	tramp    = THIS_TRAMPOLINE_PAGE;
	TRY {
		for (;;) {
			vm_ppage_t pageaddr;
			size_t page_bytes, copy_error;
			pageaddr   = (vm_ppage_t)VM_ADDR2PAGE(dst);
			page_bytes = pagesize - (dst & (pagesize - 1));
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
			copy_error = memcpy_nopf((void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(dst & (pagesize - 1))), src,
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
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(src, num_bytes)) {
		if (PHYS_IS_IDENTITY(dst, num_bytes)) {
			/* SRC|DST:identity */
			memcpy(PHYS_TO_IDENTITY(dst),
			       PHYS_TO_IDENTITY(src),
			       num_bytes);
		} else {
			/* SRC:identity */
			vm_copytophys(dst, PHYS_TO_IDENTITY(src), num_bytes);
		}
		return;
	} else {
		if (PHYS_IS_IDENTITY(dst, num_bytes)) {
			/* DST:identity */
			vm_copyfromphys(PHYS_TO_IDENTITY(dst), src, num_bytes);
			return;
		}
	}
#endif /* !NO_PHYS_IDENTITY */
	if unlikely(!num_bytes)
		return;
	bufsize = stack_avail();
	/* `512*(4|8)' bytes is more than enough of a reservation to
	 * be made, considering that the #PF handler for is guarantied
	 * to never actually be called because of us, since `buf' is
	 * allocated on a kernel stack, where kernel stacks are always
	 * LOCKED into memory. */
	if (bufsize <= 512 * sizeof(void *)) {
		if (!bufsize)
			bufsize = pagedir_pagesize() / 2;
		if (bufsize > num_bytes)
			bufsize = num_bytes;
	} else {
		bufsize -= 512 * sizeof(void *);
		if (bufsize > num_bytes)
			bufsize = num_bytes;
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
	size_t pagesize;
	uintptr_t backup;
	vm_vpage_t tramp;
	bool is_first;
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(dst, num_bytes)) {
		memset(PHYS_TO_IDENTITY(dst), byte, num_bytes);
		return;
	}
#endif /* !NO_PHYS_IDENTITY */
	if unlikely(!num_bytes)
		return;
	pagesize = pagedir_pagesize();
	is_first = true;
	tramp    = THIS_TRAMPOLINE_PAGE;
	for (;;) {
		vm_ppage_t pageaddr;
		size_t page_bytes;
		pageaddr   = (vm_ppage_t)VM_ADDR2PAGE(dst);
		page_bytes = pagesize - (dst & (pagesize - 1));
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
		/* Fill memory. */
		memset((void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(dst & (pagesize - 1))), byte,
		       page_bytes);
		if (page_bytes >= num_bytes)
			break;
		num_bytes -= page_bytes;
		dst += page_bytes;
	}
	pagedir_pop_mapone(tramp, backup);
}


#define ASSERT_ONEPAGE_RANGE(start, num_bytes, pagesize)                                  \
	assertf(!(num_bytes) ||                                                               \
	        ((start) & ~((pagesize)-1)) == (((start) + (num_bytes)-1) & ~((pagesize)-1)), \
	        "Address range %I64p...%I64p crosses a page boundry at %I64p",                \
	        (u64)(start), (u64)(start) + (num_bytes)-1,                                   \
	        (u64)((start) + (num_bytes)-1) & ~((pagesize)-1))



/* Same as the functions above, however all memory accesses are guarantied to happen within the same page.
 * In other words: `(PHYS & ~(pagedir_pagesize() - 1)) == ((PHYS + num_bytes - 1) & ~(pagedir_pagesize() - 1))' */
PUBLIC void KCALL
vm_copyfromphys_onepage(USER CHECKED void *dst,
                        PHYS vm_phys_t src,
                        size_t num_bytes)
		THROWS(E_SEGFAULT) {
	uintptr_t backup;
	vm_vpage_t tramp;
	size_t pagesize;
	pagesize = pagedir_pagesize();
	ASSERT_ONEPAGE_RANGE(src, num_bytes, pagesize);
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(src, num_bytes)) {
		memcpy(dst, PHYS_TO_IDENTITY(src), num_bytes);
		return;
	}
#endif /* !NO_PHYS_IDENTITY */
	tramp = THIS_TRAMPOLINE_PAGE;
	TRY {
		backup = pagedir_push_mapone(tramp, (vm_ppage_t)VM_ADDR2PAGE(src),
		                             PAGEDIR_MAP_FREAD);
		pagedir_syncone(tramp);
		/* Copy memory. */
		memcpy(dst, (void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(src & (pagesize - 1))), num_bytes);
	} EXCEPT {
		/* Try-catch is required, because `dst' may be a user-buffer,
		 * in which case access may cause an exception to be thrown. */
		pagedir_pop_mapone(tramp, backup);
		RETHROW();
	}
	pagedir_pop_mapone(tramp, backup);
}

PUBLIC void KCALL
vm_copytophys_onepage(PHYS vm_phys_t dst,
                      USER CHECKED void const *src,
                      size_t num_bytes)
		THROWS(E_SEGFAULT) {
	uintptr_t backup;
	vm_vpage_t tramp;
	size_t pagesize;
	pagesize = pagedir_pagesize();
	ASSERT_ONEPAGE_RANGE(dst, num_bytes, pagesize);
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(dst, num_bytes)) {
		memcpy(PHYS_TO_IDENTITY(dst), src, num_bytes);
		return;
	}
#endif /* !NO_PHYS_IDENTITY */
	tramp = THIS_TRAMPOLINE_PAGE;
	TRY {
		backup = pagedir_push_mapone(tramp, (vm_ppage_t)VM_ADDR2PAGE(dst),
		                             PAGEDIR_MAP_FWRITE);
		pagedir_syncone(tramp);
		/* Copy memory. */
		memcpy((void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(dst & (pagesize - 1))), src, num_bytes);
	} EXCEPT {
		/* Try-catch is required, because `dst' may be a user-buffer,
		 * in which case access may cause an exception to be thrown. */
		pagedir_pop_mapone(tramp, backup);
		RETHROW();
	}
	pagedir_pop_mapone(tramp, backup);
}

PUBLIC NOBLOCK void
NOTHROW(KCALL vm_copyinphys_onepage)(PHYS vm_phys_t dst,
                                     PHYS vm_phys_t src,
                                     size_t num_bytes) {
	byte_t *buf;
	size_t bufsize;
	size_t pagesize;
	pagesize = pagedir_pagesize();
	ASSERT_ONEPAGE_RANGE(dst, num_bytes, pagesize);
	ASSERT_ONEPAGE_RANGE(src, num_bytes, pagesize);
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(src, num_bytes)) {
		if (PHYS_IS_IDENTITY(dst, num_bytes)) {
			/* SRC|DST:identity */
			memcpy(PHYS_TO_IDENTITY(dst),
			       PHYS_TO_IDENTITY(src),
			       num_bytes);
		} else {
			/* SRC:identity */
			vm_copytophys_onepage(dst, PHYS_TO_IDENTITY(src), num_bytes);
		}
		return;
	} else {
		if (PHYS_IS_IDENTITY(dst, num_bytes)) {
			/* DST:identity */
			vm_copyfromphys_onepage(PHYS_TO_IDENTITY(dst), src, num_bytes);
			return;
		}
	}
#endif /* !NO_PHYS_IDENTITY */
	/* Copy data using a temporary buffer. */
	bufsize = stack_avail();
	/* `512*(4|8)' bytes is more than enough of a reservation to
	 * be made, considering that the #PF handler for is guarantied
	 * to never actually be called because of us, since `buf' is
	 * allocated on a kernel stack, where kernel stacks are always
	 * LOCKED into memory. */
	if (bufsize <= 512 * sizeof(void *)) {
		if (!bufsize)
			bufsize = pagedir_pagesize() / 2;
		if (bufsize > num_bytes)
			bufsize = num_bytes;
	} else {
		bufsize -= 512 * sizeof(void *);
		if (bufsize > num_bytes)
			bufsize = num_bytes;
	}
	assert(bufsize != 0 || !num_bytes);
	buf = (byte_t *)alloca(bufsize);
	for (;;) {
		size_t transfer_size;
		transfer_size = bufsize;
		if (transfer_size > num_bytes)
			transfer_size = num_bytes;
		vm_copyfromphys_onepage(buf, src, transfer_size);
		vm_copytophys_onepage(dst, buf, transfer_size);
		if (transfer_size >= num_bytes)
			break;
		dst += transfer_size;
		src += transfer_size;
		num_bytes -= transfer_size;
	}
}

PUBLIC NOBLOCK void
NOTHROW(KCALL vm_memsetphys_onepage)(PHYS vm_phys_t dst, int byte, size_t num_bytes) {
	size_t pagesize;
	uintptr_t backup;
	vm_vpage_t tramp;
	pagesize = pagedir_pagesize();
	ASSERT_ONEPAGE_RANGE(dst, num_bytes, pagesize);
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(dst, num_bytes)) {
		memset(PHYS_TO_IDENTITY(dst), byte, num_bytes);
		return;
	}
#endif /* !NO_PHYS_IDENTITY */
	tramp  = THIS_TRAMPOLINE_PAGE;
	backup = pagedir_push_mapone(tramp, (vm_ppage_t)VM_ADDR2PAGE(dst),
	                             PAGEDIR_MAP_FWRITE);
	pagedir_syncone(tramp);
	/* Fill memory. */
	memset((void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(dst & (pagesize - 1))),
	       byte, num_bytes);
	pagedir_pop_mapone(tramp, backup);
}

PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL vm_copyfromphys_onepage_nopf)(USER CHECKED void *dst,
                                            PHYS vm_phys_t src,
                                            size_t num_bytes) {
	uintptr_t backup;
	vm_vpage_t tramp;
	size_t result, pagesize;
	pagesize = pagedir_pagesize();
	ASSERT_ONEPAGE_RANGE(src, num_bytes, pagesize);
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(src, num_bytes))
		return memcpy_nopf(dst, PHYS_TO_IDENTITY(src), num_bytes);
#endif /* !NO_PHYS_IDENTITY */
	tramp = THIS_TRAMPOLINE_PAGE;
	backup = pagedir_push_mapone(tramp, (vm_ppage_t)VM_ADDR2PAGE(src),
	                             PAGEDIR_MAP_FREAD);
	pagedir_syncone(tramp);
	/* Copy memory. */
	result = memcpy_nopf(dst, (void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(src & (pagesize - 1))),
	                     num_bytes);
	pagedir_pop_mapone(tramp, backup);
	return result;
}

PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL vm_copytophys_onepage_nopf)(PHYS vm_phys_t dst,
                                          USER CHECKED void const *src,
                                          size_t num_bytes) {
	uintptr_t backup;
	vm_vpage_t tramp;
	size_t result, pagesize;
	pagesize = pagedir_pagesize();
	ASSERT_ONEPAGE_RANGE(dst, num_bytes, pagesize);
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(src, num_bytes))
		return memcpy_nopf(PHYS_TO_IDENTITY(dst), src, num_bytes);
#endif /* !NO_PHYS_IDENTITY */
	tramp = THIS_TRAMPOLINE_PAGE;
	backup = pagedir_push_mapone(tramp, (vm_ppage_t)VM_ADDR2PAGE(dst),
	                             PAGEDIR_MAP_FWRITE);
	pagedir_syncone(tramp);
	/* Copy memory. */
	result = memcpy_nopf((void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(dst & (pagesize - 1))),
	                     src, num_bytes);
	pagedir_pop_mapone(tramp, backup);
	return result;
}


/* Copy a whole page to/from physical memory. */
PUBLIC void KCALL
vm_pagefromphys(USER CHECKED void *dst,
                PHYS vm_ppage_t src)
		THROWS(E_SEGFAULT) {
	uintptr_t backup;
	vm_vpage_t tramp;
	size_t pagesize;
	pagesize = pagedir_pagesize();
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY_PAGE(src)) {
		memcpy(dst, PHYS_TO_IDENTITY_PAGE(src), pagesize);
		return;
	}
#endif /* !NO_PHYS_IDENTITY */
	tramp = THIS_TRAMPOLINE_PAGE;
	TRY {
		backup = pagedir_push_mapone(tramp, src, PAGEDIR_MAP_FREAD);
		pagedir_syncone(tramp);
		/* Copy memory. */
		memcpy(dst, (void *)VM_PAGE2ADDR(tramp), pagesize);
	} EXCEPT {
		/* Try-catch is required, because `dst' may be a user-buffer,
		 * in which case access may cause an exception to be thrown. */
		pagedir_pop_mapone(tramp, backup);
		RETHROW();
	}
	pagedir_pop_mapone(tramp, backup);
}

PUBLIC void KCALL
vm_pagetophys(PHYS vm_ppage_t dst,
              USER CHECKED void const *src)
		THROWS(E_SEGFAULT) {
	uintptr_t backup;
	vm_vpage_t tramp;
	size_t pagesize;
	pagesize = pagedir_pagesize();
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY_PAGE(dst)) {
		memcpy(PHYS_TO_IDENTITY_PAGE(dst), src, pagesize);
		return;
	}
#endif /* !NO_PHYS_IDENTITY */
	tramp = THIS_TRAMPOLINE_PAGE;
	TRY {
		backup = pagedir_push_mapone(tramp, dst, PAGEDIR_MAP_FWRITE);
		pagedir_syncone(tramp);
		/* Copy memory. */
		memcpy((void *)VM_PAGE2ADDR(tramp), src, pagesize);
	} EXCEPT {
		/* Try-catch is required, because `dst' may be a user-buffer,
		 * in which case access may cause an exception to be thrown. */
		pagedir_pop_mapone(tramp, backup);
		RETHROW();
	}
	pagedir_pop_mapone(tramp, backup);
}

PUBLIC NOBLOCK void
NOTHROW(KCALL vm_pageinphys)(PHYS vm_ppage_t dst, PHYS vm_ppage_t src) {
	size_t bufsize;
	size_t pagesize;
	byte_t *buf;
	pagesize = pagedir_pagesize();
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY_PAGE(src)) {
		if (PHYS_IS_IDENTITY_PAGE(dst)) {
			/* SRC|DST:identity */
			memcpy(PHYS_TO_IDENTITY_PAGE(dst),
			       PHYS_TO_IDENTITY_PAGE(src),
			       pagesize);
		} else {
			/* SRC:identity */
			vm_pagetophys(dst, PHYS_TO_IDENTITY_PAGE(src));
		}
		return;
	} else {
		if (PHYS_IS_IDENTITY_PAGE(dst)) {
			/* DST:identity */
			vm_pagefromphys(PHYS_TO_IDENTITY_PAGE(dst), src);
			return;
		}
	}
#endif /* !NO_PHYS_IDENTITY */
	/* Copy data using a temporary buffer. */
	bufsize = stack_avail();
	/* `512*(4|8)' bytes is more than enough of a reservation to
	 * be made, considering that the #PF handler for is guarantied
	 * to never actually be called because of us, since `buf' is
	 * allocated on a kernel stack, where kernel stacks are always
	 * LOCKED into memory. */
	if (bufsize <= 512 * sizeof(void *)) {
		if (!bufsize)
			bufsize = pagedir_pagesize() / 2;
		else {
			if (bufsize >= pagesize)
				goto use_whole_page_buffer;
		}
	} else {
		bufsize -= 512 * sizeof(void *);
		if (bufsize >= pagesize)
			goto use_whole_page_buffer;
	}
	assert(bufsize != 0);
	buf = (byte_t *)alloca(bufsize);
	{
		vm_phys_t pdst = VM_PPAGE2ADDR(dst);
		vm_phys_t psrc = VM_PPAGE2ADDR(src);
		while (pagesize) {
			size_t copysize;
			copysize = MIN(bufsize, pagesize);
			vm_copyfromphys_onepage(buf, psrc, copysize);
			vm_copytophys_onepage(pdst, buf, copysize);
			if (copysize >= pagesize)
				break;
			pdst += copysize;
			psrc += copysize;
			pagesize -= copysize;
		}
	}
	return;
use_whole_page_buffer:
	buf = (byte_t *)alloca(pagesize);
	vm_pagefromphys(buf, src);
	vm_pagetophys(dst, buf);
}

PUBLIC NOBLOCK void
NOTHROW(KCALL vm_memsetphyspage)(PHYS vm_ppage_t dst, int byte) {
	uintptr_t backup;
	vm_vpage_t tramp;
	size_t pagesize;
	pagesize = pagedir_pagesize();
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY_PAGE(dst)) {
		memset(PHYS_TO_IDENTITY_PAGE(dst), byte, pagesize);
		return;
	}
#endif /* !NO_PHYS_IDENTITY */
	tramp  = THIS_TRAMPOLINE_PAGE;
	backup = pagedir_push_mapone(tramp, dst, PAGEDIR_MAP_FWRITE);
	pagedir_syncone(tramp);
	/* Fill memory. */
	memset((void *)VM_PAGE2ADDR(tramp), byte, pagesize);
	pagedir_pop_mapone(tramp, backup);
}

PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL vm_pagefromphys_nopf)(USER CHECKED void *dst, PHYS vm_ppage_t src) {
	uintptr_t backup;
	vm_vpage_t tramp;
	size_t result, pagesize;
	pagesize = pagedir_pagesize();
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY_PAGE(src))
		return memcpy_nopf(dst, PHYS_TO_IDENTITY_PAGE(src), pagesize);
#endif /* !NO_PHYS_IDENTITY */
	tramp  = THIS_TRAMPOLINE_PAGE;
	backup = pagedir_push_mapone(tramp, src, PAGEDIR_MAP_FREAD);
	pagedir_syncone(tramp);
	/* Copy memory. */
	result = memcpy_nopf(dst, (void *)VM_PAGE2ADDR(tramp), pagesize);
	pagedir_pop_mapone(tramp, backup);
	return result;
}

PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL vm_pagetophys_nopf)(PHYS vm_ppage_t dst, USER CHECKED void const *src) {
	uintptr_t backup;
	vm_vpage_t tramp;
	size_t result, pagesize;
	pagesize = pagedir_pagesize();
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY_PAGE(dst))
		return memcpy_nopf(PHYS_TO_IDENTITY_PAGE(dst), src, pagesize);
#endif /* !NO_PHYS_IDENTITY */
	tramp  = THIS_TRAMPOLINE_PAGE;
	backup = pagedir_push_mapone(tramp, dst, PAGEDIR_MAP_FWRITE);
	pagedir_syncone(tramp);
	/* Copy memory. */
	result = memcpy_nopf((void *)VM_PAGE2ADDR(tramp), src, pagesize);
	pagedir_pop_mapone(tramp, backup);
	return result;
}

DECL_END


#ifndef __INTELLISENSE__
#define DEFINE_PHYS_READ 1
#include "phys-rw.c.inl"

#define DEFINE_PHYS_WRITE 1
#include "phys-rw.c.inl"

#define DEFINE_PHYS_UNALIGNED 1
#define DEFINE_PHYS_READ 1
#include "phys-rw.c.inl"

#define DEFINE_PHYS_UNALIGNED 1
#define DEFINE_PHYS_WRITE 1
#include "phys-rw.c.inl"
#endif /* !__INTELLISENSE__ */


#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_PHYS_C */
