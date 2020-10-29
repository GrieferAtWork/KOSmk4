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
#ifndef GUARD_MODDBX_MALLOC_C
#define GUARD_MODDBX_MALLOC_C 1
#define _KOS_SOURCE 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/vm.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <stddef.h>
#include <stdint.h>
#include <string.h>

/**/
#include "include/error.h"
#include "include/malloc.h"

#ifdef CONFIG_HAVE_DEBUGGER
DECL_BEGIN

#ifndef DBX_STATIC_HEAPSIZE
#define DBX_STATIC_HEAPSIZE (64 * 1024) /* 64K */
#endif /* !DBX_STATIC_HEAPSIZE */

#if 0
#define DBX_STATIC_HEAP_SETPAT(base, pat, num_bytes) (void)0
#elif __SIZEOF_POINTER__ == 4
#define DBX_STATIC_HEAP_PATTERN_USED                 UINT32_C(0xbbbbbbbb)
#define DBX_STATIC_HEAP_PATTERN_FREE                 UINT32_C(0xf7eef7ee)
#define DBX_STATIC_HEAP_SETPAT(base, pat, num_bytes) memsetl(base, pat, (num_bytes) / 4)
#elif __SIZEOF_POINTER__ == 8
#define DBX_STATIC_HEAP_PATTERN_USED                 UINT64_C(0xbbbbbbbbbbbbbbbb)
#define DBX_STATIC_HEAP_PATTERN_FREE                 UINT64_C(0xf7eef7eef7eef7ee)
#define DBX_STATIC_HEAP_SETPAT(base, pat, num_bytes) memsetq(base, pat, (num_bytes) / 8)
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported `__SIZEOF_POINTER__'"
#endif /* __SIZEOF_POINTER__ != ... */


struct sheap {
	struct sheap  *sh_next; /* [0..1] Next heap. */
	struct vm_node sh_node; /* [valid_if(sh_next)] VM node for allocating another heap. */
	byte_t sh_heap[DBX_STATIC_HEAPSIZE - /* Heap data. */
	               (sizeof(struct sheap *) +
	                sizeof(struct vm_node))];
};

/* Free a given static-heap extension. */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL sheap_free)(struct sheap *__restrict self) {
	unsigned int i;
	STATIC_ASSERT(IS_ALIGNED(sizeof(*self), PAGESIZE));
	for (i = 0; i < sizeof(*self) / PAGESIZE; ++i) {
		physaddr_t phys;
		byte_t *vaddr = (byte_t *)self + i * PAGESIZE;
		if (!pagedir_ismapped(vaddr))
			continue;
		phys = pagedir_translate(vaddr);
		pagedir_unmap(vaddr, PAGESIZE);
		page_freeone(physaddr2page(phys));
	}
	pagedir_sync(self, sizeof(*self));
}


struct freerange {
	struct freerange *fr_next; /* [0..1] Pointer to the next free segment. */
	size_t            fr_size; /* Size of this free segment. */
};
#define freerange_end(self) ((byte_t *)(self) + (self)->fr_size)

/* Static DBX heap. */
PRIVATE struct sheap static_heap;
PRIVATE struct freerange *freemem = NULL;


#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x

PRIVATE bool
NOTHROW(FCALL allocate_physical_memory)(PAGEDIR_PAGEALIGNED void *addr,
                                        PAGEDIR_PAGEALIGNED size_t num_bytes) {
	size_t i;
	for (i = 0; i < num_bytes; i += PAGESIZE) {
		physpage_t ppage;
		ppage = page_mallocone();
		if (ppage == PHYSPAGE_INVALID)
			goto fail;
		pagedir_mapone((byte_t *)addr + i,
		               physpage2addr(ppage),
		               PAGEDIR_MAP_FREAD |
		               PAGEDIR_MAP_FWRITE);
	}
	pagedir_sync(addr, num_bytes);
	return true;
fail:
	while (i) {
		physaddr_t phys;
		byte_t *vaddr = (byte_t *)addr + i;
		i -= PAGESIZE;
		phys = pagedir_translate(vaddr);
		pagedir_unmapone(vaddr);
		page_freeone(physaddr2page(phys));
	}
	pagedir_sync(addr, num_bytes);
	return false;
}


PRIVATE bool
NOTHROW(FCALL extend_heap)(void) {
	struct sheap *last_heap;
	struct sheap *new_heap;
	last_heap = &static_heap;
	while (last_heap->sh_next)
		last_heap = last_heap->sh_next;
	new_heap = (struct sheap *)vm_getfree(&vm_kernel,
	                                      HINT_GETADDR(KERNEL_VMHINT_TEMPORARY),
	                                      sizeof(struct sheap), PAGESIZE,
	                                      HINT_GETMODE(KERNEL_VMHINT_TEMPORARY));
	if (new_heap == (struct sheap *)VM_GETFREE_ERROR)
		return false;

	/* Prepare the address range for mappings. */
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	if (!pagedir_prepare_map(new_heap, sizeof(struct sheap)))
		return false;
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

	/* Allocate the backing physical memory. */
	if (!allocate_physical_memory(new_heap, sizeof(struct sheap))) {
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
		pagedir_unprepare_map(new_heap, sizeof(struct sheap));
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
		return false;
	}
	/* Reserve the associated address range to prevent the kernel
	 * from re-assigning its address range for other purposes. */
	last_heap->sh_node.vn_node.a_vmin   = PAGEID_ENCODE((byte_t *)new_heap);
	last_heap->sh_node.vn_node.a_vmax   = PAGEID_ENCODE((byte_t *)new_heap + sizeof(struct sheap)) - 1;
	last_heap->sh_node.vn_prot          = VM_PROT_READ | VM_PROT_WRITE;
	last_heap->sh_node.vn_flags         = VM_NODE_FLAG_PREPARED | VM_NODE_FLAG_NOMERGE;
	last_heap->sh_node.vn_vm            = &vm_kernel;
	last_heap->sh_node.vn_part          = NULL;
	last_heap->sh_node.vn_block         = NULL;
	last_heap->sh_node.vn_fspath        = NULL;
	last_heap->sh_node.vn_fsname        = NULL;
	last_heap->sh_node.vn_link.ln_pself = NULL;
	last_heap->sh_node.vn_link.ln_next  = NULL;
	last_heap->sh_node.vn_guard         = 0;
	vm_node_insert(&last_heap->sh_node);
	/* Remember the new heap. */
	new_heap->sh_next  = NULL;
	last_heap->sh_next = new_heap;
	/* Register the new heap's body as free heap memory. */
	{
		struct freerange *fr;
		DBX_STATIC_HEAP_SETPAT(new_heap->sh_heap,
		                       DBX_STATIC_HEAP_PATTERN_FREE,
		                       sizeof(new_heap->sh_heap));
		fr = (struct freerange *)new_heap->sh_heap;
		fr->fr_next = freemem;
		fr->fr_size = sizeof(new_heap->sh_heap);
		freemem     = fr;
	}
	return true;
}


PUBLIC WUNUSED struct heapptr
NOTHROW(FCALL dbx_heap_alloc)(size_t num_bytes) {
	struct heapptr resptr;
	struct freerange *result;
	struct freerange **presult;
	size_t remaining;
	num_bytes = CEIL_ALIGN(num_bytes, sizeof(void *));
	if unlikely(num_bytes < sizeof(struct freerange))
		num_bytes = sizeof(struct freerange);
again:
	for (presult = &freemem;;) {
		result = *presult;
		if unlikely(!result)
			goto nomem;
		if (result->fr_size >= num_bytes)
			break;
		presult = &result->fr_next;
	}
	remaining     = result->fr_size - num_bytes;
	resptr.hp_ptr = result;
	if (remaining < sizeof(struct freerange)) {
		/* Allocate the whole free-range */
		resptr.hp_siz = result->fr_size;
		*presult = result->fr_next;
	} else {
		struct freerange *newrange;
		/* Allocate from the front. */
		resptr.hp_siz = num_bytes;
		/* Replace the old free-range with a smaller one. */
		newrange = (struct freerange *)((byte_t *)result + num_bytes);
		newrange->fr_next = result->fr_next;
		newrange->fr_size = remaining;
		*presult = newrange;
	}
	DBX_STATIC_HEAP_SETPAT(resptr.hp_ptr,
	                       DBX_STATIC_HEAP_PATTERN_USED,
	                       resptr.hp_siz);
	return resptr;
nomem:
	/* Make sure that the memory request isn't too large to possibly satisfy. */
	if unlikely(num_bytes > sizeof(static_heap.sh_heap))
		goto nope;
	/* Try to allocate a heap extension, but don't
	 * do so if the kernel's been poisoned. */
	if (kernel_poisoned())
		goto nope;
	if (extend_heap())
		goto again;
nope:
	resptr.hp_ptr = NULL;
	resptr.hp_siz = 0;
	return resptr;
}

/* Try to allocate at least `num_bytes' at `addr',
 * and return the actual amount that was allocated. */
