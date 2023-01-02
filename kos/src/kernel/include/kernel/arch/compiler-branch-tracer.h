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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_ARCH_COMPILER_BRANCH_TRACER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_ARCH_COMPILER_BRANCH_TRACER_H 1

#include <hybrid/compiler.h>

#include <kernel/arch/profiler.h>

#include <hybrid/__atomic.h>
#include <hybrid/typecore.h>

#ifndef __BRANCH_PREDITION_RIGHT_WRONG_TYPE
#define __BRANCH_PREDITION_RIGHT_WRONG_SIZE __SIZEOF_POINTER__
#define __BRANCH_PREDITION_RIGHT_WRONG_TYPE __UINTPTR_TYPE__
#endif /* !__BRANCH_PREDITION_RIGHT_WRONG_TYPE */

#ifdef __CC__
DECL_BEGIN

#ifndef __BRANCH_PREDITION_ADDRESS_TYPE
#define __BRANCH_PREDITION_ADDRESS_SIZE __SIZEOF_POINTER__
#define __BRANCH_PREDITION_ADDRESS_TYPE __ULONGPTR_TYPE__
#endif /* !__BRANCH_PREDITION_ADDRESS_TYPE */

#ifndef __BRANCH_PREDITION_ADDRESS_BASE
#define __BRANCH_PREDITION_ADDRESS_BASE (__CCAST(__BRANCH_PREDITION_ADDRESS_TYPE)0)
#endif /* !__BRANCH_PREDITION_ADDRESS_BASE */

#ifndef __BRANCH_PREDITION_EXPECTED_TYPE
#define __BRANCH_PREDITION_EXPECTED_TYPE __BRANCH_PREDITION_ADDRESS_TYPE
#endif /* !__BRANCH_PREDITION_EXPECTED_TYPE */

#ifndef __BRANCH_PREDITION_RIGHT_WRONG_TYPE
#define __BRANCH_PREDITION_RIGHT_WRONG_SIZE __SIZEOF_POINTER__
#define __BRANCH_PREDITION_RIGHT_WRONG_TYPE __ULONGPTR_TYPE__
#endif /* !__BRANCH_PREDITION_RIGHT_WRONG_TYPE */

#ifndef __branch_prediction_defined
#define __branch_prediction_defined
struct branch_prediction {
	__BRANCH_PREDITION_ADDRESS_TYPE  bp_addr;   /* [const][1..1] Source location */
	__BRANCH_PREDITION_EXPECTED_TYPE bp_expect; /* [const] The expected value */
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
};
#endif /* !__branch_prediction_defined */

FUNDEF ATTR_LEAF NONNULL((1)) void
#ifdef __PREDICT_UPDATE_CC
__PREDICT_UPDATE_CC
#endif /* __PREDICT_UPDATE_CC */
__predict_update(struct branch_prediction *__restrict __pred,
                 __BRANCH_PREDITION_EXPECTED_TYPE __expr);
#define __predict_dotrace(section, expr, expected) \
	static ATTR_SECTION(section "." __PP_STR(__COUNTER__)) struct branch_prediction \
	______predict = { 0 /* Filled by `__predict_update'? */, (__BRANCH_PREDITION_EXPECTED_TYPE)(expected) }; \
	__predict_update(&______predict, (__BRANCH_PREDITION_EXPECTED_TYPE)______expr) \


DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_ARCH_COMPILER_BRANCH_TRACER_H */
