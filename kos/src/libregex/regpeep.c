/*[[[magic
options["COMPILE.language"] = "c";
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.removeif([](x) -> x.startswith("-O"));
// Actually: want to optimize to minimize stack memory usage, but this is the next-best thing
gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_LIBREGEX_REGPEEP_C
#define GUARD_LIBREGEX_REGPEEP_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define LIBREGEX_WANT_PROTOTYPES

#include "api.h"
/**/
#include <hybrid/compiler.h>

#include <hybrid/unaligned.h>

#include <kos/types.h>
#include <sys/bitstring.h>

#include <alloca.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <unicode.h>

#include <libregex/regcomp.h>

#include "regexec.h"
#include "regfast.h"

#if 0
#include <sys/syslog.h>
#define HAVE_TRACE
#define TRACE(...) syslog(LOG_DEBUG, __VA_ARGS__)
#else
#define TRACE(...) (void)0
#endif

DECL_BEGIN

/* Apply peephole optimizations to the code produced by `self' */
INTERN NONNULL((1)) re_errno_t
NOTHROW_NCX(CC libre_code_makepeep)(struct re_compiler *__restrict self) {

	/* TODO: Insert `REOP_POP_ONFAIL' opcodes.
	 *
	 * Compare the matches of  bi-branches (e.g. `REOP_JMP_ONFAIL'). If  no
	 * input exists that can possibly match both branches, then the on-fail
	 * item can be popped at the point where this becomes a guaranty in the
	 * non-failing branch.
	 * -> Optimize "ab?c" -> once "ab" has been matched, there's no
	 *    point in keeping the on-fail item that could match input "ac",
	 *    since we already know that it could never match
	 *    >>     REOP_BYTE       "a"
	 *    >>     REOP_JMP_ONFAIL 1f
	 *    >>     REOP_BYTE       "b"
	 *    >>     REOP_POP_ONFAIL     // <<< It is our job to insert this opcode right here!
	 *    >> 1:  REOP_BYTE       "c"
	 * -> Optimize "a([[:alpha:]]X[bB]|[[:lower:]]Y[bB])c" Once  'X' has  been
	 *    matched in the first branch, it is a guaranty that the second branch
	 *    can never be matched (until then it wasn't, since input exists  that
	 *    can match both [[:alpha:]] and [[:lower:]]).
	 *    >>     REOP_BYTE       "a"
	 *    >>     REOP_GROUP_START 0
	 *    >>     REOP_JMP_ONFAIL 1f
	 *    >>     REOP_CS_UTF8    [RECS_ISALPHA, RECS_DONE]
	 *    >>     // NOTE: The POP_ONFAIL isn't be inserted here, because input
	 *    >>     //       exists that matches both `RECS_ISALPHA' and `RECS_ISLOWER'
	 *    >>     REOP_BYTE       "X"
	 *    >>     REOP_POP_ONFAIL // <<< It is our job to insert this opcode right here!
	 *    >>     REOP_CS_UTF8    [RECS_CHAR2 "bB"]
	 *    >>     REOP_JMP        2f
	 *    >> 1:  REOP_CS_UTF8    [RECS_ISLOWER, RECS_DONE]
	 *    >>     REOP_BYTE       "Y"
	 *    >>     REOP_CS_UTF8    [RECS_CHAR2 "bB"]
	 *    >> 2:  REOP_GROUP_END  0
	 *    >>     REOP_BYTE       "c"
	 * -> Care must be taken not to insert an `REOP_POP_ONFAIL' opcode AFTER
	 *    the failing and non-failing branches have already re-joined. (XXX:
	 *    why not let the compiler produce a filler  `REOP_MAYBE_POP_ONFAIL'
	 *    opcode if appropriate? We could  then replace/move that opcode  to
	 *    the earliest-most location, and  replace with `REOP_NOP' if  input
	 *    exists that matches both branches, or `REOP_POP_ONFAIL' if no such
	 *    input exists)
	 *
	 *
	 * If both branches always consume  the same number of  bytes/characters
	 * (prior to joining back together), then the non-failing branch can pop
	 * the on-fail item prior to re-joining.
	 * -> Optimize "a(foo|[Ff]oo)b" -> once "afoo" has been matched, there's no
	 *    point in keeping the on-fail item for "[Ff]oo". Even though it  could
	 *    also match input "afoob", it won't be  able to do so any better  than
	 *    the "foo" branch.
	 */


	/* XXX: On host architectures without unaligned memory access, reflow generated
	 *      code by inserting `REOP_NOP' opcodes before instructions with unaligned
	 *      jump offsets.
	 *
	 * What makes this complicated is the fact that doing so can break  jump-offsets,
	 * meaning that such a mechanism would first have to identify all jumps, the make
	 * relocations for each of them, then go through and insert padding NOPs,  before
	 * finally re-applying relocations, thus fixing the jump-offsets it just broken.
	 *
	 * Furthermore, I'm not entirely certain if doing this would even be beneficial
	 * to  performance, as the extra NOPs must be just as slow as the unconditional
	 * unaligned reads currently done by `getw()' in "./regexec.c".
	 */

	/* TODO */
	(void)self;
	COMPILER_IMPURE();
	return RE_NOERROR;
}

DECL_END

#endif /* !GUARD_LIBREGEX_REGPEEP_C */
