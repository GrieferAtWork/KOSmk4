/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
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
#ifndef GUARD_KERNEL_SRC_DEBUGGER_EVAL_C
#define GUARD_KERNEL_SRC_DEBUGGER_EVAL_C 1
#define DISABLE_BRANCH_PROFILING
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <debugger/util.h>

#include <hybrid/typecore.h>

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

DECL_BEGIN


#if __SIZEOF_POINTER__ == 4
#define STRTOPTR  strtou32
#elif __SIZEOF_POINTER__ == 8
#define STRTOPTR  strtou64
#elif __SIZEOF_POINTER__ <= __SIZEOF_LONG__
#define STRTOPTR  (uintptr_t)strtoul
#else
#define STRTOPTR  (uintptr_t)strtoull
#endif

PRIVATE ATTR_DBGBSS char const *ev_current_expression = NULL;

PRIVATE ATTR_DBGTEXT bool
NOTHROW(KCALL ev_verrorf)(unsigned int flags,
                          char const *format,
                          va_list args) {
	/* TODO */
	(void)flags;
	(void)format;
	(void)args;
	return false;
}

PRIVATE ATTR_DBGTEXT bool
NOTHROW(VCALL ev_errorf)(unsigned int flags,
                         char const *format, ...) {
	bool result;
	va_list args;
	va_start(args, format);
	result = ev_verrorf(flags, format, args);
	va_end(args);
	return result;
}


PRIVATE ATTR_DBGTEXT bool
NOTHROW(FCALL ev_expr)(char **__restrict pp,
                       uintptr_t *presult,
                       unsigned int flags);

PRIVATE ATTR_DBGTEXT bool
NOTHROW(FCALL ev_unary)(char **__restrict pp,
                        uintptr_t *presult,
                        unsigned int flags) {
	char *p = *pp;
	char ch;
	uintptr_t value;
nextch:
	ch = *p++;
	switch (ch) {

	case '0':
		if (*p == 'x') {
			++p;
do_parse_as_hex:
			value = STRTOPTR(p, &p, 16);
			if (isalnum(*p))
				return ev_errorf(flags, DBGSTR("Invalid alnum %Q after hex constant"), *p);
		} else if (*p == 'b') {
			++p;
			value = STRTOPTR(p, &p, 2);
			if (isalnum(*p))
				return ev_errorf(flags, DBGSTR("Invalid alnum %Q after binary constant"), *p);
		} else {
			char *iter;
	case '1' ... '9':
			iter = p;
			--p;
			while (*iter >= '0' && *iter <= '9')
				++iter;
			if ((*iter >= 'a' && *iter <= 'f') ||
				(*iter >= 'A' && *iter <= 'F'))
				goto do_parse_as_hex;
			if (!(flags & DBG_EVALADDR_FLAG_NO_HEX)) {
				iter = strlstrip(iter);
				/* Only parse as hex, if a hex number is everything that was given! */
				if (!*iter)
					goto do_parse_as_hex;
			} else if (*p == '0') {
				/* Parse as octal */
				value = STRTOPTR(p, &p, 8);
			} else {
				value = STRTOPTR(p, &p, 10);
			}
			if (isalnum(*p))
				return ev_errorf(flags, DBGSTR("Invalid alnum %Q after decimal constant"), *p);
		}
		break;

	case 'a' ... 'f':
	case 'A' ... 'F':
		/* Check  if there are any non-hex characters.
		 * If so,  this has  to  be a  register  name.
		 * Otherwise, it's a hex number without prefix */
		{
			char *iter = p;
			while ((*iter >= '0' && *iter <= '9') ||
			       (*iter >= 'a' && *iter <= 'f') ||
			       (*iter >= 'A' && *iter <= 'F'))
				++iter;
			if (!*iter || isspace(*iter)) {
				--p;
				goto do_parse_as_hex;
			}
		}
		ATTR_FALLTHROUGH
	case 'g' ... 'z':
	case 'G' ... 'Z':
	case '_':
		/* Register name */
		{
			char *name_start;
			name_start = p - 1;
			__IF0 {
	case '%': case '$':
				name_start = p;
			}
			for (;; ++p) {
				ch = *p;
				if (isalnum(ch))
					continue;
				if (ch == '.' || ch == '_')
					continue;
				break;
			}
			if (!dbg_getregbynamep(DBG_REGLEVEL_VIEW, name_start, (size_t)(p - name_start), &value))
				return ev_errorf(flags, DBGSTR("Invalid register %$q"), (size_t)(p - name_start), name_start);
		}
		break;

	case '.':
		/* Current address. */
		value = (uintptr_t)dbg_getpcreg(DBG_REGLEVEL_VIEW);
		break;

	case '+':
		flags |= DBG_EVALADDR_FLAG_NO_HEX;
		goto nextch;

	case '-':
		flags |= DBG_EVALADDR_FLAG_NO_HEX;
		if (!ev_unary(&p, presult, flags))
			goto err;
		if (presult)
			*(intptr_t *)presult = -*(intptr_t *)presult;
		goto done;

	case '(':
		flags |= DBG_EVALADDR_FLAG_NO_HEX;
		if (!ev_expr(&p, presult, flags))
			goto err;
		p = strlstrip(p);
		if (*p != ')')
			return ev_errorf(flags, DBGSTR("Unmatched `('"));
		break;

	case 0:
		return ev_errorf(flags, DBGSTR("Empty expression"));


	default:
		if (isspace(ch))
			goto nextch;
		return ev_errorf(flags, DBGSTR("Unexpected character %Q in expression"), ch);
	}
	if (presult)
		*presult = value;
done:
	*pp = p;
	return true;
err:
	return false;
}

PRIVATE ATTR_DBGTEXT bool
NOTHROW(FCALL ev_expr)(char **__restrict pp,
                       uintptr_t *presult,
                       unsigned int flags) {
	if (!ev_unary(pp, presult, flags))
		goto err;
	flags |= DBG_EVALADDR_FLAG_NO_HEX;
	/* TODO */

	return true;
err:
	return false;
}



/* Evaluate an address expression
 * @param: flags:  Set of `DBG_EVALADDR_FLAG_*'
 * @return: true:  Evaluation failed. (when `DBG_EVALADDR_FLAG_NO_ERROR' wasn't set,
 *                                     an error was already displayed to the user)
 * @return: false: Evaluation failed. */
PUBLIC ATTR_DBGTEXT bool
NOTHROW(FCALL dbg_evaladdr)(char const *__restrict expr,
                            uintptr_t *__restrict presult,
                            unsigned int flags) {
	char *p = (char *)expr;
	p = strlstrip(p);
	ev_current_expression = p;
	if (!ev_expr(&p, presult, flags))
		return false;
	p = strlstrip(p);
	if (*p != '\0')
		return ev_errorf(flags, DBGSTR("Unused trailing text %q after expression"), expr);
	return true;
}



DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_EVAL_C */
