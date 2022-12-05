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
#ifndef GUARD_MODDBX_CMODULE_C
#define GUARD_MODDBX_CMODULE_C 1
#define _KOS_SOURCE 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER

#include <debugger/input.h>
#include <debugger/rt.h>
#include <kernel/mman.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/module.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <sched/task.h>

#include <hybrid/overflow.h>
#include <hybrid/sequence/bsearch.h>
#include <hybrid/unaligned.h>

#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libdebuginfo/debug_aranges.h>
#include <libdebuginfo/debug_info.h>
#include <libdebuginfo/dwarf.h>
#include <libdebuginfo/errno.h>

/**/
#include "include/cmodule.h"
#include "include/malloc.h"

DECL_BEGIN


/* Initialize a debug information CU parser from a given CModule CompilationUnit
 * @param: dip: A pointer  to the  first component  to load,  or `NULL'  to simply  load
 *              the first component following the start of the associated CU descriptor.
 *              When  non-NULL,  this   pointer  must  be   located  somewhere   between
 *              `cmodunit_di_start(self)' and `cmodunit_di_maxend(self)'.
 *              If it isn't, then the parser will be initialized to always indicate EOF. */
PUBLIC NONNULL((1, 2, 3)) void
NOTHROW(FCALL cmodunit_parser_from_dip)(struct cmodunit const *__restrict self,
                                        struct cmodule const *__restrict mod,
                                        di_debuginfo_cu_parser_t *__restrict result,
                                        byte_t const *dip) {
	uintptr_t temp;
	byte_t const *reader;
	uint8_t unit_type;
	reader = cmodunit_di_start(self);
	result->dup_cu_info_hdr = reader;
	/* 7.5.1.1   Compilation Unit Header */
	temp = UNALIGNED_GET32((uint32_t const *)reader); /* unit_length */
	reader += 4;
	result->dsp_ptrsize = 4;
	if (temp == UINT32_C(0xffffffff)) {
		/* 7.4 32-Bit and 64-Bit DWARF Formats
		 * In the 64-bit DWARF format, an initial length field is 96 bits in size, and has two parts:
		 *  - The first 32-bits have the value 0xffffffff.
		 *  - The following 64-bits contain the actual length represented as an unsigned 64-bit integer. */
		temp = (uintptr_t)UNALIGNED_GET64((uint64_t const *)reader); /* unit_length */
		result->dsp_ptrsize = 8;
		reader += 8;
	}
	/* Calculate the end-pointer for this CU, but limit by the max end of the CU. */
	if (OVERFLOW_UADD((uintptr_t)result->dup_cu_info_hdr, temp,
	                  (uintptr_t *)&result->dsp_cu_info_end) ||
	    result->dsp_cu_info_end > cmodunit_di_maxend(self))
		result->dsp_cu_info_end = cmodunit_di_maxend(self);

	result->dsp_version = UNALIGNED_GET16((uint16_t const *)reader); /* version */
	reader += 2;
	if (result->dsp_version >= 5) {
		unit_type = *(uint8_t const *)reader; /* unit_type */
		reader += 1;
		result->dsp_addrsize = *(uint8_t const *)reader; /* address_size */
		reader += 1;
	} else {
		unit_type = DW_UT_compile;
	}
	temp = UNALIGNED_GET32((uint32_t const *)reader); /* debug_abbrev_offset */
	reader += 4;
	if (temp == 0xffffffff)
		reader += 8;
	if (result->dsp_version < 5) {
		result->dsp_addrsize = *(uint8_t const *)reader; /* address_size */
		reader += 1;
	}
	switch (unit_type) {
	case DW_UT_skeleton:
	case DW_UT_split_compile:
		reader += 8; /* dwo_id */
		break;
	case DW_UT_type:
		reader += 8;                   /* type_signature */
		reader += result->dsp_ptrsize; /* type_offset */
		break;
	default: break;
	}
	result->dsp_cu_info_pos = reader;
	if (dip) {
		/* If the given pointer is outside the valid range, setup the parser for EOF. */
		if (dip < result->dup_cu_info_hdr ||
		    dip > result->dsp_cu_info_end)
			dip = result->dsp_cu_info_end;
		result->dsp_cu_info_pos = dip;
	}
	reader                = result->dsp_cu_info_end;
	result->dup_sections  = cmodule_di_debuginfo_cu_parser_sections(mod);
	result->dup_cu_abbrev = (di_debuginfo_cu_abbrev_t *)&self->cu_abbrev;
	/* Load the first component of the compilation unit. */
	if (!debuginfo_cu_parser_next(result)) {
		/* Fill in a stub/EOF component. */
		result->dup_comp.dic_tag         = 0; /* DW_TAG_... */
		result->dup_comp.dic_haschildren = DW_CHILDREN_no;
		result->dsp_cu_info_pos = result->dsp_cu_info_end;
	}
	result->dup_child_depth = 0;
}




PRIVATE NONNULL((1)) void
NOTHROW(FCALL cmodsymtab_fini)(struct cmodsymtab *__restrict self) {
	dbx_free(self->mst_symv);
}

PRIVATE NONNULL((1)) void
NOTHROW(FCALL cmodunit_fini)(struct cmodunit *__restrict self) {
	if (self->cu_symbols.mst_symv != (struct cmodsym *)-1)
		cmodsymtab_fini(&self->cu_symbols);
	debuginfo_cu_abbrev_fini(&self->cu_abbrev);
}

PRIVATE NONNULL((1)) void
NOTHROW(FCALL cmodule_fini)(struct cmodule *__restrict self) {
	size_t i;
	if (self->cm_pself) {
		if ((*self->cm_pself = self->cm_next) != NULL)
			self->cm_next->cm_pself = self->cm_pself;
	}
	debug_sections_unlock(&self->cm_sectrefs);
	module_decref_unlikely(self->cm_module);
	cmodsymtab_fini(&self->cm_symbols);
	for (i = 0; i < self->cm_cuc; ++i)
		cmodunit_fini(&self->cm_cuv[i]);
	/* Free mixed symbol information. */
	dbx_free(self->cm_mixed.mss_symv);
}


PRIVATE NONNULL((1)) void
NOTHROW(FCALL cmodunit_fini_for_reset)(struct cmodunit *__restrict self) {
	debuginfo_cu_abbrev_fini(&self->cu_abbrev);
}

INTERN NONNULL((1)) void
NOTHROW(FCALL cmodule_fini_for_reset)(struct cmodule *__restrict self) {
	size_t i;
	/* Only need to free/release references to external objects.
	 * iow: no need to call `dbx_free()'! */
	debug_sections_unlock(&self->cm_sectrefs);
	module_decref_unlikely(self->cm_module);
	for (i = 0; i < self->cm_cuc; ++i)
		cmodunit_fini_for_reset(&self->cm_cuv[i]);
}

/* Destroy the given CModule. (called when its reference counter hits `0') */
PUBLIC NONNULL((1)) void
NOTHROW(FCALL cmodule_destroy)(struct cmodule *__restrict self) {
	cmodule_fini(self);
	dbx_free(self);
}


