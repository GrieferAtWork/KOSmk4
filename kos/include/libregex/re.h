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
#ifndef _LIBREGEX_RE_H
#define _LIBREGEX_RE_H 1

#include "api.h"

#include <bits/types.h>

#include <libc/malloc.h>

__DECL_BEGIN

/* RE instruction stream opcodes
 *
 * ================================================ Compilation ================================================
 *
 * Simple matches:
 *     >> "x"                   REOP_CHAR 'x'
 *     >> "abc"                 REOP_EXACT "abc"
 *     >> "."                   REOP_ANY
 *     >> "[<x>]"               REOP_CHAR 'x'            (can be used to escape other characters)
 *     >> "\\"                  REOP_CHAR '\'
 *     >> "\<x>"                REOP_CHAR 'x'            (caution: many characters here have special meaning!)
 *     >> "[a-z]"               REOP_BITSET "[a-z]"      (NOTE: multi-byte utf-8 characters are encoded using `REOP_CONTAINS')
 *     >> "[^a-z]"              REOP_BITSET_NOT "[a-z]"  (NOTE: multi-byte utf-8 characters are encoded using `REOP_CONTAINS_NOT')
 *     >> "\<0-9>"              REOP_GROUP_MATCH <0-9>   // Uses `REOP_GROUP_MATCH_NONEMPTY' if the references group doesn't match epsilon
 *     >> "\w"                  <[:symcont:]>            (HINT: Also allowed in []-bitsets)
 *     >> "\W"                  <[^:symcont:]>           (HINT: Also allowed in []-bitsets)
 *     >> "\n"                  <[:lf:]>                 (HINT: Also allowed in []-bitsets)  [kos-extension]
 *     >> "[:<foo>:]"           REOP_UTF8_IS<foo>                                            [some classes are kos extensions]
 *     >> "[^:<foo>:]"          REOP_UTF8_IS<foo>_NOT                                        [kos-extension]
 *     >> "[:digit<OP><N>:]"    REOP_UTF8_ISDIGIT_<OP> <N>                                   [kos-extension]
 *     >> "[:numeric<OP><N>:]"  REOP_UTF8_ISNUMERIC_<OP> <N>                                 [kos-extension]
 *     >> "\s"                  <[:space:]>              (HINT: Also allowed in []-bitsets)  [python-extension]
 *     >> "\S"                  <[^:space:]>             (HINT: Also allowed in []-bitsets)  [python-extension]
 *     >> "\d"                  <[:digit:]>              (HINT: Also allowed in []-bitsets)  [python-extension]
 *     >> "\D"                  <[^:digit:]>             (HINT: Also allowed in []-bitsets)  [python-extension]
 *
 * Location assertion (note: it is a syntax error to use these with repetition expressions):
 *     >> "^"            REOP_AT_SOL
 *     >> "$"            REOP_AT_EOL
 *     >> "\`"           REOP_AT_SOI
 *     >> "\'"           REOP_AT_EOI
 *     >> "\b"           REOP_AT_WOB
 *     >> "\B"           REOP_AT_WOB_NOT
 *     >> "\<"           REOP_AT_SOW
 *     >> "\>"           REOP_AT_EOW
 *     >> "\_<"          REOP_AT_SOS
 *     >> "\_>"          REOP_AT_EOS
 *     >> "\A"           REOP_AT_SOI  [python-extension]
 *     >> "\Z"           REOP_AT_EOI  [python-extension]
 *
 * Expressions:
 *     >> "(X|Y)"        REOP_GROUP_START {GID}
 *     >>                REOP_JMP_ONFAIL  1f
 *     >>                <X>
 *     >>                REOP_JMP         2f
 *     >>                # HINT: Another `REOP_JMP_ONFAIL' to <Z> would go here if it existed
 *     >>             1: <Y>
 *     >>             2: REOP_GROUP_END   {GID}  // Uses `REOP_GROUP_END_NONEMPTY' if `!"".rematches("(<X>|<Y>)")'
 *
 *     >> "X?"           REOP_JMP_ONFAIL 1f
 *     >>                <X>
 *     >>             1:
 *
 *     >> "X*"        1: REOP_JMP_ONFAIL 2f
 *     >>                <X>
 *     >>                REOP_JMP        1b
 *     >>             2:
 *
 *     >> "X+"        1: <X>
 *     >>                REOP_JMP_AND_RETURN_ONFAIL 1b
 *
 *     >> "X{0}"         REOP_NOP        // Or just no instruction at all
 *
 *     >> "X{n,0}"       REOP_NOP        // Or just no instruction at all
 *
 *     >> "X{1}"         <X>
 *
 *     >> "X{0,1}"       <X?>
 *
 *     >> "X{0,}"        <X*>
 *
 *     >> "X{1,}"        <X+>
 *
 *     >> "X{n}"         REOP_SETVAR  {VAR = n}
 *     >>             1: <X>
 *     >>                REOP_DEC_JMP {VAR}, 1b
 *
 *     >> "X{n,}"        REOP_SETVAR  {VAR = n}
 *     >>             1: <X>
 *     >>                REOP_DEC_JMP {VAR}, 1b
 *     >>                REOP_JMP_ONFAIL      2f
 *     >>                REOP_JMP     1b
 *
 *     >> "X{1,m}"       REOP_SETVAR  {VAR1 = (m - 1)}
 *     >>            1:  <X>
 *     >>                REOP_JMP_ONFAIL      2f
 *     >>                REOP_DEC_JMP {VAR1}, 1b
 *     >>            2:
 *
 *     >> "X{n,m}"       REOP_SETVAR  {VAR1 = n - 1}
 *     >>                REOP_SETVAR  {VAR2 = (m - n)}
 *     >>            1:  <X>
 *     >>                REOP_DEC_JMP {VAR1}, 1b
 *     >>                REOP_JMP_ONFAIL      2f
 *     >>                REOP_DEC_JMP {VAR2}, 1b
 *     >>            2:
 *
 * HINT: Using the above  compilation patterns, inserting  code in front  of
 *       already-compiled code can simply be done whilst ignoring the chance
 *       of  relocations. This is because jumps are relative, and will never
 *       jump out of- or into some block "<X>".
 *       As  such, in order  to compile (e.g.)  "X{n,m}", simply compile "X",
 *       then memmoveup() its bytecode to insert the 2 `REOP_SETVAR' opcodes,
 *       with the guaranty that no jump offsets ever need to be adjusted.
 *
 * NOTES:
 * - "on-failure stack" elements only consist of "{ RESUME_PC, INPUT_POINTER }"
 * - Whenever a mismatch happens, the top-most element of the  "on-failure stack"
 *   is popped, which in turn contains the address of the next REOP_* instruction
 *   with which to continue, as well as the input pointer that should be restored
 *
 *
 *
 * TODO: "(?<=X)"   -- Current input position must be preceded by "X"
 * TODO: "(?<!X)"   -- Current input position must not be preceded by "X"
 * TODO: "(?=X)"    -- Current input position must be succeeded by "X"
 * TODO: "(?!X)"    -- Current input position must not be succeeded by "X"
 * TODO: Support for other (?)-extensions
 */


