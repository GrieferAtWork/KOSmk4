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
#ifndef _KOS_KERNEL_CPU_STATE_HELPERS_H
#define _KOS_KERNEL_CPU_STATE_HELPERS_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <kos/kernel/bits/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

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
local STANDARD_FUNCTIONS: {string...} = {
	"getpc",
	"setpc",
	"getsp",
	"setsp",
};
local OPTIONAL_FUNCTIONS: {string...} = {
	"foreach_gpregs",
	"foreach_gpregs_elem",
	"foreach_gpregs_size",
	"getreturn32",
	"getreturn64",
	"setreturn32",
	"setreturn64",
	"current",
	"isuser",
	"iskern",
};

function getPossibleAliasesForXCpuState(name: string): {string...} {
	return XCPUSTATE[:XCPUSTATE.index(name)];
}

local isFirst = true;
for (local xcs: XCPUSTATE) {
	if (!isFirst) {
		print;
		print;
		print;
	}
	isFirst = false;

	print("/" "************************************************************************" "/");
	print("/" "* ", xcs, "                                                            *" "/");
	print("/" "************************************************************************" "/");

	// Define macros based on aliasing
	local isFirstAlias = true;
	for (local alias: getPossibleAliasesForXCpuState(xcs)) {
		if (isFirstAlias) {
			print("#ifdef ", xcs.upper(), "_IS_", alias.upper());
			isFirstAlias = false;
		} else {
			print("#elif defined(", xcs.upper(), "_IS_", alias.upper(), ")");
		}
		for (local fun: STANDARD_FUNCTIONS) {
			local xcs_fun   = f"{xcs}_{fun}";
			local alias_fun = f"{alias}_{fun}";
			print("#ifndef ", xcs_fun);
			print("#define ", xcs_fun, " ", alias_fun);
			print("#endif /" "* !", xcs_fun, " *" "/");
		}
		for (local fun: OPTIONAL_FUNCTIONS) {
			local xcs_fun   = f"{xcs}_{fun}";
			local alias_fun = f"{alias}_{fun}";
			print("#if !defined(", xcs_fun, ") && defined(", alias_fun, ")");
			print("#define ", xcs_fun, " ", alias_fun);
			print("#endif /" "* !", xcs_fun, " && ", alias_fun, " *" "/");
		}
	}
	if (!isFirstAlias)
		print("#endif /" "* ", xcs.upper(), "_IS_?CPUSTATE *" "/");

	// Supplement missing functions
	print("#ifndef ", xcs, "_getreturn");
	print("#if __SIZEOF_POINTER__ <= 4");
	print("#define ", xcs, "_getreturn ", xcs, "_getreturn32");
	print("#else /" "* __SIZEOF_POINTER__ <= 4 *" "/");
	print("#define ", xcs, "_getreturn ", xcs, "_getreturn64");
	print("#endif /" "* __SIZEOF_POINTER__ > 4 *" "/");
	print("#endif /" "* !", xcs, "_getreturn *" "/");

	print("#ifndef ", xcs, "_setreturn");
	print("#if __SIZEOF_POINTER__ <= 4");
	print("#define ", xcs, "_setreturn ", xcs, "_setreturn32");
	print("#else /" "* __SIZEOF_POINTER__ <= 4 *" "/");
	print("#define ", xcs, "_setreturn ", xcs, "_setreturn64");
	print("#endif /" "* __SIZEOF_POINTER__ > 4 *" "/");
	print("#endif /" "* !", xcs, "_setreturn *" "/");

	print("#ifndef ", xcs, "_getreturnbool");
	print("#define ", xcs, "_getreturnbool(x) (", xcs, "_getreturn(x) != 0)");
	print("#endif /" "* !", xcs, "_getreturnbool *" "/");

	print("#ifndef ", xcs, "_setreturnbool");
	print("#define ", xcs, "_setreturnbool(x, v) ", xcs, "_setreturn(x, (v) ? 1 : 0)");
	print("#endif /" "* !", xcs, "_setreturnbool *" "/");

	print("#if !defined(", xcs, "_foreach_gpregs) && defined(", xcs, "_foreach_gpregs_elem) && defined(", xcs, "_foreach_gpregs_size)");
	print("#define ", xcs, "_foreach_gpregs(self, cb)                                         \\");
	print("	do {                                                                           \\");
	print("		unsigned int __", xcs, "_foreach_gpregs_i;                                 \\");
	print("		for (__", xcs, "_foreach_gpregs_i = 0;                                     \\");
	print("		     __", xcs, "_foreach_gpregs_i < ", xcs, "_foreach_gpregs_size(self);   \\");
	print("		     ++__", xcs, "_foreach_gpregs_i) {                                     \\");
	print("			cb(", xcs, "_foreach_gpregs_elem(self)[__", xcs, "_foreach_gpregs_i]); \\");
	print("		}                                                                          \\");
	print("	}	__WHILE0");
	print("#endif /" "* !", xcs, "_foreach_gpregs && ", xcs, "_foreach_gpregs_elem && ", xcs, "_foreach_gpregs_size *" "/");
}

// Print conversion aliases
for (local xcs: XCPUSTATE) {
	local isFirstAlias = true;
	for (local alias: getPossibleAliasesForXCpuState(xcs)) {
		if (isFirstAlias) {
			print("#ifdef ", xcs.upper(), "_IS_", alias.upper());
			isFirstAlias = false;
		} else {
			print("#elif defined(", xcs.upper(), "_IS_", alias.upper(), ")");
		}
		for (local xcs_inner: XCPUSTATE) {
			if (xcs != xcs_inner && xcs != alias && alias != xcs_inner) {
				local lhs = alias;
				local rhs = xcs_inner;
				if (XCPUSTATE.index(lhs) < XCPUSTATE.index(rhs)) {
					lhs = xcs_inner;
					rhs = alias;
				}
				print("#ifndef ", lhs.upper(), "_IS_TRANSITIVE_", rhs.upper());
				print("#define ", xcs, "_to_", xcs_inner, " ", alias, "_to_", xcs_inner);
				print("#define ", xcs_inner, "_to_", xcs, " ", xcs_inner, "_to_", alias);
				print("#endif /" "* !", lhs.upper(), "_IS_TRANSITIVE_", rhs.upper(), " *" "/");
			}
		}
	}
	if (!isFirstAlias)
		print("#endif /" "* ", xcs.upper(), "_IS_?CPUSTATE *" "/");
}


]]]*/
/************************************************************************/
/* ucpustate                                                            */
/************************************************************************/
#ifndef ucpustate_getreturn
#if __SIZEOF_POINTER__ <= 4
#define ucpustate_getreturn ucpustate_getreturn32
#else /* __SIZEOF_POINTER__ <= 4 */
#define ucpustate_getreturn ucpustate_getreturn64
#endif /* __SIZEOF_POINTER__ > 4 */
#endif /* !ucpustate_getreturn */
#ifndef ucpustate_setreturn
#if __SIZEOF_POINTER__ <= 4
#define ucpustate_setreturn ucpustate_setreturn32
#else /* __SIZEOF_POINTER__ <= 4 */
#define ucpustate_setreturn ucpustate_setreturn64
#endif /* __SIZEOF_POINTER__ > 4 */
#endif /* !ucpustate_setreturn */
#ifndef ucpustate_getreturnbool
#define ucpustate_getreturnbool(x) (ucpustate_getreturn(x) != 0)
#endif /* !ucpustate_getreturnbool */
#ifndef ucpustate_setreturnbool
#define ucpustate_setreturnbool(x, v) ucpustate_setreturn(x, (v) ? 1 : 0)
#endif /* !ucpustate_setreturnbool */
#if !defined(ucpustate_foreach_gpregs) && defined(ucpustate_foreach_gpregs_elem) && defined(ucpustate_foreach_gpregs_size)
#define ucpustate_foreach_gpregs(self, cb)                                         \
	do {                                                                           \
		unsigned int __ucpustate_foreach_gpregs_i;                                 \
		for (__ucpustate_foreach_gpregs_i = 0;                                     \
		     __ucpustate_foreach_gpregs_i < ucpustate_foreach_gpregs_size(self);   \
		     ++__ucpustate_foreach_gpregs_i) {                                     \
			cb(ucpustate_foreach_gpregs_elem(self)[__ucpustate_foreach_gpregs_i]); \
		}                                                                          \
	}	__WHILE0
#endif /* !ucpustate_foreach_gpregs && ucpustate_foreach_gpregs_elem && ucpustate_foreach_gpregs_size */



