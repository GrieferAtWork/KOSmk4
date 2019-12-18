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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_PROFILER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_PROFILER_H 1

#include <kernel/compiler.h>

#include <kernel/arch/profiler.h>
#include <kernel/compiler-branch-tracer.h>
#include <kernel/types.h>

#ifdef __CC__
DECL_BEGIN

/* Kernel branch profiling. */

#ifndef __BRANCH_PREDITION_ADDRESS_TYPE
#define __BRANCH_PREDITION_ADDRESS_TYPE ulongptr_t
#endif /* !__BRANCH_PREDITION_ADDRESS_TYPE */

#ifndef __BRANCH_PREDITION_ADDRESS_BASE
#define __BRANCH_PREDITION_ADDRESS_BASE (__CCAST(__BRANCH_PREDITION_ADDRESS_TYPE)0)
#endif /* !__BRANCH_PREDITION_ADDRESS_BASE */

#ifndef __BRANCH_PREDITION_EXPECTED_TYPE
#define __BRANCH_PREDITION_EXPECTED_TYPE __BRANCH_PREDITION_ADDRESS_TYPE
#endif /* !__BRANCH_PREDITION_EXPECTED_TYPE */

#ifndef __BRANCH_PREDITION_RIGHT_WRONG_TYPE
#define __BRANCH_PREDITION_RIGHT_WRONG_TYPE ulongptr_t
#endif /* !__BRANCH_PREDITION_RIGHT_WRONG_TYPE */

#ifndef __branch_prediction_defined
#define __branch_prediction_defined 1
struct branch_prediction {
	__BRANCH_PREDITION_ADDRESS_TYPE  bp_addr;   /* [const][1..1] Source location */
	union {
		struct {  /* For annotated branches */
			__BRANCH_PREDITION_RIGHT_WRONG_TYPE bp_wrong; /* Number of times that the prediction was wrong */
			__BRANCH_PREDITION_RIGHT_WRONG_TYPE bp_right; /* Number of times that the prediction was right */
		};
		__BRANCH_PREDITION_RIGHT_WRONG_TYPE bp_wrong_right[2]; /* Array lookup to allow for condition indexing */
		struct {  /* For free-standing (un-annotated) branches */
			__BRANCH_PREDITION_RIGHT_WRONG_TYPE bp_miss;  /* Number of times that the prediction was wrong */
			__BRANCH_PREDITION_RIGHT_WRONG_TYPE bp_hit;   /* Number of times that the prediction was current */
		};
		__BRANCH_PREDITION_RIGHT_WRONG_TYPE bp_miss_hit[2]; /* Array lookup to allow for condition indexing */
	};
	__BRANCH_PREDITION_EXPECTED_TYPE bp_expect; /* [const] The expected value */
};
#endif /* !__branch_prediction_defined */

/* Names of the branch prediction sections in drivers. */
#define BRANCH_PREDICTION_SECTION             ".data.profile_branch"
#define BRANCH_PREDICTION_SECTION_ANNOTATED   ".data.profile_branch_annotated"

#ifdef CONFIG_BUILDING_KERNEL_CORE
/* Branch predictions for the kernel core. */
INTDEF struct branch_prediction kernel_profile_branch_start[];
INTDEF struct branch_prediction kernel_profile_branch_end[];
INTDEF struct branch_prediction kernel_profile_branch_annotated_start[];
INTDEF struct branch_prediction kernel_profile_branch_annotated_end[];
#endif /* CONFIG_BUILDING_KERNEL_CORE */

struct branch_stat_group {
	size_t                    g_cover_reach; /* Number of reached branches */
	size_t                    g_cover_total; /* Total number of known branches */
	union {
		size_t                g_wrong;       /* Total number of wrong predictions */
		size_t                g_misses;      /* Total number of branch misses */
	};
	union {
		size_t                g_right;       /* Total number of right predictions */
		size_t                g_hits;        /* Total number of branch hits */
	};
};
struct branch_stat {
	struct branch_stat_group  bs_total;             /* All tracing information added up together */
	struct branch_stat_group  bs_branch;            /* Tracing information for non-annotated branches */
	struct branch_stat_group  bs_branch_annotated;  /* Tracing information for annotated branches */
};


/* Dump branch statistics on each traced branch to printk(KERN_RAW) */
FUNDEF void KCALL dump_branch_stats(void);



DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_PROFILER_H */