/* Regex opcodes (always encoded as a single byte) */
enum {

	/* Opcodes for matching (and thus: consuming) input */
	REOP_EXACT,                /* [+1+n] Followed by 1 byte N = *PC++, followed by N more bytes that must be matched exactly (N must be >= 2) */
	REOP_ANY,                  /* Match any character */
	REOP_CHAR,                 /* [+1] Followed by 1 byte that must be matched exactly */
	REOP_CONTAINS,             /* [+1+n] Followed by a COUNT-byte, followed by a `COUNT'-byte long utf-8 string (matches utf-8 character contained in said string). */
	REOP_CONTAINS_NOT,         /* [+1+n] Followed by a COUNT-byte, followed by a `COUNT'-byte long utf-8 string (matches utf-8 character not contained in said string). */
	REOP_BITSET,               /* [+1+n] Followed by a LAYOUT-byte, followed by `REOP_BITSET_LAYOUT_GETBYTES(LAYOUT)' bitset bytes.
	                            * >> bool is_char_in_set(byte_t const *layout_ptr, uint8_t ch) {
	                            * >>     uint8_t layout      = *layout_ptr++;
	                            * >>     uint8_t minch       = REOP_BITSET_LAYOUT_GETBASE(layout);
	                            * >>     uint8_t bitset_size = REOP_BITSET_LAYOUT_GETBYTES(layout);
	                            * >>     uint8_t bitset_bits = bitset_size * 8;
	                            * >>     if (OVERFLOW_USUB(ch, minch, &ch))
	                            * >>         return false;
	                            * >>     if (ch >= bitset_bits)
	                            * >>         return false;
	                            * >>     return (layout_ptr[ch / 8] & (1 << (ch % 8))) != 0;
	                            * >> }
	                            * NOTE: If the bitset would need to contain non-ascii characters, `REOP_CONTAINS' is used instead. */
	REOP_BITSET_NOT,           /* [+1+n] Same as REOP_BITSET, but the return value of `is_char_in_set' is inverted */
	REOP_GROUP_MATCH,          /* [+1] Re-match the contents of the (N = *PC++)'th already-matched group; If group start/end aren't,
	                            * triggers a match-failure. If nothing was matched, same special behavior as with  `REOP_GROUP_END'. */
	REOP_GROUP_MATCH_NONEMPTY, /* [+1] Like `REOP_GROUP_MATCH', but allowed to assume that the group was non-empty. */