PRIVATE NONNULL((1, 2)) ssize_t
NOTHROW(FCALL cmodule_enum_usermman_except)(struct mman *__restrict self,
                                            cmodule_enum_callback_t cb,
                                            void *cookie,
                                            struct cmodule *skipme) {
	ssize_t temp, result = 0;
	REF struct module *um, *nx;
	/* Enumerate modules. */
	for (um = mman_module_first_nx(self); um != NULL;
	     nx = mman_module_next_nx(self, um), decref(um), um = nx) {
		REF struct cmodule *cm;
		cm = cmodule_locate((module_t *)um);
		if likely(cm) {
			temp = 0;
			if (cm != skipme)
				temp = (*cb)(cookie, cm);
			decref(cm);
			if unlikely(temp < 0) {
				decref(um);
				goto err;
			}
			result += temp;
		}
		/* Check if the user has requested an interrupt. */
		if (dbg_awaituser()) {
			decref(um);
			result = DBX_EINTR;
			break;
		}
	}
done:
	return result;
err:
	result = temp;
	goto done;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW(FCALL cmodule_enum_drivers_except)(cmodule_enum_callback_t cb,
                                           void *cookie,
                                           struct cmodule *skipme) {
	size_t i;
	ssize_t temp, result = 0;
	REF struct driver_loadlist *dll;
	/* Enumerate drivers, including the kernel core driver. */
	dll = get_driver_loadlist();
	for (i = 0; i < dll->dll_count; ++i) {
		REF struct cmodule *cm;
		REF struct driver *drv;
		drv = dll->dll_drivers[i];
		if unlikely(!tryincref(drv))
			continue;
		cm = cmodule_locate(drv);
		decref_unlikely(drv);
		if likely(cm) {
			temp = 0;
			if (cm != skipme)
				temp = (*cb)(cookie, cm);
			decref(cm);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		/* Check if the user has requested an interrupt. */
		if (dbg_awaituser()) {
			result = DBX_EINTR;
			break;
		}
	}
done:
	decref(dll);
	return result;
err:
	result = temp;
	goto done;
}

/* Enumerate all CModules that are currently visible in the following order:
 * >> void const *pc = dbg_getpcreg(DBG_RT_REGLEVEL_VIEW);
 * >> ENUM(cmodule_ataddr(pc));
 * >> if (ADDR_ISKERN(pc)) {
 * >>     cmodule_enum_drivers();                 // Excluding `cmodule_ataddr(pc)'
 * >>     cmodule_enum_usermman(dbg_current->t_mman);
 * >> } else {
 * >>     cmodule_enum_usermman(dbg_current->t_mman); // Excluding `cmodule_ataddr(pc)'
 * >>     cmodule_enum_drivers();
 * >> }
 * @return: * :        pformatprinter-compatible return value.
 * @return: DBX_EINTR: Operation was interrupted. */
PUBLIC NONNULL((1)) ssize_t
NOTHROW(FCALL cmodule_enum)(cmodule_enum_callback_t cb,
                            void *cookie) {
	ssize_t result;
	REF struct cmodule *pc_module;
	void const *pc;
	pc        = dbg_getpcreg(DBG_RT_REGLEVEL_VIEW);
	pc_module = cmodule_ataddr(pc);
	result    = cmodule_enum_with_hint(pc_module, cb, cookie);
	xdecref(pc_module);
	return result;
}

/* Same as `cmodule_enum()', but use `start_module' (if non-NULL) instead of `cmodule_ataddr(pc)' */
PUBLIC NONNULL((2)) ssize_t
NOTHROW(FCALL cmodule_enum_with_hint)(struct cmodule *start_module,
                                      cmodule_enum_callback_t cb,
                                      void *cookie) {
	ssize_t temp, result = 0;
	if (start_module) {
		result = (*cb)(cookie, start_module);
		if (result < 0)
			goto done;
	}
	/* Enumerate other modules in the documented order. */
	if (!start_module || cmodule_iskern(start_module)) {
		temp = cmodule_enum_drivers(cb, cookie);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	/* Enumerate user-space modules. */
	if (dbg_current && dbg_current->t_self == dbg_current &&
	    dbg_current->t_mman != NULL && dbg_current->t_mman != &mman_kernel) {
		temp = cmodule_enum_usermman_except(dbg_current->t_mman, cb, cookie, start_module);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	if (start_module && !cmodule_iskern(start_module)) {
		temp = cmodule_enum_drivers(cb, cookie);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
done:
	return result;
err:
	result = temp;
	goto done;
}


/* Enumerate all user-space modules mapped within the given mman
 * `self' as CModule objects, and  invoke `cb' on each of  them.
 * @return: * :        pformatprinter-compatible return value.
 * @return: DBX_EINTR: Operation was interrupted. */
PUBLIC NONNULL((1, 2)) ssize_t
NOTHROW(FCALL cmodule_enum_usermman)(struct mman *__restrict self,
                                     cmodule_enum_callback_t cb,
                                     void *cookie) {
	return cmodule_enum_usermman_except(self, cb, cookie, NULL);
}

/* Enumerate all kernel-space drivers as CModule objects, and
 * invoke `cb' on each of them.
 * @return: * :        pformatprinter-compatible return value.
 * @return: DBX_EINTR: Operation was interrupted. */
PUBLIC NONNULL((1)) ssize_t
NOTHROW(FCALL cmodule_enum_drivers)(cmodule_enum_callback_t cb,
                                    void *cookie) {
	return cmodule_enum_drivers_except(cb, cookie, NULL);
}





/* [0..1] Linked list of loaded debug-module objects (cleared during
 *        debugger reset; elements are lazily removed as they are
 *        destroyed) */
INTERN struct cmodule *cmodule_list = NULL;

/* [0..1] Cache of already-loaded DW modules. */
INTERN REF struct cmodule *cmodule_cache = NULL;

/* Clear the internal cache of pre-loaded DW modules (called
 * from `dbx_heap_alloc()' in  an attempt  to free  memory).
 * @param: keep_loaded: When true, keep  modules descriptors  loaded if  they
 *                      are apart of the kernel, or the `dbg_current->t_mman'
 *                      Otherwise, clear all modules from the cache.
 * @return: * : The # of modules that actually got destroyed (i.e. removing
 *              them from the  cache caused  their refcnt to  drop to  `0') */
PUBLIC size_t NOTHROW(FCALL cmodule_clearcache)(bool keep_loaded) {
	size_t result = 0;
	struct cmodule **piter, *iter;
	piter = &cmodule_cache;
	while ((iter = *piter) != NULL) {
		if (keep_loaded) {
			/* Check if we should keep this module. */
			struct mman *modvm;
			modvm = iter->cm_module->md_mman;
			if (modvm == &mman_kernel ||
			    modvm == dbg_current->t_mman) {
				/* Don't remove this one. */
				piter = &iter->cm_cache;
				continue;
			}
		}
		/* Remove this one! */
		*piter = iter->cm_cache; /* Unlink */
		/* Drop the cache reference. */
		if (--iter->cm_refcnt == 0) {
			destroy(iter);
			++result;
		}
	}
	return result;
}


PRIVATE NONNULL((1, 2)) void
NOTHROW(FCALL cmodule_reloc_units)(struct cmodule *new_addr,
                                   struct cmodule *old_addr,
                                   size_t cuc) {
	size_t i;
	if (new_addr == old_addr)
		return;
	/* When relocating a cmodule causes its base-address to change,
	 * then we must fix-up the abbreviation cache list pointers  of
	 * already-initialized compilation units.
	 * Otherwise, (if those pointers referenced the static abbreviation
	 * cache), they would still point to the old object position, which
	 * is no longer valid, as the static cache will have been moved  as
	 * well. */
	for (i = 0; i < cuc; ++i) {
		struct cmodunit *new_cu, *old_cu;
		new_cu = &new_addr->cm_cuv[i];
		old_cu = &old_addr->cm_cuv[i];
		if (new_cu->cu_abbrev.dua_cache_list == old_cu->cu_abbrev.dua_stcache)
			new_cu->cu_abbrev.dua_cache_list = new_cu->cu_abbrev.dua_stcache;
	}
}


#if __SIZEOF_POINTER__ > 4
#define addrsize_isvalid(v) ((v) == 1 || (v) == 2 || (v) == 4 || (v) == 8)
#else /* __SIZEOF_POINTER__ > 4 */
#define addrsize_isvalid(v) ((v) == 1 || (v) == 2 || (v) == 4)
#endif /* __SIZEOF_POINTER__ <= 4 */

PRIVATE NONNULL((1)) void
NOTHROW(FCALL print_invalid_addrsize_warning)(di_debuginfo_cu_parser_t const *__restrict parser,
                                              byte_t const *__restrict reader) {
	printk(KERN_ERR "[dbx][dwarf%" PRIu16 "] Illegal address_size %#" PRIx8 " in .debug_info CU header at %p\n",
	       parser->dsp_version, parser->dsp_addrsize, reader);
}


PRIVATE WUNUSED NONNULL((1)) REF struct cmodule *
NOTHROW(FCALL cmodule_create)(module_t *__restrict mod) {
#define SIZEOF_CMODULE(cuc)              \
	(offsetof(struct cmodule, cm_cuv) +  \
	 ((cuc) * sizeof(struct cmodunit)) + \
	 offsetafter(struct cmodunit, cu_di_start))
	REF struct cmodule *result;
	size_t cuc_used  = 0;
	size_t cuc_alloc = 16;
	result = (REF struct cmodule *)dbx_malloc(SIZEOF_CMODULE(16));
	if unlikely(!result) {
		cuc_alloc = 1;
		result = (REF struct cmodule *)dbx_malloc(SIZEOF_CMODULE(1));
		if unlikely(!result)
			goto done;
	}
	/* Load debug sections. */
	debug_sections_lock(mod, &result->cm_sections, &result->cm_sectrefs);
	/* Special handling to ensure that .symtab is loaded as intended
	 * when   accessing  debug  information  for  the  kernel  core. */
	if (mod == (module_t *)&kernel_driver) {
		result->cm_sections.ds_symtab_start = (byte_t const *)&kernel_symbol_table;
		result->cm_sections.ds_symtab_end   = NULL;
		result->cm_sections.ds_symtab_ent   = 0;
		result->cm_sections.ds_strtab_start = NULL;
		result->cm_sections.ds_strtab_end   = NULL;
	}
	/* Now walk through .debug_info and count the total # of CUs, as
	 * well  as initialize the PER-CU fields from `struct cmodunit'.
	 * The per-CU ordering of  offsets into the .debug_info  section
	 * are gained automatically  since we're traversing  .debug_info
	 * linearly, and always appending to the end of the list of  CUs */
	{
		byte_t const *reader, *end, *next_cu;
		reader = result->cm_sections.ds_debug_info_start;
		end    = result->cm_sections.ds_debug_info_end;
		result->cm_cuv[0].cu_di_start = end; /* Initial end-pointer (for consistency) */
		while (reader < end) {
			di_debuginfo_cu_parser_t parser;
			size_t length;
			uintptr_t debug_abbrev_offset;
			uint8_t unit_type;
			struct cmodunit *cu;
			if (cuc_used >= cuc_alloc) {
				/* Must allocate space for more CUs. */
				REF struct cmodule *new_result;
				cuc_alloc  = cuc_used + 16;
				new_result = (REF struct cmodule *)dbx_realloc(result, SIZEOF_CMODULE(cuc_alloc));
				if unlikely(!new_result) {
					cuc_alloc  = cuc_used + 1;
					new_result = (REF struct cmodule *)dbx_realloc(result, SIZEOF_CMODULE(cuc_alloc));
					if unlikely(!new_result)
						goto err_r; /* Out of memory... :( */
				}
				cmodule_reloc_units(new_result, result, cuc_used);
				result = new_result;
			}
			cu = &result->cm_cuv[cuc_used];

			/* s.a. DWARF: 7.5.1.1   Compilation Unit Header */
			cu->cu_di_start         = reader;
			cu->cu_symbols.mst_symc = 0;
			cu->cu_symbols.mst_symv = (struct cmodsym *)-1; /* Not loaded. */
			length = UNALIGNED_GET32((uint32_t const *)reader); /* unit_length */
			reader += 4;
			parser.dsp_ptrsize = 4;
			if (length >= UINT32_C(0xfffffff0)) {
				if (length == UINT32_C(0xffffffff)) {
					/* 7.4 32-Bit and 64-Bit DWARF Formats
					 * In the 64-bit DWARF format, an initial length field is 96 bits in size, and has two parts:
					 *  - The first 32-bits have the value 0xffffffff.
					 *  - The following 64-bits contain the actual length represented as an unsigned 64-bit integer. */
					length = (size_t)UNALIGNED_GET64((uint64_t const *)reader);
					reader += 8;
					parser.dsp_ptrsize = 8;
				} else {
					/* 7.2.2 Initial Length Values
					 * ...
					 * values 0xfffffff0 through 0xffffffff are reserved by DWARF */
					printk(KERN_ERR "[dbx] Illegal length value in .debug_info CU header at %p\n",
					       reader - 4);
					goto done_cucs;
				}
			}
			if (OVERFLOW_UADD((uintptr_t)reader, length, (uintptr_t *)&next_cu) || next_cu > end)
				next_cu = end;
			cu[1].cu_di_start = next_cu; /* Set the END-pointer. */
			parser.dsp_version = UNALIGNED_GET16((uint16_t const *)reader);
			reader += 2; /* version */
			if (parser.dsp_version >= 5) {
				unit_type = *(uint8_t const *)reader; /* unit_type */
				reader += 1;
				parser.dsp_addrsize = *(uint8_t const *)reader; /* address_size */
				if unlikely(!addrsize_isvalid(parser.dsp_addrsize)) {
					print_invalid_addrsize_warning(&parser, reader);
					goto done_cucs;
				}
				reader += 1;
			} else {
				unit_type = DW_UT_compile;
			}
			debug_abbrev_offset = UNALIGNED_GET32((uint32_t const *)reader); /* debug_abbrev_offset */
			reader += 4;
			if (debug_abbrev_offset == 0xffffffff) {
				debug_abbrev_offset = (uintptr_t)UNALIGNED_GET64((uint64_t const *)reader);
				reader += 8;
			}
			if unlikely(OVERFLOW_UADD((uintptr_t)result->cm_sections.ds_debug_abbrev_start, debug_abbrev_offset,
			                          (uintptr_t *)&cu->cu_abbrev.dua_abbrev) ||
			            cu->cu_abbrev.dua_abbrev >= result->cm_sections.ds_debug_abbrev_end) {
				printk(KERN_ERR "[dbx] Illegal .debug_abbrev offset %#" PRIxPTR " in .debug_info CU header before %p\n",
				       debug_abbrev_offset, reader);
				goto done_cucs;
			}
			/* Fill in misc. fields of the abbreviation cache. */
			cu->cu_abbrev.dua_cache_list = cu->cu_abbrev.dua_stcache;
			cu->cu_abbrev.dua_cache_size = 0;
			cu->cu_abbrev.dua_cache_next = 0;

			if (parser.dsp_version < 5) {
				parser.dsp_addrsize = *(uint8_t const *)reader; /* address_size */
				if unlikely(!addrsize_isvalid(parser.dsp_addrsize)) {
					print_invalid_addrsize_warning(&parser, reader);
					goto done_cucs;
				}
				reader += 1;
			}

			switch (unit_type) {
			case DW_UT_skeleton:
			case DW_UT_split_compile:
				reader += 8; /* dwo_id */
				break;
			case DW_UT_type:
				reader += 8;                  /* type_signature */
				reader += parser.dsp_ptrsize; /* type_offset */
				break;
			default: break;
			}

			/* At  this point,  `reader' would be  used to initialize  `dsp_cu_info_pos' of a
			 * parser, which in all likelihood would yield a `DW_TAG_compile_unit' component. */

			/* If what follows is a  `DW_TAG_compile_unit', which itself is  then
			 * followed by EOF, then we can skip this CU. When this happens, then
			 * the  associated CU originates from an assembly file, which in turn
			 * doesn't contain any additional debug  info, so we can just  ignore
			 * and discard it here! */
			parser.dup_sections    = cmodule_di_debuginfo_cu_parser_sections(result);
			parser.dup_cu_abbrev   = &cu->cu_abbrev;
			parser.dup_cu_info_hdr = cmodunit_di_start(cu);
			parser.dsp_cu_info_end = cmodunit_di_maxend(cu);
			parser.dsp_cu_info_pos = reader;
			parser.dup_child_depth = 0;
			/* Ignore CUs for which we can't load any initial component. */
			if (debuginfo_cu_parser_next(&parser)) {
again_check_top_level_cu:
				if (parser.dup_comp.dic_tag == DW_TAG_compile_unit) {
					debuginfo_cu_parser_skipattr(&parser);
					if (!debuginfo_cu_parser_next(&parser))
						goto do_next_cu;
					if (parser.dup_child_depth == 0)
						goto again_check_top_level_cu;
				}
				/* Commit the newly initialize CU by incrementing the used-counter. */
				++cuc_used;
			}

do_next_cu:
			/* Continue parsing the next CU. */
			reader = next_cu;
		}
	}
done_cucs:
	if (cuc_used < cuc_alloc) {
		REF struct cmodule *new_result;
		/* Release unused memory. */
		new_result = (REF struct cmodule *)dbx_realloc(result, SIZEOF_CMODULE(cuc_used));
		if likely(new_result) {
			cmodule_reloc_units(new_result, result, cuc_used);
			result = new_result;
		}
	}
	/* Fill in misc. fields of result. */
	result->cm_refcnt = 1;
	module_incref(mod);
	result->cm_module           = mod; /* Inherit reference */
	result->cm_symbols.mst_symc = 0;
	result->cm_symbols.mst_symv = NULL;
	result->cm_mixed.mss_symc   = 0;
	result->cm_mixed.mss_symv   = NULL;
	result->cm_cuc              = cuc_used;
done:
	return result;
err_r:
	/* Unlock .debug_* sections. */
	debug_sections_unlock(&result->cm_sectrefs);
	dbx_free(result);
	result = NULL;
	goto done;
}

/* Lookup or create the CModule for the given `mod'
 * If  the module has already been loaded, return a reference to
 * the pre-loaded CModule. Otherwise, create and remember a  new
 * module which is then kept in-cache. If this step fails due to
 * lack of memory, `NULL' is returned instead. */
PUBLIC WUNUSED NONNULL((1)) REF struct cmodule *
NOTHROW(FCALL cmodule_locate)(module_t *__restrict mod) {
	REF struct cmodule *result;

	/* Search for an already-loaded module. */
	for (result = cmodule_list; result; result = result->cm_next) {
		if (result->cm_module == mod)
			return incref(result);
	}

	/* Create a new module. */
	result = cmodule_create(mod);
	if likely(result) {
		result->cm_next  = cmodule_list;
		result->cm_pself = &cmodule_list;
		if (cmodule_list)
			cmodule_list->cm_pself = &result->cm_next;
		cmodule_list = result;
		/* Cache the module so we can find it faster the next time around! */
		result->cm_cache = cmodule_cache;
		cmodule_cache    = incref(result);
	}
	return result;
}

/* Return the CModule descriptor for  a given `addr', which  should
 * be a program counter, or data-pointer. If no such module exists,
 * or its descriptor could not be allocated, return `NULL' instead.
 * This function is a thin wrapper around `module_fromaddr_nx()' + `cmodule_locate()' */
PUBLIC WUNUSED NONNULL((1)) REF struct cmodule *
NOTHROW(FCALL cmodule_ataddr)(void const *addr) {
	REF struct cmodule *result = NULL;
	REF module_t *mod;
	if ((mod = module_fromaddr_nx(addr)) != NULL) {
		/* Lookup the CModule for the `mod' that we've found. */
		result = cmodule_locate(mod);
		module_decref_unlikely(mod);
	}
	return result;
}

/* Return the CModule for  `dbg_getpcreg(DBG_RT_REGLEVEL_VIEW)'
 * Same as `cmodule_ataddr(dbg_getpcreg(DBG_RT_REGLEVEL_VIEW))' */
PUBLIC WUNUSED REF struct cmodule *
NOTHROW(FCALL cmodule_current)(void) {
	void const *pc;
	REF struct cmodule *result;
	pc     = dbg_getpcreg(DBG_RT_REGLEVEL_VIEW);
	result = cmodule_ataddr(pc);
	return result;
}


/* Check if the given symbol `self' is contained within `ns' */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL want_symbol)(struct cmodsym const *__restrict self, uintptr_t ns) {
	uintptr_t symbol_ns;
	symbol_ns = cmodsym_getns(self) & ~CMODSYM_DIP_NS_FCONFLICT;
	switch (ns) {

	case CMODSYM_DIP_NS_NORMAL:
		/* Accept anything */
		return true;

	case CMODSYM_DIP_NS_NONTYPE:
		/* Accept anything that isn't a type */
		return !CMODSYM_DIP_NS_ISTYPE(symbol_ns);

	case CMODSYM_DIP_NS_TYPEDEF:
		/* Accept anything that is a type */
		return CMODSYM_DIP_NS_ISTYPE(symbol_ns);

	default:
		break;
	}
	/* Want a specific namespace. */
	return symbol_ns == ns;
}

/* Return  the  preferred symbol  of the  given  2 based  on `ns'
 * If neither is preferred over the other, return `NULL' instead. */
PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) struct cmodsym *
NOTHROW(FCALL prefer_symbol)(struct cmodsym *__restrict a,
                             struct cmodsym *__restrict b,
                             uintptr_t ns) {
	uintptr_t a_ns, b_ns;
	a_ns = cmodsym_getns(a) & ~CMODSYM_DIP_NS_FCONFLICT;
	b_ns = cmodsym_getns(b) & ~CMODSYM_DIP_NS_FCONFLICT;
	switch (ns) {

	case CMODSYM_DIP_NS_NORMAL:
	case CMODSYM_DIP_NS_SYMTAB:
	case CMODSYM_DIP_NS_MIXED:
		/* Prefer normal (non-type) symbols. */
		if (CMODSYM_DIP_NS_ISNORMAL(a_ns) && !CMODSYM_DIP_NS_ISNORMAL(b_ns))
			return a;
		if (CMODSYM_DIP_NS_ISNORMAL(b_ns) && !CMODSYM_DIP_NS_ISNORMAL(a_ns))
			return b;
		break;

	case CMODSYM_DIP_NS_TYPEDEF:
		/* Prefer pure typedef over struct/union/etc name. */
		if (a_ns == CMODSYM_DIP_NS_TYPEDEF && b_ns != CMODSYM_DIP_NS_TYPEDEF)
			return a;
		if (b_ns == CMODSYM_DIP_NS_TYPEDEF && a_ns != CMODSYM_DIP_NS_TYPEDEF)
			return b;
		break;

	default:
		break;
	}
	return NULL;
}

/* Lookup the given `name' within `self' */
#ifdef CMODSYM_NAME_NEEDS_MODULE
NONNULL((1, 2, 3))
#else /* CMODSYM_NAME_NEEDS_MODULE */
NONNULL((1, 2))
#endif /* !CMODSYM_NAME_NEEDS_MODULE */
PRIVATE ATTR_PURE WUNUSED struct cmodsym *
NOTHROW(FCALL cmodsymtab_lookup)(struct cmodsymtab const *__restrict self,
#ifdef CMODSYM_NAME_NEEDS_MODULE
                                 struct cmodule const *__restrict mod,
#else /* CMODSYM_NAME_NEEDS_MODULE */
#define cmodsymtab_lookup(self, mod, name, namlen, ns) \
	cmodsymtab_lookup(self, name, namlen, ns)
#endif /* !CMODSYM_NAME_NEEDS_MODULE */
                                 char const *__restrict name, size_t namelen,
                                 uintptr_t ns) {
	struct cmodsym *result;
	size_t lo, hi;
	lo = 0, hi = self->mst_symc;
	while (lo < hi) {
		size_t index;
		int cmp;
		char const *symname;
		index  = (lo + hi) / 2;
		result = &self->mst_symv[index];
		symname = cmodsym_name(result, mod);
		cmp     = strcmpz(symname, name, namelen);
		if (cmp > 0) {
			hi = index;
		} else if (cmp < 0) {
			lo = index + 1;
		} else {
			/* Found it! */

			/* Deal with multiple symbols of the same name by looking at `ns'!
			 * Note that right now, other symbols with the same name may  both
			 * be located before and after `result'! */
			struct cmodsym *match_min, *match_max, *iter;
			/* Walk forward/backwards until we find a symbol of a different name. */
			match_min = match_max = result;
			while (match_min > self->mst_symv &&
			       strcmp(cmodsym_name(&match_min[-1], mod), symname) == 0)
				--match_min;
			while (match_max < &self->mst_symv[self->mst_symc - 1] &&
			       strcmp(cmodsym_name(&match_max[1], mod), symname) == 0)
				++match_max;

			result = NULL;
			/* Select the symbol which we prefer the most. */
			for (iter = match_min; iter <= match_max; ++iter) {
				if (!want_symbol(iter, ns))
					continue;
				if (!result) {
					result = iter;
				} else {
					result = prefer_symbol(result, iter, ns);
					if (!result)
						break;
				}
			}
			return result;
		}
	}
	/* Not found... */
	return NULL;
}





PRIVATE NONNULL((1, 2, 4)) char const *
NOTHROW(FCALL parse_symbol_name_for_object)(di_debuginfo_cu_parser_t *__restrict self,
                                            uintptr_t *__restrict pns,
                                            bool reuse_parser,
                                            bool *__restrict phas_location_information);
PRIVATE ATTR_NOINLINE NONNULL((1)) char const *
NOTHROW(FCALL parse_symbol_name_for_object_r)(di_debuginfo_cu_parser_t *__restrict self,
                                              byte_t const *__restrict abstract_origin,
                                              uintptr_t *__restrict pns,
                                              bool *__restrict phas_location_information) {
	di_debuginfo_cu_parser_t inner_parser;
	memcpy(&inner_parser, self, sizeof(inner_parser));
	inner_parser.dsp_cu_info_pos = abstract_origin;
	if (!debuginfo_cu_parser_next(&inner_parser))
		return NULL;
	return parse_symbol_name_for_object(&inner_parser, pns, true,
	                                    phas_location_information);
}


/* Varinfo feature flags. */
#define DEBUGINFO_VAR_FEATURE_HASTYPE     0x0001
#define DEBUGINFO_VAR_FEATURE_HASLOCATION 0x0002

PRIVATE ATTR_NOINLINE NONNULL((1, 2, 3, 4, 5)) void
NOTHROW(FCALL parse_variable_specifications)(di_debuginfo_cu_parser_t const *__restrict self,
                                             byte_t const *__restrict specification,
                                             char const **__restrict plinkage_name,
                                             char const **__restrict pname,
                                             unsigned int *__restrict pfeatures) {
	di_debuginfo_cu_parser_t inner_parser;
	di_debuginfo_component_attrib_t attr;
	memcpy(&inner_parser, self, sizeof(inner_parser));
	inner_parser.dsp_cu_info_pos = specification;
again:
	if (debuginfo_cu_parser_next(&inner_parser)) {
		if (inner_parser.dup_comp.dic_tag == DW_TAG_variable ||
		    inner_parser.dup_comp.dic_tag == DW_TAG_constant ||
		    inner_parser.dup_comp.dic_tag == DW_TAG_enumerator) {
			DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &inner_parser) {
				switch (attr.dica_name) {

				case DW_AT_abstract_origin: {
					byte_t const *abstract_origin;
					/* Load data from the pointed-to location. */
					if unlikely(!debuginfo_cu_parser_getref(&inner_parser, attr.dica_form,
					                                        &abstract_origin))
						return;
					if (dbg_awaituser()) /* Allow the user to break an infinite loop caused by bad debug-info... */
						return;
					inner_parser.dsp_cu_info_pos = abstract_origin;
					goto again;
				}	break;

				DW_CASE_AT_linkage_name:
					if (!*plinkage_name) {
						if unlikely(!debuginfo_cu_parser_getstring(&inner_parser, attr.dica_form, plinkage_name))
							*plinkage_name = NULL;
					}
					break;

				case DW_AT_name:
					if (!*pname) {
						if unlikely(!debuginfo_cu_parser_getstring(&inner_parser, attr.dica_form, pname))
							*pname = NULL;
					}
					break;

				case DW_AT_type:
					*pfeatures |= DEBUGINFO_VAR_FEATURE_HASTYPE;
					break;

				case DW_AT_const_value:
				case DW_AT_location:
					*pfeatures |= DEBUGINFO_VAR_FEATURE_HASLOCATION;
					break;

				default:
					break;
				}
			}
		}
	}
}

/* Parse the currently pointed-to  component's attributes in an  attempt
 * to figure out if it has a  name that should appear in symbol  tables.
 * If it does, then that name is returned. Otherwise, NULL is  returned,
 * but attributes for the current component will have still been parsed. */
PRIVATE NONNULL((1, 2, 4)) char const *
NOTHROW(FCALL parse_symbol_name_for_object)(di_debuginfo_cu_parser_t *__restrict self,
                                            uintptr_t *__restrict pns,
                                            bool reuse_parser,
                                            bool *__restrict phas_location_information) {
	di_debuginfo_component_attrib_t attr;
	byte_t const *attrib_pos;
	char const *result = NULL;
again:
	attrib_pos = self->dsp_cu_info_pos;
	switch (self->dup_comp.dic_tag) {

	case DW_TAG_variable:
	case DW_TAG_constant:
	case DW_TAG_enumerator: {
		/* Variables/constants. Requires:
		 * #1: - One of: DW_AT_const_value, DW_AT_location
		 *     - DW_AT_specification that points to another `DW_TAG_variable' with:
		 *         - One of: DW_AT_linkage_name, DW_AT_name
		 *         - One of: DW_AT_type
		 * #2: - One of: DW_AT_linkage_name, DW_AT_name
		 *     - One of: DW_AT_const_value, DW_AT_location
		 *     - One of: DW_AT_type
		 */
		char const *name_attribute = NULL;
		unsigned int features = 0;
		DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, self) {
			switch (attr.dica_name) {

			case DW_AT_abstract_origin:
				goto do_abstract_origin;

			case DW_AT_sibling:
			case DW_AT_specification: {
				byte_t const *specification;
				if (debuginfo_cu_parser_getref(self, attr.dica_form, &specification)) {
					/* Only load the pointed-to name if we don't already have one. */
					if (result && !name_attribute)
						name_attribute = result;
					if (name_attribute && !result)
						result = name_attribute;
					parse_variable_specifications(self, specification,
					                              &result, &name_attribute,
					                              &features);
				}
			}	break;

			DW_CASE_AT_linkage_name:
				if (!result) {
					if unlikely(!debuginfo_cu_parser_getstring(self, attr.dica_form, &result))
						result = NULL;
				}
				break;

			case DW_AT_name:
				if (!name_attribute) {
					if unlikely(!debuginfo_cu_parser_getstring(self, attr.dica_form, &name_attribute))
						name_attribute = NULL;
				}
				break;

			case DW_AT_type:
				features |= DEBUGINFO_VAR_FEATURE_HASTYPE;
				break;

			case DW_AT_const_value:
			case DW_AT_location:
				features |= DEBUGINFO_VAR_FEATURE_HASLOCATION;
				break;

			default:
				break;
			}
		}
		if (!result)
			result = name_attribute;
		if (!(features & DEBUGINFO_VAR_FEATURE_HASTYPE)) {
			result = NULL; /* We always need a type! */
		} else {
			*phas_location_information = (features & DEBUGINFO_VAR_FEATURE_HASLOCATION) != 0;
		}
		*pns = CMODSYM_DIP_NS_NORMAL;
	}	break;

	case DW_TAG_subprogram:
	case DW_TAG_label: {
		/* Program locations. Requires:
		 *  - One of: DW_AT_linkage_name, DW_AT_name
		 *  - One of: DW_AT_low_pc, DW_AT_entry_pc
		 */
		char const *name_attribute = NULL;
		*phas_location_information = false;
		DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, self) {
			switch (attr.dica_name) {

			case DW_AT_abstract_origin:
				goto do_abstract_origin;

			DW_CASE_AT_linkage_name:
				if (!result) {
					if unlikely(!debuginfo_cu_parser_getstring(self, attr.dica_form, &result))
						result = NULL;
				}
				break;

			case DW_AT_name:
				if (!name_attribute) {
					if unlikely(!debuginfo_cu_parser_getstring(self, attr.dica_form, &name_attribute))
						name_attribute = NULL;
				}
				break;

			case DW_AT_low_pc:
			case DW_AT_entry_pc:
				*phas_location_information = true;
				break;

			default:
				break;
			}
		}
		if (!result)
			result = name_attribute;
		*pns = CMODSYM_DIP_NS_NORMAL;
	}	break;

	case DW_TAG_array_type:
	case DW_TAG_class_type:
	case DW_TAG_enumeration_type:
	case DW_TAG_pointer_type:
	case DW_TAG_reference_type:
	case DW_TAG_string_type:
	case DW_TAG_structure_type:
	case DW_TAG_subroutine_type:
	case DW_TAG_typedef:
	case DW_TAG_union_type:
	case DW_TAG_ptr_to_member_type:
	case DW_TAG_set_type:
	case DW_TAG_subrange_type:
	case DW_TAG_base_type:
	case DW_TAG_const_type:
	case DW_TAG_file_type:
	case DW_TAG_packed_type:
	case DW_TAG_volatile_type:
	case DW_TAG_restrict_type:
	case DW_TAG_interface_type:
	case DW_TAG_namespace:
	case DW_TAG_unspecified_type:
	case DW_TAG_shared_type:
	case DW_TAG_rvalue_reference_type:
	case DW_TAG_atomic_type:
		/* Type definitions. Requires:
		 *  - One of: DW_AT_name
		 * TODO: Also require some further identification that we
		 *       can make use of know that the type is  complete.
		 *       e.g. In  the  case  of  a  struct,  require  that  there
		 *            be  a  `DW_AT_byte_size'  field.  (or  better  yet:
		 *            simply ensure that `self->dup_comp.dic_haschildren'
		 *            is true,  meaning  that  the struct  has  at  least
		 *            some  members  defined,  though  in  that  case, we
		 *            must  also  allow  a struct  without  members, that
		 *            is derived (c++-style) from another struct)
		 * Another example would be that `DW_TAG_pointer_type' must
		 * have a tag `DW_AT_type', which represents the pointed-to
		 * type.
		 * NOTE: The DWARF standard specifies that `DW_AT_declaration'
		 *       should appear in  any forward-declaration, however  I
		 *       really don't  want to  rely on  something like  that,
		 *       because I don't like the idea of the compiler  having
		 *       to specify _more_ information  to tell me that  there
		 *       is _less_ information, when I can just check if there
		 *       is the information I'm  looking for from the  get-go.
		 */
		DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, self) {
			switch (attr.dica_name) {

			case DW_AT_declaration:
				/* Only a declaration; not a definition! */
				DI_DEBUGINFO_CU_PARSER_EACHATTR_BREAK(attr, self);
				return NULL;

			case DW_AT_abstract_origin:
				goto do_abstract_origin;

			case DW_AT_name:
				if unlikely(!debuginfo_cu_parser_getstring(self, attr.dica_form, &result))
					result = NULL;
				break;

			default:
				break;
			}
		}
		/* Select the namespace based on what we're dealing with. */
		switch (self->dup_comp.dic_tag) {
		case DW_TAG_namespace: /*       */ *pns = CMODSYM_DIP_NS_NORMAL; break;
		case DW_TAG_class_type: /*      */ *pns = CMODSYM_DIP_NS_CLASS; break;
		case DW_TAG_enumeration_type: /**/ *pns = CMODSYM_DIP_NS_ENUM; break;
		case DW_TAG_structure_type: /*  */ *pns = CMODSYM_DIP_NS_STRUCT; break;
		case DW_TAG_union_type: /*      */ *pns = CMODSYM_DIP_NS_UNION; break;
		default: /*                     */ *pns = CMODSYM_DIP_NS_TYPEDEF; break;
		}
		*phas_location_information = true; /* Prevent problems down-stream */
		break;

	default:
		/* Fallback: Just skip attributes. */
		debuginfo_cu_parser_skipattr(self);
		break;
	}
	return result;
	{
		byte_t const *abstract_origin;
do_abstract_origin:
		/* Load data from the pointed-to location. */
		if unlikely(!debuginfo_cu_parser_getref(self, attr.dica_form,
		                                        &abstract_origin))
			return NULL;
		if (dbg_awaituser()) /* Allow the user to break an infinite loop caused by bad debug-info... */
			return NULL;
		if (reuse_parser) {
			self->dsp_cu_info_pos = abstract_origin;
			goto again;
		} else {
			/* Make sure that the original parser is exited correctly. */
			self->dsp_cu_info_pos = attrib_pos;
			debuginfo_cu_parser_skipattr(self);
		}
		return parse_symbol_name_for_object_r(self, abstract_origin, pns,
		                                      phas_location_information);
	}
}


