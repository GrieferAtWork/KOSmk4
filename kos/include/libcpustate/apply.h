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
#ifndef _LIBCPUSTATE_APPLY_H
#define _LIBCPUSTATE_APPLY_H 1

#include "api.h"

#include <__stdinc.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/kernel/cpu-state.h>

#include <libcpustate/asm/features.h>

#ifdef __CC__
__DECL_BEGIN

#define __LIBCPU_APPLY_GENERATE_ASMNAME2(xcpustate) cpu_apply_##xcpustate
#define __LIBCPU_APPLY_GENERATE_ASMNAME(xcpustate)  __LIBCPU_APPLY_GENERATE_ASMNAME2(xcpustate)


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
};

function getPossibleAliasesForXCpuState(name: string): {string...} {
	if (name !in XCPUSTATE)
		return {};
	return XCPUSTATE[:XCPUSTATE.index(name)];
}

local isFirst = true;
for (local xcs: APPLY_CPUSTATE) {
	if (!isFirst) {
		print;
		print;
		print;
	}
	isFirst = false;
	print("/" "************************************************************************" "/");
	print("/" "* ", xcs.ljust(68), " *" "/");
	print("/" "************************************************************************" "/");
	print("#ifdef LIBCPUSTATE_HAVE_", xcs.upper());
	// Print apply symbol name
	if (getPossibleAliasesForXCpuState(xcs)) {
		print("#ifdef ", xcs.upper(), "_ALIAS");
		print("#define PCPU_APPLY_", xcs.upper(), "_NAME \"cpu_apply_\" ", xcs.upper(), "_ALIAS_STR");
		print("#else /" "* ", xcs.upper(), "_ALIAS *" "/");
		print("#define PCPU_APPLY_", xcs.upper(), "_NAME ", repr(f"cpu_apply_{xcs}"));
		print("#endif /" "* !", xcs.upper(), "_ALIAS *" "/");
	} else {
		print("#define PCPU_APPLY_", xcs.upper(), "_NAME ", repr(f"cpu_apply_{xcs}"));
	}
	if (xcs !in XCPUSTATE)
		print("struct ", xcs, ";");
	print("/" "* Load the given CPU state and resume execute at its location. *" "/");
	print("typedef __ABNORMAL_RETURN __ATTR_NORETURN_T __ATTR_NONNULL_T((1)) void");
	print("__NOTHROW_T(LIBCPUSTATE_CC *PCPU_APPLY_", xcs.upper(), ")(struct ", xcs, " const *__restrict __state);");
	print("#ifdef LIBCPUSTATE_WANT_PROTOTYPES");
	if (getPossibleAliasesForXCpuState(xcs)) {
		print("#ifdef ", xcs.upper(), "_ALIAS");
		print("__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply_", xcs, ",");
		print("                         (struct ", xcs, " const *__restrict __state),__LIBCPU_APPLY_GENERATE_ASMNAME(", xcs.upper(), "_ALIAS),(__state))");
		print("#else /" "* ", xcs.upper(), "_ALIAS *" "/");
		print("LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void");
		print("__NOTHROW(LIBCPUSTATE_CC cpu_apply_", xcs, ")(struct ", xcs, " const *__restrict __state);");
		print("#endif /" "* !", xcs.upper(), "_ALIAS *" "/");
	} else {
		print("LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void");
		print("__NOTHROW(LIBCPUSTATE_CC cpu_apply_", xcs, ")(struct ", xcs, " const *__restrict __state);");
	}
	print("#endif /" "* LIBCPUSTATE_WANT_PROTOTYPES *" "/");
	print("#endif /" "* LIBCPUSTATE_HAVE_", xcs.upper(), " *" "/");
}