	/* Special trait classes */
	REOP_UTF8_ISDIGIT_EQ,      /* [+1] Match `[unicode_]isdigit(ch) && unicode_getnumeric(ch) == *PC++' */
	REOP_UTF8_ISDIGIT_NE,      /* [+1] Match `[unicode_]isdigit(ch) && unicode_getnumeric(ch) != *PC++' */
	REOP_UTF8_ISDIGIT_LO,      /* [+1] Match `[unicode_]isdigit(ch) && unicode_getnumeric(ch) <  *PC++' */
	REOP_UTF8_ISDIGIT_LE,      /* [+1] Match `[unicode_]isdigit(ch) && unicode_getnumeric(ch) <= *PC++' */
	REOP_UTF8_ISDIGIT_GR,      /* [+1] Match `[unicode_]isdigit(ch) && unicode_getnumeric(ch) >  *PC++' */
	REOP_UTF8_ISDIGIT_GE,      /* [+1] Match `[unicode_]isdigit(ch) && unicode_getnumeric(ch) >= *PC++' */
	REOP_UTF8_ISNUMERIC_EQ,    /* [+1] Match `unicode_isnumeric(ch) && unicode_getnumeric(ch) == *PC++' */
	REOP_UTF8_ISNUMERIC_NE,    /* [+1] Match `unicode_isnumeric(ch) && unicode_getnumeric(ch) != *PC++' */
	REOP_UTF8_ISNUMERIC_LO,    /* [+1] Match `unicode_isnumeric(ch) && unicode_getnumeric(ch) <  *PC++' */
	REOP_UTF8_ISNUMERIC_LE,    /* [+1] Match `unicode_isnumeric(ch) && unicode_getnumeric(ch) <= *PC++' */
	REOP_UTF8_ISNUMERIC_GR,    /* [+1] Match `unicode_isnumeric(ch) && unicode_getnumeric(ch) >  *PC++' */
	REOP_UTF8_ISNUMERIC_GE,    /* [+1] Match `unicode_isnumeric(ch) && unicode_getnumeric(ch) >= *PC++' */
#define REOP_UTF8_MIN REOP_UTF8_ISCNTRL
	REOP_UTF8_ISCNTRL,         /* [+0] consume trait `[unicode_]iscntrl(ch) == true' */
	REOP_UTF8_ISCNTRL_NOT,     /* [+0] consume trait `[unicode_]iscntrl(ch) == false' */
	REOP_UTF8_ISSPACE,         /* [+0] consume trait `[unicode_]isspace(ch) == true' */
	REOP_UTF8_ISSPACE_NOT,     /* [+0] consume trait `[unicode_]isspace(ch) == false' */
	REOP_UTF8_ISUPPER,         /* [+0] consume trait `[unicode_]isupper(ch) == true' */
	REOP_UTF8_ISUPPER_NOT,     /* [+0] consume trait `[unicode_]isupper(ch) == false' */
	REOP_UTF8_ISLOWER,         /* [+0] consume trait `[unicode_]islower(ch) == true' */
	REOP_UTF8_ISLOWER_NOT,     /* [+0] consume trait `[unicode_]islower(ch) == false' */
	REOP_UTF8_ISALPHA,         /* [+0] consume trait `[unicode_]isalpha(ch) == true' */
	REOP_UTF8_ISALPHA_NOT,     /* [+0] consume trait `[unicode_]isalpha(ch) == false' */
	REOP_UTF8_ISDIGIT,         /* [+0] consume trait `[unicode_]isdigit(ch) == true' */
	REOP_UTF8_ISDIGIT_NOT,     /* [+0] consume trait `[unicode_]isdigit(ch) == false' */
	REOP_UTF8_ISXDIGIT,        /* [+0] consume trait `[unicode_]isxdigit(ch) == true' */
	REOP_UTF8_ISXDIGIT_NOT,    /* [+0] consume trait `[unicode_]isxdigit(ch) == false' */
	REOP_UTF8_ISALNUM,         /* [+0] consume trait `[unicode_]isalnum(ch) == true' */
	REOP_UTF8_ISALNUM_NOT,     /* [+0] consume trait `[unicode_]isalnum(ch) == false' */
	REOP_UTF8_ISPUNCT,         /* [+0] consume trait `[unicode_]ispunct(ch) == true' */
	REOP_UTF8_ISPUNCT_NOT,     /* [+0] consume trait `[unicode_]ispunct(ch) == false' */
	REOP_UTF8_ISGRAPH,         /* [+0] consume trait `[unicode_]isgraph(ch) == true' */
	REOP_UTF8_ISGRAPH_NOT,     /* [+0] consume trait `[unicode_]isgraph(ch) == false' */
	REOP_UTF8_ISPRINT,         /* [+0] consume trait `[unicode_]isprint(ch) == true' */
	REOP_UTF8_ISPRINT_NOT,     /* [+0] consume trait `[unicode_]isprint(ch) == false' */
	REOP_UTF8_ISBLANK,         /* [+0] consume trait `[unicode_]isblank(ch) == true' */
	REOP_UTF8_ISBLANK_NOT,     /* [+0] consume trait `[unicode_]isblank(ch) == false' */
	REOP_UTF8_ISSYMSTRT,       /* [+0] consume trait `[unicode_]issymstrt(ch) == true' */
	REOP_UTF8_ISSYMSTRT_NOT,   /* [+0] consume trait `[unicode_]issymstrt(ch) == false' */
	REOP_UTF8_ISSYMCONT,       /* [+0] consume trait `[unicode_]issymcont(ch) == true' */
	REOP_UTF8_ISSYMCONT_NOT,   /* [+0] consume trait `[unicode_]issymcont(ch) == false' */
	REOP_UTF8_ISTAB,           /* [+0] consume trait `unicode_istab(ch) == true' */
	REOP_UTF8_ISTAB_NOT,       /* [+0] consume trait `unicode_istab(ch) == false' */
	REOP_UTF8_ISWHITE,         /* [+0] consume trait `unicode_iswhite(ch) == true' */
	REOP_UTF8_ISWHITE_NOT,     /* [+0] consume trait `unicode_iswhite(ch) == false' */
	REOP_UTF8_ISEMPTY,         /* [+0] consume trait `unicode_isempty(ch) == true' */
	REOP_UTF8_ISEMPTY_NOT,     /* [+0] consume trait `unicode_isempty(ch) == false' */
	REOP_UTF8_ISLF,            /* [+0] consume trait `unicode_islf(ch) == true' */
	REOP_UTF8_ISLF_NOT,        /* [+0] consume trait `unicode_islf(ch) == false' */
	REOP_UTF8_ISHEX,           /* [+0] consume trait `unicode_ishex(ch) == true' */
	REOP_UTF8_ISHEX_NOT,       /* [+0] consume trait `unicode_ishex(ch) == false' */
	REOP_UTF8_ISTITLE,         /* [+0] consume trait `unicode_istitle(ch) == true' */
	REOP_UTF8_ISTITLE_NOT,     /* [+0] consume trait `unicode_istitle(ch) == false' */
	REOP_UTF8_ISNUMERIC,       /* [+0] consume trait `unicode_isnumeric(ch) == true' */
	REOP_UTF8_ISNUMERIC_NOT,   /* [+0] consume trait `unicode_isnumeric(ch) == false' */
#define REOP_UTF8_MAX REOP_UTF8_ISNUMERIC_NOT