/* Check if the 2 given encoded DIP pointer `dip_a'
 * and  `dip_b'  reference   the  same   namespace. */
PRIVATE ATTR_CONST WUNUSED bool
NOTHROW(FCALL same_namespace)(uintptr_t dip_a, uintptr_t dip_b) {
	uintptr_t ns_a, ns_b;
	ns_a = dip_a & (CMODSYM_DIP_NSMASK & ~CMODSYM_DIP_NS_FCONFLICT);
	ns_b = dip_b & (CMODSYM_DIP_NSMASK & ~CMODSYM_DIP_NS_FCONFLICT);
	/* Quick check: Is it the same namespace id? */
	if (ns_a == ns_b)
		return true;
	/* The typedef namespace overlaps the normal namespace, and is
	 * only  there to allow  one to quickly  determine if a symbol
	 * encodes a type, as opposed to a variable/const/etc. */
	if (CMODSYM_DIP_NS_ISGLOBAL(ns_a))
		ns_a = CMODSYM_DIP_NS_NORMAL;
	if (CMODSYM_DIP_NS_ISGLOBAL(ns_b))
		ns_b = CMODSYM_DIP_NS_NORMAL;
	return ns_a == ns_b;
}

/* Insert a new symbol at the given index.
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory. */
PRIVATE WUNUSED NONNULL((1, 3)) dbx_errno_t
NOTHROW(FCALL cmodsymtab_insert_symbol)(struct cmodsymtab *__restrict self,
                                        size_t index,
                                        char const *__restrict name,
                                        uintptr_t symbol_dip) {
	size_t syma;
	assert(index <= self->mst_symc);
	syma = cmodsymtab_syma(self);
	if (self->mst_symc >= syma) {
		/* Must allocate more space. */
		struct cmodsym *new_symtab;
		size_t new_alloc = syma * 2;
		if (new_alloc < self->mst_symc + 16)
			new_alloc = self->mst_symc + 16;
		new_symtab = (struct cmodsym *)dbx_realloc(self->mst_symv,
		                                           new_alloc *
		                                           sizeof(struct cmodsym));
		if unlikely(!new_symtab) {
			/* Try again, but this time try to allocate
			 * the least amount  of additional  memory. */
			new_alloc  = self->mst_symc + 1;
			new_symtab = (struct cmodsym *)dbx_realloc(self->mst_symv,
			                                           new_alloc *
			                                           sizeof(struct cmodsym));
			if unlikely(!new_symtab)
				return DBX_ENOMEM;
		}
		self->mst_symv = new_symtab;
	}

	/* Shift up all already-defined symbols. */
	memmoveup(&self->mst_symv[index + 1],
	          &self->mst_symv[index],
	          self->mst_symc - index,
	          sizeof(struct cmodsym));

	/* Initialize the new symbols. */
	self->mst_symv[index].cms_name = name;
	self->mst_symv[index].cms_dip  = symbol_dip;

	/* Account for the fact that a new symbol got added. */
	++self->mst_symc;

	/* Indicate success. */
	return DBX_EOK;
}

/* Add a new symbol  with the given name  to the given symbol  table.
 * If another symbol with the same name and namespace already exists,
 * the operation  silently succeeds  without adding  the new  symbol,
 * alongside writing an error message to the system log.
 * However, this should only happen when there's something wrong with
 * how debug information is parsed.
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory. */
#ifdef CMODSYM_NAME_NEEDS_MODULE
PRIVATE WUNUSED NONNULL((1, 2, 3)) dbx_errno_t
#else /* CMODSYM_NAME_NEEDS_MODULE */
PRIVATE WUNUSED NONNULL((1, 2)) dbx_errno_t
#define cmodsymtab_addsymbol(self, mod, name, symbol_dip) \
	cmodsymtab_addsymbol(self, name, symbol_dip)
#endif /* !CMODSYM_NAME_NEEDS_MODULE */
NOTHROW(FCALL cmodsymtab_addsymbol)(struct cmodsymtab *__restrict self,
#ifdef CMODSYM_NAME_NEEDS_MODULE
                                    struct cmodule const *__restrict mod,
#endif /* CMODSYM_NAME_NEEDS_MODULE */
                                    char const *__restrict name,
                                    uintptr_t symbol_dip) {
	size_t lo, hi, index;
	lo = 0;
	hi = self->mst_symc;
	for (;;) {
		int cmp;
		struct cmodsym const *sym;
		char const *symname;
		index = (lo + hi) / 2;
		if (lo >= hi)
			break;
		sym     = &self->mst_symv[index];
		symname = cmodsym_name(sym, mod);
		cmp     = strcmp(name, symname);
		if (cmp < 0) {
			hi = index;
		} else if (cmp > 0) {
			lo = index + 1;
		} else {
			/* Found  a  possible conflict.  For  this purpose,
			 * determine the range of symbols that share `name' */
			lo = hi = index;
			while (lo > 0 &&
			       strcmp(cmodsym_name(&self->mst_symv[lo - 1], mod), name) == 0)
				--lo;
			while (hi < self->mst_symc - 1 &&
			       strcmp(cmodsym_name(&self->mst_symv[hi + 1], mod), name) == 0)
				++hi;
			/* Check if one of the pre-existing symbols uses the same namespace as we do. */
			for (index = lo; index <= hi; ++index) {
				sym = &self->mst_symv[index];
				if (!same_namespace(sym->cms_dip, symbol_dip))
					continue; /* Different namespace. */
				/* Symbol re-definition (this shouldn't happen...) */
#if 0
				printk(KERN_WARNING "[dbx] per-cu symbol re-definition of %q (found at %p and %p)\n",
					   name, sym->cms_dip, symbol_dip);
#endif
				return DBX_EOK;
			}
			/* No   collision  (we're  dealing  with  differing  namespace)
			 * As such, simply insert the new symbol at the end of the list
			 * of other symbols that share the same name. */
			index = hi + 1;
			break;
		}
	}
	/* Simply insert the new symbol into the global symbol table under `index' */
	return cmodsymtab_insert_symbol(self, index, name, symbol_dip);
}


/* Add an addend of `sizeof(struct cmodmixsym)' to every symbol's data-offset
 * from the given  symbol table that  has `CMODSYM_DIP_NS_MIXED' typing,  and
 * uses an (old) symbol offset that is `>= offset_of_index' */
PRIVATE WUNUSED NONNULL((1)) void
NOTHROW(FCALL cmodule_relocate_mip_symbols_below)(struct cmodsymtab *__restrict self,
                                                  uintptr_t offset_of_index) {
	size_t i;
	for (i = 0; i < self->mst_symc; ++i) {
		struct cmodsym *sym;
		sym = &self->mst_symv[i];
		if (cmodsym_ismip(sym)) {
			uintptr_t offset;
			offset = sym->cms_dip & CMODSYM_DIP_DIPMASK;
			if (offset >= offset_of_index)
				sym->cms_dip += sizeof(struct cmodmixsym);
		}
	}
}


/* Turn `sym' into a mixed .debug_info/.symtab symbol
 * encoding  `dip' and `sip' as information pointers.
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory. */
PRIVATE WUNUSED NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL cmodule_make_symbol_mixed)(struct cmodule *__restrict self,
                                         struct cmodsym *__restrict sym,
                                         byte_t const *__restrict dip,
                                         CLinkerSymbol const *__restrict sip) {
	size_t index, alloc;
	struct cmodmixsym *mixed;
	/* First up: Because we may have  been re-started, we must  check
	 *           if the mixed  symbol table may  already contain  our
	 *           entry. Doing so is normally fairly straight forward,
	 *           since  our caller usually scans .debug_info from the
	 *           front to the back, meaning that usually we're always
	 *           given  `dip' values greater  than any previous ones.
	 * Technically, not even the act of interrupting and  re-starting
	 * symbol loading should change  anything about this fact,  since
	 * our  function only gets called once for any symbol (so-long as
	 * we  eventually indicate success to our caller), but just to be
	 * save about everything, also include handling for when `dip' is
	 * greater than any pre-existing MIP's DIP-field. */
	index = self->cm_mixed.mss_symc;
	if (index != 0) {
		mixed = &self->cm_mixed.mss_symv[index - 1];
		if unlikely(dip <= mixed->ms_dip) {
			/* Very unlikely: Must either insert somewhere in the middle,
			 * or  there  already  is  another  MIP  with  the  same DIP. */
			size_t lo, hi;
			lo = 0;
			hi = index;
			for (;;) {
				index = (lo + hi) / 2;
				if (lo >= hi)
					break;
				mixed = &self->cm_mixed.mss_symv[index];
				if (dip < mixed->ms_dip) {
					hi = index;
				} else if (dip > mixed->ms_dip) {
					lo = index + 1;
				} else if (sip < mixed->ms_sip) {
					hi = index;
				} else if (sip > mixed->ms_sip) {
					lo = index + 1;
				} else {
					/* Same field... (just re-use...) */
					sym->cms_dip = cmodsym_makemip(self, mixed);
					return DBX_EOK;
				}
			}
		}
	}

	/* Check if we need more memory to hold the complete mixed symbol table. */
	alloc = dbx_malloc_usable_size(self->cm_mixed.mss_symv) / sizeof(struct cmodmixsym);
	if (self->cm_mixed.mss_symc >= alloc) {
		/* Must allocate more space for mixed symbol information. */
		struct cmodmixsym *new_mixtab;
		size_t new_alloc = alloc * 2;
		if (new_alloc < 16)
			new_alloc = 16;
		new_mixtab = (struct cmodmixsym *)dbx_realloc(self->cm_mixed.mss_symv,
		                                              new_alloc *
		                                              sizeof(struct cmodmixsym));
		if unlikely(!new_mixtab) {
			new_alloc  = self->cm_mixed.mss_symc + 1;
			new_mixtab = (struct cmodmixsym *)dbx_realloc(self->cm_mixed.mss_symv,
			                                              new_alloc *
			                                              sizeof(struct cmodmixsym));
			if unlikely(!new_mixtab)
				return DBX_ENOMEM;
		}
		self->cm_mixed.mss_symv = new_mixtab;
	}

	/* Insert the new mixed symbol at `index' */
	if unlikely(index < self->cm_mixed.mss_symc) {
		/* Move up pre-existing symbols. */
		memmoveup(&self->cm_mixed.mss_symv[index + 1],
		          &self->cm_mixed.mss_symv[index],
		          self->cm_mixed.mss_symc - index,
		          sizeof(struct cmodmixsym));
		/* Relocate already-in-use MIP pointers from
		 * the   module's   global   symbol   table. */
		cmodule_relocate_mip_symbols_below(&self->cm_symbols,
		                                   index *
		                                   sizeof(struct cmodmixsym));
	}

	/* Fill in the new symbol. */
	mixed = &self->cm_mixed.mss_symv[index];
	mixed->ms_dip = dip;
	mixed->ms_sip = sip;

	/* Fill in the data-field of the symbol */
	sym->cms_dip = cmodsym_makemip(self, mixed);

	/* Account the of 1 additional mixed-symbol that we now have. */
	++self->cm_mixed.mss_symc;

	return DBX_EOK;
}


