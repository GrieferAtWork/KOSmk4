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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_PHYS_C
#define GUARD_KERNEL_SRC_MEMORY_VM_PHYS_C 1
#define _KOS_SOURCE 1
#define __OMIT_PHYS_COPY_CONSTANT_P_WRAPPERS 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/vm.h>
#include <kernel/vm/nopf.h>
#include <kernel/vm/phys.h>

#include <hybrid/align.h>
#include <hybrid/minmax.h>

#include <alloca.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>

DECL_BEGIN

/* A data part used to describe a single, reserved page. */
PUBLIC ATTR_PERTASK struct vm_node this_trampoline_node = {
	/* .vn_node   = */ { NULL, NULL, 0, 0 },
	/* .vn_byaddr = */ LLIST_INITNODE,
	/* .vn_prot   = */ VM_PROT_PRIVATE,
	/* .vn_flags  = */ VM_NODE_FLAG_NOMERGE | VM_NODE_FLAG_PREPARED,
	/* .vn_vm     = */ &vm_kernel,
	/* .vn_part   = */ NULL,
	/* .vn_block  = */ NULL,
	/* .vn_fspath = */ NULL,
	/* .vn_fsname = */ NULL,
	/* .vn_link   = */ { NULL, NULL },
	/* .vn_guard  = */ 0
};


PUBLIC void KCALL
vm_copyfromphys(USER CHECKED void *dst,
                PHYS physaddr_t src,
                size_t num_bytes)
		THROWS(E_SEGFAULT) {
	pagedir_pushval_t backup;
	byte_t *tramp;
	bool is_first;
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(src, num_bytes)) {
		memcpy(dst, PHYS_TO_IDENTITY(src), num_bytes);
		return;
	}
#endif /* !NO_PHYS_IDENTITY */
	if unlikely(!num_bytes) {
		DEFINE_PUBLIC_SYMBOL(this_trampoline_page,
		                     &this_trampoline_node.vn_node.a_vmin,
		                     sizeof(pageid_t));
		return;
	}
	is_first = true;
	tramp    = THIS_TRAMPOLINE_BASE;
	for (;;) {
		size_t page_bytes;
		page_bytes = PAGESIZE - (src & PAGEMASK);
		if (page_bytes > num_bytes)
			page_bytes = num_bytes;
		if (is_first) {
			backup = pagedir_push_mapone(tramp,
			                             src & ~PAGEMASK,
			                             PAGEDIR_MAP_FREAD);
			is_first = true;
		} else {
			pagedir_mapone(tramp,
			               src & PAGEMASK,
			               PAGEDIR_MAP_FREAD);
		}
		pagedir_syncone(tramp);
		TRY {
			/* Copy memory. */
			memcpy(dst,
			       tramp + ((ptrdiff_t)src & PAGEMASK),
			       page_bytes);
		} EXCEPT {
			/* Try-catch is required, because `dst' may be a user-buffer,
			 * in which case access may cause an exception to be thrown. */
			pagedir_pop_mapone(tramp, backup);
			RETHROW();
		}
		if (page_bytes >= num_bytes)
			break;
		num_bytes -= page_bytes;
		src += page_bytes;
		dst = (byte_t *)dst + page_bytes;
	}
	pagedir_pop_mapone(tramp, backup);
}

PUBLIC void KCALL
vm_copytophys(PHYS physaddr_t dst,
              USER CHECKED void const *src,
              size_t num_bytes)
		THROWS(E_SEGFAULT) {
	pagedir_pushval_t backup;
	byte_t *tramp;
	bool is_first;
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(dst, num_bytes)) {
		memcpy(PHYS_TO_IDENTITY(dst), src, num_bytes);
		return;
	}
