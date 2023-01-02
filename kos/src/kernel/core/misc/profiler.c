/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MISC_PROFILER_C
#define GUARD_KERNEL_SRC_MISC_PROFILER_C 1
#define DISABLE_BRANCH_PROFILING /* Don't profile ourself! */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/mman/driver.h>
#include <kernel/printk.h>
#include <kernel/profiler.h>
#include <kernel/types.h>

#include <inttypes.h>
#include <string.h>

DECL_BEGIN

/* Branch predictions for the kernel core. */
INTDEF ATTR_WEAK struct branch_prediction kernel_profile_branch_start[];
INTDEF ATTR_WEAK struct branch_prediction kernel_profile_branch_end[];
INTDEF ATTR_WEAK struct branch_prediction kernel_profile_branch_annotated_start[];
INTDEF ATTR_WEAK struct branch_prediction kernel_profile_branch_annotated_end[];


/* Invoke `cb()' for all traced branches from all drivers, as well as the kernel core.
 * NOTE: Branch  enumeration is sorted  by individual drivers, in  that all branches of
 *       one driver are enumerated before any branch from another driver is enumerated.
 *       The order in which branches of individual drivers are enumerated is undefined,
 *       however any branch will only ever be enumerated once. Similarly, the order  in
 *       which individual drivers are enumerated is also undefined.
 * @param: cb:    The callback to-be invoked.
 * @param: arg:   Argument passed to `cb()'
 * @return: >= 0: The sum of all return values returned by `cb()'
 * @return: < 0:  The first negative return value returned by `cb()' */
PUBLIC NONNULL((1)) ssize_t KCALL
branchstat(branchstat_callback_t cb, void *arg) {
	ssize_t result;
	/* Enumerate the kernel core. */
	result = branchstat_d(cb, arg, &kernel_driver);
	if likely(result >= 0) {
		REF struct driver_loadlist *dll;
		size_t i;
		/* Enumerate all loaded drivers. */
		dll = get_driver_loadlist();
		FINALLY_DECREF_UNLIKELY(dll);
		for (i = 0; i < dll->dll_count; ++i) {
			ssize_t temp;
			struct driver *drv;
			drv = dll->dll_drivers[i];
			if unlikely(!tryincref(drv))
				continue; /* Dead driver... */
			{
				FINALLY_DECREF_UNLIKELY(drv);
				temp = branchstat_d(cb, arg, drv);
			}
			if unlikely(temp < 0) {
				result = temp;
				break;
			}
			result += temp;
		}
	}
	return result;
}

PRIVATE NONNULL((1, 3)) ssize_t KCALL
branchstat_listone(branchstat_callback_t cb, void *arg,
                   struct driver *__restrict mod,
                   struct branch_prediction const *__restrict pred,
                   bool annotated, bool is_driver) {
	ssize_t result;
	struct branch_prediction used_pred;
	memcpy(&used_pred, pred, sizeof(used_pred));
	/* In drivers, branch predictions contain driver-relative addresses.
	 * Hide this detail from `cb()' and pass a relocated copy of  `pred' */
	if (is_driver) {
		used_pred.bp_addr = (__BRANCH_PREDITION_ADDRESS_TYPE)((uintptr_t)used_pred.bp_addr +
		                                                      mod->md_loadaddr);
	}
	result = (*cb)(arg, mod, &used_pred, annotated);
	return result;
}

PRIVATE NONNULL((1, 3)) ssize_t KCALL
branchstat_list(branchstat_callback_t cb, void *arg,
                struct driver *__restrict mod,
                struct branch_prediction const *start,
                struct branch_prediction const *end,
                bool annotated, bool is_driver) {
	ssize_t temp, result = 0;
	struct branch_prediction const *iter, *next;
	for (iter = start;;) {
		/* Make sure that the branch prediction doesn't go out-of-bounds! */
		next = iter + 1;
		if (next >= end)
			break;
		/* Enumerate this prediction entry. */
		temp = branchstat_listone(cb, arg, mod, iter,
		                          annotated, is_driver);
		if unlikely(temp < 0)
			goto err;
		result += temp;
		iter = next;
	}
	return result;
err:
	return temp;
}