/* Try to evaluate the address of the symbol pointed-to by `dip'.
 *
 * Address information  is taken  from `.debug_info',  as pointed-to  by  `dip'.
 * Returns `false' is  no address  information is  available (which  may be  the
 * case  when  the associated  symbol is  actually a  constant), or  the address
 * cannot be calculated right now (i.e. the associated symbol is a TLS variable)
 * @return: * : One of `CMODULE_EVALUATE_SYMBOL_ADDRESS_*' */
#define CMODULE_EVALUATE_SYMBOL_ADDRESS_SUCCESS 0 /* Success (address was stored in `*pmodule_relative_addr') */
#define CMODULE_EVALUATE_SYMBOL_ADDRESS_NOADDR  1 /* Object doesn't have an address, or address calculation is too complex */
#define CMODULE_EVALUATE_SYMBOL_ADDRESS_EXTERN  2 /* Object doesn't have an address (according to .debug_info), but
                                                   * is declared as  externally visible, meaning  that its  address
                                                   * should be taken from some other source (such as .symtab) */
PRIVATE WUNUSED NONNULL((1, 2, 3, 4)) unsigned int
NOTHROW(FCALL cmodule_evaluate_symbol_address)(struct cmodule const *__restrict self,
                                               struct cmodunit const *__restrict cu,
                                               byte_t const *__restrict dip,
                                               uintptr_t *__restrict pmodule_relative_addr) {
	di_debuginfo_cu_parser_t parser;
	di_debuginfo_component_attrib_t attr;
	byte_t const *referenced_component;
	bool is_external = false;

	/* Load a parser for the given `dip'. */
again:
	cmodunit_parser_from_dip(cu, self, &parser, dip);

	/* Scan debug information attributes for  something
	 * that can tell us where the symbol is located at. */
	referenced_component = NULL;
	DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &parser) {
		switch (attr.dica_name) {

		case DW_AT_abstract_origin:
		case DW_AT_sibling:
		case DW_AT_specification:
			if (!debuginfo_cu_parser_getref(&parser, attr.dica_form,
			                                &referenced_component))
				referenced_component = NULL;
			break;

		case DW_AT_external:
			if (!debuginfo_cu_parser_getflag(&parser, attr.dica_form, &is_external))
				goto nope;
			break;

		case DW_AT_low_pc:
		case DW_AT_entry_pc:
			/* Directly load the encoded address constant. */
			if (debuginfo_cu_parser_getaddr(&parser, attr.dica_form,
			                                pmodule_relative_addr))
				return CMODULE_EVALUATE_SYMBOL_ADDRESS_SUCCESS;
			return CMODULE_EVALUATE_SYMBOL_ADDRESS_NOADDR;

		case DW_AT_location: {
			/* Alright,  so here we  have an actual location  expression. However, as complicated
			 * at that may appear at first glance, it all essentially boils down to only a single
			 * instruction,  as we're not allowed to have  address evaluation rely on any outside
			 * factors, such as register states.
			 * With this in mind, only 1-instruction expressions like the following are accepted:
			 *   >> DW_OP_addr 0x12345678
			 * Since this is the only way by  which the module's load-address would normally  end
			 * up being added to the calculated address. Furthermore, the DWARF specs  explicitly
			 * mention that only location expression  in this form can  appear in its version  of
			 * a  symbol name table  (DWARF5 .debug_names, which we  don't support because DWARF5
			 * is a mess of wastefully encoded debug information, and gcc still likes to generate
			 * DWARF4 by default)
			 *
			 * So in conclusion: Check that we're dealing with a 5/9-byte instruction where the
			 * first byte is the opcode of `DW_OP_addr' */
			di_debuginfo_location_t loc;
			size_t length;
			if unlikely(!debuginfo_cu_parser_getexpr(&parser, attr.dica_form, &loc))
				goto nope;
			if (!loc.l_expr || (loc.l_llist4 || loc.l_llist5))
				goto nope;
			length = (size_t)dwarf_decode_uleb128(&loc.l_expr);
			if (length != ((size_t)1 + parser.dsp_addrsize))
				goto nope;
			if (*loc.l_expr != DW_OP_addr)
				goto nope;
			++loc.l_expr;
			if (parser.dsp_addrsize == 4) {
				*pmodule_relative_addr = (uintptr_t)UNALIGNED_GET32((uint32_t const *)loc.l_expr);
			} else if (parser.dsp_addrsize == 8) {
				*pmodule_relative_addr = (uintptr_t)UNALIGNED_GET64((uint64_t const *)loc.l_expr);
			} else {
				goto nope;
			}
			return CMODULE_EVALUATE_SYMBOL_ADDRESS_SUCCESS;
		}	break;

		default:
			break;
		}
	}
	if (referenced_component) {
		if (dip == referenced_component)
			goto nope;
		/* Maybe we can find what we're looking for in here... */
		if (dbg_awaituser()) /* Allow the user to break an infinite loop caused by bad debug-info... */
			goto nope;
		dip = referenced_component;
		goto again;
	}
	if (is_external)
		return CMODULE_EVALUATE_SYMBOL_ADDRESS_EXTERN;
nope:
	return CMODULE_EVALUATE_SYMBOL_ADDRESS_NOADDR; /* Cannot load the actual symbol address! */
}


/* Register a symbol. If the symbol had already been registered,
 * then don't do anything (and return DBX_EOK).
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory. */
PRIVATE WUNUSED NONNULL((1, 2, 3, 4, 5)) dbx_errno_t
NOTHROW(FCALL cmodule_addsymbol)(struct cmodule *__restrict self,
                                 struct cmodsymtab *__restrict cu_symtab,
                                 struct cmodunit *__restrict cu,
                                 char const *__restrict name,
                                 byte_t const *__restrict dip,
                                 uintptr_t ns,
                                 bool has_location_information) {
	uintptr_t symbol_dip;
	size_t lo, hi, index;
	/* Construct the encoded DIP value for the symbol. */
	symbol_dip = cmodsym_makedip(self, dip, ns);
	/* Figure out where the symbol would need to go within the symtab of `self' */
	lo = 0;
	hi = self->cm_symbols.mst_symc;
	for (;;) {
		int cmp;
		struct cmodsym *sym;
		char const *symname;
		index = (lo + hi) / 2;
		if (lo >= hi)
			break;
		sym     = &self->cm_symbols.mst_symv[index];
		symname = cmodsym_name(sym, self);
		cmp     = strcmp(name, symname);
		if (cmp < 0) {
			hi = index;
		} else if (cmp > 0) {
			lo = index + 1;
		} else {
			/* Found  a  possible conflict.  For  this purpose,
			 * determine the range of symbols that share `name' */
			lo = hi = index;
			while (lo > 0 && strcmp(cmodsym_name(&self->cm_symbols.mst_symv[lo - 1], self), name) == 0)
				--lo;
			while (hi < self->cm_symbols.mst_symc - 1 &&
			       strcmp(cmodsym_name(&self->cm_symbols.mst_symv[hi + 1], self), name) == 0)
				++hi;
			/* Check if one of the pre-existing symbols uses the same namespace as we do. */
			for (index = lo; index <= hi; ++index) {
				sym = &self->cm_symbols.mst_symv[index];
				if (!same_namespace(sym->cms_dip, symbol_dip))
					continue; /* Different namespace. */
				/* This  is  either a  collision, or  a re-definition.
				 * We can determine the later by comparing DIP values. */
				if (sym->cms_dip == symbol_dip)
					return DBX_EOK; /* Same dip -> Redefinition (ignore silently) */
				if (ns == CMODSYM_DIP_NS_NORMAL) {
					if (cmodsym_ismip(sym)) {
						/* Already a mixed symbol... In  this case, check if the  debug
						 * information pointer of the pre-existing mixed symbol matches
						 * the pointer given to us by our caller.
						 *
						 * This can happen due to the symbol loading process  getting
						 * interrupted, and being restarted at a later point in time. */
						struct cmodmixsym const *mip;
						mip = cmodsym_getmip(sym, self);
						if (mip->ms_dip == dip)
							return DBX_EOK; /* Same dip -> Redefinition (ignore silently) */
					} else if (cmodsym_issip(sym) && ns == CMODSYM_DIP_NS_NORMAL) {
						CLinkerSymbol const *sip;
						uintptr_t dip_modrel_symaddr;
						uintptr_t sip_modrel_symaddr;
						unsigned int address_status;

						/* This is where it gets complicated, because we must decide on how
						 * we want to merge .debug_info with .symtab for a specific symbol:
						 *   - if  we don't have location info (!has_location_information)
						 *     then behavior is fairly straight-forward, as we simply have
						 *     to convert the symbol into `CMODSYM_DIP_NS_MIXED', at which
						 *     point it will pull type info from .debug_info, and location
						 *     info from .symtab
						 *   - If we do have location information, then we must try to calculate
						 *     the exact location:
						 *       - If we fail to calculate it, the location isn't an address, or
						 *         the location's address differs  from what .symtab is  saying,
						 *         then  we must add  the symbol as a  per-CU override, and mark
						 *         the  global symbol as standing in conflict (i.e. just do what
						 *         we'd normally do at this point)
						 *       - If  location informations match up, then we know that the 2
						 *         symbols reference the same entity, and we must forget about
						 *         ever having seen the symbol in .symtab */

						sip = cmodsym_getsip(sym, self);
						if (!has_location_information) {
							/* Create a mixed information symbol. */
create_mixed_symbol:
							return cmodule_make_symbol_mixed(self, sym, dip, sip);
						}
						/* Load the module-relative symbol-address `sip' */
						if (CLinkerSymbol_IsElf32(self)) {
							sip_modrel_symaddr = (uintptr_t)sip->cls_elf32.st_value;
						} else if (CLinkerSymbol_IsElf64(self)) {
							sip_modrel_symaddr = (uintptr_t)sip->cls_elf64.st_value;
						} else if (CLinkerSymbol_IsKern(self)) {
							sip_modrel_symaddr = (uintptr_t)sip->cls_kern.ks_addr;
						} else {
							goto fallback_insert_possible_collision;
						}

						/* Must deal with special case: gcc generates debug  information that  appears
						 *                              somewhat inconsistent with it self for `libc'.
						 *  - On the one hand, the following can be found in libc's .debug_info:
						 *    ```
						 *    <2><74389>: Abbrev Number: 33 (DW_TAG_variable)
						 *       <7438a>   DW_AT_name        : (indirect string, offset: 0x18916): __libm_Q
						 *       <7438e>   DW_AT_decl_file   : 15
						 *       <7438f>   DW_AT_decl_line   : 215
						 *       <74390>   DW_AT_decl_column : 1
						 *       <74391>   DW_AT_type        : <0x75bed>
						 *       <74395>   DW_AT_external    : 1
						 *       <74395>   DW_AT_declaration : 1
						 *       <74395>   DW_AT_const_value : 48 byte block: 0 0 0 0 0 0 f0 3f f4 10 11 11 11 11 a1 bf 85 55 fe 19 a0 1 5a 3f b7 db aa 9e 19 ce 14 bf 39 52 e6 86 ca cf d0 3e 2d c3 9 6e b7 fd 8a be
						 *    ```
						 *    That's  fine and all.  It's `__libm_tiny' is  a constant without any
						 *    address, and our parser is able to correctly load it and everything.
						 *
						 *  - However, there's also this entry from `.symtab':
						 *    ```
						 *    1425: 0009fd60    48 OBJECT  LOCAL  DEFAULT    4 __libm_Q
						 *    ```
						 *    And suddenly, the symbol `__libm_Q' is no longer a constant, but actually
						 *    has an address ????
						 *
						 * -> This in turn causes the below code to consider the .debug_info version of __libm_Q
						 *    as a per-CU override  for the initial declaration  taken from .symtab, which  then
						 *    results in the per-module global version of __libm_Q to remain loaded without  any
						 *    type information, also  causing any reference  to the  symbol to first  go to  the
						 *    global version, which then results in:
						 *    ```
						 *    !> eval __libm_Q
						 *    void:
						 *    (void)0
						 *    !> eval &__libm_Q
						 *    void *:
						 *    0xde1ed60 (libc.so!__libm_Q)
						 *    ```
						 *
						 * The solution chosen here is to interpret the combination of the `DW_AT_external'
						 * tag  with `DW_AT_const_value' as  special behavior to  construct a mixed symbol.
						 * After all: `DW_AT_external' means that the symbol  (should) be visible in other  CUs,
						 *            also meaning that such a symbol could never be considered as per-CU,  also
						 *            meaning that the symbol _must_ represent the symbol of the same name found
						 *            inside of the .symtab section.
						 */

						/* Evaluate the location expression from `dip' */
						address_status = cmodule_evaluate_symbol_address(self, cu, dip, &dip_modrel_symaddr);
						if (address_status == CMODULE_EVALUATE_SYMBOL_ADDRESS_NOADDR)
							goto fallback_insert_possible_collision;

						/* When `DW_AT_external' appeared, then create a mixed symbol, since this debug-info
						 * entry is referencing a symbol that would be visible from other CUs, and the stuff
						 * we've loaded from .symtab is used to indicate the same!
						 * For more information, see the explanation with `__libm_Q' as example above. */
						if (address_status == CMODULE_EVALUATE_SYMBOL_ADDRESS_EXTERN)
							goto create_mixed_symbol;

						/* Compare the location from `dip' with sip->[...].st_value */
						if (sip_modrel_symaddr != dip_modrel_symaddr)
							goto fallback_insert_possible_collision;

						/* We've  found the .debug_info entry for a symbol which we've previously
						 * only found inside of .symtab! Since the .debug_info entry contains the
						 * same location information as the info from .symtab, but in addition to
						 * this also contains type information, simply replace the  SYMTAB-symbol
						 * with its DEBUG_INFO-equivalent. */
						sym->cms_dip = symbol_dip;
						return DBX_EOK;
					}
				}
fallback_insert_possible_collision:
				if (!has_location_information) {
					return DBX_EOK; /* Without any location info, don't add this symbol!
					                 * HINT: Type symbols are cheaty  and claim to have  location
					                 *       info, so we don't need a special them for them here. */
				}
				/* TODO: If the new symbol has  the `DW_AT_external' flag set,  then
				 *       _it_ must become the globally visible symbol, replacing the
				 *       existing symbol, which must be moved into _its_  associated
				 *       CU, instead. */

				/* It's a collision!
				 * Mark the global symbol as such, and add
				 * the  new  symbol to  the  per-CU table. */
				sym->cms_dip |= CMODSYM_DIP_NS_FCONFLICT;
				/* Add the symbol to the per-CU table. */
				return cmodsymtab_addsymbol(cu_symtab, self, name, symbol_dip);
			}
			/* No   collision  (we're  dealing  with  differing  namespace)
			 * As such, simply insert the new symbol at the end of the list
			 * of other symbols that share the same name. */
			index = hi + 1;
			break;
		}
	}
	if (!has_location_information)
		return DBX_EOK; /* Without any location inf, don't add this symbol! */
	/* Simply insert the new symbol into the global symbol table under `index' */
	return cmodsymtab_insert_symbol(&self->cm_symbols, index, name, symbol_dip);
}


/* Check if `name' is a valid symbol name. */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL is_a_valid_symbol_name)(char const *__restrict name) {
	char ch = *name;
	if (!isalpha(ch) && ch != '_' && ch != '$')
		goto nope;
	++name;
	for (;;) {
		ch = *name;
		if (!ch)
			break;
		if (!isalnum(ch) && ch != '_' && ch != '$')
			goto nope;
		++name;
	}
	return true;
nope:
	return false;
}

/* Load DW symbols from the given unit `self'
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory.
 * @return: DBX_EINTR:  Operation was interrupted. */
