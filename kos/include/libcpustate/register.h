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
#ifndef _LIBCPUSTATE_REGISTER_H
#define _LIBCPUSTATE_REGISTER_H 1

#include "api.h"

#include <__stdinc.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/kernel/cpu-state.h>

#include <libcpustate/asm/features.h>
#include <libcpustate/asm/register.h> /* CPU_REGISTER_NONE */
#include <libinstrlen/bits/isa.h>     /* ISA definitions */

#ifdef LIBCPUSTATE_HAVE_MCONTEXT
#include <bits/os/mcontext.h> /* struct mcontext */
#endif /* LIBCPUSTATE_HAVE_MCONTEXT */

#ifdef LIBCPUSTATE_HAVE_UCONTEXT
#include <bits/os/ucontext.h> /* struct ucontext */
#endif /* LIBCPUSTATE_HAVE_UCONTEXT */

#ifdef LIBCPUSTATE_HAVE_FPUSTATE
#include <kos/kernel/fpu-state.h> /* struct fpustate */
#endif /* LIBCPUSTATE_HAVE_FPUSTATE */



 /* Special register constant that is always invalid */
#ifndef CPU_REGISTER_NONE
#define CPU_REGISTER_NONE 0
#endif /* !CPU_REGISTER_NONE */

#ifdef __CC__
__DECL_BEGIN

#define __LIBCPU_REGISTER_GET_GENERATE_ASMNAME2(xcpustate)   register_get_##xcpustate
#define __LIBCPU_REGISTER_GET_GENERATE_ASMNAME(xcpustate)    __LIBCPU_REGISTER_GET_GENERATE_ASMNAME2(xcpustate)
#define __LIBCPU_REGISTER_SET_GENERATE_ASMNAME2(xcpustate)   register_set_##xcpustate
#define __LIBCPU_REGISTER_SET_GENERATE_ASMNAME(xcpustate)    __LIBCPU_REGISTER_SET_GENERATE_ASMNAME2(xcpustate)
#define __LIBCPU_REGISTER_SET_P_GENERATE_ASMNAME2(xcpustate) register_set_##xcpustate##_p
#define __LIBCPU_REGISTER_SET_P_GENERATE_ASMNAME(xcpustate)  __LIBCPU_REGISTER_SET_P_GENERATE_ASMNAME2(xcpustate)


