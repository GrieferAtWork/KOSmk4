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
#ifndef _LIBUNWIND_ARCH_REGISTER_H
#define _LIBUNWIND_ARCH_REGISTER_H 1

#include "api.h"

#include <kos/anno.h>
#include <kos/bits/except.h> /* __EXCEPT_REGISTER_STATE_TYPE_IS_* */
#include <kos/kernel/cpu-state.h>

#include <libunwind/asm/features.h> /* LIBUNWIND_HAVE_GETSETREG_* */
#include <libunwind/asm/isa.h>      /* unwind_getreg_getisa */

#ifdef LIBUNWIND_HAVE_GETSETREG_MCONTEXT
#include <bits/os/mcontext.h> /* struct mcontext */
#endif /* LIBUNWIND_HAVE_GETSETREG_MCONTEXT */

#ifdef LIBUNWIND_HAVE_GETSETREG_UCONTEXT
#include <bits/os/ucontext.h> /* struct ucontext */
#endif /* LIBUNWIND_HAVE_GETSETREG_UCONTEXT */

#ifdef LIBUNWIND_HAVE_GETSETREG_FPUSTATE
#include <kos/kernel/fpu-state.h> /* struct fpustate */
#endif /* LIBUNWIND_HAVE_GETSETREG_FPUSTATE */

#include "errno.h"

#ifdef __CC__
__DECL_BEGIN

#ifndef __unwind_regno_t_defined
#define __unwind_regno_t_defined
typedef __UINTPTR_HALF_TYPE__ unwind_regno_t;
#endif /* !__unwind_regno_t_defined */

/* Register accessor callbacks for a variety of known cpu context structures.
 * NOTE: When the intent  is to unwind  both CPU  and FPU registers,  you must  create
 *       your own custom register get/set functions that call forward to the functions
 *       below:
 * >> unwind_errno_t LIBUNWIND_CC my_getreg(void const *arg, unwind_regno_t regno, void *dst) {
 * >>     unwind_errno_t error;
 * >>     struct my_cpustate_with_fpu const *me;
 * >>     me = (struct my_cpustate_with_fpu const *)arg;
 * >>     if ((error = unwind_getreg_ufpustate(me->cs_cpu, regno, dst)) != UNWIND_INVALID_REGISTER)
 * >>         return error;
 * >>     if ((error = unwind_getreg_fpustate(me->cs_fpu, regno, dst)) != UNWIND_INVALID_REGISTER)
 * >>         return error;
 * >>     return UNWIND_INVALID_REGISTER;
 * >> }
 * >> unwind_errno_t LIBUNWIND_CC my_setreg(void *arg, unwind_regno_t regno, void const *src) {
 * >>     unwind_errno_t error;
 * >>     struct my_cpustate_with_fpu *me;
 * >>     me = (struct my_cpustate_with_fpu *)arg;
 * >>     if ((error = unwind_setreg_ufpustate(me->cs_cpu, regno, src)) != UNWIND_INVALID_REGISTER)
 * >>         return error;
 * >>     if ((error = unwind_setreg_fpustate(me->cs_fpu, regno, src)) != UNWIND_INVALID_REGISTER)
 * >>         return error;
 * >>     return UNWIND_INVALID_REGISTER;
 * >> }
 * NOTE: *_exclusive functions  will always  return  `UNWIND_INVALID_REGISTER' when  attempting  to
 *       access persistent registers that are  not present within the  given CPU state, as  opposed
 *       to reading the current register value during get, and returning `CURRENT_VAL() == new_val'
 *       on set (aka.: setreg()  normally returns true  for untraced registers  when the old  value
 *       matches the new one) */