PRIVATE WUNUSED NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL cmodunit_loadsyms)(struct cmodunit *__restrict self,
                                 struct cmodule *__restrict mod) {
	dbx_errno_t result;
	di_debuginfo_cu_parser_t parser;
	struct cmodsymtab percu_symbols;
	percu_symbols.mst_symc = 0;
	percu_symbols.mst_symv = NULL;

	/* Load a debug-info parser for the unit. */
	cmodunit_parser_from_dip(self, mod, &parser, NULL);

	for (;;) {
		byte_t const *dip;
		size_t cu_depth;
		/* Load the initial compile-unit container-tag. */
		for (;;) {
			debuginfo_cu_parser_skipattr(&parser);
			if (parser.dup_comp.dic_tag == DW_TAG_compile_unit)
				break;
			if (!debuginfo_cu_parser_next(&parser))
				goto done;
			if (dbg_awaituser())
				goto err_interrupt;
		}
		cu_depth = parser.dup_child_depth;
		dip      = parser.dsp_cu_info_pos;
		/* Scan the elements of the compilation-unit. */
		if (debuginfo_cu_parser_nextchild(&parser)) {
			do {
				uintptr_t ns;
				char const *symbol_name;
				bool has_location_information;
				if (dbg_awaituser())
					goto err_interrupt;
				symbol_name = parse_symbol_name_for_object(&parser, &ns, false,
				                                           &has_location_information);
				if (symbol_name && is_a_valid_symbol_name(symbol_name)) {
					/* Register this symbol. */
					result = cmodule_addsymbol(mod, &percu_symbols, self,
					                           symbol_name, dip, ns,
					                           has_location_information);
					if unlikely(result != DBX_EOK)
						goto err;
				}
				switch (parser.dup_comp.dic_tag) {

				case DW_TAG_enumeration_type:
				case DW_TAG_namespace:
					/* Allow looking inside of these tags for other global  names.
					 * This special distinction is  required since these types  of
					 * variables _are_ actually loaded as globals. (unlike symbols
					 * defined within  the bounds  of other  components, which  we
					 * consider to have local scoping) */
					if (!debuginfo_cu_parser_next_with_dip(&parser, &dip))
						goto done;
					break;

				default: {
					/* Scan ahead to the next component at our current level.
					 * This  way, we don't  accidentally load local variables
					 * as though they were globals. */
					size_t wanted_depth;
					wanted_depth = parser.dup_child_depth;
					for (;;) {
						if (!debuginfo_cu_parser_next_with_dip(&parser, &dip))
							goto done;
						if (parser.dup_child_depth <= wanted_depth)
							break;
						/* Skip attributes of this tag. */
						debuginfo_cu_parser_skipattr(&parser);
						if (dbg_awaituser())
							goto err_interrupt;
					}
				}	break;

				}
			} while (parser.dup_child_depth >= cu_depth);
		}
	}
done:
	/* Try to free unused memory. */
	if (!percu_symbols.mst_symc) {
		if (percu_symbols.mst_symv) {
			dbx_free(percu_symbols.mst_symv);
			percu_symbols.mst_symv = NULL;
		}
	} else {
		struct cmodsym *new_symtab;
		new_symtab = (struct cmodsym *)dbx_realloc(percu_symbols.mst_symv,
		                                           percu_symbols.mst_symc *
		                                           sizeof(struct cmodsym));
		if likely(new_symtab != NULL)
			percu_symbols.mst_symv = new_symtab;
	}
	/* Write-back the per-CU symbol table. */
	self->cu_symbols.mst_symc = percu_symbols.mst_symc;
	self->cu_symbols.mst_symv = percu_symbols.mst_symv;
	return DBX_EOK;
err_interrupt:
	result = DBX_EINTR;
err:
	dbx_free(percu_symbols.mst_symv);
	assert(self->cu_symbols.mst_symc == 0);
	assert(self->cu_symbols.mst_symv == (struct cmodsym *)-1);
	return result;
}

PRIVATE WUNUSED NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL cmodule_append_symtab_symbol)(struct cmodule const *__restrict self,
                                            struct cmodsymtab *__restrict symtab,
                                            uintptr_t symtab_symbol_offset,
                                            uintptr_t strtab_name_offset) {
	char const *name;
	dbx_errno_t result = DBX_EOK;
	/* Construct the actual symbol name. */
	name = (char const *)(self->cm_sections.ds_strtab_start +
	                      strtab_name_offset);
	/* Verify that the name is in-bounds. */
	if unlikely((byte_t const *)name < self->cm_sections.ds_strtab_start ||
	            (byte_t const *)name >= self->cm_sections.ds_strtab_end)
		goto done;
	/* Verify that the name is a valid symbol identifier. */
	if (!is_a_valid_symbol_name(name))
		goto done;
	/* All right! Let's add this symbol!
	 * Note that for this purpose, we use the `CMODSYM_DIP_NS_SYMTAB'
	 * namespace, thus indicating that the symbol data offset  points
	 * into the module's .symtab. */
	result = cmodsymtab_addsymbol(symtab, self, name,
	                              CMODSYM_DIP_NS_SYMTAB |
	                              symtab_symbol_offset);
done:
	return result;
}

/* Check if we care about symbol of type `typ' (one of `STT_*') */
PRIVATE ATTR_CONST WUNUSED bool
NOTHROW(FCALL cmodule_symtab_want_symbol_type)(unsigned int typ) {
	return typ == STT_OBJECT ||
	       typ == STT_FUNC;
}

PRIVATE WUNUSED NONNULL((1, 2, 3)) dbx_errno_t
NOTHROW(FCALL cmodule_load_symtab_elf32)(struct cmodule const *__restrict self,
                                         struct cmodsymtab *__restrict symtab,
                                         Elf32_Sym const *__restrict sym) {
	dbx_errno_t result = DBX_EOK;
	/* Check if we care about this symbol. */
	if (sym->st_shndx == SHN_UNDEF)
		goto done;
	if (!cmodule_symtab_want_symbol_type(ELF32_ST_TYPE(sym->st_info)))
		goto done;
	/* Actually add the symbol. */
	result = cmodule_append_symtab_symbol(self, symtab,
	                                      (byte_t const *)sym - self->cm_sections.ds_symtab_start,
	                                      sym->st_name);
done:
	return result;
}

PRIVATE WUNUSED NONNULL((1, 2, 3)) dbx_errno_t
NOTHROW(FCALL cmodule_load_symtab_elf64)(struct cmodule const *__restrict self,
                                         struct cmodsymtab *__restrict symtab,
                                         Elf64_Sym const *__restrict sym) {
	dbx_errno_t result = DBX_EOK;
	/* Check if we care about this symbol. */
	if (sym->st_shndx == SHN_UNDEF)
		goto done;
	if (!cmodule_symtab_want_symbol_type(ELF64_ST_TYPE(sym->st_info)))
		goto done;
	/* Actually add the symbol. */
	result = cmodule_append_symtab_symbol(self, symtab,
	                                      (byte_t const *)sym - self->cm_sections.ds_symtab_start,
	                                      sym->st_name);
done:
	return result;
}

#ifdef CMODSYM_NAME_NEEDS_MODULE
PRIVATE WUNUSED NONNULL((1, 2, 3)) dbx_errno_t
#else /* CMODSYM_NAME_NEEDS_MODULE */
PRIVATE WUNUSED NONNULL((1, 2)) dbx_errno_t
#define cmodule_load_symtab_kern(symtab, mod, sym) \
	cmodule_load_symtab_kern(symtab, sym)
#endif /* !CMODSYM_NAME_NEEDS_MODULE */
NOTHROW(FCALL cmodule_load_symtab_kern)(struct cmodsymtab *__restrict symtab,
#ifdef CMODSYM_NAME_NEEDS_MODULE
                                        struct cmodule *__restrict mod,
#endif /* CMODSYM_NAME_NEEDS_MODULE */
                                        struct kernel_syment const *__restrict sym) {
	uintptr_t symtab_offset;
	char const *name = sym->ks_name;
	if (!name)
		return DBX_EOK; /* Unused entry. */
	symtab_offset = (uintptr_t)sym - (uintptr_t)&kernel_symbol_table;
	return cmodsymtab_addsymbol(symtab, mod, sym->ks_name,
	                            CMODSYM_DIP_NS_SYMTAB |
	                            symtab_offset);
}



/* Load symbols from the  module's .dynsym section, where  associated
 * debug information is then generated by cross-referencing addresses
 * of dynamic symbols with addresses of symbols loaded above.
 *
 * This is required to properly deal with symbols exported by DEFINE_PUBLIC_ALIAS(),
 * since   those  symbols   have  PUBLIC   names  different   from  INTERNal  names.
 * Also: Any symbol we find that  doesn't have any associated debug  information
 *       should still be exposed as though it had void-typing (which is normally
 *       impossible)
 *
 * As such, debug information for dynamic symbols can be loaded lazily as
 * needed, so the initial loading of these symbols would still be  rather
 * quick.
 *
 * NOTE: As far as encoding of these symbols  goes, we could make use of  a
 *       separate namespace ID  `CMODSYM_DIP_NS_DYNSYM' that overlaps  with
 *       `CMODSYM_DIP_NS_NORMAL', similar to `CMODSYM_DIP_NS_TYPEDEF', thus
 *       making it possible to identify these modules.
 *       The remainder of the DIP pointer could then be an offset into the
 *       module's  `.dynsym' section, towards the correct `Elf[32|64]_Sym'
 *       structure, and the name field would be a pointer into the .dynstr
 *       section.
 * NOTE: .symtab and .strtab is loaded/scanned similarly, and is  actually
 *       preferred over .dynsym (though only the later may be available if
 *       the module had been stripped of debug information)
 *
 * NOTE: This kind of symbol scanning must be done before loading .debug_info
 *       symbol data, such  that references to  symbols without any  location
 *       information  can  automatically have  their location  substituted by
 *       info from .dynsym and .symtab! */
PRIVATE WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cmodule_load_symtab_symbols)(struct cmodule *__restrict self) {
	dbx_errno_t error;
	struct cmodsymtab symtab;
	symtab.mst_symc = 0;
	symtab.mst_symv = NULL;
	/* Check for special case: Load kernel core symbols. */
	if (CLinkerSymbol_IsKern(self)) {
		size_t i;
		for (i = 0; i <= kernel_symbol_table.ds_mask; ++i) {
			error = cmodule_load_symtab_kern(&symtab, self,
			                                 &kernel_symbol_table.ds_list[i]);
			if unlikely(error != DBX_EOK)
				goto err;
			if (dbg_awaituser())
				goto err_intr;
		}
	} else {
		/* Quick check: Do we even have a .symtab / .strtab section?, and
		 *              if so: do we  recognize the .symtab entity  size? */
		if (self->cm_sections.ds_symtab_start >= self->cm_sections.ds_symtab_end)
			goto done; /* No .symtab / .dynsym */
		if (self->cm_sections.ds_strtab_start >= self->cm_sections.ds_strtab_end)
			goto done; /* No .strtab / .dynstr */
		if (CLinkerSymbol_IsElf32(self)) {
			Elf32_Sym const *iter, *end;
			iter = (Elf32_Sym const *)self->cm_sections.ds_symtab_start;
			end  = (Elf32_Sym const *)(self->cm_sections.ds_symtab_end - (sizeof(Elf32_Sym) - 1));
			for (; iter < end; ++iter) {
				error = cmodule_load_symtab_elf32(self, &symtab, iter);
				if unlikely(error != DBX_EOK)
					goto err;
				if (dbg_awaituser())
					goto err_intr;
			}
		} else if (CLinkerSymbol_IsElf64(self)) {
			Elf64_Sym const *iter, *end;
			iter = (Elf64_Sym const *)self->cm_sections.ds_symtab_start;
			end  = (Elf64_Sym const *)(self->cm_sections.ds_symtab_end - (sizeof(Elf64_Sym) - 1));
			for (; iter < end; ++iter) {
				error = cmodule_load_symtab_elf64(self, &symtab, iter);
				if unlikely(error != DBX_EOK)
					goto err;
				if (dbg_awaituser())
					goto err_intr;
			}
		}
	}
	/* Write-back   the  initial  symbol   table  of  .symtab  symbols.
	 * NOTE: We do this after having fully loaded .symtab for  symbols,
	 * so-as to allow `dbg_awaituser()' to interrupt the process before
	 * it would be finished. */
	self->cm_symbols.mst_symc = symtab.mst_symc;
	self->cm_symbols.mst_symv = symtab.mst_symv; /* Inherit data */
done:
	return DBX_EOK;
err_intr:
	error = DBX_EINTR;
err:
	dbx_free(symtab.mst_symv);
	return error;
}


/* Load  debug  symbols for  the give  CModule.  Since doing  this may
 * take  quite  a while,  this  function is  equipped  to make  use of
 * `dbg_awaituser()' to  allow it  to be  interrupted prior  to  being
 * completed. If this happens, then this function returns `DBX_EINTR',
 * and the caller must assume that  not all symbols have been  loaded.
 * In  this case,  the caller is  allowed to continue  as through that
 * the  symbol  they were  looking for  doesn't  exist, or  no symbols
 * exist at all.
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory.
 * @return: DBX_EINTR:  Operation was interrupted. */
PUBLIC WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cmodule_loadsyms)(struct cmodule *__restrict self) {
	dbx_errno_t result = DBX_EOK;
	/* Quick check: have symbols already been loaded. */
	if (unlikely(!self->cm_cuc) ||
	    self->cm_cuv[self->cm_cuc - 1].cu_symbols.mst_symv != (struct cmodsym *)-1) {
		/* Everything's already loaded! */
	} else {
		size_t i;
		if (!self->cm_symbols.mst_symc) {
			/* No symbols have been loaded, yet.
			 * With this in mind, try to load typeless symbol data from  .symtab
			 * first, so we can unify that information with additional data from
			 * .debug_info down below. */
			result = cmodule_load_symtab_symbols(self);
			if unlikely(result != DBX_EOK)
				goto done;
		}
		for (i = 0; i < self->cm_cuc; ++i) {
			struct cmodunit *cu;
			cu = &self->cm_cuv[i];
			/* Check if symbols from this CU have already been loaded. */
			if (cu->cu_symbols.mst_symv != (struct cmodsym *)-1)
				continue;
			/* Actually load symbols for this unit. */
			result = cmodunit_loadsyms(cu, self);
			if unlikely(result != DBX_EOK)
				break;
		}
		/* Try to release unused memory from the global symbol table. */
		if unlikely(!self->cm_symbols.mst_symc) {
			if (self->cm_symbols.mst_symv) {
				dbx_free(self->cm_symbols.mst_symv);
				self->cm_symbols.mst_symv = NULL;
			}
		} else {
			struct cmodsym *new_symtab;
			new_symtab = (struct cmodsym *)dbx_realloc(self->cm_symbols.mst_symv,
			                                           self->cm_symbols.mst_symc *
			                                           sizeof(struct cmodsym));
			if likely(new_symtab)
				self->cm_symbols.mst_symv = new_symtab;
		}
		/* Also try to release unused memory from the mixed symbol table. */
		if unlikely(!self->cm_mixed.mss_symc) {
			if (self->cm_mixed.mss_symv) {
				dbx_free(self->cm_mixed.mss_symv);
				self->cm_mixed.mss_symv = NULL;
			}
		} else {
			struct cmodmixsym *new_mixtab;
			new_mixtab = (struct cmodmixsym *)dbx_realloc(self->cm_mixed.mss_symv,
			                                              self->cm_mixed.mss_symc *
			                                              sizeof(struct cmodmixsym));
			if likely(new_mixtab)
				self->cm_mixed.mss_symv = new_mixtab;
		}
	}
done:
	return result;
}

/* Lookup the a symbol within  `self', given its `name'. If  debug
 * symbols  had yet to  be loaded, then this  function will make a
 * call to `cmodule_loadsyms()'. If that call fails, this function
 * will simply return `NULL'.
 * To do its job, this function  will first look at the  per-module
 * symbol table of `self' (iow: `self->cm_symbols'). If this  table
 * contains a symbol matching `name', that symbol is then returned,
 * unless it has the `CMODSYM_DIP_NS_FCONFLICT' flag set, in  which
 * case `dbg_getpcreg(DBG_RT_REGLEVEL_VIEW)' is  checked for  being
 * apart of `self'. If  it is, try to  find the CU associated  with
 * that address. If such a CU exists, check that CU's symbol  table
 * for `name' once again. If  that table contains the given  `name'
 * also,  return  that  symbol.  Otherwise  (if  any  of  the above
 * failed), simply  return  the  symbol already  found  within  the
 * module's global symbol table.
 * @param: ns: When different from `CMODSYM_DIP_NS_NORMAL',  restrict
 *             the search to only  return symbols from the  indicated
 *             namespace. Otherwise, ~try~ to return symbols from the
 *             given namespace, but when (at least 1) symbol is found
 *             that is apart  of a different  namespace, return  that
 *             symbol instead. */