/* CPU Register number (one of the constants from `<asm/register.h>') */
typedef unsigned int cpu_regno_t;
#define __SIZEOF_CPU_REGNO_T__ __SIZEOF_INT__


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
		print("#define PREGISTER_GET_", xcs.upper(), "_NAME \"register_get_\" ", xcs.upper(), "_ALIAS_STR");
		print("#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE");
		print("#define PREGISTER_SET_", xcs.upper(), "_NAME \"register_set_\" ", xcs.upper(), "_ALIAS_STR \"_p\"");
		print("#else /" "* LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE *" "/");
		print("#define PREGISTER_SET_", xcs.upper(), "_NAME \"register_set_\" ", xcs.upper(), "_ALIAS_STR");
		print("#endif /" "* !LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE *" "/");
		print("#else /" "* ", xcs.upper(), "_ALIAS *" "/");
		print("#define PREGISTER_GET_", xcs.upper(), "_NAME ", repr(f"register_get_{xcs}"));
		print("#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE");
		print("#define PREGISTER_SET_", xcs.upper(), "_NAME ", repr(f"register_set_{xcs}_p"));
		print("#else /" "* LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE *" "/");
		print("#define PREGISTER_SET_", xcs.upper(), "_NAME ", repr(f"register_set_{xcs}"));
		print("#endif /" "* !LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE *" "/");
		print("#endif /" "* !", xcs.upper(), "_ALIAS *" "/");
	} else {
		print("#define PREGISTER_GET_", xcs.upper(), "_NAME ", repr(f"register_get_{xcs}"));
		print("#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE");
		print("#define PREGISTER_SET_", xcs.upper(), "_NAME ", repr(f"register_set_{xcs}_p"));
		print("#else /" "* LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE *" "/");
		print("#define PREGISTER_SET_", xcs.upper(), "_NAME ", repr(f"register_set_{xcs}"));
		print("#endif /" "* !LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE *" "/");
	}
	if (xcs !in XCPUSTATE)
		print("struct ", xcs, ";");
	print;
	print("/" "* Get/set the value of a given register `regno'");
	print(" * NOTE: When `return > buflen', then");
	print(" *       register_get_*: The contents of `buf' are undefined.");
	print(" *       register_set_*: The register was not written.");
	print(" * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'");
	print(" * @param: regno: One of the macros from <asm/register.h>");
	print(" * @return: * :   The required buffer size, or 0 when `regno' isn't recognized. *" "/");
	print("typedef __ATTR_WUNUSED __ATTR_NONNULL_T((1)) __size_t");
	print("__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_GET_", xcs.upper(), ")(struct ", xcs, " const *__restrict __state, cpu_regno_t __regno,");
	print("                                              ", " " * #xcs,  "  void *__restrict __buf, __size_t __buflen);");
	print("#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE");
	print("typedef __ATTR_NONNULL_T((1)) __size_t");
	print("__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SET_", xcs.upper(), "_P)(struct ", xcs, " **__restrict __p_state, cpu_regno_t __regno,");
	print("                                              ", " " * #xcs,  "    void const *__restrict __buf, __size_t __buflen);");
	print("#else /" "* LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE *" "/");
	print("typedef __ATTR_NONNULL_T((1)) __size_t");
	print("__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SET_", xcs.upper(), ")(struct ", xcs, " *__restrict __state, cpu_regno_t __regno,");
	print("                                              ", " " * #xcs,  "  void const *__restrict __buf, __size_t __buflen);");
	print("#endif /" "* !LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE *" "/");
	print("#ifdef LIBCPUSTATE_WANT_PROTOTYPES");
	if (getPossibleAliasesForXCpuState(xcs)) {
		print("#ifdef ", xcs.upper(), "_ALIAS");
		print("__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get_", xcs, ",");
		print("                    (struct ", xcs, " const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),");
		print("                    __LIBCPU_REGISTER_GET_GENERATE_ASMNAME(", xcs.upper(), "_ALIAS),(__state,__regno,__buf,__buflen))");
		print("#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE");
		print("__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_", xcs, "_p,");
		print("                    (struct ", xcs, " **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),");
		print("                    __LIBCPU_REGISTER_SET_P_GENERATE_ASMNAME(", xcs.upper(), "_ALIAS),(__p_state,__regno,__buf,__buflen))");
		print("#else /" "* LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE *" "/");
		print("__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_", xcs, ",");
		print("                    (struct ", xcs, " *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),");
		print("                    __LIBCPU_REGISTER_SET_GENERATE_ASMNAME(", xcs.upper(), "_ALIAS),(__state,__regno,__buf,__buflen))");
		print("#define register_set_", xcs, "_p(p_state, regno, buf, buflen) register_set_", xcs, "(*(p_state), regno, buf, buflen)");
		print("#endif /" "* !LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE *" "/");
		print("#else /" "* ", xcs.upper(), "_ALIAS *" "/");
		print("LIBCPUSTATE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __size_t");
		print("__NOTHROW_NCX(LIBCPUSTATE_CC register_get_", xcs, ")(struct ", xcs, " const *__restrict __state, cpu_regno_t __regno,");
		print("                                          ", " " * #xcs, "  void *__restrict __buf, __size_t __buflen);");
		print("#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE");
		print("LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t");
		print("__NOTHROW_NCX(LIBCPUSTATE_CC register_set_", xcs, "_p)(struct ", xcs, " **__restrict __p_state, cpu_regno_t __regno,");
		print("                                          ", " " * #xcs, "    void const *__restrict __buf, __size_t __buflen);");
		print("#else /" "* LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE *" "/");
		print("LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t");
		print("__NOTHROW_NCX(LIBCPUSTATE_CC register_set_", xcs, ")(struct ", xcs, " *__restrict __state, cpu_regno_t __regno,");
		print("                                          ", " " * #xcs, "  void const *__restrict __buf, __size_t __buflen);");
		print("#define register_set_", xcs, "_p(p_state, regno, buf, buflen) register_set_", xcs, "(*(p_state), regno, buf, buflen)");
		print("#endif /" "* !LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE *" "/");
		print("#endif /" "* !", xcs.upper(), "_ALIAS *" "/");
	} else {
		print("LIBCPUSTATE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __size_t");
		print("__NOTHROW_NCX(LIBCPUSTATE_CC register_get_", xcs, ")(struct ", xcs, " const *__restrict __state, cpu_regno_t __regno,");
		print("                                          ", " " * #xcs, "  void *__restrict __buf, __size_t __buflen);");
		print("#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE");
		print("LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t");
		print("__NOTHROW_NCX(LIBCPUSTATE_CC register_set_", xcs, "_p)(struct ", xcs, " **__restrict __p_state, cpu_regno_t __regno,");
		print("                                          ", " " * #xcs, "    void const *__restrict __buf, __size_t __buflen);");
		print("#else /" "* LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE *" "/");
		print("LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t");
		print("__NOTHROW_NCX(LIBCPUSTATE_CC register_set_", xcs, ")(struct ", xcs, " *__restrict __state, cpu_regno_t __regno,");
		print("                                          ", " " * #xcs, "  void const *__restrict __buf, __size_t __buflen);");
		print("#define register_set_", xcs, "_p(p_state, regno, buf, buflen) register_set_", xcs, "(*(p_state), regno, buf, buflen)");
		print("#endif /" "* !LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE *" "/");
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
		print("__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get,(struct ", xcs, " const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),__LIBCPU_REGISTER_GET_GENERATE_ASMNAME(", xcs.upper(), "_ALIAS),(__state,__regno,__buf,__buflen))");
		print("#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE");
		print("__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_p,(struct ", xcs, " **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),__LIBCPU_REGISTER_SET_P_GENERATE_ASMNAME(", xcs.upper(), "_ALIAS),(__p_state,__regno,__buf,__buflen))");
		print("#else /" "* LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE *" "/");
		print("__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set,(struct ", xcs, " *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),__LIBCPU_REGISTER_SET_GENERATE_ASMNAME(", xcs.upper(), "_ALIAS),(__state,__regno,__buf,__buflen))");
		print("__FORCELOCAL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC register_set_p)(struct ", xcs, " **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen) { return register_set(*__p_state, __regno, __buf, __buflen); }");
		print("#endif /" "* !LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE *" "/");
		print("#else /" "* ", xcs.upper(), "_ALIAS *" "/");
		print("__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get,(struct ", xcs, " const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),register_get_", xcs, ",(__state,__regno,__buf,__buflen))");
		print("#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE");
		print("__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_p,(struct ", xcs, " **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_", xcs, "_p,(__p_state,__regno,__buf,__buflen))");
		print("#else /" "* LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE *" "/");
		print("__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set,(struct ", xcs, " *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_", xcs, ",(__state,__regno,__buf,__buflen))");
		print("__FORCELOCAL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC register_set_p)(struct ", xcs, " **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen) { return register_set(*__p_state, __regno, __buf, __buflen); }");
		print("#endif /" "* !LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE *" "/");
		print("#endif /" "* !", xcs.upper(), "_ALIAS *" "/");
	} else {
		print("__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get,(struct ", xcs, " const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),register_get_", xcs, ",(__state,__regno,__buf,__buflen))");
		print("#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE");
		print("__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_p,(struct ", xcs, " **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_", xcs, "_p,(__p_state,__regno,__buf,__buflen))");
		print("#else /" "* LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE *" "/");
		print("__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set,(struct ", xcs, " *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_", xcs, ",(__state,__regno,__buf,__buflen))");
		print("__FORCELOCAL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC register_set_p)(struct ", xcs, " **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen) { return register_set(*__p_state, __regno, __buf, __buflen); }");
		print("#endif /" "* !LIBCPUSTATE_HAVE_REGISTER_SET_", xcs.upper(), "_P_STATE *" "/");
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
#define PREGISTER_GET_UCPUSTATE_NAME "register_get_ucpustate"
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_UCPUSTATE_P_STATE
#define PREGISTER_SET_UCPUSTATE_NAME "register_set_ucpustate_p"
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_UCPUSTATE_P_STATE */
#define PREGISTER_SET_UCPUSTATE_NAME "register_set_ucpustate"
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_UCPUSTATE_P_STATE */

/* Get/set the value of a given register `regno'
 * NOTE: When `return > buflen', then
 *       register_get_*: The contents of `buf' are undefined.
 *       register_set_*: The register was not written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: regno: One of the macros from <asm/register.h>
 * @return: * :   The required buffer size, or 0 when `regno' isn't recognized. */
typedef __ATTR_WUNUSED __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_GET_UCPUSTATE)(struct ucpustate const *__restrict __state, cpu_regno_t __regno,
                                                         void *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_UCPUSTATE_P_STATE
typedef __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SET_UCPUSTATE_P)(struct ucpustate **__restrict __p_state, cpu_regno_t __regno,
                                                           void const *__restrict __buf, __size_t __buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_UCPUSTATE_P_STATE */
typedef __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SET_UCPUSTATE)(struct ucpustate *__restrict __state, cpu_regno_t __regno,
                                                         void const *__restrict __buf, __size_t __buflen);
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_UCPUSTATE_P_STATE */
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
LIBCPUSTATE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_get_ucpustate)(struct ucpustate const *__restrict __state, cpu_regno_t __regno,
                                                     void *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_UCPUSTATE_P_STATE
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_set_ucpustate_p)(struct ucpustate **__restrict __p_state, cpu_regno_t __regno,
                                                       void const *__restrict __buf, __size_t __buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_UCPUSTATE_P_STATE */
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_set_ucpustate)(struct ucpustate *__restrict __state, cpu_regno_t __regno,
                                                     void const *__restrict __buf, __size_t __buflen);
#define register_set_ucpustate_p(p_state, regno, buf, buflen) register_set_ucpustate(*(p_state), regno, buf, buflen)
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_UCPUSTATE_P_STATE */
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#endif /* LIBCPUSTATE_HAVE_UCPUSTATE */



/************************************************************************/
/* lcpustate                                                            */
/************************************************************************/
#ifdef LIBCPUSTATE_HAVE_LCPUSTATE
#ifdef LCPUSTATE_ALIAS
#define PREGISTER_GET_LCPUSTATE_NAME "register_get_" LCPUSTATE_ALIAS_STR
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE
#define PREGISTER_SET_LCPUSTATE_NAME "register_set_" LCPUSTATE_ALIAS_STR "_p"
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE */
#define PREGISTER_SET_LCPUSTATE_NAME "register_set_" LCPUSTATE_ALIAS_STR
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE */
#else /* LCPUSTATE_ALIAS */
#define PREGISTER_GET_LCPUSTATE_NAME "register_get_lcpustate"
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE
#define PREGISTER_SET_LCPUSTATE_NAME "register_set_lcpustate_p"
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE */
#define PREGISTER_SET_LCPUSTATE_NAME "register_set_lcpustate"
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE */
#endif /* !LCPUSTATE_ALIAS */

/* Get/set the value of a given register `regno'
 * NOTE: When `return > buflen', then
 *       register_get_*: The contents of `buf' are undefined.
 *       register_set_*: The register was not written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: regno: One of the macros from <asm/register.h>
 * @return: * :   The required buffer size, or 0 when `regno' isn't recognized. */
typedef __ATTR_WUNUSED __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_GET_LCPUSTATE)(struct lcpustate const *__restrict __state, cpu_regno_t __regno,
                                                         void *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE
typedef __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SET_LCPUSTATE_P)(struct lcpustate **__restrict __p_state, cpu_regno_t __regno,
                                                           void const *__restrict __buf, __size_t __buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE */
typedef __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SET_LCPUSTATE)(struct lcpustate *__restrict __state, cpu_regno_t __regno,
                                                         void const *__restrict __buf, __size_t __buflen);
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE */
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
#ifdef LCPUSTATE_ALIAS
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get_lcpustate,
                    (struct lcpustate const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),
                    __LIBCPU_REGISTER_GET_GENERATE_ASMNAME(LCPUSTATE_ALIAS),(__state,__regno,__buf,__buflen))
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_lcpustate_p,
                    (struct lcpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),
                    __LIBCPU_REGISTER_SET_P_GENERATE_ASMNAME(LCPUSTATE_ALIAS),(__p_state,__regno,__buf,__buflen))
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_lcpustate,
                    (struct lcpustate *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),
                    __LIBCPU_REGISTER_SET_GENERATE_ASMNAME(LCPUSTATE_ALIAS),(__state,__regno,__buf,__buflen))
#define register_set_lcpustate_p(p_state, regno, buf, buflen) register_set_lcpustate(*(p_state), regno, buf, buflen)
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE */
#else /* LCPUSTATE_ALIAS */
LIBCPUSTATE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_get_lcpustate)(struct lcpustate const *__restrict __state, cpu_regno_t __regno,
                                                     void *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_set_lcpustate_p)(struct lcpustate **__restrict __p_state, cpu_regno_t __regno,
                                                       void const *__restrict __buf, __size_t __buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE */
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_set_lcpustate)(struct lcpustate *__restrict __state, cpu_regno_t __regno,
                                                     void const *__restrict __buf, __size_t __buflen);
#define register_set_lcpustate_p(p_state, regno, buf, buflen) register_set_lcpustate(*(p_state), regno, buf, buflen)
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE */
#endif /* !LCPUSTATE_ALIAS */
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#endif /* LIBCPUSTATE_HAVE_LCPUSTATE */



/************************************************************************/
/* kcpustate                                                            */
/************************************************************************/
#ifdef LIBCPUSTATE_HAVE_KCPUSTATE
#ifdef KCPUSTATE_ALIAS
#define PREGISTER_GET_KCPUSTATE_NAME "register_get_" KCPUSTATE_ALIAS_STR
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE
#define PREGISTER_SET_KCPUSTATE_NAME "register_set_" KCPUSTATE_ALIAS_STR "_p"
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE */
#define PREGISTER_SET_KCPUSTATE_NAME "register_set_" KCPUSTATE_ALIAS_STR
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE */
#else /* KCPUSTATE_ALIAS */
#define PREGISTER_GET_KCPUSTATE_NAME "register_get_kcpustate"
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE
#define PREGISTER_SET_KCPUSTATE_NAME "register_set_kcpustate_p"
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE */
#define PREGISTER_SET_KCPUSTATE_NAME "register_set_kcpustate"
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE */
#endif /* !KCPUSTATE_ALIAS */

/* Get/set the value of a given register `regno'
 * NOTE: When `return > buflen', then
 *       register_get_*: The contents of `buf' are undefined.
 *       register_set_*: The register was not written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: regno: One of the macros from <asm/register.h>
 * @return: * :   The required buffer size, or 0 when `regno' isn't recognized. */
typedef __ATTR_WUNUSED __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_GET_KCPUSTATE)(struct kcpustate const *__restrict __state, cpu_regno_t __regno,
                                                         void *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE
typedef __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SET_KCPUSTATE_P)(struct kcpustate **__restrict __p_state, cpu_regno_t __regno,
                                                           void const *__restrict __buf, __size_t __buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE */
typedef __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SET_KCPUSTATE)(struct kcpustate *__restrict __state, cpu_regno_t __regno,
                                                         void const *__restrict __buf, __size_t __buflen);
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE */
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
#ifdef KCPUSTATE_ALIAS
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get_kcpustate,
                    (struct kcpustate const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),
                    __LIBCPU_REGISTER_GET_GENERATE_ASMNAME(KCPUSTATE_ALIAS),(__state,__regno,__buf,__buflen))
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_kcpustate_p,
                    (struct kcpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),
                    __LIBCPU_REGISTER_SET_P_GENERATE_ASMNAME(KCPUSTATE_ALIAS),(__p_state,__regno,__buf,__buflen))
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_kcpustate,
                    (struct kcpustate *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),
                    __LIBCPU_REGISTER_SET_GENERATE_ASMNAME(KCPUSTATE_ALIAS),(__state,__regno,__buf,__buflen))
