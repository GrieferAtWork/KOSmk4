/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_DEBUGGER_HOOK_C
#define GUARD_KERNEL_SRC_DEBUGGER_HOOK_C 1
#define DISABLE_BRANCH_PROFILING
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/hook.h>
#include <debugger/rt.h>
#include <kernel/except.h>
#include <kernel/mman.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/phys.h>

#include <hybrid/overflow.h>

#include <asm/intrin.h> /* __flush_instruction_cache */

#include <stddef.h>
#include <string.h>

DECL_BEGIN

PRIVATE ATTR_DBGTEXT ATTR_PURE WUNUSED NONNULL((1)) uintptr_t FCALL
dbg_hookiterator_current_driver_loadaddr(struct dbg_hookiterator const *__restrict self) {
	uintptr_t result;
	struct driver *drv;
	NESTED_TRY {
		if unlikely(!self->dhi_nextdriver)
			return 0; /* Kernel core. */
		if unlikely(self->dhi_nextdriver > self->dhi_drivers->dll_count)
			return 0; /* Shouldn't happen! */
		drv = self->dhi_drivers->dll_drivers[self->dhi_nextdriver - 1];
		if unlikely(!ADDR_ISKERN(drv))
			return 0; /* Shouldn't happen! */
		if unlikely(wasdestroyed(drv))
			return 0; /* Driver has been unloaded */
		result = drv->md_loadaddr;
	} EXCEPT { /* Shouldn't happen */
		if (dbg_active)
			return 0;
		RETHROW();
	}
	return result;
}


PRIVATE ATTR_DBGSTRINGS char const str_dbg_hooks[] = DBG_SECTION_HOOKS;

/* Overwrite `dst' with `src' */
PRIVATE ATTR_DBGTEXT ATTR_NOINLINE bool FCALL
dbg_overwrite_bytes(void const *dst,
                    void const *src,
                    size_t num_bytes) {
	bool result = false;
	physaddr_t phys;
	if (!dbg_active)
		mman_lock_acquire(&mman_kernel);
	if (!pagedir_ismapped(dst))
		goto done;
	while (num_bytes) {
		size_t max_copy, do_copy;
		max_copy = PAGESIZE - ((uintptr_t)dst & PAGEMASK);
		do_copy  = max_copy;
		if (do_copy > num_bytes)
			do_copy = num_bytes;
		phys = pagedir_translate(dst);
		copytophys(phys, src, do_copy);
		if (do_copy >= num_bytes)
			break;
		dst = (byte_t *)dst + do_copy;
		src = (byte_t const *)src + do_copy;
		num_bytes -= do_copy;
	}
	result = true;
done:
	if (!dbg_active)
		mman_lock_release(&mman_kernel);
	/* This flush is required because we used an aliasing
	 * memory mapping to override the hook's actual data. */
	COMPILER_BARRIER();
	__flush_instruction_cache();
	COMPILER_BARRIER();
	return result;
}

/* Overwrite `self' with `newdata' */
PRIVATE ATTR_DBGTEXT bool FCALL
dbg_overwrite(struct dbg_hookhdr const *__restrict self,
              struct dbg_hookhdr const *__restrict newdata) {
	return dbg_overwrite_bytes(self, newdata, newdata->dh_size);
}

