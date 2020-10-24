/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_LIBDEBUGINFO_DEBUG_INFO_C
#define GUARD_LIBDEBUGINFO_DEBUG_INFO_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/minmax.h>
#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <kos/exec/module.h>

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unicode.h>

#include <libdebuginfo/debug_info.h>
#include <libdebuginfo/dwarf.h>

#include "debug_aranges.h"
#include "debug_info.h"

#ifdef __KERNEL__
#include <debugger/config.h>
#include <debugger/rt.h>
#include <kernel/heap.h>
#include <kernel/panic.h> /* kernel_poisoned() */

#include <hybrid/atomic.h>
#else /* __KERNEL__ */
#include <malloc.h>
#endif /* !__KERNEL__ */


DECL_BEGIN

#ifdef __KERNEL__

#ifdef CONFIG_HAVE_DEBUGGER
/* Lock to keep track of attempts to allocate memory for the
 * purposes of abbreviation code caches. Because libdebuginfo
 * is heavily used by the kernel's builtin debugger, we have
 * to be as robust as possible against problems occurring in
 * critical places, such as the heap (which we're using here)
 *
 * Because of this, we use a lock to prevent the debugger
 * accidentally allocating temporary heap memory if the fault
 * happening while we were already trying to allocate some memory.
 *
 * For this, acquire a write-lock while debugging (which fails if
 * any other thread is already holding some other kind of lock),
 * and acquire a read-lock (to keep track of the recursion when
 * calling of these functions) otherwise.
 *
 * With this, we can prevent the debugging from recursively faulting
 * if there is a problem with the heap sub-system. */
PRIVATE struct atomic_rwlock kernel_debug_info_inside_malloc = ATOMIC_RWLOCK_INIT;
#define MY_KMALLOC_ACQUIRE_LOCK()                                                    \
	do {                                                                             \
		if (!(dbg_active ? atomic_rwlock_trywrite(&kernel_debug_info_inside_malloc)  \
		                 : atomic_rwlock_tryread(&kernel_debug_info_inside_malloc))) \
			return NULL;                                                             \
	} __WHILE0
#define MY_KMALLOC_RELEASE_LOCK() \
	atomic_rwlock_end(&kernel_debug_info_inside_malloc)

#else /* CONFIG_HAVE_DEBUGGER */
#define MY_KMALLOC_ACQUIRE_LOCK() (void)0
#define MY_KMALLOC_RELEASE_LOCK() (void)0
#endif /* !CONFIG_HAVE_DEBUGGER */

/* The debugger overrides the #PF handler to disable any form of lazy initialization
 * of memory, meaning that if we're being called from there, the only way we can
 * safely allocate memory is by allocating from the LOCKED heap with the PREFAULT
 * flag set (thus preventing any possibility of triggering a pagefault in case new
 * memory had to be allocated) */
#ifndef CONFIG_NO_DEBUGGER
#define MY_KMALLOC_HEAP (&kernel_locked_heap)
#define MY_KMALLOC_GFP  (GFP_LOCKED | GFP_PREFLT)
#else /* !CONFIG_NO_DEBUGGER */
#define MY_KMALLOC_HEAP (&kernel_default_heap)
#define MY_KMALLOC_GFP  (GFP_NORMAL)
#endif /* CONFIG_NO_DEBUGGER */


PRIVATE NOBLOCK ATTR_MALLOC WUNUSED void *
NOTHROW(CC my_kmalloc_untraced_nx)(size_t num_bytes, gfp_t flags) {
	struct heapptr ptr;
	if (kernel_poisoned())
		return NULL; /* Don't access the heap after a poisoning! */
	MY_KMALLOC_ACQUIRE_LOCK();
	ptr = heap_alloc_untraced_nx(MY_KMALLOC_HEAP,
	                             sizeof(size_t) + num_bytes,
	                             flags | MY_KMALLOC_GFP);
	MY_KMALLOC_RELEASE_LOCK();
	if (!ptr.hp_siz)
		return NULL;
	*(size_t *)ptr.hp_ptr = ptr.hp_siz;
	return (size_t *)ptr.hp_ptr + 1;
}

PRIVATE NOBLOCK WUNUSED void *
NOTHROW(CC my_krealloc_untraced_nx)(void *oldptr, size_t num_bytes, gfp_t flags) {
	struct heapptr ptr;
	if (kernel_poisoned())
		return NULL; /* Don't access the heap after a poisoning! */
	MY_KMALLOC_ACQUIRE_LOCK();
	ptr = heap_realloc_untraced_nx(MY_KMALLOC_HEAP,
	                               (size_t *)oldptr - 1,
	                               ((size_t *)oldptr)[-1],
	                               num_bytes + sizeof(size_t),
	                               flags | MY_KMALLOC_GFP,
	                               flags | MY_KMALLOC_GFP);
	MY_KMALLOC_RELEASE_LOCK();
	if (!ptr.hp_siz)
		return NULL;
	*(size_t *)ptr.hp_ptr = ptr.hp_siz;
	return (size_t *)ptr.hp_ptr + 1;
}

PRIVATE NOBLOCK void
NOTHROW(CC my_kfree_untraced)(void *ptr) {
	if (!ptr)
		return;
	if (kernel_poisoned())
		return; /* Don't access the heap after a poisoning! */
	heap_free_untraced(MY_KMALLOC_HEAP,
	                   (size_t *)ptr - 1,
	                   ((size_t *)ptr)[-1],
	                   GFP_ATOMIC | MY_KMALLOC_GFP);
}

#undef MY_KMALLOC_HEAP
#undef MY_KMALLOC_GFP
#endif /* __KERNEL__ */


#ifdef __KERNEL__
#define CACHE_CALLOC(item_count, item_size) my_kmalloc_untraced_nx((item_count) * (item_size), GFP_CALLOC | GFP_ATOMIC)
#define CACHE_RECALLOC(ptr, num_bytes)      my_krealloc_untraced_nx(ptr, num_bytes, GFP_CALLOC | GFP_ATOMIC)
#define CACHE_FREE(ptr)                     my_kfree_untraced(ptr)
#else /* __KERNEL__ */
#define CACHE_CALLOC(item_count, item_size) calloc(item_count, item_size)
#define CACHE_RECALLOC(ptr, num_bytes)      realloc(ptr, num_bytes)
#define CACHE_FREE(ptr)                     free(ptr)
#define CACHE_RECALLOC_DOES_NOT_CLEAR 1
#endif /* !__KERNEL__ */





/* Finalize the given abbreviation code controller. */
INTERN NONNULL((1)) void
NOTHROW_NCX(CC libdi_debuginfo_cu_abbrev_fini)(di_debuginfo_cu_abbrev_t *__restrict self) {
	if (self->dua_cache_list != self->dua_stcache &&
	    self->dua_cache_list != (di_debuginfo_cu_abbrev_cache_entry_t *)-1) {
		CACHE_FREE(self->dua_cache_list);
	}
#ifndef NDEBUG
	memset(self, 0xcc, offsetof(di_debuginfo_cu_abbrev_t, dua_stcache));
#endif /* !NDEBUG */
}

INTERN NONNULL((1, 2)) bool
NOTHROW_NCX(CC libdi_debuginfo_cu_abbrev_do_lookup)(byte_t *__restrict reader,
                                                    byte_t *__restrict abbrev_end,
                                                    di_debuginfo_component_t *__restrict result,
                                                    uintptr_t abbrev_code) {
	while (reader < abbrev_end) {
		uintptr_t code, tag;
		uint8_t has_children;
		byte_t *attrib_pointer;
		uintptr_t attr_name, attr_form;
		code = dwarf_decode_uleb128((byte_t **)&reader);
		if (!code)
			break;
		tag = dwarf_decode_uleb128((byte_t **)&reader);
		has_children = *(uint8_t *)reader;
		reader += 1;
		attrib_pointer = reader;
		while (reader < abbrev_end) {
			attr_name = dwarf_decode_uleb128((byte_t **)&reader);
			attr_form = dwarf_decode_uleb128((byte_t **)&reader);
			if (!attr_name && !attr_form)
				break;
		}
		if (code == abbrev_code) {
			result->dic_tag          = (uintptr_half_t)tag;
			result->dic_haschildren  = has_children;
			result->dic_attrib_start = (di_debuginfo_component_attrib_t *)attrib_pointer;
			result->dic_attrib_end   = (di_debuginfo_component_attrib_t *)reader;
			return true;
		}
	}
	return false;
}



INTERN NONNULL((1, 2)) bool
NOTHROW_NCX(CC libdi_debuginfo_cu_abbrev_lookup)(di_debuginfo_cu_abbrev_t *__restrict self,
                                                 di_debuginfo_component_t *__restrict result,
                                                 uintptr_t abbrev_code) {
#if 0
	return libdi_debuginfo_cu_abbrev_do_lookup(self->dua_abbrev_start,
	                                           self->dua_abbrev_end,
	                                           result, abbrev_code);
#else
	size_t i;
	di_debuginfo_cu_abbrev_cache_entry_t *list;
	list = self->dua_cache_list;
	if (list == self->dua_stcache ||
	    list == (di_debuginfo_cu_abbrev_cache_entry_t *)-1) {
		i = self->dua_cache_next;
		while (i) {
			--i;
			if (self->dua_stcache[i].ace_code == abbrev_code) {
				/* Found it! */
				memcpy(result, &self->dua_stcache[i].ace_comp,
				       sizeof(di_debuginfo_component_t));
				return true;
			}
		}
		i = self->dua_cache_size;
		while (i > self->dua_cache_next) {
			--i;
			if (self->dua_stcache[i].ace_code == abbrev_code) {
				/* Found it! */
				memcpy(result, &self->dua_stcache[i].ace_comp,
				       sizeof(di_debuginfo_component_t));
				return true;
			}
		}
		if (!libdi_debuginfo_cu_abbrev_do_lookup(self->dua_abbrev_start,
		                                         self->dua_abbrev_end,
		                                         result, abbrev_code))
			return false;
		if (self->dua_cache_next >= COMPILER_LENOF(self->dua_stcache)) {
			if (self->dua_cache_size >= COMPILER_LENOF(self->dua_stcache)) {
				if (list != (di_debuginfo_cu_abbrev_cache_entry_t *)-1) {
					/* Try to move into the territory of dynamically allocated caches. */
					size_t initial_cache_size;
					initial_cache_size = MIN_C(COMPILER_LENOF(self->dua_stcache) * 2,
					                           CONFIG_DEBUGINFO_ABBREV_CACHE_MAXSIZE);
					list = (di_debuginfo_cu_abbrev_cache_entry_t *)CACHE_CALLOC(initial_cache_size,
					                                                            sizeof(di_debuginfo_cu_abbrev_cache_entry_t));
					if (list) {
						memcpy(list, self->dua_stcache, sizeof(self->dua_stcache));
						self->dua_cache_list = list;
						self->dua_cache_size = initial_cache_size;
						self->dua_cache_next = COMPILER_LENOF(self->dua_stcache);
						self->dua_stcache[0].ace_code = 0; /* Allow further re-sizing */
						goto do_fill_dynamic_cache;
					}
					self->dua_cache_list = (di_debuginfo_cu_abbrev_cache_entry_t *)-1;
				}
			} else {
				/* Increase the used buffer size. */
				++self->dua_cache_size;
			}
			self->dua_cache_next = 0;
		}
		self->dua_stcache[self->dua_cache_next].ace_code = abbrev_code;
		memcpy(&self->dua_stcache[self->dua_cache_next].ace_comp,
		       result,
		       sizeof(di_debuginfo_component_t));
		++self->dua_cache_next;
		if (self->dua_cache_size < self->dua_cache_next)
			self->dua_cache_size = self->dua_cache_next;
	} else {
		i = self->dua_cache_next;
		while (i) {
			--i;
			if (list[i].ace_code == abbrev_code) {
				/* Found it! */
				memcpy(result, &list[i].ace_comp,
				       sizeof(di_debuginfo_component_t));
				return true;
			}
		}
		i = self->dua_cache_size;
		while (i > self->dua_cache_next) {
			--i;
			if (list[i].ace_code == abbrev_code) {
				/* Found it! */
				memcpy(result, &list[i].ace_comp,
				       sizeof(di_debuginfo_component_t));
				return true;
			}
		}
		if (self->dua_cache_next >= self->dua_cache_size) {
			if (self->dua_cache_size < CONFIG_DEBUGINFO_ABBREV_CACHE_MAXSIZE &&
			    self->dua_stcache[0].ace_code == 0) {
				size_t new_cache_size;
				/* Increase the cache size. */
				new_cache_size = MIN(self->dua_cache_size * 2, CONFIG_DEBUGINFO_ABBREV_CACHE_MAXSIZE);
				list = (di_debuginfo_cu_abbrev_cache_entry_t *)CACHE_RECALLOC(list,
				                                                              new_cache_size *
				                                                              sizeof(di_debuginfo_cu_abbrev_cache_entry_t));
				if likely(list) {
#ifdef CACHE_RECALLOC_DOES_NOT_CLEAR
					memset(list + self->dua_cache_size, 0,
					       (new_cache_size - self->dua_cache_size) *
					       sizeof(di_debuginfo_cu_abbrev_cache_entry_t));
#endif /* CACHE_RECALLOC_DOES_NOT_CLEAR */
					self->dua_cache_list = list;
					self->dua_cache_next = self->dua_cache_size;
					self->dua_cache_size = new_cache_size;
					goto do_lookup_for_dynamic_cache;
				} else {
					list = self->dua_cache_list;
					self->dua_stcache[0].ace_code = 1; /* Disable further re-sizing */
				}
			}
			self->dua_cache_next = 0;
		}
do_lookup_for_dynamic_cache:
		if (!libdi_debuginfo_cu_abbrev_do_lookup(self->dua_abbrev_start,
		                                         self->dua_abbrev_end,
		                                         result, abbrev_code))
			return false;
do_fill_dynamic_cache:
		list[self->dua_cache_next].ace_code = abbrev_code;
		memcpy(&list[self->dua_cache_next].ace_comp,
		       result,
		       sizeof(di_debuginfo_component_t));
		++self->dua_cache_next;
	}
	return true;
#endif
}


/* Given a pointer to the start of a debug_info CU (or a pointer to the start
 * of the .debug_info section), as well as the start & end of the .debug_abbrev
 * section, initialize the given debuginfo CU parser structure `result', and
 * advance `*pdebug_info_reader' to the start of the next unit.
 * NOTE: Upon success (return == DEBUG_INFO_ERROR_SUCCESS), the caller is responsible for
 *       finalizing the given `abbrev' through use of `debuginfo_cu_abbrev_fini(abbrev)',
 *       once the associated parser `result' is no longer being used.
 * @param: first_component_pointer: A pointer to the first component to load, or `NULL'
 *                                  to simply load the first component following the
 *                                  start of the associated CU descriptor.
 * @return: DEBUG_INFO_ERROR_SUCCESS: ...
 * @return: DEBUG_INFO_ERROR_NOFRAME: All units have been loaded.
 * @return: DEBUG_INFO_ERROR_CORRUPT: ... */