#define register_set_kcpustate_p(p_state, regno, buf, buflen) register_set_kcpustate(*(p_state), regno, buf, buflen)
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE */
#else /* KCPUSTATE_ALIAS */
LIBCPUSTATE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_get_kcpustate)(struct kcpustate const *__restrict __state, cpu_regno_t __regno,
                                                     void *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_set_kcpustate_p)(struct kcpustate **__restrict __p_state, cpu_regno_t __regno,
                                                       void const *__restrict __buf, __size_t __buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE */
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_set_kcpustate)(struct kcpustate *__restrict __state, cpu_regno_t __regno,
                                                     void const *__restrict __buf, __size_t __buflen);
#define register_set_kcpustate_p(p_state, regno, buf, buflen) register_set_kcpustate(*(p_state), regno, buf, buflen)
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE */
#endif /* !KCPUSTATE_ALIAS */
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#endif /* LIBCPUSTATE_HAVE_KCPUSTATE */



/************************************************************************/
/* icpustate                                                            */
/************************************************************************/
#ifdef LIBCPUSTATE_HAVE_ICPUSTATE
#ifdef ICPUSTATE_ALIAS
#define PREGISTER_GET_ICPUSTATE_NAME "register_get_" ICPUSTATE_ALIAS_STR
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE
#define PREGISTER_SET_ICPUSTATE_NAME "register_set_" ICPUSTATE_ALIAS_STR "_p"
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE */
#define PREGISTER_SET_ICPUSTATE_NAME "register_set_" ICPUSTATE_ALIAS_STR
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE */
#else /* ICPUSTATE_ALIAS */
#define PREGISTER_GET_ICPUSTATE_NAME "register_get_icpustate"
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE
#define PREGISTER_SET_ICPUSTATE_NAME "register_set_icpustate_p"
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE */
#define PREGISTER_SET_ICPUSTATE_NAME "register_set_icpustate"
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE */
#endif /* !ICPUSTATE_ALIAS */