#endif /* !NO_PHYS_IDENTITY */
	if unlikely(!num_bytes)
		return;
	is_first = true;
	tramp    = THIS_TRAMPOLINE_BASE;
	for (;;) {
		size_t page_bytes;
		page_bytes = PAGESIZE - (dst & PAGEMASK);
		if (page_bytes > num_bytes)
			page_bytes = num_bytes;
		if (is_first) {
			backup = pagedir_push_mapone(tramp,
			                             dst & ~PAGEMASK,
			                             PAGEDIR_MAP_FWRITE);
			is_first = false;
		} else {
			pagedir_mapone(tramp,
			               dst & ~PAGEMASK,
			               PAGEDIR_MAP_FWRITE);
		}
		pagedir_syncone(tramp);
		TRY {
			/* Copy memory. */
			memcpy(tramp + ((ptrdiff_t)dst & PAGEMASK),
			       src,
			       page_bytes);
		} EXCEPT {
			/* Try-catch is required, because `src' may be a user-buffer,
			 * in which case access may cause an exception to be thrown. */
			pagedir_pop_mapone(tramp, backup);
			RETHROW();
		}
		if (page_bytes >= num_bytes)
			break;
		num_bytes -= page_bytes;
		dst += page_bytes;
		src = (void *)((byte_t *)src + page_bytes);
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
                                    PHYS physaddr_t src,
                                    size_t num_bytes) {
	size_t result = 0;
	pagedir_pushval_t backup;
	byte_t *tramp;
	bool is_first;
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(src, num_bytes))
		return memcpy_nopf(dst, PHYS_TO_IDENTITY(src), num_bytes);
#endif /* !NO_PHYS_IDENTITY */
	if unlikely(!num_bytes)
		goto done;
	is_first = true;
	tramp    = THIS_TRAMPOLINE_BASE;
	for (;;) {
		size_t page_bytes, copy_error;
		page_bytes = PAGESIZE - (src & PAGEMASK);
		if (page_bytes > num_bytes)
			page_bytes = num_bytes;
		if (is_first) {
			backup = pagedir_push_mapone(tramp,
			                             src & ~PAGEMASK,
			                             PAGEDIR_MAP_FREAD);
			is_first = false;
		} else {
			pagedir_mapone(tramp,
			               src & ~PAGEMASK,
			               PAGEDIR_MAP_FREAD);
		}
		pagedir_syncone(tramp);
		/* Copy memory. */
		copy_error = memcpy_nopf(dst,
		                         tramp + ((ptrdiff_t)src & PAGEMASK),
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
	pagedir_pop_mapone(tramp, backup);
done:
	return result;
}

PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL vm_copytophys_nopf)(PHYS physaddr_t dst,
                                  USER CHECKED void const *src,
                                  size_t num_bytes) {
	size_t result = 0;
	pagedir_pushval_t backup;
	byte_t *tramp;
	bool is_first;
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(dst, num_bytes))
		return memcpy_nopf(PHYS_TO_IDENTITY(dst), src, num_bytes);