INTERN TEXTSECTION NONNULL((1, 2, 3, 4, 5)) unsigned int
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_loadunit)(byte_t **__restrict pdebug_info_reader,
                                                   byte_t *__restrict debug_info_end,
                                                   di_debuginfo_cu_parser_sections_t const *__restrict sectinfo,
                                                   di_debuginfo_cu_parser_t *__restrict result,
                                                   di_debuginfo_cu_abbrev_t *__restrict abbrev,
                                                   byte_t *first_component_pointer) {
	uintptr_t temp;
	byte_t *reader;
	reader = *pdebug_info_reader;
again:
	if (reader >= debug_info_end)
		return DEBUG_INFO_ERROR_NOFRAME;
	result->dup_cu_info_hdr = reader;
	/* 7.5.1.1   Compilation Unit Header */
	temp = UNALIGNED_GET32((uint32_t *)reader); /* unit_length */
	reader += 4;
	result->dup_ptrsize = 4;
	if (temp >= UINT32_C(0xfffffff0)) {
		if (temp == UINT32_C(0xffffffff)) {
			/* 7.4 32-Bit and 64-Bit DWARF Formats
			 * In the 64-bit DWARF format, an initial length field is 96 bits in size, and has two parts:
			 *  - The first 32-bits have the value 0xffffffff.
			 *  - The following 64-bits contain the actual length represented as an unsigned 64-bit integer. */
			result->dup_ptrsize = 8;
			temp = (uintptr_t)UNALIGNED_GET64((uint64_t *)reader);
			reader += 8;
		} else {
			/* 7.2.2 Initial Length Values
			 * ...
			 * values 0xfffffff0 through 0xffffffff are reserved by DWARF */
			return DEBUG_INFO_ERROR_CORRUPT;
		}
	}
	*pdebug_info_reader = result->dup_cu_info_end;
	if (OVERFLOW_UADD((uintptr_t)reader, temp, (uintptr_t *)&result->dup_cu_info_end) ||
	    result->dup_cu_info_end > debug_info_end)
		result->dup_cu_info_end = debug_info_end;
	result->dup_version = UNALIGNED_GET16((uint16_t *)reader); /* version */
	reader += 2;
#if 0
	if unlikely(result->dup_version != 2)
		return DEBUG_INFO_ERROR_CORRUPT;
#endif
	temp = UNALIGNED_GET32((uint32_t *)reader); /* debug_abbrev_offset */
	reader += 4;
	if (temp == 0xffffffff) {
		temp = (uintptr_t)UNALIGNED_GET64((uint64_t *)reader);
		reader += 8;
	}
	if unlikely(OVERFLOW_UADD((uintptr_t)sectinfo->cps_debug_abbrev_start, temp,
	                          (uintptr_t *)&abbrev->dua_abbrev_start) ||
	            abbrev->dua_abbrev_start >= sectinfo->cps_debug_abbrev_end)
		return DEBUG_INFO_ERROR_CORRUPT;
	abbrev->dua_abbrev_end = sectinfo->cps_debug_abbrev_end;
	result->dup_addrsize   = *(uint8_t *)reader; /* address_size */
	reader += 1;
#if __SIZEOF_POINTER__ > 4
	if unlikely(result->dup_addrsize != 1 &&
	            result->dup_addrsize != 2 &&
	            result->dup_addrsize != 4 &&
	            result->dup_addrsize != 8)
		return DEBUG_INFO_ERROR_CORRUPT;
#else /* __SIZEOF_POINTER__ > 4 */
	if unlikely(result->dup_addrsize != 1 &&
	            result->dup_addrsize != 2 &&
	            result->dup_addrsize != 4)
		return DEBUG_INFO_ERROR_CORRUPT;
#endif /* __SIZEOF_POINTER__ <= 4 */
	result->dup_cu_info_pos = reader;
	if (first_component_pointer) {
		/* Check if the given pointer is apart of this CU.
		 * Otherwise, continue onwards to the next CU. */
		if (first_component_pointer >= result->dup_cu_info_end)
			goto again;
		if (first_component_pointer < reader)
			return DEBUG_INFO_ERROR_NOFRAME;
		result->dup_cu_info_pos = first_component_pointer;
	}
	reader                 = result->dup_cu_info_end;
	result->dup_sections   = sectinfo;
	result->dup_cu_abbrev  = abbrev;
	abbrev->dua_cache_list = abbrev->dua_stcache;
	abbrev->dua_cache_size = 0;
	abbrev->dua_cache_next = 0;
	/* Load the first component of the compilation unit. */
	if (!libdi_debuginfo_cu_parser_next(result)) {
		libdi_debuginfo_cu_abbrev_fini(abbrev);
		goto again;
	}
	*pdebug_info_reader     = reader;
	result->dup_child_depth = 0;
	return DEBUG_INFO_ERROR_SUCCESS;
}



/* Skip data associated with the given attribute form.
 * @param: form: One of `DW_FORM_*' */
INTERN TEXTSECTION NONNULL((1)) void
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_skipform)(di_debuginfo_cu_parser_t *__restrict self,
                                                   dwarf_uleb128_t form) {
decode_form:
	switch (form) {

	case DW_FORM_addr:
		self->dup_cu_info_pos += self->dup_addrsize;
		break;

	case DW_FORM_ref_addr:
	case DW_FORM_strp:
	case DW_FORM_sec_offset:
		self->dup_cu_info_pos += self->dup_ptrsize;
		break;

	case DW_FORM_block1: {
		uint8_t length;
		length = *(uint8_t *)self->dup_cu_info_pos;
		self->dup_cu_info_pos += 1;
		if (OVERFLOW_UADD((uintptr_t)self->dup_cu_info_pos, length, (uintptr_t *)&self->dup_cu_info_pos))
			self->dup_cu_info_pos = (byte_t *)-1;
	}	break;

	case DW_FORM_block2: {
		uint16_t length;
		length = UNALIGNED_GET16((uint16_t *)self->dup_cu_info_pos);
		self->dup_cu_info_pos += 2;
		if (OVERFLOW_UADD((uintptr_t)self->dup_cu_info_pos, length, (uintptr_t *)&self->dup_cu_info_pos))
			self->dup_cu_info_pos = (byte_t *)-1;
	}	break;

	case DW_FORM_block4: {
		uint32_t length;
		length = UNALIGNED_GET32((uint32_t *)self->dup_cu_info_pos);
		self->dup_cu_info_pos += 4;
		if (OVERFLOW_UADD((uintptr_t)self->dup_cu_info_pos, length, (uintptr_t *)&self->dup_cu_info_pos))
			self->dup_cu_info_pos = (byte_t *)-1;
	}	break;

	case DW_FORM_block:
	case DW_FORM_exprloc: {
		uintptr_t length;
		length = dwarf_decode_uleb128((byte_t **)&self->dup_cu_info_pos);
		if (OVERFLOW_UADD((uintptr_t)self->dup_cu_info_pos, length, (uintptr_t *)&self->dup_cu_info_pos))
			self->dup_cu_info_pos = (byte_t *)-1;
	}	break;

	case DW_FORM_flag:
	case DW_FORM_data1:
	case DW_FORM_ref1:
		self->dup_cu_info_pos += 1;
		break;

	case DW_FORM_data2:
	case DW_FORM_ref2:
		self->dup_cu_info_pos += 2;
		break;

	case DW_FORM_data4:
	case DW_FORM_ref4:
		self->dup_cu_info_pos += 4;
		break;

	case DW_FORM_data8:
	case DW_FORM_ref8:
	case DW_FORM_ref_sig8:
		self->dup_cu_info_pos += 8;
		break;

	case DW_FORM_sdata:
		dwarf_decode_sleb128((byte_t **)&self->dup_cu_info_pos);
		break;

	case DW_FORM_udata:
	case DW_FORM_ref_udata:
		dwarf_decode_uleb128((byte_t **)&self->dup_cu_info_pos);
		break;

	case DW_FORM_string:
		self->dup_cu_info_pos = (byte_t *)strnend((char *)self->dup_cu_info_pos,
		                                          (size_t)(self->dup_cu_info_end -
		                                                   self->dup_cu_info_pos)) +
		                        1;
		break;

	case DW_FORM_indirect:
		if unlikely(self->dup_cu_info_pos >= self->dup_cu_info_end)
			break;
		form = dwarf_decode_uleb128((byte_t **)&self->dup_cu_info_pos);
		goto decode_form;

	case DW_FORM_flag_present:
		break;

	default: break;
	}
}


/* Start a new component.
 * @return: true:  ...
 * @return: false: [debuginfo_cu_parser_next] All components have been parsed.
 * @return: false: [*] The next component doesn't exist, or isn't a child/sibling/parent. */
INTERN TEXTSECTION NONNULL((1)) bool
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_next)(di_debuginfo_cu_parser_t *__restrict self) {
	uintptr_t abbrev_code;
	if (self->dup_comp.dic_haschildren != DW_CHILDREN_no)
		++self->dup_child_depth;
again:
	if (self->dup_cu_info_pos >= self->dup_cu_info_end)
		return false; /* EOF */
	/* DWARF 7.5.2: Each debugging information entry begins with an unsigned
	 * LEB128 number containing the abbreviation code for the entry */
	abbrev_code = dwarf_decode_uleb128(&self->dup_cu_info_pos);
	if (!abbrev_code) {
		if (self->dup_child_depth)
			--self->dup_child_depth;
		goto again; /* Ignored */
	}
	/* Lookup the associated abbreviation code. */
	return libdi_debuginfo_cu_abbrev_lookup(self->dup_cu_abbrev,
	                                        &self->dup_comp,
	                                        abbrev_code);
}

INTERN TEXTSECTION NONNULL((1)) bool
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_nextchild)(di_debuginfo_cu_parser_t *__restrict self) {
	if (!self->dup_comp.dic_haschildren)
		return false;
	return libdi_debuginfo_cu_parser_next(self);
}

INTERN TEXTSECTION NONNULL((1)) bool
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_nextsibling)(di_debuginfo_cu_parser_t *__restrict self) {
	byte_t *reader;
	if (self->dup_comp.dic_haschildren)
		return false;
	reader = self->dup_cu_info_pos;
	if (reader >= self->dup_cu_info_end ||
	    dwarf_decode_uleb128(&reader) == 0)
		return false;
	return libdi_debuginfo_cu_parser_next(self);
}

INTERN TEXTSECTION NONNULL((1)) bool
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_nextparent)(di_debuginfo_cu_parser_t *__restrict self) {
	byte_t *reader;
	if (self->dup_comp.dic_haschildren)
		return false;
	reader = self->dup_cu_info_pos;
	if (reader >= self->dup_cu_info_end ||
	    dwarf_decode_uleb128(&reader) != 0)
		return false;
	if (reader >= self->dup_cu_info_end ||
	    dwarf_decode_uleb128(&reader) == 0)
		return false;
	return libdi_debuginfo_cu_parser_next(self);
}

/* Skip the attributes of the current component (must be called if not
 * parsed explicitly prior to the next call to `debuginfo_cu_parser_next*')
 * @return: DEBUG_INFO_ERROR_SUCCESS: ...
 * @return: DEBUG_INFO_ERROR_CORRUPT: ... */
INTERN TEXTSECTION NONNULL((1)) void
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_skipattr)(di_debuginfo_cu_parser_t *__restrict self) {
	di_debuginfo_component_attrib_t attr;
	DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, self) {
		(void)attr.dica_name;
		(void)attr.dica_form;
	}
}

INTERN_CONST STRINGSECTION char const unknown_string[] = "??" "?";

/* Load the current debug information as an attribute encoded as
 * `form' into a storage class matching the given result-operand.
 *  - debuginfo_cu_parser_getstring(): DW_FORM_strp, DW_FORM_string
 *  - debuginfo_cu_parser_getaddr():   DW_FORM_addr
 *  - debuginfo_cu_parser_getconst():  DW_FORM_data1, DW_FORM_data2, DW_FORM_data4, DW_FORM_data8, DW_FORM_sdata, DW_FORM_udata, DW_FORM_sec_offset
 *  - debuginfo_cu_parser_getflag():   DW_FORM_flag, DW_FORM_flag_present
 *  - debuginfo_cu_parser_getref():    DW_FORM_ref_addr, DW_FORM_ref1, DW_FORM_ref2, DW_FORM_ref4, DW_FORM_ref8, DW_FORM_ref_sig8, DW_FORM_ref_udata
 *  - debuginfo_cu_parser_getexpr():   DW_FORM_exprloc */
INTERN TEXTSECTION NONNULL((1, 3)) bool
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_getstring)(di_debuginfo_cu_parser_t const *__restrict self,
                                                    uintptr_t form, char **__restrict presult) {
	byte_t *reader;
	reader = self->dup_cu_info_pos;
decode_form:
	switch (form) {

	case DW_FORM_strp: {
		char *result;
		uintptr_t offset;
		switch (self->dup_ptrsize) {

		case 4:
			offset = (uintptr_t)UNALIGNED_GET32((uint32_t *)reader);
			break;

		case 8:
			offset = (uintptr_t)UNALIGNED_GET64((uint64_t *)reader);
			break;

		default:
			__builtin_unreachable();
		}
		result = (char *)self->dup_sections->cps_debug_str_start + offset;
		if unlikely(offset >= (size_t)(self->dup_sections->cps_debug_str_end -
		                               self->dup_sections->cps_debug_str_start)) {
			if unlikely(self->dup_sections->cps_debug_str_start !=
			            self->dup_sections->cps_debug_str_end)
				ERROR(err);
			result = (char *)unknown_string;
		}
		*presult = result;
		return true;
	}	break;

	case DW_FORM_string:
		*presult = (char *)reader;
		return true;

	case DW_FORM_indirect:
		if unlikely(reader >= self->dup_cu_info_end)
			break;
		form = dwarf_decode_uleb128((byte_t **)&reader);
		goto decode_form;

	default: break;
	}
err:
	return false;
}

INTERN TEXTSECTION NONNULL((1, 3)) bool
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_getaddr)(di_debuginfo_cu_parser_t const *__restrict self,
                                                  uintptr_t form, uintptr_t *__restrict presult) {
	byte_t *reader;
	reader = self->dup_cu_info_pos;
decode_form:
	switch (form) {

	case DW_FORM_addr:
		switch (self->dup_addrsize) {

		case 1:
			*presult = *(uint8_t *)reader;
			break;

		case 2:
			*presult = UNALIGNED_GET16((uint16_t *)reader);
			break;

		case 4:
			*presult = UNALIGNED_GET32((uint32_t *)reader);
			break;

#if __SIZEOF_POINTER__ > 4
		case 8:
			*presult = UNALIGNED_GET64((uint64_t *)reader);
			break;
#endif /* __SIZEOF_POINTER__ > 4 */

		default:
			__builtin_unreachable();
		}
		return true;

	case DW_FORM_indirect:
		if unlikely(reader >= self->dup_cu_info_end)
			break;
		form = dwarf_decode_uleb128((byte_t **)&reader);
		goto decode_form;

	default: break;
	}
	return false;
}