/* Get/set the value of a given register `regno'
 * NOTE: When `return > buflen', then
 *       register_get_*: The contents of `buf' are undefined.
 *       register_set_*: The register was not written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: regno: One of the macros from <asm/register.h>
 * @return: * :   The required buffer size, or 0 when `regno' isn't recognized. */
typedef __ATTR_WUNUSED __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_GET_ICPUSTATE)(struct icpustate const *__restrict __state, cpu_regno_t __regno,
                                                         void *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE
typedef __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SET_ICPUSTATE_P)(struct icpustate **__restrict __p_state, cpu_regno_t __regno,
                                                           void const *__restrict __buf, __size_t __buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE */
typedef __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SET_ICPUSTATE)(struct icpustate *__restrict __state, cpu_regno_t __regno,
                                                         void const *__restrict __buf, __size_t __buflen);
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE */
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
#ifdef ICPUSTATE_ALIAS
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get_icpustate,
                    (struct icpustate const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),
                    __LIBCPU_REGISTER_GET_GENERATE_ASMNAME(ICPUSTATE_ALIAS),(__state,__regno,__buf,__buflen))
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_icpustate_p,
                    (struct icpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),
                    __LIBCPU_REGISTER_SET_P_GENERATE_ASMNAME(ICPUSTATE_ALIAS),(__p_state,__regno,__buf,__buflen))
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_icpustate,
                    (struct icpustate *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),
                    __LIBCPU_REGISTER_SET_GENERATE_ASMNAME(ICPUSTATE_ALIAS),(__state,__regno,__buf,__buflen))
#define register_set_icpustate_p(p_state, regno, buf, buflen) register_set_icpustate(*(p_state), regno, buf, buflen)
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE */
#else /* ICPUSTATE_ALIAS */
LIBCPUSTATE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_get_icpustate)(struct icpustate const *__restrict __state, cpu_regno_t __regno,
                                                     void *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_set_icpustate_p)(struct icpustate **__restrict __p_state, cpu_regno_t __regno,
                                                       void const *__restrict __buf, __size_t __buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE */
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_set_icpustate)(struct icpustate *__restrict __state, cpu_regno_t __regno,
                                                     void const *__restrict __buf, __size_t __buflen);
#define register_set_icpustate_p(p_state, regno, buf, buflen) register_set_icpustate(*(p_state), regno, buf, buflen)
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE */
#endif /* !ICPUSTATE_ALIAS */
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#endif /* LIBCPUSTATE_HAVE_ICPUSTATE */



/************************************************************************/
/* scpustate                                                            */
/************************************************************************/
#ifdef LIBCPUSTATE_HAVE_SCPUSTATE
#ifdef SCPUSTATE_ALIAS
#define PREGISTER_GET_SCPUSTATE_NAME "register_get_" SCPUSTATE_ALIAS_STR
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE
#define PREGISTER_SET_SCPUSTATE_NAME "register_set_" SCPUSTATE_ALIAS_STR "_p"
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE */
#define PREGISTER_SET_SCPUSTATE_NAME "register_set_" SCPUSTATE_ALIAS_STR
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE */
#else /* SCPUSTATE_ALIAS */
#define PREGISTER_GET_SCPUSTATE_NAME "register_get_scpustate"
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE
#define PREGISTER_SET_SCPUSTATE_NAME "register_set_scpustate_p"
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE */
#define PREGISTER_SET_SCPUSTATE_NAME "register_set_scpustate"
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE */
#endif /* !SCPUSTATE_ALIAS */

/* Get/set the value of a given register `regno'
 * NOTE: When `return > buflen', then
 *       register_get_*: The contents of `buf' are undefined.
 *       register_set_*: The register was not written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: regno: One of the macros from <asm/register.h>
 * @return: * :   The required buffer size, or 0 when `regno' isn't recognized. */
