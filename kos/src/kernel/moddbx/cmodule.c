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
#ifndef GUARD_MODDBX_CMODULE_C
#define GUARD_MODDBX_CMODULE_C 1
#define _KOS_SOURCE 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER

#include <debugger/input.h>
#include <debugger/rt.h>
#include <kernel/driver.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/vm/usermod.h>

#include <hybrid/overflow.h>
#include <hybrid/sequence/bsearch.h>
#include <hybrid/unaligned.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libdebuginfo/debug_aranges.h>
#include <libdebuginfo/debug_info.h>

/**/
#include "include/cmodule.h"
#include "include/malloc.h"

DECL_BEGIN

/* Initialize a debug information CU parser from a given CModule CompilationUnit
 * @param: dip: A pointer to the first component to load, or `NULL' to simply load
 *              the first component following the start of the associated CU descriptor.
 *              When non-NULL, this pointer must be located somewhere between
 *              `cmodunit_di_start(self)' and `cmodunit_di_end(self)'.
 *              If it isn't, then the parser will be initialized to always indicate EOF. */
PUBLIC NONNULL((1, 2, 3)) void
NOTHROW(FCALL cmodunit_parser_from_dip)(struct cmodunit const *__restrict self,
                                        struct cmodule const *__restrict mod,
                                        di_debuginfo_cu_parser_t *__restrict result,
                                        byte_t const *dip) {
	uintptr_t temp;
	byte_t const *reader;
	reader = cmodunit_di_start(self);
	result->dup_cu_info_hdr = reader;
	/* 7.5.1.1   Compilation Unit Header */
	temp = UNALIGNED_GET32((uint32_t const *)reader); /* unit_length */
	reader += 4;
	result->dup_ptrsize = 4;
	if (temp == UINT32_C(0xffffffff)) {
		/* 7.4 32-Bit and 64-Bit DWARF Formats
		 * In the 64-bit DWARF format, an initial length field is 96 bits in size, and has two parts:
		 *  - The first 32-bits have the value 0xffffffff.
		 *  - The following 64-bits contain the actual length represented as an unsigned 64-bit integer. */
		result->dup_ptrsize = 8;
		reader += 8;
	}
	result->dup_cu_info_end = cmodunit_di_end(self);
	result->dup_version = UNALIGNED_GET16((uint16_t const *)reader); /* version */
	reader += 2;
	temp = UNALIGNED_GET32((uint32_t const *)reader); /* debug_abbrev_offset */
	reader += 4;
	if (temp == 0xffffffff)
		reader += 8;
	result->dup_addrsize = *(uint8_t const *)reader; /* address_size */
	reader += 1;
	result->dup_cu_info_pos = reader;
	if (dip) {
		/* If the given pointer is outside the valid range, setup the parser for EOF. */
		if (dip < result->dup_cu_info_hdr ||
		    dip > result->dup_cu_info_end)
			dip = result->dup_cu_info_end;
		result->dup_cu_info_pos = dip;
	}
	reader                = result->dup_cu_info_end;
	result->dup_sections  = di_debug_sections_as_di_debuginfo_cu_parser_sections(&mod->cm_sections);
	result->dup_cu_abbrev = (di_debuginfo_cu_abbrev_t *)&self->cu_abbrev;
	/* Load the first component of the compilation unit. */
	if (!debuginfo_cu_parser_next(result)) {
		/* Fill in a stub/EOF component. */
		result->dup_comp.dic_tag         = 0; /* DW_TAG_... */
		result->dup_comp.dic_haschildren = DW_CHILDREN_no;
		result->dup_cu_info_pos = result->dup_cu_info_end;
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

INTERN NONNULL((1)) void
NOTHROW(FCALL cmodule_fini)(struct cmodule *__restrict self) {
	size_t i;
	if (self->cm_pself) {
		if ((*self->cm_pself = self->cm_next) != NULL)
			self->cm_next->cm_pself = self->cm_pself;
	}
	debug_sections_unlock(&self->cm_sectrefs module_type__arg(self->cm_modtyp));
	module_decref(self->cm_module, self->cm_modtyp);
	cmodsymtab_fini(&self->cm_symbols);
	for (i = 0; i < self->cm_cuc; ++i)
		cmodunit_fini(&self->cm_cuv[i]);
}

/* Destroy the given CModule. (called when its reference counter hits `0') */
PUBLIC NONNULL((1)) void
NOTHROW(FCALL cmodule_destroy)(struct cmodule *__restrict self) {
	cmodule_fini(self);
	dbx_free(self);
}


PRIVATE NONNULL((1, 2)) ssize_t
NOTHROW(FCALL cmodule_enum_uservm_except)(struct vm *__restrict self,
                                          cmodule_enum_callback_t cb,
                                          void *cookie,
                                          struct cmodule *skipme) {
#ifdef CONFIG_HAVE_USERMOD
	ssize_t temp, result = 0;
	REF struct usermod *um;
	TRY {
		um = vm_getusermod_above(self, NULL);
	} EXCEPT {
		goto done;
	}
	if likely(um) {
		/* Enumerate modules. */
		do {
			REF struct cmodule *cm;
			cm = cmodule_locate((module_t *)um
			                    module_type__arg(MODULE_TYPE_USRMOD));
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
				decref(um);
				result = DBX_EINTR;
				break;
			}
			/* Load the next user-space module. */
			{
				REF struct usermod *next_um;
				TRY {
					next_um = vm_getusermod_next(self, um);
				} EXCEPT {
					decref(um);
					goto done;
				}
				decref(um);
				um = next_um;
			}
		} while (um != NULL);
	}
done:
	return result;
err:
	result = temp;
	goto done;
#else /* CONFIG_HAVE_USERMOD */
	(void)self;
	(void)cb;
	(void)cookie;
	(void)skipme;
	return 0;
#endif /* !CONFIG_HAVE_USERMOD */
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW(FCALL cmodule_enum_drivers_except)(cmodule_enum_callback_t cb,
                                           void *cookie,
                                           struct cmodule *skipme) {
	size_t i;
	ssize_t temp, result = 0;
	REF struct driver_state *ds;
	REF struct cmodule *cm;
	/* Enumerate the kernel core driver. */
	if (!skipme || skipme->cm_module != (module_t *)&kernel_driver) {
		cm = cmodule_locate((module_t *)&kernel_driver
		                    module_type__arg(MODULE_TYPE_DRIVER));
		if likely(cm)
			result = (*cb)(cookie, cm);
		decref(cm);
		if unlikely(result < 0)
			goto done_nods;
	}
	ds = driver_get_state();
	for (i = 0; i < ds->ds_count; ++i) {
		cm = cmodule_locate((module_t *)ds->ds_drivers[i]
		                    module_type__arg(MODULE_TYPE_DRIVER));
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
	decref(ds);
done_nods:
	return result;
err:
	result = temp;
	goto done;
}

/* Enumerate all CModules that are currently visible in the following order:
 * >> void *pc = dbg_getpcreg(DBG_REGLEVEL_VIEW);
 * >> ENUM(cmodule_ataddr(pc));
 * >> if (ADDR_ISKERN(pc)) {
 * >>     cmodule_enum_drivers();                 // Excluding `cmodule_ataddr(pc)'
 * >>     cmodule_enum_uservm(dbg_current->t_vm);
 * >> } else {
 * >>     cmodule_enum_uservm(dbg_current->t_vm); // Excluding `cmodule_ataddr(pc)'
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
	pc = (void const *)dbg_getpcreg(DBG_REGLEVEL_VIEW);
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
	    dbg_current->t_vm != NULL && dbg_current->t_vm != &vm_kernel) {
		temp = cmodule_enum_uservm_except(dbg_current->t_vm, cb, cookie, start_module);
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


/* Enumerate all user-space modules mapped within the given vm
 * `self' as CModule objects, and invoke `cb' on each of them.
 * @return: * :        pformatprinter-compatible return value.
 * @return: DBX_EINTR: Operation was interrupted. */
PUBLIC NONNULL((1, 2)) ssize_t
NOTHROW(FCALL cmodule_enum_uservm)(struct vm *__restrict self,
                                   cmodule_enum_callback_t cb,
                                   void *cookie) {
	return cmodule_enum_uservm_except(self, cb, cookie, NULL);
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
 * from `dbx_heap_alloc()' in an attempt to free memory).
 * @param: keep_loaded: When true, keep modules descriptors loaded if they
 *                      are apart of the kernel, or the `dbg_current->t_vm'
 *                      Otherwise, clear all modules from the cache.
 * @return: * : The # of modules that actually got destroyed (i.e. removing
 *              them from the cache caused their refcnt to drop to `0') */
PUBLIC size_t NOTHROW(FCALL cmodule_clearcache)(bool keep_loaded) {
	size_t result = 0;
	struct cmodule **piter, *iter;
	piter = &cmodule_cache;
	while ((iter = *piter) != NULL) {
		if (keep_loaded) {
			/* Check if we should keep this module. */
			struct vm *modvm;
			modvm = module_vm(iter->cm_module,
			                  iter->cm_modtyp);
			if (modvm == &vm_kernel ||
			    modvm == dbg_current->t_vm) {
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
	 * then we must fix-up the abbreviation cache list pointers of
	 * already-initialized compilation units.
	 * Otherwise, (if those pointers referenced the static abbreviation
	 * cache), those points would still point to the old object position,
	 * which is no longer valid, as the static cache will have been
	 * moved as well. */
	for (i = 0; i < cuc; ++i) {
		struct cmodunit *new_cu, *old_cu;
		new_cu = &new_addr->cm_cuv[i];
		old_cu = &old_addr->cm_cuv[i];
		if (new_cu->cu_abbrev.dua_cache_list == old_cu->cu_abbrev.dua_stcache)
			new_cu->cu_abbrev.dua_cache_list = new_cu->cu_abbrev.dua_stcache;
	}
}


PRIVATE WUNUSED NONNULL((1)) REF struct cmodule *
NOTHROW(FCALL cmodule_create)(module_t *__restrict mod
                              module_type__param(modtype)) {
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
	debug_sections_lock(mod,
	                    &result->cm_sections,
	                    &result->cm_sectrefs
	                    module_type__arg(modtype));
	/* Now walk through .debug_info and count the total # of CUs, as
	 * well as initialize the PER-CU fields from `struct cmodunit'.
	 * The per-CU ordering of offsets into the .debug_info section
	 * are gained automatically since we're traversing .debug_info
	 * linearly, and always appending to the end of the list of CUs */
	{
		byte_t const *reader, *end, *next_cu;
		reader = result->cm_sections.ds_debug_info_start;
		end    = result->cm_sections.ds_debug_info_end;
		result->cm_cuv[0].cu_di_start = end; /* Initial end-pointer (for consistency) */
		while (reader < end) {
			di_debuginfo_cu_parser_t parser;
			size_t length;
			uintptr_t debug_abbrev_offset;
			struct cmodunit *cu;
			if (cuc_used >= cuc_alloc) {
				/* Must allocate space for more CUs. */
				REF struct cmodule *new_result;
				cuc_alloc  = cuc_used + 16;
				new_result = (REF struct cmodule *)dbx_realloc(result, SIZEOF_CMODULE(cuc_alloc));
				if unlikely(!new_result) {
					cuc_alloc = cuc_used + 1;
					/* FIXME: Because the DBX heap as implemented right now can only allocate
					 *        heap blocks of a limited max-size, this right here ends up failing
					 *        for very large programs.
					 *  - It does work for the kernel core (barely)
					 *  - But it fails when trying to load /bin/busybox (which just uses too many CUs...)
					 */
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
			parser.dup_ptrsize = 4;
			if (length >= UINT32_C(0xfffffff0)) {
				if (length == UINT32_C(0xffffffff)) {
					/* 7.4 32-Bit and 64-Bit DWARF Formats
					 * In the 64-bit DWARF format, an initial length field is 96 bits in size, and has two parts:
					 *  - The first 32-bits have the value 0xffffffff.
					 *  - The following 64-bits contain the actual length represented as an unsigned 64-bit integer. */
					length = (size_t)UNALIGNED_GET64((uint64_t const *)reader);
					reader += 8;
					parser.dup_ptrsize = 8;
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
			parser.dup_version = UNALIGNED_GET16((uint16_t const *)reader);
			reader += 2; /* version */
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

			parser.dup_addrsize = *(uint8_t const *)reader; /* address_size */
#if __SIZEOF_POINTER__ > 4
			if unlikely(parser.dup_addrsize != 1 && parser.dup_addrsize != 2 &&
			            parser.dup_addrsize != 4 && parser.dup_addrsize != 8)
#else /* __SIZEOF_POINTER__ > 4 */
			if unlikely(parser.dup_addrsize != 1 && parser.dup_addrsize != 2 &&
			            parser.dup_addrsize != 4)
#endif /* __SIZEOF_POINTER__ <= 4 */
			{
				printk(KERN_ERR "[dbx] Illegal address_size %#" PRIx8 " in .debug_info CU header at %p\n",
				       parser.dup_addrsize, reader);
				goto done_cucs;
			}
			reader += 1;
			/* At this point, `reader' would be used to initialize `dup_cu_info_pos' of a
			 * parser, which in all likelihood would yield a `DW_TAG_compile_unit' component. */

			/* If what follows is a `DW_TAG_compile_unit', which itself is then
			 * followed by EOF, then we can skip this CU. When this happens, then
			 * the associated CU originates from an assembly file, which in turn
			 * doesn't contain any additional debug info, so we can just ignore
			 * and discard it here! */
			parser.dup_sections    = di_debug_sections_as_di_debuginfo_cu_parser_sections(&result->cm_sections);
			parser.dup_cu_abbrev   = &cu->cu_abbrev;
			parser.dup_cu_info_hdr = cmodunit_di_start(cu);
			parser.dup_cu_info_end = cmodunit_di_end(cu);
			parser.dup_cu_info_pos = reader;
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
#if MODULE_TYPE_COUNT >= 2
	result->cm_modtyp = modtype;
#endif /* MODULE_TYPE_COUNT >= 2 */
	module_incref(mod, modtype);
	result->cm_module           = mod; /* Inherit reference */
	result->cm_symbols.mst_symc = 0;
	result->cm_symbols.mst_symv = NULL;
	result->cm_cuc              = cuc_used;
done:
	return result;
err_r:
	/* Unlock .debug_* sections. */
	debug_sections_unlock(&result->cm_sectrefs
	                       module_type__arg(modtype));
	dbx_free(result);
	result = NULL;
	goto done;
}

/* Lookup or create the CModule for the given `mod:modtype'
 * If the module has already been loaded, return a reference to
 * the pre-loaded CModule. Otherwise, create and remember a new
 * module which is then kept in-cache. If this step fails due to
 * lack of memory, `NULL' is returned instead. */
PUBLIC WUNUSED NONNULL((1)) REF struct cmodule *
NOTHROW(FCALL cmodule_locate)(module_t *__restrict mod
                              module_type__param(modtype)) {
	REF struct cmodule *result;
	/* Search for an already-loaded module. */
	for (result = cmodule_list; result; result = result->cm_next) {
		if (result->cm_module == mod)
			return incref(result);
	}
	/* Create a new module. */
	result = cmodule_create(mod module_type__arg(modtype));
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

/* Return the CModule descriptor for a given `addr', which should be a program counter, or data-pointer.
 * If no such module exists, or its descriptor could not be allocated, return `NULL' instead.
 * This function is a thin wrapper around `module_ataddr_nx()' + `cmodule_locate()' */
PUBLIC WUNUSED NONNULL((1)) REF struct cmodule *
NOTHROW(FCALL cmodule_ataddr)(void const *addr) {
	REF struct cmodule *result;
	REF module_t *mod;
	module_type_var(modtype);
	mod = module_ataddr_nx(addr, modtype);
	if (!mod)
		return NULL;
	/* Lookup the CModule for the `mod' that we've found. */
	result = cmodule_locate(mod module_type__arg(modtype));
	module_decref(mod, modtype);
	return result;
}

/* Return the CModule for `dbg_getpcreg(DBG_REGLEVEL_VIEW)'
 * Same as `cmodule_ataddr(dbg_getpcreg(DBG_REGLEVEL_VIEW))' */
PUBLIC WUNUSED REF struct cmodule *
NOTHROW(FCALL cmodule_current)(void) {
	void const *pc;
	REF struct cmodule *result;
	pc     = (void const *)dbg_getpcreg(DBG_REGLEVEL_VIEW);
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

	case CMODSYM_DIP_NS_TYPEDEF:
		/* Accept anything that is a type */
		return symbol_ns != CMODSYM_DIP_NS_NORMAL;

	default:
		break;
	}
	/* Want a specific namespace. */
	return symbol_ns == ns;
}

/* Return the preferred symbol of the given 2 based on `ns'
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
		/* Prefer normal (non-type) symbols. */
		if (a_ns == CMODSYM_DIP_NS_NORMAL && b_ns != CMODSYM_DIP_NS_NORMAL)
			return a;
		if (b_ns == CMODSYM_DIP_NS_NORMAL && a_ns != CMODSYM_DIP_NS_NORMAL)
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
PRIVATE WUNUSED NONNULL((1, 2)) struct cmodsym *
NOTHROW(FCALL cmodsymtab_lookup)(struct cmodsymtab const *__restrict self,
                                 char const *__restrict name, size_t namelen,
                                 uintptr_t ns) {
	struct cmodsym *result;
	size_t lo, hi;
	lo = 0, hi = self->mst_symc;
	while (lo < hi) {
		size_t index;
		int cmp;
		index  = (lo + hi) / 2;
		result = &self->mst_symv[index];
		/* FIXME: compare right here assumes that `name...+=namelen'
		 *        does not contain any NUL characters!
		 * -> There really needs to be a function `strcmpl(a, b, blen)'
		 *    that ensures `strlen(a) == blen && memcmp(a, b, blen) == 0',
		 *    but still returns -1,0,+1 like memcmp(), while assuming that
		 *    any character from b outside of b...+=blen is equal to NUL. */
		cmp = memcmp(name, result->cms_name, namelen * sizeof(char));
		if (cmp == 0 && result->cms_name[namelen] != 0)
			cmp = -1; /* key < symbol */
		if (cmp < 0) {
			hi = index;
		} else if (cmp > 0) {
			lo = index + 1;
		} else {
			/* Found it! */

			/* Deal with multiple symbols of the same name by looking at `ns'!
			 * Note that right now, other symbols with the same name may both
			 * be located before and after `result'! */
			char const *symname;
			struct cmodsym *match_min, *match_max, *iter;
			/* Walk forward/backwards until we find a symbol of a different name. */
			symname   = result->cms_name;
			match_min = match_max = result;
			while (match_min > self->mst_symv &&
			       strcmp(match_min[-1].cms_name, symname) == 0)
				--match_min;
			while (match_max < &self->mst_symv[self->mst_symc - 1] &&
			       strcmp(match_max[1].cms_name, symname) == 0)
				++match_max;

			result = NULL;
			/* Select the symbol which we prefer the most. */
			for (iter = match_min; iter <= match_max; ++iter) {
				if (!want_symbol(iter, ns))
					continue;
				if (!result)
					result = iter;
				else {
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





PRIVATE NONNULL((1)) char const *
NOTHROW(FCALL parse_symbol_name_for_object)(di_debuginfo_cu_parser_t *__restrict self,
                                            uintptr_t *__restrict pns,
                                            bool reuse_parser);
PRIVATE ATTR_NOINLINE NONNULL((1)) char const *
NOTHROW(FCALL parse_symbol_name_for_object_r)(di_debuginfo_cu_parser_t *__restrict self,
                                              byte_t const *__restrict abstract_origin,
                                              uintptr_t *__restrict pns) {
	di_debuginfo_cu_parser_t inner_parser;
	memcpy(&inner_parser, self, sizeof(inner_parser));
	inner_parser.dup_cu_info_pos = abstract_origin;
	if (!debuginfo_cu_parser_next(&inner_parser))
		return NULL;
	return parse_symbol_name_for_object(&inner_parser, pns, true);
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
	inner_parser.dup_cu_info_pos = specification;
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
					inner_parser.dup_cu_info_pos = abstract_origin;
					goto again;
				}	break;

				case DW_AT_linkage_name:
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

/* Parse the currently pointed-to component's attributes in an attempt
 * to figure out if it has a name that should appear in symbol tables.
 * If it does, then that name is returned. Otherwise, NULL is returned,
 * but attributes for the current component will have still been parsed. */
PRIVATE NONNULL((1)) char const *
NOTHROW(FCALL parse_symbol_name_for_object)(di_debuginfo_cu_parser_t *__restrict self,
                                            uintptr_t *__restrict pns,
                                            bool reuse_parser) {
	di_debuginfo_component_attrib_t attr;
	char const *result = NULL;
again:
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

			case DW_AT_linkage_name:
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
		if (features != (DEBUGINFO_VAR_FEATURE_HASTYPE | DEBUGINFO_VAR_FEATURE_HASLOCATION)) {
			/* TODO: If only the location is missing, check the module's symbol table
			 *       for the missing object. This is required so we can properly load
			 *       symbols defined by assembly, and later used by high-level code.
			 */
			result = NULL; /* We need a type & location! */
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
		bool has_pc_attribute      = false;
		DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, self) {
			switch (attr.dica_name) {

			case DW_AT_abstract_origin:
				goto do_abstract_origin;

			case DW_AT_linkage_name:
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
				has_pc_attribute = true;
				break;

			default:
				break;
			}
		}
		if (!result)
			result = name_attribute;
		if (!has_pc_attribute)
			result = NULL; /* We need some way of addressing the symbol. */
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
		 *       can make use of know that the type is complete.
		 *       e.g. In the case of a struct, require that there
		 *            be a `DW_AT_byte_size' field. (or better yet:
		 *            simply ensure that `self->dup_comp.dic_haschildren'
		 *            is true, meaning that the struct has at least
		 *            some members defined, though in that case, we
		 *            must also allow a struct without members, that
		 *            is derived (c++-style) from another struct)
		 * Another example would be that `DW_TAG_pointer_type' must
		 * have a tag `DW_AT_type', which represents the pointed-to
		 * type.
		 * NOTE: The DWARF standard specifies that `DW_AT_declaration'
		 *       should appear in any forward-declaration, however I
		 *       really don't want to rely on something like that,
		 *       because I don't like the idea of the compiler having
		 *       to specify _more_ information to tell me that there
		 *       is _less_ information, when I can just check if there
		 *       is the information I'm looking for from the get-go.
		 */
		DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, self) {
			switch (attr.dica_name) {

			case DW_AT_declaration:
				/* Only a declaration; not a definition! */
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
			self->dup_cu_info_pos = abstract_origin;
			goto again;
		}
		return parse_symbol_name_for_object_r(self, abstract_origin, pns);
	}
}


/* Check if the 2 given encoded DIP pointer `dip_a'
 * and `dip_b' reference the same namespace. */
PRIVATE ATTR_CONST WUNUSED bool
NOTHROW(FCALL same_namespace)(uintptr_t dip_a, uintptr_t dip_b) {
	uintptr_t ns_a, ns_b;
	ns_a = dip_a & (CMODSYM_DIP_NSMASK & ~CMODSYM_DIP_NS_FCONFLICT);
	ns_b = dip_b & (CMODSYM_DIP_NSMASK & ~CMODSYM_DIP_NS_FCONFLICT);
	/* Quick check: Is it the same namespace id? */
	if (ns_a == ns_b)
		return true;
	/* The typedef namespace overlaps the normal namespace, and is
	 * only there to allow one to quickly determine if a symbol
	 * encodes a type, as opposed to a variable/const/etc. */
	if (ns_a == CMODSYM_DIP_NS_TYPEDEF)
		ns_a = CMODSYM_DIP_NS_NORMAL;
	if (ns_b == CMODSYM_DIP_NS_TYPEDEF)
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
			 * the least amount of additional memory. */
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

/* Add a new symbol with the given name to the given symbol table.
 * If another symbol with the same name and namespace already exists,
 * the operation silently succeeds without adding the new symbol,
 * alongside writing an error message to the system log.
 * However, this should only happen when there's something wrong with
 * how debug information is parsed.
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory. */
PRIVATE WUNUSED NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL cmodsymtab_addsymbol)(struct cmodsymtab *__restrict self,
                                    char const *__restrict name,
                                    uintptr_t symbol_dip) {
	size_t lo, hi, index;
	lo = 0;
	hi = self->mst_symc;
	for (;;) {
		int cmp;
		struct cmodsym const *sym;
		index = (lo + hi) / 2;
		if (lo >= hi)
			break;
		sym = &self->mst_symv[index];
		cmp = strcmp(name, sym->cms_name);
		if (cmp < 0) {
			hi = index;
		} else if (cmp > 0) {
			lo = index + 1;
		} else {
			/* Found a possible conflict. For this purpose,
			 * determine the range of symbols that share `name' */
			lo = hi = index;
			while (lo > 0 && strcmp(self->mst_symv[lo - 1].cms_name, name) == 0)
				--lo;
			while (hi < self->mst_symc - 1 &&
			       strcmp(self->mst_symv[hi + 1].cms_name, name) == 0)
				++hi;
			/* Check of one of the pre-existing symbols uses the same namespace as we do. */
			for (index = lo; index <= hi; ++index) {
				sym = &self->mst_symv[index];
				if (!same_namespace(sym->cms_dip, symbol_dip))
					continue; /* Different namespace. */
				/* Symbol re-definition (this shouldn't happen...) */
				printk(KERN_WARNING "[dbx] per-cu symbol re-definition of %q (found at %p and %p)\n",
					   name, sym->cms_dip, symbol_dip);
				return DBX_EOK;
			}
			/* No collision (we're dealing with differing namespace)
			 * As such, simply insert the new symbol at the end of the list
			 * of other symbols that share the same name. */
			index = hi + 1;
			break;
		}
	}
	/* Simply insert the new symbol into the global symbol table under `index' */
	return cmodsymtab_insert_symbol(self, index, name, symbol_dip);
}

/* Register a symbol. If the symbol had already been registered,
 * then don't do anything (and return DBX_EOK).
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory. */
PRIVATE WUNUSED NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL cmodule_addsymbol)(struct cmodule *__restrict self,
                                 struct cmodsymtab *__restrict cu_symtab,
                                 char const *__restrict name,
                                 byte_t const *__restrict dip,
                                 uintptr_t ns) {
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
		index = (lo + hi) / 2;
		if (lo >= hi)
			break;
		sym = &self->cm_symbols.mst_symv[index];
		cmp = strcmp(name, sym->cms_name);
		if (cmp < 0) {
			hi = index;
		} else if (cmp > 0) {
			lo = index + 1;
		} else {
			/* Found a possible conflict. For this purpose,
			 * determine the range of symbols that share `name' */
			lo = hi = index;
			while (lo > 0 && strcmp(self->cm_symbols.mst_symv[lo - 1].cms_name, name) == 0)
				--lo;
			while (hi < self->cm_symbols.mst_symc - 1 &&
			       strcmp(self->cm_symbols.mst_symv[hi + 1].cms_name, name) == 0)
				++hi;
			/* Check of one of the pre-existing symbols uses the same namespace as we do. */
			for (index = lo; index <= hi; ++index) {
				sym = &self->cm_symbols.mst_symv[index];
				if (!same_namespace(sym->cms_dip, symbol_dip))
					continue; /* Different namespace. */
				/* This is either a collision, or a re-definition.
				 * We can determine the later by comparing DIP values. */
				if (sym->cms_dip == symbol_dip)
					return DBX_EOK; /* Same dip -> Redefinition (ignore silently) */
				/* It's a collision!
				 * Mark the global symbol as such, and add
				 * the new symbol to the per-CU table. */
				sym->cms_dip |= CMODSYM_DIP_NS_FCONFLICT;
				/* Add the symbol to the per-CU table. */
				return cmodsymtab_addsymbol(cu_symtab, name, symbol_dip);
			}
			/* No collision (we're dealing with differing namespace)
			 * As such, simply insert the new symbol at the end of the list
			 * of other symbols that share the same name. */
			index = hi + 1;
			break;
		}
	}
	/* Simply insert the new symbol into the global symbol table under `index' */
	return cmodsymtab_insert_symbol(&self->cm_symbols, index, name, symbol_dip);
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
		dip      = parser.dup_cu_info_pos;
		/* Scan the elements of the compilation-unit. */
		if (debuginfo_cu_parser_nextchild(&parser)) {
			do {
				uintptr_t ns;
				char const *symbol_name;
				if (dbg_awaituser())
					goto err_interrupt;
				symbol_name = parse_symbol_name_for_object(&parser, &ns, false);
				if (symbol_name && *symbol_name) {
					/* Register this symbol. */
					result = cmodule_addsymbol(mod, &percu_symbols, symbol_name, dip, ns);
					if unlikely(result != DBX_EOK)
						goto err;
				}
				switch (parser.dup_comp.dic_tag) {

				case DW_TAG_enumeration_type:
				case DW_TAG_namespace:
					/* Allow looking inside of these tags for other global names.
					 * This special distinction is required since these types of
					 * variables _are_ actually loaded as globals. (unlike symbols
					 * defined within the bounds of other components, which we
					 * consider to have local scoping) */
					dip = parser.dup_cu_info_pos;
					if (!debuginfo_cu_parser_next(&parser))
						goto done;
					break;

				default: {
					/* Scan ahead to the next component at our current level.
					 * This way, we don't accidentally load local variables
					 * as though they were globals. */
					size_t wanted_depth;
					wanted_depth = parser.dup_child_depth;
					for (;;) {
						dip = parser.dup_cu_info_pos;
						if (!debuginfo_cu_parser_next(&parser))
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

/* Load debug symbols for the give CModule. Since doing this may
 * take quite a while, this function is equipped to make use of
 * `dbg_awaituser()' to allow it to be interrupted prior to being
 * completed. If this happens, then this function returns `DBX_EINTR',
 * and the caller must assume that not all symbols have been loaded.
 * In this case, the caller is allowed to continue as through that
 * the symbol they were looking for doesn't exist, or no symbols
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
	}
	return result;
}

/* Lookup the a symbol within `self', given its `name'. If debug
 * symbols had yet to be loaded, then this function will make a
 * call to `cmodule_loadsyms()'. If that call fails, this function
 * will simply return `NULL'.
 * To do its job, this function will first look at the per-module
 * symbol table of `self' (iow: `self->cm_symbols').
 * If this table contains a symbol matching `name', that symbol
 * is then returned, unless it has the `CMODSYM_DIP_NS_FCONFLICT'
 * flag set, in which case `dbg_getpcreg(DBG_REGLEVEL_VIEW)' is
 * check for being apart of `self'. If it is, try to find the CU
 * associated with that address. If such a CU exists, check that
 * CU's symbol table for `name' once again. If that table contains
 * the given `name' also, return that symbol. Otherwise (if any
 * of the above failed), simply return the symbol already found
 * within the module's global symbol table.
 * @param: ns: When different from `CMODSYM_DIP_NS_NORMAL', restrict
 *             the search to only return symbols from the indicated
 *             namespace. Otherwise, ~try~ to return symbols from the
 *             given namespace, but when (at least 1) symbol is found
 *             that is apart of a different namespace, return that
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
	result = cmodsymtab_lookup(&self->cm_symbols, name, namelen, ns);

	/* Check if the symbol we've found is in conflict with other,
	 * per-CU symbols. If this is the case, then we must lookup the symbol
	 * once again within the table associated with the currently viewed PC
	 * pointer, as returned by `dbg_getpcreg(DBG_REGLEVEL_VIEW)' */
	if (result && (cmodsym_getns(result) & CMODSYM_DIP_NS_FCONFLICT)) {
		void const *pc;
		pc = (void const *)dbg_getpcreg(DBG_REGLEVEL_VIEW);
		if (pc >= (void const *)cmodule_getloadstart(self) &&
		    pc <  (void const *)cmodule_getloadend(self)) {
			uintptr_t module_relative_pc;
			struct cmodunit *cu;
			module_relative_pc = (uintptr_t)pc - cmodule_getloadaddr(self);
			cu = cmodule_findunit_from_pc(self, module_relative_pc);
			if (cu != NULL) {
				struct cmodsym const *cu_symbol;
				cu_symbol = cmodsymtab_lookup(&cu->cu_symbols, name, namelen, ns);
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


/* Same as `cmodule_getsym_global()', but search for symbols starting with
 * `start_module', and continuing the search within related modules. For this
 * purpose, start by searching `start_module' itself, and moving on to other
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




/* Initialize a debug information CU parser to load debug information for a component
 * located at `dip' within the `.debug_info' mapping of `self'. For this
 * purpose, this function will locate the CU that contains `dip', and proceed
 * to call `cmodunit_parser()' to initialize `result'. If the given `dip'
 * is not apart of any of the CUs of `self', then `result' will be initialized
 * to always indicate EOF.
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
		memset(result, 0, sizeof(*result));
		return;
	}
	/* Initialize the parser from `cu' and `dip'. */
	cmodunit_parser_from_dip(cu, self, result, dip);
}


PRIVATE ATTR_NOINLINE WUNUSED NONNULL((1)) struct cmodunit *
NOTHROW(FCALL cmodule_findunit_from_pc_fallback)(struct cmodule const *__restrict self,
                                                 uintptr_t module_relative_pc) {
	size_t i;
	/* Fallback: Manually search through all CUs and find one that
	 *           has a `DW_TAG_compile_unit' with a range-list which
	 *           in turn contains `module_relative_pc' */
	for (i = 0; i < self->cm_cuc; ++i) {
		unsigned int error;
		di_debuginfo_cu_parser_t parser;
		di_debuginfo_compile_unit_t cu;
		cmodunit_parser_from_dip(&self->cm_cuv[i], self, &parser, NULL);
		/* Find the nearest CU. */
		if (parser.dup_comp.dic_tag != DW_TAG_compile_unit) {
			debuginfo_cu_parser_skipattr(&parser);
			if (!debuginfo_cu_parser_next(&parser))
				goto next_cu;
		}
		/* Load attributes of this CU. */
		if (!debuginfo_cu_parser_loadattr_compile_unit(&parser, &cu))
			goto next_cu;
		/* Check if the given `module_relative_pc' is contained by this CU. */
		error = debuginfo_ranges_contains(&cu.cu_ranges, &parser,
		                                  cu.cu_ranges.r_startpc, module_relative_pc,
		                                  self->cm_sections.ds_debug_ranges_start,
		                                  self->cm_sections.ds_debug_ranges_end);
		if (error == DEBUG_INFO_ERROR_SUCCESS)
			return (struct cmodunit *)&self->cm_cuv[i]; /* Found it! */
next_cu:
		;
	}
	return NULL;
}

/* Try to find the compilation unit that contains `module_relative_pc'
 * If no such unit can be located, `NULL' will be returned instead. */
PUBLIC WUNUSED NONNULL((1)) struct cmodunit *
NOTHROW(FCALL cmodule_findunit_from_pc)(struct cmodule const *__restrict self,
                                        uintptr_t module_relative_pc) {
	struct cmodunit *result;
	/* Try to make use of .debug_aranges to find the proper CU. */
	if (self->cm_sections.ds_debug_aranges_start < self->cm_sections.ds_debug_aranges_end) {
		uintptr_t debuginfo_cu_offset;
		unsigned int error;
		error = debugaranges_locate(self->cm_sections.ds_debug_aranges_start,
		                            self->cm_sections.ds_debug_aranges_end,
		                            &debuginfo_cu_offset,
		                            module_relative_pc);
		if (error == DEBUG_INFO_ERROR_SUCCESS) {
			byte_t const *cu_start;
			cu_start = self->cm_sections.ds_debug_info_start + debuginfo_cu_offset;
			result = cmodule_findunit_from_dip(self, cu_start);
		}
	}
	/* Fallback */
	result = cmodule_findunit_from_pc_fallback(self, module_relative_pc);
	return result;
}


/* Try to find the compilation unit that contains `dip'
 * If no such unit can be located, `NULL' will be returned instead. */
PUBLIC WUNUSED ATTR_PURE NONNULL((1)) struct cmodunit *
NOTHROW(FCALL cmodule_findunit_from_dip)(struct cmodule const *__restrict self,
                                         byte_t const *__restrict dip) {
	struct cmodunit const *result;
	size_t lo, hi;
	lo = 0, hi = self->cm_cuc;
	while (lo < hi) {
		size_t index;
		index  = (lo + hi) / 2;
		result = &self->cm_cuv[index];
		if (dip < cmodunit_di_start(result))
			hi = index;
		else if (dip > cmodunit_di_end(result))
			lo = index + 1;
		else {
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
	if (strlen(info->clv_symbol.cms_name) != arg->namelen)
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
	/* Enumerate symbols with the help enumeration function.
	 * Note that we pass the given `name' as startswith-request, such
	 * that only strings that being with the given name are enumerated.
	 * We then further restrict enumeration within our callback by requiring
	 * that the name of the symbol we actually end up using has a length
	 * that is identical to `namelen' */
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
		/* Custom error code override (e.g. DBX_EINTR or DBX_ENOMEM).
		 * In general, these errors all originate from `cmodule_loadsyms()' */
		data.error = error;
	}
	return data.error;
}

/* Same as `cmod_syminfo()', but the caller is not required to fill in information
 * about any symbol at all, which are automatically loaded based on `dbg_current',
 * as well as `dbg_getpcreg(DBG_REGLEVEL_VIEW)'. However, upon success, the caller
 * is required to call `cmod_syminfo_local_fini(info)' once returned information
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
	pc = (void const *)dbg_getpcreg(DBG_REGLEVEL_VIEW);
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
		memset(&info->clv_data.s_var.v_location, 0, sizeof(info->clv_data.s_var.v_location));
}

PRIVATE NONNULL((1, 2)) void
NOTHROW(FCALL loadinfo_const_value)(di_debuginfo_cu_parser_t const *__restrict parser,
                                    struct cmodsyminfo *__restrict info,
                                    uintptr_t form) {
	uintptr_t value;
	di_debuginfo_block_t block;
	if (debuginfo_cu_parser_getconst(parser, form, &value)) {
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
                                       byte_t const *__restrict specification) {
	di_debuginfo_cu_parser_t inner_parser;
	di_debuginfo_component_attrib_t attr;
	memcpy(&inner_parser, &info->clv_parser, sizeof(inner_parser));
	inner_parser.dup_cu_info_pos = specification;
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
					inner_parser.dup_cu_info_pos = abstract_origin;
					goto again;
				}	break;

				case DW_AT_type:
					loadinfo_type(&inner_parser, info, attr.dica_form);
					break;

				case DW_AT_location:
					loadinfo_location(&inner_parser, info, attr.dica_form);
					break;

				case DW_AT_const_value:
					loadinfo_const_value(&inner_parser, info, attr.dica_form);
					break;

				default:
					break;
				}
			}
		}
	}
}

/* To-be called from inside of `cmod_symenum_callback_t' when
 * `info_loaded == false', and extended symbol information is
 * needed. */
PUBLIC NONNULL((1)) void
NOTHROW(FCALL cmod_symenum_loadinfo)(struct cmodsyminfo *__restrict info) {
	memset(&info->clv_data, 0, sizeof(info->clv_data));
	if (!info->clv_unit) {
		/* Lookup the appropriate compilation unit. */
		info->clv_unit = cmodule_findunit_from_dip(info->clv_mod,
		                                           cmodsyminfo_getdip(info));
		if unlikely(!info->clv_unit) {
			/* Shouldn't happen... (fill in stub-data) */
			memset(&info->clv_cu, 0, sizeof(info->clv_cu));
			memset(&info->clv_parser, 0, sizeof(info->clv_parser));
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
			memset(&info->clv_cu, 0, sizeof(info->clv_cu));
			goto do_load_dip;
		}
	}

	/* Load attributes for the associated CU */
	if (!debuginfo_cu_parser_loadattr_compile_unit(&info->clv_parser,
	                                               &info->clv_cu))
		memset(&info->clv_cu, 0, sizeof(info->clv_cu));

	/* Load symbol-specific debug information. */
do_load_dip:
	info->clv_parser.dup_cu_info_pos = cmodsyminfo_getdip(info);
	if (!debuginfo_cu_parser_next(&info->clv_parser)) {
		/* Fill in a stub/EOF component. */
		info->clv_parser.dup_comp.dic_tag         = 0; /* DW_TAG_... */
		info->clv_parser.dup_comp.dic_haschildren = DW_CHILDREN_no;
		info->clv_parser.dup_cu_info_pos = info->clv_parser.dup_cu_info_end;
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
				info->clv_parser.dup_cu_info_pos = abstract_origin;
				if unlikely(!debuginfo_cu_parser_next(&info->clv_parser))
					goto done_attributes;
				goto again_attributes;
			}	break;

			case DW_AT_location:
				loadinfo_location(&info->clv_parser, info, attr.dica_form);
				break;

			case DW_AT_const_value:
				loadinfo_const_value(&info->clv_parser, info, attr.dica_form);
				break;

			case DW_AT_type:
				loadinfo_type(&info->clv_parser, info, attr.dica_form);
				break;

			case DW_AT_sibling:
			case DW_AT_specification: {
				byte_t const *spec;
				if likely(debuginfo_cu_parser_getref(&info->clv_parser, attr.dica_form, &spec))
					loadinfo_specifications(info, spec);
			}	break;

			case DW_AT_low_pc:
			case DW_AT_entry_pc: {
				uintptr_t addr;
				if likely(debuginfo_cu_parser_getaddr(&info->clv_parser, attr.dica_form,
				                                      &addr))
					info->clv_data.s_var.v_objaddr = (void *)addr;
			}	break;

			default:
				break;
			}
		}
	}
done_attributes:
	;
}

/* Return non-zero if the name of the given `sym' starts with the given name. */
#define cmodsym_name_startswith(sym, startswith_name, startswith_namelen) \
	(strlen((sym)->cms_name) >= (startswith_namelen) &&                   \
	 memcmp((sym)->cms_name, startswith_name, (startswith_namelen) * sizeof(char)) == 0)


/* Enumerate symbols from `self'. When a symbol is encountered that stands in
 * conflict with some other symbol, try to resolve the conflict by looking at
 * the secondary symbol table `fallback_cu->cu_symbols'. If that table contains
 * another symbol with the same name, then that symbol will be enumerated, instead. */
PRIVATE NONNULL((1, 2, 3)) ssize_t
NOTHROW(FCALL cmod_symenum_symtab)(struct cmodsymtab const *__restrict self,
                                   /*in|out(undef)*/ struct cmodsyminfo *__restrict info,
                                   cmod_symenum_callback_t cb, char const *startswith_name,
                                   size_t startswith_namelen, uintptr_t ns,
                                   struct cmodunit const *fallback_cu) {
	ssize_t temp, result = 0;
	size_t enum_lo, enum_hi;
	size_t index;
	enum_lo = 0;
	enum_hi = self->mst_symc;
	/* Do a binary search to narrow down the range of symbols that should be enumerated. */
	for (;;) {
		char const *symbol_name;
		size_t symbol_namelen;
		int cmp;
		if (enum_lo >= enum_hi)
			goto done;
		index          = (enum_lo + enum_hi) / 2;
		symbol_name    = self->mst_symv[index].cms_name;
		symbol_namelen = strlen(symbol_name);
		if (symbol_namelen < startswith_namelen) {
			cmp = memcmp(startswith_name, symbol_name, symbol_namelen * sizeof(char));
			if (cmp == 0)
				cmp = -1; /* (startswith_name[symbol_namelen]!=0) < (symbol_name[symbol_namelen]==0) */
		} else {
			cmp = memcmp(startswith_name, symbol_name, startswith_namelen * sizeof(char));
			/* When `cmp == 0' at this point, then we've located a symbol
			 * that starts with the given `startswith_name' string! */
		}
		if (cmp < 0) {
			enum_hi = index;
		} else if (cmp > 0) {
			enum_lo = index + 1;
		} else {
			/* Found some symbol `self->mst_symv[index]' that matches our starts-with pattern. */
			break;
		}
	}
	/* Go backwards/forwards until we find the last symbol that matches our starts-with pattern. */
	enum_lo = enum_hi = index;
	while (enum_lo > 0 &&
	       cmodsym_name_startswith(&self->mst_symv[enum_lo - 1],
	                               startswith_name,
	                               startswith_namelen))
		--enum_lo;
	while (enum_hi < self->mst_symc - 1 &&
	       cmodsym_name_startswith(&self->mst_symv[enum_hi + 1],
	                               startswith_name,
	                               startswith_namelen))
		++enum_hi;
	/* At this point, we've narrowed down the range of symbols to enumerate
	 * to those found at indices [enum_lo, enum_hi] (inclusively)
	 * Now to actually enumerate them! */
	for (index = enum_lo; index <= enum_hi; ++index) {
		struct cmodsym *sym;
		sym = &self->mst_symv[index];

		/* Check if we're actually supposed to enumerate this symbol. */
		if (!want_symbol(sym, ns))
			continue;

		/* Check if the symbol stands in conflict with something else. */
		if (cmodsym_getns(sym) & CMODSYM_DIP_NS_FCONFLICT) {
			/* If we've been given a custom CU, check if it contains another version of this symbol. */
			if (fallback_cu) {
				struct cmodsym *percu_sym;
				percu_sym = cmodsymtab_lookup(&fallback_cu->cu_symbols,
				                              sym->cms_name,
				                              strlen(sym->cms_name),
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
	result = cmod_symenum_symtab(&info->clv_mod->cm_symbols, info, cb,
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
		                              /* Indicate that we don't want to enumerate symbols
		                               * from some specific CU, but only those that are
		                               * globally visible, and don't conflict with each other.
		                               * If this was non-NULL, the pointed-to CU would be
		                               * used when trying to resolve conflicting symbols. */
		                              NULL);
	}
	return result;
}


/* Enumerate local variables from the currently loaded CU */
PRIVATE ATTR_NOINLINE NONNULL((1, 2)) ssize_t
NOTHROW(FCALL cmod_symenum_locals_from_cu)(/*in|out(undef)*/ struct cmodsyminfo *__restrict info,
                                           cmod_symenum_callback_t cb, char const *startswith_name,
                                           size_t startswith_namelen, uintptr_t ns) {
	unsigned int error;
	ssize_t temp, result = 0;
	uintptr_t cu_depth;
	cu_depth = info->clv_parser.dup_child_depth;
	if (!debuginfo_cu_parser_next(&info->clv_parser))
		goto done;
again_cu_component:
	while (info->clv_parser.dup_child_depth > cu_depth) {
		if (dbg_awaituser())
			goto done;
		/* Scan components of this CU. */
		switch (info->clv_parser.dup_comp.dic_tag) {

		case DW_TAG_subprogram: {
			di_debuginfo_subprogram_t sp;
			uintptr_t subprogram_depth;
			if (!debuginfo_cu_parser_loadattr_subprogram(&info->clv_parser, &sp))
				goto generic_cu_child;
			subprogram_depth = info->clv_parser.dup_child_depth;
			/* Check if the given pointer is apart of this sub-program. */
			error = debuginfo_ranges_contains(&sp.sp_ranges, &info->clv_parser,
			                                  info->clv_cu.cu_ranges.r_startpc,
			                                  info->clv_modrel_pc,
			                                  info->clv_mod->cm_sections.ds_debug_ranges_start,
			                                  info->clv_mod->cm_sections.ds_debug_ranges_end);
			if (error != DEBUG_INFO_ERROR_SUCCESS) {
				/* Must be apart of a different sub-program. */
				for (;;) {
					if (!debuginfo_cu_parser_next(&info->clv_parser))
						goto done;
					if (info->clv_parser.dup_child_depth <= subprogram_depth)
						goto again_cu_component;
					debuginfo_cu_parser_skipattr(&info->clv_parser);
				}
			}
			for (;;) {
				byte_t const *dip;
				dip = info->clv_parser.dup_cu_info_pos;
				if (!debuginfo_cu_parser_next(&info->clv_parser))
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
					if (ns != CMODSYM_DIP_NS_NORMAL)
						goto skip_in_cu_tag_attr;
					if (debuginfo_cu_parser_loadattr_variable(&info->clv_parser, &var)) {
						if (!var.v_rawname)
							var.v_rawname = var.v_name;
						/* Only enumerate symbols that actually have a name! */
						if (var.v_rawname) {
							/* Check if the selected variable name matches our starts-with pattern. */
							size_t varname_len;
							varname_len = strlen(var.v_rawname);
							if (varname_len >= startswith_namelen &&
							    memcmp(var.v_rawname, startswith_name,
							           startswith_namelen * sizeof(char)) == 0) {
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
									goto err;
								result += temp;
							}
						}
					}
				}	break;

				case DW_TAG_inlined_subroutine:
				case DW_TAG_try_block:
				case DW_TAG_catch_block:
				case DW_TAG_lexical_block: {
					di_debuginfo_lexical_block_t block;
					if (debuginfo_cu_parser_loadattr_lexical_block(&info->clv_parser, &block)) {
						error = debuginfo_ranges_contains(&block.lb_ranges, &info->clv_parser,
						                                  info->clv_cu.cu_ranges.r_startpc,
						                                  info->clv_modrel_pc,
						                                  info->clv_mod->cm_sections.ds_debug_ranges_start,
						                                  info->clv_mod->cm_sections.ds_debug_ranges_end);
						if (error != DEBUG_INFO_ERROR_SUCCESS) {
							/* Must be apart of a different scope. */
							uintptr_t block_depth;
							block_depth = info->clv_parser.dup_child_depth;
							for (;;) {
								dip = info->clv_parser.dup_cu_info_pos;
								if (!debuginfo_cu_parser_next(&info->clv_parser))
									goto done;
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
			goto done;
		}	break;

		default:
generic_cu_child:
			debuginfo_cu_parser_skipattr(&info->clv_parser);
/*next_cu_component:*/
			if (!debuginfo_cu_parser_next(&info->clv_parser))
				goto done;
			break;
		}
	}
done:
	return result;
err:
	return temp;
}


/* Enumerate local variables from the selected CU */
PRIVATE ATTR_NOINLINE NONNULL((1, 2)) ssize_t
NOTHROW(FCALL cmod_symenum_locals)(/*in|out(undef)*/ struct cmodsyminfo *__restrict info,
                                   cmod_symenum_callback_t cb, char const *startswith_name,
                                   size_t startswith_namelen, uintptr_t ns) {
	ssize_t temp, result = 0;
	/* Initialize the parser. */
	cmodunit_parser_from_dip(info->clv_unit, info->clv_mod, &info->clv_parser, NULL);
again:
	if (dbg_awaituser()) {
		result = DBX_EINTR;
	} else {
		switch (info->clv_parser.dup_comp.dic_tag) {
	
		case DW_TAG_compile_unit:
			/* Load attributes for this CU. */
			if (!debuginfo_cu_parser_loadattr_compile_unit(&info->clv_parser,
			                                               &info->clv_cu))
				break;
			info->clv_parser.dup_comp.dic_tag = 0; /* Prevent infinite recursion on error. */
			/* Enumerate with information from this CU. */
			temp = cmod_symenum_locals_from_cu(info, cb,
			                                   startswith_name,
			                                   startswith_namelen,
			                                   ns);
			if unlikely(temp < 0)
				goto err;
			result += temp;
			/* Check for secondary CUs (although those really shouldn't exist...) */
			goto again;
	
		default:
			/* Skip unexpected components. */
			debuginfo_cu_parser_skipattr(&info->clv_parser);
			if (debuginfo_cu_parser_next(&info->clv_parser))
				goto again;
			break;
		}
	}
	return result;
err:
	return temp;
}


/* From the point of view of `cmod_syminfo()', enumerate all symbols who's names
 * start with `startswith_name...+=startswith_namelen'. When `startswith_namelen==0',
 * all symbols are enumerated.
 * Also note that this function may sporadically stop enumeration before being finished,
 * even when `cb' didn't indicate a negative return value when `dbg_awaituser()' returns
 * true, which is handled the same as enumeration completing normally.
 * NOTE: The `out(undef)' that all non-[const] fields are undefined upon return,
 *       with the exception of out-of-band fields (if any), who's contents depends
 *       on what `cb' may or may not have done.
 * @param: info:  Specifications for where to look for symbols, as well as a cookie-pointer
 *                that is passed to `cb' during invocation (the caller may embed the symbol
 *                info descriptor inside of a larger structure which can then be re-accessed
 *                via `container_of' from inside of `cb', thus allowing additional arguments
 *                to be passed to the callback function)
 *                The caller must fill in `clv_mod', `clv_unit' and `clv_modrel_pc' before
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
			 *       is used by this function to resolve conflicting symbols. */
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
		 * and recursively enumerate their symbols. */
		temp = cmodule_enum(&cmod_symenum_foreign_globals_cb, &data);
		xdecref(data.excluded_module);
		if unlikely(temp < 0)
			goto err;
		result += temp;
		did_encounter_nomem = data.did_encounter_nomem;
	}
	/* If (seemingly) nothing was enumerated, and we did
	 * encounter an out-of-memory error at one point, then
	 * propagate that error to the caller. */
	if (result == 0 && did_encounter_nomem)
		result = DBX_ENOMEM;
	return result;
err:
	return temp;
}

/* Same as `cmod_symenum()', except this function automatically manages the
 * input fields of `info' which must normally be filled in by the caller, and
 * will instead fill them in itself, as well as clean them up afterwards.
 * NOTE: _DONT_ call `cmod_syminfo_local_fini(info)' after this function returns!
 *       Any cleanup will have already been done internally by this function!
 * NOTE: The `in(oob_only)' means that only out-of-band data that is used by `cb'
 *       must be initialized prior to this function being called.
 * NOTE: The `out(undef)' that all non-[const] fields are undefined upon return,
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
	pc = (void const *)dbg_getpcreg(DBG_REGLEVEL_VIEW);
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
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_CMODULE_C */