/************************************************************************/
/* lcpustate                                                            */
/************************************************************************/
#ifdef LCPUSTATE_IS_UCPUSTATE
#ifndef lcpustate_getpc
#define lcpustate_getpc ucpustate_getpc
#endif /* !lcpustate_getpc */
#ifndef lcpustate_setpc
#define lcpustate_setpc ucpustate_setpc
#endif /* !lcpustate_setpc */
#ifndef lcpustate_getsp
#define lcpustate_getsp ucpustate_getsp
#endif /* !lcpustate_getsp */
#ifndef lcpustate_setsp
#define lcpustate_setsp ucpustate_setsp
#endif /* !lcpustate_setsp */
#if !defined(lcpustate_foreach_gpregs) && defined(ucpustate_foreach_gpregs)
#define lcpustate_foreach_gpregs ucpustate_foreach_gpregs
#endif /* !lcpustate_foreach_gpregs && ucpustate_foreach_gpregs */
#if !defined(lcpustate_foreach_gpregs_elem) && defined(ucpustate_foreach_gpregs_elem)
#define lcpustate_foreach_gpregs_elem ucpustate_foreach_gpregs_elem
#endif /* !lcpustate_foreach_gpregs_elem && ucpustate_foreach_gpregs_elem */
#if !defined(lcpustate_foreach_gpregs_size) && defined(ucpustate_foreach_gpregs_size)
#define lcpustate_foreach_gpregs_size ucpustate_foreach_gpregs_size
#endif /* !lcpustate_foreach_gpregs_size && ucpustate_foreach_gpregs_size */
#if !defined(lcpustate_getreturn32) && defined(ucpustate_getreturn32)
#define lcpustate_getreturn32 ucpustate_getreturn32
#endif /* !lcpustate_getreturn32 && ucpustate_getreturn32 */
#if !defined(lcpustate_getreturn64) && defined(ucpustate_getreturn64)
#define lcpustate_getreturn64 ucpustate_getreturn64
#endif /* !lcpustate_getreturn64 && ucpustate_getreturn64 */
#if !defined(lcpustate_setreturn32) && defined(ucpustate_setreturn32)
#define lcpustate_setreturn32 ucpustate_setreturn32
#endif /* !lcpustate_setreturn32 && ucpustate_setreturn32 */
#if !defined(lcpustate_setreturn64) && defined(ucpustate_setreturn64)
#define lcpustate_setreturn64 ucpustate_setreturn64
#endif /* !lcpustate_setreturn64 && ucpustate_setreturn64 */
#if !defined(lcpustate_current) && defined(ucpustate_current)
#define lcpustate_current ucpustate_current
#endif /* !lcpustate_current && ucpustate_current */
#if !defined(lcpustate_isuser) && defined(ucpustate_isuser)
#define lcpustate_isuser ucpustate_isuser
#endif /* !lcpustate_isuser && ucpustate_isuser */
#if !defined(lcpustate_iskern) && defined(ucpustate_iskern)
#define lcpustate_iskern ucpustate_iskern
#endif /* !lcpustate_iskern && ucpustate_iskern */
#endif /* LCPUSTATE_IS_?CPUSTATE */
#ifndef lcpustate_getreturn
#if __SIZEOF_POINTER__ <= 4
#define lcpustate_getreturn lcpustate_getreturn32
#else /* __SIZEOF_POINTER__ <= 4 */
#define lcpustate_getreturn lcpustate_getreturn64
#endif /* __SIZEOF_POINTER__ > 4 */
#endif /* !lcpustate_getreturn */
#ifndef lcpustate_setreturn
#if __SIZEOF_POINTER__ <= 4
#define lcpustate_setreturn lcpustate_setreturn32
#else /* __SIZEOF_POINTER__ <= 4 */
#define lcpustate_setreturn lcpustate_setreturn64
#endif /* __SIZEOF_POINTER__ > 4 */
#endif /* !lcpustate_setreturn */
#ifndef lcpustate_getreturnbool
#define lcpustate_getreturnbool(x) (lcpustate_getreturn(x) != 0)
#endif /* !lcpustate_getreturnbool */
#ifndef lcpustate_setreturnbool
#define lcpustate_setreturnbool(x, v) lcpustate_setreturn(x, (v) ? 1 : 0)
#endif /* !lcpustate_setreturnbool */
#if !defined(lcpustate_foreach_gpregs) && defined(lcpustate_foreach_gpregs_elem) && defined(lcpustate_foreach_gpregs_size)
#define lcpustate_foreach_gpregs(self, cb)                                         \
	do {                                                                           \
		unsigned int __lcpustate_foreach_gpregs_i;                                 \
		for (__lcpustate_foreach_gpregs_i = 0;                                     \
		     __lcpustate_foreach_gpregs_i < lcpustate_foreach_gpregs_size(self);   \
		     ++__lcpustate_foreach_gpregs_i) {                                     \
			cb(lcpustate_foreach_gpregs_elem(self)[__lcpustate_foreach_gpregs_i]); \
		}                                                                          \
	}	__WHILE0
#endif /* !lcpustate_foreach_gpregs && lcpustate_foreach_gpregs_elem && lcpustate_foreach_gpregs_size */



/************************************************************************/
/* kcpustate                                                            */
/************************************************************************/
#ifdef KCPUSTATE_IS_UCPUSTATE
#ifndef kcpustate_getpc
#define kcpustate_getpc ucpustate_getpc
#endif /* !kcpustate_getpc */
#ifndef kcpustate_setpc
#define kcpustate_setpc ucpustate_setpc
#endif /* !kcpustate_setpc */
#ifndef kcpustate_getsp
#define kcpustate_getsp ucpustate_getsp
#endif /* !kcpustate_getsp */
#ifndef kcpustate_setsp
#define kcpustate_setsp ucpustate_setsp
#endif /* !kcpustate_setsp */
#if !defined(kcpustate_foreach_gpregs) && defined(ucpustate_foreach_gpregs)
#define kcpustate_foreach_gpregs ucpustate_foreach_gpregs
#endif /* !kcpustate_foreach_gpregs && ucpustate_foreach_gpregs */
#if !defined(kcpustate_foreach_gpregs_elem) && defined(ucpustate_foreach_gpregs_elem)
#define kcpustate_foreach_gpregs_elem ucpustate_foreach_gpregs_elem
#endif /* !kcpustate_foreach_gpregs_elem && ucpustate_foreach_gpregs_elem */
#if !defined(kcpustate_foreach_gpregs_size) && defined(ucpustate_foreach_gpregs_size)
#define kcpustate_foreach_gpregs_size ucpustate_foreach_gpregs_size
#endif /* !kcpustate_foreach_gpregs_size && ucpustate_foreach_gpregs_size */
#if !defined(kcpustate_getreturn32) && defined(ucpustate_getreturn32)
#define kcpustate_getreturn32 ucpustate_getreturn32
#endif /* !kcpustate_getreturn32 && ucpustate_getreturn32 */
#if !defined(kcpustate_getreturn64) && defined(ucpustate_getreturn64)
#define kcpustate_getreturn64 ucpustate_getreturn64
#endif /* !kcpustate_getreturn64 && ucpustate_getreturn64 */
#if !defined(kcpustate_setreturn32) && defined(ucpustate_setreturn32)
#define kcpustate_setreturn32 ucpustate_setreturn32
#endif /* !kcpustate_setreturn32 && ucpustate_setreturn32 */
#if !defined(kcpustate_setreturn64) && defined(ucpustate_setreturn64)
#define kcpustate_setreturn64 ucpustate_setreturn64
#endif /* !kcpustate_setreturn64 && ucpustate_setreturn64 */
#if !defined(kcpustate_current) && defined(ucpustate_current)
#define kcpustate_current ucpustate_current
#endif /* !kcpustate_current && ucpustate_current */
#if !defined(kcpustate_isuser) && defined(ucpustate_isuser)
#define kcpustate_isuser ucpustate_isuser
#endif /* !kcpustate_isuser && ucpustate_isuser */
#if !defined(kcpustate_iskern) && defined(ucpustate_iskern)
#define kcpustate_iskern ucpustate_iskern
#endif /* !kcpustate_iskern && ucpustate_iskern */
#elif defined(KCPUSTATE_IS_LCPUSTATE)
#ifndef kcpustate_getpc
#define kcpustate_getpc lcpustate_getpc
#endif /* !kcpustate_getpc */
#ifndef kcpustate_setpc
#define kcpustate_setpc lcpustate_setpc
#endif /* !kcpustate_setpc */
#ifndef kcpustate_getsp
#define kcpustate_getsp lcpustate_getsp
#endif /* !kcpustate_getsp */
#ifndef kcpustate_setsp
#define kcpustate_setsp lcpustate_setsp
#endif /* !kcpustate_setsp */
#if !defined(kcpustate_foreach_gpregs) && defined(lcpustate_foreach_gpregs)
#define kcpustate_foreach_gpregs lcpustate_foreach_gpregs
#endif /* !kcpustate_foreach_gpregs && lcpustate_foreach_gpregs */
#if !defined(kcpustate_foreach_gpregs_elem) && defined(lcpustate_foreach_gpregs_elem)
#define kcpustate_foreach_gpregs_elem lcpustate_foreach_gpregs_elem
#endif /* !kcpustate_foreach_gpregs_elem && lcpustate_foreach_gpregs_elem */
#if !defined(kcpustate_foreach_gpregs_size) && defined(lcpustate_foreach_gpregs_size)
#define kcpustate_foreach_gpregs_size lcpustate_foreach_gpregs_size
#endif /* !kcpustate_foreach_gpregs_size && lcpustate_foreach_gpregs_size */
#if !defined(kcpustate_getreturn32) && defined(lcpustate_getreturn32)
#define kcpustate_getreturn32 lcpustate_getreturn32
#endif /* !kcpustate_getreturn32 && lcpustate_getreturn32 */
#if !defined(kcpustate_getreturn64) && defined(lcpustate_getreturn64)
#define kcpustate_getreturn64 lcpustate_getreturn64
#endif /* !kcpustate_getreturn64 && lcpustate_getreturn64 */
#if !defined(kcpustate_setreturn32) && defined(lcpustate_setreturn32)
#define kcpustate_setreturn32 lcpustate_setreturn32
#endif /* !kcpustate_setreturn32 && lcpustate_setreturn32 */
#if !defined(kcpustate_setreturn64) && defined(lcpustate_setreturn64)
#define kcpustate_setreturn64 lcpustate_setreturn64
#endif /* !kcpustate_setreturn64 && lcpustate_setreturn64 */
#if !defined(kcpustate_current) && defined(lcpustate_current)
#define kcpustate_current lcpustate_current
#endif /* !kcpustate_current && lcpustate_current */
#if !defined(kcpustate_isuser) && defined(lcpustate_isuser)
#define kcpustate_isuser lcpustate_isuser
#endif /* !kcpustate_isuser && lcpustate_isuser */
#if !defined(kcpustate_iskern) && defined(lcpustate_iskern)
#define kcpustate_iskern lcpustate_iskern
#endif /* !kcpustate_iskern && lcpustate_iskern */
#endif /* KCPUSTATE_IS_?CPUSTATE */
#ifndef kcpustate_getreturn
#if __SIZEOF_POINTER__ <= 4
#define kcpustate_getreturn kcpustate_getreturn32
#else /* __SIZEOF_POINTER__ <= 4 */
#define kcpustate_getreturn kcpustate_getreturn64
#endif /* __SIZEOF_POINTER__ > 4 */
#endif /* !kcpustate_getreturn */
#ifndef kcpustate_setreturn
#if __SIZEOF_POINTER__ <= 4
#define kcpustate_setreturn kcpustate_setreturn32
#else /* __SIZEOF_POINTER__ <= 4 */
#define kcpustate_setreturn kcpustate_setreturn64
#endif /* __SIZEOF_POINTER__ > 4 */
#endif /* !kcpustate_setreturn */
#ifndef kcpustate_getreturnbool
#define kcpustate_getreturnbool(x) (kcpustate_getreturn(x) != 0)
#endif /* !kcpustate_getreturnbool */
#ifndef kcpustate_setreturnbool
#define kcpustate_setreturnbool(x, v) kcpustate_setreturn(x, (v) ? 1 : 0)
#endif /* !kcpustate_setreturnbool */
#if !defined(kcpustate_foreach_gpregs) && defined(kcpustate_foreach_gpregs_elem) && defined(kcpustate_foreach_gpregs_size)
#define kcpustate_foreach_gpregs(self, cb)                                         \
	do {                                                                           \
		unsigned int __kcpustate_foreach_gpregs_i;                                 \
		for (__kcpustate_foreach_gpregs_i = 0;                                     \
		     __kcpustate_foreach_gpregs_i < kcpustate_foreach_gpregs_size(self);   \
		     ++__kcpustate_foreach_gpregs_i) {                                     \
			cb(kcpustate_foreach_gpregs_elem(self)[__kcpustate_foreach_gpregs_i]); \
		}                                                                          \
	}	__WHILE0