#endif /* !NO_PHYS_IDENTITY */
	if unlikely(!num_bytes)
		goto done;
	is_first = true;
	tramp    = THIS_TRAMPOLINE_BASE;
	for (;;) {
		size_t page_bytes, copy_error;
		page_bytes = PAGESIZE - (dst & PAGEMASK);
		if (page_bytes > num_bytes)
			page_bytes = num_bytes;
		if (is_first) {
			backup = pagedir_push_mapone(tramp,
			                             dst & ~PAGEMASK,
			                             PAGEDIR_MAP_FWRITE);
			is_first = false;
		} else {
			pagedir_mapone(tramp,
			               dst & ~PAGEMASK,
			               PAGEDIR_MAP_FWRITE);
		}
		pagedir_syncone(tramp);
		/* Copy memory. */
		copy_error = memcpy_nopf(tramp + ((ptrdiff_t)dst & PAGEMASK),
		                         src,
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
	pagedir_pop_mapone(tramp, backup);
done:
	return result;
}


PUBLIC NOBLOCK void
NOTHROW(KCALL vm_copyinphys)(PHYS physaddr_t dst,
                             PHYS physaddr_t src,
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
	bufsize = get_stack_avail();
	/* `512*(4|8)' bytes is more than enough of a reservation to
	 * be made, considering that the #PF handler for is guarantied
	 * to never actually be called because of us, since `buf' is
	 * allocated on a kernel stack, where kernel stacks are always
	 * LOCKED into memory. */
	if (bufsize <= 512 * sizeof(void *)) {
		if (!bufsize)
			bufsize = PAGESIZE / 2;
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
NOTHROW(KCALL vm_memsetphys)(PHYS physaddr_t dst, int byte, size_t num_bytes) {
	pagedir_pushval_t backup;
	byte_t *tramp;
	bool is_first;
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(dst, num_bytes)) {
		memset(PHYS_TO_IDENTITY(dst), byte, num_bytes);
		return;
	}
#endif /* !NO_PHYS_IDENTITY */
	if unlikely(!num_bytes)
		return;
	is_first = true;
	tramp    = THIS_TRAMPOLINE_BASE;
	for (;;) {
		size_t page_bytes;
		page_bytes = PAGESIZE - (dst & PAGEMASK);
		if (page_bytes > num_bytes)
			page_bytes = num_bytes;
		if (is_first) {
			backup = pagedir_push_mapone(tramp,
			                             dst & ~PAGEMASK,
			                             PAGEDIR_MAP_FWRITE);
			is_first = false;
		} else {
			pagedir_mapone(tramp,
			               dst & ~PAGEMASK,
			               PAGEDIR_MAP_FWRITE);
		}
		pagedir_syncone(tramp);
		/* Fill memory. */
		memset(tramp + ((ptrdiff_t)dst & PAGEMASK),
		       byte,
		       page_bytes);
		if (page_bytes >= num_bytes)
			break;
		num_bytes -= page_bytes;
		dst += page_bytes;
	}
	pagedir_pop_mapone(tramp, backup);
}


#define ASSERT_ONEPAGE_RANGE(start, num_bytes, PAGESIZE)                                  \
	assertf(!(num_bytes) ||                                                               \
	        ((start) & ~((PAGESIZE)-1)) == (((start) + (num_bytes)-1) & ~((PAGESIZE)-1)), \
	        "Address range "                                                              \
	        "%" PRIpN(__SIZEOF_PHYSADDR_T__) "..."                                        \
	        "%" PRIpN(__SIZEOF_PHYSADDR_T__) " crosses a page boundry at "                \
	        "%" PRIpN(__SIZEOF_PHYSADDR_T__),                                             \
	        (physaddr_t)(start), (physaddr_t)(start) + (num_bytes)-1,                     \
	        (physaddr_t)((start) + (num_bytes)-1) & ~((PAGESIZE)-1))



/* Same as the functions above, however all memory accesses are guarantied to happen within the same page.
 * In other words: `(PHYS & ~PAGEMASK) == ((PHYS + num_bytes - 1) & ~PAGEMASK)' */
PUBLIC void KCALL
vm_copyfromphys_onepage(USER CHECKED void *dst,
                        PHYS physaddr_t src,
                        size_t num_bytes)
		THROWS(E_SEGFAULT) {
	pagedir_pushval_t backup;
	byte_t *tramp;
	ASSERT_ONEPAGE_RANGE(src, num_bytes, PAGESIZE);
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(src, num_bytes)) {
		memcpy(dst, PHYS_TO_IDENTITY(src), num_bytes);
		return;
	}
#endif /* !NO_PHYS_IDENTITY */
	tramp = THIS_TRAMPOLINE_BASE;
	backup = pagedir_push_mapone(tramp,
	                             src & ~PAGEMASK,
	                             PAGEDIR_MAP_FREAD);
	pagedir_syncone(tramp);
	TRY {
		/* Copy memory. */
		memcpy(dst,
		       tramp + ((ptrdiff_t)src & PAGEMASK),
		       num_bytes);
	} EXCEPT {
		/* Try-catch is required, because `dst' may be a user-buffer,
		 * in which case access may cause an exception to be thrown. */
		pagedir_pop_mapone(tramp, backup);
		RETHROW();
	}
	pagedir_pop_mapone(tramp, backup);
}

PUBLIC void KCALL
vm_copytophys_onepage(PHYS physaddr_t dst,
                      USER CHECKED void const *src,
                      size_t num_bytes)
		THROWS(E_SEGFAULT) {
	pagedir_pushval_t backup;
	byte_t *tramp;
	ASSERT_ONEPAGE_RANGE(dst, num_bytes, PAGESIZE);
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(dst, num_bytes)) {
		memcpy(PHYS_TO_IDENTITY(dst), src, num_bytes);
		return;
	}
#endif /* !NO_PHYS_IDENTITY */
	tramp = THIS_TRAMPOLINE_BASE;
	backup = pagedir_push_mapone(tramp,
	                             dst & ~PAGEMASK,
	                             PAGEDIR_MAP_FWRITE);
	pagedir_syncone(tramp);
	TRY {
		/* Copy memory. */
		memcpy(tramp + ((ptrdiff_t)dst & PAGEMASK),
		       src,
		       num_bytes);
	} EXCEPT {
		/* Try-catch is required, because `dst' may be a user-buffer,
		 * in which case access may cause an exception to be thrown. */
		pagedir_pop_mapone(tramp, backup);
		RETHROW();
	}
	pagedir_pop_mapone(tramp, backup);
}