	/* Opcodes for asserting the current position in input (these don't consume anything) */
	REOP_AT_SOI,     /* [+0] Start-of-input */
	REOP_AT_EOI,     /* [+0] End-of-input */
	REOP_AT_SOL,     /* [+0] Start-of-line (REOP_AT_SOI, or following a line-feed) */
	REOP_AT_EOL,     /* [+0] End-of-line (REOP_AT_EOI, or preceding a line-feed) */
	REOP_AT_WOB,     /* [+0] WOrdBoundary (preceding and next character have non-equal `issymcont(ch)'; OOB counts as `issymcont == false') */
	REOP_AT_WOB_NOT, /* [+0] NOT WOrdBoundary (preceding and next character have equal `issymcont(ch)'; OOB counts as `issymcont == false') */
	REOP_AT_SOW,     /* [+0] StartOfWord (preceding and next character are `!issymcont(lhs) && issymcont(rhs)'; OOB counts as `issymcont == false') */
	REOP_AT_EOW,     /* [+0] EndOfWord (preceding and next character are `issymcont(lhs) && !issymcont(rhs)'; OOB counts as `issymcont == false') */
	REOP_AT_SOS,     /* [+0] StartOfSymbol (preceding and next character are `!issymcont(lhs) && issymstrt(rhs)'; OOB counts as `issymcont[/strt] == false') */
#define REOP_AT_EOS REOP_AT_EOW