PRIVATE NONNULL((1, 3, 4)) ssize_t KCALL
branchstat_listsection(branchstat_callback_t cb, void *arg,
                       struct driver *__restrict mod,
                       struct driver_section *__restrict sect,
                       bool annotated, bool is_driver) {
	ssize_t result;
	/* Enumerate all entries contains within the given section. */
	byte_t *data;
	size_t size;
	data   = module_section_getaddr_inflate(sect, &size);
	result = branchstat_list(cb, arg, mod,
	                         (struct branch_prediction *)(data),
	                         (struct branch_prediction *)(data + size),
	                         annotated, is_driver);
	return result;
}

/* Same as `branchstat()', but only invoke `cb()' for branches listed by `mod' */
PUBLIC NONNULL((1, 3)) ssize_t KCALL
branchstat_d(branchstat_callback_t cb, void *arg,
             struct driver *__restrict mod) {
	ssize_t temp, result;
	if (mod == &kernel_driver) {
		/* Special handling for the kernel driver. */
		result = branchstat_list(cb, arg, &kernel_driver,
		                         kernel_profile_branch_start,
		                         kernel_profile_branch_end,
		                         false, false);
		if likely(result >= 0) {
			temp = branchstat_list(cb, arg, &kernel_driver,
			                       kernel_profile_branch_annotated_start,
			                       kernel_profile_branch_annotated_end,
			                       true, false);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
	} else {
		REF struct driver_section *sect;
		result = 0;
		/* Lock the individual sections. */
		sect = (REF struct driver_section *)module_locksection(mod, BRANCH_PREDICTION_SECTION);
		if (sect) {
			FINALLY_DECREF(sect);
			temp = branchstat_listsection(cb, arg, mod, sect, false, true);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		sect = (REF struct driver_section *)module_locksection(mod, BRANCH_PREDICTION_SECTION_ANNOTATED);
		if (sect) {
			FINALLY_DECREF(sect);
			temp = branchstat_listsection(cb, arg, mod, sect, true, true);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
	}
	return result;
err:
	return temp;
}


PRIVATE void KCALL
dump_branch_stats_for(struct branch_prediction *start,
                      struct branch_prediction *end,
                      bool annotated) {
	for (; start < end; ++start) {
		if (!start->bp_miss && !start->bp_hit)
			continue;
		if (annotated && !start->bp_wrong)
			continue; /* Perfect hit rate */
#if 1
		printk(KERN_RAW "%%{vinfo:/os/kernel.bin:%p:%p:%%f(%%l,%%c) : %%n : %%p : }",
		       start->bp_addr, start->bp_addr);
#else
		printk(KERN_RAW "%[vinfo:%f(%l,%c) : %n : %p : ]", start->bp_addr);
#endif
		if (annotated) {
			printk(KERN_RAW "%u%% correct ("
			                "%" PRIuN(__BRANCH_PREDITION_RIGHT_WRONG_SIZE) "Iu/"
			                "%" PRIuN(__BRANCH_PREDITION_RIGHT_WRONG_SIZE) ") "
			                "(expects: %" PRIuN(__BRANCH_PREDITION_EXPECTED_SIZE) ")\n",
			       (unsigned int)((start->bp_right * 100) / (start->bp_right + start->bp_wrong)),
			       start->bp_right,
			       start->bp_right + start->bp_wrong,
			       start->bp_expect);
		} else {
			printk(KERN_RAW "tt:%" PRIuN(__BRANCH_PREDITION_RIGHT_WRONG_SIZE) ", "
			                "ff:%" PRIuN(__BRANCH_PREDITION_RIGHT_WRONG_SIZE) "\n",
			       start->bp_hit, start->bp_miss);
		}
	}
}

/* Dump branch statistics on each traced branch to printk(KERN_RAW) */
PUBLIC void KCALL dump_branch_stats(void) {
	dump_branch_stats_for(kernel_profile_branch_start,
	                      kernel_profile_branch_end,
	                      false);
	dump_branch_stats_for(kernel_profile_branch_annotated_start,
	                      kernel_profile_branch_annotated_end,
	                      true);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_PROFILER_C */