PUBLIC NOBLOCK void
NOTHROW(KCALL vm_copyinphys_onepage)(PHYS physaddr_t dst,
                                     PHYS physaddr_t src,
                                     size_t num_bytes) {
	byte_t *buf;
	size_t bufsize;
	ASSERT_ONEPAGE_RANGE(dst, num_bytes, PAGESIZE);
	ASSERT_ONEPAGE_RANGE(src, num_bytes, PAGESIZE);
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
	bufsize = get_stack_avail();
	/* `512*(4|8)' bytes is more than enough of a reservation to
	 * be made, considering that the #PF handler for is guarantied
	 * to never actually be called because of us, since `buf' is
	 * allocated on a kernel stack, where kernel stacks are always
	 * LOCKED into memory. */
	if (bufsize <= 512 * sizeof(void *)) {
		if (!bufsize)
			bufsize = PAGESIZE / 2;
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
NOTHROW(KCALL vm_memsetphys_onepage)(PHYS physaddr_t dst,
                                     int byte,
                                     size_t num_bytes) {
	pagedir_pushval_t backup;
	byte_t *tramp;
	ASSERT_ONEPAGE_RANGE(dst, num_bytes, PAGESIZE);
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(dst, num_bytes)) {
		memset(PHYS_TO_IDENTITY(dst), byte, num_bytes);
		return;
	}
#endif /* !NO_PHYS_IDENTITY */
	tramp  = THIS_TRAMPOLINE_BASE;
	backup = pagedir_push_mapone(tramp,
	                             dst & ~PAGEMASK,
	                             PAGEDIR_MAP_FWRITE);
	pagedir_syncone(tramp);
	/* Fill memory. */
	memset(tramp + ((ptrdiff_t)dst & PAGEMASK),
	       byte, num_bytes);
	pagedir_pop_mapone(tramp, backup);
}

PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL vm_copyfromphys_onepage_nopf)(USER CHECKED void *dst,
                                            PHYS physaddr_t src,
                                            size_t num_bytes) {
	pagedir_pushval_t backup;
	byte_t *tramp;
	size_t result;
	ASSERT_ONEPAGE_RANGE(src, num_bytes, PAGESIZE);
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(src, num_bytes))
		return memcpy_nopf(dst, PHYS_TO_IDENTITY(src), num_bytes);
#endif /* !NO_PHYS_IDENTITY */
	tramp  = THIS_TRAMPOLINE_BASE;
	backup = pagedir_push_mapone(tramp,
	                             src & ~PAGEMASK,
	                             PAGEDIR_MAP_FREAD);
	pagedir_syncone(tramp);
	/* Copy memory. */
	result = memcpy_nopf(dst,
	                     tramp + ((ptrdiff_t)src & PAGEMASK),
	                     num_bytes);
	pagedir_pop_mapone(tramp, backup);
	return result;
}

PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL vm_copytophys_onepage_nopf)(PHYS physaddr_t dst,
                                          USER CHECKED void const *src,
                                          size_t num_bytes) {
	pagedir_pushval_t backup;
	byte_t *tramp;
	size_t result;
	ASSERT_ONEPAGE_RANGE(dst, num_bytes, PAGESIZE);
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(dst, num_bytes))
		return memcpy_nopf(PHYS_TO_IDENTITY(dst), src, num_bytes);
#endif /* !NO_PHYS_IDENTITY */
	tramp  = THIS_TRAMPOLINE_BASE;
	backup = pagedir_push_mapone(tramp,
	                             dst & ~PAGEMASK,
	                             PAGEDIR_MAP_FWRITE);
	pagedir_syncone(tramp);
	/* Copy memory. */
	result = memcpy_nopf(tramp + ((ptrdiff_t)dst & PAGEMASK),
	                     src,
	                     num_bytes);
	pagedir_pop_mapone(tramp, backup);
	return result;
}


/* Copy a whole page to/from physical memory. */
PUBLIC void KCALL
vm_copypagefromphys(USER CHECKED void *dst,
                    PAGEDIR_PAGEALIGNED PHYS physaddr_t src)
		THROWS(E_SEGFAULT) {
	pagedir_pushval_t backup;
	byte_t *tramp;
	assert(IS_ALIGNED(src, PAGESIZE));
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(src, PAGESIZE)) {
		memcpy(dst, PHYS_TO_IDENTITY(src), PAGESIZE);
		return;
	}