INTERN TEXTSECTION NONNULL((1, 3)) bool
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_getconst)(di_debuginfo_cu_parser_t const *__restrict self,
                                                   uintptr_t form, uintptr_t *__restrict presult) {
	byte_t *reader;
	reader = self->dup_cu_info_pos;
decode_form:
	switch (form) {
	case DW_FORM_sec_offset:
		switch (self->dup_ptrsize) {

		case 4:
			*presult = (uintptr_t)UNALIGNED_GET32((uint32_t *)reader);
			break;

		case 8:
			*presult = (uintptr_t)UNALIGNED_GET64((uint64_t *)reader);
			break;

		default:
			__builtin_unreachable();
		}
		return true;

	case DW_FORM_data1: /* constant */
		*presult = (uintptr_t) * (uint8_t *)reader;
		return true;

	case DW_FORM_data2: /* constant */
		*presult = (uintptr_t)UNALIGNED_GET16((uint16_t *)reader);
		return true;

	case DW_FORM_data4: /* constant */
		*presult = (uintptr_t)UNALIGNED_GET32((uint32_t *)reader);
		return true;

	case DW_FORM_data8: /* constant */
		*presult = (uintptr_t)UNALIGNED_GET64((uint64_t *)reader);
		return true;

	case DW_FORM_sdata: /* constant */
		*presult = (uintptr_t)dwarf_decode_sleb128((byte_t **)&reader);
		return true;

	case DW_FORM_udata: /* constant */
		*presult = (uintptr_t)dwarf_decode_uleb128((byte_t **)&reader);
		return true;

	case DW_FORM_indirect:
		if unlikely(reader >= self->dup_cu_info_end)
			break;
		form = dwarf_decode_uleb128((byte_t **)&reader);
		goto decode_form;

	default: break;
	}
	return false;
}

INTERN TEXTSECTION NONNULL((1, 3)) bool
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_getflag)(di_debuginfo_cu_parser_t const *__restrict self,
                                                  uintptr_t form, bool *__restrict presult) {
	byte_t *reader;
	reader = self->dup_cu_info_pos;
decode_form:
	switch (form) {

	case DW_FORM_flag: /* constant */
		*presult = *(uint8_t *)reader ? true : false;
		return true;

	case DW_FORM_flag_present: /* constant */
		*presult = true;
		return true;

	case DW_FORM_indirect:
		if unlikely(reader >= self->dup_cu_info_end)
			break;
		form = dwarf_decode_uleb128((byte_t **)&reader);
		goto decode_form;

	default: break;
	}
	return false;
}

INTERN TEXTSECTION NONNULL((1, 3)) bool
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_getref)(di_debuginfo_cu_parser_t const *__restrict self,
                                                 uintptr_t form, byte_t **__restrict presult) {
	byte_t *reader;
	uintptr_t offset;
	reader = self->dup_cu_info_pos;
decode_form:
	switch (form) {

	case DW_FORM_ref_addr:
		switch (self->dup_ptrsize) {

		case 4:
			offset = (uintptr_t)UNALIGNED_GET32((uint32_t *)reader);
			break;

		case 8:
			offset = (uintptr_t)UNALIGNED_GET64((uint64_t *)reader);
			break;

		default:
			__builtin_unreachable();
		}
		break;

	case DW_FORM_ref1:
		offset = (uintptr_t) * (uint8_t *)reader;
		break;

	case DW_FORM_ref2:
		offset = (uintptr_t)UNALIGNED_GET16((uint16_t *)reader);
		break;

	case DW_FORM_ref4:
		offset = (uintptr_t)UNALIGNED_GET32((uint32_t *)reader);
		break;

	case DW_FORM_ref8:
	case DW_FORM_ref_sig8: /* ??? */
		offset = (uintptr_t)UNALIGNED_GET64((uint64_t *)reader);
		break;

	case DW_FORM_ref_udata:
		offset = dwarf_decode_uleb128((byte_t **)&reader);
		break;

	case DW_FORM_indirect:
		if unlikely(reader >= self->dup_cu_info_end)
			ERROR(err);
		form = dwarf_decode_uleb128((byte_t **)&reader);
		goto decode_form;

	default:
		return false;
	}
	if unlikely(offset >= (size_t)(self->dup_cu_info_end -
	                               self->dup_cu_info_hdr))
		ERROR(err);
	*presult = self->dup_cu_info_hdr + offset;
	return true;
err:
	return false;
}


INTERN TEXTSECTION NONNULL((1, 3)) bool
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_getexpr)(di_debuginfo_cu_parser_t const *__restrict self,
                                                  uintptr_t form,
                                                  di_debuginfo_location_t *__restrict result) {
	byte_t *reader;
	reader = self->dup_cu_info_pos;
decode_form:
	switch (form) {

	case DW_FORM_sec_offset: {
		uintptr_t offset;
		switch (self->dup_ptrsize) {

		case 4:
			offset = (uintptr_t)UNALIGNED_GET32((uint32_t *)reader);
			break;

		case 8:
			offset = (uintptr_t)UNALIGNED_GET64((uint64_t *)reader);
			break;

		default:
			__builtin_unreachable();
		}
		result->l_expr  = NULL;
		result->l_llist = NULL;
		if (self->dup_sections->cps_debug_loc_start <
		    self->dup_sections->cps_debug_loc_end) {
			/* Location list information was loaded by the caller. */
			result->l_llist = self->dup_sections->cps_debug_loc_start + offset;
			/* Check for corrupted location list offsets. */
			if unlikely(result->l_llist >= self->dup_sections->cps_debug_loc_end)
				ERROR(err);
			return true;
		}
	}	break;

	case DW_FORM_exprloc:
		result->l_expr  = reader;
		result->l_llist = NULL;
		return true;

	case DW_FORM_indirect:
		if unlikely(reader >= self->dup_cu_info_end)
			break;
		form = dwarf_decode_uleb128((byte_t **)&reader);
		goto decode_form;

	default: break;
	}
err:
	return false;
}


/* Load attributes specific to a certain component:
 *   - debuginfo_cu_parser_loadattr_compile_unit():       DW_TAG_compile_unit
 *   - debuginfo_cu_parser_loadattr_subprogram():         DW_TAG_subprogram
 *   - debuginfo_cu_parser_loadattr_inlined_subroutine(): DW_TAG_inlined_subroutine
 *   - debuginfo_cu_parser_loadattr_lexical_block():      DW_TAG_lexical_block, DW_TAG_try_block, DW_TAG_catch_block
 *   - debuginfo_cu_parser_loadattr_type():               DW_TAG_*_type
 *   - debuginfo_cu_parser_loadattr_member():             DW_TAG_member
 *   - debuginfo_cu_parser_loadattr_variable():           DW_TAG_variable, DW_TAG_formal_parameter
 * @return: true:  Successfully loaded the component attributes.
 * @return: false: Corrupted/incomplete attributes. */
INTERN TEXTSECTION NONNULL((1, 2)) bool
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_loadattr_compile_unit)(di_debuginfo_cu_parser_t *__restrict self,
                                                                di_debuginfo_compile_unit_t *__restrict result) {
	di_debuginfo_component_attrib_t attr;
	bool high_pc_is_relative          = false;
	result->cu_stmt_list              = (uintptr_t)-1;
	result->cu_name                   = NULL;
	result->cu_comp_dir               = NULL;
	result->cu_ranges.r_ranges_offset = (uintptr_t)-1;
	result->cu_ranges.r_startpc       = (uintptr_t)-1;
	result->cu_ranges.r_endpc         = 0;
	result->cu_addr_base              = 0;
	DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, self) {
		switch (attr.dica_name) {

		case DW_AT_name:
			if unlikely(!libdi_debuginfo_cu_parser_getstring(self, attr.dica_form,
			                                                 &result->cu_name))
				ERROR(err);
			break;

		case DW_AT_comp_dir:
			if unlikely(!libdi_debuginfo_cu_parser_getstring(self, attr.dica_form,
			                                                 &result->cu_comp_dir))
				ERROR(err);
			break;

		case DW_AT_ranges:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->cu_ranges.r_ranges_offset))
				ERROR(err);
			break;

		case DW_AT_low_pc:
			if unlikely(!libdi_debuginfo_cu_parser_getaddr(self, attr.dica_form,
			                                               &result->cu_ranges.r_startpc))
				ERROR(err);
			break;

		case DW_AT_high_pc:
			if (!libdi_debuginfo_cu_parser_getaddr(self, attr.dica_form, &result->cu_ranges.r_endpc)) {
				if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
				                                                &result->cu_ranges.r_endpc))
					ERROR(err);
				high_pc_is_relative = true;
			}
			break;

		case DW_AT_stmt_list:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->cu_stmt_list))
				ERROR(err);
			break;

		case DW_AT_addr_base:
		case DW_AT_GNU_addr_base:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->cu_addr_base))
				ERROR(err);
			break;

		default: break;
		}
	}
	if (high_pc_is_relative)
		result->cu_ranges.r_endpc += result->cu_ranges.r_startpc;
	return true;
err:
	return false;
}

INTERN TEXTSECTION NONNULL((1, 2)) bool
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_loadattr_subprogram)(di_debuginfo_cu_parser_t *__restrict self,
                                                              di_debuginfo_subprogram_t *__restrict result) {
	di_debuginfo_component_attrib_t attr;
	bool high_pc_is_relative = false;
	bool flag;
	result->sp_flags                  = DW_SUBPROGRAM_FNORMAL;
	result->sp_name                   = NULL;
	result->sp_rawname                = NULL;
	result->sp_frame_base.l_expr      = NULL;
	result->sp_frame_base.l_llist     = NULL;
	result->sp_ranges.r_ranges_offset = (uintptr_t)-1;
	result->sp_ranges.r_startpc       = (uintptr_t)-1;
	result->sp_ranges.r_endpc         = 0;
	result->sp_decl_file              = 0;
	result->sp_decl_line              = 0;
	result->sp_decl_column            = 0;
	DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, self) {
		switch (attr.dica_name) {

		case DW_AT_name:
			if unlikely(!libdi_debuginfo_cu_parser_getstring(self, attr.dica_form,
			                                                 &result->sp_name))
				ERROR(err);
			break;

		case DW_AT_linkage_name:
			if unlikely(!libdi_debuginfo_cu_parser_getstring(self, attr.dica_form,
			                                                 &result->sp_rawname))
				ERROR(err);
			break;

		case DW_AT_ranges:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->sp_ranges.r_ranges_offset))
				ERROR(err);
			break;

		case DW_AT_low_pc:
			if unlikely(!libdi_debuginfo_cu_parser_getaddr(self, attr.dica_form,
			                                               &result->sp_ranges.r_startpc))
				ERROR(err);
			break;

		case DW_AT_high_pc:
			if (!libdi_debuginfo_cu_parser_getaddr(self, attr.dica_form, &result->sp_ranges.r_endpc)) {
				if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
				                                                &result->sp_ranges.r_endpc))
					ERROR(err);
				high_pc_is_relative = true;
			}
			break;

		case DW_AT_frame_base:
			if unlikely(!libdi_debuginfo_cu_parser_getexpr(self, attr.dica_form,
			                                               &result->sp_frame_base))
				ERROR(err);
			break;

		case DW_AT_decl_file:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->sp_decl_file))
				ERROR(err);
			break;

		case DW_AT_decl_line:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->sp_decl_line))
				ERROR(err);
			break;

		case DW_AT_decl_column:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->sp_decl_column))
				ERROR(err);
			break;

		case DW_AT_external:
			if unlikely(!libdi_debuginfo_cu_parser_getflag(self, attr.dica_form, &flag))
				ERROR(err);
			if (flag)
				result->sp_flags |= DW_SUBPROGRAM_FEXTERN;
			break;

		case DW_AT_noreturn:
			if unlikely(!libdi_debuginfo_cu_parser_getflag(self, attr.dica_form, &flag))
				ERROR(err);
			if (flag)
				result->sp_flags |= DW_SUBPROGRAM_FNORETURN;
			break;

		default: break;
		}
	}
	if (!result->sp_rawname)
		result->sp_rawname = result->sp_name;
	else if (!result->sp_name)
		result->sp_name = result->sp_rawname;
	if (high_pc_is_relative)
		result->sp_ranges.r_endpc += result->sp_ranges.r_startpc;
	return true;
err:
	return false;
}

INTERN TEXTSECTION NONNULL((1, 2)) bool
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_loadattr_inlined_subroutine)(di_debuginfo_cu_parser_t *__restrict self,
                                                                      di_debuginfo_inlined_subroutine_t *__restrict result) {
	di_debuginfo_component_attrib_t attr;
	bool high_pc_is_relative          = false;
	result->is_subprogram             = NULL;
	result->is_ranges.r_ranges_offset = (uintptr_t)-1;
	result->is_ranges.r_startpc       = (uintptr_t)-1;
	result->is_ranges.r_endpc         = 0;
	result->is_call_file              = 0;
	result->is_call_line              = 0;
	result->is_call_column            = 0;
	DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, self) {
		switch (attr.dica_name) {

		case DW_AT_ranges:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->is_ranges.r_ranges_offset))
				ERROR(err);
			break;

		case DW_AT_low_pc:
			if unlikely(!libdi_debuginfo_cu_parser_getaddr(self, attr.dica_form,
			                                               &result->is_ranges.r_startpc))
				ERROR(err);
			break;

		case DW_AT_high_pc:
			if (!libdi_debuginfo_cu_parser_getaddr(self, attr.dica_form, &result->is_ranges.r_endpc)) {
				if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
				                                                &result->is_ranges.r_endpc))
					ERROR(err);
				high_pc_is_relative = true;
			}
			break;

		case DW_AT_abstract_origin:
			if unlikely(!libdi_debuginfo_cu_parser_getref(self, attr.dica_form,
			                                              &result->is_subprogram))
				ERROR(err);
			break;

		case DW_AT_call_column:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->is_call_column))
				ERROR(err);
			break;

		case DW_AT_call_file:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->is_call_file))
				ERROR(err);
			break;

		case DW_AT_call_line:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->is_call_line))
				ERROR(err);
			break;

		default: break;
		}
	}
	if (high_pc_is_relative)
		result->is_ranges.r_endpc += result->is_ranges.r_startpc;
	return true;
err:
	return false;
}

INTERN TEXTSECTION NONNULL((1, 2)) bool
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_loadattr_lexical_block)(di_debuginfo_cu_parser_t *__restrict self,
                                                                 di_debuginfo_lexical_block_t *__restrict result) {
	di_debuginfo_component_attrib_t attr;
	bool high_pc_is_relative          = false;
	result->lb_ranges.r_ranges_offset = (uintptr_t)-1;
	result->lb_ranges.r_startpc       = (uintptr_t)-1;
	result->lb_ranges.r_endpc         = 0;
	DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, self) {
		switch (attr.dica_name) {

		case DW_AT_ranges:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->lb_ranges.r_ranges_offset))
				ERROR(err);
			break;

		case DW_AT_low_pc:
			if unlikely(!libdi_debuginfo_cu_parser_getaddr(self, attr.dica_form,
			                                               &result->lb_ranges.r_startpc))
				ERROR(err);
			break;

		case DW_AT_high_pc:
			if (!libdi_debuginfo_cu_parser_getaddr(self, attr.dica_form, &result->lb_ranges.r_endpc)) {
				if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
				                                                &result->lb_ranges.r_endpc))
					ERROR(err);
				high_pc_is_relative = true;
			}
			break;

		default: break;
		}
	}
	if (high_pc_is_relative)
		result->lb_ranges.r_endpc += result->lb_ranges.r_startpc;
	return true;
