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
#ifndef _ASM_CRT_REGEX_H
#define _ASM_CRT_REGEX_H 1

#include <__crt.h>

/* Regex error codes, as returned by `regcomp(3)', `regexec(3)', and other functions. */
#define __REG_ENOSYS   (-1) /* Returned when libc.so fails to load `libregex.so' for some reason */
#define __REG_NOERROR  0    /* Success. */
#define __REG_NOMATCH  1    /* Didn't find a match (for `regexec(3)'). */
#define __REG_BADPAT   2    /* General pattern syntax error. */
#define __REG_ECOLLATE 3    /* ??? */
#define __REG_ECTYPE   4    /* Invalid/unknown character class name. */
#define __REG_EESCAPE  5    /* Trailing '\'. */
#define __REG_ESUBREG  6    /* Back reference to group that was never initialized. */
#define __REG_EBRACK   7    /* Unmatched '['. */
#define __REG_EPAREN   8    /* Unmatched '('. */
#define __REG_EBRACE   9    /* Unmatched '{'. */
#define __REG_BADBR    10   /* Invalid contents of '{...}'. */
#define __REG_ERANGE   11   /* Invalid range end (e.g. '[z-a]'). */
#define __REG_ESPACE   12   /* Out of memory. */
#define __REG_BADRPT   13   /* Nothing is preceding '+', '*', '?' or '{'. */
#if defined(__CRT_KOS) || defined(__CRT_GLC)
#define __REG_EEND     14   /* Unexpected end of pattern. */
#define __REG_ESIZE    15   /* Too large (pattern violates some hard limit that isn't the currently available ram) */
#define __REG_ERPAREN  16   /* Unmatched ')' (only when `RE_UNMATCHED_RIGHT_PAREN_ORD' was set) */
#ifdef __CRT_KOS
#define __REG_EILLSEQ  17   /* Illegal unicode character (when `RE_NO_UTF8' wasn't set) */
#define __REG_EILLSET  18   /* Tried to combine raw bytes with unicode characters in charsets (e.g. "[Ä\xC3]") */
#define __REG_ECOUNT   19   /* # of defined regex error codes. */
#else /* __CRT_KOS */
#define __REG_ECOUNT   17   /* # of defined regex error codes. */
#endif /* !__CRT_KOS */
#elif defined(__NetBSD__)
#define __REG_EMPTY    14   /* ??? */
#define __REG_ASSERT   15   /* ??? */
#define __REG_INVARG   16   /* ??? */
#define __REG_EILLSEQ  17   /* Illegal unicode character (when `RE_NO_UTF8' wasn't set) */
#define __REG_ECOUNT   18   /* # of defined regex error codes. */
#define __REG_ATOI     255  /* ??? */
#define __REG_ITOA     0400 /* ??? */
#else /* ... */
#define __REG_ECOUNT   17   /* # of defined regex error codes. */
#endif /* ... */