PUBLIC WUNUSED size_t
NOTHROW(FCALL dbx_heap_allocat)(void *addr, size_t num_bytes) {
	size_t avail;
	struct freerange *result;
	struct freerange **presult;
	if unlikely(!IS_ALIGNED((uintptr_t)addr, sizeof(void *)))
		goto nope;
	num_bytes = CEIL_ALIGN(num_bytes, sizeof(void *));
	for (presult = &freemem;;) {
		result = *presult;
		if unlikely(!result)
			goto nope;
		if ((byte_t *)addr < (byte_t *)result)
			goto nope;
		if ((byte_t *)addr < freerange_end(result))
			break; /* Found the range in question. */
		presult = &result->fr_next;
	}
	avail = (size_t)(freerange_end(result) - (byte_t *)addr);
	if (avail < num_bytes)
		goto nope;
	/* If not allocating at the front, make sure that the gap
	 * that would get created is large enough for a free-range. */
	if ((byte_t *)addr > (byte_t *)result) {
		size_t gap_size;
		gap_size = (size_t)((byte_t *)addr - (byte_t *)result);
		if (gap_size < sizeof(struct freerange))
			goto nope;
	}
	if (avail > num_bytes) {
		/* If the tail would be too small, increase the allocated size to include it. */
		size_t tail;
		tail = avail - num_bytes;
		if (tail < sizeof(struct freerange))
			num_bytes = avail;
	}
	/* Confirmed! */
	if ((byte_t *)addr == (byte_t *)result) {
		if ((byte_t *)addr + num_bytes >= freerange_end(result)) {
			/* Allocate the whole thing. */
			*presult = result->fr_next;
		} else {
			/* Take away from the front */
			struct freerange *newrange;
			newrange = (struct freerange *)((byte_t *)addr + num_bytes);
			newrange->fr_next = result->fr_next;
			newrange->fr_size = avail - num_bytes;
			*presult = newrange;
		}
	} else if ((byte_t *)addr + num_bytes >= freerange_end(result)) {
		/* Allocate from the back */
		result->fr_size -= num_bytes;
	} else {
		/* Allocate from the middle. */
		struct freerange *newrange;
		newrange = (struct freerange *)((byte_t *)addr + num_bytes);
		newrange->fr_size = (size_t)(freerange_end(result) - (byte_t *)newrange);
		newrange->fr_next = result->fr_next;
		result->fr_next   = newrange;
		result->fr_size   = (size_t)((byte_t *)addr - (byte_t *)result);
	}
	DBX_STATIC_HEAP_SETPAT(addr, DBX_STATIC_HEAP_PATTERN_USED, num_bytes);
	return num_bytes;
nope:
	return 0;
}