typedef __ATTR_WUNUSED __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_GET_SCPUSTATE)(struct scpustate const *__restrict __state, cpu_regno_t __regno,
                                                         void *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE
typedef __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SET_SCPUSTATE_P)(struct scpustate **__restrict __p_state, cpu_regno_t __regno,
                                                           void const *__restrict __buf, __size_t __buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE */
typedef __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SET_SCPUSTATE)(struct scpustate *__restrict __state, cpu_regno_t __regno,
                                                         void const *__restrict __buf, __size_t __buflen);
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE */
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
#ifdef SCPUSTATE_ALIAS
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get_scpustate,
                    (struct scpustate const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),
                    __LIBCPU_REGISTER_GET_GENERATE_ASMNAME(SCPUSTATE_ALIAS),(__state,__regno,__buf,__buflen))
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_scpustate_p,
                    (struct scpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),
                    __LIBCPU_REGISTER_SET_P_GENERATE_ASMNAME(SCPUSTATE_ALIAS),(__p_state,__regno,__buf,__buflen))
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_scpustate,
                    (struct scpustate *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),
                    __LIBCPU_REGISTER_SET_GENERATE_ASMNAME(SCPUSTATE_ALIAS),(__state,__regno,__buf,__buflen))
#define register_set_scpustate_p(p_state, regno, buf, buflen) register_set_scpustate(*(p_state), regno, buf, buflen)
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE */
#else /* SCPUSTATE_ALIAS */
LIBCPUSTATE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_get_scpustate)(struct scpustate const *__restrict __state, cpu_regno_t __regno,
                                                     void *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_set_scpustate_p)(struct scpustate **__restrict __p_state, cpu_regno_t __regno,
                                                       void const *__restrict __buf, __size_t __buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE */
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_set_scpustate)(struct scpustate *__restrict __state, cpu_regno_t __regno,
                                                     void const *__restrict __buf, __size_t __buflen);
#define register_set_scpustate_p(p_state, regno, buf, buflen) register_set_scpustate(*(p_state), regno, buf, buflen)
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE */
#endif /* !SCPUSTATE_ALIAS */
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#endif /* LIBCPUSTATE_HAVE_SCPUSTATE */



/************************************************************************/
/* fcpustate                                                            */
/************************************************************************/
#ifdef LIBCPUSTATE_HAVE_FCPUSTATE
#ifdef FCPUSTATE_ALIAS
#define PREGISTER_GET_FCPUSTATE_NAME "register_get_" FCPUSTATE_ALIAS_STR
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE
#define PREGISTER_SET_FCPUSTATE_NAME "register_set_" FCPUSTATE_ALIAS_STR "_p"
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE */
#define PREGISTER_SET_FCPUSTATE_NAME "register_set_" FCPUSTATE_ALIAS_STR
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE */
#else /* FCPUSTATE_ALIAS */
#define PREGISTER_GET_FCPUSTATE_NAME "register_get_fcpustate"
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE
#define PREGISTER_SET_FCPUSTATE_NAME "register_set_fcpustate_p"
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE */
#define PREGISTER_SET_FCPUSTATE_NAME "register_set_fcpustate"
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE */
#endif /* !FCPUSTATE_ALIAS */

/* Get/set the value of a given register `regno'
 * NOTE: When `return > buflen', then
 *       register_get_*: The contents of `buf' are undefined.
 *       register_set_*: The register was not written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: regno: One of the macros from <asm/register.h>
 * @return: * :   The required buffer size, or 0 when `regno' isn't recognized. */
typedef __ATTR_WUNUSED __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_GET_FCPUSTATE)(struct fcpustate const *__restrict __state, cpu_regno_t __regno,
                                                         void *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE
typedef __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SET_FCPUSTATE_P)(struct fcpustate **__restrict __p_state, cpu_regno_t __regno,
                                                           void const *__restrict __buf, __size_t __buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE */
typedef __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SET_FCPUSTATE)(struct fcpustate *__restrict __state, cpu_regno_t __regno,
                                                         void const *__restrict __buf, __size_t __buflen);
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE */
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
#ifdef FCPUSTATE_ALIAS
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get_fcpustate,
                    (struct fcpustate const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),
                    __LIBCPU_REGISTER_GET_GENERATE_ASMNAME(FCPUSTATE_ALIAS),(__state,__regno,__buf,__buflen))
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_fcpustate_p,
                    (struct fcpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),
                    __LIBCPU_REGISTER_SET_P_GENERATE_ASMNAME(FCPUSTATE_ALIAS),(__p_state,__regno,__buf,__buflen))
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_fcpustate,
                    (struct fcpustate *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),
                    __LIBCPU_REGISTER_SET_GENERATE_ASMNAME(FCPUSTATE_ALIAS),(__state,__regno,__buf,__buflen))
#define register_set_fcpustate_p(p_state, regno, buf, buflen) register_set_fcpustate(*(p_state), regno, buf, buflen)
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE */
#else /* FCPUSTATE_ALIAS */
LIBCPUSTATE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_get_fcpustate)(struct fcpustate const *__restrict __state, cpu_regno_t __regno,
                                                     void *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_set_fcpustate_p)(struct fcpustate **__restrict __p_state, cpu_regno_t __regno,
                                                       void const *__restrict __buf, __size_t __buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE */
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_set_fcpustate)(struct fcpustate *__restrict __state, cpu_regno_t __regno,
                                                     void const *__restrict __buf, __size_t __buflen);
#define register_set_fcpustate_p(p_state, regno, buf, buflen) register_set_fcpustate(*(p_state), regno, buf, buflen)
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE */
#endif /* !FCPUSTATE_ALIAS */
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#endif /* LIBCPUSTATE_HAVE_FCPUSTATE */



/************************************************************************/
/* mcontext                                                             */
/************************************************************************/
#ifdef LIBCPUSTATE_HAVE_MCONTEXT
#define PREGISTER_GET_MCONTEXT_NAME "register_get_mcontext"
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_MCONTEXT_P_STATE
#define PREGISTER_SET_MCONTEXT_NAME "register_set_mcontext_p"
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_MCONTEXT_P_STATE */
#define PREGISTER_SET_MCONTEXT_NAME "register_set_mcontext"
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_MCONTEXT_P_STATE */
struct mcontext;

/* Get/set the value of a given register `regno'
 * NOTE: When `return > buflen', then
 *       register_get_*: The contents of `buf' are undefined.
 *       register_set_*: The register was not written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: regno: One of the macros from <asm/register.h>
 * @return: * :   The required buffer size, or 0 when `regno' isn't recognized. */