PRIVATE ATTR_DBGTEXT ATTR_NOINLINE bool FCALL
dbg_relocate_hookpointers(struct dbg_hookhdr const *__restrict self,
                          uintptr_t loadaddr, bool selfrel) {
	bool result;
	switch (self->dh_type) {

	case DBG_HOOK_COMMAND: {
		struct dbg_commandhook const *me;
		struct dbg_commandhook newme;
		me = (struct dbg_commandhook const *)self;
		if unlikely(me->dc_size < offsetafter(struct dbg_commandhook, dc_main) ||
		            me->dc_size > offsetafter(struct dbg_commandhook, dc_auto))
			goto err;
		newme.dc_type = DBG_HOOK_COMMAND;
		newme.dc_flag = me->dc_flag & ~(DBG_HOOKFLAG_RELATIVE | DBG_HOOKFLAG_OFFSET);
		newme.dc_size = me->dc_size;
		newme.dc_name = (char *)((byte_t *)me->dc_name + loadaddr);
		if (selfrel)
			newme.dc_name = (char *)((uintptr_t)&me->dc_name + (uintptr_t)newme.dc_name);
		if unlikely(!ADDR_ISKERN(newme.dc_name))
			goto err; /* Shouldn't happen */
		*(void **)&newme.dc_main = (void *)((byte_t *)(*(void **)&me->dc_main) + loadaddr);
		if (selfrel)
			*(void **)&newme.dc_main = (void *)((uintptr_t)(*(void **)&newme.dc_main) + (uintptr_t)&me->dc_main);
		if unlikely(!ADDR_ISKERN(*(void **)&newme.dc_main))
			goto err; /* Shouldn't happen */
		if (newme.dc_size >= offsetafter(struct dbg_commandhook, dc_help)) {
			newme.dc_help = (char *)((byte_t *)me->dc_help + loadaddr);
			if (selfrel)
				newme.dc_help = (char *)((uintptr_t)newme.dc_help + (uintptr_t)&me->dc_help);
			if unlikely(newme.dc_help && !ADDR_ISKERN(newme.dc_help))
				goto err; /* Shouldn't happen */
			if (newme.dc_size >= offsetafter(struct dbg_commandhook, dc_auto)) {
				*(void **)&newme.dc_auto = (char *)((byte_t *)(*(void **)&me->dc_auto) + loadaddr);
				if (selfrel)
					*(void **)&newme.dc_auto = (void *)((uintptr_t)(*(void **)&newme.dc_auto) + (uintptr_t)&me->dc_auto);
				if unlikely(newme.dc_auto && !ADDR_ISKERN(*(void **)&newme.dc_auto))
					goto err; /* Shouldn't happen */
			}
		}
		result = dbg_overwrite((struct dbg_hookhdr *)me,
		                       (struct dbg_hookhdr *)&newme);
	}	break;

	case DBG_HOOK_INIT:
	case DBG_HOOK_RESET:
	case DBG_HOOK_FINI: {
		struct dbg_inithook const *me;
		struct dbg_inithook newme;
		me = (struct dbg_inithook const *)self;
		if unlikely(me->di_size != sizeof(newme))
			goto err;
		newme.di_type = me->di_type;
		newme.di_flag = me->di_flag & ~(DBG_HOOKFLAG_RELATIVE | DBG_HOOKFLAG_OFFSET);
		newme.di_size = sizeof(newme);
		*(void **)&newme.di_func = (char *)((byte_t *)(*(void **)&me->di_func) + loadaddr);
		if (selfrel)
			*(void **)&newme.di_func = (char *)((byte_t *)(*(void **)&newme.di_func) + (uintptr_t)&me->di_func);
		if unlikely(!ADDR_ISKERN(*(void **)&newme.di_func))
			goto err; /* Shouldn't happen */
		result = dbg_overwrite((struct dbg_hookhdr *)me,
		                       (struct dbg_hookhdr *)&newme);
	}	break;

	case DBG_HOOK_CLEAR: {
		struct dbg_clearhook const *me;
		struct {
			dbg_hook_type_t dc_type; /* == DBG_HOOK_CLEAR */
			dbg_hook_flag_t dc_flag; /* ... */
			dbg_hook_size_t dc_size; /* == offsetof(struct dbg_clearhook, dc_data) + CLEAR_OBJECT_SIZE */
			void           *dc_cobj; /* [1..1][const] Pointer to the object that should be cleared. */
		} newme;
		me = (struct dbg_clearhook const *)self;
		if unlikely(me->dc_size < offsetafter(struct dbg_clearhook, dc_cobj))
			goto err;
		newme.dc_type = DBG_HOOK_CLEAR;
		newme.dc_flag = me->dc_flag & ~(DBG_HOOKFLAG_RELATIVE | DBG_HOOKFLAG_OFFSET);
		newme.dc_size = me->dc_size;
		newme.dc_cobj = (void *)((byte_t *)me->dc_cobj + loadaddr);
		if (selfrel)
			newme.dc_cobj = (void *)((uintptr_t)newme.dc_cobj + (uintptr_t)&me->dc_cobj);
		if unlikely(!ADDR_ISKERN(newme.dc_cobj))
			goto err; /* Shouldn't happen */
		result = dbg_overwrite_bytes(me, &newme, sizeof(newme));
	}	break;

	default:
		result = true;
		break;
	}
	return result;
err:
	return false;
}


