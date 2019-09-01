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
#ifndef GUARD_KERNEL_SRC_MISC_PROFILER_C
#define GUARD_KERNEL_SRC_MISC_PROFILER_C 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile ourself! */

#include <kernel/compiler.h>

#include <kernel/printk.h>
#include <kernel/profiler.h>
#include <kernel/types.h>

DECL_BEGIN

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
			printk(KERN_RAW "%u%% correct (%Iu/%Iu) (expects: %Iu)\n",
			       (unsigned int)((start->bp_right * 100) / (start->bp_right + start->bp_wrong)),
			       start->bp_right,
			       start->bp_right + start->bp_wrong,
			       start->bp_expect);
		} else {
			printk(KERN_RAW "tt:%Iu, ff:%Iu\n",
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