// Generate c++ overloads
print("#if defined(__cplusplus) && defined(LIBCPUSTATE_WANT_PROTOTYPES)");
print("extern \"C++\" {");
for (local xcs: APPLY_CPUSTATE) {
	print("#ifdef LIBCPUSTATE_HAVE_", xcs.upper());
	if (getPossibleAliasesForXCpuState(xcs)) {
		print("#ifdef ", xcs.upper(), "_ALIAS");
		print("__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply,(struct ", xcs, " const *__restrict __state),__LIBCPU_APPLY_GENERATE_ASMNAME(", xcs.upper(), "_ALIAS),(__state))");
		print("#else /" "* ", xcs.upper(), "_ALIAS *" "/");
		print("__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply,(struct ", xcs, " const *__restrict __state),cpu_apply_", xcs, ",(__state))");
		print("#endif /" "* !", xcs.upper(), "_ALIAS *" "/");
	} else {
		print("__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply,(struct ", xcs, " const *__restrict __state),cpu_apply_", xcs, ",(__state))");
	}
	print("#endif /" "* LIBCPUSTATE_HAVE_", xcs.upper(), " *" "/");
}
print("} /" "* extern \"C++\" *" "/");
print("#endif /" "* __cplusplus && LIBCPUSTATE_WANT_PROTOTYPES *" "/");


]]]*/
/************************************************************************/
/* ucpustate                                                            */
/************************************************************************/
#ifdef LIBCPUSTATE_HAVE_UCPUSTATE
#define PCPU_APPLY_UCPUSTATE_NAME "cpu_apply_ucpustate"
/* Load the given CPU state and resume execute at its location. */
typedef __ABNORMAL_RETURN __ATTR_NORETURN_T __ATTR_NONNULL_T((1)) void
__NOTHROW_T(LIBCPUSTATE_CC *PCPU_APPLY_UCPUSTATE)(struct ucpustate const *__restrict __state);
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void
__NOTHROW(LIBCPUSTATE_CC cpu_apply_ucpustate)(struct ucpustate const *__restrict __state);
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#endif /* LIBCPUSTATE_HAVE_UCPUSTATE */



/************************************************************************/
/* lcpustate                                                            */
/************************************************************************/
#ifdef LIBCPUSTATE_HAVE_LCPUSTATE
#ifdef LCPUSTATE_ALIAS
#define PCPU_APPLY_LCPUSTATE_NAME "cpu_apply_" LCPUSTATE_ALIAS_STR
#else /* LCPUSTATE_ALIAS */
#define PCPU_APPLY_LCPUSTATE_NAME "cpu_apply_lcpustate"
#endif /* !LCPUSTATE_ALIAS */
/* Load the given CPU state and resume execute at its location. */
typedef __ABNORMAL_RETURN __ATTR_NORETURN_T __ATTR_NONNULL_T((1)) void
__NOTHROW_T(LIBCPUSTATE_CC *PCPU_APPLY_LCPUSTATE)(struct lcpustate const *__restrict __state);
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
#ifdef LCPUSTATE_ALIAS
__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply_lcpustate,
                         (struct lcpustate const *__restrict __state),__LIBCPU_APPLY_GENERATE_ASMNAME(LCPUSTATE_ALIAS),(__state))
#else /* LCPUSTATE_ALIAS */
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void
__NOTHROW(LIBCPUSTATE_CC cpu_apply_lcpustate)(struct lcpustate const *__restrict __state);
#endif /* !LCPUSTATE_ALIAS */
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#endif /* LIBCPUSTATE_HAVE_LCPUSTATE */



/************************************************************************/
/* kcpustate                                                            */
/************************************************************************/
#ifdef LIBCPUSTATE_HAVE_KCPUSTATE
#ifdef KCPUSTATE_ALIAS
#define PCPU_APPLY_KCPUSTATE_NAME "cpu_apply_" KCPUSTATE_ALIAS_STR
#else /* KCPUSTATE_ALIAS */
#define PCPU_APPLY_KCPUSTATE_NAME "cpu_apply_kcpustate"
#endif /* !KCPUSTATE_ALIAS */
/* Load the given CPU state and resume execute at its location. */
typedef __ABNORMAL_RETURN __ATTR_NORETURN_T __ATTR_NONNULL_T((1)) void
__NOTHROW_T(LIBCPUSTATE_CC *PCPU_APPLY_KCPUSTATE)(struct kcpustate const *__restrict __state);
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
#ifdef KCPUSTATE_ALIAS
__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply_kcpustate,
                         (struct kcpustate const *__restrict __state),__LIBCPU_APPLY_GENERATE_ASMNAME(KCPUSTATE_ALIAS),(__state))
#else /* KCPUSTATE_ALIAS */
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void
__NOTHROW(LIBCPUSTATE_CC cpu_apply_kcpustate)(struct kcpustate const *__restrict __state);
#endif /* !KCPUSTATE_ALIAS */
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#endif /* LIBCPUSTATE_HAVE_KCPUSTATE */



/************************************************************************/
/* icpustate                                                            */
/************************************************************************/
#ifdef LIBCPUSTATE_HAVE_ICPUSTATE
#ifdef ICPUSTATE_ALIAS
#define PCPU_APPLY_ICPUSTATE_NAME "cpu_apply_" ICPUSTATE_ALIAS_STR
#else /* ICPUSTATE_ALIAS */
#define PCPU_APPLY_ICPUSTATE_NAME "cpu_apply_icpustate"
#endif /* !ICPUSTATE_ALIAS */
/* Load the given CPU state and resume execute at its location. */
typedef __ABNORMAL_RETURN __ATTR_NORETURN_T __ATTR_NONNULL_T((1)) void
__NOTHROW_T(LIBCPUSTATE_CC *PCPU_APPLY_ICPUSTATE)(struct icpustate const *__restrict __state);
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
#ifdef ICPUSTATE_ALIAS
__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply_icpustate,
                         (struct icpustate const *__restrict __state),__LIBCPU_APPLY_GENERATE_ASMNAME(ICPUSTATE_ALIAS),(__state))