typedef __ATTR_WUNUSED __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_GET_MCONTEXT)(struct mcontext const *__restrict __state, cpu_regno_t __regno,
                                                        void *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_MCONTEXT_P_STATE
typedef __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SET_MCONTEXT_P)(struct mcontext **__restrict __p_state, cpu_regno_t __regno,
                                                          void const *__restrict __buf, __size_t __buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_MCONTEXT_P_STATE */
typedef __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SET_MCONTEXT)(struct mcontext *__restrict __state, cpu_regno_t __regno,
                                                        void const *__restrict __buf, __size_t __buflen);
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_MCONTEXT_P_STATE */
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
LIBCPUSTATE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_get_mcontext)(struct mcontext const *__restrict __state, cpu_regno_t __regno,
                                                    void *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_MCONTEXT_P_STATE
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_set_mcontext_p)(struct mcontext **__restrict __p_state, cpu_regno_t __regno,
                                                      void const *__restrict __buf, __size_t __buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_MCONTEXT_P_STATE */
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_set_mcontext)(struct mcontext *__restrict __state, cpu_regno_t __regno,
                                                    void const *__restrict __buf, __size_t __buflen);
#define register_set_mcontext_p(p_state, regno, buf, buflen) register_set_mcontext(*(p_state), regno, buf, buflen)
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_MCONTEXT_P_STATE */
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#endif /* LIBCPUSTATE_HAVE_MCONTEXT */



/************************************************************************/
/* ucontext                                                             */
/************************************************************************/
#ifdef LIBCPUSTATE_HAVE_UCONTEXT
#define PREGISTER_GET_UCONTEXT_NAME "register_get_ucontext"
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_UCONTEXT_P_STATE
#define PREGISTER_SET_UCONTEXT_NAME "register_set_ucontext_p"
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_UCONTEXT_P_STATE */
#define PREGISTER_SET_UCONTEXT_NAME "register_set_ucontext"
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_UCONTEXT_P_STATE */
struct ucontext;

/* Get/set the value of a given register `regno'
 * NOTE: When `return > buflen', then
 *       register_get_*: The contents of `buf' are undefined.
 *       register_set_*: The register was not written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: regno: One of the macros from <asm/register.h>
 * @return: * :   The required buffer size, or 0 when `regno' isn't recognized. */
typedef __ATTR_WUNUSED __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_GET_UCONTEXT)(struct ucontext const *__restrict __state, cpu_regno_t __regno,
                                                        void *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_UCONTEXT_P_STATE
typedef __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SET_UCONTEXT_P)(struct ucontext **__restrict __p_state, cpu_regno_t __regno,
                                                          void const *__restrict __buf, __size_t __buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_UCONTEXT_P_STATE */
typedef __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SET_UCONTEXT)(struct ucontext *__restrict __state, cpu_regno_t __regno,
                                                        void const *__restrict __buf, __size_t __buflen);
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_UCONTEXT_P_STATE */
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
LIBCPUSTATE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_get_ucontext)(struct ucontext const *__restrict __state, cpu_regno_t __regno,
                                                    void *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_UCONTEXT_P_STATE
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_set_ucontext_p)(struct ucontext **__restrict __p_state, cpu_regno_t __regno,
                                                      void const *__restrict __buf, __size_t __buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_UCONTEXT_P_STATE */
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_set_ucontext)(struct ucontext *__restrict __state, cpu_regno_t __regno,
                                                    void const *__restrict __buf, __size_t __buflen);
#define register_set_ucontext_p(p_state, regno, buf, buflen) register_set_ucontext(*(p_state), regno, buf, buflen)
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_UCONTEXT_P_STATE */
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#endif /* LIBCPUSTATE_HAVE_UCONTEXT */



/************************************************************************/
/* fpustate                                                             */
/************************************************************************/
#ifdef LIBCPUSTATE_HAVE_FPUSTATE
#define PREGISTER_GET_FPUSTATE_NAME "register_get_fpustate"
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_FPUSTATE_P_STATE
#define PREGISTER_SET_FPUSTATE_NAME "register_set_fpustate_p"
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_FPUSTATE_P_STATE */
#define PREGISTER_SET_FPUSTATE_NAME "register_set_fpustate"
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_FPUSTATE_P_STATE */
struct fpustate;

/* Get/set the value of a given register `regno'
 * NOTE: When `return > buflen', then
 *       register_get_*: The contents of `buf' are undefined.
 *       register_set_*: The register was not written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: regno: One of the macros from <asm/register.h>
 * @return: * :   The required buffer size, or 0 when `regno' isn't recognized. */
typedef __ATTR_WUNUSED __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_GET_FPUSTATE)(struct fpustate const *__restrict __state, cpu_regno_t __regno,
                                                        void *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_FPUSTATE_P_STATE
typedef __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SET_FPUSTATE_P)(struct fpustate **__restrict __p_state, cpu_regno_t __regno,
                                                          void const *__restrict __buf, __size_t __buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_FPUSTATE_P_STATE */
typedef __ATTR_NONNULL_T((1)) __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SET_FPUSTATE)(struct fpustate *__restrict __state, cpu_regno_t __regno,
                                                        void const *__restrict __buf, __size_t __buflen);
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_FPUSTATE_P_STATE */
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
LIBCPUSTATE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_get_fpustate)(struct fpustate const *__restrict __state, cpu_regno_t __regno,
                                                    void *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_FPUSTATE_P_STATE
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_set_fpustate_p)(struct fpustate **__restrict __p_state, cpu_regno_t __regno,
                                                      void const *__restrict __buf, __size_t __buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_FPUSTATE_P_STATE */
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_set_fpustate)(struct fpustate *__restrict __state, cpu_regno_t __regno,
                                                    void const *__restrict __buf, __size_t __buflen);