PUBLIC WUNUSED NONNULL((1, 2)) struct cmodsym const *
NOTHROW(FCALL cmodule_getsym)(struct cmodule *__restrict self,
                              char const *__restrict name,
                              size_t namelen, uintptr_t ns) {
	struct cmodsym const *result;

	/* First up: Make sure that module symbols have been loaded. */
	if (cmodule_loadsyms(self) != DBX_EOK)
		return NULL;

	/* Now check the per-module (global) symbol table for `name' */
	result = cmodsymtab_lookup(&self->cm_symbols, self, name, namelen, ns);

	/* Check  if  the  symbol  we've  found  is  in  conflict  with other,
	 * per-CU symbols. If this is the case, then we must lookup the symbol
	 * once again within the table associated with the currently viewed PC
	 * pointer,  as   returned   by   `dbg_getpcreg(DBG_RT_REGLEVEL_VIEW)' */
	if (result && (cmodsym_getns(result) & CMODSYM_DIP_NS_FCONFLICT)) {
		void const *pc;
		pc = dbg_getpcreg(DBG_RT_REGLEVEL_VIEW);
		if ((byte_t const *)pc >= cmodule_getloadmin(self) &&
		    (byte_t const *)pc <= cmodule_getloadmax(self)) {
			uintptr_t module_relative_pc;
			struct cmodunit *cu;
			module_relative_pc = (uintptr_t)pc - cmodule_getloadaddr(self);
			cu = cmodule_findunit_from_pc(self, module_relative_pc);
			if (cu != NULL) {
				struct cmodsym const *cu_symbol;
				cu_symbol = cmodsymtab_lookup(&cu->cu_symbols, self, name, namelen, ns);
				if (cu_symbol != NULL)
					return cu_symbol;
			}
		}
	}
	return result;
}



struct cmodule_getsym_global_data {
	struct cmodsym const *result;
	char const           *name;
	size_t                namelen;
	REF struct cmodule  **presult_module;
	uintptr_t             ns;
};

PRIVATE NONNULL((2)) ssize_t
NOTHROW(FCALL cmodule_getsym_global_callback)(void *cookie,
                                              struct cmodule *__restrict mod) {
	struct cmodsym const *sym;
	struct cmodule_getsym_global_data *arg;
	arg = (struct cmodule_getsym_global_data *)cookie;
	/* Lookup a symbol within the given `mod' */
	sym = cmodule_getsym(mod, arg->name, arg->namelen, arg->ns);
	if (sym != NULL) {
		/* Found it! (write-back results) */
		*arg->presult_module = incref(mod);
		arg->result          = sym;
		return -0xffff; /* Stop enumeration */
	}
	return 0;
}


/* Resolve a global symbol by finding its containing module, and returning
 * a pointer to the associated symbol object. This function is implemented
 * as a combination of `cmodule_enum()' + `cmodule_getsym()', meaning that
 * symbol resolution order matches what is done by `cmodule_enum()'
 * @return: * :   Success. (`*presult_module' was populated with a reference)
 * @return: NULL: Error: Insufficient memory.
 * @return: NULL: Error: No such symbol.
 * @return: NULL: Error: Operation was interrupted. */
PUBLIC WUNUSED NONNULL((1, 3)) struct cmodsym const *
NOTHROW(FCALL cmodule_getsym_global)(char const *__restrict name, size_t namelen,
                                     REF struct cmodule **__restrict presult_module,
                                     uintptr_t ns) {
	struct cmodule_getsym_global_data data;
	data.result         = NULL;
	data.name           = name;
	data.namelen        = namelen;
	data.presult_module = presult_module;
	data.ns             = ns;
	cmodule_enum(&cmodule_getsym_global_callback, &data);
	return data.result;
}


/* Same as `cmodule_getsym_global()',  but search for  symbols starting  with
 * `start_module', and continuing the search within related modules. For this
 * purpose,  start by searching `start_module' itself, and moving on to other
 * modules within its address space, before finally search through modules in
 * different address spaces. */
PUBLIC WUNUSED NONNULL((2, 4)) struct cmodsym const *
NOTHROW(FCALL cmodule_getsym_withhint)(struct cmodule *start_module,
                                       char const *__restrict name, size_t namelen,
                                       REF struct cmodule **__restrict presult_module,
                                       uintptr_t ns) {
	struct cmodule_getsym_global_data data;
	data.result         = NULL;
	data.name           = name;
	data.namelen        = namelen;
	data.presult_module = presult_module;
	data.ns             = ns;
	cmodule_enum_with_hint(start_module, &cmodule_getsym_global_callback, &data);
	return data.result;
}




/* Initialize a debug information CU parser to load debug information for a
 * component located at `dip' within  the `.debug_info' mapping of  `self'.
 * For this purpose, this function will locate the CU that contains  `dip',
 * and proceed to call `cmodunit_parser()'  to initialize `result'. If  the
 * given `dip' is not apart of any of the CUs of `self', then `result' will
 * be initialized to always indicate EOF.
 * @param: dip: DebugInfoPointer. (s.a. `cmodunit_parser_from_dip()') */
PUBLIC NONNULL((1, 2, 3)) void
NOTHROW(FCALL cmodule_parser_from_dip)(struct cmodule const *__restrict self,
                                       di_debuginfo_cu_parser_t *__restrict result,
                                       byte_t const *__restrict dip) {
	struct cmodunit *cu;
	/* Try to find the CU associated with `dip' */
	cu = cmodule_findunit_from_dip(self, dip);
	if unlikely(!cu) {
		/* Special case: Bad DIP pointer. */
		bzero(result, sizeof(*result));
		return;
	}
	/* Initialize the parser from `cu' and `dip'. */
	cmodunit_parser_from_dip(cu, self, result, dip);
}


PRIVATE ATTR_NOINLINE WUNUSED NONNULL((1)) struct cmodunit *
NOTHROW(FCALL cmodule_findunit_from_pc_fallback)(struct cmodule const *__restrict self,
                                                 uintptr_t module_relative_pc) {
	size_t i;
	/* Fallback: Manually search through all  CUs and find one  that
	 *           has a `DW_TAG_compile_unit' with a range-list which
	 *           in turn contains `module_relative_pc' */
	for (i = 0; i < self->cm_cuc; ++i) {
		debuginfo_errno_t error;
		di_debuginfo_cu_parser_t parser;
		di_debuginfo_compile_unit_simple_t cu;
		cmodunit_parser_from_dip(&self->cm_cuv[i], self, &parser, NULL);
		/* Find the nearest CU. */
		while (parser.dup_comp.dic_tag != DW_TAG_compile_unit) {
			debuginfo_cu_parser_skipattr(&parser);
			if (!debuginfo_cu_parser_next(&parser))
				goto next_cu;
		}
		/* Load attributes of this CU. */
		if (!debuginfo_cu_parser_loadattr_compile_unit_simple(&parser, &cu))
			goto next_cu;
		/* Check if the given `module_relative_pc' is contained by this CU. */
		error = debuginfo_rnglists_contains(&cu.cu_ranges, &parser, cu.cu_ranges.r_startpc, module_relative_pc,
		                                  di_debug_sections_as_di_rnglists_sections(&self->cm_sections));
		if (error == DEBUG_INFO_ERROR_SUCCESS)
			return (struct cmodunit *)&self->cm_cuv[i]; /* Found it! */
next_cu:
		;
	}
	return NULL;
}

/* Try to find the compilation unit that contains `module_relative_pc'
 * If  no such unit  can be located, `NULL'  will be returned instead. */
PUBLIC WUNUSED NONNULL((1)) struct cmodunit *
NOTHROW(FCALL cmodule_findunit_from_pc)(struct cmodule const *__restrict self,
                                        uintptr_t module_relative_pc) {
	struct cmodunit *result;
	/* Try to make use of .debug_aranges to find the proper CU. */
	if (self->cm_sections.ds_debug_aranges_start < self->cm_sections.ds_debug_aranges_end) {
		uintptr_t debuginfo_cu_offset;
		debuginfo_errno_t error;
		error = debugaranges_locate(self->cm_sections.ds_debug_aranges_start,
		                            self->cm_sections.ds_debug_aranges_end,
		                            &debuginfo_cu_offset,
		                            module_relative_pc);
		if (error == DEBUG_INFO_ERROR_SUCCESS) {
			byte_t const *cu_start;
			cu_start = self->cm_sections.ds_debug_info_start + debuginfo_cu_offset;
			result   = cmodule_findunit_from_dip(self, cu_start);
			if (result != NULL)
				goto done;
		}
	}
	/* Fallback */
	result = cmodule_findunit_from_pc_fallback(self, module_relative_pc);
done:
	return result;
}


/* Try  to   find  the   compilation  unit   that  contains   `dip'
 * If no such unit can be located, `NULL' will be returned instead. */
PUBLIC ATTR_PURE WUNUSED NONNULL((1)) struct cmodunit *
NOTHROW(FCALL cmodule_findunit_from_dip)(struct cmodule const *__restrict self,
                                         byte_t const *__restrict dip) {
	struct cmodunit const *result;
	size_t lo, hi;
	lo = 0, hi = self->cm_cuc;
	while (lo < hi) {
		size_t index;
		index  = (lo + hi) / 2;
		result = &self->cm_cuv[index];
		if (dip < cmodunit_di_start(result)) {
			hi = index;
		} else if (dip >= cmodunit_di_maxend(result)) {
			lo = index + 1;
		} else {
			/* Found it! */
			return (struct cmodunit *)result;
		}
	}
	return NULL;
}













/************************************************************************/
/* Mixed global/local symbol enumeration/lookup functions               */
/************************************************************************/

struct cmodsyminfo_lookup_data {
	struct cmodsyminfo info;
	size_t             namelen;
	dbx_errno_t        error;
};

PRIVATE NONNULL((1)) ssize_t
NOTHROW(FCALL cmodsyminfo_lookup_cb)(struct cmodsyminfo *__restrict info,
                                     bool info_loaded) {
	struct cmodsyminfo_lookup_data *arg;
	arg = container_of(info, struct cmodsyminfo_lookup_data, info);
	if (strlen(cmodsyminfo_name(info)) != arg->namelen)
		return 0; /* Not actually our symbol. - it's name just starts with our name as prefix. */
	/* Found it! - Make sure that extended symbol information has been loaded. */
	if (!info_loaded)
		cmod_symenum_loadinfo(info);
	arg->error = DBX_EOK; /* Indicate success */
	return -0xffff;       /* Stop enumeration */
}


/* Lookup information about a local/global symbol matching the given name.
 * @param: info: [in]  The caller must fill in `clv_mod', `clv_unit' and `clv_modrel_pc'
 *                     NOTE: If not available, you may fill `clv_mod' and `clv_unit' with
 *                           `NULL', and leave `clv_modrel_pc' undefined.
 *               [out] Upon success, all non-[const] fields may have been modified.
 * @param: name: The symbol name that should be searched for.
 * @param: ns:   Symbol namespace (one of `CMODSYM_DIP_NS_*')
 * @return: DBX_EOK:    Success
 * @return: DBX_ENOENT: No local variable `name' exists at `module_relative_pc'
 * @return: DBX_EINTR:  Operation was interrupted. */
PUBLIC NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL cmod_syminfo)(/*in|out*/ struct cmodsyminfo *__restrict info,
                            char const *__restrict name, size_t namelen,
                            uintptr_t ns) {
	/* Implement the symbol-lookup function in terms of the symbol enumeration function. */
	struct cmodsyminfo_lookup_data data;
	ssize_t error;
	/* Copy fields that the caller was supposed to initialize. */
	data.info.clv_mod       = xincref(info->clv_mod);
	data.info.clv_unit      = info->clv_unit;
	data.info.clv_modrel_pc = info->clv_modrel_pc;
	/* Set the default DBX error code. */
	data.error   = DBX_ENOENT;
	data.namelen = namelen;
	/* Enumerate  symbols  with  the  help  enumeration  function. Note
	 * that we  pass  the  given  `name'  as  startswith-request,  such
	 * that only strings that being with the given name are enumerated.
	 * We then  further restrict  enumeration  within our  callback  by
	 * requiring that the name of the  symbol we actually end up  using
	 * has a length that is identical to `namelen' */
	error = cmod_symenum(&data.info, &cmodsyminfo_lookup_cb,
	                     name, namelen,
	                     ns, CMOD_SYMENUM_SCOPE_FNORMAL);
	/* Done. However, on success, we must write-back the actual symbol information. */
	if (data.error == DBX_EOK) {
		xdecref(info->clv_mod); /* Drop the caller's original reference to their entry module. */
		/* Copy over new information (note that this also causes the
		 * reference from `data.info.clv_mod' to be inherited by the
		 * caller) */
		memcpy(info, &data.info, sizeof(struct cmodsyminfo));
	} else if (error < 0 && error != -0xffff) {
		/* Custom  error code override  (e.g. `DBX_EINTR' or `DBX_ENOMEM').
		 * In general, these errors all originate from `cmodule_loadsyms()' */
		data.error = error;
	}
	return data.error;
}

/* Same as `cmod_syminfo()', but  the caller is not  required to fill in  information
 * about  any symbol at  all, which are automatically  loaded based on `dbg_current',
 * as well as `dbg_getpcreg(DBG_RT_REGLEVEL_VIEW)'. However, upon success, the caller
 * is  required  to  call `cmod_syminfo_local_fini(info)'  once  returned information
 * is no longer being used.
 * @param: ns: Symbol namespace (one of `CMODSYM_DIP_NS_*')
 * @return: DBX_EOK:    Success
 * @return: DBX_ENOENT: No local variable `name' exists at `module_relative_pc'
 * @return: DBX_EINTR:  Operation was interrupted. */
PUBLIC NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL cmod_syminfo_local)(/*out*/ struct cmodsyminfo *__restrict info,
                                  char const *__restrict name, size_t namelen,
                                  uintptr_t ns) {
	void const *pc;
	dbx_errno_t result;
	pc = dbg_getpcreg(DBG_RT_REGLEVEL_VIEW);
	/* Lookup the module that contains `pc' */
	info->clv_mod = cmodule_ataddr(pc);
	if (info->clv_mod) {
		info->clv_modrel_pc = (uintptr_t)pc - cmodule_getloadaddr(info->clv_mod);
		info->clv_unit      = cmodule_findunit_from_pc(info->clv_mod, info->clv_modrel_pc);
		if unlikely(!info->clv_unit) {
			decref(info->clv_mod);
			info->clv_mod = NULL;
		}
	}
	/* Lookup the symbol. */
	result = cmod_syminfo(info, name, namelen, ns);
	if (result != DBX_EOK && info->clv_mod) {
		decref(info->clv_mod); /* Cleanup */
		info->clv_mod = NULL;  /* Shouldn't be necessary, but better be careful... */
	}
	return result;
}



PRIVATE NONNULL((1, 2)) void
NOTHROW(FCALL loadinfo_location)(di_debuginfo_cu_parser_t const *__restrict parser,
                                 struct cmodsyminfo *__restrict info,
                                 uintptr_t form) {
	if unlikely(!debuginfo_cu_parser_getexpr(parser, form, &info->clv_data.s_var.v_location))
		bzero(&info->clv_data.s_var.v_location, sizeof(info->clv_data.s_var.v_location));
}

PRIVATE NONNULL((1, 2, 4)) void
NOTHROW(FCALL loadinfo_const_value)(di_debuginfo_cu_parser_t const *__restrict parser,
                                    struct cmodsyminfo *__restrict info,
                                    uintptr_t form, byte_t const *__restrict attr_reader) {
	uintptr_t value;
	di_debuginfo_block_t block;
	if (debuginfo_cu_parser_getconst(parser, form, &value, attr_reader)) {
		info->clv_data.s_var.v_objaddr = info->clv_data.s_var._v_objdata;
		UNALIGNED_SET((uintptr_t *)info->clv_data.s_var._v_objdata, value);
	} else if (debuginfo_cu_parser_getblock(parser, form, &block)) {
		info->clv_data.s_var.v_objaddr = (void *)block.b_addr;
	} else {
		printk(KERN_WARNING "[dbx] Unable to decode form %" PRIxPTR " of DW_AT_const_value\n",
		       form);
	}
}

PRIVATE NONNULL((1, 2)) void
NOTHROW(FCALL loadinfo_type)(di_debuginfo_cu_parser_t const *__restrict parser,
                             struct cmodsyminfo *__restrict info,
                             uintptr_t form) {
	if unlikely(!debuginfo_cu_parser_getref(parser, form, &info->clv_data.s_var.v_typeinfo))
		info->clv_data.s_var.v_typeinfo = NULL;
}

PRIVATE ATTR_NOINLINE NONNULL((1, 2)) void
NOTHROW(FCALL loadinfo_specifications)(struct cmodsyminfo *__restrict info,
                                       byte_t const *__restrict specification,
                                       bool has_object_address) {
	di_debuginfo_cu_parser_t inner_parser;
	di_debuginfo_component_attrib_t attr;
	memcpy(&inner_parser, &info->clv_parser, sizeof(inner_parser));
	inner_parser.dsp_cu_info_pos = specification;
again:
	if (debuginfo_cu_parser_next(&inner_parser)) {
		if (inner_parser.dup_comp.dic_tag == DW_TAG_variable ||
		    inner_parser.dup_comp.dic_tag == DW_TAG_constant ||
		    inner_parser.dup_comp.dic_tag == DW_TAG_enumerator ||
		    inner_parser.dup_comp.dic_tag == DW_TAG_subprogram) {
			DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &inner_parser) {
				switch (attr.dica_name) {

				case DW_AT_abstract_origin: {
					byte_t const *abstract_origin;
					/* Load data from the pointed-to location. */
					if unlikely(!debuginfo_cu_parser_getref(&inner_parser, attr.dica_form,
					                                        &abstract_origin))
						return;
					if (dbg_awaituser()) /* Allow the user to break an infinite loop caused by bad debug-info... */
						return;
					inner_parser.dsp_cu_info_pos = abstract_origin;
					goto again;
				}	break;

				case DW_AT_type:
					loadinfo_type(&inner_parser, info, attr.dica_form);
					break;

				case DW_AT_location:
					if (!has_object_address)
						loadinfo_location(&inner_parser, info, attr.dica_form);
					break;

				case DW_AT_const_value:
					if (!has_object_address)
						loadinfo_const_value(&inner_parser, info, attr.dica_form, _attr_reader);
					break;

				default:
					break;
				}
			}
		}
	}
}