#else /* ICPUSTATE_ALIAS */
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void
__NOTHROW(LIBCPUSTATE_CC cpu_apply_icpustate)(struct icpustate const *__restrict __state);
#endif /* !ICPUSTATE_ALIAS */
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#endif /* LIBCPUSTATE_HAVE_ICPUSTATE */



/************************************************************************/
/* scpustate                                                            */
/************************************************************************/
#ifdef LIBCPUSTATE_HAVE_SCPUSTATE
#ifdef SCPUSTATE_ALIAS
#define PCPU_APPLY_SCPUSTATE_NAME "cpu_apply_" SCPUSTATE_ALIAS_STR
#else /* SCPUSTATE_ALIAS */
#define PCPU_APPLY_SCPUSTATE_NAME "cpu_apply_scpustate"
#endif /* !SCPUSTATE_ALIAS */
/* Load the given CPU state and resume execute at its location. */
typedef __ABNORMAL_RETURN __ATTR_NORETURN_T __ATTR_NONNULL_T((1)) void
__NOTHROW_T(LIBCPUSTATE_CC *PCPU_APPLY_SCPUSTATE)(struct scpustate const *__restrict __state);
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
#ifdef SCPUSTATE_ALIAS
__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply_scpustate,
                         (struct scpustate const *__restrict __state),__LIBCPU_APPLY_GENERATE_ASMNAME(SCPUSTATE_ALIAS),(__state))
#else /* SCPUSTATE_ALIAS */
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void
__NOTHROW(LIBCPUSTATE_CC cpu_apply_scpustate)(struct scpustate const *__restrict __state);
#endif /* !SCPUSTATE_ALIAS */
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#endif /* LIBCPUSTATE_HAVE_SCPUSTATE */



/************************************************************************/
/* fcpustate                                                            */
/************************************************************************/
#ifdef LIBCPUSTATE_HAVE_FCPUSTATE
#ifdef FCPUSTATE_ALIAS
#define PCPU_APPLY_FCPUSTATE_NAME "cpu_apply_" FCPUSTATE_ALIAS_STR
#else /* FCPUSTATE_ALIAS */
#define PCPU_APPLY_FCPUSTATE_NAME "cpu_apply_fcpustate"
#endif /* !FCPUSTATE_ALIAS */
/* Load the given CPU state and resume execute at its location. */
typedef __ABNORMAL_RETURN __ATTR_NORETURN_T __ATTR_NONNULL_T((1)) void
__NOTHROW_T(LIBCPUSTATE_CC *PCPU_APPLY_FCPUSTATE)(struct fcpustate const *__restrict __state);
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
#ifdef FCPUSTATE_ALIAS
__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply_fcpustate,
                         (struct fcpustate const *__restrict __state),__LIBCPU_APPLY_GENERATE_ASMNAME(FCPUSTATE_ALIAS),(__state))
#else /* FCPUSTATE_ALIAS */
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void
__NOTHROW(LIBCPUSTATE_CC cpu_apply_fcpustate)(struct fcpustate const *__restrict __state);
#endif /* !FCPUSTATE_ALIAS */
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#endif /* LIBCPUSTATE_HAVE_FCPUSTATE */



/************************************************************************/
/* mcontext                                                             */
/************************************************************************/
#ifdef LIBCPUSTATE_HAVE_MCONTEXT
#define PCPU_APPLY_MCONTEXT_NAME "cpu_apply_mcontext"
struct mcontext;
/* Load the given CPU state and resume execute at its location. */
typedef __ABNORMAL_RETURN __ATTR_NORETURN_T __ATTR_NONNULL_T((1)) void
__NOTHROW_T(LIBCPUSTATE_CC *PCPU_APPLY_MCONTEXT)(struct mcontext const *__restrict __state);
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void
__NOTHROW(LIBCPUSTATE_CC cpu_apply_mcontext)(struct mcontext const *__restrict __state);
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#endif /* LIBCPUSTATE_HAVE_MCONTEXT */