err:
	return false;
}

PRIVATE ATTR_NOINLINE TEXTSECTION NONNULL((1, 2, 3)) bool
NOTHROW_NCX(CC ao_loadattr_type)(di_debuginfo_cu_parser_t *__restrict self,
                                 di_debuginfo_type_t *__restrict result,
                                 byte_t *__restrict abstract_origin) {
	di_debuginfo_cu_parser_t pp;
	memcpy(&pp, self, sizeof(pp));
	pp.dup_cu_info_pos = abstract_origin;
	return likely(libdi_debuginfo_cu_parser_next(&pp)) &&
	       likely(libdi_debuginfo_cu_parser_loadattr_type(&pp, result));
}

PRIVATE ATTR_NOINLINE TEXTSECTION NONNULL((1, 2)) void
NOTHROW_NCX(CC load_array_size_size)(di_debuginfo_cu_parser_t *__restrict self,
                                     di_debuginfo_type_t *__restrict result) {
	di_debuginfo_cu_parser_t pp;
	di_debuginfo_type_t elem_type;
	uintptr_t elem_count;
	memcpy(&pp, self, sizeof(pp));
	if (libdi_debuginfo_cu_parser_nextchild(&pp)) {
		pp.dup_child_depth = 1;
		while (pp.dup_child_depth) {
			if (pp.dup_comp.dic_tag == DW_TAG_subrange_type) {
				di_debuginfo_component_attrib_t attr;
				DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &pp) {
					if (attr.dica_name == DW_AT_upper_bound) {
						if (libdi_debuginfo_cu_parser_getconst(&pp, attr.dica_form, &elem_count))
							++elem_count;
						goto got_elem_count;
					}
				}
			}
			libdi_debuginfo_cu_parser_skipattr(&pp);
			if (!libdi_debuginfo_cu_parser_next(&pp))
				break;
		}
	}
	return;
got_elem_count:
	pp.dup_cu_info_pos = result->t_type;
	if (libdi_debuginfo_cu_parser_next(&pp) &&
	    libdi_debuginfo_cu_parser_loadattr_type(&pp, &elem_type))
		result->t_sizeof = elem_count * elem_type.t_sizeof;
}

PRIVATE ATTR_NOINLINE TEXTSECTION NONNULL((1, 2)) void
NOTHROW_NCX(CC load_pointed_to_size)(di_debuginfo_cu_parser_t *__restrict self,
                                     di_debuginfo_type_t *__restrict result) {
	di_debuginfo_cu_parser_t pp;
	di_debuginfo_type_t inner_type;
	memcpy(&pp, self, sizeof(pp));
	pp.dup_cu_info_pos = result->t_type;
	if (libdi_debuginfo_cu_parser_next(&pp) &&
	    libdi_debuginfo_cu_parser_loadattr_type(&pp, &inner_type))
		result->t_sizeof = inner_type.t_sizeof;
}


INTERN TEXTSECTION NONNULL((1, 2)) bool
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_loadattr_type)(di_debuginfo_cu_parser_t *__restrict self,
                                                        di_debuginfo_type_t *__restrict result) {
	di_debuginfo_component_attrib_t attr;
	result->t_type        = NULL;
	result->t_name        = NULL;
	result->t_rawname     = NULL;
	result->t_decl_file   = 0;
	result->t_decl_line   = 0;
	result->t_decl_column = 0;
	result->t_sizeof      = 0;
	result->t_encoding    = 0;
	DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, self) {
		switch (attr.dica_name) {

		case DW_AT_abstract_origin: {
			byte_t *abstract_origin;
			if unlikely(!libdi_debuginfo_cu_parser_getref(self, attr.dica_form,
			                                              &abstract_origin))
				ERROR(err);
			return ao_loadattr_type(self, result, abstract_origin);
		}	break;

		case DW_AT_type:
			if unlikely(!libdi_debuginfo_cu_parser_getref(self, attr.dica_form,
			                                              &result->t_type))
				ERROR(err);
			break;

		case DW_AT_encoding:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->t_encoding))
				ERROR(err);
			break;

		case DW_AT_name:
			if unlikely(!libdi_debuginfo_cu_parser_getstring(self, attr.dica_form,
			                                                 &result->t_name))
				ERROR(err);
			break;

		case DW_AT_linkage_name:
			if unlikely(!libdi_debuginfo_cu_parser_getstring(self, attr.dica_form,
			                                                 &result->t_rawname))
				ERROR(err);
			break;

		case DW_AT_decl_file:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->t_decl_file))
				ERROR(err);
			break;

		case DW_AT_decl_line:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->t_decl_line))
				ERROR(err);
			break;

		case DW_AT_decl_column:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->t_decl_column))
				ERROR(err);
			break;

		case DW_AT_byte_size:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->t_sizeof))
				ERROR(err);
			break;

		default: break;
		}
	}
	if (!result->t_sizeof) {
		switch (self->dup_comp.dic_tag) {

		case DW_TAG_pointer_type:
		case DW_TAG_reference_type:
		case DW_TAG_rvalue_reference_type:
			result->t_sizeof = self->dup_addrsize;
			break;

		case DW_TAG_array_type:
			if (result->t_type)
				load_array_size_size(self, result);
			break;

		case DW_TAG_restrict_type:
		case DW_TAG_atomic_type:
		case DW_TAG_const_type:
		case DW_TAG_volatile_type:
		case DW_TAG_typedef:
			if (result->t_type)
				load_pointed_to_size(self, result);
			break;

		default: break;
		}
	}
	return true;
err:
	return false;
}

PRIVATE ATTR_NOINLINE TEXTSECTION NONNULL((1, 2)) bool
NOTHROW_NCX(CC ao_loadattr_member)(di_debuginfo_cu_parser_t *__restrict self,
                                   di_debuginfo_member_t *__restrict result,
                                   byte_t *__restrict abstract_origin) {
	di_debuginfo_cu_parser_t pp;
	memcpy(&pp, self, sizeof(pp));
	pp.dup_cu_info_pos = abstract_origin;
	return (likely(libdi_debuginfo_cu_parser_next(&pp))) &&
	       (likely(libdi_debuginfo_cu_parser_loadattr_member(&pp, result)));
}

INTERN TEXTSECTION NONNULL((1, 2)) bool
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_loadattr_member)(di_debuginfo_cu_parser_t *__restrict self,
                                                          di_debuginfo_member_t *__restrict result) {
	di_debuginfo_component_attrib_t attr;
	result->m_type        = NULL;
	result->m_name        = NULL;
	result->m_decl_file   = 0;
	result->m_decl_line   = 0;
	result->m_decl_column = 0;
	result->m_offset      = (uintptr_t)-1;
	result->m_bit_offset  = 0;
	result->m_bit_size    = 0;
	DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, self) {
		switch (attr.dica_name) {

		case DW_AT_abstract_origin: {
			byte_t *abstract_origin;
			if unlikely(!libdi_debuginfo_cu_parser_getref(self, attr.dica_form,
			                                              &abstract_origin))
				ERROR(err);
			return ao_loadattr_member(self, result, abstract_origin);
		}	break;

		case DW_AT_name:
			if unlikely(!libdi_debuginfo_cu_parser_getstring(self, attr.dica_form,
			                                                 &result->m_name))
				ERROR(err);
			break;

		case DW_AT_decl_file:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->m_decl_file))
				ERROR(err);
			break;

		case DW_AT_decl_line:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->m_decl_line))
				ERROR(err);
			break;

		case DW_AT_decl_column:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->m_decl_column))
				ERROR(err);
			break;

		case DW_AT_type:
			if unlikely(!libdi_debuginfo_cu_parser_getref(self, attr.dica_form,
			                                              &result->m_type))
				ERROR(err);
			break;

		case DW_AT_data_member_location:
			/* TODO: `DW_AT_data_member_location' can also be an expression! */
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->m_offset))
				ERROR(err);
			break;

		case DW_AT_bit_offset:
		case DW_AT_data_bit_offset:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->m_bit_offset))
				ERROR(err);
			break;

		case DW_AT_bit_size:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->m_bit_size))
				ERROR(err);
			break;

		default: break;
		}
	}
	return true;
err:
	return false;
}

PRIVATE ATTR_NOINLINE TEXTSECTION NONNULL((1, 2, 3)) bool
NOTHROW_NCX(CC ao_loadattr_variable)(di_debuginfo_cu_parser_t *__restrict self,
                                     di_debuginfo_variable_t *__restrict result,
                                     byte_t *__restrict abstract_origin) {
	di_debuginfo_cu_parser_t pp;
	memcpy(&pp, self, sizeof(pp));
	pp.dup_cu_info_pos = abstract_origin;
	return (likely(libdi_debuginfo_cu_parser_next(&pp))) &&
	       (likely(libdi_debuginfo_cu_parser_loadattr_variable(&pp, result)));
}

INTERN TEXTSECTION NONNULL((1, 2)) bool
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_loadattr_variable)(di_debuginfo_cu_parser_t *__restrict self,
                                                            di_debuginfo_variable_t *__restrict result) {
	di_debuginfo_component_attrib_t attr;
	result->v_location.l_expr  = NULL;
	result->v_location.l_llist = NULL;
	result->v_type             = NULL;
	result->v_name             = NULL;
	result->v_rawname          = NULL;
	result->v_decl_file        = 0;
	result->v_decl_line        = 0;
	result->v_decl_column      = 0;
	DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, self) {
		switch (attr.dica_name) {

		case DW_AT_abstract_origin: {
			byte_t *abstract_origin;
			if unlikely(!libdi_debuginfo_cu_parser_getref(self, attr.dica_form,
			                                              &abstract_origin))
				ERROR(err);
			return ao_loadattr_variable(self, result, abstract_origin);
		}	break;

		case DW_AT_location:
			if unlikely(!libdi_debuginfo_cu_parser_getexpr(self, attr.dica_form,
			                                               &result->v_location))
				ERROR(err);
			break;

		case DW_AT_name:
			if unlikely(!libdi_debuginfo_cu_parser_getstring(self, attr.dica_form,
			                                                 &result->v_name))
				ERROR(err);
			break;

		case DW_AT_linkage_name:
			if unlikely(!libdi_debuginfo_cu_parser_getstring(self, attr.dica_form,
			                                                 &result->v_rawname))
				ERROR(err);
			break;

		case DW_AT_decl_file:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->v_decl_file))
				ERROR(err);
			break;

		case DW_AT_decl_line:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->v_decl_line))
				ERROR(err);
			break;

		case DW_AT_decl_column:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &result->v_decl_column))
				ERROR(err);
			break;

		case DW_AT_type:
			if unlikely(!libdi_debuginfo_cu_parser_getref(self, attr.dica_form,
			                                              &result->v_type))
				ERROR(err);
			break;

		default: break;
		}
	}
	return true;
err:
	return false;
}


struct varname_prefix;
struct varname_prefix {
	struct varname_prefix *vp_next; /* [0..1] Next prefix */
	char const            *vp_text; /* [1..1] Prefix text */
	unsigned int           vp_fmt;  /* Format option name. */
};

LOCAL bool CC need_space(char a, char b) {
	if (a == b && (a == '*' || a == '&'))
		return true; /* &[ ]&  (prevent token concat) */
	if (isalnum(a))
		return true; /* Always put space following a string. */
	return false;
}

#define DO(x)                         \
	do {                              \
		if unlikely((temp = (x)) < 0) \
			goto err;                 \
		result += temp;               \
	}	__WHILE0
#define FORMAT(option)                                                 \
	do {                                                               \
		if (format_printer) {                                          \
			if unlikely((temp = (*format_printer)(format_arg, printer, \
			                                      arg, option)) < 0)   \
				goto err;                                              \
			result += temp;                                            \
		}                                                              \
	}	__WHILE0

PRIVATE TEXTSECTION NONNULL((1)) ssize_t CC
libdi_debuginfo_print_typename_and_varname(pformatprinter printer, void *arg,
                                           char const *type_name,
                                           struct varname_prefix *vn_prefix,
                                           char const *varname,
                                           debuginfo_print_format_t format_printer,
                                           void *format_arg) {
	ssize_t result = 0, temp;
	size_t namelen;
	if unlikely(!type_name || !*type_name)
		type_name = (char *)unknown_string;
	/* Fallback: type-name + " " + varname */
	namelen = strlen(type_name);
	FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_PREFIX);
	DO((*printer)(arg, type_name, namelen));
	FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_SUFFIX);
	if unlikely(result < 0)
		goto done;
	for (; vn_prefix; vn_prefix = vn_prefix->vp_next) {
		if (need_space(type_name[namelen - 1], vn_prefix->vp_text[0]))
			DO((*printer)(arg, " ", 1));
		type_name = vn_prefix->vp_text;
		namelen   = strlen(type_name);
		FORMAT(vn_prefix->vp_fmt);
		DO((*printer)(arg, type_name, namelen));
		FORMAT(vn_prefix->vp_fmt + 1);
	}
	if (varname && *varname) {
		if (need_space(type_name[namelen - 1], varname[0]))
			DO((*printer)(arg, " ", 1));
		FORMAT(DEBUGINFO_PRINT_FORMAT_VARNAME_PREFIX);
		DO((*printer)(arg, varname, strlen(varname)));
		FORMAT(DEBUGINFO_PRINT_FORMAT_VARNAME_SUFFIX);
	}
done:
	return result;
err:
	return temp;
}