#endif /* !kcpustate_foreach_gpregs && kcpustate_foreach_gpregs_elem && kcpustate_foreach_gpregs_size */



/************************************************************************/
/* icpustate                                                            */
/************************************************************************/
#ifdef ICPUSTATE_IS_UCPUSTATE
#ifndef icpustate_getpc
#define icpustate_getpc ucpustate_getpc
#endif /* !icpustate_getpc */
#ifndef icpustate_setpc
#define icpustate_setpc ucpustate_setpc
#endif /* !icpustate_setpc */
#ifndef icpustate_getsp
#define icpustate_getsp ucpustate_getsp
#endif /* !icpustate_getsp */
#ifndef icpustate_setsp
#define icpustate_setsp ucpustate_setsp
#endif /* !icpustate_setsp */
#if !defined(icpustate_foreach_gpregs) && defined(ucpustate_foreach_gpregs)
#define icpustate_foreach_gpregs ucpustate_foreach_gpregs
#endif /* !icpustate_foreach_gpregs && ucpustate_foreach_gpregs */
#if !defined(icpustate_foreach_gpregs_elem) && defined(ucpustate_foreach_gpregs_elem)
#define icpustate_foreach_gpregs_elem ucpustate_foreach_gpregs_elem
#endif /* !icpustate_foreach_gpregs_elem && ucpustate_foreach_gpregs_elem */
#if !defined(icpustate_foreach_gpregs_size) && defined(ucpustate_foreach_gpregs_size)
#define icpustate_foreach_gpregs_size ucpustate_foreach_gpregs_size
#endif /* !icpustate_foreach_gpregs_size && ucpustate_foreach_gpregs_size */
#if !defined(icpustate_getreturn32) && defined(ucpustate_getreturn32)
#define icpustate_getreturn32 ucpustate_getreturn32
#endif /* !icpustate_getreturn32 && ucpustate_getreturn32 */
#if !defined(icpustate_getreturn64) && defined(ucpustate_getreturn64)
#define icpustate_getreturn64 ucpustate_getreturn64
#endif /* !icpustate_getreturn64 && ucpustate_getreturn64 */
#if !defined(icpustate_setreturn32) && defined(ucpustate_setreturn32)
#define icpustate_setreturn32 ucpustate_setreturn32
#endif /* !icpustate_setreturn32 && ucpustate_setreturn32 */
#if !defined(icpustate_setreturn64) && defined(ucpustate_setreturn64)
#define icpustate_setreturn64 ucpustate_setreturn64
#endif /* !icpustate_setreturn64 && ucpustate_setreturn64 */
#if !defined(icpustate_current) && defined(ucpustate_current)
#define icpustate_current ucpustate_current
#endif /* !icpustate_current && ucpustate_current */
#if !defined(icpustate_isuser) && defined(ucpustate_isuser)
#define icpustate_isuser ucpustate_isuser
#endif /* !icpustate_isuser && ucpustate_isuser */
#if !defined(icpustate_iskern) && defined(ucpustate_iskern)
#define icpustate_iskern ucpustate_iskern
#endif /* !icpustate_iskern && ucpustate_iskern */
#elif defined(ICPUSTATE_IS_LCPUSTATE)
#ifndef icpustate_getpc
#define icpustate_getpc lcpustate_getpc
#endif /* !icpustate_getpc */
#ifndef icpustate_setpc
#define icpustate_setpc lcpustate_setpc
#endif /* !icpustate_setpc */
#ifndef icpustate_getsp
#define icpustate_getsp lcpustate_getsp
#endif /* !icpustate_getsp */
#ifndef icpustate_setsp
#define icpustate_setsp lcpustate_setsp
#endif /* !icpustate_setsp */
#if !defined(icpustate_foreach_gpregs) && defined(lcpustate_foreach_gpregs)
#define icpustate_foreach_gpregs lcpustate_foreach_gpregs
#endif /* !icpustate_foreach_gpregs && lcpustate_foreach_gpregs */
#if !defined(icpustate_foreach_gpregs_elem) && defined(lcpustate_foreach_gpregs_elem)
#define icpustate_foreach_gpregs_elem lcpustate_foreach_gpregs_elem
#endif /* !icpustate_foreach_gpregs_elem && lcpustate_foreach_gpregs_elem */
#if !defined(icpustate_foreach_gpregs_size) && defined(lcpustate_foreach_gpregs_size)
#define icpustate_foreach_gpregs_size lcpustate_foreach_gpregs_size
#endif /* !icpustate_foreach_gpregs_size && lcpustate_foreach_gpregs_size */
#if !defined(icpustate_getreturn32) && defined(lcpustate_getreturn32)
#define icpustate_getreturn32 lcpustate_getreturn32
#endif /* !icpustate_getreturn32 && lcpustate_getreturn32 */
#if !defined(icpustate_getreturn64) && defined(lcpustate_getreturn64)
#define icpustate_getreturn64 lcpustate_getreturn64
#endif /* !icpustate_getreturn64 && lcpustate_getreturn64 */
#if !defined(icpustate_setreturn32) && defined(lcpustate_setreturn32)
#define icpustate_setreturn32 lcpustate_setreturn32
#endif /* !icpustate_setreturn32 && lcpustate_setreturn32 */
#if !defined(icpustate_setreturn64) && defined(lcpustate_setreturn64)
#define icpustate_setreturn64 lcpustate_setreturn64
#endif /* !icpustate_setreturn64 && lcpustate_setreturn64 */
#if !defined(icpustate_current) && defined(lcpustate_current)
#define icpustate_current lcpustate_current
#endif /* !icpustate_current && lcpustate_current */
#if !defined(icpustate_isuser) && defined(lcpustate_isuser)
#define icpustate_isuser lcpustate_isuser
#endif /* !icpustate_isuser && lcpustate_isuser */
#if !defined(icpustate_iskern) && defined(lcpustate_iskern)
#define icpustate_iskern lcpustate_iskern
#endif /* !icpustate_iskern && lcpustate_iskern */
#elif defined(ICPUSTATE_IS_KCPUSTATE)
#ifndef icpustate_getpc
#define icpustate_getpc kcpustate_getpc
#endif /* !icpustate_getpc */
#ifndef icpustate_setpc
#define icpustate_setpc kcpustate_setpc
#endif /* !icpustate_setpc */
#ifndef icpustate_getsp
#define icpustate_getsp kcpustate_getsp
#endif /* !icpustate_getsp */
#ifndef icpustate_setsp
#define icpustate_setsp kcpustate_setsp
#endif /* !icpustate_setsp */
#if !defined(icpustate_foreach_gpregs) && defined(kcpustate_foreach_gpregs)
#define icpustate_foreach_gpregs kcpustate_foreach_gpregs
#endif /* !icpustate_foreach_gpregs && kcpustate_foreach_gpregs */
#if !defined(icpustate_foreach_gpregs_elem) && defined(kcpustate_foreach_gpregs_elem)
#define icpustate_foreach_gpregs_elem kcpustate_foreach_gpregs_elem
#endif /* !icpustate_foreach_gpregs_elem && kcpustate_foreach_gpregs_elem */
#if !defined(icpustate_foreach_gpregs_size) && defined(kcpustate_foreach_gpregs_size)
#define icpustate_foreach_gpregs_size kcpustate_foreach_gpregs_size
#endif /* !icpustate_foreach_gpregs_size && kcpustate_foreach_gpregs_size */
#if !defined(icpustate_getreturn32) && defined(kcpustate_getreturn32)
#define icpustate_getreturn32 kcpustate_getreturn32
#endif /* !icpustate_getreturn32 && kcpustate_getreturn32 */
#if !defined(icpustate_getreturn64) && defined(kcpustate_getreturn64)
#define icpustate_getreturn64 kcpustate_getreturn64
#endif /* !icpustate_getreturn64 && kcpustate_getreturn64 */
#if !defined(icpustate_setreturn32) && defined(kcpustate_setreturn32)
#define icpustate_setreturn32 kcpustate_setreturn32
#endif /* !icpustate_setreturn32 && kcpustate_setreturn32 */
#if !defined(icpustate_setreturn64) && defined(kcpustate_setreturn64)
#define icpustate_setreturn64 kcpustate_setreturn64
#endif /* !icpustate_setreturn64 && kcpustate_setreturn64 */
#if !defined(icpustate_current) && defined(kcpustate_current)
#define icpustate_current kcpustate_current
#endif /* !icpustate_current && kcpustate_current */
#if !defined(icpustate_isuser) && defined(kcpustate_isuser)
#define icpustate_isuser kcpustate_isuser
#endif /* !icpustate_isuser && kcpustate_isuser */
#if !defined(icpustate_iskern) && defined(kcpustate_iskern)
#define icpustate_iskern kcpustate_iskern
#endif /* !icpustate_iskern && kcpustate_iskern */
#endif /* ICPUSTATE_IS_?CPUSTATE */
#ifndef icpustate_getreturn
#if __SIZEOF_POINTER__ <= 4
#define icpustate_getreturn icpustate_getreturn32
#else /* __SIZEOF_POINTER__ <= 4 */
#define icpustate_getreturn icpustate_getreturn64
#endif /* __SIZEOF_POINTER__ > 4 */
#endif /* !icpustate_getreturn */
#ifndef icpustate_setreturn
#if __SIZEOF_POINTER__ <= 4
#define icpustate_setreturn icpustate_setreturn32
#else /* __SIZEOF_POINTER__ <= 4 */
#define icpustate_setreturn icpustate_setreturn64
#endif /* __SIZEOF_POINTER__ > 4 */
#endif /* !icpustate_setreturn */
#ifndef icpustate_getreturnbool
#define icpustate_getreturnbool(x) (icpustate_getreturn(x) != 0)
#endif /* !icpustate_getreturnbool */
#ifndef icpustate_setreturnbool
#define icpustate_setreturnbool(x, v) icpustate_setreturn(x, (v) ? 1 : 0)
#endif /* !icpustate_setreturnbool */
#if !defined(icpustate_foreach_gpregs) && defined(icpustate_foreach_gpregs_elem) && defined(icpustate_foreach_gpregs_size)
#define icpustate_foreach_gpregs(self, cb)                                         \
	do {                                                                           \
		unsigned int __icpustate_foreach_gpregs_i;                                 \
		for (__icpustate_foreach_gpregs_i = 0;                                     \
		     __icpustate_foreach_gpregs_i < icpustate_foreach_gpregs_size(self);   \
		     ++__icpustate_foreach_gpregs_i) {                                     \
			cb(icpustate_foreach_gpregs_elem(self)[__icpustate_foreach_gpregs_i]); \
		}                                                                          \
	}	__WHILE0