#define __LIBUNWIND_GETREG_GENERATE_ASMNAME2(xcpustate)             unwind_getreg_##xcpustate
#define __LIBUNWIND_SETREG_GENERATE_ASMNAME2(xcpustate)             unwind_setreg_##xcpustate
#define __LIBUNWIND_SETREG_P_GENERATE_ASMNAME2(xcpustate)           unwind_getreg_##xcpustate##_p
#define __LIBUNWIND_GETREG_EXCLUSIVE_GENERATE_ASMNAME2(xcpustate)   unwind_getreg_##xcpustate##_exclusive
#define __LIBUNWIND_SETREG_EXCLUSIVE_GENERATE_ASMNAME2(xcpustate)   unwind_setreg_##xcpustate##_exclusive
#define __LIBUNWIND_SETREG_P_EXCLUSIVE_GENERATE_ASMNAME2(xcpustate) unwind_getreg_##xcpustate##_exclusive_p
#define __LIBUNWIND_GETREG_GENERATE_ASMNAME(xcpustate)              __LIBUNWIND_GETREG_GENERATE_ASMNAME2(xcpustate)
#define __LIBUNWIND_SETREG_GENERATE_ASMNAME(xcpustate)              __LIBUNWIND_SETREG_GENERATE_ASMNAME2(xcpustate)
#define __LIBUNWIND_SETREG_P_GENERATE_ASMNAME(xcpustate)            __LIBUNWIND_SETREG_P_GENERATE_ASMNAME2(xcpustate)
#define __LIBUNWIND_GETREG_EXCLUSIVE_GENERATE_ASMNAME(xcpustate)    __LIBUNWIND_GETREG_EXCLUSIVE_GENERATE_ASMNAME2(xcpustate)
#define __LIBUNWIND_SETREG_EXCLUSIVE_GENERATE_ASMNAME(xcpustate)    __LIBUNWIND_SETREG_EXCLUSIVE_GENERATE_ASMNAME2(xcpustate)
#define __LIBUNWIND_SETREG_P_EXCLUSIVE_GENERATE_ASMNAME(xcpustate)  __LIBUNWIND_SETREG_P_EXCLUSIVE_GENERATE_ASMNAME2(xcpustate)

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
	print("#ifdef LIBUNWIND_HAVE_GETSETREG_", STATE);
	print("typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_", STATE, ")(/" "*struct ", state, "**" "/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);");
	print("typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_", STATE, "_EXCLUSIVE)(/" "*struct ", state, "**" "/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);");
	print("#ifdef LIBUNWIND_HAVE_GETSETREG_", STATE, "_P");
	print("typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_", STATE, "_P)(/" "*struct ", state, "***" "/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);");
	print("typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_", STATE, "_EXCLUSIVE_P)(/" "*struct ", state, "***" "/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);");
	print("#else /" "* LIBUNWIND_HAVE_GETSETREG_", STATE, "_P *" "/");
	print("typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_", STATE, ")(/" "*struct ", state, "**" "/ void *__state, unwind_regno_t __regno, void const *__restrict __src);");
	print("typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_", STATE, "_EXCLUSIVE)(/" "*struct ", state, "**" "/ void *__state, unwind_regno_t __regno, void const *__restrict __src);");
	print("#endif /" "* !LIBUNWIND_HAVE_GETSETREG_", STATE, "_P *" "/");
	if (aliases) {
		print("#ifdef ", STATE, "_ALIAS");
		print("#define UNWIND_GETREG_", STATE, '_NAME           "unwind_getreg_" ', STATE, '_ALIAS_STR');
		print("#define UNWIND_GETREG_", STATE, '_EXCLUSIVE_NAME "unwind_getreg_" ', STATE, '_ALIAS_STR "_exclusive"');
		print("#ifdef LIBUNWIND_HAVE_GETSETREG_", STATE, "_P");
		print("#define UNWIND_SETREG_", STATE, '_P_NAME           "unwind_setreg_" ', STATE, '_ALIAS_STR "_p"');
		print("#define UNWIND_SETREG_", STATE, '_EXCLUSIVE_P_NAME "unwind_setreg_" ', STATE, '_ALIAS_STR "_exclusive_p"');
		print("#else /" "* LIBUNWIND_HAVE_GETSETREG_", STATE, "_P *" "/");
		print("#define UNWIND_SETREG_", STATE, '_NAME           "unwind_setreg_" ', STATE, '_ALIAS_STR');
		print("#define UNWIND_SETREG_", STATE, '_EXCLUSIVE_NAME "unwind_setreg_" ', STATE, '_ALIAS_STR "_exclusive"');
		print("#endif /" "* !LIBUNWIND_HAVE_GETSETREG_", STATE, "_P *" "/");
		print("#else /" "* ", STATE, "_ALIAS *" "/");
	}
	print("#define UNWIND_GETREG_", STATE, "_NAME           ", repr(f"unwind_getreg_{state}"));
	print("#define UNWIND_GETREG_", STATE, "_EXCLUSIVE_NAME ", repr(f"unwind_getreg_{state}_exclusive"));
	print("#ifdef LIBUNWIND_HAVE_GETSETREG_", STATE, "_P");
	print("#define UNWIND_SETREG_", STATE, "_P_NAME           ", repr(f"unwind_setreg_{state}_p"));
	print("#define UNWIND_SETREG_", STATE, "_EXCLUSIVE_P_NAME ", repr(f"unwind_setreg_{state}_exclusive_p"));
	print("#else /" "* LIBUNWIND_HAVE_GETSETREG_", STATE, "_P *" "/");
	print("#define UNWIND_SETREG_", STATE, "_NAME           ", repr(f"unwind_setreg_{state}"));
	print("#define UNWIND_SETREG_", STATE, "_EXCLUSIVE_NAME ", repr(f"unwind_setreg_{state}_exclusive"));
	print("#endif /" "* !LIBUNWIND_HAVE_GETSETREG_", STATE, "_P *" "/");
	if (aliases)
		print("#endif /" "* !", STATE, "_ALIAS *" "/");


	print("#ifdef LIBUNWIND_WANT_PROTOTYPES");
	if (aliases) {
		print("#ifdef ", STATE, "_ALIAS");
		print("__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_getreg_", state, ",(/" "*struct ", state, "**" "/ void const *__state, unwind_regno_t __regno, void *__restrict __dst),__LIBUNWIND_GETREG_GENERATE_ASMNAME(", STATE, "_ALIAS),(__state,__regno,__dst))");
		print("__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_getreg_", state, "_exclusive,(/" "*struct ", state, "**" "/ void const *__state, unwind_regno_t __regno, void *__restrict __dst),__LIBUNWIND_GETREG_EXCLUSIVE_GENERATE_ASMNAME(", STATE, "_ALIAS),(__state,__regno,__dst))");
		print("#ifdef LIBUNWIND_HAVE_GETSETREG_", STATE, "_P");
		print("__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_", state, "_p,(/" "*struct ", state, "***" "/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_P_GENERATE_ASMNAME(", STATE, "_ALIAS),(__p_state,__regno,__src))");
		print("__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_", state, "_exclusive_p,(/" "*struct ", state, "***" "/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_EXCLUSIVE_P_GENERATE_ASMNAME(", STATE, "_ALIAS),(__p_state,__regno,__src))");
		print("#else /" "* LIBUNWIND_HAVE_GETSETREG_", STATE, "_P *" "/");
		print("__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_", state, ",(/" "*struct ", state, "**" "/ void *__state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_GENERATE_ASMNAME(", STATE, "_ALIAS),(__state,__regno,__src))");
		print("__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_", state, "_exclusive,(/" "*struct ", state, "**" "/ void *__state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_EXCLUSIVE_GENERATE_ASMNAME(", STATE, "_ALIAS),(__state,__regno,__src))");
		print("#endif /" "* !LIBUNWIND_HAVE_GETSETREG_", STATE, "_P *" "/");
		print("#else /" "* ", STATE, "_ALIAS *" "/");
	}
	function printSetRegPMacros() {
		print("#define unwind_setreg_", state, "_p(p_state, regno, src)           unwind_setreg_", state, "(*(struct ", state, " **)(p_state), regno, src) ");
		print("#define unwind_setreg_", state, "_exclusive_p(p_state, regno, src) unwind_setreg_", state, "_exclusive(*(struct ", state, " **)(p_state), regno, src) ");
	}
	print("LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_", state, ")(/" "*struct ", state, "**" "/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);");
	print("LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_", state, "_exclusive)(/" "*struct ", state, "**" "/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);");
	print("#ifdef LIBUNWIND_HAVE_GETSETREG_", STATE, "_P");
	print("LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_", state, "_p)(/" "*struct ", state, "***" "/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);");
	print("LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_", state, "_exclusive_p)(/" "*struct ", state, "***" "/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);");
	print("#else /" "* LIBUNWIND_HAVE_GETSETREG_", STATE, "_P *" "/");
	print("LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_", state, ")(/" "*struct ", state, "**" "/ void *__state, unwind_regno_t __regno, void const *__restrict __src);");
	print("LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_", state, "_exclusive)(/" "*struct ", state, "**" "/ void *__state, unwind_regno_t __regno, void const *__restrict __src);");
	if (!aliases)
		printSetRegPMacros();
	print("#endif /" "* !LIBUNWIND_HAVE_GETSETREG_", STATE, "_P *" "/");
	if (aliases) {
		print("#endif /" "* !", STATE, "_ALIAS *" "/");
		print("#ifndef LIBUNWIND_HAVE_GETSETREG_", STATE, "_P");
		printSetRegPMacros();
		print("#endif /" "* LIBUNWIND_HAVE_GETSETREG_", STATE, "_P *" "/");
	}
	print("#endif /" "* LIBUNWIND_WANT_PROTOTYPES *" "/");
	print("#endif /" "* LIBUNWIND_HAVE_GETSETREG_", STATE, " *" "/");
	print;
}
]]]*/
/************************************************************************/
/* ucpustate                                                            */
/************************************************************************/
#ifdef LIBUNWIND_HAVE_GETSETREG_UCPUSTATE
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_UCPUSTATE)(/*struct ucpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_UCPUSTATE_EXCLUSIVE)(/*struct ucpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_UCPUSTATE_P
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_UCPUSTATE_P)(/*struct ucpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_UCPUSTATE_EXCLUSIVE_P)(/*struct ucpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
#else /* LIBUNWIND_HAVE_GETSETREG_UCPUSTATE_P */
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_UCPUSTATE)(/*struct ucpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_UCPUSTATE_EXCLUSIVE)(/*struct ucpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_UCPUSTATE_P */
#define UNWIND_GETREG_UCPUSTATE_NAME           "unwind_getreg_ucpustate"
#define UNWIND_GETREG_UCPUSTATE_EXCLUSIVE_NAME "unwind_getreg_ucpustate_exclusive"
#ifdef LIBUNWIND_HAVE_GETSETREG_UCPUSTATE_P
#define UNWIND_SETREG_UCPUSTATE_P_NAME           "unwind_setreg_ucpustate_p"
#define UNWIND_SETREG_UCPUSTATE_EXCLUSIVE_P_NAME "unwind_setreg_ucpustate_exclusive_p"
#else /* LIBUNWIND_HAVE_GETSETREG_UCPUSTATE_P */
#define UNWIND_SETREG_UCPUSTATE_NAME           "unwind_setreg_ucpustate"
#define UNWIND_SETREG_UCPUSTATE_EXCLUSIVE_NAME "unwind_setreg_ucpustate_exclusive"
#endif /* !LIBUNWIND_HAVE_GETSETREG_UCPUSTATE_P */
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_ucpustate)(/*struct ucpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_ucpustate_exclusive)(/*struct ucpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_UCPUSTATE_P
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_ucpustate_p)(/*struct ucpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_ucpustate_exclusive_p)(/*struct ucpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
#else /* LIBUNWIND_HAVE_GETSETREG_UCPUSTATE_P */
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_ucpustate)(/*struct ucpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_ucpustate_exclusive)(/*struct ucpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
#define unwind_setreg_ucpustate_p(p_state, regno, src)           unwind_setreg_ucpustate(*(struct ucpustate **)(p_state), regno, src)
#define unwind_setreg_ucpustate_exclusive_p(p_state, regno, src) unwind_setreg_ucpustate_exclusive(*(struct ucpustate **)(p_state), regno, src)
#endif /* !LIBUNWIND_HAVE_GETSETREG_UCPUSTATE_P */
#endif /* LIBUNWIND_WANT_PROTOTYPES */
#endif /* LIBUNWIND_HAVE_GETSETREG_UCPUSTATE */

/************************************************************************/
/* lcpustate                                                            */
/************************************************************************/
#ifdef LIBUNWIND_HAVE_GETSETREG_LCPUSTATE
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_LCPUSTATE)(/*struct lcpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_LCPUSTATE_EXCLUSIVE)(/*struct lcpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_LCPUSTATE_P
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_LCPUSTATE_P)(/*struct lcpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_LCPUSTATE_EXCLUSIVE_P)(/*struct lcpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
#else /* LIBUNWIND_HAVE_GETSETREG_LCPUSTATE_P */
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_LCPUSTATE)(/*struct lcpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_LCPUSTATE_EXCLUSIVE)(/*struct lcpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_LCPUSTATE_P */
#ifdef LCPUSTATE_ALIAS
#define UNWIND_GETREG_LCPUSTATE_NAME           "unwind_getreg_" LCPUSTATE_ALIAS_STR
#define UNWIND_GETREG_LCPUSTATE_EXCLUSIVE_NAME "unwind_getreg_" LCPUSTATE_ALIAS_STR "_exclusive"
#ifdef LIBUNWIND_HAVE_GETSETREG_LCPUSTATE_P
#define UNWIND_SETREG_LCPUSTATE_P_NAME           "unwind_setreg_" LCPUSTATE_ALIAS_STR "_p"
#define UNWIND_SETREG_LCPUSTATE_EXCLUSIVE_P_NAME "unwind_setreg_" LCPUSTATE_ALIAS_STR "_exclusive_p"
#else /* LIBUNWIND_HAVE_GETSETREG_LCPUSTATE_P */
#define UNWIND_SETREG_LCPUSTATE_NAME           "unwind_setreg_" LCPUSTATE_ALIAS_STR
#define UNWIND_SETREG_LCPUSTATE_EXCLUSIVE_NAME "unwind_setreg_" LCPUSTATE_ALIAS_STR "_exclusive"
#endif /* !LIBUNWIND_HAVE_GETSETREG_LCPUSTATE_P */
#else /* LCPUSTATE_ALIAS */
#define UNWIND_GETREG_LCPUSTATE_NAME           "unwind_getreg_lcpustate"
#define UNWIND_GETREG_LCPUSTATE_EXCLUSIVE_NAME "unwind_getreg_lcpustate_exclusive"
#ifdef LIBUNWIND_HAVE_GETSETREG_LCPUSTATE_P
#define UNWIND_SETREG_LCPUSTATE_P_NAME           "unwind_setreg_lcpustate_p"
#define UNWIND_SETREG_LCPUSTATE_EXCLUSIVE_P_NAME "unwind_setreg_lcpustate_exclusive_p"
#else /* LIBUNWIND_HAVE_GETSETREG_LCPUSTATE_P */
#define UNWIND_SETREG_LCPUSTATE_NAME           "unwind_setreg_lcpustate"
#define UNWIND_SETREG_LCPUSTATE_EXCLUSIVE_NAME "unwind_setreg_lcpustate_exclusive"
#endif /* !LIBUNWIND_HAVE_GETSETREG_LCPUSTATE_P */
#endif /* !LCPUSTATE_ALIAS */
#ifdef LIBUNWIND_WANT_PROTOTYPES
#ifdef LCPUSTATE_ALIAS
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_getreg_lcpustate,(/*struct lcpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst),__LIBUNWIND_GETREG_GENERATE_ASMNAME(LCPUSTATE_ALIAS),(__state,__regno,__dst))
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_getreg_lcpustate_exclusive,(/*struct lcpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst),__LIBUNWIND_GETREG_EXCLUSIVE_GENERATE_ASMNAME(LCPUSTATE_ALIAS),(__state,__regno,__dst))
#ifdef LIBUNWIND_HAVE_GETSETREG_LCPUSTATE_P
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_lcpustate_p,(/*struct lcpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_P_GENERATE_ASMNAME(LCPUSTATE_ALIAS),(__p_state,__regno,__src))
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_lcpustate_exclusive_p,(/*struct lcpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_EXCLUSIVE_P_GENERATE_ASMNAME(LCPUSTATE_ALIAS),(__p_state,__regno,__src))
#else /* LIBUNWIND_HAVE_GETSETREG_LCPUSTATE_P */
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_lcpustate,(/*struct lcpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_GENERATE_ASMNAME(LCPUSTATE_ALIAS),(__state,__regno,__src))
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_lcpustate_exclusive,(/*struct lcpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_EXCLUSIVE_GENERATE_ASMNAME(LCPUSTATE_ALIAS),(__state,__regno,__src))
#endif /* !LIBUNWIND_HAVE_GETSETREG_LCPUSTATE_P */
#else /* LCPUSTATE_ALIAS */
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_lcpustate)(/*struct lcpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_lcpustate_exclusive)(/*struct lcpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_LCPUSTATE_P
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_lcpustate_p)(/*struct lcpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_lcpustate_exclusive_p)(/*struct lcpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
#else /* LIBUNWIND_HAVE_GETSETREG_LCPUSTATE_P */
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_lcpustate)(/*struct lcpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_lcpustate_exclusive)(/*struct lcpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_LCPUSTATE_P */
#endif /* !LCPUSTATE_ALIAS */
#ifndef LIBUNWIND_HAVE_GETSETREG_LCPUSTATE_P
#define unwind_setreg_lcpustate_p(p_state, regno, src)           unwind_setreg_lcpustate(*(struct lcpustate **)(p_state), regno, src)
#define unwind_setreg_lcpustate_exclusive_p(p_state, regno, src) unwind_setreg_lcpustate_exclusive(*(struct lcpustate **)(p_state), regno, src)
#endif /* LIBUNWIND_HAVE_GETSETREG_LCPUSTATE_P */
#endif /* LIBUNWIND_WANT_PROTOTYPES */
#endif /* LIBUNWIND_HAVE_GETSETREG_LCPUSTATE */

/************************************************************************/
/* kcpustate                                                            */
/************************************************************************/
#ifdef LIBUNWIND_HAVE_GETSETREG_KCPUSTATE
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_KCPUSTATE)(/*struct kcpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_KCPUSTATE_EXCLUSIVE)(/*struct kcpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_KCPUSTATE_P
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_KCPUSTATE_P)(/*struct kcpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_KCPUSTATE_EXCLUSIVE_P)(/*struct kcpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
#else /* LIBUNWIND_HAVE_GETSETREG_KCPUSTATE_P */
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_KCPUSTATE)(/*struct kcpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_KCPUSTATE_EXCLUSIVE)(/*struct kcpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_KCPUSTATE_P */
#ifdef KCPUSTATE_ALIAS
#define UNWIND_GETREG_KCPUSTATE_NAME           "unwind_getreg_" KCPUSTATE_ALIAS_STR
#define UNWIND_GETREG_KCPUSTATE_EXCLUSIVE_NAME "unwind_getreg_" KCPUSTATE_ALIAS_STR "_exclusive"
#ifdef LIBUNWIND_HAVE_GETSETREG_KCPUSTATE_P
#define UNWIND_SETREG_KCPUSTATE_P_NAME           "unwind_setreg_" KCPUSTATE_ALIAS_STR "_p"
#define UNWIND_SETREG_KCPUSTATE_EXCLUSIVE_P_NAME "unwind_setreg_" KCPUSTATE_ALIAS_STR "_exclusive_p"
#else /* LIBUNWIND_HAVE_GETSETREG_KCPUSTATE_P */
#define UNWIND_SETREG_KCPUSTATE_NAME           "unwind_setreg_" KCPUSTATE_ALIAS_STR
#define UNWIND_SETREG_KCPUSTATE_EXCLUSIVE_NAME "unwind_setreg_" KCPUSTATE_ALIAS_STR "_exclusive"
#endif /* !LIBUNWIND_HAVE_GETSETREG_KCPUSTATE_P */
#else /* KCPUSTATE_ALIAS */
#define UNWIND_GETREG_KCPUSTATE_NAME           "unwind_getreg_kcpustate"
#define UNWIND_GETREG_KCPUSTATE_EXCLUSIVE_NAME "unwind_getreg_kcpustate_exclusive"
#ifdef LIBUNWIND_HAVE_GETSETREG_KCPUSTATE_P
#define UNWIND_SETREG_KCPUSTATE_P_NAME           "unwind_setreg_kcpustate_p"
#define UNWIND_SETREG_KCPUSTATE_EXCLUSIVE_P_NAME "unwind_setreg_kcpustate_exclusive_p"
#else /* LIBUNWIND_HAVE_GETSETREG_KCPUSTATE_P */
#define UNWIND_SETREG_KCPUSTATE_NAME           "unwind_setreg_kcpustate"
#define UNWIND_SETREG_KCPUSTATE_EXCLUSIVE_NAME "unwind_setreg_kcpustate_exclusive"
#endif /* !LIBUNWIND_HAVE_GETSETREG_KCPUSTATE_P */
#endif /* !KCPUSTATE_ALIAS */
#ifdef LIBUNWIND_WANT_PROTOTYPES
#ifdef KCPUSTATE_ALIAS
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_getreg_kcpustate,(/*struct kcpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst),__LIBUNWIND_GETREG_GENERATE_ASMNAME(KCPUSTATE_ALIAS),(__state,__regno,__dst))
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_getreg_kcpustate_exclusive,(/*struct kcpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst),__LIBUNWIND_GETREG_EXCLUSIVE_GENERATE_ASMNAME(KCPUSTATE_ALIAS),(__state,__regno,__dst))
#ifdef LIBUNWIND_HAVE_GETSETREG_KCPUSTATE_P
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_kcpustate_p,(/*struct kcpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_P_GENERATE_ASMNAME(KCPUSTATE_ALIAS),(__p_state,__regno,__src))
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_kcpustate_exclusive_p,(/*struct kcpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_EXCLUSIVE_P_GENERATE_ASMNAME(KCPUSTATE_ALIAS),(__p_state,__regno,__src))
#else /* LIBUNWIND_HAVE_GETSETREG_KCPUSTATE_P */
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_kcpustate,(/*struct kcpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_GENERATE_ASMNAME(KCPUSTATE_ALIAS),(__state,__regno,__src))
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_kcpustate_exclusive,(/*struct kcpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_EXCLUSIVE_GENERATE_ASMNAME(KCPUSTATE_ALIAS),(__state,__regno,__src))
#endif /* !LIBUNWIND_HAVE_GETSETREG_KCPUSTATE_P */
#else /* KCPUSTATE_ALIAS */
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_kcpustate)(/*struct kcpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_kcpustate_exclusive)(/*struct kcpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_KCPUSTATE_P
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_kcpustate_p)(/*struct kcpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_kcpustate_exclusive_p)(/*struct kcpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
#else /* LIBUNWIND_HAVE_GETSETREG_KCPUSTATE_P */
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_kcpustate)(/*struct kcpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_kcpustate_exclusive)(/*struct kcpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_KCPUSTATE_P */
#endif /* !KCPUSTATE_ALIAS */
#ifndef LIBUNWIND_HAVE_GETSETREG_KCPUSTATE_P
#define unwind_setreg_kcpustate_p(p_state, regno, src)           unwind_setreg_kcpustate(*(struct kcpustate **)(p_state), regno, src)
#define unwind_setreg_kcpustate_exclusive_p(p_state, regno, src) unwind_setreg_kcpustate_exclusive(*(struct kcpustate **)(p_state), regno, src)
#endif /* LIBUNWIND_HAVE_GETSETREG_KCPUSTATE_P */
#endif /* LIBUNWIND_WANT_PROTOTYPES */
#endif /* LIBUNWIND_HAVE_GETSETREG_KCPUSTATE */

/************************************************************************/
/* icpustate                                                            */
/************************************************************************/
#ifdef LIBUNWIND_HAVE_GETSETREG_ICPUSTATE
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_ICPUSTATE)(/*struct icpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_ICPUSTATE_EXCLUSIVE)(/*struct icpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_ICPUSTATE_P)(/*struct icpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_ICPUSTATE_EXCLUSIVE_P)(/*struct icpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
#else /* LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P */
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_ICPUSTATE)(/*struct icpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_ICPUSTATE_EXCLUSIVE)(/*struct icpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P */
#ifdef ICPUSTATE_ALIAS
#define UNWIND_GETREG_ICPUSTATE_NAME           "unwind_getreg_" ICPUSTATE_ALIAS_STR
#define UNWIND_GETREG_ICPUSTATE_EXCLUSIVE_NAME "unwind_getreg_" ICPUSTATE_ALIAS_STR "_exclusive"
#ifdef LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P
#define UNWIND_SETREG_ICPUSTATE_P_NAME           "unwind_setreg_" ICPUSTATE_ALIAS_STR "_p"
#define UNWIND_SETREG_ICPUSTATE_EXCLUSIVE_P_NAME "unwind_setreg_" ICPUSTATE_ALIAS_STR "_exclusive_p"
#else /* LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P */
#define UNWIND_SETREG_ICPUSTATE_NAME           "unwind_setreg_" ICPUSTATE_ALIAS_STR
#define UNWIND_SETREG_ICPUSTATE_EXCLUSIVE_NAME "unwind_setreg_" ICPUSTATE_ALIAS_STR "_exclusive"
#endif /* !LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P */
#else /* ICPUSTATE_ALIAS */
#define UNWIND_GETREG_ICPUSTATE_NAME           "unwind_getreg_icpustate"
#define UNWIND_GETREG_ICPUSTATE_EXCLUSIVE_NAME "unwind_getreg_icpustate_exclusive"
#ifdef LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P
#define UNWIND_SETREG_ICPUSTATE_P_NAME           "unwind_setreg_icpustate_p"
#define UNWIND_SETREG_ICPUSTATE_EXCLUSIVE_P_NAME "unwind_setreg_icpustate_exclusive_p"
#else /* LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P */
#define UNWIND_SETREG_ICPUSTATE_NAME           "unwind_setreg_icpustate"
#define UNWIND_SETREG_ICPUSTATE_EXCLUSIVE_NAME "unwind_setreg_icpustate_exclusive"
#endif /* !LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P */
#endif /* !ICPUSTATE_ALIAS */
#ifdef LIBUNWIND_WANT_PROTOTYPES
#ifdef ICPUSTATE_ALIAS
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_getreg_icpustate,(/*struct icpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst),__LIBUNWIND_GETREG_GENERATE_ASMNAME(ICPUSTATE_ALIAS),(__state,__regno,__dst))
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_getreg_icpustate_exclusive,(/*struct icpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst),__LIBUNWIND_GETREG_EXCLUSIVE_GENERATE_ASMNAME(ICPUSTATE_ALIAS),(__state,__regno,__dst))
#ifdef LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_icpustate_p,(/*struct icpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_P_GENERATE_ASMNAME(ICPUSTATE_ALIAS),(__p_state,__regno,__src))
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_icpustate_exclusive_p,(/*struct icpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_EXCLUSIVE_P_GENERATE_ASMNAME(ICPUSTATE_ALIAS),(__p_state,__regno,__src))
#else /* LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P */
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_icpustate,(/*struct icpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_GENERATE_ASMNAME(ICPUSTATE_ALIAS),(__state,__regno,__src))
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_icpustate_exclusive,(/*struct icpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_EXCLUSIVE_GENERATE_ASMNAME(ICPUSTATE_ALIAS),(__state,__regno,__src))
#endif /* !LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P */
#else /* ICPUSTATE_ALIAS */
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_icpustate)(/*struct icpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_icpustate_exclusive)(/*struct icpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_icpustate_p)(/*struct icpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_icpustate_exclusive_p)(/*struct icpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
#else /* LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P */
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_icpustate)(/*struct icpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_icpustate_exclusive)(/*struct icpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P */
#endif /* !ICPUSTATE_ALIAS */
#ifndef LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P
#define unwind_setreg_icpustate_p(p_state, regno, src)           unwind_setreg_icpustate(*(struct icpustate **)(p_state), regno, src)
#define unwind_setreg_icpustate_exclusive_p(p_state, regno, src) unwind_setreg_icpustate_exclusive(*(struct icpustate **)(p_state), regno, src)
#endif /* LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P */
#endif /* LIBUNWIND_WANT_PROTOTYPES */
#endif /* LIBUNWIND_HAVE_GETSETREG_ICPUSTATE */

/************************************************************************/
/* scpustate                                                            */
/************************************************************************/
#ifdef LIBUNWIND_HAVE_GETSETREG_SCPUSTATE
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_SCPUSTATE)(/*struct scpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_SCPUSTATE_EXCLUSIVE)(/*struct scpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_SCPUSTATE_P)(/*struct scpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_SCPUSTATE_EXCLUSIVE_P)(/*struct scpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
#else /* LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P */
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_SCPUSTATE)(/*struct scpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_SCPUSTATE_EXCLUSIVE)(/*struct scpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P */
#ifdef SCPUSTATE_ALIAS
#define UNWIND_GETREG_SCPUSTATE_NAME           "unwind_getreg_" SCPUSTATE_ALIAS_STR
#define UNWIND_GETREG_SCPUSTATE_EXCLUSIVE_NAME "unwind_getreg_" SCPUSTATE_ALIAS_STR "_exclusive"
#ifdef LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P
#define UNWIND_SETREG_SCPUSTATE_P_NAME           "unwind_setreg_" SCPUSTATE_ALIAS_STR "_p"
#define UNWIND_SETREG_SCPUSTATE_EXCLUSIVE_P_NAME "unwind_setreg_" SCPUSTATE_ALIAS_STR "_exclusive_p"
#else /* LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P */
#define UNWIND_SETREG_SCPUSTATE_NAME           "unwind_setreg_" SCPUSTATE_ALIAS_STR
#define UNWIND_SETREG_SCPUSTATE_EXCLUSIVE_NAME "unwind_setreg_" SCPUSTATE_ALIAS_STR "_exclusive"
#endif /* !LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P */
#else /* SCPUSTATE_ALIAS */
#define UNWIND_GETREG_SCPUSTATE_NAME           "unwind_getreg_scpustate"
#define UNWIND_GETREG_SCPUSTATE_EXCLUSIVE_NAME "unwind_getreg_scpustate_exclusive"
#ifdef LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P
#define UNWIND_SETREG_SCPUSTATE_P_NAME           "unwind_setreg_scpustate_p"
#define UNWIND_SETREG_SCPUSTATE_EXCLUSIVE_P_NAME "unwind_setreg_scpustate_exclusive_p"
#else /* LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P */
#define UNWIND_SETREG_SCPUSTATE_NAME           "unwind_setreg_scpustate"
#define UNWIND_SETREG_SCPUSTATE_EXCLUSIVE_NAME "unwind_setreg_scpustate_exclusive"
#endif /* !LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P */
#endif /* !SCPUSTATE_ALIAS */
#ifdef LIBUNWIND_WANT_PROTOTYPES
#ifdef SCPUSTATE_ALIAS
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_getreg_scpustate,(/*struct scpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst),__LIBUNWIND_GETREG_GENERATE_ASMNAME(SCPUSTATE_ALIAS),(__state,__regno,__dst))
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_getreg_scpustate_exclusive,(/*struct scpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst),__LIBUNWIND_GETREG_EXCLUSIVE_GENERATE_ASMNAME(SCPUSTATE_ALIAS),(__state,__regno,__dst))
#ifdef LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_scpustate_p,(/*struct scpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_P_GENERATE_ASMNAME(SCPUSTATE_ALIAS),(__p_state,__regno,__src))
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_scpustate_exclusive_p,(/*struct scpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_EXCLUSIVE_P_GENERATE_ASMNAME(SCPUSTATE_ALIAS),(__p_state,__regno,__src))
#else /* LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P */
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_scpustate,(/*struct scpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_GENERATE_ASMNAME(SCPUSTATE_ALIAS),(__state,__regno,__src))
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_scpustate_exclusive,(/*struct scpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_EXCLUSIVE_GENERATE_ASMNAME(SCPUSTATE_ALIAS),(__state,__regno,__src))
#endif /* !LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P */
#else /* SCPUSTATE_ALIAS */
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_scpustate)(/*struct scpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_scpustate_exclusive)(/*struct scpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_scpustate_p)(/*struct scpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_scpustate_exclusive_p)(/*struct scpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
#else /* LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P */
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_scpustate)(/*struct scpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_scpustate_exclusive)(/*struct scpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P */
#endif /* !SCPUSTATE_ALIAS */
#ifndef LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P
#define unwind_setreg_scpustate_p(p_state, regno, src)           unwind_setreg_scpustate(*(struct scpustate **)(p_state), regno, src)
#define unwind_setreg_scpustate_exclusive_p(p_state, regno, src) unwind_setreg_scpustate_exclusive(*(struct scpustate **)(p_state), regno, src)
#endif /* LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P */
#endif /* LIBUNWIND_WANT_PROTOTYPES */
#endif /* LIBUNWIND_HAVE_GETSETREG_SCPUSTATE */

/************************************************************************/
/* fcpustate                                                            */
/************************************************************************/
#ifdef LIBUNWIND_HAVE_GETSETREG_FCPUSTATE
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_FCPUSTATE)(/*struct fcpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_FCPUSTATE_EXCLUSIVE)(/*struct fcpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_FCPUSTATE_P
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_FCPUSTATE_P)(/*struct fcpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_FCPUSTATE_EXCLUSIVE_P)(/*struct fcpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
#else /* LIBUNWIND_HAVE_GETSETREG_FCPUSTATE_P */
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_FCPUSTATE)(/*struct fcpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_FCPUSTATE_EXCLUSIVE)(/*struct fcpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_FCPUSTATE_P */
#ifdef FCPUSTATE_ALIAS
#define UNWIND_GETREG_FCPUSTATE_NAME           "unwind_getreg_" FCPUSTATE_ALIAS_STR
#define UNWIND_GETREG_FCPUSTATE_EXCLUSIVE_NAME "unwind_getreg_" FCPUSTATE_ALIAS_STR "_exclusive"
#ifdef LIBUNWIND_HAVE_GETSETREG_FCPUSTATE_P
#define UNWIND_SETREG_FCPUSTATE_P_NAME           "unwind_setreg_" FCPUSTATE_ALIAS_STR "_p"
#define UNWIND_SETREG_FCPUSTATE_EXCLUSIVE_P_NAME "unwind_setreg_" FCPUSTATE_ALIAS_STR "_exclusive_p"
#else /* LIBUNWIND_HAVE_GETSETREG_FCPUSTATE_P */
#define UNWIND_SETREG_FCPUSTATE_NAME           "unwind_setreg_" FCPUSTATE_ALIAS_STR
#define UNWIND_SETREG_FCPUSTATE_EXCLUSIVE_NAME "unwind_setreg_" FCPUSTATE_ALIAS_STR "_exclusive"
#endif /* !LIBUNWIND_HAVE_GETSETREG_FCPUSTATE_P */
#else /* FCPUSTATE_ALIAS */
#define UNWIND_GETREG_FCPUSTATE_NAME           "unwind_getreg_fcpustate"
#define UNWIND_GETREG_FCPUSTATE_EXCLUSIVE_NAME "unwind_getreg_fcpustate_exclusive"
#ifdef LIBUNWIND_HAVE_GETSETREG_FCPUSTATE_P
#define UNWIND_SETREG_FCPUSTATE_P_NAME           "unwind_setreg_fcpustate_p"
#define UNWIND_SETREG_FCPUSTATE_EXCLUSIVE_P_NAME "unwind_setreg_fcpustate_exclusive_p"
#else /* LIBUNWIND_HAVE_GETSETREG_FCPUSTATE_P */
#define UNWIND_SETREG_FCPUSTATE_NAME           "unwind_setreg_fcpustate"
#define UNWIND_SETREG_FCPUSTATE_EXCLUSIVE_NAME "unwind_setreg_fcpustate_exclusive"
#endif /* !LIBUNWIND_HAVE_GETSETREG_FCPUSTATE_P */
#endif /* !FCPUSTATE_ALIAS */
#ifdef LIBUNWIND_WANT_PROTOTYPES
#ifdef FCPUSTATE_ALIAS
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_getreg_fcpustate,(/*struct fcpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst),__LIBUNWIND_GETREG_GENERATE_ASMNAME(FCPUSTATE_ALIAS),(__state,__regno,__dst))
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_getreg_fcpustate_exclusive,(/*struct fcpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst),__LIBUNWIND_GETREG_EXCLUSIVE_GENERATE_ASMNAME(FCPUSTATE_ALIAS),(__state,__regno,__dst))
#ifdef LIBUNWIND_HAVE_GETSETREG_FCPUSTATE_P
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_fcpustate_p,(/*struct fcpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_P_GENERATE_ASMNAME(FCPUSTATE_ALIAS),(__p_state,__regno,__src))
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_fcpustate_exclusive_p,(/*struct fcpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_EXCLUSIVE_P_GENERATE_ASMNAME(FCPUSTATE_ALIAS),(__p_state,__regno,__src))
#else /* LIBUNWIND_HAVE_GETSETREG_FCPUSTATE_P */
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_fcpustate,(/*struct fcpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_GENERATE_ASMNAME(FCPUSTATE_ALIAS),(__state,__regno,__src))
__COMPILER_REDIRECT(LIBUNWIND_DECL,__ATTR_NONNULL((1, 3)),unwind_errno_t,__NOTHROW_NCX,LIBUNWIND_CC,unwind_setreg_fcpustate_exclusive,(/*struct fcpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src),__LIBUNWIND_SETREG_EXCLUSIVE_GENERATE_ASMNAME(FCPUSTATE_ALIAS),(__state,__regno,__src))
#endif /* !LIBUNWIND_HAVE_GETSETREG_FCPUSTATE_P */
#else /* FCPUSTATE_ALIAS */
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_fcpustate)(/*struct fcpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_fcpustate_exclusive)(/*struct fcpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_FCPUSTATE_P
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_fcpustate_p)(/*struct fcpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_fcpustate_exclusive_p)(/*struct fcpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
#else /* LIBUNWIND_HAVE_GETSETREG_FCPUSTATE_P */
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_fcpustate)(/*struct fcpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_fcpustate_exclusive)(/*struct fcpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_FCPUSTATE_P */
#endif /* !FCPUSTATE_ALIAS */
#ifndef LIBUNWIND_HAVE_GETSETREG_FCPUSTATE_P
#define unwind_setreg_fcpustate_p(p_state, regno, src)           unwind_setreg_fcpustate(*(struct fcpustate **)(p_state), regno, src)
#define unwind_setreg_fcpustate_exclusive_p(p_state, regno, src) unwind_setreg_fcpustate_exclusive(*(struct fcpustate **)(p_state), regno, src)
#endif /* LIBUNWIND_HAVE_GETSETREG_FCPUSTATE_P */
#endif /* LIBUNWIND_WANT_PROTOTYPES */
#endif /* LIBUNWIND_HAVE_GETSETREG_FCPUSTATE */

/************************************************************************/
/* mcontext                                                             */
/************************************************************************/
#ifdef LIBUNWIND_HAVE_GETSETREG_MCONTEXT
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_MCONTEXT)(/*struct mcontext**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_MCONTEXT_EXCLUSIVE)(/*struct mcontext**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_MCONTEXT_P
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_MCONTEXT_P)(/*struct mcontext***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_MCONTEXT_EXCLUSIVE_P)(/*struct mcontext***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
#else /* LIBUNWIND_HAVE_GETSETREG_MCONTEXT_P */
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_MCONTEXT)(/*struct mcontext**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_MCONTEXT_EXCLUSIVE)(/*struct mcontext**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_MCONTEXT_P */
#define UNWIND_GETREG_MCONTEXT_NAME           "unwind_getreg_mcontext"
#define UNWIND_GETREG_MCONTEXT_EXCLUSIVE_NAME "unwind_getreg_mcontext_exclusive"
#ifdef LIBUNWIND_HAVE_GETSETREG_MCONTEXT_P
#define UNWIND_SETREG_MCONTEXT_P_NAME           "unwind_setreg_mcontext_p"
#define UNWIND_SETREG_MCONTEXT_EXCLUSIVE_P_NAME "unwind_setreg_mcontext_exclusive_p"
#else /* LIBUNWIND_HAVE_GETSETREG_MCONTEXT_P */
#define UNWIND_SETREG_MCONTEXT_NAME           "unwind_setreg_mcontext"
#define UNWIND_SETREG_MCONTEXT_EXCLUSIVE_NAME "unwind_setreg_mcontext_exclusive"
#endif /* !LIBUNWIND_HAVE_GETSETREG_MCONTEXT_P */
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_mcontext)(/*struct mcontext**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_mcontext_exclusive)(/*struct mcontext**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_MCONTEXT_P
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_mcontext_p)(/*struct mcontext***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_mcontext_exclusive_p)(/*struct mcontext***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
#else /* LIBUNWIND_HAVE_GETSETREG_MCONTEXT_P */
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_mcontext)(/*struct mcontext**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_mcontext_exclusive)(/*struct mcontext**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
#define unwind_setreg_mcontext_p(p_state, regno, src)           unwind_setreg_mcontext(*(struct mcontext **)(p_state), regno, src)
#define unwind_setreg_mcontext_exclusive_p(p_state, regno, src) unwind_setreg_mcontext_exclusive(*(struct mcontext **)(p_state), regno, src)
#endif /* !LIBUNWIND_HAVE_GETSETREG_MCONTEXT_P */
#endif /* LIBUNWIND_WANT_PROTOTYPES */
#endif /* LIBUNWIND_HAVE_GETSETREG_MCONTEXT */

/************************************************************************/
/* ucontext                                                             */
/************************************************************************/
#ifdef LIBUNWIND_HAVE_GETSETREG_UCONTEXT
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_UCONTEXT)(/*struct ucontext**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_UCONTEXT_EXCLUSIVE)(/*struct ucontext**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_UCONTEXT_P
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_UCONTEXT_P)(/*struct ucontext***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_UCONTEXT_EXCLUSIVE_P)(/*struct ucontext***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
#else /* LIBUNWIND_HAVE_GETSETREG_UCONTEXT_P */
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_UCONTEXT)(/*struct ucontext**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_UCONTEXT_EXCLUSIVE)(/*struct ucontext**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_UCONTEXT_P */
#define UNWIND_GETREG_UCONTEXT_NAME           "unwind_getreg_ucontext"
#define UNWIND_GETREG_UCONTEXT_EXCLUSIVE_NAME "unwind_getreg_ucontext_exclusive"
#ifdef LIBUNWIND_HAVE_GETSETREG_UCONTEXT_P
#define UNWIND_SETREG_UCONTEXT_P_NAME           "unwind_setreg_ucontext_p"
#define UNWIND_SETREG_UCONTEXT_EXCLUSIVE_P_NAME "unwind_setreg_ucontext_exclusive_p"
#else /* LIBUNWIND_HAVE_GETSETREG_UCONTEXT_P */
#define UNWIND_SETREG_UCONTEXT_NAME           "unwind_setreg_ucontext"
#define UNWIND_SETREG_UCONTEXT_EXCLUSIVE_NAME "unwind_setreg_ucontext_exclusive"
#endif /* !LIBUNWIND_HAVE_GETSETREG_UCONTEXT_P */
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_ucontext)(/*struct ucontext**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_ucontext_exclusive)(/*struct ucontext**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_UCONTEXT_P
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_ucontext_p)(/*struct ucontext***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_ucontext_exclusive_p)(/*struct ucontext***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
#else /* LIBUNWIND_HAVE_GETSETREG_UCONTEXT_P */
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_ucontext)(/*struct ucontext**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_ucontext_exclusive)(/*struct ucontext**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
#define unwind_setreg_ucontext_p(p_state, regno, src)           unwind_setreg_ucontext(*(struct ucontext **)(p_state), regno, src)
#define unwind_setreg_ucontext_exclusive_p(p_state, regno, src) unwind_setreg_ucontext_exclusive(*(struct ucontext **)(p_state), regno, src)
#endif /* !LIBUNWIND_HAVE_GETSETREG_UCONTEXT_P */
#endif /* LIBUNWIND_WANT_PROTOTYPES */
#endif /* LIBUNWIND_HAVE_GETSETREG_UCONTEXT */

/************************************************************************/
/* fpustate                                                             */
/************************************************************************/
#ifdef LIBUNWIND_HAVE_GETSETREG_FPUSTATE
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_FPUSTATE)(/*struct fpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_FPUSTATE_EXCLUSIVE)(/*struct fpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_FPUSTATE_P
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_FPUSTATE_P)(/*struct fpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_FPUSTATE_EXCLUSIVE_P)(/*struct fpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
#else /* LIBUNWIND_HAVE_GETSETREG_FPUSTATE_P */
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_FPUSTATE)(/*struct fpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_FPUSTATE_EXCLUSIVE)(/*struct fpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
#endif /* !LIBUNWIND_HAVE_GETSETREG_FPUSTATE_P */
#define UNWIND_GETREG_FPUSTATE_NAME           "unwind_getreg_fpustate"
#define UNWIND_GETREG_FPUSTATE_EXCLUSIVE_NAME "unwind_getreg_fpustate_exclusive"
#ifdef LIBUNWIND_HAVE_GETSETREG_FPUSTATE_P
#define UNWIND_SETREG_FPUSTATE_P_NAME           "unwind_setreg_fpustate_p"
#define UNWIND_SETREG_FPUSTATE_EXCLUSIVE_P_NAME "unwind_setreg_fpustate_exclusive_p"
#else /* LIBUNWIND_HAVE_GETSETREG_FPUSTATE_P */
#define UNWIND_SETREG_FPUSTATE_NAME           "unwind_setreg_fpustate"
#define UNWIND_SETREG_FPUSTATE_EXCLUSIVE_NAME "unwind_setreg_fpustate_exclusive"
#endif /* !LIBUNWIND_HAVE_GETSETREG_FPUSTATE_P */
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_fpustate)(/*struct fpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_fpustate_exclusive)(/*struct fpustate**/ void const *__state, unwind_regno_t __regno, void *__restrict __dst);
#ifdef LIBUNWIND_HAVE_GETSETREG_FPUSTATE_P
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_fpustate_p)(/*struct fpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_fpustate_exclusive_p)(/*struct fpustate***/ void *__p_state, unwind_regno_t __regno, void const *__restrict __src);
#else /* LIBUNWIND_HAVE_GETSETREG_FPUSTATE_P */
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_fpustate)(/*struct fpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_fpustate_exclusive)(/*struct fpustate**/ void *__state, unwind_regno_t __regno, void const *__restrict __src);
#define unwind_setreg_fpustate_p(p_state, regno, src)           unwind_setreg_fpustate(*(struct fpustate **)(p_state), regno, src)
#define unwind_setreg_fpustate_exclusive_p(p_state, regno, src) unwind_setreg_fpustate_exclusive(*(struct fpustate **)(p_state), regno, src)
#endif /* !LIBUNWIND_HAVE_GETSETREG_FPUSTATE_P */
#endif /* LIBUNWIND_WANT_PROTOTYPES */
#endif /* LIBUNWIND_HAVE_GETSETREG_FPUSTATE */
/*[[[end]]]*/

#undef __LIBUNWIND_GETREG_GENERATE_ASMNAME2
#undef __LIBUNWIND_SETREG_GENERATE_ASMNAME2
#undef __LIBUNWIND_SETREG_P_GENERATE_ASMNAME2
#undef __LIBUNWIND_GETREG_EXCLUSIVE_GENERATE_ASMNAME2
#undef __LIBUNWIND_SETREG_EXCLUSIVE_GENERATE_ASMNAME2
#undef __LIBUNWIND_SETREG_P_EXCLUSIVE_GENERATE_ASMNAME2
#undef __LIBUNWIND_GETREG_GENERATE_ASMNAME
#undef __LIBUNWIND_SETREG_GENERATE_ASMNAME
#undef __LIBUNWIND_SETREG_P_GENERATE_ASMNAME
#undef __LIBUNWIND_GETREG_EXCLUSIVE_GENERATE_ASMNAME
#undef __LIBUNWIND_SETREG_EXCLUSIVE_GENERATE_ASMNAME
#undef __LIBUNWIND_SETREG_P_EXCLUSIVE_GENERATE_ASMNAME


/************************************************************************/
/* Helper wrapper for compatiblity-mode register access                 */
/************************************************************************/
#ifdef LIBUNWIND_HAVE_GETSETREG_COMPAT
struct unwind_getreg_compat_data {
	/* [1..1] The underlying, register getter function.
	 * @param: regno: One of `CFI_X86_64_UNWIND_REGISTER_*' */
	__ATTR_NONNULL((1, 3)) unwind_errno_t
	__NOTHROW_NCX_T(LIBUNWIND_CC *ugcd_getreg)(void const *__arg, unwind_regno_t __regno,
	                                           void *__restrict __dst);

	/* [?..?] Argument for `ugcd_getreg' */
	void const    *ugcd_arg;
};

struct unwind_setreg_compat_data {
	/* [1..1] The underlying, register setter function.
	 * @param: regno: One of `CFI_X86_64_UNWIND_REGISTER_*' */
	__ATTR_NONNULL((1, 3)) unwind_errno_t
	__NOTHROW_NCX_T(LIBUNWIND_CC *uscd_setreg)(void *__arg, unwind_regno_t __regno,
	                                           void const *__restrict __src);

	/* [?..?] Argument for `uscd_setreg' */
	void          *uscd_arg;
};

/* Initializers for the above data structures. */
#define unwind_getreg_compat_data_init(self, noncompat_getreg, noncompat_arg) \
	((self)->ugcd_getreg = (noncompat_getreg),                                \
	 (self)->ugcd_arg    = (noncompat_arg))
#define unwind_setreg_compat_data_init(self, noncompat_setreg, noncompat_arg) \
	((self)->uscd_setreg = (noncompat_setreg),                                \
	 (self)->uscd_arg    = (noncompat_arg))

#define UNWIND_GETREG_COMPAT_NAME "unwind_getreg_compat"
#define UNWIND_SETREG_COMPAT_NAME "unwind_setreg_compat"

/* Compatibility mode register get/set wrappers.
 * @param: regno: One of `CFI_386_UNWIND_REGISTER_*' */
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_GETREG_COMPAT)(/*struct unwind_getreg_compat_data **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t __NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_SETREG_COMPAT)(/*struct unwind_setreg_compat_data **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_compat)(/*struct unwind_getreg_compat_data **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_compat)(/*struct unwind_setreg_compat_data **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
#endif /* LIBUNWIND_WANT_PROTOTYPES */
#endif /* LIBUNWIND_HAVE_GETSETREG_COMPAT */


/************************************************************************/
/* Accessor functions for `__EXCEPT_REGISTER_STATE_TYPE'                */
/************************************************************************/
#ifdef __EXCEPT_REGISTER_STATE_TYPE_IS_LCPUSTATE
#define PUNWIND_GETREG_EXCEPT_REGISTER_STATE     PUNWIND_GETREG_LCPUSTATE
#define PUNWIND_SETREG_EXCEPT_REGISTER_STATE     PUNWIND_SETREG_LCPUSTATE
#define UNWIND_GETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_GETREG_LCPUSTATE_NAME
#define UNWIND_SETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_SETREG_LCPUSTATE_NAME
#ifdef LIBUNWIND_WANT_PROTOTYPES
#define unwind_getreg_except_register_state unwind_getreg_lcpustate
#define unwind_setreg_except_register_state unwind_setreg_lcpustate
#endif /* LIBUNWIND_WANT_PROTOTYPES */
#elif defined(__EXCEPT_REGISTER_STATE_TYPE_IS_UCPUSTATE)
#define PUNWIND_GETREG_EXCEPT_REGISTER_STATE     PUNWIND_GETREG_UCPUSTATE
#define PUNWIND_SETREG_EXCEPT_REGISTER_STATE     PUNWIND_SETREG_UCPUSTATE
#define UNWIND_GETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_GETREG_UCPUSTATE_NAME
#define UNWIND_SETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_SETREG_UCPUSTATE_NAME
#ifdef LIBUNWIND_WANT_PROTOTYPES
#define unwind_getreg_except_register_state unwind_getreg_ucpustate
#define unwind_setreg_except_register_state unwind_setreg_ucpustate
#endif /* LIBUNWIND_WANT_PROTOTYPES */
#elif defined(__EXCEPT_REGISTER_STATE_TYPE_IS_KCPUSTATE)
#define PUNWIND_GETREG_EXCEPT_REGISTER_STATE     PUNWIND_GETREG_KCPUSTATE
#define PUNWIND_SETREG_EXCEPT_REGISTER_STATE     PUNWIND_SETREG_KCPUSTATE
#define UNWIND_GETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_GETREG_KCPUSTATE_NAME
#define UNWIND_SETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_SETREG_KCPUSTATE_NAME
#ifdef LIBUNWIND_WANT_PROTOTYPES
#define unwind_getreg_except_register_state unwind_getreg_kcpustate
#define unwind_setreg_except_register_state unwind_setreg_kcpustate
#endif /* LIBUNWIND_WANT_PROTOTYPES */
#elif defined(__EXCEPT_REGISTER_STATE_TYPE_IS_ICPUSTATE)
#define PUNWIND_GETREG_EXCEPT_REGISTER_STATE     PUNWIND_GETREG_ICPUSTATE
#define PUNWIND_SETREG_EXCEPT_REGISTER_STATE     PUNWIND_SETREG_ICPUSTATE
#define UNWIND_GETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_GETREG_ICPUSTATE_NAME
#define UNWIND_SETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_SETREG_ICPUSTATE_NAME
#ifdef LIBUNWIND_WANT_PROTOTYPES
#define unwind_getreg_except_register_state unwind_getreg_icpustate
#define unwind_setreg_except_register_state unwind_setreg_icpustate
#endif /* LIBUNWIND_WANT_PROTOTYPES */
#elif defined(__EXCEPT_REGISTER_STATE_TYPE_IS_SCPUSTATE)
#define PUNWIND_GETREG_EXCEPT_REGISTER_STATE     PUNWIND_GETREG_SCPUSTATE
#define PUNWIND_SETREG_EXCEPT_REGISTER_STATE     PUNWIND_SETREG_SCPUSTATE
#define UNWIND_GETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_GETREG_SCPUSTATE_NAME
#define UNWIND_SETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_SETREG_SCPUSTATE_NAME
#ifdef LIBUNWIND_WANT_PROTOTYPES
#define unwind_getreg_except_register_state unwind_getreg_scpustate
#define unwind_setreg_except_register_state unwind_setreg_scpustate
#endif /* LIBUNWIND_WANT_PROTOTYPES */
#elif defined(__EXCEPT_REGISTER_STATE_TYPE_IS_FCPUSTATE)
#define PUNWIND_GETREG_EXCEPT_REGISTER_STATE     PUNWIND_GETREG_FCPUSTATE
#define PUNWIND_SETREG_EXCEPT_REGISTER_STATE     PUNWIND_SETREG_FCPUSTATE
#define UNWIND_GETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_GETREG_FCPUSTATE_NAME
#define UNWIND_SETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_SETREG_FCPUSTATE_NAME
#ifdef LIBUNWIND_WANT_PROTOTYPES
#define unwind_getreg_except_register_state unwind_getreg_fcpustate
#define unwind_setreg_except_register_state unwind_setreg_fcpustate
#endif /* LIBUNWIND_WANT_PROTOTYPES */
#endif /* ... */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBUNWIND_ARCH_REGISTER_H */