/* Check if any part of the given address range was already freed. */
PRIVATE bool
NOTHROW(KCALL static_heap_isfree)(void *base, size_t num_bytes) {
	struct freerange *iter = freemem;
	while (iter && (byte_t *)base >= (byte_t *)freerange_end(iter))
		iter = iter->fr_next;
	return iter && ((byte_t *)base + num_bytes) > (byte_t *)iter;
}

PRIVATE bool
NOTHROW(KCALL static_heap_contains)(void *base, size_t num_bytes) {
	struct sheap *iter = &static_heap;
	do {
		if ((byte_t *)base >= iter->sh_heap) {
			uintptr_t endptr;
			if (!OVERFLOW_UADD((uintptr_t)base, num_bytes, &endptr) &&
			    endptr <= (uintptr_t)COMPILER_ENDOF(iter->sh_heap))
				return true;
		}
	} while ((iter = iter->sh_next) != NULL);
	return false;
}


/* Free a given address range from the static heap. */
PUBLIC void
NOTHROW(FCALL dbx_heap_free)(void *base, size_t num_bytes) {
	struct freerange **piter, *iter;
	/* Make sure that the given pointer/size pair is in-bounds and valid. */
	if unlikely(!IS_ALIGNED(num_bytes, sizeof(void *)))
		goto internal_error;
	if unlikely(num_bytes <= sizeof(struct freerange)) {
		if likely(!num_bytes)
			goto done;
		goto internal_error;
	}
	if unlikely(!static_heap_contains(base, num_bytes))
		goto internal_error; /* Not apart of the static heap */
	if unlikely(static_heap_isfree(base, num_bytes))
		goto internal_error; /* Already freed */
	DBX_STATIC_HEAP_SETPAT(base, DBX_STATIC_HEAP_PATTERN_FREE, num_bytes);
	piter = &freemem;
	for (;;) {
		byte_t *iter_end;
		struct freerange *newnode;
		iter = *piter;
		if (!iter) {
			/* Append at the end. */
			newnode = (struct freerange *)base;
			newnode->fr_next = NULL;
			newnode->fr_size = num_bytes;
			*piter = newnode;
			break;
		}
		iter_end = freerange_end(iter);
		if ((byte_t *)base > iter_end) {
			piter = &iter->fr_next;
			continue;
		}
		if ((byte_t *)base == iter_end) {
			/* Extend `iter' at the end. */
			struct freerange *next;
			iter->fr_size += num_bytes;
			next = iter->fr_next;
			if ((byte_t *)next == (byte_t *)iter + iter->fr_size) {
				/* Merge `iter' with its follow-up node. */
				iter->fr_size += next->fr_size;
				iter->fr_next = next->fr_next;
				DBX_STATIC_HEAP_SETPAT(next, DBX_STATIC_HEAP_PATTERN_FREE, sizeof(*next));
			}
			break;
		}
		/* Insert before `iter'. */
		newnode = (struct freerange *)base;
		if ((byte_t *)base + num_bytes == (byte_t *)iter) {
			/* Merge together with `iter' at the front. */
			newnode->fr_next = iter->fr_next;
			newnode->fr_size = iter->fr_size + num_bytes;
			DBX_STATIC_HEAP_SETPAT(iter, DBX_STATIC_HEAP_PATTERN_FREE, sizeof(*iter));
		} else {
			newnode->fr_next = iter->fr_next;
			newnode->fr_size = iter->fr_size + num_bytes;
		}
		*piter = newnode;
		break;
	}
done:
	return /*DBX_EOK*/;
internal_error:
	return /*DBX_EINTERN*/;
}