/************************************************************************/
/* ucontext                                                             */
/************************************************************************/
#ifdef LIBCPUSTATE_HAVE_UCONTEXT
#define PCPU_APPLY_UCONTEXT_NAME "cpu_apply_ucontext"
struct ucontext;
/* Load the given CPU state and resume execute at its location. */
typedef __ABNORMAL_RETURN __ATTR_NORETURN_T __ATTR_NONNULL_T((1)) void
__NOTHROW_T(LIBCPUSTATE_CC *PCPU_APPLY_UCONTEXT)(struct ucontext const *__restrict __state);
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void
__NOTHROW(LIBCPUSTATE_CC cpu_apply_ucontext)(struct ucontext const *__restrict __state);
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#endif /* LIBCPUSTATE_HAVE_UCONTEXT */
#if defined(__cplusplus) && defined(LIBCPUSTATE_WANT_PROTOTYPES)
extern "C++" {
#ifdef LIBCPUSTATE_HAVE_UCPUSTATE
__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply,(struct ucpustate const *__restrict __state),cpu_apply_ucpustate,(__state))
#endif /* LIBCPUSTATE_HAVE_UCPUSTATE */
#ifdef LIBCPUSTATE_HAVE_LCPUSTATE
#ifdef LCPUSTATE_ALIAS
__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply,(struct lcpustate const *__restrict __state),__LIBCPU_APPLY_GENERATE_ASMNAME(LCPUSTATE_ALIAS),(__state))
#else /* LCPUSTATE_ALIAS */
__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply,(struct lcpustate const *__restrict __state),cpu_apply_lcpustate,(__state))
#endif /* !LCPUSTATE_ALIAS */
#endif /* LIBCPUSTATE_HAVE_LCPUSTATE */
#ifdef LIBCPUSTATE_HAVE_KCPUSTATE
#ifdef KCPUSTATE_ALIAS
__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply,(struct kcpustate const *__restrict __state),__LIBCPU_APPLY_GENERATE_ASMNAME(KCPUSTATE_ALIAS),(__state))
#else /* KCPUSTATE_ALIAS */
__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply,(struct kcpustate const *__restrict __state),cpu_apply_kcpustate,(__state))
#endif /* !KCPUSTATE_ALIAS */
#endif /* LIBCPUSTATE_HAVE_KCPUSTATE */
#ifdef LIBCPUSTATE_HAVE_ICPUSTATE
#ifdef ICPUSTATE_ALIAS
__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply,(struct icpustate const *__restrict __state),__LIBCPU_APPLY_GENERATE_ASMNAME(ICPUSTATE_ALIAS),(__state))
#else /* ICPUSTATE_ALIAS */
__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply,(struct icpustate const *__restrict __state),cpu_apply_icpustate,(__state))
#endif /* !ICPUSTATE_ALIAS */
#endif /* LIBCPUSTATE_HAVE_ICPUSTATE */
#ifdef LIBCPUSTATE_HAVE_SCPUSTATE
#ifdef SCPUSTATE_ALIAS
__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply,(struct scpustate const *__restrict __state),__LIBCPU_APPLY_GENERATE_ASMNAME(SCPUSTATE_ALIAS),(__state))
#else /* SCPUSTATE_ALIAS */
__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply,(struct scpustate const *__restrict __state),cpu_apply_scpustate,(__state))
#endif /* !SCPUSTATE_ALIAS */
#endif /* LIBCPUSTATE_HAVE_SCPUSTATE */
#ifdef LIBCPUSTATE_HAVE_FCPUSTATE
#ifdef FCPUSTATE_ALIAS
__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply,(struct fcpustate const *__restrict __state),__LIBCPU_APPLY_GENERATE_ASMNAME(FCPUSTATE_ALIAS),(__state))
#else /* FCPUSTATE_ALIAS */
__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply,(struct fcpustate const *__restrict __state),cpu_apply_fcpustate,(__state))
#endif /* !FCPUSTATE_ALIAS */
#endif /* LIBCPUSTATE_HAVE_FCPUSTATE */
#ifdef LIBCPUSTATE_HAVE_MCONTEXT
__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply,(struct mcontext const *__restrict __state),cpu_apply_mcontext,(__state))
#endif /* LIBCPUSTATE_HAVE_MCONTEXT */
#ifdef LIBCPUSTATE_HAVE_UCONTEXT
__COMPILER_REDIRECT_VOID(LIBCPUSTATE_DECL,__ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW,LIBCPUSTATE_CC,cpu_apply,(struct ucontext const *__restrict __state),cpu_apply_ucontext,(__state))
#endif /* LIBCPUSTATE_HAVE_UCONTEXT */
} /* extern "C++" */
#endif /* __cplusplus && LIBCPUSTATE_WANT_PROTOTYPES */
/*[[[end]]]*/

#undef __LIBCPU_APPLY_GENERATE_ASMNAME2
#undef __LIBCPU_APPLY_GENERATE_ASMNAME

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBCPUSTATE_APPLY_H */