	/* Opcodes for expression logic and processing. */
	REOP_GROUP_START,           /* [+1] Mark the start of the (N = *PC++)'th group; open "(" (current input pointer is written to `regmatch_t[N].rm_so') */
	REOP_GROUP_END,             /* [+1] Mark the end of the (N = *PC++)'th group; closing ")" (current input pointer is written to `regmatch_t[N].rm_eo')
	                             * If nothing was matched by the group:
	                             * - If the next opcode is one of [REOP_JMP, REOP_JMP_AND_RETURN_ONFAIL],  with
	                             *   the  jump pointing at a `REOP_GROUP_START' opcode referencing group N, the
	                             *   jmp-instruction is skipped over and the one that follows it gets executed.
	                             * - The same is also done for `REOP_DEC_JMP', only that in this case, a sequence
	                             *   - `REOP_JMP_ONFAIL 2f; REOP_DEC_JMP {*}, 1b; 2:'
	                             *   - `REOP_JMP_ONFAIL 2f; REOP_JMP 1b; 2:'
	                             *   also gets skipped (when 1b points to the group's `REOP_GROUP_START' opcode)
	                             */
	REOP_GROUP_END_NONEMPTY,    /* [+1] Same as `REOP_GROUP_END', but allowed to assume that group doesn't match epsilon */
	REOP_JMP,                   /* [+2] 16-bit, signed, relative jump (relative to instruction end) */
	REOP_JMP_ONFAIL,            /* [+2] push onto the "on-failure stack" a 16-bit, signed, relative addr */
	REOP_JMP_AND_RETURN_ONFAIL, /* [+2] push onto the "on-failure stack" the address of the next instruction before doing `REOP_JMP' */
	REOP_SETVAR,                /* [+2] VAR = VARS[*PC++]; VAR = *PC++; */
	REOP_DEC_JMP,               /* [+3] VAR = VARS[*PC++]; if VAR != 0, do `--VAR', followed by `REOP_JMP'; else, do nothing (and leave `VAR' unchanged) */
	REOP_NOP,                   /* [+0] No-op (for padding to get alignment right) */
	REOP_MATCHED,               /* [+0] Text has been matched (end of instruction stream)
	                             * If  the "on-failure stack" is  non-empty (and the  current match isn't perfect),
	                             * the current match is saved as a candidate, and the "on-failure stack" is popped.
	                             * Extra candidates are compared against prior ones, and the "best" one is  finally
	                             * used  (note that a  candidate consists of `{ end_input_pointer, regmatch_t[] }')
	                             * Candidate A is better than B if `A.end_input_pointer > B.end_input_pointer' */
};