PRIVATE TEXTSECTION NONNULL((1, 3, 4)) ssize_t CC
libdi_debuginfo_do_print_typename(pformatprinter printer, void *arg,
                                  di_debuginfo_cu_parser_t const *__restrict parser,
                                  di_debuginfo_type_t const *__restrict type,
                                  struct varname_prefix *vn_prefix,
                                  char const *varname,
                                  debuginfo_print_format_t format_printer,
                                  void *format_arg) {
	ssize_t result, temp;
	di_debuginfo_cu_parser_t pp;
	di_debuginfo_type_t inner_type;
	struct varname_prefix new_prefix;
	char *type_name = type->t_name;
	if unlikely(!type_name)
		type_name = type->t_rawname;
	switch (parser->dup_comp.dic_tag) {

	case DW_TAG_typedef:
		if (type_name)
			goto print_generic;
		for (;;) {
			memcpy(&pp, parser, sizeof(pp));
			if unlikely(!type->t_type)
				goto print_generic;
			pp.dup_cu_info_pos = type->t_type;
			if unlikely(!libdi_debuginfo_cu_parser_next(&pp))
				goto print_generic;
			if unlikely(!libdi_debuginfo_cu_parser_loadattr_type(&pp, &inner_type))
				goto print_generic;
			if (pp.dup_comp.dic_tag != DW_TAG_typedef)
				break;
			type = &inner_type;
		}
		result = libdi_debuginfo_print_typename(printer,
		                                        arg,
		                                        &pp,
		                                        &inner_type,
		                                        varname,
		                                        format_printer,
		                                        format_arg);
		break;

	case DW_TAG_restrict_type:
		new_prefix.vp_text = "restrict";
		goto do_varname_prefix2;

	case DW_TAG_atomic_type:
		new_prefix.vp_text = "atomic";
		goto do_varname_prefix2;

	case DW_TAG_const_type:
		new_prefix.vp_text = "const";
		goto do_varname_prefix2;

	case DW_TAG_volatile_type:
		new_prefix.vp_text = "volatile";
		goto do_varname_prefix2;

	case DW_TAG_pointer_type:
		new_prefix.vp_text = "*";
		goto do_varname_prefix;

	case DW_TAG_reference_type:
		new_prefix.vp_text = "&";
		goto do_varname_prefix;

	case DW_TAG_rvalue_reference_type:
		new_prefix.vp_text = "&&";
do_varname_prefix:
		new_prefix.vp_fmt = DEBUGINFO_PRINT_FORMAT_POINTER_PREFIX;
		goto do_varname_prefix3;
do_varname_prefix2:
		new_prefix.vp_fmt = DEBUGINFO_PRINT_FORMAT_MODIFIER_PREFIX;
do_varname_prefix3:
		memcpy(&pp, parser, sizeof(pp));
		if unlikely(!type->t_type) {
			if (!type_name)
				type_name = (char *)"void";
			goto print_generic_vn_prefix;
		}
		pp.dup_cu_info_pos = type->t_type;
		if unlikely(!libdi_debuginfo_cu_parser_next(&pp))
			goto print_generic_vn_prefix;
		if unlikely(!libdi_debuginfo_cu_parser_loadattr_type(&pp, &inner_type))
			goto print_generic_vn_prefix;
		new_prefix.vp_next = vn_prefix;
		result = libdi_debuginfo_do_print_typename(printer,
		                                           arg,
		                                           &pp,
		                                           &inner_type,
		                                           &new_prefix,
		                                           varname,
		                                           format_printer,
		                                           format_arg);
		break;

	case DW_TAG_class_type:
	case DW_TAG_interface_type:
		new_prefix.vp_text = "class";
		goto do_prefix_type;
	case DW_TAG_union_type:
		new_prefix.vp_text = "union";
		goto do_prefix_type;
	case DW_TAG_enumeration_type:
		new_prefix.vp_text = "enum";
		goto do_prefix_type;
	case DW_TAG_structure_type:
		new_prefix.vp_text = "struct";
do_prefix_type:
		result = 0;
		FORMAT(DEBUGINFO_PRINT_FORMAT_KEYWORD_PREFIX);
		DO((*printer)(arg, new_prefix.vp_text, strlen(new_prefix.vp_text)));
		FORMAT(DEBUGINFO_PRINT_FORMAT_KEYWORD_SUFFIX);
		DO((*printer)(arg, " ", 1));
		DO(libdi_debuginfo_print_typename_and_varname(printer, arg, type_name, vn_prefix, varname, format_printer, format_arg));
		break;

	case DW_TAG_subroutine_type:
		memcpy(&pp, parser, sizeof(pp));
		/* Load the function return type. */
		if (vn_prefix) {
			new_prefix.vp_next = vn_prefix;
			new_prefix.vp_text = "(";
			new_prefix.vp_fmt  = DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX;
			vn_prefix          = &new_prefix;
		}
		if (!type->t_type) {
			result = libdi_debuginfo_print_typename_and_varname(printer,
			                                                    arg,
			                                                    "void",
			                                                    vn_prefix,
			                                                    varname,
			                                                    format_printer,
			                                                    format_arg);
		} else if ((pp.dup_cu_info_pos = type->t_type,
		            libdi_debuginfo_cu_parser_next(&pp)) &&
		           (libdi_debuginfo_cu_parser_loadattr_type(&pp, &inner_type))) {
			result = libdi_debuginfo_do_print_typename(printer,
			                                           arg,
			                                           &pp,
			                                           &inner_type,
			                                           vn_prefix,
			                                           varname,
			                                           format_printer,
			                                           format_arg);
		} else {
			result = libdi_debuginfo_print_typename_and_varname(printer,
			                                                    arg,
			                                                    NULL,
			                                                    vn_prefix,
			                                                    varname,
			                                                    format_printer,
			                                                    format_arg);
		}
		if unlikely(result < 0)
			goto done;
		FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX);
		if (vn_prefix == &new_prefix) {
			DO((*printer)(arg, ")(", 2));
		} else {
			DO((*printer)(arg, "(", 1));
		}
		FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX);
		/* Load function argument types. */
		/* NOTE: It doesn't seem like any information regarding calling conventions... */
		{
			bool is_first = true;
			memcpy(&pp, parser, sizeof(pp));
			if (libdi_debuginfo_cu_parser_nextchild(&pp)) {
				size_t depth = pp.dup_child_depth;
				do {
					if (pp.dup_child_depth == depth &&
					    (pp.dup_comp.dic_tag == DW_TAG_formal_parameter ||
					     pp.dup_comp.dic_tag == DW_TAG_unspecified_parameters)) {
						if (pp.dup_comp.dic_tag == DW_TAG_unspecified_parameters) {
							if (!is_first) {
								FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_PREFIX);
								DO((*printer)(arg, ",", 1));
								FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_SUFFIX);
							}
							is_first = false;
							FORMAT(DEBUGINFO_PRINT_FORMAT_DOTS_PREFIX);
							DO((*printer)(arg, "...", 3));
							FORMAT(DEBUGINFO_PRINT_FORMAT_DOTS_SUFFIX);
						} else {
							byte_t *parameter_type_pointer = NULL;
							char *parameter_name           = NULL;
							di_debuginfo_component_attrib_t attr;
							di_debuginfo_cu_parser_t parameter_pp;
							DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &pp) {
								switch (attr.dica_name) {

								case DW_AT_type:
									libdi_debuginfo_cu_parser_getref(&pp, attr.dica_form, &parameter_type_pointer);
									break;

								case DW_AT_name:
									libdi_debuginfo_cu_parser_getstring(&pp, attr.dica_form, &parameter_name);
									break;

								default: break;
								}
							}
							if (!is_first) {
								FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_PREFIX);
								DO((*printer)(arg, ", ", parameter_name ? 2 : 1));
								FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_SUFFIX);
							}
							is_first = false;
							/* Print this parameter. */
							if (parameter_type_pointer &&
							    (memcpy(&parameter_pp, parser, sizeof(parameter_pp)),
							     parameter_pp.dup_cu_info_pos = parameter_type_pointer,
							     libdi_debuginfo_cu_parser_next(&parameter_pp)) &&
							    libdi_debuginfo_cu_parser_loadattr_type(&parameter_pp, &inner_type)) {
								temp = libdi_debuginfo_do_print_typename(printer,
								                                         arg,
								                                         &parameter_pp,
								                                         &inner_type,
								                                         NULL,
								                                         parameter_name,
								                                         format_printer,
								                                         format_arg);
							} else {
								temp = libdi_debuginfo_print_typename_and_varname(printer,
								                                                  arg,
								                                                  NULL,
								                                                  NULL,
								                                                  parameter_name,
								                                                  format_printer,
								                                                  format_arg);
							}
							if unlikely(temp < 0)
								goto err;
							result += temp;
						}
					} else {
						libdi_debuginfo_cu_parser_skipattr(&pp);
					}
				} while (libdi_debuginfo_cu_parser_next(&pp) &&
				         pp.dup_child_depth >= depth);
			}
			if (is_first) {
				FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_PREFIX);
				DO((*printer)(arg, "void", 4));
				FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_SUFFIX);
			}
		}
		FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX);
		DO((*printer)(arg, ")", 1));
		FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX);
		break;

	case DW_TAG_array_type: {
		uintptr_t elem_count;
		memcpy(&pp, parser, sizeof(pp));
		elem_count = 0;
		if (libdi_debuginfo_cu_parser_nextchild(&pp)) {
			size_t depth = pp.dup_child_depth;
			do {
				if (pp.dup_child_depth == depth &&
				    pp.dup_comp.dic_tag == DW_TAG_subrange_type) {
					di_debuginfo_component_attrib_t attr;
					DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &pp) {
						if (attr.dica_name == DW_AT_upper_bound) {
							if (libdi_debuginfo_cu_parser_getconst(&pp, attr.dica_form, &elem_count))
								++elem_count;
							goto got_elem_count;
						}
					}
				} else {
					libdi_debuginfo_cu_parser_skipattr(&pp);
				}
			} while (libdi_debuginfo_cu_parser_next(&pp) &&
			         pp.dup_child_depth >= depth);
		}
got_elem_count:
		result = 0;
		if (vn_prefix) {
			new_prefix.vp_next = vn_prefix;
			new_prefix.vp_text = "(";
			new_prefix.vp_fmt  = DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX;
			vn_prefix          = &new_prefix;
		}
		if (type->t_type &&
		    (pp.dup_cu_info_pos = type->t_type,
		     libdi_debuginfo_cu_parser_next(&pp)) &&
		    libdi_debuginfo_cu_parser_loadattr_type(&pp, &inner_type)) {
			temp = libdi_debuginfo_do_print_typename(printer,
			                                         arg,
			                                         &pp,
			                                         &inner_type,
			                                         vn_prefix,
			                                         varname,
			                                         format_printer,
			                                         format_arg);
		} else {
			temp = libdi_debuginfo_print_typename_and_varname(printer,
			                                                  arg,
			                                                  NULL,
			                                                  vn_prefix,
			                                                  varname,
			                                                  format_printer,
			                                                  format_arg);
		}
		if unlikely(temp < 0)
			goto err;
		result += temp;
		if (vn_prefix == &new_prefix) {
			FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX);
			DO((*printer)(arg, ")", 1));
			FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX);
		}
		FORMAT(DEBUGINFO_PRINT_FORMAT_BRACKET_PREFIX);
		DO((*printer)(arg, "[", 1));
		FORMAT(DEBUGINFO_PRINT_FORMAT_BRACKET_SUFFIX);
		FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
		DO(format_printf(printer, arg, "%Iu", elem_count));
		FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX);
		FORMAT(DEBUGINFO_PRINT_FORMAT_BRACKET_PREFIX);
		DO((*printer)(arg, "]", 1));
		FORMAT(DEBUGINFO_PRINT_FORMAT_BRACKET_SUFFIX);
	}	break;

print_generic_vn_prefix:
		new_prefix.vp_next = vn_prefix;
		vn_prefix          = &new_prefix;
		ATTR_FALLTHROUGH
	default:
print_generic:
		result = libdi_debuginfo_print_typename_and_varname(printer,
		                                                    arg,
		                                                    type_name,
		                                                    vn_prefix,
		                                                    varname,
		                                                    format_printer,
		                                                    format_arg);
		break;
	}
done:
	return result;
err:
	return temp;
}

INTERN TEXTSECTION NONNULL((1, 3, 4)) ssize_t CC
libdi_debuginfo_print_typename(pformatprinter printer, void *arg,
                               di_debuginfo_cu_parser_t const *__restrict parser,
                               di_debuginfo_type_t const *__restrict type,
                               char const *varname,
                               debuginfo_print_format_t format_printer,
                               void *format_arg) {
	return libdi_debuginfo_do_print_typename(printer,
	                                         arg,
	                                         parser,
	                                         type,
	                                         NULL,
	                                         varname,
	                                         format_printer,
	                                         format_arg);
}