#endif /* !icpustate_foreach_gpregs && icpustate_foreach_gpregs_elem && icpustate_foreach_gpregs_size */



/************************************************************************/
/* scpustate                                                            */
/************************************************************************/
#ifdef SCPUSTATE_IS_UCPUSTATE
#ifndef scpustate_getpc
#define scpustate_getpc ucpustate_getpc
#endif /* !scpustate_getpc */
#ifndef scpustate_setpc
#define scpustate_setpc ucpustate_setpc
#endif /* !scpustate_setpc */
#ifndef scpustate_getsp
#define scpustate_getsp ucpustate_getsp
#endif /* !scpustate_getsp */
#ifndef scpustate_setsp
#define scpustate_setsp ucpustate_setsp
#endif /* !scpustate_setsp */
#if !defined(scpustate_foreach_gpregs) && defined(ucpustate_foreach_gpregs)
#define scpustate_foreach_gpregs ucpustate_foreach_gpregs
#endif /* !scpustate_foreach_gpregs && ucpustate_foreach_gpregs */
#if !defined(scpustate_foreach_gpregs_elem) && defined(ucpustate_foreach_gpregs_elem)
#define scpustate_foreach_gpregs_elem ucpustate_foreach_gpregs_elem
#endif /* !scpustate_foreach_gpregs_elem && ucpustate_foreach_gpregs_elem */
#if !defined(scpustate_foreach_gpregs_size) && defined(ucpustate_foreach_gpregs_size)
#define scpustate_foreach_gpregs_size ucpustate_foreach_gpregs_size
#endif /* !scpustate_foreach_gpregs_size && ucpustate_foreach_gpregs_size */
#if !defined(scpustate_getreturn32) && defined(ucpustate_getreturn32)
#define scpustate_getreturn32 ucpustate_getreturn32
#endif /* !scpustate_getreturn32 && ucpustate_getreturn32 */
#if !defined(scpustate_getreturn64) && defined(ucpustate_getreturn64)
#define scpustate_getreturn64 ucpustate_getreturn64
#endif /* !scpustate_getreturn64 && ucpustate_getreturn64 */
#if !defined(scpustate_setreturn32) && defined(ucpustate_setreturn32)
#define scpustate_setreturn32 ucpustate_setreturn32
#endif /* !scpustate_setreturn32 && ucpustate_setreturn32 */
#if !defined(scpustate_setreturn64) && defined(ucpustate_setreturn64)
#define scpustate_setreturn64 ucpustate_setreturn64
#endif /* !scpustate_setreturn64 && ucpustate_setreturn64 */
#if !defined(scpustate_current) && defined(ucpustate_current)
#define scpustate_current ucpustate_current
#endif /* !scpustate_current && ucpustate_current */
#if !defined(scpustate_isuser) && defined(ucpustate_isuser)
#define scpustate_isuser ucpustate_isuser
#endif /* !scpustate_isuser && ucpustate_isuser */
#if !defined(scpustate_iskern) && defined(ucpustate_iskern)
#define scpustate_iskern ucpustate_iskern
#endif /* !scpustate_iskern && ucpustate_iskern */
#elif defined(SCPUSTATE_IS_LCPUSTATE)
#ifndef scpustate_getpc
#define scpustate_getpc lcpustate_getpc
#endif /* !scpustate_getpc */
#ifndef scpustate_setpc
#define scpustate_setpc lcpustate_setpc
#endif /* !scpustate_setpc */
#ifndef scpustate_getsp
#define scpustate_getsp lcpustate_getsp
#endif /* !scpustate_getsp */
#ifndef scpustate_setsp
#define scpustate_setsp lcpustate_setsp
#endif /* !scpustate_setsp */
#if !defined(scpustate_foreach_gpregs) && defined(lcpustate_foreach_gpregs)
#define scpustate_foreach_gpregs lcpustate_foreach_gpregs
#endif /* !scpustate_foreach_gpregs && lcpustate_foreach_gpregs */
#if !defined(scpustate_foreach_gpregs_elem) && defined(lcpustate_foreach_gpregs_elem)
#define scpustate_foreach_gpregs_elem lcpustate_foreach_gpregs_elem
#endif /* !scpustate_foreach_gpregs_elem && lcpustate_foreach_gpregs_elem */
#if !defined(scpustate_foreach_gpregs_size) && defined(lcpustate_foreach_gpregs_size)
#define scpustate_foreach_gpregs_size lcpustate_foreach_gpregs_size
#endif /* !scpustate_foreach_gpregs_size && lcpustate_foreach_gpregs_size */
#if !defined(scpustate_getreturn32) && defined(lcpustate_getreturn32)
#define scpustate_getreturn32 lcpustate_getreturn32
#endif /* !scpustate_getreturn32 && lcpustate_getreturn32 */
#if !defined(scpustate_getreturn64) && defined(lcpustate_getreturn64)
#define scpustate_getreturn64 lcpustate_getreturn64
#endif /* !scpustate_getreturn64 && lcpustate_getreturn64 */
#if !defined(scpustate_setreturn32) && defined(lcpustate_setreturn32)
#define scpustate_setreturn32 lcpustate_setreturn32
#endif /* !scpustate_setreturn32 && lcpustate_setreturn32 */
#if !defined(scpustate_setreturn64) && defined(lcpustate_setreturn64)
#define scpustate_setreturn64 lcpustate_setreturn64
#endif /* !scpustate_setreturn64 && lcpustate_setreturn64 */
#if !defined(scpustate_current) && defined(lcpustate_current)
#define scpustate_current lcpustate_current
#endif /* !scpustate_current && lcpustate_current */
#if !defined(scpustate_isuser) && defined(lcpustate_isuser)
#define scpustate_isuser lcpustate_isuser
#endif /* !scpustate_isuser && lcpustate_isuser */
#if !defined(scpustate_iskern) && defined(lcpustate_iskern)
#define scpustate_iskern lcpustate_iskern
#endif /* !scpustate_iskern && lcpustate_iskern */
#elif defined(SCPUSTATE_IS_KCPUSTATE)
#ifndef scpustate_getpc
#define scpustate_getpc kcpustate_getpc
#endif /* !scpustate_getpc */
#ifndef scpustate_setpc
#define scpustate_setpc kcpustate_setpc
#endif /* !scpustate_setpc */
#ifndef scpustate_getsp
#define scpustate_getsp kcpustate_getsp
#endif /* !scpustate_getsp */
#ifndef scpustate_setsp
#define scpustate_setsp kcpustate_setsp
#endif /* !scpustate_setsp */
#if !defined(scpustate_foreach_gpregs) && defined(kcpustate_foreach_gpregs)
#define scpustate_foreach_gpregs kcpustate_foreach_gpregs
#endif /* !scpustate_foreach_gpregs && kcpustate_foreach_gpregs */
#if !defined(scpustate_foreach_gpregs_elem) && defined(kcpustate_foreach_gpregs_elem)
#define scpustate_foreach_gpregs_elem kcpustate_foreach_gpregs_elem
#endif /* !scpustate_foreach_gpregs_elem && kcpustate_foreach_gpregs_elem */
#if !defined(scpustate_foreach_gpregs_size) && defined(kcpustate_foreach_gpregs_size)
#define scpustate_foreach_gpregs_size kcpustate_foreach_gpregs_size
#endif /* !scpustate_foreach_gpregs_size && kcpustate_foreach_gpregs_size */
#if !defined(scpustate_getreturn32) && defined(kcpustate_getreturn32)
#define scpustate_getreturn32 kcpustate_getreturn32
#endif /* !scpustate_getreturn32 && kcpustate_getreturn32 */
#if !defined(scpustate_getreturn64) && defined(kcpustate_getreturn64)
#define scpustate_getreturn64 kcpustate_getreturn64
#endif /* !scpustate_getreturn64 && kcpustate_getreturn64 */
#if !defined(scpustate_setreturn32) && defined(kcpustate_setreturn32)
#define scpustate_setreturn32 kcpustate_setreturn32
#endif /* !scpustate_setreturn32 && kcpustate_setreturn32 */
#if !defined(scpustate_setreturn64) && defined(kcpustate_setreturn64)
#define scpustate_setreturn64 kcpustate_setreturn64
#endif /* !scpustate_setreturn64 && kcpustate_setreturn64 */
#if !defined(scpustate_current) && defined(kcpustate_current)
#define scpustate_current kcpustate_current
#endif /* !scpustate_current && kcpustate_current */
#if !defined(scpustate_isuser) && defined(kcpustate_isuser)
#define scpustate_isuser kcpustate_isuser
#endif /* !scpustate_isuser && kcpustate_isuser */
#if !defined(scpustate_iskern) && defined(kcpustate_iskern)
#define scpustate_iskern kcpustate_iskern
#endif /* !scpustate_iskern && kcpustate_iskern */
#elif defined(SCPUSTATE_IS_ICPUSTATE)
#ifndef scpustate_getpc
#define scpustate_getpc icpustate_getpc
#endif /* !scpustate_getpc */
#ifndef scpustate_setpc
#define scpustate_setpc icpustate_setpc
#endif /* !scpustate_setpc */
#ifndef scpustate_getsp
#define scpustate_getsp icpustate_getsp
#endif /* !scpustate_getsp */
#ifndef scpustate_setsp
#define scpustate_setsp icpustate_setsp
#endif /* !scpustate_setsp */
#if !defined(scpustate_foreach_gpregs) && defined(icpustate_foreach_gpregs)
#define scpustate_foreach_gpregs icpustate_foreach_gpregs
#endif /* !scpustate_foreach_gpregs && icpustate_foreach_gpregs */
#if !defined(scpustate_foreach_gpregs_elem) && defined(icpustate_foreach_gpregs_elem)
#define scpustate_foreach_gpregs_elem icpustate_foreach_gpregs_elem
#endif /* !scpustate_foreach_gpregs_elem && icpustate_foreach_gpregs_elem */
#if !defined(scpustate_foreach_gpregs_size) && defined(icpustate_foreach_gpregs_size)
#define scpustate_foreach_gpregs_size icpustate_foreach_gpregs_size
#endif /* !scpustate_foreach_gpregs_size && icpustate_foreach_gpregs_size */
#if !defined(scpustate_getreturn32) && defined(icpustate_getreturn32)
#define scpustate_getreturn32 icpustate_getreturn32
#endif /* !scpustate_getreturn32 && icpustate_getreturn32 */
#if !defined(scpustate_getreturn64) && defined(icpustate_getreturn64)
#define scpustate_getreturn64 icpustate_getreturn64
#endif /* !scpustate_getreturn64 && icpustate_getreturn64 */
#if !defined(scpustate_setreturn32) && defined(icpustate_setreturn32)
#define scpustate_setreturn32 icpustate_setreturn32
#endif /* !scpustate_setreturn32 && icpustate_setreturn32 */
#if !defined(scpustate_setreturn64) && defined(icpustate_setreturn64)
#define scpustate_setreturn64 icpustate_setreturn64
#endif /* !scpustate_setreturn64 && icpustate_setreturn64 */
#if !defined(scpustate_current) && defined(icpustate_current)
#define scpustate_current icpustate_current
#endif /* !scpustate_current && icpustate_current */
#if !defined(scpustate_isuser) && defined(icpustate_isuser)
#define scpustate_isuser icpustate_isuser
#endif /* !scpustate_isuser && icpustate_isuser */
#if !defined(scpustate_iskern) && defined(icpustate_iskern)
#define scpustate_iskern icpustate_iskern
#endif /* !scpustate_iskern && icpustate_iskern */
#endif /* SCPUSTATE_IS_?CPUSTATE */
#ifndef scpustate_getreturn
#if __SIZEOF_POINTER__ <= 4
#define scpustate_getreturn scpustate_getreturn32
#else /* __SIZEOF_POINTER__ <= 4 */
#define scpustate_getreturn scpustate_getreturn64
#endif /* __SIZEOF_POINTER__ > 4 */
#endif /* !scpustate_getreturn */
#ifndef scpustate_setreturn
#if __SIZEOF_POINTER__ <= 4
#define scpustate_setreturn scpustate_setreturn32
#else /* __SIZEOF_POINTER__ <= 4 */
#define scpustate_setreturn scpustate_setreturn64
#endif /* __SIZEOF_POINTER__ > 4 */
#endif /* !scpustate_setreturn */
#ifndef scpustate_getreturnbool
#define scpustate_getreturnbool(x) (scpustate_getreturn(x) != 0)
#endif /* !scpustate_getreturnbool */
#ifndef scpustate_setreturnbool
#define scpustate_setreturnbool(x, v) scpustate_setreturn(x, (v) ? 1 : 0)
#endif /* !scpustate_setreturnbool */
#if !defined(scpustate_foreach_gpregs) && defined(scpustate_foreach_gpregs_elem) && defined(scpustate_foreach_gpregs_size)
#define scpustate_foreach_gpregs(self, cb)                                         \
	do {                                                                           \
		unsigned int __scpustate_foreach_gpregs_i;                                 \
		for (__scpustate_foreach_gpregs_i = 0;                                     \
		     __scpustate_foreach_gpregs_i < scpustate_foreach_gpregs_size(self);   \
		     ++__scpustate_foreach_gpregs_i) {                                     \
			cb(scpustate_foreach_gpregs_elem(self)[__scpustate_foreach_gpregs_i]); \
		}                                                                          \
	}	__WHILE0