/* Return a pointer to the next debugger hook, or `NULL' if the iterator has been exhausted. */
PUBLIC ATTR_DBGTEXT WUNUSED NONNULL((1)) struct dbg_hookhdr const *FCALL
dbg_hookiterator_next(struct dbg_hookiterator *__restrict self) {
	struct dbg_hookhdr *result;
	struct dbg_hookhdr *next;
	NESTED_TRY {
again:
		result = self->dhi_sectnext;
		if (result >= self->dhi_sectend) {
end_of_section:
			/* End-of-section. (try to return from a `DBG_HOOK_MORE' hook) */
			if (self->dhi_sectprev != NULL) {
				self->dhi_sectnext = self->dhi_sectprev;
				self->dhi_sectprev = NULL;
				if unlikely(!ADDR_ISKERN(self->dhi_section))
					goto end_of_driver; /* Shouldn't happen */
				if unlikely(!ADDR_ISKERN(self->dhi_section->ds_addr))
					goto end_of_driver; /* Shouldn't happen */
				if unlikely((byte_t *)self->dhi_sectnext < (byte_t *)self->dhi_section->ds_addr)
					goto end_of_driver; /* Shouldn't happen */
load_section_end_and_read_first_item:
				self->dhi_sectend = (struct dbg_hookhdr *)((byte_t *)self->dhi_section->ds_addr +
				                                           self->dhi_section->ms_size);
				if unlikely(!ADDR_ISKERN(self->dhi_sectend))
					goto end_of_driver; /* Shouldn't happen */
				goto again;
			}
end_of_driver:
			if unlikely(!ADDR_ISKERN(self->dhi_drivers))
				goto end_of_everything; /* Shouldn't happen */
			if (self->dhi_nextdriver >= self->dhi_drivers->dll_count) {
end_of_everything:
				return NULL;
			}
			{
				struct driver *next_driver;
				REF struct driver_section *sect;
				next_driver = self->dhi_drivers->dll_drivers[self->dhi_nextdriver];
				++self->dhi_nextdriver;
				if unlikely(next_driver == &kernel_driver)
					goto end_of_driver; /* The kernel core is always enumerated
					                     * first, and was thus already handled. */
				if unlikely(!ADDR_ISKERN(next_driver))
					goto end_of_driver; /* Shouldn't happen */
				if unlikely(wasdestroyed(next_driver))
					goto end_of_driver; /* Destroyed driver. */
				sect = (REF struct driver_section *)module_locksection(next_driver, str_dbg_hooks);
				if (!sect)
					goto end_of_driver; /* This driver doesn't export debugger hooks. */
				if unlikely(!ADDR_ISKERN(self->dhi_section->ds_addr) || self->dhi_section->ds_addr == (byte_t *)-1)
					goto end_of_driver; /* This might happen when the .dbg.hooks section isn't loaded into memory. */
				/* Use the new section. */
				decref_unlikely(self->dhi_section);
				self->dhi_section = sect; /* Inherit reference */
			}
			self->dhi_sectnext = (struct dbg_hookhdr *)self->dhi_section->ds_addr;
			goto load_section_end_and_read_first_item;
		}
		if (OVERFLOW_UADD((uintptr_t)result, result->dh_size, (uintptr_t *)&next) ||
		    (byte_t *)next > (byte_t *)self->dhi_sectend)
			goto end_of_section;
		self->dhi_sectnext = next;
		if (result->dh_type == DBG_HOOK_MORE) {
			struct dbg_hookhdr *inner;
			struct dbg_morehook *morehook;
			morehook = (struct dbg_morehook *)result;
			if unlikely(self->dhi_sectprev != NULL)
				goto again; /* Already iterating a MORE-hook (don't allow for recursion!) */
			inner = morehook->dm_more;
			if (morehook->dm_flag & DBG_HOOKFLAG_RELATIVE) {
				inner = (struct dbg_hookhdr *)((uintptr_t)inner + dbg_hookiterator_current_driver_loadaddr(self));
			} else if (morehook->dm_flag & DBG_HOOKFLAG_OFFSET) {
				inner = (struct dbg_hookhdr *)((uintptr_t)&morehook->dm_more + (uintptr_t)inner);
			}
			if unlikely(!ADDR_ISKERN(inner))
				goto again; /* Shouldn't happen. */
			if unlikely(morehook->dm_limt < offsetof(struct dbg_hookhdr, dh_data))
				goto again; /* Shouldn't happen. */
			self->dhi_sectprev = self->dhi_sectnext;
			self->dhi_sectnext = inner;
			self->dhi_sectend  = (struct dbg_hookhdr *)((byte_t *)inner + morehook->dm_limt);
			goto again;
		}
		if unlikely(result->dh_flag & (DBG_HOOKFLAG_RELATIVE | DBG_HOOKFLAG_OFFSET)) {
			/* Lazily relocate module-relative hook pointers on first access. */
			uintptr_t loadaddr;
			loadaddr = dbg_hookiterator_current_driver_loadaddr(self);
			if unlikely(loadaddr == 0 && !(result->dh_flag & DBG_HOOKFLAG_OFFSET)) {
				/* Nothing to do! (try to delete the RELATIVE flag, but ignore failure to do so) */
				dbg_hook_flag_t new_flags;
				new_flags = result->dh_flag & ~(DBG_HOOKFLAG_RELATIVE | DBG_HOOKFLAG_OFFSET);
				dbg_overwrite_bytes(&result->dh_flag, &new_flags,
				                    sizeof(dbg_hook_flag_t));
			} else {
				if (!dbg_relocate_hookpointers(result, loadaddr,
				                               (result->dh_flag & DBG_HOOKFLAG_OFFSET) != 0))
					goto again;
			}
		}

	} EXCEPT { /* Shouldn't happen */
		if (dbg_active)
			return NULL;
		RETHROW();
	}
	return result;
}