PRIVATE TEXTSECTION NONNULL((1, 3)) ssize_t CC
libdi_debuginfo_do_print_unknown_data(pformatprinter printer, void *arg,
                                      void const *__restrict data, size_t datasize) {
	size_t i;
	ssize_t temp, result;
	result = (*printer)(arg, "<{ ", 3);
	if unlikely(result < 0)
		goto done;
#if __SIZEOF_POINTER__ >= 8
	if ((datasize & 7) == 0) {
		for (i = 0; i < (datasize >> 3); ++i) {
			uint64_t val = UNALIGNED_GET64((uint64_t *)data + i);
			if (i) {
				temp = (*printer)(arg, ", ", 2);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
			temp = format_printf(printer, arg, "%#.16I64x", val);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
	} else
#endif /* __SIZEOF_POINTER__ >= 8 */
	if ((datasize & 3) == 0) {
		for (i = 0; i < (datasize >> 2); ++i) {
			uint32_t val = UNALIGNED_GET32((uint32_t *)data + i);
			if (i) {
				temp = (*printer)(arg, ", ", 2);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
			temp = format_printf(printer, arg, "%#.8I32x", val);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
	} else if ((datasize & 1) == 0) {
		for (i = 0; i < (datasize >> 1); ++i) {
			uint16_t val = UNALIGNED_GET16((uint16_t *)data + i);
			if (i) {
				temp = (*printer)(arg, ", ", 2);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
			temp = format_printf(printer, arg, "%#.4I16x", val);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
	} else {
		for (i = 0; i < datasize; ++i) {
			uint8_t val = *((uint8_t *)data + i);
			if (i) {
				temp = (*printer)(arg, ", ", 2);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
			temp = format_printf(printer, arg, "%#.2I8x", val);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
	}
	temp = datasize
	       ? (*printer)(arg, " }>", 3)
	       : (*printer)(arg, "}>", 2);
	if unlikely(temp < 0)
		goto err;
	result += temp;
done:
	return result;
err:
	return temp;
}

PRIVATE TEXTSECTION NONNULL((1)) ssize_t CC
print_character(pformatprinter printer, void *arg, uint64_t value) {
	ssize_t result;
	if (value <= UINT32_C(0xffffffff) && unicode_isprint((char32_t)value)) {
		char buf[UNICODE_32TO8_MAXBUF(1)];
		result = (*printer)(arg, buf, (size_t)(unicode_writeutf8(buf, (char32_t)value) - buf));
	} else {
		switch (value) {
			char ctrl_buf[2];

		case '\a':
			ctrl_buf[1] = 'a';
			goto do_ctrl;

		case '\b':
			ctrl_buf[1] = 'b';
			goto do_ctrl;

		case '\f':
			ctrl_buf[1] = 'f';
			goto do_ctrl;

		case '\n':
			ctrl_buf[1] = 'n';
			goto do_ctrl;

		case '\r':
			ctrl_buf[1] = 'r';
			goto do_ctrl;

		case '\t':
			ctrl_buf[1] = 't';
			goto do_ctrl;

		case '\v':
			ctrl_buf[1] = 'v';
			goto do_ctrl;

		case '\033':
			ctrl_buf[1] = 'e';
			goto do_ctrl;

		case '\\':
			ctrl_buf[1] = '\\';
			goto do_ctrl;

		case '\'':
			ctrl_buf[1] = '\'';
			goto do_ctrl;

		case '\"':
			ctrl_buf[1] = '\"';
do_ctrl:
			ctrl_buf[0] = '\\';
			result = (*printer)(arg, ctrl_buf, 2);
			break;

		default:
			if (value <= UINT8_C(0x7)) {
				result = format_printf(printer, arg, "\\%I8x", (uint8_t)value);
			} else if (value <= UINT8_C(0xff)) {
				result = format_printf(printer, arg, "\\x%I8x", (uint8_t)value);
			} else if (value <= UINT16_C(0xffff)) {
				result = format_printf(printer, arg, "\\u%.4I16x", (uint16_t)value);
			} else if (value <= UINT32_C(0xffffffff)) {
				result = format_printf(printer, arg, "\\U%.8I32x", (uint32_t)value);
			} else {
				result = format_printf(printer, arg, "\\x%I64x", (uint64_t)value);
			}
			break;
		}
	}
	return result;
}

PRIVATE TEXTSECTION NONNULL((1, 3, 4, 5)) ssize_t CC
libdi_debuginfo_do_print_value(pformatprinter printer, void *arg,
                               di_debuginfo_cu_parser_t const *__restrict parser,
                               di_debuginfo_type_t const *__restrict type,
                               void const *__restrict data, size_t datasize,
                               uintptr_t newline_indentation,
                               debuginfo_print_format_t format_printer,
                               void *format_arg, unsigned int flags) {
	ssize_t result, temp;
	di_debuginfo_cu_parser_t pp;
	di_debuginfo_type_t inner_type;
	switch (parser->dup_comp.dic_tag) {

	case DW_TAG_base_type:
		if (type->t_sizeof &&
		    datasize > type->t_sizeof)
			datasize = type->t_sizeof;
		switch (type->t_encoding) {

		case DW_ATE_address: {
			uintptr_t addr;
generic_print_address:
#if __SIZEOF_POINTER__ >= 8
			if (datasize >= 8)
				addr = UNALIGNED_GET64((uint64_t *)data);
			else
#endif /* __SIZEOF_POINTER__ >= 8 */
			if (datasize >= 4)
				addr = UNALIGNED_GET32((uint32_t *)data);
			else if (datasize >= 2)
				addr = UNALIGNED_GET16((uint16_t *)data);
			else if (datasize >= 1)
				addr = *(uint8_t *)data;
			else {
				addr = 0;
			}
			result = 0;
			FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
			DO(format_printf(printer, arg, "%#p", addr));
			FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX);
		}	break;

		case DW_ATE_boolean: {
			uint64_t value;
			if (datasize >= 8)
				value = UNALIGNED_GET64((uint64_t *)data);
			else if (datasize >= 4)
				value = UNALIGNED_GET32((uint32_t *)data);
			else if (datasize >= 2)
				value = UNALIGNED_GET16((uint16_t *)data);
			else if (datasize >= 1)
				value = *(uint8_t *)data;
			else {
				value = 0;
			}
			result = 0;
			if (value == 0) {
				FORMAT(DEBUGINFO_PRINT_FORMAT_BOOL_PREFIX);
				DO((*printer)(arg, "false", 5));
				FORMAT(DEBUGINFO_PRINT_FORMAT_BOOL_SUFFIX);
			} else if (value == 1) {
				FORMAT(DEBUGINFO_PRINT_FORMAT_BOOL_PREFIX);
				DO((*printer)(arg, "true", 4));
				FORMAT(DEBUGINFO_PRINT_FORMAT_BOOL_SUFFIX);
			} else {
				FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX);
				DO((*printer)(arg, "(", 1));
				FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX);
				FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_PREFIX);
				DO((*printer)(arg, "bool", 4));
				FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_SUFFIX);
				FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX);
				DO((*printer)(arg, ")", 1));
				FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX);
				FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
				DO(format_printf(printer, arg, "%I64u", value));
				FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX);
			}
		}	break;

		case DW_ATE_float:
			result = 0;
			FORMAT(DEBUGINFO_PRINT_FORMAT_FLOAT_PREFIX);
			if (datasize >= sizeof(__LONGDOUBLE)) {
				union {
					__LONGDOUBLE flt;
					byte_t bytes[sizeof(__LONGDOUBLE)];
				} value;
				memcpy(value.bytes, data, sizeof(__LONGDOUBLE));
				temp = format_printf(printer, arg, "%Lf", value.flt);
			} else if (datasize >= sizeof(double)) {
				union {
					double flt;
					byte_t bytes[sizeof(double)];
				} value;
				memcpy(value.bytes, data, sizeof(double));
				temp = format_printf(printer, arg, "%f", value.flt);
			} else if (datasize >= sizeof(float)) {
				union {
					float flt;
					byte_t bytes[sizeof(float)];
				} value;
				memcpy(value.bytes, data, sizeof(float));
				temp = format_printf(printer, arg, "%f", (double)value.flt);
			} else {
				temp = (*printer)(arg, "0.0", 3);
			}
			if unlikely(temp < 0)
				goto err;
			result += temp;
			FORMAT(DEBUGINFO_PRINT_FORMAT_FLOAT_SUFFIX);
			break;

		case DW_ATE_signed: {
			int64_t value;
			if (datasize >= 8) {
				value = (int64_t)UNALIGNED_GET64((uint64_t *)data);
			} else if (datasize >= 4) {
				value = (int64_t)(int32_t)UNALIGNED_GET32((uint32_t *)data);
			} else if (datasize >= 2) {
				value = (int64_t)(int16_t)UNALIGNED_GET16((uint16_t *)data);
			} else if (datasize >= 1) {
				value = (int64_t) * (int8_t *)data;
			} else {
				value = 0;
			}
			result = 0;
			FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
			DO(format_printf(printer, arg, "%I64d", value));
			FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX);
		}	break;

		case DW_ATE_unsigned: {
			uint64_t value;
			if (datasize >= 8) {
				value = UNALIGNED_GET64((uint64_t *)data);
			} else if (datasize >= 4) {
				value = (uint64_t)UNALIGNED_GET32((uint32_t *)data);
			} else if (datasize >= 2) {
				value = (uint64_t)UNALIGNED_GET16((uint16_t *)data);
			} else if (datasize >= 1) {
				value = (uint64_t) * (uint8_t *)data;
			} else {
				value = 0;
			}
			result = 0;
			FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
			DO(format_printf(printer, arg, "%I64u", value));
			FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX);
		}	break;

		case DW_ATE_signed_char:
		case DW_ATE_unsigned_char:
		case DW_ATE_UTF: {
			uint64_t value;
			if (datasize >= 8) {
				value = (uint64_t)UNALIGNED_GET64((uint64_t *)data);
			} else if (datasize >= 4) {
				value = (uint64_t)UNALIGNED_GET32((uint32_t *)data);
				if (type->t_encoding == DW_ATE_signed_char)
					value = (uint64_t)(int64_t)(int32_t)(uint32_t)value;
			} else if (datasize >= 2) {
				value = (uint64_t)UNALIGNED_GET16((uint16_t *)data);
				if (type->t_encoding == DW_ATE_signed_char)
					value = (uint64_t)(int64_t)(int16_t)(uint16_t)value;
			} else if (datasize >= 1) {
				value = (uint64_t) * (uint8_t *)data;
				if (type->t_encoding == DW_ATE_signed_char)
					value = (uint64_t)(int64_t)(int8_t)(uint8_t)value;
			} else {
				value = 0;
			}
			result = 0;
			if (!value) {
				FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
				DO((*printer)(arg, "0", 1));
				FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX);
			} else {
				FORMAT(DEBUGINFO_PRINT_FORMAT_CHARACTER_PREFIX);
				DO((*printer)(arg, "\'", 1));
				DO(print_character(printer, arg, value));
				DO((*printer)(arg, "\'", 1));
				FORMAT(DEBUGINFO_PRINT_FORMAT_CHARACTER_SUFFIX);
			}
		}	break;

		//case DW_ATE_complex_float: break;
		//case DW_ATE_imaginary_float: break;
		//case DW_ATE_packed_decimal: break;
		//case DW_ATE_numeric_string: break;
		//case DW_ATE_edited: break;
		//case DW_ATE_signed_fixed: break;
		//case DW_ATE_unsigned_fixed: break;
		//case DW_ATE_decimal_float: break;

		default: goto print_generic;
		}
		break;

	case DW_TAG_pointer_type:
	case DW_TAG_reference_type:
	case DW_TAG_rvalue_reference_type:
		if (type->t_sizeof &&
		    datasize > type->t_sizeof)
			datasize = type->t_sizeof;
		goto generic_print_address;


	case DW_TAG_array_type: {
		uintptr_t i, elem_count;
		memcpy(&pp, parser, sizeof(pp));
		elem_count = 0;
		if (libdi_debuginfo_cu_parser_nextchild(&pp)) {
			size_t depth = pp.dup_child_depth;
			do {
				if (pp.dup_child_depth == depth &&
				    pp.dup_comp.dic_tag == DW_TAG_subrange_type) {
					di_debuginfo_component_attrib_t attr;
					DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &pp) {
						if (attr.dica_name == DW_AT_upper_bound) {
							if (libdi_debuginfo_cu_parser_getconst(&pp, attr.dica_form, &elem_count))
								++elem_count;
							goto got_elem_count;
						}
					}
				} else {
					libdi_debuginfo_cu_parser_skipattr(&pp);
				}
			} while (libdi_debuginfo_cu_parser_next(&pp) &&
			         pp.dup_child_depth >= depth);
		}
got_elem_count:
		if unlikely(!elem_count) {
			if unlikely(datasize)
				goto print_generic;
			result = 0;
			FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_PREFIX);
			DO((*printer)(arg, "{ }", 3));
			FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_SUFFIX);
		} else {
			if (type->t_type &&
			    (pp.dup_cu_info_pos = type->t_type,
			     libdi_debuginfo_cu_parser_next(&pp)) &&
			    libdi_debuginfo_cu_parser_loadattr_type(&pp, &inner_type)) {
				while ((pp.dup_comp.dic_tag == DW_TAG_typedef ||
				        pp.dup_comp.dic_tag == DW_TAG_const_type ||
				        pp.dup_comp.dic_tag == DW_TAG_volatile_type ||
				        pp.dup_comp.dic_tag == DW_TAG_restrict_type ||
				        pp.dup_comp.dic_tag == DW_TAG_atomic_type) &&
				       inner_type.t_type) {
					pp.dup_cu_info_pos = inner_type.t_type;
					if (!libdi_debuginfo_cu_parser_next(&pp) ||
					    !libdi_debuginfo_cu_parser_loadattr_type(&pp, &inner_type))
						goto print_unknown_inner_array_type;
				}
				if unlikely(!inner_type.t_sizeof)
					inner_type.t_sizeof = datasize / elem_count;
				if (pp.dup_comp.dic_tag == DW_TAG_base_type &&
				    (inner_type.t_encoding == DW_ATE_signed_char ||
				     inner_type.t_encoding == DW_ATE_unsigned_char ||
				     inner_type.t_encoding == DW_ATE_UTF)) {
					/* Try to print an encoded string.
					 * NOTE: To be a valid string, the last character must be ZERO(0)! */
					byte_t *last_char;
					if (inner_type.t_sizeof != 1 &&
					    inner_type.t_sizeof != 2 &&
					    inner_type.t_sizeof != 4)
						goto print_as_array;
					last_char = (byte_t *)data + (elem_count - 1) * inner_type.t_sizeof;
					for (i = 0; i < inner_type.t_sizeof; ++i) {
						if (last_char[i] != 0)
							goto print_as_array;
					}
					/* Yes! -> Print this one as a string. */
					result = 0;
					FORMAT(DEBUGINFO_PRINT_FORMAT_STRING_PREFIX);
					DO(inner_type.t_sizeof == 1
					   ? (*printer)(arg, "\"", 1)
					   : inner_type.t_sizeof == 2
					     ? (*printer)(arg, "u\"", 2)
					     : (*printer)(arg, "U\"", 2));
					--elem_count;
					for (i = 0; i < elem_count; ++i) {
						uint32_t ch;
						if (inner_type.t_sizeof == 1)
							ch = *((uint8_t *)data + i);
						else if (inner_type.t_sizeof == 2)
							ch = UNALIGNED_GET16((uint16_t *)data + i);
						else {
							ch = UNALIGNED_GET32((uint32_t *)data + i);
						}
						DO(print_character(printer, arg, ch));
					}
					DO((*printer)(arg, "\"", 1));
					FORMAT(DEBUGINFO_PRINT_FORMAT_STRING_SUFFIX);
					break;
				}
print_as_array:
				result = 0;
				FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_PREFIX);
				DO((*printer)(arg, "{ ", 2));
				FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_SUFFIX);
				for (i = 0; i < elem_count; ++i) {
					uintptr_t offset;
					size_t elemavail;
					offset    = i * inner_type.t_sizeof;
					elemavail = datasize - offset;
					if unlikely(offset >= datasize)
						elemavail = 0;
					if (elemavail > inner_type.t_sizeof)
						elemavail = inner_type.t_sizeof;
					if (i) {
						FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_PREFIX);
						DO((*printer)(arg, ", ", 2));
						FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_SUFFIX);
						result += temp;
					}
					temp = libdi_debuginfo_print_value(printer,
					                                   arg,
					                                   &pp,
					                                   &inner_type,
					                                   NULL,
					                                   (byte_t *)data + offset,
					                                   elemavail,
					                                   newline_indentation,
					                                   format_printer,
					                                   format_arg,
					                                   flags);
					if unlikely(temp < 0)
						goto err;
					result += temp;
				}
			} else {
print_unknown_inner_array_type:
				result = 0;
				FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_PREFIX);
				DO((*printer)(arg, "{ ", 2));
				FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_SUFFIX);
				inner_type.t_sizeof = datasize / elem_count;
				for (i = 0; i < elem_count; ++i) {
					uintptr_t offset;
					offset = i * inner_type.t_sizeof;
					if (i) {
						FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_PREFIX);
						DO((*printer)(arg, ", ", 2));
						FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_SUFFIX);
					}
					FORMAT(DEBUGINFO_PRINT_FORMAT_UNKNOWN_PREFIX);
					DO(libdi_debuginfo_do_print_unknown_data(printer, arg,
					                                         (byte_t *)data + offset,
					                                         inner_type.t_sizeof));
					FORMAT(DEBUGINFO_PRINT_FORMAT_UNKNOWN_SUFFIX);
				}
			}
			FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_PREFIX);
			DO((*printer)(arg, " }", 2));
			FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_SUFFIX);
		}
	}	break;

	case DW_TAG_enumeration_type: {
		uintptr_t value;
		if (type->t_sizeof &&
		    datasize > type->t_sizeof)
			datasize = type->t_sizeof;
		if (datasize >= 8) {
			value = (uintptr_t)UNALIGNED_GET64((uint64_t *)data);
		} else if (datasize >= 4) {
			value = (uintptr_t)UNALIGNED_GET32((uint32_t *)data);
		} else if (datasize >= 2) {
			value = (uintptr_t)UNALIGNED_GET16((uint16_t *)data);
		} else if (datasize >= 1) {
			value = (uintptr_t) * (uint8_t *)data;
		} else {
			value = 0;
		}
		memcpy(&pp, parser, sizeof(pp));
		if (libdi_debuginfo_cu_parser_nextchild(&pp)) {
			size_t depth = pp.dup_child_depth;
			do {
				if (pp.dup_child_depth == depth &&
				    pp.dup_comp.dic_tag == DW_TAG_enumerator) {
					char *enum_name      = NULL;
					uintptr_t enum_value = 0;
					di_debuginfo_component_attrib_t attr;
					DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &pp) {
						if (attr.dica_name == DW_AT_name) {
							libdi_debuginfo_cu_parser_getstring(&pp, attr.dica_form, &enum_name);
						} else if (attr.dica_name == DW_AT_const_value) {
							libdi_debuginfo_cu_parser_getconst(&pp, attr.dica_form, &enum_value);
						}
					}
					if (enum_value == value) {
						if unlikely(!enum_name)
							goto print_generic_enum;
						result = (*printer)(arg, enum_name, strlen(enum_name));
						goto done;
					}
				}
			} while (libdi_debuginfo_cu_parser_next(&pp) &&
			         pp.dup_child_depth >= depth);
		}