#endif /* !NO_PHYS_IDENTITY */
	tramp  = THIS_TRAMPOLINE_BASE;
	backup = pagedir_push_mapone(tramp,
	                             src,
	                             PAGEDIR_MAP_FREAD);
	pagedir_syncone(tramp);
	TRY {
		/* Copy memory. */
		memcpy(dst, tramp, PAGESIZE);
	} EXCEPT {
		/* Try-catch is required, because `dst' may be a user-buffer,
		 * in which case access may cause an exception to be thrown. */
		pagedir_pop_mapone(tramp, backup);
		RETHROW();
	}
	pagedir_pop_mapone(tramp, backup);
}

PUBLIC void KCALL
vm_copypagetophys(PAGEDIR_PAGEALIGNED PHYS physaddr_t dst,
                  USER CHECKED void const *src)
		THROWS(E_SEGFAULT) {
	pagedir_pushval_t backup;
	byte_t *tramp;
	assert(IS_ALIGNED(dst, PAGESIZE));
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(dst, PAGESIZE)) {
		memcpy(PHYS_TO_IDENTITY(dst), src, PAGESIZE);
		return;
	}
#endif /* !NO_PHYS_IDENTITY */
	tramp  = THIS_TRAMPOLINE_BASE;
	backup = pagedir_push_mapone(tramp,
	                             dst,
	                             PAGEDIR_MAP_FWRITE);
	pagedir_syncone(tramp);
	TRY {
		/* Copy memory. */
		memcpy(tramp, src, PAGESIZE);
	} EXCEPT {
		/* Try-catch is required, because `dst' may be a user-buffer,
		 * in which case access may cause an exception to be thrown. */
		pagedir_pop_mapone(tramp, backup);
		RETHROW();
	}
	pagedir_pop_mapone(tramp, backup);
}

PUBLIC NOBLOCK void
NOTHROW(KCALL vm_copypageinphys)(PAGEDIR_PAGEALIGNED PHYS physaddr_t dst,
                                 PAGEDIR_PAGEALIGNED PHYS physaddr_t src) {
	size_t bufsize;
	byte_t *buf;
	assert(IS_ALIGNED(dst, PAGESIZE));
	assert(IS_ALIGNED(src, PAGESIZE));
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(src, PAGESIZE)) {
		if (PHYS_IS_IDENTITY(dst, PAGESIZE)) {
			/* SRC|DST:identity */
			memcpy(PHYS_TO_IDENTITY(dst),
			       PHYS_TO_IDENTITY(src),
			       PAGESIZE);
		} else {
			/* SRC:identity */
			vm_copypagetophys(dst, PHYS_TO_IDENTITY(src));
		}
		return;
	} else {
		if (PHYS_IS_IDENTITY(dst, PAGESIZE)) {
			/* DST:identity */
			vm_copypagefromphys(PHYS_TO_IDENTITY(dst), src);
			return;
		}
	}
#endif /* !NO_PHYS_IDENTITY */
	/* Copy data using a temporary buffer. */
	bufsize = get_stack_avail();
	/* `512*(4|8)' bytes is more than enough of a reservation to
	 * be made, considering that the #PF handler for is guarantied
	 * to never actually be called because of us, since `buf' is
	 * allocated on a kernel stack, where kernel stacks are always
	 * LOCKED into memory. */
	if (bufsize <= 512 * sizeof(void *)) {
		if (!bufsize)
			bufsize = PAGESIZE / 2;
		else {
			if (bufsize >= PAGESIZE)
				goto use_whole_page_buffer;
		}
	} else {
		bufsize -= 512 * sizeof(void *);
		if (bufsize >= PAGESIZE)
			goto use_whole_page_buffer;
	}
	assert(bufsize != 0);
	buf = (byte_t *)alloca(bufsize);
	{
		physaddr_t pdst = dst;
		physaddr_t psrc = src;
		size_t pagebytes = PAGESIZE;
		do {
			size_t copysize;
			copysize = MIN(bufsize, pagebytes);
			vm_copyfromphys_onepage(buf, psrc, copysize);
			vm_copytophys_onepage(pdst, buf, copysize);
			if (copysize >= pagebytes)
				break;
			pdst += copysize;
			psrc += copysize;
			pagebytes -= copysize;
		} while (pagebytes);
	}
	return;
use_whole_page_buffer:
	buf = (byte_t *)alloca(PAGESIZE);
	vm_copypagefromphys(buf, src);
	vm_copypagetophys(dst, buf);
}