#endif /* !scpustate_foreach_gpregs && scpustate_foreach_gpregs_elem && scpustate_foreach_gpregs_size */



/************************************************************************/
/* fcpustate                                                            */
/************************************************************************/
#ifdef FCPUSTATE_IS_UCPUSTATE
#ifndef fcpustate_getpc
#define fcpustate_getpc ucpustate_getpc
#endif /* !fcpustate_getpc */
#ifndef fcpustate_setpc
#define fcpustate_setpc ucpustate_setpc
#endif /* !fcpustate_setpc */
#ifndef fcpustate_getsp
#define fcpustate_getsp ucpustate_getsp
#endif /* !fcpustate_getsp */
#ifndef fcpustate_setsp
#define fcpustate_setsp ucpustate_setsp
#endif /* !fcpustate_setsp */
#if !defined(fcpustate_foreach_gpregs) && defined(ucpustate_foreach_gpregs)
#define fcpustate_foreach_gpregs ucpustate_foreach_gpregs
#endif /* !fcpustate_foreach_gpregs && ucpustate_foreach_gpregs */
#if !defined(fcpustate_foreach_gpregs_elem) && defined(ucpustate_foreach_gpregs_elem)
#define fcpustate_foreach_gpregs_elem ucpustate_foreach_gpregs_elem
#endif /* !fcpustate_foreach_gpregs_elem && ucpustate_foreach_gpregs_elem */
#if !defined(fcpustate_foreach_gpregs_size) && defined(ucpustate_foreach_gpregs_size)
#define fcpustate_foreach_gpregs_size ucpustate_foreach_gpregs_size
#endif /* !fcpustate_foreach_gpregs_size && ucpustate_foreach_gpregs_size */
#if !defined(fcpustate_getreturn32) && defined(ucpustate_getreturn32)
#define fcpustate_getreturn32 ucpustate_getreturn32
#endif /* !fcpustate_getreturn32 && ucpustate_getreturn32 */
#if !defined(fcpustate_getreturn64) && defined(ucpustate_getreturn64)
#define fcpustate_getreturn64 ucpustate_getreturn64
#endif /* !fcpustate_getreturn64 && ucpustate_getreturn64 */
#if !defined(fcpustate_setreturn32) && defined(ucpustate_setreturn32)
#define fcpustate_setreturn32 ucpustate_setreturn32
#endif /* !fcpustate_setreturn32 && ucpustate_setreturn32 */
#if !defined(fcpustate_setreturn64) && defined(ucpustate_setreturn64)
#define fcpustate_setreturn64 ucpustate_setreturn64
#endif /* !fcpustate_setreturn64 && ucpustate_setreturn64 */
#if !defined(fcpustate_current) && defined(ucpustate_current)
#define fcpustate_current ucpustate_current
#endif /* !fcpustate_current && ucpustate_current */
#if !defined(fcpustate_isuser) && defined(ucpustate_isuser)
#define fcpustate_isuser ucpustate_isuser
#endif /* !fcpustate_isuser && ucpustate_isuser */
#if !defined(fcpustate_iskern) && defined(ucpustate_iskern)
#define fcpustate_iskern ucpustate_iskern
#endif /* !fcpustate_iskern && ucpustate_iskern */
#elif defined(FCPUSTATE_IS_LCPUSTATE)
#ifndef fcpustate_getpc
#define fcpustate_getpc lcpustate_getpc
#endif /* !fcpustate_getpc */
#ifndef fcpustate_setpc
#define fcpustate_setpc lcpustate_setpc
#endif /* !fcpustate_setpc */
#ifndef fcpustate_getsp
#define fcpustate_getsp lcpustate_getsp
#endif /* !fcpustate_getsp */
#ifndef fcpustate_setsp
#define fcpustate_setsp lcpustate_setsp
#endif /* !fcpustate_setsp */
#if !defined(fcpustate_foreach_gpregs) && defined(lcpustate_foreach_gpregs)
#define fcpustate_foreach_gpregs lcpustate_foreach_gpregs
#endif /* !fcpustate_foreach_gpregs && lcpustate_foreach_gpregs */
#if !defined(fcpustate_foreach_gpregs_elem) && defined(lcpustate_foreach_gpregs_elem)
#define fcpustate_foreach_gpregs_elem lcpustate_foreach_gpregs_elem
#endif /* !fcpustate_foreach_gpregs_elem && lcpustate_foreach_gpregs_elem */
#if !defined(fcpustate_foreach_gpregs_size) && defined(lcpustate_foreach_gpregs_size)
#define fcpustate_foreach_gpregs_size lcpustate_foreach_gpregs_size
#endif /* !fcpustate_foreach_gpregs_size && lcpustate_foreach_gpregs_size */
#if !defined(fcpustate_getreturn32) && defined(lcpustate_getreturn32)
#define fcpustate_getreturn32 lcpustate_getreturn32
#endif /* !fcpustate_getreturn32 && lcpustate_getreturn32 */
#if !defined(fcpustate_getreturn64) && defined(lcpustate_getreturn64)
#define fcpustate_getreturn64 lcpustate_getreturn64
#endif /* !fcpustate_getreturn64 && lcpustate_getreturn64 */
#if !defined(fcpustate_setreturn32) && defined(lcpustate_setreturn32)
#define fcpustate_setreturn32 lcpustate_setreturn32
#endif /* !fcpustate_setreturn32 && lcpustate_setreturn32 */
#if !defined(fcpustate_setreturn64) && defined(lcpustate_setreturn64)
#define fcpustate_setreturn64 lcpustate_setreturn64
#endif /* !fcpustate_setreturn64 && lcpustate_setreturn64 */
#if !defined(fcpustate_current) && defined(lcpustate_current)
#define fcpustate_current lcpustate_current
#endif /* !fcpustate_current && lcpustate_current */
#if !defined(fcpustate_isuser) && defined(lcpustate_isuser)
#define fcpustate_isuser lcpustate_isuser
#endif /* !fcpustate_isuser && lcpustate_isuser */
#if !defined(fcpustate_iskern) && defined(lcpustate_iskern)
#define fcpustate_iskern lcpustate_iskern
#endif /* !fcpustate_iskern && lcpustate_iskern */
#elif defined(FCPUSTATE_IS_KCPUSTATE)
#ifndef fcpustate_getpc
#define fcpustate_getpc kcpustate_getpc
#endif /* !fcpustate_getpc */
#ifndef fcpustate_setpc
#define fcpustate_setpc kcpustate_setpc
#endif /* !fcpustate_setpc */
#ifndef fcpustate_getsp
#define fcpustate_getsp kcpustate_getsp
#endif /* !fcpustate_getsp */
#ifndef fcpustate_setsp
#define fcpustate_setsp kcpustate_setsp
#endif /* !fcpustate_setsp */
#if !defined(fcpustate_foreach_gpregs) && defined(kcpustate_foreach_gpregs)
#define fcpustate_foreach_gpregs kcpustate_foreach_gpregs
#endif /* !fcpustate_foreach_gpregs && kcpustate_foreach_gpregs */
#if !defined(fcpustate_foreach_gpregs_elem) && defined(kcpustate_foreach_gpregs_elem)
#define fcpustate_foreach_gpregs_elem kcpustate_foreach_gpregs_elem
#endif /* !fcpustate_foreach_gpregs_elem && kcpustate_foreach_gpregs_elem */
#if !defined(fcpustate_foreach_gpregs_size) && defined(kcpustate_foreach_gpregs_size)
#define fcpustate_foreach_gpregs_size kcpustate_foreach_gpregs_size
#endif /* !fcpustate_foreach_gpregs_size && kcpustate_foreach_gpregs_size */
#if !defined(fcpustate_getreturn32) && defined(kcpustate_getreturn32)
#define fcpustate_getreturn32 kcpustate_getreturn32
#endif /* !fcpustate_getreturn32 && kcpustate_getreturn32 */
#if !defined(fcpustate_getreturn64) && defined(kcpustate_getreturn64)
#define fcpustate_getreturn64 kcpustate_getreturn64
#endif /* !fcpustate_getreturn64 && kcpustate_getreturn64 */
#if !defined(fcpustate_setreturn32) && defined(kcpustate_setreturn32)
#define fcpustate_setreturn32 kcpustate_setreturn32
#endif /* !fcpustate_setreturn32 && kcpustate_setreturn32 */
#if !defined(fcpustate_setreturn64) && defined(kcpustate_setreturn64)
#define fcpustate_setreturn64 kcpustate_setreturn64
#endif /* !fcpustate_setreturn64 && kcpustate_setreturn64 */
#if !defined(fcpustate_current) && defined(kcpustate_current)
#define fcpustate_current kcpustate_current
#endif /* !fcpustate_current && kcpustate_current */
#if !defined(fcpustate_isuser) && defined(kcpustate_isuser)
#define fcpustate_isuser kcpustate_isuser
#endif /* !fcpustate_isuser && kcpustate_isuser */
#if !defined(fcpustate_iskern) && defined(kcpustate_iskern)
#define fcpustate_iskern kcpustate_iskern
#endif /* !fcpustate_iskern && kcpustate_iskern */
#elif defined(FCPUSTATE_IS_ICPUSTATE)
#ifndef fcpustate_getpc
#define fcpustate_getpc icpustate_getpc
#endif /* !fcpustate_getpc */
#ifndef fcpustate_setpc
#define fcpustate_setpc icpustate_setpc
#endif /* !fcpustate_setpc */
#ifndef fcpustate_getsp
#define fcpustate_getsp icpustate_getsp
#endif /* !fcpustate_getsp */
#ifndef fcpustate_setsp
#define fcpustate_setsp icpustate_setsp
#endif /* !fcpustate_setsp */
#if !defined(fcpustate_foreach_gpregs) && defined(icpustate_foreach_gpregs)
#define fcpustate_foreach_gpregs icpustate_foreach_gpregs
#endif /* !fcpustate_foreach_gpregs && icpustate_foreach_gpregs */
#if !defined(fcpustate_foreach_gpregs_elem) && defined(icpustate_foreach_gpregs_elem)
#define fcpustate_foreach_gpregs_elem icpustate_foreach_gpregs_elem
#endif /* !fcpustate_foreach_gpregs_elem && icpustate_foreach_gpregs_elem */
#if !defined(fcpustate_foreach_gpregs_size) && defined(icpustate_foreach_gpregs_size)
#define fcpustate_foreach_gpregs_size icpustate_foreach_gpregs_size
#endif /* !fcpustate_foreach_gpregs_size && icpustate_foreach_gpregs_size */
#if !defined(fcpustate_getreturn32) && defined(icpustate_getreturn32)
#define fcpustate_getreturn32 icpustate_getreturn32
#endif /* !fcpustate_getreturn32 && icpustate_getreturn32 */
#if !defined(fcpustate_getreturn64) && defined(icpustate_getreturn64)
#define fcpustate_getreturn64 icpustate_getreturn64
#endif /* !fcpustate_getreturn64 && icpustate_getreturn64 */
#if !defined(fcpustate_setreturn32) && defined(icpustate_setreturn32)
#define fcpustate_setreturn32 icpustate_setreturn32
#endif /* !fcpustate_setreturn32 && icpustate_setreturn32 */
#if !defined(fcpustate_setreturn64) && defined(icpustate_setreturn64)
#define fcpustate_setreturn64 icpustate_setreturn64
#endif /* !fcpustate_setreturn64 && icpustate_setreturn64 */
#if !defined(fcpustate_current) && defined(icpustate_current)
#define fcpustate_current icpustate_current
#endif /* !fcpustate_current && icpustate_current */
#if !defined(fcpustate_isuser) && defined(icpustate_isuser)
#define fcpustate_isuser icpustate_isuser
#endif /* !fcpustate_isuser && icpustate_isuser */
#if !defined(fcpustate_iskern) && defined(icpustate_iskern)
#define fcpustate_iskern icpustate_iskern
#endif /* !fcpustate_iskern && icpustate_iskern */
#elif defined(FCPUSTATE_IS_SCPUSTATE)
#ifndef fcpustate_getpc
#define fcpustate_getpc scpustate_getpc
#endif /* !fcpustate_getpc */
#ifndef fcpustate_setpc
#define fcpustate_setpc scpustate_setpc
#endif /* !fcpustate_setpc */
#ifndef fcpustate_getsp
#define fcpustate_getsp scpustate_getsp
#endif /* !fcpustate_getsp */
#ifndef fcpustate_setsp
#define fcpustate_setsp scpustate_setsp
#endif /* !fcpustate_setsp */
#if !defined(fcpustate_foreach_gpregs) && defined(scpustate_foreach_gpregs)
#define fcpustate_foreach_gpregs scpustate_foreach_gpregs
#endif /* !fcpustate_foreach_gpregs && scpustate_foreach_gpregs */
#if !defined(fcpustate_foreach_gpregs_elem) && defined(scpustate_foreach_gpregs_elem)
#define fcpustate_foreach_gpregs_elem scpustate_foreach_gpregs_elem
#endif /* !fcpustate_foreach_gpregs_elem && scpustate_foreach_gpregs_elem */
#if !defined(fcpustate_foreach_gpregs_size) && defined(scpustate_foreach_gpregs_size)
#define fcpustate_foreach_gpregs_size scpustate_foreach_gpregs_size
#endif /* !fcpustate_foreach_gpregs_size && scpustate_foreach_gpregs_size */
#if !defined(fcpustate_getreturn32) && defined(scpustate_getreturn32)
#define fcpustate_getreturn32 scpustate_getreturn32
#endif /* !fcpustate_getreturn32 && scpustate_getreturn32 */
#if !defined(fcpustate_getreturn64) && defined(scpustate_getreturn64)
#define fcpustate_getreturn64 scpustate_getreturn64
#endif /* !fcpustate_getreturn64 && scpustate_getreturn64 */
#if !defined(fcpustate_setreturn32) && defined(scpustate_setreturn32)
#define fcpustate_setreturn32 scpustate_setreturn32
#endif /* !fcpustate_setreturn32 && scpustate_setreturn32 */
#if !defined(fcpustate_setreturn64) && defined(scpustate_setreturn64)
#define fcpustate_setreturn64 scpustate_setreturn64
#endif /* !fcpustate_setreturn64 && scpustate_setreturn64 */
#if !defined(fcpustate_current) && defined(scpustate_current)
#define fcpustate_current scpustate_current
#endif /* !fcpustate_current && scpustate_current */
#if !defined(fcpustate_isuser) && defined(scpustate_isuser)
#define fcpustate_isuser scpustate_isuser
#endif /* !fcpustate_isuser && scpustate_isuser */
#if !defined(fcpustate_iskern) && defined(scpustate_iskern)
#define fcpustate_iskern scpustate_iskern
#endif /* !fcpustate_iskern && scpustate_iskern */
#endif /* FCPUSTATE_IS_?CPUSTATE */
#ifndef fcpustate_getreturn
#if __SIZEOF_POINTER__ <= 4
#define fcpustate_getreturn fcpustate_getreturn32
#else /* __SIZEOF_POINTER__ <= 4 */
#define fcpustate_getreturn fcpustate_getreturn64
#endif /* __SIZEOF_POINTER__ > 4 */
#endif /* !fcpustate_getreturn */
#ifndef fcpustate_setreturn
#if __SIZEOF_POINTER__ <= 4
#define fcpustate_setreturn fcpustate_setreturn32
#else /* __SIZEOF_POINTER__ <= 4 */
#define fcpustate_setreturn fcpustate_setreturn64
#endif /* __SIZEOF_POINTER__ > 4 */
#endif /* !fcpustate_setreturn */
#ifndef fcpustate_getreturnbool
#define fcpustate_getreturnbool(x) (fcpustate_getreturn(x) != 0)
#endif /* !fcpustate_getreturnbool */
#ifndef fcpustate_setreturnbool
#define fcpustate_setreturnbool(x, v) fcpustate_setreturn(x, (v) ? 1 : 0)
#endif /* !fcpustate_setreturnbool */
#if !defined(fcpustate_foreach_gpregs) && defined(fcpustate_foreach_gpregs_elem) && defined(fcpustate_foreach_gpregs_size)
#define fcpustate_foreach_gpregs(self, cb)                                         \
	do {                                                                           \
		unsigned int __fcpustate_foreach_gpregs_i;                                 \
		for (__fcpustate_foreach_gpregs_i = 0;                                     \
		     __fcpustate_foreach_gpregs_i < fcpustate_foreach_gpregs_size(self);   \
		     ++__fcpustate_foreach_gpregs_i) {                                     \
			cb(fcpustate_foreach_gpregs_elem(self)[__fcpustate_foreach_gpregs_i]); \
		}                                                                          \
	}	__WHILE0