PRIVATE void KCALL reset_heap(void) {
	/* Reset the static heap. */
	static_heap.sh_next = NULL;
	DBX_STATIC_HEAP_SETPAT(static_heap.sh_heap,
	                       DBX_STATIC_HEAP_PATTERN_FREE,
	                       sizeof(static_heap.sh_heap));
	freemem = (struct freerange *)static_heap.sh_heap;
	freemem->fr_next = NULL;
	freemem->fr_size = sizeof(static_heap.sh_heap);
}

PRIVATE void KCALL clear_heap(void) {
	if (kernel_poisoned())
		return; /* Don't touch the kernel VM after poison */
	/* Unmap all dynamically mapped heap nodes. */
	while (static_heap.sh_next) {
		struct vm_node *node;
		struct sheap *pred = &static_heap;
		struct sheap *iter = pred->sh_next;
		/* Find the last heap extension with a valid next-pointer. */
		while (iter->sh_next) {
			pred = iter;
			iter = iter->sh_next;
		}
		pred->sh_next = NULL;
		/* Unmap the node. */
		node = vm_paged_node_remove(&vm_kernel, iter->sh_node.vn_node.a_vmin);
		if unlikely(node != &iter->sh_node) {
			/* Shouldn't happen... */
			vm_node_insert(node);
			break;
		}
		/* Free this heap extension. */
		sheap_free(iter);
	}
}