/* Parse attributes of the currently selected component to figure out
 * if that object is located at the given `module_relative_addr'.  If
 * it is, then immediately stop parsing and return `true'. Otherwise,
 * parse all attributes and eventually return `false' */
PRIVATE NONNULL((1)) bool
NOTHROW(FCALL parser_check_object_has_address)(di_debuginfo_cu_parser_t *__restrict parser,
                                               uintptr_t module_relative_addr) {
	byte_t const *referenced_component;
	di_debuginfo_cu_parser_t _inner_parser;
	di_debuginfo_component_attrib_t attr;
	bool has_location;
	has_location = false;
again:
	referenced_component = NULL;
	DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, parser) {
		switch (attr.dica_name) {

		case DW_AT_abstract_origin:
		case DW_AT_sibling:
		case DW_AT_specification:
			if (!debuginfo_cu_parser_getref(parser, attr.dica_form,
			                                &referenced_component))
				referenced_component = NULL;
			break;

		case DW_AT_low_pc:
		case DW_AT_entry_pc: {
			uintptr_t module_relative_component_addr;
			/* Directly load the encoded address constant. */
			if (debuginfo_cu_parser_getaddr(parser, attr.dica_form,
				                            &module_relative_component_addr) &&
				module_relative_component_addr == module_relative_addr)
				return true; /* Found it! */
			has_location = true;
		}	break;

		case DW_AT_location: {
			/* Alright,  so here we  have an actual location  expression. However, as complicated
			 * at that may appear at first glance, it all essentially boils down to only a single
			 * instruction,  as we're not allowed to have  address evaluation rely on any outside
			 * factors, such as register states.
			 * With this in mind, only 1-instruction expressions like the following are accepted:
			 *   >> DW_OP_addr 0x12345678
			 * Since this is the only way by  which the module's load-address would normally  end
			 * up being added to the calculated address. Furthermore, the DWARF specs  explicitly
			 * mention that only location expression  in this form can  appear in its version  of
			 * a  symbol name table  (DWARF5 .debug_names, which we  don't support because DWARF5
			 * is a mess of wastefully encoded debug information, and gcc still likes to generate
			 * DWARF4 by default)
			 *
			 * So in conclusion: Check that we're dealing with a 5/9-byte instruction where the
			 * first byte is the opcode of `DW_OP_addr' */
			di_debuginfo_location_t loc;
			uintptr_t module_relative_component_addr;
			size_t length;
			if unlikely(!debuginfo_cu_parser_getexpr(parser, attr.dica_form, &loc))
				break;
			if (!loc.l_expr || (loc.l_llist4 || loc.l_llist5))
				break;
			length = (size_t)dwarf_decode_uleb128(&loc.l_expr);
			if (length != ((size_t)1 + parser->dsp_addrsize))
				break;
			if (*loc.l_expr != DW_OP_addr)
				break;
			++loc.l_expr;
			if (parser->dsp_addrsize == 4) {
				module_relative_component_addr = (uintptr_t)UNALIGNED_GET32((uint32_t const *)loc.l_expr);
			} else if (parser->dsp_addrsize == 8) {
				module_relative_component_addr = (uintptr_t)UNALIGNED_GET64((uint64_t const *)loc.l_expr);
			} else {
				break;
			}
			if (module_relative_component_addr == module_relative_addr)
				return true; /* Found it! */
			has_location = true;
		}	break;

		default:
			break;
		}
	}
	if (referenced_component && !has_location) {
		/* Maybe we can find what we're looking for in here... */
		if (dbg_awaituser()) /* Allow the user to break an infinite loop caused by bad debug-info... */
			goto done;
		if (parser != &_inner_parser) {
			memcpy(&_inner_parser, parser, sizeof(*parser));
			parser = &_inner_parser;
		}
		parser->dsp_cu_info_pos = referenced_component;
		if (debuginfo_cu_parser_next(&_inner_parser))
			goto again;
	}
done:
	return false;
}


/* Scan  (using the  already-initialized parser  of `info')  the current CU
 * for a symbol that has a starting address equal to `module_relative_addr'
 * Once found,  store information  about  that symbol  in  `info->clv_data'
 * If found, return the DIP for that object. Otherwise, return `NULL' */
PRIVATE NONNULL((1)) byte_t const *
NOTHROW(FCALL cmod_symenum_search_for_address)(struct cmodsyminfo *__restrict info,
                                               uintptr_t module_relative_addr) {
	for (;;) {
		byte_t const *dip;
		size_t cu_depth;
		/* Load the initial compile-unit container-tag. */
		cu_depth = info->clv_parser.dup_child_depth;
		dip      = info->clv_parser.dsp_cu_info_pos;
		/* Scan the elements of the compilation-unit. */
		if (debuginfo_cu_parser_nextchild(&info->clv_parser)) {
			do {
				if (dbg_awaituser())
					goto done;
				/* Restrict address lookup search to components that could feasibly be addressable. */
				if (info->clv_parser.dup_comp.dic_tag == DW_TAG_subprogram ||
				    info->clv_parser.dup_comp.dic_tag == DW_TAG_label ||
				    info->clv_parser.dup_comp.dic_tag == DW_TAG_variable ||
				    info->clv_parser.dup_comp.dic_tag == DW_TAG_constant ||
				    info->clv_parser.dup_comp.dic_tag == DW_TAG_enumerator) {
					/* Parse attributes of  the current component  to check if  this
					 * component points at an object that matches the given address. */
					if (parser_check_object_has_address(&info->clv_parser, module_relative_addr))
						return dip; /* Found it! */
				} else {
					debuginfo_cu_parser_skipattr(&info->clv_parser);
				}
				switch (info->clv_parser.dup_comp.dic_tag) {

				case DW_TAG_enumeration_type:
				case DW_TAG_namespace:
					/* Allow looking inside of these tags for other global  names.
					 * This special distinction is  required since these types  of
					 * variables _are_ actually loaded as globals. (unlike symbols
					 * defined within  the bounds  of other  components, which  we
					 * consider to have local scoping) */
					if (!debuginfo_cu_parser_next_with_dip(&info->clv_parser, &dip))
						goto done;
					break;

				default: {
					/* Scan ahead to the next component at our current level.
					 * This  way, we don't  accidentally load local variables
					 * as though they were globals. */
					size_t wanted_depth;
					wanted_depth = info->clv_parser.dup_child_depth;
					for (;;) {
						if (!debuginfo_cu_parser_next_with_dip(&info->clv_parser, &dip))
							goto done;
						if (info->clv_parser.dup_child_depth <= wanted_depth)
							break;
						/* Skip attributes of this tag. */
						debuginfo_cu_parser_skipattr(&info->clv_parser);
						if (dbg_awaituser())
							goto done;
					}
				}	break;

				}
			} while (info->clv_parser.dup_child_depth >= cu_depth);
		}
		for (;;) {
			debuginfo_cu_parser_skipattr(&info->clv_parser);
			if (info->clv_parser.dup_comp.dic_tag == DW_TAG_compile_unit)
				break;
			if (!debuginfo_cu_parser_next(&info->clv_parser))
				goto done;
			if (dbg_awaituser())
				goto done;
		}
	}
done:
	return NULL;
}

/* To-be called from inside of `cmod_symenum_callback_t' when
 * `info_loaded == false', and extended symbol information is
 * needed. */
PUBLIC NONNULL((1)) void
NOTHROW(FCALL cmod_symenum_loadinfo)(struct cmodsyminfo *__restrict info) {
	bool has_object_address;
	info->clv_dip = NULL;
	if (cmodsyminfo_isdip(info)) {
		info->clv_dip = cmodsyminfo_getdip(info);
	} else if (cmodsyminfo_ismip(info)) {
		info->clv_dip = cmodsyminfo_getmip(info)->ms_dip;
	}
	bzero(&info->clv_data, sizeof(info->clv_data));
	has_object_address = false;
	if (cmodsyminfo_ismip(info) || cmodsyminfo_issip(info)) {
		CLinkerSymbol const *psymbol;
		uintptr_t symbol_addr;
		if (cmodsyminfo_ismip(info)) {
			psymbol = cmodsyminfo_getmip(info)->ms_sip;
		} else {
			psymbol = cmodsyminfo_getsip(info);
		}
		/* Load the object address from .symtab */
		if (CLinkerSymbol_IsElf32(info->clv_mod)) {
			symbol_addr = (uintptr_t)psymbol->cls_elf32.st_value;
		} else if (CLinkerSymbol_IsElf64(info->clv_mod)) {
			symbol_addr = (uintptr_t)psymbol->cls_elf64.st_value;
		} else if (CLinkerSymbol_IsKern(info->clv_mod)) {
			symbol_addr = (uintptr_t)psymbol->cls_kern.ks_addr;
		} else {
			goto no_sip_addr;
		}
		has_object_address             = true;
		info->clv_data.s_var.v_objaddr = (void *)(cmodule_getloadaddr(info->clv_mod) +
		                                          symbol_addr);
	}
no_sip_addr:
	if (!info->clv_unit) {
		/* Lookup the appropriate compilation unit. */
		if (info->clv_dip)
			info->clv_unit = cmodule_findunit_from_dip(info->clv_mod, info->clv_dip);
		/* Try to load the CU by looking at the symbol address.
		 * Only do this if we don't have the DIP-address, or if
		 * we were unable to map the DIP-address. */
		if (!info->clv_unit && has_object_address) {
			uintptr_t symbol_addr;
			symbol_addr = (uintptr_t)info->clv_data.s_var.v_objaddr;
			symbol_addr -= cmodule_getloadaddr(info->clv_mod);
			info->clv_dip  = NULL; /* Re-calculate from `clv_unit' (s.a. `cmod_symenum_search_for_address()') */
			info->clv_unit = cmodule_findunit_from_pc(info->clv_mod, symbol_addr);
		}
		if (!info->clv_unit) {
			/* Shouldn't happen... (fill in stub-data) */
			bzero(&info->clv_cu, sizeof(info->clv_cu));
			bzero(&info->clv_parser, sizeof(info->clv_parser));
			return;
		}
	}

	/* Load a parser for the symbol's DIP. */
	cmodunit_parser_from_dip(info->clv_unit,
	                         info->clv_mod,
	                         &info->clv_parser,
	                         NULL);

	/* Load the nearest `DW_TAG_compile_unit' component. */
	while (info->clv_parser.dup_comp.dic_tag != DW_TAG_compile_unit) {
		debuginfo_cu_parser_skipattr(&info->clv_parser);
		if (!debuginfo_cu_parser_next(&info->clv_parser)) {
			bzero(&info->clv_cu, sizeof(info->clv_cu));
			goto do_load_dip;
		}
	}

	/* Load attributes for the associated CU */
	if (!debuginfo_cu_parser_loadattr_compile_unit(&info->clv_parser,
	                                               &info->clv_cu))
		bzero(&info->clv_cu, sizeof(info->clv_cu));

	if (!info->clv_dip && has_object_address) {
		/* The symbol being pushed originates from some module's .symtab,
		 * but we were unable to  find any debug information relating  to
		 * this symbol while parsing .debug_info.
		 *
		 * However, that doesn't  mean that the  module doesn't have  some
		 * other name by which `csym' can be addressed. After all: we _do_
		 * have the address of the symbol (csym.clv_data.s_var.v_objaddr),
		 * so we know that it exists.
		 *
		 * This can happen if we're supposed to push a library symbol  that
		 * had  been defined via something like `DEFINE_PUBLIC_ALIAS()', in
		 * which case no dedicated debug information for that symbol  would
		 * have been created,  and, so-long  as the library  didn't end  up
		 * directly using its own exported  symbol (and only ever used  its
		 * private name for the same symbol), we wouldn't know what kind of
		 * object we're dealing with.
		 *
		 * However, that isn't to say that we can't find out. After all:
		 * we  do have an address which we  can use to perform a reverse
		 * symbol lookup (akin to addr2line, only this time we use it to
		 * do an `addr2typeinfo')
		 *
		 * This  special case is  required to load  proper type information for
		 * pretty much all symbols exposed  by the user-space `libc.so',  which
		 * makes extensive  use  of  `DEFINE_PUBLIC_ALIAS(symbol, libc_symbol)'
		 * to  expose `libc_symbol' as `symbol', where we would know about both
		 * symbols at this point, though  the caller originally made a  request
		 * to `symbol', and .debug_info only contains mentions of `libc_symbol' */
		uintptr_t module_relative_addr;
		module_relative_addr = (uintptr_t)info->clv_data.s_var.v_objaddr -
		                       cmodule_getloadaddr(info->clv_mod);
		info->clv_dip = cmod_symenum_search_for_address(info, module_relative_addr);
	}

do_load_dip:
	/* Load symbol-specific debug information. */
	info->clv_parser.dsp_cu_info_pos = info->clv_dip;
	if (!info->clv_dip || !debuginfo_cu_parser_next(&info->clv_parser)) {
		/* Fill in a stub/EOF component. */
		info->clv_parser.dup_comp.dic_tag         = 0; /* DW_TAG_... */
		info->clv_parser.dup_comp.dic_haschildren = DW_CHILDREN_no;
		info->clv_parser.dsp_cu_info_pos = info->clv_parser.dsp_cu_info_end;
	}

	/* Load attributes of the pointed-to element to extract var-information. */
	if (!cmodsyminfo_istype(info)){
		di_debuginfo_component_attrib_t attr;
again_attributes:
		DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &info->clv_parser) {
			switch (attr.dica_name) {

			case DW_AT_abstract_origin: {
				byte_t const *abstract_origin;
				if unlikely(!debuginfo_cu_parser_getref(&info->clv_parser, attr.dica_form,
				                                        &abstract_origin))
					goto done_attributes;
				info->clv_parser.dsp_cu_info_pos = abstract_origin;
				if unlikely(!debuginfo_cu_parser_next(&info->clv_parser))
					goto done_attributes;
				goto again_attributes;
			}	break;

			case DW_AT_location:
				if (!has_object_address)
					loadinfo_location(&info->clv_parser, info, attr.dica_form);
				break;

			case DW_AT_const_value:
				if (!has_object_address)
					loadinfo_const_value(&info->clv_parser, info, attr.dica_form, _attr_reader);
				break;

			case DW_AT_type:
				loadinfo_type(&info->clv_parser, info, attr.dica_form);
				break;

			case DW_AT_sibling:
			case DW_AT_specification: {
				byte_t const *spec;
				if likely(debuginfo_cu_parser_getref(&info->clv_parser, attr.dica_form, &spec))
					loadinfo_specifications(info, spec, has_object_address);
			}	break;

			case DW_AT_low_pc:
			case DW_AT_entry_pc:
				if (!has_object_address) {
					uintptr_t addr;
					if likely(debuginfo_cu_parser_getaddr(&info->clv_parser, attr.dica_form, &addr))
						info->clv_data.s_var.v_objaddr = (void *)(addr + cmodule_getloadaddr(info->clv_mod));
				}
				break;

			default:
				break;
			}
		}
	}
done_attributes:
	;
}

/* Return non-zero if the name of the given `sym' starts with the given name. */
#define cmodsym_name_startswith(sym, mod, startswith_name, startswith_namelen) \
	(strstartcmpz(cmodsym_name(sym, mod), startswith_name, startswith_namelen) == 0)

/* Enumerate  symbols  from `self'.  When a  symbol is  encountered that  stands in
 * conflict with  some other  symbol, try  to resolve  the conflict  by looking  at
 * the secondary  symbol table  `fallback_cu->cu_symbols'. If  that table  contains
 * another symbol with the same name, then that symbol will be enumerated, instead. */
