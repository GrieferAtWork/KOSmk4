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
#ifndef GUARD_LIBUNWIND_REGISTER_H
#define GUARD_LIBUNWIND_REGISTER_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <libunwind/register.h>
/**/

#include <kos/kernel/cpu-state.h>

#ifdef LIBUNWIND_HAVE_GETSETREG_MCONTEXT
#include <bits/os/mcontext.h> /* struct mcontext */
#endif /* LIBUNWIND_HAVE_GETSETREG_MCONTEXT */

#ifdef LIBUNWIND_HAVE_GETSETREG_UCONTEXT
#include <bits/os/ucontext.h> /* struct ucontext */
#endif /* LIBUNWIND_HAVE_GETSETREG_UCONTEXT */

#ifdef LIBUNWIND_HAVE_GETSETREG_FPUSTATE
#include <kos/kernel/fpu-state.h> /* struct fpustate */
#endif /* LIBUNWIND_HAVE_GETSETREG_FPUSTATE */

DECL_BEGIN

/*[[[deemon
import * from deemon;
local XCPUSTATE: {string...} = {
	"ucpustate",
	"lcpustate",
	"kcpustate",
	"icpustate",
	"scpustate",
	"fcpustate",
};
local APPLY_CPUSTATE: {string...} = {
	XCPUSTATE...,
	"mcontext",
	"ucontext",
	"fpustate",
};

function getPossibleAliasesForXCpuState(name: string): {string...} {
	if (name !in XCPUSTATE)
		return {};
	return XCPUSTATE[:XCPUSTATE.index(name)];
}

for (local state: APPLY_CPUSTATE) {
	local STATE = state.upper();
	local aliases = getPossibleAliasesForXCpuState(state);
	print("/" "************************************************************************" "/");
	print("/" "* ", state.ljust(68), " *" "/");
	print("/" "************************************************************************" "/");
	if (aliases)
		print("#ifndef ", STATE, "_ALIAS");
	print("#ifdef LIBUNWIND_HAVE_GETSETREG_", STATE);
	print("INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_", state, ")(struct ", state, " const *arg, unwind_regno_t regno, void *__restrict dst);");
	print("INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_", state, "_exclusive)(struct ", state, " const *arg, unwind_regno_t regno, void *__restrict dst);");
	print("#ifdef LIBUNWIND_HAVE_GETSETREG_", STATE, "_P");
	print("INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_", state, "_p)(struct ", state, " **arg, unwind_regno_t regno, void const *__restrict src);");
	print("INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_", state, "_exclusive_p)(struct ", state, " **arg, unwind_regno_t regno, void const *__restrict src);");
	print("#else /" "* LIBUNWIND_HAVE_GETSETREG_", STATE, "_P *" "/");
	print("INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_", state, ")(struct ", state, " *arg, unwind_regno_t regno, void const *__restrict src);");
	print("INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_", state, "_exclusive)(struct ", state, " *arg, unwind_regno_t regno, void const *__restrict src);");
	print("#endif /" "* !LIBUNWIND_HAVE_GETSETREG_", STATE, "_P *" "/");
	print("#endif /" "* LIBUNWIND_HAVE_GETSETREG_", STATE, " *" "/");
	if (aliases)
		print("#endif /" "* !", STATE, "_ALIAS *" "/");
	print;
}
]]]*/
/************************************************************************/
/* ucpustate                                                            */
/************************************************************************/
#ifdef LIBUNWIND_HAVE_GETSETREG_UCPUSTATE
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_ucpustate)(struct ucpustate const *arg, unwind_regno_t regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_ucpustate_exclusive)(struct ucpustate const *arg, unwind_regno_t regno, void *__restrict dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_UCPUSTATE_P
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_ucpustate_p)(struct ucpustate **arg, unwind_regno_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_ucpustate_exclusive_p)(struct ucpustate **arg, unwind_regno_t regno, void const *__restrict src);
#else /* LIBUNWIND_HAVE_GETSETREG_UCPUSTATE_P */
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_ucpustate)(struct ucpustate *arg, unwind_regno_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_ucpustate_exclusive)(struct ucpustate *arg, unwind_regno_t regno, void const *__restrict src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_UCPUSTATE_P */
#endif /* LIBUNWIND_HAVE_GETSETREG_UCPUSTATE */

/************************************************************************/
/* lcpustate                                                            */
/************************************************************************/
#ifndef LCPUSTATE_ALIAS
#ifdef LIBUNWIND_HAVE_GETSETREG_LCPUSTATE
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_lcpustate)(struct lcpustate const *arg, unwind_regno_t regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_lcpustate_exclusive)(struct lcpustate const *arg, unwind_regno_t regno, void *__restrict dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_LCPUSTATE_P
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_lcpustate_p)(struct lcpustate **arg, unwind_regno_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_lcpustate_exclusive_p)(struct lcpustate **arg, unwind_regno_t regno, void const *__restrict src);
#else /* LIBUNWIND_HAVE_GETSETREG_LCPUSTATE_P */
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_lcpustate)(struct lcpustate *arg, unwind_regno_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_lcpustate_exclusive)(struct lcpustate *arg, unwind_regno_t regno, void const *__restrict src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_LCPUSTATE_P */
#endif /* LIBUNWIND_HAVE_GETSETREG_LCPUSTATE */
#endif /* !LCPUSTATE_ALIAS */

/************************************************************************/
/* kcpustate                                                            */
/************************************************************************/
#ifndef KCPUSTATE_ALIAS
#ifdef LIBUNWIND_HAVE_GETSETREG_KCPUSTATE
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_kcpustate)(struct kcpustate const *arg, unwind_regno_t regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_kcpustate_exclusive)(struct kcpustate const *arg, unwind_regno_t regno, void *__restrict dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_KCPUSTATE_P
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_kcpustate_p)(struct kcpustate **arg, unwind_regno_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_kcpustate_exclusive_p)(struct kcpustate **arg, unwind_regno_t regno, void const *__restrict src);
#else /* LIBUNWIND_HAVE_GETSETREG_KCPUSTATE_P */
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_kcpustate)(struct kcpustate *arg, unwind_regno_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_kcpustate_exclusive)(struct kcpustate *arg, unwind_regno_t regno, void const *__restrict src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_KCPUSTATE_P */
#endif /* LIBUNWIND_HAVE_GETSETREG_KCPUSTATE */
#endif /* !KCPUSTATE_ALIAS */

/************************************************************************/
/* icpustate                                                            */
/************************************************************************/
#ifndef ICPUSTATE_ALIAS
#ifdef LIBUNWIND_HAVE_GETSETREG_ICPUSTATE
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_icpustate)(struct icpustate const *arg, unwind_regno_t regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_icpustate_exclusive)(struct icpustate const *arg, unwind_regno_t regno, void *__restrict dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_icpustate_p)(struct icpustate **arg, unwind_regno_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_icpustate_exclusive_p)(struct icpustate **arg, unwind_regno_t regno, void const *__restrict src);
#else /* LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P */
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_icpustate)(struct icpustate *arg, unwind_regno_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_icpustate_exclusive)(struct icpustate *arg, unwind_regno_t regno, void const *__restrict src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P */
#endif /* LIBUNWIND_HAVE_GETSETREG_ICPUSTATE */
#endif /* !ICPUSTATE_ALIAS */

/************************************************************************/
/* scpustate                                                            */
/************************************************************************/
#ifndef SCPUSTATE_ALIAS
#ifdef LIBUNWIND_HAVE_GETSETREG_SCPUSTATE
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_scpustate)(struct scpustate const *arg, unwind_regno_t regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_scpustate_exclusive)(struct scpustate const *arg, unwind_regno_t regno, void *__restrict dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_scpustate_p)(struct scpustate **arg, unwind_regno_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_scpustate_exclusive_p)(struct scpustate **arg, unwind_regno_t regno, void const *__restrict src);
#else /* LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P */
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_scpustate)(struct scpustate *arg, unwind_regno_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_scpustate_exclusive)(struct scpustate *arg, unwind_regno_t regno, void const *__restrict src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P */
#endif /* LIBUNWIND_HAVE_GETSETREG_SCPUSTATE */
#endif /* !SCPUSTATE_ALIAS */

/************************************************************************/
/* fcpustate                                                            */
/************************************************************************/
#ifndef FCPUSTATE_ALIAS
#ifdef LIBUNWIND_HAVE_GETSETREG_FCPUSTATE
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_fcpustate)(struct fcpustate const *arg, unwind_regno_t regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_fcpustate_exclusive)(struct fcpustate const *arg, unwind_regno_t regno, void *__restrict dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_FCPUSTATE_P
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_fcpustate_p)(struct fcpustate **arg, unwind_regno_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_fcpustate_exclusive_p)(struct fcpustate **arg, unwind_regno_t regno, void const *__restrict src);
#else /* LIBUNWIND_HAVE_GETSETREG_FCPUSTATE_P */
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_fcpustate)(struct fcpustate *arg, unwind_regno_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_fcpustate_exclusive)(struct fcpustate *arg, unwind_regno_t regno, void const *__restrict src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_FCPUSTATE_P */
#endif /* LIBUNWIND_HAVE_GETSETREG_FCPUSTATE */
#endif /* !FCPUSTATE_ALIAS */

/************************************************************************/
/* mcontext                                                             */
/************************************************************************/
#ifdef LIBUNWIND_HAVE_GETSETREG_MCONTEXT
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_mcontext)(struct mcontext const *arg, unwind_regno_t regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_mcontext_exclusive)(struct mcontext const *arg, unwind_regno_t regno, void *__restrict dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_MCONTEXT_P
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_mcontext_p)(struct mcontext **arg, unwind_regno_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_mcontext_exclusive_p)(struct mcontext **arg, unwind_regno_t regno, void const *__restrict src);
#else /* LIBUNWIND_HAVE_GETSETREG_MCONTEXT_P */
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_mcontext)(struct mcontext *arg, unwind_regno_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_mcontext_exclusive)(struct mcontext *arg, unwind_regno_t regno, void const *__restrict src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_MCONTEXT_P */
#endif /* LIBUNWIND_HAVE_GETSETREG_MCONTEXT */

/************************************************************************/
/* ucontext                                                             */
/************************************************************************/
#ifdef LIBUNWIND_HAVE_GETSETREG_UCONTEXT
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_ucontext)(struct ucontext const *arg, unwind_regno_t regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_ucontext_exclusive)(struct ucontext const *arg, unwind_regno_t regno, void *__restrict dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_UCONTEXT_P
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_ucontext_p)(struct ucontext **arg, unwind_regno_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_ucontext_exclusive_p)(struct ucontext **arg, unwind_regno_t regno, void const *__restrict src);
#else /* LIBUNWIND_HAVE_GETSETREG_UCONTEXT_P */
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_ucontext)(struct ucontext *arg, unwind_regno_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_ucontext_exclusive)(struct ucontext *arg, unwind_regno_t regno, void const *__restrict src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_UCONTEXT_P */
#endif /* LIBUNWIND_HAVE_GETSETREG_UCONTEXT */

/************************************************************************/
/* fpustate                                                             */
/************************************************************************/
#ifdef LIBUNWIND_HAVE_GETSETREG_FPUSTATE
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_fpustate)(struct fpustate const *arg, unwind_regno_t regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_fpustate_exclusive)(struct fpustate const *arg, unwind_regno_t regno, void *__restrict dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_FPUSTATE_P
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_fpustate_p)(struct fpustate **arg, unwind_regno_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_fpustate_exclusive_p)(struct fpustate **arg, unwind_regno_t regno, void const *__restrict src);
#else /* LIBUNWIND_HAVE_GETSETREG_FPUSTATE_P */
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_fpustate)(struct fpustate *arg, unwind_regno_t regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_fpustate_exclusive)(struct fpustate *arg, unwind_regno_t regno, void const *__restrict src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_FPUSTATE_P */
#endif /* LIBUNWIND_HAVE_GETSETREG_FPUSTATE */
/*[[[end]]]*/

DECL_END

#endif /* !GUARD_LIBUNWIND_REGISTER_H */