print_generic_enum:
		result = 0;
		if (!(flags & DEBUGINFO_PRINT_VALUE_FCASTALL)) {
			char *type_name = type->t_name;
			if (!type_name)
				type_name = type->t_rawname;
			FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX);
			DO((*printer)(arg, "(", 1));
			FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX);
			FORMAT(DEBUGINFO_PRINT_FORMAT_KEYWORD_PREFIX);
			DO((*printer)(arg, "enum ", type_name ? 5 : 4));
			FORMAT(DEBUGINFO_PRINT_FORMAT_KEYWORD_SUFFIX);
			if (type_name) {
				FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_PREFIX);
				DO((*printer)(arg, type_name, strlen(type_name)));
				FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_SUFFIX);
			}
			FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX);
			DO((*printer)(arg, ")", 1));
			FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX);
		}
		FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
		DO(format_printf(printer, arg, "%I64u", value));
		FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX);
	}	break;

	case DW_TAG_interface_type:
	case DW_TAG_class_type:
	case DW_TAG_union_type:
	case DW_TAG_structure_type:
		memcpy(&pp, parser, sizeof(pp));
		if (libdi_debuginfo_cu_parser_nextchild(&pp)) {
			size_t depth  = pp.dup_child_depth;
			bool is_first = true;
			result        = (*printer)(arg, "{", 1);
			if unlikely(result < 0)
				goto done;
			do {
				if (pp.dup_child_depth == depth &&
				    pp.dup_comp.dic_tag == DW_TAG_member) {
					di_debuginfo_member_t member;
					if (!is_first) {
						FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_PREFIX);
						DO((*printer)(arg, ",", 1));
						FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_SUFFIX);
					}
					is_first = false;
					DO((*printer)(arg, "\n", 1));
					DO(format_repeat(printer, arg, '\t', newline_indentation + 1));
					if unlikely(!libdi_debuginfo_cu_parser_loadattr_member(&pp, &member))
						break;
					if (member.m_offset == (uintptr_t)-1 &&
					    parser->dup_comp.dic_tag == DW_TAG_union_type)
						member.m_offset = 0;
					if (member.m_name) {
						FORMAT(DEBUGINFO_PRINT_FORMAT_FIELD_PREFIX);
						DO(format_printf(printer, arg, ".%s", member.m_name));
						FORMAT(DEBUGINFO_PRINT_FORMAT_FIELD_SUFFIX);
						FORMAT(DEBUGINFO_PRINT_FORMAT_ASSIGN_PREFIX);
						DO((*printer)(arg, " = ", 3));
						FORMAT(DEBUGINFO_PRINT_FORMAT_ASSIGN_SUFFIX);
					}
					if likely(member.m_type) {
						di_debuginfo_cu_parser_t type_pp;
						size_t member_datasize;
						memcpy(&type_pp, &pp, sizeof(type_pp));
						type_pp.dup_cu_info_pos = member.m_type;
						if (!libdi_debuginfo_cu_parser_next(&type_pp))
							goto member_type_is_invalid;
						if (!libdi_debuginfo_cu_parser_loadattr_type(&type_pp, &inner_type))
							goto member_type_is_invalid;
						member_datasize = datasize - member.m_offset;
						if unlikely(member.m_offset >= datasize)
							member_datasize = 0;
						temp = libdi_debuginfo_print_value(printer,
						                                   arg,
						                                   &type_pp,
						                                   &inner_type,
						                                   NULL,
						                                   (byte_t *)data + member.m_offset,
						                                   member_datasize,
						                                   newline_indentation + 1,
						                                   format_printer,
						                                   format_arg,
						                                   flags);
					} else {
member_type_is_invalid:
						temp = format_printf(printer, arg,
						                     "<unknown+%Iu>",
						                     member.m_offset);
					}
					if unlikely(temp < 0)
						goto err;
					result += temp;
				} else {
					libdi_debuginfo_cu_parser_skipattr(&pp);
				}
			} while (libdi_debuginfo_cu_parser_next(&pp) &&
			         pp.dup_child_depth >= depth);
			if (is_first) {
				DO((*printer)(arg, " ", 1));
			} else {
				DO((*printer)(arg, "\n", 1));
				DO(format_repeat(printer, arg, '\t', newline_indentation));
			}
			FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_PREFIX);
			DO((*printer)(arg, "}", 1));
			FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_SUFFIX);
		} else if (!datasize) {
			result = 0;
			FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_PREFIX);
			DO((*printer)(arg, "{ }", 3));
			FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_SUFFIX);
		} else {
			goto print_generic;
		}
		break;

	case DW_TAG_typedef:
	case DW_TAG_const_type:
	case DW_TAG_volatile_type:
	case DW_TAG_restrict_type:
	case DW_TAG_atomic_type:
		for (;;) {
			memcpy(&pp, parser, sizeof(pp));
			if unlikely(!type->t_type)
				goto print_generic;
			pp.dup_cu_info_pos = type->t_type;
			if unlikely(!libdi_debuginfo_cu_parser_next(&pp))
				goto print_generic;
			if unlikely(!libdi_debuginfo_cu_parser_loadattr_type(&pp, &inner_type))
				goto print_generic;
			if (pp.dup_comp.dic_tag != DW_TAG_typedef &&
			    pp.dup_comp.dic_tag != DW_TAG_const_type &&
			    pp.dup_comp.dic_tag != DW_TAG_volatile_type &&
			    pp.dup_comp.dic_tag != DW_TAG_restrict_type &&
			    pp.dup_comp.dic_tag != DW_TAG_atomic_type)
				break;
			type = &inner_type;
		}
		result = libdi_debuginfo_do_print_value(printer,
		                                        arg,
		                                        &pp,
		                                        &inner_type,
		                                        data,
		                                        datasize,
		                                        newline_indentation,
		                                        format_printer,
		                                        format_arg,
		                                        flags);
		break;

	default:
print_generic:
		/* Fallback: Print the individual bytes / words / dwords [/ qwords]. */
		result = 0;
		FORMAT(DEBUGINFO_PRINT_FORMAT_UNKNOWN_PREFIX);
		DO(libdi_debuginfo_do_print_unknown_data(printer,
		                                         arg,
		                                         data,
		                                         type->t_sizeof
		                                         ? MIN(type->t_sizeof, datasize)
		                                         : datasize));
		FORMAT(DEBUGINFO_PRINT_FORMAT_UNKNOWN_SUFFIX);
		break;
	}
done:
	return result;
err:
	return temp;
}


/* Print the C/C++-like representation of a given value, given DWARF debug information
 * about its typing, where `parser' must have been set up to have already loaded the
 * given `type' component for the given data blob:
 * >> di_debuginfo_variable_t var;
 * >> ... // Load `var'
 * >> {
 * >>     di_debuginfo_cu_parser_t pp = parser;
 * >>     di_debuginfo_type_t typ;
 * >>     void *buffer;
 * >>
 * >>     // Load type information for the variable.
 * >>     pp.dup_cu_info_pos = var.v_type;
 * >>     debuginfo_cu_parser_loadattr_type(&pp, &typ);
 * >>
 * >>     // Load the value of this variable.
 * >>     buffer = malloca(typ.t_sizeof);
 * >>     debug_cfa_getvalue(&REGISTERS, &GET_REGISTER, var.v_location, buffer, typ.t_sizeof);
 * >>
 * >>     // Print a representation of the variable, and its data.
 * >>     debuginfo_print_value(PRINTER, ARG, &pp, &type, v.v_name, buffer, typ.t_sizeof);
 * >> }
 * @param: varname: Name of the value (when NULL, print as a cast-like expression;
 *                  otherwise, print as an declaration)
 * @param: flags:   Set of `DEBUGINFO_PRINT_VALUE_F*'
 */
INTERN TEXTSECTION NONNULL((1, 3, 4, 6)) ssize_t CC
libdi_debuginfo_print_value(pformatprinter printer, void *arg,
                            di_debuginfo_cu_parser_t const *__restrict parser,
                            di_debuginfo_type_t const *__restrict type,
                            char const *varname, void const *__restrict data,
                            size_t datasize, size_t newline_indentation,
                            debuginfo_print_format_t format_printer,
                            void *format_arg, unsigned int flags) {
	ssize_t result, temp;
	if (varname) {
		/* Declaration-like */
		result = libdi_debuginfo_print_typename(printer,
		                                        arg,
		                                        parser,
		                                        type,
		                                        varname,
		                                        format_printer,
		                                        format_arg);
		if unlikely(result < 0)
			goto done;
		FORMAT(DEBUGINFO_PRINT_FORMAT_ASSIGN_PREFIX);
		DO((*printer)(arg, " = ", 3));
		FORMAT(DEBUGINFO_PRINT_FORMAT_ASSIGN_SUFFIX);
	} else if (parser->dup_comp.dic_tag == DW_TAG_pointer_type ||
	           parser->dup_comp.dic_tag == DW_TAG_reference_type ||
	           parser->dup_comp.dic_tag == DW_TAG_rvalue_reference_type ||
	           (flags & DEBUGINFO_PRINT_VALUE_FCASTALL)) {
		/* Cast-like */
		result = 0;
		FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX);
		DO((*printer)(arg, "(", 1));
		FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX);
		DO(libdi_debuginfo_print_typename(printer, arg, parser, type, NULL,
		                                  format_printer, format_arg));
		FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX);
		DO((*printer)(arg, ")", 1));
		FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX);
	} else {
		result = 0;
	}
	DO(libdi_debuginfo_do_print_value(printer,
	                                  arg,
	                                  parser,
	                                  type,
	                                  data,
	                                  datasize,
	                                  newline_indentation,
	                                  format_printer,
	                                  format_arg,
	                                  flags));
done:
	return result;
err:
	return temp;
}

PRIVATE TEXTSECTION NONNULL((1, 2, 4, 6)) bool CC
libdi_debuginfo_enum_locals_in_cu(di_enum_locals_sections_t const *__restrict sectinfo,
                                  di_debuginfo_cu_parser_t *__restrict self,
                                  uintptr_t module_relative_pc,
                                  debuginfo_enum_locals_callback_t callback,
                                  void *arg, ssize_t *__restrict presult,
                                  bool assume_correct_cu) {
	bool result = false;
	unsigned int error;
again:
	switch (self->dup_comp.dic_tag) {

	case DW_TAG_compile_unit: {
		di_debuginfo_compile_unit_t cu;
		uintptr_t cu_depth;
		/* Load attributes of the compilation unit. */
		if (!libdi_debuginfo_cu_parser_loadattr_compile_unit(self, &cu))
			goto err;
		if (!assume_correct_cu) {
			error = debuginfo_ranges_contains(&cu.cu_ranges, self,
			                                  cu.cu_ranges.r_startpc,
			                                  module_relative_pc,
			                                  sectinfo->el_debug_ranges_start,
			                                  sectinfo->el_debug_ranges_end);
			if (error == DEBUG_INFO_ERROR_NOFRAME)
				goto next_root;
		}
		cu_depth = self->dup_child_depth;
		if (!libdi_debuginfo_cu_parser_next(self))
			goto done;
again_cu_component:
		while (self->dup_child_depth > cu_depth) {
			/* Scan components of this CU. */
			switch (self->dup_comp.dic_tag) {

			{
				di_debuginfo_subprogram_t sp;
				uintptr_t subprogram_depth;
			case DW_TAG_subprogram:
				if (!libdi_debuginfo_cu_parser_loadattr_subprogram(self, &sp))
					goto err;
				subprogram_depth = self->dup_child_depth;
				/* Check if the given pointer is apart of this sub-program. */
				error = debuginfo_ranges_contains(&sp.sp_ranges, self,
				                                  cu.cu_ranges.r_startpc,
				                                  module_relative_pc,
				                                  sectinfo->el_debug_ranges_start,
				                                  sectinfo->el_debug_ranges_end);
				if (error != DEBUG_INFO_ERROR_SUCCESS) {
					/* Must be apart of a different sub-program. */
					for (;;) {
						if (!libdi_debuginfo_cu_parser_next(self))
							goto done;
						if (self->dup_child_depth <= subprogram_depth)
							goto again_cu_component;
						libdi_debuginfo_cu_parser_skipattr(self);
					}
				}
				result = true;
				for (;;) {
					if (!libdi_debuginfo_cu_parser_next(self))
						goto done_subprogram;
again_subprogram_component:
					if (self->dup_child_depth <= subprogram_depth)
						goto done_subprogram;
					switch (self->dup_comp.dic_tag) {

					{
						di_debuginfo_variable_t var;
						di_debuginfo_type_t vartype;
						di_debuginfo_cu_parser_t type_parser;
						ssize_t temp;
					case DW_TAG_variable:
					case DW_TAG_formal_parameter:
						if (!libdi_debuginfo_cu_parser_loadattr_variable(self, &var))
							goto err;
						memcpy(&type_parser, self, sizeof(type_parser));
						memset(&vartype, 0, sizeof(vartype));
						if (var.v_type) {
							type_parser.dup_cu_info_pos = var.v_type;
							if (libdi_debuginfo_cu_parser_next(&type_parser))
								libdi_debuginfo_cu_parser_loadattr_type(&type_parser, &vartype);
						}
						temp = (*callback)(arg,
						                   &type_parser,
						                   sectinfo,
						                   &cu,
						                   &sp,
						                   &var,
						                   &vartype,
						                   module_relative_pc);
						if unlikely(temp < 0) {
							*presult = temp;
							goto done;
						}
						*presult += temp;
					}	break;

					case DW_TAG_inlined_subroutine:
					case DW_TAG_try_block:
					case DW_TAG_catch_block:
					case DW_TAG_lexical_block: {
						di_debuginfo_lexical_block_t block;
						if (!libdi_debuginfo_cu_parser_loadattr_lexical_block(self, &block))
							goto err;
						error = debuginfo_ranges_contains(&block.lb_ranges, self,
						                                  cu.cu_ranges.r_startpc,
						                                  module_relative_pc,
						                                  sectinfo->el_debug_ranges_start,
						                                  sectinfo->el_debug_ranges_end);
						if (error != DEBUG_INFO_ERROR_SUCCESS) {
							/* Must be apart of a different scope. */
							uintptr_t block_depth;
							block_depth = self->dup_child_depth;
							for (;;) {
								if (!libdi_debuginfo_cu_parser_next(self))
									goto done;
								if (self->dup_child_depth <= block_depth)
									goto again_subprogram_component;
								libdi_debuginfo_cu_parser_skipattr(self);
							}
						}
					}	break;

					default:
						libdi_debuginfo_cu_parser_skipattr(self);
						break;
					}
				}
done_subprogram:
				goto done;
			}	break;

			default:
				libdi_debuginfo_cu_parser_skipattr(self);
/*next_cu_component:*/
				if (!libdi_debuginfo_cu_parser_next(self))
					goto done;
				break;
			}
		}
	}	break;

	default:
/*next_root_skipattr:*/
		libdi_debuginfo_cu_parser_skipattr(self);
next_root:
		if (libdi_debuginfo_cu_parser_next(self))
			goto again;
		break;
	}
done:
	return result;
err:
	return false;
}