INTERN void KCALL dbx_heap_init(void) {
	reset_heap();
}
INTERN void KCALL dbx_heap_reset(void) {
	clear_heap();
	reset_heap();
}
INTERN void KCALL dbx_heap_fini(void) {
	clear_heap();
}


PUBLIC ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) ATTR_ASSUME_ALIGNED(__SIZEOF_POINTER__) void *
NOTHROW(FCALL dbx_malloc)(size_t num_bytes) {
	struct heapptr hp;
	size_t *result;
	hp = dbx_heap_alloc(sizeof(size_t) + num_bytes);
	if unlikely(!hp.hp_siz)
		return NULL;
	result    = (size_t *)hp.hp_ptr;
	*result++ = hp.hp_siz - sizeof(size_t);
	return result;
}

PUBLIC WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_ASSUME_ALIGNED(__SIZEOF_POINTER__) void *
NOTHROW(FCALL dbx_realloc)(void *ptr, size_t num_bytes) {
	void *new_ptr;
	size_t *base;
	size_t old_size, missing;
	if (!ptr)
		return dbx_malloc(num_bytes);
	num_bytes = CEIL_ALIGN(num_bytes, sizeof(void *));
	base      = (size_t *)ptr - 1;
	old_size  = *base;
	if (num_bytes <= old_size) {
		if (num_bytes < old_size) {
			size_t tail;
			tail = old_size - num_bytes;
			/* Try to truncate trailing memory. */
			if (tail >= sizeof(struct freerange)) {
				dbx_heap_free((byte_t *)ptr + num_bytes, tail);
				*base = num_bytes;
			}
		}
		return ptr;
	}
	/* Try to extend an existing heap-block. */
	missing = num_bytes - old_size;
	missing = dbx_heap_allocat((byte_t *)ptr + old_size, missing);
	if (missing) {
		/* Success! */
		*base += missing;
		return ptr;
	}
	/* Failed. - Try to allocate an entirely new block,
	 * and copy over the contents from the old one. */
	new_ptr = dbx_malloc(num_bytes);
	if likely(new_ptr) {
		memcpy(new_ptr, ptr, old_size);
		dbx_free(ptr);
	}
	return new_ptr;
}

PUBLIC ATTR_PURE WUNUSED size_t
NOTHROW(FCALL dbx_malloc_usable_size)(void *ptr) {
	if (!ptr)
		return 0;
	return ((size_t *)ptr)[-1];
}

PUBLIC void NOTHROW(FCALL dbx_free)(void *ptr) {
	size_t *base;
	if (!ptr)
		return;
	base = (size_t *)ptr - 1;
	dbx_heap_free(base, *base + sizeof(size_t));
}




DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_MALLOC_C */