#endif /* !fcpustate_foreach_gpregs && fcpustate_foreach_gpregs_elem && fcpustate_foreach_gpregs_size */
#ifdef LCPUSTATE_IS_UCPUSTATE
#ifndef KCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define lcpustate_to_kcpustate ucpustate_to_kcpustate
#define kcpustate_to_lcpustate kcpustate_to_ucpustate
#endif /* !KCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef ICPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define lcpustate_to_icpustate ucpustate_to_icpustate
#define icpustate_to_lcpustate icpustate_to_ucpustate
#endif /* !ICPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef SCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define lcpustate_to_scpustate ucpustate_to_scpustate
#define scpustate_to_lcpustate scpustate_to_ucpustate
#endif /* !SCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef FCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define lcpustate_to_fcpustate ucpustate_to_fcpustate
#define fcpustate_to_lcpustate fcpustate_to_ucpustate
#endif /* !FCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#endif /* LCPUSTATE_IS_?CPUSTATE */
#ifdef KCPUSTATE_IS_UCPUSTATE
#ifndef LCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define kcpustate_to_lcpustate ucpustate_to_lcpustate
#define lcpustate_to_kcpustate lcpustate_to_ucpustate
#endif /* !LCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef ICPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define kcpustate_to_icpustate ucpustate_to_icpustate
#define icpustate_to_kcpustate icpustate_to_ucpustate
#endif /* !ICPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef SCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define kcpustate_to_scpustate ucpustate_to_scpustate
#define scpustate_to_kcpustate scpustate_to_ucpustate
#endif /* !SCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef FCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define kcpustate_to_fcpustate ucpustate_to_fcpustate
#define fcpustate_to_kcpustate fcpustate_to_ucpustate
#endif /* !FCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#elif defined(KCPUSTATE_IS_LCPUSTATE)
#ifndef LCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define kcpustate_to_ucpustate lcpustate_to_ucpustate
#define ucpustate_to_kcpustate ucpustate_to_lcpustate
#endif /* !LCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef ICPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define kcpustate_to_icpustate lcpustate_to_icpustate
#define icpustate_to_kcpustate icpustate_to_lcpustate
#endif /* !ICPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#ifndef SCPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define kcpustate_to_scpustate lcpustate_to_scpustate
#define scpustate_to_kcpustate scpustate_to_lcpustate
#endif /* !SCPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#ifndef FCPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define kcpustate_to_fcpustate lcpustate_to_fcpustate
#define fcpustate_to_kcpustate fcpustate_to_lcpustate
#endif /* !FCPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#endif /* KCPUSTATE_IS_?CPUSTATE */
#ifdef ICPUSTATE_IS_UCPUSTATE
#ifndef LCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define icpustate_to_lcpustate ucpustate_to_lcpustate
#define lcpustate_to_icpustate lcpustate_to_ucpustate
#endif /* !LCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef KCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define icpustate_to_kcpustate ucpustate_to_kcpustate
#define kcpustate_to_icpustate kcpustate_to_ucpustate
#endif /* !KCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef SCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define icpustate_to_scpustate ucpustate_to_scpustate
#define scpustate_to_icpustate scpustate_to_ucpustate
#endif /* !SCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef FCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define icpustate_to_fcpustate ucpustate_to_fcpustate
#define fcpustate_to_icpustate fcpustate_to_ucpustate
#endif /* !FCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#elif defined(ICPUSTATE_IS_LCPUSTATE)
#ifndef LCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define icpustate_to_ucpustate lcpustate_to_ucpustate
#define ucpustate_to_icpustate ucpustate_to_lcpustate
#endif /* !LCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef KCPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define icpustate_to_kcpustate lcpustate_to_kcpustate
#define kcpustate_to_icpustate kcpustate_to_lcpustate
#endif /* !KCPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#ifndef SCPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define icpustate_to_scpustate lcpustate_to_scpustate
#define scpustate_to_icpustate scpustate_to_lcpustate
#endif /* !SCPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#ifndef FCPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define icpustate_to_fcpustate lcpustate_to_fcpustate
#define fcpustate_to_icpustate fcpustate_to_lcpustate
#endif /* !FCPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#elif defined(ICPUSTATE_IS_KCPUSTATE)
#ifndef KCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define icpustate_to_ucpustate kcpustate_to_ucpustate
#define ucpustate_to_icpustate ucpustate_to_kcpustate
#endif /* !KCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef KCPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define icpustate_to_lcpustate kcpustate_to_lcpustate
#define lcpustate_to_icpustate lcpustate_to_kcpustate
#endif /* !KCPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#ifndef SCPUSTATE_IS_TRANSITIVE_KCPUSTATE
#define icpustate_to_scpustate kcpustate_to_scpustate
#define scpustate_to_icpustate scpustate_to_kcpustate
#endif /* !SCPUSTATE_IS_TRANSITIVE_KCPUSTATE */
#ifndef FCPUSTATE_IS_TRANSITIVE_KCPUSTATE
#define icpustate_to_fcpustate kcpustate_to_fcpustate
#define fcpustate_to_icpustate fcpustate_to_kcpustate
#endif /* !FCPUSTATE_IS_TRANSITIVE_KCPUSTATE */
#endif /* ICPUSTATE_IS_?CPUSTATE */
#ifdef SCPUSTATE_IS_UCPUSTATE
#ifndef LCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define scpustate_to_lcpustate ucpustate_to_lcpustate
#define lcpustate_to_scpustate lcpustate_to_ucpustate
#endif /* !LCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef KCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define scpustate_to_kcpustate ucpustate_to_kcpustate
#define kcpustate_to_scpustate kcpustate_to_ucpustate
#endif /* !KCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef ICPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define scpustate_to_icpustate ucpustate_to_icpustate
#define icpustate_to_scpustate icpustate_to_ucpustate
#endif /* !ICPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef FCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define scpustate_to_fcpustate ucpustate_to_fcpustate
#define fcpustate_to_scpustate fcpustate_to_ucpustate
#endif /* !FCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#elif defined(SCPUSTATE_IS_LCPUSTATE)
#ifndef LCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define scpustate_to_ucpustate lcpustate_to_ucpustate
#define ucpustate_to_scpustate ucpustate_to_lcpustate
#endif /* !LCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef KCPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define scpustate_to_kcpustate lcpustate_to_kcpustate
#define kcpustate_to_scpustate kcpustate_to_lcpustate
#endif /* !KCPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#ifndef ICPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define scpustate_to_icpustate lcpustate_to_icpustate
#define icpustate_to_scpustate icpustate_to_lcpustate
#endif /* !ICPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#ifndef FCPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define scpustate_to_fcpustate lcpustate_to_fcpustate
#define fcpustate_to_scpustate fcpustate_to_lcpustate
#endif /* !FCPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#elif defined(SCPUSTATE_IS_KCPUSTATE)
#ifndef KCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define scpustate_to_ucpustate kcpustate_to_ucpustate
#define ucpustate_to_scpustate ucpustate_to_kcpustate
#endif /* !KCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef KCPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define scpustate_to_lcpustate kcpustate_to_lcpustate
#define lcpustate_to_scpustate lcpustate_to_kcpustate
#endif /* !KCPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#ifndef ICPUSTATE_IS_TRANSITIVE_KCPUSTATE
#define scpustate_to_icpustate kcpustate_to_icpustate
#define icpustate_to_scpustate icpustate_to_kcpustate
#endif /* !ICPUSTATE_IS_TRANSITIVE_KCPUSTATE */
#ifndef FCPUSTATE_IS_TRANSITIVE_KCPUSTATE
#define scpustate_to_fcpustate kcpustate_to_fcpustate
#define fcpustate_to_scpustate fcpustate_to_kcpustate
#endif /* !FCPUSTATE_IS_TRANSITIVE_KCPUSTATE */
#elif defined(SCPUSTATE_IS_ICPUSTATE)
#ifndef ICPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define scpustate_to_ucpustate icpustate_to_ucpustate
#define ucpustate_to_scpustate ucpustate_to_icpustate
#endif /* !ICPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef ICPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define scpustate_to_lcpustate icpustate_to_lcpustate
#define lcpustate_to_scpustate lcpustate_to_icpustate
#endif /* !ICPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#ifndef ICPUSTATE_IS_TRANSITIVE_KCPUSTATE
#define scpustate_to_kcpustate icpustate_to_kcpustate
#define kcpustate_to_scpustate kcpustate_to_icpustate
#endif /* !ICPUSTATE_IS_TRANSITIVE_KCPUSTATE */
#ifndef FCPUSTATE_IS_TRANSITIVE_ICPUSTATE
#define scpustate_to_fcpustate icpustate_to_fcpustate
#define fcpustate_to_scpustate fcpustate_to_icpustate
#endif /* !FCPUSTATE_IS_TRANSITIVE_ICPUSTATE */
#endif /* SCPUSTATE_IS_?CPUSTATE */
#ifdef FCPUSTATE_IS_UCPUSTATE
#ifndef LCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define fcpustate_to_lcpustate ucpustate_to_lcpustate
#define lcpustate_to_fcpustate lcpustate_to_ucpustate
#endif /* !LCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef KCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define fcpustate_to_kcpustate ucpustate_to_kcpustate
#define kcpustate_to_fcpustate kcpustate_to_ucpustate
#endif /* !KCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef ICPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define fcpustate_to_icpustate ucpustate_to_icpustate
#define icpustate_to_fcpustate icpustate_to_ucpustate
#endif /* !ICPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef SCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define fcpustate_to_scpustate ucpustate_to_scpustate
#define scpustate_to_fcpustate scpustate_to_ucpustate
#endif /* !SCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#elif defined(FCPUSTATE_IS_LCPUSTATE)
#ifndef LCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define fcpustate_to_ucpustate lcpustate_to_ucpustate
#define ucpustate_to_fcpustate ucpustate_to_lcpustate
#endif /* !LCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef KCPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define fcpustate_to_kcpustate lcpustate_to_kcpustate
#define kcpustate_to_fcpustate kcpustate_to_lcpustate
#endif /* !KCPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#ifndef ICPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define fcpustate_to_icpustate lcpustate_to_icpustate
#define icpustate_to_fcpustate icpustate_to_lcpustate
#endif /* !ICPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#ifndef SCPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define fcpustate_to_scpustate lcpustate_to_scpustate
#define scpustate_to_fcpustate scpustate_to_lcpustate
#endif /* !SCPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#elif defined(FCPUSTATE_IS_KCPUSTATE)
#ifndef KCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define fcpustate_to_ucpustate kcpustate_to_ucpustate
#define ucpustate_to_fcpustate ucpustate_to_kcpustate
#endif /* !KCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef KCPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define fcpustate_to_lcpustate kcpustate_to_lcpustate
#define lcpustate_to_fcpustate lcpustate_to_kcpustate
#endif /* !KCPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#ifndef ICPUSTATE_IS_TRANSITIVE_KCPUSTATE
#define fcpustate_to_icpustate kcpustate_to_icpustate
#define icpustate_to_fcpustate icpustate_to_kcpustate
#endif /* !ICPUSTATE_IS_TRANSITIVE_KCPUSTATE */
#ifndef SCPUSTATE_IS_TRANSITIVE_KCPUSTATE
#define fcpustate_to_scpustate kcpustate_to_scpustate
#define scpustate_to_fcpustate scpustate_to_kcpustate
#endif /* !SCPUSTATE_IS_TRANSITIVE_KCPUSTATE */
#elif defined(FCPUSTATE_IS_ICPUSTATE)
#ifndef ICPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define fcpustate_to_ucpustate icpustate_to_ucpustate
#define ucpustate_to_fcpustate ucpustate_to_icpustate
#endif /* !ICPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef ICPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define fcpustate_to_lcpustate icpustate_to_lcpustate
#define lcpustate_to_fcpustate lcpustate_to_icpustate
#endif /* !ICPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#ifndef ICPUSTATE_IS_TRANSITIVE_KCPUSTATE
#define fcpustate_to_kcpustate icpustate_to_kcpustate
#define kcpustate_to_fcpustate kcpustate_to_icpustate
#endif /* !ICPUSTATE_IS_TRANSITIVE_KCPUSTATE */
#ifndef SCPUSTATE_IS_TRANSITIVE_ICPUSTATE
#define fcpustate_to_scpustate icpustate_to_scpustate
#define scpustate_to_fcpustate scpustate_to_icpustate
#endif /* !SCPUSTATE_IS_TRANSITIVE_ICPUSTATE */
#elif defined(FCPUSTATE_IS_SCPUSTATE)
#ifndef SCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define fcpustate_to_ucpustate scpustate_to_ucpustate
#define ucpustate_to_fcpustate ucpustate_to_scpustate
#endif /* !SCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#ifndef SCPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define fcpustate_to_lcpustate scpustate_to_lcpustate
#define lcpustate_to_fcpustate lcpustate_to_scpustate
#endif /* !SCPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#ifndef SCPUSTATE_IS_TRANSITIVE_KCPUSTATE
#define fcpustate_to_kcpustate scpustate_to_kcpustate
#define kcpustate_to_fcpustate kcpustate_to_scpustate
#endif /* !SCPUSTATE_IS_TRANSITIVE_KCPUSTATE */
#ifndef SCPUSTATE_IS_TRANSITIVE_ICPUSTATE
#define fcpustate_to_icpustate scpustate_to_icpustate
#define icpustate_to_fcpustate icpustate_to_scpustate
#endif /* !SCPUSTATE_IS_TRANSITIVE_ICPUSTATE */
#endif /* FCPUSTATE_IS_?CPUSTATE */
/*[[[end]]]*/

#endif /* !_KOS_KERNEL_CPU_STATE_HELPERS_H */