/* Enumerate all local variables visible at a given source location
 * @return: >= 0: The sum of all invocations of `*callback'.
 * @return: <  0: The first negative return value of `*callback'. */
INTERN TEXTSECTION NONNULL((1, 3)) ssize_t CC
libdi_debuginfo_enum_locals(di_enum_locals_sections_t const *__restrict sectinfo,
                            uintptr_t module_relative_pc,
                            debuginfo_enum_locals_callback_t callback, void *arg) {
	ssize_t result = 0;
	di_debuginfo_cu_parser_t parser;
	di_debuginfo_cu_abbrev_t abbrev;
	byte_t *debug_info_reader;
	uintptr_t cu_offset;
	/* Try to make use of `.debug_aranges' to quickly locate the CU. */
	if (libdi_debugaranges_locate(sectinfo->el_debug_aranges_start,
	                              sectinfo->el_debug_aranges_end,
	                              &cu_offset,
	                              module_relative_pc) == DEBUG_INFO_ERROR_SUCCESS &&
	    sectinfo->el_debug_info_end > sectinfo->el_debug_info_start &&
	    (size_t)cu_offset < (size_t)(sectinfo->el_debug_info_end - sectinfo->el_debug_info_start)) {
		debug_info_reader = sectinfo->el_debug_info_start + cu_offset;
		if (libdi_debuginfo_cu_parser_loadunit(&debug_info_reader,
		                                       sectinfo->el_debug_info_end,
		                                       di_enum_locals_sections_as_di_debuginfo_cu_parser_sections(sectinfo),
		                                       &parser, &abbrev, NULL) == DEBUG_INFO_ERROR_SUCCESS) {
#if 1
			libdi_debuginfo_enum_locals_in_cu(sectinfo, &parser,
			                                  module_relative_pc,
			                                  callback, arg,
			                                  &result, true);
			libdi_debuginfo_cu_abbrev_fini(&abbrev);
			goto done;
#else
			bool was_ok;
			was_ok = libdi_debuginfo_enum_locals_in_cu(sectinfo, &parser,
			                                           module_relative_pc,
			                                           callback, arg,
			                                           &result, true);
			libdi_debuginfo_cu_abbrev_fini(&abbrev);
			if (was_ok)
				goto done;
#endif
		}
	}
	debug_info_reader = sectinfo->el_debug_info_start;
	while (libdi_debuginfo_cu_parser_loadunit(&debug_info_reader,
	                                          sectinfo->el_debug_info_end,
	                                          di_enum_locals_sections_as_di_debuginfo_cu_parser_sections(sectinfo),
	                                          &parser, &abbrev, NULL) == DEBUG_INFO_ERROR_SUCCESS) {
		bool was_ok;
		was_ok = libdi_debuginfo_enum_locals_in_cu(sectinfo, &parser,
		                                           module_relative_pc,
		                                           callback, arg,
		                                           &result, false);
		libdi_debuginfo_cu_abbrev_fini(&abbrev);
		if (was_ok)
			goto done;
	}
done:
	return result;
}


INTERN_CONST STRINGSECTION char const secname_eh_frame[]    = ".eh_frame";
INTERN_CONST STRINGSECTION char const secname_debug_frame[] = ".debug_frame";
INTERN_CONST STRINGSECTION char const secname_debug_addr[]  = ".debug_addr";
INTERN_CONST STRINGSECTION char const secname_debug_loc[]   = ".debug_loc";
INTDEF STRINGSECTION char const secname_debug_line[];
INTDEF STRINGSECTION char const secname_debug_info[];
INTDEF STRINGSECTION char const secname_debug_abbrev[];
INTDEF STRINGSECTION char const secname_debug_aranges[];
INTDEF STRINGSECTION char const secname_debug_str[];
INTDEF STRINGSECTION char const secname_debug_ranges[];
INTDEF STRINGSECTION char const secname_symtab[];
INTDEF STRINGSECTION char const secname_strtab[];
INTDEF STRINGSECTION char const secname_dynsym[];
INTDEF STRINGSECTION char const secname_dynstr[];

INTERN NONNULL((2, 3)) void
NOTHROW_NCX(CC libdi_debug_sections_lock)(module_t *dl_handle,
                                          di_debug_sections_t *__restrict sections,
                                          di_debug_dl_sections_t *__restrict dl_sections
                                          module_type__param(module_type)) {
	memset(sections, 0, sizeof(*sections));
	memset(dl_sections, 0, sizeof(*dl_sections));
	if unlikely(!dl_handle)
		return;
	/* Special handling for .eh_frame */
	dl_sections->ds_eh_frame = module_locksection_nx(dl_handle, module_type,
	                                                 secname_eh_frame,
	                                                 MODULE_LOCKSECTION_FNODATA);
	if (dl_sections->ds_eh_frame) {
		/* Make sure that user-level data for the section is available.
		 * This is essentially a portable way to assert that SHF_ALLOC was set. */
		if unlikely(module_section_getudata(dl_sections->ds_eh_frame,
		                                    module_type) == (void *)-1) {
			module_section_decref(dl_sections->ds_eh_frame, module_type);
			dl_sections->ds_eh_frame = NULL;
		}
	}
	/* Lock sections into memory */
#define LOCK_SECTION(name) \
	module_locksection_nx(dl_handle, module_type, name, MODULE_LOCKSECTION_FNORMAL)
	dl_sections->ds_debug_frame   = LOCK_SECTION(secname_debug_frame);
	dl_sections->ds_debug_addr    = LOCK_SECTION(secname_debug_addr);
	dl_sections->ds_debug_loc     = LOCK_SECTION(secname_debug_loc);
	dl_sections->ds_debug_abbrev  = LOCK_SECTION(secname_debug_abbrev);
	dl_sections->ds_debug_info    = LOCK_SECTION(secname_debug_info);
	dl_sections->ds_debug_str     = LOCK_SECTION(secname_debug_str);
	dl_sections->ds_debug_aranges = LOCK_SECTION(secname_debug_aranges);
	dl_sections->ds_debug_ranges  = LOCK_SECTION(secname_debug_ranges);
	dl_sections->ds_debug_line    = LOCK_SECTION(secname_debug_line);

	/* Special handling for loading `.symtab'/`.strtab' vs. `.dynsym'/`.dynstr' */
	dl_sections->ds_symtab = LOCK_SECTION(secname_symtab);
	if (dl_sections->ds_symtab) {
		dl_sections->ds_strtab = LOCK_SECTION(secname_strtab);
		if unlikely(!dl_sections->ds_strtab) {
			module_section_decref(dl_sections->ds_symtab,
			                      module_type);
			goto try_load_dynsym;
		}
	} else {
try_load_dynsym:
		dl_sections->ds_strtab = NULL;
		dl_sections->ds_symtab = LOCK_SECTION(secname_dynsym);
		if (dl_sections->ds_symtab) {
			dl_sections->ds_strtab = LOCK_SECTION(secname_dynstr);
			if unlikely(!dl_sections->ds_strtab) {
				module_section_decref(dl_sections->ds_symtab,
				                      module_type);
			}
		}
	}
#undef LOCK_SECTION
	/* Bind section data */
	if (dl_sections->ds_eh_frame) {
		sections->ds_eh_frame_start = (byte_t *)module_section_getudata(dl_sections->ds_eh_frame, module_type);
		sections->ds_eh_frame_end   = sections->ds_eh_frame_start + module_section_getsize(dl_sections->ds_eh_frame, module_type);
	}
#define BIND_SECTION(sect, lv_start, lv_end)                                    \
	if (sect) {                                                                 \
		size_t size;                                                            \
		(lv_start) = (byte_t *)module_section_inflate(sect, module_type, size); \
		(lv_end)   = (lv_start) + size;                                         \
	}
	BIND_SECTION(dl_sections->ds_debug_frame, sections->ds_debug_frame_start, sections->ds_debug_frame_end);
	BIND_SECTION(dl_sections->ds_debug_addr, sections->ds_debug_addr_start, sections->ds_debug_addr_end);
	BIND_SECTION(dl_sections->ds_debug_loc, sections->ds_debug_loc_start, sections->ds_debug_loc_end);
	BIND_SECTION(dl_sections->ds_debug_abbrev, sections->ds_debug_abbrev_start, sections->ds_debug_abbrev_end);
	BIND_SECTION(dl_sections->ds_debug_info, sections->ds_debug_info_start, sections->ds_debug_info_end);
	BIND_SECTION(dl_sections->ds_debug_str, sections->ds_debug_str_start, sections->ds_debug_str_end);
	BIND_SECTION(dl_sections->ds_debug_aranges, sections->ds_debug_aranges_start, sections->ds_debug_aranges_end);
	BIND_SECTION(dl_sections->ds_debug_ranges, sections->ds_debug_ranges_start, sections->ds_debug_ranges_end);
	BIND_SECTION(dl_sections->ds_debug_line, sections->ds_debug_line_start, sections->ds_debug_line_end);
#undef BIND_SECTION
	/* Bind symbol/string sections. */
	if (dl_sections->ds_symtab) {
		size_t size;
		sections->ds_strtab_start = (byte_t *)module_section_inflate(dl_sections->ds_strtab,
		                                                             module_type, size);
		sections->ds_strtab_end   = sections->ds_strtab_start + size;
		sections->ds_symtab_start = (byte_t *)module_section_inflate(dl_sections->ds_symtab,
		                                                             module_type, size);
		sections->ds_symtab_end   = sections->ds_symtab_start + size;
		sections->ds_symtab_ent   = module_section_getentsize(dl_sections->ds_symtab, module_type);
	}
}

INTERN NONNULL((1)) void
NOTHROW_NCX(CC libdi_debug_sections_unlock)(di_debug_dl_sections_t *__restrict dl_sections
                                            module_type__param(module_type)) {
	unsigned int i;
	for (i = 0; i < sizeof(di_debug_dl_sections_t) / sizeof(REF module_section_t *); ++i) {
		REF module_section_t *section;
		section = ((REF module_section_t **)dl_sections)[i];
		if (section)
			module_section_decref(section, module_type);
	}
}



#undef debuginfo_cu_parser_skipform
DEFINE_PUBLIC_ALIAS(debuginfo_cu_abbrev_fini, libdi_debuginfo_cu_abbrev_fini);
DEFINE_PUBLIC_ALIAS(debuginfo_cu_parser_loadunit, libdi_debuginfo_cu_parser_loadunit);
DEFINE_PUBLIC_ALIAS(debuginfo_cu_parser_skipform, libdi_debuginfo_cu_parser_skipform);
DEFINE_PUBLIC_ALIAS(debuginfo_cu_parser_next, libdi_debuginfo_cu_parser_next);
DEFINE_PUBLIC_ALIAS(debuginfo_cu_parser_nextchild, libdi_debuginfo_cu_parser_nextchild);
DEFINE_PUBLIC_ALIAS(debuginfo_cu_parser_nextsibling, libdi_debuginfo_cu_parser_nextsibling);
DEFINE_PUBLIC_ALIAS(debuginfo_cu_parser_nextparent, libdi_debuginfo_cu_parser_nextparent);
DEFINE_PUBLIC_ALIAS(debuginfo_cu_parser_skipattr, libdi_debuginfo_cu_parser_skipattr);
DEFINE_PUBLIC_ALIAS(debuginfo_cu_parser_getstring, libdi_debuginfo_cu_parser_getstring);
DEFINE_PUBLIC_ALIAS(debuginfo_cu_parser_getaddr, libdi_debuginfo_cu_parser_getaddr);
DEFINE_PUBLIC_ALIAS(debuginfo_cu_parser_getconst, libdi_debuginfo_cu_parser_getconst);
DEFINE_PUBLIC_ALIAS(debuginfo_cu_parser_getflag, libdi_debuginfo_cu_parser_getflag);
DEFINE_PUBLIC_ALIAS(debuginfo_cu_parser_getref, libdi_debuginfo_cu_parser_getref);
DEFINE_PUBLIC_ALIAS(debuginfo_cu_parser_getexpr, libdi_debuginfo_cu_parser_getexpr);
DEFINE_PUBLIC_ALIAS(debuginfo_cu_parser_loadattr_compile_unit, libdi_debuginfo_cu_parser_loadattr_compile_unit);
DEFINE_PUBLIC_ALIAS(debuginfo_cu_parser_loadattr_subprogram, libdi_debuginfo_cu_parser_loadattr_subprogram);
DEFINE_PUBLIC_ALIAS(debuginfo_cu_parser_loadattr_inlined_subroutine, libdi_debuginfo_cu_parser_loadattr_inlined_subroutine);
DEFINE_PUBLIC_ALIAS(debuginfo_cu_parser_loadattr_lexical_block, libdi_debuginfo_cu_parser_loadattr_lexical_block);
DEFINE_PUBLIC_ALIAS(debuginfo_cu_parser_loadattr_type, libdi_debuginfo_cu_parser_loadattr_type);
DEFINE_PUBLIC_ALIAS(debuginfo_cu_parser_loadattr_member, libdi_debuginfo_cu_parser_loadattr_member);
DEFINE_PUBLIC_ALIAS(debuginfo_cu_parser_loadattr_variable, libdi_debuginfo_cu_parser_loadattr_variable);
DEFINE_PUBLIC_ALIAS(debuginfo_print_typename, libdi_debuginfo_print_typename);
DEFINE_PUBLIC_ALIAS(debuginfo_print_value, libdi_debuginfo_print_value);
DEFINE_PUBLIC_ALIAS(debuginfo_enum_locals, libdi_debuginfo_enum_locals);
DEFINE_PUBLIC_ALIAS(debug_sections_lock, libdi_debug_sections_lock);
DEFINE_PUBLIC_ALIAS(debug_sections_unlock, libdi_debug_sections_unlock);

DECL_END

#endif /* !GUARD_LIBDEBUGINFO_DEBUG_INFO_C */