/* Regex syntax options */
#define __RE_BACKSLASH_ESCAPE_IN_LISTS 0x00000001 /* '\' can be used to escape characters in sets: '[a\[\]\-]' */
#define __RE_BK_PLUS_QM                0x00000002 /* If clear: '+' and '?' are operators and '\+' and '\?' are literals; if set: the opposite is the case. */
#define __RE_CHAR_CLASSES              0x00000004 /* Support for char-classes (e.g. `[[:alpha:]]') */
#define __RE_CONTEXT_INDEP_ANCHORS     0x00000008 /* '^' and '$' are always anchors (as opposed to only at the start/end or after/before a '(' and ')') */
#define __RE_CONTEXT_INDEP_OPS         0x00000010 /* Ignored... */
#define __RE_CONTEXT_INVALID_OPS       0x00000020 /* '*', '+', '{' and '?' appearing at the start or after '(' or '|' results in `RE_BADRPT'; If not set, they are treated as literals. */
#define __RE_DOT_NEWLINE               0x00000040 /* '.' matches line-feeds (if not set, then it doesn't) */
#define __RE_DOT_NOT_NULL              0x00000080 /* '.' doesn't match '\0' (if not set, then it does) */
#define __RE_HAT_LISTS_NOT_NEWLINE     0x00000100 /* '[^abc]' will not match line-feeds (as though line-feeds were part of the set of characters never matched). If not set, [^]-sets will match them (unless explicitly added to the set of unmatched characters) */
#define __RE_INTERVALS                 0x00000200 /* Enable support for intervals: 'x{1,2}' (if not set, '{' and '}' are literals, though escaping is governed by `RE_NO_BK_BRACES') */
#define __RE_LIMITED_OPS               0x00000400 /* If set, support for '+', '?' and '|' is disabled (if not set, support is enabled, though escaping is governed by `RE_BK_PLUS_QM' and `RE_NO_BK_VBAR') */
#define __RE_NEWLINE_ALT               0x00000800 /* '\n' (embedded ASCII 10h) is treated like as an alias for the '|'-operator (if not set, '\n' is a literal; but note the kos-exception "\" "n", which matches that 2-character sequence against arbitrary line-feeds) */
#define __RE_NO_BK_BRACES              0x00001000 /* If set, '{...}' are intervals, and '\{' and '\}' are literals; if clear, the opposite is the case (iow: '\{...\}' is an interval) */
#define __RE_NO_BK_PARENS              0x00002000 /* If set, '(...)' are groups, and '\(' and '\)' are literals; if clear, the opposite is the case (iow: '\(...\)' is a group) */
#define __RE_NO_BK_REFS                0x00004000 /* If set, '\<1-9>' matches the literal <1-9>; if clear, '\<1-9>' is a back-reference */
#define __RE_NO_BK_VBAR                0x00008000 /* If set, '|' is the alternation operation: '(a|b)' (and '\|' is a literal); if clear, the opposite is the case (iow: '(a\|b)' matches '[ab]') */
#define __RE_NO_EMPTY_RANGES           0x00010000 /* If set, a []-set like '[z-a]' results in `RE_ERANGE'; if clear, it is equal to '[]' (iow: bad ranges are simply ignored) */
#define __RE_UNMATCHED_RIGHT_PAREN_ORD 0x00020000 /* If set, unmatched ')' are treated as literals; if clear, unmatched an ')' results in `RE_ERPAREN' */
#define __RE_NO_POSIX_BACKTRACKING     0x00040000 /* If set, return the first match, rather than the perfect one (s.a. `REOP_MATCHED' and `REOP_MATCHED_PERFECT') */
#define __RE_NO_GNU_OPS                0x00080000 /* If set, disable support for '\<', '\>', '\b', '\B', '\w', '\W', '\s', '\S', '\`' and "\'" */
#define __RE_DEBUG                     0x00100000 /* Ignored... */
#define __RE_INVALID_INTERVAL_ORD      0x00200000 /* Invalid intervals like "a{b" are treated as literals (i.e. like "a\{b") */
#define __RE_ICASE                     0x00400000 /* Casing is ignored by literal-matches, and '[[:lower:]]', '[[:upper:]]', '[[:title:]]' are aliases for '[[:alpha:]]' */
#define __RE_CARET_ANCHORS_HERE        0x00800000 /* Alias for `RE_CONTEXT_INDEP_ANCHORS', but only for '^', and used internally */
#define __RE_CONTEXT_INVALID_DUP       0x01000000 /* If set, '{' appearing at the start, or after '(', '|' or '}' results in `RE_BADRPT'; else, behavior is governed by `RE_CONTEXT_INVALID_OPS' */
#define __RE_NO_SUB                    0x02000000 /* Used to implement `RE_NOSUB' */
#ifdef __CRT_KOS
#define __RE_ANCHORS_IGNORE_EFLAGS     0x20000000 /* '^' and '$' operators will ignore `RE_EXEC_NOTBOL' and `RE_EXEC_NOTEOL' */
#define __RE_NO_UTF8                   0x40000000 /* If set, pattern is byte-based (rather than a utf-8 string; e.g. '[ä]' is like '[\xC3\xA4]'). Also disables support for '\uABCD', '\UABCDABCD' */
#define __RE_NO_KOS_OPS                0x80000000 /* If set, disable support for python- and kos-extensions: '\n', "[^:<foo>:]", '\d', '\D', '\0123', '\xAB', '\uABCD', '\UABCDABCD', '\A', '\Z' */
#endif /* __CRT_KOS */


/* Possible values for `struct re_pattern_buffer::regs_allocated' */
#define __REGS_UNALLOCATED 0 /* ??? */
#define __REGS_REALLOCATE  1 /* ??? */
#define __REGS_FIXED       2 /* ??? */

#define __RE_NREGS 30 /* ??? */


/* Flags for `regcomp(3)'s `cflags' argument. */
#define __REG_EXTENDED 0x0001 /* Use `RE_POSIX_MINIMAL_BASIC' instead of `RE_POSIX_BASIC' */
#define __REG_ICASE    0x0002 /* Ignore casing during matching (s.a. `RE_ICASE') */
#ifdef __NetBSD__
#define __REG_NOSUB    0x0004 /* `regexec(3)' will ignore the `nmatch' and `pmatch' arguments (s.a. `RE_NO_SUB'). */
#define __REG_NEWLINE  0x0008 /* Clears `RE_DOT_NEWLINE'; sets `RE_HAT_LISTS_NOT_NEWLINE | RE_ANCHORS_IGNORE_EFLAGS' */
#define __REG_NOSPEC   0x0010 /* ??? */
#define __REG_PEND     0x0020 /* ??? */
#define __REG_DUMP     0x0040 /* ??? */
#define __REG_GNU      0x0080 /* ??? */
#else /* __NetBSD__ */
#define __REG_NEWLINE  0x0004 /* Clears `RE_DOT_NEWLINE'; sets `RE_HAT_LISTS_NOT_NEWLINE | RE_ANCHORS_IGNORE_EFLAGS' */
#define __REG_NOSUB    0x0008 /* `regexec(3)' will ignore the `nmatch' and `pmatch' arguments (s.a. `RE_NO_SUB'). */
#endif /* !__NetBSD__ */



/* Flags for `regexec(3)'s `eflags' argument. */
#define __REG_NOTBOL   0x0001 /* '^' doesn't match the start of input data (but only at an actual begin-of-line) */
#define __REG_NOTEOL   0x0002 /* '$' doesn't match the end of input data (but only before an actual line-feed) */
#define __REG_STARTEND 0x0004 /* Use `pmatch[0]' on input to determine the search start/end-offsets
                               * in the input buffer (allowing '\0' to be included in input  data). */
#ifdef __NetBSD__
#define __REG_TRACE 00400
#define __REG_LARGE 01000
#define __REG_BACKR 02000
#endif /* __NetBSD__ */


#endif /* !_ASM_CRT_REGEX_H */