#define register_set_fpustate_p(p_state, regno, buf, buflen) register_set_fpustate(*(p_state), regno, buf, buflen)
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_FPUSTATE_P_STATE */
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#endif /* LIBCPUSTATE_HAVE_FPUSTATE */
#if defined(__cplusplus) && defined(LIBCPUSTATE_WANT_PROTOTYPES)
extern "C++" {
#ifdef LIBCPUSTATE_HAVE_UCPUSTATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get,(struct ucpustate const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),register_get_ucpustate,(__state,__regno,__buf,__buflen))
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_UCPUSTATE_P_STATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_p,(struct ucpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_ucpustate_p,(__p_state,__regno,__buf,__buflen))
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_UCPUSTATE_P_STATE */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set,(struct ucpustate *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_ucpustate,(__state,__regno,__buf,__buflen))
__FORCELOCAL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC register_set_p)(struct ucpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen) { return register_set(*__p_state, __regno, __buf, __buflen); }
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_UCPUSTATE_P_STATE */
#endif /* LIBCPUSTATE_HAVE_UCPUSTATE */
#ifdef LIBCPUSTATE_HAVE_LCPUSTATE
#ifdef LCPUSTATE_ALIAS
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get,(struct lcpustate const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),__LIBCPU_REGISTER_GET_GENERATE_ASMNAME(LCPUSTATE_ALIAS),(__state,__regno,__buf,__buflen))
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_p,(struct lcpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),__LIBCPU_REGISTER_SET_P_GENERATE_ASMNAME(LCPUSTATE_ALIAS),(__p_state,__regno,__buf,__buflen))
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set,(struct lcpustate *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),__LIBCPU_REGISTER_SET_GENERATE_ASMNAME(LCPUSTATE_ALIAS),(__state,__regno,__buf,__buflen))
__FORCELOCAL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC register_set_p)(struct lcpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen) { return register_set(*__p_state, __regno, __buf, __buflen); }
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE */
#else /* LCPUSTATE_ALIAS */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get,(struct lcpustate const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),register_get_lcpustate,(__state,__regno,__buf,__buflen))
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_p,(struct lcpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_lcpustate_p,(__p_state,__regno,__buf,__buflen))
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set,(struct lcpustate *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_lcpustate,(__state,__regno,__buf,__buflen))
__FORCELOCAL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC register_set_p)(struct lcpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen) { return register_set(*__p_state, __regno, __buf, __buflen); }
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE */
#endif /* !LCPUSTATE_ALIAS */
#endif /* LIBCPUSTATE_HAVE_LCPUSTATE */
#ifdef LIBCPUSTATE_HAVE_KCPUSTATE
#ifdef KCPUSTATE_ALIAS
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get,(struct kcpustate const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),__LIBCPU_REGISTER_GET_GENERATE_ASMNAME(KCPUSTATE_ALIAS),(__state,__regno,__buf,__buflen))
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_p,(struct kcpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),__LIBCPU_REGISTER_SET_P_GENERATE_ASMNAME(KCPUSTATE_ALIAS),(__p_state,__regno,__buf,__buflen))
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set,(struct kcpustate *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),__LIBCPU_REGISTER_SET_GENERATE_ASMNAME(KCPUSTATE_ALIAS),(__state,__regno,__buf,__buflen))
__FORCELOCAL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC register_set_p)(struct kcpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen) { return register_set(*__p_state, __regno, __buf, __buflen); }
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE */
#else /* KCPUSTATE_ALIAS */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get,(struct kcpustate const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),register_get_kcpustate,(__state,__regno,__buf,__buflen))
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_p,(struct kcpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_kcpustate_p,(__p_state,__regno,__buf,__buflen))
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set,(struct kcpustate *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_kcpustate,(__state,__regno,__buf,__buflen))
__FORCELOCAL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC register_set_p)(struct kcpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen) { return register_set(*__p_state, __regno, __buf, __buflen); }
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE */
#endif /* !KCPUSTATE_ALIAS */
#endif /* LIBCPUSTATE_HAVE_KCPUSTATE */
#ifdef LIBCPUSTATE_HAVE_ICPUSTATE
#ifdef ICPUSTATE_ALIAS
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get,(struct icpustate const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),__LIBCPU_REGISTER_GET_GENERATE_ASMNAME(ICPUSTATE_ALIAS),(__state,__regno,__buf,__buflen))
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_p,(struct icpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),__LIBCPU_REGISTER_SET_P_GENERATE_ASMNAME(ICPUSTATE_ALIAS),(__p_state,__regno,__buf,__buflen))
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set,(struct icpustate *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),__LIBCPU_REGISTER_SET_GENERATE_ASMNAME(ICPUSTATE_ALIAS),(__state,__regno,__buf,__buflen))
__FORCELOCAL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC register_set_p)(struct icpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen) { return register_set(*__p_state, __regno, __buf, __buflen); }
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE */
#else /* ICPUSTATE_ALIAS */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get,(struct icpustate const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),register_get_icpustate,(__state,__regno,__buf,__buflen))
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_p,(struct icpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_icpustate_p,(__p_state,__regno,__buf,__buflen))
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set,(struct icpustate *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_icpustate,(__state,__regno,__buf,__buflen))
__FORCELOCAL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC register_set_p)(struct icpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen) { return register_set(*__p_state, __regno, __buf, __buflen); }
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE */
#endif /* !ICPUSTATE_ALIAS */
#endif /* LIBCPUSTATE_HAVE_ICPUSTATE */
#ifdef LIBCPUSTATE_HAVE_SCPUSTATE
#ifdef SCPUSTATE_ALIAS
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get,(struct scpustate const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),__LIBCPU_REGISTER_GET_GENERATE_ASMNAME(SCPUSTATE_ALIAS),(__state,__regno,__buf,__buflen))
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_p,(struct scpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),__LIBCPU_REGISTER_SET_P_GENERATE_ASMNAME(SCPUSTATE_ALIAS),(__p_state,__regno,__buf,__buflen))
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set,(struct scpustate *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),__LIBCPU_REGISTER_SET_GENERATE_ASMNAME(SCPUSTATE_ALIAS),(__state,__regno,__buf,__buflen))
__FORCELOCAL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC register_set_p)(struct scpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen) { return register_set(*__p_state, __regno, __buf, __buflen); }
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE */
#else /* SCPUSTATE_ALIAS */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get,(struct scpustate const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),register_get_scpustate,(__state,__regno,__buf,__buflen))
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_p,(struct scpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_scpustate_p,(__p_state,__regno,__buf,__buflen))
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set,(struct scpustate *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_scpustate,(__state,__regno,__buf,__buflen))
__FORCELOCAL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC register_set_p)(struct scpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen) { return register_set(*__p_state, __regno, __buf, __buflen); }
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE */
#endif /* !SCPUSTATE_ALIAS */
#endif /* LIBCPUSTATE_HAVE_SCPUSTATE */
#ifdef LIBCPUSTATE_HAVE_FCPUSTATE
#ifdef FCPUSTATE_ALIAS
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get,(struct fcpustate const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),__LIBCPU_REGISTER_GET_GENERATE_ASMNAME(FCPUSTATE_ALIAS),(__state,__regno,__buf,__buflen))
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_p,(struct fcpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),__LIBCPU_REGISTER_SET_P_GENERATE_ASMNAME(FCPUSTATE_ALIAS),(__p_state,__regno,__buf,__buflen))
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set,(struct fcpustate *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),__LIBCPU_REGISTER_SET_GENERATE_ASMNAME(FCPUSTATE_ALIAS),(__state,__regno,__buf,__buflen))
__FORCELOCAL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC register_set_p)(struct fcpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen) { return register_set(*__p_state, __regno, __buf, __buflen); }
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE */
#else /* FCPUSTATE_ALIAS */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get,(struct fcpustate const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),register_get_fcpustate,(__state,__regno,__buf,__buflen))
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_p,(struct fcpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_fcpustate_p,(__p_state,__regno,__buf,__buflen))
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set,(struct fcpustate *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_fcpustate,(__state,__regno,__buf,__buflen))
__FORCELOCAL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC register_set_p)(struct fcpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen) { return register_set(*__p_state, __regno, __buf, __buflen); }
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE */
#endif /* !FCPUSTATE_ALIAS */
#endif /* LIBCPUSTATE_HAVE_FCPUSTATE */
#ifdef LIBCPUSTATE_HAVE_MCONTEXT
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get,(struct mcontext const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),register_get_mcontext,(__state,__regno,__buf,__buflen))
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_MCONTEXT_P_STATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_p,(struct mcontext **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_mcontext_p,(__p_state,__regno,__buf,__buflen))
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_MCONTEXT_P_STATE */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set,(struct mcontext *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_mcontext,(__state,__regno,__buf,__buflen))
__FORCELOCAL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC register_set_p)(struct mcontext **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen) { return register_set(*__p_state, __regno, __buf, __buflen); }
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_MCONTEXT_P_STATE */
#endif /* LIBCPUSTATE_HAVE_MCONTEXT */
#ifdef LIBCPUSTATE_HAVE_UCONTEXT
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get,(struct ucontext const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),register_get_ucontext,(__state,__regno,__buf,__buflen))
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_UCONTEXT_P_STATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_p,(struct ucontext **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_ucontext_p,(__p_state,__regno,__buf,__buflen))
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_UCONTEXT_P_STATE */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set,(struct ucontext *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_ucontext,(__state,__regno,__buf,__buflen))
__FORCELOCAL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC register_set_p)(struct ucontext **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen) { return register_set(*__p_state, __regno, __buf, __buflen); }
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_UCONTEXT_P_STATE */
#endif /* LIBCPUSTATE_HAVE_UCONTEXT */
#ifdef LIBCPUSTATE_HAVE_FPUSTATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_WUNUSED __ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_get,(struct fpustate const *__restrict __state, cpu_regno_t __regno, void *__restrict __buf, __size_t __buflen),register_get_fpustate,(__state,__regno,__buf,__buflen))
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_FPUSTATE_P_STATE
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set_p,(struct fpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_fpustate_p,(__p_state,__regno,__buf,__buflen))
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_FPUSTATE_P_STATE */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,register_set,(struct fpustate *__restrict __state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen),register_set_fpustate,(__state,__regno,__buf,__buflen))
__FORCELOCAL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC register_set_p)(struct fpustate **__restrict __p_state, cpu_regno_t __regno, void const *__restrict __buf, __size_t __buflen) { return register_set(*__p_state, __regno, __buf, __buflen); }
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_FPUSTATE_P_STATE */
#endif /* LIBCPUSTATE_HAVE_FPUSTATE */
} /* extern "C++" */
#endif /* __cplusplus && LIBCPUSTATE_WANT_PROTOTYPES */
/*[[[end]]]*/