/* Helper macros for `REOP_BITSET' and `REOP_BITSET_NOT' */
#define REOP_BITSET_LAYOUT_GETBYTES(layout) (((layout)&0x1f) + 1)
#define REOP_BITSET_LAYOUT_GETBASE(layout)  ((layout)&0xe0)



/* Regex syntax flags */
#define RE_SYNTAX_BACKSLASH_ESCAPE_IN_LISTS 0x00000001 /* '\' can be used in bitsets: '[a\[\]\-]' */
#define RE_SYNTAX_ESCAPED_PLUS_QM           0x00000002 /* If clear: '+' and '?' are operators; '\+' and '\?' are literals; if set: the opposite is the case. */
#define RE_SYNTAX_CHAR_CLASSES              0x00000004 /* Support for char-classes (e.g. `[:alpha:]') */
/* TODO: More syntax flags (compatible with gLibc's `RE_*' syntax flags from <regex.h>) */

/* Regex compiler structure */
struct re_compiler {
	char const *rec_pat;    /* [1..1] Pointer to next pattern-character that has yet to be compiled. */
	__byte_t   *rec_cbase;  /* [?..1][<= rec_cend] Base-pointer for output code-buffer. */
	__byte_t   *rec_cend;   /* [?..1][>= rec_cbase] End-pointer for output code-buffer. */
	__byte_t   *rec_cptr;   /* [?..1][>= rec_cbase && <= rec_cend] Pointer to next unset opcode in code-buffer. */
	__uint8_t   rec_ngrp;   /* # of groups currently defined / id of next group */
	__uint8_t   rec_nvar;   /* # of variables referenced by code / id of next unreferenced variable  */
	__uint32_t  rec_syntax; /* [const] RE syntax flags (set of `RE_SYNTAX_*') */
};

#define re_compiler_init(self, pattern) \
	((self)->rec_pat   = (pattern),     \
	 (self)->rec_cbase = __NULLPTR,     \
	 (self)->rec_cend  = __NULLPTR,     \
	 (self)->rec_cptr  = __NULLPTR,     \
	 (self)->rec_ngrp  = 0,             \
	 (self)->rec_nvar  = 0)
#define re_compiler_fini(self, pattern) \
	(void)__libc_free((self)->rec_cbase)




__DECL_END

#endif /* !_LIBREGEX_RE_H */