PUBLIC NOBLOCK void
NOTHROW(KCALL vm_copypagesinphys)(PAGEDIR_PAGEALIGNED PHYS physaddr_t dst,
                                  PAGEDIR_PAGEALIGNED PHYS physaddr_t src,
                                  size_t num_pages) {
	while (num_pages) {
		vm_copypageinphys(dst, src);
		--num_pages;
		dst += PAGESIZE;
		src += PAGESIZE;
	}
}


PUBLIC NOBLOCK void
NOTHROW(KCALL vm_memsetphyspage)(PAGEDIR_PAGEALIGNED PHYS physaddr_t dst,
                                 int byte) {
	pagedir_pushval_t backup;
	byte_t *tramp;
	assert(IS_ALIGNED(dst, PAGESIZE));
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(dst, PAGESIZE)) {
		memset(PHYS_TO_IDENTITY(dst), byte, PAGESIZE);
		return;
	}
#endif /* !NO_PHYS_IDENTITY */
	tramp  = THIS_TRAMPOLINE_BASE;
	backup = pagedir_push_mapone(tramp,
	                             dst,
	                             PAGEDIR_MAP_FWRITE);
	pagedir_syncone(tramp);
	/* Fill memory. */
	memset(tramp, byte, PAGESIZE);
	pagedir_pop_mapone(tramp, backup);
}

PUBLIC NOBLOCK void
NOTHROW(KCALL vm_memsetphyspages)(PAGEDIR_PAGEALIGNED PHYS physaddr_t dst,
                                  int byte, size_t num_pages) {
	pagedir_pushval_t backup;
	byte_t *tramp;
	if unlikely(!num_pages)
		return;
	assert(IS_ALIGNED(dst, PAGESIZE));
#ifndef NO_PHYS_IDENTITY
	while (PHYS_IS_IDENTITY(dst, PAGESIZE)) {
		memset(PHYS_TO_IDENTITY(dst), byte, PAGESIZE);
		if (!--num_pages)
			return;
		++dst;
	}
#endif /* !NO_PHYS_IDENTITY */
	tramp  = THIS_TRAMPOLINE_BASE;
	backup = pagedir_push_mapone(tramp,
	                             dst,
	                             PAGEDIR_MAP_FWRITE);
	pagedir_syncone(tramp);
	/* Fill memory. */
	memset(tramp, byte, PAGESIZE);
	while (num_pages >= 2) {
		dst += PAGESIZE;
		pagedir_mapone(tramp, dst, PAGEDIR_MAP_FWRITE);
		pagedir_syncone(tramp);
		memset(tramp, byte, PAGESIZE);
		--num_pages;
	}
	pagedir_pop_mapone(tramp, backup);
}

PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL vm_copypagefromphys_nopf)(USER CHECKED void *dst,
                                        PAGEDIR_PAGEALIGNED PHYS physaddr_t src) {
	pagedir_pushval_t backup;
	byte_t *tramp;
	size_t result;
	assert(IS_ALIGNED(src, PAGESIZE));
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(src, PAGESIZE))
		return memcpy_nopf(dst, PHYS_TO_IDENTITY(src), PAGESIZE);
#endif /* !NO_PHYS_IDENTITY */
	tramp  = THIS_TRAMPOLINE_BASE;
	backup = pagedir_push_mapone(tramp,
	                             src,
	                             PAGEDIR_MAP_FREAD);
	pagedir_syncone(tramp);
	/* Copy memory. */
	result = memcpy_nopf(dst, tramp, PAGESIZE);
	pagedir_pop_mapone(tramp, backup);
	return result;
}

PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL vm_copypagetophys_nopf)(PAGEDIR_PAGEALIGNED PHYS physaddr_t dst,
                                      USER CHECKED void const *src) {
	pagedir_pushval_t backup;
	byte_t *tramp;
	size_t result;
	assert(IS_ALIGNED(dst, PAGESIZE));
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(dst, PAGESIZE))
		return memcpy_nopf(PHYS_TO_IDENTITY(dst), src, PAGESIZE);
#endif /* !NO_PHYS_IDENTITY */
	tramp  = THIS_TRAMPOLINE_BASE;
	backup = pagedir_push_mapone(tramp,
	                             dst,
	                             PAGEDIR_MAP_FWRITE);
	pagedir_syncone(tramp);
	/* Copy memory. */
	result = memcpy_nopf(tramp, src, PAGESIZE);
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