#undef __LIBCPU_REGISTER_GET_GENERATE_ASMNAME2
#undef __LIBCPU_REGISTER_GET_GENERATE_ASMNAME
#undef __LIBCPU_REGISTER_SET_GENERATE_ASMNAME2
#undef __LIBCPU_REGISTER_SET_GENERATE_ASMNAME
#undef __LIBCPU_REGISTER_SET_P_GENERATE_ASMNAME2
#undef __LIBCPU_REGISTER_SET_P_GENERATE_ASMNAME


/* Return the size of a given CPU register (in bytes) */
typedef __ATTR_WUNUSED_T __ATTR_CONST_T __size_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_SIZEOF)(cpu_regno_t __regno);
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
LIBCPUSTATE_DECL __ATTR_WUNUSED __ATTR_CONST __size_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_sizeof)(cpu_regno_t __regno);
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */


/* CPU register flags (set of `CPU_REGNO_F_*') */
typedef __uintptr_t cpu_regno_flags_t;
#define CPU_REGNO_F_NORMAL 0x00000000 /* Normal flags */
#define CPU_REGNO_F_FPUREG 0x00000001 /* FPU register (accessed via `struct fpustate', or some other arch-specific structure) */


/* Return the flags of a given CPU register */
typedef __ATTR_WUNUSED_T __ATTR_CONST_T cpu_regno_flags_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_FLAGS)(cpu_regno_t __regno);
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
LIBCPUSTATE_DECL __ATTR_WUNUSED __ATTR_CONST cpu_regno_flags_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_flags)(cpu_regno_t __regno);
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */

/* Return an arch-specific register constant, given its name
 * @param: isa: Instruction-set-assembly to which the given name belongs
 * @return: CPU_REGISTER_NONE: No such register. */
typedef __ATTR_WUNUSED_T __ATTR_PURE_T __ATTR_NONNULL_T((2)) cpu_regno_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_BYNAME)(instrlen_isa_t __isa,
                                                  char const *__restrict __name,
                                                  __size_t __namelen);
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
LIBCPUSTATE_DECL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((2)) cpu_regno_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_byname)(instrlen_isa_t __isa,
                                              char const *__restrict __name,
                                              __size_t __namelen);
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */

/* Callback prototype for `register_listnames()'
 * @return: * : pformatprinter-compatible return value. */
typedef __ATTR_NONNULL_T((2)) __ssize_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *pregister_listnames_callback_t)(void *__cookie,
                                                                char const *__restrict __name,
                                                                __size_t __namelen);

/* Enumerate all register names that are accepted by `register_byname'
 * @return: >= 0: Sum of return values of `cb'
 * @return: <  0: First negative return value of `cb' (enumerate was aborted) */
typedef __ATTR_NONNULL_T((1)) __ssize_t
__NOTHROW_NCX_T(LIBCPUSTATE_CC *PREGISTER_LISTNAMES)(pregister_listnames_callback_t __cb,
                                                     void *__cookie);
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __ssize_t
__NOTHROW_NCX(LIBCPUSTATE_CC register_listnames)(pregister_listnames_callback_t __cb,
                                                 void *__cookie);
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBCPUSTATE_REGISTER_H */