PRIVATE NONNULL((1, 2, 3)) ssize_t
NOTHROW(FCALL cmod_symenum_symtab)(struct cmodule const *__restrict self,
                                   /*in|out(undef)*/ struct cmodsyminfo *__restrict info,
                                   cmod_symenum_callback_t cb, char const *startswith_name,
                                   size_t startswith_namelen, uintptr_t ns,
                                   struct cmodunit const *fallback_cu) {
	ssize_t temp, result = 0;
	size_t enum_lo, enum_hi;
	size_t index;
	enum_lo = 0;
	enum_hi = self->cm_symbols.mst_symc;
	/* Do a binary search to narrow down the range of symbols that should be enumerated. */
	for (;;) {
		char const *symbol_name;
		int cmp;
		if (enum_lo >= enum_hi)
			goto done;
		index       = (enum_lo + enum_hi) / 2;
		symbol_name = cmodsym_name(&self->cm_symbols.mst_symv[index], self);
		cmp         = strstartcmpz(symbol_name, startswith_name, startswith_namelen);
		if (cmp > 0) {
			enum_hi = index;
		} else if (cmp < 0) {
			enum_lo = index + 1;
		} else {
			/* Found some symbol `self->cm_symbols.mst_symv[index]' that matches our starts-with pattern. */
			break;
		}
	}
	/* Go backwards/forwards until we find the last symbol that matches our starts-with pattern. */
	enum_lo = enum_hi = index;
	while (enum_lo > 0 &&
	       cmodsym_name_startswith(&self->cm_symbols.mst_symv[enum_lo - 1],
	                               mod, startswith_name, startswith_namelen))
		--enum_lo;
	while (enum_hi < self->cm_symbols.mst_symc - 1 &&
	       cmodsym_name_startswith(&self->cm_symbols.mst_symv[enum_hi + 1],
	                               mod, startswith_name, startswith_namelen))
		++enum_hi;
	/* At this point, we've narrowed down the range of symbols to enumerate
	 * to   those   found  at   indices   [enum_lo, enum_hi]  (inclusively)
	 * Now to actually enumerate them! */
	for (index = enum_lo; index <= enum_hi; ++index) {
		struct cmodsym *sym;
		sym = &self->cm_symbols.mst_symv[index];

		/* Check if we're actually supposed to enumerate this symbol. */
		if (!want_symbol(sym, ns))
			continue;

		/* Check if the symbol stands in conflict with something else. */
		if (cmodsym_getns(sym) & CMODSYM_DIP_NS_FCONFLICT) {
			/* If we've been given a custom CU, check if it contains another version of this symbol. */
			if (fallback_cu) {
				struct cmodsym *percu_sym;
				char const *symbol_name = cmodsym_name(sym, self);
				percu_sym = cmodsymtab_lookup(&fallback_cu->cu_symbols,
				                              self,
				                              symbol_name,
				                              strlen(symbol_name),
				                              ns);
				if (percu_sym != NULL)
					sym = percu_sym; /* Use this symbol instead! */
			}
		}

		/* Copy symbol info. */
		info->clv_symbol.cms_name = sym->cms_name;
		info->clv_symbol.cms_dip  = sym->cms_dip;

		/* Actually do the enumeration. */
		info->clv_unit = NULL; /* We don't know the actual unit at this point! */
		temp           = (*cb)(info, false);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
done:
	return result;
err:
	return temp;
}

/* Enumerate global variables of the module pointed-to by `info->clv_mod' */
PRIVATE NONNULL((1, 2)) ssize_t
NOTHROW(FCALL cmod_symenum_globals)(/*in|out(undef)*/ struct cmodsyminfo *__restrict info,
                                    cmod_symenum_callback_t cb, char const *startswith_name,
                                    size_t startswith_namelen, uintptr_t ns,
                                    bool *__restrict pdid_encounter_nomem,
                                    struct cmodunit const *fallback_cu) {
	dbx_errno_t error;
	ssize_t result;
	/* Make sure that symbols for this module have been loaded. */
	error = cmodule_loadsyms(info->clv_mod);
	if unlikely(error != DBX_EOK) {
		if (error > 0)
			error = 0;
		if (error == DBX_ENOMEM) {
			*pdid_encounter_nomem = true;
			error = 0; /* Ignore NOMEM errors (so we can at least try to enumerate other modules...) */
		}
		/* Stop enumeration.
		 * NOTE: This here here causes `cmod_symenum()' to return DBX_EINTR */
		return error;
	}
	/* Enumerate symbols from the module's global symbol table. */
	result = cmod_symenum_symtab(info->clv_mod, info, cb,
	                             startswith_name, startswith_namelen,
	                             ns, fallback_cu);
	return result;
}


struct cmod_symenum_foreign_globals_data {
	REF struct cmodule     *excluded_module; /* [1..1] */
	struct cmodsyminfo     *info;            /* [1..1] */
	cmod_symenum_callback_t cb;              /* [1..1] */
	char const             *startswith_name;
	size_t                  startswith_namelen;
	uintptr_t               ns;
	bool                    did_encounter_nomem;
};

PRIVATE NONNULL((2)) ssize_t
NOTHROW(FCALL cmod_symenum_foreign_globals_cb)(void *cookie, struct cmodule *__restrict mod) {
	ssize_t result = 0;
	struct cmod_symenum_foreign_globals_data *arg;
	arg = (struct cmod_symenum_foreign_globals_data *)cookie;
	/* Check if we're supposed to exclude this module in particular. */
	if (mod != arg->excluded_module) {
		/* Select the new module. */
		xdecref(arg->info->clv_mod);
		arg->info->clv_mod = incref(mod);
		/* Enumerate symbols of this module. */
		result = cmod_symenum_globals(arg->info,
		                              arg->cb,
		                              arg->startswith_name,
		                              arg->startswith_namelen,
		                              arg->ns,
		                              &arg->did_encounter_nomem,
		                              /* Indicate  that  we  don't want  to  enumerate symbols
		                               * from some  specific  CU,  but  only  those  that  are
		                               * globally visible, and don't conflict with each other.
		                               * If this  was non-NULL,  the  pointed-to CU  would  be
		                               * used when  trying  to  resolve  conflicting  symbols. */
		                              NULL);
	}
	return result;
}


/* Enumerate local variables from the currently loaded CU
 * @return: DBX_EOK:     Success (local were enumerated)
 * @return: DBX_ENOENT:  Function containing `info->clv_modrel_pc' not  found.
 *                       In this case, a component has been selected  (without
 *                       it's attributes being parsed) that is located outside
 *                       the depth-scope set when this function was originally
 *                       called.
 * @return: DBX_EINTR:   Operation was interrupted.
 * @return: DBX_EINTERN: Internal error. */
PRIVATE ATTR_NOINLINE NONNULL((1, 2, 6)) dbx_errno_t
NOTHROW(FCALL cmod_symenum_locals_from_cu)(/*in|out(undef)*/ struct cmodsyminfo *__restrict info,
                                           cmod_symenum_callback_t cb, char const *startswith_name,
                                           size_t startswith_namelen, uintptr_t ns,
                                           ssize_t *__restrict presult) {
	debuginfo_errno_t error;
	ssize_t temp, result = 0;
	uintptr_t cu_depth;
	cu_depth = info->clv_parser.dup_child_depth;
	if (!debuginfo_cu_parser_next(&info->clv_parser))
		goto err_intern;
again_cu_component:
	while (info->clv_parser.dup_child_depth > cu_depth) {
		if (dbg_awaituser())
			goto err_intr;
		/* Scan components of this CU. */
		switch (info->clv_parser.dup_comp.dic_tag) {

		case DW_TAG_subprogram: {
			di_debuginfo_subprogram_t sp;
			uintptr_t subprogram_depth;
			if (!debuginfo_cu_parser_loadattr_subprogram(&info->clv_parser, &sp))
				goto generic_cu_child;
			subprogram_depth = info->clv_parser.dup_child_depth;
			/* Check if the given pointer is apart of this sub-program. */
			error = debuginfo_rnglists_contains(&sp.sp_ranges, &info->clv_parser,
			                                  info->clv_cu.cu_ranges.r_startpc, info->clv_modrel_pc,
			                                  di_debug_sections_as_di_rnglists_sections(&info->clv_mod->cm_sections));
			if (error != DEBUG_INFO_ERROR_SUCCESS) {
				/* Must be apart of a different sub-program. */
				for (;;) {
					if (!debuginfo_cu_parser_next(&info->clv_parser))
						goto err_intern;
					if (info->clv_parser.dup_child_depth <= subprogram_depth)
						goto again_cu_component;
					debuginfo_cu_parser_skipattr(&info->clv_parser);
				}
			}
			for (;;) {
				byte_t const *dip;
				if (!debuginfo_cu_parser_next_with_dip(&info->clv_parser, &dip))
					goto done_subprogram;
again_subprogram_component:
				if (info->clv_parser.dup_child_depth <= subprogram_depth)
					goto done_subprogram;
				if (dbg_awaituser())
					goto done_subprogram;
				switch (info->clv_parser.dup_comp.dic_tag) {

				case DW_TAG_variable:
				case DW_TAG_formal_parameter: {
					di_debuginfo_variable_t var;
					/* Check if the caller actually wants us to enumerate local variables. */
					if (ns >= CMODSYM_DIP_NS_TYPEDEF)
						goto skip_in_cu_tag_attr;
					if (debuginfo_cu_parser_loadattr_variable(&info->clv_parser, &var)) {
						if (!var.v_rawname)
							var.v_rawname = var.v_name;
						/* Only  enumerate symbols that actually have a name, and only those
						 * where the selected variable name matches our starts-with pattern. */
						if (var.v_rawname &&
						    strstartcmpz(var.v_rawname, startswith_name, startswith_namelen) == 0) {
							/* Fill symbol information. */
							info->clv_symbol.cms_name = var.v_rawname;
							info->clv_symbol.cms_dip  = cmodsym_makedip(info->clv_mod, dip, CMODSYM_DIP_NS_NORMAL);
							info->clv_data.s_var.v_framebase = sp.sp_frame_base;
							info->clv_data.s_var.v_location  = var.v_location;
							info->clv_data.s_var.v_typeinfo  = var.v_type;
							info->clv_data.s_var.v_objaddr   = NULL;

							/* Actually enumerate this variable. */
							temp = (*cb)(info, true);
							if unlikely(temp < 0)
								goto err_callback_temp;
							result += temp;
						}
					}
				}	break;

				case DW_TAG_inlined_subroutine:
				case DW_TAG_try_block:
				case DW_TAG_catch_block:
				case DW_TAG_lexical_block: {
					di_debuginfo_lexical_block_t block;
					if (debuginfo_cu_parser_loadattr_lexical_block(&info->clv_parser, &block)) {
						error = debuginfo_rnglists_contains(&block.lb_ranges, &info->clv_parser,
						                                  info->clv_cu.cu_ranges.r_startpc, info->clv_modrel_pc,
						                                  di_debug_sections_as_di_rnglists_sections(&info->clv_mod->cm_sections));
						if (error != DEBUG_INFO_ERROR_SUCCESS) {
							/* Must be apart of a different scope. */
							uintptr_t block_depth;
							block_depth = info->clv_parser.dup_child_depth;
							for (;;) {
								if (!debuginfo_cu_parser_next_with_dip(&info->clv_parser, &dip))
									goto err_intern;
								if (info->clv_parser.dup_child_depth <= block_depth)
									goto again_subprogram_component;
								debuginfo_cu_parser_skipattr(&info->clv_parser);
							}
						}
					}
				}	break;

				/* TODO: Enumerate local types */
				/* TODO: Enumerate local enum constants */

				default:
skip_in_cu_tag_attr:
					debuginfo_cu_parser_skipattr(&info->clv_parser);
					break;
				}
			}
done_subprogram:
			*presult = result;
			return DBX_EOK;
		}	break;

		default:
generic_cu_child:
			debuginfo_cu_parser_skipattr(&info->clv_parser);
/*next_cu_component:*/
			if (!debuginfo_cu_parser_next(&info->clv_parser))
				goto err_intern;
			break;
		}
	}
	return DBX_ENOENT;
err_callback_temp:
	*presult = temp;
	return DBX_EOK;
err_intern:
	return DBX_EINTERN;
err_intr:
	return DBX_EINTR;
}


/* Enumerate local variables from the selected CU */
PRIVATE ATTR_NOINLINE NONNULL((1, 2)) ssize_t
NOTHROW(FCALL cmod_symenum_locals)(/*in|out(undef)*/ struct cmodsyminfo *__restrict info,
                                   cmod_symenum_callback_t cb, char const *startswith_name,
                                   size_t startswith_namelen, uintptr_t ns) {
	ssize_t result = 0;
	/* Initialize the parser. */
	cmodunit_parser_from_dip(info->clv_unit, info->clv_mod, &info->clv_parser, NULL);
again:
	if (dbg_awaituser()) {
do_set_interrupted:
		result = DBX_EINTR;
	} else {
		switch (info->clv_parser.dup_comp.dic_tag) {

		case DW_TAG_compile_unit: {
			dbx_errno_t error;
			/* Load attributes for this CU. */
			if (!debuginfo_cu_parser_loadattr_compile_unit(&info->clv_parser,
			                                               &info->clv_cu))
				break;
			info->clv_parser.dup_comp.dic_tag = 0; /* Prevent infinite recursion on error. */
			/* Enumerate with information from this CU. */
			error = cmod_symenum_locals_from_cu(info, cb,
			                                    startswith_name,
			                                    startswith_namelen,
			                                    ns, &result);
			if (error == DBX_EOK)
				break;
			if (error == DBX_EINTR)
				goto do_set_interrupted;
			if (error == DBX_ENOENT) {
				/* Check for secondary CUs (although those really shouldn't exist...) */
				goto skip_attributes_and_parse_next;
			}
		}	break;

		default:
			/* Skip unexpected components. */
skip_attributes_and_parse_next:
			debuginfo_cu_parser_skipattr(&info->clv_parser);
			if (debuginfo_cu_parser_next(&info->clv_parser))
				goto again;
			break;
		}
	}
	return result;
}


/* From the point  of view  of `cmod_syminfo()',  enumerate all  symbols who's  names
 * start with `startswith_name...+=startswith_namelen'. When `startswith_namelen==0',
 * all symbols are enumerated.
 * Also note that this function may sporadically stop enumeration before being finished,
 * even when `cb' didn't indicate a negative return value when `dbg_awaituser()' returns
 * true, which is handled the same as enumeration completing normally.
 * NOTE: The `out(undef)' that all non-[const]  fields are undefined upon  return,
 *       with the exception of out-of-band fields (if any), who's contents depends
 *       on what `cb' may or may not have done.
 * @param: info:  Specifications for where to look for symbols, as well as a  cookie-pointer
 *                that is passed to `cb' during invocation (the caller may embed the  symbol
 *                info descriptor inside of a larger structure which can then be re-accessed
 *                via `container_of' from inside of `cb', thus allowing additional arguments
 *                to be passed to the callback function)
 *                The  caller  must fill  in  `clv_mod', `clv_unit'  and  `clv_modrel_pc' before
 *                calling this function. If not available, you may fill `clv_mod' and `clv_unit'
 *                with `NULL', and leave `clv_modrel_pc' undefined.
 * @param: cb:    Callback to invoke for every symbol found.
 * @param: ns:    Symbol namespace (one of `CMODSYM_DIP_NS_*')
 * @param: scope: The scope of symbols that should be enumerated (set of `CMOD_SYMENUM_SCOPE_F*')
 * @return: * :        pformatprinter-compatible accumulation of return values from `cb'
 * @return: DBX_EINTR: Operation was interrupted. */
PUBLIC NONNULL((1, 2)) ssize_t
NOTHROW(FCALL cmod_symenum)(/*in|out(undef)*/ struct cmodsyminfo *__restrict info,
                            cmod_symenum_callback_t cb, char const *startswith_name,
                            size_t startswith_namelen, uintptr_t ns, uintptr_t scope) {
	ssize_t temp, result = 0;
	bool did_encounter_nomem = false;
	if (!(scope & CMOD_SYMENUM_SCOPE_FNOLOCAL)) {
		if (info->clv_mod && info->clv_unit) {
			/* Enumerate local variables */
			temp = cmod_symenum_locals(info, cb, startswith_name, startswith_namelen, ns);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
	}
	if (!(scope & CMOD_SYMENUM_SCOPE_FNOGLOBAL)) {
		if (info->clv_mod) {
			/* Enumerate globals from this module.
			 * NOTE: When `info->clv_unit' is non-NULL, then the pointed-to CU
			 *       is used by this function to resolve conflicting  symbols. */
			temp = cmod_symenum_globals(info, cb,
			                            startswith_name,
			                            startswith_namelen,
			                            ns,
			                            &did_encounter_nomem,
			                            info->clv_unit);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
	}
	if (!(scope & CMOD_SYMENUM_SCOPE_FNOFOREIGN)) {
		struct cmod_symenum_foreign_globals_data data;
		data.excluded_module     = xincref(info->clv_mod); /* Exclude the original module. */
		data.info                = info;
		data.cb                  = cb;
		data.startswith_name     = startswith_name;
		data.startswith_namelen  = startswith_namelen;
		data.ns                  = ns;
		data.did_encounter_nomem = did_encounter_nomem;
		/* Enumerate all CModules currently visible,
		 * and recursively enumerate their  symbols. */
		temp = cmodule_enum(&cmod_symenum_foreign_globals_cb, &data);
		xdecref(data.excluded_module);
		if unlikely(temp < 0)
			goto err;
		result += temp;
		did_encounter_nomem = data.did_encounter_nomem;
	}
	/* If  (seemingly) nothing was  enumerated, and we did
	 * encounter an out-of-memory error at one point, then
	 * propagate that error to the caller. */
	if (result == 0 && did_encounter_nomem)
		result = DBX_ENOMEM;
	return result;
err:
	return temp;
}

/* Same as `cmod_symenum()', except  this function automatically manages  the
 * input fields of `info' which must normally be filled in by the caller, and
 * will instead fill them in itself, as well as clean them up afterwards.
 * NOTE: _DONT_ call `cmod_syminfo_local_fini(info)' after this function returns!
 *       Any cleanup will  have already  been done internally  by this  function!
 * NOTE: The `in(oob_only)' means that only out-of-band data that is used
 *       by `cb' must be initialized prior to this function being called.
 * NOTE: The `out(undef)' that all non-[const]  fields are undefined upon  return,
 *       with the exception of out-of-band fields (if any), who's contents depends
 *       on what `cb' may or may not have done.
 * @return: * :        pformatprinter-compatible accumulation of return values from `cb'
 * @return: DBX_EINTR: Operation was interrupted. */
PUBLIC NONNULL((1, 2)) ssize_t
NOTHROW(FCALL cmod_symenum_local)(/*in(oob_only)|out(undef)*/ struct cmodsyminfo *__restrict info,
                                  cmod_symenum_callback_t cb, char const *startswith_name,
                                  size_t startswith_namelen, uintptr_t ns, uintptr_t scope) {
	void const *pc;
	ssize_t result;
	pc = dbg_getpcreg(DBG_RT_REGLEVEL_VIEW);
	/* Lookup the module that contains `pc' */
	info->clv_mod = cmodule_ataddr(pc);
	if (info->clv_mod) {
		info->clv_modrel_pc = (uintptr_t)pc - cmodule_getloadaddr(info->clv_mod);
		info->clv_unit      = cmodule_findunit_from_pc(info->clv_mod, info->clv_modrel_pc);
		if unlikely(!info->clv_unit) {
			decref(info->clv_mod);
			info->clv_mod = NULL;
		}
	}
	/* Enumerate symbols. */
	result = cmod_symenum(info, cb,
	                      startswith_name,
	                      startswith_namelen,
	                      ns, scope);
	/* Cleanup */
	xdecref(info->clv_mod);
	return result;
}





DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_MODDBX_CMODULE_C */