/* Same as `dbg_hookiterator_next()', but skip all hooks of a different type than `type' */
PUBLIC ATTR_DBGTEXT WUNUSED NONNULL((1)) struct dbg_hookhdr const *FCALL
dbg_hookiterator_next_filtered(struct dbg_hookiterator *__restrict self,
                               dbg_hook_type_t type) {
	struct dbg_hookhdr const *result;
	for (;;) {
		result = dbg_hookiterator_next(self);
		if (!result)
			break; /* No more hooks. */
		if (result->dh_type == type)
			break; /* Hook of requested type found. */
	}
	return result;
}

/* Returns the driver currently being iterated. */
PUBLIC ATTR_DBGTEXT ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) struct driver *FCALL
dbg_hookiterator_driver(struct dbg_hookiterator const *__restrict self) {
	struct driver *drv = &kernel_driver;
	NESTED_TRY {
		if unlikely(!self->dhi_nextdriver)
			goto done; /* Kernel core. */
		if unlikely(self->dhi_nextdriver > self->dhi_drivers->dll_count)
			goto done; /* Shouldn't happen! */
		drv = self->dhi_drivers->dll_drivers[self->dhi_nextdriver - 1];
		if unlikely(!ADDR_ISKERN(drv))
			drv = &kernel_driver; /* Shouldn't happen! */
		if unlikely(wasdestroyed(drv))
			drv = &kernel_driver; /* Shouldn't happen! */
	} EXCEPT { /* Shouldn't happen */
		if (dbg_active)
			goto done;
		RETHROW();
	}
done:
	return drv;
}


/* Search for a debug command matching the given name.
 * @return: NULL: No command exists that matches `name' */
PUBLIC ATTR_PURE WUNUSED NONNULL((1)) struct dbg_commandhook const *FCALL
dbg_lookup_command(char const *__restrict name) {
	struct dbg_commandhook const *result;
	struct dbg_hookiterator iter;
	dbg_hookiterator_init(&iter);
	for (;;) {
		result = DBG_HOOKITERATOR_NEXT_FILTERED(&iter, DBG_HOOK_COMMAND);
		if (!result)
			break;
		if (strcmp(result->dc_name, name) == 0)
			break; /* Found it! */
	}
	dbg_hookiterator_fini(&iter);
	return result;
}

/* Search for a debug function matching the given name most closely. */
PUBLIC ATTR_PURE WUNUSED NONNULL((1)) struct dbg_commandhook const *FCALL
dbg_lookup_command_fuzzy(char const *__restrict similar_to_name) {
	struct dbg_commandhook const *result = NULL;
	struct dbg_commandhook const *current;
	struct dbg_hookiterator iter;
	size_t result_score = (size_t)-1;
	dbg_hookiterator_init(&iter);
	for (;;) {
		size_t score;
		current = DBG_HOOKITERATOR_NEXT_FILTERED(&iter, DBG_HOOK_COMMAND);
		if (!current)
			break;
		score = fuzzy_strcasecmp(current->dc_name,
		                         similar_to_name);
		if (!result || score < result_score) {
			result       = current;
			result_score = score;
			if (!result_score)
				break; /* Perfect score */
		}
	}
	dbg_hookiterator_fini(&iter);
	return result;
}


/* Search  for  a  debug  command   who's  name  starts  with   `name'.
 * If more than one command matches this criteria, return NULL instead. */
PUBLIC ATTR_PURE WUNUSED NONNULL((1)) struct dbg_commandhook const *FCALL
dbg_lookup_command_startswith(char const *__restrict name_start) {
	struct dbg_commandhook const *result = NULL;
	struct dbg_commandhook const *current;
	struct dbg_hookiterator iter;
	size_t name_start_len = strlen(name_start);
	dbg_hookiterator_init(&iter);
	for (;;) {
		size_t hooknamelen;
		current = DBG_HOOKITERATOR_NEXT_FILTERED(&iter, DBG_HOOK_COMMAND);
		if (!current)
			break;
		hooknamelen = strlen(current->dc_name);
		if (hooknamelen < name_start_len)
			continue;
		if (bcmp(current->dc_name, name_start, hooknamelen, sizeof(char)) != 0)
			continue;
		if (result)
			return NULL; /* Ambiguous */
		result = current;
	}
	dbg_hookiterator_fini(&iter);
	return result;
}



DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_HOOK_C */
